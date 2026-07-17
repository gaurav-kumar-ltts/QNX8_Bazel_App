/*
 * $QNXtpLicenseC:
 * Copyright 2007-2021, QNX Software Systems. All Rights Reserved.
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
 *  sys/target_nto.h
 *

 *
 *  The only symbols made visible by this header are
 *  OS/compiler reserved symbols.
 */
#ifndef __TARGET_NTO_H_INCLUDED
#define __TARGET_NTO_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#error sys/target_nto.h should not be included directly.
#endif


/* <STAN_MACRO1> */


#ifndef _NULL
#define	_NULL ((void *)0)
#endif /*_NULL*/

#undef __ID_T
#define __ID_T		_INT32
#define __PRIID		PRId32

#undef __CID_T
#define __CID_T     _UINT32
#define __PRICID    PRIu32

#undef __PID_T
#define __PID_T		_INT32
#define __PRIPID	PRId32

#undef __PID64_T
#define __PID64_T	_Int64t
#define __PRIPID64	PRId64

#undef __UID_T
#define __UID_T		_INT32
#define __PRIUID	PRId32

#undef __GID_T
#define __GID_T		_INT32
#define __PRIGID	PRId32

#if defined (__cplusplus)
#undef __WCHAR_T
#define __WCHAR_T	wchar_t
#else
#ifndef __WCHAR_T
#define __WCHAR_T	_Uint32t
#endif
#endif

#undef __WINT_T
#define __WINT_T	_Int32t

#ifndef _WCMAX
#define _WCMAX		0x7fffffff
#endif

#ifndef _WCMIN
#if _WCMAX == 0x7fffffff
#define _WCMIN		0
#else
#define _WCMIN		0U
#endif
#endif

#undef __OFF_T
#undef __INO_T
#undef __BLKCNT_T
#undef __FSBLKCNT_T
#undef __FSFILCNT_T
#if __OFF_BITS__ == 64
#define __OFF_T			_Int64t
#define __PRIOFF		PRId64
#define __INO_T			_Uint64t
#define __PRIINO		PRIu64
#define __BLKCNT_T		_Uint64t
#define __FSBLKCNT_T	_Uint64t
#define __FSFILCNT_T	_Uint64t
#elif __OFF_BITS__ == 32
#define __OFF_T			_Int32t
#define __PRIOFF		PRId32
#define __INO_T			_Uint32t
#define __PRIINO		PRIu32
#define __BLKCNT_T		_Uint32t
#define __FSBLKCNT_T	_Uint32t
#define __FSFILCNT_T	_Uint32t
#else
#error __OFF_BITS__ value is unsupported
#endif

#undef __SOCKLEN_T
#define __SOCKLEN_T		_Uint32t

#undef __SA_FAMILY_T
#define __SA_FAMILY_T		_Uint8t

#undef __OFF64_T
#define __OFF64_T		_Int64t
#define __PRIOFF64		PRId64

#undef __INO64_T
#define __INO64_T		_Uint64t
#define __PRIINO64		PRIu64

#undef __BLKCNT64_T
#define __BLKCNT64_T	_Uint64t

#undef __FSBLKCNT64_T
#define __FSBLKCNT64_T	_Uint64t

#undef __FSFILCNT64_T
#define __FSFILCNT64_T	_Uint64t

#undef __BLKSIZE_T
#define __BLKSIZE_T		_Uint32t

typedef _Uint32t		_Time32t;
typedef _Int64t			_Time64t;
#undef __TIME32_MIN
#undef __TIME32_MAX
#define __TIME32_MIN 	0
#define __TIME32_MAX 	4294967295U
#undef __TIME64_MIN
#undef __TIME64_MAX
#define __TIME64_MIN 	(-9223372036854775807LL-1)
#define __TIME64_MAX 	9223372036854775807LL
#undef __TIME_T
#undef __TIME_MIN
#undef __TIME_MAX
#if __PTR_BITS__ == 64
typedef _Time64t		_Timet;
#define __PRITIME		PRId64
#define __TIME_MIN 		(__TIME64_MIN)
#define __TIME_MAX 		(__TIME64_MAX)
#else
typedef _Time32t		_Timet;
#define __PRITIME		PRIu32
#define __TIME_MIN 		(__TIME32_MIN)
#define __TIME_MAX 		(__TIME32_MAX)
#endif
#define __TIME_T		_Timet

