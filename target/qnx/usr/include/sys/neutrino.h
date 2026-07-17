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

#ifndef __NEUTRINO_H_INCLUDED
#define __NEUTRINO_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
# include <sys/platform.h>
#endif

#ifndef __TYPES_H_INCLUDED
# include _NTO_HDR_(sys/types.h)
#endif

#ifndef _SIGNAL_H_INCLUDED
# include _NTO_HDR_(signal.h)
#endif

#if defined(__EXT_POSIX1_199309) || defined(__EXT_POSIX1_199506) || defined(__EXT_POSIX1_200112)
/* We really shouldn't include sched.h at all since nothing in neutrino.h depends
 * on it.  However, we did before so for backwards compatibility we must continue
 * to do so.  But, sched.h is only supported in and after POSIX-1993, so in order
 * to compile in older environments we only include sched.h in those later versions.
 */
# ifndef _SCHED_H_INCLUDED
#  include _NTO_HDR_(sched.h)
# endif
#endif

#ifndef _TIME_H_INCLUDED
# include _NTO_HDR_(time.h)
#endif

#ifndef _LIMITS_H_INCLUDED
# include _NTO_HDR_(limits.h)
#endif

#ifndef __STORAGE_H_INCLUDED
# include _NTO_HDR_(sys/storage.h)
#endif

#ifndef __STATES_H_INCLUDED
# include _NTO_HDR_(sys/states.h)
#endif

#ifndef __INTERRUPTS_H_INCLUDED
# include _NTO_HDR_(sys/interrupts.h)
#endif

#ifndef __KPIPE_H_INCLUDED
# include _NTO_HDR_(sys/kpipe.h)
#endif

#if defined(__SYNC_T)
typedef __SYNC_T        sync_t;
# undef __SYNC_T
#endif

#if defined(__SYNC_ATTR_T)
typedef __SYNC_ATTR_T   sync_attr_t;
# undef __SYNC_ATTR_T
#endif

#if defined(__SCHED_PARAM_T)
typedef __SCHED_PARAM_T sched_param_t;
# undef __SCHED_PARAM_T
#endif

#if defined(__PTHREAD_ATTR_T)
typedef __PTHREAD_ATTR_T    pthread_attr_t;
# undef __PTHREAD_ATTR_T
#endif

#if defined(__PTHREAD_ATTR_T32)
__PTHREAD_ATTR_T32;
# undef __PTHREAD_ATTR_T32
#endif

#if defined(__PTHREAD_ATTR_T64)
__PTHREAD_ATTR_T64;
# undef __PTHREAD_ATTR_T64
#endif

#include _NTO_HDR_(sys/nto_version.h)

#define SYSMGR_PID      1
#define SYSMGR_CHID     1
#define SYSMGR_COID     ((int)_NTO_SIDE_CHANNEL)    /* System process connection is always the first side channel */
#define SYSMGR_HANDLE   0

typedef struct intrspin {
    volatile unsigned   value;
} intrspin_t;

#define __RCVID_T_SIZE  8
typedef _Int64t         rcvid_t;

__BEGIN_DECLS

#include _NTO_CPU_HDR_(neutrino.h)

#include _NTO_HDR_(_pack64.h)

typedef sync_t      nto_job_t;

#define _NTO_TIMEOUT_FLAG(__state)  ((_Uint32t)1 << (__state))
#define _NTO_TIMEOUT_RECEIVE        _NTO_TIMEOUT_FLAG(STATE_RECEIVE)
#define _NTO_TIMEOUT_SEND           _NTO_TIMEOUT_FLAG(STATE_SEND)
#define _NTO_TIMEOUT_REPLY          _NTO_TIMEOUT_FLAG(STATE_REPLY)
#define _NTO_TIMEOUT_MQ_SEND        _NTO_TIMEOUT_FLAG(STATE_MQ_SEND)
#define _NTO_TIMEOUT_MQ_RECEIVE     _NTO_TIMEOUT_FLAG(STATE_MQ_RECEIVE)
#define _NTO_TIMEOUT_SIGSUSPEND     _NTO_TIMEOUT_FLAG(STATE_SIGSUSPEND)
#define _NTO_TIMEOUT_SIGWAITINFO    _NTO_TIMEOUT_FLAG(STATE_SIGWAITINFO)
#define _NTO_TIMEOUT_NANOSLEEP      _NTO_TIMEOUT_FLAG(STATE_NANOSLEEP)
#define _NTO_TIMEOUT_MUTEX          _NTO_TIMEOUT_FLAG(STATE_MUTEX)
#define _NTO_TIMEOUT_CONDVAR        _NTO_TIMEOUT_FLAG(STATE_CONDVAR)
#define _NTO_TIMEOUT_BARRIER        _NTO_TIMEOUT_FLAG(STATE_BARRIER)
#define _NTO_TIMEOUT_JOIN           _NTO_TIMEOUT_FLAG(STATE_JOIN)
#define _NTO_TIMEOUT_INTR           _NTO_TIMEOUT_FLAG(STATE_INTR)
#define _NTO_TIMEOUT_SEM            _NTO_TIMEOUT_FLAG(STATE_SEM)
#define _NTO_TIMEOUT_RWLOCK_READ    _NTO_TIMEOUT_FLAG(STATE_RWLOCK_READ)
#define _NTO_TIMEOUT_RWLOCK_WRITE   _NTO_TIMEOUT_FLAG(STATE_RWLOCK_WRITE)
#define _NTO_TIMEOUT_PIPE           _NTO_TIMEOUT_FLAG(STATE_PIPE)


/* The _msg_info_hdr is intended to be the common subset of the 32 and 64 bit
   _msg_info structures.  The layout/content of _msg_info_hdr must always
   match the initial portion of both of the other two _msg_info[32|64].
*/
struct _msg_info_hdr {                      /* _msg_info    _server_info */
    _Uint32t                    nd;         /*  client      server */
    _Uint32t                    srcnd;      /*  server      n/a */
    pid_t                       pid;        /*  client      server */
    _Int32t                     tid;        /*  thread      n/a */
    _Int32t                     chid;       /*  server      server */
    _Int32t                     scoid;      /*  server      server */
    _Int32t                     coid;       /*  client      client */
};

struct _msg_info32 {                        /* _msg_info    _server_info */
    _Uint32t                    nd;         /*  client      server */
    _Uint32t                    srcnd;      /*  server      n/a */
    pid_t                       pid;        /*  client      server */
    _Int32t                     tid;        /*  thread      n/a */
    _Int32t                     chid;       /*  server      server */
    _Int32t                     scoid;      /*  server      server */
    _Int32t                     coid;       /*  client      client */
    _Ssize32t                   msglen;     /*  msg         n/a */
    _Ssize32t                   srcmsglen;  /*  thread      n/a */
    _Ssize32t                   dstmsglen;  /*  thread      n/a */
    _Int16t                     priority;   /*  thread      n/a */
    _Int16t                     flags;      /*  n/a         client */
    _Uint32t                    type_id;    /*  client      server channel */
};

