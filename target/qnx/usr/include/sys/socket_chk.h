/*
 * Copyright (c) 2021-2022, QNX Software Systems. All Rights Reserved.
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

#ifndef _SYS_SOCKET_H_
#error <sys/socket_chk.h> should not be included directly.
#endif

#ifndef __SOCKET_CHK_H_INCLUDED
#define __SOCKET_CHK_H_INCLUDED

#include <fortify.h>

/* Check for prerequisite macros */
#if defined(__NTO_FORTIFY_LEVEL) && defined(__FORTIFY_CHK_OVERFLOW_DST) && defined(__bos_default) && \
        defined(__BOS_TYPE_DEFAULT) && defined(__BOS_TYPE_OUTER) && defined(__BOS_UNKNOWN)

__BEGIN_DECLS

#ifndef _KERNEL

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_accept,
        __fortify_fail_overflow_dst,
        "argument 3 of 'accept' references a value greater than the size of the object referenced by argument 2");
extern int __accept_alias(int __s, struct sockaddr * __restrict __addr, socklen_t * __restrict __addrlen) __ALIASATTR("accept");

#if __BSD_VISIBLE
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_accept4,
        __fortify_fail_overflow_dst,
        "argument 3 of 'accept4' references a value greater than the size of the object referenced by argument 2");
extern int __accept4_alias(int __s, struct sockaddr * __restrict __addr, socklen_t * __restrict __addrlen, int __flags) __ALIASATTR("accept4");
#endif /* #if __BSD_VISIBLE */

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_getpeername,
        __fortify_fail_overflow_dst,
        "argument 3 of 'getpeername' references a value greater than the size of the object referenced by argument 2");
extern int __getpeername_alias(int __s, struct sockaddr * __restrict __name, socklen_t * __restrict __namelen)
        __ALIASATTR("getpeername");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_getsockname,
        __fortify_fail_overflow_dst,
        "argument 3 of 'getsockname' references a value greater than the size of the object referenced by argument 2");
extern int __getsockname_alias(int __s, struct sockaddr * __restrict __name, socklen_t * __restrict __namelen)
        __ALIASATTR("getsockname");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_getsockopt,
        __fortify_fail_overflow_dst,
        "argument 5 of 'getsockopt' references a value greater than the size of the object referenced by argument 4");
extern int __getsockopt_alias(int __s, int __level, int __optname, void * __restrict __optval, socklen_t * __restrict __optlen)
        __ALIASATTR("getsockopt");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_recv,
        __fortify_fail_overflow_dst,
        "argument 3 of 'recv' is greater than the size of the object referenced by argument 2");
extern ssize_t __recv_alias(int __s, void * __buf, size_t __len, int __flags) __ALIASATTR("recv");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_recvfrom_arg_2,
        __fortify_fail_overflow_dst,
        "argument 3 of 'recvfrom' is greater than the size of the object referenced by argument 2");
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_recvfrom_arg_5,
        __fortify_fail_overflow_dst,
        "argument 6 of 'recvfrom' references a value greater than the size of the object referenced by argument 5");
extern ssize_t __recvfrom_alias(
        int                          __fd,
        void            * __restrict __buf,
        size_t                       __len,
        int                          __flags,
        struct sockaddr * __restrict __from,
        socklen_t       * __restrict __fromlen
        ) __ALIASATTR("recvfrom");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_recvmsg_arg_2_msg_name,
        __fortify_fail_overflow_dst,
        "argument 2 of 'recvmsg' references a 'struct msghdr' object with member 'msg_namelen' greater than the size of the object "
                "referenced by member 'msg_name'");
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_recvmsg_arg_2_msg_iov,
        __fortify_fail_overflow_dst,
        "argument 2 of 'recvmsg' references a 'struct msghdr' object with member 'msg_iovlen' greater than the number of "
                "'struct iovec' elements in the object referenced by member 'msg_iov'");
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_recvmsg_arg_2_msg_control,
        __fortify_fail_overflow_dst,
        "argument 2 of 'recvmsg' references a 'struct msghdr' object with member 'msg_controllen' greater than the size of the "
                "object referenced by member 'msg_control'");
extern ssize_t __recvmsg_alias(int __s, struct msghdr *__m, int __flags) __ALIASATTR("recvmsg");

#if __BSD_VISIBLE
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_recvmmsg,
        __fortify_fail_overflow_dst,
        "argument 3 of 'recvmmsg' is greater than the number of 'struct mmsghdr' elements in the object referenced by argument 2");
extern ssize_t __recvmmsg_alias(
        int                                __s,
        struct mmsghdr        * __restrict __mm,
        size_t                             __vlen,
        int                                __flags,
        const struct timespec * __restrict __to
        ) __ALIASATTR("recvmmsg");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_sendmmsg,
        __fortify_fail_overflow_dst,
        "argument 3 of 'sendmmsg' is greater than the number of 'struct mmsghdr' elements in the object referenced by argument 2");
