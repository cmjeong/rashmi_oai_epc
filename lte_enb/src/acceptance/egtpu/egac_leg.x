
/********************************************************************20**

     Name:     eGTP Layer

     Type:     C source file

     Desc:     C Source code for Upper Interface procedures

     File:     egac_leg.x

     Sid:      egac_leg.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:36 2015

     Prg:      an

*********************************************************************21*/

#ifndef __EG_LEG_X__
#define __EG_LEG_X__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 egAcLegInit ARGS((Void));
EXTERN S16 egAcLegDeInit ARGS((Void));

EXTERN S16 egAcHdlGenCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));

EXTERN S16 egAcHdlUSapCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlLSapCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlTServerCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlCfgCfm ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlStsReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlStsCfm ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlStaReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlStaCfm ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlStaInd ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlTrcInd ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlGenCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlUSapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlLSapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlTServerCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlLSapTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlDebugCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlUstaCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
/*-- eg003.201 : changes from eg009.102: Prototype for egAcHdlCfgCntrlReq --*/
EXTERN S16 egAcHdlCfgCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /*-- tcCb data structure  --*/
               CmXtaSpCb  *spCb));

EXTERN S16 egAcHdlTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlCntrlCfm ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 egAcHdlShutDownCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));

#ifdef EGTP_U
EXTERN S16 egUAcHdlUSapCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));

EXTERN S16 egUAcHdlIPAddrCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));

EXTERN S16 egUAcHdlIPAddrCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
#endif

#ifdef EGTP_U_MULTI_THREADED
PUBLIC Void displayThreadStsInfo ARGS
((
   EgThrdSts thrdSts
));
#endif



EXTERN Void egAcUtlBuildGenCfgReq ARGS
            (( CmXtaTCCb      *tcCb,    /* tcCb data structure  */
               CmXtaSpCb      *spCb,
               EgMngmt     *egMngmt));
EXTERN Void egAcUtlBuildLSapCfgReq ARGS
            (( CmXtaTCCb  *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb,
               EgMngmt    *egMngmt));
EXTERN Void egAcUtlBuildUSapCfgReq  ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb,
               EgMngmt    *egMngmt)); 
EXTERN Void egAcUtlBuildTServerCfgReq ARGS
            (( CmXtaTCCb     *tcCb,    /* tcCb data structure  */
               CmXtaSpCb     *spCb,   
               EgMngmt    *egMngmt));
EXTERN Void egAcUtlBuildGenCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               EgMngmt   *egMngmt));  
EXTERN Void egAcUtlBuildUSapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               EgMngmt   *egMngmt));  
EXTERN Void egAcUtlBuildLSapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               EgMngmt   *egMngmt));
EXTERN Void egAcUtlBuildTServerCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               EgMngmt   *egMngmt));
EXTERN Void egAcUtlBuildTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               EgMngmt   *egMngmt));
EXTERN Void egAcUtlBuildLSapTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               EgMngmt   *egMngmt));
EXTERN Void egAcUtlBuildUstaCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               EgMngmt   *egMngmt));
EXTERN Void egAcUtlBuildDebugCntrlReq ARGS
            (( CmXtaTCCb     *tcCb,    /* tcCb data structure  */
               CmXtaSpCb     *spCb,
               EgMngmt    *egMngmt));
/*eg004.201 Added for eGTPC PSF Shutdown*/
#ifdef HW
EXTERN Void egAcUtlBuildShutdownCntrlReq ARGS
            (( EgMngmt     *egMngmt, U16 MemRelflag));
#else
EXTERN Void egAcUtlBuildShutdownCntrlReq ARGS
            (( EgMngmt     *egMngmt));
#endif
#ifdef EGTP_U
EXTERN Void egUAcUtlBuildUSapCfgReq  ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb,
               EgMngmt    *egMngmt)); 

EXTERN S16 egUAcUtlBuildIPAddrCfgReq ARGS
            (( CmXtaTCCb     *tcCb,    /* tcCb data structure  */
               CmXtaSpCb     *spCb,   
               EgMngmt    *egMngmt));

EXTERN Void egUAcUtlBuildIPAddrCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               EgMngmt   *egMngmt));
#endif


EXTERN S16 SmMiLegSendMsg ARGS((
Pst         *pst,
EgMngmt     *cfm,
Buffer      *mBuf
));

EXTERN CmXtaTCCb*  egAcLegTstCbFind ARGS((
Void
));


EXTERN S16 egAcUtlLegCb ARGS((
CmXtaMsgQElm *qElm
));


#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __EG_LEG_X_ */

/**********************************************************************

         End of file:     egac_leg.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:36 2015

**********************************************************************/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3     eg003.201 psingh      1. eg009.102: Prototype for egAcHdlCfgCntrlReq
/main/3     eg004.201 magnihotri  1. Added for eGTPC PSF Shutdown
*********************************************************************91*/
