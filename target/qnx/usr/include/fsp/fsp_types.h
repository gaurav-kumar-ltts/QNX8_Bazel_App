/*
* Copyright (c) 2025, BlackBerry Limited. All rights reserved.
*
* BlackBerry Limited and its licensors retain all intellectual property and
* proprietary rights in and to this software and related documentation. Any
* use, reproduction, disclosure or distribution of this software and related
* documentation without an express license agreement from BlackBerry Limited
* is strictly prohibited.
*/

#ifndef FSP_TYPES_H
#define FSP_TYPES_H

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
static_assert(sizeof(bool) == 1, "bool must be 1 byte");
#else  // C
#include <stdbool.h>
_Static_assert(sizeof(bool) == 1, "bool must be 1 byte");
#endif

#ifdef __cplusplus
#define CAST(T, X) (static_cast<T>(X))
#else
#define CAST(T, X) ((T)(X))
#endif

#define FSP_EXPORT __attribute__((visibility("default")))

/*!
 * \brief FSP \c errno compatible result type
 */
typedef int32_t fsp_ResultType;

/*!
 * \brief FSP specific errnos
 */
#define FSP_OK 0

/*!
 * \brief Constructs an FSP error code
 *
 * \param RESULT The constructed error code
 * \param DOMAIN The error code's domain
 * \param ERROR The basic error code
 */
#define FSP_RESULT_SET_ERROR(RESULT, DOMAIN, ERROR) \
  (RESULT = ((CAST(fsp_ResultType, DOMAIN) << 16) | CAST(fsp_ResultType, ERROR)))

/*!
 * \brief FSP nanoseconds quantity type
 */
typedef uint64_t fsp_NanosecondsType;

/*!
 * \brief FSP byte span type
 */
typedef struct fsp_ByteSpan {
  uint8_t* data;
  size_t size;
} fsp_ByteSpanType;

/*!
 * \brief FSP const byte span type
 */
typedef struct fsp_ConstByteSpan {
  const uint8_t* data;
  size_t size;
} fsp_ConstByteSpanType;

/*!
 * \brief FSP span of byte spans type
 */
typedef struct fsp_SpanSpan {
  fsp_ByteSpanType* data;
  size_t size;
} fsp_SpanSpanType;

/*!
 * \brief FSP span of const byte spans type
 */
typedef struct fsp_ConstSpanSpan {
  const fsp_ConstByteSpanType* data;
  size_t size;
} fsp_ConstSpanSpanType;

/*!
 * \brief FSP string type
 */
typedef struct fsp_String {
  char* data;
  size_t len;
} fsp_StringType;

/*!
 * \brief FSP const string type
 */
typedef struct fsp_ConstString {
  char const* data;
  size_t len;
} fsp_ConstStringType;

/*!
 * \brief FSP enum underlying type
 */
typedef enum fsp_BaseEnum { FSP_BASE_ENUM_0 } fsp_BaseEnumType;

#ifdef __cplusplus
static_assert(sizeof(fsp_BaseEnumType) == sizeof(uint32_t), "Default enum size must be 4 bytes");
#else
_Static_assert(sizeof(fsp_BaseEnumType) == sizeof(uint32_t), "Default enum size must be 4 bytes");
#endif

#endif  // FSP_TYPES_H
