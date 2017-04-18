

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     

     Desc:     This file contains the acc source
               

     File:     rmac_rgm.x

     Sid:      rmac_rgm.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:27 2013

     Prg:       

*********************************************************************21*/
#ifndef __WRACRGMX__
#define __WRACRGMX__


#ifdef __cplusplus
extern "C" {
#endif
#ifdef RRM_UNUSED_FUNC
EXTERN S16 rmAcUtlRgmFreeCb ARGS ((CmXtaMsgQElm   *qElm));
EXTERN CmXtaTCCb*  rmAcRgmTstCbFind ARGS((Void));


EXTERN S16 rmAcHdlRgmPrbRprtInd ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRgmBndReq ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRgmBndCfm ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRgmPrbRprtCfg ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));

EXTERN S16 rmAcRgmInit ARGS((Void));
EXTERN S16 rmAcRgmDeInit ARGS((Void));
#endif
#ifdef __cplusplus
}
#endif   /* __cplusplus */

#endif /* __WRACRGMX__ */
