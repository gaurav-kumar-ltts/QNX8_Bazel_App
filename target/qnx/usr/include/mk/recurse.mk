#
#	Generally useful recursive makefile.
#
#	Finds any subdirectories with "Makefile" in them, and
#	recurses into them, issuing "make" with the specified
#	target. Do not recurse into a directory if there is
#   a "Makefile.dnm" file present.
#

export
unexport PWD
unexport LIST
unexport makelist
unexport makefiles
unexport force_dirs
unexport qbdir
unexport firstdir
unexport restdir
unexport ignore
unexport sep
unexport makecmd
unexport inc_list
unexport exc_list
unexport tmp
unexport reallist
unexport MAKEFILE
unexport goal
unexport dnm_list

ifndef __NTO_VERSION
# should be kept in sync with the companion value in services/system/public/sys/nto_version.h
__NTO_VERSION=800
endif
export __NTO_VERSION

goals:=$(if $(MAKECMDGOALS),$(MAKECMDGOALS),all)

ifndef MAKEFILE
MAKEFILE=[Mm]akefile
endif

makefiles:=$(wildcard */$(MAKEFILE))
makelist:=$(sort $(patsubst %/,%,$(dir $(makefiles))))

dnm_list:=$(patsubst %/,%/.$(firstword $(goals)),$(subst Makefile.dnm,,$(wildcard */[Mm]akefile.dnm*)))
x_list:=$(foreach tmp,$(dnm_list), $(subst ., ,$(notdir $tmp)))
dnm_list:=$(foreach tmp,$(dnm_list), $(if $(filter $(goals), $(subst ., ,$(notdir $(tmp)))),$(patsubst %/,%,$(dir $(tmp)))))

makelist:=$(filter-out $(dnm_list),$(makelist))

ifneq ($(filter CPU OS,$(LIST)),)
#
# If we're working on a CPU or OS list, figure out what target systems we
# can actually build based on the host system we're running on.
#
ifndef QBUILDLIST
QBUILDLIST=buildlist.mk
ifdef QCONFIG
qbdir=$(dir $(QCONFIG))
endif
endif
-include $(qbdir)$(QBUILDLIST)
endif

ifneq (,$(LIST))
ifdef CHECKFORCE
force_dirs:=$(patsubst %/,%,$(dir $(wildcard */[Mm]akefile.force)))
endif

inc_list:=.BUGFIX. $(sort $(foreach var, $(LIST), $($(var)LIST)))
inc_list:=$(filter-out .BUGFIX., $(inc_list))
exc_list:=.BUGFIX. $(sort $(foreach var, $(LIST), $(EXCLUDE_$(var)LIST)))
exc_list:=$(filter-out .BUGFIX., $(exc_list))

ifneq (,$(exc_list))
makelist:=$(filter-out $(filter-out $(force_dirs), $(foreach dir,$(makelist),$(if $(filter $(subst ., ,$(subst -, ,$(dir))),$(subst /, ,$(exc_list))),$(dir)))),$(makelist))
endif

ifneq (,$(inc_list))
reallist:=$(foreach var,$(LIST),$(if $($(var)LIST),$(var),))
makelist:=$(filter-out $(filter-out $(force_dirs), $(foreach dir,$(makelist),$(foreach var,$(reallist),$(if $(filter $(subst ., ,$(subst -, ,$(dir))),$(subst /, ,$($(var)LIST))),,$(dir))))),$(makelist))
endif
endif

makelist:=$(foreach dir,$(EARLY_DIRS),$(filter $(dir),$(makelist))) $(filter-out $(EARLY_DIRS) $(LATE_DIRS), $(makelist)) $(foreach dir,$(LATE_DIRS),$(filter $(dir),$(makelist)))
firstdir:=$(firstword $(makelist))
restdir :=$(filter-out $(firstdir), $(makelist))

ifneq ($(filter -k,$(MFLAGS)),)
ifeq ($(QNX_NO_IGNORE),)
ignore=-
endif
endif
# define the separator as a newline character - handles differences
# between Unix and Win32 style shells.
define sep


endef

# Do not -j if we're not in the variant compilation stage
# This removes the annoying warnings
# make[2]: warning: -jN forced in submake: disabling jobserver mode.
MAKE_JLEVEL=-j $(firstword $(JLEVEL) 1)
ifeq ($(findstring VARIANT,$(LIST)),)
MAKE_JLEVEL=
endif

## flag for disabling recursive make
DISABLE_RECURSIVE_MAKE=0

## disable recursive make if running the 'make test' target
ifeq ($(goals),test)
	DISABLE_RECURSIVE_MAKE=1
	include mk/qtargets_test.mk
endif

## disable recursive make if running the 'make klocwork' target
ifneq ($(findstring klocwork,$(goals)),)
	DISABLE_RECURSIVE_MAKE=1
	include mk/qtargets_klocwork.mk
endif

## disable recursive make if running the 'make coverity' target
ifneq ($(findstring coverity,$(goals)),)
	DISABLE_RECURSIVE_MAKE=1
	include mk/qtargets_coverity.mk
endif

## conditionally disable recursive make
ifeq ($(DISABLE_RECURSIVE_MAKE),0)
makecmd = $(ignore)$(MAKE) $(MAKE_JLEVEL) -C$(dir) -f$(notdir $(firstword $(wildcard $(dir)/$(MAKEFILE)))) $(if $(MAKECMDGOALS),$@)
$(goals):
	+$(foreach dir, $(firstdir), $(makecmd))$(foreach dir, $(restdir), $(sep) $(makecmd))
endif
