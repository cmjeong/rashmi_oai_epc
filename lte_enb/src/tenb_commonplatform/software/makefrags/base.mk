##############################################################################
#
# Makefile fragment for building C/C++ code with dependency checking.
#
# Before including this fragment, make sure you have set
# TOP, TARGET_DIR, TARGET, C_SRCS, CPP_SRCS, CFLAGS, CPPFLAGS, LDFLAGS
#
# E.g. Something like (this probably doesn't work but you get the idea):
#
#   TOP = $(shell pwd)/../../..
#	TARGET_DIR = obj
#   TARGET_NAME = myapp
#   C_SRCS = File1.c File2.c
#   CPP_SRCS = File3.cpp File4.cpp
#
# Optional variables:
#
#   CPPFLAGS = -I../include
#   CFLAGS = -Wall
#   CPPFLAGS = -Wall
#   LDFLAGS = -L../libs -lsystem
#
##############################################################################

# Disable implicit rules/targets to help speed up evaluation
MAKEFLAGS=-Rr --no-print-directory

include $(TOP)/makefrags/products.mk

#
# Check mandatory variables are set.
#
ifeq ($(TARGET_DIR),)
  $(error TARGET_DIR must be set)
endif

ifeq ($(TARGET_NAME),)
  $(error TARGET_NAME must be set)
endif

ifeq ($(PRODUCT),test)
CPPFLAGS += -fprofile-arcs -ftest-coverage
LDFLAGS += -fprofile-arcs -ftest-coverage
endif

ifeq ($(PRODUCT),generic)
CPPFLAGS += -fprofile-arcs -ftest-coverage
LDFLAGS += -fprofile-arcs -ftest-coverage
endif

#
# Targets.
#
.PHONY : all build install download objects clean deps

TARGET = $(TARGET_DIR)/$(TARGET_NAME)
TARGET_DIRS = $(TARGET_DIR) $($(dir $(CPP_SRCS)):%=$(TARGET_DIR)/%) $($(dir $(C_SRCS)):%=$(TARGET_DIR)/%)
INSTALL_DIR ?= $(TARGET_DIR)
CPP_DEP_FILES = $(CPP_SRCS:%.cpp=$(TARGET_DIR)/%.dpp)
C_DEP_FILES = $(C_SRCS:%.c=$(TARGET_DIR)/%.d)

# Object files.
ifndef RANDOMISE_COMPILE_ORDER
OBJS = $(CPP_SRCS:%.cpp=%.o) $(C_SRCS:%.c=%.o)
else
OBJS = $(shell $(TOP)/makefrags/randomise $(CPP_SRCS:%.cpp=%.o) $(C_SRCS:%.c=%.o))
endif

# Get the directories of dependent libraries so we can clean them up.
LIB_DEP_MAKE_DIRSX = $(subst /obj/$(PRODUCT)/$(HARDWARE)/$(BUILD),,$(dir $(LIB_DEPS) $(LIB_DEPS_STATIC)))  # remove obj/PRODUCT/HARDWARE/BUILD
LIB_DEP_MAKE_DIRS = $(subst /obj/$(HARDWARE)/$(BUILD),,$(LIB_DEP_MAKE_DIRSX))  # remove obj/HARDWARE/BUILD


LIB_DEP_MAKE_DIRS_BUILD = $(LIB_DEP_MAKE_DIRS:%=%.build)
LIB_DEP_MAKE_DIRS_CLEAN = $(LIB_DEP_MAKE_DIRS:%=%.clean)

all: build

objects: $(TARGET_DIR) $(OBJS:%.o=$(TARGET_DIR)/%.lo)

build: $(TARGET_DIR) $(TARGET)

deps:


