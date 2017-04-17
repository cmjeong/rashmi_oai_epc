#-------------------------------------------------------------#
#Makefile for product cm - script generated.
#Only the $(CCcmFLAGS) may be modified.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCcmFLAGS=-D_GNU_SOURCE
#<---Insert cm specific defines here

#-------------------------------------------------------------#
#File/Obj macros             
#-------------------------------------------------------------#

cmOBJS= \
	$(OUT_DIR)/cm_bdy5.$(OBJ)\
	$(OUT_DIR)/cm_mem.$(OBJ)\
	$(OUT_DIR)/cm_gen.$(OBJ)\
	$(OUT_DIR)/cm_tkns.$(OBJ)\
	$(OUT_DIR)/cm_lib.$(OBJ)\
	$(OUT_DIR)/cm_hash.$(OBJ)\
	$(OUT_DIR)/cm_mblk.$(OBJ)\
	$(OUT_DIR)/cm_llist.$(OBJ)\
	$(OUT_DIR)/cm_lte.$(OBJ)\
	$(OUT_DIR)/cm_pasn1.$(OBJ)\
	$(OUT_DIR)/cm_pasn2.$(OBJ)\
	$(OUT_DIR)/cm_pasn3.$(OBJ)\
	$(OUT_DIR)/cm_pasn4.$(OBJ)\
        $(OUT_DIR)/cm_emm_edm.$(OBJ)\
        $(OUT_DIR)/cm_esm_edm.$(OBJ)\
        $(OUT_DIR)/cm_emm_esm.$(OBJ)\
        $(OUT_DIR)/cm_os.$(OBJ)\
        $(OUT_DIR)/cm_inet.$(OBJ)\
	$(OUT_DIR)/tfu.$(OBJ)

TFUOPTS=-UTFU_TDD -DTFU_VER_2 -DLCTFU -DLTEMAC_SPS

CM_INC=$(IN_DIR)/cm_emm.h $(IN_DIR)/cm_emm.x  \
       $(IN_DIR)/cm_esm.h $(IN_DIR)/cm_esm.x

#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#
$(OUT_DIR)/cm_bdy5.$(OBJ): $(IN_DIR)/cm_bdy5.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_bdy5.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_bdy5.c
$(OUT_DIR)/cm_mem.$(OBJ): $(IN_DIR)/cm_mem.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/cm_mem.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_mem.c
$(OUT_DIR)/cm_gen.$(OBJ): $(IN_DIR)/cm_gen.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_gen.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_gen.c
$(OUT_DIR)/cm_tkns.$(OBJ): $(IN_DIR)/cm_tkns.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_tkns.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_tkns.c
$(OUT_DIR)/cm_lib.$(OBJ): $(IN_DIR)/cm_lib.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_lib.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_lib.c
$(OUT_DIR)/cm_hash.$(OBJ): $(IN_DIR)/cm_hash.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_hash.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_hash.c
$(OUT_DIR)/cm_mblk.$(OBJ): $(IN_DIR)/cm_mblk.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_mblk.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_mblk.c
$(OUT_DIR)/cm_llist.$(OBJ): $(IN_DIR)/cm_llist.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_llist.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_llist.c
$(OUT_DIR)/cm_lte.$(OBJ): $(IN_DIR)/cm_lte.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_lte.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_lte.c
$(OUT_DIR)/cm_pasn1.$(OBJ): $(IN_DIR)/cm_pasn1.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_pasn1.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_pasn1.c
$(OUT_DIR)/cm_pasn2.$(OBJ): $(IN_DIR)/cm_pasn2.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_pasn2.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_pasn2.c
$(OUT_DIR)/cm_pasn3.$(OBJ): $(IN_DIR)/cm_pasn3.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_pasn3.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_pasn3.c
$(OUT_DIR)/cm_pasn4.$(OBJ): $(IN_DIR)/cm_pasn4.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_pasn4.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_pasn4.c
$(OUT_DIR)/cm_os.$(OBJ): $(IN_DIR)/cm_os.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_os.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_os.c
$(OUT_DIR)/cm_inet.$(OBJ): $(IN_DIR)/cm_inet.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/cm_inet.o $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_inet.c
$(OUT_DIR)/cm_emm_edm.$(OBJ): $(IN_DIR)/cm_emm_edm.c $(CM_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_emm_edm.c -o \
	$(OUT_DIR)/cm_emm_edm.$(OBJ)

$(OUT_DIR)/cm_esm_edm.$(OBJ): $(IN_DIR)/cm_esm_edm.c $(CM_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_esm_edm.c -o \
	$(OUT_DIR)/cm_esm_edm.$(OBJ)

$(OUT_DIR)/cm_emm_esm.$(OBJ): $(IN_DIR)/cm_emm_esm.c $(CM_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCcmFLAGS) $(IN_DIR)/cm_emm_esm.c -o \
	$(OUT_DIR)/cm_emm_esm.$(OBJ)

$(OUT_DIR)/tfu.$(OBJ): $(IN_DIR)/tfu.c $(CM_INC)
	$(CC) -c  -o $(OUT_DIR)/tfu.o $(COPTS) $(IOPTS) $(POPTS) $(TFUOPTS) $(CCcmFLAGS) $(IN_DIR)/tfu.c

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(OUT_DIR)/libcm.a:$(cmOBJS)
	ar -cr libcm.a $(cmOBJS)	
#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f $(OUT_DIR)/libcm.a $(cmOBJS)

