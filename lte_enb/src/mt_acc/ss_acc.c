/********************************************************************20**

     Name:     System Services --Acceptance Test

     Type:     C source file

     Desc:     Acceptance Test Engine for 4GMX SSI.

     File:     ss_acc.c

     Sid:      ss_acc.c@@/main/1 - Mon Aug 29 22:31:39 2011

     Prg:

*********************************************************************21*/

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "rb_common.h"
#include "ss_acc.h"
#include "ss_acc.x"
/* control variables for testing */

/* private variable declarations */
PUBLIC S16 test0ActvInit ARGS((Ent ent,Inst inst,Region region, Reason reason));
PUBLIC S16 test0ActvTsk ARGS((Pst *pst,Buffer *mBuf));
PRIVATE S32 testMain ARGS((Void)); 
PRIVATE S32 testSRegTTsk ARGS((U32 tcNum));
PRIVATE S32 testSCreateSTsk ARGS((U32 tcNum));
PRIVATE S32 testSAttachTTsk ARGS((U32 tcNum));
PRIVATE S32 testICpu ARGS((U32 tcNum));
PRIVATE Void printTestResults ARGS((Void));
PRIVATE Void executeTests ARGS((Void));
PRIVATE Void populateTests ARGS((Void));

TestCase unitTest[MAX_TESTS];
SSTskId sTskId[5];

RbAccCb accCb;

/*
 * Acceptance test engine provides a framework to execute test
 * cases in SSI. Test case in acceptance engine is executed as:
 * while testcase-available
 *  pre-requisite()
 *  test-function()
 *  post-requisite()
 * end
 */

/*
 *
 *       Fun:   rdConQ
 *
 *       Desc:  Reads the console queue.
 *
 *       Ret:   None
 *
 *       Notes: None
 *
 *       File:  ss_acc.c
 *
 */
#ifdef ANSI
PUBLIC S16 rdConQ
(
Data data
)
#else
PUBLIC S16 rdConQ(data)
Data data;
#endif
{
   TRC2(rdConQ)

   /* check if control-c */
   if (data == 0x03)
   {
#ifdef NU
      ExitProcess(1);
#endif
   }
   RETVALUE(ROK);
}


/*
 *
 *       Fun:    test0ActvInit() 
 *
 *       Desc:   This is task0 initialization function. 
 *
 *       Ret:    ROK, RFAILED
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PUBLIC S16 test0ActvInit
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
Region reg,                 /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 test0ActvInit(ent, inst, reg, reason)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
Region reg;                 /* region */
Reason reason;              /* reason */
#endif
{
   TRC2(test0ActvInit)

   UNUSED(ent);
   UNUSED(inst);
   UNUSED(reg);
   UNUSED(reason);

   RETVALUE(ROK);

} /* end of test0ActvInit */


/*
 *
 *       Fun:    test0ActvTsk() 
 *
 *       Desc:   This is task0 Activation function.
 *
 *       Ret:    ROK, RFAILED
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PUBLIC S16 test0ActvTsk
(
Pst *pst,                   /* post */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 test0ActvTsk(pst, mBuf)
Pst *pst;                   /* post */
Buffer *mBuf;               /* message buffer */
#endif
{
   PRIVATE S32 count0 = 0;

   TRC2(test0ActvTsk)

      printf("[%s:%d] message received from L-ARM\n",__func__,__LINE__);

   if(mBuf)
   {
      if(ROK!= SPutMsg(mBuf))
      {
         printf("SPutMsg() Failed:[%s:%d] \n", __func__, __LINE__);
         RETVALUE(ROK);
      }
   }

   RETVALUE(ROK);
} /* end of test0ActvTsk */


