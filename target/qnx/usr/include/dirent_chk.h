/*
 * Copyright (c) 2020-2021, QNX Software Systems. All Rights Reserved.
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

#ifndef _DIRENT_H_INCLUDED
#error <dirent_chk.h> should not be included directly.
#endif

#ifndef _DIRENT_CHK_H_INCLUDED
#define _DIRENT_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

/* Same value as NAME_MAX in limits.h */
#define _DIRENT_CHK_H_NAME_MAX   511

#if defined(__EXT_POSIX1_199506)
extern int __readdir_r_chk(DIR *__dirp, struct dirent *__entry, struct dirent **__result, _Sizet __osize)
        __ALIAS64("__readdir64_r_chk");
extern int __readdir_r_chk_diag(DIR *__dirp, struct dirent *__entry, struct dirent **__result, _Sizet __osize)
        __ALIAS64ELSE("__readdir64_r_chk", "__readdir_r_chk")
        __FORTIFY_FAIL_DIAG_ATTRIBUTE(
                "argument 2 of 'readdir_r' references an object with fewer than 'NAME_MAX' + 1 bytes for member 'd_name'");
extern int __readdir_r_alias(DIR *__dirp, struct dirent *__entry, struct dirent **__result)
        __ALIAS64ELSE("readdir64_r", "readdir_r");
#endif /* #if defined(__EXT_POSIX1_199506) */

#if defined(__EXT_LF64SRC)
extern int __readdir64_r_chk(DIR *__dirp, struct dirent64 *__entry, struct dirent64 **__result, _Sizet __osize)
        __ALIASOFF("__readdir_r_chk");
extern int __readdir64_r_chk_diag(DIR *__dirp, struct dirent64 *__entry, struct dirent64 **__result, _Sizet __osize)
        __ALIASOFFELSE("__readdir_r_chk", "__readdir64_r_chk")
        __FORTIFY_FAIL_DIAG_ATTRIBUTE(
                "argument 2 of 'readdir64_r' references an object with fewer than 'NAME_MAX' + 1 bytes for member 'd_name'");
extern int __readdir64_r_alias(DIR *__dirp, struct dirent64 *__entry, struct dirent64 **__result)
        __ALIASOFFELSE("readdir_r", "readdir64_r");
#endif /* #ifdef __EXT_LF64SRC */

#if defined(__EXT_QNX)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag__readdir_r,
        __fortify_fail_overflow_dst,
        "argument 4 of '_readdir_r' is greater than the size of the object referenced by argument 2");
extern int ___readdir_r_alias(DIR *__dirp, struct dirent *__entry, struct dirent **__result, unsigned __bufsize)
        __ALIAS64ELSE("_readdir64_r", "_readdir_r");

#if defined(__EXT_LF64SRC)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag__readdir64_r,
        __fortify_fail_overflow_dst,
        "argument 4 of '_readdir64_r' is greater than the size of the object referenced by argument 2");
extern int ___readdir64_r_alias(DIR *__dirp, struct dirent64 *__entry, struct dirent64 **__result, unsigned __bufsize)
        __ALIASOFFELSE("_readdir_r", "_readdir64_r");
#endif /* #ifdef __EXT_LF64SRC */
#endif /* #if defined(__EXT_QNX) */


#if __NTO_FORTIFY_LEVEL > 0

#if defined(__EXT_POSIX1_199506)
extern __FORTIFY_FUNCTION int readdir_r(DIR * const __dirp, struct dirent * const __entry, struct dirent ** const __result)
{
    /* Call the checked version of the readdir_r function if the size of the destination object (__entry) is known at compile
     * time */
    if ( __bos_outer(__entry) != __BOS_UNKNOWN ) {
        if ( __bos_outer(__entry) < (__builtin_offsetof(struct dirent, d_name) +
                (size_t)_DIRENT_CHK_H_NAME_MAX + 1U) ) {
            return __readdir_r_chk_diag(
                    __dirp,
                    __entry,
                    __result,
                    __bos_outer(__entry));
        } else {
            return __readdir_r_chk(
                    __dirp,
                    __entry,
                    __result,
                    __bos_outer(__entry));
        }
    } else {
        return __readdir_r_alias(__dirp, __entry, __result);
    }
}
#endif /* #if defined(__EXT_POSIX1_199506) */

#if defined(__EXT_LF64SRC)
extern __FORTIFY_FUNCTION int readdir64_r(DIR * const __dirp, struct dirent64 * const __entry, struct dirent64 ** const __result)
{
    /* Call the checked version of the readdir64_r function if the size of the destination object (__entry) is known at compile
     * time */
    if ( __bos_outer(__entry) != __BOS_UNKNOWN ) {
        if ( __bos_outer(__entry) <
                (__builtin_offsetof(struct dirent64, d_name) +
                        (size_t)_DIRENT_CHK_H_NAME_MAX + 1U) ) {
            return __readdir64_r_chk_diag(
                    __dirp,
                    __entry,
                    __result,
                    __bos_outer(__entry));
        } else {
            return __readdir64_r_chk(
                    __dirp,
                    __entry,
                    __result,
                    __bos_outer(__entry));
        }
    } else {
        return __readdir64_r_alias(__dirp, __entry, __result);
    }
}
#endif /* #if defined(__EXT_LF64SRC) */

#if defined(__EXT_QNX)
extern __FORTIFY_FUNCTION int _readdir_r(
        DIR             * const __dirp,
        struct dirent   * const __entry,
        struct dirent  ** const __result,
        const unsigned          __bufsize)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__entry, __bufsize, 1, __fortify_fail_overflow_dst_diag__readdir_r);
    return ___readdir_r_alias(__dirp, __entry, __result, __bufsize);
}

#if defined(__EXT_LF64SRC)
extern __FORTIFY_FUNCTION int _readdir64_r(
        DIR              * const __dirp,
        struct dirent64  * const __entry,
        struct dirent64 ** const __result,
        const unsigned           __bufsize)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__entry, __bufsize, 1, __fortify_fail_overflow_dst_diag__readdir64_r);
    return ___readdir64_r_alias(__dirp, __entry, __result, __bufsize);
}
#endif /* #if defined(__EXT_LF64SRC) */
#endif /* #if defined(__EXT_QNX) */

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _DIRENT_CHK_H_INCLUDED */
