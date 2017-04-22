
/********************************************************************20**

     Name:     S1AP Layer

     Type:     C source file

     Desc:     C Source code for Upper Interface procedures

     File:     szac_szt.x

     Sid:      szac_szt.x@@/main/4 - Mon Jan 10 22:16:00 2011

     Prg:      rs

*********************************************************************21*/

#ifndef __SZ_SZT_X__
#define __SZ_SZT_X__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 szAcSztDeInit ARGS((
Void
));

EXTERN S16 szAcSztInit ARGS((
Void
));

/**** Start of szt handle fucntion prototypes***********/

#ifndef SZ_ENC_DEC
EXTERN S16 szAcHdlSztBndReq ARGS((
CmXtaTCCb    *tcCb, 
CmXtaSpCb    *spCb  
));

EXTERN S16 szAcHdlSztBndCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 szAcHdlSztUbndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztAuditReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztAuditCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztFlcInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztErrInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztUDatReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztUDatInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztConReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztConInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztConRsp ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztConCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztRelReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztRelInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztRelRsp ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztRelCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztDatReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztDatInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztDatRsp ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztDatCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztEncReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztDecReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

/* sz005.301 Added for S1 Abort request support by UI */
#ifdef SZTV2
EXTERN S16 szAcHdlSztAbortS1Req ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztAbortS1Cfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
#endif /* SZTV2 */


EXTERN S16 szAcHdlSztEncDecCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

#ifdef SZ_MME
EXTERN S16 szAcHdlSztPeerAssocInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 szAcHdlSztPeerAssocRsp ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
#endif

/**** End of szt handle fucntion prototypes***********/


/**** Start of szt utility fucntion prototypes***********/

PUBLIC S16 szAcUtlSztGetNewConnId ARGS((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
UConnId        *suConnId
));

PUBLIC S16 szAcUtlSztRetrvConnId ARGS((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
UConnId        *spConnId
));

PUBLIC S16 szAcUtlSztUpdConnId ARGS((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
UConnId        spConnId
));

PUBLIC S16 szAcUtlSztFillUDatReqPdu ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztUDatEvnt  *uDatEvnt
));

PUBLIC S16 szAcUtlSztFillUDatReqPdu_r11 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztUDatEvnt  *uDatEvnt
));


PUBLIC S16 szAcUtlSztFillConReqPdu ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztConReq    *conEvnt
));

PUBLIC S16 szAcUtlSztFillConReqPdu_r11 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztConReq    *conEvnt
));

PUBLIC S16 szAcUtlSztFillConRspPdu ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztConRsp    *conEvnt
));

PUBLIC S16 szAcUtlSztFillConRspPdu_r11 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztConRsp    *conEvnt
));

PUBLIC S16 szAcUtlSztFillRelReqPdu ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztRelReq    *relEvnt
));

PUBLIC S16 szAcUtlSztFillRelReqPdu_r11 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztRelReq    *relEvnt
));


PUBLIC S16 szAcUtlSztFillRelRspPdu ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztRelRsp    *conEvnt
));

PUBLIC S16 szAcUtlSztFillRelRspPdu_r11 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztRelRsp    *conEvnt
));

PUBLIC S16 szAcUtlSztFillDatReqPdu ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztDatEvntReq   *datEvnt
));

PUBLIC S16 szAcUtlSztFillDatReqPdu_r11 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztDatEvntReq   *datEvnt
));

PUBLIC S16 szAcUtlSztFillEncReqPdu ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
SztEncDecEvnt  *encEvnt
));

/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
PUBLIC S16 szAcUtlSztFillEncReqIe ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
SztEncDecEvnt  *encEvnt
));
#endif   /* SZTV1 */

/**** End of szt utility fucntion prototypes***********/


/**** Start of szt callback fucntion prototypes***********/

PUBLIC S16 szAcSztSendMsg ARGS((
Pst            *pst,
SpId           suId,
Reason         reason,
Void           *ptr
));

PUBLIC CmXtaTCCb*  szAcSztTstCbFind ARGS((
Void
));

PUBLIC S16 szAcUtlSztCb ARGS((
CmXtaMsgQElm   *qElm
));

/**** End of szt callback fucntion prototypes***********/

