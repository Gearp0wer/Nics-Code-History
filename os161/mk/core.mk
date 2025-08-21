# core.mk is the "core" driver of the GMU build system for OS/161.
#
# It handles the tasks of:
# - Collecting source paths (.c, .S)
# - Translating those to .o paths
# - Building the .o files from each source file
# - Cleaning .o and .d files
#
# The most interesting functionality is that of collecting source paths.
#
# In essence, we perform a recursive loop over source paths, including
# any files.mk file in each subdirectory. Then, files.mk may append
# values to SRCS-y and GEN-SRCS-y in order to add new source files.
#
# Any paths appended to SRCS-y will then be recursively searched.
#
# So, for example, if you are in kern/main and you add a new file,
# hello.c, you can add it to the build system by editing kern/main/files.mk.
#
# Or, if you are in kern and add a new subdirectory, "process" you can
# edit kern/Makefile to add "process/" to SRCS-y, then add a new files.mk
# inside process/ that contains the relevant files.
#
# This system is spritually inspired by the Linux kernel build system,
# which has a similar recursive behavior.
#
# (This build system is much less complicated than the Linux kernel build
# system, but it is somewhat similar to use from an end-user perspective).
#
#
#
# One VERY IMPORTANT rule to keep in mind if you're doing anything other
# than adding simple source files: EVERY RULE that we actually provide to
# Make uses an absolute path (e.g. $(abspath filename) or $(OSTREE)/something).
#
# This is because different parts of the source tree use different working
# directories, and so to ensure they always refer to the same file, we
# must use absolute paths (as Make has no other sense of identity).
#
# However, this mostly does not matter for the GMU CS 471/571 classes. Unless
# for some reason you're trying to add a procedurally generated file, you
# should not need to touch the Makefiles besides adding a small set of filenames
# to SRCS-y, in which case you will be using relative paths (i.e. relative
# to the relevant files.mk file).
#
#
# July-August 2024: New build system built by Benjamin Wall.

# IMPORTANT: Disable builtin rules so that make doesn't try to do crazy stuff.
.SUFFIXES:

THIS_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# Include .config for all the important vars like $(CC) etc
include $(THIS_DIR)../.config

SRCS-y?=
GEN-SRCS-y?=
OBJ_REQS?=
TARGET_REQS?=
CFLAGS?=
LDFLAGS?=

# Allow the extension for the object files to be overriden. This is an
# important tool for compiling libc -- we need two versions of the libc
# object files, one for the kernel and one for the userspace.
#
# So, simply allow the relevant makefiles to specify that their extension
# should be different.
OBJ_EXT_PREFIX?=

define opt-setup
ifeq ($(OPT_$(1)),y)
# Create the cflag
  CFLAGS += -DOPT_$(1)
# Create the inverted flag
  OPT_NO_$(1)=n
else
  OPT_NO_$(1)=y
endif
endef

# Setup each option. This does two things:
# - Defines e.g. OPT_NO_DUMBVM if OPT_DUMBVM=n,
#   so that we can use it in the makefile
# - Adds -DOPT_<whatever> for each option that =y,
#   so that the C files can detect if that option is y.
$(eval $(call opt-setup,SYNCHPROBS))
$(eval $(call opt-setup,DUMBVM))
$(eval $(call opt-setup,SFS))
$(eval $(call opt-setup,NET))

# Allow for adding a prefix (useful for userprogs, etc)
TARGET_PREFIX?=./
TARGET_BACKTRACK?=./
TARGET_NAME?=

TARGET_PATH:=$(abspath $(TARGET_NAME))

all: $(TARGET_PATH) install

install::

# Define the top-level build thing. This is not 'all', so that it is easy to
# see which makefile has nothing to do (when it prints Nothing to be done for '<target>').
#
# The actual build-linked, build-lib etc will define what to actually do for the target.
$(TARGET_PATH): | $(TARGET_REQS)

C_SRC_PATHS     := $(filter %.c,$(SRCS-y))
S_SRC_PATHS     := $(filter %.S,$(SRCS-y))
LOCAL_SRC_DIRS  := $(filter %/,$(SRCS-y))
C_GEN_SRC_PATHS := $(filter %.c,$(GEN-SRCS-y))
S_GEN_SRC_PATHS := $(filter %.S,$(GEN-SRCS-y))

