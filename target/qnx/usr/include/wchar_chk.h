/*
 * $QNXtpLicenseC:
 * Copyright 2010-2023, QNX Software Systems. All Rights Reserved.
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
 * $
 */

#ifndef _WCHAR_H_INCLUDED
#error <wchar_chk.h> should not be included directly.
#endif

#ifndef _WCHAR_CHK_H_INCLUDED
#define _WCHAR_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_fgetws,
        __fortify_fail_overflow_dst,
        "argument 2 of 'fgetws' is greater than the number of 'wchar_t' elements in the object referenced by argument 1");
extern wchar_t *__fgetws_alias(wchar_t * _Restrict __ws, int __n, FILE * _Restrict __stream) __ALIASATTR("fgetws");

extern int __fwprintf_chk(FILE * _Restrict __stream, int __flag, const wchar_t * _Restrict __format, ...);
extern int __fwprintf_alias(FILE * _Restrict __stream, const wchar_t * _Restrict __format, ...) __ALIASATTR("fwprintf");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_mbsrtowcs,
        __fortify_fail_overflow_dst,
        "argument 3 of 'mbsrtowcs' is greater than the number of 'wchar_t' elements in the object referenced by argument 1");
extern size_t __mbsrtowcs_alias(wchar_t * _Restrict __dst, const char ** _Restrict __src, size_t __len, mbstate_t * _Restrict __ps)
        __ALIASATTR("mbsrtowcs");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_swprintf,
        __fortify_fail_overflow_dst,
        "argument 2 of 'swprintf' is greater than the number of 'wchar_t' elements in the object referenced by argument 1");
extern int __swprintf_chk(wchar_t * _Restrict __ws, size_t __n, int flag, size_t __osize, const wchar_t * _Restrict __format, ...);
extern int __swprintf_alias(wchar_t * _Restrict __ws, size_t __n, const wchar_t * _Restrict __format, ...) __ALIASATTR("swprintf");

extern int __vfwprintf_chk(FILE * _Restrict __stream, int __flag, const wchar_t * _Restrict __format, __NTO_va_list __arg);
extern int __vfwprintf_alias(FILE * _Restrict __stream, const wchar_t * _Restrict __format, __NTO_va_list __arg)
        __ALIASATTR("vfwprintf");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_vswprintf,
        __fortify_fail_overflow_dst,
        "argument 2 of 'vswprintf' is greater than the number of 'wchar_t' elements in the object referenced by argument 1");
extern int __vswprintf_chk(
        wchar_t       * _Restrict __ws,
        size_t                    __n,
        int                       __flag,
        size_t                    __osize,
        const wchar_t * _Restrict __format,
        __NTO_va_list             __arg);
extern int __vswprintf_alias(wchar_t * _Restrict __ws, size_t __n, const wchar_t * _Restrict __format, __NTO_va_list __arg)
        __ALIASATTR("vswprintf");

extern int __vwprintf_chk(int __flag, const wchar_t * _Restrict __format, __NTO_va_list __arg);
extern int __vwprintf_alias(const wchar_t * _Restrict __format, __NTO_va_list __arg) __ALIASATTR("wprintf");

extern size_t __wcrtomb_chk(char * _Restrict __s, wchar_t __wc, mbstate_t * _Restrict __ps, size_t __osize);
extern size_t __wcrtomb_alias(char * _Restrict __s, wchar_t __wc, mbstate_t * _Restrict __ps) __ALIASATTR("wcrtomb");

extern wchar_t *__wcscat_chk(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, size_t __osize);
extern wchar_t *__wcscat_alias(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2) __ALIASATTR("wcscat");

extern wchar_t *__wcscpy_chk(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, size_t __osize);
extern wchar_t *__wcscpy_alias(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2) __ALIASATTR("wcscpy");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_wcsftime,
        __fortify_fail_overflow_dst,
        "argument 2 of 'wcsftime' is greater than the number of 'wchar_t' "
                "elements in the object referenced by argument 1");
