/********************************************************************20**

     Name:    Common 

     Type:    C source file

     Desc:    C code for Configuration and Control Handler of System Agent.

     File:    cm_xta_fmutl.c

     Sid:      cm_xta_fmutl.c@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:15 2015

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

#include "cm_xta_app.h"
#include "cm_ftha.h"
#include "lmr.h"
#include "lmr.h"
#include "lsh.h"
#include "lsg.h"
#include "cm_xta.h"

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#include "cm_xta_app.x"
#include "cm_ftha.x"
#include "lmr.x"
#include "lsh.x"
#include "lsg.x"
#include "cm_xta.x"


#include "cm_xta_fm.x"
/*-- Control block definition --*/
PUBLIC CmXtaFmCb cmXtaFmCb;

/* cm_xta_fmutl_c_001.main_1: Added the function prototype */
PRIVATE S16 cmXtaFmSwitchNode ARGS((Void));

/***********************************************************************
*
*       Fun: cmXtaFmStopTmr 
*
*       Desc: This function stops a timer
*              
*       Ret:  ROK/RFAILED 
*              
*       Notes:  
*
*       File: cm_xta_fmutl.c 
*
************************************************************************/
#ifdef ANSI
PRIVATE S16 cmXtaFmStopTmr 
(
S16          tmrEvnt      /* timer event */
)
#else
PRIVATE S16 cmXtaFmStopTmr (tmrEvnt)
S16          tmrEvnt;      /* timer event */
#endif
{
   CmTimer   *tmr = NULLP;         /* timers array */
   CmTmrArg  arg;          /* timer arguments */
   U8          indx;

   TRC2(cmXtaFmStopTmr)

   for (indx = 0; indx < CMXTA_FM_MAX_TIMERS; indx ++)
   {
      if (cmXtaFmCb.timers[indx].tmrEvnt == tmrEvnt)
         break;
   }

   /* cm_xta_fmutl_c_001.main_1: Added the check for max timers
    * In case if there are no active timer running, return */
   if(indx == CMXTA_FM_MAX_TIMERS)
   {
      RETVALUE(ROK);
   }
   else
   {
      arg.tqCp    = &cmXtaFmCb.tqCp;
      arg.tq      = cmXtaFmCb.tq;
      arg.timers  = cmXtaFmCb.timers;
      arg.cb      = (PTR)&cmXtaFmCb;
      arg.evnt   = NOTUSED;
      arg.wait    = NOTUSED;
      arg.tNum    = indx;
      arg.max     = CMXTA_FM_MAX_TIMERS;
      /*-- Remove the timer from the timing queue. --*/
      cmRmvCbTq(&arg);
      RETVALUE(ROK);
   }

} /*-- cmXtaFmStopTmr --*/
 
/***********************************************************************
*
*       Fun: cmXtaFmStartTmr 
*
*       Desc: This function starts a timer
*              
*       Ret:  ROK/RFAILED 
*              
*       Notes:  
*
*       File: cm_xta_fmutl.c 
*
************************************************************************/
#ifdef ANSI
PRIVATE S16 cmXtaFmStartTmr 
(
S16          tmrEvnt      /* timer event */
)
#else
PRIVATE S16 cmXtaFmStartTmr (tmrEvnt)
S16          tmrEvnt;      /* timer event */
#endif
{
   CmTimer   *tmr = NULLP;         /* timers array */
   CmTmrArg  arg;          /* timer arguments */

   TRC2(cmXtaFmStartTmr)

   switch(tmrEvnt)
   {
      case CMXTA_FM_TIMER_1:
         arg.tqCp    = &cmXtaFmCb.tqCp;
         arg.tq      = cmXtaFmCb.tq;
         arg.timers  = cmXtaFmCb.timers;
         arg.cb      = (PTR)&cmXtaFmCb;
         arg.evnt   = CMXTA_FM_TIMER_1;
         arg.wait    = CMXTA_FM_TIMER_1_EXP;
         arg.tNum    = 0;
         arg.max     = CMXTA_FM_MAX_TIMERS;
         break;
      case CMXTA_FM_TIMER_2:
         arg.tqCp    = &cmXtaFmCb.tqCp;
         arg.tq      = cmXtaFmCb.tq;
         arg.timers  = cmXtaFmCb.timers;
         arg.cb      = (PTR)&cmXtaFmCb;
         arg.evnt   = CMXTA_FM_TIMER_2;
         arg.wait    = CMXTA_FM_TIMER_2_EXP;
         arg.tNum    = 1;
         arg.max     = CMXTA_FM_MAX_TIMERS;
         break;
      default:
         break;
   }

   /*-- Put the timer into the timing queue. --*/
   cmPlcCbTq(&arg);

} /*-- cmXtaFmStartTmr --*/
 
