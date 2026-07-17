/*
 * Copyright (c) 2016-2025, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

/**
 * @file secpol.h
 * @brief This file defines the libsecpol API
 *
 */

#ifndef SECPOL_SECPOL_H_INCLUDED
#define SECPOL_SECPOL_H_INCLUDED

#include <stdint.h>
#include <sys/types.h>
#include <stdbool.h>

#ifdef __QNX__
#include <sys/neutrino.h>
#include <sys/ftype.h>
#endif

/** @cond */
__BEGIN_DECLS
/** @endcond */


#define SECPOL_INVALID_TYPE 0xffffffffu

// Policy id that represents no security policy being in effect
#define SECPOL_POLICY_ID_NO_POLICY  0u
// Bit set in the policy id that indicates that the policy is immutable and
// cannot be changed once loaded.
#define SECPOL_POLICY_ID_IMMUTABLE  0x80000000u

#define SECPOL_MAGIC   0x50434553u
#define SECPOL_VERSION 1u

/** Default security policy file */
#define SECPOL_DEFAULT_POLICY_FILE "/proc/boot/secpol.bin"

/** @brief Blob entry that provides the location of the size of the blob within
 * a security policy file.
 * @details An array of @c secpol_blob_t structures follows the security policy
 * file header.
 */
typedef struct {
    /** Type of data represented by the blob. */
    uint32_t type;
    /** Offset in file of data. */
    uint32_t offset;
    /** Size of data in bytes. */
    uint32_t size;
} secpol_blob_t;


/** Handle for security policy files */
typedef struct secpol_file_s secpol_file_t;

/** Flags for @e secpol_open() */
enum secpol_open_flags_e {
    /** Use handle as default when NULL is specified for the handle in other calls. */
    SECPOL_USE_AS_DEFAULT = 1,
};

#ifdef __QNX__

#include <spawn.h>

/**
 * @brief Open a security policy file.
 * @details In most cases, you set @c path to NULL and @c flags to @c
 * SECPOL_USE_AS_DEFAULT to ensure a common security policy file is used by all
 * processes and avoid the file being opened multiple times.
 *
 * However, if you are calling a single function, instead of preceding the call
 * with @e secpol_open() to set the default security policy file, pass NULL for
 * the function's handle.  This opens the system's default security policy file
 * for the duration of the function and then closes it.
 *
 * If @c SECPOL_USE_AS_DEFAULT is used and a previous call installed a default
 * handle, the call will fail with an @e errno of @c EBUSY. This error can
 * usually be ignored as there is already a policy file accessible for other
 * functions to use.
 *
 * @param[in] path  Path to the file.  If NULL, the default path is used.
 * @param[in] flags Zero or more flags from @c secpol_open_flags_e ORred together.
 *
 * @return  A handle to the file, or NULL if open failed (@e errno is set).
 */
secpol_file_t *secpol_open(const char *path__, uint32_t flags__);

/**
 * Close the security policy file.
 *
 * @param[in] handle  Handle to the security policy file.
 *
 * @retval None
 */
void secpol_close(secpol_file_t *handle__);

/**
 * @brief Find and possibly return a given blob.
 * @details The @e secpol_find_blob() function may be used to find a blob of a
 *          particular type, typically referenced by one of the @c SECPOL_BLOB_*
 *          constants.  It may also be used to iterate through all blobs in the
 *          file with no prior knowledge of its contents by using @c
 *          SECPOL_BLOB_NEXT as the type.
 *
 * @param[in] handle Handle to the security policy file. Usually NULL, which
 *                   specifies that the default security policy file is
 *                   used (either the system default or one set using @e
 *                   secpol_open()).
 * @param[in] type   The type of blob to search for, or the constant @c
 *                   SECPOL_BLOB_NEXT to return the next blob in the file.
 * @param[out] blob_info   If non-NULL, updated with information on the blob.
 * @param[out] data        If non-NULL, updated to contain a pointer to the
 *                         contents of the blob. This memory must be freed by the
 *                         caller.
 *
 * @returns @c 0 if blob was found, or @c -1 if an error occurred
 *          (@e errno is set).
 */
int secpol_find_blob(secpol_file_t *handle__, uint32_t type__,
                     secpol_blob_t *blob_info__, void **data__);

