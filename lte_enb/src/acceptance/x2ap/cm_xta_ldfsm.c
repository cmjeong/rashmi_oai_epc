
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_ldfsm.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:18 2015

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
/* cm_xta_ldfsm_c_001.main_5 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta.x"

/* cm_xta_ldfsm_c_001.main_5 Removed cm_xta_app.x for Psf-Diameter 1.1 */
#define CMXTA_UPD_LOAD_STEP_STS(_mode, _cntr1, _cntr2) {\
   if (_mode == TRUE) {\
      _cntr2++;\
   }\
   else {\
      _cntr1++;\
   }\
}

#define CMXTA_UPD_LOAD_STS(_sts) {\
   if (cmXtaCb.loadDir.loadSts == TRUE) {\
      _sts++;\
   }\
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
PUBLIC S16 cmXtaLoadEngine
(
Void        *msg
)
#else
PUBLIC S16 cmXtaLoadEngine(msg)
Void        *msg;
#endif
{
   Bool  newCall;
   Bool  retransMode;
   S16  ret;

   CmXtaLoadCb  *loadCb;

   U16   nxtLoadIndx;

   CmXtaLoadStep *loadStep;
   /* cm_xta_ldfsm_c_001.main_3: Added Initialization */
   U16   curLoadIndx=0;
   U16   retransLoadIndx=0;

   TRC2(cmXtaLoadEngine)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaLoadEngine(): Enter Load FSM\n"));

   newCall = FALSE;
   retransMode = FALSE;

   loadCb = NULLP;

   ret  = CMXTA_ERR_NONE;
   /*-- Common Frame Load Engine --*/

   /*-- Increment the received message count --*/
   CMXTA_UPD_LOAD_STS(cmXtaCb.loadSts.rcvdMsg);

   /*-- Get the application specific load control block, if present --*/
   if ((ret = cmXtaAppLoadFindnCreate(msg, &newCall, &loadCb)) != CMXTA_ERR_NONE)
   {
      if (ret != CMXTA_ERR_DUP)
      {

         CMXTA_DBG_ERR((_cmxtap, "cmXtaLoadEngine(): call not found, dropping msg\n"));

         /*-- No call context found for the incoming message, drop the message,
           clear call context and update statistics --*/
         CMXTA_UPD_LOAD_STS(cmXtaCb.loadSts.dropMsg);

         cmXtaAppLoadFreeMsg(msg);

         /*-- No further cleanup required, no TA and product specific context
           was made in the first place --*/

         RETVALUE(ret);
      }
      else
      {
         /*-- Check if the previous call is still pending. This may
           happen in two cases. 1) the previous call was never
           completed because of some error in the stack or the
           load generator or 2) We looped back too early in the
           call list and the global list size is too small for the
           present load. Increase the queue size.
           --*/

         /*-- CAPTURE err sts --*/

         /*-- We updated the old call with the new call info, so
              continue with the load --*/
      }
   }

   /*-- A new call, update sts --*/
   if (newCall == TRUE)
   {
      CMXTA_UPD_LOAD_STS(cmXtaCb.loadSts.totalCalls);
   }

   /*-- Get the present step in the load scenario --*/
   if ((ret = cmXtaAppLoadGetCurStep(msg,
                              loadCb,
                              &curLoadIndx,
                              &retransLoadIndx)) != CMXTA_ERR_NONE)
   {
      /*-- This function generally should not fail, but if it fails,
           that means that we are just not able to match this message
           to any of the steps (in case of retract feature enalbled) or
           the present step is not expecting this message.

           Ideally if the states are maintained, then the application
           function shall return the current step so that message is
           marked as unexpected message against that step --*/

      /*-- Since this has failed anyway, so lets do the cleanup --*/
      CMXTA_UPD_LOAD_STS(cmXtaCb.loadSts.dropMsg);

      CMXTA_DBG_ERR((_cmxtap, "cmXtaLoadEngine(): current step not found, dropping msg\n"));

      cmXtaAppLoadFreeMsg(msg);

      /*-- Check if clear the call on erro --*/
      if (cmXtaCb.loadDir.clearOnErr == TRUE)
      {
         CMXTA_UPD_LOAD_STS(cmXtaCb.loadSts.failCalls);

         cmXtaAppLoadDelete(loadCb, TRUE);
      }

      RETVALUE(ret);
   }

   if (retransLoadIndx < curLoadIndx)
      retransMode = TRUE;

   /*-- Store the next set of steps --*/
   nxtLoadIndx = retransLoadIndx + 1;
   loadStep = &cmXtaCb.loadSteps[retransLoadIndx];

   /*-- Infinite load loop --*/
   while (TRUE)
   {
      /*-- If we are here for the first time, then we have the current step index --*/

      /*-- Issue with TC and LC traffic from the stack. Here we are in endless loop
           of send and expect. It may be so that we send a message out to the stack
           and the response for the same may come back to TA in TC fashion. Two
           possibilities arise :

           1. There is no state information maintained in TA for the load steps.

              a. Successful Response :

              When the response (expect step) is received, TA will again restart this same
              Load FSM from with the existing FSM, will process the received message,
              may even send the next messsage, if any and then again unwind back to this
              FSM.

              b. Failure Response :

              TA will mark the call as failued and update statistics.

           2. State information is maintained in TA for the load steps.

              The processing is same except that internal load FSM may even update the
              next load step index.

          The problem is only when we have the next step as tapa.exp*. All tapa.send steps
          are executed in a loop from the same instance of the FSM. This FSM will have to
          take a break before it processes a tapa.expect step.

          Also, when we come back to this instance of FSM, the next step may have been
          changed altogether.

          In both the cases, this FSM shall update the global states/indexes before it
          calls the application engine. Also since the gloabl index may change before
          the control is given back to this instance of FSM, store the next load index
          before executing this step and if the next step is a tapa.exp*, suspend this
          instance of FSM --*/

      /*-- Get the Step to be executed --*/

      /*-- Current Load Index and Retranmission Load Index --*/
      /*-- In case where it is possible for some of the load steps to be retransmitted
           in the network, we may end up with current load index ahead of the message
           received. The load engine shall therefore loop on retransLoadIndx instead of
           current load index and all the messages handled during this period shall be
           counted against the retransmission statistics.

           When the retransLoadIndx and curLoadIndx becomes equal, the load steps are
           back in sync with the network load --*/

           /*-- When to cleanup the clal, for retransmission shud we keep
                the call hanging --*/

      /*-- Update global load index for this --*/
      if (loadCb != NULLP)
      {
         /*-- Check if we are handling retranmissions here, then just skip the
              index increment, instead capture the statistics against the
              retransmissions for the retransLoadIndx step --*/
         if (retransMode == FALSE)
            loadCb->curStep++;
      }

      /*-- Call application specific load engine handler with all
           the information --*/

      /*-- Some of the steps may have retransmission set to FALSE, just skip
           those steps during the retransmission mode --*/
      if ((retransMode == FALSE) ||
          (loadStep->retrans == TRUE))
      {
         /*-- First check for command type --*/
         switch (loadStep->cmdType)
         {
            case CMXTA_TYPE_INT :

               /*-- Check sub command type --*/
               switch (loadStep->subType)
               {
                  case CMXTA_SUBTYPE_SEND:
                     if ((ret = cmXtaAppLoadEngine(loadCb, msg, retransMode,
                                                curLoadIndx, retransLoadIndx)) != CMXTA_ERR_NONE)
                     {
                        CMXTA_DBG_ERR((_cmxtap, "cmXtaLoadEngine(): step processing failed\n"));

                        /*-- Send failed, mark the call as failure, capture statistics and clear
                          the resources --*/

                        /*-- Update step statistics --*/
                        CMXTA_UPD_LOAD_STS(loadStep->sts.failCnt);

                        /*-- Check if clear the call on error --*/
                        if (cmXtaCb.loadDir.clearOnErr == TRUE)
                        {
                           CMXTA_UPD_LOAD_STS(cmXtaCb.loadSts.failCalls);

                           cmXtaAppLoadDelete(loadCb, TRUE);
                        }

                        cmXtaAppLoadFreeMsg(msg);

                        RETVALUE(ret);
                     }

                     CMXTA_UPD_LOAD_STEP_STS(retransMode, loadStep->sts.passCnt, loadStep->sts.retransCnt);

                     /*-- Message sent, update sts --*/
                     if (cmXtaCb.loadSts.sentMsg == 0)
                     {
                        SGetRefTime (0,
                              &cmXtaCb.loadSts.ldStartTimeSec,
                              &cmXtaCb.loadSts.ldStartTimeUSec);
                     }


                     CMXTA_UPD_LOAD_STS(cmXtaCb.loadSts.sentMsg);
 /* cm_xta_ldfsm_c_001.main_2: IU_UP changes during performance testing */
#ifdef LX_ACC
                     if (cmXtaCb.loadSts.sentMsg > cmXtaCb.loadDir.maxLoad)
                     {
                        CMXTA_DBG_INFO((_cmxtap, "cmXtaLoadEngine(): Max load reached exiting.....\n"));
                        cmXtaAppPrintInfo();
                        SExit();
                     }
#endif

                     break;

                  case CMXTA_SUBTYPE_EXPOPT     :

                     if ((ret = cmXtaAppLoadEngine(loadCb, msg, retransMode,
                                                curLoadIndx, retransLoadIndx)) != CMXTA_ERR_NONE)
                     {
                        /*-- Mark as error for all but no match. An optional step may be skipped --*/
                        if (ret != CMXTA_ERR_NOMATCH)
                        {
                           CMXTA_DBG_ERR((_cmxtap, "cmXtaLoadEngine(): optional step not found, continue\n"));
                           /*-- Expect sequence failed, mark the call as failure, capture statistics
                             and clear the resources --*/

                           /*-- Update step statistics --*/
                           CMXTA_UPD_LOAD_STS(loadStep->sts.failCnt);

                           /*-- Check if clear the call on error --*/
                           if (cmXtaCb.loadDir.clearOnErr == TRUE)
                           {
                              CMXTA_UPD_LOAD_STS(cmXtaCb.loadSts.failCalls);

                              cmXtaAppLoadDelete(loadCb, TRUE);
                           }

                           cmXtaAppLoadFreeMsg(msg);

                           RETVALUE(ret);
                        }

                        CMXTA_DBG_ERR((_cmxtap, "cmXtaLoadEngine(): step processing failed\n"));
                     }

                     CMXTA_UPD_LOAD_STEP_STS(retransMode, loadStep->sts.passCnt, loadStep->sts.retransCnt);

                     break;

                  case CMXTA_SUBTYPE_EXPECT     :

                     if ((ret = cmXtaAppLoadEngine(loadCb, msg, retransMode,
                                                curLoadIndx, retransLoadIndx)) != CMXTA_ERR_NONE)
                     {
                        CMXTA_DBG_ERR((_cmxtap, "cmXtaLoadEngine(): step processing failed\n"));

                        /*-- Expect sequence failed, mark the call as failure, capture statistics
                          and clear the resources --*/

                        /*-- Update step statistics --*/
                        CMXTA_UPD_LOAD_STS(loadStep->sts.failCnt);

                        /*-- Check if clear the call on error --*/
                        if (cmXtaCb.loadDir.clearOnErr == TRUE)
                        {
                           CMXTA_UPD_LOAD_STS(cmXtaCb.loadSts.failCalls);

                           cmXtaAppLoadDelete(loadCb, TRUE);
                        }

                        cmXtaAppLoadFreeMsg(msg);

                        RETVALUE(ret);
                     }

                     CMXTA_UPD_LOAD_STEP_STS(retransMode, loadStep->sts.passCnt, loadStep->sts.retransCnt);

                     break;

                  case CMXTA_SUBTYPE_EXPSEQ     :
                  case CMXTA_SUBTYPE_DELAY     :
                  case CMXTA_SUBTYPE_TIMEOUT :
                  case CMXTA_SUBTYPE_EXPSET     :
                  default :
                     /*-- No esoteric commands supported in load mode --*/
                     CMXTA_DBG_ERR((_cmxtap, "cmXtaLoadEngine(): unsupported subType in load (%d)\n",
                              loadStep->subType));

                     /*-- Unexpected subType, mark the call as failure, capture statistics
                       and clear the resources --*/

                     /*-- Update step statistics --*/
                     CMXTA_UPD_LOAD_STS(loadStep->sts.failCnt);

                     /*-- Check if clear the call on error --*/
                     if (cmXtaCb.loadDir.clearOnErr == TRUE)
                     {
                        CMXTA_UPD_LOAD_STS(cmXtaCb.loadSts.failCalls);

                        cmXtaAppLoadDelete(loadCb, TRUE);
                     }

                     cmXtaAppLoadFreeMsg(msg);

                     RETVALUE(CMXTA_ERR_INT);
                     break;
               }

               break;

            case CMXTA_TYPE_DIR :
            default :
               CMXTA_DBG_ERR((_cmxtap, "cmXtaLoadEngine(): unknown cmdType (%d)\n",
                           loadStep->cmdType));

               /*-- Unexpected subType, mark the call as failure, capture statistics
                 and clear the resources --*/

               /*-- Update step statistics --*/
               CMXTA_UPD_LOAD_STS(loadStep->sts.failCnt);

               /*-- Check if clear the call on error --*/
               if (cmXtaCb.loadDir.clearOnErr == TRUE)
               {
                  CMXTA_UPD_LOAD_STS(cmXtaCb.loadSts.failCalls);

                  cmXtaAppLoadDelete(loadCb, TRUE);
               }

               cmXtaAppLoadFreeMsg(msg);

               RETVALUE(CMXTA_ERR_INT);
               break;
         }

         /*-- In TC mode, by the time we reach here, the call may have alredy failed,
           the call Cb will still be around, because the assumption is that they
           are allocated in chunck at the beginning. So check the call state --*/
         if (loadCb != NULLP)
         {
            if (loadCb->fail == TRUE)
            {
               /*-- The call failed in a TC fashion. The statistics would have
                    been already captured in the fail STM and the appropriate
                    states marked. Just return --*/

               /*-- Free the message --*/
               cmXtaAppLoadFreeMsg(msg);

               RETVALUE(CMXTA_ERR_NONE);
            }
         }
      }

      /*-- Check if the end of the test steps for this call --*/
      if (nxtLoadIndx == cmXtaCb.nxtLoadIndx)
      {
         /*-- End of a successful call, update statistics and
              clear resources --*/

         CMXTA_DBG_INFO((_cmxtap, "cmXtaLoadEngine(): call completed\n"));

         CMXTA_UPD_LOAD_STS(cmXtaCb.loadSts.passCalls);

         cmXtaAppLoadDelete(loadCb, FALSE);

/* cm_xta_ldfsm_c_001.main_1: Load changes for SDK */
#ifdef SW_ACC
       /* -- Make sure to clear the existing session on SDK */
        cmXtaAppLoadFreeSwSessions(msg, retransLoadIndx);
#endif

         cmXtaAppLoadFreeMsg(msg);

         RETVALUE(CMXTA_ERR_NONE);
      }

      /*-- Update local load indexes --*/
      if (retransMode == TRUE)
      {
         /*-- Increment retransmission counter --*/
         retransLoadIndx++;

         /*-- Check if we are in sync again --*/
         if (curLoadIndx == retransLoadIndx)
            retransMode = FALSE;
      }
      else
      {
         /*-- Already in sync, lets increment both --*/
         retransLoadIndx++;
         curLoadIndx++;
      }

      nxtLoadIndx = retransLoadIndx + 1;
      loadStep = &cmXtaCb.loadSteps[retransLoadIndx];

      /*-- Check if loop again in this instance of FSM. We loop again only if
           the next step is a tapa.send again --*/
      /*-- Return for all expect sequences --*/
      if (loadStep->subType != CMXTA_SUBTYPE_SEND)
      {
         CMXTA_DBG_INFO((_cmxtap, "cmXtaLoadEngine(): expecting msg, suspend Load FSM\n"));
         break;
      }

      /*-- If we reach here, we have another message to send --*/
   }

   /*-- Free the message, if not done yet, please note that App may
        have freed the message earlier. It is upto cmXtaAppLoadFreeMsg
        to ensure that double deallocation does not happen by marking
        appropriate pointers to NULLP --*/
   cmXtaAppLoadFreeMsg(msg);

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
PUBLIC Void cmXtaLoadDisplay
(
Void
)
#else
PUBLIC Void cmXtaLoadDisplay()
#endif
{
   Txt   pBuf[100];  /* output string buffer */
   U16   cnt;

   CmXtaLoadStepSts *sts;

   TRC2(cmXtaLoadDisplay);

   sprintf(pBuf, "\t\t\t\tLOAD STS: \n");
   SPrint(pBuf);

   sprintf(pBuf, "\n\n\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t\t\t\t========= \n");
   SPrint(pBuf);

   /* cm_xta_ldfsm_c_001.main_4: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   sprintf(pBuf, "Messages:\t\tReceived (%d)\t\tSent(%d)\t\tDropped(%d)\n",
           cmXtaCb.loadSts.rcvdMsg, cmXtaCb.loadSts.sentMsg, cmXtaCb.loadSts.dropMsg);
#else
   sprintf(pBuf, "Messages:\t\tReceived (%ld)\t\tSent(%ld)\t\tDropped(%ld)\n",
           cmXtaCb.loadSts.rcvdMsg, cmXtaCb.loadSts.sentMsg, cmXtaCb.loadSts.dropMsg);
#endif /* ALIGN_64BIT */
   SPrint(pBuf);

   /* cm_xta_ldfsm_c_001.main_4: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
   sprintf(pBuf, "Call:\t\tTotal Calls (%d)\t\tPass(%d)\t\tFail(%d)\n",
           cmXtaCb.loadSts.totalCalls, cmXtaCb.loadSts.passCalls, cmXtaCb.loadSts.failCalls);
#else
   sprintf(pBuf, "Call:\t\tTotal Calls (%ld)\t\tPass(%ld)\t\tFail(%ld)\n",
           cmXtaCb.loadSts.totalCalls, cmXtaCb.loadSts.passCalls, cmXtaCb.loadSts.failCalls);
#endif /* ALIGN_64BIT */
   SPrint(pBuf);

   sprintf(pBuf, "\n\n\n\n");
   SPrint(pBuf);

   sprintf(pBuf, "\t\t\tMessages\t\tRetrans\t\tUnexpected\n");
   SPrint(pBuf);
   for (cnt = 0; cnt < cmXtaCb.nxtLoadIndx; cnt++)
   {
      sts = &cmXtaCb.loadSteps[cnt].sts;
   /* cm_xta_ldfsm_c_001.main_4: Fix for 64bit compilation warnings */
#ifdef ALIGN_64BIT
      sprintf(pBuf, "Step [%d]\t:\t\t[%4d]\t\t[%4d]\t\t[%4d]\n",
              cnt+1, sts->passCnt, sts->retransCnt, sts->failCnt);
#else
      sprintf(pBuf, "Step [%d]\t:\t\t[%4ld]\t\t[%4ld]\t\t[%4ld]\n",
              cnt+1, sts->passCnt, sts->retransCnt, sts->failCnt);
#endif /* ALIGN_64BIT */
      SPrint(pBuf);
   }

   RETVOID;
} /* cmXtaLoadDisplay */

/********************************************************************30**

         End of file:     cm_xta_ldfsm.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:18 2015

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
/main/1      ----     up  1. Main release
/main/2      ----   cm_xta_ldfsm_c_001.main_1  ve  1. Load changes for SDK
/main/3      ----   cm_xta_ldfsm_c_001.main_2  rss 1. IU_UP changes during performance
                                                      testing.
/main/4      ----   cm_xta_ldfsm_c_001.main_3  kchaitanya  1. Updated for fixing klockwork 
                                                            errors
/main/5      ----   cm_xta_ldfsm_c_001.main_4  pkaX  1. Fix for 64bit compilation warnings.
/main/6      ----   cm_xta_ldfsm_c_001.main_5  jj 1. Updated for Psf-Diameter 1.1
                          release Removed cm_xta_app.[hx] 
*********************************************************************91*/
