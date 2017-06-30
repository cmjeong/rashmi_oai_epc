
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_msm_init.c

     Sid:      fc_smm_msm_init.c@@/main/tenb_ca_rib_msm/14 - Fri Apr  1 19:40:55 2016

     Prg:      Sriky 

*********************************************************************21*/
static const char* RLOG_MODULE_NAME="SMM";
static int RLOG_MODULE_ID=2;
static int RLOG_FILE_ID=270;

#include <stdio.h>
#include <stdlib.h>
#include "wr.h"
#include "wr_lwr.h"
#include "wr_cmn.h"
#include "wr_smm_smallcell.h"
#include "wr_smm_init.h"
#include "wr_utils.h"
#include "wr_msm_common.h" 

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


PUBLIC MsmLteeNodeBparams lteeNodeBparams[WR_MAX_CELLS];
PUBLIC MsmWcdmaNodeBparams wcdmaNodeBparams;
PUBLIC MsmFaultMgmtParams faultMgmtParams;
PUBLIC MsmFapParameters fapParameters;

     /*
     *
     *       Fun:   smInitMsm
     *
     *       Desc:  This function is used to fill msm structure parameter from
     *       smallcell variable in without oam case
     *
     *       Ret:   ROK
     *
     *       Notes: None
     *              
     *       File:  wr_smm_msm_init.c 
     */
     #ifdef ANSI
     PUBLIC Void smInitMsm
     (
      U8 cellCfgIdx
     )
     #else /* if ANSI not defined*/
     PUBLIC Void smInitMsm(cellCfgIdx)
     U8 cellCfgIdx;
     #endif /* end of ANSI*/
     {
#ifndef WR_RSYS_OAM
        /*If a parameter is defined in OAM but not defined in wr_cfg.txt,
         * then add it here*/
        RLOG1(L_DEBUG,"smInitMsm:Initializing params for %d\n",cellCfgIdx);
        U8 idx =0;	
        MsmCdmaMobilityParam *mobParams = NULLP;
        MsmLteNeighFreqCfg *msmNeighFreqCfg = &lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg;
        MsmNeighCellCfg *msmNeighCellCfg = &lteeNodeBparams[cellCfgIdx].lteNeighCellCfg;
        MsmLteSrbPolicy     *msmSrbPolicy = NULLP;
        /*automation: this value has to be read from OAM for with_oam. Its
         * effecting SON_SN automation testcase*/
        MsmPrachCfgInfo *prachCfgInfo = &(lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachCfgInfo);
        lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.pucchPwrFmt3Rnti = 
           wrSmDfltPucchPwrFmt3RntiSt;
        lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.pucchPwrFmt3Siz = 
           wrSmDfltPucchPwrFmt3RntiSz;
        lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.pucchPwrFmt3aRnti = 
           wrSmDfltPucchPwrFmt3aRntiSt;
        lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.pucchPwrFmt3aSiz = 
           wrSmDfltPucchPwrFmt3aRntiSz;

        lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.puschPwrFmt3Rnti = 
           wrSmDfltPuschPwrFmt3RntiSt;
        lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.puschPwrFmt3Siz =  
           wrSmDfltPuschPwrFmt3RntiSz;
        lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.puschPwrFmt3aRnti = 
           wrSmDfltPuschPwrFmt3aRntiSt;
        lteeNodeBparams[cellCfgIdx].ltecellSchdPwrCfg.puschPwrFmt3aSiz = 
           wrSmDfltPuschPwrFmt3aRntiSz;

        lteeNodeBparams[cellCfgIdx].lteCQIPeriodicReportCfg.cqi_PUCCH_ResourceIdx = 
           wrSmDfltCqiPUCCHResIdx;
        lteeNodeBparams[cellCfgIdx].ltePdschCfgDedicated.pA[0] = wrSmDfltPdschPA;

        lteeNodeBparams[cellCfgIdx].lteRachCfgCommonParams.maxHARQMsg3 = 
           (U8)wrSmDfltMaxHARQMsg3Tx;
        lteeNodeBparams[cellCfgIdx].lteRachCfgCommonParams.ltePowerRamping.initRcvdTrgtPwr = 
           wrSmDfltPreambleInitRecvdTgtPwr;
        lteeNodeBparams[cellCfgIdx].lteRachCfgCommonParams.ltePowerRamping.powerRampingstep = 
           (U8)wrSmDfltPowerRampingStep;
        lteeNodeBparams[cellCfgIdx].lteRachCfgCommonParams.ltePreambleCfg.groupASize = 
           (U8)wrSmDflSizeOfRaPreamblesGroupA;
        lteeNodeBparams[cellCfgIdx].lteRachCfgCommonParams.ltePreambleCfg.numOfRAPreambles = 
           (U8)wrSmDfltNumberOfRaPreambles;
        lteeNodeBparams[cellCfgIdx].lteRachCfgCommonParams.ltePreambleCfg.msgSizeGroupA = 
           wrSmDfltMessageSizeGroupA;  
        lteeNodeBparams[cellCfgIdx].lteRachCfgCommonParams.ltePreambleCfg.pwrOffstGrpB = 
           wrSmDfltMessagePowerOffsetGroupB;
        lteeNodeBparams[cellCfgIdx].lteRachCfgCommonParams.lteRaSupervisionCfg.macContResTimer = 
           (U8)wrSmDfltMacContentResTmr;
        lteeNodeBparams[cellCfgIdx].lteRachCfgCommonParams.lteRaSupervisionCfg.preambleTransMax = 
           (U8)wrSmDfltPreambleTransMax;
        lteeNodeBparams[cellCfgIdx].lteRachCfgCommonParams.lteRaSupervisionCfg.rarWindowSize = 
           (U8)wrSmDfltRaRspWindowSize;

        lteeNodeBparams[cellCfgIdx].lteULPwrCtrlCommon.alpha = wrSmDfltULPwrCtrlAlpha;
        lteeNodeBparams[cellCfgIdx].lteULPwrCtrlCommon.deltaMsg3 = 
           (S8)wrSmDfltUlDeltaPreambleMsg3;
        lteeNodeBparams[cellCfgIdx].lteULPwrCtrlCommon.pNomialPucch = 
           (S8)wrSmDfltP0NominalPUCCH;
        lteeNodeBparams[cellCfgIdx].lteULPwrCtrlCommon.pNomialPusch = 
           (S8)wrSmDfltP0NominalPUSCH;
        lteeNodeBparams[cellCfgIdx].lteULPwrCtrlCommon.deltaFLst.deltaPucchFormat1 = 
           wrSmDfltDeltaFPUCCHFormat1;
        lteeNodeBparams[cellCfgIdx].lteULPwrCtrlCommon.deltaFLst.deltaPucchFormat1b = 
           wrSmDfltDeltaFPUCCHFormat1b;
        lteeNodeBparams[cellCfgIdx].lteULPwrCtrlCommon.deltaFLst.deltaPucchFormat2 = 
           wrSmDfltDeltaFPUCCHFormat2;
        lteeNodeBparams[cellCfgIdx].lteULPwrCtrlCommon.deltaFLst.deltaPucchFormat2a = 
           wrSmDfltDeltaFPUCCHFormat2a;
        lteeNodeBparams[cellCfgIdx].lteULPwrCtrlCommon.deltaFLst.deltaPucchFormat2b = 
           wrSmDfltDeltaFPUCCHFormat2b;

        lteeNodeBparams[cellCfgIdx].lteSRSCfgCommon.cSrs = (U8)wrSmDfltSrsBandwidthCfg;
        lteeNodeBparams[cellCfgIdx].lteSRSCfgCommon.simulAckNackSrs = 
           (U8)wrSmDfltAckNackSrsSimTrns;
        lteeNodeBparams[cellCfgIdx].lteSRSCfgCommon.srsMaxUpts = (U8)wrSmDfltSrsMaxUpPts;

        lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.deltaShift = wrSmDfltPUCCHDeltaShift;

        lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.plmnRatPriority[0].numberOfRats =
           wrSmDfltPlmnRatPriorList.numberOfRats;
        lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[0].\
           rsrvdFrOperUse = wrSmDfltCellRsrvdForOperUse;
        lteeNodeBparams[cellCfgIdx].lteFapControlParams.anrEpochPeriod = wrSmDfltEpocTmrVal;
        lteeNodeBparams[cellCfgIdx].lteFapControlParams.anrTricePeriod = 
           wrSmDfltTricePrdIntv;
        lteeNodeBparams[cellCfgIdx].ltePuschBasicCfgCommon.nSb = (U8)wrSmDfltNSB[cellCfgIdx];
        lteeNodeBparams[cellCfgIdx].ltePuschBasicCfgCommon.hoppingMode = 
           wrSmDfltHoppingMode[cellCfgIdx];
        lteeNodeBparams[cellCfgIdx].ltePuschBasicCfgCommon.hoppingOffset = 
           (U8)wrSmDfltPuschHoppingOff[cellCfgIdx];
        lteeNodeBparams[cellCfgIdx].ltePuschBasicCfgCommon.enable64QAM = 
           (Bool)wrSmDfltEnable64QAM[cellCfgIdx];
#ifdef LTE_ADV
        lteeNodeBparams[cellCfgIdx].caGenCfg.sCellDeActTmr   = wrSmDfltSCellDeActTmrVal;
#endif
        lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t300 = wrSmDfltTmrsAndConstsT300; 
        lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t301 = wrSmDfltTmrsAndConstsT301; 
        //suhas - not filled inwithout oam -lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t302 
        lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t310 = wrSmDfltTmrsAndConstsT310; 
        lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.n310 = wrSmDfltTmrsAndConstsN310; 
        lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t311 = wrSmDfltTmrsAndConstsT311; 
        lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.n311 = wrSmDfltTmrsAndConstsN311; 
        //suhas - not filled inwithout oam -lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t320; 
        /* ccpu00125578 T304 value set to ms500 so that
         * RRC Connection Reestablishment will be delayed during HO */
        lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.ccoT304 = 0x04; 
        lteeNodeBparams[cellCfgIdx].lteUeTimerConstants.t304 = 0x04; 
        lteeNodeBparams[cellCfgIdx].lteCellSib3CfgGrp.qHyst = wrSmDfltqHyst; 
        lteeNodeBparams[cellCfgIdx].lteCellSib3CfgGrp.sfMedium = wrSmDfltSfMed;
        lteeNodeBparams[cellCfgIdx].lteCellSib3CfgGrp.sfHigh = wrSmDfltSfHigh;
        lteeNodeBparams[cellCfgIdx].lteCellSib3CfgGrp.mobStateParams.tEvalulation = 
           wrSmDfltTEval;
        lteeNodeBparams[cellCfgIdx].lteCellSib3CfgGrp.mobStateParams.tHystNormal = 
           wrSmDfltTHyst;
        lteeNodeBparams[cellCfgIdx].lteCellSib3CfgGrp.mobStateParams.nCellChangeMedium = 
           (U16)wrSmDfltS3nCellChangeMedium;

        lteeNodeBparams[cellCfgIdx].lteCellSib3CfgGrp.mobStateParams.nCellChangeHigh = 
           (U16)wrSmDfltS3nCellChangeHigh;
        lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.cellBarred = 
           (Bool)wrSmDfltCellBarred;
        lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellSelectInfo.qRxLevMin = 
           (S8)wrSmDlftqRxLevMin;
        lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellSelectInfo.qRxLevMinOffset = 
           (U8)wrSmDfltqRxlevminoffset;
        lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.pMax = (S8)wrSmDfltPMax;
        lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForEmergency = 
           wrSmDfltACBarrNormal;
        lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringTime = 
           wrSmDfltacBarringTime;
        lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringTime = 
           wrSmDfltacBarringTime;
        lteeNodeBparams[cellCfgIdx].ltePdschCfgCommon.pB[0] = (Bool)wrSmDfltPDSCHCfgPB;
        lteeNodeBparams[cellCfgIdx].ltePdschCfgCommon.referenceSignalPwr[0] = 
           wrSmDfltRefSignalPower;
        lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOData.acBarringFactor = 
           wrSmDfltacBarringFactor;
        lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForMOSignal.acBarringFactor = 
           wrSmDfltacBarringFactor;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA1EvtRptCfg[0].threshold_RSRQ = 
           wrSmDfltThresRSRQ1;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA1EvtRptCfg[0].triggerQty = 
           wrSmDfltTrigQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA1EvtRptCfg[0].reportQty = 
           wrSmDfltRptQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA1EvtRptCfg[0].maxRptCells = 
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA1EvtRptCfg[0].reportInterval = 
           wrSmDfltRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA1EvtRptCfg[0].reportAmount = 
           wrSmDfltRptAmount;

        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA2EvtRptCfg[0].threshold_RSRQ = 
           wrSmDfltThresRSRQ1;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA2EvtRptCfg[0].triggerQty = 
           wrSmDfltTrigQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA2EvtRptCfg[0].reportQty = 
           wrSmDfltRptQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA2EvtRptCfg[0].maxRptCells = 
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA2EvtRptCfg[0].reportInterval = 
           wrSmDfltRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA2EvtRptCfg[0].reportAmount = 
           wrSmDfltRptAmount;

        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO].triggerQty = 
           wrSmDfltTrigQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO].reportQty = 
           wrSmDfltRptQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO].maxRptCells = 
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO].reportInterval = 
           wrSmDfltRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_HO].reportAmount = 
           wrSmDfltRptAmount;


        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTER_FREQ_HO_RSRP].triggerQty = 
           wrSmDfltTrigQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTER_FREQ_HO_RSRP].reportQty = 
           wrSmDfltRptQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTER_FREQ_HO_RSRP].maxRptCells = 
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTER_FREQ_HO_RSRP].reportInterval =
           wrSmDfltRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTER_FREQ_HO_RSRP].reportAmount =
           wrSmDfltMaxRptCells;


        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_ANR].triggerQty = 
           wrSmDfltTrigQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_ANR].reportQty = 
           wrSmDfltRptQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_ANR].maxRptCells = 
           wrSmDfltMaxRptCells;  
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_ANR].reportInterval = 
           wrSmDfltRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA3Cfg[MSM_MEAS_EVENTA3_INTRA_FREQ_ANR].reportAmount = 
           wrSmDfltMaxRptCells;

