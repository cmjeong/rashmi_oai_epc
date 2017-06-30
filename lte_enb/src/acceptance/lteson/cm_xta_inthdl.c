
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_inthdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:59:17 2015

     Prg:     up 

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_mem.h"         /*common memory file             */
#include "cm_hash.h"        /* common hash list             */
#include "cm_llist.h"      /* common link list */

#include "cm_xta.h"
/* cm_xta_inthdl_c_001.main_12 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */
/* cm_xta_inthdl_c_001.main_10: Deleted cm_mem.x */
#include "cm_xta.x"

/* cm_xta_inthdl_c_001.main_12 Removed cm_xta_app.x for Psf-Diameter 1.1 */
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
PUBLIC S16 cmXtaHdlIntSend
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntSend(tcCb, spCb)
CmXtaTCCb    *tcCb;   /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Void     *cmd;
   S16      ret;
   CmXtaXmlCb *xmlCb;

   TRC2(cmXtaHdlIntSend)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntSend(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntSend(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*-- LC execution of steps --*/
   if (tcCb->lcStep == FALSE)
   {
      /*-- We are here for the first time, check if the step
           mandates a LC execution. If so, skip the step here 
           and mark as having already skipped --*/

      /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
      cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "lc",  &tcCb->lcStep);

      if (tcCb->lcStep == TRUE)
      {
         /*-- The doc for the test case is already printed, so mark the test
           case as running, so that the doc is not printed again --*/
         spCb->state = CMXTA_RUN;

         RETVALUE(CMXTA_ERR_SKIP);
      }
   }

   /*-- If we are here, either the LC step was not set, or we are here for
        the second time, reset the LC step flag if set --*/
   tcCb->lcStep = FALSE;

   /*-- Reset the spCb state before any checks, so that state is
        reset even in case of failures --*/
   spCb->state = CMXTA_INIT;

   /*-- Locate the simple command handler --*/
   if ((cmd = cmXtaXmlFirstChildOfType(spCb->curStep,
                                  CMXTA_DOM_ELEMENT_NODE)) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntSend(): cmd not found\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Get the XML cb for the simple command --*/
   if ((xmlCb = cmXtaXmlFindFromXml(cmd)) == NULLP)
   {
      /*-- XML cmd not registered, flag error --*/
      CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntSend(): XML cmd not registered\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Sanity check, check its a simple command and of type other --*/
   if ((xmlCb->cmdType != CMXTA_TYPE_LEAF) ||
       (xmlCb->subType != CMXTA_SUBTYPE_OTHER))
   {
      /*-- Wrong type of command inside send tag, validate the test case
           flag error --*/
      CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntSend(): invalid cmd in <tapa.send>\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set the child element, this may be used for getting the attributes --*/
   spCb->childStep = cmd;

   /*-- Lets make a call finally --*/
   if ((ret = xmlCb->func(tcCb, spCb)) != CMXTA_ERR_NONE)
   {
      /*-- In case of no match, should we release message here --*/
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Error while sending message\n"), 3);

      RETVALUE(ret);
   }

   /*-- Load mode for TA --*/
   /*-- If load Mode is TRUE, then stored the parsed information
        in the global load step list. The product specific information
        shall be/would have been captured by the product handler functions --*/
   if (cmXtaCb.loadDir.loadMode == TRUE)
   {
      cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].cmdType = spCb->xmlCb->cmdType;
      cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].subType = spCb->xmlCb->subType;

      /*-- Increment the step information --*/
      cmXtaCb.nxtLoadIndx++;
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlIntSend */

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
PUBLIC S16 cmXtaHdlIntExpect
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntExpect(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Void     *cmd;
   S16      ret;
   CmXtaXmlCb *xmlCb;
   CmXtaMsgQElm   *msg;
   U8       queue;

   TRC2(cmXtaHdlIntExpect)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntExpect(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntExpect(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   /* cm_xta_inthdl_c_001.main_2 : Support for multiple queues */
   queue = 0;
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_U8, "queue", &queue);
   /*-- Reset the spCb state before any checks, so that state is
        reset even in case of failures --*/
   spCb->state = CMXTA_INIT;

   /*-- Locate the simple command handler --*/
   if ((cmd = cmXtaXmlFirstChildOfType(spCb->curStep,
                                  CMXTA_DOM_ELEMENT_NODE)) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpect(): cmd not found\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Get the XML cb for the simple command --*/
   if ((xmlCb = cmXtaXmlFindFromXml(cmd)) == NULLP)
   {
      /*-- XML cmd not registered, flag error --*/
      CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpect(): XML cmd not registered\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Sanity check, check its a simple command and of type other --*/
   if ((xmlCb->cmdType != CMXTA_TYPE_LEAF) ||
       (xmlCb->subType != CMXTA_SUBTYPE_OTHER))
   {
      /*-- Wrong type of command inside send tag, validate the test case
           flag error --*/
      CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpect(): invalid cmd in <tapa.expect>\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set the child element, this may be used for getting the attributes --*/
   spCb->childStep = cmd;

   /*-- Lets make a call finally --*/
   ret = xmlCb->func(tcCb, spCb);

   /*-- Load mode for TA --*/
   /*-- If load Mode is TRUE, then stored the parsed information
        in the global load step list. The product specific information
        shall be/would have been captured by the product handler functions --*/
   if (cmXtaCb.loadDir.loadMode == TRUE)
   {
      cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].cmdType = spCb->xmlCb->cmdType;
      cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].subType = spCb->xmlCb->subType;

      /*-- Increment the step information --*/
      cmXtaCb.nxtLoadIndx++;
   }

   /*-- Throw message only for real execution, skip the same in load mode --*/
   if (cmXtaCb.loadDir.loadMode == FALSE)
   {
      if (ret == CMXTA_ERR_NOMATCH)
      {
         /*-- In case of no match, should we release message here --*/
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : Unexpected message received\n"), 3);

         /*-- Invalid message was received, most likely we will skip rest of the test
           steps and move to shutdown, it makes sense to remove this message since
           it will again cause failure for shutdown steps. No one is interested
           in this message anyway in the first place and thats the reason for the
           failure. Let the world know though --*/

         CMXTA_DBG_INFO((_cmxtap, "cmXtaHdlIntExpect(): Dropping unexpected message\n"));

         /*-- Remove the msg from the Queue --*/
         cmXtaPopMsg (&(tcCb->msgQ[queue]), &msg);

         /* cm_xta_inthdl_c_001.main_9 :Added NULL check */
         if(!msg)
         {
            CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpect(): msg is NULL\n"));
            RETVALUE(CMXTA_ERR_INT);
         }
         /*-- Flush --*/
         cmXtaFlushMsg (&(tcCb->msgQ[queue]), msg);
      }
   }

   RETVALUE(ret);
}/* cmXtaHdlIntExpect */

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
PUBLIC S16 cmXtaHdlIntExpSeq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntExpSeq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Void     *cmd;
   S16      ret;
   CmXtaMsgQElm   *msg;

   TRC2(cmXtaHdlIntExpSeq)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntExpSeq(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntExpSeq(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*-- Mark the state as first time or waiting for more messages --*/
   if (tcCb->expSeq == FALSE)
   {
      /*-- Reset the expSeq before any checks, so that state is
        reset even in case of failures --*/
      tcCb->expSeq = TRUE;

      tcCb->seqCnt =    0;
      tcCb->minSeqCnt = 1;
      tcCb->maxSeqCnt = 1;

      /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
      cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_U16, "min",  &tcCb->minSeqCnt);
      cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_U16, "max",  &tcCb->maxSeqCnt);

      /*-- In case of seq, the leaf handler may get called multiple times, hence
           maintain the pointer after the first time in tcCb --*/

      /*-- Locate the simple command handler --*/
      if ((cmd = cmXtaXmlFirstChildOfType(spCb->curStep,
                  CMXTA_DOM_ELEMENT_NODE)) == NULLP)
      {
         /*-- Reset the spCb state before any checks, so that state is
           reset even in case of failures --*/
         spCb->state = CMXTA_INIT;

         CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpSeq(): cmd not found\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      /*-- Get the XML cb for the simple command --*/
      if ((tcCb->seqXmlCb = cmXtaXmlFindFromXml(cmd)) == NULLP)
      {
         /*-- Reset the spCb state before any checks, so that state is
           reset even in case of failures --*/
         spCb->state = CMXTA_INIT;

         /*-- XML cmd not registered, flag error --*/
         CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpSeq(): XML cmd not registered\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      /*-- Sanity check, check its a simple command and of type other --*/
      if ((tcCb->seqXmlCb->cmdType != CMXTA_TYPE_LEAF) ||
          (tcCb->seqXmlCb->subType != CMXTA_SUBTYPE_OTHER))
      {
         /*-- Reset the spCb state before any checks, so that state is
           reset even in case of failures --*/
         spCb->state = CMXTA_INIT;

         /*-- Wrong type of command inside send tag, validate the test case
           flag error --*/
         CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpSeq(): invalid cmd in <tapa.expseq>\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      /*-- Set the child element, this may be used for getting the attributes --*/
      spCb->childStep = cmd;

      /*-- Load mode for TA --*/
      /*-- If load Mode is TRUE, then stored the parsed information
           in the global load step list. The product specific information
           shall be captured by the product handler functions --*/
      if (cmXtaCb.loadDir.loadMode == TRUE)
      {
         cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].cmdType = spCb->xmlCb->cmdType;
         cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].subType = spCb->xmlCb->subType;

         /*-- Update min and max sequence count --*/
         cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].seqCnt    = tcCb->seqCnt;
         cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].minSeqCnt = tcCb->minSeqCnt;
         cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].minSeqCnt = tcCb->maxSeqCnt;
      }
   }

   /*-- Lets make a call finally --*/
   ret = tcCb->seqXmlCb->func(tcCb, spCb);

   /*-- Skip further processing for load mode, the same shall be done in load engine --*/
   if (cmXtaCb.loadDir.loadMode == FALSE)
   {
      /*-- Increment the step information --*/
      cmXtaCb.nxtLoadIndx++;

      RETVALUE(ret);
   }

   /*-- No load mode, lets proceed further --*/
   if (ret == CMXTA_ERR_NONE)
   {
      /*-- Success, increment sequence count --*/

      /*-- Validate the boundary conditions --*/

      /*-- Still scope for more messages, suspend --*/

      /*-- Maximum match reached, time to leave this handler, it may be possible
        that more messages for the same arrive, so if we move ahead, and the
        same message arrives again, it may fail to match with the next handler
        and fail with an message type mismatch. From TA perspective, both the 
        scenarios are fine, but from debugging perspective, it would be a good 
        idea to flag the error that extra this kind of messages were received 
        rather than a mismatch error with the next handler --*/
      if (tcCb->seqCnt <= tcCb->maxSeqCnt)
         RETVALUE(CMXTA_ERR_PENDING);
      else if (tcCb->seqCnt > tcCb->maxSeqCnt)
      {
         /*-- Reset the spCb state before any checks, so that state is
           reset even in case of failures --*/
         spCb->state = CMXTA_INIT;

         CMXTA_DBG_CALLIND((_cmxtap, "Failed : Extra messages [cnt > %ul] received\n", tcCb->maxSeqCnt), 3);

         /*-- Reset the expSeq --*/
         tcCb->expSeq = FALSE;

         /*-- The message was already processed and consumed by the leaf handler,
           nothing to do here --*/
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else if (ret == CMXTA_ERR_NOMATCH)
   {
      /*-- Match Failure, see if we have already met our requirements --*/

      /*-- Reset the expSeq --*/
      tcCb->expSeq = FALSE;

      /*-- Validate the boundary conditions --*/
      if (tcCb->seqCnt < tcCb->minSeqCnt)
      {
         /*-- Reset the spCb state before any checks, so that state is
           reset even in case of failures --*/
         spCb->state = CMXTA_INIT;

         CMXTA_DBG_CALLIND((_cmxtap, "Failed : Less messages received, Expected: [%ul] Received: [%ul]",
                  tcCb->minSeqCnt, tcCb->seqCnt), 3);

         /*-- Invalid message was received, most likely we will skip rest of the test
           steps and move to shutdown, it makes sense to remove this message since
           it will again cause failure for shutdown steps. No one is interested
           in this message anyway in the first place and thats the reason for the
           failure. Let the world know though --*/

         CMXTA_DBG_INFO((_cmxtap, "cmXtaHdlIntExpSeq(): Dropping unexpected message\n"));

         /*-- Remove the msg from the Queue --*/
         cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
         
         /* cm_xta_inthdl_c_001.main_9 :Added NULL check */
         if(!msg)
         {
            CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpSeq(): msg is NULL\n"));
            RETVALUE(CMXTA_ERR_INT);
         }
         /*-- Flush --*/
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

         RETVALUE(CMXTA_ERR_INT);
      }
      /*-- Our conditions are already met, jump to the next handler, do not consume
           the message, because it may be for the next handler --*/
      else  RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Reset the expSeq --*/
   tcCb->expSeq = FALSE;

   RETVALUE(ret);
}/* cmXtaHdlIntExpSeq */


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
PUBLIC S16 cmXtaHdlIntExpOpt
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntExpOpt(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Void     *cmd;
   /* cm_xta_inthdl_c_001.main_9 : Added initialization */
   S16      ret = CMXTA_ERR_NOMATCH;
   CmXtaXmlCb *xmlCb;

   TRC2(cmXtaHdlIntExpOpt)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntExpOpt(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntExpOpt(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*-- Reset the spCb state before any checks, so that state is
        reset even in case of failures --*/
   spCb->state = CMXTA_INIT;

   /*-- Reset flag to wait for an optional message --*/
   tcCb->expOptMsg = FALSE;

   /*-- Process message only if we did not come here for the timer expiry --*/
   /*-- Process message for load mode as well --*/
   if ((tcCb->guardTmr != TRUE)     ||
       (cmXtaCb.loadDir.loadMode == TRUE))
   {
      /*-- Locate the simple command handler --*/
      if ((cmd = cmXtaXmlFirstChildOfType(spCb->curStep,
                  CMXTA_DOM_ELEMENT_NODE)) == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpOpt(): cmd not found\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      /*-- Get the XML cb for the simple command --*/
      if ((xmlCb = cmXtaXmlFindFromXml(cmd)) == NULLP)
      {
         /*-- XML cmd not registered, flag error --*/
         CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpOpt(): XML cmd not registered\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      /*-- Sanity check, check its a simple command and of type other --*/
      if ((xmlCb->cmdType != CMXTA_TYPE_LEAF) ||
          (xmlCb->subType != CMXTA_SUBTYPE_OTHER))
      {
         /*-- Wrong type of command inside send tag, validate the test case
           flag error --*/
         CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpOpt(): invalid cmd in <tapa.expectopt>\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      /*-- Set the child element, this may be used for getting the attributes --*/
      spCb->childStep = cmd;

      /*-- Lets make a call finally --*/
      ret = xmlCb->func(tcCb, spCb);

      /*-- Load mode for TA --*/
      /*-- If load Mode is TRUE, then stored the parsed information
        in the global load step list. The product specific information
        shall be captured by the product handler functions --*/
      if (cmXtaCb.loadDir.loadMode == TRUE)
      {
         cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].cmdType = xmlCb->cmdType;
         cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].subType = xmlCb->subType;

         cmXtaCb.loadSteps[cmXtaCb.nxtLoadIndx].expOptMsg = TRUE;

         /*-- Increment the step information --*/
         cmXtaCb.nxtLoadIndx++;

         RETVALUE(ret);
      }
   }

   if ((ret == CMXTA_ERR_NOMATCH)  ||
       (tcCb->guardTmr = TRUE))
   {
      CMXTA_DBG_CALLIND((_cmxtap, " Info      : Optional message not received, continue\n"), 3);

      /*-- Reset guard timer, in case we came on timer expiry --*/
      tcCb->guardTmr = FALSE;

      RETVALUE(CMXTA_ERR_NONE);
   }

   RETVALUE(ret);
}/* cmXtaHdlIntExpOpt */


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
PUBLIC S16 cmXtaHdlIntExpSet
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntExpSet(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Void     *nxtStep;
   S16      ret;
   CmXtaXmlCb *xmlCb;
   CmXtaMsgQElm   *msg;

   Bool     match;
   U16      stepCnt;

   TRC2(cmXtaHdlIntExpSet)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntExpSet(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntExpSet(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*-- Find the first free step count --*/
   stepCnt = 0;
   match = FALSE;
   nxtStep = NULLP;

   /*-- If we come here for the first time, lets calculate the max set steps --*/
   if (tcCb->setCnt == 0)
   {
      tcCb->setRcvdCnt = 0;

      /*-- First time --*/
      while ((nxtStep = cmXtaXmlGetNextOfType(spCb->curStep, 
              nxtStep, CMXTA_DOM_ELEMENT_NODE)) != NULLP)
      {
         tcCb->setCnt++;

         if (tcCb->setCnt == CMXTA_MAX_EXP_SET_MSG)
            break;
      }
   }

   nxtStep = NULLP;
   while ((nxtStep = cmXtaXmlGetNextOfType(spCb->curStep, 
           nxtStep, CMXTA_DOM_ELEMENT_NODE)) != NULLP)
   {
      /*-- Check if free set step --*/
      if (tcCb->expSet[stepCnt] == TRUE)
      {
         stepCnt++;

         /*-- If all steps met, return --*/
         if (stepCnt == tcCb->setCnt) break;
         else continue;
      }
      else
      {
         /*-- If we are here, that means the we found a free step --*/

         /*-- Get the XML cb for the simple command --*/
         if ((xmlCb = cmXtaXmlFindFromXml(nxtStep)) == NULLP)
         {
            /*-- XML cmd not registered, flag error --*/
            CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpSet(): XML cmd not registered\n"));
            RETVALUE(CMXTA_ERR_INT);
         }

         /*-- Sanity check, check its a simple command and of type other --*/
         if ((xmlCb->cmdType != CMXTA_TYPE_LEAF) ||
             (xmlCb->subType != CMXTA_SUBTYPE_OTHER))
         {
            /*-- Wrong type of command inside send tag, validate the test case
              flag error --*/
            CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpSet(): invalid cmd in <tapa.expset>\n"));
            RETVALUE(CMXTA_ERR_INT);
         }

         /*-- Set the child element, this may be used for getting the attributes --*/
         spCb->childStep = nxtStep;

         /*-- Lets make a call finally --*/
         ret = xmlCb->func(tcCb, spCb);

         if (ret == CMXTA_ERR_NONE)
         {
            /*-- Success, set set step --*/
            tcCb->expSet[stepCnt] = TRUE;

            match = TRUE;
            break;
         }
         /*-- Match Failure, see if we have more steps pending --*/
         else if (ret == CMXTA_ERR_NOMATCH)
         {
            stepCnt++;

            /*-- If all steps met, return --*/
            if (stepCnt == tcCb->setCnt) break;
            else continue;
         }
         /*-- Any other error, break --*/
         else break;
      }
   }

   if (match == FALSE)
   {
      /*-- Reset the spCb state before any checks, so that state is
        reset even in case of failures --*/
      spCb->state = CMXTA_INIT;

      /*-- Reset set count --*/
      tcCb->setCnt = 0;

      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Unexpected message received\n"), 3);

      /*-- Invalid message was received, most likely we will skip rest of the test
        steps and move to shutdown, it makes sense to remove this message since
        it will again cause failure for shutdown steps. No one is interested
        in this message anyway in the first place and thats the reason for the
        failure. Let the world know though --*/

      /* Please Note: In case of the handler returning CMXTA_ERR_INT if something 
         does not match we will crash here, as we will try to flush and empty 
         queue */
      CMXTA_DBG_INFO((_cmxtap, "cmXtaHdlIntExpect(): Dropping unexpected message\n"));

      /*-- Remove the msg from the Queue --*/
      cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

      /* cm_xta_inthdl_c_001.main_9 :Added NULL check */
      if(!msg)
      {
         CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntExpSet(): msg is NULL\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      /*-- Flush --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

      RETVALUE(CMXTA_ERR_INT);
   }
   else
   {
      tcCb->setRcvdCnt++;

      CMXTA_DBG_CALLIND((_cmxtap, " Info      : Received message [%u] from the set\n", 
                      tcCb->setRcvdCnt), 3);

      /*-- Match found, check if all steps met --*/
      if (tcCb->setRcvdCnt < tcCb->setCnt)
         RETVALUE(CMXTA_ERR_PENDING);
   }

   /*-- Reset the spCb state before any checks, so that state is
     reset even in case of failures --*/
   spCb->state = CMXTA_INIT;

   /*-- Reset set count --*/
   tcCb->setCnt = 0;


   CMXTA_ZERO(tcCb->expSet, CMXTA_MAX_EXP_SET_MSG * sizeof(Bool));

   /*-- All steps matched, return success --*/
   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlIntExpSet */

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
PUBLIC S16 cmXtaHdlIntTimeout
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntTimeout(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   S16      ret;
   U16      tmrVal;
   CmXtaMsgQElm   *msg;
   Pst      pst;
   ProcId         srcProcId;
   ProcId         dstProcId;

   TRC2(cmXtaHdlIntTimeout)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntTimeout(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntTimeout(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*-- Internal command to handle timeout --*/

   /*-- Start a timer and wait for the timer expiry, if any other message
        is received before the timer expiry, flag error --*/

   /*-- Mark the state as first time or waiting for the timer expiry --*/
   if (tcCb->timeOutState == CMXTA_NONE)
   {
      tmrVal = CMXTA_TMR_TIMEOUT_VAL;

      /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
      cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_U16, "timeout",  &tmrVal);

      /*-- First time, start timer and suspend the test case --*/
      /*-- This happens if the test is waiting for an external
        event, start the timeout timer and suspend, yawn --*/
      cmXtaStartTmr(CMXTA_TMR_TIMEOUT, tcCb, tmrVal);

      /*-- Set state --*/
      tcCb->timeOutState = CMXTA_RUN;

      /*-- Return a positive value here, since you do
        not know which function has triggered the
        engine, better handle it using TC Callback
        as done above --*/
      RETVALUE(CMXTA_ERR_PENDING);
   }
   else
   {
      /*-- Reset the spCb state before any checks, so that state is
        reset even in case of failures --*/
      spCb->state = CMXTA_INIT;

      /*-- Reset the timer state after processing timeout --*/
      tcCb->timeOutState = CMXTA_NONE;

      /*-- Not the first time, check if the message queued is
           indeed the timeout expiry message, if any other message
           is received, stop the timeout timer and flag an error --*/
      cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
      /* cm_xta_inthdl_c_001.main_9 :Added NULL check */
      if(!msg)
      {
         cmXtaStopTmr(CMXTA_TMR_TIMEOUT, tcCb);
         RETVALUE(CMXTA_ERR_NO_VALUE);
      }

      /*-- Moved cmXtaGetPst out of Multi Proc flag--*/
      /*-- Validate if this is the msg for this function --*/
      srcProcId = CMXTA_PROCID_MASTER;
      dstProcId = CMXTA_PROCID_MASTER;
      cmXtaGetPst(&pst, ENTTST, CMXTA_INST_ID, ENTTST, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);
      pst.event = CMXTA_TMR_TIMEOUT;

      ret = cmXtaValidatePst(&(msg->pst), &pst);
      if (ret != ROK)
      {
         /*-- No match, the timeout timer is still running, stop
              it --*/
         cmXtaStopTmr(CMXTA_TMR_TIMEOUT, tcCb);

         /*-- Remove the msg from the Queue --*/
         cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

         /* cm_xta_inthdl_c_001.main_9 :Added NULL check */
         if(!msg)
         {
            CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntTimeout(): msg is NULL\n"));
            RETVALUE(CMXTA_ERR_INT);
         }
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

         RETVALUE(CMXTA_ERR_NOMATCH);
      }

      /*-- Remove the timer msg from the Queue --*/
      cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

      /* cm_xta_inthdl_c_001.main_9 :Added NULL check */
      if(!msg)
      {
         CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntTimeout(): msg is NULL\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlIntTimeout */

/*--cm_xta_inthdl_c_001.main_4  loop changes starts--*/
/*
*
*       Fun: To handle the repetition of test case steps.
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File: cm_xta_inthdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlIntRepeatStart
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntRepeatStart(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32  repeatCount = 0;
   U16  retValue = 0;

   TRC2(cmXtaHdlIntRepeatstart)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntRepeatStart(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntRepeatStart(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*--Store the current step and step count needed to repeat the steps--*/
   spCb->reStartStep = spCb->curStep;
   spCb->repeatStepCnt = spCb->stepCnt;

   /*--Get number of times to repeat the steps--*/
   retValue = cmXtaXmlGetVal(NULLP, spCb->reStartStep, 
                                     CMXTA_ATTRIB_U32, "repeatCount",
                                                      &(repeatCount));
   /* cm_xta_inthdl_c_001.main_8: deleted intialization to maximum count */
   if((retValue != CMXTA_ERR_NO_VALUE ) && (repeatCount > 0))
         spCb->repeatCount = --repeatCount; 
   else
         spCb->repeatCount = 0;

   RETVALUE(CMXTA_ERR_NONE);

}/* cmXtaHdlIntRepeatStart */


/*
*
*       Fun: To handle the repetition of test case steps.
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File: cm_xta_inthdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlIntRepeatEnd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntRepeatEnd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   /* cm_xta_inthdl_c_001.main_11: Removed the unused variable */
   TRC2(cmXtaHdlIntRepeatEnd)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntRepeatEnd(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntRepeatEnd(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*--Check for repeat count. If repeat count is > 0 then restore
      the values which are stored in cmXtaHdlIntRepeatStart and 
      decrease the repeatCount--*/
   /* cm_xta_inthdl_c_001.main_7: Addition. Added changes for repeat count and expset */
   /* cm_xta_inthdl_c_001.main_8: deleted intialization to maximum count */
       if(spCb->repeatCount)
       {

          /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
          CMXTA_DBG_PARAM((_cmxtap, "Number of times to repeat (%d)\n", spCb->repeatCount));
#else
          CMXTA_DBG_PARAM((_cmxtap, "Number of times to repeat (%ld)\n", spCb->repeatCount));
#endif /* ALIGN_64BIT */
          /*--restore the values--*/
          spCb->curStep = spCb->reStartStep;
          spCb->state = CMXTA_INIT;
          spCb->stepCnt = spCb->repeatStepCnt;
          spCb->repeatCount--;
       }

   RETVALUE(CMXTA_ERR_NONE);

}/* cmXtaHdlIntRepeatEnd */

PUBLIC U8      numLc;
EXTERN Bool isPfsSim;

/*--cm_xta_inthdl_c_001.main_4  loop changes starts--*/
/*
*
*       Fun: To handle the repetition of test case steps.
*
*       Desc:  
*              
*       Ret:   
*              
*       Notes: 
*
*       File: cm_xta_inthdl.c 
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaHdlIntRepeatStartLchCfg
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntRepeatStartLchCfg(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U32  repeatCount = 0;
   U16  retValue = 0;
   Bool isPfsSim1 =FALSE;

   TRC2(cmXtaHdlIntRepeatstart)
   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntRepeatStart(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntRepeatStart(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

//   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isPfsSim" ,&isPfsSim1);
//   retValue = cmXtaXmlGetVal(NULLP, spCb->reStartStep, 
     //                                CMXTA_ATTRIB_BOOL, "isPfsSim",&isPfsSim1);

   repeatCount = numLc;

   /*--Store the current step and step count needed to repeat the steps--*/
   spCb->reStartStep = spCb->curStep;
   spCb->repeatStepCnt = spCb->stepCnt;

   /* cm_xta_inthdl_c_001.main_8: deleted intialization to maximum count */
   if((retValue != CMXTA_ERR_NO_VALUE ) && (repeatCount > 0))
         spCb->repeatCount = --repeatCount; 
   else
         spCb->repeatCount = 0;
   RETVALUE(CMXTA_ERR_NONE);

}/* cmXtaHdlIntRepeatStart */ 

/*--loop changes ends--*/



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
PUBLIC S16 cmXtaHdlIntDelay
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntDelay(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   U16      tmrVal;
   CmXtaMsgQElm   *msg;

   TRC2(cmXtaHdlIntDelay)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntDelay(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntDelay(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*-- Internal command to handle delay --*/

   /*-- Start a timer and wait for the timer expiry, if any other message
        is received before the timer expiry, flush it --*/

   /*-- Mark the state as first time or waiting for the timer expiry --*/
   if (tcCb->timeOutState == CMXTA_NONE)
   {
      /*-- Reset the dropMsg flag --*/
      tcCb->dropMsg = FALSE;
      /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
      cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "save",  &tcCb->dropMsg);

      tmrVal = CMXTA_TMR_DELAY_VAL;
      /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
      cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_U16, "delay",  &tmrVal);

      /*-- First time, start timer and suspend the test case --*/
      /*-- This happens if the test is waiting for an external
        event, start the delay timer and suspend, yawn --*/
      cmXtaStartTmr(CMXTA_TMR_DELAY, tcCb, tmrVal);

      /*-- Set state --*/
      tcCb->timeOutState = CMXTA_RUN;

      /*-- Ask TC Engine not to run guard timer for this handler --*/
      tcCb->noGuardTmr = TRUE;

      /*-- Return a positive value here, since you do
        not know which function has triggered the
        engine, better handle it using TC Callback
        as done above --*/
      RETVALUE(CMXTA_ERR_PENDING);
   }
   else
   {
      /*-- Not the first time, check if the delay timer expired or 
           whether a new message arrived in TC queue. If a new 
           message arrived, then ignore the message and return --*/

      /*-- First check for the delay timer expiry --*/
      if (tcCb->delayTmr == TRUE)
      {
         /*-- Reset the spCb state before any checks, so that state is
           reset even in case of failures --*/
         spCb->state = CMXTA_INIT;

         /*-- Reset the timer state after processing timeout --*/
         tcCb->timeOutState = CMXTA_NONE;

         /*-- Reset the drop Msg flag --*/
         tcCb->dropMsg = FALSE;

         /*-- Reset to run guard timer going forward --*/
         tcCb->delayTmr = FALSE;

         /*-- Reset to run guard timer going forward --*/
         tcCb->noGuardTmr = FALSE;
      }
      else
      {
         /*-- Some other message arrived in the queue, ignore --*/
         if (tcCb->dropMsg == TRUE)
         {
            /*-- Remove the msg from the Queue --*/
            cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

            /* cm_xta_inthdl_c_001.main_9 :Added NULL check */
            if(!msg)
            {
               CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntDelay(): msg is NULL\n"));
               RETVALUE(CMXTA_ERR_INT);
            }
            /*-- Flush --*/
            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         }

         /*-- Return a positive value here, since you do
           not know which function has triggered the
           engine, better handle it using TC Callback
           as done above --*/
         RETVALUE(CMXTA_ERR_PENDING);
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlIntDelay */

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
PUBLIC S16 cmXtaHdlIntSuspend
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntSuspend(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   TRC2(cmXtaHdlIntSuspend)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntSuspend(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntSuspend(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*-- Internal command to handle TA suspension --*/

   /*-- Set state --*/
   tcCb->suspendTC = TRUE;

   RETVALUE(CMXTA_ERR_PENDING);
}/* cmXtaHdlIntSuspend */


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
PUBLIC S16 cmXtaHdlIntGlobalDirective
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntGlobalDirective(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Bool memFlag;
   U32  memAvail;

   TRC2(cmXtaHdlIntGlobalDirective)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntGlobalDirective(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntGlobalDirective(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*-- Global Directives : Changes the setting across all the test cases. User
        shall have to reset the global settings if one wants to revert to the
        default settings. Use cmXtaHdlIntDirective if you want to change
        settings only for a TC --*/

   /*-- Instructions : These values shall be used only till the point an 
        associated test case is not found. After that the directives inside
        the tcCb shall be used for all decisions. Essentially that means all
        handlers shall use the tcCb based directive values all the time.

        The change in the value affects the present and all future test cases.

        This has a limited usage and the real essential ones shall be either
        set to default or exposed on command line interface. These are available
        here to change the system behaviour at TA and TG configuration level
        only --*/

   /*-- Internal command to set global and TC level settings --*/

   /*-- The global and TC settings may be set from outside as well, hence
        do not assign a default value here, instead just override the 
        values if specified by the test case --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
     using XML --*/

   /*-- ignoreMsg flag --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "ignore",  &cmXtaCb.directives.ignoreMsg);

   /*-- logAlarm flag --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "logAlarm",  &cmXtaCb.directives.logAlarm);

   /*-- logTrc flag --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "logTrace",  &cmXtaCb.directives.logTrc);

   /*-- Capture Alarm flag --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "alarm",  &cmXtaCb.directives.capAlarm);

   /*-- ignoreMsg flag --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "trace",  &cmXtaCb.directives.capTrc);

   /*-- mem show flag at different TC steps --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "memory",  &cmXtaCb.directives.memFlag);

   /*-- mem show flag --*/
   memFlag = FALSE;
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "memshow",  &memFlag);
   /*-- Check we have to show the SSI memory usage here --*/
   if (memFlag == TRUE)
   {
      CMXTA_DBG_CALLIND((_cmxtap, " Info      : Memory usage\n"), 3);
      SRegInfoShow(cmXtaCb.init.region, &memAvail);
   }

   /*-- Partial Confirmation on any Interface --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "partialCfm",  &cmXtaCb.directives.partialCfm);

   /*-- loadMode flag --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "load",  &cmXtaCb.loadDir.loadMode);

   /*-- Check for sync Load steps only in load mode --*/
   if (cmXtaCb.loadDir.loadMode == TRUE)
   {
      /*-- Retracting steps allowed by default, you may still control individual
           steps by setting the appropriate step attributes --*/
      cmXtaCb.loadDir.syncLoadSteps = TRUE;

      /*-- Sync steps again by stepping back flag --*/
      cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "sync",  &cmXtaCb.loadDir.syncLoadSteps);

      /*-- Shall we maintain statistics for the load scenarios --*/
      /*-- Default is TRUE --*/
      cmXtaCb.loadDir.loadSts = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "loadsts",  &cmXtaCb.loadDir.loadSts);

      /*-- Shall we maintain data structures (state) for the load scenarios --*/
      /*-- Default is TRUE --*/
      cmXtaCb.loadDir.loadState = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "loadstate",  &cmXtaCb.loadDir.loadState);

      /*-- Maximum load (maximum concurrent calls/transactions) --*/
      cmXtaCb.loadDir.maxLoad = 1000;
      cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_U32, "maxload",  &cmXtaCb.loadDir.maxLoad);

/* cm_xta_inthdl_c_001.main_5: Updated for SIP Release 2.3 */
#ifdef SW_ACC
      /*-- Initialize Clear On error --*/
      cmXtaCb.loadDir.clearOnErr = FALSE;
      cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "clearonerror",  &cmXtaCb.loadDir.clearOnErr);
#endif

      cmXtaAppLoadInit();
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlIntGlobalDirective */


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
PUBLIC S16 cmXtaHdlIntDirective
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntDirective(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Bool memFlag;
   U32  memAvail;

   TRC2(cmXtaHdlIntDirective)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntDirective(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntDirective(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*-- TC Directives : Changes the setting across for a particular instance of
        a test case. The values do not affect the global settings.

        Instructions : These values shall not be used only till the point an 
        associated test case is not found. After that the directives inside
        the tcCb shall be used for all decisions. Essentially that means all
        handlers shall use the tcCb based directive values all the time. --*/

   /*-- Internal command to set global and TC level settings --*/

   /*-- The global and TC settings may be set from outside as well, hence
        do not assign a default value here, instead just override the 
        values if specified by the test case --*/

   /*-- Internal command to set global and TC level settings --*/

   /*-- The global and TC settings may be set from outside as well, hence
        do not assign a default value here, instead just override the 
        values if specified by the test case --*/

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
     using XML --*/

   /*-- ignoreMsg flag --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "ignore",  &tcCb->directives.ignoreMsg);

   /*-- logAlarm flag --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "logAlarm",  &tcCb->directives.logAlarm);

   /*-- logTrc flag --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "logTrace",  &tcCb->directives.logTrc);

   /*-- Capture Alarm flag --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "alarm",  &tcCb->directives.capAlarm);

   /*-- ignoreMsg flag --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "trace",  &tcCb->directives.capTrc);

   /*-- mem show flag at different TC steps --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "memory",  &tcCb->directives.memFlag);

   /*-- mem show flag --*/
   memFlag = FALSE;
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "memshow",  &memFlag);
   /*-- Check we have to show the SSI memory usage here --*/
   if (memFlag == TRUE)
   {
      CMXTA_DBG_CALLIND((_cmxtap, " Info      : Memory usage\n"), 3);
      SRegInfoShow(cmXtaCb.init.region, &memAvail);
   }

   /*-- Partial Confirmation on any Interface --*/
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "partialCfm",  &tcCb->directives.partialCfm);

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlIntDirective */

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
PUBLIC S16 cmXtaHdlIntInvalid
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntInvalid(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   TRC2(cmXtaHdlIntInvalid)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntInvalid(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntInvalid(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*-- Internal command to handle invalid XML commands, ideally this
        should not never get hit, its here in case some one wants to
        register a command, but the COMMAND may change before it gets
        executed, for eg INVITE becomes sot.conreq. The user may 
        register NULLP or cmXtaHdlIntInvalid with INVITE, since this 
        should not get hit anyway --*/

   CMXTA_DBG_CALLIND((_cmxtap, "Failed : Invalid command\n"), 3);

   /*-- Invalid step was executed, most likely we will skip rest of the test
     steps and move to shutdown, we really do not know whether it was a 
     send or expect command, so do not try to remove any message. It is
     anyway a fatal error. So we can fail hard here. Let the world know --*/

   RETVALUE(CMXTA_ERR_FATAL);
}/* cmXtaHdlIntInvalid */

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
PUBLIC S16 cmXtaHdlIntDummy
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 cmXtaHdlIntDummy(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   TRC2(cmXtaHdlIntDummy)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntDummy(): tcCb (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntDummy(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

   /*-- Internal command to handle dummy XML commands, its here in case 
        some one wants to register a command only for the attributes, 

        The user may register cmXtaHdlIntDummy with INVITE, since this 
        should not get hit anyway --*/

   RETVALUE(CMXTA_ERR_NONE);
}/* cmXtaHdlIntDummy */

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
PUBLIC S16 cmXtaHdlIntSRegInfoShow
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC  S16 cmXtaHdlIntSRegInfoShow(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{ 
   
  /* cm_xta_inthdl_c_001.main_6: Added fix for windows compilation*/ 
  U32 ptr;
  
  TRC2(cmXtaHdlInSRegInfoShow)

   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
  CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntSRegInfoShow(): tcCb (%d)\n", tcCb->tcId));
#else
  CMXTA_DBG_PARAM((_cmxtap, "cmXtaHdlIntSRegInfoShow(): tcCb (%ld)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */

  SRegInfoShow(0, &ptr);

  RETVALUE(CMXTA_ERR_NONE);
} /* cmXtaHdlIntSRegInfoShow */


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
PUBLIC S16 cmXtaHdlIntSLogMemLk
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC  S16 cmXtaHdlIntSLogMemLk(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   TRC2(cmXtaHdlIntSLogMemLk)
   
#ifdef SS_MEM_LEAK_STS
   SLogLkInfo();
#else
   /* cm_xta_inthdl_c_001.main_11: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntSLogMemLk(): tcCb (%d)\n, SS_MEM_LEAK_STS flag not enabled\n", tcCb->tcId));
#else
   CMXTA_DBG_ERR((_cmxtap, "cmXtaHdlIntSLogMemLk(): tcCb (%ld)\n, SS_MEM_LEAK_STS flag not enabled\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
#endif

   RETVALUE(CMXTA_ERR_NONE);
} /*cmXtaHdlIntSLogMemLk*/

/********************************************************************30**

         End of file:     cm_xta_inthdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:59:17 2015

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
/main/3      ---      cm_xta_inthdl_c_001.main_2   sk   1. Multiple Queue support in TA
/main/4      ---     aj  1. Moved cmXtaGetPst out of Multi Proc flag
/main/5      ---      cm_xta_inthdl_c_001.main_4 mn 1. cm_xta_loop changes
/main/6      ---      cm_xta_inthdl_c_001.main_5 ve 1. Updated for SIP Release 2.3
/main/7      ---      cm_xta_inthdl_c_001.main_6 sy 1. Added fix for windows compilation.
/main/8      ---      cm_xta_inthdl_c_001.main_7 sm 1. Added fix for repeatcount and expset.
/main/9      ---      cm_xta_inthdl_c_001.main_8 sm 1. Deleted intialization to maximum count.
/main/10     ---     cm_xta_inthdl_c_001.main_9 kchaitanya 1. Updated for fixing klockwork 
                                                            errors
/main/11     ---      cm_xta_inthdl_c_001.main_10 pchebolu 1. Deleted cm_mem.x inclusion  
/main/12     ---      cm_xta_inthdl_c_001.main_11 pkaX 1. Fix for 64bit compilation warnings.
/main/13     ----     cm_xta_inthdl_c_001.main_12 nh   1. Updated for Psf-Diameter 1.1
                                                     release Removed cm_xta_app.[hx]
*********************************************************************91*/
