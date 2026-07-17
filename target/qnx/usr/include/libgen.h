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



/*
 *  libgen.h: General file functions
 *

 */
#ifndef _LIBGEN_H_INCLUDED
#define _LIBGEN_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

#if defined(__EXT_POSIX2)
extern char     *basename( char * __fname );
extern char     *dirname( char * __fname );
#endif

#if defined(__EXT_QNX)
#if defined(__SIZE_T)
typedef __SIZE_T	size_t;
#undef __SIZE_T
#endif
extern char *pathfind_r(__const char *__path, __const char *__name, __const char *__mode, char *__buff, size_t __buff_size);


/*
 * Waiting for paths
 *
 *
 * waitfor() & waitfor_attach():
 *
 *      waitfor() calls _waitfor() with a checkfunc() that always performs a stat on the path.
 *          Use it as the generic case or when waiting for a regular file.
 *          Example of when to use waitfor():
 *              waitfor( "/tmp/log.txt", pollms, delayms );
 *
 *      waitfor_attach() calls _waitfor_ext() with poll_ms = 0. Its checkfunc_ext() will check
 *          a hash returned from a resmgr_attach()ed path and only stat() if necessary.
 *          Useful when waiting for device or mount paths.
 *          Example of when to use waitfor_attach():
 *              waitfor_attach( "/dev/ram0", delayms );
 *          Calling waitfor_attach() on regular files will block until delay_ms expires,
 *          so don't do that.
 *
 *
 * _waitfor, _waitfor_ext, checkfunc, & checkfunc_ext
 *
 * Most usages will ignore _waitfor() & _waitfor_ext in favor of
 * waitfor() & waitfor_attach().
 *
 * _waitfor() & _waitfor_ext() call the passed in checkfunc / checkfunc_ext functions
 * whenever they need to check for the presence of path, so you can customize
 * path checking and unblocking behaviour. See prototypes.
 *
 * checkfunc & checkfunc_ext() require further explanation:
 *
 *  checkfunc():
 *      Inputs: const char *path        path passed to _waitfor
 *              void *handle            handle passed to _waitfor
 *      Output: int
 *                  WAITFOR_CHECK_CONTINUE: path not found, keep performing _waitfor
 *                  WAITFOR_CHECK_ABORT:    path found, abort _waitfor
 *                  Other values:           error, abort _waitfor
 * checkfunc_ext():
 *      Inputs: const char *path        path passed to _waitfor_ext
 *              unsigned attach_hash    Either:
 *                                      The nonzero hash of a path that was
 *                                          attached by a call to resmgr_attach().
 *                                          The hash format is described by
 *                                          documentation for procmgr_event_notify_add() -
 *                                          PROCMGR_EVENT_PATHSPACE
 *                                      CHECKFUNC_FORCE_STAT
 *                                          A hint to perform a stat() on path.
 *              void *handle            handle passed to _waitfor_ext()
 *      Output: int
 *                  WAITFOR_CHECK_CONTINUE: path not found, keep performing waitfor
 *                  WAITFOR_CHECK_ABORT:    path found, abort waitfor
 *                  Other values:           error, abort waitfor
 */

#define CHECKFUNC_FORCE_STAT     0
#define WAITFOR_CHECK_CONTINUE  -1
#define WAITFOR_CHECK_ABORT     -2
extern int waitfor( __const char *__path, int __delay_ms, int __poll_ms );
extern int waitfor_attach( __const char *__path, int __delay_ms );
extern int _waitfor( __const char *__path, __const int __delay_ms, __const int __poll_ms, int (*__checkfunc)(__const char *, void *), void *__handle );
extern int _waitfor_ext( __const char *__path, __const int __delay_ms, __const int __poll_ms, int (*checkfunc_ext)(__const char *, unsigned, void *), void *__handle );
#endif

#if defined(__EXT_UNIX_MISC)
extern char *pathfind(__const char *__path, __const char *__name, __const char *__mode);
#endif

__END_DECLS

#if __NTO_FORTIFY_LEVEL > 0
#include <libgen_chk.h>
#endif

#endif
