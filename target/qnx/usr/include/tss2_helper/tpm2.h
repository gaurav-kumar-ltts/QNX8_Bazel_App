/*
 * Copyright (c) 2019-2022, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef QNX_TSS2_HELPER_TPM2_H_INCLUDED
#define QNX_TSS2_HELPER_TPM2_H_INCLUDED

/**
 * @file tpm2.h
 *
 * Header file for TPM2 helpers.
 */

/* sorted headers from this project */

/* sorted library headers */
#include <tss2/tss2_tpm2_types.h>

/* sorted system headers */
#include <stdbool.h>
#include <sys/cdefs.h>
#include <sys/types.h>

/** @cond */
__BEGIN_DECLS
/** @endcond */

/*
 * TPM2 command header structure.  See part3, section 5.2 of
 * TPM-Rev-2.0-Part-3-Commands-01.38-code.pdf, a), b) and c).  This structure is packed and so can
 * be used directly on a command buffer.  Note that command buffer data is in big endian byte order.
 */
typedef struct {
    TPMI_ST_COMMAND_TAG tag;
    UINT32 commandSize;
    TPM2_CC commandCode;
} __attribute__((__packed__)) QNX_EXT_TPM2_command_hdr_t;

/*
 * TPM2 response header structure.  See part3, sections 6.1 and 6.2 of
 * TPM-Rev-2.0-Part-3-Commands-01.38-code.pdf.  This structure is packed and so can
 * be used directly on a response buffer.  Note that response buffer data is in big endian byte
 * order.
 */
typedef struct {
    TPMI_ST_COMMAND_TAG tag;
    UINT32 responseSize;
    TPM2_RC responseCode;
} __attribute__((__packed__)) QNX_EXT_TPM2_response_hdr_t;

/**
 * Safely gets the tag member from a TPM2 command header buffer in host byte order.
 *
 * command_buffer does not need to be naturally aligned.  command_buffer_size needs to be greater
 * than or equal to the size of a TPM2 command header, otherwise the function will return an error.
 *
 * @param[in] command_buffer      The TPM2 command header buffer.
 * @param[in] command_buffer_size The size of the command header buffer.
 * @param[out] tag                The tag value in host byte order.  A value is always assigned to
 *                                it even in error conditions.  See the return values section for
 *                                more details.
 *
 * @return A standard errno value, and errno is also set in case of failure.
 * @retval EOK Success.
 * @retval EINVAL command_buffer and / or tag are NULL.  tag is set to TPM2_ST_NULL if not NULL.
 * @retval ENOBUFS command_buffer_size is smaller than the size of a TPM2 command header.  tag is
 *         set to TPM2_ST_NULL.
 */
int tss2_helper_tpm2_get_command_tag(const uint8_t *__command_buffer, size_t __command_buffer_size, TPMI_ST_COMMAND_TAG *__tag);

/**
 * Safely gets the commandSize member from a TPM2 command header buffer in host byte order.
 *
 * command_buffer does not need to be naturally aligned.  command_buffer_size needs to be greater
 * than or equal to the size of a TPM2 command header, otherwise the function will return an error.
 *
 * @param[in] command_buffer      The TPM2 command header buffer.
 * @param[in] command_buffer_size The size of the command header buffer.
 * @param[out] command_size       The commandSize value in host byte order.  A value is always
 *                                assigned to it even in error conditions.  See the return values
 *                                section for more details.
 * @param[in] exact_buffer_size   Wither to validate the extracted commandSize member value
 *                                against the command_buffer_size parameter.
 *
 * @return A standard errno value, and errno is also set in case of failure.
 * @retval EOK Success.
 * @retval EINVAL command_buffer and / or command_size are NULL.  command_size is set to 0 if not
 *         NULL.
 * @retval ENOBUFS command_buffer_size is smaller than the size of a TPM2 command header.
 *         command_size is set to 0.
 * @retval EBADMSG The extracted commandSize member has a value that is smaller than the size of the
 *         TPM2 command header structure.  command_size is set to the extracted value.
 * @retval EMSGSIZE exact_buffer_size is true and the extracted commandSize member value does not
 *         match command_buffer_size.  command_size is set to the extracted value.
 */
int tss2_helper_tpm2_get_command_size(const uint8_t *__command_buffer, size_t __command_buffer_size,
                                      uint32_t *__command_size, bool __exact_buffer_size);

