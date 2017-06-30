
/**********************************************************************
 
    Name:   RRC layer
 
    Type:   C include file
 
    Desc:   Defines required by LTE-RRC
 
    File:   nhac_acc.h
 
    Sid:      nhac_acc1.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:18:06 2015
 
    Prg:    rer
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000369       RRC
*
*/
 
#ifndef __NHACACCX__
#define __NHACACCX__

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_lte.h"        /* common LTE structures */
#include "ckw.h"            /* C-RLC interface */
#include "kwu.h"            /* D-RLC interface */
#include "crg.h"            /* C-MAC interface */
#include "cpj.h"            /* C-PDCP interface */
#include "pju.h"            /* D-PDCP interface */
#include "nhu.h"           /* RRC Upper Interface */
#include "ctf.h"           /* PHY Interface */
#include "cm_xta.h"
#include "nhac_acc.h"
#include "nh.h"
#include "lnh.h"
#include "cm_pasn.h"
/* external headers */

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_llist.x"      /* common link list */
#include "cm_lte.x"        /* common LTE structures */
#include "cm_xta.x"
#include "ckw.x"            /* C-RLC interface */
#include "kwu.x"            /* D-RLC interface */
#include "crg.x"            /* C-MAC interface */
#include "cpj.x"            /* C-PDCP interface */
#include "pju.x"            /* D-PDCP interface */
#include "nhu_asn.x"
#include "nhu.x"           /* RRC Upper Interface */
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nh.x"
#include "nh_db.x"
#include "nh_3gdb.x"


#ifdef __cplusplus
EXTERN "C" {
#endif

#define CM_PASN_USE_MBUF 1

EXTERN Txt   pbuf[255];

EXTERN CmXtaTCCb*  nhAcPjuTstCbFind ARGS((void));

EXTERN S16  nhAcConstructAndEncode
ARGS((
 Pst *pst,
 U16 msgType,
 Buffer **mBuf,
 CmXtaSpCb    *spCb,
 CmXtaTCCb    *tcCb
));

EXTERN S16  nhAcBuildRRCConReCfgComplete
ARGS((
 Buffer **mBuf
));
EXTERN S16  nhAcBuildRRCConSetupComplete
ARGS((
 Buffer **mBuf,
 CmXtaSpCb    *spCb
));
EXTERN S16  nhAcBuildRRCConReEstReq
ARGS((
Buffer **mBuf,
U8 cause
));
EXTERN S16 nhAcBuildRRCConReq 
ARGS((
Buffer **mBuf
));
EXTERN S16  nhAcBuildRRCSecModeComplete
ARGS((
 Buffer **mBuf
));
EXTERN S16  nhAcBuildRRCSecModeFail
ARGS((
 Buffer **mBuf
));
EXTERN S16  nhAcBuildUpLinkTrfr
ARGS((
 Buffer **mBuf
));
EXTERN S16  nhAcBuildRrcStatus
ARGS((
 Buffer **mBuf
));

EXTERN S16  nhAcBuildHndovrPrepTfr ARGS(( Buffer **mBuf));
EXTERN S16  nhAcBuildCSFBParamCDMA2000Req ARGS(( Buffer **mBuf));
EXTERN S16  nhAcBuildUeCapInfo ARGS(( Buffer **mBuf));
EXTERN S16  nhAcBuildCountChkResp ARGS(( Buffer **mBuf, CmXtaTCCb *tcCb, CmXtaSpCb  *spC));
EXTERN S16  nhAcBuildMeasRpt ARGS(( Buffer **mBuf));
EXTERN S16  nhAcBuildRRCReEstCmp ARGS(( Buffer **mBuf));

EXTERN S16 nhAcValidateStaCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
NhMngmt     *staCfm
));


EXTERN S16 nhAcUtlPjuCb
ARGS((
CmXtaMsgQElm *qElm
));
EXTERN S16 nhAcHdlPjuBndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlPjuUbndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlPjuDatReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlPjuBndCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlPjuDatInd
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlPjuDatCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlPjuStaInd
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

/* KWU Primitives */
EXTERN S16 nhAcHdlKwuBndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlKwuUbndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlKwuBndCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlKwuDatReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlKwuDatInd
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

/* CKW Primitives */
EXTERN S16 nhAcHdlCkwBndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlCkwBndCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlCkwUbndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlCkwCfgReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlCkwCfgCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlCkwUeIdChgReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlCkwUeIdChgCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuBndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlNhuBndCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

/* CRG interface primitives prototype declaration */
EXTERN S16 nhAcHdlCrgBndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlCrgUbndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlCrgCfgReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlCrgBndCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlCrgCfgCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

#ifdef RRC_PHY_CFG_SUPP
/* CTF interface primitives prototype declaration */
EXTERN S16 nhAcHdlCtfBndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlCtfUbndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlCtfCfgReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlCtfBndCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlCtfCfgCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16 nhAcHdlCtfUeIdChgReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 nhAcHdlCtfUeIdChgCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 nhAcCtfGetUnusedCfgIdx ARGS(( U8 *idx));
EXTERN S16 nhAcCtfGetCfgIndx ARGS(( S16 ueCellid, U8 *idx, Bool ueOrCell));

#endif /* RRC_PHY_CFG_SUPP */

EXTERN CmXtaTCCb* nhAcCkwTstCbFind ARGS((Void));