/***********************************************************************
*
*       Fun: cmXtaFmInitTmr 
*
*       Desc: This function initializes timers used by the Fault detection
*              
*       Ret:  ROK/RFAILED 
*              
*       Notes:  
*
*       File: cm_xta_fmutl.c 
*
************************************************************************/
#ifdef ANSI
PRIVATE S16 cmXtaFmInitTmr (Void)
#else
PRIVATE S16 cmXtaFmInitTmr ()
#endif
{

   TRC2(cmXtaFmInitTmr)
   cmInitTimers(cmXtaFmCb.timers, CMXTA_FM_MAX_TIMERS);
} /*-- cmXtaFmInitTmr --*/
 
/*
*
*       Fun: cmXtaFmActvTsk 
*
*       Desc: This is the active task for the Fault manager being used 
*              by CM XTA in order to detect a fault. Fault manager might 
*              run in two modes. 
*             (i). Central Fault manager-
*                    In this mode this entity would send out periodic 
*                    heartbeat messges to all the nodes present in the 
*                    system. In the event of no response from any node
*                    the request is retried for a configurable number of 
*                    times. If the retries also fails, we mark the node 
*                    as down and comence fault recovery by calling SG
*                    control primitives. 
*             (ii). Fault detection clients-
*                    In this mode this entity would run on every node in
*                    the system. This entity would then respond to heart-
*                    beat requests. 
*              
*       Ret:  ROK/RFAILED 
*              
*       Notes: 
*
*       File: cm_xta_fmutl.c 
*
*/
#ifdef ANSI
PUBLIC S16 cmXtaFmActvTsk
(
Pst            *pst,           /* pst structure */
Buffer         *mBuf            /* message buffer */
)
#else
PUBLIC S16 cmXtaFmActvTsk (pst, mBuf)
Pst            *pst;           /* pst structure */
Buffer         *mBuf;           /* message buffer */
#endif
{
   ProcId   targetProcId;
   S16      ret;
   U8       i;   

   ret = ROK;
   TRC2(cmXtaActvTsk)

      switch (pst->event)
      {
         /*-- Three events possible-
           (a). Heartbeat request from the central fault
           detection manager. 
           (b). Heartbeat response from the the fault detection
           clients on different nodes. 
           (c). Init request this is issued to get the manager 
           started on the node in either of the two modes. 
           --*/
         case EVTSTHEARTBEATREQ:
            /*-- We received a Heartbeat request from the Server 
              we have to send back a response from here --*/

            /*-- First step reverse the pst structure --*/
            cmXtaReversePst(*pst);
            /*-- Second step change event type to response --*/
            pst->event = EVTSTHEARTBEATRSP;
            /*-- Last step post the message --*/
            SPstTsk(pst, mBuf);
            break;

         case EVTSTHEARTBEATRSP:
            /*-- We received a Heartbeat response from one of the 
              Clients, we must perform the following steps. 
              1. Validate if the response came from correct 
              node. 
              2. Stop TIMER-2
              3. Send Heartbeat request to next node. 
              4. Start TIMER-2.
              --*/
            targetProcId = cmXtaProc[cmXtaFmCb.curNode].lowProcId;  
            if (pst->srcProcId != targetProcId)
            {
               CMXTA_DBG_ERR((_cmxtap, "Received Heartbeat Response from incorrect node!\n"));
               CMXTA_DBG_PARAM((_cmxtap, "cmXtaFmActvTsk() : Received: (%d):Expected: (%d)\n",
                        pst->srcProcId, targetProcId));
               SPutMsg(mBuf);
               break;
            }
            /*-- We received the Heartbeat Response from the correct node --*/
            cmXtaFmStopTmr(CMXTA_FM_TIMER_2);
            cmXtaProc[cmXtaFmCb.curNode].isUp = TRUE;
            cmXtaFmCb.curNode++;
            if (cmXtaFmCb.curNode == CMXTA_NODES )
               cmXtaFmCb.curNode = 1;

            /*-- free up the mBuf --*/
            SPutMsg(mBuf);
            /*Start the FM Timer1 here*/
            cmXtaFmStartTmr(CMXTA_FM_TIMER_1);

            break;

            /*-- This is the request that is isssued by the binary 
              in order to initialize this module. It needs to 
              do the following tasks -
              (a). figure out which mode to run in. 
              (i). Central fault detection mode - 
              (i.1). Needs to run couple of timers 
              One that will be used to send out 
              heartbeats to various clients. 
              Two that will be used to check for
              expiry of a heartbeat. 
              (ii). Fault detection client mode -
              Do absolutely nothing. 
              --*/
#ifdef CMXTA_MASTER
         case EVTSTFMSERVERINIT:
            /*-- Init this as a Server --*/
            CMXTA_DBG_INFO((_cmxtap, "cmXtaFmActvTmr() : Initiating as fault manager!  \n"));
            cmXtaFmInitTmr(); 
            cmXtaFmCb.tqCp.nxtEnt = 0;
            cmXtaFmCb.tqCp.tmrLen = 2;
#ifdef SS_MULTIPLE_PROCS
            ret = SRegCfgTmr (cmXtaProc[0].lowProcId,
                  ENTFM ,
                  CMXTA_INST_ID,
                  (S16  )1   , /* 1, 2, 3 etc               */
                  (S16  )SS_10MS     , /* SS_1MS, SS_10MS, SS_100MS */
                  cmXtaFmActvTmr);
#else
            ret = SRegCfgTmr ( ENTFM, 
                  CMXTA_INST_ID,
                  (S16  )1   , /* 1, 2, 3 etc               */
                  (S16  )SS_10MS     , /* SS_1MS, SS_10MS, SS_100MS */
                  cmXtaFmActvTmr);
#endif /* SS_MULTIPLE_PROCS */
 
            /*Initialize isUp as FALSE */
            for (i =0 ;i < CMXTA_NODES; i++)
               cmXtaProc[i].isUp = FALSE;

            /*-- Start Timer 1 --*/
            cmXtaFmStartTmr(CMXTA_FM_TIMER_1);
            cmXtaFmCb.curNode = 1;
            SPutMsg(mBuf);
            break;
#endif
         case EVTSTFMCLIENTINIT:
            /*-- Init this as a Client --*/
            /*-- Dont need to do anything here --*/
            CMXTA_DBG_INFO((_cmxtap, "cmXtaFmActvTmr() : Initiating as fault client  \n"));
           
            SPutMsg(mBuf);
            break;
         default:
            /*-- shouldn't get here --*/
            CMXTA_DBG_ERR((_cmxtap, "cmXtaFmActvTmr() : Invalid event received \n"));
            break;

      } /*-- End of switch --*/
      RETVALUE(ret);
} /*-- cmXtaFmActvTsk --*/
 

