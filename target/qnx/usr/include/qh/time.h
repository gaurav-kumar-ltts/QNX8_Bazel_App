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

#ifndef QNX_QH_TIME_H_INCLUDED
#define QNX_QH_TIME_H_INCLUDED

/**
 * @file time.h
 *
 * QNX helpers - Helpers related to time.
 */

/* sorted headers from this project */
#ifndef QNX_QH_QH_H_INCLUDED
#include "qh/qh.h"
#endif

/* sorted library headers */

/* sorted system headers */
#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif

#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

#ifndef _TIME_H_INCLUDED
#include <time.h>
#endif

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * @defgroup sleep_absolute Sleep time and absolute time
 *
 */

/**
 * @ingroup sleep_absolute
 *
 * Identifier that represents an unlimited sleep time.
 *
 */
#define QH_SLEEP_TIME_FOREVER                                                 ((uint64_t)UINT64_MAX)

/**
 * @ingroup sleep_absolute
 *
 * Identifier that represents infinity as an absolute time.
 *
 */
#define QH_ABSOLUTE_TIME_INFINITY                                             ((uint64_t)UINT64_MAX)

/**
 * @defgroup unit_conversion Unit conversion definitions
 *
 * All these definitions are in @c uint64_t.
 *
 * @{
 */
#define QH_NS_PER_US                                                                  UINT64_C(1000)

#define QH_US_PER_MS                                                                  UINT64_C(1000)
#define QH_NS_PER_MS                                                   (QH_US_PER_MS * QH_NS_PER_US)

#define QH_MS_PER_S                                                                   UINT64_C(1000)
#define QH_US_PER_S                                                     (QH_MS_PER_S * QH_US_PER_MS)
#define QH_NS_PER_S                                                     (QH_US_PER_S * QH_NS_PER_US)

#define QH_S_PER_MIN                                                                    UINT64_C(60)
#define QH_MS_PER_MIN                                                   (QH_S_PER_MIN * QH_MS_PER_S)
#define QH_US_PER_MIN                                                 (QH_MS_PER_MIN * QH_US_PER_MS)
#define QH_NS_PER_MIN                                                 (QH_US_PER_MIN * QH_NS_PER_US)

#define QH_MINS_PER_HOUR                                                                UINT64_C(60)
#define QH_S_PER_HOUR                                              (QH_MINS_PER_HOUR * QH_S_PER_MIN)
#define QH_MS_PER_HOUR                                                 (QH_S_PER_HOUR * QH_MS_PER_S)
#define QH_US_PER_HOUR                                               (QH_MS_PER_HOUR * QH_US_PER_MS)
#define QH_NS_PER_HOUR                                               (QH_US_PER_HOUR * QH_NS_PER_US)

#define QH_HOURS_PER_DAY                                                                UINT64_C(24)
#define QH_MINS_PER_DAY                                        (QH_HOURS_PER_DAY * QH_MINS_PER_HOUR)
#define QH_S_PER_DAY                                                (QH_MINS_PER_DAY * QH_S_PER_MIN)
#define QH_MS_PER_DAY                                                   (QH_S_PER_DAY * QH_MS_PER_S)
#define QH_US_PER_DAY                                                 (QH_MS_PER_DAY * QH_US_PER_MS)
#define QH_NS_PER_DAY                                                 (QH_US_PER_DAY * QH_NS_PER_US)

#define QH_DAYS_PER_WEEK                                                                 UINT64_C(7)
#define QH_HOURS_PER_WEEK                                      (QH_DAYS_PER_WEEK * QH_HOURS_PER_DAY)
#define QH_MINS_PER_WEEK                                      (QH_HOURS_PER_WEEK * QH_MINS_PER_HOUR)
#define QH_S_PER_WEEK                                              (QH_MINS_PER_WEEK * QH_S_PER_MIN)
#define QH_MS_PER_WEEK                                                 (QH_S_PER_WEEK * QH_MS_PER_S)
#define QH_US_PER_WEEK                                               (QH_MS_PER_WEEK * QH_US_PER_MS)
#define QH_NS_PER_WEEK                                               (QH_US_PER_WEEK * QH_NS_PER_US)
/** @} */

#ifdef QH_HAS_SUPPORT_TIME_FUNC

