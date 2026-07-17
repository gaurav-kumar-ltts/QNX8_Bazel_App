/*
 * Copyright (c) 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef __KPIPE_H_INCLUDED
#define __KPIPE_H_INCLUDED

#define _NTO_PIPE_CFG_SIMPLEX   0x00000000U
#define _NTO_PIPE_CFG_DUPLEX    0x00000004U

/**
 * @brief Structure specifying the nto pipe parameters.
 * @details The data in this structure is used when creating a new nto
 * pipe via PipeOpen() (with the pipe_id argument set to -1). This
 * describes the parameters of the new pipe object.
 */
typedef struct nto_pipe_cfg {
    /** The total size of the nto pipe buffer. */
    _Uint32t        pcfg_bufsz;
    /** The atomic write size used by the pipe.  */
    _Uint32t        pcfg_chunksz;
    /** The amount of available space in the buffer that will trigger
     * an IOFUNC_NOTIFY_OUTPUT event. */
    _Uint32t        pcfg_wnotify;
    /** Type of pipe (i.e. _NTO_PIPE_CFG_SIMPLEX or
     * _NTO_PIPE_CFG_DUPLEX). */
    _Uint32t        pcfg_type;
    /** Index of the buffer to use as the source. */
    _Uint32t        pcfg_sourcebuf;
    /** Reserved for future use; these also ensures that the structure
     * has 8-byte alignment. */
    _Uint32t        pcfg_reserved[11];
} nto_pipe_cfg_t;

// IDs of all supported `PipeCtl()` control messages.
#define _NTO_PIPE_CTL_NOTIFY    0x0001U
#define _NTO_PIPE_CTL_GETTIME   0x0002U
#define _NTO_PIPE_CTL_SETFLAGS  0x0003U
#define _NTO_PIPE_CTL_GETFLAGS  0x0004U
#define _NTO_PIPE_CTL_UNBLOCK   0x0005U
#define _NTO_PIPE_CTL_DISABLE   0x0006U

/**
 * @brief Common header for pipe control structures.
 * @details All control data passed to `PipeCtl()` is required to
 * define identical fields at the start of the structure.
 */
typedef struct nto_pipe_ctl_header {
    /** The control ID. */
    _Uint32t        pctl_id;
    /** The total length of the control structure and its payload. */
    _Uint32t        pctl_len;
} nto_pipe_ctl_header_t;

/**
 * @brief Structure used to query pipe times.
 * @details Instances of this structure passed to the PipeCtl() kernel
 * call to query a specified pipe for its access, modification, and/or
 * configuration times.
 */
typedef struct nto_pipe_ctl_gettime {
    /** The control ID; should always be _NTO_PIPE_CTL_GETTIME.
     * @see struct nto_pipe_ctl_header
     */
    _Uint32t        pctl_id;
    /** The total length of the structure.
     * @see struct nto_pipe_ctl_header
     */
    _Uint32t        pctl_len;
    /** A buffer to hold the pipe's access time. */
    _Uint64t        ptm_atime_nsec;
    /** A buffer to hold the pipe's configuration time. */
    _Uint64t        ptm_ctime_nsec;
    /** A buffer to hold the pipe's modification time. */
    _Uint64t        ptm_mtime_nsec;
} nto_pipe_ctl_gettime_t;

/**
 * @brief Structure used to check for I/O conditions.
 * @details This structure is passed to the PipeCtl() kernel call to
 * poll for I/O conditions, arm an event for when the conditions are
 * met, or disarm a previously armed event. This is used primarily in
 * support of handling calls to `ionotify()` on behalf of a client.
 */
