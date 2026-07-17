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
 * @file devcrypto_plugin.h
 * @brief API for devcrypto service plugins
 *
 * This file defines the devcrypto plugin API
 */

#ifndef _CRYPTO_DEVCRYPTO_PLUGIN_H_INCLUDED
#define _CRYPTO_DEVCRYPTO_PLUGIN_H_INCLUDED

#include <inttypes.h>
#include <stddef.h>
#include <sys/cdefs.h>

#include <crypto/devcrypto.h>
#include <crypto/cryptodev.h>

/**
 * @brief Plugin API version.
 */
#define DEVCRYPTO_PLUGIN_VERSION		1

/**
 * @brief Plugin entry point name.
 */
#define DEVCRYPTO_PLUGIN_ENTRY_POINT	devcrypto_plugin_ops

/**
 * @brief Plugin entry point name as a string.
 */
#define DEVCRYPTO_PLUGIN_ENTRY_NAME		"devcrypto_plugin_ops"

/** @cond */
__BEGIN_DECLS
/** @endcond */

/* forward decls */
typedef struct _devcrypto_algorithm devcrypto_algorithm_t;

/**
 * @brief Algorithm state context
 * @details The state context object is passed as a parameter to each
 *          algorithm's functions to allow algorithm-specific data
 *          to be stored and referenced. Additionally, it provides
 *          a reference to the algorithm object, which allows
 *          that object to be used.
 */
typedef struct _devcrypto_state_ctx {
	void							*data;	/*!< Algorithm-specific context data. */
	const devcrypto_algorithm_t		*alg;	/*!< The algorithm associated with this context. */
} devcrypto_state_ctx_t;

/**** Plugin Handling ****/

/**
 * @brief Initialize a plugin
 * @details This function is called to initialize the plugin and any resources
 *          that it requires. If the plugin supports options, they are passed
 *          to it as a string using the @c devcrypto command line option @c -o
 *          (option).
 *
 * @param[in] opts The option string.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_plugin_op_init)(const char *opts);

/**
 * @brief Uninitialize a plugin
 */
typedef void (*devcrypto_plugin_op_uninit)(void);

/**
 * @brief Plugin global functions
 *
 * @details The @c devcrypto service calls these functions when it
 *          initializes or uninitializes a plugin.
 */
typedef struct _devcrypto_plugin_ops {
	uint16_t					version;	/*!< The plugin version. Always set to @c DEVCRYPTO_PLUGIN_VERSION. */
	devcrypto_plugin_op_init	init;		/*!< The plugin initialization function. */
	devcrypto_plugin_op_uninit	uninit;		/*!< The plugin uninitialization function. */
} devcrypto_plugin_ops_t;

/**** Digest Handling ****/

/**
 * @brief Initialize a digest algorithm state
 *
 * @param[in,out] sctx The state context.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_digest_op_init)(devcrypto_state_ctx_t *sctx);

/**
 * @brief Update a digest algorithm state
 *
 * @param[in,out] sctx The state context.
 * @param[in] data The data buffer to digest.
 * @param[in] size The data buffer size.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_digest_op_update)(devcrypto_state_ctx_t *sctx, const uint8_t *data, uint32_t size);

/**
 * @brief Finalize a digest algorithm state
 *
 * @param[in,out] sctx The state context.
 * @param[out] digest The digest buffer.
 * @param[in,out] size The size of the digest buffer and the final digest.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_digest_op_final)(devcrypto_state_ctx_t *sctx, uint8_t *digest, uint32_t *size);

/**
 * @brief Copy a digest algorithm state
 *
 * @param[in,out] ssctx The source state context.
 * @param[in,out] dsctx The destination state context.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_digest_op_copy)(devcrypto_state_ctx_t *ssctx, devcrypto_state_ctx_t *dsctx);

/**
 * @brief Digest algorithm functions
 */
typedef struct _devcrypto_digest_ops {
	devcrypto_digest_op_init	init;		/*!< The digest initialization function. */
	devcrypto_digest_op_update	update;		/*!< The digest update function. */
	devcrypto_digest_op_final	final;		/*!< The digest finalization function. */
	devcrypto_digest_op_copy	copy;		/*!< The digest copy state function. */
} devcrypto_digest_ops_t;

/**
 * @brief Digest algorithm parameters
 */
typedef struct _devcrypto_digest_params {
	uint32_t	digestsize;		/*!< The digest size in bytes. */
	uint32_t	blocksize;		/*!< The block size in bytes. */
} devcrypto_digest_params_t;

