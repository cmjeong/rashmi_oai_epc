
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
			   -> Wrapper functions to functions defined in wr_dam.c
			   -> Wrapper functions to call pack functions defined in wr_ifm_dam_utis.c
                  for functions defined in APP 

     File:     wr_dami_ifm_app.h

     Sid:      $SID$ 

     Prg:      Suhas 

*********************************************************************21*/
#ifndef __WR_DAM_IFM_APP_H__
#define __WR_DAM_IFM_APP_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */
/* Functions called from utils file - start*/
EXTERN Void wrIfmDamWrCntrlReq(LwrMngmt    *cfg);
EXTERN Void wrIfmDamWrCfgReq(LwrMngmt *cfg);
EXTERN S16 wrIfmDamWrTnlCreatReq(U32 transId, WrDamTnlInfo *tnlInfo);
EXTERN Void wrIfmDamWrTnlModReq(U32 transId, WrDamTnlModInfo *tnlModInfo);
EXTERN Void wrIfmDamWrTnlDelReq(U32 transId, WrDamTnlId *tnlId);
EXTERN Void wrIfmDamWrUeDelReq(U32 transId, U16 cellId, U16 crnti);
EXTERN S16 wrIfmDamWrReCfgReq(U32 transId,U16 cellId,U16 crnti);
EXTERN Void wrIfmDamWrReestabReq(U32 transId, U16 cellId, U16 ocrnti, U16 ncrnti);
EXTERN Void wrIfmDamWrCellAddReq(WrDamCellInfo *cellInfo);
EXTERN Void wrIfmDamWrChngTnlState(WrDamTnlStInfo *tnlStInfo);
EXTERN Void wrIfmDamWrSetDataRcvdFlag(U16 cellId,U16 ueId);/*ccpu00138576*/
/* Functions called from utils file - end*/

/* Functions called from dam file - start*/
EXTERN S16 wrIfmDamWrCntrlCfm(CmStatus   *status,LwrMngmt    *cntrl);
EXTERN S16 wrIfmDamWrCfgCfm(LwrMngmt    *cfg,CmStatus   *cfgCfm);
EXTERN S16 wrIfmDamWrReestabCfm(U32 transId, U8 status);
EXTERN S16 wrIfmDamWrPdcpDatCfm(CmLtePdcpId pdcpId);
EXTERN S16 wrIfmDamWrTnlCreatCfm(U32 transId, U8 status, U32 lclTeid);
EXTERN S16 wrIfmDamWrTnlModCfm(U32 transId, U8 status, U32 lclTeId);
EXTERN S16 wrIfmDamWrUeDelCfm(U32 transId, U16 cellId, U16 crnti);
EXTERN Void wrIfmDamWrSendLmAlarm(U16  category, U16 event, U16 cause);
EXTERN Void wrIfmDamWrCtxtRel(U16  crnti, U16  cellId,U8 event );
/* Functions called from dam file - end*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_DAM_IFM_APP_H__ */

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
$SID$        ---      Suhas         1. TotaleNodeB GA4.0
*********************************************************************91*/
