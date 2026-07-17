/*
 * $QNXLicenseC:
 * Copyright 2007-2021, QNX Software Systems. All Rights Reserved.
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
 *  sys/pathmsg.h
 *

 */
#ifndef __PATHMSG_H_INCLUDED
#define __PATHMSG_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __SYSMSG_H_INCLUDED
#include _NTO_HDR_(sys/sysmsg.h)
#endif

#ifndef __IOMSG_H_INCLUDED
#include _NTO_HDR_(sys/iomsg.h)
#endif

#include <devctl.h>
#include <sys/dcmd_proc.h>

#define PATHMGR_PID				SYSMGR_PID
#define PATHMGR_CHID			SYSMGR_CHID
#define PATHMGR_COID			SYSMGR_COID
#define PATHMGR_HANDLE			SYSMGR_HANDLE

enum {
	_PATH_RESOLVE = _PATHMGR_BASE,
	_PATH_CHDIR,
	_PATH_CHROOT,
	_PATH_TRUST,
    _PATH_OPENDIR
};


enum {
	_TRUST_QUERY,
};

/*
 * Message of _PATH_TRUST
 */
struct _pathmgr_trust {
	_Uint16t	type;
	_Uint16t	subtype;
	int			fd;
	_Uint32t	st_mode;
	_Uint32t	operation;
};

typedef union {
	struct _pathmgr_trust			i;
} pathmgr_trust_t;


/*
 * Message for devctl PATHMGR_CHECK_OPEN
 */
typedef struct {
	pid_t		pid;
	uint32_t	reserved;
	size_t		path_len;
	char		path[];
} pathmgr_check_open_t;

#define PATHMGR_CHECK_OPEN __DIOT(_DCMD_PROC, __PROC_SUBCMD_PATHMGR + 0, pathmgr_check_open_t)


#endif
