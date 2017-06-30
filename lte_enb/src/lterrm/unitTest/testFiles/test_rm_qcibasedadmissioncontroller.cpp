


/**********************************************************************

    Name:   Test file for RRM Module

    Type:   CPP source file

    Desc:   Contains GT test cases for PRB report collector

    File:   test_rm_prbreportcollector.cpp

    Sid:      test_rm_qcibasedadmissioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:52 2016

    Prg:    sri

**********************************************************************/
#include <limits.h>
#include "gtest/gtest.h"

// File with class that is being tested
#include "test_rm.h"
#include "rm_qcibasedadmissioncontroller.h"
#include "rm_radiobearercontroller.h"

/* The below lines need to be in some common place and not inside the test code
 * */
#ifdef _cplusplus
extern "C" {
   S16 tst();
}
#endif

/* class used to test CL Module functions */
class CQCIBasedAdmissionControllerTest : public ::testing::Test
{
protected:
   virtual void SetUp()
   {
      intializeRlog();
   }

   virtual void TearDown()
   {
   }
};

RmuUErabAddModIe  stRabSetupConfig[] = {
   {{{5, TRUE, TRUE}, {200000, 200000, 200000, 200000}, 1}, 6}, //index 0
   {{{6, TRUE, TRUE}, {200000, 200000, 200000, 200000}, 1}, 7},
   {{{7, TRUE, TRUE}, {200000, 200000, 200000, 200000}, 1}, 8},
   {{{8, TRUE, TRUE}, {200000, 200000, 200000, 200000}, 1}, 9},
   {{{9, TRUE, TRUE}, {200000, 200000, 200000, 200000}, 1}, 10},
   {{{10, FALSE, TRUE}, {200000, 200000, 200000, 200000}, 2}, 11}, //index 5
   {{{2, FALSE, TRUE}, {200000, 200000, 200000, 200000}, 3}, 12},
   {{{3, FALSE, TRUE}, {200000, 200000, 200000, 200000}, 4}, 13},
   {{{4, FALSE, TRUE}, {200000, 200000, 200000, 200000}, 1}, 14},
   {{{14, FALSE, TRUE}, {200000, 200000, 200000, 200000}, 2}, 15},
   {{{12, FALSE, TRUE}, {200000, 200000, 200000, 200000}, 3}, 16}, //index 10
   {{{5, FALSE, TRUE}, {200000, 200000, 200000, 200000}, 1}, 7},
   {{{4, TRUE, FALSE}, {200000, 200000, 200000, 200000}, 1}, 7},
   {{{10, FALSE, TRUE}, {200000, 200000, 200000, 200000}, 5}, 5},
   {{{10, TRUE, TRUE}, {2000000, 2000000, 2000000, 200000}, 1}, 7},
   {{{4, TRUE, FALSE}, {4194304, 3145728, 4195304, 3145728}, 1}, 7}
};

CQCIBasedAdmissionController *getQciAdmCntrlObj(LrmCellConfigData &stCellConfigData)
{
   return new CQCIBasedAdmissionController(stCellConfigData);
}

void freeQciAdmCntrlObj(CQCIBasedAdmissionController *objQciAdmCntlr)
{
   delete objQciAdmCntlr;
}

void fillCellConfigData(LrmCellConfigData *stCellConfigData)
{
   stCellConfigData->bDuplexMode              = RM_MODE_TDD; //RM_MODE_FDD
   stCellConfigData->bNumDlNewUesPerTti       = 2;
   stCellConfigData->bNumUlNewUesPerTti       = 2;
   stCellConfigData->bNumDlReTxUesPerTti      = 1;
   stCellConfigData->bNumUlReTxUesPerTti      = 1;
   stCellConfigData->bRbcQci1TmngReq          = 20;
   stCellConfigData->bRbcQci2TmngReq          = 20;
   stCellConfigData->bRbcQci3TmngReq          = 30;
   stCellConfigData->bRbcQci4TmngReq          = 40;
   stCellConfigData->bRbcQci4TmngReqEnable    = TRUE;
   stCellConfigData->enUlDlConfig             = LRM_UL_DL_CONFIG_2;
   stCellConfigData->bMaxAvgGbrPrbUsage       = 30;
   stCellConfigData->utPrbRptInterval         = 1;
   stCellConfigData->utNumOfPrbRpts           = 20;
   stCellConfigData->bMaxActiveUesServed      = 9;
   stCellConfigData->bMaxSigUesServed         = 9;
   stCellConfigData->usMaxCsgUes              = 9;
   stCellConfigData->usMaxNonCsgUes           = 9;
   stCellConfigData->usMaxExtraUes            = (U32)MAX_EXT_UES;
 }

