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

TARGET_NAME = threeway-comms

INCLUDE_PATHS = \
  $(TOP)/libs/common \
  $(TOP)/libs/common/include
ifeq ($(PLTFRM),PAL)
CPPFLAGS = -Werror -m32
else
CPPFLAGS = -Werror 
endif

ifeq ($(STATICALLY_LINKED),yes)
  include $(TOP)/makefrags/staticlibrary.mk
else
  include $(TOP)/makefrags/sharedlibrary.mk
endif
