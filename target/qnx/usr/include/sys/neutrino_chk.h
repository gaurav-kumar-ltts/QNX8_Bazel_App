/*
 * Copyright (c) 2020-2022, QNX Software Systems. All Rights Reserved.
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

#ifndef __NEUTRINO_H_INCLUDED
#error <sys/neutrino_chk.h> should not be included directly.
#endif

#ifndef __NEUTRINO_CHK_H_INCLUDED
#define __NEUTRINO_CHK_H_INCLUDED

#include <fortify.h>

__BEGIN_DECLS

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_ConnectClientInfo,
        __fortify_fail_overflow_dst,
        "argument 3 of 'ConnectClientInfo' is greater than the number of 'gid_t' elements in member 'cred.grouplist' of the object "
                "referenced by argument 2");
extern int __ConnectClientInfo_alias(int __scoid, struct _client_info *__info, int __ngroups) __ALIASATTR("ConnectClientInfo");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_ConnectClientInfo_r,
        __fortify_fail_overflow_dst,
        "argument 3 of 'ConnectClientInfo_r' is greater than the number of 'gid_t' elements in member 'cred.grouplist' of the "
                "object referenced by argument 2");
extern int __ConnectClientInfo_r_alias(int __scoid, struct _client_info *__info, int __ngroups) __ALIASATTR("ConnectClientInfo_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_ConnectClientInfoAble,
        __fortify_fail_overflow_dst,
        "argument 5 of 'ConnectClientInfoAble' is greater than the number of 'struct _client_able' elements in the object "
                "referenced by argument 4");
extern int __ConnectClientInfoAble_alias(
        int                   __scoid,
        struct _client_info **__info_pp,
        int                   __flags,
        struct _client_able  *__abilities,
        int                   __nable
        ) __ALIASATTR("ConnectClientInfoAble");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgRead,
        __fortify_fail_overflow_dst,
        "argument 3 of 'MsgRead' is greater than the size of the object referenced by argument 2");
extern ssize_t __MsgRead_alias(rcvid_t __rcvid, void *__msg, _Sizet __bytes, _Sizet __offset) __ALIASATTR("MsgRead");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgRead_r,
        __fortify_fail_overflow_dst,
        "argument 3 of 'MsgRead_r' is greater than the size of the object referenced by argument 2");
extern ssize_t __MsgRead_r_alias(rcvid_t __rcvid, void *__msg, _Sizet __bytes, _Sizet __offset) __ALIASATTR("MsgRead_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgReadv,
        __fortify_fail_overflow_dst,
        "argument 3 of 'MsgReadv' is greater than the number of 'struct iovec' elements in the object referenced by argument 2");
extern ssize_t __MsgReadv_alias(rcvid_t __rcvid, const struct iovec *__iov, _Sizet __parts, _Sizet __offset) __ALIASATTR("MsgReadv");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgReadv_r,
        __fortify_fail_overflow_dst,
        "argument 3 of 'MsgReadv_r' is greater than the number of 'struct iovec' elements in the object referenced by argument 2");
extern ssize_t __MsgReadv_r_alias(rcvid_t __rcvid, const struct iovec *__iov, _Sizet __parts, _Sizet __offset)
        __ALIASATTR("MsgReadv_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgReceive,
        __fortify_fail_overflow_dst,
        "argument 3 of 'MsgReceive' is greater than the size of the object referenced by argument 2");
extern rcvid_t __MsgReceive_alias(int __chid, void *__msg, _Sizet __bytes, struct _msg_info *__info) __ALIASATTR("MsgReceive");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgReceive_r,
        __fortify_fail_overflow_dst,
        "argument 3 of 'MsgReceive_r' is greater than the size of the object referenced by argument 2");
extern rcvid_t __MsgReceive_r_alias(int __chid, void *__msg, _Sizet __bytes, struct _msg_info *__info) __ALIASATTR("MsgReceive_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgReceivePulse,
        __fortify_fail_overflow_dst,
        "argument 3 of 'MsgReceivePulse' is greater than the size of the object referenced by argument 2");
extern int __MsgReceivePulse_alias(int __chid, void *__pulse, _Sizet __bytes, struct _msg_info *__info)
        __ALIASATTR("MsgReceivePulse");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgReceivePulse_r,
        __fortify_fail_overflow_dst,
        "argument 3 of 'MsgReceivePulse_r' is greater than the size of the object referenced by argument 2");
extern int __MsgReceivePulse_r_alias(int __chid, void *__pulse, _Sizet __bytes, struct _msg_info *__info)
        __ALIASATTR("MsgReceivePulse_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgReceivev,
        __fortify_fail_overflow_dst,
        "argument 3 of 'MsgReceivev' is greater than the number of 'struct iovec' elements in the object referenced by argument 2");
extern rcvid_t __MsgReceivev_alias(int __chid, const struct iovec *__iov, _Sizet __parts, struct _msg_info *__info)
        __ALIASATTR("MsgReceivev");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgReceivev_r,
        __fortify_fail_overflow_dst,
        "argument 3 of 'MsgReceivev_r' is greater than the number of 'struct iovec' elements in the object referenced by "
                "argument 2");
extern rcvid_t __MsgReceivev_r_alias(int __chid, const struct iovec *__iov, _Sizet __parts, struct _msg_info *__info)
        __ALIASATTR("MsgReceivev_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSend,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSend' is greater than the size of the object referenced by argument 4");
extern long __MsgSend_alias(int __coid, const void *__smsg, _Sizet __sbytes, void *__rmsg, _Sizet __rbytes) __ALIASATTR("MsgSend");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSend_r,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSend_r' is greater than the size of the object referenced by argument 4");
extern long __MsgSend_r_alias(int __coid, const void *__smsg, _Sizet __sbytes, void *__rmsg, _Sizet __rbytes)
        __ALIASATTR("MsgSend_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendnc,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendnc' is greater than the size of the object referenced by argument 4");
extern long __MsgSendnc_alias(int __coid, const void *__smsg, _Sizet __sbytes, void *__rmsg, _Sizet __rbytes)
        __ALIASATTR("MsgSendnc");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendnc_r,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendnc_r' is greater than the size of the object referenced by argument 4");
extern long __MsgSendnc_r_alias(int __coid, const void *__smsg, _Sizet __sbytes, void *__rmsg, _Sizet __rbytes)
        __ALIASATTR("MsgSendnc_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendsv,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendsv' is greater than the number of 'struct iovec' elements in the object referenced by argument 4");
extern long __MsgSendsv_alias(int __coid, const void *__smsg, _Sizet __sbytes, const struct iovec *__riov, _Sizet __rparts)
        __ALIASATTR("MsgSendsv");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendsv_r,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendsv_r' is greater than the number of 'struct iovec' elements in the object referenced by argument 4");
extern long __MsgSendsv_r_alias(int __coid, const void *__smsg, _Sizet __sbytes, const struct iovec *__riov, _Sizet __rparts)
        __ALIASATTR("MsgSendsv_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendsvnc,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendsvnc' is greater than the number of 'struct iovec' elements in the object referenced by argument 4");
extern long __MsgSendsvnc_alias(int __coid, const void *__smsg, _Sizet __sbytes, const struct iovec *__riov, _Sizet __rparts)
        __ALIASATTR("MsgSendsvnc");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendsvnc_r,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendsvnc_r' is greater than the number of 'struct iovec' elements in the object referenced by "
                "argument 4");
extern long __MsgSendsvnc_r_alias(int __coid, const void *__smsg, _Sizet __sbytes, const struct iovec *__riov, _Sizet __rparts)
        __ALIASATTR("MsgSendsvnc_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendv,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendv' is greater than the number of 'struct iovec' elements in the object referenced by argument 4");
extern long __MsgSendv_alias(int __coid, const struct iovec *__siov, _Sizet __sparts, const struct iovec *__riov, _Sizet __rparts)
        __ALIASATTR("MsgSendv");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendv_r,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendv_r' is greater than the number of 'struct iovec' elements in the object referenced by argument 4");
extern long __MsgSendv_r_alias(int __coid, const struct iovec *__siov, _Sizet __sparts, const struct iovec *__riov, _Sizet __rparts)
        __ALIASATTR("MsgSendv_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendvnc,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendvnc' is greater than the number of 'struct iovec' elements in the object referenced by argument 4");
extern long __MsgSendvnc_alias(int __coid, const struct iovec *__siov, _Sizet __sparts, const struct iovec *__riov, _Sizet __rparts)
        __ALIASATTR("MsgSendvnc");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendvnc_r,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendvnc_r' is greater than the number of 'struct iovec' elements in the object referenced by "
                "argument 4");
extern long __MsgSendvnc_r_alias(
        int                 __coid,
        const struct iovec *__siov,
        _Sizet              __sparts,
        const struct iovec *__riov,
        _Sizet              __rparts
        ) __ALIASATTR("MsgSendvnc_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendvs,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendvs' is greater than the size of the object referenced by argument 4");
extern long __MsgSendvs_alias(int __coid, const struct iovec *__siov, _Sizet __sparts, void *__rmsg, _Sizet __rbytes)
        __ALIASATTR("MsgSendvs");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendvs_r,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendvs_r' is greater than the size of the object referenced by argument 4");
extern long __MsgSendvs_r_alias(int __coid, const struct iovec *__siov, _Sizet __sparts, void *__rmsg, _Sizet __rbytes)
        __ALIASATTR("MsgSendvs_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendvsnc,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendvsnc' is greater than the size of the object referenced by argument 4");
extern long __MsgSendvsnc_alias(int __coid, const struct iovec *__siov, _Sizet __sparts, void *__rmsg, _Sizet __rbytes)
        __ALIASATTR("MsgSendvsnc");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_MsgSendvsnc_r,
        __fortify_fail_overflow_dst,
        "argument 5 of 'MsgSendvsnc_r' is greater than the size of the object referenced by argument 4");
extern long __MsgSendvsnc_r_alias(int __coid, const struct iovec *__siov, _Sizet __sparts, void *__rmsg, _Sizet __rbytes)
        __ALIASATTR("MsgSendvsnc_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_SchedCtl,
        __fortify_fail_overflow_dst,
        "argument 3 of 'SchedCtl' is greater than the size of the object referenced by argument 2");
extern int __SchedCtl_alias(int __cmd, void *__data, size_t __length) __ALIASATTR("SchedCtl");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_overflow_dst_diag_SchedCtl_r,
        __fortify_fail_overflow_dst,
        "argument 3 of 'SchedCtl_r' is greater than the size of the object referenced by argument 2");
extern int __SchedCtl_r_alias(int __cmd, void *__data, size_t __length) __ALIASATTR("SchedCtl_r");

extern int __SyncCtl_chk(int __cmd, sync_t *__sync, void *__data, _Sizet __osize);
extern int __SyncCtl_chk_diag(int __cmd, sync_t *__sync, void *__data, _Sizet __osize) __ALIASATTR("__SyncCtl_chk")
        __FORTIFY_FAIL_DIAG_ATTRIBUTE(
                "argument 3 of 'SyncCtl' references an object smaller than expected for the command specified as argument 1");
extern int __SyncCtl_alias(int __cmd, sync_t *__sync, void *__data) __ALIASATTR("SyncCtl");

extern int __SyncCtl_r_chk(int __cmd, sync_t *__sync, void *__data, _Sizet __osize);
extern int __SyncCtl_r_chk_diag(int __cmd, sync_t *__sync, void *__data, _Sizet __osize) __ALIASATTR("__SyncCtl_r_chk")
        __FORTIFY_FAIL_DIAG_ATTRIBUTE(
                "argument 3 of 'SyncCtl_r' references an object smaller than expected for the command specified as argument 1");
extern int __SyncCtl_r_alias(int __cmd, sync_t *__sync, void *__data) __ALIASATTR("SyncCtl_r");

extern int __ThreadCtl_chk(int __cmd, void *__data, _Sizet __osize);
extern int __ThreadCtl_chk_diag(int __cmd, void *__data, _Sizet __osize) __ALIASATTR("__ThreadCtl_chk")
        __FORTIFY_FAIL_DIAG_ATTRIBUTE(
                "argument 2 of 'ThreadCtl' references an object smaller than expected for the command specified as argument 1");
extern int __ThreadCtl_alias(int __cmd, void *__data) __ALIASATTR("ThreadCtl");

extern int __ThreadCtl_r_chk(int __cmd, void *__data, _Sizet __osize);
extern int __ThreadCtl_r_chk_diag(int __cmd, void *__data, _Sizet __osize) __ALIASATTR("__ThreadCtl_r_chk")
        __FORTIFY_FAIL_DIAG_ATTRIBUTE(
                "argument 2 of 'ThreadCtl_r' references an object smaller than expected for the command specified as argument 1");
extern int __ThreadCtl_r_alias(int __cmd, void *__data) __ALIASATTR("ThreadCtl_r");

extern int __ThreadCtlExt_chk(pid_t __pid, int __tid, int __cmd, void *__data, _Sizet __osize);
extern int __ThreadCtlExt_chk_diag(pid_t __pid, int __tid, int __cmd, void *__data, _Sizet __osize)
        __ALIASATTR("__ThreadCtlExt_chk")
        __FORTIFY_FAIL_DIAG_ATTRIBUTE(
                "argument 2 of 'ThreadCtlExt' references an object smaller than expected for the command specified as argument 1");
extern int __ThreadCtlExt_alias(pid_t __pid, int __tid, int __cmd, void *__data) __ALIASATTR("ThreadCtlExt");

extern int __ThreadCtlExt_r_chk(pid_t __pid, int __tid, int __cmd, void *__data, _Sizet __osize);
extern int __ThreadCtlExt_r_chk_diag(pid_t __pid, int __tid, int __cmd, void *__data, _Sizet __osize)
        __ALIASATTR("__ThreadCtlExt_r_chk")
        __FORTIFY_FAIL_DIAG_ATTRIBUTE(
                "argument 2 of 'ThreadCtlExt_r' references an object smaller than expected for the command specified as "
                        "argument 1");
extern int __ThreadCtlExt_r_alias(pid_t __pid, int __tid, int __cmd, void *__data) __ALIASATTR("ThreadCtlExt_r");

__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_extra_arg_diag_TraceEvent,
        __fortify_fail_extra_arg,
        "more than 5 arguments specified to 'TraceEvent'");
__FORTIFY_FAIL_ALIAS_DECL(
        __fortify_fail_missing_arg_diag_TraceEvent,
        __fortify_fail_missing_arg,
        "insufficient arguments specified to 'TraceEvent' for the command specified as argument 1");
extern int __TraceEvent_alias(int __code, ...) __ALIASATTR("TraceEvent");


/**
 * Validates whether or not a combination of cmd and data arguments specified to a SyncCtl/SyncCtl_r call might result in anomalous
 * program behaviour.
 *
 * @param[in]  cmd           Command code passed to SyncCtl/SyncCtl_r.
 * @param[in]  data          Data pointer passed to SyncCtl/SyncCtl_r.
 * @param[in]  osize         Size of the data object known at compile time.
 * @param[in]  compile_time  If true (non-zero), only perform validation using values known to be constant at compile time.
 *
 * @retval  __FORTIFY_RESULT_OK            The combination of cmd and data arguments is valid, or compile_time was specified as true
 *                                         and one or more values required for validation isn't known to be constant at compile
 *                                         time.
 * @retval  __FORTIFY_RESULT_OVERFLOW_DST  The combination of cmd and data arguments may result in SyncCtl/SyncCtl_r writing past
 *                                         the end of the object pointed to by data.
 */
