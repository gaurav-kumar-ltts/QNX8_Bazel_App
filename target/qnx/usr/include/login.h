/*
 * Copyright (c) 2007, 2022, 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */


/*-


 login.h: library of routines for login family.
*/

#ifndef _LOGIN_H_INCLUDED
#define _LOGIN_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _PWD_H_INCLUDED
#include <pwd.h>
#endif

#ifndef _SHADOW_H_INCLUDED
#include <shadow.h>
#endif

#ifndef QNX_LOGIN_DEFS_H_INCLUDED
#include <login_defs.h>
#endif

#include <_pack64.h>

struct lastlog {
	time_t          ll_time;
	char            ll_line[8];
	char            ll_host[16];
};

enum pwdbstat_e {
	PdbOk,
	NoPasswd,
	NoShadow,
	NotSameDevice,
	PasswdBadType,
	ShadowBadType,
	InvalidOwner,
	BusyPasswd
};

enum retcodes {
	Success = 0,
	PermissionDenied,
	SyntaxError,
	BadArg,
	UidBusy,
	DBcorrupt,
	Failed,
	NoPasswdFile,
	PasswdBusy,
	NoSuchUser
};

#include <_packpop.h>

__BEGIN_DECLS

extern char    *chkfiles(void);
extern char    *crypt(const char *__key, const char *__salt);
extern char    *getpass(const char *__prompt);
extern const char  *pwdb_errstr(enum pwdbstat_e);
extern int      addpwent(struct passwd * __pw);
extern int      addshent(struct spwd * __sp);
extern enum pwdbstat_e auth_pwdb(void);
extern int      base_64(short __x);
extern int      build_env(char *__fname, int __preserve);
extern int      catfile(char *__fname);
extern int      check_files(void);
extern int      chgpw_name(char *__name, struct passwd * __pw);
extern int      chgsh_name(char *__name, struct spwd * __sp);
extern int      delpw_name(char *__name);
extern int      delsh_name(char *__name);
extern char*	gensalt(char *salt, int width);
extern int      get_defaults(char *__fname);
extern pid_t    getspid(int __sid);
extern int      getty(char *__ttyname);
extern int      lock_passwd(void);
extern int      new_passwd(struct passwd * __pw, char *__npassword);
extern int      new_salt(char *__salt);
extern int      password(char *__prompt, struct passwd * __pw);
extern int      pseteuid(pid_t __pid, uid_t __euid);
extern int      psetgid(pid_t __pid, gid_t __gid);
extern int      psetuid(pid_t __pid, uid_t __uid);
extern int      read_noecho(int __fd, void *__bufp, int __buflen);
extern int      run_shell(struct passwd * __pw);
extern void     setkey(const char *__key);
extern int      sid_name(int __sid, char *__name);
extern int      unlock_passwd(void);

__END_DECLS
#endif