/* NHAC - NHU Primitives --*/
EXTERN S16 nhAcHdlNhuUbndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuDatCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuStaInd
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuErrInd
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuCnclUeReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuDatReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuDatInd
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuDatRsp
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuCfgReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuCfgCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuCellCfgReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuCellCfgCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuDeleteTransReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuPdcpSduStaReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuPdcpSduStaCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuCountReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuCountCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuEncodeReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuEncodeCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuDecodeReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 nhAcHdlNhuDecodeCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
EXTERN S16  nhAcHdlNhuPdcpDataFwdReq
ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

/* NHAC - NHU utl Functions --*/
EXTERN S16 nhAcUtlFillNhuDlCcchConSetup
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatRspSdus *nhuDatRspSdu
));

EXTERN S16 nhAcUtlFillNhuDlCcchConRej
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatRspSdus *nhuDatRspSdu
));

EXTERN S16 nhAcKwuInit ARGS((Void));
EXTERN S16 nhAcKwuDeInit ARGS((Void));

EXTERN S16 nhAcUtlFillNhuDlCcchConReestbRej
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatRspSdus *nhuDatRspSdu
));

EXTERN S16 nhAcUtlCkwGetValIdxUe
ARGS((
U8 *idx,
U16 id
));

EXTERN S16 nhAcUtlCkwGetValIdxCrnti 
ARGS((
U8 *idx,
U16 id
));

EXTERN S16 initRrcXtaAccCb ARGS((Void));

EXTERN S16 nhAcUtlCrgGetValIdxUe
ARGS((
U8 *idx,
U16 id
));

EXTERN S16 nhAcUtlCrgGetValIdxCrnti
ARGS((
U8 *idx,
U16 id
));

#ifdef RRC_PHY_CFG_SUPP
EXTERN S16 nhAcUtlCtfGetValIdxUe
ARGS((
U8 *idx,
U16 id
));

EXTERN S16 nhAcUtlCtfGetValIdxCrnti
ARGS((
U8 *idx,
U16 id
));

EXTERN S16 nhAcCtfValidate
ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */
CtfCfgReqInfo *cfg
));
EXTERN S16 nhAcCtfUeValidate
ARGS ((
NhuPhyCfg *nhuCfg,
CtfDedCfgInfo *ctfCfg
));
EXTERN S16 nhAcCtfUeModValidate
ARGS ((
NhuPhyCfg *nhuCfg,
CtfDedRecfgInfo *ctfCfg
));
EXTERN S16 nhAcCtfCmnValidate
ARGS ((
NhuCmnPhyCfg *nhuCfg,
CtfCellCfgInfo *ctfCfg
));
EXTERN S16 nhAcCtfCmnModValidate
ARGS ((
NhuCmnPhyRecfg *nhuCfg,
CtfCellRecfgInfo *ctfCfg
));
#endif /* RRC_PHY_CFG_SUPP */

EXTERN S16 nhAcUtlCpjGetValIdxUe
ARGS((
U8 *idx,
U16 id
));

EXTERN S16 nhAcUtlCpjGetValIdxCrnti
ARGS((
U8 *idx,
U16 id
));

EXTERN S16 nhAcUtlFillNhuSecurityModeCmd
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhuDatReqSdu
));

EXTERN S16 nhAcUtlFillNhuConRls
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhuDatReqSdu
));

EXTERN U8 nhAcUtlGetNxtValIdx
ARGS ((
Void
));

EXTERN S16 nhAcUtlFillNhuPagingMsg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhDatReqEvntSdu,
U8 sfn,
U8 subFrmNo
));

EXTERN S16 nhAcUtlFillNhuInfoTfr
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhDatReqEvntSdu,
U8 sfn,
U8 subFrmNo
));

EXTERN S16 nhAcUtlFillNhuRrcConReCfgn
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhDatReqEvntSdu,
U8 sfn,
U8 subFrmNo
));

EXTERN S16 nhAcUtlFillNhuNhuBCCH_BCHMsg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhDatReqEvntSdu,
U8 sfn,
U8 subFrmNo
));

EXTERN S16 nhAcUtlFillNhuSysInfo
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhDatReqEvntSdu,
U8 sfn,
U8 subFrmNo
));

EXTERN S16 nhAcUtlFillNhuSysInfoBlockType1
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhDatReqEvntSdu,
U8 sfn,
U8 subFrmNo
));

EXTERN S16 nhAcUtlFillNhuRadioResCfgDedi
ARGS((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
));

EXTERN S16 nhAcUtlFillNhuSRBAddModLst
ARGS((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
));

EXTERN S16 nhAcUtlFillNhuDRBAddModLst
ARGS((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
));

EXTERN S16 nhAcUtlFillNhuDRBRlsLst
ARGS((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
));

EXTERN S16 nhAcUtlFillNhuRRCDediTrChCfg
ARGS((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
));

EXTERN S16 nhAcUtlFillNhuRRCPhyCfgDedi
ARGS((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
));

EXTERN S16 nhAcUtlFillNhuSecurityCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuSecAlgorithmConfig    *securityCfg
));

/*EXTERN S16 nhAcUtlFillNhuUe_RelatedInfo
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuUE_RelatedInfo *ue_RelatedInfo,
NhuDatReqSdus *evnt
));*/

EXTERN S16 nhAcUtlFillNhuUlUmRlc
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuUL_UM_RLC  *ulUmRlc
));

EXTERN S16 nhAcUtlFillNhuDlUmRlc
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDL_UM_RLC  *dlUmRlc
));

EXTERN S16 nhAcUtlFillCellRbCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuRbCfgList  **rbCfgList
));

EXTERN S16 nhAcUtlFillRachCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuRachCfg    *rachCfg
));

EXTERN S16 nhAcUtlFillPucchCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuPucchCfg   *pucchCfg
));

EXTERN S16 nhAcUtlFillPhichCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuPhichCfg   *phichCfg
));

#ifdef RRC_PHY_CFG_SUPP
EXTERN S16 nhAcUtlFillSysBwCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuSysBwCfg   *sysBwCfg
));
#endif

#ifdef TENB_MULT_CELL_SUPPRT
EXTERN S16 nhAcUtlFillMsapCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuLLyrSapIdInfo *llyrSapIdInfo
));
EXTERN S16 nhAcUtlFillUeMsapCfg
ARGS((
CmXtaTCCb          *tcCb,
CmXtaSpCb          *spCb,
NhuUeLLyrSapIdInfo *uellyrSapIdInfo
));
EXTERN S16 nhAcUtlFillUeSapCfg
ARGS((
CmXtaTCCb          *tcCb,
CmXtaSpCb          *spCb,
U16                cellId,
NhuUeLLyrSapIdInfo *uellyrSapIdInfo
));
#endif /* TENB_MULT_CELL_SUPPRT */

EXTERN S16 nhAcHdlMcellNhuDatRsp
ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 nhAcUtlFillRlsRbCfg
ARGS((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
NhuRbRlsCfgList **rlsRbCfg,
Ptr             evnt
));

EXTERN S16 nhAcUtlFillUeRbCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuRbCfgList  **rbCfgList,
U8            rbBitMask,
Ptr           evnt
));

EXTERN S16 nhAcUtlFilUeAddRbCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuRbCfgList  **rbCfgList,
U8            rbBitMask,
Ptr           evnt
));

EXTERN S16 nhAcUtlFilUeModRbCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuRbCfgList  **rbCfgList,
U8            rbBitMask,
Ptr           evnt
));

#ifdef RRC_PHY_CFG_SUPP
EXTERN S16 nhAcUtlFillUePhyAddCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuPhyCfg     *phyCfg,
U8             phyCfgType
));

EXTERN S16 nhAcUtlFillUePhyModCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuPhyCfg     *phyCfg,
U8             phyCfgType
));

EXTERN S16 nhAcUtlFillCmnPhyAddCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuCmnPhyCfg  *cellCfgInfo
));

EXTERN S16 nhAcUtlFillCmnPhyModCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuCmnPhyRecfg  *cellCfgInfo
));
#endif /* RRC_PHY_CFG_SUPP */

EXTERN S16 nhAcUtlFillNhuUeCfgInfo
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuUeCfgInfo  *ueCfg,
Ptr           evnt
));

EXTERN S16 nhAcUtlFillPdcpCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuPdcpCfg    *pdcpCfg,
Ptr           evnt
));

EXTERN S16 nhAcUtlFillTrChCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuTrChCfg    *trChCfg
));

EXTERN S16 nhAcUtlFillSecCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuSecurityCfg     *secCfg
));

EXTERN S16 nhAcUtlFillSCellUeCfg
ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
NhuUeSecCellInfo  *ueSCellCfgInfo
));

EXTERN S16 nhAcUtlFillNewUeCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuNewUeInfo  *ueInfo
));

EXTERN S16 nhAcUtlFillUlLogChCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuUlLogChMap *ulLogChMap
));

EXTERN S16 nhAcUtlFillUlRlcModeInfo
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuUlRlcMode  *ulRlcMode
));

EXTERN S16 nhAcUtlFillDlRlcModeInfo
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDlRlcMode  *dlRlcMode
));

EXTERN S16 nhAcUtlFillNhuEvntHdr
ARGS((
CmXtaTCCb   **tcCb,
CmXtaSpCb   **spCb,
NhuHdr      *nhuHdr
));

EXTERN S16  nhAcUtlFillNhuMobilityCntrlInfo
ARGS ((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuMobilityCntrlInfo *mobCntrlInfo,
Ptr         evnt
));

EXTERN S16 nhAcUtlFillNhuHOSecurityCfg
ARGS ((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuSecConfigHO *secCfgHo,
Ptr         evnt
));

EXTERN S16 nhAcUtlFillNhuRrcConReCfgnHo
ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
Ptr            evnt,
NhuDL_DCCH_Msg *dcchMsg
));

EXTERN S16 nhAcUtlFillNhuHoPrepInfo
ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
Ptr            evnt,
NhuHovrPrepInfo *hoPrepInfo
));
EXTERN S16 nhAcUtlFillNhuUeCapInfo
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
Ptr           evnt,
NhuUECapInfo  *ueCapInfo
));
EXTERN S16 nhAcUtlFillNhuUeRadAccessCapInfo
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
Ptr           evnt,
NhuUERadioAccessCapInfo *ueRACapInfo
));
EXTERN S16 nhAcUtlFillNhuHoCmd
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
Ptr           evnt,
NhuHovrCmd    *hoCmd
));
EXTERN S16 nhAcUtlFillNhuUECapIE
ARGS((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
Ptr         evnt,
NhuUE_EUTRA_Cap *ueEutraCap
));
#if 0 /* TODO - Need to add TCs for IRAT HO container decoding */
EXTERN S16 nhAcUtlFillNhuUE_UTRANHovrInfo
ARGS((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
Ptr         evnt,
NhuUTRANInterRATHovrInfo *ueUtraHovrIfo
));
EXTERN S16 nhAcUtlFillNhuUE_UTRANCapIE
ARGS((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
Ptr         evnt,
NhuUTRANUE_RadioAccessCapInfo *ueEutraCapInfo
));
#endif
EXTERN S16 nhAcUtlFillNhuUeCapEnq
ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
NhuDatReqSdus  *nhuDatReqSdu
));
EXTERN S16 nhAcUtlFillNhuMobFrmEutraCmd
ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
NhuDatReqSdus  *nhuDatReqSdu
));
EXTERN S16 nhAcUtlFillNhuHoFrmEutraPrep
ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
NhuDatReqSdus  *nhuDatReqSdu
));
#ifdef LTERRC_REL9
EXTERN S16 nhAcUtlFillNhuUEInfoRqst
ARGS((
  CmXtaTCCb      *tcCb,
  CmXtaSpCb      *spCb,
  NhuDatReqSdus  *nhuDatReqSdu
));
#endif /*LTERRC_REL9*/