struct _msg_info64 {                        /* _msg_info    _server_info */
    _Uint32t                    nd;         /*  client      server */
    _Uint32t                    srcnd;      /*  server      n/a */
    pid_t                       pid;        /*  client      server */
    _Int32t                     tid;        /*  thread      n/a */
    _Int32t                     chid;       /*  server      server */
    _Int32t                     scoid;      /*  server      server */
    _Int32t                     coid;       /*  client      client */
    _Int16t                     priority;   /*  thread      n/a */
    _Int16t                     flags;      /*  n/a         client */
    _Ssize64t                   msglen;     /*  msg         n/a */
    _Ssize64t                   srcmsglen;  /*  thread      n/a */
    _Ssize64t                   dstmsglen;  /*  thread      n/a */
    _Uint32t                    type_id;    /*  client      server channel */
    _Uint32t                    reserved;
};
/* <STAN_MACRO1> */
#if __PTR_BITS__ <= 32
    #define _msg_info   _msg_info32
#else
    #define _msg_info   _msg_info64
#endif
#define _server_info32  _msg_info32
#define _server_info64  _msg_info64
#define _server_info    _msg_info
/* </STAN_MACRO1> */

#define _NTO_MI_ENDIAN_BIG      0x00000001u /* Same as _NTO_CI_ENDIAN_BIG */
#define _NTO_MI_ENDIAN_DIFF     0x00000002u
#define _NTO_MI_UNBLOCK_REQ     0x00000100u
#define _NTO_MI_NET_CRED_DIRTY  0x00000200u
// Available                    0x00000400u
#define _NTO_MI_CHROOT          0x00000800u /* Client process has been chrooted - Same as _NTO_CI_CHROOT */
#define _NTO_MI_BITS_64         0x00001000u /* Same as _NTO_CI_BITS_64 */
#define _NTO_MI_BITS_DIFF       0x00002000u

/*
 * _cred_info and _client_info
 *
 * These structures are defined with a fixed-sized grouplist field
 * for backwards compatibility.  However, they are often used with
 * an arbitrary-sized grouplist field.  As such, the grouplist field
 * must come at the end of the structures.
 */
struct _cred_info {
    uid_t                       ruid;
    uid_t                       euid;
    uid_t                       suid;
    gid_t                       rgid;
    gid_t                       egid;
    gid_t                       sgid;
    _Uint32t                    ngroups;
    gid_t                       grouplist[__NGROUPS_MAX];
};

struct _client_info {
    _Uint32t                    nd;
    pid_t                       pid;
    pid_t                       sid;
    _Uint32t                    flags;
    struct _cred_info           cred;
};

/*
 * See <sys/clientinfo.h>.  There you will find macros for
 * declaring and determining the size of variable-sized
 * _cred_info and _client_info structures.
 */

#define _NTO_CI_ENDIAN_BIG          0x00000001U /* Same as _NTO_MI_ENDIAN_BIG */
#define _NTO_CI_BKGND_PGRP          0x00000004U
#define _NTO_CI_ORPHAN_PGRP         0x00000008U
#define _NTO_CI_STOPPED             0x00000080U
#define _NTO_CI_UNABLE              0x00000100U /* Failed ability check */
#define _NTO_CI_TYPE_ID             0x00000200U /* type id follows last supplementary group */
#define _NTO_CI_CHROOT              0x00000800U /* Same as _NTO_MI_CHROOT */
#define _NTO_CI_LOADER              0x00008000U /* Loader thread */
#define _NTO_CI_GROUPS_INFO_ONLY    0x40000000U /* ngroups only states how many groups client has, not content of grouplist */
#define _NTO_CI_FULL_GROUPS         0x80000000U /* indicates ngroups/grouplist contain complete info */

struct _client_able {
    _Uint32t ability;
    _Uint32t flags;
    _Uint64t range_lo;
    _Uint64t range_hi;
};

struct _vtid_info {
    _Int32t     tid;
    _Int32t     coid;
    _Int32t     priority;
    _Ssizet     srcmsglen;
    _Int32t     zero2;
    _Int32t     srcnd;
    _Ssizet     dstmsglen;
    _Int32t     zero;
};

#define _NTO_TIMER_SEARCH           0x00000001
#define _NTO_TIMER_RESET_OVERRUNS   0x00000002
#define _NTO_TIMER_SUPPORT_64BIT    0x00000004

#if defined(__CLOCKADJUST)
struct _clockadjust __CLOCKADJUST;
#undef __CLOCKADJUST
#endif

#if defined(__ITIMER)
struct _itimer __ITIMER;
#undef __ITIMER
#endif

#ifdef __TIMER_INFO
struct _timer_info   __TIMER_INFO;
struct _timer_info32 __TIMER_INFO;
struct _timer_info64 __TIMER_INFO;
#undef __TIMER_INFO
#endif

struct _sighandler_info {
    siginfo_t           siginfo;
    __sa_handler_func_t *handler;
    void                *context;
    /* void             data[] */
};

struct _sched_info {
    int                 priority_min;
    int                 priority_max;
    _Uint64t            interval;
    int                 priority_priv;
    int                 reserved[11];
};

// Timer flags.
//
// Some are states, some are behaviours programmed at either timer creating
// time or arming time, some are only for info returned to applications.

// Timer states.
#define _NTO_TI_ACTIVE              0x00000001u
                                    // mind the gap
#define _NTO_TI_EXPIRED             0x00000004u
#define _NTO_TI_STATE_MASK          (_NTO_TI_ACTIVE|_NTO_TI_EXPIRED)

// Flags to track behaviours programmed when setting the time.
#define _NTO_TI_ABSOLUTE            0x00000002u
                                    // mind the gap
#define _NTO_TI_TOD_BASED           0x00000008u
                                    // mind the gap
#define _NTO_TI_PRECISE             0x00000040u
#define _NTO_TI_TIMER_SETTIME_MASK  (_NTO_TI_ABSOLUTE|_NTO_TI_TOD_BASED|_NTO_TI_PRECISE)

// Flags to track behaviours programmed when creating the timer.
#define _NTO_TI_TARGET_PROCESS      0x00000010u
#define _NTO_TI_TIMER_CREATE_MASK   (_NTO_TI_TARGET_PROCESS)

// Used to report info to applications.
#define _NTO_TI_REPORT_TOLERANCE    0x00000020u
                                    // mind the gap
