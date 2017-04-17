
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc structures and function prototypes

     File:    szac_lhi.x

     Sid:      szac_lhi.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:42 2013

     Prg:     mn
*********************************************************************21*/

#ifndef __SZ_LHI_X__
#define __SZ_LHI_X__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 szAcLhiInit ARGS((
Void
));

EXTERN S16 szAcLhiDeInit ARGS((
Void
));

/*** start of lhi handle functions***/
EXTERN S16 szAcHdlHiGenCfgReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiTSapCfgReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiCtxtCfgReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiCfgCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiUstaCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiTrcCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiDbgCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiShutDownCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiTsapCntrlReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiCntrlCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiTrcInd ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiStaInd ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiSysStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiTsapStaReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiStaCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiGenStsReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiTsapStsReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 szAcHdlHiStsCfm ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

/*** End of lhi handle funstions****/

/*** start of lhi utl functions***/
EXTERN S16 szAcUtlLhiSendMsg ARGS((
Pst         *pst,
HiMngmt     *cfm,
Buffer      *mBuf
));

EXTERN S16 szAcUtlLhiCb ARGS((
CmXtaMsgQElm *qElm
));
/*** end of lhi utl functions****/

/* sz003.301: Updted for PSF-S1AP 3.1 release */
EXTERN S16 smHiActvInit ARGS((
Ent       ent,          
Inst      inst,        
Region    region,    
Reason    reason     
)); 

#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __SZ_LHI_X_ */

/********************************************************************30**

         End of file:     szac_lhi.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:42 2013

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
/main/3      ---      vvashishth  1. Updated for S1AP release 3.1
/main/3   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
*********************************************************************91*/