typedef struct nto_pipe_ctl_notify {
    /** The control ID; should always be _NTO_PIPE_CTL_NOTIFY.
     * @see struct nto_pipe_ctl_header
     */
    _Uint32t        pctl_id;
    /** The total length of the structure.
     * @see struct nto_pipe_ctl_header
     */
    _Uint32t        pctl_len;
    /** The notify action. One of: POLL, POLL+ARM, or ARM+STATE.
     * @see PipeNotifyActions */
    _Uint32t        pno_action;
    /** The unique PID of the client on whose behalf the pipe's I/O
     * condition is being polled. */
    _Int64t         pno_pid64;
    /** The ID of the client thread on whose behalf the pipe's I/O
     * condition is being polled. */
    _Uint32t        pno_tid;
    /** The I/O condition flags to check. A combination of
     * _NOTIFY_COND_INPUT, _NOTIFY_COND_OUTPUT, or
     * _NOTIFY_COND_OBAND. Extended conditions are also supported. */
    _Uint32t        pno_condflags;
    /** Mask specifying any extra flags that should be set when an I/O
     * event is delivered (e.g. error conditions such as HUP). */
    _Uint32t        pno_extraflags;
    /** The event to deliver when a condition is met. This event must
     * have been registered unless the condition is being disarmed (by
     * setting the event type to SIGEV_NONE). */
    struct sigevent pno_event;
    /** A buffer where the reply indicating which I/O conditions are
     * currently met are returned. */
    _Uint32t *      pno_replybuf;
} nto_pipe_ctl_notify_t;

/**
 * @defgroup PipeNotifyActions
 * @brief Notification action flags supported by in-kernel pipes.
 * @{
 */
/** Poll for a particular I/O condition. When used on its own, this
 * flag will simply report whether a particular I/O condition is
 * satisfied without arming an event. */
#define PIPE_NOTIFY_ACTION_POLL     0x00000001U
/** Arm an I/O event. If combined with the PIPE_NOTIFY_ACTION_POLL
 * flag, the event will be armed only if the polled I/O condition is
 * not satisfied. */
#define PIPE_NOTIFY_ACTION_ARM      0x00000002U
/** Specify that an armed event is triggered by a change in buffer
 * state. This is valid for input events only and will restrict event
 * delivery to I/O operations that cause the buffer to go from empty
 * to non-empty. */
#define PIPE_NOTIFY_ACTION_STATE    0x00000004U
/** @) */

/**
 * @brief Structure used to query/set the status flags.
 * @details This structure is passed to the PipeCtl() kernel call to
 * allow a pipe's status flags to be queried or set. This is used
 * primarily in support of handling devctl() calls on file descriptors
 * associated with an in-kernel pipe.
 */
typedef struct nto_pipe_ctl_flags {
    /** The control ID; one of _NTO_PIPE_CTL_GETFLAGS, or
     * _NTO_PIPE_CTL_SETFLAGS.  @see struct nto_pipe_ctl_header */
    _Uint32t        pctl_id;
    /** The total length of the structure.
     * @@see struct nto_pipectl_header  */
    _Uint32t        pctl_len;
    /** New status flags to assign to the pipe. This will be ignored
     * if the control is _NTO_PIPE_CTL_GETFLAGS. */
    _Uint32t        pfl_newflags;
    /** Will hold the pipe's current flags upon return. */
    _Uint32t        pfl_curflags;
} nto_pipe_ctl_flags_t;

/**
 * @brief Union of all control structures supported by `PipeCtl()`.
 */
typedef union nto_pipe_ctl {
    /** The common header. */
    nto_pipe_ctl_header_t   header;
    /** _NTO_PIPE_CTL_GETTIME control message payload. */
    nto_pipe_ctl_gettime_t  pctl_gettime;
    /** _NTO_PIPE_CTL_NOTIFY control message payload. */
    nto_pipe_ctl_notify_t   pctl_notify;
    /** _NTO_PIPE_CTL_GETFLAGS/SETFLAGS control message payload. */
    nto_pipe_ctl_flags_t    pctl_flags;
} nto_pipe_ctl_t;
 
#endif  // __KPIPE_H_INCLUDED