# This function is used to show an error message in the case that some files.mk
# adds something the Makefile doesn't understand.
#
# This is helpful, as it's very easy to e.g. accidentally forget the / at the end
# of a path.
define check_invalid_srcs
$(if $(strip $1), \
  $(info Error: Makefile does not understand the following items added to SRCS-y (or GEN-SRCS-y) (in '$2'):)\
  $(foreach invalid,$1,$(info - $(invalid)))\
  $(info )\
  $(info Note: The only objects you should add to SRCS-y are)\
  $(info - C files (e.g. something.c))\
  $(info - Assembly files (e.g. something.S))\
  $(info - Subdirectories (e.g. something/ -- when adding a new source directory, be sure to include the /))\
  $(info )\
  $(error Invalid items in SRCS-y))

endef

# Perform original check for invalid sources.
# Note: This assumes the calling Makefile is called "Makefile". This only affects the
# error message.
# Most of the time, you shouldn't need to add any files to e.g. kern/Makefile or
# lib/libc/Makefile anyways, so you usually shouldn't see this message.
ALL_SRCS=$(SRCS-y) $(GEN-SRCS-y)
$(eval INVALID_SRCS=$(filter-out $(filter %.c,$(ALL_SRCS)) $(filter %.S,$(ALL_SRCS)) $(filter %/,$(ALL_SRCS)),$(ALL_SRCS)))
$(eval $(call check_invalid_srcs,$(INVALID_SRCS),Makefile))

# This is the core driver of the "find source files" functionality. It recursively
# calls itself, grabbing relative paths into the C_SRC_PATHS, S_SRC_PATHS, etc.
find_sources=$(foreach dir,$(1),\
	$(eval SRCS-y=)\
	$(eval GEN-SRCS-y=)\
	$(eval include $(dir)files.mk)\
	$(eval C_SRC_PATHS += $(addprefix $(dir),$(filter %.c,$(SRCS-y))))\
	$(eval S_SRC_PATHS += $(addprefix $(dir),$(filter %.S,$(SRCS-y))))\
	$(eval LOCAL_SRC_DIRS = $(addprefix $(dir),$(filter %/,$(SRCS-y))))\
	$(eval C_GEN_SRC_PATHS += $(addprefix $(dir),$(filter %.c,$(GEN-SRCS-y))))\
	$(eval S_GEN_SRC_PATHS += $(addprefix $(dir),$(filter %.S,$(GEN-SRCS-y))))\
	$(eval ALL_SRCS=$(SRCS-y) $(GEN-SRCS-y))\
	$(eval INVALID_SRCS=$(filter-out $(filter %.c,$(ALL_SRCS)) $(filter %.S,$(ALL_SRCS)) $(filter %/,$(ALL_SRCS)),$(ALL_SRCS)))\
	$(eval $(call check_invalid_srcs,$(INVALID_SRCS),$(dir)files.mk))\
	$(call find_sources,$(LOCAL_SRC_DIRS)))

$(call find_sources,$(LOCAL_SRC_DIRS))

# One very important property of this build system is that everything is done
# with absolute paths.
# This is because Make has no sense of the identity of a file, so if you refer
# to the same file from two different paths, Make will not realize you're
# talking about the same file.
# Instead, we always use absolute paths, for everything.
C_SRC_PATHS := $(abspath $(C_SRC_PATHS))
S_SRC_PATHS := $(abspath $(S_SRC_PATHS))

C_GEN_SRC_PATHS := $(abspath $(C_GEN_SRC_PATHS))
S_GEN_SRC_PATHS := $(abspath $(S_GEN_SRC_PATHS))

