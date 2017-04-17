
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_ifm_rrm.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/


#ifndef __WR_IFM_RRM_H__
#define __WR_IFM_RRM_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RM_INTF
EXTERN S16 wrIfmRrmStatusInd (RmuFsmStatusInd *statusInd);
#else
EXTERN S16 wrIfmRrmEnodebCfgReq(RrmWrEnbCfgReqInfo *rrmWrEnbCfgReq);
EXTERN S16 wrIfmRrmCellCfgReq(RrmWrCellCfgReqInfo *rrmWrCellCfgReq);
EXTERN S16 wrIfmRrmEnodebStaInd(RrmWrEnbStaIndInfo *rrmWrEnbStaInd);
EXTERN S16 wrIfmRrmCellStaInd(RrmWrCellStaIndInfo *rrmWrCellStaInd);
EXTERN S16 wrIfmRrmUeStaInd(RrmWrUeStaIndInfo *rrmWrUeStaInd);
#endif /*RM_INTF*/
EXTERN S16 wrIfmRrmSndUeRecfgReq(RmuUeRecfgReq *ueRecfgInfo);
EXTERN S16 WrIfmRrmSendUeRelReq(CmLteCellId cellId,U16 crnti, U32 transId);
EXTERN S16 wrIfmRrmUeAdmitReq(WrCellId cellId,U16 crnti,U32 transId,U32 establishCause);
EXTERN S16 wrUmmProcRrmUeCfgRsp(RmuUeRecfgRsp *ueRecfgRespPtr);
EXTERN S16 wrIfmRrmMmeOvldStartInd(RmuMmeOvldStartInd* rrmWrMmeStartInfo);
EXTERN S16 wrIfmRrmMmeOvldStopInd(RmuMmeOvldStopInd* rrmWrMmeStopInfo);
EXTERN S16 wrIfmRrmHoAdmitReq(RmuUeHoReq *rrmWrUeHoAdmitReq);

/* SPS changes starts */
EXTERN S16 wrUmmRrmUeSpsDisInd(U8 cellId, U16 crnti);
EXTERN Void wrUmmRrmFillUeCapInfo(WrCellId cellId, RmuUeCapInfoIe *rmuCapInfo, WrUeCapInfo *ueCap);
/* SPS changes ends */
/*RRM_SP3*/
EXTERN S16 wrIfmRmuInactInd( Pst *pst, SuId suId, RmuUeInactInd   *rrmUeInactInd);
EXTERN Void wrIfmDamRmuUeInactInd(U16 crnti, U16 cellId, U32 inactEvt);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __WR_IFM_RRM_H__ */


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
