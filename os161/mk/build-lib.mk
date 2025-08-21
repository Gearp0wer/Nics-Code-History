THIS_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

TARGET_PREFIX?=

include $(THIS_DIR)core.mk

$(TARGET_PATH): $(C_OBJ_PATHS) $(S_OBJ_PATHS)
	$(call do-ar,$@,$^)




