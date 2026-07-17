/*
 * $QNXLicenseC:
 * Copyright 2021 QNX Software Systems. All Rights Reserved.
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

#ifndef __DUPFD_H_INCLUDED
#define __DUPFD_H_INCLUDED

#ifndef __NEUTRINO_H_INCLUDED
#include <sys/neutrino.h>
#endif

__BEGIN_DECLS

#define DUPFD_NO_DISCARD 0x1
extern int dupfd_register(pid64_t __dstpid, int __fd, unsigned __flags, dupfd_handle_t *__handlep);
extern int dupfd_unregister(dupfd_handle_t __handle);
extern int dupfd_getinfo(dupfd_handle_t __handle, pid64_t *__peerpidp, pid_t *__srvpidp, struct _msg_info_hdr *__infop);
extern int dupfd(dupfd_handle_t __handle, int __flags);

__END_DECLS

#endif