/**
 * @brief Digest algorithm object
 */
typedef struct _devcrypto_digest {
	devcrypto_digest_params_t	params;	/*!< The digest parameters. */
	devcrypto_digest_ops_t		ops;	/*!< The digest functions. */
} devcrypto_digest_t;

/**** MAC Handling ****/

/**
 * @brief Initialize a MAC algorithm state
 *
 * @param[in,out] sctx The state context.
 * @param[in] key The MAC key buffer.
 * @param[in] keysize The size of the MAC key buffer.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_mac_op_init)(devcrypto_state_ctx_t *sctx, const uint8_t *key, uint32_t keysize);

/**
 * @brief Update a MAC algorithm state
 *
 * @param[in,out] sctx The state context.
 * @param[in] data The data buffer to digest.
 * @param[in] size The data buffer size.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_mac_op_update)(devcrypto_state_ctx_t *sctx, const uint8_t *data, uint32_t size);

/**
 * @brief Finalize a MAC algorithm state
 *
 * @param[in,out] sctx The state context.
 * @param[out] mac The MAC buffer.
 * @param[in,out] size The size of the MAC buffer and final MAC.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_mac_op_final)(devcrypto_state_ctx_t *sctx, uint8_t *mac, uint32_t *size);

/**
 * @brief MAC algorithm functions
 */
typedef struct _devcrypto_mac_ops {
	devcrypto_mac_op_init		init;		/*!< The MAC initialization function. */
	devcrypto_mac_op_update		update;		/*!< The MAC encryption function. */
	devcrypto_mac_op_final		final;		/*!< The MAC finalization function. */
} devcrypto_mac_ops_t;

/**
 * @brief MAC algorithm parameters
 */
typedef struct _devcrypto_mac_params {
	uint32_t	tagsize;	/*!< The MAC tag size in bytes. */
} devcrypto_mac_params_t;

/**
 * @brief MAC algorithm object
 */
typedef struct _devcrypto_mac {
	devcrypto_mac_params_t	params;	/*!< The MAC parameters. */
	devcrypto_mac_ops_t		ops;	/*!< The MAC functions. */
} devcrypto_mac_t;

/**** Cipher Handling ****/

/**
 * @brief Initialize a cipher algorithm state
 *
 * @details Because @c devcrypto works using ciphers with no padding, plugins
 *          need to make sure that cipher padding is turned off. The caller
 *          is responsible for providing the cipher with padded and aligned data.
 *
 * @param[in,out] sctx The state context.
 * @param[in] key The cipher key.
 * @param[in] keysize The cipher key size.
 * @param[in] iv The initialization vector (IV).
 * @param[in] ivsize The IV size.
 * @param[in] encrypt Either @c 1 (encrypt function) or @c 0 (decrypt function).
 *
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_cipher_op_init)(devcrypto_state_ctx_t *sctx, const uint8_t *key, uint32_t keysize,
		const uint8_t *iv, uint32_t ivsize, int encrypt);

/**
 * @brief Encrypt data using the specified cipher algorithm state
 *
 * @param[in,out] sctx The state context.
 * @param[in] in The plaintext to encrypt.
 * @param[in] insize The size of the input buffer.
 * @param[out] out The encrypted plaintext (ciphertext).
 * @param[in,out] outsize The size of the output buffer and encrypted data.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_cipher_op_encrypt)(devcrypto_state_ctx_t *sctx, const uint8_t *in, uint32_t insize,
		uint8_t *out, uint32_t *outsize);

/**
 * @brief Decrypt data using the specified cipher algorithm state
 *
 * @param[in,out] sctx The state context.
 * @param[in] in The ciphertext to decrypt.
 * @param[in] insize The size of the input buffer.
 * @param[out] out The decrypted ciphertext (plaintext).
 * @param[in,out] outsize The size of the output buffer and decrypted data.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_cipher_op_decrypt)(devcrypto_state_ctx_t *sctx, const uint8_t *in, uint32_t insize,
		uint8_t *out, uint32_t *outsize);

/**
 * @brief Cipher algorithm functions
 */
typedef struct _devcrypto_cipher_ops {
	devcrypto_cipher_op_init		init;		/*!< The cipher initialization function. */
	devcrypto_cipher_op_encrypt		encrypt;	/*!< The cipher encryption function. */
	devcrypto_cipher_op_decrypt		decrypt;	/*!< The cipher decryption function. */
} devcrypto_cipher_ops_t;

