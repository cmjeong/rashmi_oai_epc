


/**********************************************************************

    Name:   Test file for RRM Module

    Type:   CPP source file

    Desc:   Contains GT test cases for Application Class

    File:   test_rm_application.cpp

    Sid:      test_rm_application.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:52:05 2016

    Prg:    sri

**********************************************************************/
#include <limits.h>
#include "gtest/gtest.h"

// File with class that is being tested
#include "test_rm.h"
#include "rm_application.h"

/* The below lines need to be in some common place and not inside the test code
 * */
#ifdef _cplusplus
extern "C" {
   S16 tst();
}
#endif

int main(int argc, char **argv)
{
   int retVal;
   ::testing::InitGoogleTest(&argc, argv);
   intializeRlog();
   retVal = RUN_ALL_TESTS();
   printf("\nGT Test Run RetVal : %d\n", retVal);
   flushData(0);
   return retVal;
}

CRrmApplication *getNewApplObj()
{
   return new CRrmApplication;
}

void delApplObj(CRrmApplication *pstApplObj)
{
   RmProtoCfg             stProtoCfg;

   // create a cell manager obj
   stProtoCfg.bCfgType = (LrmCfgType)LRM_CELL_CONFIG;
   fillCellConfigDataForSpecificConfig(&(stProtoCfg.u.stCellCfg.stCellCfgInfo),
         24);
   stProtoCfg.u.stCellCfg.enCellAddModDel = (LrmCfgAction) LRM_CFG_DEL;
   pstApplObj->processSmMsg(EVTLRMCFGREQ, (U8*)&stProtoCfg);

   delete pstApplObj;
}

CRrmApplication *createApplAndSetUpSingleCell()
{
   CRrmApplication        *pstApplObj = getNewApplObj();
   RmMngmt                stMgmtMsg;
   RmProtoCfg             stProtoCfg;

   sendRmGenCfg();
   configRmuUSap(0); //SP ID
   configRmuLSapCfg(0, 0); // SU ID, SP ID
   // create a cell manager obj
   stProtoCfg.bCfgType = (LrmCfgType)LRM_CELL_CONFIG;
   fillCellConfigDataForSpecificConfig(&(stProtoCfg.u.stCellCfg.stCellCfgInfo),
         24);
   stProtoCfg.u.stCellCfg.enCellAddModDel = (LrmCfgAction) LRM_CFG_ADD;
   pstApplObj->processSmMsg(EVTLRMCFGREQ, (U8*)&stProtoCfg);

   resetEnv();
   isStartPrbReportCfg = TRUE;
   // set cell up
   stMgmtMsg.t.usta.u.stEnbStaInfo.enStaType = 
      (LrmEnbStaType)LRM_ENBSTATYPE_CELLUP;
   stMgmtMsg.t.usta.u.stEnbStaInfo.u.bCellId = 1;
   pstApplObj->processSmMsg(EVTLRMENBSTAIND, (U8*)&stMgmtMsg);

   return pstApplObj;
}

void addMme(CRrmApplication *pstApplObj, U32 mmeId)
{
   RmProtoCfg       stProtoCfg;
   RmuFsmStatusInd  *pstFsmStatusInd = (RmuFsmStatusInd*)malloc(sizeof(RmuCommonMsg));

   // configure MME 1
   stProtoCfg.bCfgType = (LrmCfgType)LRM_ENB_CONFIG;
   stProtoCfg.u.stEnbCfg.bCfgType = RRM_ENB_CFG_MME_CFG;
   stProtoCfg.u.stEnbCfg.u.stMmeCfg.enMmeAddModOrDel = LRM_CFG_ADD;
   stProtoCfg.u.stEnbCfg.u.stMmeCfg.usMmeId = mmeId;
   pstApplObj->processSmMsg(EVTLRMCFGREQ, (U8*)&stProtoCfg);

   // configure MME UP
   pstFsmStatusInd->enStatusType = RMU_FSM_STATUS_MME;
   pstFsmStatusInd->u.stMmeStatusInd.enMmeStatus = RMU_MME_STATUS_UP;
   pstFsmStatusInd->u.stMmeStatusInd.usMmeId = mmeId;
   pstApplObj->processFsmMsg(EVTRMUFSMSTAIND, (U8*)pstFsmStatusInd);

}

