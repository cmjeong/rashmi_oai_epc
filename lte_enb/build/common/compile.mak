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
#       File:  stack.mak
#
#
#       Prg:   an
#
#********************************************************************21*/
#=======================================================================

STOPTS=-DENB 

Q=
S=
# Check for verbose build
ifneq ($(V),1)
    Q:=@
    S:=-s
endif
export Q
export S

#-DSSINT2 -DSS_TICKS_SEC=100 
# MTSS defines
SS_FLAGS=-DSS -DSS_MT -DSUNOS -DSS_LINUX -UCONRD -UNOFILESYS -USS_DEBG_MEM_CORRUP_LEVEL1 \
    -DSS_TICKS_SEC=100 -USSI_DEBUG_LEVEL1 -USS_LICENSE_CHECK -DANSI -D_GNU_SOURCE\
    -D_REENTRANT -D__EXTENSIONS__ -DDEBUGNOEXIT 

# Flags to be used if binary logging is enabled
BIN_LOGGING = -URLOG_ENABLE_TEXT_LOGGING -DRLOG_DEBUG_MODE -DRLOG_USE_CIRCULAR_BUFFER \
    -DRLOG_USE_TTI_LOGGING

# Flags to be used if text logging is enabled
TEXT_LOGGING = -DRLOG_ENABLE_TEXT_LOGGING -DRLOG_DEBUG_MODE

ifeq ($(INSTRUMENTATION), YES)
INSTRUMENTATION_FLAGS = -DSS_MEM_CORRUPTION_DETECTION 
endif

# Flags pertaining to the functionality of TeNB are included here
TENB_FLAGS=-DLTERRC_REL9 -DEGTP_U_REL_9 -UMAC_SCH_STATS -USCH_STATS \
    -DTENB_TTI_PERF -DAES -UIPV6_SUPPORTED -DLTE_RRC_DISSECTOR -DRSYS_WIRESHARK

ifeq ($(TIP_L3), YES)
TENB_FLAGS+=-DTIP_L3 -DTIP_L2_L3_SPLIT -DTIP_L3_UL2_LL2_SPLIT -DTIP_RRCMAC_CONFIG -USSI_STATIC_MEM_LEAK_DETECTION -DTIP_OAM
endif
ifeq ($(TIP_UPPER_L2), YES)
TENB_FLAGS+=-DTIP_UPPER_L2 -DTIP_L2_L3_SPLIT -DTIP_L3_UL2_LL2_SPLIT -USSI_STATIC_MEM_LEAK_DETECTION -DTIP_OAM
endif
ifeq ($(TIP_LOWER_L2), YES)
TENB_FLAGS+=-DTIP_LOWER_L2  -DTIP_L2_L3_SPLIT -DTIP_L3_UL2_LL2_SPLIT -USSI_STATIC_MEM_LEAK_DETECTION -DTIP_OAM
endif

# Flags that define the broad level functioning of the binary
ENV_FLAGS=-DNO_ERRCLS -DNOERRCHK -DDEBUGP 

# Flags to be reviewed. Some of these should be easy to remove from the source code
# LTE_TENB_PERF - This flag should not be needed. Let us just remove if 
#               - from the code
# LTEMAC_MIMO - Should just be deleted from application and preferably from MAC as well
#               Move this flag to application and MAC product makefile
# WR_UL_PWR   - Does not seem to be used. Can this be deleted
# WR_DL_CQI   - Remove the usage of this flag from umm file and makefile
# TENB_FP     - Should this move to just application?
#     -UTENB_SPLIT_ARCH_SUPPORT -UPHY_SHUTDOWN_ENABLE -UE_TM -UACC_LOG_CL \
     -UUE_RAD_CAP -ULTE_START_UL_DL_DELTA -UMAC_RLC_UL_RBUF -UPDCP_RLC_DL_RBUF -USS_DIAG \
     -USLES9_PLUS -UTENB_SPLIT_ARCH 
RVW_FLAGS=-DCM_PASN_DBG -DLTEMAC_MIMO -DWR_UL_PWR \
     -DREVIEW -DNL -DTENB_MAX_UE_SUPPORTED= 512 

