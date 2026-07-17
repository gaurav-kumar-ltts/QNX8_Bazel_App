ifneq ($(QNXBUILDCFG),)

include Makefile

else

export QNXBUILDCFG=1

KSH_HOST ?= $(QNX_HOST)/usr/bin/ksh

include $(MKFILES_ROOT)/qmacros.mk

# filter out QNX specific compiler options from being used in build-hooks
# projects
CCFLAGS:=$(filter-out $(CCFLAGS_EXCLUDED),$(CCFLAGS))
CXXFLAGS:=$(filter-out $(CXXFLAGS_EXCLUDED),$(CXXFLAGS))
CPPFLAGS:=$(filter-out $(CPPFLAGS_EXCLUDED),$(CPPFLAGS))

exports += SYSNAME
exports += GCC_VERSION
exports += BRANCH_TAG
exports += VERSION_REL
exports += PINFO_%
exports += %_HOST
exports += INSTALL_ROOT_%
exports += CFLAGS
exports += CCFLAGS
exports += CPPFLAGS
exports += CXXFLAGS
exports += LIBCXXFLAGS
exports += CCOPTS
exports += CPPOPTS
exports += CXXOPTS
exports += LDFLAGS
exports += LDOPTS
exports += ASOPTS
exports += WIN64_GCC_DRIVER
exports += LINUX_X86_64_GCC_DRIVER
exports += VARIANT%

envvars += $(foreach v,$(sort $(filter $(exports),$(.VARIABLES))),$v='$($v)')
envvars += QNXVFLAGS='$(strip $(VFLAGS))'
envvars += QNXROOTINCS='$(addprefix -I,$(USE_ROOT_INCLUDE))'
envvars += QNXROOTLIBS='$(addprefix -L,$(USE_ROOT_LIB))'

# propagate default qcc flags to external cross compilers
# See $(OS)_$(ARCH).mk for defaults
#
# Even though the -D_FORTIFY_SOURCE=n option is consumed by the C preprocessor, the
# _FORTIFY_SOURCE feature relies heavily on compiler optimization to function properly. Add
# $(FORTIFY_DEFS) to CFLAGS and CXXFLAGS rather than CPPFLAGS in order to keep the compiler
# optimization and _FORTIFY_SOURCE option together.
ifeq ($(OS),nto)
CFLAGS += $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) $(FORTIFY_DEFS) -Wall
CXXFLAGS += $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) $(FORTIFY_DEFS) -Wall
endif

$(filter-out all clean iclean distclean mostlyclean maintainer-clean hinstall, $(MAKECMDGOALS)) all:
	+$(envvars) $(KSH_HOST) $(MKFILES_ROOT)/build-cfg $(MAKECMDGOALS)

clean iclean distclean mostlyclean maintainer-clean:
	-$(MAKE) -fMakefile AUTOMAKE=: AUTOCONF=: AUTOHEADER=: AUTORECONF=: ACLOCAL=: $@

hinstall: # nothing to do

endif
