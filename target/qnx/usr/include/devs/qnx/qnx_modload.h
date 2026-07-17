/*
 * $QNXLicenseC:
 * Copyright 2016-2024, QNX Software Systems. All Rights Reserved.
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

#ifndef SYS_QNX_QNX_MODLOAD_H_
#define SYS_QNX_QNX_MODLOAD_H_

/*
 * API Verison-------------------------++
 * Minor Verison---------------------++||
 * Major Version-----------------++++||||
 *                               ||||||||
 */
#define IOSOCK_VERSION_UNKNOWN 0x00000000 /* Unset version   */
#define IOSOCK_VERSION_710_V1  0x00000001 /* Initial 710 version */
#define IOSOCK_VERSION_710_V2  0x00000002 /* GA'd 710 update 1 */
#define IOSOCK_VERSION_800_V1  0x00010000 /* Initial 800 version */
#define IOSOCK_VERSION_800_V2  0x00010001 /* GA'd 800 version */
#define IOSOCK_VERSION_800_V3  0x00010002 /* GA'd 801/802 version */
#define IOSOCK_VERSION_800_V4  0x00010003 /* GA'd 803/804 version */
#define IOSOCK_VERSION_800_V5  0x00010004 /* GA'd 805 version */
#if 0
#define IOSOCK_VERSION_710_V2  0x00000003 /* Future 710 version 3 */
#define IOSOCK_VERSION_720_V1  0x00000100 /* Future 720 version 1 */
#define IOSOCK_VERSION_810_V1  0x00010100 /* Future 810 version 1 */
#define IOSOCK_VERSION_900_V1  0x00020000 /* Future 900 version 1 */
#endif

enum _iosock_module_type {
	IOSOCK_TYPE_GENERIC, /* To handle different types (if required) */
#if 0
	IOSOCK_TYPE_NEW_WIDGET, /* Future */
#endif
};

#ifdef INVARIANTS
#define IOSOCK_FLAG_INVARIANTS          1
#else
#define IOSOCK_FLAG_INVARIANTS          0
#endif

#define IOSOCK_FLAG_BITS "\020\1INVARIANTS"

struct _iosock_module_version {
	uint32_t                        provides;
	uint32_t                        requires;
	enum _iosock_module_type        type;
	uint32_t                        flags;
};

/* Change this when you make an api change */
#define IOSOCK_VERSION_CUR IOSOCK_VERSION_800_V5

/* Also change this if the change is not backwards compatible */
#define IOSOCK_VERSION_MIN IOSOCK_VERSION_800_V5

/* Sanity check for requires > provides */
_Static_assert(IOSOCK_VERSION_MIN <= IOSOCK_VERSION_CUR, "Bad IOSOCK_VERSION_*");

/* Declare generic macros for the drivers and modules to use */
#define IOSOCK_MODULE_VER_SYM_NAME "iosock_module_version"
#define IOSOCK_MODULE_VER_SYM_INIT {IOSOCK_VERSION_CUR, IOSOCK_VERSION_MIN,\
    IOSOCK_TYPE_GENERIC, IOSOCK_FLAG_INVARIANTS}

#endif /* SYS_QNX_QNX_MODLOAD_H_ */
