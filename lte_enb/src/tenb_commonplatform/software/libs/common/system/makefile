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

TARGET_NAME = threeway-system

INCLUDE_PATHS = \
  $(TOP)/libs \
  $(TOP)/libs/common \
  $(TOP)/libs/common/include\
  $(TOP)/../../enbapp/wr \
  $(TOP)/../../enbapp/

ifeq ($(PLATFORM),brdcm)
	CPPFLAGS= -DLTE_REM -DPLATFORM_BRDCM -Werror
else
CPPFLAGS= -DLTE_REM -Werror
endif
ifeq ($(STATICALLY_LINKED),yes)
  include $(TOP)/makefrags/staticlibrary.mk
else
  include $(TOP)/makefrags/sharedlibrary.mk
endif