/**********************************************************
*
*      Fun:    cmXtaFmActvTmr
*
*      Desc:   Invoked by system services to process timers.
*
*              This function is registered during general configuration
*              using SRegCfgTmr  and is invoked at the specified period
*              by system services.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  so_tmr.c
*
**********************************************************/
#ifdef CMXTA_MASTER
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 cmXtaFmActvTmr
(
ProcId proc, 
Ent ent, 
Inst inst
)
#else
PUBLIC S16 cmXtaFmActvTmr (proc, ent, inst)
ProcId proc;
Ent ent;
Inst inst;
#endif
#else
#ifdef ANSI
PUBLIC S16 cmXtaFmActvTmr
(
void
)
#else
PUBLIC S16 cmXtaFmActvTmr ()
#endif
#endif /* SS_MULTIPLE_PROCS */
{

   TRC2(cmXtaFmActvTmr);

   cmPrcTmr (&cmXtaFmCb.tqCp, cmXtaFmCb.tq, (PFV) cmXtaFmProcTmr);

   RETVALUE (ROK);

} /* end of cmXtaFmActvTmr */



/***********************************************************
*
*      Fun:    cmXtaFmProcTmr
*
*      Desc:   Handle the expiration of a particular timer event
*
*       Ret:   RETVOID
*
*       Notes: This function dispatches the timer event expiry
*              to the appropriate module.
*
*       File:  cm_xta_fmutl.c
*
***********************************************************/
/* cm_xta_fmutl_c_001.main_1: Changed the scope of the function as
 * it is declared as PUBLIC in declaration */
