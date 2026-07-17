/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef __STORAGE_H_INCLUDED
#define __STORAGE_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#include _NTO_HDR_(_pack64.h)

#if defined(__SA_ACTION_FUNC_T)
__SA_ACTION_FUNC_T
#undef __SA_ACTION_FUNC_T
#endif

#ifndef __SIGINFO_H_INCLUDED
#include <sys/siginfo.h>
#endif

__BEGIN_DECLS

/*
 * Routine to return pointer to thread local storage structure.
 */
extern struct _thread_local_storage  *__tls(void) __attribute__((__const__));


typedef void *__getgot_func_t(void *__pltaddr);
typedef void __threadwatch_func_t(int __tid);


/*
 * Thread local storage. This data is at the top of each threads stack.
 */

struct _thread_local_storage {
    _Sizet              __stacksize;
    void               *__arg;
    int                *__errptr;
    int                 __errval; /* Not used for main() thread. */
    unsigned            __flags;
    int                 __pid;
    int                 __tid;
    unsigned            __owner;
    void               *__stackaddr;
    unsigned            __guardsize;
    unsigned            __numkeys;
    void              **__keydata; /* Indexed by pthread_key_t */
    void               *__cleanup;
    void               *__pt_tsd;
    void               *__ldd_data; /* Used by the ldd. */
    __sa_action_func_t *__sigaction;
    /** The channel ID that a procnto message handling thread is assigned to. */
    int                 __proc_thread_chid;
    int                 __reserved;
    void               *__cxa_atexit_data;
};

/*
 * Process local storage.
 */
struct _process_local_storage {
    __getgot_func_t      *_getgot;
    void                 *__spare;
    void                 *__dll_list;
    __entryfunc_t        *__entryfunc;
    _Sizet                __def_thr_stacksize;
    void                 *__reserved[4];
    __threadwatch_func_t *__threadwatch;
};

__END_DECLS

#include _NTO_HDR_(_packpop.h)

#endif
