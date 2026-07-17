/*
 * $QNXLicenseC:
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

#ifndef __PLATFORM_H_INCLUDED
# include <sys/platform.h>
#endif

#ifndef __RESMGR_H_INCLUDED
#define __RESMGR_H_INCLUDED


#if defined(__EXT_POSIX1_199309) || defined(__EXT_POSIX1_199506) || defined(__EXT_POSIX1_200112)
/* We really shouldn't include pthread.h at all since nothing in resmgr.h depends
 * on it.  However, we did before so for backwards compatibility we must continue
 * to do so.  But, pthread.h is only supported in and after POSIX-1993, so in order
 * to compile in older environments we only include sched.h in those later versions.
 */
# ifndef _PTHREAD_H_INCLUDED
#  include <pthread.h>
# endif
#endif

#ifndef __IOMSG_H_INCLUDED
# include <sys/iomsg.h>
#endif

#if defined(__IOVEC_T)
typedef __IOVEC_T	iov_t;
# undef __IOVEC_T
#endif

#include <_pack64.h>
#include <stdbool.h>

__BEGIN_DECLS

typedef struct _pulse io_pulse_t;

struct _dispatch;
typedef struct _dispatch dispatch_t;

/*
 * Grouping of IO messages that can be used with the combo connect callout.
 * The combo callout allows resmgrs to implement a faster message handling
 * scheme by skipping the management of a binding/OCB (and associated overhead of extra
 * close_dup and close_ocb callouts).
 * The combo() callout takes two messages instead of one.
 * The first is an io_open_t that is only used to resolve the path (with possible redirects).
 * The second is one of _resmgr_combomsgs_t that indicates the operation to be performed on the given path.
 * Effectively, this permits operating on a path without having to utilize an OCB.
 * The second message pointer can be NULL, which indicates to the callout that only the path in the first
 * message is to be resolved, and no operation is to be done on the file/object at the resolved path.
 * (this is used for things like realpath()/fullpath() etc., which utilize an empty _IO_CONNECT_COMBINE_CLOSE
 * sequence).
 */

typedef union _resmgr_combomsgs {
	unsigned short		type;
	struct _io_combine	combine;
	io_stat_t			stat;
	io_pathconf_t		pathconf;
	io_chmod_t			chmod;
	io_chown_t			chown;
	io_utime_t			utime;
} _resmgr_combomsgs_t;

typedef union _resmgr_iomsgs {
	unsigned short				type;

	io_pulse_t					pulse;

	struct _io_connect			connect;
	io_open_t					open;
	io_unlink_t					unlink;
	io_rename_t					rename;
	io_mknod_t					mknod;
	io_readlink_t				readlink;
	io_link_t					link;
	io_mount_t					mount;

	struct _io_combine			combine;
	io_close_t					close;
	io_write_t					write;
	io_read_t					read;
	io_stat_t					stat;
	io_notify_t					notify;
	io_devctl_t					devctl;
	io_pathconf_t				pathconf;
	io_lseek_t					lseek;
	io_chmod_t					chmod;
	io_chown_t					chown;
	io_utime_t					utime;
	io_openfd_t					openfd;
	io_fdinfo_t					fdinfo;
	io_lock_t					lock;
	io_space_t					space;
	io_shutdown_t				shutdown;
	io_msg_t					msg;
    io_mmap_t				    mmap;
    io_mmap_ext_t			    mmap_ext;
	io_dup_t					dup;
	io_sync_t					sync;
	io_power_t					power;
	io_acl_t					acl;
} resmgr_iomsgs_t;

struct _xendian_context {
	_Uint16t					type;
	_Uint16t					mode;
	_Uint32t					hint;
};
struct _extended_context {
	size_t						length;
	struct _xendian_context		xendian;
	void						*data; /* general purpose */
};

typedef struct _resmgr_context {
	rcvid_t						rcvid;
	struct _msg_info			info;
	resmgr_iomsgs_t				*msg;
	dispatch_t					*dpp;
	int							id;
	struct _extended_context	*extra;
	size_t						msg_max_size;
	long						status;
	size_t						offset;
	size_t						size;
	__FLEXARY(iov_t, iov); /* iov_t iov[] */
} resmgr_context_t;

