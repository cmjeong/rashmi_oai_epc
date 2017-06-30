#-------------------------------------------------------------#
#Makefile for product TF - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#
ifeq ($(BLDENV),lnx_perf_msstub_acc)
CCueFLAGS=-DTF -DLCCTF -DLCTFUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 \
          -UTFU_TDD -DRG -UYS_LTE_PAL -DYS_MSPD -DYS_MSPD_OSAL -DLTEMAC_SPS
else
ifeq ($(BLDENV),lnx_e2e_msstub_acc)
CCueFLAGS=-DTF -DLCCTF -DLCTFUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 \
          -UTFU_TDD -DRG -UYS_LTE_PAL -DYS_MSPD -DYS_MSPD_OSAL -DLTEMAC_SPS
else
ifeq ($(BLDENV),lnx_e2e_acc)
CCueFLAGS=-DTF -DLCCTF -DLCTFUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 \
          -UTFU_TDD -DRG -DYS_LTE_PAL -DLTEMAC_SPS 
else
CCueFLAGS=-DTF -DLCCTF -DLCTFUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 \
          -UTFU_TDD -DRG -DYS_LTE_PAL -DLTEMAC_SPS 
endif
endif
endif


# Product sources-------------------------------------------------------
uePERFSRCS= \
    $(IN_DIR)/ue_mac.c \
    $(IN_DIR)/ue_rrc.c \
    $(IN_DIR)/ue_pal.c \
    $(IN_DIR)/ue_utl.c \
    $(IN_DIR)/ue_rlc.c  \
    $(IN_DIR)/ue_emm.c   \
    $(IN_DIR)/ue_uim.c   \
    $(IN_DIR)/ue_esm.c   \
    $(IN_DIR)/ue_app_utl.c   \
    $(IN_DIR)/ue_appperf_li.c   \
    $(IN_DIR)/ue_app_li.c   \
    $(IN_DIR)/ue_app.c   \
    $(IN_DIR)/ue_data_app.c   \
    $(IN_DIR)/ue_nh_db.c


# Product objects-------------------------------------------------------
uePERFOBJS= \
    $(OUT_DIR)/ue_mac.$(OBJ) \
    $(OUT_DIR)/ue_rrc.$(OBJ) \
    $(OUT_DIR)/ue_pal.$(OBJ) \
    $(OUT_DIR)/ue_utl.$(OBJ) \
    $(OUT_DIR)/ue_rlc.$(OBJ) \
    $(OUT_DIR)/ue_emm.$(OBJ)   \
    $(OUT_DIR)/ue_uim.$(OBJ)   \
    $(OUT_DIR)/ue_esm.$(OBJ)   \
    $(OUT_DIR)/ue_app_utl.$(OBJ)   \
    $(OUT_DIR)/ue_app_li.$(OBJ)   \
    $(OUT_DIR)/ue_app.$(OBJ)   \
    $(OUT_DIR)/ue_appperf_li.$(OBJ)   \
    $(OUT_DIR)/ue_data_app.$(OBJ)   \
    $(OUT_DIR)/ue_nh_db.$(OBJ)


ueE2ESRCS= \
    $(IN_DIR)/ue_mac.c \
    $(IN_DIR)/ue_rrc.c \
    $(IN_DIR)/ue_pal.c \
    $(IN_DIR)/ue_utl.c \
    $(IN_DIR)/ue_rlc.c  \
    $(IN_DIR)/ue_emm.c   \
    $(IN_DIR)/ue_uim.c   \
    $(IN_DIR)/ue_esm.c   \
    $(IN_DIR)/ue_app_utl.c   \
    $(IN_DIR)/ue_app_li.c   \
    $(IN_DIR)/ue_app.c   \
    $(IN_DIR)/ue_data_app.c   \
    $(IN_DIR)/ue_nh_db.c


# Product objects-------------------------------------------------------
ueE2EOBJS= \
    $(OUT_DIR)/ue_mac.$(OBJ) \
    $(OUT_DIR)/ue_rrc.$(OBJ) \
    $(OUT_DIR)/ue_pal.$(OBJ) \
    $(OUT_DIR)/ue_utl.$(OBJ) \
    $(OUT_DIR)/ue_rlc.$(OBJ) \
    $(OUT_DIR)/ue_emm.$(OBJ)   \
    $(OUT_DIR)/ue_uim.$(OBJ)   \
    $(OUT_DIR)/ue_esm.$(OBJ)   \
    $(OUT_DIR)/ue_app_utl.$(OBJ)   \
    $(OUT_DIR)/ue_app_li.$(OBJ)   \
    $(OUT_DIR)/ue_app.$(OBJ)   \
    $(OUT_DIR)/ue_data_app.$(OBJ)   \
    $(OUT_DIR)/ue_nh_db.$(OBJ)   

