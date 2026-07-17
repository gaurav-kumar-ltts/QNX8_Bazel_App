/*
 * Copyright (c) 2022-2024, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef QNX_SECPOL_SECPOL_EVENTS_H_INCLUDED
#define QNX_SECPOL_SECPOL_EVENTS_H_INCLUDED

#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

/** @cond */
__BEGIN_DECLS
/** @endcond */

/*
 * Flags returned from secpolev_wait_event()
 */
/** Indicates the privilege was denied. */
#define SECPOL_EVENT_FLAG_DENIED 0x1u

typedef enum {
    /** Indicates the end of event monitoring */
    SECPOLEV_EVENT_END,
    /** secpolev_wait_event() called when event monitoring is not active */
    SECPOLEV_EVENT_ERROR,
    /** An event representing the testing of a process's abilities */
    SECPOLEV_EVENT_ABILITY_TEST,
    /** An event resulting from testing the path associated with a
     * resmgr_attach() or name_attach() call. */
    SECPOLEV_EVENT_PATH_ATTACH,
    /** An event resulting from testing the path associated with a
     * pathmgr_symlink() call. */
    SECPOLEV_EVENT_PATH_LINK,
    /** An event resulting from a process calling secpol_check_permission(). */
    SECPOLEV_EVENT_CUSTOM_PERM,
} secpolev_event_type_t;

typedef enum {
    /** Should not occur */
    SECPOLEV_PATH_EVENT_UNKNOWN,
    /** Operation was permitted */
    SECPOLEV_PATH_EVENT_OK,
    /** Operation was denied as it required a channel type change that was not
     *  permitted */
    SECPOLEV_PATH_EVENT_CONFLICT,
    /** Operation was denied as the type of operation did not match the rule
     * (attach vs link) */
    SECPOLEV_PATH_EVENT_BAD_OP,
    /** Operation was denied as there was no rule for the path. */
    SECPOLEV_PATH_EVENT_NO_RULE,
} secpolev_path_event_status_t;

typedef enum {
    /** Shutdown should complete immediately and release all resources. This
     * invalidates any strings returned by any secpolev_get_*() function.
     * The use of this is typically appropriate only by the thread that is
     * calling secpolev_wait_event().
     */
    SECPOLEV_SHUTDOWN_IMMEDIATE,
    /** Initiate shutdown and block until secpolev_wait_event() has returned
     * the SECPOLEV_EVENT_END event.
     */
    SECPOLEV_SHUTDOWN_WAIT,
    /** Initiate shutdown but don't wait until secpolev_wait_event() has returned
     * the SECPOLEV_EVENT_END event. Final cleanup will not occur until the
     * SECPOLEV_EVENT_END event is encountered.
     */
    SECPOLEV_SHUTDOWN_NOWAIT,
} secpolev_shutdown_type_t;

#define SECPOL_SHUTDOWN_IMMEDIATE   SECPOLEV_SHUTDOWN_IMMEDIATE
#define SECPOL_SHUTDOWN_WAIT        SECPOLEV_SHUTDOWN_WAIT
#define SECPOL_SHUTDOWN_NOWAIT      SECPOLEV_SHUTDOWN_NOWAIT

/**
 * Flags provided with secpolev_get_ability_info
 */
/* Ability is a static ability */
#define SECPOLEV_ABILITY_STATIC     0x1u
/* Ability is ranged. Custom abilities are assumed un-ranged.  Certain static
 * abilities are treated as un-ranged in cases where the range is not meaningful,
 * for example prot_exec.
 */
#define SECPOLEV_ABILITY_RANGED     0x2u
/* The root set of abilities was tested. */
#define SECPOLEV_ABILITY_ROOT       0x4u

/**
 * Initiate event monitoring.
 *
 * @param flags             Must be zero, there are currently no flags defined.
 * @param buffer_count      The number of 16k kernel event buffers to be
 *                          allocated. A minimum of 2 buffers must be specified.
 * @param flush_interval    The time in milliseconds that trace buffers are
 *                          flushed (trace events may be delayed by up to this
 *                          time). If 0, then no automatic flushing is performed.
 * @return @c 0 is successful, or @c -1 if an error occurred. On failure, @e
 * errno is set to:
 * - @b EINVAL buffer_count less than 2 or flags non-zero.
 * - @b EBUSY  Trace system is busy.
 * - @b EAGAIN secpolev_init() has already been called.
 * - @b EPERM  Process lacks necessary abilities.
 */
int secpolev_init(unsigned flags__, unsigned buffer_count__,
                  unsigned flush_interval__);

/**
 * Request termination of event monitoring. This may be executed in a different
 * thread than @e secpolev_wait_event() is being called in but monitoring is not
 * complete until @e secpolev_wait_event() returns @c SECPOLEV_EVENT_END.
 *
 * @param type  Indicates the manner shutdown is performed in.
 * @return Returns 0 on success, -1 on error. On failure, @e errno is set to:
 * - @b EINVAL type is invalid
 *
 */
int secpolev_shutdown(secpolev_shutdown_type_t type__);

/**
 * Flush events so they will be received immediately. This may be called from
 * any thread.
 *
 * @return 0
 */
int secpolev_flush(void);

/**
 * Wait for the next event.
 *
 * @param flags    Flags indicating information about the event. The flags are
 *                 defined by symbolic constants with a @c SECPOL_EVENT_FLAG_
 *                 prefix.
 * @return The type of event received. If either @c SECPOLEV_EVENT_END or
 * @c SECPOLEV_EVENT_ERROR is returned, @e secpolev_init() must be called to restart
 * event monitoring.
 */
