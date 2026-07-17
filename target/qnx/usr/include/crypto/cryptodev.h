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
 * @file cryptodev.h
 * @brief /dev/crypto standard API
 *
 * This file defines the crypto device ioctl API
 */

#ifndef _CRYPTO_CRYPTODEV_H_INCLUDED
#define _CRYPTO_CRYPTODEV_H_INCLUDED

#include <sys/cdefs.h>
#include <inttypes.h>

/** @cond */
__BEGIN_DECLS
/** @endcond */

/**
 * @brief Maximum algorithm result length.
 */
#define AALG_MAX_RESULT_LEN		64

/**
 * @brief Maximum hash algorithm result length.
 */
#define HASH_MAX_LEN			AALG_MAX_RESULT_LEN

/**
 * @brief Maximum HMAC key length.
 */
#define CRYPTO_HMAC_MAX_KEY_LEN		512

/**
 * @brief Maximum cipher key length.
 */
#define CRYPTO_CIPHER_MAX_KEY_LEN	64

/**
 * @defgroup CRYPTO_ALGS Cryptography device algorithms
 *
 * Algorithms supported by the cryptography device. See @c #cryptodev_session_op_t.
 *
 * @{
 */
#define CRYPTO_INVALID				0
#define CRYPTO_DES_CBC				1
#define CRYPTO_3DES_CBC				2
#define CRYPTO_BLF_CBC				3
#define CRYPTO_CAST_CBC				4
#define CRYPTO_SKIPJACK_CBC			5
#define CRYPTO_MD5_HMAC				6
#define CRYPTO_SHA1_HMAC			7
#define CRYPTO_RIPEMD160_HMAC		8
#define CRYPTO_MD5_KPDK				9
#define CRYPTO_SHA1_KPDK			10
#define CRYPTO_RIJNDAEL128_CBC		11
#define CRYPTO_AES_CBC				CRYPTO_RIJNDAEL128_CBC
#define CRYPTO_ARC4					12
#define CRYPTO_MD5					13
#define CRYPTO_SHA1					14
#define CRYPTO_SHA2_256_HMAC		15
/**
 * @brief Defines an alternative algorithm name to allow backwards compatibility.
 */
#define CRYPTO_SHA2_HMAC			CRYPTO_SHA2_256_HMAC
/**
 * @brief Defines an alternative algorithm name to allow backwards compatibility.
 */
#define CRYPTO_SHA256_HMAC			CRYPTO_SHA2_256_HMAC
#define CRYPTO_NULL_HMAC			16
#define CRYPTO_NULL_CBC				17
#define CRYPTO_DEFLATE_COMP			18
#define CRYPTO_MD5_HMAC_96			19
#define CRYPTO_SHA1_HMAC_96			20
#define CRYPTO_RIPEMD160_HMAC_96	21
#define CRYPTO_GZIP_COMP			22
#define CRYPTO_DEFLATE_COMP_NOGROW	23
#define CRYPTO_SHA2_384_HMAC		24
/**
 * @brief Defines an alternative algorithm name to allow backwards compatibility.
 */
#define CRYPTO_SHA384_HMAC			CRYPTO_SHA2_384_HMAC
#define CRYPTO_SHA2_512_HMAC		25
/**
 * @brief Defines an alternative algorithm name to allow backwards compatibility.
 */
#define CRYPTO_SHA512_HMAC			CRYPTO_SHA2_512_HMAC
#define CRYPTO_CAMELLIA_CBC			26
#define CRYPTO_AES_CTR				27
#define CRYPTO_AES_XCBC_MAC_96		28
/**
 * @brief Defines an alternative algorithm name to allow backwards compatibility.
 */
#define CRYPTO_AES_XCBC_MAC			CRYPTO_AES_XCBC_MAC_96
#define CRYPTO_AES_GCM_16			29
#define CRYPTO_AES_128_GMAC			30
#define CRYPTO_AES_192_GMAC			31
#define CRYPTO_AES_256_GMAC			32
#define CRYPTO_AES_GMAC				33
#define CRYPTO_SHA2_224				34
/**
 * @brief Defines an alternative algorithm name to allow backwards compatibility.
 */
#define CRYPTO_SHA224				CRYPTO_SHA2_224
#define CRYPTO_SHA2_256				35
/**
 * @brief Defines an alternative algorithm name to allow backwards compatibility.
 */
#define CRYPTO_SHA256				CRYPTO_SHA2_256
#define CRYPTO_SHA2_384				36
/**
 * @brief Defines an alternative algorithm name to allow backwards compatibility.
 */
#define CRYPTO_SHA384				CRYPTO_SHA2_384
#define CRYPTO_SHA2_512				37
/**
 * @brief Defines an alternative algorithm name to allow backwards compatibility.
 */
#define CRYPTO_SHA512				CRYPTO_SHA2_512
#define CRYPTO_SHA2_224_HMAC		38
/**
 * @brief Defines an alternative algorithm name to allow backwards compatibility.
 */
