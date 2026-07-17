/*
 * Copyright (c) 2025, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __NEUTRINO_H_INCLUDED
#include _NTO_HDR_(sys/neutrino.h)
#endif

#ifndef PARAM_H_INCLUDED
#include <sys/param.h>
#endif

#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

#define CONTAINER_GLOBAL 0U              /** Global Container's Identifier */
#define CONTAINER_MAX_ID 4095U           /** Maximum Container Identifier */
#define CONTAINER_INVALID (~(cid_t)0U)   /** Invalid Identifier */

/**
 * @brief The container's configuration.
 *
 * Used for creating the container with container_create().
 */
typedef struct container_config {
    cid_t lower;              /** The lower boundary for the container's identifier. */
    cid_t upper;              /** The upper boundary for the container's identifier. */
    size_t name_len;          /** The length of the container's name. */
    size_t chroot_path_len;   /** The length of the containers root directory path. */
    char const * name;        /** The container's name. */
    char const * chroot_path; /** The container's root directory path*/
    uint32_t flags;           /** Configuration flags. Must currently be zero. */
    uint32_t reserved[5];     /** Reserved for future use. */
} container_config_t;

/**
* @brief A filter that is passed to container_get_cid_list().
*
* Allows filtering between a lower and upper search boundary.
* Allows filtering for container names that match a prefix.
*/
typedef struct cid_list_filter {
    cid_t lower;              /** The lower search boundary. */
    cid_t upper;              /** The upper search boundary. */
    size_t prefix_len;        /** The length of the prefix.*/
    char const * prefix;      /** The prefix to match against the container's names. */
    uint32_t flags;           /** Filter flags. Must currently be zero. */
    uint32_t reserved[9];     /** Reserved for future use. */
} cid_list_filter_t;

/**
 * @brief Struct containing information about a container.
 *
 * Used by container_get_info().
 */
typedef struct container_info {
    pid64_t creator_pid;           /** The identifier of the container's creator. */
    uint32_t prc_count;            /** The number of processes in the container. */
    uint32_t reserved[5];          /** Reserved for future use. */
    char name[MAXHOSTNAMELEN + 1]; /** The container's name. */
    char chroot_path[PATH_MAX];    /** The container's root directory path. */
} container_info_t;

__BEGIN_DECLS

extern cid_t container_create(container_config_t const * cfg);
extern int32_t container_destroy(cid_t cid, uint32_t flags);
extern int32_t container_signal(cid_t cid, int32_t signo);
extern cid_t container_get_cid(pid_t pid);
extern int32_t container_get_cid_list(cid_list_filter_t const * filter,
                                      cid_t * buffer, size_t buffer_size);
extern int32_t container_get_info(cid_t cid, uint32_t flags,
                                  container_info_t * info);

__END_DECLS

#endif