void fillErabConfigRequest(RmuErabConfigIe *stRabConfig,
                           U8 numRabsToAdd, 
                           U8 qci,
                           U8 index,
                           RmuErabAction enErabAction)
{
   U8                             idx;
   RmuErabArpInfoIe               *stArpInfo;
   RmuErabGbrInfoIe               *stGbrInfo;
   RmuErabArpInfoIe               *stArpInfoDB;
   RmuErabGbrInfoIe               *stGbrInfoDB;

   if(index != 0)
   {
      idx = index;
      stRabConfig->stErabAddModLst[0].bErabId = stRabSetupConfig[idx].bErabId;
      stArpInfo = &(stRabConfig->stErabAddModLst[0].stErabQosInfo.stErabArpInfo);
      stArpInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabArpInfo);
      stArpInfo->bErabPrioLvl    = stArpInfoDB->bErabPrioLvl;
      stArpInfo->bErabPreemptCap = stArpInfoDB->bErabPreemptCap;
      stArpInfo->bErabPreemptVul = stArpInfoDB->bErabPreemptVul;

      stGbrInfo = &(stRabConfig->stErabAddModLst[0].stErabQosInfo.stErabGbrInfo);
      stGbrInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabGbrInfo);
      stGbrInfo->uiErabDlMbr     = stGbrInfoDB->uiErabDlMbr;
      stGbrInfo->uiErabUlMbr     = stGbrInfoDB->uiErabUlMbr;
      stGbrInfo->uiErabDlGbr     = stGbrInfoDB->uiErabDlGbr;
      stGbrInfo->uiErabUlGbr     = stGbrInfoDB->uiErabUlGbr;

      if(qci)
      {
         stRabConfig->stErabAddModLst[0].stErabQosInfo.bErabQCI = qci;
      }
      else
      {
         stRabConfig->stErabAddModLst[0].stErabQosInfo.bErabQCI = 
            stRabSetupConfig[idx].stErabQosInfo.bErabQCI;
      }
      stRabConfig->usNoErabsToAddMod = numRabsToAdd;
      stRabConfig->enErabAction = enErabAction; //RMU_ADD_ERAB;
      stRabConfig->bNoErabsToRel = 0;
      stRabConfig->bIsUeAmbrPres = FALSE;
   }
   else
   {
      for(idx = 0; idx < numRabsToAdd; idx++)
      {
         stRabConfig->stErabAddModLst[idx].bErabId = stRabSetupConfig[idx].bErabId;
         stArpInfo = &(stRabConfig->stErabAddModLst[idx].stErabQosInfo.stErabArpInfo);
         stArpInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabArpInfo);
         stArpInfo->bErabPrioLvl    = stArpInfoDB->bErabPrioLvl;
         stArpInfo->bErabPreemptCap = stArpInfoDB->bErabPreemptCap;
         stArpInfo->bErabPreemptVul = stArpInfoDB->bErabPreemptVul;

         stGbrInfo = &(stRabConfig->stErabAddModLst[idx].stErabQosInfo.stErabGbrInfo);
         stGbrInfoDB = &(stRabSetupConfig[idx].stErabQosInfo.stErabGbrInfo);
         stGbrInfo->uiErabDlMbr     = stGbrInfoDB->uiErabDlMbr;
         stGbrInfo->uiErabUlMbr     = stGbrInfoDB->uiErabUlMbr;
         stGbrInfo->uiErabDlGbr     = stGbrInfoDB->uiErabDlGbr;
         stGbrInfo->uiErabUlGbr     = stGbrInfoDB->uiErabUlGbr;

         if(qci)
         {
            stRabConfig->stErabAddModLst[idx].stErabQosInfo.bErabQCI = qci;
         }
         else
         {
            stRabConfig->stErabAddModLst[idx].stErabQosInfo.bErabQCI = 
               stRabSetupConfig[idx].stErabQosInfo.bErabQCI;
         }
      }
      stRabConfig->usNoErabsToAddMod = numRabsToAdd;
      stRabConfig->enErabAction = enErabAction; //RMU_ADD_ERAB;
      stRabConfig->bNoErabsToRel = 0;
      stRabConfig->bIsUeAmbrPres = FALSE;
   }
}

