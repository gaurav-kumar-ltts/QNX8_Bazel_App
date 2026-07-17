/*
 * Copyright (c) 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef _SYS_INOTIFY_EXT_H_
#define _SYS_INOTIFY_EXT_H_

#include <sys/cdefs.h>
#include <sys/types.h>
#include <stdint.h>

__BEGIN_DECLS

/**
 * @public
 * @defgroup fsnotify_qnx_ext_inotify The Fsnotify QNX Extended-Inotify API
 * @{
 */

/**
 * This ability is required for any client which wants to listen to
 * QNX extended events.  This is needed because some of the extended
 * events are mountpoint-wide, and may leak details about files which
 * the application should not be able to see.
 */
#define INOTIFY_ABILITY_QNX_EXT		"fsevmgr/qnxext"


/**
 * Enables the QNX extension to the inotify system.
 *
 * Indicates that the calling process understands the QNX extended events,
 * and wishes to receive events covering at least one extended condition.
 *
 * @param[in] inotify_fd The file descriptor returned from an earlier call to inotify_init()
 * @param[in] extensions A bitfield indicating which @ref qnx_inotify_ext should trigger notification
 *
 * @note Enabling QNX extended events will increase the maximum event size
 *       to @c sizeof(@ref inotify_event) + PATH_MAX
 *
 * @retval 0 on success
 * @retval -1 on error, and will set errno
 */
int inotify_qnx_ext(const int inotify_fd, const uint32_t extensions);


/**
 * @defgroup qnx_inotify_ext QNX Extended Inotify Conditions
 * @{
 * QNX extensions to the inotify interface.  These flags are passed to the
 * handle returned from inotify_init() to enable one or more QNX extensions.
*/

/** Notification when a new filesystem is mounted */
#define INOTIFY_QNX_EXT_MOUNT			0x00000001u

/** Notification when a filesystem is unmounted */
#define INOTIFY_QNX_EXT_UNMOUNT			0x00000002u

/** Get notified of important Security Events */
#define INOTIFY_QNX_EXT_SECURITY		0x00000004u

/** Set of extensions recognized by the implementation */
#define INOTIFY_QNX_EXT_MASK			0x00000007u

/** Watch is only for a directory, don't trigger events for children (not implemented yet) */
#define INOTIFY_QNX_EXT_WATCH_DIR_ONLY	0x10000000u

/**
 * @}
 */
/**
 * Header used for all QNX extensions to the inotify interface
*/
typedef struct _inotify_qnx_ext_hdr {
	uint32_t	type;			/**< One from the INOTIFY_QNX_EXT_xxx set */
	uint32_t	reserved;		/**< Reserved - Set to zero */
} inotify_qnx_ext_hdr;


/**
 * Event format for INOTIFY_QNX_EXT_MOUNT and INOTIFY_QNX_EXT_UNMOUNT
*/
typedef struct {
	inotify_qnx_ext_hdr		hdr;		/**< Header for the inotify QNX extensions */
	uint32_t				namelen;	/**< Length of the name */
	char					name[0];	/**< NUL terminated mount point */
} inotify_qnx_ext_mount;


/**
 * Known security event subtypes
 */
enum inotify_qnx_ext_security_e {
	INOTIFY_QNX_EXT_SECURITY_BLOCK_VALIDATION_FAILED,
	INOTIFY_QNX_EXT_SECURITY_NUM
};

/**
 * Format of the Block hash validation security subtype.
 */
struct blk_validation_failure {
	uint64_t blkno;				/**< physical block number */
	uint32_t hashblkno;			/**< block within hash tree */
	uint16_t hashlevel;			/**< level within hash tree */
	uint16_t hashblockoffset;	/**< Offset within hash block */
};

/**
 * Union of all payloads for all security subtypes.
 */
typedef union fsnotify_sec_payload_u {
	struct blk_validation_failure blk_hash; /**< QTD hash validation failure */
	uint8_t unused [32];				/**< Placeholder to set the minimum struct size */
} fsnotify_sec_payload_t;

/**
 * Event format for INOTIFY_QNX_EXT_SECURITY
*/
typedef struct inotify_qnx_ext_security_s {
	inotify_qnx_ext_hdr hdr;			/**< Header for the inotify QNX extensions */
	uint64_t inode;						/**< Inode number triggering the violation (0 if not relevant or cannot be determined) */
	uint16_t subtype;					/**< Event class subtype */
	uint16_t namelen;					/**< length in bytes (including NUL) of name field (could be zero as well) */
	uint32_t zero;						/**< Unused */
	fsnotify_sec_payload_t payload;		/**< Security event payload */
	char name[0];						/**< Associated mountpoint path */
} inotify_qnx_ext_security_t;

/**
 * @}
 */
__END_DECLS

#endif /* #ifndef _SYS_INOTIFY_EXT_H_ */
