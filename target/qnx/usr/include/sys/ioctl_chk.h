/*
 * Copyright 2020-2021, QNX Software Systems. All Rights Reserved.
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

#ifndef __IOCTL_H_INCLUDED
#error <ioctl_chk.h> should not be included directly.
#endif

#ifndef __IOCTL_CHK_H_INCLUDED
#define __IOCTL_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

#ifdef __bvap
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_missing_arg_diag_ioctl,
        __fortify_fail_missing_arg,
        "argument 2 of 'ioctl' includes the 'IOC_OUT' and/or 'IOC_IN' flag, but fewer than 3 arguments specified");
extern int __ioctl_alias(int __fd, int __cmd, ...) __ALIASATTR("ioctl");
#endif /* #ifdef __bvap */


#if __NTO_FORTIFY_LEVEL > 0

#ifdef __bvap
extern __FORTIFY_FUNCTION int ioctl(const int __fd, const int __cmd, ...)
{
    /* When the IOC_DIRMASK field of the __cmd argument isn't IOC_VOID, an additional __data argument is required. Fail if the
     * caller didn't specify one. Also emit an error/warning if the IOC_DIRMASK field of the __cmd argument is known to be constant
     * at compile time. A client may extend the ioctl() function (via the _register_ioctl_handler function) with a custom handler
     * accepting an arbitrary number of additional arguments, so don't enforce a maximum number of arguments. */
    if ( __bvap_len < 1 ) {
        if ( __bconst((unsigned int)__cmd & IOC_DIRMASK) ) {
            if ( ((unsigned int)__cmd & IOC_DIRMASK) != IOC_VOID ) {
                __fortify_fail_missing_arg_diag_ioctl();
            }
        } else {
            if ( ((unsigned int)__cmd & IOC_DIRMASK) != IOC_VOID ) {
                __fortify_fail_missing_arg();
            }
        }
    } else {
        /* __data argument was specified. It's required when the IOC_DIRMASK field of the __cmd argument isn't IOC_VOID and ignored
         * otherwise. */
    }
    return __ioctl_alias(__fd, __cmd, __bvap);
}
#endif /* #ifdef __bvap */

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef __IOCTL_CHK_H_INCLUDED */
