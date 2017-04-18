

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by CKW interface of XTA LTE RLC
 
    File:   kwac_lpj.x
 
    Sid:      kwac_lpj.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:35 2014
 
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


#ifndef __KWAC_LPJ_X__
#define __KWAC_LPJ_X__

#ifdef KW_PDCP
#ifdef __cplusplus
extern "C" {
#endif


/**** LPJ reg fucntion prototypes***********/


/**** LPJ hdl fucntion prototypes***********/
EXTERN S16 kwAcHdlLpjDirective ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 kwAcHdlLpjGenCfgReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjSapCfgReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjTrcCntrlReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjUStaCntrlReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjDbgCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjSapCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjStsReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjStaReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjCfgCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjCntrlCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjStsCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjStaCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjStaInd ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjTrcInd ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpjSDCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN  S16 kwAcHdlLpjL2MeasReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 kwAcHdlLpjL2MeasCfm ARGS((
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
));
#endif /* LTE_L2_MEAS */
/**** LPJ utl fucntion prototypes***********/
EXTERN Void kwAcUtlPjBuildGenCfgReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN Void kwAcUtlPjBuildSapCfgReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN Void kwAcUtlPjBuildTrcCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN Void kwAcUtlPjBuildDbgCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN Void kwAcUtlPjBuildSapCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN S16 kwAcUtlLpjFreeCb ARGS ((
CmXtaMsgQElm *qElm
));

EXTERN Void kwAcUtlPjBuildSDCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));
EXTERN S16 kwAcUtlPjVerifyStaCfm ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjSSta        *sta
));

EXTERN S16 kwAcUtlPjVerifyStaInd ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjUSta        *usta
));

EXTERN S16 kwAcUtlPjVerifyTrcInd ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjTrc         *trc
));

EXTERN S16 kwAcUtlPjVerifyStsCfm ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjSts         *sts
));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN Void kwAcUtlLpjBuildL2MeasReq  ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PjL2MeasReqEvt *l2MeasReqEvt
));
EXTERN S16 kwAcUtlLpjVldtL2MeasCfm ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PjL2MeasCfmEvt *l2MeasCfmEvt
));
#endif /* LTE_L2_MEAS */
EXTERN CmXtaTCCb*  kwAcLpjTstCbFind ARGS (( Void ));

EXTERN S16 SmMiLpjSendMsg ARGS ((
Pst         *pst,
PjMngmt     *cfm,
Buffer      *mBuf
));

#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif /* KW_PDCP */
#endif   /* __KWAC_LPJ_X__ */

/********************************************************************30**
         End of file:     kwac_lpj.x@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:35 2014
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
/main/1      ---       gk     1. LTERLC Release 2.1.
/main/2     kw005.201  ap     1. Added support for L2 Measurement.
*********************************************************************91*/

