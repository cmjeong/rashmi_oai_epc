
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_tgfsm.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:29 2015

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
/* cm_xta_tgfsm_c_001.main_3 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"

/* cm_xta_tgfsm_c_001.main_3 Removed cm_xta_app.x for Psf-Diameter 1.1 */
PUBLIC CmXtaTGFsm  cmXtaTGFsm [CMXTA_MAX] =
{
   cmXtaTGFsmS0,           /* CMXTA_START_INIT          */
   cmXtaTGFsmS1,           /* CMXTA_START_CFG     */
   cmXtaTGFsmS2,           /* CMXTA_END_CFG       */
   cmXtaTGFsmS3,           /* CMXTA_START_RUN     */
   cmXtaTGFsmS4,           /* CMXTA_END_RUN       */
   cmXtaTGFsmS5,           /* CMXTA_START_CLN     */
   cmXtaTGFsmS6,           /* CMXTA_END_CLN       */
   cmXtaTGFsmS7,           /* CMXTA_SHUTDOWN      */
};

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
PUBLIC S16 cmXtaTGReq
(
S16             ret
)
#else
PUBLIC S16 cmXtaTGReq(ret)
S16             ret;
#endif
{
   TRC2(cmXtaTGReq)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTGReq(): Enter TG FSM\n"));

   /* Enter cmd STM */
   while (TRUE)
   {
      ret = cmXtaTGFsm [cmXtaCb.grpState](ret);

      /*-- Check if complete or wait for external
           events --*/
      if ((ret == CMXTA_ERR_PENDING)  ||
          (ret == CMXTA_ERR_COMPLETE))
         break;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaInitReq */

/*-----------------  Base Incoming Command Handler FSM ----------------*/

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
PUBLIC S16 cmXtaTGFsmS0
(
S16              ret
)
#else
PUBLIC S16 cmXtaTGFsmS0(ret)
S16              ret;
#endif
{
   CmXtaXmlCb *xmlCb;
   Txt str[100];

   TRC2(cmXtaTGFsmS0)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTGFsmS0(): ret(%d)\n", ret));

   /*-- Get the first Test Group in FsmS0, get the individual test cases in
        FsmS3 --*/
   /*-- Check if last test group --*/
   if (cmXtaTGGetNxt() >= cmXtaCb.tstGrpCnt)
   {
      /*-- Set state --*/
      cmXtaCb.grpState = CMXTA_START_CLN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   sprintf(str, "%d", cmXtaCb.curTstGroup+1);

   if ((xmlCb = cmXtaXmlFind(cmXtaCb.curTstGroup+1, 0, str, TRUE)) == NULLP)
   {
      /*-- No test case found, cleanup --*/
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTGFsmS0(): XML test group (%s) not found\n", str));

      /*-- Mark STM error --*/
      cmXtaCb.TGErr = TRUE;

      /*-- Do cleanup and exit --*/
      cmXtaCb.grpState = CMXTA_SHUTDOWN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   cmXtaCb.curTGCb = xmlCb;

   /*-- Check if doc steps exists for the test group --*/
   if (xmlCb->t.xmlTG.doc != NULLP)
      cmXtaXmlGetDoc(xmlCb, xmlCb->t.xmlTG.doc, xmlCb->t.xmlTG.pre);

   /*-- Move to the next FSM --*/
   /*-- Set state --*/
   cmXtaCb.grpState = CMXTA_START_CFG;

   /*-- Return end of processing --*/
   RETVALUE(CMXTA_ERR_CONTINUE);
}

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
PUBLIC S16 cmXtaTGFsmS1
(
S16              ret
)
#else
PUBLIC S16 cmXtaTGFsmS1(ret)
S16              ret;
#endif
{
   CmXtaTCCb  *tcCb;
   Bool grpNoShutDownMod;

   TRC2(cmXtaTGFsmS1)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTGFsmS1(): ret(%d)\n", ret));

   grpNoShutDownMod = FALSE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_GRPNOSHUTDOWN) == CMXTA_TA_MODE_GRPNOSHUTDOWN)
      grpNoShutDownMod = TRUE;

   /*-- Check if network topology cfg required --*/
   /* modified for stability testing -- rer */
   if ((grpNoShutDownMod == FALSE) && (cmXtaCb.mode != CMXTA_TA_MODE_LOOP))
   {
      /*-- Default mode, the configuration will happen from
           the respective test cases, skip --*/

      /*-- Set state --*/
      cmXtaCb.grpState = CMXTA_START_RUN;

      /*-- Set state --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   /*-- If we reach here, we have to initiate the cfg procedures --*/
   /*-- Set state --*/
   cmXtaCb.grpState = CMXTA_END_CFG;

   CMXTA_DBG_CALL((_cmxtap, "\nTG Configuration:\n"));
   CMXTA_DBG_CALL((_cmxtap, "-----------------\n"));

   /*-- Do network topology cfg from here in case of not shutdown mode --*/
   if ((tcCb = cmXtaTCCreate(CMXTA_CTXT_TG, 0, 0, cmXtaCb.curTGCb->t.xmlTG.cfg)) == NULLP)
   {
      /*-- No TA cfg steps, proceed to run --*/
      /*-- Set state --*/

      CMXTA_DBG_CALLIND((_cmxtap, " Info      : No steps, skip\n"), 3);

      /*-- Set state --*/
      cmXtaCb.grpState = CMXTA_START_RUN;

      /*-- Set state --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTGFsmS1(): Triggering TC FSM\n"));

   /*-- Set default tcCb in the curTCCb --*/
   cmXtaCb.curTCCb = tcCb;

   if ((ret = cmXtaTCReq(tcCb, CMXTA_ERR_NONE)) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTGFsmS1(): TC FSM call failed, initiate cleanup\n"));

      /*-- Mark STM error --*/
      cmXtaCb.TGErr = TRUE;

      /*-- Do cleanup and exit --*/
      cmXtaCb.grpState = CMXTA_SHUTDOWN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   /*-- Return end of processing --*/
   RETVALUE(CMXTA_ERR_PENDING);
}

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
PUBLIC S16 cmXtaTGFsmS2
(
S16              ret
)
#else
PUBLIC S16 cmXtaTGFsmS2(ret)
S16              ret;
#endif
{
   Bool grpNoShutDownMod;

   TRC2(cmXtaTGFsmS2)

   grpNoShutDownMod = FALSE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_GRPNOSHUTDOWN) == CMXTA_TA_MODE_GRPNOSHUTDOWN)
      grpNoShutDownMod = TRUE;

   /*-- Check if any resource/internal error --*/
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTGFsmS2(): TG FSM failed, initiate cleanup\n"));

      /*-- Mark STM error --*/
      cmXtaCb.TGErr = TRUE;

      cmXtaCb.grpState = CMXTA_SHUTDOWN;
   }

   /*-- Check if TA level cfg failed, then skip running TC
        do a shutdown and return --*/

   /*-- If we are here, it means we are in default mode --*/
   /*-- Check the result of the cfg steps --*/
   if (cmXtaCb.result == CMXTA_TEST_FAILED)
   {
      /*-- Configuration failed, no point running test steps,
           do a shutdown of the system and exit, note we are 
           not even trying to do a cleanup of the system here,
           ideally we should do that though --*/
      cmXtaCb.grpState = CMXTA_SHUTDOWN;
   }
   else
   {
      cmXtaCb.grpState = CMXTA_START_RUN;

      /*-- Network topology is skipped or it is successful. Lets
        start the test cases --*/
      if (grpNoShutDownMod == TRUE)
      {
         CMXTA_DBG_CALL((_cmxtap, "\nTG Run Tests:\n"));
         CMXTA_DBG_CALL((_cmxtap,   "-------------\n"));
      }
   }


   /*-- Return end of processing --*/
   RETVALUE(CMXTA_ERR_CONTINUE);
}

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
PUBLIC S16 cmXtaTGFsmS3
(
S16              ret
)
#else
PUBLIC S16 cmXtaTGFsmS3(ret)
S16              ret;
#endif
{
   CmXtaTstGrp      *tg;                            /* test group cntrl blk */
   CmXtaTCCb *tcCb;

   TRC2(cmXtaTGFsmS3)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTGFsmS3(): ret(%d)\n", ret));

   /*-- Find the next test case --*/
   while (TRUE)
   {
      tg = &cmXtaCb.tstGrp[cmXtaCb.curTstGroup];

      /*-- Check if last test case in the group --*/
      if (cmXtaTCGetNxt() >= tg->endTest)
      {
         /*-- Go back to run the next test group in the list --*/
         /*-- Set state --*/
         cmXtaCb.grpState = CMXTA_START_INIT;

         /*-- Return end of processing --*/
         RETVALUE(CMXTA_ERR_CONTINUE);
      }
      else
         break;
   }

   /*-- Change the STM state before invoking the TG STM --*/
   cmXtaCb.grpState = CMXTA_END_RUN;

   if ((tcCb = cmXtaTCCreate(CMXTA_CTXT_TC, cmXtaCb.curTstGroup, tg->curTest, NULLP)) == NULLP)
   {
      /*-- Set error --*/
      cmXtaCb.TGErr = TRUE;

      /*-- Set state --*/
      cmXtaCb.grpState = CMXTA_SHUTDOWN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTGFsmS3(): Triggering TC FSM\n"));

   /*-- Set default tcCb in the curTCCb --*/
   cmXtaCb.curTCCb = tcCb;

   if ((ret = cmXtaTCReq(tcCb, CMXTA_ERR_NONE)) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTGFsmS3(): TC FSM call failed, initiate cleanup\n"));

      /*-- Mark STM error --*/
      cmXtaCb.TGErr = TRUE;

      cmXtaCb.grpState = CMXTA_SHUTDOWN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   /*-- Return end of processing --*/
   RETVALUE(CMXTA_ERR_PENDING);
}

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
PUBLIC S16 cmXtaTGFsmS4
(
S16              ret
)
#else
PUBLIC S16 cmXtaTGFsmS4(ret)
S16              ret;
#endif
{
   Bool grpNoShutDownMod;

   TRC2(cmXtaTGFsmS4)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTGFsmS4(): ret(%d)\n", ret));

   grpNoShutDownMod = FALSE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_GRPNOSHUTDOWN) == CMXTA_TA_MODE_GRPNOSHUTDOWN)
      grpNoShutDownMod = TRUE;

   /*-- Check if any resource/internal error --*/
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTGFsmS4(): TC FSM returned failure, initiate cleanup\n"));

      /*-- Mark STM error --*/
      cmXtaCb.TGErr = TRUE;

      cmXtaCb.grpState = CMXTA_SHUTDOWN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   /*-- Go back to run the next test case in the list --*/
   cmXtaCb.grpState = CMXTA_START_RUN;

   /*-- Return end of processing --*/
   RETVALUE(CMXTA_ERR_CONTINUE);
}

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
PUBLIC S16 cmXtaTGFsmS5
(
S16              ret
)
#else
PUBLIC S16 cmXtaTGFsmS5(ret)
S16              ret;
#endif
{
   CmXtaTCCb *tcCb;
   Bool loopMode;
   Bool grpNoShutDownMod;

   TRC2(cmXtaTGFsmS5)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTGFsmS5(): ret(%d)\n", ret));

   loopMode = FALSE;
   grpNoShutDownMod = FALSE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_LOOP) == CMXTA_TA_MODE_LOOP)
      loopMode = TRUE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_GRPNOSHUTDOWN) == CMXTA_TA_MODE_GRPNOSHUTDOWN)
      grpNoShutDownMod = TRUE;

   /*-- Check if network topology cfg required --*/
   if (grpNoShutDownMod == FALSE)
   {
      /*-- Set state --*/
      cmXtaCb.grpState = CMXTA_SHUTDOWN;

      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   /* In case of test cases running in loop, restart the test cases */
   if (loopMode == TRUE)
   {
      /*-- Check if max loop reached --*/
      if (++cmXtaCb.loopCnt < cmXtaCb.maxLoopCnt)
      {
         /*-- Max loop not reached, restart the loop, in case of
              default mode, CFG state is not required and in case
              of no shutdown, the CLN state would not have been
              executed, hence directly jump to running the test
              cases --*/
         cmXtaCb.grpState = CMXTA_START_RUN;

         /*-- Init/ReInit the TG and TCs --*/
         cmXtaTGInit();

         CMXTA_DBG_INFO((_cmxtap, "cmXtaTGFsmS5(): Starting the next TG loop cnt(%d)\n", 
                      cmXtaCb.loopCnt));

         /*-- Return end of processing --*/
         RETVALUE(CMXTA_ERR_CONTINUE);
      }
   }

   /*-- If we reach here, we have to initiate the cleanup procedures --*/
   /*-- Set state --*/
   cmXtaCb.grpState = CMXTA_END_CLN;

   /*-- If we reach here, we have to initiate the cleanup procedures --*/
   CMXTA_DBG_CALL((_cmxtap, "\nTG Cleanup:\n"));
   CMXTA_DBG_CALL((_cmxtap, "------------\n"));

   /*-- Do network topology cleanup from here in case of not group shutdown mode --*/
   if ((tcCb = cmXtaTCCreate(CMXTA_CTXT_TG, 0, 0, cmXtaCb.curTGCb->t.xmlTG.shutdown)) == NULLP)
   {
      /*-- No TG cfg steps, proceed to run --*/
      /*-- Set state --*/

      CMXTA_DBG_CALLIND((_cmxtap, " Info      : No steps, skip\n"), 3);

      /*-- Set state --*/
      cmXtaCb.grpState = CMXTA_SHUTDOWN;

      /*-- Set state --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTGFsmS5(): Triggering TC FSM\n"));

   /*-- Set default tcCb in the curTCCb --*/
   cmXtaCb.curTCCb = tcCb;

   if ((ret = cmXtaTCReq(tcCb, CMXTA_ERR_NONE)) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTGFsmS5(): TC FSM call failed, initiate cleanup\n"));

      /*-- Mark STM error --*/
      cmXtaCb.TGErr = TRUE;

      /*-- Do cleanup and exit --*/
      cmXtaCb.grpState = CMXTA_SHUTDOWN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   /*-- Return end of processing --*/
   RETVALUE(CMXTA_ERR_PENDING);
}

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
PUBLIC S16 cmXtaTGFsmS6
(
S16              ret
)
#else
PUBLIC S16 cmXtaTGFsmS6(ret)
S16              ret;
#endif
{
   TRC2(cmXtaTGFsmS6)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTGFsmS6(): ret(%d)\n", ret));

   /*-- Check if any resource/internal error --*/
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTGFsmS6(): TG cleanup failed, shutdown anyway\n"));

      /*-- Mark STM error --*/
      cmXtaCb.TGErr = TRUE;
   }

   /*-- Set state --*/
   cmXtaCb.grpState = CMXTA_SHUTDOWN;

   /*-- Return end of processing --*/
   RETVALUE(CMXTA_ERR_CONTINUE);
}

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
PUBLIC S16 cmXtaTGFsmS7
(
S16              ret
)
#else
PUBLIC S16 cmXtaTGFsmS7(ret)
S16              ret;
#endif
{
   TRC2(cmXtaTGFsmS7)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTGFsmS7(): ret(%d)\n", ret));

   /*-- Even if there was an internal error, lets show
        the result for the test cases we ran till now --*/
   if (cmXtaCb.directives.xmlOutput == TRUE)
      cmXtaXmlResults();
   else
      cmXtaResults();

   /*-- TG STM finished, lets revert back to TA STM --*/
   /*-- Check if error set --*/
   if ((cmXtaCb.TGErr == TRUE)   ||
       (cmXtaCb.result == CMXTA_TEST_FAILED))
      cmXtaTAReq(RFAILED);
   else
      cmXtaTAReq(CMXTA_ERR_NONE);

   RETVALUE(CMXTA_ERR_COMPLETE);
}

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
PUBLIC S16 cmXtaTGInit
( 
)
#else
PUBLIC S16 cmXtaTGInit()
#endif
{
   U16          i;                              /* test case index      */
   U16          j;                              /* test case index      */
   CmXtaTstGrp      *tg;                            /* test group cntrl blk */

   TRC2(cmXtaTGInit)

   /*-- Start from the first group (again) --*/
   cmXtaCb.curTstGroup = -1;

   /* initialize remaining elements of test group control block */
   for (j = 0; j < cmXtaCb.tstGrpCnt; j++)
   {
      tg = &cmXtaCb.tstGrp[j];

      for (i = 0; i < tg->numTests; i++)
         if (tg->tstList[i].tcSet == TRUE)
            tg->tstList[i].result = CMXTA_TEST_NONE;

      tg->testsDone = 0;
      tg->result    = CMXTA_TEST_NONE;
      tg->curTest   = tg->startTest;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaTGInit */

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
PUBLIC S16 cmXtaTGGetNxt
(
)
#else
PUBLIC S16 cmXtaTGGetNxt()
#endif
{
   TRC2(cmXtaTGGetNxt)

   /* Find next Tst Group control block */
   for (++cmXtaCb.curTstGroup; cmXtaCb.curTstGroup < cmXtaCb.tstGrpCnt; cmXtaCb.curTstGroup++)
   {
      if (cmXtaCb.tstGrp[cmXtaCb.curTstGroup].state == CMXTA_RUN)
         break;
   }

   RETVALUE(cmXtaCb.curTstGroup);
} /* cmXtaTGGetNxt */

/********************************************************************30**

         End of file:     cm_xta_tgfsm.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:29 2015

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
/main/3      ---      rer 1. Corrected stability testing checks.
/main/4      ---- cm_xta_tgfsm_c_001.main_3 jj 1. Updated for Psf-Diameter 1.1
                          release Removed cm_xta_app.[hx]
*********************************************************************91*/
