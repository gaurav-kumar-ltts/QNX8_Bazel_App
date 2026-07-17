/*
 * Copyright (c) 2019-2022, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef QNX_TSS2_HELPER_COMMON_H_INCLUDED
#define QNX_TSS2_HELPER_COMMON_H_INCLUDED

/**
 * @file common.h
 *
 * Header file for tss2 common helpers.
 */

/* sorted headers from this project */

/* sorted library headers */
#include <tss2/tss2_common.h>

/* sorted system headers */
#include <sys/cdefs.h>

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * Returns a textual description of the specified TPM 2.0 Software Stack (TSS2) error.
 *
 * @param[in] tss2_rc TPM 2.0 Software Stack (TSS2) error code.
 *
 * @return A textual description of the specified TPM 2.0 Software Stack (TSS2) error.  The return
 *         value is guaranteed not to be NULL.
 */
const char * tss2_helper_rc_to_str(TSS2_RC __tss2_rc) __attribute__((__const__));

/** @cond */
__END_DECLS
/** @endcond */

#endif /* QNX_TSS2_HELPER_COMMON_H_INCLUDED */