extern __FORTIFY_FUNCTION int __fortify_validate_SyncCtl_data(
        const int            __cmd,
        const void   * const __data __attribute__((__unused__)),
        const _Sizet         __osize,
        const int            __compile_time)
{
    if ( !__compile_time || __bconst(__cmd) ) {

        switch ( __cmd ) {

        case _NTO_SCTL_GETPRIOCEILING:

            /* __data is expected to be a pointer to an int */
            if ( __osize < sizeof(int) ) {
                return __FORTIFY_RESULT_OVERFLOW_DST;
            }
            break;

        case _NTO_SCTL_MUTEX_CONSISTENT:
        case _NTO_SCTL_MUTEX_WAKEUP:
        case _NTO_SCTL_SEM_VALUE:
        case _NTO_SCTL_SETEVENT:
        case _NTO_SCTL_SETPRIOCEILING:
        default:

            /* No data will be populated into *__data */
            break;
        }
    }

    return __FORTIFY_RESULT_OK;
}

/**
 * Validates whether or not a combination of cmd and data arguments specified to a ThreadCtl/ThreadCtl_r call might result in
 * anomalous program behaviour.
 *
 * @param[in]  cmd           Command code passed to ThreadCtl/ThreadCtl_r.
 * @param[in]  data          Data pointer passed to ThreadCtl/ThreadCtl_r.
 * @param[in]  osize         Size of the data object known at compile time.
 * @param[in]  compile_time  If true (non-zero), only perform validation using values known to be constant at compile time.
 *
 * @retval  __FORTIFY_RESULT_OK            The combination of cmd and data arguments is valid, or compile_time was specified as true
 *                                         and one or more values required for validation isn't known to be constant at compile
 *                                         time.
 * @retval  __FORTIFY_RESULT_OVERFLOW_DST  The combination of cmd and data arguments may result in ThreadCtl/ThreadCtl_r writing
 *                                         past the end of the object pointed to by data.
 */
