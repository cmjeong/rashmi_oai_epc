
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_tcfsm.c@@/main/TeNB_Main_BR/2 - Thu Apr 24 17:04:59 2014

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include <Python.h>
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta.h"
/* cm_xta_tcfsm_c_001.main_8 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"
/* cm_xta_tcfsm_c_001.main_8 Removed cm_xta_app.x for Psf-Diameter 1.1 */
#include "cm_xta_py.x"

PUBLIC CmXtaTCFsm  cmXtaTCFsm [CMXTA_MAX] =
{
   cmXtaTCFsmS0,           /* CMXTA_START_INIT          */
   cmXtaTCFsmS1,           /* CMXTA_START_CFG     */
   cmXtaTCFsmS2,           /* CMXTA_END_CFG       */
   cmXtaTCFsmS3,           /* CMXTA_START_RUN     */
   cmXtaTCFsmS4,           /* CMXTA_END_RUN       */
   cmXtaTCFsmS5,           /* CMXTA_START_CLN     */
   cmXtaTCFsmS6,           /* CMXTA_END_CLN       */
   cmXtaTCFsmS7,           /* CMXTA_SHUTDOWN      */
   cmXtaTCFsmS8,           /* CMXTA_END_SHUTDOWN  */
   cmXtaTCFsmS9,           /* CMXTA_START_EXT,    */
   cmXtaTCFsmS10,          /* CMXTA_END_EXT       */
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
PUBLIC S16 cmXtaTCReq
(
CmXtaTCCb           *tcCb,
S16               ret
)
#else
PUBLIC S16 cmXtaTCReq(tcCb, ret)
CmXtaTCCb           *tcCb;
S16             ret;
#endif
{
   TRC2(cmXtaTCReq)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCReq(): Enter TC FSM\n"));

   while (TRUE)
   {
      ret = cmXtaTCFsm [tcCb->state](tcCb, ret);

      /*-- Check if complete or wait for external
           events --*/
      if ((ret == CMXTA_ERR_PENDING)  ||
          (ret == CMXTA_ERR_COMPLETE))
         break;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaTCReq */

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
PUBLIC S16 cmXtaTCFsmS0
(
CmXtaTCCb           *tcCb,
S16               ret
)
#else
PUBLIC S16 cmXtaTCFsmS0(tcCb, ret)
CmXtaTCCb           *tcCb;
S16               ret;
#endif
{
   Bool dfltMode;

   TRC2(cmXtaTCFsmS0)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCFsmS0(): ret(%d)\n", ret));

   dfltMode = FALSE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_DFLT) == CMXTA_TA_MODE_DFLT)
      dfltMode = TRUE;

   /*-- First time in the test case execution --*/

   /*-- Check if doc steps exists for the test case --*/
   if (tcCb->xmlCb->t.xmlTC.doc != NULLP)
      cmXtaXmlGetDoc(tcCb->xmlCb, tcCb->xmlCb->t.xmlTC.doc, tcCb->xmlCb->t.xmlTC.pre);

   /*-- Validate the feature/flag dependencies here --*/
   if ((ret = cmXtaTCValidatePre(tcCb, tcCb->xmlCb->t.xmlTC.pre)) != ROK)
   {
      /*-- Flag dependency not met, do not run the TC --*/
      CMXTA_DBG_CALLIND((_cmxtap, "Ignored   : TC dependencies not met\n"), 3);

      /*-- Mark the test case as ignored, and return --*/
      tcCb->result = CMXTA_TEST_IGNORED;

      tcCb->state = CMXTA_END_SHUTDOWN;
#ifdef CM_XTA_PSF
      /*SO_ENHANCE */
      tcCb->shTxnId = 0;
#endif
      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   /*-- Check we have to show the SSI memory usage here --*/
   cmXtaLogXml(tcCb, CMXTA_MEM_TC_INIT);

   /*-- Move to the next FSM --*/
   /*-- Set state --*/
   tcCb->state = CMXTA_START_CFG;

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
PUBLIC S16 cmXtaTCFsmS1
(
CmXtaTCCb           *tcCb,
S16               ret
)
#else
PUBLIC S16 cmXtaTCFsmS1(tcCb, ret)
CmXtaTCCb           *tcCb;
S16               ret;
#endif
{
   Bool dfltMode;
   CmXtaSpCb *spCb;

   TRC2(cmXtaTCFsmS1)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCFsmS1(): ret(%d)\n", ret));

   dfltMode = FALSE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_DFLT) == CMXTA_TA_MODE_DFLT)
      dfltMode = TRUE;

   CMXTA_DBG_CALL((_cmxtap, "\nConfiguration:\n"));
   CMXTA_DBG_CALL((_cmxtap, "--------------\n"));

   /*-- Check if network topology cfg required --*/
   if (dfltMode == FALSE)
   {
      /*-- Non-Default mode, the configuration would have 
           happenend from the TA or TG STM already, skip --*/

      /*-- No cfg steps to be execute, proceed to run --*/
      /*-- Set state --*/

      CMXTA_DBG_CALLIND((_cmxtap, " Info      : Skip cfg steps\n"), 3);

      /*-- Set state --*/
      tcCb->state = CMXTA_START_RUN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }
   else
   {
      /*-- Check if cfg steps exists for the test case --*/
      if (tcCb->xmlCb->t.xmlTC.cfg == NULLP)
      {
         /*-- No cfg steps, proceed to run --*/
         /*-- Set state --*/

         CMXTA_DBG_CALLIND((_cmxtap, " Info      : No steps, skip\n"), 3);

         tcCb->state = CMXTA_START_RUN;

         /*-- Return end of processing --*/
         RETVALUE(CMXTA_ERR_CONTINUE);
      }
      else
      {
         /*-- Reset stack pointer --*/
         cmXtaTCSpReset(tcCb);

         /* Find the cfg step for the test case and associate it with 
            the present step stack */
         spCb = &tcCb->stack[tcCb->sp];

         cmXtaTCSpInit(tcCb, spCb, tcCb->xmlCb->t.xmlTC.cfg);

         /*-- Set state --*/
         tcCb->state = CMXTA_END_CFG;

         /*-- Call Tst Engine --*/
         if ((ret = cmXtaTCEngine(tcCb)) != CMXTA_ERR_NONE)
         {
            CMXTA_DBG_FATAL((_cmxtap, "cmXtaTCFsmS1(): Test Engine failure, initiate cleanup\n"));

            /*-- Mark TC STM error --*/
            tcCb->err = TRUE;

            /*-- Set state --*/
            tcCb->state = CMXTA_END_SHUTDOWN;

            /*-- Return end of processing --*/
            RETVALUE(CMXTA_ERR_CONTINUE);
         }
      }
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
PUBLIC S16 cmXtaTCFsmS2
(
CmXtaTCCb           *tcCb,
S16               ret
)
#else
PUBLIC S16 cmXtaTCFsmS2(tcCb, ret)
CmXtaTCCb           *tcCb;
S16               ret;
#endif
{
   TRC2(cmXtaTCFsmS2)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCFsmS2(): ret(%d)\n", ret));

   /*-- Check if any resource/internal error --*/
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTCFsmS2(): Test Engine failure, initiate cleanup\n"));

      /*-- Mark TC STM error --*/
      tcCb->err = TRUE;

      /*-- Set state --*/
      tcCb->state = CMXTA_END_SHUTDOWN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   /*-- If we are here, it means we are in default mode --*/
   /*-- Check the result of the cfg steps --*/
   if (tcCb->result == CMXTA_TEST_FAILED)
   {
      /*-- Configuration failed, no point running test steps or cleanup,
           do a shutdown and move to the next step --*/
      tcCb->state = CMXTA_SHUTDOWN;
   }
   else
      tcCb->state = CMXTA_START_RUN;

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
PUBLIC S16 cmXtaTCFsmS3
(
CmXtaTCCb           *tcCb,
S16               ret
)
#else
PUBLIC S16 cmXtaTCFsmS3(tcCb, ret)
CmXtaTCCb           *tcCb;
S16               ret;
#endif
{
   CmXtaSpCb *spCb;

   TRC2(cmXtaTCFsmS3)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCFsmS3(): ret(%d)\n", ret));

   /*-- Load mode for TA --*/

   /*-- Only tapa.test or tapa.load steps are considered for load
        purposes --*/

   /*-- Load mode may start in two ways :
        1. User start in load mode by giving the appropriate mode
           from the command line. In this case, all the steps in
           tapa.test or tapa.load will be considered as load steps.

        2. User steps into load mode by setting the tapa.directive.
           All the steps after the directives will be considered
           as load steps --*/

   /*-- In case of load mode, the TC Engine parses all test steps
        and forms optimized test steps for the load scenarios --*/

   /*-- The load will start after this through external load 
        generator entites. TA shall just go to sleep at this step
        and wait for a trigger at the end of the load completion.

        The easiest way to do this is to ignore this trigger and 
        assume that a new trigger will be sent later.

        At the end of the load generation, the load caluculating
        module shall post a message back to the main TA engine
        to resume further process (cleanup and shutdown). This 
        may done in the middle as well from the user input (by
        reading rdConQ) 
        
        We can not use the mode for finding out if the load mode
        is enabled because the users may not want to optimize all
        the steps for load mode. The way TA handles this is that 
        in load mode, only tapa.load or tapa.test section is 
        considered as in being load mode. So set a flag in the
        TA --*/

   /*-- Do note that the only way to come out of load mode is
        through user intervention. Once you come out of the load
        mode, only cleanup and shutdown steps are executed and
        the system is brought down --*/

   /*-- Check if we are in load mode --*/
   if ((cmXtaCb.mode & CMXTA_TA_MODE_LOAD) == CMXTA_TA_MODE_LOAD)
   {
      cmXtaCb.loadDir.loadMode = TRUE;

      /*-- Internal flag to mark that the TA was running in
           load mode once upon a time. When this flag is 
           set, TA skips cleanup steps and instead jumps
           to shutdown steps --*/
      cmXtaCb.loadDir.loadStarted = TRUE;
   }

   CMXTA_DBG_CALL((_cmxtap, "\nTest:\n"));
   CMXTA_DBG_CALL((_cmxtap, "-----\n"));

   /*-- Check we have to show the SSI memory usage here --*/
   cmXtaLogXml(tcCb, CMXTA_MEM_TC_RUN);

   /*-- Check if test steps exists for the test case --*/
   if (tcCb->xmlCb->t.xmlTC.test == NULLP)
   {
      CMXTA_DBG_CALLIND((_cmxtap, " Info      : No steps, skip\n"), 3);

      /*-- No test steps, go to cleanup --*/
      /*-- Set state --*/
      tcCb->state = CMXTA_START_CLN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }
   else
   {
      /*-- Set state --*/
      tcCb->state = CMXTA_END_RUN;

      /*-- Reset stack pointer --*/
      cmXtaTCSpReset(tcCb);

      /* Find the cfg step for the test case and associate it with 
         the present step stack */
      spCb = &tcCb->stack[tcCb->sp];

      cmXtaTCSpInit(tcCb, spCb, tcCb->xmlCb->t.xmlTC.test);

      /*-- Call Tst Engine --*/
      if ((ret = cmXtaTCEngine(tcCb)) != CMXTA_ERR_NONE)
      {
         CMXTA_DBG_FATAL((_cmxtap, "cmXtaTCFsmS3(): Test Engine failure, initiate cleanup\n"));

         /*-- Mark TC STM error --*/
         tcCb->err = TRUE;

         /*-- Set state --*/
         tcCb->state = CMXTA_END_SHUTDOWN;

         /*-- Return end of processing --*/
         RETVALUE(CMXTA_ERR_CONTINUE);
      }
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
PUBLIC S16 cmXtaTCFsmS4
(
CmXtaTCCb           *tcCb,
S16               ret
)
#else
PUBLIC S16 cmXtaTCFsmS4(tcCb, ret)
CmXtaTCCb           *tcCb;
S16               ret;
#endif
{
   TRC2(cmXtaTCFsmS4)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCFsmS4(): ret(%d)\n", ret));

   /*-- Check if any resource/internal error --*/
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTCFsmS4(): Test Engine failure, initiate cleanup\n"));

      /*-- Mark TC STM error --*/
      tcCb->err = TRUE;

      /*-- Set state --*/
      tcCb->state = CMXTA_END_SHUTDOWN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   /*-- Load mode for TA --*/

   /*-- In case of load mode, the TC Engine parses all test steps
        and forms optimized test steps for the load scenarios --*/

   /*-- The load will start after this through external load 
        generator entites. TA shall just go to sleep at this step
        and wait for a trigger at the end of the load completion.

        The easiest way to do this is to ignore this trigger and 
        assume that a new trigger will be sent later.

        At the end of the load generation, the load caluculating
        module shall post a message back to the main TA engine
        to resume further process (cleanup and shutdown). This 
        may done in the middle as well from the user input (by
        reading rdConQ) --*/
   if (cmXtaCb.loadDir.loadMode == TRUE)
   {
      CMXTA_DBG_INFO((_cmxtap, "cmXtaTCFsmS4(): TA in load mode, suspending TA, ret(%d)\n", ret));

      RETVALUE(CMXTA_ERR_PENDING);
   }
   else if (cmXtaCb.loadDir.loadStarted == TRUE)
   {
      /*-- Internal flag to mark that the TA was running in
           load mode once upon a time. When this flag is 
           set, TA skips cleanup steps and instead jumps
           to shutdown steps --*/
      /*-- Set state --*/
      tcCb->state = CMXTA_SHUTDOWN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   /*-- No load mode, business as usual --*/

   /*-- If test failed, cleanup may fail too, give it a
           best shot still, --*/
   /*-- Set state --*/
   tcCb->state = CMXTA_START_CLN;

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
PUBLIC S16 cmXtaTCFsmS5
(
CmXtaTCCb           *tcCb,
S16               ret
)
#else
PUBLIC S16 cmXtaTCFsmS5(tcCb, ret)
CmXtaTCCb           *tcCb;
S16               ret;
#endif
{
   CmXtaSpCb *spCb;

   TRC2(cmXtaTCFsmS5)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCFsmS5(): ret(%d)\n", ret));

   CMXTA_DBG_CALL((_cmxtap, "\nCleanup:\n"));
   CMXTA_DBG_CALL((_cmxtap, "--------\n"));

   /*-- Check if clean steps exists for the test case --*/
   if (tcCb->xmlCb->t.xmlTC.clean == NULLP)
   {
      CMXTA_DBG_CALLIND((_cmxtap, " Info      : No steps, skip\n"), 3);

      /*-- Check we have to show the SSI memory usage here --*/
      cmXtaLogXml(tcCb, CMXTA_MEM_TC_CLEAN);

      /*-- No clean steps, proceed to shutdown --*/
      /*-- Set state --*/
      tcCb->state = CMXTA_SHUTDOWN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }
   else
   {
      /*-- Set state --*/
      tcCb->state = CMXTA_END_CLN;

      /*-- Reset stack pointer --*/
      cmXtaTCSpReset(tcCb);

      /* Find the cfg step for the test case and associate it with 
         the present step stack */
      spCb = &tcCb->stack[tcCb->sp];

      cmXtaTCSpInit(tcCb, spCb, tcCb->xmlCb->t.xmlTC.clean);

      /*-- Call Tst Engine --*/
      if ((ret = cmXtaTCEngine(tcCb)) != CMXTA_ERR_NONE)
      {
         CMXTA_DBG_FATAL((_cmxtap, "cmXtaTCFsmS5(): Test Engine failure, initiate cleanup\n"));

         /*-- Mark TC STM error --*/
         tcCb->err = TRUE;

         /*-- Set state --*/
         tcCb->state = CMXTA_END_SHUTDOWN;

         /*-- Return end of processing --*/
         RETVALUE(CMXTA_ERR_CONTINUE);
      }
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
PUBLIC S16 cmXtaTCFsmS6
(
CmXtaTCCb           *tcCb,
S16               ret
)
#else
PUBLIC S16 cmXtaTCFsmS6(tcCb, ret)
CmXtaTCCb           *tcCb;
S16               ret;
#endif
{
   TRC2(cmXtaTCFsmS6)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCFsmS6(): ret(%d)\n", ret));

   /*-- Check we have to show the SSI memory usage here --*/
   cmXtaLogXml(tcCb, CMXTA_MEM_TC_CLEAN);

   /*-- Check if any resource/internal error --*/
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTCFsmS6(): Test Engine failure, initiate cleanup\n"));

      /*-- Mark TC STM error --*/
      tcCb->err = TRUE;

      /*-- Set state --*/
      tcCb->state = CMXTA_END_SHUTDOWN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   /*-- Set state --*/
   tcCb->state = CMXTA_SHUTDOWN;

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
PUBLIC S16 cmXtaTCFsmS7
(
CmXtaTCCb           *tcCb,
S16               ret
)
#else
PUBLIC S16 cmXtaTCFsmS7(tcCb, ret)
CmXtaTCCb           *tcCb;
S16               ret;
#endif
{
   Bool dfltMode;
   CmXtaSpCb *spCb;

   TRC2(cmXtaTCFsmS7)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCFsmS7(): ret(%d)\n", ret));

   dfltMode = FALSE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_DFLT) == CMXTA_TA_MODE_DFLT)
      dfltMode = TRUE;

   CMXTA_DBG_CALL((_cmxtap, "\nShutdown:\n"));
   CMXTA_DBG_CALL((_cmxtap, "---------\n"));

   /*-- Check if we have to delay all the shutdown steps. We 
        may have already delayed shutdown steps as well and
        we may be coming to resume to shutdown procedure.
        Check for all the conditions --*/

   if ((tcCb->directives.delayShutDown == TRUE) &&
       (tcCb->delayShutDownTmr   == FALSE))
   {
      /*-- We have to delay the shutdown steps and we are coming
           here for the first time. We may be coming in failing
           scenarios as well. We do not care for the result, the
           shutdown will be delayed for all successful and non
           successful scenarios --*/

      /*-- Delayed Test Shutdown mode --*/
      tcCb->delayShutDownTmr = TRUE;

      /*-- Run the delayTest timer --*/
      cmXtaStartTmr(CMXTA_TMR_DELAY_SHUTDOWN, tcCb, cmXtaCb.delayTstShutDownVal);

      /*-- Flag dependency not met, do not execute the step --*/
      CMXTA_DBG_CALLIND((_cmxtap, " Info      : Delay before Shutdown for delay=%d\n",
                      cmXtaCb.delayTstShutDownVal), 3);

      /*-- Return a positive value here, since you do
        not know which function has triggered the
        engine, better handle it using TC Callback
        as done above --*/
      RETVALUE(CMXTA_ERR_PENDING);
   }
   else
   {
      /*-- We have to delay the shutdown steps and we are coming
        here for the second time (ie we have already paused
        for the timer value and now we should proceed with 
        shutdown steps

        Or

        We are not delaying shutdown steps, proceed with the
        shutdown steps --*/

      /*-- Delayed Test Shutdown mode --*/
      tcCb->delayShutDownTmr = FALSE;

      /*-- Check if network topology cfg required --*/
      if (dfltMode == FALSE)
      {
         /*-- Non-Default mode, the shutdown would
           happen from the TA or TG STM, skip --*/
         CMXTA_DBG_CALLIND((_cmxtap, " Info      : Skip shutdown steps\n"), 3);

         /*-- Set state --*/
         tcCb->state = CMXTA_END_SHUTDOWN;

         /*-- Return end of processing --*/
         RETVALUE(CMXTA_ERR_NONE);
      }
      else
      {
         /*-- Check if shutdown steps exists for the test case --*/
         if (tcCb->xmlCb->t.xmlTC.shutdown == NULLP)
         {
            CMXTA_DBG_CALLIND((_cmxtap, " Info      : No steps, skip\n"), 3);

            /*-- Set state --*/
            tcCb->state = CMXTA_END_SHUTDOWN;

            /*-- Return end of processing --*/
            RETVALUE(CMXTA_ERR_NONE);
         }
         else
         {
            /*-- Set state --*/
            tcCb->state = CMXTA_END_SHUTDOWN;

            /*-- Reset stack pointer --*/
            cmXtaTCSpReset(tcCb);

            /* Find the cfg step for the test case and associate it with 
               the present step stack */
            spCb = &tcCb->stack[tcCb->sp];

            cmXtaTCSpInit(tcCb, spCb, tcCb->xmlCb->t.xmlTC.shutdown);

            /*-- Call Tst Engine --*/
            if ((ret = cmXtaTCEngine(tcCb)) != CMXTA_ERR_NONE)
            {
               CMXTA_DBG_FATAL((_cmxtap, "cmXtaTCFsmS7(): Test Engine failure, initiate cleanup\n"));

               /*-- Mark TC STM error --*/
               tcCb->err = TRUE;

               /*-- Return end of processing --*/
               RETVALUE(CMXTA_ERR_CONTINUE);
            }
         }
      }
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
PUBLIC S16 cmXtaTCFsmS8
(
CmXtaTCCb           *tcCb,
S16               ret
)
#else
PUBLIC S16 cmXtaTCFsmS8(tcCb, ret)
CmXtaTCCb           *tcCb;
S16               ret;
#endif
{
   U8 err;

   TRC2(cmXtaTCFsmS8)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCFsmS8(): ret(%d)\n", ret));

   err = tcCb->err;

   /*-- Check we have to show the SSI memory usage here --*/
   cmXtaLogXml(tcCb, CMXTA_MEM_TC_DEINIT);

   /*-- If we reach here, we are at the end of the test case, check the 
        result --*/
   /*-- Check test case results --*/
   /*-- Mark test case as passed/failed or ignored --*/
   cmXtaEndTst(tcCb);

   /*-- Release TC resources --*/
   cmXtaTCDelete(tcCb);

   /*-- Check if error set --*/
   if (err == TRUE)
   {
      cmXtaTAReq(CMXTA_ERR_INT);

      RETVALUE(CMXTA_ERR_COMPLETE);
   }
   /*-- Check if any resource/internal error --*/
   else if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTCFsmS8(): Test Engine failure, initiate cleanup\n"));

      /*-- Mark TC STM error --*/
      err = TRUE;
   }

   /*-- Trigger the TG STM --*/
   /*-- Check if error set --*/
   if (err == TRUE)
      cmXtaTGReq(CMXTA_ERR_INT);
   else
      cmXtaTGReq(CMXTA_ERR_NONE);

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
PUBLIC S16 cmXtaTCFsmS9
(
CmXtaTCCb           *tcCb,
S16               ret
)
#else
PUBLIC S16 cmXtaTCFsmS9(tcCb, ret)
CmXtaTCCb           *tcCb;
S16               ret;
#endif
{
   CmXtaSpCb *spCb;

   TRC2(cmXtaTCFsmS9)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCFsmS9(): ret(%d)\n", ret));

   /*-- Check if external steps exists for the test case --*/
   if (tcCb->ext == NULLP)
   {
      /*-- No ext steps, proceed to run --*/
      /*-- Set state --*/
      tcCb->state = CMXTA_END_EXT;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }
   else
   {
      /*-- Reset stack pointer --*/
      cmXtaTCSpReset(tcCb);

      /* Find the ext step for the test case and associate it with 
         the present step stack */
      spCb = &tcCb->stack[tcCb->sp];

      /* rer for stability testing */
      cmXtaTCSpInit(tcCb, spCb, tcCb->ext);

      /*-- Set state --*/
      tcCb->state = CMXTA_END_EXT;

      /*-- Call Tst Engine --*/
      if ((ret = cmXtaTCEngine(tcCb)) != CMXTA_ERR_NONE)
      {
         CMXTA_DBG_FATAL((_cmxtap, "cmXtaTCFsmS9(): Test Engine failure, initiate cleanup\n"));

         /*-- Mark TC STM error --*/
         tcCb->err = TRUE;

         /*-- Return end of processing --*/
         RETVALUE(CMXTA_ERR_CONTINUE);
      }
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
PUBLIC S16 cmXtaTCFsmS10
(
CmXtaTCCb           *tcCb,
S16               ret
)
#else
PUBLIC S16 cmXtaTCFsmS10(tcCb, ret)
CmXtaTCCb           *tcCb;
S16               ret;
#endif
{
   U8 err;
   U8 result;
   U8 user;

   TRC2(cmXtaTCFsmS10)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCFsmS10(): ret(%d)\n", ret));

   err = tcCb->err;
   result = tcCb->result;
   user = tcCb->user;

   /*-- Release TC resources --*/
   cmXtaTCDelete(tcCb);

   /*-- Check if error set --*/
   if (err == TRUE)
   {
      if (user == CMXTA_CTXT_TA)
         cmXtaTAReq(CMXTA_ERR_INT);
      else
         cmXtaTGReq(CMXTA_ERR_INT);

      RETVALUE(CMXTA_ERR_COMPLETE);
   }
   /*-- Check if any resource/internal error --*/
   else if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTCFsmS10(): Test Engine failure, initiate cleanup\n"));

      /*-- Mark TC STM error --*/
      err = TRUE;
   }

   /*-- If we reach here, we are at the end of the ext steps, return with the 
        results --*/
   /*-- Check test case results --*/
   if (result == CMXTA_TEST_PASSED)
      /*-- Mark test case as passed --*/
      cmXtaCb.result = CMXTA_TEST_PASSED;
   else
      /*-- Mark test case as failed --*/
      cmXtaCb.result = CMXTA_TEST_FAILED;

   /*-- Trigger the TG STM --*/
   /*-- Check if error set --*/
   if (err == TRUE)
   {
      if (user == CMXTA_CTXT_TA)
         cmXtaTAReq(CMXTA_ERR_INT);
      else
         cmXtaTGReq(CMXTA_ERR_INT);
   }
   else
   {
      if (user == CMXTA_CTXT_TA)
         cmXtaTAReq(CMXTA_ERR_NONE);
      else
         cmXtaTGReq(CMXTA_ERR_NONE);
   }

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
PUBLIC S16 cmXtaTCEngine
(
CmXtaTCCb           *tcCb
)
#else
PUBLIC S16 cmXtaTCEngine(tcCb)
CmXtaTCCb           *tcCb;
#endif
{
   S16  ret;
   CmXtaSpCb *spCb;
   Void *cmd;
   /* cm_xta_tcfsm_c_001.main_6 :Added Initialization */
   Void *curStepLcl=NULLP;
   Void *preStep;
   /* cm_xta_tcfsm_c_001.main_7: Fix for 64bit compilation warning */
   U32  guardTmr;
   Bool  extTrigger;

   TRC2(cmXtaTCEngine)

   /* cm_xta_tcfsm_c_001.main_7: Fix for 64bit compilation warning */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTCEngine(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTCEngine(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   ret = CMXTA_ERR_NONE;

   /*-- Guard timer handling, decide based 
   on step documentation, when guard timer expires, 
   mark a flag and call engine,
   in engine, first check if guard timer, then flag
   error and return,

   if a handler requires timer, then than timer event
   can still queue the message and handle it in its
   handler code --*/

   /*-- We may reach here in three ways 
        1. First time invocation, no message 
        2. Message received, 
           a. Stop the guard timer which may have been
              started earlier
           b. Call the next step to process the message
        3. Guard timer timeout
           a. Expected message not received, call the
              handler to handle the error scenario
    --*/

   /*-- First check for the test delay timer expiry --*/
   if (tcCb->delayTestTmr == TRUE)
   {
      /*-- This is just a delayed exit from the test case, at the end
           of the last test step, TA delayed the exit to take care
           of all the messages generated during the layer shutdowns (if any
           issued) --*/

      /*-- Waiting is over, lets check the results --*/

      /*-- The only check remaining to be done is to look for the messages
           not handled in the TC step and still lying in the TC queue. --*/

      /*-- All steps completed, check there are no
           pending queued messages for the test, if pending messages,
           then flag error, else mark the steps as complete --*/

      /* cm_xta_tcfsm_c_001.main_2 : Multiple queue support */
      /*-- Check if there are any messages waiting in the queue --*/
      if (cmXtaLenMsgQ(&tcCb->msgQ[0]) > 0)
      {
         /*-- More messages are lying in the queue, there could
           be two reasons, either all the messages were not 
           handled in the test case, or someone wrote the rest
           of the expect sequence in the other section of the
           test cases, either case, mark it as failed --*/
         CMXTA_DBG_CALLIND((_cmxtap, " Failed    : Extra unhandled messages in the queue\n"), 3);
         cmXtaDispNFlushQ(&tcCb->msgQ[0]);

         /*-- Mark test case as having failed --*/
         tcCb->result = CMXTA_TEST_FAILED;
      }

      tcCb->delayTestTmr = FALSE;

      /*-- End of the all the steps at all stack levels --*/
      /*-- Trigger the TC STM to continue further --*/
      ret = cmXtaTCReq(tcCb, CMXTA_ERR_NONE);

      RETVALUE(CMXTA_ERR_NONE);
   }
   /*-- Second check for the guard timer expiry --*/

   /*-- A kludge for handling optional messages --*/

   /*-- If a step is optional, then TC Engine skips the optional step if the
     next message in the TC arrives. But if the optional step is the last
     step in the TC, then there is really no next message to save the day
     for it and when the guard timer expires, the test case will fail --*/

   /*-- Let the guard timer expiry event fall through to the tapa.expopt --*/
   else if ((tcCb->guardTmr == TRUE)   &&
            (tcCb->expOptMsg == FALSE))
   {
      /*-- If in shutdown mode, still plow through rest of the steps,
        hoping that shutdown is clean --*/
      if (tcCb->state != CMXTA_END_SHUTDOWN)
      {
         /*-- Guard timer expired, TC Engine was waiting
           for some message which never came --*/
         CMXTA_DBG_CALLIND((_cmxtap, " Failed    : Timeout, did not receive the message\n"), 3);

         CMXTA_DBG_CALLIND((_cmxtap, " Info      : Skip rest of the steps\n"), 3);

         /*-- Mark the test case as failed, and return --*/
         tcCb->result = CMXTA_TEST_FAILED;

         /*-- Return TC completion --*/
         ret = CMXTA_ERR_COMPLETE;

         /*-- Reset step stack --*/
         cmXtaTCSpReset(tcCb);

         tcCb->guardTmr = FALSE;

         ret = cmXtaTCReq(tcCb, CMXTA_ERR_NONE);
         /*-- Return a positive value here, since you do
           not know which function has triggered the
           engine, better handle it using TC Callback
           as done above --*/
         RETVALUE(CMXTA_ERR_NONE);
      }
      else
      {
         /*-- Special case of guard timer failure for shutdown
           in progress, ignore the timeout and still keep on pumpting 
           the messages --*/

         /*-- Skip the current expect step, if we are here, our current step SHALL not
              be NULLP. cmXtaTCGetNxtStep returns the first TC step if current step is
              NULLP. This should not happen here, and for optimization, I am not checking
              for the current step before calling the function --*/

         /*-- Mark the test case as failed --*/
         tcCb->result = CMXTA_TEST_FAILED;

         /*-- Reset guard timer --*/
         tcCb->guardTmr = FALSE;

         /*-- Get the step stack pointer --*/
         spCb = &tcCb->stack[tcCb->sp];

         /* Find the test case step for the present step stack */
         if ((ret = cmXtaTCGetNxtStep(spCb)) == CMXTA_ERR_COMPLETE)
         {
            /*-- Reset step stack --*/
            cmXtaTCSpReset(tcCb);

            ret = cmXtaTCReq(tcCb, CMXTA_ERR_NONE);
            /*-- Return a positive value here, since you do
              not know which function has triggered the
              engine, better handle it using TC Callback
              as done above --*/
            RETVALUE(CMXTA_ERR_NONE);
         }
         else
         {
            /*-- Guard timer expired, TC Engine was waiting
              for some message which never came --*/
            CMXTA_DBG_CALLIND((_cmxtap, " Failed    : Timeout, did not receive the message\n"), 3);

            CMXTA_DBG_CALLIND((_cmxtap, " Info      : Shutdown mode, still execute rest of the steps, if any\n"), 3);
         }
      }
   }

   while (TRUE)
   {
      /*-- Get the step stack pointer --*/
      spCb = &tcCb->stack[tcCb->sp];

      /*-- Save the current step, so that we can revert back to the
           same in case when no message is received at all --*/
      preStep = spCb->curStep;

      /* Find the test case step for the present step stack */
      while ((ret = cmXtaTCGetNxtStep(spCb)) == CMXTA_ERR_NONE)
      {
         /* Check if its a simple command or a complex command */
         if (spCb->xmlCb->cmdType == CMXTA_TYPE_COMPOUND)
         {
            CMXTA_DBG_INFO((_cmxtap, "cmXtaTCEngine(): compound command found\n"));

            /*-- Print doc for the compound command --*/
            cmXtaXmlGetDocTC(tcCb, spCb->curStep, tcCb->sp);

            /*-- If we are here for the first time, check the step 
                 specific dependencies --*/
            if (cmXtaTCValidateStep(spCb->curStep) == FALSE)
            {
               /*-- Flag dependency not met, do not execute the step --*/
               /*-- Send step completed, get the next step --*/
               /*-- Store curStep in previous step --*/
               preStep = spCb->curStep;
               continue;
            }
            else
            {
               /*-- If we are here, the step is good to execute --*/

               /*-- Since we are loading the embedded steps for the compound
                 command, so in a way, we are processing the compound command.
                 When the engine comes back at this stack level, this particular
                 compound command would have been completely processed, and we
                 should jump to next step, hence do not take a step back for
                 compound command --*/

               /* A compound command, go down one stack level and load the new steps */
               cmd = spCb->xmlCb->t.xmlCmd.steps;

               /*-- Increment stack pointer --*/
               tcCb->sp++;

               /*-- Get the new step stack pointer and call Init --*/
               spCb = &tcCb->stack[tcCb->sp];

               cmXtaTCSpInit(tcCb, spCb, cmd);

               ret = CMXTA_ERR_CONTINUE;
               break;
            }
         }
         /*-- Check if TA defined basic cmd types --*/
         else if ((spCb->xmlCb->cmdType == CMXTA_TYPE_INT)  ||
                  (spCb->xmlCb->cmdType == CMXTA_TYPE_DIR))
         {
            /*-- Call the internally defined cmd types engine --*/
            ret = cmXtaTCEngineInt(tcCb, spCb);

            if (ret == CMXTA_ERR_COMPLETE)
            {
               /*-- Most likely test case failed, no point executing
                    rest of the steps, return from here --*/
               /*-- Trigger the TC STM to continue further --*/
               cmXtaTCSpReset(tcCb);

               ret = cmXtaTCReq(tcCb, CMXTA_ERR_NONE);
               /*-- Return a positive value here, since you do
                    not know which function has triggered the
                    engine, better handle it using TC Callback
                    as done above --*/
               RETVALUE(CMXTA_ERR_NONE);
            }
            else if ((ret == CMXTA_ERR_NONE) ||
                     (ret == CMXTA_ERR_CONTINUE))
            {
               /*-- Send step completed, get the next step --*/
               /*-- Store curStep in previous step --*/
               preStep = spCb->curStep;
            }
            else if ((ret == CMXTA_ERR_PENDING) ||
                     (ret == CMXTA_ERR_SKIP))
            {
               /* Go back a step, this will be again hit when the
                  message is received or the timeout happens */

               curStepLcl = spCb->curStep;
               spCb->curStep = preStep;
               break;
            }
            else
            {
               /*-- Error --*/
               CMXTA_DBG_ERR((_cmxtap, "cmXtaTCEngine(): error received, trigger TC FSM\n"));

               /*-- Trigger the TC STM to continue further --*/
               cmXtaTCSpReset(tcCb);

               ret = cmXtaTCReq(tcCb, ret);
               /*-- Return a positive value here, since you do
                    not know which function has triggered the
                    engine, better handle it using TC Callback
                    as done above --*/
               RETVALUE(CMXTA_ERR_COMPLETE);
            }
         }
         else
         {
            /*-- Unexpected step type, flag error --*/
            CMXTA_DBG_ERR((_cmxtap, "cmXtaTCEngine(): unknown cmdType (%d)\n",
                        spCb->xmlCb->cmdType));

            CMXTA_DBG_CALLIND((_cmxtap, " Info      : Skip rest of the steps\n"), 3);

            /*-- Mark test case as having failed as well --*/
            tcCb->result = CMXTA_TEST_FAILED;

            /*-- Trigger the TC STM to continue further --*/
            cmXtaTCSpReset(tcCb);

            ret = cmXtaTCReq(tcCb, CMXTA_ERR_INT);
            /*-- Return a positive value here, since you do
              not know which function has triggered the
              engine, better handle it using TC Callback
              as done above --*/
            RETVALUE(CMXTA_ERR_INT);
         }
      }

      /*-- Check if a compound command loaded, then start from
           the beginning --*/
      if (ret == CMXTA_ERR_CONTINUE)
         continue;
      else if (ret == CMXTA_ERR_PENDING)
      {
         /*-- This happens if the test is waiting for an external
              event, start the guard timer and suspend, yawn --*/

         /*-- Read the guard timer value from TC, if given --*/
         /*-- curStep is reverted back to preStep by this time, so use the local
              curStep value stored earlier --*/

         /*-- In case of 3rd party testing, we may want to wait for infinite period,
              that can be done by setting guardTmr to 0, do not start if the timer
              value is zero, the better way would be use the external parameter 
              which will wait for longer period, but not forever --*/

         /*-- Do not start guard timer if we are trying to delay the test cases. This
              may happen from internal delay command tapa.delay, but the layers may
              also not want to run guard timer for their specific handlers, the same
              can be done by setting the noGuardTmr to FALSE. It is the responsibility
              of the specific handler to reset this flag later --*/

         /*-- Run guard timer only if suggested so --*/
         if (tcCb->noGuardTmr == TRUE)
            RETVALUE(CMXTA_ERR_NONE);

         /* cm_xta_tcfsm_c_001.main_6 :Added NULL check*/
         if(!curStepLcl)
         {
            CMXTA_DBG_ERR((_cmxtap, "cmXtaTCEngine(): error, trigger TC FSM\n"));
            cmXtaDispNFlushQ(&tcCb->msgQ[0]);
            /*-- Mark test case as having failed --*/
            tcCb->result = CMXTA_TEST_FAILED;
            /*-- Trigger the TC STM to continue further --*/
            cmXtaTCSpReset(tcCb);

            ret = cmXtaTCReq(tcCb, CMXTA_ERR_INT);
            RETVALUE(CMXTA_ERR_INT); 
         }
         guardTmr = CMXTA_TMR_GUARD_VAL;

         extTrigger = FALSE;
         cmXtaXmlGetVal(NULLP, curStepLcl, CMXTA_ATTRIB_BOOL, "external",  &(extTrigger));
         /*Increased the guardTmr for external agent*/
         if (extTrigger == TRUE)
            guardTmr = CMXTA_TMR_GUARD_VAL * 1000;

         /*-- Get the guardTmr value --*/
         cmXtaXmlGetVal(NULLP, curStepLcl, CMXTA_ATTRIB_U16, "guardTmr",  &(guardTmr));

         if (guardTmr != 0)
            cmXtaStartTmr(CMXTA_TMR_GUARD_EXP, tcCb, guardTmr);

         /*-- Return a positive value here, since you do
           not know which function has triggered the
           engine, better handle it using TC Callback
           as done above --*/
         RETVALUE(CMXTA_ERR_NONE);
      }
      else if (ret == CMXTA_ERR_SKIP)
      {
         /*-- We have to execute this step in a LC fashion --*/

         /*-- This may be useful when the stack passes the 
              middle of call message to the application and
              the next step in the test case is the system
              shutdown.

              A TC step in this case will cause a stack crash,
              because the shutdown step will cleanup the stack
              STM and in some cases, the stack may not be ready
              for such shutdowns in the middle of the call. 

              --*/

         /*-- Post a message to yourself and resume from there --*/
         /* Send a message to ENTST to initiate testing */
         if (cmXtaTAPstSelfMsg((Void *)tcCb, EVTSTTTSTSKIP) != CMXTA_ERR_NONE)
         {
            /*-- Unexpected step type, flag error --*/
            CMXTA_DBG_ERR((_cmxtap, "cmXtaTCEngine(): error, trigger TC FSM\n"));

            /*-- Trigger the TC STM to continue further --*/
            cmXtaTCSpReset(tcCb);

            ret = cmXtaTCReq(tcCb, CMXTA_ERR_INT);
            /*-- Return a positive value here, since you do
              not know which function has triggered the
              engine, better handle it using TC Callback
              as done above --*/
         }

         /*-- Return a positive value here, since you do
           not know which function has triggered the
           engine, better handle it using TC Callback
           as done above --*/
         RETVALUE(CMXTA_ERR_NONE);
      }
      else if (ret == CMXTA_ERR_COMPLETE)
      {
         /*-- Reset the step count --*/
         cmXtaTCSpResetStepCnt(tcCb);

         /*-- All steps completed, check if the highest stack level --*/
         if (--tcCb->sp >= 0)
         {
            /*-- The high level is finished, we are going back to the
                 previous level, increment the step count --*/
            cmXtaTCSpIncrStepCnt(tcCb);

            continue;
         }
         /*-- All steps completed, check if we are delaying the completion
              of the test case for shutdown scenarios --*/
         if ((tcCb->state == CMXTA_END_SHUTDOWN) &&
             (tcCb->directives.delayTest == TRUE))
         {
            /*-- Delayed Test mode --*/

            tcCb->delayTestTmr = FALSE;

            /*-- Flag dependency not met, do not execute the step --*/
            CMXTA_DBG_CALLIND((_cmxtap, " Info      : Delay after TC Shutdown for delay=%d\n",
                            cmXtaCb.delayTstVal), 3);

            /*-- Run the delayTest timer --*/
            cmXtaStartTmr(CMXTA_TMR_DELAY_TST, tcCb, cmXtaCb.delayTstVal);

            /*-- Return a positive value here, since you do
              not know which function has triggered the
              engine, better handle it using TC Callback
              as done above --*/
            RETVALUE(CMXTA_ERR_NONE);
         }
         else
         {
            /*-- All steps completed, check there are no
            pending queued messages for the test, if pending messages,
            then flag error, else mark the steps as complete --*/

            /*-- Check if there is any messages waiting in the queue --*/
            if (cmXtaLenMsgQ(&tcCb->msgQ[0]) > 0)
            {
               /*-- More messages are lying in the queue, there could
                    be two reasons, either all the messages were not 
                    handled in the test case, or someone wrote the rest
                    of the expect sequence in the other section of the
                    test cases, either case, mark it as failed --*/
               CMXTA_DBG_CALLIND((_cmxtap, " Failed    : Extra unhandled messages in the queue\n"), 3);
               cmXtaDispNFlushQ(&tcCb->msgQ[0]);

               /*-- Mark test case as having failed --*/
               tcCb->result = CMXTA_TEST_FAILED;
            }

            /*-- End of the all the steps at all stack levels --*/
            /*-- Trigger the TC STM to continue further --*/
            ret = cmXtaTCReq(tcCb, CMXTA_ERR_NONE);
            RETVALUE(CMXTA_ERR_NONE);
         }
      }
      else
      {
         /*-- Unexpected step type, flag error --*/
         CMXTA_DBG_ERR((_cmxtap, "cmXtaTCEngine(): error, trigger TC FSM\n"));

         /*-- Trigger the TC STM to continue further --*/
         cmXtaTCSpReset(tcCb);

         ret = cmXtaTCReq(tcCb, CMXTA_ERR_INT);
         /*-- Return a positive value here, since you do
           not know which function has triggered the
           engine, better handle it using TC Callback
           as done above --*/
         RETVALUE(CMXTA_ERR_COMPLETE);
      }
   }

   /*-- Return end of processing --*/
   RETVALUE(CMXTA_ERR_NONE);
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
PUBLIC S16 cmXtaTCEngineInt
(
CmXtaTCCb           *tcCb,
CmXtaSpCb *spCb
)
#else
PUBLIC S16 cmXtaTCEngineInt(tcCb, spCb)
CmXtaTCCb           *tcCb;
CmXtaSpCb           *spCb;
#endif
{
   S16  ret;
   U8   queue;

   TRC2(cmXtaTCEngineInt)

   /* cm_xta_tcfsm_c_001.main_7: Fix for 64bit compilation warning */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTCEngineInt(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTCEngineInt(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   ret = CMXTA_ERR_NONE;

   while (TRUE)
   {
      /*-- Check for the command subtype, for Send, do not check
           if there is a message pending in the test case queue,
           for rest others, if no message, return pending --*/
      CMXTA_DBG_INFO((_cmxtap, "cmXtaTCEngineInt(): cmd subType (%d)\n",
                   spCb->xmlCb->subType));

      /*-- Print doc if it is the first time here --*/
      if (spCb->state == CMXTA_IDLE)
      {
         cmXtaXmlGetDocTC(tcCb, spCb->curStep, tcCb->sp);

         cmXtaTCSpIncrStepCnt(tcCb);

         spCb->state = CMXTA_INIT;
      }

      /*-- Load mode for TA --*/
      /*-- The same can be triggered by setting the appropriate mode
           or by writing tapa.load section instead of the default 
           tapa.test section. I prefer tapa.load because it is more
           explicit --*/

      /*-- If load Mode is TRUE, then parse all the steps and form
           optimized test steps for the load scenarios --*/

      /*-- Do note, some of the test scenarios may not have the meaning
           or may not behave correctly in load mode. For eg, if a TC
           wants to change the capturing of the alarm (a hypothetical
           far fetched scenario) in the middle of the TC, in a load 
           mode, it does not make sense, because TA does not provide
           a way right now to do the same in the optimized steps. 
           There does not seem to be any reason to try such a thing
           in the first place for a load scenario --*/
      if (cmXtaCb.loadDir.loadMode == TRUE)
      {
         /*-- First check for command type --*/
         switch (spCb->xmlCb->cmdType)
         {
            case CMXTA_TYPE_INT :

               /*-- If we are here for the first time, check the step 
                    specific dependencies --*/
               if ((spCb->state == CMXTA_INIT)   &&
                   (cmXtaTCValidateStep(spCb->curStep)) == FALSE)
                  RETVALUE(CMXTA_ERR_NONE);

               /*-- Check for the common load attributes for internal
                    commands --*/

               /*-- Following steps are valid only when sync feature
                    is enabled --*/
               if (cmXtaCb.loadDir.syncLoadSteps == TRUE)
               {
                  /*-- Check if we allow retracting of the steps, default
                       is TRUE --*/
                  cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].retract = TRUE;
                  cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "retract",
                                  &(cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].retract));

                  /*-- Check if we allow retransmission of the steps, default
                       is TRUE --*/

                  /*-- Do note, retrans only is valid for tapa.send at the 
                       moment. It will just be ignored for the tapa.exp...
                       family at the moment --*/
                  cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].retrans = TRUE;
                  cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "retrans",
                                  &(cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].retrans));
               }

               /*-- Check sub command type --*/
               switch (spCb->xmlCb->subType)
               {
                  case CMXTA_SUBTYPE_SEND:
                     /*-- Call Send registered API --*/
                     tcCb->busy = TRUE;
                     ret = spCb->xmlCb->func(tcCb, spCb);
                     tcCb->busy = FALSE;
                     break;

                  case CMXTA_SUBTYPE_EXPECT     :
                  case CMXTA_SUBTYPE_EXPOPT     :
                  case CMXTA_SUBTYPE_EXPSEQ     :

                     /*-- Do not check for the pending message in case of 
                          load mode --*/

                     /*-- Call Expect registered API --*/
                     tcCb->busy = TRUE;
                     ret = spCb->xmlCb->func(tcCb, spCb);
                     tcCb->busy = FALSE;
                     break;

                  case CMXTA_SUBTYPE_DELAY     :
                     /*-- Delays ignored in load mode --*/
                     break;

                  case CMXTA_SUBTYPE_TIMEOUT :
                     /*-- Timeouts ignored in load mode --*/
                     break;

                  case CMXTA_SUBTYPE_EXPSET     :
                     /*-- No esoteric commands supported in load mode --*/
                     CMXTA_DBG_ERR((_cmxtap, "cmXtaTCEngineInt(): unsupported subType in load (%d)\n",
                              spCb->xmlCb->subType));
                     ret = CMXTA_ERR_INT;
                     break;

                  default :
                     CMXTA_DBG_ERR((_cmxtap, "cmXtaTCEngineInt(): invalid subType (%d)\n",
                              spCb->xmlCb->subType));
                     ret = CMXTA_ERR_INT;
               }
               break;

            case CMXTA_TYPE_DIR :

               /*-- What shall be the meaning of this command in case of load
                    mode? TA at the moment does not have any separate handling
                    for load mode and the directives are applied immediately.

                    Use it in load mode at your own peril --*/

               /*-- In case of directive set of commands, we do not care for
                 the subcommands, these commands can be extended by the
                 users. Just call the corresponding registered API --*/

               /*-- Call Send registered API --*/
               tcCb->busy = TRUE;
               ret = spCb->xmlCb->func(tcCb, spCb);
               tcCb->busy = FALSE;
               break;

            default :
               ret = CMXTA_ERR_INT;

               /*-- Unrecognized commands have the same fate even in load
                    mode, there is a meanness in the world --*/

               /*-- Unexpected step type, flag error --*/
               CMXTA_DBG_ERR((_cmxtap, "cmXtaTCEngineInt(): unknown cmdType (%d)\n",
                      spCb->xmlCb->cmdType));
               break;
         }
      }
      else
      {
         /*-- Normal mode --*/
         /*-- First check for command type --*/
         switch (spCb->xmlCb->cmdType)
         {
            case CMXTA_TYPE_INT :

               /*-- If we are here for the first time, check the step 
                    specific dependencies --*/
               if ((spCb->state == CMXTA_INIT)   &&
                   (cmXtaTCValidateStep(spCb->curStep)) == FALSE)
                  RETVALUE(CMXTA_ERR_NONE);

               /*-- Check sub command type --*/
               switch (spCb->xmlCb->subType)
               {
                  case CMXTA_SUBTYPE_SEND:
                     /*-- Call Send registered API --*/
                     tcCb->busy = TRUE;
                     ret = spCb->xmlCb->func(tcCb, spCb);
                     tcCb->busy = FALSE;

                     /*-- Return immediately from here --*/
                     if (ret == CMXTA_ERR_SKIP)
                        RETVALUE(ret);
                     break;

                  case CMXTA_SUBTYPE_EXPECT     :
                  case CMXTA_SUBTYPE_EXPSEQ     :
                  case CMXTA_SUBTYPE_EXPSET     :
                     /*-- Check if there is a message waiting in the queue,
                       else suspend --*/
                     /*-- here we need to know which queue to to check, by 
                        default we would check in tcCb->msgQ[0] --*/
                     queue = 0;
                     cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_U8,
"queue", &queue);
                     if (cmXtaLenMsgQ(&tcCb->msgQ[queue]) > 0)
                     {
                        /*-- A message is lying in queue, we may have
                          started a guard timer earlier, to wait for
                          this message, stop it --*/
                        cmXtaStopTmr(CMXTA_TMR_GUARD_EXP, tcCb);

                        /*-- Call internal command registered API --*/
                        ret = spCb->xmlCb->func(tcCb, spCb);
                     }
                     else
                     {
                        /*-- No message pending, the doc for the test
                          case is already printed, so mark the test
                          case as running, so that the doc is not
                          printed again --*/
                        spCb->state = CMXTA_RUN;

                        /*-- Return immediately from here --*/
                        RETVALUE(CMXTA_ERR_PENDING);
                     }
                     break;

                  case CMXTA_SUBTYPE_EXPOPT     :
                     /*-- Check if there is a message waiting in the queue,
                       or the guard timer expired, else suspend --*/
                     /*-- here we need to know which queue to to check, by 
                        default we would check in tcCb->msgQ[0] --*/
                     queue = 0;
                     cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_U8,
"queue", &queue);
                     if ((tcCb->guardTmr == TRUE)        ||
                         (cmXtaLenMsgQ(&tcCb->msgQ[queue]) > 0))
                     {
                        /*-- A message may be lying in queue, we may have
                          started a guard timer earlier, to wait for
                          this message, stop it --*/
                        cmXtaStopTmr(CMXTA_TMR_GUARD_EXP, tcCb);

                        /*-- Call internal command registered API --*/
                        ret = spCb->xmlCb->func(tcCb, spCb);
                     }
                     else
                     {
                        /*-- No message pending, the doc for the test
                          case is already printed, so mark the test
                          case as running, so that the doc is not
                          printed again --*/
                        spCb->state = CMXTA_RUN;

                        /*-- Mark as waiting for an optional message --*/
                        tcCb->expOptMsg = TRUE;

                        /*-- Return immediately from here --*/
                        RETVALUE(CMXTA_ERR_PENDING);
                     }
                     break;

                  case CMXTA_SUBTYPE_DELAY     :
                     /*-- Check if there is a message waiting in the queue,
                       or the delay timer expired, else suspend --*/

                     /*-- Check if this is the first time for this handler,
                       then go in and start the timer --*/
                     if (tcCb->timeOutState == CMXTA_NONE)
                     {
                        /*-- Call internal command registered API --*/
                        ret = spCb->xmlCb->func(tcCb, spCb);

                        /*-- Return immediately from here --*/
                        if (ret == CMXTA_ERR_PENDING)
                        {
                           /*-- No message pending, the doc for the test
                             case is already printed, so mark the test
                             case as running, so that the doc is not
                             printed again --*/
                           spCb->state = CMXTA_RUN;

                           RETVALUE(ret);
                        }
                     }
                     else if ((tcCb->delayTmr == TRUE)     ||
                            (cmXtaLenMsgQ(&tcCb->msgQ[0]) > 0))
                     {
                        /*-- A message may be lying in queue, we may have
                          started a guard timer earlier, to wait for
                          this message, stop it --*/
                        cmXtaStopTmr(CMXTA_TMR_GUARD_EXP, tcCb);

                        /*-- Call internal command registered API --*/
                        ret = spCb->xmlCb->func(tcCb, spCb);

                        /*-- Return immediately from here --*/
                        if (ret == CMXTA_ERR_PENDING)
                           RETVALUE(ret);
                     }
                     break;

                  case CMXTA_SUBTYPE_TIMEOUT :

                     /*-- Check if this is the first time for this handler,
                       then go in and start the timer --*/
                     if (tcCb->timeOutState == CMXTA_NONE)
                        /*-- Call internal command registered API --*/
                        ret = spCb->xmlCb->func(tcCb, spCb);
                     else if (cmXtaLenMsgQ(&tcCb->msgQ[0]) > 0)
                     {
                        /*-- Not the first time --*/
                        /*-- A message is lying in queue, we may have
                          started a guard timer earlier, to wait for
                          this message, stop it --*/
                        cmXtaStopTmr(CMXTA_TMR_GUARD_EXP, tcCb);

                        /*-- Call internal command registered API --*/
                        ret = spCb->xmlCb->func(tcCb, spCb);
                     }
                     else
                     {
                        /*-- No message pending, the doc for the test
                          case is already printed, so mark the test
                          case as running, so that the doc is not
                          printed again --*/
                        spCb->state = CMXTA_RUN;

                        /*-- Return immediately from here --*/
                        RETVALUE(CMXTA_ERR_PENDING);
                     }
                     break;

                  /*--cm_xta_tcfsm_c_001.main_4 loop changes starts--*/
                  /*--If the internal command is repeat start then call
                      the corresponding handler function in cm_xta_inthdl.c --*/

                  case CMXTA_SUBTYPE_REPEAT_START :

                     tcCb->busy = TRUE;
                     ret = spCb->xmlCb->func(tcCb, spCb);
                     tcCb->busy = FALSE;
                     
                   break;

                  /*--If the internal command is repeat end then call
                      the corresponding handler function in cm_xta_inthdl.c --*/
                  case CMXTA_SUBTYPE_REPEAT_END :

                     tcCb->busy = TRUE;
                     ret = spCb->xmlCb->func(tcCb, spCb);
                     tcCb->busy = FALSE;
                     
                   break;
                  /*--loop changes ends--*/

                  default :
                     CMXTA_DBG_ERR((_cmxtap, "cmXtaTCEngineInt(): invalid subType (%d)\n",
                              spCb->xmlCb->subType));
                     ret = CMXTA_ERR_INT;
               }

               break;

            case CMXTA_TYPE_DIR :

               /*-- In case of directive set of commands, we do not care for
                 the subcommands, these commands can be extended by the
                 users. Just call the corresponding registered API --*/

               /*-- Call Send registered API --*/
               tcCb->busy = TRUE;
               ret = spCb->xmlCb->func(tcCb, spCb);
               tcCb->busy = FALSE;
               break;

            default :
               ret = CMXTA_ERR_INT;

               /*-- Unexpected step type, flag error --*/
               CMXTA_DBG_ERR((_cmxtap, "cmXtaTCEngineInt(): unknown cmdType (%d)\n",
                      spCb->xmlCb->cmdType));

               break;
         }
      }

      /*-- Check if the command successfully processed --*/
      if ((ret == CMXTA_ERR_CONTINUE) ||
          (ret == CMXTA_ERR_NONE))
      {
         /*-- Command done, go back to main test engine --*/
         break;
      }
      else if (ret == CMXTA_ERR_PENDING)
      {
         /*-- This happens if the present message was processed
              by the internal handler, but it not done yet, so
              if there are more queued events, loop again, 
              
              or

              a new handler was loaded, but there are no messages
              to be processed, so return, that is handled above --*/
         continue;
      }
      else if (ret == CMXTA_ERR_COMPLETE)
      {
         /*-- Command done, go back to main test engine --*/
         /*-- Change it CMXTA_ERR_NONE, because we may take this as 
              leaving the test then and there itself --*/
         ret = CMXTA_ERR_NONE;
         break;
      }
      else
      {
         /*-- Mark test case as having failed --*/
         tcCb->result = CMXTA_TEST_FAILED;

         /*-- If in shutdown mode, still plow through rest of the steps,
              hoping that shutdown is clean --*/
         if (tcCb->state != CMXTA_END_SHUTDOWN)
         {
            /*-- Handler failed, flag error --*/
            CMXTA_DBG_INFO((_cmxtap, "cmXtaTCEngineInt(): test case failed\n"));

            CMXTA_DBG_CALLIND((_cmxtap, " Info      : Skip rest of the steps\n"), 3);

            /*-- Return TC completion --*/

            /*-- Propagate resource errors, so that we can skip running any
                 more test cases, any other error, mark TC as complete --*/
            if (ret == CMXTA_ERR_RSRC)
               RETVALUE(ret);

            ret = CMXTA_ERR_COMPLETE;
            break;
         }
         else
         {
            /*-- Handler failed, flag error --*/
            CMXTA_DBG_INFO((_cmxtap, "cmXtaTCEngineInt(): test step failed\n"));

            /*-- Command done, go back to main test engine --*/
            ret = CMXTA_ERR_NONE;
            break;
         }
      }
   }

   /*-- Return end of processing --*/
   RETVALUE(ret);
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
PUBLIC S16 cmXtaTCSpReset
(
CmXtaTCCb *tcCb
)
#else
PUBLIC S16 cmXtaTCSpReset(tcCb)
CmXtaTCCb           *tcCb;
#endif
{
   TRC2(cmXtaTCSpReset)

   tcCb->sp = 0;

   RETVALUE(CMXTA_ERR_NONE);
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
PUBLIC S16 cmXtaTCSpInit
(
CmXtaTCCb *tcCb,
CmXtaSpCb *spCb,
Void  *tstSteps
)
#else
PUBLIC S16 cmXtaTCSpInit(tcCb, spCb, tstSteps)
CmXtaTCCb *tcCb;
CmXtaSpCb *spCb;
Void  *tstSteps;
#endif
{
   S16  cnt;

   TRC2(cmXtaTCSpInit)

   CMXTA_ZERO(spCb, sizeof(CmXtaSpCb));

   spCb->firstStep = tstSteps;
   spCb->state = CMXTA_IDLE;

   /*-- Reset the step count --*/
   for (cnt = tcCb->sp; cnt < CMXTA_STACK_DEPTH; cnt++)
      tcCb->stack[cnt].stepCnt = 1;

   RETVALUE(CMXTA_ERR_NONE);
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
PUBLIC S16 cmXtaTCSpIncrStepCnt
(
CmXtaTCCb *tcCb
)
#else
PUBLIC S16 cmXtaTCSpIncrStepCnt(tcCb)
CmXtaTCCb *tcCb;
#endif
{
   TRC2(cmXtaTCSpIncrStepCnt)

   tcCb->stack[tcCb->sp].stepCnt++;

   RETVALUE(CMXTA_ERR_NONE);
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
PUBLIC S16 cmXtaTCSpResetStepCnt
(
CmXtaTCCb *tcCb
)
#else
PUBLIC S16 cmXtaTCSpResetStepCnt(tcCb)
CmXtaTCCb *tcCb;
#endif
{
   S16  cnt;

   TRC2(cmXtaTCSpResetStepCnt)

   for (cnt = tcCb->sp; cnt < CMXTA_STACK_DEPTH; cnt++)
   {
      tcCb->stack[cnt].stepCnt = 1;
   }

   RETVALUE(CMXTA_ERR_NONE);
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
PUBLIC S16 cmXtaTCGenCount
(
CmXtaTCCb *tcCb,
Txt    *str
)
#else
PUBLIC S16 cmXtaTCGenCount(tcCb, str)
CmXtaTCCb *tcCb;
Txt    *str;
#endif
{
   S16  cnt;

   TRC2(cmXtaTCGenCount)

   str[0] = '\0';

   for (cnt = 0; cnt <= tcCb->sp; cnt++)
   {
      if (cnt == 0)
         sprintf(str + cmStrlen((CONSTANT U8 *)str), "%d", tcCb->stack[cnt].stepCnt);
      else
         sprintf(str + cmStrlen((CONSTANT U8 *)str), ".%d", tcCb->stack[cnt].stepCnt);
   }

   RETVALUE(CMXTA_ERR_NONE);
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
PUBLIC CmXtaTCCb *cmXtaTCCreate
(
U8              ctxt,
U16             tstGrpId,
U16             tstId,
Void            *ptr
)
#else
PUBLIC CmXtaTCCb * cmXtaTCCreate (ctxt, tstGrpId, tstId, ptr)
U8              ctxt;
U16             tstGrpId;
U16             tstId;
Void            *ptr;
#endif
{
   CmXtaTCCb * tcCb;
   CmXtaXmlCb  *xmlCb;

   Txt str[100];

   TRC2(cmXtaTCCreate)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTCCreate(): grpId(%d) tstId(%d)\n", tstGrpId, tstId));

   tcCb = NULLP;

   /* Allocate Memory for Txn CB */
   CMXTA_ALLOC(&tcCb, sizeof(CmXtaTCCb));

   if (tcCb == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTCCreate(): resource error\n"));
      RETVALUE(NULLP);
   }

   /*-- Init Directives in the test case --*/
   tcCb->directives = cmXtaCb.directives;

   tcCb->tstGrpId   = tstGrpId;
   tcCb->tstId      = tstId;

   /*-- Call App tcCb Init function --*/
   if (cmXtaAppTCCreate(tcCb) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTCCreate(): resource error\n"));

      CMXTA_FREE(tcCb, sizeof (CmXtaTCCb));
      RETVALUE(NULLP);
   }

   /*-- Reset tcCb message queue --*/
   if (cmXtaInitQ(&tcCb->msgQ[0]) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTCCreate(): resource error\n"));

      CMXTA_FREE(tcCb, sizeof (CmXtaTCCb));
      RETVALUE(NULLP);
   }

   /*-- Set TC Engine user --*/
   tcCb->user = ctxt;

   /*-- Check if the TC is to run external STM steps or is to run
        a test case --*/
   if (ctxt == CMXTA_CTXT_TC)
   {
      /*-- Set state --*/
      tcCb->state = CMXTA_START_INIT;

      sprintf(str, "%d.%d", tstGrpId+1, tstId+1);

      if ((xmlCb = cmXtaXmlFind(tstGrpId+1, tstId+1, str, TRUE)) == NULLP)
      {
         /*-- No test case found, cleanup --*/
         CMXTA_DBG_ERR((_cmxtap, "cmXtaTCCreate(): XML test case not found\n"));

         cmXtaTCDelete(tcCb);
         RETVALUE (NULLP);
      }

      tcCb->xmlCb = xmlCb;
   }
   else if (ctxt == CMXTA_CTXT_TG)
   {
      /*-- Set state --*/
      tcCb->state = CMXTA_START_EXT;

      tcCb->ext = (CmXtaXmlCb *)ptr;
   }
   else
   {
      /*-- Either TA or TG wants to execute some steps, just load
        the steps and start execution --*/
      /*-- Set state --*/
      tcCb->state = CMXTA_START_EXT;

      if ((xmlCb = cmXtaXmlFind(0, 0, (Txt *)ptr, TRUE)) == NULLP)
      {
         /*-- No test case found, cleanup --*/
         CMXTA_DBG_ERR((_cmxtap, "cmXtaTCCreate(): XML test case not found\n"));

         cmXtaTCDelete(tcCb);
         RETVALUE (NULLP);
      }

      tcCb->ext   = xmlCb;
   }

   /*-- Reset stack pointer --*/
   cmXtaTCSpReset(tcCb);

   tcCb->result = CMXTA_TEST_PASSED;

   /*-- Assign the test case Id --*/
   tcCb->tcId = ++cmXtaCb.tcCounter;

   /* Init Tmr block */
   cmInitTimers(tcCb->timers, CMXTA_MAX_TMR);

   /* cm_xta_tcfsm_c_001.main_7: Fix for 64bit compilation warning */
#ifdef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCCreate(): New test case Cb (%d) created\n", tcCb->tcId));
#else
   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCCreate(): New test case Cb (%ld) created\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   RETVALUE(tcCb);
} /* cmXtaTCCreate */

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
PUBLIC S16  cmXtaTCDelete
(
CmXtaTCCb         *tcCb       /* Transaction Block   */
)
#else
PUBLIC S16  cmXtaTCDelete (tcCb)
CmXtaTCCb      *tcCb;         /* Transaction Block   */
#endif
{
   TRC2(cmXtaTCDelete)

   /*-- Finally, delete control block (TCB) --*/
   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCDelete(): tst cb deleted\n"));

   cmXtaFlushQ(&tcCb->msgQ[0]);

   cmXtaAppTCDelete(tcCb);

   CMXTA_FREE(tcCb, sizeof (CmXtaTCCb));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaTCDelete */

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
PUBLIC S16  cmXtaTCAddTC
(
U16 tstGrpId,
U16 tstId
)
#else
PUBLIC S16  cmXtaTCAddTC (tstGrpId, tstId)
U16 tstGrpId;
U16 tstId;
#endif
{
   TRC2(cmXtaTCAddTC)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTCAddTC(): grpId(%d) tstId(%d)\n", tstGrpId, tstId));

   /*-- Register the Test group --*/
   if (tstGrpId >= CMXTA_MAX_GRP)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTCAddTC(): grpId(%d) greater than max grp(%d)\n",
                  tstGrpId, CMXTA_MAX_GRP));
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cmXtaCb.tstGrp[tstGrpId - 1].state == CMXTA_NONE)
   {
#ifdef CMXTA_IGNORE_FAIL
      /*-- Test Group not present, allow it continue still --*/
      cmXtaCb.tstGrp[tstGrpId - 1].state = CMXTA_IDLE;
      /*-- Set the tstGrpCnt to maxTestGroupNumber instead of actual number of
        test groups loaded, the missing test groups will be anyway 
        validated in the validation function --*/
      if (cmXtaCb.tstGrpCnt < tstGrpId)
         cmXtaCb.tstGrpCnt = tstGrpId;
#else
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTCAddTC(): invalid grpId(%d)\n", tstGrpId));
      RETVALUE(CMXTA_ERR_INT);
#endif
   }

   /*-- Check the TC Id --*/
   if (tstId >= CMXTA_MAX_TST)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTCAddTC(): tstId(%d) greater than max tstId(%d)\n",
               tstId, CMXTA_MAX_TST));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Check if duplicate --*/
   if (cmXtaCb.tstGrp[tstGrpId - 1].tstList[tstId - 1].tcSet == TRUE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTCAddTC(): tstId(%d) already registered\n", tstId));
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaCb.tstGrp[tstGrpId - 1].tstList[tstId - 1].tcSet = TRUE;
   cmXtaCb.tstGrp[tstGrpId - 1].tstList[tstId - 1].state = CMXTA_IDLE;

   /*-- Set the numTests to maxTestNumber instead of actual number of
     test cases loaded, the missing test cases will be anyway 
     validated in the validation function --*/
   if (cmXtaCb.tstGrp[tstGrpId - 1].numTests < tstId)
      cmXtaCb.tstGrp[tstGrpId - 1].numTests = tstId;

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaTCAddTC */

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
PUBLIC S16  cmXtaTCAddTG
(
U16 tstGrpId,
Txt *doc
)
#else
PUBLIC S16  cmXtaTCAddTG (tstGrpId, doc)
U16 tstGrpId;
Txt *doc;
#endif
{
   TRC2(cmXtaTCAddTG)

   CMXTA_DBG_PARAM((_cmxtap, "cmXtaTCAddTG(): grpId(%d)\n", tstGrpId));

   /*-- Register the Test group --*/
   if (tstGrpId >= CMXTA_MAX_GRP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTCAddTG(): grpId(%d) greater than max grp(%d)\n",
                  tstGrpId, CMXTA_MAX_GRP));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Check if duplicate --*/
   if (cmXtaCb.tstGrp[tstGrpId - 1].state == CMXTA_IDLE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTCAddTG(): grpId(%d) already registered\n", tstGrpId));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* cm_xta_tcfsm_c_001.main_6: Added validation for doc */
   if(cmStrlen((CONSTANT U8 *)doc) >= 100)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTCAddTG(): group name is larger than the max length %d\n",100));
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaCb.tstGrp[tstGrpId - 1].state = CMXTA_IDLE;
   /*-- Set the tstGrpCnt to maxTestGroupNumber instead of actual number of
     test groups loaded, the missing test groups will be anyway 
     validated in the validation function --*/
   if (cmXtaCb.tstGrpCnt < tstGrpId)
      cmXtaCb.tstGrpCnt = tstGrpId;

   /*-- Store the TG doc --*/
   CMXTA_CPY(cmXtaCb.tstGrp[tstGrpId - 1].name,
          doc,
          (cmStrlen((CONSTANT U8 *)doc) + 1) * sizeof (U8));

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaTCAddTG */

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
PUBLIC S16 cmXtaTCGetNxtStep
(
CmXtaSpCb *spCb
)
#else
PUBLIC S16 cmXtaTCGetNxtStep(spCb)
CmXtaSpCb *spCb;
#endif
{
   TRC2(cmXtaTCGetNxtStep)

   /*-- Check if the first step --*/
   if (spCb->curStep == NULLP)
      spCb->curStep = spCb->firstStep;
   else
      spCb->curStep =
         cmXtaXmlNextSiblingOfType(spCb->curStep, CMXTA_DOM_ELEMENT_NODE);

   if (spCb->curStep == NULLP)
      RETVALUE(CMXTA_ERR_COMPLETE);

   /*-- Update Step Info in the stack pointer Cb --*/
   if ((spCb->xmlCb = cmXtaXmlFindFromXml(spCb->curStep)) == NULLP)
   {
      /*-- XML cmd not registered, flag error --*/
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTCGetNxtStep(): XML cmd not registered\n"));
      spCb->curStep = NULLP;
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Reset spCb->state, only if the doc is not already printed earlier --*/
   if (spCb->state == CMXTA_INIT)
      spCb->state = CMXTA_IDLE;

   RETVALUE(CMXTA_ERR_NONE);
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
PUBLIC S16 cmXtaTCGetFirstStep
(
CmXtaSpCb *spCb
)
#else
PUBLIC S16 cmXtaTCGetFirstStep(spCb)
CmXtaSpCb *spCb;
#endif
{
   TRC2(cmXtaTCGetFirstStep)

   /*-- Check if the first step exists --*/
   if (spCb->firstStep == NULLP)
      RETVALUE(CMXTA_ERR_COMPLETE);

   RETVALUE(CMXTA_ERR_NONE);
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
PUBLIC S16 cmXtaTCGetNxt
(
)
#else
PUBLIC S16 cmXtaTCGetNxt()
#endif
{
   CmXtaTstGrp      *tg;                            /* test group cntrl blk --*/

   tg = &cmXtaCb.tstGrp[cmXtaCb.curTstGroup];

   TRC2(cmXtaTCGetNxt)

   /* Find next Tst Case control block */
   for (++tg->curTest; tg->curTest < tg->endTest; tg->curTest++)
   {
      if ((tg->tstList[tg->curTest].tcSet == TRUE)  &&
          (tg->tstList[tg->curTest].state == CMXTA_RUN))
         break;
   }

   RETVALUE(tg->curTest);
} /* cmXtaTCGetNxt */

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
PUBLIC S16  cmXtaTCValidatePre
(
CmXtaTCCb *tcCb,
Void     *pre
)
#else
PUBLIC S16  cmXtaTCValidatePre (tcCb, pre)
CmXtaTCCb *tcCb;
Void     *pre;
#endif
{
   TRC2(cmXtaTCValidatePre)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCValidatePre(): \n"));

   RETVALUE(cmXtaPyWrap_ValidatePre(tcCb, pre));
} /* cmXtaTCValidatePre */


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
PUBLIC Bool  cmXtaTCValidateStep
(
Void     *curStep
)
#else
PUBLIC Bool  cmXtaTCValidateStep (curStep)
Void     *curStep;
#endif
{
   U8  flag;

   TRC2(cmXtaTCValidateStep)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTCValidateStep(): \n"));

   /*-- Check if conditional flag is enabled, at present there is
     support for only one flag, the limitation is from XML syntax
     which does not support multiple attributes of the same
     name --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
     using XML --*/
   flag = CMXTA_MAX_FLAGS;
   cmXtaXmlGetVal(NULLP, curStep, CMXTA_ATTRIB_FLAG, "flag", &flag);

   /*-- Check if flag enabled, else return --*/
   if ((flag < CMXTA_MAX_FLAGS) && (cmXtaFlIsSet(flag) == FALSE))
   {
      /*-- Flag dependency not met, do not execute the step --*/
      CMXTA_DBG_CALLIND((_cmxtap, " Info      : Flag [%s] not enabled, skip step\n", 
               cmXtaFlagStr[flag]), 3);

      RETVALUE(FALSE);
   }

   RETVALUE(TRUE);
} /* cmXtaTCValidateStep */


/********************************************************************30**

         End of file:     cm_xta_tcfsm.c@@/main/TeNB_Main_BR/2 - Thu Apr 24 17:04:59 2014

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
/main/3      ---      cm_xta_tcfsm_c_001.main_2  sk  1. Multiple queue support
/main/4      ---      aj  1. Increased the guardTmr for external agent
/main/5      ---      cm_xta_tcfsm_c_001.main_4 mn 1. Loop changes
/main/6      ---      rer 1. Corrected stability testing checks.
/main/7      ---      cm_xta_tcfsm_c_001.main_6 kc 1. Updated for fixing
                                                      klockwork errors
/main/8      ---      cm_xta_tcfsm_c_001.main_7  pkaX  1. Fix for 64bit compilation warning
/main/9      ----     cm_xta_tcfsm_c_001.main_8  nh    1. Updated for Psf-Diameter 1.1
                                                       release Removed cm_xta_app.[hx]
*********************************************************************91*/

