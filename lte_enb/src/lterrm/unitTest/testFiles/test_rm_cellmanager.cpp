


/**********************************************************************

    Name:   Test file for RRM Module

    Type:   CPP source file

    Desc:   Contains GT test cases for PRB report collector

    File:   test_rm_prbreportcollector.cpp

    Sid:      test_rm_cellmanager.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:51:48 2016

    Prg:    sri

**********************************************************************/
#include <limits.h>
#include "gtest/gtest.h"

// File with class that is being tested
#include "test_rm.h"
#include "rm_cellmanager.h"
#include "rm_prbreportcollector.h"

/* The below lines need to be in some common place and not inside the test code
 * */
#ifdef _cplusplus
extern "C" {
   S16 tst();
}
#endif

bool isStartPrbReportCfg;
bool isStopPrbReportCfg;
bool isUeAdmitRspExpInfoSet;
bool isHoUeAdmitRspExpInfoSet;
bool isUeRecfgExpInfoSet;
bool isUeErabRelIndExpected;
bool isUeErabRelIndRcvd;
bool memAllocFail;
bool isUeRelIndRcvd;
bool isUeRelIndExpected;
bool isCellRecfgIndExpected;

UeAdmitRspExpInfo ueAdmitRspExp;
UeRecfgExpInfo ueRecfgExp;
UeHoAdmitRspExpInfo ueHoAdmitRspExp;
RmuUeRelInd   ueRelIndExp;
CellRecfgIndExpInfo cellRecfgIndExp;

CCellManager *getNewCellObj(LrmCellConfigData *stCellConfigData)
{
   return new CCellManager(stCellConfigData);
}

void freeCellManagerObj(CCellManager *pstCellManagerObj)
{
   delete pstCellManagerObj;
}

void resetEnv()
{
   isStartPrbReportCfg = FALSE;
   isStopPrbReportCfg = FALSE;
   isUeAdmitRspExpInfoSet = FALSE;
   isHoUeAdmitRspExpInfoSet = FALSE;
   isUeRecfgExpInfoSet = FALSE;
   isUeErabRelIndExpected = FALSE;
   isUeErabRelIndRcvd = FALSE;
   isUeRelIndExpected = FALSE;
   isUeRelIndRcvd = FALSE;
   isCellRecfgIndExpected = false;
   memset(&ueAdmitRspExp, 0, sizeof(UeAdmitRspExpInfo));
   memset(&ueRecfgExp, 0, sizeof(UeRecfgExpInfo));
   memset(&cellRecfgIndExp, 0, sizeof(CellRecfgIndExpInfo));
}

void createUeRecfgReq(RmuUeRecfgReq *ptrRecfgReq,
                    U32  uiTransId,
                    U8   bCellId,
                    U16  usCrnti,
                    U32  bRecfgBitMap,
                    bool isMember,
                    U16  newCrnti)
{
   if(NULL == ptrRecfgReq)
   {
      return;
   }

   ptrRecfgReq->bCellId = bCellId;
   ptrRecfgReq->uiTransId = uiTransId;
   ptrRecfgReq->usCrnti = usCrnti;
   ptrRecfgReq->isMember = isMember;
   ptrRecfgReq->bRecfgBitMap = bRecfgBitMap;

   if(bRecfgBitMap & RMU_RECFG_REQ_ERAB_CONFIG)
   {
      fillErabConfigRequest(&ptrRecfgReq->stErabConfInfo, 1, 0, 13);
   }

   if(bRecfgBitMap & RMU_RECFG_REQ_UE_CAP)
   {
      RmuEutraCapInfo *eutraCapInfo = &ptrRecfgReq->stUeCapInfo.stEutraCapInfo;
      eutraCapInfo->uiFeatureGrpIndicator = 0;
      eutraCapInfo->uiUeCategory = 0;
      eutraCapInfo->uiUeAccessStratumRls = 
         (RmuAccessStratumRls)RMU_ACCESS_STRATUM_REL9;
   }

   if(bRecfgBitMap & RMU_RECFG_REQ_NEW_CRNTI)
   {
      ptrRecfgReq->usUeNewCrnti = newCrnti;
   }

   return;
}

CCellManager* doCellConfigCellUp()
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);
   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
   return pstCellMngrObj;
}

void updatePrbRprt(CCellManager *cellMngr,
                   U32 prbUsgMask, 
                   U32 qci, 
                   U32 dl, 
                   U32 ul)
{
   RgmPrbRprtInd   prbRprtInd;
   memset(&prbRprtInd, 0, sizeof(RgmPrbRprtInd));
   prbRprtInd.bCellId = cellMngr->getCellID();
   prbRprtInd.bPrbUsageMask = prbUsgMask;
   prbRprtInd.stQciPrbRpts[0].bQci = qci;
   prbRprtInd.stQciPrbRpts[0].bAvgPrbDlUsage = dl;
   prbRprtInd.stQciPrbRpts[0].bAvgPrbUlUsage = ul;
   cellMngr->handlePrbRprt(&prbRprtInd);
}

/* Class: use CCellManagerTestStandAlone as unit test name (first argument in
 * TEST()), when you want a different configuration to be used for the 
 * test case you are writting. */
class CCellManagerTestStandAlone : public ::testing::Test
{
protected:
   virtual void SetUp()
   {
      PRNT_TEST_NAME();
   }

   virtual void TearDown()
   {
   }
};


/* Fixture class: use CCellManagerTest as unit test name (first argument in
 * TEST_F()), when common cell configuration can be used */
class CCellManagerTest : public ::testing::Test
{
public:
   CCellManager *pstCellMngrObj;
protected:
   virtual void SetUp()
   {
      PRNT_TEST_NAME();
      pstCellMngrObj = doCellConfigCellUp();
   }

   virtual void TearDown()
   {
      freeCellManagerObj(pstCellMngrObj);
   }
};

//////////////////////////////////////////
// Test scenarios starting from here
//////////////////////////////////////////
TEST(CCellManagerTestStandAlone, handleConfiguration)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;

   for(U32 idx = 1; idx < MAX_CELL_CONFIG_DATA; idx++)
   {
      fillCellConfigDataForSpecificConfig(&stCellConfigData, idx);
      pstCellMngrObj = getNewCellObj(&stCellConfigData);
      freeCellManagerObj(pstCellMngrObj);
   }
}

