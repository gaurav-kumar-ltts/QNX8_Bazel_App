#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>
#include <devctl.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/can_dcmd.h>
#include <sys/slog.h>
#include <hw/io-spi.h>

#define DEFAULT_SPI_DEVICE  "/dev/io-spi/spi0/dev0"
#define SPI_SPEED           16000000

/* MCP2515 SPI Commands */
#define MCP_RESET           0xC0
#define MCP_READ            0x03
#define MCP_WRITE           0x02
#define MCP_RTS_TX0         0x81

/* MCP2515 Registers */
#define MCP_CANCTRL         0x0F
#define MCP_CANSTAT         0x0E
#define MCP_TXB0SIDH        0x31
#define MCP_TXB0SIDL        0x32
#define MCP_TXB0DLC         0x35
#define MCP_TXB0DATA        0x36
#define MCP_RXB0DLC         0x66
#define MCP_RXB0DATA        0x67

static int spi_fd = -1;
static char spi_device_path[128] = DEFAULT_SPI_DEVICE;
static uint32_t spi_clock_rate = SPI_SPEED;
static int gpio_pin = 23;
static int unit_number = 0;
static int verbosity = 0;
static char mid_type[16] = "eid";

/* Mailbox names per spec */
static const char *mailboxes[] = { "rx0", "rx1", "tx2", "tx3", "tx4" };

typedef struct {
    const char *name;
    uint32_t eid_mid;
    uint32_t sid_mid;
    uint32_t current_mid;
    uint32_t filter;
} mailbox_config_t;

typedef struct {
    iofunc_attr_t attr;
    mailbox_config_t *mb_config;
} mcp2515_attr_t;

static mailbox_config_t mb_configs[] = {
    { "rx0", 0, 0x0,     0, 0 },
    { "rx1", 1, 0x40000, 1, 0 },
    { "tx2", 2, 0x80000, 2, 0 },
    { "tx3", 3, 0xC0000, 3, 0 },
    { "tx4", 4, 0x100000, 4, 0 }
};

/* ===== SPI Lower-Level Drivers ===== */

int spi_transfer(int fd, uint8_t *tx, uint8_t *rx, size_t len) {
    size_t size = sizeof(spi_xchng_t) + len;
    spi_xchng_t *msg = malloc(size);
    if (!msg) return -1;

    msg->nbytes = len;
    memcpy(msg->data, tx, len);

    if (devctl(fd, DCMD_SPI_DATA_XCHNG, msg, size, NULL) != EOK) {
        free(msg);
        return -1;
    }

    memcpy(rx, msg->data, len);
    free(msg);
    return 0;
}

int spi_init(int fd) {
    spi_cfg_t cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.clock_rate = spi_clock_rate;
    cfg.mode = SPI_MODE_WORD_WIDTH_8 | SPI_MODE_CPHA_0 | SPI_MODE_CPOL_0 | SPI_MODE_BODER_MSB;
    return devctl(fd, DCMD_SPI_SET_CONFIG, &cfg, sizeof(cfg), NULL);
}

int mcp2515_write_register(int fd, uint8_t reg, uint8_t value) {
    uint8_t tx[3] = { MCP_WRITE, reg, value };
    uint8_t rx[3] = { 0 };
    return spi_transfer(fd, tx, rx, 3);
}

int mcp2515_read_register(int fd, uint8_t reg, uint8_t *value) {
    uint8_t tx[3] = { MCP_READ, reg, 0x00 };
    uint8_t rx[3] = { 0 };
    if (spi_transfer(fd, tx, rx, 3) != 0) return -1;
    *value = rx[2];
    return 0;
}

int mcp2515_reset(int fd) {
    uint8_t tx[1] = { MCP_RESET };
    uint8_t rx[1] = { 0 };
    return spi_transfer(fd, tx, rx, 1);
}

int mcp2515_hw_init(int fd) {
    uint8_t canstat = 0;

    mcp2515_reset(fd);
    usleep(10000);

    mcp2515_write_register(fd, 0x2A, 0x00); // CNF1
    mcp2515_write_register(fd, 0x29, 0x91); // CNF2
    mcp2515_write_register(fd, 0x28, 0x01); // CNF3

    mcp2515_write_register(fd, MCP_CANCTRL, 0x00);
    usleep(10000);

    if (mcp2515_read_register(fd, MCP_CANSTAT, &canstat) == 0 && verbosity > 0) {
        slogf(_SLOG_SETCODE(_SLOGC_NETWORK, 0), _SLOG_INFO, 
              "[MCP2515 Driver] Controller CANSTAT = 0x%02X (GPIO: %d)", canstat, gpio_pin);
    }
    return 0;
}

/* ===== QNX Resource Manager Handlers ===== */

