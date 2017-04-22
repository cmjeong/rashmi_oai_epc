

/********************************************************************20**
 
     Name:     System Services -- Task Management
 
     Type:     C source file
 
     Desc:     Source code for System Services functions for task mgmt.
 
     File:     ss_task.c
 
     Sid:      ss_task.c@@/main/2 - Mon Apr  5 18:01:20 2010
 
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
#include "ss_task.h"       /* tasking */
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

/* ss029.103: modification: 
   Old SSI functions are not supported with multiple procIds */ 
#ifndef SS_MULTIPLE_PROCS

/*
*
*       Fun:   SRegInit
*
*       Desc:  This function is used to register an initialization function
*              for the layer. The system services will invoke the function
*              passed to it one time. The initialization function will be
*              used by the layer to initilize the layer.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRegInit
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
PAIFS16 initFnct            /* initialization function */
)
#else
PUBLIC S16 SRegInit(ent, inst, initFnct)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
PAIFS16 initFnct;           /* initialization function */
#endif
{
   /* ss021.103 - Addition for return value and pointer */
   S16         ret;     /* return value */
   SsTTskEntry *tTsk;

   TRC1(SRegInit);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance ranges */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS482, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }

   /* check initialization function */
   if (initFnct == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS483, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif

   /* ss021.103 - Modification to store initialization function */
   /* Acquire the counting semaphore for all other system
    *  tasks (this call is either running in one system task's
    *  context, or in SInit()'s context). Once we have all of
    *  them, SPstTsk() cannot run, so we can do things to the
    *  TAPA task table.
    */

   /* ss025.103 - Addition of lock around counting semaphore */
   /* lock system task table */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS484, ERRZERO,
                     "Could not lock system task table");
      RETVALUE(RFAILED);
   }

   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS485, ERRZERO,
                 "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check count of tasks */
   if (osCp.numTTsks == SS_MAX_TTSKS)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      SSLOGERROR(ERRCLS_INT_PAR, ESS486, ERRZERO, "Too many tasks");

      /* ss025.103 - Addition of unlock around counting semephore */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS487, ERRZERO,
                      "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(ROUTRES);
   }

   /* check if entity and instance already registered */
   if (osCp.tTskIds[ent][inst] != SS_TSKNC)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      SSLOGERROR(ERRCLS_INT_PAR, ESS488, ERRZERO,
                 "Entity and instance already registered");

      /* ss025.103 - Addition of unlock around counting semaphore */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS489, ERRZERO,
                         "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(RFAILED);
   }
#endif

   tTsk = &osCp.tTskTbl[osCp.nxtTTskEntry];

   tTsk->used     = TRUE;
   tTsk->ent      = ent;
   tTsk->inst     = inst;
   tTsk->tskType  = (Ttype)NULLD;
   tTsk->tskPrior = (Prior)NULLD;
   tTsk->initTsk  = initFnct;
   tTsk->actvTsk  = (ActvTsk)NULLP;
   tTsk->sTsk     = NULLP;

   osCp.tTskIds[ent][inst] = osCp.nxtTTskEntry;
   osCp.nxtTTskEntry = tTsk->nxt;
   osCp.numTTsks++;

   /* Activate initialization function, if present. Like
    *  SRegInit(), we use hard-coded parameters. Note: we
    *  assume that the initialization function is not
    *  going to call SRegTTsk() or SPstTsk(). If it does,
    *  this thread will freeze up as we are holding the
    *  TAPA task table counting semaphore.
    */
   /* ss024.103 - Modification for memory calculator tool */
#ifndef USE_MEMCAL
   (Void)(*initFnct)(ent, inst, DFLT_REGION, PWR_UP);
#else
   (Void)(*initFnct)(ent, inst, SS_STATIC_REGION, PWR_UP);
#endif /* USE_MEMCAL */

   /* unlock the table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   /* ss025.103 - Addition of unlock around counting semaphore */
   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS490, ERRZERO,
                      "Could not give the Semaphore");
      RETVALUE(RFAILED);
#endif
   }

   RETVALUE(ROK);
} /* SRegInit */



/*
*
*       Fun:   SRegActvTsk
*
*       Desc:  This function is used to register an activation function
*              for the layer. The system services will invoke the
*              function passed to it whenever a task buffer is received.
*              The activation function will be used by the layer to receive
*              messages from other entities.  It allows a priority to be
*              associated with the task so that it can be preempted if
*              necessary.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: We pass NULLP for the initialization function, because
*              it is assumed that whoever is using this call will also
*              be calling SRegInit().
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegActvTsk
(
Ent ent,                       /* entity */
Inst inst,                     /* instance */
Ttype ttype,                   /* task type */
Prior prior,                   /* task priority */
ActvTsk actvTsk                /* activate task function */
)
#else
PUBLIC S16 SRegActvTsk(ent, inst, ttype, prior, actvTsk)
Ent ent;                       /* entity */
Inst inst;                     /* instance */
Ttype ttype;                   /* task type */
Prior prior;                   /* task priority */
ActvTsk actvTsk;               /* activate task function */
#endif
{
   S16 ret;
   SSTskId sTskId;
   Prior spri;
   /* ss021.103 - Addition for pointer */
   SsTTskEntry *tTsk;

   TRC1(SRegActvTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance ranges */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS491, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }

   /* check activation function */
   if (actvTsk == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS492, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }

   /* check task type */
   if (ttype != TTNORM  &&  ttype != TTPERM)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS493, ERRZERO, "Invalid task type");
      /* ss021.103 - Addition of return fail for invalid task type */
      RETVALUE(RFAILED);
   }

   /* check task priority */
   if (prior > PRIOR3)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS494, ERRZERO, "Invalid task priority");
      RETVALUE(RFAILED);
   }
#endif

   /* lock system task table */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS495, ERRZERO,
                     "Could not lock system task table");
      RETVALUE(RFAILED);
   }

   /* lock TAPA task table */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS496, ERRZERO,
                         "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }
 
      SSLOGERROR(ERRCLS_DEBUG, ESS497, ERRZERO,
                     "Could not lock TAPA task table");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Modification for SRegInit not called yet */
   /* check if entity and instance already registered */
   if (osCp.tTskIds[ent][inst] == SS_TSKNC)
   {

#if (ERRCLASS & ERRCLS_INT_PAR)
      /* check count of tasks */
      if (osCp.numTTsks == SS_MAX_TTSKS)
      {
         SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

         /* ss025.103 - Addition of unlock around counting semaphore */
         if ( SUnlock(&osCp.sTskTblLock) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS498, ERRZERO,
                         "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
         }
         SSLOGERROR(ERRCLS_INT_PAR, ESS499, ERRZERO, "Too many tasks");
         RETVALUE(ROUTRES);
      }
#endif

      tTsk = &osCp.tTskTbl[osCp.nxtTTskEntry];
      tTsk->used     = TRUE;
      tTsk->ent      = ent;
      tTsk->inst     = inst;
      tTsk->initTsk  = (PAIFS16)NULLP;
      tTsk->actvTsk  = (ActvTsk)NULLP;
      tTsk->sTsk     = NULLP;

      osCp.tTskIds[ent][inst] = osCp.nxtTTskEntry;
      osCp.nxtTTskEntry = tTsk->nxt;
      osCp.numTTsks++;
   }


   /* check and bump the priority if it is a permanent task */
   if(ttype == TTPERM)
   {
      prior = PRIOR3;
   }

   /* ss021.103 - Modification to register task information */
   /*  We fill up the current available slot with all the
    *  information we've been given. Update table information,
    *  and the task is registered.
    */

   tTsk = &osCp.tTskTbl[osCp.tTskIds[ent][inst]];
   
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (tTsk->actvTsk != (ActvTsk)NULLP)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS500, ERRZERO,
                    "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      SSLOGERROR(ERRCLS_INT_PAR, ESS501, ERRZERO, 
                 "ActvTask already registered");
      RETVALUE(RFAILED);
   }
#endif

   tTsk->tskType  = ttype;
   tTsk->tskPrior = prior;
   tTsk->actvTsk  = actvTsk;

   /* unlock the table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS502, ERRZERO,
                      "Could not give the Semaphore");
      RETVALUE(RFAILED);
#endif
   }

   /*  Now we create a system task--one per TAPA task is the
    *  semantics of SRegActvTsk().
    */
   if (ttype == TTNORM)
      spri = SS_NORM_TSK_PRI;
   else
      spri = SS_PERM_TSK_PRI;

   ret = SCreateSTsk(spri, &sTskId);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS503, (ErrVal) ret,
                     "Could not create system task");
#endif

      SDeregTTsk(ent, inst);
      RETVALUE(ret);
   }


   /*  Attach the TAPA task we just registered, to the system
    *  task we just created.
    */
   ret = SAttachTTsk(ent, inst, sTskId);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS504, (ErrVal) ret,
                     "Could not attach TAPA task to system task");
#endif
      SDestroySTsk(sTskId);
      SDeregTTsk(ent, inst);
   }


   RETVALUE(ret);

} /* SRegActvTsk */
 

/*
*
*       Fun:   Deregister Initialize, task buffer and timer
*
*       Desc:  This function is used to deregister the initialization,
*              activation and timer functions for a task.
*
*       Ret:   ROK      - ok
*
*       Notes: None.
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SDeregInitTskTmr
(
Ent ent,                       /* entity */
Inst inst                      /* instance */
)
#else
PUBLIC S16 SDeregInitTskTmr(ent, inst)
Ent ent;                       /* entity */
Inst inst;                     /* instance */
#endif
{
   SsTTskEntry *tTsk;
   SsSTskEntry *sTsk;
   S16         ret;
   SSTskId     sTskId;
   SsIdx       idx;
   Bool        destroySTsk;


   TRC1(SDeregInitTskTmr);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance ranges */
   if (ent >= SS_MAX_ENT  ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS505, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif

   /* ss025.103 - Addition of lock around counting semaphore */
   /* lock system task table */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS506, ERRZERO,
                     "Could not lock system task table");
      RETVALUE(RFAILED);
   }

   /* lock the TAPA task table */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS507, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check whether this entity is registered */
   if (osCp.tTskIds[ent][inst] == SS_TSKNC)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      SSLOGERROR(ERRCLS_INT_PAR, ESS508, ERRZERO, "Unknown task");

      /* ss025.103 - Addition of unlock around counting semaphore */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS509, ERRZERO,
                         "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(RFAILED);
   }
#endif


   /* get out the TAPA task entry */
   tTsk = &osCp.tTskTbl[osCp.tTskIds[ent][inst]];

   /* get out the system task that's running this TAPA task */
   sTsk = tTsk->sTsk;

   /* get out the ID of this system task */
   if (sTsk != NULLP)
   {
      sTskId = sTsk->tskId;
   }
   else 
      sTskId = 0;

   /* unlock the TAPA task table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   /* ss025.103 - Addition of unlock around counting semaphore */
   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS510, ERRZERO,
                      "Could not give the Semaphore");
      RETVALUE(RFAILED);
