#!/bin/sh
#include "inputs/definitions.inc"
#include "inputs/uids.inc"

# Configure locations of PAM files.  Note, pamconf must end with a slash
setconf pamlib /system/lib/dll/pam
setconf pamconf /system/etc/pam/

#include "output/inc/_post_start.inc"

echo Process count:`pidin arg | wc -l`

exit 0