/*
 *
 *       Fun:    testSRegInit() 
 *
 *       Desc:   This function tests SRegInit() API. 
 *
 *       Ret:    PASS, FAIL
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PRIVATE S32 testSRegInit
(
U32 tcNum
)
#else
PRIVATE S32 testSRegInit(tcNum)
U32 tcNum;
#endif
{
   if( ROK != SRegInit(TST0ENT ,TSTINST0,test0ActvInit))
   {
      return FAIL;
   }

   return PASS;
}


/*
 *
 *       Fun:    testSRegActvTsk() 
 *
 *       Desc:   This function tests SRegActvTsk() API. 
 *
 *       Ret:    PASS, FAIL
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PRIVATE S32 testSRegActvTsk
(
U32 tcNum
)
#else
PRIVATE S32 testSRegActvTsk(tcNum)
U32 tcNum;
#endif
{
   if( ROK != SRegActvTsk(TST0ENT, TSTINST0, TTNORM, PRIOR0, test0ActvTsk) )
   {
      return FAIL;
   }
   return PASS;
}


/*
 *
 *       Fun:    testSRegTTsk() 
 *
 *       Desc:   Function Tests registration of TAPA tasks.
 *
 *       Ret:    PASS, FAIL
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PRIVATE S32 testSRegTTsk
(
U32 tcNum
)
#else
PRIVATE S32 testSRegTTsk(tcNum)
U32 tcNum;
#endif
{
   S16 ret;

   ret = SRegTTsk(TST0ENT, TSTINST0, TTNORM,
         PRIOR0,test0ActvInit, test0ActvTsk);
   if( ret != ROK)
   {
      printf("Failed in registering test0ActvTsk Task\n");
      return FAIL;
   }

   return PASS;
}


/*
 *
 *       Fun:    testSCreateSTsk() 
 *
 *       Desc:   This function tests SCreateSTsk() API.
 *
 *       Ret:    PASS, FAIL
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PRIVATE S32 testSCreateSTsk
(
U32 tcNum
)
#else
PRIVATE S32 testSCreateSTsk(tcNum)
U32 tcNum;
#endif
{
   S16 ret;

   printf("%s:%d\n",__func__,__LINE__);
   ret = SCreateSTsk(SS_NORM_TSK_PRI, &sTskId[0]);

   if(ret != ROK)
   {
      return FAIL;
   }
   return PASS;
}


/*
 *
 *       Fun:    testSAttachTTsk() 
 *
 *       Desc:   This function tests SAttachTTsk() API.
 *
 *       Ret:    PASS, FAIL
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PRIVATE S32 testSAttachTTsk
(
U32 tcNum
)
#else
PRIVATE S32 testSAttachTTsk(tcNum)
U32 tcNum;
#endif
{
   S16 ret0;
   S16 ret1;
   S16 ret2;
   S16 ret3;

   printf("%s:%d\n",__func__,__LINE__);
   ret0 = SAttachTTsk(TST0ENT, TSTINST0, sTskId[0]);
   if(ROK != ret0)
   {
      return FAIL;
   }
   return PASS;
}


/*
 *
 *       Fun:   testICpu() 
 *
 *       Desc:   This function tests SPstTsk API.
 *
 *       Ret:    PASS, FAIL
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PRIVATE S32 testICpu 
(
U32 tcNum
)
#else
PRIVATE S32 testICpu(tcNum)
U32 tcNum;
#endif
{
   S16 ret;
   Pst pst;
   Buffer *myBuf;
   Data srcBuf[] = "hello msg from testSPstTsk";

   SGetMsg(DFLT_REGION,0,&myBuf);
   SAddPstMsgMult(srcBuf, (MsgLen)sizeof(srcBuf), myBuf);

   pst.event     = 0;               /* event */
   pst.prior     = 0;              /* priority */
   pst.route     = 0;               /* route */
   pst.dstProcId = IARM_PROCESSOR_ID_LOW;    /* destination processor id */
   pst.dstEnt    = TST0ENT;         /* destination entity */
   pst.dstInst   = TSTINST0;        /* destination instance */
   pst.srcProcId = SFndProcId();    /* source processor id */
   pst.srcEnt    = TST0ENT;         /* source entity */
   pst.srcInst   = TSTINST0;        /* source instance */

   if (SPstTsk(&pst, myBuf) != ROK)
   {
      printf("SPstTsk Failed pst:line:%d\n",__LINE__);
      return FAIL;
   }
   printf("%s:%d Msg has sent from (0,0)->(2,0)\n",__func__,__LINE__);

   return PASS;
}