#endif
   }


   /* deregister the TAPA task */
   if (SDeregTTsk(ent, inst) != ROK)
   {
      RETVALUE(RFAILED);
   }


   /* Now, if the TAPA task was attached, and nobody else is using that
    *  system task, we should destroy it.
    */
   if (sTsk != NULLP)
   {
      destroySTsk = FALSE;

      /* lock the system task table */
      ret = SLock(&osCp.sTskTblLock);
      if (ret != ROK)
      {

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS511, (ErrVal) ret,
                        "Could not lock system task table");
#endif

         RETVALUE(RFAILED);
      }

      idx = (SsIdx) sTskId;
      sTsk = &osCp.sTskTbl[idx];

      /* check if the system task is still around */
      if (sTsk->used != TRUE)
      {
#if 0  /* ss006.13: deletion */
         SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
         if ( SUnlock(&osCp.sTskTblLock) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS512, ERRZERO,
                         "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
         }
#endif  /* ss006.13: addition */

         RETVALUE(ROK);
      }

      /* check if the system task is dying already */
      if (sTsk->termPend)
      {
#if 0  /* ss006.13: deletion */
         SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
         if ( SUnlock(&osCp.sTskTblLock) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS513, ERRZERO,
                         "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
         }
#endif  /* ss006.13: addition */
         RETVALUE(ROK);
      }


      /* If this system task entry has no more TAPA tasks attached,
       *  we destroy it, otherwise we do nothing.
       */
      if (sTsk->numTTsks == 0)
      {
         sTsk->termPend = TRUE;
         destroySTsk = TRUE;
      }


      /* unlock */
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS514, ERRZERO,
                      "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

      /* If we're destroying the system task, ask the implementation
       *  to do it.
       */
      if (destroySTsk)
      {
         ret = ssdDestroySTsk(sTsk);
         if (ret != ROK)
         {
            /* oops? */

#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS515, (ErrVal) ret,
                        "Could not destroy system task");
#endif

            RETVALUE(RFAILED);
         }
      }
   }


   RETVALUE(ROK);
} /* SDeregInitTskTmr */

#endif /* SS_MULTIPLE_PROCS */


/*
*
*       Fun:   Register a TAPA task
*
*       Desc:  This function is used to register a TAPA task,
*              and its initialization and activation functions.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
/* ss029.103: modification: procId added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SRegTTsk
(
Ent ent,                        /* entity */
Inst inst,                      /* instance */
Ttype type,                     /* task type */
Prior prior,                    /* task priority */
PAIFS16 initTsk,                /* initialization function */
ActvTsk actvTsk                 /* activation function */
)
#else
PUBLIC S16 SRegTTsk(ent, inst, type, prior, initTsk, actvTsk)
Ent ent;                        /* entity */
Inst inst;                      /* instance */
Ttype type;                     /* task type */
Prior prior;                    /* task priority */
PAIFS16 initTsk;                /* initialization function */
ActvTsk actvTsk;                /* activation function */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SRegTTsk
(
ProcId proc,                    /* processor */
Ent ent,                        /* entity */
Inst inst,                      /* instance */
Ttype type,                     /* task type */
Prior prior,                    /* task priority */
PAIFS16 initTsk,                /* initialization function */
ActvTsk actvTsk                 /* activation function */
)
#else
PUBLIC S16 SRegTTsk(proc, ent, inst, type, prior, initTsk, actvTsk)
ProcId proc;                    /* processor */
Ent ent;                        /* entity */
Inst inst;                      /* instance */
Ttype type;                     /* task type */
Prior prior;                    /* task priority */
PAIFS16 initTsk;                /* initialization function */
ActvTsk actvTsk;                /* activation function */
#endif

#endif /* SS_MULTIPLE_PROCS */

{
   S16 ret = ROK;
   SsTTskEntry *tTsk;
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   U16 procIdIdx;
#endif

   TRC1(SRegTTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)

   /* check entity and instance ranges */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS516, ERRZERO, "Invalid proc/entity/instance");
      RETVALUE(RFAILED);
   }
#else /* SS_MULTIPLE_PROCS */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS517, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* check activation function */
   if (actvTsk == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS518, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }

   /* check task type */
   if (type != TTNORM  &&  type != TTPERM)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS519, ERRZERO, "Invalid task type");
      /* ss021.103 - Addition of return fail for invalid task type */
      RETVALUE(RFAILED);
   }

   /* check task priority */
   if (prior > PRIOR3)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS520, ERRZERO, "Invalid task priority");
      RETVALUE(RFAILED);
   }
#endif

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* retrieve proc id index in the proc id table */
   procIdIdx = SGetProcIdIdx(proc); 

   /* Check whether the proc id exist in the proc id table */
   if (procIdIdx == SS_INV_PROCID_IDX)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
       SSLOGERROR(ERRCLS_INT_PAR, ESS521, ERRZERO,
                     "Could not find proc table index");
#endif

      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */



   /* Acquire the counting semaphore for all other system
    *  tasks (this call is either running in one system task's
    *  context, or in SInit()'s context). Once we have all of
    *  them, SPstTsk() cannot run, so we can do things to the
    *  TAPA task table.
    */

   /* ss025.103 - Addition of lock around counting semaphore */
   /* lock system task table */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS522, ERRZERO,
                     "Could not lock system task table");
      RETVALUE(RFAILED);
   }

   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS523, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      /* ss025.103 - Addition of unlock around counting semaphore */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS524, ERRZERO,
                      "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_DEBUG)
   /* check count of tasks */
   if (osCp.numTTsks == SS_MAX_TTSKS)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      SSLOGERROR(ERRCLS_DEBUG, ESS525, ERRZERO, "Too many tasks");

      /* ss025.103 - Addition of unlock around counting semaphore */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS526, ERRZERO,
                      "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(ROUTRES);
   }

   /* check if entity and instance already registered */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if (osCp.tTskIds[procIdIdx][ent][inst] != SS_TSKNC)
#else
   if (osCp.tTskIds[ent][inst] != SS_TSKNC)
#endif /* SS_MULTIPLE_PROCS */
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      SSLOGERROR(ERRCLS_DEBUG, ESS527, ERRZERO,
                  "Entity and instance already registered");

      /* ss025.103 - Addition of unlock around counting semaphore */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS528, ERRZERO,
                      "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(RFAILED);
   }
#endif


   /*  We fill up the current available slot with all the
    *  information we've been given. Update table information,
    *  and the task is registered.
    */
   tTsk = &osCp.tTskTbl[osCp.nxtTTskEntry];
   tTsk->used     = TRUE;
/* ss029.103: addition: procId added */ 
#ifdef SS_MULTIPLE_PROCS
   tTsk->proc     = proc;
#endif /* SS_MULTIPLE_PROCS */
   tTsk->ent      = ent;
   tTsk->inst     = inst;
   tTsk->tskType  = type;
   tTsk->tskPrior = prior;
   tTsk->initTsk  = initTsk;
   tTsk->actvTsk  = actvTsk;
   tTsk->sTsk     = NULLP;
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   osCp.tTskIds[procIdIdx][ent][inst] = osCp.nxtTTskEntry;
#else
   osCp.tTskIds[ent][inst] = osCp.nxtTTskEntry;
#endif /* SS_MULTIPLE_PROCS */
   osCp.nxtTTskEntry = tTsk->nxt;
   osCp.numTTsks++;


   /* Activate initialization function, if present. Like
    *  SRegInit(), we use hard-coded parameters. Note: we
    *  assume that the initialization function is not
    *  going to call SRegTTsk() or SPstTsk(). If it does,
    *  this thread will freeze up as we are holding the
    *  TAPA task table counting semaphore.
    */
   /* ss024.103 - Modification for memory calculator tool */
   if (initTsk != NULLP)
   {
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
      SsIdx idx;
      Void *xxCb = NULLP;
#endif /* SS_MULTIPLE_PROCS */

/* ss029.103: addition: multiple procIds related changes */ 
#ifndef SS_MULTIPLE_PROCS

#ifndef USE_MEMCAL
#ifndef SSI_MEM_CHNG
      (Void)(*initTsk)(ent, inst, DFLT_REGION, PWR_UP);
#endif
#else
      (Void)(*initTsk)(ent, inst, SS_STATIC_REGION, PWR_UP);
#endif /* USE_MEMCAL */

#else /* SS_MULTIPLE_PROCS */

#ifndef USE_MEMCAL
      (Void)(*initTsk)(proc, ent, inst, DFLT_REGION, PWR_UP, &xxCb);
#else
      (Void)(*initTsk)(proc, ent, inst, SS_STATIC_REGION, PWR_UP, &xxCb);
#endif /* USE_MEMCAL */

      /*
       * store the control block. The control block may be NULL in some cases
       */
      idx = osCp.tTskIds[procIdIdx][ent][inst]; 

      osCp.tTskTbl[idx].xxCb = xxCb;

      /* ss032.103 do a debug print if xxCb is NULLP */
      if (xxCb == NULLP)
      {
         SSLOGERROR(ERRCLS_INT_PAR, ERRZERO, ERRZERO, "Null pointer");
      }
#endif /* SS_MULTIPLE_PROCS */
   }

   /* unlock the table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   /* ss025.103 - Addition of unlock around counting semaphore */
   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS533, ERRZERO,
                      "Could not give the Semaphore");
#endif
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* SRegTTsk */


/*
*
*       Fun:   Deregister TAPA task
*
*       Desc:  This function is used to deregister a TAPA task.
*              All information about the task is removed from the
*              task table.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
/* ss029.103: addition: procId added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SDeregTTsk
(
Ent ent,                        /* entity */
Inst inst                       /* instance */
)
#else
PUBLIC S16 SDeregTTsk(ent, inst)
Ent ent;                        /* entity */
Inst inst;                      /* instance */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SDeregTTsk
(
ProcId proc,                    /* processor */
Ent ent,                        /* entity */
Inst inst                       /* instance */
)
#else
PUBLIC S16 SDeregTTsk(proc, ent, inst)
ProcId proc;                    /* processor */
Ent ent;                        /* entity */
Inst inst;                      /* instance */
#endif

#endif /* SS_MULTIPLE_PROCS */

{
   S16          ret;
   /* ss029.103: modification: The subscript should be consistent type */
   SsIdx          n;
   SsIdx        idx;
   SsTTskEntry *tTsk;
   SsSTskEntry *sTsk;
   SsTmrEntry  *tmr;
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   U16 procIdIdx;
#endif /* SS_MULTIPLE_PROCS */

   TRC1(SDeregTTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance ranges */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS534, ERRZERO, "Invalid processor/entity/instance");
      RETVALUE(RFAILED);
   }
#else /* SS_MULTIPLE_PROCS */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS535, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

#endif

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* Find the proc table index */
   procIdIdx = SGetProcIdIdx(proc);

   if (procIdIdx == SS_INV_PROCID)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS536, ERRZERO,
                             "Could not find proc id index");
