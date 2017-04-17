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

TARGET_NAME = threeway-theprotoprof

INCLUDE_PATHS = \
  ../../include \
  ../../include/theprotoprof

CPPFLAGS = -Werror

ifeq ($(STATICALLY_LINKED),yes)
  include $(TOP)/makefrags/staticlibrary.mk
else
  include $(TOP)/makefrags/sharedlibrary.mk
endif
