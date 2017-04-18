
/********************************************************************20**

     Name:    MAC - acc test file

     Type:    C Source file

     Desc:    This file contains the acc source

     File:    rgac_rgm.x

     Sid:      rgac_rgm.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Fri Jul 19 13:47:32 2013

     Prg:     nsadar 
*********************************************************************21*/
#ifndef __RGAC_RGMX__
#define __RGAC_RGMX__
#ifdef __cplusplus
extern "C" {
#endif
/* Following section includes the declarations for the handlers and utilitity 
 * functions used by the RRM Layer testing framework. */

EXTERN S16 rgAcHdlRgmBndReq ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 rgAcHdlRgmBndCfm ARGS ((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 rgAcHdlRgmUbndReq ARGS ((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb     /* spCb data structure  */
));

EXTERN S16 rgAcHdlCfgPrdRprt ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 rgAcHdlCfgPrdRprtInd ARGS((
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
));

EXTERN S16 rgAcRgmSendMsg ARGS ((
Pst            *pst,
SpId           suId,
U8             reason,
Void           *ptr
));


EXTERN S16 rgAcUtlFreeRgmCb ARGS ((
CmXtaMsgQElm   *qElm
));

EXTERN CmXtaTCCb*  rgAcRgmTstCbFind ARGS ((Void));
EXTERN S16  rgAcRgmInit ARGS ((Void));
EXTERN S16  rgAcRgmDeInit ARGS ((Void));

#ifdef __cplusplus
}
#endif
#endif /* __RGAC_ACCX__ */
/********************************************************************30**

         End of file:     rgac_rgm.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Fri Jul 19 13:47:32 2013

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
*********************************************************************91*/