#define CRYPTO_SHA224_HMAC			CRYPTO_SHA2_224_HMAC
#define CRYPTO_AES_XTS				39
#define CRYPTO_AES_ECB				40
#define CRYPTO_AES_GCM				41
#define CRYPTO_SHA512_224			42
#define CRYPTO_SHA512_256			43
#define CRYPTO_SHA512_224_HMAC		44
#define CRYPTO_SHA512_256_HMAC		45
#define CRYPTO_AES_CCM			46
#define CRYPTO_AES_CCM8_CBC_MAC_128	47
#define CRYPTO_AES_CCM8_CBC_MAC_192	48
#define CRYPTO_AES_CCM8_CBC_MAC_256	49
#define CRYPTO_AES_CCM16_CBC_MAC_128	50
#define CRYPTO_AES_CCM16_CBC_MAC_192	51
#define CRYPTO_AES_CCM16_CBC_MAC_256	52
#define CRYPTO_AES_CMAC			53
#define CRYPTO_ESN			54	/* support for extended sequence numbers */
#define CRYPTO_ALGORITHM_ALL		55
#define CRYPTO_ALGORITHM_MIN		(CRYPTO_INVALID + 1)
#define CRYPTO_ALGORITHM_MAX		(CRYPTO_ALGORITHM_ALL - 1)
/** @} */

/**
 * @brief Check if an algorithm is valid
 */
#define	CRYPTO_ALGORITHM_VALID(x)	(((x) >= CRYPTO_ALGORITHM_MIN) && ((x) <= CRYPTO_ALGORITHM_MAX))

/**
 * @defgroup CRYPTO_OPS Cryptography device operations
 *
 * Operations executed using ciphers. See @c #cryptodev_crypt_op_t.
 *
 * @{
 */
#define COP_ENCRYPT		0x0		/*!< Encrypt operation. */
#define COP_DECRYPT		0x1		/*!< Decrypt operation. */
/** @} */

/**
 * @brief CIOCGSESSION command
 *
 * This command is used to initiate a session with @c devcrypto
 * by specifying the algorithm a client wants to use.
 *
 * If @c devcrypto doesn't support this algorithm,
 * the @e ioctl() call returns -1 and errno is set to
 * ENOTSUP. Any other error means that the cryptography
 * device encountered another error internally.
 *
 * Only specific combinations of MAC and ciphers are valid.
 */
typedef struct session_op {
	uint32_t	cipher;		/*!< The cipher algorithm. See @ref CRYPTO_ALGS. */
	uint32_t	mac;		/*!< The MAC algorithm. See @ref CRYPTO_ALGS. */
	uint32_t	keylen;		/*!< The cipher key length. */
	uint8_t		*key;		/*!< The cipher key. */
	uint32_t	mackeylen;	/*!< The MAC key length. */
	uint8_t		*mackey;	/*!< The MAC key. */
	uint64_t	ses;		/*!< The session identifier. */
} cryptodev_session_op_t;

/**
 * @defgroup CRYPTO_OP_FLAGS Cryptography device CIOCCRYPT command flags
 *
 * Flags that affect how the cryptography operation is handled
 *
 * Only digest or MAC operations support the @c COP_FLAG_UPDATE and @c COP_FLAG_FINAL
 * flags. See @c #cryptodev_crypt_op_t.
 *
 * @{
 */
#define COP_FLAG_NONE		(0 << 0) /*!< No flag. */
#define COP_FLAG_UPDATE		(1 << 0) /*!< Update to hash in a series of updates. */
#define COP_FLAG_FINAL		(1 << 1) /*!< Final update to hash in a series of updates. */
/** @} */

/**
 * @brief CIOCCRYPT command
 *
 * This command is used for the following cryptography operations:
 * - Ciphers (except AEAD, which is handled by @c #cryptodev_crypt_auth_op_t)
 * - Cipher and Message Authenticated Code (MAC) combinations
 * - Digests
 * - MAC
 *
 */
typedef struct crypt_op {
	uint64_t	ses;	/*!< The session identifier. See @c #cryptodev_session_op_t. */
	uint16_t	op;		/*!< COP_ENCRYPT or COP_DECRYPT. See @ref CRYPTO_OPS. */
	uint16_t	flags;	/*!< See @ref CRYPTO_OP_FLAGS. */
	uint32_t	len;	/*!< The input or output data length. */
	uint8_t		*src;	/*!< The input data buffer. */
	uint8_t		*dst;	/*!< The output data buffer. */
	uint8_t		*mac;	/*!< The hash or MAC output buffer. */
	uint8_t		*iv;	/*!< The initialization vector for the encryption or decryption operation. */
} cryptodev_crypt_op_t;

/**
 * @defgroup UNUSED_FLAG Unused flags
 *
 * @{
 */
#define	CRYPTO_ALG_FLAG_SUPPORTED	1
#define	CRYPTO_ALG_FLAG_RNG_ENABLE	2
#define	CRYPTO_ALG_FLAG_DSA_SHA		4
/** @} */

