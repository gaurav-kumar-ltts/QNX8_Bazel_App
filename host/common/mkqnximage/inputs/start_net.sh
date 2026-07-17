#!/bin/sh
#include "inputs/definitions.inc"
#include "inputs/uids.inc"

if_up -p -r 20 __NETDEVICE__
ifconfig __NETDEVICE__ up

#if defined(__WIFIDEVICE__)
if_up -p -r 20 __WIFIDEVICE__
ifconfig __WIFIDEVICE__ up

wpa_supplicant-2.11 -Dqwdi -t -Z100 -i __WIFIDEVICE__ -c /data/var/etc/settings/wpa_supplicant.conf &
#endif

IP_ADDR=dhcp
HOSTNAME=noname

. /data/var/etc/settings/network

setconf _CS_HOSTNAME ${HOSTNAME}

if [ "$IP_ADDR" != dhcp ]; then
	ifconfig __NETDEVICE__ $IP_ADDR
fi

sysctl -w net.inet.icmp.bmcastecho=1 > /dev/null
#if ! defined(OPT_SECPOL_no)
sysctl -w qnx.sec.transition=1 > /dev/null
#elif defined(OPT_ROOT_no)
sysctl -w qnx.sec.droproot=__IO_SOCK_ID__:__IO_SOCK_ID__ > /dev/null
#endif

# If dhcpcd not run as root, need to give it read/write access to /dev/bpf
setfacl -m user:__DHCPCD_ID__:rw  /dev/bpf

if [ "$IP_ADDR" = dhcp ]; then
	STARTU_P(dhcpcd_t,__DHCPCD_ID__) dhcpcd -bq -f /system/etc/dhcpcd/dhcpcd.conf -c /system/etc/dhcpcd/dhcpcd-run-hooks
else
	/system/etc/startup/pinger.sh delay &
fi

exit 0
