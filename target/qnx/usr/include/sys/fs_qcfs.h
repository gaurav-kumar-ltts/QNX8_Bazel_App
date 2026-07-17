/*
 * Copyright (c) 2017-2019, 2024, BlackBerry Limited. All rights reserved.
 *
 * BlackBerry Limited and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation. Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from BlackBerry Limited
 * is strictly prohibited.
 */

#ifndef LIBQCFS_FS_QCFS_H_INCLUDED_
#define LIBQCFS_FS_QCFS_H_INCLUDED_

#include <inttypes.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/cdefs.h>

__BEGIN_DECLS

/* QCFS Filesystem MAX values (pathconf) */
#define QCFS_NAME_MAX			255u
#define QCFS_DIR_LINK_MAX		USHRT_MAX
#define QCFS_SYMLINK_MAX		QCFS_NAME_MAX
#define QCFS_PATH_MAX			PATH_MAX
#define QCFS_MAX_FSIZE			(1u<<48)	/* ~256TiB */

/* Root inode number */
#define QCFS_ROOT_INODE			1u

/*
 * Compression algorithms
 */
#define QCFS_COMP_NONE  0u /* no compression */
#define QCFS_COMP_LZ4HC 1u /* LZ4 high compression */
#define QCFS_COMP_ZSTD  2u /* ZStandard */
#define QCFS_COMP_NUM   3u /* maximum value */

/* Magic constants */

#define QCFS_SUPERBLOCK_MAGIC		0xB1FFBAFFu
#define QCFS_SUPERBLOCK_VERSION		0x00000001u

#define QCFS_META_BLKSIZE_MIN		4096u		/* 4KiB */
#define QCFS_META_BLKSIZE_MAX		16384u		/* 16KiB */

#define QCFS_COMP_BLKSIZE_MIN		16384u		/* 16KiB */
#define QCFS_COMP_BLKSIZE_MAX		1048576u	/* 1MiB */

/* bit set to 1 == compressed */
#define QCFS_DATA_COMPRESSED_BIT	((uint16_t)1 << 15)
/* bit set to 1 == sparse */
#define QCFS_DATA_SPARSE_BIT		((uint16_t)1 << 14)

#define QCFS_COMP_FLAGS_MASK		(0x000000000000FFFFu)

/* bit set to 1 == compressed */
#define QCFS_META_COMPRESSED_BIT	((uint16_t)1 << 15)
#define QCFS_META_SIZE_MASK			(0x7FFFu)
#define QCFS_META_ADDR_OFFSET_MASK	(0xFFFFu)

#define QCFS_INVALID_FRAGMENT		(0xFFFFFFFFu)

/*
 * Compressed Data Block Types
 *
 * Compressed data blocks addresses are split in 2 parts.
 *
 * The lower 16 bits store flags related to the data block;
 *
 * The least significant bit (0) will store whether the
 * block is compressed or not (1 = compressed)
 *
 * The second least significant bit (1) will store whether
 * the block is sparse or not (1 = sparse)
 *
 * The upper 48 bits is the address where the data block starts;
 *
 * A sparse data block has the same address as the next block but
 * with the bit indicator saying that it's sparse and its size is
 * zero on disk
 *
 * The size of a data block is derived from the difference of
 * the following block minus the current block.
 *
 * Data blocks have an upper limit of 16MiB because file
 * fragments are expressed as qcfs_meta_addr_t types (see below)
 */
typedef uint64_t	qcfs_data_addr_t;

/*
 * Meta Data Address Type
 *
 * Meta data addresses point to a meta data compressed
 * block address (upper 48 bits) and include an offset
 * into that block (lower 16 bits) pointing to where the
 * data starts inside the uncompressed block
 *
 * Meta data is everything related to the different
 * types of inodes found in the filesystem (files,
 * dirs, links, etc.). Each of these inode structures
 * differ in size.
 *
 * Note: meta data items are packed and can overlap 2
 * separate meta data blocks to avoid empty space to
 * maximize compression.
 *
 * Meta data uncompressed size is limited to 16KiB (highest power of 2 that can
 * be represented by the lower 15 bits) because the msb is used to indicate if
 * the meta data block is compressed or not (1 = compressed)
 *
 * Note: Meta addresses in inode, directory and fragment tables are
 * always relative to the beginning of that table
 */
typedef uint64_t	qcfs_meta_addr_t;
typedef uint16_t	qcfs_meta_header_t;

/*
 * QCFS Compressor Options
 */