#ifdef NHU_VER2
EXTERN S16 nhAcUtlFillNhuVarShortMACInput
ARGS((
  CmXtaTCCb             *tcCb,
  CmXtaSpCb             *spCb,
  Ptr                   evnt,
  NhuVarShortMAC_Input  *varShortMacInput
));
#endif /* NHU_VER2 */

EXTERN S16 nhAcUtlFillNhuCounterCheckMsg
ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
NhuDatReqSdus  *nhuDatReqSdu
));
EXTERN S16 nhAcUtlFillNhuDlCcchConReestb
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatRspSdus *nhuDatRspSdu
));
EXTERN S16 nhAcUtlFillNhuDlDcchCDMACsfbPrmRsp
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatRspSdus *nhuDatRspSdu
));
#ifdef RRC_PHY_CFG_SUPP
EXTERN S16 nhAcUtlFillPhyCfg
ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuPhyCfg     *phyCfg
));
EXTERN S16 nhAcUtlFillCellPhyCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuCmnPhyCfg  *phyCellCfg
));
EXTERN S16 nhAcUtlFillCellPhyReCfg
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuCmnPhyRecfg  *phyCellCfg
));
#endif
EXTERN S16 nhAcUtlFillNhuHoPrepInfoSIB1
ARGS((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuSysInfoBlockTyp1 *sib1,
Ptr           evnt
));
EXTERN S16 nhAcUtlFillNhuRadioResCfgCmnSibIE
ARGS((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigCmnSIB *radioResCfgCmn,
Ptr         evnt
));
EXTERN S16 nhAcUtlFillNhuSpsCfg
ARGS((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
));

#ifdef LTERRC_REL9
EXTERN S16 nhAcUtlFillNhuMACMainCfg
ARGS((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
));
#endif/* LTERRC_REL9*/



/* EXTERN MsgType; */
typedef struct nhAcKwuCb
{
  U8 loopBack; /* Loop Back Flag */ 
} NhAcKwuCb;

typedef struct nhAcTACb
{
   Txt               ipAddr[20];
   U16               port;
   SpId              macId;
   SpId              rlcId;
   SpId              pdcpId;
#ifdef RRC_PHY_CFG_SUPP
   SpId              phyId;
#endif

}NhAcTACb;

/* Structures to store Ckw Info */
typedef struct nhAcCkwCfgInfo
{
   U32           transId;
   CmLteRnti     ueId;
   CmLteRnti     newUeId;
   CmLteCellId   cellId;
   U8            cfgType; /* Require for CellDel/UE Delete/UEIDchange Req */
   U8            numEnt;
   U8            rbId[CKW_MAX_CFG];
   U8            rbType[CKW_MAX_CFG];
   Bool          used;
}NhAcCkwCfgInfo;

/* Structures to store Ckw Info */
typedef struct nhAcCpjCfgInfo
{
   U32           cpjTransId;
   Bool          used;
   CmLteRnti     ueId;
   CmLteRnti     newUeId;
   CmLteCellId   cellId;
   U8            cfgType; /* Require for UE Id Change req */
   U8            numEnt;
   U8            rbId[CPJ_MAX_CFG];
   U8            rbType[CPJ_MAX_CFG];
}NhAcCpjCfgInfo;

typedef struct nhAcCrgCfgInfo
{
   CrgCfgTransId    crgTransId[MAX_CRG_ID];
   CmLteRnti     ueId;
   Bool          used;
   CmLteCellId   cellId;
   U16           numTrans;
}NhAcCrgCfgInfo;

#ifdef RRC_PHY_CFG_SUPP
typedef struct nhAcCtfCfgInfo
{
   CtfCfgTransId  ctfTransId[MAX_CTF_ID];
   CmLteRnti      ueId;
   Bool           used;
   CmLteRnti      newUeId;
   U8             cfgType; /* needed for UE Id Change req */
   CmLteCellId    cellId;
   U16            numTrans;
}NhAcCtfCfgInfo;
#endif /* RRC_PHY_CFG_SUPP */

/* Structures to store KWU nfo */
typedef struct kwDatReqInfo
{
   CmLteRlcId rlcId;
#ifdef CCPU_OPT
   CmLteLcType       lcType;
   union
   {
      CmLteTimingInfo   tmg;              /*!< Timing  for BCCH/PCCH */
      CmLteRnti         rnti;             /*!< Temporary CRNTI:Applicable for CCCH. */
   }tm;                                   /*!< TM common channel  */
#endif
}KwDatReqInfo;

typedef struct nhAcKwInfo
{
   SuId              suId;
   SpId              spId;
   KwDatReqInfo      datReqInfo;
   Reason            reason;
}NhAcKwInfo;

typedef struct nhAcKwuInfo
{
   NhAcKwInfo  kwInfo;
   NhAcKwuCb   loop;
}NhAcKwuInfo;

