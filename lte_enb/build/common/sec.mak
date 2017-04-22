#-------------------------------------------------------------#
#Makefile for OpenSource Security Algorithm Library
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak
COLOR=$(COLOR_BLUE)
SRC_DIR=$(ROOT_DIR)/src/sec

# Product sources-------------------------------------------------------
C_SRCS=$(wildcard $(SRC_DIR)/*.c)

# Add the product specific header files
HDR_FILES+= $(wildcard $(SRC_DIR)/*.[hx])

#prepare the list of object files and RLOG related files
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
LOG_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$(C_SRCS))
DB_FILES =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i.db,$(C_SRCS))

# Product objects-------------------------------------------------------
#secOBJS= \
#    $(OUT_DIR)/auth_alg.$(OBJ)           \
#    $(OUT_DIR)/endianness.$(OBJ) \
#    $(OUT_DIR)/hmac.$(OBJ) \
#    $(OUT_DIR)/hmacsha256.$(OBJ) \
#    $(OUT_DIR)/mp.$(OBJ) \
#    $(OUT_DIR)/sha256.$(OBJ) \
#    $(OUT_DIR)/snow_3g.$(OBJ) \
#    $(OUT_DIR)/snow3g_f8f9.$(OBJ) \
#    $(OUT_DIR)/aes.$(OBJ) 

#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

#$(OUT_DIR)/auth_alg.$(OBJ): $(IN_DIR)/auth_alg.$(SRC1) $(ALL_INC)
#	@echo -e "  SEC OPTS $(SEC_IOPTS)"
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/auth_alg.$(SRC1) -o \
#	$(OUT_DIR)/auth_alg.$(OBJ)
#
#$(OUT_DIR)/endianness.$(OBJ): $(IN_DIR)/endianness.$(SRC1) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/endianness.$(SRC1) -o \
#	$(OUT_DIR)/endianness.$(OBJ)
#
#$(OUT_DIR)/hmac.$(OBJ): $(IN_DIR)/hmac.$(SRC1) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/hmac.$(SRC1) -o \
#	$(OUT_DIR)/hmac.$(OBJ)
#
#$(OUT_DIR)/hmacsha256.$(OBJ): $(IN_DIR)/hmacsha256.$(SRC1) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/hmacsha256.$(SRC1) -o \
#	$(OUT_DIR)/hmacsha256.$(OBJ)
#
#$(OUT_DIR)/mp.$(OBJ): $(IN_DIR)/mp.$(SRC1) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/mp.$(SRC1) -o \
#	$(OUT_DIR)/mp.$(OBJ)
#
#$(OUT_DIR)/sha256.$(OBJ): $(IN_DIR)/sha256.$(SRC1) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/sha256.$(SRC1) -o \
#	$(OUT_DIR)/sha256.$(OBJ)
#
#$(OUT_DIR)/snow_3g.$(OBJ): $(IN_DIR)/snow_3g.$(SRC1) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/snow_3g.$(SRC1) -o \
#	$(OUT_DIR)/snow_3g.$(OBJ)
#
#$(OUT_DIR)/snow3g_f8f9.$(OBJ): $(IN_DIR)/snow3g_f8f9.$(SRC1) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/snow3g_f8f9.$(SRC1) -o \
#	$(OUT_DIR)/snow3g_f8f9.$(OBJ)
#
#$(OUT_DIR)/aes.$(OBJ): $(IN_DIR)/aes.$(SRC1) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  $(COPTS) $(IOPTS) $(SEC_IOPTS) $(POPTS) $(IN_DIR)/aes.$(SRC1) -o \
#	$(OUT_DIR)/aes.$(OBJ)
#


lib:$(LIB_DIR)/libsec.a
include $(COM_BUILD_DIR)/compile.mak
#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
ifeq ($(BIN_LOG), YES)
$(LIB_DIR)/libsec.a:$(C_OBJS)
	@echo -e "Creating log DB $(COLOR)$(LOG_DIR)/secLog.db $(REVERT_COLOR)"
	$(Q)cat $(DB_FILES) > $(LOG_DIR)/secLog.db
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libsec.a $(C_OBJS)	
else
$(LIB_DIR)/libsec.a:$(C_OBJS)
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libsec.a $(C_OBJS)	
endif

#$(OUT_DIR)/rmprepro:$(rmOBJS)

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning SEC$(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/libsec.a $(C_OBJS)

