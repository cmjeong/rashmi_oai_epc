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

ROOT_DIR=$(ROOT_DIR_INTEL)
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
ARCH = cortex-a9

CC          =arm-none-linux-gnueabi-gcc -mcpu=$(ARCH)
CC_STRIP    =arm-none-linux-gnueabi-strip --strip-all
CC_LINKER   =arm-none-linux-gnueabi-gcc -mcpu=$(ARCH) 
CCPP        =arm-none-linux-gnueabi-g++ -mcpu=$(ARCH)
CCPP_LINKER =arm-none-linux-gnueabi-g++ -mcpu=$(ARCH)

CC1= $(CC)
CCPP1= $(CCPP)

ifeq ($(MODE),TDD)
CNM_ENABLE = YES
else
CNM_ENABLE=NO
endif

#-----------------------------------------------------------------------
# macro for output file name and makefile name
#
prepare_dirs:
	$(Q)echo -e "Preparing directories for build..."
	$(Q)mkdir -p $(BUILD_DIR)/obj/tip/ll2
	$(Q)mkdir -p $(BUILD_DIR)/obj/tip/ul2
	$(Q)mkdir -p $(BUILD_DIR)/obj/t22
	$(Q)mkdir -p $(BUILD_DIR)/obj/t33/net
	$(Q)mkdir -p $(BUILD_DIR)/obj/t33/radio
	$(Q)mkdir -p $(LOG_ROOT)/tip/ll2
	$(Q)mkdir -p $(LOG_ROOT)/tip/ul2
	$(Q)mkdir -p $(LOG_ROOT)/t22
	$(Q)mkdir -p $(LOG_ROOT)/t33/net
	$(Q)mkdir -p $(LOG_ROOT)/t33/radio
	$(Q)mkdir -p $(LIB_ROOT)/tip/ll2
	$(Q)mkdir -p $(LIB_ROOT)/tip/ul2
	$(Q)mkdir -p $(LIB_ROOT)/t22
	$(Q)mkdir -p $(LIB_ROOT)/t33/net
	$(Q)mkdir -p $(LIB_ROOT)/t33/radio
	$(Q)echo -e "Directories are successfully prepared"


ifeq ($(CNM_ENABLE),YES) 
CNM_OPT = -DxENABLE_CNM -DREM_ENABLE -DCNM_DEBUG
else
CNM_OPT = -UENABLE_CNM -UREM_ENABLE
endif

ifeq ($(BOARD),T33H) 
   PLTFRM_FLAGS= -DMSPD $(CNM_OPT) -DBOARD=T33H
ifeq ($(RADIO_CLUSTER),YES)
   PLATFRM_FLAGS+= -DRADIO_CLUSTER
endif
else
   PLTFRM_FLAGS= -DMSPD $(CNM_OPT)
endif

ifeq ($(MODE),TDD) 
   PLTFRM_FLAGS += -DMODE=TDD
endif
ifeq ($(CA_ENABLE),YES)
   PLTFRM_FLAGS += -DCA_ENABLE=YES
endif

# The include options get merged with the options needed by
# the called makefiles and hence we export these to make them
# available to them.
ifeq ($(CA_ENABLE),YES)
PHYPATH=$(ROOT_DIR)/src/ltephy
else
PHYPATH=$(ROOT_DIR)/src/ltephy_nonca
endif
SPACCPATH=$(ROOT_DIR)/src/t2k_spacc
I_OPTS+=-isystem $(PHYPATH)/transcede_libs/
I_OPTS+=-isystem $(PHYPATH)/transcede_libs/api
I_OPTS+=-isystem $(PHYPATH)/common
I_OPTS+=-isystem $(PHYPATH)/syscore/services/
I_OPTS+=-isystem $(PHYPATH)/phy/include
I_OPTS+=-isystem $(PHYPATH)/phy/c-code
I_OPTS+=-I$(SPACCPATH)
I_OPTS+=-I$(SPACCPATH)/include
I_OPTS+=-I$(PHYPATH)/test_mac/src/platform
PLTFRM=INTEL
BUILD=arm-none-linux-gnueabi


# The called makefiles depend on these macros and these need to be exported
export PLTFRM
export PLTFRM_FLAGS
export BUILD
export I_OPTS

