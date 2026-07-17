/*
 * Copyright (c) 2020-2023, QNX Software Systems. All Rights Reserved.
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

#ifndef __SELECT_H_INCLUDED
#error <sys/select_chk.h> should not be included directly.
#endif

#ifndef __SELECT_CHK_H_INCLUDED
#define __SELECT_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_FD_CLR,
        __fortify_fail_overflow_dst,
        "argument 1 of 'FD_CLR' is less than zero or greater than the number of bits in the object referenced by argument 2");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_FD_SET,
        __fortify_fail_overflow_dst,
        "argument 1 of 'FD_SET' is less than zero or greater than the number of bits in the object referenced by argument 2");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_pselect,
        __fortify_fail_overflow_dst,
        "argument 1 of 'pselect' is greater than the number of bits in one or more of the objects referenced by arguments 2, 3 "
                "and 4");
extern int __pselect_alias(
        int                                __nfds,
        fd_set                * __restrict __readfds,
        fd_set                * __restrict __writefds,
        fd_set                * __restrict __exceptfds,
        const struct timespec * __restrict __timeout,
        const sigset_t        * __restrict __sigmask) __ALIASATTR("pselect");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_select,
        __fortify_fail_overflow_dst,
        "argument 1 of 'select' is greater than the number of bits in one or more of the objects referenced by arguments 2, 3 "
                "and 4");
extern int __select_alias(
        int                         __nfds,
        fd_set         * __restrict __readfds,
        fd_set         * __restrict __writefds,
        fd_set         * __restrict __exceptfds,
        struct timeval * __restrict __timeout) __ALIASATTR("select");


#if __NTO_FORTIFY_LEVEL > 0

#undef FD_CLR
#define FD_CLR(fd, p)  __fd_clr_chk((fd), (p))

static __FORTIFY_FUNCTION void __fd_clr_chk(const int __fd, fd_set * const __fds)
{
    /* Fail if __fd would result in a negative array index */
    __FORTIFY_CHK(__fd, __fd < 0, __fortify_fail_overflow_dst_diag_FD_CLR, __fortify_fail_overflow_dst);
    /* Fail if __fd specifies a bit beyond the end of __fds. No need to check this if the number of bits in __fds is too large to be
     * represented by a _Sizet. */
    if ( ( __bos_default(__fds) != __BOS_UNKNOWN ) && ( __bos_default(__fds) <= ((_Sizet)-1 / 8) ) ) {
        __FORTIFY_CHK(
                __fd,
                (unsigned int)__fd >= (__bos_default(__fds) /
                        sizeof(__fds->fds_bits[0]) * (_Sizet)__NFDBITS),
                __fortify_fail_overflow_dst_diag_FD_CLR,
                __fortify_fail_overflow_dst);
    }
    __fd_clr(__fd, __fds);
}

#undef FD_SET
#define FD_SET(fd, p)  __fd_set_chk((fd), (p))

static __FORTIFY_FUNCTION void __fd_set_chk(const int __fd, fd_set * const __fds)
{
    /* Fail if __fd would result in a negative array index */
    __FORTIFY_CHK(__fd, __fd < 0, __fortify_fail_overflow_dst_diag_FD_SET, __fortify_fail_overflow_dst);
    /* Fail if __fd specifies a bit beyond the end of __fds. No need to check this if the number of bits in __fds is too large to be
     * represented by a _Sizet. */
    if ( ( __bos_default(__fds) != __BOS_UNKNOWN ) && ( __bos_default(__fds) <= ((_Sizet)-1 / 8) ) ) {
        __FORTIFY_CHK(
                __fd,
                (unsigned int)__fd >= (__bos_default(__fds) /
                        sizeof(__fds->fds_bits[0]) * (_Sizet)__NFDBITS),
                __fortify_fail_overflow_dst_diag_FD_SET,
                __fortify_fail_overflow_dst);
    }
    __fd_set(__fd, __fds);
}