#ifdef LTE_ADV
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA4EvtRptCfg[MSM_MEAS_EVENTA4_SCELL_ADD].threshold_RSRQ = 
           wrSmDfltThresRSRQ1;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA4EvtRptCfg[MSM_MEAS_EVENTA4_SCELL_ADD].triggerQty = 
           wrSmDfltTrigQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA4EvtRptCfg[MSM_MEAS_EVENTA4_SCELL_ADD].reportQty = 
           wrSmDfltRptQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA4EvtRptCfg[MSM_MEAS_EVENTA4_SCELL_ADD].maxRptCells = 
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA4EvtRptCfg[MSM_MEAS_EVENTA4_SCELL_ADD].reportInterval = 
           wrSmDfltRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measA4EvtRptCfg[MSM_MEAS_EVENTA4_SCELL_ADD].reportAmount = 
           wrSmDfltRptAmount;
#endif

        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO].triggerQty = 
           wrSmDfltTrigQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO].reportQty = 
           wrSmDfltRptQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO].maxRptCells = 
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO].reportInterval = 
           wrSmDfltRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTRA_FREQ_HO].reportAmount = 
           wrSmDfltMaxRptCells;


        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_HO_RSRP].triggerQty = 
           wrSmDfltTrigQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_HO_RSRP].reportQty = 
           wrSmDfltRptQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_HO_RSRP].maxRptCells = 
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_HO_RSRP].reportInterval = 
           wrSmDfltRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp\
           .measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_HO_RSRP].reportAmount = 
           wrSmDfltMaxRptCells;


        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_ANR].triggerQty = 
           wrSmDfltTrigQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_ANR].reportQty = 
           wrSmDfltRptQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_ANR].maxRptCells = 
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_ANR].reportInterval = 
           wrSmDfltRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEvtA5Cfg[MSM_MEAS_EVENTA5_INTER_FREQ_ANR].reportAmount = 
           wrSmDfltMaxRptCells;


        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEutraPeridRptCfg[MSM_MEAS_EUTRA_PERIODIC_REPORT_STRNG_CELLS].\
           triggerQty = wrSmDfltTrigQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEutraPeridRptCfg[MSM_MEAS_EUTRA_PERIODIC_REPORT_STRNG_CELLS].\
           reportQty = wrSmDfltRptQty;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEutraPeridRptCfg[MSM_MEAS_EUTRA_PERIODIC_REPORT_STRNG_CELLS].\
           maxRptCells = wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEutraPeridRptCfg[MSM_MEAS_EUTRA_PERIODIC_REPORT_STRNG_CELLS].\
           reportInterval = wrSmDfltRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measEutraPeridRptCfg[MSM_MEAS_EUTRA_PERIODIC_REPORT_STRNG_CELLS].\
           /*reportAmount = wrSmDfltMaxRptCells;*/
           reportAmount = wrSmDfltRptAmount;


        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_HO].maxReportCell = 
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_HO].reportAmount = 
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_HO].reportInterval = 
           wrSmDfltRptInterval;

        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_REDIR].maxReportCell = 
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_REDIR].reportAmount = 
           wrSmDfltRptAmount;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measUtraEventB2RptCfg[WR_MEAS_UTRA_EVENTB2_REDIR].reportInterval = 
           wrSmDfltRptInterval;

        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_REDIR].b2Threshold1RSRQ = \
           wrSmDfltGeranB2Thres1RSRQ;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_REDIR].maxReportCell = \
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_REDIR].reportAmount = \
           wrSmDfltRptAmount;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_REDIR].reportInterval = \
           wrSmDfltRptInterval;

        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_HO].b2Threshold1RSRQ = \
           wrSmDfltGeranB2Thres1RSRQ;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_HO].maxReportCell = \
           wrSmDfltMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_HO].reportAmount = \
           wrSmDfltRptAmount;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measGeranEventB2RptCfg[WR_MEAS_GERAN_EVENTB2_INTER_RAT_HO].reportInterval = \
           wrSmDfltRptInterval;

        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measGERANPeridRptCfg[0].maxRptCells = 
           wrSmDfltGeranMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measGERANPeridRptCfg[0].reportAmount = 
           wrSmDfltGeranRptAmt;

        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measUtraPeriodRptCfg[MSM_MEAS_UTRA_PRDRPT_STRGCELLS_CSFB].maxReportCell = 
           wrSmDfltUtraMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measUtraPeriodRptCfg[MSM_MEAS_UTRA_PRDRPT_STRGCELLS_CSFB].reportInterval = 
           wrSmDfltUtraRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measUtraPeriodRptCfg[MSM_MEAS_UTRA_PRDRPT_STRGCELLS_CSFB].reportAmount = 0;


        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measUtraPeriodRptCfg[WR_MEAS_UTRA_PRDRPT_STRGCELLS_ANR].maxReportCell = 
           wrSmDfltUtraMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measUtraPeriodRptCfg[WR_MEAS_UTRA_PRDRPT_STRGCELLS_ANR].reportInterval = 
           wrSmDfltUtraRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.\
           measUtraPeriodRptCfg[WR_MEAS_UTRA_PRDRPT_STRGCELLS_ANR].reportAmount = 0;


        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measCDMA1xPeridRptCfg[0].maxReportCell = 
           wrSmDfltCdmaMaxRptCells;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measCDMA1xPeridRptCfg[0].reportInterval = 
           wrSmDfltCdmaRptInterval;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measCDMA1xPeridRptCfg[0].reportAmount = 
           wrSmDfltCdmaRptAmount;

        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measSpeedCfg.timeToTriggerSfMedium = 
           wrSmDfltTimeToTrigSfMedium;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measSpeedCfg.timeToTriggerSfHigh = 
           wrSmDfltTimeToTrigSfHigh;

        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.rsrpFltrCoeff = 
           wrSmDfltRsrpFltrCoeff;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.rsrqFltrCoeff = 
           wrSmDfltRsrqFltrCoeff;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.measQtyCDMA2k = 
           wrSmDfltMeasQtyCDMA2k;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.measQtyUtraTdd = 
           (U8)wrSmDfltMeasQtyUtraTdd;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.fltrCoeffGERAN = 
           (U8)wrSmDfltGeranFltrCoeff;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.ecnoFltrCoeff = 
           wrSmDfltEcnoFltrCoeff;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.measQtyUtraFdd = 
           (U8)wrSmDfltMeasQtyUtraFdd;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.qtyCfg.filterCoefficient2FDDr10 = 
           wrSmDfltEcnoFltrCoeff;
        lteeNodeBparams[cellCfgIdx].lteCellMeasCfgGrp.measGap.gapPatternForInterRAT = 
           wrSmDfltGapPatForInterRAT;
        lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.nCSAN = 
           wrSmDfltPUCCHnCSAN[cellCfgIdx];
        lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.nRBCqi = 
           wrSmDfltPUCCHnRBCQI[cellCfgIdx];
        lteeNodeBparams[cellCfgIdx].lteAcBarringInfo.acBarringForEmergency = 
           wrSmDfltACBarrNormal;

        lteeNodeBparams[cellCfgIdx].lteRrmTddParam.simulAckNackEnb = wrSmDfltSimultAckNackAndCQI;


        lteeNodeBparams[cellCfgIdx].lteCellSib6CfgGrp.tReselection = wrSmDfltReslct;
        lteeNodeBparams[cellCfgIdx].lteCellSib6CfgGrp.tReselectionSfMedium = 
           wrSmDfltReslctSfMed;
        lteeNodeBparams[cellCfgIdx].lteCellSib6CfgGrp.tReselectionSfHigh = 
           wrSmDfltReslctSfHigh;
        lteeNodeBparams[cellCfgIdx].sib7CfgGrp.tReselectionGERAN = 
           wrSmDfltGerantReselection;
        lteeNodeBparams[cellCfgIdx].sib7CfgGrp.pres_SpeedStateScaleFactors = PRSNT_NODEF;
        lteeNodeBparams[cellCfgIdx].sib7CfgGrp.tReselectionGERANSFMedium = LWR_O_DOT_5;
        lteeNodeBparams[cellCfgIdx].sib7CfgGrp.tReselectionGERANSFHigh = LWR_O_DOT_5;
        /*multiCell*/
        lteeNodeBparams[cellCfgIdx].lteMAC_SCH_Config.maxHARQ_Tx = wrSmDfltMaxUlHqTx;
        lteeNodeBparams[cellCfgIdx].lteMAC_SCH_Config.periodicBSR_Timer = 
           wrSmDfltMacCfgPeriodicBSRTimer;
        lteeNodeBparams[cellCfgIdx].lteMAC_SCH_Config.retxBSR_Timer = wrSmDfltMacCfgRetxBSRTimer;
        lteeNodeBparams[cellCfgIdx].lteMAC_SCH_Config.ttiBundling = wrSmDfltMacCfgTtiBundling;
        lteeNodeBparams[cellCfgIdx].lteCQIPeriodicReportCfg.cqi_PUCCH_ResourceIdx = 
           wrSmDfltSrPUCCHResIdx;

        msmSrbPolicy = &(lteeNodeBparams[cellCfgIdx].lteRabPolicyCfgGrp.srbPolicy[idx]);
        for(idx = 0; idx < (LWR_MAX_SRBS-1); idx++)
        {
           msmSrbPolicy = &(lteeNodeBparams[cellCfgIdx].lteRabPolicyCfgGrp.srbPolicy[idx]);
           msmSrbPolicy->rlcInfo.tpRetransmit = wrSmDfltSrbPollRetrans;
           msmSrbPolicy->rlcInfo.pollPdu = wrSmDfltSrbPollPdu; 
           msmSrbPolicy->rlcInfo.pollByte = wrSmDfltSrbPollByte;
           msmSrbPolicy->rlcInfo.maxRetransThresh = wrSmDfltSrbMaxReTxThresh;
           msmSrbPolicy->rlcInfo.timerReordering = wrSmDfltDlSrbtReordring;
           msmSrbPolicy->rlcInfo.timerStatusProhibit = wrSmDfltSrbTStatProhibit;
        }

        lteeNodeBparams[cellCfgIdx].csfbCfgGrp.marketId = wrSmDfltCdmaMktId;
        lteeNodeBparams[cellCfgIdx].csfbCfgGrp.switchNum = wrSmDfltCdmaSwitchNum;
        lteeNodeBparams[cellCfgIdx].csfbCfgGrp.sectorNum = wrSmDfltCdmaSectorNum;
        
        wrSmDfltCellType = LWR_1XRTT;

        mobParams = &(lteeNodeBparams[cellCfgIdx].cdmaMobilityParam);
        mobParams->sidIncl = wrSmDfltCdma1xSidIncl; 
        mobParams->sid = wrSmDfltCdma1xSid;              
        mobParams->nidIncl = wrSmDfltCdma1xNidIncl;
        mobParams->nid = wrSmDfltCdma1xNid;
        mobParams->multSidsIncl = wrSmDfltCdma1xMultSidsIncl;
        mobParams->multSids = wrSmDfltCdma1xMultSids;         
        mobParams->multNidsIncl = wrSmDfltCdma1xMultNidsIncl;
        mobParams->multNids = wrSmDfltCdma1xMultNids;
        mobParams->regZoneIncl = wrSmDfltCdma1xRegZoneIncl;
        mobParams->regZone = wrSmDfltCdma1xRegZone;
        mobParams->totalZonesIncl = wrSmDfltCdma1xTotalZonesIncl;
        mobParams->totalZones = wrSmDfltCdma1xTotalZones;
        mobParams->zoneTimerIncl = wrSmDfltCdma1xZoneTimerIncl;
        mobParams->zoneTimer = wrSmDfltCdma1xZoneTimer;
        mobParams->pktZoneIdIncl = wrSmDfltCdma1xPktZoneIdIncl;
        mobParams->pktZoneId = wrSmDfltCdma1xPktZoneId;
        mobParams->pzIdHysParamIncl = wrSmDfltCdma1xPzIdHysParamIncl;
        mobParams->pzHystEnabled = wrSmDfltCdma1xPzHystEnabled;
        mobParams->pzHystInfoIncl = wrSmDfltCdma1xPzHystInfoIncl;
        mobParams->pzHystListLen = wrSmDfltCdma1xPzHystListLen;
        mobParams->pzHystActTimer = wrSmDfltCdma1xPzHystActTimer;
        mobParams->pzHystTimerMul = wrSmDfltCdma1xPzHystTimerMul;
        mobParams->pzHystTimerExp = wrSmDfltCdma1xPzHystTimerExp; 
        mobParams->pRevIncl = wrSmDfltCdma1xPRevIncl;
        mobParams->pRev = wrSmDfltCdma1xPRev;
        mobParams->minPRevIncl = wrSmDfltCdma1xMinPRevIncl;
        mobParams->minPRev = wrSmDfltCdma1xMinPRev;
        mobParams->negSlotCycIndxSupIncl = wrSmDfltCdma1xNegSlotCycIndxSupIncl;
        mobParams->negSlotCycIndxSup = wrSmDfltCdma1xNegSlotCycIndxSup;
        mobParams->encModeIncl = wrSmDfltCdma1xEncModeIncl;
        mobParams->encMode = wrSmDfltCdma1xEncMode;
        mobParams->encSupIncl = wrSmDfltCdma1xEncSupIncl;
        mobParams->encSup = wrSmDfltCdma1xEncSup;
        mobParams->sigEncSupIncl = wrSmDfltCdma1xSigEncSupIncl;
        mobParams->sigEncSup = wrSmDfltCdma1xSigEncSup;
        mobParams->msgIntSupIncl = wrSmDfltCdma1xMsgIntSupIncl;
        mobParams->msgIntSup = wrSmDfltCdma1xMsgIntSup;
        mobParams->sigIntSupINCLIncl = wrSmDfltCdma1xSigIntSupINCLIncl;
        mobParams->sigIntSupINCL = wrSmDfltCdma1xSigIntSupINCL;
        mobParams->sigIntSupIncl = wrSmDfltCdma1xSigIntSupIncl;
        mobParams->sigIntSup = wrSmDfltCdma1xSigIntSup;
        mobParams->authIncl = wrSmDfltCdma1xAuthIncl;
        mobParams->auth = wrSmDfltCdma1xAuth;
        mobParams->maxNumAltoSoIncl = wrSmDfltCdma1xMaxNumAltoSoIncl;
        mobParams->maxNumAltoSo = wrSmDfltCdma1xMaxNumAltoSo;
        mobParams->useSyncIdIncl = wrSmDfltCdma1xUseSyncIdIncl;
        mobParams->useSyncId = wrSmDfltCdma1xUseSyncId;
        mobParams->msInitPosLocSupIndIncl = wrSmDfltCdma1xMsInitPosLocSupIndIncl; 
        mobParams->msInitPosLocSupInd = wrSmDfltCdma1xMsInitPosLocSupInd;
        mobParams->mobQosIncl = wrSmDfltCdma1xMobQosIncl;
        mobParams->mobQos = wrSmDfltCdma1xMobQos;
        mobParams->bandClsInfoReqIncl = wrSmDfltCdma1xBandClsInfoReqIncl;
        mobParams->bandClsInfoReq = wrSmDfltCdma1xBandClsInfoReq;
        mobParams->bandClsIncl = wrSmDfltCdma1xBandClsIncl;
        mobParams->bandCls = wrSmDfltCdma1xBandCls;
        mobParams->bypassRegIndIncl = wrSmDfltCdma1xBypassRegIndIncl;
        mobParams->bypassRegInd = wrSmDfltCdma1xBypassRegInd;
        mobParams->altBandClsIncl = wrSmDfltCdma1xAltBandClsIncl;
        mobParams->altBandCls = wrSmDfltCdma1xAltBandCls;
        mobParams->maxAddServInstIncl = wrSmDfltCdma1xMaxAddServInstIncl;
        mobParams->maxAddServInst = wrSmDfltCdma1xMaxAddServInst;
        mobParams->homeRegIncl = wrSmDfltCdma1xHomeRegIncl;
        mobParams->homeReg = wrSmDfltCdma1xHomeReg;
        mobParams->forSidRegIncl = wrSmDfltCdma1xForSidRegIncl;
        mobParams->forSidReg = wrSmDfltCdma1xForSidReg;
        mobParams->forNidRegIncl = wrSmDfltCdma1xForNidRegIncl;
        mobParams->forNidReg = wrSmDfltCdma1xForNidReg;
        mobParams->powerUpRegIncl = wrSmDfltCdma1xPowerUpRegIncl;
        mobParams->powerUpReg = wrSmDfltCdma1xPowerUpReg;
        mobParams->powerDownRegIncl = wrSmDfltCdma1xPowerDownRegIncl;
        mobParams->powerDownReg = wrSmDfltCdma1xPowerDownReg;
        mobParams->parmRegIncl = wrSmDfltCdma1xParmRegIncl;
        mobParams->parmReg = wrSmDfltCdma1xParmReg;
        mobParams->regPrdIncl = wrSmDfltCdma1xRegPrdIncl;
        mobParams->regPrd = wrSmDfltCdma1xRegPrd;
        mobParams->regDistIncl = wrSmDfltCdma1xRegDistIncl;
        mobParams->regDist = wrSmDfltCdma1xRegDist;
        mobParams->prefMsIdTypeIncl = wrSmDfltCdma1xPrefMsIdTypeIncl;
        mobParams->prefMsIdType = wrSmDfltCdma1xPrefMsIdType;
        mobParams->extPrefMsIdTypeIncl = wrSmDfltCdma1xExtPrefMsIdTypeIncl;
        mobParams->extPrefMsIdType = wrSmDfltCdma1xExtPrefMsIdType;
        mobParams->meIdReqdIncl = wrSmDfltCdma1xMeIdReqdIncl;
        mobParams->meIdReqd = wrSmDfltCdma1xMeIdReqd;
        mobParams->mccIncl = wrSmDfltCdma1xMccIncl;
        mobParams->mcc = wrSmDfltCdma1xMcc;
        mobParams->imsi1112Incl = wrSmDfltCdma1xImsi1112Incl;
        mobParams->imsi1112 = wrSmDfltCdma1xImsi1112;
        mobParams->imsiTSupIncl = wrSmDfltCdma1xImsiTSupIncl;
        mobParams->imsiTSup = wrSmDfltCdma1xImsiTSup;
        mobParams->recntMsgIndIncl = wrSmDfltCdma1xRecntMsgIndIncl;
        mobParams->recntMsgInd = wrSmDfltCdma1xRecntMsgInd;
        mobParams->rerModeSupIncl = wrSmDfltCdma1xRerModeSupIncl;
        mobParams->rerModeSup = wrSmDfltCdma1xRerModeSup;
        mobParams->tzkModeSupIncl = wrSmDfltCdma1xTzkModeSupIncl;
        mobParams->tzkModeSup = wrSmDfltCdma1xTzkModeSup;
        mobParams->tzkIdIncl = wrSmDfltCdma1xTzkIdIncl;
        mobParams->tzkId = wrSmDfltCdma1xTzkId;
        mobParams->pilRepIncl = wrSmDfltCdma1xPilRepIncl;
        mobParams->pilRep = wrSmDfltCdma1xPilRep;
        mobParams->sdbSupIncl = wrSmDfltCdma1xSdbSupIncl;
        mobParams->sdbSup = wrSmDfltCdma1xSdbSup;
        mobParams->autoFcsoAllIncl = wrSmDfltCdma1xAutoFcsoAllIncl;
        mobParams->autoFcsoAll = wrSmDfltCdma1xAutoFcsoAll;
        mobParams->sdbInRcnmIncl = wrSmDfltCdma1xSdbInRcnmIncl;
        mobParams->sdbInRcnm = wrSmDfltCdma1xSdbInRcnm;
        mobParams->fpcFchIncl = wrSmDfltCdma1xFpcFchIncl;
        mobParams->fpcFchInitSetptRC3 = wrSmDfltCdma1xFpcFchInitSetptRC3;
        mobParams->fpcFchInitSetptRC4 = wrSmDfltCdma1xFpcFchInitSetptRC4;
        mobParams->fpcFchInitSetptRC5 = wrSmDfltCdma1xFpcFchInitSetptRC5;
        mobParams->fpcFchInitSetptRC11 = wrSmDfltCdma1xFpcFchInitSetptRC11;
        mobParams->fpcFchInitSetptRC12 = wrSmDfltCdma1xFpcFchInitSetptRC12;
        mobParams->tAddIncl = wrSmDfltCdma1xTAddIncl;
        mobParams->tAdd = wrSmDfltCdma1xTAdd;
        mobParams->pilotIncIncl = wrSmDfltCdma1xPilotInclIncl;
        mobParams->pilotInc = wrSmDfltCdma1xPilotInc;
        mobParams->randIncl = wrSmDfltCdma1xRandIncl;
        mobParams->rand = wrSmDfltCdma1xRand;
        mobParams->lpSecIncl = wrSmDfltCdma1xLpSecIncl;
        mobParams->lpSec = wrSmDfltCdma1xLpSec;
        mobParams->ltmOffIncl = wrSmDfltCdma1xLtmOffIncl;
        mobParams->ltmOff = wrSmDfltCdma1xLtmOff;
        mobParams->dayltIncl = wrSmDfltCdma1xDayltIncl;
        mobParams->daylt = wrSmDfltCdma1xDaylt;
        mobParams->gcsnaL2ActTimerIncl = wrSmDfltCdma1xGcsnaL2ActTimerIncl;
        mobParams->gcsnaL2ActTimer = wrSmDfltCdma1xGcsnaL2ActTimer;
        mobParams->gcsnaSeqCtxtTimerIncl = wrSmDfltCdma1xGcsnaSeqCtxtTimerIncl;
        mobParams->gcsnaSeqCtxtTimer = wrSmDfltCdma1xGcsnaSeqCtxtTimer;
	     mobParams->reserved = wrSmDfltCdma1xReserved;

	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdmaEutraTimeSync = \
             wrSmDfltSib8CdmaEutraTimeSync;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.tReselection = \
             wrSmDfltSib8TReselection;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.sfMedium = wrSmDfltSib8SfMedium;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.sfHigh = wrSmDfltSib8SfHigh;

	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.sid = \
            wrSmDfltCdma1xRegParamsSid;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.nid = \
            wrSmDfltCdma1xRegParamsNid;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.mulSID = \
            wrSmDfltCdma1xRegParamsMulSID;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.mulNID = \
            wrSmDfltCdma1xRegParamsMulNID;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.homeReg = \
            wrSmDfltCdma1xRegParamsHomeReg;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.\
            foreignSIDReg = wrSmDfltCdma1xRegParamsForeignSIDReg ;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.foreignNIDReg = \
            wrSmDfltCdma1xRegParamsForeignNIDReg;
          
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.paramReg = \
            wrSmDfltCdma1xRegParamsParamReg;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.powerUpReg = \
            wrSmDfltCdma1xRegParamsPowerUpReg;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.regPeriod = \
            wrSmDfltCdma1xRegParamsRegPeriod;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.regZone = \
            wrSmDfltCdma1xRegParamsRegZone;
        lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.totalZone = \
            wrSmDfltCdma1xRegParamsTotalZone;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.zoneTimer = \
            wrSmDfltCdma1xRegParamsZoneTimer;
	lteeNodeBparams[cellCfgIdx].cellSib8CfgGrp.cdma1xrttRegParams.powerDownReg = \
            wrSmDfltCdma1xRegParamsPowerDownReg;

	lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring0to9_r9 = \
            wrSmDfltCdma1xAcBarring0to9;
	lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring10_r9 = \
            wrSmDfltCdma1xAcBarring10;
	lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring11_r9 = \
            wrSmDfltCdma1xAcBarring11;
	lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring12_r9 = \
            wrSmDfltCdma1xAcBarring12;
	lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring13_r9 = \
            wrSmDfltCdma1xAcBarring13;
	lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring14_r9 = \
            wrSmDfltCdma1xAcBarring14;
	lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_Barring15_r9 = \
            wrSmDfltCdma1xAcBarring15;
	lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_BarringMsg_r9 = \
            wrSmDfltCdma1xAcBarringMsg;
	lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_BarringReg_r9 = \
            wrSmDfltCdma1xAcBarringReg;
	lteeNodeBparams[cellCfgIdx].barringConfig1xRTTCfg.ac_BarringEmg_r9 = \
            wrSmDfltCdma1xAcBarringEmg;

        for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numEutraFreq; \
              idx++)
        {
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              priority = wrSmDfltPriority;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              qRxLevMin = wrSmDfltQRxLevMin;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              pMax = wrSmDfltS3pMax;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              tReselection = wrSmDfltTReselection;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              tReselectionSFMed = wrSmDfltTReselectionSFMed;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              tReselectionSFHigh = wrSmDfltTReselectionSFHigh;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              sIntraSearch = wrSmDfltSIntraSearch;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              sNonIntraSearch = wrSmDfltSNonIntraSearch;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              servThresholdLow = wrSmDfltServThresholdLow;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              threshXHigh = wrSmDfltThreshXHigh;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              threshXLow =  wrSmDfltThreshXLow;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              measBandwidth = wrSmDfltMeasBandwidth;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              presAntennaPort1 =  wrSmDfltPresAntennaPort1;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              neighCellCfg =  wrSmDfltNeighCellCfg;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              qOffsetFreq = LWR_Q_OFFSET_RANGE_0;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              offsetFreq =  LWR_Q_OFFSET_RANGE_0;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              threshXHighQR9 = wrSmDfltThreshXHighQR9;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              threshXLowQR9 =  wrSmDfltThreshXLowQR9;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              reselecThreshQRel9 = wrSmDfltReselecThreshQRel9;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              sIntraSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              sIntraSearchRel9.sSearchQRel9 = wrSmDfltsSearchQRel9;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              sInterSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              sInterSearchRel9.sSearchQRel9 = wrSmDfltsSearchQRel9;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              pMaxUsage = wrSmDfltPMaxUsage;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              sfUsage = wrSmDfltSfUsage;
        }
       for(idx = 0;idx < lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numUtraFreq; idx++)
        {

           msmNeighFreqCfg->t.addNeighFreq[idx].utranFreq.priority = \
                            (U8)wrSmDfltUtraFaPriorInfo[idx].priority;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranFreq.threshXhigh = \
                            (U8)wrSmDfltUtraFaPriorInfo[idx].threshXhigh;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranFreq.threshXlow = \
                            (U8)wrSmDfltUtraFaPriorInfo[idx].threshXLow;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranFreq.qRxLevMin = \
                            (U8)wrSmDfltUtraFaPriorInfo[idx].qRxLevMin;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranFreq.pMaxUtra = \
                            (U8)wrSmDfltUtraFaPriorInfo[idx].pMaxUtra;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranFreq.pQualMin = \
                            (U8)wrSmDfltUtraFaPriorInfo[idx].qQualMin;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranFreq.offsetFreq = \
                            (U8)wrSmDfltUtraFaPriorInfo[idx].offsetFreq;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranFreq.duplexModeUtra = \
                            (U8)wrSmDfltUtraFaPriorInfo[idx].duplexType;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranFreq.threshXHighQR9 = \
                            (U8)wrSmDfltUtraFaPriorInfo[idx].threshXhighQRel9;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranFreq.threshXLowQR9 = \
                            (U8)wrSmDfltUtraFaPriorInfo[idx].threshXlowQRel9;
        }
        for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numUtraTddFreq; idx++)
        {

           msmNeighFreqCfg->t.addNeighFreq[idx].utranTddFreq.freqIndex = \
                            (U8)(wrSmDfltUtraTddFaPriorInfo[idx].faIndex);
           msmNeighFreqCfg->t.addNeighFreq[idx].utranTddFreq.priority = \
                            (U8)wrSmDfltUtraTddFaPriorInfo[idx].priority;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranTddFreq.threshXhigh = \
                            (U8)wrSmDfltUtraTddFaPriorInfo[idx].threshXhigh;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranTddFreq.threshXlow = \
                            (U8)wrSmDfltUtraTddFaPriorInfo[idx].threshXLow;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranTddFreq.qRxLevMin = \
                            (U8)wrSmDfltUtraTddFaPriorInfo[idx].qRxLevMin;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranTddFreq.pMaxUtra  = \
                            (U8)wrSmDfltUtraTddFaPriorInfo[idx].pMaxUtra;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranTddFreq.offsetFreq  = \
                            (U8)wrSmDfltUtraTddFaPriorInfo[idx].offsetFreq;
           msmNeighFreqCfg->t.addNeighFreq[idx].utranTddFreq.duplexModeUtra  = \
                            (U8)wrSmDfltUtraTddFaPriorInfo[idx].duplexType;
        }
        for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighCellCfg. \
              numUtraCells;idx++)
        {
           msmNeighCellCfg->t.neighAddCfg[idx].utranCell.nrIndex = \
             wrSmDfltExtUtraCell[cellCfgIdx][idx].relationIdx;
        }
        for(idx=0 ;idx<lteeNodeBparams[cellCfgIdx].cdmaBandClassParams.numBandClass;
              idx++)
        {
           lteeNodeBparams[cellCfgIdx].csfbCfgGrp.searchRate = \
              wrSmDfltCdma1xSrchWindSize;
           
        }
       for(idx=0; idx < lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numCdma1xFreq; \
         idx++)
       {
          lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t.addNeighFreq[idx]. \
             cdma1xFreq.searchRate = wrSmDfltCdma1xSrchWindSize;
       }
        for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighCellCfg. \
              numCdma1xCells;idx++)
        {
           msmNeighCellCfg->t.neighAddCfg[idx].cdma1xCell.systemType = \
                   wrSmDfltCdmaSystemType;
           msmNeighCellCfg->t.neighAddCfg[idx].cdma1xCell.channelNum = \
                   wrSmDfltCdmaChannelNum;
           msmNeighCellCfg->t.neighAddCfg[idx].cdma1xCell.cellType = LWR_1XRTT;
           msmNeighCellCfg->t.neighAddCfg[idx].cdma1xCell.tgtCell.marketId = \
                   wrSmDfltCdmaMktId;
           msmNeighCellCfg->t.neighAddCfg[idx].cdma1xCell.tgtCell.switchNum = \
                   wrSmDfltCdmaSwitchNum;
           msmNeighCellCfg->t.neighAddCfg[idx].cdma1xCell.tgtCell.sectorNum = \
                   wrSmDfltCdmaSectorNum;
           msmNeighCellCfg->t.neighAddCfg[idx].cdma1xCell.tgtCell.cellId = \
                   wrSmDfltCdmaCellId;

        }
        for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numGeranFreq; \
              idx++)
        {
           msmNeighFreqCfg->t.addNeighFreq[idx].geranFreq.qRxLevMin = \
                   wrSmDfltGeranqRxLevMin;
           msmNeighFreqCfg->t.addNeighFreq[idx].geranFreq.threshXHigh = \
                   wrSmDfltGeranthreshXHigh;
           msmNeighFreqCfg->t.addNeighFreq[idx].geranFreq.threshXLow = \
                   wrSmDfltGeranthreshXLow;
           msmNeighFreqCfg->t.addNeighFreq[idx].geranFreq.pMax = \
                   wrSmDfltGeranpMaxGeran;
        }
        for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighCellCfg.numEutraCells; idx++)
        {
           msmNeighCellCfg->t.neighAddCfg[idx].eutraCell.nrIndex  = \
                                                                    wrSmDfltNriIndex[idx];
           msmNeighCellCfg->t.neighAddCfg[idx].eutraCell.cio = wrSmDfltCIO;
           msmNeighCellCfg->t.neighAddCfg[idx].eutraCell.qoffset = wrSmDfltQoff;
           msmNeighCellCfg->t.neighAddCfg[idx].eutraCell.dlBw = wrSmDfltCellDlBW[idx];
        }
        lteeNodeBparams[cellCfgIdx].lteProcTimerCfg.s1ResetTmr = 
           wrSmDfltX2ResetRetryTmr; 
        lteeNodeBparams[cellCfgIdx].lteProcTimerCfg.x2ResetTmr = 
           wrSmDfltS1ResetRetryTmr;
        /* Scheduler Configuration */

        prachCfgInfo->prachFreqOffset = (Bool)wrSmDfltPrachFreqOffset;
        prachCfgInfo->zeroCorrelationZoneCfg = (Bool)wrSmDfltZeroCorrelZoneCfg;
        prachCfgInfo->highSpeedFlag = (Bool)wrSmDfltHighSpeedFlag;
        lteeNodeBparams[cellCfgIdx].lteEnbProtoCfg.sctpPortNumS1 = wrSmSctpPort;
        lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci1TmngReq = wrSmDfltQci1TmngReq;
        lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci2TmngReq = wrSmDfltQci2TmngReq;
        lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci3TmngReq = wrSmDfltQci3TmngReq;
        lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci4TmngReq = wrSmDfltQci4TmngReq;
        lteeNodeBparams[cellCfgIdx].lteSmCellCfg.rrmQci4TmngReqEnable = wrSmDfltQci4TmngReqEnable;
