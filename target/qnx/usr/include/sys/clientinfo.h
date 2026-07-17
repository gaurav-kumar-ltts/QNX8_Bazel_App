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

#ifndef CLIENTINFO_H_
#define CLIENTINFO_H_

#include <stddef.h>
#include <sys/neutrino.h>
#include <alloca.h>

/**
 * Determine the size of a _cred_info structure for the given the number of
 * groups.
 * While the structure's group list is defined to hold __NGROUPS_MAX elements,
 * the structure's real size can be smaller or larger, depending on the number
 * of groups.
 * @param   num_groups  The number of groups in the structure's grouplist array
 * @return  The total size of the structure, in bytes
 */
static inline size_t
nto_cred_info_size(
    unsigned const num_groups
)
{
    size_t cis = 0;

    cis += offsetof(struct _cred_info, grouplist);
    cis += (size_t)num_groups * sizeof(gid_t);

    return cis;
}

/*
 * _CRED_INFO_SIZE(ngroups) and _CLIENT_INFO_SIZE(ngroups) macros
 *
 * Calculate the size of a _cred_info or _client_info structure based on
 * the number of groups.
 *
 * New code should use nto_cred_info_size().
 */

#define _CRED_INFO_SIZE(_groupcount) nto_cred_info_size(_groupcount)


#define _CLIENT_INFO_SIZE(_groupcount) (offsetof(struct _client_info, cred.grouplist) + ((_groupcount)*sizeof(gid_t)))


/* _DECL_CLIENT_INFO(name, ngroups)
 *
 * Locals or statics can be declared of sufficient size for a
 * particular number of groups using the _DECL_*_INFO macros.
 * These macros take a name and ngroups as parameters, declare a
 * buffer pointer of the appropriate type and alloca a buffer for it
 * of _CLIENT_INFO_SIZE(ngroups) bytes.
 *
 * For example:
 *    _DECL_CLIENT_INFO(full_info_p, ngroups);
 *    _DECL_CLIENT_INFO(perms_only_p, 0);
 *
 *    memcpy(perms_only_p, full_info_p, _CLIENT_INFO_SIZE(0));
 */
#define _DECL_CLIENT_INFO(_name,_groupcount) 		\
	struct _client_info *_name = alloca(_CLIENT_INFO_SIZE(_groupcount))


#define _NTO_CLIENTINFO_EXTRA (~0U ^ (~0U >> 1))


#endif /* CLIENTINFO_H_ */
