#!/bin/sh

# Allow network settings to be altered by a file in /boot. This is primarily
# for real targets which have a FAT boot partition.
if [ /boot/network -nt /data/var/etc/settings/network ]; then
    # Don't source file directly, who knows what commands might be in it.
    grep -E '^(HOSTNAME|IP_ADDR|TIME_SERVERS)=[-:%a-zA-Z0-9 ."'\'']*$' /boot/network >/tmp/network
    . /data/var/etc/settings/network
    . /tmp/network
    rm /tmp/network
    echo HOSTNAME=$HOSTNAME >/data/var/etc/settings/network
    echo IP_ADDR=$IP_ADDR >>/data/var/etc/settings/network
    echo TIME_SERVERS=$TIME_SERVERS >>/data/var/etc/settings/network
fi

# Replace the wpa_supplicant.conf on the data partition with
# /boot/wpa_supplicant.conf if it is newer
if [ /boot/wpa_supplicant.conf -nt /data/var/etc/settings/wpa_supplicant.conf ]; then
    echo "Copying /boot/wpa_supplicant.conf to /data/var/etc/settings/wpa_supplicant.conf"
    cp -p /boot/wpa_supplicant.conf /data/var/etc/settings/wpa_supplicant.conf
    # Set ownership and permissions to match those specified in data_files.builtin
    chown root:root /data/var/etc/settings/wpa_supplicant.conf
    chmod 0640 /data/var/etc/settings/wpa_supplicant.conf
fi
