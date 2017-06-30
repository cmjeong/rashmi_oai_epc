

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     

     Desc:     This file contains the acc source
               

     File:     wrac_rmu.x

     Sid:      rmac_rmu.x@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/1 - Wed Apr  3 15:41:28 2013

     Prg:       

*********************************************************************21*/
#ifndef __WRACRMUX__
#define __WRACRMUX__


#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 rmAcUtlRmuFreeCb ARGS ((CmXtaMsgQElm   *qElm));
EXTERN CmXtaTCCb*  rmAcRmuTstCbFind ARGS((Void));


EXTERN S16 rmAcHdlRmuMmeOvldStartInd 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuMmeOvldStopInd	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeAdmitReq		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeAdmitRsp 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeRelReq		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeRelRsp		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeRecfgReq		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeIcsReq		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeErabRecfgReq	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeCapRecfgReq	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeCrntiRecfgReq	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeScellRecfgReq ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeRecfgRsp		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuCellReconfigInd ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuFsmStatusInd ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeHoReq	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeHoRsp		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuUeRelInd  ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 rmAcHdlRmuSpsDisInd  ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));

EXTERN S16 rmAcHdlRmuBndReq(CmXtaTCCb    *tcCb, CmXtaSpCb    *spCb );
EXTERN S16 rmAcHdlRmuBndCfm(CmXtaTCCb    *tcCb, CmXtaSpCb    *spCb );

EXTERN S16 rmAcRmuInit ARGS((Void));
EXTERN S16 rmAcRmuDeInit ARGS((Void));

#ifdef __cplusplus
}
#endif   /* __cplusplus */

#endif /* __WRACRMUX__ */
