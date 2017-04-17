#
##-------------------------------------------------------------#
#Makefile for product mt - script generated.
#Only the $(CCmtFLAGS) may be modified.
#-------------------------------------------------------------#
include ../common/rsys_fancy.mak
include ../common/env.mak

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCmtFLAGS=-UBIT_64 -DSS_MT_TMR -USS_LOGGER_SUPPORT -DEGTP_U#<---Insert mt specific defines here

#-------------------------------------------------------------#
#File/Obj macros             
#-------------------------------------------------------------#
SRC_DIR=$(ROOT_DIR)/src/mt/security
PHYPATH=$(ROOT_DIR)/src/ltephybrcm/L1_SRC_Files/LTE_L1_1.16.5

C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
I_OPTS=$(PLTFRM_INCLUDES)

C_OPTS=-g -O3 -pipe -pedantic -W -Wno-comment -Wshadow -Wcast-qual \
    -fno-strict-aliasing -fsigned-char --std=c99 -march=mips32r2 \
    -mtune=mips32r2 -mips32r2

lib:$(LIB_DIR)/libmtsec.a
$(C_OBJS) : $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(C_OPTS) $(I_OPTS) -c -o $@ $<

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(LIB_DIR)/libmtsec.a:$(C_OBJS)
	$(Q)ar -cr $(LIB_DIR)/libmtsec.a $(C_OBJS)	

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo -e "$(COLOR_RED)Cleaning CPUH security algorithms$(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/libmtsec.a $(C_OBJS)


