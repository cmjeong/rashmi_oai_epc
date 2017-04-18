#
#
##--------------------------------------------------------------#
##Makefile for product WR
##--------------------------------------------------------------#
include ../common/rsys_fancy.mak
COLOR=$(COLOR_RED)

SRC_DIR=$(ROOT_DIR)/src/enbapp/

C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_SRCS:=$(filter-out %pal.c, $(C_SRCS))
C_SRCS:=$(filter-out %intel.c, $(C_SRCS))
C_SRCS:=$(filter-out %t2k.h, $(C_SRCS))
C_SRCS:=$(filter-out %t2k.c, $(C_SRCS))
C_SRCS:=$(filter-out %t3k.h, $(C_SRCS))
C_SRCS:=$(filter-out %t3k.c, $(C_SRCS))
C_SRCS:=$(filter-out %t33.h, $(C_SRCS))
C_SRCS:=$(filter-out %t33.c, $(C_SRCS))
C_SRCS:=$(filter-out %brcm.h, $(C_SRCS))
C_SRCS:=$(filter-out %brcm.c, $(C_SRCS))
C_SRCS:=$(filter-out %wr_mi.c, $(C_SRCS))
C_SRCS:=$(filter-out %wr_smm_enbapp.c, $(C_SRCS))
#TODO: enbapp_utils may be needed without OAM 
#TODO: Need to decide on the lower file
C_SRCS:=$(filter-out %wr_smm_init_merged.c, $(C_SRCS))
C_SRCS:=$(filter-out %wr_umm_lclctxtrel.c, $(C_SRCS))
C_SRCS:=$(filter-out %wr_umm_sec.c, $(C_SRCS))
C_SRCS:=$(filter-out %wr_umm_uecap.c, $(C_SRCS))
C_SRCS:=$(filter-out %t2200_tdd.c, $(C_SRCS))
C_SRCS:=$(filter-out %t3300_tdd.c, $(C_SRCS))
C_SRCS:=$(filter-out %t2200_fdd.c, $(C_SRCS))
C_SRCS:=$(filter-out %t3300_fdd.c, $(C_SRCS))
C_SRCS:=$(filter-out %watchdog_tmr.c, $(C_SRCS))
C_SRCS:=$(filter-out %wr_nmm_intel.c, $(C_SRCS))
C_SRCS:=$(filter-out %wr_nmm.c, $(C_SRCS))
C_SRCS:=$(filter-out %sw_version_brcm_fdd.c, $(C_SRCS))
C_SRCS:=$(filter-out %sw_version_brcm_tdd.c, $(C_SRCS))
C_SRCS:=$(filter-out %sw_version_pal_fdd.c, $(C_SRCS))
C_SRCS:=$(filter-out %wr_smm_enbapp_utils.c, $(C_SRCS))
C_SRCS:=$(filter-out %wr_smm_enbapp_cmnplatutils.c, $(C_SRCS))
C_SRCS:=$(filter-out %wr_utils.c, $(C_SRCS))
C_SRCS:=$(filter-out %tenb_stats.c, $(C_SRCS))

C_SRCS_WO_PEDANTIC = $(SRC_DIR)/wr_smm_watchdog_tmr.c
ifneq ($(PLTFRM),PAL)
C_SRCS_WO_PEDANTIC += $(SRC_DIR)/wr_nmm.c
endif

ifneq ($(CNM_ENABLE), YES)
C_SRCS:=$(filter-out %wr_cnm.c, $(C_SRCS))
endif

ifeq ($(PLTFRM),PAL)
#C_SRCS:=$(filter-out %smm_cl.c, $(C_SRCS))
endif

ifeq ($(OAM_ENABLE), YES)
ifeq ($(TIP),YES)
ifneq ($(TIP_L3),YES)
C_SRCS:=$(filter-out %wr_smm_dyncfg.c, $(C_SRCS))
endif
endif
#C_SRCS:=$(filter-out %wr_smm_enbapp_utils.c, $(C_SRCS))
else
C_SRCS:=$(filter-out %wr_smm_dyncfg.c, $(C_SRCS))
#C_SRCS:=$(filter-out %wr_smm_enbapp_cmnplatutils.c, $(C_SRCS))
endif
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
LOG_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i,$(C_SRCS))
DB_FILES =$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.i.db,$(C_SRCS))

C_WO_PED_OBJS=$(OBJ_DIR)/wr_smm_watchdog_tmr.o 
LOG_FILES+= $(OBJ_DIR)/wr_smm_watchdog_tmr.i
DB_FILES += $(OBJ_DIR)/wr_smm_watchdog_tmr.i.db
DB_FILES += $(OBJ_DIR)/wr_tenb_stats.i.db
C_WO_PED_OBJS += $(OBJ_DIR)/wr_tenb_stats.o
LOG_FILES+= $(OBJ_DIR)/wr_tenb_stats.i

ifneq ($(PLTFRM),PAL)
DB_FILES += $(OBJ_DIR)/wr_nmm.i.db
C_WO_PED_OBJS += $(OBJ_DIR)/wr_nmm.o
LOG_FILES+= $(OBJ_DIR)/wr_nmm.i
endif

C_WO_PED_OBJS+=$(OBJ_DIR)/wr_utils.o 
LOG_FILES+= $(OBJ_DIR)/wr_utils.i
DB_FILES += $(OBJ_DIR)/wr_utils.i.db

# prepare the list of common header files
HDR_FILES+=$(wildcard $(CM_DIR)/env*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/gen*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/ssi*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/cm*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lnh*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lpj*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lkw*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lrg*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lys*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lhi*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lsb*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/leg*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lsz*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/lxz*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/nhu*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/szt*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/czt*.[hx])
HDR_FILES+=$(wildcard $(CM_DIR)/egt*.[hx])

lib:$(LIB_DIR)/libwr.a
include $(COM_BUILD_DIR)/compile.mak

#TODO: Clean up usage of x2ap files from application
I_OPTS += -I$(ROOT_DIR)/src/x2ap
##--------------------------------------------------------------#
##User macros (to be modified)
#--------------------------------------------------------------#
#-DLWLCSMRMMILRM -UTCSMRMMILRM -DLCSMRMMILRM -DPTSMMILRM
RrmFlags=-DRMU_LWLC -DRM_NPLC  -LRM_NPLC

#SonFlags=-DNLU_LWLC -DNLU_TC -DLWLCSMSONILNL -DTCSMSONILNL -DLCSMSONILNL

CCwrFLAGS=-DWR_RELAY -DEU_DAT_APP -DEGTP_U -DTFU_WRR_2 -DDG -DVALIDATION_CHK \
    -DWR_TEST_CODE -DWR_TEST_CLI -UMME_LDBAL -DDEBUGP  $(RrmFlags)\

ifeq ($(OAM_ENABLE),YES)
ifneq ($(TIP),YES)
CCwrFLAGS+= -DWR_RSYS_OAM -DREM_ENABLE
else
ifeq ($(TIP_L3),YES)
CCwrFLAGS+= -DWR_RSYS_OAM -DREM_ENABLE
endif 
ifeq ($(TIP_UPPER_L2),YES)
CCwrFLAGS+= -UWR_RSYS_OAM -UREM_ENABLE
endif 
ifeq ($(TIP_LOWER_L2),YES)
CCwrFLAGS+= -UWR_RSYS_OAM -UREM_ENABLE
endif 
endif 
endif 

MOD_FLAGS=-DWR $(CCwrFLAGS) $(SonFlags)

ifeq ($(TIP_L3),YES)
MOD_FLAGS+=-DENB_OVRLOAD -DSZ -DSB -DNH -DWR_DAM_LC
else
ifeq ($(TIP_UPPER_L2),YES)
MOD_FLAGS+=-DENB_OVRLOAD -DSZ -DSB -DNH -DWR_DAM_LC
else
MOD_FLAGS+=-DENB_OVRLOAD -DSZ -DSB -DNH -UWR_DAM_LC
endif
endif

ifneq ($(PLTFRM),BRDCM)
MOD_FLAGS+=-DPJ
endif

I_OPTS+=-I$(ROOT_DIR)/src/mt

# Product sources-------------------------------------------------------
#wrPerfLnxSRCSUU= \
    $(IN_DIR)/ \
    $(IN_DIR)/