extern __FORTIFY_FUNCTION int __fortify_validate_ThreadCtl_data(
        const int            __cmd,
        const void   * const __data,
        const _Sizet         __osize,
        const int            __compile_time)
{
    if ( !__compile_time || __bconst(__cmd) ) {

        switch ( __cmd ) {

        case _NTO_TCTL_ALIGN_FAULT:
        case _NTO_TCTL_RUNMASK_GET_AND_SET:

            /* __data is expected to be a pointer to an int or unsigned int */
            if ( __osize < sizeof(int) ) {
                return __FORTIFY_RESULT_OVERFLOW_DST;
            }
            break;

        case _NTO_TCTL_NAME:

            /* __data is expected to be a pointer to a struct _thread_name. The name_buf_len member of the struct _thread_name
             * indicates the maximum number of subsequent bytes that may be read and/or written */
            if ( __osize < __builtin_offsetof(struct _thread_name, name_buf) ) {
                return __FORTIFY_RESULT_OVERFLOW_DST;
            }
            if ( ( !__compile_time || __bconst(((struct _thread_name *)__data)->name_buf_len) ) &&
                    ( ((struct _thread_name *)__data)->name_buf_len > 0 ) &&
                    ( (unsigned int)((struct _thread_name *)__data)->name_buf_len >
                            (__osize - __builtin_offsetof(struct _thread_name, name_buf)) ) ) {
                return __FORTIFY_RESULT_OVERFLOW_DST;
            }
            break;

        case _NTO_TCTL_RUNMASK_GET_AND_SET_INHERIT:

            /* __data is expected to be a pointer to a struct _thread_runmask. The size member of the struct _thread_runmask
             * indicates the length of the subsequent runmask and inherit_mask arrays with elements of type unsigned int. */
            if ( __osize < sizeof(struct _thread_runmask) ) {
                return __FORTIFY_RESULT_OVERFLOW_DST;
            }
            if ( ( !__compile_time || __bconst(((struct _thread_runmask *)__data)->size) ) &&
                    ( ((struct _thread_runmask *)__data)->size > 0 ) &&
                    ( (unsigned int)((struct _thread_runmask *)__data)->size >
                            (((__osize - sizeof(struct _thread_runmask)) / (2 * sizeof(unsigned int)))) ) ) {
                return __FORTIFY_RESULT_OVERFLOW_DST;
            }
            break;

        case _NTO_TCTL_SIGSTACK:

            /* __data is expected to be a pointer to a stack_t */
            if ( __osize < sizeof(stack_t) ) {
                return __FORTIFY_RESULT_OVERFLOW_DST;
            }
            break;

        case _NTO_TCTL_ADD_EXIT_EVENT:
        case _NTO_TCTL_DEL_EXIT_EVENT:
        case _NTO_TCTL_IO:
        case _NTO_TCTL_IO_LEVEL:
        case _NTO_TCTL_IO_PRIV:
        case _NTO_TCTL_ONE_THREAD_CONT:
        case _NTO_TCTL_ONE_THREAD_HOLD:
        case _NTO_TCTL_RUNMASK:
        case _NTO_TCTL_THREADS_CONT:
        case _NTO_TCTL_THREADS_HOLD:
        default:

            /* No data will be populated into *__data */
            break;
        }
    }

    return __FORTIFY_RESULT_OK;
}


