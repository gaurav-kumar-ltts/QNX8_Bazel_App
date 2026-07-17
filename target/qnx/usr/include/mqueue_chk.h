/*
 * Copyright 2019-2023, QNX Software Systems. All Rights Reserved.
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
 */

#ifndef _MQUEUE_H_INCLUDED
#error <mqueue_chk.h> should not be included directly.
#endif

#ifndef _MQUEUE_CHK_H_INCLUDED
#define _MQUEUE_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

#ifdef __bvap
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_extra_arg_diag_mq_open,
        __fortify_fail_extra_arg,
        "more than 4 arguments specified to 'mq_open'");
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_missing_arg_diag_mq_open,
        __fortify_fail_missing_arg,
        "argument 2 of 'mq_open' includes the 'O_CREAT' flag, but fewer than 4 arguments specified");
extern mqd_t __mq_open_alias(const char *__name, int __oflag, ...) __ALIASATTR("mq_open");
#endif /* #ifdef __bvap */

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_mq_receive,
        __fortify_fail_overflow_dst,
        "argument 3 of 'mq_receive' is greater than the size of the object referenced by argument 2");
extern ssize_t __mq_receive_alias(mqd_t __mqdes, char *__msg_ptr, size_t __msg_len, unsigned *__msg_prio) __ALIASATTR("mq_receive");

#if defined(__EXT_POSIX1_200112)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_mq_timedreceive,
        __fortify_fail_overflow_dst,
        "argument 3 of 'mq_timedreceive' is greater than the size of the object referenced by argument 2");
extern ssize_t __mq_timedreceive_alias(
        mqd_t                  __mqdes,
        char                  *__msg_ptr,
        size_t                 __msg_len,
        unsigned              *__msg_prio,
        const struct timespec *__abs_timeout) __ALIASATTR("mq_timedreceive");
#endif /* #if defined(__EXT_POSIX1_200112) */

#ifdef __EXT_QNX
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_mq_clockreceive,
        __fortify_fail_overflow_dst,
        "argument 3 of 'mq_clockreceive' is greater than the size of the "
                "object referenced by argument 2");
ssize_t __mq_clockreceive_alias(
        mqd_t                  __mqdes,
        char                  *__msg_ptr,
        size_t                 __msg_len,
        unsigned              *__msg_prio,
        clockid_t              __clk,
        struct timespec const *__abs_timeout) __ALIASATTR("mq_clockreceive");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_mq_timedreceive_monotonic,
        __fortify_fail_overflow_dst,
        "argument 3 of 'mq_timedreceive_monotonic' is greater than the size of the object referenced by argument 2");
extern ssize_t __mq_timedreceive_monotonic_alias(
        mqd_t                  __mqdes,
        char                  *__msg_ptr,
        size_t                 __msg_len,
        unsigned              *__msg_prio,
        const struct timespec *__abs_mono_timeout) __ALIASATTR("mq_timedreceive_monotonic");
#endif /* #ifdef __EXT_QNX */


#if __NTO_FORTIFY_LEVEL > 0

#ifdef __bvap
extern __FORTIFY_FUNCTION mqd_t mq_open(const char *__name, int __oflag, ...)
{
    /* Fail if the caller specified more than the maximum number of arguments recognized by the mq_open function, as the caller may
     * have specified the __mode and/or __mq_attr argument in the wrong place */
    if ( __bvap_len > 2 ) {
        __fortify_fail_extra_arg_diag_mq_open();
    /* When the __oflag argument includes O_CREAT, additional __mode and __mq_attr arguments are required. Fail if the caller didn't
     * specify them. Also emit an error/warning if the __oflag argument is known to be constant at compile time. */
    } else if ( __bvap_len < 2 ) {
        __FORTIFY_CHK(
                __oflag & O_CREAT,
                (__oflag & O_CREAT) != 0,
                __fortify_fail_missing_arg_diag_mq_open,
                __fortify_fail_missing_arg);
    } else {
        /* __mode and __mq_attr arguments were specified. They're required when the __oflag argument includes O_CREAT and ignored
         * otherwise. */
    }
    return __mq_open_alias(__name, __oflag, __bvap);
}
#endif /* #ifdef __bvap */

extern __FORTIFY_FUNCTION ssize_t mq_receive(mqd_t __mqdes, char *__msg_ptr, size_t __msg_len, unsigned *__msg_prio)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, __msg_ptr, __msg_len, 1, __fortify_fail_overflow_dst_diag_mq_receive);
    return __mq_receive_alias(__mqdes, __msg_ptr, __msg_len, __msg_prio);
}

#if defined(__EXT_POSIX1_200112)
extern __FORTIFY_FUNCTION ssize_t mq_timedreceive(
        mqd_t                  __mqdes,
        char                  *__msg_ptr,
        size_t                 __msg_len,
        unsigned              *__msg_prio,
        const struct timespec *__abs_timeout)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, __msg_ptr, __msg_len, 1, __fortify_fail_overflow_dst_diag_mq_timedreceive);
    return __mq_timedreceive_alias(__mqdes, __msg_ptr, __msg_len, __msg_prio, __abs_timeout);
}
#endif /* #if defined(__EXT_POSIX1_200112) */

#ifdef __EXT_QNX
extern __FORTIFY_FUNCTION ssize_t mq_clockreceive(
        mqd_t                  __mqdes,
        char                  *__msg_ptr,
        size_t                 __msg_len,
        unsigned              *__msg_prio,
        clockid_t              __clk,
        struct timespec const *__abs_timeout)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            __msg_ptr,
            __msg_len,
            1,
            __fortify_fail_overflow_dst_diag_mq_clockreceive);
    return __mq_clockreceive_alias(
            __mqdes,
            __msg_ptr,
            __msg_len,
            __msg_prio,
            __clk,
            __abs_timeout);
}

extern __FORTIFY_FUNCTION ssize_t mq_timedreceive_monotonic(
        mqd_t __mqdes,
        char *__msg_ptr,
        size_t __msg_len,
        unsigned *__msg_prio,
        const struct timespec *__abs_mono_timeout)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            __msg_ptr,
            __msg_len,
            1,
            __fortify_fail_overflow_dst_diag_mq_timedreceive_monotonic);
    return __mq_timedreceive_monotonic_alias(__mqdes, __msg_ptr, __msg_len, __msg_prio, __abs_mono_timeout);
}
#endif /* #ifdef __EXT_QNX */

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _MQUEUE_CHK_H_INCLUDED */
