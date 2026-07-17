/*
 * $QNXtpLicenseC:
 * Copyright 2010-2021, QNX Software Systems. All Rights Reserved.
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

#ifndef _STDIO_H_INCLUDED
#error <stdio_chk.h> should not be included directly.
#endif

#ifndef _STDIO_CHK_H_INCLUDED
#define _STDIO_CHK_H_INCLUDED

#include <fortify.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC system_header
#endif

__BEGIN_DECLS

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_fgets,
        __fortify_fail_overflow_dst,
        "argument 2 of 'fgets' is greater than the size of the object referenced by argument 1");
extern char *__fgets_alias(char *__s, int __n, FILE *__fp) __ALIASATTR("fgets");

#ifdef __bvap
extern int __fprintf_chk(FILE * const __fp, int __flag, const char * const __format, ...)
        __attribute__((__format__(__printf__, 3, 4)));
#endif /* #ifdef __bvap */

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_fread,
        __fortify_fail_overflow_dst,
        "the product of arguments 2 and 3 of 'fread' is greater than the size of the object referenced by argument 1");
extern size_t __fread_alias(void *__ptr, size_t __size, size_t __n, FILE *__fp) __ALIASATTR("fread");

#ifdef __bvap
extern int __printf_chk(int __flag, const char * const __format, ...) __attribute__((__format__(__printf__, 2, 3)));
#endif /* #ifdef __bvap */

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_snprintf,
        __fortify_fail_overflow_dst,
        "argument 2 of 'snprintf' is greater than the size of the object referenced by argument 1");
extern int __snprintf_chk(char *__s, size_t __size, int __flag, size_t __osize, const char *__format, ...)
        __attribute__((__format__(__printf__, 5, 6)));

extern int __sprintf_chk(char *__s, int __flag, size_t __osize, const char *__format, ...)
        __attribute__((__format__(__printf__, 4, 5)));

#ifdef __bvap
extern int __vfprintf_chk(FILE * const __fp, int __flag, const char * const __format, __NTO_va_list __arg)
        __attribute__((__format__(__printf__, 3, 0)));

extern int __vprintf_chk(int __flag, const char * const __format, __NTO_va_list __arg)
        __attribute__((__format__(__printf__, 2, 0)));
#endif /* #ifdef __bvap */

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_vsnprintf,
        __fortify_fail_overflow_dst,
        "argument 2 of 'vsnprintf' is greater than the size of the object referenced by argument 1");
extern int __vsnprintf_chk(char *__s, size_t __size, int __flag, size_t __osize, const char *__format, __NTO_va_list  __arg)
        __attribute__((__format__(__printf__, 5, 0)));

extern int __vsprintf_chk(char *__s, int __flag, size_t __osize, const char *__format, __NTO_va_list  __arg)
        __attribute__((__format__(__printf__, 4, 0)));

#if !defined(__EXT_ANSIC_201112) && ( __cplusplus - 0 <= 201103L )
extern char *__gets_chk(char *__s, size_t __osize);
extern char *__gets_alias(char *__s) __ALIASATTR("gets");
#endif /* #if !defined(__EXT_ANSIC_201112) && ( __cplusplus - 0 <= 201103L ) */

#if defined(__EXT_QNX)
#ifdef __bvap
extern int __asprintf_chk(char **__strp, int __flag, const char *__fmt, ...) __attribute__((__format__(__printf__, 3, 4)));
extern int __asprintf_alias(char **__strp, const char *__fmt, ...) __ALIASATTR("asprintf")
        __attribute__((__format__(__printf__, 2, 3)));
#endif /* #ifdef __bvap */

extern int __vasprintf_chk(char **__strp, int __flag, const char *__fmt, __NTO_va_list __arg)
        __attribute__((__format__(__printf__, 3, 0)));
extern int __vasprintf_alias(char **__strp, const char *__fmt, __NTO_va_list __arg) __ALIASATTR("vasprintf")
        __attribute__((__format__(__printf__, 2, 0)));
#endif /* #if defined(__EXT_QNX) */

#if defined(__EXT_POSIX1_200809)
#ifdef __bvap
extern int __dprintf_chk(int __fildes, int __flag, const char * _Restrict __format, ...)
        __attribute__((__format__(__printf__, 3, 4)));
extern int __dprintf_alias(int __fildes, const char * _Restrict __format, ...) __ALIASATTR("dprintf")
        __attribute__((__format__(__printf__, 2, 3)));
#endif /* #ifdef __bvap */

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_getdelim,
        __fortify_fail_overflow_dst,
        "argument 2 of 'getdelim' references a value greater than the size of the object indirectly referenced by argument 1");