#wrE2eLnxSRCS= \
#    $(IN_DIR)/wr_emm_eom.$(SRC) \
#    $(IN_DIR)/wr_umm_meas.$(SRC) \
#    $(IN_DIR)/wr_lmm.$(SRC) \
#    $(IN_DIR)/wr_emm_neighenb.$(SRC) \
#    $(IN_DIR)/wr_emm_cfg.$(SRC) \
#    $(IN_DIR)/wr_emm_csg.$(SRC) \
#    $(IN_DIR)/wr_emm_ecsfb_cfg.$(SRC) \
#    $(IN_DIR)/wr_emm_rim_app.$(SRC) \
#    $(IN_DIR)/wr_emm_rim.$(SRC) \
#    $(IN_DIR)/wr_umm_rrccsfb.$(SRC) \
#    $(IN_DIR)/wr_umm_mobparms.$(SRC) \
#    $(IN_DIR)/wr_umm_ulnas.$(SRC) \
#    $(IN_DIR)/wr_umm_dlnas.$(SRC) \
#    $(IN_DIR)/wr_umm_rabsetup.$(SRC) \
#    $(IN_DIR)/wr_umm_ctxtrel.$(SRC) \
#    $(IN_DIR)/wr_umm_rabrel.$(SRC) \
#    $(IN_DIR)/wr_umm_rabmod.$(SRC) \
#    $(IN_DIR)/wr_umm_lcrabrel.$(SRC) \
#    $(IN_DIR)/wr_emm.$(SRC) \
#    $(IN_DIR)/wr_emm_pbm.$(SRC) \
#    $(IN_DIR)/wr_emm_pws.$(SRC) \
#    $(IN_DIR)/wr_emm_pbm_sib.$(SRC) \
#    $(IN_DIR)/wr_emm_ecsfb_utils.$(SRC) \
#    $(IN_DIR)/wr_umm_ecsfb_utils.$(SRC)\
#    $(IN_DIR)/wr_emm_cell.$(SRC) \
#    $(IN_DIR)/wr_emm_mme.$(SRC) \
#    $(IN_DIR)/wr_emm_mme_s1ap.$(SRC) \
#    $(IN_DIR)/wr_emm_plmn.$(SRC) \
#    $(IN_DIR)/wr_utils.$(SRC) \
#    $(IN_DIR)/wr_smm_smallcell.$(SRC) \
#    $(IN_DIR)/wr_smm_init.$(SRC) \
#    $(IN_DIR)/wr_smm_cfg.$(SRC) \
#    $(IN_DIR)/wr_smm_rrc.$(SRC) \
#    $(IN_DIR)/wr_smm_rlc.$(SRC) \
#    $(IN_DIR)/wr_smm_mac.$(SRC) \
#    $(IN_DIR)/wr_smm_s1ap.$(SRC) \
#    $(IN_DIR)/wr_smm_sctp.$(SRC) \
#    $(IN_DIR)/wr_smm_tucl.$(SRC) \
#    $(IN_DIR)/wr_smm_egtp.$(SRC) \
#    $(IN_DIR)/wr_smm_enbapp_rsys.$(SRC) \
#    $(IN_DIR)/wr_smm_rrm.$(SRC) \
#    $(IN_DIR)/wr_smm_watchdog_tmr.$(SRC) \
#    $(IN_DIR)/wr_smm_pdcp.$(SRC) \
#    $(IN_DIR)/wr_smm_cl.$(SRC) \
#    $(IN_DIR)/wr_smm_x2ap.$(SRC) \
#    $(IN_DIR)/wr_plat.$(SRC) \
#    $(IN_DIR)/wr_ifm_x2ap.$(SRC) \
#    $(IN_DIR)/wr_ifm_egtp.$(SRC) \
#    $(IN_DIR)/wr_ifm_rrc.$(SRC) \
#    $(IN_DIR)/wr_ifm_pdcp.$(SRC) \
#    $(IN_DIR)/wr_tenb_stats.$(SRC) \
#    $(IN_DIR)/wr_ifm_schd.$(SRC) \
#    $(IN_DIR)/wr_ifm_s1ap.$(SRC) \
#    $(IN_DIR)/wr_ifm_l1.$(SRC) \
#    $(IN_DIR)/wr_umm.$(SRC) \
#    $(IN_DIR)/wr_dam.$(SRC) \
#    $(IN_DIR)/wr_dam_ifm_app.$(SRC) \
#    $(IN_DIR)/wr_ifm_dam.$(SRC) \
#    $(IN_DIR)/wr_dam_ex_ms.$(SRC) \
#    $(IN_DIR)/wr_dam_tmr.$(SRC) \
#    $(IN_DIR)/wr_ifm_dam_utils.$(SRC) \
#    $(IN_DIR)/wr_umm_egtp_hdl.$(SRC) \
#    $(IN_DIR)/wr_umm_rrc_msg.$(SRC) \
#    $(IN_DIR)/wr_umm_sch_msg.$(SRC) \
#    $(IN_DIR)/wr_umm_s1ap_msg.$(SRC) \
#    $(IN_DIR)/wr_umm_rrccon.$(SRC) \
#    $(IN_DIR)/wr_umm_l1_msg.$(SRC) \
#    $(IN_DIR)/wr_umm_l1_hdl.$(SRC) \
#    $(IN_DIR)/wr_umm_pdcp_hdl.$(SRC) \
#    $(IN_DIR)/wr_umm_rrc_hdl.$(SRC) \
#    $(IN_DIR)/wr_umm_sch_hdl.$(SRC) \
#    $(IN_DIR)/wr_umm_s1ap_hdl.$(SRC) \
#    $(IN_DIR)/wr_umm_x2ap_hdl.$(SRC) \
#    $(IN_DIR)/wr_tmr.$(SRC) \
#    $(IN_DIR)/wr_ex_ms.$(SRC) \
#    $(IN_DIR)/wr_lwr.$(SRC) \
#    $(IN_DIR)/wr_umm_initcntsetup.$(SRC) \
#    $(IN_DIR)/wr_umm_rrcreestab.$(SRC) \
#    $(IN_DIR)/wr_umm_ctxtmod.$(SRC) \
#    $(IN_DIR)/wr_emm_anr.$(SRC) \
#    $(IN_DIR)/wr_emm_ecsfb_anr.$(SRC) \
#    $(IN_DIR)/wr_umm_x2srcho.$(SRC) \
#    $(IN_DIR)/wr_umm_x2tgtho.$(SRC) \
#    $(IN_DIR)/wr_umm_s1srcho.$(SRC) \
#    $(IN_DIR)/wr_umm_s1tgtho.$(SRC) \
#    $(IN_DIR)/wr_umm_ho.$(SRC) \
#    $(IN_DIR)/wr_umm_csfbupdtcell.$(SRC) \
#    $(IN_DIR)/wr_umm_csfb.$(SRC)\
#    $(IN_DIR)/wr_umm_ecsfb.$(SRC)\
#    $(IN_DIR)/wr_diag.$(SRC)    \
#    $(IN_DIR)/wr_smm_diag_hdl.$(SRC)\
#    $(IN_DIR)/wr_umm_locrpt.$(SRC)\
#    $(IN_DIR)/wr_umm_anrmeas.$(SRC)\
#    $(IN_DIR)/wr_umm_eventanr.$(SRC)\
#    $(IN_DIR)/wr_umm_dlcdma.$(SRC)\
#    $(IN_DIR)/wr_kpi.$(SRC)\
#    $(IN_DIR)/wr_umm_drx.$(SRC)\
#    $(IN_DIR)/wr_nmm.$(SRC)\
#    $(IN_DIR)/wr_dbg_log.$(SRC)\
#    $(IN_DIR)/wr_smm_tmr.$(SRC)\
#    $(IN_DIR)/wr_alarm.$(SRC)\
#    $(IN_DIR)/wr_umm_lteadv.$(SRC)\
#    $(IN_DIR)/wr_emm_lteadv.$(SRC)\
#    $(IN_DIR)/wr_emm_s1_flex.$(SRC)\
#    $(IN_DIR)/wr_emm_cnm.$(SRC)\
#    $(IN_DIR)/wr_smm_son.$(SRC)\
#    $(IN_DIR)/wr_smm_son_utils.$(SRC)\
#    $(IN_DIR)/wr_ifm_son.$(SRC)\
#    $(IN_DIR)/wr_emm_son.$(SRC)\
#    $(IN_DIR)/wr_umm_csfb_geran.$(SRC)
#
#ifeq ($(BLDENV),lnx_e2e_bc)
#SECSRC=c
#OBJ1=o
##wrE2eLnxSRCS +=	 ../../mt/security/hmac.$(SECSRC) \
##                 ../../mt/security/hmacsha256.$(SECSRC) \
##                 ../../mt/security/mp.$(SECSRC) \
##                 ../../mt/security/endianness.$(SECSRC) \
##                 ../../mt/security/sha256.$(SECSRC) \
##                 ../../mt/security/sha2k32.$(SECSRC) 
#endif
#
#ifeq ($(OAM_ENABLE),YES)
#wrE2eLnxSRCS1= \
#     $(IN_DIR)/wr_smm_enbapp_cmnplatutils.$(SRC) \
#     $(IN_DIR)/wr_smm_dyncfg.$(SRC)
#else
#ifeq ($(OAM_ENV),WR_RSYS_OAM)
#wrE2eLnxSRCS1= \
#     $(IN_DIR)/wr_smm_enbapp_cmnplatutils.$(SRC)\
#     $(IN_DIR)/wr_smm_dyncfg.$(SRC)
#else
#ifeq ($(OAM_ENV),WR_RSYS_OAM_SRC)
#wrE2eLnxSRCS1= \
#     $(IN_DIR)/wr_smm_enbapp_cmnplatutils.$(SRC) \
#     $(IN_DIR)/wr_smm_dyncfg.$(SRC)
#else
#wrE2eLnxSRCS1= \
#    $(IN_DIR)/wr_smm_enbapp_utils.$(SRC)
#endif
#endif
#endif

