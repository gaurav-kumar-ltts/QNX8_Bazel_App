/*
 * $QNXLicenseC:
 * Copyright 2007-2023, QNX Software Systems. All Rights Reserved.
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

#ifndef __TRACE_H_INCLUDED
#define __TRACE_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __STATES_H_INCLUDED
#include _NTO_HDR_(sys/states.h)
#endif

/* TraceEvent() - modes */

// top four bits encode the number of parameters to TraceEvent()
#define _NTO_TRACE_ADDALLCLASSES     (((_Uint32t)0x00000001<<28)|1u)
#define _NTO_TRACE_DELALLCLASSES     (((_Uint32t)0x00000001<<28)|2u)
#define _NTO_TRACE_ADDCLASS          (((_Uint32t)0x00000002<<28)|3u)
#define _NTO_TRACE_DELCLASS          (((_Uint32t)0x00000002<<28)|4u)
#define _NTO_TRACE_ADDEVENT          (((_Uint32t)0x00000003<<28)|5u)
#define _NTO_TRACE_DELEVENT          (((_Uint32t)0x00000003<<28)|6u)
#define _NTO_TRACE_ADDEVENTHANDLER   (((_Uint32t)0x00000005<<28)|7u)
#define _NTO_TRACE_DELEVENTHANDLER   (((_Uint32t)0x00000003<<28)|8u)
#define _NTO_TRACE_INSERTEVENT       (((_Uint32t)0x00000005<<28)|9u)
#define _NTO_TRACE_START             (((_Uint32t)0x00000001<<28)|10u)
#define _NTO_TRACE_STOP              (((_Uint32t)0x00000001<<28)|11u)
#define _NTO_TRACE_ALLOCBUFFER       (((_Uint32t)0x00000003<<28)|12u)
#define _NTO_TRACE_DEALLOCBUFFER     (((_Uint32t)0x00000001<<28)|13u)
#define _NTO_TRACE_FLUSHBUFFER       (((_Uint32t)0x00000001<<28)|14u)
#define _NTO_TRACE_QUERYEVENTS       (((_Uint32t)0x00000001<<28)|15u)
#define _NTO_TRACE_SETALLCLASSESFAST (((_Uint32t)0x00000001<<28)|16u)
#define _NTO_TRACE_SETALLCLASSESWIDE (((_Uint32t)0x00000001<<28)|17u)
#define _NTO_TRACE_SETCLASSFAST      (((_Uint32t)0x00000002<<28)|18u)
#define _NTO_TRACE_SETCLASSWIDE      (((_Uint32t)0x00000002<<28)|19u)
#define _NTO_TRACE_SETEVENTFAST      (((_Uint32t)0x00000003<<28)|20u)
#define _NTO_TRACE_SETEVENTWIDE      (((_Uint32t)0x00000003<<28)|21u)
#define _NTO_TRACE_SETCLASSPID       (((_Uint32t)0x00000003<<28)|22u)
#define _NTO_TRACE_SETCLASSTID       (((_Uint32t)0x00000004<<28)|23u)
#define _NTO_TRACE_SETEVENTPID       (((_Uint32t)0x00000004<<28)|24u)
#define _NTO_TRACE_SETEVENTTID       (((_Uint32t)0x00000005<<28)|25u)
#define _NTO_TRACE_CLRCLASSPID       (((_Uint32t)0x00000002<<28)|26u)
#define _NTO_TRACE_CLRCLASSTID       (((_Uint32t)0x00000002<<28)|27u)
#define _NTO_TRACE_CLREVENTPID       (((_Uint32t)0x00000003<<28)|28u)
#define _NTO_TRACE_CLREVENTTID       (((_Uint32t)0x00000003<<28)|29u)
#define _NTO_TRACE_INSERTSUSEREVENT  (((_Uint32t)0x00000004<<28)|30u)
#define _NTO_TRACE_INSERTCUSEREVENT  (((_Uint32t)0x00000004<<28)|31u)
#define _NTO_TRACE_INSERTUSRSTREVENT (((_Uint32t)0x00000003<<28)|32u)
#define _NTO_TRACE_STARTNOSTATE      (((_Uint32t)0x00000001<<28)|33u)
#define _NTO_TRACE_SETRINGMODE       (((_Uint32t)0x00000001<<28)|34u)
#define _NTO_TRACE_SETLINEARMODE     (((_Uint32t)0x00000001<<28)|35u)
#define _NTO_TRACE_ADDCLASSEVHANDLER (((_Uint32t)0x00000004<<28)|36u)
#define _NTO_TRACE_DELCLASSEVHANDLER (((_Uint32t)0x00000002<<28)|37u)
#define _NTO_TRACE_SKIPBUFFER        (((_Uint32t)0x00000001<<28)|38u)
#define _NTO_TRACE_OVERWRITEBUFFER   (((_Uint32t)0x00000001<<28)|39u)
#define _NTO_TRACE_QUERYVERSION      (((_Uint32t)0x00000001<<28)|40u)
#define _NTO_TRACE_QUERYSUPPORT      (((_Uint32t)0x00000001<<28)|41u)
#define _NTO_TRACE_INSERTSCLASSEVENT (((_Uint32t)0x00000005<<28)|42u)
#define _NTO_TRACE_INSERTCCLASSEVENT (((_Uint32t)0x00000005<<28)|43u)
#define _NTO_TRACE_SETBUFFER         (((_Uint32t)0x00000003<<28)|44u)
#define _NTO_TRACE_LOGGER_ATTACH     (((_Uint32t)0x00000003<<28)|45u)
#define _NTO_TRACE_WAITBUFFER        (((_Uint32t)0x00000002<<28)|46u)
#define _NTO_TRACE_LOGGER_DETACH     (((_Uint32t)0x00000001<<28)|47u)
#define _NTO_TRACE_PMU_CONFIG        (((_Uint32t)0x00000002<<28)|48u)
#define _NTO_TRACE_PMU_QUERYEVENTS   (((_Uint32t)0x00000001<<28)|49u)