#undef __CLOCK_T
#define __CLOCK_T		_Uint32t
#define __PRICLOCK		PRIu32

#undef __MODE_T
#define __MODE_T		_Uint32t
#define __PRIMODE		PRIo32

#undef __DEV__T
#define __DEV_T			_Uint32t
#define __PRIDEV		PRIu32

#undef __NLINK_T
#define __NLINK_T		_Uint32t

#undef __TIMER_T
#define __TIMER_T		int

#undef __CLOCKID_T
#define __CLOCKID_T		int
#define __PRICLOCKID	"d"

#undef __USECONDS_T
#define __USECONDS_T	_Uint32t

#undef __SUSECONDS_T
#define __SUSECONDS_T	_Int32t

#undef __KEY_T
#define __KEY_T			_Uint32t

#undef __PTHREAD_T
#define __PTHREAD_T		_Int32t
#define __PRIPTHREAD	PRId32

#if __PADDR_BITS__==64
#define __PRIPADDR		PRIx64
#elif __PADDR_BITS__==32
#define __PRIPADDR		PRIx32
#else
#error Unknown paddr_t size
#endif

struct __iovec32 {
	_Uintptr32t	_iov_base; \
	_Size32t 	_iov_len; \
};

struct __iovec64 {
	_Uintptr64t	_iov_base; \
	_Size64t 	_iov_len; \
};

#undef __IOVEC_T
#define __IOVEC_T \
	struct iovec { \
		union { \
			void *iov_base; \
			const void *iov_base_const; \
		}; \
		_Sizet iov_len; \
	}

#undef __MBSTATE_T
#define __MBSTATE_T \
	struct _Mbstatet {	/* state of a multibyte translation */ \
		_Wchart		_Wchar; \
		unsigned short _Byte, _State; \
	}

#undef __FPOS_T
#define __FPOS_T \
	struct _Fpost {		/* file position */ \
	_Off64t				_Off; \
	_Mbstatet			_Wstate; \
	}

#undef _FPOSOFF
#define _FPOSOFF(fp)	((fp)._Off)

/* Synchronization structures. */

/**
 * Common synchronization structure used by kernel calls.
 * The structure maintains some user-mode state, depending on the type of object
 * it represents. Additionally, a pointer to this structure is used as an
 * identifier when looking for a kernel object to match.
 * Per-type structures are defined below. These distinct types are used to
 * enforce some type checking in user code. However, each should have an
 * indentical layout to that of the common structure (other than the union being
 * restricted to the field relavant to that type).
 */
#undef __SYNC_T
#define __SYNC_T \
	struct _sync { \
		union {															\
			unsigned	__count;	/* Count for recursive mutexs and semaphores */ \
			int			__fd;		/* File descriptor for a named-semaphore */	\
			int			__clockid;	/* Clock for timed condvar wait */	\
		} __u;															\
		unsigned	__owner;		/* Thread id for mutex, type for others */ \
	}

/**
 * User-mode mutex structure.
 * Used for the definition of pthread_mutex_t.
 */
struct _sync_mutex {
    union {
        unsigned __count;
    } __u;
    unsigned __owner;
};

/**
 * User-mode condition variable structure.
 * Used for the definition of pthread_cond_t.
 */
struct _sync_cond {
    union {
        int __clockid;
    } __u;
    unsigned __owner;
};

/**
 * User-mode semaphore structure.
 * Used for the definition of sem_t.
 */
struct _sync_sem {
    union {
        unsigned __count;
        int      __fd;
    } __u;
    unsigned __owner;
};

/**
 * User-mode read-write lock structure.
 * Used for the definition of pthread_rwlock_t.
 */
struct _sync_rwlock {
    union {
        unsigned __count;
    } __u;
    unsigned __owner;
};

#undef __SYNC_ATTR_T
#define __SYNC_ATTR_T \
	struct _sync_attr { \
		int		__protocol; \
		int		__flags; \
		int		__prioceiling; \
		int		__clockid;		/* Condvars only */ \
		int		__count; \
		int		__reserved[3]; \
	}

#undef __PTHREAD_RWLOCKATTR_T
#define __PTHREAD_RWLOCKATTR_T struct _sync_attr

/*
 * Used to define time specifications.
 */