/* Fill utility function prototypes */
EXTERN S16 szAcUtlSztFillS1SetupReq ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupRsp ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupRsp_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupRsp_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupFail ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitUeMsg ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitUeMsg_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitUeMsg_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupReq ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupReq_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupReq_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupRsp ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupFail ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUplnkNasTpt ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUplnkNasTpt_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUplnkNasTpt_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDwnlnkNasTpt ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDwnlnkNasTpt_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDwnlnkNasTpt_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillNasNonDlvryInd ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillReset ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillResetAck ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtModFail ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsCmd ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsCmpl ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsReq ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsReq_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsReq_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillErrInd ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPaging ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPaging_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPaging_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABMdfyRqst ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABMdfyResp ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABSetupRqst ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu  **pdu));
EXTERN S16 szAcUtlSztFillE_RABSetupRqst_r9 ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu  **pdu));
EXTERN S16 szAcUtlSztFillE_RABSetupRqst_r11 ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu  **pdu));
EXTERN S16 szAcUtlSztFillE_RABSetupResp ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABRlsCmmd ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABRlsResp ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABRlsInd ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUECntxtModRqst ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu  **pdu));
EXTERN S16 szAcUtlSztFillUECntxtModResp ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
/**** End of szt utility fucntion prototypes***********/


/**** Start of szt callback fucntion prototypes***********/

PUBLIC S16 szAcSztSendMsg ARGS((
Pst            *pst,
SpId           suId,
Reason         reason,
Void           *ptr
));

PUBLIC CmXtaTCCb*  szAcSztTstCbFind ARGS((
Void
));

PUBLIC S16 szAcUtlSztCb ARGS((
CmXtaMsgQElm   *qElm
));

/**** End of szt callback fucntion prototypes***********/