extern ssize_t __getdelim_alias(char **__lineptr, size_t *__lenptr, int __delimiter, FILE *__stream) __ALIASATTR("getdelim");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_getline,
        __fortify_fail_overflow_dst,
        "argument 2 of 'getline' references a value greater than the size of the object indirectly referenced by argument 1");
extern ssize_t __getline_alias(char **__lineptr, size_t *__lenptr, FILE *__stream) __ALIASATTR("getline");

extern int __vdprintf_chk(int __fildes, int __flag, const char * _Restrict __format, __NTO_va_list __arg)
        __attribute__((__format__(__printf__, 3, 0)));
extern int __vdprintf_alias(int __fildes, const char * _Restrict __format, __NTO_va_list __arg) __ALIASATTR("vdprintf")
        __attribute__((__format__(__printf__, 2, 0)));
#endif /* #if defined(__EXT_POSIX1_200809) */


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION char *fgets(char * const __s, const int __n, FILE * const __fp)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __s, (unsigned int)__n, __n > 0, __fortify_fail_overflow_dst_diag_fgets);
    return __fgets_alias(__s, __n, __fp);
}

#ifdef __bvap
extern __FORTIFY_FUNCTION int fprintf(FILE * const __fp, const char * const __format, ...)
{
/* The format attribute is specified in the prototype for this function, so the
 * compiler will have already applied -Wformat checks. Silence the irrelevant
 * instance of -Wformat-nonliteral in the call below. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    /* Leverage the compiler's built-in __fprintf_chk function which resolves to a call to the __fprintf_chk function when the
     * second argument is nonzero (i.e. the _FORTIFY_SOURCE feature test macro has been defined with a value greater than 1) and the
     * __format argument isn't a trivially simple format string. Otherwise, it resolves to a call to the regular (unfortified)
     * fprintf function or a compatible but more performant alternative. __fprintf_chk causes __fortify_fail_fmt_n to be invoked if
     * the second argument (__flag) is nonzero and the __format argument contains the n conversion specifier (e.g. "%n"). */
    return __builtin___fprintf_chk(__fp, __NTO_FORTIFY_LEVEL - 1, __format, __bvap);
#pragma GCC diagnostic pop
}
#endif /* #ifdef __bvap */

extern __FORTIFY_FUNCTION size_t fread(void * const __ptr, const size_t __size, const size_t __n, FILE * const __fp)
{
    /* Fail if the maximum number of bytes read (__size * __n) is greater than the size of the destination object (__ptr)
     * determined at compile time. Also emit an error/warning if both the __size and __n arguments are known to be constant at
     * compile time. __bos_outer is used to obtain the size of the destination object instead of __bos in order to reduce false
     * positives when the _FORTIFY_SOURCE feature test macro has been defined with a value greater than 1. */
    if ( __bos_outer(__ptr) != __BOS_UNKNOWN ) {
        /* Attempt to put all constant terms on one side of the comparison expression so that the compiler will fold them together
         * into a single constant */
        if ( __bconst(__n) ) {
            if ( __bconst(__size) ) {
                if ( ( __size != 0 ) && ( __n > (__bos_outer(__ptr) / __size) ) ) {
                    __fortify_fail_overflow_dst_diag_fread();
                }
            } else {
                if ( __unlikely(( __n != 0 ) && ( __size > (__bos_outer(__ptr) / __n) )) ) {
                    __fortify_fail_overflow_dst();
                }
            }
        } else {
            if ( __unlikely(( __size != 0 ) && ( __n > (__bos_outer(__ptr) / __size) )) ) {
                __fortify_fail_overflow_dst();
            }
        }
    }
    return __fread_alias(__ptr, __size, __n, __fp);
}

#ifdef __bvap
extern __FORTIFY_FUNCTION int printf(const char * const __format, ...)
{
/* The format attribute is specified in the prototype for this function, so the
 * compiler will have already applied -Wformat checks. Silence the irrelevant
 * instance of -Wformat-nonliteral in the call below. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    /* Leverage the compiler's built-in __printf_chk function which resolves to a call to the __printf_chk function when the first
     * argument is nonzero (i.e. the _FORTIFY_SOURCE feature test macro has been defined with a value greater than 1) and the
     * __format argument isn't a trivially simple format string. Otherwise, it resolves to a call to the regular (unfortified)
     * printf function or a compatible but more performant alternative. __printf_chk causes __fortify_fail_fmt_n to be invoked if
     * the first argument (__flag) is nonzero and the __format argument contains the n conversion specifier (e.g. "%n"). */
    return __builtin___printf_chk(__NTO_FORTIFY_LEVEL - 1, __format, __bvap);
#pragma GCC diagnostic pop
}