# Flags that can be removed when everything works. These flags are not included
# in the compilation at the moment.
DEL_FLAGS=-DSS_WL_REGION=1 -DVE_PERF_MEAS -UVE_SUPPORT_RLC_UM_MODE -ULTE_LNX_AFFINITY \
     -DKW_BG_DL_PROC -DKW_BG_UL_PROC -DWR_SB_SCTP -DPHY_ERROR_LOGGING -UWR_DETECT_RLF \
     -USS_MEM_CORRUPTION_DETECTION -DL2_LOGGING_ENABLED -DLTEMAC_DRX -UUSE_PURE \
     -DLTE_MULTIUE -DCMKV2 -DYS_ENB_CFG -DTA_NEW -DTENB_DISABLE_DL_ZBC 

ALL_FLAGS=$(SS_FLAGS) $(CMN_FLAGS) $(ENV_FLAGS) $(RVW_FLAGS) $(TENB_FLAGS) $(LNXENV)

# compiler options:
C_OPTS+=-g -O3 -mtune=native  -pipe -pedantic -Wall -Wno-comment -Wshadow -Wno-unused-function \
    -Wcast-qual -fno-strict-aliasing -fsigned-char --std=c99
#C_OPTS+=-g -pipe -pedantic -Wall -Werror -Wno-comment -Wshadow \
    -Wcast-qual -fno-strict-aliasing -fsigned-char --std=c99

COPTS_WO_PEDANTIC=$(subst -pedantic,,$(COPTS))

xCPP_OPTS+=-g -O3 -mtune=native -pipe -pedantic -Wall -Wno-comment -Wshadow \
    -Wcast-qual -fno-strict-aliasing -fsigned-char -lstdc++ 
#xCPP_OPTS+=-g -pipe -pedantic -Wall  -Werror -Wno-comment -Wshadow \
    -Wcast-qual -fno-strict-aliasing -fsigned-char -lstdc++ 

# Include path settings
I_OPTS+=-I$(ROOT_DIR)/src/sec -I$(SRC_DIR) -I$(ROOT_DIR)/src/cm -I$(ROOT_DIR)/src/mt -I$(ROOT_DIR)/src/rlog -I$(ROOT_DIR)/src/tip
I_OPTS+=$(PLTFRM_INCLUDES)
.SUFFIXES:.c .o

ifneq ($(TEXT_LOG), YES)
$(C_OBJS):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR_FILES)
	@echo -e "Preprocessing $(COLOR_BLUE) $< $(REVERT_COLOR)"
	$(Q)$(CC) -E -o $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$<) $(C_OPTS) $(I_OPTS)\
    $(BIN_LOGGING) $(ALL_FLAGS) $(MOD_FLAGS) $(PLTFRM_FLAGS) $<
	$(Q)perl $(COM_BUILD_DIR)/rlog.pl $(PLTFRM) $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$<)
	@echo -e "Compiling $(COLOR_RED) $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$<) $(REVERT_COLOR)"
	$(Q)$(CC) $(C_OPTS) -c -o $@ $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$<)
$(C_WO_PED_OBJS):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR_FILES)
	@echo -e "Preprocessing $(COLOR_BLUE) $< $(REVERT_COLOR)"
	$(Q)$(CC) -E -o $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$<) $(COPTS_WO_PEDANTIC) $(I_OPTS)\
    $(BIN_LOGGING) $(ALL_FLAGS) $(MOD_FLAGS) $(PLTFRM_FLAGS) $<
	$(Q)perl $(COM_BUILD_DIR)/rlog.pl $(PLTFRM) $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$<)
	@echo -e "Compiling $(COLOR_RED) $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$<) $(REVERT_COLOR)"
	$(Q)$(CC) $(COPTS_WO_PEDANTIC) -c -o $@ $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$<)
