/*
 * Copyright (c) 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */
#ifndef __FSNOTIFY_H
#define __FSNOTIFY_H


#include <sys/cdefs.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/inotify_ext.h>

__BEGIN_DECLS

/**
 * @file sys/fsnotify.h
 * @brief This is the public header file for use by all resmgr which want to generate
 * fsnotify events.
 *
 * @defgroup fsnotify_resmgr_api Filesystem Notifications API for Resmgrs
 * @copydoc fsnotify_resmgr_if
 * @{
 */

/**
 * Per mountpoint opaque context structure.
 *
 * Allocated by a call to fsnotify_add_mount().  A filesystem resmgr will need
 * to save this, as it is used in most of the fsnotify calls.  Files being
 * modified will be identified as an fsnotify_node_t that falls within a given
 * mount context.
 */
typedef struct fsnotify_mount fsnotify_mount_t;

/**
 * fsnotify abstract file/directory identification.
 *
 * The fsnotify system uses an abstract identifier for each file within a mount.
 * The filesystem will provide a value for each file/directory ("node" in the
 * documentation).  The fsnotify code will match up the node + mount to determine
 * if any watches have been triggered.
 */
typedef uint64_t fsnotify_node_t;

#define INVALID_NODE (fsnotify_node_t)(~0ul)	// should not conflict with any valid filehandle/node_t

static inline fsnotify_node_t make_filehandle(dev_t devno, ino_t ino, uint32_t gen)
{
	fsnotify_node_t handle = (uint64_t)devno << 48;
	handle |= (uint64_t)(uint16_t)(gen) << 32;
	handle |= (uint64_t)(uint32_t)ino;
	return handle;
}

bool fsnotify_is_enabled(void);

/**
 * Initialize the fsnotify library, and open a connection to the event manager.
 *
 * This function will allocate a notification context, open a connection to the
 * event manager, and initialize the fsnotify library for use by a resmgr to
 * accept watches and emit events.  There is no deinit function call, the
 * context shall remain allocated, and the connection to the event manager
 * shall remain open.
 *
 * @note This function only needs to be called once per resmgr process.  It is
 *       safe to call multiple times, and each subsequent call will return
 *       success.
 *
 *
 * @pre The event manager process must already be running
 *
 * @retval EOK on success
 * @retval errno on failure
 */
errno_t fsnotify_init(void);

/**
 * Inform the fsnotify system that a new mountpoint has been created
 *
 * Create an fsnotify mount context for a mountpoint/device.  This should be
 * called once per mountpoint/device that exists within the server process. The
 * function will allocate an fsnotify_mount_t structure, and return a pointer
 * to it in @p mntctx.  This mount context will be required for most future
 * fsnotify calls.
 *
 * @param[in] mntpath Pointer to a NUL-terminated buffer containing the
 *                    UTF-8 mountpoint
 * @param[in] devno   A dev_t unique to this mountpoint (obtained from rsrcdbmgr_devno_attach())
 * @param[out] mntctx Location to where the function can store the pointer to
 *                    the mount context
 *
 * @pre fsnotify_init() must have been called successfully
 * @post the fsnotify system will allocate and initialize a mount context
 *
 * @retval EOK on success
 * @retval errno value on failure
 */

errno_t fsnotify_add_mount(const char* mntpath, dev_t devno, unsigned flags, fsnotify_mount_t** mntctx);

/**
 * Inform the fsnotify system that the given mountpoint has been removed.
 *
 * @param[in] mntctx Pointer to a context previously allocated from fsnotify_add_mount()
 *
 * @post @p mntctx will be deallocated
 * @post Any active notifications on the mountpoint will be cleaned up.
 *
 * @retval EOK for success
 * @retval errno value on error
 */
errno_t fsnotify_remove_mount(fsnotify_mount_t* mntctx);

/**
 * Inform the fsnotify system that a file/dir has been opened.
 *
 * Called for any open of a file, even combine opens.  This function will allocate
 * and initialize tracking information inside the fsnotify system.
 *
 * @param[in] mntctx Context of the mountpoint containing the file that's being opened
 * @param[in] node Unique identifier of the file/dir within the mountpoint
 * @param[in] parent_node Unique identifier of the parent file/dir within the mountpoint
 * @param[in] name Path component name of file/dir being opened. Non-NUL-terminated
 * @param[in] namelen size in bytes of @p name.
 * @param[in] rw True if this is a read-write open.  false otherwise
 * @param[in] isdir True if @p node refers to a directory
 *
 * @post Some tracking information will be allocated in the fsnotify subsystem.
 *       This information is released by a call to fsnotify_close().
 *
 * @retval EOK for success
 * @retval errno value for failure
 */