#endif
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* We deregister all timers for this TAPA task, since it's going
    *  away now. Lock the timer table and iterate through it, removing
    *  all timers owned by this task.
    */
   if (SLock(&osCp.tmrTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS537, ERRZERO,
                             "Could not lock timer table");
#endif
      RETVALUE(RFAILED);
   }

   for (idx = 0;  idx < SS_MAX_TMRS;  idx++)
   {
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
      if ((osCp.tmrTbl[idx].ownerProc == proc) &&  
          (osCp.tmrTbl[idx].ownerEnt == ent) &&  
          (osCp.tmrTbl[idx].ownerInst == inst))
#else /* SS_MULTIPLE_PROCS */
      if ((osCp.tmrTbl[idx].ownerEnt == ent) &&  
          (osCp.tmrTbl[idx].ownerInst == inst))
#endif /* SS_MULTIPLE_PROCS */
      {
         /* shut down this timer */
         tmr = &osCp.tmrTbl[idx];
         if (ssdDeregTmr(tmr) == ROK)
         {
            tmr->used      = FALSE;
            tmr->tmrId     = 0;
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
            tmr->ownerProc  = PROCNC;
#endif /* SS_MULTIPLE_PROCS */
            tmr->ownerEnt  = ENTNC;
            tmr->ownerInst = INSTNC;
            tmr->interval  = 0;
            tmr->tmrActvFn = NULLP;

            tmr->nxt = osCp.nxtTmrEntry;
            osCp.nxtTmrEntry = (SsIdx)idx;
            osCp.numTmrs--;
         }
         else
         {
#if 0  /* ss006.13: deletion */
           SUnlock(&osCp.tmrTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
          if ( SUnlock(&osCp.tmrTblLock) != ROK)
          {
#if (ERRCLASS & ERRCLS_DEBUG)
             SSLOGERROR(ERRCLS_DEBUG, ESS538, ERRZERO,
                      "Could not give the Semaphore");
             RETVALUE(RFAILED);
#endif
          }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS539, ERRZERO,
                        "Could not deregister task's timer(s)");
#endif
            RETVALUE(RFAILED);

         }
      }
   }

#if 0  /* ss006.13: deletion */
           SUnlock(&osCp.tmrTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
          if ( SUnlock(&osCp.tmrTblLock) != ROK)
          {
#if (ERRCLASS & ERRCLS_DEBUG)
             SSLOGERROR(ERRCLS_DEBUG, ESS540, ERRZERO,
                      "Could not give the Semaphore");
             RETVALUE(RFAILED);
#endif
          }
#endif  /* ss006.13: addition */


   /* Now, we grab the system task table lock and the locks
    *  for all the system tasks. This will prevent them from
    *  examining the TAPA task index table while we're changing
    *  it. This is only necessary for one case, where a task is
    *  detached from a system task and is being deregistered,
    *  but messages for it are still in the system task's demand
    *  queue.
    */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS541, (ErrVal) ret,
                     "Could not lock system task table");
#endif

      RETVALUE(RFAILED);
   }

   for (n = 0;  n < SS_MAX_STSKS;  n++)
   {
      if (osCp.sTskTbl[n].used)
      {
         if (!SS_CHECK_CUR_STSK(&osCp.sTskTbl[n]))
         {
            ret = SLock(&osCp.sTskTbl[n].lock);
            if (ret != ROK)
            {
#if (ERRCLASS & ERRCLS_DEBUG)
               SSLOGERROR(ERRCLS_DEBUG, ESS542, (ErrVal) ret,
                              "Could not lock system task entry");
#endif
               /* unlock everything we've locked */
               while (n > 0)
               {
                  n--;
                  if (osCp.sTskTbl[n].used)
                  {
                     if (!SS_CHECK_CUR_STSK(&osCp.sTskTbl[n]))
                     {
#if 0  /* ss006.13: deletion */
                        SUnlock(&osCp.sTskTbl[n].lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
                        if ( SUnlock(&osCp.sTskTbl[n].lock) != ROK)
                        {
#if (ERRCLASS & ERRCLS_DEBUG)
                           SSLOGERROR(ERRCLS_DEBUG, ESS543, ERRZERO,
                              "Could not give the Semaphore");
                           RETVALUE(RFAILED);
#endif
                        }
#endif  /* ss006.13: addition */
                     }
                  }
               }
#if 0  /* ss006.13: deletion */
               SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
               if ( SUnlock(&osCp.sTskTblLock) != ROK)
               {
#if (ERRCLASS & ERRCLS_DEBUG)
                   SSLOGERROR(ERRCLS_DEBUG, ESS544, ERRZERO,
                             "Could not give the Semaphore");
                    RETVALUE(RFAILED);
#endif
               }
#endif  /* ss006.13: addition */

               RETVALUE(RFAILED);
            }
         }
      }
   }


   /* Acquire the counting semaphore for all TAPA tasks. Once
    *  we have all of them, both SPstTsk() and SRegTTsk() cannot
    *  run, so we can do things to the TAPA task table.
    */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
      /* unlock all the system task entries */
      for (n = 0;  n < SS_MAX_STSKS;  n++)
      {
         if (osCp.sTskTbl[n].used)
         {
            if (!SS_CHECK_CUR_STSK(&osCp.sTskTbl[n]))
            {
#if 0  /* ss006.13: deletion */
               SUnlock(&osCp.sTskTbl[n].lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
               if ( SUnlock(&osCp.sTskTbl[n].lock) != ROK)
               {
#if (ERRCLASS & ERRCLS_DEBUG)
                    SSLOGERROR(ERRCLS_DEBUG, ESS545, ERRZERO,
                         "Could not give the Semaphore");
                    RETVALUE(RFAILED);
#endif
               }
#endif  /* ss006.13: addition */
            }
         }
      }

      /* unlock the system task table */
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
       if ( SUnlock(&osCp.sTskTblLock) != ROK)
       {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS546, ERRZERO,
                         "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
       }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS547, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


   /* get out the TAPA task entry */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   idx = osCp.tTskIds[procIdIdx][ent][inst];
#else /* SS_MULTIPLE_PROCS */
   idx = osCp.tTskIds[ent][inst];
#endif /* SS_MULTIPLE_PROCS */


   /* make sure this TAPA task exists */
   if (idx == SS_TSKNC)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

      /* unlock all the system task entries */
      for (n = 0;  n < SS_MAX_STSKS;  n++)
      {
         if (osCp.sTskTbl[n].used)
         {
            if (!SS_CHECK_CUR_STSK(&osCp.sTskTbl[n]))
            {
#if 0  /* ss006.13: deletion */
               SUnlock(&osCp.sTskTbl[n].lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
               if ( SUnlock(&osCp.sTskTbl[n].lock) != ROK)
               {
#if (ERRCLASS & ERRCLS_DEBUG)
                  SSLOGERROR(ERRCLS_DEBUG, ESS548, ERRZERO,
                         "Could not give the Semaphore");
                  RETVALUE(RFAILED);
#endif
               }
#endif  /* ss006.13: addition */
            }
         }
      }

      /* unlock the system task table */
#if 0  /* ss006.13: deletion */
               SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
               if ( SUnlock(&osCp.sTskTblLock) != ROK)
               {
#if (ERRCLASS & ERRCLS_DEBUG)
                  SSLOGERROR(ERRCLS_DEBUG, ESS549, ERRZERO,
                         "Could not give the Semaphore");
                  RETVALUE(RFAILED);
#endif
               }
#endif  /* ss006.13: addition */

      SSLOGERROR(ERRCLS_INT_PAR, ESS550, ERRZERO, "Unknown task");
      RETVALUE(RFAILED);
   }

   tTsk = &osCp.tTskTbl[idx];

#ifdef SS_MULTIPLE_PROCS
   /* ss032.103: Call the init function of the TAPA task */
   if (tTsk->initTsk != NULLP)
   {
#ifndef USE_MEMCAL
      (Void)(*(tTsk->initTsk))(proc, ent, inst, 
                             DFLT_REGION, 
                             NRM_TERM, 
                             &(osCp.tTskTbl[idx].xxCb));
#else
      (Void)(*(tTsk->initTsk))(proc, ent, inst, 
                             SS_STATIC_REGION, 
                             NRM_TERM, 
                             &(osCp.tTskTbl[idx].xxCb));
#endif /* USE_MEMCAL */
   }
#endif /* SS_MULTIPLE_PROCS */

   /* We check the sTsk element; if it is not NULLP, the
    *  task is attached. So we have to detach it before
    *  deregistering the task.
    */
   if (tTsk->sTsk != NULLP)
   {
      sTsk = tTsk->sTsk;

      tTsk->sTsk = NULLP;

      for (n = 0;  n < SS_MAX_TTSKS;  n++)
      {
         if (sTsk->tTsks[n] == idx)
         {
            sTsk->tTsks[n] = SS_INVALID_IDX;
            sTsk->numTTsks--;
            break;
         }
      }

      /* call the implementation to detach the task */
      ssdDetachTTsk(tTsk);
   }


   /* Now we empty the entry for this task and update the table
    *  information
    */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS 
   osCp.tTskIds[procIdIdx][ent][inst] = SS_TSKNC;
#else /* SS_MULTIPLE_PROCS */
   osCp.tTskIds[ent][inst] = SS_TSKNC;
#endif /* SS_MULTIPLE_PROCS */

   tTsk->used    = FALSE;
#ifdef SS_MULTIPLE_PROCS
   tTsk->proc    = PROCNC;
#endif /* SS_MULTIPLE_PROCS */
   tTsk->ent     = ENTNC;
   tTsk->inst    = INSTNC;
   tTsk->tskType = TTUND;
   tTsk->initTsk = NULLP;
   tTsk->actvTsk = NULLP;
   tTsk->sTsk    = NULLP;

   tTsk->nxt = osCp.nxtTTskEntry;
   osCp.nxtTTskEntry = idx;
   osCp.numTTsks--;

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* mark the control block for this task as invalid */
   osCp.tTskTbl[idx].xxCb = NULLP;
#endif

   /* unlock the TAPA task table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   /* unlock all the system task entries */
   for (n = 0;  n < SS_MAX_STSKS;  n++)
   {
      if (osCp.sTskTbl[n].used)
      {
         if (!SS_CHECK_CUR_STSK(&osCp.sTskTbl[n]))
         {
#if 0  /* ss006.13: deletion */
            SUnlock(&osCp.sTskTbl[n].lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
            if ( SUnlock(&osCp.sTskTbl[n].lock) != ROK)
            {
#if (ERRCLASS & ERRCLS_DEBUG)
                SSLOGERROR(ERRCLS_DEBUG, ESS551, ERRZERO,
                         "Could not give the Semaphore");
                RETVALUE(RFAILED);
#endif
             }
#endif  /* ss006.13: addition */
         }
      }
   }

   /* unlock the system task table */
#if 0  /* ss006.13: deletion */
               SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
               if ( SUnlock(&osCp.sTskTblLock) != ROK)
               {
#if (ERRCLASS & ERRCLS_DEBUG)
                  SSLOGERROR(ERRCLS_DEBUG, ESS552, ERRZERO,
                         "Could not give the Semaphore");
                  RETVALUE(RFAILED);
#endif
               }
#endif  /* ss006.13: addition */

   RETVALUE(ROK);
} /* SDeregTTsk */


/*
*
*       Fun:   Create system task
*
*       Desc:  This function is used to create a system task. An
*              entry is located in the system task table and the
*              implementation-specific function is called.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SCreateSTsk
(
SSTskPrior tskPrior,            /* task priority */
SSTskId *tskId                  /* filled in with system task ID */
)
#else
PUBLIC S16 SCreateSTsk(tskPrior, tskId)
SSTskPrior tskPrior;            /* task priority */
SSTskId *tskId;                 /* filled in with system task ID */
#endif
{
   S16 ret;
   SsSTskEntry *sTsk;


   TRC1(SCreateSTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check task ID pointer */
   if (tskId == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS553, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }

   /* check system task priority */
   if (tskPrior > SS_LOWEST_STSK_PRIOR)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS554, ERRZERO,
                     "Invalid system task priority");
      RETVALUE(RFAILED);
   }
#endif


   /* lock the system task table */ 
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS555, (ErrVal) ret,
                     "Could not lock system task table");
