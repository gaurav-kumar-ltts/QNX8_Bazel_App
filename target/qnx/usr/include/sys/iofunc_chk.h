/*
 * Copyright (c) 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef __IOFUNC_H_INCLUDED
#error <sys/iofunc_chk.h> should not be included directly.
#endif

#ifndef __IOFUNC_CHK_H_INCLUDED
#define __IOFUNC_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_iofunc_client_info_able,
        __fortify_fail_overflow_dst,
        "argument 6 of 'iofunc_client_info_able' is greater than the number of "
                "'struct _client_able' elements in the object referenced by "
                "argument 5");
extern int __iofunc_client_info_able_alias(
        resmgr_context_t const  *__ctp,
        int                      __ioflag,
        struct _client_info    **__info_pp,
        int                      __flags,
        struct _client_able     *__abilities,
        int                      __nable)
        __ALIASATTR("iofunc_client_info_able");


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION int iofunc_client_info_able(
        resmgr_context_t const  * const __ctp,
        int const                       __ioflag,
        struct _client_info    ** const __info_pp,
        int const                       __flags,
        struct _client_able     * const __abilities,
        int const                       __nable)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __abilities,
            (unsigned int)__nable,
            __nable > 0,
            __fortify_fail_overflow_dst_diag_iofunc_client_info_able);
    return __iofunc_client_info_able_alias(
            __ctp,
            __ioflag,
            __info_pp,
            __flags,
            __abilities,
            __nable);
}

#endif /* __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef __IOFUNC_CHK_H_INCLUDED */