#if __NTO_FORTIFY_LEVEL > 0

extern __FORTIFY_FUNCTION int ConnectClientInfo(const int __scoid, struct _client_info * const __info, const int __ngroups)
{
    __FORTIFY_CHK_OVERFLOW_DST_MEMBER(
            __BOS_TYPE_OUTER,
            __info,
            cred.grouplist[0],
            (unsigned int)__ngroups,
            __ngroups > 0,
            __fortify_fail_overflow_dst_diag_ConnectClientInfo);
    return __ConnectClientInfo_alias(__scoid, __info, __ngroups);
}

extern __FORTIFY_FUNCTION int ConnectClientInfo_r(const int __scoid, struct _client_info * const __info, const int __ngroups)
{
    __FORTIFY_CHK_OVERFLOW_DST_MEMBER(
            __BOS_TYPE_OUTER,
            __info,
            cred.grouplist[0],
            (unsigned int)__ngroups,
            __ngroups > 0,
            __fortify_fail_overflow_dst_diag_ConnectClientInfo_r);
    return __ConnectClientInfo_r_alias(__scoid, __info, __ngroups);
}

extern __FORTIFY_FUNCTION int ConnectClientInfoAble(
        const int                    __scoid,
        struct _client_info ** const __info_pp,
        const int                    __flags,
        struct _client_able  * const __abilities,
        const int                    __nable)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            __abilities,
            (unsigned int)__nable,
            __nable > 0,
            __fortify_fail_overflow_dst_diag_ConnectClientInfoAble);
    return __ConnectClientInfoAble_alias(__scoid, __info_pp, __flags, __abilities, __nable);
}