#endif

      RETVALUE(RFAILED);
   }


#ifdef SS_SINGLE_THREADED
   /* When singlethreaded, we only need to create one... */
#ifndef SSI_MEM_CHNG
   if (osCp.numSTsks == 1)
#else
   if (osCp.numSTsks == 2)
#endif /* SSI_MEM_CHNG */
   {
#ifndef SSI_MEM_CHNG
      *tskId = 0;
      osCp.sTskTbl[0].termPend = FALSE;
#else
      *tskId = 1;
      osCp.sTskTbl[1].termPend = FALSE;
#endif /* SSI_MEM_CHNG */
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS556, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

      RETVALUE(ROK);
   }
#endif /* SS_SINGLE_THREADED */


   /* check count of system tasks */
   if (osCp.numSTsks == SS_MAX_STSKS)
   {
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS557, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_ADD_RES)
      SSLOGERROR(ERRCLS_ADD_RES, ESS558, ERRZERO, "Too many system tasks");
#endif

      RETVALUE(ROUTRES);
   }


   /* initialize the system task entry with the information we have */
   sTsk = &osCp.sTskTbl[osCp.nxtSTskEntry];

   /* store the system task priority */
   sTsk->tskPrior = tskPrior;

   /* initialize the demand queue */
   if (ssInitDmndQ(&sTsk->dQ) != ROK)
   {
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS559, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS560, (ErrVal) ret,
                  "Could not initialize demand queue");
#endif

      RETVALUE(RFAILED);
   }

   /* initialize the system task entry lock */
   if (SInitLock(&sTsk->lock, SS_STSKENTRY_LOCK) != ROK)
   {
      ssDestroyDmndQ(&sTsk->dQ);
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS561, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS562, (ErrVal) ret,
                  "Could not initialize system task entry lock");
#endif

      RETVALUE(RFAILED);
   }


   /* we ask the implementation to start this system task */
   ret = ssdCreateSTsk(sTsk);
   if (ret != ROK)
   {
      /* failed, clean up */
      SDestroyLock(&sTsk->lock);
      ssDestroyDmndQ(&sTsk->dQ);
      sTsk->tskPrior = 0;

#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS563, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS564, (ErrVal) ret,
                  "Could not create system task");
#endif

      RETVALUE(RFAILED);
   }

   /* success, update the table */
   *tskId = osCp.nxtSTskEntry;
   sTsk->tskId       = osCp.nxtSTskEntry;
   sTsk->used        = TRUE;
   sTsk->termPend    = FALSE;
   osCp.nxtSTskEntry = sTsk->nxt;
   osCp.numSTsks++;

   /* unlock the system task table */
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS565, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

   RETVALUE(ROK);

} /* SCreateSTsk */

/** for multi-core support **/
#ifdef SS_MULTICORE_SUPPORT

/*
*
*       Fun:   Register the CPU information
*
*       Desc:  This function is used to register the number of cores
*              present and the number of threads which can be run on
*              each core.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegCpuInfo 
(
SCpuInfo *cpuInfo    /* Information about the cores/threads per core */
)
#else
PUBLIC S16 SRegCpuInfo (cpuInfo)
SCpuInfo *cpuInfo;  /* Information about the cores/threads per core */
#endif
{
	U32 coreCount = 0;

   /* check the number of cores */
	if ( cpuInfo->numCores > SS_MAX_CORES || 
	    cpuInfo->threadsPerCore > SS_MAX_THREADS_PER_CORE || 
		 cpuInfo->numCores < 1 || 
		 cpuInfo->threadsPerCore < 1 )
	{
      SSLOGERROR(ERRCLS_INT_PAR, ESS822, ERRZERO, "Invalid number of cores\n");
      RETVALUE(RFAILED);
	}

   /* lock mCInfo */
	SLock(&osCp.mCILock);
	osCp.mCInfo.cpuInfo.numCores = cpuInfo->numCores;
	osCp.mCInfo.cpuInfo.threadsPerCore = cpuInfo->threadsPerCore;
	/* if the cpu register is supplied then use it */
	for (; coreCount < cpuInfo->numCores; coreCount++)
	{
	    U32 thrCnt = 0;
		 for (;thrCnt < SS_MAX_THREADS_PER_CORE;thrCnt++)
		 {
	      osCp.mCInfo.coreInfo[coreCount].tskPerCoreLst[thrCnt] = -1;
		 } /* for */
	    osCp.mCInfo.coreInfo[coreCount].exclusive = FALSE;
	    osCp.mCInfo.coreInfo[coreCount].thrs 
		  = osCp.mCInfo.cpuInfo.threadRegister[coreCount] 
		  = cpuInfo->threadRegister[coreCount];
	}
   /* unlock mCInfo */
	SUnlock(&osCp.mCILock);

   RETVALUE(ROK);

} /* SRegCpuInfo */



/*
*
*       Fun:   Get the current core/cpu affinity for a thread/lwp
*
*       Desc:  This function is used to get the current processor/core 
*              affinity for a a system task (thread/lwp). It sets the 
*              affinity based on the mode supplied by the caller. 
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetAffinity
(
SSTskId *tskId,                  /* filled in with system task ID */
U32 *coreId                      /* the core/processor id to which the affinity is set */
)
#else
PUBLIC S16 SGetAffinity(tskId, coreId)
SSTskId *tskId;                 /* filled in with system task ID */
U32 *coreId;                    /* the core/processor id to which the affinity is set */
#endif
{
   S16 ret;

	/* implementation specific */
	ret = ssdGetAffinity(tskId, coreId);

	if (ret != ROK)
	{
     SSLOGERROR(ERRCLS_INT_PAR, ESS823, ERRZERO, "Failed to get affinity\n");
	  RETVALUE(RFAILED);
	} /* end if */


   RETVALUE(ROK);

} /* SGetAffinity */