extern __FORTIFY_FUNCTION int snprintf(char * const __s, const size_t __size, const char * const __format, ...)
{
    /* Fail and emit an error/warning if the maximum number of characters to write into the buffer including the terminating NUL
     * character (__size) is constant at compile time and greater than the size of the destination object (__s) determined at
     * compile time. Note that the compiler's built-in __snprintf_chk function also emits a similar warning under the same
     * conditions, but this one uses the style defined in fortify.h. */
    if ( ( __bos_default(__s) != __BOS_UNKNOWN ) && __bconst(__size) && ( __size > __bos_default(__s) ) ) {
        __fortify_fail_overflow_dst_diag_snprintf();
    }
/* The format attribute is specified in the prototype for this function, so the
 * compiler will have already applied -Wformat checks. Silence the irrelevant
 * instance of -Wformat-nonliteral in the call below. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    /* Leverage the compiler's built-in __snprintf_chk function which resolves to a call to the __snprintf_chk function when:
     *     - the third argument is a nonzero value (i.e. the _FORTIFY_SOURCE feature test macro has been defined with a value
     *       greater than 1) and the __format argument isn't a trivially simple format string, and/or
     *     - the fourth argument is a value other than __BOS_UNKNOWN (i.e. the size of the destination object (__s) is known at
     *       compile time).
     * Otherwise, it resolves to a call to the regular (unfortified) snprintf function or a compatible but more performant
     * alternative. __snprintf_chk causes __fortify_fail_fmt_n to be invoked if the third argument (__flag) is nonzero and the
     * __format argument contains the n conversion specifier (e.g. "%n"), or calls __fortify_fail_overflow_dst if the __size
     * argument is greater than the size of the destination object (__s) determined at compile time. */
    return __builtin___snprintf_chk(__s, __size, __NTO_FORTIFY_LEVEL - 1, __bos_default(__s), __format, __bvap);
#pragma GCC diagnostic pop
}

extern __FORTIFY_FUNCTION int sprintf(char * const __s, const char * const __format, ...)
{
/* The format attribute is specified in the prototype for this function, so the
 * compiler will have already applied -Wformat checks. Silence the irrelevant
 * instance of -Wformat-nonliteral in the call below. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    /* Leverage the compiler's built-in __sprintf_chk function which resolves to a call to the __sprintf_chk function when:
     *     - the second argument is a nonzero value (i.e. the _FORTIFY_SOURCE feature test macro has been defined with a value
     *       greater than 1) and the __format argument isn't a trivially simple format string, and/or
     *     - the third argument is a value other than __BOS_UNKNOWN (i.e. the size of the destination object (__s) is known at
     *       compile time).
     * Otherwise, it resolves to a call to the regular (unfortified) sprintf function or a compatible but more performant
     * alternative. __sprintf_chk causes __fortify_fail_fmt_n to be invoked if the second argument (__flag) is nonzero and the
     * __format argument contains the n conversion specifier (e.g. "%n"), or calls __fortify_fail_overflow_dst if the length of the
     * formatted string including the terminating NUL character is greater than the size of the destination object (__s) determined
     * at compile time. */
    return __builtin___sprintf_chk(__s, __NTO_FORTIFY_LEVEL - 1, __bos_default(__s), __format, __bvap);
#pragma GCC diagnostic pop
}
#endif /* #ifdef __bvap */

extern __FORTIFY_FUNCTION int vfprintf(FILE * const __fp, const char * const __format, __NTO_va_list __arg)
{
    /* Leverage the compiler's built-in __vfprintf_chk function which resolves to a call to the __vfprintf_chk function when the
     * second argument is a nonzero value (i.e. the _FORTIFY_SOURCE feature test macro has been defined with a value greater than 1)
     * and the __format argument isn't a trivially simple format string. Otherwise, it resolves to a call to the regular
     * (unfortified) vfprintf function or a compatible but more performant alternative. __vfprintf_chk causes __fortify_fail_fmt_n
     * to be invoked if the second argument (__flag) is nonzero and the __format argument contains the n conversion specifier
     * (e.g. "%n"). */
    return __builtin___vfprintf_chk(__fp, __NTO_FORTIFY_LEVEL - 1, __format, __arg);
}