extern __FORTIFY_FUNCTION ssize_t MsgRead(const rcvid_t __rcvid, void * const __msg, const _Sizet __bytes, const _Sizet __offset)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__msg, __bytes, 1, __fortify_fail_overflow_dst_diag_MsgRead);
    return __MsgRead_alias(__rcvid, __msg, __bytes, __offset);
}

extern __FORTIFY_FUNCTION ssize_t MsgRead_r(const rcvid_t __rcvid, void * const __msg, const _Sizet __bytes, const _Sizet __offset)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__msg, __bytes, 1, __fortify_fail_overflow_dst_diag_MsgRead_r);
    return __MsgRead_r_alias(__rcvid, __msg, __bytes, __offset);
}

extern __FORTIFY_FUNCTION ssize_t MsgReadv(
        const rcvid_t              __rcvid,
        const struct iovec * const __iov,
        const _Sizet               __parts,
        const _Sizet               __offset)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __iov[0], so declare a complete struct iovec local to this block. A cast is needed to convert
     * __iov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__iov,
            __parts,
            1,
            __fortify_fail_overflow_dst_diag_MsgReadv);
    return __MsgReadv_alias(__rcvid, __iov, __parts, __offset);
}

extern __FORTIFY_FUNCTION ssize_t MsgReadv_r(
        const rcvid_t              __rcvid,
        const struct iovec * const __iov,
        const _Sizet               __parts,
        const _Sizet               __offset)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __iov[0], so declare a complete struct iovec local to this block. A cast is needed to convert
     * __iov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__iov,
            __parts,
            1,
            __fortify_fail_overflow_dst_diag_MsgReadv_r);
    return __MsgReadv_r_alias(__rcvid, __iov, __parts, __offset);
}

extern __FORTIFY_FUNCTION rcvid_t MsgReceive(
        const int                __chid,
        void             * const __msg,
        const _Sizet             __bytes,
        struct _msg_info * const __info)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__msg, __bytes, 1, __fortify_fail_overflow_dst_diag_MsgReceive);
    return __MsgReceive_alias(__chid, __msg, __bytes, __info);
}

extern __FORTIFY_FUNCTION rcvid_t MsgReceive_r(
        const int                __chid,
        void             * const __msg,
        const _Sizet             __bytes,
        struct _msg_info * const __info)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__msg, __bytes, 1, __fortify_fail_overflow_dst_diag_MsgReceive_r);
    return __MsgReceive_r_alias(__chid, __msg, __bytes, __info);
}

extern __FORTIFY_FUNCTION int MsgReceivePulse(
        const int                __chid,
        void             * const __pulse,
        const _Sizet             __bytes,
        struct _msg_info * const __info)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__pulse, __bytes, 1, __fortify_fail_overflow_dst_diag_MsgReceivePulse);
    return __MsgReceivePulse_alias(__chid, __pulse, __bytes, __info);
}

extern __FORTIFY_FUNCTION int MsgReceivePulse_r(
        const int                __chid,
        void             * const __pulse,
        const _Sizet             __bytes,
        struct _msg_info * const __info)
{
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_OUTER,
            (_Uint8t *)__pulse,
            __bytes,
            1,
            __fortify_fail_overflow_dst_diag_MsgReceivePulse_r);
    return __MsgReceivePulse_r_alias(__chid, __pulse, __bytes, __info);
}

extern __FORTIFY_FUNCTION rcvid_t MsgReceivev(
        const int                  __chid,
        const struct iovec * const __iov,
        const _Sizet               __parts,
        struct _msg_info   * const __info)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __iov[0], so declare a complete struct iovec local to this block. A cast is needed to convert
     * __iov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__iov,
            __parts,
            1,
            __fortify_fail_overflow_dst_diag_MsgReceivev);
    return __MsgReceivev_alias(__chid, __iov, __parts, __info);
}

extern __FORTIFY_FUNCTION rcvid_t MsgReceivev_r(
        const int                  __chid,
        const struct iovec * const __iov,
        const _Sizet               __parts,
        struct _msg_info   * const __info)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __iov[0], so declare a complete struct iovec local to this block. A cast is needed to convert
     * __iov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__iov,
            __parts,
            1,
            __fortify_fail_overflow_dst_diag_MsgReceivev_r);
    return __MsgReceivev_r_alias(__chid, __iov, __parts, __info);
}

