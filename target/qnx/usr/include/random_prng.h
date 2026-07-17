/*
 * $QNXLicenseC:
 * Copyright 2019, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */


/* Description: library interface for adding random number generators to random */

#ifndef _RANDOM_PRNG_H_INCLUDED
#define _RANDOM_PRNG_H_INCLUDED

#include <stddef.h>

/**
 * @brief Prototype for function to be used by the random service to add entropy
 * the PRNG.
 *
 * @param buffer    Pointer to buffer containing entropy to be added. Data
 *                  must be greater than zero bytes.
 * @param size      Size of buffer in bytes.
 */
typedef void (*prng_add_entropy_fn)(void const *buffer, size_t size);

/**
 * @brief Prototype for function pointer to get random values from the PRNG
 *
 * @param[out] outdata Buffer used to store random values
 * @param[in] size Size of the outdata buffer
 *
 * @return EOK on success, errno otherwise
 */
typedef int (*prng_pseudorand_fn)(unsigned char *outdata, size_t size);

/**
 * @brief Prototype for function pointer to initialize the PRNG
 *
 * @return EOK on success, errno otherwise
 */
typedef int (*prng_init_fn)(void);

/**
 * @brief Prototype for function to cleanup the PRNG
 */
typedef void (*prng_cleanup_fn)(void);

#endif
