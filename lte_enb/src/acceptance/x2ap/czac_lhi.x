
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc structures and function prototypes

     File:    czac_lhi.x

     Sid:      czac_lhi.x@@/main/2 - Tue Aug 30 18:35:50 2011

     Prg:     sy
*********************************************************************21*/

#ifndef __CZ_LHI_X__
#define __CZ_LHI_X__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 czAcLhiInit ARGS((
Void
));

EXTERN S16 czAcLhiDeInit ARGS((
Void
));

/*** start of lhi handle functions***/
EXTERN S16 czAcHdlHiGenCfgReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiTSapCfgReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiCtxtCfgReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiCfgCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiUstaCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiTrcCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiDbgCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiShutDownCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiTsapCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiCntrlCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiTrcInd ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiStaInd ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiSysStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiTsapStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiStaCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiGenStsReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiTsapStsReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 czAcHdlHiStsCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

/*** End of lhi handle funstions****/

#ifdef HI

/*** start of lhi utl functions***/
EXTERN S16 czAcUtlLhiSendMsg ARGS((
Pst         *pst,
HiMngmt     *cfm,
Buffer      *mBuf
));

#endif

EXTERN S16 czAcUtlLhiCb ARGS((
CmXtaMsgQElm *qElm
));
/*** end of lhi utl functions****/



#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __CZ_LHI_X_ */

/********************************************************************30**

         End of file:     czac_lhi.x@@/main/2 - Tue Aug 30 18:35:50 2011

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
/main/2      ---      pt       1. LTE-X2AP 3.1 release.
*********************************************************************91*/
