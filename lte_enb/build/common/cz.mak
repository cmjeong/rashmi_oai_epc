#
#-------------------------------------------------------------#
#Makefile for product CZ - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak
COLOR=$(COLOR_MAG)

SRC_DIR=$(ROOT_DIR)/src/x2ap
#product specific options should be identified.
MOD_FLAGS= -DCZ

HDR_FILES+=$(wildcard $(CM_DIR)/env*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/gen*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/ssi*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/cm*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lsz*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/szt.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/sbt.[hx])

HDR_FILES+=$(wildcard $(SRC_DIR)/*.[hx])
# Product sources-------------------------------------------------------
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_SRCS:=$(filter-out %cz_ex_pt.c,$(C_SRCS))
C_SRCS:=$(filter-out %cz_tst.c,$(C_SRCS))
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))

#czSRCS= \
#    $(IN_DIR)/cz_db.$(SRC) \
#    $(IN_DIR)/cz_lim.$(SRC) \
#    $(IN_DIR)/cz_nmm.$(SRC) \
#    $(IN_DIR)/cz_ex_ms.$(SRC) \
#    $(IN_DIR)/cz_id.$(SRC) \
#    $(IN_DIR)/cz_lmm.$(SRC) \
#    $(IN_DIR)/cz_ptli.$(SRC) \
#    $(IN_DIR)/cz_ptmi.$(SRC) \
#    $(IN_DIR)/cz_ptui.$(SRC) \
#    $(IN_DIR)/cz_tmr.$(SRC) \
#    $(IN_DIR)/cz_uim.$(SRC) \
#    $(IN_DIR)/cz_utl.$(SRC) \
#    $(IN_DIR)/cz_tpm.$(SRC) \
#    $(IN_DIR)/cz_bmp.$(SRC) \
#    $(IN_DIR)/cz_edm.$(SRC) \
#    $(IN_DIR)/cz_gpm.$(SRC) \
#    $(IN_DIR)/cz_ldm.$(SRC) \
#
#
## Product objects-------------------------------------------------------
#czOBJS= \
#    $(OUT_DIR)/cz_db.$(OBJ) \
#    $(OUT_DIR)/cz_lim.$(OBJ) \
#    $(OUT_DIR)/cz_nmm.$(OBJ) \
#    $(OUT_DIR)/cz_ex_ms.$(OBJ) \
#    $(OUT_DIR)/cz_id.$(OBJ) \
#    $(OUT_DIR)/cz_lmm.$(OBJ) \
#    $(OUT_DIR)/cz_ptli.$(OBJ) \
#    $(OUT_DIR)/cz_ptmi.$(OBJ) \
#    $(OUT_DIR)/cz_ptui.$(OBJ) \
#    $(OUT_DIR)/cz_tmr.$(OBJ) \
#    $(OUT_DIR)/cz_uim.$(OBJ) \
#    $(OUT_DIR)/cz_utl.$(OBJ) \
#    $(OUT_DIR)/cz_tpm.$(OBJ) \
#    $(OUT_DIR)/cz_bmp.$(OBJ) \
#    $(OUT_DIR)/cz_edm.$(OBJ) \
#    $(OUT_DIR)/cz_gpm.$(OBJ) \
#    $(OUT_DIR)/cz_ldm.$(OBJ) 
#
#
#CZCM_INC=$(VS_DIR)/cz.h $(VS_DIR)/cz.x $(VS_DIR)/cz_err.h
#
#ALL_INC=$(CZCM_INC) $(CM_INC)
#   
##-------------------------------------------------------------#
##-------------------------------------------------------------#
##Compiler macros             
##-------------------------------------------------------------#
#
#$(OUT_DIR)/cz_db.$(OBJ): $(IN_DIR)/cz_db.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/cz_db.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) \
#	$(IN_DIR)/cz_db.$(SRC)
#$(OUT_DIR)/cz_lim.$(OBJ): $(IN_DIR)/cz_lim.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_lim.$(SRC) -o \
#	$(OUT_DIR)/cz_lim.$(OBJ)
#$(OUT_DIR)/cz_nmm.$(OBJ): $(IN_DIR)/cz_nmm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_nmm.$(SRC) -o \
#	$(OUT_DIR)/cz_nmm.$(OBJ)
#$(OUT_DIR)/cz_ex_ms.$(OBJ): $(IN_DIR)/cz_ex_ms.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_ex_ms.$(SRC) -o \
#	$(OUT_DIR)/cz_ex_ms.$(OBJ)
#$(OUT_DIR)/cz_id.$(OBJ): $(IN_DIR)/cz_id.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_id.$(SRC) -o \
#	$(OUT_DIR)/cz_id.$(OBJ)
#$(OUT_DIR)/cz_lmm.$(OBJ): $(IN_DIR)/cz_lmm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_lmm.$(SRC) -o \
#	$(OUT_DIR)/cz_lmm.$(OBJ)
#$(OUT_DIR)/cz_ptli.$(OBJ): $(IN_DIR)/cz_ptli.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_ptli.$(SRC) -o \
#	$(OUT_DIR)/cz_ptli.$(OBJ)
#$(OUT_DIR)/cz_ptmi.$(OBJ): $(IN_DIR)/cz_ptmi.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_ptmi.$(SRC) -o \
#	$(OUT_DIR)/cz_ptmi.$(OBJ)
#$(OUT_DIR)/cz_ptui.$(OBJ): $(IN_DIR)/cz_ptui.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_ptui.$(SRC) -o \
#	$(OUT_DIR)/cz_ptui.$(OBJ)
#$(OUT_DIR)/cz_tmr.$(OBJ): $(IN_DIR)/cz_tmr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_tmr.$(SRC) -o \
#	$(OUT_DIR)/cz_tmr.$(OBJ)
#$(OUT_DIR)/cz_uim.$(OBJ): $(IN_DIR)/cz_uim.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_uim.$(SRC) -o \
#	$(OUT_DIR)/cz_uim.$(OBJ)
#$(OUT_DIR)/cz_utl.$(OBJ): $(IN_DIR)/cz_utl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_utl.$(SRC) -o \
#	$(OUT_DIR)/cz_utl.$(OBJ)
#$(OUT_DIR)/cz_tpm.$(OBJ): $(IN_DIR)/cz_tpm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_tpm.$(SRC) -o \
#	$(OUT_DIR)/cz_tpm.$(OBJ)
#$(OUT_DIR)/cz_bmp.$(OBJ): $(IN_DIR)/cz_bmp.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_bmp.$(SRC) -o \
#	$(OUT_DIR)/cz_bmp.$(OBJ)
#$(OUT_DIR)/cz_edm.$(OBJ): $(IN_DIR)/cz_edm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_edm.$(SRC) -o \
#	$(OUT_DIR)/cz_edm.$(OBJ)
#$(OUT_DIR)/cz_gpm.$(OBJ): $(IN_DIR)/cz_gpm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_gpm.$(SRC) -o \
#	$(OUT_DIR)/cz_gpm.$(OBJ)
#$(OUT_DIR)/cz_ldm.$(OBJ): $(IN_DIR)/cz_ldm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) $(IN_DIR)/cz_ldm.$(SRC) -o \
#	$(OUT_DIR)/cz_ldm.$(OBJ)

lib:$(LIB_DIR)/libcz.a
include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(LIB_DIR)/libcz.a:$(C_OBJS)
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libcz.a $(szOBJS)	

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning X2AP$(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/libcz.a $(C_OBJS)

