


/**********************************************************************

    Name:   Test file for RRM Module

    Type:   CPP source file

    Desc:   Contains GT test cases for PRB report collector

    File:   test_rm_prbreportcollector.cpp

    Sid:      test_rm_prbbasedadmissioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:51:50 2016

    Prg:    sri

**********************************************************************/
#include <limits.h>
#include "gtest/gtest.h"

// File with class that is being tested
#include "test_rm.h"
#include "rm_prbbasedadmissioncontroller.h"
#include "rm_prbreportcollector.h"
#include "rgm.x"

/* The below lines need to be in some common place and not inside the test code
 * */
#ifdef _cplusplus
extern "C" {
   S16 tst();
}
#endif

// Fill pre-defined cell configuration array. Array elements are defined as below
// {bMaxAvgGbrPrbUsage,bCellId,bNumTxAnt,bDuplexMode,enCellDlBandWidth,
//  enUlDlConfig,utPrbRptInterval,utNumOfPrbRpts}
U32                  preDefCellConfigData[MAX_CELL_CONFIG_DATA][16]= {
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_25,LRM_UL_DL_CONFIG_2,5,5,2,2,1,1,20,20,30,40}, //0th
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_50,LRM_UL_DL_CONFIG_2,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_75,LRM_UL_DL_CONFIG_2,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_100,LRM_UL_DL_CONFIG_2,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_25,LRM_UL_DL_CONFIG_0,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_25,LRM_UL_DL_CONFIG_1,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_25,LRM_UL_DL_CONFIG_3,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_25,LRM_UL_DL_CONFIG_4,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_25,LRM_UL_DL_CONFIG_5,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_25,LRM_UL_DL_CONFIG_6,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_50,LRM_UL_DL_CONFIG_0,5,5,2,2,1,1,20,20,30,40}, //10th
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_50,LRM_UL_DL_CONFIG_1,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_50,LRM_UL_DL_CONFIG_2,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_50,LRM_UL_DL_CONFIG_3,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_50,LRM_UL_DL_CONFIG_4,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_50,LRM_UL_DL_CONFIG_5,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_50,LRM_UL_DL_CONFIG_6,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_75,LRM_UL_DL_CONFIG_0,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_75,LRM_UL_DL_CONFIG_1,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_75,LRM_UL_DL_CONFIG_2,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_75,LRM_UL_DL_CONFIG_3,5,5,2,2,1,1,20,20,30,40},//20th
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_75,LRM_UL_DL_CONFIG_4,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_75,LRM_UL_DL_CONFIG_5,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_75,LRM_UL_DL_CONFIG_6,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_100,LRM_UL_DL_CONFIG_0,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_100,LRM_UL_DL_CONFIG_1,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_100,LRM_UL_DL_CONFIG_2,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_100,LRM_UL_DL_CONFIG_3,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_100,LRM_UL_DL_CONFIG_4,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_100,LRM_UL_DL_CONFIG_5,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_TDD,LRM_BANDWIDTH_100,LRM_UL_DL_CONFIG_6,5,5,2,2,1,1,20,20,30,40}, //30th
   {50,1,2,RM_MODE_FDD,LRM_BANDWIDTH_25,0/*for FDD no config mode*/,5,5,2,2,1,1,20,20,30,40},//31th
   {50,1,2,RM_MODE_FDD,LRM_BANDWIDTH_50,0,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_FDD,LRM_BANDWIDTH_75,0,5,5,2,2,1,1,20,20,30,40},
   {50,1,2,RM_MODE_FDD,LRM_BANDWIDTH_100,0,5,5,2,2,1,1,20,20,30,40}
};