#ifndef RESMGR_HANDLE_T
# define RESMGR_HANDLE_T		void
#endif

typedef int(*_resmgr_connect_func_t)(resmgr_context_t *ctp, resmgr_iomsgs_t *msg, void *handle, void *extra);

typedef int(*_resmgr_func_t)(resmgr_context_t *ctp, resmgr_iomsgs_t *msg, void *ocb);

typedef struct _resmgr_connect_funcs {
	unsigned	nfuncs;
	int			(*open)(resmgr_context_t *ctp, io_open_t *msg, RESMGR_HANDLE_T *handle, void *extra);
	int			(*unlink)(resmgr_context_t *ctp, io_unlink_t *msg, RESMGR_HANDLE_T *handle, void *reserved);
	int			(*rename)(resmgr_context_t *ctp, io_rename_t *msg, RESMGR_HANDLE_T *handle, io_rename_extra_t *extra);
	int			(*mknod)(resmgr_context_t *ctp, io_mknod_t *msg, RESMGR_HANDLE_T *handle, void *reserved);
	int			(*readlink)(resmgr_context_t *ctp, io_readlink_t *msg, RESMGR_HANDLE_T *handle, void *reserved);
	int			(*link)(resmgr_context_t *ctp, io_link_t *msg, RESMGR_HANDLE_T *handle, io_link_extra_t *extra);
	int			(*unblock)(resmgr_context_t *ctp, io_pulse_t *msg, RESMGR_HANDLE_T *handle, void *reserved);
	int			(*mount)(resmgr_context_t *ctp, io_mount_t *msg, RESMGR_HANDLE_T *handle, io_mount_extra_t *extra);
	int			(*combo)(resmgr_context_t *ctp, io_open_t *msg1, RESMGR_HANDLE_T *handle, _resmgr_combomsgs_t *msg2);
} resmgr_connect_funcs_t;
#define _RESMGR_CONNECT_NFUNCS	((sizeof(resmgr_connect_funcs_t)-sizeof(unsigned))/sizeof(void *))

#ifndef RESMGR_OCB_T
# define RESMGR_OCB_T			void
#endif

typedef struct _resmgr_io_funcs {
	unsigned	nfuncs;
	int			(*read)(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb);
	int			(*write)(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb);
	int			(*close_ocb)(resmgr_context_t *ctp, void *reserved, RESMGR_OCB_T *ocb);
	int			(*stat)(resmgr_context_t *ctp, io_stat_t *msg, RESMGR_OCB_T *ocb);
	int			(*notify)(resmgr_context_t *ctp, io_notify_t *msg, RESMGR_OCB_T *ocb);
	int			(*devctl)(resmgr_context_t *ctp, io_devctl_t *msg, RESMGR_OCB_T *ocb);
	int			(*unblock)(resmgr_context_t *ctp, io_pulse_t *msg, RESMGR_OCB_T *ocb);
	int			(*pathconf)(resmgr_context_t *ctp, io_pathconf_t *msg, RESMGR_OCB_T *ocb);
	int			(*lseek)(resmgr_context_t *ctp, io_lseek_t *msg, RESMGR_OCB_T *ocb);
	int			(*chmod)(resmgr_context_t *ctp, io_chmod_t *msg, RESMGR_OCB_T *ocb);
	int			(*chown)(resmgr_context_t *ctp, io_chown_t *msg, RESMGR_OCB_T *ocb);
	int			(*utime)(resmgr_context_t *ctp, io_utime_t *msg, RESMGR_OCB_T *ocb);
	int			(*openfd)(resmgr_context_t *ctp, io_openfd_t *msg, RESMGR_OCB_T *ocb);
	int			(*fdinfo)(resmgr_context_t *ctp, io_fdinfo_t *msg, RESMGR_OCB_T *ocb);
	int			(*lock)(resmgr_context_t *ctp, io_lock_t *msg, RESMGR_OCB_T *ocb);
	int			(*space)(resmgr_context_t *ctp, io_space_t *msg, RESMGR_OCB_T *ocb);
	int			(*shutdown)(resmgr_context_t *ctp, io_shutdown_t *msg, RESMGR_OCB_T *ocb);
	int			(*mmap)(resmgr_context_t *ctp, io_mmap_t *msg, RESMGR_OCB_T *ocb);
	int			(*msg)(resmgr_context_t *ctp, io_msg_t *msg, RESMGR_OCB_T *ocb);
	int			(*check_msg)(resmgr_context_t const *ctp, resmgr_iomsgs_t const *msg,
							 bool combine, RESMGR_OCB_T const *ocb);
	int			(*dup)(resmgr_context_t *ctp, io_dup_t *msg, RESMGR_OCB_T *ocb);
	int			(*close_dup)(resmgr_context_t *ctp, io_close_t *msg, RESMGR_OCB_T *ocb);
	int			(*lock_ocb)(resmgr_context_t *ctp, void *reserved, RESMGR_OCB_T *ocb);
	int			(*unlock_ocb)(resmgr_context_t *ctp, void *reserved, RESMGR_OCB_T *ocb);
	int			(*sync)(resmgr_context_t *ctp, io_sync_t *msg, RESMGR_OCB_T *ocb);
	int			(*power)(resmgr_context_t *ctp, io_power_t *msg, RESMGR_OCB_T *ocb);
	int			(*acl)(resmgr_context_t *ctp, io_acl_t *msg, RESMGR_OCB_T *ocb);
	int			(*pause)(resmgr_context_t *ctp, void *reserved, RESMGR_OCB_T *ocb);	// reserved.
	int			(*unpause)(resmgr_context_t *ctp, io_pulse_t *msg, RESMGR_OCB_T *ocb);	// reserved.
	int			(*read64)(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb);
	int			(*write64)(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb);
	int			(*notify64)(resmgr_context_t *ctp, io_notify_t *msg, RESMGR_OCB_T *ocb);
	int			(*utime64)(resmgr_context_t *ctp, io_utime_t *msg, RESMGR_OCB_T *ocb);
} resmgr_io_funcs_t;
#define _RESMGR_IO_NFUNCS		((sizeof(resmgr_io_funcs_t)-sizeof(unsigned))/sizeof(void *))