# Product objects-------------------------------------------------------
#wrE2eLnxOBJS= \
#    $(OUT_DIR)/wr_sw_version.$(OBJ) \
#    $(OUT_DIR)/wr_emm_eom.$(OBJ) \
#    $(OUT_DIR)/wr_umm_meas.$(OBJ) \
#    $(OUT_DIR)/wr_umm_anrmeas.$(OBJ) \
#    $(OUT_DIR)/wr_umm_eventanr.$(OBJ) \
#    $(OUT_DIR)/wr_umm_dlcdma.$(OBJ) \
#    $(OUT_DIR)/wr_lmm.$(OBJ) \
#    $(OUT_DIR)/wr_emm_neighenb.$(OBJ) \
#    $(OUT_DIR)/wr_emm_cfg.$(OBJ) \
#    $(OUT_DIR)/wr_emm_csg.$(OBJ) \
#    $(OUT_DIR)/wr_emm_ecsfb_cfg.$(OBJ) \
#    $(OUT_DIR)/wr_emm_rim_app.$(OBJ) \
#    $(OUT_DIR)/wr_emm_rim.$(OBJ) \
#    $(OUT_DIR)/wr_utils.$(OBJ) \
#    $(OUT_DIR)/wr_dam.$(OBJ) \
#    $(OUT_DIR)/wr_dam_ifm_app.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_dam.$(OBJ) \
#    $(OUT_DIR)/wr_dam_ex_ms.$(OBJ) \
#    $(OUT_DIR)/wr_dam_tmr.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_dam_utils.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rrccsfb.$(OBJ) \
#    $(OUT_DIR)/wr_umm_mobparms.$(OBJ) \
#    $(OUT_DIR)/wr_umm_ulnas.$(OBJ) \
#    $(OUT_DIR)/wr_umm_dlnas.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rabsetup.$(OBJ) \
#    $(OUT_DIR)/wr_umm_ctxtrel.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rabmod.$(OBJ) \
#    $(OUT_DIR)/wr_emm_cell.$(OBJ) \
#    $(OUT_DIR)/wr_emm_mme.$(OBJ) \
#    $(OUT_DIR)/wr_umm_sch_msg.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rrc_msg.$(OBJ) \
#    $(OUT_DIR)/wr_umm_s1ap_msg.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rrccon.$(OBJ) \
#    $(OUT_DIR)/wr_umm_l1_msg.$(OBJ) \
#    $(OUT_DIR)/wr_emm_mme_s1ap.$(OBJ) \
#    $(OUT_DIR)/wr_emm_plmn.$(OBJ) \
#    $(OUT_DIR)/wr_emm.$(OBJ) \
#    $(OUT_DIR)/wr_emm_pbm.$(OBJ) \
#    $(OUT_DIR)/wr_emm_pws.$(OBJ) \
#    $(OUT_DIR)/wr_emm_pbm_sib.$(OBJ) \
#    $(OUT_DIR)/wr_emm_ecsfb_utils.$(OBJ) \
#    $(OUT_DIR)/wr_umm_ecsfb_utils.$(OBJ) \
#    $(OUT_DIR)/wr_smm_smallcell.$(OBJ) \
#    $(OUT_DIR)/wr_smm_init_merged.$(OBJ)  	\
#    $(OUT_DIR)/wr_smm_cl.$(OBJ) \
#    $(OUT_DIR)/wr_smm_mac.$(OBJ) \
#    $(OUT_DIR)/wr_smm_rlc.$(OBJ) \
#    $(OUT_DIR)/wr_smm_pdcp.$(OBJ) \
#    $(OUT_DIR)/wr_msm_common.$(OBJ) \
#    $(OUT_DIR)/wr_smm_rrc.$(OBJ) \
#    $(OUT_DIR)/wr_smm_s1ap.$(OBJ) \
#    $(OUT_DIR)/wr_smm_x2ap.$(OBJ) \
#    $(OUT_DIR)/wr_plat.$(OBJ) \
#    $(OUT_DIR)/wr_smm_egtp.$(OBJ) \
#    $(OUT_DIR)/wr_smm_sctp.$(OBJ) \
#    $(OUT_DIR)/wr_smm_tucl.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_x2ap.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_egtp.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_rrc.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_pdcp.$(OBJ) \
#    $(OUT_DIR)/wr_tenb_stats.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_schd.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_rrm.$(OBJ) \
#    $(OUT_DIR)/wr_ptli.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_s1ap.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_l1.$(OBJ) \
#    $(OUT_DIR)/wr_umm.$(OBJ) \
#    $(OUT_DIR)/wr_umm_s1ap_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_umm_egtp_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_umm_l1_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_umm_pdcp_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rrc_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_umm_sch_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_umm_x2ap_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_smm_enbapp_rsys.$(OBJ) \
#    $(OUT_DIR)/wr_smm_rrm.$(OBJ) \
#    $(OUT_DIR)/wr_smm_watchdog_tmr.$(OBJ) \
#    $(OUT_DIR)/wr_umm_x2ap_msg.$(OBJ) \
#    $(OUT_DIR)/wr_tmr.$(OBJ) \
#    $(OUT_DIR)/wr_ptmi.$(OBJ) \
#    $(OUT_DIR)/wr_utils.$(OBJ) \
#    $(OUT_DIR)/wr_ex_ms.$(OBJ) \
#    $(OUT_DIR)/wr_lwr.$(OBJ) \
#    $(OUT_DIR)/wr_umm_initcntsetup.$(OBJ) \
#    $(OUT_DIR)/wr_umm_lcrabrel.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rabrel.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rrcreestab.$(OBJ) \
#    $(OUT_DIR)/wr_umm_ctxtmod.$(OBJ) \
#    $(OUT_DIR)/wr_emm_anr.$(OBJ) \
#    $(OUT_DIR)/wr_emm_ecsfb_anr.$(OBJ) \
#    $(OUT_DIR)/wr_umm_x2srcho.$(OBJ) \
#    $(OUT_DIR)/wr_umm_x2tgtho.$(OBJ) \
#    $(OUT_DIR)/wr_umm_s1srcho.$(OBJ) \
#    $(OUT_DIR)/wr_umm_s1tgtho.$(OBJ) \
#    $(OUT_DIR)/wr_umm_ho.$(OBJ) \
#    $(OUT_DIR)/wr_umm_csfbupdtcell.$(OBJ) \
#    $(OUT_DIR)/wr_umm_csfb.$(OBJ) \
#    $(OUT_DIR)/wr_umm_ecsfb.$(OBJ) \
#    $(OUT_DIR)/wr_umm_locrpt.$(OBJ)\
#    $(OUT_DIR)/wr_diag.$(OBJ)\
#    $(OUT_DIR)/wr_smm_diag_hdl.$(OBJ)\
#    $(OUT_DIR)/wr_kpi.$(OBJ)\
#    $(OUT_DIR)/wr_umm_drx.$(OBJ)\
#    $(OUT_DIR)/wr_nmm.$(OBJ)\
#    $(OUT_DIR)/wr_dbg_log.$(OBJ)\
#    $(OUT_DIR)/wr_smm_tmr.$(OBJ)\
#    $(OUT_DIR)/wr_alarm.$(OBJ)\
#    $(OUT_DIR)/wr_umm_lteadv.$(OBJ)\
#    $(OUT_DIR)/wr_emm_lteadv.$(OBJ)\
#    $(OUT_DIR)/wr_emm_s1_flex.$(OBJ)\
#    $(OUT_DIR)/wr_emm_cnm.$(OBJ)\
#    $(OUT_DIR)/wr_smm_son.$(OBJ)\
#    $(OUT_DIR)/wr_smm_son_utils.$(OBJ)\
#    $(OUT_DIR)/wr_ifm_son.$(OBJ)\
#    $(OUT_DIR)/wr_emm_son.$(OBJ)\
#    $(OUT_DIR)/wr_umm_csfb_geran.$(OBJ)
#
#ifeq ($(OAM_ENABLE),YES)
#wrE2eLnxOBJS1 =\
#     $(OUT_DIR)/wr_smm_enbapp_cmnplatutils.$(OBJ)\
#     $(OUT_DIR)/wr_smm_dyncfg.$(OBJ)\
#     $(OUT_DIR)/wr_msm_common.$(OBJ)
#else
#ifeq ($(OAM_ENV),WR_RSYS_OAM)
#wrE2eLnxOBJS1 =\
#     $(OUT_DIR)/wr_smm_enbapp_cmnplatutils.$(OBJ)\
#     $(OUT_DIR)/wr_smm_dyncfg.$(OBJ)\
#     $(OUT_DIR)/wr_msm_common.$(OBJ)
#else
#ifeq ($(OAM_ENV),WR_RSYS_OAM_SRC)
#wrE2eLnxOBJS1 =\
#     $(OUT_DIR)/wr_smm_enbapp_cmnplatutils.$(OBJ)\
#     $(OUT_DIR)/wr_smm_dyncfg.$(OBJ)\
#     $(OUT_DIR)/wr_msm_common.$(OBJ)
#else
#wrE2eLnxOBJS1 =\
##     $(OUT_DIR)/wr_smm_enbapp_utils.$(OBJ)
#endif
#endif
#endif

