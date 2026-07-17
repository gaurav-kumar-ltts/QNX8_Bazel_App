/*
 * Copyright (c) 2016-2019, 2024, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

/**
 * @file qcrypto_keys.h
 * @brief QNX cryptography library key handling API
 *
 * This API provides a consistent interface to the various key generation primitives offered by
 * third-party libraries.
 */

#ifndef LIBQCRYPTO_QCRYPTO_KEYS_H_INCLUDED_
#define LIBQCRYPTO_QCRYPTO_KEYS_H_INCLUDED_

#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>

#include <qcrypto/qcrypto.h>

#include <sys/cdefs.h>

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * @brief Key encoding formats
 */
typedef uint32_t qcrypto_key_format_t;

#define QCRYPTO_KEY_FMT_UNKNOWN    0u /*!< Unknown key format. */
#define QCRYPTO_KEY_FMT_SYMMETRIC  1u /*!< Symmetric key format. */
#define QCRYPTO_KEY_FMT_DER        2u /*!< Public or private key DER format. */
#define QCRYPTO_KEY_FMT_PEM        3u /*!< Public or private key PEM format. */
#define QCRYPTO_KEY_FMT_MAX        4u /*!< Maximum value supported internally by the @c qcrypto library. */
#define QCRYPTO_KEY_FMT_PRIVATE    100u /*!< Value above which custom formats can use. */

/**
 * @brief Supported ECC curves
 *
 * @details Custom plugins can use custom values starting at the value specified by @c
 *          QCRYPTO_EC_CURVE_PRIVATE.
 */
typedef uint32_t qcrypto_ec_curve_t;

#define QCRYPTO_EC_CURVE_UNKNOWN    0u
#define QCRYPTO_EC_CURVE_SECP160R1  1u
#define QCRYPTO_EC_CURVE_SECP192R1  2u
#define QCRYPTO_EC_CURVE_SECP224R1  3u
#define QCRYPTO_EC_CURVE_SECP256R1  4u
#define QCRYPTO_EC_CURVE_SECP384R1  5u
#define QCRYPTO_EC_CURVE_SECP521R1  6u
#define QCRYPTO_EC_CURVE_SECT163K1  7u
#define QCRYPTO_EC_CURVE_SECT163R2  8u
#define QCRYPTO_EC_CURVE_SECT233K1  9u
#define QCRYPTO_EC_CURVE_SECT233R1  10u
#define QCRYPTO_EC_CURVE_SECT239K1  11u
#define QCRYPTO_EC_CURVE_SECT283K1  12u
#define QCRYPTO_EC_CURVE_SECT283R1  13u
#define QCRYPTO_EC_CURVE_SECT409K1  14u
#define QCRYPTO_EC_CURVE_SECT409R1  15u
#define QCRYPTO_EC_CURVE_SECT571K1  16u
#define QCRYPTO_EC_CURVE_SECT571R1  17u
#define QCRYPTO_EC_CURVE_WTLS5      18u
#define QCRYPTO_EC_CURVE_MAX        19u /*!< Maximum value supported internally by the cryptography library. */
#define QCRYPTO_EC_CURVE_PRIVATE    100u /*!< Value above which custom types can use. */


/**
 * @brief EC key types
 *
 * @details Only named curve keys can be used in X.509 certificates.
 */
typedef enum {
	QCRYPTO_EC_KEY_TYPE_NAMED = 0,		/*!< Key is created with the curve name encoded. */
	QCRYPTO_EC_KEY_TYPE_EXPLICIT = 1,	/*!< Key is created with the explicit curve parameters encoded. */
} qcrypto_ec_key_type_t;

/**
 * @brief Public or private key arguments
 */
typedef struct {
	union {
		struct {
			size_t					bits;		/*!< The modulus size in bits. */
			size_t					pubexp;		/*!< The public exponent value. */
		} rsa;
		struct {
			size_t					psize;		/*!< The prime size in bits. */
		} dsa;
		struct {
			qcrypto_ec_curve_t		curve;		/*!< The ECC curve. */
			qcrypto_ec_key_type_t	type;		/*!< The ECC key type. */
		} ec;
		struct {
			size_t					psize;		/*!< The prime size in bits. */
		} dh;
		void						*private;	/*!< Private arguments to pass for other key types. */
	};
} qcrypto_key_args_t;

/**
 * @brief Request a key from the QNX cryptography
 *          library
 *
 * @details This function is used to request a specific key algorithm from the @c qcrypto
 *          library.
 *
 * @param[in] name The algorithm name (for example, @c ec).
 *
 * @param[in] tag The tag value that identifies the plugin in the @c qcrypto library
 *                configuration file to retrieve the algorithm from.
 *
 * @param[in] flags Reserved for future use.
 *
 * @param[out] ctx A context pointer that is filled with the algorithm context on success.
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_keygen_request(const char *name, const char *tag, uint32_t flags,
		qcrypto_ctx_t **ctx);

/**
 * @brief Query whether the specified key generation algorithm is supported
 *
 * @details This function checks whether a particular key generation algorithm is supported by the
 *          library.
 *
 * @param[in] name  The algorithm name (e.g., @c ec).
 * @param[in] tag   The tag value that identifies the plugin in the @c qcrypto library
 *                  configuration file to check for the algorithm; or NULL, to use the default
 *                  tag (@e __progname).
 * @param[in] flags Reserved for future use.
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_keygen_supported(const char *name, const char *tag, uint32_t flags);

/**
 * @brief Check if a key is symmetric
 *
 * @param[in] key The key handle.
 *
 * @return @c true if the key is symmetric or @c false otherwise.
 */
