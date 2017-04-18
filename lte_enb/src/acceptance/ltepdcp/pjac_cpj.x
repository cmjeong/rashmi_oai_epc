

/**********************************************************************
 
    Name:   LTE PDCP layer
 
    Type:   C include file
 
    Desc:   Defines required by CPJ interface of XTA LTE PDCP
 
    File:   pjac_cpj.x
 
    Sid:      pjac_cpj.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:46 2015
 
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


#ifndef __PJAC_CPJ_X__
#define __PJAC_CPJ_X__

/* Venki - #ifndef KW_PDCP */
#ifndef KW_PDCP

#ifdef __cplusplus
extern "C" {
#endif

#include "pj_udx.c"
/**** CPJ reg fucntion prototypes***********/


/**** CPJ hdl fucntion prototypes***********/

EXTERN S16 pjAcHdlCpjBndReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjBndCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjUbndReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjCfgReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjCfgCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjReEstReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjReEstCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjSecCfgReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjSecCfgCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjUeIdChgReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjUeIdChgCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjCountReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjCountCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjSduStaReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjSduStaCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjDatResumeReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjDatResumeCfm ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

EXTERN S16 pjAcHdlCpjDatForwardReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));

/**** CPJ utl fucntion prototypes***********/

EXTERN S16 pjAcUtlCpjBuildCfgReq ARGS
((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjCfgReqInfo   *cfgReq
));

EXTERN S16 pjAcUtlCpjValdtCfgCfm ARGS
((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjCfgCfmInfo   *cfgReq
));

EXTERN S16 pjAcUtlCpjBuildReEstReq ARGS
((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjReEstReqInfo   *cfgReq
));

EXTERN S16 pjAcUtlValdtReEstCfm ARGS
((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjReEstCfmInfo   *cfgReq
));

EXTERN S16 pjAcUtlCpjBuildSecCfgReq ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjSecCfgReqInfo *cfgReq
));

EXTERN S16 pjAcUtlValdtSecCfgCfm ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjSecCfgCfmInfo *cfgReq
));

EXTERN S16 pjAcUtlCpjBuildUeIdChgReq ARGS
((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjUeInfo    *ueInfo,
CpjUeInfo    *newUeInfo
));

EXTERN S16 pjAcUtlCpjBuildCountReq ARGS
((
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
CpjCountReqInfo *cfgReq
));

EXTERN S16 pjAcUtlValdtCountCfm ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjCountCfmInfo *cfgReq
));

EXTERN S16 pjAcUtlValdtSduStaCfm ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjSduStaCfmInfo *cfgReq
));

EXTERN S16 pjAcUtlCpjBuildSduStaReq ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjSduStaReqInfo *cfgReq
));

EXTERN S16 pjAcUtlValdtDatResumeCfm ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjDatResumeCfmInfo *datResumeCfm 
));

EXTERN S16 pjAcUtlCpjBuildDatResumeReq ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjDatResumeReqInfo *datResumeReq 
));

EXTERN S16 pjAcUtlCpjBuildDatForwardReq ARGS
((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
CpjDataFwdReqInfo *datForwardReq 
));

/* CPJ Circular Q Primitives */
EXTERN Void pjAcUtlCpjCQMakeNull ARGS ((
KwAcCpjCfgReqQ *queue
));

EXTERN U16 pjAcUtlCpjCircQAddOne ARGS ((
U16 idx
));

EXTERN U16 pjAcUtlCpjCircQEnqueue ARGS ((
KwAcCpjCfgReqQ *queue
));

EXTERN U16 pjAcUtlCpjCircQGetFront ARGS ((
KwAcCpjCfgReqQ *queue
));

EXTERN U16 pjAcUtlCpjCircQGetNext ARGS ((
KwAcCpjCfgReqQ *queue,
U16            idx
));

EXTERN Void pjAcUtlCpjCircQDequeue ARGS ((
KwAcCpjCfgReqQ *queue
));

EXTERN S16 pjAcUtlCpjFreeCb ARGS
((
CmXtaMsgQElm   *qElm
));

/**** CPJ Porting Function prototypes ****/

#ifdef __cplusplus
}
#endif   /* __cplusplus */

#endif /* KW_PDCP */
#endif   /* __PJAC_CPJ_X__ */


/**********************************************************************
         End of file:     pjac_cpj.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:46 2015
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       vb         1. LTE PDCP Initial Release 2.1.
*********************************************************************91*/