/* TraceEvent() - external classes */
enum {
    _NTO_TRACE_EMPTY,
    _NTO_TRACE_CONTROL,
    _NTO_TRACE_KERCALL,
    _NTO_TRACE_KERCALLENTER,
    _NTO_TRACE_KERCALLEXIT,
    _NTO_TRACE_KERCALLINT,
    _NTO_TRACE_INT,
    _NTO_TRACE_RESERVEDCLASS1,
    _NTO_TRACE_RESERVEDCLASS2,
    _NTO_TRACE_PROCESS,
    _NTO_TRACE_THREAD,
    _NTO_TRACE_RESERVEDCLASS3,
    _NTO_TRACE_USER,
    _NTO_TRACE_SYSTEM,
    _NTO_TRACE_COMM,
    _NTO_TRACE_RESERVEDCLASS4,
    _NTO_TRACE_RESERVEDCLASS5,
    _NTO_TRACE_QUIP,
    _NTO_TRACE_SEC,
    _NTO_TRACE_QVM,
    _NTO_TRACE_PMU,
    _NTO_TRACE_NUM_CLASSES
};

/* TraceEvent() - external events */
#define _NTO_TRACE_EMPTYEVENT       (0x00000000u)

#define _NTO_TRACE_CONTROLTIME      ((_Uint32t)0x00000001<<0)
#define _NTO_TRACE_CONTROLBUFFER    ((_Uint32t)0x00000001<<1)
#define _NTO_TRACE_CONTROLBUFFEREND ((_Uint32t)0x00000001<<2)
#define _NTO_TRACE_CONTROLDROPPED   ((_Uint32t)0x00000001<<3)

