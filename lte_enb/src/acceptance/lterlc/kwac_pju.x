

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by PJU interface of XTA LTE RLC
 
    File:   kwac_pju.x
 
    Sid:      kwac_pju.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:39 2014
 
    Prg:    gk 
 
**********************************************************************/
 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*     1000371       LTE RLC
*
*/


#ifndef __KWAC_PJU_X__
#define __KWAC_PJU_X__

#ifdef KW_PDCP
#ifdef __cplusplus
extern "C" {
#endif

/**** PJU reg fucntion prototypes***********/
/*
EXTERN S16 kwAcPjuInit ARGS((
Void
));

EXTERN S16 kwAcPjuDeInit ARGS((
Void
));
*/
/**** PJU hdl fucntion prototypes***********/
EXTERN S16 kwAcHdlPjuBndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlPjuBndCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlPjuUnBndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlPjuDatReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlPjuDatInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlPjuDatCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlPjuStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlPjuDatFwdReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlPjuDatFwdInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

/**** PJU utl fucntion prototypes***********/
EXTERN S16 kwAcUtlCmpPjuDatReqBuf ARGS ((
Buffer *srcBuf,
Buffer *dstBuf,
U32    size
));
EXTERN S16 kwAcUtlCpyPjuDatReq ARGS((
CmLtePdcpId    *pdcpId,
U32            *sduId,
Buffer         *mBuf,
U16            sduSize,
U8             entity
));

EXTERN S16 kwAcUtlBuildPjuDatReq ARGS((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CmLtePdcpId    *pdcpId,
U32            *sduId,
Buffer         **mBuf,
U8             entity
));

EXTERN S16 kwAcUtlValdtPjuDatInd ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwAcMsgQElm       *kwElm,
U8                entity
));

EXTERN S16 kwAcUtlBuildPjuDatFwdReq ARGS ((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PjuDatFwdReqInfo   *datFwdReq
));

EXTERN S16 kwAcUtlValdtPjuDatFwdInd ARGS ((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwAcMsgQElm       *kwElm
));
EXTERN S16 kwAcUtlPjuFreeCb ARGS ((
CmXtaMsgQElm *qElm
));

/* Data Request Circular Q primitives */
EXTERN Void kwAcUtlPjuDatReqCQMakeNull ARGS ((
KwAcPjuDatReqQ *queue
));

EXTERN U16 kwAcUtlPjuDatReqCircQAddOne ARGS ((
U16 idx
));

EXTERN U16 kwAcUtlPjuDatReqCircQEnqueue ARGS ((
KwAcPjuDatReqQ *queue
));

EXTERN U16 kwAcUtlPjuDatReqCircQGetFront ARGS ((
KwAcPjuDatReqQ *queue
));

EXTERN U16 kwAcUtlPjuDatReqCircQGetNext ARGS ((
KwAcPjuDatReqQ *queue,
U16            idx
));

EXTERN Void kwAcUtlPjuDatReqCircQDequeue ARGS ((
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

#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif /* KW_PDCP */
#endif   /* __KWAC_PJU_X__ */


/**********************************************************************
         End of file:     kwac_pju.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:39 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---   mn         1. LTERLC Release 2.1.
*********************************************************************91*/

