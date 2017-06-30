#*********************************************************************17*/
################################################################################
##
# Makefile Options:
#
#  make [clean] PRODUCT=<product> [BUILD=<build>]
#
# Copyright radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../../..
include $(TOP)/makefrags/products.mk

TARGET_NAME = fileTransMgr

LIB_DEPS = \
  $(TOP)/libs/messaging/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libthreeway-messaging \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
  $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet \
  $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
  $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system \
  $(TOP)/libs/mib-core/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-core

SYSTEM_LIBS = pthread

CFLAGS=-Wall
CPPFLAGS=-Wall -Werror

INCLUDE_PATHS = \
  $(TOP)/apps \
  $(TOP)/libs/messaging/transport
  
vpath %.cpp

BFIN_UCLINUX_APP_STACK_SIZE = 0x80000

include $(TOP)/makefrags/application.mk