#undef __TIMESPEC_DEF
#define __TIMESPEC_DEF(__name, __pref, __sec_t, __ns_t) \
	struct __name {						\
	    __sec_t			__pref##_sec;	\
	    __ns_t			__pref##_nsec;	\
    }

#undef	__TIMESPEC
#define __TIMESPEC	__TIMESPEC_DEF(timespec, tv, _Timet, long)
#undef	__TIMESPEC_INTERNAL
#define	__TIMESPEC_INTERNAL	__TIMESPEC_DEF(__timespec, __tv, _Timet, long); \
					__TIMESPEC_DEF(__timespec32, _tv, _Time32t, _Int32t); \
					__TIMESPEC_DEF(__timespec64, _tv, _Time64t, _Int64t)


#undef __SCHED_PARAM_DEF
#if defined(__EXT_QNX) || defined(__EXT_POSIX1_200112)
#define __SCHED_PARAM_DEF(__name, __ts, __pref) \
	struct __name { \
		_INT32	__pref##_priority; \
		_INT32	__pref##_curpriority; \
		union {	\
			_INT32	__reserved[8]; \
			struct {	\
				_INT32	__ss_low_priority;	\
				_INT32	__ss_max_repl;	\
				struct __ts	__ss_repl_period;	\
				struct __ts	__ss_init_budget;	\
			}			__ss;	\
		}			__ss_un;	\
	}
	#define __sched_ss_low_priority	__ss_un.__ss.__ss_low_priority
	#define __sched_ss_max_repl		__ss_un.__ss.__ss_max_repl
	#define __sched_ss_repl_period	__ss_un.__ss.__ss_repl_period
	#define __sched_ss_init_budget	__ss_un.__ss.__ss_init_budget
#else
#define __SCHED_PARAM_DEF(__name, __ts, __pref) \
	struct __name { \
		_INT32	__pref##_priority; \
		_INT32	__pref##_curpriority; \
		_INT32	__spare[8]; \
	}
#endif

#undef	__SCHED_PARAM_INTERNAL
#define	__SCHED_PARAM_INTERNAL	__SCHED_PARAM_DEF(__sched_param, __timespec,__sched); \
								__SCHED_PARAM_DEF(__sched_param32, __timespec32,__sched); \
								__SCHED_PARAM_DEF(__sched_param64, __timespec64,__sched) \

#undef	__SCHED_PARAM_T
#define	__SCHED_PARAM_T	__SCHED_PARAM_DEF(sched_param, timespec, sched)

/*
 * Used to define thread creation attributes.
 */
typedef void (__exitfunc_t)(void *);
typedef void (__entryfunc_t)(void *, void *(*)(void *));
/* <STAN_MACRO5/> */
#define __PTHREAD_ATTR_SIZED(__sname,__sizet, __stackt, __funct, __scheds, __entry_t)  \
	struct __sname { \
		int							__flags; \
		__sizet						__stacksize; \
		__stackt					__stackaddr; \
		_Uintptrt					__reserved0; \
		int							__policy; \
		struct __scheds				__param; \
		unsigned					__guardsize; \
		unsigned					__prealloc; \
		_Uintptrt					__reserved1; \
	}
#undef __PTHREAD_ATTR_T
#define __PTHREAD_ATTR_T __PTHREAD_ATTR_SIZED(_thread_attr, _Sizet, void *, __exitfunc_t *, __sched_param, __entryfunc_t *)
#define __PTHREAD_ATTR_T32 __PTHREAD_ATTR_SIZED(_thread_attr32, _Size32t, _Uintptr32t, _Uintptr32t, __sched_param32, _Uintptr32t)
#define __PTHREAD_ATTR_T64 __PTHREAD_ATTR_SIZED(_thread_attr64, _Size64t, _Uintptr64t, _Uintptr64t, __sched_param64, _Uintptr64t)

/*
 * Used to define FILE
 */
