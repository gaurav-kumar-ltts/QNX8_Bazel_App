#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <devctl.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <hw/io-spi.h>

#define SPI_DEVICE      "/dev/io-spi/spi0/dev0"
#define CAN_DEV_NODE0   "/dev/can0"
#define CAN_DEV_NODE1   "/dev/can1"
#define SPI_SPEED       1000000

/* MCP2515 SPI Commands */
#define MCP_RESET       0xC0
#define MCP_READ        0x03
#define MCP_WRITE       0x02
#define MCP_RTS_TX0     0x81

/* MCP2515 Registers */
#define MCP_CANCTRL     0x0F
#define MCP_CANSTAT     0x0E
#define MCP_TXB0SIDH    0x31
#define MCP_TXB0SIDL    0x32
#define MCP_TXB0DLC     0x35
#define MCP_TXB0DATA    0x36

static int spi_fd = -1;

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
    cfg.clock_rate = SPI_SPEED;
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

    /* 1. Software Reset */
    mcp2515_reset(fd);
    usleep(10000);

    /* 2. Configure Bit Timing (500 kbps @ 16 MHz Oscillator) */
    mcp2515_write_register(fd, 0x2A, 0x00); // CNF1
    mcp2515_write_register(fd, 0x29, 0x91); // CNF2
    mcp2515_write_register(fd, 0x28, 0x01); // CNF3

    /* 3. Switch to Normal Mode */
    mcp2515_write_register(fd, MCP_CANCTRL, 0x00);
    usleep(10000);

    /* 4. Verify Mode Change */
    if (mcp2515_read_register(fd, MCP_CANSTAT, &canstat) == 0) {
        printf("[MCP2515 Driver] Controller CANSTAT = 0x%02X\n", canstat);
        fflush(stdout);
    }
    return 0;
}

/* ===== QNX Resource Manager Handlers ===== */

int io_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb) {
    int status;
    char rx_buffer[] = "CAN_FRAME_RX_DATA\n";
    size_t nbytes = sizeof(rx_buffer) - 1;

    if ((status = iofunc_read_verify(ctp, msg, ocb, NULL)) != EOK)
        return status;

    if (msg->i.xtype & _IO_XTYPE_MASK)
        return EINVAL;

    if (ocb->offset > 0) {
        _IO_SET_READ_NBYTES(ctp, 0);
        return _RESMGR_NPARTS(0);
    }

    /* Fixed: Pass 0 as offset for direct reply buffer transmission */
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

/* ===== Main Entry Point ===== */

int main(int argc, char **argv) {
    /* Suppress unused parameter warnings */
    (void)argc;
    (void)argv;

    dispatch_t *dpp;
    resmgr_io_funcs_t io_funcs;
    resmgr_connect_funcs_t connect_funcs;
    dispatch_context_t *ctp;
    resmgr_attr_t rattr;
    
    iofunc_attr_t ioattr0;
    iofunc_attr_t ioattr1;
    
    int resmgr_id0, resmgr_id1;

    spi_fd = open(SPI_DEVICE, O_RDWR);
    if (spi_fd < 0) {
        perror("[MCP2515 Driver] Failed to open SPI device");
        return EXIT_FAILURE;
    }

    if (spi_init(spi_fd) != 0 || mcp2515_hw_init(spi_fd) != 0) {
        fprintf(stderr, "[MCP2515 Driver] Failed to initialize MCP2515 hardware.\n");
        fflush(stderr);
        close(spi_fd);
        return EXIT_FAILURE;
    }

    dpp = dispatch_create();
    if (!dpp) {
        fprintf(stderr, "[MCP2515 Driver] Unable to allocate dispatch handle.\n");
        fflush(stderr);
        close(spi_fd);
        return EXIT_FAILURE;
    }

    iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &connect_funcs, _RESMGR_IO_NFUNCS, &io_funcs);
    io_funcs.read = io_read;
    io_funcs.write = io_write;

    iofunc_attr_init(&ioattr0, S_IFCHR | 0666, NULL, NULL);
    iofunc_attr_init(&ioattr1, S_IFCHR | 0666, NULL, NULL);

    memset(&rattr, 0, sizeof(rattr));
    rattr.flags = 0;

    resmgr_id0 = resmgr_attach(dpp, &rattr, CAN_DEV_NODE0, _FTYPE_ANY, 0,
                               &connect_funcs, &io_funcs, &ioattr0);
    if (resmgr_id0 == -1) {
        fprintf(stderr, "[MCP2515 Driver] Failed to attach %s: errno %d (%s)\n", 
                CAN_DEV_NODE0, errno, strerror(errno));
        fflush(stderr);
        close(spi_fd);
        return EXIT_FAILURE;
    }
    printf("[MCP2515 Driver] Registered %s successfully.\n", CAN_DEV_NODE0);
    fflush(stdout);

    resmgr_id1 = resmgr_attach(dpp, &rattr, CAN_DEV_NODE1, _FTYPE_ANY, 0,
                               &connect_funcs, &io_funcs, &ioattr1);
    if (resmgr_id1 == -1) {
        fprintf(stderr, "[MCP2515 Driver] Failed to attach %s: errno %d (%s)\n", 
                CAN_DEV_NODE1, errno, strerror(errno));
        fflush(stderr);
        close(spi_fd);
        return EXIT_FAILURE;
    }
    printf("[MCP2515 Driver] Registered %s successfully.\n", CAN_DEV_NODE1);
    fflush(stdout);

    ctp = dispatch_context_alloc(dpp);

    while (1) {
        ctp = dispatch_block(ctp);
        dispatch_handler(ctp);
    }

    close(spi_fd);
    return EXIT_SUCCESS;
}