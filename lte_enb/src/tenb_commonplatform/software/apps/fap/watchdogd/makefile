
###############################################################################
#
# Makefile Options:
#
#  make [clean] PRODUCT=<product> [BUILD=<build>]
#
# Copyright Radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../..
include $(TOP)/makefrags/products.mk

TARGET_NAME = watchdogd

LIB_DEPS = \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
  $(TOP)/libs/messaging/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libthreeway-messaging \
  $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet \
  $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
  $(TOP)/libs/common/clog/obj/$(HARDWARE)/$(BUILD)/libRadisys-clog \
  $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system

SYSTEM_LIBS = pthread

CFLAGS=-Wall
CPPFLAGS=-Wall -Werror

INCLUDE_PATHS = \
  $(TOP)/apps \
  $(TOP)/libs/messaging/transport

BFIN_UCLINUX_APP_STACK_SIZE = 0x80000

include $(TOP)/makefrags/application.mk
