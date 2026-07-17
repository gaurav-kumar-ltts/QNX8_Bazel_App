/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems. All Rights Reserved.
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
 *  aarch64/inline.h
 *

 */

#ifndef _AARCH64_INLINE_H_INCLUDED
#define _AARCH64_INLINE_H_INCLUDED

/*
 *  some handy pragma's for low-level work:
 */

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _AARCH64_INOUT_INCLUDED
#include <aarch64/inout.h>
#endif

__BEGIN_DECLS

static __inline__ void __attribute__((__unused__))
isb(void)
{
	__asm__ __volatile__("isb" : : : "memory");
}

static __inline__ void __attribute__((__unused__))
dmb(void)
{
	__asm__ __volatile__("dmb	ish" : : : "memory");
}

static __inline__ void __attribute__((__unused__))
dmb_ishst(void)
{
	__asm__ __volatile__("dmb	ishst" : : : "memory");
}


static __inline__ void
csdb(void)
{
	__asm__ __volatile__("csdb" : : : "memory");
}

static __inline__ void
pssbb(void)
{
	__asm__ __volatile__("pssbb" : : : "memory");
}

static __inline__ void
ssbb(void)
{
	__asm__ __volatile__("ssbb" : : : "memory");
}

static __inline__ void
esb(void)
{
	__asm__ __volatile__("esb" : : : "memory");
}

static __inline__ void
psb_csync(void)
{
	__asm__ __volatile__("psb csync" : : : "memory");
}

static __inline__ void
sb(void)
{
	__asm__ __volatile__("sb" : : : "memory");
}

static __inline__ void
tsb_csync(void)
{
	__asm__ __volatile__("tsb csync" : : : "memory");
}


#define __raw_aa64_sr_rd32(__reg)									\
		({															\
			uint32_t	__res;										\
			__asm__ __volatile__("mrs	%0," #__reg : "=r"(__res));	\
			__res;													\
		})

#define aa64_sr_rd32(__reg)		__raw_aa64_sr_rd32(__reg)


#define __raw_aa64_sr_rd64(__reg)									\
		({															\
			uint64_t	__res;										\
			__asm__ __volatile__("mrs	%0," #__reg : "=r"(__res));	\
			__res;													\
		 })

#define aa64_sr_rd64(__reg)		__raw_aa64_sr_rd64(__reg)


#define __raw_aa64_sr_wr32(__reg, __val) \
		__asm__ __volatile__("msr " #__reg ",%0" :: "r"((uint32_t)(__val)))

#define aa64_sr_wr32(__reg, __val)		__raw_aa64_sr_wr32(__reg, __val)


#define __raw_aa64_sr_wr64(__reg, __val) \
		__asm__ __volatile__("msr " #__reg ",%0" :: "r"((uint64_t)(__val)))

#define aa64_sr_wr64(__reg, __val)		__raw_aa64_sr_wr64(__reg, __val)


/* ldsp() - set the current stack pointer */
static __inline__ void ldsp(_Uintptrt __sp) {
	__asm__ __volatile__("mov	sp, %0" :: "r" (__sp));
}

/* rdsp() - obtain the current stack pointer */
static __inline__ _Uintptrt rdsp(void) {
	_Uintptrt sp;
	__asm__ ("mov	%0, sp" : "=r" (sp));
	return sp;
}


/*
 * Check ARMv8: The system instruction class encoding.
 */
#define SYSINST_OP0_SHIFT	19
#define SYSINST_OP0_MASK	0x3
#define SYSINST_OP1_SHIFT	16
#define SYSINST_OP1_MASK	0x7
#define SYSINST_CRN_SHIFT	12
#define SYSINST_CRN_MASK	0xf
#define SYSINST_CRM_SHIFT	8
#define SYSINST_CRM_MASK	0xf
#define SYSINST_OP2_SHIFT	5
#define SYSINST_OP2_MASK	0x7

#define sys_reg_encode(op0, op1, crn, crm, op2) \
	(((op0) << SYSINST_OP0_SHIFT) | ((op1) << SYSINST_OP1_SHIFT) | \
	((crn) << SYSINST_CRN_SHIFT) | ((crm) << SYSINST_CRM_SHIFT) | \
	((op2) << SYSINST_OP2_SHIFT))

__END_DECLS

#endif
