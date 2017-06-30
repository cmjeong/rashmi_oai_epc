#-------------------------------------------------------------#
#Makefile for product TF - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCueFLAGS=-DTF -DLCCTF -DLCTFUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 \
          -UTFU_TDD -DRG 

# Product sources-------------------------------------------------------
uePERFSRCS= \
    $(IN_DIR)/ue_main.c  \
    $(IN_DIR)/ue_mac.c \
    $(IN_DIR)/ue_rrc.c \
    $(IN_DIR)/ue_pal.c \
    $(IN_DIR)/ue_utl.c \
    $(IN_DIR)/ue_rlc.c  \
    $(IN_DIR)/ue_emm.c   \
    $(IN_DIR)/ue_uim.c   \
    $(IN_DIR)/ue_esm.c   \
    $(IN_DIR)/ue_app_utl.c   \
    $(IN_DIR)/ue_data_app_cav.c   \
    $(IN_DIR)/ue_app_li.c   \
    $(IN_DIR)/ue_appperf_li.c   \
    $(IN_DIR)/ue_app.c   \
    $(IN_DIR)/ue_nh_db.c


# Product objects-------------------------------------------------------
uePERFOBJS= \
    $(OUT_DIR)/ue_main.$(OBJ) \
    $(OUT_DIR)/ue_mac.$(OBJ) \
    $(OUT_DIR)/ue_rrc.$(OBJ) \
    $(OUT_DIR)/ue_pal.$(OBJ) \
    $(OUT_DIR)/ue_utl.$(OBJ) \
    $(OUT_DIR)/ue_rlc.$(OBJ) \
    $(OUT_DIR)/ue_emm.$(OBJ)   \
    $(OUT_DIR)/ue_uim.$(OBJ)   \
    $(OUT_DIR)/ue_esm.$(OBJ)   \
    $(OUT_DIR)/ue_app_utl.$(OBJ)   \
    $(OUT_DIR)/ue_data_app_cav.$(OBJ)   \
    $(OUT_DIR)/ue_app_li.$(OBJ)   \
    $(OUT_DIR)/ue_appperf_li.$(OBJ)   \
    $(OUT_DIR)/ue_app.$(OBJ)   \
    $(OUT_DIR)/ue_nh_db.$(OBJ)


# Product sources-------------------------------------------------------
ueE2ESRCS= \
    $(IN_DIR)/ue_main.c  \
    $(IN_DIR)/ue_mac.c \
    $(IN_DIR)/ue_rrc.c \
    $(IN_DIR)/ue_pal.c \
    $(IN_DIR)/ue_utl.c \
    $(IN_DIR)/ue_rlc.c  \
    $(IN_DIR)/ue_emm.c   \
    $(IN_DIR)/ue_uim.c   \
    $(IN_DIR)/ue_esm.c   \
    $(IN_DIR)/ue_app_utl.c   \
    $(IN_DIR)/ue_data_app_cav.c   \
    $(IN_DIR)/ue_app_li.c   \
    $(IN_DIR)/ue_app.c   \
    $(IN_DIR)/ue_nh_db.c


# Product objects-------------------------------------------------------
ueE2EOBJS= \
    $(OUT_DIR)/ue_main.$(OBJ) \
    $(OUT_DIR)/ue_mac.$(OBJ) \
    $(OUT_DIR)/ue_rrc.$(OBJ) \
    $(OUT_DIR)/ue_pal.$(OBJ) \
    $(OUT_DIR)/ue_utl.$(OBJ) \
    $(OUT_DIR)/ue_rlc.$(OBJ) \
    $(OUT_DIR)/ue_emm.$(OBJ)   \
    $(OUT_DIR)/ue_uim.$(OBJ)   \
    $(OUT_DIR)/ue_esm.$(OBJ)   \
    $(OUT_DIR)/ue_app_utl.$(OBJ)   \
    $(OUT_DIR)/ue_data_app_cav.$(OBJ)   \
    $(OUT_DIR)/ue_app_li.$(OBJ)   \
    $(OUT_DIR)/ue_app.$(OBJ)   \
    $(OUT_DIR)/ue_nh_db.$(OBJ)


