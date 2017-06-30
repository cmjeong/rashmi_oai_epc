###############################################################################
#
# Makefile Options:
#
#  make [clean] PRODUCT=<product> [BUILD=<build>]
#
# Copyright radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../../..
include $(TOP)/makefrags/products.mk

newall: build

TARGET_NAME = mib-firkler

LIB_DEPS = \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
  $(TOP)/libs/mib-core/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-core \
  $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet \
  $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
  $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system \

INCLUDE_PATHS = \
  $(TOP)/apps/fap

vpath %.cpp $(TOP)/apps/fap/management/oam
CPP_SRCS = MibHelper.cpp

SYSTEM_LIBS = pthread

ifeq ($(BUILD),i686-linux)
SYSTEM_LIBS+=dl
endif

BFIN_UCLINUX_APP_STACK_SIZE = 0x8000

include $(TOP)/makefrags/application.mk
