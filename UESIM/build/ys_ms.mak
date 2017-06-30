#-------------------------------------------------------------#
#Makefile for product TF - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCysFLAGS=-DTF -DYS -DDEBUG -UYS_LTE_PAL -DYS_MSPD -DLCCTF -DLCYSUITFU \
			 -DLCTFU -DLCTFUITFU -DTFU_VER_2 -UTFU_TDD -DRG -DLCYSUICTF \
			 -DYS_MSPD

# Product sources-------------------------------------------------------
ysSRCS= \
    $(IN_DIR)/ys_ms_ue_cl.c \
    $(IN_DIR)/ys_ms_ue_cl_pal.c \
    $(IN_DIR)/ys_ms_ue_cl_stub.c \
    $(IN_DIR)/ys_ms_ue_cl_utl.c 


# Product objects-------------------------------------------------------
ysOBJS= \
    $(OUT_DIR)/ys_ms_ue_cl.$(OBJ) \
    $(OUT_DIR)/ys_ms_ue_cl_pal.$(OBJ) \
    $(OUT_DIR)/ys_ms_ue_cl_stub.$(OBJ) \
    $(OUT_DIR)/ys_ms_ue_cl_utl.$(OBJ) 

#YSCM_INC=$(IN_DIR)/ys.h $(IN_DIR)/ys.x
UE_INC = ../lteue/
#ALL_INC=$(YSCM_INC) $(CM_INC)
ALL_INC=$(UE_INC) $(CM_INC)
   
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

$(OUT_DIR)/ys_ms_ue_cl.$(OBJ): $(IN_DIR)/ys_ms_ue_cl.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ys_ms_ue_cl.c -o \
	$(OUT_DIR)/ys_ms_ue_cl.$(OBJ)

$(OUT_DIR)/ys_ms_ue_cl_pal.$(OBJ): $(IN_DIR)/ys_ms_ue_cl_pal.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ys_ms_ue_cl_pal.c -o \
	$(OUT_DIR)/ys_ms_ue_cl_pal.$(OBJ)

$(OUT_DIR)/ys_ms_ue_cl_stub.$(OBJ): $(IN_DIR)/ys_ms_ue_cl_stub.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ys_ms_ue_cl_stub.c -o \
	$(OUT_DIR)/ys_ms_ue_cl_stub.$(OBJ)

$(OUT_DIR)/ys_ms_ue_cl_utl.$(OBJ): $(IN_DIR)/ys_ms_ue_cl_utl.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ys_ms_ue_cl_utl.c -o \
	$(OUT_DIR)/ys_ms_ue_cl_utl.$(OBJ)


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