TEST_F(CCellManagerTest, handle_ERABSetupRequest)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
}

TEST_F(CCellManagerTest, handle_Handover_UEAdmitReq)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // Handover UE 2
   RmuUeHoReq ueHoReq;
   ueHoReq.bCellId = 1;
   ueHoReq.uiTransId = 1;
   ueHoReq.usCrnti = 96;
   ueHoReq.isEmrgncyBrersPsnt = FALSE;
   ueHoReq.isMember = TRUE;
   ueHoReq.enHoS1apCause = RMU_CAUSE_HANDOVER_DESIRABLE_RADIO_REASON;
   ueHoReq.enHoType = RMU_HO_TYPE_IntraLTE;
   ueHoReq.stUeCapInfo.stEutraCapInfo.uiFeatureGrpIndicator = 0;
   ueHoReq.stUeCapInfo.stEutraCapInfo.uiUeCategory = 0;
   ueHoReq.stUeCapInfo.stEutraCapInfo.uiUeAccessStratumRls = 
      (RmuAccessStratumRls)RMU_ACCESS_STRATUM_REL9;
   fillErabConfigRequest(&(ueHoReq.stErabConfInfo), 1, 1, 12);

   resetEnv();
   isHoUeAdmitRspExpInfoSet = TRUE;
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueHoAdmitRspExp.usCrnti = 96;
   ueHoAdmitRspExp.bNoErabsAdmitted = 1;
   ueHoAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;

   pstCellMngrObj->procUeHoReq(ueHoReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 96);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABSetup_SingleUeReject)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 2,4);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 51, 49);
   
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 2, 4);
   stUeRecfgReq.stErabConfInfo.enErabAction = RMU_MOD_ERAB;
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabGbrInfo.uiErabDlMbr = 400000 ;
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabGbrInfo.uiErabUlMbr = 400000 ;
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabGbrInfo.uiErabDlGbr = 400000 ;
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabGbrInfo.uiErabUlGbr = 400000 ;
   
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 1;
   ueRecfgExp.bNoErabsRejected = 1;
   ueRecfgExp.bNoErabsAccepted = 0;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;
   ueRecfgExp.stStatusInfo.enStatus = RMU_FAILURE;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
}

TEST_F(CCellManagerTest, handle_ERABSetup_SingleUe)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 2,11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 3,12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   updatePrbRprt(pstCellMngrObj, 3, 1, 49, 49);
   updatePrbRprt(pstCellMngrObj, 3, 2, 49, 49);
   
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 4,13);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 8;
 
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
}

TEST_F(CCellManagerTest, handle_ERABSetup_CsgUE_NonCsgPreemption)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABSetup_CsgUE_NonCsgNonVulnerable)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a non-vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABSetup_EmergencyARP_nonCsgVulnerable)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   // marking as non-CSG member
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   // setting emergency ARP value
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPrioLvl = 3;
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABSetup_EmergencyARP_nonCsgNonVulnerable)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a non vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   // setting emergency ARP value
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPrioLvl = 3;
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABSetup_EmergencyARP_CsgVulnerable)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   // marking as CSG member
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   // setting emergency ARP value
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPrioLvl = 3;
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABSetup_EmergencyARP_CsgNonVulnerable)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a non vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   // setting up a non-CSG member
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   // setting emergency ARP value
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPrioLvl = 3;
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABSetup_NonCsg_nonCsgVulnerable)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   // marking as non-CSG member
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABSetup_Reject_preemption_incapable)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   // marking as non-CSG member
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   // preemption incapable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 1;
   ueRecfgExp.bNoErabsRejected = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERAB_Setup_Release_Setup)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   U32 erabId = stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].bErabId;
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // send ERAB release indication for the UE 61 bearer
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   stUeRecfgReq.stErabConfInfo.enErabAction = RMU_DEL_ERAB;
   stUeRecfgReq.stErabConfInfo.usNoErabsToAddMod = 0;
   stUeRecfgReq.stErabConfInfo.bNoErabsToRel = 1;
   stUeRecfgReq.stErabConfInfo.stErabRelLst[0].enErabRelCause = RMU_CAUSE_UNSPECIFIED;
   stUeRecfgReq.stErabConfInfo.stErabRelLst[0].bErabId = erabId;
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 0, 0);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_triggerPrbReport)
{
   resetEnv();
   isStartPrbReportCfg = TRUE;
   pstCellMngrObj->triggerStartPrbUsageReport();

}

TEST_F(CCellManagerTest, handle_UE_membership_mod)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 2, 10);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE Context modification
   bRecfgBitMap = RMU_RECFG_REQ_CSG_MEMBERSHIP_MOD;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 8;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