#define _RESMGR_NOREPLY			(INT_MIN + 0)	/* Do not reply to sender (could use _RESMGR_AGAIN later) */
#define _RESMGR_DEFAULT			(INT_MIN + 1)	/* Default action (usually return ENOSYS) */
#define _RESMGR_DELAY_CLOSE		(INT_MIN + 2) 	/* Defunct; to be removed */
#define _RESMGR_NPARTS(_num)	(-(_num))				/* Reply with this many parts from ctp->iov */
#define _RESMGR_ERRNO(_err)		(_err)					/* Reply with a short status containing an errno (can be EOK) */
#define _RESMGR_PTR(_h,_p,_n)	(SETIOV((_h)->iov+0,(_p),(_n)),_RESMGR_NPARTS(1))
#define _RESMGR_STATUS(_c,_s)	((_c)->status = (_s))

/*
 * flags for resmgr_attach(). Many match PATHMGR_FLAG_*.
 */
#define _RESMGR_FLAG_BEFORE		0x0001	/* Force path to be resolved before others at the same mountpoint. */
#define _RESMGR_FLAG_AFTER		0x0002	/* Force path to be resolved after others at the same mountpoint. */
#define _RESMGR_FLAG_OPAQUE		0x0004	/* Don't resolve to mountpoints with shorter pathname matches. */
#define _RESMGR_FLAG_FTYPEONLY	0x0008	/* Only attach at "/", and only match ftype */
#define _RESMGR_FLAG_FTYPEALL	0x0010	/* Matching all ftypes (for redirecting servers) */
#define _RESMGR_FLAG_DIR		0x0100	/* Allow resolving of longer pathnames. */
#define _RESMGR_FLAG_SELF		0x0200	/* Allow resolving names to itself. */
#define _RESMGR_FLAG_DETACH_CTP		0x80000000	/* Manager will use resmgr_detach_ctp() on this link */
#define _RESMGR_FLAG_MASK		0x031f	/* Flags which match a PATHMGR_FLAG_* */

/*
 * flags for resmgr_detach()
 */
#define _RESMGR_DETACH_ALL		0x0000	/* Detach the name from the namespace and invalidate all open bindings. */
#define _RESMGR_DETACH_PATHNAME	0x0001	/* Only detach the name from the namespace */
#define _RESMGR_DETACH_CLOSE	0x8000	/* Call close on bindings when detaching */