/*
*
*       Fun:   Set the core/cpu affinity for a thread/lwp
*
*       Desc:  This function is used to set processor/core affinity for a 
*              a system task (thread/lwp). It sets the affinity based on the
*              mode supplied by the caller. 
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SSetAffinity
(
SSTskId *tskId,                  /* filled in with system task ID */
SsAffinityMode mode,             /* the mode according to which the affinty is set */
U32 coreId,                      /* the core/processor id to which the affinity has to be set */
SSTskId *tskAssociatedTskId      /* filled in with system task ID of the associated layer */
)
#else
PUBLIC S16 SSetAffinity(tskId, mode, coreId, tskAssociatedTskId)
SSTskId *tskId;                 /* filled in with system task ID */
SsAffinityMode mode;            /* the mode according to which the affinty is set */
U32 coreId;                     /* the core/processor id to which the affinity has to be set */
SSTskId *tskAssociatedTskId;    /* filled in with system task ID of the associated layer */
#endif
{
   S16 ret;
  
   /* validate the mode */
	if (mode < SS_AFFINITY_MODE_DEFAULT || 
	    mode > SS_AFFINITY_MODE_EXCL)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS824, ERRZERO, "Invalid mode for setting core affinity\n");
      RETVALUE(RFAILED);
	} /* end if */

	/* check the value of core id */
	if (SS_AFFINITY_MODE_SPECIFIC == mode && 
	    (coreId > osCp.mCInfo.cpuInfo.numCores || coreId < 0))
	{
      SSLOGERROR(ERRCLS_INT_PAR, ESS825, ERRZERO, "Invalid core id\n");
      RETVALUE(RFAILED);
	} /* end if */

	/* set affinity according to the mode supplied */
	switch (mode)
	{
	  case SS_AFFINITY_MODE_DEFAULT:
	  {
	    U32 coreCounter = 0, coreIndex = 0;
		 S8 repeatFlag = 1;
		 SEARCH_FOR_CORE:
		 for (coreIndex = osCp.mCInfo.currentCore;  
		      coreCounter < osCp.mCInfo.cpuInfo.numCores; 
				coreCounter++, coreIndex = (++coreIndex)%osCp.mCInfo.cpuInfo.numCores /* again start from core 0 */ 
			  )
		 {
		   if (!osCp.mCInfo.coreInfo[coreIndex].exclusive 
				 && osCp.mCInfo.cpuInfo.threadRegister[coreIndex])
			{
			  if (osCp.mCInfo.coreInfo[coreIndex].thrs || !repeatFlag)  
			  {
	          /* call the implementation specific affinity function */
		       ret = ssdSetAffinity(tskId, coreIndex);
      
		       if (ret != ROK)
		       {
               SSLOGERROR(ERRCLS_INT_PAR, ESS826, ERRZERO, "Failed to set core affinity\n");
               RETVALUE(RFAILED);
		       } /* end if */
  
				 /* lock mCInfo */
				 SLock(&osCp.mCILock);
			    /* move the current core index */
			    osCp.mCInfo.currentCore = (coreIndex+1)%osCp.mCInfo.cpuInfo.numCores;
  
				 /* save the tskId in tskList */
				 osCp.mCInfo.coreInfo[coreIndex].tskPerCoreLst[
				   osCp.mCInfo.cpuInfo.threadRegister[coreIndex] - 
					osCp.mCInfo.coreInfo[coreIndex].thrs] = *tskId;

			    /* decrement the available thread count in the thread register */
			    osCp.mCInfo.coreInfo[coreIndex].thrs--;

				 /* unlock mCInfo */
				 SUnlock(&osCp.mCILock);
  
			    break;
			  } /* end if there are threads available in the core */    
			} /* end if the core is not exclusive flagged and 
			       the core has threads for SSI use */
		 } /* end for */
		 if (coreCounter == osCp.mCInfo.cpuInfo.numCores && repeatFlag)
		 {
			repeatFlag = 0;
		   SSLOGERROR(ERRCLS_INT_PAR, ESS829, ERRZERO, "Overloading of threads per core!!\n");
			goto SEARCH_FOR_CORE; 
		 } /* end if no thrs on cores available and overallocation is needed */
	    break;
	  } /* end case SS_AFFINITY_MODE_DEFAULT */
	  case SS_AFFINITY_MODE_SPECIFIC:
	  {
	    /* check if the core is used exclusively for any task */
		 if (osCp.mCInfo.coreInfo[coreId].exclusive)
		 {
         SSLOGERROR(ERRCLS_INT_PAR, ESS831, ERRZERO, "Can not set core affinity, core is exclusively used for other task\n");
         RETVALUE(RFAILED);
		 } /* end if */
	    /* call the implementation specific affinity function with the core id supplied by caller */
		 ret = ssdSetAffinity(tskId, coreId);

		 if (ret != ROK)
		 {
         SSLOGERROR(ERRCLS_INT_PAR, ESS826, ERRZERO, "Failed to set core affinity\n");
         RETVALUE(RFAILED);
		 } /* end if */

		 /* lock mCInfo */
		 SLock(&osCp.mCILock);

		 /* move the current core index */
		 osCp.mCInfo.currentCore = (coreId+1)%osCp.mCInfo.cpuInfo.numCores;

       /* save the tskId in tskList */
       osCp.mCInfo.coreInfo[coreId].tskPerCoreLst[
         osCp.mCInfo.cpuInfo.threadRegister[coreId] - 
         osCp.mCInfo.coreInfo[coreId].thrs] = *tskId;
 
       /* decrement the available thread count in the thread register */
       osCp.mCInfo.coreInfo[coreId].thrs--;
 
		 /* unlock mCInfo */
		 SUnlock(&osCp.mCILock);

		 if (osCp.mCInfo.coreInfo[coreId].thrs < 0)
		 {
		   SSLOGERROR(ERRCLS_INT_PAR, ESS829, ERRZERO, "Overloading of threads per core!!\n");
		 } /* end else */


	    break;
	  } /* end case SS_AFFINITY_MODE_SPECIFIC */
	  case SS_AFFINITY_MODE_ASSOC:
	  {
	   
		 /* search for the associated tsk id in osCp */
		 U32 coreIndex = 0, threadIndex = 0;
		 Bool tskNotFound = TRUE;
		 for (;tskNotFound && coreIndex < SS_MAX_CORES; coreIndex++)
		 {
		   for (threadIndex = 0; threadIndex < SS_MAX_THREADS_PER_CORE; threadIndex++)
			{
		     if (osCp.mCInfo.coreInfo[coreIndex].tskPerCoreLst[threadIndex] == *tskAssociatedTskId)
			  {
			    if (!osCp.mCInfo.coreInfo[coreIndex].exclusive)
				 {
			      /* set the affinity for the given task on to the core coreIndex */
			      ret = ssdSetAffinity(tskId, coreIndex);
    
		         if (ret != ROK)
		         {
                 SSLOGERROR(ERRCLS_INT_PAR, ESS826, ERRZERO, "Failed to set core affinity\n");
                 RETVALUE(RFAILED);
		         } /* end if */
    
					/* lock mCInfo */
					SLock(&osCp.mCILock);

			      /* move the current core index */
			      osCp.mCInfo.currentCore = (coreIndex+1)%osCp.mCInfo.cpuInfo.numCores;
    
               /* save the tskId in tskList */
               osCp.mCInfo.coreInfo[coreIndex].tskPerCoreLst[               
                osCp.mCInfo.cpuInfo.threadRegister[coreIndex] - 
                osCp.mCInfo.coreInfo[coreIndex].thrs] = *tskId;
 
               /* decrement the available thread count in the thread register */
               osCp.mCInfo.coreInfo[coreIndex].thrs--;
 
					/* unlock mCInfo */
					SUnlock(&osCp.mCILock);

				   if (osCp.mCInfo.coreInfo[coreIndex].thrs < 0) 
				   {
		           SSLOGERROR(ERRCLS_INT_PAR, ESS829, ERRZERO, "Overloading of threads per core!!\n");
				   } /* end if */

				 } /* end if */
				 else
				 {
               SSLOGERROR(ERRCLS_INT_PAR, ESS831, ERRZERO, "Can not set core affinity, core is exclusively used for other task\n");
					RETVALUE(RFAILED);
				 } /* end else */
				 tskNotFound = FALSE;
			    break;
			  } /* end if */
			} /* end inner for */
		 } /* end for */

		 /* check if tskAssociatedTskId is valid or not */
		 if (coreIndex == SS_MAX_CORES)
		 {
		   SSLOGERROR(ERRCLS_INT_PAR, ESS832, ERRZERO, "Invalid core id\n");
			RETVALUE(RFAILED);
		 } /* if */
	    break;
	  } /* end case SS_AFFINITY_MODE_ASSOC */
	  case SS_AFFINITY_MODE_EXCL:
	  {
	    /* check if any thread is already running on the core */
		 if (coreId != SS_DEFAULT_CORE && 
		     osCp.mCInfo.coreInfo[coreId].thrs == osCp.mCInfo.cpuInfo.threadRegister[coreId] &&
			  !osCp.mCInfo.coreInfo[coreId].exclusive)
		 {
	      /* call the implementation specific affinity function */
		   ret = ssdSetAffinity(tskId, coreId);
    
		   if (ret != ROK)
		   {
           SSLOGERROR(ERRCLS_INT_PAR, ESS826, ERRZERO, "Failed to set core affinity\n");
           RETVALUE(RFAILED);
		   } /* end if */
		
			/* lock mCInfo */
			SLock(&osCp.mCILock);

			/* set the exclusive flag so that the core will not be used for other system tasks */
		   osCp.mCInfo.coreInfo[coreId].exclusive = TRUE;
         
         /* save the tskId in tskList */
         osCp.mCInfo.coreInfo[coreId].tskPerCoreLst[               
          osCp.mCInfo.cpuInfo.threadRegister[coreId] - 
          osCp.mCInfo.coreInfo[coreId].thrs] = *tskId;
 
         /* decrement the available thread count in the thread register */
         osCp.mCInfo.coreInfo[coreId].thrs--;
 
			/* unlock mCInfo */
			SUnlock(&osCp.mCILock);

		 } /* end if */
		 else if (coreId == SS_DEFAULT_CORE)
		 {
	        U32 coreCounter = 0, coreIndex = 0;
		     for (coreIndex = osCp.mCInfo.currentCore;  
		          coreCounter < osCp.mCInfo.cpuInfo.numCores; 
				    coreCounter++, (++coreIndex)%osCp.mCInfo.cpuInfo.numCores  
			      )
		     {
		       if (!osCp.mCInfo.coreInfo[coreIndex].exclusive 
				     && osCp.mCInfo.cpuInfo.threadRegister[coreIndex])
			    {
			      if ( osCp.mCInfo.coreInfo[coreIndex].thrs == osCp.mCInfo.cpuInfo.threadRegister[coreIndex] &&
					    osCp.mCInfo.coreInfo[coreIndex].thrs)  
			      {
	              /* call the implementation specific affinity function */
		           ret = ssdSetAffinity(tskId, coreIndex);
          
		           if (ret != ROK)
		           {
                   SSLOGERROR(ERRCLS_INT_PAR, ESS826, ERRZERO, "Failed to set core affinity\n");
                   RETVALUE(RFAILED);
		           } /* end if */
      
					  /* lock mCInfo */
					  SLock(&osCp.mCILock);

			        /* move the current core index */
			        osCp.mCInfo.currentCore = (coreIndex+1)%osCp.mCInfo.cpuInfo.numCores;
      
                 /* save the tskId in tskList */
                 osCp.mCInfo.coreInfo[coreIndex].tskPerCoreLst[               
                   osCp.mCInfo.cpuInfo.threadRegister[coreIndex] - 
                   osCp.mCInfo.coreInfo[coreIndex].thrs] = *tskId;
 
                 /* decrement the available thread count in the thread register */
                 osCp.mCInfo.coreInfo[coreIndex].thrs--;
 
			        /* set the exclusive flag so that the core will not be used for other system tasks */
		           osCp.mCInfo.coreInfo[coreIndex].exclusive = TRUE;

					  /* unlock mCInfo */
					  SUnlock(&osCp.mCILock);

			        break;
			      } /* end if there are threads available in the core */    
			    } /* end if the core is not exclusive flagged and 
			           the core has threads for SSI use */
		     } /* end for */
		     if (coreCounter == osCp.mCInfo.cpuInfo.numCores)
		     {
                 SSLOGERROR(ERRCLS_INT_PAR, ESS828, ERRZERO, "Failed to set core affinity, no threads on cores available\n");
                 RETVALUE(RFAILED);
		     } /* end if no thrs on cores available */
			  

		 } /* else if */
		 else
		 {
         SSLOGERROR(ERRCLS_INT_PAR, ESS830, ERRZERO, "Can not set exclusive affinity for the core\n");
         RETVALUE(RFAILED);
		 } /* end else */
	    break;
	  } /* end case SS_AFFINITY_MODE_EXCL */
	  default:
	  {
	    SSLOGERROR(ERRCLS_INT_PAR, ESS827, ERRZERO, "Invalid mode for setting core affinity\n");
		 RETVALUE(RFAILED);
	  } /* end default case */
	} /* end of switch */

   RETVALUE(ROK);

} /* SSetAffinity */

#endif /* SS_MULTICORE_SUPPORT */

/** end multi-core support **/


/*
*
*       Fun:   Destroy system task
*
*       Desc:  This function is used to destroy a system task. The
*              entry is located in the system task table and the
*              implementation-specific function is called.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SDestroySTsk
(
SSTskId tskId                   /* system task to be destroyed */
)
#else
PUBLIC S16 SDestroySTsk(tskId)
SSTskId tskId;                  /* system task to be destroyed */
#endif
{
   S16 ret;
   /* ss029.103: modification: the subscript should be of same type */
   SsIdx i;
   SsIdx idx;
   SsSTskEntry *sTsk;
	U32 tskInd = 0;


   TRC1(SDestroySTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate the system task ID */
   if (tskId >= SS_MAX_STSKS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS566, (ErrVal) tskId, "Invalid task ID");
      RETVALUE(RFAILED);
   }
#endif


   /* lock the system task table */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS567, (ErrVal) ret,
                     "Could not lock system task table");
#endif

      RETVALUE(RFAILED);
   }


   idx = (SsIdx) tskId;
   sTsk = &osCp.sTskTbl[idx];


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* 
    * check to see this system task exists and it is not already scheduled
    *  for termination 
    */
   if (sTsk->used != TRUE)
   {
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS568, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

      SSLOGERROR(ERRCLS_INT_PAR, ESS569, (ErrVal) idx,
                        "Invalid system task ID");
      RETVALUE(RFAILED);
   }
   else if (sTsk->termPend != FALSE)
   {
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS570, ERRZERO,
                       "Could not give the Semaphore");
           RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

      SSLOGERROR(ERRCLS_INT_PAR, ESS571, (ErrVal) idx,
                        "Invalid system task ID");
      RETVALUE(RFAILED);
   }
