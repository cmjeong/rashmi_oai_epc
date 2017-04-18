


/********************************************************************20**

Name:     EnodeB Application

Type:     C source file

Desc:     This file contains 


File:     wr_smm_tenb_utils.c

Sid:      fc_smm_enb_utils.c@@/main/tenb_ca_rib_msm/11 - Fri Apr  1 19:40:54 2016

Prg:       

 *********************************************************************21*/
static const char* RLOG_MODULE_NAME="SMM";
static int RLOG_MODULE_ID=2;
static int RLOG_FILE_ID=39;
#include<stdlib.h>
#include "wr.h"
#include "wr_emm.h"
#include "wr_lwr.h"
#include "wr_cmn.h"
#include "wr_smm_smallcell.h"
#include "wr_smm_init.h"
#include "wr_utils.h"
#include "wr_msm_common.h" 
#include "wr_smm_watchdog_tmr.h"
#include "lrm.x"
#include "wr_umm.h"
#include <math.h>
EXTERN MsmLteeNodeBparams lteeNodeBparams[WR_MAX_CELLS];
EXTERN MsmFapParameters   fapParameters;
#ifdef WR_RSYS_OAM
PUBLIC S16  MsmSmmDynCfgReq(Void *cfg, U32 cfgTyp, U16 cellIdx);
EXTERN Void MsmConfigComplete(Void);
EXTERN Void SmUpdateMibParms(U32 msgType, U32 action, Void* Cfg, U16 cellIdx);
EXTERN Void SmUpdateSwVersion(const char *swver);
EXTERN S16  smRegInitTmr ARGS((Void));
EXTERN Bool sendKick;
#endif
PRIVATE Void wrSmmEnbBldSib1Cfg
(
 LwrMngmt *lwrMng,
 U8 cfgGrpIndex, 
 U8 accessMode,
 U8 cellCfgIdx
 );
PRIVATE Void wrSmmEnbBldSib2Cfg(LwrMngmt *lwrMng,U8 cfgGrpIndex,U8 cellCfgIdx);
PRIVATE Void wrSmmEnbBldSib3Cfg(LwrMngmt *lwrMng,U8 cfgGrpIndex,U8 cellCfgIdx);
PRIVATE Void wrSmmEnbSetBwFrmBwIdx(U32 bwIdx);
PRIVATE Void wrSmmEnbIsPciRangeValid
( 
 LwrSib4CsgInfo            *pciRange
 );
PRIVATE void wrSmmEnbBldSib8Cfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex,
 U8       cellCfgIdx 
 );
PRIVATE S16 wrSmmEnbBuildMobParams
(
 LwrCdma2k1xMobParams *mobParams,
 U8 cellCfgIdx
 );
EXTERN S16 wrFillSectorId
(
 TknStrOSXL                  *ptr,
 U8                           len,
 Data                         *val
 );
EXTERN S16 wrSmmEnbValidateIpAddr(Void);
PRIVATE Void wrSmmEnbBldMeasCellCfg(LwrMngmt   *lwrMng,U8 cfgGrpIndex, U8 cellCfgIdx);
PRIVATE Void wrSmmEnbBldRabPolicy(LwrMngmt *lwrMng,U8 cfgGrpIndex,U8 cellCfgIdx);
PRIVATE U16 wrSmmEnbPciRangeMapping
(
 LwrSib4CsgInfo            *pciRange
 );
#ifdef RM_INTF
EXTERN S16 wrSmmEnbBuildRmuProtCellCfg(LrmCellConfiguration *cellCfg , U8 cellCfgIdx);
EXTERN S16 wrSmmEnbBuildRmuProtEnbCfg(LrmEnbConfiguration *enbCfg,U8 cellCfgIdx);
PUBLIC S16 wrSmmEnbBuildRmuProtMmeCfg
(
 U16 mmeId, 
 LrmEnbConfiguration *enbCfg, 
 U32 action
 );
#endif
#ifdef WR_RSYS_OAM
PRIVATE S16 wrSmmEnbInitDbgCfg(Void);
EXTERN S16  smRegInitTmr ARGS((Void));
#ifdef TENB_STATS
EXTERN S16 TSInfInitStatsFrmWork ARGS((
         Bool   tenbSocketStats,
         Bool   tenbFileStats,
         Bool   tenbConsoleStats,
         U32    tenbStatsPeriodicity,
         U32    tendStatsSocketPort
         ));
EXTERN Void TSInfSetEnbIp ARGS((
         U32 enbIpAddr
         ));
#endif
#endif/*WR_RSYS_OAM*/
EXTERN MsmFaultMgmtParams faultMgmtParams;
#ifdef LTE_ADV
PUBLIC S16 wrSmmEnbBuildWrScellCntrl
(
 S32 action
 );             
#endif


/* Populate the SIB periodicites */
/*
 *
 *       Fun:   wrSmmEnbBuildGenCfg
 *
 *       Desc:  fill in cellCfg for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_smm_tenb_utils.c  
 */
#ifdef ANSI
PUBLIC S16 wrSmmEnbBuildGenCfg
(
 LwrMngmt *lwrMng,
 U8       cellCfgIdx 
 )
#else /* if ANSI not defined*/
PUBLIC S16 wrSmmEnbBuildGenCfg(lwrMng,cellCfgIdx)
   LwrMngmt *lwrMng;
   U8       cellCfgIdx; 
#endif /* end of ANSI*/
{
   /*U8 loopCnt = 0;*/
   LwrGenCfg    *cfg = NULLP;
   cfg   = &(lwrMng->t.cfg.t.genCfg);
   /*----------- Fill General Configuration Parameters ---------*/

   /* Filling UE Inactivity Timer */
   cfg->cellCfg.rrmRntiStart = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmRntiStart;
   cfg->cellCfg.maxRrmRntis = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxRrmRntis;
   cfg->cellCfg.rrmPrmblStart = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmPrmblStart;
   cfg->cellCfg.macRntiStart = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.macRntiStart;
   cfg->cellCfg.maxMacRntis = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxMacRntis;
   cfg->noOfCells =  lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.numOfCells;
   wrSmDfltNumCells =  lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.numOfCells;
   printf("\n%s:Number Of Cells = %d\n",__func__,lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.numOfCells);
   RLOG1(L_DEBUG, "\n:Number Of Cells = %d\n",lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.numOfCells);
   cfg->inactvTmrVal = lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.inactvTmrVal;
   cfg->expiryCnt   = lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.maxExpires;
   cfg->endMrkTmrVal = lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.endMrkTmrVal;
   /* Fill UL SRS Periodicity */
   cfg->ulSrsPeriod  = wrSmUlSrsPeriod;

#ifdef ENB_OVRLOAD
   cfg->eNBOvldParams.critThrldVal = WR_CRIT_THRLD_VAL;
   cfg->eNBOvldParams.majThrldVal  = WR_MAX_THRLD_VAL; 
   cfg->eNBOvldParams.minThrldVal  = WR_MIN_THRLD_VAL;
   cfg->eNBOvldParams.critRcvryVal = WR_CRIT_RCVRY_VAL;
   cfg->eNBOvldParams.majRcvryVal  = WR_MAX_RCVRY_VAL;
   cfg->eNBOvldParams.minRcvryVal  = WR_MIN_RCVRY_VAL;
   cfg->eNBOvldParams.eNBMemCritThresVal= WR_ENB_MEM_CRIT_THRES_VAL;
   cfg->eNBOvldParams.eNBMemMajThresVal = WR_ENB_MEM_MAX_THRES_VAL;
   cfg->eNBOvldParams.eNBMemMinThresVal = WR_ENB_MEM_MIN_THRES_VAL;
   cfg->eNBOvldParams.eNBOvldMonTimerVal= WR_ENB_OVLD_MON_TMR_VAL;
   cfg->eNBOvldParams.eNBOvldMonfreq   = WR_ENB_OVLD_MON_FREQ;
   cfg->eNBOvldParams.maxCntval        = WR_MAX_CNT_VAL;
   cfg->eNBOvldParams.eNbOvrLdFlag     = WR_ENB_OVLD_FLAG;
#endif  
   printf("in smm rrcLogEnable = %d\n",lteeNodeBparams[0].lteGostLog.rrcLogEnable);
   printf("\n in wr_smm_enb_utils.c  IP address = %s\n",lteeNodeBparams[0].lteGostLog.ipAddress);
   cfg->enblSIAndPagngLog = lteeNodeBparams[0].lteGostLog.rrcLogEnable;

   RETVALUE(ROK);
}/*end of wrSmmEnbBuildGenCfg*/

/*
 *       Fun:   wrSmmEnbBuildCellCfg
 *
 *       Desc:  fill in cellCfg for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_smm_tenb_utils.c  
 */

#ifdef ANSI
PUBLIC S16 wrSmmEnbBuildCellCfg
(
 LwrMngmt *lwrMng, 
 U8       cellCfgIdx 
 )
#else /* if ANSI not defined*/
PUBLIC S16 wrSmmEnbBuildCellCfg(lwrMng, cellCfgIdx)
   LwrMngmt *lwrMng;
   U8       cellCfgIdx;
#endif /* end of ANSI*/
{
   LwrCellMibCfgGrp    *lwrMib = NULLP;
   LwrCellSib4CfgGrp   *sib4 =NULLP;
   LwrProcTimerCfgGrp  *tmrCfg = NULLP;
   U8                   idx = 0;
   U8                  cfgGrpIndex = 0;
   LwrCellSib6CfgGrp   *sib6 = NULLP;
   LwrCellSib7CfgGrp   *sib7 = NULLP;
   //LwrCellSib9CfgGrp   *sib9 = NULLP;      
   LwrAddCellCfg       *enbCfg = NULLP;
   LwrRgrCfgGrp        *rgrCfg = NULLP;
   LwrCtfCfgGrp        *ctfCfg = NULLP;
   LwrRlcCfgGrp        *rlcCfg = NULLP;
   LwrCellSchdCfg      *schdCfg = NULLP;
   LwrSrbPolicy     *srbInfo = NULLP;
   LwrCsfbCfgGrp       *csfbGrp = NULLP;
   U16                 dfltDrxCycle;
   U8                  dfltModPrdCoeff;
   LwrCellUlSchdCfgGrp *ulSchdCfgGrp = NULLP;
   LwrCellDlSchdCfgGrp *dlSchdCfgGrp = NULLP;
   U8 wrHoDedPreamCount = 0;

   TRC2(wrSmmEnbBuildCellCfg);

   enbCfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell);
   lwrMng->t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng->t.protoCfg.t.cellCfg.action = WR_ACT_ADD;

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.dlCarrierFreq = 
      lteeNodeBparams[cellCfgIdx].lteAddCellCfg.earfdnDl; /*ccpu00127813 changes*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellId = cellCfgIdx + 1; 
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellIndex     = cellCfgIdx; 
   /*DRX QCI */
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.isDRXQCIEnabled = 
      lteeNodeBparams[cellCfgIdx].lteDrxCfgParams.isDRXQCIEnabled;

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellSizeType = 
      lteeNodeBparams[cellCfgIdx].lteAddCellCfg.cellSizeType;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.physCellId = 
      lteeNodeBparams[cellCfgIdx].lteAddCellCfg.physCellId; 
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.duplexMode = 
      lteeNodeBparams[cellCfgIdx].lteAddCellCfg.duplexMode; 
   printf("\nwrSmmEnbBuildCellCfg:Duplex mode is %d\n",lteeNodeBparams[cellCfgIdx].lteAddCellCfg.duplexMode);
   RLOG1(L_DEBUG, "\nwrSmmEnbBuildCellCfg:Duplex mode is %d\n",lteeNodeBparams[cellCfgIdx].lteAddCellCfg.duplexMode);
#ifdef LTE_ADV
#if 0/* Disabling timer untill we hae the activation/deactivation logic in mac*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.sCellDeActTmr.pres = PRSNT_NODEF;
#else
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.sCellDeActTmr.pres = NOTPRSNT;
#endif
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.sCellDeActTmr.val = lteeNodeBparams[cellCfgIdx]. \
                                                              caGenCfg.sCellDeActTmr;

#endif /* LTE_ADV */
   /*CA_DEV*/
   /* CSG_DEV start */
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.csgAccessMode = 
      lteeNodeBparams[cellCfgIdx].lteFapAccessParams.accessMode;
   /* because there will be value for startPci and pciRange always, setting 
    * pciRangeInfoPres to PRSNT_NODEF */
   if(TRUE ==  lteeNodeBparams[cellCfgIdx].lteAddCellCfg.isSmallCellPciCfgd)
   {
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.smallCellCsgPciRange.\
         pciRangeInfoPres = PRSNT_NODEF;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.smallCellCsgPciRange.startPci = 
         lteeNodeBparams[cellCfgIdx].lteAddCellCfg.startPci;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.smallCellCsgPciRange.pciRange =
         lteeNodeBparams[cellCfgIdx].lteAddCellCfg.pciRange;
   }
   if(lteeNodeBparams[cellCfgIdx].lteFapAccessParams.accessMode == WR_ENB_HYBRID_ACCESS)
   {
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.hcsgParam.minDlResNonCsg  =
         lteeNodeBparams[cellCfgIdx].lteAddCellCfg.minDlResNonCsg;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.hcsgParam.minUlResNonCsg  =
         lteeNodeBparams[cellCfgIdx].lteAddCellCfg.minUlResNonCsg;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.hcsgParam.maxCsgUeSup    =
         wrSmDfltMaxCsgUEs;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.hcsgParam.maxNonCsgUeSup =
         wrSmDfltMaxNonCsgUEs;
   }
   /* CSG_DEV end */

   /*Filling MIB params*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType 
      = WR_CELL_CFG_GRP_MIB;
   lwrMib = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.mibCfgGrp);

   lwrMib->dlBw = lteeNodeBparams[cellCfgIdx].lteCellMibCfgGrp.dlBw[0];
   wrSmmEnbSetBwFrmBwIdx(lwrMib->dlBw);
   lwrMib->phichCfg.phichDur = wrSmDfltPhichDur;
   lwrMib->phichCfg.phichRes = wrSmDfltPhichRes;
   cfgGrpIndex++;

   /* Build the sib1 configuration parameter */
   wrSmmEnbBldSib1Cfg(lwrMng, cfgGrpIndex, \
         lteeNodeBparams[cellCfgIdx].lteFapAccessParams.accessMode,cellCfgIdx);
   cfgGrpIndex++; 

   /* Build the sib2 configuration parameter */
   wrSmmEnbBldSib2Cfg(lwrMng, cfgGrpIndex,cellCfgIdx);
   cfgGrpIndex++; 

   /* Build the sib2 configuration parameter */
   wrSmmEnbBldSib3Cfg(lwrMng, cfgGrpIndex,cellCfgIdx);
   cfgGrpIndex++; 

   /* Configure the SIB4 parameters*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_SIB4;
   sib4 = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.sib4CfgGrp);

   /*Updating the CSG Split Info parameters */
   if(TRUE == lteeNodeBparams[cellCfgIdx].lteSib4CsgInfo.isCsgPciCfgd)
   {
      sib4->csgInfo.isCsgPciCfgd      = TRUE;
      sib4->csgInfo.csgStartPhyCellId = 
         lteeNodeBparams[cellCfgIdx].lteSib4CsgInfo.csgStartPhyCellId;
      sib4->csgInfo.csgPciRange = (U8)lteeNodeBparams[cellCfgIdx].lteSib4CsgInfo.csgPciRange;
   }

   /* ccpu00132596 */
   wrSmmEnbIsPciRangeValid(&sib4->csgInfo);
   /* ccpu00132596 */

   cfgGrpIndex++;

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_TIMER;
   /* Filling Emm (S1/X2) Timer values */
   /* TODO: Do the same for all other timers */
   tmrCfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].
         t.procTimerCfgGrp);

   tmrCfg->s1SetupTmr                       = wrSmDfltS1SetupTmr;
   tmrCfg->s1UpdateTmr                      = wrSmDfltUpdateTmr;
   tmrCfg->s1RetryCount                     = wrSmDfltS1RtryCntTmr;
   tmrCfg->s1TimeToWait                     = wrSmDfltS1TimeToWait;
   tmrCfg->s1MmeConfigurationTransferTmr    = wrSmDfltS1MmeCfgTrfrTmr;
   tmrCfg->s1ResetTmr                       = wrSmDfltX2ResetRetryTmr; 
   tmrCfg->x2SetupTmr                       = wrSmDfltX2SetupTmr;
   tmrCfg->x2SetTimeToWait                  = wrSmDfltX2SetTimeToWait;
   tmrCfg->x2UpdateTmr                      = wrSmDfltX2UpdateTmr;
   tmrCfg->x2UpdTimeToWait                  = wrSmDfltX2UpdateTimeToWait;
   tmrCfg->x2ResetTmr                       = wrSmDfltS1ResetRetryTmr; 
   tmrCfg->X2ResetRetryCount                = wrSmDfltX2RstRtryCntTmr;
   tmrCfg->X2SetupRetryCount                = wrSmDfltX2SetupRtryCntTmr;
   tmrCfg->x2UpdRetryCount                  = wrSmDfltX2UpdateRetryCount;
   tmrCfg->internalNoWaitRetryTmr           = wrSmDfltIntNoWaitRetryTmr;

   /* Fill RRC Timer Values */
   tmrCfg->rrcConnectionSetupTmr           = wrSmDfltRrcConSetupTmr;
   tmrCfg->rrcConnectionReconfigTmr        = wrSmDfltRrcConReCfgTmr;
   tmrCfg->rrcConnectionReEstablishTmr     = wrSmDfltRrcConReEstTmr;
   tmrCfg->rrcSecurityModeCommandTmr       = wrSmDfltRrcSecModCmdTmr;
   tmrCfg->rrcUeCapabilityEnquiryTmr       = wrSmDfltRrcUeCapEnqTmr;
   tmrCfg->rrcConnectionReleaseTmr         = wrSmDfltRrcConRelTmr;
   tmrCfg->rrcHandoverPrepTmr              = wrSmDfltRrcHandoverPrepTmr;
   tmrCfg->rrcUeInformationRequestTmr      = wrSmDfltRrcUeInfReqTmr;

   tmrCfg->s1InitialContextSetupTmr        = wrSmDflts1InitialContextSetupTmr;
   tmrCfg->s1ErabReleaseIndicationTmr      =wrSmDflts1ErabReleaseIndicationTmr;
   tmrCfg->s1UeContextReleaseTmr           = wrSmDflts1UeContextReleaseTmr;
   tmrCfg->s1PathSwitchTmr                 = wrSmDflts1PathSwitchTmr;
   tmrCfg->s1HandoverCancelTmr             = 
      lteeNodeBparams[cellCfgIdx].lteProcTimerCfg.s1HandoverCancelTmr;
   tmrCfg->x2HandoverPrepTmr               = wrSmDfltx2HandoverPrepTmr;
   tmrCfg->x2RelocOverallTmr               = wrSmDfltx2RelocOverallTmr;
   tmrCfg->x2StoreUeContextTmr             = wrSmDfltx2StoreUeContextTmr;
   tmrCfg->x2SnStatusTransferTmr           = wrSmDfltx2SnStatusTransferTmr;
   tmrCfg->internalSubCellChangeTmr        = wrSmDfltinternalSubCellChangeTmr;
   tmrCfg->internalSubCellPdcpControlTmr   =
      wrSmDfltinternalSubCellPdcpControlTmr;
   tmrCfg->ehrpdOptHoCompleteTmr          = wrSmDfltehrpdOptHoCompleteTmr;
   tmrCfg->intraEnbHoCompleteTmr          = wrSmDfltintraEnbHoCompleteTmr;
   tmrCfg->measurementReportToWaitTmr     = wrSmDfltmeasurementReportToWaitTmr;
   tmrCfg->internalResourceSetupTmr       = wrSmDfltinternalResourceSetupTmr;
   tmrCfg->internalResourceReleaseTmr     = wrSmDfltinternalResourceReleaseTmr;
   tmrCfg->internalSecurityControlTmr     = wrSmDfltinternalSecurityControlTmr;
   tmrCfg->internalRrcDataTransferTmr     = wrSmDfltinternalRrcDataTransferTmr;
   tmrCfg->internalForwardingPathSetupTmr =
      wrSmDfltinternalForwardingPathSetupTmr;
   tmrCfg->internalReestablishControlTmr   =
      wrSmDfltinternalReestablishControlTmr;
   tmrCfg->internalBufferFlushTmr          = wrSmDfltinternalBufferFlushTmr;
   tmrCfg->internalDataTransferStartTmr    =
      wrSmDfltinternalDataTransferStartTmr;
   tmrCfg->internalDataForwardEndIndTmr    =
      wrSmDfltinternalDataForwardEndIndTmr;
   tmrCfg->internalReestablishTimeToWaitTmr =
      wrSmDfltinternalReestablishTimeToWaitTmr;
   tmrCfg->internalUserInactivityTmr       = wrSmDfltinternalUserInactivityTmr;
   tmrCfg->internalSignalingInactivityTmr  =
      wrSmDfltinternalSignalingInactivityTmr;
   tmrCfg->internalUnassignedTmr           = wrSmDfltinternalUnassignedTmr;
   tmrCfg->internalNoWaitRetryTmr          = wrSmDfltinternalNoWaitRetryTmr;
   tmrCfg->internalRrcResetTmr             = wrSmDfltinternalRrcResetTmr;
   tmrCfg->internalEnbResetTmr             = wrSmDfltinternalEnbResetTmr;
   tmrCfg->internalSolicitMeasurementTmr   =
      wrSmDfltinternalSolicitMeasurementTmr;
   tmrCfg->internalRtdInfoReqTmr           = wrSmDfltinternalRtdInfoReqTmr;
   tmrCfg->s1HandoverPrepTmr = lteeNodeBparams[cellCfgIdx].lteProcTimerCfg.s1PrepTimerVal;
   tmrCfg->s1RelocOverallTmr = lteeNodeBparams[cellCfgIdx].lteProcTimerCfg.s1OvrAllTimerVal;
   tmrCfg->s1IRatHandoverPrepTmr = 
      lteeNodeBparams[cellCfgIdx].lteProcTimerCfg.s1RATPrepTimerVal;
   tmrCfg->s1IRatRelocOverallTmr = 
      lteeNodeBparams[cellCfgIdx].lteProcTimerCfg.s1RATOvrAllTimerVal;
   tmrCfg->x2HandoverPrepTmr = lteeNodeBparams[cellCfgIdx].lteProcTimerCfg.x2PrepTimerVal;
   tmrCfg->x2RelocOverallTmr = lteeNodeBparams[cellCfgIdx].lteProcTimerCfg.x2OvrAllTimerVal;

   //RIM parameters
   MsmLteRimParams *lteRimParams = &(lteeNodeBparams[cellCfgIdx].lteRimParams);
   tmrCfg->rimOvrlTmr = lteRimParams->rimOvrlTmrVal;
   tmrCfg->rimRirTmr = lteRimParams->rimRirTmr;
   tmrCfg->rimRiTmr = lteRimParams->rimRiTmr;
   tmrCfg->rimRiaeTmr = lteRimParams->rimRiaeTmr;
   tmrCfg->rimMaxRetryCnt = lteRimParams->rimMaxRetryCnt;

   /*Config SIB6 Params*/
   cfgGrpIndex++; 



   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_SIB6;

   sib6 = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.sib6CfgGrp);

   /*Updating the SIB6 parameters*/
   sib6->reCfgType            = wrSmDfltUtraReCfgType;
   sib6->sfUsagePres.pres     = PRSNT_NODEF;
   sib6->tReselection         = lteeNodeBparams[cellCfgIdx].lteCellSib6CfgGrp.tReselection;
   sib6->tReselectionSfMedium = 
      lteeNodeBparams[cellCfgIdx].lteCellSib6CfgGrp.tReselectionSfMedium;
   sib6->tReselectionSfHigh   = 
      lteeNodeBparams[cellCfgIdx].lteCellSib6CfgGrp.tReselectionSfHigh;
   /*Config SIB7 Params*/
   cfgGrpIndex++; 

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_SIB7;

   sib7 = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.sib7CfgGrp);

   sib7->reCfgType = wrSmDfltGeranReCfgType;
   sib7->tReselectionGERAN                = 
      lteeNodeBparams[cellCfgIdx].sib7CfgGrp.tReselectionGERAN;
   sib7->pres_SpeedStateScaleFactors.pres = 
      lteeNodeBparams[cellCfgIdx].sib7CfgGrp.pres_SpeedStateScaleFactors;
   sib7->pres_SpeedStateScaleFactors.val     = PRSNT_NODEF;
   sib7->tReselectionGERANSFMedium        = 
      lteeNodeBparams[cellCfgIdx].sib7CfgGrp.tReselectionGERANSFMedium;
   sib7->tReselectionGERANSFHigh          = 
      lteeNodeBparams[cellCfgIdx].sib7CfgGrp.tReselectionGERANSFHigh;
   /*Config SIB7 Params*/

   cfgGrpIndex++;

   if(lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.numCdma1xCells > 0)
      //     if (smCfgCb.noOfNeighCdma1xCells[cellCfgIdx] > 0)
   {
      /*Config SIB8 Params*/
      wrSmmEnbBldSib8Cfg(lwrMng, cfgGrpIndex,cellCfgIdx);
      cfgGrpIndex++;
   }

#if 0 /* sri: temp block for TIP. SIB9 broadcast not proper */
   /*Config SIB9 Params*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_SIB9;
   sib9 = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.sib9CfgGrp);
   /*cmMemcpy(sib9->henbName, "RADISYS", 8);*/
   cmMemcpy(sib9->henbName, lteeNodeBparams[cellCfgIdx].lteCellSib9CfgGrp.henbName,
         strlen((S8 *)lteeNodeBparams[cellCfgIdx].lteCellSib9CfgGrp.henbName));
   sib9->henbName[strlen((S8 *)lteeNodeBparams[cellCfgIdx].lteCellSib9CfgGrp.henbName)] = '\0';
   cfgGrpIndex++;
#endif

   /* Build the SIB Scheduling confuration parameters */
   wrSmmEnbBldCellSibSchCfg(lwrMng, cfgGrpIndex,cellCfgIdx);
   cfgGrpIndex++; 

   /* Build the rab policy configuration parameter */
   wrSmmEnbBldRabPolicy(lwrMng, cfgGrpIndex, cellCfgIdx);
   cfgGrpIndex++;

   wrSmmEnbBldCellEaidCfg(lwrMng, cfgGrpIndex);
   cfgGrpIndex++; 

   /* Build the Measurement  configuration parameters */
   wrSmmEnbBldMeasCellCfg(lwrMng, cfgGrpIndex,cellCfgIdx);
   cfgGrpIndex++; 

   /* Build the ANR confuration parameters */
   wrSmmEnbBldCellAnrCfg(lwrMng, cfgGrpIndex,cellCfgIdx); 
   cfgGrpIndex++; 



   tmrCfg->s1ResetTmr   = lteeNodeBparams[cellCfgIdx].lteProcTimerCfg.s1ResetTmr; 
   tmrCfg->x2ResetTmr   = lteeNodeBparams[cellCfgIdx].lteProcTimerCfg.x2ResetTmr; 
   /* Fill the RRM config */
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = 
      WR_CELL_CFG_GRP_RRM;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].
      t.rrmCfgGrp.enbCacInfo.maxEnbCallCount = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxUeSupp;

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].
      t.rrmCfgGrp.enbCacInfo.dfltRrmRntiSize = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxRrmRntis;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].
      t.rrmCfgGrp.enbCacInfo.dfltRrmStartPreamble = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmPrmblStart;
   /* Using 2/3rd of dedicated preambles for HO and reamining for PDCCH 
    * order RACH purpose at MAC*/
   wrHoDedPreamCount = 
      (lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxRrmPrmbls * 2)/3;
   if(wrHoDedPreamCount)
   {
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].
         t.rrmCfgGrp.enbCacInfo.dfltRrmNumPreamble = wrHoDedPreamCount;
   }
   else
   {/* Very less preambles are configure. Assigning complete 
     * for HO and none for pdcch order */
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].
         t.rrmCfgGrp.enbCacInfo.dfltRrmNumPreamble = 
         lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxRrmPrmbls;
   }

   cfgGrpIndex++; 
   /* LTE_ADV starts */
   /*Fill the LTE Advanced Config*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_LTEA;
   cmMemcpy((U8 *)&lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.lteAdvCfgGrp.lteAdvancedConfig, 
         (U8 *)&smCfgCb.lteAdvancedConfig, sizeof(LwrLteAdvancedConfig));
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.\
      lteAdvCfgGrp.pres = TRUE;
   cfgGrpIndex++; 
   /* LTE_ADV ends */

   /*UL and DL scheduler config*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = 
      WR_CELL_CFG_GRP_ULSCHD;
   ulSchdCfgGrp = &lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
                  cellCfgGrp[cfgGrpIndex].t.ulSchdCfgGrp;
   ulSchdCfgGrp->ulSchedulingAlg =
      lteeNodeBparams[cellCfgIdx].lteCellUlSchdCfgGrp.ulSchedulingAlg;
   ulSchdCfgGrp->maxUePerUlSf =
      lteeNodeBparams[cellCfgIdx].lteCellUlSchdCfgGrp.maxUePerUlSf;
   ulSchdCfgGrp->maxUlUeNewTxPerTti =
      lteeNodeBparams[cellCfgIdx].lteCellUlSchdCfgGrp.maxUlUeNewTxPerTti;
   cfgGrpIndex++; 

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = 
      WR_CELL_CFG_GRP_DLSCHD;
   dlSchdCfgGrp = &lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
                  cellCfgGrp[cfgGrpIndex].t.dlSchdCfgGrp;
   dlSchdCfgGrp->dlSchedulingAlg = 
      lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.dlSchedulingAlg;
   dlSchdCfgGrp->maxUePerDlSf = 
      lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.maxUePerDlSf;
   dlSchdCfgGrp->dlfsSchdType = lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.dlfsSchd;
   dlSchdCfgGrp->maxDlUeNewTxPerTti = 
      lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.maxDlUeNewTxPerTti;
   dlSchdCfgGrp->dlfsSchd = 
      lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.dlfsSchd;
   cfgGrpIndex++; 

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_ULPWRCNTRL;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].
      t.uLPwrCtrl.p0UePUSCH = wrSmDfltP0UEPUSCH;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].
      t.uLPwrCtrl.accumulationEnabled = wrSmDfltAccumulationEnabled;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].
      t.uLPwrCtrl.deltaMCSenabled = wrSmDfltDeltaMCSEnabled;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].
      t.uLPwrCtrl.p0UePUCCH = wrSmDfltP0UEPUCCH;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].
      t.uLPwrCtrl.pSRSoffset = wrSmDfltpSRSOffset;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].
      t.uLPwrCtrl.filterCoefficient = wrSmDfltFilterCoef;
   cfgGrpIndex++;
   /* Fill MAC config*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_RGR;
   rgrCfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.rgrCfgGrp);

   rgrCfg->dfltStartRnti = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.macRntiStart;
   rgrCfg->dfltRntiSize = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxMacRntis;
   rgrCfg->dfltCfiCfg = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.dfltCfiCfg;
   rgrCfg->dfltTrgUlCqi = wrSmDfltTrgUlCqi;
   rgrCfg->dfltBcchPchRaCodeRate = wrSmDfltBcchPchRaCodeRate;
   rgrCfg->dfltPdcchCodeRate = wrSmDfltPdcchCodeRate;
   rgrCfg->dfltPuschSubBndStrt = wrSmDfltPuschSubBndStrt;
   rgrCfg->dfltPuschNoSubbnds = wrSmDfltPuschNoSubbnds;
   rgrCfg->dfltULCmnCodRateCcchCqi = wrSmDfltULCmnCodRateCcchCqi;
   rgrCfg->dfltDLCmnCodRateCcchCqi = wrSmDfltDlCmnCodRateCcchCqi;
   rgrCfg->dfltIsDlFreqSel = lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.dlfsSchd;
   rgrCfg->dfltThresholdCqi = wrSmDfltThresholdCqi;
   rgrCfg->dfltMaxDlHqTx = wrSmDfltMaxDlHqTx;
   rgrCfg->dfltMaxMsg4HqTx = wrSmDfltMaxMsg4HqTx;
   rgrCfg->dfltPuschSubBandSz = wrSmDfltPuschSubBandSz;
   rgrCfg->dfltPuschSubBandDmrs = wrSmDfltPuschSubBandDmrs;
   rgrCfg->dfltMaxPucchRbs = wrSmDfltMaxPucchRbs[cellCfgIdx];
   cfgGrpIndex++;

   /* Fill CTF configuration */
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_CTF;
   ctfCfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.ctfCfgGrp); 
   ctfCfg->dfltScSpacing = wrSmDfltScSpacing;
   ctfCfg->dfltTagPeriod = lteeNodeBparams[cellCfgIdx].lteMsCellCfgReq.period;
   ctfCfg->dfltOpMode = lteeNodeBparams[cellCfgIdx].lteMsCellCfgReq.opMode;
   cfgGrpIndex++;

   /* Fill RLC configuration */
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = 
      WR_CELL_CFG_GRP_RLC;
   rlcCfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.rlcCfgGrp);
   rlcCfg->ulModeInfo.dfltAmRlcSrbtStatusProh = wrSmDfltAmRlcSrbtStatusProh;
   rlcCfg->ulModeInfo.dfltAmRlcDrbtStatusProh = wrSmDfltAmRlcDrbtStatusProh;
   rlcCfg->ulModeInfo.dfltUmRlcsnFieldLen = wrSmDfltUmRlcsnFieldLen;
   rlcCfg->ulModeInfo.drbtReordring = wrSmDfltUlDrbtReordring;
   rlcCfg->ulModeInfo.srbtReordring = wrSmDfltUlSrbtReordring;

   rlcCfg->dlModeInfo.dfltAmRlcSrbmaxRetxThresh = wrSmDfltAmRlcSrbmaxRetxThresh;
   rlcCfg->dlModeInfo.dfltAmRlcSrbmaxpollByte = wrSmDfltAmRlcSrbmaxpollByte;
   rlcCfg->dlModeInfo.dfltAmRlcSrbpollPdu = wrSmDfltAmRlcSrbpollPdu;
   rlcCfg->dlModeInfo.dfltAmRlcSrbtPollRetx = wrSmDfltAmRlcSrbtPollRetx;
   rlcCfg->dlModeInfo.dfltAmRlcDrbmaxRetxThresh = wrSmDfltAmRlcDrbmaxRetxThresh;
   rlcCfg->dlModeInfo.dfltAmRlcDrbmaxpollByte = wrSmDfltAmRlcDrbmaxpollByte;
   rlcCfg->dlModeInfo.dfltAmRlcDrbpollPdu = wrSmDfltAmRlcDrbpollPdu;
   rlcCfg->dlModeInfo.dfltAmRlcDrbtPollRetx = wrSmDfltAmRlcDrbtPollRetx;
   rlcCfg->dlModeInfo.dfltUmRlcsnFieldLen = wrSmDfltUmRlcsnFieldLen;
   rlcCfg->dlModeInfo.srbtReordring = wrSmDfltDlSrbtReordring;
   rlcCfg->dlModeInfo.drbtReordring = wrSmDfltDlDrbtReordring;

   cfgGrpIndex++;

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_RAB_POLICY;

   MsmLteSrbPolicy     *msmSrbPolicy = NULLP;
   for(idx = 0; idx < (LWR_MAX_SRBS-1); idx++)
   {
      srbInfo = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.rabPolicyCfgGrp.srbPolicy[idx]);
      msmSrbPolicy = &(lteeNodeBparams[cellCfgIdx].lteRabPolicyCfgGrp.srbPolicy[idx]);
      srbInfo->rlcInfo.tpRetransmit = msmSrbPolicy->rlcInfo.tpRetransmit;
      srbInfo->rlcInfo.pollPdu = msmSrbPolicy->rlcInfo.pollPdu;
      srbInfo->rlcInfo.pollByte = msmSrbPolicy->rlcInfo.pollByte;
      srbInfo->rlcInfo.maxRetransThresh = 
         msmSrbPolicy->rlcInfo.maxRetransThresh;
      srbInfo->rlcInfo.timerReorderingDl = 
         msmSrbPolicy->rlcInfo.timerReordering;
      srbInfo->rlcInfo.timerReorderingUl = 
         msmSrbPolicy->rlcInfo.timerReordering;
      srbInfo->rlcInfo.timerStatusProhibit = 
         msmSrbPolicy->rlcInfo.timerStatusProhibit;
      //srbInfo->lchInfo.srbId = msmSrbPolicy->srbId; 
      srbInfo->lchInfo.pbr                = 
         wrSmDfltPrioInfoTbl.srb[idx].pbr;
      srbInfo->lchInfo.bucketSizeDuration = 
         wrSmDfltPrioInfoTbl.srb[idx].bucketSizeDur;
      srbInfo->lchInfo.lchGrpId           = 
         wrSmDfltPrioInfoTbl.srb[idx].lchGrp;
      srbInfo->lchInfo.priority           = 
         wrSmDfltPrioInfoTbl.srb[idx].lchPriority;
   }
   cfgGrpIndex++;

   schdCfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.schdCfgGrp);
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = 
      WR_CELL_CFG_GRP_SCHD;
   schdCfg->prdEnum = wrSmDfltSrsCfgPrdEnum;
   schdCfg->retxCnt = wrSmDfltRetxCnt;
   WR_GET_PAGING_CYCLE(lteeNodeBparams[cellCfgIdx].ltePCCHCfgCommon.defaultPagingCycle,\
         dfltDrxCycle);
   WR_GET_MODIFI_COEFF(wrSmDfltModPeriodCoeff, dfltModPrdCoeff);
   schdCfg->modPrd = dfltModPrdCoeff * dfltDrxCycle;
   schdCfg->pwrCfg.pucchPwrFmt3Rnti = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.pucchPwrFmt3Rnti;
   schdCfg->pwrCfg.pucchPwrFmt3Siz = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.pucchPwrFmt3Siz;

   schdCfg->pwrCfg.pucchPwrFmt3aRnti = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.pucchPwrFmt3aRnti;
   schdCfg->pwrCfg.pucchPwrFmt3aSiz = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.pucchPwrFmt3aSiz;

   schdCfg->pwrCfg.puschPwrFmt3Rnti = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.puschPwrFmt3Rnti;
   schdCfg->pwrCfg.puschPwrFmt3Siz = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.puschPwrFmt3Siz;

   schdCfg->pwrCfg.puschPwrFmt3aRnti = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.puschPwrFmt3aRnti;
   schdCfg->pwrCfg.puschPwrFmt3aSiz = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.pucchPwrFmt3aSiz;

   schdCfg->pwrCfg.pucchPwrFmt3aEnable = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.pucchPwrFmt3aEnable;
   schdCfg->pwrCfg.puschPwrFmt3aEnable = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.puschPwrFmt3aEnable;

   schdCfg->pwrCfg.isUlGrpPwrCntrlPucchEnable = 
      wrSmDfltisUlGrpPwrCntrlPucchEnable;
   schdCfg->pwrCfg.isUlGrpPwrCntrlPuschEnable = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.isUlGrpPwrCntrlPuschEnable;
   if((wrHoDedPreamCount) && 
         (lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxRrmPrmbls - wrHoDedPreamCount))   
   {/* Assigning the remaining ded preambles to MAC for
     * PDCCH order RACH */
      schdCfg->preamPres  = TRUE;
      schdCfg->preamStart = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmPrmblStart + 
         wrHoDedPreamCount;
      schdCfg->preamSize  = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxRrmPrmbls - 
         wrHoDedPreamCount;
   }
   else
   {
      schdCfg->preamPres  = FALSE;
      schdCfg->preamStart = 0;
      schdCfg->preamSize  = 0;
   }

   schdCfg->rachCfg.preambleFormat = wrSmDfltPreambleFrmt;
   schdCfg->rachCfg.raOccSize = wrSmDfltRaOccSz;
   schdCfg->rachCfg.raOccSfnEnum = wrSmDfltRaOccSfnEnum;
   schdCfg->rachCfg.prachResource = wrSmDfltPrachResource;
   schdCfg->genCfg.macInst = cellCfgIdx;
   schdCfg->genCfg.maxUePerUlSf = 
      lteeNodeBparams[cellCfgIdx].lteCellUlSchdCfgGrp.maxUePerUlSf;
   schdCfg->genCfg.maxUePerDlSf = 
      lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.maxUePerDlSf;
   schdCfg->genCfg.maxUlBwPerUe = wrSmDfltMaxUlBwPerUe;
   schdCfg->genCfg.maxDlBwPerUe = wrSmDfltMaxDlBwPerUe;
   schdCfg->genCfg.maxDlRetxBw = wrSmDfltMaxDlRetxBw;
   schdCfg->genCfg.maxDlUeNewTxPerTti = 
      lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.maxDlUeNewTxPerTti;
   schdCfg->genCfg.maxUlUeNewTxPerTti = 
      lteeNodeBparams[cellCfgIdx].lteCellUlSchdCfgGrp.maxUlUeNewTxPerTti;
   schdCfg->genCfg.cellModSchm = wrSmDfltCellModSchm;
   /* SPS changes starts */
   schdCfg->spsCfg.bIsSpsEnabled = lteeNodeBparams[cellCfgIdx].stSpsCellCfg.bIsSpsEnabled;
   if (schdCfg->spsCfg.bIsSpsEnabled == TRUE)
   {
      schdCfg->spsCfg.maxDlSpsUePerTti = 
         lteeNodeBparams[cellCfgIdx].stSpsCellCfg.maxDlSpsUePerTti;
      schdCfg->spsCfg.maxUlSpsUePerTti = 
         lteeNodeBparams[cellCfgIdx].stSpsCellCfg.maxUlSpsUePerTti;
      schdCfg->spsCfg.maxDlBwInRbs = lteeNodeBparams[cellCfgIdx].stSpsCellCfg.maxDlBwInRbs;
   }
   /* SPS changes ends */

   schdCfg->isDynCfiEnb = lteeNodeBparams[cellCfgIdx].lteDynCfiParams.isDynCfiEnb;

   cfgGrpIndex++; 

   csfbGrp = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.csfbCfgGrp);
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_CSFB;
   csfbGrp->eCsfbMeasSup = lteeNodeBparams[cellCfgIdx].csfbCfgGrp.ecsfbSupport;
   csfbGrp->dualRxSup = lteeNodeBparams[cellCfgIdx].csfbCfgGrp.dualRxSup;
   RLOG1(L_DEBUG, "smBuildCellCfg:eCSFB value from oam = %d\n",\
         lteeNodeBparams[cellCfgIdx].csfbCfgGrp.ecsfbSupport);
   /*RRC Rel10 Upgrade - start*/
   if (TRUE == lteeNodeBparams[cellCfgIdx].csfbCfgGrp.dualRxTxSup)
   {
      if(LWR_ECSFB_NOT_SUPPORTED == csfbGrp->eCsfbMeasSup) 
      {
         RLOG2(L_ERROR, "Invalid Cfg for paramter DUAL_RX_TX_SUPPORTED:" 
               "eCSFB should be supported(currently=%d) inorder to support "
               "DualRxTx Cfg(%d)",csfbGrp->eCsfbMeasSup,lteeNodeBparams[cellCfgIdx].\
               csfbCfgGrp.dualRxTxSup);

         RETVALUE(RFAILED);
      }
   }
   RLOG1(L_DEBUG, "smBuildCellCfg:dualRxTx value from oam =\
         %d\n",lteeNodeBparams[cellCfgIdx].csfbCfgGrp.dualRxTxSup);
   csfbGrp->dualRxTxSup = lteeNodeBparams[cellCfgIdx].csfbCfgGrp.dualRxTxSup;
   csfbGrp->cdma1xRttSup = wrSmDfltCdma1xrttRegSup;

   /*RRC Rel10 Upgrade - end*/
   csfbGrp->csfbToUtraMeasSup = 
      lteeNodeBparams[cellCfgIdx].csfbCfgGrp.csfbToUtranWithMeasEnabled;
   csfbGrp->csfbToCdmaMeasSup = lteeNodeBparams[cellCfgIdx].csfbCfgGrp.csfbSupport;
   csfbGrp->cdma1xrttCsfbCfg.secId.isOctStrPres = NOTPRSNT;
   csfbGrp->cdma1xrttCsfbCfg.secId.cdmaType = wrSmDfltCellType;
   if(FALSE == csfbGrp->cdma1xrttCsfbCfg.secId.isOctStrPres)
   {
      csfbGrp->cdma1xrttCsfbCfg.secId.s.cdmaSectorId.marketId = 
         lteeNodeBparams[cellCfgIdx].csfbCfgGrp.marketId;
      csfbGrp->cdma1xrttCsfbCfg.secId.s.cdmaSectorId.switchNum = 
         lteeNodeBparams[cellCfgIdx].csfbCfgGrp.switchNum;
      csfbGrp->cdma1xrttCsfbCfg.secId.s.cdmaSectorId.cellId = 
         wrSmDfltCdmaCellId;
      csfbGrp->cdma1xrttCsfbCfg.secId.s.cdmaSectorId.sectorNum = 
         lteeNodeBparams[cellCfgIdx].csfbCfgGrp.sectorNum;
   }
   else
   {
      wrFillSectorId(&csfbGrp->cdma1xrttCsfbCfg.secId.s.sectorIdPtr, 7,
            (Data *)&wrSmDfltSecId);
   }
   wrSmmEnbBuildMobParams(&csfbGrp->cdma1xrttCsfbCfg.mobParams,cellCfgIdx);
   cfgGrpIndex++; 

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.numOfGrps = cfgGrpIndex;
#ifdef LTE_UNLICENSED
   if ((wrSmDfltNumCells - wrSmDfltNumUnLicnsdCells))
   {
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = WR_CFG_TYPE_UNLICNSD_CELL;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.coExistMethod = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.coExistMethod;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.lteOnPeriod = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.lteOnPeriod;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.caeMethod = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.caeMethod;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.adaptiveTx = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.adaptiveTx;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.transPeriod = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.transPeriod;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.listenPrd = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.listenPrd;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.energyTh = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.energyTh;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.scanTimePrd = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.scanTimePrd;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.activityTh = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.activityTh;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.txPowerLimit = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.txPowerLimit;
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.numFreq = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.numFreq;
      cmMemcpy(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.earfcn,
            lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.earfcn, (sizeof(U32)*LWR_LTEU_MAX_EARFCN));

      //lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.earfcn[LWR_LTEU_MAX_EARFCN] = 
        // lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.earfcn[LWR_LTEU_MAX_EARFCN];
      lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.lteUCfgGrp.isLaaCell = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteUCfg.isLaaCell;
      cfgGrpIndex++;
   }
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.numOfGrps = cfgGrpIndex;
#endif

   /*GA 5.0 changes*/ 
   enbCfg->isAutoCfgModeEnb = lteeNodeBparams[cellCfgIdx].lteTransModeCellCfg.bIsAutoConfigEnabled;
   enbCfg->txPrefMode = lteeNodeBparams[cellCfgIdx].lteTransModeCellCfg.transModeUse;
   /*GA 5.0 changes*/ 

   /*PHY parameters*/
   enbCfg->shutdownPwrCfg.lwPwrCfg.lowRefSigPwr = wrSmDfltLowRefSigPwr;
   enbCfg->shutdownPwrCfg.lwPwrCfg.lowPilotSigPwr = wrSmDfltLowPilotSigPwr;
   enbCfg->shutdownPwrCfg.lwPwrCfg.lowPriSigPwr = wrSmDfltLowPriSigPwr;
   enbCfg->shutdownPwrCfg.lwPwrCfg.lowSecSigPwr = wrSmDfltLowSecSigPwr;
   enbCfg->shutdownPwrCfg.hiPwrCfg.highRefSigPwr = wrSmDfltRefSigPwr; 
   enbCfg->shutdownPwrCfg.hiPwrCfg.highPilotSigPwr = wrSmDfltPilotSigPwr;
   enbCfg->shutdownPwrCfg.hiPwrCfg.highPriSigPwr = wrSmDfltPriSigPwr;
   enbCfg->shutdownPwrCfg.hiPwrCfg.highSecSigPwr = wrSmDfltSecSigPwr;
   /*multiCell*/
   enbCfg->macMainCfg.timeAlignmentTimerDedicated = 
      lteeNodeBparams[cellCfgIdx].macMainConfig.timeAlignmentTimerDedicated; 
   enbCfg->macMainCfg.ulSchCfg.maxHARQ_Tx = 
      lteeNodeBparams[cellCfgIdx].lteMAC_SCH_Config.maxHARQ_Tx;
   enbCfg->macMainCfg.ulSchCfg.periodicBSR_Timer = 
      lteeNodeBparams[cellCfgIdx].lteMAC_SCH_Config.periodicBSR_Timer;
   enbCfg->macMainCfg.ulSchCfg.retxBSR_Timer = 
      lteeNodeBparams[cellCfgIdx].lteMAC_SCH_Config.retxBSR_Timer;
   enbCfg->macMainCfg.ulSchCfg.ttiBundling = 
      lteeNodeBparams[cellCfgIdx].lteMAC_SCH_Config.ttiBundling;
   enbCfg->macMainCfg.ulSchCfg.deltaHqOffset = wrSmDfltDeltaHqOffst;
   enbCfg->macMainCfg.phr_Config.periodicPHR_Timer = 
      wrSmDfltMacCfgPeriodicPHR_Timer;
   enbCfg->macMainCfg.phr_Config.prohibitPHR_Timer = 
      wrSmDfltMacCfgProhibitPHRTimer;
   enbCfg->macMainCfg.phr_Config.dl_PathlossChange = 
      wrSmDfltMacCfgDlPathlossChange; 

   enbCfg->pdcpInfo.umSnSize = NHU_PDCP_SN_SIZE_7BITS; 
   enbCfg->pdcpInfo.statRprtReqrd = wrSmDfltStatusReportReqd;
   enbCfg->pdcpInfo.discardTimer = wrSmDfltDiscardTimer;

   enbCfg->puschDedicated.ackIdx = wrSmDfltBetaOffACKIdx;
   enbCfg->puschDedicated.riIdx = wrSmDfltBetaOffRIIdx;
   enbCfg->puschDedicated.cqiIdx = wrSmDfltBetaOffCQIIdx;

#ifdef WR_RSYS_OAM
   enbCfg->cqiRptCfg.subbndCqik = 
      lteeNodeBparams[cellCfgIdx].lteCQIPeriodicReportCfg.subBandCQI.k;
#endif

   enbCfg->puschDedicated.puschPwrCfg.pres = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.isUlGrpPwrCntrlPuschEnable;
   enbCfg->puschDedicated.puschPwrCfg.isFmt3a = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.puschPwrFmt3aEnable;
   enbCfg->pucchPwrCfg.pres = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.isUlGrpPwrCntrlPucchEnable;
   enbCfg->pucchPwrCfg.isFmt3a = 
      lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.pucchPwrFmt3aEnable;
   enbCfg->pdschCfgDedicated.pA = lteeNodeBparams[cellCfgIdx].ltePdschCfgDedicated.pA[0];
   enbCfg->schReqCfg.dsrTransMax = wrSmDfltDsrTransMax;
   enbCfg->schReqCfg.srPucchRsrcIdx = 
      lteeNodeBparams[cellCfgIdx].lteCQIPeriodicReportCfg.cqi_PUCCH_ResourceIdx; 
   enbCfg->qosCfg.ueBr = wrSmDfltUeBr;
   enbCfg->cqiRptCfg.aperCqiEnbld = FALSE;
   enbCfg->cqiRptCfg.cqiAperiodicMode = wrSmDfltCqiRprtModeAperiodic;
   enbCfg->cqiRptCfg.nomPdschRsEpreOff = (S8)wrSmDfltCqiNomPDSCHRSEPREoff;
   enbCfg->cqiRptCfg.periodRptSetupPres = FALSE;
   enbCfg->cqiRptCfg.cqiPucchRsrcIdx = wrSmDfltCqiPUCCHResIdx;
   enbCfg->cqiRptCfg.cqipmiCfgIdx = WR_UMM_CQI_PMI_CONFIG_IDX;
   enbCfg->cqiRptCfg.subbndCqik = 0;
   enbCfg->cqiRptCfg.fmtInd = WR_UE_CQI_FMT_WB;/*129311*/
   enbCfg->cqiRptCfg.riCfgIdx = 0;
   enbCfg->cqiRptCfg.simulAckNackAndCQI = wrSmDfltSimultAckNackAndCQI;
   enbCfg->cqiRptCfg.periodicmode = wrSmDfltPrdModeEnum;
   /*ccpu00129641*/
   enbCfg->cqiRptCfg.riPres = FALSE;

   enbCfg->numTxAntenna = 
     lteeNodeBparams[cellCfgIdx].lteAntenna_Common_Config.numAntPorts;

   enbCfg->csfbToGeranCfg.isGERANMeasAllowedForCCO = 
      lteeNodeBparams[cellCfgIdx].csfbToGeranCfg.isGERANMeasAllowedForCCO;
   enbCfg->csfbToGeranCfg.isCCOAllowed = 
      lteeNodeBparams[cellCfgIdx].csfbToGeranCfg.isCCOAllowed;
   enbCfg->csfbToGeranCfg.rrcDatCfmWaitTmr = 
      lteeNodeBparams[cellCfgIdx].csfbToGeranCfg.rrcDatCfmWaitTmr;
   enbCfg->csfbToGeranCfg.GERANMeasWaitTmr = 
      lteeNodeBparams[cellCfgIdx].csfbToGeranCfg.GERANMeasWaitTmr;
   enbCfg->csfbToGeranCfg.T304expWaitTmrVal = 
      lteeNodeBparams[cellCfgIdx].csfbToGeranCfg.T304expWaitTmrVal;

   /*multiCell*/
   RETVALUE(ROK);
} /* end of wrSmmEnbBuildCellCfg */

/*
 *
 *       Fun:   wrSmmEnbBldSib1Cfg
 *
 *       Desc:  fill in sib1 Cfg for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_smm_enb_utils.c 
 *
 */

PRIVATE Void wrSmmEnbBldSib1Cfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex,
 U8         accessMode,
 U8          cellCfgIdx
 )
{
   LwrCellSib1CfgGrp    *sib1 =NULLP;
   MsmLteCellSib1CfgGrp *sib1cfg = NULLP;
   MsmLtePlmnId  *priPlmn;
   MsmLtePlmnId  *plmn;
   U32 idx; 
   U32 idx1 = 1; 
   TRC2(wrSmmEnbBldSib1Cfg);

   /*Filling sib1 params*/
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType 
      = WR_CELL_CFG_GRP_SIB1;

   sib1 =&(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.sib1CfgGrp);

   sib1cfg  =&(lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp);
   sib1->freqBandInd = sib1cfg->freqBandInd;
   
   printf("\nwrSmmEnbBldSib1Cfg: Frequency Band Indicator is %d\n",sib1cfg->freqBandInd);
   RLOG1(L_DEBUG, "\nwrSmmEnbBldSib1Cfg: Frequency Band Indicator is %d\n",sib1cfg->freqBandInd);

   sib1->cellAccessInfo.numOfPlmns = 
      lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.numOfPlmns;
   for(idx =0; idx < sib1cfg->cellAccessInfo.numOfPlmns; idx++ )
   {
      if(lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.\
            plmnInfo[idx].isPrimary == TRUE)
      {
         priPlmn = &sib1cfg->cellAccessInfo.plmnInfo[idx].plmnId;
         sib1->cellAccessInfo.plmnInfo[0].plmnId.numMncDigits  = 
            priPlmn->numMncDigits;
         sib1->cellAccessInfo.plmnInfo[0].plmnId.mcc[0] =priPlmn->mcc[0];
         sib1->cellAccessInfo.plmnInfo[0].plmnId.mcc[1] =priPlmn->mcc[1];
         sib1->cellAccessInfo.plmnInfo[0].plmnId.mcc[2] =priPlmn->mcc[2];

         sib1->cellAccessInfo.plmnInfo[0].plmnId.mnc[0]=priPlmn->mnc[0];
         sib1->cellAccessInfo.plmnInfo[0].plmnId.mnc[1]=priPlmn->mnc[1];
         sib1->cellAccessInfo.plmnInfo[0].plmnId.mnc[2]=priPlmn->mnc[2];
         sib1->cellAccessInfo.plmnInfo[0].rsrvdFrOperUse = 
            sib1cfg->cellAccessInfo.plmnInfo[idx].rsrvdFrOperUse;
      }
      else
      {
         plmn = &sib1cfg->cellAccessInfo.plmnInfo[idx].plmnId;
         sib1->cellAccessInfo.plmnInfo[idx1].plmnId.numMncDigits  = 
            plmn->numMncDigits;
         sib1->cellAccessInfo.plmnInfo[idx1].plmnId.mcc[0] =plmn->mcc[0];
         sib1->cellAccessInfo.plmnInfo[idx1].plmnId.mcc[1] =plmn->mcc[1];
         sib1->cellAccessInfo.plmnInfo[idx1].plmnId.mcc[2] =plmn->mcc[2];

         sib1->cellAccessInfo.plmnInfo[idx1].plmnId.mnc[0]=plmn->mnc[0];
         sib1->cellAccessInfo.plmnInfo[idx1].plmnId.mnc[1]=plmn->mnc[1];
         sib1->cellAccessInfo.plmnInfo[idx1].plmnId.mnc[2]=plmn->mnc[2];
         sib1->cellAccessInfo.plmnInfo[idx1].rsrvdFrOperUse = 
            sib1cfg->cellAccessInfo.plmnInfo[idx].rsrvdFrOperUse;
         idx1++;
      }
   }


   sib1->cellAccessInfo.tac = sib1cfg->cellAccessInfo.tac;
   sib1->cellAccessInfo.cellId = sib1cfg->cellAccessInfo.cellId;
   /* CSG_DEV start */
   if(WR_ENB_OPEN_ACCESS == accessMode)
   {
      sib1->cellAccessInfo.csgIndication = FALSE;
      sib1->cellAccessInfo.csgIdentity.pres = NOTPRSNT;
   }
   else if(WR_ENB_CLOSED_ACCESS == accessMode)
   {
      sib1->cellAccessInfo.csgIndication = TRUE;
      wrFillTknU32(&sib1->cellAccessInfo.csgIdentity,
            sib1cfg->cellAccessInfo.csgIdentity);
   }
   else /* hybrid access */
   {
      sib1->cellAccessInfo.csgIndication = FALSE;
      wrFillTknU32(&sib1->cellAccessInfo.csgIdentity,
            sib1cfg->cellAccessInfo.csgIdentity);
   }
   /* CSG_DEV end */
   sib1->cellAccessInfo.cellBarred = sib1cfg->cellAccessInfo.cellBarred;
   sib1->cellAccessInfo.intraFreqReSelection = (Bool)wrSmDfltIntraFreqResel;
   sib1->cellSelectInfo.qRxLevMin = sib1cfg->cellSelectInfo.qRxLevMin;
   /* Start - Fix for ccpu00123651 */
   wrFillTknU8(&(sib1->cellSelectInfo.qRxLevMinOffset), \
         sib1cfg->cellSelectInfo.qRxLevMinOffset);
   /* End - Fix for ccpu00123651 */
   sib1->pMax = sib1cfg->pMax;

   sib1->siWindowSize = wrSmDfltSiWinSize;

   /*TODO:*/
#ifdef LTE_TDD
   sib1->tddCfg.specialSubframeCfg = 
      lteeNodeBparams[cellCfgIdx].lteTddParam.specialSubFramePattern;
   sib1->tddCfg.subframeCfg = lteeNodeBparams[cellCfgIdx].lteTddParam.subframeAssignment;
#else
   sib1->tddCfg.specialSubframeCfg = 0;
   sib1->tddCfg.subframeCfg = 0;
#endif
   RETVOID;
} /* end of wrSmmEnbBldSib1Cfg */ 

/*
 *
 *       Fun:   wrSmmEnbBldSib2Cfg
 *
 *       Desc:  fill in sib2 Cfg for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_smm_enb_utils.c 
 *
 */

PRIVATE Void wrSmmEnbBldSib2Cfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex,
 U8         cellCfgIdx
 )
{
   LwrCellSib2CfgGrp *sib2 = NULLP;
   LwrPuschCfgCommon *puschCfgCmn = NULLP;
   LwrPucchCfgCommon *pucchCfgCmn = NULLP;
   LwrSRSCfgCommon   *srsCfgCmn = NULLP;
   LwrPrachCfgCommon *prachCmn = NULLP;
   LwrRachCfgCommon  *rachCmn = NULLP;
   LwrULPwrCtrlCommon *uLPwrCtrlCmn = NULLP;
   LwrUeTimerConstants *ueTmr = NULLP;

   MsmLtePreambleCfgParams *lteRachPreambleCfg = NULLP;
   MsmLteDeltaPUCCHLst *deltaFLst = NULLP;
   MsmLteULPwrCtrlCommon *msmUlPwrCtrlCmn = NULLP;
   MsmPrachCfgInfo *prachCfgInfo = NULLP;
   MsmLteRachCfgCommonParams *lteRachCfgComnParams = NULLP;

   TRC2(wrSmmEnbBldSib2Cfg);

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = 
      WR_CELL_CFG_GRP_SIB2;

   sib2 =&(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.sib2CfgGrp);

   lteRachCfgComnParams = &lteeNodeBparams[cellCfgIdx].lteRachCfgCommonParams;  
   lteRachPreambleCfg = &lteRachCfgComnParams->ltePreambleCfg;
   msmUlPwrCtrlCmn = &(lteeNodeBparams[cellCfgIdx].lteULPwrCtrlCommon);
   deltaFLst = &(msmUlPwrCtrlCmn->deltaFLst);
   prachCfgInfo = &(lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachCfgInfo);


   puschCfgCmn = &(sib2->radioResourceCommon.puschCfgCommon);
   pucchCfgCmn = &(sib2->radioResourceCommon.pucchCfgCommon);
   srsCfgCmn = &(sib2->radioResourceCommon.srsCfgCommon);
   prachCmn = &(sib2->radioResourceCommon.prachCfgCommon);
   rachCmn = &(sib2->radioResourceCommon.rachCfgCommon);
   uLPwrCtrlCmn = &(sib2->radioResourceCommon.ulPwrCtrlCommon);
   ueTmr = &(sib2->ueTimerConstants);

   sib2->ueTimerConstants.t302 = 9;

   wrFillTknU8(&(sib2->acBarringInfo.pres), wrSmDfltACBarrInfoPres);
   sib2->acBarringInfo.acBarringForEmergency =  
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForEmergency;

   wrFillTknU8(&(sib2->acBarringInfo.acBarringForMOData.pres), \
         wrSmDfltMOACBarrInfoPres);

   sib2->ulFreqInfo.ulBandwidth = lteeNodeBparams[cellCfgIdx].lteULFrequencyInfo.ulBandwidth;
   sib2->ulFreqInfo.eARFCN      =  
      lteeNodeBparams[cellCfgIdx].lteULFrequencyInfo.eARFCN; 

   sib2->ulFreqInfo.addSpectEmission =(U8)wrSmDfltAddSpectEmn;

   sib2->acBarringInfo.acBarringForMOData.acBarringAC11 = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringAC11;
   sib2->acBarringInfo.acBarringForMOData.acBarringAC12 = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringAC12;
   sib2->acBarringInfo.acBarringForMOData.acBarringAC13 = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringAC13;
   sib2->acBarringInfo.acBarringForMOData.acBarringAC14 = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringAC14;
   sib2->acBarringInfo.acBarringForMOData.acBarringAC15 = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringAC15;

   /* RRC 3GPP TS 36.331:Sec 6.3.1: 
    * ac-BarringFactor Values other than p00 can only be set if all 
    * bits of the corresponding ac-BarringForSpecialAC are set to 0.
    * Originaly these changes has to be performed in OAM. But these
    * check added for 3rd party 
    */ 
   if((sib2->acBarringInfo.acBarringForMOData.acBarringAC11    | 
            sib2->acBarringInfo.acBarringForMOData.acBarringAC12 |
            sib2->acBarringInfo.acBarringForMOData.acBarringAC13 |
            sib2->acBarringInfo.acBarringForMOData.acBarringAC14 |
            sib2->acBarringInfo.acBarringForMOData.acBarringAC15) &&
         (NhuAC_BarringConfigac_BarringFactorp00Enum != 
          sib2->acBarringInfo.acBarringForMOData.acBarringFactor))
   {
      sib2->acBarringInfo.acBarringForMOData.acBarringFactor = 
         NhuAC_BarringConfigac_BarringFactorp00Enum;
   }
   else
   {
      sib2->acBarringInfo.acBarringForMOData.acBarringFactor = 
         lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringFactor;
   }

   sib2->acBarringInfo.acBarringForMOData.acBarringTime = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringTime;

   wrFillTknU8(&(sib2->acBarringInfo.acBarringForMOSignal.pres),\
         wrSmDfltDOACBarrInfoPres);

   sib2->acBarringInfo.acBarringForMOSignal.acBarringAC11 = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringAC11;
   sib2->acBarringInfo.acBarringForMOSignal.acBarringAC12 = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringAC12;
   sib2->acBarringInfo.acBarringForMOSignal.acBarringAC13 = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringAC13;
   sib2->acBarringInfo.acBarringForMOSignal.acBarringAC14 = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringAC14;
   sib2->acBarringInfo.acBarringForMOSignal.acBarringAC15 = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringAC15;

   /* RRC 3GPP TS 36.331:Sec 6.3.1: 
    * ac-BarringFactor Values other than p00 can only be set if all 
    * bits of the corresponding ac-BarringForSpecialAC are set to 0.
    * Originaly these changes has to be performed in OAM. But these
    * check added for 3rd party 
    */  
   if((sib2->acBarringInfo.acBarringForMOSignal.acBarringAC11    |
            sib2->acBarringInfo.acBarringForMOSignal.acBarringAC12 |
            sib2->acBarringInfo.acBarringForMOSignal.acBarringAC13 |
            sib2->acBarringInfo.acBarringForMOSignal.acBarringAC14 |
            sib2->acBarringInfo.acBarringForMOSignal.acBarringAC15) &&
         (NhuAC_BarringConfigac_BarringFactorp00Enum != 
          sib2->acBarringInfo.acBarringForMOSignal.acBarringFactor))
   {
      sib2->acBarringInfo.acBarringForMOSignal.acBarringFactor = 
         NhuAC_BarringConfigac_BarringFactorp00Enum;
   }
   else
   {
      sib2->acBarringInfo.acBarringForMOSignal.acBarringFactor = 
         lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringFactor;
   }

   sib2->acBarringInfo.acBarringForMOSignal.acBarringTime = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringTime;
   wrFillTknU8(&(sib2->acBarringVideo.pres),wrSmDfltVDACBarrInfoPres);

   sib2->acBarringVideo.acBarringAC11 = wrSmDfltacBarringAC11;

   sib2->acBarringVideo.acBarringAC12 = wrSmDfltacBarringAC12;
   sib2->acBarringVideo.acBarringAC13 = wrSmDfltacBarringAC13;
   sib2->acBarringVideo.acBarringAC14 = wrSmDfltacBarringAC14;
   sib2->acBarringVideo.acBarringAC15 = wrSmDfltacBarringAC15;
   sib2->acBarringVideo.acBarringFactor = wrSmDfltacBarringFactor;
   sib2->acBarringVideo.acBarringTime = wrSmDfltacBarringTime;

   wrFillTknU8(&(sib2->acBarringVideo.pres),wrSmDfltVOACBarrInfoPres);

   sib2->acBarringVoice.acBarringAC11 = wrSmDfltacBarringAC11;
   sib2->acBarringVoice.acBarringAC12 = wrSmDfltacBarringAC12;
   sib2->acBarringVoice.acBarringAC13 = wrSmDfltacBarringAC13;
   sib2->acBarringVoice.acBarringAC14 = wrSmDfltacBarringAC14;
   sib2->acBarringVoice.acBarringAC15 = wrSmDfltacBarringAC15;
   sib2->acBarringVoice.acBarringFactor = wrSmDfltacBarringFactor;
   sib2->acBarringVoice.acBarringTime = wrSmDfltacBarringTime;

   /*Filling BCCH*/
   sib2->radioResourceCommon.bcchCfgCommon.modPeriodCoeff 
      =(U8)wrSmDfltModPeriodCoeff;
   /*Filling PCCH*/
   sib2->radioResourceCommon.pcchCfgCommon.defaultPagingCycle 
      =lteeNodeBparams[cellCfgIdx].ltePCCHCfgCommon.defaultPagingCycle;
   sib2->radioResourceCommon.pcchCfgCommon.nB =
      lteeNodeBparams[cellCfgIdx].ltePCCHCfgCommon.nB;

   /*Filling PDSCH*/

   sib2->radioResourceCommon.pdschCfgCommon.pB = 
      lteeNodeBparams[cellCfgIdx].ltePdschCfgCommon.pB[0];
   sib2->radioResourceCommon.pdschCfgCommon.referenceSignalPwr = 
      lteeNodeBparams[cellCfgIdx].ltePdschCfgCommon.referenceSignalPwr[0];
   
   /*Filling PRACH*/
   /* wrSmDfltRootSequenceIdx: this str is not filled from wr_cf.So same default
    * value is taken here*/

   prachCmn->rootSequenceIndx = lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.rootSequenceIndx;
   prachCmn->prachCfgInfo.highSpeedFlag = (Bool)prachCfgInfo->highSpeedFlag;
   prachCmn->prachCfgInfo.zeroCorrelationZoneCfg= prachCfgInfo->zeroCorrelationZoneCfg;
   prachCmn->prachCfgInfo.prachFreqOffset = (Bool)prachCfgInfo->prachFreqOffset;
   
   /*prachCfgIdxLst is a list with 0th index being the preferred value.
    * Hence, using the same in SIB2 */
   prachCmn->prachCfgInfo.prachCfgIdx = 
      lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachParamLst.prachCfgIdxLst[0];

   /*Filling RACH*/
   rachCmn->maxHARQMsg3 = lteRachCfgComnParams->maxHARQMsg3;
   rachCmn->powerRamping.initRcvdTrgtPwr = 
      lteRachCfgComnParams->ltePowerRamping.initRcvdTrgtPwr;
   rachCmn->powerRamping.powerRampingstep= 
      lteRachCfgComnParams->ltePowerRamping.powerRampingstep;
   rachCmn->preambleCfg.groupASize = lteRachPreambleCfg->groupASize;
   rachCmn->preambleCfg.numOfRAPreambles= lteRachPreambleCfg->numOfRAPreambles;
   rachCmn->preambleCfg.msgSizeGroupA= lteRachPreambleCfg->msgSizeGroupA;  
   rachCmn->preambleCfg.pwrOffstGrpB= lteRachPreambleCfg->pwrOffstGrpB;
   rachCmn->raSupervisionCfg.macContResTimer = 
      lteRachCfgComnParams->lteRaSupervisionCfg.macContResTimer;
   rachCmn->raSupervisionCfg.preambleTransMax = 
      lteRachCfgComnParams->lteRaSupervisionCfg.preambleTransMax;
   rachCmn->raSupervisionCfg.rarWindowSize = 
      lteRachCfgComnParams->lteRaSupervisionCfg.rarWindowSize;

   /*Filling SRC */

   sib2->radioResourceCommon.srsCfgCommon.subframeCfg =(U8)wrSmDfltSrsSubfrmCfg;

   /*Filling UL Power Control*/
   sib2->radioResourceCommon.ulCyclicPrefix =wrSmDfltUlCyclicPrefixLength;
   uLPwrCtrlCmn->alpha = msmUlPwrCtrlCmn->alpha;
   uLPwrCtrlCmn->deltaMsg3 = msmUlPwrCtrlCmn->deltaMsg3;
   uLPwrCtrlCmn->pNomialPucch= msmUlPwrCtrlCmn->pNomialPucch;
   uLPwrCtrlCmn->pNomialPusch= msmUlPwrCtrlCmn->pNomialPusch;
   uLPwrCtrlCmn->deltaFLst.deltaPucchFormat1= deltaFLst->deltaPucchFormat1;
   uLPwrCtrlCmn->deltaFLst.deltaPucchFormat1b= deltaFLst->deltaPucchFormat1b;
   uLPwrCtrlCmn->deltaFLst.deltaPucchFormat2= deltaFLst->deltaPucchFormat2;
   uLPwrCtrlCmn->deltaFLst.deltaPucchFormat2a= deltaFLst->deltaPucchFormat2a;
   uLPwrCtrlCmn->deltaFLst.deltaPucchFormat2b= deltaFLst->deltaPucchFormat2b;

   srsCfgCmn->cSrs = lteeNodeBparams[cellCfgIdx].lteSRSCfgCommon.cSrs;
   srsCfgCmn->simulAckNackSrs = lteeNodeBparams[cellCfgIdx].lteSRSCfgCommon.simulAckNackSrs;
   srsCfgCmn->srsMaxUpts = lteeNodeBparams[cellCfgIdx].lteSRSCfgCommon.srsMaxUpts;

   pucchCfgCmn->deltaShift = lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.deltaShift;
   pucchCfgCmn->nRBCqi = lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.nRBCqi;
   pucchCfgCmn->nCSAN = lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.nCSAN;
   pucchCfgCmn->n1PucchAn = 
      lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.n1PucchAn;

   puschCfgCmn->puschRefSigCfg.grpHopEnabled = 
      lteeNodeBparams[cellCfgIdx].ltePuschRefSignalCfg.grpHopEnabled;
   puschCfgCmn->puschRefSigCfg.grpAsgnPusch = 
      lteeNodeBparams[cellCfgIdx].ltePuschRefSignalCfg.grpAsgnPusch;
   puschCfgCmn->puschRefSigCfg.seqHopEnabled = 
      lteeNodeBparams[cellCfgIdx].ltePuschRefSignalCfg.seqHopEnabled;
   puschCfgCmn->puschRefSigCfg.cyclicShift = 
      lteeNodeBparams[cellCfgIdx].ltePuschRefSignalCfg.cyclicShift;

   puschCfgCmn->puschBasicCfg.nSb = lteeNodeBparams[cellCfgIdx].ltePuschBasicCfgCommon.nSb;
   puschCfgCmn->puschBasicCfg.hoppingMode = 
      lteeNodeBparams[cellCfgIdx].ltePuschBasicCfgCommon.hoppingMode;
   puschCfgCmn->puschBasicCfg.hoppingOffset = 
      lteeNodeBparams[cellCfgIdx].ltePuschBasicCfgCommon.hoppingOffset;
   puschCfgCmn->puschBasicCfg.enable64QAM = 
      lteeNodeBparams[cellCfgIdx].ltePuschBasicCfgCommon.enable64QAM;

   ueTmr->t300 = lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t300; 
   ueTmr->t301 = lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t301; 
   ueTmr->t302 = lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t302; 
   ueTmr->t310 = lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t310; 
   ueTmr->n310 = lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.n310; 
   ueTmr->t311 = lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t311; 
   ueTmr->n311 = lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.n311; 
   ueTmr->t320 = lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t320; 
   /* ccpu00125578 T304 value set to ms500 so that
    * RRC Connection Reestablishment will be delayed during HO */
   ueTmr->t304 = lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t304; 
   ueTmr->ccoT304 = lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.ccoT304; 
   sib2->timeAlignmentCommon = lteeNodeBparams[cellCfgIdx].sib2Cfg.timeAlignmentCommon;

   RETVOID;
} /* end of wrSmmEnbBldSib2Cfg */

PRIVATE Void wrSmmEnbBldSib3Cfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex,
 U8         cellCfgIdx
 )
{
   LwrCellSib3CfgGrp *sib3 =NULLP;
   MsmLteMeasMobilityStatParams  *mobStateParams = NULLP;
   MsmLteCellSib3CfgGrp          *dfltSib3 = NULLP;

   TRC2(wrSmmEnbBldSib3Cfg);

   dfltSib3 = &lteeNodeBparams[cellCfgIdx].lteCellSib3CfgGrp;
   mobStateParams = &dfltSib3->mobStateParams;
   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = 
      WR_CELL_CFG_GRP_SIB3;
   sib3 = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.sib3CfgGrp);

   /*Updating the SIB3 parameters*/
   sib3->qHyst                               = 
      lteeNodeBparams[cellCfgIdx].lteCellSib3CfgGrp.qHyst;
   sib3->speedStateReselPres                 = WR_PRSNT;
   sib3->sfMedium                            = 
      lteeNodeBparams[cellCfgIdx].lteCellSib3CfgGrp.sfMedium;
   sib3->sfHigh                              = 
      lteeNodeBparams[cellCfgIdx].lteCellSib3CfgGrp.sfHigh;
   /*Updating the mobility state parameters*/
   sib3->mobStateParams.tEvalulation         = mobStateParams->tEvalulation;
   sib3->mobStateParams.tHystNormal          = mobStateParams->tHystNormal;
   sib3->mobStateParams.nCellChangeMedium    = (U16)wrSmDfltS3nCellChangeMedium;
   sib3->mobStateParams.nCellChangeHigh      = (U16)wrSmDfltS3nCellChangeHigh;

   /*  commenting out as these info will be filled from neighbour 
    *  configuration not from here */
   RETVOID;
} /* end of wrSmmEnbBldSib3Cfg */

/*
 *
 *       Fun:   wrSmmEnbSetBwFrmBwIdx
 *
 *       Desc:  Function which changes the bandwidth prameter depending on the 
 *              bandwidth Idx Configured configured. This Itself calls the wrSmmSetBandwidth.
 *              This function used in case of OAM.
 *
 *       Ret:   Void
 *
 *       Notes: None
 *
 *       File:  wr_smm_enb_utils.c
 *
 */

PRIVATE Void wrSmmEnbSetBwFrmBwIdx
(
 U32    bwIdx
 )
{
   switch ( bwIdx )
   {
      case MSM_LWR_BANDWIDTH_25 :
         {
            wrSmmSetBandwidth(WR_FREQ_BANDWIDTH_5MHZ,0);
         }
         break;

      case MSM_LWR_BANDWIDTH_50 :
         {
            wrSmmSetBandwidth(WR_FREQ_BANDWIDTH_10MHZ,0);
         }
         break;

      case MSM_LWR_BANDWIDTH_75 :
         {
            wrSmmSetBandwidth(WR_FREQ_BANDWIDTH_15MHZ,0);
         }
         break;

      case MSM_LWR_BANDWIDTH_100:
         {
            wrSmmSetBandwidth(WR_FREQ_BANDWIDTH_20MHZ,0);
         }
         break;

      default: /* By default 20 MHZ is configured */
         {
            WR_DBGP(WR_ERROR,(WR_PRNT_BUF,
                     "Configured Bandwidth value [%ld] is not supported. \
                     Only Bandwidth 5, 10, 15 & 20Mhz are supported.Setting to 20MHz by default\n",
                     bwIdx));
            wrSmmSetBandwidth(WR_FREQ_BANDWIDTH_20MHZ,0);
         }
         break;
   }
   RETVOID;
}

PRIVATE void wrSmmEnbBldSib8Cfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex,
 U8         cellCfgIdx 
 )
{
   LwrCellSib8CfgGrp *sib8Cfg = NULLP;
   MsmCellSib8CfgGrp *msmCellSib8Cfg = &lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp;

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_SIB8;

   sib8Cfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.sib8CfgGrp);
   sib8Cfg->cdmaEutraTimeSync = msmCellSib8Cfg->cdmaEutraTimeSync;
   sib8Cfg->sfMedium = msmCellSib8Cfg->sfMedium; 
   sib8Cfg->sfHigh = msmCellSib8Cfg->sfHigh;
   sib8Cfg->tReselection = msmCellSib8Cfg->tReselection;

   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.pres = wrSmDfltCdma1xrttRegSup;/*RRC Rel 10 Upgrade*/
   /*wrSmDfltCdma1xrttRegSup is set to TRUE by default. configurability to be supported
     in the future*/
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.sid = \
                                                     msmCellSib8Cfg->cdma1xrttRegParams.sid;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.nid = \
                                                     msmCellSib8Cfg->cdma1xrttRegParams.nid;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.mulSID = 
      msmCellSib8Cfg->cdma1xrttRegParams.mulSID;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.mulNID =  \
                                                         msmCellSib8Cfg->cdma1xrttRegParams.mulNID;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.homeReg = \
                                                         msmCellSib8Cfg->cdma1xrttRegParams.homeReg;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.foreignSIDReg = \
                                                               msmCellSib8Cfg->cdma1xrttRegParams.foreignSIDReg;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.foreignNIDReg = \
                                                               msmCellSib8Cfg->cdma1xrttRegParams.foreignNIDReg;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.paramReg = \
                                                          msmCellSib8Cfg->cdma1xrttRegParams.paramReg;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.powerUpReg = \
                                                            msmCellSib8Cfg->cdma1xrttRegParams.powerUpReg;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.regPeriod = \
                                                           msmCellSib8Cfg->cdma1xrttRegParams.regPeriod;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.regZone = \
                                                         msmCellSib8Cfg->cdma1xrttRegParams.regZone;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.totalZone = \
                                                           msmCellSib8Cfg->cdma1xrttRegParams.totalZone;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.zoneTimer = \
                                                           msmCellSib8Cfg->cdma1xrttRegParams.zoneTimer;
   sib8Cfg->cdma1xrttParams.cdma1xrttRegParams.powerDownRegPres = 
      msmCellSib8Cfg->cdma1xrttRegParams.powerDownReg;

   sib8Cfg->cdma1xrttParams.cdma1xrttACBarringCfg.pres = PRSNT_NODEF; 
   sib8Cfg->cdma1xrttParams.cdma1xrttACBarringCfg.acBarring0to9_r9 = \
                                                                     lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring0to9_r9;
   sib8Cfg->cdma1xrttParams.cdma1xrttACBarringCfg.acBarring10_r9 = \
                                                                   lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring10_r9;
   sib8Cfg->cdma1xrttParams.cdma1xrttACBarringCfg.acBarring11_r9 = \
                                                                   lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring11_r9;
   sib8Cfg->cdma1xrttParams.cdma1xrttACBarringCfg.acBarring12_r9 = \
                                                                   lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring12_r9;
   sib8Cfg->cdma1xrttParams.cdma1xrttACBarringCfg.acBarring13_r9 = \
                                                                   lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring13_r9;
   sib8Cfg->cdma1xrttParams.cdma1xrttACBarringCfg.acBarring14_r9 = \
                                                                   lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring14_r9;
   sib8Cfg->cdma1xrttParams.cdma1xrttACBarringCfg.acBarring15_r9 = \
                                                                   lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring15_r9;
   sib8Cfg->cdma1xrttParams.cdma1xrttACBarringCfg.acBarringMsg_r9 = \
                                                                    lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_BarringMsg_r9;
   sib8Cfg->cdma1xrttParams.cdma1xrttACBarringCfg.acBarringReg_r9 = \
                                                                    lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_BarringReg_r9;
   sib8Cfg->cdma1xrttParams.cdma1xrttACBarringCfg.acBarringEmg_r9 = \
                                                                    lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_BarringEmg_r9;

} /* end of smBldSib8Cfg */
 /* end of wrSmmEnbBldSib8Cfg */
/*
 *
 *       Fun:   wrSmmEnbBldRabPolicy
 *
 *       Desc:  fill in rab policy for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_smm_enb_utils.c 
 *
 */

PRIVATE Void wrSmmEnbBldRabPolicy
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex,
 U8         cellCfgIdx
 )
{
   LwrRabPolicyCfgGrp  *rabPolicyCfg = NULLP;
   U8                  qciIdx = 0;

   TRC2(wrSmmEnbBldRabPolicy);


   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_RAB_PARAMS;
   rabPolicyCfg= &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.rabPolicyCfgGrp);
   rabPolicyCfg->arpForEmergencyServ = 
      lteeNodeBparams[cellCfgIdx].lteAddCellCfg.emergencyServicePriorityLevel;
   rabPolicyCfg->numDrbPolicies=WR_MAX_QCI;
   for(qciIdx=0; qciIdx<rabPolicyCfg->numDrbPolicies; qciIdx++)
   {
      if(lteeNodeBparams[cellCfgIdx].lteRabPolicyCfgGrp.isDscpEnable==TRUE)
      {
         rabPolicyCfg->drbPolicy[qciIdx].qciInfo.qciSupported=TRUE;
         rabPolicyCfg->drbPolicy[qciIdx].qci=(qciIdx+1);
         rabPolicyCfg->drbPolicy[qciIdx].dscpInfo.qci=(qciIdx+1);
         rabPolicyCfg->drbPolicy[qciIdx].dscpInfo.dscp= 
            lteeNodeBparams[cellCfgIdx].lteRabPolicyCfgGrp.drbPolicy[qciIdx].dscpInfo.dscp;
      }
      else
      {
         rabPolicyCfg->drbPolicy[qciIdx].qciInfo.qciSupported=TRUE;
         rabPolicyCfg->drbPolicy[qciIdx].qci=(qciIdx+1);
         rabPolicyCfg->drbPolicy[qciIdx].dscpInfo.qci=(qciIdx+1);
         rabPolicyCfg->drbPolicy[qciIdx].dscpInfo.dscp= 0;
      } 
   }

   rabPolicyCfg->drbPolicy[0].rlcInfo.rlcMode = WR_RLC_UM_MODE;
   rabPolicyCfg->drbPolicy[0].rlcInfo.ulSnFieldLength = 
      NhuSN_FieldLengthsize5Enum;
   rabPolicyCfg->drbPolicy[0].rlcInfo.dlSnFieldLength = 
      NhuSN_FieldLengthsize10Enum;
   rabPolicyCfg->drbPolicy[0].rlcInfo.ulTimerReordering = 
      wrSmDfltUlDrbtReordring;
   rabPolicyCfg->drbPolicy[0].rlcInfo.dlTimerReordering = 
      wrSmDfltDlDrbtReordring;
   rabPolicyCfg->drbPolicy[0].pdcpInfo.umSnSize = 
      NhuPDCP_Configrlc_UMpdcp_SN_Sizelen7bitsEnum;
   rabPolicyCfg->drbPolicy[0].pdcpInfo.discardTimer = 
      NhuPDCP_ConfigdiscardTimerinfinityEnum;
   rabPolicyCfg->drbPolicy[0].pdcpInfo.statRprtReqrd = TRUE;
   rabPolicyCfg->drbPolicy[0].lchInfo.lchPriority        = 
      wrSmDfltPrioInfoTbl.drb[1].lchPriority;
   rabPolicyCfg->drbPolicy[0].lchInfo.prioritisedBitRate = 
      wrSmDfltPrioInfoTbl.drb[1].pbr;
   rabPolicyCfg->drbPolicy[0].lchInfo.bcketSizeDurn      = 
      wrSmDfltPrioInfoTbl.drb[1].bucketSizeDur;

   rabPolicyCfg->drbPolicy[1].rlcInfo.rlcMode = WR_RLC_UM_MODE;
   rabPolicyCfg->drbPolicy[1].rlcInfo.ulSnFieldLength = 
      NhuSN_FieldLengthsize5Enum;
   rabPolicyCfg->drbPolicy[1].rlcInfo.dlSnFieldLength = 
      NhuSN_FieldLengthsize10Enum;
   rabPolicyCfg->drbPolicy[1].rlcInfo.ulTimerReordering = 
      wrSmDfltUlDrbtReordring;
   rabPolicyCfg->drbPolicy[1].rlcInfo.dlTimerReordering = 
      wrSmDfltDlDrbtReordring;
   rabPolicyCfg->drbPolicy[1].pdcpInfo.umSnSize = 
      NhuPDCP_Configrlc_UMpdcp_SN_Sizelen7bitsEnum;
   rabPolicyCfg->drbPolicy[1].pdcpInfo.discardTimer = 
      NhuPDCP_ConfigdiscardTimerinfinityEnum;
   rabPolicyCfg->drbPolicy[1].pdcpInfo.statRprtReqrd = TRUE;
   rabPolicyCfg->drbPolicy[1].lchInfo.lchPriority    = 
      wrSmDfltPrioInfoTbl.drb[2].lchPriority;
   rabPolicyCfg->drbPolicy[1].lchInfo.prioritisedBitRate = 
      wrSmDfltPrioInfoTbl.drb[2].pbr;
   rabPolicyCfg->drbPolicy[1].lchInfo.bcketSizeDurn      = 
      wrSmDfltPrioInfoTbl.drb[2].bucketSizeDur;

   rabPolicyCfg->drbPolicy[2].rlcInfo.rlcMode = WR_RLC_UM_MODE;
   rabPolicyCfg->drbPolicy[2].rlcInfo.ulSnFieldLength = 
      NhuSN_FieldLengthsize5Enum;
   rabPolicyCfg->drbPolicy[2].rlcInfo.dlSnFieldLength = 
      NhuSN_FieldLengthsize10Enum;
   rabPolicyCfg->drbPolicy[2].rlcInfo.ulTimerReordering = 
      wrSmDfltUlDrbtReordring;
   rabPolicyCfg->drbPolicy[2].rlcInfo.dlTimerReordering = 
      wrSmDfltDlDrbtReordring;
   rabPolicyCfg->drbPolicy[2].pdcpInfo.umSnSize = 
      NhuPDCP_Configrlc_UMpdcp_SN_Sizelen7bitsEnum;
   rabPolicyCfg->drbPolicy[2].pdcpInfo.discardTimer = 
      NhuPDCP_ConfigdiscardTimerinfinityEnum;
   rabPolicyCfg->drbPolicy[2].pdcpInfo.statRprtReqrd = TRUE;
   rabPolicyCfg->drbPolicy[2].lchInfo.lchPriority     = 
      wrSmDfltPrioInfoTbl.drb[3].lchPriority;
   rabPolicyCfg->drbPolicy[2].lchInfo.prioritisedBitRate = 
      wrSmDfltPrioInfoTbl.drb[3].pbr;
   rabPolicyCfg->drbPolicy[2].lchInfo.bcketSizeDurn      = 
      wrSmDfltPrioInfoTbl.drb[3].bucketSizeDur;

   rabPolicyCfg->drbPolicy[3].rlcInfo.rlcMode = WR_RLC_UM_MODE;
   rabPolicyCfg->drbPolicy[3].rlcInfo.ulSnFieldLength = 
      NhuSN_FieldLengthsize5Enum;
   rabPolicyCfg->drbPolicy[3].rlcInfo.dlSnFieldLength = 
      NhuSN_FieldLengthsize10Enum;
   rabPolicyCfg->drbPolicy[3].rlcInfo.ulTimerReordering = 
      wrSmDfltUlDrbtReordring;
   rabPolicyCfg->drbPolicy[3].rlcInfo.dlTimerReordering = 
      wrSmDfltDlDrbtReordring;
   rabPolicyCfg->drbPolicy[3].pdcpInfo.umSnSize = 
      NhuPDCP_Configrlc_UMpdcp_SN_Sizelen7bitsEnum;
   rabPolicyCfg->drbPolicy[3].pdcpInfo.discardTimer = 
      NhuPDCP_ConfigdiscardTimerinfinityEnum;
   rabPolicyCfg->drbPolicy[3].pdcpInfo.statRprtReqrd = TRUE;
   rabPolicyCfg->drbPolicy[3].lchInfo.lchPriority       = 
      wrSmDfltPrioInfoTbl.drb[4].lchPriority;
   rabPolicyCfg->drbPolicy[3].lchInfo.prioritisedBitRate = 
      wrSmDfltPrioInfoTbl.drb[4].pbr;
   rabPolicyCfg->drbPolicy[3].lchInfo.bcketSizeDurn      = 
      wrSmDfltPrioInfoTbl.drb[4].bucketSizeDur;


   rabPolicyCfg->drbPolicy[4].rlcInfo.rlcMode = WR_RLC_AM_MODE;
   rabPolicyCfg->drbPolicy[4].rlcInfo.ulTimerStatusProhibit = 
      NhuT_StatusProhibitms10Enum; 
   rabPolicyCfg->drbPolicy[4].rlcInfo.ulTimerReordering = 
      wrSmDfltUlDrbtReordring;
   rabPolicyCfg->drbPolicy[4].rlcInfo.ulPollByte = NhuPollBytekBinfinityEnum;
   rabPolicyCfg->drbPolicy[4].rlcInfo.ulPollPdu = NhuPollPDUp16Enum; 
   rabPolicyCfg->drbPolicy[4].rlcInfo.ulTpRetransmit = 
      NhuT_PollRetransmitms400Enum;
   rabPolicyCfg->drbPolicy[4].rlcInfo.ulMaxRetransThresh = 
      NhuUL_AM_RLCmaxRetxThresholdt8Enum;
   rabPolicyCfg->drbPolicy[4].rlcInfo.dlTimerStatusProhibit = 
      NhuT_StatusProhibitms35Enum;
   rabPolicyCfg->drbPolicy[4].rlcInfo.dlTimerReordering = 
      wrSmDfltDlDrbtReordring; 
   rabPolicyCfg->drbPolicy[4].rlcInfo.dlPollByte = NhuPollBytekBinfinityEnum; 
   rabPolicyCfg->drbPolicy[4].rlcInfo.dlPollPdu = NhuPollPDUp8Enum; 
   rabPolicyCfg->drbPolicy[4].rlcInfo.dlTpRetransmit = 
      NhuT_PollRetransmitms400Enum;
   rabPolicyCfg->drbPolicy[4].rlcInfo.dlMaxRetransThresh = 
      NhuPDCP_ConfigdiscardTimerinfinityEnum; 
   rabPolicyCfg->drbPolicy[4].pdcpInfo.discardTimer = 
      NhuPDCP_ConfigdiscardTimerinfinityEnum;
   rabPolicyCfg->drbPolicy[4].pdcpInfo.statRprtReqrd = TRUE;
   rabPolicyCfg->drbPolicy[4].lchInfo.lchPriority        = 
      wrSmDfltPrioInfoTbl.drb[5].lchPriority;
   rabPolicyCfg->drbPolicy[4].lchInfo.prioritisedBitRate = 
      wrSmDfltPrioInfoTbl.drb[5].pbr;
   rabPolicyCfg->drbPolicy[4].lchInfo.bcketSizeDurn      = 
      wrSmDfltPrioInfoTbl.drb[5].bucketSizeDur;

   rabPolicyCfg->drbPolicy[5].rlcInfo.rlcMode = WR_RLC_AM_MODE;
   rabPolicyCfg->drbPolicy[5].rlcInfo.ulTimerStatusProhibit = 
      NhuT_StatusProhibitms10Enum; 
   rabPolicyCfg->drbPolicy[5].rlcInfo.ulTimerReordering = 
      NhuT_Reorderingms30Enum;
   rabPolicyCfg->drbPolicy[5].rlcInfo.ulPollByte = NhuPollBytekBinfinityEnum;
   rabPolicyCfg->drbPolicy[5].rlcInfo.ulPollPdu = NhuPollPDUp16Enum; 
   rabPolicyCfg->drbPolicy[5].rlcInfo.ulTpRetransmit = 
      NhuT_PollRetransmitms400Enum;
   rabPolicyCfg->drbPolicy[5].rlcInfo.ulMaxRetransThresh = 
      NhuUL_AM_RLCmaxRetxThresholdt8Enum;
   rabPolicyCfg->drbPolicy[5].rlcInfo.dlTimerStatusProhibit = 
      NhuT_StatusProhibitms40Enum;
   rabPolicyCfg->drbPolicy[5].rlcInfo.dlTimerReordering = 
      wrSmDfltDlDrbtReordring; 
   rabPolicyCfg->drbPolicy[5].rlcInfo.dlPollByte = NhuPollBytekBinfinityEnum; 
   rabPolicyCfg->drbPolicy[5].rlcInfo.dlPollPdu = NhuPollPDUp16Enum; 
   rabPolicyCfg->drbPolicy[5].rlcInfo.dlTpRetransmit = 
      NhuT_PollRetransmitms400Enum;
   rabPolicyCfg->drbPolicy[5].rlcInfo.dlMaxRetransThresh = 
      NhuPDCP_ConfigdiscardTimerinfinityEnum; 
   rabPolicyCfg->drbPolicy[5].pdcpInfo.discardTimer = 
      NhuPDCP_ConfigdiscardTimerinfinityEnum;
   rabPolicyCfg->drbPolicy[5].pdcpInfo.statRprtReqrd = TRUE;
   rabPolicyCfg->drbPolicy[5].lchInfo.lchPriority        = 
      wrSmDfltPrioInfoTbl.drb[6].lchPriority;
   rabPolicyCfg->drbPolicy[5].lchInfo.prioritisedBitRate = 
      wrSmDfltPrioInfoTbl.drb[6].pbr;
   rabPolicyCfg->drbPolicy[5].lchInfo.bcketSizeDurn      = 
      wrSmDfltPrioInfoTbl.drb[6].bucketSizeDur;

   rabPolicyCfg->drbPolicy[6].rlcInfo.rlcMode = WR_RLC_AM_MODE;
   rabPolicyCfg->drbPolicy[6].rlcInfo.ulTimerStatusProhibit = 
      NhuT_StatusProhibitms35Enum; 
   rabPolicyCfg->drbPolicy[6].rlcInfo.ulTimerReordering = 
      wrSmDfltUlDrbtReordring;
   rabPolicyCfg->drbPolicy[6].rlcInfo.ulPollByte = NhuPollBytekBinfinityEnum;
   rabPolicyCfg->drbPolicy[6].rlcInfo.ulPollPdu = NhuPollPDUp16Enum; 
   rabPolicyCfg->drbPolicy[6].rlcInfo.ulTpRetransmit = 
      NhuT_PollRetransmitms400Enum;
   rabPolicyCfg->drbPolicy[6].rlcInfo.ulMaxRetransThresh = 
      NhuUL_AM_RLCmaxRetxThresholdt8Enum;
   rabPolicyCfg->drbPolicy[6].rlcInfo.dlTimerStatusProhibit = 
      NhuT_StatusProhibitms5Enum;
   rabPolicyCfg->drbPolicy[6].rlcInfo.dlTimerReordering = 
      wrSmDfltDlDrbtReordring; 
   rabPolicyCfg->drbPolicy[6].rlcInfo.dlPollByte = NhuPollBytekBinfinityEnum; 
   rabPolicyCfg->drbPolicy[6].rlcInfo.dlPollPdu = NhuPollPDUp16Enum; 
   rabPolicyCfg->drbPolicy[6].rlcInfo.dlTpRetransmit = 
      NhuT_PollRetransmitms400Enum;
   rabPolicyCfg->drbPolicy[6].rlcInfo.dlMaxRetransThresh = 
      NhuUL_AM_RLCmaxRetxThresholdt8Enum; 
   rabPolicyCfg->drbPolicy[6].pdcpInfo.discardTimer = 
      NhuPDCP_ConfigdiscardTimerinfinityEnum;
   rabPolicyCfg->drbPolicy[6].pdcpInfo.statRprtReqrd = TRUE;
   rabPolicyCfg->drbPolicy[6].lchInfo.lchPriority     = 
      wrSmDfltPrioInfoTbl.drb[7].lchPriority;
   rabPolicyCfg->drbPolicy[6].lchInfo.prioritisedBitRate = 
      wrSmDfltPrioInfoTbl.drb[7].pbr;
   rabPolicyCfg->drbPolicy[6].lchInfo.bcketSizeDurn      = 
      wrSmDfltPrioInfoTbl.drb[7].bucketSizeDur;

   rabPolicyCfg->drbPolicy[7].rlcInfo.rlcMode = WR_RLC_AM_MODE;
   rabPolicyCfg->drbPolicy[7].rlcInfo.ulTimerStatusProhibit = 
      NhuT_StatusProhibitms35Enum; 
   rabPolicyCfg->drbPolicy[7].rlcInfo.ulTimerReordering = 
      wrSmDfltUlDrbtReordring;
   rabPolicyCfg->drbPolicy[7].rlcInfo.ulPollByte = 
      NhuPollBytekBinfinityEnum;
   rabPolicyCfg->drbPolicy[7].rlcInfo.ulPollPdu = NhuPollPDUp16Enum; 
   rabPolicyCfg->drbPolicy[7].rlcInfo.ulTpRetransmit = 
      NhuT_PollRetransmitms400Enum;
   rabPolicyCfg->drbPolicy[7].rlcInfo.ulMaxRetransThresh = 
      NhuUL_AM_RLCmaxRetxThresholdt8Enum;
   rabPolicyCfg->drbPolicy[7].rlcInfo.dlTimerStatusProhibit = 
      NhuT_StatusProhibitms35Enum;
   rabPolicyCfg->drbPolicy[7].rlcInfo.dlTimerReordering = 
      wrSmDfltDlDrbtReordring; 
   rabPolicyCfg->drbPolicy[7].rlcInfo.dlPollByte = NhuPollBytekBinfinityEnum; 
   rabPolicyCfg->drbPolicy[7].rlcInfo.dlPollPdu = NhuPollPDUp16Enum; 
   rabPolicyCfg->drbPolicy[7].rlcInfo.dlTpRetransmit = 
      NhuT_PollRetransmitms400Enum;
   rabPolicyCfg->drbPolicy[7].rlcInfo.dlMaxRetransThresh = 
      NhuUL_AM_RLCmaxRetxThresholdt8Enum; 
   rabPolicyCfg->drbPolicy[7].pdcpInfo.discardTimer = 
      NhuPDCP_ConfigdiscardTimerinfinityEnum;
   rabPolicyCfg->drbPolicy[7].pdcpInfo.statRprtReqrd = TRUE;
   rabPolicyCfg->drbPolicy[7].lchInfo.lchPriority   = 
      wrSmDfltPrioInfoTbl.drb[8].lchPriority;
   rabPolicyCfg->drbPolicy[7].lchInfo.prioritisedBitRate = 
      wrSmDfltPrioInfoTbl.drb[8].pbr;
   rabPolicyCfg->drbPolicy[7].lchInfo.bcketSizeDurn  = 
      wrSmDfltPrioInfoTbl.drb[8].bucketSizeDur;

   rabPolicyCfg->drbPolicy[8].rlcInfo.rlcMode = WR_RLC_AM_MODE;
   rabPolicyCfg->drbPolicy[8].rlcInfo.ulTimerStatusProhibit = 
      NhuT_StatusProhibitms35Enum; 
   rabPolicyCfg->drbPolicy[8].rlcInfo.ulTimerReordering = 
      wrSmDfltUlDrbtReordring;
   rabPolicyCfg->drbPolicy[8].rlcInfo.ulPollByte = NhuPollBytekBinfinityEnum;
   rabPolicyCfg->drbPolicy[8].rlcInfo.ulPollPdu = NhuPollPDUp16Enum; 
   rabPolicyCfg->drbPolicy[8].rlcInfo.ulTpRetransmit = 
      NhuT_PollRetransmitms400Enum;
   rabPolicyCfg->drbPolicy[8].rlcInfo.ulMaxRetransThresh = 
      NhuUL_AM_RLCmaxRetxThresholdt8Enum;
   rabPolicyCfg->drbPolicy[8].rlcInfo.dlTimerStatusProhibit = 
      NhuT_StatusProhibitms35Enum;
   rabPolicyCfg->drbPolicy[8].rlcInfo.dlTimerReordering = 
      wrSmDfltDlDrbtReordring; 
   rabPolicyCfg->drbPolicy[8].rlcInfo.dlPollByte = NhuPollBytekBinfinityEnum; 
   rabPolicyCfg->drbPolicy[8].rlcInfo.dlPollPdu = NhuPollPDUp16Enum; 
   rabPolicyCfg->drbPolicy[8].rlcInfo.dlTpRetransmit = 
      NhuT_PollRetransmitms400Enum;
   rabPolicyCfg->drbPolicy[8].rlcInfo.dlMaxRetransThresh = 
      NhuUL_AM_RLCmaxRetxThresholdt8Enum; 
   rabPolicyCfg->drbPolicy[8].pdcpInfo.discardTimer = 
      NhuPDCP_ConfigdiscardTimerinfinityEnum;
   rabPolicyCfg->drbPolicy[8].pdcpInfo.statRprtReqrd = TRUE;
   rabPolicyCfg->drbPolicy[8].lchInfo.lchPriority        = 
      wrSmDfltPrioInfoTbl.drb[9].lchPriority;
   rabPolicyCfg->drbPolicy[8].lchInfo.prioritisedBitRate = 
      wrSmDfltPrioInfoTbl.drb[9].pbr;
   rabPolicyCfg->drbPolicy[8].lchInfo.bcketSizeDurn      = 
      wrSmDfltPrioInfoTbl.drb[9].bucketSizeDur;

   RETVOID;
} /* end of wrSmmEnbBldRabPolicy */


/*
 *
 *       Fun: wrSmmEnbBuildMobParams - Fill Mobility parameters
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enb_utils.c
 *
 */

PRIVATE S16 wrSmmEnbBuildMobParams
(
 LwrCdma2k1xMobParams *mobParams,
 U8  cellCfgIdx
 )
{
   MsmCdmaMobilityParam *mobParam;

   mobParam = &(lteeNodeBparams[cellCfgIdx].cdmaMobilityParam);

   mobParams->sidIncl = mobParam->sidIncl; 
   mobParams->sid = mobParam->sid;
   mobParams->nidIncl = mobParam->nidIncl;
   mobParams->nid = mobParam->nid;
   mobParams->multSidsIncl = mobParam->multSidsIncl;
   mobParams->multSids = mobParam->multSids;
   mobParams->multNidsIncl = mobParam->multNidsIncl;
   mobParams->multNids = mobParam->multNids;
   mobParams->regZoneIncl = mobParam->regZoneIncl;
   mobParams->regZone = mobParam->regZone;
   mobParams->totalZonesIncl = mobParam->totalZonesIncl;
   mobParams->totalZones = mobParam->totalZones;
   mobParams->zoneTimerIncl = mobParam->zoneTimerIncl;
   mobParams->zoneTimer = mobParam->zoneTimer;
   mobParams->pktZoneIdIncl = mobParam->pktZoneIdIncl;
   mobParams->pktZoneId = mobParam->pktZoneId;
   mobParams->pzIdHysParamIncl = mobParam->pzIdHysParamIncl;
   mobParams->pzHystEnabled = mobParam->pzHystEnabled;
   mobParams->pzHystInfoIncl = mobParam->pzHystInfoIncl;
   mobParams->pzHystListLen = mobParam->pzHystListLen;
   mobParams->pzHystActTimer = mobParam->pzHystActTimer;
   mobParams->pzHystTimerMul = mobParam->pzHystTimerMul;
   mobParams->pzHystTimerExp = mobParam->pzHystTimerExp;
   mobParams->pRevIncl = mobParam->pRevIncl;
   mobParams->pRev = mobParam->pRev;
   mobParams->minPRevIncl = mobParam->minPRevIncl;
   mobParams->minPRev = mobParam->minPRev;
   mobParams->negSlotCycIndxSupIncl = mobParam->negSlotCycIndxSupIncl;
   mobParams->negSlotCycIndxSup = mobParam->negSlotCycIndxSup;
   mobParams->encModeIncl = mobParam->encModeIncl;
   mobParams->encMode = mobParam->encMode;
   mobParams->encSupIncl = mobParam->encSupIncl;
   mobParams->encSup = mobParam->encSup;
   mobParams->sigEncSupIncl = mobParam->sigEncSupIncl;
   mobParams->sigEncSup = mobParam->sigEncSup;
   mobParams->msgIntSupIncl = mobParam->msgIntSupIncl;
   mobParams->msgIntSup = mobParam->msgIntSup;
   mobParams->sigIntSupINCLIncl = mobParam->sigIntSupINCLIncl;
   mobParams->sigIntSupINCL = mobParam->sigIntSupINCL;
   mobParams->sigIntSupIncl = mobParam->sigIntSupIncl;
   mobParams->sigIntSup = mobParam->sigIntSup;
   mobParams->authIncl = mobParam->authIncl;
   mobParams->auth = mobParam->auth;
   mobParams->maxNumAltoSoIncl = mobParam->maxNumAltoSoIncl;
   mobParams->maxNumAltoSo = mobParam->maxNumAltoSo;
   mobParams->useSyncIdIncl = mobParam->useSyncIdIncl;
   mobParams->useSyncId = mobParam->useSyncId;
   mobParams->msInitPosLocSupIndIncl = mobParam->msInitPosLocSupIndIncl;
   mobParams->msInitPosLocSupInd = mobParam->msInitPosLocSupInd;
   mobParams->mobQosIncl = mobParam->mobQosIncl;
   mobParams->mobQos = mobParam->mobQos;
   mobParams->bandClsInfoReqIncl = mobParam->bandClsInfoReqIncl;
   mobParams->bandClsInfoReq = mobParam->bandClsInfoReq;
   mobParams->bandClsIncl = mobParam->bandClsIncl;
   mobParams->bandCls = mobParam->bandCls;
   mobParams->bypassRegIndIncl = mobParam->bypassRegIndIncl;
   mobParams->bypassRegInd = mobParam->bypassRegInd;
   mobParams->altBandClsIncl = mobParam->altBandClsIncl;
   mobParams->altBandCls = mobParam->altBandCls;
   mobParams->maxAddServInstIncl = mobParam->maxAddServInstIncl;
   mobParams->maxAddServInst = mobParam->maxAddServInst;
   mobParams->homeRegIncl = mobParam->homeRegIncl;
   mobParams->homeReg = mobParam->homeReg;
   mobParams->forSidRegIncl = mobParam->forSidRegIncl;
   mobParams->forSidReg = mobParam->forSidReg;
   mobParams->forNidRegIncl = mobParam->forNidRegIncl;
   mobParams->forNidReg = mobParam->forNidReg;
   mobParams->powerUpRegIncl = mobParam->powerUpRegIncl;
   mobParams->powerUpReg = mobParam->powerUpReg;
   mobParams->powerDownRegIncl = mobParam->powerDownRegIncl;
   mobParams->powerDownReg = mobParam->powerDownReg;
   mobParams->parmRegIncl = mobParam->parmRegIncl;
   mobParams->parmReg = mobParam->parmReg;
   mobParams->regPrdIncl = mobParam->regPrdIncl;
   mobParams->regPrd = mobParam->regPrd;
   mobParams->regDistIncl = mobParam->regDistIncl;
   mobParams->regDist = mobParam->regDist;
   mobParams->prefMsIdTypeIncl = mobParam->prefMsIdTypeIncl;
   mobParams->prefMsIdType = mobParam->prefMsIdType;
   mobParams->extPrefMsIdTypeIncl = mobParam->extPrefMsIdTypeIncl;
   mobParams->extPrefMsIdType = mobParam->extPrefMsIdType;
   mobParams->meIdReqdIncl = mobParam->meIdReqdIncl;
   mobParams->meIdReqd = mobParam->meIdReqd;
   mobParams->mccIncl = mobParam->mccIncl;
   mobParams->mcc = mobParam->mcc;
   mobParams->imsi1112Incl = mobParam->imsi1112Incl;
   mobParams->imsi1112 = mobParam->imsi1112;
   mobParams->imsiTSupIncl = mobParam->imsiTSupIncl;
   mobParams->imsiTSup = mobParam->imsiTSup;
   mobParams->recntMsgIndIncl = mobParam->recntMsgIndIncl;
   mobParams->recntMsgInd = mobParam->recntMsgInd;
   mobParams->rerModeSupIncl = mobParam->rerModeSupIncl;
   mobParams->rerModeSup = mobParam->rerModeSup;
   mobParams->tzkModeSupIncl = mobParam->tzkModeSupIncl;
   mobParams->tzkModeSup = mobParam->tzkModeSup;
   mobParams->tzkIdIncl = mobParam->tzkIdIncl;
   mobParams->tzkId = mobParam->tzkId;
   mobParams->pilRepIncl = mobParam->pilRepIncl;
   mobParams->pilRep = mobParam->pilRep;
   mobParams->sdbSupIncl = mobParam->sdbSupIncl;
   mobParams->sdbSup = mobParam->sdbSup;
   mobParams->autoFcsoAllIncl = mobParam->autoFcsoAllIncl;
   mobParams->autoFcsoAll = mobParam->autoFcsoAll;
   mobParams->sdbInRcnmIncl = mobParam->sdbInRcnmIncl;
   mobParams->sdbInRcnm = mobParam->sdbInRcnm;
   mobParams->fpcFchIncl = mobParam->fpcFchIncl;
   mobParams->fpcFchInitSetptRC3 = mobParam->fpcFchInitSetptRC3;
   mobParams->fpcFchInitSetptRC4 = mobParam->fpcFchInitSetptRC4;
   mobParams->fpcFchInitSetptRC5 = mobParam->fpcFchInitSetptRC5;
   mobParams->fpcFchInitSetptRC11 = mobParam->fpcFchInitSetptRC11;
   mobParams->fpcFchInitSetptRC12 = mobParam->fpcFchInitSetptRC12;
   mobParams->tAddIncl = mobParam->tAddIncl;
   mobParams->tAdd = mobParam->tAdd;
   mobParams->pilotIncIncl = mobParam->pilotIncIncl;
   mobParams->PilotInc = mobParam->pilotInc;
   mobParams->randIncl = mobParam->randIncl;
   mobParams->rand = mobParam->rand;
   mobParams->lpSecIncl = mobParam->lpSecIncl;
   mobParams->lpSec = mobParam->lpSec;
   mobParams->ltmOffIncl = mobParam->ltmOffIncl;
   mobParams->ltmOff = mobParam->ltmOff;
   mobParams->dayltIncl = mobParam->dayltIncl;
   mobParams->daylt = mobParam->daylt;
   mobParams->gcsnaL2ActTimerIncl = mobParam->gcsnaL2ActTimerIncl;
   mobParams->gcsnaL2ActTimer = mobParam->gcsnaL2ActTimer;
   mobParams->gcsnaSeqCtxtTimerIncl = mobParam->gcsnaSeqCtxtTimerIncl;
   mobParams->gcsnaSeqCtxtTimer = mobParam->gcsnaSeqCtxtTimer;

   RETVALUE(ROK);
} /* end of wrSmmEnbBuildMobParams */ 

/** @brief This function is responsible for retrieving the pciRange
 *         and checking whether the final PCI is in the valid region
 *         of 0 to 503. If not set to default values.
 *
 * @details
 *
 *     Function: wrSmmEnbIsPciRangeValid
 *
 *         Processing steps:
 *         - Get the default pciRange.
 *         - Based on the Enum Value return the exact PCI Range Value. 
 *         - Add the startPci & PciRange. Check whether this added value is b/n 0-503
 *         - If not in 0 - 503 range then set to default values.
 *
 * @param[in] pciRange     : pointer to the default pciRange
 * 
 */
PRIVATE Void wrSmmEnbIsPciRangeValid
( 
 LwrSib4CsgInfo            *pciRange
 )
{
   U16        mappedPciRange = 0;
   U16        rangeofPci= 0;

   mappedPciRange = wrSmmEnbPciRangeMapping(pciRange);


   if(mappedPciRange != 0)
   {
      rangeofPci = pciRange->csgStartPhyCellId + (mappedPciRange - 1);
   }
   else
   {
      rangeofPci = pciRange->csgStartPhyCellId + mappedPciRange; 
   }

   if(rangeofPci >= 504)
   {
      RLOG2(L_ERROR, "For startPhyCellId %d and PciRange %d, the PCI is "
            "exceeding 504 So Setting pciRange to default values ",
            pciRange->csgStartPhyCellId, pciRange->csgPciRange);

      pciRange->csgStartPhyCellId = 1;
      pciRange->csgPciRange = 5;
   }
}

/** @brief This function is responsible for retrieving the Enum
 *         based on the default pciRange and Mapping it to the 
 *         exact PCI Range Value.
 *
 * @details
 *
 *     Function: wrSmmEnbPciRangeMapping
 *
 *         Processing steps:
 *         - Get the default pciRange.
 *         - Based on the Enum Value return the exact PCI Range Value. 
 *
 * @param[in] pciRange     : pointer to the default pciRange
 * 
 * @return U16
 *     -# Exact PCI Range Value
 */
PRIVATE U16 wrSmmEnbPciRangeMapping
(
 LwrSib4CsgInfo            *pciRange
 )
{
   U16   mappedPci = 0;

   if(pciRange->isCsgPciCfgd == WR_PRSNT)
   {
      switch(pciRange->csgPciRange)
      {
         case NhuPhysCellIdRangerangen4Enum : 
            mappedPci = 4;
            break;
         case NhuPhysCellIdRangerangen8Enum :
            mappedPci = 8;
            break;
         case NhuPhysCellIdRangerangen12Enum :
            mappedPci = 12;
            break;
         case NhuPhysCellIdRangerangen16Enum :
            mappedPci = 16;
            break;
         case NhuPhysCellIdRangerangen24Enum :
            mappedPci = 24;
            break;
         case NhuPhysCellIdRangerangen32Enum :    
            mappedPci = 32;
            break;
         case NhuPhysCellIdRangerangen48Enum :
            mappedPci = 48;
            break;
         case NhuPhysCellIdRangerangen64Enum :
            mappedPci = 64;
            break;
         case NhuPhysCellIdRangerangen84Enum :
            mappedPci = 84;
            break;
         case NhuPhysCellIdRangerangen96Enum :
            mappedPci = 96;
            break;
         case NhuPhysCellIdRangerangen128Enum :
            mappedPci = 128;
            break;
         case NhuPhysCellIdRangerangen168Enum :
            mappedPci = 168;
            break;
         case NhuPhysCellIdRangerangen252Enum :
            mappedPci = 252;
            break;
         case NhuPhysCellIdRangerangen504Enum :
            mappedPci = 504;
            break;
         default :
            RLOG1(L_ERROR, "PCI Range value not found for PCI entry %d",
                  pciRange->csgPciRange);
            break;
      }
   }
   RETVALUE(mappedPci);
}

#ifndef WR_RSYS_OAM
/**
 *  @brief This function validates the IpAddress read from wr_cfg.txt for MME 
 *  and  Neighbour that are stored in smCfgCb. 
 *
 *  @details  Function: wrSmmEnbValidateIpAddr 
 *          Processing steps:
 *          - Return SUCESS If:
 *                The types of IP ADDRESS supported by ENodeB should be 
 *                matched with types of IP ADDRESS supported by list of 
 *                MMEs and Neighbours. 
 *            Else
 *                Return FAILURE
 *
 *  @param[in] Void Void
 *
 *  @return S32
 *     -# Success : ROK
 *     -# Failure : RFAILED
 *
 */
#ifdef ANSI 
PUBLIC S16 wrSmmEnbValidateIpAddr
(
)
#else
PUBLIC S16 wrSmmEnbValidateIpAddr(Void)
#endif
{
   Bool          ipv4Present = FALSE;
   Bool          ipv6Present = FALSE;
   U16           cnt;
   S16           retVal = ROK;
   Bool          eNBIpv4Present = FALSE;
   Bool          eNBIpv6Present = FALSE;
   TRC2(wrSmmEnbValidateIpAddr);
   if(TRUE == fapParameters.lteEnodebIpAddr.ipv4pres)
   {
      eNBIpv4Present = TRUE; 
   }
   else if(TRUE == fapParameters.lteEnodebIpAddr.ipv6pres)
   {
      eNBIpv6Present = TRUE; 
   }
   /* Validate MME IP Addresses */
   for(cnt = 0; cnt < smCfgCb.noOfCfg; cnt++)
   {
      if(smCfgCb.mmeCfg[cnt]->mmeAddr[0].type == CM_TPTADDR_IPV4)
      {
         ipv4Present = TRUE;
      }
      else if(smCfgCb.mmeCfg[cnt]->mmeAddr[0].type == CM_TPTADDR_IPV6)
      {
         ipv6Present = TRUE;
      }
   }
   /* eNB is having IPv4 and IPv6 and MME is either IPv4 or IPv6 then it is 
    * valid configuration.
    */
   if((eNBIpv4Present == eNBIpv6Present) && (TRUE == eNBIpv4Present)) 
   {
      if((ipv4Present != TRUE) && (ipv6Present != TRUE))
      {
         RLOG0(L_ERROR, "MME and EnbIp Address configuration not valid");
         retVal = RFAILED;
         RETVALUE(retVal);
      }
   }
   /* eNB is having IPv4 and MME is having IPv4 or eNB is having IPv6
    *  and MME is having IPv6 then it is valid configuration.
    */
   if((eNBIpv4Present != ipv4Present) && (eNBIpv6Present != ipv6Present))
   {
      RLOG0(L_ERROR, "MME and EnbIp Address configuration not valid");
      retVal = RFAILED;
      RETVALUE(retVal);
   }
   if((eNBIpv4Present == ipv4Present) && (eNBIpv6Present != ipv6Present))
   {
      RLOG0(L_ERROR, "MME and EnbIp Address configuration not valid");
      retVal = RFAILED;
      RETVALUE(retVal);
   }
   if((eNBIpv6Present == ipv6Present) && (eNBIpv4Present != ipv4Present))
   {
      RLOG0(L_ERROR, "MME and EnbIp Address configuration not valid");
      retVal = RFAILED;
      RETVALUE(retVal);
   }
#if 0
   /* Validate Neighbour IP Addresses */
   ipv4Present = FALSE;
   ipv6Present = FALSE;
   for(cnt = 0; cnt < lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteNeighCellCfg.numEutraCells; cnt++)
   {
   }
   /* eNB is having IPv4 and IPv6 and Neighbour is either IPv4 or IPv6 then it is 
    * valid configuration.
    */

   if((eNBIpv4Present == eNBIpv6Present) && (TRUE == eNBIpv4Present)) 
   {
      if((ipv4Present != TRUE) && (ipv6Present != TRUE))
      {
         RLOG0(L_ERROR, "Neighbour and EnbIp Address configuration not valid");
         retVal = RFAILED;
         RETVALUE(retVal);
      }
   }
   /* eNB is having IPv4 and MME is having IPv4 or eNB is having IPv6
    *  and Neighbour is having IPv6 then it is valid configuration.
    */

   if((eNBIpv4Present != ipv4Present) && (eNBIpv6Present != ipv6Present))
   {
      RLOG0(L_ERROR, "Neighbour and EnbIp Address configuration not valid");
      retVal = RFAILED;
      RETVALUE(retVal);
   }
   if((eNBIpv4Present == ipv4Present) && (eNBIpv6Present != ipv6Present))
   {
      RLOG0(L_ERROR, "Neighbour and EnbIp Address configuration not valid");
      retVal = RFAILED;
      RETVALUE(retVal);
   }
   if((eNBIpv6Present == ipv6Present) && (eNBIpv4Present != ipv4Present))
   {
      RLOG0(L_ERROR, "Neighbour and EnbIp Address configuration not valid");
      retVal = RFAILED;
      RETVALUE(retVal);
   }
#endif
   RETVALUE(retVal);
} /*end of  wrSmmEnbValidateIpAddr*/
#endif
/* CSG_DEV start */
/*
 *
 *       Fun:   wrSmmEnbValidateConfigParams
 *
 *       Desc:  Validates the values configured from OAM in MsmLteeNodeBparams.
 *
 *       Ret:   ROK, RFAILED
 *
 *       File:  wr_smm_enb_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 wrSmmEnbValidateConfigParams
(
 U8 cellCfgIdx
 )
#else
PUBLIC S16 wrSmmEnbValidateConfigParams (cellCfgIdx)
   U8 cellCfgIdx;
#endif
{
   U8    maxCsgUes;
   U8    maxNonCsgUes;
   U8    minDlResNonCsg;
   U8    minUlResNonCsg;
   U16   maxCsgPci = 0;                                                              
   U16   maxSmallCellPci = 0;                                                        
   U16   csgPciRange = 0;                                                            
   S16   retVal = ROK;                                                               
   U16   csgStartPci = lteeNodeBparams[cellCfgIdx].lteSib4CsgInfo.csgStartPhyCellId;             
   U16   smallCellStartPci = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.startPci;                 
   U16   servingCellPci = 
      lteeNodeBparams[cellCfgIdx].lteAddCellCfg.physCellId;
   U32   csgId = lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.csgIdentity;       
   U8    accessMode = lteeNodeBparams[cellCfgIdx].lteFapAccessParams.accessMode;                 
   U8    isCsgPciCfgd = lteeNodeBparams[cellCfgIdx].lteSib4CsgInfo.isCsgPciCfgd;                 
   U8    isSmallCellPciCfgd = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.isSmallCellPciCfgd;      

   /* For serving cell validation EnbType is required */
   wrSmDfltEnbType = smGetEnbType(servingCellPci,cellCfgIdx);

   /* validate serving cell PCI */
   /* Removed one part of the check to make warning free */
   /*if (servingCellPci <  WR_PCI_MIN_VAL || servingCellPci > WR_PCI_MAX_VAL)*/

   if(WR_ENB_OPEN_ACCESS != accessMode && WR_ENODEB_TYPE_MACRO == wrSmDfltEnbType)
   {
      RLOG2(L_ERROR, "Invalid AccessMode and ENB Type Configuration: "
            "AccessMode [%d] ENB Type [%d]",
            accessMode, wrSmDfltEnbType);
      RETVALUE(RFAILED);
   }

   if(TRUE == isSmallCellPciCfgd)
   {
      maxSmallCellPci = smallCellStartPci +
         lteeNodeBparams[cellCfgIdx].lteAddCellCfg.pciRange;
      /* Removed one part of check to make warning free */   
      /*if(WR_PCI_MIN_VAL > smallCellStartPci || WR_PCI_MAX_VAL < maxSmallCellPci)*/
      if(WR_PCI_MAX_VAL < maxSmallCellPci)
      {
         RLOG2(L_ERROR, "Invalid SmallCell PCI "
               "configuration SmallCell Start PCI [%d] Max [%d]",
               smallCellStartPci, maxSmallCellPci);
         RETVALUE(RFAILED);
      }
   }
   else
   {
      RLOG1(L_ERROR, "Missing SmallCell PCI configuration AccesMode [%d]",
            accessMode);
      RETVALUE(RFAILED);
   }

   if(TRUE == lteeNodeBparams[cellCfgIdx].lteSib4CsgInfo.isCsgPciCfgd)
   {
      WR_EMM_GET_PCI_RANGE(lteeNodeBparams[cellCfgIdx].lteSib4CsgInfo.csgPciRange,
            csgPciRange);
      maxCsgPci = csgStartPci + csgPciRange;
      /* Removed one part of check to make warning free */
      /*if(WR_PCI_MIN_VAL > csgStartPci || WR_PCI_MAX_VAL < maxCsgPci)*/
      if(WR_PCI_MAX_VAL < maxCsgPci)
      {
         lteeNodeBparams[cellCfgIdx].lteSib4CsgInfo.isCsgPciCfgd = FALSE;
         RLOG2(L_ERROR, "Ingnoring invalid CSG PCI OPEN Access "
               "configuration CSG Start PCI [%d] Max [%d]",
               csgStartPci, maxCsgPci);
      }
   }

   /*GA 5.0 Changes*/
#ifndef WR_RSYS_OAM
   if(wrSmmEnbValidateIpAddr() != ROK)
   {
      RLOG0(L_ERROR, "Validation of Configuration Parameters Failed");
      RETVALUE(RFAILED);
   }
#endif
   /*GA 5.0 Changes*/

   /* CSG configuration parameter validation */
   switch(accessMode)
   {
      case WR_ENB_OPEN_ACCESS:
         {
            if(WR_ENODEB_TYPE_HOME == wrSmDfltEnbType && 
                  (((TRUE == isCsgPciCfgd) && 
                    (servingCellPci > csgStartPci &&
                     servingCellPci < maxCsgPci)) ||
                   (servingCellPci < smallCellStartPci || 
                    servingCellPci > maxSmallCellPci)))
            {
               RLOG0(L_ERROR, "Invalid PCI Configuration in OPEN Access");
               RLOG4(L_ERROR, "ENBTYPE [%d] PCI [%d] CSG Start PCI [%d] Max [%d]",
                     wrSmDfltEnbType, servingCellPci, csgStartPci, maxCsgPci);
               RLOG2(L_ERROR, "SmallCell Start PCI [%d] Max [%d]",
                     smallCellStartPci, maxSmallCellPci);
               retVal = RFAILED;
            }
            else if (WR_ENODEB_TYPE_MACRO == wrSmDfltEnbType && 
                  (((TRUE == isCsgPciCfgd) && 
                    (servingCellPci > csgStartPci &&
                     servingCellPci < maxCsgPci)) ||
                   (servingCellPci > smallCellStartPci &&
                    servingCellPci < maxSmallCellPci)))
            {
               RLOG0(L_ERROR, "Invalid PCI Configuration in OPEN Access");
               RLOG4(L_ERROR, "ENBTYPE [%d] PCI [%d] CSG Start PCI [%d] Max [%d]",
                     wrSmDfltEnbType, servingCellPci, csgStartPci, maxCsgPci);
               RLOG2(L_ERROR, "SmallCell Start PCI [%d] Max [%d]",
                     smallCellStartPci, maxSmallCellPci);
               retVal = RFAILED;
            }
         }
         break;
      case WR_ENB_CLOSED_ACCESS:
         {
            if(FALSE == isCsgPciCfgd)
            {
               RLOG0(L_ERROR, "Incomplete CLOSED Mode CSG configuration");
               RLOG3(L_ERROR, "CSG ID [%d] CSG PCI CFGD [%d] SmallCell PCI "
                     "CFGD [%d]", csgId, isCsgPciCfgd, isSmallCellPciCfgd);
               retVal = RFAILED;
            }
            else
            {
               if(0 > csgId || WR_CSG_ID_MAX_VAL < csgId)
               {
                  RLOG1(L_ERROR, "CSG ID not in range CSG ID [%d]", csgId);
                  retVal = RFAILED;
               }
               if(servingCellPci < csgStartPci || 
                     servingCellPci > maxCsgPci)
               {
                  RLOG0(L_ERROR, "Invalid PCI Configuration in CLOSED Access");
                  RLOG4(L_ERROR, "ENBTYPE [%d] PCI [%d] CSG Start PCI [%d] "
                        "Max [%d]", wrSmDfltEnbType, servingCellPci, csgStartPci,
                        maxCsgPci);
                  RLOG2(L_ERROR, "SmallCell Start PCI [%d] Max [%d]",
                        smallCellStartPci, maxSmallCellPci);
                  retVal = RFAILED;
               }
            }
         }
         break;
      case WR_ENB_HYBRID_ACCESS:
         /*GA 5.0 Changes*/
         {
            /* Validate Max number of CSG and Non CSG UEs configured */
            maxCsgUes = lteeNodeBparams[cellCfgIdx].lteFapAccessParams.maxCSGMembers;
            maxNonCsgUes = lteeNodeBparams[cellCfgIdx].lteFapAccessParams.maxNonCSGMembers;
            minDlResNonCsg = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.minDlResNonCsg;
            minUlResNonCsg = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.minUlResNonCsg;
            if((maxCsgUes > lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxUeSupp) ||
                  (maxNonCsgUes > lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxUeSupp) ||
                  ((maxNonCsgUes == maxCsgUes) &&
                   (maxCsgUes < lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxUeSupp) &&
                   ((maxCsgUes + maxNonCsgUes) != lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxUeSupp)) ||
                  ((maxCsgUes != maxNonCsgUes) &&
                   ((maxCsgUes + maxNonCsgUes) != lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxUeSupp)))
            {
               RLOG0(L_ERROR, "Invalid number of CSG or Non CSG UEs configured");
               RLOG3(L_ERROR, "Non CSG UE CFGD [%d] CSG UE CFGD "
                     "[%d] Max UE Supported [%d]", maxNonCsgUes,
                     maxCsgUes, lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxUeSupp);
               RETVALUE(RFAILED);
            }
            /* Validate minimum number of UL and DL resources configured  */
            if(minDlResNonCsg > 100)
            {
               RLOG1(L_ERROR, "Invalid number of Minimum DL Resources [%d]",
                     minDlResNonCsg);
               RETVALUE(RFAILED);
            }
            if(minUlResNonCsg > 100)
            {
               RLOG1(L_ERROR, "Invalid number of Minimum UL Resources [%d]",
                     minUlResNonCsg);
               RETVALUE(RFAILED);
            }
         }
         break;
      default:
         {
            RLOG1(L_ERROR, "Invalid Access Mode configuration [%d]",
                  accessMode);
            retVal = RFAILED;
         }
         break;
   }

   if(1 == lteeNodeBparams[cellCfgIdx].lteTransModeCellCfg.bIsAutoConfigEnabled)
   {
      lteeNodeBparams[cellCfgIdx].lteTransModeCellCfg.transModeUse = 4;
   }
   else
   {
      lteeNodeBparams[cellCfgIdx].lteTransModeCellCfg.transModeUse = 
         lteeNodeBparams[cellCfgIdx].lteTransModeCellCfg.preferredTransMode;
   }
   /*GA 5.0 Changes*/
   RETVALUE(retVal);
} /* end of wrSmmEnbValidateConfigParams */
/* CSG_DEV end */

/*
 *
 *       Fun:   wrSmmEnbBuildWrEnbCfg
 *
 *       Desc:  This function for filling eNodeB Configuration
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
PUBLIC S16 wrSmmEnbBuildWrEnbCfg
(
 LwrMngmt *lwrMng,
 U8 cellCfgIdx
 )
{
   LwrENodeBCfg *enbCfg = NULLP;
   TknStrOSXL   *enbName;
   MsmLtePlmnId *priPlmn;
   MsmLtePlmnId *plmn;
   U32          idx = 0;
   U32          idx1 = 1;
   U32          itr = 0;

   TRC2(wrSmmEnbBuildWrEnbCfg);

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_ENB;
   lwrMng->t.protoCfg.t.eNbCfg.action = WR_ACT_ADD;

   enbCfg =&(lwrMng->t.protoCfg.t.eNbCfg.t.eNodeBCfg);

   /* add enb name */
   enbName = &(enbCfg->protoCfg.enbName);
   enbName->len = (U16)(strlen((S8 *)&(lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.henbName)));
   WR_ALLOC(&(enbName->val), enbName->len);
   if(NULLP == enbName->val)
   {
      RLOG0(L_FATAL, "Failed to allocate memory.");
      RETVALUE(RFAILED);
   }
   cmMemcpy(enbName->val, lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.henbName, enbName->len);

   enbCfg->maxNumOfUe = wrSmDfltMaxNoUE;
#ifdef LTE_ADV
#ifdef LTE_ADV_UECAP
   enbCfg->isCellFreqCont = lteeNodeBparams[cellCfgIdx].caGenCfg.isCellFreqCont;
#endif /*LTE_ADV_UECAP*/
   enbCfg->isCaEnabled = lteeNodeBparams[cellCfgIdx].caGenCfg.isCaEnabled;
#endif /*LTE_ADV*/
   enbCfg->enbCfgTransTmrVal = wrSmDfltEnbCfgTransTmrVal;
   enbCfg->pwsEtwsCmas = (U8)lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.pwsEtwsCmas; /* Enable ETWS or CMAS or disable both*/
   enbCfg->avgFreeCpuRqd = (U8)lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.avgFreeCpuRqd; /* Configure free cpu req*/
   if(WR_ENODEB_TYPE_HOME == wrSmDfltEnbType)
   {
      enbCfg->protoCfg.enbId = 
         lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.cellId;
      /* in home enb case eNodeB Id and cellId are same wrSmDfltEnbID; */
   }
   else
   {
      /* in macro enb case eNodeB Id is MSB 20 bits of cellId */
      enbCfg->protoCfg.enbId = 
         ((lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.cellId) >> 8);
   }
   enbCfg->protoCfg.enbType = 
      smGetEnbType(lteeNodeBparams[cellCfgIdx].lteAddCellCfg.physCellId,cellCfgIdx);/*wrSmDfltEnbType*/;
   RLOG2(L_DEBUG, "wrSmmEnbBuildWrEnbCfg:enbCfg->protoCfg.enbType = %lu,\
         enbCfg->protoCfg.enbId = %lu\n",
         enbCfg->protoCfg.enbType,enbCfg->protoCfg.enbId);
   /*
      wrCpyCmTptAddr(&enbCfg->protoCfg.enbIpAddr[WR_IPV4_IDX], &smCfgCb.enbIpAddr[WR_IPV4_IDX]);
      wrCpyCmTptAddr(&enbCfg->protoCfg.enbIpAddr[WR_IPV6_IDX], &smCfgCb.enbIpAddr[WR_IPV6_IDX]);
      if(enbCfg->protoCfg.enbIpAddr[WR_IPV4_IDX].type == CM_TPTADDR_IPV4)
      {
      enbCfg->protoCfg.enbIpAddr[WR_IPV4_IDX].u.ipv4TptAddr.port =  
      lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.sctpPortNumS1;
      }
      else if(enbCfg->protoCfg.enbIpAddr[WR_IPV6_IDX].type == CM_TPTADDR_IPV6)
      {
      enbCfg->protoCfg.enbIpAddr[WR_IPV6_IDX].u.ipv6TptAddr.port =  
      lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.sctpPortNumS1;
      }
      */
   if(TRUE == fapParameters.lteEnodebIpAddr.ipv4pres)
   {
      enbCfg->protoCfg.enbIpAddr[WR_IPV4_IDX].type = CM_TPTADDR_IPV4; 
      enbCfg->protoCfg.enbIpAddr[WR_IPV4_IDX].u.ipv4TptAddr.address = fapParameters.lteEnodebIpAddr.enbIpAddr;
      enbCfg->protoCfg.enbIpAddr[WR_IPV4_IDX].u.ipv4TptAddr.port =  
         lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.sctpPortNumS1;
   }
   else if(TRUE == fapParameters.lteEnodebIpAddr.ipv6pres)
   {
      enbCfg->protoCfg.enbIpAddr[WR_IPV6_IDX].type = CM_TPTADDR_IPV6;
      cmMemcpy((U8*)enbCfg->protoCfg.enbIpAddr[WR_IPV6_IDX].u.ipv6TptAddr.ipv6NetAddr,
            (U8*)fapParameters.lteEnodebIpAddr.enbIpv6Addr, sizeof(CmInetIpAddr6));
      enbCfg->protoCfg.enbIpAddr[WR_IPV6_IDX].u.ipv6TptAddr.port =  
         lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.sctpPortNumS1;
   }

   enbCfg->protoCfg.numPlmns = lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.numOfPlmns;

   for(idx =0; idx < lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.\
         cellAccessInfo.numOfPlmns; idx++ )
   {
      if(lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.\
            plmnInfo[idx].isPrimary == TRUE)
      {
         priPlmn = &lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.\
                   cellAccessInfo.plmnInfo[idx].plmnId;
         enbCfg->protoCfg.plmns[0].plmnId.numMncDigits  = priPlmn->numMncDigits;
         enbCfg->protoCfg.plmns[0].plmnId.mcc[0] =priPlmn->mcc[0];
         enbCfg->protoCfg.plmns[0].plmnId.mcc[1] =priPlmn->mcc[1];
         enbCfg->protoCfg.plmns[0].plmnId.mcc[2] =priPlmn->mcc[2];

         enbCfg->protoCfg.plmns[0].plmnId.mnc[0]=priPlmn->mnc[0];
         enbCfg->protoCfg.plmns[0].plmnId.mnc[1]=priPlmn->mnc[1];
         enbCfg->protoCfg.plmns[0].plmnId.mnc[2]=priPlmn->mnc[2];
         enbCfg->protoCfg.plmns[0].plmnRatPriority.numberOfRats = 
            lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.plmnRatPriority[idx].numberOfRats;
         for(itr = 0; itr < enbCfg->protoCfg.plmns[0].plmnRatPriority.\
               numberOfRats; itr++)
         {
            enbCfg->protoCfg.plmns[0].plmnRatPriority.rat[itr] = 
               wrSmDfltPlmnRatPriorList.rat[itr];
         }
         enbCfg->protoCfg.plmns[idx].isRedirSupport = wrSmDfltPlmnRedirSuppLst[idx];
      }
      else
      {
         plmn = &lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.\
                plmnInfo[idx].plmnId;
         enbCfg->protoCfg.plmns[idx1].plmnId.numMncDigits  = plmn->numMncDigits;
         enbCfg->protoCfg.plmns[idx1].plmnId.mcc[0] =plmn->mcc[0];
         enbCfg->protoCfg.plmns[idx1].plmnId.mcc[1] =plmn->mcc[1];
         enbCfg->protoCfg.plmns[idx1].plmnId.mcc[2] =plmn->mcc[2];

         enbCfg->protoCfg.plmns[idx1].plmnId.mnc[0]=plmn->mnc[0];
         enbCfg->protoCfg.plmns[idx1].plmnId.mnc[1]=plmn->mnc[1];
         enbCfg->protoCfg.plmns[idx1].plmnId.mnc[2]=plmn->mnc[2];
         enbCfg->protoCfg.plmns[idx1].plmnRatPriority.numberOfRats = 
            lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.plmnRatPriority[idx].numberOfRats;
         for(itr = 0; itr < enbCfg->protoCfg.plmns[idx1].plmnRatPriority.\
               numberOfRats; itr++)
         {
            enbCfg->protoCfg.plmns[idx1].plmnRatPriority.rat[itr] = 
               wrSmDfltPlmnRatPriorList.rat[itr];
         }
         enbCfg->protoCfg.plmns[idx].isRedirSupport = wrSmDfltPlmnRedirSuppLst[idx];
         idx1++;
      }
   }

   enbCfg->protoCfg.sctpPortNumS1 = lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.sctpPortNumS1;
   enbCfg->protoCfg.sctpPortNumX2 = lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.sctpPortNumX2;

#ifdef MME_LDBAL
   enbCfg->numOfMmePriGrps                 = wrSmDfltNumOfPriorityGrps;
#endif /* end of MME_LDBAL */
   /* CNM_DEV */
   enbCfg->isCnmEnabled = lteeNodeBparams[cellCfgIdx].lteCnmCfg.cnmEnable;
#if 0
   enbCfg->csfbToGeranCfg.isGERANMeasAllowedForCCO = 
      lteeNodeBparams[cellCfgIdx].csfbToGeranCfg.isGERANMeasAllowedForCCO;
   enbCfg->csfbToGeranCfg.isCCOAllowed = 
      lteeNodeBparams[cellCfgIdx].csfbToGeranCfg.isCCOAllowed;
   enbCfg->csfbToGeranCfg.rrcDatCfmWaitTmr = 
      lteeNodeBparams[cellCfgIdx].csfbToGeranCfg.rrcDatCfmWaitTmr;
   enbCfg->csfbToGeranCfg.GERANMeasWaitTmr = 
      lteeNodeBparams[cellCfgIdx].csfbToGeranCfg.GERANMeasWaitTmr;
   enbCfg->csfbToGeranCfg.T304expWaitTmrVal = 
      lteeNodeBparams[cellCfgIdx].csfbToGeranCfg.T304expWaitTmrVal;
 #endif

   /* Fill Scheduler Specific Values in Enodeb Configuration on LWR interface */
   /* DL SCH Config and Type */
   enbCfg->schedEnbCfg.dlSchType =  lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.dlSchedulingAlg;
   enbCfg->schedEnbCfg.schDlPfs.tptCoeffi = lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.pfsDlTptCoefficient;
   enbCfg->schedEnbCfg.schDlPfs.fairCoeffi = lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.pfsDlFairCoefficient;
   for(idx = 0; idx < WR_MAX_QCI; idx++)
   {
      enbCfg->schedEnbCfg.schDlPfs.dlQciWgtList[idx] = lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.dlQciWgtList[idx];
   }
   /* UL SCH Config and Type */
   enbCfg->schedEnbCfg.ulSchType = lteeNodeBparams[cellCfgIdx].lteCellUlSchdCfgGrp.ulSchedulingAlg;
   enbCfg->schedEnbCfg.schUlPfs.tptCoeffi = lteeNodeBparams[cellCfgIdx].lteCellUlSchdCfgGrp.pfsUlTptCoefficient;
   enbCfg->schedEnbCfg.schUlPfs.fairCoeffi = lteeNodeBparams[cellCfgIdx].lteCellUlSchdCfgGrp.pfsUlFairCoefficient;
   for( idx = 0; idx < MAX_NUM_QCI; idx++)
   {
      enbCfg->schedEnbCfg.schUlPfs.ulQciWgtList[idx] = lteeNodeBparams[cellCfgIdx].lteCellUlSchdCfgGrp.ulQciWgtList[idx];
   }
   enbCfg->schedEnbCfg.numAntPorts = lteeNodeBparams[cellCfgIdx].lteAntenna_Common_Config.numAntPorts;
#if 0
   RLOG3(L_DEBUG,"\nwrSmmEnbBuildWrEnbCfg:numAntPorts=%d:schedEnbCfg.numAntPorts=%d:enbCfg->numTxAntenna=%d\n",
   lteeNodeBparams[cellCfgIdx].lteAntenna_Common_Config.numAntPorts,
   enbCfg->schedEnbCfg.numAntPorts,
   enbCfg->numTxAntenna);
#endif
   RETVALUE(ROK);
} /* wrSmmEnbBuildWrEnbCfg */

/*
 *
 *       Fun:  wrSmmEnbBldMeasCellCfg 
 *
 *       Desc:  fill in measurement cfg for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_smm_enb_utils.c 
 *
 */

PRIVATE Void wrSmmEnbBldMeasCellCfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex,
 U8         cellCfgIdx
 )
{
   LwrCellMeasCfgGrp          *measCfg = NULLP;
   MsmLteMeasEvntRptCfg       *dflMeasCfg = NULLP;
   MsmLteMeasEvntA3RptCfg     *measEvtA3Cfg = NULLP;
   MsmLteMeasUtraEvntB2RptCfg *b2UtraMeasCfg = NULLP; 
   MsmLteMeasUtraEvntB2RptCfg *b2UtraTddMeasCfg = NULLP; 
   MsmLteMeasGeranEvntB2RptCfg *b2GeranMeasCfg = NULLP;
   MsmMeasEutraPeridRptCfg    *eutraMeasPeridCfg = NULLP;
   MsmMeasUtraPeriodRptCfg    *utraMeasPeridCfg  = NULLP;
   MsmLteMeasEvntA5RptCfg     *measEvtA5Cfg = NULLP;
   LwrMeasEvntA3RptCfg       *a3Cfg;
   LwrMeasEvntA5RptCfg       *a5Cfg;
   LwrMeasEvntRptCfg         *eventCfg;
   LwrMeasEutraPeridRptCfg   *eutraPerd;
   LwrMeasUtraPeriodRptCfg   *utraPerd;
   LwrMeasUtraEvntB2RptCfg   *b2UtraCfg; 
   LwrMeasUtraEvntB2RptCfg   *b2UtraTddCfg;
   LwrMeasGeranEvntB2RptCfg   *b2GeranCfg = NULLP;
   LwrMeasGERANPeridRptCfg   *geranPrdCfg;
   /*S8                         offset;*/
   /* Fix for CR - ccpu00137183  */
   MsmLteMeasMobilityStatParams  *mobStateParams = NULLP;


   TRC2(wrSmmEnbBldMeasCellCfg);

   /* Fix for CR - ccpu00137183  */
   mobStateParams = &lteeNodeBparams[cellCfgIdx].lteCellSib3CfgGrp.mobStateParams;


   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_MEAS;

   measCfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.measCfgGrp);
   eventCfg = &measCfg->measA1EvtRptCfg[WR_MEAS_EVENTA1_HO_RSRP];

   dflMeasCfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA1EvtRptCfg[0];
   /* configure Event A1 */
   eventCfg->isPres.pres    = PRSNT_NODEF;
   eventCfg->reason         = wrSmDfltReason;
   eventCfg->threshold_RSRP =  dflMeasCfg->threshold_RSRP;
   eventCfg->threshold_RSRQ =  dflMeasCfg->threshold_RSRQ;
   eventCfg->hysteresis     =  dflMeasCfg->hysteresis;
   eventCfg->timeToTrigger  =  dflMeasCfg->timeToTrigger;
   eventCfg->triggerQty     =  dflMeasCfg->triggerQty;
   eventCfg->reportQty      =  dflMeasCfg->reportQty;
   eventCfg->maxRptCells    =  dflMeasCfg->maxRptCells;
   eventCfg->reportInterval =  dflMeasCfg->reportInterval;
   eventCfg->reportAmount   =  dflMeasCfg->reportAmount;

   /* configure Event A2 */
   dflMeasCfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA2EvtRptCfg[0];
   eventCfg = &measCfg->measA2EvtRptCfg[WR_MEAS_EVENTA2_HO_RSRP];

   eventCfg->isPres.pres = PRSNT_NODEF;
   eventCfg->reason = wrSmDfltReason;
   eventCfg->threshold_RSRP = dflMeasCfg->threshold_RSRP;
   eventCfg->threshold_RSRQ = dflMeasCfg->threshold_RSRQ;
   eventCfg->hysteresis     = dflMeasCfg->hysteresis;
   eventCfg->timeToTrigger  = dflMeasCfg->timeToTrigger;
   eventCfg->triggerQty     = dflMeasCfg->triggerQty;
   eventCfg->reportQty      = dflMeasCfg->reportQty;
   eventCfg->maxRptCells    = dflMeasCfg->maxRptCells;
   eventCfg->reportInterval = dflMeasCfg->reportInterval;
   eventCfg->reportAmount   = dflMeasCfg->reportAmount;

   /* configure Event A4 */
   eventCfg = &measCfg->measA4EvtRptCfg[WR_MEAS_EVENTA4_ANR_SPECIFIC];

   eventCfg->isPres.pres = PRSNT_NODEF;
   eventCfg->reason = wrSmDfltReason;
   eventCfg->threshold_RSRP = wrSmDfltThresRSRP1;
   eventCfg->threshold_RSRQ = wrSmDfltThresRSRQ1;
   eventCfg->hysteresis = wrSmDfltHysteresis; 
   eventCfg->timeToTrigger = wrSmDfltTimeToTrig; 
   eventCfg->triggerQty = wrSmDfltTrigQty;
   eventCfg->reportQty = wrSmDfltRptQty;
   eventCfg->maxRptCells = wrSmDfltMaxRptCells;
   eventCfg->reportInterval = wrSmDfltRptInterval;
   eventCfg->reportAmount = wrSmDfltRptAmount;

   /* configure Event A3 - intra */
   measEvtA3Cfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
                  measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO];
   a3Cfg = &measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_HO];
   a3Cfg->isPres.pres = PRSNT_NODEF;
   a3Cfg->reason = wrSmDfltReason;

   /* Offset Range is between -30 to 30*/
   if(measEvtA3Cfg->offset > 31)
   {
      measEvtA3Cfg->offset = 30;
   }
   else if (measEvtA3Cfg->offset < -31)
   {
      measEvtA3Cfg->offset = -30;
   }

   a3Cfg->offset = measEvtA3Cfg->offset;
   a3Cfg->reportOnLeave = wrSmDfltRptOnLeave;
   a3Cfg->hysteresis = measEvtA3Cfg->hysteresis;
   a3Cfg->timeToTrigger = measEvtA3Cfg->timeToTrigger;
   a3Cfg->triggerQty = measEvtA3Cfg->triggerQty;
   a3Cfg->reportQty = measEvtA3Cfg->reportQty;
   a3Cfg->maxRptCells = measEvtA3Cfg->maxRptCells;
   a3Cfg->reportInterval = measEvtA3Cfg->reportInterval;
   a3Cfg->reportAmount = measEvtA3Cfg->reportAmount;

   /* configure Event A3 - inter */
   /* ccpu00133426 - inter freq ho requirement - start*/
   measEvtA3Cfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
                  measEvtA3Cfg[MSM_MEAS_EVENTA3_INTER_FREQ_HO_RSRP];
   a3Cfg = &measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTER_FREQ_HO_RSRP];
   a3Cfg->isPres.pres = PRSNT_NODEF;
   a3Cfg->reason = wrSmDfltReason;
   a3Cfg->offset = measEvtA3Cfg->offset;
   a3Cfg->reportOnLeave = wrSmDfltRptOnLeave;
   a3Cfg->hysteresis = measEvtA3Cfg->hysteresis;
   a3Cfg->timeToTrigger = measEvtA3Cfg->timeToTrigger;
   a3Cfg->triggerQty = measEvtA3Cfg->triggerQty;
   a3Cfg->reportQty = measEvtA3Cfg->reportQty;
   a3Cfg->maxRptCells = measEvtA3Cfg->maxRptCells;
   a3Cfg->reportInterval = measEvtA3Cfg->reportInterval;
   a3Cfg->reportAmount = measEvtA3Cfg->reportAmount;
   /* ccpu00133426 - inter freq ho requirement - end*/

   /*Event A3 for ANR */
   measEvtA3Cfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
                  measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_ANR];
   a3Cfg = &measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ANR];
   a3Cfg->isPres.pres = PRSNT_NODEF;
   a3Cfg->reason = wrSmDfltReason;

   /* Offset Range is between
    * -30 to 30*/
   if(measEvtA3Cfg->offset > (lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
            measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO].offset))
   {
      measEvtA3Cfg->offset = (lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
            measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO].offset) - 5;
   }
   else if (measEvtA3Cfg->offset < -31)
   {
      measEvtA3Cfg->offset = -30;
   }

   a3Cfg->offset = measEvtA3Cfg->offset;
   a3Cfg->reportOnLeave = wrSmDfltRptOnLeave;
   a3Cfg->hysteresis = measEvtA3Cfg->hysteresis;
   a3Cfg->timeToTrigger = measEvtA3Cfg->timeToTrigger;
   a3Cfg->triggerQty = measEvtA3Cfg->triggerQty;
   a3Cfg->reportQty = measEvtA3Cfg->reportQty;
   a3Cfg->maxRptCells = measEvtA3Cfg->maxRptCells;
   a3Cfg->reportInterval = measEvtA3Cfg->reportInterval;
   a3Cfg->reportAmount = measEvtA3Cfg->reportAmount;

#ifdef LTE_ADV
   /* configure Event A4 */
   dflMeasCfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA4EvtRptCfg[MSM_MEAS_EVENTA4_SCELL_ADD];
   eventCfg = &measCfg->measA4EvtRptCfg[WR_MEAS_EVENTA4_SCELL_ADD];

   eventCfg->isPres.pres = PRSNT_NODEF;
   eventCfg->reason = wrSmDfltReason;
   eventCfg->threshold_RSRP = dflMeasCfg->threshold_RSRP;
   eventCfg->threshold_RSRQ = dflMeasCfg->threshold_RSRQ;
   eventCfg->hysteresis     = dflMeasCfg->hysteresis;
   eventCfg->timeToTrigger  = dflMeasCfg->timeToTrigger;
   eventCfg->triggerQty     = dflMeasCfg->triggerQty;
   eventCfg->reportQty      = dflMeasCfg->reportQty;
   eventCfg->maxRptCells    = dflMeasCfg->maxRptCells;
   eventCfg->reportInterval = dflMeasCfg->reportInterval;
   eventCfg->reportAmount   = dflMeasCfg->reportAmount;
#endif

   /* LTE_ADV_ABS starts */
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].isPres.pres = 
      PRSNT_NODEF;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].reason = wrSmDfltReason;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].offset = 0; /* Report all neighbor stronger than serving */
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].reportOnLeave = FALSE;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].hysteresis = 
      wrSmDfltHysteresis;  
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].timeToTrigger = 
      wrSmDfltTimeToTrig; 
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].triggerQty = 
      wrSmDfltTrigQty;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].reportQty = 
      wrSmDfltRptQty;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].maxRptCells = 
      wrSmDfltMaxRptCells;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].reportInterval = 
      wrSmDfltRptInterval;
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].reportAmount = 0; /* Report only once */
   measCfg->measEvtA3Cfg[WR_MEAS_EVENTA3_INTRA_FREQ_ABS].offset = 
      smCfgCb.lteAdvancedConfig.a3Offset; /* ABS Offset */
   /* LTE_ADV_ABS ends */

   /* configure Event A5 */
   a5Cfg = &measCfg->measEvtA5Cfg[WR_MEAS_EVENTA5_INTRA_FREQ_HO];
   measEvtA5Cfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
                  measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO];
   /* configure Intra Event A5 */
   a5Cfg->isPres.pres = PRSNT_NODEF;
   a5Cfg->reason = wrSmDfltReason;
   a5Cfg->threshold1_RSRP = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO].\
      threshold1_RSRP;
   a5Cfg->threshold1_RSRQ = wrSmDfltThresRSRQ1;
   a5Cfg->threshold2_RSRP =  
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
      measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO].threshold2_RSRP;
   a5Cfg->threshold2_RSRQ = wrSmDfltThresRSRQ2;
   a5Cfg->hysteresis = measEvtA5Cfg->hysteresis;
   a5Cfg->timeToTrigger = measEvtA5Cfg->timeToTrigger;
   a5Cfg->triggerQty = measEvtA5Cfg->triggerQty;
   a5Cfg->reportQty = measEvtA5Cfg->reportQty;
   a5Cfg->maxRptCells = measEvtA5Cfg->maxRptCells;
   a5Cfg->reportInterval = measEvtA5Cfg->reportInterval;
   a5Cfg->reportAmount = measEvtA5Cfg->reportAmount;

   a5Cfg = &measCfg->measEvtA5Cfg[WR_MEAS_EVENTA5_INTER_FREQ_HO_RSRP];
   measEvtA5Cfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
                  measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_HO_RSRP];
   /* configure Inter Event A5 */
   a5Cfg->isPres.pres = PRSNT_NODEF;
   a5Cfg->reason = wrSmDfltReason;

   /*range check taken from wr_smm_enbapp_utils.c*/
   /* if RSRP configured is out range (which is defined in RRC)
    * will be defaulted nearest value with in the range 
    * Here check spec defined range only */
   if (measEvtA5Cfg->threshold1_RSRP > 97) /* RSRP Max range check */
   {
      measEvtA5Cfg->threshold1_RSRP = 97;
   }
   else if (measEvtA5Cfg->threshold1_RSRP < 0)/* RSRP Min range check */
   {
      measEvtA5Cfg->threshold1_RSRP = 0;
   }
   a5Cfg->threshold1_RSRP = measEvtA5Cfg->threshold1_RSRP;
   a5Cfg->threshold1_RSRQ = wrSmDfltThresRSRQ1;

   /* if RSRP configured is out range (which is defined in RRC)
    * will be defaulted nearest value with in the range 
    * Here check spec defined range only */
   if (measEvtA5Cfg->threshold2_RSRP > 97) /* RSRP Max range check */
   {
      measEvtA5Cfg->threshold2_RSRP = 97;
   }
   else if (measEvtA5Cfg->threshold2_RSRP < 0)/* RSRP Min range check */
   {
      measEvtA5Cfg->threshold2_RSRP = 0;
   } 
   a5Cfg->threshold2_RSRP = measEvtA5Cfg->threshold2_RSRP;
   a5Cfg->threshold2_RSRQ = wrSmDfltThresRSRQ2;
   a5Cfg->hysteresis = measEvtA5Cfg->hysteresis;
   a5Cfg->timeToTrigger = measEvtA5Cfg->timeToTrigger;
   a5Cfg->triggerQty = measEvtA5Cfg->triggerQty;
   a5Cfg->reportQty = measEvtA5Cfg->reportQty;
   a5Cfg->maxRptCells = measEvtA5Cfg->maxRptCells;
   a5Cfg->reportInterval = measEvtA5Cfg->reportInterval;
   a5Cfg->reportAmount = measEvtA5Cfg->reportAmount;

   a5Cfg = &measCfg->measEvtA5Cfg[WR_MEAS_EVENTA5_INTER_FREQ_ANR];
   measEvtA5Cfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
                  measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_ANR];
   /* configure Inter Event A5 */
   a5Cfg->isPres.pres = PRSNT_NODEF;
   a5Cfg->reason = wrSmDfltReason;

   /* if RSRP configured is out range (which is defined in RRC)
    * will be defaulted nearest value with in the range
    * Here check spec defined range only */
   if (measEvtA5Cfg->threshold1_RSRP > 97) /* RSRP Max range check */
   {
      measEvtA5Cfg->threshold1_RSRP = 97;
   }
   else if (measEvtA5Cfg->threshold1_RSRP < 0)/* RSRP Min range check */
   {
      measEvtA5Cfg->threshold1_RSRP = 0;
   }

   a5Cfg->threshold1_RSRP = measEvtA5Cfg->threshold1_RSRP;
   a5Cfg->threshold1_RSRQ = wrSmDfltThresRSRQ1;


   /* if RSRP configured is out range (which is defined in RRC)
    * will be defaulted nearest value with in the range 
    * Here check spec defined range only */
   if (measEvtA5Cfg->threshold2_RSRP > 97) /* RSRP Max range check */
   {
      measEvtA5Cfg->threshold2_RSRP = 97;
   }
   else if (measEvtA5Cfg->threshold2_RSRP < 0)/* RSRP Min range check */
   {
      measEvtA5Cfg->threshold2_RSRP = 0;
   } 
   a5Cfg->threshold2_RSRP = measEvtA5Cfg->threshold2_RSRP;
   a5Cfg->threshold2_RSRQ = wrSmDfltThresRSRQ2;
   a5Cfg->hysteresis = measEvtA5Cfg->hysteresis;
   a5Cfg->timeToTrigger = measEvtA5Cfg->timeToTrigger;
   a5Cfg->triggerQty = measEvtA5Cfg->triggerQty;
   a5Cfg->reportQty = measEvtA5Cfg->reportQty;
   a5Cfg->maxRptCells = measEvtA5Cfg->maxRptCells;
   a5Cfg->reportInterval = measEvtA5Cfg->reportInterval;
   a5Cfg->reportAmount = measEvtA5Cfg->reportAmount;

   /* configure Event Periodic */
   eutraPerd = &measCfg->\
               measEutraPerdRptCfg[WR_MEAS_EUTRA_PERIODIC_REPORT_STRNG_CELLS];
   eutraMeasPeridCfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
                       measEutraPeridRptCfg[MSM_MEAS_EUTRA_PERIODIC_REPORT_STRNG_CELLS];
   eutraPerd->isPres.pres = PRSNT_NODEF;
   eutraPerd->reason = wrSmDfltReason;
   eutraPerd->triggerQty = eutraMeasPeridCfg->triggerQty;
   eutraPerd->reportQty = eutraMeasPeridCfg->reportQty;
   eutraPerd->maxRptCells = eutraMeasPeridCfg->maxRptCells;
   eutraPerd->reportInterval = eutraMeasPeridCfg->reportInterval;
   eutraPerd->reportAmount = eutraMeasPeridCfg->reportAmount;

   /* configure Event B2 for GERAN */
   b2GeranCfg = &measCfg->measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_REDIR];
   b2GeranMeasCfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
                    measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_REDIR];
   b2GeranCfg->b2Threshold1RSRP = b2GeranMeasCfg->b2Threshold1RSRP;
   b2GeranCfg->b2Threshold1RSRQ = b2GeranMeasCfg->b2Threshold1RSRQ;
   b2GeranCfg->b2Threshold2Geran = b2GeranMeasCfg->b2Threshold2Geran;
   b2GeranCfg->hysteresis = b2GeranMeasCfg->hysteresis;
   b2GeranCfg->maxReportCell = b2GeranMeasCfg->maxReportCell;
   b2GeranCfg->reportAmount = b2GeranMeasCfg->reportAmount;
   b2GeranCfg->reportInterval = b2GeranMeasCfg->reportInterval;
   b2GeranCfg->timeToTrigger = b2GeranMeasCfg->timeToTrigger;

   /* configure Event B2 for GERAN */
   b2GeranCfg = &measCfg->measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_HO];
   b2GeranMeasCfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
                    measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_HO];
   b2GeranCfg->b2Threshold1RSRP = b2GeranMeasCfg->b2Threshold1RSRP;
   b2GeranCfg->b2Threshold1RSRQ = b2GeranMeasCfg->b2Threshold1RSRQ;
   b2GeranCfg->b2Threshold2Geran = b2GeranMeasCfg->b2Threshold2Geran;
   b2GeranCfg->hysteresis = b2GeranMeasCfg->hysteresis;
   b2GeranCfg->maxReportCell = b2GeranMeasCfg->maxReportCell;
   b2GeranCfg->reportAmount = b2GeranMeasCfg->reportAmount;
   b2GeranCfg->reportInterval = b2GeranMeasCfg->reportInterval;
   b2GeranCfg->timeToTrigger = b2GeranMeasCfg->timeToTrigger;

   /* configure Event B2 */
   b2UtraCfg = &measCfg->measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_HO]; 
   b2UtraMeasCfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
                   measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_HO];
   b2UtraCfg->reason = WR_MEAS_UTRA_EVENTB2_HO;
   b2UtraCfg->activeState = TRUE;

   /* If RSRP configured is exceeding Spec defined Val
    * then set it to default value */
   if( b2UtraMeasCfg->b2Threshold1RSRP > WR_SM_MAX_B2_THRESH1_RSRP)
   {
      b2UtraMeasCfg->b2Threshold1RSRP = 70;
   }
   b2UtraCfg->b2Threshold1RSRP = b2UtraMeasCfg->b2Threshold1RSRP;

   if(  b2UtraMeasCfg->b2Threshold1RSRQ > WR_SM_MAX_B2_THRESH1_RSRQ)
   {
      b2UtraMeasCfg->b2Threshold1RSRQ = 32;
   }
   b2UtraCfg->b2Threshold1RSRQ = b2UtraMeasCfg->b2Threshold1RSRQ;

   if(( b2UtraMeasCfg->b2Threshold2UtraRSCP > WR_SM_MAX_B2_THRESH1_RSCP) || 
         ( b2UtraMeasCfg->b2Threshold2UtraRSCP < WR_SM_MIN_B2_THRESH1_RSCP))
   {
      b2UtraMeasCfg->b2Threshold2UtraRSCP = 65;
   }
   b2UtraCfg->b2Threshold2UtraRSCP = b2UtraMeasCfg->b2Threshold2UtraRSCP;

   if( b2UtraMeasCfg->b2Threshold2UtraEcNo > WR_SM_MAX_B2_THRESH1_ECNO)
   {
      b2UtraMeasCfg->b2Threshold2UtraEcNo = 30;
   }
   b2UtraCfg->b2Threshold2UtraEcNo = b2UtraMeasCfg->b2Threshold2UtraEcNo;

   b2UtraCfg->hysteresis = b2UtraMeasCfg->hysteresis;
   b2UtraCfg->maxReportCell = b2UtraMeasCfg->maxReportCell;
   b2UtraCfg->reportAmount = b2UtraMeasCfg->reportAmount;
   b2UtraCfg->reportInterval = b2UtraMeasCfg->reportInterval;
   b2UtraCfg->timeToTrigger = b2UtraMeasCfg->timeToTrigger;

   /* Configure UTRA Event B2 for Redirection to TD-SCDMA */
   b2UtraTddCfg = &measCfg->measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_REDIR]; 
   b2UtraTddMeasCfg = 
      &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
      measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_REDIR];

   /* If RSRP configured is exceeding Spec defined Val
    * then set it to default value */
   if( b2UtraTddMeasCfg->b2Threshold1RSRP > WR_SM_MAX_B2_THRESH1_RSRP)
   {
      b2UtraTddMeasCfg->b2Threshold1RSRP = 70;
   }
   b2UtraTddCfg->b2Threshold1RSRP = b2UtraTddMeasCfg->b2Threshold1RSRP;

   if( b2UtraTddMeasCfg->b2Threshold1RSRQ > WR_SM_MAX_B2_THRESH1_RSRQ)
   {
      b2UtraTddMeasCfg->b2Threshold1RSRQ = 32;
   }
   b2UtraTddCfg->b2Threshold1RSRQ = b2UtraTddMeasCfg->b2Threshold1RSRQ;
   b2UtraTddCfg->b2Threshold2UtraRSCP = b2UtraTddMeasCfg->b2Threshold2UtraRSCP;
   b2UtraTddCfg->b2Threshold2UtraEcNo = b2UtraTddMeasCfg->b2Threshold2UtraEcNo;

   /* b2Threshold2UtraTddRSCP parameter is not present in msm str. But it is
    * used in wr_umm_meas.c.So retained the smallcell variable
    * wrSmDfltUtraTddB2ThresRSCP */
   if(( wrSmDfltUtraTddB2ThresRSCP > WR_SM_MAX_B2_THRESH1_RSCP) || 
         ( wrSmDfltUtraTddB2ThresRSCP < WR_SM_MIN_B2_THRESH1_RSCP))
   {
      wrSmDfltUtraTddB2ThresRSCP = 65;
   }
   b2UtraTddCfg->b2Threshold2UtraTddRSCP = wrSmDfltUtraTddB2ThresRSCP;

   b2UtraTddCfg->hysteresis = b2UtraTddMeasCfg->hysteresis;
   b2UtraTddCfg->maxReportCell = b2UtraTddMeasCfg->maxReportCell;
   b2UtraTddCfg->reportAmount = b2UtraTddMeasCfg->reportAmount;
   b2UtraTddCfg->reportInterval = b2UtraTddMeasCfg->reportInterval;
   b2UtraTddCfg->timeToTrigger = b2UtraTddMeasCfg->timeToTrigger;

   geranPrdCfg = &measCfg->measGERANPeridRptCfg[LWR_MEAS_GERAN_REPORT_STRNG_CELLS];
   geranPrdCfg->isPres.pres = PRSNT_NODEF;
   geranPrdCfg->reason = wrSmDfltUtraReason;
   /*geranPrdCfg->QoffsetGERAN = 
     lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measGERANPeridRptCfg[0].qoffsetGERAN;*/
   geranPrdCfg->maxRptCells = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measGERANPeridRptCfg[0].maxRptCells;
   geranPrdCfg->reportInterval = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measGERANPeridRptCfg[0].reportInterval;
   geranPrdCfg->reportAmount = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measGERANPeridRptCfg[0].reportAmount;

   /*config for UTRA*/
   /* Below Report Amount parametrs hardcoded because current CSFB design 
    * support for only one measurement report per frequency. 
    * This will be resolved soon*/
   utraPerd = &measCfg->measUtraPerdRptCfg[WR_MEAS_UTRA_PRDRPT_STRGCELLS_CSFB];
   utraMeasPeridCfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
                      measUtraPeriodRptCfg[MSM_MEAS_UTRA_PRDRPT_STRGCELLS_CSFB];

   utraPerd->reason = wrSmDfltUtraReason;
   utraPerd->maxReportCell= utraMeasPeridCfg->maxReportCell;
   utraPerd->reportInterval= utraMeasPeridCfg->reportInterval;
   utraPerd->reportAmount= utraMeasPeridCfg->reportAmount;

   utraPerd = &measCfg->measUtraPerdRptCfg[WR_MEAS_UTRA_PRDRPT_STRGCELLS_ANR];
   utraMeasPeridCfg = &lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
                      measUtraPeriodRptCfg[MSM_MEAS_UTRA_PRDRPT_STRGCELLS_ANR];

   utraPerd->reason = wrSmDfltUtraReason;
   utraPerd->maxReportCell= utraMeasPeridCfg->maxReportCell;
   utraPerd->reportInterval= utraMeasPeridCfg->reportInterval;
   utraPerd->reportAmount= utraMeasPeridCfg->reportAmount;


   /* configure 1xCdma Event B1 */
   measCfg->meas1xCDMAEventB1RptCfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->meas1xCDMAEventB1RptCfg[0].reason = wrSmDfltReason;
   measCfg->meas1xCDMAEventB1RptCfg[0].cellType = wrSmDfltCellType;
   measCfg->meas1xCDMAEventB1RptCfg[0].threshold = wrSmDfltCdmaThres1;
   measCfg->meas1xCDMAEventB1RptCfg[0].hysteresis = wrSmDfltCdmaHysteresis;
   measCfg->meas1xCDMAEventB1RptCfg[0].timeToTrigger = wrSmDfltCdmaTimeToTrig;
   measCfg->meas1xCDMAEventB1RptCfg[0].maxRptCells = wrSmDfltCdmaMaxRptCells;
   measCfg->meas1xCDMAEventB1RptCfg[0].reportInterval =
      wrSmDfltCdmaRptInterval;
   measCfg->meas1xCDMAEventB1RptCfg[0].reportAmount = wrSmDfltCdmaRptAmount;

   /* configure 1xCdma Event B2 */
   measCfg->meas1xCDMAEventB2RptCfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->meas1xCDMAEventB2RptCfg[0].reason = wrSmDfltReason;
   measCfg->meas1xCDMAEventB2RptCfg[0].cellType = wrSmDfltCellType;
   measCfg->meas1xCDMAEventB2RptCfg[0].threshold1Rsrp = wrSmDfltCdmaThresRSRP1;
   measCfg->meas1xCDMAEventB2RptCfg[0].threshold1Rsrq = wrSmDfltCdmaThresRSRQ1;
   measCfg->meas1xCDMAEventB2RptCfg[0].threshold2 = wrSmDfltCdmaThres1;
   measCfg->meas1xCDMAEventB2RptCfg[0].hysteresis = wrSmDfltCdmaHysteresis;
   measCfg->meas1xCDMAEventB2RptCfg[0].timeToTrigger = wrSmDfltCdmaTimeToTrig;
   measCfg->meas1xCDMAEventB2RptCfg[0].maxRptCells = wrSmDfltCdmaMaxRptCells;
   measCfg->meas1xCDMAEventB2RptCfg[0].trigQtyEutra = wrSmDfltTrigQty;
   measCfg->meas1xCDMAEventB2RptCfg[0].reportInterval =
      wrSmDfltCdmaRptInterval;
   measCfg->meas1xCDMAEventB2RptCfg[0].reportAmount = wrSmDfltCdmaRptAmount;


   /* configure Cdma Hrpd Event B1 */
   measCfg->measCDMAHrpdEventB1RptCfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->measCDMAHrpdEventB1RptCfg[0].reason = wrSmDfltReason;
   measCfg->measCDMAHrpdEventB1RptCfg[0].cellType = wrSmDfltCellType;
   measCfg->measCDMAHrpdEventB1RptCfg[0].threshold = wrSmDfltCdmaThres1;
   measCfg->measCDMAHrpdEventB1RptCfg[0].hysteresis = wrSmDfltCdmaHysteresis;
   measCfg->measCDMAHrpdEventB1RptCfg[0].timeToTrigger =
      wrSmDfltCdmaTimeToTrig;
   measCfg->measCDMAHrpdEventB1RptCfg[0].maxRptCells = wrSmDfltCdmaMaxRptCells;
   measCfg->measCDMAHrpdEventB1RptCfg[0].reportInterval =
      wrSmDfltCdmaRptInterval;
   measCfg->measCDMAHrpdEventB1RptCfg[0].reportAmount = wrSmDfltCdmaRptAmount;

   /* configure Cdma Hrpd Event B2 */
   measCfg->measCDMAHrpdEventB2RptCfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->measCDMAHrpdEventB2RptCfg[0].reason = wrSmDfltReason;
   measCfg->measCDMAHrpdEventB2RptCfg[0].cellType = wrSmDfltCellType;
   measCfg->measCDMAHrpdEventB2RptCfg[0].threshold1Rsrp =
      wrSmDfltCdmaThresRSRP1;
   measCfg->measCDMAHrpdEventB2RptCfg[0].threshold1Rsrq =
      wrSmDfltCdmaThresRSRQ1;
   measCfg->measCDMAHrpdEventB2RptCfg[0].threshold2 = wrSmDfltCdmaThres1;
   measCfg->measCDMAHrpdEventB2RptCfg[0].hysteresis = wrSmDfltCdmaHysteresis;
   measCfg->measCDMAHrpdEventB2RptCfg[0].timeToTrigger =
      wrSmDfltCdmaTimeToTrig;
   measCfg->measCDMAHrpdEventB2RptCfg[0].maxRptCells = wrSmDfltCdmaMaxRptCells;
   measCfg->measCDMAHrpdEventB2RptCfg[0].trigQtyEutra = wrSmDfltTrigQty;
   measCfg->measCDMAHrpdEventB2RptCfg[0].reportInterval =
      wrSmDfltCdmaRptInterval;
   measCfg->measCDMAHrpdEventB2RptCfg[0].reportAmount = wrSmDfltCdmaRptAmount;

   /* configure 1xCdma Periodic */
   measCfg->meas1xCDMAPeridRptCfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->meas1xCDMAPeridRptCfg[0].reason = wrSmDfltReason;
   measCfg->meas1xCDMAPeridRptCfg[0].cellType = wrSmDfltCellType;
   measCfg->meas1xCDMAPeridRptCfg[0].maxRptCells = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measCDMA1xPeridRptCfg[0].maxReportCell;
   measCfg->meas1xCDMAPeridRptCfg[0].reportInterval = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measCDMA1xPeridRptCfg[0].reportInterval;
   measCfg->meas1xCDMAPeridRptCfg[0].reportAmount = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measCDMA1xPeridRptCfg[0].reportAmount;

   /* configure Cdma HRPD Periodic */
   measCfg->measCDMAHrpdPeridRptCfg[0].isPres.pres = PRSNT_NODEF;
   measCfg->measCDMAHrpdPeridRptCfg[0].reason = wrSmDfltReason;
   measCfg->measCDMAHrpdPeridRptCfg[0].cellType = wrSmDfltCellType;
   measCfg->measCDMAHrpdPeridRptCfg[0].maxRptCells = wrSmDfltCdmaMaxRptCells;
   measCfg->measCDMAHrpdPeridRptCfg[0].reportInterval =
      wrSmDfltCdmaRptInterval;
   measCfg->measCDMAHrpdPeridRptCfg[0].reportAmount = wrSmDfltCdmaRptAmount;

   /* configure Speed scaling Factors */
   measCfg->measSpdSclFact.sfUsagePres.pres =  PRSNT_NODEF;
   measCfg->measSpdSclFact.sMeasure = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measSpeedCfg.sMeasure;
   measCfg->measSpdSclFact.timeToTriggerSfMedium = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measSpeedCfg.timeToTriggerSfMedium;
   measCfg->measSpdSclFact.timeToTriggerSfHigh = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measSpeedCfg.timeToTriggerSfHigh;

   /* configure Mobility state Params */
   measCfg->mobStatParams.speedStatPres.pres =  PRSNT_NODEF;
   /* Fix for CR - ccpu00137183  */
   measCfg->mobStatParams.tEvalulation       = mobStateParams->tEvalulation;
   measCfg->mobStatParams.tHystNormal        = mobStateParams->tHystNormal; 
   measCfg->mobStatParams.nCellChangeMedium  = wrSmDfltNCellChangeMedium;
   measCfg->mobStatParams.nCellChangeHigh    = wrSmDfltNCellChangeHigh;  

   /* configure Quantity params */
   measCfg->qtyCfg.rsrpFltrCoeff  = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.rsrpFltrCoeff; 
   measCfg->qtyCfg.rsrqFltrCoeff  = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.rsrqFltrCoeff; 
   measCfg->qtyCfg.measQtyCDMA2k  = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.measQtyCDMA2k;
   measCfg->qtyCfg.measQtyUtraTdd = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.measQtyUtraTdd;
   measCfg->qtyCfg.fltrCoeffGERAN = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.fltrCoeffGERAN;
   measCfg->qtyCfg.ecnoFltrCoeff  = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.ecnoFltrCoeff; 
   measCfg->qtyCfg.measQtyUtraFdd = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.measQtyUtraFdd; 
   measCfg->qtyCfg.filterCoefficient2FDDr10  = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.filterCoefficient2FDDr10;/*RRC Rel10 Upgrade*/ 

   /* configure Measurement Gap params */
   measCfg->measGap.gapForANRPres.pres =  PRSNT_NODEF;
   measCfg->measGap.gapPatternForInterFA = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measGap.gapPatternForInterFA;
   measCfg->measGap.gapPatternForInterRAT = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measGap.gapPatternForInterRAT;
   measCfg->measGap.gapPatternForANR = 
      lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measGap.gapPatternForANR;;

   /* configure PreRegistration HRPD */
   measCfg->preRegHrpd.preRegAllowed = wrSmDfltPreRegAllowed;
   measCfg->preRegHrpd.preRegZoneId = wrSmDfltPreRegZoneId;
   measCfg->preRegHrpd.NumOf2ndPreRegZoneIdList =
      wrSmDfltNumOf2ndPreRegZoneIdList;
   measCfg->preRegHrpd.secondaryPreRegZoneId1 = wrSmDfltSecondaryPreRegZoneId1;
   measCfg->preRegHrpd.secondaryPreRegZoneId2 = wrSmDfltSecondaryPreRegZoneId2;

   measCfg->anrRptCfg = lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.anrRptCfg;
   measCfg->hoRptCfg = lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.hoRptCfg;
   /*rsrq_ho*/
   measCfg->rsrqHoThrshld = wrSmDfltThresRSRQ;
#ifdef LTE_ADV
   measCfg->isMeasReqForSCellAdd = lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.isMeasReqForSCellAdd;
#endif
   RETVOID;
} /* end of wrSmmEnbBldMeasCellCfg */

/*
 *
 *       Fun:   wrSmmEnbBldCellAnrCfg
 *
 *       Desc:  fill in cell anr Cfg for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_smm_enb_utils.c 
 *
 */

PUBLIC void wrSmmEnbBldCellAnrCfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex,
 U8         cellCfgIdx
 )
{
   LwrCellAnrCfgGrp          *anrCfg;
   TRC2(wrSmmEnbBldCellAnrCfg);

   anrCfg = &lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].t.anrCfgGrp;

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType = 
      WR_CELL_CFG_GRP_ANR;
   anrCfg->csfbTransTmrVal = wrSmDfltCsfbTmrVal;
   wrFillTknU32(&(anrCfg->epocTimerVal), \
         lteeNodeBparams[cellCfgIdx].lteFapControlParams.anrEpochPeriod);

   anrCfg->tricePeriodIntv = lteeNodeBparams[cellCfgIdx].lteFapControlParams.anrTricePeriod;
   /*Removed DRX Flag */
   anrCfg->ueAnrDrxCfg.longDrxCycle =  
      lteeNodeBparams[cellCfgIdx].lteFapControlParams.anrDrxLongCycle;  
   anrCfg->ueAnrDrxCfg.drxOnDurTmr  =  
      lteeNodeBparams[cellCfgIdx].lteFapControlParams.anrDrxOnDurTmr;
   /* Fix for ccpu00132334 - To read DRX Inactivity timer for ANR*/
   anrCfg->ueAnrDrxCfg.inActivTmr   =  
      lteeNodeBparams[cellCfgIdx].lteFapControlParams.anrDrxInactvTmr; 
   RETVOID;
} /* end of wrSmmEnbBldCellAnrCfg */

/*
 *
 *       Fun:   wrSmmEnbBuildModCellCfg
 *
 *       Desc:  fill in cellCfg for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 */
#ifdef ANSI
PUBLIC S16 wrSmmEnbBuildModCellCfg
(
 LwrMngmt *lwrMng ,
 U8        cellCfgIdx
 )
#else /* if ANSI not defined*/
PUBLIC S16 wrSmmEnbBuildModCellCfg(lwrMng, cellCfgIdx)
   LwrMngmt lwrMng;
   U8       cellCfgIdx;
#endif /* end of ANSI*/
{
   LwrCellMibCfgGrp *lwrMib = NULLP;
   LwrCellSib1CfgGrp *sib1 =NULLP;
   U8                cfgGrpIndex = 0;

   TRC2(wrSmmEnbBuildModCellCfg);

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_CELL;
   lwrMng->t.protoCfg.t.cellCfg.action = WR_ACT_MOD;

   lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellId = (cellCfgIdx + 1); /* this ownCellID in case of PLD based, jst logic cell */
   lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellIndex = 
      (cellCfgIdx + WR_DFLT_CELL_IDX);

   /*Filling MIB params*/
   lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].grpType 
      = WR_CELL_CFG_GRP_MIB;
   lwrMib = &(lwrMng->t.protoCfg.t.cellCfg.t.modCell.\
         cellCfgGrp[cfgGrpIndex].t.mibCfgGrp);
   lwrMng->t.protoCfg.t.cellCfg.t.modCell.reCfgType = LWR_CELL_CFG_GRP;  
   /*lwrMib->dlBw = wrSmDfltCellDlBW[cellCfgIdx];*/
   lwrMib->dlBw = lteeNodeBparams[cellCfgIdx].lteCellMibCfgGrp.dlBw[0];
   lwrMib->phichCfg.phichDur = wrSmDfltPhichDur;
   lwrMib->phichCfg.phichRes = wrSmDfltPhichRes;
   cfgGrpIndex++;
   /*Filling sib1 params*/
   lwrMng->t.protoCfg.t.cellCfg.t.modCell.cellCfgGrp[cfgGrpIndex].grpType 
      = WR_CELL_CFG_GRP_SIB1;

   sib1 =&(lwrMng->t.protoCfg.t.cellCfg.t.modCell.\
         cellCfgGrp[cfgGrpIndex].t.sib1CfgGrp);

   sib1->reCfgType = LWR_CELL_SIB1_CFG_CELL_ACCESS_INFO;

   sib1->cellAccessInfo.plmnInfo[0].rsrvdFrOperUse =wrSmDfltCellRsrvdForOperUse;

   /* Modify tac */
   sib1->cellAccessInfo.tac = 
      (U16)(lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.tac + 1);

   sib1->cellAccessInfo.cellId = 
      lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.cellId;
   /* CSG_DEV start */
   if(WR_ENB_OPEN_ACCESS == lteeNodeBparams[cellCfgIdx].lteFapAccessParams.accessMode)
   {
      sib1->cellAccessInfo.csgIndication = FALSE;
      sib1->cellAccessInfo.csgIdentity.pres = NOTPRSNT;
   }
   else if(WR_ENB_CLOSED_ACCESS == lteeNodeBparams[cellCfgIdx].lteFapAccessParams.accessMode)
   {
      sib1->cellAccessInfo.csgIndication = TRUE;
      wrFillTknU32(&sib1->cellAccessInfo.csgIdentity,
            lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.csgIdentity);
   }
   else /* hybrid access */
   {
      sib1->cellAccessInfo.csgIndication = FALSE;
      wrFillTknU32(&sib1->cellAccessInfo.csgIdentity,
            lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.csgIdentity);
   }
   /* CSG_DEV end */
   /*sib1->cellAccessInfo.cellBarred = (Bool)wrSmDfltCellBarred;*/
   sib1->cellAccessInfo.cellBarred = 
      lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.cellBarred;
   sib1->cellAccessInfo.intraFreqReSelection = (Bool)wrSmDfltIntraFreqResel;

   /*sib1->cellSelectInfo.qRxLevMin = (S8)wrSmDlftqRxLevMin;*/
   sib1->cellSelectInfo.qRxLevMin = 
      lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellSelectInfo.qRxLevMin;
   /* Start - Fix for ccpu00123651 */
   /*wrFillTknU8(&(sib1->cellSelectInfo.qRxLevMinOffset), \
     (U8)wrSmDfltqRxlevminoffset);*/
   wrFillTknU8(&(sib1->cellSelectInfo.qRxLevMinOffset),\
         lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellSelectInfo.qRxLevMinOffset);
   /* End - Fix for ccpu00123651 */

   /*sib1->pMax = (S8)wrSmDfltPMax;*/
   sib1->pMax = lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.pMax;
   sib1->siWindowSize = wrSmDfltSiWinSize;

   /*TODO:*/
#ifdef LTE_TDD
   sib1->tddCfg.specialSubframeCfg = 
      lteeNodeBparams[cellCfgIdx].lteTddParam.specialSubFramePattern;
   sib1->tddCfg.subframeCfg = lteeNodeBparams[cellCfgIdx].lteTddParam.subframeAssignment;
#else
   sib1->tddCfg.specialSubframeCfg = 0;
   sib1->tddCfg.subframeCfg = 0;
#endif
   cfgGrpIndex++;

   lwrMng->t.protoCfg.t.cellCfg.t.modCell.numOfGrps = cfgGrpIndex;

   RETVALUE(ROK);
} /* end of wrSmmEnbBuildModCellCfg */

#ifdef RM_INTF
/**
 *
 *       Fun:  wrSmmEnbFillRmuAcbInfo 
 *
 *       Desc:  This function is used for filling default ACB info to RRM
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 */
#ifdef ANSI 
PRIVATE void wrSmmEnbFillRmuAcbInfo(LrmCellConfiguration *cellCfg, U8 cellCfgIdx)
#else
PRIVATE void wrSmmEnbFillRmuAcbInfo(cellCfg, cellCfgIdx)
   LrmCellConfiguration *cellCfg;
   U8 cellCfgIdx;
#endif
{
   U8 acbMask = 0x00;

   cellCfg->stCellCfgInfo.stAcbInfo.bAcBarringEmergency = lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForEmergency;
   /*Filling ACB params*/
   
   cellCfg->stCellCfgInfo.stAcbInfo.bIsacBarringMoSig = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.barringSignalUsage;
   cellCfg->stCellCfgInfo.stAcbInfo.bIsacBarringMoData = 
      lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.barringDataUsage;
   cellCfg->stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbTime = 
      (CmRrmAcBarringTime)lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringTime;


    if(lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringAC11)
    {
       acbMask |= LRM_ACB_SPECIAL_AC_11; 
    }
    if(lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringAC12)
    {
       acbMask |= LRM_ACB_SPECIAL_AC_12;
    }
    if(lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringAC13)
    {
       acbMask |= LRM_ACB_SPECIAL_AC_13;
    }
    if(lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringAC14)
    {
       acbMask |= LRM_ACB_SPECIAL_AC_14;
    }
    if(lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringAC15)
    {
       acbMask |= LRM_ACB_SPECIAL_AC_15;
    }

   cellCfg->stCellCfgInfo.stAcbInfo.stAcBarringMoSig.bAcbForSpac = acbMask; 

    if(acbMask && 
          (lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringFactor != 0))
    {
       cellCfg->stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbFactor = RM_ACB_FACTOR_P00; 
    }
    else
    {
       cellCfg->stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbFactor = (CmRrmAcBarringFactor) 
         lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringFactor;
    }

    acbMask = 0x00;

    cellCfg->stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbTime = (CmRrmAcBarringTime)
       lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringTime;

    if(lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringAC11)
    {
       acbMask |= LRM_ACB_SPECIAL_AC_11; 
    }
    if(lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringAC12)
    {
       acbMask |= LRM_ACB_SPECIAL_AC_12;
    }
    if(lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringAC13)
    {
       acbMask |= LRM_ACB_SPECIAL_AC_13;
    }
    if(lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringAC14)
    {
       acbMask |= LRM_ACB_SPECIAL_AC_14;
    }
    if(lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringAC15)
    {
       acbMask |= LRM_ACB_SPECIAL_AC_15;
    }

    cellCfg->stCellCfgInfo.stAcbInfo.stAcBarringMoData.bAcbForSpac = acbMask; 

    if(acbMask && 
          (lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringFactor != 0))
    {
       cellCfg->stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbFactor = RM_ACB_FACTOR_P00; 
    }
    else
    {
       cellCfg->stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbFactor = (CmRrmAcBarringFactor) 
         lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringFactor;
    }
    cellCfg->stCellCfgInfo.flagTransMode        = lteeNodeBparams[cellCfgIdx].lteTransModeCellCfg.transModeUse;
    RLOG1(L_INFO,"DLFSS is %d",cellCfg->stCellCfgInfo.flagDlfsScheduling);
#ifdef INTEL_FDD_NODLFSS
    if(cellCfg->stCellCfgInfo.flagDlfsScheduling == 1)
    {
       RLOG0(L_ERROR,"DLFSS is not supported in INTEL FDD,So Disabling it");
       cellCfg->stCellCfgInfo.flagDlfsScheduling = 0;
    }
#endif
     

   RETVOID;
}
/*
 *
 *       Fun:   wrSmmEnbBuildRmuProtCellCfg
 *
 *       Desc:  This function is used for filling cell configuration in RRM
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
#ifdef ANSI 
PUBLIC S16 wrSmmEnbBuildRmuProtCellCfg(LrmCellConfiguration *cellCfg , U8 cellCfgIdx)
#else
PUBLIC S16 wrSmmEnbBuildRmuProtCellCfg(cellCfg , cellCfgIdx)
   LrmCellConfiguration *cellCfg;
   U8  cellCfgIdx;
#endif
{

   U16 usNumSpsUePerTti;
   U16 usTotalSpsN1PucchRes;
#ifdef LTE_ADV
   U16 usTotalCaN1PucchRes;
#endif
#ifdef LTE_TDD
   U8              maxUeSchdPerUlSf[LRM_UL_DL_CONFIG_MAX] = {1,2,4,5,7,9,2};
#endif   

   TRC2(wrSmmEnbBuildRmuProtCellCfg);

   cellCfg->enCellAddModDel = LRM_PROTOCFG_ADD_CELL;

   cellCfg->stCellCfgInfo.bCellId              = cellCfgIdx+1; /*currently we support only one cell*/
   cellCfg->stCellCfgInfo.enCellDlBandWidth    = 
      lteeNodeBparams[cellCfgIdx].lteCellMibCfgGrp.dlBw[0];
   /*Filling ACB params*/
   wrSmmEnbFillRmuAcbInfo(cellCfg, cellCfgIdx);
   cellCfg->stCellCfgInfo.usMaxUlBroadbandBw   = 10; /*TODO*/
   cellCfg->stCellCfgInfo.usMaxDlBroadbandBw   = 10; /*TODO*/
   cellCfg->stCellCfgInfo.bNRbCqi              = 
      lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.nRBCqi;
   cellCfg->stCellCfgInfo.bNCsAn               = 
      lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.nCSAN;
   cellCfg->stCellCfgInfo.bMaxActiveUesServed  = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxUeSupp;
   cellCfg->stCellCfgInfo.bMaxSigUesServed     = (lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxUeSupp + 
         WR_MAX_SR_CQI_NOT_CONFIGURED_UES);

   /* RRM_SP1_START */
   cellCfg->stCellCfgInfo.bMaxAvgGbrPrbUsage = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxAvgGbrPrbUsage;
   cellCfg->stCellCfgInfo.bRbcQci1TmngReq = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci1TmngReq;
   cellCfg->stCellCfgInfo.bRbcQci2TmngReq = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci2TmngReq;
   cellCfg->stCellCfgInfo.bRbcQci3TmngReq = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci3TmngReq;
   cellCfg->stCellCfgInfo.bRbcQci4TmngReq = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci4TmngReq;
   cellCfg->stCellCfgInfo.bRbcQci4TmngReqEnable = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci4TmngReqEnable;
   cellCfg->stCellCfgInfo.bDuplexMode = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.duplexMode;
   cellCfg->stCellCfgInfo.bNumDlNewUesPerTti = lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.maxUePerDlSf;
   cellCfg->stCellCfgInfo.bNumUlNewUesPerTti = lteeNodeBparams[cellCfgIdx].lteCellUlSchdCfgGrp.maxUePerUlSf;
   cellCfg->stCellCfgInfo.bArpForEmergencyBearer = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.emergencyServicePriorityLevel;
   /* reserving default number of DL re-Tx UEs per TTI to 1 */
   cellCfg->stCellCfgInfo.bNumDlReTxUesPerTti = wrSmDfltMinDlReTxUesPerTti;
   cellCfg->stCellCfgInfo.bNumUlReTxUesPerTti = wrSmDfltMinUlReTxUesPerTti;
   /* RRM_SP1_END */

   cellCfg->stCellCfgInfo.flagDlfsScheduling   = 
      lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.dlfsSchd;
   cellCfg->stCellCfgInfo.bWaitTime            = 3;  /*TODO: Pick from OAM*/
   cellCfg->stCellCfgInfo.bRcmAlgoType = 1; /* TODO */

   cellCfg->stCellCfgInfo.bNumTxAnt = 
      lteeNodeBparams[cellCfgIdx].lteAntenna_Common_Config.numAntPorts;
   RLOG2(L_DEBUG,"\nwrSmmEnbBuildRmuProtCellCfg:numAntPorts=%d:cellCfg->stCellCfgInfo.bNumTxAnt=%d\n",
   lteeNodeBparams[cellCfgIdx].lteAntenna_Common_Config.numAntPorts,
   cellCfg->stCellCfgInfo.bNumTxAnt);
   /* CR Fix :- ccpu00136285 and ccpu00137294*/

   cellCfg->stCellCfgInfo.enSrPrdcty           = 
      lteeNodeBparams[cellCfgIdx].lteRrmTddParam.srPrdcty;
   cellCfg->stCellCfgInfo.enCqiPrdcty          = 
      lteeNodeBparams[cellCfgIdx].lteRrmTddParam.cqiPrdcty;
   cellCfg->stCellCfgInfo.usNumSrResPerTti     = 
      lteeNodeBparams[cellCfgIdx].lteRrmTddParam.numSrPerTti;
   cellCfg->stCellCfgInfo.usNumCqiResPerTti    = 
      lteeNodeBparams[cellCfgIdx].lteRrmTddParam.numCqiPerTti;
   cellCfg->stCellCfgInfo.bSimulCqiAckNack     = 
      lteeNodeBparams[cellCfgIdx].lteRrmTddParam.simulAckNackEnb;
#ifdef LTE_TDD 
   cellCfg->stCellCfgInfo.enUlDlConfig         = 
      lteeNodeBparams[cellCfgIdx].lteTddParam.subframeAssignment; /* TODO 1*/
   cellCfg->stCellCfgInfo.enSplSfCfg           = 
      lteeNodeBparams[cellCfgIdx].lteTddParam.specialSubFramePattern; /* TODO 7*/
#endif
   cellCfg->stCellCfgInfo.usN1Pucch            = 
      lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.n1PucchAn;
   cellCfg->stCellCfgInfo.enDsrTransMax        = wrSmDfltDsrTransMax; /* TODO 7*/
   /*Removed DRX Flag */
   cellCfg->stCellCfgInfo.stRmCellDrxCfg.bIsDrxEnabled = 
      lteeNodeBparams[cellCfgIdx].lteDrxCfgParams.isDrxEnabled;
   cellCfg->stCellCfgInfo.stRmCellDrxCfg.usDrxInactvTmr = 
      lteeNodeBparams[cellCfgIdx].lteDrxCfgParams.drxInactvTmr;
   cellCfg->stCellCfgInfo.stRmCellDrxCfg.bDrxRetxTmr = 
      (U8)lteeNodeBparams[cellCfgIdx].lteDrxCfgParams.drxRetxTmr;

   cellCfg->stCellCfgInfo.stRmCellDrxCfg.usLongDrxCycleGbr    = 
      lteeNodeBparams[cellCfgIdx].lteDrxCfgParams.drxLongCycleOffst.longDrxCycleGbr; 
   cellCfg->stCellCfgInfo.stRmCellDrxCfg.usLongDrxCycleNonGbr = 
      lteeNodeBparams[cellCfgIdx].lteDrxCfgParams.drxLongCycleOffst.longDrxCycleNonGbr; 
   /*DRX QCI*/
   cellCfg->stCellCfgInfo.stRmCellDrxCfg.bIsGbrDrxDis = 
      lteeNodeBparams[cellCfgIdx].lteDrxCfgParams.isDRXQCIEnabled;

   /* SPS changes starts */
   cellCfg->stCellCfgInfo.stSpsCellCfg.bIsSpsEnabled = 
      lteeNodeBparams[cellCfgIdx].stSpsCellCfg.bIsSpsEnabled;
   if (cellCfg->stCellCfgInfo.stSpsCellCfg.bIsSpsEnabled == TRUE)
   {
      cellCfg->stCellCfgInfo.stSpsCellCfg.usMaxDlSpsUePerTti = 
         lteeNodeBparams[cellCfgIdx].stSpsCellCfg.maxDlSpsUePerTti;
      cellCfg->stCellCfgInfo.stSpsCellCfg.usMaxUlSpsUePerTti = 
         lteeNodeBparams[cellCfgIdx].stSpsCellCfg.maxUlSpsUePerTti;
   }
   /* SPS changes ends */

   /* Ca Dev Start */
   cellCfg->stCellCfgInfo.usMaxDlUePerTti = 
      lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.maxDlUeNewTxPerTti;
#ifdef LTE_ADV
   cellCfg->stCellCfgInfo.bIsCaEnabled  = 
      lteeNodeBparams[cellCfgIdx].caGenCfg.isCaEnabled;
#endif
   /* Ca Dev End */

   if(cellCfg->stCellCfgInfo.stSpsCellCfg.usMaxDlSpsUePerTti <
         cellCfg->stCellCfgInfo.stSpsCellCfg.usMaxUlSpsUePerTti)
   {
      usNumSpsUePerTti = cellCfg->stCellCfgInfo.stSpsCellCfg.usMaxUlSpsUePerTti;
   }
   else
   {
      usNumSpsUePerTti = cellCfg->stCellCfgInfo.stSpsCellCfg.usMaxDlSpsUePerTti;
   }
#ifdef LTE_TDD 
   usTotalSpsN1PucchRes = usNumSpsUePerTti * \
                          maxUeSchdPerUlSf[cellCfg->stCellCfgInfo.enUlDlConfig];
#else
   usTotalSpsN1PucchRes = usNumSpsUePerTti;
#endif 

#ifdef LTE_ADV
   /* Calculating number of N1 resources required for CA 1BCS */
#ifdef LTE_TDD

   if (cellCfg->stCellCfgInfo.enUlDlConfig == LRM_UL_DL_CONFIG_1)
   {
      /* UL DL Config 1 */
      usTotalCaN1PucchRes = cellCfg->stCellCfgInfo.usMaxDlUePerTti * 2;
   }
   else
   {
      /* UL DL Config 2 only for now*/
      usTotalCaN1PucchRes = cellCfg->stCellCfgInfo.usMaxDlUePerTti * 4;
   }
#else

   usTotalCaN1PucchRes = cellCfg->stCellCfgInfo.usMaxDlUePerTti;
#endif/*LTE_TDD*/
   usTotalCaN1PucchRes = usTotalCaN1PucchRes * 2;
#endif/*LTE_ADV*/

   if( lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.n1PucchAn <
         (cellCfg->stCellCfgInfo.usNumSrResPerTti + usTotalSpsN1PucchRes))
   {
      RLOG3(L_ERROR,"SM : Not Enough N1 PUCCH resources are available, "
            "so Changing it"
            "usN1Pucch(%d), bNumSrPerTti(%d), usTotalSpsN1PucchRes(%d)\n",
            lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.n1PucchAn,
            cellCfg->stCellCfgInfo.usNumSrResPerTti, usTotalSpsN1PucchRes);
      lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.n1PucchAn =
         cellCfg->stCellCfgInfo.usNumSrResPerTti + usTotalSpsN1PucchRes;
   }
   cellCfg->stCellCfgInfo.usN1Pucch  = 
      lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.n1PucchAn;

   /* HCSG_DEV Start */
   if(lteeNodeBparams[cellCfgIdx].lteFapAccessParams.accessMode == WR_ENB_HYBRID_ACCESS)
   {
      cellCfg->stCellCfgInfo.usMaxNonCsgUes   = wrSmDfltMaxNonCsgUEs;
      cellCfg->stCellCfgInfo.usMaxCsgUes      = wrSmDfltMaxCsgUEs;
      cellCfg->stCellCfgInfo.usMaxExtraUes    = 
         ceil(cellCfg->stCellCfgInfo.bMaxActiveUesServed * 0.25);
      cellCfg->stCellCfgInfo.usAccessMode     = lteeNodeBparams[cellCfgIdx].lteFapAccessParams.accessMode;
   }
   else
   {
      cellCfg->stCellCfgInfo.usMaxNonCsgUes = 0;
      cellCfg->stCellCfgInfo.usMaxCsgUes    = wrSmDfltMaxCsgUEs;
      cellCfg->stCellCfgInfo.usMaxExtraUes  =  0;
   }
   /* HCSG_DEV End */
   RETVALUE(ROK);
}
/*
 *
 *       Fun:   wrSmmEnbBuildRmuProtCellDel
 *
 *       Desc:  This function is used for filling cell configuration in RRM
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
#ifdef ANSI 
PUBLIC S16 wrSmmEnbBuildRmuProtCellDel(LrmCellConfiguration *cellCfg, U8 cellCfgIdx)
#else
PUBLIC S16 wrSmmEnbBuildRmuProtCellDel(cellCfg, cellCfgIdx)
   LrmCellConfiguration *cellCfg;
   U8 cellCfgIdx;
#endif
{
   TRC2(wrSmmEnbBuildRmuProtCellDel);

   cellCfg->enCellAddModDel = LRM_PROTOCFG_DEL_CELL;

   cellCfg->stCellCfgInfo.bCellId              = cellCfgIdx + 1; /*currently we support only one cell*/
   cellCfg->stCellCfgInfo.enCellDlBandWidth    = 
      lteeNodeBparams[cellCfgIdx].lteCellMibCfgGrp.dlBw[0];
   cellCfg->stCellCfgInfo.usMaxUlBroadbandBw   = 10; /*TODO*/
   cellCfg->stCellCfgInfo.usMaxDlBroadbandBw   = 10; /*TODO*/
   cellCfg->stCellCfgInfo.bNRbCqi              = 
      lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.nRBCqi;
   cellCfg->stCellCfgInfo.bNCsAn               = 
      lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.nCSAN;
   cellCfg->stCellCfgInfo.bMaxActiveUesServed  = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxUeSupp;
   cellCfg->stCellCfgInfo.bMaxSigUesServed     = 
      lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxUeSupp + WR_MAX_SR_CQI_NOT_CONFIGURED_UES;  /*TODO*/
   /* RRM_SP1_START */
   cellCfg->stCellCfgInfo.bMaxAvgGbrPrbUsage = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.maxAvgGbrPrbUsage;
   cellCfg->stCellCfgInfo.bRbcQci1TmngReq = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci1TmngReq;
   cellCfg->stCellCfgInfo.bRbcQci2TmngReq = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci2TmngReq;
   cellCfg->stCellCfgInfo.bRbcQci3TmngReq = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci3TmngReq;
   cellCfg->stCellCfgInfo.bRbcQci4TmngReq = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci4TmngReq;
   cellCfg->stCellCfgInfo.bRbcQci4TmngReqEnable = lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci4TmngReqEnable;
   cellCfg->stCellCfgInfo.bDuplexMode = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.duplexMode;
   cellCfg->stCellCfgInfo.bNumDlNewUesPerTti = lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.maxUePerDlSf;
   cellCfg->stCellCfgInfo.bNumUlNewUesPerTti = lteeNodeBparams[cellCfgIdx].lteCellUlSchdCfgGrp.maxUePerUlSf;
   cellCfg->stCellCfgInfo.bArpForEmergencyBearer = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.emergencyServicePriorityLevel;
   /* reserving default number of DL re-Tx UEs per TTI to 1 */
   cellCfg->stCellCfgInfo.bNumDlReTxUesPerTti = wrSmDfltMinDlReTxUesPerTti;
   cellCfg->stCellCfgInfo.bNumUlReTxUesPerTti = wrSmDfltMinUlReTxUesPerTti;
   /* RRM_SP1_END */

   cellCfg->stCellCfgInfo.flagDlfsScheduling   = 
      lteeNodeBparams[cellCfgIdx].lteCellDlSchdCfgGrp.dlfsSchd;
   cellCfg->stCellCfgInfo.bWaitTime            = 3;  /*TODO: Pick from OAM*/
   cellCfg->stCellCfgInfo.flagTransMode        = lteeNodeBparams[cellCfgIdx].lteTransModeCellCfg.transModeUse;
   cellCfg->stCellCfgInfo.bRcmAlgoType = 1; /* TODO */
   /* CR Fix :- ccpu00136285 and ccpu00137294*/

   cellCfg->stCellCfgInfo.bNumTxAnt = 
      lteeNodeBparams[cellCfgIdx].lteAntenna_Common_Config.numAntPorts;
   RLOG2(L_DEBUG,"\nwrSmmEnbBuildRmuProtCellDel:numAntPorts=%d:cellCfg->stCellCfgInfo.bNumTxAnt=%d\n",
   lteeNodeBparams[cellCfgIdx].lteAntenna_Common_Config.numAntPorts,
   cellCfg->stCellCfgInfo.bNumTxAnt);

   cellCfg->stCellCfgInfo.stRmCellDrxCfg.bIsDrxEnabled = 
      lteeNodeBparams[cellCfgIdx].lteDrxCfgParams.isDrxEnabled;
   cellCfg->stCellCfgInfo.stRmCellDrxCfg.usDrxInactvTmr = 
      lteeNodeBparams[cellCfgIdx].lteDrxCfgParams.drxInactvTmr;
   cellCfg->stCellCfgInfo.stRmCellDrxCfg.bDrxRetxTmr = 
      (U8)lteeNodeBparams[cellCfgIdx].lteDrxCfgParams.drxRetxTmr;

   cellCfg->stCellCfgInfo.stRmCellDrxCfg.usLongDrxCycleGbr    = 
      lteeNodeBparams[cellCfgIdx].lteDrxCfgParams.drxLongCycleOffst.longDrxCycleGbr; 
   cellCfg->stCellCfgInfo.stRmCellDrxCfg.usLongDrxCycleNonGbr = 
      lteeNodeBparams[cellCfgIdx].lteDrxCfgParams.drxLongCycleOffst.longDrxCycleNonGbr; 
   RETVALUE(ROK);
}
/*
 *
 *       Fun:   wrSmmEnbBuildRmuProtMmeCfg
 *
 *       Desc:  This function is used for filling Mme configuration in RRM
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
#ifdef ANSI 
PUBLIC S16 wrSmmEnbBuildRmuProtMmeCfg
(
 U16 mmeId, 
 LrmEnbConfiguration *enbCfg, 
 U32 action
 )
#else
PUBLIC S16 wrSmmEnbBuildRmuProtMmeCfg(mmeId, enbCfg, action)
   U16                 mmeId;
   LrmEnbConfiguration *enbCfg;
   U32                 action;
#endif
{
   TRC2(wrSmmEnbBuildRmuProtMmeCfg);

   enbCfg->bCfgType = RRM_ENB_CFG_MME_CFG;
   enbCfg->u.stMmeCfg.enMmeAddModOrDel = action;
   enbCfg->u.stMmeCfg.usMmeId        = mmeId;

   RETVALUE(ROK);
}
/*
 *
 *       Fun:   wrSmmEnbBuildRmuProtEnbCfg
 *
 *       Desc:  This function is used for filling Enb configuration in RRM
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
#ifdef ANSI 
PUBLIC S16 wrSmmEnbBuildRmuProtEnbCfg(LrmEnbConfiguration *enbCfg, U8 cellCfgIdx)
#else
PUBLIC S16 wrSmmEnbBuildRmuProtEnbCfg(enbCfg,cellCfgIdx)
   LrmEnbConfiguration *enbCfg;
   U8 cellCfgIdx;
#endif
{
   TRC2(wrSmmEnbBuildRmuProtEnbCfg);

   enbCfg->bCfgType = RRM_ENB_CFG_SYS_CFG;
   enbCfg->u.bMaxNumCells = lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.numOfCells ;

   RETVALUE(ROK);
}
#endif /*RM_INTF*/
/*
 * 
 *       Fun:   smGetEnbType
 *
 *       Desc:  This function is get EnbType from phyCellId, smallCellPci and smallCellPciRange 
 *
 *       Ret:   EnbType [WR_ENODEB_TYPE_HOME / WR_ENODEB_TYPE_MACRO]
 *
 *       Notes: None
 *              
 *       File:  wr_smm_enb_utils.c
 *
 */
#ifdef ANSI 
PUBLIC U8 smGetEnbType(U16 phyCellId, U8 cellCfgIdx)
#else
PUBLIC U8 smGetEnbType(phyCellId, cellCfgIdx)
   U16 phyCellId;
   U8 cellCfgIdx;
#endif
{
   U16 smallCellStartPci = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.startPci;
   U16 smallCellPciRange = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.pciRange;
   if ((phyCellId >= smallCellStartPci) && \
         (phyCellId <= (smallCellStartPci + smallCellPciRange)))
   {
      RETVALUE(WR_ENODEB_TYPE_HOME);
   }
   else
   {
      RETVALUE(WR_ENODEB_TYPE_MACRO);
   }
}/*end of smGetEnbType*/

#ifdef WR_RSYS_OAM
/*
 *
 *       Fun:   wrSmmEnbStaticCfgReq
 *
 *       Desc:  This function is to conform MIB is populated we can start cfg start layere
 *
 *       Ret:   None
 *
 *       Notes: <NONE>
 *
 *       File:  wr_enb_cmnplt_enbapp.c
 *
 */
PUBLIC S16 wrSmmEnbStaticCfgReq(Void)
{
   U16 smEvent;
#ifdef TENB_AS_SECURITY
   U32 loopCnt = 0;
#endif

   TRC2(wrSmmEnbStaticCfgReq);

#ifndef NL
   if(ROK != wrSmmEnbValidateConfigParams(WR_SM_DFLT_CELL_INDX))
   {
      RLOG0(L_ERROR, "wrSmmEnbValidateConfigParams Failed");
      RETVALUE(RFAILED);
   }
#endif
   wrSmmEnbInitFreePeerIdList(); /*initialize free peerId list*/


   if(ROK != wrSmmEnbInitMmeCfg())
   {
      RLOG0(L_ERROR, "unable to wrSmmEnbInitMmeCfg");
      RETVALUE(RFAILED);
   }

#ifdef TENB_AS_SECURITY
   for(loopCnt = 0; loopCnt < WR_MAX_AS_SEC_ALGOS; loopCnt++)
   {
      wreNodBPriIntgAlgo[loopCnt].pres = FALSE;
      wreNodBPriCiphAlgo[loopCnt].pres = FALSE;
   }
   for(loopCnt = 0; loopCnt < WR_MAX_AS_SEC_ALGOS; loopCnt++)
   {
      if((lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSmCellCfg.genUeCfg.intgAlgo[loopCnt] < \
               WR_MAX_AS_SEC_ALGOS) && \
            (lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSmCellCfg.genUeCfg.intgAlgo[loopCnt] >= 0))
      {
         wreNodBPriIntgAlgo[loopCnt].pres= TRUE;
         wreNodBPriIntgAlgo[loopCnt].val = 
            lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSmCellCfg.genUeCfg.intgAlgo[loopCnt];
      }
   }
   for(loopCnt = 0; loopCnt < WR_MAX_AS_SEC_ALGOS; loopCnt++)
   {
      if((lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSmCellCfg.genUeCfg.ciphAlgo[loopCnt] < \
               WR_MAX_AS_SEC_ALGOS) && \
            (lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSmCellCfg.genUeCfg.ciphAlgo[loopCnt] >= 0))
      {
         wreNodBPriCiphAlgo[loopCnt].pres= TRUE;
         wreNodBPriCiphAlgo[loopCnt].val = 
            lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSmCellCfg.genUeCfg.ciphAlgo[loopCnt];
      }
   }
#endif

   if(ROK != wrSmmEnbInitDbgCfg())
   {
      RLOG0(L_ERROR, "unable to wrSmmEnbInitDbgCfg");
      RETVALUE(RFAILED);
   }

#ifndef LTE_ENB_PERF
   smEvent = EVTWRSONCFG;
#else /* if not defined LTE_ENB_PERF */
   smEvent = EVTWRAPPCFG;
#endif /* end of LTE_ENB_PERF */
   /* Invoke the state machine */
   smCb.smState = WR_SM_STATE_INIT;

   /* Register and Initiallize Timer */   

   if (smRegInitTmr() != ROK)
   {
      RLOG0(L_ERROR, "smRegInitTmr Failed");
      RETVALUE(RFAILED);
   }

   cmInitTimers(&(smCb.cfgCb.guardCfgTmr), 1); /* Guard (Static/Dynamic Cfg) Timer  */

   smWrProcSm((U8)smEvent);

/*aug27_stats_fix*/
#ifdef TENB_STATS
   if (TSInfInitStatsFrmWork(fapParameters.tenbStatsCfg.tenbSocketStats,
            fapParameters.tenbStatsCfg.tenbFileStats,
            fapParameters.tenbStatsCfg.tenbConsoleStats,
            fapParameters.tenbStatsCfg.tenbStatsPeriodicity,
            fapParameters.tenbStatsCfg.tendStatsSocketPort) != ROK)
   {
      RLOG0(L_ERROR, "TENB_STATS Wrong Cfgn");
      RETVALUE(RFAILED);
   }
   TSInfSetEnbIp(fapParameters.lteEnodebIpAddr.enbIpAddr);
   printf("\nTENB_STATS:tenbSocketStats=%d:tenbFileStats=%d:tenbConsoleStats=%d\n",
                   fapParameters.tenbStatsCfg.tenbSocketStats,
                   fapParameters.tenbStatsCfg.tenbFileStats,
                   fapParameters.tenbStatsCfg.tenbConsoleStats);

   printf("\nAUG27_TENB_STATS:tenbStatsPeriodicity=%ld:tendStatsSocketPort=%ld:enbIpAddr=%ld\n",
                   fapParameters.tenbStatsCfg.tenbStatsPeriodicity,
                   fapParameters.tenbStatsCfg.tendStatsSocketPort,
                   fapParameters.lteEnodebIpAddr.enbIpAddr);
#endif
#ifdef RSYS_WIRESHARK
   wrInitWireShark();
#endif
/*aug27_stats_fix*/
   RETVALUE(ROK);
}/*wrSmmEnbStaticCfgReq*/

/*
 *
 *       Fun:   smPackStartStopStackReq
 *
 *       Desc:  packing and sending dynamic configuration to SM
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *
 *       File:  wr_smm_dyncfg.c
 *
 */ 

PRIVATE S16 smPackStartStopStackReq(U8 isPerdREMReq,U8 isStackStart,U8 isImmediate)
{
   Pst    smPst;
   Buffer *mBuf;          /* message buffer */

   TRC2(smPackStartStopStackReq);

   SM_SET_ZERO(&smPst, sizeof(Pst));

   smPst.dstProcId = SM_SM_PROC;
   smPst.srcProcId = SM_SM_PROC;
   smPst.dstEnt = ENTSM;
   smPst.srcEnt = ENTWR;
   smPst.dstInst = 0;
   smPst.srcInst = 0;
   smPst.event  = EVTSTKSTRSTPREQ;
   smPst.pool   = WR_POOL;
   smPst.selector= SM_SELECTOR_LC;

   if(SGetMsg(DFLT_REGION, WR_POOL, &mBuf) != ROK)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   } /* end of if statement */

   SAddPstMsgMult((Data *)&(isImmediate), (MsgLen) sizeof(U8), mBuf);
   SAddPstMsgMult((Data *)&(isStackStart), (MsgLen) sizeof(U8), mBuf);
   SAddPstMsgMult((Data *)&(isPerdREMReq), (MsgLen) sizeof(U8), mBuf);

   RETVALUE(SPstTsk(&smPst, mBuf));
} /* end of smPackSendAdminChange */

/*
 *
 *       Fun:   MsmStartStopStackReq.
 *
 *       Desc:  While stack is running anf HeMS changed the admin state 
 *              this function will handle the eNodeB state
 *
 *       Ret:   ROK
 *
 *       Notes: 
 *              If true Unlocked with permission to serve traffic (and enable RF transmitter(s)).
 *              If false Locked. Transition FAP to state where it is NOT permitted to serve traffic. RF transmitter is disabled.
 *
 *       File:  wr_sm_wr_cntrl.c
 *
 */
PUBLIC Void MsmStartStopStackReq(U8 isPerdREMReq,U8 isStackStart,U8 isImmediate)
{
   TRC2(MsmStartStopStackReq);

   smPackStartStopStackReq(isPerdREMReq,isStackStart,isImmediate);

   RETVOID;
} /*end of MsmStartStopStackReq*/

/*
 *
 *       Fun:   smStartStopStack.
 *
 *       Desc:  While stack is running anf HeMS changed the admin state 
 *              this function will handle the eNodeB state
 *
 *       Ret:   ROK
 *
 *       Notes: 
 *              If true Unlocked with permission to serve traffic (and enable RF transmitter(s)).
 *              If false Locked. Transition FAP to state where it is NOT permitted to serve traffic. RF transmitter is disabled.
 *
 *       File:  wr_smm_enb_utils.c
 *
 */
PUBLIC S16 smStartStopStack(U8 isPerdREMReq,U8 isStackStart,U8 isImmediate)
{
   TRC2(smStartStopStack);

   /*  CmTptAddr addr; */
   if(TRUE == isStackStart)
   {
      if(fapParameters.lteEnodebIpAddr.ipv4pres == TRUE)
      {
         smCb.smState = WR_SM_STATE_INIT;
         if (smCb.reCfg == TRUE)
         {
            wrEmmCb.datAppAddr[WR_IPV4_IDX].type = CM_TPTADDR_IPV4;
            wrEmmCb.datAppAddr[WR_IPV4_IDX].u.ipv4TptAddr.address = \
                                                                    fapParameters.lteEnodebIpAddr.enbIpAddr;
         }
      }
      if(fapParameters.lteEnodebIpAddr.ipv6pres == TRUE)
      {
         CmTptAddr addr;
         addr.type = CM_TPTADDR_IPV6;
         cmMemcpy((U8*)addr.u.ipv6TptAddr.ipv6NetAddr,
               (U8*)fapParameters.lteEnodebIpAddr.enbIpv6Addr, sizeof(CmInetIpAddr6));

         smCb.smState = WR_SM_STATE_INIT;
         if (smCb.reCfg == TRUE)
         {
            cmMemcpy((U8*)wrEmmCb.datAppAddr[WR_IPV6_IDX].u.ipv6TptAddr.ipv6NetAddr, 
                  (U8*)fapParameters.lteEnodebIpAddr.enbIpv6Addr, sizeof(CmInetIpAddr6));
         }

      }
      smWrProcSm(EVTWRSONCFG);
      sendKick = TRUE;
   }
   else
   {
#ifdef TENB_T2K3K_SPECIFIC_CHANGES
      if(smCb.isPciMod == TRUE)
#endif
      {
         smCb.reCfg = TRUE;
         smCb.syncState = FALSE; 
      }
      if( (isPerdREMReq == TRUE) &&(isImmediate == TRUE))
      {
         smCb.prem = TRUE;
         wrWatchdogSendRemovePid(0); 
         smBuildShutRestart();
      }
      else if ((isPerdREMReq == TRUE) && (isImmediate == FALSE))
      {
         smCb.prem = TRUE;
      }
      else
      {
         wrWatchdogSendRemovePid(0);
         smBuildShutRestart();
      }
   }
   RETVALUE(ROK);
} /*end of smStartStopStack*/

/*
 *
 *       Fun:  wrSmmEnbInitMmeCfg 
 *
 *       Desc:  This function is used for filling mme configuration in smCb
 *
 *       Ret:   Void
 *
 *       Notes: None
 *              
 *       File:  fc_smm_enbapp_cmnplatutils.c 
 *
 */
#ifdef ANSI 
PUBLIC S16 wrSmmEnbInitMmeCfg()
#else
PUBLIC S16 wrSmmEnbInitMmeCfg()
#endif
{ 
   U32                  idx = 0;
   U8                   idx1 = 0;
   U8                   idx2 = 0;
   U8                   idx3 = 0;
   U8 emtpyIpv6Addr[WR_IPV6_ADDR_LEN] = {0};
   Mmeiptype            *mmeIpType = NULLP;
   CmTptAddr            addr;

   U8                   ret = ROK;
   LwrSmMmeCfg          *mmeCfg = NULLP;
   MsmLteeNodeBIPparams *mmeIpParam = NULLP;

   TRC2(wrSmmEnbInitMmeCfg);

   mmeIpParam = &fapParameters.lteeNodeBIPparams;
   smCfgCb.freeMmeIdx  = 0;
   smCfgCb.numMmeAdded = 0;
   smCfgCb.noMmeAddCfm = 0;
   smCfgCb.noMmeDelCfm = 0;

   smCfgCb.noOfCfg = mmeIpParam->lteS1connmode;
   if((smCfgCb.noOfCfg <= 0) || (smCfgCb.noOfCfg > LWR_SM_MAX_MMES))
   {
      RLOG1(L_ERROR, "Error Number of MME = %d",smCfgCb.noOfCfg);
      RETVALUE(RFAILED);
   }
   idx1 = 0;
   for(idx = 0; idx < smCfgCb.noOfCfg; idx++)
   {
      idx3 = 0;
      WR_ALLOC(&mmeCfg, sizeof(LwrSmMmeCfg));
      if(mmeCfg == NULLP)
      {
         RLOG1(L_FATAL, "Memory allocation failed for Number of MME = %d",
               smCfgCb.noOfCfg);
         RETVALUE(RFAILED);
      }
      mmeCfg->mmeId = idx +1;
      /* check for duplicate MME primary ip */
      for(idx2 = 0; idx2 < idx; idx2++)
      {
         /*Check If MME ip is IPV4*/
         if(mmeIpParam->lteSiglinkserverlist[idx].ipv4pres == TRUE)
         {
            if((0 == mmeIpParam->lteSiglinkserverlist[idx].mmeipv4) || (smCfgCb.mmeCfg[idx2]->mmeAddr[idx1].u.ipv4TptAddr.address == mmeIpParam->lteSiglinkserverlist[idx].mmeipv4))
            {
               ret = RFAILED;
               break;
            }
            mmeIpType = &mmeIpParam->lteSiglinkserverlist[idx];
            if((mmeIpType->ipv4pres == TRUE) && (mmeIpType->mmeipv4 == 0))
            {
               ret = RFAILED;
               break;
            }
         }

         /*Check If MME ip is IPV6*/
         if(mmeIpParam->lteSiglinkserverlist[idx].ipv6pres == TRUE)
         {
            if((ROK == cmMemcmp((U8*)&mmeIpParam->lteSiglinkserverlist[idx].mmeipv6,(U8*)&emtpyIpv6Addr, sizeof(CmInetIpAddr6)))||(ROK == cmMemcmp((U8*)&smCfgCb.mmeCfg[idx2]->mmeAddr[idx1].u.ipv6TptAddr.ipv6NetAddr,(U8*)&mmeIpParam->lteSiglinkserverlist[idx].mmeipv6,sizeof(CmInetIpAddr6))))
            {
               ret = RFAILED;
               break;
            }
            mmeIpType = &mmeIpParam->lteSiglinkserverlist[idx];
            if((mmeIpType->ipv6pres == TRUE) && (ROK == cmMemcmp((U8*)&mmeIpType->mmeipv4,(U8*)&emtpyIpv6Addr, sizeof(CmInetIpAddr6))))
            {
               ret = RFAILED;
               break;
            }
         }
      }
      if(ROK == ret)
      {
         if(fapParameters.lteeNodeBIPparams.lteSiglinkserverlist[idx1].ipv4pres == TRUE)
         {   
            addr.type = CM_TPTADDR_IPV4;
            addr.u.ipv4TptAddr.address =fapParameters.lteeNodeBIPparams.lteSiglinkserverlist[idx1].mmeipv4;
            wrCpyCmTptAddr(&mmeCfg->mmeAddr[idx3++],&addr);
         }
         if(fapParameters.lteeNodeBIPparams.lteSiglinkserverlist[idx1].ipv6pres == TRUE)
         {
            addr.type = CM_TPTADDR_IPV6;
            cmMemcpy((U8*)addr.u.ipv6TptAddr.ipv6NetAddr,(U8*)fapParameters.lteeNodeBIPparams.lteSiglinkserverlist[idx1].mmeipv6, sizeof(CmInetIpAddr6));

            wrCpyCmTptAddr(&mmeCfg->mmeAddr[idx3++],&addr);
         }
         idx1++;
      }
      if(RFAILED != wrSmmEnbValidateFillMmeIp(mmeCfg,&idx3,mmeIpParam->lteSecIp1[idx]))
      {
         if(RFAILED != wrSmmEnbValidateFillMmeIp(mmeCfg,&idx3,mmeIpParam->lteSecIp2[idx]))
         {
            if(RFAILED != wrSmmEnbValidateFillMmeIp(mmeCfg,&idx3,mmeIpParam->lteSecIp3[idx]))
            {
               wrSmmEnbValidateFillMmeIp(mmeCfg,&idx3,mmeIpParam->lteSecIp4[idx]);
            }
         }
      }
      mmeCfg->noOfIps = idx3;
      smCfgCb.mmeCfg[idx] = mmeCfg;
   }
   RETVALUE(ROK);
}/*end of wrSmmEnbInitMmeCfg*/

/*
 *
 *       Fun:  wrSmmEnbInitDbgCfg
 *
 *       Desc:  This function is used for filling Debug options in smCb
 *
 *       Ret:   Void
 *
 *       Notes: None
 *
 *       File:  wr_smm_enb_utils.c
 *
 */
#ifdef ANSI
PRIVATE S16 wrSmmEnbInitDbgCfg()
#else
PRIVATE S16 wrSmmEnbInitDbgCfg()
#endif
{

   TRC2(wrSmmEnbInitDbgCfg);

   smCfgCb.hiDbg = fapParameters.lteDbgParams.hiDbg;
   smCfgCb.sbDbg = fapParameters.lteDbgParams.sbDbg;
   smCfgCb.szDbg = fapParameters.lteDbgParams.szDbg;
   smCfgCb.egDbg = fapParameters.lteDbgParams.egDbg;
   smCfgCb.wrDbg = fapParameters.lteDbgParams.wrDbg;
   smCfgCb.nhDbg = fapParameters.lteDbgParams.nhDbg;
   smCfgCb.kwDbg = fapParameters.lteDbgParams.kwDbg;
   smCfgCb.rgDbg = fapParameters.lteDbgParams.rgDbg;
   smCfgCb.ysDbg = fapParameters.lteDbgParams.ysDbg;
   smCfgCb.smDbg = fapParameters.lteDbgParams.smDbg;
   smCfgCb.czDbg = fapParameters.lteDbgParams.czDbg;

   RETVALUE(ROK);
}/*end of wrSmmEnbInitDbgCfg*/


/*
 *
 *       Fun:  wrSmmEnbInitFreePeerIdList
 *
 *       Desc:  This function is used to intialize free peerId list
 *                          
 *
 *       Ret:   Void
 *
 *       Notes: None
 *              
 *       File:  fc_smm_enbapp_cmnplatutils.c 
 *
 */
#ifdef ANSI 
PUBLIC Void wrSmmEnbInitFreePeerIdList()
#else
PUBLIC Void wrSmmEnbInitFreePeerIdList()
#endif
{
   U16 idx;

   for(idx = 0; idx < WR_SMM_MAX_PEERID_SUPPORTED; idx++)
   {
      smCfgCb.freePeeIdList.peerId[idx] = idx+1; 
   }
   smCfgCb.freePeeIdList.freePeerIdIdx = 0;
   RETVOID;
}/*end of wrSmmEnbInitFreePeerIdList*/

/*
 *
 *       Fun:   wrSmmEnbFillNghEutraFreqParamToMsm
 *
 *       Desc:  This function is used for filling Neighbor 
 *              eutra freq parameter              
 *
 *       Ret:   Void
 *
 *       Notes: None
 *              
 *       File:  fc_smm_enb_utils.c 
 *
 */
#ifdef ANSI 
PUBLIC Void wrSmmEnbFillNghEutraFreqParamToMsm(MsmLteNeighEutraFreq *msmNghEutraFreq, 
      MsmLteNeighEutraFreq *msmNghEutraFreqDyn,
      U32 reCfgType)
#else
PUBLIC Void wrSmmEnbFillNghEutraFreqParamToMsm
(
 msmNghEutraFreq, 
 msmNghEutraFreqDyn, 
 reCfgType
 )
MsmLteNeighEutraFreq *msmNghEutraFreq;
MsmLteNeighEutraFreq *msmNghEutraFreqDyn;
U32 reCfgType;
#endif
{
   TRC2(wrSmmEnbFillNghEutraFreqParam);
   msmNghEutraFreq->reCfgType    = reCfgType;
   msmNghEutraFreq->freqIndex    = msmNghEutraFreqDyn->freqIndex;
   msmNghEutraFreq->status       = wrSmDfltStatus;
   msmNghEutraFreq->earfcnUl     = msmNghEutraFreqDyn->earfcnUl;
   msmNghEutraFreq->earfcnDl     = msmNghEutraFreqDyn->earfcnDl;
   msmNghEutraFreq->priority     = msmNghEutraFreqDyn->priority;
   msmNghEutraFreq->qRxLevMin    = msmNghEutraFreqDyn->qRxLevMin;
   msmNghEutraFreq->pMaxUsage    = wrSmDfltPMaxUsage;
   msmNghEutraFreq->pMax         = msmNghEutraFreqDyn->pMax;
   msmNghEutraFreq->tReselection = msmNghEutraFreqDyn->tReselection;
   msmNghEutraFreq->sfUsage      = wrSmDfltSfUsage;
   msmNghEutraFreq->tReselectionSFMed  = msmNghEutraFreqDyn->tReselectionSFMed;
   msmNghEutraFreq->tReselectionSFHigh = msmNghEutraFreqDyn->tReselectionSFHigh;
   msmNghEutraFreq->sIntraSearch   = msmNghEutraFreqDyn->sIntraSearch;
   msmNghEutraFreq->sNonIntraSearch  = msmNghEutraFreqDyn->sNonIntraSearch;
   msmNghEutraFreq->servThresholdLow     = msmNghEutraFreqDyn->servThresholdLow;
   msmNghEutraFreq->threshXHigh  = msmNghEutraFreqDyn->threshXHigh;
   msmNghEutraFreq->threshXLow   = msmNghEutraFreqDyn->threshXLow;
   msmNghEutraFreq->measBandwidth  = msmNghEutraFreqDyn->measBandwidth;
   msmNghEutraFreq->presAntennaPort1   = msmNghEutraFreqDyn->presAntennaPort1;
   msmNghEutraFreq->neighCellCfg       = msmNghEutraFreqDyn->neighCellCfg;
   msmNghEutraFreq->qOffsetFreq        = msmNghEutraFreqDyn->qOffsetFreq;
   msmNghEutraFreq->offsetFreq         = msmNghEutraFreqDyn->offsetFreq;
   msmNghEutraFreq->sIntraSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
   msmNghEutraFreq->sIntraSearchRel9.sSearchQRel9 =  wrSmDfltsSearchQRel9;
   msmNghEutraFreq->sInterSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
   msmNghEutraFreq->sInterSearchRel9.sSearchQRel9 = wrSmDfltsSearchQRel9;
   msmNghEutraFreq->qQualMinRel9  = wrSmDfltDualMinRel9;
   msmNghEutraFreq->reselecThreshQRel9  =  wrSmDfltReselecThreshQRel9;
   msmNghEutraFreq->threshXHighQR9 =  msmNghEutraFreqDyn->threshXHighQR9;
   msmNghEutraFreq->threshXLowQR9  =  msmNghEutraFreqDyn->threshXLowQR9;

}/*end of wrSmmEnbFillNghEutraFreqParam*/


/*
 *
 *       Fun:   wrSmmEnbFillNghEutraFreqParam
 *
 *       Desc:  This function is used for filling Neighbor 
 *              eutra freq parameter              
 *
 *       Ret:   Void
 *
 *       Notes: None
 *              
 *       File:  fc_smm_enb_utils.c 
 *
 */
#ifdef ANSI 
PUBLIC Void wrSmmEnbFillNghEutraFreqParam(LwrNeighEutraFreq *lwrNghEutraFreq, 
      MsmLteNeighEutraFreq *msmNghEutraFreq,
      U32 reCfgType)
#else
PUBLIC Void wrSmmEnbFillNghEutraFreqParam
(
 lwrNghEutraFreq, 
 msmNghEutraFreq, 
 reCfgType
 )
LwrNeighEutraFreq *lwrNghEutraFreq;
MsmLteNeighEutraFreq *msmNghEutraFreq;
U32 reCfgType;
#endif
{
   TRC2(wrSmmEnbFillNghEutraFreqParam);
   lwrNghEutraFreq->reCfgType    = reCfgType;
   lwrNghEutraFreq->freqIndex    = msmNghEutraFreq->freqIndex;
   lwrNghEutraFreq->status       = wrSmDfltStatus;
   lwrNghEutraFreq->earfcnUl     = msmNghEutraFreq->earfcnUl;
   lwrNghEutraFreq->earfcnDl     = msmNghEutraFreq->earfcnDl;
   lwrNghEutraFreq->priority     = msmNghEutraFreq->priority;
   lwrNghEutraFreq->qRxLevMin    = msmNghEutraFreq->qRxLevMin;
   lwrNghEutraFreq->pMaxUsage    = wrSmDfltPMaxUsage;
   lwrNghEutraFreq->pMax         = msmNghEutraFreq->pMax;
   lwrNghEutraFreq->tReselection = msmNghEutraFreq->tReselection;
   lwrNghEutraFreq->sfUsage      = wrSmDfltSfUsage;
   lwrNghEutraFreq->tReselectionSFMed  = msmNghEutraFreq->tReselectionSFMed;
   lwrNghEutraFreq->tReselectionSFHigh = msmNghEutraFreq->tReselectionSFHigh;
   lwrNghEutraFreq->sIntraSearch.pres  = PRSNT_NODEF;
   lwrNghEutraFreq->sIntraSearch.val   = msmNghEutraFreq->sIntraSearch;
   lwrNghEutraFreq->sNonIntraSearch.pres = PRSNT_NODEF;
   lwrNghEutraFreq->sNonIntraSearch.val  = msmNghEutraFreq->sNonIntraSearch;
   lwrNghEutraFreq->servThresholdLow     = msmNghEutraFreq->servThresholdLow;
   lwrNghEutraFreq->threshXHigh  = msmNghEutraFreq->threshXHigh;
   lwrNghEutraFreq->threshXLow   = msmNghEutraFreq->threshXLow;
   lwrNghEutraFreq->measBandwidth.pres =  PRSNT_NODEF;
   lwrNghEutraFreq->measBandwidth.val  = msmNghEutraFreq->measBandwidth;
   lwrNghEutraFreq->presAntennaPort1   = msmNghEutraFreq->presAntennaPort1;
   lwrNghEutraFreq->neighCellCfg       = msmNghEutraFreq->neighCellCfg;
   lwrNghEutraFreq->qOffsetFreq        = msmNghEutraFreq->qOffsetFreq;
   lwrNghEutraFreq->offsetFreq         = msmNghEutraFreq->offsetFreq;
   lwrNghEutraFreq->sIntraSearchRel9.pres =  PRSNT_NODEF;
   lwrNghEutraFreq->sIntraSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
   lwrNghEutraFreq->sIntraSearchRel9.sSearchQRel9 =  wrSmDfltsSearchQRel9;
   lwrNghEutraFreq->sInterSearchRel9.pres         = PRSNT_NODEF;
   lwrNghEutraFreq->sInterSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
   lwrNghEutraFreq->sInterSearchRel9.sSearchQRel9 = wrSmDfltsSearchQRel9;
   lwrNghEutraFreq->qQualMinRel9.pres = PRSNT_NODEF;
   lwrNghEutraFreq->qQualMinRel9.val  = wrSmDfltDualMinRel9;
   lwrNghEutraFreq->reselecThreshQRel9.pres = PRSNT_NODEF;
   lwrNghEutraFreq->reselecThreshQRel9.val  =  wrSmDfltReselecThreshQRel9;
   lwrNghEutraFreq->threshXQRel9.threshXHighQR9 =  msmNghEutraFreq->threshXHighQR9;
   lwrNghEutraFreq->threshXQRel9.threshXLowQR9  =  msmNghEutraFreq->threshXLowQR9;

}/*end of wrSmmEnbFillNghEutraFreqParam*/

/*
 *
 *       Fun:   wrSmmEnbFillNghUtraFreqParam
 *
 *       Desc:  This function is used for filling Neighbor 
 *              utra Freq parameter              
 *
 *       Ret:   Void
 *
 *       Notes: None
 *              
 *       File:  wr_smm_enb_utils.c 
 *
 */
#ifdef ANSI 
PUBLIC Void wrSmmEnbFillNghUtraFreqParam
(
 LwrNeighUtraFreq *lwrNghUtraFreq, 
 MsmLteNeighUtraFreq *msmNghUtraFreq, 
 U32 reCfgType
 )
#else
PUBLIC Void wrSmmEnbFillNghUtraFreqParam
(
 lwrNghUtraFreq,msmNghUtraFreq, 
 reCfgType
 )
LwrNeighUtraFreq *lwrNghUtraFreq;
MsmLteNeighUtraFreq *msmNghUtraFreq;
U32 reCfgType;
#endif
{
   TRC2(wrSmmEnbFillNghUtraFreqParam);

   lwrNghUtraFreq->reCfgType = reCfgType; 
   lwrNghUtraFreq->freqIndex = msmNghUtraFreq->freqIndex; 
   lwrNghUtraFreq->status    = wrSmDfltStatus; 
   lwrNghUtraFreq->t.utraFdd.arfcnDl = msmNghUtraFreq->arfcnDl;
   lwrNghUtraFreq->t.utraFdd.arfcnUl = msmNghUtraFreq->arfcnUl;

   lwrNghUtraFreq->priority.pres = PRSNT_NODEF;
   lwrNghUtraFreq->priority.val = msmNghUtraFreq->priority; 
   lwrNghUtraFreq->threshXhigh  = msmNghUtraFreq->threshXhigh; 
   lwrNghUtraFreq->threshXlow   = msmNghUtraFreq->threshXlow; 
   lwrNghUtraFreq->qRxLevMin    = msmNghUtraFreq->qRxLevMin;
   lwrNghUtraFreq->pMaxUtra     = msmNghUtraFreq->pMaxUtra;
   lwrNghUtraFreq->t.utraFdd.pQualMin     = msmNghUtraFreq->pQualMin;  
   lwrNghUtraFreq->offsetFreq   = msmNghUtraFreq->offsetFreq;
   lwrNghUtraFreq->duplexMode	 = MSM_UTRA_DUPLEX_MODE_FDD;
   lwrNghUtraFreq->t.utraFdd.thresR9.pres = PRSNT_NODEF;
   lwrNghUtraFreq->t.utraFdd.thresR9.thresXHighQR9 = msmNghUtraFreq->threshXHighQR9;
   lwrNghUtraFreq->t.utraFdd.thresR9.thresXLowQR9 = msmNghUtraFreq->threshXLowQR9;

}/*end of wrSmmEnbFillNghUtraFreqParam*/


/*
 *
 *       Fun:  wrSmmEnbFillNghEnbParam 
 *
 *       Desc:  This function is used for filling Neighbor 
 *              Eutra cell parameter              
 *
 *       Ret:   Void
 *
 *       Notes: None
 *              
 *       File:  fc_smm_enbapp_cmnplatutils.c 
 *
 */
#ifdef ANSI 
PUBLIC Void wrSmmEnbFillNghEnbParam(SmNeigEnbList *nghEnbCfg, 
      MsmEUTRANeighCell *msmNghEutraCell,
      U8 cellCfgIdx)
#else
PUBLIC Void wrSmmEnbFillNghEnbParam(nghEnbCfg, msmNghEutraCell, cellCfgIdx)
   SmNeigEnbList *nghEnbCfg;
   MsmEUTRANeighCell *msmNghEutraCell;
   U8 cellCfgIdx;
#endif
{
   TRC2(wrSmmEnbFillNghEnbParam);

   nghEnbCfg->numCell++;
   nghEnbCfg->nghEnbCfg.enbType = smGetEnbType(msmNghEutraCell->pci,0); 

   /*ccpu00138869 start*/
   if(nghEnbCfg->nghEnbCfg.enbType == WR_ENODEB_TYPE_MACRO)
   {
      nghEnbCfg->nghEnbCfg.enbId   = ((msmNghEutraCell->cid) >>8); 
   }
   else
   {
      nghEnbCfg->nghEnbCfg.enbId   = msmNghEutraCell->cid; 
   }
   RLOG2(L_DEBUG,"wrSmmEnbFillNghEnbParam:enbType = %lu,enbId = %lu\n",
         nghEnbCfg->nghEnbCfg.enbType,nghEnbCfg->nghEnbCfg.enbId);

   nghEnbCfg->nghEnbCfg.peerId  = wrSmmEnbGetPeerId(nghEnbCfg->nghEnbCfg.enbId); 
   nghEnbCfg->nghEnbCfg.plmn.numMncDigits = 
      msmNghEutraCell->plmnId[0].numMncDigits; 
   nghEnbCfg->nghEnbCfg.plmn.mcc[0] = msmNghEutraCell->plmnId[0].mcc[0]; 
   nghEnbCfg->nghEnbCfg.plmn.mcc[1] = msmNghEutraCell->plmnId[0].mcc[1];
   nghEnbCfg->nghEnbCfg.plmn.mcc[2] = msmNghEutraCell->plmnId[0].mcc[2];
   nghEnbCfg->nghEnbCfg.plmn.mnc[0] = msmNghEutraCell->plmnId[0].mnc[0]; 
   nghEnbCfg->nghEnbCfg.plmn.mnc[1] = msmNghEutraCell->plmnId[0].mnc[1]; 
   if(msmNghEutraCell->plmnId[0].numMncDigits == 3)
   {
      nghEnbCfg->nghEnbCfg.plmn.mnc[2] = msmNghEutraCell->plmnId[0].mnc[2]; 
   }
   else
   {
      nghEnbCfg->nghEnbCfg.plmn.mnc[2] = 0; 
   }
   nghEnbCfg->nghEnbCfg.ipAddr.u.ipv4TptAddr.port       = 0; 
   nghEnbCfg->nghEnbCfg.ipAddr.u.ipv4TptAddr.address    = 0; 
   nghEnbCfg->nghEnbCfg.secIpAddr.u.ipv4TptAddr.port    = 0;
   nghEnbCfg->nghEnbCfg.secIpAddr.u.ipv4TptAddr.address = 0;
   nghEnbCfg->nghEnbCfg.state     = wrSmDfltNeEnbState; 

   nghEnbCfg->nghEnbCfg.isX2Reqd  = 
      wrSmmEnbGetIsX2Enabl(nghEnbCfg->nghEnbCfg.enbId, cellCfgIdx);
   nghEnbCfg->nghEnbCfg.alarmVal.maxErrIndCnt = 
      faultMgmtParams.frequentFaultMgmtParameters.maxX2ErrIndCnt;
   nghEnbCfg->nghEnbCfg.alarmVal.minErrIndTime = 
      faultMgmtParams.frequentFaultMgmtParameters.minX2ErrIndTime;
   nghEnbCfg->nghEnbCfg.alarmVal.maxResetCnt = 
      faultMgmtParams.frequentFaultMgmtParameters.maxX2ResetCnt;
   nghEnbCfg->nghEnbCfg.alarmVal.minResetTime = 
      faultMgmtParams.frequentFaultMgmtParameters.minX2ResetTime;
}/*end of wrSmmEnbFillNghEnbParam*/

/*
 *
 *       Fun:   wrSmmEnbFillNghEutraCellParam
 *
 *       Desc:  This function is used for filling Neighbor 
 *              Eutra cell parameter              
 *
 *       Ret:   Void
 *
 *       Notes: None
 *              
 *       File:  fc_smm_enbapp_cmnplatutils.c 
 *
 */
#ifdef ANSI 
PUBLIC Void wrSmmEnbFillNghEutraCellParam(LwrEUTRANeighCell *lwrNghEutraCell, 
      MsmEUTRANeighCell *msmNghEutraCell,
      U32 reCfgType)
#else
PUBLIC Void wrSmmEnbFillNghEutraCellParam(lwrNghEutraCell,msmNghEutraCell, reCfgType)
   LwrEUTRANeighCell *lwrNghEutraCell;
   MsmEUTRANeighCell *msmNghEutraCell;
   U32                reCfgType;
#endif
{
   TRC2(wrSmmEnbFillNghEutraCellParam);
   lwrNghEutraCell->reCfgType = reCfgType;
   lwrNghEutraCell->nrIndex = msmNghEutraCell->nrIndex; 
   lwrNghEutraCell->enbType = smGetEnbType(msmNghEutraCell->pci,0);
   /*Do not do right shift by 8 for MACRO as it is done in EMM module*/
   lwrNghEutraCell->enbId   = msmNghEutraCell->cid; 
   /*Do not do right shift by 8 for MACRO as it is done in EMM module*/
   RLOG3(L_DEBUG,"wrSmmEnbFillNghEutraCellParam: enbType = %lu,cid = %lu, enbid = %lu\n",
         lwrNghEutraCell->enbType,msmNghEutraCell->cid, lwrNghEutraCell->enbId);

   lwrNghEutraCell->cio     = msmNghEutraCell->cio;
   lwrNghEutraCell->enbPlmn.numMncDigits = 
      msmNghEutraCell->plmnId[0].numMncDigits;
   lwrNghEutraCell->plmnId[0].numMncDigits = 
      msmNghEutraCell->plmnId[0].numMncDigits;
   lwrNghEutraCell->enbPlmn.mcc[0] = msmNghEutraCell->plmnId[0].mcc[0];
   lwrNghEutraCell->enbPlmn.mcc[1] = msmNghEutraCell->plmnId[0].mcc[1];
   lwrNghEutraCell->enbPlmn.mcc[2] = msmNghEutraCell->plmnId[0].mcc[2];

   lwrNghEutraCell->enbPlmn.mnc[0] = msmNghEutraCell->plmnId[0].mnc[0];
   lwrNghEutraCell->enbPlmn.mnc[1] = msmNghEutraCell->plmnId[0].mnc[1];
   lwrNghEutraCell->enbPlmn.mnc[2] = msmNghEutraCell->plmnId[0].mnc[2];
   lwrNghEutraCell->plmnId[0].mcc[0] = msmNghEutraCell->plmnId[0].mcc[0];
   lwrNghEutraCell->plmnId[0].mcc[1] = msmNghEutraCell->plmnId[0].mcc[1];
   lwrNghEutraCell->plmnId[0].mcc[2] = msmNghEutraCell->plmnId[0].mcc[2];

   lwrNghEutraCell->plmnId[0].mnc[0] = msmNghEutraCell->plmnId[0].mnc[0];
   lwrNghEutraCell->plmnId[0].mnc[1] = msmNghEutraCell->plmnId[0].mnc[1];
   lwrNghEutraCell->plmnId[0].mnc[2] = msmNghEutraCell->plmnId[0].mnc[2];

   lwrNghEutraCell->numPlmn = 1;
   lwrNghEutraCell->pci     = msmNghEutraCell->pci;
   lwrNghEutraCell->qoffset = msmNghEutraCell->qoffset;
   lwrNghEutraCell->dlBw    = msmNghEutraCell->dlBw; /*msmNghEutraCell->dlBw; wrSmDfltCellDlBW;*/
   /*ccpu00136251-Mod-TAC should be from OAM not from SIB1*/
   lwrNghEutraCell->tac     = msmNghEutraCell->tac;
   lwrNghEutraCell->ulBw    = msmNghEutraCell->ulBw; /*msmNghEutraCell->ulBw; wrSmDfltCellUlBW;*/
   lwrNghEutraCell->earfcnDl= msmNghEutraCell->earfcnDl;
   lwrNghEutraCell->earfcnUl= msmNghEutraCell->earfcnUl;
   lwrNghEutraCell->blackListed = msmNghEutraCell->BlackListed;
   lwrNghEutraCell->refSigPower = msmNghEutraCell->RSTxPower;
   /* CNM_DEV start */
   lwrNghEutraCell->numAntenna = msmNghEutraCell->numAntenna;
   lwrNghEutraCell->ulDlSubFrameCfg = msmNghEutraCell->ulDlSubFrameCfg;
   lwrNghEutraCell->splSfCfg = msmNghEutraCell->splSfCfg;
   lwrNghEutraCell->cpDl = msmNghEutraCell->cpDl;
   lwrNghEutraCell->cpUl = msmNghEutraCell->cpUl;
   lwrNghEutraCell->rsrp = msmNghEutraCell->rsrp;
   lwrNghEutraCell->rssi = msmNghEutraCell->rssi;
   /* CNM_DEV end */
   /* CSG_DEV start */
   lwrNghEutraCell->isCsgIdResolved = WR_EMM_NBR_CSG_ID_DISCOVERED;
   lwrNghEutraCell->isCsgAccessModeResolved = WR_EMM_CELL_ACCESS_MODE_DETERMINED;
   lwrNghEutraCell->csgAccessMode = msmNghEutraCell->csgAccessMode;
   lwrNghEutraCell->csgId = msmNghEutraCell->csgId;
   /* CSG_DEV end */
   lwrNghEutraCell->numAntenna = msmNghEutraCell->numAntenna;
   lwrNghEutraCell->ulDlSubFrameCfg = msmNghEutraCell->ulDlSubFrameCfg;
   lwrNghEutraCell->splSfCfg = msmNghEutraCell->splSfCfg;
   lwrNghEutraCell->cpDl = msmNghEutraCell->cpDl;
   lwrNghEutraCell->cpUl = msmNghEutraCell->cpUl;
   lwrNghEutraCell->rsrp = msmNghEutraCell->rsrp;
   lwrNghEutraCell->rssi = msmNghEutraCell->rssi;
   lwrNghEutraCell->isHeMsCell = msmNghEutraCell->isHeMsCell;
}/*end of wrSmmEnbFillNghEutraCellParam*/

/*
 *
 *       Fun:   wrSmmEnbFillNghUtraCellParam
 *
 *       Desc:  This function is used for filling Neighbor 
 *              utra cell parameter              
 *
 *       Ret:   Void
 *
 *       Notes: None
 *              
 *       File:  fc_smm_enbapp_cmnplatutils.c 
 *
 */
#ifdef ANSI 
PUBLIC Void wrSmmEnbFillNghUtraCellParam(LwrUtraNeighCell *lwrNghUtraCell, 
      MsmUtraNeighCell *msmNghUtraCell,
      U32 reCfgType)
#else
PUBLIC Void wrSmmEnbFillNghUtraCellParam
(
 lwrNghEutraCell,
 msmNghUtraCell, 
 reCfgType
 )
LwrUtraNeighCell *lwrNghUtraCell;
MsmUtraNeighCell *msmNghUtraCell;
U32 reCfgType;
#endif
{
   U32 plmnIdx = 0;
   TRC2(wrSmmEnbFillNghUtraCellParam);

   lwrNghUtraCell->reCfgType = reCfgType;
   lwrNghUtraCell->nrIndex = msmNghUtraCell->nrIndex;
   lwrNghUtraCell->rncId   = msmNghUtraCell->rncId;
   lwrNghUtraCell->cId     = msmNghUtraCell->cId;

   lwrNghUtraCell->numPlmn = msmNghUtraCell->numPlmn;
   for(plmnIdx = 0; plmnIdx < lwrNghUtraCell->numPlmn; plmnIdx++)
   {
      lwrNghUtraCell->plmnId[plmnIdx].mcc[0] = msmNghUtraCell->plmnId[plmnIdx].mcc[0];
      lwrNghUtraCell->plmnId[plmnIdx].mcc[1] = msmNghUtraCell->plmnId[plmnIdx].mcc[1];
      lwrNghUtraCell->plmnId[plmnIdx].mcc[2] = msmNghUtraCell->plmnId[plmnIdx].mcc[2];

      lwrNghUtraCell->plmnId[plmnIdx].numMncDigits = 
         msmNghUtraCell->plmnId[plmnIdx].numMncDigits;

      lwrNghUtraCell->plmnId[plmnIdx].mnc[0] = msmNghUtraCell->plmnId[plmnIdx].mnc[0];
      lwrNghUtraCell->plmnId[plmnIdx].mnc[1] = msmNghUtraCell->plmnId[plmnIdx].mnc[1];

      if(3 == lwrNghUtraCell->plmnId[plmnIdx].numMncDigits)
         lwrNghUtraCell->plmnId[plmnIdx].mnc[2] = msmNghUtraCell->plmnId[plmnIdx].mnc[2];
   } 
   lwrNghUtraCell->t.utraFdd.psc = msmNghUtraCell->psc;
   lwrNghUtraCell->lac = msmNghUtraCell->lac;
   lwrNghUtraCell->rac = msmNghUtraCell->rac;

   lwrNghUtraCell->duplexMode = MSM_UTRA_DUPLEX_MODE_FDD;

   lwrNghUtraCell->t.utraFdd.arfcnDl = msmNghUtraCell->arfcnDl;
   lwrNghUtraCell->t.utraFdd.arfcnUl = msmNghUtraCell->arfcnUl;
   lwrNghUtraCell->isRimSupported = msmNghUtraCell->isRimSupported;

}/*end of wrSmmEnbFillNghUtraCellParam*/

/*
 *
 *       Fun:  wrSmmEnbValidateFillMmeIp 
 *
 *       Desc:  validate for duplicacy and fill mme Ip
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_smm_enb_utils.c 
 *
 */

PUBLIC S16 wrSmmEnbValidateFillMmeIp
(
 LwrSmMmeCfg *mmeCfg,
 U8          *idx,
 Mmeiptype   ip
 )
{
   U8 idx1 = 0;
   U8 ret = ROK;
   U8 idx2 = *idx;
   U8 emtpyIpv6Addr[WR_IPV6_ADDR_LEN] = {0};

   for(idx1 = 0; idx1 < idx2; idx1++)
   {
      if((0 == ip.mmeipv4) && 
            (ROK == cmMemcmp((U8*)&ip.mmeipv6, (U8*)&emtpyIpv6Addr,
                             sizeof(CmInetIpAddr6))))
      {
         ret = RFAILED;
         RLOG0(L_INFO, "Secondary MME IP is 0");
         break;
      }
      else  
      {
         /* Check if IPv4 address is same as received */
         if((mmeCfg->mmeAddr[idx1].type == CM_TPTADDR_IPV4) && (ip.ipv4pres == TRUE) 
               && (mmeCfg->mmeAddr[idx1].u.ipv4TptAddr.address == ip.mmeipv4))
         {
            ret = ROKDNA;
            RLOG0(L_ERROR, "MME IPv4 is duplicate");
            break;
         }
         /* Check if IPv6 address is same as received */
         else if((mmeCfg->mmeAddr[idx1].type == CM_TPTADDR_IPV6) && (ip.ipv6pres == TRUE) 
               && ( ROK == cmMemcmp((U8*)&mmeCfg->mmeAddr[idx1].u.ipv6TptAddr.ipv6NetAddr, 
                     (U8*)&ip.mmeipv6,sizeof(CmInetIpAddr6))))
         {
            ret = ROKDNA;
            RLOG0(L_ERROR, "MME IPv6 is duplicate");
            break;
         }
      }
   }
   if(ROK == ret)
   {
      if(ip.ipv4pres == TRUE)
      {
         mmeCfg->mmeAddr[*idx].type = CM_TPTADDR_IPV4;
         mmeCfg->mmeAddr[*idx].u.ipv4TptAddr.address = ip.mmeipv4;
      }
      if(ip.ipv6pres == TRUE)
      {
         mmeCfg->mmeAddr[*idx].type = CM_TPTADDR_IPV6;
         cmMemcpy((U8*)&mmeCfg->mmeAddr[*idx].u.ipv6TptAddr.ipv6NetAddr,
               (U8*)&ip.mmeipv6,sizeof(CmInetIpAddr6));
      }
      *idx = *idx + 1;
   }

   RETVALUE(ret);
} /* end of wrSmmEnbValidateFillMmeIp */

/*
 *
 *       Fun:  wrSmmEnbGetPeerId 
 *
 *       Desc:  This function is used get peerId from free list 
 *                          
 *
 *       Ret:   U8 peerId
 *
 *       Notes: None
 *              
 *       File:  fc_smm_enbapp_cmnplatutils.c 
 *
 */
PUBLIC U8 wrSmmEnbGetPeerId(U32 enbId)
{
   U8 peerId = 0;

   WR_GET_X2AP_PEER_ID(peerId, enbId);  
   RETVALUE(peerId);
}/*end of wrSmmEnbGetPeerId*/

/*
 *
 *       Fun:  smReturnPeerIdToFreeList
 *
 *       Desc:  This function is to return peerId back to free list
 *               once neighbor deleted 
 *                          
 *
 *       Ret:   Void 
 *
 *       Notes: None
 *              
 *       File:  fc_smm_enbapp_cmnplatutils.c 
 *
 */
#ifdef ANSI 
PUBLIC Void smReturnPeerIdToFreeList(U8 peerId)
#else
PUBLIC Void smReturnPeerIdToFreeList(U8 peerId)
#endif
{
   WR_CLEAR_X2AP_PEER_ID(peerId);

   RETVOID;
}/*end of smReturnPeerIdToFreeList*/


/*
 *
 *       Fun:   wrSmmEnbFillNghCdma1xFreqParam
 *
 *       Desc:  This function is used for filling Neighbor 
 *              cdma 1xrtt freq parameter              
 *
 *       Ret:   Void
 *
 *       Notes: None
 *              
 *       File:  fc_smm_enbapp_cmnplatutils.c 
 *
 */
#ifdef ANSI 
PUBLIC Void wrSmmEnbFillNghCdma1xFreqParam(LwrNeighCdma1xFreq *lwrNghCdma1xFreq, 
      LwrCDMA1xNeighCell *nghCdma1xCell,
      U32 reCfgType, U8 idx, U8 cellCfgIdx)
#else
PUBLIC Void wrSmmEnbFillNghCdma1xFreqParam
(
 lwrNghCdma1xFreq, 
 nghCdma1xCell, 
 reCfgType, 
 idx,
 cellCfgIdx
 )
LwrNeighCdma1xFreq *lwrNghCdma1xFreq;
LwrCDMA1xNeighCell *nghCdma1xCell;
U32 reCfgType;
U8 idx;
U8 cellCfgIdx;
#endif
{
   TRC2(wrSmmEnbFillNghCdma1xFreqParam);

   lwrNghCdma1xFreq->reCfgType    = reCfgType;
   lwrNghCdma1xFreq->freqIndex    = idx + 1;
   lwrNghCdma1xFreq->status       = wrSmDfltStatus;
   lwrNghCdma1xFreq->bandClass    = nghCdma1xCell->bandClass;
   lwrNghCdma1xFreq->arfcn        = nghCdma1xCell->arfcn;
   lwrNghCdma1xFreq->searchRate   = lteeNodeBparams[cellCfgIdx].csfbCfgGrp.searchRate;
   lwrNghCdma1xFreq->offsetFreq   = wrSmDfltCdma1xOffsetFreq;
   lwrNghCdma1xFreq->freqPriority = 1;

}/*end of wrSmmEnbFillNghCdma1xFreqParam*/

/*
 *
 *       Fun: wrSmmEnbGetIsX2Enabl 
 *
 *       Desc:  This function is used  x2enable  flag
 *                          
 *
 *       Ret:   U8 
 *
 *       Notes: None
 *              
 *       File:  fc_smm_enbapp_cmnplatutils.c 
 *
 */
#ifdef ANSI 
PUBLIC U8 wrSmmEnbGetIsX2Enabl(U32 enbId,U8 cellCfgIdx)
#else
PUBLIC U8 wrSmmEnbGetIsX2Enabl(U32 enbId, U8 cellCfgIdx)
#endif
{
   RETVALUE(lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.isX2Enabled);
}/*end of wrSmmEnbGetIsX2Enabl*/


/*
 *
 *       Fun:  wrSmConfigComplete 
 *
 *       Desc:  This function is to 
 *
 *       Ret:   None
 *
 *       Notes: <NONE>
 *
 *       File:  wr_enb_cmnplt_enbapp.c
 *
 */
PUBLIC Void wrSmConfigComplete()
{

   TRC2(wrMsmConfigComplete);

   MsmConfigComplete();
   SmUpdateSwVersion(wrGetSwVersion());

   smCb.smState = WR_SM_STATE_OAM_DYN_START;
   RETVOID;
}

/*
 *
 *       Fun:   MsmEnodeBinitialCfgComplete
 *
 *       Desc:  This function is to conform MIB is populated we can start cfg start layere
 *
 *       Ret:   None
 *
 *       Notes: <NONE>
 *
 *       File:  wr_smm_enbapp_cmnplatutils.c
 *
 **/

PUBLIC S16 MsmEnodeBinitialCfgComplete(Void)
{
   Pst    smPst;
   Buffer *mBuf;          /* message buffer */

   TRC2(MsmEnodeBinitialCfgComplete);

   SM_SET_ZERO(&smPst, sizeof(Pst));

   smPst.dstProcId = SM_SM_PROC;
   smPst.srcProcId = SM_SM_PROC;
   smPst.dstEnt = ENTSM;
   smPst.srcEnt = ENTWR;
   smPst.dstInst = 0;
   smPst.srcInst = 0;
   smPst.event  = EVTSMSTATICCFG;
   smPst.pool   = WR_POOL;
   smPst.selector= SM_SELECTOR_LC;


   if(SGetMsg(DFLT_REGION, WR_POOL, &mBuf) != ROK)
   {

      RETVALUE(RFAILED);
   } /* end of if statement */

   SPstTsk(&smPst, mBuf); 
   RETVALUE(ROK);
}/* end of MsmEnodeBinitialCfgComplete */

/*
 *
 *       Fun:   smBuildCdmaHrpdaBandClass
 *
 *       Desc:  This function for filling the Cell Band Class Configuration
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildCdmaHrpdaBandClass
(
 LwrMngmt *lwrMng
 )
#else /* if ANSI not defined*/
PUBLIC S16 smBuildCdmaHrpdaBandClass(*lwrMng)
   LwrMngmt *lwrMng
#endif /* end of ANSI*/
{
   RETVALUE(ROK);
} /* end of smBuildCdmaHrpdaBandClass */
#endif /*WR_RSYS_OAM*/ 

/*
 *
 *       Fun:   wrSmmEnbBldCellEaidCfg
 *
 *       Desc:  fill in EAID cfg for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_smm_enb_utils.c 
 *
 */

PUBLIC void wrSmmEnbBldCellEaidCfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex
 )
{
   LwrCellEAIDCfgGrp         *eaidCfgGrp = NULLP;
   U8                        idx = 0;
   U32                       tempEaid = 0x112233;

   TRC2(wrSmmEnbBldCellEaidCfg);

   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_EAID;

   eaidCfgGrp = &(lwrMng->t.protoCfg.t.cellCfg.t.\
         addCell.cellCfgGrp[cfgGrpIndex].t.eaidCfgGrp);

   for (idx = 0; idx < LWR_SM_MAX_EAIDS; idx++)
   {
      eaidCfgGrp->eaid[idx].pres = TRUE;
      //eaidCfgGrp->eaid[idx].val = lteeNodeBparams[cellCfgIdx].lteCellEAIDCfgGrp.eaid[idx];
      eaidCfgGrp->eaid[idx].val = tempEaid++;
      /* eaidCfgGrp->eaid[idx].val = tempEaid++; */
   }
   RETVOID;
} /* end of wrSmmEnbBldCellEaidCfG */

/*
 *
 *       Fun:   wrSmmEnbBuildWrMmeCfg
 *
 *       Desc:  fill in neighbour Cfg for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
#ifdef ANSI
PUBLIC S16 wrSmmEnbBuildWrMmeCfg
(
 LwrMngmt *lwrMng,
 LwrSmMmeCfg *mmeSmCfg
 )
#else /* if ANSI not defined*/
PUBLIC S16 wrSmmEnbBuildWrMmeCfg(*lwrMng,*mmeCfg)
   LwrMngmt *lwrMng;
   LwrSmMmeCfg *mmeSmCfg;
#endif /* end of ANSI*/
{
   LwrAddModMmeCfg *mmeCfg =NULLP;
   U8              idx = 0;

   TRC2(wrSmmEnbBuildWrMmeCfg);

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_MME;
   lwrMng->t.protoCfg.t.mmeCfg.action = WR_ACT_ADD;

   mmeCfg =&(lwrMng->t.protoCfg.t.mmeCfg.t.addMme);

   mmeCfg->mmeIndex = (U8)(mmeSmCfg->mmeId);

   /*Filling IP Address*/
   mmeCfg->noOfIps = mmeSmCfg->noOfIps;
   for(idx = 0; idx < mmeSmCfg->noOfIps; idx++)
   {
      wrCpyCmTptAddr(&mmeCfg->ipAddr[idx], &mmeSmCfg->mmeAddr[idx]);
      if(CM_TPTADDR_IPV4 ==  mmeCfg->ipAddr[idx].type)
      {
         mmeCfg->ipAddr[idx].u.ipv4TptAddr.port = wrSmDfltMmePort;
      }
      else if(CM_TPTADDR_IPV6 ==  mmeCfg->ipAddr[idx].type)
      {
         mmeCfg->ipAddr[idx].u.ipv6TptAddr.port = wrSmDfltMmePort;
      }
   }

   /*Filling MME state*/
   mmeCfg->mmeState =wrSmDfltMmeState;
   mmeCfg->adminState =wrSmDfltMmeAdminState;

   mmeCfg->alarmVal.maxErrIndCnt = 
      faultMgmtParams.frequentFaultMgmtParameters.maxS1ErrIndCnt;
   mmeCfg->alarmVal.maxResetCnt = 
      faultMgmtParams.frequentFaultMgmtParameters.maxS1ResetCnt;
   mmeCfg->alarmVal.minErrIndTime = 
      faultMgmtParams.frequentFaultMgmtParameters.minS1ErrIndTime;
   mmeCfg->alarmVal.minResetTime = 
      faultMgmtParams.frequentFaultMgmtParameters.minS1ResetTime;
   RETVALUE(ROK);
} /* end of wrSmmEnbBuildWrMmeCfg */

/*
 *
 *       Fun:   wrSmmEnbBldCellSibSchCfg
 *
 *       Desc:  fill in sib scheduling cfg for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_smm_enb_utils.c 
 *
 */

PUBLIC void wrSmmEnbBldCellSibSchCfg
(
 LwrMngmt   *lwrMng,
 U8         cfgGrpIndex,
 U8         cellCfgIdx
 )
{
   LwrCellSibSchedCfgGrp *sibSchCfg = NULLP;

   TRC2(wrSmmEnbBldCellSibSchCfg);


   lwrMng->t.protoCfg.t.cellCfg.t.addCell.cellCfgGrp[cfgGrpIndex].grpType =
      WR_CELL_CFG_GRP_SIB_SCHED;

   sibSchCfg = &(lwrMng->t.protoCfg.t.cellCfg.t.addCell.\
         cellCfgGrp[cfgGrpIndex].t.sibSchedCfgGrp);
   /* Populate the SIB periodicites */
   sibSchCfg->sib2Period = WR_SIB2_PERIOD; 
   sibSchCfg->sib3Period = WR_SIB3_PERIOD;
   sibSchCfg->sib4Period = WR_SIB4_PERIOD; 
   /* If the number of Frequency entries is >1(the first entry is alwys Intra frequency), 
   */
   sibSchCfg->sib5Period = WR_SIB5_PERIOD; 

   if ((lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numUtraFreq > 0) || \
         (lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numUtraTddFreq > 0)) 
      // if ((lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numUtraFreq > 0) || (smCfgCb.noOfUtraTddFreq[cellCfgIdx] > 0))
   {
      sibSchCfg->sib6PeriodValid = TRUE;   
      sibSchCfg->sib6Period = WR_SIB6_PERIOD; 
   }
   else
   {
      sibSchCfg->sib6PeriodValid = FALSE;
   }
   /* Fix for CR ccpu00142792 */
   if(lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numGeranFreq > 0)
      // if (smCfgCb.noOfGeranFreq[cellCfgIdx] > 0)
   {
      sibSchCfg->sib7PeriodValid = TRUE;
      sibSchCfg->sib7Period = WR_SIB7_PERIOD;
   }
   else
   {
      sibSchCfg->sib7PeriodValid = FALSE;
   }
#if 0 /* sri: temp block for TIP. SIB9 broadcast not proper */
   sibSchCfg->sib9Period = WR_SIB9_PERIOD; 
#endif
   if(lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.numCdma1xCells > 0)
      //   if (smCfgCb.noOfNeighCdma1xCells[cellCfgIdx] > 0)
   {
      sibSchCfg->sib8PeriodValid = TRUE;
      sibSchCfg->sib8Period = WR_SIB8_PERIOD;
   }
   else
   {
      sibSchCfg->sib8PeriodValid = FALSE;
   }
   sibSchCfg->siWindow = wrSmDfltSiWinSize;
   sibSchCfg->sib10ManualPrdPres = TRUE;
   sibSchCfg->sib10RepetPeriod = wrSmDfltSib10RptPrd;
   sibSchCfg->sib10NumBroadCast = wrSmDfltSib10NumBroadCast;
   sibSchCfg->sib11WarnSegSize = wrSmDfltWarnSegSize;
   RETVOID;
} /* end of wrSmmEnbBldCellSibSchCfg */

/*
 *
 *       Fun:    wrSmmEnbBuildWrNrEutraFreqCfg - Build Neighbour frequency
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp.c
 *
 */
PUBLIC S16 wrSmmEnbBuildWrNrEutraFreqCfg
(
 LwrMngmt *lwrMng,
 U8        cellCfgIdx
 )
{
   U32 idx = 0;
   LwrNeighFreqAddModCfg *nrFreqCfg =NULLP;
   MsmLteNeighEutraFreq *msmNghEutraFreq = NULLP;

   TRC2(wrSmmEnbBuildWrNrEutraFreqCfg);

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = (cellCfgIdx + 1); /* this is ownCellID in case of PLD based, jst a logic entity */
   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = lteeNodeBparams[cellCfgIdx]. \
                                               lteNeighFreqCfg.numEutraFreq;  

   nrFreqCfg = (lwrMng->t.protoCfg.t.neighFreqCfg.t.addNeighFreq);
   nrFreqCfg->type = WR_NEIGH_CELL_EUTRA;

   for(idx=0; idx < lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numEutraFreq; idx++)
   {
      msmNghEutraFreq = &lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t. \
                        addNeighFreq[idx].eutranFreq;
      nrFreqCfg->t.eutranFreq.reCfgType = wrSmDfltReCfgType;
      nrFreqCfg->t.eutranFreq.status = wrSmDfltStatus;
      nrFreqCfg->t.eutranFreq.earfcnUl = msmNghEutraFreq->earfcnUl;
      nrFreqCfg->t.eutranFreq.earfcnDl = msmNghEutraFreq->earfcnDl;

      nrFreqCfg->t.eutranFreq.priority = msmNghEutraFreq->priority;
      nrFreqCfg->t.eutranFreq.qRxLevMin = msmNghEutraFreq->qRxLevMin;
      nrFreqCfg->t.eutranFreq.pMaxUsage = wrSmDfltPMaxUsage;
      nrFreqCfg->t.eutranFreq.pMax =  msmNghEutraFreq->pMax;
      nrFreqCfg->t.eutranFreq.tReselection = msmNghEutraFreq->tReselection;
      nrFreqCfg->t.eutranFreq.sfUsage = wrSmDfltSfUsage;
      nrFreqCfg->t.eutranFreq.tReselectionSFMed = msmNghEutraFreq->tReselectionSFMed;
      nrFreqCfg->t.eutranFreq.tReselectionSFHigh = msmNghEutraFreq->tReselectionSFHigh;
      nrFreqCfg->t.eutranFreq.sIntraSearch.pres = PRSNT_NODEF;
      nrFreqCfg->t.eutranFreq.sIntraSearch.val =  msmNghEutraFreq->sIntraSearch;
      nrFreqCfg->t.eutranFreq.sNonIntraSearch.pres = PRSNT_NODEF;
      nrFreqCfg->t.eutranFreq.sNonIntraSearch.val = msmNghEutraFreq->sNonIntraSearch;
      nrFreqCfg->t.eutranFreq.servThresholdLow = msmNghEutraFreq->servThresholdLow;
      nrFreqCfg->t.eutranFreq.threshXHigh = msmNghEutraFreq->threshXHigh;
      nrFreqCfg->t.eutranFreq.threshXLow =  msmNghEutraFreq->threshXLow;
      nrFreqCfg->t.eutranFreq.measBandwidth.pres =  PRSNT_NODEF;
      nrFreqCfg->t.eutranFreq.measBandwidth.val =  msmNghEutraFreq->measBandwidth;
      nrFreqCfg->t.eutranFreq.presAntennaPort1 =  msmNghEutraFreq->presAntennaPort1;
      nrFreqCfg->t.eutranFreq.neighCellCfg =  msmNghEutraFreq->neighCellCfg;
      nrFreqCfg->t.eutranFreq.qOffsetFreq = msmNghEutraFreq->qOffsetFreq;
      nrFreqCfg->t.eutranFreq.offsetFreq =  msmNghEutraFreq->offsetFreq;
      nrFreqCfg->t.eutranFreq.sIntraSearchRel9.pres =  PRSNT_NODEF;
      nrFreqCfg->t.eutranFreq.sIntraSearchRel9.sSearchPRel9 =
         wrSmDfltsSearchPRel9;
      nrFreqCfg->t.eutranFreq.sIntraSearchRel9.sSearchQRel9 =
         wrSmDfltsSearchQRel9;
      nrFreqCfg->t.eutranFreq.sInterSearchRel9.pres = PRSNT_NODEF;
      nrFreqCfg->t.eutranFreq.sInterSearchRel9.sSearchPRel9 =
         wrSmDfltsSearchPRel9;
      nrFreqCfg->t.eutranFreq.sInterSearchRel9.sSearchQRel9 =
         wrSmDfltsSearchQRel9;
      nrFreqCfg->t.eutranFreq.qQualMinRel9.pres = PRSNT_NODEF;
      nrFreqCfg->t.eutranFreq.qQualMinRel9.val = wrSmDfltDualMinRel9;
      nrFreqCfg->t.eutranFreq.reselecThreshQRel9.pres = PRSNT_NODEF;
      nrFreqCfg->t.eutranFreq.reselecThreshQRel9.val =
         wrSmDfltReselecThreshQRel9;
      nrFreqCfg->t.eutranFreq.threshXQRel9.threshXHighQR9 =
         msmNghEutraFreq->threshXHighQR9;
      nrFreqCfg->t.eutranFreq.threshXQRel9.threshXLowQR9 =
         msmNghEutraFreq->threshXLowQR9;

      nrFreqCfg++;
   }
   RETVALUE(ROK);
} /* end of wrSmmEnbBuildWrNrEutraFreqCfg */
/*
 *
 *       Fun:    wrSmmEnbBuildWrNrUtraFddFreqCfg - Build Neighbour frequency
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp.c
 *
 */
PUBLIC S16 wrSmmEnbBuildWrNrUtraFddFreqCfg
(
 LwrMngmt   *lwrMng,
 U8         cellCfgIdx
 )
{
   U8  idx = 0;
   LwrNeighFreqAddModCfg *nrFreqCfg =NULLP;
   MsmLteNeighUtraFreq *msmNghUtraFreq = NULLP;

   TRC2(wrSmmEnbBuildWrNrUtraFddFreqCfg);
   for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numUtraFreq; idx++)
   {  
      msmNghUtraFreq = &lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t.\
                       addNeighFreq[idx].utranFreq; 
      nrFreqCfg = &lwrMng->t.protoCfg.t.neighFreqCfg.t.addNeighFreq[idx];
      nrFreqCfg->type = WR_NEIGH_CELL_UTRA_FDD;
      nrFreqCfg->t.utranFreq.reCfgType = 0x000fff;
      nrFreqCfg->t.utranFreq.freqIndex = msmNghUtraFreq->freqIndex;
      nrFreqCfg->t.utranFreq.t.utraFdd.arfcnUl = msmNghUtraFreq->arfcnUl;
      nrFreqCfg->t.utranFreq.t.utraFdd.arfcnDl =  msmNghUtraFreq->arfcnDl;

      nrFreqCfg->t.utranFreq.priority.pres = PRSNT_NODEF;
      nrFreqCfg->t.utranFreq.priority.val = msmNghUtraFreq->priority;
      nrFreqCfg->t.utranFreq.threshXhigh = msmNghUtraFreq->threshXhigh;
      nrFreqCfg->t.utranFreq.threshXlow = msmNghUtraFreq->threshXlow;
      nrFreqCfg->t.utranFreq.qRxLevMin = msmNghUtraFreq->qRxLevMin;
      nrFreqCfg->t.utranFreq.pMaxUtra = msmNghUtraFreq->pMaxUtra;
      nrFreqCfg->t.utranFreq.t.utraFdd.pQualMin = msmNghUtraFreq->pQualMin;
      nrFreqCfg->t.utranFreq.offsetFreq = msmNghUtraFreq->offsetFreq;
      nrFreqCfg->t.utranFreq.duplexMode = MSM_UTRA_DUPLEX_MODE_FDD;
      nrFreqCfg->t.utranFreq.t.utraFdd.thresR9.pres = PRSNT_NODEF;
      nrFreqCfg->t.utranFreq.t.utraFdd.thresR9.thresXHighQR9 =
         msmNghUtraFreq->threshXHighQR9;
      nrFreqCfg->t.utranFreq.t.utraFdd.thresR9.thresXLowQR9 =
         msmNghUtraFreq->threshXLowQR9;
   }
   RETVALUE(ROK);
} /* end of wrSmmEnbBuildWrNrUtraFddFreqCfg */

/*
 *
 *       Fun:    wrSmmEnbBuildWrNrUtraTddFreqCfg - Build Neighbour frequency
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp.c
 *
 */
PUBLIC S16 wrSmmEnbBuildWrNrUtraTddFreqCfg
(
 LwrMngmt   *lwrMng,
 U8         cellCfgIdx
 )
{
   U8  idx = 0;
   LwrNeighFreqAddModCfg *nrFreqCfg =NULLP;
   MsmLteNeighUtraTddFreq *msmNghUtraFreq = NULLP; 

   TRC2(wrSmmEnbBuildWrNrUtraTddFreqCfg);

   for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numUtraTddFreq; idx++)
   {  
      msmNghUtraFreq = &lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t.addNeighFreq[idx].utranTddFreq;
      nrFreqCfg = &lwrMng->t.protoCfg.t.neighFreqCfg.t.addNeighFreq[idx];
      nrFreqCfg->type = WR_NEIGH_CELL_UTRA_TDD;
      nrFreqCfg->t.utranFreq.reCfgType = 0x000fff;
      nrFreqCfg->t.utranFreq.freqIndex = msmNghUtraFreq->freqIndex;
      nrFreqCfg->t.utranFreq.t.utraTdd.arfcn = msmNghUtraFreq->arfcn;
      nrFreqCfg->t.utranFreq.t.utraTdd.tddMode = msmNghUtraFreq->tddMode;
      nrFreqCfg->t.utranFreq.t.utraTdd.bandIndicator = msmNghUtraFreq->bandIndicator;

      nrFreqCfg->t.utranFreq.priority.pres = PRSNT_NODEF;
      nrFreqCfg->t.utranFreq.priority.val = msmNghUtraFreq->priority;
      nrFreqCfg->t.utranFreq.threshXhigh = msmNghUtraFreq->threshXhigh;
      nrFreqCfg->t.utranFreq.threshXlow = msmNghUtraFreq->threshXlow;
      nrFreqCfg->t.utranFreq.qRxLevMin = msmNghUtraFreq->qRxLevMin;
      nrFreqCfg->t.utranFreq.pMaxUtra = msmNghUtraFreq->pMaxUtra;
      nrFreqCfg->t.utranFreq.offsetFreq = msmNghUtraFreq->offsetFreq;
      nrFreqCfg->t.utranFreq.duplexMode = MSM_UTRA_DUPLEX_MODE_TDD;
   }
   RETVALUE(ROK);
} /* end of wrSmmEnbBuildWrNrUtraTddFreqCfg */
/*
 *
 *       Fun:   wrSmmEnbBuildWrNghCfg
 *
 *       Desc:  fill in neighbour Cfg for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
#ifdef ANSI
PUBLIC S16 wrSmmEnbBuildWrNghCfg
(
 LwrMngmt *lwrMng,
 U8        cellCfgIdx
 )
#else /* if ANSI not defined*/
PUBLIC S16 wrSmmEnbBuildWrNghCfg(*lwrMng, cellCfgIdx)
   LwrMngmt *lwrMng;
   U8        cellCfgIdx;
#endif /* end of ANSI*/
{
   LwrNeighAddModCfg *neighCfg = NULLP;
   U32 idx = 0;
   U32 enbId = 0;
   U32 indx2 = 0;
   MsmEUTRANeighCell *msmNghEutraCell = NULLP;
   MsmEUTRANeighCell *msmNghEutraCell2 = NULLP;

   TRC2(wrSmmEnbBuildWrNghCfg);


   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH;
   lwrMng->t.protoCfg.t.neighCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighCfg.cellId = cellCfgIdx + 1; /* this ownCellID in case of PLD based, jst a logic entity */
   lwrMng->t.protoCfg.t.neighCfg.numEnb = lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.numEutraCells;

   neighCfg = (lwrMng->t.protoCfg.t.neighCfg.t.neighAdd);
   for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.numEutraCells; idx++)
   {
      msmNghEutraCell = &lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.t. \
                        neighAddCfg[idx].eutraCell;
      enbId = msmNghEutraCell->cid;
      for(indx2 = 0; indx2 < idx; indx2++)
      {
         msmNghEutraCell2 = &lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.t. \
                            neighAddCfg[indx2].eutraCell;
         /* checking if the eNB is already add to configuration */
         /* if yes, ignoring the duplicate configuration and proceeding */
         /* this may occur when multiple cells or same eNB is configured */
         if(enbId == msmNghEutraCell2->cid)
         {
            continue;
         }
      }
      neighCfg->enbType = smGetEnbType(msmNghEutraCell->pci, cellCfgIdx); 
      if(neighCfg->enbType == 0)
      {
         neighCfg->enbId = (enbId >> 8);
      }
      else
      {
         neighCfg->enbId = enbId;
      }

      neighCfg->enbIndx = wrSmDfltNeighEnbIndex[idx];
      neighCfg->peerId = msmNghEutraCell->peerId; 

      neighCfg->plmn.numMncDigits = msmNghEutraCell->plmnId[0].numMncDigits; 
      neighCfg->plmn.mcc[0] = msmNghEutraCell->plmnId[0].mcc[0];
      neighCfg->plmn.mcc[1] = msmNghEutraCell->plmnId[0].mcc[1];
      neighCfg->plmn.mcc[2] = msmNghEutraCell->plmnId[0].mcc[2];

      neighCfg->plmn.mnc[0] = msmNghEutraCell->plmnId[0].mnc[0]; 
      neighCfg->plmn.mnc[1] = msmNghEutraCell->plmnId[0].mnc[1];
      neighCfg->plmn.mnc[2] = msmNghEutraCell->plmnId[0].mnc[2];

       MsmNeighCellCfg * nghCellCfg = &(lteeNodeBparams[cellCfgIdx].lteNeighCellCfg);
       if(nghCellCfg->t.neighAddCfg[idx].eutraCell.isIpv4Pres == TRUE)
      {
         neighCfg->ipAddr.u.ipv4TptAddr.port = WRSM_LCZ_ENB_SCTPORT;
         neighCfg->ipAddr.u.ipv4TptAddr.address = nghCellCfg->t.neighAddCfg[idx].eutraCell.enbAddr;
       
       }
       else if(nghCellCfg->t.neighAddCfg[idx].eutraCell.isIpv6Pres == TRUE)
      {
         neighCfg->ipAddr.u.ipv6TptAddr.port = WRSM_LCZ_ENB_SCTPORT;
         neighCfg->ipAddr.u.ipv4TptAddr.address = nghCellCfg->t.neighAddCfg[idx].eutraCell.enbAddr;
         cmMemcpy((U8*)neighCfg->ipAddr.u.ipv6TptAddr.ipv6NetAddr, 
                   (U8*)&(nghCellCfg->t.neighAddCfg[idx].eutraCell.enbIpv6Addr), sizeof(CmInetIpAddr6));
       }
       
      

      /* LTE_ADV_DSFR starts */
      /* neighCfg->dsfrCEFreqRange = smCfgCb.wrNghCellCfg[cellCfgIdx][0]->dsfrCEFreqRange;*/
      /* LTE_ADV_DSFR ends */
      neighCfg->state = wrSmDfltNeEnbState;
      if ( ( neighCfg->enbType == WR_ENODEB_TYPE_MACRO ) &&
            ((msmNghEutraCell->isX2Reqd == WR_X2_CON_ENBL_ALL ) ||
             (msmNghEutraCell->isX2Reqd == WR_X2_CON_ENBL_MACRO )))
      {
         neighCfg->isX2Reqd = TRUE;
      }
      else if ( ( neighCfg->enbType == WR_ENODEB_TYPE_HOME) &&
            ((msmNghEutraCell->isX2Reqd == WR_X2_CON_ENBL_ALL ) ||
             (msmNghEutraCell->isX2Reqd == WR_X2_CON_ENBL_FEMTO )))
      {
         neighCfg->isX2Reqd = TRUE;
      }
      else
      {
         neighCfg->isX2Reqd = FALSE;
         msmNghEutraCell->isX2Reqd = FALSE;
      }
      neighCfg++;
   }
   RETVALUE(ROK);
} /* end of wrSmmEnbBuildWrNghCfg */ 

/*
 *
 *       Fun:   wrSmmEnbBuildWrNehCellCfg
 *
 *       Desc:  This function for filling neighbour cell configuration
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
#ifdef ANSI
PUBLIC S16 wrSmmEnbBuildWrNehCellCfg
(
 LwrMngmt *lwrMng,
 U8        cellCfgIdx
 )
#else /* if ANSI not defined*/
PUBLIC S16 wrSmmEnbBuildWrNehCellCfg(*lwrMng, cellCfgIdx)
   LwrMngmt *lwrMng;
   U8        cellCfgIdx;
#endif /* end of ANSI*/
{
   LwrEUTRANeighCell *eutraNeghCell = NULLP;
   MsmEUTRANeighCell *msmNghEutraCell = NULLP; 
   U32 idx;

   TRC2(wrSmmEnbBuildWrNehCellCfg);

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = cellCfgIdx + 1; /* this is ownCellID in case of PLD, jst a logical entity */
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = lteeNodeBparams[cellCfgIdx]. \
                                                lteNeighCellCfg.numEutraCells; 
   for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.numEutraCells; \
         idx++)
   {
      msmNghEutraCell = &lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.t.neighAddCfg[idx].eutraCell;
      lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].type =
         WR_NEIGH_CELL_EUTRA;
      eutraNeghCell =&(lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].
            t.eutraCell);
      eutraNeghCell->cellNum = wrSmDfltNeigCellNum[idx];
      eutraNeghCell->nrIndex =  msmNghEutraCell->nrIndex;
      eutraNeghCell->enbId = msmNghEutraCell->cid;

      eutraNeghCell->cio = msmNghEutraCell->cio;
      eutraNeghCell->enbPlmn.numMncDigits =  msmNghEutraCell->plmnId[0]. \
                                             numMncDigits;
      eutraNeghCell->enbPlmn.mcc[0] = msmNghEutraCell->plmnId[0].mcc[0];
      eutraNeghCell->enbPlmn.mcc[1] = msmNghEutraCell->plmnId[0].mcc[1];
      eutraNeghCell->enbPlmn.mcc[2] = msmNghEutraCell->plmnId[0].mcc[2];
      eutraNeghCell->enbPlmn.mnc[0] = msmNghEutraCell->plmnId[0].mnc[0];
      eutraNeghCell->enbPlmn.mnc[1] = msmNghEutraCell->plmnId[0].mnc[1];
      eutraNeghCell->enbPlmn.mnc[2] = msmNghEutraCell->plmnId[0].mnc[2];

      eutraNeghCell->enbType = smGetEnbType(msmNghEutraCell->pci,cellCfgIdx);
      eutraNeghCell->numPlmn = wrSmDfltNeighCellNoPlmn;

      eutraNeghCell->pci =  msmNghEutraCell->pci;
      eutraNeghCell->tac =  msmNghEutraCell->tac; 

      eutraNeghCell->qoffset = msmNghEutraCell->qoffset;

      eutraNeghCell->dlBw = msmNghEutraCell->dlBw;
      eutraNeghCell->earfcnDl = msmNghEutraCell->earfcnDl;
      eutraNeghCell->earfcnUl = msmNghEutraCell->earfcnUl;

      /* CSG_DEV start */
      eutraNeghCell->isCsgIdResolved = WR_EMM_NBR_CSG_ID_DISCOVERED;
      eutraNeghCell->isCsgAccessModeResolved = WR_EMM_CELL_ACCESS_MODE_DETERMINED;
      eutraNeghCell->csgAccessMode = msmNghEutraCell->csgAccessMode;
      eutraNeghCell->csgId = msmNghEutraCell->csgId;
      /* CSG_DEV end */

      /*  eutraNeghCell++;*/
      /* CNM_DEV start */
      eutraNeghCell->numAntenna = msmNghEutraCell->numAntenna;
      eutraNeghCell->ulDlSubFrameCfg = msmNghEutraCell->ulDlSubFrameCfg;
      eutraNeghCell->splSfCfg = msmNghEutraCell->splSfCfg;
      eutraNeghCell->cpDl = msmNghEutraCell->cpDl;
      eutraNeghCell->cpUl = msmNghEutraCell->cpUl;
      eutraNeghCell->rsrp = msmNghEutraCell->rsrp;
      eutraNeghCell->rssi = msmNghEutraCell->rssi;
      eutraNeghCell->isHeMsCell = msmNghEutraCell->isHeMsCell;
      /* CNM_DEV end */
   }   

   RETVALUE(ROK);
} /* end of wrSmmEnbBuildWrNehCellCfg */

/*
 *
 *       Fun:   wrSmmEnbBuildWrNehUtraFddCellCfg
 *
 *       Desc:  This function for filling neighbour cell configuration
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
#ifdef ANSI
PUBLIC S16 wrSmmEnbBuildWrNehUtraFddCellCfg
(
 LwrMngmt                     *lwrMng,
 U8                            cellCfgIdx
 )
#else /* if ANSI not defined*/
PUBLIC S16 wrSmmEnbBuildWrNehUtraFddCellCfg(*lwrMng, cellCfgIdx)
   LwrMngmt                     *lwrMng;
   U8                            cellCfgIdx;
#endif /* end of ANSI*/
{
   U8                        idx = 0;
   U8                        plmnIdx = 0;
   LwrUtraNeighCell          *utraNeghCell = NULLP;
   MsmUtraNeighCell          *msmNghUtraCell = NULLP;

   TRC2(wrSmmEnbBuildWrNehUtraFddCellCfg);

   for (idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.numUtraCells; \
         idx++) 
   {
      msmNghUtraCell = &lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.t.\
                       neighAddCfg[idx].utranCell;
      lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].type = 
         WR_NEIGH_CELL_UTRA_FDD;

      utraNeghCell =&(lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].
            t.utranCell);

      utraNeghCell->nrIndex = msmNghUtraCell->nrIndex;
      utraNeghCell->rncId = msmNghUtraCell->rncId;

      utraNeghCell->cId =  msmNghUtraCell->cId;

      utraNeghCell->numPlmn = msmNghUtraCell->numPlmn;
      for(plmnIdx = 0; plmnIdx < utraNeghCell->numPlmn; plmnIdx++)
      {
         /*Fix for ccpu00124056 */
         utraNeghCell->plmnId[plmnIdx].mcc[0] = msmNghUtraCell->plmnId[plmnIdx].mcc[0];
         utraNeghCell->plmnId[plmnIdx].mcc[1] = msmNghUtraCell->plmnId[plmnIdx].mcc[1];
         utraNeghCell->plmnId[plmnIdx].mcc[2] = msmNghUtraCell->plmnId[plmnIdx].mcc[2];

         utraNeghCell->plmnId[plmnIdx].numMncDigits = msmNghUtraCell-> \
                                                      plmnId[plmnIdx].numMncDigits;

         utraNeghCell->plmnId[plmnIdx].mnc[0] = msmNghUtraCell->plmnId[plmnIdx].mnc[0]; 
         utraNeghCell->plmnId[plmnIdx].mnc[1] = msmNghUtraCell->plmnId[plmnIdx].mnc[1];

         if(3 == utraNeghCell->plmnId[plmnIdx].numMncDigits)
            utraNeghCell->plmnId[plmnIdx].mnc[2] = msmNghUtraCell->plmnId[plmnIdx].mnc[2];
         /*End Fix for ccpu00124056 */
      }

      utraNeghCell->duplexMode = MSM_UTRA_DUPLEX_MODE_FDD;
      utraNeghCell->t.utraFdd.psc = msmNghUtraCell->psc;
      utraNeghCell->t.utraFdd.arfcnDl = msmNghUtraCell->arfcnDl;
      utraNeghCell->t.utraFdd.arfcnUl = msmNghUtraCell->arfcnUl;
      utraNeghCell->t.utraFdd.isHOAllowed = TRUE;
      utraNeghCell->t.utraFdd.pcpich = 70;
      utraNeghCell->lac = msmNghUtraCell->lac;
      utraNeghCell->rac = msmNghUtraCell->rac;
      utraNeghCell->isRimSupported = msmNghUtraCell->isRimSupported;
      utraNeghCell->isVoipCapable = msmNghUtraCell->isVoipCapable;
      utraNeghCell->isPsHOCapable = msmNghUtraCell->isPsHOCapable;
   }
   RETVALUE(ROK);
} /* end of wrSmmEnbBuildWrNehUtraFddCellCfg */

/*
 *
 *       Fun:   wrSmmEnbBuildWrNehUtraTddCellCfg
 *
 *       Desc:  This function for filling neighbour cell configuration
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
#ifdef ANSI
PUBLIC S16 wrSmmEnbBuildWrNehUtraTddCellCfg
(
 LwrMngmt                     *lwrMng,
 U8                            cellCfgIdx
 )
#else /* if ANSI not defined*/
PUBLIC S16 wrSmmEnbBuildWrNehUtraTddCellCfg(*lwrMng, cellCfgIdx)
   LwrMngmt                     *lwrMng;
   U8                            cellCfgIdx;
#endif /* end of ANSI*/
{
   U8                        idx = 0;
   U8                        plmnIdx = 0;
   LwrUtraNeighCell          *utraNeghCell = NULLP;
   MsmUtraTddNeighCell       *msmNghUtraTddCell = NULLP;

   TRC2(wrSmmEnbBuildWrNehUtraTddCellCfg);

   for (idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.numUtraTddCells; idx++) 
   {
      msmNghUtraTddCell = &lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.t.\
                          neighAddCfg[idx].utranTddCell;
      lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].type = 
         WR_NEIGH_CELL_UTRA_TDD;

      utraNeghCell =&(lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[idx].
            t.utranCell);

      utraNeghCell->nrIndex = msmNghUtraTddCell->nrIndex;
      utraNeghCell->rncId = msmNghUtraTddCell->rncId; 

      utraNeghCell->cId =  msmNghUtraTddCell->cId;

      utraNeghCell->numPlmn = msmNghUtraTddCell->numPlmn;
      for(plmnIdx = 0; plmnIdx < utraNeghCell->numPlmn; plmnIdx++)
      {
         /*Fix for ccpu00124056 */
         utraNeghCell->plmnId[plmnIdx].mcc[0] = msmNghUtraTddCell-> \
                                                plmnId[plmnIdx].mcc[0];
         utraNeghCell->plmnId[plmnIdx].mcc[1] = msmNghUtraTddCell-> \
                                                plmnId[plmnIdx].mcc[1];
         utraNeghCell->plmnId[plmnIdx].mcc[2] = msmNghUtraTddCell-> \
                                                plmnId[plmnIdx].mcc[2];

         utraNeghCell->plmnId[plmnIdx].numMncDigits = msmNghUtraTddCell-> \
                                                      plmnId[plmnIdx].numMncDigits;

         utraNeghCell->plmnId[plmnIdx].mnc[0] = msmNghUtraTddCell-> \
                                                plmnId[plmnIdx].mnc[0];
         utraNeghCell->plmnId[plmnIdx].mcc[1] = msmNghUtraTddCell-> \
                                                plmnId[plmnIdx].mnc[1];

         if(3 == msmNghUtraTddCell->plmnId[plmnIdx].numMncDigits)
            utraNeghCell->plmnId[plmnIdx].mcc[2] = msmNghUtraTddCell-> \
                                                   plmnId[plmnIdx].mnc[2];
         /*End Fix for ccpu00124056 */
      }

      utraNeghCell->duplexMode = MSM_UTRA_DUPLEX_MODE_TDD;
      utraNeghCell->t.utraTdd.cellParamId = msmNghUtraTddCell->cellParamId;
      utraNeghCell->t.utraTdd.arfcn = msmNghUtraTddCell->arfcn;
      utraNeghCell->t.utraTdd.pccpch = msmNghUtraTddCell->pccpch; 
      utraNeghCell->lac = msmNghUtraTddCell->lac; 
      utraNeghCell->rac = msmNghUtraTddCell->rac;
      utraNeghCell->isRimSupported = msmNghUtraTddCell->isRimSupported;
   }
   RETVALUE(ROK);
} /* end of wrSmmEnbBuildWrNehUtraTddCellCfg */

/*
 *
 *       Fun:   wrSmmEnbBuildCdma1xRTTBandClass
 *
 *       Desc:  This function for filling the Cell Band Class Configuration
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
#ifdef ANSI
PUBLIC S16 wrSmmEnbBuildCdma1xRTTBandClass
(
 LwrMngmt *lwrMng,
 U8        cellCfgIdx
 )
#else
PUBLIC S16 wrSmmEnbBuildCdma1xRTTBandClass(*lwrMng, cellCfgIdx)
   LwrMngmt *lwrMng;
   U8        cellCfgIdx;
#endif
{
   LwrNeighBandClassCfg *bandClassCfg = NULLP;
   MsmCdmaBandClassCfg  *bandClass = NULLP;
   U8                    idx = 0;
   U8                    numOfBandCls = 0;

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_BAND_CLASS;
   lwrMng->t.protoCfg.t.bandClassCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.bandClassCfg.cellId = cellCfgIdx + 1;

   bandClassCfg =lwrMng->t.protoCfg.t.bandClassCfg.t.bcAddCfg;

   for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].cdmaBandClassParams. \
         numBandClass ; idx++)
   { 
      bandClass = &lteeNodeBparams[cellCfgIdx].cdmaBandClassParams.t. \
                  bandClassAddCfg[idx].t.bandClass1XRtt,
                bandClassCfg->bandType = LWR_NEIGH_BAND_TYPE_CDMA_1XRTT;
      bandClassCfg->t.bandClass1xRtt.reCfgType = wrSmDfltBandClsReCfgType;
      bandClassCfg->t.bandClass1xRtt.bandClassIndex = idx;
      bandClassCfg->t.bandClass1xRtt.bandClass = bandClass->bandClass; 
      bandClassCfg->t.bandClass1xRtt.cellReselectPrior = bandClass->cellReselectPrior;
      bandClassCfg->t.bandClass1xRtt.threshXHigh = bandClass->threshXHigh; 
      bandClassCfg->t.bandClass1xRtt.threshXLow = bandClass->threshXLow;
      bandClassCfg++;
      numOfBandCls++;
   } 
   lwrMng->t.protoCfg.t.bandClassCfg.numBandClass = numOfBandCls;

   RETVALUE(ROK);
}/* wrSmmEnbBuildCdma1xRTTBandClass */

/*
 *
 *       Fun: wrSmmEnbBuildWrNr1xCdmaCellCfg- Build Neighbour cell
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp.c
 *
 */
PUBLIC S16 wrSmmEnbBuildWrNr1xCdmaCellCfg
(
 LwrMngmt *lwrMng,
 U8      cellCfgIdx
 )
{
   LwrNeighCellAddCfg *nrCellCfg = NULLP;
   MsmCDMA1xNeighCell *msmNghCdma1xCell = NULLP;
   U32                idx = 0;
   U32                idx1 = 0;
   U8                 numCells = 0;

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = cellCfgIdx + 1;

   for(idx=0; idx < lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.numCdma1xCells;\
         idx++)
   {
      for(idx1 = 0; idx1<
            lteeNodeBparams[cellCfgIdx].cdmaBandClassParams.numBandClass; idx1++)
      {
         if(lteeNodeBparams[cellCfgIdx].cdmaBandClassParams.t.bandClassAddCfg\
               [idx1].t.bandClass1XRtt.bandClass ==
               lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.t.neighAddCfg[idx].\
               cdma1xCell.bandClass)
         {
            nrCellCfg = &(lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg[numCells]);

            msmNghCdma1xCell = &(lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.\
                  t.neighAddCfg[idx].cdma1xCell);
            nrCellCfg->type = WR_NEIGH_CELL_CDMA2K_1XRTT;
            nrCellCfg->t.cdma1xCell.cellNum = 1;
            nrCellCfg->t.cdma1xCell.nrIndex = idx;
            nrCellCfg->t.cdma1xCell.status = TRUE;

            nrCellCfg->t.cdma1xCell.bandClass = msmNghCdma1xCell->bandClass;
            nrCellCfg->t.cdma1xCell.arfcn = msmNghCdma1xCell->arfcn;
            nrCellCfg->t.cdma1xCell.pnOffset = msmNghCdma1xCell->pnOffset; 
            nrCellCfg->t.cdma1xCell.curRank = msmNghCdma1xCell->curRank;
            nrCellCfg->t.cdma1xCell.neighCellFlag = FALSE;
            nrCellCfg->t.cdma1xCell.systemType = msmNghCdma1xCell->systemType;
            nrCellCfg->t.cdma1xCell.channelNum = msmNghCdma1xCell->channelNum;
            nrCellCfg->t.cdma1xCell.pilotOneWay = wrSmDfltCdmaPilotOneWay;
            nrCellCfg->t.cdma1xCell.secId.cdmaType = msmNghCdma1xCell->cellType;
            nrCellCfg->t.cdma1xCell.secId.isOctStrPres = FALSE;

            if(TRUE == nrCellCfg->t.cdma1xCell.secId.isOctStrPres)
            {
               wrFillSectorId(&nrCellCfg->t.cdma1xCell.secId.s.sectorIdPtr, 5,
                     (Data *)&wrSmDfltSecIdPerNgh);
            }
            else
            {
               nrCellCfg->t.cdma1xCell.secId.s.cdmaSectorId.marketId = 
                  msmNghCdma1xCell->tgtCell.marketId;
               nrCellCfg->t.cdma1xCell.secId.s.cdmaSectorId.switchNum = 
                  msmNghCdma1xCell->tgtCell.switchNum;
               nrCellCfg->t.cdma1xCell.secId.s.cdmaSectorId.cellId = 
                  msmNghCdma1xCell->tgtCell.cellId;
               nrCellCfg->t.cdma1xCell.secId.s.cdmaSectorId.sectorNum = 
                  msmNghCdma1xCell->tgtCell.sectorNum;
            }
            wrSmmEnbBuildMobParams(&nrCellCfg->t.cdma1xCell.mobParams,
                  cellCfgIdx);
            numCells++;
         }
      }
   }
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = numCells;
   RETVALUE(ROK);
}/*wrSmmEnbBuildWrNr1xCdmaCellCfg*/ 

/*
 *
 *       Fun: wrSmmEnbBuildWrNr1xCdmaFreqCfg- Build Neighbour frequency
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp.c
 *
 */

PUBLIC S16 wrSmmEnbBuildWrNr1xCdmaFreqCfg
(
 LwrMngmt *lwrMng,
 U8        cellCfgIdx
 )
{
   LwrNeighFreqAddModCfg *nrFreqCfg =NULLP;
   MsmLteNeighCdma1xFreq *cdma1xNeighFreqCfg = NULLP;
   U32 idx = 0;
   U32 idx1 = 0;
   U8  numFreqAdded = 0;

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = cellCfgIdx + 1;

   for(idx=0; idx < lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numCdma1xFreq; \
         idx++)
   {
      for(idx1 = 0; idx1<
            lteeNodeBparams[cellCfgIdx].cdmaBandClassParams.numBandClass; idx1++)
      {
         if(lteeNodeBparams[cellCfgIdx].cdmaBandClassParams.t.bandClassAddCfg\
               [idx1].t.bandClass1XRtt.bandClass ==
               lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t.addNeighFreq[idx].\
               cdma1xFreq.bandClass)
         {
            cdma1xNeighFreqCfg = &lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t. \
                                 addNeighFreq[idx].cdma1xFreq;
            nrFreqCfg = lwrMng->t.protoCfg.t.neighFreqCfg.t.addNeighFreq;

            nrFreqCfg->type = WR_NEIGH_CELL_CDMA2K_1XRTT;

            nrFreqCfg->t.cdma1xFreq.reCfgType = wrSmDfltCdma1xNeighFreqReCfgType;
            nrFreqCfg->t.cdma1xFreq.freqIndex = idx1;
            nrFreqCfg->t.cdma1xFreq.status = TRUE;
            nrFreqCfg->t.cdma1xFreq.bandClass = cdma1xNeighFreqCfg->bandClass;
            nrFreqCfg->t.cdma1xFreq.arfcn = cdma1xNeighFreqCfg->arfcn;
            nrFreqCfg->t.cdma1xFreq.searchRate = cdma1xNeighFreqCfg->searchRate;     
            nrFreqCfg->t.cdma1xFreq.offsetFreq = wrSmDfltCdma1xOffsetFreq;
            nrFreqCfg->t.cdma1xFreq.freqPriority = cdma1xNeighFreqCfg->freqPriority;

            numFreqAdded++;
         }
      }
   }
   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = numFreqAdded;
   RETVALUE(ROK);
}/*wrSmmEnbBuildWrNr1xCdmaFreqCfg*/

/*
 *
 *       Fun:    wrSmmEnbBuildWrNrGeranFreqCfg - Build Neighbour frequency
 *
 *       Desc:  LwrMngmt filled for GERAN freq configuration 
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp_utils.c
 *
 */
PUBLIC S16 wrSmmEnbBuildWrNrGeranFreqCfg
(
 LwrMngmt *lwrMng,
 U8        cellCfgIdx
 )
{
   U8  idx = 0;
   LwrNeighFreqAddModCfg *nrFreqCfg = NULLP;
   //LwrNeighGERANFreq  *geranFreqCfg = NULLP;
   MsmLteNeighGERANFreq *msmNghGeranFreq = NULLP;

   TRC2(wrSmmEnbBuildWrNrGeranFreqCfg);

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_FREQ;
   lwrMng->t.protoCfg.t.neighFreqCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighFreqCfg.cellId = cellCfgIdx + 1; /* this is ownCellID in case of
                                                                 PLD based conf, jst a logic entity */
   lwrMng->t.protoCfg.t.neighFreqCfg.numFreq = lteeNodeBparams[cellCfgIdx]. \
                                               lteNeighFreqCfg.numGeranFreq;
   nrFreqCfg = lwrMng->t.protoCfg.t.neighFreqCfg.t.addNeighFreq;

   for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numGeranFreq; \
         idx++)
   {
      msmNghGeranFreq = &lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t. \
                        addNeighFreq[idx].geranFreq;
      nrFreqCfg->type = WR_NEIGH_CELL_GERAN;
      nrFreqCfg->t.geranFreq.reCfgType     = 0x000fff;     
      nrFreqCfg->t.geranFreq.freqIndex     = idx+1;     
      nrFreqCfg->t.geranFreq.status        = wrSmDfltStatus;
      nrFreqCfg->t.geranFreq.bandIndicator = msmNghGeranFreq->bandIndicator;
      nrFreqCfg->t.geranFreq.bcchArfcn     = msmNghGeranFreq->bcchArfcn;
      nrFreqCfg->t.geranFreq.qRxLevMin     = msmNghGeranFreq->qRxLevMin;
      nrFreqCfg->t.geranFreq.cellReselePri = msmNghGeranFreq->cellReselectionPriority;
      nrFreqCfg->t.geranFreq.threshXHigh   = msmNghGeranFreq->threshXHigh;
      nrFreqCfg->t.geranFreq.threshXLow    = msmNghGeranFreq->threshXLow;
      nrFreqCfg->t.geranFreq.ncc_Permitted = msmNghGeranFreq->ncc_Permitted;
      nrFreqCfg->t.geranFreq.pMaxGeran.pres= msmNghGeranFreq->pMaxPres;
      nrFreqCfg->t.geranFreq.pMaxGeran.val = msmNghGeranFreq->pMax;
      nrFreqCfg++;
   }
   RETVALUE(ROK);
} /* end of wrSmmEnbBuildWrNrGeranFreqCfg*/

/*
 *
 *       Fun:    wrSmmEnbBuildWrNrGeranCellCfg - Build Neighbour cell cfg
 *
 *       Desc:   
 *
 *       Ret:    Void
 *
 *       Notes:  None
 *
 *      File:    wr_smm_enbapp.c
 *
 */
PUBLIC S16 wrSmmEnbBuildWrNrGeranCellCfg
(
 LwrMngmt *lwrMng,
 U8        cellCfgIdx
 )
{
   U8  idx = 0;
   LwrNeighCellAddCfg *nrCellCfg =NULLP;
   MsmLteGERANNeighCell *msmNghGeranCell = NULLP;

   TRC2(wrSmmEnbBuildWrNrGeranCellCfg);

   lwrMng->t.protoCfg.type = WR_CFG_TYPE_NEIGH_CELL;
   lwrMng->t.protoCfg.t.neighCellCfg.action = WR_ACT_ADD;
   lwrMng->t.protoCfg.t.neighCellCfg.cellId = cellCfgIdx + 1; /* this is ownCellID in case of
                                                                 PLD based conf, jst a logic entity */
   lwrMng->t.protoCfg.t.neighCellCfg.numCells = (U8)lteeNodeBparams[cellCfgIdx]. \
                                                lteNeighCellCfg.numGeranCells;
   nrCellCfg =lwrMng->t.protoCfg.t.neighCellCfg.t.neighAddCfg; 

   for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.numGeranCells; \
         idx++) /*TODO:check for >/= smCfgCb.noOfGeranCell */
   { 
      msmNghGeranCell = &lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.t.\
                        neighAddCfg[idx].geranCell;
      nrCellCfg->type                      = WR_NEIGH_CELL_GERAN;
      nrCellCfg->t.geranCell.reCfgType     = wrSmDfltGeranReCfgType;
      nrCellCfg->t.geranCell.status        = wrSmDfltStatus;
      nrCellCfg->t.geranCell.nrIndex       = idx+1;
      nrCellCfg->t.geranCell.plmnId.numMncDigits = msmNghGeranCell->plmnId.numMncDigits;
      nrCellCfg->t.geranCell.plmnId.mcc[0] = msmNghGeranCell->plmnId.mcc[0];
      nrCellCfg->t.geranCell.plmnId.mcc[1] = msmNghGeranCell->plmnId.mcc[1];
      nrCellCfg->t.geranCell.plmnId.mcc[2] = msmNghGeranCell->plmnId.mcc[2];
      nrCellCfg->t.geranCell.plmnId.mnc[0] = msmNghGeranCell->plmnId.mnc[0];
      nrCellCfg->t.geranCell.plmnId.mnc[1] = msmNghGeranCell->plmnId.mnc[1];
      if(msmNghGeranCell->plmnId.numMncDigits == 3)
      {
         nrCellCfg->t.geranCell.plmnId.mnc[2] = msmNghGeranCell->plmnId.mnc[2];
      }
      nrCellCfg->t.geranCell.lac           = msmNghGeranCell->lac;
      nrCellCfg->t.geranCell.rac           = msmNghGeranCell->rac;
      nrCellCfg->t.geranCell.bsic          = msmNghGeranCell->bsic;
      nrCellCfg->t.geranCell.ci            = msmNghGeranCell->ci;
      nrCellCfg->t.geranCell.bandIndicator = msmNghGeranCell->bandIndicator; 
      nrCellCfg->t.geranCell.bcchArfcn     = msmNghGeranCell->bcchArfcn;
      nrCellCfg->t.geranCell.nccPermittedMeas = msmNghGeranCell->ncc_PermittedMeas;
      nrCellCfg->t.geranCell.isDTMCapable  = msmNghGeranCell->isDTMCapable;
      nrCellCfg->t.geranCell.rimSupportForGeranNgh  = msmNghGeranCell-> \
                                                      rimSupportForGeranNgh; 

      nrCellCfg->t.geranCell.ncoVal        = msmNghGeranCell->networkControlOrder;
      nrCellCfg->t.geranCell.ncoPres       = msmNghGeranCell-> \
                                             networkControlOrderPres;
      nrCellCfg->t.geranCell.offsetFreq    = msmNghGeranCell->offsetFreq ;
      nrCellCfg++;
   }
   RETVALUE(ROK);
} /* end of wrSmmEnbBuildWrNrGeranCellCfg */

/*files from enapp_utils.c*/
/*
 * 
 *        Fun:   wrSmmEnbFillX2InitCntrl
 * 
 *        Desc:  fill x2 params
 * 
 *        Ret:   ROK
 * 
 *        Notes: None
 *               
 *        File:  wr_smm_enb_utils.c 
 */
#ifdef ANSI
PUBLIC S16 wrSmmEnbFillX2InitCntrl
(
 LwrMngmt *cntrl,
 U8   cellCfgIndx
 )
#else /* if ANSI not defined*/
PUBLIC S16 wrSmmEnbFillX2InitCntrl(lwrMng, cellCfgIndx)
   LwrMngmt *cntrl;
   U8   cellCfgIndx;
#endif /* end of ANSI*/
{
   U8       noOfCfg; 

   TRC2(wrSmmEnbFillX2InitCntrl);

   for ( noOfCfg=0; noOfCfg < lteeNodeBparams[cellCfgIndx].lteNeighCellCfg. \
         numEutraCells; noOfCfg++)
   {
      cntrl->t.cntrl.idLst[noOfCfg] = lteeNodeBparams[cellCfgIndx].lteNeighCellCfg. \
                                      t.neighAddCfg[noOfCfg].eutraCell.peerId;
   }
   cntrl->t.cntrl.numConn = noOfCfg;

   RETVALUE(ROK);
} /* end of wrSmmEnbFillX2InitCntrl */    

/*
 *
 *       Fun:   wrSmmEnbBuildDynWrNbrEnbCfg
 *
 *       Desc:  fill in neighbour Cfg for WR
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *              
 *       File:  wr_sm_wr_cntrl.c 
 *
 */
#ifdef ANSI
PUBLIC S16 wrSmmEnbBuildDynWrNbrEnbCfg
(
 U32    idx,
 LwrMngmt *lwrMng
 )
#else /* if ANSI not defined*/
PUBLIC S16 wrSmmEnbBuildDynWrNbrEnbCfg(idx,lwrMng)
   U32    idx;
   LwrMngmt *lwrMng;
#endif /* end of ANSI*/
{
   TRC2(wrSmmEnbBuildDynWrNbrEnbCfg);

   lwrMng->t.nbrAddCfm.enbId = lteeNodeBparams[WR_DFLT_CELL_IDX].lteNeighCellCfg. \
                               t.neighAddCfg[idx].eutraCell.cid;
   lwrMng->t.nbrAddCfm.peerId =  (lteeNodeBparams[WR_DFLT_CELL_IDX].lteNeighCellCfg. \
         t.neighAddCfg[idx].eutraCell.peerId)-1;
   wrCpyCmTptAddr(&lwrMng->t.nbrAddCfm.ipAddr,&smCfgCb.
         wrNghCellCfg[WR_DFLT_CELL_IDX][idx]->ipAddr);
   RETVALUE(ROK);
}/*wrSmmEnbBuildDynWrNbrEnbCfg*/

/*
 *
 *       Fun:    SmMiLwrAddNeighCfgReq - Neighbor Config Request
 *
 *       Desc:   Process the Neighbor Config Request
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_wr_ptmi.c
 *
 */
#ifdef ANSI
PUBLIC S16 SmMiLwrAddNeighCfgReq
(
 Pst          *pst,
 LwrMngmt     *cfgReq
 )
#else
PUBLIC S16 SmMiLwrAddNeighCfgReq(pst, cfgReq)
   Pst          *pst;
   LwrMngmt     *cfgReq;
#endif /* ANSI */
{
   U8                         idx = 0;
   U8                         dbIdx = 0;
   U8                         cellIdx = 0;
   LwrNghCellCfg             *nghCellCfg;

   TRC2(SmMiLwrAddNeighCfgReq);

   WR_ALLOC(&nghCellCfg, sizeof(LwrNghCellCfg));
   if((nghCellCfg == NULLP) || (NULLP == cfgReq))
   {
      RLOG0(L_FATAL, "Failed to allocate memory for NghCellCfg");
      RETVALUE(RFAILED);
   }
   nghCellCfg->enbId = cfgReq->t.nbrAddReq.enbId;
   nghCellCfg->enbAddr = cfgReq->t.nbrAddReq.nbIpAddress;
   wrCpyCmTptAddr(&nghCellCfg->ipAddr, &cfgReq->t.nbrAddReq.nbIpAddress);
   /*   nghCellCfg->peerId = wrSmmGetX2apFreePeerId();*/
   WR_GET_PEERID_FROM_ENBID(nghCellCfg->enbId, nghCellCfg->peerId);
   if(WR_SMM_INVALID_PEERID == nghCellCfg->peerId)
   {
      RLOG0(L_ERROR, "Failed to get PeerId from wrX2apPeerIdLst List");
      WR_FREE(nghCellCfg, sizeof(LwrNghCellCfg));
      RETVALUE(RFAILED);
   }
   /* check if this neighbor info is already present in smCfgCb list */
   for(idx=0; idx<WR_SMM_MAX_NBR_ENB; idx++)
   {
      for(cellIdx = 0; cellIdx < wrSmDfltNumCells; cellIdx++)
      {
         if(NULLP != smCfgCb.wrNghCellCfg[cellIdx][idx])
         {
            if(nghCellCfg->enbId == lteeNodeBparams[cellIdx].lteNeighCellCfg.t. \
                  neighAddCfg[idx].eutraCell.cid)
            {
               dbIdx = idx;
               /*ccpu00127802*/
               RLOG0(L_WARNING, "Neighbor already present in neighbor list");
               WR_FREE(nghCellCfg, sizeof(LwrNghCellCfg));
               break;
            }
         }
         else if(NULLP == smCfgCb.wrNghCellCfg[cellIdx][idx])
         {
            dbIdx = idx;
            smCfgCb.wrNghCellCfg[cellIdx][idx] = nghCellCfg;
            smCfgCb.noOfNghCfg[cellIdx]++;
            break;
         }
      }
   }
   if(idx == WR_SMM_MAX_NBR_ENB)
   {
      WR_FREE(nghCellCfg, sizeof(LwrNghCellCfg));
      RETVALUE(RFAILED);
   }
   if(cfgReq != NULLP)
   {
      WR_FREE(cfgReq, sizeof(LwrMngmt));
   }
   RLOG1(L_INFO, "smCb.smState before adding dynamic Nbr Enodeb is =%d",
         smCb.smState);
   /*      smCb.smState = WR_SM_STATE_DYN_X2AP_CFG_DONE;*/

#ifndef WR_RSYS_OAM   
   smBuildDynCzPeerCfg(idx +1,dbIdx);/*TO CHECK*/
#endif

   RETVALUE(ROK);
} /* end of SmMiLwrAddNeighCfgReq() */

PRIVATE S16 fillMsmGeranCell(LwrGERANNeighCell *ipCell, MsmLteGERANNeighCell *opCell)
{
   cmMemset((U8*)opCell,0,sizeof(MsmLteGERANNeighCell));

   opCell->lac = ipCell->lac;
   opCell->rac = ipCell->rac;
   opCell->bsic = ipCell->bsic;
   opCell->ci = ipCell->ci;
   opCell->qoffsetGERAN = ipCell->offsetFreq;
   opCell->bandIndicator = ipCell->bandIndicator;
   opCell->bcchArfcn = ipCell->bcchArfcn;
   opCell->ncc_PermittedMeas = ipCell->nccPermittedMeas;
   opCell->isDTMCapable = ipCell->isDTMCapable;
   opCell->rimSupportForGeranNgh = ipCell->rimSupportForGeranNgh;
   opCell->networkControlOrder = ipCell->ncoVal;
   opCell->networkControlOrderPres = ipCell->ncoPres;
   opCell->qoffsetGERAN = ipCell->offsetFreq;

   opCell->plmnId.numMncDigits = ipCell->plmnId.numMncDigits;
   opCell->plmnId.mcc[0] = ipCell->plmnId.mcc[0];
   opCell->plmnId.mcc[1] = ipCell->plmnId.mcc[1];
   opCell->plmnId.mcc[2] = ipCell->plmnId.mcc[2];
   opCell->plmnId.mnc[0] = ipCell->plmnId.mnc[0];
   opCell->plmnId.mnc[1] = ipCell->plmnId.mnc[1];
   opCell->plmnId.mnc[2] = ipCell->plmnId.mnc[2];

   RETVALUE(ROK);
}

PRIVATE S16 fillMsmEutraCell(LwrEUTRANeighCell *ipCell, MsmEUTRANeighCell *opCell)
{
   cmMemset((U8*)opCell,0,sizeof(MsmEUTRANeighCell));

   opCell->cid = ipCell->enbId;
   opCell->pci = ipCell->pci;
   opCell->tac = ipCell->tac;

   opCell->numPlmn = ipCell->numPlmn;
   opCell->plmnId[0].numMncDigits = ipCell->enbPlmn.numMncDigits;
   opCell->plmnId[0].mcc[0] = ipCell->enbPlmn.mcc[0];
   opCell->plmnId[0].mcc[1] = ipCell->enbPlmn.mcc[1];
   opCell->plmnId[0].mcc[2] = ipCell->enbPlmn.mcc[2];
   opCell->plmnId[0].mnc[0] = ipCell->enbPlmn.mnc[0];
   opCell->plmnId[0].mnc[1] = ipCell->enbPlmn.mnc[1];
   opCell->plmnId[0].mnc[2] = ipCell->enbPlmn.mnc[2];
   opCell->earfcnDl = ipCell->earfcnDl;
   opCell->earfcnUl = ipCell->earfcnUl;
   opCell->cio = ipCell->cio;
   opCell->qoffset = ipCell->qoffset;
   opCell->RSTxPower = ipCell->refSigPower;
   opCell->BlackListed = ipCell->blackListed;
   opCell->csgAccessMode = ipCell->csgAccessMode;
   opCell->csgId = ipCell->csgId;
   opCell->numAntenna = ipCell->numAntenna;
   opCell->ulDlSubFrameCfg = ipCell->ulDlSubFrameCfg;
   opCell->splSfCfg = ipCell->splSfCfg;
   opCell->cpDl = ipCell->cpDl;
   opCell->cpUl = ipCell->cpUl;
   opCell->rsrp = ipCell->rsrp;
   opCell->rssi = ipCell->rssi;
   opCell->ulBw = ipCell->ulBw;
   opCell->dlBw = ipCell->dlBw;

   RETVALUE(ROK);
}

PRIVATE S16 fillMsmUtraCell(LwrUtraNeighCell *ipCell, MsmUtraNeighCell *opCell)
{
   U32 idx;

   cmMemset((U8*)opCell,0,sizeof(MsmUtraNeighCell));

   opCell->rncId = ipCell->rncId;
   opCell->cId = ipCell->cId;
   opCell->lac = ipCell->lac;
   opCell->rac = ipCell->rac;

   opCell->numPlmn = ipCell->numPlmn;
   for (idx=0; idx < ipCell->numPlmn; idx++)
   {
      opCell->plmnId[idx].numMncDigits = ipCell->plmnId[idx].numMncDigits;
      opCell->plmnId[idx].mcc[0] = ipCell->plmnId[idx].mcc[0];
      opCell->plmnId[idx].mcc[1] = ipCell->plmnId[idx].mcc[1];
      opCell->plmnId[idx].mcc[2] = ipCell->plmnId[idx].mcc[2];
      opCell->plmnId[idx].mnc[0] = ipCell->plmnId[idx].mnc[0];
      opCell->plmnId[idx].mnc[1] = ipCell->plmnId[idx].mnc[1];
      opCell->plmnId[idx].mnc[2] = ipCell->plmnId[idx].mnc[2];
   }

   opCell->psc = ipCell->t.utraFdd.psc;
   opCell->arfcnUl = ipCell->t.utraFdd.arfcnUl;
   opCell->arfcnDl = ipCell->t.utraFdd.arfcnDl;
   opCell->duplexMode = MSM_UTRA_DUPLEX_MODE_FDD;
   opCell->isRimSupported = ipCell->isRimSupported;
   opCell->isVoipCapable = ipCell->isVoipCapable;
   opCell->isPsHOCapable = ipCell->isPsHOCapable;

   RETVALUE(ROK);
}

/*
 *
 *       Fun:    SmMiLwrHdlNghCellInd- Neighbor Cell Indication
 *
 *       Desc:   Process the Neighbor cell indication from application
 *              
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_enb_utils.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLwrHdlNghCellInd 
(
 Pst          *pst,
 LwrNghCellInd *nghCellInfo
 )
#else
PUBLIC S16 SmMiLwrHdlNghCellInd(pst, nghCellInfo)
   Pst          *pst;
   LwrNghCellInd     *nghCellInfo;
#endif /* ANSI */
{
   U32 action;
   MsmEUTRANeighCell msmEutranCell;
   MsmUtraNeighCell  msmUtranCell;
   MsmLteGERANNeighCell msmGeranCell;
   U8                 cellId;

   action = nghCellInfo->action;
   cellId = nghCellInfo->cellId-1;

   if (action == WR_ACT_ADD)
   {
      if (nghCellInfo->t.neighAddCfg.type == WR_NEIGH_CELL_EUTRA)
      {
         fillMsmEutraCell(&nghCellInfo->t.neighAddCfg.t.eutraCell, &msmEutranCell);
#ifdef WR_RSYS_OAM
         SmUpdateMibParms(MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS, MSM_ACT_ADD,
               (void*)&msmEutranCell, cellId);
#endif
      }
      else if (nghCellInfo->t.neighAddCfg.type == WR_NEIGH_CELL_UTRA_FDD)
      {
         fillMsmUtraCell(&nghCellInfo->t.neighAddCfg.t.utranCell, &msmUtranCell);
#ifdef WR_RSYS_OAM
         SmUpdateMibParms(MSM_LTE_UTRA_NEIGHBORLIST_IN_USE_PARAMETERS, MSM_ACT_ADD,
               (void*)&msmUtranCell, cellId);
#endif
      }
      else if(nghCellInfo->t.neighAddCfg.type == WR_NEIGH_CELL_GERAN)
      {
         fillMsmGeranCell(&nghCellInfo->t.neighAddCfg.t.geranCell, &msmGeranCell);
#ifdef WR_RSYS_OAM
         SmUpdateMibParms(MSM_GERAN_NEIGHBOR_CELL_IN_USE_PARAMETERS, MSM_ACT_ADD, (void*)&msmGeranCell,cellId);
#endif
      }
   }
   else if (action == WR_ACT_MOD)
   {
      if (nghCellInfo->t.neighModCfg.type == WR_NEIGH_CELL_EUTRA)
      {
         fillMsmEutraCell(&nghCellInfo->t.neighModCfg.t.eutraCell, &msmEutranCell);
#ifdef WR_RSYS_OAM
         SmUpdateMibParms(MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS, MSM_ACT_MOD,
               (void*)&msmEutranCell,cellId);
#endif
      }
      else if (nghCellInfo->t.neighModCfg.type == WR_NEIGH_CELL_UTRA_FDD)
      {
         fillMsmUtraCell(&nghCellInfo->t.neighModCfg.t.utranCell, &msmUtranCell);
#ifdef WR_RSYS_OAM
         SmUpdateMibParms(MSM_LTE_UTRA_NEIGHBORLIST_IN_USE_PARAMETERS, MSM_ACT_MOD,
               (void*)&msmUtranCell,cellId);
#endif
      }
   }
   else if (action == WR_ACT_DEL)
   {
      if (nghCellInfo->t.neighDelCfg.type == WR_NEIGH_CELL_EUTRA)
      {
         msmEutranCell.cid = nghCellInfo->t.neighDelCfg.t.eutranCell.cid;
         msmEutranCell.plmnId[0].numMncDigits = nghCellInfo->t.neighDelCfg.t.eutranCell.plmnId.numMncDigits;
         msmEutranCell.plmnId[0].mcc[0] = nghCellInfo->t.neighDelCfg.t.eutranCell.plmnId.mcc[0];
         msmEutranCell.plmnId[0].mcc[1] = nghCellInfo->t.neighDelCfg.t.eutranCell.plmnId.mcc[1];
         msmEutranCell.plmnId[0].mcc[2] = nghCellInfo->t.neighDelCfg.t.eutranCell.plmnId.mcc[2];

         msmEutranCell.plmnId[0].mnc[0] = nghCellInfo->t.neighDelCfg.t.eutranCell.plmnId.mnc[0];
         msmEutranCell.plmnId[0].mnc[1] = nghCellInfo->t.neighDelCfg.t.eutranCell.plmnId.mnc[1];
         msmEutranCell.plmnId[0].mnc[2] = nghCellInfo->t.neighDelCfg.t.eutranCell.plmnId.mnc[2];

#ifdef WR_RSYS_OAM
         SmUpdateMibParms(MSM_LTE_EUTRAN_NEIGHBORLIST_IN_USE_PARAMETERS, MSM_ACT_DEL,
               (void*)&msmEutranCell,cellId);
#endif
      }
      else if (nghCellInfo->t.neighDelCfg.type == WR_NEIGH_CELL_UTRA_FDD)
      {
         msmUtranCell.cId = nghCellInfo->t.neighDelCfg.t.utranCell.cid;
         msmUtranCell.plmnId[0].numMncDigits = nghCellInfo->t.neighDelCfg.t.utranCell.plmnId.numMncDigits;
         msmUtranCell.plmnId[0].mcc[0] = nghCellInfo->t.neighDelCfg.t.utranCell.plmnId.mcc[0];
         msmUtranCell.plmnId[0].mcc[1] = nghCellInfo->t.neighDelCfg.t.utranCell.plmnId.mcc[1];
         msmUtranCell.plmnId[0].mcc[2] = nghCellInfo->t.neighDelCfg.t.utranCell.plmnId.mcc[2];

         msmUtranCell.plmnId[0].mnc[0] = nghCellInfo->t.neighDelCfg.t.utranCell.plmnId.mnc[0];
         msmUtranCell.plmnId[0].mnc[1] = nghCellInfo->t.neighDelCfg.t.utranCell.plmnId.mnc[1];
         msmUtranCell.plmnId[0].mnc[2] = nghCellInfo->t.neighDelCfg.t.utranCell.plmnId.mnc[2];

#ifdef WR_RSYS_OAM
         SmUpdateMibParms(MSM_LTE_UTRA_NEIGHBORLIST_IN_USE_PARAMETERS, MSM_ACT_DEL,
               (void*)&msmUtranCell,cellId);
#endif
      }
   }

   WR_FREE(nghCellInfo,sizeof(LwrNghCellInd));
   RETVALUE(ROK);
}

/*
 *
 *       Fun:    SmMiLwrUpDateNhgCellCfgReq - Neighbor Config Request
 *
 *       Desc:   Process the Neighbor Config Request
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_sm_wr_ptmi.c
 *
 */

#ifdef ANSI
PUBLIC S16 SmMiLwrUpDateNhgCellCfgReq 
(
 Pst          *pst,
 LwrMngmt     *cfgReq
 )
#else
PUBLIC S16 SmMiLwrUpDateNhgCellCfgReq(pst, cfgReq)
   Pst          *pst;
   LwrMngmt     *cfgReq;
#endif /* ANSI */
{
   TRC2(SmMiLwrUpDateNhgCellCfgReq)

      /* Memory leak fix ccpu00145573 */ 
      WR_FREE(cfgReq, sizeof(LwrMngmt)); 

   RETVALUE(ROK);
}/*end of SmMiLwrUpDateNhgCellCfgReq*/

#ifdef LTE_ADV
/*
 *
 *       Fun:   wrSmmEnbBuildWrScellCntrl
 *
 *       Desc:  Invokes scell functionalities
 *
 *       Ret:   ROK
 *
 *       Notes: None
 *
 *       File:  wr_smm_enbapp_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 wrSmmEnbBuildWrScellCntrl 
(
 S32 action
 )
#else
PUBLIC S16 wrSmmEnbBuildWrScellCntrl(action)
   S32 action;
#endif
{
   LwrMngmt cntrl;
   Pst      pst;

   TRC2(wrSmmEnbBuildWrScellCntrl)

      SM_SET_ZERO(&cntrl, sizeof(LwrMngmt));
   SM_SET_ZERO(&pst, sizeof(Pst));


   /* Fill Header */
   cntrl.hdr.msgType             = TCNTRL;
   cntrl.hdr.entId.ent           = ENTWR;
   cntrl.hdr.entId.inst          = SM_INST_ZERO;
   cntrl.hdr.response.selector   = SM_SELECTOR_TC;

   switch(action)
   {
      case RGR_SCELLRELEASE:
         cntrl.hdr.elmId.elmnt         = STWRSCELLRELEASE;
         break;
      case RGR_SCELLADD:
         cntrl.hdr.elmId.elmnt         = STWRSCELLADD;
         break;
      case RGR_SCELLACT:
         cntrl.hdr.elmId.elmnt         = STWRSCELLACT;
         break;
      case RGR_SCELLDEACT:
         cntrl.hdr.elmId.elmnt         = STWRSCELLDEACT;
         break;
      default:
         break;
   }

   /* Fill Pst */
   pst.selector  = SM_SELECTOR_TC;
   pst.srcEnt    = ENTSM;
   pst.dstEnt    = ENTWR;
   pst.dstProcId = SM_WR_PROC;
   pst.srcProcId = SM_SM_PROC;
   pst.event     = EVTLWRCNTRLREQ;

   RLOG0(L_EVENT, "Control Req to send ERAB Release Indication");
   /* Send the request to the APP */
   SmMiLwrCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* end of wrSmmEnbBuildWrScellCntrl */
#endif
