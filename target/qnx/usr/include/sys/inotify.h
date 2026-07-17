/*
 * Copyright (c) 2023, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef _SYS_INOTIFY_H_
#define _SYS_INOTIFY_H_

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS


/**
 * @public
 * @defgroup fsnotify_client_api Fsnotify Client Application API
 * @copydoc fsnotify_client_if_design
 * @{
 */


/**
 * Format of a standard inotify event
 */
struct inotify_event {
	_Int32t   wd;     /**< Watch Descriptor, matches a return value from inotify_add_watch() */
	_Uint32t  mask;   /**< Bitfield of IN_* conditions which triggered this event */
	_Uint32t  cookie; /**< Cookie to allow matching up REMOVE and ADD events from a rename */
	_Uint32t  len;    /**< Length in bytes of the name field, including the NUL terminator */
	char name[0];     /**< UTF-8 NUL-terminated filename, only valid for certain condition types */
};

/**
 *
 * These values can be used with inotify_add_watch() to control which
 * conditions will trigger the watch.  They will also be set in events
 * returned from the system, to indicate which conditions caused the
 * event to be delivered.
 * @defgroup inotify_cond Supported Inotify Conditions
 * @{
 */
#define IN_ACCESS           0x00000001u /**< Notified if the file is read */
#define IN_MODIFY           0x00000002u /**< Notified if the file is written */
#define IN_ATTRIB           0x00000004u /**< Notified if the time/owner/perms is changed */
#define IN_CLOSE_WRITE      0x00000008u /**< Notified when a R/W fd is closed on the file */
#define IN_CLOSE_NOWRITE    0x00000010u /**< Notified when a R/O fd is closed on the file */
#define IN_OPEN             0x00000020u /**< Notified when the file is opened */
#define IN_MOVED_FROM       0x00000040u /**< Directory watches only.  Notified that a file was removed from the directory*/
#define IN_MOVED_TO         0x00000080u /**< Directory watches only.  Notified that a file was relocated into the directory */
#define IN_CREATE           0x00000100u /**< Directory watches only.  Notified that a new file is created */
#define IN_DELETE           0x00000200u /**< Directory watches only.  Notified that a file was deleted */
#define IN_DELETE_SELF      0x00000400u /**< Both file and directory.  Informs you the watched file/dir was deleted */
#define IN_MOVE_SELF        0x00000800u /**< Both file and directory.  Informs you the watched file/dir was moved */
#define IN_CLOSE            (IN_CLOSE_WRITE | IN_CLOSE_NOWRITE) /**< Convenience for both IN_CLOSE types */
#define IN_MOVE             (IN_MOVED_FROM | IN_MOVED_TO) /**< Convenience for both IN_MOVE types */

/**
 * Short hand for all inotify conditions
 */
#define IN_ALL_EVENTS (IN_ACCESS | IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE | IN_CLOSE_NOWRITE | IN_OPEN | IN_MOVED_FROM | IN_MOVED_TO | IN_CREATE | IN_DELETE | IN_DELETE_SELF | IN_MOVE_SELF)


/**
 * @}
 */

/* These flags can only be set in the mask of events returned to the client */
#define IN_UNMOUNT          0x00002000u /**< Notified that the filesystem containing the watched path was unmounted */
#define IN_Q_OVERFLOW       0x00004000u /**< The event queue overflowed, and some events were lost */
#define IN_IGNORED          0x00008000u /**< This watch isn't valid anymore, no new events will come from it */
#define IN_ISDIR            0x00010000u /**< Indicates the event describes operations on a directory */



/**
 * These flags should be bitwise OR into the @p mask parameter when adding a watch.
 * @defgroup watch_ctrl_flags Additional flags to control the behaviour of a watch
 * @{
 */
#define IN_DONT_FOLLOW      0x00100000u /**< Don't follow symlinks when registering a watch */
#define IN_MASK_ADD         0x00200000u /**< Merge additional conditions into an existing watch */
#define IN_ONLYDIR          0x00400000u /**< Only watch the requested path if it is a directory */
#define IN_ONESHOT          0x00800000u /**< Remove the watch after it triggers one time */
#define IN_EXCL_UNLINK      0x01000000u /**< Don't omit events to a parent directory watch, for unlinked files (unimplemented) */
#define IN_MASK_CREATE      0x02000000u /**< Only add a watch if one does not already exist for this path */
#define IN_NONBLOCK         0x04000000u /**< Set the O_NONBLOCK flag on the fd returned from inotify_init1() */
#define IN_CLOEXEC          0x08000000u /**< Set the O_CLOEXEC flag on the fd returned from inotify_init1() */