extern size_t __wcsftime_alias(
        wchar_t         * _Restrict __ws,
        size_t                      __maxsize,
        wchar_t const   * _Restrict __format,
        struct tm const * _Restrict __timeptr) __ALIASATTR("wcsftime");

extern wchar_t *__wcsncat_chk(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n, size_t __osize);
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_wcsncat,
        __fortify_fail_overflow_dst,
        "argument 3 of 'wcsncat' is greater than or equal to the number of 'wchar_t' elements in the object referenced by "
                "argument 1");
extern wchar_t *__wcsncat_alias(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n) __ALIASATTR("wcsncat");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_wcsncpy,
        __fortify_fail_overflow_dst,
        "argument 3 of 'wcsncpy' is greater than the number of 'wchar_t' elements in the object referenced by argument 1");
extern wchar_t *__wcsncpy_alias(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n) __ALIASATTR("wcsncpy");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_wcsrtombs,
        __fortify_fail_overflow_dst,
        "argument 3 of 'wcsrtombs' is greater than the size of the object referenced by argument 1");
extern size_t __wcsrtombs_alias(char * _Restrict __dst, const wchar_t ** _Restrict __src, size_t __len, mbstate_t * _Restrict __ps)
        __ALIASATTR("wcsrtombs");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_wcsxfrm,
        __fortify_fail_overflow_dst,
        "argument 3 of 'wcsxfrm' is greater than the number of 'wchar_t' "
                "elements in the object referenced by argument 1");
extern size_t __wcsxfrm_alias(
        wchar_t       * _Restrict __ws1,
        wchar_t const * _Restrict __ws2,
        size_t                    __n) __ALIASATTR("wcsxfrm");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_wmemcpy,
        __fortify_fail_overflow_dst,
        "argument 3 of 'wmemcpy' is greater than the number of 'wchar_t' elements in the object referenced by argument 1");
extern wchar_t *__wmemcpy_alias(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n) __ALIASATTR("wmemcpy");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_wmemmove,
        __fortify_fail_overflow_dst,
        "argument 3 of 'wmemmove' is greater than the number of 'wchar_t' elements in the object referenced by argument 1");
extern wchar_t *__wmemmove_alias(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n) __ALIASATTR("wmemmove");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_wmemset,
        __fortify_fail_overflow_dst,
        "argument 3 of 'wmemset' is greater than the number of 'wchar_t' elements in the object referenced by argument 1");
extern wchar_t *__wmemset_alias(wchar_t * __s, wchar_t __wc, size_t __n) __ALIASATTR("wmemset");

extern int __wprintf_chk(int __flag, const wchar_t * _Restrict __format, ...);
extern int __wprintf_alias(const wchar_t * _Restrict __format, ...) __ALIASATTR("wprintf");


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION wchar_t *fgetws(wchar_t * const _Restrict __ws, const int __n, FILE * const _Restrict __stream)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __ws, (unsigned int)__n, __n > 0, __fortify_fail_overflow_dst_diag_fgetws);
    return __fgetws_alias(__ws, __n, __stream);
}

extern __FORTIFY_FUNCTION int fwprintf(FILE * const _Restrict __stream, const wchar_t * const _Restrict __format, ...)
{
    /* If __NTO_FORTIFY_LEVEL is greater than 1, call __fwprintf_chk instead of the regular (unfortified) fwprintf function.
     * __fwprintf_chk causes __fortify_fail_fmt_n to be invoked if the second argument (__flag) is nonzero and the
     * __format argument is a format string containing the n conversion specifier (e.g. "%n"). */
    if ( __NTO_FORTIFY_LEVEL > 1 ) {
        return __fwprintf_chk(__stream, __NTO_FORTIFY_LEVEL - 1, __format, __bvap);
    } else {
        return __fwprintf_alias(__stream, __format, __bvap);
    }
}

extern __FORTIFY_FUNCTION size_t mbsrtowcs(
        wchar_t       * const _Restrict __dst,
        const char   ** const _Restrict __src,
        const size_t                    __len,
        mbstate_t     * const _Restrict __ps)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __dst, __len, 1, __fortify_fail_overflow_dst_diag_mbsrtowcs);
    return __mbsrtowcs_alias(__dst, __src, __len, __ps);
}

