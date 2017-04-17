#
#
##-------------------------------------------------------------#
#Makefile for product TF - script generated.
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak
COLOR=$(COLOR_BLUE)

SRC_DIR=$(ROOT_DIR)/src/lteclbrcm
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_SRCS:=$(filter-out %ur_stub.c, $(C_SRCS))
C_SRCS:=$(filter-out %ur_ex_pt.c, $(C_SRCS))
C_SRCS:=$(filter-out %ur_tst.c, $(C_SRCS))

#prepare the list of object files and RLOG related files
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
LOG_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$(C_SRCS))
DB_FILES =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i.db,$(C_SRCS))

MOD_FLAGS=-DYS -DAPI_MAIN -DYS_FS -UYS_FS_DBG_l1MSG_DUMP -UYS_FS_DEBUG \
    -ULTEFAPI_DISSECTOR

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

#CCysFLAGS=-DTF -DYS -UDEBUG -DLCCTF -DLCYSUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 -DNOFILESYS \
#           -DRG -DLCYSUICTF -DAPI_MAIN -DLCYSMILYS -DLCLYS -UDEBUGP -DTFU_UPGRADE -DYS_FS \
#          -UYS_FS_DBG_L1MSG_DUMP -UYS_FS_DEBUG -ULTEFAPI_DISSECTOR -USM

# Product sources-------------------------------------------------------
#urSRCS= \
#	$(IN_DIR)/ur_l1cl.$(SRC) \
#	$(IN_DIR)/ur_ptui.$(SRC) \
#	$(IN_DIR)/ur_ptmi.$(SRC) \
#	$(IN_DIR)/ur_utl.$(SRC) \
#	$(IN_DIR)/ur_mi.$(SRC) \
#	$(IN_DIR)/ur_ui.$(SRC) \
#	$(IN_DIR)/ur_dl.$(SRC) \
#	$(IN_DIR)/ur_ul.$(SRC) \
#	$(IN_DIR)/ur_sm.$(SRC) \
#	$(IN_DIR)/ur_tmr.$(SRC) \
#	$(IN_DIR)/ur_ex_ms.$(SRC) \
#	$(IN_DIR)/ur_li.$(SRC) \
#	$(IN_DIR)/ur_wrapper.$(SRC) \
#	$(IN_DIR)/ur_init.$(SRC) \
#	$(IN_DIR)/ur_db.$(SRC) 

# Product objects-------------------------------------------------------
#urOBJS= \
#	$(OUT_DIR)/ur_l1cl.$(OBJ) \
#	$(OUT_DIR)/ur_ptui.$(OBJ) \
#	$(OUT_DIR)/ur_ptmi.$(OBJ) \
#	$(OUT_DIR)/ur_utl.$(OBJ) \
#	$(OUT_DIR)/ur_mi.$(OBJ) \
#	$(OUT_DIR)/ur_ui.$(OBJ) \
#	$(OUT_DIR)/ur_dl.$(OBJ) \
#	$(OUT_DIR)/ur_ul.$(OBJ) \
#	$(OUT_DIR)/ur_sm.$(OBJ) \
#	$(OUT_DIR)/ur_tmr.$(OBJ) \
#	$(OUT_DIR)/ur_ex_ms.$(OBJ) \
#	$(OUT_DIR)/ur_li.$(OBJ) \
#	$(OUT_DIR)/ur_wrapper.$(OBJ) \
#	$(OUT_DIR)/ur_init.$(OBJ) \
#	$(OUT_DIR)/ur_db.$(OBJ)


#URCM_INC=$(VS_DIR)/ur_dl.h $(VS_DIR)/ur_err.h $(VS_DIR)/ur.x 

#ALL_INC=$(URCM_INC) $(CM_INC)