/**
 * @brief unused
 *
 * @warning Unused
 */
typedef struct crparam {
	uint8_t		*crp_p;		/*!< unused */
	uint32_t	crp_nbits;	/*!< unused */
} cryptodev_cparam_t;

/**
 * @brief Maximum number of crypto key parameters
 */
#define CRK_MAXPARAM	8

/**
 * @brief CIOCKEY command
 *
 * @warning This command is not supported
 */
typedef struct crypt_kop {
	uint32_t		crk_op;						/*!< @see CRYPTO_KEY_OPS */
	uint32_t		crk_status;					/*!< unused */
	uint16_t		crk_iparams;				/*!< unused */
	uint16_t		crk_oparams;				/*!< unused */
	uint32_t		crk_pad1;					/*!< unused */
	struct crparam	crk_param[CRK_MAXPARAM];	/*!< unused */
} cryptodev_crypt_kop_t;

/**
 * @defgroup CRYPTO_KEY_OPS Supported asymmetric crypto operations
 *
 * @warning unused
 *
 * @see crypt_kop
 *
 * @{
 */
#define CRK_ALGORITHM_MIN	0
#define CRK_MOD_EXP			0
#define	CRK_MOD_EXP_CRT		1
#define CRK_DSA_SIGN		2
#define CRK_DSA_VERIFY		3
#define CRK_DH_COMPUTE_KEY	4
#define CRK_ALGORITHM_ALL	5
#define CRK_ALGORITHM_MAX	(CRK_ALGORITHM_ALL - 1)
/** @} */

/**
 * @defgroup CIOCASYMFEAT Supported asymmetric crypto features
 *
 * WARNING: The CIOCASYMFEAT command will always return
 * no support for any of these features
 *
 * @{
 */
#define CRF_MOD_EXP			(1 << CRK_MOD_EXP)
#define CRF_MOD_EXP_CRT		(1 << CRK_MOD_EXP_CRT)
#define CRF_DSA_SIGN		(1 << CRK_DSA_SIGN)
#define CRF_DSA_VERIFY		(1 << CRK_DSA_VERIFY)
#define CRF_DH_COMPUTE_KEY	(1 << CRK_DH_COMPUTE_KEY)
/** @} */

/**
 * @brief CIOCAUTHCRYPT command
 *
 * This command handles AEAD ciphers such as
 * AES-GCM.
 */
typedef struct crypt_auth_op {
	uint64_t	ses;		/*!< The session identifier. See @c #cryptodev_session_op_t. */
	uint16_t	op;			/*!< @c COP_ENCRYPT or @c COP_DECRYPT.  See @ref CRYPTO_OPS. */
	uint16_t	flags;		/*!< Reserved for future use. */
	uint32_t	len;		/*!< The input or output data length. */
	uint32_t	auth_len;	/*!< The length of the authenticated data. */
	uint8_t		*auth_src;	/*!< Additional authenticated data. */
	uint8_t		*src;		/*!< The input data buffer. */
	uint8_t		*dst;		/*!< The output data buffer. */
	uint8_t		*tag;		/*!< The tag input or output buffer. */
	uint32_t	tag_len;	/*!< The tag length. */
	uint8_t		*iv;		/*!< The initialization vector (IV). */
	uint32_t	iv_len;		/*!< The IV length. */
} cryptodev_crypt_auth_op_t;

/**
 * @brief CIOCCPHASH command
 *
 * @details This command copies a digest state
 *          from one session to another to continue the digest
 *          operation.
 */
typedef struct cphash_op {
	uint64_t	dst_ses;	/*!< The destination session. */
	uint64_t	src_ses;	/*!< The source session. */
} cphash_op_t;

/**
 * @defgroup CRYPTO_DEV_IOCTL Crypto device ioctl command identifiers
 *
 * WARNING: The CIOCASYMFEAT command will always return no support
 * for any features
 *
 * @{
 */
#define	CRIOGET			_IOWR('c', 100, uint32_t)
#define	CIOCGSESSION	_IOWR('c', 101, struct session_op)
#define	CIOCFSESSION	_IOW('c', 102, uint32_t)
#define CIOCCRYPT		_IOWR('c', 103, struct crypt_op)
#define CIOCKEY			_IOWR('c', 104, struct crypt_kop)
#define CIOCASYMFEAT	_IOR('c', 105, uint32_t)
#define CIOCAUTHCRYPT	_IOWR('c', 106, struct crypt_auth_op)
#define CIOCCPHASH		_IOW('c', 107, struct cphash_op)
/** @} */

/**
 * @brief CRIOGET command file descriptor duplicate flag.
 *
 * This flag indicates that to use the cryptography device 
 * for operations, a driver doesn't require the caller
 * to call ioctl(fd, CRIOGET, &dupfd) to get an extra file
 * descriptor.
 */
#define CRIOGET_NOT_NEEDED	1

/** @cond */
__END_DECLS
/** @endcond */

#endif /* _CRYPTO_CRYPTODEV_H_INCLUDED */
