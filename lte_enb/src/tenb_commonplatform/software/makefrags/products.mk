##############################################################################
#
# Makefile fragment to validate and set BUILD, PRODUCT and HARDWARE combinations.
#
# Will set BUILD based on HARDWARE if possible.
#
# TOP, PRODUCT and HARDWARE must be set.
#
##############################################################################

# Check TOP is set.
ifeq ($(TOP),)
  $(error TOP must be set and reference the top level 'software' directory)
endif

# Check PRODUCT is set.
ifeq ($(PRODUCT),)
  $(error PRODUCT must be set)
endif

ifneq ($(PRODUCT),hbs2-iu)
ifneq ($(PRODUCT),hbs2-sip)
ifneq ($(PRODUCT),hbs2-handbag)
ifneq ($(PRODUCT),hbs2-rrc)
ifneq ($(PRODUCT),hbs2-bae)
ifneq ($(PRODUCT),hbs2-factory)
ifneq ($(PRODUCT),pc-iu)
ifneq ($(PRODUCT),generic)
ifneq ($(PRODUCT),test)
  $(error PRODUCT must be one of hbs2-iu, hbs2-sip, hbs2-handbag, hbs2-rrc, hbs2-bae, hbs2-factory, pc-iu, generic or test)
endif
endif
endif
endif
endif
endif
endif
endif
endif

ifeq ($(PRODUCT),generic)
  HARDWARE = generic
  BUILD = i686-linux
endif

ifeq ($(PRODUCT),pc-iu)
  # Force settings
  HARDWARE = generic
  BUILD = i686-linux
endif

ifeq ($(PRODUCT),test)
  # Default to generic and i686-linux.
  HARDWARE ?= generic
  BUILD ?= i686-linux
endif

ifeq ($(BUILD),arm-none-linux-gnueabi)
  # Default to 4.0 
  HARDWARE ?= hbs2-4
else
ifeq ($(findstring hbs2,$(PRODUCT)),hbs2)
  # Default to 3.5 + 2008.
  HARDWARE ?= hbs2-3-5
  BUILD ?= bfin-uclinux-2008
endif
endif

ifeq ($(BUILD),mipsel-unknown-linux-gnu)
	  # Default to 4.0
	  HARDWARE ?= hbs2-4
endif

# Check HARDWARE is set.
ifeq ($(HARDWARE),)
  $(error HARDWARE must be set)
endif

# Target is either the target h/w or generic to build with current host defaults.
ifneq ($(HARDWARE),generic)
ifneq ($(HARDWARE),hbs2-3-1)
ifneq ($(HARDWARE),hbs2-3-5)
ifneq ($(HARDWARE),hbs2-4)
  $(error HARDWARE must be one of generic, hbs2-3-1, hbs2-3-5 or hbs2-4)
endif
endif
endif
endif

ifeq ($(HARDWARE),hbs2-3-1)
  BUILD ?= bfin-uclinux-2006
  STATICALLY_LINKED ?= yes
endif
ifeq ($(HARDWARE),hbs2-3-5)
  BUILD ?= bfin-uclinux-2008
  STATICALLY_LINKED ?= yes
endif
ifeq ($(HARDWARE),hbs2-4)
  BUILD ?= arm-linux
  STATICALLY_LINKED ?= no
endif
ifeq ($(HARDWARE),generic)
  BUILD ?= i686-linux
  STATICALLY_LINKED ?= no
endif

ifeq ($(BUILD),)
  $(error BUILD must be set)
endif

ifneq ($(BUILD),i686-linux)
ifneq ($(BUILD),bfin-uclinux-2006)
ifneq ($(BUILD),bfin-uclinux-2008)
ifneq ($(BUILD),bfin-uclinux-2008-mf)
ifneq ($(BUILD),i686-pc-cygwin)
ifneq ($(BUILD),arm-none-linux-gnueabi)
ifneq ($(BUILD),mipsel-unknown-linux-gnu)	
  $(error BUILD must be one of i686-linux, bfin-uclinux-2006, bfin-uclinux-2008, bfin-uclinux-2008-mf, arm-none-linux-gnueabi or i686-pc-cygwin)
endif  
endif
endif
endif
endif
endif
endif

BUILD_BASE = $(BUILD)
ifeq ($(findstring bfin-uclinux,$(BUILD)),bfin-uclinux)
  BUILD_BASE = bfin-uclinux
endif

export PRODUCT
export HARDWARE
export BUILD
STATICALLY_LINKED ?= yes
export STATICALLY_LINKED

ifeq ($(BUILD),arm-none-linux-gnueabi)
	REM_ENABLED ?= yes
	export REM_ENABLED=yes
endif
