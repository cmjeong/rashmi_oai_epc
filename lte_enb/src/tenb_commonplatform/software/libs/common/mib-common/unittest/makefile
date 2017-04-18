###############################################################################
#
# Makefile Options:
#
#  make [run|clean]
#
# Copyright Radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../../..

TARGET_NAME = Radisys-mib-common-unittest

INCLUDE_PATHS = \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/generic/generic \
  $(TOP)/libs/common/mib-common \
  $(TOP)/libs/common

LIB_DEPS = \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common
  
include $(TOP)/makefrags/unittest_sharedlibrary.mk
