#
#
#-------------------------------------------------------------#
#Makefile for product ib - script generated.
#Only the $(CCib) may be modified.
#-------------------------------------------------------------#

include ../common/rsys_fancy.mak

include ../common/env.mak

SRC_DIR=$(ROOT_DIR)/src/ltepdcp

#Prepare source file list
C_SRCS=$(wildcard $(SRC_DIR)/*.c)

#Remove unwanted files from the list
#TODO: brcm should also be added here
C_SRCS:=$(filter-out %ptlib_pal.c,$(C_SRCS))
C_SRCS:=$(filter-out %ptlib_brcm.c,$(C_SRCS))
C_SRCS:=$(filter-out %t2k.c,$(C_SRCS))
C_SRCS:=$(filter-out %t33.c,$(C_SRCS))
C_SRCS:=$(filter-out %tenb_stats.c,$(C_SRCS))
ifeq ($(PLTFRM), BRDCM)
C_SRCS:=$(filter-out %t2k_ptnspacc.c,$(C_SRCS))
C_SRCS:=$(filter-out %mspdt2k_ptsec.c,$(C_SRCS))
else 
ifeq ($(PLTFRM), INTEL)
C_SRCS:=$(filter-out %brcm_ptsec.c,$(C_SRCS))
else 
C_SRCS:=$(filter-out %t2k_ptnspacc.c,$(C_SRCS))
C_SRCS:=$(filter-out %mspdt2k_ptsec.c,$(C_SRCS))
C_SRCS:=$(filter-out %brcm_ptsec.c,$(C_SRCS))
endif
endif

#prepare the list of object files and RLOG related files
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
LOG_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$(C_SRCS))
DB_FILES =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i.db,$(C_SRCS))

#prepare the header file list for this layer
# prepare the list of common header files
HDR_FILES+=$(wildcard $(CM_DIR)/env*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/gen*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/ssi*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/cm*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lpj.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/kwu.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/pju.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/cpj.[hx])

# Add the product specific header files
HDR_FILES+= $(wildcard $(SRC_DIR)/*.[hx])

I_OPTS+=-I$(ROOT_DIR)/src/sec
#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#
#TODO: Removed flags PTPJLIB KW_BG_DL_PROC KW_BG_UL_PROC PX
#MOD_FLAGS= -UKW_PDCP -DPJ -DPTPJLIB  
#TODO: Removed flags PTPJLIB KW_BG_DL_PROC KW_BG_UL_PROC PX TENB_AS_SECURITY
MOD_FLAGS= -UKW_PDCP -DKW -DPJ -DPTPJLIB


# Product objects-------------------------------------------------------
#ifeq ($(SEC_FLAG),-DTENB_AS_SECURITY)
#pjOBJS= \
#    $(OUT_DIR)/pj_cfg_dl.$(OBJ) \
#    $(OUT_DIR)/pj_cfg_ul.$(OBJ) \
#    $(OUT_DIR)/pj_udx.$(OBJ) \
#    $(OUT_DIR)/pj_udx_ptdl.$(OBJ) \
#    $(OUT_DIR)/pj_udx_ptul.$(OBJ) \
#    $(OUT_DIR)/pj_udx_ul.$(OBJ) \
#    $(OUT_DIR)/pj_udx_dl.$(OBJ) \
#    $(OUT_DIR)/pj_dlm.$(OBJ) \
#    $(OUT_DIR)/pj_ulm.$(OBJ) \
#    $(OUT_DIR)/pj_utl.$(OBJ) \
#    $(OUT_DIR)/pj_ul_utl.$(OBJ) \
#    $(OUT_DIR)/pj_dl_utl.$(OBJ) \
#    $(OUT_DIR)/pj_dbm.$(OBJ) \
#    $(OUT_DIR)/pj_dbm_ul.$(OBJ) \
#    $(OUT_DIR)/pj_dbm_dl.$(OBJ) \
#    $(OUT_DIR)/pj_lim.$(OBJ) \
#    $(OUT_DIR)/pj_uim.$(OBJ) \
#    $(OUT_DIR)/pj_lmm.$(OBJ) \
#    $(OUT_DIR)/pj_tmr.$(OBJ) \
#    $(OUT_DIR)/pj_ul_ex_ms.$(OBJ) \
#    $(OUT_DIR)/pj_dl_ex_ms.$(OBJ) \
#    $(OUT_DIR)/pj_lib.$(OBJ) \
#    $(OUT_DIR)/pj_ptmi.$(OBJ) \
#    $(OUT_DIR)/pj_ptli.$(OBJ) \
#    $(OUT_DIR)/pj_ptui.$(OBJ) \
#    $(OUT_DIR)/pj_id.$(OBJ) \
#    $(OUT_DIR)/pj_brcm_ptsec.$(OBJ)\
#    $(OUT_DIR)/pj_ptlib.$(OBJ) \
#    $(OUT_DIR)/pj_tenb_stats.$(OBJ) 
#else
#pjOBJS= \
#    $(OUT_DIR)/pj_cfg_dl.$(OBJ) \
#    $(OUT_DIR)/pj_cfg_ul.$(OBJ) \
#    $(OUT_DIR)/pj_udx.$(OBJ) \
#    $(OUT_DIR)/pj_udx_ptdl.$(OBJ) \
#    $(OUT_DIR)/pj_udx_ptul.$(OBJ) \
#    $(OUT_DIR)/pj_udx_ul.$(OBJ) \
#    $(OUT_DIR)/pj_udx_dl.$(OBJ) \
#    $(OUT_DIR)/pj_dlm.$(OBJ) \
#    $(OUT_DIR)/pj_ulm.$(OBJ) \
#    $(OUT_DIR)/pj_utl.$(OBJ) \
#    $(OUT_DIR)/pj_ul_utl.$(OBJ) \
#    $(OUT_DIR)/pj_dl_utl.$(OBJ) \
#    $(OUT_DIR)/pj_dbm.$(OBJ) \
#    $(OUT_DIR)/pj_dbm_ul.$(OBJ) \
#    $(OUT_DIR)/pj_dbm_dl.$(OBJ) \
#    $(OUT_DIR)/pj_lim.$(OBJ) \
#    $(OUT_DIR)/pj_uim.$(OBJ) \
#    $(OUT_DIR)/pj_lmm.$(OBJ) \
#    $(OUT_DIR)/pj_tmr.$(OBJ) \
#    $(OUT_DIR)/pj_ul_ex_ms.$(OBJ) \
#    $(OUT_DIR)/pj_dl_ex_ms.$(OBJ) \
#    $(OUT_DIR)/pj_lib.$(OBJ) \
#    $(OUT_DIR)/pj_ptmi.$(OBJ) \
#    $(OUT_DIR)/pj_ptli.$(OBJ) \
#    $(OUT_DIR)/pj_ptui.$(OBJ) \
#    $(OUT_DIR)/pj_id.$(OBJ) \
#    $(OUT_DIR)/pj_brcm_ptsec.$(OBJ)\
#    $(OUT_DIR)/pj_ptlib.$(OBJ) \
#    $(OUT_DIR)/pj_tenb_stats.$(OBJ) 
#endif


#PJCM_INC=$(VS_DIR)/pj.h   $(VS_DIR)/pj.x $(VS_DIR)/pj_env.h $(VS_DIR)/pj_err.h

#ALL_INC=$(PJCM_INC) $(CM_INC)
   
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

#$(OUT_DIR)/pj_lim.$(OBJ): $(IN_DIR)/pj_lim.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_lim.$(SRC) -o \
#	$(OUT_DIR)/pj_lim.$(OBJ)
#$(OUT_DIR)/pj_uim.$(OBJ): $(IN_DIR)/pj_uim.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_uim.$(SRC) -o \
#	$(OUT_DIR)/pj_uim.$(OBJ)
#$(OUT_DIR)/pj_lmm.$(OBJ): $(IN_DIR)/pj_lmm.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_lmm.$(SRC) -o \
#	$(OUT_DIR)/pj_lmm.$(OBJ)
#$(OUT_DIR)/pj_cfg_ul.$(OBJ): $(IN_DIR)/pj_cfg_ul.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_cfg_ul.$(SRC) -o \
#	$(OUT_DIR)/pj_cfg_ul.$(OBJ)
#$(OUT_DIR)/pj_udx.$(OBJ): $(IN_DIR)/pj_udx.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_udx.$(SRC) -o \
#	$(OUT_DIR)/pj_udx.$(OBJ)
#$(OUT_DIR)/pj_udx_dl.$(OBJ): $(IN_DIR)/pj_udx_dl.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_udx_dl.$(SRC) -o \
#	$(OUT_DIR)/pj_udx_dl.$(OBJ)
#$(OUT_DIR)/pj_udx_ul.$(OBJ): $(IN_DIR)/pj_udx_ul.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_udx_ul.$(SRC) -o \
#	$(OUT_DIR)/pj_udx_ul.$(OBJ)
##$(OUT_DIR)/pj_udx_ptul.$(OBJ): $(IN_DIR)/pj_udx_ptul.$(SRC) $(ALL_INC)
##	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_udx_ptul.$(SRC) -o \
##	$(OUT_DIR)/pj_udx_ptul.$(OBJ)
#$(OUT_DIR)/pj_udx_ptul.$(OBJ): $(IN_DIR)/pj_udx_ptul.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_udx_ptul.$(SRC) -o \
#	$(OUT_DIR)/pj_udx_ptul.$(OBJ)
#$(OUT_DIR)/pj_udx_ptdl.$(OBJ): $(IN_DIR)/pj_udx_ptdl.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_udx_ptdl.$(SRC) -o \
#	$(OUT_DIR)/pj_udx_ptdl.$(OBJ)
#$(OUT_DIR)/pj_cfg_dl.$(OBJ): $(IN_DIR)/pj_cfg_dl.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_cfg_dl.$(SRC) -o \
#	$(OUT_DIR)/pj_cfg_dl.$(OBJ)
#$(OUT_DIR)/pj_lib.$(OBJ): $(IN_DIR)/pj_lib.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_lib.$(SRC) -o \
#	$(OUT_DIR)/pj_lib.$(OBJ)
#$(OUT_DIR)/pj_ptlib.$(OBJ): $(IN_DIR)/pj_ptlib.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_ptlib.$(SRC) -o \
#	$(OUT_DIR)/pj_ptlib.$(OBJ)
#$(OUT_DIR)/pj_tenb_stats.$(OBJ): $(IN_DIR)/pj_tenb_stats.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_tenb_stats.$(SRC) -o \
#	$(OUT_DIR)/pj_tenb_stats.$(OBJ)
#$(OUT_DIR)/pj_brcm_ptsec.$(OBJ): $(IN_DIR)/pj_brcm_ptsec.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_brcm_ptsec.$(SRC) -o \
#	$(OUT_DIR)/pj_brcm_ptsec.$(OBJ)
#$(OUT_DIR)/pj_dbm.$(OBJ): $(IN_DIR)/pj_dbm.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_dbm.$(SRC) -o \
#	$(OUT_DIR)/pj_dbm.$(OBJ)
#$(OUT_DIR)/pj_dbm_dl.$(OBJ): $(IN_DIR)/pj_dbm_dl.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_dbm_dl.$(SRC) -o \
#	$(OUT_DIR)/pj_dbm_dl.$(OBJ)
#$(OUT_DIR)/pj_dbm_ul.$(OBJ): $(IN_DIR)/pj_dbm_ul.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_dbm_ul.$(SRC) -o \
#	$(OUT_DIR)/pj_dbm_ul.$(OBJ)
#$(OUT_DIR)/pj_dlm.$(OBJ): $(IN_DIR)/pj_dlm.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_dlm.$(SRC) -o \
#	$(OUT_DIR)/pj_dlm.$(OBJ)
#$(OUT_DIR)/pj_ulm.$(OBJ): $(IN_DIR)/pj_ulm.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_ulm.$(SRC) -o \
#	$(OUT_DIR)/pj_ulm.$(OBJ)
#$(OUT_DIR)/pj_utl.$(OBJ): $(IN_DIR)/pj_utl.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_utl.$(SRC) -o \
#	$(OUT_DIR)/pj_utl.$(OBJ)
#$(OUT_DIR)/pj_ul_utl.$(OBJ): $(IN_DIR)/pj_ul_utl.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_ul_utl.$(SRC) -o \
#	$(OUT_DIR)/pj_ul_utl.$(OBJ)
#$(OUT_DIR)/pj_dl_utl.$(OBJ): $(IN_DIR)/pj_dl_utl.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_dl_utl.$(SRC) -o \
#	$(OUT_DIR)/pj_dl_utl.$(OBJ)
#$(OUT_DIR)/pj_ptmi.$(OBJ): $(IN_DIR)/pj_ptmi.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_ptmi.$(SRC) -o \
#	$(OUT_DIR)/pj_ptmi.$(OBJ)
#$(OUT_DIR)/pj_ptli.$(OBJ): $(IN_DIR)/pj_ptli.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_ptli.$(SRC) -o \
#	$(OUT_DIR)/pj_ptli.$(OBJ)
#$(OUT_DIR)/pj_ptui.$(OBJ): $(IN_DIR)/pj_ptui.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_ptui.$(SRC) -o \
#	$(OUT_DIR)/pj_ptui.$(OBJ)
#$(OUT_DIR)/pj_id.$(OBJ): $(IN_DIR)/pj_id.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_id.$(SRC) -o \
#	$(OUT_DIR)/pj_id.$(OBJ)
#$(OUT_DIR)/pj_tmr.$(OBJ): $(IN_DIR)/pj_tmr.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_tmr.$(SRC) -o \
#	$(OUT_DIR)/pj_tmr.$(OBJ)
#$(OUT_DIR)/pj_ul_ex_ms.$(OBJ): $(IN_DIR)/pj_ul_ex_ms.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_ul_ex_ms.$(SRC) -o \
#	$(OUT_DIR)/pj_ul_ex_ms.$(OBJ)
#$(OUT_DIR)/pj_dl_ex_ms.$(OBJ): $(IN_DIR)/pj_dl_ex_ms.$(SRC) $(ALL_INC)
#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_dl_ex_ms.$(SRC) -o \
#	$(OUT_DIR)/pj_dl_ex_ms.$(OBJ)

lib:$(LIB_DIR)/libpj.a
include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
ifeq ($(BIN_LOG), YES)
$(LIB_DIR)/libpj.a:$(C_OBJS)
	@echo -e "Creating log DB $(COLOR)$(LOG_DIR)/pjLog.db $(REVERT_COLOR)"
	$(Q)cat $(DB_FILES) > $(LOG_DIR)/pjLog.db
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libpj.a $(C_OBJS)	
else
$(LIB_DIR)/libpj.a:$(C_OBJS)
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libpj.a $(C_OBJS)	
endif

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning PDCP$(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/libpj.a $(C_OBJS)


