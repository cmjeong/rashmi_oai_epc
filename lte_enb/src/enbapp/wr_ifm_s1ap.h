
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_ifm_s1ap.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/



#ifndef __WR_IFM_S1AP_H__
#define __WR_IFM_S1AP_H__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 WrIfmS1apBndReq(Pst *pst, SuId suId, SpId spId);
EXTERN S16 WrIfmS1apSndMgmtMsg(SztUDatEvnt *uDatEvnt);
EXTERN S16 WrIfmS1apUbndReq(Pst *pst, SpId spId, Reason reason);
EXTERN S16 WrIfmS1apConReq(SztConReq *conReq);
EXTERN S16 WrIfmS1apConReq(SztConReq *conReq);
EXTERN S16 WrIfmS1apRelReq(SztRelReq *relReq);
EXTERN S16 WrIfmS1apRelRsp(SztRelRsp *relRsp);
EXTERN S16 WrIfmS1apDatReq(SztDatEvntReq *datEvnt);
EXTERN S16 WrIfmS1apEncDecReq(SztEncDecEvnt *sztEncDecEvnt);
EXTERN S16 WrIfmS1apAudReq(SztAudEvnt *audEvnt);
EXTERN S16 wrIfmS1apSndUeMsg(U32 spConnId, S1apPdu *s1pdu);
EXTERN S16 WrIfmS1apDatReq(SztDatEvntReq *datEvnt);
EXTERN S16 WrIfmS1apSndAbortMsg(SztAbortS1 *abortS1);
EXTERN S16 WrIfmS1apConRsp(SztConRsp  *conRsp);
EXTERN S16 wrUmmPrcS1ConInd(SztConReq  *conReq, U32 *cause);
EXTERN S16 WrIfmSztEncDecCfm(Pst  *pst,SuId  suId,
            SztEncDecEvnt  *sztEncDecEvnt,SztReqStatus  *status);
EXTERN S16 wrUmmPrcSztEncDecCfm(SztEncDecEvnt   *sztEncDecCfmSdus,SztReqStatus   *status);





#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_IFM_S1AP_H__ */




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
