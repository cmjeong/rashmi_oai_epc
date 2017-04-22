
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_ifm_pdcp.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/


#ifndef __WR_IFM_PDCP_H__
#define __WR_IFM_PDCP_H__

#ifdef __cplusplus
extern "C" {
#endif


EXTERN S16 WrIfmPdcpBndReq (Pst *pst, SuId suId, SpId spId);
EXTERN S16 WrIfmPdcpDatInd (CmLtePdcpId *pdcpId,Buffer *mBuf);
EXTERN S16 WrIfmPdcpDatReq (CmLtePdcpId *pdcpId,PjuSduId sduId,U8 priority, Buffer *mBuf);
EXTERN S16 WrIfmPdcpDatFwdReq (CmLtePdcpId *pdcpId, PjuDatFwdReqInfo *fwdReq);
EXTERN S16 WrIfmPdcpUbndReq (Pst* pst, SpId spId, Reason reason); 
EXTERN S16 WrIfmPdcpDatFwdInd (Pst *pst, SuId suId, CmLtePdcpId *pdcpId, PjuDatFwdIndInfo *datFwdInd);
#ifdef TENB_AS_SECURITY
EXTERN Void wrCpyCpjToCtf(CpjKdfCfmInfo  *kdfCfmInf, CtfKdfCfmInfo  *ctfKdfCfmInf);
EXTERN S16 WrIfmPdcpKdfCfm (
Pst            *pst, 
SuId            suId, 
CpjCfgTransId   transId, 
CpjKdfCfmInfo  *kdfCfmInfo,
U8              status
);
EXTERN S16 wrIfmPdcpKdfReq (CpjKdfReqInfo *info, U32 transid);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_IFM_PDCP_H__ */


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