/* class used to test CL Module functions */
class CPRBBasedAdmissionControllerTest : public ::testing::Test
{
   public:
      CAdmissionController *admController;
      CUEManager* act32Sig16UeMgr;
   protected:
   virtual void SetUp()
   {
      PRNT_TEST_NAME();
      act32Sig16UeMgr = createUEManager(MAX_ACT_UES, MAX_SIG_UES, MAX_CSG_UES,
            MAX_NON_CSG_UES, (U32)MAX_EXT_UES);
      admController = createAdmissionController(64, 123, *act32Sig16UeMgr);

   }

   virtual void TearDown()
   {
      delete act32Sig16UeMgr;
      delete admController;
   }
};

CPRBBasedAdmissionController *getPrbAdmCntrlObj(LrmCellConfigData &cellConfigData)
{
   return new CPRBBasedAdmissionController(cellConfigData);
}

void freePrbAdmCntrlObj(CPRBBasedAdmissionController *objPrbAdmCntlr)
{
   delete objPrbAdmCntlr;
}

void fillCellConfigDataForSpecificConfig(LrmCellConfigData *stCellConfigData,
      U8 configType)
{
   U8 idx = 0;
   stCellConfigData->bMaxAvgGbrPrbUsage = preDefCellConfigData[configType-1][idx++];/*PRB usage in %*/
   stCellConfigData->bCellId = preDefCellConfigData[configType-1][idx++];
   stCellConfigData->bNumTxAnt = preDefCellConfigData[configType-1][idx++]; /*Currently testing for 2 Tx antennas*/
   stCellConfigData->bDuplexMode = preDefCellConfigData[configType-1][idx++];
   stCellConfigData->enCellDlBandWidth = (LrmCellBandwidth) preDefCellConfigData[configType-1][idx++];
   stCellConfigData->enUlDlConfig = (LrmUlDlConfig) preDefCellConfigData[configType-1][idx++]; /*TDD config mode 2*/
   stCellConfigData->utPrbRptInterval = preDefCellConfigData[configType-1][idx++];/* configred to SCH*/
   stCellConfigData->utNumOfPrbRpts = preDefCellConfigData[configType-1][idx++];/* used for sliding window*/
   stCellConfigData->bNumDlNewUesPerTti       = preDefCellConfigData[configType-1][idx++];
   stCellConfigData->bNumUlNewUesPerTti       = preDefCellConfigData[configType-1][idx++];
   stCellConfigData->bNumDlReTxUesPerTti      = preDefCellConfigData[configType-1][idx++];
   stCellConfigData->bNumUlReTxUesPerTti      = preDefCellConfigData[configType-1][idx++];
   stCellConfigData->bRbcQci1TmngReq          = preDefCellConfigData[configType-1][idx++];
   stCellConfigData->bRbcQci2TmngReq          = preDefCellConfigData[configType-1][idx++];
   stCellConfigData->bRbcQci3TmngReq          = preDefCellConfigData[configType-1][idx++];
   stCellConfigData->bRbcQci4TmngReq          = preDefCellConfigData[configType-1][idx];
   stCellConfigData->bRbcQci4TmngReqEnable    = TRUE;
   stCellConfigData->enSrPrdcty               = LRM_SR_PRDCTY_40;
   stCellConfigData->enCqiPrdcty              = LRM_CQI_PRDCTY_80;
   stCellConfigData->usNumSrResPerTti         = 6;
   stCellConfigData->enDsrTransMax            = DSR_TRANS_N32;
   stCellConfigData->bArpForEmergencyBearer   = 3;
   stCellConfigData->bMaxActiveUesServed      = MAX_ACT_UES;
   stCellConfigData->bMaxSigUesServed         = MAX_SIG_UES;
   stCellConfigData->usMaxCsgUes              = MAX_CSG_UES;
   stCellConfigData->usMaxNonCsgUes           = MAX_NON_CSG_UES;
   stCellConfigData->usMaxExtraUes            = (U32)MAX_EXT_UES;
   stCellConfigData->bNRbCqi                  = 6;
   stCellConfigData->usNumCqiResPerTti        = 6;

   stCellConfigData->stAcbInfo.bIsacBarringMoSig = 0 ;
   stCellConfigData->stAcbInfo.stAcBarringMoSig.enAcbTime = RM_ACB_TIME_S4;
   stCellConfigData->stAcbInfo.stAcBarringMoSig.enAcbFactor = RM_ACB_FACTOR_P95;
   stCellConfigData->stAcbInfo.stAcBarringMoSig.bAcbForSpac = 0xf0; /* barred all special access class */
   
   stCellConfigData->stAcbInfo.bIsacBarringMoData = 0 ;
   stCellConfigData->stAcbInfo.stAcBarringMoData.enAcbTime = RM_ACB_TIME_S4;
   stCellConfigData->stAcbInfo.stAcBarringMoData.enAcbFactor = RM_ACB_FACTOR_P95;
   stCellConfigData->stAcbInfo.stAcBarringMoData.bAcbForSpac = 0xf0; /* barred all special access class */
  
   stCellConfigData->stAcbInfo.bAcBarringEmergency = false; /* Not barred Emergecny calls */

   stCellConfigData->bNCsAn                   = 0;
   stCellConfigData->stSpsCellCfg.bIsSpsEnabled = false;
   stCellConfigData->stSpsCellCfg.usMaxDlSpsUePerTti = 1;
   stCellConfigData->stSpsCellCfg.usMaxUlSpsUePerTti = 1;
   stCellConfigData->flagDlfsScheduling       = 0;
   stCellConfigData->flagTransMode            = 0;
   stCellConfigData->bSimulCqiAckNack         = true;
   stCellConfigData->stRmCellDrxCfg.usLongDrxCycleGbr     = 0;
   stCellConfigData->stRmCellDrxCfg.usLongDrxCycleNonGbr  = 0;
   stCellConfigData->stRmCellDrxCfg.usDrxInactvTmr        = 0;
   stCellConfigData->stRmCellDrxCfg.bDrxRetxTmr           = 0;
   stCellConfigData->stRmCellDrxCfg.bIsDrxEnabled         = true;

   stCellConfigData->usN1Pucch = 0;
   stCellConfigData->bWaitTime = 1;
   stCellConfigData->usMaxUlBroadbandBw = 100;
   stCellConfigData->usMaxDlBroadbandBw = 100;
   stCellConfigData->bRcmAlgoType = 1;
   stCellConfigData->enSplSfCfg = LRM_SPL_SF_CONFIG_2;
   stCellConfigData->usAccessMode = 1;
   return;
}

