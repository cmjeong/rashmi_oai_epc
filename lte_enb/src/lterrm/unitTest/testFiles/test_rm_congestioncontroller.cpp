


/**********************************************************************

    Name:   Test file for RRM Module

    Type:   CPP source file

    Desc:   Contains GT test cases for Congestion Controller Class

    File:   test_rm_congetioncontroller.cpp

    Sid:      test_rm_congestioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/11 - Mon Feb 15 12:52:08 2016

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

/* class used to test Congestion Controller Class functions */
class CCongestionControllerTest : public ::testing::Test
{
public:
   LrmCellConfigData         stCellConfigData;
   CCellManager              *pstCellMngrObj;
protected:
   virtual void SetUp()
   {
      PRNT_TEST_NAME();
      sendRmGenCfg();
      configRmuUSap(0); //SP ID
      fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);
      stCellConfigData.bMaxAvgGbrPrbUsage = 70;
      pstCellMngrObj = getNewCellObj(&stCellConfigData);
      pstCellMngrObj->setEnbState(RMU_ENB_STATUS_UP);
   }

   virtual void TearDown()
   {
      freeCellManagerObj(pstCellMngrObj);
   }
};

//////////////////////////////////////////
// Test scenarios starting from here
// //////////////////////////////////////
TEST_F(CCongestionControllerTest, handle_congestionDetection)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

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

   updatePrbRprt(pstCellMngrObj, 3, 1, 50, 50);

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
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 70, 70);

   updatePrbRprt(pstCellMngrObj, 3, 1, 77, 77);
   updatePrbRprt(pstCellMngrObj, 3, 1, 77, 77);
   updatePrbRprt(pstCellMngrObj, 3, 1, 77, 77);
   updatePrbRprt(pstCellMngrObj, 3, 1, 77, 77);

   resetEnv();
   isUeErabRelIndExpected = TRUE;
   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80);

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCongestionControllerTest, handle_congestion_slowdecrease_3preemption)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

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

   updatePrbRprt(pstCellMngrObj, 3, 1, 50, 50); // avg = 50

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
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 70, 70); // avg = 60

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

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 66

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

   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 70
   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 72

   /* sample time = 15 ms
    * totWindTime = 25 ms (window size 5 * interval 5)
    */
   /* preemption 1 */
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 78
   //updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 80

   resetEnv();
   updatePrbRprt(pstCellMngrObj, 3, 1, 82, 82); // avg = 80
   updatePrbRprt(pstCellMngrObj, 3, 1, 82, 82); // avg = 81
   isUeErabRelIndExpected = TRUE;
   updatePrbRprt(pstCellMngrObj, 3, 1, 82, 82); // avg = 81

   resetEnv();
   updatePrbRprt(pstCellMngrObj, 3, 1, 82, 82); // avg = 81
   updatePrbRprt(pstCellMngrObj, 3, 1, 82, 82); // avg = 82
   updatePrbRprt(pstCellMngrObj, 3, 1, 77, 77); // avg = 80
   updatePrbRprt(pstCellMngrObj, 3, 1, 77, 77); // avg = 78
   updatePrbRprt(pstCellMngrObj, 3, 1, 77, 77); // avg = 78
   updatePrbRprt(pstCellMngrObj, 3, 1, 77, 77); // avg = 78
   isUeErabRelIndExpected = TRUE;
   updatePrbRprt(pstCellMngrObj, 3, 1, 82, 82); // avg = 78
   updatePrbRprt(pstCellMngrObj, 3, 1, 70, 70); // avg = 76
   updatePrbRprt(pstCellMngrObj, 3, 1, 65, 65); // avg = 70
   updatePrbRprt(pstCellMngrObj, 3, 1, 60, 60); // avg = 67
   updatePrbRprt(pstCellMngrObj, 3, 1, 55, 55); // avg = 65
   updatePrbRprt(pstCellMngrObj, 3, 1, 50, 50); // avg = 65
   updatePrbRprt(pstCellMngrObj, 3, 1, 50, 50); // avg = 65

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCongestionControllerTest, handle_congestion_rapiddecrease_1preemption)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

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

   updatePrbRprt(pstCellMngrObj, 3, 1, 50, 50); // avg = 50

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
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 70, 70); // avg = 60

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

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 12);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 66

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

   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 70
   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 72

   /* sample time = 15 ms
    * totWindTime = 25 ms (window size 5 * interval 5)
    */
   /* preemption 1 */
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 78
   //updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 80 for sampleTime = 80

   resetEnv();
   updatePrbRprt(pstCellMngrObj, 3, 1, 82, 82); // avg = 80 for sampleTime = 80
   updatePrbRprt(pstCellMngrObj, 3, 1, 72, 72); // avg = 79 for sampleTime = 79
   updatePrbRprt(pstCellMngrObj, 3, 1, 70, 70); // avg = 78 for sampleTime = 77
   updatePrbRprt(pstCellMngrObj, 3, 1, 65, 65); // avg = 77 for sampleTime = 74
   updatePrbRprt(pstCellMngrObj, 3, 1, 62, 62); // avg = 75 for sampleTime = 74
   updatePrbRprt(pstCellMngrObj, 3, 1, 57, 57); // avg = 75 for sampleTime = 74
   updatePrbRprt(pstCellMngrObj, 3, 1, 52, 52); // avg = 75 for sampleTime = 74
   updatePrbRprt(pstCellMngrObj, 3, 1, 57, 57); // avg = 75 for sampleTime = 74

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