extern ssize_t __sendmmsg_alias(int __s, struct mmsghdr * __restrict __mm, size_t __vlen, int __flags) __ALIASATTR("sendmmsg");
#endif /* #if __BSD_VISIBLE */


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION int accept(
        const int                          __s,
        struct sockaddr * const __restrict __addr,
        socklen_t       * const __restrict __addrlen)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            (_Uint8t *)__addr,
            *__addrlen,
            __addrlen != _NULL,
            __fortify_fail_overflow_dst_diag_accept);
    return __accept_alias(__s, __addr, __addrlen);
}

#if __BSD_VISIBLE
extern __FORTIFY_FUNCTION int accept4(
        const int                          __s,
        struct sockaddr * const __restrict __addr,
        socklen_t       * const __restrict __addrlen,
        const int                          __flags)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            (_Uint8t *)__addr,
            *__addrlen,
            __addrlen != _NULL,
            __fortify_fail_overflow_dst_diag_accept4);
    return __accept4_alias(__s, __addr, __addrlen, __flags);
}
#endif /* #if __BSD_VISIBLE */

extern __FORTIFY_FUNCTION int getpeername(
        const int                          __s,
        struct sockaddr * const __restrict __name,
        socklen_t       * const __restrict __namelen)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            (_Uint8t *)__name,
            *__namelen,
            __namelen != _NULL,
            __fortify_fail_overflow_dst_diag_getpeername);
    return __getpeername_alias(__s, __name, __namelen);
}

extern __FORTIFY_FUNCTION int getsockname(
        const int                          __s,
        struct sockaddr * const __restrict __name,
        socklen_t       * const __restrict __namelen)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            (_Uint8t *)__name,
            *__namelen,
            __namelen != _NULL,
            __fortify_fail_overflow_dst_diag_getsockname);
    return __getsockname_alias(__s, __name, __namelen);
}

extern __FORTIFY_FUNCTION int getsockopt(
        const int                    __s,
        const int                    __level,
        const int                    __optname,
        void      * const __restrict __optval,
        socklen_t * const __restrict __optlen)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            (_Uint8t *)__optval,
            *__optlen,
            __optlen != _NULL,
            __fortify_fail_overflow_dst_diag_getsockopt);
    return __getsockopt_alias(__s, __level, __optname, __optval, __optlen);
}

extern __FORTIFY_FUNCTION ssize_t recv(const int __s, void * const __buf, const size_t __len, const int __flags)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__buf, __len, 1, __fortify_fail_overflow_dst_diag_recv);
    return __recv_alias(__s, __buf, __len, __flags);
}

extern __FORTIFY_FUNCTION ssize_t recvfrom(
        const int                          __fd,
        void            * const __restrict __buf,
        const size_t                       __len,
        const int                          __flags,
        struct sockaddr * const __restrict __from,
        socklen_t       * const __restrict __fromlen)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__buf, __len, 1, __fortify_fail_overflow_dst_diag_recvfrom_arg_2);
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            (_Uint8t *)__from,
            *__fromlen,
            __fromlen != _NULL,
            __fortify_fail_overflow_dst_diag_recvfrom_arg_5);
    return __recvfrom_alias(__fd, __buf, __len, __flags, __from, __fromlen);
}

extern __FORTIFY_FUNCTION ssize_t recvmsg(const int __s, struct msghdr * const __m, const int __flags)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __m->msg_iov[0], so declare a complete struct iovec local to this block. A cast is needed to
     * convert __m->msg_iov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete,
     * block-scoped struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            (_Uint8t *)__m->msg_name,
            __m->msg_namelen,
            1,
            __fortify_fail_overflow_dst_diag_recvmsg_arg_2_msg_name);
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (struct iovec *)__m->msg_iov,
            (unsigned int)__m->msg_iovlen,
            __m->msg_iovlen > 0,
            __fortify_fail_overflow_dst_diag_recvmsg_arg_2_msg_iov);
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            (_Uint8t *)__m->msg_control,
            __m->msg_controllen,
            1,
            __fortify_fail_overflow_dst_diag_recvmsg_arg_2_msg_control);
    return __recvmsg_alias(__s, __m, __flags);
}

#if __BSD_VISIBLE
extern __FORTIFY_FUNCTION ssize_t recvmmsg(
        const int                                __s,
        struct mmsghdr        * const __restrict __mm,
        const size_t                             __vlen,
        const int                                __flags,
        const struct timespec * const __restrict __to)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __mm, __vlen, 1, __fortify_fail_overflow_dst_diag_recvmmsg);
    return __recvmmsg_alias(__s, __mm, __vlen, __flags, __to);
}

extern __FORTIFY_FUNCTION ssize_t sendmmsg(
        const int                         __s,
        struct mmsghdr * const __restrict __mm,
        const size_t                      __vlen,
        const int                         __flags)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_DEFAULT, __mm, __vlen, 1, __fortify_fail_overflow_dst_diag_sendmmsg);
    return __sendmmsg_alias(__s, __mm, __vlen, __flags);
}
#endif /* #if __BSD_VISIBLE */

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

#endif /* #ifndef _KERNEL */

__END_DECLS

#endif /* #if defined(__NTO_FORTIFY_LEVEL) && ... */

#endif /* #ifndef __SOCKET_CHK_H_INCLUDED */
