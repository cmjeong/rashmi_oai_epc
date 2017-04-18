

/**********************************************************************
 
    Name:   LTE PDCP layer
 
    Type:   C include file
 
    Desc:   Defines required by PJU interface of XTA LTE PDCP
 
    File:   pjac_pju.x
 
    Sid:      pjac_pju.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:07 2015
 
    Prg:    Adarsh 
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000371       LTE PDCP
*
*/


#ifndef __PJAC_PJU_X__
#define __PJAC_PJU_X__

/* Venki */
#ifndef KW_PDCP
#ifdef __cplusplus
extern "C" {
#endif

/**** PJU reg fucntion prototypes***********/
/*
EXTERN S16 pjAcPjuInit ARGS((
Void
));

EXTERN S16 pjAcPjuDeInit ARGS((
Void
));
*/
/**** PJU hdl fucntion prototypes***********/
EXTERN S16 pjAcHdlPjuBndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlPjuBndCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlPjuUnBndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlPjuDatReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlPjuDatInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlPjuDatCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlPjuStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlPjuDatFwdReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlPjuDatFwdInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

/**** PJU utl fucntion prototypes***********/
EXTERN S16 pjAcUtlCmpPjuDatReqBuf ARGS ((
Buffer *srcBuf,
Buffer *dstBuf,
U32    size
));
EXTERN S16 pjAcUtlCpyPjuDatReq ARGS((
CmLtePdcpId    *pdcpId,
U32            *sduId,
Buffer         *mBuf,
U16            sduSize,
U8             entity
));

EXTERN S16 pjAcUtlBuildPjuDatReq ARGS((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CmLtePdcpId    *pdcpId,
U32            *sduId,
Buffer         **mBuf,
U8             entity
));

EXTERN S16 pjAcUtlValdtPjuDatInd ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwAcMsgQElm       *kwElm,
U8                entity
));

EXTERN S16 pjAcUtlBuildPjuDatFwdReq ARGS ((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PjuDatFwdReqInfo   *datFwdReq,
CmLtePdcpId  *pdcpId
));

EXTERN S16 pjAcUtlValdtPjuDatFwdInd ARGS ((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwAcMsgQElm       *kwElm
));
EXTERN S16 pjAcUtlPjuFreeCb ARGS ((
CmXtaMsgQElm *qElm
));

/* Data Request Circular Q primitives */
EXTERN Void pjAcUtlPjuDatReqCQMakeNull ARGS ((
KwAcPjuDatReqQ *queue
));

EXTERN U16 pjAcUtlPjuDatReqCircQAddOne ARGS ((
U16 idx
));

EXTERN U16 pjAcUtlPjuDatReqCircQEnqueue ARGS ((
KwAcPjuDatReqQ *queue
));

EXTERN U16 pjAcUtlPjuDatReqCircQGetFront ARGS ((
KwAcPjuDatReqQ *queue
));

EXTERN U16 pjAcUtlPjuDatReqCircQGetNext ARGS ((
KwAcPjuDatReqQ *queue,
U16            idx
));

EXTERN Void pjAcUtlPjuDatReqCircQDequeue ARGS ((
KwAcPjuDatReqQ *queue
));

/**** PJU Porting fucntion prototypes***********/
#if defined(PTNHLIPJU) || defined(PTNXLIPJU)
EXTERN S16 PtLiPjuBndReq ARGS ((
Pst         *post,
SuId        suId,
SpId        spId
));

EXTERN S16 PtLiPjuUbndReq ARGS ((
Pst         *post,
SpId        spId,
Reason      reason
));

EXTERN S16 PtLiPjuDatReq ARGS ((
Pst            *post,
SpId           spId,
CmLtePdcpId    *pdcpId,
PjuSduId       sduId,
Buffer         *mBuf
));

EXTERN S16 PtLiPjuDatFwdReq ARGS ((
Pst* pst,
SpId spId,
CmLtePdcpId * pdcpId,
PjuDatFwdReqInfo * datFwdReq
));


#endif /* PTNHLIPJU || PTNXLIPJU */

EXTERN S16 pjAcHdlPjuShutdown ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));


#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif /* KW_PDCP */
#endif   /* __PJAC_PJU_X__ */


/**********************************************************************
         End of file:     pjac_pju.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:07 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       vb         1. LTE PDCP Release 2.1.
*********************************************************************91*/