#define _NTO_TRACE_KERCALLFIRST     (0x00000000u)
#define _NTO_TRACE_KERCALLLAST      (__KER_BAD)
#define _NTO_TRACE_KERCALL64        ((_Uint32t)0x00000001u<<9)

/* _TRACE_INT_C event types
 * 0-6 are reserved for the old 7.x ISR events.
 * _TRACE_INT_DELIVER is internal; the TraceEvent() API exposes a mask
 * per-interrupt with the _NTO_TRACE_INT class. The rest use _NTO_TRACE_IST.
 */
#define _TRACE_INT_DELIVER          (7U)

#define _NTO_TRACE_INTFIRST         (0x00000000u)
#define _NTO_TRACE_INTLAST          (0xffffffffu)

#define _NTO_TRACE_PROCCREATE       ((_Uint32t)0x00000001<<0)
#define _NTO_TRACE_PROCDESTROY      ((_Uint32t)0x00000001<<1)
#define _NTO_TRACE_PROCCREATE_NAME  ((_Uint32t)0x00000001<<2)
#define _NTO_TRACE_PROCDESTROY_NAME ((_Uint32t)0x00000001<<3)
#define _NTO_TRACE_PROCTHREAD_NAME  ((_Uint32t)0x00000001<<4)

#define _NTO_TRACE_THDEAD           STATE_DEAD
#define _NTO_TRACE_THRUNNING        STATE_RUNNING
#define _NTO_TRACE_THREADY          STATE_READY
#define _NTO_TRACE_THSTOPPED        STATE_STOPPED
#define _NTO_TRACE_THSEND           STATE_SEND
#define _NTO_TRACE_THRECEIVE        STATE_RECEIVE
#define _NTO_TRACE_THREPLY          STATE_REPLY
#define _NTO_TRACE_THWAITPAGE       STATE_WAITPAGE
#define _NTO_TRACE_THSIGSUSPEND     STATE_SIGSUSPEND
#define _NTO_TRACE_THSIGWAITINFO    STATE_SIGWAITINFO
#define _NTO_TRACE_THNANOSLEEP      STATE_NANOSLEEP
#define _NTO_TRACE_THMUTEX          STATE_MUTEX
#define _NTO_TRACE_THCONDVAR        STATE_CONDVAR
#define _NTO_TRACE_THJOIN           STATE_JOIN
#define _NTO_TRACE_THINTR           STATE_INTR
#define _NTO_TRACE_THSEM            STATE_SEM
#define _NTO_TRACE_THBARRIER        STATE_BARRIER
#define _NTO_TRACE_THWAITCTX        STATE_WAITCTX
#define _NTO_TRACE_THRWLOCK_READ    STATE_RWLOCK_READ
#define _NTO_TRACE_THRWLOCK_WRITE   STATE_RWLOCK_WRITE
#define _NTO_TRACE_THPIPE           STATE_PIPE
#define _NTO_TRACE_THCREATE         STATE_CREATE
#define _NTO_TRACE_THDESTROY        STATE_DESTROY
#define _NTO_TRACE_THMUON_MUTEX     STATE_MUON_MUTEX
#define _NTO_TRACE_THTRACEBUFFER    STATE_TRACEBUFFER
#define _NTO_TRACE_THINTR_ATTACH_EV STATE_INTR_ATTACH_EV
#define _NTO_TRACE_THTIMER_DELEGATE STATE_TIMER_DELEGATE
#define _NTO_TRACE_THSEND_NOTIFY    STATE_SEND_NOTIFY

#define _NTO_TRACE_THFIRST _NTO_TRACE_THDEAD
#define _NTO_TRACE_THLAST  _NTO_TRACE_THSEND_NOTIFY

#define _NTO_TRACE_USERFIRST        (0x00000000u)
#define _NTO_TRACE_USERLAST         (0x000003ffu)

#define _NTO_TRACE_QUIPFIRST        (0x00000000u)
#define _NTO_TRACE_QUIPLAST         (0x000003ffu)

