#-------------------------------------------------------------#
#Makefile for OpenSource Security Algorithm Library
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak
COLOR=$(COLOR_GREEN)
SRC_DIR=$(ROOT_DIR)/src/sec
OBJ_DIR=$(OBJ_ROOT)/cpuh
LIB_DIR=$(ROOT_DIR)/src/enbapp/build/lib

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

SEC_IOPTS += -I$(SRC_DIR)

# Product objects-------------------------------------------------------
secOBJS= \
    $(OUT_DIR)/auth_alg.$(OBJ)           \
    $(OUT_DIR)/endianness.$(OBJ) \
    $(OUT_DIR)/hmac.$(OBJ) \
    $(OUT_DIR)/hmacsha256.$(OBJ) \
    $(OUT_DIR)/mp.$(OBJ) \
    $(OUT_DIR)/sha256.$(OBJ) \
    $(OUT_DIR)/snow_3g.$(OBJ) \
    $(OUT_DIR)/snow3g_f8f9.$(OBJ) \
    $(OUT_DIR)/aes.$(OBJ) 

#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

$(OUT_DIR)/auth_alg.$(OBJ): $(IN_DIR)/auth_alg.$(SRC1) $(ALL_INC)
	@echo -e "  SEC OPTS $(SEC_IOPTS)"
	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/auth_alg.$(SRC1) -o \
	$(OUT_DIR)/auth_alg.$(OBJ)

$(OUT_DIR)/endianness.$(OBJ): $(IN_DIR)/endianness.$(SRC1) $(ALL_INC)
	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/endianness.$(SRC1) -o \
	$(OUT_DIR)/endianness.$(OBJ)

$(OUT_DIR)/hmac.$(OBJ): $(IN_DIR)/hmac.$(SRC1) $(ALL_INC)
	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/hmac.$(SRC1) -o \
	$(OUT_DIR)/hmac.$(OBJ)

$(OUT_DIR)/hmacsha256.$(OBJ): $(IN_DIR)/hmacsha256.$(SRC1) $(ALL_INC)
	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/hmacsha256.$(SRC1) -o \
	$(OUT_DIR)/hmacsha256.$(OBJ)

$(OUT_DIR)/mp.$(OBJ): $(IN_DIR)/mp.$(SRC1) $(ALL_INC)
	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/mp.$(SRC1) -o \
	$(OUT_DIR)/mp.$(OBJ)

$(OUT_DIR)/sha256.$(OBJ): $(IN_DIR)/sha256.$(SRC1) $(ALL_INC)
	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/sha256.$(SRC1) -o \
	$(OUT_DIR)/sha256.$(OBJ)

$(OUT_DIR)/snow_3g.$(OBJ): $(IN_DIR)/snow_3g.$(SRC1) $(ALL_INC)
	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/snow_3g.$(SRC1) -o \
	$(OUT_DIR)/snow_3g.$(OBJ)

$(OUT_DIR)/snow3g_f8f9.$(OBJ): $(IN_DIR)/snow3g_f8f9.$(SRC1) $(ALL_INC)
	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/snow3g_f8f9.$(SRC1) -o \
	$(OUT_DIR)/snow3g_f8f9.$(OBJ)

$(OUT_DIR)/aes.$(OBJ): $(IN_DIR)/aes.$(SRC1) $(ALL_INC)
	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/aes.$(SRC1) -o \
	$(OUT_DIR)/aes.$(OBJ)

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(LIB_DIR)/libsec.a:$(secOBJS) 
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q) -cr $(LIB_DIR)/libsec.a $(secOBJS)

#$(OUT_DIR)/rmprepro:$(rmOBJS)

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning CPUH CM$(REVERT_COLOR)"
	@echo -e "$(COLOR_RED) $(secOBJS) $(REVERT_COLOR)"
	\rm -f $(OUT_DIR)/libsec.a $(secOBJS)

