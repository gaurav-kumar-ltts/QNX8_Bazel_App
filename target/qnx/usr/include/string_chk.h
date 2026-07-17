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

#ifndef _STRING_H_INCLUDED
#error <string_chk.h> should not be included directly.
#endif

#ifndef _STRING_CHK_H_INCLUDED
#define _STRING_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_memcpy,
        __fortify_fail_overflow_dst,
        "argument 3 of 'memcpy' is greater than the size of the object referenced by argument 1");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag___memcpy_isr,
        __fortify_fail_overflow_dst,
        "argument 3 of '__memcpy_isr' is greater than the size of the object referenced by argument 1");
extern void *__memcpy_isr_alias(void *__s1, const void *__s2, size_t __n) __ALIASATTR("__memcpy_isr");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_memmove,
        __fortify_fail_overflow_dst,
        "argument 3 of 'memmove' is greater than the size of the object referenced by argument 1");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_memset,
        __fortify_fail_overflow_dst,
        "argument 3 of 'memset' is greater than the size of the object referenced by argument 1");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag___memset_isr,
        __fortify_fail_overflow_dst,
        "argument 3 of '__memset_isr' is greater than the size of the object referenced by argument 1");
extern void *__memset_isr_alias(void *__s, int __c, size_t __n) __ALIASATTR("__memset_isr");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_stpcpy,
        __fortify_fail_overflow_dst,
        "argument 2 of 'stpcpy' references a string longer than the object referenced by argument 1");
extern char *__stpcpy_chk(char * _Restrict __dst, const char * _Restrict __src, size_t __osize);

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_stpncpy,
        __fortify_fail_overflow_dst,
        "argument 3 of 'stpncpy' is greater than the size of the object referenced by argument 1");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_strcat,
        __fortify_fail_overflow_dst,
        "argument 2 of 'strcat' references a string longer than the object referenced by argument 1");
extern char *__strcat_chk(char *__s1, const char *__s2, size_t __osize);

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_strcpy,
        __fortify_fail_overflow_dst,
        "argument 2 of 'strcpy' references a string longer than the object referenced by argument 1");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag___strcpy_isr,
        __fortify_fail_overflow_dst,
        "argument 2 of '__strcpy_isr' references a string longer than the object referenced by argument 1");
extern char *__strcpy_isr_alias(char *__s1, const char *__s2) __ALIASATTR("__strcpy_isr");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_strlcat,
        __fortify_fail_overflow_dst,
        "argument 3 of 'strlcat' is greater than the size of the object referenced by argument 1");
extern size_t __strlcat_alias(char *__s1, const char *__s2, size_t __n) __ALIASATTR("strlcat");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_strlcpy,
        __fortify_fail_overflow_dst,
        "argument 3 of 'strlcpy' is greater than the size of the object referenced by argument 1");
extern size_t __strlcpy_alias(char *__s1, const char *__s2, size_t __n) __ALIASATTR("strlcpy");

extern char *__strncat_chk(char *__s1, const char *__s2, size_t __n, size_t __osize);
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_strncat,
        __fortify_fail_overflow_dst,
        "argument 3 of 'strncat' is greater than or equal to the size of the object referenced by argument 1");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_strncpy,
        __fortify_fail_overflow_dst,
        "argument 3 of 'strncpy' is greater than the size of the object referenced by argument 1");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_strxfrm,
        __fortify_fail_overflow_dst,
        "argument 3 of 'strxfrm' is greater than the size of the object "
                "referenced by argument 1");
extern size_t __strxfrm_alias(char *__s1, char const *__s2, size_t __n)
        __ALIASATTR("strxfrm");

#if defined(__EXT_POSIX1_200112) || defined(__EXT_XOPEN_EX)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_memccpy,
        __fortify_fail_overflow_dst,
        "argument 4 of 'memccpy' is greater than the size of the object referenced by argument 1");
extern void *__memccpy_alias(void * __restrict __s1, const void * __restrict __s2, int __c, size_t __n) __ALIASATTR("memccpy");
#endif /* #if defined(__EXT_POSIX1_200112) || defined(__EXT_XOPEN_EX) */

