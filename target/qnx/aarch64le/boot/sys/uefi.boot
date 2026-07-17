[
#
# Boot image attributes for an EFI format image.
#
# The build file MUST specify load address via the [image=] attribute.
#
attr="?-bigendian"
+rsvd_vaddr
vboot=0xffffff8060000000
len=0x200
filter="mkifsf_uefi %a %s %i"
pagesizes=4k
]
