
/********************************************************************20**

     Name:    Common XML TA 

     Type:    C source file

     Desc:    C code 

     File:    

     Sid:      cm_xta_tmr.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Fri Jul 19 19:25:10 2013

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

#ifdef CMXTA_FTHA_INTEGRATED
#include "cm_ftha.h"
#include "lmr.h"
#include "lsh.h"
#include "lsg.h"
#endif
#include "cm_xta.h"
/* cm_xta_tmr_c_001.main_7 Removed cm_xta_app.h for Psf-Diameter 1.1 */
/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_llist.x"      /* common link list */

#ifdef CMXTA_FTHA_INTEGRATED
#include "cm_ftha.x"
#include "lmr.x"
#include "lsh.x"
#include "lsg.x"
#endif
#include "cm_xta.x"

/* cm_xta_tmr_c_001.main_7 Removed cm_xta_app.x for Psf-Diameter 1.1 */
/*cm_xta_tmr_c_001.main_2 :Support for multiple proc */
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
#ifdef SS_MULTIPLE_PROCS
#ifdef ANSI
PUBLIC S16 cmXtaActvTmr
(
ProcId proc,
Ent    ent,
Inst   inst
)
#else
PUBLIC S16 cmXtaActvTmr(proc, ent, inst)
ProcId proc;
Ent    ent;
Inst   inst;
#endif
#else /*-- SS_MULTIPLE_PROCS --*/
#ifndef MT_TMR_CHANGES
#ifdef ANSI
PUBLIC S16 cmXtaActvTmr
(
Void
)
#else
PUBLIC S16 cmXtaActvTmr(Void)
#endif
#else
#ifdef ANSI
PUBLIC S16 cmXtaActvTmr
(
Ent    ent,
Inst   inst
)
#else
PUBLIC S16 cmXtaActvTmr(ent, inst)
Ent    ent;
Inst   inst;
#endif
#endif
#endif
{
#ifdef SS_MULTIPLE_PROCS
   UNUSED(proc);
   UNUSED(ent);
   UNUSED(inst);
#endif

   TRC2(cmXtaActvTmr)
   
   cmPrcTmr(&cmXtaCb.tqCp, cmXtaCb.tq, (PFV) cmXtaProcTmr);

   RETVALUE(ROK);
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
PUBLIC S16 cmXtaStartTmr
(
S16     event,
Ptr     cp,
U16     tmrVal
)
#else
PUBLIC S16 cmXtaStartTmr(event, cp, tmrVal)
S16     event;
Ptr     cp;
U16     tmrVal;
#endif
{
   CmTmrArg tmrArg;
   CmXtaTCCb *tcCb = NULLP;

   TRC2(cmXtaStartTmr)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaStartTmr(): tmrEvnt (%d), timerVal (%d)\n", event, tmrVal));

   /* Do the proper casting */
   switch (event)
   {
      case CMXTA_TMR_GUARD_EXP :
      case CMXTA_TMR_TIMEOUT   :
      case CMXTA_TMR_DELAY     :
      case CMXTA_TMR_DELAY_TST :
      case CMXTA_TMR_DELAY_SHUTDOWN :

         tcCb = (CmXtaTCCb *) cp;
         tmrArg.wait = tmrVal;
         tmrArg.max  = CMXTA_MAX_TMR;
         tmrArg.timers = tcCb->timers;

         break;
#if 0
      case CMXTA_TMR_PERD_RPT_TMR :
         {
            WrAccPerdRptTmr   *perdRptTmr = NULLP;
            perdRptTmr = (WrAccPerdRptTmr *) cp;
            tmrArg.wait = tmrVal;
            tmrArg.max  = CMXTA_MAX_TMR;
            tmrArg.timers = perdRptTmr->tcCb->timers;
            break;
         }

      case CMXTA_TMR_T321:
         {
            WrAccT321   *t321 = NULLP;
            t321 = (WrAccT321 *) cp;
            tmrArg.wait = tmrVal;
            tmrArg.max  = CMXTA_MAX_TMR;
            tmrArg.timers = t321->tcCb->timers;
            break;
         }
#endif
      default:
         CMXTA_DBG_ERR((_cmxtap, "cmXtaStartTmr(): invalid tmrEvnt (%d)\n", event));
         RETVALUE(CMXTA_ERR_INT);
         break;
   } /* End of switch */


   /* Timer value should not be zero */
   if (tmrArg.wait != 0)
   {
      tmrArg.tqCp   = &(cmXtaCb.tqCp); /* Timing Queue control point */
      tmrArg.tq     = cmXtaCb.tq;      /* Timing Queue */
      tmrArg.cb     = (PTR)cp;         /* Control block to return in case of timer expiry */
      tmrArg.evnt   = (U8)event;       /* Timer event for this timer */
      tmrArg.tNum   = 0;
      cmPlcCbTq(&tmrArg);              /* Place the timer on the timing queue */
      RETVALUE(CMXTA_ERR_NONE);
   }

   /* cm_xta_tmr_c_001.main_6: Fix for 64bit compilation warning */
#ifdef ALIGN_64BIT
   CMXTA_DBG_ERR((_cmxtap, "cmXtaStartTmr(): started timer for (%d)\n", tmrArg.wait));
#else
   CMXTA_DBG_ERR((_cmxtap, "cmXtaStartTmr(): started timer for (%ld)\n", tmrArg.wait));
#endif /* ALIGN_64BIT */

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
PUBLIC S16 cmXtaStopTmr
(
S16     event,
Ptr     cp
)
#else
PUBLIC S16 cmXtaStopTmr(event, cp)
S16     event;
Ptr     cp;
#endif
{
   U8  tmrNum;
   CmTmrArg tmrArg;

   TRC2(cmXtaStopTmr)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaStopTmr(): tmrEvnt (%d)\n", event));

   /* Do the proper casting */
   switch (event)
   {
      case CMXTA_TMR_GUARD_EXP :
      case CMXTA_TMR_TIMEOUT   :
      case CMXTA_TMR_DELAY     :
      case CMXTA_TMR_DELAY_TST :
      case CMXTA_TMR_DELAY_SHUTDOWN :
      {
         CmXtaTCCb *tcCb = (CmXtaTCCb *) cp;
         tmrArg.max  = CMXTA_MAX_TMR;
         tmrArg.timers = tcCb->timers;
         break;
      }

#if 0
      case CMXTA_TMR_PERD_RPT_TMR :
         {
            WrAccPerdRptTmr   *perdRptTmr = (WrAccPerdRptTmr *) cp;
            tmrArg.max  = CMXTA_MAX_TMR;
            tmrArg.timers = perdRptTmr->tcCb->timers;
            break;
         }

      case CMXTA_TMR_T321:
         {
            WrAccT321   *t321 = (WrAccT321 *) cp;
            tmrArg.max  = CMXTA_MAX_TMR;
            tmrArg.timers = t321->tcCb->timers;
            break;
         }
#endif
      default:
         CMXTA_DBG_ERR((_cmxtap, "cmXtaStopTmr(): invalid tmrEvnt (%d)\n", event));
         RETVALUE(CMXTA_ERR_INT);
   } /* End of switch */

   /* search in the timer queue of the cb for this timer event */

   for (tmrNum = 0; tmrNum < (U8)tmrArg.max; tmrNum++)
   {
      if (tmrArg.timers[tmrNum].tmrEvnt == event)
      {
         tmrArg.tqCp   = &(cmXtaCb.tqCp);
         tmrArg.tq     = cmXtaCb.tq;
         tmrArg.cb     = (PTR) cp;
         tmrArg.evnt   = event;
         tmrArg.wait   = 0;
         tmrArg.tNum   = tmrNum;
         cmRmvCbTq(&tmrArg);
      }
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
PUBLIC Void cmXtaProcTmr
(
PTR cb,
S16 event
)
#else
PUBLIC Void cmXtaProcTmr(cb, event)
PTR cb;
S16 event;
#endif
{
   TRC2(cmXtaProcTmr)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaProcTmr(): tmrEvnt (%d)\n", event));

   switch (event)
   {
      case CMXTA_TMR_GUARD_EXP :
      case CMXTA_TMR_TIMEOUT   :
      case CMXTA_TMR_DELAY     :
      case CMXTA_TMR_DELAY_TST :
      case CMXTA_TMR_DELAY_SHUTDOWN :
      {
         CmXtaTCCb *tcCb = (CmXtaTCCb *) cb;

         /*-- Call internal timer handler callback to push
              the message in the test queue --*/
         cmXtaIntPrcTimerExp(tcCb, event);
         break;
      }
#if 0
      case CMXTA_TMR_PERD_RPT_TMR:
         {
            WrAccPerdRptTmr *perdRptTmr = (WrAccPerdRptTmr *) cb;
            printf("\n Perd Rpt Tmr expired ");
            WrAccHdlPerdRptTmrExpiry(perdRptTmr);
            break;
         }

      case CMXTA_TMR_T321:
         {
            WrAccT321   *t321 = (WrAccT321 *) cb;
            printf("\n T321 Timer expired so sending empty CGI report ");
            WrAccHdlT321Expiry(t321);
            break;
         }
#endif
      default:
         CMXTA_DBG_ERR((_cmxtap, "cmXtaProcTmr(): invalid tmrEvnt (%d)\n", event));
   } /* End of switch */

   RETVOID;
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
PUBLIC S16 cmXtaTmrInitQ
(
Void
)
#else
PUBLIC S16 cmXtaTmrInitQ()
#endif
{
   Pst      pst;
   S16      ret;
   ProcId   srcProcId;
   ProcId   dstProcId;

   TRC2(cmXtaTmrInitQ)

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTmrInitQ(): init tmr module\n"));

   cmXtaCb.tqCp.nxtEnt = 0;
   cmXtaCb.tqCp.tmrLen = CMXTA_TQ_SIZE;

   /* cmXtaGetPst moved out of MULTIPLE PROC*/
   /*-- Get the Pst information here --*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaGetPst(&pst, ENTTST, CMXTA_INST_ID, ENTTST, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   /*-- Register the timer function with SSI --*/
#ifdef SS_MULTIPLE_PROCS
   if ((ret = SRegCfgTmr(pst.srcProcId, pst.srcEnt, pst.srcInst,
                         (S16  )cmXtaCb.timerPeriod   , /* 1, 2, 3 etc               */
                         (S16  )cmXtaCb.timerUnit     , /* SS_1MS, SS_10MS, SS_100MS */
                         cmXtaActvTmr)) != ROK)
#else
#ifndef SS_MT_TMR
   if ((ret = SRegCfgTmr(pst.srcEnt, pst.srcInst,
                         (S16  )cmXtaCb.timerPeriod   , /* 1, 2, 3 etc               */
                         (S16  )cmXtaCb.timerUnit     , /* SS_1MS, SS_10MS, SS_100MS */
                         cmXtaActvTmr)) != ROK)
/* cm_xta_tmr_c_001.main_5 Modifed the Called function to SRegCfgTmrMt if SS_MT_TMR is enabled */
#else
   if ((ret = SRegCfgTmrMt(pst.srcEnt, pst.srcInst,
                         (S16  )cmXtaCb.timerPeriod   , /* 1, 2, 3 etc               */
                         (S16  )cmXtaCb.timerUnit     , /* SS_1MS, SS_10MS, SS_100MS */
                         (PAIFTMRS16)cmXtaActvTmr)) != ROK)
#endif
#endif
      RETVALUE(ret);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTmrInitQ(): tmr init done\n"));

   RETVALUE(ROK);
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
PUBLIC S16 cmXtaTmrDeInitQ
(
Void
)
#else
PUBLIC S16 cmXtaTmrDeInitQ()
#endif
{
   Pst      pst;
   ProcId   srcProcId;
   ProcId   dstProcId;

   TRC2(cmXtaTmrDeInitQ)

   /*-- Get the Pst information here --*/
   /* cmXtaGetPst moved out of MULTIPLE PROC*/
   srcProcId = CMXTA_PROCID_MASTER;
   dstProcId = CMXTA_PROCID_MASTER;
   cmXtaGetPst(&pst, ENTTST, CMXTA_INST_ID, ENTTST, CMXTA_INST_ID, srcProcId, dstProcId, FALSE);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTmrDeInitQ(): shutdown tmr module\n"));

#ifdef SS_MULTIPLE_PROCS
   SDeregCfgTmr(pst.srcProcId, pst.srcEnt, pst.srcInst, (S16)cmXtaCb.timerPeriod, (S16)cmXtaCb.timerUnit, (PAIFTMRS16)cmXtaActvTmr);
#else
#ifndef SS_MT_TMR
   SDeregCfgTmr(pst.srcEnt, pst.srcInst, (S16)cmXtaCb.timerPeriod, (S16)cmXtaCb.timerUnit, cmXtaActvTmr);
/* cm_xta_tmr_c_001.main_5 Modifed the Called function to SDeregCfgTmrMt if SS_MT_TMR is enabled */
#else
   SDeregCfgTmrMt(pst.srcEnt, pst.srcInst, (S16)cmXtaCb.timerPeriod, (S16)cmXtaCb.timerUnit, (PAIFTMRS16)cmXtaActvTmr);
#endif
#endif

   CMXTA_ZERO(&cmXtaCb.tqCp, sizeof(CmTqCp));
   CMXTA_ZERO((U8 *)&cmXtaCb.tq, sizeof(CmTqType) * CMXTA_TQ_SIZE);

   CMXTA_DBG_INFO((_cmxtap, "cmXtaTmrDeInitQ(): shutdown done\n"));

   RETVALUE(ROK);
}


/********************************************************************30**

         End of file:     cm_xta_tmr.c@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Fri Jul 19 19:25:10 2013

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
/main/2      ----                 up  1. Main release
/main/3  cm_xta_tmr_c_001.main_2  sk  1. Support for multiple proc 
/main/4      ---                  aj  1. cmXtaGetPst moved out of MULTIPLE_PROC 
                                      2. FTHA Integration related change 
/main/5      ---                  st  1. Added support for newly introduced
                                         timer activation changes under 
                                         MT_TMR_CHANGES flag.
/main/6      ---      cm_xta_tmr_c_001.main_5  ds  1. Modifed the Called function
                                         to SRegCfgTmrMt & SDeregCfgTmrMt if 
                                         SS_MT_TMR is defined.
/main/7      ---      cm_xta_tmr_c_001.main_6  pkaX 1. Fix for 64bit compilation warning
/main/8      ----     cm_xta_tmr_c_001.main_7  nh 1. Updated for Psf-Diameter 1.1
                                                  release Removed cm_xta_app.[hx]
*********************************************************************91*/