# Product objects-------------------------------------------------------
#wrE2eLnxOBJS_ms= \
#    $(OUT_DIR)/wr_sw_version.$(OBJ) \
#    $(OUT_DIR)/wr_emm_eom.$(OBJ) \
#    $(OUT_DIR)/wr_umm_meas.$(OBJ) \
#    $(OUT_DIR)/wr_umm_anrmeas.$(OBJ) \
#    $(OUT_DIR)/wr_umm_eventanr.$(OBJ) \
#    $(OUT_DIR)/wr_umm_dlcdma.$(OBJ) \
#    $(OUT_DIR)/wr_lmm.$(OBJ) \
#    $(OUT_DIR)/wr_emm_neighenb.$(OBJ) \
#    $(OUT_DIR)/wr_emm_cfg.$(OBJ) \
#    $(OUT_DIR)/wr_emm_csg.$(OBJ) \
#    $(OUT_DIR)/wr_emm_ecsfb_cfg.$(OBJ) \
#    $(OUT_DIR)/wr_emm_rim_app.$(OBJ) \
#    $(OUT_DIR)/wr_emm_rim.$(OBJ) \
#    $(OUT_DIR)/wr_smm_smallcell.$(OBJ) \
#    $(OUT_DIR)/wr_utils.$(OBJ) \
#    $(OUT_DIR)/wr_dam.$(OBJ) \
#    $(OUT_DIR)/wr_dam_ifm_app.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_dam.$(OBJ) \
#    $(OUT_DIR)/wr_dam_ex_ms.$(OBJ) \
#    $(OUT_DIR)/wr_dam_tmr.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_dam_utils.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rrccsfb.$(OBJ) \
#    $(OUT_DIR)/wr_umm_mobparms.$(OBJ) \
#    $(OUT_DIR)/wr_umm_ulnas.$(OBJ) \
#    $(OUT_DIR)/wr_umm_dlnas.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rabsetup.$(OBJ) \
#    $(OUT_DIR)/wr_umm_ctxtrel.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rabmod.$(OBJ) \
#    $(OUT_DIR)/wr_emm_cell.$(OBJ) \
#    $(OUT_DIR)/wr_emm_mme.$(OBJ) \
#    $(OUT_DIR)/wr_umm_sch_msg.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rrc_msg.$(OBJ) \
#    $(OUT_DIR)/wr_umm_s1ap_msg.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rrccon.$(OBJ) \
#    $(OUT_DIR)/wr_umm_l1_msg.$(OBJ) \
#    $(OUT_DIR)/wr_emm_mme_s1ap.$(OBJ) \
#    $(OUT_DIR)/wr_emm_plmn.$(OBJ) \
#    $(OUT_DIR)/wr_emm.$(OBJ) \
#    $(OUT_DIR)/wr_emm_pbm.$(OBJ) \
#    $(OUT_DIR)/wr_emm_pws.$(OBJ) \
#    $(OUT_DIR)/wr_emm_pbm_sib.$(OBJ) \
#    $(OUT_DIR)/wr_emm_ecsfb_utils.$(OBJ) \
#    $(OUT_DIR)/wr_umm_ecsfb_utils.$(OBJ) \
#    $(OUT_DIR)/wr_smm_init.$(OBJ)  	\
#    $(OUT_DIR)/wr_smm_cfg.$(OBJ)  	\
#    $(OUT_DIR)/wr_smm_cl.$(OBJ) \
#    $(OUT_DIR)/wr_smm_mac.$(OBJ) \
#    $(OUT_DIR)/wr_smm_rlc.$(OBJ) \
#    $(OUT_DIR)/wr_smm_pdcp.$(OBJ) \
#    $(OUT_DIR)/wr_smm_rrc.$(OBJ) \
#    $(OUT_DIR)/wr_smm_s1ap.$(OBJ) \
#    $(OUT_DIR)/wr_smm_x2ap.$(OBJ) \
#    $(OUT_DIR)/wr_plat.$(OBJ) \
#    $(OUT_DIR)/wr_smm_egtp.$(OBJ) \
#    $(OUT_DIR)/wr_smm_sctp.$(OBJ) \
#    $(OUT_DIR)/wr_smm_tucl.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_x2ap.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_egtp.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_rrc.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_pdcp.$(OBJ) \
#    $(OUT_DIR)/wr_tenb_stats.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_schd.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_rrm.$(OBJ) \
#    $(OUT_DIR)/wr_ptli.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_s1ap.$(OBJ) \
#    $(OUT_DIR)/wr_ifm_l1.$(OBJ) \
#    $(OUT_DIR)/wr_umm.$(OBJ) \
#    $(OUT_DIR)/wr_umm_s1ap_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_umm_egtp_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_umm_l1_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_umm_pdcp_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rrc_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_umm_sch_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_umm_x2ap_hdl.$(OBJ) \
#    $(OUT_DIR)/wr_smm_enbapp_rsys.$(OBJ) \
#    $(OUT_DIR)/wr_smm_rrm.$(OBJ) \
#    $(OUT_DIR)/wr_smm_watchdog_tmr.$(OBJ) \
#    $(OUT_DIR)/wr_umm_x2ap_msg.$(OBJ) \
#    $(OUT_DIR)/wr_tmr.$(OBJ) \
#    $(OUT_DIR)/wr_ptmi.$(OBJ) \
#    $(OUT_DIR)/wr_utils.$(OBJ) \
#    $(OUT_DIR)/wr_ex_ms.$(OBJ) \
#    $(OUT_DIR)/wr_lwr.$(OBJ) \
#    $(OUT_DIR)/wr_umm_initcntsetup.$(OBJ) \
#    $(OUT_DIR)/wr_umm_lcrabrel.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rabrel.$(OBJ) \
#    $(OUT_DIR)/wr_umm_rrcreestab.$(OBJ) \
#    $(OUT_DIR)/wr_umm_ctxtmod.$(OBJ) \
#    $(OUT_DIR)/wr_emm_anr.$(OBJ) \
#    $(OUT_DIR)/wr_emm_ecsfb_anr.$(OBJ) \
#    $(OUT_DIR)/wr_umm_x2srcho.$(OBJ) \
#    $(OUT_DIR)/wr_umm_x2tgtho.$(OBJ) \
#    $(OUT_DIR)/wr_umm_s1srcho.$(OBJ) \
#    $(OUT_DIR)/wr_umm_s1tgtho.$(OBJ) \
#    $(OUT_DIR)/wr_umm_ho.$(OBJ) \
#    $(OUT_DIR)/wr_umm_csfbupdtcell.$(OBJ) \
#    $(OUT_DIR)/wr_umm_csfb.$(OBJ) \
#    $(OUT_DIR)/wr_umm_ecsfb.$(OBJ) \
#    $(OUT_DIR)/wr_diag.$(OBJ) \
#    $(OUT_DIR)/wr_smm_diag_hdl.$(OBJ)\
#    $(OUT_DIR)/wr_umm_locrpt.$(OBJ)\
#    $(OUT_DIR)/wr_kpi.$(OBJ)\
#    $(OUT_DIR)/wr_umm_drx.$(OBJ)\
#    $(OUT_DIR)/wr_nmm.$(OBJ)\
#    $(OUT_DIR)/wr_dbg_log.$(OBJ)\
#    $(OUT_DIR)/wr_smm_tmr.$(OBJ)\
#    $(OUT_DIR)/wr_alarm.$(OBJ)\
#    $(OUT_DIR)/wr_umm_lteadv.$(OBJ)\
#    $(OUT_DIR)/wr_emm_lteadv.$(OBJ)\
#    $(OUT_DIR)/wr_emm_s1_flex.$(OBJ)\
#    $(OUT_DIR)/wr_emm_cnm.$(OBJ)\
#    $(OUT_DIR)/wr_smm_son.$(OBJ)\
#    $(OUT_DIR)/wr_smm_son_utils.$(OBJ)\
#    $(OUT_DIR)/wr_ifm_son.$(OBJ)\
#    $(OUT_DIR)/wr_emm_son.$(OBJ)\
#    $(OUT_DIR)/wr_umm_csfb_geran.$(OBJ)
#
#ifeq ($(BLDENV),lnx_e2e_bc)
#wrE2eLnxOBJS_ms += $(OUT_DIR)/hmac.$(OBJ) \
#                   $(OUT_DIR)/hmacsha256.$(OBJ) \
#                   $(OUT_DIR)/mp.$(OBJ) \
#                   $(OUT_DIR)/endianness.$(OBJ) \
#                   $(OUT_DIR)/sha256.$(OBJ) \
#                   $(OUT_DIR)/sha2k32.$(OBJ) 
#endif
#ifeq ($(BLDENV),lnx_e2e_bc_blog)
#wrE2eLnxOBJS_ms += $(OUT_DIR)/hmac.$(OBJ) \
#                   $(OUT_DIR)/hmacsha256.$(OBJ) \
#                   $(OUT_DIR)/mp.$(OBJ) \
#                   $(OUT_DIR)/endianness.$(OBJ) \
#                   $(OUT_DIR)/sha256.$(OBJ) \
#                   $(OUT_DIR)/sha2k32.$(OBJ) 
#endif
#ifeq ($(OAM_ENABLE),YES)
#wrE2eLnxOBJS_ms1 =\
#     $(OUT_DIR)/wr_smm_enbapp_cmnplatutils.$(OBJ)\
#     $(OUT_DIR)/wr_smm_dyncfg.$(OBJ)\
#     $(OUT_DIR)/wr_msm_common.$(OBJ)
#else
#ifeq ($(OAM_ENV),WR_RSYS_OAM)
#wrE2eLnxOBJS_ms1 =\
#     $(OUT_DIR)/wr_smm_enbapp_cmnplatutils.$(OBJ)\
     $(OUT_DIR)/wr_smm_dyncfg.$(OBJ)\
