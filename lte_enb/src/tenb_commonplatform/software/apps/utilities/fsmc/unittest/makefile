###############################################################################
#
# Makefile Options:
#  make all | clean
#
# Copyright Radisys Limited
#
###############################################################################
 
TOP = $(shell pwd)/../../../..
 
# Make sure target name is unique as the resulting shared library is put
# in a directory software/test/unittest/unittest-libs with all the other unit test libs.
TARGET_NAME = fsmc-unittest

FSM_BASENAME = FsmcUnitTest

include $(TOP)/makefrags/unittest_sharedlibrary.mk

FSMC = $(TOP)/apps/utilities/fsmc/fsmc

FSMC_GENERATED_FILES = \
 $(FSM_BASENAME)_fsm.h \
 $(FSM_BASENAME)_fsm_interface.h \
 $(FSM_BASENAME)_fsm.cpp

#.INTERMEDIATE: $(FSMC_GENERATED_FILES)
$(FSMC_GENERATED_FILES) : $(FSM_BASENAME).fsm $(FSMC)
	$(FSMC) $<