#endif


   /* lock this system task entry */
   if (!SS_CHECK_CUR_STSK(sTsk))
   {
      ret = SLock(&sTsk->lock);
      if (ret != ROK)
      {
#if 0  /* ss006.13: deletion */
         SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
         if ( SUnlock(&osCp.sTskTblLock) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
             SSLOGERROR(ERRCLS_DEBUG, ESS572, ERRZERO,
                       "Could not give the Semaphore");
             RETVALUE(RFAILED);
#endif
         }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS573, (ErrVal) ret,
                        "Could not lock system task entry");
#endif

         RETVALUE(RFAILED);
      }
   }

   /* lock the TAPA task table */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
      if (!SS_CHECK_CUR_STSK(sTsk))
      {
#if 0  /* ss006.13: deletion */
         SUnlock(&sTsk->lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
         if ( SUnlock(&sTsk->lock) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
             SSLOGERROR(ERRCLS_DEBUG, ESS574, ERRZERO,
                       "Could not give the Semaphore");
             RETVALUE(RFAILED);
#endif
         }
#endif  /* ss006.13: addition */
      }
#if 0  /* ss006.13: deletion */
         SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
         if ( SUnlock(&osCp.sTskTblLock) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
             SSLOGERROR(ERRCLS_DEBUG, ESS575, ERRZERO,
                       "Could not give the Semaphore");
             RETVALUE(RFAILED);
#endif
         }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS576, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


   /* If this system task entry has any TAPA tasks attached,
    *  we have to detach them
    */
   if (sTsk->numTTsks)
   {
      /* detach all TAPA tasks that are attached here */
      for (i = 0;  i < SS_MAX_TTSKS;  i++)
      {
         if (sTsk->tTsks[i] == SS_INVALID_IDX)
            continue;

         osCp.tTskTbl[sTsk->tTsks[i]].sTsk = NULLP;
         sTsk->tTsks[i] = SS_INVALID_IDX;
         sTsk->numTTsks--;
      }
   }


   /* set the termination pending flag to TRUE */
   sTsk->termPend = TRUE;


   /* unlock everything */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   if (!SS_CHECK_CUR_STSK(sTsk))
   {
#if 0  /* ss006.13: deletion */
      SUnlock(&sTsk->lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&sTsk->lock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS577, ERRZERO,
                       "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */
   }

#if 0  /* ss006.13: deletion */
   SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
        SSLOGERROR(ERRCLS_DEBUG, ESS578, ERRZERO,
                     "Could not give the Semaphore");
        RETVALUE(RFAILED);
#endif
    }
#endif  /* ss006.13: addition */


   /* We call this after unlocking because it is possible that the
    *  caller is this very system task and we need to take care of
    *  that. The actual mechanism of notifying the thread that it
    *  has to die, or actually killing the thread is left to the
    *  implementation.
    */
   ret = ssdDestroySTsk(sTsk);
   if (ret != ROK)
   {
      /* Here, we're a little messed up. We've pretty much made this
       *  system task unusable, but now, its not going to die. So..??
       */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS579, (ErrVal) ret,
                  "Could not destroy system task");
#endif

      RETVALUE(RFAILED);
   }
   
	/* multi-core support */
#ifdef SS_MULTICORE_SUPPORT

	/* Remove CPU affinity if any */
   for (tskInd = 0;  tskInd < SS_MAX_STSKS;  tskInd++)
   {
      if (osCp.sTskTbl[tskInd].tskId == sTsk->tskId)
      {
		   /* search for the tskId in coreInfo */
			U32 coreId = 0;
			for (coreId = 0; coreId < SS_MAX_CORES; coreId++)
			{
			  U32 thrId = 0;
			  for (thrId = 0; thrId < SS_MAX_THREADS_PER_CORE; thrId++)
			  {
			    if (sTsk->tskId == osCp.mCInfo.coreInfo[coreId].tskPerCoreLst[thrId])
				 {
               /* lock mCInfo */
	            SLock(&osCp.mCILock);

					/* increment the available threads */
					osCp.mCInfo.coreInfo[coreId].thrs++;

					/* reset the thread id */
					osCp.mCInfo.coreInfo[coreId].tskPerCoreLst[thrId] = 0;

					/* if exclusive flag is set then remove it */
					if (osCp.mCInfo.coreInfo[coreId].exclusive)
					{
					  osCp.mCInfo.coreInfo[coreId].exclusive = FALSE;
					} /* end if excl set */

               /* unlock mCInfo */
	            SUnlock(&osCp.mCILock);

					break;
				 } /* end if sTsk matched a thread */
			  } /* end for loop of thread Ids */
			} /* for */
         break;
      } /* end if */
   } /* end for */

#endif /* SS_MULTICORE_SUPPORT */
/* end multi-core support */

   /* ss019.103 - added to release semaphore for system task */
   if (ssPostSema(&osCp.dep.ssStarted) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
       SSLOGERROR(ERRCLS_DEBUG, ESS580, ERRZERO,
                         "Could not unlock the Semaphore");
       RETVALUE(RFAILED);
#endif
   }
   
   RETVALUE(ROK);
} /* SDestroySTsk */



/*
*
*       Fun:   Attach TAPA task
*
*       Desc:  This function is used to attach a TAPA task to a
*              system task. The system task will begin to execute
*              the TAPA task.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
/* ss029.103: addition: procId added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SAttachTTsk
(
Ent ent,                        /* entity ID of the task */
Inst inst,                      /* instance ID of the task */
SSTskId sTskId                  /* system task to use */
)
#else
PUBLIC S16 SAttachTTsk(ent, inst, sTskId)
Ent ent;                        /* entity ID of the task */
Inst inst;                      /* instance ID of the task */
SSTskId sTskId;                 /* system task to use */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SAttachTTsk
(
ProcId proc,                    /* processor ID of the task */
Ent ent,                        /* entity ID of the task */
Inst inst,                      /* instance ID of the task */
SSTskId sTskId                  /* system task to use */
)
#else
PUBLIC S16 SAttachTTsk(proc, ent, inst, sTskId)
ProcId proc;                    /* processor ID of the task */
Ent ent;                        /* entity ID of the task */
Inst inst;                      /* instance ID of the task */
SSTskId sTskId;                 /* system task to use */
#endif

#endif /* SS_MULTIPLE_PROCS */

{
   S16 ret;
   S16 i;
   SsIdx idx;
   SsSTskEntry *sTsk;
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   U16 procIdIdx;
#endif /* SS_MULTIPLE_PROCS */
#ifdef SSI_MEM_CHNG
   SsTTskEntry *tTsk;
#endif


   TRC1(SAttachTTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance range */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* check proc, entity and instance range */
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS581, ERRZERO, "Invalid processor/entity/instance");
      RETVALUE(RFAILED);
   }
#else /* SS_MULTIPLE_PROCS */
   /* check entity and instance range */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS582, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* check the system task index */
   if ((SsIdx)sTskId >= SS_MAX_STSKS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS583, (ErrVal) sTskId,
                  "Invalid system task ID");
      RETVALUE(RFAILED);
   }
#endif

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* get the proc id idx */
   procIdIdx = SGetProcIdIdx(proc);

   if (procIdIdx == SS_INV_PROCID)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS584, ERRZERO,
                             "Could not find proc id index");
#endif
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */

   /* lock the system task table */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS585, (ErrVal) ret,
                     "Could not lock system task table");
#endif

      RETVALUE(RFAILED);
   }


   sTsk = &osCp.sTskTbl[(SsIdx)sTskId];


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this system task exists */
   if (sTsk->used == FALSE)
   {
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS586, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

      SSLOGERROR(ERRCLS_INT_PAR, ESS587, (ErrVal) sTskId,
                     "Unknown system task ID");
      RETVALUE(RFAILED);
   }
#endif


   /* lock the system task entry */
   if (!SS_CHECK_CUR_STSK(sTsk))
   {
      ret = SLock(&sTsk->lock);
      if (ret != ROK)
      {
#if 0  /* ss006.13: deletion */
         SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
        if ( SUnlock(&osCp.sTskTblLock) != ROK)
        {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS588, ERRZERO,
                     "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
        }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS589, (ErrVal) ret,
                        "Could not lock system task entry");
#endif

         RETVALUE(RFAILED);
      }
   }


   /* if this system task is about to die, we don't attach */
   if (sTsk->termPend == TRUE)
   {
      if (!SS_CHECK_CUR_STSK(sTsk))
      {
#if 0  /* ss006.13: deletion */
         SUnlock(&sTsk->lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
        if ( SUnlock(&sTsk->lock) != ROK)
        {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS590, ERRZERO,
                     "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
        }
#endif  /* ss006.13: addition */
      }
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS591, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

      RETVALUE(RFAILED);
   }


   /* lock the TAPA task table */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
      if (!SS_CHECK_CUR_STSK(sTsk))
      {
#if 0  /* ss006.13: deletion */
         SUnlock(&sTsk->lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
        if ( SUnlock(&sTsk->lock) != ROK)
        {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS592, ERRZERO,
                     "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
        }
#endif  /* ss006.13: addition */
      }

#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS593, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS594, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


   /* get the index of the TAPA task entry in the table */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   idx = osCp.tTskIds[procIdIdx][ent][inst];
#else /* SS_MULTIPLE_PROCS */
   idx = osCp.tTskIds[ent][inst];
#endif /* SS_MULTIPLE_PROCS */

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check out the TAPA task ID */
   if (idx == SS_TSKNC)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      if (!SS_CHECK_CUR_STSK(sTsk))
      {
#if 0  /* ss006.13: deletion */
         SUnlock(&sTsk->lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
        if ( SUnlock(&sTsk->lock) != ROK)
        {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS595, ERRZERO,
                     "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
        }
#endif  /* ss006.13: addition */
      }
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS596, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

      SSLOGERROR(ERRCLS_INT_PAR, ESS597, ERRZERO, "Unknown task");
      RETVALUE(RFAILED);
   }
#endif


   /* verify that this TAPA task is not already attached */
   if (osCp.tTskTbl[idx].sTsk != NULLP)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      if (!SS_CHECK_CUR_STSK(sTsk))
      {
#if 0  /* ss006.13: deletion */
         SUnlock(&sTsk->lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
        if ( SUnlock(&sTsk->lock) != ROK)
        {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS598, ERRZERO,
                     "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
        }
#endif  /* ss006.13: addition */
      }
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS599, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

      RETVALUE(RFAILED);
   }


   /* verify that there is space for another TAPA task */
   if (sTsk->numTTsks == SS_MAX_TTSKS)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
      if (!SS_CHECK_CUR_STSK(sTsk))
      {
#if 0  /* ss006.13: deletion */
         SUnlock(&sTsk->lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
        if ( SUnlock(&sTsk->lock) != ROK)
        {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS600, ERRZERO,
                     "Could not give the Semaphore");
            RETVALUE(RFAILED);
#endif
        }
#endif  /* ss006.13: addition */
      }
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS601, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

      RETVALUE(ROUTRES);
   }


   /*  Find place for this TAPA task in the system task's list
    *  of TAPA tasks to run. Plug in this TAPA task.
    */
   for (i = 0;  i < SS_MAX_TTSKS;  i++)
   {
      if (sTsk->tTsks[i] == SS_INVALID_IDX)
      {
         sTsk->tTsks[i] = idx;
         sTsk->numTTsks++;
         break;
      }
   }


   /* Fill in the system task info in the TAPA task entry, so
    *  the TAPA task knows who's running it.
    */
   osCp.tTskTbl[idx].sTsk = sTsk;

#ifdef SSI_MEM_CHNG
   tTsk = &osCp.tTskTbl[idx];
   if(tTsk->initTsk != NULLP)
   {
       (Void)(tTsk->initTsk)(tTsk->ent, tTsk->inst, sTsk->region, PWR_UP);
   }
#endif /* SSI_MEM_CHNG */

   /* call the implementation to do anything implementation-specific */
   ret = ssdAttachTTsk(&osCp.tTskTbl[idx]);


   /* unlock the tables; we're done */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
   if (!SS_CHECK_CUR_STSK(sTsk))
   {
#if 0  /* ss006.13: deletion */
      SUnlock(&sTsk->lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&sTsk->lock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS602, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */
   }
#if 0  /* ss006.13: deletion */
   SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
        SSLOGERROR(ERRCLS_DEBUG, ESS603, ERRZERO,
                     "Could not give the Semaphore");
        RETVALUE(RFAILED);
#endif
   }
#endif  /* ss006.13: addition */


   /* If the implementation didn't succeed, we have to undo everything.
    *  We call SDetachTTsk, to make it easier.
    */
   if (ret != ROK)
   {
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
      SDetachTTsk(proc, ent, inst);
#else /* SS_MULTIPLE_PROCS */
      SDetachTTsk(ent, inst);
#endif /* SS_MULTIPLE_PROCS */
      RETVALUE(RFAILED);
   }


   RETVALUE(ROK);
} /* SAttachTTsk */


