###############################################################################
#
# Makefile Options:
#
#  make [run|clean]
#
# Copyright radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../..

TARGET_NAME = Radisys-mib-core-unittest

INCLUDE_PATHS = \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/generic/generic \
  $(TOP)/libs/mib-core \
  $(TOP)/libs/common

LIB_DEPS = \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
  $(TOP)/libs/mib-core/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-core

include $(TOP)/makefrags/unittest_sharedlibrary.mk
