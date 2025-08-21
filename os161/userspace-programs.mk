include .config

# Userspace programs are automatically globbed by this Makefile, from
# each of the relevant directories.
#
# This doesn't appear to slow down the build at all, and makes it very
# easy to create new testbins with ./create-testbin.sh.
#
# As such, you really have no need to edit this file.
PROGRAMS=$(wildcard testbin/* bin/* sbin/*)

# Arguments: <directory> [args]
# Assumes that we're calling Makefile. If not, provide -f to args
do-mk=$(MAKE) -C $(1) -s $(2)

# Argument: $(1) = name of new recipe, $(2) = make command
define macro-mk-single-unconditional
$(1):
	+@$(2)

endef

# Argument: $(1) = name of new recipe, $(2) = make command, $(3) = program directory
#
# If we can find the depend.mk file for this testbin, then we use its recipe
# to compile the testbin (and to re-make depend.mk). Then, our new synthetic
# recipe depends on depend.mk, so depend.mk can inject new dependencies.
#
# The goal is that depend.mk injects the exact correct dependencies for the file,
# so then this userspace-programs.mk file will itself detect if that testbin
# needs to be re-built, and only in that case rebuild it.
#
# Otherwise, we have to just make -C on that testbin unconditionally.
#
# The overall goal here is that calling make -C on every testbin is slow. So
# if we can instead only call it when necessary, we can speed up builds by a
# lot -- and these depend.mk makefile fragments are quite able to accomplish that.
define macro-mk-single-fast
ifeq (,$(wildcard $(3)depend.mk))
$(1):
	+@$(2)
else
$(1): $(abspath $(wildcard $(3)depend.mk))
	@:
include $(3)depend.mk
endif

endef
# NOTE: We need a newline after the endif, so that all the ifeq..s can be concatenated
# together in a syntactically valid way.

# Argument: <what> e.g. make, make clean
# Should not be used for make all as that one should be faster, using the depend.mk/lock.mk system.
define macro-mk-everything

$(1): $(foreach prog,$(PROGRAMS),$(1)-$(prog))

$(foreach prog,$(PROGRAMS),$(call macro-mk-single-unconditional,$(1)-$(prog),$(call do-mk,$(prog)/,$(1))))

endef

# Create the all target manually, as it depends on the macro-mk-single-fast machinery.
# We name the targets all-$(prog)
all: $(foreach prog,$(PROGRAMS),all-$(prog))

# Create the all targets for each program.
$(foreach prog,$(PROGRAMS),$(eval $(call macro-mk-single-fast,all-$(prog),$$(call do-mk,$(prog)/,all),$(prog)/)))

$(eval $(call macro-mk-everything,clean))