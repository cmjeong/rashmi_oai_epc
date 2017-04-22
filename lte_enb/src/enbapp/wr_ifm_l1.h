
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_ifm_l1.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/


#ifndef __WR_IFM_L1_H__
#define __WR_IFM_L1_H__

#ifdef __cplusplus
extern "C" {
#endif
#define WR_MS_PHY_SHUTDOWN_CFM    0x01
#define WR_MS_TX_PWR_DOWN_CFM     0x02
#define WR_MS_TX_PWR_UP_CFM       0x04

#define WR_MS_PHY_PWR_DOWN_CFM    6
#define WR_MS_PHY_PWR_UP_CFM      7
#define IS_DUMMY_SHUTDOWN(a) (a%2)==0 ? TRUE : FALSE
#define WR_MS_CELL_STOP_CFM       8

/* UMM CTF Prototypes */
EXTERN S16 TfLiCtfBndCfm (Pst *pst, SuId suId, U8 status);
EXTERN S16 WrIfmL1BndCfm (Pst *pst, SuId suId, U8 status);
EXTERN S16 TfLiCtfCfgCfm (Pst *pst, SuId suId, CtfCfgTransId transId, 
                          U8 status);
EXTERN S16 WrIfmL1CfgCfm (Pst *pst, SuId suId, CtfCfgTransId transId, 
                          U8 status);
EXTERN S16 WrIfmL1EnbStopInd (Pst *pst, SuId suId, CtfCfgTransId transId);
EXTERN S16 TfLiCtfUeIdChgCfm (Pst *pst, SuId suId, CtfCfgTransId transId,
                              CtfUeInfo *ueInfo, U8 status);
/* CNM_DEV start */
EXTERN S16 TfLiCtfCnmInitialSyncRsp (Pst *pst, SuId suId, CtfCfgTransId *transId,
                              CtfCnmInitSyncRsp *cnmInitSyncRsp);
EXTERN S16 TfLiCtfCnmSyncInd (Pst *pst, SuId suId, CtfCfgTransId *transId,
                              CtfCnmCellSyncInd *cnmSyncInd);
EXTERN S16 TfLiCtfCnmSyncRsp (Pst *pst, SuId suId, CtfCfgTransId *transId,
                              CtfCnmCellSyncRsp *cnmSyncRsp);
/* CNM_DEV end */

EXTERN S16 WrIfmL1BndReq (Pst* pst, SuId suId, SpId spId);
EXTERN S16 WrIfmL1UbndReq (Pst* pst, SpId spId, Reason reason);
EXTERN S16 wrIfmPhyCellCfg (CtfCfgReqInfo *cellCfgReq, U32 transId);
EXTERN S16 wrIfmPhyUeCfg (CtfCfgReqInfo *ueCfg, U32 transId);
#ifdef TENB_AS_SECURITY
EXTERN S16 WrIfmL1KdfCfm (Pst *pst, SuId suId, CtfCfgTransId transId,CtfKdfCfmInfo *kdfCfmInfo,
                          U8 status);
EXTERN S16 wrIfmPhyKdfReq (CtfKdfReqInfo *info, U32 transid);
#endif

/* CNM_DEV start */
EXTERN S16 wrIfmPhyCnmInitialSyncReq (CtfCnmInitSyncReq *cnmInitSyncReq,
      U32 transId);
EXTERN S16 wrIfmPhyCnmCellSyncReq (CtfCnmCellSyncReq *cnmCellSyncReq,
      U32 transId);

EXTERN S16 WrIfmL1CnmInitialSyncRsp (Pst *pst, SuId suId, CtfCfgTransId *transId,
      CtfCnmInitSyncRsp *cnmInitSyncRsp);
EXTERN S16 WrIfmL1CnmSyncInd (Pst *pst, SuId suId, CtfCfgTransId *transId,
      CtfCnmCellSyncInd *cnmSyncInd);
EXTERN S16 WrIfmL1CnmSyncRsp (Pst *pst, SuId suId, CtfCfgTransId *transId,
      CtfCnmCellSyncRsp *cnmSyncRsp);
/* CNM_DEV end */

/* Periodic REM scan for TPM */
EXTERN S16 TfLiCtfPerCellSrchRsp (Pst *pst,SuId suId,CtfCfgTransId *transId,
CtfPeriodicRemCellSearchRsp  *perCellSrchRsp); 
/* Periodic REM scan for TPM End */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_IFM_L1_H__ */


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
