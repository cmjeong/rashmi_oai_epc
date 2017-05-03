
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_init.c

     Sid:      fc_smm_init_t2k.c@@/main/TeNB_Main_BR/13 - Mon Aug 11 16:52:17 2014

     Prg:      Sriky 

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="SMM";
static int RLOG_FILE_ID=263;
static int RLOG_MODULE_ID=2;
#include<errno.h>
#include<signal.h>
#include "wr.h"
#include "wr_emm.h"
#include "wr_umm.h"
#include "wr_smm_init.h"
#include "wr_smm_smallcell.h"
#include "cm_os.h"       /* common hashing */
#include "cm_os.x"
#include "ss_diag.h"      /* Common logging header */
/* LTE_ADV starts */
#include "wr_cmn.h"
/* LTE_ADV ends */
#include <stdlib.h>
#ifdef LTE_L2_MEAS
#include "lpj.h"
#include "lkw.h"
#include "lrg.h"
#include "wr_dam.h"
#endif/*LTE_L2_MEAS*/

#include "wr_kpiIds.h"
#include "wr_kpi.h"
#include "mt_4gmx.x"
#if defined (PDCP_RLC_DL_RBUF) || defined(MAC_RLC_UL_RBUF) 
#include "kwu.h"
#include "kwu.x"
#include "rgu.h"
#include "rgu.x"
#include "ss_rbuf.h"
#include "ss_rbuf.h"
#include "ss_rbuf.x"
#endif

#include "tip.h"
#include "tip_cmn.h"

/** print software version **/
EXTERN const char * wrGetSwVersion(Void);
EXTERN const char * wrGetSwVersion_LL2(Void);
EXTERN const char * wrGetSwVersion_UL2(Void);
#ifdef TIP_L3
EXTERN U8 tipIsL3Ready;
#endif
#ifdef SRS_PHY
U8 isStartDl = 0;
extern void start_dl();
#endif

#define PRINT_STR(x)   #x
#include "wr_msm_common.h"
extern MsmLteeNodeBparams lteeNodeBparams[WR_MAX_CELLS];
#ifdef WR_RSYS_OAM
EXTERN Void SmAppTst(Void);
EXTERN Void MsmConfigComplete(Void);
EXTERN Void MsmShutDownAck(Void);
PRIVATE void *wrSmmAppTstCaller(void *arg);
PRIVATE void SCreateSmmAppTst(void);
PRIVATE const char* wrSmmPrintSmmEvent(U8 event);

EXTERN S32 ssCheckAndAddMemoryRegionMap ARGS((pthread_t  threadId,
                                               Region region));
#endif
#ifdef WR_WATCHDOG
EXTERN Void wrRegWatchDog(Void);
#endif

EXTERN Void ysPhyCommInit(Void);
EXTERN Void ssMlogInit(Void);
EXTERN Void ssMemlogInit(Void);
EXTERN U8   macCfgInst;
PUBLIC TstTkn    tkn;
#ifdef REM_ENABLE
void initNmmTask(void);
#endif
EXTERN S32 l3TipSockFd;
EXTERN S32 Ll2TipSockFd;
EXTERN S32 Ul2TipSockFd;