/*
*
*       Fun:   Detach TAPA task
*
*       Desc:  This function is used to detach a TAPA task from a
*              system task. The system task will stop executing
*              the TAPA task.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
/* ss029.103: addition: procId added */ 
#ifndef SS_MULTIPLE_PROCS

#ifdef ANSI
PUBLIC S16 SDetachTTsk
(
Ent ent,                        /* entity ID of the task */
Inst inst                       /* instance ID of the task */
)
#else
PUBLIC S16 SDetachTTsk(ent, inst)
Ent ent;                        /* entity ID of the task */
Inst inst;                      /* instance ID of the task */
#endif

#else /* SS_MULTIPLE_PROCS */

#ifdef ANSI
PUBLIC S16 SDetachTTsk
(
ProcId proc,                    /* processor ID of the task */
Ent ent,                        /* entity ID of the task */
Inst inst                       /* instance ID of the task */
)
#else
PUBLIC S16 SDetachTTsk(proc, ent, inst)
ProcId proc;                    /* processor ID of the task */
Ent ent;                        /* entity ID of the task */
Inst inst;                      /* instance ID of the task */
#endif

#endif /* SS_MULTIPLE_PROCS */

{
   S16 ret;
   S16 i;
   SsIdx idx;
   SsTTskEntry *tTsk;
   SsSTskEntry *sTsk;
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   U16 procIdIdx;
#endif /* SS_MULTIPLE_PROCS */

   TRC1(SDetachTTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance ranges */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* check entity and instance ranges */
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS604, ERRZERO, "Invalid processor/entity/instance");
      RETVALUE(RFAILED);
   }
#else /* SS_MULTIPLE_PROCS */
   /* check entity and instance ranges */
   if (ent >= SS_MAX_ENT ||  inst >= SS_MAX_INST)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS605, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */
#endif

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   /* get the proc id idx */
   procIdIdx = SGetProcIdIdx(proc);

   if (procIdIdx == SS_INV_PROCID)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS606, ERRZERO,
                             "Could not find proc id index");
#endif
      RETVALUE(RFAILED);
   }
#endif /* SS_MULTIPLE_PROCS */


   /* Lock the system task table. We do this to prevent
    *  the system task from being destroyed and confusing
    *  matters before we detach.
    */
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS607, (ErrVal) ret,
                     "Could not lock system task table");
#endif

      RETVALUE(RFAILED);
   }


   /* lock the TAPA task table */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
#if 0  /* ss006.13: deletion */
     SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
    if ( SUnlock(&osCp.sTskTblLock) != ROK)
    {
#if (ERRCLASS & ERRCLS_DEBUG)
        SSLOGERROR(ERRCLS_DEBUG, ESS608, ERRZERO,
                     "Could not give the Semaphore");
        RETVALUE(RFAILED);
#endif
    }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS609, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* Check this TAPA task. We do this with the TAPA task table
    *  locked, coz we don't want the task to be found, but then
    *  be deregistered before we lock
    */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if (osCp.tTskIds[procIdIdx][ent][inst] == SS_TSKNC)
#else /* SS_MULTIPLE_PROCS */
   if (osCp.tTskIds[ent][inst] == SS_TSKNC)
#endif /* SS_MULTIPLE_PROCS */
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
     if ( SUnlock(&osCp.sTskTblLock) != ROK)
     {
#if (ERRCLASS & ERRCLS_DEBUG)
        SSLOGERROR(ERRCLS_DEBUG, ESS610, ERRZERO,
                     "Could not give the Semaphore");
        RETVALUE(RFAILED);
#endif
     }
#endif  /* ss006.13: addition */

      SSLOGERROR(ERRCLS_INT_PAR, ESS611, ERRZERO, "Unknown task");
      RETVALUE(RFAILED);
   }
#endif

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   idx = osCp.tTskIds[procIdIdx][ent][inst];
#else /* SS_MULTIPLE_PROCS */
   idx = osCp.tTskIds[ent][inst];
#endif /* SS_MULTIPLE_PROCS */

   tTsk = &osCp.tTskTbl[idx];

   /* check if this TAPA task is attached to anyone */
   if (tTsk->sTsk == NULLP)
   {
      SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
     if ( SUnlock(&osCp.sTskTblLock) != ROK)
     {
#if (ERRCLASS & ERRCLS_DEBUG)
        SSLOGERROR(ERRCLS_DEBUG, ESS612, ERRZERO,
                     "Could not give the Semaphore");
        RETVALUE(RFAILED);
#endif
     }
#endif  /* ss006.13: addition */
      RETVALUE(ROK);
   }


   /* we get the system task entry out */
   sTsk = tTsk->sTsk;


   /* We unlock the TAPA task table here, and then re-lock it later
    *  because of lock sequencing--we have to lock the system task
    *  entry first, and then the TAPA task table. Note, the system
    *  task table is locked, so nobody can sneak in and destroy the
    *  system task while we're doing this.
    */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);


   /* lock the system task entry */
   if (!SS_CHECK_CUR_STSK(sTsk))
   {
      ret = SLock(&sTsk->lock);
      if (ret != ROK)
      {
#if 0  /* ss006.13: deletion */
         SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
       if ( SUnlock(&osCp.sTskTblLock) != ROK)
       {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS613, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
       }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS614, (ErrVal) ret,
                        "Could not lock system task entry");
#endif

         RETVALUE(RFAILED);
      }
   }


   /* now we lock the TAPA task table */
   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
#if 0  /* ss006.13: deletion */
      SUnlock(&sTsk->lock);
      SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&sTsk->lock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS615, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS616, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS617, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


   /* Now, we can safely update both the system task entry
    *  and the TAPA task entry. First, we update the TAPA
    *  task entry--nobody is running it now.
    */
   tTsk->sTsk = NULLP;


   /*  Remove this TAPA task from the system task's list of
    *  TAPA tasks to run.
    */
   for (i = 0;  i < SS_MAX_TTSKS;  i++)
   {
      if (sTsk->tTsks[i] == idx)
      {
         sTsk->tTsks[i] = SS_INVALID_IDX;
         sTsk->numTTsks--;
         break;
      }
   }


   /* call the implementation to do anything it needs to */
   ret = ssdDetachTTsk(tTsk);


   /* unlock the TAPA task table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   /* unlock the system task entry */
   if (!SS_CHECK_CUR_STSK(sTsk))
   {
#if 0  /* ss006.13: deletion */
      SUnlock(&sTsk->lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&sTsk->lock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS618, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */
   }

   /* unlock the system task table */
#if 0  /* ss006.13: deletion */
   SUnlock(&osCp.sTskTblLock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS619, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */


   /* If the implementation couldn't detach the task, we just
    *  return an error, nothing else we can do.
    */
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }


   RETVALUE(ROK);
} /* SDetachTTsk */


/*
*
*       Fun:   Post a message to a task
*
*       Desc:  This function is used to post a message to a TAPA
*              task. The message is delivered to the demand queue
*              of the system task that is running the specified
*              destination task.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_task.c
*
*/
#ifdef ANSI
PUBLIC S16 SPstTsk
(
Pst *pst,                       /* post information */
Buffer *mBuf                    /* message to post */
)
#else
PUBLIC S16 SPstTsk(pst, mBuf)
Pst *pst;                       /* post information */
Buffer *mBuf;                   /* message to post */
#endif
{
   S16 r;
   S16 i;
#if 0 /* ss001.13: change - old code */
   S16 j;
#else /* ss001.13: change - new code */
#if (defined(SS_DRVR_SUPPORT))
   S16 j;
#endif
#endif /* ss001.13: change */
   SsIdx dstIdx;
   SsIdx srcIdx;
   Prior prior;
   SsTTskEntry *tTsk;
   SsMsgInfo *msgInfo;
#if (defined(SS_DRVR_SUPPORT)  ||  defined(SS_RTR_SUPPORT))
   Pst nPst;
   Bool nPstUsed = FALSE;
#endif
#if (defined(SS_RTR_SUPPORT))
   Route rte;
#endif
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   U16 srcProcIdIdx;
   U16 dstProcIdIdx;
#endif /* SS_MULTIPLE_PROCS */


   TRC1(SPstTsk);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check the message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS620, ERRZERO, "Invalid message buffer");
      RETVALUE(RFAILED);
   }

   /* check the pst structure */
   if (pst == NULLP)
   {
      SPutMsg(mBuf);
      SSLOGERROR(ERRCLS_INT_PAR, ESS621, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Addition to check for valid route */
   /* ss023.103 - Modification to fix bug in route validation */
   /* check the route */
   if (pst->route == RTENC)
   {
      SPutMsg(mBuf);
      SSLOGERROR(ERRCLS_INT_PAR, ESS622, ERRZERO, "No route defined");
      RETVALUE(RFAILED);
   }
#endif


   /* lock the TAPA task table */
   SS_ACQUIRE_SEMA(&osCp.tTskTblSem, r);
   if (r != ROK)
   {
      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS623, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if (pst->srcProcId == SS_INV_PROCID || pst->srcEnt >= SS_MAX_ENT       ||
       pst->srcInst >= SS_MAX_INST     || pst->dstProcId == SS_INV_PROCID ||
       pst->dstEnt >= SS_MAX_ENT       ||  pst->dstInst >= SS_MAX_INST)
#else /* SS_MULTIPLE_PROCS */
   if (pst->srcEnt >= SS_MAX_ENT       ||  pst->srcInst >= SS_MAX_INST    ||
       pst->dstEnt >= SS_MAX_ENT       ||  pst->dstInst >= SS_MAX_INST)
#endif /* SS_MULTIPLE_PROCS */
   {
#if 0 /* ss006.13: deletion */
      SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1 /* ss006.13: addition */
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS624, ERRZERO,
                     "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: addition */

      SPutMsg(mBuf);

      SSLOGERROR(ERRCLS_INT_PAR, ESS625, ERRZERO,
                  "Invalid source/destination entity/instance");

      RETVALUE(RFAILED);
   }
#endif

   /* ss019.103 - modified for use with message router in virtual/physical
    * configuration */

#ifdef SS_RTR_SUPPORT
   /* check if we have a router task registered for this route */
   if (pst->route < RTENC  &&  osCp.rtrTskTbl[pst->route] != NULLP)
   {
      /* copy the Pst structure into a local duplicate */
      for (i = 0;  i < (S16)sizeof(Pst);  i++)
      {
         *(((U8 *)(&nPst)) + i) = *(((U8 *) pst) + i);
      }
      pst = &nPst;
      nPstUsed = TRUE;


      /* lock the router task entry */
      rte = pst->route;
      r = SLock(&osCp.rtrTskLocks[rte]);
      if (r != ROK)
      {
#if 0 /* ss006.13: deletion */
         SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1 /* ss006.13: addition */
         if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS626, ERRZERO,
                     "Could not release the semaphore");
            RETVALUE(RFAILED);
#endif
          }
#endif /* ss006.13: addition */
         SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS627, ERRZERO,
                     "Could not lock router task entry");
#endif

         RETVALUE(RFAILED);
      }

      /* call the router activation function */
      r = (*osCp.rtrTskTbl[rte])(pst, mBuf);

      /* unlock the router task entry */
#if 0  /* ss006.13: deletion */
      SUnlock(&osCp.rtrTskLocks[rte]);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if ( SUnlock(&osCp.rtrTskLocks[rte]) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
          SSLOGERROR(ERRCLS_DEBUG, ESS628, ERRZERO,
                     "Could not give the Semaphore");
          RETVALUE(RFAILED);
#endif
      }
#endif  /* ss006.13: addition */

      if (r == RFAILED  ||  r == ROKIGNORE)
      {
#if 0 /* ss006.13: deletion */
         SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1 /* ss006.13: addition */
         if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS629, ERRZERO,
                     "Could not release the semaphore");
            RETVALUE(RFAILED);
#endif
          }
