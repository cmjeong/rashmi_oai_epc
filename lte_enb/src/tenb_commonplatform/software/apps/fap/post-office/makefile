###############################################################################
#
# Makefile Options:
#
#  make [clean] PRODUCT=<product>
#
# Copyright radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../..

TARGET_NAME = post-office

LIB_DEPS = \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
  $(TOP)/libs/messaging/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libthreeway-messaging \
  $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet \
  $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
  $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system
  #$(TOP)/libs/common/clog/obj/$(HARDWARE)/$(BUILD)/libRadisys-clog \

SYSTEM_LIBS = pthread

BFIN_UCLINUX_APP_STACK_SIZE = 0x80000

include $(TOP)/makefrags/application.mk
