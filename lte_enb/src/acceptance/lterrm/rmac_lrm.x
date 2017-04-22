

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     

     Desc:     This file contains the acc source
               

     File:     wrac_rmu.x

     Sid:      rmac_lrm.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:25 2013

     Prg:       

*********************************************************************21*/
#ifndef __WRACRMUX__
#define __WRACRMUX__


#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 rmAcUtlLrmFreeCb ARGS ((CmXtaMsgQElm   *qElm));
EXTERN CmXtaTCCb*  rmAcLrmTstCbFind ARGS((Void));

EXTERN S16 rmAcHdlLrmCpuLoadInd 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmGenCfgReq 		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmGenCfgCfm 		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmSapCfgReq 		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmSapCfgCfm 		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmSapCfgReqRgm ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmCellCfgCfm 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmCellCfgReq		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmEnbCfgReq		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmEnbCfgCfm		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmCfgCfm		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmCtrlReq     ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmCtrlCfm     ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlLrmCellUpInd ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));

EXTERN S16 rmAcLrmInit ARGS((Void));
EXTERN S16 rmAcLrmDeInit ARGS((Void));

#ifdef __cplusplus
}
#endif   /* __cplusplus */

#endif /* __WRACRMUX__ */
