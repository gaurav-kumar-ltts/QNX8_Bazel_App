/*
 * Copyright (c) 2022, BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#ifndef _IOSPI_H_INCLUDED
#define _IOSPI_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include <devctl.h>
#include <hw/dma.h>
#include <limits.h>
#include <hw/dma.h>
#include <semaphore.h>
#include <sys/slog.h>
#include <sys/slogcodes.h>
#include <sys/slog2.h>

#define IOSPI_NAME        "io-spi"
#define IOSPI_DEV_PATH    "/dev/io-spi/"

/*
 * SPI driver information
 */
#define SPI_VERSION_MAJOR    1
#define SPI_VERMAJOR_SHIFT   16
#define SPI_VERSION_MINOR    0
#define SPI_VERMINOR_SHIFT   8
#define SPI_REVISION         0
#define SPI_VERREV_SHIFT     0

#define SPI_FEATURE_DMA        (1 << 31)
/* DMA buffer alignment mask, alignment = 2^alignment */
#define SPI_FEATURE_DMA_ALIGN  0xFF

#define SPI_DRVR_NAME_LEN      20
#define SPI_BUS_NAME_LEN       20
#define SPI_DEV_NAME_LEN       20

typedef struct {
    uint32_t    version;
    char        name[SPI_DRVR_NAME_LEN];    /* Driver name */
    uint32_t    feature;
    uint32_t    verbosity;                  /* Driver verbosity level */
} spi_drvinfo_t;

typedef struct {
    uint32_t    mode;        /* SPI mode */
    uint32_t    clock_rate;  /* bus speed */
} spi_cfg_t;

typedef struct {
    int         devno;                       /* Device NO. Physical NO. */
    char        name[SPI_DEV_NAME_LEN];      /* Device name */
    uint32_t    current_clkrate;             /* Device current bus speed */
    spi_cfg_t   cfg;                         /* Device configuration */
} spi_devinfo_t;

typedef struct {
    uint32_t    nbytes;           /* Exchange data length */
    uint8_t     data[0];          /* Exchange data */
} spi_xchng_t;

/* SPI mode */
#define SPI_MODE_WORD_WIDTH_MASK   (0xFF)      /* Word width in bits mask */
#define SPI_MODE_WORD_WIDTH_8      (8)         /* 8-bit word width */
#define SPI_MODE_WORD_WIDTH_16     (16)        /* 16-bit word width */
#define SPI_MODE_WORD_WIDTH_32     (32)        /* 32-bit word width */

/* CPHA: Clock phase */
#define SPI_MODE_CPHA_0        (0 <<  8)    /* CPHA=0: First SCK transition at middle of data bit */
#define SPI_MODE_CPHA_1        (1 <<  8)    /* CPHA=1: First SCK transition at beginning of data bit */

/* CPOL: Clock polarity */
#define SPI_MODE_CPOL_0        (0 <<  9)    /* CPOL=0: leading edge is a rising edge, and trailing edge is a falling edge */
#define SPI_MODE_CPOL_1        (1 <<  9)    /* CPOL=1: leading edge is a falling edge, and trailing edge is a rising edge */

#define SPI_MODE_BODER_MSB     (1 << 10)

/* Chip select polarity */
#define SPI_MODE_CSPOL_HIGH    (1 << 11)
#define SPI_MODE_CSSTAT_HIGH   (1 << 12)
#define SPI_MODE_CSHOLD_HIGH   (1 << 13)

#define SPI_MODE_RDY_MASK      (3 << 14)    /* Ready signal control */
#define SPI_MODE_RDY_NONE      (0 << 14)
#define SPI_MODE_RDY_EDGE      (1 << 14)    /* Falling edge signal */
#define SPI_MODE_RDY_LEVEL     (2 << 14)    /* Low level signal */
#define SPI_MODE_IDLE_INSERT   (1 << 16)

/* SPI transaction buffer max bound */
#define SPI_BUF_MAX_64K            (0xFFFF)        /* SPI transaction buffer max bound is 64K */
#define SPI_BUF_MAX_128K           (0x1FFFF)       /* SPI transaction buffer max bound is 128K */

typedef struct _spi_ctrl spi_ctrl_t;
typedef struct _spi_resmgr_ctrl spi_resmgr_ctrl_t;
typedef struct _spi_global_cfg spi_global_cfg_t;
typedef struct _spi_bus spi_bus_t;
typedef struct _spi_funcs spi_funcs_t;
typedef struct _spi_dev spi_dev_t;

/*
 * The following devctls are used by a client application
 * to control the SPI interface.
 */

#define _DCMD_SPI               (_DCMD_MISC)

#define DCMD_SPI_SET_CONFIG     (__DIOT (_DCMD_SPI, 0x11, spi_cfg_t))
#define DCMD_SPI_GET_DRVINFO    (__DIOF (_DCMD_SPI, 0x12, spi_drvinfo_t))
#define DCMD_SPI_GET_DEVINFO    (__DIOF (_DCMD_SPI, 0x13, spi_devinfo_t))
#define DCMD_SPI_DATA_XCHNG     (__DIOTF(_DCMD_SPI, 0x14, spi_xchng_t))


/* SPI hardware device structure */
struct _spi_dev {
    iofunc_attr_t  attr;        /* Note: attr has to be the first member!!!
                                 * We'll use it to get the addr of spi_dev_t
                                 */

    int            parent_busno;/* Device parent bus No. */

    spi_devinfo_t  devinfo;

    uint32_t       cs_delay;    /* CS delay */

    uint32_t       devctrl;     /* SPI device control register value. Calculated by setcfg */

    int            resmgr_id;

    spi_bus_t      *parent_bus; /* The address of its parent bus node */

