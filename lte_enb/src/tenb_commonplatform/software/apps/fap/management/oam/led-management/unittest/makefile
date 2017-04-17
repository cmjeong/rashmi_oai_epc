###############################################################################
#
# Makefile Options:
#
#  make [clean]
#
# Copyright radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../../../../..

TARGET_NAME = led-unittest

CPP_SRCS = \
  FiatLux.cpp \
  Led_fsm.cpp \
  LedInfo.cpp \
  LedBehaviour_v3_5.cpp \
  LedBehaviour_v4.cpp \
  oam_env.cpp

vpath %.cpp ..
vpath %.cpp ../..
vpath %.cpp ../plat-v3.5
vpath %.cpp ../plat-v4
vpath %.cpp $(TOP)/libs/messaging/messages/oam

INCLUDE_PATHS = \
  $(TOP)/apps/fap \
  $(TOP)/apps/fap/management/oam/led-management \
  $(TOP)/apps/fap/management/oam/led-management/plat-v3.5 \
  $(TOP)/apps/fap/management/oam/led-management/plat-v4 \
  $(TOP)/libs/messaging/messages/oam \
  $(TOP)/libs/messaging/unittest
  

include $(TOP)/makefrags/unittest_sharedlibrary.mk
