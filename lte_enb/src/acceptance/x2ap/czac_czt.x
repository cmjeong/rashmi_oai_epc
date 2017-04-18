
/********************************************************************20**

     Name:     X2AP Layer

     Type:     C source file

     Desc:     C Source code for Upper Interface procedures

     File:     czac_czt.x

     Sid:      czac_czt.x@@/main/2 - Tue Aug 30 18:35:46 2011

     Prg:      aj

*********************************************************************21*/

#ifndef __CZ_CZT_X__
#define __CZ_CZT_X__

#ifdef __cplusplus
extern "C" {
#endif

/* cz001.101 : CR Fixes. */
#include "czac_asn.x"

EXTERN S16 czAcCztDeInit ARGS((
Void
));

EXTERN S16 czAcCztInit ARGS((
Void
));

/**** Start of czt handle fucntion prototypes***********/

EXTERN S16 czAcHdlCztBndReq ARGS((
CmXtaTCCb    *tcCb, 
CmXtaSpCb    *spCb  
));

EXTERN S16 czAcHdlCztBndCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 czAcHdlCztUbndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));


EXTERN S16 czAcHdlCztStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 czAcHdlCztLclErrInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));


EXTERN S16 czAcHdlCztEvnt ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 czAcHdlCztBmpInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 czAcHdlCztBmpCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 czAcHdlCztGpRetxReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 czAcHdlCztGpReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 czAcHdlCztGpErrReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

PUBLIC S16 czAcHdlCztBmpReq
ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

PUBLIC S16 czAcHdlCztBmpRsp
ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 czAcHdlCztGpInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 czAcHdlCztGpRsp ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 czAcHdlCztGpCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 czAcHdlCztLclRelReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 czAcHdlCztLclRelCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));


EXTERN S16 czAcHdlCztPeerAssocInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 czAcHdlCztPeerAssocRsp ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 czAcHdlCztAudReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 czAcHdlCztAudCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));


EXTERN S16 czAcHdlDirective ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
/**** End of czt handle fucntion prototypes***********/


/**** Start of czt utility fucntion prototypes***********/

PUBLIC S16 czAcUtlCztFillGpReqPdu_R9 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt    **cztEvnt
));
PUBLIC S16 czAcUtlCztFillGpReqPdu_R11 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt    **cztEvnt
));
PUBLIC S16 czAcHdlCztGpErrInd
ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
PUBLIC S16 czAcUtlCztFillGpRspPdu_R9 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt    **cztEvnt
));
PUBLIC S16 czAcUtlCztFillGpRspPdu_R11 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt    **cztEvnt
));

PUBLIC S16 czAcUtlCztFillBmpReqPdu_R9 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt    **relEvnt
));
PUBLIC S16 czAcUtlCztFillBmpReqPdu_R11 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt    **relEvnt
));

PUBLIC S16 czAcUtlCztFillBmpRspPdu_R9 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt    **cztEvnt
));
PUBLIC S16 czAcUtlCztFillBmpRspPdu_R11 ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt    **cztEvnt
));

/**** End of czt utility fucntion prototypes***********/


/**** Start of czt callback fucntion prototypes***********/

PUBLIC S16 czAcCztSendMsg ARGS((
Pst            *pst,
SpId           suId,
Reason         reason,
Void           *ptr
));

PUBLIC CmXtaTCCb*  czAcCztTstCbFind ARGS((
Void
));

PUBLIC S16 czAcUtlCztCb ARGS((
CmXtaMsgQElm   *qElm
));

/**** End of czt callback fucntion prototypes***********/

/* Fill utility function prototypes */


EXTERN S16 czAcUtlCztFillLoadInd_R9  ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillLoadInd_R11  ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillX2SetupReq_R9 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillX2SetupReq_R11 ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillX2SetupRsp ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillX2SetupFail ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillReset ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillPrivateMsg ARGS ((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillResetAck ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillENBConfigUpd ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillENBConfigUpdAckg ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillENBConfigUpdFail ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillResStatusRqst_R9 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillResStatusRqst_R11 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillResStatusFail_R9 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillResStatusFail_R11 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillResStatusUpd_R9 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillResStatusUpd_R11 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztResStatusResp_R9 ARGS((CmXtaTCCb    *tcCb,CmXtaSpCb    *spCb,CztEvnt    **cztEvnt ));
EXTERN S16 czAcUtlCztResStatusResp_R11 ARGS((CmXtaTCCb    *tcCb,CmXtaSpCb    *spCb,CztEvnt    **cztEvnt ));
EXTERN S16 czAcUtlCztFillSnStatusTrfr ARGS((CmXtaTCCb    *tcCb,CmXtaSpCb    *spCb,CztEvnt    **cztEvnt));

EXTERN S16 czAcUtlCztFillHovrRqst_R9 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillHovrRqst_R11 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillHovrRqstAck ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillHovrCancel ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillHovrPrepFail  ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillENBStatusTfr  ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillUeCxtRls  ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));
EXTERN S16 czAcUtlCztFillErrInd  ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt **pdu));

PUBLIC S16 czAcUtlCztFillMobChgReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt    **pdu));
PUBLIC S16 czAcUtlCztFillMobChgAck ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt    **pdu));
PUBLIC S16 czAcUtlCztFillMobChgFail ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt    **pdu));
PUBLIC S16 czAcUtlCztFillRlfInd_R9 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt    **pdu));
PUBLIC S16 czAcUtlCztFillRlfInd_R11 ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt    **pdu));
PUBLIC S16 czAcUtlCztFillHOReport ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt    **pdu));
PUBLIC S16 czAcUtlCztFillCellActReq ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt    **pdu));
PUBLIC S16 czAcUtlCztFillCellActRes ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt    **pdu));
PUBLIC S16 czAcUtlCztFillCellActFail ARGS((CmXtaTCCb  *tcCb, CmXtaSpCb  *spCb, CztEvnt    **pdu));

EXTERN S16 czFillTknStr4 ARGS ((TknStr4 *ptr, U8 len, U8 val));
EXTERN S16 czFillTknStrOSXL ARGS ((TknStrOSXL *ptr, U16 len, Data *val, CztEvnt  **pdu));
EXTERN S16 czAcUtlFillTknU32 ARGS((TknU32 *encParam,U32 val));
EXTERN S16 czAcUtlFillTknU8 ARGS((TknU8 *encParam,U8 val));
EXTERN S16 czAcUtlFillTknU16 ARGS((TknU16 *encParam,U16 val));

EXTERN S16 czAcUtlValidateMsg ARGS((CmXtaTCCb  *tcCb,CmXtaSpCb *spCb,
                                      CzAccMsgQElm *czMsg, S16  event));
EXTERN S16 czAcUtlCztGetErrCause ARGS((CztX2AP_PDU *pdu, U8 *causeType, U8 *causeVal));
EXTERN U8 czAcUtlGetMsgType ARGS((CztX2AP_PDU   *pdu));
EXTERN S16 czAcUtlCztGetCritDiag ARGS((CztEvnt   *evnt, CzAcCztCrit *critInfo));


EXTERN S16  czAcUtlGetProcInfo ARGS((U8  msgId,
                                     U8 *procCode, 
                                     U8 *msgType, 
                                     U8 *criticality));

EXTERN CztNetAddrLst dynamDstAddrLst;
#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __CZ_CZT_X_ */

/**********************************************************************

         End of file:     czac_czt.x@@/main/2 - Tue Aug 30 18:35:46 2011

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
/main/1      ---     sy        1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