clean: $(LIB_DEP_MAKE_DIRS_CLEAN)
	rm -rf $(TARGET_DIR)/*
	rm -f $(INSTALL_DIR)/$(TARGET_NAME) $(EXTRA_FILES_TO_CLEAN)

cleantarget:
	rm -f $(INSTALL_DIR)/$(TARGET_NAME)

install: $(INSTALL_DIR)/$(TARGET_NAME)

download: $(INSTALL_DIR)/$(TARGET_NAME)
	cd $(INSTALL_DIR) && $(TOP)/makefrags/msync $(FAPIP) $(TARGET_NAME) /mnt/bank-active/dbx/$(TARGET_NAME)

# Produce rule to copy target to install directory if different
ifneq ($(INSTALL_DIR), $(TARGET_DIR))
$(INSTALL_DIR)/$(TARGET_NAME): $(INSTALL_DIR) $(TARGET)
	@echo "Installing $(TARGET_NAME)"
	@cp $(TARGET) $(INSTALL_DIR)
endif

#
# Library stuff...
#

# Check for pre-built dependent dyamic libraries
ifneq ($(STATICALLY_LINKED),yes)
ifneq ($(LIB_DEPS_PREBUILT),)

# Installation location
INSTALL_DIR ?= $(TOP)/libs/bin/threeway/$(HARDWARE)/$(BUILD)

# Installation rules to copy shared library
install: install-prebuilt

install-prebuilt: $(LIB_DEPS_PREBUILT:%=%.so)
	$(Q)cp $^ $(INSTALL_DIR)

endif
endif

# Clean any libraries.
$(LIB_DEP_MAKE_DIRS_CLEAN):
	@echo "######## Cleaning library $(subst .clean,,$@) #########"
	$(MAKE) -C $(subst .clean,,$@) clean PRODUCT=$(PRODUCT)
	@echo "######## Completed $(subst .clean,,$@) #########"
	@echo ""

# If LIB_DEPS not empty, rebuild each library and generate a list
# of library filenames that target is dependent on to force a
# re-link if libs are newer.
# These libraries are shared libraries if the platform supports it
# or static if not e.g. bfin-uclinux-* doesn't (easily) support
# shared libraries.
ifeq ($(STATICALLY_LINKED),yes)
  LIB_NAMES = $(LIB_DEPS:%=%.a) $(LIB_DEPS_STATIC:%=%.a)
else
  LIB_NAMES = $(LIB_DEPS:%=%.so) $(LIB_DEPS_STATIC:%=%.a)
endif

# Make any libraries.
# Due to dependecy issues, ensure mib-common is built first.
$(filter-out %mib-common/.build,$(LIB_DEP_MAKE_DIRS_BUILD) ): $(filter %mib-common/.build,$(LIB_DEP_MAKE_DIRS_BUILD))

.PHONY:$(LIB_DEP_MAKE_DIRS_BUILD)
$(LIB_DEP_MAKE_DIRS_BUILD): %/.build:
	$(Q)$(MAKE) -C $(@D) PRODUCT=$(PRODUCT) STATICALLY_LINKED=$(STATICALLY_LINKED)

# Function!
derive_makefile_dir = $(subst /obj/$(HARDWARE)/$(BUILD),,$(subst /obj/$(PRODUCT)/$(HARDWARE)/$(BUILD),,$(dir $(1))))

# Definition!
define create_build_lib_rule
$(1):: $(call derive_makefile_dir,$(1)).build
	@cd .
endef

# Generate a list of explicit rules or the format:
# some/obj/dir/libexample.a : some/.build
# another/obj/dir/libdiff.a : another/.build
# etc...
$(foreach LIB,$(LIB_NAMES),$(eval $(call create_build_lib_rule,$(LIB))))

# If LIB_DEPS_PREBUILT or LIB_DEPS_PREBUILT_STATIC not empty, generate list of
# library filenames that target is dependent on to force a re-link if libs are newer.
LIB_NAMES_PREBUILT = $(LIB_DEPS_PREBUILT:%=%.a) $(sort $(LIB_DEPS_PREBUILT_STATIC:%=%.a))
$(TARGET): $(LIB_NAMES_PREBUILT)
$(LIB_NAMES_PREBUILT):
	@echo ######## Library $@ is prebuilt ########


#
# Compilers.
#

# If compiler(s) hasn't been specified and BUILD indicates we are building
# for some other host then use compilers for that host.
#TOOLCHAIN_PATH =
# if TOOLCHAIN_PATH is not defined then take the new path 
ifndef TOOLCHAIN_PATH
ifeq ($(findstring bfin-uclinux-2008,$(BUILD)),bfin-uclinux-2008)
  TOOLCHAIN_PATH=/opt/uClinux-2008R1.5/bfin-uclinux/bin/
endif
endif

# Distributed build requested
ifeq ($(DISTRIBUTE),1)

ifeq ($(BUILD),bfin-uclinux-2008)
ifneq ($(ICECC_BFIN_CXX),)
# BFIN makefile
  BASE_CC=/usr/lib/icecc/bin/gcc
  BASE_CPP=/usr/lib/icecc/bin/g++

  export ICECC_CXX=$(ICECC_BFIN_CXX)
  export ICECC_CC=$(ICECC_BFIN_CC)
  export ICECC_VERSION=$(ICECC_BFIN_VERSION)
else
ifneq ($(ICECC_CXX),)
# BFIN makefile BFIN specific settings not configured so use original generic settings.
    BASE_CC=/usr/lib/icecc/bin/gcc
    BASE_CPP=/usr/lib/icecc/bin/g++
endif
endif
endif

ifeq ($(BUILD),arm-none-linux-gnueabi)
ifneq ($(ICECC_ARM_CXX),)
# BFIN makefile
  BASE_CC=/usr/lib/icecc/bin/gcc
  BASE_CPP=/usr/lib/icecc/bin/g++

  export ICECC_CXX=$(ICECC_ARM_CXX)
  export ICECC_CC=$(ICECC_ARM_CC)
  export ICECC_VERSION=$(ICECC_ARM_VERSION)
else
ifneq ($(ICECC_CXX),)
# BFIN makefile BFIN specific settings not configured so use original generic settings.
    BASE_CC=/usr/lib/icecc/bin/gcc
    BASE_CPP=/usr/lib/icecc/bin/g++
endif
endif
endif


ifeq ($(BUILD),i686-linux)
ifneq ($(ICECC_i686_CXX),)
# i686 (32bit only Donald !)
  BASE_CC=/usr/bin/gcc
  BASE_CPP=/usr/bin/g++

  export ICECC_CXX=$(ICECC_i686_CXX)
  export ICECC_CC=$(ICECC_i686_CC)
  export ICECC_VERSION=$(ICECC_i686_VERSION)
endif
endif

endif


ifneq ($(BUILD),)
ifneq ($(BUILD),i686-linux)
ifneq ($(BUILD),i686-pc-cygwin)
  # No BUILD specified or is not i686-linux or i686-pc-cygwin so set compilers for target.
  BASE_CC ?= $(TOOLCHAIN_PATH)$(BUILD_BASE)-gcc
  BASE_CPP ?= $(TOOLCHAIN_PATH)$(BUILD_BASE)-g++
  BASE_AR ?= $(TOOLCHAIN_PATH)$(BUILD_BASE)-ar
endif
endif
endif

# If still no compilers use GNU ones.
BASE_CC ?= gcc
BASE_CPP ?= g++
BASE_AR ?= ar


#
# Compiler options.
#

# Set a define for the product for use in code.
PRODUCT_DEFINE:=$(subst -,_,$(PRODUCT))

# Set a define for the hardware for use in code.
HARDWARE_DEFINE:=$(subst -,_,$(HARDWARE))

# Set a define for the build for use in code.
BUILD_DEFINE:=$(subst -,_,$(BUILD))
ifeq ($(BUILD),bfin-uclinux-2008-mf)
  # Treat mudflap builds same as non-mudflap builds in the code.
  BUILD_DEFINE = bfin_uclinux_2008
endif

# Set a define for the target for use in code.
TARGET_DEFINE:=$(subst -,_,$(subst .,_,$(TARGET_NAME)))

# -Wno-reorder     Remove warnings due to constructor argument list in different order from class declaration.
# -Wno-format      Remove warnings due to %u, and not %ul in (s)printf.
# -Wno-deprecated  Remove warnings in Standard Template Library headers.
ifeq ($(PLTFRM),PAL)
CPPFLAGS += -m32 -DPRODUCT_$(PRODUCT_DEFINE) -DPRODUCT_STR=\"$(PRODUCT)\" -DHARDWARE_$(HARDWARE_DEFINE) -DBUILD_$(BUILD_DEFINE) -DBUILD=$(BUILD_DEFINE) -DTARGET_$(TARGET_DEFINE) -D__STDC_FORMAT_MACROS
CXXFLAGS += -m32 -Wno-reorder -fsigned-char
else
CPPFLAGS += -DPRODUCT_$(PRODUCT_DEFINE) -DPRODUCT_STR=\"$(PRODUCT)\" -DHARDWARE_$(HARDWARE_DEFINE) -DBUILD_$(BUILD_DEFINE) -DBUILD=$(BUILD_DEFINE) -DTARGET_$(TARGET_DEFINE) -D__STDC_FORMAT_MACROS
CXXFLAGS += -Wno-reorder -fsigned-char
endif
CFLAGS   += -fsigned-char

ifeq ($(ETH),USE_ETH1)
  CPPFLAGS += -DUSE_ETH1
endif

# As we try to obliterate warnings, we need to stage changes per tool chain version
ifneq (,$(findstring $(BUILD_BASE),bfin-uclinux arm-none-linux-gnueabi))
ifndef BUILD_WITH_WARNINGS
  #CXXFLAGS += -Werror
  #CFLAGS   += -Werror
endif
endif

# Target the correct processor when building.  Can only do this with 2008 toolchain.
# This enables the compiler to workaround processor errata.
ifeq ($(findstring bfin-uclinux-2008,$(BUILD)),bfin-uclinux-2008)
ifeq ($(HARDWARE),hbs2-3-5)
  CPPFLAGS += -mcpu=bf537-0.3
  CFLAGS   += -mcpu=bf537-0.3
  LDFLAGS  += -mcpu=bf537-0.3
endif
ifeq ($(HARDWARE),hbs2-3-1)
  CPPFLAGS += -mcpu=bf533-0.5
  CFLAGS   += -mcpu=bf533-0.5
  LDFLAGS  += -mcpu=bf533-0.5
endif
endif

# Mudflap build options.
ifeq ($(BUILD),bfin-uclinux-2008-mf)
  CFLAGS   += -fmudflapth
  CXXFLAGS += -fmudflapth
  LDFLAGS  += -lmudflapth
endif

ifeq ($(BUILD),arm-none-linux-gnueabi)
ifeq ($(HARDWARE),hbs2-4)
#  CPPFLAGS += -mcpu=cortex-a8 -mthumb
#  CFLAGS   += -mcpu=cortex-a8 -mthumb
#  LDFLAGS  += -mcpu=cortex-a8 -mthumb -rdynamic

  CPPFLAGS += -march=armv6 -mthumb
  CFLAGS   += -march=armv6 -mthumb
  LDFLAGS  += -march=armv6 -mthumb -rdynamic
endif
endif

ifeq ($(PLTFRM),PAL)
LDFLAGS += -m32 -Wl,-R../lib/:./
else
LDFLAGS += -Wl,-R../lib/:./
endif

ifdef DEMO16USERS_SIMS_2001
  CPPFLAGS += -DDEMO16USERS_SIMS_2001
endif

# Check for verbose build
ifneq ($(V),1)
 Q:=@
endif

#
# Additional directories for sources
#

ifneq ($(SRC_DIRS),)
  CPP_SRCS := $(CPP_SRCS) $(notdir $(wildcard $(SRC_DIRS:%=%/*.cpp)))
  vpath %.cpp $(SRC_DIRS:%=% : )
  C_SRCS := $(C_SRCS) $(notdir $(wildcard $(SRC_DIRS:%=%/*.c)))
  vpath %.c $(SRC_DIRS:%=% : )
endif

#
# Make the code.
#

# Sort removes duplicates to avoid warnings from make.
$(sort $(TARGET_DIRS) $(INSTALL_DIR)):
	mkdir -p $@

OBJ_DEPS = $(OBJS:%.o=$(TARGET_DIR)/%.lo)

# Don't start building code until all our libs are built as they may
# generate headers that we need.
$(OBJ_DEPS): $(filter %mib-common.a,$(LIB_NAMES)) $(filter %mib-common.so,$(LIB_NAMES))

ifeq ($(CREATE_ARCHIVE),yes)
$(TARGET): $(OBJ_DEPS)
	@echo "Archiving $(@F)"
	$(Q)$(BASE_AR) crs $@ $^
else
$(TARGET): $(OBJ_DEPS) $(LIB_NAMES)
	@echo "Linking $(@F)"
	$(Q)$(BASE_CPP) -o $@ $(OBJ_DEPS) $(LDFLAGS)
ifeq ($(BUILD_BASE),bfin-uclinux)
# Make sure we increase the application stack size for bfin-uclinux-* applications.
ifneq ($(BFIN_UCLINUX_APP_STACK_SIZE),)
	@echo "Changing $(@F) stack size to $(BFIN_UCLINUX_APP_STACK_SIZE)"
	$(Q)$(TOOLCHAIN_PATH)bfin-uclinux-flthdr -s $(BFIN_UCLINUX_APP_STACK_SIZE) $@
endif
# Normally compress bfin binaries but we may want to override this behaviour.
ifeq ($(BFIN_LINK_UNCOMPRESSED),)
	@echo "Compressing $(@F)"
	$(Q)$(TOOLCHAIN_PATH)bfin-uclinux-flthdr -z $@
else
	@echo "Leaving $(@F) uncompressed"
endif
endif
endif

$(TARGET_DIR)/%.lo: %.cpp
	@echo "Compiling $<"
	$(Q)$(WRAP_CXX) $(BASE_CPP) -o $@ -c $< $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -MT $@ -MF $(basename $@).dpp

$(TARGET_DIR)/%.lo: %.c
	@echo "Compiling $<"
	$(Q)$(WRAP_CC) $(BASE_CC) -o $@ -c $< $(CPPFLAGS) $(CFLAGS) -MMD -MP -MT $@ -MF $(basename $@).d

# For debug, allow pre-processed output to be easily grabbed
$(TARGET_DIR)/%.i: %.cpp
	@echo "Preprocessing $<"
	$(Q)$(BASE_CPP) -E $< -o $@ $(CPPFLAGS) $(CXXFLAGS)

$(TARGET_DIR)/%.i: %.c
	@echo "Preprocessing $<"
	$(Q)$(BASE_CPP) -E $< -o $@ $(CPPFLAGS) $(CFLAGS)

-include $(CPP_DEP_FILES) $(C_DEP_FILES)

