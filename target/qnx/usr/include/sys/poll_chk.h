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

#ifndef __POLL_H_INCLUDED
#error <sys/poll_chk.h> should not be included directly.
#endif

#ifndef __POLL_CHK_H_INCLUDED
#define __POLL_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

#ifndef _KERNEL
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_poll,
        __fortify_fail_overflow_dst,
        "argument 2 of 'poll' is greater than the number of 'struct pollfd' elements in the object referenced by argument 1");
extern int __poll_alias(struct pollfd *__fds, nfds_t __nfds, int __timeout) __ALIASATTR("poll");
#endif /* #ifndef _KERNEL */


#if __NTO_FORTIFY_LEVEL > 0

#ifndef _KERNEL
extern __FORTIFY_FUNCTION int poll(struct pollfd * const __fds, const nfds_t __nfds, const int __timeout)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __fds, __nfds, 1, __fortify_fail_overflow_dst_diag_poll);
    return __poll_alias(__fds, __nfds, __timeout);
}
#endif /* #ifndef _KERNEL */

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef __POLL_CHK_H_INCLUDED */
