


/**********************************************************************

    Name:   Test file for RRM Module

    Type:   CPP source file

    Desc:   Contains GT test cases for UE Manager Class

    File:   test_rm_uemanager.cpp

    Sid:      test_rm_uemanager.cpp@@/main/tenb_5.0_RIB_GA/5 - Fri Feb 12 12:09:11 2016

    Prg:    sri

**********************************************************************/
#include <limits.h>
#include "gtest/gtest.h"

// File with class that is being tested
#include "test_rm.h"
#include "rm_uemanager.h"

/* The below lines need to be in some common place and not inside the test code
 * */
#ifdef _cplusplus
extern "C" {
   S16 tst();
}
#endif

/* class used to test CL Module functions */
class CUeManagerTest : public ::testing::Test
{
public:
protected:
   virtual void SetUp()
   {
      PRNT_TEST_NAME();
   }

   virtual void TearDown()
   {
   }
};

CUEManager *getUeManagerObj(LrmCellConfigData *stCellConfigData)
{
   return new CUEManager(*stCellConfigData);
}

void freeUeManagerObj(CUEManager *uemngr)
{
   delete uemngr;
}

//////////////////////////////////////////
// Test scenarios starting from here
// //////////////////////////////////////
TEST_F(CUeManagerTest, handle_sig2Act_maxUeReached_rejectNonCsg)
{
   LrmCellConfigData              stCellConfigData;
   CUEManager                     *objUEMngr;
   CUEContext                     *ue61, *ue62, *ue63, *ue64;

   fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);

   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 3;
   stCellConfigData.bMaxSigUesServed         = 5;
   stCellConfigData.usMaxCsgUes              = 3;
   stCellConfigData.usMaxNonCsgUes           = 3;
   stCellConfigData.usMaxExtraUes            = 1;

   objUEMngr = getUeManagerObj(&stCellConfigData);

   ue61 = objUEMngr->admitUE(61, RMU_EST_CAUSE_MO_SIGNALLING);
   ASSERT_EQ(NULL, objUEMngr->moveUEfromSigLstToActiveLst(ue61));

   ue62 = objUEMngr->admitUE(62, RMU_EST_CAUSE_MO_SIGNALLING);
   ue62->setMemberShip(false);
   ASSERT_EQ(NULL, objUEMngr->moveUEfromSigLstToActiveLst(ue62));

   ue63 = objUEMngr->admitUE(63, RMU_EST_CAUSE_MO_SIGNALLING);
   ASSERT_EQ(NULL, objUEMngr->moveUEfromSigLstToActiveLst(ue63));

   ue64 = objUEMngr->admitUE(64, RMU_EST_CAUSE_MO_SIGNALLING);
   ue64->setMemberShip(false);
   ASSERT_EQ(ue64, objUEMngr->moveUEfromSigLstToActiveLst(ue64));

   freeUeManagerObj(objUEMngr);
}

TEST_F(CUeManagerTest, handle_sig2Act_maxUeReached_allowCsg)
{
   LrmCellConfigData              stCellConfigData;
   CUEManager                     *objUEMngr;
   CUEContext                     *ue61, *ue62, *ue63, *ue64;

   fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);

   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 3;
   stCellConfigData.bMaxSigUesServed         = 5;
   stCellConfigData.usMaxCsgUes              = 3;
   stCellConfigData.usMaxNonCsgUes           = 3;
   stCellConfigData.usMaxExtraUes            = 1;

   objUEMngr = getUeManagerObj(&stCellConfigData);

   ue61 = objUEMngr->admitUE(61, RMU_EST_CAUSE_MO_SIGNALLING);
   ASSERT_EQ(NULL, objUEMngr->moveUEfromSigLstToActiveLst(ue61));

   ue62 = objUEMngr->admitUE(62, RMU_EST_CAUSE_MO_SIGNALLING);
   ue62->setMemberShip(false);
   ASSERT_EQ(NULL, objUEMngr->moveUEfromSigLstToActiveLst(ue62));

   ue63 = objUEMngr->admitUE(63, RMU_EST_CAUSE_MO_SIGNALLING);
   ASSERT_EQ(NULL, objUEMngr->moveUEfromSigLstToActiveLst(ue63));

   ue64 = objUEMngr->admitUE(64, RMU_EST_CAUSE_MO_SIGNALLING);
   ASSERT_EQ(ue62, objUEMngr->moveUEfromSigLstToActiveLst(ue64));

   freeUeManagerObj(objUEMngr);
}

TEST_F(CUeManagerTest, handle_sig2Act_maxUeReached_allowNonCsg)
{
   LrmCellConfigData              stCellConfigData;
   CUEManager                     *objUEMngr;
   CUEContext                     *ue61, *ue62, *ue63, *ue64;

   fillCellConfigDataForSpecificConfig(&stCellConfigData, 24);

   /* change the max csg and max active UEs according to the test case */
   stCellConfigData.bMaxActiveUesServed      = 3;
   stCellConfigData.bMaxSigUesServed         = 5;
   stCellConfigData.usMaxCsgUes              = 2;
   stCellConfigData.usMaxNonCsgUes           = 1;
   stCellConfigData.usMaxExtraUes            = 1;

   objUEMngr = getUeManagerObj(&stCellConfigData);

   ue61 = objUEMngr->admitUE(61, RMU_EST_CAUSE_MO_SIGNALLING);
   ASSERT_EQ(NULL, objUEMngr->moveUEfromSigLstToActiveLst(ue61));

   ue62 = objUEMngr->admitUE(62, RMU_EST_CAUSE_MO_SIGNALLING);
   ASSERT_EQ(NULL, objUEMngr->moveUEfromSigLstToActiveLst(ue62));

   ue63 = objUEMngr->admitUE(63, RMU_EST_CAUSE_MO_SIGNALLING);
   ASSERT_EQ(NULL, objUEMngr->moveUEfromSigLstToActiveLst(ue63));

   ue64 = objUEMngr->admitUE(64, RMU_EST_CAUSE_MO_SIGNALLING);
   ue64->setMemberShip(false);
   ASSERT_EQ(ue61, objUEMngr->moveUEfromSigLstToActiveLst(ue64));

   freeUeManagerObj(objUEMngr);
}

/**********************************************************************
         End of file:     test_rm_uemanager.cpp@@/main/tenb_5.0_RIB_GA/5 - Fri Feb 12 12:09:11 2016
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
*********************************************************************91*/