typedef struct nhAcPjuInfo
{
   SpId     spId;
   SuId     suId;
   Reason   reason;
   U8       loopBack;
   CmLtePdcpId      pdcpId;
}NhAcPjuInfo;
/* This structure is used for sending back Rfailed from the lower layer
 * interface primitives.This is used to simulate the error scenario */
typedef struct nhAcSndErrReq
{
   U8   rcvMacErr;
   U8   rcvRlcErr;
   U8   rcvPdcpErr;
#ifdef RRC_PHY_CFG_SUPP
   U8   rcvPhyErr;
#endif
   U8   expMacErr;
   U8   expRlcErr;
   U8   expPdcpErr;
#ifdef RRC_PHY_CFG_SUPP
   U8   expPhyErr;
#endif
}NhAcSndErrReq;
/* This structure is used for storing encoded buffer to send in DatReq in 
 * case of HO */
typedef struct nhAcHoEncBufInfo
{
   Bool   encBufPres;
   U32    msgLen;        /*!< size of encoded data in bits */
   Buffer *encBuf;

}NhAcHoEncBufInfo;

/* This structure is used for storing CFG or DAT request status
  which should be reterned from lower layers to generate failure
 * cases */
typedef struct nhAcReqFail
{
   Bool     crgCfg;
   Bool     cpjCfg;
   Bool     ckwCfg;
   Bool     pjuDat;
   Bool     kwuDat;
   Bool     ueIdChg;
}NhAcReqFail;
/* Acceptance Test Global Structure */
typedef struct nhAccCb
{
   NhAcTACb           taCb;
   U32              ckwInd;
   NhAcKwuInfo      kwuCb; 
   NhAcCkwCfgInfo   ckwCfgInfo[CKW_MAX_CFG];
   NhAcCpjCfgInfo   cpjCfgInfo[CPJ_MAX_CFG];
   U32              ckwTransId[CKW_MAX_CFG];
   /*xta mac specific control structure*/
   CrgCfgTransId    crgTransId[MAX_CRG_ID];
   U32              crgInd;

#ifdef RRC_PHY_CFG_SUPP
   NhAcCtfCfgInfo   ctfCfgInfo[CTF_MAX_CFG];
   CtfCfgTransId    ctfTransId[MAX_CTF_ID];
   U32              ctfInd;
#endif
   U32              cpjInd;
   U32              cpjTransId[MAX_CPJ_ID];
   U32              noOfrb;
   U32              start;
   U8               rlcMode;
   U32              mui;
   NhAcPjuInfo      pjuCb;
   Bool             valChk;
   NhAcSndErrReq    sndErrReq;
   NhAcHoEncBufInfo encBufInfo;
   Bool             makeCfmFail;
   NhAcReqFail      reqFail;
}NhAccCb;

EXTERN NhAccCb nhAccCb;

EXTERN S16 nhAcRgActvTsk
ARGS((
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
));
EXTERN S16 nhAcKwActvTsk
ARGS((
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
));
EXTERN S16 nhAcPjActvTsk
ARGS((
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
));
#ifdef RRC_PHY_CFG_SUPP
EXTERN S16 nhAcTfActvTsk
ARGS((
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
));
#endif /* RRC_PHY_CFG_SUPP */
EXTERN S16 nhAcNxActvTsk
ARGS((
Pst    *pst,                /* post */
Buffer *mBuf                /* message buffer */
));
EXTERN S16 nhAcPjActvInit
ARGS((
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
));
#ifdef RRC_PHY_CFG_SUPP
EXTERN S16 nhAcTfActvInit
ARGS((
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
));
#endif  /* RRC_PHY_CFG_SUPP */
EXTERN S16 nhAcRgActvInit
ARGS((
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
));
EXTERN S16 nhAcNxActvInit
ARGS((
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
));
EXTERN S16 nhAcKwActvInit
ARGS((
Ent entity,            /* entity */
Inst inst,             /* instance */
Region region,         /* region */
Reason reason          /* reason */
));

typedef struct nhAcCmInfo
{
   SuId              suId;
   SpId              spId; 
   Reason            reason;
}NhAcCmInfo;

typedef struct nhAcCkwInfo
{
   NhAcCmInfo     cmInfo;
   CkwCfgInfo     cfgInfo; 
   CkwUeInfo      ueInfo;
   CkwUeInfo      newUeInfo;
   U32            transId;
}NhAcCkwInfo; 

typedef struct nhAcNhuInfo
{
   SuId           suId;
   Status         status;
   U16             decMsgType;
   NhAcHoEncBufInfo encBufInfo;
}NhAcNhuInfo; 

/******************************************************************************/
/*CRG Interface Structure definition and function declarations-start*/
/******************************************************************************/
typedef struct nhAcCrgInfo
{
   NhAcCmInfo  cmInfo;
   CrgCfgTransId transId;
   CrgCfgReqInfo cfgInfo;
}NhAcCrgInfo;

typedef struct nhAcCpjInfo
{
   NhAcCmInfo  cmInfo;
   U32 transId;
   CpjCfgReqInfo cfgInfo;
   CpjSecCfgReqInfo secCfgInfo;
   CpjUeInfo ueInfo;
   CpjUeInfo newUeInfo;
}NhAcCpjInfo;

/******************************************************************************/
/*CRG Interface Structure definition and function declarations-end*/
/******************************************************************************/
#ifdef RRC_PHY_CFG_SUPP
typedef struct nhAcCtfInfo
{
   NhAcCmInfo     cmInfo;
   CtfCfgTransId  transId;
   CtfCfgReqInfo  cfgInfo;
   CtfUeInfo      ueInfo;
   CtfUeInfo      newUeInfo; 
}NhAcCtfInfo;

