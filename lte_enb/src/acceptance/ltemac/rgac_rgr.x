

/********************************************************************20**

     Name:    MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source

     File:    rgac_rgr.x

     Sid:      rgac_rgr.x@@/main/3 - Fri Jul 29 10:02:21 2011

     Prg:     nsadar 
*********************************************************************21*/
#ifndef __RGAC_RRGX__
#define __RGAC_RRGX__
#ifdef __cplusplus
extern "C" {
#endif
/* Following section includes the declarations for the handlers and utilitity 
 * functions used by the RRM Layer testing framework. */

   EXTERN S16 rgAcHdlRgrBndReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlRgrBndCfm ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlRgrUbndReq ARGS ((
            CmXtaTCCb    *tcCb,
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlRgrEnbCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlRgrCellCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlRgrUeCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlRgrLchCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlRgrLcgCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb  *spCb
            ));
   EXTERN S16 rgAcHdlRgrCellReCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlRgrUeReCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlRgrLchReCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlRgrLcgReCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb  *spCb
            ));
   EXTERN S16 rgAcHdlRgrDelReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlRgrRstReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
/* Added for sending TTI tick to RRM */
#ifdef RGR_RRM_TICK
   EXTERN S16 rgAcHdlRgrTtiInd ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
#endif
   EXTERN S16 rgAcHdlRgrCfgCfm ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcUtlRgrBuildEnbCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb      *spCb,     /* spCb data structure  */
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN S16 rgAcUtlRgrBuildCellCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb      *spCb,     /* spCb data structure  */
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlRgrBuildUeCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlRgrBuildLchCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlRgrBuildLcgCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb      *spCb,
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlRgrBuildDlSchInfo ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb      *spCb,
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlRgrBuildUlSchInfo ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb      *spCb,
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlRgrBuildDlfsSchInfo ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb      *spCb,
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN S16 rgAcUtlRgrBuildCellReCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlRgrBuildUeReCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlRgrBuildLchReCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlRgrBuildLcgReCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb      *spCb,
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlRgrBuildDelReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN Void rgAcUtlRgrBuildRstReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            RgrCfgReqInfo  *cfgReq
            ));
   EXTERN PUBLIC S16 rgAcUtlFreeRgrCb ARGS ((CmXtaMsgQElm   *qElm));
   EXTERN PUBLIC S16 rgAcRgrSendMsg ARGS ((Pst            *pst,
            SpId           suId,
            U8             reason,
            Void           *ptr
            ));
   EXTERN PUBLIC CmXtaTCCb*  rgAcRgrTstCbFind ARGS ((Void));
   /* Added for SI Enhancement*/
#ifdef RGR_SI_SCH
   EXTERN S16 rgAcHdlRgrSiCfgCfm ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcHdlRgrSiCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcUtlRgrBuildSiCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            RgrSiCfgReqInfo  *cfgReq
            ));

   EXTERN S16 rgAcHdlRgrWarningSiCfgReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));

   EXTERN S16 rgAcUtlRgrBuildWarningSiCfgReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            RgrWarningSiCfgReqInfo  *cfgReq
            ));
   EXTERN S16 rgAcHdlRgrWarningSiCfgCfm ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));

   EXTERN S16 rgAcHdlRgrWarningSiStopReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
#endif
#ifdef RGR_CQI_REPT
   EXTERN S16 rgAcHdlRgrStaInd ARGS((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
#endif
    EXTERN S16 rgAcHdlRgrUeStaInd ARGS((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
/* LTE_ADV_FLAG_REMOVED_START */
   EXTERN S16 rgAcHdlRgrLoadInfInd ARGS((
	   CmXtaTCCb      *tcCb,    /* tcCb data structure  */
           CmXtaSpCb    *spCb     /* spCb data structure  */
           ));
   EXTERN S16 rgAcHdlRgrLoadInfReq ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   EXTERN S16 rgAcUtlRgrBuildLoadInfReq ARGS ((
            CmXtaTCCb      *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb,     /* spCb data structure  */
            RgrLoadInfReqInfo  *loadInfReq
            ));

#ifdef LTE_ADV
EXTERN S16 rgAcHdlRgrSCellActDeactReq ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));
#endif
/* LTE_ADV_FLAG_REMOVED_END */
EXTERN PUBLIC S32 rgSCHUtlGetAllwdCchTbSz ARGS((U32 bo, U8 *nPrb, U8 *mcs));
   
EXTERN S16 rgAcDcfiStubExec ARGS ((
            CmXtaTCCb    *tcCb,    /* tcCb data structure  */
            CmXtaSpCb    *spCb     /* spCb data structure  */
            ));
   
#ifdef __cplusplus
}
#endif
#endif /* __RGAC_ACCX__ */
/********************************************************************30**

         End of file:     rgac_rgr.x@@/main/3 - Fri Jul 29 10:02:21 2011

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
             rg001.201 sm 1. Added TTI indication to RGR User.
             rg004.201 rnt 1.Modified for SI Enhancement
             rg009.201 asehgal 1.Removed compiler warning.
/main/3      ---     dvasisht  1. Updated for LTE MAC Release 3.1          
$SID$        ---      rt       1. LTE MAC 4.1 release
*********************************************************************91*/
