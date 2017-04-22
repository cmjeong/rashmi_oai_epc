

/**********************************************************************
 
    Name:   LTE MAC layer
 
    Type:   C include file
 
    Desc:   Defines required by RGU interface of XTA LTE MAC
 
    File:   rgac_rgu.x
 
    Sid:      kwac_rgu.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:43 2014
 
    Prg:    sm 
 
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


#ifndef __KWAC_RGU_X__
#define __KWAC_RGU_X__

#ifdef __cplusplus
extern "C" {
#endif


/**** RGU reg fucntion prototypes***********/
/*
EXTERN S16 kwAcRguInit ARGS((
Void
));

EXTERN S16 kwAcRguDeInit ARGS((
Void
));*/


/**** RGU hdl fucntion prototypes***********/

EXTERN S16 kwAcHdlRguBndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguBndCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguUbndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguCDatReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguDDatReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguCDatInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguDDatInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguCStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguDStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguCStaRsp ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguDStaRsp ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguHqFlInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguRxSduCreate ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguRxPduCreate ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlShutdown ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlChkVar ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlRguSkipValidation ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN S16 kwAcHdlRguHqStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
#ifdef LTE_RLC_R9
EXTERN S16 kwAcHdlRguL2MUlThrpMeasReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
#endif
#endif
/**** RGU utl fucntion prototypes***********/

EXTERN S16 kwAcUtlValdtCDatReq ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguCDatReqInfo    *datReq
));

EXTERN S16 kwAcUtlValdtDDatReq ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguDDatReqInfo    *datReq
));

EXTERN S16 kwAcUtlValdtCStaRsp ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguCStaRspInfo    *staRsp
));

EXTERN S16 kwAcUtlValdtDStaRsp ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguDStaRspInfo    *staRsp
));

EXTERN S16 kwAcUtlBuildCDatInd ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguCDatIndInfo    *datInd
));

EXTERN S16 kwAcUtlBuildDDatInd ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguDDatIndInfo    *datInd
));

EXTERN S16 kwAcUtlBuildRguCStaInd ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguCStaIndInfo    *staInd
));

EXTERN S16 kwAcUtlBuildRguDStaInd ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguDStaIndInfo    *staInd
));
EXTERN S16 kwAcUtlBuildRxSduCreate ARGS((
CmXtaTCCb            *tcCb,
CmXtaSpCb            *spCb
));

EXTERN S16 kwAcUtlBuildRxPduCreate ARGS((
CmXtaTCCb            *tcCb,
CmXtaSpCb            *spCb
));

EXTERN S16 kwAcUtlFreeRguCb ARGS ((
CmXtaMsgQElm   *qElm
));

EXTERN S16 kwAcUtlRguCpyDDatReq ARGS ((
RguDDatReqInfo   *datReq
));

#ifdef KW_PDCP

EXTERN S16 kwAcUtlBuildRxPdcpPduCreate ARGS ((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
));

EXTERN S16 kwAcHdlRguRxPdcpPduCreate ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
#endif /* KW_PDCP */
/* Callback Primitives */
/*
EXTERN CmXtaTCCb*  kwAcRguTstCbFind ARGS ((
Void
));

EXTERN S16 kwAcRguSendMsg ARGS ((
Pst            *pst,
SuId           suId,
SpId           spId,
Reason         reason,
Void           *ptr
));

EXTERN U16 kwAcUtlKwuDatReqCircQGetFront ARGS ((
KwAcKwuDatReqQ *queue
));

EXTERN U16 kwAcUtlKwuDatReqCircQGetNext ARGS ((
KwAcKwuDatReqQ *queue,
U16            idx
));
*/
/* RGU DStaRsp Circular Q Primitives */
EXTERN Void kwAcUtlRguDStaRspCQMakeNull ARGS ((
KwAcRguDStaRspQ *queue
));

EXTERN U16 kwAcUtlRguDStaRspCircQAddOne ARGS ((
U16 idx
));

EXTERN S16 kwAcUtlRguDStaRspCircQEnqueue ARGS ((
KwAcRguDStaRspQ *queue
));

EXTERN U16 kwAcUtlRguDStaRspCircQGetFront ARGS ((
KwAcRguDStaRspQ *queue
));

EXTERN S16 kwAcUtlRguDStaRspCircQGetNext ARGS ((
KwAcRguDStaRspQ *queue,
U16            idx
));

EXTERN Void kwAcUtlRguDStaRspCircQDequeue ARGS ((
KwAcRguDStaRspQ *queue
));

/* RGU DStaInd Circular Q Primitives */
EXTERN Void kwAcUtlRguDStaIndCQMakeNull ARGS ((
KwAcRguDStaIndQ *queue
));

EXTERN U16 kwAcUtlRguDStaIndCircQAddOne ARGS ((
U16 idx
));

EXTERN S16 kwAcUtlRguDStaIndCircQEnqueue ARGS ((
KwAcRguDStaIndQ *queue
));

EXTERN U16 kwAcUtlRguDStaIndCircQGetFront ARGS ((
KwAcRguDStaIndQ *queue
));

