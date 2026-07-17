[
#
# Boot image attributes for plain binary image.
#
# Assumes that control is passed to the startup entry point after loading.
#
# The build file MUST specify load address via the [image=] attribute.
#
attr="?-bigendian"
+rsvd_vaddr
vboot=0xfffffc0060000000
pagesize=64k
pagesizes=64k
]
