#!/bin/sh
#include "inputs/definitions.inc"

# Checks the magic number in the superblock to identify a file system
# check_magic <block-dev> <offset> <magic>
#    <block-dev>  Path to block device containing file system
#    <offset>     Offset to location of magic value in file system
#    <magic>      Expected value (constant reversed and expressed as an octal string)
function check_magic
{
	# Output everything to files and compare the files.
	dd if=$1 bs=1 skip=$2 count=4 >/dev/shmem/fs-magic1 2>/dev/null
	print -Re $3 >/dev/shmem/fs-magic2
	[ $(</dev/shmem/fs-magic1) = $(</dev/shmem/fs-magic2) ]
}


echo "---> Mounting file systems"

if [ -e /data -a -e /system ]; then
	exit 0
fi

#if defined(__OPT_PART_SIZES__) && ! defined(OPT_PART_SIZES_full)
# If a system image replaced the boot partition only, the size of the data
# partition might be wrong. So update it.
updatefs.sh
#endif

mount -t __BOOT_TYPE__ __BOOT_PART__ /boot
if [ -e /boot/onboot ]; then
	echo Running onboot script
	ksh /boot/onboot
fi


if [ -e __SYSTEM_PART_QTD__ ]; then
	# Mounting a QTD protected file system is a two step process.  First mount the QTD
	# container and then the file system contained within
	mount -t qtd -o key=__IFS_PATH__/qtd_public_key.pem __SYS_TRUST_OPT__ __SYSTEM_PART_QTD__ __SYSTEM_PART_QTD__-fs
	if check_magic __SYSTEM_PART_QTD__-fs 8192 "\0042\0021\0031\0150"; then
		mount -t qnx6 -o noatime __SYS_TRUST_OPT__ __SYSTEM_PART_QTD__-fs /system
	elif check_magic __SYSTEM_PART_QTD__-fs 0 "\0377\0272\0377\0261"; then
		mount -t qcfs __SYS_TRUST_OPT__ __SYSTEM_PART_QTD__-fs /system
	else
		echo "Don't recognise the filesystem"
	fi
	rm -f /dev/shmem/fs-magic*
elif [ -e __SYSTEM_PART_QTSAFEFS__ ]; then
    qtsafefsd -o key=__IFS_PATH__/qtsafefs_public_key.pem __SYS_TRUST_OPT__ __SYSTEM_PART_QTSAFEFS__ /system
elif [ -e __SYSTEM_PART_QCFS__ ]; then
	mount -t qcfs __SYS_TRUST_OPT__ __SYSTEM_PART_QCFS__ /system
else # QNX6
	mount -t qnx6 -o noatime __SYS_TRUST_OPT__ __SYSTEM_PART_QNX6__ /system __MOUNT_STDERR__
#if defined(__OPT_PART_SIZES__) && ! defined(OPT_PART_SIZES_full)
	# We've mounted the system file system opportunistically. If it appears that
	# it was in need of expansion, unmount, expand and remount.
	if [ ! -e /system/etc/build.date -o -e /system/needs_expansion ]; then
		umount /system 2>/dev/null
		expandfs.sh
		mount -t qnx6 -o noatime __SYS_TRUST_OPT__ __SYSTEM_PART_QNX6__ /system __MOUNT_STDERR__
		rm -f /system/needs_expansion
		touch /system/etc/build.date
		FS_EXPANDED=1
	fi
	# Perhaps this is really an installer partition.
	if [ -e /system/needs_install ]; then
		/system/installfs
	fi
#endif
fi


mount -t qnx6 __DATA_OPTIONS__ __DATA_PART__ __DATA_MOUNT_PT__ __MOUNT_STDERR__
#if defined(__OPT_PART_SIZES__) && ! defined(OPT_PART_SIZES_full)
# As for the system partition, the data partition might need expanding.
if [ ! -e /data/var/etc/build.date -o -e /data/needs_expansion ]; then
	if [ -z "${FS_EXPANDED}" ]; then
		umount /data 2>/dev/null
		expandfs.sh
		mount -t qnx6 __DATA_OPTIONS__ __DATA_PART__ __DATA_MOUNT_PT__ __MOUNT_STDERR__
	fi
	rm -f /data/needs_expansion
	touch /data/var/etc/build.date
fi
#endif

/system/bin/cleanup_tmp
