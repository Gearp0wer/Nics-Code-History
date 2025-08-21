THIS_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# We let build-testbin.mk work for sbin and bin executables as well, as
# long as they specify the install directory. This makes it simpler to
# maintain--fewer nested "include"s.
INSTALL_DIR?=testbin

# IMPORTANT: crt0 must come become libc
LDFLAGS += $(OSTREE)/lib/crt0/crt0.o $(OSTREE)/lib/libc/libc.a 

TARGET_REQS = $(OSTREE)/lib/libc/libc.a $(OSTREE)/lib/crt0/crt0.o

include $(THIS_DIR)build-linked.mk

$(OSTREE)/lib/libc/libc.a:
	+make -C $(OSTREE)/lib/libc

$(OSTREE)/lib/crt0/crt0.o:
	+make -C $(OSTREE)/lib/crt0

$(OSTREE)/root/$(INSTALL_DIR)/$(TARGET_NAME): $(TARGET_PATH)
	@mkdir -p $(OSTREE)/root/$(INSTALL_DIR)
# Install this file in the $(INSTALL_DIR) directory.
	$(call do-install,$(TARGET_PATH),$@)

# For the top-level makefile to automatically detect that we want to rebuild,
# we need to indirectly show it our output files (our $(TARGET_PATH), and also
# the installed target), as it doesn't have a direct way to get that.
#
# Essentially, this list should include any file that, if it is out of date,
# we want it to be rebuilt for sure.
#
# That way the top-level makefile works as expected.
DESIRED_TARGETS=$(TARGET_PATH) $(OSTREE)/root/$(INSTALL_DIR)/$(TARGET_NAME)

# NOTE: For some reason we can't seem to make a rule so that make knows how
# to generate the C_DEP_PATHS.
#
# Instead, we depend on C_OBJ_PATHS, because we know that every time we compile
# the obj, the C_DEP_PATHS will also be up to date.
$(abspath depend.mk): $(C_SRC_PATHS) $(SRC_ASM) $(C_OBJ_PATHS)
	$(call do-show-gen,$@)
# truncate the file using >. The main recipe is the $(DESIRED_TARGETS), as those
# are what we actually want to buid.
	@echo "$(DESIRED_TARGETS):  \\" > depend.mk
# We extract all the files from the .d file and concatenate them together.
# We use 'awk' to remove duplicates (e.g. in the case of badcall).
#
# NOTE: This RELIES on the fact that we always call gcc with absolute paths.
# This makes it generate the .d files with absolute paths, and then we can
# simply extract the paths that way.
# If gcc did not give us absolute paths in this case, we would have to
# absolute-ify them ourselves.
	@cat $(foreach dep,$(C_DEP_PATHS),$(dep) ) | grep -oE " .*\.(c|h)" | awk '!seen[$$0]++' | sed -E 's|([^\n]+)|\1 \\|g' >> depend.mk
# finally, generate the actual recipe.
ifeq ($(MAKEFILE_COLORS),y)
	@echo -e "\n\t@echo -e \"\$$\$$(tput setaf 3)REBUILD \$$\$$(tput sgr0)$(TARGET_PATH)\"" >> depend.mk
else
	@echo -e "\n\t@echo -e \"REBUILD $(TARGET_PATH)\"" >> depend.mk
endif
	@echo -e "\t+@$(MAKE) -C $(dir $(abspath depend.mk)) -s all" >> depend.mk

# In order to indicate to make that we care about all of the DESIRED_TARGETS,
# we use an additional recipe of depend.mk: $(DESIRED_TARGETS).
	@echo -e "\n$(abspath depend.mk): $(DESIRED_TARGETS)" >> depend.mk

# Files that we install.
install:: $(OSTREE)/root/$(INSTALL_DIR)/$(TARGET_NAME) $(abspath depend.mk)

clean::
	$(call do-clean,$(abspath depend.mk))