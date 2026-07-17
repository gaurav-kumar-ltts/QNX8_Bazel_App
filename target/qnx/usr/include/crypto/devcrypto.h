/*
 * $QNXLicenseC:
 * Copyright (c) 2018, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software. Free development
 * licenses are available for evaluation and non-commercial purposes. For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others. Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

/**
 * @file devcrypto.h
 * @brief devcrypto service and plugin common API
 *
 * This file defines the common API for the devcrypto service
 * and its plugins
 */

#ifndef _CRYPTO_DEVCRYPTO_H_INCLUDED
#define _CRYPTO_DEVCRYPTO_H_INCLUDED

#include <stdarg.h>
#include <stdint.h>
#include <sys/cdefs.h>

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * @brief Types of log levels
 */
typedef enum _devcrypto_logtype {
	DEVCRYPTO_LOGTYPE_PRINT,
	DEVCRYPTO_LOGTYPE_INFO,
	DEVCRYPTO_LOGTYPE_WARNING,
	DEVCRYPTO_LOGTYPE_ERROR,
	DEVCRYPTO_LOGTYPE_FATAL,
} devcrypto_logtype_t;

/**
 * @brief Message logging function
 *
 * @param[in] type log type
 * @param[in] fmt format string
 * @param[in] ... format string parameters
 */
void devcrypto_log(devcrypto_logtype_t type, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

/**
 * @defgroup DEVCRYPTO_LOG_MACROS Devcrypto logging macros
 *
 * @{
 */
/**
 * \{
 */
#define devcrypto_fatal(...)	devcrypto_log(DEVCRYPTO_LOGTYPE_FATAL,   ## __VA_ARGS__)
#define devcrypto_error(...)	devcrypto_log(DEVCRYPTO_LOGTYPE_ERROR,   ## __VA_ARGS__)
#define devcrypto_warn(...)		devcrypto_log(DEVCRYPTO_LOGTYPE_WARNING, ## __VA_ARGS__)
#define devcrypto_info(...)		devcrypto_log(DEVCRYPTO_LOGTYPE_INFO,    ## __VA_ARGS__)
#define devcrypto_print(...)	devcrypto_log(DEVCRYPTO_LOGTYPE_PRINT,   ## __VA_ARGS__)
/**
 * \}
 */
/**
 * @}
 */

/**
 * @brief Convert binary to hex
 *
 * @param[out] dst destination buffer (should at least be 2xcount+1 in length)
 * @param[in] src binary data to convert
 * @param[in] count src length
 *
 * @returns
 * @retval EOK if successful
 * @retval errno on failure
 */
int devcrypto_bin2hex(char *dst, const uint8_t *src, size_t count);

/**
 * @brief Print binary data in hex format
 *
 * @param[in] value binary data to print
 * @param[in] count value length
 */
void devcrypto_print_hex(const uint8_t *value, size_t count);

/** @cond */
__END_DECLS
/** @endcond */

#endif /* _CRYPTO_DEVCRYPTO_H_INCLUDED */