#if defined(__EXT_QNX)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_memcpyv,
        __fortify_fail_overflow_dst,
        "argument 2 of 'memcpyv' is negative or greater than the number of 'struct iovec' elements in the object referenced by "
                "argument 1");
extern size_t __memcpyv_alias(
        const struct iovec *__dst,
        int                 __dparts,
        size_t              __doff,
        const struct iovec *__src,
        int                 __sparts,
        size_t              __soff) __ALIASATTR("memcpyv");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_memset_s,
        __fortify_fail_overflow_dst,
        "argument 2 of 'memset_s' is greater than the size of the object referenced by argument 1");
extern errno_t __memset_s_alias(void *__v, rsize_t __smax, int __c, rsize_t __n) __ALIASATTR("memset_s");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_straddstr,
        __fortify_fail_overflow_dst,
        "argument 4 of 'straddstr' references a value greater than the size of the object indirectly referenced by argument 3");
extern int __straddstr_alias(const char *__str, int __len, char **__pbuf, size_t *__pmaxbuf) __ALIASATTR("straddstr");
#endif /* #if defined(__EXT_QNX) */


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION void *memcpy(void *__dst, const void *__src, size_t __nbytes)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__dst, __nbytes, 1, __fortify_fail_overflow_dst_diag_memcpy);
    /* Leverage the compiler's built-in memcpy function, which can potentially be optimized into something more performant than a
     * call to the regular (unfortified) memcpy function */
    return __builtin_memcpy(__dst, __src, __nbytes);
}

extern __FORTIFY_FUNCTION void *__memcpy_isr(void *__s1, const void *__s2, size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__s1, __n, 1, __fortify_fail_overflow_dst_diag___memcpy_isr);
    return __memcpy_isr_alias(__s1, __s2, __n);
}

extern __FORTIFY_FUNCTION void *memmove(void *__s1, const void *__s2, size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__s1, __n, 1, __fortify_fail_overflow_dst_diag_memmove);
    /* Leverage the compiler's built-in memmove function, which can potentially be optimized into something more performant than a
     * call to the regular (unfortified) memmove function */
    return __builtin_memmove(__s1, __s2, __n);
}

extern __FORTIFY_FUNCTION void *memset(void *__s, int __c, size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__s, __n, 1, __fortify_fail_overflow_dst_diag_memset);
    /* Leverage the compiler's built-in memset function, which can potentially be optimized into something more performant than a
     * call to the regular (unfortified) memset function */
    return __builtin_memset(__s, __c, __n);
}

extern __FORTIFY_FUNCTION void *__memset_isr(void *__s, int __c, size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__s, __n, 1, __fortify_fail_overflow_dst_diag___memset_isr);
    return __memset_isr_alias(__s, __c, __n);
}

extern __FORTIFY_FUNCTION char *stpcpy(char * _Restrict __dst, const char * _Restrict __src)
{
    /* Fail and emit an error/warning if the source string (__src) including the NUL terminator is known at compile time to be
     * longer than the destination object (__dst) */
    if ( ( __bos_default(__dst) != __BOS_UNKNOWN ) && __bconst(__builtin_strlen(__src)) &&
            ( __builtin_strlen(__src) >= __bos_default(__dst) ) ) {
        __fortify_fail_overflow_dst_diag_stpcpy();
    }
    /* Leverage the compiler's built-in __stpcpy_chk function which resolves to a call to the __stpcpy_chk function or a compatible
     * but more performant alternative when the third argument is a value other than __BOS_UNKNOWN (i.e. the size of the destination
     * object (__dst) is known at compile time). Otherwise, it resolves to a call to the regular (unfortified) stpcpy function or a
     * compatible but more performant alternative. __stpcpy_chk calls __fortify_fail_overflow_dst if the length of the source string
     * (__src) plus a NUL terminator is greater than the size of the destination object (__dst) determined at compile time. */
    return __builtin___stpcpy_chk(__dst, __src, __bos_default(__dst));
}