#define _NTO_TRACE_SECFIRST        (0x00000000u)
#define _NTO_TRACE_SECLAST         (0x000003ffu)

#define _NTO_TRACE_QVMFIRST         (0x00000000u)
#define _NTO_TRACE_QVMLAST          (0x000003ffu)

#define _NTO_TRACE_SYS_RESERVED     (0x00000001u)
#define _NTO_TRACE_SYS_PATHMGR      (0x00000002u)
#define _NTO_TRACE_SYS_APS_NAME     (0x00000003u)
#define _NTO_TRACE_SYS_APS_BUDGETS  (0x00000004u)
#define _NTO_TRACE_SYS_APS_BNKR     (0x00000005) /* when APS scheduler detects bankruptcy */
#define _NTO_TRACE_SYS_MMAP         (0x00000006u)
#define _NTO_TRACE_SYS_MUNMAP       (0x00000007u)
#define _NTO_TRACE_SYS_MAPNAME      (0x00000008u)
#define _NTO_TRACE_SYS_ADDRESS      (0x00000009u)
#define _NTO_TRACE_SYS_FUNC_ENTER   (0x0000000au)
#define _NTO_TRACE_SYS_FUNC_EXIT    (0x0000000bu)
#define _NTO_TRACE_SYS_SLOG         (0x0000000cu)
#define _NTO_TRACE_SYS_DEFRAG_START (0x0000000du)
#define _NTO_TRACE_SYS_RUNSTATE     (0x0000000eu)
#define _NTO_TRACE_SYS_POWER        (0x0000000fu)
#define _NTO_TRACE_SYS_IPI          (0x00000010u)
#define _NTO_TRACE_SYS_PAGEWAIT     (0x00000011u)
#define _NTO_TRACE_SYS_TIMER        (0x00000012u)
#define _NTO_TRACE_SYS_DEFRAG_END   (0x00000013u)
#define _NTO_TRACE_SYS_PROFILE      (0x00000014u)
#define _NTO_TRACE_SYS_MAPNAME_64   (0x00000015u)
#define _NTO_TRACE_SYS_APS_PSTATS   (0x00000016u)
#define _NTO_TRACE_SYS_APS_OSTATS   (0x00000017u)
#define _NTO_TRACE_SYS_APS_INFO     (0x00000018u)
#define _NTO_TRACE_SYS_APS_JOIN     (0x00000019u)
#define _NTO_TRACE_SYS_APS_THREAD   (0x0000001au)
#define _NTO_TRACE_SYS_APS_PROCESS  (0x0000001bu)
#define _NTO_TRACE_SYS_SCHED_CONF   (0x0000001cu)
#define _NTO_TRACE_SYS_IST_ATTACH   (0x0000001du)
#define _NTO_TRACE_SYS_IST_DETACH   (0x0000001eu)
#define _NTO_TRACE_SYS_PCTRACE      (0x0000001fu)
#define _NTO_TRACE_SYS_SEND_IPI     (0x00000020u)
#define _NTO_TRACE_SYS_LAST         _NTO_TRACE_SYS_SEND_IPI
#define _NTO_TRACE_SYS_IPI_64       (_NTO_TRACE_SYS_IPI|_NTO_TRACE_KERCALL64)
#define _NTO_TRACE_SYS_PROFILE_64   (_NTO_TRACE_SYS_PROFILE|_NTO_TRACE_KERCALL64)
#define _NTO_TRACE_SYS_ADDRESS_64    (_NTO_TRACE_SYS_ADDRESS|_NTO_TRACE_KERCALL64)
#define _NTO_TRACE_SYS_FUNC_ENTER_64 (_NTO_TRACE_SYS_FUNC_ENTER|_NTO_TRACE_KERCALL64)
#define _NTO_TRACE_SYS_FUNC_EXIT_64  (_NTO_TRACE_SYS_FUNC_EXIT|_NTO_TRACE_KERCALL64)
#define _NTO_TRACE_SYS_SEND_IPI_64  (_NTO_TRACE_SYS_SEND_IPI|_NTO_TRACE_KERCALL64)

