#
#
##-------------------------------------------------------------#
#Makefile for product SZ - script generated.
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak
COLOR=$(COLOR_MAG)

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

MOD_FLAGS=-DSZ -US1AP_REL851 -DS1AP_REL9A6
SRC_DIR=$(ROOT_DIR)/src/s1ap
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_SRCS:=$(filter-out %sz_dbr8.c,$(C_SRCS))
C_SRCS:=$(filter-out %sz_dbr9.c,$(C_SRCS))
C_SRCS:=$(filter-out %sz_ex_pt.c,$(C_SRCS))
C_SRCS:=$(filter-out %sz_tst.c,$(C_SRCS))
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))

HDR_FILES+=$(wildcard $(CM_DIR)/env*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/gen*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/ssi*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/cm*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lsz*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/szt.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/sbt.[hx])

HDR_FILES+=$(wildcard $(SRC_DIR)/*.[hx])

# Product sources-------------------------------------------------------
#szSRCS= \
#    $(IN_DIR)/sz_db.$(SRC) \
#    $(IN_DIR)/sz_li.$(SRC) \
#    $(IN_DIR)/sz_mgmt.$(SRC) \
#    $(IN_DIR)/sz_mi.$(SRC) \
#    $(IN_DIR)/sz_msgfn.$(SRC) \
#    $(IN_DIR)/sz_ex_ms.$(SRC) \
#    $(IN_DIR)/sz_ndb.$(SRC) \
#    $(IN_DIR)/sz_id.$(SRC) \
#    $(IN_DIR)/sz_sm.$(SRC) \
#    $(IN_DIR)/sz_smlienb.$(SRC) \
#    $(IN_DIR)/sz_smuienb.$(SRC) \
#    $(IN_DIR)/sz_ptli.$(SRC) \
#    $(IN_DIR)/sz_ptmi.$(SRC) \
#    $(IN_DIR)/sz_ptui.$(SRC) \
#    $(IN_DIR)/sz_tmr.$(SRC) \
#    $(IN_DIR)/sz_ui.$(SRC) \
#    $(IN_DIR)/sz_utils.$(SRC) \
#    $(IN_DIR)/sz_3gdb.$(SRC) 


# Product objects-------------------------------------------------------
#szOBJS= \
#    $(OUT_DIR)/sz_db.$(OBJ) \
#    $(OUT_DIR)/sz_li.$(OBJ) \
#    $(OUT_DIR)/sz_mgmt.$(OBJ) \
#    $(OUT_DIR)/sz_mi.$(OBJ) \
#    $(OUT_DIR)/sz_msgfn.$(OBJ) \
#    $(OUT_DIR)/sz_ex_ms.$(OBJ) \
#    $(OUT_DIR)/sz_ndb.$(OBJ) \
#    $(OUT_DIR)/sz_id.$(OBJ) \
#    $(OUT_DIR)/sz_sm.$(OBJ) \
#    $(OUT_DIR)/sz_smlienb.$(OBJ) \
#    $(OUT_DIR)/sz_smuienb.$(OBJ) \
#    $(OUT_DIR)/sz_ptli.$(OBJ) \
#    $(OUT_DIR)/sz_ptmi.$(OBJ) \
#    $(OUT_DIR)/sz_ptui.$(OBJ) \
#    $(OUT_DIR)/sz_tmr.$(OBJ) \
#    $(OUT_DIR)/sz_ui.$(OBJ) \
#    $(OUT_DIR)/sz_utils.$(OBJ) \
#    $(OUT_DIR)/sz_3gdb.$(OBJ) 


#SZCM_INC=$(VS_DIR)/sz.h $(VS_DIR)/sz.x $(VS_DIR)/sz_err.h

#ALL_INC=$(SZCM_INC) $(CM_INC)
   
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

#$(OUT_DIR)/sz_db.$(OBJ): $(IN_DIR)/sz_db.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/sz_db.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) \
#	$(IN_DIR)/sz_db.$(SRC)
#
#$(OUT_DIR)/sz_3gdb.$(OBJ): $(IN_DIR)/sz_3gdb.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/sz_3gdb.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) \
#	$(IN_DIR)/sz_3gdb.$(SRC)
#
#$(OUT_DIR)/sz_li.$(OBJ): $(IN_DIR)/sz_li.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_li.$(SRC) -o \
#	$(OUT_DIR)/sz_li.$(OBJ)
#$(OUT_DIR)/sz_mgmt.$(OBJ): $(IN_DIR)/sz_mgmt.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_mgmt.$(SRC) -o \
#	$(OUT_DIR)/sz_mgmt.$(OBJ)
#$(OUT_DIR)/sz_mi.$(OBJ): $(IN_DIR)/sz_mi.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_mi.$(SRC) -o \
#	$(OUT_DIR)/sz_mi.$(OBJ)
#$(OUT_DIR)/sz_msgfn.$(OBJ): $(IN_DIR)/sz_msgfn.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_msgfn.$(SRC) -o \
#	$(OUT_DIR)/sz_msgfn.$(OBJ)
#$(OUT_DIR)/sz_ex_ms.$(OBJ): $(IN_DIR)/sz_ex_ms.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_ex_ms.$(SRC) -o \
#	$(OUT_DIR)/sz_ex_ms.$(OBJ)
#$(OUT_DIR)/sz_ndb.$(OBJ): $(IN_DIR)/sz_ndb.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_ndb.$(SRC) -o \
#	$(OUT_DIR)/sz_ndb.$(OBJ)
#$(OUT_DIR)/sz_id.$(OBJ): $(IN_DIR)/sz_id.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_id.$(SRC) -o \
#	$(OUT_DIR)/sz_id.$(OBJ)
#$(OUT_DIR)/sz_sm.$(OBJ): $(IN_DIR)/sz_sm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_sm.$(SRC) -o \
#	$(OUT_DIR)/sz_sm.$(OBJ)
#$(OUT_DIR)/sz_smlienb.$(OBJ): $(IN_DIR)/sz_smlienb.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_smlienb.$(SRC) -o \
#	$(OUT_DIR)/sz_smlienb.$(OBJ)
#$(OUT_DIR)/sz_smuienb.$(OBJ): $(IN_DIR)/sz_smuienb.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_smuienb.$(SRC) -o \
#	$(OUT_DIR)/sz_smuienb.$(OBJ)
#$(OUT_DIR)/sz_ptli.$(OBJ): $(IN_DIR)/sz_ptli.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_ptli.$(SRC) -o \
#	$(OUT_DIR)/sz_ptli.$(OBJ)
#$(OUT_DIR)/sz_ptmi.$(OBJ): $(IN_DIR)/sz_ptmi.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_ptmi.$(SRC) -o \
#	$(OUT_DIR)/sz_ptmi.$(OBJ)
#$(OUT_DIR)/sz_ptui.$(OBJ): $(IN_DIR)/sz_ptui.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_ptui.$(SRC) -o \
#	$(OUT_DIR)/sz_ptui.$(OBJ)
#$(OUT_DIR)/sz_tmr.$(OBJ): $(IN_DIR)/sz_tmr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_tmr.$(SRC) -o \
#	$(OUT_DIR)/sz_tmr.$(OBJ)
#$(OUT_DIR)/sz_ui.$(OBJ): $(IN_DIR)/sz_ui.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_ui.$(SRC) -o \
#	$(OUT_DIR)/sz_ui.$(OBJ)
#$(OUT_DIR)/sz_utils.$(OBJ): $(IN_DIR)/sz_utils.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) $(IN_DIR)/sz_utils.$(SRC) -o \
#	$(OUT_DIR)/sz_utils.$(OBJ)

lib:$(LIB_DIR)/libsz.a
include $(COM_BUILD_DIR)/compile.mak
#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(LIB_DIR)/libsz.a:$(C_OBJS)
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libsz.a $(szOBJS)	

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning SCTP$(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/libsz.a $(C_OBJS)