/* Fill utility function prototypes */
EXTERN S16 szAcUtlSztFillS1SetupReq ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupRsp ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupRsp_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupRsp_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupFail ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitUeMsg ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitUeMsg_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitUeMsg_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupReq ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupReq_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupReq_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupRsp ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupFail ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUplnkNasTpt ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUplnkNasTpt_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUplnkNasTpt_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDwnlnkNasTpt ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDwnlnkNasTpt_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDwnlnkNasTpt_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillNasNonDlvryInd ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillReset ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillResetAck ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtModFail ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsCmd ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsCmpl ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsReq ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsReq_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsReq_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillErrInd ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPaging ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPaging_r9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPaging_r11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABMdfyRqst ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABMdfyResp ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABSetupRqst ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu  **pdu));
EXTERN S16 szAcUtlSztFillE_RABSetupRqst_r9 ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu  **pdu));
EXTERN S16 szAcUtlSztFillE_RABSetupRqst_r11 ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu  **pdu));
EXTERN S16 szAcUtlSztFillE_RABSetupResp ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABRlsCmmd ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABRlsResp ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABRlsInd ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUECntxtModRqst ARGS ((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu  **pdu));
EXTERN S16 szAcUtlSztFillUECntxtModResp ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillNoDataMsg ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrReqd ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrCmmd ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrPrepFail ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrRqst ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrRqst_r9 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrRqst_r11 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrRqstAckg ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrFail ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrNtfy ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPathSwRqst ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPathSwRqst_r9 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPathSwRqst_r11 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPathSwRqstAckg ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPathSwRqstFail ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrCancel ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrCancelAckg ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBStatusTfr ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillMMEStatusTfr ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillWriteReplaceWarningRqst ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillWriteReplaceWarningResp ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBDirectInformTfr ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillMMEDirectInformTfr ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDeactvTrace ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillTraceStart ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillTraceStart_r9 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillTraceStart_r11 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillTraceFailInd ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillLocReport ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillLocRprtngCntrl ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillLocRprtngFailInd ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBConfigUpd ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBConfigUpdAckg ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBConfigUpdFail ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillMMEConfigUpd ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillMMEConfigUpdAckg ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillMMEConfigUpdFail ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUlnkS1cdma2000tunneling ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDlnkS1cdma2000tunneling ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillOverloadStart ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillOverloadStart_r9 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillOverloadStart_r11 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillOverloadStop ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillOverloadStop_r9 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillOverloadStop_r11 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUECapbltyInfoInd ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBConfigTfr  ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBConfigTfr_r9  ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBConfigTfr_r11  ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillMMEConfigTfr  ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillCellTrafficTrace  ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillCellTrafficTrace_r9  ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillCellTrafficTrace_r11  ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInvalidPdu ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillKillRqst ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillKillResp ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDlnkUeAssocLppaTprt ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUlnkUeAssocLppaTprt ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDlnkNonUeAssocLppaTprt ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUlnkNonUeAssocLppaTprt ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, S1apPdu **pdu));
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
EXTERN S16 szAcUtlSztFillSrcToTget ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, SzIePdu **iePdu));
EXTERN S16 szAcUtlSztFillTgetToSrc ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, SzIePdu **iePdu));
#endif  /* SZTV1 */
/* sz008.301: support for source RNC to target RNC */
#ifdef SZTV3
EXTERN S16 szAcUtlSztFillSrcRncToTgetRnc ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, SzIePdu **iePdu));
EXTERN S16 szAcUtlSztFillTgetRncToSrcRnc ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, SzIePdu **iePdu));
#endif
#else
EXTERN S16 szAcUtlSztFillE_RABSetupRqst ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABSetupRqst_r9 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABSetupRqst_r11 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABSetupResp ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABMdfyRqst ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABMdfyResp ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABRlsCmmd ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABRlsInd ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillE_RABRlsResp ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupReq ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupReq_r9 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupReq_r11 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupRsp ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitCxtSetupFail ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsReq ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsReq_r9 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsReq_r11 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsCmd ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtRlsCmpl ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUECntxtModRqst ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUECntxtModResp ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUeCxtModFail ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitUeMsg ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitUeMsg_r9 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInitUeMsg_r11 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDwnlnkNasTpt ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDwnlnkNasTpt_r9 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDwnlnkNasTpt_r11 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUplnkNasTpt ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUplnkNasTpt_r9 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUplnkNasTpt_r11 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillNasNonDlvryInd ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillErrInd ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillInvalidPdu ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillReset ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillResetAck ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupReq ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupRsp ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupRsp_r9 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupRsp_r11 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillS1SetupFail ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPaging ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPaging_r9 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPaging_r11 ARGS ((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrReqd ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrCmmd ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrPrepFail ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrRqst ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrRqst_r9 ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrRqst_r11 ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrRqstAckg ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrFail ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrNtfy ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPathSwRqst ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPathSwRqst_r9 ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPathSwRqst_r11 ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPathSwRqstAckg ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillPathSwRqstFail ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrCancel ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillHovrCancelAckg ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBStatusTfr ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillMMEStatusTfr ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDeactvTrace ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillTraceStart ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillTraceStart_r9 ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillTraceStart_r11 ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillTraceFailInd ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillLocRprtngCntrl ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillLocRprtngFailInd ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillLocReport ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBConfigUpd ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBConfigUpdAckg ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBConfigUpdFail ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillMMEConfigUpd ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillMMEConfigUpdAckg ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillMMEConfigUpdFail ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUlnkS1cdma2000tunneling ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDlnkS1cdma2000tunneling ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUECapbltyInfoInd ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillOverloadStart ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillOverloadStart_r9 ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillOverloadStart_r11 ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillOverloadStop ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillOverloadStop_r9 ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillOverloadStop_r11 ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillWriteReplaceWarningRqst ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillWriteReplaceWarningResp ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBDirectInformTfr ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillMMEDirectInformTfr ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillENBConfigTfr ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillMMEConfigTfr ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillCellTrafficTrace ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillNoDataMsg ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillKillRqst ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillKillResp ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDlnkUeAssocLppaTprt ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUlnkUeAssocLppaTprt ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillDlnkNonUeAssocLppaTprt ARGS((S1apPdu **pdu));
EXTERN S16 szAcUtlSztFillUlnkNonUeAssocLppaTprt ARGS((S1apPdu **pdu));
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
EXTERN S16 szAcUtlSztFillSrcToTget ARGS((U8 type, SzIePdu **iePdu));
EXTERN S16 szAcUtlSztFillTgetToSrc ARGS((SzIePdu **iePdu));
#endif /* SZTV1 */
/* sz008.301: support for source RNC to target RNC */
#ifdef SZTV3
EXTERN S16 szAcUtlSztFillSrcRncToTgetRnc ARGS((SzIePdu **iePdu));
EXTERN S16 szAcUtlSztFillTgetRncToSrcRnc ARGS((SzIePdu **iePdu));
#endif
#endif /* SZ_ENC_DEC */

EXTERN S16 szFillTknStr4 ARGS ((TknStr4 *ptr, U8 len, U8 val));
EXTERN S16 szFillTknStrOSXL ARGS ((TknStrOSXL *ptr, U16 len, Data *val, S1apPdu  **pdu));
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
EXTERN S16 szFillTknStrOSXLIe ARGS ((TknStrOSXL *ptr, U16 len, Data *val, CmMemListCp *memCp));
#endif  /* SZTV1 */
EXTERN S16 szFillTknU32 ARGS((TknU32 *encParam,U32 val));
EXTERN S16 szFillTknU8 ARGS((TknU8 *encParam,U8 val));
EXTERN S16 szFillTknU16 ARGS((TknU16 *encParam,U16 val));


#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __SZ_SZT_X_ */

/**********************************************************************

         End of file:     szac_szt.x@@/main/4 - Mon Jan 10 22:16:00 2011

**********************************************************************/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/4      ---      pkaX  1. Updated for S1AP release 3.1
/main/4   sz004.301   va    1. Updated for Transparent Container Enc/Dec 
/main/4   sz005.301   va    1. Updated for S1 Abort request support by UI
/main/4   sz008.301  akaranth 1. support for source RNC to target RNC.
*********************************************************************91*/
