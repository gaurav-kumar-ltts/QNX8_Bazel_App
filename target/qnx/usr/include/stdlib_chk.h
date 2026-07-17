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

#ifndef _STDLIB_H_INCLUDED
#error <stdlib_chk.h> should not be included directly.
#endif

#ifndef _STDLIB_CHK_H_INCLUDED
#define _STDLIB_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

/* Same value as PATH_MAX in limits.h */
#define _STDLIB_CHK_H_PATH_MAX  1024

#if defined(__EXT_XOPEN_EX)
#if defined(__EXT_QNX)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_ptsname_r,
        __fortify_fail_overflow_dst,
        "argument 3 of 'ptsname_r' is greater than the size of the object "
                "referenced by argument 2");
extern int __ptsname_r_alias(int __fildes, char *__buffer, size_t __buflen)
        __ALIASATTR("ptsname_r");
#endif /* #if defined(__EXT_QNX) */

extern char *__realpath_chk(const char *__file_name, char *__resolved_name, size_t __osize);
extern char *__realpath_chk_diag(const char *__file_name, char *__resolved_name, size_t __osize) __ALIASATTR("__realpath_chk")
        __FORTIFY_FAIL_DIAG_ATTRIBUTE("argument 2 of 'realpath' references an object smaller than 'PATH_MAX' bytes");
extern char *__realpath_alias(const char *__file_name, char *__resolved_name) __ALIASATTR("realpath");
#endif /* #if defined(__EXT_XOPEN_EX) */

#if defined(__EXT_ANSIC_199012)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_mbstowcs,
        __fortify_fail_overflow_dst,
        "argument 3 of 'mbstowcs' is greater than the number of 'wchar_t' elements in the object referenced by argument 1");
extern size_t __mbstowcs_alias(wchar_t *__pwcs, const char *__s, size_t __n) __ALIASATTR("mbstowcs");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_wcstombs,
        __fortify_fail_overflow_dst,
        "argument 3 of 'wcstombs' is greater than the size of the object referenced by argument 1");
extern size_t __wcstombs_alias(char *__s, const wchar_t *__pwcs, size_t __n) __ALIASATTR("wcstombs");

extern int __wctomb_chk(char *__s, wchar_t __wchar, size_t __osize);
extern int __wctomb_alias(char *__s, wchar_t __wchar) __ALIASATTR("wctomb");
#endif /* #if defined(__EXT_ANSIC_199012) */

#if defined(__EXT_PCDOS)
extern void __searchenv_chk(
        char const *__name,
        char const *__env_var,
        char       *__buf,
        size_t      __osize);
extern void __searchenv_chk_diag(
        char const *__name,
        char const *__env_var,
        char       *__buf,
        size_t      __osize)
        __ALIASATTR("__searchenv_chk")
        __FORTIFY_FAIL_DIAG_ATTRIBUTE(
                "argument 3 of 'searchenv' references an object smaller than "
                        "'PATH_MAX' bytes");
extern void __searchenv_alias(
        char const *__name,
        char const *__env_var,
        char       *__buf)
        __ALIASATTR("searchenv");
#endif /* #if defined(__EXT_PCDOS) */


#if __NTO_FORTIFY_LEVEL > 0

#if defined(__EXT_XOPEN_EX)
#if defined(__EXT_QNX)
extern __FORTIFY_FUNCTION int ptsname_r(
        int const            __fildes,
        char         * const __buffer,
        size_t const         __buflen)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __buffer,
            __buflen,
            1,
            __fortify_fail_overflow_dst_diag_ptsname_r);
    return __ptsname_r_alias(__fildes, __buffer, __buflen);
}
#endif /* #if defined(__EXT_QNX) */

extern __FORTIFY_FUNCTION char *realpath(const char * const __file_name, char * const __resolved_name)
{
    /* If the size of the destination object (__resolved_name) is known at compile time, call __realpath_chk instead of the regular
     * (unfortified) realpath function. __realpath_chk calls __fortify_fail_overflow_dst if the length of the NUL-terminated string
     * to be written exceeds the size of the destination object (__resolved_name) determined at compile time. */
    if ( __bos_default(__resolved_name) != __BOS_UNKNOWN ) {
        /* Emit an error/warning if the size of the destination object is less
         * than PATH_MAX. PATH_MAX is already known to be an integer
         * constant. */
        if ( __bos_default(__resolved_name) < (size_t)_STDLIB_CHK_H_PATH_MAX ) {
            return __realpath_chk_diag(
                    __file_name,
                    __resolved_name,
                    __bos_default(__resolved_name));
        } else {
            return __realpath_chk(
                    __file_name,
                    __resolved_name,
                    __bos_default(__resolved_name));
        }
    } else {
        return __realpath_alias(__file_name, __resolved_name);
    }
}
#endif /* #if defined(__EXT_XOPEN_EX) */

#if defined(__EXT_ANSIC_199012)
extern __FORTIFY_FUNCTION size_t mbstowcs(wchar_t * const __pwcs, const char * const __s, const size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __pwcs, __n, 1, __fortify_fail_overflow_dst_diag_mbstowcs);
    return __mbstowcs_alias(__pwcs, __s, __n);
}

extern __FORTIFY_FUNCTION size_t wcstombs(char * const __s, const wchar_t * const __pwcs, const size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __s, __n, 1, __fortify_fail_overflow_dst_diag_wcstombs);
    return __wcstombs_alias(__s, __pwcs, __n);
}

extern __FORTIFY_FUNCTION int wctomb(char * const __s, const wchar_t __wchar)
{
    /* If the size of the destination object (__s) is known at compile time, call the __wctomb_chk function instead of the regular
     * (unfortified) wctomb function. __wctomb_chk calls __fortify_fail_overflow_dst if the length of the multi-byte character to be
     * written exceeds the size of the destination object (__s) determined at compile time. */
    if ( __bos_default(__s) != __BOS_UNKNOWN ) {
        return __wctomb_chk(__s, __wchar, __bos_default(__s));
    } else {
        return __wctomb_alias(__s, __wchar);
    }
}
#endif /* #if defined(__EXT_ANSIC_199012) */

#if defined(__EXT_PCDOS)
extern __FORTIFY_FUNCTION void searchenv(
        char const * const __name,
        char const * const __env_var,
        char       * const __buf)
{
    if ( __bos_default(__buf) != __BOS_UNKNOWN ) {
        /* Emit an error/warning if the size of the destination object is less
         * than PATH_MAX. PATH_MAX is already known to be an integer
         * constant. */
        if ( __bos_default(__buf) < (size_t)_STDLIB_CHK_H_PATH_MAX ) {
            __searchenv_chk_diag(
                    __name,
                    __env_var,
                    __buf,
                    __bos_default(__buf));
        } else {
            __searchenv_chk(
                    __name,
                    __env_var,
                    __buf,
                    __bos_default(__buf));
        }
    } else {
        __searchenv_alias(__name, __env_var, __buf);
    }
}
#endif /* #if defined(__EXT_PCDOS) */

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _STDLIB_CHK_H_INCLUDED */
