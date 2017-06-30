#********************************************************************20**
#
#       Name:   LTE eNodeB Sample Application
#
#       Type:   make file
#
#       Desc:   Compile, assemble and link product software for
#               various configurations. Further comments are
#               embedded in the file. 
#
#               This file supports a variety of environments and
#               build targets. The default build target will be the
#               portable target for the Linu 2.4.x with GNU C(gcc)
#
#       Env:    Linux 2.4.x with GNU C (gcc)
#
#               BUILD TARGETS:
#
#               clean            remove all object files
#   
#       File:  makefile
#
#
#       Prg:   an
#
#********************************************************************21*/
#=======================================================================

# Identify the location our software which is used by rest
# of the build scripts
include ../common/rsys_fancy.mak
include ../common/env.mak

RULE=$(COLOR_RED)
OPTS=$(COLOR_GREEN)
NORM=$(REVERT_COLOR)

ROOT_DIR=$(ROOT_DIR_PAL)
export ROOT_DIR

# For improved speed
CPUINFO=`cat /proc/cpuinfo | grep processor| wc -l`
ifeq ($(CPUINFO), 1)
   NUM_PARALLEL=1
else
   NUM_PARALLEL=$(shell echo $(CPUINFO) - 1 |bc)
endif

ifeq ($(FAST), 1)
   NUM_PARALLEL=$(shell echo $(CPUINFO) + 2 |bc)
endif

PARALLEL_COMP=-j $(NUM_PARALLEL) 
#PARALLEL_COMP=-j 1

# Different options to CPUH and CPUL builds
# Other apsects of tool chain set here
# These should be made available appropriately to the builds

CC          =gcc -m32
CC_STRIP    =strip --strip-all
CC_LINKER   =gcc -m32
CCPP        =g++ -m32
CCPP_LINKER =g++ -m32

CC1= $(CC)
CCPP1= $(CCPP)
CC2= $(CC)
CCPP2= $(CCPP)
CC3= $(CC)
CCPP3= $(CCPP)

ifeq ($(MODE),TDD)
echo -e "TDD Mode on x_86 is not valid. Resetting to Default"
#CNM_ENABLE = YES
CNM_ENABLE=NO
MODE=FDD
else
CNM_ENABLE=NO
endif

#-----------------------------------------------------------------------
# macro for output file name and makefile name
#
prepare_dirs:
	$(Q)echo -e "Preparing directories for build..."
	$(Q)mkdir -p $(BUILD_DIR)/obj/pal/ll2
	$(Q)mkdir -p $(LOG_ROOT)/pal/ll2
	$(Q)mkdir -p $(LIB_ROOT)/pal/ll2
	$(Q)mkdir -p $(BUILD_DIR)/obj/pal/ul2
	$(Q)mkdir -p $(LOG_ROOT)/pal/ul2
	$(Q)mkdir -p $(LIB_ROOT)/pal/ul2
	$(Q)mkdir -p $(BUILD_DIR)/obj/pal/l3
	$(Q)mkdir -p $(LOG_ROOT)/pal/l3
	$(Q)mkdir -p $(LIB_ROOT)/pal/l3
	$(Q)echo -e "Directories are successfully prepared"


ifeq ($(CNM_ENABLE),YES) 
CNM_OPT = -DxENABLE_CNM -DREM_ENABLE -DCNM_DEBUG
else
CNM_OPT = -UENABLE_CNM -UREM_ENABLE
endif

   PLTFRM_FLAGS= -UMSPD $(CNM_OPT)

ifeq ($(MODE),TDD) 
   PLTFRM_FLAGS += -DMODE=TDD
endif
ifeq ($(CA_ENABLE),YES)
   PLTFRM_FLAGS += -DCA_ENABLE=YES
endif
ifeq ($(TIP),YES)
   PLTFRM_FLAGS += -DTIP_OAM
endif
ifeq ($(SRS_PHY),YES)
   PLTFRM_FLAGS += -DSRS_PHY -DUSE_PURE