#ifdef ANSI
PUBLIC Void cmXtaFmProcTmr
(
Ptr              cb,          /* control block using this timer */
S16              tmrEvnt      /* timer event */
)
#else
PUBLIC Void cmXtaFmProcTmr(cb, tmrEvnt)
Ptr              cb;          /* control block using this timer */
S16              tmrEvnt;     /* timer event */
#endif
{
   Buffer *mBuf;
   Pst    pst;

   switch(tmrEvnt)
   {
      case CMXTA_FM_TIMER_1:
         /*-- If we are here it means that Timer 1 expired i.e. 
           we must send heartbeat to all nodes present --*/
         /*-- Fault manager server shall run on Master which shall always 
           be the first in the cmXtaProcs array --*/
         cmXtaGetPst(&pst, ENTFM, CMXTA_INST_ID, ENTFM, CMXTA_INST_ID, 
               cmXtaProc[0].lowProcId, cmXtaProc[cmXtaFmCb.curNode].lowProcId, TRUE);
         pst.srcProcId = cmXtaProc[0].lowProcId;
         pst.dstProcId = cmXtaProc[cmXtaFmCb.curNode].lowProcId;

         /*-- Allocate MBUF --*/
         CMXTA_ALLOCMBUF(&mBuf);

         pst.event = EVTSTHEARTBEATREQ;
         /* Stop Timer1 here */
         cmXtaFmStopTmr(CMXTA_FM_TIMER_1);
         /*-- Start timer 2 --*/
         cmXtaFmStartTmr(CMXTA_FM_TIMER_2);
         /*ReInitialize the retryCount as the 0*/
         cmXtaFmCb.retryCount = 0;
         /*-- Post the message to client --*/
         SPstTsk(&pst, mBuf);

         break;

      case CMXTA_FM_TIMER_2:
         /*-- If we are here it means a node timed out we must retry once --*/
         if (cmXtaFmCb.retryCount == CMXTA_FM_MAX_RETRY)
         {
            /*-- Mark this node as down --*/
            cmXtaFmCb.retryCount = 0;
            /* Stop Timer2 here */
            cmXtaFmStopTmr(CMXTA_FM_TIMER_2);
            /*Send the Disable node command to this Node*/
            if(cmXtaProc[cmXtaFmCb.curNode].isUp == TRUE)
               cmXtaFmSwitchNode(); 
            cmXtaProc[cmXtaFmCb.curNode].isUp = FALSE;
            /*Move the current Node to the Next Node*/
            cmXtaFmCb.curNode++;
            if (cmXtaFmCb.curNode == CMXTA_NODES )
               cmXtaFmCb.curNode = 1;
            /*-- Start recovery using SG --=------------------------*/
            /*-- Start timer 1 --*/
            cmXtaFmStartTmr(CMXTA_FM_TIMER_1);
            break;
         }
         /*-- Increment retry count by one --*/
         cmXtaFmCb.retryCount++;
         /*-- Fill in the pst structure --*/
         /*-- Fault manager server shall run on Master which shall always 
           be the first in the cmXtaProcs array --*/
         cmXtaGetPst(&pst, ENTFM, CMXTA_INST_ID, ENTFM, CMXTA_INST_ID, 
               cmXtaProc[0].lowProcId, cmXtaProc[cmXtaFmCb.curNode].lowProcId, TRUE);
         pst.srcProcId = cmXtaProc[0].lowProcId;
         pst.dstProcId = cmXtaProc[cmXtaFmCb.curNode].lowProcId;
         /*-- Allocate MBUF --*/
         CMXTA_ALLOCMBUF(&mBuf);
         pst.event = EVTSTHEARTBEATREQ;
         /*-- Start timer 2 --*/
         cmXtaFmStopTmr(CMXTA_FM_TIMER_2);
         cmXtaFmStartTmr(CMXTA_FM_TIMER_2);
         /*-- Post the message to client --*/
         SPstTsk(&pst, mBuf);

         break;
      default:
         break;

   } 
}
#endif