sem_t smOamStartSema;
#define WR_SMM_VALIDATE_CFG_PARAM(_param, _min, _max)\
{\
   if(_min > _param || _param > _max)\
   {\
      RLOG2(L_ERROR, " Invalid parameter value %s = %d ", #_param, _param);\
      RLOG2(L_ERROR, " Param should be min=%d, max=%d ", _min, _max);\
      RETVALUE(RFAILED);\
   }\
}

PUBLIC U32 LL2_IP_ADDR;
PUBLIC U32 LL2_PORT_TIP;
PUBLIC U32 UL2_IP_ADDR;
PUBLIC U32 UL2_PORT_TIP;
PUBLIC U32 L3_IP_ADDR;
PUBLIC U32 L3_PORT_TIP;
PUBLIC U32 UL2_GTP_IP_ADDR;

PUBLIC U16 proc_Id;

PUBLIC    SmCb smCb;
PUBLIC    SmCfgCb smCfgCb;   
#ifdef LTE_L2_MEAS
PUBLIC    U32 glbMacMeasFlag;
#endif
PUBLIC U16 wrSmMaxBufLen[SS_DIAG_MAX_CIRC_BUF];

#ifdef E_TM
PUBLIC Void wrSmHdlCellCfgEvent(U8 event);
EXTERN U8 etmCellState;
#endif

#ifdef TENB_STATS
PUBLIC Void TSInfCfgCL (Void);
#endif

PUBLIC Void smBuildShutRestart(Void);
PRIVATE Void smBuildFullRstctrl(Void); 
#if ((!defined(TIP_LOWER_L2)) && (!defined(TIP_UPPER_L2)))
#if defined (PDCP_RLC_DL_RBUF) || defined(MAC_RLC_UL_RBUF) 
PRIVATE S16 t2kRbufInit(Void); 
#endif
#endif
PUBLIC Void wrSmmSetBandwidth(U32 freqBandwidth,U8  loopCnt);

EXTERN S16 wrEmmSndSchdReCfgReq ARGS((U32  cellId,U32  minDlResNonCsg, U32 minUlResNonCsg));
EXTERN S16 smSndCliRmuProtModCellCfg ARGS((U8 cellId, U16 maxCsgUEs, U16 maxNonCsgUEs));
/* CSG_DEV */
void flushData(int sig);
/* unused variable */
/* PRIVATE U8 wrLogEnbFirstTime = FALSE; */

#ifdef WR_TEST_CODE
/* S1 CLI variables */
U8 wrTgrMmeCfgUpdFail = FALSE;
U8 wrTgrEnbErrInd     = FALSE;
U8 wrDntRspMmeCfgUpd  = FALSE;
U8 wrTgrEnbCfgUpdRtx  = FALSE;
U8 wrTgrS1SetupRtx    = FALSE;

/* X2 CLI variables */
U8 wrTgrX2SetupFail = FALSE;
U8 wrTgX2SetupFailWoTW = FALSE;
U8 wrDntRspX2Setup = FALSE;
U8 wrTgrX2CfgUpdFail = FALSE;
U8 wrTgrX2CfgUpdFailWoTW = FALSE;
U8 wrDntRspX2CfgUpd = FALSE;
U8 wrDntRspX2Reset = FALSE;
U8 wrTrgX2ErrInd = FALSE;

U8 wrTrgNasNonDlvrInd = FALSE;

/* RRC CLI variables */
U8 wrTrgRrcConTO = FALSE;
U8 wrTrgRrcConRelTO = FALSE;
U8 wrTrgUeCapTO = FALSE;
U8 wrTrgSecTO = FALSE;
U8 wrTrgRrcReConTO = FALSE;
U8 wrTrgRrcRestTO = FALSE;  
#ifdef WR_TEST_CODE
#ifdef LTE_ADV
U16 wrCliPCellId = 0;
WrCrnti wrCliUeCrnti = 0;
U8 wrCliUeIdx = 0;
U16 wrCliSCellId = 0;
#endif
#endif


U8        wrCmdArgs[MAXCMDLEN];
U16       wrCmdLen;
EXTERN U8 wrTgrEnbOverLoad;
#ifdef WR_CLI_TARGET_BOARD
PRIVATE S16 smCliRecvTsk ARGS((Pst *pst, Buffer *mBuf));
#endif

PUBLIC Keys  wrCliSecArgKey[] = {
   {"on",            0},
   {"off",           1},
   {"enb",           2},
   {"dis",           3},
   {"",  MATCH_FAILED }
};

/* LTE_ADV starts */
PUBLIC Keys  wrCliLteaArgKey[] = {
   {"abs",            RGR_ABS},
   {"sfr",            RGR_SFR},
   {"dsfr",           RGR_DSFR},
   {"re",             RGR_RE},
#ifdef LTE_ADV
   {"scellrel",       RGR_SCELLRELEASE},
   {"scelladd",       RGR_SCELLADD},
   {"scellact",       RGR_SCELLACT},
   {"scelldeact",     RGR_SCELLDEACT},
#endif
   {"",  MATCH_FAILED  }
};
/* LTE_ADV ends */

PUBLIC Keys  wrDbgLyrKey[] = {
   {"app",           1 },
   {"s1ap",          2 },
   {"sctp",          3 },
   {"tucl",          4 },
   {"x2ap",          5 },
   {"egtp",          6 },
   {"rrc",           7 },
   {"rlc",           8 },
   {"pdcp",          9 },
   {"mac",           10 },
   {"cl",            11 },
   {"cplane",        12 },
   {"all",           13 },
   {"",    MATCH_FAILED }     
};

#ifdef PHY_ERROR_LOGING
PUBLIC    SmUlAllocInfoCb smUlAllocInfoCb;   
#endif

PUBLIC Keys  wrCliMenuKey[] = {
   {"help",                      0 },
   {"enbovld",                   1 },
   {"snds1cfgupd",               2 },
   {"snds1cfgupdfail",           3 },
   {"dbgp",                      4 },
   {"s1partrst",                 5 },
   {"s1fullrst",                 6 },
   {"sndx2setupfail",            7 },
   {"dntrspx2setup",             8 },
   {"sndx2cfgupdfail",           9 },
   {"dntrspx2cfgupd",           10 },
   {"dntrspx2rst",              11 },
   {"sndx2errind",              12 },
   {"sndx2rst",                 13 },
   {"memstatus",                14 },
   {"sndrabrls",                15 },
   {"sndenberrind",             16 },
   {"sndnasnondelind",          17 },
   {"dntrsps1cfgupd",           18 },
   {"sndendcfgupdrx",           19 },
   {"snds1setuprx",             20 },
   {"empty",                    21 },
   {"empty",                    22 },
   {"drprrcconnsetupcmplt",     23 },
   {"drprrcrelcfm",             24 },
   {"drpuecapinfo",             25 },
   {"drpseccmplt",              26 },
   {"drprrcrecfgcmlpt",         27 },
   {"drprrcreestabcmplt",       28 },
   {"enbportlog",               29 },
   {"trgRrcRestTO",             30 },
   {"loadInd",                  31 },
   {"printNrInfo",              32 },
   {"macstats",                 33 },
   {"phylogging",               34 },
#ifdef E_TM 
   {"etmtest",                  35 },
#endif /* E_TM */
   {"ipchange",                 36 },
/* LTE_ADV starts */
   {"ltea",                     37 },
/* LTE_ADV ends */
   /* CSG_DEV */
   {"csgprntcellinfo",          38 },
   {"csgprntnbrinfo",           39 },
   {"",               MATCH_FAILED }
};
#endif

PUBLIC S8 *wrCfgTagLst[MAX_CFG_PARAM] = {
   "WR_TAG_CELL_ID",
   "WR_TAG_NOS_OF_CELLS",
   "WR_TAG_DUP_MODE",
   "WR_TAG_MAX_UE_SUPPORT",
   "WR_TAG_MAX_AVG_GBRPRB_USAGE",
   "WR_TAG_MCC_0",
   "WR_TAG_MCC_1",
   "WR_TAG_MCC_2",
   "WR_TAG_MNC_0",
   "WR_TAG_MNC_1",
   "WR_TAG_MNC_2",
   "WR_TAG_TA_CODE",
   "WR_TAG_FREQ_BAND_IND",
   "WR_TAG_ENB_IP_ADDR",
   "WR_TAG_ENB_IP_ADDR_IPV6",
   "WR_TAG_PCI_SELECT_TYPE",
   "WR_TAG_PRACH_SELECT_TYPE",
   "WR_TAG_EARFCN_SELECT_TYPE",
   "WR_TAG_PCI_LIST",
   "WR_TAG_DL_EARFCN_LIST",
   "WR_TAG_UL_EARFCN_LIST",
   "WR_TAG_ROOTSEQ_IDX_LIST",
   "WR_TAG_PRACHCFG_IDX_LIST",
   "WR_TAG_ZERO_CORR_ZONE_CFG_LIST",
   "WR_TAG_PRACH_FREQ_OFFSET_LIST",
   "WR_TAG_ROOTSEQ_IDX",
   "WR_TAG_ZERO_CORR_ZONE_CFG",
   "WR_TAG_PRACH_FREQ_OFFSET",
   "WR_TAG_NO_OF_MME_INFO",
   "WR_TAG_MME_INFO",
   "WR_TAG_NO_OF_MME_INFO_IPV6",
   "WR_TAG_MME_INFO_IPV6",
   "WR_TAG_HI_DBG",
   "WR_TAG_SB_DBG",
   "WR_TAG_SZ_DBG",
   "WR_TAG_EG_DBG",
   "WR_TAG_WR_DBG",
   "WR_TAG_NH_DBG",
   "WR_TAG_KW_DBG",
   "WR_TAG_RG_DBG",
   "WR_TAG_YS_DBG",
   "WR_TAG_SM_DBG",
   "WR_TAG_INACTIVITY_TIMER_VAL",
   "WR_TAG_MAX_EXPIRY"
#ifdef LTE_HO_SUPPORT
      ,
   "WR_TAG_CZ_DBG",
   "WR_TAG_X2_PREP_TMR",
   "WR_TAG_X2_OVRALL_TMR",
   "WR_TAG_NO_OF_BRDCST_PLMN",
   "WR_TAG_PLMN_ID_LST",
   "WR_TAG_NO_OF_NGH_INFO",
   "WR_TAG_NO_OF_GU_GRP",
   "WR_TAG_S1_PREP_TMR",
   "WR_TAG_S1_OVRALL_TMR",
   "WR_TAG_NO_OF_NGH_CFG",
   "WR_TAG_NGH_CELL_CFG",
   "WR_TAG_NO_OF_NGH_CFG_IPV6",
   "WR_TAG_NGH_CELL_CFG_IPV6",
   "WR_TAG_MEAS_CFG_ENB",
   "WR_TAG_RRM_RNTI_STRT",
   "WR_TAG_MAX_RRM_RNTIS",
   "WR_TAG_MAC_RNTI_STRT",
   "WR_TAG_MAX_MAC_RNTIS",
   "WR_TAG_RRM_NO_OF_DED_PREMBL",
   "WR_TAG_RRM_DED_PREMBL_STRT",
   "WR_TAG_MAC_NO_OF_PREMBL",
   "WR_TAG_A1_RSRP_THRSHLD_VAL",
   "WR_TAG_A2_RSRP_THRSHLD_VAL",
   "WR_TAG_INTRA_A5_RSRP_THRSD1_VAL",
   "WR_TAG_INTRA_A5_RSRP_THRSD2_VAL",
   "WR_TAG_INTER_A5_RSRP_THRSD1_VAL",
   "WR_TAG_INTER_A5_RSRP_THRSD2_VAL",
   "WR_TAG_INTRA_HO_A3_OFFSET",
   "WR_TAG_INTRA_ANR_A3_OFFSET",
   "WR_TAG_INTER_ANR_A5_RSRP_THRSD1_VAL",  
   "WR_TAG_INTER_ANR_A5_RSRP_THRSD2_VAL",  
   "WR_TAG_ANR_REPORT_CFG_VAL",
   "WR_TAG_ANR_CELL_VALID_AGE_VAL",
   "WR_TAG_HO_REPORT_CFG_VAL",/*rsrq_ho*/
   "WR_TAG_RSRQ_THRSHLD_VAL",
   "WR_TAG_ANR_EPOC_TMR_VAL_IN_SECS",
   "WR_TAG_ANR_TRICE_INTV_COUNT",
   "WR_TAG_UTRA_B2_RSRP_THRSD1_VAL",
   "WR_TAG_UTRA_FDD_B2_RSCP_THRSD2_VAL",
   "WR_TAG_UTRA_TDD_B2_RSCP_THRSD2_VAL",
   "WR_TAG_S_MEASURE_VAL",
   "WR_TAG_INTRA_TTT_VAL",
   "WR_TAG_INTRA_HYTERISIS",
   "WR_TAG_PCI_VAL",
   "WR_TAG_DL_NUM_UE_PER_TTI",
   "WR_TAG_UL_NUM_UE_PER_TTI",
   "WR_TAG_DL_SCHD_TYPE",
   "WR_TAG_UL_SCHD_TYPE",
   "WR_TAG_DLFS_SCHD_TYPE",
   "WR_TAG_PFS_DL_TPT_COEFFICIENT",
   "WR_TAG_PFS_DL_FAIRNESS_COEFFICIENT",
   "WR_TAG_PFS_UL_TPT_COEFFICIENT",
   "WR_TAG_PFS_UL_FAIRNESS_COEFFICIENT",
   "WR_TAG_TM_AUTO_CONFIG",
   "WR_TAG_PREFERRED_TM",
   "WR_TAG_MAX_X2_PEERS",
   "WR_TAG_X2_TIME_TO_WAIT",
   "WR_TAG_UE_HO_ATTACH_TMR",
   "WR_TAG_SCTP_SRVC_TYPE",
   "WR_TAG_OP_MODE",
   "WR_TAG_PERIOD",
   "WR_TAG_DL_EARFCN",
   "WR_TAG_UL_EARFCN",
   "WR_TAG_END_MARKER_TIMER_VAL"
#endif
#ifdef OAM_PH0_SUPPORT
      ,
   "WR_TAG_S1_RESET_TMR",
   "WR_TAG_X2_RESET_TMR"
#endif
#ifdef TENB_AS_SECURITY
      ,
   "WR_TAG_AS_PRI_INTG_ALGO_LST",
   "WR_TAG_AS_PRI_CIPH_ALGO_LST"
#endif
      ,
   "WR_TAG_DIAG_TUCL",
   "WR_TAG_DIAG_S1AP",
   "WR_TAG_DIAG_EGTP",
   "WR_TAG_DIAG_APP",
   "WR_TAG_DIAG_LTERRC",
   "WR_TAG_DIAG_LTERLC",
   "WR_TAG_DIAG_LTEPDCP",
   "WR_TAG_DIAG_LTECL",
   "WR_TAG_DIAG_LTEMAC",
   "WR_TAG_DIAG_X2AP",
   "WR_TAG_DIAG_SCTP"
#ifdef PHY_ERROR_LOGING
      ,
   "WR_TAG_UL_ENABLE_TIME"
#endif
    ,
   "WR_TAG_NO_OF_UTRA_FDD_NGH_CFG",
   "WR_TAG_NGH_UTRA_FDD_CELL_CFG",
   "WR_TAG_NO_OF_UTRA_TDD_NGH_CFG",
   "WR_TAG_NGH_UTRA_TDD_CELL_CFG",
   "WR_TAG_NUM_EUTRA_FREQ",
   "WR_TAG_EUTRA_FREQ_CFG",
   "WR_TAG_NUM_UTRA_FDD_FREQ",
   "WR_TAG_UTRA_FDD_FREQ_CFG",
   "WR_TAG_NUM_UTRA_TDD_FREQ",
   "WR_TAG_UTRA_TDD_FREQ_CFG",
   "WR_TAG_NUM_CDMA_1XRTT_BAND_CLS",
   "WR_TAG_CDMA_1XRTT_BAND_CLS",
   "WR_TAG_NUM_CDMA_1XRTT_NEIGH_FREQ",
   "WR_TAG_CDMA_1XRTT_NEIGH_FREQ",
   "WR_TAG_NUM_CDMA_1XRTT_NEIGH_CELL",
   "WR_TAG_CDMA_1XRTT_NEIGH_CELL",
   "WR_TAG_CSFB_UTRA_CFG_VAL",
   "WR_TAG_CSFB_CDMA_CFG_VAL",
   "WR_TAG_ECSFB_CFG_VAL",
   "WR_TAG_DUAL_RX_SUPPORTED",
   "WR_TAG_MAX_DL_UE_PER_TTI",
   "WR_TAG_MAX_UL_UE_PER_TTI",
   "WR_TAG_DEFAULT_PAGING_CYCLE",
   "WR_TAG_DEFAULT_PCCH_CFG_NB",
   "WR_TAG_SCTP_RTO_MIN",
   "WR_TAG_SCTP_RTO_MAX",
   "WR_TAG_SCTP_RTO_INITIAL",
   "WR_TAG_SCTP_HRTBEAT_INTERVAL",
   "WR_TAG_ABS_A3_OFFSET",
   "WR_TAG_PICO_OFFSET",
   "WR_TAG_ABS_PATTERN_TYPE",
   "WR_TAG_ABS_PATTERN",
   "WR_TAG_ABS_LOAD_PERIODICITY",
   "WR_TAG_SFR_START_RB",
   "WR_TAG_SFR_END_RB",
   "WR_TAG_SFR_POWER_LOW",
   "WR_TAG_SFR_POWER_HIGH",
   "WR_TAG_DRX_QCI_SUPPORT_ENABLED",
   "WR_TAG_DRX_ENABLED",
   "WR_TAG_DRX_INACTIVITY_TMR",
   "WR_TAG_DRX_RETX_TMR",
   "WR_TAG_DRX_LONG_CYCLE_GBR",
   "WR_TAG_DRX_LONG_CYCLE_NON_GBR",
   "WR_TAG_ANR_DRX_LONG_CYCLE",
   "WR_TAG_ANR_DRX_ON_DURATION_TMR",
   "WR_TAG_ANR_DRX_INACTIVITY_TMR" 
#ifdef E_TM
      ,
   "WR_TAG_BOOT_MODE",
   "WR_TAG_ETM_ID"
#endif /* E_TM */
      ,
   "WR_TAG_BANDWIDTH",
   "WR_TAG_PWS_ETWS_CMAS_CNTRL",
   "WR_TAG_TDD_ULDL_CFG_MODE",
   "WR_TAG_TDD_SPCL_SF_CONFIG"
#ifdef WR_WATCHDOG
      ,
   "WR_TAG_WATCHDOG_SOFT_LIMIT",
   "WR_TAG_WATCHDOG_HARD_LIMIT"
#endif /* WR_WATCHDOG */
   ,
   "WR_TAG_INT_FREQ_MEAS_GAP", /* Measurement gap configuration */
   "WR_TAG_ANR_MEAS_GAP_CONFIG",   
   "WR_TAG_SRC_HO_CANCEL_TMR",
   "WR_TAG_LOG_PATH", 
   "WR_TAG_LOG_FILE",  
   "WR_TAG_LOG_MAX_FILES",
   "WR_TAG_LOG_FILESIZE_LIMIT", 
   "WR_TAG_LOG_LEVEL", 
   "WR_TAG_LOG_MASK",
   "WR_TAG_LOG_PORT",
   "WR_TAG_LOG_REMOTE_LOGGING",
   "WR_TAG_LOG_CIRBUF_SIZE",
   "WR_TAG_LOG_COREDUMP_FLAG",
   "WR_TAG_RRM_SR_PRDCTY",
   "WR_TAG_RRM_CQI_PRDCTY",
   "WR_TAG_RRM_NUM_SR_PER_TTI",
   "WR_TAG_RRM_NUM_CQI_PER_TTI",
   "WR_TAG_RRM_N1_PUCCH",
   "WR_TAG_SPS_ENABLE_FLAG",
   "WR_TAG_DL_NUM_SPS_UE_PER_TTI",
   "WR_TAG_UL_NUM_SPS_UE_PER_TTI",
   "WR_TAG_MAX_SPS_RB",
   "WR_TAG_DSCP_ENABLE",
   "WR_TAG_QCI_DSCP_MAP",
   "WR_TAG_DL_QCI_SCHD_WGT",
   "WR_TAG_UL_QCI_SCHD_WGT",
   "WR_TAG_CSG_CSG_ID",
   "WR_TAG_CSG_ACCESS_MODE",
   "WR_TAG_CSG_CSG_PCI_START",
   "WR_TAG_CSG_CSG_PCI_RANGE",
   "WR_TAG_CSG_SMCELL_PCI_START",
   "WR_TAG_CSG_SMCELL_PCI_RANGE",
   "WR_TAG_CSG_HENB_NAME",
   "WR_TAG_MAX_CSG_UES",
   "WR_TAG_MAX_NON_CSG_UES",
   "WR_TAG_MIN_DL_RSRC_FOR_NON_CSG",
   "WR_TAG_MIN_UL_RSRC_FOR_NON_CSG",
   "WR_TAG_RIM_CFG",
   "WR_TAG_NUM_GERAN_NEIGH_FREQ",  
   "WR_TAG_GERAN_NEIGH_FREQ",
   "WR_TAG_NUM_GERAN_NEIGH_CELL",
   "WR_TAG_GERAN_NEIGH_CELL",
   "WR_TAG_GERAN_MEAS_CFG",
   "WR_TAG_CELL_PMAX",
   "WR_TAG_CNM_ENABLED",
   "WR_TAG_CNM_BOARD_TYPE",
   "WR_TAG_TA_TMR_CMN",
   "WR_TAG_TA_TMR_DED",
   "WR_TAG_CELL_SIZE_TYPE",
   "WR_TAG_ARP_EMER_SERV", /* ARP for Emergency Bearers */
   "WR_TAG_DCFI_ENABLE",
   "WR_TAG_CFI",
   "WR_TAG_GRP_PUCCH_PWR_CTRL_ENABLE",
   "WR_TAG_GRP_PUSCH_PWR_CTRL_ENABLE",
   "WR_TAG_LTE_PUCCH_PWR_FMT3A_ENABLE",
   "WR_TAG_LTE_PUSCH_PWR_FMT3A_ENABLE",
   "WR_TAG_DUAL_RX_TX_SUPPORTED", /*RRC Rel 10 Upgrade*/
   "WR_TAG_GERAN_B2_RED_RSRP_THRSD1_VAL",
   "WR_TAG_GERAN_B2_RED_THRSD2_VAL",
   "WR_TAG_GERAN_B2_HO_RSRP_THRSD1_VAL",
   "WR_TAG_GERAN_B2_HO_THRSD2_VAL",
   "WR_TAG_NUM_PRB_RPTS",
   "WR_TAG_PRB_RPT_INTERVAL",
   "WR_TAG_SRS_ENABLE",
   "WR_TAG_SRS_PERIODICITY",
   "WR_TAG_SRS_CELL_BANDWIDTH",
   "WR_TAG_SRS_CELL_SUBFRAME_CFG",
   "WR_TAG_SRS_CELL_ACKNACK_SIMTX",
   "WR_TAG_SRS_CELL_MAX_UPPTS",
   "WR_TAG_SRS_UE_BANDWIDTH",
   "WR_TAG_SRS_UE_HOPPING_BW"
#ifdef RSYS_WIRESHARK
      ,
   "WR_TAG_WIRESHARK_PORT",/* to send Logs to wireshark */
   "WR_TAG_WIRESHARK_DST_IP_ADDR", /* to send Logs to wireshark */
   "WR_TAG_RRC_LOG_ENABLE" /* to send Logs to wireshark */
#endif
      ,
   "WR_TAG_RSYS_TPM_TGT_RSRP",
   "WR_TAG_RSYS_TPM_ATTN_CONST_IDX",
   "WR_TAG_RSYS_TPM_MIN_RSRP",
   "WR_TAG_RSYS_TPM_MAX_RSRP",
   "WR_TAG_NUM_TX_ANTENNA"
#ifdef LTE_ADV
    ,
   "WR_TAG_ENABLE_CA", 
   "WR_TAG_A4_RSRP_THRSHLD_VAL", //suhas_sprint12
   "WR_TAG_MEAS_SCELL_ADD_REL"
#ifdef LTE_ADV_UECAP
   ,
   "WR_TAG_CELL_FREQ_CONTIGUOUS"
#endif /*LTE_ADV_UECAP*/
#endif /*LTE_ADV*/
#ifdef TENB_STATS
      ,
   "WR_TAG_TENB_STATS"
#endif
#ifdef LTE_UNLICENSED
      ,
   "WR_TAG_LTEU_NUM_CELLS",
   "WR_TAG_LTEU_CELL_TYPE",
   "WR_TAG_LTEU_COEXIST_METHOD",
   "WR_TAG_LTEU_ON_PERIOD",
   "WR_TAG_LTEU_CCA_METHOD",
   "WR_TAG_LTEU_ADPT_PRD_TX_ENB",
   "WR_TAG_LTEU_TX_PERIOD",
   "WR_TAG_LTEU_LISTENING_PERIOD",
   "WR_TAG_LTEU_ENERGY_THRESHOLD",
   "WR_TAG_LTEU_SCAN_TIME_PERIOD",
   "WR_TAG_LTEU_ACTIVITY_THRESHOLD",
   "WR_TAG_LTEU_MAX_RSRP",
   "WR_TAG_LTEU_FREQ_CFG"
#endif
      ,
   "WR_TAG_L3_IP",
   "WR_TAG_UL2_IP_LIST",
   "WR_TAG_LL2_IP_LIST",
   "WR_TAG_UL2_EGTP_IP_LIST",
   "WR_TAG_UL2_IP",
   "WR_TAG_LL2_IP",
   "WR_TAG_DUL2_IP",
   "WR_TAG_L3_PORT"

};

/* Chinna:X2ap*/
U16 peerIdLst[WR_SMM_MAX_NBR_ENB]={1,4,5,8,12,15,17,21,24,27,32,36,38,42,44,48};
EXTERN S16 InitDrvrTsk ARGS (( Void));

PRIVATE Void wrSmmInitSmCfgCb
(
Void
)
{
   U8                        cellCnt;
   U8                        idCnt;

   for(cellCnt = 0; cellCnt < wrSmDfltNumCells; cellCnt++)
   {
   for(idCnt = 0;idCnt < WR_SMM_MAX_NBR_ENB; idCnt++)
   {
         //smCfgCb.wrNghCellCfg[cellCnt][idCnt] = NULLP;
      smCfgCb.wrX2apPeerIdLst[idCnt].pres = FALSE;
      smCfgCb.wrX2apPeerIdLst[idCnt].val = peerIdLst[idCnt];
   }
      lteeNodeBparams[cellCnt].lteSctpCfgParams.rtoInitial = 2;
      lteeNodeBparams[cellCnt].lteSctpCfgParams.rtoMin = 1;
      lteeNodeBparams[cellCnt].lteSctpCfgParams.rtoMax = 10;
      lteeNodeBparams[cellCnt].lteSctpCfgParams.heartBeatInterval = 50;    /* Heartbeat timer,5 seconds */
   }
   /* SCTP Heartbeat Param Initialization */
}

#ifdef TIP_L3
pthread_t tmpThrId;

SSTskId rrc_s1ap_app_taskId;

/*
*
*       Fun:   tst
*
*       Desc:  tst entry point. First entry point.
*
*       Ret:   ROK on success, RFAILED on error
*
*       Notes: None
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC S16 tst
(
Void
)
#else
PUBLIC S16 tst(Void)
#endif
{

   struct     sockaddr_in tipSrcAddr;      /* Global Internet address/port */
   S32        tipSockfd;
   U32        ipAddr;
   U16        port;

   /* System tasks that are needed as per the architecture */
#ifndef TIP_L2_L3_SPLIT
   pthread_attr_t attr;
   SSTskId rlc_mac_cl_taskId;
#endif
#ifndef TIP_L3
   SSTskId egtp_dat_app_taskId;
#endif
   SSTskId sctp_taskId;
   SSTskId sm_taskId;
#ifdef TIP_L3
   SSTskId s1ap_taskId;
   SSTskId x2ap_taskId;
   SSTskId rrc_taskId;
#endif
   SSTskId tucl_taskId;
#ifdef WR_CLI_TARGET_BOARD
   Inst dstInst = 1;
   SSTskId cli_taskId;
   Pst  cliPst;
#endif /* WR_CLI_TARGET_BOARD */
#ifdef SPLIT_RLC_DL_TASK
   SSTskId rlc_dl_taskId;
#endif 
   U16 smEvent;
   /* wr002.102: Added trace macro */
   TRC2(tst)

   /**print the software version **/
   printf("\nL3 SOFTWARE VERSION : %s\n", wrGetSwVersion());

   proc_Id = WR_L3_OFFSET;
   SSetProcId(SM_SM_PROC);
#ifndef LTE_ENB_PAL
    ysPhyCommInit();
    ssMlogInit();
    ssMemlogInit();
#endif

   /* To Initialize SmCfg Cb params with default values */
   wrSmmInitSmCfgCb();/* To intialize wrNghCellCfg and SCTP Params */
   /* Read the parameters from the file and copy into global control block */
   if(smWrReadConfigParams() != ROK)
   {
      fprintf(stderr, "Failed to read from file wr_cfg.txt");
      RETVALUE(RFAILED);
   } /* end of if statement */

   if((S32)(tipSockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
   {
      perror("Server-socket() tipSockfd error lol!");
      exit(1);
   }
   
   printf("Tip Socket Creation entered\n");

   l3TipSockFd = tipSockfd;
   ipAddr = htonl(L3_IP_ADDR);
   port   = L3_PORT_TIP;

   cmMemset((U8*)&tipSrcAddr, 0, sizeof(tipSrcAddr));
   tipSrcAddr.sin_family      = AF_INET;
   tipSrcAddr.sin_port        = htons(port);
   tipSrcAddr.sin_addr.s_addr = ipAddr;

   if(bind(tipSockfd, (struct sockaddr *)&tipSrcAddr, 
                              sizeof(struct sockaddr)) == -1)
   {
      perror("Server-bind() error:");
      exit(1);
   }

    InitL3TipSockTsk();
    InitL3DrvrTsk();

   if(fapParameters.lteEnodebIpAddr.ipv4pres == TRUE)
     rlInitLog(CM_TPTADDR_IPV4);
   else if(fapParameters.lteEnodebIpAddr.ipv6pres == TRUE)
     rlInitLog(CM_TPTADDR_IPV6);
   else
   {
      rlInitLog(CM_TPTADDR_IPV4);
   }

#ifdef TIP_L3
//    InitDrvrTsk();
#endif

#ifndef LTE_ENB_PAL
#ifdef SS_MULTICORE_SUPPORT
   {
      /* Two cores, each having one hardware thread */
      SCpuInfo cpuInfo = { 2, 1, {1, 1}};
      SRegCpuInfo(&cpuInfo);
   }
#endif /* SS_MULTICORE_SUPPORT */
#endif
   /*  All the System tasks(threads)  are created with same priority*/
   /* Needs discussion with Team : In order to reduce the number of 
      threads in our system, we are tieing all L3, Iu, CN side to same
      thread(system task). Essentially this will reduce number of 
      threads but impacts parallelism, since application threads involves
      IO operations. */
   SCreateSTsk(32, &rrc_s1ap_app_taskId); 
#ifdef TIP_L3
   sm_taskId = rrc_s1ap_app_taskId;
   SCreateSTsk(32, &s1ap_taskId); 
   x2ap_taskId = s1ap_taskId;
   SCreateSTsk(32, &rrc_taskId); 
   SCreateSTsk(32, &sctp_taskId); 
   tucl_taskId = sctp_taskId;
#else
   sm_taskId = sctp_taskId = egtp_dat_app_taskId = rrc_s1ap_app_taskId;
#ifndef TUCL_TTI_RCV
   SCreateSTsk(32, &tucl_taskId);
#endif
   /* tucl_taskId = egtp_dat_app_taskId; */
#ifdef TUCL_TTI_RCV
   tucl_taskId = rrc_s1ap_app_taskId;
#endif
#endif

#ifndef TIP_L3_UL2_LL2_SPLIT
   SCreateSTsk(32, &egtp_dat_app_taskId);
   /*Pin eGTP-U thread to Core 1.*/
#ifndef LTE_PAL_ENB
#ifdef SS_MULTICORE_SUPPORT
   SSetAffinity(&egtp_dat_app_taskId, SS_AFFINITY_MODE_SPECIFIC, 1, NULLP);
#endif
#endif /* SS_MULTICORE_SUPPORT */
#endif

#ifndef TIP_L2_L3_SPLIT
   SCreateSTsk(PRIOR0, &rlc_mac_cl_taskId);  
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

#ifndef LTE_PAL_ENB
#ifdef SS_MULTICORE_SUPPORT
   SSetAffinity(&rlc_mac_cl_taskId, SS_AFFINITY_MODE_SPECIFIC, 0, NULLP);
#endif /* SS_MULTICORE_SUPPORT */
#endif


#ifdef SPLIT_RLC_DL_TASK
   SCreateSTsk(1, &rlc_dl_taskId);
   SSetAffinity(&rlc_dl_taskId, SS_AFFINITY_MODE_SPECIFIC, 1, NULLP);
#endif 
#endif

#ifndef WR_RSYS_OAM
#ifndef NL
   U8 cellCfgIdx;
   /* CSG_DEV : Validate Configration Parameters */
   for(cellCfgIdx = 0; cellCfgIdx < wrSmDfltNumCells; cellCfgIdx++)
   {
      if(wrSmmEnbValidateConfigParams(cellCfgIdx) != ROK)
      {
         RLOG0(L_ERROR, "Validation of Configuration Parameters Failed");
      flushData(SIGSEGV);
      RETVALUE(RFAILED);
   }
   }
#endif
#endif
#ifndef TIP_L3_UL2_LL2_SPLIT
   /* Create PDCP tasks and attach them 
      to a single system thread */
   if(smPjUlInit(egtp_dat_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "PDCP UL Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
   /* Create RLC/PDCP tasks and attach them 
      to a single system thread */
   if(smPjDlInit(egtp_dat_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "PDCP DL Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
#endif 
#ifndef TIP_L2_L3_SPLIT
   /* Create RLC/PDCP tasks and attach them 
      to a single system thread */
   if(smKwUlInit(egtp_dat_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "RLC UL Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
   /* Create RLC/PDCP tasks and attach them 
      to a single system thread */
#ifdef SPLIT_RLC_DL_TASK
   if(smKwDlInit(rlc_dl_taskId) != ROK)
#else 
   if(smKwDlInit(rlc_mac_cl_taskId) != ROK)
#endif 
   {
      RLOG0(L_FATAL, "RLC DL Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */

   /* Create LTE MAC tapa task and attach it
      to a single system thread */
   if(smRgInit(rlc_mac_cl_taskId) != ROK )
   {
      RLOG0(L_FATAL, "LTE MAC Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */


   /* Create Convergence layer TAPA tasks and attach them 
      to a single system thread */
   if(smYsInit(rlc_mac_cl_taskId) != ROK)
   {
      RLOG0(L_FATAL, "CL Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
#endif

#ifdef WR_WATCHDOG
   wrRegWatchDog();
#endif

   /* Create RRC, RRC App and S1AP TAPA tasks and attach them 
      to a single system thread */
#ifdef TIP_L3
   if(smNhInit(rrc_taskId) != ROK)
#else
   if(smNhInit(rrc_s1ap_app_taskId) != ROK)
#endif
   {
      RLOG0(L_FATAL, "RRC Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */

#ifdef WR_RELAY
   if(smWrInit(rrc_s1ap_app_taskId) != ROK )
   {
      RLOG0(L_FATAL, "EnodeBApp Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
#endif /* end of WR_RELAY */
#ifdef TIP_L3
   if(smSzInit(s1ap_taskId) != ROK )
#else
   if(smSzInit(rrc_s1ap_app_taskId) != ROK )
#endif
   {
      RLOG0(L_FATAL, "S1AP Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */


   if(smRmInit(rrc_s1ap_app_taskId) != ROK )
   {
      RLOG0(L_FATAL, "RRM Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
   if(smNlInit(rrc_s1ap_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "SON Tapa Task initialization failed");
      RETVALUE(RFAILED);
   }

#ifdef TIP_L3
   if(smCzInit(x2ap_taskId) != ROK )
#else
   if(smCzInit(rrc_s1ap_app_taskId) != ROK )
#endif
   {
      RLOG0(L_FATAL, "X2AP Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */

#ifndef  TIP_L3_UL2_LL2_SPLIT
   /* Create EGTP and EGTP APP TAPA tasks and attach them 
      to a single system thread */
   if(smEgInit(egtp_dat_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "EGTP Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
#ifdef EU_DAT_APP 
   if(smEuInit(egtp_dat_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "EGTP Data APP Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
#endif /* EU_DAT_APP */
#endif
   /* Create SCTP TAPA tasks and attach them to system thread */
   if(smSbInit(sctp_taskId) != ROK)
   {
      RLOG0(L_FATAL, "SCTP Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */

   /* Create TUCL TAPA task and attach them to system threads */
   if(smHiInit(tucl_taskId) != ROK)
   {
      RLOG0(L_FATAL, "TUCL Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
   /* Create the SM TAPA task */
   SRegTTsk(ENTSM, (Inst) 0, TTNORM, PRIOR0, (PAIFS16)smActvInit, smActvTsk);
   SAttachTTsk(ENTSM, (Inst) 0, sm_taskId);

#ifdef WR_CLI_TARGET_BOARD
   SM_SET_ZERO(&cliPst, sizeof(Pst));
   /* Creating new trhead for cli command */
   if(SCreateSTsk(PRIOR0, &cli_taskId) != ROK)
   {
      RLOG0(L_FATAL, "Failed to Create System Task");
      RETVALUE(RFAILED);
   }
   if(SRegTTsk(ENTSM, (Inst) dstInst, TTNORM, PRIOR0, NULLP, smCliRecvTsk) != ROK)
   {
      RLOG0(L_FATAL, "Failed to Register CLI Tapa Task");
      RETVALUE(RFAILED);
   }
   if(SAttachTTsk(ENTSM, (Inst) dstInst, cli_taskId) != ROK)
   {
      RLOG0(L_FATAL, "Failed to Attach CLI Tapa Task");
      RETVALUE(RFAILED);
   }
   /* Self post to trigger system task */
   WR_FILL_PST(cliPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTSM,0,0, EVTWRCLIRECV, WR_POOL, SM_SELECTOR_LC);
   cliPst.dstInst = dstInst; /* instance 2 */

   if(wrSmSelfPstMsg(&cliPst) != ROK)
   {
      RLOG_STR(L_FATAL, "Self post failed for the event [%s]",PRINT_STR(EVTWRCLIRECV));
      RETVALUE(RFAILED);
   }
#endif

#if defined (PDCP_RLC_DL_RBUF) || defined(MAC_RLC_UL_RBUF) 
  t2kRbufInit(); 
#endif

   RLOG0(L_ALWAYS, "TAPA Task Successfully registered");

   /* Enable sm debugs */
   if(smCfgCb.smDbg == 1)
   {
      /* Update DbgMsk */
      smCb.init.dbgMask = 0xffffffff;
      RLOG0(L_DEBUG, "Enabled SM Debug Prints");
   } /* end of if statement */
   smCb.smState = WR_SM_STATE_INIT;
   smCb.smCellState = FALSE;
   smCb.numOfCells = 0;
#ifndef LTE_ENB_PERF
   smEvent = EVTWRSONCFG;
#else
#ifdef RM_INTF
   smEvent = EVTWRRRMCFG;
#else
   smEvent = EVTWRAPPCFG;
#endif /*RM_INTF*/
#endif

#ifdef WR_RSYS_OAM
   SCreateSmmAppTst(); 
#else
#ifdef E_TM
   if(wrSmDfltBootMode)
   {
      smCb.smState = WR_SM_STATE_CL_INIT;
      smEvent = EVTWRCLCFG;
      smWrEtmProcSm(smEvent);
   }
   else
#endif
   {
      /* Invoke the state machine */
      smWrProcSm(smEvent);
#ifdef TENB_STATS
   printf("Calling TSInfInitStatsFrmWork \n");
   printf("wrSmDfltTenbSocketStats = %ld, wrSmDfltTenbFileStats = %ld, wrSmDfltTenbConsoleStats = %ld, wrSmDfltTenbStatsPeriodicity = %ld, wrSmDfltTenbStatsSocketPort = %ld \n", wrSmDfltTenbSocketStats, wrSmDfltTenbFileStats, wrSmDfltTenbConsoleStats, wrSmDfltTenbStatsPeriodicity, wrSmDfltTenbStatsSocketPort);
      if (TSInfInitStatsFrmWork(wrSmDfltTenbSocketStats,
               wrSmDfltTenbFileStats,
               wrSmDfltTenbConsoleStats,
               wrSmDfltTenbStatsPeriodicity,
               wrSmDfltTenbStatsSocketPort) != ROK)
      {
         RLOG0(L_ERROR, "TENB_STATS Wrong Cfgn");
         RETVALUE(RFAILED);
      }
      printf("Calling TSInfSetEnbIp \n");

      TSInfSetEnbIp(fapParameters.lteEnodebIpAddr.enbIpAddr);
#endif /*end of TENB_STATS */
}
#endif

#ifdef REM_ENABLE
   initNmmTask();
#endif

#ifdef SS_SEGV_SIG_HDLR
#ifndef SS_MULTIPLE_PROCS
   if(SRegIntrptHdlr((Ent)ENTWR, (Inst)0,wrSigSegvActvTsk) != ROK)
   {
      RLOG0(L_FATAL, "Failed to register Interrupt Handler");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */
#endif /* SS_SEGV_SIG_HDLR */ 

   RETVALUE(ROK);

} /* end of tst function */
#else
#if ((!defined(TIP_LOWER_L2)) && (!defined(TIP_UPPER_L2)))
pthread_t tmpThrId;

SSTskId rrc_s1ap_app_taskId;

/*
*
*       Fun:   tst
*
*       Desc:  tst entry point. First entry point.
*
*       Ret:   ROK on success, RFAILED on error
*
*       Notes: None
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC S16 tst
(
Void
)
#else
PUBLIC S16 tst(Void)
#endif
{

   /* System tasks that are needed as per the architecture */
   pthread_attr_t attr;
   SSTskId rlc_mac_cl_taskId;
   SSTskId egtp_dat_app_taskId;
   SSTskId sctp_taskId;
   SSTskId sm_taskId;
   SSTskId tucl_taskId;
#ifdef WR_CLI_TARGET_BOARD
   Inst dstInst = 1;
   SSTskId cli_taskId;
   Pst  cliPst;
#endif /* WR_CLI_TARGET_BOARD */
#ifdef SPLIT_RLC_DL_TASK
   SSTskId rlc_dl_taskId;
#endif 
   U16 smEvent;
   /* wr002.102: Added trace macro */
   TRC2(tst)

   SSetProcId(SM_SM_PROC);
#ifndef LTE_ENB_PAL
    ysPhyCommInit();
    ssMlogInit();
    ssMemlogInit();
#endif

   /* To Initialize SmCfg Cb params with default values */
   wrSmmInitSmCfgCb();/* To intialize wrNghCellCfg and SCTP Params */
   /* Read the parameters from the file and copy into global control block */
   if(smWrReadConfigParams() != ROK)
   {
      fprintf(stderr, "Failed to read from file wr_cfg.txt");
      RETVALUE(RFAILED);
   } /* end of if statement */

   if(fapParameters.lteEnodebIpAddr.ipv4pres == TRUE)
     rlInitLog(CM_TPTADDR_IPV4);
   else if(fapParameters.lteEnodebIpAddr.ipv6pres == TRUE)
     rlInitLog(CM_TPTADDR_IPV6);
   else
   {
      rlInitLog(CM_TPTADDR_IPV4);
   }

#ifndef LTE_ENB_PAL
#ifdef SS_MULTICORE_SUPPORT
   {
      /* Two cores, each having one hardware thread */
      SCpuInfo cpuInfo = { 2, 1, {1, 1}};
      SRegCpuInfo(&cpuInfo);
   }
#endif /* SS_MULTICORE_SUPPORT */
#endif
   /*  All the System tasks(threads)  are created with same priority*/
   /* Needs discussion with Team : In order to reduce the number of 
      threads in our system, we are tieing all L3, Iu, CN side to same
      thread(system task). Essentially this will reduce number of 
      threads but impacts parallelism, since application threads involves
      IO operations. */
#ifdef SRS_PHY
   start_dl();
#endif
   SCreateSTsk(32, &rrc_s1ap_app_taskId); 
   
   sm_taskId = sctp_taskId = egtp_dat_app_taskId = rrc_s1ap_app_taskId;
#ifndef TUCL_TTI_RCV
   SCreateSTsk(32, &tucl_taskId);
#endif
   /* tucl_taskId = egtp_dat_app_taskId; */
#ifdef TUCL_TTI_RCV
   tucl_taskId = rrc_s1ap_app_taskId;
#endif

   SCreateSTsk(32, &egtp_dat_app_taskId);
   /*Pin eGTP-U thread to Core 1.*/
#ifndef LTE_PAL_ENB
#ifdef SS_MULTICORE_SUPPORT
   SSetAffinity(&egtp_dat_app_taskId, SS_AFFINITY_MODE_SPECIFIC, 1, NULLP);
#endif
#endif /* SS_MULTICORE_SUPPORT */

   SCreateSTsk(PRIOR0, &rlc_mac_cl_taskId);  
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

#ifndef LTE_PAL_ENB
#ifdef SS_MULTICORE_SUPPORT
   SSetAffinity(&rlc_mac_cl_taskId, SS_AFFINITY_MODE_SPECIFIC, 0, NULLP);
#endif /* SS_MULTICORE_SUPPORT */
#endif


#ifdef SPLIT_RLC_DL_TASK
   SCreateSTsk(1, &rlc_dl_taskId);
   SSetAffinity(&rlc_dl_taskId, SS_AFFINITY_MODE_SPECIFIC, 1, NULLP);
#endif 

#ifndef WR_RSYS_OAM
#ifndef NL
   U8 cellCfgIdx;
   /* CSG_DEV : Validate Configration Parameters */
   for(cellCfgIdx = 0; cellCfgIdx < wrSmDfltNumCells; cellCfgIdx++)
   {
      if(wrSmmEnbValidateConfigParams(cellCfgIdx) != ROK)
      {
         RLOG0(L_ERROR, "Validation of Configuration Parameters Failed");
      flushData(SIGSEGV);
      RETVALUE(RFAILED);
   }
   }
#endif
#endif
   /* Create PDCP tasks and attach them 
      to a single system thread */
   if(smPjUlInit(egtp_dat_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "PDCP UL Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
   /* Create RLC/PDCP tasks and attach them 
      to a single system thread */
   if(smPjDlInit(egtp_dat_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "PDCP DL Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
   /* Create RLC/PDCP tasks and attach them 
      to a single system thread */
   if(smKwUlInit(egtp_dat_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "RLC UL Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
   /* Create RLC/PDCP tasks and attach them 
      to a single system thread */
#ifdef SPLIT_RLC_DL_TASK
   if(smKwDlInit(rlc_dl_taskId) != ROK)
#else 
   if(smKwDlInit(rlc_mac_cl_taskId) != ROK)
#endif 
   {
      RLOG0(L_FATAL, "RLC DL Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */

   /* Create LTE MAC tapa task and attach it
      to a single system thread */
   if(smRgInit(rlc_mac_cl_taskId) != ROK )
   {
      RLOG0(L_FATAL, "LTE MAC Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */


   /* Create Convergence layer TAPA tasks and attach them 
      to a single system thread */
   if(smYsInit(rlc_mac_cl_taskId) != ROK)
   {
      RLOG0(L_FATAL, "CL Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */

#ifdef WR_WATCHDOG
   wrRegWatchDog();
#endif

   /* Create RRC, RRC App and S1AP TAPA tasks and attach them 
      to a single system thread */
   if(smNhInit(rrc_s1ap_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "RRC Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */

#ifdef WR_RELAY
   if(smWrInit(rrc_s1ap_app_taskId) != ROK )
   {
      RLOG0(L_FATAL, "EnodeBApp Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
#endif /* end of WR_RELAY */
   if(smSzInit(rrc_s1ap_app_taskId) != ROK )
   {
      RLOG0(L_FATAL, "S1AP Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */


   if(smRmInit(rrc_s1ap_app_taskId) != ROK )
   {
      RLOG0(L_FATAL, "RRM Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
   if(smNlInit(rrc_s1ap_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "SON Tapa Task initialization failed");
      RETVALUE(RFAILED);
   }

   if(smCzInit(rrc_s1ap_app_taskId) != ROK )
   {
      RLOG0(L_FATAL, "X2AP Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */

   /* Create EGTP and EGTP APP TAPA tasks and attach them 
      to a single system thread */
   if(smEgInit(egtp_dat_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "EGTP Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
#ifdef EU_DAT_APP 
   if(smEuInit(egtp_dat_app_taskId) != ROK)
   {
      RLOG0(L_FATAL, "EGTP Data APP Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
#endif /* EU_DAT_APP */
   /* Create SCTP TAPA tasks and attach them to system thread */
   if(smSbInit(sctp_taskId) != ROK)
   {
      RLOG0(L_FATAL, "SCTP Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */

   /* Create TUCL TAPA task and attach them to system threads */
   if(smHiInit(tucl_taskId) != ROK)
   {
      RLOG0(L_FATAL, "TUCL Tapa Task initialization failed");
      RETVALUE(RFAILED);
   } /* end of if statement */
   /* Create the SM TAPA task */
   SRegTTsk(ENTSM, (Inst) 0, TTNORM, PRIOR0, (PAIFS16)smActvInit, smActvTsk);
   SAttachTTsk(ENTSM, (Inst) 0, sm_taskId);

#ifdef WR_CLI_TARGET_BOARD
   SM_SET_ZERO(&cliPst, sizeof(Pst));
   /* Creating new trhead for cli command */
   if(SCreateSTsk(PRIOR0, &cli_taskId) != ROK)
   {
      RLOG0(L_FATAL, "Failed to Create System Task");
      RETVALUE(RFAILED);
   }
   if(SRegTTsk(ENTSM, (Inst) dstInst, TTNORM, PRIOR0, NULLP, smCliRecvTsk) != ROK)
   {
      RLOG0(L_FATAL, "Failed to Register CLI Tapa Task");
      RETVALUE(RFAILED);
   }
   if(SAttachTTsk(ENTSM, (Inst) dstInst, cli_taskId) != ROK)
   {
      RLOG0(L_FATAL, "Failed to Attach CLI Tapa Task");
      RETVALUE(RFAILED);
   }
   /* Self post to trigger system task */
   WR_FILL_PST(cliPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTSM,0,0, EVTWRCLIRECV, WR_POOL, SM_SELECTOR_LC);
   cliPst.dstInst = dstInst; /* instance 2 */

   if(wrSmSelfPstMsg(&cliPst) != ROK)
   {
      RLOG_STR(L_FATAL, "Self post failed for the event [%s]",PRINT_STR(EVTWRCLIRECV));
      RETVALUE(RFAILED);
   }
#endif

#if defined (PDCP_RLC_DL_RBUF) || defined(MAC_RLC_UL_RBUF) 
  t2kRbufInit(); 
#endif

   RLOG0(L_ALWAYS, "TAPA Task Successfully registered");

   /* Enable sm debugs */
   if(smCfgCb.smDbg == 1)
   {
      /* Update DbgMsk */
      smCb.init.dbgMask = 0xffffffff;
      RLOG0(L_DEBUG, "Enabled SM Debug Prints");
   } /* end of if statement */
   smCb.smState = WR_SM_STATE_INIT;
   smCb.smCellState = FALSE;
   smCb.numOfCells = 0;
#ifndef LTE_ENB_PERF
   smEvent = EVTWRSONCFG;
#else
#ifdef RM_INTF
   smEvent = EVTWRRRMCFG;
#else
   smEvent = EVTWRAPPCFG;
#endif /*RM_INTF*/
#endif

#ifdef WR_RSYS_OAM
   SCreateSmmAppTst(); 
#else
#ifdef E_TM
   if(wrSmDfltBootMode)
   {
      smCb.smState = WR_SM_STATE_CL_INIT;
      smEvent = EVTWRCLCFG;
      smWrEtmProcSm(smEvent);
   }
   else
#endif
   {
      /* Invoke the state machine */
      smWrProcSm(smEvent);
#ifdef TENB_STATS
   printf("Calling TSInfInitStatsFrmWork \n");
   printf("wrSmDfltTenbSocketStats = %ld, wrSmDfltTenbFileStats = %ld, wrSmDfltTenbConsoleStats = %ld, wrSmDfltTenbStatsPeriodicity = %ld, wrSmDfltTenbStatsSocketPort = %ld \n", wrSmDfltTenbSocketStats, wrSmDfltTenbFileStats, wrSmDfltTenbConsoleStats, wrSmDfltTenbStatsPeriodicity, wrSmDfltTenbStatsSocketPort);
      if (TSInfInitStatsFrmWork(wrSmDfltTenbSocketStats,
               wrSmDfltTenbFileStats,
               wrSmDfltTenbConsoleStats,
               wrSmDfltTenbStatsPeriodicity,
               wrSmDfltTenbStatsSocketPort) != ROK)
      {
         RLOG0(L_ERROR, "TENB_STATS Wrong Cfgn");
         RETVALUE(RFAILED);
      }
      printf("Calling TSInfSetEnbIp \n");

      TSInfSetEnbIp(fapParameters.lteEnodebIpAddr.enbIpAddr);
#endif /*end of TENB_STATS */
}
#endif

#ifdef REM_ENABLE
   initNmmTask();
#endif

#ifdef SS_SEGV_SIG_HDLR
#ifndef SS_MULTIPLE_PROCS
   if(SRegIntrptHdlr((Ent)ENTWR, (Inst)0,wrSigSegvActvTsk) != ROK)
   {
      RLOG0(L_FATAL, "Failed to register Interrupt Handler");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */
#endif /* SS_SEGV_SIG_HDLR */ 

   RETVALUE(ROK);

} /* end of tst function */

#endif
#endif

#if ((!defined(TIP_LOWER_L2)) && (!defined(TIP_UPPER_L2)))
#if defined(PDCP_RLC_DL_RBUF) || defined(MAC_RLC_UL_RBUF) 
#ifdef ANSI
PRIVATE S16 t2kRbufInit()
#else
PRIVATE S16 t2kRbufInit()
#endif
{
   TRC2(t2kRbufInit);



#ifdef PDCP_RLC_DL_RBUF 
   if(SCreateSRngBuf(SS_RNG_BUF_DLPDCP_TO_DLRLC,0,0,sizeof(KwuDatReqDetl),
       SS_RNG_DLPDCP_TO_DLRLC_SIZE) != ROK)
   {
       printf("Ring Buffer Create Failed\n");
       RETVALUE(RFAILED);
   }
   /* Attach PJ to second ring buffer as Tx entity */
   SAttachSRngBuf(SS_RNG_BUF_DLPDCP_TO_DLRLC, SS_RBUF_ENT_DLPDCP,SS_RNG_TX);
   /* Attach PJ to first ring buffer as Rx entity */
   SAttachSRngBuf(SS_RNG_BUF_DLPDCP_TO_DLRLC, SS_RBUF_ENT_DLRLC,SS_RNG_RX);
#endif 
#ifdef  MAC_RLC_UL_RBUF
   if(SCreateSRngBuf(SS_RNG_BUF_ULMAC_TO_ULRLC,0,0,sizeof(RguDedDatInd1),
       SS_RNG_ULMAC_TO_ULRLC_SIZE) != ROK)
   {
      printf("Ring Buffer Create Failed\n");
      RETVALUE(RFAILED);
   }
     SAttachSRngBuf(SS_RNG_BUF_ULMAC_TO_ULRLC, SS_RBUF_ENT_ULMAC,SS_RNG_TX);
     SAttachSRngBuf(SS_RNG_BUF_ULMAC_TO_ULRLC, SS_RBUF_ENT_ULRLC,SS_RNG_RX);
#endif 
#ifdef RLC_MAC_DAT_REQ_RBUF
   if(SCreateSRngBuf(SS_RNG_BUF_DLRLC_TO_DLMAC_DAT_REQ,0,0,sizeof(RguInfoRingElem),
       SS_RNG_DLRLC_TO_DLMAC_DAT_REQ_SIZE) != ROK)
   {
      printf("Ring Buffer Create Failed\n");
      RETVALUE(RFAILED);
   }
   SAttachSRngBuf(SS_RNG_BUF_DLRLC_TO_DLMAC_DAT_REQ, SS_RBUF_ENT_DLRLC_DAT_REQ,SS_RNG_TX);
   SAttachSRngBuf(SS_RNG_BUF_DLRLC_TO_DLMAC_DAT_REQ, SS_RBUF_ENT_DLMAC_DAT_REQ,SS_RNG_RX);
#endif 
#ifdef RLC_MAC_STA_RSP_RBUF
   if(SCreateSRngBuf(SS_RNG_BUF_DLRLC_TO_DLMAC,0,0,sizeof(RguDStaRspInfo),
       SS_RNG_DLRLC_TO_DLMAC_SIZE) != ROK)
   {
      printf("Ring Buffer Create Failed\n");
      RETVALUE(RFAILED);
   }
   SAttachSRngBuf(SS_RNG_BUF_DLRLC_TO_DLMAC, SS_RBUF_ENT_DLRLC_STA_RSP,SS_RNG_TX);
   SAttachSRngBuf(SS_RNG_BUF_DLRLC_TO_DLMAC, SS_RBUF_ENT_DLMAC_STA_RSP,SS_RNG_RX);
#endif 
#ifdef  MAC_RLC_HARQ_STA_RBUF 
   if(SCreateSRngBuf(SS_RNG_BUF_MAC_HARQ,0,0,sizeof(RguHarqStatusInd),
       SS_RNG_MAC_TO_RLC_HARQ_IND_SIZE) != ROK)
   {
      printf("Ring Buffer Create Failed\n");
      RETVALUE(RFAILED);
   }
   SAttachSRngBuf(SS_RNG_BUF_MAC_HARQ, SS_RBUF_ENT_MAC_HARQ_STA,SS_RNG_TX);
   SAttachSRngBuf(SS_RNG_BUF_MAC_HARQ, SS_RBUF_ENT_RLC_HARQ_STA,SS_RNG_RX);
#endif 


   RETVALUE(ROK);

}
#endif
#endif
/*
*
*       Fun:  wrSmSelfPstMsg 
*
*       Desc:  This function is used by  Layer to self post 
*              a message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC S16 wrSmSelfPstMsg
(
Pst   *pst
)
#else
PUBLIC S16 wrSmSelfPstMsg(pst)
Pst   *pst;
#endif
{
   Buffer *mBuf;          /* message buffer */

   TRC2(wrSmSelfPstMsg);

   if(SGetMsg(DFLT_REGION, WR_POOL, &mBuf) != ROK)
   {
      RLOG0(L_FATAL, "Memory allocation failed in wrSmSelfPstMsg");
      RETVALUE(RFAILED);
   } /* end of if statement */

   if (SPstTsk(pst, mBuf) != ROK)
   {
      RLOG0(L_FATAL, "SPstTsk failed in wrSmSelfPstMsg");
      RETVALUE(RFAILED);
   }

   RETVALUE (ROK);

} /* end of wrSmSelfPstMsg */


PRIVATE const char* wrSmmPrintSmmEvent
(
U8   event
)
{
   const char*    eventStr;

   switch (event)
   {
      case EVTWRTUCLCFG:
         eventStr = PRINT_STR(EVTWRTUCLCFG);
         break;

      case EVTWRSCTPCFG:
         eventStr = PRINT_STR(EVTWRSCTPCFG);
         break;

      case EVTWRS1APCFG:
         eventStr = PRINT_STR(EVTWRS1APCFG);
         break;

      case EVTWREGTPCFG:
         eventStr = PRINT_STR(EVTWREGTPCFG);
         break;

      case EVTWRAPPCFG:
         eventStr = PRINT_STR(EVTWRAPPCFG);
         break;

      case EVTWRRRCCFG:
         eventStr = PRINT_STR(EVTWRRRCCFG);
         break;

      case EVTWRPDCPCFG:
         eventStr = PRINT_STR(EVTWRPDCPCFG);
         break;

      case EVTWRRLCCFG:
         eventStr = PRINT_STR(EVTWRRLCCFG);
         break;

      case EVTWRMACCFG:
         eventStr = PRINT_STR(EVTWRMACCFG);
         break;

      case EVTWRCLCFG:
         eventStr = PRINT_STR(EVTWRCLCFG);
         break;

      case EVTWRX2APCFG:
         eventStr = PRINT_STR(EVTWRX2APCFG);
         break;

#ifdef RM_INTF
      case EVTWRRRMCFG:
         eventStr = PRINT_STR(EVTWRRRMCFG);
         break;
#endif

      case EVTWRSONCFG:
         eventStr = PRINT_STR(EVTWRSONCFG);
         break;

      case EVTWRS1APSTKBND:
         eventStr = PRINT_STR(EVTWRS1APSTKBND);
         break;

      case EVTWREGTPSTKBND:
         eventStr = PRINT_STR(EVTWREGTPSTKBND);
         break;

      case EVTWRX2APSTKBND:
         eventStr = PRINT_STR(EVTWRX2APSTKBND);
         break;

      case EVTWRRRCSTKBND:
         eventStr = PRINT_STR(EVTWRRRCSTKBND);
         break;

      case EVTWRENBDEBUGS:
         eventStr = PRINT_STR(EVTWRENBDEBUGS);
         break;

      case EVTWRENBALRMS:
         eventStr = PRINT_STR(EVTWRENBALRMS);
         break;

      case EVTWRINITS1SETUP:
         eventStr = PRINT_STR(EVTWRINITS1SETUP);
         break;

      case EVTWRCELLCFG:
         eventStr = PRINT_STR(EVTWRCELLCFG);
         break;

      case EVTWRINITX2SETUP:
         eventStr = PRINT_STR(EVTWRINITX2SETUP);
         break;

      case EVTWRENBLOG:
         eventStr = PRINT_STR(EVTWRENBLOG);
         break;

      case EVTWRCLIRECV:
         eventStr = PRINT_STR(EVTWRCLIRECV);
         break;

      case EVTWRSTARTDYNUPDATE:
         eventStr = PRINT_STR(EVTWRSTARTDYNUPDATE);
         break;

#ifdef RM_INTF
      case EVTWRRRMSTKBND:
         eventStr = PRINT_STR(EVTWRRRMSTKBND);
         break;
#endif
      default:
         eventStr = PRINT_STR(Invalid event);
         break;
   }

   return eventStr;
}
/*
*
*       Fun:   smWrConfigCell
*
*       Desc:  This function is entry function to the  main State Machine
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/
PUBLIC Void smWrConfigCell
(
U16         cellId
)
{
   TRC2(smWrConfigCell);

   /* CHINNA: Currently cell Id configured as cellIdx + 1 */
   if(smCb.smCellState != TRUE)
   {
      smCb.smCellState = TRUE;
      smCfgCellAdd(cellId - 1);
   }
   else
   {
      smCb.cellIdLst[smCb.numOfCells] = cellId;
      smCb.numOfCells++;
   }
}

#ifdef TIP_L3
/*
*
*       Fun:   smWrProcSm
*
*       Desc:  This function is entry function to the  main State Machine
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void smWrProcSm
(
U8 event
)
#else
PUBLIC Void smWrProcSm( event)
U8  event;
#endif /* ANSI */
{
   TRC2(smWrProcSm);

 
   switch (smCb.smState)
   {
      case WR_SM_STATE_INIT:
         {
            for(U8 idx = 0; idx < WR_MAX_CELLS; idx++)
            {   
               smInitMsm(idx); 
            }
#ifndef LTE_ENB_PERF
            RLOG0(L_DEBUG,"Configuring SON");
            wrSmHdlSonCfgEvent(event);
            break;
         }
      case WR_SM_STATE_SON_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring TUCL");
            wrSmHdlTuclCfgEvent(event);
            break;
         }
      case WR_SM_STATE_TUCL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring SCTP");
            wrSmHdlSctpCfgEvent(event);
            break;
         }
      case WR_SM_STATE_SCTP_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring S1AP");
            wrSmHdlS1apCfgEvent(event);
            break;
         }
      case WR_SM_STATE_S1AP_CFG_DONE:
         {
#ifndef  TIP_L3_UL2_LL2_SPLIT
            RLOG0(L_DEBUG,"Configuring EGTP");
            wrSmHdlEgtpCfgEvent(event);
            break;
         }
      case WR_SM_STATE_EGTP_CFG_DONE:
         {
#endif
            RLOG0(L_DEBUG,"Configuring X2AP");
            wrSmHdlX2apCfgEvent(event);       
            break;
         }
      case WR_SM_STATE_X2AP_CFG_DONE:
         {
#endif /* LTE_ENB_PERF */
#ifdef RM_INTF
            RLOG0(L_DEBUG,"Configuring RRM");
            wrSmHdlRrmCfgEvent(event);
#else
            RLOG0(L_DEBUG,"Configuring eNodeBApp");
            wrSmHdlAppCfgEvent(event);
#endif /*RM_INTF*/
            break;
         }
#ifdef RM_INTF
      case WR_SM_STATE_RRM_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring eNodeBApp");
            wrSmHdlAppCfgEvent(event);
            break;
         }
#endif /*RM_INTF*/
      case WR_SM_STATE_APP_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring RRC");
            wrSmHdlRrcCfgEvent(event);
            break;
         }
      case WR_SM_STATE_RRC_CFG_DONE:
         {
#ifndef  TIP_L3_UL2_LL2_SPLIT
            RLOG0(L_DEBUG,"Configuring PDCP UL");
            wrSmHdlPdcpUlCfgEvent(event);
            break;
         }
      case WR_SM_STATE_PDCP_UL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring PDCP DL");
            wrSmHdlPdcpDlCfgEvent(event);
            break;
         }
      case WR_SM_STATE_PDCP_DL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring RLC UL");
            wrSmHdlRlcUlCfgEvent(event);
            break;
         }
      case WR_SM_STATE_RLC_UL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring RLC DL");
            wrSmHdlRlcDlCfgEvent(event);
            break;
         }
      case WR_SM_STATE_RLC_DL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring MAC");
            wrSmHdlMacCfgEvent(event);
            break;
         }
      case WR_SM_STATE_MAC_CFG_DONE:
         {
            /* Schd Cfg, event is EVTWRMACSCHDCFG */
            wrSmHdlMacCfgEvent(event);
            break;
         }
      case WR_SM_STATE_MAC_SCHD_CFG_DONE:
         {
#ifndef LTE_ENB_PAL
            RLOG0(L_DEBUG,"Configuring CL");
            wrSmHdlCLCfgEvent(event);
            break;
         }
      case WR_SM_STATE_CL_CFG_DONE:
         {
#endif
#endif /*TIP_L3_UL2_LL2_SPLIT*/
            RLOG0(L_DEBUG,"Enabling eNodeB Debugs");
            /* Initializing Dbg Mask to Zero */
            smCfgCb.smDbgMsk = 0;
            wrSmHdlEnbDebugs(event);
#ifdef TENB_STATS
#ifdef TIP_LOWER_L2
            TSInfCfgCL();
#endif
#endif
            break;
         }
      case WR_SM_STATE_ENB_LOG_DONE:
         {
            RLOG0(L_DEBUG,"Enabling eNodeB Alarms");
            wrSmHdlEnbAlarms(event);
            break;
         }
      case WR_SM_STATE_ENB_ALRMS_DONE:

         {
#ifndef LTE_ENB_PERF
            RLOG0(L_DEBUG,"Binding S1AP stack");
            wrSmHdlBndS1apStack(event);
            break;
         }
      case WR_SM_STATE_S1AP_STK_BND_DONE:
         {
#ifndef  TIP_L3_UL2_LL2_SPLIT
            RLOG0(L_DEBUG,"Binding EGTP stack");
            wrSmHdlBndEgtpStack(event);
            break;
         }
      case WR_SM_STATE_EGTP_STK_BND_DONE:
         {
#endif /* end of TIP_L3_UL2_LL2_SPLIT */
            RLOG0(L_DEBUG,"Binding X2AP stack");
            wrSmHdlBndX2apStack(event);
            break;
         }
      case WR_SM_STATE_X2AP_STK_BND_DONE:
         {
#endif /* end of LTE_ENB_PERF */
#ifndef  TIP_L3_UL2_LL2_SPLIT
            RLOG0(L_DEBUG,"Binding RRC stack");
            wrSmHdlBndRrcStack(event);
#else
            RLOG0(L_DEBUG,"Binding RRM stack");
            wrSmHdlBndRrmStack(event);
#endif
            break;
         }
#ifndef  TIP_L3_UL2_LL2_SPLIT
      case WR_SM_STATE_RRC_STK_BND_DONE:
#endif
#ifdef RM_INTF
#ifndef  TIP_L3_UL2_LL2_SPLIT
         {
            RLOG0(L_DEBUG,"Binding RRM stack");
            wrSmHdlBndRrmStack(event);
            break;
         }
#endif
      case WR_SM_STATE_RRM_STK_BND_DONE:
#endif
         {
            RLOG0(L_DEBUG,"Binding RRC/APP stack");
            smBindUnBindWrToCtfSap(ABND_ENA);
            break;
         }
      case WR_SM_STATE_RRC_STK_BND_DONE:
         {
            tipIsL3Ready = TRUE;
            smCb.smState = WR_SM_STATE_APP_CELL_CFG_DONE;
            printf("\n***** L3 initialization done. Waiting for lower layers...\n");
#if 0
            if(!tipCheckIsL2Ready())
            {
               printf("\n*** Awaiting L2 INIT ***\n");
            }
            else
            {
               smCfgCellAdd(0);
            }
#endif
            break;
         }
      case WR_SM_STATE_APP_CELL_CFG_DONE:
         {
#ifndef LTE_ENB_PERF
            RLOG0(L_DEBUG,"Establishing S1-SETUP");
            wrSmHdlInitS1Setup(event);
#else
            RLOG0(L_DEBUG,"Configuring Cell at eNodeBApp");
            smCb.smState = WR_SM_STATE_AWAIT_CELL_UP;
            wrSmHdlInitCellCfg(EVTWRCELLCFG);
#endif
            break;
         }
      case WR_SM_STATE_CELL_UP:
         {
            U8       cellCfgIndx = 0;
#ifdef WR_RSYS_KPI
            if(kpiInfo.startCollec == FALSE)
            {
#ifdef LTE_L2_MEAS
               RLOG0(L_DEBUG,"Starting L2 Measurements");
               kpiInfo.l2CollecEna = TRUE;
               wrKpiStartKpiCollecPrc(kpiInfo.l2CollecEna); 
#endif
            }
#endif 
#ifdef RM_INTF
            RLOG0(L_DEBUG,"(APP->RRM) : Cell Up indication to RRM");
            wrSmSndRrmCellUpInd(event);
#endif
            /* Send Cell Up Indication to SON for 
             * each cell */
            for(cellCfgIndx = 0; cellCfgIndx < wrSmDfltNumCells; cellCfgIndx++)
            {
               wrSmSndSonCellUpInd(event, cellCfgIndx);
            }

#ifdef WR_RSYS_OAM
            RLOG0(L_DEBUG,"(APP_>OAM) : MsmConfigComplete to OAM");
            wrSmConfigComplete();
            break;
         }
      case WR_SM_STATE_OAM_DYN_START:
      {
#endif
            RLOG0(L_DEBUG,"Establishing X2 connection");
            wrSmHdlInitX2Setup(event);
            break;
         }
      default:
         {
            RLOG1(L_ERROR, "smWrProcSm() Invalid  state [%d] received",
                  smCb.smState);
            break;
         }
   }
   RETVOID;
} /* smWrProcSm */
#else
#if ((!defined(TIP_LOWER_L2)) && (!defined(TIP_UPPER_L2)))
/*
*
*       Fun:   smWrProcSm
*
*       Desc:  This function is entry function to the  main State Machine
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void smWrProcSm
(
U8 event
)
#else
PUBLIC Void smWrProcSm( event)
U8  event;
#endif /* ANSI */
{
   TRC2(smWrProcSm);

 
   switch (smCb.smState)
   {
      case WR_SM_STATE_INIT:
         {
            for(U8 idx = 0; idx < WR_MAX_CELLS; idx++)
            {   
               smInitMsm(idx); 
            }
#ifndef LTE_ENB_PERF
            RLOG0(L_DEBUG,"Configuring SON");
            wrSmHdlSonCfgEvent(event);
            break;
         }
      case WR_SM_STATE_SON_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring TUCL");
            wrSmHdlTuclCfgEvent(event);
            break;
         }
      case WR_SM_STATE_TUCL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring SCTP");
            wrSmHdlSctpCfgEvent(event);
            break;
         }
      case WR_SM_STATE_SCTP_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring S1AP");
            wrSmHdlS1apCfgEvent(event);
            break;
         }
      case WR_SM_STATE_S1AP_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring EGTP");
            wrSmHdlEgtpCfgEvent(event);
            break;
         }
      case WR_SM_STATE_EGTP_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring X2AP");
            wrSmHdlX2apCfgEvent(event);       
            break;
         }
      case WR_SM_STATE_X2AP_CFG_DONE:
         {
#endif /* LTE_ENB_PERF */
#ifdef RM_INTF
            RLOG0(L_DEBUG,"Configuring RRM");
            wrSmHdlRrmCfgEvent(event);
#else
            RLOG0(L_DEBUG,"Configuring eNodeBApp");
            wrSmHdlAppCfgEvent(event);
#endif /*RM_INTF*/
            break;
         }
#ifdef RM_INTF
      case WR_SM_STATE_RRM_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring eNodeBApp");
            wrSmHdlAppCfgEvent(event);
            break;
         }
#endif /*RM_INTF*/
      case WR_SM_STATE_APP_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring RRC");
            wrSmHdlRrcCfgEvent(event);
            break;
         }
      case WR_SM_STATE_RRC_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring PDCP UL");
            wrSmHdlPdcpUlCfgEvent(event);
            break;
         }
      case WR_SM_STATE_PDCP_UL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring PDCP DL");
            wrSmHdlPdcpDlCfgEvent(event);
            break;
         }
      case WR_SM_STATE_PDCP_DL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring RLC UL");
            wrSmHdlRlcUlCfgEvent(event);
            break;
         }
      case WR_SM_STATE_RLC_UL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring RLC DL");
            wrSmHdlRlcDlCfgEvent(event);
            break;
         }
      case WR_SM_STATE_RLC_DL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring MAC");
            wrSmHdlMacCfgEvent(event);
            break;
         }
      case WR_SM_STATE_MAC_CFG_DONE:
         {
            /* Schd Cfg, event is EVTWRMACSCHDCFG */
            wrSmHdlMacCfgEvent(event);
            break;
         }
      case WR_SM_STATE_MAC_SCHD_CFG_DONE:
         {
#ifndef LTE_ENB_PAL
            RLOG0(L_DEBUG,"Configuring CL");
            wrSmHdlCLCfgEvent(event);
            break;
         }
      case WR_SM_STATE_CL_CFG_DONE:
         {
#endif
            RLOG0(L_DEBUG,"Enabling eNodeB Debugs");
            /* Initializing Dbg Mask to Zero */
            smCfgCb.smDbgMsk = 0;
            wrSmHdlEnbDebugs(event);
#ifdef TENB_STATS
            TSInfCfgCL();
#endif
            break;
         }
      case WR_SM_STATE_ENB_LOG_DONE:
         {
            RLOG0(L_DEBUG,"Enabling eNodeB Alarms");
            wrSmHdlEnbAlarms(event);
            break;
         }
      case WR_SM_STATE_ENB_ALRMS_DONE:

         {
#ifndef LTE_ENB_PERF
            RLOG0(L_DEBUG,"Binding S1AP stack");
            wrSmHdlBndS1apStack(event);
            break;
         }
      case WR_SM_STATE_S1AP_STK_BND_DONE:
         {
            RLOG0(L_DEBUG,"Binding EGTP stack");
            wrSmHdlBndEgtpStack(event);
            break;
         }
      case WR_SM_STATE_EGTP_STK_BND_DONE:
         {
            RLOG0(L_DEBUG,"Binding X2AP stack");
            wrSmHdlBndX2apStack(event);
            break;
         }
      case WR_SM_STATE_X2AP_STK_BND_DONE:
         {
#endif /* end of LTE_ENB_PERF */
            RLOG0(L_DEBUG,"Binding RRC stack");
            wrSmHdlBndRrcStack(event);
            break;
         }
      case WR_SM_STATE_RRC_STK_BND_DONE:
#ifdef RM_INTF
         {
            RLOG0(L_DEBUG,"Binding RRM stack");
            wrSmHdlBndRrmStack(event);
            break;
         }
      case WR_SM_STATE_RRM_STK_BND_DONE:
#endif
         {
#ifndef LTE_ENB_PERF
            RLOG0(L_DEBUG,"Establishing S1-SETUP");
            wrSmHdlInitS1Setup(event);
#else
            RLOG0(L_DEBUG,"Configuring Cell at eNodeBApp");
            smCb.smState = WR_SM_STATE_AWAIT_CELL_UP;
            wrSmHdlInitCellCfg(EVTWRCELLCFG);
#endif
            break;
         }
      case WR_SM_STATE_CELL_UP:
         {
            U8       cellCfgIndx = 0;
#ifdef WR_RSYS_KPI
            if(kpiInfo.startCollec == FALSE)
            {
#ifdef LTE_L2_MEAS
               RLOG0(L_DEBUG,"Starting L2 Measurements");
               kpiInfo.l2CollecEna = TRUE;
               wrKpiStartKpiCollecPrc(kpiInfo.l2CollecEna); 
#endif
            }
#endif 
#ifdef RM_INTF
            RLOG0(L_DEBUG,"(APP->RRM) : Cell Up indication to RRM");
            wrSmSndRrmCellUpInd(event);
#endif
            /* Send Cell Up Indication to SON for 
             * each cell */
            for(cellCfgIndx = 0; cellCfgIndx < wrSmDfltNumCells; cellCfgIndx++)
            {
               wrSmSndSonCellUpInd(event, cellCfgIndx);
            }

#ifdef WR_RSYS_OAM
            RLOG0(L_DEBUG,"(APP_>OAM) : MsmConfigComplete to OAM");
            wrSmConfigComplete();
            break;
         }
      case WR_SM_STATE_OAM_DYN_START:
      {
#endif
            RLOG0(L_DEBUG,"Establishing X2 connection");
            wrSmHdlInitX2Setup(event);
            break;
         }
      default:
         {
            RLOG1(L_ERROR, "smWrProcSm() Invalid  state [%d] received",
                  smCb.smState);
            break;
         }
   }
   RETVOID;
} /* smWrProcSm */

#endif
#endif

/*
*
*       Fun:   wrSmHdlUnBndRrmStack
*
*       Desc:  This function handles unbind of RRM stack
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlUnBndRrmStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlUnBndRrmStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlUnBndRrmStack);

   if(event == EVTWRRRMSTKUNBND)
   {
      /* UnBind RRM to MAC */
      smBindUnBindRmToRgmSap(AUBND);
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRRRMSTKUNBND. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlUnBndRrmStack */

/*
*
*       Fun:   wrSmHdlUnBndRrcStack
*
*       Desc:  This function handles unbind of RRC stack
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlUnBndRrcStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlUnBndRrcStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlUnBndRrcStack);

   if(event == EVTWRRRCSTKUNBND)
   {
      /* UnBind APP to MAC */
      smBindUnBindWrToRgrSap(AUBND);
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRRRCSTKUNBND. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlUnBndRrcStack */

/*
*
*       Fun:   wrSmHdlUnBndX2apStack
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlUnBndX2apStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlUnBndX2apStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlUnBndX2apStack);

   if(event == EVTWRX2APSTKUNBND)
   {
      /* UnBind APP to X2AP */
      smBindUnBindWrToCztSap(AUBND_DIS);
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRX2APSTKUNBND. Received event %s ",
          wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlUnBndX2apStack */

/*
*
*       Fun:   wrSmHdlUnBndEgtpStack
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlUnBndEgtpStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlUnBndEgtpStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlUnBndEgtpStack);

   if(event == EVTWREGTPSTKUNBND)
   {
      /* UnBind APP to EGTP */
      smBindUnBindWrToEgtSap(AUBND_DIS);
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWREGTPSTKUNBND. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlUnBndEgtpStack */

/*
*
*       Fun:   wrSmHdlUnBndS1apStack
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlUnBndS1apStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlUnBndS1apStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlUnBndS1apStack);

   if(event == EVTWRS1APSTKUNBND)
   {
      /* UnBind APP to S1AP */
      smBindUnBindWrToSztSap(AUBND_DIS);
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRS1APSTKUNBND. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlUnBndS1apStack */


#ifdef ANSI
PUBLIC Void smWrShutdownSm
(
U8 event
)
#else
PUBLIC Void smWrShutdownSm()
U8  event;
#endif /* ANSI */
{

#ifndef WR_RSYS_OAM
   U16 smevent;
#endif
   TRC2(smWrShutdownSm);
   switch (smCb.smState)
   {   
      case WR_SM_STATE_DINIT:
         {
            /* Unbind RRM stack */
            RLOG0(L_DEBUG,"Unbinding RRM stack");
            wrSmHdlUnBndRrmStack(event);
            break;
         }

      case WR_SM_STATE_RRM_STK_UNBND_DONE:
         {
            /* Unbind RRC stack */
            RLOG0(L_DEBUG,"Unbinding RRC stack");
            wrSmHdlUnBndRrcStack(event);
            break;
         }
      case WR_SM_STATE_RRC_STK_UNBND_DONE:
         {
            /* Unbind X2AP stack */
            RLOG0(L_DEBUG,"Unbinding X2AP stack");
            wrSmHdlUnBndX2apStack(event);
            break;
         }
      case WR_SM_STATE_X2AP_STK_UNBND_DONE:
         {
            /* Unbind EGTP stack */
            RLOG0(L_DEBUG,"Unbinding EGTP stack");
            wrSmHdlUnBndEgtpStack(event);
            break;
         }
      case WR_SM_STATE_EGTP_STK_UNBND_DONE:
         {
            /* Unbind S1AP stack */
            RLOG0(L_DEBUG,"Unbinding S1AP stack");
            wrSmHdlUnBndS1apStack(event);
            break;
         }
      case WR_SM_STATE_S1AP_STK_UNBND_DONE:
         {
            RLOG0(L_DEBUG,"S1AP Unbinding completed, now initiating RRM shutdown");
            smBuildRmShutDownCntrl();
            break;
         }
      case WR_SM_STATE_RRM_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"RRM Shutdown completed, now initiating eNBApp shutdown");
            smBuildWrShutDownCntrl();
            break;
         }
      case WR_SM_STATE_APP_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"eNBApp shutdown completed, now initiating SON shutdown");
            smBuildNlShutDownCntrl();
            break;
         }
      case WR_SM_STATE_SON_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"SON Shutdown completed, now initiating RRC layer shutdown");
            smBuildNhShutDownCntrl();
            break;
         } 
      case WR_SM_STATE_RRC_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"RRC Shutdown completed , now initaiting  PDCP DL layer shutdown");
            smBuildPjShutDownCntrl(WR_SM_PJDL_INST);
            break;
         }
      case WR_SM_STATE_PDCP_DL_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"PDCP_DL shutdown completed , now initiating  PDCP UL layer shutdown");
            smBuildPjShutDownCntrl(WR_SM_PJUL_INST);
            break;
         }
      case WR_SM_STATE_PDCP_UL_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"PDCP_UL shutting down completed , now initiating  RLC DL layer shutdown");
            smBuildKwShutDownCntrl((Inst)WR_SM_KWDL_INST);
            break;
         }
      case WR_SM_STATE_RLC_DL_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"RLC_DL shuting down completed, now initiating  RLC UL layer shutdown");
            smBuildKwShutDownCntrl((Inst)WR_SM_KWUL_INST);
            break;
         }
      case WR_SM_STATE_RLC_UL_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"RLC_UL shuting down completed, now initiating  Scheduler shutdown");
            smBuildRgSCHShutDownCtrl();
            break;
         }
      case WR_SM_STATE_MAC_SCH_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"MAC_SCH shuting down completed, now initiating  MAC layer shutdown");
            smBuildRgShutDownCntrl();
            break;
         }  
      case WR_SM_STATE_MAC_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"MAC shuting down completed ,now initiating EGTP layer shutdown");
            smBuildWrUnbindEg();
            /* cross verify SCHEDULER release/reconfiguration */
            smBuildEgShutDownCntrl();
            break;
         }

      case  WR_SM_STATE_EGTP_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"EGTP shuting down completed , now initiating  X2AP layer shutdown");
            smBuildWrUnbindCz();
            smBuildCzShutDownCntrl();
            break;
         }
      case WR_SM_STATE_X2AP_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"X2AP shuting down completed, now initiating S1AP layer shutdown");
            smBuildWrUnbindSz();
            smBuildSzShutDownCntrl();
            break;
         }

      case WR_SM_STATE_S1AP_SHUTDWN_DONE:
         {
#ifndef LTE_ENB_PAL
            RLOG0(L_DEBUG,"S1AP shuting down completed, now initiating CL shutdown");
            smBuildYsShutDownCntrl();
            break;
         }

      case  WR_SM_STATE_CL_SHUTDWN_DONE:
         {
           RLOG0(L_DEBUG,"CL shuting down completed, now initiating SCTP layer shutdown");
#else
           RLOG0(L_DEBUG,"S1AP shuting down completed, now initiating SCTP layer shutdown");
#endif
            RLOG0(L_DEBUG,"");
            smBuildSbShutDownCntrl();
            break;
         }

      case WR_SM_STATE_SCTP_SHUTDWN_DONE:
         {
            RLOG0(L_DEBUG,"SCTP shuting down completed, now initiating TUCL layer shutdown");
            smBuildHiShutDownCntrl();
            break;
         }
      case  WR_SM_STATE_TUCL_SHUTDWN_DONE:
         {
#ifdef WR_RSYS_OAM
            RLOG0(L_ALWAYS, "All layers Shutdown completed;"
                             "(APP->OAM) : ShutdownAck to OAM");
            MsmShutDownAck();
#else
            RLOG0(L_DEBUG, "Re-initialisation of stack started");
            smCb.smState = WR_SM_STATE_INIT;
            smevent = EVTWRSONCFG;
            smWrProcSm(smevent);
#endif
            break;
         }
      default:
         {
            RLOG1(L_ERROR, "Invalid state [%d] recevied",smCb.smState);
            break;
         }

   }
   RETVOID;
}
#ifndef LTE_ENB_PERF
/*
*
*       Fun:   wrSmHdlTuclCfgEvent
*
*       Desc:  This function is handles events in Init state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/


#ifdef ANSI
PUBLIC Void wrSmHdlTuclCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlTuclCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2 (wrSmHdlTuclCfgEvent);

   if(event == EVTWRTUCLCFG)
   {
      /* Start TUCL Configuration */
      wrSmHiCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRTUCLCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlTuclCfgEvent */
/*
*
*       Fun:   wrSmHdlSctpCfgEvent
*
*       Desc:  This function is handles events in TUCL Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/


#ifdef ANSI
PUBLIC Void wrSmHdlSctpCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlSctpCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlSctpCfgEvent);

   if(event == EVTWRSCTPCFG )
   {
      /* Start SCTP Configuration */
      wrSmSbCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRSCTPCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlSctpCfgEvent */

/*
*
*       Fun:   wrSmHdlS1apCfgEvent
*
*       Desc:  This function is handles events in SCTP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/


#ifdef ANSI
PUBLIC Void wrSmHdlS1apCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlS1apCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlS1apCfgEvent);

   if(event == EVTWRS1APCFG )
   {
      /* Start S1AP Configuration */
      wrSmSzCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRS1APCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlS1apCfgEvent */

#ifdef LTE_HO_SUPPORT
/*
*
*       Fun:   wrSmHdlX2apCfgEvent
*
*       Desc:  This function is handles events in X2AP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/


#ifdef ANSI
PUBLIC Void wrSmHdlX2apCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlX2apCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlX2apCfgEvent);

   if(event == EVTWRX2APCFG )
   {
      /* Start X2AP Configuration */
      wrSmCzCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRX2APCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlX2apCfgEvent */
#endif

/*
*
*       Fun:   wrSmHdlEgtpCfgEvent
*
*       Desc:  This function is handles events in S1AP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void wrSmHdlEgtpCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlEgtpCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlEgtpCfgEvent);

   if(event == EVTWREGTPCFG )
   {
      /* Start EGTP Configuration */
      wrSmEgCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWREGTPCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlEgtpCfgEvent */
#endif

/*
*
*       Fun:   wrSmHdlSonCfgEvent
*
*       Desc:  This function handles events once eNB APP Config done and
*              initiate to start SON configuration
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/


#ifdef ANSI
PUBLIC Void wrSmHdlSonCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlSonCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlSonCfgEvent);

   if(event == EVTWRSONCFG )
   {
      /* Start SON Configuration */
      wrSmNlCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRSONCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlSonCfgEvent */

/*
*
*       Fun:   wrSmSndSonCellUpInd
*
*       Desc:  This function sends cell up indication to SON module
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void wrSmSndSonCellUpInd
(
U8 event,
U8 cellCfgIndx
)
#else
PUBLIC Void wrSmSndSonCellUpInd(event, cellCfgIndx)
U8  event;
U8  cellCfgIndx;
#endif /* ANSI */
{
   TRC2(wrSmSndSonCellUpInd);

   /*send cell up indication to SON module */
   smSendCellUpIndToSon(cellCfgIndx);

   RETVOID;
} 


#ifdef RM_INTF
/*
*
*       Fun:   wrSmHdlRrmCfgEvent
*
*       Desc:  This function is handles events in EGTP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/


#ifdef ANSI
PUBLIC Void wrSmHdlRrmCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlRrmCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlRrmCfgEvent);

   if(event == EVTWRRRMCFG )
   {
      /* Start Application Configuration */
      wrSmRmCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRRRMCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlRrmCfgEvent */
#endif /*RM_INTF*/

/*
*
*       Fun:   wrSmHdlDamCfgEvent
*
*       Desc:  This function is handles events in EGTP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlDamCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlDamCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlDamCfgEvent);

   if(event == EVTWRDAMCFG )
   {
      /* Start Application Configuration */
      smBuildDamGenCfg();
      smBuildWrPjuLSapCfg(WR_PJ_SUID , WR_PJ_SPID);
      smBuildWrPjuLSapCfg(WR_PJ_SUID + 1, WR_PJ_SPID);
      smBuildWrEgtLSapCfg(WR_EG_SUID, WR_EG_SPID);
#ifdef TIP_UPPER_L2
      smBuildWrAppDamLSapCfg(WR_DAM_SUID,WR_DAM_SPID);
#endif
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRDAMCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlDamCfgEvent */


/*
*
*       Fun:   wrSmHdlAppCfgEvent
*
*       Desc:  This function is handles events in EGTP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlAppCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlAppCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlAppCfgEvent);

   if(event == EVTWRAPPCFG )
   {
      /* Start Application Configuration */
      wrSmWrCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRAPPCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlAppCfgEvent */

/*
*
*       Fun:   wrSmHdlRrcCfgEvent
*
*       Desc:  This function is handles events in EGTP App Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlRrcCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlRrcCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlRrcCfgEvent);

   if(event == EVTWRRRCCFG )
   {
      /* Start RRC Configuration */
      wrSmNhCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRRRCCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlRrcCfgEvent */

#ifdef PHY_ERROR_LOGING
/*
*       Fun:   wrSmSendUlAllocCfgReq
*
*       Desc:  This function is sends events for UL Alloc Configuration 
*
*       Ret:   None
*
*       Notes: <NONE>
*
*/
#ifdef ANSI
PUBLIC Void wrSmSendUlAllocCfgReq
(
SmPhyCmd phyCmd
)
#else
PUBLIC Void wrSmSendUlAllocCfgReq(phyCmd)
SmPhyCmd phyCmd;
#endif /* ANSI */
{
   TRC2(wrSmSendUlAllocCfgReq);

   /* Start Sch Alloc Configuration */
   wrSmRgSchUlAllocCfg(phyCmd);

   RETVOID;
} /* end of wrSmSendUlAllocCfgReq*/
#endif /* PHY_ERROR_LOGING */
/*
*
*       Fun:   wrSmHdlPdcpUlCfgEvent
*
*       Desc:  This function is handles events in RRC APP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_enb_init.c
*
*/


#ifdef ANSI
PUBLIC Void wrSmHdlPdcpUlCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlPdcpUlCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlPdcpUlCfgEvent);

   if(event == EVTWRPDCPCFG )
   {
      /* Start PDCP Configuration */
      wrSmPjUlCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRPDCPCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlPdcpCfgEvent */

/*
*
*       Fun:   wrSmHdlPdcpDlCfgEvent
*
*       Desc:  This function is handles events in RRC APP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_enb_init.c
*
*/


#ifdef ANSI
PUBLIC Void wrSmHdlPdcpDlCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlPdcpDlCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlPdcpDlCfgEvent);

   if(event == EVTWRPDCPCFG )
   {
      /* Start PDCP Configuration */
      wrSmPjDlCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRPDCPCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlPdcpCfgEvent */

/*
*
*       Fun:   wrSmHdlRlcUlCfgEvent
*
*       Desc:  This function is handles events in PDCP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_enb_init.c
*
*/


#ifdef ANSI
PUBLIC Void wrSmHdlRlcUlCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlRlcUlCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlRlcUlCfgEvent);

   if(event == EVTWRRLCCFG )
   {
      /* Start RLC Configuration */
      wrSmKwUlCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRRLCCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlRlcCfgEvent */

/*
*
*       Fun:   wrSmHdlRlcDlCfgEvent
*
*       Desc:  This function is handles events in PDCP Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_enb_init.c
*
*/


#ifdef ANSI
PUBLIC Void wrSmHdlRlcDlCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlRlcDlCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlRlcDlCfgEvent);

   if(event == EVTWRRLCCFG )
   {
      /* Start RLC Configuration */
      wrSmKwDlCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRRLCCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlRlcCfgEvent */

/*
*
*       Fun:   wrSmHdlMacCfgEvent
*
*       Desc:  This function is handles events in RLC Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlMacCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlMacCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlMacCfgEvent);

   switch (event)
   {
      case EVTWRMACCFG:
   {
      /* Start LTE MAC Configuration */
      wrSmRgCfg();
            break;
         }
      case EVTWRMACSCHDCFG:
         {
            /* Start LTE Schd Configuration */
            smBuildRgSchInsCfg();
            break;
         }
      default:
         {
            RLOG1(L_ERROR, "Invalid event [%d] received", event);
            break;
         } 
   }
   RETVOID;
} /* end of wrSmHdlMacCfgEvent */

#ifndef LTE_ENB_PAL
/*
*
*       Fun:   wrSmHdlCLCfgEvent
*
*       Desc:  This function is handles events in MAC Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlCLCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlCLCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlCLCfgEvent);

   if(event == EVTWRCLCFG )
   {
      /* Start LTE Convergence Layer Configuration */
      wrSmYsCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRCLCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlCLCfgEvent */
#endif

#ifndef LTE_ENB_PERF
/*
*
*       Fun:   wrSmHdlBndS1apStack
*
*       Desc:  This function is handles events in CL Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/


#ifdef ANSI
PUBLIC Void wrSmHdlBndS1apStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlBndS1apStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlBndS1apStack);

   if(event == EVTWRS1APSTKBND)
   {
      /*Bind the SCTP lower SAP with TUCL */
      smBindUnBindSbToLSap(SB_HI_SPID,ABND_ENA);
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRS1APSTKBND. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlCLCfgEvent */

/*
*
*       Fun:   wrSmHdlBndEgtpStack
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlBndEgtpStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlBndEgtpStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlBndEgtpStack);

   if(event == EVTWREGTPSTKBND)
   {
      /*Bind the EGTP lower SAP with */
      smBindUnBindEgToHitSap(EG_HI_SPID,ABND_ENA);
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWREGTPSTKBND. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlBndEgtpStack */

#ifdef LTE_HO_SUPPORT
/*
*
*       Fun:   wrSmHdlBndX2apStack
*
*       Desc:  This function is handles events in Egtp Stack Bind  done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/


#ifdef ANSI
PUBLIC Void wrSmHdlBndX2apStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlBndX2apStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlBndX2apStack);

   if(event == EVTWRX2APSTKBND)
   {
      /*Bind the X2AP lower SAP with SCTP */
      smBindUnBindCzToLSap(ABND_ENA);
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRX2APSTKBND. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlCLCfgEvent */
#endif /* LTE_HO_SUPPORT */
#endif /* LTE_ENB_PERF */

/*
*
*       Fun:   wrSmHdlBndRrmStack
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlBndRrmStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlBndRrmStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlBndRrmStack);

   if(event == EVTWRRRMSTKBND)
   {
      /*Bind the RRM with MAC */
      smBindUnBindRmToRgmSap(ABND);
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRRRMSTKBND. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlBndRgmStack */


/*
*
*       Fun:   wrSmSndRrmCellUpInd
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_enb_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmSndRrmCellUpInd
(
U8 event                   
)
#else
PUBLIC Void wrSmSndRrmCellUpInd(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmSndRrmCellUpInd);

   /*Bind the MAC lower SAP with CL */
#if 0
   smSendCellUpIndToRrm((U16)event);
#else
//CHINNA: temporary hardcoding CellId
   smSendCellUpIndToRrm(1);
#endif

   RETVOID;
} /* end of wrSmHdlBndRgmStack */

/*
*
*       Fun:   wrSmHdlBndMacStack
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlBndMacStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlBndMacStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlBndMacStack);

   macCfgInst = 0;

   if(event == EVTWRRRCSTKBND)
   {
      /*Bind the MAC lower SAP with CL */
      smBindUnBindRgToTfuSap(ABND);
   }
   else
   {
      RLOG1(L_ERROR, "Invalid event [%d] received", event);
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlBndMacStack */

/*
*
*       Fun:   wrSmHdlBndPdcpStack
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlBndPdcpStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlBndPdcpStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlBndPdcpStack);

   macCfgInst = 0;

   if(event == EVTWRRRCSTKBND)
   {
      /*Bind the MAC lower SAP with CL */
      smBindUnBindPjKwuSap((Inst)WR_SM_KWUL_INST, ABND); 
   }
   else
   {
      RLOG1(L_ERROR, "Invalid event [%d] received", event);
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlBndEgtpStack */

/*
*
*       Fun:   wrSmHdlBndDamStack
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlBndDamStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlBndDamStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlBndDamStack);

   macCfgInst = 0;

   if(event == EVTWRRRCSTKBND)
   {
      /*Bind the MAC lower SAP with CL */
      smBindUnBindWrToPjuSap(WR_SM_PJUL_INST, ABND_ENA);
   }
   else
   {
      RLOG1(L_ERROR, "Invalid event [%d] received", event);
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlBndEgtpStack */



#ifndef  TIP_L3_UL2_LL2_SPLIT
/*
*
*       Fun:   wrSmHdlBndRrcStack
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlBndRrcStack
(
U8 event
)
#else
PUBLIC Void wrSmHdlBndRrcStack(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlBndRrcStack);

   macCfgInst = 0;

   if(event == EVTWRRRCSTKBND)
   {
      /*Bind the MAC lower SAP with CL */
      smBindUnBindRgToTfuSap(ABND);
   }
   else
   {
      RLOG1(L_ERROR, "Invalid event [%d] received", event);
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlBndEgtpStack */
#endif
/*
*
*       Fun:   wrSmHdlEnbAlarms
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void  wrSmHdlEnbAlarms
(
U8 event
)
#else
PUBLIC Void wrSmHdlEnbAlarms(event)
U8  event;
#endif /* ANSI */
{
   Pst  wrPst;

   TRC2(wrSmHdlEnbAlarms);
   SM_SET_ZERO(&wrPst, sizeof(Pst));

   if(event == EVTWRENBALRMS)
   {
      /* Send Control request to enable alarms in reqd. layers */
#ifndef LTE_ENB_PERF
      smBuildSzGenCntrl();

#ifdef LTE_HO_SUPPORT
      smBuildCzGenCntrl();
#endif
#endif
      smBuildNhGenCntrl();
      smBuildWrGenCntrl();
      smBuildEgGenCntrl();

      smCb.smState = WR_SM_STATE_ENB_ALRMS_DONE;
      RLOG0(L_DEBUG, "ALARM - Reporting of alarms is enabled successfully");
      /* Trigger to next state */
#ifndef LTE_ENB_PERF
      WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRS1APSTKBND, WR_POOL, SM_SELECTOR_LC);
#else
      WR_FILL_PST(wrPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRRRCSTKBND, WR_POOL, SM_SELECTOR_LC);
#endif

      if(wrSmSelfPstMsg(&wrPst) != ROK)
      {
         RLOG_STR(L_FATAL, "Self post failed for the event [%s]",PRINT_STR(EVTWRS1APSTKBND));
      }
      else
      {
         RLOG0(L_INFO, "ENABLING OF ALARMS IS SUCCESSFULLY PERFORMED. ");
      } /* end of else part */

   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRENBALRMS. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */
   smBuildNhGenCntrl();
   RETVOID;
} /* end of wrSmHdlEnbAlarms */

/*
 *
 *       Fun:   wrSmHdlEnbDebugs
 *
 *       Desc:  This function is handles events in done state
 *
 *       Ret:   None
 *
 *       Notes: <NONE>
 *
 *       File:  wr_smm_init.c
 *
 */

#ifdef ANSI
PUBLIC Void wrSmHdlEnbDebugs
(
U8 event
)
#else
PUBLIC Void wrSmHdlEnbDebugs(event)
U8  event;
#endif /* ANSI */
{
   Pst lclPst;

   TRC2(wrSmHdlEnbDebugs);

   SM_SET_ZERO(&lclPst, sizeof(Pst));

   if(event == EVTWRENBDEBUGS)
   {
#ifndef LTE_ENB_PERF
      /* Send Control request to enable debugs */
      if((smCfgCb.hiDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_HI_DBG_MASK))
      {
         RLOG0(L_DEBUG, "Enabling TUCL Debug Prints");
         smBuildHiDbgCntrl();
         RETVOID;
      } /* end of if statement */
      /* Send Control request to enable debugs */
      if((smCfgCb.sbDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_SB_DBG_MASK))
      {
         RLOG0(L_DEBUG, "Enable SCTP Debug Prints");
         smBuildSbDbgCntrl();
         RETVOID;
      } /* end of if statement */
      /* Send Control request to enable debugs */
      if((smCfgCb.szDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_SZ_DBG_MASK))
      {
         RLOG0(L_DEBUG, "Enable S1AP Debug Prints");
         smBuildSzDbgCntrl();
         RETVOID;
      } /* end of if statement */
      /* Send Control request to enable debugs */
      if((smCfgCb.egDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_EG_DBG_MASK))
      {
         RLOG0(L_DEBUG, "Enable EGTP Debug Prints");
         smBuildEgDbgCntrl();
         RETVOID;
      } /* end of if statement */

#ifdef LTE_HO_SUPPORT
      /* Send Control request to enable debugs */
      if((smCfgCb.czDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_CZ_DBG_MASK))
      {
         RLOG0(L_DEBUG, "Enable X2AP Debug Prints");
         smBuildCzDbgCntrl();
         RETVOID;
      } /* end of if statement */
#endif
#endif
      /* Send Control request to enable debugs */
      if((smCfgCb.wrDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_WR_DBG_MASK))
      {
         RLOG0(L_DEBUG, "Enable eNodeBApp Debug Prints");
         smBuildWrDbgCntrl();
         RETVOID;
      } /* end of if statement */
      /* Send Control request to enable debugs */
      if((smCfgCb.nhDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_NH_DBG_MASK))
      {
         RLOG0(L_DEBUG, "Enable RRC Debug Prints");
         smBuildNhDbgCntrl();
         RETVOID;
      } /* end of if statement */
      /* Send Control request to enable debugs */
      if((smCfgCb.kwDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_KW_DBG_MASK))
      {
         RLOG0(L_DEBUG, "Enable RLC  Debug Prints");
         smBuildKwDbgCntrl();
         RETVOID;
      } /* end of if statement */
      /* Send Control request to enable debugs */
      if((smCfgCb.rgDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_RG_DBG_MASK))
      {
         RLOG0(L_DEBUG, "Enable MAC  Debug Prints");
         smBuildRgDbgCntrl();
         RLOG0(L_DEBUG, "Enable Scheduler  Debug Prints");
         smBuildSchdDbgCntrl();
         RETVOID;
      } /* end of if statement */
#ifdef YS_PICO
      /* Send Control request to enable debugs */
      if((smCfgCb.ysDbg == 1) && !(smCfgCb.smDbgMsk & WR_SM_YS_DBG_MASK))
      {
         RLOG0(L_DEBUG, "Enable CL Debug Prints");
         smBuildYsDbgCntrl();
         RETVOID;
      } /* end of if statement */
#endif /* YS_PICO */ 
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRENBDEBUGS. Received event %s ",
         wrSmmPrintSmmEvent(event));
      RETVOID;
   } /* end of else part */


   /* Assuming after all Debug Cntrl Reqs. */
   smCb.smState = WR_SM_STATE_ENB_LOG_DONE;
   RLOG0(L_DEBUG, "Enabling of Debug prints is success");
   WR_FILL_PST(lclPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRENBALRMS, WR_POOL, SM_SELECTOR_LC);
   if (wrSmSelfPstMsg(&lclPst) != ROK)
   {
      RLOG_STR(L_FATAL, "Self post failed for the event [%s]",PRINT_STR(EVTWRENBALRMS));
   }

   RETVOID;
} /* end of wrSmHdlEnbDebugs */

/*
*
*       Fun:   wrSmHdlInitS1Setup
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void  wrSmHdlInitS1Setup
(
U8 event
)
#else
PUBLIC Void wrSmHdlInitS1Setup(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlInitS1Setup);

   if(event == EVTWRINITS1SETUP)
   {
      /* Send Control request to APP to indicate binding is complete*/
      smBuildWrS1InitCntrl();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRINITS1SETUP. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlInitS1Setup*/

/*
*
*       Fun:   wrSmHdlInitCellCfg
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void  wrSmHdlInitCellCfg
(
U8 event
)
#else
PUBLIC Void wrSmHdlInitCellCfg(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlInitCellCfg);

   if(event == EVTWRCELLCFG)
   {
      /* Send Control request to APP to indicate binding is complete*/
      smBuildWrCellCntrl();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRCELLCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlInitCellCfg */

#ifdef LTE_HO_SUPPORT
/*
*
*       Fun:   wrSmHdlInitX2Setup
*
*       Desc:  This function is handles events in done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void  wrSmHdlInitX2Setup
(
U8 event
)
#else
PUBLIC Void wrSmHdlInitX2Setup(event)
U8  event;
#endif /* ANSI */
{
   U8       cellCfgIndx = 0;

   TRC2(wrSmHdlInitX2Setup);

   if(event == EVTWRINITX2SETUP)
   {
      /* Send Control request */
      /* MultiCell - Send X2 Control Request for eNBs cfgd as 
       * Neighbors in all serving cells. */
      for(cellCfgIndx = 0; cellCfgIndx < wrSmDfltNumCells; cellCfgIndx++)
      {
         smBuildWrX2InitCntrl(cellCfgIndx);
      }
   }
#ifdef WR_RSYS_OAM
   else if(event == EVTWRSTARTDYNUPDATE)
   {
     MsmConfigComplete();
   }
#endif
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRINITX2SETUP. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlInitX2Setup*/
#endif

/*
*
*       Fun:  wrSmmSetBandwidth 
*
*       Desc:  Function which changes the bandwidth prameter depending on the 
*              bandwidth configured. Currently function supports 5MHZ and 10MHZ
*              configuration only
*
*       Ret:   Void
*
*       Notes: None
*
*       File:  wr_smm_init.c
*
*/

PUBLIC Void wrSmmSetBandwidth
(
U32    freqBandwidth,
U8     loopCnt
)
{

   switch(freqBandwidth)
   {
      case WR_FREQ_BANDWIDTH_5MHZ:
      {
         lteeNodeBparams[loopCnt].lteCellMibCfgGrp.dlBw[0] = CTF_BW_RB_25;      /* 25 RBS */ 
         lteeNodeBparams[loopCnt].lteULFrequencyInfo.ulBandwidth        = CTF_BW_RB_25;      /* 25 RBS */ 
         wrSmDfltMaxUlBwPerUe    = 25;
         wrSmDfltMaxDlBwPerUe    = 25;
         wrSmDfltMaxDlRetxBw     = 25;
         wrSmDfltPuschSubBndStrt = 2;
         wrSmDfltPuschNoSubbnds  = 4;
         wrSmDfltPuschSubBandSz  = 5;
         /* Fix for 5MHZ Band 13 */
         wrSmDfltZeroCorrelZoneCfg = 0x0A;
         /*ccpu00130314:  Fix for 5MHZ RACH issue. for 5MHZ range for FreqOffset is 0-19*/ 
         wrSmDfltPrachFreqOffset   = 0x00;
          
	     wrSmNumUesGrpPwrCtrlFmt3  = 12; 
	     wrSmNumUesGrpPwrCtrlFmt3A = 25; 
      }
      break;
      /* By default the configuration is made for 10 Mhz, still overwriting the 
       * values*/
      case WR_FREQ_BANDWIDTH_10MHZ:
      {
         lteeNodeBparams[loopCnt].lteCellMibCfgGrp.dlBw[0] = CTF_BW_RB_50;      /* 50 RBS */ 
         lteeNodeBparams[loopCnt].lteULFrequencyInfo.ulBandwidth       = CTF_BW_RB_50;      /* 50 RBS */ 
         wrSmDfltMaxUlBwPerUe    = 50;
         wrSmDfltMaxDlBwPerUe    = 50;
         wrSmDfltMaxDlRetxBw     = 50;
         wrSmDfltPuschSubBndStrt = 1;
         wrSmDfltPuschNoSubbnds  = 8;
         wrSmDfltPuschSubBandSz  = 6;
        /* Note :- wrSmDfltZeroCorrelZoneCfg not required for 10 Mhz as 
                   default configuration is 10 Mhz.
        */ 
	     wrSmNumUesGrpPwrCtrlFmt3  = 13; 
	     wrSmNumUesGrpPwrCtrlFmt3A = 27; 
      }
      break;
      case WR_FREQ_BANDWIDTH_15MHZ:
      {
         lteeNodeBparams[loopCnt].lteCellMibCfgGrp.dlBw[0] = CTF_BW_RB_75;      /* 75 RBS */ 
         lteeNodeBparams[loopCnt].lteULFrequencyInfo.ulBandwidth        = CTF_BW_RB_75;      /* 75 RBS */ 
         wrSmDfltMaxUlBwPerUe    = 75;
         wrSmDfltMaxDlBwPerUe    = 75;
         wrSmDfltMaxDlRetxBw     = 75;
         wrSmDfltPuschSubBndStrt = 1;
         wrSmDfltPuschNoSubbnds  = 12;
         wrSmDfltPuschSubBandSz  = 6;
	     wrSmNumUesGrpPwrCtrlFmt3  = 13; 
	     wrSmNumUesGrpPwrCtrlFmt3A = 27; 
      }
      break;
      case WR_FREQ_BANDWIDTH_20MHZ:
      {
         lteeNodeBparams[loopCnt].lteCellMibCfgGrp.dlBw[0] = CTF_BW_RB_100;        /* 100 RBS */ 
         lteeNodeBparams[loopCnt].lteULFrequencyInfo.ulBandwidth        = CTF_BW_RB_100;      /* 50 RBS */ 
         wrSmDfltMaxUlBwPerUe    = 100;
         wrSmDfltMaxDlBwPerUe    = 100;
         wrSmDfltMaxDlRetxBw     = 100;
         wrSmDfltPuschSubBndStrt = 1;
         wrSmDfltPuschNoSubbnds  = 32;
         wrSmDfltPuschSubBandSz  = 3;
         /*ccpu00139148 - Grouping number of UEs depending on Channel BW */
         wrSmNumUesGrpPwrCtrlFmt3  = 14;
         wrSmNumUesGrpPwrCtrlFmt3A = 28;
      }
      break;
   }

   RETVOID;
}


/*
*
*       Fun:   wrCfgGetTagNum
*
*       Desc:  Retrive the Tag number corresponds to the tag string.
*
*       Ret:   Void
*
*       Notes: None
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void smWrCfgGetTagNum
(
U8* tag,
U16* tagNum
)
#else
PUBLIC Void smWrCfgGetTagNum(tag, tagNum)
U8* tag;
U16* tagNum;
#endif
{
   S16 loopCnt = 0;

   TRC2(smWrCfgGetTagNum);

   for (loopCnt = 0; loopCnt < (MAX_CFG_PARAM); loopCnt++)
   {
      if (0 == strcmp((S8 *)tag,wrCfgTagLst[loopCnt]))
      {
         *tagNum = loopCnt;
         break;
      }
   }/* End of for */
   RETVOID;
}/* End of wrCfgGetTagNum()*/

/*
*
*       Fun:   wrCfgValdtInput
*
*       Desc:  This function validates the format of the input and 
*              throws an error in case it's wrong.
*
*       Ret:   Void
*
*       Notes: None
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void wrCfgValdtInput
(
U8* input,
Bool* status,
U8* noOfElem
)
#else
PUBLIC Void wrCfgValdtInput(input, status, noOfElem)
U8* input;
Bool* status;
U8* noOfElem;
#endif
{
   U16 strLen = 0;
   S16 loopCnt = 0;
   U8 lCnt = 0;
   U8 rCnt = 0;
   U8 dupCnt = 0;   
   U8 numOfComa = 0;
   TRC2(wrCfgValdtInput);
   strLen = strlen((S8 *)input);
   while (loopCnt < strLen)
   {
      if ('{' == input[loopCnt])
      {
        lCnt++;
      }
      else if ('}' == input[loopCnt])
      {
        rCnt++;
        /* Calculating the number of inner structures and arrays */
        if ((lCnt - rCnt) >= 2)
        {
           dupCnt++;
        }
      }
      else if (' ' == input[loopCnt])
      {
         RLOG0(L_ERROR, " Please check the "
           "Configuration format.There should not be any space in the configuration values.");
         *status = FALSE;
         break;
      }
      else if ((',' == input[loopCnt]) && (',' == input[loopCnt + 1]))      
      {
         RLOG0(L_ERROR, " Please check the "
         "Configuration format.Parameter value is  missing between"
         " two commas.");
         *status = FALSE;
         break;
      }
      else if (('}' == input[loopCnt]) && ('{' == input[loopCnt + 1]))      
      {
         RLOG0(L_ERROR, " Please check the Configuration format. Comma is missing.");
         *status = FALSE;
         break;
      }
      else if (',' == input[loopCnt])
      {
         numOfComa++;
      }
      loopCnt++;
   }/* End of while()*/
   if (FALSE != *status)
   {
      if (lCnt != rCnt)
      {
         RLOG0(L_ERROR, " Please check the"
         " Configuration format. '{' or '}' missed out or remove the space if presents");
         *status = FALSE;
      }
      else
      {
         /* Condition to check whether the input is a simple array of system
            defined data types or a single user defined structure.*/

         if (lCnt == 1)
         {
            /* Calculating the number of elements in the array or structure using the 
               number of commas */
            *noOfElem = numOfComa + 1;
            *status = TRUE;
         }
         else
         {
            /* Calculating the number of structures if the input is array 
             * of structures. deduction of 1 is for the outer most braces and 
             * deduction of dupCnt is for inner structures if any */
            *noOfElem = (lCnt - 1) - dupCnt;
            *status = TRUE;
         }
      }
   }/* End of if ()*/
   RETVOID;
}/* End of wrCfgValdtInput() */

/*
*
*       Fun:   wrCfgGetParamVal
*
*       Desc:  This function parses the validated input and makes the
*              the list of parameters and returns the list and the number of parameters.
*
*       Ret:   Void
*
*       Notes: None
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void wrCfgGetParamVal
(
U8* tagVal,
U8 paramLst[][100],
U16* noOfParams
)
#else
PUBLIC Void wrCfgGetParamVal(tagVal, paramLst[][100], noOfParams)
U8* tagVal;
U8 paramLst[][100];
U16* noOfParams;
#endif
{
   U16 strLen = 0;
   S16 loopCnt = 0;
   U8 loopCnt1 = 0;
   U8 param[100];

   TRC2(wrCfgGetParamVal);

   strLen = strlen((S8 *)tagVal);
   while (loopCnt < strLen)
   {
      if (('{' != tagVal[loopCnt]) && ('}' != tagVal[loopCnt]) && 
         (',' != tagVal[loopCnt]))   
      {
         loopCnt1 = 0;
         while((',' != tagVal[loopCnt]) && ('}' != tagVal[loopCnt]))
         {
            param[loopCnt1++] = tagVal[loopCnt];
            loopCnt++;
         }
         param[loopCnt1] = '\0'; 
         /* Increment the param count for this parameter */
         strcpy((S8 *)paramLst[*noOfParams], (S8 *)param);
         (*noOfParams)++;
      }
      else
      {
         /* skipping the charecter */
         loopCnt += 1;
      }
   }/* End of while()*/
   RETVOID;
}/* End of wrCfgGetParamVal() */

#ifdef WR_TEST_CODE

/*
*
*       Fun:   wrIBPrintMenu
*
*       Desc:  Print Menu
*
*       Ret:   None.
*
*       Notes: None
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PRIVATE Void wrIBPrintMenu
(
Void
)
#else
PRIVATE Void wrIBPrintMenu()
#endif
{
   Txt pBuf[512];

   TRC2(sbIBPrintMenu);

   sprintf(pBuf, "\n\t\t *** List of available commands are: ***\n");
   SPrint(pBuf);
   sprintf(pBuf, "1.help       ----- Display help\n");
   SPrint(pBuf);
   sprintf(pBuf, "2.overload   ----- Move ENB into overloaded state\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|Command             | Action|Input1   |Input2  | Description                            |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|snds1cfgupd         | NA    | NA      |NA      | send s1 config update                  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|snds1cfgupdfail     | on    | NA      |NA      | enable sending s1 config update fail   |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable sending s1 config update fail  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|s1partrst           | NA    | NA      |NA      | send s1ap partial reset                |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|s1fullrst           | NA    | NA      |NA      | send s1ap full reset                   |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|sndx2setupfail      | on    | 0       |NA      | enable sending x2 setup fail without   |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | time to wait                           |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | on    | 1       |NA      | enable sending x2 setup fail with time |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | to wait                                |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable sending x2 setup fail          |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|dntrspx2setup       | on    | NA      |NA      | enable discarding x2setup request      |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable discarding x2setup request     |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|sndx2cfgupdfail     | on    | 0       |NA      | enable sending x2 config update fail   |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | without time to wait                   |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | on    | 1       |NA      | enable sending x2 config updatefail    |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | with time to wait                      |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable sending x2 config update fail  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|--------------------------------------  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|dntrspx2cfgupd      | on    | NA      |NA      | enable discarding x2 config update     |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable discarding x2 config update    |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|--------------------------------------  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|dntrspx2rst         | on    | NA      |NA      | enable discarding x2 reset             |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable discarding x2 reset            |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|--------------------------------------  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|sndx2errind         | on    | NA      |NA      | enable sending x2 error indication     |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable sending x2 error indication    |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|--------------------------------------  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|sndx2rst            | NA    | NA      |NA      | send x2 reset request                  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|--------------------------------------  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|sndrabrls           | NA    | NA      |NA      | initiate rab release procedure         |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|--------------------------------------  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|sndenberrind        | on    | NA      |NA      | enable sending enodeB error indication |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable sending enodeB error indication|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|sndnasnondelind     | on    | NA      |NA      | enable sending NAS non delivery        |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | indication                             |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable sending NAS non delivery       |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | indication                             |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|dntrsps1cfgupd      | on    | NA      |NA      | enable discarding s1 config update     |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | message                                |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable discarding s1 config update    |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | message                                |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|sndendcfgupdrx      | on    | NA      |NA      | enable sending config update response  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable sending config update response |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|snds1setuprx        | on    | NA      |NA      | enable sending s1 setup response       |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable sending s1 setup response      |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|drprrcconnsetupcmplt| on    | NA      |NA      | enable discarding rrc connection setup |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | complete                               |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable discarding rrc connection setup|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | complete                               |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|drprrcrelcfm        | on    | NA      |NA      | enable discarding rrc release confirm  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable discarding rrc release confirm |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|drpuecapinfo        | on    | NA      |NA      | enable discarding ue capability info   |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable discarding ue capability info  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|drpseccmplt         | on    | NA      |NA      | enable discarding security mode        |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | complete                               |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable discarding security mode       |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | complete                               |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|drprrcrecfgcmlpt    | on    | NA      |NA      | enable discarding rrc reconfig complete|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable discarding rrc reconfig        |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | complete                               |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|drprrcreestabcmplt  | on    | NA      |NA      | enable discarding rrc restablishment   |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | complete                               |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable discarding rrc restablishment  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | complete                               |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|dbgp                | on    | layer   |1       | send debug enable in the layer with    |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       | name    |        | debug level as 1                       |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | on    | layer   |2       | send debug enable in the layer with    |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       | name    |        | debug level as 2                       |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | on    | layer   |3       | send debug enable in the layer with    |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       | name    |        | debug level as 3                       |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | on    | layer   |4       | send debug enable in the layer with    |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       | name    |        | debug level as 4                       |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | layer   |NA      | send debug disable in the layer        |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       | name    |        |                                        |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|macstats            | on    | NA      |NA      | enable MAC CQI & HARQ ACK/NACK stats   |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable  MAC CQI & HARQ ACK/NACK stats |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
#ifdef PHY_ERROR_LOGING
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|phylogging          | on    | NA      |NA      | enable PHY logging                     |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | NA      |NA      | disable PHY logging                    |\n");
   SPrint(pBuf);
/* LTE_ADV starts */
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|ltea                | on    | abs     |NA      | enable Almost Blanking Subframe (ABS)  |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | Feature                                |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | on    | re      |NA      | enable Range Extension(RE) Feature     |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | on    | sfr     |NA      | enable Soft Frequency Reuse(SFR)       |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | Feature                                |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | on    | dsfr    |NA      | enable Dynamic Soft Frequency Reuse    |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | (DSFR) Feature                         |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | abs     |NA      | disable Almost Blanking Subframe       |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | (ABS) Feature                          |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | re      |NA      | disable Range Extension(RE) Feature    |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | sfr     |NA      | disable Soft Frequency Reuse(SFR)      |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | Feature                                |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    | off   | dsfr    |NA      | disable Dynamic Soft Frequency Reuse   |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|                    |       |         |        | (DSFR) Feature                         |\n");
   SPrint(pBuf);
/* LTE_ADV ends */
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
    /* ccpu00125303:Added debug prints for cpu load indication */
   SPrint(pBuf);
#endif
   sprintf(pBuf, "\t|loadInd             | on    | CPU %%   |NA      | Trigger CPU load indication            |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|ipchange            | on    | w.x.y.z  |NA      | Trigger IP change                      |\n");
   SPrint(pBuf);
   sprintf(pBuf, "\t|--------------------|-------|---------|--------|----------------------------------------|\n");
   SPrint(pBuf);

   

   RETVOID;

} /* wrIBPrintMenu */


/*
 *
 *       Fun:   wrISStrtoul
 *
 *       Desc:  wrapper for strtoul 
 *
 *       Ret:    ascii string to long value 
 *
 *       Notes: None
 *
 *       File:  
 *        
 */
#ifdef ANSI
PRIVATE U32 wrISStrtoul
(     
 CONSTANT S8 *str
)          
#else
PRIVATE U32 wrISStrtoul(str)
CONSTANT S8 *str;
#endif   
{
      TRC2(wrISStrtoul)
         RETVALUE(strtoul(str, NULLP, NULLP));
                 
} /* end of wrISStrtoul */


/*
 *
 *      Fun:   wrIBParseMenu
 *
 *      Desc:  This function parses the menu option selected
 *
 *      Ret:   RETVOID,
 *
 *      Notes: None.
 *
 *      File:  wr_smm_init.c
 *
 */

#ifdef ANSI
PRIVATE Void wrIBParseMenu
(
TstTkn     *token             /* Command Name */
)
#else
PRIVATE Void wrIBParseMenu(token)
TstTkn     *token;            /* Command Name */
#endif
{
   Txt  pBuf[100];
   S32  cmd;
   S32  arg1 = NULLP;
   S32  arg2;
   U32  memAvail;
#if defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION)
   U32 memIndx;
#endif

   TRC2(wrIBParseMenu)

   cmd = osMatchKeyword(wrCliMenuKey, (S8 *)token->tok.val);
   if (token->nmbArgs >= 1)
   {
      arg1 = osMatchKeyword(wrCliSecArgKey ,(S8*)token->args[0].val);

      if(! (arg1 == WR_ON || arg1 == WR_OFF))
      {
         sprintf(pBuf, "CLI Error: ** Second Option is invalid **\n");
         SPrint(pBuf);
         RETVOID;
      }     
   }

   switch (cmd)
   {
      case  0: /* help */ 
         {
            wrIBPrintMenu();
         }
         break;

      case  1:  /* enbovld */ 
         {
            if (token->nmbArgs != 2 )
            {
               sprintf(pBuf, "CLI Error: ** For endovld Third Option is \
                     invalid **\n");
               SPrint(pBuf);
               break;
            }
            arg2 =  wrISStrtoul((S8*)token->args[1].val);
            if (arg1 == WR_ON)
            {
               switch(arg2)
               {
                  case 1:
                     {
                        smSndWrCellReCfgSib2(0x08);
                        ALARM("Triggered eNB Overload with CRITICAL\n");
                     }
                     break;
                  case 2:
                     {
                        smSndWrCellReCfgSib2(0x04);
                        ALARM("Triggered eNB Overload with MAJOR\n");
                     }
                     break;
                  case 3:
                     {
                        smSndWrCellReCfgSib2(0x02);
                        ALARM("Triggered eNB Overload with MINOR\n");
                     }
                     break;

               }
            }
            else if(arg1 == WR_OFF)
            {
               smSndWrCellReCfgSib2(0x01);
               ALARM("Triggered eNB Overload STOP\n");
            }
         }
         break;

      case  2:  /* snds1cfgupd */
         {
            U8       cellCfgIndx = 0;
            /* Modify TAC and cell id */
            ALARM("Trigger S1 & X2 Cfg Upd \n");
            for(cellCfgIndx = 0; cellCfgIndx < wrSmDfltNumCells; cellCfgIndx++)
            {
               smSndWrModCellCfg(cellCfgIndx);
            }
         }
         break;

      case  3:  /* snds1cfgupdfail */
         {
            if (arg1 == WR_ON)
            {
               ALARM("Enable MME Cfg Upd fail \n");
               wrTgrMmeCfgUpdFail = TRUE;
            }
            else 
            {
               ALARM("Disable MME Cfg Upd fail \n");
               wrTgrMmeCfgUpdFail = FALSE;
            }
         }
         break;

      case  4: /* dbgp */ 
         {      
         }
         break;

      case  5: /* s1partrst */ 
         {
            ALARM("Trigger Partial S1-Reset \n");
            smBuildWrPartRstCntrl();
         }
         break;
      case  6:  /* s1fullrst */
         {
            ALARM("Trigger Full S1-Reset \n");
            smBuildWrFullRstCntrl();
         }
         break; 
      case  7:  /*  sndx2setupfail */
         {
            if (token->nmbArgs != 2 )
            {
               sprintf(pBuf, " Error : **  Argument Missing ** sndx2setupfail\
                     on/off with_timetowait\n");
               SPrint(pBuf);
               break;
            }
            arg2 =  wrISStrtoul((S8*)token->args[1].val); 

            if(arg2 == 1)
            {
               if (arg1 == WR_ON )
               {
                  wrTgrX2SetupFail = TRUE;
               }
               else
               {
                  wrTgrX2SetupFail =  FALSE;
               }
            }
            else
            {
               if (arg1 == WR_ON )
               {
                  wrTgX2SetupFailWoTW = TRUE;
               }
               else 
               {
                  wrTgX2SetupFailWoTW = FALSE;
               }
            }
         }
         break; 
      case  8:  /* dntrspx2setup */
         {
            if (arg1 == WR_ON )
            {
               wrDntRspX2Setup = TRUE;
            }
            else 
            {
               wrDntRspX2Setup = FALSE;
            }     
            ALARM("Enable/Disable X2 Setup retransmission:\
                  wrDntRspX2Setup = %d\n", wrDntRspX2Setup);
         }
         break; 
      case  9:  /* sndx2cfgupdfail */
         {
            if (token->nmbArgs != 2 )
            {
               sprintf(pBuf, " Error : **  Argument Missing ** sndx2cfgupdfail\
                     on/off with_timetowait\n");
               SPrint(pBuf);
               break;
            }
            arg2 =  wrISStrtoul((S8*)token->args[1].val); 

            if(arg2 == 1)
            {
               if (arg1 == WR_ON )
               {
                  wrTgrX2CfgUpdFail = TRUE;
               }
               else 
               {
                  wrTgrX2CfgUpdFail = FALSE;
               }       
            }
            else
            {
               if (arg1 == WR_ON )
               {
                  wrTgrX2CfgUpdFailWoTW = TRUE;
               }
               else 
               {
                  wrTgrX2CfgUpdFailWoTW = FALSE;
               }
            }      
            ALARM("Enable/Disable X2 CfgUpd Fail :\
                  wrTgrX2CfgUpdFail = %d\n", wrTgrX2CfgUpdFail);
         }
         break;
      case 10:  /* dntrspx2cfgupd */
         {
            if (arg1 == WR_ON )
            {
               wrDntRspX2CfgUpd = TRUE;
            }
            else 
            {
               wrDntRspX2CfgUpd = FALSE;
            }      
            ALARM("Enable/Disable X2 CfgUpd Retransmission: \
                  wrDntRspX2CfgUpd = %d\n", wrDntRspX2CfgUpd);
         }
         break;
      case 11: /* dntrspx2rst */ 
         {
            if (arg1 == WR_ON )
            {
               wrDntRspX2Reset = TRUE;
            }
            else 
            {
               wrDntRspX2Reset = FALSE;
            }      

            ALARM("Enable/Disable X2 Reset Retransmission:\
                  wrDntRspX2Reset = %d\n", wrDntRspX2Reset);
         }
         break;
      case 12: /* sndx2errind */
         {
            if (arg1 == WR_ON )
            {
               wrTrgX2ErrInd = TRUE;
            }
            else 
            {
               wrTrgX2ErrInd = FALSE;
            }      
         }
         break;
      case 13: /* sndx2rst */
         {
            ALARM("Tiggering X2-Reset \n");
            /* Trigger X2 Reset To all Neighbor Enb's */
            smBuildNghRstCntrl();
         }
         break;
      case  14: /* memstatus */
         {
#if defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION)
            for(memIndx = 0; memIndx < 4/* (SS_MAX_REGS)*/; memIndx++)
            {
               SRegInfoShow(memIndx, &memAvail);
               memAvail = 0;
            }
#else
            SRegInfoShow(DFLT_REGION, &memAvail);
#endif  
            /* Statistics print */
            wrUmmEnbStats();
         }
         break;
      case 15: /* sndrabrls*/
         {
            smBuildWrErabRelIndCntrl();
         }
         break;
      case 16: /* sndenberrind */
         {
            if (arg1 == WR_ON )
            {
               wrTgrEnbErrInd = TRUE;
            }
            else 
            {
               wrTgrEnbErrInd = FALSE;
            }      
         }
         break;
      case 17: /* sndnasnondelind */
         {
            if (arg1 == WR_ON )
            {
               wrTrgNasNonDlvrInd = TRUE;
            }
            else 
            {
               wrTrgNasNonDlvrInd = FALSE;
            }      
         }
         break;
      case 18: /* dntrsps1cfgupd */
         {
            if (arg1 == WR_ON )
            {
               wrDntRspMmeCfgUpd = TRUE;
            }
            else 
            {
               wrDntRspMmeCfgUpd = FALSE;
            }      
         }
         break;
      case 19: /* sndendcfgupdrx */
         {
            if (arg1 == WR_ON )
            {
               wrTgrEnbCfgUpdRtx = TRUE;
            }
            else 
            {
               wrTgrEnbCfgUpdRtx = FALSE;
            }      
         }
         break;
      case 20: /* snds1setuprx */
         {
            if (arg1 == WR_ON )
            {
               wrTgrS1SetupRtx = TRUE;
            }
            else 
            {
               wrTgrS1SetupRtx = FALSE;
            }      
         }
         break;
      case 23: /* drprrcconnsetupcmplt */
         {
            if (arg1 == WR_ON )
            {
               wrTrgRrcConTO = TRUE;
            }
            else 
            {
               wrTrgRrcConTO = FALSE;
            }      
         }
         break;
      case 24: /* drprrcrelcfm */
         {
            if (arg1 == WR_ON )
            {
               wrTrgRrcConRelTO = TRUE;
            }
            else 
            {
               wrTrgRrcConRelTO = FALSE;
            }      
         }
         break;
      case 25: /* drpuecapinfo  */
         {
            if (arg1 == WR_ON )
            {
               wrTrgUeCapTO = TRUE;
            }
            else 
            {
               wrTrgUeCapTO = FALSE;
            }      
         }
         break;
      case 26: /* drpseccmplt */
         {
            if (arg1 == WR_ON )
            {
               wrTrgSecTO = TRUE;
            }
            else 
            {
               wrTrgSecTO = FALSE;
            }      
         }
         break;
      case 27: /* drprrcrecfgcmlpt */
         {
            if (arg1 == WR_ON )
            {
               wrTrgRrcReConTO = TRUE;
            }
            else 
            {
               wrTrgRrcReConTO = FALSE;
            }      
         }
         break;
      case 28: /* drprrcreestabcmplt */
         {
            if (arg1 == WR_ON )
            {
               wrTrgRrcRestTO = TRUE;
            }
            else 
            {
               wrTrgRrcRestTO = FALSE;
            }      
         }
         break;
       case 29: /* enbportlog */
         {
         }
         break;
      case 30: /* trgRrcRestTO */
         {
            wrTrgRrcRestTO = (wrTrgRrcRestTO)?FALSE:TRUE;
         }
         break;
      case 31: /* loadInd */
         {
            ALARM("Tiggering Load Indication\n");

            if (token->nmbArgs != 2 )
            {
               sprintf(pBuf, " Error : ** Token Missing **\n");
               SPrint(pBuf);
               break;
            }
            /* Choice, at present only 1 (CPU load) is supported */
            arg1 =  wrISStrtoul((S8*)token->args[0].val);

            /* Value */
            arg2 =  wrISStrtoul((S8*)token->args[1].val);

            /* Modify CPU Load using Enodeb reconfiguration */
#ifdef RM_INTF
            if(smSendCpuLoadToRrm((U8)arg2) != ROK)
            {
               ALARM("Failed to send EnbSta indication to RRM\n");
            }
#endif

            if (smSndLoadInd(WRSM_ENB_CPU_LOAD, arg2) != ROK)
            {
               ALARM("Load indication failed\n");
            }

         }
         break;
      case 32: /* printNrInfo */
         {
            ALARM("Tiggering ANR to print Neighbour cell Information\n");
            smBuildAnrPrintCntrl();
         }
         break;
#ifdef PHY_ERROR_LOGING
      case 33: /* macstats */
         {
            ALARM("Tiggering Mac Stats\n");

            if(arg1 == WR_ON)
            {
               /* send data the updated data to MAC Sch */
               wrSmSendUlAllocCfgReq(PHY_CMD_START_TEST);
            }
            else
            {
               /* send data the updated data to MAC Sch */
               wrSmSendUlAllocCfgReq(PHY_CMD_STOP_TEST);   
            }
         }
         break;

      case 34: /* phylogging */
         {
            ALARM("Tiggering PHY logging\n");

            if(arg1 == WR_ON)
            {
               /* send data the updated data to MAC Sch */
               wrSmSendUlAllocCfgReq(PHY_CMD_ENABLE_LOG);
            }
            else
            {
               /* send data the updated data to MAC Sch */
               wrSmSendUlAllocCfgReq(PHY_CMD_DISABLE_LOG);   
            }
         }
         break;
#endif /* PHY_ERROR_LOGING */
#ifdef E_TM
      case 35: /* etmtest */
         {
            if ( arg1 == WR_ON ) 
            {
               ALARM("Command Enetered: etmtest on \n");
               if ( token->nmbArgs != 2 ) 
               {
                  ALARM("Wrong Usage of the command!!!\n");
                  ALARM("Usage: etmtest on/off < test mode >\n");
                  break;
               }
               arg2 =  wrISStrtoul((S8*)token->args[1].val);
               if ( arg2 < 1 || arg2 > 6 ) 
               {
                  ALARM("Error(Val = %ld): Invalid Test Model. Valid TM: 1 to 6 \n", arg2); 
                  break;
               }
               if ( etmCellState == ETM_CELL_STATE_IDLE )
               {
                  ALARM("Cell Cfg Has not been done!!\n");
                  break; 
               }
               else if ( etmCellState == ETM_CELL_STATE_UP )
               {
                  ALARM("Already test is sarted, try 'etmtest off', before starting new test\n");
                  break;
               }
               /* Send ETM Init */ 
               wrSmDfltEtmId = arg2;
               RLOG1(L_ERROR,"Entered Test Model = %ld", wrSmDfltEtmId);
               wrSmYsEtmCfg();
            }
            else if ( arg1 == WR_OFF ) 
            {
               ALARM("Command Enetered: etmtest off \n");
               if ( etmCellState == ETM_CELL_STATE_IDLE || etmCellState == ETM_CELL_STATE_CFG ) 
               {
                  ALARM("Test has not been started!!\n");
                  break;
               }
               /* Send ETM_STOP request  */
               smBuildYsEtmCntrl(ADISIMM);
            }
         }
         break;
#endif /* E_TM */
     case 36:
             if(WR_ON == arg1)
             {
                 CmInetAddrInfo addrInfo;
                 CmInetAddrInfo *res = NULLP;
                 S16 ret;

                 if(token->nmbArgs!=2)
                 {
                   ALARM("Usage:ipchange on <ip address in format of w.x.y.z>!!\n");
                    break;
                 } 
                 ret = cmInetGetAddrInfo((S8 *)token->args[1].val, NULLP,&addrInfo,&res);
                 if(ret != ROK)
                 {
                      if(res)
                      {
                         cmInetFreeAddrInfo(res);
                      }
                      ALARM("Validation of IP address failed:[%s]",(S8 *)token->args[1].val);
                      break;
                 }

                if (res && res->ai_family == AF_INET)
                {
                  cmInetAddr((S8 *)token->args[1].val,&(fapParameters.lteEnodebIpAddr.enbIpAddr));
                  fapParameters.lteEnodebIpAddr.enbIpAddr = \
                                  CM_INET_HTON_U32(fapParameters.lteEnodebIpAddr.enbIpAddr);
                  fapParameters.lteEnodebIpAddr.ipv4pres = TRUE;
                }
                else if (res && res->ai_family == AF_INET6)
                {
                  cmMemcpy((U8*)fapParameters.lteEnodebIpAddr.enbIpv6Addr,(U8*)token->args[1].val, sizeof(CmInetIpAddr6));
                  fapParameters.lteEnodebIpAddr.ipv6pres = TRUE;
                }
                else
                {
                      cmInetFreeAddrInfo(res);/*klockwork fix*/
                      ALARM("Unknown error:[%s]",(S8 *)token->args[1].val);
                      break;
                }

                 /* First release all cals,call full reset, and bring down Tx Power */ 
                 /* get confirmation and then call shutdown */
                 /*execv("./ipchange.sh",((S8*)token->args[1].val));*/
					  smCb.reCfg = TRUE;
                 smBuildShutRestart(); 
             } 
             break;        
/* LTE_ADV starts */
      case  37:  /* lteadv */
         {
            /* Modify LTEA */
            arg2 = osMatchKeyword(wrCliLteaArgKey ,(S8*)token->args[1].val);
            
            switch(arg2)
            {            
               case RGR_ABS:
               case RGR_SFR:
               case RGR_DSFR:
               case RGR_RE: 
               {
                  RgrFeatureStatus status = ((arg1 == WR_ON) ?  RGR_ENABLE : RGR_DISABLE);
                  WrEmmlteAdvFeatureActDeact configInfo = {(RgrFeature)arg2, status};         
                  smSndWrLteAdvancedCellReCfg(&configInfo);
                  sprintf(pBuf, "Application Configuration Initiated **\n");
                  SPrint(pBuf);
                  break;
               }
#ifdef LTE_ADV
               case RGR_SCELLRELEASE:
               case RGR_SCELLADD:
               case RGR_SCELLACT:
               case RGR_SCELLDEACT:
               {   
                  /*USAGE: ltea on scellrel <pcellid> <ueid> <scellid>*/ 
                  /*USAGE: ltea on scelladd <pcellid> <ueid> <scellid>*/ 
                  /*USAGE: ltea on scellact <pcellid> <ueid> <scellid>*/ 
                  /*USAGE: ltea on scelldeact <pcellid> <ueid> <scellid>*/ 
                  wrCliPCellId = (U16)wrISStrtoul((S8*)token->args[2].val);
                  wrCliUeCrnti = (U8)wrISStrtoul((S8*)token->args[3].val);
                  wrCliSCellId = (U16)wrISStrtoul((S8*)token->args[4].val);
                  wrSmmEnbBuildWrScellCntrl(arg2);
               }
               break;
#endif
               default:
               {
                  sprintf(pBuf, "CLI Error: ** Second Option is invalid **\n");
                  SPrint(pBuf);
                  RETVOID;
               }
            }
         }
         break;
/* LTE_ADV ends */

      /* CSG_DEV start */
      case 38: /* csgprntcellinfo */
      {
         if (token->nmbArgs != 2 )
         {
            sprintf(pBuf, " Error : ** Token Missing [Enter Cell ID]**\n");
            SPrint(pBuf);
            break;
         }
         arg2 =  wrISStrtoul((S8*)token->args[1].val);

         wrUmmCsgPrntCellInfo(arg2);
      }
      break;

      case 39: /* csgprntnbrinfo */
      {
         if (token->nmbArgs != 2 )
         {
            sprintf(pBuf, " Error : ** Token Missing [Enter Cell ID]**\n");
            SPrint(pBuf);
            break;
         }
         arg2 =  wrISStrtoul((S8*)token->args[1].val);

         wrUmmCsgPrntNbrCsgInfo(arg2);
      }
      break;
      /* CSG_DEV end */
 

        
     default:
         sprintf(pBuf, " Unknown CLI Command : Type 'help' For Menu  \n");
         SPrint(pBuf);
         break;
   }

   RETVOID;
} /* end of sbIBParseMenu */ 



/*
*
*       Fun:   wrIBLineToTkn
*
*       Desc:  Convert Line format to Token Format
*
*       Ret:   Number of arguments on success
*              RFAILED on error
*
*       Notes:
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PRIVATE S16 wrIBLineToTkn
(
S8           *line,
TstTkn       *token
)
#else
PRIVATE S16 wrIBLineToTkn(line, token)
S8           *line;
TstTkn       *token;
#endif
{
   S8 *lPtr;
   S8 word[20];
   S32 i;

   TRC2(wrIBLineToTkn)

   lPtr = osGetWord(line, word);

   if (osStrlen(word) >= sizeof(token->tok.val)) /* make sure there's room */
      RETVALUE(-1);

   osStrcpy((S8*)token->tok.val, word);

   token->tok.pres = TRUE;
   token->tok.len = osStrlen((S8 *)token->tok.val);
   token->nmbArgs = 0;

   for (i = 0; i < MAXARGS; i++)
   {
      lPtr = osGetWord(lPtr, word);

      if (osStrlen(word) >= sizeof(token->tok.val)) /* make sure there's room */
         RETVALUE(-1);

      if (*word == '\0' || *word == '#') /* end of line or comment */
      {
         token->args[i].pres = FALSE;
         break;
      }

      osStrcpy((S8 *)token->args[i].val, word);
      token->args[i].pres = TRUE;
      token->args[i].len = osStrlen((S8*)token->args[i].val);
      token->nmbArgs++;
   }

   RETVALUE(token->nmbArgs);

} /* end of wrIBLineToTkn */   
#endif /* WR_TEST_CODE */

#ifdef WR_CLI_TARGET_BOARD
/* Function to receive CLI command from CLI client */
/*
 *
 *      Fun:    smCliRecvTsk
 *
 *      Desc:   Receive socket event from CLI client
 *
 *      Ret:    ROK - ok
 *
 *      Notes:  None
 *
        File:
 *
 */

#ifdef ANSI
PRIVATE S16 smCliRecvTsk
(
 Pst    *post,               /* post structure */
 Buffer *mBuf                /* message buffer */
 )
#else
PRIVATE S16 smCliRecvTsk (post, mBuf)
   Pst    *post;               /* post structure */
   Buffer *mBuf;               /* message buffer */
#endif
{
   TRC3(smCliRecvTsk);
   U32 addr_len;
   S16 bytes_read;
   U8 recv_data[50];
   U32 idx = 0;
   struct sockaddr_in6 server_addr6;
   struct sockaddr_in server_addr;
   int domain;
   static S32 sock;
   struct sockaddr *server;


   /* Free mBuf */
   WR_FREEMBUF(mBuf);
   if(smCfgCb.enbIpAddr.type == CM_TPTADDR_IPV4)
   {
      server_addr.sin_family = AF_INET;
      server_addr.sin_port = htons(WR_CLI_READ_PORT_NUM);
      server_addr.sin_addr.s_addr = INADDR_ANY;
      bzero(&(server_addr.sin_zero),8);
      domain = AF_INET;
      server = (struct sockaddr *)&server_addr; 
      addr_len = sizeof(struct sockaddr_in);

   }
   else if(smCfgCb.enbIpAddr.type == CM_TPTADDR_IPV6)
   {
      server_addr6.sin6_family = AF_INET6;
      server_addr6.sin6_port = htons(WR_CLI_READ_PORT_NUM);
      server_addr6.sin6_addr = in6addr_any;
      bzero(&(server_addr6.sin6_zero),8);
      domain = AF_INET6;
      server = (struct sockaddr *)&server_addr6; 
      addr_len = sizeof(struct sockaddr_in6);
   }


   if ((sock = socket(domain, SOCK_DGRAM, 0)) == -1)
   {
      RLOG_STR(L_FATAL, "Socket system call failed for CLI listener :%s",
         strerror(errno));
      exit(1);
   }
   if (bind(sock,server,addr_len) == -1)
   {
      RLOG_STR(L_FATAL, "Bind system call failed for CLI listener :%s",
         strerror(errno));
      exit(1);
   }
   RLOG1(L_INFO, "UDP Server for CLI Commands waiting for client on port %d", WR_CLI_READ_PORT_NUM);

   memset((char*)recv_data, 0, sizeof(recv_data));

   while (1)
   {
      bytes_read = recvfrom(sock,recv_data,50, MSG_WAITALL,
            server, &addr_len);


      if(bytes_read > 0)
      {
         /*ccpu00127802*/
         RLOG1(L_INFO, "Received CLI command=%s,Buf Size=%d", recv_data, strlen(recv_data));
         idx = 0;
         while(1)
         {
           rdConQ(recv_data[idx]);
           if ( recv_data[idx++] == '\0' )
           {
              break;
           }
         }
         memset((char*)recv_data, 0, sizeof(recv_data));
      }
      else
      {
         RLOG_STR(L_DEBUG, "No data received on CLI listener");
      }
  }
}
#endif /* WR_CLI_TARGET_BOARD */

#ifdef WR_TEST_CODE
/*
*
*       Fun:   smWrProcCliMsg
*
*       Desc: Used to parse the command line token
*       received from CLI thread. 
*
*       Ret:   Void
*
*       File:  wr_smm_init.c
*
*/

PUBLIC Void smWrProcCliMsg(Void)
{
   wrIBParseMenu(&tkn);
   RETVOID;
}
#endif

/*
*
*       Fun:   rdConQ
*
*       Desc:  
*
*       Ret:   ROK, RFAILED
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC S16 rdConQ
(
Data data
)
#else
PUBLIC S16 rdConQ(data)
Data data;
#endif
{
   Pst       cliPst;

   TRC2(rdConQ)


   if ((data == 0x03) ||
       (data == 27))
   {
      /*ccpu00127802*/
      RLOG0(L_ERROR, "wrong key hit ");     
   }
   switch (data)
   {
      case 'q' :
      case 'Q' :
         exit(0);
         break;
#ifndef LTE_ENB_PAL
      case 'd':
      case 'D':
#ifdef T2K_MEM_LEAK_DBG
   DumpT2kMemLeakInfoToFile();
#endif
#ifdef SSI_STATIC_MEM_LEAK_DETECTION
   DumpStaticMemLeakFiles();
#endif
        RLOG0(L_ALWAYS, "************* Printing the LOGS on User Request ***************");
        ssMlogPrint();
        ssMemlogWrite(); 
      break;
#endif
#ifdef WR_TEST_CODE
      default :
         if (wrCmdLen >= MAXCMDLEN - 1)
         {
            wrCmdLen = 0;
            fprintf(stderr, "Invalid input : Wrong key hit\n");     
            RETVALUE(ROK);
         }
         
         wrCmdArgs[wrCmdLen++] = data;

         if ((data == '\n') || (data == '\0'))
         {
            wrIBLineToTkn((S8*)wrCmdArgs, &tkn);

            WR_FILL_PST(cliPst, SM_SM_PROC, SM_WR_PROC, ENTSM, ENTWR,0,0, EVTWRCLIRECV, WR_POOL, SM_SELECTOR_LC);

            if(wrSmSelfPstMsg(&cliPst) != ROK)
            {
               RLOG0(L_ERROR, "Failed to do self post");
               RETVALUE(RFAILED);
            }

//            wrIBParseMenu(&tkn);
            wrCmdLen = 0;
            cmMemset((U8 *)wrCmdArgs, 0, MAXCMDLEN);
         }
#else
         /*ccpu00127802*/
         RLOG0(L_INFO, "****************************************************************");
         RLOG0(L_INFO, "CLI is disabled as 'WR_TEST_CODE' compile time flag is not enbaled");
         RLOG0(L_INFO, "****************************************************************");
#endif
        break;
   }
   RETVALUE(ROK);
}

