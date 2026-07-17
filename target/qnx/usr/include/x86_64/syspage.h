/*
 * Copyright (c) 2007, 2022 BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */



/*
 *  x86_64/syspage.h
 *

 */

#ifndef __X86_64_SYSPAGE_H_INCLUDED
#define __X86_64_SYSPAGE_H_INCLUDED

#ifndef __SYSPAGE_H_INCLUDED
#error x86_64/syspage.h should not be included directly.
#endif

/*
 *    CPU capability/state flags
 */
#define X86_64_CPU_FLAG(x) ((_Uint64t)1 << (unsigned)(x))
#define X86_64_CPU_CPUID        X86_64_CPU_FLAG(0)    /* CPU supports cpuid instruction */
#define X86_64_CPU_RDTSC        X86_64_CPU_FLAG(1)    /* CPU supports rdtsc instruction */
#define X86_64_CPU_INVLPG       X86_64_CPU_FLAG(2)  /* CPU has INVLPG instruction */
#define X86_64_CPU_WP           X86_64_CPU_FLAG(3)  /* CPU has WP bit in CR0 */
#define X86_64_CPU_BSWAP        X86_64_CPU_FLAG(4)  /* CPU has BSWAP instruction */
#define X86_64_CPU_MMX          X86_64_CPU_FLAG(5)  /* CPU has MMX instructions */
#define X86_64_CPU_CMOV         X86_64_CPU_FLAG(6)  /* CPU has CMOVxx instructions */
#define X86_64_CPU_PSE          X86_64_CPU_FLAG(7)  /* CPU has page size extensions */
#define X86_64_CPU_PGE          X86_64_CPU_FLAG(8)  /* CPU has TLB global mappings */
#define X86_64_CPU_MTRR         X86_64_CPU_FLAG(9)  /* CPU has MTRR registers */
#define X86_64_CPU_SEP          X86_64_CPU_FLAG(10)  /* CPU supports SYSENTER  */
#define X86_64_CPU_SIMD         X86_64_CPU_FLAG(11)  /* CPU supports SIMD (SSE1)  */
#define X86_64_CPU_FXSR         X86_64_CPU_FLAG(12)  /* CPU supports FXSAVE/FXRSTOR  */
#define X86_64_CPU_PAE          X86_64_CPU_FLAG(13)  /* CPU has phys addr extension  */
#define X86_64_CPU_NX           X86_64_CPU_FLAG(14)  /* CPU supports NX PTE bit */
#define X86_64_CPU_SSE2         X86_64_CPU_FLAG(15)  /* CPU supports SSE2 */
#define X86_64_CPU_AVX          X86_64_CPU_FLAG(16)  /* CPU supports AVX */
#define X86_64_CPU_XSAVE        X86_64_CPU_FLAG(17)  /* CPU supports XSAVE/XRSTOR */
#define X86_64_CPU_PAT          X86_64_CPU_FLAG(18)  /* CPU supports Page Attribute Tables */
#define X86_64_CPU_PTESPLIT_TLBFLUSH X86_64_CPU_FLAG(19)  /* Needs TLB flush when splitting a large page */
#define X86_64_CPU_PCID         X86_64_CPU_FLAG(20)  /* CPU supports PCID's */
#define X86_64_CPU_INVARIANT_TSC  X86_64_CPU_FLAG(21)  /* CPU supports invariant(constant) TSC */
#define X86_64_CPU_RDRAND       X86_64_CPU_FLAG(22)   /* CPU supports rdrand */
#define X86_64_CPU_RDSEED       X86_64_CPU_FLAG(23)  /* CPU supports rdseed */
#define X86_64_CPU_FSGSBASE     X86_64_CPU_FLAG(24)  /* CPU supports readfs,gs */
#define X86_64_CPU_TSC_DEADLINE X86_64_CPU_FLAG(25)  /* CPU supports TSC DEADLINE */

// System-independent flags from sys/syspage.h. The CPU-specific ones must
// not overlap with these.
//#define CPU_FLAG_FPU          X86_64_CPU_FLAG(30)
//#define CPU_FLAG_MMU          X86_64_CPU_FLAG(31)

struct x86_64_syspage_entry {
    _Uint64t    spare[4];
};

#define HYPINFO_VIRT_VMX    0UL
#define HYPINFO_VIRT_SVM    1UL

#endif
