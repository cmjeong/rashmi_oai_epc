

/**********************************************************************
 
    Name:   LTE PDCP layer
 
    Type:   C include file
 
    Desc:   Defines required by LPJ interface of XTA LTE PDCP
 
    File:   pjac_lpj.x
 
    Sid:      pjac_lpj.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:00 2015
 
    Prg:    Adarsh 
 
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


#ifndef __PJAC_LPJ_X__
#define __PJAC_LPJ_X__

#ifdef KW_PDCP
#ifdef __cplusplus
extern "C" {
#endif


/**** LPJ reg fucntion prototypes***********/


/**** LPJ hdl fucntion prototypes***********/
EXTERN S16 pjAcHdlLpjDirective ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 pjAcHdlLpjGenCfgReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjSapCfgReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjTrcCntrlReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjUStaCntrlReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjDbgCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjSapCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjStsReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjStaReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjCfgCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjCntrlCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjStsCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjStaCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjStaInd ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjTrcInd ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjSDCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjSapCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN  S16 pjAcHdlLpjL2MeasReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 pjAcHdlLpjL2MeasCfm ARGS((
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
));
#endif /* LTE_L2_MEAS */
/**** LPJ utl fucntion prototypes***********/
EXTERN Void pjAcUtlPjBuildGenCfgReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN Void pjAcUtlPjBuildSapCfgReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN Void pjAcUtlPjBuildTrcCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN Void pjAcUtlPjBuildDbgCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN Void pjAcUtlPjBuildSapCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN S16 pjAcUtlLpjFreeCb ARGS ((
CmXtaMsgQElm *qElm
));

EXTERN Void pjAcUtlPjBuildSDCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));
EXTERN S16 pjAcUtlPjVerifyStaCfm ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjSSta        *sta
));

EXTERN S16 pjAcUtlPjVerifyStaInd ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjUSta        *usta
));

EXTERN S16 pjAcUtlPjVerifyTrcInd ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjTrc         *trc
));

EXTERN S16 pjAcUtlPjVerifyStsCfm ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjSts         *sts
));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN Void pjAcUtlLpjBuildL2MeasReq  ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PjL2MeasReqEvt *l2MeasReqEvt
));
EXTERN S16 pjAcUtlLpjVldtL2MeasCfm ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PjL2MeasCfmEvt *l2MeasCfmEvt
));
#endif /* LTE_L2_MEAS */
EXTERN CmXtaTCCb*  pjAcLpjTstCbFind ARGS (( Void ));

EXTERN S16 SmMiLpjSendMsg ARGS ((
Pst         *pst,
PjMngmt     *cfm,
Buffer      *mBuf
));

#ifdef __cplusplus
}
#endif   /* __cplusplus */

/* ##################################################################################################### */

/* Venki - #ifndef KW_PDCP */
#else

#ifdef __cplusplus
extern "C" {
#endif


/**** LPJ reg fucntion prototypes***********/


/**** LPJ hdl fucntion prototypes***********/
EXTERN S16 pjAcHdlLpjDirective ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 pjAcHdlLpjGenCfgReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjSapCfgReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjTrcCntrlReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjUStaCntrlReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjDbgCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjSapCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjStsReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjStaReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjCfgCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjCntrlCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjStsCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjStaCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjStaInd ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjTrcInd ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjSDCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 pjAcHdlLpjSapCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN  S16 pjAcHdlLpjL2MeasReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 pjAcHdlLpjL2MeasCfm ARGS((
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
));
#endif /* LTE_L2_MEAS */
/**** LPJ utl fucntion prototypes***********/
EXTERN Void pjAcUtlPjBuildGenCfgReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN Void pjAcUtlPjBuildSapCfgReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN Void pjAcUtlPjBuildTrcCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN Void pjAcUtlPjBuildDbgCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN Void pjAcUtlPjBuildSapCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));

EXTERN S16 pjAcUtlLpjFreeCb ARGS ((
CmXtaMsgQElm *qElm
));

EXTERN Void pjAcUtlPjBuildSDCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *kwMngmt
));
EXTERN S16 pjAcUtlPjVerifyStaCfm ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjSSta        *sta
));

EXTERN S16 pjAcUtlPjVerifyStaInd ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjUSta        *usta
));

EXTERN S16 pjAcUtlPjVerifyTrcInd ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjTrc         *trc
));

EXTERN S16 pjAcUtlPjVerifyStsCfm ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjSts         *sts
));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN Void pjAcUtlLpjBuildL2MeasReq  ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PjL2MeasReqEvt *l2MeasReqEvt
));
EXTERN S16 pjAcUtlLpjVldtL2MeasCfm ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PjL2MeasCfmEvt *l2MeasCfmEvt
));
#endif /* LTE_L2_MEAS */
EXTERN CmXtaTCCb*  pjAcLpjTstCbFind ARGS (( Void ));

EXTERN S16 SmMiLpjSendMsg ARGS ((
Pst         *pst,
PjMngmt     *cfm,
Buffer      *mBuf
));

#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif /* KW_PDCP */
#endif   /* __PJAC_LPJ_X__ */

/********************************************************************30**
         End of file:     pjac_lpj.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:00 2015
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
/main/1      ---      av     1. LTE PDCP Initial Release 2.1.
*********************************************************************91*/