#if 0
   prbRprtInd = (RgmPrbRprtInd*) malloc(sizeof(RgmPrbRprtInd));
   memset(prbRprtInd, 0, sizeof(RgmPrbRprtInd));
   prbRprtInd->bCellId = 1;
   prbRprtInd->bPrbUsageMask = 3;
   prbRprtInd->stQciPrbRpts[0].bAvgPrbDlUsage = 48;
   prbRprtInd->stQciPrbRpts[0].bAvgPrbUlUsage = 48;
   CPRBReportCollector::getInstance().updateQCIsPRBReport(prbRprtInd);

   // ERAB Setup
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   // setting emergency ARP value
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabArpInfo.bErabPrioLvl = 3;
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
#endif
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERAB_Setup_Modified)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // send ERAB release indication for the UE 61 bearer
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   stUeRecfgReq.stErabConfInfo.enErabAction = RMU_MOD_ERAB;
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERAB_Setup_MAX_RABNum)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 9, 1, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_FAILURE;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERAB_Modify_MAX_RABNum)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 9, 1, 0);
   stUeRecfgReq.stErabConfInfo.enErabAction = RMU_MOD_ERAB;
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_FAILURE;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERAB_Release_MAX_RABNum)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 9, 1, 0);
   stUeRecfgReq.stErabConfInfo.enErabAction = RMU_DEL_ERAB;
   stUeRecfgReq.stErabConfInfo.usNoErabsToAddMod = 0;
   stUeRecfgReq.stErabConfInfo.bNoErabsToRel = 9;
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_FAILURE;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ICS_multiBearer)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   // add another bearer in UE reconfiguration
   RmuErabConfigIe *stRabConfig = &(stUeRecfgReq.stErabConfInfo);
   U32 idx = 12;
   stRabConfig->stErabAddModLst[1].bErabId = stRabSetupConfig[idx].bErabId;
   RmuErabArpInfoIe *stArpInfo = &(stRabConfig->stErabAddModLst[1].stErabQosInfo.stErabArpInfo);
   RmuErabArpInfoIe *stArpInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabArpInfo);
   stArpInfo->bErabPrioLvl    = stArpInfoDB->bErabPrioLvl;
   stArpInfo->bErabPreemptCap = stArpInfoDB->bErabPreemptCap;
   stArpInfo->bErabPreemptVul = stArpInfoDB->bErabPreemptVul;

   RmuErabGbrInfoIe *stGbrInfo = &(stRabConfig->stErabAddModLst[1].stErabQosInfo.stErabGbrInfo);
   RmuErabGbrInfoIe *stGbrInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabGbrInfo);
   stGbrInfo->uiErabDlMbr     = stGbrInfoDB->uiErabDlMbr;
   stGbrInfo->uiErabUlMbr     = stGbrInfoDB->uiErabUlMbr;
   stGbrInfo->uiErabDlGbr     = stGbrInfoDB->uiErabDlGbr;
   stGbrInfo->uiErabUlGbr     = stGbrInfoDB->uiErabUlGbr;
   stRabConfig->stErabAddModLst[1].stErabQosInfo.bErabQCI = 1;
   stRabConfig->usNoErabsToAddMod++;

   resetEnv();
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 2;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ICS_multiBearer_rejection)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   // add another bearer in UE reconfiguration
   RmuErabConfigIe *stRabConfig = &(stUeRecfgReq.stErabConfInfo);
   U32 idx = 11;
   stRabConfig->stErabAddModLst[1].bErabId = stRabSetupConfig[idx].bErabId;
   RmuErabArpInfoIe *stArpInfo = &(stRabConfig->stErabAddModLst[1].stErabQosInfo.stErabArpInfo);
   RmuErabArpInfoIe *stArpInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabArpInfo);
   stArpInfo->bErabPrioLvl    = stArpInfoDB->bErabPrioLvl;
   stArpInfo->bErabPreemptCap = stArpInfoDB->bErabPreemptCap;
   stArpInfo->bErabPreemptVul = stArpInfoDB->bErabPreemptVul;

   RmuErabGbrInfoIe *stGbrInfo = &(stRabConfig->stErabAddModLst[1].stErabQosInfo.stErabGbrInfo);
   RmuErabGbrInfoIe *stGbrInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabGbrInfo);
   stGbrInfo->uiErabDlMbr     = stGbrInfoDB->uiErabDlMbr;
   stGbrInfo->uiErabUlMbr     = stGbrInfoDB->uiErabUlMbr;
   stGbrInfo->uiErabDlGbr     = stGbrInfoDB->uiErabDlGbr;
   stGbrInfo->uiErabUlGbr     = stGbrInfoDB->uiErabUlGbr;
   stRabConfig->stErabAddModLst[1].stErabQosInfo.bErabQCI = 1;
   stRabConfig->usNoErabsToAddMod++;

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.bNoErabsRejected = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_Handover_UEAdmitReq_rejection)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // Handover UE 2
   RmuUeHoReq ueHoReq;
   ueHoReq.bCellId = 1;
   ueHoReq.uiTransId = 1;
   ueHoReq.usCrnti = 96;
   ueHoReq.isEmrgncyBrersPsnt = FALSE;
   ueHoReq.isMember = TRUE;
   ueHoReq.enHoS1apCause = RMU_CAUSE_HANDOVER_DESIRABLE_RADIO_REASON;
   ueHoReq.enHoType = RMU_HO_TYPE_IntraLTE;
   ueHoReq.stUeCapInfo.stEutraCapInfo.uiFeatureGrpIndicator = 0;
   ueHoReq.stUeCapInfo.stEutraCapInfo.uiUeCategory = 0;
   ueHoReq.stUeCapInfo.stEutraCapInfo.uiUeAccessStratumRls = 
      (RmuAccessStratumRls)RMU_ACCESS_STRATUM_REL9;
   fillErabConfigRequest(&(ueHoReq.stErabConfInfo), 1, 0, 13);
   // add another bearer in UE admit request
   RmuErabConfigIe *stRabConfig = &(ueHoReq.stErabConfInfo);
   U32 idx = 11;
   stRabConfig->stErabAddModLst[1].bErabId = stRabSetupConfig[idx].bErabId;
   RmuErabArpInfoIe *stArpInfo = &(stRabConfig->stErabAddModLst[1].stErabQosInfo.stErabArpInfo);
   RmuErabArpInfoIe *stArpInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabArpInfo);
   stArpInfo->bErabPrioLvl    = stArpInfoDB->bErabPrioLvl;
   stArpInfo->bErabPreemptCap = stArpInfoDB->bErabPreemptCap;
   stArpInfo->bErabPreemptVul = stArpInfoDB->bErabPreemptVul;

   RmuErabGbrInfoIe *stGbrInfo = &(stRabConfig->stErabAddModLst[1].stErabQosInfo.stErabGbrInfo);
   RmuErabGbrInfoIe *stGbrInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabGbrInfo);
   stGbrInfo->uiErabDlMbr     = stGbrInfoDB->uiErabDlMbr;
   stGbrInfo->uiErabUlMbr     = stGbrInfoDB->uiErabUlMbr;
   stGbrInfo->uiErabDlGbr     = stGbrInfoDB->uiErabDlGbr;
   stGbrInfo->uiErabUlGbr     = stGbrInfoDB->uiErabUlGbr;
   stRabConfig->stErabAddModLst[1].stErabQosInfo.bErabQCI = 1;
   stRabConfig->usNoErabsToAddMod++;

   resetEnv();
   isHoUeAdmitRspExpInfoSet = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueHoAdmitRspExp.usCrnti = 96;
   ueHoAdmitRspExp.bNoErabsAdmitted = 1;
   ueHoAdmitRspExp.bNoErabsRejected = 1;
   ueHoAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;

   pstCellMngrObj->procUeHoReq(ueHoReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 96);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERAB_Modified_Rejection)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // send ERAB release indication for the UE 61 bearer
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   stUeRecfgReq.stErabConfInfo.enErabAction = RMU_MOD_ERAB;
   RmuErabConfigIe *stRabConfig = &(stUeRecfgReq.stErabConfInfo);
   RmuErabGbrInfoIe *stGbrInfo = &(stRabConfig->stErabAddModLst[0].stErabQosInfo.stErabGbrInfo);
   stGbrInfo->uiErabDlMbr     = 2000000;
   stGbrInfo->uiErabUlMbr     = 2000000;
   stGbrInfo->uiErabDlGbr     = 2000000;
   stGbrInfo->uiErabUlGbr     = 2000000;
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 1;
   ueRecfgExp.bNoErabsRejected = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_FAILURE;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABModifyRequest_for_GBR_increase_triggers_PreEmption)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);

   resetEnv();
   //isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);


   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);

   resetEnv();
 //  isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 4
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 64, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);

   resetEnv();

   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // ERAB Modify
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 14, RMU_MOD_ERAB);

   resetEnv();
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);


   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
}

