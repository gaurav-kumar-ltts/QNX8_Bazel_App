/*
 * Copyright (c) 2019-2023, QNX Software Systems. All Rights Reserved.
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

#ifndef _UNISTD_H_INCLUDED
#error <unistd_chk.h> should not be included directly.
#endif

#ifndef _UNISTD_CHK_H_INCLUDED
#define _UNISTD_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

/* Same value as PATH_MAX in limits.h */
#define _UNISTD_CHK_H_PATH_MAX   1024

/* Same value as SSIZE_MAX in limits.h */
#define _UNISTD_CHK_H_SSIZE_MAX  ((ssize_t)((size_t)-1 >> 1))

#if defined(__EXT_POSIX1_198808)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_confstr,
        __fortify_fail_overflow_dst,
        "argument 3 of 'confstr' is greater than the size of the object referenced by argument 2");
extern size_t __confstr_alias(int __name, char *__buf, size_t __len) __ALIASATTR("confstr");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_getcwd,
        __fortify_fail_overflow_dst,
        "argument 2 of 'getcwd' is greater than the size of the object referenced by argument 1");
extern char *__getcwd_alias(char *__buf, size_t __size) __ALIASATTR("getcwd");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_getgroups,
        __fortify_fail_overflow_dst,
        "argument 1 of 'getgroups' is greater than the number of 'gid_t' elements in the object referenced by argument 2");
extern int __getgroups_alias(int __gidsetsize, gid_t __grouplist[]) __ALIASATTR("getgroups");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_pread,
        __fortify_fail_overflow_dst,
        "argument 3 of 'pread' is greater than the size of the object referenced by argument 2");
extern ssize_t __pread_alias(int __filedes, void *__buff, size_t __nbytes, off_t __offset) __ALIAS64ELSE("pread64", "pread");

#ifdef __EXT_LF64SRC
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_pread64,
        __fortify_fail_overflow_dst,
        "argument 3 of 'pread64' is greater than the size of the object referenced by argument 2");
extern ssize_t __pread64_alias(int __filedes, void *__buff, size_t __nbytes, off64_t __offset) __ALIASOFFELSE("pread", "pread64");
#endif /* #ifdef __EXT_LF64SRC */

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_read,
        __fortify_fail_overflow_dst,
        "argument 3 of 'read' is greater than the size of the object referenced by argument 2");
extern ssize_t __read_alias(int __fildes, void *__buffer, size_t __len) __ALIASATTR("read");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_readlink,
        __fortify_fail_overflow_dst,
        "argument 3 of 'readlink' is greater than the size of the object referenced by argument 2");
extern ssize_t __readlink_alias(const char *__path, char *__buf, size_t __bufsiz) __ALIASATTR("readlink");
#endif /* #if defined(__EXT_POSIX1_198808) */

#if defined(__EXT_POSIX1_199506)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_getlogin_r,
        __fortify_fail_overflow_dst,
        "argument 2 of 'getlogin_r' is greater than the size of the object referenced by argument 1");
extern int __getlogin_r_alias(char *__name, size_t __namesize) __ALIASATTR("getlogin_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_ttyname_r,
        __fortify_fail_overflow_dst,
        "argument 3 of 'ttyname_r' is greater than the size of the object referenced by argument 2");
extern int __ttyname_r_alias(int __fildes, char *__buf, size_t __bufsize) __ALIASATTR("ttyname_r");
#endif /* #if defined(__EXT_POSIX1_199506) */

#if defined(__EXT_POSIX1_200809)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_readlinkat,
        __fortify_fail_overflow_dst,
        "argument 4 of 'readlinkat' is greater than the size of the object referenced by argument 3");
extern ssize_t __readlinkat_alias(int __dirfd, const char *__pathname, char *__buf, size_t __bufsize) __ALIASATTR("readlinkat");
#endif /* #if defined(__EXT_POSIX1_200809) */

#if defined(__EXT_UNIX_MISC)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_getgrouplist,
        __fortify_fail_overflow_dst,
        "argument 4 of 'getgrouplist' references a value greater than the number of 'gid_t' elements in the object referenced "
                "by argument 3");
extern int __getgrouplist_alias(const char *__uname, gid_t __agroup, gid_t *__groups, int *__grpcnt) __ALIASATTR("getgrouplist");
#endif /* #if defined(__EXT_UNIX_MISC) */

#if defined(__EXT_XOPEN_EX)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_gethostname,
        __fortify_fail_overflow_dst,
        "argument 2 of 'gethostname' is greater than the size of the object referenced by argument 1");
extern int __gethostname_alias(char *__buffer, size_t __buffer_length) __ALIASATTR("gethostname");

extern char *__getwd_chk(char *__pathname, size_t osize);
extern char *__getwd_chk_diag(char *__pathname, size_t osize) __ALIASATTR("__getwd_chk")
        __FORTIFY_FAIL_DIAG_ATTRIBUTE("argument 1 of 'getwd' references an object smaller than 'PATH_MAX' bytes");
