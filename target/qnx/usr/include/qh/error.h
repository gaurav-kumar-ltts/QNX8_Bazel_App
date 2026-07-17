/*
 * $QNXLicenseC:
 * Copyright 2017-2021, QNX Software Systems.  All Rights Reserved.
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

#ifndef QNX_QH_ERROR_H_INCLUDED
#define QNX_QH_ERROR_H_INCLUDED

/**
 * @file error.h
 *
 * QNX helpers - Helpers related to the @e errno variable.
 */

/* sorted headers from this project */
#ifndef QNX_QH_LOG_H_INCLUDED
#include "qh/log.h"
#endif

/* sorted library headers */

/* sorted system headers */

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * @brief A macro that sets @e errno.
 *
 * @details Because what is passed in to the macro is only evaluated once, it is safe to execute
 * operations as part of calling the macro.
 *
 * @param[in] __errval The standard @e errno to set @e errno to.
 */
#define QH_SET_ERRNO(__errval) (errno = (__errval))

/**
 *
 * @brief A macro that sets @e errno and returns its value.
 *
 * @details Because this is a macro that calls return, the invoking function actually returns when
 * the macro is executed. The invoking function is expected to have an @c int as its return type.
 *
 * Because what is passed in to the macro is only evaluated once, it is safe to execute operations
 * as part of calling the macro.
 *
 * @param[in] __errval The standard @e errno to set @e errno to and then return with.
 */
#define QH_RET_ERRNO(__errval) return qh_set_errno(__errval)

/**
 *
 * @brief A macro that conditionally sets @e errno and always returns the specified error.
 *
 * @details If the @e errno passed in is not EOK, @e errno is set to it, and then the pre-evaluated
 * value of @e errno is returned.  If @e errno evaluates to EOK, @e errno is not set, but EOK is
 * returned.
 *
 * Because this is a macro that calls return, the invoking function actually returns when the
 * macro is executed. The invoking function is expected to have an @c int as its return type.
 *
 * Because what is passed in to the macro is only evaluated once, it is safe to execute operations
 * as part of calling the macro.
 *
 * @param[in] __errval The standard @e errno to set @e errno to (if not EOK) and then return with.
 */
#define QH_RET_ERRNO_WEOK(__errval) return qh_set_errno_on_error(__errval)

/**
 * @brief A macro that conditionally (if not EOK) sets @e errno and returns the specified error.
 *
 * @details If the @e errno passed in is not EOK, @e errno is set to it, and then the pre-evaluated
 * value of @e errno is returned.  If @e errno evaluates to EOK, @e errno is not set and the macro
 * does not call return.
 *
 * Because this is a macro that conditionally calls return, the invoking function may actually
 * return when the macro is executed. The invoking function is expected to have an @c int as its
 * return type.
 *
 * Because what is passed in to the macro is only evaluated once, it is safe to execute operations
 * as part of calling the macro.
 *
 * @param[in] __errval The standard @e errno to set @e errno to (if not EOK) and then return with.
 */
#define QH_RET_ON_ERRNO(__errval) \
        do { \
            const errno_t qh_ret_on_errno_errno__ = qh_set_errno_on_error(__errval); \
            if (qh_ret_on_errno_errno__ != EOK) { \
                return qh_ret_on_errno_errno__; \
            } \
        } while ((bool)false)

/**
 * @brief A convenience macro that allows you to call @e qh_abort_on_errno() without specifying @e
 *        __qh_log_info.
 *
 * @details This macro defines for the caller the @c qh_log_info_t structure that you use with @e
 *          qh_abort_on_errno() with a few default parameters. These parameters make the log message
 *          show the originating location of the abort call in case of failure.
 *
 * @param[in] __errval    The standard @e errno to validate (and log, in case of failure). Passing a
 *                        value smaller than 0 (EOK) logs an error without details about the errno
 *                        and aborts.
 * @param[in] __err_msg     The message to log prior to aborting, in case of failure.
 *
 */
#define QH_ABORT_ON_ERRNO(__errval, __err_msg) \
        qh_abort_on_errno(QH_LOG_INFO_ANON(QH_LOG_CRITICAL, QH_FILENAME, __func__, __LINE__), \
                            (__errval), (__err_msg))

