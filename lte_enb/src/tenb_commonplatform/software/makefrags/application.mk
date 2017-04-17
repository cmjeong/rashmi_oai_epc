##############################################################################
#
# Makefile fragment for building an application under Linux.
# Before including this fragment, make sure you have set
# TARGET_DIR, INSTALL_DIR, TARGET_NAME, LIBS & INCLUDE_PATHS
# E.g.
#
# TOP = $(shell pwd)/../../..
# TARGET_DIR = obj
# TARGET_NAME = myapp
# LIBS = threeway-comms threeway-system
# INCLUDE_PATHS = \
#	../../include
#
# TARGET_DIR defaults to 'obj/PRODUCT/BUILD' if not
# specified in the calling makefile.
#
# TOP points at the 'software' directory.
#
##############################################################################

include $(TOP)/makefrags/products.mk

ifeq ($(BUILD_BASE),bfin-uclinux)
ifeq ($(BFIN_UCLINUX_APP_STACK_SIZE),)
  $(error BFIN_UCLINUX_APP_STACK_SIZE must be set)
endif
endif

# Set TARGET_DIR if not set already.
TARGET_DIR ?= obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)

# Include paths.
INCLUDE_PATHS := \
  $(TOP)/libs/common \
  $(TOP)/libs/common/include \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/generic/generic \
  $(TOP)/libs \
  $(TOP)/thirdparty/md5/obj/$(HARDWARE)/$(BUILD) \
  $(TOP)/thirdparty/kb_getc/obj/$(HARDWARE)/$(BUILD) \
  $(INCLUDE_PATHS)

CPP_SRCS := $(CPP_SRCS) $(wildcard *.cpp)
C_SRCS   := $(C_SRCS) $(wildcard *.c)

vpath %.h $(INCLUDE_PATHS)

LIB_BASES = $(subst lib,,$(notdir $(LIB_DEPS)))
LIB_BASES_STATIC = $(subst lib,,$(notdir $(LIB_DEPS_STATIC)))
LIB_BASES_PREBUILT = $(subst lib,,$(notdir $(LIB_DEPS_PREBUILT)))
LIB_BASES_PREBUILT_STATIC = $(subst lib,,$(notdir $(LIB_DEPS_PREBUILT_STATIC)))

LIB_PATHS := $(LIB_PATHS) $(dir $(LIB_DEPS)) $(dir $(LIB_DEPS_STATIC)) \
             $(dir $(LIB_DEPS_PREBUILT)) $(dir $(LIB_DEPS_PREBUILT_STATIC))

CPPFLAGS += $(INCLUDE_PATHS:%=-I%)
CFLAGS   += -Wall -Wno-unknown-pragmas -fmessage-length=0 #-std=gnu99
CXXFLAGS += -Wall -Wno-unknown-pragmas -fmessage-length=0
LDFLAGS  := -Wall -W -fmessage-length=0 -g \
            -Wl,-Bstatic $(LIB_BASES_STATIC:%=-l%) $(LIB_BASES_PREBUILT_STATIC:%=-l%) \
            -Wl,-Bdynamic $(LIB_BASES:%=-l%) $(LIB_BASES_PREBUILT:%=-l%) $(SYSTEM_LIBS:%=-l%) \
				-Wl,-R../lib/:./ \
            $(LIB_PATHS:%=-L%) $(LDFLAGS)
			
# Keep debug info in i686-linux builds, optimise other builds.
ifeq ($(BUILD),i686-linux)
  CFLAGS   += -g
  CXXFLAGS += -g
else
ifdef DEBUG
  CFLAGS   += -g
  CXXFLAGS += -g
else
  OPTIMISATION ?= 2
  CFLAGS   += -O$(strip $(OPTIMISATION))
  CXXFLAGS += -O$(strip $(OPTIMISATION))
endif
endif

ifeq ($(ETH),USE_ETH1)
  CPPFLAGS += -DUSE_ETH1
  CFLAGS   += -DUSE_ETH1
  CXXFLAGS += -DUSE_ETH1
endif

# Set build specific stuff.
ifeq ($(BUILD_BASE),bfin-uclinux)
  LDFLAGS += -Wl,-elf2flt
endif

include $(TOP)/makefrags/base.mk
