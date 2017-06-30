
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_res.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:26 2015

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta.h"
/* cm_xta_res_c_001.main_2 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"

/* cm_xta_res_c_001.main_2 Removed cm_xta_app.x for Psf-Diameter 1.1 */
/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaFailTest
(
Void
)
#else
PUBLIC S16 cmXtaFailTest()
#endif
{
   CmXtaTstGrp *tstGrp;

   TRC2(cmXtaFailTest)

   tstGrp = &cmXtaCb.tstGrp[cmXtaCb.curTstGroup];

   CMXTA_DBG_CALLIND((_cmxtap, "Test %d Failed\n", tstGrp->curTest + 1), 1);

   /* log the result in the test and group control blocks       */
   tstGrp->tstList[tstGrp->curTest].result = CMXTA_TEST_FAILED;
   tstGrp->result = CMXTA_TEST_FAILED;

   RETVALUE(ROK);
} /* cmXtaFailTest */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaIgnoreTest
(
Void
)
#else
PUBLIC S16 cmXtaIgnoreTest()
#endif
{
   CmXtaTstGrp *tstGrp;

   TRC2(cmXtaIgnoreTest)

   tstGrp = &cmXtaCb.tstGrp[cmXtaCb.curTstGroup];

   CMXTA_DBG_CALLIND((_cmxtap, "Test %d Ignored\n", tstGrp->curTest + 1), 1);

   /* log the result in the test and group control blocks       */
   tstGrp->tstList[tstGrp->curTest].result = CMXTA_TEST_IGNORED;
   if ((tstGrp->result != CMXTA_TEST_FAILED) &&
       (tstGrp->result != CMXTA_TEST_PASSED) &&
       (tstGrp->result != CMXTA_TEST_LEAK))
      tstGrp->result = CMXTA_TEST_IGNORED;

   RETVALUE(ROK);
} /* cmXtaIgnoreTest */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaPassTest
(
Void
)
#else
PUBLIC S16 cmXtaPassTest()
#endif
{
   CmXtaTstGrp *tstGrp;

   TRC2(cmXtaPassTest)

   tstGrp = &cmXtaCb.tstGrp[cmXtaCb.curTstGroup];

   CMXTA_DBG_CALLIND((_cmxtap, "Test %d Passed\n", tstGrp->curTest + 1), 1);

   /* log the result in the test and group control blocks       */
   tstGrp->tstList[tstGrp->curTest].result = CMXTA_TEST_PASSED;
   if ((tstGrp->result != CMXTA_TEST_FAILED) &&
       (tstGrp->result != CMXTA_TEST_LEAK))
      tstGrp->result = CMXTA_TEST_PASSED;

   RETVALUE(ROK);
} /* cmXtaPassTest */

/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC Void cmXtaEndTst
(
CmXtaTCCb      *tcCb
)
#else
PUBLIC Void cmXtaEndTst(tcCb)
CmXtaTCCb      *tcCb;
#endif
{
   TRC2(cmXtaEndTst)

   if (tcCb->result == CMXTA_TEST_FAILED)
      cmXtaFailTest();
   else if (tcCb->result == CMXTA_TEST_PASSED)
      cmXtaPassTest();
   else cmXtaIgnoreTest();

   /*-- Check memory leaks for the test cases --*/
   cmXtaCheckMemory(tcCb);

   RETVOID;
} /* cmXtaEndTst */


