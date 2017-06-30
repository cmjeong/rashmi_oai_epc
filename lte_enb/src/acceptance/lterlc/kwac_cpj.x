

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by CPJ interface of XTA LTE RLC
 
    File:   kwac_ckw.x
 
    Sid:      kwac_cpj.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:25 2014
 
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


#ifndef __KWAC_CPJ_X__
#define __KWAC_CPJ_X__

#ifdef KW_PDCP

#ifdef __cplusplus
extern "C" {
#endif


/**** CPJ reg fucntion prototypes***********/


/**** CPJ hdl fucntion prototypes***********/

EXTERN S16 kwAcHdlCpjBndReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjBndCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjUbndReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjCfgReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjCfgCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjReEstReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjReEstCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjSecCfgReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjSecCfgCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjUeIdChgReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjUeIdChgCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjCountReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjCountCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjSduStaReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 kwAcHdlCpjSduStaCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

/**** CPJ utl fucntion prototypes***********/

EXTERN S16 kwAcUtlCpjBuildCfgReq ARGS
((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjCfgReqInfo   *cfgReq
));

EXTERN S16 kwAcUtlCpjValdtCfgCfm ARGS
((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjCfgCfmInfo   *cfgReq
));

EXTERN S16 kwAcUtlCpjBuildReEstReq ARGS
((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjReEstReqInfo   *cfgReq
));

EXTERN S16 kwAcUtlValdtReEstCfm ARGS
((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjReEstCfmInfo   *cfgReq
));

EXTERN S16 kwAcUtlCpjBuildSecCfgReq ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjSecCfgReqInfo *cfgReq
));

EXTERN S16 kwAcUtlValdtSecCfgCfm ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjSecCfgCfmInfo *cfgReq
));

EXTERN S16 kwAcUtlCpjBuildUeIdChgReq ARGS
((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjUeInfo    *ueInfo,
CpjUeInfo    *newUeInfo
));

EXTERN S16 kwAcUtlCpjBuildCountReq ARGS
((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjCountReqInfo *cfgReq
));

EXTERN S16 kwAcUtlValdtCountCfm ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjCountCfmInfo *cfgReq
));

EXTERN S16 kwAcUtlValdtSduStaCfm ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjSduStaCfmInfo *cfgReq
));

EXTERN S16 kwAcUtlCpjBuildSduStaReq ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjSduStaReqInfo *cfgReq
));

/* CPJ Circular Q Primitives */
EXTERN Void kwAcUtlCpjCQMakeNull ARGS ((
KwAcCpjCfgReqQ *queue
));

EXTERN U16 kwAcUtlCpjCircQAddOne ARGS ((
U16 idx
));

EXTERN U16 kwAcUtlCpjCircQEnqueue ARGS ((
KwAcCpjCfgReqQ *queue
));

EXTERN U16 kwAcUtlCpjCircQGetFront ARGS ((
KwAcCpjCfgReqQ *queue
));

EXTERN U16 kwAcUtlCpjCircQGetNext ARGS ((
KwAcCpjCfgReqQ *queue,
U16            idx
));

EXTERN Void kwAcUtlCpjCircQDequeue ARGS ((
KwAcCpjCfgReqQ *queue
));

EXTERN S16 kwAcUtlCpjFreeCb ARGS
((
CmXtaMsgQElm   *qElm
));

/**** CPJ Porting Function prototypes ****/

#ifdef __cplusplus
}
#endif   /* __cplusplus */

#endif /* KW_PDCP */
#endif   /* __KWAC_CPJ_X__ */


/**********************************************************************
         End of file:     kwac_cpj.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:25 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---   gk         1. LTERLC Release 2.1.
*********************************************************************91*/