//////////////////////////////////////////
// Test scenarios starting from here
// //////////////////////////////////////
TEST_F(CPRBBasedAdmissionControllerTest, handletrigger_start_prb_report)
{
   U8                             cellId = 1;
   S16                            ret;
   LrmCellConfigData              cellConfigData;
   CPRBBasedAdmissionController   *objPrbAdmCntlr;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   configRmuLSapCfg(0, 0); // SU ID, SP ID
   fillCellConfigDataForSpecificConfig(&cellConfigData, 24);

   objPrbAdmCntlr = getPrbAdmCntrlObj(cellConfigData);

   resetEnv();
   isStartPrbReportCfg = TRUE;

   ret = objPrbAdmCntlr->triggerPrbReportConfig(cellId, RGM_PRB_REPORT_START);
   EXPECT_EQ(ret, ROK);
   freePrbAdmCntrlObj(objPrbAdmCntlr);
}

TEST_F(CPRBBasedAdmissionControllerTest, handletrigger_stop_prb_report)
{
   U8                             cellId = 1;
   S16                            ret;
   LrmCellConfigData              cellConfigData;
   CPRBBasedAdmissionController   *objPrbAdmCntlr;

   configRmuLSapCfg(0, 0); // SU ID, SP ID
   fillCellConfigDataForSpecificConfig(&cellConfigData, 24);

   objPrbAdmCntlr = getPrbAdmCntrlObj(cellConfigData);

   resetEnv();
   isStopPrbReportCfg = TRUE;

   ret = objPrbAdmCntlr->triggerPrbReportConfig(cellId, RGM_PRB_REPORT_STOP);
   EXPECT_EQ(ret, ROK);
   freePrbAdmCntrlObj(objPrbAdmCntlr);
}