extern __FORTIFY_FUNCTION int swprintf(
        wchar_t       * const _Restrict __ws,
        const size_t                    __n,
        const wchar_t * const _Restrict __format,
        ...)
{
    /* If __NTO_FORTIFY_LEVEL is greater than 1 and/or the size (in wchar_t elements) of the destination object (__ws) is known at
     * compile time, call __swprintf_chk instead of the regular (unfortified) swprintf function. __swprintf_chk causes
     * __fortify_fail_fmt_n to be invoked if the third argument (__flag) is nonzero and the __format argument is a format string
     * containing the n conversion specifier (e.g. "%n"). __swprintf_chk invokes __fortify_fail_overflow_dst if the maximum number
     * of wide characters to store (__n) is greater than the size (in wchar_t elements) of the destination object (__ws). */
    if ( __bos_default(__ws) != __BOS_UNKNOWN ) {
        /* Fail and emit an error/warning at compile time if the __n argument is known to be constant and is greater than the size
         * (in wchar_t elements) of the destination object (__ws) */
        if ( __bconst(__n) && ( __n > (__bos_default(__ws) / sizeof(__ws[0])) ) ) {
            __fortify_fail_overflow_dst_diag_swprintf();
        }
        return __swprintf_chk(__ws, __n, __NTO_FORTIFY_LEVEL - 1, __bos_default(__ws) / sizeof(__ws[0]), __format, __bvap);
    } else if ( __NTO_FORTIFY_LEVEL > 1 ) {
        return __swprintf_chk(__ws, __n, __NTO_FORTIFY_LEVEL - 1, __BOS_UNKNOWN, __format, __bvap);
    } else {
        return __swprintf_alias(__ws, __n, __format, __bvap);
    }
}

extern __FORTIFY_FUNCTION int vfwprintf(
        FILE          * const _Restrict __stream,
        const wchar_t * const _Restrict __format,
        __NTO_va_list                   __arg)
{
    /* If __NTO_FORTIFY_LEVEL is greater than 1, call __vfwprintf_chk instead of the regular (unfortified) vfwprintf function.
     * __vfwprintf_chk causes __fortify_fail_fmt_n to be invoked if the second argument (__flag) is nonzero and the __format
     * argument is a format string containing the n conversion specifier (e.g. "%n"). */
    if ( __NTO_FORTIFY_LEVEL > 1 ) {
        return __vfwprintf_chk(__stream, __NTO_FORTIFY_LEVEL - 1, __format, __arg);
    } else {
        return __vfwprintf_alias(__stream, __format, __arg);
    }
}

extern __FORTIFY_FUNCTION int vswprintf(
        wchar_t       * const _Restrict __ws,
        const size_t                    __n,
        const wchar_t * const _Restrict __format,
        __NTO_va_list                   __arg)
{
    /* If __NTO_FORTIFY_LEVEL is greater than 1 and/or the size (in wchar_t elements) of the destination object (__ws) is known at
     * compile time, call __vswprintf_chk instead of the regular (unfortified) vswprintf function. __vswprintf_chk causes
     * __fortify_fail_fmt_n to be invoked if the third argument (__flag) is nonzero and the __format argument is a format string
     * containing the n conversion specifier (e.g. "%n"). __vswprintf_chk invokes __fortify_fail_overflow_dst if the maximum number
     * of wide characters to store (__n) is greater than the size (in wchar_t elements) of the destination object (__ws). */
    if ( __bos_default(__ws) != __BOS_UNKNOWN ) {
        /* Fail and emit an error/warning at compile time if the __n argument is known to be constant and is greater than the size
         * (in wchar_t elements) of the destination object (__ws) */
        if ( __bconst(__n) && ( __n > (__bos_default(__ws) / sizeof(__ws[0])) ) ) {
            __fortify_fail_overflow_dst_diag_vswprintf();
        }
        return __vswprintf_chk(__ws, __n, __NTO_FORTIFY_LEVEL - 1, __bos_default(__ws) / sizeof(__ws[0]), __format, __arg);
    } else if ( __NTO_FORTIFY_LEVEL > 1 ) {
        return __vswprintf_chk(__ws, __n, __NTO_FORTIFY_LEVEL - 1, __BOS_UNKNOWN, __format, __arg);
    } else {
        return __vswprintf_alias(__ws, __n, __format, __arg);
    }
}

