# A configuration checker to make sure as many things are correct as possible.
# Should be included after .config.

# As a basic check, make sure that OSTREE exists.
ifeq ($(OSTREE),)
  $(error OSTREE variable is empty. Makefile will not work. Try running ./configure)
endif

# Ensure that the OSTREE has the expected files.
# This should help to make absolutely sure that OSTREE works as expected.
ifeq ($(wildcard $(OSTREE)/kern),)
  $(error Could not find kern folder -- OSTREE seems to be misconfigured -- try running ./configure)
endif
ifeq ($(wildcard $(OSTREE)/mk),)
  $(error Could not find mk folder -- OSTREE seems to be misconfigured -- try running ./configure)
endif
ifeq ($(wildcard $(OSTREE)/lib),)
  $(error Could not find lib folder -- OSTREE seems to be misconfigured -- try running ./configure)
endif

# Make sure that our THIS_DIR logic works.
# Note: The alternative would be to always include .config in our Makefiles, to ensure
# that we could use $(OSTREE). But that makes userspace program Makefiles slightly less
# clean.
THIS_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

ifneq ($(OSTREE)/mk/,$(THIS_DIR))
  $(info Note: THIS_DIR = $(THIS_DIR))
  $(info Note: needs to = $(OSTREE)/mk/)
  $(info Note: If your path has spaces in it, you likely need to move os161 somewhere else to work on it.)
  $(error Makefile THIS_DIR logic does not work. Note that compiling inside a directory with spaces in the name is not supported)
endif

# Check that we have a valid PLATFORM
# In theory we could check multiple options -- but because we only support mips,
# ensure that the platform is mips
ifneq ($(PLATFORM),mips)
  $(error Unsupported platform "$(PLATFORM). Your .config is misconfigured. Try running ./configure")
endif

# For the CC, AR, LD, we could also ensure that they MUST be cs161-gcc --
# but for now let's use a warning.
ifneq ($(CC),cs161-gcc)
  $(warning WARNING C compiler "$(CC)" is unlikely to work. You probably want to use cs161-gcc. Try running ./configure)
endif
ifneq ($(LD),cs161-gcc)
  $(warning WARNING Linker "$(LD)" is unlikely to work. You probably want to use cs161-gcc. Try running ./configure)
endif
ifneq ($(AR),cs161-ar)
  $(warning WARNING Archiver "$(AR)" is unlikely to work. You probably want to use cs161-ar. Try running ./configure)
endif