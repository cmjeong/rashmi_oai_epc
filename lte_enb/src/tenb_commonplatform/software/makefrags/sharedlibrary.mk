##############################################################################
#
# Makefile fragment for building a shared library under Linux.
# Before including this fragment, make sure you have set
# TOP, TARGET_DIR, TARGET_NAME & INCLUDE_PATHS
# E.g.
#
# TOP = $(shell pwd)/../../../..
# TARGET_DIR = obj/$(HARDWARE)/$(BUILD)
# TARGET_NAME = threeway-comms
# INCLUDE_PATHS = \
#	../../include \
#	../../include/comms
#
# TOP and TARGET_DIR default to the values above if not specified in the
# calling makefile.
#
# Built library is 'lib<TARGET_NAME>.so'
#
##############################################################################

# Libraries are *generally* product agnostic.
ifeq ($(PRODUCTAWARE), yes)
  TARGET_DIR ?= obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)
  INSTALL_DIR ?= $(TOP)/libs/bin/threeway/$(PRODUCT)/$(HARDWARE)/$(BUILD)
endif

include $(TOP)/makefrags/products.mk

# Build AND install libraries.
newbuild: install
install: build

# Set TARGET_DIR and INSTALL_DIR if not set already.
TARGET_DIR ?= obj/$(HARDWARE)/$(BUILD)
# Put all libraries in the same place so we don't need long lists
# of library paths.
INSTALL_DIR ?= $(TOP)/libs/bin/threeway/$(HARDWARE)/$(BUILD)

LIB_BASES = $(subst lib,,$(notdir $(LIB_DEPS))) \
            $(subst lib,,$(notdir $(LIB_DEPS_STATIC))) \
            $(subst lib,,$(notdir $(LIB_DEPS_PREBUILT)))

LIB_PATHS := $(LIB_PATHS) $(dir $(LIB_DEPS)) $(dir $(LIB_DEPS_STATIC)) \
             $(dir $(LIB_DEPS_PREBUILT)) $(dir $(LIB_DEPS_PREBUILT_STATIC))

# Set up the actual target.
ifeq ($(BUILD),i686-linux)
  TARGET_NAME := lib$(TARGET_NAME).so
else
  ifeq ($(BUILD),arm-none-linux-gnueabi)
    TARGET_NAME := lib$(TARGET_NAME).so
  else
	 ifeq ($(BUILD),mipsel-unknown-linux-gnu)
	   TARGET_NAME := lib$(TARGET_NAME).so
	 else
    ifeq ($(BUILD),i686-pc-cygwin)
      TARGET_NAME := lib$(TARGET_NAME).dll
    else
      $(error Can't build shared library for BUILD=$(BUILD))
	   endif
    endif
  endif
endif

CPP_SRCS := $(CPP_SRCS) $(wildcard *.cpp)
C_SRCS   := $(C_SRCS) $(wildcard *.c)

vpath %.h $(INCLUDE_PATHS)

ifneq ($(BUILD),i686-pc-cygwin)
  CXXFLAGS += -fPIC
  CFLAGS   += -fPIC
  LDFLAGS  += -fPIC
endif

ifeq ($(PLTFRM),PAL)
CPPFLAGS += $(INCLUDE_PATHS:%=-I%) -m32
else
CPPFLAGS += $(INCLUDE_PATHS:%=-I%)
endif

CFLAGS   += -Wall -Wno-unknown-pragmas -fmessage-length=0 -std=gnu99
ifeq ($(PLTFRM),PAL)
CXXFLAGS += -Wall -Wno-unknown-pragmas -fmessage-length=0 -m32
LDFLAGS  := -m32 -Wall -Wl,-R../lib/:./ -fmessage-length=0 -g -shared $(LIBS:%=-l%) $(LIB_BASES:%=-l%) $(LIB_PATHS:%=-L%) $(LDFLAGS)
else
CXXFLAGS += -Wall -Wno-unknown-pragmas -fmessage-length=0
LDFLAGS  := -Wall -Wl,-R../lib/:./ -fmessage-length=0 -g -shared $(LIBS:%=-l%) $(LIB_BASES:%=-l%) $(LIB_PATHS:%=-L%) $(LDFLAGS)
endif
# Keep debug info in i686-linux builds, optimise other builds.
ifeq ($(BUILD),i686-linux)
  CFLAGS   += -g
  CXXFLAGS += -g
else
  CFLAGS   += -O2
  CXXFLAGS += -O2
endif

include $(TOP)/makefrags/base.mk
