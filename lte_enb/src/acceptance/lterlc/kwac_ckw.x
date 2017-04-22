

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by CKW interface of XTA LTE RLC
 
    File:   kwac_ckw.x
 
    Sid:      kwac_ckw.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:23 2014
 
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


#ifndef __KWAC_CKW_X__
#define __KWAC_CKW_X__

#ifdef __cplusplus
extern "C" {
#endif


/**** CKW reg fucntion prototypes***********/
/*
EXTERN S16 kwAcCkwInit ARGS((
Void
));

EXTERN S16 kwAcCkwDeInit ARGS((
Void
));
*/
/**** CKW hdl fucntion prototypes***********/

EXTERN S16 kwAcHdlCkwBndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCkwBndCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCkwUbndReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCkwCfgReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCkwCfgCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCkwUeIdChgReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCkwUeIdChgCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCkwMapDlUl ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

/**** CKW utl fucntion prototypes***********/

EXTERN S16 kwAcUtlCkwBuildCfgReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CkwCfgInfo   *cfgInfo
));

EXTERN S16 kwAcUtlValdtCfgCfm ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
CkwCfgCfmInfo  *cfgCfm
));

EXTERN S16 kwAcUtlCkwFreeCb ARGS ((
CmXtaMsgQElm *qElm
));

EXTERN S16 kwAcUtlCkwBuildUeIdChgReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CkwUeInfo    *ueInfo,
CkwUeInfo    *newUeInfo
));

/* CKW Circular Q Primitives */
EXTERN Void kwAcUtlCkwCQMakeNull ARGS ((
KwAcCkwCircQ *queue
));

EXTERN U16 kwAcUtlCkwCircQAddOne ARGS ((
U16 idx
));

EXTERN U16 kwAcUtlCkwCircQEnqueue ARGS ((
KwAcCkwCircQ *queue
));

EXTERN U16 kwAcUtlCkwCircQGetFront ARGS ((
KwAcCkwCircQ *queue
));

EXTERN U16 kwAcUtlCkwCircQGetNext ARGS ((
KwAcCkwCircQ *queue,
U16            idx
));

EXTERN Void kwAcUtlCkwCircQDequeue ARGS ((
KwAcCkwCircQ *queue
));
/*
EXTERN S16 kwAcUtlCmpKwuDatReqBuf ARGS ((
Buffer *srcBuf,
Buffer *dstBuf,
U32    size
));
*/
/**** CKW Porting Function prototypes ****/
EXTERN S16 PtLiCkwBndReq ARGS ((
Pst         *post,
SuId        suId,
SpId        spId
));

EXTERN S16 PtLiCkwUbndReq ARGS ((
Pst         *post,
SpId        spId,
Reason      reason
));

EXTERN S16 PtLiCkwCfgReq ARGS ((
Pst         *pst,
SpId        spId,
CkwCfgInfo  *cfgInfo
));

EXTERN S16 PtLiCkwUeIdChgReq ARGS ((
Pst         *pst,
SpId        spId,
U32         transId,
CkwUeInfo   *ueInfo,
CkwUeInfo   *newUeInfo
));

#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __KWAC_CKW_X__ */


/**********************************************************************
         End of file:     kwac_ckw.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:23 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     gk            1. Initial Release.
/main/2      ---     gk            1. LTE RLC Release 2.1.
*********************************************************************91*/