extern __FORTIFY_FUNCTION int vwprintf(const wchar_t * const _Restrict __format, __NTO_va_list __arg)
{
    /* If __NTO_FORTIFY_LEVEL is greater than 1, call __vwprintf_chk instead of the regular (unfortified) vwprintf function.
     * __vwprintf_chk causes __fortify_fail_fmt_n to be invoked if the first argument (__flag) is nonzero and the __format argument
     * is a format string containing the n conversion specifier (e.g. "%n"). */
    if ( __NTO_FORTIFY_LEVEL > 1 ) {
        return __vwprintf_chk(__NTO_FORTIFY_LEVEL - 1, __format, __arg);
    } else {
        return __vwprintf_alias(__format, __arg);
    }
}

extern __FORTIFY_FUNCTION size_t wcrtomb(char * const _Restrict __s, const wchar_t __wc, mbstate_t * const _Restrict __ps)
{
    /* If the size of the destination object (__s) is known at compile time, call __wcrtomb_chk instead of the regular (unfortified)
     * wcrtomb function. __wcrtomb_chk calls __fortify_fail_overflow_dst if the length of the multi-byte character to be written
     * exceeds the size of the destination object (__s) determined at compile time. */
    if ( __bos_default(__s) != __BOS_UNKNOWN ) {
        return __wcrtomb_chk(__s, __wc, __ps, __bos_default(__s));
    } else {
        return __wcrtomb_alias(__s, __wc, __ps);
    }
}

extern __FORTIFY_FUNCTION wchar_t *wcscat(wchar_t * const _Restrict __ws1, const wchar_t * const _Restrict __ws2)
{
    /* If the size of the destination object (__ws1) is known at compile time, call __wcscat_chk instead of the regular
     * (unfortified) wcscat function. __wcscat_chk calls __fortify_fail_overflow_dst if the length of the concatenated wide string
     * plus the terminating wide NUL character is greater than the size (in wchar_t elements) of the destination object (__ws1)
     * determined at compile time. */
    if ( __bos_default(__ws1) != __BOS_UNKNOWN ) {
        return __wcscat_chk(__ws1, __ws2, __bos_default(__ws1) / sizeof(__ws1[0]));
    } else {
        return __wcscat_alias(__ws1, __ws2);
    }
}

extern __FORTIFY_FUNCTION wchar_t *wcscpy(wchar_t * const _Restrict __ws1, const wchar_t * const _Restrict __ws2)
{
    /* If the size of the destination object (__ws1) is known at compile time, call __wcscpy_chk instead of the regular
     * (unfortified) wcscpy function. __wcscpy_chk calls __fortify_fail_overflow_dst if the length of the NUL-terminated wide string
     * to be copied is greater than the size (in wchar_t elements) of the destination object (__ws1) determined at compile time. */
    if ( __bos_default(__ws1) != __BOS_UNKNOWN ) {
        return __wcscpy_chk(__ws1, __ws2, __bos_default(__ws1) / sizeof(__ws1[0]));
    } else {
        return __wcscpy_alias(__ws1, __ws2);
    }
}

extern __FORTIFY_FUNCTION size_t wcsftime(
        wchar_t         * const _Restrict __ws,
        size_t const                      __maxsize,
        wchar_t const   * const _Restrict __format,
        struct tm const * const _Restrict __timeptr)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __ws,
            __maxsize,
            1,
            __fortify_fail_overflow_dst_diag_wcsftime);
    return __wcsftime_alias(__ws, __maxsize, __format, __timeptr);
}

