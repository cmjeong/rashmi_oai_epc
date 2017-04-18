

/**********************************************************************
 
    Name:   LTE PDCP layer
 
    Type:   C include file
 
    Desc:   Defines required by KWU interface of XTA LTE PDCP
 
    File:   pjac_kwu.x
 
    Sid:      pjac_kwu.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:52 2015
 
    Prg:    adarsh 
 
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


#ifndef __PJAC_KWU_X__
#define __PJAC_KWU_X__

#ifdef __cplusplus
extern "C" {
#endif

/**** KWU reg fucntion prototypes***********/
/*
EXTERN S16 pjAcKwuInit ARGS((
Void
));

EXTERN S16 pjAcKwuDeInit ARGS((
Void
));
*/
/**** KWU hdl fucntion prototypes***********/
EXTERN S16 pjAcHdlKwuBndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlKwuBndCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlKwuUnBndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlKwuDatReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlKwuDatInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlKwuDatCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
/*
EXTERN S16 pjAcHdlKwuDiscSduReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
*/

EXTERN S16 pjAcHdlKwuReEstCmpInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));


EXTERN S16 pjAcHdlKwuStaInd ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 pjAcHdlKwuShutdown ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlKwuDiscSduCfm ARGS((
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN S16 pjAcHdlKwuDatAckInd ARGS((
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
));
#endif
/**** KWU utl fucntion prototypes***********/
EXTERN S16 pjAcUtlCpyKwuDatReq ARGS((
KwuDatReqInfo  *datReq,
Buffer         *mBuf,
U32            sduSize,
U8            entity
));


EXTERN S16 pjAcUtlKwuFreeCb ARGS ((
CmXtaMsgQElm *qElm
));

/* Data Request Circular Q primitives */
EXTERN Void pjAcUtlKwuDatReqCQMakeNull ARGS ((
PjAcKwuDatReqQ *queue
));

EXTERN U16 pjAcUtlKwuDatReqCircQAddOne ARGS ((
U16 idx
));

EXTERN U16 pjAcUtlKwuDatReqCircQEnqueue ARGS ((
PjAcKwuDatReqQ *queue
));

EXTERN U16 pjAcUtlKwuDatReqCircQGetFront ARGS ((
PjAcKwuDatReqQ *queue
));

EXTERN U16 pjAcUtlKwuDatReqCircQGetNext ARGS ((
PjAcKwuDatReqQ *queue,
U16            idx
));

EXTERN Void pjAcUtlKwuDatReqCircQDequeue ARGS ((
PjAcKwuDatReqQ *queue
));

/* Data Confirm Circular Q primitives */
EXTERN Void pjAcUtlKwuDatCfmCQMakeNull ARGS ((
PjAcKwuDatCfmQ *queue
));

EXTERN U16 pjAcUtlKwuDatCfmCircQAddOne ARGS ((
U16 idx
));

EXTERN S16 pjAcUtlKwuDatCfmCircQEnqueue ARGS ((
PjAcKwuDatCfmQ *queue
));

EXTERN U16 pjAcUtlKwuDatCfmCircQGetFront ARGS ((
PjAcKwuDatCfmQ *queue
));

EXTERN S16 pjAcUtlKwuDatCfmCircQGetNext ARGS ((
PjAcKwuDatCfmQ *queue,
U16            idx
));

EXTERN Void pjAcUtlKwuDatCfmCircQDequeue ARGS ((
PjAcKwuDatCfmQ *queue
));

EXTERN S16 pjAcUtlCmpKwuDatReqBuf ARGS ((
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

EXTERN S16 pjAcUtlKwuCpyDatReq ARGS ((
KwuDatReqInfo   *datReq,
Buffer          *mBuf
));



#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __PJAC_KWU_X__ */

/**********************************************************************
         End of file:     pjac_kwu.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:52 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      av            1. LTE PDCP Initial Release 2.1
*********************************************************************91*/