/**
 * Safely gets the commandCode member from a TPM2 command header buffer in host byte order.
 *
 * command_buffer does not need to be naturally aligned.  command_buffer_size needs to be greater
 * than or equal to the size of a TPM2 command header, otherwise the function will return an error.
 *
 * @param[in] command_buffer      The TPM2 command header buffer.
 * @param[in] command_buffer_size The size of the command header buffer.
 * @param[out] tpm2_cc            The commandCode value in host byte order.  A value is always
 *                                assigned to it even in error conditions.  See the return values
 *                                section for more details.
 *
 * @return A standard errno value, and errno is also set in case of failure.
 * @retval EOK Success.
 * @retval EINVAL command_buffer and / or tpm2_cc are NULL.  tpm2_cc is set to 0 if not NULL.
 * @retval ENOBUFS command_buffer_size is smaller than the size of a TPM2 command header.  tpm2_cc
 *         is set to 0.
 */
int tss2_helper_tpm2_get_command_code(const uint8_t *__command_buffer, size_t __command_buffer_size, TPM2_CC *__tpm2_cc);

/**
 * Safely gets the tag member from a TPM2 response header buffer in host byte order.
 *
 * response_buffer does not need to be naturally aligned.  response_buffer_size needs to be greater
 * than or equal to the size of a TPM2 response header, otherwise the function will return an error.
 *
 * @param[in] response_buffer      The TPM2 response header buffer.
 * @param[in] response_buffer_size The size of the response header buffer.
 * @param[out] tag                 The tag value in host byte order.  A value is always assigned to
 *                                 it even in error conditions.  See the return values section for
 *                                 more details.
 *
 * @return A standard errno value, and errno is also set in case of failure.
 * @retval EOK Success.
 * @retval EINVAL response_buffer and / or tag are NULL.  tag is set to TPM2_ST_NULL if not NULL.
 * @retval ENOBUFS response_buffer_size is smaller than the size of a TPM2 response header.  tag is
 *         set to TPM2_ST_NULL.
 */
int tss2_helper_tpm2_get_response_tag(const uint8_t *__response_buffer, size_t __response_buffer_size,
                                      TPMI_ST_COMMAND_TAG *__tag);

/**
 * Safely gets the responseSize member from a TPM2 response header buffer in host byte order.
 *
 * response_buffer does not need to be naturally aligned.  response_buffer_size needs to be greater
 * than or equal to the size of a TPM2 response header, otherwise the function will return an error.
 *
 * @param[in] response_buffer      The TPM2 response header buffer.
 * @param[in] response_buffer_size The size of the response header buffer.
 * @param[out] response_size       The responseSize value in host byte order.  A value is always
 *                                 assigned to it even in error conditions.  See the return values
 *                                 section for more details.
 * @param[in] exact_buffer_size    Wither to validate the extracted responseSize member value
 *                                 against the response_buffer_size parameter.
 *
 * @return A standard errno value, and errno is also set in case of failure.
 * @retval EOK Success.
 * @retval EINVAL response_buffer and / or response_size are NULL.  response_size is set to 0 if not
 *         NULL.
 * @retval ENOBUFS response_buffer_size is smaller than the size of a TPM2 response header.
 *         response_size is set to 0.
 * @retval EBADMSG The extracted responseSize member has a value that is smaller than the size of
 *         the TPM2 response header structure.  response_size is set to the extracted value.
 * @retval EMSGSIZE exact_buffer_size is true and the extracted responseSize member value does not
 *         match response_buffer_size.  response_size is set to the extracted value.
 */
int tss2_helper_tpm2_get_response_size(const uint8_t *__response_buffer, size_t __response_buffer_size,
                                       uint32_t *__response_size, bool __exact_buffer_size);

/**
 * Safely gets the responseCode member from a TPM2 response header buffer in host byte order.
 *
 * response_buffer does not need to be naturally aligned.  response_buffer_size needs to be greater
 * than or equal to the size of a TPM2 response header, otherwise the function will return an error.
 *
 * @param[in] response_buffer      The TPM2 response header buffer.
 * @param[in] response_buffer_size The size of the response header buffer.
 * @param[out] tpm2_rc             The responseCode value in host byte order.  A value is always
 *                                 assigned to it even in error conditions.  See the return values
 *                                 section for more details.
 *
 * @return A standard errno value, and errno is also set in case of failure.
 * @retval EOK Success.
 * @retval EINVAL response_buffer and / or tpm2_rc are NULL.  tpm2_rc is set to TPM2_RC_FAILURE if
 *         not NULL.
 * @retval ENOBUFS response_buffer_size is smaller than the size of a TPM2 response header.  tpm2_rc
 *         is set to TPM2_RC_FAILURE.
 */
int tss2_helper_tpm2_get_response_code(const uint8_t *__response_buffer, size_t __response_buffer_size, TPM2_RC *__tpm2_rc);

/** @cond */
__END_DECLS
/** @endcond */

#endif /* QNX_TSS2_HELPER_TPM2_H_INCLUDED */
