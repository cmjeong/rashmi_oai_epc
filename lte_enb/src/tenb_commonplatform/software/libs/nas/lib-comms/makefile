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

TARGET_NAME = comms

INCLUDE_PATHS = \
  $(TOP)/libs/common \
  $(TOP)/libs/common/include \
  $(TOP)/libs/nas/include \
  $(TOP)/libs/nas/include/lib-system \
  $(TOP)/libs/nas/include/lib-comms \
  $(TOP)/libs/messaging/transport \
  $(TOP)/libs \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/generic/generic

CPPFLAGS = -Werror

ifeq ($(STATICALLY_LINKED),yes)
  include $(TOP)/makefrags/staticlibrary.mk
else
  include $(TOP)/makefrags/sharedlibrary.mk
endif