#define _NTO_TI_TOLERANT            0x00000080u
#define _NTO_TI_WAKEUP              0x00000100u
#define _NTO_TI_PROCESS_TOLERANT    0x00000200u
#define _NTO_TI_HIGH_RESOLUTION     0x00000400u
#define _NTO_TI_INFO_MASK           (_NTO_TI_REPORT_TOLERANCE|_NTO_TI_TOLERANT| \
                                     _NTO_TI_WAKEUP|_NTO_TI_PROCESS_TOLERANT| \
                                     _NTO_TI_HIGH_RESOLUTION)

/* TimerDelegate() actions */
#define _NTO_TIMER_DELEGATE          1U
#define _NTO_TIMER_RECLAIM           2U
#define _NTO_TIMER_QUERY_DELEGATE    3U

/*
 * Definitions for type and subtype of any pulse.
 * We keep the codes away from the defined SI_ signal codes to prevent
 * confusion.
 */
#define _PULSE_TYPE                 0
#define _PULSE_SUBTYPE              0
#define _PULSE_CODE_UNBLOCK         (-32)   /* value - rcvid */
#define _PULSE_CODE_DISCONNECT      (-33)   /* value - not used, use scoid (server connection) */
#define _PULSE_CODE_THREADDEATH     (-34)   /* value - thread id */
#define _PULSE_CODE_COIDDEATH       (-35)   /* value - coid */
#define _PULSE_CODE_NET_ACK         (-36)   /* value - vtid; not in use anymore */
#define _PULSE_CODE_NET_UNBLOCK     (-37)   /* value - vtid */
#define _PULSE_CODE_NET_DETACH      (-38)   /* value - coid */
#define _PULSE_CODE_RESTART         (-39)   /* value - cookie */
#define _PULSE_CODE_NORESTART       (-40)   /* value - cookie */
#define _PULSE_CODE_UNBLOCK_RESTART (-41)   /* value - rcvid */
#define _PULSE_CODE_UNBLOCK_TIMER   (-42)   /* value - rcvid */
#define _PULSE_CODE_PIPE_INPUT      (-43)   /* value - data available */
#define _PULSE_CODE_PIPE_OUTPUT     (-44)   /* value - space available */

/*
 * Values within this range will not be delivered by the system unless
 * requested. Values outside this range are soft-reserved for system usage.
 * (They may be sent but services may react in unexpected ways.)
 */
#define _PULSE_CODE_MINAVAIL    0
#define _PULSE_CODE_MAXAVAIL    127

struct _pulse {
    _Uint16t                    type;
    _Uint16t                    subtype;
    _Int8t                      code;
    _Uint8t                     zero[3];
    union sigval                value;
    _Int32t                     scoid;
};

/*
 * Define interrupt flags.
 */
#define _NTO_HARD_FLAGS_END     0x01

/*
 * Define flags which can be applied to a pulse type.
 */
#define _NTO_PULSE_IF_UNIQUE    0x1000
#define _NTO_PULSE_REPLACE      0x2000

/*
 * Define the flags of a process PROCESS.flags
 */
#define _NTO_PF_NOCLDSTOP       0x00000001u
#define _NTO_PF_LOADING         0x00000002u
#define _NTO_PF_TERMING         0x00000004u
#define _NTO_PF_ZOMBIE          0x00000008u
#define _NTO_PF_NOZOMBIE        0x00000010u
#define _NTO_PF_FORKED          0x00000020u
// Available                    0x00000040u
#define _NTO_PF_STOPPED         0x00000080u
#define _NTO_PF_DEBUG_STOPPED   0x00000100u
#define _NTO_PF_BKGND_PGRP      0x00000200u
#define _NTO_PF_NOISYNC         0x00000400u
#define _NTO_PF_CONTINUED       0x00000800u
#define _NTO_PF_CHECK_INTR      0x00001000u
#define _NTO_PF_COREDUMP        0x00002000u
#define _NTO_PF_SPAWN_HELD      0x00004000u
// Available                    0x00008000u
#define _NTO_PF_SLEADER         0x00010000u
#define _NTO_PF_WAITINFO        0x00020000u
// Available                    0x00040000u
#define _NTO_PF_KILL_REQUEST    0x00080000u
#define _NTO_PF_NOCOREDUMP      0x00100000u
#define _NTO_PF_CORE_REQUEST    0x00200000u
#define _NTO_PF_WAITDONE        0x00400000u
// Available                    0x00800000u
#define _NTO_PF_ASLR            0x01000000u
#define _NTO_PF_EXECED          0x02000000u
#define _NTO_PF_APP_STOPPED     0x04000000u
#define _NTO_PF_64BIT           0x08000000u
#define _NTO_PF_COREDUMP_WAIT   0x10000000u
// Available                    0x20000000u
#define _NTO_PF_NOEXEC_STACK    0x40000000u
#define _NTO_PF_LOADER_PERMS    0x80000000u

/*
 * Thread Control commands
 */
#define _NTO_TCTL_IO_PRIV               1
#define _NTO_TCTL_THREADS_HOLD          2
#define _NTO_TCTL_THREADS_CONT          3
#define _NTO_TCTL_RUNMASK               4
#define _NTO_TCTL_ALIGN_FAULT           5
#define _NTO_TCTL_RUNMASK_GET_AND_SET   6
#define _NTO_TCTL_RUNMASK_GET_AND_SET_64    7
#define _NTO_TCTL_ONE_THREAD_HOLD       8
#define _NTO_TCTL_ONE_THREAD_CONT       9
#define _NTO_TCTL_RUNMASK_GET_AND_SET_INHERIT   10
#define _NTO_TCTL_NAME                  11
// Available                            12
// Available                            13
#define _NTO_TCTL_IO                    14
// Available                            15
// Available                            16
#define _NTO_TCTL_ADD_EXIT_EVENT        17
#define _NTO_TCTL_DEL_EXIT_EVENT        18
#define _NTO_TCTL_IO_LEVEL              19
// Available                            20
// Available                            21
// Available                            22
#define _NTO_TCTL_SIGSTACK              23
#define _NTO_TCTL_TLS_SET_TP            24
#define _NTO_TCTL_HYP_VCPU              25

#define _NTO_TCTL_RESERVED              0x80000000u
#define _NTO_TCTL_IO_LEVEL_INHERIT      0x40000000u

#define _NTO_IO_LEVEL_NONE      1u
#define _NTO_IO_LEVEL_1         2u
#define _NTO_IO_LEVEL_2         3u

/*
 * Channel Control commands
 */
#define _NTO_CCTL_PULSE_POOL            1
#define _NTO_CCTL_WIDE                  2
// Available                            3
#define _NTO_CCTL_NOTIFY_SEND           4
#define _NTO_CCTL_SERVER_BOOST_THREAD   5

