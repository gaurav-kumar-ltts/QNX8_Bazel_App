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
 *  sys/procmsg.h
 *

 */
#ifndef __PROCMSG_H_INCLUDED
#define __PROCMSG_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __SYSMSG_H_INCLUDED
#include _NTO_HDR_(sys/sysmsg.h)
#endif

#ifndef _SPAWN_H_INCLUDED
#include _NTO_HDR_(spawn.h)
#endif

#ifndef __SIGINFO_H_INCLUDED
#include _NTO_HDR_(sys/siginfo.h)
#endif

#ifndef __RESOURCE_H_INCLUDED
#include _NTO_HDR_(sys/resource.h)
#endif

#if defined(__ID_T)
typedef __ID_T		id_t;
#undef __ID_T
#endif

#if defined(__PID_T)
typedef __PID_T		pid_t;
#undef __PID_T
#endif

#if defined(__UID_T)
typedef __UID_T		uid_t;
#undef __UID_T
#endif

#if defined(__GID_T)
typedef __GID_T		gid_t;
#undef __GID_T
#endif

#define PROCMGR_PID				SYSMGR_PID
#define PROCMGR_CHID			SYSMGR_CHID
#define PROCMGR_COID			SYSMGR_COID
#define PROCMGR_HANDLE			SYSMGR_HANDLE

enum {
	_PROC_SPAWN = _PROCMGR_BASE,
	_PROC_WAIT,
	_PROC_FORK,
	_PROC_GETSETID,
	_PROC_SETPGID,
	_PROC_UMASK,
	__PROC_UNUSED, // Available
	_PROC_SESSION,
	_PROC_DAEMON,
	_PROC_EVENT,
	_PROC_RESOURCE,
	_PROC_POSIX_SPAWN,
	_PROC_POSIX_SPAWNP,
	_PROC_VALUE,
	_PROC_TIMER_TOLERANCE,
	_PROC_UNUSED2, // Available
	_PROC_MAC,
	_PROC_SERVMON,
	_PROC_GETPID64,
	_PROC_GETNAME,
	_PROC_GET_ALL_PID,
	_PROC_DEBUG,
	_PROC_COREDUMP,
	_PROC_GET_ALL_CHILD_PID,
};

enum {
	_PROC_SPAWN_UNUSED1,
	_PROC_SPAWN_UNUSED2,
	_PROC_SPAWN_ARGS,
	_PROC_SPAWN_DONE,
	_PROC_SPAWN_EXEC,
	_PROC_SPAWN_UNUSED3,
	_PROC_SPAWN_START,
};

enum {
	_PROC_ID_GETID,
	_PROC_ID_SETUID,
	_PROC_ID_SETGID,
	_PROC_ID_SETEUID,
	_PROC_ID_SETEGID,
	_PROC_ID_SETREUID,
	_PROC_ID_SETREGID,
	_PROC_ID_SETGROUPS,
	_PROC_ID_GETID_NO_CRED
};

enum {
	_PROC_EVENT_NOTIFY,
	_PROC_EVENT_TRIGGER,
	_PROC_EVENT_NOTIFY_ADD,
	_PROC_EVENT_NOTIFY_DEL,
	_PROC_EVENT_TRIGGER_UPDATEABLE,
};

enum {
	_PROC_SERVER_MONITOR_CONFIG,
	_PROC_SERVER_MONITOR_IGNORE,
	_PROC_SERVER_MONITOR_ALIVE
};

enum {
	_PROC_UMASK_SET,
	_PROC_UMASK_GET
};

enum {
	_PROC_RESOURCE_USAGE,
	_PROC_RESOURCE_GETLIMIT,
	_PROC_RESOURCE_SETLIMIT,
	_PROC_RESOURCE_SETABILITIES,
	_PROC_RESOURCE_LOOKUPABILITY,
	_PROC_RESOURCE_CREATEABILITY,
	_PROC_RESOURCE_ABILITY_NAME
};

enum {
	_PROC_TIMER_TOLERANCE_GET,
	_PROC_TIMER_TOLERANCE_SET
};

enum {
	_PROC_MAC_POLICY,
	_PROC_MAC_POLICY_ID,
	_PROC_MAC_SET_TYPE_ID,
	_PROC_MAC_POLICY_MULTI,
};

