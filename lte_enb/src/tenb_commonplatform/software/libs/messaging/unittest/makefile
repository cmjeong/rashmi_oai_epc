###############################################################################
#
# Makefile Options:
#
#  make [clean]
#
# Copyright radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../..

TARGET_NAME = threeway-messaging-unittest

LIB_DEPS = \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
  $(TOP)/libs/messaging/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libthreeway-messaging \
  $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet \
  $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
  $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system

include $(TOP)/makefrags/unittest_sharedlibrary.mk
