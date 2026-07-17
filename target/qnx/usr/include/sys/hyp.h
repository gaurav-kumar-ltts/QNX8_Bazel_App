/*
 * $QNXLicenseC:
 * Copyright 2015-2023, QNX Software Systems. All Rights Reserved.
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

/**
 * @file
 * hyp.h   hypervisor interface definitions
 */
#ifndef __HYP_H_INCLUDED
#define __HYP_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif


#define HYP_VERSION_MAJOR  2U
#define HYP_VERSION_MINOR  0U

#define HYP_GLOBAL_ID_NAME  "HYP global ID"

#define HYP_GUEST_ID_NONE   (~(uint64_t)0U)


#if defined(__X86_64__)

typedef struct arch_hyp_data_s {
    /** On privileged function return, the ISR for this IDT is run (if non-zero) */
    unsigned    intr_vector;
} arch_hyp_data_t;

#elif defined(__aarch64__)

typedef struct arch_hyp_data_s {
    // None
} arch_hyp_data_t;

#else
#error "Unknown architecture"
#endif

/**
 * Data shared by the kernel hypervisor layer with a hyp_privileged_function_t
 */
typedef struct hyp_data_s {
    _Uint64t        *guest_id; /**< Latest guest id to have run on the current CPU */
    arch_hyp_data_t  arch;
} hyp_data_t;


/**
 * Hypervisor Privilege function prototype
 *
 * Client functions with this signature can be run via the privileged function
 * call interface. This can be used for any kind of function that requires
 * hypervisor privilege, but the environment in which the function runs is
 * specialized in particular for the needs of a function that will perform a
 * guest enter and later handle the exit.
 *
 * All architectures:
 * - hyp_init_msg_t provides the address of the hyp_priv_func_wrapper_t
 * - calling thread must be running with ThreadCtl _NTO_TCTL_HYP_VCPU which
 *   requires procmgr ability, PROCMGR_AID_HYP, this marks the thread as a vcpu
 *   that runs at the host OS privilege level
 * - function runs with interrupts disabled
 *
 * Aarch64 EL1 Host specifics:
 * - calling thread must:
 *   - setup registers as though calling hyp_priv_func_wrapper_t directly
 *   - then issue HVC 0
 * - function runs on caller's stack but SP is transfered to SP_EL2
 *
 * Aarch64 EL2 Host specifics:
 * - calling thread must call hyp_priv_func_wrapper_t directly
 * - function runs on caller's stack but SP is transfered to SP_EL2 with
 *
 * x86_64 specifics:
 * - calling thread must call hyp_priv_func_wrapper_t directly
 */
typedef void (*hyp_privileged_function_t)(hyp_data_t *dat, void *p1, void *p2);


/**
 * Privilege function call wrapper prototype
 * Returned via hyp_init_reply_t if host OS supports direct calls
 */
typedef void (*hyp_priv_func_wrapper_t)(hyp_privileged_function_t func, void *p1, void *p2);


/**
 * Control Page Operations
 * The operation is determined by the offset from the start of the control page
 */

/** Force a guest virtual machine exit */
#define HCO_FORCE_GUEST_EXIT     (0x00U)

/** x86_64: Return the posted interrupt vector */
#define HCO_X86_GET_POST_VECTOR  (0x100U)


/**
 * Message sub-types supported by the hypervisor interface
 */
typedef enum hyp_msg_subtypes {
    /** See ::hyp_init_msg */
    HMS_INIT,

    HMS_NUM_SUBTYPES
} hyp_msg_subtypes_t;

/**
 * Layout of the header for all hypervisor messages
 */

typedef struct hyp_msg_header_s {
    _Uint16t  type;      /**< Must be _sys_bases::_HYP_BASE */
    _Uint16t  subtype;
} hyp_msg_header_t;

/**
 * Layout of the ::HMS_INIT message.
 */
typedef struct hyp_init_msg_s {
    hyp_msg_header_t  hdr; /**<  Must be: _HYP_BASE, HMS_INIT */
    _Uint32t  zero1;
    _Uint64t  control_page;
    _Uint32t  zero[4];
} hyp_init_msg_t;

/**
 * Layout of the ::HMS_INIT reply.
 */
typedef struct hyp_init_reply_s {
    struct {
        _Uint16t  major;             /**< HYP_VERSION_MAJOR */
        _Uint16t  minor;             /**< HYP_VERSION_MINOR */
    }  interface_version;
    _Uint32t  init_status;           /**< 0 = success, non-zero is failure */
    _Uint32t  init_status_desc_len;  /**< length of init_status_desc string */
    _Uint32t  in_safety_state;
    hyp_priv_func_wrapper_t  priv_func_wrapper;
    _Uint64t  reserved[4];
    char      init_status_desc[];        /**< variably sized string */
    /* To be followed by init_status_desc buffer space */
} hyp_init_reply_t;


/**
 * Union of possible message layouts for the type ::_HYP_BASE.
 */
typedef union hyp_all_msgs {
    hyp_msg_header_t     hdr;
    hyp_init_msg_t       init;
} hyp_all_msgs_t;

#endif
