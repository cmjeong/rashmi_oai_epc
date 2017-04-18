###############################################################################
#
# Makefile Options:
#
#  make [clean] PRODUCT=<product> [BUILD=<build>]
#
# Copyright (C) radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../..
include $(TOP)/makefrags/products.mk

TARGET_NAME = ike-tunnel-ind

LIB_DEPS = 

SYSTEM_LIBS = 

CFLAGS=-Wall

BFIN_UCLINUX_APP_STACK_SIZE = 0x80000

include $(TOP)/makefrags/application.mk
