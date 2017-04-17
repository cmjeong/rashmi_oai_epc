###############################################################################
#
# Makefile Options:
#
#  make [clean] PRODUCT=<product> [BUILD=<build>]
#
# Copyright Radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../../..
include $(TOP)/makefrags/products.mk

TARGET_NAME = ntp-client

LIB_DEPS = \
  $(TOP)/libs/messaging/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libthreeway-messaging \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
  $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
  $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system \
  $(TOP)/libs/common/clog/obj/$(HARDWARE)/$(BUILD)/libRadisys-clog \
  $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet

INCLUDE_PATHS = \
  $(TOP)/libs/messaging/transport

SYSTEM_LIBS = m crypt pthread

CPPFLAGS = -DDAC_DEBUG -DHAVE_CONFIG_H -Werror
CFLAGS =-Wcast-qual -Wmissing-prototypes -Wpointer-arith -Wshadow -Wstrict-prototypes
# -MT refclock_acts.o -MD -MP -MF ".deps/refclock_acts.Tpo" -c -o refclock_acts.o refclock_acts.c; \

BFIN_UCLINUX_APP_STACK_SIZE = 0x80000

include $(TOP)/makefrags/application.mk