typedef union __attribute__((__packed__)) {
	struct {
		int32_t lvl;
	} lz4hc;
	struct {
		int32_t lvl;
	} zstd;
} qcfs_compressor_opt_t;

/*
 * QCFS Superblock
 *
 * Superblock is 4KiB in size for alignment reasons
 * filled with empty
 *
 * The root inode address is where to get the first
 * inode information from which everything else
 * follows
 *
 */
#define QFCS_SUPERBLOCK_SIZE	4096u

typedef union __attribute__((__packed__)) qcfs_superblock_s {
	struct {
		uint32_t				magic;				/* magic marker */
		uint32_t				version;			/* version */
		uint32_t				flags;				/* qcfs options */
		uint16_t				compressor;			/* compressor type */
		uint16_t				metablksize;		/* meta data uncompressed block size as power of 2 (see QCFS_META_BLKSIZE_*) */
		uint32_t				compblksize;		/* file data uncompressed block size as power of 2 (see QCFS_COMP_BLKSIZE_*) */
		uint32_t				blksize;			/* system reported block size */
		uint32_t				inodes;				/* number of inodes in fs */
		uint64_t				compblocks;			/* number of compressed data/fragment blocks in fs */
		uint64_t				metablocks;			/* number of compressed meta blocks in fs */
		uint32_t				fragments;			/* number of fragments in fragment table */
		uint32_t				dentry_groupsize;	/* maximum number of dentry index groups */
		uint64_t				totalsize;			/* total filesystem size */
		qcfs_data_addr_t		root_inode;			/* root inode meta block address */
		qcfs_data_addr_t		data_start;			/* where the compressed data blocks start */
		qcfs_data_addr_t		inode_table;		/* inode table start address */
		qcfs_data_addr_t		directory_table;	/* directory table start address */
		qcfs_data_addr_t		fragment_table;		/* fragment table start address */
		qcfs_compressor_opt_t	compopts;			/* compressor options */
	};
	char						filler[QFCS_SUPERBLOCK_SIZE];
} qcfs_superblock_t;

/* static size check to make sure that the superblock is of proper size */
_Static_assert(sizeof(qcfs_superblock_t) == QFCS_SUPERBLOCK_SIZE,"Superblock is not of expected size");

/*
 * QCFS Disk Format
 *
 * ***********************************
 * *           SUPERBLOCK            *
 * ***********************************
 * *          DATA BLOCKS            *
 * ***********************************
 * *          INODE INDEX            *
 * ***********************************
 * *          INODE TABLE            *
 * ***********************************
 * *        DIRECTORY TABLE          *
 * ***********************************
 * *        FRAGMENT INDEX           *
 * ***********************************
 * *      FRAGMENT DATA BLOCKS       *
 * ***********************************
 */

/*
 * Inode Data Structures
 *
 * Each inode contains an identical base
 * inode structure and then adds the extras
 * it needs to fulfill its role
 */

/*
 * File fragment entry
 *
 * file fragments are packed and compressed
 * together in compressed data blocks and an entry
 * is added to the fragment entry index in the
 * fragment table
 *
 * The inode contains the fragment index number which
 * after lookup gives the location of the compressed data
 * block and offset within that data block where the fragment
 * is stored
 *
 * The fragment table contains N+1 fragments (need an ending block
 * to calculate the fragment size as addr X+1 - X)
 */
typedef struct __attribute__((__packed__)) qcfs_fragment_entry_s {
	qcfs_data_addr_t	start;	/* addr of fragment block relative to fragments start */
} qcfs_fragment_entry_t;

/*
 * Inode base
 *
 * NOTES: QNX uses 4 bytes for mode_t while other platforms may or not be 4 bytes so
 * use uint32_t instead of mode_t
 */
typedef struct __attribute__((__packed__)) qcfs_inode_base_s {
	uint32_t	mode;		/* inode permissions + type */
	uint32_t	uid;		/* inode uid */
	uint32_t	gid;		/* inode gid */
	uint32_t	mtime;		/* inode creation time */
	uint32_t	ino;		/* inode number */
	uint32_t	nlink;		/* number of hardlinks */
	uint32_t	aclsize;	/* inode aclsize */
	uint32_t	isize;		/* inode total size */
} qcfs_inode_base_t;


/*
 * File inode
 *
 * file inodes have an index for the fragment as well as a list of data blocks
 * of size N+1 which are sequential. blocks[0] is where the file data starts. blocks[N+1]
 * points to the next file's blocks[0]. This information is used to quickly locate
 * where to read data from and what is the total size to read for the current block
 * as a diff between blocks[N] and blocks[N+1], and is why we store an extra block
 * address.
 */