void downAndDeleteMme(CRrmApplication *pstApplObj, U32 mmeId)
{
   RmProtoCfg       stProtoCfg;
   RmuFsmStatusInd  *pstFsmStatusInd = (RmuFsmStatusInd*)malloc(sizeof(RmuCommonMsg));

   // configure MME DOWN 
   pstFsmStatusInd->enStatusType = RMU_FSM_STATUS_MME;
   pstFsmStatusInd->u.stMmeStatusInd.enMmeStatus = RMU_MME_STATUS_DOWN;
   pstFsmStatusInd->u.stMmeStatusInd.usMmeId = mmeId;
   pstApplObj->processFsmMsg(EVTRMUFSMSTAIND, (U8*)pstFsmStatusInd);
   
   // configure MME 1
   stProtoCfg.bCfgType = (LrmCfgType)LRM_ENB_CONFIG;
   stProtoCfg.u.stEnbCfg.bCfgType = RRM_ENB_CFG_MME_CFG;
   stProtoCfg.u.stEnbCfg.u.stMmeCfg.enMmeAddModOrDel = LRM_CFG_DEL;
   stProtoCfg.u.stEnbCfg.u.stMmeCfg.usMmeId = mmeId;
   pstApplObj->processSmMsg(EVTLRMCFGREQ, (U8*)&stProtoCfg);
}
void mmeOverloadStartInd(CRrmApplication *pstApplObj,U32 mmeId,rmuMmeOvldStatus cause)
{
   RmuMmeOvldStartInd *pstRmuOverLoadStartInd =
      (RmuMmeOvldStartInd*)malloc(sizeof(RmuCommonMsg));
   // MME Overload Start Indication
   pstRmuOverLoadStartInd->enMmeOvldStatus = cause;
   pstRmuOverLoadStartInd->usMmeId = mmeId;
   pstApplObj->processFsmMsg(EVTRMUOVLDSTRTIND, (U8*)pstRmuOverLoadStartInd);
}

class CApplicationTest : public ::testing::Test
{
public:
   CRrmApplication   *pstApplObj;
protected:
   virtual void SetUp()
   {
      PRNT_TEST_NAME();
      pstApplObj = createApplAndSetUpSingleCell();
   }

   virtual void TearDown()
   {
      delApplObj(pstApplObj);
   }
};

//////////////////////////////////////////
// Test scenarios starting from here
// //////////////////////////////////////
TEST_F(CApplicationTest, handle_PrbReportIndication)
{
   RgmPrbRprtInd     prbRprtInd;

   memset(&prbRprtInd, 0, sizeof(RgmPrbRprtInd));
   prbRprtInd.bCellId = 1;
   prbRprtInd.bPrbUsageMask = 3;
   prbRprtInd.stQciPrbRpts[0].bQci = 1;
   prbRprtInd.stQciPrbRpts[0].bAvgPrbDlUsage = 47;
   prbRprtInd.stQciPrbRpts[0].bAvgPrbUlUsage = 47;
   
   pstApplObj->processMacMsg(EVTRGMPRBRPRTIND, (U8*) &prbRprtInd);
}

TEST_F(CApplicationTest, handle_ueInactivityIndication)
{
   RmuUeAdmitReq     *admitReq;
   RmuUeRecfgReq     *stUeRecfgReq;
   RmuUeInactInd     *ueInactInd;
   U8                bRecfgBitMap;

   // UE 1
   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   stUeRecfgReq = (RmuUeRecfgReq*)malloc(sizeof(RmuUeRecfgReq));
   bRecfgBitMap = RMU_RECFG_REQ_ERAB_CONFIG;
   createUeRecfgReq(stUeRecfgReq, 1, 1, 61, bRecfgBitMap, TRUE, 0);

   resetEnv();
   isUeRecfgExpInfoSet = TRUE;
   ueRecfgExp.usCrnti = 61;
   ueRecfgExp.bRecfgBitMap = 3;
   ueRecfgExp.bNoErabsAccepted = 1;
   ueRecfgExp.stStatusInfo.enStatus = RMU_SUCCESS;
   ueRecfgExp.stErabAcceptLst[0].bErabId = 5;

   pstApplObj->processFsmMsg(EVTRMUUERECFGREQ, (U8*) stUeRecfgReq);

   // send UE inactivity indication - NO DATA
   ueInactInd = (RmuUeInactInd*)malloc(sizeof(RmuUeInactInd));
   ueInactInd->uiCrnti = 61;
   ueInactInd->uiCellId = 1;
   ueInactInd->uiInactEvt = RMU_UE_NO_DATA;
   pstApplObj->processFsmMsg(EVTRMUUEINACTIND, (U8*) ueInactInd);

   // send UE inactivity indication - DATA
   ueInactInd = (RmuUeInactInd*)malloc(sizeof(RmuUeInactInd));
   ueInactInd->uiCrnti = 61;
   ueInactInd->uiCellId = 1;
   ueInactInd->uiInactEvt = RMU_UE_DATA;
   pstApplObj->processFsmMsg(EVTRMUUEINACTIND, (U8*) ueInactInd);

}

