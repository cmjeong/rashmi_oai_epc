

/********************************************************************20**
 
     Name:     System Services -- Timing
 
     Type:     C source file
 
     Desc:     Source code for System Services related to timing.
 
     File:     ss_timer.c
 
     Sid:      ss_timer.c@@/main/2 - Mon Apr  5 18:01:21 2010
 
     Prg:      kp
  
*********************************************************************21*/


/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

#include "ss_err.h"        /* errors */
#include "ss_dep.h"        /* implementation-specific */
#include "ss_queue.h"      /* queues */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */



/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */



/* ss028.103 - Modification for SRegCfgTmr Support */
/*
*
*       Fun:   Register Configurable Timer Task - timer
*
*       Desc:  This function is used to register a timer function for the
*              layer. The system services will periodically invoke the
*              function passed to it. The timer function will be used by the
*              layer to manage the layers internal protocol timers.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_timer.c
*
*/
/* ss029.103: addition: procId added and timer function type modified */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SRegCfgTmr
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PFS16 tmrFnct               /* timer function, typically SActvTmr */
)
#else
PUBLIC S16 SRegCfgTmr(ent, inst, period, units, tmrFnct)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
PFS16 tmrFnct;              /* timer function, typically SActvTmr */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SRegCfgTmr
(
ProcId proc,                /* processor */
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PAIFTMRS16 tmrFnct               /* timer function, typically SActvTmr */
)
#else
PUBLIC S16 SRegCfgTmr(proc, ent, inst, period, units, tmrFnct)
ProcId proc;                /* processor */
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
PAIFTMRS16 tmrFnct;              /* timer function, typically SActvTmr */
#endif

#endif /* SS_MULTIPLE_PROCS */
{
#if (ERRCLASS & ERRCLS_INT_PAR)
   U8 i;
#endif
   S16 ret;
   SsTmrEntry *tmr;
/* ss029.103: addition: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
#if (ERRCLASS & ERRCLS_INT_PAR)
   U16 procIdIdx;
#endif /* ERRCLASS & ERRCLS_INT_PAR */
#endif /* SS_MULTPLE_PROCS */

   TRC1(SRegCfgTmr);

#if (ERRCLASS & ERRCLS_INT_PAR)

/* ss029.103: addition: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS787, ERRZERO, "Invalid processor/entity/instance");
      RETVALUE(RFAILED);
   }
#else /* SS_MULTIPLE_PROCS */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS788, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* check period */
   if (period <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS789, ERRZERO, "Invalid period");
      RETVALUE(RFAILED);
   }

   /* check period units*/
   if ((units < 1) || (units > SS_TICKS_SEC))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS790, ERRZERO, "Invalid period units");
      RETVALUE(RFAILED);
   }

   /* check timer function */
   if (tmrFnct == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS791, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }

/* ss029.103: addition: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* check if the procId has been registered with SSI */
   procIdIdx = SGetProcIdIdx(proc);

   if (procIdIdx == SS_INV_PROCID_IDX)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS792, ERRZERO,
                     "Could not find proc id index");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */


   /* check task ID */
   /* lock TAPA task table */
   SS_ACQUIRE_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS793, ERRZERO,
                     "Could not lock TAPA task table");
      RETVALUE(RFAILED);
   }

/* ss029.103: addition: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if (osCp.tTskIds[procIdIdx][ent][inst] == SS_TSKNC)
#else /* SS_MULTIPLE_PROCS */
   if (osCp.tTskIds[ent][inst] == SS_TSKNC)
#endif /* SS_MULTIPLE_PROCS */
   {
#if 0  /* ss006.13: deletion */
      SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1  /* ss006.13: addition */
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS794, ERRZERO,
                     "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: addition */
      SSLOGERROR(ERRCLS_INT_PAR, ESS795, ERRZERO, "Unknown task");
      RETVALUE(RFAILED);
   }
#if 0  /* ss006.13: deletion */
   SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1  /* ss006.13: addition */
   if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS796, ERRZERO,
                     "Could not release the semaphore");
   RETVALUE(RFAILED);
#endif
   }
#endif /* ss006.13: addition */

#endif

   /* lock the timer table */
   ret = SLock(&osCp.tmrTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS797, (ErrVal) ret,
                     "Could not lock timer table");
#endif
      RETVALUE(ret);
   }


   /* check if we've got room for another timer */
   if (osCp.numTmrs == SS_MAX_TMRS)
   {
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.tmrTblLock);
#endif /* ss006.13: deletion */
#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.tmrTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS798, ERRZERO,
                     "Could not unlock the semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS799, ERRZERO, "Too many timers");