int io_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb) {
    int status;
    char rx_buffer[] = "testing\n";
    size_t nbytes = sizeof(rx_buffer) - 1;

    if ((status = iofunc_read_verify(ctp, msg, ocb, NULL)) != EOK)
        return status;

    if (msg->i.xtype & _IO_XTYPE_MASK)
        return EINVAL;

    if (ocb->offset > 0) {
        _IO_SET_READ_NBYTES(ctp, 0);
        return _RESMGR_NPARTS(0);
    }

    resmgr_msgwrite(ctp, rx_buffer, nbytes, 0);
    ocb->offset = nbytes;

    _IO_SET_READ_NBYTES(ctp, nbytes);
    return _RESMGR_NPARTS(0);
}

int io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb) {
    int status;
    char *buf;

    if ((status = iofunc_write_verify(ctp, msg, ocb, NULL)) != EOK)
        return status;

    if (msg->i.xtype & _IO_XTYPE_MASK)
        return EINVAL;

    buf = malloc(msg->i.nbytes);
    if (!buf) return ENOMEM;

    resmgr_msgread(ctp, buf, msg->i.nbytes, sizeof(msg->i));

    size_t payload_len = (msg->i.nbytes > 8) ? 8 : msg->i.nbytes;
    mcp2515_write_register(spi_fd, MCP_TXB0SIDH, 0x24); 
    mcp2515_write_register(spi_fd, MCP_TXB0SIDL, 0x60);
    mcp2515_write_register(spi_fd, MCP_TXB0DLC, payload_len);

    for (size_t i = 0; i < payload_len; i++) {
        mcp2515_write_register(spi_fd, MCP_TXB0DATA + i, (uint8_t)buf[i]);
    }

    uint8_t rts_tx[1] = { MCP_RTS_TX0 };
    uint8_t rts_rx[1] = { 0 };
    spi_transfer(spi_fd, rts_tx, rts_rx, 1);

    free(buf);

    _IO_SET_WRITE_NBYTES(ctp, msg->i.nbytes);
    return _RESMGR_NPARTS(0);
}

int io_devctl(resmgr_context_t *ctp, io_devctl_t *msg, RESMGR_OCB_T *ocb) {
    int status;
    size_t nbytes = 0;
    uint32_t *data;

    if ((status = iofunc_devctl_default(ctp, msg, ocb)) != _RESMGR_DEFAULT) {
        return status;
    }

    data = _DEVCTL_DATA(msg->i);
    mcp2515_attr_t *mcp_attr = (mcp2515_attr_t *)ocb->attr;
    mailbox_config_t *mb = mcp_attr ? mcp_attr->mb_config : NULL;

    switch (msg->i.dcmd) {
        case CAN_DEVCTL_SET_MID:
            if (data && mb) {
                mb->current_mid = *data;
            }
            nbytes = 0;
            status = EOK;
            break;

        case CAN_DEVCTL_SET_MFILTER:
            if (data && mb) {
                mb->filter = *data;
            }
            nbytes = 0;
            status = EOK;
            break;

        case CAN_DEVCTL_GET_MID:
            if (msg->i.nbytes >= sizeof(uint32_t)) {
                uint32_t *out_data = _DEVCTL_DATA(msg->o);
                *out_data = mb ? mb->current_mid : 0;
                nbytes = sizeof(uint32_t);
            }
            status = EOK;
            break;

        case CAN_DEVCTL_GET_MFILTER:
            if (msg->i.nbytes >= sizeof(uint32_t)) {
                uint32_t *out_data = _DEVCTL_DATA(msg->o);
                *out_data = mb ? mb->filter : 0;
                nbytes = sizeof(uint32_t);
            }
            status = EOK;
            break;

        case CAN_DEVCTL_READ_CANMSG_EXT: {
            uint8_t dlc = 0;
            uint8_t rx_data[8] = {0};

            // Read DLC from RXB0
            uint8_t tx_dlc[3] = { MCP_READ, MCP_RXB0DLC, 0 };
            uint8_t rx_dlc[3] = { 0 };
            if (spi_transfer(spi_fd, tx_dlc, rx_dlc, 3) == 0) {
                dlc = rx_dlc[2] & 0x0F;
                if (dlc > 8) dlc = 8;
            }

            // Read Data Payload from RXB0 if DLC > 0
            if (dlc > 0) {
                size_t transfer_size = 3 + dlc;
                uint8_t *tx_buf = malloc(transfer_size);
                uint8_t *rx_buf = malloc(transfer_size);
                if (tx_buf && rx_buf) {
                    memset(tx_buf, 0, transfer_size);
                    memset(rx_buf, 0, transfer_size);
                    tx_buf[0] = MCP_READ;
                    tx_buf[1] = MCP_RXB0DATA;

                    if (spi_transfer(spi_fd, tx_buf, rx_buf, transfer_size) == 0) {
                        for (int i = 0; i < dlc; i++) {
                            rx_data[i] = rx_buf[2 + i];
                        }
                    }
                }
                free(tx_buf);
                free(rx_buf);
            }

            if (msg->i.nbytes >= sizeof(struct can_msg)) {
                struct can_msg *can_out = _DEVCTL_DATA(msg->o);
                memset(can_out, 0, sizeof(struct can_msg));
                can_out->mid = mb ? mb->current_mid : 0;
                can_out->len = dlc;
                memcpy(can_out->dat, rx_data, dlc);
                nbytes = sizeof(struct can_msg);
            }
            status = EOK;
            break;
        }

        case CAN_DEVCTL_WRITE_CANMSG_EXT:
            nbytes = 0;
            status = EOK;
            break;

        default:
            return ENOTSUP;
    }

    memset(&msg->o, 0, sizeof(msg->o));
    msg->o.ret_val = status;
    return _RESMGR_PTR(ctp, &msg->o, sizeof(msg->o) + nbytes);
}