CM_DIR=../cm
MT_DIR=../mt
ALL_INC=$(UECM_INC) $(CM_DIR)
   
UECM_INC=$(IN_DIR)/ue.h $(IN_DIR)/ue.x $(CM_DIR)/nhu_asn.x \
         $(CM_DIR)/cm_emm.h $(CM_DIR)/cm_emm.x  \
         $(CM_DIR)/cm_esm.h $(CM_DIR)/cm_esm.x  \
         $(CM_DIR)/nhu_asn.h $(IN_DIR)/ue_nh_db.x \
         $(CM_DIR)/nhu.h $(CM_DIR)/nhu.x
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

$(OUT_DIR)/ue_main.$(OBJ): $(IN_DIR)/ue_main.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_main.c -o \
	$(OUT_DIR)/ue_main.$(OBJ)

$(OUT_DIR)/ue_mac.$(OBJ): $(IN_DIR)/ue_mac.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_mac.c -o \
	$(OUT_DIR)/ue_mac.$(OBJ)

$(OUT_DIR)/ue_rrc.$(OBJ): $(IN_DIR)/ue_rrc.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_rrc.c -o \
	$(OUT_DIR)/ue_rrc.$(OBJ)

$(OUT_DIR)/ue_pal.$(OBJ): $(IN_DIR)/ue_pal.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_pal.c -o \
	$(OUT_DIR)/ue_pal.$(OBJ)

$(OUT_DIR)/ue_rb.$(OBJ): $(IN_DIR)/ue_rb.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_rb.c -o \
	$(OUT_DIR)/ue_rb.$(OBJ)

$(OUT_DIR)/ue_utl.$(OBJ): $(IN_DIR)/ue_utl.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_utl.c -o \
	$(OUT_DIR)/ue_utl.$(OBJ)

$(OUT_DIR)/ue_rlc.$(OBJ): $(IN_DIR)/ue_rlc.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_rlc.c -o \
	$(OUT_DIR)/ue_rlc.$(OBJ)

$(OUT_DIR)/ue_emm.$(OBJ): $(IN_DIR)/ue_emm.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_emm.c -o \
	$(OUT_DIR)/ue_emm.$(OBJ)

$(OUT_DIR)/ue_uim.$(OBJ): $(IN_DIR)/ue_uim.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_uim.c -o \
	$(OUT_DIR)/ue_uim.$(OBJ)

$(OUT_DIR)/ue_esm.$(OBJ): $(IN_DIR)/ue_esm.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_esm.c -o \
	$(OUT_DIR)/ue_esm.$(OBJ)

$(OUT_DIR)/ue_app_utl.$(OBJ): $(IN_DIR)/ue_app_utl.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_app_utl.c -o \
	$(OUT_DIR)/ue_app_utl.$(OBJ)

$(OUT_DIR)/ue_data_app_cav.$(OBJ): $(IN_DIR)/ue_data_app_cav.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_data_app_cav.c -o \
	$(OUT_DIR)/ue_data_app_cav.$(OBJ)

$(OUT_DIR)/ue_app_li.$(OBJ): $(IN_DIR)/ue_app_li.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_app_li.c -o \
	$(OUT_DIR)/ue_app_li.$(OBJ)

$(OUT_DIR)/ue_appperf_li.$(OBJ): $(IN_DIR)/ue_appperf_li.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_appperf_li.c -o \
	$(OUT_DIR)/ue_appperf_li.$(OBJ)

$(OUT_DIR)/ue_app.$(OBJ): $(IN_DIR)/ue_app.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_app.c -o \
	$(OUT_DIR)/ue_app.$(OBJ)

$(OUT_DIR)/ue_nh_db.$(OBJ): $(IN_DIR)/ue_nh_db.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_nh_db.c -o \
	$(OUT_DIR)/ue_nh_db.$(OBJ)

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(OUT_DIR)/libperfue.a:$(uePERFOBJS)
	ar -cr libue.a $(uePERFOBJS) 

$(OUT_DIR)/libe2eue.a:$(ueE2EOBJS)
	ar -cr libue.a $(ueE2EOBJS) 
#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f $(OUT_DIR)/libue.a $(ueOBJS)

