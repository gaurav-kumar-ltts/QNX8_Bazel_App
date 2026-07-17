.PHONY : debug

NAME=		devs-$(PROJECT)
USEFILE=	$(PROJECT_ROOT)/$(NAME).use
INSTALLDIR=	lib/dll
DEVS_PATH=	$(QNX_TARGET)/usr/include/devs

EXTRA_INCVPATH+= \
	$(DEVS_PATH) \
	$(DEVS_PATH)/contrib/ck/include \
	$(DEVS_PATH)/include_$(CPU) \
	$(DEVS_PATH)/qnx \
	$(DEVS_PATH)/qnx-gen \
	$(DEVS_PATH)/sys-nto

CCFLAGS+=	-D__FreeBSD__
CCFLAGS+=	-fno-builtin-log -fno-strict-aliasing
CCFLAGS+=	-Wno-pointer-sign -Wno-unused-but-set-variable
CCFLAGS+=	-std=iso9899:1999 -D__EXT

CCFLAGS+=	-D_KERNEL -DHAVE_KERNEL_OPTION_HEADERS
CCFLAGS+=	-Wpointer-arith -Wmissing-prototypes -Wall
ifneq ($(QNX_ALLOW_WERROR), 0)
CCFLAGS+=	-Werror
endif
CCFLAGS+=	-fwrapv

include $(MKFILES_ROOT)/qtargets.mk

debug: all
debug: CCFLAGS+= -O0
debug: DEBUG=-g
debug: FORTIFY_LEVEL=0

ifeq ($(findstring diag,$(VARIANT_LIST)),diag)
CCFLAGS+= -DINVARIANTS -DINVARIANT_SUPPORT -DKTR
endif

ifeq ($(INTERFACE_PREFIX),)
	INTERFACE_PREFIX="$(PROJECT)"
endif
DRIVER_SPECIFIC_USE+=\nThis driver creates interface names prefixed with $(INTERFACE_PREFIX).
ifeq ($(HOST_SYSTEM),Linux)
	# Need add -e when invoking echo to interpret character escapes.
	ECHO_ARG=-e
endif

DRIVER_DESCRIPTION=$(subst PINFO DESCRIPTION=,,$(PINFO))
export DRIVER_DESCRIPTION
export DRIVER_SPECIFIC_USE
export DRIVER_SPECIFIC_OPTIONS
$(PROJECT_ROOT)/$(NAME).use:
	@$(ECHO_HOST) "divert(-1)" > $@.m4
	@$(ECHO_HOST) $(ECHO_ARG) "define(\`__DRIVER_DESCRIPTION__',\`$$DRIVER_DESCRIPTION')" >> $@.m4
	@$(ECHO_HOST) $(ECHO_ARG) "define(\`__DRIVER_SPECIFIC_USE__',\`$$DRIVER_SPECIFIC_USE')" >> $@.m4
	@$(ECHO_HOST) $(ECHO_ARG) "define(\`__DRIVER_SPECIFIC_OPTIONS__',\`$$DRIVER_SPECIFIC_OPTIONS')" >> $@.m4
	@$(ECHO_HOST) "divert(0)dnl" >> $@.m4
	@cat $(DEVS_PATH)/devs.use >> $@.m4
	@m4 $@.m4 > $@
	@$(RM_HOST) $@.m4

include $(DEVS_PATH)/opt_global.mk
