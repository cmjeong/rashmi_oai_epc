###############################################################################
#
# Makefile Options:
#
#  make [clean] BUILD=<build>
#
# Copyright Radisys Limited
#
###############################################################################

TOP = $(shell pwd)/../../..

TARGET_NAME = Radisys-clog

INCLUDE_PATHS = \
  $(TOP)/libs/common \
  $(TOP)/libs/common/include

# Blackfin can't use the lockfree algorithm since the processor lacks the
#  required atomic compare-and-swap instructions
ifneq ($(HARDWARE),hbs2-3-5)
CFLAGS=-DCLOG_LOCKFREE
endif

ifeq ($(PLTFRM),PAL)
LDFLAGS=-lgcc -m32 -Wl, -R../lib/:./
else
LDFLAGS=-lgcc -Wl, -R../lib/:./
endif

ifeq ($(STATICALLY_LINKED),yes)
  include $(TOP)/makefrags/staticlibrary.mk
else
  include $(TOP)/makefrags/sharedlibrary.mk
endif
