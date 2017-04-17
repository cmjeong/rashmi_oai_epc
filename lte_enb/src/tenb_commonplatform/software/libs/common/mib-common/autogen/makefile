###############################################################################
#
# Makefile Options:
#
#  make [clean]
#
# Copyright Radisys Limited
#
###############################################################################

PRODUCT=test
override BUILD=i686-linux
override HARDWARE=generic
STATICALLY_LINKED=yes  # for libxml2...only the static version is provided
TOP = $(shell pwd)/../../../..

include $(TOP)/makefrags/products.mk
TARGET_NAME = radisys-mib-autogen
TARGET_DIR = obj

REDHAT := $(wildcard /etc/redhat-release)
ifeq ($(strip $(REDHAT)),)
INCLUDE_PATHS = \
  . \
  $(TOP)/libs/bin/libxml2-2.7.2/$(HARDWARE)/$(BUILD)/include/libxml2

LIB_DEPS_PREBUILT = \
  $(TOP)/libs/bin/libxml2-2.7.2/$(HARDWARE)/$(BUILD)/lib/libxml2 
else
INCLUDE_PATHS = \
  . \
  $(TOP)/libs/bin/libxml2/$(HARDWARE)/$(BUILD)/include/libxml2

LIB_DEPS_PREBUILT = \
  $(TOP)/libs/bin/libxml2/$(HARDWARE)/$(BUILD)/lib/libxml2 
endif

SYSTEM_LIBS = pthread

include $(TOP)/makefrags/application.mk

