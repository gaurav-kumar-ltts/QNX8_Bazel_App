/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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





#ifndef _NET_NETBYTE_H_INCLUDED
#define _NET_NETBYTE_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifndef _GULLIVER_H_INCLUDED
#include <gulliver.h>
#endif


__BEGIN_DECLS

#ifdef __EXT_BSD
/* libsocket */
uint16_t htobe16(uint16_t);
uint32_t htobe32(uint32_t);
uint64_t htobe64(uint64_t);
uint16_t htole16(uint16_t);
uint32_t htole32(uint32_t);
uint64_t htole64(uint64_t);

uint16_t be16toh(uint16_t);
uint32_t be32toh(uint32_t);
uint64_t be64toh(uint64_t);
uint16_t le16toh(uint16_t);
uint32_t le32toh(uint32_t);
uint64_t le64toh(uint64_t);
#endif
__END_DECLS


#if defined(__LITTLEENDIAN__)
#define __NET_LE16(__x)	((__x))
#define __NET_LE32(__x)	((__x))
#define __NET_LE64(__x)	((__x))


static __inline__ _Uint16t __net_be16 (_Uint16t __x)
	{
#if defined(__CPU_ENDIAN_RET16)
		return	__cpu_endian_ret16(__x);
#else
		return (((__x >> 8) & 0xff) | ((__x & 0xff) << 8));
#endif
	}

#define __NET_BE16(__x) __net_be16(__x)
#define __NET_BSWAP16(__x) __NET_BE16((__x))


static __inline__ _Uint32t __net_be32 (_Uint32t __x)
	{
#if defined(__CPU_ENDIAN_RET32)
		return	__cpu_endian_ret32(__x);
#else
		return (((__x >> 24) & 0xff) | ((__x >> 8) & 0xff00) |
			((__x & 0xff00) << 8) | ((__x & 0xff) << 24));
#endif
	}

#define __NET_BE32(__x) __net_be32(__x)
#define __NET_BSWAP32(__x) __NET_BE32((__x))


static __inline__ _Uint64t __net_be64(_Uint64t __x)
	{
#if defined(__CPU_ENDIAN_RET64)
		return __cpu_endian_ret64(__x);
#else
		return (((__x >> 56) & 0xff) | ((__x >> 40) & 0xff00) |
			((__x >> 24) & 0xff0000) | ((__x >>  8) & 0xff000000) |
			((__x & 0xff000000) <<  8) | ((__x & 0xff0000) << 24) |
			((__x & 0xff00) << 40) | ((__x & 0xff) << 56));
#endif
	}

#define __NET_BE64(__x) __net_be64(__x)
#define __NET_BSWAP64(__x) __NET_BE64((__x))

#elif defined(__BIGENDIAN__)


static __inline__ _Uint16t __net_le16 (_Uint16t __x)
	{
#if defined(__CPU_ENDIAN_RET16)
		return __cpu_endian_ret16(__x);
#else
		return (((__x >> 8) & 0xff) | ((__x & 0xff) << 8));
#endif
	}

#define __NET_LE16(__x) __net_le16(__x)
#define __NET_BSWAP16(__x) __NET_LE16((__x))


static __inline__ _Uint32t __net_le32 (_Uint32t __x)
	{
#if defined(__CPU_ENDIAN_RET32)
		return __cpu_endian_ret32(__x);
#else
		return (((__x >> 24) & 0xff) | ((__x >> 8) & 0xff00) |
			((__x & 0xff00) << 8) | ((__x & 0xff) << 24));
#endif
	}

#define __NET_LE32(__x) __net_le32(__x)
#define __NET_BSWAP32(__x) __NET_LE32((__x))


static __inline__ _Uint64t __net_le64 (_Uint64t __x)
	{
#if defined(__CPU_ENDIAN_RET64)
		return __cpu_endian_ret64(__x);
#else
		return (((__x >> 56) & 0xff) | ((__x >> 40) & 0xff00) |
			((__x >> 24) & 0xff0000) | ((__x >>  8) & 0xff000000) |
			((__x & 0xff000000) <<  8) | ((__x & 0xff0000) << 24) |
			((__x & 0xff00) << 40) | ((__x & 0xff) << 56));
#endif
	}

#define __NET_LE64(__x) __net_le64(__x)
#define __NET_BSWAP64(__x) __NET_LE64((__x))

#define __NET_BE16(__x)	((__x))
#define __NET_BE32(__x)	((__x))
#define __NET_BE64(__x)	((__x))

#else
#error ENDIAN Not defined for system
#endif


#define __htons(__x)	__NET_BE16((__x))
#define __ntohs(__x)	__NET_BE16((__x))
#define __htonl(__x)	__NET_BE32((__x))
#define __ntohl(__x)	__NET_BE32((__x))

#ifdef __EXT_BSD

#define htobe16(__x)	__NET_BE16((__x))
#define be16toh(__x)	__NET_BE16((__x))
#define htobe32(__x)	__NET_BE32((__x))
#define be32toh(__x)	__NET_BE32((__x))
#define htobe64(__x)	__NET_BE64((__x))
#define be64toh(__x)	__NET_BE64((__x))

#define htole16(__x)	__NET_LE16((__x))
#define le16toh(__x)	__NET_LE16((__x))
#define htole32(__x)	__NET_LE32((__x))
#define le32toh(__x)	__NET_LE32((__x))
#define htole64(__x)	__NET_LE64((__x))
#define le64toh(__x)	__NET_LE64((__x))

#define bswap16(__x)	__NET_BSWAP16((__x))
#define bswap32(__x)	__NET_BSWAP32((__x))
#define bswap64(__x)	__NET_BSWAP64((__x))

#endif /* __EXT_BSD */

#endif /* !_NET_NETBYTE_H_INCLUDED */