/**
 * @}
 */

/**
 * Initialize the inotify subsystem for the process.
 *
 * This function shall create a new connection to the inotify subsystem. It will
 * return a file descriptor which is required for all other inotify API calls.
 *
 * Closing the returned file descriptor will close the connection, and
 * release any watches created via this descriptor.
 *
 * This function aligns with the [ISO/IEC 23360-1-2:2021] (https://www.iso.org/standard/77866.html)
 *
 * @pre The Event Manager must be running
 * @post A connection to the fsevmgr shall be opened
 * @post some memory and locks within your process will be allocated.
 *
 * @returns A valid file descriptor on success
 * @returns -1 and sets errno to EMFILE if the maximum number of inotify connections have been opened.
 * @returns -1 and sets errno to ENFILE if no more file descriptors can be opened.
 */
int inotify_init(void);


/**
 * Initialize the inotify subsystem for the process, passing flags for the fd
 *
 * This function shall create a new connection to the inotify subsystem. It will
 * return a file descriptor which is required for all other inotify API calls.
 * If @p flags is 0, this function is identical to inotify_init().
 *
 * Closing the returned file descriptor will close the connection, and
 * release any watches created via this descriptor.
 *
 * @param[in] flags Additional flags to control the behaviour of the fd
 *
 * @pre The Event Manager must be running
 * @post A connection to the fsevmgr shall be opened
 * @post some memory and locks within the calling process will be allocated.
 *
 * @returns A valid file descriptor on success
 * @returns -1 and sets errno to EMFILE if no more inotify instances can be opened.
 * @returns -1 and sets errno to ENFILE if no more file descriptors can be opened.
 * @returns -1 and sets errno to ENAMETOOLONG if the FSNOTIFY_PREFIX env var is too long
 * @returns -1 and sets errno to EINVAL if @p flags contains unknown values
 */
int inotify_init1(const int flags);


/**
 * Register for notifications from a path.
 *
 * This function will register to receive notification events when operations
 * are performed against a given file.
 *
 * This function aligns with the [ISO/IEC 23360-1-2:2021] (https://www.iso.org/standard/77866.html)
 *
 * @param[in] inotify_fd The file descriptor returned from inotify_init()
 * @param[in] path       The path to the file for which they process wants to
 *                       receive notification.  The program must have at least read access.
 * @param[in] mask       A bitfield made up of the IN_* values.  Only the
 *                       conditions listed will trigger notification events
 *
 * @returns A watch descriptor.  When this watch is triggered, the
 *         struct inotify_event.wd field will be set to the value returned from this function.
 *
 * @returns -1 and sets errno to  EACCESS if the program does not have at least read access to @p path
 * @returns -1 and errno ENOENT  if @p path does not exist
 * @returns -1 and errno ENOTDIR If @p mask includes IN_ONLYDIR and @p path does not refer to a directory
 */
int inotify_add_watch(const int inotify_fd, const char* const path, const _Uint32t mask);

/**
 * Remove a watch.
 *
 * This function will remove and deallocate the watch identified by @p watchid.
 *
 * This function aligns with the [ISO/IEC 23360-1-2:2021] (https://www.iso.org/standard/77866.html)
 *
 * @param[in] inotify_fd The fd returned from inotify_init()
 * @param[in] watchid The watch descriptor returned from inotify_add_watch()
 *
 * @post An @c IN_IGNORED event will be generated for the watch @p watchid
 *
 * @returns 0 on success
 * @returns -1 and sets errno to EINVAL if @p watchid doesn't exist
 * @returns -1 and sets errno to EBADF if @p inotify_fd is not a file descriptor
 */
int inotify_rm_watch(const int inotify_fd, const int watchid);

/**
 * @}
 */

__END_DECLS

#endif /* #ifndef _SYS_INOTIFY_H_ */