extern __FORTIFY_FUNCTION char *stpncpy(char * _Restrict __dst, const char * _Restrict __src, size_t __num)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __dst, __num, 1, __fortify_fail_overflow_dst_diag_stpncpy);
    /* Leverage the compiler's built-in stpncpy function, which can potentially be optimized into something more performant than a
     * call to the regular (unfortified) stpncpy function */
    return __builtin_stpncpy(__dst, __src, __num);
}

extern __FORTIFY_FUNCTION char *strcat(char *__s1, const char *__s2)
{
    /* Fail and emit an error/warning if the source string (__s2) including the NUL terminator is known at compile time to be
     * longer than the destination object (__s1) */
    if ( ( __bos_default(__s1) != __BOS_UNKNOWN ) && __bconst(__builtin_strlen(__s2)) &&
            ( __builtin_strlen(__s2) >= __bos_default(__s1) ) ) {
        __fortify_fail_overflow_dst_diag_strcat();
    }
    /* Leverage the compiler's built-in __strcat_chk function which resolves to a call to the __strcat_chk function or a compatible
     * but more performant alternative when the third argument is a value other than __BOS_UNKNOWN (i.e. the size of the destination
     * object (__s1) is known at compile time). Otherwise, it resolves to a call to the regular (unfortified) strcat function or a
     * compatible but more performant alternative. __strcat_chk calls __fortify_fail_overflow_dst if the length of the concatenated
     * string plus the terminating NUL character is greater than the size of the destination object (__s1) determined at compile
     * time. */
    return __builtin___strcat_chk(__s1, __s2, __bos_default(__s1));
}

extern __FORTIFY_FUNCTION char *strcpy(char *__s1, const char *__s2)
{
    /* Fail if the length of the source string (__s2) including the terminating NUL character is greater than the size of the
     * destination object (__s1) determined at compile time. Also emit an error/warning if the length of the source string (__s2) is
     * known to be constant at compile time. */
    if ( __bos_default(__s1) != __BOS_UNKNOWN ) {

        /* Leverage the compiler's built-in strlen function, which can potentially be optimized into something more performant than
         * a call to the strlen function */
        const size_t __len = __builtin_strlen(__s2);

        __FORTIFY_CHK(__len, __len >= __bos_default(__s1), __fortify_fail_overflow_dst_diag_strcpy, __fortify_fail_overflow_dst);

        /* Since we already know the length of the source string, use memcpy rather than strcpy to perform the copy operation.
         * Leverage the compiler's built-in memcpy function, which can potentially be optimized into something more performant than
         * a call to the regular (unfortified) memcpy function. */
        return (char *)__builtin_memcpy(__s1, __s2, __len + 1);

    /* Otherwise, leverage the compiler's built-in strcpy function, which can potentially be optimized into something more
     * performant than a call to the regular (unfortified) strcpy function */
    } else {
        return __builtin_strcpy(__s1, __s2);
    }
}

extern __FORTIFY_FUNCTION char *__strcpy_isr(char *__s1, const char *__s2)
{
    /* Fail if the length of the source string (__s2) including the terminating NUL character is greater than the size of the
     * destination object (__s1) determined at compile time. Also emit an error/warning if the length of the source string (__s2) is
     * known to be constant at compile time. */
    if ( __bos_default(__s1) != __BOS_UNKNOWN ) {

        const size_t __len = __bconst(__builtin_strlen(__s2)) ? __builtin_strlen(__s2) : __strlen_isr(__s2);

        __FORTIFY_CHK(
                __len,
                __len >= __bos_default(__s1),
                __fortify_fail_overflow_dst_diag___strcpy_isr,
                __fortify_fail_overflow_dst);

        /* Since we already know the length of the source string, use __memcpy_isr rather than __strcpy_isr to perform the copy
         * operation */
        return (char *)__memcpy_isr_alias(__s1, __s2, __len + 1);

    } else {
        return __strcpy_isr_alias(__s1, __s2);
    }
}

extern __FORTIFY_FUNCTION size_t strlcat(char *__s1, const char *__s2, size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __s1, __n, 1, __fortify_fail_overflow_dst_diag_strlcat);
    return __strlcat_alias(__s1, __s2, __n);
}

