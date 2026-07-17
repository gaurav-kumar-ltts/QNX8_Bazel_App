/*
 * $QNXLicenseC:
 * Copyright 2017-2022, QNX Software Systems.  All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.  Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef QNX_QH_LOG_H_INCLUDED
#define QNX_QH_LOG_H_INCLUDED

/**
 * @file log.h
 * QNX helpers related to logging. All QNX helpers logging functions are thread safe.
 */

/* sorted headers from this project */
#ifndef QNX_QH_ATTR_H_INCLUDED
#include "qh/attr.h"
#endif

/* sorted library headers */

/* sorted system headers */
#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifndef _STDARG_H_INCLUDED
#include <stdarg.h>
#endif

#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * @defgroup verbosity_levels Verbosity levels
 *
 * Identifiers that represent the verbosity levels when logging messages.
 *
 * The QNX helpers logging functions treat verbosity level 0 as if it was @c QH_LOG_SEVERITY_INFO.
 * This mechanism is just for convenience because it allows simpler @e qh_log() calls, where 0
 * is specified instead of a @c QH_LOG_SEVERITY_* identifier.
 *
 * It includes convenience identifiers equivalent to the @c QH_LOG_SEVERITY_* identifiers, but with
 * shorter names that are easier to use in the code.
 *
 * @{
 */
#define QH_LOG_SEVERITY_SHUTDOWN                                                         UINT64_C(1)
#define QH_LOG_SEVERITY_CRITICAL                                                         UINT64_C(2)
#define QH_LOG_SEVERITY_ERROR                                                            UINT64_C(3)
#define QH_LOG_SEVERITY_WARNING                                                          UINT64_C(4)
#define QH_LOG_SEVERITY_NOTICE                                                           UINT64_C(5)
#define QH_LOG_SEVERITY_INFO                                                             UINT64_C(6)
#define QH_LOG_SEVERITY_DEBUG1                                                           UINT64_C(7)
#define QH_LOG_SEVERITY_DEBUG2                                                           UINT64_C(8)
/** @} */

/**
 * @ingroup verbosity_levels
 */
#define QH_LOG_SHUTDOWN                                                     QH_LOG_SEVERITY_SHUTDOWN
/**
 * @ingroup verbosity_levels
 */
#define QH_LOG_CRITICAL                                                     QH_LOG_SEVERITY_CRITICAL
/**
 * @ingroup verbosity_levels
 */
#define QH_LOG_ERROR                                                           QH_LOG_SEVERITY_ERROR
/**
 * @ingroup verbosity_levels
 */
#define QH_LOG_WARNING                                                       QH_LOG_SEVERITY_WARNING
/**
 * @ingroup verbosity_levels
 */
#define QH_LOG_NOTICE                                                         QH_LOG_SEVERITY_NOTICE
/**
 * @ingroup verbosity_levels
 */
#define QH_LOG_INFO                                                             QH_LOG_SEVERITY_INFO
/**
 * @ingroup verbosity_levels
 */
#define QH_LOG_DEBUG1                                                         QH_LOG_SEVERITY_DEBUG1
/**
 * @ingroup verbosity_levels
 */
#define QH_LOG_DEBUG2                                                         QH_LOG_SEVERITY_DEBUG2

/**
 * @defgroup message_destinations Message destinations
 *
 * Log flags that specify log message destinations.
 * @{
 */
#define QH_LOG_DEST_STDOUT                                                      UINT64_C(0x00100000)
#define QH_LOG_DEST_STDERR                                                      UINT64_C(0x00200000)
#define QH_LOG_DEST_SLOG                                                        UINT64_C(0x00400000)
#define QH_LOG_DEST_SLOG2                                                       UINT64_C(0x00800000)
/** @} */

/**
 * @defgroup all_destinations Set of log destinations or no log destinations
 *
 * Identifiers that represent either a set of log destinations or no destinations.
 * @{
 */
#define QH_LOG_DEST_NONE                                                                 UINT64_C(0)
#define QH_LOG_DEST_ALL                                                         UINT64_C(0xFFF00000)
#define QH_LOG_DEST_CL                                     (QH_LOG_DEST_STDOUT | QH_LOG_DEST_STDERR)
/** @} */

/**
 * @defgroup blocked_destinations Blocked destinations
 *
 * Log flags that represent a log message destination that is blocked.
 * @{
 */
#define QH_LOG_NO_DEST_STDOUT                                                   UINT64_C(0x00000100)
#define QH_LOG_NO_DEST_STDERR                                                   UINT64_C(0x00000200)
#define QH_LOG_NO_DEST_SLOG                                                     UINT64_C(0x00000400)
#define QH_LOG_NO_DEST_SLOG2                                                    UINT64_C(0x00000800)
/** @} */

/**
 * @defgroup log_to_sterr Log to stderr based on log level
 *
 * @brief These convenience flags combine a log level and the @c stderr destination.
 *
 * @details These flags indicate that an attempt should be made to output log messages with the
 * specified log level to @e stderr. This action is often required when a process does something
 * that should not go unnoticed at startup (e.g., it exits because of a critical error) and it is
 * useful to output a log message to @e stderr. Only the critical, shutdown, error, and warning
 * levels are provided because all other levels are typically not important enough to require a
 * message to go to @e stderr specifically.
 * @{
 */
#define QH_LOG_SHUTDOWN_STDERR                       (QH_LOG_SEVERITY_SHUTDOWN | QH_LOG_DEST_STDERR)
#define QH_LOG_CRITICAL_STDERR                       (QH_LOG_SEVERITY_CRITICAL | QH_LOG_DEST_STDERR)
#define QH_LOG_ERROR_STDERR                             (QH_LOG_SEVERITY_ERROR | QH_LOG_DEST_STDERR)
#define QH_LOG_WARNING_STDERR                         (QH_LOG_SEVERITY_WARNING | QH_LOG_DEST_STDERR)
/** @} */

/**
 * @defgroup log_to_cl Log to stderr or stdout based on log level
 *
 * @brief These convenience flags combine a log level and the @c stdout and @c stderr destinations.
 *
 * @details These flags indicate that an attempt should be made to output log messages with the
 * specified log level to @e stderr or @e stdout. This action is often required when a process does
 * something that should not go unnoticed at startup (e.g., it exits because of a critical error)
 * and it is useful to output a log message to command line outputs.
 * @{
 */
#define QH_LOG_SHUTDOWN_CL                               (QH_LOG_SEVERITY_SHUTDOWN | QH_LOG_DEST_CL)
#define QH_LOG_CRITICAL_CL                               (QH_LOG_SEVERITY_CRITICAL | QH_LOG_DEST_CL)
#define QH_LOG_ERROR_CL                                     (QH_LOG_SEVERITY_ERROR | QH_LOG_DEST_CL)
#define QH_LOG_WARNING_CL                                 (QH_LOG_SEVERITY_WARNING | QH_LOG_DEST_CL)
#define QH_LOG_NOTICE_CL                                   (QH_LOG_SEVERITY_NOTICE | QH_LOG_DEST_CL)
#define QH_LOG_INFO_CL                                       (QH_LOG_SEVERITY_INFO | QH_LOG_DEST_CL)
/** @} */

/**
 * @defgroup log_message_output Log message output
 *
 * Optional flags used in a @e qh_log_*() call that modify the log message output.
 *
 */

/**
 * @ingroup log_message_output
 *
 * Add the thread ID to the end of the log message in square brackets. For example, if the thread
 * ID is 3345, @c [3345] is added.
 *
 */
#define QH_LOG_OPTION_TID                                               UINT64_C(0x0000000100000000)

/**
 * @ingroup log_message_output
 *
 * Exclude the thread ID from the log message.
 *
 */
#define QH_LOG_OPTION_NOTID                                             UINT64_C(0x0000000200000000)

/**
 * @ingroup log_message_output
 *
 * Add location information to the log message.
 *
 */
#define QH_LOG_OPTION_LOC                                               UINT64_C(0x0000000400000000)

/**
 * @ingroup log_message_output
 *
 * Exclude location information from the log message.
 *
 */
#define QH_LOG_OPTION_NOLOC                                             UINT64_C(0x0000000800000000)

/**
 * @ingroup log_message_output
 *
 * Include the context name in the log message. Each log line is prefixed with the context name
 * followed by a colon and a space, and then the log message. (This is the default behavior.)
 *
 */
#define QH_LOG_OPTION_PREFIX                                            UINT64_C(0x0000001000000000)

/**
 * @ingroup log_message_output
 *
 * Exclude the context name from the log message.
 *
 */
#define QH_LOG_OPTION_NOPREFIX                                          UINT64_C(0x0000002000000000)

/**
 * @defgroup severity_masks Severity level masks
 *
 * A set of masks that represent the different sections of the severity level.
 * @{
 */
#define QH_LOG_SEVERITY_MASK                                                    UINT64_C(0x000000FF)
#define QH_LOG_DEST_MASK                                                        UINT64_C(0xFFF00000)
#define QH_LOG_NO_DEST_MASK                                                     UINT64_C(0x000FFF00)
#define QH_LOG_OPTION_MASK                                              UINT64_C(0x0000003F00000000)
#define QH_LOG_RESERVED_MASK                                            UINT64_C(0x000FFFC000000000)
/** @} */

/**
 * @defgroup convert_destinations Flags for converting destinations
 *
 * The size of the shift for converting from @c *_DEST_* defines and masks to @c *_NO_DEST_* ones,
 * and vice versa.
 *
 * @{
 */
#define QH_LOG_DEST_TO_NO_DEST_SHIFT                                                              12
/** @} */

/**
 * @defgroup user_reserved User-reserved area
 *
 * @brief A mask and shift size that represent the area of the flags that is reserved for users.
 *
 * @details Because the logging functions do not look at this area when they log, callers are free
 *          to set anything they like in this area. Having this area allows finer-grained control
 *          over specific types of messages the caller needs.
 * @{
 */
#define QH_LOG_USER_RESERVED_MASK                                       UINT64_C(0xFFF0000000000000)
#define QH_LOG_USER_RESERVED_SHIFT                                                                52
/** @} */

/**
 * @ingroup verbosity_levels
 */
#define QH_LOG_SEVERITY_NONE                                                             UINT64_C(0)
/**
 * @ingroup verbosity_levels
 */
#define QH_LOG_SEVERITY_ALL                                                     QH_LOG_SEVERITY_MASK

/**
 * @defgroup version_numbers Version numbers
 *
 */

/**
 * @ingroup version_numbers
 *
 * Identifier that represents the version number of the first version of the @c qh_log_info_t
 * structure.
 *
 */
#define QH_LOG_INFO_VERSION_1                                                   UINT32_C(0x00010000)

/**
 * @ingroup version_numbers
 *
 * Identifier that represents the version number of the current version of the structure.
 *
 */
#define QH_LOG_INFO_VERSION                                                    QH_LOG_INFO_VERSION_1

/**
 * The opaque context type used by QNX helpers logging functions.
 */
typedef struct qh_log_context_s qh_log_context_t;

/**
 * The information structure used with QNX helpers logging functions.
 */
typedef struct qh_log_info_s {
    /** The version number of this structure.  Always set this to @c QH_LOG_INFO_VERSION. */
    uint32_t version;
    /** The line on which the log message originates. */
    uint32_t line;
    /** The filename where the log message originates. */
    const char *filename;
    /** Whether @e filename contains the full path.*/
    bool short_filename;
    /** The function where the log message originates. */
    const char *function;
    /**
     * The @c QH_LOG_SEVERITY_* identifier for this message.  Can be combined with
     * @c QH_LOG_DEST_* and @c QH_LOG_NO_DEST_* for messages that also need to control destinations.
     */
    uint64_t severity;
    /** The caller's logging context. */
    qh_log_context_t * const *context;
} qh_log_info_t;

/**
 * The default user context unless the user of the log header has already defined one. If the user
 * does not define one, it is set to @c qh_log_user_context_, which refers to the automatically
 * created module's context. This context is used with the logging macros.
 */

#ifdef QH_LOG_NULL_USER_CONTEXT
#if defined(QH_LOG_USER_CONTEXT_NAME) || defined(QH_LOG_USER_CONTEXT_VAR)
#error "QH_LOG_NULL_USER_CONTEXT cannot be used together with QH_LOG_USER_CONTEXT_NAME or " \
        "QH_LOG_USER_CONTEXT_VAR."
#endif
#define QH_LOG_USER_CONTEXT_REF                                                                 NULL
#else
#ifndef QH_LOG_USER_CONTEXT_VAR
#define QH_LOG_USER_CONTEXT_VAR                                                 qh_log_user_context_
#endif
extern qh_log_context_t *QH_LOG_USER_CONTEXT_VAR QH_ATTR_VAR_VISIBILITY("hidden");
#define QH_LOG_USER_CONTEXT_REF                                             &QH_LOG_USER_CONTEXT_VAR
#endif

/**
 * A helper macro used by logging macros to simplify the creation of anonymous log info structures.
 */
#define QH_LOG_INFO_ANON(__severity, __filename, __function, __line) \
        &(qh_log_info_t){ \
            .version = QH_LOG_INFO_VERSION, \
            .line = (__line), \
            .filename = (__filename), \
            .short_filename = QH_FILENAME_HAS_FULLPATH == false, \
            .function = (__function), \
            .severity = (__severity), \
            .context = QH_LOG_USER_CONTEXT_REF, \
        }

/**
 * @brief A macro that logs a message without any associated location information
 *
 * @details This macro is thread safe and guarantees that @e errno is the same when it returns as it
 * was on entry.
 *
 * @c qh_log_errno is set on error.  In order to detect failure, @c qh_log_errno can be set to EOK
 * prior to calling it, and verification can then be done after the call.
 *
 * The @c fmt parameter is omitted from the macro signature to prevent the compile-time warnings
 * that occur when you use the @c -Wpedantic GCC option and there are no variable arguments in the
 * macro.
 *
 * For formatting parameters, see @e printf().
 *
 * @param[in] __severity The @c QH_LOG_SEVERITY_* severity level for this log message. Optionally,
 *                          can be combined with @c QH_LOG_DEST_*, @c QH_LOG_NO_DEST_*, or both when
 *                          specific messages also need to add or block destinations.
 */
#define qh_log_noloc(__severity, ...) \
        qh_log_ex(QH_LOG_INFO_ANON((__severity) | QH_LOG_OPTION_NOLOC, NULL, NULL, UINT32_C(0)), \
                    __VA_ARGS__)

/**
 * @brief A macro that logs a message along with the originating filename and line number
 *
 * @details This macro is thread safe and guarantees that @e errno is the same when it returns as it
 *          was on entry.
 *
 * @c qh_log_errno is set on error.  In order to detect failure, @c qh_log_errno can be set to EOK
 * prior to calling it, and verification can then be done after the call.
 *
 * The @c fmt parameter is omitted from the macro signature to prevent the compile-time warnings
 * that occur when you use the @c -Wpedantic GCC option and there are no variable arguments in the
 * macro.
 *
 * For formatting parameters, see @e printf().
 *
 * @param[in] __severity The @c QH_LOG_SEVERITY_* severity level for this log message. Optionally,
 *                          can be combined with @c QH_LOG_DEST_*, @c QH_LOG_NO_DEST_*, or both when
 *                          specific messages also need to add or block destinations.
 */
#define qh_log(__severity, ...) \
        qh_log_ex(QH_LOG_INFO_ANON((__severity), QH_FILENAME, NULL, __LINE__), __VA_ARGS__)

/**
 * @defgroup message_with_severity Message with severity
 *
 * Convenience logging macros that implicitly specify the logging severity that is normally
 * specified when calling the @e qh_log() or @e qh_log_noloc() macros.
 * @{
 */
#define qh_log_shutdown(...) qh_log(QH_LOG_SEVERITY_SHUTDOWN, __VA_ARGS__)
#define qh_log_critical(...) qh_log(QH_LOG_SEVERITY_CRITICAL, __VA_ARGS__)
#define qh_log_error(...) qh_log(QH_LOG_SEVERITY_ERROR, __VA_ARGS__)
#define qh_log_warning(...) qh_log(QH_LOG_SEVERITY_WARNING, __VA_ARGS__)
#define qh_log_notice(...) qh_log(QH_LOG_SEVERITY_NOTICE, __VA_ARGS__)
#define qh_log_info(...) qh_log(QH_LOG_SEVERITY_INFO, __VA_ARGS__)
#define qh_log_debug1(...) qh_log(QH_LOG_SEVERITY_DEBUG1, __VA_ARGS__)
#define qh_log_debug2(...) qh_log(QH_LOG_SEVERITY_DEBUG2, __VA_ARGS__)

#define qh_log_noloc_shutdown(...) qh_log_noloc(QH_LOG_SEVERITY_SHUTDOWN, __VA_ARGS__)
#define qh_log_noloc_critical(...) qh_log_noloc(QH_LOG_SEVERITY_CRITICAL, __VA_ARGS__)
#define qh_log_noloc_error(...) qh_log_noloc(QH_LOG_SEVERITY_ERROR, __VA_ARGS__)
#define qh_log_noloc_warning(...) qh_log_noloc(QH_LOG_SEVERITY_WARNING, __VA_ARGS__)
#define qh_log_noloc_notice(...) qh_log_noloc(QH_LOG_SEVERITY_NOTICE, __VA_ARGS__)
#define qh_log_noloc_info(...) qh_log_noloc(QH_LOG_SEVERITY_INFO, __VA_ARGS__)
#define qh_log_noloc_debug1(...) qh_log_noloc(QH_LOG_SEVERITY_DEBUG1, __VA_ARGS__)
#define qh_log_noloc_debug2(...) qh_log_noloc(QH_LOG_SEVERITY_DEBUG2, __VA_ARGS__)
/** @} */

/**
 * @brief A macro that logs a message along with the originating filename, function, and line number
 *
 * @details This macro is thread safe and guarantees that @e errno is the same when it returns as it
 * was on entry.
 *
 * @c qh_log_errno is set on error.  In order to detect failure, @c qh_log_errno can be set to EOK
 * prior to calling it, and verification can then be done after the call.
 *
 * The @c fmt parameter is omitted from the macro signature to prevent the compile-time warnings
 * that occur when you use the @c -Wpedantic GCC option and there are no variable arguments in the
 * macro.
 *
 * For formatting parameters, see @e printf().
 *
 * @param[in] __severity The @c QH_LOG_SEVERITY_* severity level for this log message. Optionally,
 *                          can be combined with @c QH_LOG_DEST_*, @c QH_LOG_NO_DEST_*, or both when
 *                          specific messages also need to add or block destinations.
 */
#define qh_log_loc(__severity, ...) \
        qh_log_ex(QH_LOG_INFO_ANON((__severity) | QH_LOG_OPTION_LOC, QH_FILENAME, __func__, __LINE__), \
                    __VA_ARGS__)

/**
 * @brief A macro that logs a debug line trace message along with the originating filename,
 * function, and line number, using the @c QH_LOG_SEVERITY_DEBUG2 severity level
 *
 * This macro can be called with or without a message. Examples:
 * @code qh_log_linetrace(); @endcode
 * @code qh_log_linetrace("extra info"); @endcode
 * @code qh_log_linetrace(extra_info_string); @endcode
 *
 * @c qh_log_errno is set on error.  In order to detect failure, @c qh_log_errno can be set to EOK
 * prior to calling it, and verification can then be done after the call. @c errno is unmodified.
 *
 * The @c fmt parameter is omitted from the macro signature to prevent the compile-time warnings
 * that occur when you use the @c -Wpedantic GCC option and there are no variable arguments in the
 * macro.
 *
 * @param[in] __msg Typically, a short string to insert in the line trace log message. Can be
 *                  omitted if you don't need to add any specific information.
 */
#define qh_log_linetrace(__msg) qh_log_loc(QH_LOG_SEVERITY_DEBUG2, "DBG trace: %s", "" __msg)

/**
 * @brief Thread-local qh log error macro
 *
 * The @c qh_log_errno macro is set to certain error values (the same set @c errno would get) by
 * the qh_log_ex and qh_vlog_ex functions, and by macros making use of these functions.  This
 * is a macro, but you can always examine or set it as if it were a simple @c errno_t variable.
 *
 * Each thread in a multi-threaded program has its own error value in its thread local storage. No
 * matter which thread you're in, you can simply refer to @c qh_log_errno given it's defined in such
 * a way that it refers to the correct variable for the thread.
 */
#define qh_log_errno (*qh_log_get_errno_ptr())

/*
 * Internal use only for the TLS implementation of qh_log_errno.
 */
errno_t * qh_log_get_errno_ptr(void) __attribute__((__const__));

/**
 * @brief Get the string representation of the specified verbosity.
 *
 * @details The @e qh_log_verbosity_to_str() function gets the string representation of the
 *          specified verbosity level (QH_LOG_SEVERITY_*) that would be used for logging
 *          configuration. Values outside the range of valid QH_LOG_SEVERITY_* levels are treated
 *          as if QH_LOG_SEVERITY_ALL was specified.
 *
 * @param[in] __verbosity The @c QH_LOG_SEVERITY_* verbosity level for which to get the string
 *                        representation.
 *
 * @return The string representation of the specified verbosity.
 */
const char * qh_log_verbosity_to_str(uint64_t __verbosity) __attribute__((__const__));

/**
 * @brief Get the verbosity for the specified combination of context and destinations
 *
 * @details The @e qh_log_get_verbosity() function gets the highest level of verbosity available for
 *          the specified context and set of destinations. Specify NULL for @e __context to get the
 *          highest verbosity for the default context.
 *
 * @param[in] __context      The context to get the verbosity for.
 * @param[in] __destinations Logging destination flags.
 *
 * @return The highest verbosity level associated with the destinations.
 */
uint64_t qh_log_get_verbosity(qh_log_context_t * const *__context, uint64_t __destinations);

/**
 * @brief Get the verbosity for the specified combination of named context and destinations
 *
 * @details Gets the highest level of verbosity available for a given set of destinations for
 *          contexts that match the specified name.
 *
 *          For @c context, specify @c all to match all contexts and @c default to return the
 *          verbosity for the default context.
 *
 * @param[in] __context_name The context name to match.
 * @param[in] __destinations The logging destination flags.
 *
 * @return The highest verbosity level associated with the destinations.
 */
uint64_t qh_log_get_verbosity_by_name(const char *__context_name, uint64_t __destinations);

/**
 * @brief Get the destinations a specified context uses
 *
 * @details This function gets the logging destination flags (e.g., @c QH_LOG_DEST_*) for a given
 *          context. Specify NULL for @c __context to get the flags for the default context.
 *
 * @param[in] __context The context to get the destinations for.
 *
 * @return The logging destination flags.
 */
uint64_t qh_log_get_destinations(qh_log_context_t * const *__context);

/**
 * @brief Get logging destinations based on a context name.
 *
 * @details Gets the logging destination flags (e.g., @c QH_LOG_DEST_*) for all contexts that
 *          match the specified name.
 *
 *          For @c __context_name, specify @c all to match all contexts and @c default to return
 *          flags for the default context.
 *
 * @param[in] __context_name The context name to match.
 *
 * @return The logging destination flags.
 */
uint64_t qh_log_get_destinations_by_name(const char *__context_name);

/**
 * @brief Update the logging configuration based on a configuration string
 *
 * @details Logging using QNX helpers is controlled by a configuration string that specifies a
 *          combination of the destination flags, the verbosity of a context, and the
 *          message-specific flags. For a detailed description of this string, see
 *          <a href="manual/control_logging.xml">Controlling QNX helpers logging</a>.
 *
 *          Calling @e qh_log_update_config() has no effect if the configuration has been locked
 *          using a @c QH_LOG_CONFIG_CTX* environment variable.
 *
 * @param[in] __config_str The logging configuration string.
 *
 * @return EOK on success or a standard @e errno on failure (and @e errno is set).
 */
errno_t qh_log_update_config(const char *__config_str);

/**
 * @brief Set the logging configuration to command line mode.
 *
 * @details Unless configured otherwise, the diagnostics logged through QNX helpers go to @c slog2.
 * For command line tools, it is more practical to output diagnostics to @e stderr instead. To make
 * it easier to configure a system to require only the default settings in most situations, call
 * qh_log_set_cl_mode(), which sets the QNX helpers logging configuration to use command line
 * defaults instead of its normal defaults. When this function is called, it rolls back any previous
 * configuration, applies QNX helpers command line defaults, and then applies command line defaults
 * from the following environment variables in this order:
 *
 * - @e QH_LOG_CONFIG_CTX_CL
 * - @e QH_LOG_CONFIG_CTX_CL__<i>progname</i> (@c __progname)
 *
 * The @e QH_LOG_CONFIG_CTX_CL* environment variables have exactly the same format as their @e
 * QH_LOG_CONFIG_CTX* counterparts, and like those environment variables, the configuration can be
 * locked if the environment variables are set. For more information on the format and the locking
 * mechanism, see <a href="manual/control_logging.xml">Controlling QNX
 * helpers logging</a>.
 *
 */
void qh_log_set_cl_mode(void);

/**
 * @brief Check whether a message with the given log information structure is logged.
 *
 * @details Given a message's log information structure, this function determines if it is logged
 *          when it is used in a logging call. This function is useful when a message
 *          is expensive to build because the caller can determine whether to build a message based
 *          on whether it would be logged. To perform this same check based on the severity only,
 *          use @e QH_LOG_CHECK().
 *
 * @param[in] __log_info The log information structure of the log message to check.
 *
 * @return Returns @c true if the message would be logged; otherwise, @c false.
 */
bool qh_log_check(const qh_log_info_t *__log_info);

/**
 * @brief A macro that checks whether a message with the specified severity would be logged.
 *
 * @details Given a message's severity, this function determines if it is logged when it is used in
 *          a logging call. It is simpler to use than @e qh_log_check() because it only requires
 *          a severity parameter. This function is useful when a message is expensive to build
*           because the caller can determine whether to build a message based on whether it would
 *          be logged.
 *
 * @param __severity The @c QH_LOG_SEVERITY_* severity level for this log message. Optionally, can
 *                   be combined with @c QH_LOG_DEST_*, @c QH_LOG_NO_DEST_*, or both when specific
 *                   messages also need to add or block destinations.
 *
 * @return Returns @c true if the message would be logged, and @c false otherwise.
 */
#define QH_LOG_CHECK(__severity) qh_log_check(QH_LOG_INFO_ANON((__severity), NULL, NULL, UINT32_C(0)))

/**
 * @brief Log a formatted message.
 *
 * @details This function logs a formatted message to the set of active destinations. It includes
 *          the severity level set in the log information structure (@c __log_info).
 *
 *          In most cases, call logging is done using the QNX helpers logging macros (which in turn
 *          call @e qh_log_ex()) because they greatly simplify the calls, but you can also use
 *          this function directly.
 *
 *          Although QNX does not recommend it, if it's absolutely necessary, it is safe to call
 *          this function with @c __log_info set to NULL, which specifies the default log
 *          information and context configuration.
 *
 * @note @c qh_log_errno is set on error.  In order to detect failure, @c qh_log_errno can be set to
 *       EOK prior to calling it, and verification can then be done after the call.  In all
 *       circumstances, @c errno is unmodified.
 *
 * @param[in] __log_info The log information structure to use with this log message, or NULL to use
 *                       default values.
 * @param[in] __fmt      A string that specifies the format of the output. The formatting string
 *                       determines the additional arguments you need to provide. For more
 *                       information, see @e printf().
 */
void qh_log_ex(const qh_log_info_t *__log_info, const char *__fmt, ...)
                QH_ATTR_FUNC_FORMAT_PRINTF(2, 3);

/**
 * @brief Log a formatted message using a variable-argument list
 *
 * @details This function logs a formatted message to the set of active destinations. It includes
 *          the severity level set in the log information structure (@c __log_info).
 *
 *          This function is a varargs version of @e qh_log_ex().
 *
 *          In most cases, logging calls are done using the QNX helpers logging macros (which in
 *          turn call @e qh_log_ex()) because they greatly simplify the calls, but you can also use
 *          this function directly.
 *
 *          Although QNX does not recommend it, if it's absolutely necessary, it is safe to call
 *          this function with @c __log_info set to NULL, which specifies the default log
 *          information and context configuration.
 *
 * @note @c qh_log_errno is set on error.  In order to detect failure, @c qh_log_errno can be set to
 *       EOK prior to calling it, and verification can then be done after the call.  In all
 *       circumstances, @c errno is unmodified.
 *
 * @param[in] __log_info The log information structure to use with this log message, or NULL to use
 *                     default values.
 * @param[in] __fmt      A string that specifies the format of the output. The formatting string
 *                     determines the additional arguments you need to provide. For more
 *                     information, see @e vprintf().
 * @param[in] __arglist  A variable-argument list of the additional arguments, which must be
 *                     initialized with the @e va_start() macro.
 */
void qh_vlog_ex(const qh_log_info_t *__log_info, const char *__fmt, va_list __arglist)
                QH_ATTR_FUNC_FORMAT_PRINTF(2, 0);

/**
 * @brief Create a logging context
 *
 * The qh_log_context_create() function creates a logging context with a given name for use with the
 * QNX helpers logging interface.  The context name is used as a prefix when the context is used for
 * logging and to match the context when it is specified by name in the API.
 *
 * Normally, applications and libraries do not call this function directly. Instead, they use
 * the QH_LOG_DEFAULT_CONTEXT_INIT() macro and define @c QH_LOG_USER_CONTEXT_NAME to hold the
 * context name. For more information, see <a href="manual/set_up_logging.xml">Setting up QNX
 * helpers logging</a>.
 *
 * Although it is suboptimal, calling this function more than once with the same context pointer is
 * allowed, but if a context at that address exists already, the name in the second call is ignored.
 *
 * @param[in]  __name    The name of the context to create.
 * @param[out] __context The location where the context can be stored.
 *
 * @return EOK on success or a standard @e errno on failure (and @e errno is set).
 *
 */
errno_t qh_log_context_create(const char *__name, qh_log_context_t **__context);

/**
 * @brief Normalize a context name.
 *
 * @details This function normalizes a context name in preparation for context creation (it converts
 * it the same way as @e qh_log_context_create() does), or gets the name that the creation process
 * used, given the provided context name.
 *
 * The conversion process happens in-place, replacing the passed-in buffer with the normalized
 * version of the name.
 *
 * @param[in,out] __context_name The name of the context to convert on input, and the converted name
 *                             on output. If the @c context_name is NULL or has zero length, an
 *                             error is returned.
 *
 * @return EOK on success or a standard @e errno on failure (and @e errno is set).
 *
 */
errno_t qh_log_context_normalize_name(char *__context_name);

/**
 * @brief Destroys a logging context.
 *
 * @details Destroys a logging context previously created with @e qh_log_context_create().
 *
 * Applications and libraries do not normally call this function directly, as it would
 * automatically be handled by the @e QH_LOG_DEFAULT_CONTEXT_INIT() macro.

 * Although it is suboptimal, calling this function more than once with the same context pointer or
 * with a NULL context pointer is allowed.
 *
 * @param[in] __context The location of the context. A NULL value has no effect.
 *
 * @e errno is unmodified.
 *
 */
void qh_log_context_destroy(qh_log_context_t **__context);

/*
 * Internal use only.
 */
void qh_log_context_create_or_abort(const char *__name,
                                    qh_log_context_t **__context,
                                    const char *__filename,
                                    const char *__funcname,
                                    uint32_t __line);

/*
 * Internal use only.
 */
#define QH_LOG_CONTEXT_INIT(qh_log_ctx_name__, qh_log_ctx_var__, qh_log_ctx_var_name__) \
        qh_log_context_t *qh_log_ctx_var__; \
        static void qh_log_context_init_##qh_log_ctx_var_name__##_(void) \
                                                        QH_ATTR_FUNC_CONSTRUCTOR_PRIORITY(115); \
        static void qh_log_context_fini_##qh_log_ctx_var_name__##_(void) \
                                                        QH_ATTR_FUNC_DESTRUCTOR_PRIORITY(115); \
        static void qh_log_context_init_##qh_log_ctx_var_name__##_(void) \
        { \
            qh_log_context_create_or_abort((qh_log_ctx_name__), &qh_log_ctx_var__, \
                                            QH_FILENAME, __func__, __LINE__); \
        } \
        static void qh_log_context_fini_##qh_log_ctx_var_name__##_(void) \
        { \
            qh_log_context_destroy(&qh_log_ctx_var__); \
        }

#ifdef QH_LOG_USER_CONTEXT_NAME
#define QH_LOG_DEFAULT_CONTEXT_INIT() \
        QH_LOG_CONTEXT_INIT(QH_LOG_USER_CONTEXT_NAME, QH_LOG_USER_CONTEXT_VAR, QH_LOG_USER_CONTEXT_VAR)
#else
#define QH_LOG_DEFAULT_CONTEXT_INIT() \
        _Static_assert(false, "QH_LOG_USER_CONTEXT_NAME must be defined in order to use " \
                        "QH_LOG_DEFAULT_CONTEXT_INIT");
#endif

/** @cond */
__END_DECLS
/** @endcond */

#endif /* QNX_QH_LOG_H_INCLUDED */