/**
 * Find and possibly return a given custom class blob.
 *
 * @param[in] handle      Handle to the security policy file. Usually NULL, which
 *                        specifies that the default security policy file is
 *                        used (either the system default or one set using @e
 *                        secpol_open()).
 * @param[in] name        The name of the class associated with the blob.
 * @param[out] blob_info  If non-NULL, updated with information on the blob.
 * @param[out] data       If non-NULL, updated to contain a pointer to the
 *                        contents of the blob. This memory must be freed by the
 *                        caller.
 *
 * @returns @c 0 if blob was found, or @c -1 if an error occurred
 *          (@e errno is set).
 */
int secpol_find_custom_blob(secpol_file_t *handle__, const char *name__,
                            secpol_blob_t *blob_info__, void **data__);

/**
 * Reset the handle so that secpol_find_blob with SECPOL_BLOB_NEXT returns the
 * first blob.
 *
 * @param[in] handle    Handle to the security policy file. Usually NULL, which
 *                      specifies that the default security policy file is used
 *                      (either the system default or one set using @e
 *                      secpol_open()).
 *
 * @retval None
 */
void secpol_reset(secpol_file_t *handle);

/**
 * Return the type ID associated with a type name
 *
 * @param[in] handle    Handle to the security policy file. Usually NULL, which
 *                      specifies that the default security policy file is used
 *                      (either the system default or one set using @e
 *                      secpol_open()).
 * @param[in] type_name Name of the type.
 *
 * @return Type ID associated with the name, or @c SECPOL_INVALID_TYPE if the
 * name was not found.
 */
uint32_t secpol_get_type_id(secpol_file_t *handle__, const char *type_name__);

/**
 * Return the type name associated with a type ID
 *
 * @param[in] handle    Handle to the security policy file. Usually NULL, which
 *                      specifies that the default security policy file is used
 *                      (either the system default or one set using @e
 *                      secpol_open()).
 * @param[in] type_id   ID of the type.
 *
 * @return Name of the type, or NULL if the type ID was not found.
 */
const char *secpol_get_type_name(secpol_file_t *handle__, uint32_t type_id__);

/**
 * Flags for @e secpol_transition_type(), @e secpol_posix_spawnattr_settypeid()
 * and @e secpol_resolve_name().
 */
enum secpol_flags_e {
    /** The specified name refers directly to a type name. */
    SECPOL_TYPE_NAME = 1,
};

/**
 * @brief Return the type ID of the process.
 * @details The type ID that the @e secpol_type_id() function returns is
 * accurate only if the process does not call @e procmgr_set_type_id() and
 * instead makes any type changes by calling @e secpol_transition_type().
 *
 * @return Type ID of the process.
 */
uint32_t secpol_type_id(void);

/**
 * Sets the type ID of the process.
 *
 * @param[in] type_id    The type ID to set
 *
 * @return 0 if the type was successfully switched; if no type change was
 *         performed, -1 and @e errno is set to one of the following values:
 *         - @b ENOTSUP No security policy is in use.
 *         - @b EPERM The process lacks the PROCMGR_AID_SETTYPEID ability or
 *           does not have a subrange that includes type_id.
 *         - @b ESECTYPEINVAL The value of type_id is invalid.
 */
int secpol_set_type_id(uint32_t type_id__);

/**
 * Resolve a type name to a type ID.
 *
 * By default, the type name is assumed to refer to a derived type; that is, a
 * type that is selected based on the process' current type and the name passed
 * in. The @c name parameter can also represent the actual type name by passing
 * @c SECPOL_TYPE_NAME in the flags.
 *
 * @param[in] handle  Handle to the security policy file. Usually NULL, which
 *                    specifies that the default security policy file is used
 *                    (either the system default or one set using @e
 *                    secpol_open()).
 * @param[in] name    Type name to look up.
 * @param[in] flags   Zero or more flags from @c secpol_flags_e ORred together.
 *
 * @return The type ID that is associated with @c name based on the current type
 *         of the process, or @c SECPOL_INVALID_TYPE if there is no type ID to
 *         return.
 */
uint32_t secpol_resolve_name(secpol_file_t *handle__, const char *name__,
                             uint32_t flags__);


