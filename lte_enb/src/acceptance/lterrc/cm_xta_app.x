
/********************************************************************20**

     Name:    LTE-RRC - acc test file

     Type:    C Include file

     Desc:    This file contains the acc structures and 
              function prototypes

     File:    cm_xta_app.x

     Sid:      cm_xta_app.x@@/main/tenb_main_ccb/1 - Wed Jul 22 20:18:05 2015

     Prg:     mraj 

*********************************************************************21*/
#ifndef __CM_XTA_APP_X__
#define __CM_XTA_APP_X__

#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 cmXtaAppLoadFindnCreate ARGS((
                     Void  *msg,
                     Bool  *newCall,
                     CmXtaLoadCb  **loadCb));

EXTERN S16 cmXtaAppLoadFreeMsg ARGS(( Void     *loadMsg));
EXTERN S16 cmXtaAppLoadDelete ARGS((
                     CmXtaLoadCb  *loadCb,
                     Bool      fail));
EXTERN S16 cmXtaAppLoadInit ARGS((Void));
EXTERN S16 cmXtaAppLoadGetCurStep ARGS((
                     Void  *loadMsg,
                     CmXtaLoadCb  *loadCb,
                     U16   *curLoadIndx,
                     U16   *retransLoadIndx));
EXTERN S16 cmXtaAppLoadEngine ARGS((
                     CmXtaLoadCb    *loadCb,
                     Void        *loadMsg,
                     Bool        retransMode,
                     U16         curLoadIndx,
                     U16         retransLoadIndx));
EXTERN S16 cmXtaAppTst ARGS(( Void));
EXTERN S16 cmXtaAppInit ARGS(( Void));
EXTERN S16 cmXtaAppDeInit ARGS(( Void));
EXTERN S16 cmXtaAppParseCmdLine ARGS(( Void));
EXTERN Void cmXtaAppUsage ARGS(( Void));
EXTERN S16 cmXtaAppTCCreate ARGS(( CmXtaTCCb         *tcCb));
EXTERN S16  cmXtaAppTCDelete ARGS(( CmXtaTCCb         *tcCb));
EXTERN S16 cmXtaAppInitQ ARGS(( CmXtaMsgQ *msgQ));
EXTERN Void cmXtaAppFlushQ ARGS(( CmXtaMsgQ *msgQ));
EXTERN S16 cmXtaAppPyInit ARGS(( Void));
EXTERN S16 cmXtaAppPyDeInit ARGS(( Void));

#ifdef __cplusplus
}
#endif
#endif /* __CM_XTA_APP_X__ */
/********************************************************************30**

         End of file:     cm_xta_app.x@@/main/tenb_main_ccb/1 - Wed Jul 22 20:18:05 2015

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

ver       pat     init            description
------------ -------- ---- ----------------------------------------------
/main/1      ---     rer        1. LTE RRC Initial Release.
/main/2      ---     ch      1. RRC Release 2.1.
*********************************************************************91*/