TEST_F(CCellManagerTest, handle_ERABModifyRequest_for_GBR_decrease)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 0, 0);


   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 64, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 15);

   resetEnv();

   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 0, 0);

   // ERAB Modify
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 14, RMU_MOD_ERAB);
   
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabGbrInfo.uiErabDlMbr = 3146752;
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabGbrInfo.uiErabUlMbr = 2098176;
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabGbrInfo.uiErabDlGbr = 3146752;
   stUeRecfgReq.stErabConfInfo.stErabAddModLst[0].stErabQosInfo.stErabGbrInfo.uiErabUlGbr = 2098176;

   resetEnv();
   isUeErabRelIndExpected = FALSE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
}


TEST_F(CCellManagerTest, handle_ERABModifyRequest_for_Non_GBR_to_GBR_is_rejected)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 4
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 64, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);

   resetEnv();

   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // ERAB Modify
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 13, RMU_MOD_ERAB);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 1;
   ueRecfgExp.bNoErabsAccepted = 0;
   ueRecfgExp.bNoErabsRejected = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);


   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
}

TEST_F(CCellManagerTest, handle_ERABModifyRequest_for_to_change_qci_to_1_When_max_qci1_reached_is_rejected)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);


   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 4
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 64, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);

   resetEnv();

   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 5
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 65, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 65, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 65;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 65, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 2, 11);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 65;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 55, 55);

   // ERAB Modify
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 65, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11, RMU_MOD_ERAB);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 65;
   ueRecfgExp.bRecfgBitMap = 1;
   ueRecfgExp.bNoErabsAccepted = 0;
   ueRecfgExp.bNoErabsRejected = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 65);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABModifyRequest_for_to_change_qci_2341_When_max_qci1_reached_is_rejected)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);


   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 4
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 64, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);

   resetEnv();

   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 5
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 65, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 65, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 65;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup for qci-2
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 65, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 2, 11);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 65;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // ERAB Modify qci 2 to 3
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 65, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 3, 11, RMU_MOD_ERAB);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 65;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.bNoErabsRejected = 0;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Modify qci 3 to 4
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 65, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 4, 11, RMU_MOD_ERAB);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 65;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.bNoErabsRejected = 0;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 55, 55);

   // ERAB Modify qci 4 to 1
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 65, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11, RMU_MOD_ERAB);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 65;
   ueRecfgExp.bRecfgBitMap = 1;
   ueRecfgExp.bNoErabsAccepted = 0;
   ueRecfgExp.bNoErabsRejected = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 65);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABModifyRequest_for_not_admitted_bearer_is_rejected)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Modify for unknown RAB ID
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 10, RMU_MOD_ERAB);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 1;
   ueRecfgExp.bNoErabsAccepted = 0;
   ueRecfgExp.bNoErabsRejected = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
 
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABModifyRequest_for_invaid_qci_is_rejected)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Modify for to change the invalid QCI
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 11, 11, RMU_MOD_ERAB);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 1;
   ueRecfgExp.bNoErabsAccepted = 0;
   ueRecfgExp.bNoErabsRejected = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
 
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABModifyRequest_for_qci1_to_2_accepted)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Modify changing the qci 1 to 2  
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 2, 11, RMU_MOD_ERAB);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.bNoErabsRejected = 0;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
 
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCellManagerTest, handle_ERABModifyRequest_non_gbr_to_non_gbr_is_accepted)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
#if 0
   // ERAB Setup
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
#endif
   // ERAB Modify changing the qci 5 to 6  
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 6, 13, RMU_MOD_ERAB);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.bNoErabsRejected = 0;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
 
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
}

TEST(CCellManagerTestStandAlone, handle_UeAdmission_whenMax_CSGUEs_Reached_SameArpQciPriority_Different_InactivityTimerExpiry_is_preEmpt)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;
   RmuUeInactInd             ueInactiveInd;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 2;
   stCellConfigData.bMaxSigUesServed         = 2;
   stCellConfigData.usMaxCsgUes              = 1;
   stCellConfigData.usMaxNonCsgUes           = 1;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   //RmuUeInactInd *ueInactiveInd = (RmuUeInactInd*) malloc(sizeof(RmuUeInactInd));
   /* send the UE inactive indication for UE-1 for 1st time*/
   memset(&ueInactiveInd, 0, sizeof(RmuUeInactInd));
   ueInactiveInd.uiCrnti = 61;
   ueInactiveInd.uiCellId = 1;
   ueInactiveInd.uiInactEvt = RMU_UE_NO_DATA;
   pstCellMngrObj->procUeInactInd(ueInactiveInd);
 
   /* send the UE inactive indication for UE-1 for 2nd time*/
   memset(&ueInactiveInd, 0, sizeof(RmuUeInactInd));
   ueInactiveInd.uiCrnti = 61;
   ueInactiveInd.uiCellId = 1;
   ueInactiveInd.uiInactEvt = RMU_UE_NO_DATA;
   pstCellMngrObj->procUeInactInd(ueInactiveInd);
 

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, true, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);


   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   /* expect the UE Release indication */
   isUeRelIndExpected = true; 
   ueRelIndExp.bCellId = 1;
   ueRelIndExp.usCrnti = 61;
   //ueRelIndExp.enRelCause = ;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   freeCellManagerObj(pstCellMngrObj);
}