/**
 * @brief Transition to a new type.
 * @details The secpol_transition_type() function attempts to switch to a new
 * type that is either specified as a type name, or, more commonly, as a string
 * (e.g., "run") that is used to derive a type from the current type of the
 * process.
 *
 * If the function is successful, it indicates that there is a security policy
 * in use, the process is now running with whatever capabilities were deemed
 * appropriate, and that the process should not itself attempt to modify
 * abilities as a means of dropping privilege.
 *
 * If the function fails, the process should instead perform whatever privilege
 * dropping procedure it supports, which in some cases means doing nothing. If
 * the function fails and a policy is in force, system trace events are emitted
 * to allow the problem to be diagnosed.
 *
 * Behavior should usually be based only on success or failure, not on the
 * specific cause of failure.  Failure of this function should not be considered
 * fatal as it will render the program unable to run without security policies.
 *
 * By default, a derived type is used; that is, the type ID is selected based on
 * the process' current type and the name passed in. The @c name parameter can
 * also represent the actual type name by passing @c SECPOL_TYPE_NAME in the
 * flags.
 *
 * It is expected this function will be called only once following
 * initialization.  Multiple calls to the function are unlikely to yield any
 * security benefits.
 *
 * @b Example
 *
 * A security policy has the following rules:
 *
 * @code
 * derive_type resmgr1_t run resmgr1_run_t;
 * derive_type resmgr2_t run resmgr_post_init_t;
 * @endcode
 *
 * If a resource manager is started using the security type @c resmgr1_t and
 * then calls the following function, it switches its type to @c resmgr1_run_t:
 *
 * @code secpol_transition_type(NULL, NULL, 0); @endcode
 *
 * Alternatively, if the resource manager is started using the type @c
 * resmgr2_t, this call switches it to @c resmgr_post_init_t.
 *
 * @param[in] handle  Handle to the security policy file. Usually NULL, which
 *                    specifies that the default security policy file is used
 *                    (either the system default or one set using @e
 *                    secpol_open()).
 * @param[in] name    Name of type, or name to derive type from based on the
 *                    current type.  If a derived type is used, NULL may be
 *                    passed to use the default name "run".
 * @param[in] flags   Zero or more flags from @c secpol_flags_e ORred together.
 *
 * @return 0 if the type was successfully switched; if no type change was
 * performed, -1 and @e errno
 *         is set to one of the following values:
 *         - @b ENOTSUP - No security policy is in effect.
 *         - @b ESECTYPEINVAL  - The security policy is invalid.
 */
int secpol_transition_type(secpol_file_t *handle__, const char *name__,
                           uint32_t flags__);

/**
 * @brief Update a spawn attribute object to spawn a child with a different type
 * @details If a security policy is in force, the @e
 * secpol_posix_spawnattr_settypeid() function updates the POSIX spawn attribute
 * structure with the type to spawn as. If a policy is not in force, the
 * function does nothing.
 *
 * This function is equivalent to calling @e posix_spawnattr_settypeid(), but @e
 * secpol_posix_spawnattr_settypeid() is simpler to use and allows a process to
 * work both with and without security policies.
 *
 * By default, the type ID is selected based on the process' current type and
 * the name passed in (i.e., a derived type). The @c name parameter can also
 * represent the actual type name by passing @c SECPOL_TYPE_NAME in the flags.
 *
 * If the process spawns multiple child processes that are expected to have
 * different security needs, a different name can be used for each to allow the
 * security policy to fit the security requirements more closely. If the
 * security of all children is likely to be substantially the same, NULL can be
 * passed for the name to use the default name "child". This option can be used
 * only if a derived type is used.
 *
 * Because @e secpol_posix_spawnattr_settypeid() sets the @c
 * POSIX_SPAWN_SETTYPEID flag in the spawn attributes if it is appropriate, you
 * don't need to set it using @e posix_spawnattr_setxflags().  However, if you
 * call @e posix_spawnattr_setxflags() to set additional flags, it is possible
 * to lose flags that @e secpol_posix_spawnattr_settypeid() has set. To avoid
 * this problem, call @e posix_spawnattr_getxflags() to get the current flags,
 * OR in the additional flags, and then set the result using @e
 * posix_spawnattr_setxflags().
 *
 * @b Example
 *
 * A security policy has the following rules:
 *
 * @code
 * derive_type resmgr1_t low_priv resmgr1_low_t;
 * derive_type resmgr1_t high_priv resmgr1_high_t;
 * @endcode
 *
 * These rules allow you use the following function call to spawn child processes
 * with a lower level of privilege (of type @c resmgr1_low_t):
 *
 * @code secpol_posix_spawnattr_settypeid(NULL, &attr, "low_priv", 0); @endcode
 *
 * The following function spawns child processes with a higher level of
 * privilege (type @c resmgr1_high_t):
 *
 * @code secpol_posix_spawnattr_settypeid(NULL, &attr, "high_priv", 0); @endcode
 *
 * @param[in] handle     Handle to the security policy file. Usually NULL, which
 *                       specifies that the default security policy file is used
 *                       (either the system default or one set using @e
 *                       secpol_open()).
 * @param[in,out] attrp   A pointer to the spawn attributes object to update.
 * @param[in] name        Name of type, or name to derive type from based on the
 *                        current type.  If a derived type is used, NULL may be
 *                        passed to use the default name "child".
 * @param[in] flags       Zero or more flags from @c secpol_flags_e ORred together.
 *
 * @returns @c 0 if spawn attributes were successfully updated or no update was
 *          wanted, or @c -1 if attribute update failed or no valid type was
 *          found.
 */
