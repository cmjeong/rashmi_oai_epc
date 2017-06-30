

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by CKW interface of XTA LTE RLC
 
    File:   kwac_ckw.x
 
    Sid:      kwac_lkw.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:33 2014
 
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


#ifndef __KWAC_LKW_X__
#define __KWAC_LKW_X__

#ifdef __cplusplus
extern "C" {
#endif


/**** LKW reg fucntion prototypes***********/


/**** LKW hdl fucntion prototypes***********/
EXTERN S16 kwAcHdlLkwGenCfgReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwSapCfgReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwTrcCntrlReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwUStaCntrlReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwDbgCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwSapCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwStsReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwStaReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwCfgCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwCntrlCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwStsCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwStaCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwStaInd ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwTrcInd ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLkwSDCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN  S16 kwAcHdlLkwL2MeasReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 kwAcHdlLkwL2MeasCfm ARGS((
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
));
#endif /* LTE_L2_MEAS */
/**** LKW utl fucntion prototypes***********/
EXTERN Void kwAcUtlKwBuildGenCfgReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwMngmt     *kwMngmt
));

EXTERN Void kwAcUtlKwBuildSapCfgReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwMngmt     *kwMngmt
));

EXTERN Void kwAcUtlKwBuildTrcCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwMngmt     *kwMngmt
));

EXTERN Void kwAcUtlKwBuildDbgCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwMngmt     *kwMngmt
));

EXTERN Void kwAcUtlKwBuildSapCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwMngmt     *kwMngmt
));

EXTERN S16 kwAcUtlLkwFreeCb ARGS ((
CmXtaMsgQElm *qElm
));

EXTERN Void kwAcUtlKwBuildSDCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwMngmt     *kwMngmt
));
/*
EXTERN S16 kwAcUtlKwVerifyStaCfm ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
KwSSta        *sta
));

EXTERN S16 kwAcUtlKwVerifyStaInd ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
KwUSta        *usta
));

EXTERN S16 kwAcUtlKwVerifyTrcInd ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
KwTrc         *trc
));

EXTERN S16 kwAcUtlKwVerifyStsCfm ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
KwSts         *sts
));

EXTERN CmXtaTCCb*  kwAcLkwTstCbFind ARGS (( Void ));

EXTERN S16 SmMiLkwSendMsg ARGS ((
Pst         *pst,
KwMngmt     *cfm,
Buffer      *mBuf
));

EXTERN S16 kwAcLkwInit ARGS (( Void ));

EXTERN S16 kwAcLkwDeInit ARGS (( Void ));
*/
#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __KWAC_LKW_X__ */

/********************************************************************30**
         End of file:     kwac_lkw.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:33 2014
*********************************************************************31*/


/********************************************************************40**
        Notes:
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**
        Revision history:
 
*********************************************************************61*/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     gk      1. Initial Release.
/main/2      ---     gk      1. LTE RLC Release 2.1
/main/3   kw005.201  ap      1. Added support for L2 Measurement.
*********************************************************************91*/

