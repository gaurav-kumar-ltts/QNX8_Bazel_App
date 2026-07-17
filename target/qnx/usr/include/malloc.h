/*
 * $QNXLicenseC:
 * Copyright 2007-2022, QNX Software Systems. All Rights Reserved.
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

#ifndef _MALLOC_H_INCLUDED
#define _MALLOC_H_INCLUDED
#define _MALLOC_H_DECLARED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#include <_pack64.h>

#if defined(__SIZE_T)
typedef __SIZE_T	size_t;
#undef __SIZE_T
#endif

#if defined(__INTPTR_T)
typedef __INTPTR_T	intptr_t;
#undef __INTPTR_T
#endif

#if defined(__EXT_QNX) && !defined(_alloca)
# ifndef _ALLOCA_H_INCLUDED
#  include <alloca.h>
# endif
#endif

__BEGIN_DECLS

extern void *calloc(size_t __n, size_t __size)
		__attribute__((__alloc_size__(1, 2)));
extern void *malloc(size_t __size) __attribute__((__alloc_size__(1)));
extern void *realloc(void *__ptr, size_t __size)
		__attribute__((__alloc_size__(2)));
extern void free(void *__ptr);

#if defined(__EXT_ANSIC_201112)
extern void *aligned_alloc(size_t __alignment, size_t __size)
		__attribute__((__alloc_size__(2)));
#endif

#if defined(__EXT_POSIX1_200112)		/* Approved 1003.1d D14 */
extern int posix_memalign(void **__memptr, size_t __alignment, size_t __size);
#endif

#if defined(__EXT_XOPEN_EX)
extern void *valloc(size_t __size) __attribute__((__alloc_size__(1)));
#endif

#if defined(__EXT_QNX)		/* SVID/XPG/ELIX functions */

extern void *reallocarray(void *__optr, size_t __nmemb, size_t __size)
		__attribute__((__alloc_size__(2, 3)));
extern void *recallocarray(void *__ptr, size_t __oldnmemb,
						   size_t __newnmemb, size_t __size)
		__attribute__((__alloc_size__(3, 4)));

/* Deprecated */
enum malloc_opt_cmds {
	MALLOC_VERIFY,
	MALLOC_VERIFY_ON,
	MALLOC_STATS,
	MALLOC_FREE_CHECK,
	MALLOC_ARENA_SIZE,
	MALLOC_MONOTONIC_GROWTH,
	MALLOC_MEMORY_HOLD,
	MALLOC_ARENA_CACHE_MAXSZ,
	MALLOC_ARENA_CACHE_MAXBLK,
	MALLOC_ARENA_CACHE_FREE_NOW,
	MALLOC_ERROR_GET_FNPTR,
	MALLOC_ERROR_SET_FNPTR,
	MALLOC_SET_MMAP_PRELOAD,
	MALLOC_GET_MMAP_PRELOAD,
	MALLOC_SET_MAX_LOCK_RETRY,
	MALLOC_GET_MAX_LOCK_RETRY,
	MALLOC_MAX_ALIGNMENT,
	MALLOC_LAST
};

/* Deprecated except for:
 * M_TRIM_THRESHOLD
 * M_MMAP_THRESHOLD
 * M_GRANULARITY
 *
 * Don't enum these, so we don't get coercion errors if the caller is C++
 */
# define M_MXFAST	      (int)MALLOC_LAST
# define M_NLBLKS	      ((int)MALLOC_LAST+1)
# define M_GRAIN		  ((int)MALLOC_LAST+2)
# define M_TRIM_THRESHOLD ((int)MALLOC_LAST+3)
# define M_TOP_PAD	      ((int)MALLOC_LAST+4)
# define M_MMAP_THRESHOLD ((int)MALLOC_LAST+5)
# define M_MMAP_MAX	      ((int)MALLOC_LAST+6)
# define M_GRANULARITY	  ((int)MALLOC_LAST+7)

/* Deprecated */
struct malloc_stats {
	size_t	m_small_freemem;/* memory in free small blocks */
	size_t	m_freemem;	/* memory in free big blocks */
	size_t	m_small_overhead;/* space in header block headers */
	size_t	m_overhead;	/* space used by block headers */
	size_t	m_small_allocmem;/* space in small blocks in use */
	size_t	m_allocmem;	/* space in big blocks in use */
	size_t	m_coreallocs;	/* number of core allocations performed */
	size_t	m_corefrees;	/* number of core de-allocations performed */
	size_t	m_heapsize;	/* size of the arena */
	size_t	m_frees;	/* number of frees performed */
	size_t	m_allocs;	/* number of allocations performed */
	size_t	m_reallocs;	/* number of realloc functions performed */
	size_t	m_small_blocks;	/* number of small blocks */
	size_t	m_blocks;	/* number of big blocks */
	size_t	m_hblocks;	/* number of header blocks */
};

struct mallinfo {
    size_t  arena;  /* size of the arena */
    size_t  ordblks;/* the number of free chunks */
    size_t  smblks; /* always zero */
    size_t  hblks;  /* number of arenas */
    size_t  hblkhd; /* total bytes held in mmapped regions */
    size_t  usmblks;/* the maximum total allocated space. This will be
                     * greater than current total if trimming has
                     * occurred
                     */
    size_t  fsmblks;/* always zero */
    size_t  uordblks;/* current total allocated space */
    size_t  fordblks;/* total free space */
    size_t  keepcost;/* the maximum number of bytes that could ideally
                      * be released back to system via malloc_trim.
                      * ("ideally" means that it ignores page
                      * restrictions etc.)
                      */
};

extern size_t malloc_usable_size(void *__mem);
extern struct mallinfo mallinfo(void);
extern int mallopt(int __cmd, intptr_t __value);

extern void *memalign(size_t __alignment, size_t __size)
		__attribute__((__alloc_size__(2)));

#endif

__END_DECLS

#include <_packpop.h>

#endif
