#-------------------------------------------------------------#
#Makefile for SON
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak
COLOR=$(COLOR_YELLOW)

SRC_DIR=$(ROOT_DIR)/src/lteson/src

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#
MOD_FLAGS = -DNL

# Product sources-------------------------------------------------------
C_SRCS=$(wildcard $(SRC_DIR)/*.c)

# prepare the list of common header files
HDR_FILES+=$(wildcard $(CM_DIR)/env*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/gen*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/ssi*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/cm*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lnl*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/nlu*.[hx])

# Add the product specific header files
HDR_FILES+= $(wildcard $(SRC_DIR)/*.[hx])

#prepare the list of object files and RLOG related files
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
LOG_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$(C_SRCS))
DB_FILES =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i.db,$(C_SRCS))

#nlSRCS= \
#    $(IN_DIR)/nl_init.$(SRC) \
#    $(IN_DIR)/nl_ptui.$(SRC) \
#    $(IN_DIR)/nl_ptmi.$(SRC) \
#    $(IN_DIR)/nl_lmm.$(SRC) \
#    $(IN_DIR)/nl_ex_ms.$(SRC)\
#    $(IN_DIR)/nl_pci_sel.$(SRC)\
#    $(IN_DIR)/nl_events.$(SRC)\
#    $(IN_DIR)/nl_alarm.$(SRC)\
#    $(IN_DIR)/nl_earfcn_sel.$(SRC)\
#    $(IN_DIR)/nl_prach_sel.$(SRC)

# Product objects-------------------------------------------------------
#nlOBJS= \
#    $(OUT_DIR)/nl_init.$(OBJ) \
#    $(OUT_DIR)/nl_ptui.$(OBJ) \
#    $(OUT_DIR)/nl_ptmi.$(OBJ) \
#    $(OUT_DIR)/nl_lmm.$(OBJ)  \
#    $(OUT_DIR)/nl_ex_ms.$(OBJ) \
#    $(OUT_DIR)/nl_pci_sel.$(OBJ) \
#    $(OUT_DIR)/nl_earfcn_sel.$(OBJ) \
#    $(OUT_DIR)/nl_events.$(OBJ) \
#    $(OUT_DIR)/nl_alarm.$(OBJ) \
#    $(OUT_DIR)/nl_prach_sel.$(OBJ)
#
#NL_INC=$(VS_DIR)/nl.h $(VS_DIR)/nl.x
#ALL_INC=$(NL_INC) $(CM_INC)
   
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

#$(OUT_DIR)/nl_init.$(OBJ): $(IN_DIR)/nl_init.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCnlFLAGS) $(IN_DIR)/nl_init.$(SRC) -o \
#	$(OUT_DIR)/nl_init.$(OBJ)
#$(OUT_DIR)/nl_ptui.$(OBJ): $(IN_DIR)/nl_ptui.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCnlFLAGS) $(IN_DIR)/nl_ptui.$(SRC) -o \
#	$(OUT_DIR)/nl_ptui.$(OBJ)
#$(OUT_DIR)/nl_ptmi.$(OBJ): $(IN_DIR)/nl_ptmi.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCnlFLAGS) $(IN_DIR)/nl_ptmi.$(SRC) -o \
#	$(OUT_DIR)/nl_ptmi.$(OBJ)
#$(OUT_DIR)/nl_lmm.$(OBJ): $(IN_DIR)/nl_lmm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCnlFLAGS) $(IN_DIR)/nl_lmm.$(SRC) -o \
#	$(OUT_DIR)/nl_lmm.$(OBJ)
#$(OUT_DIR)/nl_ex_ms.$(OBJ): $(IN_DIR)/nl_ex_ms.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCnlFLAGS) $(IN_DIR)/nl_ex_ms.$(SRC) -o \
#	$(OUT_DIR)/nl_ex_ms.$(OBJ)
#$(OUT_DIR)/nl_pci_sel.$(OBJ): $(IN_DIR)/nl_pci_sel.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCnlFLAGS) $(IN_DIR)/nl_pci_sel.$(SRC) -o \
#	$(OUT_DIR)/nl_pci_sel.$(OBJ)
#$(OUT_DIR)/nl_earfcn_sel.$(OBJ): $(IN_DIR)/nl_earfcn_sel.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCnlFLAGS) $(IN_DIR)/nl_earfcn_sel.$(SRC) -o \
#	$(OUT_DIR)/nl_earfcn_sel.$(OBJ)
#$(OUT_DIR)/nl_events.$(OBJ): $(IN_DIR)/nl_events.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCnlFLAGS) $(IN_DIR)/nl_events.$(SRC) -o \
#	$(OUT_DIR)/nl_events.$(OBJ)
#$(OUT_DIR)/nl_alarm.$(OBJ): $(IN_DIR)/nl_alarm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCnlFLAGS) $(IN_DIR)/nl_alarm.$(SRC) -o \
#	$(OUT_DIR)/nl_alarm.$(OBJ)
#$(OUT_DIR)/nl_prach_sel.$(OBJ): $(IN_DIR)/nl_prach_sel.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCnlFLAGS) $(IN_DIR)/nl_prach_sel.$(SRC) -o \
#	$(OUT_DIR)/nl_prach_sel.$(OBJ)
#

lib:$(LIB_DIR)/libnl.a
include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
ifeq ($(BIN_LOG), YES)
$(LIB_DIR)/libnl.a:$(C_OBJS)
	@echo -e "Creating log DB $(COLOR)$(LOG_DIR)/nlLog.db $(REVERT_COLOR)"
	$(Q)cat $(DB_FILES) > $(LOG_DIR)/nlLog.db
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libnl.a $(C_OBJS)	
else
$(LIB_DIR)/libnl.a:$(C_OBJS)
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libnl.a $(C_OBJS)	
endif

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning SON$(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/libnl.a $(C_OBJS)