//////////////////////////////////////////
// Test scenarios for ACB starts here
//////////////////////////////////////////
TEST_F(CApplicationTest, handle_ACB_mmeOveLoad_enableMoSigMoData)
{
   RmuMmeOvldStartInd *pMmeOvldStartInd = (RmuMmeOvldStartInd*)malloc(sizeof(RmuCommonMsg));
   RmuUeAdmitReq     *admitReq;

   addMme(pstApplObj,1);

   pMmeOvldStartInd->enMmeOvldStatus = RMU_MME_REJECT_MOSIG_MODATA;
   pMmeOvldStartInd->usMmeId = 1;

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;
   pstApplObj->processFsmMsg(EVTRMUOVLDSTRTIND, (U8*)pMmeOvldStartInd);

   // verify UE admission
   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MO_SIGNALLING, 1, 62, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_DELAY_TOLERANT, 1, 63, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 64, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;
 
   downAndDeleteMme(pstApplObj,1);
}

TEST_F(CApplicationTest, handle_ACB_mmeOveLoad_enableMoData)
{
   RmuMmeOvldStartInd *pMmeOvldStartInd = (RmuMmeOvldStartInd*)malloc(sizeof(RmuCommonMsg));
   RmuUeAdmitReq     *admitReq;

   addMme(pstApplObj,1);

   pMmeOvldStartInd->enMmeOvldStatus = RMU_MME_REJECT_MODATA;
   pMmeOvldStartInd->usMmeId = 1;

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;
   pstApplObj->processFsmMsg(EVTRMUOVLDSTRTIND, (U8*)pMmeOvldStartInd);

   // verify UE admission
   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MO_SIGNALLING, 1, 62, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 63, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_DELAY_TOLERANT, 1, 64, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;

   downAndDeleteMme(pstApplObj,1);
}

TEST_F(CApplicationTest, handle_ACB_mmeOveLoad_permitEmg_mtAcc_enableMoSigMoData)
{
   RmuMmeOvldStartInd *pMmeOvldStartInd = (RmuMmeOvldStartInd*)malloc(sizeof(RmuCommonMsg));
   RmuUeAdmitReq     *admitReq;

   addMme(pstApplObj,1);

   pMmeOvldStartInd->enMmeOvldStatus = RMU_MME_PERMITONLY_EMG_MTACCESS;
   pMmeOvldStartInd->usMmeId = 1;

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;
   pstApplObj->processFsmMsg(EVTRMUOVLDSTRTIND, (U8*)pMmeOvldStartInd);

   // verify UE admission
   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MO_SIGNALLING, 1, 62, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_DELAY_TOLERANT, 1, 63, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 64, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MT_ACCESS, 1, 65, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;
 
   downAndDeleteMme(pstApplObj,1);
}

TEST_F(CApplicationTest, handle_ACB_mmeOveLoad_permitHighPrio_mtAcc_enableMoSigMoData)
{
   RmuMmeOvldStartInd *pMmeOvldStartInd = (RmuMmeOvldStartInd*)malloc(sizeof(RmuCommonMsg));
   RmuUeAdmitReq     *admitReq;

   addMme(pstApplObj,1);

   pMmeOvldStartInd->enMmeOvldStatus = RMU_MME_PERMITONLY_HIGHPRI_MTACCESS;
   pMmeOvldStartInd->usMmeId = 1;

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0x00;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0x00;
   pstApplObj->processFsmMsg(EVTRMUOVLDSTRTIND, (U8*)pMmeOvldStartInd);

   // verify UE admission
   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MO_SIGNALLING, 1, 62, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_DELAY_TOLERANT, 1, 63, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 64, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MT_ACCESS, 1, 65, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS, 1, 66, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;

   downAndDeleteMme(pstApplObj,1);
}

TEST_F(CApplicationTest, handle_ACB_mmeOveLoad_rejDelayTol_enableMoSigMoData)
{
   RmuMmeOvldStartInd *pMmeOvldStartInd = (RmuMmeOvldStartInd*)malloc(sizeof(RmuCommonMsg));
   RmuUeAdmitReq     *admitReq;

   addMme(pstApplObj,1);

   pMmeOvldStartInd->enMmeOvldStatus = RMU_MME_REJECT_DELAY_TOLERNT_ACCESS;
   pMmeOvldStartInd->usMmeId = 1;

   // set the expect info
   resetEnv();
   pstApplObj->processFsmMsg(EVTRMUOVLDSTRTIND, (U8*)pMmeOvldStartInd);

   // verify UE admission
   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MO_DATA, 1, 61, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MO_SIGNALLING, 1, 62, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_DELAY_TOLERANT, 1, 63, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_FAILURE;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_EMERGENCY, 1, 64, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_MT_ACCESS, 1, 65, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   admitReq = (RmuUeAdmitReq*)malloc(sizeof(RmuUeAdmitReq));
   createAdmitReq(admitReq, RMU_EST_CAUSE_HIGH_PRIORTY_ACCESS, 1, 66, 1);
   resetEnv();
   isUeAdmitRspExpInfoSet = true;
   ueAdmitRspExp.stStatusInfo.enStatus = RMU_SUCCESS;
   pstApplObj->processFsmMsg(EVTRMUUEADMITREQ, (U8*) admitReq);

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;

   downAndDeleteMme(pstApplObj,1);
}