typedef struct __attribute__((__packed__)) qcfs_inode_file_s {
	qcfs_inode_base_t		base;		/* base inode */
	uint64_t				size;		/* file size */
	uint32_t				frag;		/* fragment offset in fragment index */
	uint32_t				frag_off;	/* fragment offset within fragment block */
	qcfs_data_addr_t		blocks[];	/* file data block list */
	/* uint8_t					acl[]	file acl data */
} qcfs_inode_file_t;

/*
 * Directories
 *
 * directory inodes have a directory index to speed up directory searching
 * when they contain many children inodes
 *
 * Directory entries are stored in a directory table where each
 * meta data block is compressed
 *
 * The goal of the algorithm is to balance the number of directory entries accounted
 * for each directory index. The equation to be resolved is basically
 *
 * nchildren = lpidx*nlpidx + upidx*nupidx
 *
 * nidx = number of index entries to add
 * lpidx = lower bound dir entries per index
 * upidx = upper bound dir entries per index
 * nlpidx = number of times a dir index will contain lpidx entries
 * nupidx = number of times a dir index will contain upidx entries
 *
 * For example, suppose we have 81 children and the minimum amount of children for a directory
 * index to be added is 20.
 *
 * nidx = ceil(81/20) = 5
 * lpidx = 81/5 = 16
 * upidx = ceil(81/5) = 17
 * nlpidx = 17*5 - 81 = 4
 * nupidx = 5 - 4 = 1
 *
 * 16 + 16 + 16 + 16 + 17 = 81
 *
 * This is to avoid having an unbalanced index which will slow searching for folder entries in large
 * folders.
 *
 * With the above example, if we simply cut an index every 20, the last entry would only cover 1 item
 *
 * 20 + 20 + 20 + 20 + 1 = 81
 *
 * These counts are stored within the directory index entry so that the filesystem driver
 * knows how many directory entries are found between directory index locations when searching
 * for the matching directory entry.
 *
 * NOTE: there is no directory index for the first group of directory entries, it's implicitly contained
 * in the directory inode data structure.
 *
 * The minimum value is stored in the superblock as 'dentry_groupsize' but only used to construct the
 * filesystem itself. The fs driver doesn't need the value to know where the data is located.
 *
 */

/*
 * Directory index entry
 */
typedef struct __attribute__((__packed__)) qcfs_dir_index_s {
	qcfs_meta_addr_t	start;		/* directory entry address (inside the meta block) */
	uint16_t			count;		/* number of directory entries covering this index element */
	uint16_t			size;		/* name size */
	char				name[];		/* name of directory entry */
} qcfs_dir_index_t;

/*
 * Directory entry
 *
 * Many of these are packed together and form the entries
 * under a folder.
 *
 * There are stored packed and compressed in the directory table
 */
typedef struct __attribute__((__packed__)) qcfs_dir_entry_s {
	uint32_t			ino;		/* inode number */
	uint16_t			type;		/* entry type (S_IFREG, S_IFDIR, etc.) */
	uint16_t			size;		/* name size */
	char				name[];		/* entry name */
} qcfs_dir_entry_t;

/*
 * Directory inode
 */
typedef struct __attribute__((__packed__)) qcfs_inode_dir_s {
	qcfs_inode_base_t	base;			/* base inode */
	qcfs_meta_addr_t	start;			/* directory listing start in directory table */
	uint32_t			nchildren;		/* children count (number of directory entries) */
	uint32_t			parent_ino;		/* parent inode number */
	uint32_t			size;			/* directory size (size of dir entries) */
	uint16_t			count;			/* first dir entry group size */
	uint16_t			index_count;	/* number of directory index entries */
	qcfs_dir_index_t	index[];		/* directory index */
	/* uint8_t					acl[]	directory acl data */
} qcfs_inode_dir_t;

/*
 * Link inode
 */
typedef struct __attribute__((__packed__)) qcfs_inode_link_s {
	qcfs_inode_base_t	base;		/* base inode */
	char				path[];		/* symlink path - non NUL-terminated */
} qcfs_inode_link_t;

/*
 * Hardlink inode
 *
 * Hardlinks only have a named entry in a dir inode
 * and an address to the file inode it references
 */

__END_DECLS

#endif /* LIBQCFS_FS_QCFS_H_INCLUDED_ */
