/*
 * $QNXLicenseC:
 * Copyright 2017-2021, QNX Software Systems.  All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.  Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef QNX_QH_QH_H_INCLUDED
#define QNX_QH_QH_H_INCLUDED

/**
 * @file qh.h
 *
 * QNX helpers that set QH_FILENAME.
 *
 */

/* sorted headers from this project */

/* sorted library headers */
#if !defined(__QNXNTO__) && !defined(_LIB_COMPAT_H_INCLUDED)
#include <lib/compat.h>
#endif

/* sorted system headers */
#ifndef _ERRNO_H_INCLUDED
#include <errno.h>
#endif

#ifndef _STDIO_H_INCLUDED
#include <stdio.h>
#endif

#ifndef _STDLIB_H_INCLUDED
#include <stdlib.h>
#endif

#ifndef _STRING_H_INCLUDED
#include <string.h>
#endif

#ifndef __CDEFS_H_INCLUDED
#include <sys/cdefs.h>
#endif

#ifndef _UNISTD_H_INCLUDED
#include <unistd.h>
#endif

/** @cond */
__BEGIN_DECLS
/** @endcond */

#if defined(__GNUC__)
#define QH_FILENAME \
        (__builtin_strrchr(__FILE__, (int8_t)'/') != NULL) ? \
            (&__builtin_strrchr(__FILE__, (int8_t)'/')[1]) : \
                ((__builtin_strrchr(__FILE__, (int8_t)'\\') != NULL) ? \
                    (&__builtin_strrchr(__FILE__, (int8_t)'\\')[1]) : __FILE__)
#define QH_FILENAME_HAS_FULLPATH                                                               false
#define QH_SHORT_FILENAME_DEFINED
#else
/**
 * Specifies a QNX helpers filename. If you are using a GNU compiler, @c QH_FILENAME is
 * <tt>__FILE__</tt> with the path removed.
 */
#define QH_FILENAME __FILE__
/**
 * Specifies whether the filename that @c QH_FILENAME specifies contains the full path (contains
 * @c true) or just the name of the file (contains @c false). If it contains @c false, @c
 * QH_SHORT_FILENAME_DEFINED is defined.
 */
#define QH_FILENAME_HAS_FULLPATH                                                                true
#endif

/*
 * OS based support definitions
 */
#ifdef __QNXNTO__
#define QH_HAS_SUPPORT_SLOG
#define QH_HAS_SUPPORT_TIME_FUNC
#define QH_HAS_SUPPORT_STOPWATCH_FUNC
#endif

#if !defined(__MINGW32__) && !defined(__MINGW64__) && !defined(__DARWIN__)
#define QH_HAS_SUPPORT_QUICK_EXIT
#endif

/** @cond */
__END_DECLS
/** @endcond */

#endif /* QNX_QH_QH_H_INCLUDED */
