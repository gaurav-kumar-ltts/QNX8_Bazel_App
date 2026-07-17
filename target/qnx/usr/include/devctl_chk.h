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

#ifndef _DEVCTL_H_INCLUDED
#error <devctl_chk.h> should not be included directly.
#endif

#ifndef _DEVCTL_CHK_H_INCLUDED
#define _DEVCTL_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_devctl,
        __fortify_fail_overflow_dst,
        "argument 4 of 'devctl' is greater than the size of the object referenced by argument 3");
extern int __devctl_alias(int __fd, int __dcmd, void *__dev_data_ptr, size_t __nbytes, int *__dev_info_ptr) __ALIASATTR("devctl");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_devctlv,
        __fortify_fail_overflow_dst,
        "argument 4 of 'devctlv' is greater than the number of 'struct iovec' elements in the object referenced by argument 6");
extern int __devctlv_alias(
        int                 __fd,
        int                 __dcmd,
        int                 __sparts,
        int                 __rparts,
        const struct iovec *__sv,
        const struct iovec *__rv,
        int                *__dev_info_ptr) __ALIASATTR("devctlv");

#if defined(__EXT_QNX)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag__devctl,
        __fortify_fail_overflow_dst,
        "argument 4 of '_devctl' is greater than the size of the object referenced by argument 3");
extern int ___devctl_alias(int __fd, int __dcmd, void *__data_ptr, size_t __nbytes, unsigned __flags) __ALIASATTR("_devctl");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_posix_devctl,
        __fortify_fail_overflow_dst,
        "argument 4 of 'posix_devctl' is greater than the size of the object referenced by argument 3");
extern int __posix_devctl_alias(int __fd, int __dcmd, void *__dev_data_ptr, size_t __nbytes, int *__dev_info_ptr)
        __ALIASATTR("devctl");
#endif /* #if defined(__EXT_QNX) */


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION int devctl(
        const int            __fd,
        const int            __dcmd,
        void         * const __dev_data_ptr,
        const size_t         __nbytes,
        int          * const __dev_info_ptr)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__dev_data_ptr, __nbytes, 1, __fortify_fail_overflow_dst_diag_devctl);
    return __devctl_alias(__fd, __dcmd, __dev_data_ptr, __nbytes, __dev_info_ptr);
}

extern __FORTIFY_FUNCTION int devctlv(
        const int                  __fd,
        const int                  __dcmd,
        const int                  __sparts,
        const int                  __rparts,
        const struct iovec * const __sv,
        const struct iovec * const __rv,
        int                * const __dev_info_ptr)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __rv[0], so declare a complete struct iovec local to this block. A cast is needed to convert
     * __rv from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__rv,
            (unsigned int)__rparts,
            __rparts > 0,
            __fortify_fail_overflow_dst_diag_devctlv);
    return __devctlv_alias(__fd, __dcmd, __sparts, __rparts, __sv, __rv, __dev_info_ptr);
}

#if defined(__EXT_QNX)
extern __FORTIFY_FUNCTION int _devctl(
        const int              __fd,
        const int              __dcmd,
        void           * const __data_ptr,
        const size_t           __nbytes,
        const unsigned         __flags)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__data_ptr, __nbytes, 1, __fortify_fail_overflow_dst_diag__devctl);
    return ___devctl_alias(__fd, __dcmd, __data_ptr, __nbytes, __flags);
}

extern __FORTIFY_FUNCTION int posix_devctl(
        const int            __fd,
        const int            __dcmd,
        void         * const __dev_data_ptr,
        const size_t         __nbytes,
        int          * const __dev_info_ptr)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            (_Uint8t *)__dev_data_ptr,
            __nbytes,
            1,
            __fortify_fail_overflow_dst_diag_posix_devctl);
    return __posix_devctl_alias(__fd, __dcmd, __dev_data_ptr, __nbytes, __dev_info_ptr);
}
#endif /* #if defined(__EXT_QNX) */

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _DEVCTL_CHK_H_INCLUDED */