errno_t fsnotify_open(fsnotify_mount_t* mntctx, fsnotify_node_t node,
		fsnotify_node_t parent_node, void *cookie, const char* name, size_t namelen,
		int ioflags, bool isdir);

errno_t fsnotify_create(fsnotify_mount_t *mntctx, fsnotify_node_t parent, const char *name, size_t namelen, bool isdir);

errno_t fsnotify_link(fsnotify_mount_t *mntctx, fsnotify_node_t node, fsnotify_node_t parent, const char *name, size_t namelen);

/**
 * Inform the fsnotify system a file/dir has been unlinked.
 *
 * Called every time an unlink() operation removes a name from a file/directory.
 *
 * @param[in] mntctx Mountpoint on which this file/directory exists
 * @param[in] node Unique identifier of this file/directory
 * @param[in] parent_node Unique identifier of this file/directory's parent
 * @param[in] name Non-NUL-terminated component pathname
 * @param[in] namelen size in bytes of @p name
 *
 * @retval EOK unlink notification was added to the fsnotify system
 * @retval errno Error occurred
 */
errno_t fsnotify_unlink(fsnotify_mount_t* mntctx, fsnotify_node_t node,
		fsnotify_node_t parent_node, const char* name, size_t namelen, unsigned linkcount, unsigned opencount, bool isdir);

/**
 * Inform the library that a rename operation just completed on a file
 *
 * Called when a rename within the same mountpoint has completed.  Renames
 * across mounts will be indicated as an unlink, and a later create.
 *
 * @param[in] mntctx Mount context for the mountpoint on which this file/dir resides.
 * @param[in] node Unique identifier of the file/directory being renamed.
 * @param[in] old_parent Unique identifier of the parent directory from before the rename
 * @param[in] new_parent Unique identifier of the new parent_directory
 * @param[in] oldname The old component name of the file/directory (not NUL-terminated)
 * @param[in] oldnamelen Length in bytes of @p oldname
 * @param[in] newname The new component name of the file/directory
 * @param[in] newnamelen Lengthin bytes of @p newname
 *
 * @retval EOK rename notification was added to the fsnotify system
 * @retval errno Error occurred
 */
errno_t fsnotify_rename(fsnotify_mount_t* mntctx, fsnotify_node_t node,
		fsnotify_node_t old_parent, fsnotify_node_t new_parent,
		const char* oldname, size_t oldnamelen,
		const char* newname, size_t newnamelen, bool isdir,
		fsnotify_node_t existing, unsigned linkcount, unsigned opencount);

/**
 * Inform the fsnotify system that a file/dir ownership has changed
 *
 * Call when a file/directory has had itss ownership (uid or gid) changed
 *
 * @param[in] mntctx Mountpoint to which this file/directory belongs
 * @param[in] node Unique identifier of file/node with modified attributes
 *
 * @retval EOK ownership change indicator was added to the fsnotify system
 * @retval errno Error occurred
 */
errno_t fsnotify_owner(fsnotify_mount_t * mntctx, fsnotify_node_t node, void *cookie, bool isdir);

/**
 * Inform the fsnotify system that a file/dir access permissions have changed
 *
 * Call when a file/directory has had its access permissions changed
 *
 * @param[in] mntctx Mountpoint to which this file/directory belongs
 * @param[in] node Unique identifier of file/node with modified attributes
 *
 * @retval EOK permission change indicator was added to the fsnotify system
 * @retval errno Error occurred
 */
errno_t fsnotify_perms(fsnotify_mount_t * mntctx, fsnotify_node_t node, void *cookie, bool isdir);

/* File ACL has changed; may also have changed the group mode bits (ie file perms). */
errno_t fsnotify_acl(fsnotify_mount_t * mntctx, fsnotify_node_t node, void *cookie, bool isdir);

/**
 * Indicate that the given node is completely gone.
 *
 * When a filesystem completely releases @p node, and it becomes open
 * for re-use, indicate this to the fsnotify system.
 *
 * @param[in] mntctx Mountpoint on which this node exists
 * @param[in] node   The node which is fully removed
 *
 * @retval EOK notification was added to the fsnotify system
 * @retval errno Error occurred.
 */
errno_t fsnotify_remove(fsnotify_mount_t* mntctx, fsnotify_node_t node);

/**
 * Inform the library that a read operation just completed on a file/dir
 *
 * Called when a read() or readdir() is successfully completed.
 *
 * @param[in] mntctx Mount context for the mountpoint on which this file/dir resides.
 * @param[in] node Unique identifier of the file/directory which was read
 *
 * @retval EOK read notification was added to the fsnotify system
 * @retval errno Error occurred
 */
errno_t fsnotify_read(fsnotify_mount_t* mntctx, fsnotify_node_t node, void *cookie, bool isdir);