CUEContext *createUeCb()
{
   CUEContext                     *pUE = NULL;
   return pUE;
}

void freeUeCb(CUEContext *pUE)
{
   free((void*)pUE);
}

TEST_F(CQCIBasedAdmissionControllerTest, handleRab_setup_request_qci1)
{
   bool                           sRet;
   LrmCellConfigData              stCellConfigData;
   CQCIBasedAdmissionController   *objQciAdmCntlr;
   RmuErabConfigIe                stRabConfig;
   RrmRbcRspInfo                  erabRbcRspInfo;

   fillCellConfigData(&stCellConfigData);

   fillErabConfigRequest(&stRabConfig, 8, 1, 0);

   objQciAdmCntlr = getQciAdmCntrlObj(stCellConfigData);

   sRet = objQciAdmCntlr->canRBsBeAdmitted(stRabConfig, erabRbcRspInfo);

   EXPECT_EQ(sRet, TRUE);
   EXPECT_EQ(erabRbcRspInfo.nErabsAccepted, 7);
   EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 1);

   freeQciAdmCntrlObj(objQciAdmCntlr);
}

TEST_F(CQCIBasedAdmissionControllerTest, handleRab_setup_request_qci2)
{
   bool                           sRet;
   LrmCellConfigData              stCellConfigData;
   CQCIBasedAdmissionController   *objQciAdmCntlr;
   RmuErabConfigIe                stRabConfig;
   RrmRbcRspInfo                  erabRbcRspInfo;

   fillCellConfigData(&stCellConfigData);

   objQciAdmCntlr = getQciAdmCntrlObj(stCellConfigData);

   fillErabConfigRequest(&stRabConfig, 8, 2, 0);
   sRet = objQciAdmCntlr->canRBsBeAdmitted(stRabConfig, erabRbcRspInfo);

   EXPECT_EQ(sRet, TRUE);
   EXPECT_EQ(erabRbcRspInfo.nErabsAccepted, 8);
   EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 0);

   /* add number of accepted bearers */
   objQciAdmCntlr->rbAdditionInd(2);
   objQciAdmCntlr->rbAdditionInd(2);
   objQciAdmCntlr->rbAdditionInd(2);
   objQciAdmCntlr->rbAdditionInd(2);
   objQciAdmCntlr->rbAdditionInd(2);
   objQciAdmCntlr->rbAdditionInd(2);
   objQciAdmCntlr->rbAdditionInd(2);
   objQciAdmCntlr->rbAdditionInd(2);

   fillErabConfigRequest(&stRabConfig, 8, 2, 0);
   sRet = objQciAdmCntlr->canRBsBeAdmitted(stRabConfig, erabRbcRspInfo);

   EXPECT_EQ(sRet, TRUE);
   EXPECT_EQ(erabRbcRspInfo.nErabsAccepted, 6);
   EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 2);

   freeQciAdmCntrlObj(objQciAdmCntlr);
}