#else
        /*If a parameter is defined in wr_cfg.txt but not defined in OAM,
         *then add it here*/
        U8 idx = 0;
        MsmLteNeighFreqCfg *msmNeighFreqCfg = &lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg;
        for(idx = 0; idx < lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.numEutraFreq; \
              idx++)
        {
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              reselecThreshQRel9 = wrSmDfltReselecThreshQRel9;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              sIntraSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              sIntraSearchRel9.sSearchQRel9 = wrSmDfltsSearchQRel9;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              sInterSearchRel9.sSearchPRel9 = wrSmDfltsSearchPRel9;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              sInterSearchRel9.sSearchQRel9 = wrSmDfltsSearchQRel9;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              pMaxUsage = wrSmDfltPMaxUsage;
           msmNeighFreqCfg->t.addNeighFreq[idx].eutranFreq. \
              sfUsage = wrSmDfltSfUsage;
        }
        RLOG1(L_DEBUG,"smInitMsm:for OAM %d\n",cellCfgIdx);
#endif
        RETVOID;
     }

#ifdef __cplusplus
}
#endif /* __cplusplus */


/********************************************************************30**

           End of file:     fc_smm_msm_init.c@@/main/tenb_ca_rib_msm/14 - Fri Apr  1 19:40:55 2016

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
SID$        ---      Suhas         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