extern __FORTIFY_FUNCTION size_t strlcpy(char *__s1, const char *__s2, size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __s1, __n, 1, __fortify_fail_overflow_dst_diag_strlcpy);
    return __strlcpy_alias(__s1, __s2, __n);
}

extern __FORTIFY_FUNCTION char *strncat(char *__s1, const char *__s2, size_t __n)
{
    /* Fail and emit an error/warning if the maximum number of characters to append including the terminating NUL character
     * (__n + 1) is greater than the size of the destination object (__s1) determined at compile time */
    if ( ( __bos_default(__s1) != __BOS_UNKNOWN ) && __bconst(__n) && ( __n >= __bos_default(__s1) ) ) {
        __fortify_fail_overflow_dst_diag_strncat();
    }
    /* Leverage the compiler's built-in __strncat_chk function which resolves to a call to the __strncat_chk function or a
     * compatible but more performant alternative when the third argument is a value other than __BOS_UNKNOWN (i.e. the size of the
     * destination object (__s1) is known at compile time). Otherwise, it resolves to a call to the regular (unfortified) strncat
     * function or a compatible but more performant alternative. __strncat_chk calls __fortify_fail_overflow_dst if the length of
     * the concatenated string plus the terminating NUL character is greater than the size of the destination object (__s1)
     * determined at compile time. */
    return __builtin___strncat_chk(__s1, __s2, __n, __bos_default(__s1));
}

extern __FORTIFY_FUNCTION char *strncpy(char *__s1, const char *__s2, size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __s1, __n, 1, __fortify_fail_overflow_dst_diag_strncpy);
    /* Leverage the compiler's built-in strncpy function, which can potentially be optimized into something more performant than a
     * call to the regular (unfortified) strncpy function */
    return __builtin_strncpy(__s1, __s2, __n);
}

extern __FORTIFY_FUNCTION size_t strxfrm(
        char         * const __s1,
        char const   * const __s2,
        size_t const         __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __s1,
            __n,
            1,
            __fortify_fail_overflow_dst_diag_strxfrm);
    return __strxfrm_alias(__s1, __s2, __n);
}

#if defined(__EXT_POSIX1_200112) || defined(__EXT_XOPEN_EX)
extern __FORTIFY_FUNCTION void *memccpy(void * __restrict __s1, const void * __restrict __s2, int __c, size_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__s1, __n, 1, __fortify_fail_overflow_dst_diag_memccpy);
    return __memccpy_alias(__s1, __s2, __c, __n);
}
#endif /* #if defined(__EXT_POSIX1_200112) || defined(__EXT_XOPEN_EX) */

#if defined(__EXT_QNX)
extern __FORTIFY_FUNCTION size_t memcpyv(
        const struct iovec *__dst,
        int                 __dparts,
        size_t              __doff,
        const struct iovec *__src,
        int                 __sparts,
        size_t              __soff)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __dst, (unsigned int)__dparts, 1, __fortify_fail_overflow_dst_diag_memcpyv);
    return __memcpyv_alias(__dst, __dparts, __doff, __src, __sparts, __soff);
}

extern __FORTIFY_FUNCTION errno_t memset_s(void *__v, rsize_t __smax, int __c, rsize_t __n)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__v, __smax, 1, __fortify_fail_overflow_dst_diag_memset_s);
    return __memset_s_alias(__v, __smax, __c, __n);
}

extern __FORTIFY_FUNCTION int straddstr(
        const char  * const __str,
        const int           __len,
        char       ** const __pbuf,
        size_t      * const __pmaxbuf)
{
    if ( __pmaxbuf != NULL ) {
        /* No need to check for __pbuf == NULL as *__pbuf is never evaluated. It's only used as an argument to __builtin_object_size
         * and as an operand of sizeof. */
        __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, *__pbuf, *__pmaxbuf, 1, __fortify_fail_overflow_dst_diag_straddstr);
    }
    return __straddstr_alias(__str, __len, __pbuf, __pmaxbuf);
}
#endif /* #if defined(__EXT_QNX) */

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _STRING_CHK_H_INCLUDED */
