
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_rrc_msg.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_UMM_RRC_MSG_H__
#define __WR_UMM_RRC_MSG_H__

#include "wr.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

EXTERN S16 wrUmmRrcFillUeSrbInfo (WrUeRBInfo *srbCfg,U8  rabId);
EXTERN S16 wrUmmRrcFillConSetup (NhuDatRspSdus *nhuDatRspSdu,  WrUeCb *ueCb);
EXTERN S16 wrFillRrcSrbAddModLst (NhuRadioResourceConfigDedicated *radioResCfg,
                                           WrUeCb *ueCb, Ptr evnt, U8 srbId);
EXTERN S16 wrFillNhuUeCfgInfo (Ptr evnt, NhuUeCfgInfo *ueCfg, WrUeCb *ueCb,
                                                                 U8 msgType);
EXTERN S16 wrFillPdcpCfg (NhuPdcpCfg *pdcpCfg, U8 rbId, U8 cfmReqd,
                                                               WrUeCb *ueCb);
EXTERN S16 wrFillTrChCfg (NhuTrChCfg *trChCfg,WrUeCb  *ueCb);
EXTERN S16 wrUmmRrcFillSecCfg(NhuSecurityCfg *rrcSecCfg, WrUeSecCfg *secCfg);
EXTERN S16 wrUmmRrcFillSecModeCmd (U32 transId, WrUeSecCfg *secCfg, 
                                               NhuDatReqSdus *rrcDatReqSdu, U32 ueRlsVer);
EXTERN S16 wrFillRadResPhyCfgDed(NhuRadioResourceConfigDedicated *radioResCfg, 
                                            Ptr evnt, U8 rbId, WrUeCb *ueCb);
EXTERN S16 wrFillUeAddRbCfg (NhuRbCfgList **rbCfgList,WrUeCb *ueCb,U8 msgType);
EXTERN S16 wrUmmRrcCreateRrcReconfigMsg(NhuDatReqSdus *recfgMsg,
                                                             U8 recfgTransId);
EXTERN S16 wrUmmRrcPrepRadioResourceDed(
                                   NhuRadioResourceConfigDedicated *radioRes);
/* SPS changes starts */
EXTERN S16 wrUmmRrcReconfigFillDrb(WrUeCb *ueCb, Bool bIsUeSpsEnabled, NhuDRB_ToAddMod *drbIe, U8 erabId, 
                 U8 drbId, U8 lchId, U8 qci, Bool isDlSpsEnabled, Bool isUlSpsEnabled);

EXTERN Void wrUmmRrcReconfigFillulPbr(NhuDRB_ToAddMod *drbIe,U32 ulGbr,U32 qci,Bool isUlSpsEnabled);

/* SPS changes ends */
EXTERN S16 wrUmmRrcFillSrbIE(U16 cellId, NhuSRB_ToAddMod *srbIe, U8 isSrb1);
/* SPS changes starts */
EXTERN S16 wrUmmRrcAddDrbCfg(U16 cellId, NhuRbCfgInfo *drbCfg, U8 drbId, U8 lcId, U8 qci, Bool isUlSpsEnabled);
/* SPS changes ends */
EXTERN S16 wrUmmRrcFillUeCapEnq (NhuDatReqSdus *nhuDatReqSdu, 
                                  WrUmmRatLst *ratLst, U32 transId);
EXTERN S16 wrUmmRrcFillUeRadAccCapInfo (TknStrOSXL  *encodedInfo, 
                                       NhuEncReqSdus *encReq, WrUeCb *ueCb);
EXTERN S16 wrUmmRrcFillDlInfTfr(NhuDatReqSdus *dlInfoTfrPdu, 
                                             TknStrOSXL *nasPdu, U8 pdcpId);
EXTERN S16 wrUmmFillRrcEvntHdr(NhuHdr *nhuHdr, U16 cellId, U16 crnti, 
                                                               U32 transId);
EXTERN S16 wrUmmRrcBldConRls(WrUeCb *ueCb, U8 accessStratumRls, WrUmmRedirectInfo
      *redirectInfo, NhuDatReqSdus *sdu, U32 relCause, U32 t320InMin);

EXTERN S16 wrUmmRrcAddSrbCfg(U16 cellId, NhuRbCfgInfo *srbCfg, U8 isSrb1);
EXTERN S16 wrUmmRrcAddSrb1Cfg(Ptr evnt, NhuUeCfgInfo *ueCfg, WrUeCb *ueCb);
EXTERN S16 wrUmmFillRrcReEstabSetup(NhuDatRspSdus *nhuDatRspSdu, WrUeCb *ueCb);
EXTERN S16 wrUmmRrcDedNASInfo(NhuDatReqSdus *evnt, 
                     NhuRRCConRecfgn_r8_IEs *reCfgIes, TknStrOSXL *nasPdu);
