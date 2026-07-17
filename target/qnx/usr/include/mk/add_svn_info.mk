#
# Copyright (c) 2019, 2024, BlackBerry Limited. All rights reserved.
#
# BlackBerry Limited and its licensors retain all intellectual property and
# proprietary rights in and to this software and related documentation. Any
# use, reproduction, disclosure or distribution of this software and related
# documentation without an express license agreement from BlackBerry Limited
# is strictly prohibited.

##############################################################################
#
# Include this file in your common.mk to automatically add information about
# where in the source repository the code was taken from in a program's use 
# message.
#
# If source came from SVN, this will include branch- and revision information.
# For code from git it will be branch, commit hash, and commit date/-time.
#
# The use message must be contained in a separate file (e.g., myprogram.use);
# use messages inside .c files will most likely fail to build. The usefile
# should contain a placeholder "%%BRANCH%%" that will be replaced at build
# time with the relevant source-control information.
#
# The Makefile variable USEFILE must be defined before including this file.
# It must contain the pathname of the file containing the use message.
#
# If the code came from SVN, the variable URL must also be defined; it should 
# contain the SVN URL of the "common.mk" including this here file.
# To define the variable, add the following line to your common.mk file:
#     URL:=<dollar>URL<dollar>
# ...where each <dollar> is a single '$'.
# Remember to include "URL" in the file's "svn:keywords" property.
#
# Within the USEFILE, every instance of the string  %%BRANCH%%  will be
# replaced by a string of the form...
#     <branch>/<dir> @<revision>                    for SVN, or
#     <branch>/<dir>, commit <hash> (<date_time>)   for git
#
##############################################################################

ifeq ($(USEFILE),)
$(error make variable 'USEFILE' not set)
endif

# By default, assume we are in a working copy (of either git or SVN).
# If the variable WORKSPACE_TO_WORKING_COPY is set, it must contain a string
# of the form  <what>,<with>  where <what> is a pathname portion that will
# be replaced by <with>. The <what> part may contain a '%' character that 
# will match any number of non-'/' characters.
WORKSPACE_PROJECT_DIR:=$(or $(PROJECT_ROOT),$(dir $(realpath $(USEFILE))))
ifeq ($(WORKSPACE_TO_WORKING_COPY),)
WORKING_COPY_PROJECT_DIR:=$(WORKSPACE_PROJECT_DIR)
else
WORKING_COPY_PROJECT_DIR:=$(shell echo $(WORKSPACE_PROJECT_DIR) | sed -e 's,$(subst %,[^/]*,$(WORKSPACE_TO_WORKING_COPY)),')
endif

# Try to get git branch information from working copy
GIT_BRANCH:=$(shell (cd $(WORKING_COPY_PROJECT_DIR) && git rev-parse --abbrev-ref HEAD) 2> /dev/null)
ifneq ($(GIT_BRANCH),)
## We seem to have a git working copy. Get the working copy's root directory.
GIT_WORKING_COPY_ROOT:=$(shell (cd $(WORKING_COPY_PROJECT_DIR) && git rev-parse --show-toplevel) 2> /dev/null)

## Build the combined branch/path information by replacing
## the working copy's root with the branch name.
BRANCH_PATH:=$(patsubst %/,%,$(subst $(GIT_WORKING_COPY_ROOT),$(GIT_BRANCH),$(WORKING_COPY_PROJECT_DIR)))

## Get the last commit hash and -date/-time
GIT_COMMIT:=$(shell (cd $(WORKING_COPY_PROJECT_DIR) && git log -n1 --decorate=short --format='commit %h (%cI)') 2> /dev/null)

## Construct the final repository information
#REPO_INFO:=$(BRANCH_PATH), $(GIT_COMMIT)
## For now, don't include root/branch/path information in order to not
## accidentally publish any interna. Hopefully, the commit id will be 
## sufficient to also look up the repo in gitlab...
REPO_INFO:=$(GIT_COMMIT)

undefine GIT_WORKING_COPY_ROOT
undefine BRANCH_PATH
undefine GIT_COMMIT
else  # ifneq ($(GIT_BRANCH),)
## No git information available, try SVN instead.
SVN_REVISION:=$(strip $(shell svn info --show-item revision $(WORKING_COPY_PROJECT_DIR) 2> /dev/null))
ifneq ($(SVN_REVISION),)
### Looks like an SVN working copy.
### Acquire the project directory's path relative to the repository.
### This will have the form "^/<branch>/<path>".
SVN_RELATIVE_URL:=$(strip $(shell svn info --show-item relative-url $(WORKING_COPY_PROJECT_DIR) 2> /dev/null))

### Strip the leading "^/", leaving only <branch>/<path>
BRANCH_PATH:=$(patsubst ^/%,%,$(SVN_RELATIVE_URL))

### Construct the final repository information
REPO_INFO:=$(BRANCH_PATH) @$(SVN_REVISION)

undefine SVN_RELATIVE_URL
undefine BRANCH_PATH
else  ## ifneq ($(SVN_REVISION),)
### Neither git nor SVN. Sorry.
REPO_INFO:=unknown repo/branch
endif ## ifneq ($(SVN_REVISION),)

undefine SVN_REVISION
endif # ifneq ($(GIT_BRANCH),)

# The original usefile will be used to create a temporary one in which the
# %%BRANCH%% placeholder is replaced by the REPO_INFO generated above.
# Remember the original (=source) name, and let USEFILE point to the 
# temporary file so it gets picked up by "usemsg" later on.
USEFILE_SRC:=$(USEFILE)
undefine USEFILE
USEFILE:=$(USEFILE_SRC).tmp

# Don't keep the temporary usefile when finished
.INTERMEDIATE: $(USEFILE)

# Keep default make target 'all'
all:

# Finally, a rule to create the actual usefile from the template.
$(USEFILE): $(USEFILE_SRC)
	sed -e 's|%%BRANCH%%|$(REPO_INFO)|g' $< > $@

undefine WORKSPACE_PROJECT_DIR
undefine WORKING_COPY_PROJECT_DIR
undefine GIT_BRANCH
