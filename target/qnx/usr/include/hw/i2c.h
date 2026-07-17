/*
 * Copyright (c) 2015, 2022-2025, BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _I2C_LIB_H_INCLUDED
#define _I2C_LIB_H_INCLUDED

#include <devctl.h>
#include <stddef.h>
#include <stdint.h>

#ifndef	_PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#define I2CLIB_VERSION_MAJOR    (1U)
#define I2CLIB_VERSION_MINOR    (0U)
#define I2CLIB_REVISION         (0U)

typedef struct {
    unsigned char   major;
    unsigned char   minor;
    unsigned char   revision;
} i2c_libversion_t;

/*
 * These codes are returned by devctl DCMD_I2C_STATUS to provide the cause of
 * of a failed I2C transaction.
 */
typedef enum {
    I2C_STATUS_DONE      = 0x0001,   /* transaction completed (with or
                                        without error) */
    I2C_STATUS_ERROR     = 0x0002,   /* timeout/unknown error */
    I2C_STATUS_NACK      = 0x0010,   /* slave no-acknowledge */
    I2C_STATUS_ARBL      = 0x0020,   /* lost arbitration */
    I2C_STATUS_BUSY      = 0x0040,   /* timed out */
    I2C_STATUS_ABORT     = 0x0100,   /* transaction aborted */
    I2C_STATUS_ADDR_NACK = 0x0200,   /* I2C_STATUS_NACK is address NACK */
    I2C_STATUS_DATA_NACK = 0x0400    /* I2C_STATUS_NACK is data NACK */
} i2c_status_t;

#define MAX_I2C_ERROR   (I2C_STATUS_DATA_NACK)

/* Limit the data length for I2C transaction */
#define MAX_I2C_DATA_LEN   (4096U)

/* Limit number of registers to access for DCMD_I2C_REGACC */
#define MAX_I2C_NUM_REGSACC (512U)

typedef enum {
    I2C_ADDRFMT_10BIT   = 0x0001,
    I2C_ADDRFMT_7BIT    = 0x0002,
} i2c_addrfmt_t;

typedef enum {
    I2C_SPEED_STANDARD  = 0x0001,   /* up to 100 kbit/s */
    I2C_SPEED_FAST      = 0x0002,   /* up to 400 kbit/s */
    I2C_SPEED_HIGH      = 0x0004    /* up to 3.4 Mbit/s */
} i2c_speed_mode_t;

/*
 * I2C_CAPS_FORCE_STOP:
 *   This controller cannot keep the I2C bus active between individual messages
 *   and will always issue a STOP condition at the end of each message, even if
 *   the upper layer requests a repeated-START (no-STOP) sequence.
 *
 *   For such controllers, correct repeated-START behavior can only be achieved
 *   when the I2C framework submits multiple messages (e.g., write + read) as a
 *   single combined transaction through xfer(). This allows the controller to
 *   perform the internal repeated-START properly to maintain repeated-START
 *   semantics and prevent unwanted STOP conditions.
 *
 */
#define I2C_CAPS_FORCE_STOP  (1U << 0)

typedef struct {
    _Uint32t            speed_mode; /* supported speeds: I2C_SPEED_* */
    _Uint32t            addr_mode;  /* supported address fmts: I2C_ADDRFMT_* */
    _Uint32t            verbosity;  /* Driver verbosity level */
    _Uint32t            caps;       /* I2C controller/driver capabilities */
} i2c_driver_info_t;

typedef struct {
    _Uint32t            addr;   /* I2C address */
    _Uint32t            fmt;    /* 7- or 10-bit format */
} i2c_addr_t;

typedef struct {
    i2c_addr_t          slave;  /* slave address */
    _Uint32t            len;    /* length of send data in bytes */
    _Uint32t            stop;   /* send stop when complete? (0=no, 1=yes) */
} i2c_send_t;

typedef struct {
    i2c_addr_t          slave;  /* slave address */
    _Uint32t            len;    /* length of receive data in bytes */
    _Uint32t            stop;   /* send stop when complete? (0=no, 1=yes) */
} i2c_recv_t;

typedef struct {
    i2c_addr_t          slave;      /* slave address */
    _Uint32t            send_len;   /* length of send data in bytes */
    _Uint32t            recv_len;   /* length of receive data in bytes */
    _Uint32t            stop;       /* set stop when complete? */
} i2c_sendrecv_t;

typedef struct {
    uint8_t             clr;        /* 1: clear;  0: no changes */
    uint8_t             set;        /* 1: set;    0: no changes */
    uint8_t             toggle;     /* 1: toggle; 0: no changes */
} i2c_regops_t;

typedef struct {
    i2c_addr_t          slave;      /* slave address */
    uint32_t            addr;       /* register address, sent out in LSB order */
    uint32_t            addrlen;    /* address length in byte count */
    uint32_t            nregs;      /* number of registers to read; also length of receive data in bytes. nregs must be >= 1 */
    uint32_t            nregops;    /* number of register operations. nregops must be either 0 or equal to nregs */
    uint32_t            flags;
    #define  REGACC_RD_STOP  (1U << 0U)  /* set stop when reading register value complete */
    #define  REGACC_RESEND   (1U << 1U)  /* need to resend the send commands before register writing */
    /* followed by nregs recv buffer and then nregops regop structs and then send commands if needed */
} i2c_regacc_t;

/*
 * Resource Manager Interface
 */

/*
 * The following devctls are used by a client application
 * to control the I2C interface.
 */

#define _DCMD_I2C   (_DCMD_MISC)