TEST_F(CQCIBasedAdmissionControllerTest, handleRab_setup_request_qci3)
{
   bool                           sRet;
   LrmCellConfigData              stCellConfigData;
   CQCIBasedAdmissionController   *objQciAdmCntlr;
   RmuErabConfigIe                stRabConfig;
   RrmRbcRspInfo                  erabRbcRspInfo;

   fillCellConfigData(&stCellConfigData);

   objQciAdmCntlr = getQciAdmCntrlObj(stCellConfigData);

   fillErabConfigRequest(&stRabConfig, 8, 3, 0);
   sRet = objQciAdmCntlr->canRBsBeAdmitted(stRabConfig, erabRbcRspInfo);

   EXPECT_EQ(sRet, TRUE);
   EXPECT_EQ(erabRbcRspInfo.nErabsAccepted, 8);
   EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 0);

   /* add number of accepted bearers */
   objQciAdmCntlr->rbAdditionInd(3);
   objQciAdmCntlr->rbAdditionInd(3);
   objQciAdmCntlr->rbAdditionInd(3);
   objQciAdmCntlr->rbAdditionInd(3);
   objQciAdmCntlr->rbAdditionInd(3);
   objQciAdmCntlr->rbAdditionInd(3);
   objQciAdmCntlr->rbAdditionInd(3);
   objQciAdmCntlr->rbAdditionInd(3);

   fillErabConfigRequest(&stRabConfig, 8, 3, 0);
   sRet = objQciAdmCntlr->canRBsBeAdmitted(stRabConfig, erabRbcRspInfo);

   EXPECT_EQ(sRet, TRUE);
   EXPECT_EQ(erabRbcRspInfo.nErabsAccepted, 6);
   EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 2);

   freeQciAdmCntrlObj(objQciAdmCntlr);
}

TEST_F(CQCIBasedAdmissionControllerTest, handleRab_setup_request_qci4)
{
   bool                           sRet;
   LrmCellConfigData              stCellConfigData;
   CQCIBasedAdmissionController   *objQciAdmCntlr;
   RmuErabConfigIe                stRabConfig;
   RrmRbcRspInfo                  erabRbcRspInfo;

   fillCellConfigData(&stCellConfigData);

   objQciAdmCntlr = getQciAdmCntrlObj(stCellConfigData);

   fillErabConfigRequest(&stRabConfig, 8, 4, 0);
   sRet = objQciAdmCntlr->canRBsBeAdmitted(stRabConfig, erabRbcRspInfo);

   EXPECT_EQ(sRet, TRUE);
   EXPECT_EQ(erabRbcRspInfo.nErabsAccepted, 8);
   EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 0);

   /* add number of accepted bearers */
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);

   fillErabConfigRequest(&stRabConfig, 8, 4, 0);
   sRet = objQciAdmCntlr->canRBsBeAdmitted(stRabConfig, erabRbcRspInfo);

   EXPECT_EQ(sRet, TRUE);
   EXPECT_EQ(erabRbcRspInfo.nErabsAccepted, 6);
   EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 2);

   freeQciAdmCntrlObj(objQciAdmCntlr);
}

TEST_F(CQCIBasedAdmissionControllerTest, handleRab_modify_request)
{
   bool                           sRet;
   LrmCellConfigData              stCellConfigData;
   CQCIBasedAdmissionController   *objQciAdmCntlr;
   RmuErabConfigIe                stRabConfig;
   RrmRbcRspInfo                  erabRbcRspInfo;
   CUEContext       *pUE = new CUEContext();
   CERABInfo        *ptrObjERab = new CERABInfo();

   /* add QCI 2 bearer in UE CB */
   pUE->setCRNTI(61);
   fillErabConfigRequest(&stRabConfig, 1, 2, 0);
   ptrObjERab->updateERABInfo(stRabConfig.stErabAddModLst[0], 61);
   pUE->addERAB(ptrObjERab);

   fillCellConfigData(&stCellConfigData);
   objQciAdmCntlr = getQciAdmCntrlObj(stCellConfigData);
 
   /* add max number of QCI 1 bearers in QCI based admission controller */
   objQciAdmCntlr->rbAdditionInd(1);
   objQciAdmCntlr->rbAdditionInd(1);
   objQciAdmCntlr->rbAdditionInd(1);
   objQciAdmCntlr->rbAdditionInd(1);
   objQciAdmCntlr->rbAdditionInd(1);
   objQciAdmCntlr->rbAdditionInd(1);
   objQciAdmCntlr->rbAdditionInd(1);
   objQciAdmCntlr->rbAdditionInd(1);
   objQciAdmCntlr->rbAdditionInd(1);
   objQciAdmCntlr->rbAdditionInd(1);

   fillErabConfigRequest(&stRabConfig, 1, 1, 0, RMU_MOD_ERAB);
   sRet = objQciAdmCntlr->canModifyRBsBeAdmitted(pUE, stRabConfig, erabRbcRspInfo);

   EXPECT_EQ(sRet, FALSE);
   EXPECT_EQ(erabRbcRspInfo.nErabsAccepted, 0);
   EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 1);

   delete pUE;
   delete ptrObjERab;
   freeQciAdmCntrlObj(objQciAdmCntlr);
}

