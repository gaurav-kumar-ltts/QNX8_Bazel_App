[
#
# Boot image attributes for an S-record format image.
#
# The build file MUST specify load address via the [image=] attribute.
#
attr="?-bigendian"
filter="mkifsf_srec %a %I %i"
+rsvd_vaddr
vboot=0xfffffc0060000000
pagesize=64k
pagesizes=64k
]