#define DCMD_I2C_SET_BUS_SPEED      (__DIOT (_DCMD_I2C, 2, unsigned))
#define DCMD_I2C_SEND               (__DIOT (_DCMD_I2C, 5, i2c_send_t))
#define DCMD_I2C_RECV               (__DIOTF(_DCMD_I2C, 6, i2c_recv_t))
#define DCMD_I2C_SENDRECV           (__DIOTF(_DCMD_I2C, 7, i2c_sendrecv_t))
#define DCMD_I2C_DRIVER_INFO        (__DIOF (_DCMD_I2C, 8, i2c_driver_info_t))
#define DCMD_I2C_STATUS             (__DIOF (_DCMD_I2C, 9, i2c_status_t))
#define DCMD_I2C_BUS_RESET          (__DION (_DCMD_I2C, 10))
#define DCMD_I2C_SENDS              (__DIOT (_DCMD_I2C, 11, i2c_send_t))
#define DCMD_I2C_REGACC             (__DIOTF(_DCMD_I2C, 12, i2c_regacc_t))

/*
 * Driver interface
 */
typedef struct {
    /* size of this structure */
    size_t size;

    /*
     * Return version information
     * Returns:
     * 0    success
     * -1   failure
     */
    int (*version_info)(i2c_libversion_t *version);

    /*
     * Initialize master interface.
     * Returns a handle that is passed to all other functions.
     * Returns:
     * !NULL    success
     * NULL     failure
     */
    void *(*init)(int argc, char *argv[]);

    /*
     * Clean up driver.
     * Frees memory associated with "hdl".
     */
    void (*fini)(void *hdl);

    /*
     * Master send.
     * Parameters:
     * (in)     hdl         Handle returned from init()
     * (in)     buf         Buffer of data to send
     * (in)     len         Length in bytes of buf
     * (in)     stop        If !0, set stop condition when send completes
     * Returns:
     * bitmask of status bits
     */
    i2c_status_t (*send)(void *hdl, void *buf, unsigned int len,
                         unsigned int stop);
    /*
     * Master receive.
     * Parameters:
     * (in)     hdl         Handle returned from init()
     * (in)     buf         Buffer for received data
     * (in)     len         Length in bytes of buf
     * (in)     stop        If !0, set stop condition when recv completes
     * Returns:
     * bitmask of status bits
     */
    i2c_status_t (*recv)(void *hdl, void *buf, unsigned int len,
                         unsigned int stop);

    /*
     * Force the master to free the bus.
     * Returns when the stop condition has been sent.
     * Returns:
     * 0    success
     * -1   failure
     */
    int (*abort)(void *hdl, int rcvid);

    /*
     * Specify the target slave address.
     * Returns:
     * 0    success
     * -1   failure
     */
    int (*set_slave_addr)(void *hdl, unsigned int addr, i2c_addrfmt_t fmt);

    /*
     * Specify the bus speed.
     * If an invalid bus speed is requested, this function should return
     * failure and leave the bus speed unchanged.
     * Parameters:
     * (in)     speed       Bus speed. Units are implementation-defined.
     * (out)    ospeed      Actual bus speed (if NULL, this is ignored)
     * Returns:
     * 0    success
     * -1   failure
     */
    int (*set_bus_speed)(void *hdl, unsigned int speed, unsigned int *ospeed);

    /*
     * Request info about the driver.
     * Returns:
     * 0    success
     * -1   failure
     */
    int (*driver_info)(void *hdl, i2c_driver_info_t *info);

    /*
     * Handle a driver-specific devctl().
     * Parameters:
     * (in)     cmd         Device command
     * (i/o)    msg         Message buffer
     * (in)     msglen      Length of message buffer in bytes
     * (out)    nbytes      Bytes to return (<= msglen)
     * (out)    info        Extra status information returned by devctl
     * Returns:
     * EOK      success
     * errno    failure
     */
    int (*ctl)(void *hdl, int cmd, void *msg, int msglen,
               int *nbytes, int *info);

    /*
     * Reset i2c bus module.
     * Returns:
     * EOK    success
     * EIO   failure
     */
    int (*bus_reset)(void *hdl);

    /*
     * I2C master transfer(single or multi send/recv).
     * Parameters:
     * (in)     hdl         Handle returned from init()
     * (in)     send_buf    Buffer of data to send
     * (in)     send_len    Length in bytes of send_buf
     * (in)     recv_buf    Buffer for received data
     * (in)     recv_len    Length in bytes of recv_buf
     * Returns:
     * bitmask of status bits
     */
    i2c_status_t (*xfer)(void *const hdl, void *const send_buf, const uint32_t send_len,
                         void *const recv_buf, const uint32_t recv_len);
} i2c_master_funcs_t;

/*
 * Fills in the given table with the hardware-specific functions.
 * If a function table entry is unimplemented, it should
 * be left unchanged (and not set to NULL, etc.).
 * "funcs->size" should be set by whomever has allocated the
 * table. Don't change this.
 * Parameters:
 * (i/o)    funcs       Function table
 * (in)     tabsize     size of "funcs" in bytes
 * Returns:
 * 0    success
 * -1   failure
 */
typedef int (i2c_master_getfuncs_f)(i2c_master_funcs_t *funcs, int tabsize);
extern i2c_master_getfuncs_f   i2c_master_getfuncs;

#define I2C_ADD_FUNC(tabletype, table, entry, func, limit) \
    do { \
        if (offsetof(tabletype, entry) + sizeof((table)->entry) <= (size_t)(limit)) \
            (table)->entry = (func); \
    } while (0)

/*
 * Logging function for driver
 * Parameters:
 * (in)     verbosity   Verbosity level
 * (in)     level       Severity level
 * (in)     fmt         Logging message format
 * Returns:
 *  none
 */
extern void i2c_slogf(const unsigned verbosity, const unsigned level, const char *fmt, ...);

#endif
