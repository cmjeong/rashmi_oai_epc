

/**********************************************************************
 
    Name:   LTE PDCP layer
 
    Type:   C include file
 
    Desc:   Defines required by LPK interface of XTA LTE PDCP
 
    File:   pjac_lpk.x
 
    Sid:      pjac_lpk.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:03 2015
 
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


#ifndef __PJAC_LPK_X__
#define __PJAC_LPK_X__

#ifdef KW_PDCP
#ifdef __cplusplus
extern "C" {
#endif


/**** LPK reg fucntion prototypes***********/


/**** LPK hdl fucntion prototypes***********/
EXTERN S16 kwAcHdlLpkDirective ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 kwAcHdlLpkGenCfgReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkSapCfgReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkTrcCntrlReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkUStaCntrlReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkDbgCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkSapCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkStsReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkStaReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkCfgCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkCntrlCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkStsCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkStaCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkStaInd ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkTrcInd ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkSDCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

/* Venki */

EXTERN S16 kwAcHdlLpkSapCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN  S16 kwAcHdlLpkL2MeasReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 kwAcHdlLpkL2MeasCfm ARGS((
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
));
#endif /* LTE_L2_MEAS */
/**** LPK utl fucntion prototypes***********/
EXTERN Void kwAcUtlPkBuildGenCfgReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *kwMngmt
));

EXTERN Void kwAcUtlPkBuildSapCfgReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *kwMngmt
));

EXTERN Void kwAcUtlPkBuildTrcCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *kwMngmt
));

EXTERN Void kwAcUtlPkBuildDbgCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *kwMngmt
));

EXTERN Void kwAcUtlPkBuildSapCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *kwMngmt
));

EXTERN S16 kwAcUtlLpkFreeCb ARGS ((
CmXtaMsgQElm *qElm
));

EXTERN Void kwAcUtlPkBuildSDCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *kwMngmt
));
EXTERN S16 kwAcUtlPkVerifyStaCfm ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PkSSta        *sta
));

EXTERN S16 kwAcUtlPkVerifyStaInd ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PkUSta        *usta
));

EXTERN S16 kwAcUtlPkVerifyTrcInd ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PkTrc         *trc
));

EXTERN S16 kwAcUtlPkVerifyStsCfm ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PkSts         *sts
));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN Void kwAcUtlLpkBuildL2MeasReq  ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PkL2MeasReqEvt *l2MeasReqEvt
));
EXTERN S16 kwAcUtlLpkVldtL2MeasCfm ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PkL2MeasCfmEvt *l2MeasCfmEvt
));
#endif /* LTE_L2_MEAS */
EXTERN CmXtaTCCb*  kwAcLpkTstCbFind ARGS (( Void ));

EXTERN S16 SmMiLpkSendMsg ARGS ((
Pst         *pst,
PkMngmt     *cfm,
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


/**** LPK reg fucntion prototypes***********/


/**** LPK hdl fucntion prototypes***********/
EXTERN S16 kwAcHdlLpkDirective ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
EXTERN S16 kwAcHdlLpkGenCfgReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkSapCfgReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkTrcCntrlReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkUStaCntrlReq  ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkDbgCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkSapCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkStsReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkStaReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkCfgCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkCntrlCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkStsCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkStaCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkStaInd ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkTrcInd ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 kwAcHdlLpkSDCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

/* Venki */

EXTERN S16 kwAcHdlLpkSapCntrlReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN  S16 kwAcHdlLpkL2MeasReq ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));
EXTERN S16 kwAcHdlLpkL2MeasCfm ARGS((
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
));
#endif /* LTE_L2_MEAS */
/**** LPK utl fucntion prototypes***********/
EXTERN Void kwAcUtlPkBuildGenCfgReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *kwMngmt
));

EXTERN Void kwAcUtlPkBuildSapCfgReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *kwMngmt
));

EXTERN Void kwAcUtlPkBuildTrcCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *kwMngmt
));

EXTERN Void kwAcUtlPkBuildDbgCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *kwMngmt
));

EXTERN Void kwAcUtlPkBuildSapCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *kwMngmt
));

EXTERN S16 kwAcUtlLpkFreeCb ARGS ((
CmXtaMsgQElm *qElm
));

EXTERN Void kwAcUtlPkBuildSDCntrlReq ARGS ((
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *kwMngmt
));
EXTERN S16 kwAcUtlPkVerifyStaCfm ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PkSSta        *sta
));

EXTERN S16 kwAcUtlPkVerifyStaInd ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PkUSta        *usta
));

EXTERN S16 kwAcUtlPkVerifyTrcInd ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PkTrc         *trc
));

EXTERN S16 kwAcUtlPkVerifyStsCfm ARGS ((
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PkSts         *sts
));
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
EXTERN Void kwAcUtlLpkBuildL2MeasReq  ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PkL2MeasReqEvt *l2MeasReqEvt
));
EXTERN S16 kwAcUtlLpkVldtL2MeasCfm ARGS((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PkL2MeasCfmEvt *l2MeasCfmEvt
));
#endif /* LTE_L2_MEAS */
EXTERN CmXtaTCCb*  kwAcLpkTstCbFind ARGS (( Void ));

EXTERN S16 SmMiLpkSendMsg ARGS ((
Pst         *pst,
PkMngmt     *cfm,
Buffer      *mBuf
));

#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif /* KW_PDCP */
#endif   /* __PJAC_LPK_X__ */

/********************************************************************30**
         End of file:     pjac_lpk.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:03 2015
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
/main/1      ---       vb     1. LTE PDCP Initial Release 2.1.
*********************************************************************91*/