#ifdef LTE_L2_MEAS
void wrSendL2MeasTrigger()
{
   Pst               pst;          /* post structure  */
   LrgSchMeasReqInfo    measInfo;      /* Meas Req Info */
   static int transId;

   if(ROK == wrDamGetActiveUeCnt(0) || (WR_CELL_STATE_UP != wrEmmCb.cellCb[0]->cellState))
   {
      if(ROK == wrDamGetActiveUeCnt(0))	
      {      
         /*ccpu00127802*/
         RLOG0(L_WARNING, "Reporting of L2 Measurements is disabled as there "
            "are no Active UEs in the System");
      }
      /*Send Zero Statistics to PM*/
        glbMacMeasFlag = 0; 
      RETVOID;
   }

   if(glbMacMeasFlag > 0 )
   {
      /*ccpu00127802*/
      RLOG1(L_WARNING, "Already Request in Progress with transId = [%d]", glbMacMeasFlag);
      RETVOID;
   }

   SM_SET_ZERO(&pst, sizeof(Pst));

   /*Fill Pst Structure*/
   pst.selector  = 0; /*Currently hardCoded to 1 to accelerate debugging*/
   pst.srcEnt    = ENTSM; 
   pst.dstEnt    = wrCb.rgrSap[0]->pst.dstEnt;
   pst.dstProcId = wrCb.rgrSap[0]->pst.dstProcId;
   pst.srcProcId = wrCb.rgrSap[0]->pst.srcProcId;
   pst.dstInst = wrCb.rgrSap[0]->pst.dstInst;
   pst.srcInst = wrCb.rgrSap[0]->pst.srcInst;

   pst.event = EVTLRGSCHL2MEASREQ;

   /*Fill response Values.*/
   measInfo.hdr.response.selector = 0;
   measInfo.hdr.response.prior = 0;
   measInfo.hdr.response.route = 0;
   measInfo.hdr.response.mem.region = 0;
   measInfo.hdr.response.mem.pool = 0;  
   measInfo.hdr.transId = transId++;
   glbMacMeasFlag = measInfo.hdr.transId;

   /*ccpu00127802*/
   RLOG1(L_INFO, "Sending Measurement Request with TransId=[%d]", measInfo.hdr.transId);
   /*Fill desired Measurement Info*/
   measInfo.cellId = 1;
   measInfo.measType = LRG_L2MEAS_AVG_PRB_DL
      |LRG_L2MEAS_AVG_PRB_UL
      |LRG_L2MEAS_AVG_PRB_PER_QCI_DL
      |LRG_L2MEAS_AVG_PRB_PER_QCI_UL
      |LRG_L2MEAS_RA_PREAMBLE
      |LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL
      |LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL;


   measInfo.timePrd = 6000;   /*changed 6000 from 3000 mjkim 2012-08-28*/
#if 0
#else
   measInfo.avgPrbQciUl.numQci=1;
   measInfo.avgPrbQciUl.qci[0]=5;
#endif

#if 0        
#else
   measInfo.avgPrbQciDl.numQci=1;
   measInfo.avgPrbQciDl.qci[0]=5;
#endif

#if 0
#else
   measInfo.nmbActvUeQciUl.sampPrd = 255;
   measInfo.nmbActvUeQciUl.numQci = 1;
   measInfo.nmbActvUeQciUl.qci[0] = 5;
#endif

#if 0
#else
   measInfo.nmbActvUeQciDl.sampPrd = 255;
   measInfo.nmbActvUeQciDl.numQci = 1;
   measInfo.nmbActvUeQciDl.qci[0] = 5;
#endif

   SmMiLrgSchL2MeasStartReq(&pst,&measInfo);

   RETVOID;
}  