/**
 * @brief Cipher algorithm parameters
 */
typedef struct _devcrypto_cipher_params {
	uint32_t	minkeysize;		/*!< The minimum key size in bytes. */
	uint32_t	maxkeysize;		/*!< The maximum key size in bytes. */
	uint32_t	ivsize;			/*!< The default initialization vector (IV) size in bytes. */
	uint32_t	blocksize;		/*!< The cipher block size in bytes. */
} devcrypto_cipher_params_t;

/**
 * @brief Cipher algorithm object
 */
typedef struct _devcrypto_cipher {
	devcrypto_cipher_params_t	params;	/*!< The cipher parameters. */
	devcrypto_cipher_ops_t		ops;	/*!< The cipher functions. */
} devcrypto_cipher_t;

/**** AEAD Cipher Handling ****/

/**
 * @brief Initialize an AEAD cipher algorithm state
 *
 * @details Because @c devcrypto works using ciphers with no padding, plugins
 *          need to make sure that cipher padding is turned off. The caller
 *          is responsible for providing the cipher with padded and aligned data.
 *
 *          The @c insize argument is only used for algorithms that require
 *          that the plaintext size be known before encryption or decryption
 *          can begin (e.g., AES-CCM). This requirement also means the algorithm
 *          must encrypt or decrypt all the data in a single operation.
 *
 *          The @c tag argument is only used for algorithms that require
 *          the tag to be input before decryption can begin (e.g., AES-CCM).
 *
 * @param[in,out] sctx The state context.
 * @param[in] key The cipher key.
 * @param[in] keysize The size of the cipher key.
 * @param[in] iv The initialization vector (IV) buffer.
 * @param[in] ivsize The size of the IV buffer.
 * @param[in] tag The tag value (only used for decryption).
 * @param[in] tagsize The size of the tag buffer.
 * @param[in] insize The size of the input data to encrypt or decrypt.
 * @param[in] encrypt Either @c 1 (encrypt function) or @c 0 (decrypt function).
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_aead_cipher_op_init)(devcrypto_state_ctx_t *sctx, const uint8_t *key, uint32_t keysize,
		const uint8_t *iv, uint32_t ivsize, uint8_t *tag, uint32_t tagsize, uint32_t insize, int encrypt);

/**
 * @brief Encrypt data using the specified AEAD cipher algorithm state
 *
 * @param[in,out] sctx The state context.
 * @param[in] in The plaintext buffer to encrypt.
 * @param[in] insize The size of the input buffer.
 * @param[in] aad The Additional Authentication Data (AAD) buffer.
 * @param[in] aadsize The AAD buffer size.
 * @param[out] tag The tag value produced by encryption.
 * @param[in] tagsize The size of the tag buffer.
 * @param[out] out The encrypted plaintext (ciphertext).
 * @param[in,out] outsize The size of the output buffer and the encrypted data.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_aead_cipher_op_encrypt)(devcrypto_state_ctx_t *sctx, const uint8_t *in, uint32_t insize,
		uint8_t *aad, uint32_t aadsize, uint8_t *tag, uint32_t tagsize, uint8_t *out, uint32_t *outsize);

/**
 * @brief Decrypt data using the specified AEAD cipher algorithm state
 *
 * @details Some algorithms (e.g., AES-CCM) require the @c tag value in the initialization phase.
 *
 * @param[in,out] sctx The state context.
 * @param[in] in The ciphertext buffer to decrypt.
 * @param[in] insize The size of the input buffer.
 * @param[in] aad The Additional Authentication Data (AAD) buffer.
 * @param[in] aadsize The size of the AAD buffer.
 * @param[in] tag The tag value to use for decryption and verification.
 * @param[in] tagsize The size of the tag buffer.
 * @param[out] out The decrypted ciphertext (plaintext).
 * @param[in,out] outsize The size of the output buffer and the decrypted data.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
typedef int (*devcrypto_aead_cipher_op_decrypt)(devcrypto_state_ctx_t *sctx, const uint8_t *in, uint32_t insize,
		uint8_t *aad, uint32_t aadsize, uint8_t *tag, uint32_t tagsize, uint8_t *out, uint32_t *outsize);

/**
 * @brief AEAD cipher algorithm functions
 */
