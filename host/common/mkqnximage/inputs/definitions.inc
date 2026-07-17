--start-strip       # Avoid all the blank lines appearing in the output
#include "output/inc/options.inc"

#define __DEFAULT_PERMISSIONS__ [uid=0 gid=0 dperms=755 perms=644]

#if defined(OPT_UNION_no)
#define __IFS_PATH__ /ifs
#else
#define __IFS_PATH__ /proc/boot
#endif

#define __BIN_PATH__ bin

#if defined(OPT_ASLR_yes)
#define __ASLR_OPTION__ -mr
#else
#define __ASLR_OPTION__ -m~r
#endif

#define __IOPKT_TCPIP_OPTS__

#if defined(OPT_APS_yes)
#define __MODULE_APS__ module=aps__SAFETY__
#else
#define __MODULE_APS__
#endif

#if defined(OPT_SECURE_PROCFS_yes)
#define __SEC_PROCFS_OPTION__ -d 0777 -u 0777
#else
#define __SEC_PROCFS_OPTION__ -d 022 -u 066
#endif

#if defined(OPT_ABLELOCK_no)
#define __ABLE_OPTIONS__ -b~l
#else
#define __ABLE_OPTIONS__
#endif

#define __PROCNTO_OPTIONS__ __ASLR_OPTION__ __SEC_PROCFS_OPTION__ __ABLE_OPTIONS__

#if !defined(OPT_PROC_no)
#define __PROCNTO__ __OPT_PROC__
#else
#define __PROCNTO__ procnto-smp-instr
#endif

#define __PROC_PATH__ __IFS_PATH__:/system/bin
#if defined(OPT_GRAPHICS_yes)
#define __PROC_LIB__ __IFS_PATH__:/system/lib:/system/lib/dll:/system/graphics/driver
#else
#define __PROC_LIB__ __IFS_PATH__:/system/lib:/system/lib/dll
#endif

#define __DATA_MOUNT_PT__ /data
#define __DATA_PREFIX__

#if ! defined(OPT_SECPOL_no) || defined(OPT_ROOT_no)
#define SUBST_NP(__SUBST__) __SUBST__
#define DROPROOT_NP(__ID__) -U __ID__:__ID__
#define DROPROOT_SCREEN(__ID__) -u __ID__:__ID__
#else
#define SUBST_NP(__SUBST__)
#define DROPROOT_NP(user)
#define DROPROOT_SCREEN(__ID__)
#endif
#if ! defined(OPT_SECPOL_no)
#define SUBST_P(__SUBST__) __SUBST__
#define DROPROOT_P(__ID__) -U __ID__:__ID__
#else
#define SUBST_P(__SUBST__)
#define DROPROOT_P(__ID__)
#endif
#if defined(OPT_SECPOL_no) && defined(OPT_ROOT_no)
#define SUBST_N(__SUBST__) __SUBST__
#define DROPROOT_N(__ID__) -U __ID__:__ID__
#else
#define SUBST_N(sub)
#define DROPROOT_N(__ID__)
#endif

#define START_P(__TYPE__) SUBST_P(on -T __TYPE__)
#define STARTU_P(__TYPE__,__USER__) SUBST_P(on -T __TYPE__ -u __USER__:__USER__)
#define SLMTYPE_P(__TYPE__) SUBST_P(<SLM:type>__TYPE__</SLM:type>)
#define SLMUSER_P(__ID__)  SUBST_P(<SLM:user>__ID__:__ID__</SLM:user>)

#include "output/inc/_definitions.inc"
#include "inputs/filesystems.inc"

#if ! defined(__RANDOM_INTERUPT_ENTROPY__)
#define __RANDOM_INTERUPT_ENTROPY__
#endif

#if ! defined(__RANDOM_OTHER_ENTROPY__)
#define __RANDOM_OTHER_ENTROPY__
#endif

#if ! defined(__IOSOCK_OPTIONS__)
#define __IOSOCK_OPTIONS__
#endif

#if ! defined(__IOSOCK_QVM_OPTIONS__)
#define __IOSOCK_QVM_OPTIONS__
#endif

#if ! defined(__WIFIDRIVER__)
#define __WIFIDRIVER__
#endif

#if ! defined(__STARTUP_OPTS__)
#if defined OPT_BOOT_MODE_uefi
#define __STARTUP_OPTS__ -D3f8.115200
#else
#define __STARTUP_OPTS__
#endif
#endif

#if ! defined(__IFS_COMPRESS__)
#define __IFS_COMPRESS__
#endif

#if ! defined(__OPT_PART_SIZES__) || defined(OPT_PART_SIZES_full)
#define __NO_SYS_FS_EXPANSION__
#elif defined(OPT_QTD_yes) || defined(OPT_QTSAFEFS_yes) || ! defined(OPT_QCFS_no)
#define __NO_SYS_FS_EXPANSION__
#endif

--end-strip