TEST_F(CApplicationTest, handle_mmeOverload_OAM_Override)
{
   RmuMmeOvldStartInd *pMmeOvldStartInd = (RmuMmeOvldStartInd*)malloc(sizeof(RmuCommonMsg));
   RmProtoCfg         stProtoCfg;

   addMme(pstApplObj,1);

   pMmeOvldStartInd->enMmeOvldStatus = RMU_MME_REJECT_MOSIG_MODATA;
   pMmeOvldStartInd->usMmeId = 1;

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;
   pstApplObj->processFsmMsg(EVTRMUOVLDSTRTIND, (U8*)pMmeOvldStartInd);

   stProtoCfg.bCfgType = (LrmCfgType)LRM_CELL_CONFIG;
   stProtoCfg.u.stCellCfg.enCellAddModDel = LRM_CFG_MOD;
   stProtoCfg.u.stCellCfg.usReCfgType = (LRM_CELL_RECFGTYPE_ACB_MODATA |
         LRM_CELL_RECFGTYPE_ACB_MOSIG);
   stProtoCfg.u.stCellCfg.stCellCfgInfo.bCellId = 1;
   stProtoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoSig = false;
   stProtoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoData = false;
   stProtoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbFactor = RM_ACB_FACTOR_P95;
   stProtoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.enAcbTime = RM_ACB_TIME_S4;
   stProtoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoSig.bAcbForSpac = 0xf0;
   stProtoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.bIsacBarringMoData = false;
   stProtoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbFactor = RM_ACB_FACTOR_P95;
   stProtoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.enAcbTime = RM_ACB_TIME_S4;
   stProtoCfg.u.stCellCfg.stCellCfgInfo.stAcbInfo.stAcBarringMoData.bAcbForSpac = 0xf0;
   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = false;
   pstApplObj->processSmMsg(EVTLRMCFGREQ, (U8*)&stProtoCfg);

   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;

   downAndDeleteMme(pstApplObj,1);
}

#if 0
TEST_F(CApplicationTest, handle_ACB_mmeOveLoadStartindDiffCause)
{
   CRrmApplication   *pstApplObj = createApplAndSetUpSingleCell();

   addMme(pstApplObj, 1);
   addMme(pstApplObj, 2);
   addMme(pstApplObj, 3);

   mmeOverloadStartInd(pstApplObj,1,RMU_MME_REJECT_MODATA);
   mmeOverloadStartInd(pstApplObj,2,RMU_MME_REJECT_MOSIG_MODATA);
   
   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = false;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moSig.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moSig.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moSig.spAc = 0xf0;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;
   mmeOverloadStartInd(pstApplObj,3,RMU_MME_PERMITONLY_EMG_MTACCESS);

   delApplObj(pstApplObj);
}
#endif

TEST_F(CApplicationTest, handle_ACB_mmeOveLoadStartindSameCause)
{
   addMme(pstApplObj, 1);
   addMme(pstApplObj, 2);
   addMme(pstApplObj, 3);

  
   mmeOverloadStartInd(pstApplObj,1,RMU_MME_REJECT_MODATA);
   mmeOverloadStartInd(pstApplObj,2,RMU_MME_REJECT_MODATA);
   
   // set the expect info
   resetEnv();
   isCellRecfgIndExpected = true;
   cellRecfgIndExp.u.acbExpInfo.moSig.isEnable = false;
   cellRecfgIndExp.u.acbExpInfo.moData.isEnable = true;
   cellRecfgIndExp.u.acbExpInfo.moData.time = RM_ACB_TIME_S4;
   cellRecfgIndExp.u.acbExpInfo.moData.factor = RM_ACB_FACTOR_P95;
   cellRecfgIndExp.u.acbExpInfo.moData.spAc = 0xf0;
   mmeOverloadStartInd(pstApplObj,3,RMU_MME_REJECT_MODATA);

}

/**********************************************************************
         End of file:     test_rm_application.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:52:05 2016
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
*********************************************************************91*/
