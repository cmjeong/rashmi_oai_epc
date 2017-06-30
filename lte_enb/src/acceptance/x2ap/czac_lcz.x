
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc structures and 
              function prototypes

     File:    czac_lcz.x

     Sid:      czac_lcz.x@@/main/2 - Tue Aug 30 18:35:48 2011

     Prg:     pk 
*********************************************************************21*/

#ifndef __CZ_LCZ_X__
#define __CZ_LCZ_X__

#ifdef __cplusplus
extern "C" {
#endif
typedef struct _eNodeBProfile
{
   CzProtCfg     protCfg;
   CzPeerCfg     peerCfg;
}eNodeBProfile;

EXTERN eNodeBProfile czENodeB[CZ_MAX_ENODEB];
EXTERN CzProtCfg     czProtProf[10];
EXTERN CzPeerCfg    czPeerProf[10];

EXTERN S16 czAcLczInit ARGS((
Void
));

EXTERN S16 czAcLczDeInit ARGS((
Void
));

EXTERN S16 SmMiLczSendMsg ARGS((
Pst         *pst,
CzMngmt     *cfm,
Buffer      *mBuf
));

/**** Lcz Handle function prototype starts here *********************/
EXTERN S16 czAcHdlGenCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structur                   */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlUSapCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlLSapCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlProtCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlPeerCfgReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlCfgCfm ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlStsReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlStsCfm ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlStaReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlStaCfm ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlStaInd ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlTrcInd ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlUSapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlLSapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlLSapTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlPNodeTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlDebugCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlPeerCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlUstaCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlxrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlAssocCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlEndPtCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlENbMapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlAuditCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlCntrlCfm ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlShutDownCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));
EXTERN S16 czAcHdlSctDelay ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));

EXTERN S16 czAcHdlTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb));

/*****  End of Lcz handle prototypes**********************************/

/*** Lcz utility function prototypes starts here ********************/

EXTERN Void czAcUtlBuildGenCfgReq ARGS
            (( CmXtaTCCb      *tcCb,    /* tcCb data structure  */
               CmXtaSpCb      *spCb,
               CzMngmt     *czMngmt));
EXTERN Void czAcUtlBuildLSapCfgReq ARGS
            (( CmXtaTCCb  *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb,
               CzMngmt    *czMngmt));
EXTERN Void czAcUtlBuildUSapCfgReq  ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb  *spCb,
               CzMngmt    *czMngmt));
EXTERN Void czAcUtlBuildProtCfgReq ARGS
            (( CmXtaTCCb     *tcCb,    /* tcCb data structure  */
               CmXtaSpCb     *spCb,
               CzMngmt    *czMngmt));
EXTERN Void czAcUtlBuildPeerCfgReq ARGS
            (( CmXtaTCCb     *tcCb,    /* tcCb data structure  */
               CmXtaSpCb     *spCb,
               CzMngmt    *czMngmt));
EXTERN Void czAcUtlBuildUSapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               CzMngmt   *czMngmt));
EXTERN Void czAcUtlBuildLSapCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               CzMngmt   *czMngmt));
EXTERN Void czAcUtlBuildLSapTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               CzMngmt   *czMngmt));
EXTERN Void czAcUtlBuildPNodeTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               CzMngmt   *czMngmt));
EXTERN Void czAcUtlBuildTrcCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               CzMngmt   *czMngmt));
EXTERN Void czAcUtlBuildPeerCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               CzMngmt   *czMngmt));
EXTERN Void czAcUtlBuildUstaCntrlReq ARGS
            (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
               CmXtaSpCb    *spCb,
               CzMngmt   *czMngmt));
EXTERN Void czAcUtlBuildDebugCntrlReq ARGS
            (( CmXtaTCCb     *tcCb,    /* tcCb data structure  */
               CmXtaSpCb     *spCb,
               CzMngmt    *czMngmt));
EXTERN Void czAcUtlBuildShutdownCntrlReq ARGS
            (( CzMngmt     *czMngmt));

EXTERN Void  czAcUtlBuildEndPtCntrlReq ARGS
            (( CmXtaTCCb      *tcCb,    /* tcCb data structure  */
               CmXtaSpCb      *spCb,
               CzMngmt     *czMngmt));
EXTERN Void  czAcUtlBuildAssocCntrlReq ARGS
            (( CmXtaTCCb      *tcCb,    /* tcCb data structure  */
               CmXtaSpCb      *spCb,
               CzMngmt     *czMngmt));

/********* End of Lcz utility prototypes*****************/

/*** Lcz utility function prototypes starts here ********/
EXTERN CmXtaTCCb*  czAcLczTstCbFind ARGS
            (( Void));
EXTERN S16 czAcUtlLczCb ARGS
            (( CmXtaMsgQElm *qElm));
/********* End of Lcz utility prototypes*****************/

#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __CZ_LMG_X__ */

/********************************************************************30**

         End of file:     czac_lcz.x@@/main/2 - Tue Aug 30 18:35:48 2011

*********************************************************************31*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---        ds              1. LTE-X2AP Initial Release.
/main/2      ---        pt              1. LTE-X2AP 3.1 release.
*********************************************************************91*/