secpolev_event_type_t secpolev_wait_event(unsigned *flags__);

/**
 * Return the timestamp associated with the last event received.
 *
 * @return  The timestamp obtained from ClockCycles() when the current event was
 *          generated. If there is no current event, UINT64_MAX is returned and
 *          errno is set to ENOTSUP.
 */
uint64_t secpolev_get_timestamp(void);

/**
 * Return the PID of the process associated with the last event received.
 * @return The PID or 0 if there is no current event.
 */
pid_t secpolev_get_pid(void);

/**
 * Return the name of the process associated with the last event received or NULL
 * if not known. There are typically a few ability checks, for example prot_exec
 * and map_fixed that are tested prior to a process receiving a name.
 *
 * The returned string remains valid until the next call to @e secpolev_wait_event().
 *
 * @return The process name.
 */
const char *secpolev_get_process_name(void);

/**
 * Return the name of the type associated with the process or NULL if unknown.
 * For a process with type id 0, the string "-" is returned.
 *
 * The returned string remains valid until the next call to @e secpolev_wait_event().
 *
 * @return The process type.
 */
const char *secpolev_get_process_type(void);

/**
 * Returns information about an ability event (that is, an event of type
 * @c SECPOLEV_EVENT_ABILITY_TEST).
 *
 * The start and end values indicate the range tested for a ranged ability. For
 * static abilities the SECPOLEV_ABILITY_RANGED is set if the ability supports
 * ranges. For custom abilities, this flag is not set and it is unknown if the
 * ability supports ranges though they typically do not.
 *
 * The returned strings remains valid until the next call to @e secpolev_wait_event().
 *
 * @param id    If non-NULL set to the ID of the ability
 * @param name  If non-NULL set to the name of the ability
 * @param flags If non-NULL, provides zero more @c SECPOLEV_ABILITY_* flags.
 * @param start If non-NULL set to the start of the range that was tested. This
 *              is only likely to be meaningful if the @c SECPOLEV_ABILITY_RANGED
 *              flag is set.
 * @param end   If non-NULL set to the end of the range that was tested. This is
 *              only likely to be meaningful if the @c SECPOLEV_ABILITY_RANGED
 *              flag is set.
 * @return @c 0 is successful, or @c -1 if an error occurred.  On failure, @e
 * errno is set to:
 * - @b ENOTSUP There is no current event or the event is not of type
 *              @c SECPOLEV_EVENT_ABILITY_TEST.
 */
int secpolev_get_ability_info(unsigned *id__, const char **name__, unsigned *flags__,
                              uint64_t *start__, uint64_t *end__);

/**
 * Returns information about a path event (one with type @c SECPOLEV_EVENT_PATH_ATTACH
 * or @c SECPOLEV_EVENT_PATH_LINK.
 *
 * The returned string remains valid until the next call to @e secpolev_wait_event().
 *
 * @param path      If non-NULL, returns the path associated with the event.
 * @param status    If non-NULL, provides additional information as to why the
 *                  rule was denied.
 *
 * @return @c 0 is successful, or @c -1 if an error occurred.  On failure, @e
 * errno is set to:
 * - @b ENOTSUP There is no current event or the event is not of type
 *              @c SECPOLEV_EVENT_PATH_ATTACH or @c SECPOLEV_EVENT_PATH_LINK.
 */
int secpolev_get_path_info(const char **path__, secpolev_path_event_status_t *status__);

/**
 * Returns information about a secpol custom permission event (one with type
 * @c SECPOLEV_EVENT_CUSTOM_PERM).
 *
 * The returned strings remain valid until the next call to @e secpolev_wait_event().
 *
 * @param class_name    If non-NULL returns the name of the class associated with
 *                      the event.
 * @param perm_name     If non-NULL returns the name of the class's permission
 *                      that was tested.
 * @param obj_type      If non-NULL returns the name of the security type of the
 *                      object associated with the test.
 *
 * @return @c 0 is successful, or @c -1 if an error occurred.  On failure, @e
 * errno is set to:
 * - @b ENOTSUP There is no current event or the event is not of type
 *              @c SECPOLEV_EVENT_CUSTOM_PERM.
 */
int secpolev_get_custom_perm_info(const char **class_name__, const char **perm_name__,
                                  const char **obj_type__);

/**
 * Returns the number of event fragments that have been dropped. A change in this
 * number indicates that there is too little buffer space to reliably capture
 * all events. Due to restarted kernel calls and events being made up of multiple
 * fragments it is not possible to infer from this number how many, or if any
 * events have been lost.
 *
 * The dropped count is always returned as 0 when secpolgenerate is in use as
 * it can not be used reliably as a determination of required buffer count.
 *
 * @return Number of dropped fragments
 */
uint64_t secpolev_get_dropped_count(void);

typedef void (*secpolev_log_callback_t)(char const *format, va_list args);

/**
 * Set a callback for any error logging that is done by secpolev. Setting the
 * callback to NULL (the default) will result in output to stderr.
 * @param log_callback	Callback function
 */
void secpolev_set_log_callback(secpolev_log_callback_t log_callback__);

/**
 * Log a message using the log callback set by secpolev_set_log_callback or to
 * stderr if none is set.
 * @param format    printf style format string
 */
void secpolev_log(char const *format__, ...) __attribute__ ((format (printf, 1, 2)));

/**
 * Log a message using the log callback set by secpolev_set_log_callback or to
 * stderr if none is set.
 * @param format    printf style format string
 * @param args      values to be output
 */
void secpolev_vlog(char const *format__, va_list args__) __attribute__ ((format (printf, 1, 0)));


/** @cond */
__END_DECLS
/** @endcond */

#endif