# Add to the linker options the platform specific components
L_OPTS+=-L$(PHYPATH)/transcede_libs/bin -L$(ROOT_DIR)/src/t2k_spacc
L_OPTS+=-liccserv -lnsl -lrt -lm -lpthread -lshm -lmlog -lntl $(SPACCPATH)/libspaccdev.so 


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
	@echo -e "$(OPTS)    BOARD=T33H    - For SoC T33H. Default is T2K$(NORM)"
	@echo -e "$(OPTS)    TEXT_LOG=YES   - With text logging instead of binary$(NORM)"
	@echo -e "$(OPTS)    OAM_EANBLE=YES - OAM as part of the solution$(NORM)"
	@echo -e "$(OPTS)    MODE=TDD       - If not specified, MODE=FDD$(NORM)"
	@echo -e "$(OPTS)    CA_ENABLE=YES  - If not specified, CA_ENABLE=NO$(NORM)"
	@echo -e "$(RULE)remlib            Builds remapp$(NORM)"
	@echo -e "$(RULE)clean_ps          tdd cleanup everything EXCEPT OAM & REMAPP$(NORM)"
	@echo -e "$(RULE)clean_all         tdd cleanup everything EXCEPT OAM & REMAPP$(NORM)"
	@echo -e "$(RULE)clean_rem         cleanup remapp$(NORM)"
	@echo -e "******************************************************************"

enb_lowerl2:
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2  CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CCPP1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/tip.mak OBJ_DIR=$(OBJ_ROOT)/tip/ll2 LIB_DIR=$(LIB_ROOT)/tip/ll2 LOG_DIR=$(LOG_ROOT)/tip/ll2 CC='$(CC1)' TIP_LOWER_L2=YES

enb_upperl2:
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2  CC='$(CC1)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CCPP1)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_UPPER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_LOWER_L2=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/tip.mak OBJ_DIR=$(OBJ_ROOT)/tip/ul2 LIB_DIR=$(LIB_ROOT)/tip/ul2 LOG_DIR=$(LOG_ROOT)/tip/ul2 CC='$(CC1)' TIP_LOWER_L2=YES


enb: oam
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22  CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CCPP1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys.mak OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'

net_cluster: oam
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CCPP1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES

radio_cluster:
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CCPP1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak OBJ_DIR=$(BUILD_DIR)/obj/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES

oam:
	$(MAKE) -f $(COM_BUILD_DIR)/oam.mak

###################################################################################################
#	TeNB REM Compilation
###################################################################################################
rem: oam
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rem.mak rem

ifeq ($(BOARD), T33H)
link_enb: link_net link_radio
else
ifeq ($(TIP),YES)
link_enb: link_ll2 link_ul2
else
link_enb: link_all
endif
endif

ifeq ($(OAM_ENABLE), YES)
link_ll2:enb_lowerl2
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/tip/ll2/enodeb_ll2 -Wl,-R../lib/:. $(OBJ_ROOT)/tip/ll2/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/tip/ll2 $(L_OAM) -L$(ROOT_DIR)/libs/tip/ll2 -lrm -lnl

link_ul2:enb_upperl2
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/tip/ul2/enodeb -Wl,-R../lib/:. $(OBJ_ROOT)/tip/ul2/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/tip/ul2 $(L_OAM) -L$(ROOT_DIR)/libs/tip/ul2/ -lrm -lnl

link_all:enb 
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/t22/enodeb -Wl,-R../lib/:. $(OBJ_ROOT)/t22/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/t22 $(L_OAM) -L$(ROOT_DIR)/libs/t22 -lrm -lnl

link_net: net_cluster
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/t33/net/enodeb_net -Wl,-R../lib/:. $(OBJ_ROOT)/t33/net/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/t33/net $(L_OAM) -L$(ROOT_DIR)/libs/t33/net -lrm -lnl

link_radio: radio_cluster
	# Linking to build CPUL binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/t33/radio/enodeb_radio -Wl,-R../lib/:.  $(OBJ_ROOT)/t33/radio/*.o \
	$(L_OPTS) -L$(LIB_ROOT)/t33/radio $(L_OAM)  -L$(ROOT_DIR)/libs/t33/radio -lrm -lnl
