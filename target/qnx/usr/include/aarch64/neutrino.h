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

#ifndef __AARCH64_NEUTRINO_H_INCLUDED
#define __AARCH64_NEUTRINO_H_INCLUDED

#ifndef __NEUTRINO_H_INCLUDED
#error aarch64/neutrino.h should not be included directly.
#endif

__BEGIN_DECLS

static __inline__ void __attribute__((__unused__))
(__inline_InterruptDisable)(void)
{
	__asm__ __volatile__("msr	daifset, #2": : : "memory");
}

static __inline__ void __attribute__((__unused__))
(__inline_InterruptEnable)(void)
{
	__asm__ __volatile__("msr	daifclr, #2": : : "memory");
}

static __inline__ unsigned
(__inline_InterruptStatus)(void)
{
	_Uint64t __val;
	__asm__ __volatile__( "mrs %[val], daif" : [val] "=&r" (__val));
	return ((unsigned)__val & 0x80u) ^ 0x80u;
}

static __inline__ void __attribute__((__unused__))
(__inline_DebugBreak)(void)
{
	/*
	 * WARNING: must match the breakpoint instruction used by gdb.
	 * FIXME_AARCH64: what immediate value to use?
	 */
	__asm__ __volatile__("brk #0");
}

static __inline__ void __attribute__((__unused__))
(__inline_DebugKDBreak)(void)
{
	__asm__ __volatile__("brk #0xfffe");
}

#define CLOCKCYCLES_INCR_BIT	0

static __inline__ _Uint64t __attribute__((__unused__))
ClockCycles(void)
{
	_Uint64t	cntv;

	/*
	 * We need an isb barrier to ensure our read occurs in program order
	 */
	__asm__ __volatile__(
		"isb	\n"
		"mrs	%[cntv], cntvct_el0"
		: [cntv] "=r"(cntv)
	);
	return cntv;
}

extern size_t __page_size;

__END_DECLS

#endif /* __AARCH64_NEUTRINO_H_INCLUDED */