extern __FORTIFY_FUNCTION int vprintf(const char * const __format, __NTO_va_list __arg)
{
    /* Leverage the compiler's built-in __vprintf_chk function which resolves to a call to the __vprintf_chk function when the
     * first argument is a nonzero value (i.e. the _FORTIFY_SOURCE feature test macro has been defined with a value greater than 1)
     * and the __format argument isn't a trivially simple format string. Otherwise, it resolves to a call to the regular
     * (unfortified) vprintf function or a compatible but more performant alternative. __vprintf_chk causes __fortify_fail_fmt_n to
     * be invoked if the first argument (__flag) is nonzero and the __format argument contains the n conversion specifier
     * (e.g. "%n"). */
    return __builtin___vprintf_chk(__NTO_FORTIFY_LEVEL - 1, __format, __arg);
}

extern __FORTIFY_FUNCTION int vsnprintf(char * const __s, const size_t __size, const char * const __format, __NTO_va_list __arg)
{
    /* Fail and emit an error/warning if the maximum number of characters to write into the buffer including the terminating NUL
     * character (__size) is greater than the size of the destination object (__s) determined at compile time. Note that the
     * compiler's built-in __vsnprintf_chk function also emits a similar warning under the same conditions, but this one uses the
     * style defined in fortify.h. */
    if ( ( __bos_default(__s) != __BOS_UNKNOWN ) && __bconst(__size) && ( __size > __bos_default(__s) ) ) {
        __fortify_fail_overflow_dst_diag_vsnprintf();
    }
    /* Leverage the compiler's built-in __vsnprintf_chk function which resolves to a call to the __vsnprintf_chk function when:
     *     - the third argument is a nonzero value (i.e. the _FORTIFY_SOURCE feature test macro has been defined with a value
     *       greater than 1) and the __format argument isn't a trivially simple format string, and/or
     *     - the fourth argument is a value other than __BOS_UNKNOWN (i.e. the size of the destination object (__s) is known at
     *       compile time).
     * Otherwise, it resolves to a call to the regular (unfortified) vsnprintf function or a compatible but more performant
     * alternative. __vsnprintf_chk causes __fortify_fail_fmt_n to be invoked if the third argument (__flag) is nonzero and the
     * __format argument contains the n conversion specifier (e.g. "%n"), or calls __fortify_fail_overflow_dst if the __size
     * argument is greater than the size of the destination object (__s) determined at compile time. */
    return __builtin___vsnprintf_chk(__s, __size, __NTO_FORTIFY_LEVEL - 1, __bos_default(__s), __format, __arg);
}

extern __FORTIFY_FUNCTION int vsprintf(char * const __s, const char * const __format, __NTO_va_list __arg)
{
    /* Leverage the compiler's built-in __vsprintf_chk function which resolves to a call to the __vsprintf_chk function when:
     *     - the second argument is a nonzero value (i.e. the _FORTIFY_SOURCE feature test macro has been defined with a value
     *       greater than 1) and the __format argument isn't a trivially simple format string.
     *     - the third argument is a value other than __BOS_UNKNOWN (i.e. the size of the destination object (__s) is known at
     *       compile time).
     * Otherwise, it resolves to a call to the regular (unfortified) vsprintf function or a compatible but more performant
     * alternative. __vsprintf_chk causes __fortify_fail_fmt_n to be invoked if the second argument (__flag) is nonzero and the
     * __format argument contains the n conversion specifier (e.g. "%n"), or calls __fortify_fail_overflow_dst if the length of the
     * formatted string including the terminating NUL character is greater than the size of the destination object (__s) determined
     * at compile time. */
    return __builtin___vsprintf_chk(__s, __NTO_FORTIFY_LEVEL - 1, __bos_default(__s), __format, __arg);
}

#if !defined(__EXT_ANSIC_201112) && ( __cplusplus - 0 <= 201103L )
extern __FORTIFY_FUNCTION char *gets(char * const __s)
{
    /* If the size of the destination object (__s) is known at compile time, call __gets_chk instead of the regular (unfortified)
     * gets function. __gets_chk calls __fortify_fail_overflow_dst if the length of the NUL-terminated string read from standard
     * input is greater than the size of the destination object (__s) determined at compile time. */
    if ( __bos_default(__s) != __BOS_UNKNOWN ) {
        return __gets_chk(__s, __bos_default(__s));
    } else {
        return __gets_alias(__s);
    }
}
#endif /* #if !defined(__EXT_ANSIC_201112) && ( __cplusplus - 0 <= 201103L ) */

