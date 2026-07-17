# This spec file is read by gcc when linking.  It is used to specify the
# standard libraries we need in order to link with various sanitizer libs.

*link_libasan: -lm

*link_libhwasan: -lm

*link_libtsan: -lm

*link_libubsan: -lm

*link_liblsan: -lm

