#
#-------------------------------------------------------------#
#Makefile for product HI - script generated.
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak
COLOR=$(COLOR_RED)
#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

MOD_FLAGS=-USZ -DHI

SRC_DIR=$(ROOT_DIR)/src/tucl

# Product sources-------------------------------------------------------
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_SRCS:=$(filter-out %tst.c, $(C_SRCS))
C_SRCS:=$(filter-out %ex_pt.c, $(C_SRCS))
C_SRCS:=$(filter-out %acc.c, $(C_SRCS))
C_SRCS:=$(filter-out %acc1.c, $(C_SRCS))
C_SRCS:=$(filter-out %acc2.c, $(C_SRCS))
C_SRCS:=$(filter-out %accsh.c, $(C_SRCS))
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))

# prepare the list of common header files
HDR_FILES+=$(wildcard $(CM_DIR)/env*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/gen*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/ssi*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/cm*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lhi.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/hit.[hx])

#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

#$(OUT_DIR)/hi_bdy1.$(OBJ): $(IN_DIR)/hi_bdy1.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/hi_bdy1.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) \
#	$(IN_DIR)/hi_bdy1.$(SRC)
#$(OUT_DIR)/hi_bdy2.$(OBJ): $(IN_DIR)/hi_bdy2.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_bdy2.$(SRC) -o \
#	$(OUT_DIR)/hi_bdy2.$(OBJ)
#$(OUT_DIR)/hi_bdy3.$(OBJ): $(IN_DIR)/hi_bdy3.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_bdy3.$(SRC) -o \
#	$(OUT_DIR)/hi_bdy3.$(OBJ)
#$(OUT_DIR)/hi_ex_ms.$(OBJ): $(IN_DIR)/hi_ex_ms.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_ex_ms.$(SRC) -o \
#	$(OUT_DIR)/hi_ex_ms.$(OBJ)
#$(OUT_DIR)/hi_id.$(OBJ): $(IN_DIR)/hi_id.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_id.$(SRC) -o \
#	$(OUT_DIR)/hi_id.$(OBJ)
#$(OUT_DIR)/hi_ptmi.$(OBJ): $(IN_DIR)/hi_ptmi.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_ptmi.$(SRC) -o \
#	$(OUT_DIR)/hi_ptmi.$(OBJ)
#$(OUT_DIR)/hi_ptui.$(OBJ): $(IN_DIR)/hi_ptui.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_ptui.$(SRC) -o \
#	$(OUT_DIR)/hi_ptui.$(OBJ)
#

lib: $(LIB_DIR)/libhi.a
include $(COM_BUILD_DIR)/compile.mak
#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(LIB_DIR)/libhi.a:$(C_OBJS)
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	ar -cr $(LIB_DIR)/libhi.a $(C_OBJS)	

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning TUCL$(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/libhi.a $(C_OBJS)