TEST_F(CPRBBasedAdmissionControllerTest, handle_ERAB_rejection_from_acceptList)
{
   S16                            ret;
   LrmCellConfigData              cellConfigData;
   CPRBBasedAdmissionController   *objPrbAdmCntlr;
   RmuErabConfigIe                stRabConfig;
   RrmRbcRspInfo                  erabRbcRspInfo;
   CERABInfoLst                   preEmptedERABs;
   RgmPrbRprtInd                  prbRprtInd;

   fillCellConfigDataForSpecificConfig(&cellConfigData, 24);
   cellConfigData.bMaxAvgGbrPrbUsage = 20;
   objPrbAdmCntlr = getPrbAdmCntrlObj(cellConfigData);

   memset(&prbRprtInd, 0, sizeof(RgmPrbRprtInd));
   prbRprtInd.bCellId = 1;
   prbRprtInd.bPrbUsageMask = 3;
   prbRprtInd.stQciPrbRpts[0].bQci = 1;
   prbRprtInd.stQciPrbRpts[0].bAvgPrbDlUsage = 16;
   prbRprtInd.stQciPrbRpts[0].bAvgPrbUlUsage = 16;
   CPRBReportCollector::getInstance().updateQCIsPRBReport(&prbRprtInd);

   fillErabConfigRequest(&stRabConfig, 3, 1, 0);
   stRabConfig.stErabAddModLst[0].stErabQosInfo.stErabGbrInfo.uiErabDlGbr = 20000;
   stRabConfig.stErabAddModLst[0].stErabQosInfo.stErabGbrInfo.uiErabUlGbr = 20000;
   stRabConfig.stErabAddModLst[1].stErabQosInfo.stErabGbrInfo.uiErabDlGbr = 2000000;
   stRabConfig.stErabAddModLst[1].stErabQosInfo.stErabGbrInfo.uiErabUlGbr = 2000000;
   stRabConfig.stErabAddModLst[2].stErabQosInfo.stErabGbrInfo.uiErabDlGbr = 20000;
   stRabConfig.stErabAddModLst[2].stErabQosInfo.stErabGbrInfo.uiErabUlGbr = 20000;

   memset(&erabRbcRspInfo, 0, sizeof(RrmRbcRspInfo));
   erabRbcRspInfo.usCRNTI = 61;
   erabRbcRspInfo.nErabsAccepted = 3;
   erabRbcRspInfo.eRabAcceptedLst[0].bERabId  = 6;
   erabRbcRspInfo.eRabAcceptedLst[1].bERabId  = 7;
   erabRbcRspInfo.eRabAcceptedLst[2].bERabId  = 8;

   ret = objPrbAdmCntlr->canRBsBeAdmitted(stRabConfig, erabRbcRspInfo);

   EXPECT_EQ(ret, true);
   EXPECT_EQ(erabRbcRspInfo.nErabsAccepted, 2);
   EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 1);
   EXPECT_EQ(erabRbcRspInfo.eRabAcceptedLst[0].bERabId, 6);
   EXPECT_EQ(erabRbcRspInfo.eRabAcceptedLst[1].bERabId, 8);
   EXPECT_EQ(erabRbcRspInfo.eRabRejectedLst[0].bERabId, 7);

   freePrbAdmCntrlObj(objPrbAdmCntlr);
}