extern char *__getwd_alias(char *__pathname) __ALIASATTR("getwd");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_swab,
        __fortify_fail_overflow_dst,
        "argument 3 of 'swab' is greater than the size of the object referenced by argument 2");
extern void __swab_alias(const void * __restrict __src, void * __restrict __dest, ssize_t __num) __ALIASATTR("swab");
#endif /* #if defined(__EXT_XOPEN_EX) */

#if defined(__EXT_QNX)
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_getdomainname,
        __fortify_fail_overflow_dst,
        "argument 2 of 'getdomainname' is greater than the size of the object referenced by argument 1");
extern int __getdomainname_alias(char *__name, size_t __namelen) __ALIASATTR("getdomainname");

extern int __readblock_chk(int __fd, size_t __blksize, unsigned __blk, int __numblks, void *__buff, size_t __osize);
extern int __readblock_chk_diag(int __fd, size_t __blksize, unsigned __blk, int __numblks, void *__buff, size_t __osize)
        __ALIASATTR("__readblock_chk")
        __FORTIFY_FAIL_DIAG_ATTRIBUTE(
                "the product of arguments 2 and 4 of 'readblock' is greater than the size of the object referenced by argument 5");
extern int __readblock_alias(int __fd, size_t __blksize, unsigned __blk, int __numblks, void *__buff) __ALIASATTR("readblock");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_readcond,
        __fortify_fail_overflow_dst,
        "argument 3 of 'readcond' is greater than the size of the object referenced by argument 2");
extern int __readcond_alias(int __fd, void *__buff, int __nbytes, int __min, int __time, int __timeout) __ALIASATTR("readcond");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_SETIOV,
        __fortify_fail_overflow_dst,
        "argument 3 of 'SETIOV' is greater than the size of the object referenced by argument 2");
#endif /* #if defined(__EXT_QNX) */


#if __NTO_FORTIFY_LEVEL > 0

#if defined(__EXT_POSIX1_198808)
extern __FORTIFY_FUNCTION size_t confstr(const int __name, char * const __buf, const size_t __len)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __buf, __len, 1, __fortify_fail_overflow_dst_diag_confstr);
    return __confstr_alias(__name, __buf, __len);
}

extern __FORTIFY_FUNCTION char *getcwd(char * const __buf, const size_t __size)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __buf, __size, 1, __fortify_fail_overflow_dst_diag_getcwd);
    return __getcwd_alias(__buf, __size);
}

extern __FORTIFY_FUNCTION int getgroups(const int __gidsetsize, gid_t * const __grouplist)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __grouplist,
            (unsigned int)__gidsetsize,
            __gidsetsize > 0,
            __fortify_fail_overflow_dst_diag_getgroups);
    return __getgroups_alias(__gidsetsize, __grouplist);
}

extern __FORTIFY_FUNCTION ssize_t pread(const int __filedes, void * const __buff, const size_t __nbytes, const off_t __offset)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__buff, __nbytes, 1, __fortify_fail_overflow_dst_diag_pread);
    return __pread_alias(__filedes, __buff, __nbytes, __offset);
}

#ifdef __EXT_LF64SRC
extern __FORTIFY_FUNCTION ssize_t pread64(const int __filedes, void * const __buff, const size_t __nbytes, const off64_t __offset)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__buff, __nbytes, 1, __fortify_fail_overflow_dst_diag_pread64);
    return __pread64_alias(__filedes, __buff, __nbytes, __offset);
}
#endif /* #ifdef __EXT_LF64SRC */

extern __FORTIFY_FUNCTION ssize_t read(const int __fildes, void * const __buffer, const size_t __len)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__buffer, __len, 1, __fortify_fail_overflow_dst_diag_read);
    return __read_alias(__fildes, __buffer, __len);
}

extern __FORTIFY_FUNCTION ssize_t readlink(const char * const __path, char * const __buf, const size_t __bufsiz)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __buf, __bufsiz, 1, __fortify_fail_overflow_dst_diag_readlink);
    return __readlink_alias(__path, __buf, __bufsiz);
}
#endif /* #if defined(__EXT_POSIX1_198808) */

#if defined(__EXT_POSIX1_199506)
extern __FORTIFY_FUNCTION int getlogin_r(char * const __name, const size_t __namesize)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __name, __namesize, 1, __fortify_fail_overflow_dst_diag_getlogin_r);
    return __getlogin_r_alias(__name, __namesize);
}

extern __FORTIFY_FUNCTION int ttyname_r(const int __fildes, char * const __buf, const size_t __bufsize)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __buf, __bufsize, 1, __fortify_fail_overflow_dst_diag_ttyname_r);
    return __ttyname_r_alias(__fildes, __buf, __bufsize);
}
#endif /* #if defined(__EXT_POSIX1_199506) */

