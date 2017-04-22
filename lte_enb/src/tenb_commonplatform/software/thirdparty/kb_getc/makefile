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

TARGET_NAME = kb_getc

INCLUDE_PATHS = \
  $(TOP)/thirdparty/kb_getc

ifeq ($(STATICALLY_LINKED),yes)
  include $(TOP)/makefrags/staticlibrary.mk
else
  include $(TOP)/makefrags/sharedlibrary.mk
endif
