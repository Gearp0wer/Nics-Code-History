TARGET_NAME=$(abspath crt0.o)
SOURCE=$(abspath $(PLATFORM)-crt0.S)

include ../../mk/core.mk

# Assemble the crt0 for the current platform. Depend on .config in case
# the platform gets changed.
$(TARGET_NAME): $(SOURCE) ../../.config $(OSTREE)/kern/compile/machine-lnk
	$(call do-cc,$@,$<,$(CFLAGS))

clean::
	$(call do-clean,crt0.o)