#define _FORK_ASPACE	0x00000001u	/* Don't share address space */
#define _FORK_NOFDS		0x00000002u	/* Don't dup any fd's */
#define _FORK_NOZOMBIE	0x00000004u	/* Don't allow waiting */
#define _FORK_COW		0x00000008u	/* Use copy-on-write */
#define _FORK_NEWAPP	0x00000010u	/* Child is a new app */

#include _NTO_HDR_(_pack64.h)

/*
 * Message of _PROC_SPAWN/_PROC_SPAWN_START
 */
#ifdef __EXT_QNX		/* struct inheritance is only defined in __EXT_QNX */
struct _proc_spawn {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint16t						searchlen;
	_Uint16t						pathlen;
	struct __msg_inheritance		parms;
	_Uint16t						nfds;
	_Uint16t						nargv;
	_Uint16t						narge;
	_Uint16t						reserved;
	_Uint32t						nbytes;		/* Number of bytes of argv + arge with nulls */
	/* _Int32t						fd_map[nfds] */
	/* char							search[searchlen] */
	/* char							path[pathlen] */
	/* char							argv[nargv][] */
	/* char							arge[narge][] */
};

typedef union {
	struct _proc_spawn				i;
} proc_spawn_t;
#endif

/*
 * Message of _PROC_SPAWN/_PROC_SPAWN_ARGS
 */
struct _proc_spawn_args {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint32t						nbytes;
	_Uint32t						offset;
	_Uint64t						buf;
};

typedef union {
	struct _proc_spawn_args			i;
} proc_spawn_args_t;

/*
 * Message of _PROC_SPAWN/_PROC_SPAWN_FD
 */
struct _proc_spawn_fd {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint16t						flags;
	_Uint16t						nfds;
	_Int32t							base;
	pid_t							ppid;
	/* int							fd[nfds] */
};
#define _PROC_SPAWN_FD_LIST		0x0001		/* only fds from passed in list (otherwise all fds) */
#define _PROC_SPAWN_FD_NOCLOEXC	0x0002		/* no fds with CLOEXC set (i.e. spawn) */
#if 0
#define _PROC_SPAWN_FD_BASE		0x0004		/* start finding fd's from base */
#endif

struct _proc_spawn_fd_info {
	int								fd;
	_Uint32t						nd;
	_Uint32t						srcnd;
	pid_t							pid;
	_Int32t							chid;
	_Int32t							scoid;
	_Int32t							coid;
};

struct _proc_spawn_fd_reply {
	_Uint16t						flags;
	_Uint16t						nfds;
	/* struct _proc_spawn_fd_info	info[nfds]; */
};

#define _PROC_SPAWN_FDREPLY_MORE	0x00000001	/* More fd's to return, send again */

typedef union {
	struct _proc_spawn_fd			i;
	struct _proc_spawn_fd_reply		o;
} proc_spawn_fd_t;


/*
 * Message of _PROC_SPAWN/_PROC_SPAWN_DONE
 */
struct _proc_spawn_done {
	_Uint16t						type;
	_Uint16t						subtype;
	_Int32t							rcvid;
};

typedef union {
	struct _proc_spawn_done			i;
} proc_spawn_done_t;

/*
 * additional msg parts for remote spawn
 */
typedef struct {
	_Uint32t						key;
	_Uint32t						umask;
	_Uint16t						nfds;
	_Uint16t						root_len;
	_Uint16t						cwd_len;
	_Uint16t						flags;
	/*	char* root[PATH_MAX]	*/
	/*	char* cwd[PATH_MAX]	*/
	/*	struct _proc_spawn_fd_info	fd_array[]	*/
}	proc_spawn_remote_t;

/* definition for flags field */
#define _PROC_SPAWN_REMOTE_FLAGS_FDALLIN		0x1

typedef struct {
	_Uint32t						nd;
	pid_t							pid;
	_Uint32t						chid;
	_Int32t							size;
} spawn_remote_t;

#define SPAWN_REMOTE_FDARRAY_SIZE	10
#define SPAWN_REMOTE_REMOTEBUF_SIZE	(sizeof(struct _proc_spawn_fd_info) * SPAWN_REMOTE_FDARRAY_SIZE + PATH_MAX * 2 + sizeof(proc_spawn_remote_t))
#define SPAWN_REMOTE_MSGBUF_SIZE	(sizeof(spawn_remote_t) + SPAWN_REMOTE_REMOTEBUF_SIZE)

/*
 * Message of _PROC_SPAWN/_PROC_SPAWN_DIR
 */

enum {
	_PROC_SPAWN_DIR_ALL,
	_PROC_SPAWN_DIR_ROOT,
	_PROC_SPAWN_DIR_CWD
};