/*
 * Limit on the maximum number of characters for a thread name
 */
#define _NTO_THREAD_NAME_MAX            100

struct _thread_name {
    int     new_name_len;
    int     name_buf_len;
    __FLEXARY(char, name_buf); /* char name_buf[] */
};

/*
 * Where 'size' must be the precise value required
 * to define the number of cpus currently on the
 * system: eg. RMSK_SIZE(_syspage_ptr->num_cpu).
 */
struct _thread_runmask {
    int         size;
    /*  unsigned    runmask[size];      */
    /*  unsigned    inherit_mask[size]; */
};

#define RMSK_SIZE(num_cpu)  (((num_cpu) - 1) / __INT_BITS__ + 1)

/* Where 'cpu' is zero based */
#define RMSK_SET(cpu, p)    ((p)[(cpu) / __INT_BITS__] |=   \
                             (1 << ((cpu) % __INT_BITS__)))

#define RMSK_CLR(cpu, p)    ((p)[(cpu) / __INT_BITS__] &=       \
                             ~(1 << ((cpu) % __INT_BITS__)))

#define RMSK_ISSET(cpu, p)  ((p)[(cpu) / __INT_BITS__] &    \
                             (1 << ((cpu) % __INT_BITS__)))


#define NTONET_KIF_VERSION              0x1 /* current kif version */


/*
 * Define channel flags
 */
#define _NTO_CHF_FIXED_PRIORITY     0x0001u
#define _NTO_CHF_UNBLOCK            0x0002u
#define _NTO_CHF_THREAD_DEATH       0x0004u
#define _NTO_CHF_DISCONNECT         0x0008u
#define _NTO_CHF_NET_MSG            0x0010u
#define _NTO_CHF_SENDER_LEN         0x0020u
#define _NTO_CHF_COID_DISCONNECT    0x0040u
#define _NTO_CHF_REPLY_LEN          0x0080u
#define _NTO_CHF_PULSE_POOL         0x0100u
// Available                        0x0200u
// Available                        0x0400u
#define _NTO_CHF_GLOBAL             0x0800u
#define _NTO_CHF_PRIVATE            0x1000u
#define _NTO_CHF_MSG_PAUSING        0x2000u
#define _NTO_CHF_INHERIT_RUNMASK    0x4000u
#define _NTO_CHF_UNBLOCK_TIMER      0x8000u

#define _NTO_CHO_CUSTOM_EVENT       0x00000001u

struct nto_channel_config {
    struct sigevent event;
    unsigned num_pulses;
    unsigned rearm_threshold;
    unsigned options;
    unsigned reserved[3];
};

/*
 * Define connect flags
 */
#define _NTO_COF_CLOEXEC        0x0001U
#define _NTO_COF_DEAD           0x0002U
#define _NTO_COF_NOINHERIT      0x0004U
#define _NTO_COF_LOCAL          0x0008U
// Available                    0x0010U
// Available                    0x0020U
#define _NTO_COF_NOSHARE        0x0040U
#define _NTO_COF_ALLOWED        0x0080U
// Available                    0x0100U
// Available                    0x0200U
#define _NTO_COF_PIPE           0x0400U
#define _NTO_COF_NOEVENT        0x0800U
// Available                    0x1000U
#define _NTO_COF_REG_EVENTS     0x2000U
// Available                    0x4000U
#define _NTO_COF_DUP2           0x8000U
#define _NTO_COF_MASK           0xffffU

/* If the 2nd from top bit is set then we don't use the fd connection vector. */
#define _NTO_SIDE_CHANNEL       0x40000000U

/* scoids are marked with this bit */
#define _NTO_CONNECTION_SCOID   0x00010000U


/* If the 2nd from top bit is set in the channel id, then it is a global channel. */
#define _NTO_GLOBAL_CHANNEL     0x40000000

/* MsgRegisterEvent special coid values */
#define _NTO_REGEVENT_ALLOW_ANY_SERVER  (-1)
#define _NTO_REGEVENT_ALLOW_SELF        (-2)

/*
 * Define flags of a timeout
 * The first n bits are reserved for (1L << thp->state)
 */
#define _NTO_TIMEOUT_MASK       (((unsigned)1 << STATE_TIMEOUT_MAX) - 1u)
#define _NTO_TIMEOUT_ACTIVE     ((unsigned)1 << STATE_TIMEOUT_MAX)
#define _NTO_TIMEOUT_NO_WAIT    ((unsigned)1 << (STATE_TIMEOUT_MAX + 1u))


/*
 * InterruptCharacteristic types
 */
#define _NTO_IC_LATENCY                 0

/*
 * Flag bits for InterruptAttach[Event]
 */
#define _NTO_INTR_FLAGS_END             0x00000001u
#define _NTO_INTR_FLAGS_NO_UNMASK       0x00000002u
#define _NTO_INTR_FLAGS_PROCESS         0x00000004u
#define _NTO_INTR_FLAGS_TRK_MSK         0x00000008u
#define _NTO_INTR_FLAGS_ARRAY           0x00000010u
#define _NTO_INTR_FLAGS_EXCLUSIVE       0x00000020u
#define _NTO_INTR_FLAGS_FPU             0x00000040u  //handler do FPU/SIMD, internal use for now.
#define _NTO_INTR_FLAGS_CPU_LOCAL       0x00000080u
#define _NTO_INTR_FLAGS_EVENT_PRIORITY  0x00000100u
#define _NTO_INTR_FLAGS_INTERNAL_MASK   0xff000000u

/*
 * Flag bits for InterruptWait()
 */
#define _NTO_INTR_WAIT_FLAGS_FAST   0x000000001U
#define _NTO_INTR_WAIT_FLAGS_UNMASK 0x000000002U

/*
 * System independent interrupt classes for InterruptAttach[Event]
 */
#define _NTO_INTR_CLASS_EXTERNAL    0x00000000u
#define _NTO_INTR_CLASS_SYNTHETIC   0x7fff0000u

#define _NTO_INTR_SPARE         (_NTO_INTR_CLASS_SYNTHETIC|0xffffu)

#define _NTO_HOOK_TRACE         (_NTO_INTR_CLASS_SYNTHETIC|0u)
#define _NTO_HOOK_IDLE          (_NTO_INTR_CLASS_SYNTHETIC|1u)
#define _NTO_HOOK_OVERDRIVE     (_NTO_INTR_CLASS_SYNTHETIC|2u)
#define _NTO_HOOK_LAST          (_NTO_INTR_CLASS_SYNTHETIC|2u)
#define _NTO_HOOK_IDLE2_FLAG    0x8000u

/*
 * Idle Hook Control structure
 */
