#

#-------------------------------------------------------------#
#Makefile for product TF - script generated.
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak
COLOR=$(COLOR_BLUE)

SRC_DIR=$(ROOT_DIR)/src/lteclsrs
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_SRCS:=$(filter-out %pal_db.c, $(C_SRCS))
C_SRCS:=$(filter-out %pal_db_fdd.c, $(C_SRCS))
C_SRCS:=$(filter-out %pal_id.c, $(C_SRCS))
C_SRCS:=$(filter-out %dft.c, $(C_SRCS))
C_SRCS:=$(filter-out %pal_tst.c, $(C_SRCS))
C_SRCS:=$(filter-out %pal_main.c, $(C_SRCS))
C_SRCS:=$(filter-out %stub.c, $(C_SRCS))
C_SRCS:=$(filter-out %ex_pt.c, $(C_SRCS))

C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
LOG_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$(C_SRCS))
DB_FILES =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i.db,$(C_SRCS))

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCysFLAGS=-DTF -DYS -DDEBUG -DYS_LTE_PAL -DLTE_PAL_ENB -DYS_PERF_MEAS -DLCCTF -DLCYSUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 \
          -UTFU_TDD -DRG -DLCYSUICTF -DAPI_MAIN

MOD_FLAGS=-DTF -DYS -DYS_LTE_PAL -DRG -DAPI_MAIN -DYS_ENB_CFG #-DLTE_PAL_ENB -DLTE_ENB_PAL

lib:$(LIB_DIR)/libtf.a
include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
ifeq ($(BIN_LOG), YES)
$(LIB_DIR)/libtf.a:$(C_OBJS)
	@echo -e "Creating log DB $(COLOR)$(LOG_DIR)/ysLog.db $(REVERT_COLOR)"
	$(Q)cat $(DB_FILES) > $(LOG_DIR)/ysLog.db
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libtf.a $(C_OBJS)	
else
$(LIB_DIR)/libtf.a:$(C_OBJS)
	@echo -e " $(COLOR)$(C_OBJS) $@ $(REVERT_COLOR)"
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libtf.a $(C_OBJS)	
endif

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning CL$(REVERT_COLOR)"
	$(Q)\rm -f $(OUT_DIR)/libtf.a $(C_OBJS)