struct _proc_spawn_dir {
	_Uint16t						type;
	_Uint16t						subtype;
	_Int32t							ppid;
	_Uint16t						request;
	_Uint16t						pathmax;
};

struct _proc_spawn_dir_reply {
	_Uint16t						result;
	_Uint16t						rootlen;
};

typedef union {
	struct _proc_spawn_dir			i;
	struct _proc_spawn_dir_reply	o;
} proc_spawn_dir_t;

/*
 * Message of _PROC_POSIX_SPAWN
 */
struct _proc_posix_spawn {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint16t						pathlen;
	_Uint16t						nargv;
	_Uint16t						narge;
	_Uint16t						searchlen;
	_Uint16t						reserved[2];
	_Uint32t						filact_bytes;	/* size of the _posix_spawn_file_actions_t */
	_Uint32t						filact_obytes;	/* size of the _posix_spawn_file_actions_t.open */
	_Uint32t						argenv_bytes;	/* Number of bytes of argv + arge with nulls */
	_Uint32t						attr_bytes;		/* size of the _posix_spawnattr_t */
	/* _posix_spawnattr_t			attr;		  */
	/* _posix_spawn_file_actions_t	filact		  */
	/* char							search[searchlen] */
	/* char							path[pathlen] */
	/* char							argv[nargv][] */
	/* char							arge[narge][] */
};

typedef union {
	struct _proc_posix_spawn		i;
} proc_posixspawn_t;


/*
 * _PROC_NGROUPS_MAX defines the limit on the number of groups that can be
 * delivered through a _proc_getsetid message or reply.  We chose this
 * value because it's about as large as it can be without increasing the
 * maximum size of a proc message.  Since the libc API and internal kernel
 * implementations don't impose a limit themselves, this turns out to define
 * sysconf(_SC_NGROUPS_MAX).
 */
#define _PROC_NGROUPS_MAX 384
/*
 * Message of _PROC_GETSETID
 */
struct _proc_getsetid {
	_Uint16t						type;
	_Uint16t						subtype;
	pid_t							pid;
	id_t							eid;
	id_t							rid;
	_Int32t							ngroups;
	/* gid_t						groups[ngroups]; -- up to _PROC_NGROUPS_MAX*/
};

struct _proc_getsetid_reply {
	_Uint32t						zero;
	pid_t							pgrp;
	pid_t							ppid;
	pid_t							sid;
	pid_t							orig_ppid;
	_Uint32t						reserved[2];
	struct _cred_info				cred; /* note: might have up to _PROC_NGROUPS_MAX */
};

typedef union {
	struct _proc_getsetid			i;
	struct _proc_getsetid_reply		o;
} proc_getsetid_t;


/*
 * Message of _PROC_SETPGID
 */
struct _proc_setpgid {
	_Uint16t						type;
	_Uint16t						zero;
	pid_t							pid;
	pid_t							pgid;
};

typedef union {
	struct _proc_setpgid			i;
} proc_setpgid_t;


/*
 * Message of _PROC_WAIT
 */
struct _proc_wait {
	_Uint16t						type;
	_Int16t							idtype;
	_Int32t							options;
	id_t							id;
};

typedef union {
	struct _proc_wait				i;
	siginfo_t						o;
} proc_wait_t;


/*
 * Message of _PROC_FORK
 */
struct _proc_fork {
	_Uint16t						type;
	_Uint16t						zero;
	_Uint32t						flags;
	_Uint64t						frame;
};

typedef union {
	struct _proc_fork				i;
} proc_fork_t;


/*
 * Message of _PROC_UMASK
 */
struct _proc_umask {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint32t						umask;
	pid_t							pid;
};

struct _proc_umask_reply {
	_Uint32t						zero1;
	_Uint32t						umask;
};

typedef union {
	struct _proc_umask				i;
	struct _proc_umask_reply		o;
} proc_umask_t;

/*
 * Message of _PROC_SESSION
 */
struct _proc_session {
	_Uint16t						type;
	_Uint16t						xid;
	pid_t							sid;
	_Int32t							id;
	_Uint32t						event;
};

typedef union {
	struct _proc_session			i;
} proc_session_t;

/*
 * Message of _PROC_DAEMON
 */
struct _proc_daemon {
	_Uint16t						type;
	_Uint16t						subtype;
	_Int32t							status;
	_Uint32t						flags;
	_Uint32t						reserved;
};

