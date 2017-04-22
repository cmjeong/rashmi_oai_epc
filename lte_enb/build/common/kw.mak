#
##-------------------------------------------------------------#
##Makefile for product ib - script generated.
#Only the $(CCib) may be modified.
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak

SRC_DIR=$(ROOT_DIR)/src/lterlc

#Prepare source file list
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_SRCS:=$(filter-out %kw_tst.c,$(C_SRCS))

#prepare the list of object files and RLOG related files
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
LOG_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$(C_SRCS))
DB_FILES =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i.db,$(C_SRCS))

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#
#TODO: Move LCRGU to envopt.h.
MOD_FLAGS=-DRG -DYS -DKW -DPX -DLCRGU -DLCKWULUDX -DLCUDX -DLWLCKWULUDX #-DLTE_L2_MEAS_RLC -DLTE_L2_MEAS

# Product objects-------------------------------------------------------
#kwOBJS= \
#    $(OUT_DIR)/kw_amm.$(OBJ) \
#    $(OUT_DIR)/kw_cfg.$(OBJ) \
#    $(OUT_DIR)/kw_dbm.$(OBJ) \
#    $(OUT_DIR)/kw_ex_ms.$(OBJ) \
#    $(OUT_DIR)/kw_id.$(OBJ) \
#    $(OUT_DIR)/kw_lim.$(OBJ) \
#    $(OUT_DIR)/kw_lmm.$(OBJ) \
#    $(OUT_DIR)/kw_ptli.$(OBJ) \
#    $(OUT_DIR)/kw_ptmi.$(OBJ) \
#    $(OUT_DIR)/kw_ptui.$(OBJ) \
#    $(OUT_DIR)/kw_tmm.$(OBJ) \
#    $(OUT_DIR)/kw_tmr.$(OBJ) \
#    $(OUT_DIR)/kw_uim.$(OBJ) \
#    $(OUT_DIR)/kw_umm.$(OBJ) \
#    $(OUT_DIR)/kw_pj_lim.$(OBJ) \
#    $(OUT_DIR)/kw_pj_uim.$(OBJ) \
#    $(OUT_DIR)/kw_pj_lmm.$(OBJ) \
#    $(OUT_DIR)/kw_pj_cfg.$(OBJ) \
#    $(OUT_DIR)/kw_pj_dbm.$(OBJ) \
#    $(OUT_DIR)/kw_pj_dlm.$(OBJ) \
#    $(OUT_DIR)/kw_pj_ulm.$(OBJ) \
#    $(OUT_DIR)/kw_pj_utl.$(OBJ) \
#    $(OUT_DIR)/kw_pj_tmr.$(OBJ) \
#    $(OUT_DIR)/kw_pj_lib.$(OBJ) \
#    $(OUT_DIR)/kw_ptlib.$(OBJ) \
#    $(OUT_DIR)/kw_utl.$(OBJ)
#
#
#KWCM_INC=$(VS_DIR)/kw.h   $(VS_DIR)/kw.x $(VS_DIR)/kw_env.h $(VS_DIR)/kw_err.h
#
#ALL_INC=$(KWCM_INC) $(CM_INC)
#   
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#
#
#$(OUT_DIR)/kw_amm.$(OBJ): $(IN_DIR)/kw_amm.$(SRC) $(ALL_INC)
#	$(CC)  -o$(OUT_DIR)/kw_amm.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) \
#	$(IN_DIR)/kw_amm.$(SRC)
#$(OUT_DIR)/kw_cfg.$(OBJ): $(IN_DIR)/kw_cfg.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_cfg.$(SRC) -o \
#	$(OUT_DIR)/kw_cfg.$(OBJ)
#$(OUT_DIR)/kw_dbm.$(OBJ): $(IN_DIR)/kw_dbm.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_dbm.$(SRC) -o \
#	$(OUT_DIR)/kw_dbm.$(OBJ)
#$(OUT_DIR)/kw_ex_ms.$(OBJ): $(IN_DIR)/kw_ex_ms.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_ex_ms.$(SRC) -o \
#	$(OUT_DIR)/kw_ex_ms.$(OBJ)
#$(OUT_DIR)/kw_id.$(OBJ): $(IN_DIR)/kw_id.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_id.$(SRC) -o \
#	$(OUT_DIR)/kw_id.$(OBJ)
#$(OUT_DIR)/kw_lim.$(OBJ): $(IN_DIR)/kw_lim.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_lim.$(SRC) -o \
#	$(OUT_DIR)/kw_lim.$(OBJ)
#$(OUT_DIR)/kw_lmm.$(OBJ): $(IN_DIR)/kw_lmm.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_lmm.$(SRC) -o \
#	$(OUT_DIR)/kw_lmm.$(OBJ)
#$(OUT_DIR)/kw_ptli.$(OBJ): $(IN_DIR)/kw_ptli.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_ptli.$(SRC) -o \
#	$(OUT_DIR)/kw_ptli.$(OBJ)
#$(OUT_DIR)/kw_ptmi.$(OBJ): $(IN_DIR)/kw_ptmi.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_ptmi.$(SRC) -o \
#	$(OUT_DIR)/kw_ptmi.$(OBJ)
#$(OUT_DIR)/kw_ptui.$(OBJ): $(IN_DIR)/kw_ptui.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_ptui.$(SRC) -o \
#	$(OUT_DIR)/kw_ptui.$(OBJ)
#$(OUT_DIR)/kw_tmm.$(OBJ): $(IN_DIR)/kw_tmm.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_tmm.$(SRC) -o \
#	$(OUT_DIR)/kw_tmm.$(OBJ)
#$(OUT_DIR)/kw_tmr.$(OBJ): $(IN_DIR)/kw_tmr.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_tmr.$(SRC) -o \
#	$(OUT_DIR)/kw_tmr.$(OBJ)
#$(OUT_DIR)/kw_uim.$(OBJ): $(IN_DIR)/kw_uim.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_uim.$(SRC) -o \
#	$(OUT_DIR)/kw_uim.$(OBJ)
#$(OUT_DIR)/kw_umm.$(OBJ): $(IN_DIR)/kw_umm.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_umm.$(SRC) -o \
#	$(OUT_DIR)/kw_umm.$(OBJ)
#$(OUT_DIR)/kw_pj_lim.$(OBJ): $(IN_DIR)/kw_pj_lim.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_pj_lim.$(SRC) -o \
#	$(OUT_DIR)/kw_pj_lim.$(OBJ)
#$(OUT_DIR)/kw_pj_uim.$(OBJ): $(IN_DIR)/kw_pj_uim.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_pj_uim.$(SRC) -o \
#	$(OUT_DIR)/kw_pj_uim.$(OBJ)
#$(OUT_DIR)/kw_pj_lmm.$(OBJ): $(IN_DIR)/kw_pj_lmm.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_pj_lmm.$(SRC) -o \
#	$(OUT_DIR)/kw_pj_lmm.$(OBJ)
#$(OUT_DIR)/kw_pj_cfg.$(OBJ): $(IN_DIR)/kw_pj_cfg.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_pj_cfg.$(SRC) -o \
#	$(OUT_DIR)/kw_pj_cfg.$(OBJ)
#$(OUT_DIR)/kw_pj_lib.$(OBJ): $(IN_DIR)/kw_pj_lib.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_pj_lib.$(SRC) -o \
#	$(OUT_DIR)/kw_pj_lib.$(OBJ)
#$(OUT_DIR)/kw_ptlib.$(OBJ): $(IN_DIR)/kw_ptlib.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_ptlib.$(SRC) -o \
#	$(OUT_DIR)/kw_ptlib.$(OBJ)
#$(OUT_DIR)/kw_pj_dbm.$(OBJ): $(IN_DIR)/kw_pj_dbm.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_pj_dbm.$(SRC) -o \
#	$(OUT_DIR)/kw_pj_dbm.$(OBJ)
#$(OUT_DIR)/kw_pj_dlm.$(OBJ): $(IN_DIR)/kw_pj_dlm.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_pj_dlm.$(SRC) -o \
#	$(OUT_DIR)/kw_pj_dlm.$(OBJ)
#$(OUT_DIR)/kw_pj_ulm.$(OBJ): $(IN_DIR)/kw_pj_ulm.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_pj_ulm.$(SRC) -o \
#	$(OUT_DIR)/kw_pj_ulm.$(OBJ)
#$(OUT_DIR)/kw_pj_utl.$(OBJ): $(IN_DIR)/kw_pj_utl.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_pj_utl.$(SRC) -o \
#	$(OUT_DIR)/kw_pj_utl.$(OBJ)
#$(OUT_DIR)/kw_pj_tmr.$(OBJ): $(IN_DIR)/kw_pj_tmr.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_pj_tmr.$(SRC) -o \
#	$(OUT_DIR)/kw_pj_tmr.$(OBJ)
#$(OUT_DIR)/kw_utl.$(OBJ): $(IN_DIR)/kw_utl.$(SRC) $(ALL_INC)
#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_utl.$(SRC) -o \
#	$(OUT_DIR)/kw_utl.$(OBJ)
#
#
#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#

lib: $(LIB_DIR)/libkw.a
include $(COM_BUILD_DIR)/compile.mak

ifeq ($(BIN_LOG), YES)
$(LIB_DIR)/libkw.a:$(C_OBJS)
	@echo -e "Creating log DB $(COLOR)$(LOG_DIR)/kwLog.db $(REVERT_COLOR)"
	$(Q)cat $(DB_FILES) > $(LOG_DIR)/kwLog.db
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libkw.a $(C_OBJS)	
else
$(LIB_DIR)/libkw.a:$(C_OBJS)
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libkw.a $(C_OBJS)	
endif

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning RLC$(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/libkw.a $(C_OBJS)