extern __FORTIFY_FUNCTION int pselect(
        const int                                __nfds,
        fd_set                * const __restrict __readfds,
        fd_set                * const __restrict __writefds,
        fd_set                * const __restrict __exceptfds,
        const struct timespec * const __restrict __timeout,
        const sigset_t        * const __restrict __sigmask)
{
    /* Fail if __nfds specifies a greater number of bits than the bit size of __readfds, __writefds or __exceptfds. In each case,
     * the check is unnecessary if the number of bits in the relevant object is too large to be represented by a _Sizet. Negative
     * __nfds values are already handled by the standard implementation of pselect. */
    if ( ( __bos_default(__readfds) != __BOS_UNKNOWN ) && ( __bos_default(__readfds) <= ((_Sizet)-1 / 8) ) ) {
        __FORTIFY_CHK(
                __nfds,
                ( __nfds > 0 ) && ( (unsigned int)__nfds >
                        (__bos_default(__readfds) /
                                sizeof(__readfds->fds_bits[0]) *
                                (_Sizet)__NFDBITS) ),
                __fortify_fail_overflow_dst_diag_pselect,
                __fortify_fail_overflow_dst);
    }
    if ( ( __bos_default(__writefds) != __BOS_UNKNOWN ) && ( __bos_default(__writefds) <= ((_Sizet)-1 / 8) ) ) {
        __FORTIFY_CHK(
                __nfds,
                ( __nfds > 0 ) && ( (unsigned int)__nfds >
                        (__bos_default(__writefds) /
                                sizeof(__writefds->fds_bits[0]) *
                                (_Sizet)__NFDBITS) ),
                __fortify_fail_overflow_dst_diag_pselect,
                __fortify_fail_overflow_dst);
    }
    if ( ( __bos_default(__exceptfds) != __BOS_UNKNOWN ) && ( __bos_default(__exceptfds) <= ((_Sizet)-1 / 8) ) ) {
        __FORTIFY_CHK(
                __nfds,
                ( __nfds > 0 ) && ( (unsigned int)__nfds >
                        (__bos_default(__exceptfds) /
                                sizeof(__exceptfds->fds_bits[0]) *
                                (_Sizet)__NFDBITS) ),
                __fortify_fail_overflow_dst_diag_pselect,
                __fortify_fail_overflow_dst);
    }
    return __pselect_alias(__nfds, __readfds, __writefds, __exceptfds, __timeout, __sigmask);
}

extern __FORTIFY_FUNCTION int select(
        const int                         __nfds,
        fd_set         * const __restrict __readfds,
        fd_set         * const __restrict __writefds,
        fd_set         * const __restrict __exceptfds,
        struct timeval * const __restrict __timeout)
{
    /* Fail if __nfds specifies a greater number of bits than the bit size of __readfds, __writefds or __exceptfds. In each case,
     * the check is unnecessary if the number of bits in the relevant object is too large to be represented by a _Sizet. Negative
     * __nfds values are already handled by the standard implementation of select. */
    if ( ( __bos_default(__readfds) != __BOS_UNKNOWN ) && ( __bos_default(__readfds) <= ((_Sizet)-1 / 8) ) ) {
        __FORTIFY_CHK(
                __nfds,
                ( __nfds > 0 ) && ( (unsigned int)__nfds >
                        (__bos_default(__readfds) /
                                sizeof(__readfds->fds_bits[0]) *
                                (_Sizet)__NFDBITS) ),
                __fortify_fail_overflow_dst_diag_select,
                __fortify_fail_overflow_dst);
    }
    if ( ( __bos_default(__writefds) != __BOS_UNKNOWN ) && ( __bos_default(__writefds) <= ((_Sizet)-1 / 8) ) ) {
        __FORTIFY_CHK(
                __nfds,
                ( __nfds > 0 ) && ( (unsigned int)__nfds >
                        (__bos_default(__writefds) /
                                sizeof(__writefds->fds_bits[0]) *
                                (_Sizet)__NFDBITS) ),
                __fortify_fail_overflow_dst_diag_select,
                __fortify_fail_overflow_dst);
    }
    if ( ( __bos_default(__exceptfds) != __BOS_UNKNOWN ) && ( __bos_default(__exceptfds) <= ((_Sizet)-1 / 8) ) ) {
        __FORTIFY_CHK(
                __nfds,
                ( __nfds > 0 ) && ( (unsigned int)__nfds >
                        (__bos_default(__exceptfds) /
                                sizeof(__exceptfds->fds_bits[0]) *
                                (_Sizet)__NFDBITS) ),
                __fortify_fail_overflow_dst_diag_select,
                __fortify_fail_overflow_dst);
    }
    return __select_alias(__nfds, __readfds, __writefds, __exceptfds, __timeout);
}

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef __SELECT_CHK_H_INCLUDED */
