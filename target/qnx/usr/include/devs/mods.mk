.PHONY : debug

NAME=		mods-$(PROJECT)
USEFILE=	$(PROJECT_ROOT)/$(NAME).use
INSTALLDIR=	lib/dll
MODS_PATH=	$(QNX_TARGET)/usr/include/devs

EXTRA_INCVPATH+= \
	$(MODS_PATH) \
	$(MODS_PATH)/contrib/ck/include \
	$(MODS_PATH)/include_$(CPU) \
	$(MODS_PATH)/qnx \
	$(MODS_PATH)/qnx-gen \
	$(MODS_PATH)/sys-nto

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

ifeq ($(HOST_SYSTEM),Linux)
	# Need add -e when invoking echo to interpret character escapes.
	ECHO_ARG=-e
endif

MODULE_DESCRIPTION=$(subst PINFO DESCRIPTION=,,$(PINFO))
export MODULE_DESCRIPTION
export MODULE_SPECIFIC_USE
export MODULE_SPECIFIC_OPTIONS
$(PROJECT_ROOT)/$(NAME).use:
	@$(ECHO_HOST) "divert(-1)" > $@.m4
	@$(ECHO_HOST) $(ECHO_ARG) "define(\`__MODULE_DESCRIPTION__',\`$$MODULE_DESCRIPTION')" >> $@.m4
	@$(ECHO_HOST) $(ECHO_ARG) "define(\`__MODULE_SPECIFIC_USE__',\`$$MODULE_SPECIFIC_USE')" >> $@.m4
	@$(ECHO_HOST) $(ECHO_ARG) "define(\`__MODULE_SPECIFIC_OPTIONS__',\`$$MODULE_SPECIFIC_OPTIONS')" >> $@.m4
	@$(ECHO_HOST) "divert(0)dnl" >> $@.m4
	@cat $(MODS_PATH)/mods.use >> $@.m4
	@m4 $@.m4 > $@
	@$(RM_HOST) $@.m4

include $(MODS_PATH)/opt_global.mk