/*****************************************************************************
*
*     Fun:   cmXtaFmActvInit
*
*     Desc:  Invoked by system services to initialize the FM Layer
*            protocol layer.
*
*            The first and second parameters (entity, instance)
*            specify the entity and instance id.
*
*            The third parameter (region) specifies the memory region
*            to be used to allocate structures and buffers.
*
*            The fourth parameter (reason) specifies the reason for
*            calling this initialization function.
*
*            Allowable values for parameters are specified in ssi.h.
*
*     Ret:   ROK   - ok
*
*     Notes: None
*
*     File:  cm_xta_fmutl.c
*
*****************************************************************************/
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 cmXtaFmActvInit
(
ProcId proc,                /* proc id */
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason,              /* reason */
void   **xxCb
)
#else
PUBLIC S16 cmXtaFmActvInit(proc, ent, inst, region, reason, xxCb)
ProcId    proc;                 /* proc id */
Ent    ent;                 /* entity */
Inst   inst;                /* instance */
Region region;              /* region */
Reason reason;              /* reason */
void   **xxCb;
#endif
#else /* SS_MULTIPLE_PROCS */
#ifdef ANSI
PUBLIC S16 cmXtaFmActvInit
(
Ent    ent,                 /* entity */
Inst   inst,                /* instance */
Region region,              /* region */
Reason reason               /* reason */
)
#else
PUBLIC S16 cmXtaFmActvInit(ent, inst, region, reason)
Ent    ent;                 /* entity */
Inst   inst;                /* instance */
Region region;              /* region */
Reason reason;              /* reason */
#endif
#endif /* SS_MULTIPLE_PROCS */
{
   TRC2(cmXtaFmActvInit);

   cmMemset ((U8 *)&cmXtaFmCb, 0, sizeof(CmXtaFmCb));
#ifdef SS_MULTIPLE_PROCS
   *xxCb = NULLP;
#endif
   RETVALUE(ROK);
} /* cmXtaFmActvInit */
#ifdef CMXTA_MASTER

/*
*
*       Fun:   cmXtaFmSwitchNode
*
*       Desc:  Call handler for swap node control request for System Manager
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  cm_xta_lsghdl.c
*
*/
#ifdef ANSI
PRIVATE S16 cmXtaFmSwitchNode
(
)
#else
PRIVATE S16 cmXtaFmSwitchNode()
#endif
{
   ProcId       srcProcId;
   ProcId       dstProcId;
   /* local variables */
   SgHiDisableNode *disableReq; 
   SgMngmt  cntrl;
   Pst      pst;
   /* so003.202 : Updated for SIP FTHA */
   Ent          entList[LSG_MAX_ENTS];
   Inst         instList[LSG_MAX_ENTS];
   U8           nmb;
   S16          i;

   TRC2(cmXtaFmSwitchNode)

   CMXTA_ZERO(&cntrl, sizeof(SgMngmt));

   CMXTA_ZERO(&pst, sizeof(Pst));
   
   cntrl.apiType                    = LSG_HI_API;

   disableReq   = &(cntrl.t.hi.cntrl.u.disableNode);
   
   cmMemset ((U8 *) disableReq  , 0, sizeof (SgHiDisableNode));   
   srcProcId = CMXTA_PROCID_MASTER;

   dstProcId = CMXTA_PROCID_MASTER; 

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTSG, CMXTA_INST_ID, srcProcId, dstProcId, TRUE);

   dstProcId = cmXtaProc[cmXtaFmCb.curNode].lowProcId;
   /*-- ACtion is enable --*/

   cntrl.t.hi.cntrl.action = LSG_ADISABLE;
   
   cntrl.t.hi.cntrl.subAction = NOTUSED;
   
   disableReq->forcedDisable = TRUE;

   disableReq->procId = cmXtaProc[cmXtaFmCb.curNode].lowProcId;

   disableReq->nmbEnts = 1;

   /* cm_xta_fmutl_c_001.main_1: Send the control request to entity
    * depending on the compile time flag */
#ifdef SO
   disableReq->entList[0].ent = ENTSO;
#endif /* SO */
#ifdef SZ
   disableReq->entList[0].ent = ENTSZ;
#endif /* SZ */
#ifdef AQ
   disableReq->entList[0].ent = ENTAQ;
#endif /* AQ */

   disableReq->entList[0].inst = 0;
  
   (Void) cmXtaInitHdr(&(cntrl.hdr), 1, ENTSG, CMXTA_INST_ID, STGEN, pst.selector);
    /* Send the request to the TUCL */
   (Void) SmMiLsgCntrlReq(&pst, &cntrl);

   RETVALUE(CMXTA_ERR_NONE);

}/* cmXtaHdlSgSwapNode */
#endif
/********************************************************************30**

         end of file:     cm_xta_fmutl.c@@/main/1 - wed jun 27 16:21:27 2007

*********************************************************************31*/


/********************************************************************40**

        notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ----     aj  1. main release
/main/2      ---      cm_xta_fmutl_c_001.main_1 pka  1. Fix for integration testing
*********************************************************************91*/