#define _NTO_TRACE_PMU_EVENT_TYPE           (0x00000000u)
#define _NTO_TRACE_PMU_EVENT_COUNTER        (0x00000001u)
#define _NTO_TRACE_PMU_LAST                 _NTO_TRACE_PMU_EVENT_COUNTER

// For backwards compatibility
#define _NTO_TRACE_SYS_COMPACTION    _NTO_TRACE_SYS_DEFRAG_START

#define _NTO_TRACE_COMM_SMSG        (0x00000000u)
#define _NTO_TRACE_COMM_SPULSE      (0x00000001u)
#define _NTO_TRACE_COMM_RMSG        (0x00000002u)
#define _NTO_TRACE_COMM_RPULSE      (0x00000003u)
#define _NTO_TRACE_COMM_SPULSE_EXE  (0x00000004u)
#define _NTO_TRACE_COMM_SPULSE_DIS  (0x00000005u)
#define _NTO_TRACE_COMM_SPULSE_DEA  (0x00000006u)
#define _NTO_TRACE_COMM_SPULSE_UN   (0x00000007u)
#define _NTO_TRACE_COMM_SPULSE_QUN  (0x00000008u)
#define _NTO_TRACE_COMM_SIGNAL      (0x00000009u)
#define _NTO_TRACE_COMM_REPLY       (0x0000000au)
#define _NTO_TRACE_COMM_ERROR       (0x0000000bu)
#define _NTO_TRACE_COMM_LAST        _NTO_TRACE_COMM_ERROR

#define _NTO_TRACE_MAX_CLASS        (0x0000001fu)
#define _NTO_TRACE_MAX_CODES        (0x000003ffu)

// Flags that may be set in the header
#define _NTO_TRACE_PROCESS_INJECTED (0x00010000u)

#define _NTO_TRACE_SETEVENT_C(c,cl) (c&=~(0x1fu<<10),c|=(cl))
#define _NTO_TRACE_GETEVENT_C(c)    ((c)&(0x1fu<<10))
#define _NTO_TRACE_SETEVENT(c, e)   (c&=~(0x3ffu),c|=(e))
#define _NTO_TRACE_GETEVENT(c)      ((unsigned)(c)&0x3ffu)
#define _NTO_TRACE_GETCPU(h)        (((h)&0x3f000000u)>>24)

/* Query support flags */
#define _NTO_TRACE_NOINSTRSUPP      (0x00000000u)
#define _NTO_TRACE_SUPPINSTR        (0x00000001u<<0)

enum _TRACE_PATH_ATTACH_STATUS {
    _TRACE_PATH_ATTACH_OK,
    _TRACE_PATH_ATTACH_NO_RULE,
    _TRACE_PATH_ATTACH_CONFLICT,
    _TRACE_PATH_ATTACH_BAD_OP,
};

enum _TRACE_QNET_CONNECT_STATUS {
    _TRACE_QNET_CONNECT_OK,
    _TRACE_QNET_CONNECT_SERVER_FAILED,
    _TRACE_QNET_CONNECT_CLIENT_FAILED,
};

enum _TRACE_SEC_ABLE_FLAGS {
    _TRACE_SEC_ABLE_DENY = 0u,
    _TRACE_SEC_ABLE_ALLOW = 1u,
    _TRACE_SEC_ABLE_IS_ROOT = 2u,
    _TRACE_SEC_ABLE_UNCREATED = 4u,
};

