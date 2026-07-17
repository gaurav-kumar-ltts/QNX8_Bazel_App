/*
 * Copyright (c) 2022, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef QNX_LOGIN_DEFS_H_INCLUDED
#define QNX_LOGIN_DEFS_H_INCLUDED

/* read only for all but super user */
#define PASSWD_UMASK	022
/* read/write for super user, non-accessable for others... */
#define SHADOW_UMASK	077

/* Return codes from check_files */
#define	NO_PASSWORD		001
#define	NO_SHADOW		002
#define	DIFFERENT_DEVS	004
#define	ON_RAMDISK		010
#define	NO_DRIVE		020

#define MAX_PWLEN       512
#define MIN_PWLEN       6
#define TOO_SIMPLE      2

#ifndef LOGINDIR
#define LOGINDIR     "/etc/"
#endif

#define	PW_LOCK      LOGINDIR ".pwlock"
#define	LOCK_TIMEOUT 60

#define LOGIN_STR	"login: "

#define MAX_SALT	256
#define DEFAULT_SALT_WIDTH      16

#define CRYPTTYPE_SHA256	's'
#define CRYPTTYPE_SHA512	'S'

#endif
