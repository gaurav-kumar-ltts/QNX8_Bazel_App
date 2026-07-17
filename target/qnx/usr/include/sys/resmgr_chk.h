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

#ifndef __RESMGR_H_INCLUDED
#error <sys/resmgr_chk.h> should not be included directly.
#endif

#ifndef __RESMGR_CHK_H_INCLUDED
#define __RESMGR_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_resmgr_msgget,
        __fortify_fail_overflow_dst,
        "argument 3 of 'resmgr_msgget' is greater than the size of the object referenced by argument 2");
extern ssize_t __resmgr_msgget_alias(resmgr_context_t *__ctp, void *__msg, size_t __size, size_t __offset)
        __ALIASATTR("resmgr_msgget");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_resmgr_msggetv,
        __fortify_fail_overflow_dst,
        "argument 3 of 'resmgr_msggetv' is greater than the number of 'iov_t' elements in the object referenced by argument 2");
extern ssize_t __resmgr_msggetv_alias(resmgr_context_t *__ctp, iov_t *__rmsg, size_t __rparts, size_t __offset)
        __ALIASATTR("resmgr_msggetv");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_resmgr_msgread,
        __fortify_fail_overflow_dst,
        "argument 3 of 'resmgr_msgread' is greater than the size of the object referenced by argument 2");
extern ssize_t __resmgr_msgread_alias(resmgr_context_t *__ctp, void *__msg, size_t __size, size_t __offset)
        __ALIASATTR("resmgr_msgread");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_resmgr_msgreadv,
        __fortify_fail_overflow_dst,
        "argument 3 of 'resmgr_msgreadv' is greater than the number of 'struct iovec' elements in the object referenced by "
                "argument 2");
extern ssize_t __resmgr_msgreadv_alias(resmgr_context_t *__ctp, struct iovec *__rmsg, int __rparts, size_t __offset)
        __ALIASATTR("resmgr_msgreadv");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_resmgr_pathname,
        __fortify_fail_overflow_dst,
        "argument 4 of 'resmgr_pathname' is negative or greater than the size of the object referenced by argument 3");
extern int __resmgr_pathname_alias(int __id, unsigned __flags, char *__path, int __maxbuf) __ALIASATTR("resmgr_pathname");


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION ssize_t resmgr_msgget(
        resmgr_context_t * const __ctp,
        void             * const __msg,
        const size_t             __size,
        const size_t             __offset)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__msg, __size, 1, __fortify_fail_overflow_dst_diag_resmgr_msgget);
    return __resmgr_msgget_alias(__ctp, __msg, __size, __offset);
}

extern __FORTIFY_FUNCTION ssize_t resmgr_msggetv(
        resmgr_context_t * const __ctp,
        iov_t            * const __rmsg,
        const size_t             __rparts,
        const size_t             __offset)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __rmsg, __rparts, 1, __fortify_fail_overflow_dst_diag_resmgr_msggetv);
    return __resmgr_msggetv_alias(__ctp, __rmsg, __rparts, __offset);
}

extern __FORTIFY_FUNCTION ssize_t resmgr_msgread(
        resmgr_context_t * const __ctp,
        void             * const __msg,
        const size_t             __size,
        const size_t             __offset)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__msg, __size, 1, __fortify_fail_overflow_dst_diag_resmgr_msgread);
    return __resmgr_msgread_alias(__ctp, __msg, __size, __offset);
}

extern __FORTIFY_FUNCTION ssize_t resmgr_msgreadv(
        resmgr_context_t * const __ctp,
        struct iovec     * const __rmsg,
        const int                __rparts,
        const size_t             __offset)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __rmsg,
            (unsigned int)__rparts,
            1,
            __fortify_fail_overflow_dst_diag_resmgr_msgreadv);
    return __resmgr_msgreadv_alias(__ctp, __rmsg, __rparts, __offset);
}

extern __FORTIFY_FUNCTION int resmgr_pathname(const int __id, const unsigned __flags, char * const __path, const int __maxbuf)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __path,
            (unsigned int)__maxbuf,
            1,
            __fortify_fail_overflow_dst_diag_resmgr_pathname);
    return __resmgr_pathname_alias(__id, __flags, __path, __maxbuf);
}

#endif /* __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef __RESMGR_CHK_H_INCLUDED */