TEST(CCellManagerTestStandAlone, handle_UeAdmission_nonCsg_whenMaxServedUeReached)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 3;
   stCellConfigData.bMaxSigUesServed         = 10;
   stCellConfigData.usMaxCsgUes              = 3;
   stCellConfigData.usMaxNonCsgUes           = 3;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);


   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 4
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_SIGNALLING, 1, 64, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);
   
   //resetEnv();
   //isUeAdmitRspExpInfoSet = TRUE;
   //ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.stStatusInfo.enStatus = RMU_REDIRECT;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   freeCellManagerObj(pstCellMngrObj);
}

TEST(CCellManagerTestStandAlone, handle_UeAdmission_emergency_whenMaxServedUeReached)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 2;
   stCellConfigData.bMaxSigUesServed         = 10;
   stCellConfigData.usMaxCsgUes              = 2;
   stCellConfigData.usMaxNonCsgUes           = 2;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);


   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 63, 1);

   /* expect the UE Release indication */
   resetEnv();
   isUeRelIndExpected = true; 
   ueRelIndExp.bCellId = 1;
   ueRelIndExp.usCrnti = 61;

   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   freeCellManagerObj(pstCellMngrObj);
}

TEST(CCellManagerTestStandAlone, handle_UeAdmission_whenMax_nonCSGUEs_Reached_SameArpQciPriority_Different_InactivityTimerExpiry_is_preEmpt)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;
   RmuUeInactInd             ueInactiveInd;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 3;
   stCellConfigData.bMaxSigUesServed         = 2;
   stCellConfigData.usMaxCsgUes              = 1;
   stCellConfigData.usMaxNonCsgUes           = 2;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, false, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, false, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

 

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, false, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   //RmuUeInactInd *ueInactiveInd = (RmuUeInactInd*) malloc(sizeof(RmuUeInactInd));
   /* send the UE inactive indication for UE-1 for 1st time*/
   memset(&ueInactiveInd, 0, sizeof(RmuUeInactInd));
   ueInactiveInd.uiCrnti = 62;
   ueInactiveInd.uiCellId = 1;
   ueInactiveInd.uiInactEvt = RMU_UE_NO_DATA;
   pstCellMngrObj->procUeInactInd(ueInactiveInd);
 
   /* send the UE inactive indication for UE-1 for 2nd time*/
   memset(&ueInactiveInd, 0, sizeof(RmuUeInactInd));
   ueInactiveInd.uiCrnti = 62;
   ueInactiveInd.uiCellId = 1;
   ueInactiveInd.uiInactEvt = RMU_UE_NO_DATA;
   pstCellMngrObj->procUeInactInd(ueInactiveInd);

   /* send the UE inactive indication for UE-1 for 2nd time*/
   memset(&ueInactiveInd, 0, sizeof(RmuUeInactInd));
   ueInactiveInd.uiCrnti = 62;
   ueInactiveInd.uiCellId = 1;
   ueInactiveInd.uiInactEvt = RMU_UE_NO_DATA;
   pstCellMngrObj->procUeInactInd(ueInactiveInd);


  
  // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 64, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, false, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   //RmuUeInactInd *ueInactiveInd = (RmuUeInactInd*) malloc(sizeof(RmuUeInactInd));
   /* send the UE inactive indication for UE-1 for 1st time*/
   memset(&ueInactiveInd, 0, sizeof(RmuUeInactInd));
   ueInactiveInd.uiCrnti = 64;
   ueInactiveInd.uiCellId = 1;
   ueInactiveInd.uiInactEvt = RMU_UE_NO_DATA;
   pstCellMngrObj->procUeInactInd(ueInactiveInd);
 
   /* send the UE inactive indication for UE-1 for 2nd time*/
   memset(&ueInactiveInd, 0, sizeof(RmuUeInactInd));
   ueInactiveInd.uiCrnti = 64;
   ueInactiveInd.uiCellId = 1;
   ueInactiveInd.uiInactEvt = RMU_UE_NO_DATA;
   pstCellMngrObj->procUeInactInd(ueInactiveInd);

   // UE 4
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   /* expect the UE Release indication */
   isUeRelIndExpected = true; 
   ueRelIndExp.bCellId = 1;
   ueRelIndExp.usCrnti = 62;
   //ueRelIndExp.enRelCause = ;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
 
   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   freeCellManagerObj(pstCellMngrObj);
}

TEST(CCellManagerTestStandAlone, handle_UeAdmission_whenMax_nonCSGUEs_Reached_same_Arp_different_QciPriority_same_InactivityTimerExpiry_is_preEmpt)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;
   RmuUeInactInd             ueInactiveInd;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 2;
   stCellConfigData.bMaxSigUesServed         = 1;
   stCellConfigData.usMaxCsgUes              = 1;
   stCellConfigData.usMaxNonCsgUes           = 1;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, false, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, false, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

  /* send the UE inactive indication for UE-1 for 1st time*/
   memset(&ueInactiveInd, 0, sizeof(RmuUeInactInd));
   ueInactiveInd.uiCrnti = 61;
   ueInactiveInd.uiCellId = 1;
   ueInactiveInd.uiInactEvt = RMU_UE_NO_DATA;
   pstCellMngrObj->procUeInactInd(ueInactiveInd);
 
   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, false, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 3, 11);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   //RmuUeInactInd *ueInactiveInd = (RmuUeInactInd*) malloc(sizeof(RmuUeInactInd));
   /* send the UE inactive indication for UE-1 for 1st time*/
   memset(&ueInactiveInd, 0, sizeof(RmuUeInactInd));
   ueInactiveInd.uiCrnti = 62;
   ueInactiveInd.uiCellId = 1;
   ueInactiveInd.uiInactEvt = RMU_UE_NO_DATA;
   pstCellMngrObj->procUeInactInd(ueInactiveInd);
 

   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   /* expect the UE Release indication */
   isUeRelIndExpected = true; 
   ueRelIndExp.bCellId = 1;
   ueRelIndExp.usCrnti = 62;
   //ueRelIndExp.enRelCause = ;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   freeCellManagerObj(pstCellMngrObj);
}

