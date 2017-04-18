
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc structures and 
              function prototypes

     File:    szac_lsb.x

     Sid:      szac_lsb.x@@/main/3 - Mon Jan 10 22:15:47 2011

     Prg:     pk 
*********************************************************************21*/

#ifndef __SZ_LSB_X__
#define __SZ_LSB_X__

#ifdef __cplusplus
extern "C" {
#endif


EXTERN S16 szAcLsbInit ARGS((
Void
));

EXTERN S16 szAcLsbDeInit ARGS((
Void
));

/***** start of hdl function prototypes**************/
EXTERN S16 szAcHdlSbGenCfgReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbTSapCfgReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbSctSapCfgReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbCfgCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbUstaCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbTrcCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbTSapCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbSctSapCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbDebugCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbShutDownCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbCntrlCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbGenStsReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbSctSapStsReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbTSapStsReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbStsCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbSysStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbSctSapStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbTSapStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbGenStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbAssocStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbDtaStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbStaCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbStaInd ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlSbTrcInd ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));
/*end of handle functions*/

/*start of utility functions*/
EXTERN S16 szAcUtlLsbBldSctSapCfg ARGS((
CmXtaTCCb     *tcCb,   /* tcCb data structure  */
CmXtaSpCb     *spCb,
SpId       spId,
SbMgmt     *cfg     /* Configuration structure */
));

EXTERN S16 szAcUtlLsbBldTSapCfg ARGS((
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb   *spCb,
SuId       suId,
SpId       spId,
SbMgmt     *cfg     /* Configuration structure */
));

EXTERN S16 szAcUtlLsbBldGenCfg ARGS((
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb   *spCb,
SbMgmt     *cfg      /* Configuration structure */
));

EXTERN S16 szAcUtlLsbCb ARGS((
CmXtaMsgQElm *qElm
));

/*end of utility function*/

EXTERN S16 szAcUtlLsbSendMsg ARGS((
Pst         *pst,
SbMgmt     *cfg,
Buffer     *mBuf
));
/*end of call back functions*/

/* sz003.301: Updted for PSF-S1AP 3.1 release */
EXTERN S16 smSbActvInit ARGS((
Ent ent, 
Inst inst, 
Region region,
Reason reason
));


#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __SZ_LSB_X__ */

/********************************************************************30**

         End of file:     szac_lsb.x@@/main/3 - Mon Jan 10 22:15:47 2011

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
/main/3   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
*********************************************************************91*/