#     $(OUT_DIR)/wr_msm_common.$(OBJ)
#else
#ifeq ($(OAM_ENV),WR_RSYS_OAM_SRC)
#wrE2eLnxOBJS_ms1 =\
#     $(OUT_DIR)/wr_smm_enbapp_cmnplatutils.$(OBJ)\
#     $(OUT_DIR)/wr_smm_dyncfg.$(OBJ)\
#     $(OUT_DIR)/wr_msm_common.$(OBJ)
#else
#wrE2eLnxOBJS_ms1 =\
#     $(OUT_DIR)/wr_smm_enbapp_utils.$(OBJ)
#endif
#endif
#endif

#wrPerfLnxOBJS= \
#    $(OUT_DIR)/ \
#    $(OUT_DIR)/

#wrPerfLnxOBJSUU= \
#    $(OUT_DIR)/ \
#    $(OUT_DIR)/
    
#wrPerfCavSRCS= \
#    $(IN_DIR)/ \
#    $(IN_DIR)/

#wrE2eCavSRCS= \
#    $(IN_DIR)/ \
#    $(IN_DIR)/


# Product objects-------------------------------------------------------
#wrE2eCavOBJS= \
#    $(OUT_DIR)/ \
#    $(OUT_DIR)/

#wrPerfCavOBJS= \
#    $(OUT_DIR)/ \
#    $(OUT_DIR)/
 
# Product sources-------------------------------------------------------
#wrPerfCavSRCSUU= \
#    $(IN_DIR)/ \
#    $(IN_DIR)/

#wrPerfCavOBJSUU=\
#    $(OUT_DIR)/ \
#    $(OUT_DIR)/

#WRCM_INC=$(VS_DIR)/wr.h

#ALL_INC=$(WRCM_INC) $(CM_INC)

