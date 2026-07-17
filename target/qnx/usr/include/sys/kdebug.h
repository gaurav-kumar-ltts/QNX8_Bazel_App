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



/*
 *  sys/kdebug.h
 *

 */
#ifndef __KDEBUG_H_INCLUDED
#define __KDEBUG_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#define KDEBUG_PROC_CURRENT			3U
#define KDEBUG_CURRENT				2U

#define KDEBUG_TYPE_PROCESS			0U
#define KDEBUG_TYPE_OBJECT			1U

#define KDREQ_PARKIT				2U
#define KDREQ_DUMP_SWEEP			5U
#define KDREQ_SHUTDOWN_REPORT		6U

union kd_request {
	struct kdr_hdr {
		unsigned	req;
	}							hdr;	/*in*/

	struct kdr_parkit {
		struct kdr_hdr	hdr;			/*in*/
		unsigned		cpu;			/*in*/
	}							parkit;

	struct kdr_dump_sweep {
		struct kdr_hdr	hdr;			/*in*/
		int				do_filter;		/*in*/
		_Paddr64t		paddr;			/*in/out*/
		_Paddr64t		size;			/*out*/
	}							dump_sweep;

	struct kdr_shutdown_report {
		struct kdr_hdr	hdr;				/*in*/
		unsigned				sigcode;	/*in*/
		const void				*regs;		/*in*/
	}							shutdown_report;
};


typedef int (*kdrequest_t)(union kd_request *);

/* <STAN_MACRO1, STAN_MACRO5/> */
#define __KDEBUG_INFO_SIZED(__sname, __voidp, __requestfn, __kdebugprivatep, __ccharp, __kdumpprivatep) \
	struct __sname { \
		unsigned char					proc_version; /* KDEBUG_PROC_CURRENT */ \
		unsigned char					debug_version; \
		unsigned short					flags; \
		__voidp							unused1[3]; \
		__requestfn						request; \
		__kdebugprivatep				kdbg_private; \
		__voidp							unused2; \
		__ccharp						timestamp; \
		__voidp							unused3; \
		__kdumpprivatep					kdump_private; \
		__voidp							reserved[5]; \
	}
__KDEBUG_INFO_SIZED(kdebug_info, void*, kdrequest_t, const struct kdebug_private*, const char*, const struct kdump_private*);
__KDEBUG_INFO_SIZED(kdebug_info64, _Uint64t, _Uint64t, _Uint64t, _Uint64t, _Uint64t);		/* <STAN_TAGNAME/> */

struct kdebug_callback {
	unsigned short					kdebug_version; /* KDEBUG_CURRENT */
	unsigned short					callback_len;
	void							*reserved1;
	unsigned						(*fault_entry)(void *entry, unsigned sigcode, void *regs);
	void							*reserved2[2];
	struct cpu_extra_state			*extra;
	void							*reserved3[7];
};


/* <STAN_MACRO1, STAN_MACRO5/> */
#define __KDEBUG_VECTOR_ENTRY_SIZED(__sname, __voidpp) \
	struct __sname { \
		__voidpp		vector; \
		unsigned short	nentries; \
		unsigned short	base_id; \
	}
__KDEBUG_VECTOR_ENTRY_SIZED(kdebug_vector_entry, void**);
__KDEBUG_VECTOR_ENTRY_SIZED(kdebug_vector_entry64, _Uint64t);


#define KDEBUG_VECTOR_VER			2U

/* <STAN_MACRO1, STAN_MACRO5/> */
#define __KDEBUG_PRIVATE_SIZED(__sname, __voidp, __voidpp, __vector_entryp) \
	struct __sname { \
		unsigned						flags; \
		__voidp							actives;			/* pointer to the active array pointer */ \
		__voidp							aspaces;			/* pointer to the aspaces_prp array pointer */ \
		__voidpp						irqstack;			/* pointer to irq stack */ \
		__vector_entryp					process_vector;		/* pointer to process vector */ \
		unsigned short					vector_ver;			/* version of vector type */ \
		unsigned short					th_tid_off;			/* offset within active to tid */ \
		unsigned short					th_reg_off;			/* offset within active to registers */ \
		unsigned short					th_process_off;		/* offset within active to process entry */ \
		unsigned short					pr_pid_off;			/* offset within process to pid */ \
		unsigned short					pr_debug_name_off;	/* offset within process to name pointer */ \
		unsigned short					irq_reg_off;		/* offset within irq stack to registers */ \
		unsigned short					pr_threads_off;		/* offset within process to threads vector */ \
		unsigned short					pr_kdebug_off;		/* offset within process to kdebug_entry */ \
		unsigned short					th_pri_off;			/* offset within thread entry of priority */ \
		unsigned short					pr_memory_off;		/* offset within process entry of memory */ \
		unsigned short					th_client_off;		/* offset within thread to client*/ \
		__voidp							percpu;				/* base of per-cpu area */ \
		unsigned short					percpu_stride;		/* distance to next cpu entry in per-cpu area*/ \
		unsigned short					percpu_active_off;	/* offset of active thread in percpu entry*/ \
		__voidp							muon_cpus;			/* base of per-cpu area */ \
		unsigned short					mcpu_stride;		/* size of per-cpu area*/ \
		unsigned short					mcpu_active_off;	/* offset of active muon thread in muon_cpu_t */ \
		unsigned short					mthr_nto_thread_off; /* offset of pointer to THREAD in muon_thread_t */ \
	}
__KDEBUG_PRIVATE_SIZED(kdebug_private, void*, void**, struct kdebug_vector_entry*);
__KDEBUG_PRIVATE_SIZED(kdebug_private64, _Uint64t, _Uint64t, _Uint64t);

#define KDUMP_VERSION 2U

typedef void (*kdump_dump_sweep_t)(int do_filter, _Paddr64t *ppaddr, _Paddr64t *psize);

/* <STAN_MACRO1, STAN_MACRO5/> */
#define __KDUMP_PRIVATE_SIZED(__sname, __voidp, __uintptrtp, __kdump_sweep) \
	struct __sname { \
		unsigned short				kdump_version;			/* version of kdump structure */ \
		unsigned short				as_hat_off;				/* offset within aspace entry of hat_aspace */ \
		__kdump_sweep				dump_sweep;				/* pmem iterator function */ \
	}
__KDUMP_PRIVATE_SIZED(kdump_private, void*, _Uintptrt*, kdump_dump_sweep_t);
__KDUMP_PRIVATE_SIZED(kdump_private64, _Uint64t, _Uint64t, _Uint64t);

struct kprintf_ringbuffer {
	_Uint32t			buf_magic;
	_Uint32t			buf_size;
	volatile _Uint32t	buf_idx;
	_Uint32t			pad[5];
	char				buf[1];
};

#define KPRINTF_ACTIVE_RINGBUFFER	0xbeefeeeeU
#define KPRINTF_INACTIVE_RINGBUFFER 0xdeadbeefU

#endif
