/*
 * Copyright (c) 2022, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

/**
 * @file pkcs11-core.h
 *
 * @brief PKCS#11 Core Library API
 */

#ifndef QNX_PKCS11_PKCS11_CORE_H_INCLUDED
#define QNX_PKCS11_PKCS11_CORE_H_INCLUDED

#include <stdbool.h>
#include <string.h>
#include <pkcs11/pkcs11.h>

/**
 * @brief PKCS#11 attributes object
 *
 * @note Do not manipulate the object internals directly, this is handled by the API
 *       found in this file.
 */
typedef struct pkcs11_attributes_s {
	CK_ATTRIBUTE  *attr; /*!< attribute array */
	CK_ULONG      num_attr; /*!< number of attributes held above */
	CK_ULONG      max_num_attr; /*!< maximum number of attributes in attribute array */
	uint8_t       *attr_data; /*!< attribute data */
	size_t        attr_data_size; /*!< current attribute data buffer size */
	size_t        max_attr_data_size; /*!< maximum attribute data buffer size */
} pkcs11_attributes_t;

#define PKCS11_ATTRIBUTES_INITIALIZER { \
	.attr = NULL,                       \
	.num_attr = 0,                      \
	.max_num_attr = 0,                  \
	.attr_data = NULL,                  \
	.attr_data_size = 0,                \
	.max_attr_data_size = 0,            \
}

/**
 * @brief PKCS#11 strcmp library
 *
 * Encapsulate all the offending strcmp code required because
 * PKCS#11 standard uses unsigned chars for strings
 *
 * @param[in]  p1  first string compare
 * @param[in]  p2  second string to compare
 *
 * @return same as @c strcmp function
 */
static inline int pkcs11_strcmp(const CK_CHAR *p1, const CK_CHAR *p2)
{
	return strcmp((const char*)p1, (const char*)p2);
}

/**
 * @brief PKCS#11 bool wrapper for MISRA compliance
 *
 * @param[in]  value  PKCS#11 boolean value
 *
 * @return  @c true or @c false bool
 */
static inline bool pkcs11_bool(CK_BBOOL value)
{
	return (value != 0u);
}

/**
 * @brief Clear sensitive memory properly
 *
 * @param[in] dst   data to clear
 * @param[in] size  size of data
 */
void pkcs11_memclear(void *dst, size_t size);

/**
 * @brief Constant time compare function
 *
 * @param[in] v1    first value to compare
 * @param[in] v2    second value to compare
 * @param[in] size  length to compare v1 to v2
 *
 * @return @c CKR_OK if @c v1 matches @c v2 for given @c size, @c CKR_* error code otherwise
 */
CK_RV pkcs11_memcmp(const uint8_t *v1, const uint8_t *v2, size_t size);

/**
 * @brief Return description of error code
 *
 * @param[in]  ckr  CKR_* error code
 *
 * @return string representing the error
 */
const char* pkcs11_strckr(CK_RV ckr);

/**
 * @brief Duplicate attributes
 *
 * @param[in]   in   input attributes object
 * @param[out]  out  output attributes object
 *
 * @note The @c out object can be a freshly initialized (with PKCS11_ATTRIBUTES_INITIALIZER)
 *       or re-used object.
 *
 * @return @c CKR_OK on success, @c CKR_* error code otherwise
 */
CK_RV pkcs11_core_attributes_duplicate(const pkcs11_attributes_t *in, pkcs11_attributes_t *out);

/**
 * @brief Copy an attribute value
 *
 * @param[in]   in   attribute to copy data from
 * @param[out]  out  attribute to copy data into
 *
 * @note The @c out object needs to be properly initialized and have a large enough buffer
 *       set up in @c pValue and its length assigned to @c ulValueLen
 *
 * @return @c CKR_OK on success, @c CKR_* error code otherwise
 */
CK_RV pkcs11_core_copy_attribute(const CK_ATTRIBUTE *in, CK_ATTRIBUTE *out);

/**
 * @brief Check if an attributes object has a specific attribute
 *
 * @param[in]   pattrs  attributes object
 * @param[in]   type    attribute type
 * @param[out]  ppattr  pointer to attribute object (optional)
 *
 * @return @c CKR_OK on success, @c CKR_* error code otherwise
 */
CK_RV pkcs11_core_attributes_has_attribute(const pkcs11_attributes_t *pattrs, CK_ATTRIBUTE_TYPE type,
	CK_ATTRIBUTE **ppattr);

/**
 * @brief Copy an attribute value into a buffer from an attributes object
 *
 * @param[in]   pattrs  attributes object
 * @param[in]   type    attribute type
 * @param[out]  buf     buffer to copy data to
 * @param[in]   bufsize buffer size
 *
 * @return @c CKR_OK on success, @c CKR_* error code otherwise
 */
CK_RV pkcs11_core_attributes_copy_attribute(const pkcs11_attributes_t *pattrs, CK_ATTRIBUTE_TYPE type, void *buf,
	size_t bufsize);

/**
 * @brief Set attributes on an object
 *
 * @param[in,out]  pattrs   attributes object to modify
 * @param[in]      pattr    attributes array to add to object
 * @param[in]      nattr    number of attributes in array to set
 *
 * @note The internal buffers may grow as a result of this function call.
 *
 * @note Attributes of type CKF_ARRAY_ATTRIBUTE are currently unsupported.
 *
 * @return @c CKR_OK on success, @c CKR_* error code otherwise
 */
CK_RV pkcs11_core_set_attributes(pkcs11_attributes_t *pattrs, const CK_ATTRIBUTE *pattr, CK_ULONG nattr);

/**
 * @brief Check attribute subset matches exactly items in the set
 *
 * @param[in]  set     Set attributes object
 * @param[in]  subset  Subset attributes object
 *
 * @return  @c true if subset matches, @c false otherwise
 */
bool pkcs11_core_attributes_match_subset(const pkcs11_attributes_t *set, const pkcs11_attributes_t *subset);

/**
 * @brief Cleanup attributes
 *
 * @note Caller takes care of the lifetime of the attributes object
 *
 * @param[in] pattrs  attributes object
 */
void pkcs11_core_attributes_cleanup(pkcs11_attributes_t *pattrs);

/**
 * @brief Fill the attribute values as per input template given by caller
 *
 * @param[in]      pattrs     attributes object
 * @param[in,out]  ptemplate  attributes template array to fill
 * @param[in]      ntemplate  number of attributes in template
 *
 * @return @c CKR_OK on success, @c CKR_* error code otherwise
 */
CK_RV pkcs11_core_attributes_get_values(const pkcs11_attributes_t *pattrs, CK_ATTRIBUTE *ptemplate,
	CK_ULONG ntemplate);

/**
 * @brief Print PKCS#11 attributes
 *
 * @param[in] pattrs  attributes array
 * @param[in] nattr   attributes array size
 */
void pkcs11_core_attributes_print(const CK_ATTRIBUTE* pattrs, CK_ULONG nattr);

#endif /* QNX_PKCS11_PKCS11_CORE_H_INCLUDED */