extern __FORTIFY_FUNCTION long MsgSend(
        const int            __coid,
        const void   * const __smsg,
        const _Sizet         __sbytes,
        void         * const __rmsg,
        const _Sizet         __rbytes)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__rmsg, __rbytes, 1, __fortify_fail_overflow_dst_diag_MsgSend);
    return __MsgSend_alias(__coid, __smsg, __sbytes, __rmsg, __rbytes);
}

extern __FORTIFY_FUNCTION long MsgSend_r(
        const int            __coid,
        const void   * const __smsg,
        const _Sizet         __sbytes,
        void         * const __rmsg,
        const _Sizet         __rbytes)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__rmsg, __rbytes, 1, __fortify_fail_overflow_dst_diag_MsgSend_r);
    return __MsgSend_r_alias(__coid, __smsg, __sbytes, __rmsg, __rbytes);
}

extern __FORTIFY_FUNCTION long MsgSendnc(
        const int            __coid,
        const void   * const __smsg,
        const _Sizet         __sbytes,
        void         * const __rmsg,
        const _Sizet         __rbytes)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__rmsg, __rbytes, 1, __fortify_fail_overflow_dst_diag_MsgSendnc);
    return __MsgSendnc_alias(__coid, __smsg, __sbytes, __rmsg, __rbytes);
}

extern __FORTIFY_FUNCTION long MsgSendnc_r(
        const int            __coid,
        const void   * const __smsg,
        const _Sizet         __sbytes,
        void         * const __rmsg,
        const _Sizet         __rbytes)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__rmsg, __rbytes, 1, __fortify_fail_overflow_dst_diag_MsgSendnc_r);
    return __MsgSendnc_r_alias(__coid, __smsg, __sbytes, __rmsg, __rbytes);
}

extern __FORTIFY_FUNCTION long MsgSendsv(
        const int                  __coid,
        const void         * const __smsg,
        const _Sizet               __sbytes,
        const struct iovec * const __riov,
        const _Sizet               __rparts)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __riov[0], so declare a complete struct iovec local to this block. A cast is needed to
     * convert __riov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__riov,
            __rparts,
            1,
            __fortify_fail_overflow_dst_diag_MsgSendsv);
    return __MsgSendsv_alias(__coid, __smsg, __sbytes, __riov, __rparts);
}

extern __FORTIFY_FUNCTION long MsgSendsv_r(
        const int                  __coid,
        const void         * const __smsg,
        const _Sizet               __sbytes,
        const struct iovec * const __riov,
        const _Sizet               __rparts)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __riov[0], so declare a complete struct iovec local to this block. A cast is needed to
     * convert __riov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__riov,
            __rparts,
            1,
            __fortify_fail_overflow_dst_diag_MsgSendsv_r);
    return __MsgSendsv_r_alias(__coid, __smsg, __sbytes, __riov, __rparts);
}

extern __FORTIFY_FUNCTION long MsgSendsvnc(
        const int                  __coid,
        const void         * const __smsg,
        const _Sizet               __sbytes,
        const struct iovec * const __riov,
        const _Sizet               __rparts)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __riov[0], so declare a complete struct iovec local to this block. A cast is needed to
     * convert __riov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__riov,
            __rparts,
            1,
            __fortify_fail_overflow_dst_diag_MsgSendsvnc);
    return __MsgSendsvnc_alias(__coid, __smsg, __sbytes, __riov, __rparts);
}

extern __FORTIFY_FUNCTION long MsgSendsvnc_r(
        const int                  __coid,
        const void         * const __smsg,
        const _Sizet               __sbytes,
        const struct iovec * const __riov,
        const _Sizet               __rparts)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __riov[0], so declare a complete struct iovec local to this block. A cast is needed to
     * convert __riov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__riov,
            __rparts,
            1,
            __fortify_fail_overflow_dst_diag_MsgSendsvnc_r);
    return __MsgSendsvnc_r_alias(__coid, __smsg, __sbytes, __riov, __rparts);
}

extern __FORTIFY_FUNCTION long MsgSendv(
        const int                  __coid,
        const struct iovec * const __siov,
        const _Sizet               __sparts,
        const struct iovec * const __riov,
        const _Sizet               __rparts)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __riov[0], so declare a complete struct iovec local to this block. A cast is needed to
     * convert __riov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__riov,
            __rparts,
            1,
            __fortify_fail_overflow_dst_diag_MsgSendv);
    return __MsgSendv_alias(__coid, __siov, __sparts, __riov, __rparts);
}

extern __FORTIFY_FUNCTION long MsgSendv_r(
        const int                  __coid,
        const struct iovec * const __siov,
        const _Sizet               __sparts,
        const struct iovec * const __riov,
        const _Sizet               __rparts)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __riov[0], so declare a complete struct iovec local to this block. A cast is needed to
     * convert __riov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__riov,
            __rparts,
            1,
            __fortify_fail_overflow_dst_diag_MsgSendv_r);
    return __MsgSendv_r_alias(__coid, __siov, __sparts, __riov, __rparts);
}

extern __FORTIFY_FUNCTION long MsgSendvnc(
        const int                  __coid,
        const struct iovec * const __siov,
        const _Sizet               __sparts,
        const struct iovec * const __riov,
        const _Sizet               __rparts)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __riov[0], so declare a complete struct iovec local to this block. A cast is needed to
     * convert __riov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__riov,
            __rparts,
            1,
            __fortify_fail_overflow_dst_diag_MsgSendvnc);
    return __MsgSendvnc_alias(__coid, __siov, __sparts, __riov, __rparts);
}