TEST_F(CCongestionControllerTest, handle_erabSetup_during_congestion)
{
   RmuUeAdmitReq             admitReq;
   U8                        bRecfgBitMap;
   RmuUeRecfgReq             stUeRecfgReq;
   RmuUeRelReq               ueRelReq;

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

   updatePrbRprt(pstCellMngrObj, 3, 1, 50, 50); // avg = 50

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
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 62;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 70, 70); // avg = 60

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

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 63, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 1, 11);
   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 63;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 66

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

   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 70
   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 72

   /* sample time = 15 ms
    * totWindTime = 25 ms (window size 5 * interval 5)
    */
   /* preemption 1 */
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 78
   //updatePrbRprt(pstCellMngrObj, 3, 1, 80, 80); // avg = 80

   resetEnv();
   updatePrbRprt(pstCellMngrObj, 3, 1, 82, 82); // avg = 80
   updatePrbRprt(pstCellMngrObj, 3, 1, 82, 82); // avg = 81
   isUeErabRelIndExpected = TRUE;
   updatePrbRprt(pstCellMngrObj, 3, 1, 82, 82); // avg = 81

   // ERAB Setup
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(&stUeRecfgReq, 1, 1, 64, bRecfgBitMap, TRUE, 0);
   fillErabConfigRequest(&(stUeRecfgReq.stErabConfInfo), 1, 2, 12);
   resetEnv();
   isUeErabRelIndExpected = TRUE;
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 64;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstCellMngrObj->procUeRecfgReq(stUeRecfgReq);

   resetEnv();
   updatePrbRprt(pstCellMngrObj, 3, 1, 77, 77); // avg = 78
   updatePrbRprt(pstCellMngrObj, 3, 1, 77, 77); // avg = 78
   updatePrbRprt(pstCellMngrObj, 3, 1, 77, 77); // avg = 78
   updatePrbRprt(pstCellMngrObj, 3, 1, 82, 82); // avg = 78
   updatePrbRprt(pstCellMngrObj, 3, 1, 70, 70); // avg = 76
   updatePrbRprt(pstCellMngrObj, 3, 1, 65, 65); // avg = 70
   updatePrbRprt(pstCellMngrObj, 3, 1, 60, 60); // avg = 67
   updatePrbRprt(pstCellMngrObj, 3, 1, 55, 55); // avg = 65
   updatePrbRprt(pstCellMngrObj, 3, 1, 50, 50); // avg = 65
   updatePrbRprt(pstCellMngrObj, 3, 1, 50, 50); // avg = 65

   createUeRelReq(&ueRelReq, 1, 1, 61);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 62);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 63);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

   createUeRelReq(&ueRelReq, 1, 1, 64);
   pstCellMngrObj->procUeRelReq(&ueRelReq);

}

/**********************************************************************
End of file:     test_rm_congestioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/11 - Mon Feb 15 12:52:08 2016
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
*********************************************************************91*/
