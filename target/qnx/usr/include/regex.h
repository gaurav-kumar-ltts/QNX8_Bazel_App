/*
 * $QNXLicenseC:
 * Copyright 2020, QNX Software Systems. All Rights Reserved.
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

#ifndef __REGEX_H_INCLUDED
#define __REGEX_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if defined(__SIZE_T)
typedef __SIZE_T    size_t;
#undef __SIZE_T
#endif

#if defined(__SSIZE_T)
typedef __SSIZE_T      ssize_t;
#undef __SSIZE_T
#endif

/*
 * POSIX cflags for regcomp()
 */
#define REG_EXTENDED    0x01
#define REG_ICASE       0x02
#define REG_NOSUB       0x04
#define REG_NEWLINE     0x08

/*
 * Extended cflags for regcomp()
 */
#if defined(__EXT_QNX)
#define REG_BASIC       0x00
#define REG_NOSPEC      0x10
#define REG_PEND        0x20
#define REG_DUMP        0x80
#endif

/*
 * POSIX eflags for regexec()
 */
#define REG_NOTBOL      0x01
#define REG_NOTEOL      0x02

/*
 * Extended eflags for regexec()
 */
#if defined(__EXT_QNX)
#define REG_STARTEND    0x004
#define REG_TRACE       0x100
#define REG_LARGE       0x200
#define REG_BACKR       0x400
#endif

/*
 * POSIX error return values
 */
#define REG_NOMATCH     1
#define REG_BADPAT      2
#define REG_ECOLLATE    3
#define REG_ECTYPE      4
#define REG_EESCAPE     5
#define REG_ESUBREG     6
#define REG_EBRACK      7
#define REG_EPAREN      8
#define REG_EBRACE      9
#define REG_BADBR       10
#define REG_ERANGE      11
#define REG_ESPACE      12
#define REG_BADRPT      13

#if defined(__EXT_XOPEN_EX)
#define REG_ENOSYS  17
#endif

/*
 * Extended error return values
 */
#if defined(__EXT_QNX)
#define REG_OK      0
#define REG_EMPTY   14
#define REG_ASSERT  15
#define REG_INVARG  16
#define REG_ATOI    255
#define REG_ITOA    256
#endif

#include <_pack64.h>

typedef ssize_t regoff_t;

typedef struct {
    int re_magic;
    size_t re_nsub;
    const char *re_endp;
    void *re_g;
} regex_t;

typedef struct {
    regoff_t rm_so;
    regoff_t rm_eo;
} regmatch_t;

#include <_packpop.h>


#ifdef __cplusplus
extern "C" {
#endif

extern int
regcomp(
    regex_t *__preg,
    const char *__pattern,
    int __cflags);

extern int
regexec(
    const regex_t *__preg,
    const char *__str,
    size_t __nmatch,
    regmatch_t *__pmatch,
    int __eflags);

extern size_t
regerror(
    int __errcode,
    const regex_t *__preg,
    char *__errbuf,
    size_t __errbuf_size);

extern void
regfree(
    regex_t *__preg);

#ifdef __cplusplus
}
#endif

#endif // __REGEX_H_INCLUDED
