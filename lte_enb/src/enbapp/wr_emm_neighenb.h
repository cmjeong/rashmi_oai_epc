
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_emm_neighenb.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_EMM_NEIGHENB_H__
#define __WR_EMM_NEIGHENB_H__

#include "wr.h"
#include "wr_cmn.h"
#include "wr_emm.h"
#include "wr_ifm_s1ap.h"

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

/*Default value has been set to 6 sec */
#define WR_EMM_X2_SETUP_DFLT_TMR_VAL 20000
#define WR_EMM_X2_SETUP_FAIL_TMR_VAL 20000
#define WR_EMM_X2_SETUP_TIME_TO_WAIT 5
/* ccpu00125633 : wait Timer is changed from 1000 to 2000 since this value should be greater than
 *  sctp freeze timer for X2AP-Interface monitoring */
#define WR_ENB_CON_WAIT_TIMER        2000
#define WR_EMM_X2_RST_RETX_DFLT_TMR_VAL  1000
#define WR_EMM_X2_SETUP_MAX_RTX_VAL 0xFF 
#define WR_EMM_X2_RST_MAX_RTX_VAL 0xFF 
#define WR_EMM_X2_CFG_UPD_MAX_RTX_VAL 0xFF
#define WR_EMM_ENB_CFG_TRANSFER_RTX_CNT 0xFF

#define WR_EMM_X2_CFG_UPD_TMR_VAL      20000
#define WR_EMM_X2_CFG_UPD_FAIL_TMR_VAL 20000

#define WR_CZ_CAUSE_RADIONW      0
#define WR_CZ_CAUSE_TRANSPORT    1
#define WR_CZ_CAUSE_PROTOCOL     2
#define WR_CZ_CAUSE_MISC         3

#define WR_EMM_X2_CONFIG_EXTEN_IE_COUNT 2
#define WR_EMM_X2_CONFIG_FAIL_IE_COUNT 2
#define WR_EMM_X2_CONFIG_TIME_TO_WAIT 5
#define WR_EMM_X2_MACRO_ENBID_LEN 20
#define WR_EMM_X2_HOME_ENBID_LEN 28
#define WR_EMM_X2_NEIGH_EXTEN_IE_COUNT 1 /*!< Number members in neighbor list extension */

typedef struct ueX2apId
{
  Bool oldeNBUeX2apIdPres;
  U32  oldeNBUeX2apId;
  Bool neweNBUeX2apIdPres;
  U32  neweNBUeX2apId;
} UeX2apId;

#if 0
#define WR_GET_ENBID_FROM_PEERID(_eNbId,_peerId) {\
       _eNbId = wrEmmCb.x2ApEnbIdLst[_peerId];\
}

#define WR_GET_X2AP_PEER_ID(_peerId, eNBId, enbIdx) {\
        _peerId = enbIdx + 1; \
       wrEmmCb.x2ApEnbIdLst[_peerId] = eNBId;\
}
#endif

/*
 * Maximum no. of pools an eNB can belong to
*/

EXTERN S16 wrEmmNghEnbBldEBCfgUptReq(CztEvnt **pdu,WrEmmEnbCfgUpd *cellInfo);
EXTERN S16 wrEmmNghEnbSndEnCfgUpReq(WrNeighEnbCb *nghEnbCb,WrEmmEnbCfgUpd *cellInfo);
EXTERN S16 wrEmmNghEnbBldEBCfgUptReqFail(CztEvnt **pdu);
EXTERN S16 wrEmmNghEnbBldEBCfgUptReqAck(CztEvnt **pdu);
EXTERN S16 wrEmmNghEnbSndEnCfgUpReqAck(U32 peerId);
EXTERN S16 wrEmmNghEnbSndEnCfgUpReqFail(U32 peerId);
EXTERN S16 wrEmmNghEnbBldX2SetupReq(CztEvnt  **pdu);
EXTERN S16 wrEmmNghEnbSndX2SetupReq(WrNeighEnbCb *nghEnbCb);
EXTERN S16 wrEmmNghEnbSndX2Setup(WrNeighEnbCb  *nghEnbCb);
EXTERN S16 wrEmmNghEnbPrcStaInd(CztStaInd *cztSta);
EXTERN S16 wrEmmNghEnbSetupTmrExpiry(PTR);
EXTERN S16 wrEmmNghEnbSetupWaitTmrExpiry(PTR);
EXTERN S16 wrEmmNghEnbMsgTmrExpiry(PTR);
EXTERN S16 wrEmmNghEnodebIdCmp(WrNeighEnbCb *enbnghCb);
EXTERN S16 wrEmmNghEcgiCmp(WrEutranNeighCellCb *nghSrvdCellCb,WrNeighEnbCb *enbnghCb);
EXTERN S16 wrEmmBldEBCfgUptReq(CztEvnt  **pdu,WrEmmEnbCfgUpd *cellInfo);
EXTERN S16 wrEmmBldEBCfgUptReqFail(CztEvnt **pdu,Bool incTimeToWait);
EXTERN S16 wrEmmSndEnCfgUpReqFail(U32 peerId,Bool incTimeToWait);
EXTERN S16 wrEmmBldEBCfgUptReqAck(CztEvnt  **pdu);
EXTERN S16 wrEmmSndEnCfgUpReqAck(U32 peerId);
EXTERN S16 wrEmmNghEnbPrcRcvdPdu(U32 peerId,CztEvnt *pdu);
EXTERN S16 wrEmmNghTrigCfgUpd(WrCellCb *cellCb);
EXTERN S16 wrEmmNghTrigReset(Void );
EXTERN S16 wrEmmNghBrngAllX2Down(Void );

EXTERN U8 wrFillBwCfg(U8 dlBwIn);
EXTERN WrNrEutranFreqCb* wrEmmAnrGetEutranFreqNode(U16 earfcnDl,WrNrEutranCb *eutranCb);
EXTERN S16 wrEmmNghEnbParsePlmnIe(CztPLMN_Identity  *plmnIe, WrPlmnId  *plmnId); 
EXTERN S16 wrEmmNghEnbParseTknStr4Ie(TknStr4 *ie, U32 *lvalue);
EXTERN S16 wrEmmSendSetupReqNghEnbInfoToSon(WrCellCb  *cellCb, WrNeighEnbCb *enbNghCb,
           CztX2SetupRqst  *setupReq);
EXTERN S16 wrEmmSendSetupRspNghEnbInfoToSon(WrCellCb  *cellCb, WrNeighEnbCb  *enbNghCb,  
           CztX2SetupResp  *setupRsp);
EXTERN S16 wrEmmSendCfgUpdateNghEnbInfoToSon(WrCellCb *cellCb, WrNeighEnbCb  *enbNghCb,
           CztENBConfigUpd  *cfgUpdate);
EXTERN S16 wrEmmSendNghEnbDelToSon(WrCellCb *cellCb, WrNeighEnbCb *enbNghCb);
PUBLIC S16 wrEmmNghTrigCfgUpdNghCellMod
(
 WrCellCb  *cellCb,
 U32       enbId
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_EMM_NEIGHENB_H__ */

/*********************************************************************31*
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
