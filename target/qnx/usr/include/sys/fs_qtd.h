/*
 * Copyright 2018-2021, Blackberry Limited. All Rights Reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef LIBQTD_SYS_FS_QTD_H_INCLUDED_
#define LIBQTD_SYS_FS_QTD_H_INCLUDED_

#include <inttypes.h>
#include <unistd.h>

#include <sys/cdefs.h>

__BEGIN_DECLS

#define QTD_SUPERBLOCK_MAGIC	0xc5c6c7c8u
#define QTD_SUPERBLOCK_VERSION	0x1u
#define QTD_SUPERBLOCK_SIZE		4096u
#define QTD_SALT_MAX_SIZE		128u		/* 2x size of max digest size */
#define QTD_DIGEST_MAX_SIZE		64u			/* maximum supported digest length */
#define QTD_LEVELS_MAX			10u			/* Max number of merkle tree levels */
#define QTD_BLOCKSIZE_MIN		512u			/* minimum block size */
#define QTD_BLOCKSIZE_MAX		131072u		/* maximum block size */

/*
 * Signature Algorithms
 */
#define QTD_SIG_INVALID         0u /* trap invalid sig types */
#define QTD_SIG_RSAWITHSHA256   1u /* RSA with SHA256 */
#define QTD_SIG_ECDSAWITHSHA256 2u /* ECDSA with SHA256 */
#define QTD_SIG_EDDSA_25519     3u /* EdDSA with ED25519 */
#define QTD_SIG_EDDSA_448       4u /* EdDSA with ED448 */
#define QTD_SIG_ECDSAWITHSHA384 5u /* ECDSA with SHA384 */
#define QTD_SIG_ECDSAWITHSHA512 6u /* ECDSA with SHA512 */
#define QTD_SIG_MAX             7u

/*
 * Hash Algorithms
 */
#define QTD_HASH_INVALID     0u /* Trap invalid hash values */
#define QTD_HASH_SHA1        1u
#define QTD_HASH_SHA256      2u
#define QTD_HASH_SHA512      3u
#define QTD_HASH_SHA512_256  4u
#define QTD_HASH_BLAKE2S256  5u
#define QTD_HASH_BLAKE2B256  6u
#define QTD_HASH_BLAKE2B512  7u
#define QTD_HASH_BLAKE3      8u
#define QTD_HASH_MAX         9u

/*
 * Option Flags
 */
#define QTD_PARTITION_MODE 0x01u /* full partition mode */

/*
 * QTD Superblock
 */
typedef union __attribute__((__packed__)) qtd_superblock_s {
	struct {
		uint32_t				magic;								/* magic marker */
		uint32_t				version;							/* version */
		uint32_t				flags;								/* flags */
		uint32_t				blksize;							/* block size */
		uint32_t				hblksize;							/* hash block size */
		uint32_t				hashtype;							/* hash type */
		uint64_t				fssize;								/* total size of inner fs */
		uint64_t				totalsize;							/* whole image size covered by qtd */
		uint64_t				offset;								/* where the merkle meta data starts */
		uint32_t				sigtype;							/* sig type */
		uint32_t				saltsize;							/* salt size */
		uint8_t					salt[QTD_SALT_MAX_SIZE];			/* salt */
		uint64_t				rollback;							/* rollback version */
		uint32_t				pathtrust;							/* pathtrust trust field (unused) */
		uint8_t					roothash[QTD_DIGEST_MAX_SIZE];		/* root hash */
		uint32_t				sigsize;							/* signature size */
		uint8_t					sig[0];								/* signature */
	};
	char						filler[QTD_SUPERBLOCK_SIZE];
} qtd_superblock_t;

_Static_assert(sizeof(qtd_superblock_t) == QTD_SUPERBLOCK_SIZE, "Invalid superblock size");

__END_DECLS

#endif /* LIBQTD_SYS_FS_QTD_H_INCLUDED_ */
