/*
 * Copyright (c) 2017-2022, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef QNX_TABRM_TABRM_TCTI_H_INCLUDED
#define QNX_TABRM_TABRM_TCTI_H_INCLUDED

/**
 * @file tcti.h
 * TCTI library interface to the TABRM service.
 */

/* sorted headers from this project */

/* sorted library headers */
#include <tss2/tss2_tcti.h>

/* sorted system headers */

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * Initialize a TABRM TCTI context.
 *
 * The client of the library is responsible for the memory allocation holding the context.  In order
 * for it to know how much memory to allocate for the context, a @c NULL @a context can be
 * specified, in which case the required size will then be stored in @a size.  The client can then
 * use this size to allocate enough space to hold the context to be initialized.
 *
 * @param[in] context  A pointer to the context to be initialized, or NULL if the client simply
 *                     wants to determine the size to allocate.
 * @param[in,out] size On input: the size of the context to be initialized pointed to by @a context,
 *                     and is ignored if @a context is NULL.
 *                     On output: the minimum amount of memory that would be required to hold @a
 *                     context, unless @a size is NULL.
 * @param[in] dev_path The target TABRM device path name.  If dev_path is NULL, /dev/tpmrm0 is used.
 *
 * Note that this function follows the standard TCTI function type TSS2_TCTI_INIT_FCN found in
 * <tss2/tcti.h>, and also follows its naming convention.
 *
 * @return TSS2_RC_SUCCESS on success, and a tss2 return code (TSS2_RC) on failure (in which case
 *         errno is also set to a standard error number).
 */
TSS2_RC Tss2_Tcti_Tabrm_Init(TSS2_TCTI_CONTEXT *__context, size_t *__size, const char *__dev_path);

/** @cond */
__END_DECLS
/** @endcond */

#endif /* QNX_TABRM_TABRM_TCTI_H_INCLUDED */