TEST(CCellManagerTestStandAlone, handle_UeAdmission_whenMax_CSG_Emergency_UEs_Reached_is_preEmpt_non_csgUe)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 3;
   stCellConfigData.bMaxSigUesServed         = 2;
   stCellConfigData.usMaxCsgUes              = 1;
   stCellConfigData.usMaxNonCsgUes           = 2;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
 
   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   // UE 4 
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 64, 1);

   /* expect the UE Release indication */
   isUeRelIndExpected = true; 
   ueRelIndExp.bCellId = 1;
   ueRelIndExp.usCrnti = 63;
   //ueRelIndExp.enRelCause = ;
   
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
 

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   freeCellManagerObj(pstCellMngrObj);
}

TEST_F(CCellManagerTest, handle_ERABModifyRequest_multiBearer)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, FALSE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup - for bearer 1
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 10);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup - for bearer 2
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, FALSE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 48, 48);

   // ERAB Modify
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 10, RMU_MOD_ERAB);
   // modify the GBR bit rate to higher value
   RmuErabConfigIe *stRabConfig = &(stUeRecfgReq.stErabConfInfo);
   U32 idx = 10;
   RmuErabGbrInfoIe *stGbrInfo = &(stRabConfig->stErabAddModLst[0].stErabQosInfo.stErabGbrInfo);
   RmuErabGbrInfoIe *stGbrInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabGbrInfo);
   stGbrInfo->uiErabDlMbr     = 2000000;
   stGbrInfo->uiErabUlMbr     = 2000000;
   stGbrInfo->uiErabDlGbr     = 2000000;
   stGbrInfo->uiErabUlGbr     = 2000000;

   // add another bearer in UE reconfiguration
   stRabConfig = &(stUeRecfgReq.stErabConfInfo);
   idx = 11;
   stRabConfig->stErabAddModLst[1].bErabId = stRabSetupConfig[idx].bErabId;
   RmuErabArpInfoIe *stArpInfo = &(stRabConfig->stErabAddModLst[1].stErabQosInfo.stErabArpInfo);
   RmuErabArpInfoIe *stArpInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabArpInfo);
   stArpInfo->bErabPrioLvl    = stArpInfoDB->bErabPrioLvl;
   stArpInfo->bErabPreemptCap = stArpInfoDB->bErabPreemptCap;
   stArpInfo->bErabPreemptVul = stArpInfoDB->bErabPreemptVul;

   stGbrInfo = &(stRabConfig->stErabAddModLst[1].stErabQosInfo.stErabGbrInfo);
   stGbrInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabGbrInfo);
   stGbrInfo->uiErabDlMbr     = 4096;
   stGbrInfo->uiErabUlMbr     = 4096;
   stGbrInfo->uiErabDlGbr     = 4096;
   stGbrInfo->uiErabUlGbr     = 4096;
   stRabConfig->stErabAddModLst[1].stErabQosInfo.bErabQCI = 2;
   stRabConfig->usNoErabsToAddMod++;

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.bNoErabsRejected = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
}

TEST_F(CCellManagerTest, handle_stopPrbReportConfig)
{
   resetEnv();
   isStopPrbReportCfg = TRUE;

   pstCellMngrObj->triggerStopPrbUsageReport();

}


TEST_F(CCellManagerTest, handle_QCIBased_ERAB_rejection)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   //fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 5, 0, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.bNoErabsRejected = 4;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   //fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 5, 0, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.bNoErabsRejected = 4;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, TRUE, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 47);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, TRUE, 0);
   //fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 2, 0, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.bNoErabsRejected = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

