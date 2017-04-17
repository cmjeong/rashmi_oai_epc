

/********************************************************************20**

     Name:    MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source

     File:    rgac_crg.x

     Sid:      rgac_crg.x@@/main/3 - Sat Jul 30 02:20:54 2011

     Prg:     ns 
*********************************************************************21*/
#ifndef __RGAC_CRGX__
#define __RGAC_CRGX__
#ifdef __cplusplus
extern "C" {
#endif
/* Following section includes the declarations for the handlers and utilitity 
 * functions used by the Dummy CRG testing framework. */

   EXTERN S16 rgAcHdlCrgBndReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlCrgBndCfm ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlCrgUbndReq ARGS ((
            CmXtaTCCb    *tcCb,
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlCrgCellCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlCrgUeCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlCrgLchCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlCrgCellReCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlCrgUeReCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlCrgLchReCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlCrgDelReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlCrgRstReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlCrgCfgCfm ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN Void rgAcUtlCrgBuildCellCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            CrgCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlCrgBuildUeCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            CrgCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlCrgBuildLchCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            CrgCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlCrgBuildCellReCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            CrgCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlCrgBuildUeReCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            CrgCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlCrgBuildLchReCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            CrgCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlCrgBuildDelReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            CrgCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlCrgBuildRstReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            CrgCfgReqInfo  *cfgReq
            ));
   EXTERN PUBLIC S16 rgAcUtlFreeCrgCb ARGS ((CmXtaMsgQElm   *qElm));
   EXTERN PUBLIC S16 rgAcCrgSendMsg ARGS ((Pst *pst,SpId suId,U8 reason,Void
            *ptr));
   EXTERN PUBLIC CmXtaTCCb*  rgAcCrgTstCbFind ARGS ((Void));





#ifdef __cplusplus
}
#endif
#endif /* __RGAC_ACCX__ */
/********************************************************************30**

         End of file:     rgac_crg.x@@/main/3 - Sat Jul 30 02:20:54 2011

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
/main/1      ---     ns  1. Initial Release.
/main/2      ---     ns  1. LTE MAC 2.1 release
/main/3      ---   asehgal 1. Updated for LTE MAC Release 3.1
$SID$        ---     rt    1. LTE MAC 4.1 release
*********************************************************************91*/