struct _idle_hook {
    unsigned        hook_size;
    unsigned        cmd;
    unsigned        mode;
    unsigned        latency;
    _Uint64t        next_fire;
    _Uint64t        curr_time;
    _Uint64t        tod_adjust;
    unsigned        resp;
    struct {
        unsigned        length;
        unsigned        scale;
    }               time;
    struct sigevent trigger;
    unsigned        *intrs;
    unsigned        block_stack_size;
};

struct _clockperiod {
    _Uint32t                    nsec;
    _Int32t                     fract;
};


/*
 * Sync Control commands
 */
#define _NTO_SCTL_SETPRIOCEILING    1       /* mutex    const int *prioceiling */
#define _NTO_SCTL_GETPRIOCEILING    2       /* mutex    int *prioceiling */
#define _NTO_SCTL_SETEVENT          3       /* mutex    struct sigevent *event */
#define _NTO_SCTL_MUTEX_WAKEUP      4       /* mutex    wakeup thread blocking on mutex */
#define _NTO_SCTL_MUTEX_CONSISTENT  5       /* mutex    pthread_mutex_consistent() */
#define _NTO_SCTL_SEM_VALUE         6       /* named semaphore  sem_getvalue() */

/*
 * Read/write lock operations
 */
#define _NTO_RWLOCK_READ_LOCK       0U
#define _NTO_RWLOCK_READ_TRYLOCK    1U
#define _NTO_RWLOCK_READ_UNLOCK     2U
#define _NTO_RWLOCK_WRITE_LOCK      3U
#define _NTO_RWLOCK_WRITE_UNLOCK    4U
#define _NTO_RWLOCK_WRITE_TRYLOCK   5U

/*
 * ConnectClientInfoExt flags
 */
#define _NTO_CLIENTINFO_GETGROUPS 1
#define _NTO_CLIENTINFO_GETTYPEID 2

/*
 * ConnectDupFd operations
 */
#define _NTO_DUPFD_REGISTER         1
#define _NTO_DUPFD_REGISTER_DISC    2
#define _NTO_DUPFD_UNREGISTER       3
#define _NTO_DUPFD_LOOKUP           4
#define _NTO_DUPFD_VERIFY           5

typedef _Uint64t  dupfd_handle_t;

struct iovec;
struct _asyncmsg_connection_descriptor;
union _channel_connect_attr;

/*
 * MsgQueueCtl() commands
 */
#define _NTO_MQCTL_NOTIFY       1
#define _NTO_MQCTL_GETATTR      2
#define _NTO_MQCTL_SETATTR      3
#define _NTO_MQCTL_GETBUFSIZE   4

struct _mqctl_getbufsize {
    union {
        struct {
            _Uint32t __maxmsg;
            _Uint32t __msgsize;
        } __in;
        struct {
            _Sizet __bufsize;
        } __out;
    };
};

/*
 * Structure used in calls to SyncCtl(_NTO_SCTL_MUTEX_WAKEUP)
 */
struct _sync_ctl_wakeup
{
    pid_t   __pid;
    int     __tid;
};

/*
 * Function prototypes for all kernel calls.
 */
extern int ChannelCreate(unsigned __flags);
extern int ChannelCreate_r(unsigned __flags);
extern int ChannelCreatePulsePool(unsigned __flags, struct nto_channel_config const*__config);
extern int ChannelDestroy(int __chid);
extern int ChannelDestroy_r(int __chid);
extern int ChannelCtl(int __chid, int __cmd, void *data);
extern int ChannelCtl_r(int __chid, int __cmd, void *data);
extern int ConnectAttach(_Uint32t __nd, pid_t __pid, int __chid, unsigned __index, int __flags);
extern int ConnectAttach_r(_Uint32t __nd, pid_t __pid, int __chid, unsigned __index, int __flags);
extern int ConnectAttachExt(_Uint32t __nd, pid_t __pid, int __chid, unsigned __index, int __flags, struct _asyncmsg_connection_descriptor *__cd);
extern int ConnectDetach(int __coid);
extern int ConnectDetach_r(int __coid);
extern int ConnectServerInfo(pid_t __pid, int __coid, struct _server_info *__info);
extern int ConnectServerInfo_r(pid_t __pid, int __coid, struct _server_info *__info);
extern int ConnectClientInfoExtraArgs(int __scoid, struct _client_info *__info_pp, int __ngroups, struct _client_able *__abilities, int __nable, unsigned *__type_id);
extern int ConnectClientInfoExtraArgs_r(int __scoid, struct _client_info *__info_pp, int __ngroups, struct _client_able *__abilities, int __nable, unsigned *__type_id);
extern int ConnectClientInfo(int __scoid, struct _client_info *__info, int __ngroups);
extern int ConnectClientInfo_r(int __scoid, struct _client_info *__info, int __ngroups);
extern int ConnectClientInfoExt(int __scoid, struct _client_info **__info_pp, int flags);
extern int ClientInfoExtFree(struct _client_info **__info_pp);
extern int ConnectClientInfoAble(int __scoid, struct _client_info **__info_pp, int flags, struct _client_able * const abilities, const int nable);
extern int ConnectFlags(pid_t __pid, int __coid, unsigned __mask, unsigned __bits);
extern int ConnectFlags_r(pid_t __pid, int __coid, unsigned __mask, unsigned __bits);
extern int ConnectDupFd(int __op, pid64_t *__dstpid, dupfd_handle_t *__handle, pid_t *__srvpid, struct _msg_info_hdr *__info);
extern int ConnectDupFd_r(int __op, pid64_t *__dstpid, dupfd_handle_t *__handle, pid_t *__srvpid, struct _msg_info_hdr *__info);
extern int ChannelConnectAttr(unsigned __id, union _channel_connect_attr *__old_attr, union _channel_connect_attr *__new_attr, unsigned __flags);

