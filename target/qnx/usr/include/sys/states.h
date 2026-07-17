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
 *  sys/states.h
 *

 */
#ifndef __STATES_H_INCLUDED
#define __STATES_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

/*
 * Define the states of a thread
 * THREAD.state
 */
#define STATE_DEAD            0u
#define STATE_RUNNING         1u
#define STATE_READY           2u
#define STATE_STOPPED         3u

#define STATE_SEND            4u
#define STATE_RECEIVE         5u
#define STATE_REPLY           6u

#define STATE_MQ_SEND         7u
#define STATE_MQ_RECEIVE      8u
#define STATE_WAITPAGE        9u

#define STATE_SIGSUSPEND      10u
#define STATE_SIGWAITINFO     11u
#define STATE_NANOSLEEP       12u
#define STATE_MUTEX           13u
#define STATE_CONDVAR         14u
#define STATE_JOIN            15u
#define STATE_INTR            16u
#define STATE_SEM             17u
#define STATE_WAITCTX         18u

#define STATE_RWLOCK_READ     19u
#define STATE_RWLOCK_WRITE    20u

#define STATE_BARRIER         21u

#define STATE_PIPE            22u

#define STATE_TIMEOUT_MAX     24u   /* TimerTimeout() only provides 24 bits to encode the state as
                                     1 << STATE_*, so timeout states must be less than 24. */

/* Not real states; these are used by kernel tracing. */
#define STATE_CREATE          24u
#define STATE_DESTROY         25u

#define STATE_MUON_MUTEX      26u
#define STATE_TRACEBUFFER     27u
#define STATE_INTR_ATTACH_EV  28u
#define STATE_TIMER_DELEGATE  29u
#define STATE_SEND_NOTIFY     30u

#define STATE_MAX             63u


__END_DECLS

#endif