$(CPP_OBJS):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDR_FILES)
	@echo -e "Preprocessing $(COLOR_BLUE) $< $(REVERT_COLOR)"
	$(Q)$(CC) -E -o $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.i,$<) $(CPP_OPTS) $(I_OPTS)\
    $(BIN_LOGGING) $(ALL_FLAGS) $(MOD_FLAGS) $(PLTFRM_FLAGS) $<
	$(Q)perl $(COM_BUILD_DIR)/rlog.pl $(PLTFRM) $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.i,$<)
	@echo -e "Compiling $(COLOR_RED) $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.i,$<) $(REVERT_COLOR)"
	$(Q)$(CC) -c -o $(CPP_OPTS) $@ $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.i,$<)

$(C_OBJS_WO_LOG):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR_FILES)
	@echo -e "Compiling $(COLOR_RED) $< $(REVERT_COLOR)"
	$(Q)$(CC) -c -o $@ $(C_OPTS) $(I_OPTS) $(ALL_FLAGS) $(BIN_LOGGING) $(MOD_FLAGS) \
    $(PLTFRM_FLAGS) $<

$(C_WO_PED_OBJS_WO_LOG):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR_FILES)
	@echo -e "Compiling $(COLOR_RED) $< $(REVERT_COLOR)"
	$(Q)$(CC) -c -o $@ $(COPTS_WO_PEDANTIC) $(I_OPTS) $(ALL_FLAGS) $(BIN_LOGGING) $(MOD_FLAGS) \
    $(PLTFRM_FLAGS) $<

$(CPP_OBJS_WO_LOG):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDR_FILES)
	@echo -e "Compiling $(COLOR_RED) $< $(REVERT_COLOR)"
	$(Q)$(CC) -c -o $@ $(CPP_OPTS) $(I_OPTS) $(ALL_FLAGS) $(BIN_LOGGING) $(MOD_FLAGS) \
    $(PLTFRM_FLAGS) $<
else
$(C_OBJS):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR_FILES)
	@echo -e "Compiling $(COLOR_RED) $< $(REVERT_COLOR)"
	$(Q)$(CC) -c -o $@ $(C_OPTS) $(I_OPTS) $(ALL_FLAGS) $(TEXT_LOGGING) $(MOD_FLAGS) \
    $(PLTFRM_FLAGS) $<
$(C_WO_PED_OBJS):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR_FILES)
	@echo -e "Compiling $(COLOR_RED) $< $(REVERT_COLOR)"
	$(Q)$(CC) -c -o $@ $(COPTS_WO_PEDANTIC) $(I_OPTS) $(ALL_FLAGS) $(TEXT_LOGGING) $(MOD_FLAGS) \
    $(PLTFRM_FLAGS) $<
$(CPP_OBJS):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDR_FILES)
	@echo -e "Compiling $(COLOR_RED) $< $(REVERT_COLOR)"
	$(Q)$(CC) -c -o $@ $(CPP_OPTS) $(I_OPTS) $(ALL_FLAGS) $(TEXT_LOGGING) $(MOD_FLAGS) \
    $(PLTFRM_FLAGS) $<

$(C_OBJS_WO_LOG):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR_FILES)
	@echo -e "Compiling $(COLOR_RED) $< $(REVERT_COLOR)"
	$(Q)$(CC) -c -o $@ $(C_OPTS) $(I_OPTS) $(ALL_FLAGS) $(TEXT_LOGGING) $(MOD_FLAGS) \
    $(PLTFRM_FLAGS) $<

$(C_WO_PED_OBJS_WO_LOG):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR_FILES)
	@echo -e "Compiling $(COLOR_RED) $< $(REVERT_COLOR)"
	$(Q)$(CC) -c -o $@ $(COPTS_WO_PEDANTIC) $(I_OPTS) $(ALL_FLAGS) $(TEXT_LOGGING) $(MOD_FLAGS) \
    $(PLTFRM_FLAGS) $<

$(CPP_OBJS_WO_LOG):$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDR_FILES)
	@echo -e "Compiling $(COLOR_RED) $< $(REVERT_COLOR)"
	$(Q)$(CC) -c -o $@ $(CPP_OPTS) $(I_OPTS) $(ALL_FLAGS) $(TEXT_LOGGING) $(MOD_FLAGS) \
    $(PLTFRM_FLAGS) $<
endif