/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC Void cmXtaResults
(
Void
)
#else
PUBLIC Void cmXtaResults(Void)
#endif
{
   U8           i;                              /* index                */
   U8           memResult;
   U16          j;                              /* index                */
   Bool         first;                          /* index                */

   TRC2(cmXtaResults)

   first = FALSE;
   /* display a pass/fail summary for each executed test     */
   CMXTA_DBG_RES((_cmxtap, "\n\n"));
   CMXTA_DBG_RES((_cmxtap, "TEST RESULT SUMMARY\n"));
   CMXTA_DBG_RES((_cmxtap, "===================\n\n"));

   for (i = 0; i < cmXtaCb.tstGrpCnt; i++)
   {
      if (cmXtaCb.tstGrp[i].state == CMXTA_RUN)
      {
         if (cmXtaCb.tstGrp[i].result == CMXTA_TEST_PASSED)
         {
            /* this test group was performed, display info.     */
            CMXTA_DBG_RES((_cmxtap, "%10d: Test Group [%-65s]: %s\n", i+1, cmXtaCb.tstGrp[i].name, "PASSED"));
         }
         else if (cmXtaCb.tstGrp[i].result == CMXTA_TEST_IGNORED)
         {
            /* this test group was performed, display info.     */
            CMXTA_DBG_RES((_cmxtap, "%10d: Test Group [%-65s]: %s\n", i+1, cmXtaCb.tstGrp[i].name, "IGNORED"));
         }
         else if (cmXtaCb.tstGrp[i].result == CMXTA_TEST_FAILED)
         {
            /* this test group was performed, display info.     */
            CMXTA_DBG_RES((_cmxtap, "%10d: Test Group [%-65s]: %s\n", i+1, cmXtaCb.tstGrp[i].name, "FAILED"));
         }
         else
         {
            /* this test group was performed, display info.     */
            CMXTA_DBG_RES((_cmxtap, "%10d: Test Group [%-65s]: %s\n", i+1, cmXtaCb.tstGrp[i].name, "MEMORY LEAK"));
         }


         first = FALSE;
         if (cmXtaCb.tstGrp[i].result == CMXTA_TEST_FAILED)
         {
           /* print the list of tests failed in this group   */
           CMXTA_DBG_RESIND((_cmxtap, "%10sFailed:\n", ""), 1);
           for (j = 0; j < cmXtaCb.tstGrp[i].numTests; j++)
              if ((cmXtaCb.tstGrp[i].tstList[j].tcSet == TRUE)  &&
                  (cmXtaCb.tstGrp[i].tstList[j].result == CMXTA_TEST_FAILED))
                 CMXTA_DBG_RESIND((_cmxtap,"\t\tTest %3d:\t[%-15s]\n", j+1, "FAILED"     ), 2);
         }

         first = FALSE;
         for (j = 0; j < cmXtaCb.tstGrp[i].numTests; j++)
            if ((cmXtaCb.tstGrp[i].tstList[j].tcSet == TRUE)  &&
                  (cmXtaCb.tstGrp[i].tstList[j].result == CMXTA_TEST_IGNORED))
            {
               if (first == FALSE)
               {
                  CMXTA_DBG_RESIND((_cmxtap, "%10sIgnored:\n", ""), 1);
                  first = TRUE;
               }

               CMXTA_DBG_RESIND((_cmxtap,"\t\tTest %3d:\t[%-15s]\t[%s]\n", j+1, "IGNORED",
                              cmXtaCb.tstGrp[i].tstList[j].flag), 2);
            }

         first = FALSE;
         for (j = 0; j < cmXtaCb.tstGrp[i].numTests; j++)
            if ((cmXtaCb.tstGrp[i].tstList[j].tcSet == TRUE)  &&
                  (cmXtaCb.tstGrp[i].tstList[j].result == CMXTA_TEST_LEAK))
            {
               if (first == FALSE)
               {
                  CMXTA_DBG_RESIND((_cmxtap, "%10sMemory Leaks:\n", ""), 1);
                  first = TRUE;
               }

               memResult = cmXtaCb.tstGrp[i].tstList[j].memResult;

               if (((memResult & CMXTA_TEST_LEAK_CFG) == CMXTA_TEST_LEAK_CFG)       &&
                   ((memResult & CMXTA_TEST_LEAK_RUN) == CMXTA_TEST_LEAK_RUN))
               {
                  CMXTA_DBG_RESIND((_cmxtap,"\t\tTest %3d:\t[%-15s]\n", j+1, "CFG+RT LEAK"), 2);
               }
               else if ((memResult & CMXTA_TEST_LEAK_CFG) == CMXTA_TEST_LEAK_CFG)
               {
                  CMXTA_DBG_RESIND((_cmxtap,"\t\tTest %3d:\t[%-15s]\n", j+1, "MEMORY LEAK"), 2);
               }
               else
               {
                  CMXTA_DBG_RESIND((_cmxtap,"\t\tTest %3d:\t[%-15s]\n", j+1, "RT MEMORY LEAK"), 2);
               }
            }

         CMXTA_DBG_RES((_cmxtap, "\n"));
      }
   }

   CMXTA_DBG_RES((_cmxtap, "\n\n"));

   RETVOID;
} /* cmXtaResults */


