

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     

     Desc:     This file contains the acc source
               

     File:     nlac_lnl.x

     Sid:      nlac_lnl.x@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 18:02:56 2014

     Prg:      subhamay 

*********************************************************************21*/
#ifndef __NLACLNLX__
#define __NLACLNLX__


#ifdef __cplusplus
extern "C" {
#endif

EXTERN S16 nlAcUtlLnlFreeCb ARGS ((CmXtaMsgQElm   *qElm));
EXTERN CmXtaTCCb*  nlAcLnlTstCbFind ARGS((Void));

EXTERN S16 nlAcHdlLnlGenCfgReq 		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlGenCfgCfm 		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlNluSapCfgReq 		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlNluSapCfgCfm 		ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlNluSapCfgFail 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlCellCfgReq 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlCellCfgCfm 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlCellCfgFail 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlCellReCfgReq 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlCellReCfgCfm 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlCellReCfgFail 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlNghCellCfgReq 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlNghCellCfgCfm 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlNghCellCfgFail 	ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlShutdownReq        ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlShutdownCfm        ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlCfgUpdateInd       ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));
EXTERN S16 nlAcHdlLnlStatusInd          ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb));

EXTERN S16 nlAcLnlInit ARGS((Void));
EXTERN S16 nlAcLnlDeInit ARGS((Void));

#ifdef __cplusplus
}
#endif   /* __cplusplus */

#endif /* __NLACLNLX__ */
