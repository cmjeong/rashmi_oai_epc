###############################################################################
#
# Makefile Options:
#
#  make [clean] BUILD=<build>
#
# Copyright radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../..

TARGET_NAME = threeway-messaging

PRODUCTAWARE = yes

ifeq ($(PLTFRM),PAL)
CPPFLAGS= -DLTE_REM -Werror -m32
else
CPPFLAGS= -DLTE_REM -Werror
endif
INCLUDE_PATHS = \
  $(TOP)/libs \
  $(TOP)/libs/messaging/messages \
  $(TOP)/libs/messaging/transport \
  $(TOP)/libs/common/include \
  $(TOP)/libs/common \
  $(TOP)/libs/common/clog \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/generic/generic \
  $(TOP)/libs/nas/include \
  $(TOP)/libs/nas/include/lib-system \
  $(TOP)/thirdparty/encodix/Common \
  $(TOP)/libs/nas/lib-24008/codegen \
  $(TOP)/libs/nas/lib-25331/generated/$(BUILD_BASE) \
  $(TOP)/thirdparty/oss/include/$(BUILD)\
  $(TOP)/../src/lteremapp/inc \
  $(TOP)/../../enbapp/wr \
  $(TOP)/../../enbapp/

LIB_DEPS = $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
           $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet \
           $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
           $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system

# To make the library easier to use, set the runtime path to where the dependent libraries are installed
#  This avoids the need to set LD_LIBRARY_PATH for the dependent shared libs.
ifeq ($(BUILD), i686-linux)
LDFLAGS=-Wl,-rpath=`pwd`/../../libs/bin/threeway/$(HARDWARE)/$(BUILD):`pwd`/../../libs/bin/threeway/$(PRODUCT)/$(HARDWARE)/$(BUILD)
ifeq ($(PLTFRM),PAL)
LDFLAGS += -m32 -Wl,-R../lib/:./ 
else
LDFLAGS += -Wl,-R../lib/:./ 
endif
endif

SRC_DIRS = \
  messages/carb \
  messages/cli \
  messages/common \
  messages/cphy \
  messages/tenpin \
  messages/ike \
  messages/up-mgmt \
  messages/watchdog \
  messages/fntp \
  messages/oam \
  messages/rem \
  transport

ifeq ($(STATICALLY_LINKED),yes)
  include $(TOP)/makefrags/staticlibrary.mk
else
  include $(TOP)/makefrags/sharedlibrary.mk
endif