extern __FORTIFY_FUNCTION long MsgSendvnc_r(
        const int                  __coid,
        const struct iovec * const __siov,
        const _Sizet               __sparts,
        const struct iovec * const __riov,
        const _Sizet               __rparts)
{
#if defined(__IOVEC_T)
    /* struct iovec has been declared with file scope but its contents have not been defined. The __FORTIFY_CHK_OVERFLOW_DST macro
     * performs a sizeof operation on __riov[0], so declare a complete struct iovec local to this block. A cast is needed to
     * convert __riov from a pointer to the incomplete, file-scoped struct iovec into a pointer to the complete, block-scoped
     * struct iovec. */
    __IOVEC_T;
#endif
    __FORTIFY_CHK_OVERFLOW_DST(
            __BOS_TYPE_DEFAULT,
            (const struct iovec *)__riov,
            __rparts,
            1,
            __fortify_fail_overflow_dst_diag_MsgSendvnc_r);
    return __MsgSendvnc_r_alias(__coid, __siov, __sparts, __riov, __rparts);
}

extern __FORTIFY_FUNCTION long MsgSendvs(
        const int                  __coid,
        const struct iovec * const __siov,
        const _Sizet               __sparts,
        void               * const __rmsg,
        const _Sizet               __rbytes)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__rmsg, __rbytes, 1, __fortify_fail_overflow_dst_diag_MsgSendvs);
    return __MsgSendvs_alias(__coid, __siov, __sparts, __rmsg, __rbytes);
}

extern __FORTIFY_FUNCTION long MsgSendvs_r(
        const int                  __coid,
        const struct iovec * const __siov,
        const _Sizet               __sparts,
        void               * const __rmsg,
        const _Sizet               __rbytes)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__rmsg, __rbytes, 1, __fortify_fail_overflow_dst_diag_MsgSendvs_r);
    return __MsgSendvs_r_alias(__coid, __siov, __sparts, __rmsg, __rbytes);
}

extern __FORTIFY_FUNCTION long MsgSendvsnc(
        const int                  __coid,
        const struct iovec * const __siov,
        const _Sizet               __sparts,
        void               * const __rmsg,
        const _Sizet               __rbytes)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__rmsg, __rbytes, 1, __fortify_fail_overflow_dst_diag_MsgSendvsnc);
    return __MsgSendvsnc_alias(__coid, __siov, __sparts, __rmsg, __rbytes);
}

extern __FORTIFY_FUNCTION long MsgSendvsnc_r(
        const int                  __coid,
        const struct iovec * const __siov,
        const _Sizet               __sparts,
        void               * const __rmsg,
        const _Sizet               __rbytes)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__rmsg, __rbytes, 1, __fortify_fail_overflow_dst_diag_MsgSendvsnc_r);
    return __MsgSendvsnc_r_alias(__coid, __siov, __sparts, __rmsg, __rbytes);
}

extern __FORTIFY_FUNCTION int SchedCtl(const int __cmd, void * const __data, const size_t __length)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__data, __length, 1, __fortify_fail_overflow_dst_diag_SchedCtl);
    return __SchedCtl_alias(__cmd, __data, __length);
}

extern __FORTIFY_FUNCTION int SchedCtl_r(const int __cmd, void * const __data, const size_t __length)
{
    __FORTIFY_CHK_OVERFLOW_DST(__BOS_TYPE_OUTER, (_Uint8t *)__data, __length, 1, __fortify_fail_overflow_dst_diag_SchedCtl_r);
    return __SchedCtl_r_alias(__cmd, __data, __length);
}

extern __FORTIFY_FUNCTION int SyncCtl(const int __cmd, sync_t * const __sync, void * const __data)
{
    /* Fail if the specified command (__cmd) will write to the object pointed to by the __data argument and that object is of
     * insufficient length. Also emit an error/warning if the __cmd argument is known to be constant at compile time. __bos0 is used
     * to obtain the length of the destination object instead of __bos in order to reduce false positives when the _FORTIFY_SOURCE
     * feature test macro has been defined with a value greater than 1. */
    if ( __bos_outer(__data) != __BOS_UNKNOWN ) {
        if ( __fortify_validate_SyncCtl_data(__cmd, __data, __bos_outer(__data), 1) != __FORTIFY_RESULT_OK ) {
            return __SyncCtl_chk_diag(__cmd, __sync, __data, __bos_outer(__data));
        } else {
            return __SyncCtl_chk(__cmd, __sync, __data, __bos_outer(__data));
        }
    } else {
        return __SyncCtl_alias(__cmd, __sync, __data);
    }
}

extern __FORTIFY_FUNCTION int SyncCtl_r(const int __cmd, sync_t * const __sync, void * const __data)
{
    /* Fail if the specified command (__cmd) will write to the object pointed to by the __data argument and that object is of
     * insufficient length. Also emit an error/warning if the __cmd argument is known to be constant at compile time. __bos0 is used
     * to obtain the length of the destination object instead of __bos in order to reduce false positives when the _FORTIFY_SOURCE
     * feature test macro has been defined with a value greater than 1. */
    if ( __bos_outer(__data) != __BOS_UNKNOWN ) {
        if ( __fortify_validate_SyncCtl_data(__cmd, __data, __bos_outer(__data), 1) != __FORTIFY_RESULT_OK ) {
            return __SyncCtl_r_chk_diag(__cmd, __sync, __data, __bos_outer(__data));
        } else {
            return __SyncCtl_r_chk(__cmd, __sync, __data, __bos_outer(__data));
        }
    } else {
        return __SyncCtl_r_alias(__cmd, __sync, __data);
    }
}