#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#
#$(OUT_DIR)/ur_l1cl.$(OBJ): $(IN_DIR)/ur_l1cl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_l1cl.$(SRC) -o \
#	$(OUT_DIR)/ur_l1cl.$(OBJ)
#
#$(OUT_DIR)/ur_ptui.$(OBJ): $(IN_DIR)/ur_ptui.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_ptui.$(SRC) -o \
#	$(OUT_DIR)/ur_ptui.$(OBJ)
#
#$(OUT_DIR)/ur_ptmi.$(OBJ): $(IN_DIR)/ur_ptmi.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_ptmi.$(SRC) -o \
#	$(OUT_DIR)/ur_ptmi.$(OBJ)
#
#$(OUT_DIR)/ur_utl.$(OBJ): $(IN_DIR)/ur_utl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_utl.$(SRC) -o \
#	$(OUT_DIR)/ur_utl.$(OBJ)
#
#$(OUT_DIR)/ur_mi.$(OBJ): $(IN_DIR)/ur_mi.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_mi.$(SRC) -o \
#	$(OUT_DIR)/ur_mi.$(OBJ)
#
#$(OUT_DIR)/ur_ui.$(OBJ): $(IN_DIR)/ur_ui.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_ui.$(SRC) -o \
#	$(OUT_DIR)/ur_ui.$(OBJ)
#
#$(OUT_DIR)/ur_dl.$(OBJ): $(IN_DIR)/ur_dl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_dl.$(SRC) -o \
#	$(OUT_DIR)/ur_dl.$(OBJ)
#
#$(OUT_DIR)/ur_ul.$(OBJ): $(IN_DIR)/ur_ul.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_ul.$(SRC) -o \
#	$(OUT_DIR)/ur_ul.$(OBJ)
#
#$(OUT_DIR)/ur_sm.$(OBJ): $(IN_DIR)/ur_sm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_sm.$(SRC) -o \
#	$(OUT_DIR)/ur_sm.$(OBJ)
#
#$(OUT_DIR)/ur_tmr.$(OBJ): $(IN_DIR)/ur_tmr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_tmr.$(SRC) -o \
#	$(OUT_DIR)/ur_tmr.$(OBJ)
#
#$(OUT_DIR)/ur_ex_ms.$(OBJ): $(IN_DIR)/ur_ex_ms.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_ex_ms.$(SRC) -o \
#	$(OUT_DIR)/ur_ex_ms.$(OBJ)
#
#$(OUT_DIR)/ur_li.$(OBJ): $(IN_DIR)/ur_li.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_li.$(SRC) -o \
#	$(OUT_DIR)/ur_li.$(OBJ)
#
#$(OUT_DIR)/ur_wrapper.$(OBJ): $(IN_DIR)/ur_wrapper.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_wrapper.$(SRC) -o \
#	$(OUT_DIR)/ur_wrapper.$(OBJ)
#
#$(OUT_DIR)/ur_init.$(OBJ): $(IN_DIR)/ur_init.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_init.$(SRC) -o \
#	$(OUT_DIR)/ur_init.$(OBJ)
#
#$(OUT_DIR)/ur_db.$(OBJ): $(IN_DIR)/ur_db.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_db.$(SRC) -o \
#	$(OUT_DIR)/ur_db.$(OBJ)

lib:$(LIB_DIR)/libur.a
include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
ifeq ($(BIN_LOG), YES)
$(LIB_DIR)/libur.a:$(C_OBJS)
	@echo -e "Creating log DB $(COLOR)$(LOG_DIR)/urLog.db $(REVERT_COLOR)"
	$(Q)cat $(DB_FILES) > $(LOG_DIR)/urLog.db
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libur.a $(C_OBJS)	
else
$(LIB_DIR)/libur.a:$(C_OBJS)
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libur.a $(C_OBJS)	
endif

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning CL$(REVERT_COLOR)"
	$(Q)\rm -f $(OUT_DIR)/libur.a $(C_OBJS)
#
#********************************************************************30**
#  
#        End of file:     ur.mak@@/main/TeNB_Main_BR/3 - Wed Jun 11 13:06:24 2014
#    
#********************************************************************31*/
#
#********************************************************************40**
#  
#        Notes:
#  
#********************************************************************41*/
#
#********************************************************************50**
#
#********************************************************************51*/
#
#********************************************************************60**
#  
#       Revision history:
#  
#********************************************************************61*/
#  
#********************************************************************90**
#
#   ver       pat    init                  description
#---------- -------- ---- -----------------------------------------------
#********************************************************************91*/

# DO NOT DELETE THIS LINE -- make depend depends on it.