extern long MsgSend(int __coid, const void *__smsg, _Sizet __sbytes, void *__rmsg, _Sizet __rbytes);
extern long MsgSend_r(int __coid, const void *__smsg, _Sizet __sbytes, void *__rmsg, _Sizet __rbytes);
extern long MsgSendnc(int __coid, const void *__smsg, _Sizet __sbytes, void *__rmsg, _Sizet __rbytes);
extern long MsgSendnc_r(int __coid, const void *__smsg, _Sizet __sbytes, void *__rmsg, _Sizet __rbytes);
extern long MsgSendsv(int __coid, const void *__smsg, _Sizet __sbytes, const struct iovec *__riov, _Sizet __rparts);
extern long MsgSendsv_r(int __coid, const void *__smsg, _Sizet __sbytes, const struct iovec *__riov, _Sizet __rparts);
extern long MsgSendsvnc(int __coid, const void *__smsg, _Sizet __sbytes, const struct iovec *__riov, _Sizet __rparts);
extern long MsgSendsvnc_r(int __coid, const void *__smsg, _Sizet __sbytes, const struct iovec *__riov, _Sizet __rparts);
extern long MsgSendvs(int __coid, const struct iovec *__siov, _Sizet __sparts, void *__rmsg, _Sizet __rbytes);
extern long MsgSendvs_r(int __coid, const struct iovec *__siov, _Sizet __sparts, void *__rmsg, _Sizet __rbytes);
extern long MsgSendvsnc(int __coid, const struct iovec *__siov, _Sizet __sparts, void *__rmsg, _Sizet __rbytes);
extern long MsgSendvsnc_r(int __coid, const struct iovec *__siov, _Sizet __sparts, void *__rmsg, _Sizet __rbytes);
extern long MsgSendv(int __coid, const struct iovec *__siov, _Sizet __sparts, const struct iovec *__riov, _Sizet __rparts);
extern long MsgSendv_r(int __coid, const struct iovec *__siov, _Sizet __sparts, const struct iovec *__riov, _Sizet __rparts);
extern long MsgSendvnc(int __coid, const struct iovec *__siov, _Sizet __sparts, const struct iovec *__riov, _Sizet __rparts);
extern long MsgSendvnc_r(int __coid, const struct iovec *__siov, _Sizet __sparts, const struct iovec *__riov, _Sizet __rparts);
extern rcvid_t MsgReceive(int __chid, void *__msg, _Sizet __bytes, struct _msg_info *__info);
extern rcvid_t MsgReceive_r(int __chid, void *__msg, _Sizet __bytes, struct _msg_info *__info);
extern rcvid_t MsgReceivev(int __chid, const struct iovec *__iov, _Sizet __parts, struct _msg_info *__info);
extern rcvid_t MsgReceivev_r(int __chid, const struct iovec *__iov, _Sizet __parts, struct _msg_info *__info);
extern int MsgReceivePulse(int __chid, void *__pulse, _Sizet __bytes, struct _msg_info *__info);
extern int MsgReceivePulse_r(int __chid, void *__pulse, _Sizet __bytes, struct _msg_info *__info);
extern int MsgReply(rcvid_t __rcvid, long __status, const void *__msg, _Sizet __bytes);
extern int MsgReply_r(rcvid_t __rcvid, long __status, const void *__msg, _Sizet __bytes);
extern int MsgReplyv(rcvid_t __rcvid, long __status, const struct iovec *__iov, _Sizet __parts);
extern int MsgReplyv_r(rcvid_t __rcvid, long __status, const struct iovec *__iov, _Sizet __parts);
extern ssize_t MsgRead(rcvid_t __rcvid, void *__msg, _Sizet __bytes, _Sizet __offset);
extern ssize_t MsgRead_r(rcvid_t __rcvid, void *__msg, _Sizet __bytes, _Sizet __offset);
extern ssize_t MsgReadv(rcvid_t __rcvid, const struct iovec *__iov, _Sizet __parts, _Sizet __offset);
extern ssize_t MsgReadv_r(rcvid_t __rcvid, const struct iovec *__iov, _Sizet __parts, _Sizet __offset);
extern ssize_t MsgWrite(rcvid_t __rcvid, const void *__msg, _Sizet __bytes, _Sizet __offset);
extern ssize_t MsgWrite_r(rcvid_t __rcvid, const void *__msg, _Sizet __bytes, _Sizet __offset);
extern ssize_t MsgWritev(rcvid_t __rcvid, const struct iovec *__iov, _Sizet __parts, _Sizet __offset);
extern ssize_t MsgWritev_r(rcvid_t __rcvid, const struct iovec *__iov, _Sizet __parts, _Sizet __offset);
extern int MsgSendPulse(int __coid, int __priority, int __code, long  __value);
extern int MsgSendPulse_r(int __coid, int __priority, int __code, long  __value);
extern int MsgSendPulsePtr(int __coid, int __priority, int __code, void *  __value);
extern int MsgSendPulsePtr_r(int __coid, int __priority, int __code, void *  __value);
extern int MsgDeliverEvent(rcvid_t __rcvid, const struct sigevent *__event);
extern int MsgDeliverEvent_r(rcvid_t __rcvid, const struct sigevent *__event);
extern int MsgVerifyEvent(rcvid_t __rcvid, const struct sigevent *__event);
extern int MsgVerifyEvent_r(rcvid_t __rcvid, const struct sigevent *__event);
extern int MsgRegisterEvent(struct sigevent *__event, int __coid);
extern int MsgRegisterEvent_r(struct sigevent *__event, int __coid);
extern int MsgUnregisterEvent(const struct sigevent *__event);
extern int MsgUnregisterEvent_r(const struct sigevent *__event);
extern int MsgInfo(rcvid_t __rcvid, struct _msg_info *__info);
extern int MsgInfo_r(rcvid_t __rcvid, struct _msg_info *__info);
extern int MsgError(rcvid_t __rcvid, int __err);
extern int MsgError_r(rcvid_t __rcvid, int __err);
extern int MsgCurrent(rcvid_t __rcvid);
extern int MsgCurrent_r(rcvid_t __rcvid);
extern int MsgPause(rcvid_t __rcvid, unsigned __cookie);
extern int MsgPause_r(rcvid_t __rcvid, unsigned __cookie);

extern int SignalKill(_Uint32t __nd, pid_t __pid, int __tid, int __signo, int __code, int __value);
extern int SignalKill_r(_Uint32t __nd, pid_t __pid, int __tid, int __signo, int __code, int __value);
extern int SignalKillSigval(_Uint32t __nd, pid_t __pid, int __tid, int __signo, int __code, const union sigval *__value);
extern int SignalKillSigval_r(_Uint32t __nd, pid_t __pid, int __tid, int __signo, int __code, const union sigval *__value);
extern int SignalReturn(struct _sighandler_info *__info);
extern int SignalAction(pid_t __pid, void (*__sigstub)(void), int __signo, const struct sigaction *__act, struct sigaction *__oact);
extern int SignalAction_r(pid_t __pid, void (*__sigstub)(void), int __signo, const struct sigaction *__act, struct sigaction *__oact);
extern int SignalProcmask(pid_t __pid, int __tid, int __how, const sigset_t *__set, sigset_t *__oldset);
extern int SignalProcmask_r(pid_t __pid, int __tid, int __how, const sigset_t *__set, sigset_t *__oldset);
extern int SignalSuspend(const sigset_t *__set);
extern int SignalSuspend_r(const sigset_t *__set);
extern int SignalWaitinfo(const sigset_t *__set, siginfo_t *__info);
extern int SignalWaitinfo_r(const sigset_t *__set, siginfo_t *__info);
extern int SignalWaitinfoMask(const sigset_t *__set, siginfo_t *__info, const sigset_t *__mask);
extern int SignalWaitinfoMask_r(const sigset_t *__set, siginfo_t *__info, const sigset_t *__mask);