/* Security event flags */
#define _NTO_TRACE_SEC_ABLE         (0x00000000u)
#define _NTO_TRACE_SEC_ABLE_LOOKUP  (0x00000001u)
#define _NTO_TRACE_SEC_PATH_ATTACH  (0x00000002u)
#define _NTO_TRACE_SEC_QNET_CONNECT (0x00000003u)
#define _NTO_TRACE_SEC_PERM_LOOKUP  (0x00000004u)
#define _NTO_TRACE_SEC_PERM_TEST    (0x00000005u)
#define _NTO_TRACE_SEC_UNREG_EVENT  (0x00000006u)
#define _NTO_TRACE_SEC_OPEN_EVENT   (0x00000007u)

/* Power event flags */
#define _NTO_TRACE_POWER_CPUMASK        0x0000ffffu
#define _NTO_TRACE_POWER_IDLE           0x00010000u
#define _NTO_TRACE_POWER_START          0x00020000u
#define _NTO_TRACE_POWER_IDLE_REACHED   0x00040000u /* for _NTO_TRACE_POWER_IDLE */
#define _NTO_TRACE_POWER_VFS_OVERDRIVE  0x00040000u /* for !_NTO_TRACE_POWER_IDLE */
#define _NTO_TRACE_POWER_VFS_DYNAMIC    0x00080000u /* for !_NTO_TRACE_POWER_IDLE */
#define _NTO_TRACE_POWER_VFS_STEP_UP    0x00100000u /* for !_NTO_TRACE_POWER_IDLE */

/* Hypervisor events */
#define _NTO_TRACE_QVM_GUEST_ENTER          (0x00000000u)
#define _NTO_TRACE_QVM_GUEST_EXIT           (0x00000001u)
#define _NTO_TRACE_QVM_CREATE_VCPU_THREAD   (0x00000002u)
#define _NTO_TRACE_QVM_RAISE_INTR           (0x00000003u)
#define _NTO_TRACE_QVM_LOWER_INTR           (0x00000004u)
#define _NTO_TRACE_QVM_TIMER_CREATE         (0x00000005u)
#define _NTO_TRACE_QVM_TIMER_FIRE           (0x00000006u)
#define _NTO_TRACE_QVM_CYCLES               (0x00000007u)

#define _TRACE_MAX_EVENT_NUM        (0x00000400u)

#define _TRACE_MAX_TH_STATE_NUM STATE_MAX

typedef _Uint32t __traceentry;

typedef struct traceevent {
    __traceentry header;  /* CPU, event, format */
    __traceentry data[3]; /* event data         */
} traceevent_t;

/* tracefile header keywords */
#define _TRACE_MAX_HEADER_LEN       (512)
#define _TRACE_HEADER_PREFIX        "TRACE_"
#define _TRACE_HEADER_POSTFIX       "::"

#define _TRACE_HEADER_KEYWORDS()    \
    _TRACE_MK_HK(HEADER_BEGIN),     \
    _TRACE_MK_HK(FILE_NAME),        \
    _TRACE_MK_HK(DATE),             \
    _TRACE_MK_HK(VER_MAJOR),        \
    _TRACE_MK_HK(VER_MINOR),        \
    _TRACE_MK_HK(LITTLE_ENDIAN),    \
    _TRACE_MK_HK(BIG_ENDIAN),       \
    _TRACE_MK_HK(MIDDLE_ENDIAN),    \
    _TRACE_MK_HK(ENCODING),         \
    _TRACE_MK_HK(BOOT_DATE),        \
    _TRACE_MK_HK(CYCLES_PER_SEC),   \
    _TRACE_MK_HK(CPU_NUM),          \
    _TRACE_MK_HK(SYSNAME),          \
    _TRACE_MK_HK(NODENAME),         \
    _TRACE_MK_HK(SYS_RELEASE),      \
    _TRACE_MK_HK(SYS_VERSION),      \
    _TRACE_MK_HK(MACHINE),          \
    _TRACE_MK_HK(SYSPAGE_LEN),      \
    _TRACE_MK_HK(NORMALIZEDN),      \
    _TRACE_MK_HK(HEADER_END)

