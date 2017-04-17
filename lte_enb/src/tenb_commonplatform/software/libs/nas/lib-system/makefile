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

TARGET_NAME = system

INCLUDE_PATHS = \
  $(TOP)/libs/common \
  $(TOP)/libs/common/include \
  $(TOP)/libs/nas/include \
  $(TOP)/libs/nas/include/lib-system \
  $(TOP)/libs/nas/include/lib-comms \

CPPFLAGS = -Werror

ifeq ($(STATICALLY_LINKED),yes)
  include $(TOP)/makefrags/staticlibrary.mk
else
  include $(TOP)/makefrags/sharedlibrary.mk
endif
