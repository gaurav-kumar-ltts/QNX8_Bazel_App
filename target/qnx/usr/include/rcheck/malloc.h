/*
 * Copyright (c) 2007-2008, 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef __RCHECK_MALLOC_H_INCLUDED
#define __RCHECK_MALLOC_H_INCLUDED


/*
 * (c) Copyright 1990, 1991 Conor P. Cahill (uunet!virtech!cpcahil).
 * You may copy, distribute, and use this software as long as this
 * copyright statement is not removed.
 */

#define M_HANDLE_IGNORE     0
#define M_HANDLE_ABORT      1
#define M_HANDLE_EXIT       2
#define M_HANDLE_CORE       3
#define M_HANDLE_STOP       4
#define M_HANDLE_TRACEBACK  0x40
#define M_HANDLE_DUMP       0x80

#define MALLOC_VERBOSE          107
#define MALLOC_TRUNCATE         118
#define MALLOC_HANDLE_SIGNALS   117
#define MALLOC_EVENTBTDEPTH     116
#define MALLOC_TRACEBTDEPTH     115
#define MALLOC_EVENTFILE        108
#define MALLOC_TRACEFILE        110
#define MALLOC_TRACING          119
#define MALLOC_TRACEMIN         111
#define MALLOC_TRACEMAX         112
#define MALLOC_WARN             100
#define MALLOC_FATAL            101
#define MALLOC_DUMP_LEAKS       120
#define MALLOC_DUMP_STATS       121
#define MALLOC_CKALLOC          114
#define MALLOC_CKACCESS         106
#define MALLOC_CTRL_CMD         123
#define MALLOC_CTRL_CMD_FILE    124


#endif /* __RCHECK_MALLOC_H_INCLUDED */
