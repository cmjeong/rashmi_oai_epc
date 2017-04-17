
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc structures and 
              function prototypes

     File:    czac_lsb.x

     Sid:      czac_lsb.x@@/main/tenb_main_ccb/1 - Wed Jul 22 20:08:29 2015

     Prg:     sy 
*********************************************************************21*/

#ifndef __CZ_LSB_X__
#define __CZ_LSB_X__

#ifdef __cplusplus
extern "C" {
#endif


EXTERN S16 czAcLsbInit ARGS((
Void
));

EXTERN S16 czAcLsbDeInit ARGS((
Void
));

/***** start of hdl function prototypes**************/
EXTERN S16 czAcHdlSbGenCfgReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbTSapCfgReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbSctSapCfgReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbCfgCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbUstaCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbTrcCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbTSapCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbSctSapCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbDebugCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbShutDownCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbCntrlCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbGenStsReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbSctSapStsReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbTSapStsReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbStsCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbSysStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbSctSapStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbTSapStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbGenStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbAssocStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbDtaStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbStaCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbStaInd ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlSbTrcInd ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
/*end of handle functions*/

#ifdef SB

/*start of utility functions*/
EXTERN S16 czAcUtlLsbBldSctSapCfg ARGS((
CmXtaTCCb     *tcCb,   /* tcCb data structure  */
CmXtaSpCb     *spCb,
SpId       spId,
SbMgmt     *cfg     /* Configuration structure */
));

EXTERN S16 czAcUtlLsbBldTSapCfg ARGS((
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb   *spCb,
SuId       suId,
SpId       spId,
SbMgmt     *cfg     /* Configuration structure */
));

EXTERN S16 czAcUtlLsbBldGenCfg ARGS((
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb   *spCb,
SbMgmt     *cfg      /* Configuration structure */
));

EXTERN S16 czAcUtlLsbCb ARGS((
CmXtaMsgQElm *qElm
));

/*end of utility function*/

EXTERN S16 czAcUtlLsbSendMsg ARGS((
Pst         *pst,
SbMgmt     *cfg,
Buffer     *mBuf
));
/*end of call back functions*/

#endif


#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __CZ_LSB_X__ */

/********************************************************************30**

         End of file:     czac_lsb.x@@/main/tenb_main_ccb/1 - Wed Jul 22 20:08:29 2015

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
/main/1      ---      sy       1. LTE-X2AP Initial Release.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
