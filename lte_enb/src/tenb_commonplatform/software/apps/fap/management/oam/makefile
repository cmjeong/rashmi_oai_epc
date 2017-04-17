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

TARGET_NAME = oam

SRC_DIRS = managed-objects

LIB_DEPS = \
  $(TOP)/libs/messaging/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libthreeway-messaging \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
  $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet \
  $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system \
  $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
  $(TOP)/libs/mib-core/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-core \
  #$(TOP)/libs/common/clog/obj/$(HARDWARE)/$(BUILD)/libRadisys-clog \
  #$(TOP)/apps/utilities/fap-flash/shared/$(HARDWARE)\

SYSTEM_LIBS = pthread
# We only have OSS libs for BF533+2006 and BF537+2008 (and i686)
# but we wing it when doing 3.1+2008 by using the BF537 versions...
#LIB_DEPS_PREBUILT = $(TOP)/thirdparty/oss/libs/$(BUILD)/libasn1code

LIB_DEPS_PREBUILT = 

ifneq ($(findstring bfin-uclinux-2008,$(BUILD)),bfin-uclinux-2008)
  SYSTEM_LIBS+=dl
endif

INCLUDE_PATHS = \
  $(CWD) \
  $(CWD)/managed-objects \
  $(TOP)/apps/fap \
  $(TOP)/apps/utilities \
  $(TOP)/libs/messaging \
  $(TOP)/thirdparty/oss/include/$(BUILD) \
  $(TOP)/libs/messaging/transport \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/generic/generic \
  $(TOP)/libs/mib-core \
  $(TOP)/../../enbapp/wr \
  $(TOP)/../../enbapp/

ifeq ($(PLATFORM),brdcm)
   CPPFLAGS = -Dlinux -DLTE_REM -g3 -Dx__ARMCC_VERSION -DPLATFORM_BRDCM -Werror
else
   CPPFLAGS = -Dlinux -DLTE_REM -g3 -Dx__ARMCC_VERSION -Werror
endif
vpath %.cpp $(TOP)/apps/fap/ntp-client/Ver2  $(TOP)/apps/utilities/fap-flash/shared

CPP_SRCS =  StateMachine.cpp #NorFlash.cpp

BFIN_UCLINUX_APP_STACK_SIZE = 0x80000

include $(TOP)/makefrags/application.mk