/**
 * @brief Conditionally log an error message using QNX helpers logging functions and then call @e
 *        abort() if the specified @e errno is not EOK.
 *
 * @details If the @e errno specified by @e __errval is not EOK, this function logs an error message
 *          and then calls @e abort(). If @e __errval is EOK, the function does nothing.
 *
 * @param[in] __qh_log_info The logging information for the abort message.
 * @param[in] __errval    The standard @e errno to validate (and log, in case of failure). Passing a
 *                        value smaller than 0 (EOK) logs an error without details about the @e
 *                        errno and aborts.
 * @param[in] __err_msg     The message to log before aborting, in case of failure.
 *
 * @return None
 */
void qh_abort_on_errno(const qh_log_info_t *__qh_log_info, int __errval, const char *__err_msg);

/**
 * @brief Convenience macro that logs an error message using a QNX helpers function and then calls
 *        @e abort().
 *
 * @details For parameters, see @e printf().
 */
#define QH_ABORT(...) \
        do { \
            qh_log_ex(QH_LOG_INFO_ANON(QH_LOG_CRITICAL, QH_FILENAME, __func__, __LINE__), \
                        __VA_ARGS__); \
            abort(); \
        } while ((bool)false)

/**
 * @brief Store a new error code as a variable if the new error is not zero and the previously
 *        stored one is.
 *
 * @details This function allows a caller to make successive calls with a @c sticky_error variable
 *          and a new, potentially different error. After the caller makes successive calls to the
 *          this function, it can look at the value of @e __sticky_error to determine what the first
 *          error was, if any.
 *
 *          In addition to standard error numbers (e.g., @e errno), this function can be used with
 *          any set of error codes that consider zero to indicate success (e.g., many enumerated
            types).
 *
 * @param[in,out] __sticky_error The location in which to store the first error code encountered in
 *                               successive calls to the function.
 * @param[in]     __new_error    The new error code to use, if @e __sticky_error is 0.
 *
 * @return The value of @e __new_error.
 */
int qh_sticky_error(int *__sticky_error, int __new_error);

/**
 * @brief Store a new error code as a variable if the new error is not zero.
 *
 * @details This function allows a caller to make successive calls with a @c sticky_error variable
 *          and a new, potentially different error. After the caller makes successive calls to the
 *          this function, it can look at the value of @e __sticky_error to determine what the last
 *          error was, if any.
 *
 * @param[in,out] __sticky_error The location in which to store the last error code encountered in
 *                             successive calls to the function.
 * @param[in]     __new_error    The new error code to use, if not 0.
 *
 * @return The value of <tt>__new_error</tt>.
 */
int qh_sticky_error_last(int *__sticky_error, int __new_error);

/**
 * @brief Convert an error number into an error message and guarantee that @e errno is kept intact
 *        in the process.
 *
 * @details This function simply makes use of @e strerror(), but guarantees that @e errno is the
 *          same on the way out of the function as it was on the way in.
 *
 *          Do not modify the returned string.
 *
 * @param[in] __errval The error number that you want the message for.
 *
 * @return A pointer to the error message.
 */
const char * qh_strerror(int __errval);

/**
 * @brief Set @e errno.
 *
 * @details This function sets @e errno to the error value specified by @e __errval and returns the
 *          value of @e __errval.
 *
 * @param[in] __errval The standard @e errno to set @e errno to.
 *
 * @return The value of @e __errval.
 */
static inline errno_t
qh_set_errno(const errno_t __errval)
{
    errno = __errval;
    return __errval;
}

/**
 * @brief Conditionally set @e errno.
 *
 * @details This function sets @e errno to the error value specified by @e __errval if it is not EOK
 *          and returns the value of @e __errval.
 *
 * @param[in] __errval The standard @e errno to set @e errno to if not EOK.
 *
 * @return The value of @e __errval.
 */
static inline errno_t
qh_set_errno_on_error(const errno_t __errval)
{
    if (__errval != EOK) {
        errno = __errval;
    }

    return __errval;
}

/** @cond */
__END_DECLS
/** @endcond */

#endif /* QNX_QH_ERROR_H_INCLUDED */
