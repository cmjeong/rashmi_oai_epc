###############################################################################
#
# Makefile Options:
#
#  make [clean] [BUILD=<build>]
#
# Copyright Radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../..
include $(TOP)/makefrags/products.mk

TARGET_NAME = dump-enum-ids

LIB_DEPS = \
  $(TOP)/libs/messaging/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libthreeway-messaging \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
  $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet \
  $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
  $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system

SYSTEM_LIBS = pthread

BFIN_UCLINUX_APP_STACK_SIZE = 0x10000
CPPFLAGS = -Werror

include $(TOP)/makefrags/application.mk
