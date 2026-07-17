# This is executed by running mkqnximage --update=...

#include "inputs/definitions.inc"
#include "inputs/uids.inc"

# Get the value of QTD_OFFSET if set.
. ./part.info

mount -uo exec /dev/shmem
cp /system/bin/shutdown /dev/shmem
cp /system/bin/slay /dev/shmem
cp /system/bin/sync /dev/shmem

PATH=/dev/shmem:$PATH

#include "output/inc/_update.inc"

# Update the partition information for when we re-start devb so that it has
# the partitions and has them in the right locations.
./updatefs.sh update

/dev/shmem/sync

slay __DEVB_NAME__
while ! slay -p __DEVB_NAME__ >/dev/null 2>&1; do
	toybox sleep 0.2
done

__DEVB_NAME__ blk cache=64M,auto=partition,vnode=2000,ncache=2000,commit=low __DEVB_OPTS__
waitfor /dev/hd0

if [ -e boot.part ]; then
#if ! defined(IMAGE_TYPE_bios)
	dd bs=163840 if=boot.part of=/dev/hd0t12
#else
	dd bs=163840 if=boot.part of=/dev/hd0t177
	# Set the boot offset (usually done by diskimage)
	toybox printf "\1" | dd of=/dev/hd0t177 bs=1 seek=4 count=1
#endif
fi
if [ -e system.part ]; then
	if [ -e /dev/hd0t178 ]; then
		SYSTEM_PART=/dev/hd0t178
	elif [ -e /dev/hd0t181 ]; then
		SYSTEM_PART=/dev/hd0t181
	elif [ -e /dev/hd0t185 ]; then
		SYSTEM_PART=/dev/hd0t185
	elif [ -e /dev/hd0t186 ]; then
		SYSTEM_PART=/dev/hd0t186
	fi
	dd bs=163840 if=system.part of=$SYSTEM_PART
	# If this partition uses QTD, we need to put the QTD data at the end of the
	# system partition.
	if [ -e system-qtd.part ]; then
		dd bs=512 if=system-qtd.part of=$SYSTEM_PART seek=$QTD_OFFSET
	fi
fi
if [ -e data.part ]; then
	dd bs=163840 if=data.part of=/dev/hd0t179
fi
/dev/shmem/sync

echo Rebooting . . .
toybox sleep 2
shutdown
toybox sleep 10
