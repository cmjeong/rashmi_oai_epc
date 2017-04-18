
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_sch_msg.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_UMM_SCH_MSG_H__
#define __WR_UMM_SCH_MSG_H__

#include "wr.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

EXTERN S16 wrUmmSchFillRgrUeTxModeCfg(RgrUeTxModeCfg *ueCfg, WrUeCb *ueCb);
EXTERN S16 wrUmmSchFillRgrUeDlCqiCfg(RgrUeDlCqiCfg *ueCfg, 
                     WrCqiRptCfg *cqiRptCfg,S8 cqiOffst,U8 bresCfgBitMap);
EXTERN S16 wrUmmSchFillRgrUeUlHqCfg(RgrUeUlHqCfg *ueCfg, WrUeCb *ueCb);
EXTERN S16 wrUmmSchFillRgrUeUlPwrCfg(RgrUeUlPwrCfg *ueCfg, WrUeCb *ueCb);
EXTERN S16 wrUmmSchFillRgrUeQosCfg(RgrUeQosCfg *ueCfg, WrUeCb *ueCb);
EXTERN S16 wrUmmSchFillRgrUeTaTmrCfg(RgrUeTaTmrCfg *ueCfg, WrUeCb *ueCb);
EXTERN S16 wrUmmSchFillRgrUeAckNackRepCfg(RgrUeAckNackRepCfg *cfg, WrUeCb *ue);
EXTERN S16 wrUmmSchFillRgrUeMeasGapCfg(RgrUeMeasGapCfg *ueCfg, WrUeCb *ueCb);
EXTERN S16 wrUmmSchFillRgrUeCapCfg(RgrUeCapCfg *ueCfg, WrUeCb *ueCb);
EXTERN S16 wrUmmSchFillRgrCodeBookRstCfg(RgrCodeBookRstCfg *ueCfg, WrUeCb *ue);
EXTERN S16 wrUmmSchdUeRel(U32 transId, U16 crnti, U16 cellId);
EXTERN S16 wrUmmSchFillUeCfg(U32 transId, WrUeCb *ueCb, RgrCfgReqInfo *cfg);
EXTERN S16 wrUmmSchdUeIdChg(U32 transId, U16 cellId, U16 oldRnti, 
               U16 newRnti,WrUeCb *ueCb);

EXTERN Void wrUmmSchdFillUeRadioResCfgInfo(RgrUeRecfg *ueRecfg, 
                  RmuUeRecfgRsp       *ueRecfgRespPtr,
                  WrUeCb                    *ueCb,
                  Bool                 isTxModeChngTrig);

EXTERN Void wrUmmSchdFillUeCategory(CmLteUeCategory *ueCatEnum, WrUeCb *ueCb);
                                    /*passing ueCb - CA dev changes*/
EXTERN S16 wrSchFillRgrUeTxModeCfg(RgrUeTxModeCfg  *ueCfg,WrUeCb  *ueCb);

#ifdef TFU_UPGRADE
EXTERN S16 wrUmmSchFillRgrUeSrCfg(RgrUeSrCfg *ueCfg, WrUeCb *ueCb);
EXTERN S16 wrUmmSchFillRgrUeSrsUlDedCfg(RgrUeUlSrsCfg *ueCfg, WrUeCb  *ueCb);
#endif //TFU_UPGRADE

#ifdef RGR_V1
EXTERN Void wrUmmSchdFillPeriodicBsrTmr(RgrUeBsrTmrCfg *ueBsrTmrCfg, 
               WrUeCb *ueCb);
#endif

/* ccpu00128203 */
EXTERN S16 wrUmmSchdUeLcgCfg (WrUeCb *ueCb, U32 transId, U8   grpId, U32 ulGbr, U32 ulMbr);
EXTERN S16 wrUmmSchdUeLcgReCfg (WrUeCb *ueCb, U32 transId, U8	grpId, U32 ulGbr, U32 ulMbr);
EXTERN S16 wrUmmSchdUeLcgDel (WrUeCb *ueCb, U32 transId, U8	grpId);
/* SPS changes starts */
EXTERN Void wrUmmFillSpsSchdCfgUe(U8 transType, WrUeCb *ueCb, RmuUeRecfgRsp *rrmUeRecfgResp, \
      RgrUeCfg *ueCfg, U32 numErabs, Void *pErabList, U32 accessStratumRls, WrSpsCfg *pSpsCfg, \
      Bool *pIsUeDlSpsEnabled, Bool *pIsUeUlSpsEnabled);
EXTERN Void wrUmmFillSpsSchdReCfgUe(U8 transType, WrUeCb *ueCb, RmuUeRecfgRsp *rrmUeRecfgResp, \
      RgrUeRecfg *ueRecfg, U32 numErabs, Void *pErabList, WrSpsCfg *pSpsCfg, \
      Bool *pIsUeDlSpsEnabled, Bool *pIsUeUlSpsEnabled);
/* SPS changes ends */

EXTERN Void wrUmmSchdFillUeAccessStratumRls(
   RgrAccessStratumRls        *accessStratumRls,
   WrUeCb                     *ueCb);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_UMM_SCH_MSG_H__ */

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
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
