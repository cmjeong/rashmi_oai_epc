#
#
##-------------------------------------------------------------#
#Makefile for product RG - script generated.
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak
COLOR=$(COLOR_GREEN)

SRC_DIR=$(ROOT_DIR)/src/ltemac

# prepare the list of common header files
HDR_FILES+=$(wildcard $(CM_DIR)/env*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/gen*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/ssi*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/cm*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/crg.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lrg*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/rgr.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/rgm.[hx])

# Add the product specific header files
HDR_FILES+= $(wildcard $(SRC_DIR)/*.[hx])

#prepare the list of source files
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_SRCS:=$(filter-out %rg_tmr.c, $(C_SRCS))
C_SRCS:=$(filter-out %rg_ex_pt.c, $(C_SRCS))
C_SRCS:=$(filter-out %rg_tst.c, $(C_SRCS))

#prepare the list of object files and RLOG related files
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
LOG_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$(C_SRCS))
DB_FILES =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i.db,$(C_SRCS))

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#
# Including RG_PHASE2_SCHED for supporting more than one schedulers 
# supported by mac
# TODO: make it define for LTEMAC_MIMO and remove it from envopt.h
MOD_FLAGS=-DRGM_LC -DRGM_LWLC -USM -DTF -URG_DEBUG -DxRG_PHASE2_SCHED -DxRGR_V1 \
    -DRG_UL_DELTA=2 -ULTEMAC_DLUE_TMGOPTMZ -UTENB_SPLIT_ARCH -DRG -ULTEMAC_MIMO

# Product sources-------------------------------------------------------
#rgSRCS= \
#    $(IN_DIR)/rg_cfg.$(SRC) \
#    $(IN_DIR)/rg_com.$(SRC) \
#    $(IN_DIR)/rg_dbm.$(SRC) \
#    $(IN_DIR)/rg_dhm.$(SRC) \
#    $(IN_DIR)/rg_dux.$(SRC) \
#    $(IN_DIR)/rg_ex_ms.$(SRC) \
#    $(IN_DIR)/rg_id.$(SRC) \
#    $(IN_DIR)/rg_lim.$(SRC) \
#    $(IN_DIR)/rg_lmm.$(SRC) \
#    $(IN_DIR)/rg_mux.$(SRC) \
#    $(IN_DIR)/rg_ptli.$(SRC) \
#    $(IN_DIR)/rg_ptmi.$(SRC) \
#    $(IN_DIR)/rg_ptui.$(SRC) \
#    $(IN_DIR)/rg_ram.$(SRC) \
#    $(IN_DIR)/rg_rom.$(SRC) \
#    $(IN_DIR)/rg_l2m.$(SRC) \
#    $(IN_DIR)/rg_sch.$(SRC) \
#    $(IN_DIR)/rg_sch_l2m.$(SRC) \
#    $(IN_DIR)/rg_tom.$(SRC) \
#    $(IN_DIR)/rg_uhm.$(SRC) \
#    $(IN_DIR)/rg_uim.$(SRC) \
#    $(IN_DIR)/rg_utl.$(SRC) \
#    $(IN_DIR)/rg_sch_cfg.$(SRC) \
#    $(IN_DIR)/rg_sch_cmn.$(SRC) \
#    $(IN_DIR)/rg_sch_dbm.$(SRC) \
#    $(IN_DIR)/rg_sch_gom.$(SRC) \
#    $(IN_DIR)/rg_sch_sc1.$(SRC) \
#    $(IN_DIR)/rg_sch_dhm.$(SRC) \
#    $(IN_DIR)/rg_sch_dlfs.$(SRC) \
#    $(IN_DIR)/rg_sch_ex_ms.$(SRC) \
#    $(IN_DIR)/rg_sch_inf.$(SRC) \
#    $(IN_DIR)/rg_sch_lmm.$(SRC) \
#    $(IN_DIR)/rg_sch_maxci.$(SRC) \
#    $(IN_DIR)/rg_sch_mga.$(SRC) \
#    $(IN_DIR)/rg_sch_pfs.$(SRC) \
#    $(IN_DIR)/rg_sch_pt.$(SRC) \
#    $(IN_DIR)/rg_sch_pwr.$(SRC) \
#    $(IN_DIR)/rg_sch_ram.$(SRC) \
#    $(IN_DIR)/rg_sch_rr.$(SRC) \
#    $(IN_DIR)/rg_sch_tmr.$(SRC) \
#    $(IN_DIR)/rg_sch_uhm.$(SRC) \
#    $(IN_DIR)/rg_sch_utl.$(SRC) \
#    $(IN_DIR)/rg_sch_tom.$(SRC) \
#    $(IN_DIR)/rg_sch_utl_clist.$(SRC)\
#    $(IN_DIR)/rg_sch_drx.$(SRC)\
#    $(IN_DIR)/rg_sch_sps.$(SRC)
#
#
#
# Product objects-------------------------------------------------------
#rgOBJS= \
#    $(OUT_DIR)/rg_cfg.$(OBJ) \
#    $(OUT_DIR)/rg_com.$(OBJ) \
#    $(OUT_DIR)/rg_dbm.$(OBJ) \
#    $(OUT_DIR)/rg_dhm.$(OBJ) \
#    $(OUT_DIR)/rg_dux.$(OBJ) \
#    $(OUT_DIR)/rg_ex_ms.$(OBJ) \
#    $(OUT_DIR)/rg_id.$(OBJ) \
#    $(OUT_DIR)/rg_lim.$(OBJ) \
#    $(OUT_DIR)/rg_lmm.$(OBJ) \
#    $(OUT_DIR)/rg_mux.$(OBJ) \
#    $(OUT_DIR)/rg_ptli.$(OBJ) \
#    $(OUT_DIR)/rg_ptmi.$(OBJ) \
#    $(OUT_DIR)/rg_ptui.$(OBJ) \
#    $(OUT_DIR)/rg_ram.$(OBJ) \
#    $(OUT_DIR)/rg_rom.$(OBJ) \
#    $(OUT_DIR)/rg_l2m.$(OBJ) \
#    $(OUT_DIR)/rg_sch.$(OBJ) \
#    $(OUT_DIR)/rg_sch_l2m.$(OBJ) \
#    $(OUT_DIR)/rg_tom.$(OBJ) \
#    $(OUT_DIR)/rg_uhm.$(OBJ) \
#    $(OUT_DIR)/rg_uim.$(OBJ) \
#    $(OUT_DIR)/rg_utl.$(OBJ)  \
#    $(OUT_DIR)/rg_sch_cfg.$(OBJ) \
#    $(OUT_DIR)/rg_sch_cmn.$(OBJ) \
#    $(OUT_DIR)/rg_sch_dbm.$(OBJ) \
#    $(OUT_DIR)/rg_sch_gom.$(OBJ)\
#    $(OUT_DIR)/rg_sch_sc1.$(OBJ)\
#    $(OUT_DIR)/rg_sch_dhm.$(OBJ)\
#    $(OUT_DIR)/rg_sch_dlfs.$(OBJ) \
#    $(OUT_DIR)/rg_sch_ex_ms.$(OBJ) \
#    $(OUT_DIR)/rg_sch_inf.$(OBJ) \
#    $(OUT_DIR)/rg_sch_lmm.$(OBJ) \
#    $(OUT_DIR)/rg_sch_maxci.$(OBJ) \
#    $(OUT_DIR)/rg_sch_mga.$(OBJ) \
#    $(OUT_DIR)/rg_sch_pfs.$(OBJ) \
#    $(OUT_DIR)/rg_sch_pt.$(OBJ) \
#    $(OUT_DIR)/rg_sch_pwr.$(OBJ) \
#    $(OUT_DIR)/rg_sch_ram.$(OBJ) \
#    $(OUT_DIR)/rg_sch_rr.$(OBJ) \
#    $(OUT_DIR)/rg_sch_tmr.$(OBJ) \
#    $(OUT_DIR)/rg_sch_uhm.$(OBJ) \
#    $(OUT_DIR)/rg_sch_utl.$(OBJ) \
#    $(OUT_DIR)/rg_sch_tom.$(OBJ) \
#    $(OUT_DIR)/rg_sch_utl_clist.$(OBJ) \
#    $(OUT_DIR)/rg_sch_drx.$(OBJ)  \
#    $(OUT_DIR)/rg_sch_sps.$(OBJ)
#
#
#
#
#RGCM_INC=$(VS_DIR)/rg.h $(VS_DIR)/rg.x $(VS_DIR)/rg_err.h $(VS_DIR)/rg_env.h
#
#ALL_INC=$(RGCM_INC) $(CM_INC)
#   
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

#$(OUT_DIR)/rg_cfg.$(OBJ): $(IN_DIR)/rg_cfg.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  -o$(OUT_DIR)/rg_cfg.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) \
#	$(IN_DIR)/rg_cfg.$(SRC)
#$(OUT_DIR)/rg_com.$(OBJ): $(IN_DIR)/rg_com.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_com.$(SRC) -o \
#	$(OUT_DIR)/rg_com.$(OBJ)
#$(OUT_DIR)/rg_dbm.$(OBJ): $(IN_DIR)/rg_dbm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_dbm.$(SRC) -o \
#	$(OUT_DIR)/rg_dbm.$(OBJ)
#$(OUT_DIR)/rg_dhm.$(OBJ): $(IN_DIR)/rg_dhm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_dhm.$(SRC) -o \
#	$(OUT_DIR)/rg_dhm.$(OBJ)
#$(OUT_DIR)/rg_dux.$(OBJ): $(IN_DIR)/rg_dux.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_dux.$(SRC) -o \
#	$(OUT_DIR)/rg_dux.$(OBJ)
#$(OUT_DIR)/rg_ex_ms.$(OBJ): $(IN_DIR)/rg_ex_ms.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_ex_ms.$(SRC) -o \
#	$(OUT_DIR)/rg_ex_ms.$(OBJ)
#$(OUT_DIR)/rg_id.$(OBJ): $(IN_DIR)/rg_id.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_id.$(SRC) -o \
#	$(OUT_DIR)/rg_id.$(OBJ)
#$(OUT_DIR)/rg_lim.$(OBJ): $(IN_DIR)/rg_lim.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_lim.$(SRC) -o \
#	$(OUT_DIR)/rg_lim.$(OBJ)
#$(OUT_DIR)/rg_lmm.$(OBJ): $(IN_DIR)/rg_lmm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_lmm.$(SRC) -o \
#	$(OUT_DIR)/rg_lmm.$(OBJ)
#$(OUT_DIR)/rg_mux.$(OBJ): $(IN_DIR)/rg_mux.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_mux.$(SRC) -o \
#	$(OUT_DIR)/rg_mux.$(OBJ)
#$(OUT_DIR)/rg_ptli.$(OBJ): $(IN_DIR)/rg_ptli.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_ptli.$(SRC) -o \
#	$(OUT_DIR)/rg_ptli.$(OBJ)
#$(OUT_DIR)/rg_ptmi.$(OBJ): $(IN_DIR)/rg_ptmi.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_ptmi.$(SRC) -o \
#	$(OUT_DIR)/rg_ptmi.$(OBJ)
#$(OUT_DIR)/rg_ptui.$(OBJ): $(IN_DIR)/rg_ptui.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_ptui.$(SRC) -o \
#	$(OUT_DIR)/rg_ptui.$(OBJ)
#$(OUT_DIR)/rg_ram.$(OBJ): $(IN_DIR)/rg_ram.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_ram.$(SRC) -o \
#	$(OUT_DIR)/rg_ram.$(OBJ)
#$(OUT_DIR)/rg_rom.$(OBJ): $(IN_DIR)/rg_rom.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_rom.$(SRC) -o \
#	$(OUT_DIR)/rg_rom.$(OBJ)
#$(OUT_DIR)/rg_l2m.$(OBJ): $(IN_DIR)/rg_l2m.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_l2m.$(SRC) -o \
#	$(OUT_DIR)/rg_l2m.$(OBJ)
#$(OUT_DIR)/rg_sch.$(OBJ): $(IN_DIR)/rg_sch.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch.$(SRC) -o \
#	$(OUT_DIR)/rg_sch.$(OBJ)
#$(OUT_DIR)/rg_sch_l2m.$(OBJ): $(IN_DIR)/rg_sch_l2m.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_l2m.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_l2m.$(OBJ)
#$(OUT_DIR)/rg_tom.$(OBJ): $(IN_DIR)/rg_tom.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_tom.$(SRC) -o \
#	$(OUT_DIR)/rg_tom.$(OBJ)
#$(OUT_DIR)/rg_uhm.$(OBJ): $(IN_DIR)/rg_uhm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_uhm.$(SRC) -o \
#	$(OUT_DIR)/rg_uhm.$(OBJ)
#$(OUT_DIR)/rg_uim.$(OBJ): $(IN_DIR)/rg_uim.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_uim.$(SRC) -o \
#	$(OUT_DIR)/rg_uim.$(OBJ)
#$(OUT_DIR)/rg_utl.$(OBJ): $(IN_DIR)/rg_utl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_utl.$(SRC) -o \
#	$(OUT_DIR)/rg_utl.$(OBJ)
#
#$(OUT_DIR)/rg_sch_sc1.$(OBJ): $(IN_DIR)/rg_sch_sc1.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_sc1.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_sc1.$(OBJ)
#$(OUT_DIR)/rg_sch_gom.$(OBJ): $(IN_DIR)/rg_sch_gom.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_gom.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_gom.$(OBJ)
#$(OUT_DIR)/rg_sch_inf.$(OBJ): $(IN_DIR)/rg_sch_inf.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_inf.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_inf.$(OBJ)
#$(OUT_DIR)/rg_sch_lmm.$(OBJ): $(IN_DIR)/rg_sch_lmm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_lmm.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_lmm.$(OBJ)
#$(OUT_DIR)/rg_sch_cfg.$(OBJ): $(IN_DIR)/rg_sch_cfg.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_cfg.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_cfg.$(OBJ)
#$(OUT_DIR)/rg_sch_cmn.$(OBJ): $(IN_DIR)/rg_sch_cmn.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_cmn.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_cmn.$(OBJ)
#$(OUT_DIR)/rg_sch_dbm.$(OBJ): $(IN_DIR)/rg_sch_dbm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_dbm.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_dbm.$(OBJ)
#$(OUT_DIR)/rg_sch_dhm.$(OBJ): $(IN_DIR)/rg_sch_dhm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_dhm.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_dhm.$(OBJ)
#$(OUT_DIR)/rg_sch_dlfs.$(OBJ): $(IN_DIR)/rg_sch_dlfs.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_dlfs.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_dlfs.$(OBJ)
#$(OUT_DIR)/rg_sch_ex_ms.$(OBJ): $(IN_DIR)/rg_sch_ex_ms.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_ex_ms.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_ex_ms.$(OBJ)
#
#$(OUT_DIR)/rg_sch_maxci.$(OBJ): $(IN_DIR)/rg_sch_maxci.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_maxci.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_maxci.$(OBJ)
#$(OUT_DIR)/rg_sch_mga.$(OBJ): $(IN_DIR)/rg_sch_mga.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_mga.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_mga.$(OBJ)
#$(OUT_DIR)/rg_sch_pfs.$(OBJ): $(IN_DIR)/rg_sch_pfs.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_pfs.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_pfs.$(OBJ)
#$(OUT_DIR)/rg_sch_pt.$(OBJ): $(IN_DIR)/rg_sch_pt.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_pt.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_pt.$(OBJ)
#$(OUT_DIR)/rg_sch_pwr.$(OBJ): $(IN_DIR)/rg_sch_pwr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_pwr.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_pwr.$(OBJ)
#$(OUT_DIR)/rg_sch_ram.$(OBJ): $(IN_DIR)/rg_sch_ram.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_ram.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_ram.$(OBJ)
#$(OUT_DIR)/rg_sch_rr.$(OBJ): $(IN_DIR)/rg_sch_rr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_rr.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_rr.$(OBJ)
#$(OUT_DIR)/rg_sch_tmr.$(OBJ): $(IN_DIR)/rg_sch_tmr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_tmr.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_tmr.$(OBJ)
#$(OUT_DIR)/rg_sch_tom.$(OBJ): $(IN_DIR)/rg_sch_tom.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_tom.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_tom.$(OBJ)
#$(OUT_DIR)/rg_sch_uhm.$(OBJ): $(IN_DIR)/rg_sch_uhm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_uhm.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_uhm.$(OBJ)
#$(OUT_DIR)/rg_sch_utl.$(OBJ): $(IN_DIR)/rg_sch_utl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_utl.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_utl.$(OBJ)
#$(OUT_DIR)/rg_sch_utl_clist.$(OBJ): $(IN_DIR)/rg_sch_utl_clist.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c  $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_utl_clist.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_utl_clist.$(OBJ)
#$(OUT_DIR)/rg_sch_drx.$(OBJ): $(IN_DIR)/rg_sch_drx.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_drx.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_drx.$(OBJ)
#$(OUT_DIR)/rg_sch_sps.$(OBJ): $(IN_DIR)/rg_sch_sps.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) $(IN_DIR)/rg_sch_sps.$(SRC) -o \
#	$(OUT_DIR)/rg_sch_sps.$(OBJ)
lib:$(LIB_DIR)/librg.a
include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
ifeq ($(BIN_LOG), YES)
$(LIB_DIR)/librg.a:$(C_OBJS)
	@echo -e "Creating log DB $(COLOR)$(LOG_DIR)/rgLog.db $(REVERT_COLOR)"
	$(Q)cat $(DB_FILES) > $(LOG_DIR)/rgLog.db
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/librg.a $(C_OBJS)	
else
$(LIB_DIR)/librg.a:$(C_OBJS)
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/librg.a $(C_OBJS)	
endif

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaing MAC$(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/librg.a $(C_OBJS)

