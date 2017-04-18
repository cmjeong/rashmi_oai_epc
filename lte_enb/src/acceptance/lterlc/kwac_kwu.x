

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by KWU interface of XTA LTE RLC
 
    File:   kwac_kwu.x
 
    Sid:      kwac_kwu.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:28 2014
 
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


#ifndef __KWAC_KWU_X__
#define __KWAC_KWU_X__

#ifdef __cplusplus
extern "C" {
#endif

/**** KWU reg fucntion prototypes***********/
/*
EXTERN S16 kwAcKwuInit ARGS((
Void
));

EXTERN S16 kwAcKwuDeInit ARGS((
Void
));
*/
/**** KWU hdl fucntion prototypes***********/
EXTERN S16 kwAcHdlKwuBndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlKwuBndCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlKwuUnBndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlKwuDatReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlKwuDatInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlKwuDatCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlKwuDiscSduReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlKwuStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN S16 kwAcHdlKwuDatAckInd ARGS((
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
));
EXTERN S16 kwAcHdlKwuDiscSduCfm ARGS((
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
));
#endif
/**** KWU utl fucntion prototypes***********/
EXTERN S16 kwAcUtlCpyKwuDatReq ARGS((
KwuDatReqInfo  *datReq,
Buffer         *mBuf,
U32            sduSize,
U8            entity
));

EXTERN S16 kwAcUtlBuildKwuDatReq ARGS((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwuDatReqInfo  *datReq,
Buffer         **mBuf,
U8            entity
));

EXTERN S16 kwAcUtlValdtKwuDatInd ARGS((
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwAcMsgQElm       *kwElm,
U8                entity
));

EXTERN S16 kwAcUtlKwuFreeCb ARGS ((
CmXtaMsgQElm *qElm
));

/* Data Request Circular Q primitives */
EXTERN Void kwAcUtlKwuDatReqCQMakeNull ARGS ((
KwAcKwuDatReqQ *queue
));

EXTERN U16 kwAcUtlKwuDatReqCircQAddOne ARGS ((
U16 idx
));

EXTERN U16 kwAcUtlKwuDatReqCircQEnqueue ARGS ((
KwAcKwuDatReqQ *queue
));

EXTERN U16 kwAcUtlKwuDatReqCircQGetFront ARGS ((
KwAcKwuDatReqQ *queue
));

EXTERN U16 kwAcUtlKwuDatReqCircQGetNext ARGS ((
KwAcKwuDatReqQ *queue,
U16            idx
));

EXTERN Void kwAcUtlKwuDatReqCircQDequeue ARGS ((
KwAcKwuDatReqQ *queue
));

/* Data Confirm Circular Q primitives */
EXTERN Void kwAcUtlKwuDatCfmCQMakeNull ARGS ((
KwAcKwuDatCfmQ *queue
));

EXTERN U16 kwAcUtlKwuDatCfmCircQAddOne ARGS ((
U16 idx
));

EXTERN S16 kwAcUtlKwuDatCfmCircQEnqueue ARGS ((
KwAcKwuDatCfmQ *queue
));

EXTERN U16 kwAcUtlKwuDatCfmCircQGetFront ARGS ((
KwAcKwuDatCfmQ *queue
));

EXTERN S16 kwAcUtlKwuDatCfmCircQGetNext ARGS ((
KwAcKwuDatCfmQ *queue,
U16            idx
));

EXTERN Void kwAcUtlKwuDatCfmCircQDequeue ARGS ((
KwAcKwuDatCfmQ *queue
));

EXTERN S16 kwAcUtlCmpKwuDatReqBuf ARGS ((
Buffer *srcBuf,
Buffer *dstBuf,
U32    size
));

/**** KWU Porting fucntion prototypes***********/
EXTERN S16 PtLiKwuBndReq ARGS ((
Pst         *post,
SuId        suId,
SpId        spId
));

EXTERN S16 PtLiKwuUbndReq ARGS ((
Pst         *post,
SpId        spId,
Reason      reason
));

EXTERN S16 PtLiKwuDatReq ARGS ((
Pst            *post,
SpId           spId,
KwuDatReqInfo  *datReq,
Buffer         *mBuf
));

EXTERN S16 PtLiKwuDiscSduReq ARGS ((
Pst               *post,
SpId              spId,
KwuDiscSduInfo    *discSdu
));

#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __KWAC_KWU_X__ */


/**********************************************************************
         End of file:     kwac_kwu.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:28 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     gk            1. Initial Release.
/main/2      ---     gk            1. LTE RLC Release 2.1.
/main/3   kw005.201  ap            1. Added support for L2 Measurement.
*********************************************************************91*/