/*
*
*       Fun:   wrSendL2MeasStartReq 
*
*       Desc:  This function is used to start L2 Meas 
*              at lower layers (PDCP/RLC/MAC) 
*
*       Ret:   S16 ret
*              
*
*       Notes:
*
*       File:  wr_smm_init.c
*
*/
S16 PUBLIC  wrSendL2MeasStartReq(Void)
{
   U16          measType;
   S16         ret = ROK;

   TRC2(wrSendL2MeasStartReq)

   /*bulding and sending L2 Meas req for sending to PDCP layer  */
    measType = LPJ_L2MEAS_UL_LOSS | LPJ_L2CPU_PERCORE_STATS;
             /*  LPJ_L2MEAS_DL_DELAY| 
              LPJ_L2MEAS_DL_DISC |
	           LPJ_L2MEAS_DLDP_BIT_RATE |
              LPJ_L2MEAS_ULDP_BIT_RATE|LPJ_L2MEAS_DLCP_BIT_RATE|
              LPJ_L2MEAS_ULCP_BIT_RATE;*/
   /*building and sending L2 meas Req*/
   smSndPjL2MeasStartReq(measType);

   /*Sending L2 Meas Req to RLC layer*/
   measType =  LKW_L2MEAS_DL_DISC ;
   smSndKwL2MeasStartReq(measType);

   measType =  LKW_L2MEAS_UU_LOSS ; 
   smSndKwL2MeasStartReq(measType);

   measType =  LKW_L2MEAS_DL_DELAY; 
   smSndKwL2MeasStartReq(measType);

   /*filling Meas type*/
   measType = LKW_L2MEAS_DL_IP;
   /*building and sending L2 meas Req for sending to RLC Layer*/
   smSndKwL2MeasStartReq(measType);

    /*filling Meas type*/
   measType = LKW_L2MEAS_UL_IP;
   /*building and sending L2 meas Req for sending to RLC Layer*/
   smSndKwL2MeasStartReq(measType);
  
#if 1
   measType = LRG_L2MEAS_AVG_PRB_PER_QCI_DL|
              LRG_L2MEAS_AVG_PRB_DL|
              LRG_L2MEAS_AVG_PRB_UL|
              LRG_L2MEAS_RA_PREAMBLE |
              LRG_L2MEAS_AVG_PRB_PER_QCI_UL |
              LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL |
              LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL |
              LRG_L2MEAS_TB_TRANS_DL_COUNT |
              LRG_L2MEAS_TB_TRANS_UL_COUNT |
              LRG_L2MEAS_TB_TRANS_DL_FAULTY_COUNT |
              LRG_L2MEAS_TB_TRANS_UL_FAULTY_COUNT;
#else
  measType = LRG_L2MEAS_RA_PREAMBLE;
#endif
   /*buidling and sending L2 meas req for sending to Mac Layer*/
   smSndRgSchL2MeasStartReq(measType);
   
   RETVALUE(ret);
}/*wrSendL2MeasStartReq*/
/*
*
*       Fun:   wrSndL2MeasStopReq 
*
*       Desc:  This function is used to Stop L2 Meas 
*              at lower layers (PDCP/RLC/MAC) 
*
*       Ret:   S16 ret
*              
*
*       Notes:
*
*       File:  wr_smm_init.c
*
*/
S16 PUBLIC  wrSndL2MeasStopReq(Void)
{
  U16 measType;

  TRC2(wrSndL2MeasStopReq)
 
/* Send L2 Meas Stop req to PDCP layer  */
  measType = LPJ_L2MEAS_UL_LOSS | LPJ_L2CPU_PERCORE_STATS;
       /*     LPJ_L2MEAS_DL_DELAY |
              LPJ_L2MEAS_DL_DISC;*/ 
  smSndPjL2MeasStopReq(measType);
  (kpiInfo.numOfL2MeasStopReq)++;

  measType = LKW_L2MEAS_DL_DISC;
  smSndKwL2MeasStopReq(measType);
  (kpiInfo.numOfL2MeasStopReq)++;

  measType = LKW_L2MEAS_UU_LOSS;
  smSndKwL2MeasStopReq(measType);
  (kpiInfo.numOfL2MeasStopReq)++;

  measType = LKW_L2MEAS_DL_IP;
  smSndKwL2MeasStopReq(measType);
  (kpiInfo.numOfL2MeasStopReq)++;

  measType = LKW_L2MEAS_UL_IP;
  smSndKwL2MeasStopReq(measType);
  (kpiInfo.numOfL2MeasStopReq)++; 

  measType = LKW_L2MEAS_DL_DELAY ;
  smSndKwL2MeasStopReq(measType);
  (kpiInfo.numOfL2MeasStopReq)++;

#if 1
  measType = LRG_L2MEAS_AVG_PRB_PER_QCI_DL|
             LRG_L2MEAS_AVG_PRB_DL|
             LRG_L2MEAS_AVG_PRB_UL|
             LRG_L2MEAS_RA_PREAMBLE|
        LRG_L2MEAS_AVG_PRB_PER_QCI_UL |
             LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL |
             LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL|
             LRG_L2MEAS_TB_TRANS_DL_COUNT |
             LRG_L2MEAS_TB_TRANS_UL_COUNT |
             LRG_L2MEAS_TB_TRANS_DL_FAULTY_COUNT |
             LRG_L2MEAS_TB_TRANS_UL_FAULTY_COUNT;
#else
  measType = LRG_L2MEAS_RA_PREAMBLE;
#endif
  smSndRgSchL2MeasStopReq(measType);
  (kpiInfo.numOfL2MeasStopReq)++;

  RETVALUE(ROK);
}/*wrSndL2MeasStopReq*/
/*
*
*       Fun:   wrSndL2MeasSendReq
*
*       Desc:  This function is used to request L2 Meas
*              to lower layers (PDCP/RLC/MAC)
*
*       Ret:   S16 ret
*
*
*       Notes:
*
*       File:  wr_smm_init.c
*
*/
S16 PUBLIC  wrSndL2MeasSendReq(Void)
{
  U16 measType;

  TRC2(wrSndL2MeasSendReq)

/* This part sends L2 meas req to PDCP lyaer */
  measType = LPJ_L2MEAS_UL_LOSS | LPJ_L2CPU_PERCORE_STATS;
           /* LPJ_L2MEAS_DL_DELAY | 
             LPJ_L2MEAS_UL_LOSS; */
  smSndPjL2MeasSendReq(measType);

  measType = LKW_L2MEAS_DL_DISC;
            /*LKW_L2MEAS_UU_LOSS;*/
  smSndKwL2MeasSendReq(measType);

  measType = LKW_L2MEAS_UU_LOSS;
  smSndKwL2MeasSendReq(measType);

  measType = LKW_L2MEAS_DL_IP;
  smSndKwL2MeasSendReq(measType);

  measType = LKW_L2MEAS_UL_IP;
  smSndKwL2MeasSendReq(measType);

  measType = LKW_L2MEAS_DL_DELAY ;
  smSndKwL2MeasSendReq(measType);

#if 1
  measType = LRG_L2MEAS_AVG_PRB_PER_QCI_DL|
             LRG_L2MEAS_AVG_PRB_DL|
             LRG_L2MEAS_AVG_PRB_UL|
             LRG_L2MEAS_RA_PREAMBLE|
             LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_DL |
             LRG_L2MEAS_NMB_ACTV_UE_PER_QCI_UL |
             LRG_L2MEAS_AVG_PRB_PER_QCI_UL|
             LRG_L2MEAS_TB_TRANS_DL_COUNT |
             LRG_L2MEAS_TB_TRANS_UL_COUNT |
             LRG_L2MEAS_TB_TRANS_DL_FAULTY_COUNT |
             LRG_L2MEAS_TB_TRANS_UL_FAULTY_COUNT;
#else
  measType = LRG_L2MEAS_RA_PREAMBLE; 
#endif
  smSndRgSchL2MeasSendReq(measType);

   RETVALUE(ROK);
}/*wrSndL2MeasSendReq*/
 