EXTERN S16 wrUmmRrcBldReestabReject(NhuDatRspSdus *reestabRejSdu);
EXTERN S16 wrUmmRrcBldReestabMsg(NhuDatRspSdus *reestabSdu, WrUeCb *ueCb);
EXTERN S16 wrUmmRrcFillTrchCfg (NhuTrChCfg *trChCfg, WrUeCb *ueCb);
EXTERN S16 wrUmmRrcFillMacCfgIe ( NhuMAC_MainConfig  *macCfg, WrUeCb *ueCb);
   /* SPS changes starts */
EXTERN S16 wrUmmRrcFillDedRadioCfg(NhuRadioResourceConfigDedicated *ded,
                                          WrUeCb *ueCB,CmMemListCp *memCp, Bool isUeUlSpsEnabled);
   /* SPS changes ends */
EXTERN S16 wrUmmRrcFillSrcToTgetIe(WrUeCb *ueCb, NhuEncReqSdus *hoPrepMsgEnc);
EXTERN S16 wrUmmUtraRrcFillSrcToTgetIe(WrUeCb *ueCb, NhuEncReqSdus *hoPrepMsgEnc,
                                                  TknStrOSXL *utraUeCapContainer);
EXTERN S16 wrUmmRrcFillUePhyCfgDedInfo(
                        CmMemListCp                    *memCp,
                        NhuRadioResourceConfigDedicated  *rrcCfgDed,
                        RmuUeRecfgRsp                    *rrmUeRecfgResp,
                        WrCellId                          cellId);
EXTERN S16 wrUmmRrcFillUeRadioResDedInfo(
                        /* SPS changes starts */
                        CmMemListCp                    *memCp,
                        WrUeCb                           *ueCb,
                        WrSpsCfg                       *pSpsCfg,
                        /* SPS changes ends */
                        NhuRadioResourceConfigDedicated  *rrcCfgDed,
                        RmuUeRecfgRsp *rrmUeRecfgResp);
EXTERN Void wrUmmRrcFillIntgAlgo(NhuSecAlgorithmConfig *secAlgCfg, WrUeCb *ueCb);
EXTERN S16 wrUmmRrcModDrbCfg(U16  cellId,NhuRbCfgInfo *drbCfg,U8  drbId,
                               U8  lcId,U8  qci, Bool isUlSpsEnabled);
EXTERN S16 wrUmmFillNhuUeCfgInfo(NhuUeCfgInfo  *ueCfg,WrUeCb *ueCb,U16   newCrnti);
EXTERN S16 wrUmmRrcFillConRej(NhuDatRspSdus *nhuDatRspEvntSdu,U32  waitTime);
EXTERN S16 wrUmmRrcFillSrcMeasCfgInfo(NhuMeasConfig *measCfg,WrUeCb  *ueCb,CmMemListCp *memCp);
EXTERN Void wrUmmRrcGetNhuMacMainCfgFrmReCfg( NhuDatReqSdus *rrcReCfgMsg,
                                    NhuMAC_MainConfig   **macCfg);
//EXTERN S16 wrUmmRrcFillRatContnr(CmMemListCp  *memCp,NhuUE_CapRAT_Cont  *rrcIe,
//                     TknStrOSXL *ueRatInfo,U32   ratType);
#ifdef TENB_AS_SECURITY
EXTERN S16 wrUmmFillNhuUeCfgInfo1 (NhuUeCfgInfo *ueCfg, WrUeCb *ueCb, U16 newCrnti);
#endif //TENB_AS_SECURITY

/* SPS changes starts */
PUBLIC S16 wrUmmRrcFillSpsCfgIe(CmMemListCp *memCp, U8 bSpsBitMap, U16 spsRnti, \
      RmuSpsConfigDl *pDlSpsCfg, RmuSpsConfigUl *pUlSpsCfg, NhuSPS_Config *spsCfgIe, U16 duplexMode);
/* SPS changes ends */
PUBLIC S16 wrUmmRrcReconfigFillModDrb(WrUeCb *ueCb, Bool isUeUlSpsEnabled, \
       NhuDRB_ToAddMod *drbIe, U8 erabId, U8 drbId, U8 lchId, U8 qci);
EXTERN S16 wrUmmFillNhuGeranRedirectInfo
(
 WrUmmRedirectInfo          *redirectInfo,
 NhuRRCConRls_r8_IEs         *conRlsR8,
 NhuDatReqSdus                *nhuDatReqSdu,
 U8                           accessStratumRls
);
EXTERN U32 wrGetRptInvlValFromEnum(U32 enumVal);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_UMM_RRC_MSG_H__ */

/********************************************************************30**

           End of file:    $SID$

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