#endif /* ss006.13: addition */
         RETVALUE((r == RFAILED) ? RFAILED : ROK);
      }
   }
#endif  /* SS_RTR_SUPPORT */

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS

   /* get proc id index */
   srcProcIdIdx = SGetProcIdIdx(pst->srcProcId);
   dstProcIdIdx = SGetProcIdIdx(pst->dstProcId);

   if (srcProcIdIdx != SS_INV_PROCID_IDX)
      srcIdx = osCp.tTskIds[srcProcIdIdx][pst->srcEnt][pst->srcInst];

   if (dstProcIdIdx != SS_INV_PROCID_IDX)
      dstIdx = osCp.tTskIds[dstProcIdIdx][pst->dstEnt][pst->dstInst];

   if (((srcProcIdIdx != SS_INV_PROCID_IDX) && (srcIdx == SS_TSKNC)) || 
       ((dstProcIdIdx != SS_INV_PROCID_IDX) && (dstIdx == SS_TSKNC)))
   {
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS630, ERRZERO,
                     "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
      }

      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS631, ERRZERO, "Unknown task");
#endif

      RETVALUE(RFAILED);
   }

#else /* SS_MULTIPLE_PROCS */
   /* ss019.103 - modified for use with message router in virtual/physical
    * configuration */

   /* get the src and destination task */
   srcIdx = osCp.tTskIds[pst->srcEnt][pst->srcInst];
   dstIdx = osCp.tTskIds[pst->dstEnt][pst->dstInst];


   /* If the source/destination processor ID is local, the
    *  source/destination TAPA task must be local.
    */
   if ((pst->srcProcId == osCp.procId  &&  srcIdx == SS_TSKNC) 
      ||  (pst->dstProcId == osCp.procId  &&  dstIdx == SS_TSKNC))
   {
#if 0 /* ss006.13: deletion */
      SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1 /* ss006.13: addition */
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS632, ERRZERO,
                     "Could not release the semaphore");
      RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: addition */
      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS633, ERRZERO, "Unknown task");
#endif

      RETVALUE(RFAILED);
   }

#endif /* SS_MULTIPLE_PROCS */

#ifdef SS_DRVR_SUPPORT
   /* Check for the destination procId. If it is non-local,
    *  we need to find the driver task that will handle this
    *  message.
    */
/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
   if (dstProcIdIdx == SS_INV_PROCID_IDX)
#else /* SS_MULTIPLE_PROCS */
   if (pst->dstProcId != osCp.procId)
#endif /* SS_MULTIPLE_PROCS */
   {
      /*  Need to optimize this search.
       */
      for (i = 0;  i < SS_MAX_DRVRTSKS;  i++)
      {
         if (osCp.drvrTskTbl[i].used
               &&  pst->dstProcId >= osCp.drvrTskTbl[i].low
               &&  pst->dstProcId <= osCp.drvrTskTbl[i].high)
         {
            /* Copy the Pst structure into a local duplicate if not
             *  already done.
             */
            if (!nPstUsed)
            {
               for (j = 0;  j < (S16)sizeof(Pst);  j++)
               {
                  *(((U8 *)(&nPst)) + j) = *(((U8 *) pst) + j);
               }
               pst = &nPst;
               nPstUsed = TRUE;
            }


            /* lock the driver task entry */
            r = SLock(&osCp.drvrTskTbl[i].lock);
            if (r != ROK)
            {
#if 0 /* ss006.13: deletion */
               SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1 /* ss006.13: addition */
               if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
               {
#if (ERRCLASS & ERRCLS_DEBUG)
                  SSLOGERROR(ERRCLS_DEBUG, ESS634, ERRZERO,
                     "Could not release the semaphore");
                  RETVALUE(RFAILED);
#endif
               }
#endif /* ss006.13: addition */
               SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
               SSLOGERROR(ERRCLS_DEBUG, ESS635, ERRZERO,
                           "Could not lock driver task entry");
#endif

               RETVALUE(RFAILED);
            }

            CMCHKPKLOG(cmPkInst, osCp.drvrTskTbl[i].channel, mBuf, ESS636, pst);

            (osCp.drvrTskTbl[i].actvTsk)(pst, mBuf);

            /* unlock */
#if 0  /* ss006.13: deletion */
            SUnlock(&osCp.drvrTskTbl[i].lock);
#endif  /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
            if ( SUnlock(&osCp.drvrTskTbl[i].lock) != ROK)
            {
#if (ERRCLASS & ERRCLS_DEBUG)
              SSLOGERROR(ERRCLS_DEBUG, ESS637, ERRZERO,
                     "Could not give the Semaphore");
              RETVALUE(RFAILED);
#endif
            }
#endif  /* ss006.13: addition */
#if 0 /* ss006.13: deletion */
            SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1 /* ss006.13: addition */
            if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
            {
#if (ERRCLASS & ERRCLS_DEBUG)
               SSLOGERROR(ERRCLS_DEBUG, ESS638, ERRZERO,
                     "Could not release the semaphore");
               RETVALUE(RFAILED);
#endif
            }
#endif /* ss006.13: addition */
            RETVALUE(ROK);
         }
      }

#if 0 /* ss006.13: deletion */
      SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1 /* ss006.13: addition */
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS639, ERRZERO,
                     "Could not release the semaphore");
            RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: addition */
      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS640, ERRZERO,
                  "Could not find a driver task to handle this proc ID");
#endif

      RETVALUE(RFAILED);
   }
#endif  /* SS_DRVR_SUPPORT */


   /* plug the Pst structure into the message information portion */
   msgInfo = (SsMsgInfo *) (mBuf->b_rptr);
   for (i = 0;  i < (S16 )sizeof(Pst);  i++)
      *(((U8 *)(&msgInfo->pst)) + i) = *(((U8 *) pst) + i);


   /*  Write the message to the demand queue of the system
    *  task which is running the destination task
    */
   tTsk = &osCp.tTskTbl[dstIdx];
   prior = tTsk->tskPrior;

   if (tTsk->sTsk == NULLP)
   {
#if 0 /* ss006.13: deletion */
      SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1 /* ss006.13: addition */
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS641, ERRZERO,
                     "Could not release the semaphore");
            RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: addition */
      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS642, (ErrVal) 0,
                 "Destination TAPA task is not attached");
#endif

      RETVALUE(RFAILED);
   }

   r = ssDmndQPutLast(&tTsk->sTsk->dQ, mBuf,
                           ((prior * SS_MAX_MSG_PRI) + pst->prior));
   if (r != ROK)
   {
#if 0 /* ss006.13: deletion */
      SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1 /* ss006.13: addition */
      if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
           SSLOGERROR(ERRCLS_DEBUG, ESS643, ERRZERO,
                     "Could not release the semaphore");
            RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: addition */
      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_ADD_RES)
      SSLOGERROR(ERRCLS_ADD_RES, ESS644, (ErrVal) r,
                     "Could not write to demand queue");
#endif

      RETVALUE(RFAILED);
   }


   /* unlock, we're done */
#if 0 /* ss006.13: deletion */
   SS_RELEASE_SEMA(&osCp.tTskTblSem);
#endif /* ss006.13: deletion */
#if 1 /* ss006.13: addition */
   if ( SS_RELEASE_SEMA(&osCp.tTskTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
        SSLOGERROR(ERRCLS_DEBUG, ESS645, ERRZERO,
                  "Could not release the semaphore");
        RETVALUE(RFAILED);
#endif
   }
#endif /* ss006.13: addition */


   /* If the implementation has anything to do... note that
    *  we call it unlocked at this time.
    */
   ssdPstTsk(pst, mBuf, tTsk);


   RETVALUE(ROK);
} /* SPstTsk */


/********************************************************************30**
  
         End of file:     ss_task.c@@/main/2 - Mon Apr  5 18:01:20 2010
  
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

1.2          ---      ag   1. Added ssdPstTsk() function in SPstTsk
             ---      ag   2. Fixed a bug in function SPstTsk
             ---      bsr  3. moved code from ssdDeregInitTskTmr to 
                              SDeregInitTskTmr.
             ---      bsr  4. Added timer deregistration to SDeregTTsk
             ---      bsr  5. Added a check in SPstTsk to see if the
                              destination tapa task is attached to a
                              system task.
             ---      bsr  6. packed channel id into mBuf instead
                              of passing it via route field in post
                              strucure before calling DrvrActvTsk
             ---      kp   7. Fixed bug in SDeregInitTskTmr
             ---      kp   8. Fixed bug in SDeregTTsk
             ---      kp   9. Changed parameters for ssdPstTsk
             ---      kp   9. Cosmetic changes

1.3          ---      kp   1. Added in Message Router support

1.3+         ss001.13 kp   1. Compile warning removed.
1.3+         ss006.13 jn   2. Compile warning "Value computed
                              is not used" removed for
                              SUnlock and SS_RELEASE_SEMA.
1.3+         ss019.103 bp   3. Modification for Message Router support
                              Addition of release of system task semaphore
1.3+         ss021.103 bjp  4. Return fail if invalid task type in SRegActvTsk
                                  and SRegTTsk
                               Check for valid route in SPstTsk
			       Modify SRegInit and SRegActvTsk
             ss023.103 bjp  5. Bug fix in validation of route for SPstTsk\
	     ss024.103 bjp  6. Modifications for memory calculator tool 
1.3+         ss025.103 7. Added locks around counting semaphores
1.3+    ss029.103     kkj   1. Multiple proc ids support added
1.3+         ss032.103 kkj  1. Changes for calling the init function while
                               deregistering the TAPA task
/main/4      ---       rp   1. SSI enhancements for Multi-core architecture
                               support
*********************************************************************91*/
