


/**********************************************************************

    Name:   Test file for RRM Module

    Type:   CPP source file

    Desc:   Contains GT test cases for Pre-Emptable ERAB Finder class.

    File:   test_rm_preemptableErabFinder.cpp

    Sid:      test_rm_preemptableErabFinder.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:51 2016

    Prg:    sri

**********************************************************************/
#include <limits.h>
#include "gtest/gtest.h"

// File with class that is being tested
#include "test_rm.h"
#include "rm_preEmptableERABFinder.h"

/* The below lines need to be in some common place and not inside the test code
 * */
#ifdef _cplusplus
extern "C" {
   S16 tst();
}
#endif

/* class used to test CL Module functions */
class CPreEmptableERABFinderTest : public ::testing::Test
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

CPreEmptableERABFinder *getNewPreemptableErabFinderObj(
                                  LrmCellConfigData &stCellConfigData)
{
   return new CPreEmptableERABFinder(stCellConfigData);
}

void freePreemptableErabFinderObj(CPreEmptableERABFinder *pstErabFinderObj)
{
   delete pstErabFinderObj;
}

//////////////////////////////////////////
// Test scenarios starting from here
// //////////////////////////////////////
TEST_F(CPreEmptableERABFinderTest, handle_non_radio_resource_available_case)
{
   LrmCellConfigData         stCellConfigData;
   CPreEmptableERABFinder    *pstErabFinderObj;
   RmuErabConfigIe           stRabConfig;
   RrmRbcRspInfo             erabRbcRspInfo;
   CERABInfoLst              preEmptedERABs;

   fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);
   pstErabFinderObj = getNewPreemptableErabFinderObj(stCellConfigData);

   fillErabConfigRequest(&stRabConfig, 5, 1, 0);

   erabRbcRspInfo.nErabsRejected = 1;
   erabRbcRspInfo.eRabRejectedLst[0].uiReqPrbForDl = 2;
   erabRbcRspInfo.eRabRejectedLst[0].uiReqPrbForUl = 3;
   erabRbcRspInfo.eRabRejectedLst[0].bArpVal      = 5;
   erabRbcRspInfo.eRabRejectedLst[0].bCause       = RMU_CAUSE_INVALID_QOS_COMB;
   erabRbcRspInfo.eRabRejectedLst[0].bERabId      = 6;
   erabRbcRspInfo.eRabRejectedLst[0].bIsPreemptable  = false;
   erabRbcRspInfo.eRabRejectedLst[0].bErabPreemptCap = false;
   erabRbcRspInfo.eRabRejectedLst[0].bIsModifyReq = false;

   pstErabFinderObj->findPreEmptableERABs(true, erabRbcRspInfo, preEmptedERABs);

   freePreemptableErabFinderObj(pstErabFinderObj);
}

/**********************************************************************
 End of file:     test_rm_preemptableErabFinder.cpp@@/main/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:51:51 2016
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
*********************************************************************91*/
