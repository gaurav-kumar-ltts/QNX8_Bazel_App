/*
 * $QNXLicenseC:
 * Copyright 2018-2021, QNX Software Systems. All Rights Reserved.
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

#ifndef _FCNTL_H_INCLUDED
#error <fcntl_chk.h> should not be included directly.
#endif

#ifndef _FCNTL_CHK_H_INCLUDED
#define _FCNTL_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

#ifdef __bvap

#ifdef __EXT_LF64SRC
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_extra_arg_diag_open64,
        __fortify_fail_extra_arg,
        "more than 3 arguments specified to 'open64'");
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_missing_arg_diag_open64,
        __fortify_fail_missing_arg,
        "argument 2 of 'open64' includes the 'O_CREAT' flag, but fewer than 3 arguments specified");
extern int __open64_alias(const char *__path, int __oflag, ...) __ALIASOFFELSE("open", "open64");
#endif /* #ifdef __EXT_LF64SRC */

#if defined(__EXT_POSIX1_198808)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_extra_arg_diag_open,
        __fortify_fail_extra_arg,
        "more than 3 arguments specified to 'open'");
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_missing_arg_diag_open,
        __fortify_fail_missing_arg,
        "argument 2 of 'open' includes the 'O_CREAT' flag, but fewer than 3 arguments specified");
extern int __open_alias(const char *__path, int __oflag, ...) __ALIAS64ELSE("open64", "open");
#endif

#if defined(__EXT_POSIX1_200809)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_extra_arg_diag_openat,
        __fortify_fail_extra_arg,
        "more than 4 arguments specified to 'openat'");
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_missing_arg_diag_openat,
        __fortify_fail_missing_arg,
        "argument 3 of 'openat' includes the 'O_CREAT' flag, but fewer than 4 arguments specified");
extern int __openat_alias(int __fd, const char *__path, int __oflag, ...) __ALIASATTR("openat");
#endif

#if defined(__EXT_PCDOS)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_extra_arg_diag_sopen,
        __fortify_fail_extra_arg,
        "more than 4 arguments specified to 'sopen'");
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_missing_arg_diag_sopen,
        __fortify_fail_missing_arg,
        "argument 2 of 'sopen' includes the 'O_CREAT' flag, but fewer than 4 arguments specified");
extern int __sopen_alias(const char *__path, int __oflag, int __share, ...) __ALIASATTR("sopen");
#endif

#endif /* #ifdef __bvap */


#if __NTO_FORTIFY_LEVEL > 0

#ifdef __bvap

#ifdef __EXT_LF64SRC
extern __FORTIFY_FUNCTION int open64(const char *__path, int __oflag, ...)
{
    /* Fail if the caller specified more than the maximum number of arguments recognized by the open64 function, as the caller may
     * have specified the __mode argument in the wrong place */
    if ( __bvap_len > 1 ) {
        __fortify_fail_extra_arg_diag_open64();
    /* When the __oflag argument includes O_CREAT, an additional __mode argument is required. Fail if the caller didn't specify
     * it. Also emit an error/warning if the __oflag argument is known to be constant at compile time. */
    } else if ( __bvap_len < 1 ) {
        __FORTIFY_CHK(
                __oflag & O_CREAT,
                (__oflag & O_CREAT) != 0,
                __fortify_fail_missing_arg_diag_open64,
                __fortify_fail_missing_arg);
    } else {
        /* A __mode argument was specified. It's required when the __oflag argument includes O_CREAT and ignored otherwise. */
    }
    return __open64_alias(__path, __oflag, __bvap);
}
#endif

#if defined(__EXT_POSIX1_198808)
extern __FORTIFY_FUNCTION int open(const char *__path, int __oflag, ...)
{
    /* Fail if the caller specified more than the maximum number of arguments recognized by the open function, as the caller may
     * have specified the __mode argument in the wrong place */
    if ( __bvap_len > 1 ) {
        __fortify_fail_extra_arg_diag_open();
    /* When the __oflag argument includes O_CREAT, an additional __mode argument is required. Fail if the caller didn't specify
     * it. Also emit an error/warning if the __oflag argument is known to be constant at compile time. */
    } else if ( __bvap_len < 1 ) {
        __FORTIFY_CHK(
                __oflag & O_CREAT,
                (__oflag & O_CREAT) != 0,
                __fortify_fail_missing_arg_diag_open,
                __fortify_fail_missing_arg);
    } else {
        /* A __mode argument was specified. It's required when the __oflag argument includes O_CREAT and ignored otherwise. */
    }
    return __open_alias(__path, __oflag, __bvap);
}
#endif

#if defined(__EXT_POSIX1_200809)
extern __FORTIFY_FUNCTION int openat(int __fd, const char *__path, int __oflag, ...)
{
    /* Fail if the caller specified more than the maximum number of arguments recognized by the openat function, as the caller may
     * have specified the __mode argument in the wrong place */
    if ( __bvap_len > 1 ) {
        __fortify_fail_extra_arg_diag_openat();
    /* When the __oflag argument includes O_CREAT, an additional __mode argument is required. Fail if the caller didn't specify
     * it. Also emit an error/warning if the __oflag argument is known to be constant at compile time. */
    } else if ( __bvap_len < 1 ) {
        __FORTIFY_CHK(
                __oflag & O_CREAT,
                (__oflag & O_CREAT) != 0,
                __fortify_fail_missing_arg_diag_openat,
                __fortify_fail_missing_arg);
    } else {
        /* A __mode argument was specified. It's required when the __oflag argument includes O_CREAT and ignored otherwise. */
    }
    return __openat_alias(__fd, __path, __oflag, __bvap);
}
#endif

#if defined(__EXT_PCDOS)
extern __FORTIFY_FUNCTION int sopen(const char *__path, int __oflag, int __share, ...)
{
    /* Fail if the caller specified more than the maximum number of arguments recognized by the sopen function, as the caller may
     * have specified the __mode argument in the wrong place */
    if ( __bvap_len > 1 ) {
        __fortify_fail_extra_arg_diag_sopen();
    /* When the __oflag argument includes O_CREAT, an additional __mode argument is required. Fail if the caller didn't specify
     * it. Also emit an error/warning if the __oflag argument is known to be constant at compile time. */
    } else if ( __bvap_len < 1 ) {
        __FORTIFY_CHK(
                __oflag & O_CREAT,
                (__oflag & O_CREAT) != 0,
                __fortify_fail_missing_arg_diag_sopen,
                __fortify_fail_missing_arg);
    } else {
        /* A __mode argument was specified. It's required when the __oflag argument includes O_CREAT and ignored otherwise. */
    }
    return __sopen_alias(__path, __oflag, __share, __bvap);
}
#endif

#endif /* #ifdef __bvap */

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _FCNTL_CHK_H_INCLUDED */