endif

# The include options get merged with the options needed by
# the called makefiles and hence we export these to make them
# available to them.
PLTFRM=PAL
BUILD=i686-linux


# The called makefiles depend on these macros and these need to be exported
export PLTFRM
export PLTFRM_FLAGS
export BUILD
export I_OPTS

# Add to the linker options the platform specific components
L_OPTS+=-lnsl -lrt -lm -lpthread 


# Export some of the flags expected from the command line.
# These macros are made available for the makefiles called from this makefile
export BOARD
export MODE
export OAM_ENABLE
export CNM_ENABLE
export TEXT_LOG
export CA_ENABLE

###################################################################################################
#	TeNB Compilation Options	- Help Menu
###################################################################################################
help:
	@echo -e "******************************************************************"
	@echo -e "BUILD COMMAND            DESCRIPTION                              "
	@echo -e "------------------------------------------------------------------"
	@echo -e "$(RULE)tenb - Builds all components of TeNB$(NORM)"
	@echo -e "$(OPTS)  options: $(NORM)"
	@echo -e "$(OPTS)    TEXT_LOG=YES   - With text logging instead of binary$(NORM)"
	@echo -e "$(OPTS)    OAM_ENABLE=YES - OAM as part of the solution$(NORM)"
	@echo -e "$(OPTS)    TIP=YES        - For TIP based architecture$(NORM)"
	@echo -e "$(OPTS)    MODE=TDD       - Not valid for x_86. Default MODE=FDD$(NORM)"
	@echo -e "$(RULE)clean_all         tdd cleanup everything $(NORM)"
	@echo -e "******************************************************************"

enb_upperl2:
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2  CC='$(CC3)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC3)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC3)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC3)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC3)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC3)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC3)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC3)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CCPP2)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC2)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC2)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC2)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC2)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC2)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC2)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC2)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC2)' TIP_UPPER_L2=YES
ifeq ($(SRS_PHY),YES)
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys_srs.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC2)' TIP_UPPER_L2=YES
else
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys_pal.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC2)' TIP_UPPER_L2=YES
endif
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sec.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC2)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/tip.mak OBJ_DIR=$(OBJ_ROOT)/pal/ul2 LIB_DIR=$(LIB_ROOT)/pal/ul2 LOG_DIR=$(LOG_ROOT)/pal/ul2 CC='$(CC2)' TIP_UPPER_L2=YES

enb_lowerl2:
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2  CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CCPP3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
ifeq ($(SRS_PHY),YES)
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys_srs.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
else
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys_pal.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES
endif
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sec.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC2)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/tip.mak OBJ_DIR=$(OBJ_ROOT)/pal/ll2 LIB_DIR=$(LIB_ROOT)/pal/ll2 LOG_DIR=$(LOG_ROOT)/pal/ll2 CC='$(CC3)' TIP_LOWER_L2=YES

enb_l3: oam
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3  CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CCPP1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
ifeq ($(SRS_PHY),YES)
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys_srs.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
else
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys_pal.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES
endif
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sec.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC2)' TIP_L3=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/tip.mak OBJ_DIR=$(OBJ_ROOT)/pal/l3 LIB_DIR=$(LIB_ROOT)/pal/l3 LOG_DIR=$(LOG_ROOT)/pal/l3 CC='$(CC1)' TIP_L3=YES

enb: oam
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal  CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CCPP1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
ifeq ($(SRS_PHY), YES)
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys_srs.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
else
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys_pal.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
endif
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sec.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/tip.mak OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'

oam:
	$(MAKE) -f $(COM_BUILD_DIR)/oam.mak

###################################################################################################
#	TeNB REM Compilation
###################################################################################################
rem: oam
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rem.mak rem

ifeq ($(TIP), YES)
link_enb: link_l3 link_ll2 link_ul2
else
link_enb: link_all
endif