/*
*
*       Fun: 
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File:  
*
*/
#ifdef ANSI
PUBLIC Void cmXtaXmlResults
(
Void
)
#else
PUBLIC Void cmXtaXmlResults(Void)
#endif
{
   U8           i;                              /* index                */
   U16          j;                              /* index                */
   Bool         first;                          /* index                */

   TRC2(cmXtaXmlResults)

   first = FALSE;
   /* display a pass/fail summary for each executed test     */
   CMXTA_DBG_RES((_cmxtap, "\n\n"));
   CMXTA_DBG_RESIND((_cmxtap, "<tapa.results>\n\n"), cmXtaCb.xmlIndent);

   for (i = 0; i < cmXtaCb.tstGrpCnt; i++)
   {
      /*-- Get Test group information --*/
      if (cmXtaCb.tstGrp[i].state != CMXTA_RUN)
      {
         CMXTA_DBG_RESIND((_cmxtap, "<tapa.testgroup id=\"%d\" result=\"NOTRUN\">\n",
                      i+1), cmXtaCb.xmlIndent+1);
      }
      else if (cmXtaCb.tstGrp[i].result == CMXTA_TEST_PASSED)
      {
         CMXTA_DBG_RESIND((_cmxtap, "<tapa.testgroup id=\"%d\" result=\"PASSED\">\n",
                      i+1), cmXtaCb.xmlIndent+1);
      }
      else if (cmXtaCb.tstGrp[i].result == CMXTA_TEST_FAILED)
      {
         CMXTA_DBG_RESIND((_cmxtap, "<tapa.testgroup id=\"%d\" result=\"FAILED\">\n",
                      i+1), cmXtaCb.xmlIndent+1);
      }
      else if (cmXtaCb.tstGrp[i].result == CMXTA_TEST_IGNORED)
      {
         CMXTA_DBG_RESIND((_cmxtap, "<tapa.testgroup id=\"%d\" result=\"IGNORED\">\n",
                      i+1), cmXtaCb.xmlIndent+1);
      }

      /*-- Get individual test case information --*/
      if (cmXtaCb.tstGrp[i].state == CMXTA_RUN)
      {
         for (j = 0; j < cmXtaCb.tstGrp[i].numTests; j++)
         {
            if (cmXtaCb.tstGrp[i].tstList[j].tcSet == TRUE)
            {
               if (cmXtaCb.tstGrp[i].tstList[j].result == CMXTA_TEST_PASSED)
               {
                  CMXTA_DBG_RESIND((_cmxtap, "<tapa.testcase id=\"%d.%d\" result=\"PASSED\"/>\n",
                               i+1, j+1), cmXtaCb.xmlIndent+2);
               }
               else if (cmXtaCb.tstGrp[i].tstList[j].result == CMXTA_TEST_FAILED)
               {
                  CMXTA_DBG_RESIND((_cmxtap, "<tapa.testcase id=\"%d.%d\" result=\"FAILED\"/>\n",
                               i+1, j+1), cmXtaCb.xmlIndent+2);
               }
               else if (cmXtaCb.tstGrp[i].tstList[j].result == CMXTA_TEST_IGNORED)
               {
                  CMXTA_DBG_RESIND((_cmxtap, "<tapa.testcase id=\"%d.%d\" result=\"IGNORED\"/>\n",
                               i+1, j+1), cmXtaCb.xmlIndent+2);
               }
               else if (cmXtaCb.tstGrp[i].tstList[j].result == CMXTA_TEST_NONE)
               {
                  CMXTA_DBG_RESIND((_cmxtap, "<tapa.testcase id=\"%d.%d\" result=\"NOTRUN\"/>\n",
                              i+1, j+1), cmXtaCb.xmlIndent+2);
               }
            }
         }
      }
      else
      {
         for (j = 0; j < cmXtaCb.tstGrp[i].numTests; j++)
         {
            if (cmXtaCb.tstGrp[i].tstList[j].tcSet == TRUE)
            {
               CMXTA_DBG_RESIND((_cmxtap, "<tapa.testcase id=\"%d.%d\" result=\"NOTRUN\"/>\n",
                            i+1, j+1), cmXtaCb.xmlIndent+2);
            }
         }
      }

      CMXTA_DBG_RESIND((_cmxtap, "</tapa.testgroup>\n\n"), cmXtaCb.xmlIndent+1);
   }

   CMXTA_DBG_RESIND((_cmxtap, "</tapa.results>\n"), cmXtaCb.xmlIndent);
   CMXTA_DBG_RESIND((_cmxtap, "\n\n"), cmXtaCb.xmlIndent);

   RETVOID;
} /* cmXtaXmlResults */

/********************************************************************30**

         End of file:     cm_xta_res.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:26 2015

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

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/2      ----     up  1. Main release
/main/3      ---- cm_xta_res_c_001.main_2 nh 1. Updated for Psf-Diameter 1.1
                          release Removed cm_xta_app.[hx]
*********************************************************************91*/