/*     
*     Fun:   wrMemCpuUtilMeasStartReq
*
*     This function is used to start memory and CPU utilization 
*              measurement information 
*
*       Ret:   S16 ret
*              
*
*       Notes:
*
*       File:  wr_smm_init_merged.c
*
*/
S16 PUBLIC  wrMemCpuUtilMeasStartReq(Void)
{
   S16         ret = ROK;

   TRC2(wrCpuUtilMeasStartReq)

   /* Enable the measurement mask for the CPU and MEMORY utilization */
   smCb.memCpuMeasCb.memUtilizationMask = TRUE;
   smCb.memCpuMeasCb.cpuUtilizationMask = TRUE;
   cmInitTimers(&(smCb.memCpuMeasCb.cpuMemUtilTmr), 1);

   ret = wrStartTmr((PTR)NULLP,WR_TMR_MEM_CPU_UTIL_INFO,CM_MEM_CPU_UITL_INFO_TMR_VAL);

   RETVALUE(ret);
}/*wrSendL2MeasStartReq*/


/*
 *
*       Fun:   wrMemCpuL3MeasStopReq 
*
*       Desc:  This function is used to stop memory and CPU utilization 
*              measurement information 
*
*       Ret:   S16 ret
*              
*
*       Notes:
*
*       File:  wr_smm_init.c
*
*/
S16 PUBLIC  wrMemCpuL3MeasStopReq(Void)
{
   S16 ret = ROK;
   TRC2(wrMemCpuL3MeasStopReq)

   /* Disable the measurement mask for the CPU and MEMORY utilization */
   wrStopTmr((PTR)NULLP,WR_TMR_MEM_CPU_UTIL_INFO);
   /* Enable the measurement mask for the CPU and MEMORY utilization */
   smCb.memCpuMeasCb.memUtilizationMask = FALSE;
   smCb.memCpuMeasCb.cpuUtilizationMask = FALSE;
   cmClearMemUtilizationCounter(&smCb.memCpuMeasCb.memInfo);
   cmClearCpuUtilizationCounter(&smCb.memCpuMeasCb.cpuInfo);
   RETVALUE(ret);
}/*wrSndL2MeasStopReq*/

