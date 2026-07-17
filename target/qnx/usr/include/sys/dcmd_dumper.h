/*
 * $QNXLicenseC:
 * Copyright 2007, 2021 QNX Software Systems. All Rights Reserved.
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





#ifndef __SYS_DCMD_DUMPER_H_INCLUDED
#define __SYS_DCMD_DUMPER_H_INCLUDED

#include <limits.h>
#include <sys/types.h>

enum message_type {
	DUMPER_NOTIFYEVENT=1,     /* add or update a notify event            */
	DUMPER_REMOVEEVENT,       /* remove a notify event                   */
	DUMPER_REMOVEALL,         /* deprecated */
	DUMPER_GETPATH            /*request dump pathname using pid*/
};

typedef union {
	struct {
		pid_t pid;
	} i;
	struct {
		char dump_pathname[PATH_MAX];
	} o;
}dump_info_t;

#define DCMD_DUMPER_NOTIFYEVENT   __DIOT(_DCMD_MISC, DUMPER_NOTIFYEVENT, struct sigevent)
#define DCMD_DUMPER_REMOVEEVENT   __DIOT(_DCMD_MISC, DUMPER_REMOVEEVENT, 0)
#define DCMD_DUMPER_REMOVEALL     __DIOT(_DCMD_MISC, DUMPER_REMOVEALL, 0)
#define DCMD_DUMPER_GETPATH       __DIOTF(_DCMD_MISC, DUMPER_GETPATH, dump_info_t)


#endif