#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#
#
#$(OUT_DIR)/wr_sw_version.$(OBJ): $(IN_DIR)/wr_sw_version.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_sw_version.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_sw_version.$(SRC)
#		  
#$(OUT_DIR)/wr_emm_eom.$(OBJ): $(IN_DIR)/wr_emm_eom.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_eom.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_emm_eom.$(SRC)
#		  
#$(OUT_DIR)/wr_umm_meas.$(OBJ): $(IN_DIR)/wr_umm_meas.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_meas.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_umm_meas.$(SRC)
#
#$(OUT_DIR)/wr_umm_ecsfb_meas.$(OBJ): $(IN_DIR)/wr_umm_ecsfb_meas.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_ecsfb_meas.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_umm_ecsfb_meas.$(SRC)
#
#$(OUT_DIR)/wr_umm_anrmeas.$(OBJ): $(IN_DIR)/wr_umm_anrmeas.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c -o$(OUT_DIR)/wr_umm_anrmeas.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_umm_anrmeas.$(SRC)
#		  
#$(OUT_DIR)/wr_umm_eventanr.$(OBJ): $(IN_DIR)/wr_umm_eventanr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c -o$(OUT_DIR)/wr_umm_eventanr.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_umm_eventanr.$(SRC)
#
#$(OUT_DIR)/wr_umm_dlcdma.$(OBJ): $(IN_DIR)/wr_umm_dlcdma.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c -o$(OUT_DIR)/wr_umm_dlcdma.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_umm_dlcdma.$(SRC)
#
#$(OUT_DIR)/wr_lmm.$(OBJ): $(IN_DIR)/wr_lmm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_lmm.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_lmm.$(SRC)
#
#$(OUT_DIR)/wr_emm_neighenb.$(OBJ): $(IN_DIR)/wr_emm_neighenb.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_neighenb.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_emm_neighenb.$(SRC)
#
#$(OUT_DIR)/wr_emm_cfg.$(OBJ): $(IN_DIR)/wr_emm_cfg.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_cfg.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_emm_cfg.$(SRC)
#
#$(OUT_DIR)/wr_emm_csg.$(OBJ): $(IN_DIR)/wr_emm_csg.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_csg.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_emm_csg.$(SRC)
#
#$(OUT_DIR)/wr_emm_ecsfb_cfg.$(OBJ): $(IN_DIR)/wr_emm_ecsfb_cfg.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_ecsfb_cfg.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_emm_ecsfb_cfg.$(SRC)
#
#$(OUT_DIR)/wr_emm_rim_app.$(OBJ): $(IN_DIR)/wr_emm_rim_app.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_rim_app.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_emm_rim_app.$(SRC)
#
#$(OUT_DIR)/wr_emm_rim.$(OBJ): $(IN_DIR)/wr_emm_rim.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_rim.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_emm_rim.$(SRC)
#
#$(OUT_DIR)/wr_smm_smallcell.$(OBJ): $(IN_DIR)/wr_smm_smallcell.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_smm_smallcell.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_smm_smallcell.$(SRC)
#
#$(OUT_DIR)/wr_umm_rrccsfb.$(OBJ): $(IN_DIR)/wr_umm_rrccsfb.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_rrccsfb.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_rrccsfb.$(SRC)
#
#$(OUT_DIR)/wr_umm_mobparms.$(OBJ): $(IN_DIR)/wr_umm_mobparms.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_mobparms.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_mobparms.$(SRC)
#
#$(OUT_DIR)/wr_umm_ulnas.$(OBJ): $(IN_DIR)/wr_umm_ulnas.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_ulnas.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_ulnas.$(SRC)
#
#$(OUT_DIR)/wr_umm_s1ap_msg.$(OBJ): $(IN_DIR)/wr_umm_s1ap_msg.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_s1ap_msg.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_s1ap_msg.$(SRC)
#
#$(OUT_DIR)/wr_umm_dlnas.$(OBJ): $(IN_DIR)/wr_umm_dlnas.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_dlnas.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_dlnas.$(SRC)
#
#$(OUT_DIR)/wr_umm_rabsetup.$(OBJ): $(IN_DIR)/wr_umm_rabsetup.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_rabsetup.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_rabsetup.$(SRC)
#
#$(OUT_DIR)/wr_umm_ctxtrel.$(OBJ): $(IN_DIR)/wr_umm_ctxtrel.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_ctxtrel.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_ctxtrel.$(SRC)
#
#$(OUT_DIR)/wr_umm_rabrel.$(OBJ): $(IN_DIR)/wr_umm_rabrel.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_rabrel.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_rabrel.$(SRC)
#
#$(OUT_DIR)/wr_umm_rabmod.$(OBJ): $(IN_DIR)/wr_umm_rabmod.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_rabmod.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_rabmod.$(SRC)
#
#$(OUT_DIR)/wr_umm_lcrabrel.$(OBJ): $(IN_DIR)/wr_umm_lcrabrel.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_lcrabrel.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_lcrabrel.$(SRC)
#
#$(OUT_DIR)/wr_umm_rrccon.$(OBJ): $(IN_DIR)/wr_umm_rrccon.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_rrccon.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_rrccon.$(SRC)
#
#$(OUT_DIR)/wr_emm_cell.$(OBJ): $(IN_DIR)/wr_emm_cell.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_cell.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_emm_cell.$(SRC)
#
#$(OUT_DIR)/wr_emm_pbm.$(OBJ): $(IN_DIR)/wr_emm_pbm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_pbm.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_emm_pbm.$(SRC)
#
#$(OUT_DIR)/wr_emm_pws.$(OBJ): $(IN_DIR)/wr_emm_pws.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_pws.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_emm_pws.$(SRC)
#
#$(OUT_DIR)/wr_emm_mme.$(OBJ): $(IN_DIR)/wr_emm_mme.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_mme.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_emm_mme.$(SRC)
#
#$(OUT_DIR)/wr_utils.$(OBJ): $(IN_DIR)/wr_utils.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_utils.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_utils.$(SRC)
#
#$(OUT_DIR)/wr_emm_mme_s1ap.$(OBJ): $(IN_DIR)/wr_emm_mme_s1ap.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_mme_s1ap.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_emm_mme_s1ap.$(SRC) 
#
#$(OUT_DIR)/wr_umm_rrc_msg.$(OBJ): $(IN_DIR)/wr_umm_rrc_msg.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_rrc_msg.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_rrc_msg.$(SRC)
#
#$(OUT_DIR)/wr_umm_l1_msg.$(OBJ): $(IN_DIR)/wr_umm_l1_msg.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_l1_msg.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_l1_msg.$(SRC)
#
#$(OUT_DIR)/wr_umm_sch_msg.$(OBJ): $(IN_DIR)/wr_umm_sch_msg.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_sch_msg.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_sch_msg.$(SRC)
#
#$(OUT_DIR)/wr_emm_plmn.$(OBJ): $(IN_DIR)/wr_emm_plmn.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_plmn.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_emm_plmn.$(SRC)
#
#$(OUT_DIR)/wr_emm_pbm_sib.$(OBJ): $(IN_DIR)/wr_emm_pbm_sib.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_pbm_sib.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_emm_pbm_sib.$(SRC)
#
#$(OUT_DIR)/wr_emm_ecsfb_utils.$(OBJ): $(IN_DIR)/wr_emm_ecsfb_utils.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_ecsfb_utils.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_emm_ecsfb_utils.$(SRC)
#
#$(OUT_DIR)/wr_umm_ecsfb_utils.$(OBJ): $(IN_DIR)/wr_umm_ecsfb_utils.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c -o$(OUT_DIR)/wr_umm_ecsfb_utils.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#        $(IN_DIR)/wr_umm_ecsfb_utils.$(SRC)
#
#$(OUT_DIR)/wr_umm.$(OBJ): $(IN_DIR)/wr_umm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm.$(SRC)
#
#$(OUT_DIR)/wr_dam_ifm_app.$(OBJ): $(IN_DIR)/wr_dam_ifm_app.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_dam_ifm_app.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_dam_ifm_app.$(SRC)
#
#$(OUT_DIR)/wr_dam.$(OBJ): $(IN_DIR)/wr_dam.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_dam.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_dam.$(SRC)
#
#$(OUT_DIR)/wr_nmm.$(OBJ): $(IN_DIR)/wr_nmm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_nmm.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_nmm.$(SRC)
#
#$(OUT_DIR)/wr_dbg_log.$(OBJ): $(IN_DIR)/wr_dbg_log.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_dbg_log.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_dbg_log.$(SRC)
#
#$(OUT_DIR)/wr_ifm_dam.$(OBJ): $(IN_DIR)/wr_ifm_dam.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_ifm_dam.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_ifm_dam.$(SRC)
#
#$(OUT_DIR)/wr_dam_ex_ms.$(OBJ): $(IN_DIR)/wr_dam_ex_ms.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_dam_ex_ms.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_dam_ex_ms.$(SRC)
#
#$(OUT_DIR)/wr_dam_tmr.$(OBJ): $(IN_DIR)/wr_dam_tmr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_dam_tmr.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_dam_tmr.$(SRC)
#
#$(OUT_DIR)/wr_ifm_dam_utils.$(OBJ): $(IN_DIR)/wr_ifm_dam_utils.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_ifm_dam_utils.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_ifm_dam_utils.$(SRC)
#
#$(OUT_DIR)/wr_smm_init.$(OBJ): $(IN_DIR)/wr_smm_init.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_smm_init.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_smm_init.$(SRC)
#
#$(OUT_DIR)/wr_smm_cfg.$(OBJ): $(IN_DIR)/wr_smm_cfg.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_smm_cfg.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_smm_cfg.$(SRC)
#
#$(OUT_DIR)/wr_smm_init_merged.$(OBJ): $(IN_DIR)/wr_smm_init_merged.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_smm_init_merged.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_smm_init_merged.$(SRC)
#
#$(OUT_DIR)/wr_smm_rrc.$(OBJ): $(IN_DIR)/wr_smm_rrc.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCSMNHMILNH -DLCLNH $(IN_DIR)/wr_smm_rrc.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_rrc.$(OBJ)
#
#$(OUT_DIR)/wr_smm_rlc.$(OBJ): $(IN_DIR)/wr_smm_rlc.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCKWMILKW -DLCPJMILPJ -DLCLKW $(IN_DIR)/wr_smm_rlc.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_rlc.$(OBJ)
#
#$(OUT_DIR)/wr_smm_mac.$(OBJ): $(IN_DIR)/wr_smm_mac.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCRGMILRG  -DLCLRG -DLCSMMILRG $(IN_DIR)/wr_smm_mac.$(SRC) -o $(OUT_DIR)/wr_smm_mac.$(OBJ)
#
#$(OUT_DIR)/wr_smm_s1ap.$(OBJ): $(IN_DIR)/wr_smm_s1ap.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCSMMILSZ -DLCLSZ -DSZ_ENB $(IN_DIR)/wr_smm_s1ap.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_s1ap.$(OBJ)
#
#$(OUT_DIR)/wr_smm_x2ap.$(OBJ): $(IN_DIR)/wr_smm_x2ap.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCSMMILCZ -DLCLCZ -DCZ_ENB $(IN_DIR)/wr_smm_x2ap.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_x2ap.$(OBJ)
#
#$(OUT_DIR)/wr_plat.$(OBJ): $(IN_DIR)/wr_plat.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCSMMILCZ -DLCLCZ -DCZ_ENB $(IN_DIR)/wr_plat.$(SRC) -o \
#	$(OUT_DIR)/wr_plat.$(OBJ)
#
#$(OUT_DIR)/wr_smm_sctp.$(OBJ): $(IN_DIR)/wr_smm_sctp.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCSMSBMILSB -DLCLSB -DLSB4 -DLSB8 $(IN_DIR)/wr_smm_sctp.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_sctp.$(OBJ)
#
#$(OUT_DIR)/wr_smm_tucl.$(OBJ): $(IN_DIR)/wr_smm_tucl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCSMHIMILHI $(IN_DIR)/wr_smm_tucl.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_tucl.$(OBJ)
#
#$(OUT_DIR)/wr_smm_egtp.$(OBJ): $(IN_DIR)/wr_smm_egtp.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCSMMILEG -DLCLEG $(IN_DIR)/wr_smm_egtp.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_egtp.$(OBJ)
#
#$(OUT_DIR)/wr_smm_enbapp_rsys.$(OBJ): $(IN_DIR)/wr_smm_enbapp_rsys.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLWLCSMMILWR  -DLWLCSWR -DLWLCWRMILWR -DSM -UPTSMMILWR $(IN_DIR)/wr_smm_enbapp_rsys.$(SRC) -o\
#	$(OUT_DIR)/wr_smm_enbapp_rsys.$(OBJ)
#
#$(OUT_DIR)/wr_smm_watchdog_tmr.$(OBJ): $(IN_DIR)/wr_smm_watchdog_tmr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLWLCSMMILWR  -DLWLCSWR -DLWLCWRMILWR -DSM -UPTSMMILWR $(IN_DIR)/wr_smm_watchdog_tmr.$(SRC) -o\
#	$(OUT_DIR)/wr_smm_watchdog_tmr.$(OBJ)
#
#$(OUT_DIR)/wr_smm_enbapp_utils.$(OBJ): $(IN_DIR)/wr_smm_enbapp_utils.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLWLCSMMILWR  -DLWLCSWR -DLWLCWRMILWR -DSM $(IN_DIR)/wr_smm_enbapp_utils.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_enbapp_utils.$(OBJ)
#
#$(OUT_DIR)/wr_smm_enbapp_cmnplatutils.$(OBJ): $(IN_DIR)/wr_smm_enbapp_cmnplatutils.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLWLCSMMILWR  -DLWLCSWR -DLWLCWRMILWR -DSM $(IN_DIR)/wr_smm_enbapp_cmnplatutils.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_enbapp_cmnplatutils.$(OBJ)
#
#$(OUT_DIR)/wr_msm_common.$(OBJ): $(IN_DIR)/wr_msm_common.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLWLCSMMILWR  -DLWLCSWR -DLWLCWRMILWR -DSM $(IN_DIR)/wr_msm_common.$(SRC) -o \
#	$(OUT_DIR)/wr_msm_common.$(OBJ)
#
#$(OUT_DIR)/wr_smm_dyncfg.$(OBJ): $(IN_DIR)/wr_smm_dyncfg.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLWLCSMMILWR  -DLWLCSWR -DLWLCWRMILWR -DSM $(IN_DIR)/wr_smm_dyncfg.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_dyncfg.$(OBJ)
#
#$(OUT_DIR)/wr_smm_rrm.$(OBJ): $(IN_DIR)/wr_smm_rrm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -ULCSMMILWR  -ULCSWR -ULCWRMILWR  $(IN_DIR)/wr_smm_rrm.$(SRC) -o\
#	$(OUT_DIR)/wr_smm_rrm.$(OBJ)
#$(OUT_DIR)/wr_smm_son.$(OBJ): $(IN_DIR)/wr_smm_son.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) $(IN_DIR)/wr_smm_son.$(SRC) -o\
#	$(OUT_DIR)/wr_smm_son.$(OBJ)
#
#$(OUT_DIR)/wr_smm_son_utils.$(OBJ): $(IN_DIR)/wr_smm_son_utils.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) $(IN_DIR)/wr_smm_son_utils.$(SRC) -o\
#	$(OUT_DIR)/wr_smm_son_utils.$(OBJ)
#
#$(OUT_DIR)/wr_smm_pdcp.$(OBJ): $(IN_DIR)/wr_smm_pdcp.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR)  $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCSMMILPJ -DLCPJMILPJ -DLCLPJ $(IN_DIR)/wr_smm_pdcp.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_pdcp.$(OBJ)
#
#$(OUT_DIR)/wr_smm_cl.$(OBJ): $(IN_DIR)/wr_smm_cl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR)  $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCSMYSMILYS -DLCYSMILYS -DLCLYS $(IN_DIR)/wr_smm_cl.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_cl.$(OBJ)
#
#$(OUT_DIR)/wr_emm.$(OBJ): $(IN_DIR)/wr_emm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR)  $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCSMYSMILYS -DLCYSMILYS -DLCLYS $(IN_DIR)/wr_emm.$(SRC) -o \
#	$(OUT_DIR)/wr_emm.$(OBJ)
#
#$(OUT_DIR)/wr_ifm_x2ap.$(OBJ): $(IN_DIR)/wr_ifm_x2ap.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_ifm_x2ap.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_ifm_x2ap.$(SRC)
#
#$(OUT_DIR)/wr_ifm_egtp.$(OBJ): $(IN_DIR)/wr_ifm_egtp.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_ifm_egtp.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_ifm_egtp.$(SRC)
#
#$(OUT_DIR)/wr_ifm_rrc.$(OBJ): $(IN_DIR)/wr_ifm_rrc.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_ifm_rrc.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_ifm_rrc.$(SRC)
#
#$(OUT_DIR)/wr_ifm_pdcp.$(OBJ): $(IN_DIR)/wr_ifm_pdcp.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_ifm_pdcp.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_ifm_pdcp.$(SRC)
#
#$(OUT_DIR)/wr_tenb_stats.$(OBJ): $(IN_DIR)/wr_tenb_stats.$(SRC) $(ALL_INC)
#	$(CC)  -o$(OUT_DIR)/wr_tenb_stats.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_tenb_stats.$(SRC)
#
#$(OUT_DIR)/wr_ifm_schd.$(OBJ): $(IN_DIR)/wr_ifm_schd.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_ifm_schd.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_ifm_schd.$(SRC)
#
#$(OUT_DIR)/wr_ifm_rrm.$(OBJ): $(IN_DIR)/wr_ifm_rrm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c -o$(OUT_DIR)/wr_ifm_rrm.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_ifm_rrm.$(SRC)
#$(OUT_DIR)/wr_ifm_son.$(OBJ): $(IN_DIR)/wr_ifm_son.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c -o$(OUT_DIR)/wr_ifm_son.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_ifm_son.$(SRC)
#
#$(OUT_DIR)/wr_emm_son.$(OBJ): $(IN_DIR)/wr_emm_son.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c -o$(OUT_DIR)/wr_emm_son.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_emm_son.$(SRC)
#
#$(OUT_DIR)/wr_ptli.$(OBJ): $(IN_DIR)/wr_ptli.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c -o$(OUT_DIR)/wr_ptli.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_ptli.$(SRC)
#
#$(OUT_DIR)/wr_ifm_s1ap.$(OBJ): $(IN_DIR)/wr_ifm_s1ap.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC) -c -o$(OUT_DIR)/wr_ifm_s1ap.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_ifm_s1ap.$(SRC)
#
#$(OUT_DIR)/wr_ifm_l1.$(OBJ): $(IN_DIR)/wr_ifm_l1.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_ifm_l1.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_ifm_l1.$(SRC)
#
#$(OUT_DIR)/wr_umm_egtp_hdl.$(OBJ): $(IN_DIR)/wr_umm_egtp_hdl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_egtp_hdl.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_egtp_hdl.$(SRC)
#
#$(OUT_DIR)/wr_umm_l1_hdl.$(OBJ): $(IN_DIR)/wr_umm_l1_hdl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_l1_hdl.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_l1_hdl.$(SRC)
#
#$(OUT_DIR)/wr_umm_pdcp_hdl.$(OBJ): $(IN_DIR)/wr_umm_pdcp_hdl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_pdcp_hdl.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_pdcp_hdl.$(SRC)
#
#$(OUT_DIR)/wr_umm_rrc_hdl.$(OBJ): $(IN_DIR)/wr_umm_rrc_hdl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_rrc_hdl.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_rrc_hdl.$(SRC)
#
#$(OUT_DIR)/wr_umm_s1ap_hdl.$(OBJ): $(IN_DIR)/wr_umm_s1ap_hdl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_s1ap_hdl.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_s1ap_hdl.$(SRC)
#
#$(OUT_DIR)/wr_umm_sch_hdl.$(OBJ): $(IN_DIR)/wr_umm_sch_hdl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_sch_hdl.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_sch_hdl.$(SRC)
#
#$(OUT_DIR)/wr_umm_x2ap_hdl.$(OBJ): $(IN_DIR)/wr_umm_x2ap_hdl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_x2ap_hdl.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_x2ap_hdl.$(SRC)
#
#$(OUT_DIR)/wr_umm_x2ap_msg.$(OBJ): $(IN_DIR)/wr_umm_x2ap_msg.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_x2ap_msg.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_x2ap_msg.$(SRC)
#
#$(OUT_DIR)/wr_tmr.$(OBJ): $(IN_DIR)/wr_tmr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_tmr.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_tmr.$(SRC)
#
##$(OUT_DIR)/wr_mi.$(OBJ): $(IN_DIR)/wr_mi.$(SRC) $(ALL_INC)
##	$(Q) $(CC)  -o$(OUT_DIR)/wr_mi.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
##	$(IN_DIR)/wr_mi.$(SRC)
#
#$(OUT_DIR)/wr_ptmi.$(OBJ): $(IN_DIR)/wr_ptmi.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_ptmi.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCWRMILWR -DLWLCWRMILWR -DLWLCWR -DSM -DLCLWR \
#	$(IN_DIR)/wr_ptmi.$(SRC)
#
#$(OUT_DIR)/wr_ex_ms.$(OBJ): $(IN_DIR)/wr_ex_ms.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_ex_ms.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -ULCWR -DRG  -DLWLCWR  -DLWLCLWR   -DLCLWR -DSM   \
#	$(IN_DIR)/wr_ex_ms.$(SRC)
#
#$(OUT_DIR)/wr_lwr.$(OBJ): $(IN_DIR)/wr_lwr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_lwr.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLWLCSMMILWR -DSM  -DLCLWR -DLWLCLWR -DLCSMMILWR  \
#	$(IN_DIR)/wr_lwr.$(SRC)
#
#$(OUT_DIR)/wr_umm_initcntsetup.$(OBJ): $(IN_DIR)/wr_umm_initcntsetup.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_initcntsetup.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_initcntsetup.$(SRC)
#
#$(OUT_DIR)/wr_umm_rrcreestab.$(OBJ): $(IN_DIR)/wr_umm_rrcreestab.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_rrcreestab.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_rrcreestab.$(SRC)
#
#$(OUT_DIR)/wr_umm_ctxtmod.$(OBJ): $(IN_DIR)/wr_umm_ctxtmod.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_ctxtmod.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_ctxtmod.$(SRC)
#
#$(OUT_DIR)/wr_emm_anr.$(OBJ): $(IN_DIR)/wr_emm_anr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_anr.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DDG \
#	$(IN_DIR)/wr_emm_anr.$(SRC)
#
#$(OUT_DIR)/wr_emm_ecsfb_anr.$(OBJ): $(IN_DIR)/wr_emm_ecsfb_anr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_ecsfb_anr.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DDG \
#	$(IN_DIR)/wr_emm_ecsfb_anr.$(SRC)
#
#$(OUT_DIR)/wr_umm_x2srcho.$(OBJ): $(IN_DIR)/wr_umm_x2srcho.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_x2srcho.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_x2srcho.$(SRC)
#
#$(OUT_DIR)/wr_umm_x2tgtho.$(OBJ): $(IN_DIR)/wr_umm_x2tgtho.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_x2tgtho.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_x2tgtho.$(SRC)
#
#$(OUT_DIR)/wr_umm_s1tgtho.$(OBJ): $(IN_DIR)/wr_umm_s1tgtho.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_s1tgtho.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_s1tgtho.$(SRC)
#
#$(OUT_DIR)/wr_umm_s1srcho.$(OBJ): $(IN_DIR)/wr_umm_s1srcho.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_s1srcho.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_s1srcho.$(SRC)
#
#$(OUT_DIR)/wr_umm_ho.$(OBJ): $(IN_DIR)/wr_umm_ho.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_ho.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_ho.$(SRC)
#
#$(OUT_DIR)/wr_umm_csfbupdtcell.$(OBJ): $(IN_DIR)/wr_umm_csfbupdtcell.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_csfbupdtcell.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_csfbupdtcell.$(SRC)
#
#$(OUT_DIR)/wr_umm_csfb.$(OBJ): $(IN_DIR)/wr_umm_csfb.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_csfb.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_csfb.$(SRC)
#
#$(OUT_DIR)/wr_umm_ecsfb.$(OBJ): $(IN_DIR)/wr_umm_ecsfb.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_ecsfb.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_ecsfb.$(SRC)
#
#$(OUT_DIR)/wr_diag.$(OBJ): $(IN_DIR)/wr_diag.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_diag.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_diag.$(SRC)
#
#
#
#$(OUT_DIR)/wr_smm_diag_hdl.$(OBJ): $(IN_DIR)/wr_smm_diag_hdl.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_smm_diag_hdl.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_smm_diag_hdl.$(SRC)
#
#$(OUT_DIR)/wr_umm_locrpt.$(OBJ): $(IN_DIR)/wr_umm_locrpt.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_locrpt.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_locrpt.$(SRC)
#
#$(OUT_DIR)/wr_kpi.$(OBJ): $(IN_DIR)/wr_kpi.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_kpi.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_kpi.$(SRC)
#
#$(OUT_DIR)/wr_alarm.$(OBJ): $(IN_DIR)/wr_alarm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_alarm.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_alarm.$(SRC)
#
#$(OUT_DIR)/wr_emm_s1_flex.$(OBJ): $(IN_DIR)/wr_emm_s1_flex.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_s1_flex.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_emm_s1_flex.$(SRC)
#
#$(OUT_DIR)/wr_emm_cnm.$(OBJ): $(IN_DIR)/wr_emm_cnm.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_cnm.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_emm_cnm.$(SRC)
#
#$(OUT_DIR)/wr_umm_csfb_geran.$(OBJ): $(IN_DIR)/wr_umm_csfb_geran.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_csfb_geran.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_csfb_geran.$(SRC)
#
#$(OUT_DIR)/wr_umm_drx.$(OBJ): $(IN_DIR)/wr_umm_drx.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_drx.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_drx.$(SRC)
#
#$(OUT_DIR)/wr_smm_tmr.$(OBJ): $(IN_DIR)/wr_smm_tmr.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -I$(SS_DIR)  $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) -DLCSMYSMILYS -DLCYSMILYS -DLCLYS $(IN_DIR)/wr_smm_tmr.$(SRC) -o \
#	$(OUT_DIR)/wr_smm_tmr.$(OBJ)
#
#$(OUT_DIR)/wr_umm_lteadv.$(OBJ): $(IN_DIR)/wr_umm_lteadv.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_umm_lteadv.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_umm_lteadv.$(SRC)
#
#$(OUT_DIR)/wr_emm_lteadv.$(OBJ): $(IN_DIR)/wr_emm_lteadv.$(SRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/wr_emm_lteadv.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	$(IN_DIR)/wr_emm_lteadv.$(SRC) 
#
#
#ifeq ($(BLDENV),lnx_e2e_bc)
#
#$(OUT_DIR)/hmac.$(OBJ): ../../mt/security/hmac.$(SECSRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/hmac.$(OBJ) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	../../mt/security/hmac.$(SECSRC)
#$(OUT_DIR)/hmacsha256.$(OBJ1): ../../mt/security/hmacsha256.$(SECSRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/hmacsha256.$(OBJ) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	../../mt/security/hmacsha256.$(SECSRC)
#$(OUT_DIR)/mp.$(OBJ): ../../mt/security/mp.$(SECSRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/mp.$(OBJ) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	../../mt/security/mp.$(SECSRC)
#$(OUT_DIR)/endianness.$(OBJ): ../../mt/security/endianness.$(SECSRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/endianness.$(OBJ) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	../../mt/security/endianness.$(SECSRC)	
#$(OUT_DIR)/sha256.$(OBJ): ../../mt/security/sha256.$(SECSRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/sha256.$(OBJ) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	../../mt/security/sha256.$(SECSRC)
#$(OUT_DIR)/sha2k32.$(OBJ): ../../mt/security/sha2k32.$(SECSRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/sha2k32.$(OBJ) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	../../mt/security/sha2k32.$(SECSRC)
#endif
#ifeq ($(BLDENV),lnx_e2e_bc_blog)
#$(OUT_DIR)/hmac.$(OBJ1): ../../mt/security/hmac.$(SECSRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/hmac.$(OBJ1) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	../../mt/security/hmac.$(SECSRC)
#$(OUT_DIR)/hmacsha256.$(OBJ1): ../../mt/security/hmacsha256.$(SECSRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/hmacsha256.$(OBJ1) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	../../mt/security/hmacsha256.$(SECSRC)
#$(OUT_DIR)/mp.$(OBJ1): ../../mt/security/mp.$(SECSRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/mp.$(OBJ1) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	../../mt/security/mp.$(SECSRC)
#$(OUT_DIR)/endianness.$(OBJ1): ../../mt/security/endianness.$(SECSRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/endianness.$(OBJ1) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	../../mt/security/endianness.$(SECSRC)	
#$(OUT_DIR)/sha256.$(OBJ1): ../../mt/security/sha256.$(SECSRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/sha256.$(OBJ1) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	../../mt/security/sha256.$(SECSRC)
#$(OUT_DIR)/sha2k32.$(OBJ1): ../../mt/security/sha2k32.$(SECSRC) $(ALL_INC)
#	@echo -e "Compiling $(COLOR) $< $(REVERT_COLOR)..."
#	$(Q) $(CC)  -o$(OUT_DIR)/sha2k32.$(OBJ1) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \
#	../../mt/security/sha2k32.$(SECSRC)
#endif
#$(OUT_DIR)/libperflnxwr.a:$(wrPerfLnxOBJS)
#	 $(AR) -cr $(OUT_DIR)/libperflnxwr.a $(wrPerfLnxOBJS)	