/**
 * Prototype for a callback function that provides the results of a poll check.
 *
 * @param[in]  __cb_data          The callback data provided in the @e __cb_data parameter to
 *                                @e qh_poll_until().
 * @param[out] __continue_polling Tells @e qh_poll_until() whether to continue polling.
 *
 * @returns EOK on success, which indicates that the poll executed correctly. The @e
 *          __continue_polling value determines whether polling continues or not.
 *          On failure, returns a standard  @e errno ( @e errno is also set), which is used as-is as
 *          the return value of @e qh_poll_until(). Polling stops and @e qh_poll_until() returns
 *          EOK to the caller.
 *
 */
typedef int qh_poll_check_cb_ft(void *__cb_data, bool *__continue_polling);

/**
 * Gets the (adjusted) time from the clock with the specified ID, in nanoseconds.
 *
 * @param[in] __clock_id          The ID of the clock to get the time from.
 * @param[in] __forward_offset_ns The number of nanoseconds by which to adjust the time forward.
 *
 * @return The time from the clock specified by @e __clock_id in nanoseconds, or zero if an error
 *         occurs ( @e errno is set).
 */
uint64_t qh_get_nstime(clockid_t __clock_id, uint64_t __forward_offset_ns);

/**
 * @brief Sleep for a specified amount of time, trying not to exceed a specified absolute time.
 *
 * @details Sleep is governed by the clock specified by @e __clock_id.
 *
 * @param[in] __sleep_time_ns        The amount of time to sleep for, in nanoseconds. Set to 0 to
 *                                 return right away, with EOK, ETIME or a standard  @e errno
 *                                 value.
 * @param[in] __clock_id             The ID of the clock to use for the operation.
 * @param[in] __max_absolute_time_ns The maximum absolute time (in nanoseconds) at which sleeping
 *                                   should stop when @e __sleep_time_ns exceeds it (the sleep time
 *                                   is shortened). This time is based on the clock specified by @c
 *                                   __clock_id.
 *
 * @return EOK, ETIME, or a standard  @e errno on failure. The  @e errno variable is set if the return
 *         value is not EOK.
 *
 * @retval EOK If the function slept for the amount of time specified by @e __sleep_time_ns and has
 *         not reached the specified absolute time.
 * @retval ETIME If the time specified by @e __max_absolute_time_ns has passed. The function may or
 *         may not have slept before it returns.
 */
int qh_nssleep(uint64_t __sleep_time_ns, clockid_t __clock_id, uint64_t __max_absolute_time_ns);

/**
 * @brief Call the specified poll check function at a specified interval.
 *
 * @details This function calls the poll check function specified by @e __poll_check_f at intervals
 *          specified in nanoseconds by @e __poll_interval_ns until either a maximum absolute time
 *          has been reached or the poll check function tells it to stop polling. Sleeping between
 *          the poll check calls and evaluating the maximum absolute time is done
 *          using the clock specified by @e __clock_id.
 *
 * @param[in] __poll_interval_ns     The amount of time (in nanoseconds) between the poll check
 *                                   calls.
 * @param[in] __clock_id             The ID of the clock to use for the operation.
 * @param[in] __max_absolute_time_ns The maximum absolute time (in nanoseconds) at which polling
 *                                   should stop, based on the clock specified by @e __clock_id.
 * @param[in] __poll_check_f         The poll function used to determine if polling should continue
 *                                   or not.
 * @param[in] __cb_data              The callback data provided to the @e __cb_data parameter of
 *                                   @e __poll_check_f.
 *
 * @return EOK, ETIME, or a standard  @e errno on failure.  @e errno is set if the return value is not
 *         EOK.
 *
 * @retval EOK If the function slept for the amount of time specified by @e __sleep_time_ns and has
 *         not reached the specified absolute time.
 * @retval ETIME If the time specified by @e __max_absolute_time_ns has passed. The function may or
 *         may not have slept before returning.
 *
 */
int qh_poll_until(uint64_t __poll_interval_ns,
                    clockid_t __clock_id,
                    uint64_t __max_absolute_time_ns,
                    qh_poll_check_cb_ft __poll_check_f,
                    void *__cb_data);

#endif /* QH_HAS_SUPPORT_TIME_FUNC */

/** @cond */
__END_DECLS
/** @endcond */

#endif /* QNX_QH_TIME_H_INCLUDED */
