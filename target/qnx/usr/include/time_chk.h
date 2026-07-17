/*
 * Copyright (c) 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef _TIME_H_INCLUDED
#error <time_chk.h> should not be included directly.
#endif

#ifndef _TIME_CHK_H_INCLUDED
#define _TIME_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_strftime,
        __fortify_fail_overflow_dst,
        "argument 2 of 'strftime' is greater than the size of the object "
                "referenced by argument 1");
extern size_t __strftime_alias(
        char            *__s,
        size_t           __maxsiz,
        char const      *__fmt,
        struct tm const *__tp) __ALIASATTR("strftime");


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION size_t strftime(
        char            * const __s,
        size_t const            __maxsiz,
        char const      * const __fmt,
        struct tm const * const __tp)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __s,
            __maxsiz,
            1,
            __fortify_fail_overflow_dst_diag_strftime);
    return __strftime_alias(__s, __maxsiz, __fmt, __tp);
}

#endif /* __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _TIME_CHK_H_INCLUDED */
