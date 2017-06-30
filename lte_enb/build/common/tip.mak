#-------------------------------------------------------------#
#Makefile for product cm - script generated.
#Only the $(CCcmFLAGS) may be modified.
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak
COLOR=$(COLOR_GREEN)

SRC_DIR=$(ROOT_DIR)/src/tip

CM_DIR=$(ROOT_DIR)/src/cm
WR_DIR=$(ROOT_DIR)/src/enbapp
MT_DIR=$(ROOT_DIR)/src/mt

# TODO - The dependency between layers and CM files should be removed #
I_OPTS+= -I$(CM_DIR) -I$(WR_DIR) -I$(MT_DIR)

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#
#CCrmFLAGS=-DLRM_LWLC -DRMU_LWLC -URMU_NPLC -DRGM_LWLC -DLWLCSMRMMILRM -DLCSMRMMILRM -DSM -DRM_INTF
#CCnlFlags=-DLWLCSMSONILNL -DNLU_LWLC -DLCSMSONILNL -DNLU_TC -DTCSMSONILNL -DNL
#CCcmFLAGS=-DSS_MT_TMR -DSS_FLOAT  -DRGR_V1 -DLSZV1 -DVE_SB_SCTP $(CCrmFLAGS)
#CCsmFLAGS=-DHI -DSB -DEG -DWR -DKW -DKW_PDCP -DPJ -DSZ -DYS -DRG -DNH -UVE_SM_LOG_TO_FILE -DRGR_SI_SCH -DTA_NEW -DSI_NEW -DCZ $(CCrmFLAGS) $(CCnlFlags)

#-------------------------------------------------------------#
# Define all the layers that are part of this binary so that  #
# their coupling requirements get defined from envopt.h.      #
#-------------------------------------------------------------#
# TODO -DRM has conflict with some cm_atm files. It is temp-  #
# orarily removed from this list.                             #
MOD_FLAGS=-DNH -DWR -DNX -DSZ -DCZ -DSB -DHI -DEG -DSM -DNL -DSM -DRG -DKW -DPJ -DYS 
#This module does not support binary logging so disable it
TEXT_LOG=YES

#-------------------------------------------------------------#
# Source file list. This needs to be explicitly built as CM
# directory contains files for both CPUL and CPUH.
#-------------------------------------------------------------#
C_SRCS=$(wildcard $(SRC_DIR)/*.c)

C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
LOG_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$(C_SRCS))
DB_FILES =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i.db,$(C_SRCS))

#C_OBJS_WO_LOG=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
HDR_FILES+= $(wildcard $(SRC_DIR)/*.[hx])



lib: $(LIB_DIR)/libtip.a

include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(LIB_DIR)/libtip.a:$(C_OBJS)
	@echo -e "Creating Archive $(C_OBJS) $(COLOR) $@ $(REVERT_COLOR) "
	$(Q)ar -cr $(LIB_DIR)/libtip.a $(C_OBJS)	
#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning CPUH TIP$(REVERT_COLOR)"
	@echo -e "$(COLOR_RED) $(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/libtip.a $(C_OBJS_WO_LOG)