#$(OUT_DIR)/libperflnxwruu.a:$(wrPerfLnxOBJSUU)
#	$(AR) -cr $(OUT_DIR)/libperflnxwr.a $(wrPerfLnxOBJSUU)	

#$(OUT_DIR)/libwrtenbapp_ms.a:$(wrE2eLnxOBJS_ms) $(wrE2eLnxOBJS_ms1)
#	$(AR) -cr $(OUT_DIR)/libe2elnxwr_ms.a $(wrE2eLnxOBJS_ms)	$(wrE2eLnxOBJS_ms1)

#ifeq (${BLDENV},lnx_e2e_ms)
#$(OUT_DIR)/libe2elnxwr_ms.a:$(wrE2eLnxOBJS_ms) $(wrE2eLnxOBJS_ms1)
#	$(AR) -cr $(OUT_DIR)/libe2elnxwr_ms.a $(wrE2eLnxOBJS_ms) $(wrE2eLnxOBJS_ms1)
#else
#ifeq ($(BLDENV),lnx_e2e_bc)
#else
#$(OUT_DIR)/libe2elnxwr.a:$(wrE2eLnxOBJS_ms) $(wrE2eLnxOBJS_ms1)
#	$(AR) -cr $(OUT_DIR)/libe2elnxwr.a $(wrE2eLnxOBJS_ms) $(wrE2eLnxOBJS_ms1)
#endif
#endif

