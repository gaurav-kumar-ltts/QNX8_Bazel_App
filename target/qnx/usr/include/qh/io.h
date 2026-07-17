/*
 * $QNXLicenseC:
 * Copyright 2019-2021, QNX Software Systems.  All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.  Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef QNX_QH_IO_H_INCLUDED
#define QNX_QH_IO_H_INCLUDED

/**
 * @file io.h
 *
 * QNX helpers - IO helpers.
 */

/* sorted headers from this project */
#ifndef QNX_QH_QH_H_INCLUDED
#include "qh/qh.h"
#endif

/* sorted library headers */

/* sorted system headers */

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * @brief Close a file and retry on @c EINTR.
 *
 * @details When @e close() is called and it returns an error with @e errno set to @c EINTR, the
 * caller is responsible for calling it again; otherwise, the file descriptor does not get closed,
 * which creates a file descriptor leak. This function handles this task for the caller and also
 * handles cases where the file descriptor is -1, which would otherwise require the caller to wrap
 * the @e close() call.
 *
 * This function never returns @c EINTR.
 *
 * @param[in] __fd The file descriptor of the file to close (just like the one that would otherwise
 *                  be passed to the @e close() function), or -1 (in which case the function does
                    not call @e close() and returns successfully).
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is set).
 */
static inline int
qh_close(const int __fd)
{
    int __retval;

    if (__fd == -1) {
        return EOK;
    }

    do {
        __retval = close(__fd);
    } while ((__retval == -1) && (errno == EINTR));

    if (__retval != -1) {
        return EOK;
    }

    return errno;
}

/** @cond */
__END_DECLS
/** @endcond */

#endif /* QNX_QH_IO_H_INCLUDED */