else
link_ll2:enb_lowerl2
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/tip/ll2/enodeb_ll2 -Wl,-R../lib/:. $(OBJ_ROOT)/tip/ll2/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/tip/ll2  -L$(ROOT_DIR)/libs/tip/ll2 -lrm -lnl

link_ul2:enb_upperl2
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/tip/ul2/enodeb_ul2 -Wl,-R../lib/:. $(OBJ_ROOT)/tip/ul2/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/tip/ul2 -L$(ROOT_DIR)/libs/tip/ul2 -lrm -lnl

link_all: enb
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/t22/enodeb -Wl,-R../lib/:. $(OBJ_ROOT)/t22/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/t22 -L$(ROOT_DIR)/libs/t22 -lrm -lnl

link_net: net_cluster
	# Linking to build CPUH binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/t33/net/enodeb_net -Wl,-R../lib/:. $(OBJ_ROOT)/t33/net/*.o\
    $(L_OPTS) -L$(LIB_ROOT)/t33/net -L$(ROOT_DIR)/libs/t33/net -lrm -lnl

link_radio: radio_cluster
	# Linking to build CPUL binary
	$(Q)$(CC1) -g -o $(OBJ_ROOT)/t33/radio/enodeb_radio -Wl,-R../lib/:.  $(OBJ_ROOT)/t33/radio/*.o \
	$(L_OPTS) -L$(LIB_ROOT)/t33/radio  -L$(ROOT_DIR)/libs/t33/radio
endif

clean_rem:	
	$(MAKE) -f $(COM_BUILD_DIR)/rem.mak clean

clean_oam:
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/oam.mak clean

clean_ps:
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak clean OBJ_DIR=$(BUILD_DIR)/obj/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC2)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC2)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC2)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC2)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak clean OBJ_DIR=$(BUILD_DIR)/obj/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC2)'
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak clean OBJ_DIR=$(OBJ_ROOT)/t22 LIB_DIR=$(LIB_ROOT)/t22 LOG_DIR=$(LOG_ROOT)/t22 CC='$(CC1)'

clean_net:
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CCPP1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak clean OBJ_DIR=$(BUILD_DIR)/obj/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak clean OBJ_DIR=$(BUILD_DIR)/obj/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/net LIB_DIR=$(LIB_ROOT)/t33/net LOG_DIR=$(LOG_ROOT)/t33/net CC='$(CC1)' NET_CLUSTER=YES

clean_radio:
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nh.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/wr.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sb.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/hi.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/sz.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cz.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/eg.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/nl.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rm.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CCPP1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak clean OBJ_DIR=$(BUILD_DIR)/obj/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rg.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/kw.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/ys.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/pj.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/cm.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/rl.mak clean OBJ_DIR=$(BUILD_DIR)/obj/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES
	$(Q)$(MAKE) -f $(COM_BUILD_DIR)/mt.mak clean OBJ_DIR=$(OBJ_ROOT)/t33/radio LIB_DIR=$(LIB_ROOT)/t33/radio LOG_DIR=$(LOG_ROOT)/t33/radio CC='$(CC1)' RADIO_CLUSTER=YES


ifneq ($(BOARD),T33H)
clean_all: clean_rem clean_ps clean_oam
else
clean_all: clean_rem clean_net clean_radio clean_oam
endif
	
###################################################################################################
#	TeNB Compilation- Binary Logging with OAM, Watchdog and REM
###################################################################################################

#tenb: prepare_dirs prepare_code oam rem net_cluster radio_cluster link_net link_radio copy_build

tenb: prepare_dirs prepare_code oam rem copy_build

copy_Intel_L1Bins:
ifeq  ($(MODE),TDD)
	$(Q)$(MAKE) copy_IntelTdd_L1Bins
else
	$(Q)$(MAKE) copy_IntelFdd_L1Bins
endif

copy_IntelFdd_L1Bins:
ifneq ($(CA_ENABLE),YES)
	mkdir -p $(ROOT_DIR)/l1
	/bin/cp -f $(PHYPATH)/bin/LteApp_DL.a $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/bin/LteApp_UL.a $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/ltert/l1.sh $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/ltert/ltel1 $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/ltert/phycfg.xml $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/transcede_libs/bin/libshm.so $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/ltert/phycfg_timer.xml $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/ltert/mapcode.xml $(ROOT_DIR)/l1/
else
	mkdir -p $(ROOT_DIR)/l1
	/bin/cp -f $(PHYPATH)/bin/LteApp0.a $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/bin/LteApp1.a $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/bin/LteApp2.a $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/bin/LteApp3.a $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/ltert/ltel1 $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/ltert/phycfg.xml $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/transcede_libs/bin/libshm.so $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/ltert/phycfg_timer.xml $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/ltert/mapcode.xml /$(ROOT_DIR)/l1/
endif
copy_IntelTdd_L1Bins:
ifneq ($(CA_ENABLE),YES)
	mkdir -p $(ROOT_DIR)/l1
	/bin/cp -f $(PHYPATH)/bin/LteApp_DL.a $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/bin/LteApp_UL.a $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/ltert/l1.sh $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/ltert/ltel1 $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/ltert/phycfg.xml $(ROOT_DIR)/l1/
	/bin/cp -f $(PHYPATH)/transcede_libs/bin/libshm.so $(ROOT_DIR)/l1/
else
	mkdir -p ../l1
	/bin/cp -rf $(PHYPATH)/primary/ ../l1/
	/bin/cp -rf $(PHYPATH)/secondary/ ../l1/
	/bin/cp -rf $(PHYPATH)/script/ ../l1/
	/bin/cp -f $(PHYPATH)/ltert/phycfg_timer.xml ../l1/
endif

copy_oam_bins_libs:
	$(Q) cp -rf ./oambins/*  ./rsys/bin/.
	$(Q) cp -rf ./oamlibs/*  ./rsys/libs/. 

prepare_code:
ifeq ($(BOARD), T33H)
	$(Q)rsync -a  $(ROOT_DIR)/src/enbapp/wr_smm_init_t33.c $(ROOT_DIR)/src/enbapp/wr_smm_init.c
	$(Q)rsync -a $(ROOT_DIR)/src/enbapp/wr_sw_version_t3300_fdd.c $(ROOT_DIR)/src/enbapp/wr_sw_version.c
	$(Q)rsync -a $(ROOT_DIR)/src/ltepdcp/pj_ptlib_t33.c $(ROOT_DIR)/src/ltepdcp/pj_ptlib.c
else
ifeq ($(TIP),YES)
	$(Q)rsync -a $(ROOT_DIR)/src/enbapp/wr_smm_init_pal.c $(ROOT_DIR)/src/enbapp/wr_smm_init.c
	$(Q)rsync -a $(ROOT_DIR)/src/enbapp/wr_sw_version_t2200_fdd.c $(ROOT_DIR)/src/enbapp/wr_sw_version.c
	$(Q)rsync -a $(ROOT_DIR)/src/ltepdcp/pj_ptlib_t2k.c $(ROOT_DIR)/src/ltepdcp/pj_ptlib.c
else
	$(Q)rsync -a $(ROOT_DIR)/src/enbapp/wr_smm_init_t2k.c $(ROOT_DIR)/src/enbapp/wr_smm_init.c
	$(Q)rsync -a $(ROOT_DIR)/src/enbapp/wr_sw_version_t2200_fdd.c $(ROOT_DIR)/src/enbapp/wr_sw_version.c
	$(Q)rsync -a $(ROOT_DIR)/src/ltepdcp/pj_ptlib_t2k.c $(ROOT_DIR)/src/ltepdcp/pj_ptlib.c
endif
endif

copy_build: link_enb
ifeq ($(BOARD), T33H)
ifeq ($(OAM_ENABLE),YES)
	@echo -e "Copying eNodeB Build, REM and Watchdog"
	$(Q)rm -rf ./rsys
	$(Q)echo . | . ../brcm/TeNBCP_build mspd
	$(Q)mkdir -p rsys/slave
	$(Q)mkdir -p $(ROOT_DIR)/bin/unstripped
	$(Q)cp -f ./obj/t33/net/enodeb_net ./rsys/bin
	$(Q)cp -f ./obj/t33/radio/enodeb_radio ./rsys/bin
	$(Q)arm-none-linux-gnueabi-strip -S ./rsys/bin/*
	$(Q)$(MAKE) copy_Intel_L1Bins
	$(Q)cp -f ../config/ssi_mem_net ./rsys/config
	$(Q)cp -f ../config/ssi_mem_radio ./rsys/slave
	$(Q)cp -f ../config/ssi_rem ./rsys/config/
	$(Q)cp -f ../scripts/l3_t33h.sh ./rsys/scripts/start_eNB.sh
	$(Q)cp -f ../scripts/l1_t33h.sh $(ROOT_DIR)/l1
	$(Q)cp -f ../config/icc_setup $(ROOT_DIR)/l1
	$(Q)cp -f ../scripts/l2_t33h.sh ./rsys/bin
	$(Q)cp -f ../config/icc_setup ./rsys/scripts
	$(Q)cp -rf ./rsys $(ROOT_DIR)/bin/unstripped/.
ifneq ($(TEXT_LOG), YES)
	$(Q)cp -f ./obj/t33/net/rlogapp rsys/bin/
	$(Q)cat $(LOG_ROOT)/t33/net/*.db > $(LOG_ROOT)/t33/net/rlog.logdb
	$(Q)cat $(LOG_ROOT)/t33/radio/*.db > $(LOG_ROOT)/t33/radio/rlog.logdb
	$(Q)cp -f $(LOG_ROOT)/t33/net/rlog.logdb rsys/bin/rlog_net.logdb
	$(Q)cp -f $(LOG_ROOT)/t33/radio/rlog.logdb rsys/slave/rlog_radio.logdb
endif
	$(Q)cp -rf ./rsys $(ROOT_DIR)/bin/

	$(Q)mkdir -p $(ROOT_DIR)/libs  $(ROOT_DIR)/libs/net $(ROOT_DIR)/libs/radio
	$(Q)cp -f ./lib/t33/net/*.a $(ROOT_DIR)/libs/net
	$(Q)cp -f ./lib/t33/radio/*.a $(ROOT_DIR)/libs/radio
	$(Q)if [ -e $(ROOT_DIR)/src/lteremapp/libs/arm-none-linux-gnueabi/libssi.a ];then cp -f $(ROOT_DIR)/src/lteremapp/libs/arm-none-linux-gnueabi/* $(ROOT_DIR)/libs/;fi
else
	$(Q)rm -rf ./rsys_withoutoam
	$(Q)mkdir -p rsys_withoutoam  rsys_withoutoam/config rsys_withoutoam/bin rsys_withoutoam/scripts 
	$(Q)mkdir -p $(ROOT_DIR)/bin/unstripped
	$(Q)cp -f ./obj/t33/net/enodeb_net ./rsys_withoutoam/bin
	$(Q)cp -f ./obj/t33/radio/enodeb_radio ./rsys_withoutoam/bin
ifeq  ($(MODE),TDD)
	$(Q)cp -f ../config/wr_cfg_tdd.txt ./rsys_withoutoam/config/wr_cfg.txt
else
	$(Q)cp -f ../config/wr_cfg_fdd.txt ./rsys_withoutoam/config/wr_cfg.txt
endif
	$(Q)arm-none-linux-gnueabi-strip -S ./rsys_withoutoam/bin/*
	$(Q)cp -f ../config/ssi_mem_net ./rsys_withoutoam/config
	$(Q)cp -f ../config/ssi_mem_radio ./rsys_withoutoam/config
	$(Q)cp -f ../scripts/l3_t33h.sh ./rsys_withoutoam/scripts/start_eNB.sh
	$(Q)make copy_Intel_L1Bins
	$(Q)cp -f ../scripts/l1_t33h.sh $(ROOT_DIR)/l1
	$(Q)cp -f ../scripts/l2_t33h.sh ./rsys_withoutoam/bin
	$(Q)cp -rf ./rsys_withoutoam $(ROOT_DIR)/bin/unstripped
ifneq ($(TEXT_LOG), YES)
	$(Q)cp -f ./obj/t33/net/rlogapp rsys_withoutoam/bin/
	$(Q)cat $(LOG_ROOT)/t33/net/*.db > $(LOG_ROOT)/t33/net/rlog.logdb
	$(Q)cat $(LOG_ROOT)/t33/radio/*.db > $(LOG_ROOT)/t33/radio/rlog.logdb
	$(Q)cp -f $(LOG_ROOT)/t33/net/rlog.logdb rsys_withoutoam/bin/rlog_net.logdb
	$(Q)cp -f $(LOG_ROOT)/t33/radio/rlog.logdb rsys_withoutoam/bin/rlog_radio.logdb
	$(Q)echo -e "Completed generation of log database"
endif
	$(Q)cp -rf ./rsys_withoutoam $(ROOT_DIR)/bin/
	$(Q)mkdir -p $(ROOT_DIR)/libs  $(ROOT_DIR)/libs/net $(ROOT_DIR)/libs/radio
	#cp -rf ../src/ltephy/mindSpeed/lowercore/transcede_libs/bin/libshm.so ../bin/rsys_withoutoam/ 
	$(Q)cp -f ./lib/t33/net/*.a $(ROOT_DIR)/libs/net
	$(Q)cp -f ./lib/t33/radio/*.a $(ROOT_DIR)/libs/radio
endif
else
ifeq ($(TIP),YES)
	$(Q)rm -rf ./rsys_withoutoam
	$(Q)mkdir -p rsys_withoutoam  rsys_withoutoam/config rsys_withoutoam/bin rsys_withoutoam/scripts 
	$(Q)mkdir -p $(ROOT_DIR)/bin/unstripped
ifneq ($(TEXT_LOG), YES)
	$(Q)cp -f ./obj/tip/ll2/rlogapp rsys_withoutoam/bin/
	$(Q)cat $(LOG_ROOT)/tip/ll2/*.db > $(LOG_ROOT)/tip/ll2/rlog.logdb
	$(Q)cp -f $(LOG_ROOT)/tip/ll2/rlog.logdb rsys_withoutoam/bin/
	$(Q)cp -f ./obj/tip/ul2/rlogapp rsys_withoutoam/bin/
	$(Q)cat $(LOG_ROOT)/tip/ul2/*.db > $(LOG_ROOT)/tip/ul2/rlog.logdb
	$(Q)cp -f $(LOG_ROOT)/tip/ul2/rlog.logdb rsys_withoutoam/bin/
	$(Q)echo -e "Completed generation of log database"
endif
	$(Q)cp -f ./obj/tip/ul2/enodeb_ul2 $(ROOT_DIR)/bin/unstripped/enodeb_ul2withoutoam
	$(Q)cp -f ./obj/tip/ul2/enodeb_ul2 ./rsys_withoutoam/bin
	$(Q)cp -f ./obj/tip/ll2/enodeb_ll2 $(ROOT_DIR)/bin/unstripped/enodeb_ll2withoutoam
	$(Q)cp -f ./obj/tip/ll2/enodeb_ll2 ./rsys_withoutoam/bin
	$(Q)arm-none-linux-gnueabi-strip -S ./rsys_withoutoam/bin/enodeb_ll2
	$(Q)arm-none-linux-gnueabi-strip -S ./rsys_withoutoam/bin/enodeb_ul2
ifeq  ($(MODE),TDD)
	$(Q)cp -f ../config/wr_cfg_tdd.txt ./rsys_withoutoam/bin/wr_cfg.txt
else
	$(Q)cp -f ../config/wr_cfg_fdd.txt ./rsys_withoutoam/bin/wr_cfg.txt
endif
	$(Q)cp -f ../config/ssi_mem ./rsys_withoutoam/config
	$(Q)cp -f ../scripts/start_eNB_without_OAM_t2k.sh ./rsys_withoutoam/scripts/start_eNB.sh
	$(Q)make copy_Intel_L1Bins
	$(Q)cp -rf ./rsys_withoutoam $(ROOT_DIR)/bin/
	$(Q)mkdir -p $(ROOT_DIR)/libs/
	#cp -rf ../src/ltephy/mindSpeed/lowercore/transcede_libs/bin/libshm.so ../bin/rsys_withoutoam/ 
	$(Q)cp -f ./lib/tip/ll2/*.a $(ROOT_DIR)/libs/
	$(Q)cp -f ./lib/tip/ul2/*.a $(ROOT_DIR)/libs/
else
ifeq ($(OAM_ENABLE),YES)
	@echo -e "Copying eNodeB Build, REM and Watchdog"
	$(Q)rm -rf ./rsys
	$(Q)echo . | . ../brcm/TeNBCP_build mspd
ifeq  ($(MODE),TDD)
ifeq  ($(CA_ENABLE),YES)
	$(Q)cp -f ./rsys/config/configFile_TDD_intel ./rsys/config/configFile
else
	$(Q)cp -f ./rsys/config/configFile_TDD_intel_nonca ./rsys/config/configFile
endif
else
ifeq  ($(CA_ENABLE),YES)
	$(Q)cp -f ./rsys/config/configFile_FDD_intel ./rsys/config/configFile
else
	$(Q)cp -f ./rsys/config/configFile_FDD_intel_nonca ./rsys/config/configFile
endif
endif
	$(Q)mkdir -p $(ROOT_DIR)/bin/unstripped
	$(Q)cp -f ./obj/t22/enodeb ./rsys/bin
	$(Q)$(MAKE) copy_Intel_L1Bins
	$(Q)cp -f ../config/ssi_mem ./rsys/config/
	$(Q)cp -f ../scripts/start_eNB_t2k.sh ./rsys/scripts/start_eNB.sh
	$(Q)cp -rf ./rsys $(ROOT_DIR)/bin/unstripped/.
	$(Q)arm-none-linux-gnueabi-strip -S ./rsys/bin/*
ifneq ($(TEXT_LOG), YES)
	$(Q)cp -f ./obj/t22/rlogapp rsys/bin/
	$(Q)cat $(LOG_ROOT)/t22/*.db > $(LOG_ROOT)/t22/rlog.logdb
	$(Q)cp -f $(LOG_ROOT)/t22/rlog.logdb rsys/bin/
	$(Q)echo -e "Completed generation of log database"
endif
	$(Q)cp -rf ./rsys $(ROOT_DIR)/bin
	$(Q)mkdir -p $(ROOT_DIR)/libs/
	$(Q)cp -f ./lib/t22/*.a $(ROOT_DIR)/libs
	$(Q)if [ -e $(ROOT_DIR)/src/lteremapp/libs/arm-none-linux-gnueabi/libssi.a ];then cp -f $(ROOT_DIR)/src/lteremapp/libs/arm-none-linux-gnueabi/* $(ROOT_DIR)/libs/;fi
else
	$(Q)rm -rf ./rsys_withoutoam
	$(Q)mkdir -p rsys_withoutoam  rsys_withoutoam/config rsys_withoutoam/bin rsys_withoutoam/scripts 
	$(Q)mkdir -p $(ROOT_DIR)/bin/unstripped
ifneq ($(TEXT_LOG), YES)
	$(Q)cp -f ./obj/t22/rlogapp rsys_withoutoam/bin/
	$(Q)cat $(LOG_ROOT)/t22/*.db > $(LOG_ROOT)/t22/rlog.logdb
	$(Q)cp -f $(LOG_ROOT)/t22/rlog.logdb rsys_withoutoam/bin/
	$(Q)echo -e "Completed generation of log database"
endif
	$(Q)cp -f ./obj/t22/enodeb $(ROOT_DIR)/bin/unstripped/enodeb_withoutoam
	$(Q)cp -f ./obj/t22/enodeb ./rsys_withoutoam/bin
	$(Q)arm-none-linux-gnueabi-strip -S ./rsys_withoutoam/bin/enodeb
ifeq  ($(MODE),TDD)
	$(Q)cp -f ../config/wr_cfg_tdd.txt ./rsys_withoutoam/bin/wr_cfg.txt
else
	$(Q)cp -f ../config/wr_cfg_fdd.txt ./rsys_withoutoam/bin/wr_cfg.txt
endif
	$(Q)cp -f ../config/ssi_mem ./rsys_withoutoam/config
	$(Q)cp -f ../scripts/start_eNB_without_OAM_t2k.sh ./rsys_withoutoam/scripts/start_eNB.sh
	$(Q)make copy_Intel_L1Bins
	$(Q)cp -rf ./rsys_withoutoam $(ROOT_DIR)/bin/
	$(Q)mkdir -p $(ROOT_DIR)/libs/
	#cp -rf ../src/ltephy/mindSpeed/lowercore/transcede_libs/bin/libshm.so ../bin/rsys_withoutoam/ 
	$(Q)cp -f ./lib/t22/*.a $(ROOT_DIR)/libs/
endif
endif
endif
###################################################################################################
#													END OF MAKEFILE
###################################################################################################
