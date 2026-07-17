ifneq ($(COMPILER_DRIVER),qcc)
CCVFLAG_shared = -fpic -D__PIC__
ASVFLAG_shared = -D__PIC__ -Wa,--defsym -Wa,__PIC__=1
endif

OPTIMIZE_TIME_gcc=-O2
OPTIMIZE_SIZE_gcc=-Os
OPTIMIZE_NONE_gcc=-O0
OPTIMIZE__gcc=$(OPTIMIZE_TIME_gcc)

FORTIFY_DEFS = $(if $(FORTIFY_LEVEL),-D_FORTIFY_SOURCE=$(FORTIFY_LEVEL),)

CC_linux_x86_64_gcc += -c -Wall -pipe $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) $(FORTIFY_DEFS)
AS_linux_x86_64_gcc += -c -Wall -pipe -O $(addprefix -Wa$(comma)-I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES)) 