ifeq ($(OAM_ENABLE), YES)
link_all:enb 
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/pal/enodeb -Wl,-R../lib/:. $(OBJ_ROOT)/pal/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/pal $(L_OAM) -L$(ROOT_DIR)/libs/pal -lrm -lnl

link_l3: enb_l3
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/pal/l3/enodeb_l3 -Wl,-R../lib/:. $(OBJ_ROOT)/pal/l3/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/pal/l3 $(L_OAM) -L$(ROOT_DIR)/libs/pal/l3 -lrm -lnl

#link_ul2: enb_upperl2
	# Linking to build CPUH binary
#	$(Q)$(CC1) -g -o $(OBJ_ROOT)/pal/ul2/enodeb_ul2 -Wl,-R../lib/:. $(OBJ_ROOT)/pal/ul2/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/pal/ul2 $(L_OAM) -L$(ROOT_DIR)/libs/pal/ul2 -lrm -lnl

#link_ll2: enb_lowerl2
	# Linking to build CPUH binary
#	$(Q)$(CC1) -g -o $(OBJ_ROOT)/pal/ll2/enodeb_ll2 -Wl,-R../lib/:. $(OBJ_ROOT)/pal/ll2/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/pal/ll2 $(L_OAM) -L$(ROOT_DIR)/libs/pal/ll2 -lrm -lnl

else
link_all: enb
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/pal/enodeb -Wl,-R../lib/:. $(OBJ_ROOT)/pal/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/pal -L$(ROOT_DIR)/libs/pal -lrm -lnl

link_l3: enb_l3
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/pal/l3/enodeb_l3 -Wl,-R../lib/:. $(OBJ_ROOT)/pal/l3/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/pal/l3 -L$(ROOT_DIR)/libs/pal/l3 -lrm -lnl
endif
link_ul2: enb_upperl2
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/pal/ul2/enodeb_ul2 -Wl,-R../lib/:. $(OBJ_ROOT)/pal/ul2/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/pal/ul2 -L$(ROOT_DIR)/libs/pal/ul2 -L$(ROOT_DIR)/libs/pal/ul2/libsec.a -lrm -lnl

link_ll2: enb_lowerl2
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/pal/ll2/enodeb_ll2 -Wl,-R../lib/:. $(OBJ_ROOT)/pal/ll2/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/pal/ll2 -L$(ROOT_DIR)/libs/pal/ll2 -lrm -lnl
#endif

clean_rem:	
	$(MAKE) -f $(COM_BUILD_DIR)/rem.mak clean

clean_oam:
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/oam.mak clean

clean_ps:
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak clean OBJ_DIR=$(BUILD_DIR)/obj/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC2)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC2)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC2)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC2)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak clean OBJ_DIR=$(BUILD_DIR)/obj/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC2)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sec.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/tip.mak clean OBJ_DIR=$(OBJ_ROOT)/pal LIB_DIR=$(LIB_ROOT)/pal LOG_DIR=$(LOG_ROOT)/pal CC='$(CC1)'

clean_all: clean_rem clean_ps clean_oam
	
###################################################################################################
#	TeNB Compilation- Binary Logging with OAM, Watchdog and REM
###################################################################################################

#tenb: prepare_dirs prepare_code oam rem net_cluster radio_cluster link_net link_radio copy_build

tenb: prepare_dirs prepare_code oam rem copy_build

prepare_code:
	$(Q)rsync -a $(ROOT_DIR)/src/enbapp/wr_smm_init_pal.c $(ROOT_DIR)/src/enbapp/wr_smm_init.c
	$(Q)rsync -a $(ROOT_DIR)/src/enbapp/wr_sw_version_pal_fdd.c $(ROOT_DIR)/src/enbapp/wr_sw_version.c
	$(Q)rsync -a $(ROOT_DIR)/src/ltepdcp/pj_ptlib_pal.c $(ROOT_DIR)/src/ltepdcp/pj_ptlib.c
	$(Q)rsync -a $(ROOT_DIR)/src/cm/envopt_pal.h $(ROOT_DIR)/src/cm/envopt.h