/* ===== Argument Parsing ===== */

void parse_arguments(int argc, char **argv) {
    int opt;
    struct option long_options[] = {
        { "mid", required_argument, 0, 'm' },
        { 0, 0, 0, 0 }
    };

    while ((opt = getopt_long(argc, argv, "s:c:g:u:v", long_options, NULL)) != -1) {
        switch (opt) {
            case 's':
                strncpy(spi_device_path, optarg, sizeof(spi_device_path) - 1);
                break;
            case 'c':
                spi_clock_rate = (uint32_t)strtoul(optarg, NULL, 10);
                break;
            case 'g':
                gpio_pin = atoi(optarg);
                break;
            case 'u':
                unit_number = atoi(optarg);
                break;
            case 'v':
                verbosity++;
                break;
            case 'm':
                strncpy(mid_type, optarg, sizeof(mid_type) - 1);
                break;
            default:
                break;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (strcmp(mid_type, "sid") == 0) {
            mb_configs[i].current_mid = mb_configs[i].sid_mid;
        } else {
            mb_configs[i].current_mid = mb_configs[i].eid_mid;
        }
    }
}

/* ===== Main Entry Point ===== */

int main(int argc, char **argv) {
    parse_arguments(argc, argv);

    dispatch_t *dpp;
    resmgr_io_funcs_t io_funcs;
    resmgr_connect_funcs_t connect_funcs;
    dispatch_context_t *ctp;
    resmgr_attr_t rattr;

    spi_fd = open(spi_device_path, O_RDWR);
    if (spi_fd < 0) {
        perror("[MCP2515 Driver] Failed to open SPI device");
        return EXIT_FAILURE;
    }

    if (spi_init(spi_fd) != 0 || mcp2515_hw_init(spi_fd) != 0) {
        fprintf(stderr, "[MCP2515 Driver] Failed to initialize hardware.\n");
        close(spi_fd);
        return EXIT_FAILURE;
    }

    dpp = dispatch_create();
    if (!dpp) {
        close(spi_fd);
        return EXIT_FAILURE;
    }

    iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &connect_funcs, _RESMGR_IO_NFUNCS, &io_funcs);
    io_funcs.read = io_read;
    io_funcs.write = io_write;
    io_funcs.devctl = io_devctl;

    memset(&rattr, 0, sizeof(rattr));
    rattr.flags = 0;

    char channel_path[64];
    snprintf(channel_path, sizeof(channel_path), "/dev/can%d", unit_number);

    for (int m = 0; m < 5; m++) {
        char path[128];
        snprintf(path, sizeof(path), "%s/%s", channel_path, mailboxes[m]);

        mcp2515_attr_t *mcp_attr = malloc(sizeof(mcp2515_attr_t));
        if (!mcp_attr) continue;

        iofunc_attr_init(&mcp_attr->attr, S_IFCHR | 0666, NULL, NULL);
        mcp_attr->mb_config = &mb_configs[m];

        int id = resmgr_attach(dpp, &rattr, path, _FTYPE_ANY, 0,
                               &connect_funcs, &io_funcs, &mcp_attr->attr);
        if (id == -1) {
            fprintf(stderr, "[MCP2515 Driver] Failed to attach %s: %s\n", path, strerror(errno));
            free(mcp_attr);
        } else {
            if (verbosity > 0) {
                slogf(_SLOG_SETCODE(_SLOGC_NETWORK, 0), _SLOG_INFO,
                      "[MCP2515 Driver] Registered node: %s (MID: 0x%X)", path, mb_configs[m].current_mid);
            }
        }
    }

    ctp = dispatch_context_alloc(dpp);

    while (1) {
        ctp = dispatch_block(ctp);
        dispatch_handler(ctp);
    }

    close(spi_fd);
    return EXIT_SUCCESS;
}