#if 1
TEST_F(CPRBBasedAdmissionControllerTest, handle_cellConfig_invalid_buplexMode)
{
   LrmCellConfigData              stCellConfigData;
   CPRBBasedAdmissionController   *objPrbAdmCntlr;
   RgmPrbRprtInd                  prbRprtInd;

   fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);
   stCellConfigData.bDuplexMode  = (LrmCellBandwidth) RM_MODE_TDD;
   stCellConfigData.enUlDlConfig = (LrmUlDlConfig) LRM_UL_DL_CONFIG_MAX;

   objPrbAdmCntlr = getPrbAdmCntrlObj(stCellConfigData);

   memset(&prbRprtInd, 0, sizeof(RgmPrbRprtInd));
   prbRprtInd.bCellId = 1;
   prbRprtInd.bPrbUsageMask = 3;
   prbRprtInd.stQciPrbRpts[0].bQci = 1;
   prbRprtInd.stQciPrbRpts[0].bAvgPrbDlUsage = 0;
   prbRprtInd.stQciPrbRpts[0].bAvgPrbUlUsage = 0;
   CPRBReportCollector::getInstance().updateQCIsPRBReport(&prbRprtInd);

   U32 expDlPrbUsage = 0;
   EXPECT_EQ((CPRBReportCollector::getInstance()).getCurrentGbrDlPrbUsage(), 
         expDlPrbUsage);

   freePrbAdmCntrlObj(objPrbAdmCntlr);
}
#endif

TEST_F(CPRBBasedAdmissionControllerTest, handle_memAllocFailure)
{
   U8                             cellId = 1;
   S16                            ret;
   LrmCellConfigData              stCellConfigData;
   CPRBBasedAdmissionController   *objPrbAdmCntlr;

   fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);

   objPrbAdmCntlr = getPrbAdmCntrlObj(stCellConfigData);

   resetEnv();
   memAllocFail = TRUE;

   ret = objPrbAdmCntlr->triggerPrbReportConfig(cellId, RGM_PRB_REPORT_START);
   EXPECT_EQ(ret, RFAILED);
   freePrbAdmCntrlObj(objPrbAdmCntlr);
}

TEST_F(CPRBBasedAdmissionControllerTest, handle_invalid_erabId_canRbsBeAdmitted)
{
   LrmCellConfigData         stCellConfigData;
   RmuErabConfigIe           stRabConfig;
   RrmRbcRspInfo             erabRbcRspInfo;
   CERABInfoLst              preEmptedERABs;
   CPRBBasedAdmissionController   *objPrbAdmCntlr;

   fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);

   objPrbAdmCntlr = getPrbAdmCntrlObj(stCellConfigData);

   fillErabConfigRequest(&stRabConfig, 2, 1, 0);

   erabRbcRspInfo.usCRNTI = 61;
   erabRbcRspInfo.nErabsAccepted = 1;
   erabRbcRspInfo.eRabAcceptedLst[0].uiReqPrbForDl = 2;
   erabRbcRspInfo.eRabAcceptedLst[0].uiReqPrbForUl = 3;
   erabRbcRspInfo.eRabAcceptedLst[0].bERabId      = 15;

   objPrbAdmCntlr->canRBsBeAdmitted(stRabConfig, erabRbcRspInfo);

   freePrbAdmCntrlObj(objPrbAdmCntlr);
}