# Provide an error detection functionality for C source paths that are invalid.
# This is useful for when you remove a C file but forget to update the Makefile,
# as it gives a more helpful error than the cryptic message about a .o file
# that Make doesn't know how to build.
#
# Note that this does NOT include items in the GEN-SRCS-y set, so any autogenerated
# sources are not detected by this logic.
ifneq ($(wildcard $(C_SRC_PATHS)),$(C_SRC_PATHS))
  $(info Error: Makefile detected that you specified a C source file that does not exist.)
  $(info This might happen if you deleted a C source file without removing it from the associated Makefile,)
  $(info or it might happen if you misspelled the C file's name.)
  $(info )
  $(info You should determine which files.mk / Makefile contains the invalid paths, and then make sure)
  $(info that the file names are correct.)
  $(info )
  $(info The invalid paths are: )
  $(foreach invalid,$(filter-out $(wildcard $(C_SRC_PATHS)),$(C_SRC_PATHS)),$(info - $(invalid)))
  $(info )
  $(error Invalid C source paths specified)
endif

# Same idea with .S paths.
ifneq ($(wildcard $(S_SRC_PATHS)),$(S_SRC_PATHS))
  $(info Error: Makefile detected that you specified a .S source file that does not exist.)
  $(info This might happen if you deleted a .S source file without removing it from the associated Makefile,)
  $(info or it might happen if you misspelled the .S file's name.)
  $(info )
  $(info You should determine which files.mk / Makefile contains the invalid paths, and then make sure)
  $(info that the file names are correct.)
  $(info )
  $(info The invalid paths are: )
  $(foreach invalid,$(filter-out $(wildcard $(S_SRC_PATHS)),$(S_SRC_PATHS)),$(info - $(invalid)))
  $(info )
  $(error Invalid .S source paths specified)
endif

# After we check for file existence, collect all the paths together.
C_SRC_PATHS += $(C_GEN_SRC_PATHS)
S_SRC_PATHS += $(S_GEN_SRC_PATHS)

C_OBJ_PATHS := $(patsubst %.c,%$(OBJ_EXT_PREFIX).o,$(C_SRC_PATHS))
# The .d files also end up getting the ext prefix.
C_DEP_PATHS := $(patsubst %.c,%$(OBJ_EXT_PREFIX).d,$(C_SRC_PATHS))
S_OBJ_PATHS := $(patsubst %.S,%$(OBJ_EXT_PREFIX).o,$(S_SRC_PATHS))

include $(THIS_DIR)core-cflags.mk
include $(THIS_DIR)core-fns.mk

# Note on OBJ_REQS:
# We automatically add $(OSTREE)/kern/compile/machine-lnk to OBJ_REQS.
# This is because files all across the source tree require on being
# able to find the machine/ include path, and in fact, it previously
# had to be added to each makefile individually anyways. So adding it
# all in one place allows us to handle it more cleanly (i.e. less makefile churn).

$(C_OBJ_PATHS): %$(OBJ_EXT_PREFIX).o: %.c | $(OBJ_REQS) $(OSTREE)/kern/compile/machine-lnk 
	$(call do-cc,$@,$<,$(CFLAGS))

$(S_OBJ_PATHS): %$(OBJ_EXT_PREFIX).o: %.S | $(OBJ_REQS) $(OSTREE)/kern/compile/machine-lnk 
	$(call do-cc,$@,$<,$(CFLAGS))

# Here we actually gneerate the machine-lnk and correspondingly,
# the machine directory.
#
# In order to get make to only update the symlink (of machine)
# when necessary, we create a dummy file in the same directory,
# that we actually depend on, then update the symlink and dummy
# in lockstep.
#
# # Depend on .config because this is platform-specific.
$(OSTREE)/kern/compile/machine-lnk: $(OSTREE)/.config
# do-symlink to create the actual symlink
# create this before the dummy file for correct ordering.
# that is, we don't want other make jobs thinking the symlink
# is ready when it isn't yet.
	$(call do-symlink,$(OSTREE)/kern/compile/machine,$(OSTREE)/kern/arch/$(PLATFORM)/include)
# create the dummy file
	@touch $@

# Note: The responsibility for cleaning machine/ has been delegated to the
# top-level makefile, as it is used throughout the build.

# We provide a specialized target for cleaning just the target.
clean-$(TARGET_NAME):
	$(call do-clean,$(TARGET_PATH))

# Clean depends on the TARGET_NAME target so it is always cleaned too.
clean:: clean-$(TARGET_NAME)
# The main thing we want each sub-Makefile to clean is its object files
# and .d files. We could do all of this with a single find command at the
# top-level, but that has the disadvantage of making it impossible to e.g.
# make clean for a single userspace program.
	$(call do-show-clean,$(dir $(TARGET_PATH))*.o)
	@find . -name "*.o" -exec rm {} \;
	$(call do-show-clean,$(dir $(TARGET_PATH))*.d)
	@find . -name "*.d" -exec rm {} \;

-include $(C_DEP_PATHS)

.PHONY: clean clean-$(TARGET_NAME) install
