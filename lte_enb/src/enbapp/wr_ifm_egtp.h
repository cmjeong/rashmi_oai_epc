
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_ifm_egtp.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/


#ifndef __WR_IFM_EGTP_H__
#define __WR_IFM_EGTP_H__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 WrIfmEgtpBndReq(Pst *pst, SuId suId, SpId spId);
EXTERN S16 WrIfmEgtpUbndReq(Pst *pst, SpId spId, Reason reason);
EXTERN S16 WrIfmEgtpEguLclTnlMgmtReq (EgtUEvnt  *egtUEvnt); 
EXTERN S16 WrIfmEgtpEguStaReq(EgtUEvnt *egtUEvnt);
EXTERN S16 WrIfmEgtpEguDatReq(EgtUEvnt *egtUEvnt);
#if 0
EXTERN S16 WrHdlCreatEgtpTunelCfm (Pst *pst, SuId suId, CmLtePdcpId *pdcpId);
EXTERN S16 WrIfmEgtpEguLclTnlMgmtCfm (Pst *pst, SuId suId, EgtUEvnt *eguMsg);

EXTERN S16 WrIfmEgtpEguDatInd (Pst *pst, SuId suId, EgtUEvnt *eguMsg); 
EXTERN S16 WrIfmEgtpEguStaCfm (Pst *pst, SuId suId, EgtUEvnt *eguMsg); 
EXTERN S16 WrIfmEgtpEguUStaInd (Pst *pst, SuId suId, EgtUEvnt *eguMsg);

EXTERN S16 WrIfmEgtpEguErrInd (Pst *pst, SuId suId, EgtUEvnt *eguMsg);


EXTERN S16 WrIfmEgtpDatInd (Pst *pst, SuId suId, EgtUEvnt *eguMsg);
EXTERN S16 EuLiEgtDatInd (Pst *pst, SuId suId, EgtUEvnt *eguMsg);
#ifdef EGTP_U
EXTERN S16 PtLiEgtEguLclTnlMgmtReq (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
EXTERN S16 PtLiEgtEguStaReq (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
EXTERN S16 PtLiEgtEguDatReq (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
EXTERN S16 EuLiEgtEguLclTnlMgmtReq (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
EXTERN S16 EuLiEgtEguStaReq (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
EXTERN S16 EuLiEgtEguDatReq (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
EXTERN S16 EuLiEgtEguLclTnlMgmtCfm (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
EXTERN S16 EuLiEgtEguStaCfm (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
EXTERN S16 EuLiEgtEguUStaInd (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
EXTERN S16 EuLiEgtEguErrInd (Pst *pst, SuId suId, EgtUEvnt *egtUEvnt);
EXTERN S16 WrIfmEgtpBndCfm (Pst *pst, SuId suId, U8 status);
EXTERN S16 EuLiEgtBndCfm (Pst *pst, SuId suId, U8 status);
#endif
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_IFM_EGTP_H__ */



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
