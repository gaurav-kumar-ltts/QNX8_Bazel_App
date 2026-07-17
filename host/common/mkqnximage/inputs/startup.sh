#!/bin/sh
#include "inputs/definitions.inc"
#include "inputs/uids.inc"

. __IFS_PATH__/build/options

# By default set umask so that services don't accidentally create group/world writable files.
umask 022

#if ! defined(OPT_PATHTRUST_no) && defined(OPT_SECPOL_no)
#define ALLOW_PATHTRUST on -A allow,all,lock,path_trust
#else
#define ALLOW_PATHTRUST
#endif

echo "---> Starting slogger2"
STARTU_P(slogger_t,__SLOGGER_ID__) slogger2 DROPROOT_N(__SLOGGER_ID__)
waitfor /dev/slog

echo "---> Starting PCI Services"
#if defined (__HAS_PCI__)
STARTU_P(pci_server_t,__PCI_SERVER_ID__) pci-server --aspace-enable --config=__IFS_PATH__/pci_server.cfg
waitfor /dev/pci/server_id_1
# Not ideal. Can't set ACLs. Perhaps supplementary groups would be better
chmod a+rx /dev/pci/server_id_1
#if ! defined(OPT_SECPOL_no)
chmod a+r /dev/shmem/pci/pci_db
setfacl -m user:__IO_USB_ID__:rw,user:__IO_SOCK_ID__:rw /dev/shmem/pci/pci_hw /dev/shmem/pci/pci_sync
#endif
#endif

#include "output/inc/_startup_postpci.inc"

#if defined (OPT_GRAPHICS_no)
#if ! defined(OPT_BOOT_MODE_uefi)
STARTU_P(devc_t,__DEVC_ID__) __DEVC_NAME__ -e __DEVC_OPTS__

on SUBST_P(-T console_t) -d -t __DEVC_PATH__ ksh -l
#if defined(__DEVC_PATH2__)
# Start more consoles which can be switched to using ctrl-alt-[1-4]
on SUBST_P(-T console2_t) -d -t __DEVC_PATH2__ ksh -l
on SUBST_P(-T console3_t) -d -t __DEVC_PATH3__ ksh -l
on SUBST_P(-T console4_t) -d -t __DEVC_PATH4__ ksh -l
#endif
#endif
#endif

#if defined(OPT_TCG_yes) || defined(OPT_TCG_cmdline)
echo "---> Starting TABRM"
START_P(tabrm_t) tabrm DROPROOT_NP(__TABRM_ID__)
waitfor /dev/tpmrm0
#endif

#if defined(OPT_QFIM_yes)
echo "---> Starting qfimd"
START_P(qfimd_t) qfimd
waitfor /dev/qfim/record
#endif

echo "---> Starting fsevmgr"
STARTU_P(fsevmgr_t,__FSEVMGR_ID__) fsevmgr

echo "---> Starting devb"
ALLOW_PATHTRUST START_P(devb_t) __DEVB_NAME__ SUBST_NP(cam user=__DEVB_ID__:__DEVB_ID__) blk cache=64M,auto=partition,vnode=2000,ncache=2000,commit=low __DEVB_OPTS__
waitfor /dev/hd0

echo "---> Mounting file systems"
mount_fs.sh
if [ ! -e /system ]; then
	echo No system file system, giving up.
	exit 1
fi

#include "output/inc/_startup_postfs.inc"

#To support proper operation of input capture via io-hid, devc-con-hid should be used instead
#if defined(OPT_GRAPHICS_yes)
echo "---> Starting io-hid"
START_P(iohid_t) io-hid -dps2ser-vm kbd:kbddev:vmware:mousedev  DROPROOT_P(__IO_HID_ID__)
waitfor /dev/io-hid/io-hid
chown __SCREEN_ID__ /dev/io-hid/io-hid

#if ! defined(OPT_BOOT_MODE_uefi)
echo "---> Starting devc"
STARTU_P(devc_t,__DEVC_ID__) __DEVC_NAME__ -e __DEVC_OPTS__
on SUBST_P(-T console_t) -d -t __DEVC_PATH__ ksh -l
#if defined(__DEVC_PATH2__)
# Start more consoles which can be switched to using ctrl-alt-[1-4]
on SUBST_P(-T console2_t) -d -t __DEVC_PATH2__ ksh -l
on SUBST_P(-T console3_t) -d -t __DEVC_PATH3__ ksh -l
on SUBST_P(-T console4_t) -d -t __DEVC_PATH4__ ksh -l
#endif
#endif
#endif

START_P(random_t) random DROPROOT_NP(__RANDOM_ID__) -s /data/var/random/rnd-seed __RANDOM_INTERUPT_ENTROPY__ __RANDOM_OTHER_ENTROPY__
waitfor /dev/random
STARTU_P(pipe_t,__PIPE_ID__) pipe DROPROOT_N(__PIPE_ID__)
waitfor /dev/pipe
STARTU_P(devc_pty_t,__DEVC_PTY_ID__) devc-pty DROPROOT_NP(__DEVC_PTY_ID__)
STARTU_P(dumper_t,__DUMPER_ID__) dumper DROPROOT_N(__DUMPER_ID__) -d /data/var/dumper -M 1000 -D cores

echo "---> Starting Networking"
#if defined(OPT_IO_SOCK_DIAG_yes)
#define __IO_SOCK__ io-sock-diag
#else
#define __IO_SOCK__ io-sock
#endif
#if defined(OPT_USB_yes)
STARTU_P(io_sock_t,__IO_SOCK_ID__) __IO_SOCK__ -m phy -m pci -m usb __NETDRIVER__ __WIFIDRIVER__ __IOSOCK_OPTIONS__ __IOSOCK_QVM_OPTIONS__
#else
STARTU_P(io_sock_t,__IO_SOCK_ID__) __IO_SOCK__ -m phy -m pci __NETDRIVER__ __WIFIDRIVER__ __IOSOCK_OPTIONS__ __IOSOCK_QVM_OPTIONS__
#endif
start_net.sh

echo "---> Starting sshd"
if [ ! -f /data/var/ssh/ssh_host_rsa_key ]; then
    ssh-keygen -q -t rsa -N '' -f /data/var/ssh/ssh_host_rsa_key
    chown __SSHD_ID__:__SSHD_ID__ /data/var/ssh/ssh_host_rsa_key*
fi
if [ ! -f /data/var/ssh/ssh_host_ed25519_key ]; then
    ssh-keygen -q -t ed25519 -N '' -f /data/var/ssh/ssh_host_ed25519_key
    chown __SSHD_ID__:__SSHD_ID__ /data/var/ssh/ssh_host_ed25519_key*
fi
STARTU_P(sshd_t,__SSHD_ID__) /system/bin/sshd -f /system/etc/ssh/sshd_config

STARTU_P(qconn_t,__QCONN_ID__) qconn
#if defined(__HAS_GDBSERVER__)
STARTU_P(gdbserver_t,__GDBSERVER_ID__) gdbserver --multi 127.0.0.1:9000 & 
#endif

echo "---> Starting misc"
STARTU_P(mqueue_t,__MQUEUE_ID__) mqueue
#if defined(OPT_TCG_cmdline)
START_P(tabrmshare_t) tabrmshare DROPROOT_NP(__TABRMSHARE_ID__)
#endif


# Execute the post startup script.  This is a separate script to allow for common behavior of
# both slm and script based startup.
 /system/etc/startup/post_startup.sh