typedef union {
	struct _proc_daemon				i;
} proc_daemon_t;

/*
 * Message of _PROC_EVENT
 */
struct _proc_event {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint32t						flags;
	struct sigevent					event;
};

typedef union {
	struct _proc_event				i;
} proc_event_t;

struct _proc_event_del {
	_Uint16t						type;
	_Uint16t						subtype;
	int								id;
};

typedef union {
	struct _proc_event_del			i;
} proc_event_del_t;

/*
 * Message of _PROC_VALUE
 */
struct _proc_value {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint32t						vtype;
	_Uint64t						value;
	_Int32t							id;
	struct sigevent					event;
};

typedef union {
	struct _proc_value				i;
} proc_value_t;

/*
 * Message header for all _PROC_RESOURCE
 */
struct _proc_resource_hdr {
	_Uint16t						type;
	_Uint16t						subtype;
	pid_t							pid;
};

/*
 * Message of _PROC_RESOURCE/_PROC_RESOURCE_USAGE
 */
struct _proc_resource_usage {
	_Uint16t						type;
	_Uint16t						subtype;
	pid_t							pid;
	_Uint32t						who;
};

typedef union {
	struct _proc_resource_usage		i;
	struct rusage					o;
	struct __rusage32				o32;
	struct __rusage64				o64;
} proc_resource_usage_t;

/*
 * Message of _PROC_RESOURCE/_PROC_RESOURCE_GETLIMIT
 */
struct _proc_resource_getlimit {
	_Uint16t						type;
	_Uint16t						subtype;
	pid_t							pid;
	_Uint32t						count;
	_Uint32t						reserved;
	_Uint32t						resource[1];
};

typedef union {
	struct _proc_resource_getlimit	i;
#if defined(__EXT_LF64SRC)
	struct rlimit64					o[1];
#else
	struct rlimit					o[1];
#endif
} proc_resource_getlimit_t;

/*
 * Message of _PROC_RESOURCE/_PROC_RESOURCE_SETLIMIT
 */
struct _proc_resource_setlimit {
	_Uint16t						type;
	_Uint16t						subtype;
	pid_t							pid;
	_Uint32t						count;
	_Uint32t						reserved;
	struct _proc_resource_entry {
		_Uint32t						resource;
		_Uint32t						reserved;
#if defined(__EXT_LF64SRC)
		struct rlimit64					limit;
#else
		struct rlimit					limit;
#endif
	}								entry[1];
};

typedef union {
	struct _proc_resource_setlimit	i;
} proc_resource_setlimit_t;

/*
 * Message of _PROC_RESOURCE/_PROC_RESOURCE_SETABILITIES
 */
struct _proc_resource_setabilities {
	_Uint16t						type;
	_Uint16t						subtype;
	pid_t							pid;
	_Uint32t						count;
	_Uint32t						entry[1];
};

typedef union {
	struct _proc_resource_setabilities	i;
} proc_resource_setabilities_t;

/*
 * Message of _PROC_RESOURCE/_PROC_RESOURCE_LOOKUPABILITY,_PROC_RESOURCE_CREATEABILITY
 */
struct _proc_resource_lookupability {
	_Uint16t						type;
	_Uint16t						subtype;
	pid_t							pid;
	_Uint32t						flags;
	_Uint32t						namelen;
	/* char							name[namelen] */
};

typedef union {
	struct _proc_resource_lookupability	i;
} proc_resource_lookupability_t;

/*
 * Message of _PROC_RESOURCE/_PROC_RESOURCE_DYNAMIC_ABILITY_NAME
 */
struct _proc_resource_ability_name {
	_Uint16t						type;
	_Uint16t						subtype;
	pid_t							pid;	/* UNUSED */
	_Uint32t						able;
};

typedef union {
	struct		_proc_resource_ability_name	i;
} proc_resource_ability_name_t;


/*
 * Message of _PROC_TIMER_TOLERANCE
 */
struct _proc_timer_tolerance {
	_Uint16t						type;
	_Uint16t						subtype;
	pid_t							pid;
	_Uint64t						tolerance;
};

struct _proc_timer_tolerance_reply {
	_Uint64t						tolerance;
};

typedef union {
	struct _proc_timer_tolerance		i;
	struct _proc_timer_tolerance_reply	o;
} proc_timer_tolerance_t;

