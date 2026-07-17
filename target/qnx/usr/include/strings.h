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
 *  strings.h    String functions (porting assist)
 *

 */
#ifndef _STRINGS_H_INCLUDED
#define _STRINGS_H_INCLUDED

#ifndef _STRING_H_INCLUDED
#include <string.h>
#endif

__BEGIN_DECLS


extern int  ffs(int);
#ifdef __EXT_QNX
extern int  ffsl(long int);
extern int  ffsll(long long int);
extern int  fls(int);
extern int  flsl(long int);
extern int  flsll(long long int);
#endif
extern int  strcasecmp(const char *, const char *);
extern int  strncasecmp(const char *, const char *, size_t);

__END_DECLS

#endif