/* Definition of the structure, expanded in stdio.h */
#undef __FILE_T_DEF
#define __FILE_T_DEF \
struct _Filet {															\
	unsigned int	_Mode;			/* mode flags */				\
	int				_Handle;		/* file descriptor */			\
	unsigned char	*_Buf;			/* location of buffer */		\
	unsigned char	*_Bend;			/* end of buffer */				\
	unsigned char	*_Next;			/* next character position */	\
	unsigned char	*_Rend;			/* end of read buffer */		\
	unsigned char	*_Wend;			/* end of write buffer */		\
	unsigned char	*_Rback;		/* end of undo buffer */		\
	_Wchart			*_WRback;		/* end of wide undo buffer */	\
	_Wchart			_WBack[2];		/* wide undo buffer */			\
	unsigned char	*_Rsave;		/* Saved end of read buffer */	\
	unsigned char	*_WRend;		/* end of wide read buffer */	\
	unsigned char	*_WWend;		/* end of wide write buffer */	\
	_Mbstatet		_Wstate;		/* wide multibyte state */		\
	struct _Filet	*_NextFile;		/* next file entry */			\
	unsigned char	_Back[2];		/* undo buffer */				\
	unsigned char	_Cbuf;			/* Single character buffer */	\
	void *_Flock;							/* file lock */			\
	unsigned char	_Spare[4];										\
}

#undef __FILE_T
#define __FILE_T struct _Filet


/*
 * Signal structures
 */
#undef __STACK_T
#define __STACK_T	__32_64_STACK_T(void *, _Sizet)
/* <STAN_MACRO5/> */
#define __32_64_STACK_T(__pt, __st) \
	struct {					\
		__pt		ss_sp;		\
		__st		ss_size;	\
		int			ss_flags;	\
	}

#undef __SIGSET_T
#define __SIGSET_T _Uint64t

#undef __UCONTEXT_T
#define __UCONTEXT_T	struct __ucontext_t


/* These are C99 types */

typedef _Int8t						_Intleast8t;
typedef _Uint8t						_Uintleast8t;
typedef _Int8t						_Intfast8t;
typedef _Uint8t						_Uintfast8t;

typedef _Int16t						_Intleast16t;
typedef _Uint16t					_Uintleast16t;
typedef _Int16t						_Intfast16t;
typedef _Uint16t					_Uintfast16t;

typedef _Int32t						_Intleast32t;
typedef _Uint32t					_Uintleast32t;
typedef _Int32t						_Intfast32t;
typedef _Uint32t					_Uintfast32t;

typedef _Int64t						_Intleast64t;
typedef _Uint64t					_Uintleast64t;
typedef _Int64t						_Intfast64t;
typedef _Uint64t					_Uintfast64t;

typedef _Int64t						_Intmaxt;
typedef _Uint64t					_Uintmaxt;

#undef __PTHREAD_KEY_T
#define __PTHREAD_KEY_T		int

#undef __PTHREAD_COND_T
#define __PTHREAD_COND_T		struct _sync_cond

#undef __PTHREAD_CONDATTR_T
#define __PTHREAD_CONDATTR_T	struct _sync_attr

#undef __PTHREAD_MUTEX_T
#define __PTHREAD_MUTEX_T		struct _sync_mutex

#undef __PTHREAD_RWLOCK_T
#define __PTHREAD_RWLOCK_T		struct _sync_rwlock

#undef __PTHREAD_MUTEXATTR_T
#define __PTHREAD_MUTEXATTR_T	struct _sync_attr

#undef __PTHREAD_ONCE_T
#define __PTHREAD_ONCE_T	\
	struct _pthread_once {	\
		int					__once;	\
		struct _sync_mutex	__mutex;	\
	}

/* C11 thread types - same as POSIX above */

/* <STAN_MACRO1> */
#undef __THRD_COND_T
#define __THRD_COND_T		struct _sync_cond

#undef __THRD_THRD_T
#define __THRD_THRD_T		_Int32t

#undef __THRD_TSS_T
#define __THRD_TSS_T		int

#undef __THRD_MTX_T
#define __THRD_MTX_T		struct _sync_mutex

#undef __THRD_ONCE_T
#define __THRD_ONCE_T			\
	struct _thrd_once {		\
		int					__once;		\
		struct _sync_mutex	__mutex;	\
	}
/* </STAN_MACRO1> */

#define __THRD_ONCE_INIT { 0, { {_NTO_SYNC_NONRECURSIVE}, _NTO_SYNC_INITIALIZER } }

/*
 * Synchronization manifests and structures.
 */

