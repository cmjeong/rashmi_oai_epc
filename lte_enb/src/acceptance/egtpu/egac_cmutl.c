
/********************************************************************20**

     Name:    EGTP 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    egac_cmutl.c

     Sid:      egac_cmutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:23 2015

     Prg:     ad

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_tpt.h"         /* Transport  header file       */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */

#include "leg.h"           /* Egtpeter Layer Manager   */
#include "egt.h"           /* Egtpeter Upper Interface */
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#endif
#ifdef SS_MULTIPLE_PROCS
#include "eg_edm.h"        /* EDM Module structures            */
#endif /* SS_MULTIPLE_PROCS */
#include "eg.h"           /* Egtpeter Upper Interface */
#include "eg_edm.h"
#include "eg_util.h"       /* Egtpeter Utility library */
#include "egac_edm.h"           /* Egtpeter Upper Interface */
#if 0
#include "eg_dbutl.h"       /* IE Types and message types */
#endif
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_tpt.x"         /* Transport  header file       */
#include "cm_llist.x"      /* common link list */
#include "cm_dns.h"
#include "cm_dns.x"

#include "egt.x"           /* Eg Upper Interface */
#include "leg.x"           /* Eg layer manager  */

/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif
#include "cm_xta.h"
#include "egac_acc.h"
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"
#include "eg_tpt.x"            /* EGTP TPT module defines */

#include "cm_xta.x"
#include "egac_acc.x"
#include "egac_edm.x"
#include "eg_edm.x"
#include "egac_egt.x"
#include "eg_util.x"       /* Eg Utility library */

#if 0
#include "eg_dbutl.x"           /* Egtpeter Upper Interface */
#endif
#ifdef EGTP_C
#include "eg_dbs3.x"           /* Egtpeter Upper Interface */
#include "eg_dbs4.x"           /* Egtpeter Upper Interface */
#include "eg_dbs10.x"           /* Egtpeter Upper Interface */
#include "eg_dbs16.x"           /* Egtpeter Upper Interface */
#ifdef EG_REL_930
#include "eg_dbsn.x"           /* Egtpeter Upper Interface */
#include "eg_dbsm.x"           /* Egtpeter Upper Interface */
#endif /* EG_REL_930 */
/* eg009.201 - Added for S2B */
#ifdef EG_S2B_SUPP
#include "eg_dbs2b.x"           /* Egtp S2B Interface */
#endif /* EG_S2B_SUPP */
/* eg009.201 - Added for S2A */
#ifdef EG_S2A_SUPP
#include "eg_dbs2a.x"           /* Egtp S2A Interface */
#endif /* EG_S2A_SUPP */
#endif
#if 0
#include "eg_dbs11.x"           /* Egtpeter Upper Interface */
#include "eg_dbs5.x"           /* Egtpeter Upper Interface */
#endif
/*eg004.201 Header files added for eGTP-C PSF*/
#ifdef HW
#include "lhw.x"
#include "hw.x"
#endif

#ifdef EGTP_C
 /********************************************
  * Encode Decode Mapping function structure *
  ********************************************/
typedef struct parse_cmd {
S16 (*egacencParseFn) ARGS((EgIe* ,Buffer*));
S16 (*egacdecParseFn) ARGS((EgIe* ,Buffer*,U16));
}IEPARSE_CMD;

PRIVATE S16 egAcEncodeGmHdr ARGS((CmXtaTCCb *tcCb,CmXtaSpCb *spCb,EgMsg *egMsg, Buffer *mBuf));

PRIVATE S16 egAcEncIe ARGS((CmXtaTCCb *tcCb,CmXtaSpCb *spCb,EgIe *ie, Buffer *mBuf));

PRIVATE S16 egAcEncIeData ARGS((EgIe *ie, Buffer *mBuf));

/********************************************************
 * Encode Parser Functions for eGTP Message IE Encoding *
 ********************************************************/
PRIVATE S16 egAcEncEG_UNSIGNED_8 ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_UNSIGNED_16 ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_UNSIGNED_32 ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_STRING_8 ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_STRING_16 ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_STRING_32 ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_STRING_132 ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_STRING_MAX ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_SNETWORK ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_INDICATION ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_PVT_EXTN ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_CAUSE ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_TRC_INFO ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_BEARER_FLAG ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_FTEID ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_ULI_DATA ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_FQOS ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_BQOS_IEDATA ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_PAA_IEDATA ARGS((EgIe* ,Buffer*));
/* PRIVATE S16 egAcEncEG_BID_LST ARGS((EgIe* ,Buffer*)); */
PRIVATE S16 egAcEncEG_GLOBAL_CNID ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_AUTH_QUIN ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_AUTH_QUAD ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_CMP_REQ ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_GUTI ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_F_CONT ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_TRGTID ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_PKTFLOWID ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_SRCID ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_PDN_CONN_SET_ID ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_IP_ADDR ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_GSM_KEY_TRIP ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_UMTS_KEY_CIPH_QUIN ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_GSM_KEY_CIPH_QUIN ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_UMTS_KEY_QUIN ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_EPS_SEC_QUAD_QUIN ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_UMTS_KEY_QUAD_QUIN ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_F_CAUSE ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_S103_PDN_FW_INFO ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_S1U_DATA_FW ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_SRC_RNC_PDCP_CTX ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_PDUNUM ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_UE_TIME_ZONE ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_TRACE_REF ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_RAB_CONTEXT ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_AMBR ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_GLOBAL_CN_ID ARGS((EgIe* ,Buffer*));
#ifdef EG_REL_930
PRIVATE S16 egAcEncEG_MBMS_IPMCAST_DIST ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_UCI ARGS((EgIe* ,Buffer*));
PRIVATE S16 egAcEncEG_CSG_INFO_REP_ACT ARGS((EgIe* ,Buffer*));
#endif /* EG_REL_930 */


PRIVATE S16 egAcDecodeGmHdr ARGS((EgMsg *egMsg, Buffer *mBuf));

PRIVATE S16 egAcDecIe ARGS((EgMsg *egMsg, Buffer *mBuf, 
                           EgIeLevelInfo *ieLvlInfo, U16 *outIeLen));

PRIVATE S16 egAcDecGrpIe ARGS((EgMsg *egMsg, Buffer *mBuf, 
                           EgIeLevelInfo *ieLvlInfo, U16 ieLen));

PRIVATE S16 egAcDecIeData ARGS((EgMsg *egMsg, LegIeEntry *ieEntry, 
                              Buffer *mBuf, EgIe *egIe, U16 ieLen));
/********************************************************
 * Decode Parser Functions for eGTP Message IE Encoding *
 ********************************************************/
PRIVATE S16 egAcDecEG_UNSIGNED_8 ARGS((EgIe* ,Buffer*,U16 ));
PRIVATE S16 egAcDecEG_UNSIGNED_16 ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_UNSIGNED_32 ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_STRING_8 ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_STRING_16 ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_STRING_32 ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_STRING_132 ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_STRING_MAX ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_SNETWORK ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_INDICATION ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_CAUSE ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_PVT_EXTN ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_TRC_INFO ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_BEARER_FLAG ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_FTEID ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_ULI_DATA ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_FQOS ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_BQOS_IEDATA ARGS((EgIe* ,Buffer*,U16));
PRIVATE S16 egAcDecEG_PAA_IEDATA ARGS((EgIe* ,Buffer*,U16));
/* PRIVATE S16 egAcDecEG_BID_LST ARGS((EgIe* ,Buffer*, U16)); */
PRIVATE S16 egAcDecEG_GLOBAL_CNID ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_AUTH_QUIN ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_AUTH_QUAD ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_CMP_REQ ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_GUTI ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_F_CONT ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_TRGTID ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_PKTFLOWID ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_SRCID ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_PDN_CONN_SET_ID ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_IP_ADDR ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_GSM_KEY_TRIP ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_UMTS_KEY_CIPH_QUIN ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_GSM_KEY_CIPH_QUIN ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_UMTS_KEY_QUIN ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_EPS_SEC_QUAD_QUIN ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_UMTS_KEY_QUAD_QUIN ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_F_CAUSE ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_S103_PDN_FW_INFO ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_S1U_DATA_FW ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_SRC_RNC_PDCP_CTX ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_PDUNUM ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_UE_TIME_ZONE ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_TRACE_REF ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_RAB_CONTEXT ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_AMBR ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_GLOBAL_CN_ID ARGS((EgIe* ,Buffer*, U16));
#ifdef EG_REL_930
PRIVATE S16 egAcDecEG_MBMS_IPMCAST_DIST ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_UCI ARGS((EgIe* ,Buffer*, U16));
PRIVATE S16 egAcDecEG_CSG_INFO_REP_ACT ARGS((EgIe* ,Buffer*, U16));
#endif /* EG_REL_930 */

/******************************************
 * Encode Decode Mapping function Metrics *
 ******************************************/
IEPARSE_CMD EgacParse_function[] =
{
  { NULLP, NULLP },
  IEPARSEMAPFUNCTION(EG_FTEID), /* 1 */
  IEPARSEMAPFUNCTION(EG_UNSIGNED_8) ,
  IEPARSEMAPFUNCTION(EG_UNSIGNED_16),
  IEPARSEMAPFUNCTION(EG_UNSIGNED_32),
  IEPARSEMAPFUNCTION(EG_CAUSE),
  IEPARSEMAPFUNCTION(EG_PVT_EXTN),
  IEPARSEMAPFUNCTION(EG_TRC_INFO),
  IEPARSEMAPFUNCTION(EG_ULI_DATA),
  IEPARSEMAPFUNCTION(EG_FQOS),
  IEPARSEMAPFUNCTION(EG_BQOS_IEDATA), /* 10 */
  IEPARSEMAPFUNCTION(EG_PAA_IEDATA),
  IEPARSEMAPFUNCTION(EG_GLOBAL_CNID),
  IEPARSEMAPFUNCTION(EG_STRING_8),
  IEPARSEMAPFUNCTION(EG_STRING_16),
  IEPARSEMAPFUNCTION(EG_STRING_32),
  IEPARSEMAPFUNCTION(EG_STRING_132),
  IEPARSEMAPFUNCTION(EG_STRING_MAX),
  IEPARSEMAPFUNCTION(EG_SNETWORK),
  IEPARSEMAPFUNCTION(EG_INDICATION),
  IEPARSEMAPFUNCTION(EG_BEARER_FLAG), /* 20 */
  {NULLP , NULLP}, 
  IEPARSEMAPFUNCTION(EG_IP_ADDR),
  IEPARSEMAPFUNCTION(EG_S103_PDN_FW_INFO),
  IEPARSEMAPFUNCTION(EG_S1U_DATA_FW),
  IEPARSEMAPFUNCTION(EG_PDUNUM),
  IEPARSEMAPFUNCTION(EG_UE_TIME_ZONE),
  IEPARSEMAPFUNCTION(EG_TRACE_REF),
  IEPARSEMAPFUNCTION(EG_RAB_CONTEXT),
  IEPARSEMAPFUNCTION(EG_GSM_KEY_TRIP),
  IEPARSEMAPFUNCTION(EG_UMTS_KEY_CIPH_QUIN), /* 30 */
  IEPARSEMAPFUNCTION(EG_GSM_KEY_CIPH_QUIN),
  IEPARSEMAPFUNCTION(EG_UMTS_KEY_QUIN),
  IEPARSEMAPFUNCTION(EG_EPS_SEC_QUAD_QUIN),
  IEPARSEMAPFUNCTION(EG_UMTS_KEY_QUAD_QUIN),
  IEPARSEMAPFUNCTION(EG_AUTH_QUIN),
  IEPARSEMAPFUNCTION(EG_AUTH_QUAD),
  IEPARSEMAPFUNCTION(EG_CMP_REQ),
  IEPARSEMAPFUNCTION(EG_GUTI),
  IEPARSEMAPFUNCTION(EG_F_CONT), 
  IEPARSEMAPFUNCTION(EG_F_CAUSE), /* 40 */
  IEPARSEMAPFUNCTION(EG_TRGTID),
  IEPARSEMAPFUNCTION(EG_SRCID),
  IEPARSEMAPFUNCTION(EG_PKTFLOWID),
  IEPARSEMAPFUNCTION(EG_SRC_RNC_PDCP_CTX),
  IEPARSEMAPFUNCTION(EG_PDN_CONN_SET_ID), /* 45 */
  IEPARSEMAPFUNCTION(EG_AMBR), /* 46 */
  IEPARSEMAPFUNCTION(EG_GLOBAL_CN_ID), /* 47 */
#ifdef EG_REL_930
  IEPARSEMAPFUNCTION(EG_MBMS_IPMCAST_DIST), /* MBMS IP Multicast distribution */
  IEPARSEMAPFUNCTION(EG_UCI),               /* user CSG Information */
  IEPARSEMAPFUNCTION(EG_CSG_INFO_REP_ACT), /* 50 */ /* CSG info reporting action */
#endif /* EG_REL_930 */
  {NULLP , NULLP},
  {NULLP , NULLP},
};

EXTERN Void  makeAndAddRecoveryIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddPvtExtnIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddUnknownIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo
));

PUBLIC Void  egEgtBuildEchoMsgRsp ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg **egMsg,
Mem         *memInfo
));

PUBLIC Void  egEgtBuildEchoMsgReq ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg **egMsg,
Mem         *memInfo
));

/* eg001.102 snatarajan  1. EGTP_C Path management changes. */
PRIVATE S16 egAcEncEG_IP_ADDR ARGS
((
EgIe       *egIe,
Buffer     *mBuf
));

PRIVATE S16 egAcDecEG_IP_ADDR ARGS
((
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
));

PRIVATE S16 egAcEncEG_S103_PDN_FW_INFO ARGS
((
EgIe   *egIe,
Buffer *mBuf
));

PRIVATE S16 egAcDecEG_S103_PDN_FW_INFO ARGS
((
EgIe   *egIe,
Buffer *mBuf,
U16        ieLen
));

PRIVATE S16 egAcDecEG_S1U_DATA_FW ARGS
((
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
));

PRIVATE S16 egAcEncEG_S1U_DATA_FW ARGS
((
EgIe       *egIe,
Buffer     *mBuf
));

PRIVATE S16 egAcEncEG_PDUNUM ARGS
((
EgIe       *egIe,
Buffer     *mBuf
));

PRIVATE S16 egAcDecEG_PDUNUM ARGS
((
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
));

PRIVATE S16 egAcEncEG_GSM_KEY_TRIP ARGS
((
EgIe   *egIe,
Buffer *mBuf
));

PRIVATE S16 egAcDecEG_GSM_KEY_TRIP ARGS
((
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
));

PRIVATE S16 egAcEncEG_UMTS_KEY_CIPH_QUIN ARGS
((
EgIe       *egIe,
Buffer     *mBuf
));

PRIVATE S16 egAcDecEG_UMTS_KEY_CIPH_QUIN ARGS
((
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
));

PRIVATE S16 egAcEncEG_GSM_KEY_CIPH_QUIN ARGS
((
EgIe   *egIe,
Buffer *mBuf
));

PRIVATE S16 egAcDecEG_GSM_KEY_CIPH_QUIN ARGS
((
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
));

PRIVATE S16 egAcEncEG_UMTS_KEY_QUIN ARGS
((
EgIe   *egIe,
Buffer *mBuf
));

PRIVATE S16 egAcDecEG_UMTS_KEY_QUIN ARGS
((
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
));

PRIVATE S16 egAcEncEG_EPS_SEC_QUAD_QUIN ARGS
((
EgIe   *egIe,
Buffer *mBuf
));

PRIVATE S16 egAcDecEG_EPS_SEC_QUAD_QUIN ARGS
((
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
));

PRIVATE S16 egAcEncEG_UMTS_KEY_QUAD_QUIN ARGS
((
EgIe   *egIe,
Buffer *mBuf
));

PRIVATE S16 egAcDecEG_UMTS_KEY_QUAD_QUIN ARGS
((
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
));

PRIVATE S16 egAcEncEG_AUTH_QUIN ARGS
((
EgIe       *egIe,
Buffer     *mBuf
));

PRIVATE S16 egAcDecEG_AUTH_QUIN ARGS
((
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
));

PRIVATE S16 egAcEncEG_AUTH_QUAD ARGS
((
EgIe       *egIe,
Buffer     *mBuf
));

PRIVATE S16 egAcDecEG_AUTH_QUAD ARGS
((
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
));

PRIVATE S16 egAcEncEG_CMP_REQ ARGS
((
EgIe   *egIe,
Buffer *mBuf
));

PRIVATE S16 egAcDecEG_CMP_REQ ARGS
((
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
));

PRIVATE S16 egAcEncEG_GUTI ARGS
((
EgIe       *egIe,
Buffer     *mBuf
));


PRIVATE S16 egAcDecEG_GUTI ARGS
((
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
));

PRIVATE S16 egAcEncEG_F_CONT ARGS
((
EgIe   *egIe,
Buffer *mBuf
));

PRIVATE S16 egAcDecEG_F_CONT ARGS
((
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
));

PRIVATE S16 egAcEncEG_F_CAUSE ARGS
((
EgIe   *egIe,
Buffer *mBuf
));

PRIVATE S16 egAcDecEG_F_CAUSE ARGS
((
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
));

PRIVATE S16 egAcEncEG_TRGTID ARGS
((
EgIe   *egIe,
Buffer *mBuf
));

PRIVATE S16 egAcDecEG_TRGTID ARGS
((
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
));

PRIVATE S16 egAcEncEG_PKTFLOWID ARGS
((
EgIe       *egIe,
Buffer     *mBuf
));

PRIVATE S16 egAcDecEG_PKTFLOWID ARGS
((
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
));

PRIVATE S16 egAcEncEG_SRC_RNC_PDCP_CTX ARGS
((
EgIe       *egIe,
Buffer     *mBuf
));

PRIVATE S16 egAcDecEG_SRC_RNC_PDCP_CTX ARGS
((
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
));

PRIVATE S16 egAcEncEG_PDN_CONN_SET_ID ARGS
((
EgIe   *egIe,
Buffer *mBuf
));

PRIVATE S16 egAcDecEG_PDN_CONN_SET_ID ARGS
((
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
));

#endif /* EGTP_C */

#ifdef EGTP_U
PRIVATE S16 egUAcEncodeGmHdr ARGS((CmXtaTCCb *tcCb,CmXtaSpCb *spCb,EgUMsg *eguMsg, Buffer *mBuf));

PRIVATE S16 egUAcEncIe ARGS((CmXtaTCCb *tcCb,CmXtaSpCb *spCb,EgUIe *ie, Buffer *mBuf));

PRIVATE S16 egUAcEncIeData ARGS((EgUIe *ie, Buffer *mBuf));
PRIVATE S16 egUAcDecodeGmHdr ARGS((EgUMsg *egMsg, Buffer *mBuf ));
#endif /* EGTP_U */

#ifdef EGTP_C
/*
 *  
 *   Fun:  egAcEncodeGmHdr
 *   
 *   Desc:  To encode the Egtp Msg header as per specs
 *   
 *   Ret:   ROK  - for Success
 *   
 *   Notes: None
 *   
 *   File:  egac_egmutl.c
 *   
*/
#ifdef ANSI
PRIVATE S16 egAcEncodeGmHdr
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
EgMsg  *egMsg,
Buffer     *mBuf
)
#else
PRIVATE S16 egAcEncodeGmHdr( tcCb,spCb,egMsg, mBuf)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
EgMsg  *egMsg;
Buffer     *mBuf;
#endif
{
   S16              retValue = ROK;
   MsgLen           len = EGAC_LEN_THREE;
   EgMsgHdr         header;
   Data             dumMsgLen[EGAC_LEN_THREE]; /* for length encoding */
   U8               tmpByte;
   U8               spareByte[EGAC_LEN_TWO];
   EgAcTCCb     *egTcCb = NULLP;
   U8               msgVer= EGAC_MSG_VERSION;
   U8               unDefMsgType = FALSE;
       
#ifdef LEG_FILE_LOG 
   TRC3(egAcEncodeGmHdr)
#endif

   /********************************************
    * Clearing of message lenth and spare byte *
    *******************************************/
   cmMemset((U8*)dumMsgLen, EG_ZERO, len);
   cmMemset((U8*)spareByte, EG_ZERO, EGAC_LEN_TWO);

   /********************************************************
    * Copy the eGTP message header to a local buffer       *
    *******************************************************/
   cmMemset((U8* )&header, 0, sizeof(EgMsgHdr));
   cmMemcpy( (U8* )&header, (U8* )&egMsg->msgHdr,
           sizeof(EgMsgHdr));


   egTcCb = (EgAcTCCb *)tcCb->tcCb;
  

   retValue = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, (Txt  *)"version",  &msgVer);
   if(retValue != CMXTA_ERR_NO_VALUE)
   {
      header.version      = msgVer;
   }

   header.msgType      = egMsg->msgHdr.msgType;

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"unDefMsgType",  &unDefMsgType);
   
#ifdef NEXT
   retValue = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"seqNoIdx",  &seqNoIdx);
   if(retValue != CMXTA_ERR_NO_VALUE)
   {
     if ( egTcCb->seqNo[seqNoIdx].present == TRUE)
     {
       header.seqNumber = egTcCb->seqNo[seqNoIdx].value;
     }
   }
#endif /* NEXT */
   /********************************************************
    * Encode the version  number 
    *******************************************************/
   tmpByte = header.version << EGAC_SHIFT_5;

   /********************************************************
    * Encode the TEID value if present                     *
    *******************************************************/
   if(header.teidPres)
      tmpByte |=  EG_MASK_BIT4;
 
   SAddPstMsg(tmpByte, mBuf);

   /*********************************************************
    * Encode the Message Type                             *
    ********************************************************/
   if(unDefMsgType)
   { 
      SAddPstMsg(110, mBuf);
   }
   else
   {
      SAddPstMsg(header.msgType, mBuf);
   }

   /*********************************************************
    * Encode the message length with zeroes                 *
    * At the end of the encoding all the IE's, the final    *
    * Length will be calculated and updated the mBuf        *
    ********************************************************/
   SAddPstMsgMult(dumMsgLen, EGAC_LEN_TWO, mBuf);

   /*********************************************************
    * Encode the Teid if T-bit is set                       *
    ********************************************************/
   if(header.teidPres)
      EGAC_ENC_U32(header.teid, mBuf);

   /*********************************************************
    * Encode the sequence number                            *
    ********************************************************/
	 header.seqNumber &= 0x00FFFFFF;
	 header.seqNumber <<= EG_SHIFT_8;
	 header.seqNumber &= 0xFFFFFF00;

   EGAC_ENC_U32(header.seqNumber, mBuf);

#ifdef LEG_FILE_LOG
    EG_TRC_FILE(<< egAcEncodeGmHdr, LEG_DBGMASK_EDM)
#endif

   RETVALUE(ROK);


}


/*
 *  
 *   Fun:  egAcEncIe
 *   
 *   Desc:  acEncodes the IE 
 *   
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   
 *   Notes: None
 *   
 *   File:  eg_denc.c
 *   
*/
#ifdef ANSI
PRIVATE S16 egAcEncIe
(
CmXtaTCCb *tcCb,
CmXtaSpCb *spCb,
EgIe  *ie,
Buffer *mBuf 
)
#else
PRIVATE S16 egAcEncIe(tcCb,spCb,ie, mBuf)
CmXtaTCCb *tcCb;
CmXtaSpCb *spCb;
EgIe  *ie;
Buffer *mBuf; 
#endif
{

   S16      retVal = ROK;
   MsgLen   initLen = 0; /* Initial mBuf Length for Grp IE length encoding */
   MsgLen   finLen = 0;  /* final mBuf Length for Grp IE length encoding */
   U16   ieLen = 0;  /* actual length of IE being encoded */
   Data     dumBytes[EGAC_LEN_BYTES];
   CmLList *tmpNode = NULLP;
   EgIe    *tmpIe = NULLP;
   U16      cnt = 0;
   U8       tmpByte = 0;
   U8       invRecovIeLen = 1;
   U8       invPvtextIeLen = 3;
   Bool     invalidIeLengthFlag = FALSE;

#ifdef LEG_FILE_LOG 
   TRC3(egAcEncIe);
#endif


   cmMemset((U8*)dumBytes, 0, EGAC_LEN_BYTES);

   /*************************
    * Check for IE validity *
    ************************/
   if(ie == NULLP)
   {
      retVal = EGT_ERR_MSG_UNABLE_TO_COMPLY;
      RETVALUE(retVal);
   }

   /****************************************
    * Store the index to encode the length *
    ***************************************/
   SFndLenMsg(mBuf, &initLen);

   /**********************
    * Encode the IE Type *
	 *********************/
	SAddPstMsg(ie->ieType, mBuf);

	/******************************************
	 * Encode dummy bytes in the length field *
	 *******************************************/
	SAddPstMsgMult((U8*)dumBytes, EGAC_LEN_TWO, mBuf);

	/**************************
	 * Encode the IE Instance *
	 ***************************/
	tmpByte = (tmpByte | (ie->ieInst & EGAC_MASK_INST));
	SAddPstMsg(tmpByte, mBuf);

   /**************************************
    * check whether this is a grouped IE *
    *************************************/
   if(ie->dataType == EGAC_GROUPED)
   {
      /**********************************
       * Call the encode IE recursively *
       *********************************/
      CM_LLIST_FIRST_NODE(&ie->t.grouped.gIeList, tmpNode);
      while((cnt < ie->t.grouped.gIeList.count) && (tmpNode))
      {
         tmpIe = (EgIe*)tmpNode->node;
         retVal = egAcEncIe(tcCb,spCb,tmpIe, mBuf);
 
         /********************************
          * Encoding of IE is successful *
          *******************************/
         if(retVal == ROK)
         {
            cnt++;
            CM_LLIST_NEXT_NODE(&ie->t.grouped.gIeList, tmpNode);
         }
         else
         {
            RETVALUE(retVal);
         }
      }
   }
   else
   {
   /**********************
    * Encode the IE data *
    *********************/ 
      retVal = egAcEncIeData( ie, mBuf);
      if(retVal != ROK)
         RETVALUE(retVal);
   }
   /********************************************
    * Encode the IE length for this grouped IE *
    *******************************************/
   SFndLenMsg(mBuf, &finLen);

   /***********************************
    * Decrement 4bytes for the ie Hdr *
    **********************************/
   ieLen = finLen - initLen - EGAC_LEN_FOUR;
   
   /***********************************************************
    * Increment the index to point the actual length location *
    **********************************************************/
   initLen += EGAC_IE_LEN_OFFSET;


   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_ENUM_U8,(Txt  *)"invalidIeLengthFlag",&invalidIeLengthFlag);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,
                 (Txt  *)"invRecovIeLen",  &invRecovIeLen);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,
                 (Txt  *)"invPvtextIeLen",  &invPvtextIeLen);

   if(invalidIeLengthFlag)
   {
      switch(ie->ieType)
      {
         case EGAC_IMSI_IETYPE:
            {
               ieLen = 6; 
               break;
            }
         case EGAC_PCO_IETYPE:
            {
               ieLen = 16; 
               break;
            }
         case EGAC_RECOV_IETYPE:
            {
               ieLen = invRecovIeLen;
               break;
            }
         case EGAC_PEXT_IETYPE:
            {
               ieLen = invPvtextIeLen;
               break;
            }
      } /* end of switch statement */
   } /* end of if statement   */

   /********************************************
    * Encode the offset b/w finLen and initLen *
    *******************************************/
   EGAC_ENC_LEN(ieLen, mBuf, initLen); 
   
   RETVALUE(retVal);
}



/***********************************************************************
*
*   Fun:  egAcEncIeData
*
*   Desc:  Encode the GTP Msg IE Data part
*
*   Ret:   ROK  - for Success
*          RFAILED - for Failure
*
*   Notes: None
*
*   File:  eg_edm.c
*
***********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncIeData
(
EgIe      *egIe,            /* IE to encode the data portion */
Buffer     *mBuf          /* Buffer to hold the Encoded msg */
) 
#else
PRIVATE S16 egAcEncIeData(egIe, mBuf)
EgIe        *egIe;       /* IE to encode the data portion */
Buffer      *mBuf;       /* Buffer to hold the Encoded msg */
#endif
{
   S16         retVal = ROK;           /* Holds the return value */
   Data        dumBytes[EGAC_MAX_BYTES]; /* tmp holds the data for Enc */

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncIeData);

	cmMemset((U8*)dumBytes, EGAC_ZERO, EGAC_LEN_BYTES);
	/*****************************************************
	 * Check if the data type is out of index    (OR)    *
	 * The index of the function is not valid one        *
	 *******************************************************/
	if((egIe->dataType >= EG_MAX_DATATYPE) ||
		 !(EgacParse_function[egIe->dataType].egacencParseFn))
	{
	  retVal = EGT_ERR_INV_IE_TYPE;
	}
	else
	{
	  /**************************************************
		*       * Handling of encoding  of different data types  *
		*             **************************************************/
	  retVal = EgacParse_function[egIe->dataType].egacencParseFn(egIe,mBuf);
	}

    RETVALUE(retVal);    
}

/*************************************************************************
 *  
 *   Fun:  egAcDecIeData
 *   
 *   Desc:  Decodes the GTP Msg IE Data part 
 *   
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   
 *   Notes: None
 *   
 *   File:  eg_edm.c
 *   
 *************************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecIeData
(
EgMsg     *egMsg,  /* Event message to stores the decoded ie */
LegIeEntry *ieEntry, /* IE ENTRY */
Buffer         *mBuf,     /* Buffer which has to decode */
EgIe           *egIe,     /* Ie to store the decoded IE data */
U16             ieLen      /* IE Length psnt in the Hdr */
)
#else
PRIVATE S16 egAcDecIeData(egMsg, ieEntry, mBuf, egIe, ieLen)
EgMsg *egMsg;      /* Event message to stores the decoded ie */
LegIeEntry *ieEntry; /* IE ENTRY */
Buffer     *mBuf;         /* Buffer which has to decode */
EgIe      *egIe;          /* Ie to store the decoded IE data */
U16         ieLen;         /* Total Ie Length excluding hdr   */
#endif
{
   S16      retVal;           /* Holds the return value */
   Data     dumBytes[EGAC_MAX_BYTES]; /* Holds the Data for decoding */
   U8       tmpByte;         /* Holds 1 byte of data for decoding  */

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecIeData);

   retVal = ROK;
   tmpByte =0;
   cmMemset((U8*)dumBytes, EGAC_ZERO, EGAC_LEN_BYTES);

	  /*************************************************
		* Check if the data type is out of index (OR)   *
		* The index of the function is not valid one    *
		*************************************************/
	  if((ieEntry->dataType >=EG_MAX_DATATYPE) ||
			!(EgacParse_function[ieEntry->dataType].egacdecParseFn))
	  {
		 retVal = EGT_ERR_INV_IE_TYPE;
	  }
	  else
	  {
		 retVal = EgacParse_function[ieEntry->dataType].egacdecParseFn(egIe,mBuf,ieLen);
	  }

   RETVALUE(retVal);
}

/*
*
*    Fun:     egAcEncEgMsg
*
*    Desc:    encode the structure EgMsg
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    egAc_egtutl2.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcEncEgMsg
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg          *egMsg,  /* the egtp message to be encoded */
Buffer      **mBuf    /* to hold the encoded buffer */
)
#else
PUBLIC S16 egAcEncEgMsg(tcCb,spCb,egMsg, mBuf)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg          *egMsg;  /* the egtp message to be encoded */
Buffer      **mBuf;   /* to hold the encoded buffer */
#endif
{
   /* this is used to hold the return value of sub methods */
   S16      retVal = 0;
   U8       cnt=0;
   EgIe    *ie = NULLP;
   CmLList  *tmpNode = NULLP;
   MsgLen    msgLen =0;
   U32       msgLength=0;
   Bool      invalidMsgLength = FALSE;
   S16       retInvalid=ROK;

#ifdef LEG_FILE_LOG 
   TRC3(egAcEncEgMsg)
#endif 

   /* validation is successful, do the encoding */
   /* allocating memory for the buffer */
   retVal = SGetMsg(DFLT_REGION, DFLT_POOL, mBuf);
   if(retVal != ROK)
   {
      /* send msg to Main thread with result code set to RFAILED */
      retVal = EGAC_ERR_MEM_ALLOC_FAILED;
      RETVALUE(retVal);
   }
   /* encode the Msg header */
   retVal = egAcEncodeGmHdr(tcCb,spCb,egMsg, *mBuf);
   if(retVal != ROK)
   {
      /* free the mBuf */
      SPutMsg(*mBuf);
      RETVALUE(retVal);
   }

   /* encode the IE one by one */
   /* get the first IE in the List */
   CM_LLIST_FIRST_NODE(&egMsg->egIeList, tmpNode);
   for(cnt = 0; ((cnt < egMsg->egIeList.count) && (tmpNode)); cnt++)
   {
      ie = (EgIe*)tmpNode->node;
      /* encode the IE */
      retVal = egAcEncIe(tcCb,spCb,ie,*mBuf);
      if(retVal != ROK)
      {
      /* encoding failed. send Msg to Main Thread */
      /* free the mBuf */
         SPutMsg(*mBuf);
         RETVALUE(retVal);
      }
      else
      {
         /* get the next IE from the List */
         CM_LLIST_NEXT_NODE(&egMsg->egIeList, tmpNode);
      }
   }

   /* fill the Msg length */
   SFndLenMsg(*mBuf, &msgLen);

   if((egMsg->msgHdr.msgType == EGT_GTPC_MSG_ECHO_RSP) ||
     (egMsg->msgHdr.msgType == EGT_GTPC_MSG_ECHO_REQ))
      msgLen -= EGAC_LEN_FOUR;
   else   
      msgLen -= EGAC_LEN_FOUR;
   cnt = 2; /* length starts from index 2 */
   retInvalid = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_ENUM_U8,(Txt  *)"invalidMsgLength",&invalidMsgLength);
   if(retInvalid != CMXTA_ERR_NO_VALUE)
   {
      cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U32,(Txt  *)"msgLength",&msgLength);
      msgLen =  msgLength; 
   }
   EGAC_ENC_LEN(msgLen, *mBuf, cnt);
   EgUtilDeAllocGmMsg(&egMsg);
   

   RETVALUE(ROK);
} /*end of egAcEncEgMsg */


/*
*
*    Fun:     egAcDecEgMsg
*
*    Desc:    Decode the structure EgMsg from buffer
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    egAc_egtutl2.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcDecEgMsg
(
EgMsg   *egMsg,     /* to hold the decodeed egtp message */
Buffer      *mBuf       /* the encodeed buffer */
)
#else
PUBLIC S16 egAcDecEgMsg(egMsg, mBuf)
EgMsg   *egMsg;     /* to hold the decodeed egtp message */
Buffer      *mBuf;      /* the encodeed buffer */
#endif
{
   /* initialized local variables */
   MsgLen msgLen = 0;
   /* this is used to hold the return value of sub methods */
   Mem       mem;
   S16      retVal = 0;
   EgIeLevelInfo   ieLvlInfo;
   U16       ieLen = 0;
   Bool      validateIe = FALSE;

#ifdef LEG_FILE_LOG 
   TRC3(egAcDecEgMsg)
#endif

   mem.region  = DFLT_REGION;
   mem.pool    = DFLT_POOL;

   /* find the msg Length for tracking purpose */
   SFndLenMsg(mBuf, &msgLen);

   cmMemset((Data *)&ieLvlInfo, 0, sizeof(EgIeLevelInfo));

   /* decode the Egtp Msg Header */
   retVal = egAcDecodeGmHdr(egMsg, mBuf);
   if(retVal != ROK)
   {
      /* free the memory */
      SPutMsg(mBuf);
      /* decoding failed. send Msg to Main Thread */
      RETVALUE(retVal);
   }
   /*eg007.201: read the flag for IE validation */
   cmXtaXmlGetVal(NULLP,NULLP,CMXTA_ATTRIB_BOOL,(Txt  *)"validateIe",&validateIe);
   if (!validateIe)
   {
      /* just return from here don't validate the IEs */
      RETVALUE(ROK);
   }

   /*  decode the IEs */
   msgLen -= EGAC_LEN_TWELVE;
   while(msgLen)
   {
      ieLvlInfo.level = 0;
      retVal = egAcDecIe(egMsg, mBuf, &ieLvlInfo, &ieLen);
      if(retVal != ROK)
      {
         SPutMsg(mBuf);
         /* decoding failed, send Msg to Main thread */
         RETVALUE(retVal);
      }
      SFndLenMsg(mBuf, &msgLen);
   }

   RETVALUE(ROK);
} /*end of egAcDecEgMsg */


/*
 *  
 *   Fun:  egAcDecodeGmHdr
 *   
 *   Desc:  Decodes the Egtp Msg Header
 *   
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   
 *   Notes: None
 *   
 *   File:  eg_denc.c
 *   
*/
#ifdef ANSI
PRIVATE S16 egAcDecodeGmHdr
(
EgMsg  *egMsg, 
Buffer     *mBuf
)
#else
PRIVATE S16 egAcDecodeGmHdr(egMsg, mBuf)
EgMsg  *egMsg; 
Buffer     *mBuf;
#endif
{

   S16      retVal = ROK;
   MsgLen   msgLen = 0;
   MsgLen   bufLen = 0; 
   U8       tmpByte = 0;

#ifdef LEG_FILE_LOG 
   TRC3(egAcDecodeGmHdr);
#endif 


   /*************************************************************
    * Check for validity of event message and mBuf              *
    ************************************************************/
   if(mBuf == NULLP)
   {
      retVal = EGT_ERR_MSG_UNABLE_TO_COMPLY;
      RETVALUE(retVal);
   }

   /****************************************************
    * Check the length of buffer to be decoded         *
    ***************************************************/
   SFndLenMsg(mBuf, &bufLen);

   /******************************
    * decode the version         *
    *****************************/
   SRemPreMsg(&tmpByte, mBuf);
   egMsg->msgHdr.version = tmpByte >> EGAC_SHIFT_5;

   /******************************
    * decode the message Type    *
    *****************************/
   SRemPreMsg(&(egMsg->msgHdr.msgType), mBuf);

   /******************************
    * decode the message length  *
    *****************************/
   EGAC_DEC_U16(msgLen, mBuf);
   
   bufLen -= EGAC_LEN_FOUR;

   /***********************************
    * decode the Teid if T-bit is set *
    **********************************/
   if ( tmpByte & EGAC_MASK_BIT4 )
   {
      egMsg->msgHdr.teidPres = TRUE;
      EGAC_DEC_U32(egMsg->msgHdr.teid, mBuf);
      bufLen -= EGAC_LEN_FOUR;
   }
   
   /***********************
    * decode the seq no   *
    **********************/
   EGAC_DEC_U32(egMsg->msgHdr.seqNumber, mBuf);
	egMsg->msgHdr.seqNumber >>= EGAC_LEN_EIGHT;
	egMsg->msgHdr.seqNumber &= 0x00FFFFFF;

   bufLen -= EGAC_LEN_FOUR;
  

   RETVALUE(retVal); 
} 


/*
 *  
 *   Fun:  egAcDecIe
 *   
 *   Desc:  Decodes the Egtp IE 
 *   
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   
 *   Notes: None
 *   
 *   File:  eg_denc.c
 *   
*/
#ifdef ANSI
PRIVATE S16 egAcDecIe
(
EgMsg      *egMsg, 
Buffer         *mBuf,
EgIeLevelInfo *ieLvlInfo,
U16            *outIeLen
)
#else
PRIVATE S16 egAcDecIe(egMsg, mBuf, ieLvlInfo, outIeLen)
EgMsg      *egMsg; 
Buffer         *mBuf;
EgIeLevelInfo *ieLvlInfo;
U16            *outIeLen;
#endif
{
   S16              retVal = ROK;
   EgIe             tmpIe;
   LegIeEntry       *ieEntry = NULLP;
   MsgLen           msgLen = 0;
   U16           tmpIeLen = 0;
   EgUstaDgn        dgn;
   Data             dumBytes[EGAC_LEN_BYTES];
   EgIeLevelInfo    tmpLvlInfo;
   U16              cnt = 0;
   U8               tmpByte = 0;

#ifdef LEG_FILE_LOG 
   TRC3(egAcDecIe);
#endif 

   cmMemset((U8*)dumBytes, EG_ZERO, EGAC_LEN_BYTES);
   cmMemset((U8*)&dgn, EG_ZERO, sizeof(EgUstaDgn));
   cmMemset((U8*)&tmpLvlInfo, EG_ZERO, sizeof(tmpLvlInfo));
   cmMemset((U8*)&tmpIe, EG_ZERO, sizeof(EgIe));

   /*****************************************
    * find the length of the encoded buffer *
    ****************************************/
   SFndLenMsg(mBuf, &msgLen);

   /*************************
    * decode the IE Type    *
    ************************/
   SRemPreMsg(&tmpIe.ieType, mBuf);
   msgLen--;

   /************************
    * decode the IE length *
    ***********************/
   EGAC_DEC_U16(tmpIeLen, mBuf);
   msgLen -= EGAC_LEN_TWO;
   *outIeLen = tmpIeLen;

   /*******************************************
    * get the IE entry from the IE Dictionary *
    ******************************************/
   ieEntry = egGetIeFrmIeDict(tmpIe.ieType);
   if ( ieEntry == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /**********************************
    * decode the IE CR and Instance  *
    *********************************/
   SRemPreMsg(&tmpByte, mBuf);
   msgLen--;

   /************************************************************************
    * Get the instance and the Cr from the tmp Byte as the 4th octet is CR *
    * and Instance. Instance is present in 0,1,2,3 bits pos, 5th bit is    *
    * spare 6th, 7th and 8th bits are for CR value                         *
    ***********************************************************************/
   tmpIe.ieInst = tmpByte & EGAC_MASK_INST; /* Mask value is 0x1F */

   /********************************************
    * retreive the data type from the ie entry *
    *******************************************/
   tmpIe.dataType = ieEntry->dataType;

   /*******************************************
    * check whether this IE is grouped IE     *
    ******************************************/
   if(ieEntry->dataType == EG_GROUPED)
   {
      /***********************************
       * Fill the IE Level Info          *
       **********************************/
      EG_FILL_IE_LVL_INFO(ieLvlInfo, ieLvlInfo->level, tmpIe.ieType,
                          tmpIe.ieInst);
 
      /***********************************
       * Append this IE into the IE List *
       **********************************/
      EgUtilGmAppendIe(egMsg, ieLvlInfo, &tmpIe);   

      ieLvlInfo->level++;

      /********************************************************************
       * Call this function recursively to decode the IEs in the Group    *
       *******************************************************************/
      retVal = egAcDecGrpIe(egMsg, mBuf, ieLvlInfo, tmpIeLen);
      if(retVal != ROK)
         RETVALUE(retVal);

      /********************************************************************
       * Restore the level of the parent IE, so that the remaining IE's   *
       * can be appended correctly                                        *
       *******************************************************************/
      ieLvlInfo->level--;

      EG_FILL_IE_LVL_INFO(ieLvlInfo, ieLvlInfo->level, tmpIe.ieType,
                          tmpIe.ieInst);
   }
   else /* non-grouped IE */
   {
      /**********************
       * decode the IE Data *
       *********************/
      retVal = egAcDecIeData(egMsg, ieEntry, mBuf, &tmpIe, tmpIeLen);

      /*********************************************************************
       * if decoding fails, check whether for this IE CR is set or not     *
       ********************************************************************/
      /* TODO - need to find whether this is really req or not */
#ifdef NEXT 
      if(retVal != ROK)
      {
         if(intfType)
         {
         
            gmEntry = egAcDbGetMsgFrmGmDict(egMsg->msgHdr.msgType,
                                          intfType);
            if( gmEntry != NULLP)
            {
               /************************************************************
                * Get the ieProp and then check whether this ie is         *
                * mandatory or not                                         */
               if( (idx=gmEntry->posIndex[tmpIe.ieInst][tmpIe.ieType]) != 0)
               {
                  ieProp = gmEntry->ieProperties[idx];
                  if( ieProp.ieClass != EGAC_IE_MANDATORY)
                  {
                     /*****************
                      * skip the IE   *
                      ****************/
                     retVal = ROK;
                  }
                  else
                  {

                  }
               } /* end if ieEntry is found */
            } /* end of if gmEntry is valid */ 
         } /* End of if Intf Type is known  */
         if ( (!intfType) || (gmEntry != NULLP) || (idx == 0) )
         {
            /********************************************************** 
             * skip this IE and continue further processing           *
             *********************************************************/
            msgLen -= tmpIeLen;
            RETVALUE(ROK);
         }
      } /* End of if the retVal != ROK */
#endif /* NEXT */

   /********************************************************************
    * check whether it is a grouped IE, if it is check whether the     *
    * parent IE of this IE is already present, and use this count to   *
    * append the IE                                                    *
    *******************************************************************/
      if(ieLvlInfo->level)
      {
         for(cnt = 0; cnt < ieLvlInfo->level; cnt++)
         { 
            tmpLvlInfo.ieInfo[cnt].ieTypePres = ieLvlInfo->ieInfo[cnt].ieTypePres;
            tmpLvlInfo.ieInfo[cnt].ieType = ieLvlInfo->ieInfo[cnt].ieType;
         }
         tmpLvlInfo.level =  ieLvlInfo->level - 1;
      }

      /*****************************************
       * append this IE into the IE List       *
       ****************************************/
      EgUtilGmAppendIe(egMsg, ieLvlInfo, &tmpIe);   
   } /* end of the grouped chk */

   RETVALUE(retVal); 
}


/*
 *  
 *   Fun:  egAcDecGrpIe
 *   
 *   Desc:  Decodes the Egtp Grouped IE 
 *   
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   
 *   Notes: None
 *   
 *   File:  eg_denc.c
 *   
*/
#ifdef ANSI
PRIVATE S16 egAcDecGrpIe
(
EgMsg      *egMsg, 
Buffer         *mBuf,
EgIeLevelInfo *ieLvlInfo,
U16            inIeLen
)
#else
PRIVATE S16 egAcDecGrpIe(egMsg, mBuf, ieLvlInfo, inIeLen)
EgMsg      *egMsg; 
Buffer         *mBuf;
EgIeLevelInfo *ieLvlInfo;
U16            inIeLen;
#endif
{
   S16        retVal;
   U16        tmpIeLen;
   U16        grpIeLen;
   U16        padBytes;

#ifdef LEG_FILE_LOG 
   TRC3(egAcDecGrpIe);
#endif 

   retVal = ROK;
   tmpIeLen = 0;
   grpIeLen = inIeLen;
   padBytes = 0;


   while(grpIeLen)
   {
      retVal = egAcDecIe(egMsg, mBuf, ieLvlInfo, &tmpIeLen);
      if( retVal != ROK)
      { 
         RETVALUE(retVal);
      }
      grpIeLen -= tmpIeLen;
   }
   RETVALUE(retVal);
}



/*
*
*       Fun:   egEgtBuildEchoMsgRsp
*
*       Desc:  This function is used to Build EchoRsp message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildEchoMsgRsp
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg **egMsg,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildEchoMsgRsp(tcCb,spCb,egMsg,memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg **egMsg;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegIeProperties       ieProperties;
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egEgtBuildEchoMsgRsp)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildEchoMsgRsp() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
   cmMemset((U8 *)&ieProperties, 0 , sizeof(LegIeProperties));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_ECHO_RSP);

   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
   /* Common function which frame message based on instance value */
   ieProperties.ieInst = 0;
   makeAndAddRecoveryIe(tcCb,spCb,*egMsg,&egLvlInfo,ieProperties);
   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));

   ieProperties.ieInst = 0;
   /* Common function which frame message based on instance value */
   makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,ieProperties);
}


/*
*
*       Fun:   egEgtBuildEchoMsgReq
*
*       Desc:  This function is used to Build EchoReq message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_s11utl.c
*
*/

#ifdef ANSI
PUBLIC Void  egEgtBuildEchoMsgReq
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg **egMsg,
Mem         *memInfo
)
#else
PUBLIC Void egEgtBuildEchoMsgReq(tcCb,spCb,egMsg,memInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg **egMsg;
Mem         *memInfo;
#endif /* ANSI */
{
   EgIeLevelInfo         egLvlInfo;
   LegIeProperties       ieProperties;
   U8                    noIEs= FALSE;
   U8                    mandIePres = TRUE;
   U8                    unknownIe = TRUE;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egEgtBuildEchoMsgReq)

   if( EgUtilAllocGmMsg(egMsg,memInfo) != ROK )
   {
      CMXTA_DBG_ERR((_cmxtap,"egEgtBuildCrtSesReqMsg() : Unable to allocate memory for EGTP message\n"));
      RETVOID;
   }
   
   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
   cmMemset((U8 *)&ieProperties, 0 , sizeof(LegIeProperties));

   /* Build the Header  with Default values and also by taking from XML*/
   egAcEgtBuildEgHeader(tcCb,spCb,&((*egMsg)->msgHdr),EGT_GTPC_MSG_ECHO_REQ);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                     (Txt  *)"noIEs",  &noIEs);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                     (Txt  *)"mandIePres",  &mandIePres);
   if(!noIEs)
   {
   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
   /* Common function which frame message based on instance value */
   ieProperties.ieInst = 0;
   if(mandIePres)
   makeAndAddRecoveryIe(tcCb,spCb,*egMsg,&egLvlInfo,ieProperties);
   cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
   ieProperties.ieInst = 0;
   /* Common function which frame message based on instance value */
   makeAndAddPvtExtnIe(tcCb,spCb,*egMsg,&egLvlInfo,ieProperties);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                     (Txt  *)"unknownIe",  &unknownIe);
   
   if(unknownIe)
   {
      cmMemset((U8 *)&egLvlInfo, 0 , sizeof(EgIeLevelInfo));
      makeAndAddUnknownIe(tcCb, spCb, *egMsg, &egLvlInfo);
   }
   }
}


/*
*
*       Fun:   egAcEgtBuildEgS3Message
*
*       Desc:  This function is used to Build EG S3 message 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_eguutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcEdmBuildEgS3Message
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8          msgType,
EgMsg       **egMsg,
U8          intfType,
Mem         *memInfo
)
#else
PUBLIC S16 egAcEdmBuildEgS3Message(tcCb, spCb, msgType, egMsg, intfType, memInfo)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
U8          msgType;
EgMsg       **egMsg;
U8          intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEdmBuildEgS3Message);

   switch(msgType)
   {
	   case EGT_GTPC_MSG_FR_REQ:
      {
         egEgtBuildS3FwdRelReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_FR_RSP:
      {
         egEgtBuildS3FwdRelRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_FR_COMP_NOTFN:
      {
         egEgtBuildS3FwdRelCmpNtfMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_FR_COMP_ACK:
      {
         egEgtBuildS3FwdRelCmpAckMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_FWD_ACC_CNTXT_ACK:
      {
         egEgtBuildS3FwdRelCmpAckMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_DTCH_NOTFN:
      {
         egEgtBuildS3DetNtfMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_DTCH_ACK:
      {
         egEgtBuildS3DetAckMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      default:
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcEdmBuildEgS3Message(). Probable mismatch of the interface and the Message Type \n"));
      }
   } /* End of switch */

   RETVALUE(CMXTA_ERR_NONE);
}  /*  egAcEdmBuildEgS3Message */


/*
*
*       Fun:   egAcEgtBuildEgS4Message
*
*       Desc:  This function is used to Build EG S4 message 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_eguutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcEdmBuildEgS4Message
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8          msgType,
EgMsg       **egMsg,
U8          intfType,
Mem         *memInfo
)
#else
PUBLIC S16 egAcEdmBuildEgS4Message(tcCb, spCb, msgType, egMsg, intfType, memInfo)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
U8          msgType;
EgMsg       **egMsg;
U8          intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEdmBuildEgS4Message);

   switch(msgType)
   {
      case EGT_GTPC_MSG_CS_REQ:
      {
         /* Build CSREQ */
         egEgtBuildS4CrtSesReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_CS_RSP:
      {
         /* Build CSRSP based on the response */
         egEgtBuildCrtSesRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_MB_REQ:
      {
          egEgtBuildS4ModBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_MB_RSP:
      {
          egEgtBuildS4ModBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
          break;
      }
      /* eg012.201: added fix for ccpu00124570 */
      case EGT_GTPC_MSG_RAB_REQ: 
      {
          egEgtBuildS4RelAccBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
          break;
      }

      case EGT_GTPC_MSG_RAB_RSP: 
      {
          egEgtBuildS4RelAccBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
          break;
      }

      default:
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcEdmBuildEgS4Message(). Probable mismatch of the interface and the Message Type \n"));
      }
   } /* End of switch */

   RETVALUE(CMXTA_ERR_NONE);
}  /*  egAcEdmBuildEgS4Message */


/*
*
*       Fun:   egAcEgtBuildEgS5Message
*
*       Desc:  This function is used to Build EG S5 message 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_eguutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcEdmBuildEgS5Message
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8         msgType,
EgMsg   **egMsg,
U8       intfType,
Mem         *memInfo
)
#else
PUBLIC S16 egAcEdmBuildEgS5Message(tcCb,spCb,msgType,egMsg,intfType,memInfo)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
U8         msgType;
EgMsg   **egMsg;
U8       intfType;
Mem         *memInfo;
#endif /* ANSI */
{


   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEdmBuildEgS5Message);

   switch(msgType)
   {
      case EGT_GTPC_MSG_CS_REQ:
      {
         /* Build CSREQ */
         egEgtBuildCrtSesReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_CS_RSP:
      {
         /* Build CSRSP based on the response */
         egEgtBuildCrtSesRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_CB_REQ:
      {
          egEgtBuildCrtBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_CB_RSP:
      {
          egEgtBuildCrtBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_BR_CMND:
      {
          egEgtBuildBreResCmdMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_BR_FAIL_IND:
      {
          egEgtBuildBreResFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MB_REQ:
      {
          egEgtBuildModBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MB_RSP:
      {
          egEgtBuildModBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DS_REQ:
      {
          egEgtBuildDelSesReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DB_REQ:
      {
          egEgtBuildDelBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DD_NOTFN_FAIL_IND:
      {
          egEgtBuildDwLnkDatNotFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DS_RSP:
      {
          egEgtBuildDelSesRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DB_RSP:
      {
          egEgtBuildDelBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DWN_DATA_NOTFN:
      {
          egEgtBuildDwDatLnkNotMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DWN_DATA_NOTFN_ACK:
      {
          egEgtBuildDwDatLnkNotAckMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MB_CMND:
      {
          egEgtBuildModBreCmdMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBFAIL_IND:
      {
          egEgtBuildModBreFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_UB_REQ:
      {
          egEgtBuildUpdBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_UB_RSP:
      {
          egEgtBuildUpdBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DB_CMND:
      {
          egEgtBuildDeActvBreCmdMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_DB_FAIL_IN:
      {
         egEgtBuildDeActvBreFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      default:
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcEdmBuildEgS5Message(). Probable mismatch of the interface and the Message Type \n"));
      }
   } /* End of switch */

   RETVALUE(CMXTA_ERR_NONE);
}  /*  egAcEdmBuildEgS5Message */


/*
*
*       Fun:   egAcEgtBuildEgS10Message
*
*       Desc:  This function is used to Build EG S10 message 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_eguutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcEdmBuildEgS10Message
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8          msgType,
EgMsg       **egMsg,
U8          intfType,
Mem         *memInfo
)
#else
PUBLIC S16 egAcEdmBuildEgS10Message(tcCb, spCb, msgType, egMsg, intfType, memInfo)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
U8          msgType;
EgMsg       **egMsg;
U8          intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEdmBuildEgS10Message);

   switch(msgType)
   {
      case EGT_GTPC_MSG_FR_REQ:
      {
         egEgtBuildS10FwdrelReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_FR_RSP:
      {
         egEgtBuildS10FwdrelRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_CNTXT_REQ:
      {
         egEgtBuildS10CtxReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_CNTXT_RSP:
      {
         egEgtBuildS10CtxRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_CNTXT_ACK:
      {
         egEgtBuildS10CtxAckMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      default:
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcEdmBuildEgS10Message(). Probable mismatch of the interface and the Message Type \n"));
      }
   } /* End of switch */

   RETVALUE(CMXTA_ERR_NONE);
}  /*  egAcEdmBuildEgS10Message */


/*
*
*       Fun:   egAcEgtBuildEgS11Message
*
*       Desc:  This function is used to Build EG CX DX message 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_eguutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcEdmBuildEgS11Message
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8         msgType,
EgMsg   **egMsg,
U8          intfType,
Mem         *memInfo
)
#else
PUBLIC S16 egAcEdmBuildEgS11Message(tcCb,spCb,msgType,egMsg,intfType,memInfo)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
U8         msgType;
EgMsg   **egMsg;
U8          intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEdmBuildEgS11Message);

   switch(msgType)
   {
      case EGT_GTPC_MSG_CS_REQ:
      {
         /* Build CSREQ */
         egEgtBuildCrtSesReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_CS_RSP:
      {
         /* Build CSRSP based on the response */
         egEgtBuildCrtSesRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_CB_REQ:
      {
          egEgtBuildCrtBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_CB_RSP:
      {
          egEgtBuildCrtBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_BR_CMND:
      {
          egEgtBuildBreResCmdMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_BR_FAIL_IND:
      {
          egEgtBuildBreResFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MB_REQ:
      {
          egEgtBuildModBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MB_RSP:
      {
          egEgtBuildModBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DS_REQ:
      {
          egEgtBuildDelSesReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DB_REQ:
      {
          egEgtBuildDelBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DD_NOTFN_FAIL_IND:
      {
          egEgtBuildDwLnkDatNotFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DS_RSP:
      {
          egEgtBuildDelSesRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DB_RSP:
      {
          egEgtBuildDelBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DWN_DATA_NOTFN:
      {
          egEgtBuildDwDatLnkNotMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DWN_DATA_NOTFN_ACK:
      {
          egEgtBuildDwDatLnkNotAckMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MB_CMND:
      {
          egEgtBuildModBreCmdMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBFAIL_IND:
      {
          egEgtBuildModBreFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_UB_REQ:
      {
          egEgtBuildUpdBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_UB_RSP:
      {
          egEgtBuildUpdBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DB_CMND:
      {
          egEgtBuildDeActvBreCmdMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_DB_FAIL_IN:
      {
         egEgtBuildDeActvBreFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_SSPND_NOTFN:
      {
         egEgtBuildS11SuspendNotMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_SSPND_ACK:
      {
         egEgtBuildS11SuspendAckMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_RSME_NOTFN:
      {
         egEgtBuildS11ResumeNotMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_RSME_ACK:
      {
         egEgtBuildS11ResumeAckMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_CF_TUNN_REQ:
      {
         egEgtBuildS11CrtFwdTunReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_CF_TUNN_RSP:
      {
         egEgtBuildS11CrtFwdTunRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      default:
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcEdmBuildEgS11Message(). Probable mismatch of the interface and the Message Type \n"));
      }
   } /* End of switch */

   RETVALUE(CMXTA_ERR_NONE);
}  /*  egAcEdmBuildEgS11Message */


/*
*
*       Fun:   egAcEgtBuildEgS16Message
*
*       Desc:  This function is used to Build EG S16 message 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_eguutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcEdmBuildEgS16Message
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8          msgType,
EgMsg       **egMsg,
U8          intfType,
Mem         *memInfo
)
#else
PUBLIC S16 egAcEdmBuildEgS16Message(tcCb, spCb, msgType, egMsg, intfType, memInfo)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
U8          msgType;
EgMsg       **egMsg;
U8          intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEdmBuildEgS16Message);

   switch(msgType)
   {
      case EGT_GTPC_MSG_FR_REQ:
      {
         egEgtBuildS16FwdRelReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_FR_RSP:
      {
         egEgtBuildS16FwdRelRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_ID_REQ:
      {
         egEgtBuildS16IdReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      case EGT_GTPC_MSG_ID_RSP:
      {
         egEgtBuildS16IdRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }

      default:
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcEdmBuildEgS16Message(). Probable mismatch of the interface and the Message Type \n"));
      }
   } /* End of switch */

   RETVALUE(CMXTA_ERR_NONE);
}  /*  egAcEdmBuildEgS16Message */

#ifdef EG_REL_930
/*
*
*       Fun:   egAcEgtBuildEgSMMessage
*
*       Desc:  This function is used to Build EG SM message 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_eguutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcEdmBuildEgSMMessage
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8          msgType,
EgMsg       **egMsg,
U8          intfType,
Mem         *memInfo
)
#else
PUBLIC S16 egAcEdmBuildEgSMMessage(tcCb, spCb, msgType, egMsg, intfType, memInfo)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
U8          msgType;
EgMsg       **egMsg;
U8          intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   TRC2(egAcEdmBuildEgSMMessage);

   switch(msgType)
   {
      case EGT_GTPC_MSG_MBMS_SESS_START_REQ:
      {
         egEgtBuildSMSesStartReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBMS_SESS_START_RSP:
      {
         egEgtBuildSMSesStartRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBMS_SESS_UPD_REQ:
      {
         egEgtBuildSMSesUpdReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBMS_SESS_UPD_RSP:
      {
         egEgtBuildSMSesUpdRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBMS_SESS_STOP_REQ:
      {
         egEgtBuildSMSesStopReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBMS_SESS_STOP_RSP:
      {
         egEgtBuildSMSesStopRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      default:
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcEdmBuildEgSMMessage(). Probable mismatch of the interface and the Message Type \n"));
      }
   } /* End of switch */

   RETVALUE(CMXTA_ERR_NONE);
}  /*  egAcEdmBuildEgSMMessage */
/*
*
*       Fun:   egAcEgtBuildEgSNMessage
*
*       Desc:  This function is used to Build EG SN message 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_eguutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcEdmBuildEgSNMessage
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8          msgType,
EgMsg       **egMsg,
U8          intfType,
Mem         *memInfo
)
#else
PUBLIC S16 egAcEdmBuildEgSNMessage(tcCb, spCb, msgType, egMsg, intfType, memInfo)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
U8          msgType;
EgMsg       **egMsg;
U8          intfType;
Mem         *memInfo;
#endif /* ANSI */
{
   TRC2(egAcEdmBuildEgSNMessage);

   switch(msgType)
   {
      case EGT_GTPC_MSG_MBMS_SESS_START_REQ:
      {
         egEgtBuildSNSesStartReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBMS_SESS_START_RSP:
      {
         egEgtBuildSNSesStartRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBMS_SESS_UPD_REQ:
      {
         egEgtBuildSNSesUpdReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBMS_SESS_UPD_RSP:
      {
         egEgtBuildSNSesUpdRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBMS_SESS_STOP_REQ:
      {
         egEgtBuildSNSesStopReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBMS_SESS_STOP_RSP:
      {
         egEgtBuildSNSesStopRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      default:
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcEdmBuildEgSNMessage(). Probable mismatch of the interface and the Message Type \n"));
      }
   } /* End of switch */

   RETVALUE(CMXTA_ERR_NONE);
}  /*  egAcEdmBuildEgSNMessage */

#endif /* EG_REL_930 */


/*
*
*       Fun:   egAcEdmBuildEgMsg
*
*       Desc:  This function is used to Build EG message 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_egtutl.c
*
*/

#ifdef ANSI
PUBLIC S16 egAcEdmBuildEgMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
U8                msgType,
EgMsg **egMsg
)
#else
PUBLIC S16 egAcEdmBuildEgMsg(tcCb,spCb,msgType,egMsg)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
U8               msgType;
EgMsg **egMsg;
#endif /* ANSI */
{
   Mem    memInfo;
   U8     intfType= EGT_GTP_INT_S11;
   S16    ret = 0;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEdmBuildEgMsg)

   cmMemset((U8*)&memInfo, 0 , sizeof(Mem));

   /* Get the value of the interface for  which the eGTP message need to 
    to be built */
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_ENUM_U8,(Txt  *)"intfType",&intfType);
   if(ret == CMXTA_ERR_NO_VALUE)
   {
       CMXTA_DBG_ERR((_cmxtap,"egAcEdmBuildEgMsg(): The value of interface is expected from the xml file\n"));
       RETVALUE(CMXTA_ERR_INT); 
   }

   memInfo.pool   = DFLT_REGION;
   memInfo.region = DFLT_POOL;

   switch(intfType)
   {
      case EGT_GTP_INT_S11:
      {
            /* Build S11 messages  */
            ret = egAcEdmBuildEgS11Message(tcCb,spCb,msgType,egMsg,intfType,&memInfo);
            if(ret != CMXTA_ERR_NONE)
            {
               RETVALUE(ret);
            }
            break;
      }
      case EGT_GTP_INT_S5_S8:
      {
            /* Build S5/S8 messages  */
            ret = egAcEdmBuildEgS5Message(tcCb,spCb,msgType,egMsg,intfType,&memInfo);
            if(ret != CMXTA_ERR_NONE)
            {
               RETVALUE(ret);
            }
            break;
      }
      case EGT_GTP_INT_S3:
      {
            /* Build S3 interface messages  */
            ret = egAcEdmBuildEgS3Message(tcCb,spCb,msgType,egMsg,intfType,&memInfo);
            if(ret != CMXTA_ERR_NONE)
            {
               RETVALUE(ret);
            }
            break;
      }
      case EGT_GTP_INT_S4:
      {
            /* Build S4 interface messages  */
            ret = egAcEdmBuildEgS4Message(tcCb,spCb,msgType,egMsg,intfType,&memInfo);
            if(ret != CMXTA_ERR_NONE)
            {
               RETVALUE(ret);
            }
            break;
      }
      case EGT_GTP_INT_S10:
      {
            /* Build S10 interface messages  */
            ret = egAcEdmBuildEgS10Message(tcCb,spCb,msgType,egMsg,intfType,&memInfo);
            if(ret != CMXTA_ERR_NONE)
            {
               RETVALUE(ret);
            }
            break;
      }
      case EGT_GTP_INT_S16:
      {
            /* Build S16 interface messages  */
            ret = egAcEdmBuildEgS16Message(tcCb,spCb,msgType,egMsg,intfType,&memInfo);
            if(ret != CMXTA_ERR_NONE)
            {
               RETVALUE(ret);
            }
            break;
      }
#ifdef EG_REL_930
      case EGT_GTP_INT_SM:
      {
            /* Build SM interface messages  */
            ret = egAcEdmBuildEgSMMessage(tcCb,spCb,msgType,egMsg,intfType,&memInfo);
            if(ret != CMXTA_ERR_NONE)
            {
               RETVALUE(ret);
            }
            break;
      }
      case EGT_GTP_INT_SN:
      {
            /* Build SN interface messages  */
            ret = egAcEdmBuildEgSNMessage(tcCb,spCb,msgType,egMsg,intfType,&memInfo);
            if(ret != CMXTA_ERR_NONE)
            {
               RETVALUE(ret);
            }
            break;
      }
/*****************************
 * eg009.201 - Added for S2B *
 *****************************/
#ifdef EG_S2B_SUPP
      case EGT_GTP_INT_S2B:
      {
         /* Build S2B interface messages  */
         ret = egAcEdmBuildEgS2aS2bMessage(tcCb,spCb,msgType,egMsg,intfType,&memInfo);
         if(ret != CMXTA_ERR_NONE)
         {
            RETVALUE(ret);
         }
         break;
      }
#endif/*EG_S2B_SUPP*/
/*****************************
 * eg009.201 - Added for S2A *
 *****************************/
#ifdef EG_S2A_SUPP
      case EGT_GTP_INT_S2A:
      {
         /* Build S2A interface messages  */
         ret = egAcEdmBuildEgS2aS2bMessage(tcCb,spCb,msgType,egMsg,intfType,&memInfo);
         if(ret != CMXTA_ERR_NONE)
         {
            RETVALUE(ret);
         }
         break;
      }
#endif/*EG_S2A_SUPP */


#endif /* EG_REL_930 */
      default:
      {
         /* For negative scenarios, this isused fill the message for the invalid interfac msg */
 
         if ( msgType == EGT_GTPC_MSG_ECHO_REQ )
         {
            egEgtBuildEchoMsgReq(tcCb,spCb,egMsg,&memInfo);
         }
         else if ( EGT_GTPC_MSG_ECHO_RSP )
         {
            egEgtBuildEchoMsgRsp(tcCb,spCb,egMsg,&memInfo);
         }

      }
   }/* End of Switch of interface */

  RETVALUE(CMXTA_ERR_NONE);
   
} /*  egAcEdmBuildEgMsg  */


/************************************************************************
*                   CONFIG SECTION IN XTA FOR IE AND MSG                *
************************************************************************/


/*
*
*   Func  : egGetMsgFrmGMDict
*
*   Desc  : This function retrieves the GM Properties with in the
            EGTP message
*
*    Return: None
*
*  File  : egac_tst.c
*
*/

#ifdef ANSI
PUBLIC LegIeEntry* egGetIeFrmIeDict
(
U8         ieType           /* Ie Type to get the entry */
)
#else
PUBLIC LegIeEntry* egGetIeFrmIeDict(ieType)
U8         ieType;           /* Ie Type to get the entry */
#endif
{
    U16         idx = 0; /* Index to ge the ie position */

   /*-- eg003.201 : TRC changes from eg006.102--*/
    EG_TRC2(egGetIeFrmIeDict)

    /* Get the position index of the ieType in the dict */
    idx = egAccCb.selfIeCfg.posIdx[ieType];
    
    /* If the position is present then return the address of it */
    if(idx != 0)
    {
       return(&egAccCb.selfIeCfg.ieEntry[idx-1]);
    }
    else
    {
       return(NULLP);
    }  /*end of else statement  */

} /* egGetIeFrmIeDict  */


/*
*
*      Fun  : populateGmConfigInTA 
*
*      Desc : This function populatest the DM configuration in the global control block
*
*      Ret  : Void
*
*      Notes: None
*
*      File : populateGmConfigInTA.c
*
*/
 
#ifdef ANSI
PUBLIC S16 populateGmConfigInTA 
(
CmXtaTCCb *tcCb,
CmXtaSpCb *spCb,
U8     intfType,
U8     diffPeerCfg
)
#else
PUBLIC S16 populateGmConfigInTA(tcCb, spCb, intfType, diffPeerCfg)
CmXtaTCCb *tcCb;
CmXtaSpCb *spCb;
U8     intfType;
U8     diffPeerCfg;
#endif
{
   U8    idx = 0;
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(populateGmConfigInTA)


   switch(intfType)
   {
      case EGT_GTP_INT_S3:
      {
         /**********************************************
         *   Copy the GM Config parameters in XTA      *
         *   Check if the self and peer config is done *
         **********************************************/
         /* Find for the idx of the appId in the Test Architeture  */
         for(idx=0;idx < MAX_APP_INTERFACES;idx++)
         {
            if((egAccCb.intfTypeMap[idx] == intfType)  && 
               ((!diffPeerCfg && egAccCb.selfGmMsgCfgDone[idx]) ||
               (diffPeerCfg && egAccCb.peerGmMsgCfgDone[idx])))
            {
               break;
            }
            else
            {
               /*****************************************************
                *  eg007.201:Updated  map only if its not configured*
                *****************************************************/
               if ( egAccCb.intfTypeMap[idx] != EGT_GTP_INT_UNKNWN)
               {
                  continue;
               }
               egAccCb.intfTypeMap[idx] = intfType;
      
               if(!diffPeerCfg)
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.selfGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);
      
                  }
                  cmMemset((U8*)egAccCb.selfGmMsgCfg[idx].gmEntry,
                                 EG_ZERO, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry)));
                  egMakes3GmDict(egAccCb.selfGmMsgCfg[idx].gmEntry, &egAccCb.selfGmMsgCfg[idx].nmbMsg);
                  egAccCb.selfGmMsgCfgDone[idx] = TRUE;
               }
               else
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.peerGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);

                  }
                  egMakes3GmDict(egAccCb.peerGmMsgCfg[idx].gmEntry, &egAccCb.peerGmMsgCfg[idx].nmbMsg);
                  egAccCb.peerGmMsgCfgDone[idx] = TRUE;
               }
               break;
            }
         } /* end of for loop  */
      } /* End of S3 interface */
      case EGT_GTP_INT_S4:
      {
         /**********************************************
         *   Copy the GM Config parameters in XTA      *
         *   Check if the self and peer config is done *
         **********************************************/
         /* Find for the idx of the appId in the Test Architeture  */
         for(idx=0;idx < MAX_APP_INTERFACES;idx++)
         {
            if((egAccCb.intfTypeMap[idx] == intfType)  && 
               ((!diffPeerCfg && egAccCb.selfGmMsgCfgDone[idx]) ||
               (diffPeerCfg && egAccCb.peerGmMsgCfgDone[idx])))
            {
               break;
            }
            else
            {
               /*****************************************************
                *  eg007.201:Updated  map only if its not configured*
                *****************************************************/
               if ( egAccCb.intfTypeMap[idx] != EGT_GTP_INT_UNKNWN)
               {
                  continue;
               }
               egAccCb.intfTypeMap[idx] = intfType;
      
               if(!diffPeerCfg)
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.selfGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);
      
                  }
                  cmMemset((U8*)egAccCb.selfGmMsgCfg[idx].gmEntry,
                                 EG_ZERO, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry)));
                  egMakes4GmDict(egAccCb.selfGmMsgCfg[idx].gmEntry, &egAccCb.selfGmMsgCfg[idx].nmbMsg);
                  egAccCb.selfGmMsgCfgDone[idx] = TRUE;
               }
               else
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.peerGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);

                  }
                  egMakes4GmDict(egAccCb.peerGmMsgCfg[idx].gmEntry, &egAccCb.peerGmMsgCfg[idx].nmbMsg);
                  egAccCb.peerGmMsgCfgDone[idx] = TRUE;
               }
               break;
            }
         } /* end of for loop  */
      } /* End of S4 interface */
      case EGT_GTP_INT_S5_S8:
      {
         /**********************************************
         *   Copy the GM Config parameters in XTA      *
         *   Check if the self and peer config is done *
         **********************************************/
         /* Find for the idx of the appId in the Test Architeture  */
         for(idx=0;idx < MAX_APP_INTERFACES;idx++)
         {
            if((egAccCb.intfTypeMap[idx] == intfType)  && 
               ((!diffPeerCfg && egAccCb.selfGmMsgCfgDone[idx]) ||
               (diffPeerCfg && egAccCb.peerGmMsgCfgDone[idx])))
            {
               break;
            }
            else
            {
               /*****************************************************
                *  eg007.201:Updated  map only if its not configured*
                *****************************************************/
               if ( egAccCb.intfTypeMap[idx] != EGT_GTP_INT_UNKNWN)
               {
                  continue;
               }
               egAccCb.intfTypeMap[idx] = intfType;
      
               if(!diffPeerCfg)
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.selfGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);
      
                  }
                  cmMemset((U8*)egAccCb.selfGmMsgCfg[idx].gmEntry,
                                 EG_ZERO, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry)));
                  egMakes5GmDict(egAccCb.selfGmMsgCfg[idx].gmEntry, &egAccCb.selfGmMsgCfg[idx].nmbMsg);
                  egAccCb.selfGmMsgCfgDone[idx] = TRUE;
               }
               else
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.peerGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);

                  }
                  egMakes5GmDict(egAccCb.peerGmMsgCfg[idx].gmEntry, &egAccCb.peerGmMsgCfg[idx].nmbMsg);
                  egAccCb.peerGmMsgCfgDone[idx] = TRUE;
               }
               break;
            }
         } /* end of for loop  */
      } /* End of S5 interface */
      case EGT_GTP_INT_S10:
      {
         /**********************************************
         *   Copy the GM Config parameters in XTA      *
         *   Check if the self and peer config is done *
         **********************************************/
         /* Find for the idx of the appId in the Test Architeture  */
         for(idx=0;idx < MAX_APP_INTERFACES;idx++)
         {
            if((egAccCb.intfTypeMap[idx] == intfType)  && 
               ((!diffPeerCfg && egAccCb.selfGmMsgCfgDone[idx]) ||
               (diffPeerCfg && egAccCb.peerGmMsgCfgDone[idx])))
            {
               break;
            }
            else
            {
               /*****************************************************
                *  eg007.201:Updated  map only if its not configured*
                *****************************************************/
               if ( egAccCb.intfTypeMap[idx] != EGT_GTP_INT_UNKNWN)
               {
                  continue;
               }
               egAccCb.intfTypeMap[idx] = intfType;
      
               if(!diffPeerCfg)
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.selfGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);
      
                  }
                  cmMemset((U8*)egAccCb.selfGmMsgCfg[idx].gmEntry,
                                 EG_ZERO, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry)));
                  egMakes10GmDict(egAccCb.selfGmMsgCfg[idx].gmEntry, &egAccCb.selfGmMsgCfg[idx].nmbMsg);
                  egAccCb.selfGmMsgCfgDone[idx] = TRUE;
               }
               else
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.peerGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);

                  }
                  egMakes10GmDict(egAccCb.peerGmMsgCfg[idx].gmEntry, &egAccCb.peerGmMsgCfg[idx].nmbMsg);
                  egAccCb.peerGmMsgCfgDone[idx] = TRUE;
               }
               break;
            }
         } /* end of for loop  */
      } /* End of S10 interface */
      case EGT_GTP_INT_S11:
      {
         /**********************************************
         *   Copy the GM Config parameters in XTA      *
         *   Check if the self and peer config is done *
         **********************************************/
         /* Find for the idx of the appId in the Test Architeture  */
         for(idx=0;idx < MAX_APP_INTERFACES;idx++)
         {
            if((egAccCb.intfTypeMap[idx] == intfType)  && 
               ((!diffPeerCfg && egAccCb.selfGmMsgCfgDone[idx]) ||
               (diffPeerCfg && egAccCb.peerGmMsgCfgDone[idx])))
            {
               break;
            }
            else
            {
               /*****************************************************
                *  eg007.201:Updated  map only if its not configured*
                *****************************************************/
               if ( egAccCb.intfTypeMap[idx] != EGT_GTP_INT_UNKNWN)
               {
                  continue;
               }
               egAccCb.intfTypeMap[idx] = intfType;
      
               if(!diffPeerCfg)
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.selfGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);
      
                  }
                  cmMemset((U8*)egAccCb.selfGmMsgCfg[idx].gmEntry,
                                 EG_ZERO, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry)));
                  egMakes11GmDict(egAccCb.selfGmMsgCfg[idx].gmEntry, &egAccCb.selfGmMsgCfg[idx].nmbMsg);
                  egAccCb.selfGmMsgCfgDone[idx] = TRUE;
               }
               else
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.peerGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);

                  }
                  egMakes11GmDict(egAccCb.peerGmMsgCfg[idx].gmEntry, &egAccCb.peerGmMsgCfg[idx].nmbMsg);
                  egAccCb.peerGmMsgCfgDone[idx] = TRUE;
               }
               break;
            }
         } /* end of for loop  */
      } /* End of S11 interface */
      case EGT_GTP_INT_S16:
      {
         /**********************************************
         *   Copy the GM Config parameters in XTA      *
         *   Check if the self and peer config is done *
         **********************************************/
         /* Find for the idx of the appId in the Test Architeture  */
         for(idx=0;idx < MAX_APP_INTERFACES;idx++)
         {
            if((egAccCb.intfTypeMap[idx] == intfType)  && 
               ((!diffPeerCfg && egAccCb.selfGmMsgCfgDone[idx]) ||
               (diffPeerCfg && egAccCb.peerGmMsgCfgDone[idx])))
            {
               break;
            }
            else
            {
               /*****************************************************
                *  eg007.201:Updated  map only if its not configured*
                *****************************************************/
               if ( egAccCb.intfTypeMap[idx] != EGT_GTP_INT_UNKNWN)
               {
                  continue;
               }
               egAccCb.intfTypeMap[idx] = intfType;
      
               if(!diffPeerCfg)
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.selfGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);
      
                  }
                  cmMemset((U8*)egAccCb.selfGmMsgCfg[idx].gmEntry,
                                 EG_ZERO, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry)));
                  egMakes16GmDict(egAccCb.selfGmMsgCfg[idx].gmEntry, &egAccCb.selfGmMsgCfg[idx].nmbMsg);
                  egAccCb.selfGmMsgCfgDone[idx] = TRUE;
               }
               else
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.peerGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);

                  }
                  egMakes16GmDict(egAccCb.peerGmMsgCfg[idx].gmEntry, &egAccCb.peerGmMsgCfg[idx].nmbMsg);
                  egAccCb.peerGmMsgCfgDone[idx] = TRUE;
               }
               break;
            }
         } /* end of for loop  */
      } /* End of S16 interface */
#ifdef EG_REL_930

      case EGT_GTP_INT_SM:
      {
         /**********************************************
         *   Copy the GM Config parameters in XTA      *
         *   Check if the self and peer config is done *
         **********************************************/
         /* Find for the idx of the appId in the Test Architeture  */
         for(idx=0;idx < MAX_APP_INTERFACES;idx++)
         {
            if((egAccCb.intfTypeMap[idx] == intfType)  && 
               ((!diffPeerCfg && egAccCb.selfGmMsgCfgDone[idx]) ||
               (diffPeerCfg && egAccCb.peerGmMsgCfgDone[idx])))
            {
               break;
            }
            else
            {
               /*****************************************************
                *  eg007.201:Updated  map only if its not configured*
                *****************************************************/
               if ( egAccCb.intfTypeMap[idx] != EGT_GTP_INT_UNKNWN)
               {
                  continue;
               }
               egAccCb.intfTypeMap[idx] = intfType;
      
               if(!diffPeerCfg)
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.selfGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);
      
                  }
                  cmMemset((U8*)egAccCb.selfGmMsgCfg[idx].gmEntry,
                                 EG_ZERO, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry)));
                  egMakesmGmDict(egAccCb.selfGmMsgCfg[idx].gmEntry, &egAccCb.selfGmMsgCfg[idx].nmbMsg);
                  egAccCb.selfGmMsgCfgDone[idx] = TRUE;
               }
               else
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.peerGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);

                  }
                  egMakesmGmDict(egAccCb.peerGmMsgCfg[idx].gmEntry, &egAccCb.peerGmMsgCfg[idx].nmbMsg);
                  egAccCb.peerGmMsgCfgDone[idx] = TRUE;
               }
               break;
            }
         } /* end of for loop  */
      } /* End of SM interface */
	   case EGT_GTP_INT_SN:
      {
         /**********************************************
         *   Copy the GM Config parameters in XTA      *
         *   Check if the self and peer config is done *
         **********************************************/
         /* Find for the idx of the appId in the Test Architeture  */
         for(idx=0;idx < MAX_APP_INTERFACES;idx++)
         {
            if((egAccCb.intfTypeMap[idx] == intfType)  && 
               ((!diffPeerCfg && egAccCb.selfGmMsgCfgDone[idx]) ||
               (diffPeerCfg && egAccCb.peerGmMsgCfgDone[idx])))
            {
               break;
            }
            else
            {
               /*****************************************************
                *  eg007.201:Updated  map only if its not configured*
                *****************************************************/
               if ( egAccCb.intfTypeMap[idx] != EGT_GTP_INT_UNKNWN)
               {
                  continue;
               }
               egAccCb.intfTypeMap[idx] = intfType;
      
               if(!diffPeerCfg)
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.selfGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);
      
                  }
                  cmMemset((U8*)egAccCb.selfGmMsgCfg[idx].gmEntry,
                                 EG_ZERO, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry)));
                  egMakesnGmDict(egAccCb.selfGmMsgCfg[idx].gmEntry, &egAccCb.selfGmMsgCfg[idx].nmbMsg);
                  egAccCb.selfGmMsgCfgDone[idx] = TRUE;
               }
               else
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.peerGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                      CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                      RETVALUE(CMXTA_ERR_INT);

                  }
                  egMakesnGmDict(egAccCb.peerGmMsgCfg[idx].gmEntry, &egAccCb.peerGmMsgCfg[idx].nmbMsg);
                  egAccCb.peerGmMsgCfgDone[idx] = TRUE;
               }
               break;
            }
         } /* end of for loop  */
      } /* End of SM interface */
#endif /* EG_REL_930 */
/*****************************
 * eg009.201 - Added for S2B *
 *****************************/
#ifdef EG_S2B_SUPP
      case EGT_GTP_INT_S2B:
      {
         /**********************************************
          *   Copy the GM Config parameters in XTA      *
          *   Check if the self and peer config is done *
          **********************************************/
         /* Find for the idx of the appId in the Test Architeture  */
         for(idx=0;idx < MAX_APP_INTERFACES;idx++)
         {
            if((egAccCb.intfTypeMap[idx] == intfType)  && 
                  ((!diffPeerCfg && egAccCb.selfGmMsgCfgDone[idx]) ||
                   (diffPeerCfg && egAccCb.peerGmMsgCfgDone[idx])))
            {
               break;
            }
            else
            {
               if ( egAccCb.intfTypeMap[idx] != EGT_GTP_INT_UNKNWN)
               {
                  continue;
               }

               egAccCb.intfTypeMap[idx] = intfType;

               if(!diffPeerCfg)
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.selfGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                     CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                     RETVALUE(CMXTA_ERR_INT);

                  }
                  cmMemset((U8*)egAccCb.selfGmMsgCfg[idx].gmEntry,
                        EG_ZERO, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry)));
                  egMakes2bGmDict(egAccCb.selfGmMsgCfg[idx].gmEntry, &egAccCb.selfGmMsgCfg[idx].nmbMsg);
                  egAccCb.selfGmMsgCfgDone[idx] = TRUE;
               }
               else
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.peerGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                     CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                     RETVALUE(CMXTA_ERR_INT);

                  }
                  egMakes2bGmDict(egAccCb.peerGmMsgCfg[idx].gmEntry, &egAccCb.peerGmMsgCfg[idx].nmbMsg);
                  egAccCb.peerGmMsgCfgDone[idx] = TRUE;
               }
               break;
            }
         } /* end of for loop  */
      } /* End of S2B interface */ 
#endif/*EG_S2B_SUPP*/

/*****************************
 * eg009.201 - Added for S2A *
 *****************************/
#ifdef EG_S2A_SUPP
      case EGT_GTP_INT_S2A:
      {
         /**********************************************
          *   Copy the GM Config parameters in XTA      *
          *   Check if the self and peer config is done *
          **********************************************/
         /* Find for the idx of the appId in the Test Architeture  */
         for(idx=0;idx < MAX_APP_INTERFACES;idx++)
         {
            if((egAccCb.intfTypeMap[idx] == intfType)  && 
                  ((!diffPeerCfg && egAccCb.selfGmMsgCfgDone[idx]) ||
                   (diffPeerCfg && egAccCb.peerGmMsgCfgDone[idx])))
            {
               break;
            }
            else
            {
               if ( egAccCb.intfTypeMap[idx] != EGT_GTP_INT_UNKNWN)
               {
                  continue;
               }

               egAccCb.intfTypeMap[idx] = intfType;

               if(!diffPeerCfg)
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.selfGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                     CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                     RETVALUE(CMXTA_ERR_INT);

                  }
                  cmMemset((U8*)egAccCb.selfGmMsgCfg[idx].gmEntry,
                        EG_ZERO, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry)));
                  egMakes2aGmDict(egAccCb.selfGmMsgCfg[idx].gmEntry, &egAccCb.selfGmMsgCfg[idx].nmbMsg);
                  egAccCb.selfGmMsgCfgDone[idx] = TRUE;
               }
               else
               {
                  if( (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data** )&egAccCb.peerGmMsgCfg[idx].gmEntry, (LEG_MAX_NUM_OF_MSGS * sizeof(LegMsgEntry))) != ROK))
                  {
                     CMXTA_DBG_ERR((_cmxtap,"unable to allocate memory for the msg's\n"));
                     RETVALUE(CMXTA_ERR_INT);

                  }
                  egMakes2aGmDict(egAccCb.peerGmMsgCfg[idx].gmEntry, &egAccCb.peerGmMsgCfg[idx].nmbMsg);
                  egAccCb.peerGmMsgCfgDone[idx] = TRUE;
               }
               break;
            }
         } /* end of for loop  */
      } /* End of S2A interface */ 
#endif/*EG_S2A_SUPP*/
   }
   RETVALUE(ROK);
} /* populateGmConfigInTA  */




/*
*
*      Fun  : populateIeConfigInTA 
*
*      Desc : This function populatest the AVP configuration in the global control block
*
*      Ret  : Void
*
*      Notes: None
*
*      File : populateIeConfigInTA.c
*
*/
 
#ifdef ANSI
PUBLIC S16 populateIeConfigInTA 
(
CmXtaTCCb *tcCb,
CmXtaSpCb *spCb,
U8     diffPeerCfg
)
#else
PUBLIC S16 populateIeConfigInTA(tcCb, spCb, diffPeerCfg)
CmXtaTCCb *tcCb;
CmXtaSpCb *spCb;
U8     diffPeerCfg;
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(populateIeConfigInTA)

   /**********************************************
   *   Copy the IE Config parameters in XTA      *
   *   Check if the self and peer config is done *
   **********************************************/
   if ( (!diffPeerCfg && egAccCb.selfIeCfgDone) ||
        (diffPeerCfg && egAccCb.peerIeCfgDone))
   {
      RETVALUE(ROK);
   }
   else
   {
      if(!diffPeerCfg)
      {
         cmMemset((U8 *)egAccCb.selfIeCfg.posIdx, 0, LEG_MAX_IES);
         cmMemset((U8 *)egAccCb.selfIeCfg.ieEntry, 0, LEG_MAX_IES_ALL_MSGS * sizeof(LegIeEntry));
         egMakeIeDict( egAccCb.selfIeCfg.ieEntry,  &egAccCb.selfIeCfg.nmbIe, egAccCb.selfIeCfg.posIdx);
         egAccCb.selfIeCfgDone = TRUE;
      }
      else
      {
         cmMemset((U8 *)egAccCb.peerIeCfg.posIdx, 0, LEG_MAX_IES);
         cmMemset((U8 *)egAccCb.peerIeCfg.ieEntry, 0, LEG_MAX_IES_ALL_MSGS * sizeof(LegIeEntry));
         egMakeIeDict( egAccCb.peerIeCfg.ieEntry,  &egAccCb.peerIeCfg.nmbIe, egAccCb.peerIeCfg.posIdx);
         egAccCb.peerIeCfgDone = TRUE;

      }
   }  /*end of else statement  */

   RETVALUE(ROK);
} /* populateIeConfigInTA  */

/*
*
*   Func  : egGetMsgFrmGMDict
*
*   Desc  : This function retrieves the GM Properties with in the
            EGTP message
*
*    Return: None
*
*  File  : egac_tst.c
*
*/

#ifdef ANSI
PUBLIC LegMsgEntry* egGetMsgFrmGmDict
(
U8         msgType,           /* Message Type to get the entry */
U8        intfType          /* Interface type the msg belogs */
)
#else
PUBLIC LegMsgEntry* egGetMsgFrmGmDict(msgType, intfType)
U8         msgType;          /* Message Type to get the entry */
U8        intfType;          /* Interface type the msg belogs */
#endif
{
    U8         idx = 0;
    U8        cnt = 0;
    U8        gmMsgIndex = 0;

   /*-- eg003.201 : TRC changes from eg006.102--*/
    EG_TRC2(egGetMsgFrmGMDict)

    /* Find for the idx of the appId in the Test Architeture  */
    for(idx=0;idx < MAX_APP_INTERFACES;idx++)
    {
       if(egAccCb.intfTypeMap[idx] == intfType)
       {
          break;
       }
       else if(egAccCb.intfTypeMap[idx] == 0)
       {
          CMXTA_DBG_ERR((_cmxtap,"egGetMsgFrmGMDict() Unable to find the intf population in the Test Architecture\n"));
          return(NULLP);
        } /* end of if statement */
        else
        {
           continue;
        }

    } /* end of for loop  */
    if ( idx == MAX_APP_INTERFACES) 
    {
       return NULLP;
    }
    /* Search for the presence of the msgEntry in the dictionary of the intf present at idx  */
    for(cnt = 0; cnt < egAccCb.selfGmMsgCfg[idx].nmbMsg; cnt++)
    {
       if(msgType == egAccCb.selfGmMsgCfg[idx].gmEntry[cnt].msgType )
       {
             gmMsgIndex  = cnt;
             break;
       } /* end of if statement  */
    } /* end of for loop   */

    /* If the GmEntry is present then return the address of it */
    if(cnt != egAccCb.selfGmMsgCfg[idx].nmbMsg)
    {
       return(&egAccCb.selfGmMsgCfg[idx].gmEntry[gmMsgIndex]);
    }
    else
    {
       return(NULLP);
    }  /*end of else statement  */

} /* egGetMsgFrmGMDict  */



/*
 *
 *       Fun:   egAcUtlDEdmValidateMsg
 *
 *       Desc:  Decode the Edmp Message and validate
 *
 *       Ret:   ROK/RFAILED
 *
 *       Notes: This utility function
 *              validates the Edmp message at the Dummy 
 *
 *       File: xx_egtutl.c 
 *
 */

#ifdef ANSI
PUBLIC S16 egAcUtlDEdmValidateMsg
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
Buffer     *mBuf
)
#else
PUBLIC S16 egAcUtlDEdmValidateMsg (tcCb, spCb, mBuf)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
Buffer     *mBuf;
#endif
{
   EgMsg     *egMsg = NULLP;
   U8           xmlMsgType = 0;
   U8           invalidCommandType = FALSE;
   Mem           memInfo;
   EgIeLevelInfo ieLvlInfo;
   EgAcTCCb     *egTcCb = NULLP;  
   S16            ret = 0;
  
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcUtlDEdmValidateMsg);
 
   cmMemset((U8*)&memInfo, 0 , sizeof(Mem));
   cmMemset((U8*)&ieLvlInfo, 0 , sizeof(EgIeLevelInfo));
 
   egTcCb = (EgAcTCCb *)tcCb->tcCb;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap,"egAcUtlDEdmValidateMsg(), tcId (%ld)\n",tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap,"egAcUtlDEdmValidateMsg(), tcId (%d)\n",tcCb->tcId));
#endif
   memInfo.region = DFLT_REGION;
   memInfo.pool   = DFLT_POOL;
   /* Decode the Edmp Message  */
 
   if(EgUtilAllocGmMsg(&egMsg,&memInfo)!= ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,"egAcUtlDEdmValidateMsg() Unable to allocate the message \n"));
      RETVALUE(CMXTA_ERR_INT);
   } 
  
   if( egAcDecEgMsg(egMsg,mBuf) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,"egAcUtlDEdmValidateMsg() Unable to Decode the message \n"));
      EgUtilDeAllocGmMsg(&egMsg);
      RETVALUE(CMXTA_ERR_INT);
   } 

   if(egMsg)
   {
#ifdef LEG_FILE_LOG
   EgUtilGmDump(egMsg,stdout,&position);
#else
   EgUtilGmDump(egMsg);
#endif /* end of if LEG_FILE_LOG */

      /* Validate the message type  */
      ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_ENUM_U8,(Txt  *)"msgType",&xmlMsgType);
      if(ret != CMXTA_ERR_NO_VALUE)
      {
         cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_ENUM_U8,(Txt  *)"invalidCommandType",&invalidCommandType);
         if(invalidCommandType == FALSE)
         {
            if(egMsg->msgHdr.msgType != xmlMsgType)
            {
               CMXTA_DBG_ERR((_cmxtap,"egAcUtlDEdmValidateMsg(): Expected Command code[%d] Received Command code[%d]\n",xmlMsgType,egMsg->msgHdr.msgType));
               RETVALUE(CMXTA_ERR_INT);
            } /* end of validation  */
         } /* end of if statemnt   */
      }
   } 
   else
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   EgUtilDeAllocGmMsg(&egMsg);
   RETVALUE(CMXTA_ERR_NONE);
} /*-- egAcUtlDEdmValidateMsg --*/


/*
 *
 *       Fun:   egAcUtlDEdmBuildMsg
 *
 *       Desc:  Build the Edmp Message
 *
 *       Ret:   ROK/RFAILED
 *
 *       Notes: This utility function builds the Edmp Message
 *
 *       File: xx_egtutl.c 
 *
 */

#ifdef ANSI
PUBLIC S16 egAcUtlDEdmBuildMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsg      **egMsg
)
#else
PUBLIC S16 egAcUtlDEdmBuildMsg (tcCb, spCb, egMsg)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsg      **egMsg;
#endif
{
   U8            msgType = 0;
   S16            retMsg = 0;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcUtlDEdmBuildMsg)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcUtlDEdmBuildMsg(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcUtlDEdmBuildMsg(), tcId (%d)\n", tcCb->tcId));
#endif

    /* eg006.201: Avoid Segfault caused by NULL assignment to egMsg --*/ 

   /*  Default CSR*/
   msgType = (U8) EGT_GTPC_MSG_CS_REQ;
   retMsg = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"msgType",  &(msgType));
   if(retMsg == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"egAcUtlDEdmBuildMsg() msgType is needed from the xml file\n"));
      RETVALUE(CMXTA_ERR_INT); 
   }

   egDEdmBuildEgMsg(tcCb,spCb,msgType,egMsg);

   RETVALUE(CMXTA_ERR_NONE);
} /*-- egAcUtlDEdmBuildMsg --*/

/*
*
*       Fun:   egDEdmBuildEgMsg
*
*       Desc:  This function is used to Build Dummy EG message 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egAc_egtutl.c
*
*/

#ifdef ANSI
PUBLIC Void  egDEdmBuildEgMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
U8             msgType,
EgMsg **egMsg
)
#else
PUBLIC Void egDEdmBuildEgMsg(tcCb,spCb,msgType,egMsg)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
U8                msgType;
EgMsg       **egMsg;
#endif /* ANSI */
{
   Mem    memInfo;
   U8     intfType= 1; /* S11 interface */
   S16    ret = 0;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egDEdmBuildEgMsg)

   cmMemset((U8*)&memInfo, 0 , sizeof(Mem));
   /* Get the value of the interface for  which the Edmp message need to 
    to be built */
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_ENUM_U8,(Txt  *)"intfType",&intfType);
   if(ret == CMXTA_ERR_NO_VALUE)
   {
       CMXTA_DBG_ERR((_cmxtap,"egDEdmBuildEgMsg(): The value of interface is expected from the xml file\n"));
       RETVOID;
   }

   memInfo.pool   = DFLT_REGION;
   memInfo.region = DFLT_POOL;

   switch(msgType)
   {
      case EGT_GTPC_MSG_CS_REQ:
      {
         /* Build CSREQ */
         egEgtBuildCrtSesReqMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_CS_RSP:
      {
         /* Build CSRSP based on the response */
         egEgtBuildCrtSesRspMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_CB_REQ:
      {
          egEgtBuildCrtBreReqMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_CB_RSP:
      {
          egEgtBuildCrtBreRspMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_BR_CMND:
      {
          egEgtBuildBreResCmdMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_BR_FAIL_IND:
      {
          egEgtBuildBreResFlrIndMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_MB_REQ:
      {
          egEgtBuildModBreReqMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_MB_RSP:
      {
          egEgtBuildModBreRspMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_DS_REQ:
      {
          egEgtBuildDelSesReqMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_DB_REQ:
      {
          egEgtBuildDelBreReqMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_DD_NOTFN_FAIL_IND:
      {
          egEgtBuildDwLnkDatNotFlrIndMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_DS_RSP:
      {
          egEgtBuildDelSesRspMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_DB_RSP:
      {
          egEgtBuildDelBreRspMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_DWN_DATA_NOTFN:
      {
          egEgtBuildDwDatLnkNotMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_DWN_DATA_NOTFN_ACK:
      {
          egEgtBuildDwDatLnkNotAckMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_MB_CMND:
      {
          egEgtBuildModBreCmdMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBFAIL_IND:
      {
          egEgtBuildModBreFlrIndMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_UB_REQ:
      {
          egEgtBuildUpdBreReqMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_UB_RSP:
      {
          egEgtBuildUpdBreRspMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      case EGT_GTPC_MSG_DB_CMND:
      {
          egEgtBuildDeActvBreCmdMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }

      case EGT_GTPC_MSG_DB_FAIL_IN:
      {
         egEgtBuildDeActvBreFlrIndMsg(tcCb,spCb,egMsg,intfType,&memInfo);
         break;
      }
      default:
      { 
         if ( msgType == EGT_GTPC_MSG_ECHO_REQ )
         {
            egEgtBuildEchoMsgReq(tcCb,spCb,egMsg,&memInfo);
         }
         else if ( EGT_GTPC_MSG_ECHO_RSP )
         {
            egEgtBuildEchoMsgRsp(tcCb,spCb,egMsg,&memInfo);
         }

      }
   } /* End of switch */


   /*-- eg003.201 : changes from eg006.102: added RETVOID--*/
  RETVOID;
} /*  egDEdmBuildEgMsg  */


/* Ie Data Encoding and decoding functions */
/***********************************************************************
 *   Fun:   egAcEncEG_UNSIGNED_8
 *   Desc:  Encodes the IE Data of type U8
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_UNSIGNED_8
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_UNSIGNED_8(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
  S16 retValue = 0; /* retrun value used for success or failure */
  retValue= SAddPstMsg(egIe->t.valUnSgnd8, mBuf);
  RETVALUE(retValue);
} 
/***********************************************************************
 *   Fun:   egAcEncEG_UNSIGNED_16
 *   Desc:  Encodes the IE
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_UNSIGNED_16
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_UNSIGNED_16(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
    S16 retValue = 0; /* retrun value used for success or failure */
    EG_ENC_U16(egIe->t.valUnSgnd16, mBuf);
    RETVALUE(retValue);
} 
/***********************************************************************
 *   Fun:   egAcEncEG_UNSIGNED_32
 *   Desc:  Encodes the IE data of type U32
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_UNSIGNED_32
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_UNSIGNED_32(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = 0; /* retrun value used for success or failure */
   EG_ENC_U32(egIe->t.valUnSgnd32, mBuf);
   RETVALUE(retValue);
}
/***********************************************************************
 *   Fun:   egAcEncEG_STRING_8
 *   Desc:  Encodes the IE Data type STRING_8
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16  egAcEncEG_STRING_8
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16  egAcEncEG_STRING_8(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   EG_ENC_STR(mBuf, egIe->t.valStr8.val, egIe->t.valStr8.length, EG_LEN_EIGHT, retVal);
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcEncEG_STRING_16
 *   Desc:  Encodes the IE Data type STRING_16
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_STRING_16
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_STRING_16(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   EG_ENC_STR(mBuf, egIe->t.valStr16.val, egIe->t.valStr16.length, EG_LEN_SIXTEEN, retVal);
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcEncEG_STRING_32
 *   Desc:  Encodes the IE data type STRING_32
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_STRING_32
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_STRING_32(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
  S16 retVal = ROK; /* Return value used to know the successful parsing */
  EG_ENC_STR(mBuf, egIe->t.valStr32.val, egIe->t.valStr32.length, EG_LEN_32, retVal);
  RETVALUE(retVal);
} 
/***********************************************************************
 *   Fun:   egAcEncEG_STRING_132
 *   Desc:  Encodes the IE DATA Of type STRING_132
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_STRING_132
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_STRING_132(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   EG_ENC_STR(mBuf, egIe->t.valStr132.val, egIe->t.valStr132.length, EG_LEN_132, retVal);
   RETVALUE(retVal);
} 
/***********************************************************************
 *   Fun:   egAcEncEG_STRING_MAX
 *   Desc:  Encodes the IE data type STRING_MAX
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_STRING_MAX
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_STRING_MAX(egIe, mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   EG_ENC_STR(mBuf, egIe->t.valStr.val, egIe->t.valStr.length, EG_MAX_STR_LEN, retVal);
   RETVALUE(retVal);
} 
/***********************************************************************
 *   Fun:   egAcEncEG_SNETWORK
 *   Desc:  Encodes the IE Data type SNETWORK
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_SNETWORK
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_SNETWORK(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   EG_ENC_NETID(egIe->t.sNwk,mBuf);
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcEncEG_INDICATION
 *   Desc:  Encodes the IE Data type INDICATION
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_INDICATION
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_INDICATION(egIe, mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   Data     dumBytes[EG_MAX_BYTES]; /* Holds the Data for decoding */
   dumBytes[0]  = ((egIe->t.indication.isSGWCIPres * EG_MASK_BIT1) |
                    (egIe->t.indication.isISRAIPres * EG_MASK_BIT2) |
                    (egIe->t.indication.isISRSIPres * EG_MASK_BIT3) |
                    (egIe->t.indication.isOIPres * EG_MASK_BIT4)    |
                    (egIe->t.indication.isDFIPres * EG_MASK_BIT5)   |
                    (egIe->t.indication.isHIPres * EG_MASK_BIT6)    |
                    (egIe->t.indication.isDTFPres * EG_MASK_BIT7)   |
                    (egIe->t.indication.isDAFPres * EG_MASK_BIT8));

   dumBytes[1]  = ((egIe->t.indication.isMSVPres * EG_MASK_BIT1)   |
                    (egIe->t.indication.isSIPres * EG_MASK_BIT2)    |
                    (egIe->t.indication.isPTPres * EG_MASK_BIT3)   |
                    (egIe->t.indication.isCRSIPres * EG_MASK_BIT4)   |
                    (egIe->t.indication.isCFSIPres * EG_MASK_BIT5));

   retVal= SAddPstMsgMult(dumBytes, EG_LEN_TWO, mBuf);
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcEncEG_PVT_EXTN
 *   Desc:  Encodes the IE data type PVT EXTN
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_PVT_EXTN
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_PVT_EXTN(egIe, mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   EG_ENC_U16(egIe->t.pvtExt.entId, mBuf);

   /************************************************
    * For encoding the remaining bytes to prop val *
    ***********************************************/
   EG_ENC_STR( mBuf, egIe->t.pvtExt.propVal.val,
                egIe->t.pvtExt.propVal.length, EG_LEN_132, retVal);
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcEncEG_CAUSE
 *   Desc:  Encodes the IE Data type and offedning IE info 
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_CAUSE
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_CAUSE(egIe, mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16  retVal = ROK; /* Holds the IE parsing result   */

    /* Encode the cause value */
    SAddPstMsg(egIe->t.cause.causeVal, mBuf);

    /* Encode the cause source*/
	 egIe->t.cause.ieCS = egIe->t.cause.ieCS & 0x01;
    SAddPstMsg(egIe->t.cause.ieCS, mBuf);

    /* Encode the offending IE Type */
    SAddPstMsg(egIe->t.cause.ieType, mBuf);

    /* Encode the offending IE length */
    EG_ENC_U16(egIe->t.cause.ieLength, mBuf);

    /* Encode the offending IE instance */
    SAddPstMsg(egIe->t.cause.ieInst & 0x0F, mBuf);

   RETVALUE(retVal);
}

/***********************************************************************
 *   Fun:   egAcEncEG_TRC_INFO
 *   Desc:  Encodes the IE data type TRC INFO
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_TRC_INFO
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_TRC_INFO(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */

   EG_ENC_NETID(egIe->t.trcInfo.sNwk,mBuf);
	EG_ENC_U32(egIe->t.trcInfo.trcId, mBuf);
	SAddPstMsgMult(egIe->t.trcInfo.trigEvnts,EG_LEN_NINE, mBuf);
	EG_ENC_U16(egIe->t.trcInfo.lstNETypes, mBuf);
	EG_ENC_U8(egIe->t.trcInfo.sesnTrcDep, mBuf);
/*************************************
 * eg009.201 - Added for S2B and S2A *
 *************************************/
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
	SAddPstMsgMult(egIe->t.trcInfo.trigEvnts,EG_LEN_TWELVE, mBuf);
#else
	EG_ENC_U16(egIe->t.trcInfo.lstOfIntfs, mBuf);
#endif
	switch (egIe->t.trcInfo.trcColEntAddr.type)
	{
	  case CM_TPTADDR_IPV4:
		 {
			EG_ENC_U32(egIe->t.trcInfo.trcColEntAddr.u.ipv4, mBuf);
			break;
		 } /* end of case */
#ifdef EG_IPV6_SUPPORTED
	  case CM_TPTADDR_IPV6:
		 {
			SAddPstMsgMult(egIe->t.trcInfo.trcColEntAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
			break;
		 } /* end of case */
#endif /* EG_IPV6_SUPPORTED */
	  default:
		 {
		 	RETVALUE(RFAILED);
		 } /* end of case */
	}
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcEncEG_BEARER_FLAG
 *   Desc:  Encodes the IE data type BEARER FLAG
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_BEARER_FLAG
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_BEARER_FLAG(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
  S16  retVal = ROK; /* Return value used to know the successful parsing */
  U8  tmpByte = 0;      /* Holds 1 byte of data for decoding  */

  tmpByte =  ((egIe->t.bearFlags.isPPCPres * EG_MASK_BIT1) | 
              (egIe->t.bearFlags.isVBPres * EG_MASK_BIT2));
  SAddPstMsg(tmpByte, mBuf);

  RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcEncEG_FTEID
 *   Desc:  Encodes the IE data type FTEID
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_FTEID
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_FTEID(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16  retVal = ROK; /* Return value used to know the successful parsing */

   /***************************************
    * F-TEID  Ie is having the fields:    *
    * one octet: 1-5bits intfType         *
    * one octet: 6th bit EBIF pres        *
    * one octet: 7th bit V6 pres          *
    * one octet: 8th bit V4 pres          *
    * four octets of TEID value           *
    * if 7th bit is set then ipv6 addr    *
    * else 8th bit is set then ipv4 addr  *
    **************************************/
   /*eg009.201:New amcro introduced for better understandingG*/
   egIe->t.fTeid.intfType &= EG_MASK_FTEID_INTFTYPE;

   if(egIe->t.fTeid.isIPv4Pres)
   {
      egIe->t.fTeid.intfType |= EG_MASK_BIT8;
   }
   else
   {
      egIe->t.fTeid.intfType |= EG_MASK_BIT7;
   }
   SAddPstMsg(egIe->t.fTeid.intfType, mBuf);

   EG_ENC_U32(egIe->t.fTeid.teid, mBuf);
   if(egIe->t.fTeid.isIPv4Pres)
	{
	  /***************************
		* Encode the IPV4 address *
		**************************/
	  SAddPstMsgMult(egIe->t.fTeid.u.ip4Addr, EG_LEN_FOUR, mBuf);
	}
	else
	{
	  /***************************
		* Encode the IPV6 address *
		**************************/
	  SAddPstMsgMult(egIe->t.fTeid.u.ipv6Address,
			EG_LEN_SIXTEEN, mBuf);
	}

   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcEncEG_ULI_DATA
 *   Desc:  Encodes the IE Data type ULI
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_ULI_DATA
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_ULI_DATA(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16  retVal = ROK; /* Return value used to know the successful parsing */
    U8  tmpByte;      /* Holds 1 byte of data for decoding  */

   /*********************************************
    * Prepare the first byte which tells        *
    * the presence of the CGI, SAI,RAI,TAI,ECGI *
    *********************************************/
    tmpByte =((egIe->t.uli.isCGIPres * EG_MASK_BIT1) |
              (egIe->t.uli.isSAIPres * EG_MASK_BIT2)  |
              (egIe->t.uli.isRAIPres * EG_MASK_BIT3)  |
              (egIe->t.uli.isTAIPres * EG_MASK_BIT4)  |
              (egIe->t.uli.isECGIPres * EG_MASK_BIT5));
    SAddPstMsg(tmpByte,mBuf);

   /************************************
    * Check if the CGI presence is set *
    ***********************************/
   if(egIe->t.uli.isCGIPres)
   {
      /************************************
       * Encode the MCC,MNC,LAC,CI fields *
       ***********************************/
      EG_ENC_NETID(egIe->t.uli.cgi.sNwk, mBuf);

      EG_ENC_U16(egIe->t.uli.cgi.lac, mBuf);
      EG_ENC_U16(egIe->t.uli.cgi.ci, mBuf);
   }

  /************************************
    * Check if the SAI presence is set *
    ***********************************/
   if(egIe->t.uli.isSAIPres)
   {
      /*************************************
       * Encode the MCC,MNC,LAC,SAC fields *
       *************************************/
       EG_ENC_NETID(egIe->t.uli.sai.sNwk, mBuf);
       EG_ENC_U16(egIe->t.uli.sai.lac, mBuf);
       EG_ENC_U16(egIe->t.uli.sai.sac, mBuf);
   }

   /************************************
    * Check if the RAI presence is set *
    ***********************************/
   if(egIe->t.uli.isRAIPres)
   {
      /*************************************
       * Encode the MCC,MNC,LAC,RAC fields *
       ************************************/
      EG_ENC_NETID(egIe->t.uli.rai.sNwk, mBuf);
      EG_ENC_U16(egIe->t.uli.rai.lac, mBuf);
      EG_ENC_U16(egIe->t.uli.rai.rac, mBuf);
   }

   /************************************
    * Check if the TAI presence is set *
    ***********************************/
  if(egIe->t.uli.isTAIPres)
   {
      /*************************************
       * Encode the MCC,MNC,LAC,TAC fields *
       *************************************/
       EG_ENC_NETID(egIe->t.uli.tai.sNwk, mBuf);
       EG_ENC_U16(egIe->t.uli.tai.tac, mBuf);
   }

   /*************************************
    * Check if the ECGI presence is set *
    ************************************/
   if(egIe->t.uli.isECGIPres)
   {
      /**************************************
       * Encode the MCC,MNC,LAC,ECGI fields *
       **************************************/
       EG_ENC_NETID(egIe->t.uli.ecgi.sNwk, mBuf);

      /****************************************
       * Mask the high 4bits of the ECI value *
       * And then Encode the ECI value        *
       ****************************************/
       egIe->t.uli.ecgi.ecId &= EG_MASK_ECI;
       EG_ENC_U32(egIe->t.uli.ecgi.ecId, mBuf);

   }
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcEncEG_FQOS
 *   Desc:  Encodes the IE Data type FQOS
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_FQOS
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_FQOS(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */

   EG_ENC_FQOS(egIe->t.fQos, mBuf);
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcEncEG_BQOS_IEDATA
 *   Desc:  Encodes the IE data type BQOS
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_BQOS_IEDATA
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_BQOS_IEDATA(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
  S16 retVal = ROK; /* Return value used to know the successful parsing */
  U8  tmpByte = 0;

  tmpByte =  egIe->t.bQos.prityLvl << EG_SHIFT_2;
  tmpByte |= (egIe->t.bQos.isPVIPres * EG_MASK_BIT1);
  tmpByte |= (egIe->t.bQos.isPCIPres * EG_MASK_BIT1);

  SAddPstMsg(tmpByte,mBuf);
  SAddPstMsg(egIe->t.bQos.qci,mBuf);
  SAddPstMsgMult(egIe->t.bQos.upMBR.val, EG_LEN_FIVE, mBuf);
  SAddPstMsgMult(egIe->t.bQos.dnMBR.val, EG_LEN_FIVE, mBuf);
  SAddPstMsgMult(egIe->t.bQos.upGBR.val, EG_LEN_FIVE, mBuf);
  SAddPstMsgMult(egIe->t.bQos.dnGBR.val, EG_LEN_FIVE, mBuf);

  RETVALUE(retVal);
} 
/***********************************************************************
 *   Fun:   egAcEncEG_PAA_IEDATA
 *   Desc:  Encodes the IE data type PAA
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_PAA_IEDATA
(
EgIe* egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_PAA_IEDATA(egIe,mBuf)
EgIe* egIe;
Buffer *mBuf;
#endif
{
    S16 retVal = ROK; /* Return value used to know the successful parsing */

    egIe->t.paa.pdnType &= EG_MASK_LOW3;
    SAddPstMsg(egIe->t.paa.pdnType, mBuf);
    switch(egIe->t.paa.pdnType)
    {
        case 1:
        {
           /**************************************************************
            * if the PDN type is 1, then the pdn address is of type Ipv4 *
            * decode the ipv4 address which is of 4 octets length        *
            **************************************************************/
            SAddPstMsgMult(egIe->t.paa.u.pdnIpv4Addr, EG_LEN_FOUR, mBuf);
            break;
        }
        case 2:
        {
           /***********************************************************
            * If the pdnType is 2, then first octet will tell the pdn *
            * prifix next 16octets will tell the ipv6 address         *
            ***********************************************************/
            SAddPstMsg(egIe->t.paa.pdnPrefix,mBuf);
            SAddPstMsgMult(egIe->t.paa.u.pdnIpv6Addr, EG_LEN_SIXTEEN, mBuf);
            break;
        }
        case 3:
        {
           /************************************************************
            * If the pdnType is 3, then first octet will tell the pdn  *
            * prifix next 16octets will be the ipv6 address next 4     *
            * octets will be the ipv4 address                          *
            ************************************************************/
           SAddPstMsg(egIe->t.paa.pdnPrefix,mBuf);
           SAddPstMsgMult(egIe->t.paa.u.pdnBoth.pdnIpv6Addr,
                           EG_LEN_SIXTEEN, mBuf);
           SAddPstMsgMult(egIe->t.paa.u.pdnBoth.pdnIpv4Addr, EG_LEN_FOUR, mBuf);
           break;
        }
        default:
        {
          /******************
           * Invalid length *
           ******************/
           retVal = EGT_ERR_IE_INV_LEN;
           break;
        }
     }

   RETVALUE(retVal);
}

/***********************************************************************
 *   Fun:   egAcEncEG_AUTH_QUIN
 *   Desc:  Encodes the IE data type Authentication Quintuplet
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_AUTH_QUIN
(
EgIe       *egIe,
Buffer     *mBuf
)
#else
PRIVATE S16 egAcEncEG_AUTH_QUIN(egIe, mBuf)
EgIe       *egIe;
Buffer     *mBuf;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_AUTH_QUIN)

   /* mandate the length as 16 octets */
   egIe->t.authQt.rand.length = EG_LEN_SIXTEEN;

   /* encode the RAND which is of 16 octets*/
   EG_ENC_STR(mBuf, egIe->t.authQt.rand.val, egIe->t.authQt.rand.length, EG_LEN_SIXTEEN, retValue);
   if( retValue != ROK)
   {
      RETVALUE(retValue);
   }

   /* encode the XRES length in single octet and XRES which can be of 16 octets */
   SAddPstMsg(egIe->t.authQt.xresLen, mBuf);
   EG_ENC_STR(mBuf, egIe->t.authQt.xres.val, egIe->t.authQt.xresLen, EG_LEN_SIXTEEN, retValue);
   if( retValue != ROK)
   {
      RETVALUE(retValue);
   }

   /* mandate the length as 16 octets */
   egIe->t.authQt.ck.length = EG_LEN_SIXTEEN;

   /* encode the CK, IK each is of 16 octets length */
   EG_ENC_STR(mBuf, egIe->t.authQt.ck.val, egIe->t.authQt.ck.length, EG_LEN_SIXTEEN, retValue);
   if( retValue != ROK)
   {
      RETVALUE(retValue);
   }

   /* mandate the length as 16 octets */
   egIe->t.authQt.ik.length = EG_LEN_SIXTEEN;

   EG_ENC_STR(mBuf, egIe->t.authQt.ik.val, egIe->t.authQt.ik.length, EG_LEN_SIXTEEN, retValue);
   if( retValue != ROK)
   {
      RETVALUE(retValue);
   }

   /* encode the AUTN */
   SAddPstMsg(egIe->t.authQt.autnLen, mBuf);
   EG_ENC_STR(mBuf, egIe->t.authQt.autn.val, egIe->t.authQt.autn.length, EG_LEN_SIXTEEN, retValue);
   if( retValue != ROK)
   {
      RETVALUE(retValue);
   }

   RETVALUE(ROK);
} /* end of egAcEncEG_AUTH_QUIN */


/***********************************************************************
 *   Fun:   egAcEncEG_AUTH_QUAD
 *   Desc:  Encodes the IE data type Authentication Quadruplet
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_AUTH_QUAD
(
EgIe               *egIe,
Buffer             *mBuf
)
#else
PRIVATE S16 egAcEncEG_AUTH_QUAD(egIe, mBuf)
EgIe               *egIe;
Buffer             *mBuf;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_AUTH_QUAD) 

   /* mandate the length as 16 octets */
   egIe->t.quadruplet.rand.length = EG_LEN_SIXTEEN;

   /* encode the RAND which is of 16 octets*/
   EG_ENC_STR(mBuf, egIe->t.quadruplet.rand.val, egIe->t.quadruplet.rand.length, EG_LEN_SIXTEEN, retValue);

   /* encode the XRES length in single octet and XRES which can be of 16 octets */
   SAddPstMsg(egIe->t.quadruplet.xresLen, mBuf);
   EG_ENC_STR(mBuf, egIe->t.quadruplet.xres.val, egIe->t.quadruplet.xresLen, EG_LEN_SIXTEEN, retValue);

   /* encode the AUTN length in single octet and AUTH which can be of 16 octets */
   SAddPstMsg(egIe->t.quadruplet.autnLen, mBuf);
   EG_ENC_STR(mBuf, egIe->t.quadruplet.autn.val, egIe->t.quadruplet.autnLen, EG_LEN_SIXTEEN, retValue);
   /* encode the Kasme which is of 32 octets */
   egIe->t.quadruplet.kasme.length = EG_KASME_LEN;
   EG_ENC_STR(mBuf, egIe->t.quadruplet.kasme.val, egIe->t.quadruplet.kasme.length, EG_LEN_32, retValue);

   RETVALUE(ROK);
} /* end of egAcEncEG_AUTH_QUAD */


/***********************************************************************
 *   Fun:   egAcEncEG_CMP_REQ
 *   Desc:  Encodes the IE data type Complete Request Message
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_CMP_REQ
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_CMP_REQ(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_CMP_REQ)

   /* encode the CRM Type */
   SAddPstMsg(egIe->t.crm.crmType, mBuf);

   /* encode the CRM Value */
   EG_ENC_STR(mBuf, egIe->t.crm.crm.val, egIe->t.crm.crm.length, EG_MAX_STR_LEN, retValue);

   RETVALUE(retValue);
} /* end of egAcEncEG_CMP_REQ */


/***********************************************************************
 *   Fun:   egAcEncEG_GUTI
 *   Desc:  Encodes the IE data type GUTI
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_GUTI
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_GUTI(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_GUTI)

   /* encode the NETID */
   EG_ENC_NETID(egIe->t.guti.sNwk,mBuf);
   EG_ENC_U16(egIe->t.guti.mmeGrpId, mBuf);
   SAddPstMsg(egIe->t.guti.mmeCode, mBuf);
   EG_ENC_U32(egIe->t.guti.mTmsi, mBuf);

   RETVALUE(ROK);
} /* end of egAcEncEG_GUTI */


/***********************************************************************
 *   Fun:   egAcEncEG_F_CONT
 *   Desc:  Encodes the IE data type F-Container
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_F_CONT
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_F_CONT(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_F_CONT)

   /* encode the container type - mask the msb 4 bits */
   SAddPstMsg(egIe->t.fContainer.containerType & 0x0F, mBuf);
   EG_ENC_STR(mBuf, egIe->t.fContainer.fContainer.val, egIe->t.fContainer.fContainer.length, EG_LEN_32, retValue);

   RETVALUE(retValue);
} /* end of egAcEncEG_F_CONT */


/***********************************************************************
 *   Fun:   egAcEncEG_TRGTID
 *   Desc:  Encodes the IE data type Target Id
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_TRGTID
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_TRGTID(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_TRGTID)
   /* encode the target type */
   SAddPstMsg(egIe->t.targetId.targetType, mBuf);
   EG_ENC_STR(mBuf, egIe->t.targetId.targetId.val, egIe->t.targetId.targetId.length, EG_LEN_EIGHT, retValue);

   RETVALUE(retValue);
} /* end of egAcEncEG_TRGTID */


/***********************************************************************
 *   Fun:   egAcEncEG_PKTFLOWID
 *   Desc:  Encodes the IE data type Packet Flow Id
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_PKTFLOWID
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_PKTFLOWID(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{ 
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_PKTFLOWID)

   /* encode the ebi - mask the msb 4 bits */
   SAddPstMsg((egIe->t.pktFlowId.ebi & 0x0F), mBuf);
   SAddPstMsg(egIe->t.pktFlowId.pktFlowId, mBuf);

   RETVALUE(ROK);
} /* end of egAcEncEG_PKTFLOWID */


/***********************************************************************
 *   Fun:   egAcEncEG_SRCID
 *   Desc:  Encodes the IE data type Cell Id
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_SRCID
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_SRCID(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

   EG_ENC_STR(mBuf, egIe->t.srcId.targetCellId.val, egIe->t.srcId.targetCellId.length, EG_LEN_EIGHT, retValue);
   SAddPstMsg(egIe->t.srcId.sourceType, mBuf);
   EG_ENC_STR(mBuf, egIe->t.srcId.sourceId.val, egIe->t.srcId.sourceId.length, EG_LEN_SIXTEEN, retValue);

   RETVALUE(retValue);
} /* end of egAcEncEG_SRCID */

/***********************************************************************
 *   Fun:   egAcEncEG_GLOBAL_CNID
 *   Desc:  Encodes the IE data type Global CN Id
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_GLOBAL_CNID
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_GLOBAL_CNID(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

   EG_ENC_NETID(egIe->t.gblCnId.sNwk,mBuf);
   EG_ENC_STR(mBuf, egIe->t.gblCnId.cnId.val, egIe->t.gblCnId.cnId.length, EG_LEN_FOUR, retValue);

   RETVALUE(retValue);
} /* end of egAcEncEG_GLOBAL_CNID */


/***********************************************************************
 *   Fun:   egAcEncEG_PDN_CONN_SET_ID
 *   Desc:  Encodes the IE data type PDN Connection Set Identifier
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_PDN_CONN_SET_ID
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_PDN_CONN_SET_ID(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;
	U8  tmpByte = 0;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_PDN_CONN_SET_ID)

   egIe->t.csid.nodeIdType = ((egIe->t.csid.nodeIdType << EG_SHIFT_4) & 0xF0);
	tmpByte = (egIe->t.csid.nodeIdType) | (egIe->t.csid.noOfCSIDs & 0x0F);

   SAddPstMsg(tmpByte , mBuf);

   EG_ENC_STR(mBuf, egIe->t.csid.nodeId.val, egIe->t.csid.nodeId.length, EG_LEN_SIXTEEN, retValue);
   EG_ENC_STR(mBuf, egIe->t.csid.csid.val, egIe->t.csid.csid.length, EG_LEN_SIXTEEN, retValue);

   RETVALUE(retValue);
} /* end of egAcEncEG_PDN_CONN_SET_ID */


/***********************************************************************
 *   Fun:   egAcEncEG_IP_ADDR
 *   Desc:  Encodes the IE data type IP Address
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_IP_ADDR
(
EgIe       *egIe,
Buffer     *mBuf
)
#else
PRIVATE S16 egAcEncEG_IP_ADDR(egIe, mBuf)
EgIe       *egIe;
Buffer     *mBuf;
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_IP_ADDR)

   switch (egIe->t.ipAddr.type)
   {
      case CM_TPTADDR_IPV4:
      {
         EG_ENC_U32(egIe->t.ipAddr.u.ipv4, mBuf);
         break;
      } /* end of case */
#ifdef EG_IPV6_SUPPORTED
      case CM_TPTADDR_IPV6:
      {
         SAddPstMsgMult(egIe->t.ipAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
         break;
      } /* end of case */
#endif /* EG_IPV6_SUPPORTED */
      default:
      {
			RETVALUE(RFAILED);
      } /* end of case */
   }

   RETVALUE(ROK);
} /* end of egAcEncEG_IP_ADDR */


/***********************************************************************
 *   Fun:   egAcEncEG_GSM_KEY_TRIP
 *   Desc:  Encodes the IE data type GSM Key Triplet
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_GSM_KEY_TRIP
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_GSM_KEY_TRIP(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 cnt = 0;
   S16 retValue = ROK;
	U8  tmpByte = 0;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_GSM_KEY_TRIP)

	tmpByte = (((egIe->t.gsmKeyT.secMode << EG_SHIFT_5)&0xE0) | 
				 (egIe->t.gsmKeyT.isDRXIPres * EG_MASK_BIT4) | (egIe->t.gsmKeyT.cksn & 0x07));
   SAddPstMsg(tmpByte , mBuf);

	tmpByte = 0;
	tmpByte = (egIe->t.gsmKeyT.nmbTrip << EG_SHIFT_5) & 0xE0;
	tmpByte |= (egIe->t.gsmKeyT.isUAMBRIPres * EG_MASK_BIT2);
	tmpByte |= (egIe->t.gsmKeyT.isSAMBRIPres * EG_MASK_BIT1);
   SAddPstMsg(tmpByte , mBuf);

   SAddPstMsg( (egIe->t.gsmKeyT.usedCipher & 0x07), mBuf);

   /* encode Kc in eight octets */
   SAddPstMsgMult(egIe->t.gsmKeyT.kc, EG_LEN_EIGHT, mBuf);

   for (cnt = 0; cnt < egIe->t.gsmKeyT.nmbTrip; cnt++)
	{
	  SAddPstMsgMult(egIe->t.gsmKeyT.authTrip[cnt].rand, 16, mBuf);
	  SAddPstMsgMult(egIe->t.gsmKeyT.authTrip[cnt].sres, 4, mBuf);
	  SAddPstMsgMult(egIe->t.gsmKeyT.authTrip[cnt].kc, 8, mBuf);
	} /* end of loop */

   /* encode drx parameter - is of 5 octets */
   SAddPstMsgMult(egIe->t.gsmKeyT.drxParam, EG_LEN_TWO, mBuf);

	/* encode upLink subscribed UE AMBR */
   EG_ENC_U32(egIe->t.gsmKeyT.upSubsUEAMBR, mBuf);

	/* encode downLink subscribed UE AMBR */
   EG_ENC_U32(egIe->t.gsmKeyT.dnSubsUEAMBR, mBuf);

	/* encode upLink used UE AMBR */
   EG_ENC_U32(egIe->t.gsmKeyT.upUsedUEAMBR, mBuf);

	/* encode downLink used UE AMBR */
   EG_ENC_U32(egIe->t.gsmKeyT.dnUsedUEAMBR, mBuf);

   /* here we are mandating the length of UE Ntwrk will be of 15 octets */
   egIe->t.gsmKeyT.ueNtwrkCapb.length = EG_UE_NTWRK_CAPB_LEN;

   /* encode UE Network Capability - can be max of 15 octets */
   EG_ENC_STR(mBuf, egIe->t.gsmKeyT.ueNtwrkCapb.val, egIe->t.gsmKeyT.ueNtwrkCapb.length, EG_LEN_SIXTEEN, retValue);

  /* here we are mandating the length of MS Ntwrk will be of 10 octets */
   egIe->t.gsmKeyT.msNtwrkCapb.length = EG_MS_NTWRK_CAPB_LEN;

   /* encode MS Network Capability - can be max of 10 octets */
   EG_ENC_STR(mBuf, egIe->t.gsmKeyT.msNtwrkCapb.val, egIe->t.gsmKeyT.msNtwrkCapb.length, EG_LEN_SIXTEEN, retValue);

   /* here we are mandating the length of MEID will be of 16 octets */
   egIe->t.gsmKeyT.meId.length = EG_LEN_SIXTEEN;

   /* encode MEID - is of 16 octets */
   EG_ENC_STR(mBuf, egIe->t.gsmKeyT.meId.val, egIe->t.gsmKeyT.meId.length, EG_LEN_SIXTEEN, retValue);

	tmpByte = 0;

	tmpByte = egIe->t.gsmKeyT.isUNA * EG_MASK_BIT1;
	tmpByte |= egIe->t.gsmKeyT.isGENA * EG_MASK_BIT2;
	tmpByte |= egIe->t.gsmKeyT.isGANA * EG_MASK_BIT3;
	tmpByte |= egIe->t.gsmKeyT.isINA * EG_MASK_BIT4;
	tmpByte |= egIe->t.gsmKeyT.isENA * EG_MASK_BIT5;
	tmpByte |= egIe->t.gsmKeyT.isHNNA * EG_MASK_BIT6;

   SAddPstMsg(tmpByte , mBuf);
#ifdef EG_REL_930
   /* encode Voice Domain Preference and UE's usage Setting length */
	SAddPstMsg( egIe->t.gsmKeyT.vDomPrefUEUsageLen, mBuf);
   
	/* encode UE's usage setting (1 bit field) Bit-3
	 * encode Voice  domain prefernce for E-UTRAN(2 bit field) Bit 2 and 1 */
	if(egIe->t.gsmKeyT.vDomPrefUEUsageLen)
	{
	  tmpByte = 0;
	  tmpByte = egIe->t.gsmKeyT.ueUsageSett * EG_MASK_BIT1;
	  tmpByte <<= EG_SHIFT_2;
	  tmpByte |= egIe->t.gsmKeyT.vDomPref && 0x03;

	  SAddPstMsg(tmpByte , mBuf);
	}
#endif /* EG_REL_930 */


   RETVALUE(retValue);
} /* end of egAcEncEG_GSM_KEY_TRIP */


/***********************************************************************
 *   Fun:   egAcEncEG_UMTS_KEY_CIPH_QUIN
 *   Desc:  Encodes the IE data type UMTS Key, Used Cipher and Quintuplets
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_UMTS_KEY_CIPH_QUIN
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_UMTS_KEY_CIPH_QUIN(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 cnt = 0;
   S16 retValue = ROK;
	U8  tmpByte = 0;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_UMTS_KEY_CIPH_QUIN)

	tmpByte = (((egIe->t.umtsKeyUCQt.secMode << EG_SHIFT_5)&0xE0) | 
				 (egIe->t.umtsKeyUCQt.isDRXIPres * EG_MASK_BIT4) | (egIe->t.umtsKeyUCQt.cksn & 0x07));
   SAddPstMsg(tmpByte , mBuf);

	tmpByte = 0;
	tmpByte = (egIe->t.umtsKeyUCQt.nmbQuin << EG_SHIFT_5) & 0xE0;
	tmpByte |= (egIe->t.umtsKeyUCQt.isUAMBRIPres * EG_MASK_BIT2);
	tmpByte |= (egIe->t.umtsKeyUCQt.isSAMBRIPres * EG_MASK_BIT1);
   SAddPstMsg(tmpByte , mBuf);

   SAddPstMsg( (egIe->t.umtsKeyUCQt.usedCipher & 0x07), mBuf);
   /* mandate the length as 16 octets */
   egIe->t.umtsKeyUCQt.ck.length = EG_LEN_SIXTEEN;
   egIe->t.umtsKeyUCQt.ik.length = EG_LEN_SIXTEEN;

   /* encode CK, IK each of 16 octets */
   EG_ENC_STR(mBuf, egIe->t.umtsKeyUCQt.ck.val, egIe->t.umtsKeyUCQt.ck.length, EG_LEN_SIXTEEN, retValue);
   EG_ENC_STR(mBuf, egIe->t.umtsKeyUCQt.ik.val, egIe->t.umtsKeyUCQt.ik.length, EG_LEN_SIXTEEN, retValue);
	for(cnt = 0;cnt < egIe->t.umtsKeyUCQt.nmbQuin;cnt++)
	{
	  /* mandate the length as 16 octets */
	  egIe->t.umtsKeyUCQt.authQuin[cnt].rand.length = EG_LEN_SIXTEEN;

	  /* encode the RAND which is of 16 octets*/
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyUCQt.authQuin[cnt].rand.val, egIe->t.umtsKeyUCQt.authQuin[cnt].rand.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* encode the XRES length in single octet and XRES which can be of 16 octets */
	  SAddPstMsg(egIe->t.umtsKeyUCQt.authQuin[cnt].xresLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyUCQt.authQuin[cnt].xres.val, egIe->t.umtsKeyUCQt.authQuin[cnt].xresLen, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* mandate the length as 16 octets */
	  egIe->t.umtsKeyUCQt.authQuin[cnt].ck.length = EG_LEN_SIXTEEN;
	  egIe->t.umtsKeyUCQt.authQuin[cnt].ik.length = EG_LEN_SIXTEEN;

	  /* encode the CK, IK each is of 16 octets length */
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyUCQt.authQuin[cnt].ck.val, egIe->t.umtsKeyUCQt.authQuin[cnt].ck.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  EG_ENC_STR(mBuf, egIe->t.umtsKeyUCQt.authQuin[cnt].ik.val, egIe->t.umtsKeyUCQt.authQuin[cnt].ik.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* encode the AUTN */
	  SAddPstMsg(egIe->t.umtsKeyUCQt.authQuin[cnt].autnLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyUCQt.authQuin[cnt].autn.val, egIe->t.umtsKeyUCQt.authQuin[cnt].autnLen, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }
	}

   /* encode drx parameter - is of 2 octets */
   SAddPstMsgMult(egIe->t.umtsKeyUCQt.drxParam, EG_LEN_TWO, mBuf);

	/* encode upLink subscribed UE AMBR */
   EG_ENC_U32(egIe->t.umtsKeyUCQt.upSubsUEAMBR, mBuf);

	/* encode downLink subscribed UE AMBR */
   EG_ENC_U32(egIe->t.umtsKeyUCQt.dnSubsUEAMBR, mBuf);

	/* encode upLink used UE AMBR */
   EG_ENC_U32(egIe->t.umtsKeyUCQt.upUsedUEAMBR, mBuf);

	/* encode downLink used UE AMBR */
   EG_ENC_U32(egIe->t.umtsKeyUCQt.dnUsedUEAMBR, mBuf);

   /* here we are mandating the length of UE Ntwrk will be of 15 octets */
   egIe->t.umtsKeyUCQt.ueNtwrkCapb.length = EG_UE_NTWRK_CAPB_LEN;

   /* encode UE Network Capability - can be max of 15 octets */
   EG_ENC_STR(mBuf, egIe->t.umtsKeyUCQt.ueNtwrkCapb.val, egIe->t.umtsKeyUCQt.ueNtwrkCapb.length, EG_LEN_SIXTEEN, retValue);

  /* here we are mandating the length of MS Ntwrk will be of 10 octets */
   egIe->t.umtsKeyUCQt.msNtwrkCapb.length = EG_MS_NTWRK_CAPB_LEN;

   /* encode MS Network Capability - can be max of 10 octets */
   EG_ENC_STR(mBuf, egIe->t.umtsKeyUCQt.msNtwrkCapb.val, egIe->t.umtsKeyUCQt.msNtwrkCapb.length, EG_LEN_SIXTEEN, retValue);

   /* here we are mandating the length of MEID will be of 16 octets */
   egIe->t.umtsKeyUCQt.meId.length = EG_LEN_SIXTEEN;

   /* encode MEID - is of 16 octets */
   EG_ENC_STR(mBuf, egIe->t.umtsKeyUCQt.meId.val, egIe->t.umtsKeyUCQt.meId.length, EG_LEN_SIXTEEN, retValue);

	tmpByte = 0;

	tmpByte = egIe->t.umtsKeyUCQt.isUNA * EG_MASK_BIT1;
	tmpByte |= egIe->t.umtsKeyUCQt.isGENA * EG_MASK_BIT2;
	tmpByte |= egIe->t.umtsKeyUCQt.isGANA * EG_MASK_BIT3;
	tmpByte |= egIe->t.umtsKeyUCQt.isINA * EG_MASK_BIT4;
	tmpByte |= egIe->t.umtsKeyUCQt.isENA * EG_MASK_BIT5;
	tmpByte |= egIe->t.umtsKeyUCQt.isHNNA * EG_MASK_BIT6;

	SAddPstMsg(tmpByte, mBuf);
#ifdef EG_REL_930
   /* encode Voice Domain Preference and UE's usage Setting length */
	SAddPstMsg( egIe->t.umtsKeyUCQt.vDomPrefUEUsageLen, mBuf);
   
	/* encode UE's usage setting (1 bit field) Bit-3
	 * encode Voice  domain prefernce for E-UTRAN(2 bit field) Bit 2 and 1 */
	if(egIe->t.umtsKeyUCQt.vDomPrefUEUsageLen)
	{
	  tmpByte = 0;
	  tmpByte = egIe->t.umtsKeyUCQt.ueUsageSett * EG_MASK_BIT1;
	  tmpByte <<= EG_SHIFT_2;
	  tmpByte |= egIe->t.umtsKeyUCQt.vDomPref && 0x03;

	  SAddPstMsg(tmpByte , mBuf);
	}
#endif /* EG_REL_930 */

   RETVALUE(retValue);
} /* end of egAcEncEG_UMTS_KEY_CIPH_QUIN */


/***********************************************************************
 *   Fun:   egAcEncEG_GSM_KEY_CIPH_QUIN
 *   Desc:  Encodes the IE data type GSM Key, Used Cipher and Quintuplets
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_GSM_KEY_CIPH_QUIN
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_GSM_KEY_CIPH_QUIN(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 cnt = 0;
   S16 retValue = ROK;
	U8  tmpByte = 0;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_GSM_KEY_CIPH_QUIN)

	tmpByte = (((egIe->t.gsmKeyUCQt.secMode << EG_SHIFT_5)&0xE0) | 
				 (egIe->t.gsmKeyUCQt.isDRXIPres * EG_MASK_BIT4) | (egIe->t.gsmKeyUCQt.cksn & 0x07));
   SAddPstMsg(tmpByte , mBuf);

	tmpByte = 0;
	tmpByte = (egIe->t.gsmKeyUCQt.nmbQuin << EG_SHIFT_5) & 0xE0;
	tmpByte |= (egIe->t.gsmKeyUCQt.isUAMBRIPres * EG_MASK_BIT2);
	tmpByte |= (egIe->t.gsmKeyUCQt.isSAMBRIPres * EG_MASK_BIT1);
   SAddPstMsg(tmpByte , mBuf);

   SAddPstMsg( (egIe->t.gsmKeyUCQt.usedCipher & 0x07), mBuf);

   /* encode KC of 8 octets */
   SAddPstMsgMult(egIe->t.gsmKeyUCQt.kc, EG_LEN_EIGHT, mBuf);

	for(cnt = 0;cnt < egIe->t.gsmKeyUCQt.nmbQuin;cnt++)
	{
	  /* mandate the length as 16 octets */
	  egIe->t.gsmKeyUCQt.authQuin[cnt].rand.length = EG_LEN_SIXTEEN;

	  /* encode the RAND which is of 16 octets*/
	  EG_ENC_STR(mBuf, egIe->t.gsmKeyUCQt.authQuin[cnt].rand.val, egIe->t.gsmKeyUCQt.authQuin[cnt].rand.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* encode the XRES length in single octet and XRES which can be of 16 octets */
	  SAddPstMsg(egIe->t.gsmKeyUCQt.authQuin[cnt].xresLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.gsmKeyUCQt.authQuin[cnt].xres.val, egIe->t.gsmKeyUCQt.authQuin[cnt].xresLen, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* mandate the length as 16 octets */
	  egIe->t.gsmKeyUCQt.authQuin[cnt].ck.length = EG_LEN_SIXTEEN;
	  egIe->t.gsmKeyUCQt.authQuin[cnt].ik.length = EG_LEN_SIXTEEN;

	  /* encode the CK, IK each is of 16 octets length */
	  EG_ENC_STR(mBuf, egIe->t.gsmKeyUCQt.authQuin[cnt].ck.val, egIe->t.gsmKeyUCQt.authQuin[cnt].ck.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  EG_ENC_STR(mBuf, egIe->t.gsmKeyUCQt.authQuin[cnt].ik.val, egIe->t.gsmKeyUCQt.authQuin[cnt].ik.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* encode the AUTN */
	  SAddPstMsg(egIe->t.gsmKeyUCQt.authQuin[cnt].autnLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.gsmKeyUCQt.authQuin[cnt].autn.val, egIe->t.gsmKeyUCQt.authQuin[cnt].autnLen, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }
	}

   /* encode drx parameter - is of 2 octets */
   SAddPstMsgMult(egIe->t.gsmKeyUCQt.drxParam, EG_LEN_TWO, mBuf);

	/* encode upLink subscribed UE AMBR */
   EG_ENC_U32(egIe->t.gsmKeyUCQt.upSubsUEAMBR, mBuf);

	/* encode downLink subscribed UE AMBR */
   EG_ENC_U32(egIe->t.gsmKeyUCQt.dnSubsUEAMBR, mBuf);

	/* encode upLink used UE AMBR */
   EG_ENC_U32(egIe->t.gsmKeyUCQt.upUsedUEAMBR, mBuf);

	/* encode downLink used UE AMBR */
   EG_ENC_U32(egIe->t.gsmKeyUCQt.dnUsedUEAMBR, mBuf);

   /* here we are mandating the length of UE Ntwrk will be of 15 octets */
   egIe->t.gsmKeyUCQt.ueNtwrkCapb.length = EG_UE_NTWRK_CAPB_LEN;

   /* encode UE Network Capability - can be max of 15 octets */
   EG_ENC_STR(mBuf, egIe->t.gsmKeyUCQt.ueNtwrkCapb.val, egIe->t.gsmKeyUCQt.ueNtwrkCapb.length, EG_LEN_SIXTEEN, retValue);

  /* here we are mandating the length of MS Ntwrk will be of 10 octets */
   egIe->t.gsmKeyUCQt.msNtwrkCapb.length = EG_MS_NTWRK_CAPB_LEN;

   /* encode MS Network Capability - can be max of 10 octets */
   EG_ENC_STR(mBuf, egIe->t.gsmKeyUCQt.msNtwrkCapb.val, egIe->t.gsmKeyUCQt.msNtwrkCapb.length, EG_LEN_SIXTEEN, retValue);

   /* here we are mandating the length of MEID will be of 16 octets */
   egIe->t.gsmKeyUCQt.meId.length = EG_LEN_SIXTEEN;

   /* encode MEID - is of 16 octets */
   EG_ENC_STR(mBuf, egIe->t.gsmKeyUCQt.meId.val, egIe->t.gsmKeyUCQt.meId.length, EG_LEN_SIXTEEN, retValue);

	tmpByte = 0;

	tmpByte = egIe->t.gsmKeyUCQt.isUNA * EG_MASK_BIT1;
	tmpByte |= egIe->t.gsmKeyUCQt.isGENA * EG_MASK_BIT2;
	tmpByte |= egIe->t.gsmKeyUCQt.isGANA * EG_MASK_BIT3;
	tmpByte |= egIe->t.gsmKeyUCQt.isINA * EG_MASK_BIT4;
	tmpByte |= egIe->t.gsmKeyUCQt.isENA * EG_MASK_BIT5;
	tmpByte |= egIe->t.gsmKeyUCQt.isHNNA * EG_MASK_BIT6;

	SAddPstMsg(tmpByte, mBuf);

#ifdef EG_REL_930
   /* encode Voice Domain Preference and UE's usage Setting length */
	SAddPstMsg( egIe->t.gsmKeyUCQt.vDomPrefUEUsageLen, mBuf);
   
	/* encode UE's usage setting (1 bit field) Bit-3
	 * encode Voice  domain prefernce for E-UTRAN(2 bit field) Bit 2 and 1 */
	if(egIe->t.gsmKeyUCQt.vDomPrefUEUsageLen)
	{
	  tmpByte = 0;
	  tmpByte = egIe->t.gsmKeyUCQt.ueUsageSett * EG_MASK_BIT1;
	  tmpByte <<= EG_SHIFT_2;
	  tmpByte |= egIe->t.gsmKeyUCQt.vDomPref && 0x03;

	  SAddPstMsg(tmpByte , mBuf);
	}
#endif /* EG_REL_930 */

   RETVALUE(retValue);
} /* end of egAcEncEG_GSM_KEY_CIPH_QUIN */


/***********************************************************************
 *   Fun:   egAcEncEG_UMTS_KEY_QUIN
 *   Desc:  Encodes the IE data type UMTS Key, and Quintuplets
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_UMTS_KEY_QUIN
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_UMTS_KEY_QUIN(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 cnt = 0;
   S16 retValue = ROK;
	U8  tmpByte = 0;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_UMTS_KEY_QUIN)

	tmpByte = (((egIe->t.umtsKeyQt.secMode << EG_SHIFT_5)&0xE0) | 
				 (egIe->t.umtsKeyQt.isDRXIPres * EG_MASK_BIT4) | (egIe->t.umtsKeyQt.ksi & 0x07));
   SAddPstMsg(tmpByte , mBuf);

	tmpByte = 0;
	tmpByte = (egIe->t.umtsKeyQt.nmbQuin<< EG_SHIFT_5) & 0xE0;
	tmpByte |= (egIe->t.umtsKeyQt.isUAMBRIPres * EG_MASK_BIT2);
	tmpByte |= (egIe->t.umtsKeyQt.isSAMBRIPres * EG_MASK_BIT1);
   SAddPstMsg(tmpByte , mBuf);
   /* 7th one is  spare octect */
	tmpByte = 0;
   SAddPstMsg( tmpByte, mBuf);

   /* mandate the length as 16 octets */
   egIe->t.umtsKeyQt.ck.length = EG_LEN_SIXTEEN;
   egIe->t.umtsKeyQt.ik.length = EG_LEN_SIXTEEN;

   /* encode CK, IK each of 16 octets */
   EG_ENC_STR(mBuf, egIe->t.umtsKeyQt.ck.val, egIe->t.umtsKeyQt.ck.length, EG_LEN_SIXTEEN, retValue);
   EG_ENC_STR(mBuf, egIe->t.umtsKeyQt.ik.val, egIe->t.umtsKeyQt.ik.length, EG_LEN_SIXTEEN, retValue);
	for(cnt = 0;cnt < egIe->t.umtsKeyQt.nmbQuin;cnt++)
	{
	  /* mandate the length as 16 octets */
	  egIe->t.umtsKeyQt.authQuin[cnt].rand.length = EG_LEN_SIXTEEN;

	  /* encode the RAND which is of 16 octets*/
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQt.authQuin[cnt].rand.val, egIe->t.umtsKeyQt.authQuin[cnt].rand.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* encode the XRES length in single octet and XRES which can be of 16 octets */
	  SAddPstMsg(egIe->t.umtsKeyQt.authQuin[cnt].xresLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQt.authQuin[cnt].xres.val, egIe->t.umtsKeyQt.authQuin[cnt].xresLen, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* mandate the length as 16 octets */
	  egIe->t.umtsKeyQt.authQuin[cnt].ck.length = EG_LEN_SIXTEEN;
	  egIe->t.umtsKeyQt.authQuin[cnt].ik.length = EG_LEN_SIXTEEN;

	  /* encode the CK, IK each is of 16 octets length */
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQt.authQuin[cnt].ck.val, egIe->t.umtsKeyQt.authQuin[cnt].ck.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQt.authQuin[cnt].ik.val, egIe->t.umtsKeyQt.authQuin[cnt].ik.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* encode the AUTN */
	  SAddPstMsg(egIe->t.umtsKeyQt.authQuin[cnt].autnLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQt.authQuin[cnt].autn.val, egIe->t.umtsKeyQt.authQuin[cnt].autnLen, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }
	}

   /* encode drx parameter - is of 2 octets */
   SAddPstMsgMult(egIe->t.umtsKeyQt.drxParam, EG_LEN_TWO, mBuf);

	/* encode upLink subscribed UE AMBR */
   EG_ENC_U32(egIe->t.umtsKeyQt.upSubsUEAMBR, mBuf);

	/* encode downLink subscribed UE AMBR */
   EG_ENC_U32(egIe->t.umtsKeyQt.dnSubsUEAMBR, mBuf);

	/* encode upLink used UE AMBR */
   EG_ENC_U32(egIe->t.umtsKeyQt.upUsedUEAMBR, mBuf);

	/* encode downLink used UE AMBR */
   EG_ENC_U32(egIe->t.umtsKeyQt.dnUsedUEAMBR, mBuf);

   /* here we are mandating the length of UE Ntwrk will be of 15 octets */
   egIe->t.umtsKeyQt.ueNtwrkCapb.length = EG_UE_NTWRK_CAPB_LEN;

   /* encode UE Network Capability - can be max of 15 octets */
   EG_ENC_STR(mBuf, egIe->t.umtsKeyQt.ueNtwrkCapb.val, egIe->t.umtsKeyQt.ueNtwrkCapb.length, EG_LEN_SIXTEEN, retValue);

  /* here we are mandating the length of MS Ntwrk will be of 10 octets */
   egIe->t.umtsKeyQt.msNtwrkCapb.length = EG_MS_NTWRK_CAPB_LEN;

   /* encode MS Network Capability - can be max of 10 octets */
   EG_ENC_STR(mBuf, egIe->t.umtsKeyQt.msNtwrkCapb.val, egIe->t.umtsKeyQt.msNtwrkCapb.length, EG_LEN_SIXTEEN, retValue);

   /* here we are mandating the length of MEID will be of 16 octets */
   egIe->t.umtsKeyQt.meId.length = EG_LEN_SIXTEEN;

   /* encode MEID - is of 16 octets */
   EG_ENC_STR(mBuf, egIe->t.umtsKeyQt.meId.val, egIe->t.umtsKeyQt.meId.length, EG_LEN_SIXTEEN, retValue);

	tmpByte = 0;

	tmpByte = egIe->t.umtsKeyQt.isUNA * EG_MASK_BIT1;
	tmpByte |= egIe->t.umtsKeyQt.isGENA * EG_MASK_BIT2;
	tmpByte |= egIe->t.umtsKeyQt.isGANA * EG_MASK_BIT3;
	tmpByte |= egIe->t.umtsKeyQt.isINA * EG_MASK_BIT4;
	tmpByte |= egIe->t.umtsKeyQt.isENA * EG_MASK_BIT5;
	tmpByte |= egIe->t.umtsKeyQt.isHNNA * EG_MASK_BIT6;

	SAddPstMsg(tmpByte, mBuf);

#ifdef EG_REL_930
   /* encode Voice Domain Preference and UE's usage Setting length */
	SAddPstMsg( egIe->t.umtsKeyQt.vDomPrefUEUsageLen, mBuf);
   
	/* encode UE's usage setting (1 bit field) Bit-3
	 * encode Voice  domain prefernce for E-UTRAN(2 bit field) Bit 2 and 1 */
	if(egIe->t.umtsKeyQt.vDomPrefUEUsageLen)
	{
	  tmpByte = 0;
	  tmpByte = egIe->t.umtsKeyQt.ueUsageSett * EG_MASK_BIT1;
	  tmpByte <<= EG_SHIFT_2;
	  tmpByte |= egIe->t.umtsKeyQt.vDomPref && 0x03;

	  SAddPstMsg(tmpByte , mBuf);
	}
#endif /* EG_REL_930 */
   RETVALUE(retValue);
} /* end of egAcEncEG_UMTS_KEY_QUIN */


/***********************************************************************
 *   Fun:   egAcEncEG_EPS_SEC_QUAD_QUIN
 *   Desc:  Encodes the IE data type EPS Security Context, Quadruplets and Quintuplets
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_EPS_SEC_QUAD_QUIN
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_EPS_SEC_QUAD_QUIN(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 cnt = 0;
   S16 retValue = ROK;
	U8  tmpByte = 0x00;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_EPS_SEC_QUAD_QUIN)

	tmpByte = (((egIe->t.eSecCxtQdQt.secMode & 0x07) << EG_SHIFT_5)) | 
		 (egIe->t.eSecCxtQdQt.isNHIPres * EG_MASK_BIT5) |
		 (egIe->t.eSecCxtQdQt.isDRXIPres * EG_MASK_BIT4) | (egIe->t.eSecCxtQdQt.ksi & 0x07);
	  SAddPstMsg(tmpByte, mBuf);

	tmpByte = 0x00;
	tmpByte = ((egIe->t.eSecCxtQdQt.nmbQuin & 0x07) << EG_SHIFT_5) |
		 ((egIe->t.eSecCxtQdQt.nmbQuadru & 0x07) << EG_SHIFT_2) |
		 (egIe->t.eSecCxtQdQt.isUAMBRIPres * EG_MASK_BIT2) |
		 (egIe->t.eSecCxtQdQt.isOCSIPres  * EG_MASK_BIT1);
	SAddPstMsg(tmpByte, mBuf);

	tmpByte = egIe->t.eSecCxtQdQt.isSAMBRIPres * EG_MASK_BIT7;
   tmpByte |= ( (((egIe->t.eSecCxtQdQt.nasProtAlgo & 0x07) << EG_SHIFT_4))| 
          (egIe->t.eSecCxtQdQt.usedNasCipher & 0x0F));
   SAddPstMsg(tmpByte , mBuf);

   /* encode NAS Downlink Count and NAS Uplink Count - each of 3 octets long */
   EG_ENC_U24(egIe->t.eSecCxtQdQt.nasDlCount, mBuf);
   EG_ENC_U24(egIe->t.eSecCxtQdQt.nasUlCount, mBuf);

   /* encode Kasme of 32 octets */
   egIe->t.eSecCxtQdQt.kasme.length = EG_KASME_LEN;
   EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.kasme.val, egIe->t.eSecCxtQdQt.kasme.length, EG_LEN_32, retValue);

	for(cnt=0;cnt < egIe->t.eSecCxtQdQt.nmbQuadru;cnt++)
	{
	  /* mandate the length as 16 octets */
	  egIe->t.eSecCxtQdQt.authQuadru[cnt].rand.length = EG_LEN_SIXTEEN;

	  /* encode the RAND which is of 16 octets*/
	  EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuadru[cnt].rand.val, egIe->t.eSecCxtQdQt.authQuadru[cnt].rand.length, EG_LEN_SIXTEEN, retValue);

	  /* encode the XRES length in single octet and XRES which can be of 16 octets */
	  SAddPstMsg(egIe->t.eSecCxtQdQt.authQuadru[cnt].xresLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuadru[cnt].xres.val, egIe->t.eSecCxtQdQt.authQuadru[cnt].xresLen, EG_LEN_SIXTEEN, retValue);

	  /* encode the AUTN length in single octet and AUTH which can be of 16 octets */
	  SAddPstMsg(egIe->t.eSecCxtQdQt.authQuadru[cnt].autnLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuadru[cnt].autn.val, egIe->t.eSecCxtQdQt.authQuadru[cnt].autnLen, EG_LEN_SIXTEEN, retValue);

	  /* encode the Kasme which is of 31 octets */
	  egIe->t.eSecCxtQdQt.authQuadru[cnt].kasme.length = EG_KASME_LEN;
	  EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuadru[cnt].kasme.val, egIe->t.eSecCxtQdQt.authQuadru[cnt].kasme.length, EG_LEN_32, retValue);
	}
	for(cnt=0;cnt<egIe->t.eSecCxtQdQt.nmbQuin;cnt++)
	{
	  /* mandate the length as 16 octets */
	  egIe->t.eSecCxtQdQt.authQuin[cnt].rand.length = EG_LEN_SIXTEEN;

	  /* encode the RAND which is of 16 octets*/
	  EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuin[cnt].rand.val, egIe->t.eSecCxtQdQt.authQuin[cnt].rand.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* encode the XRES length in single octet and XRES which can be of 16 octets */
	  SAddPstMsg(egIe->t.eSecCxtQdQt.authQuin[cnt].xresLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuin[cnt].xres.val, egIe->t.eSecCxtQdQt.authQuin[cnt].xresLen, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* mandate the length as 16 octets */
	  egIe->t.eSecCxtQdQt.authQuin[cnt].ck.length = EG_LEN_SIXTEEN;
	  egIe->t.eSecCxtQdQt.authQuin[cnt].ik.length = EG_LEN_SIXTEEN;

	  /* encode the CK, IK each is of 16 octets length */
	  EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuin[cnt].ck.val, egIe->t.eSecCxtQdQt.authQuin[cnt].ck.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuin[cnt].ik.val, egIe->t.eSecCxtQdQt.authQuin[cnt].ik.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* encode the AUTN */
	  SAddPstMsg(egIe->t.eSecCxtQdQt.authQuin[cnt].autnLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuin[cnt].autn.val, egIe->t.eSecCxtQdQt.authQuin[cnt].autn.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }
	}
	/* encode drx parameter - is of 2 octets */
   SAddPstMsgMult(egIe->t.eSecCxtQdQt.drxParam, EG_LEN_TWO, mBuf);

	/* encode next hop parameter - is of 32 octets */
   SAddPstMsgMult(egIe->t.eSecCxtQdQt.nxtHop, 32, mBuf);

	/* encode ncc parameter - is of 3 bits*/
   SAddPstMsg((egIe->t.eSecCxtQdQt.ncc)&0x07,mBuf);

  	/* encode upLink subscribed UE AMBR */
   EG_ENC_U32(egIe->t.eSecCxtQdQt.upSubsUEAMBR, mBuf);

	/* encode downLink subscribed UE AMBR */
   EG_ENC_U32(egIe->t.eSecCxtQdQt.dnSubsUEAMBR, mBuf);

	/* encode upLink used UE AMBR */
   EG_ENC_U32(egIe->t.eSecCxtQdQt.upUsedUEAMBR, mBuf);

	/* encode downLink used UE AMBR */
   EG_ENC_U32(egIe->t.eSecCxtQdQt.dnUsedUEAMBR, mBuf);

   /* here we are mandating the length of UE Ntwrk will be of 15 octets */
   egIe->t.eSecCxtQdQt.ueNtwrkCapb.length = EG_UE_NTWRK_CAPB_LEN;

   /* encode UE Network Capability - can be max of 15 octets */
   EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.ueNtwrkCapb.val, egIe->t.eSecCxtQdQt.ueNtwrkCapb.length, EG_LEN_SIXTEEN, retValue);

  /* here we are mandating the length of MS Ntwrk will be of 10 octets */
   egIe->t.eSecCxtQdQt.msNtwrkCapb.length = EG_MS_NTWRK_CAPB_LEN;

   /* encode MS Network Capability - can be max of 10 octets */
   EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.msNtwrkCapb.val, egIe->t.eSecCxtQdQt.msNtwrkCapb.length, EG_LEN_SIXTEEN, retValue);

   /* here we are mandating the length of MEID will be of 16 octets */
   egIe->t.eSecCxtQdQt.meId.length = EG_LEN_SIXTEEN;

   /* encode MEID - is of 16 octets */
   EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.meId.val, egIe->t.eSecCxtQdQt.meId.length, EG_LEN_SIXTEEN, retValue);

	tmpByte = 0;

	tmpByte = egIe->t.eSecCxtQdQt.isUNA * EG_MASK_BIT1;
	tmpByte |= egIe->t.eSecCxtQdQt.isGENA * EG_MASK_BIT2;
	tmpByte |= egIe->t.eSecCxtQdQt.isGANA * EG_MASK_BIT3;
	tmpByte |= egIe->t.eSecCxtQdQt.isINA * EG_MASK_BIT4;
	tmpByte |= egIe->t.eSecCxtQdQt.isENA * EG_MASK_BIT5;
	tmpByte |= egIe->t.eSecCxtQdQt.isHNNA * EG_MASK_BIT6;
	SAddPstMsg(tmpByte, mBuf);

	tmpByte = egIe->t.eSecCxtQdQt.nccOld & 0x07;
	tmpByte |= (egIe->t.eSecCxtQdQt.ksiOld & 0x07)<< EG_SHIFT_2;
	tmpByte |= (egIe->t.eSecCxtQdQt.isNHIOldPres * EG_MASK_BIT8);
	SAddPstMsg(tmpByte, mBuf);

  /* encode Kasme_old of 32 octets */
   egIe->t.eSecCxtQdQt.kasmeOld.length = EG_KASME_LEN;
   EG_ENC_STR(mBuf, egIe->t.eSecCxtQdQt.kasmeOld.val, egIe->t.eSecCxtQdQt.kasmeOld.length, EG_LEN_32, retValue);

	/* encode next hop_old parameter - is of 32 octets */
   SAddPstMsgMult(egIe->t.eSecCxtQdQt.nxtHopOld, 32, mBuf);

#ifdef EG_REL_930
   /* encode Voice Domain Preference and UE's usage Setting length */
	SAddPstMsg( egIe->t.eSecCxtQdQt.vDomPrefUEUsageLen, mBuf);
   
	/* encode UE's usage setting (1 bit field) Bit-3
	 * encode Voice  domain prefernce for E-UTRAN(2 bit field) Bit 2 and 1 */
	if(egIe->t.eSecCxtQdQt.vDomPrefUEUsageLen)
	{
	  tmpByte = 0;
	  tmpByte = egIe->t.eSecCxtQdQt.ueUsageSett * EG_MASK_BIT1;
	  tmpByte <<= EG_SHIFT_2;
	  tmpByte |= egIe->t.eSecCxtQdQt.vDomPref && 0x03;

	  SAddPstMsg(tmpByte , mBuf);
	}
#endif /* EG_REL_930 */

   RETVALUE(retValue);
} /* end of egAcEncEG_EPS_SEC_QUAD_QUIN */


/***********************************************************************
 *   Fun:   egAcEncEG_UMTS_KEY_QUAD_QUIN
 *   Desc:  Encodes the IE data type UMTS Key, Quadruplets and Quintuplets
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_UMTS_KEY_QUAD_QUIN
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_UMTS_KEY_QUAD_QUIN(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 cnt = 0;
   S16 retValue = ROK;
	U8  tmpByte = 0x00;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_UMTS_KEY_QUAD_QUIN)

	tmpByte = ((egIe->t.umtsKeyQdQt.secMode & 0x07) << EG_SHIFT_5) | 
		 (egIe->t.umtsKeyQdQt.isDRXIPres * EG_MASK_BIT4) | (egIe->t.umtsKeyQdQt.ksi & 0x07);
	SAddPstMsg(tmpByte, mBuf);

	tmpByte = 0x00;
	tmpByte = (((egIe->t.umtsKeyQdQt.nmbQuin & 0x07) << EG_SHIFT_5) |
		 ((egIe->t.umtsKeyQdQt.nmbQuadru & 0x03) << EG_SHIFT_2) |
		 (egIe->t.umtsKeyQdQt.isUAMBRIPres * EG_MASK_BIT2) |
		 (egIe->t.umtsKeyQdQt.isSAMBRIPres * EG_MASK_BIT1));
	SAddPstMsg(tmpByte, mBuf);

  /* 7th one is spare octect */
	tmpByte = 0x00;
   SAddPstMsg(tmpByte , mBuf);

   /* mandate the length as 16 octets */
   egIe->t.umtsKeyQdQt.ck.length = EG_LEN_SIXTEEN;
   egIe->t.umtsKeyQdQt.ik.length = EG_LEN_SIXTEEN;

   /* encode CK, IK each of 16 octets */
   EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.ck.val, egIe->t.umtsKeyQdQt.ck.length, EG_LEN_SIXTEEN, retValue);
   EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.ik.val, egIe->t.umtsKeyQdQt.ik.length, EG_LEN_SIXTEEN, retValue);

	for(cnt=0;cnt < egIe->t.umtsKeyQdQt.nmbQuadru;cnt++)
	{
	  /* mandate the length as 16 octets */
	  egIe->t.umtsKeyQdQt.authQuadru[cnt].rand.length = EG_LEN_SIXTEEN;

	  /* encode the RAND which is of 16 octets*/
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuadru[cnt].rand.val, egIe->t.umtsKeyQdQt.authQuadru[cnt].rand.length, EG_LEN_SIXTEEN, retValue);

	  /* encode the XRES length in single octet and XRES which can be of 16 octets */
	  SAddPstMsg(egIe->t.umtsKeyQdQt.authQuadru[cnt].xresLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuadru[cnt].xres.val, egIe->t.umtsKeyQdQt.authQuadru[cnt].xresLen, EG_LEN_SIXTEEN, retValue);

	  /* encode the AUTN length in single octet and AUTH which can be of 16 octets */
	  SAddPstMsg(egIe->t.umtsKeyQdQt.authQuadru[cnt].autnLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuadru[cnt].autn.val, egIe->t.umtsKeyQdQt.authQuadru[cnt].autnLen, EG_LEN_SIXTEEN, retValue);

	  /* encode the Kasme which is of 31 octets */
	  egIe->t.umtsKeyQdQt.authQuadru[cnt].kasme.length = EG_KASME_LEN;
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuadru[cnt].kasme.val, egIe->t.umtsKeyQdQt.authQuadru[cnt].kasme.length, EG_LEN_32, retValue);
	}
	for(cnt=0;cnt<egIe->t.umtsKeyQdQt.nmbQuin;cnt++)
	{
	  /* mandate the length as 16 octets */
	  egIe->t.umtsKeyQdQt.authQuin[cnt].rand.length = EG_LEN_SIXTEEN;

	  /* encode the RAND which is of 16 octets*/
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuin[cnt].rand.val, egIe->t.umtsKeyQdQt.authQuin[cnt].rand.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* encode the XRES length in single octet and XRES which can be of 16 octets */
	  SAddPstMsg(egIe->t.umtsKeyQdQt.authQuin[cnt].xresLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuin[cnt].xres.val, egIe->t.umtsKeyQdQt.authQuin[cnt].xresLen, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* mandate the length as 16 octets */
	  egIe->t.umtsKeyQdQt.authQuin[cnt].ck.length = EG_LEN_SIXTEEN;
	  egIe->t.umtsKeyQdQt.authQuin[cnt].ik.length = EG_LEN_SIXTEEN;

	  /* encode the CK, IK each is of 16 octets length */
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuin[cnt].ck.val, egIe->t.umtsKeyQdQt.authQuin[cnt].ck.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuin[cnt].ik.val, egIe->t.umtsKeyQdQt.authQuin[cnt].ik.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }

	  /* encode the AUTN */
	  SAddPstMsg(egIe->t.umtsKeyQdQt.authQuin[cnt].autnLen, mBuf);
	  EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuin[cnt].autn.val, egIe->t.umtsKeyQdQt.authQuin[cnt].autn.length, EG_LEN_SIXTEEN, retValue);
	  if( retValue != ROK)
	  {
		 RETVALUE(retValue);
	  }
	}
	/* encode drx parameter - is of 2 octets */
   SAddPstMsgMult(egIe->t.umtsKeyQdQt.drxParam, EG_LEN_TWO, mBuf);

  	/* encode upLink subscribed UE AMBR */
   EG_ENC_U32(egIe->t.umtsKeyQdQt.upSubsUEAMBR, mBuf);

	/* encode downLink subscribed UE AMBR */
   EG_ENC_U32(egIe->t.umtsKeyQdQt.dnSubsUEAMBR, mBuf);

	/* encode upLink used UE AMBR */
   EG_ENC_U32(egIe->t.umtsKeyQdQt.upUsedUEAMBR, mBuf);

	/* encode downLink used UE AMBR */
   EG_ENC_U32(egIe->t.umtsKeyQdQt.dnUsedUEAMBR, mBuf);

   /* here we are mandating the length of UE Ntwrk will be of 15 octets */
   egIe->t.umtsKeyQdQt.ueNtwrkCapb.length = EG_UE_NTWRK_CAPB_LEN;

   /* encode UE Network Capability - can be max of 15 octets */
   EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.ueNtwrkCapb.val, egIe->t.umtsKeyQdQt.ueNtwrkCapb.length, EG_LEN_SIXTEEN, retValue);

  /* here we are mandating the length of MS Ntwrk will be of 10 octets */
   egIe->t.umtsKeyQdQt.msNtwrkCapb.length = EG_MS_NTWRK_CAPB_LEN;

   /* encode MS Network Capability - can be max of 10 octets */
   EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.msNtwrkCapb.val, egIe->t.umtsKeyQdQt.msNtwrkCapb.length, EG_LEN_SIXTEEN, retValue);

   /* here we are mandating the length of MEID will be of 16 octets */
   egIe->t.umtsKeyQdQt.meId.length = EG_LEN_SIXTEEN;

   /* encode MEID - is of 16 octets */
   EG_ENC_STR(mBuf, egIe->t.umtsKeyQdQt.meId.val, egIe->t.umtsKeyQdQt.meId.length, EG_LEN_SIXTEEN, retValue);

	tmpByte = 0;

	tmpByte = egIe->t.umtsKeyQdQt.isUNA * EG_MASK_BIT1;
	tmpByte |= egIe->t.umtsKeyQdQt.isGENA * EG_MASK_BIT2;
	tmpByte |= egIe->t.umtsKeyQdQt.isGANA * EG_MASK_BIT3;
	tmpByte |= egIe->t.umtsKeyQdQt.isINA * EG_MASK_BIT4;
	tmpByte |= egIe->t.umtsKeyQdQt.isENA * EG_MASK_BIT5;
	tmpByte |= egIe->t.umtsKeyQdQt.isHNNA * EG_MASK_BIT6;
	SAddPstMsg(tmpByte, mBuf);

#ifdef EG_REL_930
   /* encode Voice Domain Preference and UE's usage Setting length */
	SAddPstMsg( egIe->t.umtsKeyQdQt.vDomPrefUEUsageLen, mBuf);
   
	/* encode UE's usage setting (1 bit field) Bit-3
	 * encode Voice  domain prefernce for E-UTRAN(2 bit field) Bit 2 and 1 */
	if(egIe->t.umtsKeyQdQt.vDomPrefUEUsageLen)
	{
	  tmpByte = 0;
	  tmpByte = egIe->t.umtsKeyQdQt.ueUsageSett * EG_MASK_BIT1;
	  tmpByte <<= EG_SHIFT_2;
	  tmpByte |= egIe->t.umtsKeyQdQt.vDomPref && 0x03;

	  SAddPstMsg(tmpByte , mBuf);
	}
#endif /* EG_REL_930 */

   RETVALUE(retValue);
} /* end of egAcEncEG_UMTS_KEY_QUAD_QUIN */


/***********************************************************************
 *   Fun:   egAcEncEG_F_CAUSE
 *   Desc:  Encodes the IE data type F-Cause
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_F_CAUSE
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_F_CAUSE(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_F_CAUSE)

   /* encode the FCause Type */
	egIe->t.fCause.causeType = egIe->t.fCause.causeType & 0x0F;
   SAddPstMsg(egIe->t.fCause.causeType, mBuf);

   /* encode the FCause Value */
   EG_ENC_U16(egIe->t.fCause.cause, mBuf);

   RETVALUE(retValue);
} /* end of egAcEncEG_F_CAUSE */


/***********************************************************************
 *   Fun:   egAcEncEG_S103_PDN_FW_INFO
 *   Desc:  Encodes the IE data type S103 PDN Data Forwarding Info
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_S103_PDN_FW_INFO
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_S103_PDN_FW_INFO(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;
	U8  cnt;
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_S103_PDN_FW_INFO)

   /* encode the PSDN Address length */
	switch (egIe->t.s103PDF.hsgwAddr.type)
	{
	  case CM_TPTADDR_IPV4:
		 {
			/* in case of IPv4 encode length as 4 */
			egIe->t.s103PDF.hsgwAddrLen = 0x04;
			SAddPstMsg(egIe->t.s103PDF.hsgwAddrLen, mBuf);
			EG_ENC_U32(egIe->t.s103PDF.hsgwAddr.u.ipv4, mBuf);
			break;
		 } /* end of case */
#ifdef EG_IPV6_SUPPORTED
	  case CM_TPTADDR_IPV6:
		 {
			/* in case of IPv6 encode length as 16 */
			egIe->t.s103PDF.hsgwAddrLen = 0x10;
			SAddPstMsg(egIe->t.s103PDF.hsgwAddrLen, mBuf);
			SAddPstMsgMult(egIe->t.s103PDF.hsgwAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
			break;
		 } /* end of case */
#endif /* end of CM_TPTADDR_IPV6 */
	  default:
		 {
		 	RETVALUE(RFAILED);
		 } /* end of case */
	} /* end of switch */

   /* encode the GRE Key */
   EG_ENC_U32(egIe->t.s103PDF.greKey, mBuf);

   /* encode the EBI Number */
   SAddPstMsg(egIe->t.s103PDF.ebiNumber, mBuf);

   /* encode the Bearer Id - can be max of 10 octets */
	for(cnt = 0; cnt < egIe->t.s103PDF.ebiNumber && cnt < EG_MAX_NMB_BEARER;cnt++)
	{
	  SAddPstMsg(egIe->t.s103PDF.ebi[cnt] & 0x0F, mBuf);
	}

   RETVALUE(retValue);
} /* end of egAcEncEG_S103_PDN_FW_INFO */


/***********************************************************************
 *   Fun:   egAcEncEG_S1U_DATA_FW
 *   Desc:  Encodes the IE data type S1-U Data Forwarding
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_S1U_DATA_FW
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_S1U_DATA_FW(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_S1U_DATA_FW)

   SAddPstMsg(egIe->t.s1UDF.ebi & 0x0F, mBuf);

   /* encode the SGW Address length */
   switch (egIe->t.s1UDF.sgwAddr.type)
   {
      case CM_TPTADDR_IPV4:
      {
         /* in case of IPv4 encode length as 4 */
			egIe->t.s1UDF.sgwAddrLen = 0x04;
         SAddPstMsg(egIe->t.s1UDF.sgwAddrLen , mBuf);
         EG_ENC_U32(egIe->t.s1UDF.sgwAddr.u.ipv4, mBuf);
         break;
      } /* end of case */
#ifdef EG_IPV6_SUPPORTED
      case CM_TPTADDR_IPV6:
      {
         /* in case of IPv6 encode length as 16 */
			egIe->t.s1UDF.sgwAddrLen = 0x10;
         SAddPstMsg(egIe->t.s1UDF.sgwAddrLen , mBuf);
         SAddPstMsgMult(egIe->t.s1UDF.sgwAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
         break;
      } /* end of case */
#endif /* end of CM_TPTADDR_IPV6 */
		default:
		{
			RETVALUE(RFAILED);
		} /* end of case */
   } /* end of switch */

   /* encode the S1U-TEID */
   EG_ENC_U32(egIe->t.s1UDF.sgwS1UTEID, mBuf);

   RETVALUE(retValue);
} /* end of egAcEncEG_S1U_DATA_FW */


/***********************************************************************
 *   Fun:   egAcEncEG_SRC_RNC_PDCP_CTX
 *   Desc:  Encodes the IE data type Source RNC PDCP Context
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_SRC_RNC_PDCP_CTX
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_SRC_RNC_PDCP_CTX(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_SRC_RNC_PDCP_CTX)

   EG_ENC_STR(mBuf, egIe->t.valStr.val, egIe->t.valStr.length, EG_MAX_STR_LEN, retValue);

   RETVALUE(retValue);
} /* end of egAcEncEG_SRC_RNC_PDCP_CTX */


/***********************************************************************
 *   Fun:   egAcEncEG_PDUNUM
 *   Desc:  Encodes the IE data type PDU Number
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_PDUNUM
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_PDUNUM(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcEncEG_PDUNUM)

   /* encode NSAPI */
   SAddPstMsg(egIe->t.pduNum.nsapi, mBuf);

   /* encode the DownLink GTP-U Sequence Number */
   EG_ENC_U16(egIe->t.pduNum.dnLinkSeqNo, mBuf);

   /* encode the Uplink GTP-U Sequence Number */
   EG_ENC_U16(egIe->t.pduNum.upLinkSeqNo, mBuf);

   /* encode the Send N-PDU Number */
   EG_ENC_U16(egIe->t.pduNum.SNPduNo, mBuf);

   /* encode the Receive N-PDU Number */
   EG_ENC_U16(egIe->t.pduNum.RNPduNo, mBuf);

   RETVALUE(retValue);
} /* end of egAcEncEG_PDUNUM */

/***********************************************************************
 *   Fun:   egAcEncEG_UE_TIME_ZONE
 *   Desc:  Encodes the IE data type Time zone
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_UE_TIME_ZONE
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_UE_TIME_ZONE(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

   /* encode time zone */
   SAddPstMsg(egIe->t.timeZone.timezone, mBuf);
   /* encode day light savings time */
	egIe->t.timeZone.dayLiteSavTime = egIe->t.timeZone.dayLiteSavTime & 0x03;
   SAddPstMsg(egIe->t.timeZone.dayLiteSavTime, mBuf);
   RETVALUE(retValue);
}
/***********************************************************************
 *   Fun:   egAcEncEG_TRACE_REF
 *   Desc:  Encodes the IE data type trace reference
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_TRACE_REF
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_TRACE_REF(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

   /* encode snkw */
	EG_ENC_NETID(egIe->t.trcRef.sNwk,mBuf);
   /* encode trace id */
   EG_ENC_U32(egIe->t.trcRef.trcId, mBuf);
   RETVALUE(retValue);
}
/***********************************************************************
 *   Fun:   egAcEncEG_RAB_CONTEXT
 *   Desc:  Encodes the IE data type RAB Context
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_RAB_CONTEXT
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_RAB_CONTEXT(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

   /* encode nsapi */
	SAddPstMsg(egIe->t.rabCntxt.nsapi & 0x0F,mBuf);
	/* encode Downlink GTP-U Sequence Number */
	EG_ENC_U16(egIe->t.rabCntxt.dnlEgUSeqNo ,mBuf);
	/* encode Uplink GTP-U Sequence Number */
	EG_ENC_U16(egIe->t.rabCntxt.uplEgUSeqNo ,mBuf);
	/* Downlink GTP-U Sequence Number */
	EG_ENC_U16(egIe->t.rabCntxt.dnlPdcpSeqNo ,mBuf);
	/*  Uplink GTP-U Sequence Number */
	EG_ENC_U16(egIe->t.rabCntxt.uplPdcpSeqNo ,mBuf);

   RETVALUE(retValue);
}
/***********************************************************************
 *   Fun:   egAcEncEG_AMBR
 *   Desc:  Encodes the IE data type Aggregate Maximum Bit Rate
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_AMBR
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_AMBR(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

	/*encode APN-AMBR for uplink */
	EG_ENC_U32(egIe->t.ambr.uplAPNAMBR, mBuf);
	/* encode APN-AMBR for downlink */
	EG_ENC_U32(egIe->t.ambr.dnlAPNAMBR, mBuf);

   RETVALUE(retValue);
}
/***********************************************************************
 *   Fun:   egAcEncEG_GLOBAL_CN_ID
 *   Desc:  Encodes the IE data type Global CN Id
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_GLOBAL_CN_ID
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_GLOBAL_CN_ID(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

   /* Encode sNwk */
	EG_ENC_NETID(egIe->t.gblCnId.sNwk,mBuf);
	/* Encode cnId */
   EG_ENC_STR(mBuf, egIe->t.gblCnId.cnId.val, egIe->t.gblCnId.cnId.length, EG_LEN_FOUR, retValue);

   RETVALUE(retValue);
} /* egAcEncEG_GLOBAL_CN_ID */

#ifdef EG_REL_930
/***********************************************************************
 *   Fun:   egAcEncEG_MBMS_IPMCAST_DIST
 *   Desc:  Encodes the IE data type MBMS Multicast IP Distribution
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_MBMS_IPMCAST_DIST
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_MBMS_IPMCAST_DIST(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;

	/* encode Common Tunnel Endpoint Identifier Data */
	EG_ENC_U32(egIe->t.mbmsIPMCastDist.cteidDat, mBuf);

	/* encode IP Multicast Distribution Address Type */
	EG_ENC_U8(egIe->t.mbmsIPMCastDist.ipMCastDistAddr.type, mBuf);
	/* encode IP Multicast Distribution Address */
	switch (egIe->t.mbmsIPMCastDist.ipMCastDistAddr.type)
	{
	  case CM_TPTADDR_IPV4:
		 {
			EG_ENC_U32(egIe->t.mbmsIPMCastDist.ipMCastDistAddr.u.ipv4, mBuf);
			break;
		 } /* end of case */
#ifdef EG_IPV6_SUPPORTED
	  case CM_TPTADDR_IPV6:
		 {
			SAddPstMsgMult(egIe->t.mbmsIPMCastDist.ipMCastDistAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
			break;
		 } /* end of case */
#endif /* EG_IPV6_SUPPORTED */
	  default:
		 {
		 	RETVALUE(RFAILED);
		 } /* end of case */
	}

	/* encode  IP Multicast Source Address Type */
	EG_ENC_U8(egIe->t.mbmsIPMCastDist.ipMCastSrcAddr.type, mBuf);
	/* encode  IP Multicast Source Address */
	switch (egIe->t.mbmsIPMCastDist.ipMCastSrcAddr.type)
	{
	  case CM_TPTADDR_IPV4:
		 {
			EG_ENC_U32(egIe->t.mbmsIPMCastDist.ipMCastSrcAddr.u.ipv4, mBuf);
			break;
		 } /* end of case */
#ifdef EG_IPV6_SUPPORTED
	  case CM_TPTADDR_IPV6:
		 {
			SAddPstMsgMult(egIe->t.mbmsIPMCastDist.ipMCastSrcAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
			break;
		 } /* end of case */
#endif /* EG_IPV6_SUPPORTED */
	  default:
		 {
		 	RETVALUE(RFAILED);
		 } /* end of case */
	}

	/* encode MBMS HC Indicator */
	EG_ENC_U8(egIe->t.mbmsIPMCastDist.mbmsHCInd, mBuf);

   RETVALUE(retValue);
}

/***********************************************************************
 *   Fun:   egAcEncEG_UCI 
 *   Desc:  Encodes the IE data type user CSG information
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_UCI 
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_UCI(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;
	U8 tmpByte = 0x00;

   /* encode serving network */
   EG_ENC_NETID(egIe->t.uci.sNwk,mBuf);
	
	/* encode CSG Id values */
	/* CSG Id consists of 4 octets. Bit 3 of Octect 8 is the most significant bit and
	 * bit 1 of Octet 11 is the least significant bit
	 */
	egIe->t.uci.csgId &= 0x07FFFFFF;
	EG_ENC_U32(egIe->t.uci.csgId, mBuf);

	/* encode access mode */
	tmpByte = ( egIe->t.uci.accMode && 0x03) << 0x06;
	/* encode CMI */
	tmpByte |= egIe->t.uci.isCMIPres * EG_MASK_BIT1;
	/* encode LCSG */
	tmpByte |= egIe->t.uci.isLCSGPres * EG_MASK_BIT2;

	EG_ENC_U8(tmpByte, mBuf);

   RETVALUE(retValue);
}/* egAcEncEG_UCI */

/***********************************************************************
 *   Fun:   egAcEncEG_CSG_INFO_REP_ACT 
 *   Desc:  Encodes the IE data type CSG information reproting action
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcEncEG_CSG_INFO_REP_ACT 
(
EgIe   *egIe,
Buffer *mBuf
)
#else
PRIVATE S16 egAcEncEG_CSG_INFO_REP_ACT(egIe, mBuf)
EgIe   *egIe;
Buffer *mBuf;
#endif
{
   S16 retValue = ROK;
	U8 tmpByte = 0x00;

   /* encode UCICSG */
	tmpByte |= egIe->t.csgInfoReqAct.isUCICSGPres * EG_MASK_BIT1;
	/* encode UCISHC */
	tmpByte |= egIe->t.csgInfoReqAct.isUCISHCPres * EG_MASK_BIT2;
	/* encode UCIUHC */
	tmpByte |= egIe->t.csgInfoReqAct.isUCIUHCPres * EG_MASK_BIT3;

	EG_ENC_U8(tmpByte, mBuf);

   RETVALUE(retValue);
}/* egAcEncEG_CSG_INFO_REP_ACT */

#endif /* EG_REL_930 */

/***********************************************************************
 *   Fun:   egAcDecEG_UNSIGNED_8
 *   Desc:  Decodes the IE data type U8
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_UNSIGNED_8
(
EgIe* egIe,
Buffer *mBuf,
U16 ieLen
)
#else
PRIVATE S16 egAcDecEG_UNSIGNED_8(egIe,mBuf,ieLen)
EgIe* egIe;
Buffer *mBuf;
U16 ieLen;
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */

   SRemPreMsg(&egIe->t.valUnSgnd8, mBuf);
   RETVALUE(retVal);
} 
/***********************************************************************
 *   Fun:   egAcDecEG_UNSIGNED_16
 *   Desc:  Decodes the IE data type U16
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_UNSIGNED_16
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_UNSIGNED_16(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   EG_DEC_U16(egIe->t.valUnSgnd16, mBuf);
   RETVALUE(retVal);
} 
/***********************************************************************
 *   Fun:   egAcDecEG_UNSIGNED_32
 *   Desc:  Decodes the IE data type U32
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_UNSIGNED_32
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_UNSIGNED_32(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   EG_DEC_U32(egIe->t.valUnSgnd32, mBuf);
   RETVALUE(retVal);
}

/***********************************************************************
 *   Fun:   egAcDecEG_STRING_8
 *   Desc:  Decodes the IE data type string_8
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_STRING_8
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_STRING_8(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   egIe->t.valStr8.length = ieLen;
   EG_DEC_STR(mBuf, egIe->t.valStr8.val, egIe->t.valStr8.length, EG_LEN_EIGHT, retVal);
   RETVALUE(retVal);
}

/***********************************************************************
 *   Fun:   egAcDecEG_STRING_16
 *   Desc:  Decodes the IE data type STRING_16
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_STRING_16
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_STRING_16(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
    egIe->t.valStr16.length = ieLen;
    EG_DEC_STR(mBuf, egIe->t.valStr16.val, egIe->t.valStr16.length, EG_LEN_SIXTEEN, retVal);
    RETVALUE(retVal);
}

/***********************************************************************
 *   Fun:   egAcDecEG_STRING_32
 *   Desc:  Decodes the IE  data type STRING_32
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_STRING_32
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_STRING_32(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   egIe->t.valStr32.length = ieLen;
   EG_DEC_STR(mBuf, egIe->t.valStr32.val, egIe->t.valStr32.length, EG_LEN_32, retVal);
   RETVALUE(retVal);
}

/***********************************************************************
 *   Fun:   egAcDecEG_STRING_132
 *   Desc:  Decodes the IE data type STRING_132
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_STRING_132
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_STRING_132(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   egIe->t.valStr132.length = ieLen;
   EG_DEC_STR(mBuf, egIe->t.valStr132.val, egIe->t.valStr132.length, EG_LEN_132, retVal);
   RETVALUE(retVal);
}

/***********************************************************************
 *   Fun:   egAcDecEG_STRING_MAX
 *   Desc:  Decodes the IE data type STRING_MAX
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_STRING_MAX
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_STRING_MAX(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   egIe->t.valStr.length = ieLen;
   EG_DEC_STR(mBuf, egIe->t.valStr.val, egIe->t.valStr.length, EG_MAX_STR_LEN, retVal);
   RETVALUE(retVal);
}


/***********************************************************************
 *   Fun:   egAcDecEG_SNETWORK
 *   Desc:  Decodes the IE data type SNETWORK
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_SNETWORK
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_SNETWORK(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   EG_DEC_NETID(egIe->t.sNwk,mBuf);
   RETVALUE(retVal);
 }

/***********************************************************************
 *   Fun:   egAcDecEG_INDICATION
 *   Desc:  Decodes the IE data type INDICATION
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_INDICATION
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_INDICATION(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   Data     dumBytes[EG_MAX_BYTES];
   SRemPreMsgMult(dumBytes, EG_LEN_TWO, mBuf);
   egIe->t.indication.isSGWCIPres = ((dumBytes[0] & EG_MASK_BIT1) > 0)?1:0;
   egIe->t.indication.isISRAIPres = ((dumBytes[0] & EG_MASK_BIT2) > 0)?1:0;
   egIe->t.indication.isISRSIPres = ((dumBytes[0] & EG_MASK_BIT3) > 0)?1:0;
   egIe->t.indication.isOIPres = ((dumBytes[0] & EG_MASK_BIT4) > 0)?1:0;
   egIe->t.indication.isDFIPres = ((dumBytes[0] & EG_MASK_BIT5) > 0)?1:0;
   egIe->t.indication.isHIPres = ((dumBytes[0] & EG_MASK_BIT6) > 0)?1:0;
   egIe->t.indication.isDTFPres = ((dumBytes[0] & EG_MASK_BIT7) > 0)?1:0;
   egIe->t.indication.isDAFPres = ((dumBytes[0] & EG_MASK_BIT8) > 0)?1:0;
   egIe->t.indication.isMSVPres = ((dumBytes[1] & EG_MASK_BIT1) > 0)?1:0;
   egIe->t.indication.isSIPres = ((dumBytes[1] & EG_MASK_BIT2) > 0)?1:0;
   egIe->t.indication.isPTPres = ((dumBytes[1] & EG_MASK_BIT3) > 0)?1:0;
   egIe->t.indication.isPPres = ((dumBytes[1] & EG_MASK_BIT4) > 0)?1:0;
   egIe->t.indication.isCRSIPres = ((dumBytes[1] & EG_MASK_BIT5) > 0)?1:0;
   egIe->t.indication.isCFSIPres = ((dumBytes[1] & EG_MASK_BIT6) > 0)?1:0;
   /***************************************************
    * Check whether the reserved bits are used or not *
   ***************************************************/
   if( dumBytes[1] & 0xC0)
   {
      /* Send the error */
     retVal = EGT_ERR_INV_IE_VAL;

   }
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcDecEG_CAUSE   
 *   Desc:  Decodes the IE data type EMB CAUSE
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_CAUSE
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_CAUSE(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */

	/* decode cause value */
   SRemPreMsg(&egIe->t.cause.causeVal, mBuf);
	/* decode cause source */
   SRemPreMsg(&egIe->t.cause.ieCS, mBuf);
	egIe->t.cause.ieCS = egIe->t.cause.ieCS & 0x01;

  /* decode offending IE type */
   SRemPreMsg(&egIe->t.cause.ieType, mBuf);

  /* decode offending IE legth */
   EG_DEC_U16(egIe->t.cause.ieLength, mBuf);

  /* decode offending IE legth */
   SRemPreMsg(&egIe->t.cause.ieInst, mBuf);
   egIe->t.cause.ieInst = egIe->t.cause.ieInst & EG_MASK_LOW4;

   RETVALUE(retVal);

}
/***********************************************************************
 *   Fun:   egAcDecEG_PVT_EXTN
 *   Desc:  Decodes the IE data type PVT EXTN
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_PVT_EXTN
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_PVT_EXTN(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   EG_DEC_U16(egIe->t.pvtExt.entId, mBuf);
   /* call the EgStr132 for decoding the remaining bytes to prop val */
   egIe->t.pvtExt.propVal.length = ieLen-2;
   EG_DEC_STR( mBuf, egIe->t.pvtExt.propVal.val,  egIe->t.pvtExt.propVal.length, EG_LEN_132, retVal);
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcDecEG_TRC_INFO
 *   Desc:  Decodes the IE data type TRC INFO
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_TRC_INFO
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_TRC_INFO(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{

   S16 retVal = ROK; /* Return value used to know the successful parsing */

   EG_DEC_NETID(egIe->t.trcInfo.sNwk,mBuf);
	EG_DEC_U32(egIe->t.trcInfo.trcId, mBuf);
	SRemPreMsgMult(egIe->t.trcInfo.trigEvnts,EG_LEN_NINE, mBuf);
	EG_DEC_U16(egIe->t.trcInfo.lstNETypes, mBuf);
	EG_DEC_U8(egIe->t.trcInfo.sesnTrcDep, mBuf);
/*************************************
 * eg009.201 - Added for S2B and S2A *
 *************************************/
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
	SRemPreMsgMult(egIe->t.trcInfo.trigEvnts,EG_LEN_TWELVE, mBuf);
#else
	EG_DEC_U16(egIe->t.trcInfo.lstOfIntfs, mBuf);
#endif


  egIe->t.trcInfo.trcColEntAddr.type = (ieLen == 4) ? CM_TPTADDR_IPV4 : CM_TPTADDR_IPV6;

   switch (egIe->t.trcInfo.trcColEntAddr.type)
   {
      case CM_TPTADDR_IPV4:
      {
         EG_DEC_U32(egIe->t.trcInfo.trcColEntAddr.u.ipv4, mBuf);
         break;
      } /* end of case */
#ifdef EG_IPV6_SUPPORTED
      case CM_TPTADDR_IPV6:
      {
         SRemPreMsgMult(egIe->t.trcInfo.trcColEntAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
         break;
      } /* end of case */
#endif /* EG_IPV6_SUPPORTED */
      default:
      {
			RETVALUE(RFAILED);
      } /* end of case */
   }

   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcDecEG_BEARER_FLAG
 *   Desc:  Decodes the IE data type BEARER FLAG
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_BEARER_FLAG
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_BEARER_FLAG(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   U8       tmpByte = 0;         /* Holds 1 byte of data for decoding  */

   SRemPreMsg(&tmpByte, mBuf);
   egIe->t.bearFlags.isPPCPres = tmpByte & EG_MASK_BIT1;
   egIe->t.bearFlags.isVBPres = tmpByte & EG_MASK_BIT2;
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcDecEG_FTEID
 *   Desc:  Decodes the IE data type FTEID
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/

#ifdef ANSI
PRIVATE S16 egAcDecEG_FTEID
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_FTEID(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{

   S16 retVal = ROK; /* Return value used to know the successful parsing */
   U8       tmpByte = 0;         /* Holds 1 byte of data for decoding  */
   Data     dumBytes[EG_MAX_BYTES]; /* Holds the Data for decoding */

   /*************************************
   * F-TEID  Ie is having the fields:    *
   * one octet: 1-5bits intfType         *
   * one octet: 6th bit EBIF pres        *
   * one octet: 7th bit V6 pres          *
   * one octet: 8th bit V4 pres          *
   * four octets of TEID value           *
   * if 7th bit is set then ipv6 addr    *
   * else 8th bit is set then ipv4 addr  *
   * ************************************/
   SRemPreMsg(&tmpByte,mBuf);
   ieLen -= 1;
   egIe->t.fTeid.intfType = tmpByte & EG_MASK_FTEID_INTFTYPE;
   EG_DEC_U32(egIe->t.fTeid.teid, mBuf);
   ieLen -= 4;
   if(tmpByte & EG_MASK_BIT7)
   {
      /* decode the IPV6 address */
      egIe->t.fTeid.isIPv4Pres = FALSE;
      egIe->t.fTeid.isIPv6Pres = TRUE;
      SRemPreMsgMult(egIe->t.fTeid.u.ipv6Address, EG_LEN_SIXTEEN, mBuf);
      ieLen -= 16;   /* IPV6 is of 16bytes and 1Dece is for 1st octet */
   }
   else if(tmpByte & EG_MASK_BIT8)
   {
      /* decode the ipv4 address */
      egIe->t.fTeid.isIPv4Pres = TRUE;
      egIe->t.fTeid.isIPv6Pres = FALSE;
      SRemPreMsgMult(egIe->t.fTeid.u.ip4Addr, EG_LEN_FOUR, mBuf);
      ieLen -= 4;   /* IPV4 is of 4bytes and 1byte is for 1st octet */
   }
   /***********************************************
    * Check if there are any spare bits remove it *
    ***********************************************/
   if( ieLen)
   {
      SRemPreMsgMult(dumBytes, ieLen, mBuf);
   }
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcDecEG_ULI_DATA 
 *   Desc:  Decodes the IE data type ULI
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_ULI_DATA
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_ULI_DATA(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   U8  tmpByte = 0;         /* Holds 1 byte of data for decoding  */

   SRemPreMsg(&tmpByte,mBuf);
   /* Check if the CGI presence is there or not */
   if(tmpByte & EG_MASK_BIT1)
   {
      /* decode the MCC,MNC,LAC,CI fields */
      EG_DEC_NETID(egIe->t.uli.cgi.sNwk,mBuf);
      EG_DEC_U16(egIe->t.uli.cgi.lac,mBuf);
      EG_DEC_U16(egIe->t.uli.cgi.ci,mBuf);
      egIe->t.uli.isCGIPres = TRUE;
   }
   /* Check if the SAI presence is there or not */
   if(tmpByte & EG_MASK_BIT2)
   {
      /* decode the MCC,MNC,LAC,SAI fields */
      EG_DEC_NETID(egIe->t.uli.sai.sNwk,mBuf);
      EG_DEC_U16(egIe->t.uli.sai.lac,mBuf);
      EG_DEC_U16(egIe->t.uli.sai.sac,mBuf);
      egIe->t.uli.isSAIPres = TRUE;
   }
   /* Check if the RAI presence is there or not */
   if(tmpByte & EG_MASK_BIT3)
   {
      /* decode the MCC,MNC,LAC,RAI fields */
      EG_DEC_NETID(egIe->t.uli.rai.sNwk,mBuf);
      EG_DEC_U16(egIe->t.uli.rai.lac,mBuf);
      EG_DEC_U16(egIe->t.uli.rai.rac,mBuf);
      egIe->t.uli.isRAIPres = TRUE;
   }
   /* Check if the TAI presence is there or not */
   if(tmpByte & EG_MASK_BIT4)
   {
      /* decode the MCC,MNC,TAC fields */
      EG_DEC_NETID(egIe->t.uli.tai.sNwk,mBuf);
      EG_DEC_U16(egIe->t.uli.tai.tac,mBuf);
      egIe->t.uli.isTAIPres = TRUE;
   }
   /**********************************************
    * Check if the ECGI presence is there or not *
    **********************************************/
   if(tmpByte & EG_MASK_BIT5)
   {
      /* decode the MCC,MNC,ECGI fields */
      EG_DEC_NETID(egIe->t.uli.ecgi.sNwk,mBuf);
      EG_DEC_U32(egIe->t.uli.ecgi.ecId, mBuf);
      /**************************************
      * EG_MASK_ECI:mask value  0x0fffffff  *
      ***************************************/
      egIe->t.uli.ecgi.ecId &=  EG_MASK_ECI;
      egIe->t.uli.isECGIPres = TRUE;
   }
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcDecEG_FQOS
 *   Desc:  Decodes the IE data type FQOS
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_FQOS
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_FQOS(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   Data     dumBytes[EG_MAX_BYTES]; /* Holds the Data for decoding */
   EG_DEC_FQOS((&egIe->t.fQos), mBuf);
   /* calculate the remaining IE */
   ieLen -= EG_QOS_LEN;
   if(ieLen)
   {
      /* remove the remaining spare bits */
      SRemPreMsgMult(dumBytes,ieLen, mBuf);
   }
   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcDecEG_BQOS_IEDATA
 *   Desc:  Decodes the IE data type BQOS 
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/

#ifdef ANSI
PRIVATE S16 egAcDecEG_BQOS_IEDATA
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_BQOS_IEDATA(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
	U8  tmpByte = 0;
	Data dumBytes[EG_MAX_BYTES]; /* Holds the Data for decoding */


   SRemPreMsg(&tmpByte,mBuf);

   egIe->t.bQos.isPVIPres = tmpByte & EG_MASK_BIT1;
	egIe->t.bQos.isPCIPres = tmpByte & EG_MASK_BIT7;

	tmpByte >>= EG_SHIFT_2; /* Right shift twice */
	egIe->t.bQos.prityLvl = tmpByte & 0x0F;

	SRemPreMsg(&egIe->t.bQos.qci,mBuf);
	SRemPreMsgMult(egIe->t.bQos.upMBR.val, EG_LEN_FIVE, mBuf);
	SRemPreMsgMult(egIe->t.bQos.dnMBR.val, EG_LEN_FIVE, mBuf);
	SRemPreMsgMult(egIe->t.bQos.upGBR.val, EG_LEN_FIVE, mBuf);
	SRemPreMsgMult(egIe->t.bQos.dnGBR.val, EG_LEN_FIVE, mBuf);
	ieLen -= 22;
   if(ieLen)
   {
      /* remove the remaining spare bits */
      SRemPreMsgMult(dumBytes,ieLen, mBuf);
   }

   RETVALUE(retVal);
}
/***********************************************************************
 *   Fun:   egAcDecEG_PAA_IEDATA
 *   Desc:  Decodes the IE data type PAA
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_PAA_IEDATA
(
EgIe* egIe,        /* Ie to store the decoded IE data */
Buffer *mBuf,      /* Holds the Data for decoding */
U16 ieLen          /* Ie Length to decode */
)
#else
PRIVATE S16 egAcDecEG_PAA_IEDATA(egIe,mBuf,ieLen)
EgIe* egIe;        /* Ie to store the decoded IE data */
Buffer *mBuf;      /* Holds the Data for decoding */
U16 ieLen;         /* Ie Length to decode */
#endif
{
   S16 retVal = ROK; /* Return value used to know the successful parsing */
   SRemPreMsg(&egIe->t.paa.pdnType, mBuf);
   /* mask the high 4 bits as pdn type 4bits */
   egIe->t.paa.pdnType = egIe->t.paa.pdnType & EG_MASK_LOW4;
   switch(egIe->t.paa.pdnType)
   {
      case 1:
      {
        /**************************************************************
         * if the pdn type is 1, then the pdn address is of type Ipv4 *
         * decode the ipv4 address which is of 4 octets length        *
         **************************************************************/
         egIe->t.paa.pdnPrefix =0;
         SRemPreMsgMult(egIe->t.paa.u.pdnIpv4Addr, EG_LEN_FOUR, mBuf);
         break;
      }
      case 2:
      {
        /******************************************************************
         * If the pdnType is 2, then first octet will tell the pdn prifix *
         * next 16octets will tell the ipv6 address                       *
         ******************************************************************/
         SRemPreMsg(&egIe->t.paa.pdnPrefix,mBuf);
         SRemPreMsgMult(egIe->t.paa.u.pdnIpv6Addr, EG_LEN_SIXTEEN, mBuf);
         break;
      }
      case 3:
      {
        /******************************************************************
         * If the pdnType is 3, then first octet will tell the pdn prifix *
         * next 16octets will be the ipv6 address                         *
         * next 4 octets will be the ipv4 address                         *
         ******************************************************************/
         SRemPreMsg(&egIe->t.paa.pdnPrefix,mBuf);
         SRemPreMsgMult(egIe->t.paa.u.pdnBoth.pdnIpv6Addr, EG_LEN_SIXTEEN, mBuf);
         SRemPreMsgMult(egIe->t.paa.u.pdnBoth.pdnIpv4Addr, EG_LEN_FOUR, mBuf);
         break;
      }
      default:
     {
         /* Invalid length */
         retVal = EGT_ERR_IE_INV_LEN;
         break;
      }
   }
   RETVALUE(retVal);
}


/***********************************************************************
 *   Fun:   egAcDecEG_AUTH_QUIN
 *   Desc:  Decodes the IE data type Authentication Quintuplet
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_AUTH_QUIN
(
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
)
#else
PRIVATE S16 egAcDecEG_AUTH_QUIN(egIe, mBuf, ieLen)
EgIe       *egIe;
Buffer     *mBuf;
U16        ieLen;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_AUTH_QUIN)

   /* Decode the RAND which is of 16 octets*/
   egIe->t.authQt.rand.length = EG_LEN_SIXTEEN;
   EG_DEC_STR(mBuf, egIe->t.authQt.rand.val, egIe->t.authQt.rand.length, EG_LEN_SIXTEEN, retValue);

   /* decode the XRES length in single octet and XRES which can be of 16 octets */
   SRemPreMsg(&egIe->t.authQt.xresLen, mBuf);
   EG_DEC_STR(mBuf, egIe->t.authQt.xres.val, egIe->t.authQt.xresLen, EG_LEN_SIXTEEN, retValue);

   /* decode the CK, IK each is of 16 octets length */
   egIe->t.authQt.ck.length = EG_LEN_SIXTEEN;
   EG_DEC_STR(mBuf, egIe->t.authQt.ck.val, egIe->t.authQt.ck.length, EG_LEN_SIXTEEN, retValue);
   egIe->t.authQt.ik.length = EG_LEN_SIXTEEN;
   EG_DEC_STR(mBuf, egIe->t.authQt.ik.val, egIe->t.authQt.ik.length, EG_LEN_SIXTEEN, retValue);

   /* decode the AUTN */
   SRemPreMsg(&egIe->t.authQt.autnLen, mBuf);
   EG_DEC_STR(mBuf, egIe->t.authQt.autn.val, egIe->t.authQt.autnLen, EG_LEN_SIXTEEN, retValue);

   RETVALUE(ROK);
} /* end of egAcDecEG_AUTH_QUIN */


/***********************************************************************
 *   Fun:   egAcDecEG_AUTH_QUAD
 *   Desc:  Decodes the IE data type Authentication Quadruplet
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_AUTH_QUAD
(
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
)
#else
PRIVATE S16 egAcDecEG_AUTH_QUAD(egIe, mBuf, ieLen)
EgIe       *egIe;
Buffer     *mBuf;
U16        ieLen;
#endif
{
   S16 retValue = ROK;
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_AUTH_QUAD)
 	
   /* decode the RAND which is of 16 octets*/
   egIe->t.quadruplet.rand.length = EG_LEN_SIXTEEN;
   EG_DEC_STR(mBuf, egIe->t.quadruplet.rand.val, egIe->t.quadruplet.rand.length, EG_LEN_SIXTEEN, retValue);

   /* decode the XRES length in single octet and XRES which can be of 16 octets */
   SRemPreMsg(&egIe->t.quadruplet.xresLen, mBuf);
   EG_DEC_STR(mBuf, egIe->t.quadruplet.xres.val, egIe->t.quadruplet.xresLen, EG_LEN_SIXTEEN, retValue);

   /* decode the AUTN length in single octet and AUTH which can be of 16 octets */
   SRemPreMsg(&egIe->t.quadruplet.autnLen, mBuf);
   EG_DEC_STR(mBuf, egIe->t.quadruplet.autn.val, egIe->t.quadruplet.autnLen, EG_LEN_SIXTEEN, retValue);

   /* decode the Kasme which is of 31 octets */
   egIe->t.quadruplet.kasme.length = EG_KASME_LEN;
   EG_DEC_STR(mBuf, egIe->t.quadruplet.kasme.val, egIe->t.quadruplet.kasme.length, EG_LEN_32, retValue);

   RETVALUE(ROK);
} /* end of egAcDecEG_AUTH_QUAD */


/***********************************************************************
 *   Fun:   egAcDecEG_CMP_REQ
 *   Desc:  Decodes the IE data type Complete Request Message
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_CMP_REQ
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_CMP_REQ(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_CMP_REQ)

   /* decode the CRM Type */
   SRemPreMsg(&egIe->t.crm.crmType, mBuf);

   /* decode the CRM Value */
   egIe->t.crm.crm.length = ieLen - 1;
   EG_DEC_STR(mBuf, egIe->t.crm.crm.val, egIe->t.crm.crm.length, EG_MAX_STR_LEN, retValue);

   RETVALUE(retValue);
} /* end of egAcDecEG_CMP_REQ */


/***********************************************************************
 *   Fun:   egAcDecEG_GUTI
 *   Desc:  Decodes the IE data type GUTI
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_GUTI
(
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
)
#else
PRIVATE S16 egAcDecEG_GUTI(egIe, mBuf, ieLen)
EgIe       *egIe;
Buffer     *mBuf;
U16        ieLen;
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_GUTI)

   /* decode the NETID */
   EG_DEC_NETID(egIe->t.guti.sNwk,mBuf);
   EG_DEC_U16(egIe->t.guti.mmeGrpId, mBuf);
   SRemPreMsg(&egIe->t.guti.mmeCode, mBuf);
   EG_DEC_U32(egIe->t.guti.mTmsi, mBuf);

   RETVALUE(ROK);
} /* end of egAcDecEG_GUTI */


/***********************************************************************
 *   Fun:   egAcDecEG_F_CONT
 *   Desc:  Decodes the IE data type F-Container
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_F_CONT
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_F_CONT(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_F_CONT)
      
   /* decode the container type */
   SRemPreMsg(&egIe->t.fContainer.containerType, mBuf);

   egIe->t.fContainer.fContainer.length = ieLen - 1;
   EG_DEC_STR(mBuf, egIe->t.fContainer.fContainer.val, egIe->t.fContainer.fContainer.length, EG_LEN_32, retValue);

   RETVALUE(retValue);
} /* end of egAcDecEG_F_CONT */


/***********************************************************************
 *   Fun:   egAcDecEG_TRGTID
 *   Desc:  Decodes the IE data type Target Id
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_TRGTID
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_TRGTID(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_TRGTID)

   /* decode the target type */
   SRemPreMsg(&egIe->t.targetId.targetType, mBuf);

   egIe->t.targetId.targetId.length = ieLen - 1;
   EG_DEC_STR(mBuf, egIe->t.targetId.targetId.val, egIe->t.targetId.targetId.length, EG_LEN_EIGHT, retValue);

   RETVALUE(retValue);
} /* end of egAcDecEG_TRGTID */


/***********************************************************************
 *   Fun:   egAcDecEG_PKTFLOWID
 *   Desc:  Decodes the IE data type Packet Flow Id
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_PKTFLOWID
(
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
)
#else
PRIVATE S16 egAcDecEG_PKTFLOWID(egIe, mBuf, ieLen)
EgIe       *egIe;
Buffer     *mBuf;
U16        ieLen;
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_PKTFLOWID)

   /* decode the EBI */
   SRemPreMsg(&egIe->t.pktFlowId.ebi, mBuf);
	egIe->t.pktFlowId.ebi &= 0x0F;
   SRemPreMsg(&egIe->t.pktFlowId.pktFlowId, mBuf);

   RETVALUE(ROK);
} /* end of egAcDecEG_PKTFLOWID */


/***********************************************************************
 *   Fun:   egAcDecEG_SRCID
 *   Desc:  Decodes the IE data type Cell Id
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_SRCID
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_SRCID(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;

   egIe->t.srcId.targetCellId.length = EG_LEN_EIGHT;

   EG_DEC_STR(mBuf, egIe->t.srcId.targetCellId.val, egIe->t.srcId.targetCellId.length, EG_LEN_EIGHT, retValue);

   SRemPreMsg(&egIe->t.srcId.sourceType, mBuf);

   egIe->t.srcId.sourceId.length = ieLen - 9;
   EG_DEC_STR(mBuf, egIe->t.srcId.sourceId.val, egIe->t.srcId.sourceId.length, EG_LEN_SIXTEEN, retValue);

   RETVALUE(retValue);
} /* end of egAcDecEG_SRCID */

/***********************************************************************
 *   Fun:   egAcDecEG_GLOBAL_CNID
 *   Desc:  Decodes the IE data type Global CN Id
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_GLOBAL_CNID
(
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
)
#else
PRIVATE S16 egAcDecEG_GLOBAL_CNID(egIe, mBuf, ieLen)
EgIe       *egIe;
Buffer     *mBuf;
U16        ieLen;
#endif
{
   S16 retValue = ROK;

   EG_DEC_NETID(egIe->t.gblCnId.sNwk,mBuf);

   egIe->t.gblCnId.cnId.length = ieLen - 3;
   EG_DEC_STR(mBuf, egIe->t.gblCnId.cnId.val, egIe->t.gblCnId.cnId.length, EG_LEN_FOUR, retValue);

   RETVALUE(retValue);
} /* end of egAcDecEG_GLOBAL_CNID */


/***********************************************************************
 *   Fun:   egAcDecEG_PDN_CONN_SET_ID
 *   Desc:  Decodes the IE data type PDN Connection Set Identifier
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_PDN_CONN_SET_ID
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_PDN_CONN_SET_ID(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;
	Data dumBytes[EG_MAX_BYTES];

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_PDN_CONN_SET_ID)

	SRemPreMsg(&dumBytes[0], mBuf);
	ieLen -= 1;
	egIe->t.csid.noOfCSIDs = dumBytes[0] & 0x0F;
	egIe->t.csid.nodeIdType = ((dumBytes[0] & 0xF0) >> EG_SHIFT_4);

	switch(egIe->t.csid.nodeIdType)
	{
	  case 0:
		 {
			egIe->t.csid.nodeId.length = EG_LEN_FOUR;
			EG_DEC_STR(mBuf, egIe->t.csid.nodeId.val, egIe->t.csid.nodeId.length,EG_LEN_SIXTEEN , retValue);
			ieLen -= EG_LEN_FOUR;
		 }
		 break;
	  case 1:
		 {
			egIe->t.csid.nodeId.length = EG_LEN_SIXTEEN;
			EG_DEC_STR(mBuf, egIe->t.csid.nodeId.val, egIe->t.csid.nodeId.length, EG_LEN_SIXTEEN, retValue);
			ieLen -= EG_LEN_SIXTEEN;
		 }
		 break;
	  case 2:
		 {
			egIe->t.csid.nodeId.length = EG_LEN_FOUR;
			EG_DEC_STR(mBuf, egIe->t.csid.nodeId.val, egIe->t.csid.nodeId.length, EG_LEN_SIXTEEN, retValue);
			ieLen -= EG_LEN_FOUR;
		 }
		 break;
	  default:
		 retValue = RFAILED;
		 EG_RETVALUE(retValue);
	}

	egIe->t.csid.csid.length = egIe->t.csid.noOfCSIDs * 0x02;
	EG_DEC_STR(mBuf, egIe->t.csid.csid.val, egIe->t.csid.csid.length, EG_LEN_SIXTEEN, retValue);
	ieLen -= egIe->t.csid.csid.length;

	if(ieLen)
	{
	  /* remove the remaining spare bits */
	  SRemPreMsgMult(dumBytes,ieLen, mBuf);
	}
	RETVALUE(retValue);
} /* end of egAcDecEG_PDN_CONN_SET_ID */


/***********************************************************************
 *   Fun:   egAcDecEG_IP_ADDR
 *   Desc:  Decodes the IE data type IP Address
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_IP_ADDR
(
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
)
#else
PRIVATE S16 egAcDecEG_IP_ADDR(egIe, mBuf, ieLen)
EgIe       *egIe;
Buffer     *mBuf;
U16        ieLen;
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_IP_ADDR)

   egIe->t.ipAddr.type = (ieLen == 4) ? CM_TPTADDR_IPV4 : CM_TPTADDR_IPV6;

   switch (egIe->t.ipAddr.type)
   {
      case CM_TPTADDR_IPV4:
      {
         EG_DEC_U32(egIe->t.ipAddr.u.ipv4, mBuf);
         break;
      } /* end of case */
#ifdef EG_IPV6_SUPPORTED
      case CM_TPTADDR_IPV6:
      {
         SRemPreMsgMult(egIe->t.ipAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
         break;
      } /* end of case */
#endif /* EG_IPV6_SUPPORTED */
      default:
      {
			RETVALUE(RFAILED);
      } /* end of case */
   }

   RETVALUE(ROK);
} /* end of egAcDecEG_IP_ADDR */


/***********************************************************************
 *   Fun:   egAcDecEG_GSM_KEY_TRIP
 *   Desc:  Decodes the IE data type GSM Key Triplet
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_GSM_KEY_TRIP
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_GSM_KEY_TRIP(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;
   S16 cnt = 0;
   U8  tempOctet = 0x00;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_GSM_KEY_TRIP)

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.gsmKeyT.secMode  = (tempOctet & 0xE0) >> EG_SHIFT_5;
   egIe->t.gsmKeyT.isDRXIPres = (tempOctet & EG_MASK_BIT4)?1:0;
   egIe->t.gsmKeyT.cksn     = (tempOctet & 0x07);

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.gsmKeyT.nmbTrip = (tempOctet & 0xE0) >> EG_SHIFT_5;
   egIe->t.gsmKeyT.isUAMBRIPres = (tempOctet & EG_MASK_BIT2)?1:0;
   egIe->t.gsmKeyT.isSAMBRIPres = (tempOctet & EG_MASK_BIT1)?1:0;

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.gsmKeyT.usedCipher = tempOctet & 0x07;

   /* decode Kc in eight octets */
   SRemPreMsgMult(egIe->t.gsmKeyT.kc, EG_LEN_EIGHT, mBuf);

	for (cnt = 0; cnt < egIe->t.gsmKeyT.nmbTrip; cnt++)
	{
	  SRemPreMsgMult(egIe->t.gsmKeyT.authTrip[cnt].rand, 16, mBuf);
	  SRemPreMsgMult(egIe->t.gsmKeyT.authTrip[cnt].sres, 4, mBuf);
	  SRemPreMsgMult(egIe->t.gsmKeyT.authTrip[cnt].kc, 8, mBuf);
	} /* end of loop */

   /* decode drx parameter - is of 2 octets */
   SRemPreMsgMult(egIe->t.gsmKeyT.drxParam, EG_LEN_TWO, mBuf);

	/* decode upLink subscribed UE AMBR */
   EG_DEC_U32(egIe->t.gsmKeyT.upSubsUEAMBR, mBuf);

	/* decode downLink subscribed UE AMBR */
   EG_DEC_U32(egIe->t.gsmKeyT.dnSubsUEAMBR, mBuf);

	/* decode upLink used UE AMBR */
   EG_DEC_U32(egIe->t.gsmKeyT.upUsedUEAMBR, mBuf);

	/* decode downLink used UE AMBR */
   EG_DEC_U32(egIe->t.gsmKeyT.dnUsedUEAMBR, mBuf);

	/* decode UE Network Capability - can be max of 15 octets */
	EG_DEC_STR(mBuf, egIe->t.gsmKeyT.ueNtwrkCapb.val, EG_UE_NTWRK_CAPB_LEN, EG_LEN_SIXTEEN, retValue);
	/* here we are mandating the length of UE Ntwrk will be of 15 octets */
	egIe->t.gsmKeyT.ueNtwrkCapb.length = EG_UE_NTWRK_CAPB_LEN;

	/* decode MS Network Capability - can be max of 10 octets */
	EG_DEC_STR(mBuf, egIe->t.gsmKeyT.msNtwrkCapb.val, EG_MS_NTWRK_CAPB_LEN, EG_LEN_SIXTEEN, retValue);
	/* here we are mandating the length of MS Ntwrk will be of 10 octets */
	egIe->t.gsmKeyT.msNtwrkCapb.length = EG_MS_NTWRK_CAPB_LEN;

	/* decode MEID - is of 16 octets */
	EG_DEC_STR(mBuf, egIe->t.gsmKeyT.meId.val, EG_LEN_SIXTEEN , EG_LEN_SIXTEEN, retValue);
	/* here we are mandating the length of MEID will be of 16 octets */
	egIe->t.gsmKeyT.meId.length = EG_LEN_SIXTEEN;

   SRemPreMsg(&tempOctet, mBuf);
	egIe->t.gsmKeyT.isUNA = (tempOctet & EG_MASK_BIT1)?1:0;
	egIe->t.gsmKeyT.isGENA = (tempOctet & EG_MASK_BIT2)?1:0;
	egIe->t.gsmKeyT.isGANA = (tempOctet & EG_MASK_BIT3)?1:0;
	egIe->t.gsmKeyT.isINA = (tempOctet & EG_MASK_BIT4)?1:0;
	egIe->t.gsmKeyT.isENA = (tempOctet & EG_MASK_BIT5)?1:0;
	egIe->t.gsmKeyT.isHNNA = (tempOctet & EG_MASK_BIT6)?1:0;

#ifdef EG_REL_930
	/* decode Voice Domain Preference and UE's usage Setting length */
	SRemPreMsg(&egIe->t.gsmKeyT.vDomPrefUEUsageLen, mBuf);

	/* decode UE's usage setting (1 bit field) Bit-3
	 * decode Voice  domain prefernce for E-UTRAN(2 bit field) Bit 2 and 1 */
	if(egIe->t.gsmKeyT.vDomPrefUEUsageLen)
	{
	  SRemPreMsg(&tempOctet, mBuf);
	  egIe->t.gsmKeyT.ueUsageSett = (tempOctet & EG_MASK_BIT3)?1:0;

	  egIe->t.gsmKeyT.vDomPref = tempOctet && 0x03;
	}
#endif /* EG_REL_930 */

   RETVALUE(retValue);
} /* end of egAcDecEG_GSM_KEY_TRIP */


/***********************************************************************
 *   Fun:   egAcDecEG_UMTS_KEY_CIPH_QUIN
 *   Desc:  Decodes the IE data type UMTS Key, Used Cipher and Quintuplets
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_UMTS_KEY_CIPH_QUIN
(
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
)
#else
PRIVATE S16 egAcDecEG_UMTS_KEY_CIPH_QUIN(egIe, mBuf, ieLen)
EgIe       *egIe;
Buffer     *mBuf;
U16        ieLen;
#endif
{
   S16 retValue = ROK;
   S16 cnt = 0;
   U8  tempOctet = 0x00;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_UMTS_KEY_CIPH_QUIN)

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.umtsKeyUCQt.secMode  = (tempOctet & 0xE0) >> EG_SHIFT_5;
   egIe->t.umtsKeyUCQt.isDRXIPres = (tempOctet & EG_MASK_BIT4)?1:0;
   egIe->t.umtsKeyUCQt.cksn     = (tempOctet & 0x07);

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.umtsKeyUCQt.nmbQuin = (tempOctet & 0xE0) >> EG_SHIFT_5;
   egIe->t.umtsKeyUCQt.isUAMBRIPres = (tempOctet & EG_MASK_BIT2)?1:0;
   egIe->t.umtsKeyUCQt.isSAMBRIPres = (tempOctet & EG_MASK_BIT1)?1:0;

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.umtsKeyUCQt.usedCipher = tempOctet & 0x07;

/* decode CK, IK each of 16 octets */
   egIe->t.umtsKeyUCQt.ck.length = EG_LEN_SIXTEEN;
   EG_DEC_STR(mBuf, egIe->t.umtsKeyUCQt.ck.val, egIe->t.umtsKeyUCQt.ck.length, EG_LEN_SIXTEEN, retValue);

   egIe->t.umtsKeyUCQt.ik.length = EG_LEN_SIXTEEN;
	EG_DEC_STR(mBuf, egIe->t.umtsKeyUCQt.ik.val, egIe->t.umtsKeyUCQt.ik.length, EG_LEN_SIXTEEN, retValue);

	for (cnt = 0; cnt < egIe->t.umtsKeyUCQt.nmbQuin; cnt++)
	{
	  /* Decode the RAND which is of 16 octets*/
	  egIe->t.umtsKeyUCQt.authQuin[cnt].rand.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyUCQt.authQuin[cnt].rand.val, egIe->t.umtsKeyUCQt.authQuin[cnt].rand.length, EG_LEN_SIXTEEN, retValue);

	  /* decode the XRES length in single octet and XRES which can be of 16 octets */
	  SRemPreMsg(&egIe->t.umtsKeyUCQt.authQuin[cnt].xresLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyUCQt.authQuin[cnt].xres.val, egIe->t.umtsKeyUCQt.authQuin[cnt].xresLen, EG_LEN_SIXTEEN, retValue);

	  /* decode the CK, IK each is of 16 octets length */
	  egIe->t.umtsKeyUCQt.authQuin[cnt].ck.length = EG_LEN_SIXTEEN;
	  egIe->t.umtsKeyUCQt.authQuin[cnt].ik.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyUCQt.authQuin[cnt].ck.val, egIe->t.umtsKeyUCQt.authQuin[cnt].ck.length, EG_LEN_SIXTEEN, retValue);
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyUCQt.authQuin[cnt].ik.val, egIe->t.umtsKeyUCQt.authQuin[cnt].ik.length, EG_LEN_SIXTEEN, retValue);

	  /* decode the AUTN */
	  SRemPreMsg(&egIe->t.umtsKeyUCQt.authQuin[cnt].autnLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyUCQt.authQuin[cnt].autn.val, egIe->t.umtsKeyUCQt.authQuin[cnt].autnLen, EG_LEN_SIXTEEN, retValue);

	}

   /* decode drx parameter - is of 2 octets */
   SRemPreMsgMult(egIe->t.umtsKeyUCQt.drxParam, EG_LEN_TWO, mBuf);

	/* decode upLink subscribed UE AMBR */
   EG_DEC_U32(egIe->t.umtsKeyUCQt.upSubsUEAMBR, mBuf);

	/* decode downLink subscribed UE AMBR */
   EG_DEC_U32(egIe->t.umtsKeyUCQt.dnSubsUEAMBR, mBuf);

	/* decode upLink used UE AMBR */
   EG_DEC_U32(egIe->t.umtsKeyUCQt.upUsedUEAMBR, mBuf);

	/* decode downLink used UE AMBR */
   EG_DEC_U32(egIe->t.umtsKeyUCQt.dnUsedUEAMBR, mBuf);


 /* decode UE Network Capability - can be max of 15 octets */
	EG_DEC_STR(mBuf, egIe->t.umtsKeyUCQt.ueNtwrkCapb.val, EG_UE_NTWRK_CAPB_LEN, EG_LEN_SIXTEEN, retValue);
	/* here we are mandating the length of UE Ntwrk will be of 15 octets */
	egIe->t.umtsKeyUCQt.ueNtwrkCapb.length = EG_UE_NTWRK_CAPB_LEN;

	/* decode MS Network Capability - can be max of 10 octets */
	EG_DEC_STR(mBuf, egIe->t.umtsKeyUCQt.msNtwrkCapb.val, EG_MS_NTWRK_CAPB_LEN, EG_LEN_SIXTEEN, retValue);
	/* here we are mandating the length of MS Ntwrk will be of 10 octets */
	egIe->t.umtsKeyUCQt.msNtwrkCapb.length = EG_MS_NTWRK_CAPB_LEN;

	/* decode MEID - is of 16 octets */
	EG_DEC_STR(mBuf, egIe->t.umtsKeyUCQt.meId.val, EG_LEN_SIXTEEN , EG_LEN_SIXTEEN, retValue);
	/* here we are mandating the length of MEID will be of 16 octets */
	egIe->t.umtsKeyUCQt.meId.length = EG_LEN_SIXTEEN;

   SRemPreMsg(&tempOctet, mBuf);
	egIe->t.umtsKeyUCQt.isUNA = (tempOctet & EG_MASK_BIT1)?1:0;
	egIe->t.umtsKeyUCQt.isGENA = (tempOctet & EG_MASK_BIT2)?1:0;
	egIe->t.umtsKeyUCQt.isGANA = (tempOctet & EG_MASK_BIT3)?1:0;
	egIe->t.umtsKeyUCQt.isINA = (tempOctet & EG_MASK_BIT4)?1:0;
	egIe->t.umtsKeyUCQt.isENA = (tempOctet & EG_MASK_BIT5)?1:0;
	egIe->t.umtsKeyUCQt.isHNNA = (tempOctet & EG_MASK_BIT6)?1:0;

#ifdef EG_REL_930
	/* decode Voice Domain Preference and UE's usage Setting length */
	SRemPreMsg(&egIe->t.umtsKeyUCQt.vDomPrefUEUsageLen, mBuf);

	/* decode UE's usage setting (1 bit field) Bit-3
	 * decode Voice  domain prefernce for E-UTRAN(2 bit field) Bit 2 and 1 */
	if(egIe->t.umtsKeyUCQt.vDomPrefUEUsageLen)
	{
	  SRemPreMsg(&tempOctet, mBuf);
	  egIe->t.umtsKeyUCQt.ueUsageSett = (tempOctet & EG_MASK_BIT3)?1:0;

	  egIe->t.umtsKeyUCQt.vDomPref = tempOctet && 0x03;
	}
#endif /* EG_REL_930 */

   RETVALUE(retValue);
} /* end of egAcDecEG_UMTS_KEY_CIPH_QUIN */


/***********************************************************************
 *   Fun:   egAcDecEG_GSM_KEY_CIPH_QUIN
 *   Desc:  Decodes the IE data type GSM Key, Used Cipher and Quintuplets
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_GSM_KEY_CIPH_QUIN
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_GSM_KEY_CIPH_QUIN(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;
   S16 cnt = 0;
   U8  tempOctet = 0x00;
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_GSM_KEY_CIPH_QUIN)

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.gsmKeyUCQt.secMode  = (tempOctet & 0xE0) >> EG_SHIFT_5;
   egIe->t.gsmKeyUCQt.isDRXIPres = (tempOctet & EG_MASK_BIT4)?1:0;
   egIe->t.gsmKeyUCQt.cksn     = (tempOctet & 0x07);

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.gsmKeyUCQt.nmbQuin = (tempOctet & 0xE0) >> EG_SHIFT_5;
   egIe->t.gsmKeyUCQt.isUAMBRIPres = (tempOctet & EG_MASK_BIT2)?1:0;
   egIe->t.gsmKeyUCQt.isSAMBRIPres = (tempOctet & EG_MASK_BIT1)?1:0;

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.gsmKeyUCQt.usedCipher = tempOctet & 0x07;

	/* decode Kc in eight octets */
	SRemPreMsgMult(egIe->t.gsmKeyUCQt.kc, EG_LEN_EIGHT, mBuf);

  	for (cnt = 0; cnt < egIe->t.gsmKeyUCQt.nmbQuin; cnt++)
	{
	  /* Decode the RAND which is of 16 octets*/
	  egIe->t.gsmKeyUCQt.authQuin[cnt].rand.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.gsmKeyUCQt.authQuin[cnt].rand.val, egIe->t.gsmKeyUCQt.authQuin[cnt].rand.length, EG_LEN_SIXTEEN, retValue);

	  /* decode the XRES length in single octet and XRES which can be of 16 octets */
	  SRemPreMsg(&egIe->t.gsmKeyUCQt.authQuin[cnt].xresLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.gsmKeyUCQt.authQuin[cnt].xres.val, egIe->t.gsmKeyUCQt.authQuin[cnt].xresLen, EG_LEN_SIXTEEN, retValue);

	  /* decode the CK, IK each is of 16 octets length */
	  egIe->t.gsmKeyUCQt.authQuin[cnt].ck.length = EG_LEN_SIXTEEN;
	  egIe->t.gsmKeyUCQt.authQuin[cnt].ik.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.gsmKeyUCQt.authQuin[cnt].ck.val, egIe->t.gsmKeyUCQt.authQuin[cnt].ck.length, EG_LEN_SIXTEEN, retValue);
	  EG_DEC_STR(mBuf, egIe->t.gsmKeyUCQt.authQuin[cnt].ik.val, egIe->t.gsmKeyUCQt.authQuin[cnt].ik.length, EG_LEN_SIXTEEN, retValue);

	  /* decode the AUTN */
	  SRemPreMsg(&egIe->t.gsmKeyUCQt.authQuin[cnt].autnLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.gsmKeyUCQt.authQuin[cnt].autn.val, egIe->t.gsmKeyUCQt.authQuin[cnt].autnLen, EG_LEN_SIXTEEN, retValue);

	}

   /* decode drx parameter - is of 2 octets */
   SRemPreMsgMult(egIe->t.gsmKeyUCQt.drxParam, EG_LEN_TWO, mBuf);

	/* decode upLink subscribed UE AMBR */
   EG_DEC_U32(egIe->t.gsmKeyUCQt.upSubsUEAMBR, mBuf);

	/* decode downLink subscribed UE AMBR */
   EG_DEC_U32(egIe->t.gsmKeyUCQt.dnSubsUEAMBR, mBuf);

	/* decode upLink used UE AMBR */
   EG_DEC_U32(egIe->t.gsmKeyUCQt.upUsedUEAMBR, mBuf);

	/* decode downLink used UE AMBR */
   EG_DEC_U32(egIe->t.gsmKeyUCQt.dnUsedUEAMBR, mBuf);

 /* decode UE Network Capability - can be max of 15 octets */
    EG_DEC_STR(mBuf, egIe->t.gsmKeyUCQt.ueNtwrkCapb.val, EG_UE_NTWRK_CAPB_LEN, EG_LEN_SIXTEEN, retValue);
	 /* here we are mandating the length of UE Ntwrk will be of 15 octets */
	 egIe->t.gsmKeyUCQt.ueNtwrkCapb.length = EG_UE_NTWRK_CAPB_LEN;

	 /* decode MS Network Capability - can be max of 10 octets */
	 EG_DEC_STR(mBuf, egIe->t.gsmKeyUCQt.msNtwrkCapb.val, EG_MS_NTWRK_CAPB_LEN, EG_LEN_SIXTEEN, retValue);
	 /* here we are mandating the length of MS Ntwrk will be of 10 octets */
	 egIe->t.gsmKeyUCQt.msNtwrkCapb.length = EG_MS_NTWRK_CAPB_LEN;

	 /* decode MEID - is of 16 octets */
	 EG_DEC_STR(mBuf, egIe->t.gsmKeyUCQt.meId.val, EG_LEN_SIXTEEN , EG_LEN_SIXTEEN, retValue);
	 /* here we are mandating the length of MEID will be of 16 octets */
	 egIe->t.gsmKeyUCQt.meId.length = EG_LEN_SIXTEEN;


   SRemPreMsg(&tempOctet, mBuf);
	egIe->t.gsmKeyUCQt.isUNA = (tempOctet & EG_MASK_BIT1)?1:0;
	egIe->t.gsmKeyUCQt.isGENA = (tempOctet & EG_MASK_BIT2)?1:0;
	egIe->t.gsmKeyUCQt.isGANA = (tempOctet & EG_MASK_BIT3)?1:0;
	egIe->t.gsmKeyUCQt.isINA = (tempOctet & EG_MASK_BIT4)?1:0;
	egIe->t.gsmKeyUCQt.isENA = (tempOctet & EG_MASK_BIT5)?1:0;
	egIe->t.gsmKeyUCQt.isHNNA = (tempOctet & EG_MASK_BIT6)?1:0;

#ifdef EG_REL_930
	/* decode Voice Domain Preference and UE's usage Setting length */
	SRemPreMsg(&egIe->t.gsmKeyUCQt.vDomPrefUEUsageLen, mBuf);

	/* decode UE's usage setting (1 bit field) Bit-3
	 * decode Voice  domain prefernce for E-UTRAN(2 bit field) Bit 2 and 1 */
	if(egIe->t.gsmKeyUCQt.vDomPrefUEUsageLen)
	{
	  SRemPreMsg(&tempOctet, mBuf);
	  egIe->t.gsmKeyUCQt.ueUsageSett = (tempOctet & EG_MASK_BIT3)?1:0;

	  egIe->t.gsmKeyUCQt.vDomPref = tempOctet && 0x03;
	}
#endif /* EG_REL_930 */
   RETVALUE(retValue);
} /* end of egAcDecEG_GSM_KEY_CIPH_QUIN */


/***********************************************************************
 *   Fun:   egAcDecEG_UMTS_KEY_QUIN
 *   Desc:  Decodes the IE data type UMTS Key, and Quintuplets
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_UMTS_KEY_QUIN
(
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
)
#else
PRIVATE S16 egAcDecEG_UMTS_KEY_QUIN(egIe, mBuf, ieLen)
EgIe       *egIe;
Buffer     *mBuf;
U16        ieLen;
#endif
{
   S16 retValue = ROK;
   S16 cnt = 0;
   U8  tempOctet = 0x00;

   /*-- eg003.201 : TRC changes from eg006.102--*/
 	EG_TRC2(egAcDecEG_UMTS_KEY_QUIN)
   
   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.umtsKeyQt.secMode  = (tempOctet & 0xE0) >> EG_SHIFT_5;
   egIe->t.umtsKeyQt.isDRXIPres = (tempOctet & EG_MASK_BIT4)?1:0;
   egIe->t.umtsKeyQt.ksi = (tempOctet & 0x07);

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.umtsKeyQt.nmbQuin = (tempOctet & 0xE0) >> EG_SHIFT_5;
   egIe->t.umtsKeyQt.isUAMBRIPres = (tempOctet & EG_MASK_BIT2)?1:0;
   egIe->t.umtsKeyQt.isSAMBRIPres = (tempOctet & EG_MASK_BIT1)?1:0;

  /* 7th one is spare octect */
   SRemPreMsg(&tempOctet, mBuf);
	tempOctet = 0x00;

/* decode CK, IK each of 16 octets */
   egIe->t.umtsKeyQt.ck.length = EG_LEN_SIXTEEN;
   EG_DEC_STR(mBuf, egIe->t.umtsKeyQt.ck.val, egIe->t.umtsKeyQt.ck.length, EG_LEN_SIXTEEN, retValue);

   egIe->t.umtsKeyQt.ik.length = EG_LEN_SIXTEEN;
	EG_DEC_STR(mBuf, egIe->t.umtsKeyQt.ik.val, egIe->t.umtsKeyQt.ik.length, EG_LEN_SIXTEEN, retValue);

	for (cnt = 0; cnt < egIe->t.umtsKeyQt.nmbQuin; cnt++)
	{
	  /* Decode the RAND which is of 16 octets*/
	  egIe->t.umtsKeyQt.authQuin[cnt].rand.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQt.authQuin[cnt].rand.val, egIe->t.umtsKeyQt.authQuin[cnt].rand.length, EG_LEN_SIXTEEN, retValue);

	  /* decode the XRES length in single octet and XRES which can be of 16 octets */
	  SRemPreMsg(&egIe->t.umtsKeyQt.authQuin[cnt].xresLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQt.authQuin[cnt].xres.val, egIe->t.umtsKeyQt.authQuin[cnt].xresLen, EG_LEN_SIXTEEN, retValue);

	  /* decode the CK, IK each is of 16 octets length */
	  egIe->t.umtsKeyQt.authQuin[cnt].ck.length = EG_LEN_SIXTEEN;
	  egIe->t.umtsKeyQt.authQuin[cnt].ik.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQt.authQuin[cnt].ck.val, egIe->t.umtsKeyQt.authQuin[cnt].ck.length, EG_LEN_SIXTEEN, retValue);
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQt.authQuin[cnt].ik.val, egIe->t.umtsKeyQt.authQuin[cnt].ik.length, EG_LEN_SIXTEEN, retValue);

	  /* decode the AUTN */
	  SRemPreMsg(&egIe->t.umtsKeyQt.authQuin[cnt].autnLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQt.authQuin[cnt].autn.val, egIe->t.umtsKeyQt.authQuin[cnt].autnLen, EG_LEN_SIXTEEN, retValue);

	}

   /* decode drx parameter - is of 2 octets */
   SRemPreMsgMult(egIe->t.umtsKeyQt.drxParam, EG_LEN_TWO, mBuf);

	/* decode upLink subscribed UE AMBR */
   EG_DEC_U32(egIe->t.umtsKeyQt.upSubsUEAMBR, mBuf);

	/* decode downLink subscribed UE AMBR */
   EG_DEC_U32(egIe->t.umtsKeyQt.dnSubsUEAMBR, mBuf);

	/* decode upLink used UE AMBR */
   EG_DEC_U32(egIe->t.umtsKeyQt.upUsedUEAMBR, mBuf);

	/* decode downLink used UE AMBR */
   EG_DEC_U32(egIe->t.umtsKeyQt.dnUsedUEAMBR, mBuf);

 /* decode UE Network Capability - can be max of 15 octets */
     EG_DEC_STR(mBuf, egIe->t.umtsKeyQt.ueNtwrkCapb.val, EG_UE_NTWRK_CAPB_LEN, EG_LEN_SIXTEEN, retValue);
	  /* here we are mandating the length of UE Ntwrk will be of 15 octets */
	  egIe->t.umtsKeyQt.ueNtwrkCapb.length = EG_UE_NTWRK_CAPB_LEN;

	  /* decode MS Network Capability - can be max of 10 octets */
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQt.msNtwrkCapb.val, EG_MS_NTWRK_CAPB_LEN, EG_LEN_SIXTEEN, retValue);
	  /* here we are mandating the length of MS Ntwrk will be of 10 octets */
	  egIe->t.umtsKeyQt.msNtwrkCapb.length = EG_MS_NTWRK_CAPB_LEN;

	  /* decode MEID - is of 16 octets */
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQt.meId.val, EG_LEN_SIXTEEN , EG_LEN_SIXTEEN, retValue);
	  /* here we are mandating the length of MEID will be of 16 octets */
	  egIe->t.umtsKeyQt.meId.length = EG_LEN_SIXTEEN;


   SRemPreMsg(&tempOctet, mBuf);
	egIe->t.umtsKeyQt.isUNA = (tempOctet & EG_MASK_BIT1)?1:0;
	egIe->t.umtsKeyQt.isGENA = (tempOctet & EG_MASK_BIT2)?1:0;
	egIe->t.umtsKeyQt.isGANA = (tempOctet & EG_MASK_BIT3)?1:0;
	egIe->t.umtsKeyQt.isINA = (tempOctet & EG_MASK_BIT4)?1:0;
	egIe->t.umtsKeyQt.isENA = (tempOctet & EG_MASK_BIT5)?1:0;
	egIe->t.umtsKeyQt.isHNNA = (tempOctet & EG_MASK_BIT6)?1:0;

#ifdef EG_REL_930
	/* decode Voice Domain Preference and UE's usage Setting length */
	SRemPreMsg(&egIe->t.umtsKeyQt.vDomPrefUEUsageLen, mBuf);

	/* decode UE's usage setting (1 bit field) Bit-3
	 * decode Voice  domain prefernce for E-UTRAN(2 bit field) Bit 2 and 1 */
	if(egIe->t.umtsKeyQt.vDomPrefUEUsageLen)
	{
	  SRemPreMsg(&tempOctet, mBuf);
	  egIe->t.umtsKeyQt.ueUsageSett = (tempOctet & EG_MASK_BIT3)?1:0;

	  egIe->t.umtsKeyQt.vDomPref = tempOctet && 0x03;
	}
#endif /* EG_REL_930 */

   RETVALUE(retValue);
} /* end of egAcDecEG_UMTS_KEY_QUIN */


/***********************************************************************
 *   Fun:   egAcDecEG_EPS_SEC_QUAD_QUIN
 *   Desc:  Decodes the IE data type EPS Security Context, Quadruplets and Quintuplets
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_EPS_SEC_QUAD_QUIN
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_EPS_SEC_QUAD_QUIN(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;
   U8  tempOctet = 0x00;
	U8  cnt;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_EPS_SEC_QUAD_QUIN)
 
   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.eSecCxtQdQt.secMode = (tempOctet & 0xE0) >> EG_SHIFT_5;
   egIe->t.eSecCxtQdQt.ksi = (tempOctet & 0x07);
	egIe->t.eSecCxtQdQt.isNHIPres = (tempOctet & 0x10)?1:0;
	egIe->t.eSecCxtQdQt.isDRXIPres = (tempOctet & 0x08)?1:0;

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.eSecCxtQdQt.nmbQuin = (tempOctet & 0xE0) >> EG_SHIFT_5;
   egIe->t.eSecCxtQdQt.nmbQuadru = (tempOctet & 0x1C) >> EG_SHIFT_2;
	egIe->t.eSecCxtQdQt.isUAMBRIPres = (tempOctet & 0x02)?1:0;
	egIe->t.eSecCxtQdQt.isOCSIPres = (tempOctet & 0x01)?1:0;

   SRemPreMsg(&tempOctet, mBuf);
	egIe->t.eSecCxtQdQt.isSAMBRIPres = (tempOctet & 0x80)?1:0;
   egIe->t.eSecCxtQdQt.nasProtAlgo = (tempOctet&0x70) >> EG_SHIFT_4;
   egIe->t.eSecCxtQdQt.usedNasCipher = (tempOctet & 0x0F);

   /* decode NAS Downlink Count and NAS Uplink Count - each of 3 octets long */
   EG_DEC_U24(egIe->t.eSecCxtQdQt.nasDlCount, mBuf);
   EG_DEC_U24(egIe->t.eSecCxtQdQt.nasUlCount, mBuf);

   /* decode Kasme of 32 octets */
   egIe->t.eSecCxtQdQt.kasme.length = EG_KASME_LEN;
   EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.kasme.val, egIe->t.eSecCxtQdQt.kasme.length, EG_LEN_32, retValue);

	for(cnt=0; cnt < egIe->t.eSecCxtQdQt.nmbQuadru; cnt++)
	{
	  /* decode the RAND which is of 16 octets*/
	  egIe->t.eSecCxtQdQt.authQuadru[cnt].rand.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuadru[cnt].rand.val, egIe->t.eSecCxtQdQt.authQuadru[cnt].rand.length, EG_LEN_SIXTEEN, retValue);

	  /* decode the XRES length in single octet and XRES which can be of 16 octets */
	  SRemPreMsg(&egIe->t.eSecCxtQdQt.authQuadru[cnt].xresLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuadru[cnt].xres.val, egIe->t.eSecCxtQdQt.authQuadru[cnt].xresLen, EG_LEN_SIXTEEN, retValue);

	  /* decode the AUTN length in single octet and AUTH which can be of 16 octets */
	  SRemPreMsg(&egIe->t.eSecCxtQdQt.authQuadru[cnt].autnLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuadru[cnt].autn.val, egIe->t.eSecCxtQdQt.authQuadru[cnt].autnLen, EG_LEN_SIXTEEN, retValue);

	  /* decode the Kasme which is of 31 octets */
	  egIe->t.eSecCxtQdQt.authQuadru[cnt].kasme.length = EG_KASME_LEN;
	  EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuadru[cnt].kasme.val, egIe->t.eSecCxtQdQt.authQuadru[cnt].kasme.length, EG_LEN_32, retValue);
	}

	for(cnt=0; cnt < egIe->t.eSecCxtQdQt.nmbQuin; cnt++)
	{
	  /* Decode the RAND which is of 16 octets*/
	  egIe->t.eSecCxtQdQt.authQuin[cnt].rand.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuin[cnt].rand.val, egIe->t.eSecCxtQdQt.authQuin[cnt].rand.length, EG_LEN_SIXTEEN, retValue);

	  /* decode the XRES length in single octet and XRES which can be of 16 octets */
	  SRemPreMsg(&egIe->t.eSecCxtQdQt.authQuin[cnt].xresLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuin[cnt].xres.val, egIe->t.eSecCxtQdQt.authQuin[cnt].xresLen, EG_LEN_SIXTEEN, retValue);

	  /* decode the CK, IK each is of 16 octets length */
	  egIe->t.eSecCxtQdQt.authQuin[cnt].ck.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuin[cnt].ck.val, egIe->t.eSecCxtQdQt.authQuin[cnt].ck.length, EG_LEN_SIXTEEN, retValue);
	  egIe->t.eSecCxtQdQt.authQuin[cnt].ik.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuin[cnt].ik.val, egIe->t.eSecCxtQdQt.authQuin[cnt].ik.length, EG_LEN_SIXTEEN, retValue);

	  /* decode the AUTN */
	  SRemPreMsg(&egIe->t.eSecCxtQdQt.authQuin[cnt].autnLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.authQuin[cnt].autn.val, egIe->t.eSecCxtQdQt.authQuin[cnt].autnLen, EG_LEN_SIXTEEN, retValue);
	}

   /* decode drx parameter - is of 2 octets */
   SRemPreMsgMult(egIe->t.eSecCxtQdQt.drxParam, EG_LEN_TWO, mBuf);

   /* decode nh  parameter - is of 32 octets */
   SRemPreMsgMult(egIe->t.eSecCxtQdQt.nxtHop, EG_LEN_32, mBuf);

	/* decode upLink subscribed UE AMBR */
   EG_DEC_U32(egIe->t.eSecCxtQdQt.upSubsUEAMBR, mBuf);

	/* decode downLink subscribed UE AMBR */
   EG_DEC_U32(egIe->t.eSecCxtQdQt.dnSubsUEAMBR, mBuf);

	/* decode upLink used UE AMBR */
   EG_DEC_U32(egIe->t.eSecCxtQdQt.upUsedUEAMBR, mBuf);

	/* decode downLink used UE AMBR */
   EG_DEC_U32(egIe->t.eSecCxtQdQt.dnUsedUEAMBR, mBuf);

 /* decode UE Network Capability - can be max of 15 octets */
	EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.ueNtwrkCapb.val, EG_UE_NTWRK_CAPB_LEN, EG_LEN_SIXTEEN, retValue);
	/* here we are mandating the length of UE Ntwrk will be of 15 octets */
	egIe->t.eSecCxtQdQt.ueNtwrkCapb.length = EG_UE_NTWRK_CAPB_LEN;

	/* decode MS Network Capability - can be max of 10 octets */
	EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.msNtwrkCapb.val, EG_MS_NTWRK_CAPB_LEN, EG_LEN_SIXTEEN, retValue);
	/* here we are mandating the length of MS Ntwrk will be of 10 octets */
	egIe->t.eSecCxtQdQt.msNtwrkCapb.length = EG_MS_NTWRK_CAPB_LEN;

	/* decode MEID - is of 16 octets */
	EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.meId.val, EG_LEN_SIXTEEN , EG_LEN_SIXTEEN, retValue);
	/* here we are mandating the length of MEID will be of 16 octets */
	egIe->t.eSecCxtQdQt.meId.length = EG_LEN_SIXTEEN;

   SRemPreMsg(&tempOctet, mBuf);
	egIe->t.eSecCxtQdQt.isUNA = (tempOctet & EG_MASK_BIT1)?1:0;
	egIe->t.eSecCxtQdQt.isGENA = (tempOctet & EG_MASK_BIT2)?1:0;
	egIe->t.eSecCxtQdQt.isGANA = (tempOctet & EG_MASK_BIT3)?1:0;
	egIe->t.eSecCxtQdQt.isINA = (tempOctet & EG_MASK_BIT4)?1:0;
	egIe->t.eSecCxtQdQt.isENA = (tempOctet & EG_MASK_BIT5)?1:0;
	egIe->t.eSecCxtQdQt.isHNNA = (tempOctet & EG_MASK_BIT6)?1:0;

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.eSecCxtQdQt.ncc = (tempOctet & 0x07);

	SRemPreMsg(&tempOctet, mBuf);
	egIe->t.eSecCxtQdQt.nccOld = (tempOctet & 0x07);
	egIe->t.eSecCxtQdQt.ksiOld = (tempOctet & 0x38) >> EG_SHIFT_3;
	egIe->t.eSecCxtQdQt.isNHIOldPres = (tempOctet & 0x80)?1:0;

 /* decode Kasme of 32 octets */
   egIe->t.eSecCxtQdQt.kasmeOld.length = EG_KASME_LEN;
   EG_DEC_STR(mBuf, egIe->t.eSecCxtQdQt.kasmeOld.val, egIe->t.eSecCxtQdQt.kasmeOld.length, EG_LEN_32, retValue);

   /* decode nh old  parameter - is of 32 octets */
   SRemPreMsgMult(egIe->t.eSecCxtQdQt.nxtHopOld, EG_LEN_32, mBuf);

#ifdef EG_REL_930
	/* decode Voice Domain Preference and UE's usage Setting length */
	SRemPreMsg(&egIe->t.eSecCxtQdQt.vDomPrefUEUsageLen, mBuf);

	/* decode UE's usage setting (1 bit field) Bit-3
	 * decode Voice  domain prefernce for E-UTRAN(2 bit field) Bit 2 and 1 */
	if(egIe->t.eSecCxtQdQt.vDomPrefUEUsageLen)
	{
	  SRemPreMsg(&tempOctet, mBuf);
	  egIe->t.eSecCxtQdQt.ueUsageSett = (tempOctet & EG_MASK_BIT3)?1:0;

	  egIe->t.eSecCxtQdQt.vDomPref = tempOctet && 0x03;
	}
#endif /* EG_REL_930 */

   RETVALUE(retValue);
} /* end of egAcDecEG_EPS_SEC_QUAD_QUIN */


/***********************************************************************
 *   Fun:   egAcDecEG_UMTS_KEY_QUAD_QUIN
 *   Desc:  Decodes the IE data type UMTS Key, Quadruplets and Quintuplets
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_UMTS_KEY_QUAD_QUIN
(
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
)
#else
PRIVATE S16 egAcDecEG_UMTS_KEY_QUAD_QUIN(egIe, mBuf, ieLen)
EgIe       *egIe;
Buffer     *mBuf;
U16        ieLen;
#endif
{
   S16 retValue = ROK;
   S16 cnt = 0;
   U8  tempOctet = 0x00;
   
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_UMTS_KEY_QUAD_QUIN)

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.umtsKeyQdQt.secMode  = (tempOctet & 0xE0) >> EG_SHIFT_5;
   egIe->t.umtsKeyQdQt.isDRXIPres = (tempOctet & EG_MASK_BIT4)?1:0;
   egIe->t.umtsKeyQdQt.ksi = (tempOctet & 0x07);

   SRemPreMsg(&tempOctet, mBuf);
   egIe->t.umtsKeyQdQt.nmbQuin = (tempOctet & 0xE0) >> EG_SHIFT_5;
   egIe->t.umtsKeyQdQt.nmbQuadru = (tempOctet & 0x1C) >> EG_SHIFT_2;
	egIe->t.umtsKeyQdQt.isUAMBRIPres = (tempOctet & 0x02)?1:0;
	egIe->t.umtsKeyQdQt.isSAMBRIPres = (tempOctet & 0x01)?1:0;

  /* 7th one is spare octect */
   SRemPreMsg(&tempOctet, mBuf);
	tempOctet = 0x00;

/* decode CK, IK each of 16 octets */
   egIe->t.umtsKeyQdQt.ck.length = EG_LEN_SIXTEEN;
   EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.ck.val, egIe->t.umtsKeyQdQt.ck.length, EG_LEN_SIXTEEN, retValue);

   egIe->t.umtsKeyQdQt.ik.length = EG_LEN_SIXTEEN;
	EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.ik.val, egIe->t.umtsKeyQdQt.ik.length, EG_LEN_SIXTEEN, retValue);

	for(cnt=0; cnt < egIe->t.umtsKeyQdQt.nmbQuadru; cnt++)
	{
	  /* decode the RAND which is of 16 octets*/
	  egIe->t.umtsKeyQdQt.authQuadru[cnt].rand.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuadru[cnt].rand.val, egIe->t.umtsKeyQdQt.authQuadru[cnt].rand.length, EG_LEN_SIXTEEN, retValue);

	  /* decode the XRES length in single octet and XRES which can be of 16 octets */
	  SRemPreMsg(&egIe->t.umtsKeyQdQt.authQuadru[cnt].xresLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuadru[cnt].xres.val, egIe->t.umtsKeyQdQt.authQuadru[cnt].xresLen, EG_LEN_SIXTEEN, retValue);

	  /* decode the AUTN length in single octet and AUTH which can be of 16 octets */
	  SRemPreMsg(&egIe->t.umtsKeyQdQt.authQuadru[cnt].autnLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuadru[cnt].autn.val, egIe->t.umtsKeyQdQt.authQuadru[cnt].autnLen, EG_LEN_SIXTEEN, retValue);

	  /* decode the Kasme which is of 31 octets */
	  egIe->t.umtsKeyQdQt.authQuadru[cnt].kasme.length = EG_KASME_LEN;
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuadru[cnt].kasme.val, egIe->t.umtsKeyQdQt.authQuadru[cnt].kasme.length, EG_LEN_32, retValue);
	}

	for (cnt = 0; cnt < egIe->t.umtsKeyQdQt.nmbQuin; cnt++)
	{
	  /* Decode the RAND which is of 16 octets*/
	  egIe->t.umtsKeyQdQt.authQuin[cnt].rand.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuin[cnt].rand.val, egIe->t.umtsKeyQdQt.authQuin[cnt].rand.length, EG_LEN_SIXTEEN, retValue);

	  /* decode the XRES length in single octet and XRES which can be of 16 octets */
	  SRemPreMsg(&egIe->t.umtsKeyQdQt.authQuin[cnt].xresLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuin[cnt].xres.val, egIe->t.umtsKeyQdQt.authQuin[cnt].xresLen, EG_LEN_SIXTEEN, retValue);

	  /* decode the CK, IK each is of 16 octets length */
	  egIe->t.umtsKeyQdQt.authQuin[cnt].ck.length = EG_LEN_SIXTEEN;
	  egIe->t.umtsKeyQdQt.authQuin[cnt].ik.length = EG_LEN_SIXTEEN;
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuin[cnt].ck.val, egIe->t.umtsKeyQdQt.authQuin[cnt].ck.length, EG_LEN_SIXTEEN, retValue);
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuin[cnt].ik.val, egIe->t.umtsKeyQdQt.authQuin[cnt].ik.length, EG_LEN_SIXTEEN, retValue);

	  /* decode the AUTN */
	  SRemPreMsg(&egIe->t.umtsKeyQdQt.authQuin[cnt].autnLen, mBuf);
	  EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.authQuin[cnt].autn.val, egIe->t.umtsKeyQdQt.authQuin[cnt].autnLen, EG_LEN_SIXTEEN, retValue);
	}

   /* decode drx parameter - is of 2 octets */
   SRemPreMsgMult(egIe->t.umtsKeyQdQt.drxParam, EG_LEN_TWO, mBuf);

	/* decode upLink subscribed UE AMBR */
   EG_DEC_U32(egIe->t.umtsKeyQdQt.upSubsUEAMBR, mBuf);

	/* decode downLink subscribed UE AMBR */
   EG_DEC_U32(egIe->t.umtsKeyQdQt.dnSubsUEAMBR, mBuf);

	/* decode upLink used UE AMBR */
   EG_DEC_U32(egIe->t.umtsKeyQdQt.upUsedUEAMBR, mBuf);

	/* decode downLink used UE AMBR */
   EG_DEC_U32(egIe->t.umtsKeyQdQt.dnUsedUEAMBR, mBuf);

 /* decode UE Network Capability - can be max of 15 octets */
	EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.ueNtwrkCapb.val, EG_UE_NTWRK_CAPB_LEN, EG_LEN_SIXTEEN, retValue);
	/* here we are mandating the length of UE Ntwrk will be of 15 octets */
	egIe->t.umtsKeyQdQt.ueNtwrkCapb.length = EG_UE_NTWRK_CAPB_LEN;

	/* decode MS Network Capability - can be max of 10 octets */
	EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.msNtwrkCapb.val, EG_MS_NTWRK_CAPB_LEN, EG_LEN_SIXTEEN, retValue);
	/* here we are mandating the length of MS Ntwrk will be of 10 octets */
	egIe->t.umtsKeyQdQt.msNtwrkCapb.length = EG_MS_NTWRK_CAPB_LEN;

	/* decode MEID - is of 16 octets */
	EG_DEC_STR(mBuf, egIe->t.umtsKeyQdQt.meId.val, EG_LEN_SIXTEEN , EG_LEN_SIXTEEN, retValue);
	/* here we are mandating the length of MEID will be of 16 octets */
	egIe->t.umtsKeyQdQt.meId.length = EG_LEN_SIXTEEN;

   SRemPreMsg(&tempOctet, mBuf);
	egIe->t.umtsKeyQdQt.isUNA = (tempOctet & EG_MASK_BIT1)?1:0;
	egIe->t.umtsKeyQdQt.isGENA = (tempOctet & EG_MASK_BIT2)?1:0;
	egIe->t.umtsKeyQdQt.isGANA = (tempOctet & EG_MASK_BIT3)?1:0;
	egIe->t.umtsKeyQdQt.isINA = (tempOctet & EG_MASK_BIT4)?1:0;
	egIe->t.umtsKeyQdQt.isENA = (tempOctet & EG_MASK_BIT5)?1:0;
	egIe->t.umtsKeyQdQt.isHNNA = (tempOctet & EG_MASK_BIT6)?1:0;

#ifdef EG_REL_930
	/* decode Voice Domain Preference and UE's usage Setting length */
	SRemPreMsg(&egIe->t.umtsKeyQdQt.vDomPrefUEUsageLen, mBuf);

	/* decode UE's usage setting (1 bit field) Bit-3
	 * decode Voice  domain prefernce for E-UTRAN(2 bit field) Bit 2 and 1 */
	if(egIe->t.umtsKeyQdQt.vDomPrefUEUsageLen)
	{
	  SRemPreMsg(&tempOctet, mBuf);
	  egIe->t.umtsKeyQdQt.ueUsageSett = (tempOctet & EG_MASK_BIT3)?1:0;

	  egIe->t.umtsKeyQdQt.vDomPref = tempOctet && 0x03;
	}
#endif /* EG_REL_930 */

   RETVALUE(retValue);
} /* end of egAcDecEG_UMTS_KEY_QUAD_QUIN */


/***********************************************************************
 *   Fun:   egAcDecEG_F_CAUSE
 *   Desc:  Decodes the IE data type F-Cause
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_F_CAUSE
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_F_CAUSE(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_F_CAUSE);

   /* decode the FCause Type */
   SRemPreMsg(&egIe->t.fCause.causeType, mBuf);
	egIe->t.fCause.causeType = egIe->t.fCause.causeType & 0x0F;

   /* decode the FCause Value */
   EG_DEC_U16(egIe->t.fCause.cause, mBuf);

   RETVALUE(retValue);
} /* end of egAcDecEG_F_CAUSE */


/***********************************************************************
 *   Fun:   egAcDecEG_S103_PDN_FW_INFO
 *   Desc:  Decodes the IE data type S103 PDN Data Forwarding Info
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_S103_PDN_FW_INFO
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_S103_PDN_FW_INFO(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;
   U8  cnt;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_S103_PDN_FW_INFO)

	SRemPreMsg(&egIe->t.s103PDF.hsgwAddrLen, mBuf);

   if (egIe->t.s103PDF.hsgwAddrLen == 0x04)
	{
	  egIe->t.s103PDF.hsgwAddr.type = CM_TPTADDR_IPV4;
	  EG_DEC_U32(egIe->t.s103PDF.hsgwAddr.u.ipv4, mBuf);
	} /* end of if */
#ifdef EG_IPV6_SUPPORTED
	else if (tempOctet == 0x0F)
	{
	  egIe->t.s103PDF.hsgwAddr.type = CM_TPTADDR_IPV6;
	  SRemPreMsgMult(egIe->t.s103PDF.hsgwAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
	} /* end of case */
#endif /* end of CM_TPTADDR_IPV6 */
   else
	{
		RETVALUE(RFAILED);
	}

   /* decode the GRE Key */
   EG_DEC_U32(egIe->t.s103PDF.greKey, mBuf);

   /* decode the EBI Number */
   SRemPreMsg(&egIe->t.s103PDF.ebiNumber, mBuf);

	for(cnt=0;cnt<egIe->t.s103PDF.ebiNumber && cnt < EG_MAX_NMB_BEARER;cnt++)
	{
	  SRemPreMsg(&egIe->t.s103PDF.ebi[cnt], mBuf);
	}

   RETVALUE(retValue);
} /* end of egAcDecEG_S103_PDN_FW_INFO */


/***********************************************************************
 *   Fun:   egAcDecEG_S1U_DATA_FW
 *   Desc:  Decodes the IE data type S1-U Data Forwarding
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_S1U_DATA_FW
(
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
)
#else
PRIVATE S16 egAcDecEG_S1U_DATA_FW(egIe, mBuf, ieLen)
EgIe       *egIe;
Buffer     *mBuf;
U16        ieLen;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_S1U_DATA_FW)

   SRemPreMsg(&egIe->t.s1UDF.ebi, mBuf);
   egIe->t.s1UDF.ebi = (egIe->t.s1UDF.ebi & 0x0F);

   /* decode the SGW Address length */
   SRemPreMsg(&egIe->t.s1UDF.sgwAddrLen, mBuf);

   if(egIe->t.s1UDF.sgwAddrLen == 0x04)
   {
      egIe->t.s1UDF.sgwAddr.type = CM_TPTADDR_IPV4;
      EG_DEC_U32(egIe->t.s1UDF.sgwAddr.u.ipv4, mBuf);
   } /* end of if */
#ifdef EG_IPV6_SUPPORTED
   else if (egIe->t.s1UDF.sgwAddrLen == 0x0F)
	{
	  egIe->t.s1UDF.sgwAddr.type = CM_TPTADDR_IPV6;
	  SRemPreMsgMult(egIe->t.s1UDF.sgwAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
	} /* end of case */
#endif /* end of CM_TPTADDR_IPV6 */
   else
	{
		RETVALUE(RFAILED);
	}

   /* decode the S1U-TEID */
   EG_DEC_U32(egIe->t.s1UDF.sgwS1UTEID, mBuf);

   RETVALUE(retValue);
} /* end of egAcDecEG_S1U_DATA_FW */


/***********************************************************************
 *   Fun:   egAcDecEG_SRC_RNC_PDCP_CTX
 *   Desc:  Decodes the IE data type Source RNC PDCP Context
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_SRC_RNC_PDCP_CTX
(
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
)
#else
PRIVATE S16 egAcDecEG_SRC_RNC_PDCP_CTX(egIe, mBuf, ieLen)
EgIe       *egIe;
Buffer     *mBuf;
U16        ieLen;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_SRC_RNC_PDCP_CTX)
   EG_DEC_STR(mBuf, egIe->t.valStr.val, egIe->t.valStr.length, EG_MAX_STR_LEN, retValue);

   RETVALUE(retValue);
} /* end of egAcDecEG_SRC_RNC_PDCP_CTX */


/***********************************************************************
 *   Fun:   egAcDecEG_PDUNUM
 *   Desc:  Decodes the IE data type PDU Number
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_PDUNUM
(
EgIe       *egIe,
Buffer     *mBuf,
U16        ieLen
)
#else
PRIVATE S16 egAcDecEG_PDUNUM(egIe, mBuf, ieLen)
EgIe       *egIe;
Buffer     *mBuf;
U16        ieLen;
#endif
{
   S16 retValue = ROK;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDecEG_PDUNUM)

   /* Decode NSAPI */
   SAddPstMsg(egIe->t.pduNum.nsapi, mBuf);

   /* Decode the DownLink GTP-U Sequence Number */
   EG_DEC_U16(egIe->t.pduNum.dnLinkSeqNo, mBuf);

   /* Decode the Uplink GTP-U Sequence Number */
   EG_DEC_U16(egIe->t.pduNum.upLinkSeqNo, mBuf);

   /* Decode the Send N-PDU Number */
   EG_DEC_U16(egIe->t.pduNum.SNPduNo, mBuf);

   /* Decode the Receive N-PDU Number */
   EG_DEC_U16(egIe->t.pduNum.RNPduNo, mBuf);

   RETVALUE(retValue);
} /* end of egAcDecEG_PDUNUM */
/***********************************************************************
 *   Fun:   egAcDecEG_UE_TIME_ZONE
 *   Desc:  Decodes the IE data type Time zone
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_UE_TIME_ZONE
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_UE_TIME_ZONE(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;

   /* decode time zone */
   SRemPreMsg(&egIe->t.timeZone.timezone, mBuf);
   /* decode day light savings time */
   SRemPreMsg(&egIe->t.timeZone.dayLiteSavTime, mBuf);
	egIe->t.timeZone.dayLiteSavTime = egIe->t.timeZone.dayLiteSavTime & 0x03;

   RETVALUE(retValue);
}
/***********************************************************************
 *   Fun:   egAcDecEG_TRACE_REF
 *   Desc:  Decodes the IE data type trace reference
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_TRACE_REF
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_TRACE_REF(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;

   /* decode snkw */
	EG_DEC_NETID(egIe->t.trcRef.sNwk,mBuf);
   /* decode trace id */
   EG_DEC_U32(egIe->t.trcRef.trcId, mBuf);

   RETVALUE(retValue);
}/* egAcDecEG_TRACE_REF */
/***********************************************************************
 *   Fun:   egAcDecEG_RAB_CONTEXT
 *   Desc:  Decodes the IE data type RAB Context
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_RAB_CONTEXT
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_RAB_CONTEXT(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;

   /* decode nsapi */
	SRemPreMsg(&egIe->t.rabCntxt.nsapi,mBuf);
	egIe->t.rabCntxt.nsapi = egIe->t.rabCntxt.nsapi & 0x0F;
	/* decode Downlink GTP-U Sequence Number */
	EG_DEC_U16(egIe->t.rabCntxt.dnlEgUSeqNo ,mBuf);
	/* decode Uplink GTP-U Sequence Number */
	EG_DEC_U16(egIe->t.rabCntxt.uplEgUSeqNo ,mBuf);
	/*decode Downlink GTP-U Sequence Number */
	EG_DEC_U16(egIe->t.rabCntxt.dnlPdcpSeqNo ,mBuf);
	/* decode Uplink GTP-U Sequence Number */
	EG_DEC_U16(egIe->t.rabCntxt.uplPdcpSeqNo ,mBuf);

   RETVALUE(retValue);
} /* egAcDecEG_RAB_CONTEXT */
/***********************************************************************
 *   Fun:   egAcDecEG_GLOBAL_CN_ID
 *   Desc:  Decodes the IE data type Global CN Id
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_GLOBAL_CN_ID
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_GLOBAL_CN_ID(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;

   /* decode sNwk */
	EG_DEC_NETID(egIe->t.gblCnId.sNwk,mBuf);
	/* decode cnId */
   egIe->t.gblCnId.cnId.length = EG_LEN_FOUR;
   EG_DEC_STR(mBuf, egIe->t.gblCnId.cnId.val, egIe->t.gblCnId.cnId.length, EG_LEN_FOUR, retValue);

   RETVALUE(retValue);
} /* egAcDecEG_GLOBAL_CN_ID */

/***********************************************************************
 *   Fun:   egAcDecEG_AMBR_
 *   Desc:  Decodes the IE data type Aggregate Maximum Bit Rate
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_AMBR
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_AMBR(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;

	/*decode APN-AMBR for uplink */
	EG_DEC_U32(egIe->t.ambr.uplAPNAMBR, mBuf);
	/* decode APN-AMBR for downlink */
	EG_DEC_U32(egIe->t.ambr.dnlAPNAMBR, mBuf);

   RETVALUE(retValue);
} /* egAcDecEG_AMBR */

#ifdef EG_REL_930
/***********************************************************************
 *   Fun:   egAcDecEG_MBMS_IPMCAST_DIST
 *   Desc:  Decodes the IE data type RAB Context
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_MBMS_IPMCAST_DIST
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_MBMS_IPMCAST_DIST(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;

	/* decode Common Tunnel Endpoint Identifier Data */
	EG_DEC_U32(egIe->t.mbmsIPMCastDist.cteidDat, mBuf);

   /* decode IP Multicast Distribution Address Type */
   EG_DEC_U8(egIe->t.mbmsIPMCastDist.ipMCastDistAddr.type, mBuf);
   /* decode IP Multicast Distribution Address */
   switch (egIe->t.mbmsIPMCastDist.ipMCastDistAddr.type)
   {
      case CM_TPTADDR_IPV4:
      {
         EG_DEC_U32(egIe->t.mbmsIPMCastDist.ipMCastDistAddr.u.ipv4, mBuf);
         break;
      } /* end of case */
#ifdef EG_IPV6_SUPPORTED
      case CM_TPTADDR_IPV6:
      {
         SRemPreMsgMult(egIe->t.mbmsIPMCastDist.ipMCastDistAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
         break;
      } /* end of case */
#endif /* EG_IPV6_SUPPORTED */
      default:
      {
			RETVALUE(RFAILED);
      } /* end of case */
   }

  /* decode IP Multicast Source Address Type */
   EG_DEC_U8(egIe->t.mbmsIPMCastDist.ipMCastSrcAddr.type, mBuf);
   /* decode IP Multicast Source Address */
   switch (egIe->t.mbmsIPMCastDist.ipMCastSrcAddr.type)
   {
      case CM_TPTADDR_IPV4:
      {
         EG_DEC_U32(egIe->t.mbmsIPMCastDist.ipMCastSrcAddr.u.ipv4, mBuf);
         break;
      } /* end of case */
#ifdef EG_IPV6_SUPPORTED
      case CM_TPTADDR_IPV6:
      {
         SRemPreMsgMult(egIe->t.mbmsIPMCastDist.ipMCastSrcAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
         break;
      } /* end of case */
#endif /* EG_IPV6_SUPPORTED */
      default:
      {
			RETVALUE(RFAILED);
      } /* end of case */
   }

	/* decode MBMS HC Indicator  */
	EG_DEC_U8(egIe->t.mbmsIPMCastDist.mbmsHCInd, mBuf);

   RETVALUE(retValue);
}

/***********************************************************************
 *   Fun:   egAcDecEG_UCI 
 *   Desc:  Decodes the IE data type user CSG information
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_UCI 
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_UCI(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16    ieLen;
#endif
{
   S16 retValue = ROK;
	U8 tmpByte = 0x00;

   /* decode serving network */
	EG_DEC_NETID(egIe->t.uci.sNwk,mBuf);
	
	/* decode CSG Id values */
	/* CSG Id consists of 4 octets. Bit 3 of Octect 8 is the most significant bit and
	 * bit 1 of Octet 11 is the least significant bit
	 */
	EG_DEC_U32(egIe->t.uci.csgId, mBuf);
	egIe->t.uci.csgId &= 0x07FFFFFF;

	EG_DEC_U8(tmpByte, mBuf);
	/* decode access mode */
	egIe->t.uci.accMode =  (tmpByte >> 0x06) && 0x03;
	/* decode LCSG */
	egIe->t.uci.isLCSGPres = ((tmpByte & EG_MASK_BIT2) > 0)?1:0;
	/* decode CMI */
	egIe->t.uci.isCMIPres = ((tmpByte & EG_MASK_BIT1) > 0)?1:0;

   RETVALUE(retValue);
}/* egAcDecEG_UCI */

/***********************************************************************
 *   Fun:   egAcDecEG_CSG_INFO_REP_ACT 
 *   Desc:  Decodes the IE data type CSG information reproting action
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   Notes: None
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egAcDecEG_CSG_INFO_REP_ACT 
(
EgIe   *egIe,
Buffer *mBuf,
U16    ieLen
)
#else
PRIVATE S16 egAcDecEG_CSG_INFO_REP_ACT(egIe, mBuf, ieLen)
EgIe   *egIe;
Buffer *mBuf;
U16     ieLen;
#endif
{
   S16 retValue = ROK;
	U8 tmpByte = 0x00;

	EG_DEC_U8(tmpByte, mBuf);
   /* decode UCICSG */
	egIe->t.csgInfoReqAct.isUCICSGPres = ((tmpByte & EG_MASK_BIT1) > 0)?1:0;
	/* decode UCISHC */
	egIe->t.csgInfoReqAct.isUCISHCPres = ((tmpByte & EG_MASK_BIT2) > 0)?1:0;
	/* decode UCIUHC */
	egIe->t.csgInfoReqAct.isUCIUHCPres = ((tmpByte & EG_MASK_BIT3) > 0)?1:0;

   RETVALUE(retValue);
}/* egAcDecEG_CSG_INFO_REP_ACT */


#endif /* EG_REL_930 */

/****************************************
 * eg009.201 - Modified for S2A and S2B *
 ****************************************/

/*************************************
 * eg009.201 - Added for S2A and S2B *
 *************************************/
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
/*
*
*       Fun:   egAcEgtBuildEgS2aS2bMessage
*
*       Desc:  This function is used to Build EG SN message 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_eguutl.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcEdmBuildEgS2aS2bMessage
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
U8          msgType,
EgMsg       **egMsg,
U8          intfType,
Mem         *memInfo
)
#else
PUBLIC S16 egAcEdmBuildEgS2aS2bMessage(tcCb, spCb, msgType, egMsg, intfType, memInfo)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
U8          msgType;
EgMsg       **egMsg;
U8          intfType;
Mem         *memInfo;
#endif /* ANSI */

{
   TRC2(egAcEdmBuildEgS2aS2bMessage);

   switch(msgType)
    {
      case EGT_GTPC_MSG_CS_REQ:
      {
         /* Build CSREQ */
         egEgtBuildS2AS2BCrtSesReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_CS_RSP:
      {
         /* Build CSRSP based on the response */
         egEgtBuildS2AS2BCrtSesRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_CB_REQ:
      {
          egEgtBuildS2AS2BCrtBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_CB_RSP:
      {
          egEgtBuildS2AS2BCrtBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DS_REQ:
      {
          egEgtBuildS2AS2BDelSesReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DB_REQ:
      {
          egEgtBuildS2AS2BDelBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DS_RSP:
      {
          egEgtBuildS2AS2BDelSesRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DB_RSP:
      {
          egEgtBuildS2AS2BDelBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MB_CMND:
      {
          egEgtBuildS2AS2BModBreCmdMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_MBFAIL_IND:
      {
          egEgtBuildS2AS2BModBreFlrIndMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_UB_REQ:
      {
          egEgtBuildS2AS2BUpdBreReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_UB_RSP:
      {
          egEgtBuildS2AS2BUpdBreRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DPDN_CON_SET_REQ:
      {
          egEgtBuildS2AS2BDelPdnConReqMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_DPDN_CON_SET_RSP:
      {
          egEgtBuildS2AS2BDelPdnConRspMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
       case EGT_GTPC_MSG_TRC_SESS_ACTVN:
      {
          egEgtBuildS2AS2BTrcSessActMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      case EGT_GTPC_MSG_TRC_SESS_DEACTVN:
      {
          egEgtBuildS2AS2BTrcSessDeactMsg(tcCb,spCb,egMsg,intfType,memInfo);
         break;
      }
      default:
      {
         CMXTA_DBG_ERR((_cmxtap,"egAcEdmBuildEgS2aS2bMessage(). Probable mismatch of the interface and the Message Type \n"));
      }
   } /* End of switch */

   RETVALUE(CMXTA_ERR_NONE);
}  /*  egAcEdmBuildEgS2aS2bMessage */

#endif /*end of EG_S2A_SUPP and EG_S2B_SUPP*/
/*eg009.201 Modified for adding S2A and S2B functions*/
#endif /* EGTP_C */

/* End of eGTP-C Ie Data encoding and decoding functions */
#ifdef EGTP_U
/*
*
*    Fun:     egUAcEncEgMsg
*
*    Desc:    Encode the structure EgUMsg
*
*    Ret:     ROK  -ok
*
*    Notes:   None
*
*    File:    egac_cmutl.c
*
*/
#ifdef ANSI
PUBLIC S16 egUAcEncEgMsg
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgUMsg          *eguMsg,  /* the egtp message to be encoded */
Buffer      **mBuf        /* to hold the encoded buffer */
)
#else
PUBLIC S16 egUAcEncEgMsg(tcCb,spCb,eguMsg, mBuf)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgUMsg          *eguMsg;  /* the egtp message to be encoded */
Buffer      **mBuf;       /* to hold the encoded buffer */
#endif
{
   /* this is used to hold the return value of sub methods */
   S16      retVal = 0;
   U8       cnt=0;
   EgUIe    *ie = NULLP;
   CmLList  *tmpNode = NULLP;
   MsgLen    msgLen =0;
   U8        msgType = 0;

#ifdef LEG_FILE_LOG 
   TRC3(egUAcEncEgMsg)
#endif 

   /* validation is successful, do the encoding */
   /* allocating memory for the buffer */
   retVal = SGetMsg(DFLT_REGION, DFLT_POOL, mBuf);
   if(retVal != ROK)
   {
      /* send msg to Main thread with result code set to RFAILED */
      retVal = EGAC_ERR_MEM_ALLOC_FAILED;
      RETVALUE(retVal);
   }
   /* encode the Msg header */
   retVal = egUAcEncodeGmHdr(tcCb, spCb, eguMsg, *mBuf);
   if(retVal != ROK)
   {
      /* free the mBuf */
      SPutMsg(*mBuf);
      RETVALUE(retVal);
   }

   /* update message type */
   msgType = eguMsg->msgHdr.msgType; 

   /* Encoding of  IE's is not required for GPDU's */
   if(msgType != EGT_GTPU_MSG_GPDU)
   {   
      /* encode the IE one by one */
      /* get the first IE in the List */
      CM_LLIST_FIRST_NODE(&eguMsg->u.egIeList, tmpNode);
      for(cnt = 0; ((cnt < eguMsg->u.egIeList.count) && (tmpNode)); cnt++)
      {
         ie = (EgUIe*)tmpNode->node;
         /* encode the IE */
         retVal = egUAcEncIe(tcCb,spCb,ie,*mBuf);
         if(retVal != ROK)
         {
            /* encoding failed. send Msg to Main Thread */
            /* free the mBuf */
            SPutMsg(*mBuf);
            RETVALUE(retVal);
         }
         else
         {
            /* get the next IE from the List */
            CM_LLIST_NEXT_NODE(&eguMsg->u.egIeList, tmpNode);
         }
      }
   }
   else
   {
      /***************************************************************
       * Append the buffer received, with the encoded header buffer  *
       ***************************************************************/
      SCatMsg(*mBuf,eguMsg->u.mBuf,M1M2);
   }

   /************************************************************
    * Calculate total Buffer length and decrement 8bytes, to   *
    * get the value tobe filled in the length field of the     *
    * message header                                           *
    ************************************************************/
   SFndLenMsg(*mBuf, &msgLen);
   msgLen -= EG_LEN_EIGHT;

   /************************************************************
    * Fill the message length, length starts from index 2      *
    ************************************************************/
   cnt = EG_LEN_TWO;

   EGAC_ENC_LEN(msgLen, *mBuf, cnt);

   EgUUtilDeAllocGmMsg(&eguMsg);
   
   RETVALUE(ROK);
} /*end of egUAcEncEgMsg */

/*
 *  
 *   Fun:  egUAcEncodeGmHdr
 *   
 *   Desc:  To encode the Egtp Msg header as per specs
 *   
 *   Ret:   ROK  - for Success
 *   
 *   Notes: None
 *   
 *   File:  egac_egmutl.c
 *   
*/
#ifdef ANSI
PRIVATE S16 egUAcEncodeGmHdr
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
EgUMsg        *eguMsg,
Buffer        *mBuf
)
#else
PRIVATE S16 egUAcEncodeGmHdr( tcCb,spCb,eguMsg, mBuf)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
EgUMsg        *eguMsg;
Buffer        *mBuf;
#endif
{
   S16              retValue = ROK;
   MsgLen           len = EGAC_LEN_THREE;
   EgUMsgHdr         header;
   Data             dumMsgLen[EGAC_LEN_THREE]; /* for length encoding */
   U8               tmpByte=0;
   U8               spareByte[EGAC_LEN_TWO];
   U8               tempMsgType = EGT_GTPU_MSG_GPDU;
   EgAcTCCb        *egTcCb = NULLP;
   U8               unDefMsgType = FALSE;
   U8                invVersion = FALSE;
   U8                invPtType = FALSE;
   U8                unKnownChReqExtHdr = FALSE;
   U8                unKnownChNotReqExtHdr = FALSE;
   U8                unKnownChNotReqExtHdr1 = FALSE;
   U8                extHdr = 0;
   U8              extHdrLenWrong = FALSE;
   U8                tmpBuf[10];
   /* eg006.201: merge changes from eg006.201 --*/
   Bool              extPres = FALSE;      /* Flag for indication of S, E or P presense flag */

       
#ifdef LEG_FILE_LOG 
   TRC3(egUAcEncodeGmHdr)
#endif

   /********************************************
    * Clearing of message lenth and spare byte *
    *******************************************/
   cmMemset((U8*)dumMsgLen, EG_ZERO, len);
   cmMemset((U8*)spareByte, EG_ZERO, EGAC_LEN_TWO);

   /********************************************************
    * Copy the eGTP message header to a local buffer       *
    *******************************************************/
   cmMemset((U8* )&header, 0, sizeof(EgUMsgHdr));
   cmMemcpy( (U8* )&header, (U8* )&(eguMsg->msgHdr),
           sizeof(EgUMsgHdr));

   cmMemset(tmpBuf, 0, 10);

   egTcCb = (EgAcTCCb *)tcCb->tcCb;

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invVersion",  &invVersion);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invPtType",  &invPtType);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"unKnownChReqExtHdr",  
         &unKnownChReqExtHdr);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"unKnownChNotReqExtHdr",  
         &unKnownChNotReqExtHdr);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"unKnownChNotReqExtHdr1",  
         &unKnownChNotReqExtHdr1);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"extHdrLenWrong",  
         &extHdrLenWrong);

   if(!invVersion)
   {
      /********************************************************
      * Encode the version  number 
      *******************************************************/
      tmpByte |= EGAC_MASK_BIT6;
   }
  
   retValue = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"msgType",  &tempMsgType);
   if(retValue != CMXTA_ERR_NO_VALUE)
   {
      header.msgType      = tempMsgType;
   }

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"unDefMsgType",  &unDefMsgType);
   
   if(!invPtType)
   {
   /********************************************************
    * Encode the protocol type 
    *******************************************************/
   tmpByte |= EGAC_MASK_BIT5;
   }


   /*************************************************
    * Encode the Extension Header Flag, if present  *
    *************************************************/
   if(header.extHdr.udpPort.pres || header.extHdr.pdcpNmb.pres)
   {
      tmpByte |=  EGAC_MASK_BIT3;
   }

   /**************************************************
    * Encode the Sequence Number Flag, if present    *
    **************************************************/

   retValue = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"seqNoPrsnt", &header.seqNumber.pres);

   if(header.seqNumber.pres)
   {
      retValue = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U16, (Txt  *)"seqNo", &header.seqNumber.val);
      if(retValue  == CMXTA_ERR_NO_VALUE)
      {
         CMXTA_DBG_ERR((_cmxtap,"egUAcEncodeGmHdr() Sequence number is needed form XML\n"));
         RETVALUE(CMXTA_ERR_INT); 
      }
      tmpByte |=  EGAC_MASK_BIT2;
   }

   /**************************************************
    * Encode the N-PDU Number Flag, if present       *
    *************************************************/
   if(header.nPduNmb.pres)
   {
      tmpByte |=  EGAC_MASK_BIT1;
   }

  /*-- eg006.201: Flag for Aligning Encoder to spec --*/
   if((tmpByte & EG_MASK_BIT1) || (tmpByte & EG_MASK_BIT2)||
                                    (tmpByte & EG_MASK_BIT3))
   {
      extPres = TRUE;
   }
   /*eg012.201:added check */
   if (ROK != SAddPstMsg(tmpByte, mBuf))
   {
      RETVALUE(RFAILED);
   }       

   /*********************************************************
    * Encode the Message Type                             *
    ********************************************************/
   if(unDefMsgType)
   { 
      SAddPstMsg(110, mBuf);
   }
   else
   {
      SAddPstMsg(header.msgType, mBuf);
   }

   /*********************************************************
    * Encode the message length with zeroes                 *
    * At the end of the encoding all the IE's, the final    *
    * Length will be calculated and updated the mBuf        *
    ********************************************************/
   SAddPstMsgMult(dumMsgLen, EGAC_LEN_TWO, mBuf);

   /*********************************************************
    * Encode the Teid                        *
    ********************************************************/
   EGAC_ENC_U32(header.teId, mBuf);

   /*********************************************
    * Encode the sequence number,if present     *
    *********************************************/
   if(header.seqNumber.pres)
   {
      EGAC_ENC_U16(header.seqNumber.val, mBuf);
   }
   /*-- eg006.201: Set the field when extPres flag is TRUE --*/ 
   /*-- eg003.201: IOT compatiblity : Set the field in case 
     PN or Ext Hdr bit is set --*/
    else if (extPres)
    {
       header.seqNumber.val = EG_ZERO ;
       EGAC_ENC_U16(header.seqNumber.val, mBuf);
    }


   /*********************************************
    * Encode the N-PDU Number, if present       *
    *********************************************/
   if(header.nPduNmb.pres)
   {
      SAddPstMsg(header.nPduNmb.val, mBuf);
   }
   /*-- eg006.201: Set the field when extPres flag is TRUE --*/ 
   /*-- eg003.201: IOT compatiblity : Set the field in case 
     Seq No. or Ext Hdr bit is set --*/
    else if (extPres)
    {
      header.nPduNmb.val = EG_ZERO;
      SAddPstMsg(header.nPduNmb.val, mBuf);
    }
   /*********************************************
    * Encode extension headers, if present      *
    *********************************************/
   if(header.extHdr.udpPort.pres)
   {
      if(unKnownChNotReqExtHdr)
      {
         /* CR : 0 0 */
         extHdr = 10; 
         SAddPstMsg(extHdr, mBuf);
      }
      else if(unKnownChNotReqExtHdr1)
      {
         /* CR : 1 0 */
         extHdr = 170;
         SAddPstMsg(extHdr, mBuf);
      }
      else if(unKnownChReqExtHdr)
      {
         /* CR : 1 1 */
         extHdr = 204;
         SAddPstMsg(extHdr, mBuf);
      }
      else
      {
         SAddPstMsg(EGU_EXT_HDR_UDP_TYPE, mBuf);
      }
      if(extHdrLenWrong)
      {
         /* Wrong Ext hdr length */
         SAddPstMsg(EGAC_LEN_TWO, mBuf);
         SAddPstMsgMult(tmpBuf,6,mBuf);
      }
      else
      {
         SAddPstMsg(EGAC_LEN_ONE, mBuf);
         EGAC_ENC_U16(header.extHdr.udpPort.val, mBuf);
      }
   }

   if(header.extHdr.pdcpNmb.pres)
   {
      SAddPstMsg(EGU_EXT_HDR_PDCP_TYPE, mBuf);
      if(extHdrLenWrong)
      {
         /* Wrong Ext hdr len */
         SAddPstMsg(EGAC_LEN_TWO, mBuf);
         SAddPstMsgMult(tmpBuf,6,mBuf);
      }
      else
      {
         SAddPstMsg(EGAC_LEN_ONE, mBuf);
         EGAC_ENC_U16(header.extHdr.pdcpNmb.val, mBuf);
      }
   }

   if(tmpByte & EG_MASK_BIT3)
   {
      SAddPstMsg(EG_ZERO, mBuf);
   }
   /*-- eg003.201: IOT compatiblity : Set the field in case 
     Seq No. or PN bit is set --*/
   else if(extPres)
   {
      SAddPstMsg(EG_ZERO, mBuf);
   }

#ifdef LEG_FILE_LOG
    EG_TRC_FILE(<< egUAcEncodeGmHdr, LEG_DBGMASK_EDM)
#endif

   RETVALUE(ROK);


} /* End of egUAcEncodeGmHdr */


/*
 *  
 *   Fun:  egUAcEncIe
 *   
 *   Desc:  acEncodes the IE 
 *   
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   
 *   Notes: None
 *   
 *   File:  eg_denc.c
 *   
*/
#ifdef ANSI
PRIVATE S16 egUAcEncIe
(
CmXtaTCCb *tcCb,
CmXtaSpCb *spCb,
EgUIe  *ie,
Buffer *mBuf 
)
#else
PRIVATE S16 egUAcEncIe(tcCb,spCb,ie, mBuf)
CmXtaTCCb *tcCb;
CmXtaSpCb *spCb;
EgUIe  *ie;
Buffer *mBuf; 
#endif
{

   S16      retVal = ROK;
   MsgLen   initLen = 0; /* Initial mBuf Length for Grp IE length encoding */
#if 0
   MsgLen   finLen = 0;  /* final mBuf Length for Grp IE length encoding */
   U16   ieLen = 0;  /* actual length of IE being encoded */
#endif
   Data     dumBytes[EGAC_LEN_BYTES];
   /*
   Data     dumBytes1[EGAC_LEN_ONE];
   U8       invRecovIeLen = 1;
   U8       invPvtextIeLen = 3;
   Bool     invalidIeLengthFlag = FALSE; */
#if 0
   EgIeEntry  *ieEntry = NULLP;     /* Holds IE Entry for the IE */
   U16         iePosIdx = 0;        /* Ie Poiton Idx */
#endif
   U8       unknownTvIe = FALSE;
   U8       unknownTlvIe = FALSE;
   U8       ieType = 0;
   /*
   U8       invIeLen = FALSE;
   U8       invOptIeLen = FALSE;  
   U8       invOptIeLen1 = FALSE;*/

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egUAcEncIe);

   cmMemset((U8*)dumBytes, 0, EGAC_LEN_BYTES);

   /*************************
    * Check for IE validity *
    ************************/
   if(ie == NULLP)
   {
      retVal = EGT_ERR_MSG_UNABLE_TO_COMPLY;
      RETVALUE(retVal);
   }
   /*commented as we dont have any ie dictonary
   iePosIdx = egCb.egUCb.edmUCb.egIeCb.posIdx[ie->ieType];
   ieEntry = &(egCb.egUCb.edmUCb.egIeCb.ieEntry[iePosIdx]);
   */

      /****************************************
      * Store the index to encode the length *
      ***************************************/
      SFndLenMsg(mBuf, &initLen);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"unknownTvIe",  &unknownTvIe);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"unknownTlvIe",  &unknownTlvIe);
   if(unknownTvIe)
   {
      /* Replace IE type */
      ieType = 15;
      SAddPstMsg(ieType, mBuf);
    }
    else if (unknownTlvIe && (ie->ieType == EGU_PVT_EXTN_IETYPE))
    {
         /* Replace PVT Ext with a unknown tlv type IE */
         ieType = 138;
         SAddPstMsg(ieType, mBuf);
    }
    else
    {
      /**********************
      * Encode the IE Type *
      *********************/
      SAddPstMsg(ie->ieType, mBuf);
    }

   /*****************************************
    * Encode dummy bytes in the length field *
    ****************************************/

    /*commented:as we dont have any gm dictoniary
   if(!ieEntry->tvType)
   {
      if(ie->ieType != EGU_IE_EXT_HDR_LST)
      {
         SAddPstMsgMult((U8*)dumBytes, EG_LEN_TWO, mBuf);
      }
      else
      {
         SAddPstMsgMult((U8*)dumBytes1, EG_LEN_ONE, mBuf);
      }
   }
   */
   /**********************
    * Encode the IE data  *
    ***********************/ 
   retVal = egUAcEncIeData(ie, mBuf);
   if(retVal != ROK)
   {
      RETVALUE(retVal);
   }

  /*********************************************
   * Insert Correct IE length for TLV type IEs *
   *********************************************/
/*   if(!ieEntry->tvType)
   { */
      /********************************************
       * Calculate final length of the buffer     *
       ********************************************/
   /*   SFndLenMsg(mBuf, &finLen);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invIeLen",  &invIeLen);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invOptIeLen",  
            &invOptIeLen);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"invOptIeLen1",  
            &invOptIeLen1);
      if(invIeLen && (ieEntry->ieCode == EGU_IE_GSN_ADDR))
      {
         ieLen = 20;
      }
      else if( invOptIeLen && (ieEntry->ieCode == EGU_IE_PVT_EXTN))
      { */
         /* Pvt Ext IE length is mentioned as 250 and
          * dummy data related to that is added */
       /*  U8 tmpLen = 0;
         U8 buf[250];
         cmMemset (buf, 0, 250);
         ieLen = 250;
         tmpLen = finLen - initLen - EG_LEN_THREE;
         tmpLen = ieLen - tmpLen;

         SAddPstMsgMult(buf, (MsgLen)tmpLen,mBuf);
      }
      else if(invOptIeLen1 && (ieEntry->ieCode == EGU_IE_PVT_EXTN))
      {  */
         /* ie length is manipulated */
      /*   ieLen = 250;
      }
      else
      {*/
         /***********************************
         * Decrement 3bytes for the ie Hdr *
         ***********************************/
    /*     if(ie->ieType != EGU_IE_EXT_HDR_LST)
         {
            ieLen = finLen - initLen - EG_LEN_THREE;
         }
         else
         {
            ieLen = finLen - initLen - EG_LEN_TWO;
         }
      }
*/
      /***********************************************************
       * Increment the index to point the actual length location *
       ***********************************************************/
  /*    initLen += EG_IE_LEN_OFFSET;

      cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_ENUM_U8,(Txt  *)"invalidIeLengthFlag",&invalidIeLengthFlag);

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,
                 (Txt  *)"invRecovIeLen",  &invRecovIeLen);

      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,
                 (Txt  *)"invPvtextIeLen",  &invPvtextIeLen);

      if(invalidIeLengthFlag)
      {
         switch(ie->ieType)
         {
            case EGAC_RECOV_IETYPE:
               {
                  ieLen = invRecovIeLen;
                  break;
               }
            case EGAC_PEXT_IETYPE:
               {
                  ieLen = invPvtextIeLen;
                  break;
               }
         } * end of switch statement 
      }  end of if statement   */

      /********************************************
       * Encode the offset b/w finLen and initLen *
       ********************************************/
   /*   if(ie->ieType != EGU_IE_EXT_HDR_LST)
      {
         EGAC_ENC_LEN(ieLen, mBuf, initLen);
      }
      else
      {
         SRepMsg(ieLen, mBuf, initLen);
      }
   }  */


   RETVALUE(retVal);
}



/***********************************************************************
*
*   Fun:  egUAcEncIeData
*
*   Desc:  Encode the GTP Msg IE Data part
*
*   Ret:   ROK  - for Success
*          RFAILED - for Failure
*
*   Notes: None
*
*   File:  egac_cmutl.c
*
***********************************************************************/
#ifdef ANSI
PRIVATE S16 egUAcEncIeData
(
EgUIe      *egIe,            /* IE to encode the data portion */
Buffer     *mBuf          /* Buffer to hold the Encoded msg */
) 
#else
PRIVATE S16 egUAcEncIeData(egIe, mBuf)
EgUIe        *egIe;       /* IE to encode the data portion */
Buffer      *mBuf;       /* Buffer to hold the Encoded msg */
#endif
{
   S16         retVal = ROK;           /* Holds the return value */

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egUAcEncIeData);

   /***************************************************************
    * Handling of encoding  of different data types               *
    **************************************************************/
   switch(egIe->dataType)
   {
        case EGAC_UNSIGNED_8:
        {
            SAddPstMsg(egIe->t.valUnSgnd8, mBuf);
            break;
        } /* end of case unsigned 8 */

        case EGAC_UNSIGNED_32:
        {
             EGAC_ENC_U32(egIe->t.valUnSgnd32, mBuf);
             break;
        } /* end of case unsigned 32 */

        case EGAC_PVT_EXTN:
        {
             EGAC_ENC_U16(egIe->t.pvtExt.entId, mBuf);

             /************************************************
              * For encoding the remaining bytes to prop val *
              ***********************************************/
             SAddPstMsgMult(egIe->t.pvtExt.propVal.val,
             egIe->t.pvtExt.propVal.length, mBuf);
             break;
        }       

      case EGAC_IP_ADDR:
         if(egIe->t.ipAddr.addrType == CM_TPTADDR_IPV4)
         {
            EGAC_ENC_U32(egIe->t.ipAddr.u.ipv4, mBuf);
         }
#ifdef EGAC_IPV6_SUPPORTED
         else if (egIe->t.ipAddr.addrType == CM_TPTADDR_IPV6)
         {
            SAddPstMsgMult(egIe->t.ipAddr.u.ipv6, EG_LEN_SIXTEEN, mBuf);
         }
#endif /* EGAC_IPV6_SUPPORTED */
         break;

      case EGAC_EXT_HDR_TYPE_LST:
         {
            U16 cnt = 0;
            for(cnt = 0; cnt < egIe->t.extHdrTypeLst.noOfExtHdrs; cnt++)
               SAddPstMsg(egIe->t.extHdrTypeLst.extType[cnt], mBuf);
            break;
         }
       default:
       {
             retVal = EGT_ERR_INV_IE_TYPE;
       } /* end of case default */

    } /* end of switch case */
    RETVALUE(retVal);    
}
/*
 *
 *       Fun:   egUAcUtlDEdmBuildMsg
 *
 *       Desc:  Build the Edmp Message
 *
 *       Ret:   ROK/RFAILED
 *
 *       Notes: This utility function builds the EGTPU Message
 *
 *       File: egac_cmutl.c
 *
 */

#ifdef ANSI
PUBLIC S16 egUAcUtlDEdmBuildMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgUMsg           **eguMsg
)
#else
PUBLIC S16 egUAcUtlDEdmBuildMsg (tcCb, spCb, eguMsg)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgUMsg           **eguMsg;
#endif
{
   U8            msgType = 0;
   S16            retMsg = 0;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egUAcUtlDEdmBuildMsg)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egUAcUtlDEdmBuildMsg(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egUAcUtlDEdmBuildMsg(), tcId (%d)\n", tcCb->tcId));
#endif


   /*  Default GPDU */
   msgType = (U8) EGT_GTPU_MSG_GPDU;

   retMsg = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt  *)"msgType",  &(msgType));
   if(retMsg == CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"egUAcUtlDEdmBuildMsg() msgType is needed from the xml file\n"));
      RETVALUE(CMXTA_ERR_INT); 
   }
   if((retMsg = egUDEdmBuildEgMsg(tcCb, spCb, msgType, eguMsg)) != CMXTA_ERR_NONE)
        RETVALUE(retMsg);

   RETVALUE(CMXTA_ERR_NONE);
} /*-- egUAcUtlDEdmBuildMsg --*/

/*
*
*       Fun:   egUDEdmBuildEgMsg
*
*       Desc:  This function is used to Build Dummy EG message 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_cmutl.c
*
*/

#ifdef ANSI
PUBLIC S16  egUDEdmBuildEgMsg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
U8                 msgType,
EgUMsg           **eguMsg
)
#else
PUBLIC S16 egUDEdmBuildEgMsg(tcCb, spCb, msgType, eguMsg)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
U8                 msgType;
EgUMsg           **eguMsg;
#endif /* ANSI */
{
   Mem            memInfo;
   S16            ret = 0;
   U8             len = 10;
   U32            lclTeid = EGUAC_DFLT_TEID; 
   U8             buf[100] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                              0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                              0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                              0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                              0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                              0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                              0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                              0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                              0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                              0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egUDEdmBuildEgMsg)

   cmMemset((U8*)&memInfo, 0 , sizeof(Mem));

   memInfo.pool   = DFLT_REGION;
   memInfo.region = DFLT_POOL;

   egUAcEgtBuildEgHeader(tcCb, spCb, &((*eguMsg)->msgHdr), msgType );

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"lclTeid",&(lclTeid));
   (*eguMsg)->lclTeid = lclTeid;

   if(msgType == EGT_GTPU_MSG_GPDU)
   {
      /*-- eg003.201 : Corrected region & pool useage --*/
     if((ret = SGetMsg(memInfo.region, memInfo.pool, &((*eguMsg)->u.mBuf))) != ROK)
     {
        CMXTA_DBG_ERR((_cmxtap,"egUDEdmBuildEgMsg() : Unable to allocate memory for EGTP-U mBuf message\n"));
        RETVALUE(ret);
     }

     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"bufLen",&(len));

     if(len)
     {
      if((ret = SAddPstMsgMult(buf, (MsgLen)len, ((*eguMsg)->u.mBuf))) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap,"egUDEdmBuildEgMsg() : Unable to build EGTP-U mBuf message\n"));
         RETVALUE(ret);
      }
     }
   }
   else
   {
      switch(msgType)
      {
         case EGT_GTPU_MSG_ECHO_REQ:
         {
             /* Build eGTP-U Echo Request Message  */
             ret = eguAcEdmBuildEchoReqMsg(tcCb, spCb, msgType, eguMsg, &memInfo);
             break;
         }
         case EGT_GTPU_MSG_ECHO_RSP:
         {
             /* Build eGTP-U Echo Response Message  */
             ret = eguAcEdmBuildEchoRspMsg(tcCb, spCb, msgType, eguMsg, &memInfo);
             break;
         }
         case EGT_GTPU_MSG_ERROR_IND:
         {
             /* Build eGTP-U Error Indication Message  */
             ret = eguAcEdmBuildErrIndMsg(tcCb, spCb, msgType, eguMsg, &memInfo);
             break;
         }
         case EGT_GTPU_MSG_SUPP_EXT_HDR_NTF:
         {
             /* Build eGTP-U Supported Extension Header Notification Message  */
             ret = eguAcEdmBuildSuppExtHdrNotMsg(tcCb, spCb, msgType, eguMsg, &memInfo);
             break;
         }
         case EGT_GTPU_MSG_END_MARKER:
         {
             /* Build eGTP-U End Marker Message  */
             ret = eguAcEdmBuildEndMarkerMsg(tcCb, spCb, msgType, eguMsg, &memInfo);
             break;
         }
         default:
         {
         }
      }
   }   

   RETVALUE(ret);

} /* egUAcUtlDEdmBuildMsg */   

/*
*
*       Fun:   egUAcEgtBuildEgHeader
*
*       Desc:  This function is used to Build CSR message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_cmutl.c  
*
*/

#ifdef ANSI
PUBLIC Void  egUAcEgtBuildEgHeader
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgUMsgHdr         *eguHdr,
U8                msgType
)
#else
PUBLIC Void egUAcEgtBuildEgHeader(tcCb,spCb,eguHdr,msgType)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgUMsgHdr         *eguHdr;
U8              msgType;
#endif /* ANSI */
{


   U8             pduNmb=0;
   U16            seqNo=0;
   U16            udpPortNmb=0;
   U16            pdcpPortNmb=0;
   U32            remTeid=0;
   Bool           pduNmbPres;
   Bool           seqNoPres;
   Bool           udpextPres;
   Bool           pdcpextPres;
   Bool           FillIes;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egUAcEgtBuildEgHeader)

   pduNmb      = EGUAC_DFLT_PDU_NMB; 
   seqNo       = EGUAC_DFLT_SEQ_NMB;
   udpPortNmb  = EGUAC_DFLT_UDP_PORT_NMB;
   pdcpPortNmb = EGUAC_DFLT_PDCP_PORT_NMB;
   remTeid     = EGUAC_DFLT_TEID;
   FillIes     = TRUE;

   pduNmbPres = FALSE;
   seqNoPres = FALSE;
   udpextPres = FALSE;
   pdcpextPres = FALSE;

   eguHdr->nPduNmb.pres = TRUE;
   eguHdr->seqNumber.pres = TRUE;
   eguHdr->extHdr.udpPort.pres = TRUE;
   eguHdr->extHdr.pdcpNmb.pres = TRUE;

   eguHdr->msgType = msgType;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"pduNmbPres",&(pduNmbPres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,(Txt  *)"npduNmb",&(pduNmb));
   if(pduNmbPres == TRUE)
   {
     eguHdr->nPduNmb.pres = TRUE;
     eguHdr->nPduNmb.val = pduNmb;
   }
   else
     eguHdr->nPduNmb.pres = FALSE;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"seqNoPres",&(seqNoPres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"seqNo",&(seqNo));
   if(seqNoPres == TRUE)
   {
     eguHdr->seqNumber.pres = TRUE;
     eguHdr->seqNumber.val = seqNo;
   }
   else
     eguHdr->seqNumber.pres = FALSE;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"udpextPres",&(udpextPres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"udpPortNmb",&(udpPortNmb));
   if(udpextPres == TRUE)
   {
     eguHdr->extHdr.udpPort.pres = TRUE;
     eguHdr->extHdr.udpPort.val = udpPortNmb;
   }
   else
     eguHdr->extHdr.udpPort.pres = FALSE;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,(Txt  *)"pdcpextPres",&(pdcpextPres));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt  *)"pdcpPortNmb",&(pdcpPortNmb));
   if(pdcpextPres == TRUE)
   {
     eguHdr->extHdr.pdcpNmb.pres = TRUE;
     eguHdr->extHdr.pdcpNmb.val = pdcpPortNmb;
   }
   else
     eguHdr->extHdr.pdcpNmb.pres = FALSE;


   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"remTeid",&(remTeid));
   eguHdr->teId = remTeid;

   RETVOID;
}


/***********************************************************************
 *   Fun:  egUAcDecodeGmHdr
 *   
 *   Desc:  Decodes the GTP-U Msg Header
 *   
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   
 *   Notes: None
 *   
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PRIVATE S16 egUAcDecodeGmHdr 
(
   EgUMsg    *egMsg,         /* Event message stores the decoded hdr */
   Buffer     *mBuf             /* Buffer to decode the header */
 )
#else
PRIVATE S16 egUAcDecodeGmHdr(egMsg, mBuf)
   EgUMsg     *egMsg;         /* Event message stores the decoded hdr */
   Buffer      *mBuf;            /* Buffer to decode the header */
#endif
{
   S16      retVal  = ROK;       /* Holds the return value */
   U8       tmpByte = 0;         /* Holds one byte of data after Dec */
   U8       version = 0;         /* Holds the version type, decoded */
   MsgLen   msgLen  = 0;         /* Holds the msgLen from the Hdr */
   MsgLen   bufLen  = 0;         /* Holds the total buffer length */
   /* eg006.201: merge changes form eg006.201 --*/
   Bool     extPres = FALSE;      /* Flag for indication of S, E or P presense flag */

   EG_TRC2(egUAcDecodeGmHdr);

   /*********************************************
    * Check the length of buffer to be decoded  *
    *********************************************/
   SFndLenMsg(mBuf, &bufLen);

   /**********************************
    * Minimum Msg header is 8 bytes  *
    **********************************/
   if(bufLen <  EGU_MIN_MSG_LEN)
   {
      CMXTA_DBG_ERR((_cmxtap,"egUDecMsgReq() : EgMsg is Null\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*************************************************
    * Store the first byte in tmpByte, Right shift  *
    * 5 times to get version                        *
    *************************************************/
   SRemPreMsg(&tmpByte, mBuf);
   version = tmpByte >> EG_SHIFT_5;

   /*********************************************************
    * Check if the version is 1, if not report INV version  *
    *********************************************************/
   if(version != EGU_MSG_VERSION)
   {
      CMXTA_DBG_ERR((_cmxtap,"egUDecMsgReq() : Invalid version\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /**************************************************************
    * Decode the Protocol Type, and if it is not 1, return error *
    **************************************************************/
   if (!(tmpByte & EG_MASK_BIT5))
   {
      CMXTA_DBG_ERR((_cmxtap,"egUDecMsgReq() : Invalid version\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /******************************
    * decode the message Type    *
    ******************************/
   SRemPreMsg((Data*)&(egMsg->msgHdr.msgType), mBuf);

   /******************************
    * decode the message length  *
    *****************************/
   EG_DEC_U16(msgLen, mBuf);

  /*-- eg006.201: Flag for Aligning Decoder to spec --*/
   if((tmpByte & EG_MASK_BIT1) || (tmpByte & EG_MASK_BIT2)
                                 || (tmpByte & EG_MASK_BIT3))
   {
      extPres = TRUE;
   }

   /*******************************************************************
    * The message length should not have the first 8 mandatory octets *
    * Check whether the message lenght is 8 octets less than the      *
    * total buffer length                                             *
    ******************************************************************/
   if(msgLen != bufLen - EG_LEN_EIGHT)
   {
      CMXTA_DBG_ERR((_cmxtap,"egUDecMsgReq() : Invalid version\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   EG_DEC_U32(egMsg->msgHdr.teId, mBuf);

   /***********************************************
    * Decode the Sequence Number, if S-bit is set *
    ***********************************************/
   if ( tmpByte & EG_MASK_BIT2 )
   {
      egMsg->msgHdr.seqNumber.pres = PRSNT_NODEF;
      EG_DEC_U16(egMsg->msgHdr.seqNumber.val, mBuf);
   }

   /*-- eg006.201: Decode the field in case extPres flag is set --*/ 
   /*-- eg003.201: IOT changes: Decode the field in case
        Ext Hdr. or PN bit is set --*/
	else if(extPres)
	{
      egMsg->msgHdr.seqNumber.pres = NOTPRSNT;
      EG_DEC_U16(egMsg->msgHdr.seqNumber.val, mBuf);
	}

   /*********************************************
    * Decode the N-PDU Number, if PN-bit is set *
    *********************************************/
   if ( tmpByte & EG_MASK_BIT1 )
   {
      egMsg->msgHdr.nPduNmb.pres = PRSNT_NODEF;
      SRemPreMsg(&(egMsg->msgHdr.nPduNmb.val), mBuf);
   }

   /*-- eg006.201: Decode the field in case extPres flag is set --*/ 
   /*-- eg003.201: IOT changes:  Decode the field in case 
        Seq No. or Ext hdr bit is set --*/
	else if(extPres)
	{
      egMsg->msgHdr.nPduNmb.pres = NOTPRSNT;
      SRemPreMsg(&(egMsg->msgHdr.nPduNmb.val), mBuf);
	}

   EG_RETVALUE(retVal); 
} /* End of egUAcDecodeGmHdr() */


/***********************************************************************
 *   Fun:  egUAcDecEgMsg 
 *   
 *   Desc:  Decodes the GTP-U Msg and then validate it.
 *   
 *   Ret:   ROK  - for Success
 *          RFAILED - for Failure
 *   
 *   Notes: None
 *   
 *   File:  eg_edm.c
 **********************************************************************/
#ifdef ANSI
PUBLIC S16 egUAcDecEgMsg 
(
   EgUMsg   *egMsg,
   Buffer   *mBuf
)
#else
PUBLIC S16 egUAcDecEgMsg(egMsg, mBuf )
   EgUMsg   *egMsg;
   Buffer   *mBuf;
#endif
{
   S16            retVal  = ROK;       /* stores the return value */
   MsgLen         msgLen  = 0;         /* Stores Message len. after decoding */
   Mem            mem;                 /* Memory used for allocating */
   Bool           iePres[EGU_MAX_IE];    /* Holds IE Presence value */

   EG_TRC2(egUDecMsgReq);

   if (!egMsg || !mBuf)
   {
      CMXTA_DBG_ERR((_cmxtap,"egUDecMsgReq() : EgMsg is Null\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*********************************************************
    * Initialize memory region and pool                     *
    *********************************************************/
   mem.region = DFLT_REGION;
   mem.pool   = DFLT_POOL;

   /**************************************************
    * Initialize iePres array                        *
    **************************************************/
   cmMemset((Bool *)iePres, EG_ZERO, sizeof(iePres));

   /**************************************************
    * Find the message length for tracking purpose   *
    *************************************************/
   SFndLenMsg(mBuf, &msgLen);

   /**************************************************
    * Decode the GTP-U message header                *
    **************************************************/
   retVal = egUAcDecodeGmHdr(egMsg, mBuf);
   if(retVal != ROK)
   {

      CMXTA_DBG_ERR((_cmxtap,"egUDecMsgReq() : Decoding the header failed\n"));
      SPutMsg(mBuf);
      RETVALUE(CMXTA_ERR_INT);
   }

   EG_RETVALUE(retVal);
} /* End of egUDecMsgReq() */


/*
 *
 *       Fun:   egUAcUtlValidateMsg
 *
 *       Desc:  Decode the Message and validate
 *
 *       Ret:   ROK/RFAILED
 *
 *       Notes: This utility function
 *              validates the Edmp message at the Dummy 
 *
 *       File: xx_egtutl.c 
 *
 */

#ifdef ANSI
PUBLIC S16 egUAcUtlValidateMsg 
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
Buffer     *mBuf
)
#else
PUBLIC S16 egUAcUtlValidateMsg(tcCb, spCb, mBuf)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
Buffer     *mBuf;
#endif
{
   EgUMsg     *egMsg = NULLP;
   U8           xmlMsgType = 0;
   Mem           memInfo;
   EgAcTCCb     *egTcCb = NULLP;  
   S16            ret = 0;
   /*-- eg005.201: Seq Num is updated to 32-bit --*/
   U32          seqNo = 0;
  
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcUtlDEdmValidateMsg);
 
   cmMemset((U8*)&memInfo, 0 , sizeof(Mem));
 
   egTcCb = (EgAcTCCb *)tcCb->tcCb;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap,"egUAcUtlValidateMsg(), tcId (%ld)\n",tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap,"egUAcUtlValidateMsg(), tcId (%d)\n",tcCb->tcId));
#endif
   memInfo.region = DFLT_REGION;
   memInfo.pool   = DFLT_POOL;
   /* Decode the Edmp Message  */
 
   if(EgUUtilAllocGmMsg(&egMsg,&memInfo)!= ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,"egUAcUtlValidateMsg() Unable to allocate the message for GTP-U \n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   if( egUAcDecEgMsg(egMsg,mBuf) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,"egUAcUtlValidateMsg() Unable to Decode the message \n"));
      EgUUtilDeAllocGmMsg(&egMsg);
      RETVALUE(CMXTA_ERR_INT);
   } 

   if(egMsg)
   {
#ifdef LEG_FILE_LOG
   EgUtilGmDump(egMsg,stdout,&position);
#else
   EgUUtilGmDump(egMsg);
#endif /* end of if LEG_FILE_LOG */

      /* Validate the message type  */
      ret = cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_ENUM_U8,(Txt  *)"msgType",&xmlMsgType);
      if(ret != CMXTA_ERR_NO_VALUE)
      {
         if(xmlMsgType != egMsg->msgHdr.msgType)
         {
               CMXTA_DBG_ERR((_cmxtap,"egUAcUtlValidateMsg(): Expected Message Type [%d] Received Message Type[%d]\n",xmlMsgType,egMsg->msgHdr.msgType));
               RETVALUE(CMXTA_ERR_INT);
         } /* end of validation  */
      }
      /*-- eg005.201: Seq Num is updated to 32-bit --*/
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt  *)"seqNo",&(seqNo));
      if(ret != CMXTA_ERR_NO_VALUE)
      {
         if(seqNo != egMsg->msgHdr.seqNumber.val)
         {
            CMXTA_DBG_ERR((_cmxtap, "egUAcUtlValidateMsg() Failed : seqNumber mismatch: exp \
                                     (val=%ld) rcvd (val=%ld) \n",
                         seqNo,
                         egMsg->msgHdr.seqNumber.val));

            RETVALUE(CMXTA_ERR_INT);
         }
      }
   } 
   else
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   EgUUtilDeAllocGmMsg(&egMsg);
   RETVALUE(CMXTA_ERR_NONE);
} /*-- egAcUtlDEdmValidateMsg --*/

#endif /* EGTP_U */

/**********************************************************************

         End of file:     egac_cmutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:23 2015

**********************************************************************/

/********************************************************************40**
 
        Notes:
 
*********************************************************************41*/

/********************************************************************50**
 
*********************************************************************51*/

/********************************************************************60**
 
        Revision history:
 
*********************************************************************61*/

/********************************************************************80**
 
*********************************************************************81*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       ad          1. Created for Initial release 1.1
/main/2      ---       rkumar      1. Initial for eGTP 1.2 Release
/main/2      eg001.102 snatarajan  1. EGTP_C Path management changes.
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3      eg003.201 psingh      1. Merged code from eg006.102 to Fix
                                     TRACE5 macro related issue
                                   2. Updated Region & Pool in argument
                                   3. Encode/Decode changes for IOT 
/main/3      eg004.201 magnihotri  1. Header files added for eGTP-C PSF 
/main/3      eg005.201 psingh      1. Format specifiers for Seq Num updated 
                                      to 32-bit
/main/3      eg006.201 psingh      1. Removed EGTPU_HDR_ALWAYS_PRSNT flag and
                                      updated IOT implementaion
/main/3      eg007.201 psingh      1. Updated egAcDecEgMsg to fill intfMap 
                                      only if intfType is unknown
             eg009.201 asaurabh    1. Added for S2A and S2B.
                                   2. New amcro introduced for better 
                                      understanding
                                   3. Modified for S2A and S2B
/main/3      eg012.201shpandey     1. Added fix for ccpu00124570
                                   2. In function egUAcEncodeGmHdr:added check
*********************************************************************91*/