copy_build: link_enb
ifeq ($(TIP), YES)
ifeq ($(OAM_ENABLE),YES)
	@echo -e "Copying eNodeB tip with oam build..."
	$(Q)echo . | . ./TeNBCP_build linux
	$(Q)mkdir -p rsys rsys/config rsys/bin rsys/scripts
	$(Q)mkdir -p $(ROOT_DIR)/bin/unstripped
ifneq ($(TEXT_LOG), YES)
	$(Q)cp -f ./obj/pal/l3/rlogapp rsys/bin/
	$(Q)cat $(LOG_ROOT)/pal/l3/*.db > $(LOG_ROOT)/pal/l3/rlog.logdb
	$(Q)cat $(LOG_ROOT)/pal/ll2/*.db > $(LOG_ROOT)/pal/ll2/rlog.logdb
	$(Q)cat $(LOG_ROOT)/pal/ul2/*.db > $(LOG_ROOT)/pal/ul2/rlog.logdb
	$(Q)cp -f $(LOG_ROOT)/pal/l3/rlog.logdb rsys/bin/rlog_l3.logdb
	$(Q)cp -f $(LOG_ROOT)/pal/ll2/rlog.logdb rsys/bin/rlog_ll2.logdb
	$(Q)cp -f $(LOG_ROOT)/pal/ul2/rlog.logdb rsys/bin/rlog_ul2.logdb
endif
	$(Q)cp -f ./obj/pal/l3/enodeb_l3 ./rsys/bin
	$(Q)cp -f ./obj/pal/ll2/enodeb_ll2 ./rsys/bin
	$(Q)cp -f ./obj/pal/ul2/enodeb_ul2 ./rsys/bin
	$(Q)cp -f ../config/wr_cfg_fdd.txt ./rsys/bin/wr_cfg.txt
	$(Q)cp -f ../config/ys_cfg.txt ./rsys/bin/ys_cfg.txt
	$(Q)cp -f ../config/ssi_mem_net ./rsys/config
	$(Q)cp -f ../config/ssi_mem_radio ./rsys/config
	$(Q)cp -f ../config/ssi_mem ./rsys/config
	$(Q)cp -f ./rsys/config/configFile_tip_4cells ./rsys/config/configFile
	$(Q)cp -f ../scripts/start_ul2_tip.sh ./rsys/bin/ul2.sh
	$(Q)cp -f ../scripts/start_ll2_tip.sh ./rsys_withoutoam/bin/ll2.sh
#	$(Q)cp -f ../scripts/l3_t33h.sh ./rsys/scripts/start_eNB.sh
#	$(Q)cp -f ../scripts/l1_t33h.sh $(ROOT_DIR)/l1
#	$(Q)cp -f ../config/icc_setup $(ROOT_DIR)/l1
#	$(Q)cp -f ../scripts/l2_t33h.sh ./rsys/bin
#	$(Q)cp -f ../config/icc_setup ./rsys/scripts
#	$(Q)cp -f $(ROOT_DIR)/src/lteremapp/obj/hbs2-iu/hbs2-4/arm-none-linux-gnueabi/rem  ./rsys/bin/
	$(Q)cp -rf ./rsys $(ROOT_DIR)/bin/
	$(Q)mkdir -p $(ROOT_DIR)/libs  $(ROOT_DIR)/libs/l3 $(ROOT_DIR)/libs/ll2 $(ROOT_DIR)/libs/ul2
	$(Q)cp -f ./lib/pal/l3/*.a $(ROOT_DIR)/libs/l3
	$(Q)cp -f ./lib/pal/ll2/*.a $(ROOT_DIR)/libs/ll2
	$(Q)cp -f ./lib/pal/ul2/*.a $(ROOT_DIR)/libs/ul2
#	$(Q)if [ -e $(ROOT_DIR)/src/lteremapp/libs/arm-none-linux-gnueabi/libssi.a ];then cp -f $(ROOT_DIR)/src/lteremapp/libs/arm-none-linux-gnueabi/* $(ROOT_DIR)/libs/;fi
else
	@echo -e "Copying eNodeB TIP without oam build..."
	$(Q)mkdir -p rsys_withoutoam  rsys_withoutoam/config rsys_withoutoam/bin
	$(Q)mkdir -p $(ROOT_DIR)/bin/unstripped
ifneq ($(TEXT_LOG), YES)
	$(Q)cp -f ./obj/pal/l3/rlogapp rsys_withoutoam/bin/
	$(Q)cat $(LOG_ROOT)/pal/l3/*.db > $(LOG_ROOT)/pal/l3/rlog.logdb
	$(Q)cat $(LOG_ROOT)/pal/ll2/*.db > $(LOG_ROOT)/pal/ll2/rlog.logdb
	$(Q)cat $(LOG_ROOT)/pal/ul2/*.db > $(LOG_ROOT)/pal/ul2/rlog.logdb
	$(Q)cp -f $(LOG_ROOT)/pal/l3/rlog.logdb rsys_withoutoam/bin/rlog_l3.logdb
	$(Q)cp -f $(LOG_ROOT)/pal/ll2/rlog.logdb rsys_withoutoam/bin/rlog_ll2.logdb
	$(Q)cp -f $(LOG_ROOT)/pal/ul2/rlog.logdb rsys_withoutoam/bin/rlog_ul2.logdb
	$(Q)echo -e "Completed generation of log database"
endif
	$(Q)cp -f ./obj/pal/l3/enodeb_l3 ./rsys_withoutoam/bin
	$(Q)cp -f ./obj/pal/ll2/enodeb_ll2 ./rsys_withoutoam/bin
	$(Q)cp -f ./obj/pal/ul2/enodeb_ul2 ./rsys_withoutoam/bin
	$(Q)cp -f ../config/wr_cfg_fdd.txt ./rsys_withoutoam/bin/wr_cfg.txt
	$(Q)cp -f ../config/ssi_mem ./rsys_withoutoam/config
	$(Q)cp -f ../config/ys_cfg.txt ./rsys_withoutoam/bin/ys_cfg.txt
	$(Q)cp -f ../config/ssi_mem_net ./rsys_withoutoam/config
	$(Q)cp -f ../config/ssi_mem_radio ./rsys_withoutoam/config
	$(Q)cp -f ../scripts/start_l3_tip.sh ./rsys_withoutoam/bin/l3.sh
	$(Q)cp -f ../scripts/start_ul2_tip.sh ./rsys_withoutoam/bin/ul2.sh
	$(Q)cp -f ../scripts/start_ll2_tip.sh ./rsys_withoutoam/bin/ll2.sh
#	$(Q)cp -f ../scripts/l3_t33h.sh ./rsys_withoutoam/scripts/start_eNB.sh
#	$(Q)cp -f ../scripts/l1_t33h.sh $(ROOT_DIR)/l1
#	$(Q)cp -f ../scripts/l2_t33h.sh ./rsys_withoutoam/bin
	$(Q)cp -rf ./rsys_withoutoam $(ROOT_DIR)/bin/
	$(Q)mkdir -p $(ROOT_DIR)/libs  $(ROOT_DIR)/libs/l3 $(ROOT_DIR)/libs/ll2 $(ROOT_DIR)/libs/ul2
	#cp -rf ../src/ltephy/mindSpeed/lowercore/transcede_libs/bin/libshm.so ../bin/rsys_withoutoam/ 
	$(Q)cp -f ./lib/pal/l3/*.a $(ROOT_DIR)/libs/l3
	$(Q)cp -f ./lib/pal/ll2/*.a $(ROOT_DIR)/libs/ll2
	$(Q)cp -f ./lib/pal/ul2/*.a $(ROOT_DIR)/libs/ul2
endif
else
ifeq ($(OAM_ENABLE),YES)
	@echo -e "Copying eNodeB with oam build..."
	$(Q)echo . | . ./TeNBCP_build linux
	$(Q)mkdir -p rsys rsys/config rsys/bin rsys/scripts 
	$(Q)mkdir -p $(ROOT_DIR)/bin/unstripped
ifneq ($(TEXT_LOG), YES)
	$(Q)cp -f ./obj/pal/rlogapp rsys/bin/
	$(Q)cat $(LOG_ROOT)/pal/*.db > $(LOG_ROOT)/pal/rlog.logdb
	$(Q)cp -f $(LOG_ROOT)/pal/rlog.logdb rsys/bin/
	$(Q)echo -e "Completed generation of log database"
endif
	$(Q)cp -f ./obj/pal/enodeb ./rsys/bin
	$(Q)cp -f ../config/ssi_mem ./rsys/config/
	$(Q)cp -f ../config/ssi_rem ./rsys/config/
	$(Q)cp -f ../../src/tenb_commonplatform/scripts/install_pal.sh ./rsys/scripts/install.sh
	$(Q)cp -f $(ROOT_DIR)/src/lteremapp/obj/hbs2-iu/hbs2-4/$(BUILD)/rem  ./rsys/bin/
	$(Q)cp -rf ./rsys $(ROOT_DIR)/bin/
	$(Q)mkdir -p $(ROOT_DIR)/libs/
	$(Q)cp -f ./lib/pal/*.a $(ROOT_DIR)/libs
	$(Q)if [ -e $(ROOT_DIR)/src/lteremapp/libs/$(BUILD)/libssi.a ];then cp -f $(ROOT_DIR)/src/lteremapp/libs/$(BUILD)/* $(ROOT_DIR)/libs/;fi
else
	@echo -e "Copying eNodeB build..."
	$(Q)mkdir -p rsys_withoutoam  rsys_withoutoam/config rsys_withoutoam/bin rsys_withoutoam/scripts 
	$(Q)mkdir -p $(ROOT_DIR)/bin/unstripped
ifneq ($(TEXT_LOG), YES)
	$(Q)cp -f ./obj/pal/rlogapp rsys_withoutoam/bin/
	$(Q)cat $(LOG_ROOT)/pal/*.db > $(LOG_ROOT)/pal/rlog.logdb
	$(Q)cp -f $(LOG_ROOT)/pal/rlog.logdb rsys_withoutoam/bin/
	$(Q)echo -e "Completed generation of log database"
endif
	$(Q)cp -f ./obj/pal/enodeb ./rsys_withoutoam/bin
	$(Q)cp -f ../config/wr_cfg_fdd.txt ./rsys_withoutoam/bin/wr_cfg.txt
	$(Q)cp -f ../config/ys_cfg.txt ./rsys_withoutoam/bin/ys_cfg.txt
	$(Q)cp -f ../config/ssi_mem ./rsys_withoutoam/config
	$(Q)cp -f ../config/ssi_mem_radio ./rsys_withoutoam/config
	$(Q)cp -f ../config/ssi_mem_net ./rsys_withoutoam/config
	$(Q)cp -f ../scripts/start_eNB.sh ./rsys_withoutoam/bin/start_eNB.sh
	#cp -rf ../src/ltephy/Libs/* ./rsys_withoutoam/l1
	$(Q)cp -rf ./rsys_withoutoam $(ROOT_DIR)/bin/
	$(Q)mkdir -p $(ROOT_DIR)/libs/
	#cp -rf ../src/ltephy/mindSpeed/lowercore/transcede_libs/bin/libshm.so ../bin/rsys_withoutoam/ 
	$(Q)cp -f ./lib/pal/*.a $(ROOT_DIR)/libs/
endif
endif
###################################################################################################
#													END OF MAKEFILE
###################################################################################################
