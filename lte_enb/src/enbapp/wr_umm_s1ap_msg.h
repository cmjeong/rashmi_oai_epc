
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_s1ap_msg.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
#ifndef __WR_UMM_S1AP_MSG_H__
#define __WR_UMM_S1AP_MSG_H__

#include "wr.h"
#include "wr_umm.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

/* Number of IEs present in the Location Reprot message */
#define WR_UMM_NO_COMP_LOCATION_REPORT         5
#define WR_UMM_NO_COMP_LOCATION_REPORT_FAIL    3

typedef struct wrUmmRabRlsLst
{
   U8                       erabId;
   WrUmmMsgCause            cause;
   Bool                     rabFailed;
   U8                       qci; /*Added for KPI*/
} WrUmmRabRlsLst;

/*Function Prototypes*/
EXTERN S16 wrUmmS1apBldInitUePdu(WrUeCb *ueCb, TknStrOSXL *nasPdu,
                                 WrPlmnId *plmnId, U16 tac, WrGummei *gummei,
                                 TknU32 *gummeiType, S1apPdu **pdu);
EXTERN S16 wrUmmS1apFillInitCntxtSetRsp(WrS1ConCb *s1apCon,
                                 NhuDatIndSdus *datIndSdu,
                                 S1apPdu   **pdu);
EXTERN S16 wrUmmS1apFillUeCapInfo(WrS1ConCb *s1apCon,TknStrOSXL *octnStr,
                                 S1apPdu **pdu);
EXTERN S16 wrUmmS1apBldERABRelRsp(WrS1ConCb *s1apCon, S1apPdu **pdu, 
                                  U8 numrab,WrUmmRabRlsLst  *rabLst);
EXTERN S16 wrUmmS1apBldERABRelInd(WrS1ConCb *s1apCon, S1apPdu **pdu,
                                 U8 numRabs, WrUmmRabRlsLst *rabLst);
EXTERN S16 wrUmmS1apBldUlNasPdu(WrUeCb *ueCb, TknStrOSXL *nas, S1apPdu **pdu);
EXTERN S16 wrUmmS1apBldERABModRsp(WrS1ConCb *s1apCon, S1apPdu **pdu, 
                                 U8 numRabs, WrUmmRabRlsLst  *rabLst);
EXTERN S16 wrUmmS1apUeCntxtModRsp(WrS1ConCb *s1apCon, S1apPdu **ctxtModPdu);
EXTERN S16 wrUmmS1apUeCntxtModFailure(WrS1ConCb *s1apCon,
                                 S1apPdu **ctxtModPdu, WrUmmMsgCause *cause);
EXTERN S16 wrUmmS1apFillCtxtRelReq(WrUeCb *ueCb, S1apPdu **pdu, 
                                 WrUmmMsgCause *cause);
EXTERN S16 wrUmmS1apFillNasNonDlvInd(WrS1ConCb *s1apCon, S1apPdu **s1ap_pdu, 
                                 TknStrOSXL *nasPdu, WrUmmMsgCause *cause);
EXTERN S16 wrUmmS1apFillInitCntxtSetFail(WrS1ConCb *s1apCon, 
                                 S1apPdu **s1apPdu, WrUmmMsgCause *cause);
EXTERN S16 wrUmmS1apFillCtxtRelCmpl (WrS1ConCb *s1Con, S1apPdu **pdu);

EXTERN S16 wrUmmS1apBldLocReport (WrUeCb *ueCb, S1apPdu **pdu);
EXTERN S16 wrUmmS1apBldLocReportFail (WrUeCb *ueCb, S1apPdu **pdu);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


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
