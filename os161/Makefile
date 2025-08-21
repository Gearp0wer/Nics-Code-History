# Before include'ing .config, we error check it ourselves.
# This is so we can generate a helpful error in the case
# that it doesn't exist.
ifeq (,$(wildcard .config))
  $(error Could not find .config -- try running ./configure to generate a .config)
endif

include .config

# Arguments: <directory> [args]
# Assumes that we're calling Makefile. If not, provide -f to args
do-mk=$(MAKE) -C $(1) -s $(2) || exit $$?

# Argument: <what> e.g. make, make clean
do-mk-everything= \
	$(call do-mk,kern/,$(1)); \
	$(call do-mk,lib/libc/,$(1)); \
	$(call do-mk,lib/crt0/,$(1)); \
	$(call do-mk,./,-f userspace-programs.mk $(1));

# NOTE: If you're not using the ctags, e.g. if you're not using vim,
# feel free to comment out "tags" below (e.g. all: # tags), which
# may speed up your builds slightly.
all: tags
# Double check that the module is loaded. This makes sure we exit out
# early if the compilation won't work at all.
	@if ! cs161-gcc -v >/dev/null 2>&1; then echo "$$(tput setaf 1)ERROR:$$(tput sgr0) cs161-gcc not found. Please run module load sys161/2.0.8"; exit 1; fi
	+@$(call do-mk-everything,)

# Include the core-fns for do-show-clean, do-clean and do-clean-symlink
include mk/core-fns.mk

# Generate ctags for all files in the source tree.
# This is slightly slow, but it does make vim more useful, as you can
# e.g. jump-to-definition.
tags:
	@$(call do-show-gen,$(OSTREE)/tags)
# Note: ctags is called with & to make it run separately. This should
# keep builds fast.
	@ctags -f $(OSTREE)/tags -R kern lib bin sbin testbin &

# Main clean rule: Delete all the compiled files. This calls 'make clean'
# all the other makefiles, but also handles all of the .o and .d in the tree.
clean::
# Automatically use -j8 for the inner make clean. This seems a bit silly,
# but it does speed it up.
	+@$(call do-mk-everything,clean -j8)

# The top-level makefile is responsible for cleaning the machine
# symlink which is used throughout the kernel to find machine-specific
# headers.
# IMPORTANT! Must also clean the dummy file, as it is what indicates
# the existence of the file to make
	$(call do-clean,$(OSTREE)/kern/compile/machine-lnk)
	$(call do-clean-symlink,$(OSTREE)/kern/compile/machine)
# We also generate ctags so clean those here
	$(call do-clean,$(OSTREE)/tags)

.PHONY: all clean tags

# Check the error conditions, so that the makefile fails fast in case something is wrong.
include mk/mk-check-detailed.mk