

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     

     Desc:     This file contains the acc source
               

     File:     nlac_nlu.x

     Sid:      nlac_nlu.x@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:04:18 2014

     Prg:      subhamay 

*********************************************************************21*/
#ifndef __NLACNLUX__
#define __NLACNLUX__


#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 nlAcUtlNluFreeCb ARGS ((
CmXtaMsgQElm   *qElm
));

EXTERN CmXtaTCCb*  nlAcNluTstCbFind ARGS((
Void
));

EXTERN S16 nlAcHdlNluBndReq ARGS ((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb
));

EXTERN S16 nlAcHdlNluBndCfm ARGS ((
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb
));

EXTERN S16 nlAcHdlNluNghReq ARGS((
CmXtaTCCb *tcCb, 
CmXtaSpCb *spCb
));

EXTERN S16 nlAcHdlNluPciModIndCfm ARGS((
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
));


EXTERN S16 nlAcNluInit ARGS((
Void
));

EXTERN S16 nlAcNluDeInit ARGS((
Void
));

#ifdef __cplusplus
}
#endif   /* __cplusplus */

#endif /* __NLACNLUX__ */
