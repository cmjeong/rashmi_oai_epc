

#-------------------------------------------------------------#
#Makefile for product TF - script generated.
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak
COLOR=$(COLOR_BLUE)

SRC_DIR=$(ROOT_DIR)/src/lteclms
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_SRCS:=$(filter-out %ys_stub.c, $(C_SRCS))
C_SRCS:=$(filter-out %ys_ex_pt.c, $(C_SRCS))
C_SRCS:=$(filter-out %ys_tst.c, $(C_SRCS))
C_SRCS:=$(filter-out %se_tst.c, $(C_SRCS))
C_SRCS:=$(filter-out %dft.c, $(C_SRCS))
C_SRCS:=$(filter-out %etm.c, $(C_SRCS))
C_SRCS:=$(filter-out %pal.c, $(C_SRCS))
C_SRCS:=$(filter-out %stub.c, $(C_SRCS))

#prepare the list of object files and RLOG related files
C_WO_PED_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
LOG_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$(C_SRCS))
DB_FILES =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i.db,$(C_SRCS))

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

#CCysFLAGS=-DTF -DYS -DDEBUG -DYS_LTE_PAL -DLTE_PAL_ENB -DYS_PERF_MEAS -DLCCTF -DLCYSUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 \
          -UTFU_TDD -DRG -DLCYSUICTF -DAPI_MAIN


MOD_FLAGS=-DTF -DYS -DRG -DAPI_MAIN -DYS_MS_PHY -DYS_MIB_WARND -DYS_PHY_STOP_AUTO  -DYS_ALLOC_ON_NEED -DMSPD_T2K_CHANGES -URG_ULSCHED_AT_CRC


lib:$(LIB_DIR)/libtf.a
include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
ifeq ($(BIN_LOG), YES)
$(LIB_DIR)/libtf.a:$(C_WO_PED_OBJS)
	@echo -e "Creating log DB $(COLOR)$(LOG_DIR)/ysLog.db $(REVERT_COLOR)"
	$(Q)cat $(DB_FILES) > $(LOG_DIR)/ysLog.db
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libtf.a $(C_WO_PED_OBJS)	
else
$(LIB_DIR)/libtf.a:$(C_WO_PED_OBJS)
	@echo -e " $(COLOR)$(C_WO_PED_OBJS) $@ $(REVERT_COLOR)"
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libtf.a $(C_WO_PED_OBJS)	
endif

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning CL$(REVERT_COLOR)"
	$(Q)\rm -f $(OUT_DIR)/libtf.a $(C_WO_PED_OBJS)
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
