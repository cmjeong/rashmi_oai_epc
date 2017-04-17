


/**********************************************************************

    Name:   Test file for RRM Module

    Type:   CPP source file

    Desc:   Contains GT test cases for PRB report collector

    File:   test_rm_prbreportcollector.cpp

    Sid:      test_rm_prbreportcollector.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:51 2016

    Prg:    sri

**********************************************************************/
#include <limits.h>
#include "gtest/gtest.h"

// File with class that is being tested
#include "rm_prbreportcollector.h"
#include "rgm.x"
#include "test_rm.h"

/* The below lines need to be in some common place and not inside the test code
 * */
#ifdef _cplusplus
extern "C" {
   S16 tst();
}
#endif

/* class used to test CL Module functions */
class CPrbReportCollectorTest : public ::testing::Test
{
public:
   RgmPrbRprtInd   *prbRprtInd;
protected:
   virtual void SetUp()
   {
      PRNT_TEST_NAME();
      prbRprtInd = (RgmPrbRprtInd*) malloc(sizeof(RgmPrbRprtInd));
      CPRBReportCollector::getInstance().configurePRBReportCollector(
            10, 5);
   }

   virtual void TearDown()
   {
      free((void*)prbRprtInd);
   }
};

struct prbUsageTable
{
   U8 qci[4];
   U8 dlUsage[4];
   U8 ulUsage[4];
   U8 expectedDLTotal;
   U8 expectedULTotal;
};

prbUsageTable usageTable[] = {
   {{1, 2, 3, 4}, {5, 5, 5, 5}, {5, 5, 5, 5}, 20, 20}, //0
   {{1, 2, 3, 4}, {15, 15, 15, 15}, {15, 15, 15, 15}, 40, 40}, //1
   {{1, 2, 3, 4}, {3, 4, 5, 6}, {7, 8, 9, 10}, 33, 38},//2
   {{1, 2, 3, 4}, {5, 5, 5, 5}, {5, 5, 5, 5}, 30, 34},//3
   {{1, 2, 3, 4}, {15, 15, 15, 15}, {10, 10, 10, 10}, 36, 35},//4
   {{1, 2, 3, 4}, {6, 6, 6, 6}, {6, 6, 6, 6}, 36, 36}//replaces 0 - index added mainly to understand testcase handlePrb_usage_report
};

void fillPrbUsage(RgmPrbRprtInd *usageInfo, int i)
{
   int j;
   for(j = 0; j < RRM_MAX_GBR_QCIS; j++)
   {
      usageInfo->stQciPrbRpts[j].bQci = usageTable[i].qci[j];
      usageInfo->stQciPrbRpts[j].bAvgPrbDlUsage = usageTable[i].dlUsage[j];
      usageInfo->stQciPrbRpts[j].bAvgPrbUlUsage = usageTable[i].ulUsage[j];
   }
}

TEST_F(CPrbReportCollectorTest, handlePrb_usage_report)
{
   int i;
   int size = (sizeof(usageTable) / sizeof(prbUsageTable));

   for(i = 0; i < size; i++)
   {
      prbRprtInd->bCellId = 1;
      prbRprtInd->bPrbUsageMask = 3;
      fillPrbUsage(prbRprtInd, i);

      CPRBReportCollector::getInstance().updateQCIsPRBReport(prbRprtInd);
      EXPECT_EQ(CPRBReportCollector::getInstance().getCurrentGbrDlPrbUsage(),
            usageTable[i].expectedDLTotal);
      EXPECT_EQ(CPRBReportCollector::getInstance().getCurrentGbrUlPrbUsage(),
            usageTable[i].expectedULTotal);
   }
}

TEST_F(CPrbReportCollectorTest, handlePrb_for_last_slot)
{
      prbRprtInd->bCellId = 1;
      prbRprtInd->bPrbUsageMask = 3;
      fillPrbUsage(prbRprtInd, 0);

      CPRBReportCollector::getInstance().updateQCIsPRBReport(prbRprtInd);
      CPRBReportCollector::getInstance().getCurrentGbrUlPrbUsage(8);
 
}
/**********************************************************************
         End of file:     test_rm_prbreportcollector.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:51 2016
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
*********************************************************************91*/