//////////////////////////////////////////
// Test scenarios for ACB starts here
//////////////////////////////////////////
TEST_F(CCellManagerTest, handle_ACB_reCfg_enableEmergency)
{
   LrmCellConfiguration      stCellCfg;
   RmuUeAdmitReq             admitReq;

   // update ACB reconfiguration info
   stCellCfg.usReCfgType = LRM_CELL_RECFGTYPE_ACB_EMERGENCY;
   stCellCfg.stCellCfgInfo.bCellId = 1;
   stCellCfg.stCellCfgInfo.stAcbInfo.bAcBarringEmergency = true;
   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoSig = false;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbFactor = RM_ACB_FACTOR_P95;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbTime = RM_ACB_TIME_S4;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.bAcbForSpac = 0xf0;
   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoData = false;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbFactor = RM_ACB_FACTOR_P95;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbTime = RM_ACB_TIME_S4;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.bAcbForSpac = 0xf0;

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.emergency = true;
   pstCellMngrObj->reConfigureCell(stCellCfg);

   // verify UE attach
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeAdmitReq(admitReq);

   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_SIGNALLING, 1, 62, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeAdmitReq(admitReq);

   createAdmitReq(&admitReq, RMU_EST_CAUSE_DELAY_TOLERANT, 1, 63, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeAdmitReq(admitReq);

   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 64, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstCellMngrObj->procUeAdmitReq(admitReq);

   createAdmitReq(&admitReq, RMU_EST_CAUSE_MT_ACCESS, 1, 65, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeAdmitReq(admitReq);

   createAdmitReq(&admitReq, RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS, 1, 66, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeAdmitReq(admitReq);

}

TEST_F(CCellManagerTest, handle_ACB_reCfgMoSig_enableMoSig)
{
   LrmCellConfiguration      stCellCfg;

   // update ACB reconfiguration info
   stCellCfg.usReCfgType = LRM_CELL_RECFGTYPE_ACB_MOSIG;
   stCellCfg.stCellCfgInfo.bCellId = 1;
   stCellCfg.stCellCfgInfo.stAcbInfo.bAcBarringEmergency = false;
   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoSig = true;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbFactor = RM_ACB_FACTOR_P30;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbTime = RM_ACB_TIME_S512;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.bAcbForSpac = 0xf0;
   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoData = false;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbFactor = RM_ACB_FACTOR_P95;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbTime = RM_ACB_TIME_S4;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.bAcbForSpac = 0xf0;

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S512;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P30;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   pstCellMngrObj->reConfigureCell(stCellCfg);

}

TEST_F(CCellManagerTest, handle_ACB_reCfgMoData_enableMoData)
{
   LrmCellConfiguration      stCellCfg;
   // update ACB reconfiguration info
   stCellCfg.usReCfgType = LRM_CELL_RECFGTYPE_ACB_MODATA;
   stCellCfg.stCellCfgInfo.bCellId = 1;
   stCellCfg.stCellCfgInfo.stAcbInfo.bAcBarringEmergency = false;
   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoSig = false;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbFactor = RM_ACB_FACTOR_P95;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbTime = RM_ACB_TIME_S4;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.bAcbForSpac = 0xf0;
   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoData = true;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbFactor = RM_ACB_FACTOR_P30;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbTime = RM_ACB_TIME_S512;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.bAcbForSpac = 0xf0;

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S512;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P30;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;
   pstCellMngrObj->reConfigureCell(stCellCfg);

}

TEST_F(CCellManagerTest, handle_ACB_reCfgMoSigMoData_enableMoData)
{
   LrmCellConfiguration      stCellCfg;

   // update ACB reconfiguration info
   stCellCfg.usReCfgType = (LRM_CELL_RECFGTYPE_ACB_MODATA |
      LRM_CELL_RECFGTYPE_ACB_MOSIG);
   stCellCfg.stCellCfgInfo.bCellId = 1;
   stCellCfg.stCellCfgInfo.stAcbInfo.bAcBarringEmergency = false;
   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoSig = false;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbFactor = RM_ACB_FACTOR_P30;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbTime = RM_ACB_TIME_S512;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.bAcbForSpac = 0xf0;

   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoData = true;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbFactor = RM_ACB_FACTOR_P30;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbTime = RM_ACB_TIME_S512;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.bAcbForSpac = 0xf0;

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S512;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P30;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;
   pstCellMngrObj->reConfigureCell(stCellCfg);

}

TEST_F(CCellManagerTest, handle_ACB_reCfgMoSigMoData_enableMoSig)
{
   LrmCellConfiguration      stCellCfg;
   // update ACB reconfiguration info
   stCellCfg.usReCfgType = (LRM_CELL_RECFGTYPE_ACB_MODATA |
      LRM_CELL_RECFGTYPE_ACB_MOSIG);
   stCellCfg.stCellCfgInfo.bCellId = 1;
   stCellCfg.stCellCfgInfo.stAcbInfo.bAcBarringEmergency = false;
   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoSig = true;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbFactor = RM_ACB_FACTOR_P30;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbTime = RM_ACB_TIME_S512;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.bAcbForSpac = 0xf0;

   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoData = false;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbFactor = RM_ACB_FACTOR_P30;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbTime = RM_ACB_TIME_S512;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.bAcbForSpac = 0xf0;

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S512;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P30;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   pstCellMngrObj->reConfigureCell(stCellCfg);

}

TEST_F(CCellManagerTest, handle_ACB_reCfgMoSigMoData_enableEmergency)
{
   LrmCellConfiguration      stCellCfg;

   // update ACB reconfiguration info
   stCellCfg.usReCfgType = (LRM_CELL_RECFGTYPE_ACB_MODATA |
      LRM_CELL_RECFGTYPE_ACB_MOSIG | 
      LRM_CELL_RECFGTYPE_ACB_EMERGENCY);
   stCellCfg.stCellCfgInfo.bCellId = 1;
   stCellCfg.stCellCfgInfo.stAcbInfo.bAcBarringEmergency = true;
   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoSig = false;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbFactor = RM_ACB_FACTOR_P30;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbTime = RM_ACB_TIME_S512;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.bAcbForSpac = 0xf0;

   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoData = false;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbFactor = RM_ACB_FACTOR_P30;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbTime = RM_ACB_TIME_S512;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.bAcbForSpac = 0xf0;

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.emergency = true;
   pstCellMngrObj->reConfigureCell(stCellCfg);

}

TEST_F(CCellManagerTest, handle_ACB_reCfgMoSigMoData_enableAll)
{
   LrmCellConfiguration      stCellCfg;

   // update ACB reconfiguration info
   stCellCfg.usReCfgType = (LRM_CELL_RECFGTYPE_ACB_MODATA |
      LRM_CELL_RECFGTYPE_ACB_MOSIG | 
      LRM_CELL_RECFGTYPE_ACB_EMERGENCY);
   stCellCfg.stCellCfgInfo.bCellId = 1;
   stCellCfg.stCellCfgInfo.stAcbInfo.bAcBarringEmergency = true;
   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoSig = true;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbFactor = RM_ACB_FACTOR_P30;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbTime = RM_ACB_TIME_S512;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.bAcbForSpac = 0xf0;

   stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoData = true;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbFactor = RM_ACB_FACTOR_P30;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbTime = RM_ACB_TIME_S512;
   stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.bAcbForSpac = 0xf0;

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.emergency = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S512;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P30;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S512;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P30;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;
   pstCellMngrObj->reConfigureCell(stCellCfg);

}

TEST(CCellManagerTestStandAlone, handle_ueadmission_ccpu00148899)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 2;
   stCellConfigData.bMaxSigUesServed         = 2;
   stCellConfigData.usMaxCsgUes              = 2;
   stCellConfigData.usMaxNonCsgUes           = 2;
   stCellConfigData.usMaxExtraUes            = 0;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 2,4);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 2,4);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 7;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 63, 1);
   /* expect the UE Release indication */
   resetEnv();
   isUeRelIndExpected = true; 
   ueRelIndExp.bCellId = 1;
   ueRelIndExp.usCrnti = 62;
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeAdmitReq(admitReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   freeCellManagerObj(pstCellMngrObj);
}

