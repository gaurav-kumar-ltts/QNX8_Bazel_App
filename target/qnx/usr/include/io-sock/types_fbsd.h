/*
 * $QNXLicenseC:
 * Copyright 2020, QNX Software Systems. All Rights Reserved.
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

#ifndef _TYPES_FBSD_H_
#define _TYPES_FBSD_H_

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/param.h>

#define _INT8_T_DECLARED
#define _INT16_T_DECLARED
#define _INT32_T_DECLARED
#define _INT64_T_DECLARED
#define _UINT8_T_DECLARED
#define _UINT16_T_DECLARED
#define _UINT32_T_DECLARED
#define _UINT64_T_DECLARED
#define _INTPTR_T_DECLARED
#define _BLKSIZE_T_DECLARED
#define _BLKCNT_T_DECLARED
#define _CLOCK_T_DECLARED
#define _CLOCKID_T_DECLARED
#define _DEV_T_DECLARED
#define _FSBLKCNT_T_DECLARED
#define _GID_T_DECLARED
#define _ID_T_DECLARED
#define _INO_T_DECLARED
#define _KEY_T_DECLARED
#define _MODE_T_DECLARED
#define _NLINK_T_DECLARED
#define _OFF_T_DECLARED
#define _PID_T_DECLARED
#define _SIZE_T_DECLARED
#define _SSIZE_T_DECLARED
#define _SUSECONDS_T_DECLARED
#define _TIME_T_DECLARED
#define _TIMER_T_DECLARED
#define _UID_T_DECLARED
#define _USECONDS_T_DECLARED

typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;

#ifndef _U_INT8_T_DEFINED
#define _U_INT8_T_DEFINED
typedef _Uint8t         u_int8_t;
#endif
#ifndef _U_INT16_T_DEFINED
#define _U_INT16_T_DEFINED
typedef _Uint16t        u_int16_t;
#endif
#ifndef _U_INT32_T_DEFINED
#define _U_INT32_T_DEFINED
typedef _Uint32t        u_int32_t;
#endif
#ifndef _U_INT64_T_DEFINED
#define _U_INT64_T_DEFINED
typedef _Uint64t        u_int64_t;
#endif

typedef _Uint8t         __uint8_t;
typedef _Uint16t        __uint16_t;
typedef _Uint32t        __uint32_t;
typedef _Uint64t        __uint64_t;

typedef _Uint64t        u_quad_t;
typedef _Uint64t	kpaddr_t;
typedef _Uint64t	kvaddr_t;
typedef _Uint64t	ksize_t;
typedef _Int64t		kssize_t;

typedef	__uint8_t	__sa_family_t;
typedef	__uint32_t	__socklen_t;

typedef	const char *	c_caddr_t;	/* core address, pointer to const */

#define	__packed	__attribute__((__packed__))
#define	__aligned(x)	__attribute__((__aligned__(x)))

#define	__POSIX_VISIBLE		202405
#define	__XSI_VISIBLE		800
#define	__BSD_VISIBLE		1
#define	__ISO_C_VISIBLE		2023
#define	__EXT1_VISIBLE		1

#ifdef __FBSDID
#undef __FBSDID
#endif
#define __FBSDID(s)	/* nothing */

#if defined(__X86_64__)
typedef _Int64t		__register_t;
typedef _Uint64t	__uintptr_t;
#define	_ALIGNBYTES	(sizeof(__register_t) - 1)
#define _ALIGN(p)	(((__uintptr_t)(p) + _ALIGNBYTES) & ~_ALIGNBYTES)
#elif defined(__aarch64__)
#define	_ALIGNBYTES	(sizeof(long long) - 1)
#define	_ALIGN(p)	(((u_long)(p) + _ALIGNBYTES) & ~_ALIGNBYTES)
#else
#error _ALIGN not defined for CPU
#endif

#endif /* !_TYPES_FBSD_H_ */
