/*
 * $QNXLicenseC:
 * Copyright 2019-2021, QNX Software Systems.  All Rights Reserved.
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

#ifndef QNX_QH_MISC_H_INCLUDED
#define QNX_QH_MISC_H_INCLUDED

/**
 * @file misc.h
 * QNX helpers - Miscellaneous helpers.
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

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * @defgroup qh_unused QH_UNUSED
 *
 * Convenience macro that marks a variable as unused to prevent compiler warnings.
 * @{
 */
#define QH_UNUSED(__unused) ((void)(__unused))
/** @} */

/**
 * @defgroup qh_array_length QH_ARRAY_LENGTH
 *
 * Convenience macro that determines the length (number of elements) of an array.
 * @{
 */
#define QH_ARRAY_LENGTH(__arr) (sizeof(__arr) / sizeof((__arr)[0]))
/** @} */

/**
 * Return whether a @c uint8_t value is a power of two
 *
 * @return Returns @c true if the value is a power of two; otherwise, @c false.
 */
static inline bool
qh_is_pwr_of_2_u8(const uint8_t val__)
{
    return ((val__ & (val__ - (uint8_t)1)) == 0u) && (val__ != 0u);
}

/**
 * Return whether a @c uint16_t value is a power of two
 *
 * @return Returns @c true if the value is a power of two; otherwise, @c false.
 */
static inline bool
qh_is_pwr_of_2_u16(const uint16_t val__)
{
    return ((val__ & (val__ - (uint16_t)1)) == 0u) && (val__ != 0u);
}

/**
 * Return whether a @c uint32_t value is a power of two
 *
 * @return Returns @c true if the value is a power of two; otherwise, @c false.
 */
static inline bool
qh_is_pwr_of_2_u32(const uint32_t val__)
{
    return ((val__ & (val__ - (uint32_t)1)) == 0u) && (val__ != 0u);
}

/**
 * Return whether a @c uint64_t value is a power of two
 *
 * @return Returns @c true if the value is a power of two; otherwise, @c false.
 */
static inline bool
qh_is_pwr_of_2_u64(const uint64_t val__)
{
    return ((val__ & (val__ - (uint64_t)1)) == 0u) && (val__ != 0u);
}

/**
 * Return whether the absolute value of an @c int8_t value is a power of two
 *
 * @return Returns @c true if the absolute value is a power of two; otherwise, @c false.
 */
static inline bool
qh_is_pwr_of_2_s8(const int8_t val__)
{
    const uint8_t uval__ = (val__ >= 0) ? (uint8_t)val__ : (uint8_t)(-val__);
    return ((uval__ & (uval__ - (uint8_t)1)) == 0u) && (uval__ != 0u);
}

/**
 * Return whether the absolute value of an @c int16_t value is a power of two
 *
 * @return Returns @c true if the absolute value is a power of two; otherwise, @c false.
 */
static inline bool
qh_is_pwr_of_2_s16(const int16_t val__)
{
    const uint16_t uval__ = (val__ >= 0) ? (uint16_t)val__ : (uint16_t)(-val__);
    return ((uval__ & (uval__ - (uint16_t)1)) == 0u) && (uval__ != 0u);
}

/**
 * Return whether the absolute value of an @c int32_t value is a power of two
 *
 * @return Returns @c true if the absolute value is a power of two; otherwise, @c false.
 */
static inline bool
qh_is_pwr_of_2_s32(const int32_t val__)
{
    const uint32_t uval__ = (val__ >= 0) ? (uint32_t)val__ : (uint32_t)(-val__);
    return ((uval__ & (uval__ - (uint32_t)1)) == 0u) && (uval__ != 0u);
}

/**
 * Return whether the absolute value of an @c int64_t value is a power of two
 *
 * @return Returns @c true if the absolute value is a power of two; otherwise, @c false.
 */
static inline bool
qh_is_pwr_of_2_s64(const int64_t val__)
{
    const uint64_t uval__ = (val__ >= 0) ? (uint64_t)val__ : (uint64_t)(-val__);
    return ((uval__ & (uval__ - (uint64_t)1)) == 0u) && (uval__ != 0u);
}

/**
 * Return the currently running program name without the path.
 *
 * @return A pointer to a @c const string containing the current program's name.
 */
const char *qh_get_progname(void);

/** @cond */
__END_DECLS
/** @endcond */

#endif /* QNX_QH_MISC_H_INCLUDED */