#endif /* RRC_PHY_CFG_SUPP */

/* Message queue element */
typedef struct nhAccMsgQElm
{
   Pst           pst;    /* pst structure */
   Buffer        *mBuf;
   union
   {
      /* to Support other Info */   
      NhMngmt       nhMngmt;
      NhAcKwuInfo   kwuInfo;
      NhAcCkwInfo   ckwInfo;
      NhAcCrgInfo   crgInfo;
      NhAcCpjInfo   cpjInfo; 
      NhAcPjuInfo   pjuInfo;
      NhAcNhuInfo   nhuInfo;
#ifdef RRC_PHY_CFG_SUPP
      NhAcCtfInfo   ctfInfo;
#endif
   }u;
   PMSGFREEFS16      msgFreeFun;       /* Function to free the msg */
}NhAccMsgQElm;

/*CPJ Cfg parameters validation structure*/
typedef struct nhaccCpjEnt
{
   U8  rbId;
   U8  pdcpId;
   U8  cfgType;
   U8  cfgReqBitMask;
   CpjRlcInfo rlcInfo;
   U32  discardTmr;
   CpjHdrCompCfg hdrComCfg;
}NhaccCpjEnt;


typedef struct nhAccCpjSecVal
{
   NhuIntgKeyAlgoInfo   intgCfgInfo;
   NhuCiphKeyAlgoInfo   cipCfgInfo;
   CpjSecCfg            secCfg;
   Bool                 conReCfgCause;
   U8                   secCfgBitMsk;
}NhAccCpjSecVal;

typedef struct nhAccCpjVal
{
   CmLteRnti ueId;
   Bool used;
   U16 tCrnti;
   CmLteCellId cellId;
   U32     transId;
   U8 numEnt;
   NhaccCpjEnt entity[CPJ_MAX_CFG];
   NhAccCpjSecVal secInfo;
}NhAccCpjVal;
/*CPJ Cfg parameters validation structure-end*/

/*CKW Cfg parameters validation structure*/
typedef struct nhaccCkwEnt
{
   U8  cfgType;
   U8  rbId;
   CmLteRlcMode         entMode;           
   U8                   dir;
}NhaccCkwEnt;

typedef struct nhAccCkwVal
{

   U32                  transId;             
   CmLteRnti            ueId;                
   CmLteCellId          cellId;
   U16  tCrnti;
   NhaccCkwEnt         entity[CKW_MAX_ENT_CFG];
   Bool used;
}NhAccCkwVal;
/*CKW Cfg parameters validation structure-end*/

/*CRG Cfg parameters validation structure*/
/*tydef struct nhaccCfgUe
{
cellId
crnti
}NhaccCfgUe*/

typedef struct nhaccRecfgLch
{
U8 rbId;
U8 dir;
U8 lcId;
}NhaccRecfgLch;

typedef struct nhaccCfgLch
{
U8 rbId;
U8 dlTrchType;
U8 ulTrchType;
U8 dir;
U8 lcId;
}NhaccCfgLch;

typedef struct nhaccCrgRecfg
{
/*NhaccRecfgUe uecfg;*/
NhaccRecfgLch lchCfg[10];
}NhaccCrgRecfg;

typedef struct nhaccCrgCfg
{
/*NhaccCfgUe uecfg;*/
NhaccCfgLch lchCfg[10];
}NhaccCrgCfg;

/*typedef struct nhaccCrgRlsCfg
{
NhaccRlsCfgUe ueCfg;
NhaccRlsCfglch lchCfg[10];
}NhaccCrgRlsCfg;*/

typedef struct nhAccCrgVal
{
U16 tCrnti;
CmLteCellId    cellId;
U16 ueId;
Bool used;
   union
   {
     NhaccCrgCfg crgCfg;
     NhaccCrgRecfg crgReCfg;
     /*NhaccCrgRlsCfg crgRlsCfg;*/
   }u;
}NhAccCrgVal;
#ifdef RRC_PHY_CFG_SUPP
typedef struct nhAccCtfVal
{
U32 transId;             
U16 tCrnti;
CmLteCellId    cellId;
U16 ueId;
Bool used;
   union
   {
     NhuPhyCfg       phyCfg;
     NhuCmnPhyCfg    cellCfgInfo;
     NhuCmnPhyRecfg  cellRecfgInfo;
   }u;
}NhAccCtfVal;
#endif /* RRC_PHY_CFG_SUPP */

/*CRG Cfg parameters validation structure-end*/
EXTERN S16 nhAcUtlFillValRbRlsCfgUe
ARGS((
NhuRbRlsCfgList  *lclRlsRbCfg
));

EXTERN S16 nhAcUtlFillValRbCfgLstUe
ARGS((
U8            rbBitMask,
NhuRbCfgList  **rbCfgList
));

EXTERN S16 nhAcFillCpjSecValid
ARGS((
NhuSecurityCfg *secCfg
));

EXTERN S16 nhAcCrgValidate ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb,CrgCfgReqInfo *cfg));

EXTERN CmXtaTCCb*  nhAcCrgTstCbFind ARGS((Void));

EXTERN S16 nhAcCkwValidate ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb,CkwCfgInfo *ckwCfgParam));
EXTERN S16 nhAcUtlCpjVal ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, CpjCfgReqInfo *req));
EXTERN S16 nhAcUtlCpjSecVal ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, CpjSecCfgReqInfo *req));