#if 0
//NOTE: All QCI test cases need to relook. since the we cannt receive more than 8 bearers in one incoming request

TEST_F(CQCIBasedAdmissionControllerTest, handleRab_setup_release_request)
{
   bool                           sRet;
   LrmCellConfigData              stCellConfigData;
   CQCIBasedAdmissionController   *objQciAdmCntlr;
   RmuErabConfigIe                stRabConfig;
   RrmRbcRspInfo                  erabRbcRspInfo;

   fillCellConfigData(&stCellConfigData);

   fillErabConfigRequest(&stRabConfig, 9, 4, 0);

   objQciAdmCntlr = getQciAdmCntrlObj(stCellConfigData);

   sRet = objQciAdmCntlr->canRBsBeAdmitted(stRabConfig, erabRbcRspInfo);

   EXPECT_EQ(sRet, TRUE);
   EXPECT_EQ(erabRbcRspInfo.nErabsAccepted, 8);
   EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 1);

   /* since 8 bearers were added, send 8 bearers add ind */
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);
   objQciAdmCntlr->rbAdditionInd(4);

   //cmMemset((U8*)&stRabConfig, 0, sizeof(stRabConfig));
   objQciAdmCntlr->rbReleaseInd(4);

   fillErabConfigRequest(&stRabConfig, 1, 4, 0);

   sRet = objQciAdmCntlr->canRBsBeAdmitted(stRabConfig, erabRbcRspInfo);

   EXPECT_EQ(sRet, TRUE);
   EXPECT_EQ(erabRbcRspInfo.nErabsAccepted, 1);
   EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 0);

   freeQciAdmCntrlObj(objQciAdmCntlr);
}
#endif
TEST_F(CQCIBasedAdmissionControllerTest, handleRab_setup_invalidQCI)
{
   bool                           sRet;
   LrmCellConfigData              stCellConfigData;
   CQCIBasedAdmissionController   *objQciAdmCntlr;
   RmuErabConfigIe                stRabConfig;
   RrmRbcRspInfo                  erabRbcRspInfo;

   fillCellConfigData(&stCellConfigData);

   fillErabConfigRequest(&stRabConfig, 1, 12, 0);

   objQciAdmCntlr = getQciAdmCntrlObj(stCellConfigData);

   sRet = objQciAdmCntlr->canRBsBeAdmitted(stRabConfig, erabRbcRspInfo);

   EXPECT_EQ(sRet, FALSE);
   EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 1);

   freeQciAdmCntrlObj(objQciAdmCntlr);
}

TEST_F(CQCIBasedAdmissionControllerTest, handle_cellConfig_invalid_buplexMode)
{
   LrmCellConfigData              stCellConfigData;
   CQCIBasedAdmissionController   *objQciAdmCntlr;

   fillCellConfigData(&stCellConfigData);
   stCellConfigData.bDuplexMode  = (LrmCellBandwidth) RM_MODE_TDD;
   stCellConfigData.enUlDlConfig = (LrmUlDlConfig) LRM_UL_DL_CONFIG_MAX;

   objQciAdmCntlr = getQciAdmCntrlObj(stCellConfigData);

   freeQciAdmCntrlObj(objQciAdmCntlr);
}


/**********************************************************************
         End of file:     test_rm_qcibasedadmissioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:52 2016
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
*********************************************************************91*/
