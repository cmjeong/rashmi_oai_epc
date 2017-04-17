#-------------------------------------------------------------#
#Makefile for product TF - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCysFLAGS=-DTF -DYS -DDEBUG -DYS_LTE_PAL -DLCCTF -DLCYSUITFU -DLCTFU \
          -DLCTFUITFU -DTFU_VER_2 -UTFU_TDD -DRG -DLCYSUICTF 


# Product sources-------------------------------------------------------
ysSRCS= \
    $(IN_DIR)/ys_pal_li.c \
    $(IN_DIR)/ys_pal_ui.c \
    $(IN_DIR)/ys_pal_ptui.c \
    $(IN_DIR)/ys_pal_msg.c \
    $(IN_DIR)/ys_pal_tmr.c \
    $(IN_DIR)/ys_pal_ex_ms.c \
    $(IN_DIR)/ys_pal_init.c \
    $(IN_DIR)/ys_pal_utl.c


# Product objects-------------------------------------------------------
ysOBJS= \
    $(OUT_DIR)/ys_pal_li.$(OBJ) \
    $(OUT_DIR)/ys_pal_ui.$(OBJ) \
    $(OUT_DIR)/ys_pal_ptui.$(OBJ) \
    $(OUT_DIR)/ys_pal_msg.$(OBJ) \
    $(OUT_DIR)/ys_pal_tmr.$(OBJ) \
    $(OUT_DIR)/ys_pal_ex_ms.$(OBJ) \
    $(OUT_DIR)/ys_pal_init.$(OBJ) \
    $(OUT_DIR)/ys_pal_utl.$(OBJ)

YSCM_INC=$(IN_DIR)/ys_pal.h $(IN_DIR)/ys_pal.x

ALL_INC=$(YSCM_INC) $(CM_INC)
   
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

$(OUT_DIR)/ys_pal_li.$(OBJ): $(IN_DIR)/ys_pal_li.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ys_pal_li.c -o \
	$(OUT_DIR)/ys_pal_li.$(OBJ)

$(OUT_DIR)/ys_pal_ui.$(OBJ): $(IN_DIR)/ys_pal_ui.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ys_pal_ui.c -o \
	$(OUT_DIR)/ys_pal_ui.$(OBJ)

$(OUT_DIR)/ys_pal_ptui.$(OBJ): $(IN_DIR)/ys_pal_ptui.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ys_pal_ptui.c -o \
	$(OUT_DIR)/ys_pal_ptui.$(OBJ)

$(OUT_DIR)/ys_pal_msg.$(OBJ): $(IN_DIR)/ys_pal_msg.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ys_pal_msg.c -o \
	$(OUT_DIR)/ys_pal_msg.$(OBJ)

$(OUT_DIR)/ys_pal_tmr.$(OBJ): $(IN_DIR)/ys_pal_tmr.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ys_pal_tmr.c -o \
	$(OUT_DIR)/ys_pal_tmr.$(OBJ)

$(OUT_DIR)/ys_pal_ex_ms.$(OBJ): $(IN_DIR)/ys_pal_ex_ms.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ys_pal_ex_ms.c -o \
	$(OUT_DIR)/ys_pal_ex_ms.$(OBJ)

$(OUT_DIR)/ys_pal_init.$(OBJ): $(IN_DIR)/ys_pal_init.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ys_pal_init.c -o \
	$(OUT_DIR)/ys_pal_init.$(OBJ)

$(OUT_DIR)/ys_pal_utl.$(OBJ): $(IN_DIR)/ys_pal_utl.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ys_pal_utl.c -o \
	$(OUT_DIR)/ys_pal_utl.$(OBJ)

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(OUT_DIR)/liblnxys.a:$(ysOBJS)
	ar -cr $(OUT_DIR)/libtf.a $(ysOBJS) 

$(OUT_DIR)/libcavys.a:$(ysOBJS)
	ar -cr $(OUT_DIR)/libtf.a $(ysOBJS) 

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f $(OUT_DIR)/libtf.a $(tfOBJS)