EXTERN S16 kwAcUtlRguDStaIndCircQGetNext ARGS ((
KwAcRguDStaIndQ *queue,
U16            idx
));

EXTERN Void kwAcUtlRguDStaIndCircQDequeue ARGS ((
KwAcRguDStaIndQ *queue
));

/* RGU CDatReq Circular Q Primitives */
EXTERN Void kwAcUtlRguCDatReqCQMakeNull ARGS ((
KwAcRguCDatReqQ *queue
));

EXTERN U16 kwAcUtlRguCDatReqCircQAddOne ARGS ((
U16 idx
));

EXTERN S16 kwAcUtlRguCDatReqCircQEnqueue ARGS ((
KwAcRguCDatReqQ *queue
));

EXTERN U16 kwAcUtlRguCDatReqCircQGetFront ARGS ((
KwAcRguCDatReqQ *queue
));

EXTERN S16 kwAcUtlRguCDatReqCircQGetNext ARGS ((
KwAcRguCDatReqQ *queue,
U16            idx
));

EXTERN Void kwAcUtlRguCDatReqCircQDequeue ARGS ((
KwAcRguCDatReqQ *queue
));

/* RGU DDatReq Circular Q Primitives */
EXTERN Void kwAcUtlRguDDatReqCQMakeNull ARGS ((
KwAcRguDDatReqQ *queue
));

EXTERN U16 kwAcUtlRguDDatReqCircQAddOne ARGS ((
U16 idx
));

EXTERN S16 kwAcUtlRguDDatReqCircQEnqueue ARGS ((
KwAcRguDDatReqQ *queue
));

EXTERN U16 kwAcUtlRguDDatReqCircQGetFront ARGS ((
KwAcRguDDatReqQ *queue
));

EXTERN S16 kwAcUtlRguDDatReqCircQGetNext ARGS ((
KwAcRguDDatReqQ *queue,
U16            idx
));

EXTERN Void kwAcUtlRguDDatReqCircQDequeue ARGS ((
KwAcRguDDatReqQ *queue
));

/* RGU CDatInd Circular Q Primitives */
EXTERN Void kwAcUtlRguCDatIndCQMakeNull ARGS ((
KwAcRguCDatIndQ *queue
));

EXTERN U16 kwAcUtlRguCDatIndCircQAddOne ARGS ((
U16 idx
));

EXTERN S16 kwAcUtlRguCDatIndCircQEnqueue ARGS ((
KwAcRguCDatIndQ *queue
));

EXTERN U16 kwAcUtlRguCDatIndCircQGetFront ARGS ((
KwAcRguCDatIndQ *queue
));

EXTERN S16 kwAcUtlRguCDatIndCircQGetNext ARGS ((
KwAcRguCDatIndQ *queue,
U16            idx
));

EXTERN Void kwAcUtlRguCDatIndCircQDequeue ARGS ((
KwAcRguCDatIndQ *queue
));

/* RGU DDatInd Circular Q Primitives */
EXTERN Void kwAcUtlRguDDatIndCQMakeNull ARGS ((
KwAcRguDDatIndQ *queue
));

EXTERN U16 kwAcUtlRguDDatIndCircQAddOne ARGS ((
U16 idx
));

EXTERN S16 kwAcUtlRguDDatIndCircQEnqueue ARGS ((
KwAcRguDDatIndQ *queue
));

EXTERN U16 kwAcUtlRguDDatIndCircQGetFront ARGS ((
KwAcRguDDatIndQ *queue
));

EXTERN S16 kwAcUtlRguDDatIndCircQGetNext ARGS ((
KwAcRguDDatIndQ *queue,
U16            idx
));

EXTERN Void kwAcUtlRguDDatIndCircQDequeue ARGS ((
KwAcRguDDatIndQ *queue
));

/**** RGU utl fucntion prototypes***********/
EXTERN S16 PtUiRguBndCfm ARGS ((
Pst      *pst,                      /* post structure */
SuId     suId,                      /* Service User Id */
U8       status                     /* Status */
));

EXTERN S16 PtUiRguCDatInd ARGS ((
Pst               *pst,
SuId              suId,
RguCDatIndInfo    *cDatInd
));

EXTERN S16 PtUiRguDDatInd ARGS ((
Pst               *pst,
SuId              suId,
RguDDatIndInfo    *dDatInd
));

EXTERN S16 PtUiRguCStaInd ARGS ((
Pst               *pst,
SuId              suId,
RguCStaIndInfo    *cStaInd
));

EXTERN S16 PtUiRguDStaInd ARGS ((
Pst               *pst,
SuId              suId,
RguDStaIndInfo    *dStaInd
));
#ifdef LTE_L2_MEAS
EXTERN S16 PtUiRguHqStaInd ARGS((
Pst               *pst,
SuId              suId,
RguHarqStatusInd *harqStatusInd
));
#endif
#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __KWAC_RGU_X__ */


/**********************************************************************
         End of file:     kwac_rgu.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:43 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sm            1. Initial Release.
/main/2      ---     gk            1. LTE RLC Release 2.1.
/main/3     kw005.201 ap           1. Added support for L2 Measurement.
*********************************************************************91*/

