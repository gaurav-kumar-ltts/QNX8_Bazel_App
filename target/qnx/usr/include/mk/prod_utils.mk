__prod_utils_mk_CCFLAGS_nto = -D_FILE_OFFSET_BITS=64
__prod_utils_mk_CCFLAGS_win64 = -D_FILE_OFFSET_BITS=64
CCFLAGS += $(__prod_utils_mk_CCFLAGS_$(OS))
