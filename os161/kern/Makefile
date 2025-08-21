include ../.config

TARGET_NAME=kernel
SRCS-y=dev/ fs/ lib/ main/ test/ thread/ userprog/ libc/

# Only include asst1/ if we're doing the synchprobs.
SRCS-$(OPT_SYNCHPROBS) += asst1/

# Only include vm/ if we're not using dumbvm.
SRCS-$(OPT_NO_DUMBVM) += vm/

# Depending on the current $(PLATFORM), include the corresponding
# subdirectory from the arch/ folder.
SRCS-y += arch/$(PLATFORM)/$(PLATFORM)/

# Include the automatically generated autoconf.c
GEN-SRCS-y += compile/autoconf.c

# Include the automatically generated vers.c
GEN-SRCS-y += compile/vers.c

# Use ".k.o" instead of just ".o" so that the C files that are shared with
# libc can be compiled into two separate objects.
OBJ_EXT_PREFIX=.k

CFLAGS+=-ffreestanding -D_KERNEL -G 0

CFLAGS+=-I$(OSTREE)/kern/dev 

LOAD_ADDRESS=0x80001000
LDFLAGS+= \
	-Ttext $(LOAD_ADDRESS) -T $(OSTREE)/kern/arch/$(PLATFORM)/ldscript \
	-G 0

# Need autoconf.h to build some device files, and we do need autoconf.c
OBJ_REQS += compile/autoconf.h compile/autoconf.c

OBJ_REQS := $(abspath $(OBJ_REQS))

# Make it so that rebuilding any source file results in the kernel being deleted. This ensures
# that a non-compiling kernel cannot be accidentally run.
OBJ_REQS += clean-$(TARGET_NAME) clean-installed-kernel

# Build a linked executable
include ../mk/build-linked.mk

# Install the kernel into root. Also copy
# the sys161.conf.
$(OSTREE)/root/kernel: $(TARGET_PATH)
	@mkdir -p $(OSTREE)/root
	$(call do-install,$(TARGET_PATH),$@)
	@if ! [ -f $(OSTREE)/root/sys161.conf ]; then \
		$(call do-install,$(OSTREE)/sys161-default.conf,$(OSTREE)/root/sys161.conf); \
	fi

# Create a dummy makefile in the root that allows for easy rebuilds.
$(OSTREE)/root/Makefile: | $(TARGET_PATH)
	@mkdir -p $(OSTREE)/root
	$(call do-show-gen,$@)
	@echo -e "all:\n\t+@make -s -C ..\n\nclean:\n\t+@make -s -C .. clean" > $@

# Files that we install.
install:: $(OSTREE)/root/kernel $(OSTREE)/root/Makefile

clean-installed-kernel:
	@rm -f $(OSTREE)/root/kernel

$(abspath compile/autoconf.h compile/autoconf.c):
	$(call do-show-gen,$(abspath compile/autoconf.c))
	$(call do-show-gen,$(abspath compile/autoconf.h))
	@sh gen-autoconf.sh

.PHONY: vers-c-always-rebuilds clean-installed-kernel

# IMPORTANT: If we delete the vers.c, then we will have to come up with another
# way to force the kernel to be deleted / regenerated on rebuild.
$(abspath compile/vers.c): vers-c-always-rebuilds
	$(call do-show-gen,$@)
	@sh gen-newvers.sh $(CONFIG)

clean::
# Note: We don't clean compile/version, because the version number should not
# necessarily be updated between make cleans.
#
# It will be deleted by ./configure, though.
	$(call do-show-clean,$(abspath compile)/*.h)
	@rm -f compile/*.h
	$(call do-show-clean,$(abspath compile)/*.c)
	@rm -f compile/*.c