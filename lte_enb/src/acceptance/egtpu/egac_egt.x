
/********************************************************************20**

     Name:     eGTP Layer

     Type:     C source file

     Desc:     C Source code for Upper Interface procedures

     File:     egac_egt.x

     Sid:      egac_egt.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:30 2015

     Prg:      an

*********************************************************************21*/

#ifndef __EG_EGT_X__
#define __EG_EGT_X__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _egtEgEvt
{
SuId           suId;
U32          lclTransId;    /* Transaction ID */
U32          teid;      /* self TEID */
CmStatus     status;
U8           eventType;    /* Status event type */
TknU32      transId;   /* Transaction IDentifier */
TknU32      lclTeid;   /* Local Tunnel Identifier */
U8          reason; 
}EgtEgEvt;

EXTERN S16 egAcEgtDeInit ARGS((
Void
));

EXTERN S16 egAcEgtInit ARGS((
Void
));

/**** Start of egt handle fucntion prototypes***********/

EXTERN S16 egAcHdlEgtBndReq ARGS((
CmXtaTCCb    *tcCb, 
CmXtaSpCb    *spCb  
));

EXTERN S16 egAcHdlEgtBndCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 egAcHdlEgtUbndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 egAcHdlEgtSigReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 egAcHdlEgtSigInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 egAcHdlEgtSigRsp ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 egAcHdlEgtSigCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 egAcHdlEgtStaReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 egAcHdlEgtStaCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 egAcHdlEgtStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 egAcHdlEgtErrInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 egAcHdlEgtLclDelReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 egAcHdlEgtLclDelCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

#ifdef EGTP_U

EXTERN S16 eguAcHdlEgtDatReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

/*  eg001.201 Adding Procedure declaration   */
EXTERN S16 eguAcHdlEgtControlParameter ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 eguAcHdlEgtDatInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 eguAcHdlLclTnlMgmtReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 eguAcHdlLclTnlMgmtCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 eguAcHdlEgtStaReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 eguAcHdlEgtStaCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 eguAcHdlEgtUStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 eguAcHdlEgtErrInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

#endif /* EGTP_U */

/**** End of egt handle fucntion prototypes***********/

PUBLIC S16 egAcUtlEgtCb ARGS((
CmXtaMsgQElm   *qElm
));

EXTERN CmXtaTCCb*  egAcEgtTstCbFind ARGS((
Void
));

EXTERN S16 egAcEgtSendMsg ARGS((
Pst            *pst,
SpId           suId,
Reason         reason,
Void           *ptr
));

/*-- eg003.201 : merge changes from eg006.102: deleted EuLiEgtBndCfm declaration --*/ 

#ifdef EGTP_C
EXTERN S16 egAcUtlEgtBuildMsg ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */ 
EgBuildMsg   *bldMsg,
EgMsg        **egMsg,
U8           apiType));

EXTERN S16 egAcEgtBuildIEs ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */ 
EgBuildMsg   *bldMsg,
EgMsg        **egMsg,
U8           apiType,
U8           eventType,
U8           egtpMsgType));

#endif /* EGTP_C */
#ifdef EGTP_C
PUBLIC S16 egAcEgtSaveMsg ARGS
((
Pst               *pst,
EgtEgEvt         egEvt,
CmTptAddr   *localAddr,
CmTptAddr     *remAddr,
EgMsg           *egMsg,
EgPathInfo   *pathInfo,
EgPathStatus   *pathStatus,
EgErrEvnt      *errEvnt 
));
#else
PUBLIC S16 egAcEgtSaveMsg ARGS
((
Pst               *pst,
EgtEgEvt         egEvt
));
#endif


EXTERN SpId egAcEgtGetSpId ARGS((
U8    tptProt,
U8   entityId,
Bool  useDummy
));

EXTERN U8 egAcEgtGetTransport ARGS((
         CmXtaTCCb    *tcCb    /* tcCb data structure  */
));

EXTERN S16 egAcEguGetAddress ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CmTptAddr    *address,
U8           addrType));

/*-- eg006.201: Prototype for  egAcEgGetAddress --*/
#ifdef EGTP_C 
EXTERN S16 egAcEgGetAddress ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CmTptAddr    *address,
U8           addrType));
#endif

EXTERN S16 egAcEgtGetAddress ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,     /* spCb data structure  */ 
EgBuildMsg   *bldMsg,
U8           addrType));

#ifdef EGTP_U

EXTERN S16 eguAcUtlEgtBuildDatReq ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgBuildMsg        *bldMsg,
EgtUEvnt          **eguEvtMsg
));

EXTERN S16 eguAcUtlEgtBuildTnlMgmtReq ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgBuildMsg        *bldMsg,
EgtUEvnt          **eguEvtMsg
));

EXTERN S16 eguAcUtlEgtBuildStaReq ARGS
((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgBuildMsg        *bldMsg,
EgtUEvnt          **eguEvtMsg
));

/*-- eg003.201 : merge changes from eg006.102: made egAcEgtSaveEguMsg EXTERN */
EXTERN S16 egAcEgtSaveEguMsg ARGS
((
Pst         *pst,
SuId        suId,
EgtUEvnt    *eguMsg
));

#endif /* EGTP_U */

#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __EG_EGT_X_ */

/**********************************************************************

         End of file:     egac_egt.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:30 2015

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
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3   eg001.201   asaurabh    1. Added procedure declaration
/main/3   eg003.201   psingh      1. Merged code from eg006.102 to Fix warnings
/main/3   eg006.201   psingh      1. Added Prototype for  egAcEgGetAddress
*********************************************************************91*/
