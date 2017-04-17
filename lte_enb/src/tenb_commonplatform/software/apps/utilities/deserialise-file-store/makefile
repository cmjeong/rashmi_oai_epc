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
PRODUCT = generic
include $(TOP)/makefrags/products.mk

TARGET_NAME = deserialise-file-store
TARGET_DIR = obj/$(HARDWARE)/$(BUILD)

LIB_DEPS = \
  $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system \
  $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet \
  $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
  $(TOP)/libs/mib-core/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-core \
  $(TOP)/libs/messaging/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libthreeway-messaging \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
#$(TOP)/libs/mib-core/obj/$(HARDWARE)/$(HARDWARE)/$(BUILD)/libRadisys-mib-core \
#$(TOP)/libs/nas/lib-system/obj/$(HARDWARE)/$(BUILD)/libsystem \
#$(TOP)/libs/nas/lib-comms/obj/$(HARDWARE)/$(BUILD)/libcomms \
#$(TOP)/apps/fap/management/oam-sm/obj/$(HARDWARE)/$(BUILD)/libsm \

INCLUDE_PATHS = \
    $(TOP)/../../enbapp/src/wr \
    $(TOP)/../../enbapp/src

SYSTEM_LIBS = pthread

BFIN_UCLINUX_APP_STACK_SIZE = 0x10000
CPPFLAGS = -Werror

include $(TOP)/makefrags/application.mk