TEST(CCellManagerTestStandAlone,
      handle_HighPriorityUE_Admission_when_Max_ActiveUE_Reached_MODATA_and_Nonpreemptible)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 3;
   stCellConfigData.bMaxSigUesServed         = 3;
   stCellConfigData.usMaxCsgUes              = 3;
   stCellConfigData.usMaxNonCsgUes           = 0;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
  
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 4 
   createAdmitReq(&admitReq, RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS, 1, 64, 1);

   /* expect the UE Release indication */
   isUeRelIndExpected = true; 
   ueRelIndExp.bCellId = 1;
   ueRelIndExp.usCrnti = 61;
   //ueRelIndExp.enRelCause = ;
   
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
 
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   freeCellManagerObj(pstCellMngrObj);
}

TEST(CCellManagerTestStandAlone,
      handle_HighPriorityUE_Admission_when_Max_ActiveUE_Reached_Emergency_and_Nonpreemptible)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 3;
   stCellConfigData.bMaxSigUesServed         = 3;
   stCellConfigData.usMaxCsgUes              = 3;
   stCellConfigData.usMaxNonCsgUes           = 0;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
  
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 4 
   createAdmitReq(&admitReq, RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS, 1, 64, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstCellMngrObj->procUeAdmitReq(admitReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   freeCellManagerObj(pstCellMngrObj);
   resetEnv();
}

TEST(CCellManagerTestStandAlone,
      handle_HighPriorityUE_Admission_when_Max_ActiveUE_Reached_MODATA_and_Nonpreemptible_CSG_Morethan_ConfiguredCSG)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 4;
   stCellConfigData.bMaxSigUesServed         = 4;
   stCellConfigData.usMaxCsgUes              = 2;
   stCellConfigData.usMaxNonCsgUes           = 2;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
  
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, true, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 4
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 64, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
  
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, false, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 5 
   createAdmitReq(&admitReq, RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS, 1, 65, 1);

   /* expect the UE Release indication */
   isUeRelIndExpected = true; 
   ueRelIndExp.bCellId = 1;
   ueRelIndExp.usCrnti = 61;
   
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 65, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 65;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
 
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 65);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   freeCellManagerObj(pstCellMngrObj);
}

TEST(CCellManagerTestStandAlone,
      handle_HighPriorityUE_Admission_when_Max_ActiveUE_Reached_MODATA_and_Nonpreemptible_CSG_Equalto_ConfiguredCSG)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 4;
   stCellConfigData.bMaxSigUesServed         = 4;
   stCellConfigData.usMaxCsgUes              = 2;
   stCellConfigData.usMaxNonCsgUes           = 2;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, TRUE, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
  
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, false, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 4
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 64, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
  
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, false, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 5 
   createAdmitReq(&admitReq, RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS, 1, 65, 1);

   /* expect the UE Release indication */
   isUeRelIndExpected = true; 
   ueRelIndExp.bCellId = 1;
   ueRelIndExp.usCrnti = 63;
   
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 65, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 65;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
 
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 65);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   freeCellManagerObj(pstCellMngrObj);
}

TEST(CCellManagerTestStandAlone,
      handle_HighPriorityUE_Admissioni_bypreempting_Preemptable_CSGUE)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 3;
   stCellConfigData.bMaxSigUesServed         = 3;
   stCellConfigData.usMaxCsgUes              = 2;
   stCellConfigData.usMaxNonCsgUes           = 1;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 4 
   createAdmitReq(&admitReq, RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS, 1, 64, 1);

   /* expect the UE Release indication */
   isUeRelIndExpected = true; 
   ueRelIndExp.bCellId = 1;
   ueRelIndExp.usCrnti = 61;
   
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
 
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 65);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   freeCellManagerObj(pstCellMngrObj);
}

TEST(CCellManagerTestStandAlone,
      handle_EmergencyUE_Admission_bypreempting_NonPreemptable_CSGUE)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 3;
   stCellConfigData.bMaxSigUesServed         = 3;
   stCellConfigData.usMaxCsgUes              = 2;
   stCellConfigData.usMaxNonCsgUes           = 1;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 4 
   createAdmitReq(&admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 64, 1);

   /* expect the UE Release indication */
   isUeRelIndExpected = true; 
   ueRelIndExp.bCellId = 1;
   ueRelIndExp.usCrnti = 61;
   
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
 
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 65);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   freeCellManagerObj(pstCellMngrObj);
}

TEST(CCellManagerTestStandAlone,
      handle_EmergencyUE_Admission_with_Emergency_Bearer)
{
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   
   fillCellConfigDataForSpecificConfig(&stCellConfigData, 27);
   
   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 3;
   stCellConfigData.bMaxSigUesServed         = 3;
   stCellConfigData.usMaxCsgUes              = 2;
   stCellConfigData.usMaxNonCsgUes           = 1;
   stCellConfigData.usMaxExtraUes            = 1;

   pstCellMngrObj = getNewCellObj(&stCellConfigData);
   pstCellMngrObj->rmInitRadioRes();
   pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
  
   updatePrbRprt(pstCellMngrObj, 3, 1, 47, 40);

   // UE 1
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 61, bRecfgBitMap, true, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
   
   // UE 2
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 62, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 62, bRecfgBitMap, false, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 7);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 3
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 63, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, false, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);
  
   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, false, 0);
   // setting up a vulnerable bearer
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 7);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 6;

   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   // UE 4 
   createAdmitReq(&admitReq, RMU_EST_CAUSE_MO_DATA, 1, 64, 1);
   pstCellMngrObj->procUeAdmitReq(admitReq);

   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG | RMU_RECFG_REQ_UE_CAP;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, true, 0);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.stStatusInfo.enStatus = RMU_REDIRECT;
   
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);
   
   freeCellManagerObj(pstCellMngrObj);
   resetEnv();
}

/**********************************************************************
         End of file:     test_rm_cellmanager.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:51:48 2016
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
*********************************************************************91*/