/*
 *
 *       Fun:    tst() 
 *
 *       Desc:   This function is entry point for task registration
 *
 *       Ret:    ROK, RFAILED
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PUBLIC S16 tst
(
Void
)
#else
PUBLIC S16 tst()
#endif
{
   SSetProcId(MT_PROCESSOR_ID_LOW);
   uarmInit();
   uarmDrvrInit();
   testMain();
   return ROK;
}


/*
 *
 *       Fun:    printTestResults() 
 *
 *       Desc:  This function prints test results. 
 *
 *       Ret:    ROK, RFAILED
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PRIVATE Void printTestResults
(
Void
)
#else
PRIVATE Void printTestResults(Void)
#endif
{
   S32  tstCnt = 0;
   S32  numPass = 0;
   S32  numFail = 0;
   S16  index = 0;

   printf("\nTest Results:\n");
   printf("id\tname%14s\tstatus\n", " ");
   for (tstCnt = 0; tstCnt < MAX_TESTS; tstCnt++)
   {
      /* Valid test case is identified by testFunc availability */
      if (unitTest[tstCnt].testFunc != NULL)
      {
         /* Collect results of tests */
         (unitTest[tstCnt].result)?  numFail++:numPass++;
         printf("%d\t%-16s\t%s\n", tstCnt, unitTest[tstCnt].tcName, (unitTest[tstCnt].result)? "FAIL" : "PASS");
      }
   }
   printf("Total Tests: %d\t Tests Passed: %d\tTests Failed: %d\n",numPass+numFail, numPass, numFail);

   return;
}


/*
 *
 *       Fun:    executeTests() 
 *
 *       Desc:  This test function execute all test cases. 
 *
 *       Ret:    ROK, RFAILED
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PRIVATE Void executeTests
(
Void
)
#else
PRIVATE Void executeTests(Void)
#endif
{
   S32 idx = 0;
   S32 ret = 0;

   for (idx = 0; idx < MAX_TESTS; idx++)
   {
      /* Valid test case is identified by testFunc availability */
      if (unitTest[idx].testFunc != NULL)
      {
         /* Run pre requisites */
         if (unitTest[idx].preReq != NULL)
         {
            ret = unitTest[idx].preReq(idx);
            if (ret != PASS)
            {
               unitTest[idx].result = FAIL;
               continue;
            }
         }

         /* Collect results of tests */
         ret = unitTest[idx].testFunc(idx);
         if (ret != PASS)
         {
            unitTest[idx].result = FAIL;
            continue;
         }

         /* Run post requisites */
         if (unitTest[idx].postReq != NULL)
         {
            ret = unitTest[idx].postReq(NULL);
            if (ret != PASS)
            {
               unitTest[idx].result = FAIL;
               continue;
            }
         }

         unitTest[idx].result = PASS;
      }
   }

   return;
}


/*
 *
 *       Fun:    populateTests() 
 *
 *       Desc:   This function populate all the test cases.
 *
 *       Ret:    ROK, RFAILED
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PRIVATE Void populateTests
(
Void
)
#else
PRIVATE Void populateTests(Void)
#endif
{
   S32 indx = 0;
   indx++; DEFAULT_TEST_INIT(&unitTest[indx], indx, "SRegTTsk() Test", testSRegTTsk,NULL,NULL);
   indx++; DEFAULT_TEST_INIT(&unitTest[indx], indx, "SCreateSTsk() Test", testSCreateSTsk,NULL,NULL);
   indx++; DEFAULT_TEST_INIT(&unitTest[indx], indx, "SAttachTTsk() Test", testSAttachTTsk,NULL,NULL);
   indx++; DEFAULT_TEST_INIT(&unitTest[indx], indx, "testICpu() Test", testICpu,NULL,NULL);
   return;
}


/*
 *
 *       Fun:    testMain() 
 *
 *       Desc:   This is main function and this entry point os test engine.
 *
 *       Ret:    ROK, RFAILED
 *
 *       Notes:  None.
 *
 *       File:   rb_acc.c
 *
 */
#ifdef ANSI
PUBLIC S32 testMain
(
)
#else
PUBLIC S32 testMain()
#endif
{

   /* Populate all the test cases */
   populateTests();

   /* Get the test case results */
   executeTests();

   printTestResults();
   return 0;
}


/********************************************************************30**

         End of file:     ss_acc.c@@/main/1 - Mon Aug 29 22:31:39 2011

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

   ver        pat        init                  description
---------  ---------  ----------  -------------------------------------
/main/1      --------     ------    1. Initial release
*********************************************************************91*/
