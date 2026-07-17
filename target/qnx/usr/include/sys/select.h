/*
 * $QNXLicenseC:
 * Copyright 2007-2020, QNX Software Systems. All Rights Reserved.
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



/*
 *  sys/select.h
 *

 */

#ifndef __SELECT_H_INCLUDED
#define __SELECT_H_INCLUDED

#ifndef _LIMITS_H_INCLUDED
#include <limits.h>
#endif

#ifndef _SYS_TIME_H_
#include <sys/time.h>
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

typedef int	__fd_mask;

#define __NFDBITS       ((int)(sizeof(__fd_mask) * CHAR_BIT))

#ifndef FD_SETSIZE
 #define FD_SETSIZE 256
#endif

typedef struct fd_set {
    __fd_mask fds_bits[(FD_SETSIZE + __NFDBITS - 1) / __NFDBITS];
} fd_set;

#if defined(__TIMESPEC)
__TIMESPEC;
#undef __TIMESPEC
#endif

#if defined(__SIGSET_T)
typedef __SIGSET_T  sigset_t;
#undef __SIGSET_T
#endif

#define FD_CLR(fd, p)   __fd_clr((fd), (p))

#define FD_ISSET(fd, p) __fd_isset((fd), (p))

#define FD_SET(fd, p)   __fd_set((fd), (p))

#define FD_ZERO(p)      __fd_zero(p)


__BEGIN_DECLS
struct timeval;

static __ALWAYS_INLINE __ARTIFICIAL void __fd_clr(const int __fd, fd_set * const __fds)
{
    __fds->fds_bits[__fd / __NFDBITS] &= ~(1 << (__fd % __NFDBITS));
}

static __ALWAYS_INLINE __ARTIFICIAL int __fd_isset(const int __fd, const fd_set * const __fds)
{
    return __fds->fds_bits[__fd / __NFDBITS] & (1 << (__fd % __NFDBITS));
}

static __ALWAYS_INLINE __ARTIFICIAL void __fd_set(const int __fd, fd_set * const __fds)
{
    __fds->fds_bits[__fd / __NFDBITS] |= (1 << (__fd % __NFDBITS));
}

static __ALWAYS_INLINE __ARTIFICIAL void __fd_zero(fd_set * const __fds)
{
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
    (void)__builtin_memset(__fds, 0, sizeof(*__fds));
#else
# error not configured for system
#endif
}

extern int select(int __nfds, fd_set * __restrict __readfds,
				  fd_set * __restrict __writefds,
				  fd_set * __restrict __exceptfds,
				  struct timeval * __restrict __timeout);
extern int pselect(int __nfds, fd_set * __restrict __readfds,
				   fd_set * __restrict __writefds,
				   fd_set * __restrict __exceptfds,
				   const struct timespec * __restrict __timeout,
				   const sigset_t * __restrict __sigmask);

#if defined(__EXT_UNIX_MISC)
typedef __fd_mask	fd_mask;
#define NFDBITS		__NFDBITS
#endif

/* FD_ZERO is now implemented as a call to __builtin_memset rather than memset, so the declarations of size_t and memset below are
 * no longer necessary. They are maintained here for backwards compatibility. */
#ifndef __MEMSET_DEFINED
#define __MEMSET_DEFINED

#if defined(__SIZE_T)
typedef __SIZE_T	size_t;
#undef __SIZE_T
#endif

extern void *memset( void *__s, int __c, size_t __n );

#endif /* #ifndef __MEMSET_DEFINED */

__END_DECLS

#if __NTO_FORTIFY_LEVEL > 0
#include <sys/select_chk.h>
#endif

#endif