TEST_F(CPRBBasedAdmissionControllerTest, handle_invalid_erabId_canModifyRbsBeAdmitted)
{
   LrmCellConfigData         stCellConfigData;
   RmuErabConfigIe           stRabConfig;
   RrmRbcRspInfo             erabRbcRspInfo;
   CERABInfoLst              preEmptedERABs;
   CPRBBasedAdmissionController   *objPrbAdmCntlr;
   RmuUeAdmitReq  admitReq;
   RmuUeAdmitRsp  admitRsp;
   CUEContext     *pUE = NULL;

   admitRsp.bWaitTime =100;
   admitRsp.stStatusInfo.enStatus = RMU_FAILURE;

   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_SIGNALLING, 1, 1, 61);

   pUE = admController->handleUEAdmission(admitReq, &admitRsp);

   fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);

   objPrbAdmCntlr = getPrbAdmCntrlObj(stCellConfigData);

   fillErabConfigRequest(&stRabConfig, 2, 1, 0);

   erabRbcRspInfo.usCRNTI = 61;
   erabRbcRspInfo.nErabsAccepted = 1;
   erabRbcRspInfo.eRabAcceptedLst[0].uiReqPrbForDl = 2;
   erabRbcRspInfo.eRabAcceptedLst[0].uiReqPrbForUl = 3;
   erabRbcRspInfo.eRabAcceptedLst[0].bERabId      = 15;

   objPrbAdmCntlr->canModifyRBsBeAdmitted(pUE, stRabConfig, erabRbcRspInfo);

   freePrbAdmCntrlObj(objPrbAdmCntlr);
}


TEST_F(CPRBBasedAdmissionControllerTest, handle_invalid_erabId_UpdatePrbRejLst)
{
   LrmCellConfigData         stCellConfigData;
   RmuErabConfigIe           stRabConfig;
   RrmRbcRspInfo             erabRbcRspInfo;
   CERABInfoLst              preEmptedERABs;
   CPRBBasedAdmissionController   *objPrbAdmCntlr;

   fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);

   objPrbAdmCntlr = getPrbAdmCntrlObj(stCellConfigData);

   memset(&erabRbcRspInfo, 0, sizeof(erabRbcRspInfo));
   fillErabConfigRequest(&stRabConfig, 2, 1, 0);

   erabRbcRspInfo.nErabsRejected = 1;
   erabRbcRspInfo.eRabRejectedLst[0].bERabId = 15;

   objPrbAdmCntlr->updatePrbUsageForRejErabs(stRabConfig, erabRbcRspInfo);

   U32 expDlPrbUsage = 0;
   U32 expUlPrbUsage = 0;

   EXPECT_EQ(erabRbcRspInfo.eRabRejectedLst[0].uiReqPrbForDl, 
         expDlPrbUsage);
   EXPECT_EQ(erabRbcRspInfo.eRabRejectedLst[0].uiReqPrbForUl, 
         expUlPrbUsage);

   freePrbAdmCntrlObj(objPrbAdmCntlr);
}

TEST_F(CPRBBasedAdmissionControllerTest, handle_UpdatePrbRejLst)
{
   LrmCellConfigData         stCellConfigData;
   RmuErabConfigIe           stRabConfig;
   RrmRbcRspInfo             erabRbcRspInfo;
   CERABInfoLst              preEmptedERABs;
   CPRBBasedAdmissionController   *objPrbAdmCntlr;
   U32 erabId;

   fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);

   objPrbAdmCntlr = getPrbAdmCntrlObj(stCellConfigData);

   memset(&erabRbcRspInfo, 0, sizeof(erabRbcRspInfo));
   fillErabConfigRequest(&stRabConfig, 2, 1, 0);
   erabId = stRabConfig.stErabAddModLst[0].bErabId;

   erabRbcRspInfo.nErabsRejected = 1;
   erabRbcRspInfo.eRabRejectedLst[0].bERabId = erabId;

   objPrbAdmCntlr->updatePrbUsageForRejErabs(stRabConfig, erabRbcRspInfo);

   U32 expDlPrbUsage = 3;
   U32 expUlPrbUsage = 3;

   EXPECT_EQ(erabRbcRspInfo.eRabRejectedLst[0].uiReqPrbForDl, 
         expDlPrbUsage);
   EXPECT_EQ(erabRbcRspInfo.eRabRejectedLst[0].uiReqPrbForUl, 
         expUlPrbUsage);

   freePrbAdmCntrlObj(objPrbAdmCntlr);
}

/**********************************************************************
         End of file:     test_rm_prbbasedadmissioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:51:50 2016
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
*********************************************************************91*/
