[
#
# Boot image attributes for an ELF format image.
#
# The build file MUST specify load address via the [image=] attribute.
#
attr="?-bigendian"
+rsvd_vaddr
vboot=0xfffffc0060000000
len=0x200
filter="mkifsf_elf %a %s %i"
pagesize=64k
pagesizes=64k
]
