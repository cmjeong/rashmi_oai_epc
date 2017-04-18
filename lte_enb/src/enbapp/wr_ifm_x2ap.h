
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_ifm_x2ap.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/


#ifndef __WR_IFM_X2AP_H__
#define __WR_IFM_X2AP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* UMM CZT Function Prototypes */
EXTERN S16 WrIfmX2apGpReq (CztEvnt *cztEvnt);
EXTERN S16 WrIfmX2apBndCfm  (Pst *pst, SuId suId, U8 status);
EXTERN S16 WrIfmX2apGpInd  (Pst *pst, SuId suId, CztEvnt *cztInd);
EXTERN S16 WrIfmX2apGpCfm (Pst *pst, SuId suId, CztEvnt *cztCfm);
EXTERN S16 WrIfmX2apBmpInd (Pst *pst, SuId suId, CztEvnt *cztInd);
EXTERN S16 WrIfmX2apBmpCfm (Pst *pst, SuId suId, CztEvnt *cztCfm);
EXTERN S16 WrIfmX2apGpErrInd (Pst *pst, SuId suId, CztEvnt *cztEvnt);
EXTERN S16 WrIfmX2apLclErrorInd (Pst *post, SuId suId, CztLclErrInd *cztLclErrInd);
EXTERN S16 WrIfmX2apRelCfm (Pst *pst, SuId suId, CztRlsCfm *rlsCfm);
EXTERN S16 WrIfmX2apStaInd  (Pst *post, SuId suId, CztStaInd *cztSta);
EXTERN S16 WrIfmX2apDynamPeerAssocInd (Pst *pst, SuId suId, CztPeerAssocInd *peerAssocInd);
EXTERN S16 WrIfmX2apAudCfm  (Pst *pst, SuId suId, CztAudEvnt *audEvnt);
EXTERN S16 WrIfmX2apBndReq  (Pst *pst, SuId suId, SpId spId);
EXTERN S16 WrIfmX2apUbndReq  (Pst *pst, SpId spId, Reason reason);
EXTERN S16 WrIfmX2apGpRetxReq (CztReTxInfo *cztReTxInfo);
EXTERN S16 WrIfmX2apGpRsp (CztEvnt *cztEvnt);
EXTERN S16 WrIfmX2apGpErrReq (CztEvnt *cztEvnt);
EXTERN S16 WrIfmX2apRelReq (CztRlsReq *relReq);
EXTERN S16 WrIfmX2apBmpReq (CztEvnt *cztEvnt);
EXTERN S16 WrIfmX2apBmpRsp (CztEvnt *cztEvnt);
EXTERN S16 WrIfmX2apDynamPeerAssocRsp (Pst *pst, SpId spId, CztPeerAssocRsp *peerAssocRsp);
EXTERN S16 WrIfmX2apAudReq  (Pst *pst, SpId spId, CztAudEvnt *audEvnt);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_IFM_X2AP_H__ */



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