/**
 * Inform the library that a write operation just completed on a file/dir
 *
 * Called when a write() is successfully completed.
 *
 * @param[in] mntctx Mount context for the mountpoint on which this file/dir resides.
 * @param[in] node Unique identifier of the file/directory which was written to
 *
 * @retval EOK write notification was added to the fsnotify system
 * @retval errno Error occurred
 */
errno_t fsnotify_write(fsnotify_mount_t* mntctx, fsnotify_node_t node, void *cookie);


/**
 * Inform the library that a space operation just completed on a file
 *
 * Called when an IO_SPACE is successfully completed.
 *
 * @param[in] mntctx Mount context for the mountpoint on which this file/dir resides.
 * @param[in] node Unique identifier of the file which was grown/truncated
  *
 * @retval EOK truncate notification was added to the fsnotify system
 * @retval errno Error occurred
 */
errno_t fsnotify_truncate(fsnotify_mount_t* mntctx, fsnotify_node_t node, void *cookie);

/**
 * Inform the library that a file/dir has been closed
 *
 * Called when the last dup of an fd is closed.
 *
 * @param[in] mntctx Mount context for the mountpoint on which this file/dir resides.
 * @param[in] node Unique identifier of the file which was closed
 * @param[in] isdir True if the close is for a directory
  *
 * @retval EOK truncate notification was added to the fsnotify system
 * @retval errno Error occurred
 */
errno_t fsnotify_close(fsnotify_mount_t* mntctx, fsnotify_node_t node, void *cookie, int ioflags, unsigned linkcount, unsigned opencount, bool isdir);

errno_t fsnotify_openfd(fsnotify_mount_t* mntctx, fsnotify_node_t node, void *cookie, void *newcookie, int ioflags, bool isdir);

errno_t fsnotify_mmap(fsnotify_mount_t* mntctx, fsnotify_node_t node, void *cookie, void *newcookie, int ioflags, bool isdir);

/* A file/directory has had its timestamps updated */
errno_t fsnotify_utime(fsnotify_mount_t *mntctx, fsnotify_node_t node, void *cookie, bool isdir);

errno_t fsnotify_combo(fsnotify_mount_t *mntctx, fsnotify_node_t node, fsnotify_node_t parent, size_t namelen, const char *name, void *cookie, bool setup);

/**
 * @}
 */

/**
 * Fill in an fsnotify security hash violation structure
 *
 * Allocate and populate an fsnotify hash mismatch security violation.
 *
 * @param[in] mntctx  Pointer to the context which identifies what mountpoint
 *                    the violation occurred on.
 * @param[in] node    Node ID of file on which the hash violation happened
 * @param[in] offset  Offset within @p inode where the violation happened
 * @param[in,out]     sec_event Pointer to where the function can store the
 *                          allocated security violation
 *
 * @post On successful return, @p sec_event points at allocated memory
 *
 */
errno_t fsnotify_security_init_hash_violation(fsnotify_mount_t* mntctx, fsnotify_node_t node,
		uint64_t offset, fsnotify_sec_payload_t** sec_event);

/**
 * Fill in an fsnotify security hash violation structure for a blk device violation
 *
 * Allocate and populate an fsnotify hash mismatch security violation.
 *
 * @param[in] mntctx  Pointer to the context which identifies what mountpoint
 *                    the violation occurred on.
 * @param[in] inode Inode of file on which the hash violation happened
 * @param[in] offset Offset within @p inode where the violation happened
 * @param[in] blkno disk block where violation occurred.
 * @param[in] hashblkno block within the hash tree
 * @param[in] hashlevel Level within hash tree
 * @param[in] hashblockoffset Offset within hash block where the mismatch is
 *                            located
 * @param[in,out] sec_event Pointer to where the function can store the
 *                          allocated security violation
 *
 * @post On successful return, @p sec_event points at allocated memory
 *
 * @retval EOK @p sec_event is allocated and initialized
 * @retval errno an error has occurredtypedef struct fsnotify_mount_s fsnotify_mount_t
 */
errno_t fsnotify_security_init_blk_hash_violation(fsnotify_mount_t* mntctx,
		fsnotify_node_t inode, uint64_t offset, uint64_t blkno,
		uint32_t hashblkno, uint16_t hashlevel, uint16_t hashblockoffset,
		fsnotify_sec_payload_t** sec_event);

/* A filesystem has been mounted at the given path (global/broadcast event) */
errno_t fsnotify_mount(char *mntpath);

/* A filesystem has been unmounted from the given path (global/broadcast event) */
errno_t fsnotify_unmount(char *umntpath);

errno_t fsnotify_security(enum inotify_qnx_ext_security_e subtype, fsnotify_sec_payload_t* violation, char *mntpath);

__END_DECLS

#endif /* #ifndef __fsnotify_h */
