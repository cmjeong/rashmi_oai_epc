###############################################################################
#
# Makefile Options:
#
#  make [clean] PRODUCT=<product> [BUILD=<build>]
#
# Copyright radisys Limited
#
###############################################################################

CWD:= $(shell pwd)
TOP = $(shell pwd)/../../../..
include $(TOP)/makefrags/products.mk

newall: build

TARGET_NAME = tr069-v2

SRC_DIRS = autogen messages xml

LIB_DEPS = \
  $(TOP)/libs/messaging/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libthreeway-messaging \
  $(TOP)/libs/mib-core/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-core \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
  $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet \
  $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system \
  $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
  $(TOP)/thirdparty/md5/obj/$(HARDWARE)/$(BUILD)/libmd5\
  $(TOP)/libs/mib-core/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-core


SYSTEM_LIBS = pthread

LIB_DEPS_PREBUILT_STATIC = \
  $(TOP)/libs/bin/csoap/$(HARDWARE)/$(BUILD)/lib/libnanohttp \
  $(TOP)/libs/bin/csoap/$(HARDWARE)/$(BUILD)/lib/libcsoap \
  $(TOP)/libs/bin/libxml2-2.7.2/$(HARDWARE)/$(BUILD)/lib/libxml2 \
  $(TOP)/libs/bin/csoap/$(HARDWARE)/$(BUILD)/lib/libssl \
  $(TOP)/libs/bin/csoap/$(HARDWARE)/$(BUILD)/lib/libcrypto

CPPFLAGS = -DLTE_REM -Werror -DTIP_OAM
CFLAGS = -std=gnu99 -DTIP_OAM
LDFLAGS=-Wl,--no-as-needed -ldl

INCLUDE_PATHS = \
  $(CWD) \
  $(CWD)/messages \
  $(CWD)/xml \
  $(TOP)/apps/fap/management/oam \
  $(TOP)/apps/fap/management/update \
  $(TOP)/apps/utilities \
  $(TOP)/libs/bin/libxml2-2.7.2/$(HARDWARE)/$(BUILD)/include/libxml2 \
  $(TOP)/libs/bin/csoap/$(HARDWARE)/$(BUILD)/include/libcsoap-1.1 \
  $(TOP)/libs/bin/csoap/$(HARDWARE)/$(BUILD)/include/nanohttp-1.1 \
  $(TOP)/libs/messaging \
  $(TOP)/libs/messaging/transport \
  $(TOP)/apps/utilities/fap-flash/shared/$(HARDWARE) \
  $(TOP)/apps/utilities/fap-flash/shared  \
  $(TOP)/thirdparty/md5 \
  $(TOP)/../../enbapp/wr \
  $(TOP)/../../enbapp/

vpath %.cpp $(TOP)/apps/fap/management/oam
CPP_SRCS =  MibHelper.cpp

BFIN_UCLINUX_APP_STACK_SIZE = 0x80000

include $(TOP)/makefrags/application.mk
