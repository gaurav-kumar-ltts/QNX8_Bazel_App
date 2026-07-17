/*
 * $QNXLicenseC:
 * Copyright 2017, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */
#ifndef __WIPE_H__
#define __WIPE_H__

#include <stdint.h>
#include <limits.h>

/*  If the target is a filesystem, attempt to unmount the filesystem prior to
    wiping. The default behavior is to return an error if the target filesystem
    is mounted.
*/
#define WIPE_FLAG_UNMOUNT           (0x00000001u)

/*  Allow the wipe operation to be performed insecurely. This option will enable
    using an insecure version of the requested method. If a method is not
    capable of performing the operation securely, this flag must be set in order
    to use it. The default behavior is to always perform the requested operation
    securely.
*/
#define WIPE_FLAG_INSECURE          (0x00000002u)

/*  Perform the wipe asynchronously. The default behavior is to perform the wipe
    synchronously on the programs main thread.
*/
#define WIPE_FLAG_ASYNC             (0x00000004u)

/*  If the wipe method is WIPE_METHOD_WRITE, attempt to use direct i/o. This
    flag is ignored for all other wipe methods.
*/
#define WIPE_FLAG_DIRECTIO          (0x00000008u)

/*  Enable test mode, which will run through the entire wipe process but not
    actually issue of any of the commands that will destroy (wipe) the data.
*/
#define WIPE_FLAG_TESTMODE          (0x00000010u)

/*  If the wipe scope is WIPE_SCOPE_FS, wipe free space instead of the
    filesystem data contents.
*/
#define WIPE_FLAG_FREESPACE         (0x00000020u)

/*  Bypass io-blk cache coherency operations. By default, io-blk cache coherency
    is enforced by invalidating any cache buffers associated with the wipe
    target range. The use of this option omits the cache coherency operation and
    will generally allow any cached data to be accessed following the wipe.
    Extreme caution should be used when specifying this flag, as it can lead to
    both insecure and sometimes dangerous side effects.
*/
#define WIPE_FLAG_CACHE_INCOHERENT  (0x00000040u)

/*  Enumerate the number of device units (usually sectors) that will be wiped.
    This will execute a first pass through the configured iterator and count all
    of the units to be wiped. Note that depending on configuration of the wipe
    actors for aligned and unaligned portions, the total number of device units
    may exceed either of the total number of units on the target or the total
    number of units to wipe. This is due to the fact that some wipe actors break
    the operation into two parts, marking the units and committing the marked
    units.
*/
#define WIPE_FLAG_ENUMERATE         (0x00000080u)


/*  The mask of valid flags.
*/
#define WIPE_FLAG_MASK              (0xFF0000FFu)

/*  Describes the scope of data that is to be wiped.

    Example disk layout:
    --------------------------------------------------------------------------
    |          |       f,p,d       | p,d |        p,d         |       d      |
    --------------------------------------------------------------------------
    |<- boot ->|
               |<---- "/base" ---->|
               |<------  /dev/hd0 ------>|
                                         |<---- /dev/hd1 ---->|
                                                              |<-- unused -->|
    |<------------------------------- /dev/emmc ---------------------------->|
*/
typedef enum wipe_scope {
    /*  Specifies only the filesystem and data regions owned by the filesystem.
        Regions marked with 'f' above are affected/selectable.
    */
    WIPE_SCOPE_FS,

    /*  Specifies a partition which may contain a number of filesysems.
        Regions marked with 'p' above are affected/selectable.
    */
    WIPE_SCOPE_PARTITION,

    /*  Specifies an entire device which may contain a number of partitions.
        Regions marked with 'd' above are affected.
    */
    WIPE_SCOPE_DEVICE,

    /*  Specifies a single file.
    */
    WIPE_SCOPE_FILE,

    /*  The number of wipe scopes.
    */
    WIPE_SCOPE_N
} wipe_scope_t;

