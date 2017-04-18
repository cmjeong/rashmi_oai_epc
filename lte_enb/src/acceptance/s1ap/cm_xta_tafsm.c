
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_tafsm.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:28 2015

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include <stdlib.h>
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta.h"
/* cm_xta_tafsm_c_001.main_7 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"

/* cm_xta_tafsm_c_001.main_7 Removed cm_xta_app.x for Psf-Diameter 1.1 */
#ifdef SIP
#endif 
PUBLIC CmXtaTAFsm  cmXtaTAFsm [CMXTA_MAX] =
{
   cmXtaTAFsmS0,           /* CMXTA_START_INIT          */
   cmXtaTAFsmS1,           /* CMXTA_START_CFG     */
   cmXtaTAFsmS2,           /* CMXTA_END_CFG       */
   cmXtaTAFsmS3,           /* CMXTA_START_RUN     */
   cmXtaTAFsmS4,           /* CMXTA_END_RUN       */
   cmXtaTAFsmS5,           /* CMXTA_START_CLN     */
   cmXtaTAFsmS6,           /* CMXTA_END_CLN       */
   cmXtaTAFsmS7,           /* CMXTA_SHUTDOWN      */
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
PUBLIC S16 cmXtaTAReq
(
S16             ret
)
#else
PUBLIC S16 cmXtaTAReq(ret)
S16             ret;
#endif
{
   TRC2(cmXtaTAReq)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTAReq(): Enter TA FSM\n"));

   /* Enter cmd STM */
   while (TRUE)
   {
      ret = cmXtaTAFsm [cmXtaCb.state](ret);

      /*-- Check if complete or wait for external
           events --*/
      if ((ret == CMXTA_ERR_PENDING)  ||
          (ret == CMXTA_ERR_COMPLETE))
         break;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaTAReq */

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
PUBLIC S16 cmXtaTAFsmS0
(
S16              ret
)
#else
PUBLIC S16 cmXtaTAFsmS0(ret)
S16              ret;
#endif
{
   Bool noShutDownMod;
   /* Updated for FTHA Integration Environment*/
#ifdef CMXTA_FTHA_INTEGRATED
   Pst      pst;
   Buffer *mBuf;
#endif

   TRC2(cmXtaTAFsmS0)

   noShutDownMod = FALSE;

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS0(): ret(%d)\n", ret));

   if ((cmXtaCb.mode & CMXTA_TA_MODE_DFLT_NOSHUTDOWN) == CMXTA_TA_MODE_DFLT_NOSHUTDOWN)
      noShutDownMod = TRUE;

   /*-- We reach either for the first time registeration
        or after the change of topology in case of topology
        mode --*/

   /*-- Register all layer instances, and post a message to
        self to continue the rest of the STM in the appropriate
        system task --*/

   /*-- Generate/Regenerate the new Pst structures to talk to
        layers --*/
   (Void)cmXtaMasterInitPst();

   /* Register all layer instances */
   if (cmXtaRegister() != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTAFsmS0(): Registeration failed\n"));

      /*-- Mark STM error --*/
      cmXtaCb.err = TRUE;

      /*-- Registeration itself failed, do cleanup and exit --*/
      cmXtaCb.state = CMXTA_SHUTDOWN;

      /*-- Return end of processing --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }
   /* cm_xta_tafsm_c_001.main_2 : Support for multiple proc */
   /*-- Hack for master/slave mode, SIP TA uses some of the SIP stack functions which 
        internally uses soCb.maxBlkSize --*/

   /*-- If running in multiple binary mode, bring up IPC module
        before we do anything else --*/
   if ((cmXtaCb.masterMode != CMXTA_TA_INST_NONE) &&
       (cmXtaAppIpcInit()  != CMXTA_ERR_NONE))
   {
      CMXTA_DBG_INFO((_cmxtap, "tst(): IPC init failed, exiting\n"));

      SExit();

      RETVALUE(CMXTA_ERR_INT);
   }
   /* cm_xta_tafsm_c_001.main_6: Removed the un-used code. */
   /*-- Move to the next FSM --*/
   /*-- Set state --*/
   cmXtaCb.state = CMXTA_START_CFG;

   /* Send a message to ENTST to initiate testing */
   if (cmXtaTAPstSelfMsg(NULLP, EVTSTTTSTINIT) != CMXTA_ERR_NONE)
   {
      /*-- Mark STM error --*/
      cmXtaCb.err = TRUE;

      /*-- Do cleanup and exit --*/
      cmXtaCb.state = CMXTA_SHUTDOWN;

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
PUBLIC S16 cmXtaTAFsmS1
(
S16              ret
)
#else
PUBLIC S16 cmXtaTAFsmS1(ret)
S16              ret;
#endif
{
   Bool noShutDownMod;
   CmXtaTCCb *tcCb;

   TRC2(cmXtaTAFsmS1)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS1(): ret(%d)\n", ret));

   noShutDownMod = FALSE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_DFLT_NOSHUTDOWN) == CMXTA_TA_MODE_DFLT_NOSHUTDOWN)
      noShutDownMod = TRUE;

   /*-- Check if network topology cfg required --*/
   if (noShutDownMod == FALSE)
   {
      /*-- Set state --*/
      cmXtaCb.state = CMXTA_START_RUN;

      /*-- Set state --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   /*-- If we reach here, we have to initiate the cfg procedures --*/
   /*-- Set the state --*/
   cmXtaCb.state = CMXTA_END_CFG;

   CMXTA_DBG_CALL((_cmxtap, "\nTA Configuration:\n"));
   CMXTA_DBG_CALL((_cmxtap, "-----------------\n"));

   /*-- Do network topology cfg from here in case of not shutdown mode --*/
   if ((tcCb = cmXtaTCCreate(CMXTA_CTXT_TA, 0, 0, (Void *)"tapa.sys.init")) == NULLP)
   {
      /*-- No TA cfg steps, proceed to run --*/
      /*-- Set state --*/

      CMXTA_DBG_CALLIND((_cmxtap, " Info      : No steps, skip\n"), 3);

      /*-- Set state --*/
      cmXtaCb.state = CMXTA_START_RUN;

      /*-- Set state --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS1(): Triggering TC FSM\n"));

   /*-- Set default tcCb in the curTCCb --*/
   cmXtaCb.curTCCb = tcCb;

   if ((ret = cmXtaTCReq(tcCb, CMXTA_ERR_NONE)) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTAFsmS1(): TC FSM call failed, initiate cleanup\n"));

      /*-- Mark STM error --*/
      cmXtaCb.err = TRUE;

      /*-- Do cleanup and exit --*/
      cmXtaCb.state = CMXTA_SHUTDOWN;

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
PUBLIC S16 cmXtaTAFsmS2
(
S16              ret
)
#else
PUBLIC S16 cmXtaTAFsmS2(ret)
S16              ret;
#endif
{
   TRC2(cmXtaTAFsmS2)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS2(): ret(%d)\n", ret));

   /*-- Check if any resource/internal error --*/
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTAFsmS2(): TG FSM failed, initiate cleanup\n"));

      /*-- Mark STM error --*/
      cmXtaCb.err = TRUE;

      cmXtaCb.state = CMXTA_SHUTDOWN;
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
      cmXtaCb.state = CMXTA_SHUTDOWN;
   }
   else
      cmXtaCb.state = CMXTA_START_RUN;

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
PUBLIC S16 cmXtaTAFsmS3
(
S16              ret
)
#else
PUBLIC S16 cmXtaTAFsmS3(ret)
S16              ret;
#endif
{
   Bool noShutDownMod;

   TRC2(cmXtaTAFsmS3)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS3(): ret(%d)\n", ret));

   noShutDownMod = FALSE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_DFLT_NOSHUTDOWN) == CMXTA_TA_MODE_DFLT_NOSHUTDOWN)
      noShutDownMod = TRUE;

   /*-- Check if network topology cfg required --*/
   if (noShutDownMod == TRUE)
   {
      CMXTA_DBG_CALL((_cmxtap, "\nTA Run Tests:\n"));
      CMXTA_DBG_CALL((_cmxtap,   "-------------\n"));
   }

   /*-- Network topology is skipped or it is successful. Lets
        start the test cases --*/

   /*-- Change the STM state before invoking the TG STM --*/
   cmXtaCb.state = CMXTA_END_RUN;

   /*-- Init/ReInit the TG and TCs --*/
   cmXtaTGInit();

   /* Setting state for STM outside the STM, see it as  
      create of STM rather */
   cmXtaCb.grpState = CMXTA_START_INIT;

   if ((ret = cmXtaTGReq(CMXTA_ERR_NONE)) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTAFsmS3(): TG FSM call failed, initiate cleanup\n"));

      /*-- Mark STM error --*/
      cmXtaCb.err = TRUE;

      cmXtaCb.state = CMXTA_SHUTDOWN;

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
PUBLIC S16 cmXtaTAFsmS4
(
S16              ret
)
#else
PUBLIC S16 cmXtaTAFsmS4(ret)
S16              ret;
#endif
{
   Bool noShutDownMod;

   TRC2(cmXtaTAFsmS4)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS4(): ret(%d)\n", ret));

   noShutDownMod = FALSE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_DFLT_NOSHUTDOWN) == CMXTA_TA_MODE_DFLT_NOSHUTDOWN)
      noShutDownMod = TRUE;

   /*-- Check if any resource/internal error --*/
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTAFsmS4(): TG FSM returned failure, initiate cleanup\n"));

      /*-- Mark STM error --*/
      cmXtaCb.err = TRUE;

      cmXtaCb.state = CMXTA_SHUTDOWN;
   }

   /*-- Set state --*/
   cmXtaCb.state = CMXTA_START_CLN;

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
PUBLIC S16 cmXtaTAFsmS5
(
S16              ret
)
#else
PUBLIC S16 cmXtaTAFsmS5(ret)
S16              ret;
#endif
{
   Bool noShutDownMod;

   Bool loopMode;
   CmXtaTCCb *tcCb;

   TRC2(cmXtaTAFsmS5)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS5(): ret(%d)\n", ret));

   noShutDownMod = FALSE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_DFLT_NOSHUTDOWN) == CMXTA_TA_MODE_DFLT_NOSHUTDOWN)
      noShutDownMod = TRUE;

   /*-- Check if network topology cleanup required --*/
   if (noShutDownMod == FALSE)
   {
      /*-- Set state --*/
      cmXtaCb.state = CMXTA_SHUTDOWN;

      /*-- Set state --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   loopMode = FALSE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_LOOP) == CMXTA_TA_MODE_LOOP)
      loopMode = TRUE;

   /*-- Check if loopMode and not the last loopCnt --*/
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
         CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS5(): Starting the next loop cnt(%d)\n", 
                      cmXtaCb.loopCnt));

         cmXtaCb.state = CMXTA_START_RUN;

         /*-- Return end of processing --*/
         RETVALUE(CMXTA_ERR_CONTINUE);
      }
   }

   /*-- If we reach here, we have to initiate the cleanup procedures --*/
   CMXTA_DBG_CALL((_cmxtap, "\nTA Cleanup:\n"));
   CMXTA_DBG_CALL((_cmxtap, "------------\n"));

   /*-- Set state --*/
   cmXtaCb.state = CMXTA_END_CLN;

   /*-- Do network topology cleanup from here in case of not shutdown mode --*/
   if ((tcCb = cmXtaTCCreate(CMXTA_CTXT_TA, 0, 0, (Void *)"tapa.sys.deinit")) == NULLP)
   {
      /*-- No TA cfg steps, proceed to run --*/
      /*-- Set state --*/

      CMXTA_DBG_CALLIND((_cmxtap, " Info      : No steps, skip\n"), 3);

      /*-- Set state --*/
      cmXtaCb.state = CMXTA_SHUTDOWN;

      /*-- Set state --*/
      RETVALUE(CMXTA_ERR_CONTINUE);
   }

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS5(): Triggering TC FSM\n"));

   /*-- Set default tcCb in the curTCCb --*/
   cmXtaCb.curTCCb = tcCb;

   if ((ret = cmXtaTCReq(tcCb, CMXTA_ERR_NONE)) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_FATAL((_cmxtap, "cmXtaTAFsmS5(): TC FSM call failed, initiate cleanup\n"));

      /*-- Mark STM error --*/
      cmXtaCb.err = TRUE;

      /*-- Do cleanup and exit --*/
      cmXtaCb.state = CMXTA_SHUTDOWN;

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
PUBLIC S16 cmXtaTAFsmS6
(
S16              ret
)
#else
PUBLIC S16 cmXtaTAFsmS6(ret)
S16              ret;
#endif
{
   TRC2(cmXtaTAFsmS6)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS6(): ret(%d)\n", ret));

   /*-- Wait here for the result of network topology delete --*/
   if (ret != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTAFsmS6(): TA cleanup failed, shutdown anyway\n"));

      /*-- Mark STM error --*/
      cmXtaCb.err = TRUE;
   }

   /*-- No point checking TA level shutdown failure result, just move
        to shutdown --*/
   if (cmXtaCb.result == CMXTA_TEST_FAILED)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTAFsmS6(): TA cleanup failed, shutdown anyway\n"));
   }

   /*-- Set state --*/
   cmXtaCb.state = CMXTA_SHUTDOWN;

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
PUBLIC S16 cmXtaTAFsmS7
(
S16              ret
)
#else
PUBLIC S16 cmXtaTAFsmS7(ret)
S16              ret;
#endif
{
   U16  totalTop;

   Bool dfltMode;
   Bool loopMode;
   Bool noGrpShutDownMod;
   Bool topMode;

   TRC2(cmXtaTAFsmS7)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS7(): ret(%d)\n", ret));

   dfltMode = FALSE;
   loopMode = FALSE;
   topMode = FALSE;
   noGrpShutDownMod = FALSE;

   /*-- The loop mode code here is for the normal mode, the no shutdown mode
        loop will happen from clean STM --*/
   if ((cmXtaCb.mode & CMXTA_TA_MODE_GRPNOSHUTDOWN) == CMXTA_TA_MODE_GRPNOSHUTDOWN)
      noGrpShutDownMod = TRUE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_DFLT) == CMXTA_TA_MODE_DFLT)
      dfltMode = TRUE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_MULT_TOP) == CMXTA_TA_MODE_MULT_TOP)
      topMode = TRUE;

   if ((cmXtaCb.mode & CMXTA_TA_MODE_LOOP) == CMXTA_TA_MODE_LOOP)
      loopMode = TRUE;

   /* In case of test cases running in loop, restart the test cases */
   /* If multiple topology mode, select the next topology, if last, start from
      the first */

   /* Find total toplogies */
   totalTop = topCount;

   /*-- Check if error set, or configuration failed --*/
   if ((cmXtaCb.err == TRUE)  ||
       (cmXtaCb.result == CMXTA_TEST_FAILED))
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTAFsmS7(): Shutting down the TA\n"));

      CMXTA_DBG_CALL((_cmxtap, "Info      : Shutting down the TA\n"));

      /*-- Destroy all system tasks --*/
      cmXtaDeRegister(TRUE);

      /*-- Release global resources --*/
      cmXtaMasterDeInit();

      /*-- Check we have to show the SSI memory usage here --*/
      cmXtaLogXml(NULLP, CMXTA_MEM_TA_DEINIT);

      /*-- Check we have to capture XML logs here --*/
      cmXtaLogXml(NULLP, CMXTA_MEM_LOG_DEINIT);

      SExit();
   }
   else if (noGrpShutDownMod == TRUE)
   {
      /*-- First take care of no TG shutdown mode --*/
      /*-- For no TG shutdown mode, the looping is handled
           in TG STM, take care of topology mode here --*/
      if (topMode == TRUE)
      {
         /* Max loop reached, check if more topology */

         /* Find the next valid process topology */
         while (++cmXtaCb.curTopId < totalTop)
         {
            if (cmXtaTop[cmXtaCb.curTopId].valid == TRUE)
               break;
         }

         /* Check if last topology */
         if (cmXtaCb.curTopId < totalTop)
         {
            CMXTA_DBG_CALL((_cmxtap, "Info      : Restarting TA\n"));

            CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS7(): Restarting the TA with new topology (%d)\n", 
                         cmXtaCb.curTopId));

            /*-- Destroy all system tasks --*/
            cmXtaDeRegister(FALSE);

            /*-- Last topology not reached, restart the loop --*/
            /*-- In case of a new topology, all the system tasks
              are destroyed and are respawned, hence start from
              the INIT state --*/
            cmXtaCb.state = CMXTA_START_INIT;

            /*-- Return end of processing --*/
            RETVALUE(CMXTA_ERR_CONTINUE);
         }
         else
         {
            CMXTA_DBG_CALL((_cmxtap, "Info      : Shutting down the TA\n"));

            CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS7(): Shutting down the TA\n"));

            /*-- Destroy all system tasks --*/
            cmXtaDeRegister(TRUE);

            /*-- Release global resources --*/
            cmXtaMasterDeInit();

            /*-- Check we have to show the SSI memory usage here --*/
            cmXtaLogXml(NULLP, CMXTA_MEM_TA_DEINIT);

            /*-- Check we have to capture XML logs here --*/
            cmXtaLogXml(NULLP, CMXTA_MEM_LOG_DEINIT);

            SExit();
         }
      }
      else
      {
         CMXTA_DBG_CALL((_cmxtap, "Info      : Shutting down the TA\n"));

         /*-- Normal mode --*/
         CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS7(): Shutting down the TA\n"));

         /*-- Destroy all system tasks --*/
         cmXtaDeRegister(TRUE);

         /*-- Release global resources --*/
         cmXtaMasterDeInit();

         /*-- Check we have to show the SSI memory usage here --*/
         cmXtaLogXml(NULLP, CMXTA_MEM_TA_DEINIT);

         /*-- Check we have to capture XML logs here --*/
         cmXtaLogXml(NULLP, CMXTA_MEM_LOG_DEINIT);

         SExit();
      }
   }
   else if ((loopMode == TRUE) && (topMode == TRUE))
   {
      /*-- Check if max loop reached, then search for next topology --*/
      if (++cmXtaCb.loopCnt < cmXtaCb.maxLoopCnt)
      {
         /*-- Max loop not reached, restart the loop, in case of
              default mode, CFG state is not required and in case
              of no shutdown, the CLN state would not have been
              executed, hence directly jump to running the test
              cases --*/
         cmXtaCb.state = CMXTA_START_RUN;

         CMXTA_DBG_CALL((_cmxtap, "Info      : Restarting TA\n"));

         CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS7(): Starting the next loop cnt(%d)\n", 
                      cmXtaCb.loopCnt));

         /*-- Return end of processing --*/
         RETVALUE(CMXTA_ERR_CONTINUE);
      }
      else
      {
         /* Max loop reached, check if more topology */

         /* Find the next valid process topology */
         while (++cmXtaCb.curTopId < totalTop)
         {
            if (cmXtaTop[cmXtaCb.curTopId].valid == TRUE)
               break;
         }

         /* Check if last topology */
         if (cmXtaCb.curTopId < totalTop)
         {
            CMXTA_DBG_CALL((_cmxtap, "Info      : Restarting TA\n"));

            CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS7(): Restarting the TA with new topology (%d)\n", 
                         cmXtaCb.curTopId));

            /*-- Destroy all system tasks --*/
            cmXtaDeRegister(FALSE);

            /*-- Last topology not reached, restart the loop --*/
            /*-- In case of a new topology, all the system tasks
                 are destroyed and are respawned, hence start from
                 the INIT state --*/
            cmXtaCb.state = CMXTA_START_INIT;

            /*-- Reset the loop Count --*/
            cmXtaCb.loopCnt = 0;

            /*-- Return end of processing --*/
            RETVALUE(CMXTA_ERR_CONTINUE);
         }
         else
         {
            CMXTA_DBG_CALL((_cmxtap, "Info      : Shutting down the TA\n"));

            CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS7(): Shutting down the TA\n"));

            /*-- Destroy all system tasks --*/
            cmXtaDeRegister(TRUE);

            /*-- Release global resources --*/
            cmXtaMasterDeInit();

            /*-- Check we have to show the SSI memory usage here --*/
            cmXtaLogXml(NULLP, CMXTA_MEM_TA_DEINIT);

            /*-- Check we have to capture XML logs here --*/
            cmXtaLogXml(NULLP, CMXTA_MEM_LOG_DEINIT);

            SExit();
         }
      }
   }
   else if (topMode == TRUE)
   {
      /* Max loop reached, check if more topology */

      /* Find the next valid process topology */
      while (++cmXtaCb.curTopId < totalTop)
      {
         if (cmXtaTop[cmXtaCb.curTopId].valid == TRUE)
            break;
      }

      /* Check if last topology */
      if (cmXtaCb.curTopId < totalTop)
      {
         CMXTA_DBG_CALL((_cmxtap, "Info      : Restarting TA\n"));

         CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS7(): Restarting the TA with new topology (%d)\n", 
                      cmXtaCb.curTopId));

         /*-- Destroy all system tasks --*/
         cmXtaDeRegister(FALSE);

         /*-- Last topology not reached, restart the loop --*/
         /*-- In case of a new topology, all the system tasks
              are destroyed and are respawned, hence start from
              the INIT state --*/
         cmXtaCb.state = CMXTA_START_INIT;

         /*-- Return end of processing --*/
         RETVALUE(CMXTA_ERR_CONTINUE);
      }
      else
      {
         CMXTA_DBG_CALL((_cmxtap, "Info      : Shutting down the TA\n"));

         CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS7(): Shutting down the TA\n"));

         /*-- Destroy all system tasks --*/
         cmXtaDeRegister(TRUE);

         /*-- Release global resources --*/
         cmXtaMasterDeInit();

         /*-- Check we have to show the SSI memory usage here --*/
         cmXtaLogXml(NULLP, CMXTA_MEM_TA_DEINIT);

         /*-- Check we have to capture XML logs here --*/
         cmXtaLogXml(NULLP, CMXTA_MEM_LOG_DEINIT);

         SExit();
      }
   }
   else if (loopMode == TRUE)
   {
      /*-- Check if max loop reached --*/
      if (++cmXtaCb.loopCnt < cmXtaCb.maxLoopCnt)
      {
         /*-- Max loop not reached, restart the loop, in case of
              default mode, CFG state is not required and in case
              of no shutdown, the CLN state would not have been
              executed, hence directly jump to running the test
              cases --*/
         cmXtaCb.state = CMXTA_START_RUN;

         CMXTA_DBG_CALL((_cmxtap, "Info      : Restarting TA\n"));

         CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS7(): Starting the next loop cnt(%d)\n",
                      cmXtaCb.loopCnt));

         /*-- Return end of processing --*/
         RETVALUE(CMXTA_ERR_CONTINUE);
      }
      else
      {
         CMXTA_DBG_CALL((_cmxtap, "Info      : Shutting down the TA\n"));

         CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS7(): Shutting down the TA\n"));

         /*-- Destroy all system tasks --*/
         cmXtaDeRegister(TRUE);

         /*-- Release global resources --*/
         cmXtaMasterDeInit();

         /*-- Check we have to show the SSI memory usage here --*/
         cmXtaLogXml(NULLP, CMXTA_MEM_TA_DEINIT);

         /*-- Check we have to capture XML logs here --*/
         cmXtaLogXml(NULLP, CMXTA_MEM_LOG_DEINIT);

         SExit();
      }
   }
   else
   {
      CMXTA_DBG_CALL((_cmxtap, "Info      : Shutting down the TA\n"));

      /*-- Normal mode --*/
      CMXTA_DBG_INFO((_cmxtap, "cmXtaTAFsmS7(): Shutting down the TA\n"));

      /*-- Destroy all system tasks --*/
      cmXtaDeRegister(TRUE);

      /*-- Release global resources --*/
      cmXtaMasterDeInit();

      /*-- Check we have to show the SSI memory usage here --*/
      cmXtaLogXml(NULLP, CMXTA_MEM_TA_DEINIT);

      /*-- Check we have to capture XML logs here --*/
      cmXtaLogXml(NULLP, CMXTA_MEM_LOG_DEINIT);

      SExit();
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
PUBLIC S16 cmXtaTAPstSelfMsg
(
Void *ptr,
U8   event
)
#else
PUBLIC S16 cmXtaTAPstSelfMsg(ptr, event)
Void *ptr;
U8   event;
#endif 
{
   Buffer *mBuf;
   Pst    pst;
   Pst    *ptrPst;
   U8     msg[2];
   ProcId         srcProcId;
   ProcId         dstProcId;

   TRC2(cmXtaTAPstSelfMsg)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTAPstSelfMsg(): Post self message\n"));

   ptrPst = &pst;
   /* Moved the cmXtaGetPst out of the Multiple Proc flag*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaGetPst(&pst, ENTTST, CMXTA_INST_ID, ENTTST, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
   pst.event = event;

   CMXTA_ALLOCMBUF(&mBuf);

   if (mBuf != NULLP)
   {
      if (ptr != NULLP)
      {
         CMCHKPKLOG(cmPkPtr, (PTR)ptr, mBuf, 0, ptrPst);
      }
      else
      {
         SAddPstMsgMult ((Data *)msg, 2 * sizeof(U8), mBuf);
      }

      SPstTsk(&pst, mBuf);
   }
   else
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaTAPstSelfMsg(): self msg sending failed\n"));

      RETVALUE(CMXTA_ERR_RSRC);
   }

   RETVALUE(CMXTA_ERR_NONE);
}

/********************************************************************30**

         End of file:     cm_xta_tafsm.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:28 2015

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
/main/3      ---      cm_xta_tafsm_c_001.main_2  sk  1. Support for multiple proc
/main/4      ---      rb  1. Updated for PDCP Software release 1.1
/main/5      ---      st  1. Incorporated SIP related file inclusion changes.
/main/6      ---      aj  1. Updated for FTHA Integration  
                          2. Moved the cmXtaGetPst out of the Multiple Proc flag 
/main/7      ---      cm_xta_tafsm_c_001.main_6 pka 1. Removed the unused code.                          
/main/8      ----     cm_xta_tafsm_c_001.main_7 jj 1. Updated for Psf-Diameter 1.1
                          release Removed cm_xta_app.[hx]
*********************************************************************91*/