typedef struct _devcrypto_aead_cipher_ops {
	devcrypto_aead_cipher_op_init		init;		/*!< The cipher initialization function. */
	devcrypto_aead_cipher_op_encrypt	encrypt;	/*!< The cipher encryption function. */
	devcrypto_aead_cipher_op_decrypt	decrypt;	/*!< The cipher decryption function. */
} devcrypto_aead_cipher_ops_t;

/**
 * @brief AEAD cipher algorithm parameters
 */
typedef struct _devcrypto_aead_cipher_params {
	uint32_t	minkeysize;		/*!< The minimum key size in bytes. */
	uint32_t	maxkeysize;		/*!< The maximum key size in bytes. */
	uint32_t	ivsize;			/*!< The default initialization vector (IV) size in bytes. */
	uint32_t	mintagsize;		/*!< The minimum tag size in bytes. */
	uint32_t	maxtagsize;		/*!< The maximum tag size in bytes. */
	uint32_t	blocksize;		/*!< The size of the cipher block in bytes. */
} devcrypto_aead_cipher_params_t;

/**
 * @brief AEAD cipher algorithm object
 */
typedef struct _devcrypto_aead_cipher {
	devcrypto_aead_cipher_params_t	params;		/*!< The authenticated encryption with associated data (AEAD) cipher parameters. */
	devcrypto_aead_cipher_ops_t		ops;		/*!< The AEAD cipher functions. */
} devcrypto_aead_cipher_t;

/**** Algorithm Handling ****/

/**
 * @brief Algorithm types
 *
 * @see devcrypto_algorithm_t
 */
typedef enum {
	DEVCRYPTO_UNKNOWN_TYPE = 0,	/*!< Unknown algorithm. */
	DEVCRYPTO_DIGEST_TYPE,		/*!< Digest algorithm. */
	DEVCRYPTO_CIPHER_TYPE,		/*!< Cipher algorithm. */
	DEVCRYPTO_AEAD_CIPHER_TYPE,	/*!< AEAD cipher algorithm. */
	DEVCRYPTO_MAC_TYPE,			/*!< MAC algorithm. */
} devcrypto_algorithm_type_t;

/**
 * @brief Initialize an algorithm
 *
 * @details This function is called when an algorithm is requested
 *          to allow plugins to allocate resources and prepare the
 *          algorithm for use.
 *
 * @param[in,out] sctx The state context.
 *
 * @return EOK if successful or @c errno if an error occurred.

 */
typedef int (*devcrypto_algorithm_op_init)(devcrypto_state_ctx_t *sctx);

/**
 * @brief Uninitialize an algorithm
 *
 * @details This function signals that the user has released
 *          the algorithm object and the plugin can clean
 *          up the resources associated with it.
 *
 * @param[in,out] sctx The state context.
 *
 */
typedef void (*devcrypto_algorithm_op_uninit)(devcrypto_state_ctx_t *sctx);

/**
 * @brief Maximum size of the plugin name, including the NUL terminator.
 */
#define DEVCRYPTO_ALG_NAME_MAX	32

/**
 * @brief Algorithm object
 */
typedef struct _devcrypto_algorithm {
	const char						name[DEVCRYPTO_ALG_NAME_MAX];	/*!< The algorithm name. */
	uint32_t						type;							/*!< The algorithm type. @see devcrypto_algorithm_type_t */
	union {
		devcrypto_digest_t			digest;							/*!< The digest algorithm object. */
		devcrypto_cipher_t			cipher;							/*!< The cipher algorithm object. */
		devcrypto_aead_cipher_t		aead_cipher;					/*!< The authenticated encryption with associated data (AEAD) cipher algorithm object. */
		devcrypto_mac_t				mac;							/*!< The MAC algorithm object. */
	};
	devcrypto_algorithm_op_init		init;							/*!< The algorithm initialization function. */
	devcrypto_algorithm_op_uninit	uninit;							/*!< The algorithm uninitialization function. */
	void							*extra;							/*!< Extra storage for plugin use. */
} devcrypto_algorithm_t;

/**
 * @brief Register an algorithm
 *
 * @param[in] alg The algorithm object.
 *
 * @return EOK if successful or @c errno if an error occurred.
 */
extern int devcrypto_plugin_register_algorithm(const devcrypto_algorithm_t *alg);

/** @cond */
__END_DECLS
/** @endcond */

#endif /* _CRYPTO_DEVCRYPTO_PLUGIN_H_INCLUDED */
