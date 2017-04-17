


/**********************************************************************

    Name:   Test file for RRM Module

    Type:   CPP source file

    Desc:   Contains GT test cases for PRB report collector

    File:   test_rm_prbreportcollector.cpp

    Sid:      test_rm_rbadmissioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:53 2016

    Prg:    sri

**********************************************************************/
#include <limits.h>
#include "gtest/gtest.h"

// File with class that is being tested
#include "test_rm.h"
#include "rm_prbbasedadmissioncontroller.h"
#include "rm_qcibasedadmissioncontroller.h"
#include "rm_prbreportcollector.h"
#include "rm_rbadmissioncontroller.h"

/* The below lines need to be in some common place and not inside the test code
 * */
#ifdef _cplusplus
extern "C" {
   S16 tst();
}
#endif

CCellManager *cellManager;

/* class used to test CL Module functions */
class CRBAdmissionControllerTest : public ::testing::Test
{
public:
protected:
   virtual void SetUp()
   {
      LrmCellConfigData stCellConfigData;
      
      intializeRlog();
      fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);
      cellManager = getNewCellObj(&stCellConfigData);
   }

   virtual void TearDown()
   {
      freeCellManagerObj(cellManager);
   }
};

CRBAdmissionController *getRbAdmCtrl(LrmCellConfigData &stCellConfigData)
{
   return new CRBAdmissionController(stCellConfigData, cellManager);
}

void freeRbAdmCtrl(CRBAdmissionController *objRbAdmCtrl)
{
   delete objRbAdmCtrl;
}

//////////////////////////////////////////
// Test scenarios starting from here
// //////////////////////////////////////
TEST_F(CRBAdmissionControllerTest, handletrigger_configuration)
{
   LrmCellConfigData              stCellConfigData;
   CRBAdmissionController         *objRbAdmCntlr;
   U8                             idx;

   for(idx = 1; idx < MAX_CELL_CONFIG_DATA; idx++)
   {
      fillCellConfigDataForSpecificConfig(&stCellConfigData, idx);
      objRbAdmCntlr = getRbAdmCtrl(stCellConfigData);
      freeRbAdmCtrl(objRbAdmCntlr);
   }
}

TEST_F(CRBAdmissionControllerTest, handletrigger_rbadmission_qci1)
{
   U8                             idx;
   LrmCellConfigData              stCellConfigData;
   RmuErabConfigIe                stRabConfig;
   RrmRbcRspInfo                  erabRbcRspInfo;
   CRBAdmissionController         *objRbAdmCntlr;
   CUEContext                     *pUE = createUeCb();
   RgmPrbRprtInd                  prbRprtInd;

   for(idx = 1; idx < 2; idx++)
   {
      fillCellConfigDataForSpecificConfig(&stCellConfigData, idx);
      objRbAdmCntlr = getRbAdmCtrl(stCellConfigData);

      prbRprtInd.bCellId = 1;
      prbRprtInd.bPrbUsageMask = 3;
      fillPrbUsage(&prbRprtInd, 0);

      CPRBReportCollector::getInstance().updateQCIsPRBReport(&prbRprtInd);
      erabRbcRspInfo.usCRNTI = 61; 
      fillErabConfigRequest(&stRabConfig, 2, 1, 0);
      objRbAdmCntlr->canRBsBeAdmitted(pUE, 
                                      stRabConfig, 
                                      erabRbcRspInfo);

      EXPECT_EQ(erabRbcRspInfo.nErabsAccepted, 1);
      EXPECT_EQ(erabRbcRspInfo.nErabsRejected, 1);
      freeRbAdmCtrl(objRbAdmCntlr);
   }
   freeUeCb(pUE);
}

/**********************************************************************
         End of file:     test_rm_rbadmissioncontroller.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:53 2016
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
*********************************************************************91*/



