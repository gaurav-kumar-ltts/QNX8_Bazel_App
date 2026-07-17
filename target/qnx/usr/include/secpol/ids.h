/*
 * $QNXLicenseC:
 * Copyright 2018-2025, QNX Software Systems. All Rights Reserved.
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

/**
 * @file ids.h
 * @brief This file defines the ID parsing API
 */

#ifndef SECPOL_IDS_H_INCLUDED
#define SECPOL_IDS_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * @brief Change the caller's identifiers based on a given string
 *
 * @details The @c set_ids_from_arg() function sets the returned user ID, group ID,
 *          and supplementary group IDs.
 *
 *          This function doesn't support negative IDs.
 *
 *          The @p arg string format can take one of the following two forms:
 *          - @b UID
 *            @code uid:gid,sgid1,sgid2,sgid3,... @endcode
 *            All IDs must be numbers. The UID and GID are separated by
 *            a colon. The GID can be followed by a comma-separated list of supplementary
 *            group IDs. If the GID is not specified, the GID of the calling process is
 *            returned. The supplementary GIDs are also optional. *
 *          - @b Username
 *            @code username,sgid1,sgid2,sgid3,... @endcode
 *            The username must be a valid username defined in @c /etc/passwd; otherwise, the
 *            function errors out with EINVAL. The supplementary GIDs are optional and
 *            must be a comma-separated list of numbers. The GID is looked up in @c /etc/passwd.
 *            The supplementary GIDs returned are a union of the supplementary GIDs in @c
 *            /etc/group for the given username and the GIDs parsed from @p arg.
 *
 *          See also get_ids_from_arg().
 *
 * @param[in]  arg   The formatted string containing the ID information.
 *
 * @return @b EOK on success; on failure, -1 and @e errno is set to one of the following values:
 *         - @b EINVAL - The argument is in an invalid format or references a non-existent username.
 *         - @b ERANGE - An ID in the argument is larger than the @c uid_t or @c gid_t data
 *                       type supports.
 *         - @b E2BIG - The system can't support the number of supplementary GIDs specified in the
 *         argument.
 *         - @b EPERM - The calling process does not have the required permissions to set IDs.
 *
 */
int set_ids_from_arg(const char * arg__);


/**
 * @brief Get identifiers from an argument string, or the string and @c /etc/passwd and @c /etc/group
 *
 * @details The @c get_ids_from_arg() function parses a given formatted string and returns
 *          the corresponding user ID, group ID, and supplementary group IDs. If @p supp_gids and
 *          @p supp_count are not NULL, the supplementary GIDs found are written there, and
 *          @p supp_count is set to the number of supplementary GIDs written there. If there is not
 *          enough space in the provided array, E2BIG is returned.
 *
 *          QNX recommends that you allocate your supplementary GID array to the size
 *          returned by <tt>sysconf(_SC_NGROUPS_MAX)</tt> to ensure that you have enough space.
 *
 *          This function doesn't support negative IDs.
 *
 *          The @p arg string format can take one of the following two forms:
 *          - @b UID
 *            @code uid:gid,sgid1,sgid2,sgid3,... @endcode
 *            All IDs must be numbers. The UID and GID are separated by
 *            a colon. The GID can be followed by a comma-separated list of supplementary
 *            group IDs. If the GID is not specified, the GID of the calling process is
 *            returned. The supplementary GIDs are also optional.
 *          - @b Username
 *            @code username,sgid1,sgid2,sgid3,... @endcode
 *            The username must be a valid username defined in @c /etc/passwd; otherwise, the
 *            function errors out with EINVAL. The supplementary GIDs are optional and
 *            must be a comma-separated list of numbers. The GID is looked up in @c /etc/passwd.
 *            The supplementary GIDs returned are a union of the supplementary GIDs in @c
 *            /etc/group for the given username and the GIDs parsed from @p arg.
 *
 *          See also set_ids_from_arg().
 *
 * @param[in]      arg          The formatted string containing the ID information.
 * @param[out]     uid          The UID as read or inferred from the formatted string.
 * @param[out]     gid          The GID as read or inferred from the formatted string.
 * @param[out]     supp_gids    An allocated array to store the supplementary GIDs that are
 *                                read from the formatted string and @c /etc/group. If NULL,
 *                                the supplementary GIDs are not returned.
 * @param[in,out]  supp_count   As input, the size of the provided @p supp_gids array,
 *                                or NULL if the caller is not requesting the supplementary GIDs.
 *                                As ouput on success, this is set to the number of supplementary GIDs
 *                                written to the @p supp_gids array.
 *
 * @return @b EOK on success; on failure, one the following values:
 *         - @b EINVAL - The argument is in an invalid format or references a non-existant username.
 *         - @b ERANGE - An ID in the argument is larger than the @c uid_t or @c gid_t data
 *                       type supports.
 *         - @b E2BIG  - The array provided by the caller is not large enough to hold all of the IDs.
 *         - @b ENOMEM - Out of memory.
 *
 */
int get_ids_from_arg(const char * arg__,
                     uid_t * uid__,
                     gid_t * gid__,
                     gid_t * supp_gids__,
                     size_t * supp_count__);

/** @cond */
__END_DECLS
/** @endcond */

#endif /* _SECPOL_IDS_H_INCLUDED */
