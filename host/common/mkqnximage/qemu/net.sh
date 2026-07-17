#!/bin/bash

bridge_helper=$1
bridge_conf=$2
net_type=$3
net_name=$4

if [ -z "$bridge_helper" -o -z "$bridge_conf" -o -z "$net_type" ]; then
    echo "Usage <bridge-helper> <bridge-conf> <net-type>"
    exit 1
fi

# Need to be root
if [ $EUID != 0 ]
then
    echo "Please run as root eg:"
    echo "sudo $0"
    exit 1
fi

if [ `stat -c %u $bridge_helper` != 0 ]; then
    echo "Changing ownership of $bridge_helper"
    chown 0 $bridge_helper
fi
if [ ! -u $bridge_helper ]; then
    echo "Making $bridge_helper setuid root"
    chmod u+s $bridge_helper
fi

umask 0022
mkdir -p `dirname $bridge_conf`

if [ "$net_type" = nat ]; then
    # Allowed to use virbr0
    grep -qs '^allow virbr0' $bridge_conf
    if [ $? -ne 0 ]; then
        echo "Adding allow virbr0 to $bridge_conf"
        echo "allow virbr0" >> $bridge_conf
    fi

    brctl show | grep -q ^virbr0
    if [ $? -eq 0 ]
    then
        # Have virbr0, no need to setup br0
        exit 0
    fi

    # Need to setup br0

    # Allowed to use br0
    grep -qs '^allow br0' $bridge_conf
    if [ $? -ne 0 ]; then
        echo "Adding allow br0 to $bridge_conf"
        echo "allow br0" >> $bridge_conf
    fi

    # Is br0 present
    brctl show | grep -q ^br0
    if [ $? -ne 0 ]
    then
        brctl addbr br0
        if [ $? -ne 0 ]
        then
            echo "Failed to create br0"
            exit 1
        fi
    fi

    # br0 IP
    ifconfig br0 172.31.1.1/24 up

    # br0 DHCP
    ps -elf | grep dnsmasq | grep -q 'interface=br0'
    if [ $? -ne 0 ]
    then
        dnsmasq --interface=br0 --bind-interfaces --except-interface=lo0 --dhcp-range=172.31.1.2,172.31.1.254
    fi
elif [ "$net_type" = bridge ]; then
    # Need to setup br1

    # Allowed to use br1
    grep -qs "^allow $net_name" $bridge_conf
    if [ $? -ne 0 ]; then
        echo "Adding allow $net_name to $bridge_conf"
        echo "allow $net_name" >> $bridge_conf
    fi

    # Is br1 present
    brctl show | grep -q ^$net_name
    if [ $? -ne 0 ]
    then
        echo "$net_name interface not present. Make sure that the system is properly configured to allow the bridge network type"
        exit 1
    fi
fi

exit 0
