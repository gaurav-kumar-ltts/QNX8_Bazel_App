/*
 * Copyright (c) 2025, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */
#ifndef __CONTAINERMSG_H_INCLUDED
#define __CONTAINERMSG_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __SYSMSG_H_INCLUDED
#include _NTO_HDR_(sys/sysmsg.h)
#endif

#define CONTAINERMGR_COID SYSMGR_COID

/**
 * @brief The container manager's message types.
 */
enum {
    CONTAINER_CREATE = _CONTAINER_BASE,
    CONTAINER_DESTROY,
    CONTAINER_SIGNAL,
    CONTAINER_GET_CID,
    CONTAINER_GET_CID_LIST,
    CONTAINER_GET_INFO,
};

/**
 * @brief Message header.
 *
 * Needs to be included on all messages sent to the container manager.
 */
typedef struct container_msg_header {
    _Uint16t type;
    _Uint16t subtype;
} container_msg_header_t;

/**
 * @brief CONTAINER_CREATE request.
 */
struct _container_create {
    container_msg_header_t hdr;
    cid_t lower;            /** The lower boundary for the container's identifier.*/
    cid_t upper;            /** The upper boundary for the container's identifier.*/
    uint32_t flags;         /** Configuration flags. Must currently be zero. */
    size_t name_len;        /** The length of the container's name. */
    size_t chroot_path_len; /** The length of the container's root directory path. */
    uint32_t reserved[5];   /** Reserved for future use. */
};

/**
 * @brief CONTAINER_CREATE reply.
 */
struct _container_create_reply {
    cid_t cid;             /** The identifier of the created container. */
};

/**
 * @brief CONTAINER_CREATE message union.
 *
 * The sender's buffer must contain the container's name string followed
 * by the container's root directory path string after the
 * container_create_t message.
 */
typedef union {
    struct _container_create i;
    struct _container_create_reply o;
} container_create_t;

/**
 * @brief CONTAINER_DESTROY request.
 */
struct _container_destroy {
    container_msg_header_t hdr;
    cid_t cid;      /** The identifier of the container to destroy. */
    uint32_t flags; /** Must currently be zero. */
};

/**
 * @brief CONTAINER_DESTROY message union.
 */
typedef union {
    struct _container_destroy i;
} container_destroy_t;

/**
 * @brief CONTAINER_SIGNAL request.
 */
struct _container_signal {
    container_msg_header_t hdr;
    cid_t cid;     /** The identifier of the container to signal. */
    int32_t signo; /** The signal number. */
};

/**
 * @brief CONTAINER_SIGNAL message union.
 */
typedef union {
    struct _container_signal i;
} container_signal_t;

/**
 * @brief CONTAINER_GET_CID request.
 */
struct _container_get_cid {
    container_msg_header_t hdr;
    pid_t pid; /** The identifier of the target process. */
};

/**
 * @brief CONTAINER_GET_CID reply.
 */
struct _container_get_cid_reply {
    cid_t cid; /** The container that the target process is part of. */
};

/**
 * @brief CONTAINER_GET_CID message union.
 */
typedef union {
    struct _container_get_cid i;
    struct _container_get_cid_reply o;
} container_get_cid_t;

/**
 * @brief CONTAINER_GET_CID_LIST request.
 */
struct _container_get_cid_list {
    container_msg_header_t hdr;
    cid_t lower;          /** The lower search boundary. */
    cid_t upper;          /** The upper search boundary. */
    uint32_t flags;       /** Filter flags. Must currently be zero. */
    size_t prefix_len;    /** The length of the prefix. */
    uint32_t reserved[9]; /** Reserved for future use. */
};

/**
 * @brief CONTAINER_GET_CID_LIST message union.
 *
 * The sender's buffer must contain the filter's prefix string after
 * the container_get_cid_list_t message.
 */
typedef union {
    struct _container_get_cid_list i;
} container_get_cid_list_t;

/**
 * @brief CONTAINER_GET_INFO request.
 */
struct _container_get_info {
    container_msg_header_t hdr;
    cid_t cid;            /** The target container's identifier. */
    uint32_t flags;       /** Must currently be zero. */
    uint32_t reserved[5]; /** Reserved for future use. */
};

/**
 * @brief CONTAINER_GET_INFO message union.
 */
typedef union {
    struct _container_get_info i;
} container_get_info_t;

/**
 * @brief A union of all container manager messages.
 */
typedef union {
    container_msg_header_t hdr;
    container_create_t create;
    container_destroy_t destroy;
    container_signal_t signal;
    container_get_cid_t get_cid;
    container_get_cid_list_t get_cid_list;
    container_get_info_t get_info;
} container_msg_t;

#endif
