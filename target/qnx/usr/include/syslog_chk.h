/*
 * Copyright (c) 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef _SYSLOG_H_INCLUDED
#error <syslog_chk.h> should not be included directly.
#endif

#ifndef _SYSLOG_CHK_H_INCLUDED
#define _SYSLOG_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

#ifdef __bvap
extern void __syslog_chk(int __pri, int __flag, char const *__fmt, ...)
        __attribute__((__format__(__printf__, 3, 4)));

extern void __syslog_alias(int __pri, char const *__fmt, ...)
        __ALIASATTR("syslog") __attribute__((__format__(__printf__, 2, 3)));
#endif /* #ifdef __bvap */

extern void __vsyslog_chk(
        int __pri, int __flag, char const *__fmt, __NTO_va_list __ap)
        __attribute__((__format__(__printf__, 3, 0)));

extern void __vsyslog_alias(
        int __pri, char const *__fmt, __NTO_va_list __ap)
        __ALIASATTR("vsyslog") __attribute__((__format__(__printf__, 2, 0)));


#if __NTO_FORTIFY_LEVEL > 0

#ifdef __bvap
extern __FORTIFY_FUNCTION void syslog(
        int const          __pri,
        char const * const __fmt,
        ...)
{
/* The format attribute is specified in the prototype for this function, so the
 * compiler will have already applied -Wformat checks. Silence the irrelevant
 * instances of -Wformat-nonliteral in the calls below. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    /* If __NTO_FORTIFY_LEVEL is greater than 1, call __syslog_chk instead of
     * the regular (unfortified) syslog function. __syslog_chk causes
     * __fortify_fail_fmt_n to be invoked if the second argument (__flag) is
     * nonzero and an n conversion specifier (e.g. "%n") in the __fmt format
     * string would result in data being written to an address specified by an
     * optional argument. */
    if ( __NTO_FORTIFY_LEVEL > 1 ) {
        __syslog_chk(__pri, __NTO_FORTIFY_LEVEL - 1, __fmt, __bvap);
    } else {
        __syslog_alias(__pri, __fmt, __bvap);
    }
#pragma GCC diagnostic pop
}
#endif /* #ifdef __bvap */

extern __FORTIFY_FUNCTION void vsyslog(
        int const             __pri,
        char const    * const __fmt,
        __NTO_va_list         __ap)
{
    /* If __NTO_FORTIFY_LEVEL is greater than 1, call __vsyslog_chk instead of
     * the regular (unfortified) vsyslog function. __vsyslog_chk causes
     * __fortify_fail_fmt_n to be invoked if the second argument (__flag) is
     * nonzero and an n conversion specifier (e.g. "%n") in the __fmt format
     * string would result in data being written to an address specified by an
     * optional argument. */
    if ( __NTO_FORTIFY_LEVEL > 1 ) {
        __vsyslog_chk(__pri, __NTO_FORTIFY_LEVEL - 1, __fmt, __ap);
    } else {
        __vsyslog_alias(__pri, __fmt, __ap);
    }
}

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _SYSLOG_CHK_H_INCLUDED */