/*
*
*       Fun:   smSendKpiMemCpuInfo
*
*       Desc:  This function is used to send cpu and memory  
*              KPI information to OAM
*
*       Ret:   S16 ret
*
*
*       Notes:
*
*       File:  wr_smm_init.c
*
*/
PUBLIC Void smSendKpiMemCpuInfo(Void)
{
   U32  kpiId = INVALID_KPI;
   CmLteMemInfo *mInfo;
   U16 ssiMemIdx = 0;
   U16 sharedMemIdx = 0;
#ifdef WR_RSYS_OAM
   U16 kpiIdAvgCpu = KPI_ID_LTE_L3CPUSTATS_CORE0_AVG;
   U16 kpiIdMaxCpu = KPI_ID_LTE_L3CPUSTATS_CORE0_MAX;
#endif
   U8 idxCore = 0;

   if(smCb.memCpuMeasCb.memUtilizationMask == TRUE)
   {
      U8   idxReg;
      U8   idxPool;
      U8   numReg;
      mInfo = &(smCb.memCpuMeasCb.memCfmInfo);
      numReg = mInfo->numRegions;
      RLOG1(L_DEBUG, "Number of Regions in CPUH :%d", numReg); 
      for(idxReg=0; idxReg< numReg; idxReg++)
      {
         ssiMemIdx    = 0;
         sharedMemIdx = 0;

         if(mInfo->regInfo[idxReg].regionType == 0)
         {
            if (idxReg == 0)
               kpiId = KPI_ID_LTE_MEMINFO_CPUH_SSI_REG0_POOL0_SIZE;
            else if (idxReg == 1)
               kpiId = KPI_ID_LTE_MEMINFO_CPUH_SSI_REG1_POOL0_SIZE;
            else if (idxReg == 2)
               kpiId = KPI_ID_LTE_MEMINFO_CPUH_SSI_REG2_POOL0_SIZE;
            else if (idxReg == 3)
               kpiId = KPI_ID_LTE_MEMINFO_CPUH_SSI_REG3_POOL0_SIZE;
            for(idxPool=0; idxPool<mInfo->regInfo[idxReg].numPools; idxPool++)
            {
               WR_INC_KPI((kpiId + ssiMemIdx++),KPI_VALUE_TYPE_INTEGER,
                     mInfo->regInfo[idxReg].poolInfo[idxPool].poolSize);
               WR_INC_KPI((kpiId + ssiMemIdx++),KPI_VALUE_TYPE_INTEGER,
                     mInfo->regInfo[idxReg].poolInfo[idxPool].totAvailable);
               WR_INC_KPI((kpiId + ssiMemIdx++),KPI_VALUE_TYPE_INTEGER,
                     mInfo->regInfo[idxReg].poolInfo[idxPool].crntUsed);
               WR_INC_KPI((kpiId + ssiMemIdx++),KPI_VALUE_TYPE_INTEGER,
                     mInfo->regInfo[idxReg].poolInfo[idxPool].maxUsed);

            }
         }
         else if(mInfo->regInfo[idxReg].regionType == 1)
         {
            kpiId = KPI_ID_LTE_MEMINFO_CPUH_SHARED_REG_POOL0_SIZE;
            for(idxPool=0; idxPool<mInfo->regInfo[idxReg].numPools; idxPool++)
            {
               WR_INC_KPI((kpiId + sharedMemIdx++),KPI_VALUE_TYPE_INTEGER,
                     mInfo->regInfo[idxReg].poolInfo[idxPool].poolSize);
               WR_INC_KPI((kpiId + sharedMemIdx++),KPI_VALUE_TYPE_INTEGER,
                     mInfo->regInfo[idxReg].poolInfo[idxPool].totAvailable);
               WR_INC_KPI((kpiId + sharedMemIdx++),KPI_VALUE_TYPE_INTEGER,
                     mInfo->regInfo[idxReg].poolInfo[idxPool].crntUsed);
               WR_INC_KPI((kpiId + sharedMemIdx++),KPI_VALUE_TYPE_INTEGER,
                     mInfo->regInfo[idxReg].poolInfo[idxPool].maxUsed);

               }
            }
         }
   }
   if(smCb.memCpuMeasCb.cpuUtilizationMask == TRUE)
   {
      for(idxCore=0; idxCore < smCb.memCpuMeasCb.cpuCfmInfo.numCores; idxCore++)
      {
            WR_INC_KPI((kpiIdAvgCpu + idxCore),KPI_VALUE_TYPE_INTEGER,
                  smCb.memCpuMeasCb.cpuCfmInfo.cpuUtil[idxCore].avgCpuUtil);
            WR_INC_KPI((kpiIdMaxCpu + idxCore),KPI_VALUE_TYPE_INTEGER,
                  smCb.memCpuMeasCb.cpuCfmInfo.cpuUtil[idxCore].maxCpuUtil);

      }
   }

   /*Increments number of confirm recevied from PDCP layer*/
   
   RLOG0(L_DEBUG,"Received Confirmation for L2 Measurement config");
   //if(kpiInfo.numOfTrggrL2MeasReq == kpiInfo.numOfRcvdL2MeasCfm)
   if( kpiInfo.measConfigRecv == WR_MEAS_CFG_DONE )
   {
      #ifdef WR_RSYS_OAM
         KpisInfoSentNotification();
      #endif
   }

}



