#
#-------------------------------------------------------------#
#Makefile for product NH - script generated.
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak

CC       = $(RRC_COMP)
SRC_DIR  = $(ROOT_DIR)/src/lterrc
CM_DIR   = $(ROOT_DIR)/src/cm

COLOR=$(COLOR_GREEN)

# prepare the list of common header files
HDR_FILES+=$(wildcard $(CM_DIR)/env*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/gen*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/ssi*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/cm*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/nhu*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lnh*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/crl.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/crg.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/cpj.[hx])

# Add the product specific header files
HDR_FILES+= $(wildcard $(SRC_DIR)/*.[hx])

# prepare the list of source files
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_SRCS:=$(filter-out %nh_tst.c,$(C_SRCS))
C_SRCS:=$(filter-out %nh_ex_pt.c,$(C_SRCS))
#C_SRCS:=$(filter-out %nh_init.c,$(C_SRCS))

#prepare the list of object files and RLOG related files
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
LOG_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$(C_SRCS))
DB_FILES =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i.db,$(C_SRCS))

C_SRCS_WO_PEDANTIC = $(SRC_DIR)/nh_init.c
C_WO_PED_OBJS = $(OBJ_DIR)/nh_init.o
LOG_FILES+= $(OBJ_DIR)/nh_init.i
DB_FILES+= $(OBJ_DIR)/nh_init.i.db

lib: $(LIB_DIR)/libnh.a

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#
MOD_FLAGS=-DNH -DLTERRC_REL9

# Include the rules for making .o from .c
include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
ifeq ($(BIN_LOG), YES)
$(LIB_DIR)/libnh.a:$(C_OBJS) $(C_WO_PED_OBJS)
	@echo -e "Creating log DB $(COLOR)$(LOG_DIR)/nhLog.db $(REVERT_COLOR)"
	$(Q)cat $(DB_FILES) > $(LOG_DIR)/nhLog.db
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libnh.a $(C_OBJS)	$(C_WO_PED_OBJS)
else
$(LIB_DIR)/libnh.a:$(C_OBJS)
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libnh.a $(C_OBJS) $(C_WO_PED_OBJS)	
endif

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning RRC$(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/libnh.a $(C_OBJS) $(C_WO_PED_OBJS)

