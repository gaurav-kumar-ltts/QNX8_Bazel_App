/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)select.h	8.2 (Berkeley) 1/4/94
 */

#ifndef _SYS_SELINFO_H_
#define	_SYS_SELINFO_H_

#include <sys/event.h>		/* for struct klist */
#ifdef __QNXNTO__
#include <sys/iofunc.h>
#endif /* __QNXNTO__ */

struct selfd;
TAILQ_HEAD(selfdlist, selfd);

/*
 * Used to maintain information about processes that wish to be
 * notified when I/O becomes possible.
 */
struct selinfo {
#ifndef __QNXNTO__
	struct selfdlist	si_tdlist;	/* List of sleeping threads. */
	struct knlist		si_note;	/* kernel note list */
	struct mtx		*si_mtx;	/* Lock for tdlist. */
#else /* !__QNXNTO__ */
	struct knlist		si_note;	/* kernel note list */
	struct mtx		*si_mtx;	/* holder if mtxp passed as null */
	int			si_trig;
	iofunc_notify_t		*si_notify;
#endif /* __QNXNTO__ */
};

#ifndef __QNXNTO__
#define	SEL_WAITING(si)		(!TAILQ_EMPTY(&(si)->si_tdlist))
#else /* !__QNXNTO__ */
#define	SEL_WAITING(si)		((si)->si_notify != NULL && (si)->si_notify[(si)->si_trig].list != NULL)
#endif /* __QNXNTO__ */

#ifdef _KERNEL
void	seldrain(struct selinfo *sip);
#ifndef __QNXNTO__
void	selrecord(struct thread *selector, struct selinfo *sip);
#else /* !__QNXNTO__ */
int	selrecord(struct thread *selector, struct mtx **mtxpp,
    iofunc_notify_t *nop, int lim, unsigned trig_satisfied, unsigned trig_future,
    struct selinfo *sip);
void	selclone(struct selinfo *dst, struct selinfo *src, unsigned trig_future);
#endif /* __QNXNTO__ */
void	selwakeup(struct selinfo *sip);
void	selwakeuppri(struct selinfo *sip, int pri);
void	seltdfini(struct thread *td);
#endif

#endif /* !_SYS_SELINFO_H_ */