extern int ThreadCreate(pid_t __pid, void *(*__func)(void *__arg), void *__arg, const struct _thread_attr *__attr);
extern int ThreadCreate_r(pid_t __pid, void *(*__func)(void *__arg), void *__arg, const struct _thread_attr *__attr);
extern int ThreadDestroy(int __tid, int __priority, void *__status);
extern int ThreadDestroy_r(int __tid, int __priority, void *__status);
extern int ThreadDetach(int __tid);
extern int ThreadDetach_r(int __tid);
extern int ThreadJoin(int __tid, void **__status);
extern int ThreadJoin_r(int __tid, void **__status);
extern int ThreadCancel(int __tid, void (*__canstub)(void));
extern int ThreadCancel_r(int __tid, void (*__canstub)(void));
extern int ThreadCtl(int __cmd, void *__data);
extern int ThreadCtl_r(int __cmd, void *__data);
extern int ThreadCtlExt(pid_t __pid, int __tid, int __cmd, void *__data);
extern int ThreadCtlExt_r(pid_t __pid, int __tid, int __cmd, void *__data);

struct qtime_entry;
struct syspage_entry;

extern int InterruptHookTrace(const struct sigevent *(*__handler)(int), unsigned __flags);
extern int InterruptHookIdle(void (*__handler)(_Uint64t *, struct qtime_entry *), unsigned __flags);
extern int InterruptHookIdle2(void (*__handler)(unsigned, struct syspage_entry *, struct _idle_hook *), unsigned __flags);
extern int InterruptHookOverdriveEvent(const struct sigevent *__event, unsigned __flags);
extern int InterruptAttachEvent(int __intr, const struct sigevent *__event, unsigned __flags);
extern int InterruptAttachEvent_r(int __intr, const struct sigevent *__event, unsigned __flags);
extern int InterruptAttachEventPriority(int intr, struct sigevent const * event,
                                        unsigned prio, unsigned flags);
extern int InterruptAttachEventPriority_r(int intr, struct sigevent const * event,
                                          unsigned prio, unsigned flags);
extern int InterruptAttachThread(int __intr, unsigned __flags);
extern int InterruptAttachThread_r(int __intr, unsigned __flags);
extern int InterruptAttach(int __intr, const struct sigevent *(*__handler)(void *__area, int __id), const void *__area, int __size, unsigned __flags);
extern int InterruptAttach_r(int __intr, const struct sigevent *(*__handler)(void *__area, int __id), const void *__area, int __size, unsigned __flags);
extern int InterruptAttachArray(int __intr, const struct sigevent * const *(*__handler)(void *__area, int __id), const void *__area, int __size, unsigned __flags);
extern int InterruptAttachArray_r(int __intr, const struct sigevent * const *(*__handler)(void *__area, int __id), const void *__area, int __size, unsigned __flags);
extern int InterruptDetach(int __id);
extern int InterruptDetach_r(int __id);
extern int InterruptWait(int __flags, const _Uint64t *__timeout);
extern int InterruptWait_r(int __flags, const _Uint64t *__timeout);
extern int InterruptCharacteristic(int __type, int __id, unsigned *__new, unsigned *__old);
extern int InterruptCharacteristic_r(int __type, int __id, unsigned *__new, unsigned *__old);
extern int InterruptQuery(unsigned type, int id, unsigned long extra, struct interrupt_query_data *data);
extern int InterruptQuery_r(unsigned type, int id, unsigned long extra, struct interrupt_query_data *data);
extern int InterruptUnblock(int __id);
extern int InterruptUnblock_r(int __id);
extern int InterruptCtl(int __id, int __cmd, void *__data, size_t __len);
extern int InterruptCtl_r(int __id, int __cmd, void *__data, size_t __len);

extern int SchedGet(pid_t __pid, int __tid, struct sched_param *__param);
extern int SchedGet_r(pid_t __pid, int __tid, struct sched_param *__param);
extern unsigned int SchedGetCpuNum(void);
extern int SchedSet(pid_t __pid, int __tid, int __algorithm, const struct sched_param *__param);
extern int SchedSet_r(pid_t __pid, int __tid, int __algorithm, const struct sched_param *__param);
extern int SchedInfo(pid_t __pid, int __algorithm, struct _sched_info *__info);
extern int SchedInfo_r(pid_t __pid, int __algorithm, struct _sched_info *__info);
extern int SchedYield(void);
extern int SchedYield_r(void);
extern int SchedCtl(int __cmd, void *__data, size_t __length);
extern int SchedCtl_r(int __cmd, void *__data, size_t __length);
extern int SchedJobCreate(nto_job_t *__job);
extern int SchedJobCreate_r(nto_job_t   *__job);
extern int SchedJobDestroy(nto_job_t    *__job);
extern int SchedJobDestroy_r(nto_job_t  *__job);
extern int SchedWaypoint(nto_job_t *__job, const _Int64t *__new, const _Int64t *__max, _Int64t *__old);
extern int SchedWaypoint_r(nto_job_t *__job, const _Int64t *__new, const _Int64t *__max, _Int64t *__old);
/* Temp definitions */
extern int SchedWaypoint2(nto_job_t *__job, const _Int64t *__new, const _Int64t *__max, _Int64t *__old);
extern int SchedWaypoint2_r(nto_job_t *__job, const _Int64t *__new, const _Int64t *__max, _Int64t *__old);

extern int TimerCreate(clockid_t __id, const struct sigevent *__notify);
extern int TimerCreate_r(clockid_t __id, const struct sigevent *__notify);
extern int TimerDestroy(timer_t __id);
extern int TimerDestroy_r(timer_t __id);
extern int TimerSettime(timer_t __id, int __flags, const struct _itimer *__itime, struct _itimer *__oitime);
extern int TimerSettime_r(timer_t __id, int __flags, const struct _itimer *__itime, struct _itimer *__oitime);
extern int TimerInfo(pid_t __pid, timer_t __id, int __flags, struct _timer_info *__info);
extern int TimerInfo_r(pid_t __pid, timer_t __id, int __flags, struct _timer_info *__info);
extern int TimerAlarm(clockid_t __id, const struct _itimer *__itime, struct _itimer *__otime);
extern int TimerAlarm_r(clockid_t __id, const struct _itimer *__itime, struct _itimer *__otime);
extern int TimerTimeout(clockid_t __id, _Uint32t __flags, const struct sigevent *__notify, const _Uint64t *__ntime,
                        _Uint64t *__otime);
