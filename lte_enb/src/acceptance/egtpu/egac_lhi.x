
/********************************************************************20**

     Name:     eGTP Layer

     Type:     C source file

     Desc:     C Source code for Layer manager Interface for TUCL

     File:     egac_lhi.x

     Sid:      egac_lhi.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:38 2015

     Prg:      an

*********************************************************************21*/

#ifndef __EG_LHI_X__
#define __EG_LHI_X__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 egAcLhiInit ARGS(( Void));
EXTERN S16 egAcLhiDeInit ARGS (( Void));

/******************************************************************************
*              CONFIGURATION REQUEST HANDLER FUNCTIONS
*******************************************************************************/

EXTERN S16 egAcHdlHiGenCfgReq ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                      CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiTSapCfgReq ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                       CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiCtxtCfgReq ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                       CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiCfgCfm ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                   CmXtaSpCb    *spCb));

/******************************************************************************
*              CONTROL REQUEST HANDLER FUNCTIONS
*******************************************************************************/

EXTERN S16 egAcHdlHiUstaCntrlReq ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                         CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiTrcCntrlReq ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                        CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiDbgCntrlReq ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                        CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiShutDownCntrlReq ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                             CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiTsapCntrlReq ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                         CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiCntrlCfm ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                     CmXtaSpCb    *spCb));

/******************************************************************************
*              TRACE AND STATUS HANDLER FUNCTIONS
*******************************************************************************/

EXTERN S16 egAcHdlHiTrcInd ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                   CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiStaInd ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                   CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiSysStaInd ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                      CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiTsapStaReq ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                       CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiStaCfm ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                   CmXtaSpCb    *spCb));

/******************************************************************************
*              STATISTICS HANDLER FUNCTIONS
*******************************************************************************/


EXTERN S16 egAcHdlHiGenStsReq ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                      CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiTsapStsReq ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                       CmXtaSpCb    *spCb));

EXTERN S16 egAcHdlHiStsCfm ARGS (( CmXtaTCCb    *tcCb,    /* tcCb data structure  */
                                   CmXtaSpCb    *spCb));

PUBLIC S16 egAcHdlHiSysStaReq ARGS ((
CmXtaTCCb  *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));


EXTERN S16 egAcUtlLhiCb ARGS (( CmXtaMsgQElm *qElm));


EXTERN S16 egAcSmMiLhiCfgCfm ARGS((  Pst     *pst,          /* post structure */
                                     HiMngmt *cfm));        /* configuration */

EXTERN S16 egAcSmMiLhiStaInd ARGS((  Pst     *pst,          /* post structure */
                                       HiMngmt *usta));        /* Ustatus  */

EXTERN S16 egAcSmMiLhiCntrlCfm ARGS((  Pst     *pst,          /* post structure */
                                       HiMngmt *cfm));        /* configuration */

EXTERN S16 egAcSmMiLhiStaCfm ARGS((  Pst     *pst,          /* post structure */
                                     HiMngmt *cfm));        /* configuration */

EXTERN S16 egAcSmMiLhiTrcInd ARGS((  Pst     *pst,          /* post structure */
                                     HiMngmt *trc,          /* Trace          */                  
                                     Buffer  *mBuf));       /* message buffer */

EXTERN S16 egAcSmMiLhiStsCfm ARGS((  Pst     *pst,          /* post structure */
                                     HiMngmt *sts));        /* configuration */



EXTERN S16 egAcUtlLhiSendMsg ARGS((  Pst     *pst,          /* post structure */
                                     HiMngmt *trc,          /* Trace          */                  
                                     Buffer  *mBuf));       /* message buffer */

/*-- eg003.201 : changes from eg006.102 : Deleted duplicate declaration of egAcUtlLhiCb --*/

#ifdef __cplusplus
}
#endif   /* __cplusplus */
#endif   /* __EG_LHI_X_ */

/**********************************************************************

         End of file:     egac_lhi.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:38 2015

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
/main/2      ---      rss         1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3    eg003.201  psingh      1. Merged code from eg006.102 to Fix
                                     warnings
*********************************************************************91*/