/*
*
*       Fun:   wrMemCpuL3MeasSendReq
*
*       Desc:  This function is used to stop memory and CPU utilization 
*              measurement information 
*
*       Ret:   S16 ret
*
*
*       Notes:
*
*       File:  wr_smm_init.c
*
*/
S16 PUBLIC  wrMemCpuL3MeasSendReq(Void)
{
   S16 ret = ROK;

   TRC2(wrMemCpuUtilMeasSendReq)

   wrStopTmr((PTR)NULLP,WR_TMR_MEM_CPU_UTIL_INFO);
   if(ret == ROK)
   {
      if(smCb.memCpuMeasCb.cpuUtilizationMask == TRUE)
      {
         cmFillCpuUtilizationMeas(&(smCb.memCpuMeasCb.cpuCfmInfo),
                             &(smCb.memCpuMeasCb.cpuInfo));
      }
      
      if(smCb.memCpuMeasCb.memUtilizationMask == TRUE)
      {
         /* Update Memory Info */
         cmFillMemUtilizationMeas(&(smCb.memCpuMeasCb.memCfmInfo),
                                &(smCb.memCpuMeasCb.memInfo));
      }
      smSendKpiMemCpuInfo();
      cmClearMemUtilizationCounter(&smCb.memCpuMeasCb.memInfo);
      cmClearCpuUtilizationCounter(&smCb.memCpuMeasCb.cpuInfo);
   }

   ret = wrStartTmr((PTR)NULLP,WR_TMR_MEM_CPU_UTIL_INFO,CM_MEM_CPU_UITL_INFO_TMR_VAL);

   RETVALUE(ret);
}/*wrSndL2MeasSendReq*/

