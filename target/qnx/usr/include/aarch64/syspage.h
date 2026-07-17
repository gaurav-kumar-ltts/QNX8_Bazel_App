/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

/*
 *  aarch64/syspage.h
 */

#ifndef __AARCH64_SYSPAGE_H_INCLUDED
#define __AARCH64_SYSPAGE_H_INCLUDED

#ifndef __SYSPAGE_H_INCLUDED
#error aarch64/syspage.h should not be included directly.
#endif

/*
 * CPU capability/state flags.
 *
 * This contains definitions of the legacy ARMv7 flags so that AArch32
 * programs can continue to check for feature flags as expected.
 */
#define	AARCH32_CPU_FLAG_V6			0x0002UL		/* ARMv6 ISA implemented */
#define	AARCH32_CPU_FLAG_SMP		0x0008UL		/* multiprocessor system */
#define AARCH32_CPU_FLAG_V7_MP		0x0010UL		/* ARMv7 multiprocessor extenstions */
#define AARCH32_CPU_FLAG_V7			0x0020UL		/* ARMv7 ISA implemented */
#define AARCH32_CPU_FLAG_NEON		0x0040UL		/* Neon Media Engine */
#define AARCH32_CPU_FLAG_CC_INCR_32	0x0200UL		/* CLOCKCYCLES_INCR_BIT == 32 */
#define AARCH32_CPU_FLAG_IDIV		0x0400UL		/* h/w divide: UDIV, SDIV supported */
#define	AARCH32_CPU_FLAG_VFP_D32	0x0800UL		/* VFP has 32 double registers */

#define	AARCH64_CPU_FLAG_SMP		(AARCH32_CPU_FLAG_SMP)
#define	AARCH64_CPU_FLAG_SIMD		(AARCH32_CPU_FLAG_NEON)
#define	AARCH64_CPU_FLAG_CC_INCR_32	(AARCH32_CPU_FLAG_CC_INCR_32)
#define AARCH64_CPU_FLAG_S32G_TLB_ERRATA	0x80UL	/* S32G va > 2TB need to use tlbi vmalle1is */
#define AARCH64_CPU_FLAG_IMX8QM_TLB_ERRATA	0x100UL	/* applicable only if Board Rev < 2.0(B0) */
#define AARCH64_CPU_SPECTRE_V2_FIX  0x1000UL
#define AARCH64_CPU_SPECTRE_V2_MMU  0x2000UL
#define AARCH64_CPU_ACTLR		0x4000UL
#define AARCH64_CPU_FLAG_LSE	0x8000UL
#define AARCH64_CPU_FLAG_VHE	0x00010000UL
#define AARCH64_CPU_PAUTH		0x20000UL
#define AARCH64_CPU_FLAG_KRYO_TLB	0x40000UL
#define AARCH64_CPU_SSBS		0x80000UL

#define AARCH64_CPU_FLAG_AES	0x100000UL
#define AARCH64_CPU_FLAG_PMULL	0x200000UL
#define AARCH64_CPU_FLAG_SHA1	0x400000UL
#define AARCH64_CPU_FLAG_SHA256	0x800000UL
#define AARCH64_CPU_FLAG_SHA512	0x1000000UL
#define AARCH64_CPU_FLAG_SHA3	0x2000000UL
#define AARCH64_CPU_FLAG_RNDR	0x4000000UL

#define AARCH64_CPU_FLAG_ICACHE_COHERENT	0x08000000UL

#define AARCH64_CPU_FLAG_SVE				0x10000000UL
#define AARCH64_CPU_FLAG_ERRATA_TLB_TFA		(1UL << 32)
#define AARCH64_CPU_FLAG_ERRATA_SB_TR		(1UL << 33)
#define AARCH64_CPU_FLAG_ERRATA_TC_TR		(1UL << 34)

// System-independent flags from sys/syspage.h. The CPU-specific ones must
// not overlap with these.
//#define CPU_FLAG_MMU						0x40000000UL
//#define CPU_FLAG_FPU						0x80000000UL

/*
 * A cpu number indexed array of a value needed to send an IPI to that CPU.
 * It can be simply the CPU number according to the GIC (which can be
 * different from the CPU number according to procnto), or even a full
 * affinity value identifying the CPU, as needed by the GICv3 system
 * register interface.
 */
struct aarch64_gic_map_entry {
	_Uint64t	gic_cpu[1];			/* variable sized array */
};

/*
 * A cpu number indexed array of the index into the redistributor array
 * for the same CPU.  This is needed for the GICv3 PPI callouts as well
 * as for qvm to look at the right redistributor regardless of what
 * procnto think the order of the CPUs is.
 * The top 16-bits indicate the redistributor range (if there are
 * several discontiguous), and the bottom 16 bits are the index into
 * that range.
 */
struct aarch64_gicr_map_entry {
	_Uint32t	gicr_idx[1];			/* variable sized array */
};

/*
  * The AArch64 ID register space goes from S3_0_C0_C1_0
  * through S3_0_C0_C7_7.  While it's not impossible they might
  * expand this one day, they still have plenty of unattributed
  * space to work with, per ARMv8.7.
  */
 #define AARCH64_IDDUMP_ENTRIES  (7*8)
 struct aarch64_idreg_dump_entry {
         _Uint64t        idreg[1];       /* variable sized array, 56 entries per CPU */
};

struct aarch64_syspage_entry {
	_Uint64t			L0_vaddr;
	syspage_entry_info	gic_map;
	syspage_entry_info	gicr_map;
	syspage_entry_info	idreg_dump;
	_Uint64t			rsvd[6];
};

struct aarch64_cpupage_entry {
	_Uint64t	gic_cpu;
};

#define HYPINFO_VIRT_ARM    0UL

#endif /* __AARCH64_SYSPAGE_H_INCLUDED */
