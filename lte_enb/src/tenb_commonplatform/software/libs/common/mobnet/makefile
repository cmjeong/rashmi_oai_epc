###############################################################################
#
# Makefile Options:
#
#  make [clean] BUILD=<build>
#
# Copyright Radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../..

TARGET_NAME = threeway-mobnet

INCLUDE_PATHS = \
  $(TOP)/libs \
  $(TOP)/libs/common \
  $(TOP)/libs/common/include \
  $(TOP)/libs/nas/lib-25331/generated/$(BUILD_BASE) \
  $(TOP)/thirdparty/oss/include/$(BUILD)

ifeq ($(STATICALLY_LINKED),yes)
  include $(TOP)/makefrags/staticlibrary.mk
else
  include $(TOP)/makefrags/sharedlibrary.mk
endif