    spi_dev_t      *next;       /* Pointer to the next dev node */
};

/* Hardware interface between io-spi and SPI device driver */
struct _spi_funcs {

    /**
     *  @brief             SPI driver cleanup function.
     *  @param  hdl        SPI driver handler.
     *
     *  @return            Void.
     */
    void (*spi_fini)(void *const hdl);

    /**
     *  @brief             Get SPI driver info function.
     *  @param  hdl        SPI driver handler.
     *  @param  info       The pointer where you want to store drvinfo.
     *
     *  @return            Void.
     */
    void (*drvinfo)(const void *const hdl, spi_drvinfo_t *info);

    /**
     *  @brief             Get SPI device info function.
     *  @param  hdl        SPI driver handler.
     *  @param  spi_dev    SPI device structure.
     *  @param  info       The pointer where you want to store devinfo.
     *
     *  @return            Void.
     */
    void (*devinfo)(const void *const hdl, const spi_dev_t *const spi_dev, spi_devinfo_t *const info);

    /**
     *  @brief             Set SPI device configuration.
     *  @param hdl         SPI driver handler.
     *  @param spi_dev     SPI device structure pointer.
     *  @param cfg         The spi_cfg_t structure which stores the config info
     *
     *  @return            EOK --success otherwise fail
     */
    int (*setcfg)(const void *const hdl, spi_dev_t *spi_dev, const spi_cfg_t *const cfg);

    /**
     *  @brief             SPI transfer function.
     *  @param hdl         SPI driver handler.
     *  @param spi_dev     SPI device structure pointer.
     *  @param buf         The buffer which stores the transfer data.
     *  @param tnbytes     The number of transmit bytes.
     *  @param rnbytes     The number of receive bytes.
     *
     *  @return            EOK --success otherwise fail.
     */
    int (*xfer)(void *const hdl, spi_dev_t *const spi_dev, uint8_t *const buf, const uint32_t tnbytes, const uint32_t rnbytes);

    /**
     *  @brief             SPI DMA transfer function.
     *  @param hdl         SPI driver handler.
     *  @param spi_dev     SPI device structure pointer.
     *  @param addr        DMA address pointer.
     *  @param tnbytes     The number of transmit bytes.
     *  @param rnbytes     The number of receive bytes.
     *
     *  @return            EOK --success otherwise fail.
     */
    int (*dma_xfer)(void *const hdl, spi_dev_t *spi_dev, dma_addr_t *addr, const uint32_t tnbytes, const uint32_t rnbytes);

    /**
     *  @brief             Allocate DMA buffer.
     *  @param  hdl        SPI driver handler.
     *  @param  addr       DMA address pointer.
     *  @param  len        DMA buffer size.
     *
     *  @return            EOK --success otherwise fail.
     */
    int (*dma_allocbuf)(void *const hdl, dma_addr_t *addr, const uint32_t len);

    /**
     *  @brief             Free DMA buffer.
     *  @param  hdl        SPI driver handler.
     *  @param  addr       DMA address pointer.
     *
     *  @return            EOK --success otherwise fail.
     */
    int (*dma_freebuf)(void *const hdl, dma_addr_t *addr);
};

struct _spi_bus {
    spi_ctrl_t      *spi_ctrl;   /* The address of spi_ctrl structure */

    /* Each SPI bus has its own thread, dispatch and ctp */
    pthread_t           tid;
    dispatch_t          *dispatch;
    dispatch_context_t  *ctp;

    volatile bool   done;

    int             busno;
    char            name[SPI_BUS_NAME_LEN]; /* SPI bus name, such as SPI0, SPI1 */
    uint64_t        pbase;
    int             irq;
    uint64_t        input_clk;   /* SPI bus input clock */
    uint64_t        buf_max;     /* SPI transaction buffer boundary */

    sem_t           *sem;        /* SPI semaphore */
    struct sigevent evt;         /* SPI event */

    char            *bs;         /* SPI device driver board/controller specific options */
    spi_funcs_t     *funcs;      /* SPI device driver low level interface functions */
    void            *drvhdl;     /* Address of the low level SPI device driver structure */

    uint8_t         *buf;        /* SPI xfer data buffer for not DMA mode */
    uint32_t        buflen;      /* SPI xfer data buffer size for not DMA mode */

    dma_addr_t      dma_addr;           /* SPI DMA addr */
    uint32_t        dma_buflen;         /* SPI DMA buffer size */
    char            *dma_init_opts;     /* DMA init opts */
    char            *dma_attach_opts;   /* DMA attach opts */
    uint8_t         dma_thld;           /* DMA threshold */

    spi_dev_t       *devlist;    /* Chip select device list under this bus */

    spi_bus_t       *next;       /* Pointer to the next bus node */
};

/* SPI global parameters structure */
struct _spi_global_cfg {
    uint8_t       verbosity;
};

/* SPI resmgr structure */
struct _spi_resmgr_ctrl {
    resmgr_attr_t             resmgr_attr;
    resmgr_connect_funcs_t    resmgr_connect_funcs;
    resmgr_io_funcs_t         resmgr_io_funcs;
};

/* io-spi control structure */
struct _spi_ctrl {
    spi_resmgr_ctrl_t   rctrl;          /* SPI resmgr structure */
    spi_global_cfg_t    global;         /* SPI global parameters */
    spi_bus_t           *buslist;       /* SPI bus list */
};

/* utils.c: helper functions which are called by SPI device drivers */
void spi_slogf(const int verbosity, const char *fmt, ...);
int spi_destroy_devs(spi_dev_t *dev);
int spi_create_devs(spi_dev_t *dev);

#endif /* _IOSPI_H_INCLUDED */
