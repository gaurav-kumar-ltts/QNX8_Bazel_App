#!/bin/sh
# Update the boot block to have the disk properly partitioned. The current
# partitioning might not match what is desired if either it's all being changed
# due to new partition options in mkqnximage or when a image file is written
# to the SD card.

update_boot=

TMPDIR=/dev/shmem
cd /dev/shmem

# When performing an update, the options file could be in one of two locations
if [ -e /proc/boot/build/options ]; then
    . /proc/boot/build/options
else
    . /ifs/build/options
fi

# If it exists, get the information on the partition type for the system
# partition. It might not match what we currently have since it changes depending
# on the use, or not of qtd, qcfs and qtsafefs.
unset SYS_TYPE
if [ -f part.info ]; then
    . ./part.info
fi

# Find out how the disk is currently partitioned. We need this write a new boot
# sector.
fdisk /dev/hd0 info >diskinfo

# Note all the following uses a temporary file rather than assigning the output
# of grep to a variable. The latter doesn't work as pipe is not running.

grep 'Total Sectors' diskinfo >part_info
read total <part_info
total=${total#*: }

grep '0:.*beg.*end' diskinfo >part_info
read boot_type <part_info
boot_type=${boot_type#*\(}
boot_type=${boot_type%%\)*}

read boot_offset <part_info
boot_offset=${boot_offset#*off=}
boot_offset=${boot_offset%%,*}

grep '1:.*beg.*end' diskinfo >part_info
read sys_type <part_info
sys_type=${sys_type#*\(}
sys_type=${sys_type%%\)*}

read sys_offset <part_info
sys_offset=${sys_offset#*off=}
sys_offset=${sys_offset%%,*}

grep '2:.*beg.*end' diskinfo >part_info
read data_type <part_info
data_type=${data_type#*\(}
data_type=${data_type%%\)*}

read actual_data_sectors <part_info
actual_data_sectors=${actual_data_sectors#*size=}

if [ ${sys_type} != 0 -a ${data_type} = 0 ]; then
    # The system partition type is set but not the data. This means we have or
    # had an installer partition. If we were invoked from the mount_fs.sh script
    # it's important we do nothing or we'll prevent the mounting of the installer
    # partition. We will then get executed again by the installer with an arg
    # of update.
    if [ "$1" != update ]; then
        exit
    fi
fi

if [ -n "${SYS_TYPE}" -a "${SYS_TYPE}" != ${sys_type} ]; then
    echo "Changing system partition type"
    sys_type=${SYS_TYPE}
    update_boot=1
fi
# If a system image replaced only the boot partition, the partition info
# will show a sys_type of 0 and we have to correct it from the configuration.
if [ ${sys_type} = 0 ]; then
	if [ "$OPT_QTD" = yes ]; then
		sys_type=185
	elif [ "$OPT_QCFS" != no ]; then
		sys_type=181
	elif [ "$OPT_QTSAFEFS" != no ]; then
		sys_type=186
	else
		sys_type=178
	fi
    update_boot=1
fi

# If we booted from an image file, there is no data partition. So update to
# what it should be.
if [ ${data_type} != 179 ]; then
    data_type=179
    update_boot=1
fi

# Work out how big the partitions should be based on the configured sizes
remain_parts=${OPT_PART_SIZES}
boot_part_size=${remain_parts%%:*}
boot_sectors=$((${boot_part_size} * 2048))

remain_parts=${remain_parts#*:}
sys_part_size=${remain_parts%%:*}
sys_sectors=$((${sys_part_size} * 2048))

# Get maximum number of sectors available for the data partition.
max_data_sectors=$(($total - $boot_offset - $boot_sectors - $sys_sectors))

if [ "${remain_parts}" = "${sys_part_size}" ]; then
    # data size not specified so have it match what was used as max_sectors when
    # the file system was created. To get more than 64GB you have to explicitly
    # configure it.
    data_part_size=64000
else
    remain_parts=${remain_parts#*:}
    data_part_size=${remain_parts%%:*}
fi
data_sectors=$((${data_part_size} * 2048))
if [ $data_sectors -gt $max_data_sectors ]; then
    data_sectors=$max_data_sectors
fi

# The following will only be done on the first boot after an update
if [ "$actual_data_sectors" != "$data_sectors" ]; then
    echo Resizing data partition
    update_boot=1
fi

if [ -n "${update_boot}" ]; then
    cat >disk.layout <<EOF
[sector_size=512 cylinders=${total} sectors_per_track=1 heads=1 start_at_cylinder=${boot_offset}]
[partition=1 boot=true type=${boot_type} num_sectors=${boot_sectors}]
[partition=2 boot=false type=${sys_type} num_sectors=${sys_sectors}]
[partition=3 boot=false type=${data_type} num_sectors=${data_sectors}]
EOF
    diskimage -p -c disk.layout -o boot-sector

    # Update the boot sector with new partition info
    dd if=boot-sector of=/dev/hd0
    # Refresh info
    mount -e /dev/hd0
    echo Updated boot sector
fi

rm -f boot-sector disk.layout diskinfo part_info
