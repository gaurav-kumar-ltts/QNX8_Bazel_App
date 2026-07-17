/*
 * $QNXLicenseC:
 * Copyright 2020, QNX Software Systems. All Rights Reserved.
 *
 * This software is QNX Confidential Information subject to
 * confidentiality restrictions. DISCLOSURE OF THIS SOFTWARE IS
 * PROHIBITED UNLESS AUTHORIZED BY QNX SOFTWARE SYSTEMS IN WRITING.
 *
 * You must obtain a written license from and pay applicable license
 * fees to QNX Software Systems before you may reproduce, modify or
 * distribute this software, or any work that includes all or part
 * of this software. For more information visit
 * http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information. $
 */
#ifndef __FS_QUOTA_H_INCLUDED
#define __FS_QUOTA_H_INCLUDED

#include <inttypes.h>

#define IOMSG_FSYS_QUOTAS	'q'

#define QUOTA_FILENAME		".quotas"
#define QUOTA_MAGIC			0x41544F51
#define QUOTA_VERSION		1

#define QUOTA_NOID_LIMIT	0x0001

#define QUOTA_NFILES_UNLIMITED(_nf)	((_nf) == 0u)
#define QUOTA_NFILES_NONE(_nf)		((_nf) == ~0u)
#define QUOTA_FILESZ_UNLIMITED(_nb)	((_nb) == 0ull)
#define QUOTA_FILESZ_NONE(_nb)		((_nb) == ~0ull)


typedef struct quota_header {
	uint32_t		quota_magic;
	uint16_t		quota_version;
	uint16_t		quota_flags;
	uint64_t		fsys_usage;
	uint32_t		warning_filesz;
	uint32_t		warning_nfiles;
	uint32_t		num_uids;
	uint32_t		num_gids;
	uint32_t		_pad_[8];
} quota_header_t;

typedef struct quota_entry {
	int32_t			ug_id;
	uint32_t		warn_filesz;
	uint64_t		hard_filesz;
	uint64_t		soft_filesz;
	uint64_t		used_filesz;
	uint32_t		warn_nfiles;
	uint32_t		hard_nfiles;
	uint32_t		soft_nfiles;
	uint32_t		used_nfiles;
	uint32_t		_pad_[4];
} quota_entry_t;

#endif /* __FS_QUOTA_H_INCLUDED */