#$(OUT_DIR)/libperfcavwr.a:$(wrPerfCavOBJS)
#	 $(AR) -cr $(OUT_DIR)/libperfcavwr.a $(wrPerfCavOBJS)	
#
#$(OUT_DIR)/libperfcavwruu.a:$(wrPerfCavOBJSUU)
#	$(AR) -cr $(OUT_DIR)/libperfcavwr.a $(wrPerfCavOBJSUU)	
#
#$(OUT_DIR)/libe2ecavwr.a:$(wrE2eCavOBJS)
#	 $(AR) -cr $(OUT_DIR)/libe2ecavwr.a $(wrE2eCavOBJS)	

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
ifeq ($(BIN_LOG),YES)
$(LIB_DIR)/libwr.a:$(C_OBJS) $(C_WO_PED_OBJS)
	@echo -e "Creating log DB $(COLOR)$(LOG_DIR)/wrLog.db $(REVERT_COLOR)"
	$(Q)cat $(DB_FILES) > $(LOG_DIR)/wrLog.db
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libwr.a $(C_OBJS) $(C_WO_PED_OBJS)
else
$(LIB_DIR)/libwr.a:$(C_OBJS) $(C_WO_PED_OBJS)
	@echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
	$(Q)ar -cr $(LIB_DIR)/libwr.a $(C_OBJS)	$(C_WO_PED_OBJS)
endif

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	@echo $(OAM_ENABLE)
	@echo -e "$(COLOR_RED)Cleaning TeNB application$(REVERT_COLOR)"
	$(Q)\rm -f $(LIB_DIR)/libwr.a $(C_OBJS) $(C_WO_PED_OBJS)

