/*
 * Copyright (c) 2022, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef _XHCI_SOC_H
#define _XHCI_SOC_H

#include <sys/io-usb-otg.h>

#define XHCI_SOC_API_VERSION    0x0002

typedef struct xhci_soc_api_s {
    _uint32 version;
} xhci_soc_api_t;

typedef struct xhci_soc_entry_s {
    xhci_soc_api_t api;
    /*
     * This function is called while the USB host controller driver is parsing
     * command line arguments once the soc dll has been selected and is used to
     * allocate a context for the soc to store board specific details.
     *
     * @param   hcd             Handle to the USB host controller driver
     * @param   hcd_verbosity   The verbosity level USB host controller driver
     * @param   err_status      Used to collect error status on failure
     *
     * @return  A pointer to the soc context on success
     * @return  NULL on failure
     */
    void *(*alloc) (usb_hcd_t *hcd, int hcd_verbosity, int *err_status);

    /*
     * This function is called when shutting down the controller or when a
     * failure occurred while initializing the controller. It is used to
     * release the memory used for the soc context from alloc().
     *
     * @param   soc             Pointer to the soc context
     *
     * @return  None
     */
    void (*free) (void *soc);

    /*
     * This function is called when initializing the controller. It is used to
     * begin initializing the soc context (see alloc()) before mapping in the
     * xHCI core after processing the command line arguments.
     *
     * @param   soc             Pointer to the soc context
     * @param   hcd_flags       Host controller driver flags,
     *                          see XHCI_FLAGS_* from xhci.h
     *
     * @return	None
     */
    int (*init) (void *soc, uint32_t *hcd_flags);

    /*
     * This function is called after the controller is initialized. It is used to
     * finalize initializations for the soc context.
     *
     * @param   soc             Pointer to the soc context
     *
     * @return	EOK on success
     * @return  non-zero on failure
     */
    int (*init_end) (void *soc);

    /*
     * This function is called before the controller is started. It is used to
     * perform board-specific initializations before the controller is reset.
     * Note the controller should typically be in a STOPPED state, but
     * it might be in a RUNNING state.
     *
     * @param   soc             Pointer to the soc context
     * @param   hcd_flags       Host controller driver flags,
     *                          see XHCI_FLAGS_* from xhci.h
     *
     * @return	EOK on success
     * @return  non-zero on failure
     */
    int (*init1) (void *soc, uint32_t *hcd_flags);

    /*
     * This function is called before the controller is started. It is used to
     * perform board-specific initializations after the controller is reset.
     * Note the controller should be in STOPPED state.
     *
     * @param   soc             Pointer to the soc context
     *
     * @return	EOK on success
     * @return  non-zero on failure
     */
    int (*init2) (void *soc);

    /*
     * This function is called when the controller is shutting down or if
     * the controller initialization failed. It is used to clean up the soc
     * context before releasing its resources.
     *
     * @param   soc             Pointer to the soc context
     *
     * @return	EOK on success
     * @return  non-zero on failure
     */
    int (*fini) (void *soc);

    /*
     * This function is called when the controller is stopping and if the
     * controller failed to start. It is used to bring down the soc context,
     * see (init1()).
     *
     * @param   soc             Pointer to the soc context
     *
     * @return	EOK on success
     * @return  non-zero on failure
     */
    int (*fini1) (void *soc);

    /*
     * This function is called when the controller is stopping and if the
     * controller failed to start. It is used to bring down the soc context,
     * see (init2()).

     *
     * @param   soc             Pointer to the soc context
     *
     * @return	EOK on success
     * @return  non-zero on failure
     */
    int (*fini2) (void *soc);

    /*
     * This function is called after the controller is stopped to finish
     * bringing down the soc context.
     *
     * @param   soc             Pointer to the soc context
     *
     * @return	EOK on success
     * @return  non-zero on failure
     */
    int (*stop_end) (void *soc);

    /*
     * This function is called while the USB host controller driver is parsing
     * command line arguments and is used to collect soc/board specific
     * settings.
     *
     * @param   soc             Pointer to the soc context
     * @param   arg             String containing command line arguments
     *
     * @return	None
     */
    int (*process_args) (void *soc, char *arg);
} xhci_soc_entry_t;

#endif    // _XHCI_SOC_H

#if defined(QNXNTO) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/hardware/trunk/hardware/devu/controller/hc/public/hw/xhci_soc.h $ $Rev: 977664 $")
#endif