#ifdef RRC_PHY_CFG_SUPP
EXTERN CmXtaTCCb*  nhAcCtfTstCbFind ARGS((Void));
EXTERN S16 nhAcUtlCtfCb
ARGS((
CmXtaMsgQElm *qElm
));

#endif /* RRC_PHY_CFG_SUPP */

EXTERN S16 nhAcUtlCrgCb
ARGS((
CmXtaMsgQElm *qElm
));

EXTERN S16 nhAcHdlCpjBndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 nhAcHdlCpjBndCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 nhAcHdlCpjCfgReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 nhAcHdlCpjCfgCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 nhAcHdlCpjUbndReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 nhAcHdlCpjUeIdChgReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 nhAcHdlCpjUeIdChgCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 nhAcHdlCpjReEstReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
));

EXTERN S16 nhAcHdlCpjReEstCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
));

EXTERN S16 nhAcHdlCpjSecCfgReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
));

EXTERN S16 nhAcHdlCpjSecCfgCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
));

EXTERN S16 nhAcHdlCpjCountReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
));

EXTERN S16 nhAcHdlCpjCountCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
));

EXTERN S16 nhAcHdlCpjSduStaReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
));

EXTERN S16 nhAcHdlCpjSduStaCfm
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structcre  */
CmXtaSpCb    *spCb     /* spCb data structcre  */
));

EXTERN S16 nhAcUtlKwuCb
ARGS((
CmXtaMsgQElm *qElm
));

EXTERN S16  nhAcGetSapIdFromProt
ARGS((
int macro
));

EXTERN S16  nhAcConstructAndEncodeCcchMsg
ARGS((
Pst *pst,
U16 msgType,
Buffer **mBuf,
CmXtaSpCb    *spCb,
CmXtaTCCb    *tcCb
));

EXTERN S16 nhAcUtlCpjCb
ARGS((
CmXtaMsgQElm *qElm
));

EXTERN S16 nhAcUtlCkwCb
ARGS((
CmXtaMsgQElm *qElm
));
EXTERN S16 nhAcUtlLnhCb
ARGS((
CmXtaMsgQElm *qElm
));
EXTERN S16 nhAcUtlLnhSendMsg
ARGS((
Pst         *pst,
NhMngmt     *cfm,
Buffer      *mBuf
));
EXTERN Void nhAcGetStatus
ARGS((
Void           *curStep,
CmStatus       *status
));
EXTERN S16 nhAcValidateStatus
ARGS((
CmStatus       *status,
CmStatus       *incStatus
));
EXTERN S16 nhAcUtlNhBuildPnodeCntrlReq
ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
NhMngmt   *nhMngmt
));
EXTERN S16 nhAcUtlNhBuildStartCntrlReq
ARGS((
NhMngmt     *nhMngmt
));


/* Extern linkage for Layer Manager Handler function */

EXTERN CmXtaTCCb*  nhAcKwuTstCbFind ARGS((void));

EXTERN S16 nhAcHdlNhGenCfgReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhUsapCfgReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhLsapCfgReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhProtCfgReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhCfgCfm ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhUstaCntrlReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhLsapCntrlReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhUsapCntrlReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
#ifdef NH_TRACE_ENABLED
EXTERN S16 nhAcHdlNhTrcCntrlReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
#endif
EXTERN S16 nhAcHdlNhPnodeTrcCntrlReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
/* #ifdef DEBUGP */
EXTERN S16 nhAcHdlNhDebugCntrlReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
/* #endif */
EXTERN S16 nhAcHdlNhShutDownCntrlReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhStartCntrlReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhCntrlCfm ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhGenStsReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhPnodeStsReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhCellStsReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhStsCfm ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhSysStaReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhUsapStaReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhGenStaReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhLsapStaReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhStaCfm ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhStaInd ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
EXTERN S16 nhAcHdlNhTrcInd ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb));
/* Extern linkage for Layer Manager Utility function */

EXTERN S16 nhAcUtlNhBuildGenCfgReq ARGS((CmXtaTCCb  *tcCb,
                                         CmXtaSpCb  *spCb,
                                         NhMngmt    *nhMngmt));
EXTERN S16 nhAcUtlNhBuildUsapCfgReq ARGS((CmXtaTCCb  *tcCb,
                                          CmXtaSpCb  *spCb,
                                          NhMngmt    *nhMngmt));
EXTERN S16 nhAcUtlNhBuildLsapCfgReq ARGS((CmXtaTCCb  *tcCb,
                                          CmXtaSpCb  *spCb,
                                          NhMngmt    *nhMngmt));
EXTERN S16 nhAcUtlNhBuildProtCfgReq ARGS((CmXtaTCCb  *tcCb,
                                          CmXtaSpCb  *spCb,
                                          NhMngmt    *nhMngmt));
EXTERN S16 nhAcUtlNhBuildUstaCntrlReq ARGS((CmXtaTCCb  *tcCb,
                                            CmXtaSpCb  *spCb,
                                            NhMngmt    *nhMngmt));
EXTERN S16 nhAcUtlNhBuildUsapCntrlReq ARGS((CmXtaTCCb  *tcCb,
                                            CmXtaSpCb  *spCb,
                                            NhMngmt    *nhMngmt));
EXTERN S16 nhAcUtlNhBuildLsapCntrlReq ARGS((CmXtaTCCb  *tcCb,
                                            CmXtaSpCb  *spCb,
                                            NhMngmt    *nhMngmt));