#if defined(__EXT_POSIX1_200809)
extern __FORTIFY_FUNCTION ssize_t readlinkat(
        const int            __dirfd,
        const char   * const __pathname,
        char         * const __buf,
        const size_t         __bufsize)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __buf, __bufsize, 1, __fortify_fail_overflow_dst_diag_readlinkat);
    return __readlinkat_alias(__dirfd, __pathname, __buf, __bufsize);
}
#endif /* #if defined(__EXT_POSIX1_200809) */

#if defined(__EXT_UNIX_MISC)
extern __FORTIFY_FUNCTION int getgrouplist(
        const char  * const __uname,
        const gid_t         __agroup,
        gid_t       * const __groups,
        int         * const __grpcnt)
{
    /* The real implementation assumes a non-NULL __grpcnt, so we will too */
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __groups,
            (unsigned int)*__grpcnt,
            *__grpcnt > 0,
            __fortify_fail_overflow_dst_diag_getgrouplist);
    return __getgrouplist_alias(__uname, __agroup, __groups, __grpcnt);
}
#endif /* #if defined(__EXT_UNIX_MISC) */

#if defined(__EXT_XOPEN_EX)
extern __FORTIFY_FUNCTION int gethostname(char * const __buffer, const size_t __buffer_length)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __buffer, __buffer_length, 1, __fortify_fail_overflow_dst_diag_gethostname);
    return __gethostname_alias(__buffer, __buffer_length);
}

extern __FORTIFY_FUNCTION char *getwd(char * const __pathname)
{
    /* Call the checked version of the getwd function if the length of the destination object (__pathname) is known at compile
     * time */
    if ( __bos_default(__pathname) != __BOS_UNKNOWN ) {
        if ( __bos_default(__pathname) < (size_t)_UNISTD_CHK_H_PATH_MAX ) {
            return __getwd_chk_diag(__pathname, __bos_default(__pathname));
        } else {
            return __getwd_chk(__pathname, __bos_default(__pathname));
        }
    } else {
        return __getwd_alias(__pathname);
    }
}

extern __FORTIFY_FUNCTION void swab(const void * const __restrict __src, void * const __restrict __dest, const ssize_t __num)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            (_Uint8t *)__dest,
            (size_t)__num,
            __num > 0,
            __fortify_fail_overflow_dst_diag_swab);
    __swab_alias(__src, __dest, __num);
}
#endif /* #if defined(__EXT_XOPEN_EX) */

#if defined(__EXT_QNX)
extern __FORTIFY_FUNCTION int getdomainname(char * const __name, const size_t __namelen)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __name, __namelen, 1, __fortify_fail_overflow_dst_diag_getdomainname);
    return __getdomainname_alias(__name, __namelen);
}

extern __FORTIFY_FUNCTION int readblock(
        const int              __fd,
        const size_t           __blksize,
        const unsigned         __blk,
        const int              __numblks,
        void           * const __buff)
{
    /* Call the checked version of the readblock function if the length of the destination object (__buff) is known at compile
     * time */
    if ( __bos_outer(__buff) != __BOS_UNKNOWN ) {
        /* Emit an error/warning if the size to read is valid and invariably exceeds the size of the destination object (__buff) */
        if ( __bconst(__blksize) && __bconst(__numblks) && ( __blksize != 0 ) && ( __numblks > 0 ) &&
                ( (size_t)__numblks <= ((size_t)_UNISTD_CHK_H_SSIZE_MAX / __blksize) ) &&
                ( (__blksize * (size_t)__numblks) > __bos_outer(__buff) ) ) {
            return __readblock_chk_diag(__fd, __blksize, __blk, __numblks, __buff, __bos_outer(__buff));
        } else {
            return __readblock_chk(__fd, __blksize, __blk, __numblks, __buff, __bos_outer(__buff));
        }
    } else {
        return __readblock_alias(__fd, __blksize, __blk, __numblks, __buff);
    }
}

extern __FORTIFY_FUNCTION int readcond(
        const int         __fd,
        void      * const __buff,
        const int         __nbytes,
        const int         __min,
        const int         __time,
        const int         __timeout)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            (_Uint8t *)__buff,
            (unsigned int)__nbytes,
            1,
            __fortify_fail_overflow_dst_diag_readcond);
    return __readcond_alias(__fd, __buff, __nbytes, __min, __time, __timeout);
}

#undef SETIOV
#define SETIOV(__iov, __addr, __len)  (__setiov_chk((__iov), (__addr), (__len)))

static __FORTIFY_FUNCTION void __setiov_chk(iov_t * const __iov, void * const __addr, const size_t __len)
{
    /* Note that while the SETIOV macro and __setiov function don't actually write data to the specified buffer, the iov_t object
     * populated by SETIOV will typically be passed to one of many functions (e.g. writev) that will. The fortified implementations
     * of those functions aren't able to validate the length of a buffer pointed to by an iov_t object, so the validation is
     * performed here. */
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__addr, __len, 1, __fortify_fail_overflow_dst_diag_SETIOV);
    __setiov(__iov, __addr, __len);
}
#endif /* #if defined(__EXT_QNX) */

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef _UNISTD_CHK_H_INCLUDED */