extern __FORTIFY_FUNCTION wchar_t *wcsncat(wchar_t * const _Restrict __ws1, const wchar_t * const _Restrict __ws2, const size_t __n)
{
    /* If the size of the destination object (__ws1) is known at compile time, call __wcsncat_chk instead of the regular
     * (unfortified) wcsncat function. __wcsncat_chk calls __fortify_fail_overflow_dst if the length of the concatenated wide string
     * plus the terminating wide NUL character is greater than the size (in wchar_t elements) of the destination object (__ws1)
     * determined at compile time. */
    if ( __bos_default(__ws1) != __BOS_UNKNOWN ) {
        /* Fail and emit an error/warning if the maximum number of wide characters to append including the terminating wide NUL
         * character (__n + 1) is known to be constant at compile time and is greater than the size (in wchar_t elements) of the
         * destination object (__s1) */
        if ( __bconst(__n) && ( __n >= (__bos_default(__ws1) / sizeof(__ws1[0])) ) ) {
            __fortify_fail_overflow_dst_diag_wcsncat();
        }
        return __wcsncat_chk(__ws1, __ws2, __n, __bos_default(__ws1) / sizeof(__ws1[0]));
    } else {
        return __wcsncat_alias(__ws1, __ws2, __n);
    }
}

extern __FORTIFY_FUNCTION wchar_t *wcsncpy(wchar_t * const _Restrict __ws1, const wchar_t * const _Restrict __ws2, const size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __ws1, __n, 1, __fortify_fail_overflow_dst_diag_wcsncpy);
    return __wcsncpy_alias(__ws1, __ws2, __n);
}

extern __FORTIFY_FUNCTION size_t wcsrtombs(
        char           * const _Restrict __dst,
        const wchar_t ** const _Restrict __src,
        const size_t                     __len,
        mbstate_t      * const _Restrict __ps)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __dst, __len, 1, __fortify_fail_overflow_dst_diag_wcsrtombs);
    return __wcsrtombs_alias(__dst, __src, __len, __ps);
}

extern __FORTIFY_FUNCTION size_t wcsxfrm(
        wchar_t       * const _Restrict __ws1,
        wchar_t const * const _Restrict __ws2,
        size_t const                    __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __ws1,
            __n,
            1,
            __fortify_fail_overflow_dst_diag_wcsxfrm);
    return __wcsxfrm_alias(__ws1, __ws2, __n);
}

extern __FORTIFY_FUNCTION wchar_t *wmemcpy(wchar_t * const _Restrict __ws1, const wchar_t * const _Restrict __ws2, const size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, __ws1, __n, 1, __fortify_fail_overflow_dst_diag_wmemcpy);
    return __wmemcpy_alias(__ws1, __ws2, __n);
}

extern __FORTIFY_FUNCTION wchar_t *wmemmove(
        wchar_t       * const _Restrict __ws1,
        const wchar_t * const _Restrict __ws2,
        const size_t                    __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, __ws1, __n, 1, __fortify_fail_overflow_dst_diag_wmemmove);
    return __wmemmove_alias(__ws1, __ws2, __n);
}

extern __FORTIFY_FUNCTION wchar_t *wmemset(wchar_t * const __ws, const wchar_t __wc, const size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, __ws, __n, 1, __fortify_fail_overflow_dst_diag_wmemset);
    return __wmemset_alias(__ws, __wc, __n);
}

extern __FORTIFY_FUNCTION int wprintf(const wchar_t * const _Restrict __format, ...)
{
    /* If __NTO_FORTIFY_LEVEL is greater than 1, call __wprintf_chk instead of the regular (unfortified) wprintf function.
     * __wprintf_chk causes __fortify_fail_fmt_n to be invoked if the first argument (__flag) is nonzero and the __format argument
     * is a format string containing the n conversion specifier (e.g. "%n"). */
    if ( __NTO_FORTIFY_LEVEL > 1 ) {
        return __wprintf_chk(__NTO_FORTIFY_LEVEL - 1, __format, __bvap);
    } else {
        return __wprintf_alias(__format, __bvap);
    }
}

#endif /* __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _WCHAR_CHK_H_INCLUDED */
