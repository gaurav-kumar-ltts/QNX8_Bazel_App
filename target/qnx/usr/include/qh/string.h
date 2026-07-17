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

#ifndef QNX_QH_STRING_H_INCLUDED
#define QNX_QH_STRING_H_INCLUDED

/**
 * @file string.h
 * QNX helpers - Helpers related to strings and string conversions.
 */

/* sorted headers from this project */
#ifndef QNX_QH_ATTR_H_INCLUDED
#include "qh/attr.h"
#endif

/* sorted library headers */

/* sorted system headers */
#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif

#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * @defgroup qh_str_stringify QH_STR_STRINGIFY
 *
 * A macro that makes a string from the passed-in argument name.
 * @{
 */
#define QH_STR_STRINGIFY(__ARG) #__ARG
/** @} */

/**
 * @defgroup qh_str_expanded_stringify QH_STR_EXPANDED_STRINGIFY
 *
 * A macro that makes a string from the passed-in argument's value.
 * @{
 */
#define QH_STR_EXPANDED_STRINGIFY(__ARG) QH_STR_STRINGIFY(__ARG)
/** @} */

/**
 * @brief Print formatted output into a newly allocated string.
 *
 * @details It is the responsibility of the caller to free the returned string (using @e free()).
 *
 * @param[in] fmt A string that specifies the format of the output. The formatting string determines
 *                the additional arguments you need to provide. For more information, see @e printf().
 *
 * @return A pointer to the newly allocated and formatted string, or NULL if an error occurred
 *         (@e errno is set).
 */
char * qh_malloc_sprintf(const char *fmt, ...) QH_ATTR_FUNC_FORMAT_PRINTF(1, 2);

/**
 * @brief Return a specified string, a fallback string if the specified string is NULL, or an empty
 * string if the fallback string is also NULL.
 *
 * @details The qh_str() function always returns a non-NULL string.
 *
 * @param[in] __str          The string to be returned, if non-NULL.
 * @param[in] __fallback_str The string to be returned, if non-NULL and @e str is NULL.
 *
 * @return A non-NULL string (@e str or @e fallback_str value, or an empty string).
 */
const char * qh_str(const char *__str, const char *__fallback_str) __attribute__((__const__));

/**
 * @brief Safely create a duplicate of a string.
 *
 * @details The @e qh_strdup() function creates a duplicate of the string pointed to by @e __str (or
 * pointed to by @e __fallback_str if @e __str is NULL) and returns a pointer to the new copy. If both
 * @e __str and @e __fallback_str are NULL, it returns NULL and sets @e errno to EINVAL.
 *
 * @param[in] __str          The string to duplicate, if non-NULL.
 * @param[in] __fallback_str The string to duplicate if non-NULL and @e str is NULL.
 *
 * @return A pointer to a copy of a non-NULL (either @e __str or @e __fallback_str), or NULL if both
 *         @e __str or @e __fallback_str were NULL. When returning NULL, @e errno is always set,
 *         either to EINVAL if both strings were NULL, or to a standard @e errno if an error
 *         occurred while creating the duplicate string.
 */
char * qh_strdup(const char *__str, const char *__fallback_str) QH_ATTR_FUNC_MALLOC;

/**
 * @brief Safely compare two strings.
 *
 * @details The @e qh_strcmp() function compares the string that @e __str1 points to the one that @e
 *          __str2 points to. A NULL argument is valid and compares as smaller to a non-NULL string
 *          and as equal to another NULL string.
 *
 * @param[in] __str1 The first string to compare, or NULL.
 * @param[in] __str2 The second string to compare, or NULL.
 *
 * @return
 * - @c -2 if @e __str1 is NULL and @e __str2 is not
 * - @c 2 if @e __str2 is NULL and @e __str1 is not
 * - If @e __str1 and @e __str2 are not NULL:
 *             - < @c 0 if @e __str1 is less than @e __str2
 *             - @c 0 if @e __str1 is equal to @e __str2
 *             - > @c 0 if @e __str1 is greater than @e __str2
 */
int qh_strcmp(const char *__str1, const char *__str2) __attribute__((__pure__));

/**
 * @brief Set the memory to zero.
 *
 * @details The @e qh_memclear() function clears the memory, setting it to zero, while bypassing any
 *          possible compiler optimizations that could otherwise prevent the memory from being
 *          cleared.
 *
 * @param[out] __dst The destination buffer to clear.
 * @param[in] __size The size of the destination buffer to clear.
 */
static inline void qh_memclear(void *__dst, size_t __size) QH_ATTR_FUNC_NONNULL_PARAMS(1);
static inline void
qh_memclear(void * const __dst, const size_t __size)
{
    (void)memset_s(__dst, __size, 0, __size);
}

/**
 * Safely converts a string into an @c int8_t.
 *
 * This function is similar to @e strtoll(), but does more error checking on the result of the
 * conversion and ensures that the result fits in an @c int8_t. This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_int8() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().
 *
 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for @c ERANGE).
 * @retval ERANGE The number value is either smaller than @c INT8_MIN (and @c INT8_MIN is returned)
 *         or larger than @c INT8_MAX (and @c INT8_MAX is returned).
 */
int qh_str_to_int8(const char *__str, int __base, int8_t *__number, size_t *__end_offset);

/**
 * Safely converts a string into an @c int16_t.
 *
 * This function is similar to @e strtoll(), but does more error checking on the result of the
 * conversion and ensures that the result fits in an @c int16_t. This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_int16() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().
 *
 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is either smaller than @c INT16_MIN (and @c INT16_MIN is returned)
 *         or larger than @c INT16_MAX (and @c INT16_MAX is returned).
 */
int qh_str_to_int16(const char *__str, int __base, int16_t *__number, size_t *__end_offset);

/**
 * Safely converts a string into an @c int32_t.
 *
 * This function is similar to @e strtoll(), but does more error checking on the result of the
 * conversion and ensures that the result fits in an @c int32_t. This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_int32() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().
 *
 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is either smaller than @c INT32_MIN (and @c INT32_MIN is returned)
 *         or larger than @c INT32_MAX (and @c INT32_MAX is returned).
 */
int qh_str_to_int32(const char *__str, int __base, int32_t *__number, size_t *__end_offset);

/**
 * Safely converts a string into an @c int64_t.
 *
 * This function is similar to @e strtoll(), but does more error checking on the result of the
 * conversion and ensures that the result fits in an @c int64_t.  This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_int64() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().
 *
 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is either smaller than @c INT64_MIN (and @c INT64_MIN is returned)
 *         or larger than @c INT64_MAX (and @c INT64_MAX is returned).
 */
int qh_str_to_int64(const char *__str, int __base, int64_t *__number, size_t *__end_offset);

/**
 * Safely converts a string into an @c int.
 *
 * This function is similar to @e strtoll(), but does more error checking on the result of the
 * conversion and ensures that the result fits in an @c int.  This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_int() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().
 *
 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is either smaller than @c INT_MIN (and @c INT_MIN is returned)
 *         or larger than @c INT_MAX (and @c INT_MAX is returned).
 */
int qh_str_to_int(const char *__str, int __base, int *__number, size_t *__end_offset);

/**
 * Safely converts a string into a @c ssize_t.
 *
 * This function is similar to @e strtoll(), but does more error checking on the result of the
 * conversion and ensures that the result fits in a @c ssize_t.  This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_ssize() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().
 *
 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number
 *         isn't updated except for ERANGE).
 * @retval ERANGE The number value is either smaller than the min value of ssize_t (and the min
 *         value is returned) or larger than @c SSIZE_MAX (and @c SSIZE_MAX is returned).
 */
int qh_str_to_ssize(const char *__str, int __base, ssize_t *__number, size_t *__end_offset);

/**
 * Safely converts a string into a @c char.
 *
 * This function is similar to @e strtoll(), but does more error checking on the result of the
 * conversion and ensures that the result fits in a @c char.  This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_char() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().
 *
 * Depending on target architecture, char may be signed or unsigned. A check is done based
 * on CHAR_MIN to determine which conversion must be made.
 *
 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is either smaller than @c CHAR_MIN (and @c CHAR_MIN is returned)
 *         or larger than @c CHAR_MAX (and @c CHAR_MAX is returned).
 */
int qh_str_to_char(const char *__str, int __base, char *__number, size_t *__end_offset);

/**
 * Safely converts a string into a @c signed @c char.
 *
 * This function is similar to @e strtoll(), but does more error checking on the result of the
 * conversion and ensures that the result fits in a @c signed @c char.  This simplifies the work the
 * caller is required to do, which is only to validate that the return value from
 * @e qh_str_to_schar() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().
 *
 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is either smaller than @c SCHAR_MIN (and @c SCHAR_MIN is returned)
 *         or larger than @c SCHAR_MAX (and @c SCHAR_MAX is returned).
 */
int qh_str_to_schar(const char *__str, int __base, signed char *__number, size_t *__end_offset);

/**
 * Safely converts a string into a @c long.
 *
 * This function is similar to @e strtoll(), but does more error checking on the result of the
 * conversion and ensures that the result fits in a @c long.  This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_long() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().
 *
 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is either smaller than @c LONG_MIN (and @c LONG_MIN is returned)
 *         or larger than @c LONG_MAX (and @c LONG_MAX is returned).
 */
int qh_str_to_long(const char *__str, int __base, long *__number, size_t *__end_offset);

/**
 * Safely converts a string into a @c long @c long.
 *
 * This function is similar to @e strtoll(), but does more error checking on the result of the
 * conversion and ensures that the result fits in a @c long @c long.  This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_llong() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().
 *
 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is either smaller than @c LLONG_MIN (and @c LLONG_MIN is returned)
 *         or larger than @c LLONG_MAX (and @c LLONG_MAX is returned).
 */
int qh_str_to_llong(const char *__str, int __base, long long *__number, size_t *__end_offset);

/**
 * Safely converts a string into a @c uint8_t
 *
 * This function is similar to @e strtoull(), but does more error checking on the result of the
 * conversion and ensures that the result fits in a @c uint8_t. This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_uint8() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().

 * For more information on using this function, see the documentation for @e strtoull().
 *
 * Unlike @e strtoull(), this function does not accept a negative sign.
 *
 * @param[in]  __str        The string to convert into a number.
 * @param[in]  __base       The base of the number to parse.
 * @param[out] __number     Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is larger than @c UINT8_MAX and @c UINT8_MAX is returned.
 */
int qh_str_to_uint8(const char *__str, int __base, uint8_t *__number, size_t *__end_offset);

/**
 * Safely converts a string into a @c uint16_t
 *
 * This function is similar to @e strtoull(), but does more error checking on the result of the
 * conversion and ensures that the result fits in a @c uint16_t. This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_uint16() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().

 * For more information on using this function, see the documentation for @e strtoull().
 *
 * Unlike @e strtoull(), this function does not accept a negative sign.
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is larger than @c UINT16_MAX and @c UINT16_MAX is returned.
 */
int qh_str_to_uint16(const char *__str, int __base, uint16_t *__number, size_t *__end_offset);

/**
 * Safely converts a string into a @c uint32_t.
 *
 * This function is similar to @e strtoull(), but does more error checking on the result of the
 * conversion and ensures that the result fits in a @c uint32_t. This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_uint32() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().

 * For more information on using this function, see the documentation for @e strtoull().
 *
 * Unlike @e strtoull(), this function does not accept a negative sign.
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is larger than @c UINT32_MAX and @c UINT32_MAX is returned.
 */
int qh_str_to_uint32(const char *__str, int __base, uint32_t *__number, size_t *__end_offset);

/**
 * Safely converts a string into a @c uint64_t.
 *
 * This function is similar to @e strtoull(), but does more error checking on the result of the
 * conversion and ensures that the result fits in a @c uint64_t.  This simplifies the work required by the
 * caller, which only needs to validate that the return value from @e qh_str_to_uint64() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().

 * For more information on using this function, see the documentation for @e strtoull().
 *
 * Unlike @e strtoull(), this function does not accept a negative sign.
 *
 * @param[in]  __str    The string to convert into a number.
 * @param[in]  __base   The base of the number to parse.
 * @param[out] __number Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @e number
 *         isn't updated except for ERANGE).
 * @retval ERANGE The number value is larger than @c UINT64_MAX and @c UINT64_MAX is returned.
 */
int qh_str_to_uint64(const char *__str, int __base, uint64_t *__number, size_t *__end_offset);

/**
 * Safely converts a string into an @c unsigned @c int.
 *
 * This function is similar to @e strtoull(), but does more error checking on the result of the
 * conversion and ensures that the result fits in an @c unsigned @c int. This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_uint() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().

 * For more information on using this function, see the documentation for @e strtoull().
 *
 * Unlike @e strtoull(), this function does not accept a negative sign.
 *
 * @param[in]  __str        The string to convert into a number.
 * @param[in]  __base       The base of the number to parse.
 * @param[out] __number     Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is larger than @c UINT_MAX and @c UINT_MAX is returned.
 */
int qh_str_to_uint(const char *__str, int __base, unsigned int *__number, size_t *__end_offset);

/**
 * Safely converts a string into a @c size_t.
 *
 * This function is similar to @e strtoull(), but does more error checking on the result of the
 * conversion and ensures that the result fits in a @c size_t. This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_size() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().

 * For more information on using this function, see the documentation for @e strtoull().
 *
 * Unlike @e strtoull(), this function does not accept a negative sign.
 *
 * @param[in]  __str        The string to convert into a number.
 * @param[in]  __base       The base of the number to parse.
 * @param[out] __number     Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is larger than @c SIZE_MAX and @c SIZE_MAX is returned.
 */
int qh_str_to_size(const char *__str, int __base, size_t *__number, size_t *__end_offset);

/**
 * Safely converts a string into an @c unsigned @c char.
 *
 * This function is similar to @e strtoull(), but does more error checking on the result of the
 * conversion and ensures that the result fits in an @c unsigned @c char. This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_uchar() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().

 * For more information on using this function, see the documentation for @e strtoull().
 *
 * Unlike @e strtoull(), this function does not accept a negative sign.
 *
 * @param[in]  __str        The string to convert into a number.
 * @param[in]  __base       The base of the number to parse.
 * @param[out] __number     Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is larger than @c UCHAR_MAX and @c UCHAR_MAX is returned.
 */
int qh_str_to_uchar(const char *__str, int __base, unsigned char *__number, size_t *__end_offset);

/**
 * Safely converts a string into an @c unsigned @c long.
 *
 * This function is similar to @e strtoull(), but does more error checking on the result of the
 * conversion and ensures that the result fits in an @c unsigned @c long. This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_ulong() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().

 * For more information on using this function, see the documentation for @e strtoull().
 *
 * Unlike @e strtoull(), this function does not accept a negative sign.
 *
 * @param[in]  __str        The string to convert into a number.
 * @param[in]  __base       The base of the number to parse.
 * @param[out] __number     Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is larger than @c ULONG_MAX and @c ULONG_MAX is returned.
 */
int qh_str_to_ulong(const char *__str, int __base, unsigned long *__number, size_t *__end_offset);

/**
 * Safely converts a string into an @c unsigned @c long @c long.
 *
 * This function is similar to @e strtoull(), but does more error checking on the result of the
 * conversion and ensures that the result fits in an @c unsigned @c long @c long. This simplifies
 * the work the caller is required to do, which is only to validate that the return value from
 * @e qh_str_to_ullong() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().

 * For more information on using this function, see the documentation for @e strtoull().
 *
 * Unlike @e strtoull(), this function does not accept a negative sign.
 *
 * @param[in]  __str        The string to convert into a number.
 * @param[in]  __base       The base of the number to parse.
 * @param[out] __number     Pointer to the location where the number can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is larger than @c ULLONG_MAX and @c ULLONG_MAX is returned.
 */
int qh_str_to_ullong(const char *__str,
                        int __base,
                        unsigned long long *__number,
                        size_t *__end_offset);

/**
* Safely converts a string representing a size in bytes with an optional size
* suffix into a @c uint64_t.
*
* The string is interpreted as a decimal (base 10) and if a suffix is specified,
* the value is multiplied by a corresponding amount. Valid suffixes are @c k, @c m, @c g, and @c t,
* each of which represents the appropriate power of 1024. Note that suffixes are case
* insensitive and must come directly after the number, with no whitespace in between.
*
* This function is similar to @e strtoull(), but does more error checking on the result of the
* conversion and ensures that the result fits in a @c uint64_t. This simplifies the work the caller is
* required to do, which is only to validate that the return value from @e
* qh_str_to_bytes() is EOK.
*
* For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
* optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
* returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
* updated with the offset of the last character the function parsed. When NULL, the function
* treats trailing characters as invalid, except for characters recognized by @e isspace().
*
* For more information on using this function, see the documentation for @e strtoull().
*
* @param[in]  __str The string to convert into a number.
* @param[out] __number Pointer to the location where the number can be stored.
* @param[out] __end_offset The offset where parsing stopped.
*
* @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't
*         updated except for ERANGE).
* @retval ERANGE The number value is larger than @c UINT64_MAX and @c UINT64_MAX is returned.
*/
int qh_str_to_bytes(const char *__str, uint64_t *__number, size_t *__end_offset);

/**
 * Safely converts a string into a boolean
 *
 * The string passed (@e __str) is interpreted as either a string of a predetermined set
 * (@c t or @c true for @c true, @c f or @c false for @c false) or as a number.
 * It evaluates as false if the number passed is equal to zero, or true otherwise.
 * If @e __str matches one of the above specific cases, it evaluates to the respective value.
 * The case of @e __str passed does not matter and string literals are supported.
 *
 * For more information on using this function, see the documentation for @e strtoull().
 *
 * @param[in]  __str The string to convert into a @c bool.
 * @param[out] __out Pointer to where the @c bool can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __out is unchanged).
 * @retval ERANGE The number value is larger than @c LLONG_MAX (and true is returned) or
 * less than @c LLONG_MIN (and true is returned).
 */
int qh_str_to_bool(const char *__str, bool *__out, size_t *__end_offset);

/**
 * Safely converts a string into a @c mode_t.
 *
 * The string is interpreted as an octal (base 8).
 *
 * This function is similar to @e strtoull(), but does more error checking on the result of the
 * conversion and ensures that the result fits in a @c mode_t. This simplifies the work the caller is
 * required to do, which is only to validate that the return value from @e qh_str_to_mode() is EOK.
 *
 * For conversion of strings that are part of a longer one (e.g., a comma-separated list), an
 * optional @e __end_offset parameter can be specified. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().
 *
 * For more information on using this function, see the documentation for @e strtoull().
 *
 * Unlike @e strtoull(), this function does not accept a negative sign.
 *
 * @param[in]  __str  The string to convert into a mode.
 * @param[out] __mode Pointer to the location where the mode can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c mode isn't
 *         updated except for ERANGE).
 * @retval ERANGE The number value is larger than the maximum allowed, but the returned mode is
 *         still set only with the valid mode bits that were set.
 */
int qh_str_to_mode(const char *__str, mode_t *__mode, size_t *__end_offset);

/**
 * @brief Safely converts a string that represents a signal name or number into an @c int.
 *
 * @details The @e qh_str_to_signal() function converts a string that represents a signal number
 * or name (e.g., @c term, @c sigterm, @c SigTerm, etc.) to a signal number. The string is
 * interpreted as a decimal (base 10). Passing it @c SIGHUP is equivalent to passing it @c 1,
 * @c HUP, or @c sigHUP (i.e., the case does not matter).
 *
 * It is similar to @e strtoll(), but does more error checking on the result of
 * the conversion and ensures that the result fits in an @c int. This simplifies the work the caller
 * is required to do, which is only to validate that the return value from @e
 * qh_str_to_signal() is EOK.
 *
 * To convert strings that are part of a longer one (e.g., a comma-separated list), you can specify
 * the optional @e __end_offset parameter. When you specify @e __end_offset, the function
 * returns successfully even if there are trailing characters. When non-NULL, @e __end_offset is
 * always updated with the offset of the last character the function parsed. When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().

 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str The string to convert into a signal number.
 * @param[out] __number Pointer to the location where the signal can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number isn't updated).
 */
int qh_str_to_signal(const char *__str, int *__number, size_t *__end_offset);

/**
 * @brief Safely converts a string that represents an @e errno symbol or number into its corresponding
 * @e errno value (an @c int).
 *
 * @details The @e qh_str_to_errno() function converts a string that represents an @e errno symbol or
 * number (e.g., ENOMEM, EOK, etc.) to an @e errno number.  The string is interpreted as a symbol
 * first, and as a decimal (base 10) otherwise.
 *
 * When passed a number, it is similar to @e strtoll(), but does more error checking on the result
 * of the conversion and ensures that the result fits in an @c int.  This simplifies the work the
 * caller is required to do, which is only to validate that the return value from
 * @e qh_str_to_errno() is EOK.
 *
 * To convert strings that are part of a longer one (e.g., a comma-separated list), you can specify
 * the optional @e __end_offset parameter.  When you specify @e __end_offset, the function returns
 * successfully even if there are trailing characters.  When non-NULL, @e __end_offset is always
 * updated with the offset of the last character the function parsed.  When NULL, the function
 * treats trailing characters as invalid, except for characters recognized by @e isspace().

 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str The string to convert into an @e errno number.
 * @param[out] __number Pointer to the location where the @e errno value can be stored.
 * @param[out] __end_offset The offset where parsing stopped.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __number
 *         isn't updated, even for ERANGE).
 * @retval ERANGE The number value is either smaller than @c INT_MIN (and @c INT_MIN is returned)
 *         or larger than @c INT_MAX (and @c INT_MAX is returned).
 */
int qh_str_to_errno(const char *__str, int *__number, size_t *__end_offset);

/**
 * Safely converts a string into a @c uid_t.
 *
 * The @e qh_str_username_to_uid() function first checks the password database to determine if the
 * string corresponds to a user name. If it does, the user ID for that account is
 * returned. Otherwise, the function attempts to interpret the string as a decimal number (base 10)
 * similar to @e strtoll(), but does more error checking on the result of the conversion and ensures
 * that the result fits in a @c uid_t. This simplifies the work caller is required to do, which is
 * only to validate that the return value from @e qh_str_username_to_uid() is EOK.
 *
 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str The string to convert into a @c uid_t.
 * @param[out] __uid Pointer to the location where the @c uid_t can be stored.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c __uid
 *         isn't updated).
 */
#if !defined(__MINGW32__) && !defined(__MINGW64__)
int qh_str_username_to_uid(const char *__str, uid_t *__uid);
#endif

/**
 * @brief Safely converts a string into a @c gid_t.
 *
 * @details The @e qh_str_groupname_to_gid() function first checks the password database to
 * determine if the string corresponds to a group name. If it does, the group ID (gid) for that
 * group is returned. Otherwise, the function attempts to interpret the string as a decimal number
 * (base 10), similar to @e strtoll() but with more error checking on the result of the conversion,
 * and ensures that the result fits in a @c gid_t. By performing these tasks, it simplifies the work
 * the caller is required to do, which is only to validate that the return value from @e
 * qh_str_groupname_to_gid() is EOK.
 *
 * For more information on using this function, see the documentation for @e strtoll().
 *
 * @param[in]  __str The string to convert into a group ID (gid).
 * @param[out] __gid Pointer to the location where the gid can be stored.
 *
 * @return EOK on success or a standard @e errno on failure (@e errno is also set, and @c gid isn't
 *         updated).
 */
#if !defined(__MINGW32__) && !defined(__MINGW64__)
int qh_str_groupname_to_gid(const char *__str, gid_t *__gid);
#endif

/** @cond */
__END_DECLS
/** @endcond */

#endif /* QNX_QH_STRING_H_INCLUDED */