int secpol_posix_spawnattr_settypeid(secpol_file_t *handle__,
                                     posix_spawnattr_t *attrp__,
                                     const char *name__, uint32_t flags__);

/** Handle for security policy permissions */
typedef struct secpol_permission_s secpol_permission_t;

/**
 * Flags for @e secpol_get_permission()
 */
enum secpol_get_permission_flags_e {
    /** If set, @e secpol_get_permission() will fail and return NULL if there is
     * no policy in use or the specified class or permission does not exist.  If
     * not set, the permission will be allowed for @c root users when there is
     * no policy and never allowed when there is a policy.
     */
    SECPOL_PERM_STRICT = 1,
};

/**
 * @brief Returns a handle to a permission associated with a custom class.
 * @details The @e secpol_get_permission() function returns a permission object
 *          that @e secpol_check_permission() uses to determine whether a
 *          request from a process is permitted. By default, the @e
 *          secpol_get_permission() function succeeds even when no security
 *          policy is in use or if the class or permission cannot be
 *          found. However, if the system uses security policies, the permission
 *          is always denied.
 *
 *          If the system is not using security policies, permission checking is
 *          performed by evaluating the class and permission name that @e
 *          secpol_get_permission() provides against environment variables.  For
 *          more information, see <a
 *          href="manual/check_custom_permissions.xml">Checking custom
 *          permissions when no policy is used</a>.
 *
 * @param[in] handle     Handle to the security policy file. Usually NULL, which
 *                       specifies that the default security policy file is used
 *                       (either the system default or one set using @e
 *                       secpol_open()).
 * @param[in] class      Name of the class associated with the permission.
 * @param[in] permission Name of the permission.
 * @param[in] flags      Zero or more flags taken from the @c
 *                       secpol_get_permission_flags_e enumeration.
 *
 * @returns A handle to the permission, or NULL if the call failed. On failure,
 * @e errno is set to one of the following values:
 * - @b ENOTSUP No security policy is in use.
 * - @b ENOSYS The class or permission is not in the policy file or the policy
     ID is wrong.
 * - @b EINVAL Parameters are not valid for the specified policy file.
 * - @b ENOMEM Out of memory.
 * - @b ENOENT Unable to open the policy file.
 */
secpol_permission_t *secpol_get_permission(secpol_file_t *handle__,
                                           const char *class__,
                                           const char *permission__,
                                           unsigned flags__);

