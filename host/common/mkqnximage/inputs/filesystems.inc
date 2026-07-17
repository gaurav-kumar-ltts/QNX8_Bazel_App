#if defined(IMAGE_TYPE_bios)
#define __BOOT_TYPE__ qnx6
#define __BOOT_PART__ /dev/hd0t177
#define __SYSTEM_PART_QTSAFEFS__ /dev/hd0t186
#define __SYSTEM_PART_QTD__ /dev/hd0t185
#define __SYSTEM_PART_QCFS__ /dev/hd0t181
#define __SYSTEM_PART_QNX6__ /dev/hd0t178
#define __DATA_PART__ /dev/hd0t179
#endif

#if defined(IMAGE_TYPE_uefi)
#define __BOOT_TYPE__ dos
#define __BOOT_PART__ /dev/hd0.efi.0
#define __SYSTEM_PART_QTSAFEFS__ /dev/hd0.qtsafefs.1
#define __SYSTEM_PART_QTD__ /dev/hd0.qtd.1
#define __SYSTEM_PART_QCFS__ /dev/hd0.qcfs.1
#define __SYSTEM_PART_QNX6__ /dev/hd0.qnx6.1
#define __DATA_PART__ /dev/hd0.qnx6.2
#endif

#if defined(IMAGE_TYPE_qemu)
#define __BOOT_TYPE__
#define __BOOT_PART__
#define __SYSTEM_PART_QTSAFEFS__ /dev/hd0t186
#define __SYSTEM_PART_QTD__ /dev/hd0t185
#define __SYSTEM_PART_QCFS__ /dev/hd0t181
#define __SYSTEM_PART_QNX6__ /dev/hd0t178
#define __DATA_PART__ /dev/hd0t179
#endif

#if defined(IMAGE_TYPE_other)
#define __BOOT_TYPE__ dos
#define __BOOT_PART__ /dev/hd0t12
#define __SYSTEM_PART_QTSAFEFS__ /dev/hd0t186
#define __SYSTEM_PART_QTD__ /dev/hd0t185
#define __SYSTEM_PART_QCFS__ /dev/hd0t181
#define __SYSTEM_PART_QNX6__ /dev/hd0t178
#define __DATA_PART__ /dev/hd0t179
#endif

#if ! defined(__SYS_TRUST_OPT__)
#define __SYS_TRUST_OPT__
#endif

#if ! defined(OPT_SECURE_DATA_no)
#define __DATA_OPTIONS__ -o __OPT_SECURE_DATA__
#else
#define __DATA_OPTIONS__
#endif

#if defined(__OPT_PART_SIZES__) && ! defined(OPT_PART_SIZES_full)
// If we're using expandable partitions, hide errors from first mount
#define __MOUNT_STDERR__ 2>/dev/null
#else
#define __MOUNT_STDERR__
#endif
