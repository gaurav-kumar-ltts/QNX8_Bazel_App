/*
 * Copyright (c) 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef _UCHAR_H_INCLUDED
#error <uchar_chk.h> should not be included directly.
#endif

#ifndef _UCHAR_CHK_H_INCLUDED
#define _UCHAR_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

size_t __c16rtomb_chk(
        char      * _Restrict __s,
        char16_t              __c16,
        mbstate_t * _Restrict __pst,
        size_t                __osize);
size_t __c16rtomb_alias(
        char      * _Restrict __s,
        char16_t              __c16,
        mbstate_t * _Restrict __pst) __ALIASATTR("c16rtomb");

size_t __c32rtomb_chk(
        char      * _Restrict __s,
        char32_t              __c32,
        mbstate_t * _Restrict __pst,
        size_t                __osize);
size_t __c32rtomb_alias(
        char      * _Restrict __s,
        char32_t              __c32,
        mbstate_t * _Restrict __pst) __ALIASATTR("c32rtomb");


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION size_t c16rtomb(
        char           * const _Restrict __s,
        char16_t const                   __c16,
        mbstate_t      * const _Restrict __pst)
{
    if ( __bos_default(__s) != __BOS_UNKNOWN ) {
        return __c16rtomb_chk(__s, __c16, __pst, __bos_default(__s));
    } else {
        return __c16rtomb_alias(__s, __c16, __pst);
    }
}

extern __FORTIFY_FUNCTION size_t c32rtomb(
        char           * const _Restrict __s,
        char32_t const                   __c32,
        mbstate_t      * const _Restrict __pst)
{
    if ( __bos_default(__s) != __BOS_UNKNOWN ) {
        return __c32rtomb_chk(__s, __c32, __pst, __bos_default(__s));
    } else {
        return __c32rtomb_alias(__s, __c32, __pst);
    }
}

#endif /* __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _UCHAR_CHK_H_INCLUDED */
