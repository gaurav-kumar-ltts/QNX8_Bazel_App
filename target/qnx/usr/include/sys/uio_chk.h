/*
 * Copyright (c) 2020-2021, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software. Free development
 * licenses are available for evaluation and non-commercial purposes. For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others. Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */

#ifndef __UIO_H_INCLUDED
#error <uio_chk.h> should not be included directly.
#endif

#ifndef __UIO_CHK_H_INCLUDED
#define __UIO_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_readv,
        __fortify_fail_overflow_dst,
        "argument 3 of 'readv' is greater than the number of 'struct iovec' elements in the object referenced by argument 2");
extern ssize_t __readv_alias(int __fildes, const struct iovec *__iov, int __nparts) __ALIASATTR("readv");


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION ssize_t readv(const int __fildes, const struct iovec * const __iov, const int __nparts)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __iov,
            (unsigned int)__nparts,
            __nparts > 0,
            __fortify_fail_overflow_dst_diag_readv);
    return __readv_alias(__fildes, __iov, __nparts);
}

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef __UIO_CHK_H_INCLUDED */