bool qcrypto_key_is_symmetric(qcrypto_key_t *key);

/**
 * @brief Check if a key is public
 *
 * @param[in] key The key handle.
 *
 * @return @c true if the key is public or @c false otherwise.
 */
bool qcrypto_key_is_public(qcrypto_key_t *key);

/**
 * @brief Check if a key is private
 *
 * @param[in] key The key handle.
 *
 * @return @c true if the key is private or @c false otherwise.
 */
bool qcrypto_key_is_private(qcrypto_key_t *key);

/**
 * @brief Generate a symmetric key
 * @details This function generates a symmetric key of size @c keysize.
 *
 * @param[in] ctx The algorithm context object.
 * @param[out] key A pointer to the key handle.
 * @param[in] keysize The key size.
 *
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_key_generate(qcrypto_ctx_t *ctx, qcrypto_key_t **key, size_t keysize);

/**
 * @brief Initialize PKI key generation using the specified arguments
 * @details This function initializes a PKI key generation algorithm using the specified key arguments.
 *
 * @param[in] ctx The algorithm context object.
 * @param[in] kargs The key arguments.
 *
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_keypair_init(qcrypto_ctx_t *ctx, const qcrypto_key_args_t *kargs);

/**
 * @brief Initialize PKI key generation using parameters in a file
 * @details This function initializes a PKI key generation algorithm using key parameters from a file.
 *
 * @param[in] ctx The algorithm context object.
 * @param[in] params_file The key parameters filename.
 * @param[in] fmt The file's encoding format (see @c #qcrypto_key_format_t).
 *
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_keypair_init_from_file(qcrypto_ctx_t *ctx, const char *params_file, qcrypto_key_format_t fmt);

/**
 * @brief Initialize PKI key generation using parameters in memory
 * @details This function initializes a PKI key generation algorithm using key parameters stored in
 *          memory.
 *
 * @param[in] ctx The algorithm context object.
 * @param[in] params The key parameters buffer.
 * @param[in] size The size of @c params.
 * @param[in] fmt The encoding format of @c params (see @c #qcrypto_key_format_t).
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_keypair_init_from_mem(qcrypto_ctx_t *ctx, const uint8_t *params, size_t size, qcrypto_key_format_t fmt);

/**
 * @brief Generate a PKI key
 * @details The public key can be omitted and retrieved using @e qcrypto_pubkey_from_privkey() later.
 *
 * @param[in] ctx The algorithm context object.
 * @param[out] pubkey The public key handle (optional).
 * @param[out] privkey The private key handle.
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_keypair_generate(qcrypto_ctx_t *ctx, qcrypto_key_t **pubkey,
		qcrypto_key_t **privkey);

/**
 * @brief Release a key
 *
 * @param[in] key The key handle.
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
void qcrypto_release_key(qcrypto_key_t *key);

/**
 * @brief Extract a public key
 * @details This function extracts the public key from the specified private key.
 *
 * @param[in] ctx The algorithm context object.
 * @param[in] privkey The private key handle.
 * @param[out] pubkey A pointer to the public key handle.
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_pubkey_from_privkey(qcrypto_ctx_t *ctx, qcrypto_key_t *privkey, qcrypto_key_t **pubkey);

/**
 * @brief Load a symmetric key from a file
 * @details This function loads a symmetric key from the specified file.
 *
 * @param[in] ctx The algorithm context object.
 * @param[out] key A pointer to a symmetric key handle.
 * @param[in] filename The key filename.
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_key_from_file(qcrypto_ctx_t *ctx, qcrypto_key_t **key, const char *filename);

/**
 * @brief Load a public key from a file
 * @details This function loads a public key from the specified file.
 *
 * @param[in] ctx The algorithm context object.
 * @param[out] key A pointer to the public key handle.
 * @param[in] filename The key filename.
 * @param[in] fmt The key encoding format (see @c #qcrypto_key_format_t).
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_pubkey_from_file(qcrypto_ctx_t *ctx, qcrypto_key_t **key, const char *filename,
		qcrypto_key_format_t fmt);

/**
 * @brief Load a private key from a file
 * @details This function loads a private key from the specified file.
 *
 * @param[in] ctx The algorithm context object.
 * @param[out] key A pointer to the key handle.
 * @param[in] filename The key filename.
 * @param[in] fmt The key encoding format (see @c #qcrypto_key_format_t).
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_privkey_from_file(qcrypto_ctx_t *ctx, qcrypto_key_t **key, const char *filename,
		qcrypto_key_format_t fmt);

/**
 * @brief Load a symmetric key from memory
 * @details This function loads a symmetric key from the specified memory buffer.
 *
 * @param[in] ctx The algorithm context object.
 * @param[out] key A pointer to a symmetric key handle.
 * @param[in] kbuf The key buffer.
 * @param[in] ksize The key buffer size.
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_key_from_mem(qcrypto_ctx_t *ctx, qcrypto_key_t **key, const uint8_t *kbuf,
		size_t ksize);

/**
 * @brief Load a public key from memory
 * @details This function loads a public key from the specified memory buffer.
 *
 * @param[in] ctx The algorithm context object.
 * @param[out] key A pointer to the public key handle.
 * @param[in] kbuf The key buffer.
 * @param[in] ksize The key buffer size.
 * @param[in] fmt The key encoding format (see @c #qcrypto_key_format_t).
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_pubkey_from_mem(qcrypto_ctx_t *ctx, qcrypto_key_t **key, const uint8_t *kbuf,
		size_t ksize, qcrypto_key_format_t fmt);

/**
 * @brief Load a private key from memory
 * @details This function loads a private key from the specified memory buffer.
 *
 * @param[in] ctx The algorithm context object.
 * @param[out] key A pointer to the private key handle.
 * @param[in] kbuf The key buffer.
 * @param[in] ksize The key buffer size.
 * @param[in] fmt The key encoding format (see @c #qcrypto_key_format_t).
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_privkey_from_mem(qcrypto_ctx_t *ctx, qcrypto_key_t **key, const uint8_t *kbuf,
		size_t ksize, qcrypto_key_format_t fmt);

/**
 * @brief Save a symmetric key to a file
 * @details This function saves a symmetric key to the specified filename.
 *
 * @param[in] ctx The algorithm context object.
 * @param[in] key The symmetric key handle.
 * @param[in] filename The key filename.
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_key_to_file(qcrypto_ctx_t *ctx, qcrypto_key_t *key, const char *filename);

/**
 * @brief Save a public key to a file
 * @details This function saves a public key to the specified filename.
 *
 * @param[in] ctx The algorithm context object.
 * @param[in] key The public key handle.
 * @param[in] filename The key filename.
 * @param[in] fmt The key encoding format (see @c #qcrypto_key_format_t).
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_pubkey_to_file(qcrypto_ctx_t *ctx, qcrypto_key_t *key, const char *filename,
		qcrypto_key_format_t fmt);

/**
 * @brief Save a private key to a file
 * @details This function saves a private key to the specified filename.
 *
 * @param[in] ctx The algorithm context object.
 * @param[in] key The private key handle.
 * @param[in] filename The key filename.
 * @param[in] fmt The key encoding format (see @c #qcrypto_key_format_t).
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_privkey_to_file(qcrypto_ctx_t *ctx, qcrypto_key_t *key, const char *filename,
		qcrypto_key_format_t fmt);

/**
 * @brief Save a symmetric key to memory
 * @details This function saves a symmetric key to the specified memory buffer.
 *
 * @param[in] ctx The algorithm context object.
 * @param[in] key The symmetric key handle.
 * @param[in] kbuf The key buffer. To return the actual key size in @c ksize,
 *                 specify NULL.
 * @param[in,out] ksize The size of the provided key buffer. Must be at least as large
 *                      as the key. The actual key size is returned in @c ksize if the
 *                      call is successful.
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_key_to_mem(qcrypto_ctx_t *ctx, qcrypto_key_t *key, uint8_t *kbuf, size_t *ksize);

/**
 * @brief Save a public key to memory
 * @details This function saves a public key to the specified memory buffer.
 *
 * @param[in] ctx The algorithm context object.
 * @param[in] key The public key handle.
 * @param[in] kbuf The key buffer. To return the actual key size in @c ksize,
 *                 specify NULL.
 * @param[in,out] ksize The size of the provided key buffer. Must be at least as large
 *                      as the key. The actual key size is returned in @c ksize if the
 *                      call is successful.
 * @param[in] fmt The key encoding format (see @c #qcrypto_key_format_t).
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_pubkey_to_mem(qcrypto_ctx_t *ctx, qcrypto_key_t *key, uint8_t *kbuf, size_t *ksize,
		qcrypto_key_format_t fmt);

/**
 * @brief Save a private key to memory
 * @details This function saves a private key to the specified memory buffer.
 *
 * @param[in] ctx The algorithm context object.
 * @param[in] key The private key handle.
 * @param[in] kbuf The key buffer. To return the actual key size in @c ksize,
 *                 specify NULL.
 * @param[in,out] ksize The size of the provided key buffer. Must be at least as large
 *                      as the key. The actual key size is returned in @c ksize if the
 *                      call is successful.
 * @param[in] fmt The key encoding format (see @c #qcrypto_key_format_t).
 *
 * @return QCRYPTO_R_EOK if successful or @c qcrypto_errno if an error occurred.
 */
int qcrypto_privkey_to_mem(qcrypto_ctx_t *ctx, qcrypto_key_t *key, uint8_t *kbuf, size_t *ksize,
		qcrypto_key_format_t fmt);


/** @cond */
__END_DECLS
/** @endcond */

#endif /* LIBQCRYPTO_QCRYPTO_KEYS_H_INCLUDED_ */