/* On count */
#define _NTO_SYNC_NONRECURSIVE	0x80000000U	/* mutexes */
#define _NTO_SYNC_SHARED		0x40000000U	/* all objects */
#define _NTO_SYNC_PRIOCEILING	0x20000000U	/* mutexes */
#define _NTO_SYNC_PRIONONE		0x10000000U	/* mutexes */
#define _NTO_SYNC_WAKEUP		0x08000000U	/* mutexes */
#define _NTO_SYNC_KFORCE		0x04000000U	/* mutexes */
#define _NTO_SYNC_ROBUST		0x02000000U /* mutexes */
#define _NTO_SYNC_NOERRORCHECK	0x01000000U	/* mutexes */
#define _NTO_SYNC_COUNTMASK		0x00ffffffU	/* mutexes */
/* On owner */
#define _NTO_SYNC_MUTEX_FREE	0x00000000U	/*    0  newly-initialized mutex */
#define _NTO_SYNC_WAITING		0x80000000U	/* Top bit used with mutexes */
#define _NTO_SYNC_OWNER_MASK	0x7fffffffU	/* Owner used with mutexes */
#define _NTO_SYNC_INITIALIZER	0xffffffffU	/*   -1  uninitialized object */
#define _NTO_SYNC_DESTROYED		0xfffffffeU	/*   -2  mutexes, cond, sem, spin */
#define _NTO_SYNC_NAMED_SEM		0xfffffffdU	/*   -3  named semaphore */
#define _NTO_SYNC_SEM			0xfffffffcU	/*   -4  unnamed semaphore */
#define _NTO_SYNC_COND			0xfffffffbU	/*   -5  condition variable */
#define _NTO_SYNC_SPIN			0xfffffffaU	/*   -6  spinlock */
#define _NTO_SYNC_JOB			0xfffffff9U	/*   -7  job */
#define _NTO_SYNC_BARRIER		0xfffffff8U	/*   -8  barrier */
#define _NTO_SYNC_RWLOCK		0xfffffff7U /*   -9  read-write lock */
#define _NTO_SYNC_OWNERDEAD		0xffffff00U	/* -256  mutex (when a process dies with a mutex locked) */

/*
 * Copyright (c) 1995-1999 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 */

/* Customize DINKUM libraries */
#if defined(__LITTLEENDIAN__)
#define _D0		3	/* 0: big endian, 3: little endian floating-point */
#elif defined(__BIGENDIAN__)
#define _D0		0	/* 0: big endian, 3: little endian floating-point */
#else
#error ENDIAN Not defined for system
#endif
#if __LONGDOUBLE_BITS__ == 64
#define _DLONG	0		/* 0: 64, 1: 80, 2: 128 long double bits */
#define _LBIAS	0x3fe	/* 64 long double bits */
#define _LOFF	4		/* 64 long double bits */
#elif __LONGDOUBLE_BITS__ == 80
#define _DLONG	1		/* 0: 64, 1: 80, 2: 128 long double bits */
#define _LBIAS	0x3ffe	/* 80/128 long double bits */
#define _LOFF	15		/* 80/128 long double bits */
#elif __LONGDOUBLE_BITS__ == 128
#define _DLONG	2		/* 0: 64, 1: 80, 2: 128 long double bits */
#define _LBIAS	0x3ffe	/* 80/128 long double bits */
#define _LOFF	15		/* 80/128 long double bits */
#elif defined(__LONGDOUBLE_BITS__)
#error __LONGDOUBLE_BITS__ not a supported size
#endif

		/* FLOATING-POINT PROPERTIES */
#define _DBIAS	0x3fe	/* IEEE format double and float */
#define _DOFF	4
#define _FBIAS	0x7e
#define _FOFF	7
#define _FRND	1

		/* integer properties */
#define _BITS_BYTE	8
#define _C2			1	/* 0 if not 2's complement */
#if defined(__CHAR_SIGNED__)
#define _CSIGN		1	/* 0 if char is not signed */
#elif defined(__CHAR_UNSIGNED__)
#define _CSIGN		0	/* 0 if char is not signed */
#endif
#define _MBMAX		8	/* MB_LEN_MAX */

#define _MAX_EXP_DIG	8	/* for parsing numerics */
#define _MAX_INT_DIG	32
#define _MAX_SIG_DIG	48

#ifndef __LINKER_WARNING
#define __LINKER_WARNING(__symbol, __warning)
#endif

/* </STAN_MACRO1> */

#endif