extern __FORTIFY_FUNCTION int ThreadCtl(const int __cmd, void * const __data)
{
    /* Fail if the specified command (__cmd) will write to the object pointed to by the __data argument and that object is of
     * insufficient length. Also emit an error/warning if the __cmd argument is known to be constant at compile time. __bos0 is used
     * to obtain the length of the destination object instead of __bos in order to reduce false positives when the _FORTIFY_SOURCE
     * feature test macro has been defined with a value greater than 1. */
    if ( __bos_outer(__data) != __BOS_UNKNOWN ) {
        if ( __fortify_validate_ThreadCtl_data(__cmd, __data, __bos_outer(__data), 1) != __FORTIFY_RESULT_OK ) {
            return __ThreadCtl_chk_diag(__cmd, __data, __bos_outer(__data));
        } else {
            return __ThreadCtl_chk(__cmd, __data, __bos_outer(__data));
        }
    } else {
        return __ThreadCtl_alias(__cmd, __data);
    }
}

extern __FORTIFY_FUNCTION int ThreadCtl_r(const int __cmd, void * const __data)
{
    /* Fail if the specified command (__cmd) will write to the object pointed to by the __data argument and that object is of
     * insufficient length. Also emit an error/warning if the __cmd argument is known to be constant at compile time. __bos0 is used
     * to obtain the length of the destination object instead of __bos in order to reduce false positives when the _FORTIFY_SOURCE
     * feature test macro has been defined with a value greater than 1. */
    if ( __bos_outer(__data) != __BOS_UNKNOWN ) {
        if ( __fortify_validate_ThreadCtl_data(__cmd, __data, __bos_outer(__data), 1) != __FORTIFY_RESULT_OK ) {
            return __ThreadCtl_r_chk_diag(__cmd, __data, __bos_outer(__data));
        } else {
            return __ThreadCtl_r_chk(__cmd, __data, __bos_outer(__data));
        }
    } else {
        return __ThreadCtl_r_alias(__cmd, __data);
    }
}

extern __FORTIFY_FUNCTION int ThreadCtlExt(const pid_t __pid, const int __tid, const int __cmd, void * const __data)
{
    /* Fail if the specified command (__cmd) will write to the object pointed to by the __data argument and that object is of
     * insufficient length. Also emit an error/warning if the __cmd argument is known to be constant at compile time. __bos0 is used
     * to obtain the length of the destination object instead of __bos in order to reduce false positives when the _FORTIFY_SOURCE
     * feature test macro has been defined with a value greater than 1. */
    if ( __bos_outer(__data) != __BOS_UNKNOWN ) {
        if ( __fortify_validate_ThreadCtl_data(__cmd, __data, __bos_outer(__data), 1) != __FORTIFY_RESULT_OK ) {
            return __ThreadCtlExt_chk_diag(__pid, __tid, __cmd, __data, __bos_outer(__data));
        } else {
            return __ThreadCtlExt_chk(__pid, __tid, __cmd, __data, __bos_outer(__data));
        }
    } else {
        return __ThreadCtlExt_alias(__pid, __tid, __cmd, __data);
    }
}

extern __FORTIFY_FUNCTION int ThreadCtlExt_r(const pid_t __pid, const int __tid, const int __cmd, void * const __data)
{
    /* Fail if the specified command (__cmd) will write to the object pointed to by the __data argument and that object is of
     * insufficient length. Also emit an error/warning if the __cmd argument is known to be constant at compile time. __bos0 is used
     * to obtain the length of the destination object instead of __bos in order to reduce false positives when the _FORTIFY_SOURCE
     * feature test macro has been defined with a value greater than 1. */
    if ( __bos_outer(__data) != __BOS_UNKNOWN ) {
        if ( __fortify_validate_ThreadCtl_data(__cmd, __data, __bos_outer(__data), 1) != __FORTIFY_RESULT_OK ) {
            return __ThreadCtlExt_r_chk_diag(__pid, __tid, __cmd, __data, __bos_outer(__data));
        } else {
            return __ThreadCtlExt_r_chk(__pid, __tid, __cmd, __data, __bos_outer(__data));
        }
    } else {
        return __ThreadCtlExt_r_alias(__pid, __tid, __cmd, __data);
    }
}

extern __FORTIFY_FUNCTION int TraceEvent(const int __code, ...)
{
    /* Fail and emit an error/warning if the caller specified more arguments than the maximum number expected for any of the
     * supported commands */
    if ( __bvap_len > 4 ) {
        __fortify_fail_extra_arg_diag_TraceEvent();
    /* Fail if the caller specified insufficient arguments for the specified command (__code). Also emit an error/warning if the
     * __code argument is known to be constant at compile time. */
    } else {
         __FORTIFY_CHK(
                 (unsigned int)__code >> 28,
                 ((unsigned int)__code >> 28) > (unsigned int)(__bvap_len + 1),
                __fortify_fail_missing_arg_diag_TraceEvent,
                __fortify_fail_missing_arg);
    }
    return __TraceEvent_alias(__code, __bvap);
}

#endif /* #if __NTO_FORTIFY_LEVEL > 0 */

__END_DECLS

#endif /* #ifndef __NEUTRINO_CHK_H_INCLUDED */