/*
*
*       Fun:   wrMemCpuUtilTmrExp
*
*       Desc:  This function is used to call SOC specific API to get  
*              CPU and Memory information 
*
*       Ret:   S16 ret
*
*
*       Notes:
*
*       File:  wr_smm_init.c
*
*/
Void PUBLIC  wrMemCpuUtilTmrExp(Void)
{
   if(smCb.memCpuMeasCb.memUtilizationMask == TRUE)
   {
      cmUpdateSsiMemInfo(&(smCb.memCpuMeasCb.memInfo));
      UpdateSocMemInfo(CM_L3_MEM_UTIL_AREAIDX, &(smCb.memCpuMeasCb.memInfo));
   }
   if(smCb.memCpuMeasCb.cpuUtilizationMask == TRUE)
   {
      UpdateSocCpuInfo(&(smCb.memCpuMeasCb.cpuInfo),CM_L3_CPU_UTIL);
   }

   wrStartTmr((PTR)NULLP,WR_TMR_MEM_CPU_UTIL_INFO,CM_MEM_CPU_UITL_INFO_TMR_VAL);
}
#endif/*LTE_L2_MEAS*/ 

#ifdef WR_RSYS_OAM
/*
*
*       Fun:  SCreateSmmAppTst
*
*       Desc: Create SmmApp Thread 
*
*       Ret:   ROK, RFAILED
*
*       File:  wr_enb_init.c
*
*/

#ifdef ANSI
PRIVATE void SCreateSmmAppTst()
#else
PRIVATE void SCreateSmmAppTst()
#endif
{
   RLOG0(L_INFO, "*********\nIn SCreateSmmAppTst\n**********");
   printf("In SCreateSmmAppTst\n");

  U32 threadCreated = FALSE;
  U32 cnt = 0;

  pthread_t      tskId_smmApp;
  pthread_attr_t attr;
  struct sched_param tskId_smmApp_param;
  tskId_smmApp_param.sched_priority = sched_get_priority_min(SCHED_RR);

   /* initialize the started semaphore */
   if (sem_init(&smOamStartSema, 0, 0) != 0)
   {
      RLOG0(L_FATAL, "SCreateSmmAppTst() : Initialisation of smOamStartSema failed");
      RETVOID;
   }

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

   /* When the thread is created, we check for the memory mapping table if
    * threadId can be placed in thread memory map table. If it is not able to place
    * threadId is stored in tmporary array. Once thread is created successful,
    * thread_cancel is sent for each thread which are created before. All the 
    * threads are made to wait on sema which is cancel point for thread.
    */
   while(threadCreated == FALSE)
   {
      cnt++;
      if ((pthread_create(&tskId_smmApp, &attr, wrSmmAppTstCaller, NULLP)) != 0)
      {
         RLOG0(L_FATAL, "SCreateSmmAppTst() : pthread_create failed");
         pthread_attr_destroy(&attr);
         RETVOID;
      }

      threadCreated = ssCheckAndAddMemoryRegionMap(tskId_smmApp,(SS_MAX_REGS-1));
   }
  pthread_setschedparam(tskId_smmApp, SCHED_RR, &tskId_smmApp_param);
  sem_post (&smOamStartSema);

}/*End SCreateSmmAppTst*/

/*
*
*       Fun:  wrSmmAppTstCaller
*
*       Desc: Create SmmApp Thread 
*
*       Ret:   ROK, RFAILED
*
*       File:  wr_enb_init.c
*
*/

#ifdef ANSI
PRIVATE void *wrSmmAppTstCaller
(
Void *arg
)
#else
PRIVATE void *wrSmmAppTstCaller(arg)
Void *arg;
#endif

{
   S16 ret;
   RLOG0(L_DEBUG, "wrSmmAppTstCaller() ");
   printf("In wrSmmAppTstCaller()\n");
   while ((ret = sem_wait(&smOamStartSema) != ROK) && (errno == EINTR))
   {
      RLOG0(L_FATAL, "wrSmmAppTstCaller() : sem_wait failed");
      printf("wrSmmAppTstCaller() sem_wait failed\n");
      continue;
   }
   SmAppTst();
   RETVALUE((Void *)NULLP);
}/*End wrSmmAppTstCaller*/
#endif
#ifdef E_TM
/*
*
*       Fun:   smWrEtmProcSm
*
*       Desc:  This function is entry function to the  main State Machine for ETM
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void smWrEtmProcSm
(
U8 event
)
#else
PUBLIC Void smWrEtmProcSm(event)
U8  event;
#endif /* ANSI */
{
   TRC2(smWrEtmProcSm);

   switch (smCb.smState)
   {
      case WR_SM_STATE_CL_INIT:
         {
            wrSmHdlCLCfgEvent(event);
            break;
         }
      case WR_SM_STATE_CL_CFG_DONE:
         {
            wrSmHdlCellCfgEvent(event);
            break;
         }
      default:
         {
            RLOG1(L_ERROR, "Invalid state [%d] received",smCb.smState);
            break;
         }
   }
} /* smWrEtmProcSm */   
/*
*
*       Fun:   wrSmHdlCellCfgEvent
*
*       Desc:  This function is handles events in MAC Config done state
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

#ifdef ANSI
PUBLIC Void wrSmHdlCellCfgEvent
(
U8 event
)
#else
PUBLIC Void wrSmHdlCellCfgEvent(event)
U8  event;
#endif /* ANSI */
{
   TRC2(wrSmHdlCellCfgEvent);

   if(event == EVTWRCELLCFG )
   {
      /* Start LTE Convergence Layer Configuration */
      wrSmYsCellCfg();
   }
   else
   {
      RLOG_STR(L_ERROR,"Expected event EVTWRCELLCFG. Received event %s ",
         wrSmmPrintSmmEvent(event));
   } /* end of else part */

   RETVOID;
} /* end of wrSmHdlCellCfgEvent */

#endif

PUBLIC Void smBuildShutRestart()

{
   TRC2(smBuildShutRestart);
   smCb.smState = WR_SM_STATE_REBOOT_REQUIRED;
   /* Stop the RLOG restriction for limiting the number of LOgs per 10ms
    * All logs here onwards will be logged
    */
   rlStopLogCountLimit();
   smBuildFullRstctrl();
   RLOG0(L_INFO, "Message to initiate shutdown");
   RETVOID;
}   



/*
*
*       Fun:   smBuildFullRstctrl
*
*       Desc:  This function Builds and send control request for full reset
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/

PRIVATE Void smBuildFullRstctrl(Void)
{
   LwrMngmt *cntrl = NULLP;
   Pst      pst;

    TRC2(smBuildFullRstctrl);
   /* wr002.102: Corrected function name in trace macro */

   WR_ALLOC(&cntrl, sizeof(LwrMngmt));

   if(cntrl == NULLP)
   {
      printf("Calling smBuildFullRstctrl 2\n");
      RETVOID;
   }

   SM_SET_ZERO(cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));

  /* cntrl.t.cntrl.u.sapId       =  0; */ /* Needed ? */

   /* Fill Header */
   cntrl->hdr.msgType             = TCNTRL;
   cntrl->hdr.entId.ent           = ENTWR;
   cntrl->hdr.entId.inst          = SM_INST_ZERO;
   cntrl->hdr.elmId.elmnt         = STWRMMERSETCTRL;
   cntrl->hdr.response.selector   = SM_SELECTOR_LWLC;

   cntrl->t.cntrl.u.oper = smCfgCb.mmeCfg[0]->mmeId;   /*MMEID for which reset is to be done*/
                              /* Currently supporting one */
   /* Fill Pst */
   pst.selector  = SM_SELECTOR_LWLC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.event     = EVTLWRCNTRLREQ;
     RLOG0(L_DEBUG, "APP Shutdown Cntrl Req to wr sent");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, cntrl);
   RETVOID;
   
} 

#ifdef LTE_PAL_ENB
/*
*
*       Fun:   Initialize CL task.
*
*       Desc:  Invoked to create LTE CL TAPA task.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  ve_se_tst.c
*
*/
#ifdef ANSI
PUBLIC S16 smYsInit
(
SSTskId    sysTskId
)
#else
PUBLIC S16 smYsInit(sysTskId)
SSTskId    sysTskId;
#endif
{

   TRC2(smYsInit); 

   /* Register CL TAPA Task */
   if (SRegTTsk((Ent)ENTYS, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR0,
            ysActvInit, (ActvTsk)ysActvTsk) != ROK) 
   {
      RLOG0(L_FATAL, "Failed to Register CL Tapa Task");
      RETVALUE(RFAILED);
   } /* end of if statement */

#ifndef CNE_UE_SIM_TEST
   if (SRegTTsk((Ent)ENTTF, (Inst)0, (Ttype)TTNORM, (Prior)PRIOR0,
            NULLP, (ActvTsk)ysActvTsk) != ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

   /* Attach PHY STUB TAPA Task */
   if (SAttachTTsk((Ent)ENTTF, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */
#endif

   /* Attach CL TAPA Task */
   if (SAttachTTsk((Ent)ENTYS, (Inst)0, sysTskId)!= ROK) 
   {
      RETVALUE(RFAILED);
   } /* end of if statement */

   RLOG1(L_INFO, "CL Tapa Task successfully registered and attached to %d",sysTskId);

   RETVALUE(ROK);
} /* end of smYsInit */

#endif


#ifdef TIP_UPPER_L2
/*
*
*       Fun:   tst
*
*       Desc:  tst entry point. First entry point.
*
*       Ret:   ROK on success, RFAILED on error
*
*       Notes: None
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC S16 tst
(
Void
)
#else
PUBLIC S16 tst(Void)
#endif
{
   struct     sockaddr_in tipSrcAddr;      /* Global Internet address/port */
   S32        tipSockfd;
   U32        ipAddr;
   U16        port;
 
	SSTskId egtp_dat_app_taskId;
	 U16        smEvent;
	/* System tasks that are needed as per the architecture */
	/* wr002.102: Added trace macro */
	TRC2(tst)

   /**print the software version for LL2**/
   printf("\nUL2 SOFTWARE VERSION : %s\n", wrGetSwVersion_UL2());

#ifndef LTE_ENB_PAL
	ysPhyCommInit();
	ssMlogInit();
	ssMemlogInit();
#endif

	/* To Initialize SmCfg Cb params with default values */
	wrSmmInitSmCfgCb();/* To intialize wrNghCellCfg and SCTP Params */
	/* Read the parameters from the file and copy into global control block */
	if(smWrReadConfigParams() != ROK)
	{
		fprintf(stderr, "Failed to read from file wr_cfg.txt");
		RETVALUE(RFAILED);
	} /* end of if statement */

   proc_Id = WR_UL2_OFFSET + (UL2_IP_ADDR & 0x0000ffff); //UL2_PORT_TIP;
   SSetProcId(SM_PJ_PROC);

   if((S32)(tipSockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
   {
      perror("Server-socket() tipSockfd error lol!");
      exit(1);
   }
   
   printf("Tip Socket Creation entered\n");
   Ul2TipSockFd = tipSockfd;
   ipAddr = htonl(UL2_IP_ADDR);
   port   = UL2_PORT_TIP;

   cmMemset((U8*)&tipSrcAddr, 0, sizeof(tipSrcAddr));
   tipSrcAddr.sin_family      = AF_INET;
   tipSrcAddr.sin_port        = htons(port);
   tipSrcAddr.sin_addr.s_addr = ipAddr;

   if(bind(tipSockfd, (struct sockaddr *)&tipSrcAddr, 
                              sizeof(struct sockaddr)) == -1)
   {
      perror("Server-bind() error:");
      exit(1);
   }

   InitUL2TipSockTsk();
   InitUL2DrvrTsk();

//	InitDrvrTsk();

	rlSetLogPath("./");
	rlSetLogFile("upperL2");
	rlSetNumOfLogFiles(5);
	rlSetLogFileSizeLimit(5);
	rlSetLogLevel(6);
	rlSetLogPort(9999);
	rlSetRemoteLoggingFlag(0);
	rlSetCircularBufferSize(100);
	rlEnableDisableCore(1);
	rlSetModuleMask(0);
	rlInitLog(CM_TPTADDR_IPV4);

	SCreateSTsk(32, &egtp_dat_app_taskId);

	/* Create PDCP tasks and attach them 
	   to a single system thread */
	if(smPjUlInit(egtp_dat_app_taskId) != ROK)
	{
		RLOG0(L_FATAL, "PDCP UL Tapa Task initialization failed");
		RETVALUE(RFAILED);
	} /* end of if statement */
	/* Create RLC/PDCP tasks and attach them 
	   to a single system thread */
	if(smPjDlInit(egtp_dat_app_taskId) != ROK)
	{
		RLOG0(L_FATAL, "PDCP DL Tapa Task initialization failed");
		RETVALUE(RFAILED);
	} /* end of if statement */

	/* Create EGTP and EGTP APP TAPA tasks and attach them 
	   to a single system thread */
	if(smEgInit(egtp_dat_app_taskId) != ROK)
	{
		RLOG0(L_FATAL, "EGTP Tapa Task initialization failed");
		RETVALUE(RFAILED);
	} /* end of if statement */
#ifdef EU_DAT_APP 
	if(smEuInit(egtp_dat_app_taskId) != ROK)
	{
		RLOG0(L_FATAL, "EGTP Data APP Tapa Task initialization failed");
		RETVALUE(RFAILED);
	} /* end of if statement */
#endif /* EU_DAT_APP */

         /* Create the SM TAPA task */
        SRegTTsk(ENTSM, (Inst) 0, TTNORM, PRIOR0, (PAIFS16)smActvInit, smActvTsk);
        SAttachTTsk(ENTSM, (Inst) 0, egtp_dat_app_taskId);

   smCb.smState = WR_SM_STATE_INIT;
	smEvent = EVTWREGTPCFG;
	smWrProcSm(smEvent);
	RETVALUE(ROK);

} /* end of tst function */

/*
*
*       Fun:   smWrProcSm
*
*       Desc:  This function is entry function to the  main State Machine
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void smWrProcSm
(
U8 event
)
#else
PUBLIC Void smWrProcSm( event)
U8  event;
#endif /* ANSI */
{
   U8 idx; 
   TRC2(smWrProcSm);

 
   switch (smCb.smState)
   {
      case WR_SM_STATE_INIT:
         {
            for(idx = 0; idx < WR_MAX_CELLS; idx++)
            {   
               smInitMsm(idx); 
            }
            RLOG0(L_DEBUG,"Configuring EGTP");
            wrSmHdlEgtpCfgEvent(event);
            break;
         }
      case WR_SM_STATE_EGTP_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring PDCP UL");
            wrSmHdlPdcpUlCfgEvent(event);
            break;
         }
      case WR_SM_STATE_PDCP_UL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring PDCP DL");
            wrSmHdlPdcpDlCfgEvent(event);
            break;
         }
      case WR_SM_STATE_PDCP_DL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring DAM");
            wrSmHdlDamCfgEvent(event);
            break;
         }
      case WR_SM_STATE_APP_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Binding PDCP stack");
            wrSmHdlBndPdcpStack(event);
            break;
         }
      case WR_SM_STATE_RRC_STK_BND_DONE:
         {
            RLOG0(L_DEBUG,"Binding EGTP stack");
            wrSmHdlBndEgtpStack(event);
            break;
         }
      case WR_SM_STATE_X2AP_STK_BND_DONE:
         {
            RLOG0(L_DEBUG,"Binding DAM stack");
            wrSmHdlBndDamStack(event);
            tipBldSendInitInd(PDCP_MOD_ID, PDCP_INIT_IND); 
            break;
         }
      default:
         {
            RLOG1(L_ERROR, "smWrProcSm() Invalid  state [%d] received",
                  smCb.smState);
            break;
         }
   }
   RETVOID;
} /* smWrProcSm */
#endif

#ifdef TIP_LOWER_L2
/*
*
*       Fun:   tst
*
*       Desc:  tst entry point. First entry point.
*
*       Ret:   ROK on success, RFAILED on error
*
*       Notes: None
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC S16 tst
(
Void
)
#else
PUBLIC S16 tst(Void)
#endif
{
   struct     sockaddr_in tipSrcAddr;      /* Global Internet address/port */
   S32        tipSockfd;
   U32        ipAddr;
   U16        port;
 
	/* System tasks that are needed as per the architecture */
	pthread_attr_t attr;
	SSTskId rlc_mac_cl_taskId;
	SSTskId rlc_ul_taskId;
        U16 smEvent;
	/* wr002.102: Added trace macro */
	TRC2(tst)

   /**print the software version for LL2**/
   printf("\nLL2 SOFTWARE VERSION : %s\n", wrGetSwVersion_LL2());

	/* To Initialize SmCfg Cb params with default values */
	wrSmmInitSmCfgCb();/* To intialize wrNghCellCfg and SCTP Params */
	/* Read the parameters from the file and copy into global control block */
	if(smWrReadConfigParams() != ROK)
	{
		fprintf(stderr, "Failed to read from file wr_cfg.txt");
		RETVALUE(RFAILED);
	} /* end of if statement */
 
#ifdef SRS_PHY
   start_dl();
#endif
   proc_Id = WR_LL2_OFFSET + (LL2_IP_ADDR & 0x0000ffff); //LL2_PORT_TIP;
   SSetProcId(SM_RG_PROC);

   if((S32)(tipSockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
   {
      perror("Server-socket() tipSockfd error lol!");
      exit(1);
   }
   
   printf("Tip Socket Creation entered\n");
  Ll2TipSockFd = tipSockfd;
  ipAddr = htonl(LL2_IP_ADDR);
  port = LL2_PORT_TIP;

   cmMemset((U8*)&tipSrcAddr, 0, sizeof(tipSrcAddr));
   tipSrcAddr.sin_family      = AF_INET;
   tipSrcAddr.sin_port        = htons(port);
   tipSrcAddr.sin_addr.s_addr = ipAddr;

   if(bind(tipSockfd, (struct sockaddr *)&tipSrcAddr, 
                              sizeof(struct sockaddr)) == -1)
   {
      perror("Server-bind() error:");
      exit(1);
   }

   InitLL2TipSockTsk();

//	InitDrvrTsk();

	rlSetLogPath("./");
	rlSetLogFile("lowerL2");
	rlSetNumOfLogFiles(5);
	rlSetLogFileSizeLimit(5);
	rlSetLogLevel(6);
	rlSetLogPort(9999);
	rlSetRemoteLoggingFlag(0);
	rlSetCircularBufferSize(100);
	rlEnableDisableCore(1);
	rlSetModuleMask(0);
	rlInitLog(CM_TPTADDR_IPV4);

#ifndef LTE_ENB_PAL
	ysPhyCommInit();
	ssMlogInit();
	ssMemlogInit();
#endif

#ifndef LTE_ENB_PAL
#ifdef SS_MULTICORE_SUPPORT
	{
		/* Two cores, each having one hardware thread */
		SCpuInfo cpuInfo = { 2, 1, {1, 1}};
		SRegCpuInfo(&cpuInfo);
	}
#endif /* SS_MULTICORE_SUPPORT */
#endif

	/*  All the System tasks(threads)  are created with same priority*/
	/* Needs discussion with Team : In order to reduce the number of 
	   threads in our system, we are tieing all L3, Iu, CN side to same
	   thread(system task). Essentially this will reduce number of 
	   threads but impacts parallelism, since application threads involves
	   IO operations. */

	SCreateSTsk(PRIOR0, &rlc_mac_cl_taskId);  
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

#ifndef LTE_PAL_ENB
#ifdef SS_MULTICORE_SUPPORT
	SSetAffinity(&rlc_mac_cl_taskId, SS_AFFINITY_MODE_SPECIFIC, 0, NULLP);
#endif /* SS_MULTICORE_SUPPORT */
#endif


	SCreateSTsk(32, &rlc_ul_taskId);
#ifndef LTE_PAL_ENB
	SSetAffinity(&rlc_ul_taskId, SS_AFFINITY_MODE_SPECIFIC, 1, NULLP);
#ifdef SPLIT_RLC_DL_TASK
	SCreateSTsk(1, &rlc_dl_taskId);
	SSetAffinity(&rlc_dl_taskId, SS_AFFINITY_MODE_SPECIFIC, 1, NULLP);
#endif 
#endif 
	/* Create RLC/PDCP tasks and attach them 
	   to a single system thread */
	if(smKwUlInit(rlc_ul_taskId) != ROK)
	{
		RLOG0(L_FATAL, "RLC UL Tapa Task initialization failed");
		RETVALUE(RFAILED);
	} /* end of if statement */

	/* Create RLC/PDCP tasks and attach them 
	   to a single system thread */
#ifdef SPLIT_RLC_DL_TASK
	if(smKwDlInit(rlc_dl_taskId) != ROK)
#else 
		if(smKwDlInit(rlc_mac_cl_taskId) != ROK)
#endif 
		{
			RLOG0(L_FATAL, "RLC DL Tapa Task initialization failed");
         pthread_attr_destroy(&attr);
			RETVALUE(RFAILED);
		} /* end of if statement */

	/* Create LTE MAC tapa task and attach it
	   to a single system thread */
	if(smRgInit(rlc_mac_cl_taskId) != ROK )
	{
		RLOG0(L_FATAL, "LTE MAC Tapa Task initialization failed");
      pthread_attr_destroy(&attr);
		RETVALUE(RFAILED);
	} /* end of if statement */


	/* Create Convergence layer TAPA tasks and attach them 
	   to a single system thread */
	if(smYsInit(rlc_mac_cl_taskId) != ROK)
	{
		RLOG0(L_FATAL, "CL Tapa Task initialization failed");
      pthread_attr_destroy(&attr);
		RETVALUE(RFAILED);
	} /* end of if statement */

   /* Create the SM TAPA task */
   SRegTTsk(ENTSM, (Inst) 0, TTNORM, PRIOR0, (PAIFS16)smActvInit, smActvTsk);
   SAttachTTsk(ENTSM, (Inst) 0, rlc_mac_cl_taskId);

	smCb.smState = WR_SM_STATE_INIT;
	smEvent = EVTWRRLCCFG;
	smWrProcSm(smEvent);
   pthread_attr_destroy(&attr);
	RETVALUE(ROK);

} /* end of tst function */

/*
*
*       Fun:   smWrProcSm
*
*       Desc:  This function is entry function to the  main State Machine
*
*       Ret:   None
*
*       Notes: <NONE>
*
*       File:  wr_smm_init.c
*
*/
#ifdef ANSI
PUBLIC Void smWrProcSm
(
U8 event
)
#else
PUBLIC Void smWrProcSm( event)
U8  event;
#endif /* ANSI */
{
   U8      idx;
   TRC2(smWrProcSm);

 
   switch (smCb.smState)
   {
      case WR_SM_STATE_INIT:
         {
            for(idx = 0; idx < WR_MAX_CELLS; idx++)
            {   
               smInitMsm(idx); 
            }
            RLOG0(L_DEBUG,"Configuring RLC UL");
            wrSmHdlRlcUlCfgEvent(event);
            break;
         }
      case WR_SM_STATE_RLC_UL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring RLC DL");
            wrSmHdlRlcDlCfgEvent(event);
            break;
         }
      case WR_SM_STATE_RLC_DL_CFG_DONE:
         {
            RLOG0(L_DEBUG,"Configuring MAC");
            wrSmHdlMacCfgEvent(event);
            break;
         }
      case WR_SM_STATE_MAC_CFG_DONE:
         {
            /* Schd Cfg, event is EVTWRMACSCHDCFG */
            wrSmHdlMacCfgEvent(event);
            break;
         }
      case WR_SM_STATE_MAC_SCHD_CFG_DONE:
         {
#ifndef LTE_ENB_PAL
            RLOG0(L_DEBUG,"Configuring CL");
            wrSmHdlCLCfgEvent(event);
            break;
         }
      case WR_SM_STATE_CL_CFG_DONE:
         {
#endif
            wrSmHdlBndMacStack(event);
            break;
         }
      case WR_SM_STATE_RRC_STK_BND_DONE:
         {
            //TipSendPjBndReqRlc(Inst WR_SM_KWDL_INST);
            break;
         }
      default:
         {
            RLOG1(L_ERROR, "smWrProcSm() Invalid  state [%d] received",
                  smCb.smState);
            break;
         }
   }
   RETVOID;
} /* smWrProcSm */
#endif

/********************************************************************30**

           End of file:     fc_smm_init_t2k.c@@/main/TeNB_Main_BR/13 - Mon Aug 11 16:52:17 2014

*********************************************************************31*/


/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