/*  Describes the available methods to wipe the data.
*/
typedef enum wipe_method {
    /*  Wipe by writing all data with zeroes.
    */
    WIPE_METHOD_WRITE,

    /*  Wipe by using the hardware's 'erase' functionality. The contents of the
        data blocks will be set to the device's erase value (usually 0 or 1).
        Units of erasure are generally an in 'erase block groups' defined by the
        hardware.
    */
    WIPE_METHOD_ERASE,

    /*  Wipe by using the hardware's 'trim' functionality. This is generally
        identical in behavior to the 'erase' functionality except that erasure
        units are in 'write block groups', which are generally smaller than
        erase block groups.
    */
    WIPE_METHOD_TRIM,

    /*  Wipe by using the hardware's 'discard' functionality. This marks blocks
        as being no longer used and the device may or may not wipe the contents
        of discarded blocks in the background. The hardware provides no
        guarantee that existing data within a block will be erased and so this
        method is insecure.
    */
    WIPE_METHOD_DISCARD,

    /*  Do nothing. This is intended to be used by informational actions.
    */
    WIPE_METHOD_NOOP,

    /*  The number of wipe methods.
    */
    WIPE_METHOD_N
} wipe_method_t;

typedef struct wipe_request wipe_request_t;


/*  Returns the verbosity associated with a wipe request. See wipe.c for a
    complete description of how this function operates.

    Parameters
        request - A pointer to the request to process
    Returns:
        The current verbosity level.
*/
uint8_t wipe_request_verbosity(
    const wipe_request_t * const request);

/*  Sets the verbosity associated with a wipe request.

    Parameters
        request - A pointer to the request to process
        verbose_level - The new verbosity level to set.
                        A level of -1 means no change.
    Returns:
        The current verbosity level, or -errno if an error occurs.
        A return of 0 means a verbosity level of 0.
*/
int wipe_request_set_verbosity(
    wipe_request_t * const request,
    int verbose_level);


/*  Sets the scope of a wipe request

    Parameters
        request - A pointer to the request to set 
        scope -   The scope of the wipe.
    Returns:
        EOK on success or -errno if an error occurs.
*/
int wipe_request_scope(
    wipe_request_t * const request,
    const wipe_scope_t scope);


/*  Sets the method for a wipe request

    Parameters
        request - A pointer to the request to set 
        method - The wipe method to use.
    Returns:
        EOK on success or -errno if an error occurs.
*/
int wipe_request_method(
    wipe_request_t * const request,
    const wipe_method_t method);


/*  Sets the flags for the specified request.

    Parameters
        request - A pointer to the wipe request structure.
        flags   - Desired flags for the request.  Any clear bits
                  in flags will also be cleared in the request.

    Returns
        EOK on success, -errno on error
*/
int wipe_request_set_flags(
    wipe_request_t* const request,
    const unsigned flags);


/*  Performs the wipe request.
    
    Parameters
        request - The configured request to process
    Returns
        EOK on success, or -errno on failure.
*/
int wipe(
    wipe_request_t * const request);


/*  Initializes a wipe request with default values.

    Parameters
        request - A pointer to the request to initialize.
    Returns
        POSIX errno on failure, EOK on success
*/
int wipe_request_init(
    wipe_request_t *const request);


/*  Allocates a wipe request.

    Parameters
        request - A pointer to set to the allocated request.
    Returns
        POSIX errno on failure, EOK on success
*/
int wipe_request_alloc(
    wipe_request_t **request);

/*  Releases a wipe request.

    Parameters
        request - A pointer to the request to cleanup.
*/
int wipe_request_fini(
    wipe_request_t * request);

/*  Displays information about a wipe request.

    Parameters
        request - A pointer to the request structure to display information for.
*/
void wipe_request_display(
    const wipe_request_t * const request);

/*  Sets the path for the specified request.

    Parameters
        request - A pointer to the wipe request structure.
        path    - A NUL terminated path to be wiped

    Returns
        EOK on success, -errno on error
*/
int wipe_request_set_path(
        wipe_request_t* const request,
        const char* const path);

/*  Sets the erase unit size limit for the specified request.

    Parameters
        request - A pointer to the wipe request structure.
        limit   - A NUL terminated path to be wiped

    Returns
        EOK on success, -errno on error
*/
int wipe_request_set_erase_unit_limit(
    wipe_request_t* const request,
    const uint64_t limit);
#endif /* __WIPE_H__ */