#endif

      RETVALUE(ROUTRES);
   }

   /* ss021.103 - Addtion of check for duplicate timer */
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check through the timer table for a matching timer entry */
   for (i = 0; i < SS_MAX_TMRS; i++)
   {   
/* ss029.103: addition: multiple procId related changes */ 
      if ((osCp.tmrTbl[i].ownerEnt == ent) &&  
#ifdef SS_MULTIPLE_PROCS
          (osCp.tmrTbl[i].ownerProc == proc) && 
#endif /* SS_MULTIPLE_PROCS */
          (osCp.tmrTbl[i].ownerInst == inst) && 
          (osCp.tmrTbl[i].tmrActvFn == tmrFnct) && 
          (osCp.tmrTbl[i].interval == (U32) ((period * SS_TICKS_SEC) / units)))
      {  
         /* is this timer in use ? (unexpired) */
         if (osCp.tmrTbl[i].used == TRUE)
         {  
            /* to prevent the same timer to be registered with SS  UNLOCK and */
            /* then RFAIL */
            if (SUnlock(&osCp.tmrTblLock) != ROK)
            {
#if (ERRCLASS & ERRCLS_DEBUG)
   SSLOGERROR(ERRCLS_DEBUG, ESS800, ERRZERO, "Could not unlock the semaphore");
   RETVALUE(RFAILED);
#endif
            }
            RETVALUE(RFAILED);
         }
      }
   }
#endif

   /* fill in the information we have into the timer entry */
   tmr = &osCp.tmrTbl[osCp.nxtTmrEntry];
   tmr->tmrId     = osCp.nxtTmrEntry;
/* ss029.103: addition: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
   tmr->ownerProc = proc;
#endif /* SS_MULTIPLE_PROCS */
   tmr->ownerEnt  = ent;
   tmr->ownerInst = inst;
   tmr->interval  = (U32) ((period * SS_TICKS_SEC) / units);
   tmr->tmrActvFn = tmrFnct;


   /* ask the implementation to start the timer */
   ret = ssdRegTmr(tmr);
   if (ret != ROK)
   {
      tmr->tmrId = 0;
/* ss029.103: addition: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
      tmr->ownerProc = PROCNC;
#endif /* SS_MULTIPLE_PROCS */
      tmr->ownerEnt = ENTNC;
      tmr->ownerInst = INSTNC;
      tmr->interval = 0;
      tmr->tmrActvFn = NULLP;
   }
   else
   {
      tmr->used = TRUE;
      osCp.nxtTmrEntry = tmr->nxt;
      osCp.numTmrs++;
   }


   /* unlock the timer table */
#if 0  /* ss006.13: deletion */
   SUnlock(&osCp.tmrTblLock);
#endif /* ss006.13: deletion */
#if 1  /* ss006.13: addition */
   if ( SUnlock(&osCp.tmrTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS801, ERRZERO,
                     "Could not unlock the semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif /* ss006.13: addition */

   RETVALUE(ret);
}


/* ss028.103 - Modification for SRegCfgTmr support */
/*
*
*       Fun:   SDeregCfgTmr  
*
*       Desc:  This function is used to deregister a timer function.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_timer.c
*
*/
/* ss029.103: addition: procId added and timer function type modified */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SDeregCfgTmr
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PFS16 tmrFnct               /* timer function */
)
#else
PUBLIC S16 SDeregCfgTmr(ent, inst, period, units, tmrFnct)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
PFS16 tmrFnct;              /* timer function */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SDeregCfgTmr
(
ProcId proc,                /* processor */
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
S16 units,                  /* period units */
PAIFTMRS16 tmrFnct               /* timer function */
)
#else
PUBLIC S16 SDeregCfgTmr(proc, ent, inst, period, units, tmrFnct)
ProcId proc;                /* processor */
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
S16 units;                  /* period units*/
PAIFTMRS16 tmrFnct;              /* timer function */
#endif

#endif /* SS_MULTIPLE_PROCS */
{
   S16 ret;
   S16 idx;
   SsTmrEntry *tmr;
/* ss029.103: addition: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
#if (ERRCLASS & ERRCLS_INT_PAR)
   U16 procIdIdx;
#endif /* ERRCLASS & ERRCLS_INT_PAR */
#endif /* SS_MULTIPLE_PROCS */


   TRC1(SDeregCfgTmr);


#if (ERRCLASS & ERRCLS_INT_PAR)

/* ss029.103: addition: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS802, ERRZERO, "Invalid processor/entity/instance");
      RETVALUE(RFAILED);
   }

#else /* SS_MULTIPLE_PROCS */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS803, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */
   /* check period */
   if (period <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS804, ERRZERO, "Invalid period");
      RETVALUE(RFAILED);
   }

   /* check period units */
   if ((units < 1) || (units > SS_TICKS_SEC))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS805, ERRZERO, "Invalid period units");
      RETVALUE(RFAILED);
   }

   /* check timer function */
   if (tmrFnct == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS806, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }

/* ss029.103: addition: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* check if the procId has been registered with SSI */
   procIdIdx = SGetProcIdIdx(proc);

   if (procIdIdx == SS_INV_PROCID_IDX)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS807, ERRZERO,
                     "Could not find proc id index");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* check task ID */
   /* lock TAPA task table */
   SS_ACQUIRE_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS808, ERRZERO,
                     "Could not lock TAPA task table");
      RETVALUE(RFAILED);
   }

/* ss029.103: addition: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if (osCp.tTskIds[procIdIdx][ent][inst] == SS_TSKNC)
#else /* SS_MULTIPLE_PROCS */
   if (osCp.tTskIds[ent][inst] == SS_TSKNC)
#endif /* SS_MULTIPLE_PROCS */
   {
#if 0  /* ss006.13: deletion */
      SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1  /* ss006.13: addition */
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS809, ERRZERO,
                     "Could not release the semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: addition */
      SSLOGERROR(ERRCLS_INT_PAR, ESS810, ERRZERO, "Unknown task");
      RETVALUE(RFAILED);
   }
#if 0  /* ss006.13: deletion */
   SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1  /* ss006.13: addition */
   if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS811, ERRZERO,
                     "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
    }
#endif /* ss006.13: addition */

#endif

   /* lock the timer table */
   ret = SLock(&osCp.tmrTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS812, (ErrVal) ret,
                     "Could not lock timer table");
#endif
      RETVALUE(ret);
   }


   /* Note: Right now, we're using ent, inst and tmrActvFn to locate
    *       the timer,, this will change to using tmrId, some day.
    */

   /* locate the timer to delete in the timer table */
   for (idx = 0;  idx < SS_MAX_TMRS;  idx++)
   {
      /* ss021.103 - Modification find timer by ent, inst, func, and period */
      /* ss029.103: addition: multiple procId related changes */ 
      if (osCp.tmrTbl[idx].ownerEnt == ent
#ifdef SS_MULTIPLE_PROCS
            &&  osCp.tmrTbl[idx].ownerProc == proc 
#endif /* SS_MULTIPLE_PROCS */
            &&  osCp.tmrTbl[idx].ownerInst == inst
            &&  osCp.tmrTbl[idx].tmrActvFn == tmrFnct
	    &&  osCp.tmrTbl[idx].interval == (U32) ((period * SS_TICKS_SEC) / units))
      {
         break;
      }
   }

   if (idx == SS_MAX_TMRS)
   {
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.tmrTblLock);
#endif /* ss006.13: deletion */
#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.tmrTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS813, ERRZERO,
                     "Could not unlock the semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS814, ERRZERO, "Could not locate timer");
#endif

      RETVALUE(RFAILED);
   }


   /* ask the implementation to shut down this timer */
   tmr = &osCp.tmrTbl[idx];
   ret = ssdDeregTmr(tmr);
   if (ret == ROK)
   {
      tmr->used = FALSE;
      tmr->tmrId = 0;
/* ss029.103: addition: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
      tmr->ownerProc = PROCNC;
#endif /* SS_MULTIPLE_PROCS */
      tmr->ownerEnt = ENTNC;
      tmr->ownerInst = INSTNC;
      tmr->interval = 0;
      tmr->tmrActvFn = NULLP;

      tmr->nxt = osCp.nxtTmrEntry;
      osCp.nxtTmrEntry = (SsIdx)idx;
      osCp.numTmrs--;
   }


   /* unlock the timer table */
#if 0  /* ss006.13: deletion */
   SUnlock(&osCp.tmrTblLock);
#endif /* ss006.13: deletion */
#if 1  /* ss006.13: addition */
   if ( SUnlock(&osCp.tmrTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS815, ERRZERO,
                     "Could not unlock the semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif /* ss006.13: addition */


   RETVALUE(ret);
}



/********************************************************************30**
  
         End of file:     ss_timer.c@@/main/2 - Mon Apr  5 18:01:21 2010
  
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
1.1          ---      kp   1. initial release
  
1.2          ---      bsr  1. Regenerated the error codes

1.3          ---      kp   1. Regenerated error codes
1.3+        ss006.13  jn   2. Compile warning - "Value computed
                              is not used" removed for
                              SS_RELEASE_SEMA and SUnlock.
1.3+        ss021.103 bjp  3. Modification to find a timer by ent, inst,
                                 func, and period in SDeregTmr
			      Check for duplicate timer in SRegTmr
1.3+        ss028.103 bjp  1. Modification for SRegCfgTmr support
1.3+        ss029.103 kkj  1. Multiple proc ids support added
/main/4      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/
