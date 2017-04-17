#
#
##-------------------------------------------------------------#
#Makefile for product SB - script generated.
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak
COLOR=$(COLOR_MAG)
#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

SRC_DIR=$(ROOT_DIR)/src/sctp

# Product sources-------------------------------------------------------
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_SRCS:=$(filter-out %tst.c, $(C_SRCS))
C_SRCS:=$(filter-out %ex_pt.c, $(C_SRCS))

#prepare the list of object files and RLOG related files
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
LOG_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$(C_SRCS))
DB_FILES =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i.db,$(C_SRCS))

# prepare the list of common header files
HDR_FILES+=$(wildcard $(CM_DIR)/env*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/gen*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/ssi*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/cm*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lsb*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/hit.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/sct.[hx])

MOD_FLAGS=-DSB

# This module does not support binary logging
TEXT_LOG=YES

#sbSRCS= \
#    $(IN_DIR)/sb_bdy1.$(SRC) \
#    $(IN_DIR)/sb_bdy2.$(SRC) \
#    $(IN_DIR)/sb_bdy3.$(SRC) \
#    $(IN_DIR)/sb_bdy4.$(SRC) \
#    $(IN_DIR)/sb_ex_ms.$(SRC) \
#    $(IN_DIR)/sb_id.$(SRC) \
#    $(IN_DIR)/sb_ptmi.$(SRC) \
#    $(IN_DIR)/sb_ptui.$(SRC) \
#    $(IN_DIR)/sb_ptli.$(SRC) \
#    $(IN_DIR)/sb_mtu.$(SRC) \
#    $(IN_DIR)/sb_port.$(SRC)


# Product objects-------------------------------------------------------
#sbOBJS= \
#    $(OUT_DIR)/sb_bdy1.$(OBJ) \
#    $(OUT_DIR)/sb_bdy2.$(OBJ) \
#    $(OUT_DIR)/sb_bdy3.$(OBJ) \
#    $(OUT_DIR)/sb_bdy4.$(OBJ) \
#    $(OUT_DIR)/sb_ex_ms.$(OBJ) \
#    $(OUT_DIR)/sb_id.$(OBJ) \
#    $(OUT_DIR)/sb_ptmi.$(OBJ) \
#    $(OUT_DIR)/sb_ptui.$(OBJ) \
#    $(OUT_DIR)/sb_ptli.$(OBJ) \
#    $(OUT_DIR)/sb_mtu.$(OBJ) \
#    $(OUT_DIR)/sb_port.$(OBJ) 


#SBCM_INC=$(VS_DIR)/sb.h $(VS_DIR)/sb.x $(VS_DIR)/sb_mtu.h $(VS_DIR)/sb_mtu.x $(VS_DIR)/sb_port.h $(VS_DIR)/sb_port.x $(VS_DIR)/sb_err.h
#ALL_INC=$(SBCM_INC) $(CM_INC)
   
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

#$(OUT_DIR)/sb_bdy1.$(OBJ): $(IN_DIR)/sb_bdy1.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/sb_bdy1.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CCsbFLAGS) \
#	$(IN_DIR)/sb_bdy1.$(SRC)
#$(OUT_DIR)/sb_bdy2.$(OBJ): $(IN_DIR)/sb_bdy2.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCsbFLAGS) $(IN_DIR)/sb_bdy2.$(SRC) -o \
#	$(OUT_DIR)/sb_bdy2.$(OBJ)
#$(OUT_DIR)/sb_bdy3.$(OBJ): $(IN_DIR)/sb_bdy3.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCsbFLAGS) $(IN_DIR)/sb_bdy3.$(SRC) -o \
#	$(OUT_DIR)/sb_bdy3.$(OBJ)
#$(OUT_DIR)/sb_bdy4.$(OBJ): $(IN_DIR)/sb_bdy4.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCsbFLAGS) $(IN_DIR)/sb_bdy4.$(SRC) -o \
#	$(OUT_DIR)/sb_bdy4.$(OBJ)
#$(OUT_DIR)/sb_ex_ms.$(OBJ): $(IN_DIR)/sb_ex_ms.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCsbFLAGS) $(IN_DIR)/sb_ex_ms.$(SRC) -o \
#	$(OUT_DIR)/sb_ex_ms.$(OBJ)
#$(OUT_DIR)/sb_id.$(OBJ): $(IN_DIR)/sb_id.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCsbFLAGS) $(IN_DIR)/sb_id.$(SRC) -o \
#	$(OUT_DIR)/sb_id.$(OBJ)
#$(OUT_DIR)/sb_ptmi.$(OBJ): $(IN_DIR)/sb_ptmi.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCsbFLAGS) $(IN_DIR)/sb_ptmi.$(SRC) -o \
#	$(OUT_DIR)/sb_ptmi.$(OBJ)
#$(OUT_DIR)/sb_ptui.$(OBJ): $(IN_DIR)/sb_ptui.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCsbFLAGS) $(IN_DIR)/sb_ptui.$(SRC) -o \
#	$(OUT_DIR)/sb_ptui.$(OBJ)
#$(OUT_DIR)/sb_ptli.$(OBJ): $(IN_DIR)/sb_ptli.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCsbFLAGS) $(IN_DIR)/sb_ptli.$(SRC) -o \
#	$(OUT_DIR)/sb_ptli.$(OBJ)
#$(OUT_DIR)/sb_mtu.$(OBJ): $(IN_DIR)/sb_mtu.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCsbFLAGS) $(IN_DIR)/sb_mtu.$(SRC) -o \
#	$(OUT_DIR)/sb_mtu.$(OBJ)
#$(OUT_DIR)/sb_port.$(OBJ): $(IN_DIR)/sb_port.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCsbFLAGS) $(IN_DIR)/sb_port.$(SRC) -o \
#	$(OUT_DIR)/sb_port.$(OBJ)

lib: $(LIB_DIR)/libsb.a
include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(LIB_DIR)/libsb.a:$(C_OBJS)
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)$(AR) -cr $(LIB_DIR)/libsb.a $(C_OBJS)	

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning SCTP$(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/libsb.a $(C_OBJS)