#if defined(__EXT_QNX)
#ifdef __bvap
extern __FORTIFY_FUNCTION int asprintf(char ** const __strp, const char * const __fmt, ...)
{
/* The format attribute is specified in the prototype for this function, so the
 * compiler will have already applied -Wformat checks. Silence the irrelevant
 * instances of -Wformat-nonliteral in the calls below. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    /* If __NTO_FORTIFY_LEVEL is greater than 1, call __asprintf_chk instead of the regular (unfortified) asprintf function.
     * __asprintf_chk causes __fortify_fail_fmt_n to be invoked if the second argument (__flag) is nonzero and the __fmt argument is
     * a format string containing the n conversion specifier (e.g. "%n"). */
    if ( __NTO_FORTIFY_LEVEL > 1 ) {
        return __asprintf_chk(__strp, __NTO_FORTIFY_LEVEL - 1, __fmt, __bvap);
    } else {
        return __asprintf_alias(__strp, __fmt, __bvap);
    }
#pragma GCC diagnostic pop
}
#endif /* #ifdef __bvap */

extern __FORTIFY_FUNCTION int vasprintf(char ** const __strp, const char * const __fmt, __NTO_va_list __arg)
{
    /* If __NTO_FORTIFY_LEVEL is greater than 1, call __vasprintf_chk instead of the regular (unfortified) vasprintf function.
     * __vasprintf_chk causes __fortify_fail_fmt_n to be invoked if the second argument (__flag) is nonzero and the __fmt argument
     * is a format string containing the n conversion specifier (e.g. "%n"). */
    if ( __NTO_FORTIFY_LEVEL > 1 ) {
        return __vasprintf_chk(__strp, __NTO_FORTIFY_LEVEL - 1, __fmt, __arg);
    } else {
        return __vasprintf_alias(__strp, __fmt, __arg);
    }
}
#endif /* #if defined(__EXT_QNX) */

#if defined(__EXT_POSIX1_200809)
#ifdef __bvap
extern __FORTIFY_FUNCTION int dprintf(const int __fildes, const char * const _Restrict __format, ...)
{
/* The format attribute is specified in the prototype for this function, so the
 * compiler will have already applied -Wformat checks. Silence the irrelevant
 * instances of -Wformat-nonliteral in the calls below. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    /* If __NTO_FORTIFY_LEVEL is greater than 1, call __dprintf_chk instead of the regular (unfortified) dprintf function.
     * __dprintf_chk causes __fortify_fail_fmt_n to be invoked if the second argument (__flag) is nonzero and the __format argument
     * is a format string containing the n conversion specifier (e.g. "%n"). */
    if ( __NTO_FORTIFY_LEVEL > 1 ) {
        return __dprintf_chk(__fildes, __NTO_FORTIFY_LEVEL - 1, __format, __bvap);
    } else {
        return __dprintf_alias(__fildes, __format, __bvap);
    }
#pragma GCC diagnostic pop
}
#endif /* #ifdef __bvap */

extern __FORTIFY_FUNCTION ssize_t getdelim(
        char      ** const __lineptr,
        size_t     * const __lenptr,
        const int          __delimiter,
        FILE       * const __stream)
{
    if ( __lenptr != NULL ) {
        /* No need to check for __lineptr == NULL as *__lineptr is never evaluated. It's only used as an argument to
         * __builtin_object_size and as an operand of sizeof. */
        __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, *__lineptr, *__lenptr, 1, __fortify_fail_overflow_dst_diag_getdelim);
    }
    return __getdelim_alias(__lineptr, __lenptr, __delimiter, __stream);
}

extern __FORTIFY_FUNCTION ssize_t getline(char ** const __lineptr, size_t * const __lenptr, FILE * const __stream)
{
    if ( __lenptr != NULL ) {
        /* No need to check for __lineptr == NULL as *__lineptr is never evaluated. It's only used as an argument to
         * __builtin_object_size and as an operand of sizeof. */
        __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, *__lineptr, *__lenptr, 1, __fortify_fail_overflow_dst_diag_getline);
    }
    return __getline_alias(__lineptr, __lenptr, __stream);
}

extern __FORTIFY_FUNCTION int vdprintf(const int __fildes, const char * const _Restrict __format, __NTO_va_list __arg)
{
    /* If __NTO_FORTIFY_LEVEL is greater than 1, call __vdprintf_chk instead of the regular (unfortified) vdprintf function.
     * __vdprintf_chk causes __fortify_fail_fmt_n to be invoked if the second argument (__flag) is nonzero and the __format argument
     * is a format string containing the n conversion specifier (e.g. "%n"). */
    if ( __NTO_FORTIFY_LEVEL > 1 ) {
        return __vdprintf_chk(__fildes, __NTO_FORTIFY_LEVEL - 1, __format, __arg);
    } else {
        return __vdprintf_alias(__fildes, __format, __arg);
    }
}
#endif /* #if defined(__EXT_POSIX1_200809) */

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _STDIO_CHK_H_INCLUDED */