extern int TimerTimeout_r(clockid_t __id, _Uint32t __flags, const struct sigevent *__notify, const _Uint64t *__ntime,
                          _Uint64t *__otime);
extern int TimerDelegate(_Uint32t __action, _Int32t owner_cpu, _Int32t delegate_cpu);
extern int TimerDelegate_r(_Uint32t __action, _Int32t owner_cpu, _Int32t delegate_cpu);

extern int SyncTypeCreate(unsigned __type, sync_t *__sync, const struct _sync_attr *__attr);
extern int SyncTypeCreate_r(unsigned __type, sync_t *__sync, const struct _sync_attr *__attr);
extern int SyncDestroy(sync_t *__sync);
extern int SyncDestroy_r(sync_t *__sync);
extern int SyncTypeDestroy(uint32_t type, sync_t *__sync);
extern int SyncTypeDestroy_r(uint32_t type, sync_t *__sync);
extern int SyncCtl(int __cmd, sync_t *__sync, void *__data);
extern int SyncCtl_r(int __cmd, sync_t *__sync, void *__data);
extern int SyncMutexEvent(sync_t *__sync, const struct sigevent *event);
extern int SyncMutexEvent_r(sync_t *__sync, const struct sigevent *event);
extern int SyncMutexLock(sync_t *__sync);
extern int SyncMutexLock_r(sync_t *__sync);
extern int SyncMutexUnlock(sync_t *__sync);
extern int SyncMutexUnlock_r(sync_t *__sync);
extern int SyncCondvarWait(sync_t *__sync, sync_t *__mutex);
extern int SyncCondvarWait_r(sync_t *__sync, sync_t *__mutex);
extern int SyncCondvarSignal(sync_t *__sync, int __all);
extern int SyncCondvarSignal_r(sync_t *__sync, int __all);
extern int SyncSemPost(sync_t *__sync);
extern int SyncSemPost_r(sync_t *__sync);
extern int SyncSemWait(sync_t *__sync, int __tryto);
extern int SyncSemWait_r(sync_t *__sync, int __tryto);
extern int SyncRWLock(sync_t *__sync, unsigned __op);
extern int SyncRWLock_r(sync_t *__sync, unsigned __op);

/* process manager private kernel interface */
extern _Intptrt __Ring0(int (*__func)(void *), void *__arg);
extern _Intptrt __Ring0_r(int (*__func)(void *), void *__arg);

extern int ClockTime(clockid_t __id, const _Uint64t *__new, _Uint64t *__old);
extern int ClockTime_r(clockid_t __id, const _Uint64t *__new, _Uint64t *__old);
extern int ClockAdjust(clockid_t __id, const struct _clockadjust *_new, struct _clockadjust *__old);
extern int ClockAdjust_r(clockid_t __id, const struct _clockadjust *_new, struct _clockadjust *__old);
extern int ClockPeriod(clockid_t __id, const struct _clockperiod *_new, struct _clockperiod *__old, int __reserved);
extern int ClockPeriod_r(clockid_t __id, const struct _clockperiod *_new, struct _clockperiod *__old, int __reserved);
extern int ClockId(pid_t __pid, int __tid);
extern int ClockId_r(pid_t __pid, int __tid);

/* QNET private kernel interface */
extern int NetCred(int __coid, const struct _client_info *__info);
extern int NetVtid(int __vtid, const struct _vtid_info *__info);
extern int NetUnblock(int __vtid);
extern int NetInfoscoid(int __local_scoid, int __remote_scoid);
extern int NetSignalKill(void *sigdata, struct _cred_info *cred);

extern int TraceEvent(int __code, ...);
extern void DebugBreak(void);
extern void DebugKDBreak(void);

#define DebugBreak()            __inline_DebugBreak()
#define DebugKDBreak()          __inline_DebugKDBreak()

extern void InterruptEnable(void);
extern void InterruptDisable(void);
extern int  InterruptMask(int __intr, int __id);
extern int  InterruptUnmask(int __intr, int __id);
extern void InterruptLock(struct intrspin * __spin);
extern void InterruptUnlock(struct intrspin * __spin);
extern unsigned InterruptStatus(void);

#define InterruptEnable()       __inline_InterruptEnable()
#define InterruptDisable()      __inline_InterruptDisable()
#define InterruptStatus()       __inline_InterruptStatus()

/* For backwards compatibility only, use SyncTypeCreate[_r] instead */
extern int SyncCreate(sync_t *__sync, const struct _sync_attr *__attr);
extern int SyncCreate_r(sync_t *__sync, const struct _sync_attr *__attr);

extern int SyncBarrierWait(sync_t * __sync);
extern int SyncBarrierWait_r(sync_t * __sync);


extern int SysSrandom(const _Uint64t *__seedp, _Uint64t *__entropy,
        _Sizet __elements);
extern int SysSrandom_r(const _Uint64t *__seedp, _Uint64t *__entropy,
        _Sizet __elements);

extern int MsgQueueOpen(rcvid_t __rcvid, int __queueid, _Uint32t __msgsize,
                        _Uint32t __maxmsg, unsigned __oflag);
extern int MsgQueueSend(int __fd, char const *__msg, size_t __msglen,
                        unsigned __priority);
extern int MsgQueueReceive(int __fd, char *__msg, size_t __msglen,
                           unsigned *priority);
extern int MsgQueueCtl(int __fd, int __cmd, void *__data);
extern int MsgQueueClose(rcvid_t __rcvid, int __queueid);

extern int PipeOpen(int __scoid, int __pipeid, struct nto_pipe_cfg * __cfg,
                    unsigned __flags);
extern int PipeOpen_r(int __scoid, int __pipeid, struct nto_pipe_cfg * __cfg,
                      unsigned __flags);
extern int PipeCtl(int __scoid, union nto_pipe_ctl * __ctl);
extern int PipeCtl_r(int __scoid, union nto_pipe_ctl * __ctl);
extern int PipeCtlNotify(int __scoid, _Int32t __action, _Uint32t __flags,
                         pid_t __tgtpid, _Int32t __tgttid,
                         struct sigevent const * const __event, _Uint32t *__conditions);
extern int PipeCtlNotify_r(int __scoid, _Int32t __action, _Uint32t __flags,
                           pid_t __tgtpid, _Int32t __tgttid,
                           struct sigevent const * const __event, _Uint32t *__conditions);
extern int PipeClose(int __pipeid);
extern int PipeClose_r(int __pipeid);

__END_DECLS

#include _NTO_HDR_(_packpop.h)

#if __NTO_FORTIFY_LEVEL > 0
#include <sys/neutrino_chk.h>
#endif

/* Local node: obsolete */
#define       ND_LOCAL_NODE           0

#endif