ueE2EPERFSRCS= \
    $(IN_DIR)/ue_mac.c \
    $(IN_DIR)/ue_rrc.c \
    $(IN_DIR)/ue_pal.c \
    $(IN_DIR)/ue_utl.c \
    $(IN_DIR)/ue_rlc.c  \
    $(IN_DIR)/ue_emm.c   \
    $(IN_DIR)/ue_uim.c   \
    $(IN_DIR)/ue_esm.c   \
    $(IN_DIR)/ue_app_utl.c   \
    $(IN_DIR)/ue_app_e2eperf_li.c   \
    $(IN_DIR)/ue_app.c   \
    $(IN_DIR)/ue_nh_db.c

# Product objects-------------------------------------------------------
ueE2EPERFOBJS= \
    $(OUT_DIR)/ue_mac.$(OBJ) \
    $(OUT_DIR)/ue_rrc.$(OBJ) \
    $(OUT_DIR)/ue_pal.$(OBJ) \
    $(OUT_DIR)/ue_utl.$(OBJ) \
    $(OUT_DIR)/ue_rlc.$(OBJ) \
    $(OUT_DIR)/ue_emm.$(OBJ)   \
    $(OUT_DIR)/ue_uim.$(OBJ)   \
    $(OUT_DIR)/ue_esm.$(OBJ)   \
    $(OUT_DIR)/ue_app_utl.$(OBJ)   \
    $(OUT_DIR)/ue_app.$(OBJ)   \
    $(OUT_DIR)/ue_app_e2eperf_li.$(OBJ)   \
    $(OUT_DIR)/ue_nh_db.$(OBJ)

PHY_DIR= ../ltephy/mindspeed


UE_INC=$(IN_DIR)/ue.h $(IN_DIR)/ue.x  $(IN_DIR)/ue_nh_db.x

ifeq ($(BLDENV),lnx_perf_msstub_acc)
UE_INC += $(PHY_DIR)/LtePhyL2Api.h $(PHY_DIR)/apidefs.h $(PHY_DIR)/ctrlmsg.h $(PHY_DIR)/maciface.h

else
ifeq ($(BLDENV),lnx_e2e_msstub_acc)
UE_INC += $(PHY_DIR)/LtePhyL2Api.h $(PHY_DIR)/apidefs.h $(PHY_DIR)/ctrlmsg.h $(PHY_DIR)/maciface.h

endif
endif

ALL_INC=$(UE_INC) $(CM_INC)
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

$(OUT_DIR)/ue_mac.$(OBJ): $(IN_DIR)/ue_mac.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_mac.c -o \
	$(OUT_DIR)/ue_mac.$(OBJ)

$(OUT_DIR)/ue_rrc.$(OBJ): $(IN_DIR)/ue_rrc.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_rrc.c -o \
	$(OUT_DIR)/ue_rrc.$(OBJ)

$(OUT_DIR)/ue_pal.$(OBJ): $(IN_DIR)/ue_pal.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_pal.c -o \
	$(OUT_DIR)/ue_pal.$(OBJ)

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

$(OUT_DIR)/ue_app_li.$(OBJ): $(IN_DIR)/ue_app_li.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_app_li.c -o \
	$(OUT_DIR)/ue_app_li.$(OBJ)

$(OUT_DIR)/ue_appperf_li.$(OBJ): $(IN_DIR)/ue_appperf_li.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_appperf_li.c -o \
	$(OUT_DIR)/ue_appperf_li.$(OBJ)

$(OUT_DIR)/ue_app_e2eperf_li.$(OBJ): $(IN_DIR)/ue_app_e2eperf_li.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_app_e2eperf_li.c -o \
	$(OUT_DIR)/ue_app_e2eperf_li.$(OBJ)

$(OUT_DIR)/ue_app.$(OBJ): $(IN_DIR)/ue_app.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_app.c -o \
	$(OUT_DIR)/ue_app.$(OBJ)

$(OUT_DIR)/ue_data_app.$(OBJ): $(IN_DIR)/ue_data_app.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/ue_data_app.c -o \
	$(OUT_DIR)/ue_data_app.$(OBJ)
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

$(OUT_DIR)/libe2eperfue.a:$(ueE2EPERFOBJS)
	ar -cr libue.a $(ueE2EPERFOBJS) 
#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f $(OUT_DIR)/libue.a $(ueOBJS)

