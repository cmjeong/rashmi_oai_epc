###############################################################################
#
# Makefile Options:
#
#  make [clean] BUILD=<build>
#
# Copyright � 3Way Networks Ltd
#
###############################################################################

TOP = $(shell pwd)/../../..
PRODUCT = generic
HARDWARE=generic
BUILD=i686-linux
LDFLAGS = -lpthread -Wl, -R../lib/:./
include $(TOP)/makefrags/products.mk

TARGET_NAME = fap-trace-logger
TARGET_DIR = obj/$(HARDWARE)/$(BUILD)
CPPFLAGS = -Werror

include $(TOP)/makefrags/application.mk