EXTERN S16 nhAcUtlNhBuildTrcCntrlReq ARGS((CmXtaTCCb  *tcCb, 
                                               CmXtaSpCb  *spCb,
                                               NhMngmt    *nhMngmt));
#ifdef DEBUGP
EXTERN S16 nhAcUtlNhBuildDebugCntrlReq ARGS((CmXtaTCCb  *tcCb,
                                             CmXtaSpCb  *spCb,
                                             NhMngmt    *nhMngmt));
#endif 
EXTERN S16 nhAcUtlNhBuildShutdownCntrlReq ARGS((NhMngmt  *nhMngmt));

EXTERN S16 nhAcUtlFillNhuRLCDrbCfg ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb,
                                         NhuRLC_Config *rlcCfg, Ptr evnt));

EXTERN S16 nhAcUtlFillNhuPDCPDrbCfg ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb,
                                         NhuPDCP_Config *pdcpCfg, Ptr evnt));

EXTERN S16 nhAcNhuSaveMsg ARGS((Pst  *pst, SuId suId, U8 status,
                                void *nhuInfo));

EXTERN CmXtaTCCb* nhAcNhuTstCbFind ARGS((Void));

EXTERN S16 nhAcUtlNhuCb ARGS((CmXtaMsgQElm *qElm));

EXTERN S16 nhAcUtlStrToken ARGS((Txt *line, Txt *frstWord, Txt delimiter));

EXTERN S16 nhAcNhuInit ARGS((Void));

EXTERN S16 nhAcNhuDeInit ARGS((Void));

EXTERN S16 NxLiNhuBndReq  ARGS(( Pst *pst, SuId suId, SpId spId ));

EXTERN S16 NxLiNhuUbndReq  ARGS(( Pst *pst, SpId spId, Reason reason));

EXTERN S16 NxLiNhuDatReq  ARGS((Pst *pst, SpId spId, 
                                NhuDatReqSdus *nhuDatReqSdus));

EXTERN S16 NxLiNhuDatRsp  ARGS((Pst *pst, SpId spId, 
                                NhuDatRspSdus *nhuDatRspSdus));

EXTERN S16 NxLiNhuCfgReq  ARGS((Pst *pst, SpId spId, 
                                NhuCfgReqSdus *nhuCfgReqSdus));

EXTERN S16 NxLiNhuCellCfgReq  ARGS((Pst *pst, SpId spId, 
                                    NhuCellCfgReqSdus *nhuCfgReqSdus));

EXTERN S16 NxLiNhuCnclUeReq  ARGS((Pst *pst, SpId spId, NhuCellId cellId, NhuCrnti ueId));

EXTERN S16 NxLiNhuDeleteTransReq  ARGS((Pst *pst, SpId spId, NhuCellId cellId, NhuCrnti ueId, U32 transId));
EXTERN S16 NxLiNhuPdcpSduStaReq ARGS((Pst *pst, SuId suId, NhuHdr  nhuHdr));
EXTERN S16 NxLiNhuCountReq ARGS((Pst *pst, SuId suId, NhuHdr  *cntHdr));
EXTERN S16 NxLiNhuEncodeReq ARGS((Pst *pst, SuId suId, NhuEncReqSdus *nhuEncReqSdus));
EXTERN S16 NxLiNhuDecodeReq ARGS((Pst *pst, SuId suId, NhuDecodeSduReq *nhuDecodeSduReq));
EXTERN S16 NxLiNhuPdcpDatFwdReq ARGS(( Pst *pst,SuId  suId,NhuHdr nhuHeader));

EXTERN S16 nhAcCrgInit ARGS((Void));
EXTERN S16 nhAcCkwInit ARGS((Void));
EXTERN S16 nhAcLnhInit ARGS((Void));
EXTERN S16 nhAcCpjInit ARGS((Void));
EXTERN CmXtaTCCb*  nhAcCpjTstCbFind ARGS((Void));
EXTERN S16 nhAcPjuInit ARGS((Void));
EXTERN S16 nhAcCrgDeInit ARGS((Void));
EXTERN S16 nhAcCkwDeInit ARGS((Void));
EXTERN S16 nhAcCpjDeInit ARGS((Void));
EXTERN S16 nhAcPjuDeInit ARGS((Void));
EXTERN S16 nhAcUtlPjuFillForDecodeFail ARGS((Buffer **mBuf));
#ifdef LTERRC_REL9
EXTERN S16  nhAcBuildUeInfoResp ARGS((Buffer **mBuf,CmXtaTCCb    *tcCb,CmXtaSpCb    *spCb));
EXTERN S16  nhAcBuildProximityInd ARGS((Buffer **mBuf,CmXtaTCCb    *tcCb,CmXtaSpCb    *spCb));
#endif
EXTERN S16 nhAcLnhDeInit ARGS((Void));
EXTERN S16 nhAcCpjUtlStrToken ARGS(( Txt *line, Txt *frstWord, Txt  delimiter));
EXTERN S16 nhAcUtlFillFailStatus ARGS((CmXtaTCCb   *tcCb, CmXtaSpCb   *spCb));
#ifdef RRC_PHY_CFG_SUPP
EXTERN S16 nhAcCtfInit ARGS((Void));
EXTERN S16 nhAcCtfDeInit ARGS((Void));
#endif

#ifdef __cplusplus
}
#endif


#endif

/**********************************************************************
         End of file:     nhac_acc1.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:18:06 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      rer                1. LTE RRC Initial Release.
/main/2      ---      ch                 1. RRC Release 2.1.
/main/3      ---      sbalakrishna       1. Updated for Release of 3.1
*********************************************************************91*/


