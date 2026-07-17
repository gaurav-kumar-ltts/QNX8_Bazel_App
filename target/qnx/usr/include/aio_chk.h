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

#ifndef _AIO_H_INCLUDED
#error <aio_chk.h> should not be included directly.
#endif

#ifndef _AIO_CHK_H_INCLUDED
#define _AIO_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_lio_listio,
        __fortify_fail_overflow_dst,
        "argument 3 of 'lio_listio' is greater than the number of 'struct aiocb *' elements in the object referenced by "
                "argument 2");
extern int __lio_listio_alias(
        int                                  __mode,
        struct aiocb    * __restrict __const __list[],
        int                                  __nent,
        struct sigevent * __restrict         __sig) __ALIAS64ELSE("lio_listio64", "lio_listio");

#if defined(__EXT_LF64SRC)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_lio_listio64,
        __fortify_fail_overflow_dst,
        "argument 3 of 'lio_listio64' is greater than the number of 'struct aiocb64 *' elements in the object referenced by "
                "argument 2");
extern int __lio_listio64_alias(
        int                                  __mode,
        struct aiocb64  * __restrict __const __list[],
        int                                  __nent,
        struct sigevent * __restrict         __sig) __ALIASOFFELSE("lio_listio", "lio_listio64");
#endif /* #if defined(__EXT_LF64SRC) */


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION int lio_listio(
        __const int                          __mode,
        struct aiocb    * __restrict __const __list[],
        __const int                          __nent,
        struct sigevent * __restrict __const __sig)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (struct aiocb * __const *)__list,
            (unsigned int)__nent,
            __nent > 0,
            __fortify_fail_overflow_dst_diag_lio_listio);
    return __lio_listio_alias(__mode, __list, __nent, __sig);
}

#if defined(__EXT_LF64SRC)
extern __FORTIFY_FUNCTION int lio_listio64(
        __const int                          __mode,
        struct aiocb64  * __restrict __const __list[],
        __const int                          __nent,
        struct sigevent * __restrict __const __sig)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (struct aiocb64  * __const *)__list,
            (unsigned int)__nent,
            __nent > 0,
            __fortify_fail_overflow_dst_diag_lio_listio64);
    return __lio_listio64_alias(__mode, __list, __nent, __sig);
}
#endif /* #if defined(__EXT_LF64SRC) */

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _AIO_CHK_H_INCLUDED */