/**
 * @brief Check if a requesting process has a specified permission.
 * @details When a call to @e secpol_check_permission() fails, it indicates that
 *          the caller is denied the permission check. In most cases, all errors
 *          should be treated identically.
 *
 *          The @c otype argument allows you to restrict the test for a
 *          permission to a specific object that the permission accesses or acts
 *          on. For more information, see <a
 *          href="manual/restrict_permissions_by_object.xml">Customizing
 *          permissions using a security policy</a>.
 *
 *          If the system is not using security policies, permission checking is
 *          performed by evaluating the class and permission name specified by
 *          @e secpol_get_permission() against environment variables. See <a
 *          href="manual/check_custom_permissions.xml">Checking custom
 *          permissions when no policy is used</a>.
 *
 * @param[in] info       The message information associated with the message that
 *                       this check relates to.
 * @param[in] otype      The type of the object being accessed or acted on.
 * @param[in] permission A handle to a permission returned by
 *                       @e secpol_get_permission().
 *
 * @returns @c 0 if the requesting process has the indicated permission for the
 *          type @c otype, or @c -1 if the call failed. On failure, @e errno is
 *          set to one of the following values:
 * - @b EPERM Permission denied.
 * - @b EINVAL Invalid parameters to function.
 * - @b ENOMEM Out of memory.
 */
int secpol_check_permission(const struct _msg_info *info__, uint32_t otype__,
                            const secpol_permission_t *permission__);

/**
 * @brief Locate an entry associated with a type ID
 * @details The @e secpol_find_entry() function locates an entry associated with
 *          a type ID in an array that is sorted by type ID and where the first
 *          element is the type ID.
 *
 * @param[in] type_id  Type ID to search for.
 * @param[in] array    Array to search.
 * @param[in] ecount   Number of elements.
 * @param[in] esize    Size of each element in bytes.
 *
 * @return A pointer to the element, or NULL if an element with the indicated
 * type ID wasn't found.
 */
void *secpol_find_entry(uint32_t type_id__, void *array__, uint32_t ecount__,
                        uint32_t esize__);

/**
 * Return the CRC32 of block of data.
 *
 * @param[in] buffer    Pointer to a buffer of data.
 * @param[in] length    Length of data.
 *
 * @return The CRC (cyclic redundancy check).
 */
uint32_t secpol_crc32(const void *buffer__, uint32_t length__);

/**
 * @brief Return the policy ID of any policy that has been pushed to @c procnto.
 *
 * @details The @e secpol_get_policy_id() function returns the policy ID of the
 *          security policy that is in effect. A policy ID of 0 indicates that
 *          there is no policy.
 *
 * @param[out] policy_id    Address of a variable to hold the policy ID.
 *
 * @returns @c 0 if call was successful, or -1 if request failed (@e errno is
 * set).
 */
int secpol_get_policy_id(uint32_t *policy_id__);

// Types that symbols like RESMGR_HANDLE_T and RESMGR_OCB_T represent depend on
// the order headers are included. As it's not up to us to define these things,
// avoid including any of the affected headers.
struct _iofunc_attr;            // == iofunc_attr_t
struct _dispatch;               // == dispatch_t
struct _resmgr_attr;            // == resmgr_attr_t
struct _resmgr_connect_funcs;   // == resmgr_connect_funcs_t
struct _resmgr_io_funcs;        // == resmgr_io_funcs_t