#define _TRACE_GET_FLAG(c)          ((unsigned)(c)&0x0fffffffu)
#define _TRACE_GET_COUNT(c)         (((unsigned)(c)>>28)&0x7u)
#define _TRACE_FLAGS_RING           (0x00010000u)
#define _TRACE_FLAGS_WRITING        (0x00020000u)
#define _TRACE_FLAGS_WRITTING       _TRACE_FLAGS_WRITING
#define _TRACE_FLAGS_FLUSH          (0x00040000u)

#define _TRACE_MAX_KER_CALL_NUM     (128u)
#define _TRACE_MAX_IST_NUM          (_NTO_TRACE_IST_LAST+1u)
#define _TRACE_MAX_COMM_NUM         (_NTO_TRACE_COMM_LAST+1u)
#define _TRACE_MAX_SYSTEM_NUM       (_NTO_TRACE_SYS_LAST+1u)
#define _TRACE_MAX_USER_NUM         (_NTO_TRACE_USERLAST+1u)
#define _TRACE_MAX_QUIP_NUM         (_NTO_TRACE_QUIPLAST+1u)
#define _TRACE_MAX_SEC_NUM          (_NTO_TRACE_SECLAST+1u)
#define _TRACE_MAX_QVM_NUM          (_NTO_TRACE_QVMLAST+1u)
#define _TRACE_MAX_PMU_NUM          (_NTO_TRACE_PMU_LAST+1u)

#define _NTO_TRACE_KERCALLMASK      (_TRACE_MAX_KER_CALL_NUM-1u)

/* S-simple, C-comb., CC-comb.-cont, B-begin, E-end */
#define _TRACE_STRUCT_S             ((_Uint32t)0x00000000u)
#define _TRACE_STRUCT_CB            ((_Uint32t)0x00000001u<<30)
#define _TRACE_STRUCT_CC            ((_Uint32t)0x00000002u<<30)
#define _TRACE_STRUCT_CE            ((_Uint32t)0x00000003u<<30)
#define _TRACE_GET_STRUCT(c)        ((c)&((_Uint32t)0x3u<<30))

/* internal classes (C-class) */
#define _TRACE_EMPTY_C              ((_Uint32t)0x00000000u<<10)
#define _TRACE_CONTROL_C            ((_Uint32t)0x00000001u<<10)
#define _TRACE_KER_CALL_C           ((_Uint32t)0x00000002u<<10)
#define _TRACE_INT_C                ((_Uint32t)0x00000003u<<10)
#define _TRACE_PR_TH_C              ((_Uint32t)0x00000004u<<10)
#define _TRACE_SYSTEM_C             ((_Uint32t)0x00000005u<<10)
#define _TRACE_CONTAINER_C          _TRACE_SYSTEM_C     //Container class never defined
#define _TRACE_USER_C               ((_Uint32t)0x00000006u<<10)
#define _TRACE_COMM_C               ((_Uint32t)0x00000007u<<10)
#define _TRACE_QUIP_C               ((_Uint32t)0x00000008u<<10)
#define _TRACE_SEC_C                ((_Uint32t)0x00000009u<<10)
#define _TRACE_QVM_C                ((_Uint32t)0x0000000au<<10)
#define _TRACE_PMU_C                ((_Uint32t)0x0000000bu<<10)
#define _TRACE_TOT_CLASS_NUM        (12u)

#define _TRACE_CONTROL_TIME         (0x00000001U)
#define _TRACE_CONTROL_BUFFER       (0x00000002U)
#define _TRACE_CONTROL_BUFFER_END   (0x00000004U)
#define _TRACE_CONTROL_DROPPED      (0x00000008U)

