
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc structures and 
              function prototypes

     File:    szac_lsz.x

     Sid:      szac_lsz.x@@/main/3 - Mon Jan 10 22:15:50 2011

     Prg:     pk 
*********************************************************************21*/

#ifndef __SZ_LSZ_X__
#define __SZ_LSZ_X__

#ifdef __cplusplus
extern "C" {
#endif


EXTERN S16 szAcLszInit ARGS((
Void
));

EXTERN S16 szAcLszDeInit ARGS((
Void
));

EXTERN S16 SmMiLszSendMsg ARGS((
Pst         *pst,
SzMngmt     *cfm,
Buffer      *mBuf
));

/**** Lsz Handle function prototype starts here *********************/
EXTERN S16 szAcHdlGenCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlUSapCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlLSapCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlProtCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlPeerCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlCfgCfm ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlStsReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlStsCfm ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlStaReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlStaCfm ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlStaInd ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlTrcInd ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlUSapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlLSapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlLSapTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlPNodeTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlDebugCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlPeerCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlUstaCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlENbMapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlAuditCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlCntrlCfm ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlShutDownCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 szAcHdlSctDelay ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));


/***** End of Lsz handle prototypes**********************************/

/*** Lsz utility function prototypes starts here ********************/

EXTERN Void szAcUtlBuildGenCfgReq ARGS
            (( CmXtaTCCb      *tcCb,    /* tcCb data structure  */
               CmXtaSpCb      *spCb,
               SzMngmt     *szMngmt));
EXTERN Void szAcUtlBuildLSapCfgReq ARGS
            (( CmXtaTCCb  *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb,
               SzMngmt    *szMngmt));
EXTERN Void szAcUtlBuildUSapCfgReq  ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb,
               SzMngmt    *szMngmt));
EXTERN Void szAcUtlBuildProtCfgReq ARGS
            (( CmXtaTCCb     *tcCb,    /* tcCb data structure  */
               CmXtaSpCb     *spCb,
               SzMngmt    *szMngmt));
EXTERN Void szAcUtlBuildPeerCfgReq ARGS
            (( CmXtaTCCb     *tcCb,    /* tcCb data structure  */
               CmXtaSpCb     *spCb,
               SzMngmt    *szMngmt));
EXTERN Void szAcUtlBuildUSapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               SzMngmt   *szMngmt));
EXTERN Void szAcUtlBuildLSapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               SzMngmt   *szMngmt));
EXTERN Void szAcUtlBuildLSapTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               SzMngmt   *szMngmt));
EXTERN Void szAcUtlBuildPNodeTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               SzMngmt   *szMngmt));
EXTERN Void szAcUtlBuildTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               SzMngmt   *szMngmt));
EXTERN Void szAcUtlBuildPeerCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               SzMngmt   *szMngmt));
EXTERN Void szAcUtlBuildUstaCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               SzMngmt   *szMngmt));
EXTERN Void szAcUtlBuildDebugCntrlReq ARGS
            (( CmXtaTCCb     *tcCb,    /* tcCb data structure  */
               CmXtaSpCb     *spCb,
               SzMngmt    *szMngmt));
EXTERN Void szAcUtlBuildShutdownCntrlReq ARGS
            (( SzMngmt     *szMngmt));


/********* End of Lsz utility prototypes*****************/

/*** Lsz utility function prototypes starts here ********/
EXTERN CmXtaTCCb*  szAcLszTstCbFind ARGS
            (( Void));
EXTERN S16 szAcUtlLszCb ARGS
            (( CmXtaMsgQElm *qElm));
/********* End of Lsz utility prototypes*****************/

#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __SZ_LMG_X__ */

/********************************************************************30**

         End of file:     szac_lsz.x@@/main/3 - Mon Jan 10 22:15:50 2011

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
/main/3      ---      pkaX  1. Updated for S1AP release 3.1
*********************************************************************91*/