/*
 * flags for resmgr_pathname(). Must match _FDINFO_FLAG_*.
 */
#define _RESMGR_PATHNAME_LOCALPATH	0x0001	/* Used to return smaller path for displaying */

/*
 * If using thread pool functions, default to passing resmgr_context_t
 */
#ifndef THREAD_POOL_PARAM_T
# define THREAD_POOL_PARAM_T	resmgr_context_t
#endif

#ifndef THREAD_POOL_HANDLE_T
# define THREAD_POOL_HANDLE_T	dispatch_t
#endif

struct binding;

extern int resmgr_pathname(int __id, unsigned __flags, char *__path, int __maxbuf);
extern int resmgr_overridable(int __id, int __uid);
extern int resmgr_devino(int __id, dev_t *__pdevno, ino64_t *__pino);
extern int resmgr_open_bind(resmgr_context_t *__ctp, RESMGR_OCB_T *__ocb, const resmgr_io_funcs_t *__io_funcs);
extern int resmgr_msg_again(resmgr_context_t *__ctp, rcvid_t __rcvid);

extern ssize_t resmgr_msgwrite(resmgr_context_t *__ctp, const void *__msg,  size_t _size, size_t __offset);
extern ssize_t resmgr_msgwritev(resmgr_context_t *__ctp, const struct iovec *__smsg, int __sparts, size_t __offset);
extern ssize_t resmgr_msgread(resmgr_context_t *__ctp, void *__msg, size_t __size, size_t __offset);
extern ssize_t resmgr_msgreadv(resmgr_context_t *__ctp, struct iovec *__rmsg, int __rparts, size_t __offset);
extern ssize_t resmgr_msgget(resmgr_context_t *__ctp, void *__msg, size_t __size, size_t __offset);
extern ssize_t resmgr_msggetv(resmgr_context_t *__ctp, iov_t *__rmsg, size_t __rparts, size_t __offset);
extern size_t resmgr_msggetsize(resmgr_context_t *__ctp, size_t __start_offset, size_t * __local_size, size_t *__remote_size);

extern int  resmgr_msgreply(resmgr_context_t *__ctp, void *__ptr, size_t __len);
extern int  resmgr_msgreplyv(resmgr_context_t *__ctp, const struct iovec *__iov, int __parts);
extern int  resmgr_endian(resmgr_context_t *__ctp, resmgr_iomsgs_t *__msg);
extern void resmgr_endian_context(resmgr_context_t *__ctp, int __type, int __mode, int __hint);

extern void * _resmgr_ocb(resmgr_context_t *__ctp, struct _msg_info_hdr *__info);
extern void * resmgr_ocb(resmgr_context_t *__ctp);
extern const resmgr_io_funcs_t *_resmgr_iofuncs(resmgr_context_t *__ctp, struct _msg_info_hdr *__info);
extern const resmgr_io_funcs_t *resmgr_iofuncs(resmgr_context_t *__ctp);
extern int resmgr_ocb_iofuncs(resmgr_context_t * const ctp, void** ocb, const resmgr_io_funcs_t** iofuncs);

extern int resmgr_unbind(resmgr_context_t *__ctp);
extern int _resmgr_unbind(struct _msg_info_hdr *__rep);
extern int _resmgr_detach_id(resmgr_context_t *__ctp, int __id, unsigned __flags);

extern int _resmgr_complete_delayed_close(resmgr_context_t *__ctp);
extern int _resmgr_check_open(resmgr_context_t *ctp, int link_id, io_open_t	const *msg);

extern int resmgr_pause_queue(resmgr_context_t *const ctp, const void *const private_data, size_t extra_size);
extern int resmgr_pause_resume(resmgr_context_t *const ctp, RESMGR_OCB_T *const ocb,
                    int (*callback)(resmgr_context_t *ctp, RESMGR_OCB_T *const ocb,
                    void *private_data));
extern int resmgr_pause(resmgr_context_t *ctp);

__END_DECLS

#include <_packpop.h>

#if __NTO_FORTIFY_LEVEL > 0
#include <sys/resmgr_chk.h>
#endif

#endif
