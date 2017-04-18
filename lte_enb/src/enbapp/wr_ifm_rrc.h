
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_ifm_rrc.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/



#ifndef __WR_IFM_RRC_H__
#define __WR_IFM_RRC_H__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 WrIfmRrcBndReq(Pst *pst, SuId suId, SpId spId);
EXTERN S16 WrIfmRrcUbndReq(Pst *pst, SpId spId, Reason reason);
EXTERN S16 WrIfmRrcCfgReq(NhuCfgReqSdus *nhuCfgReqSdus);
EXTERN S16 wrIfmRrcRelUe(NhuCellId cellId, NhuCrnti crnti);
EXTERN S16 WrIfmRrcDeleteTransReq(NhuCellId cellId, NhuCrnti ueId, U32 transId);
EXTERN S16 WrIfmRrcCountReq(NhuHdr *countHdr);
EXTERN S16 WrIfmRrcPdcpSduStaReq(NhuHdr  nhuHdr);
EXTERN S16 wrSndNhuCellCfgReq(NhuCellCfgReqSdus **nhuCellCfgReq);
EXTERN S16 wrIfmRrcSndReqToUe(NhuDatReqSdus   *nhuDatReqSdu);
EXTERN S16 wrIfmRrcSndCcchRspToUe(NhuDatRspSdus *nhuDatRspEvntSdu);
EXTERN S16 wrIfmRrcSndDecodeReq(NhuDecodeSduReq *decSdu);
EXTERN S16 wrIfmRrcSndEncodeReq(NhuEncReqSdus *encSdu);
EXTERN S16 wrIfmRrcSndCcchRspToUe(NhuDatRspSdus *nhuDatRspEvntSdu);
EXTERN S16 wrIfmRrcSndCfgReq(NhuCfgReqSdus  *nhuCfgReqSdus);
EXTERN S16 wrUmmPrcPdcpSduStaCfm(NhuPdcpSduStaCfm   *pdcpSduStaCfm);
EXTERN S16 wrIfmRrcSndMsg(NhuDatReqSdus   *nhuDatReqSdu);
EXTERN S16 WrIfmRrcGetPdcpSduSta(NhuHdr   nhuHdr);
EXTERN S16 WrIfmRrcStartPdcpDataFwdReq(NhuHdr nhuHdr);
EXTERN S16 WrIfmRrcPdcpDatResumeReq(NhuHdr nhuHdr);
EXTERN S16 WrIfmRrcSendStartPdcpDataFwdReq(NhuHdr nhuHdr);
EXTERN S16 WrIfmRrcSendPdcpDatResumeReq(NhuHdr nhuHdr);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_IFM_RRC_H__ */



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