/* thread create/destroy */
#define _TRACE_PR_TH_CREATE_T       (STATE_CREATE)
#define _TRACE_PR_TH_DESTROY_T      (STATE_DESTROY)
#define _TRACE_PR_TH_CREATE_VT      (_TRACE_PR_TH_CREATE_T+_TRACE_MAX_TH_STATE_NUM)
#define _TRACE_PR_TH_DESTROY_VT     (_TRACE_PR_TH_DESTROY_T+_TRACE_MAX_TH_STATE_NUM)

/* process create/destroy => (event<64) */
#define _TRACE_PR_TH_CREATE_P       ((_Uint32t)0x00000001u<<6)
#define _TRACE_PR_TH_DESTROY_P      ((_Uint32t)0x00000002u<<6)
#define _TRACE_PR_TH_CREATE_P_NAME  ((_Uint32t)0x00000003u<<6)
#define _TRACE_PR_TH_DESTROY_P_NAME ((_Uint32t)0x00000004u<<6)
/* additional thread information */
#define _TRACE_PR_TH_NAME_T         ((_Uint32t)0x00000005u<<6)

/* size of individual trace buffers */
#define _TRACEBUFSIZE               (16ULL * 1024ULL)
#define _TRACELEMENTS               ( (_TRACEBUFSIZE-sizeof(struct traceheader))/sizeof(struct traceevent) )

/* Special constant to identify the end of a buffer; each buffer ends
 * with a CONTROL BUFFER_END event encoded as:
 *      < header, timestamp, _TRACECOOKIE, _TRACECOOKIE >
 */
#define _TRACECOOKIE    (0xe6e6e6e6U)

#define _TRACE_WAITBUFFER_DONE 1

#if defined(__QNXNTO__)
/* just needed for kernel <=> tracelogger interface */

#ifndef _SYS_TIME_H
#include _NTO_HDR_(sys/time.h)
#endif

#ifndef __NEUTRINO_H_INCLUDED
#include _NTO_HDR_(sys/neutrino.h)
#endif

#ifndef _STDARG_H_INCLUDED
#include _NTO_HDR_(stdarg.h)
#endif

typedef struct {
    struct traceheader{
        _Uintptrt reserved1;
        _Uintptrt reserved2;
        _Uint32t         flags;        /* event mask, locking states, ...   */
        _Uint32t         num_events;   /* number of events in the buffer    */
        _Uint32t         seq_buff_num; /* buffer number in the sequence     */
        _Uint32t         reserved3[45];/* reserved for future expansions    */
    } h;
    struct traceevent data[_TRACELEMENTS];
} tracebuf_t;

#define PMU_MAX_EVENT_TYPE  32U
typedef struct {
    uint32_t n;
    uint32_t type[PMU_MAX_EVENT_TYPE];
} trace_pmu_config_t;


__BEGIN_DECLS

extern int trace_vnlogf( int __code, int __max, const char *__fmt, va_list __arglist );
extern int trace_logf( int __code, const char *__fmt, ...) __attribute__ ((format (__printf__, 2, 3)));
extern int trace_nlogf( int __code, int __max, const char *__fmt, ... ) __attribute__ ((format (__printf__, 3, 4)));
extern int trace_logi( int __code, unsigned __d1, unsigned __d2 );
extern int trace_logbc( int __class, int __event, const void *__data, size_t __nbytes);
extern int trace_logb( int __code, const void *__buf, size_t __nbytes );
extern int trace_func_enter( void const *__this_fn, void const *__call_site );
extern int trace_func_exit( void const *__this_fn, void const *__call_site );

static __inline__ int trace_here( void )
{
    void * const pc = __builtin_extract_return_addr(__builtin_return_address(0));
    return TraceEvent((int)_NTO_TRACE_INSERTCCLASSEVENT, _TRACE_SYSTEM_C >> 10,
            _NTO_TRACE_SYS_ADDRESS_64, &pc, sizeof(pc)/sizeof(_Uint32t));
}

__END_DECLS

#endif

#endif