/**
 * @brief Attach a path to the pathname space with permissions set via a security
 *        policy.
 * @details The @e secpol_resmgr_attach() function performs the same operation
 *          as @e resmgr_attach() but also allows you to set permissions,
 *          ownership, and ACLs based on a security policy. It provides a way
 *          for a system integrator to set permissions for a server without
 *          adding command line parameters.
 *
 *          Most parameters have the same meaning as the corresponding @e
 *          resmgr_attach() ones.
 *
 *          If @e iofunc_attr has a mount structure, and @e mount->dev is 0,
 *          then @e secpol_resmgr_attach() issues a @e resmgr_devino() call for
 *          @e mount->dev and @e attr->inode.
 *
 *          If there is no security policy file, @e secpol_resmgr_attach()
 *          behaves the same as @e resmgr_attach().
 *
 *          You can use a security policy file to configure mount points
 *          only, without using any other security policies functionality.
 *
 *          <B>Testing a secpol_resmgr_attach() call</B>
 *
 *          To test the use of @e secpol_resmgr_attach(), create a file with a
 *          sample @c mount_point policy. For example, create a file @c
 *          policy.txt that has the following content. Replace @c
 *          /dev/mountpoint with the path that your resource manager uses:
 *          @code
 *          mount_point 1000:1001 { u::rw g::r u:99:rw } /dev/mountpoint;
 *          @endcode
 *
 *          Use the following command to compile the file:
 *
 *          @code
 *          secpolcompile -o policy.bin policy.txt
 *          @endcode
 *
 *          Put the compiled policy on your target (at @e filepath) and use the
 *          following command to create a process manager symlink to it, which
 *          allows it to be accessed at the path <tt>/proc/boot/secpol.bin</tt>:
 *
 *          @code
 *          ln -sPf <filepath> /proc/boot/secpol.bin
 *          @endcode
 *
 *          Run your resource manager and use @c getfacl to look at the
 *          ownership and permissions of your mount point, which should be the
 *          ones specified in the policy.
 *
 *          If the call to @e secpol_resmgr_attach() fails instead, it might be
 *          because your resource manager prevents the use of ACLs. You can
 *          confirm this by removing <tt>u:99:rw</tt> in the example policy
 *          above and trying again. You can't use ACLs when the @e mount member
 *          of your @c iofunc_attr_t structure is set to an @c iofunc_mount_t
 *          structure rather than left as NULL. To fix this issue, the @e conf
 *          member of the mount structure should include the flag @c
 *          IOFUNC_PC_ACL (go to "The iofunc_mount_t mount structure" in
 *          <em>Getting Started with the QNX OS</em>). Because there is rarely,
 *          if ever, a reason to disable the use of ACLs with resource manager
 *          mount points, setting @c IOFUNC_PC_ACL allows their use with no
 *          further action required by you.
 *
 * @param[in] handle    Handle to the security policy file. Usually NULL, which
 *                      specifies that the default security policy file is used
 *                      (either the system default or one set using @e
 *                      secpol_open()).
 * @param[in] dpp       A dispatch handle (see @e resmgr_attach() in the @e C
 *                      @e Library @e Reference).
 * @param[in] attr      A resource manager attribute (see @e resmgr_attach()).
 * @param[in] path      The path to attach to. Unlike @e resmgr_attach(), this
 *                      value cannot be NULL.
 * @param[in] file_type The file type (see @e resmgr_attach()).
 * @param[in] flags     Flags that control the pathname resolution (see @e
 *                      resmgr_attach()).
 * @param[in] connect_funcs   Structure that defines connect functions (see @e
 *                            resmgr_attach()).
 * @param[in] io_funcs        Structure that defines connect I/O functions (see
 *                            @e resmgr_attach()).
 * @param[in,out] iofunc_attr Attribute structure that is passed as the @p
 *                            handle parameter of @e resmgr_attach(). It
 *                            contains the ownership, permissions, and ACLs for
 *                            the mount point and may be updated by @e
 *                            secpol_resmgr_attach().
 * @param[out] perms_set      If non-NULL, set to true if permissions were
 *                            altered; otherwise, set to false.
 *
 * @returns A unique link ID associated with this attach, or -1 on failure.
 * @returns The returned ID is needed to detach the pathname at a later time
 *          using @e resmgr_detach().  It is also passed to all connect and I/O
 *          message handlers in the resource manager context structure (@p ctp)
 *          created by @e resmgr_context_alloc().
 * @returns On failure, @e errno is set to ENOTSUP if the policy includes ACLs
 *          and the resource manager does not allow them.
 * @returns For other possible errors, see @e resmgr_attach().
 */
int secpol_resmgr_attach(secpol_file_t *handle__, struct _dispatch *dpp__,
                         struct _resmgr_attr *attr__, const char *path__,
                         enum _file_type file_type__, unsigned flags__,
                         const struct _resmgr_connect_funcs *connect_funcs__,
                         const struct _resmgr_io_funcs *io_funcs__,
                         struct _iofunc_attr *iofunc_attr__, bool *perms_set__);

/** Constant that can be passed to @c secpol_find_entry to return the next blob
 * of any type.
 */
#define SECPOL_BLOB_NEXT 0xffffffffu

#endif  // __QNX__


/** @cond */
__END_DECLS
/** @endcond */

#endif