struct _proc_mac_policy {
	_Uint16t	type;
	_Uint16t	subtype;
	_Uint32t	datalen;
	_Uint8t		data[];
	// For  _PROC_MAC_POLICY_MULTI messages, the datalen/data may be repeated
	// to push multiple blobs. The length field is always 32-bit aligned.
};

typedef union {
	struct _proc_mac_policy				i;
} proc_mac_policy_t;

struct _proc_mac_policy_id {
	_Uint16t	type;
	_Uint16t	subtype;
};

struct _proc_mac_policy_id_reply {
	_Uint32t	policy_id;
};

typedef union {
	struct _proc_mac_policy_id			i;
	struct _proc_mac_policy_id_reply	o;
} proc_mac_policy_id_t;

struct _proc_mac_set_type_id {
	_Uint16t	type;
	_Uint16t	subtype;
	_Uint32t	type_id;
};

typedef union {
	struct _proc_mac_set_type_id		i;
} proc_mac_set_type_id_t;

/*
 * Message of _PROC_SERVMON
 */
struct _proc_servmon {
    _Uint16t    type;
    _Uint16t	subtype;
    _Uint32t    timeout;
    pid_t   target_pid;
    struct sigevent event;
};

typedef union {
	struct _proc_servmon				i;
} proc_servmon_t;

/*
 * Message of _PROC_GETPID64
 */
struct _proc_getpid64 {
    _Uint16t	type;
    _Uint16t	zero;
	pid_t	pid;
};

typedef union {
	struct _proc_getpid64	i;
	pid64_t					o;
} proc_getpid64_t;

/* 
 * _PROC_GETNAME
 */

/********************************/
/* struct _proc_getname		*/
/********************************/
struct _proc_getname {
	_Uint16t		type;
	_Uint16t		zero;
	_Uint32t		reserved;
	pid64_t			pid;
};


/********************************/
/* proc_getname_t	            */
/********************************/
typedef union {
	struct _proc_getname	i;
	char					o;
} proc_getname_t;
/*
 * Message of _PROC_GET_ALL_PID
 */
struct _proc_getallpid {
    _Uint16t	type;
    _Uint16t	zero;
};

typedef union {
	struct _proc_getallpid	i;
	pid64_t 				o[0];		/* dynamic array of pids */
} proc_getallpid_t;


/*
 * Message of _PROC_GET_ALL_CHILD_PID
 */
struct proc_get_all_child_pid {
    _Uint16t type;
    _Uint16t zero;
    _Uint32t reserved;
    pid64_t pid;
};

typedef union {
    struct proc_get_all_child_pid i;
    pid64_t o[0]; /* dynamic array of pids */
} proc_get_all_child_pid_t;

#include "debug.h"


/*
 * Messages of _PROC_DEBUG
 */

/********************************/
/* _PROC_DEBUG subtypes 		*/
/********************************/
enum {
	_PROC_DEBUG_PROC_INFO,		/* return data of a single process */
	_PROC_DEBUG_GET_GENERAL_REGS,
	_PROC_DEBUG_GET_FP_REGS,
	_PROC_DEBUG_THREAD_STATUS,
};

/********************************/
/* struct _debug   				*/
/********************************/
typedef struct _proc_debug {
	_Uint16t	type;
	_Uint16t	subtype;
	unsigned	tid;
	pid64_t		pid;
} proc_debug_i_t;



/********************************/
/* proc_debug_t		            */
/********************************/
typedef union {
	struct _proc_debug 					i;
	debug_process_t					 	o_proc_info;
	debug_greg_t						o_general_regs;
	debug_fpreg_t						o_fp_regs;
	debug_thread_t						o_thread_status;
} proc_debug_t;



/*
 * Messages of _PROC_COREDUMP
 */

/********************************/
/* _PROC_COREDUMP subtypes 		*/
/********************************/
enum {
	_PROC_COREDUMP_REGISTER_EVENT,	/* register an event to be fired in case of a fault */
	_PROC_COREDUMP_CONT_TERM		/* continue termination of a dumping process */
};

/********************************/
/* struct _proc_coredump		*/
/********************************/
typedef struct _proc_coredump {
	_Uint16t		type;
	_Uint16t		subtype;
	_Uint32t		reserved;
	pid64_t			pid;
	union {
		struct sigevent	event;
		_Int32t         status; /*  result of the core file creation */
	};
} proc_coredump_i_t;


/********************************/
/* proc_coredump_t	            */
/********************************/
typedef union {
	struct _proc_coredump				i;
} proc_coredump_t;


#include _NTO_HDR_(_packpop.h)

#endif
