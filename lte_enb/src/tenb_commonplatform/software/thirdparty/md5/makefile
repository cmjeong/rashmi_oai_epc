###############################################################################
#
# Makefile Options:
#
#  make [clean] BUILD=<build>
#
# Copyright radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../..

TARGET_NAME = md5

INCLUDE_PATHS = \
  $(TOP)/thirdparty/md5

ifeq ($(STATICALLY_LINKED),yes)
  include $(TOP)/makefrags/staticlibrary.mk
else
  include $(TOP)/makefrags/sharedlibrary.mk
endif
