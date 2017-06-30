

/********************************************************************20**
 
     Name:     System Services -- general functions
 
     Type:     C source file
 
     Desc:     Source code for System Services startup and general
               System Services.
 
     File:     ss_gen.c
 
     Sid:      sm_gen.c@@/main/1 - Mon Apr  5 18:01:10 2010
 
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



/* public variable declarations */

PUBLIC SsOs     osCp;           /* common OS control point */

 
EXTERN Cntr     cfgNumRegs;
EXTERN SsRegCfg cfgRegInfo[SS_MAX_REGS];


/* ss029.103: modification: multiple procId related changes */ 
#ifdef SS_MULTIPLE_PROCS
/* PRIVATE functions */
PRIVATE S16 SInsProcId ARGS((ProcId proc));
PRIVATE S16 SRemProcId ARGS((ProcId proc));
PRIVATE S16 SLockOsCp  ARGS((Void));
PRIVATE S16 SULockOsCp ARGS((Void));
#endif /* SS_MULTIPLE_PROCS */


/*
*
*       Fun:   System Services initialization function
*
*       Desc:  This is the general initialization function for
*              all System Services implementations. It initializes
*              all the common global data structures and calls the
*              implementation-specific initialization and start
*              functions.
*
*       Ret:   Void
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SInit
(
void
)
#else
PUBLIC S16 SInit()
#endif
{
   S16 ret;
   REG1 S16 i;
   REG2 S16 j;
   REG3 S16 k;
   SsTTskEntry *tTsk;
   SsSTskEntry *sTsk;
   SsTmrEntry *tmr;
   SsRegionEntry *reg;
#ifdef SS_DRVR_SUPPORT
   SsDrvrTskEntry *drvrTsk;
#endif
   
   TRC1(SInit);
 
   /* ss019.103 - Modified for correct initialization of OS control point */
   /* start initializing OS control point */
/* ss029.103: modification: multiple procId related changes */ 
#ifndef SS_MULTIPLE_PROCS
   osCp.procId = SS_PROC_ID;
#else /* SS_MULTIPLE_PROCS */
   for (i = 0; i < SS_MAX_PROCS; i++)
      osCp.procLst.procId[i] = PROCNC;

   osCp.procLst.free = SS_MAX_PROCS;
#endif /* SS_MULTIPLE_PROCS */

   /* implementation specific general initialization */
   ret = ssdInitGen();
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }

   /* initialize memory information */
   osCp.numRegions = 0;

   for (i = 0;  i < SS_MAX_REGS;  i++)
   {
      reg = &osCp.regionTbl[i];

      reg->used = FALSE;

      reg->start = NULLP;
      reg->size = 0;
      reg->regCb = NULLP;
      reg->flags = 0;
      reg->alloc = NULLP;
      reg->free = NULLP;
      reg->ctl = NULLP;

      /* zero the pool information */
      reg->numPools = 0;
      for (j = 0;  j < SS_MAX_POOLS_PER_REG;  j++)
         reg->poolTbl[j].type = SS_POOL_UND;

      /* find this region ID in the region configuration structure */
      for (j = 0;  j < cfgNumRegs;  j++)
         if (cfgRegInfo[j].region == i)
            break;

      /* this region is not configured */
      if (j == cfgNumRegs)
         continue;

      /* Load the configuration information into the region table.
       *  Note, the region still has to be registered, for it to
       *  be usable.
       */
      for (k = 0;  k < cfgRegInfo[j].numPools;  k++)
      {
         reg->poolTbl[k].type = cfgRegInfo[j].pools[k].type;
         if (reg->poolTbl[k].type == SS_POOL_DYNAMIC)
            reg->poolTbl[k].u.dpool.size = cfgRegInfo[j].pools[k].size;
      }
   }

   ret = ssInitSema(&osCp.regionTblSem, SS_MAX_STSKS);
   if (ret != ROK)
   {
      goto cleanup1;
   }

   /* implementation specific memory initialization */
   ret = ssdInitMem();
   if (ret != ROK)
   {

/* ss006.13: addition */
      if ( (ssDestroySema(&osCp.regionTblSem)) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS009, ERRZERO,
                         "Could not destroy the Semaphore");
         RETVALUE(RFAILED);
#endif
      }
      goto cleanup1;
   }


   /* initialize TAPA and system task information */
/* ss029.103: modification: multiple procId related changes */ 
#ifndef SS_MULTIPLE_PROCS
   for (i = 0;  i < SS_MAX_ENT;  i++)
      for (j = 0;  j < SS_MAX_INST;  j++)
         osCp.tTskIds[i][j] = SS_TSKNC;
#else /* SS_MULTIPLE_PROCS */
   for (i = 0;  i < SS_MAX_PROCS;  i++)
      for (j = 0;  j < SS_MAX_ENT;  j++)
         for (k = 0;  k < SS_MAX_INST;  k++)
            osCp.tTskIds[i][j][k] = SS_TSKNC;
#endif /* SS_MULTIPLE_PROCS */

   for (i = 0;  i < SS_MAX_TTSKS;  i++)
   {
      tTsk = &osCp.tTskTbl[i];

      tTsk->used = FALSE;
      tTsk->ent = ENTNC;
      tTsk->inst = INSTNC;
      tTsk->tskType = TTUND;
      tTsk->tskPrior = 0;
      tTsk->initTsk = NULLP;
      tTsk->actvTsk = NULLP;
      tTsk->sTsk = NULLP;
/* ss029.103: addition: TAPA task control block added */
#ifdef SS_MULTIPLE_PROCS
      tTsk->xxCb = NULLP;
#endif /* SS_MULTIPLE_PROCS */

      tTsk->nxt = i + 1;
   }

   osCp.numTTsks = 0;
   osCp.nxtTTskEntry = 0;

   ret = ssInitSema(&osCp.tTskTblSem, SS_MAX_STSKS);
   if (ret != ROK)
   {
      goto cleanup2;
   }


   /* initialize system task information */
   for (i = 0;  i < SS_MAX_STSKS;  i++)
   {
      sTsk = &osCp.sTskTbl[i];

      sTsk->used = FALSE;
      sTsk->termPend = FALSE;
      sTsk->tskPrior = 0;
      for (j = 0;  j < SS_MAX_TTSKS;  j++)
         sTsk->tTsks[j] = SS_INVALID_IDX;
      sTsk->numTTsks = 0;

      sTsk->nxt = i + 1;
   }

   osCp.numSTsks = 0;
   osCp.nxtSTskEntry = 0;

   ret = SInitLock(&osCp.sTskTblLock, SS_STSKTBL_LOCK);
   if (ret != ROK)
   {
/* ss006.13: addition */
      if ( (ssDestroySema(&osCp.tTskTblSem)) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS010, ERRZERO,
                         "Could not destroy the Semaphore");
         RETVALUE(RFAILED);

#endif
      }
      goto cleanup2;
   }

   /* ss028.103 - Addition of lock for mBuf reference count */
   SInitLock(&osCp.mBufRefLock, SS_LOCK_MUTEX);

   /* implementation specific task initialization */
   ret = ssdInitTsk();
   if (ret != ROK)
   {
      SDestroyLock(&osCp.sTskTblLock);
/* ss006.13: addition */
      if ( (ssDestroySema(&osCp.tTskTblSem)) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS011, ERRZERO,
                         "Could not destroy the Semaphore");
         RETVALUE(RFAILED);

#endif
      }
      goto cleanup2;
   }

#ifdef SS_DRVR_SUPPORT
   /* initialize driver task information */
   for (i = 0;  i < SS_MAX_DRVRTSKS;  i++)
   {
      drvrTsk = &osCp.drvrTskTbl[i];

      drvrTsk->used = FALSE;

      drvrTsk->channel = 0;
      drvrTsk->actvTsk = NULLP;
      drvrTsk->isTsk = NULLP;
      drvrTsk->low = 0;
      drvrTsk->high = 0;
   }

   osCp.numDrvrTsks = 0;

   /* implementation specific driver initialization */
   ret = ssdInitDrvr();
   if (ret != ROK)
   {
      goto cleanup3;
   }
#endif


   /* initialize the demand queue lookup table */
   osCp.dmndQLookupTbl[0] = 255;
   osCp.dmndQLookupTbl[1] = 0;
   osCp.dmndQLookupTbl[2] = 1;
   osCp.dmndQLookupTbl[3] = 1;
   for (i = 4;  i < 256;  i++)
   {
      if (i >= 128  &&  i <= 255)
         osCp.dmndQLookupTbl[i] = 7;
      if (i >= 64  &&  i <= 127)
         osCp.dmndQLookupTbl[i] = 6;
      if (i >= 32  &&  i <= 63)
         osCp.dmndQLookupTbl[i] = 5;
      if (i >= 16  &&  i <= 31)
         osCp.dmndQLookupTbl[i] = 4;
      if (i >= 8  &&  i <= 15)
         osCp.dmndQLookupTbl[i] = 3;
      if (i >= 4  &&  i <= 7)
         osCp.dmndQLookupTbl[i] = 2;
   }


   /* initialize timer information */
   for (i = 0;  i < SS_MAX_TMRS;  i++)
   {
      tmr = &osCp.tmrTbl[i];

      tmr->used = FALSE;
      tmr->tmrId = 0;
      tmr->ownerEnt = ENTNC;
      tmr->ownerInst = INSTNC;
      tmr->interval = 0;
      tmr->tmrActvFn = NULLP;

      tmr->nxt = i + 1;
   }

   osCp.numTmrs = 0;
   osCp.nxtTmrEntry = 0;

   ret = SInitLock(&osCp.tmrTblLock, SS_TMRTBL_LOCK);
   if (ret != ROK)
   {
      goto cleanup4;
   }

   /* implementation specific timer initialization */
   ret = ssdInitTmr();
   if (ret != ROK)
   {
      SDestroyLock(&osCp.tmrTblLock);
      goto cleanup4;
   }


   /* implementation specific final initialization */
   ret = ssdInitFinal();
   if (ret != ROK)
   {
      goto cleanup5;
   }


   /* call tst() function */
   ret = tst();
   if (ret != ROK)
   {
      goto cleanup6;
   }


   /* call implementation-specific starter function */
   ssdStart();


   RETVALUE(ROK);


   /* clean up code */
cleanup6:
   ssdDeinitFinal();

cleanup5:
   ssdDeinitTmr();
   SDestroyLock(&osCp.tmrTblLock);

cleanup4:
#ifdef SS_DRVR_SUPPORT
   ssdDeinitDrvr();

cleanup3:
#endif
   ssdDeinitTsk();
   SDestroyLock(&osCp.sTskTblLock);
/* ss006.13: addition */
      if ( (ssDestroySema(&osCp.tTskTblSem)) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS012, ERRZERO,
                         "Could not destroy the Semaphore");
         RETVALUE(RFAILED);

#endif
      }

cleanup2:
   ssdDeinitMem();
/* ss006.13: addition */
      if ( (ssDestroySema(&osCp.regionTblSem)) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS013, ERRZERO,
                         "Could not destroy the Semaphore");
         RETVALUE(RFAILED);

#endif
      }

cleanup1:
   ssdDeinitGen();


   RETVALUE(RFAILED);
}


/* ss033.103: Added SDeInit API to free all the resources */
/*
*
*       Fun:   System Services de-initialization function
*
*       Desc:  This is the de-initialization function for System 
*              Services implementations. It releases all the common
*              global data structures.
*
*       Ret:   Void
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SDeInit
(
void
)
#else
PUBLIC S16 SDeInit()
#endif
{

   TRC1(SDeInit);

   ssdDeinitFinal();

   ssdDeinitTmr();
   SDestroyLock(&osCp.tmrTblLock);

#ifdef SS_DRVR_SUPPORT
   ssdDeinitDrvr();
#endif

   ssdDeinitTsk();
   SDestroyLock(&osCp.sTskTblLock);

   if ((ssDestroySema(&osCp.tTskTblSem)) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
    SSLOGERROR(ERRCLS_DEBUG, ESS014, ERRZERO,
                      "Could not destroy the Semaphore");
    RETVALUE(RFAILED);

#endif
   }

   ssdDeinitMem();

   if ((ssDestroySema(&osCp.regionTblSem)) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS015, ERRZERO,
                      "Could not destroy the Semaphore");
      RETVALUE(RFAILED);

#endif
   }

   ssdDeinitGen();
   RETVALUE(ROK);

}


/*
*
*       Fun:   SPrint
*
*       Desc:  Print a string.
*
*              This function should be used for debugging only.
*
*       Ret:   ROK      - ok
*
*       Notes: Text buffer should be null terminated.
*
*              SDisplay will replace SPrint.
*
*              Typical usage consists of a call to sprintf to
*              format the string into a buffer followed by a
*              call to SPrint
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SPrint
(
Txt *buf                        /* buffer */
)
#else
PUBLIC S16 SPrint(buf)
Txt *buf;                       /* buffer */
#endif
{
   TRC1(SPrint);

   SDisplay(0, buf);

   RETVALUE(ROK);

} /* end of SPrint */


/*
*
*       Fun:   SError
*
*       Desc:  Invoked by layer when an unrecoverable
*              software error is detected. This function should
*              never return.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SError
(
Seq seq,                    /* sequence */
Reason reason               /* reason */
)
#else
PUBLIC S16 SError(seq, reason)
Seq seq;                    /* sequence */
Reason reason;              /* reason */
#endif
{
   S16 ret;
   DateTime dt;
   Txt errBuf[256];


   TRC1(SError);


   SGetDateTime(&dt);
   sprintf(errBuf, "\n\ndate: %02d/%02d/%04d time: %02d:%02d:%02d\n",
          (int)dt.month,(int)dt.day,(int)dt.year + 1900,
          (int)dt.hour,(int)dt.min,(int)dt.sec);
   SPrint(errBuf);


   ret = ssdError(seq, reason);


   RETVALUE(ret);
}


/*
*
*       Fun:   SLogError
*
*       Desc:  Invoked by layer to log an error.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC Void SLogError
(
Ent ent,                    /* Calling layer's entity id */
Inst inst,                  /* Calling layer's instance id */
ProcId procId,              /* Calling layer's processor id */
Txt *file,                  /* file name where error occured */
S32 line,                   /* line in file where error occured */
ErrCls errCls,              /* error class */
ErrCode errCode,            /* layer unique error code */
ErrVal errVal,              /* error value */
Txt *errDesc                /* description of error */
)
#else
PUBLIC Void SLogError(ent, inst, procId, file, line,
                        errCls, errCode, errVal, errDesc)
Ent ent;                    /* Calling layer's entity id */
Inst inst;                  /* Calling layer's instance id */
ProcId procId;              /* Calling layer's processor id */
Txt *file;                  /* file name where error occured */
S32 line;                   /* line in file where error occured */
ErrCls errCls;              /* error class */
ErrCode errCode;            /* layer unique error code */
ErrVal errVal;              /* error value */
Txt *errDesc;               /* description of error */
#endif
{
   DateTime dt;
   Txt errBuf[512];


   TRC1(SLogError);


   SGetDateTime(&dt);
   sprintf(errBuf, "\n\ndate: %02d/%02d/%04d time: %02d:%02d:%02d\n",
          (int)dt.month,(int)dt.day,(int)dt.year + 1900,
          (int)dt.hour,(int)dt.min,(int)dt.sec);
   SDisplay(0,errBuf);


   ssdLogError(ent, inst, procId, file, line,
                     errCls, errCode, errVal, errDesc);


   RETVOID;
}

/* ss029.103: modification: 
   SFndProcId function is not supported with multiple procIds */ 
#ifndef SS_MULTIPLE_PROCS

/*
*
*       Fun:   SFndProcId
*
*       Desc:  This function finds the local processor ID.
*
*       Ret:   local processor id
*
*       Notes:
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC ProcId SFndProcId
(
void
)
#else
PUBLIC ProcId SFndProcId()
#endif
{
   TRC1(SFndProcId);

   RETVALUE(osCp.procId);
} /* end of SFndProcId */


/*
*
*       Fun:   SSetProcId
*
*       Desc:  This function stores the local processor ID.
*
*       Ret:   Void
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC Void SSetProcId
(
ProcId procId
)
#else
PUBLIC Void SSetProcId(procId)
ProcId procId;
#endif
{
   TRC1(SSetProcId);

   osCp.procId = procId;

   RETVOID;
}

#endif /* SS_MULTIPLE_PROCS */

/* ss029.103: addition: New SSI functions with multiple proc support */ 
#ifdef SS_MULTIPLE_PROCS

/*
*
*       Fun:   SGetProcIdIdx
*
*       Desc:  This function finds index of procId in the process id table 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC U16 SGetProcIdIdx
(
ProcId proc
)
#else
PUBLIC U16 SGetProcIdIdx(proc)
ProcId proc; 
#endif
{
   U16 i;
   U16 idx;

   TRC1(SGetProcIdIdx);

   idx = SS_HASH_IDX(proc);

   for (i = idx; i < SS_MAX_PROCS; i++)
      if (osCp.procLst.procId[i] == proc)
         return i;

   /* search upto idx */
   for (i = 0; i < idx; i++)
      if (osCp.procLst.procId[i] == proc)
         return i;

   RETVALUE(SS_INV_PROCID_IDX);
} /* SGetProcIdIdx */


/*
*
*       Fun:   SInsProcId
*
*       Desc:  This function inserts procId in the process id table 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PRIVATE S16 SInsProcId
(
ProcId proc
)
#else
PRIVATE S16 SInsProcId(proc)
ProcId proc; 
#endif
{
   U16 i;
   U16 idx;

   TRC1(SInsProcId);

   idx = SS_HASH_IDX(proc);

   for (i = idx; i < SS_MAX_PROCS; i++)
      if (osCp.procLst.procId[i] == SS_INV_PROCID)
      {
         osCp.procLst.procId[i] = proc;
         osCp.procLst.free--;
         RETVALUE(ROK);
      }

   /* search for free entry upto idx */
   for (i = 0; i < idx; i++)
      if (osCp.procLst.procId[i] == SS_INV_PROCID)
      {
         osCp.procLst.procId[i] = proc;
         osCp.procLst.free--;
         RETVALUE(ROK);
      }

   RETVALUE(RFAILED);
} /* SInsProcId */


/*
*
*       Fun:   SRemProcId
*
*       Desc:  This function inserts procId in the process id table 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PRIVATE S16 SRemProcId
(
ProcId proc
)
#else
PRIVATE S16 SRemProcId(proc)
ProcId proc; 
#endif
{
   U16 i;
   U16 idx;

   TRC1(SRemProcId);

   idx = SS_HASH_IDX(proc);

   for (i = idx; i < SS_MAX_PROCS; i++)
      if (osCp.procLst.procId[i] == proc)
      {
         osCp.procLst.procId[i] = SS_INV_PROCID;
         osCp.procLst.free++;
         RETVALUE(ROK);
      }

   /* search upto idx */
   for (i = 0; i < idx; i++)
      if (osCp.procLst.procId[i] == proc)
      {
         osCp.procLst.procId[i] = SS_INV_PROCID;
         osCp.procLst.free++;
         RETVALUE(ROK);
      }

   RETVALUE(RFAILED);
} /* SRemProcId */


/*
*
*       Fun:   SLockOsCp
*
*       Desc:  This function locks OsCp 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PRIVATE S16 SLockOsCp
(
Void
)
#else
PRIVATE S16 SLockOsCp(Void)
#endif
{
   S16 ret;

   TRC1(SLockOsCp);

   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS016, ERRZERO,
                     "Could not lock system task table");
      RETVALUE(RFAILED);
   }

   SS_ACQUIRE_ALL_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS017, ERRZERO,
                     "Could not lock TAPA task table");
#endif

      if ( SUnlock(&osCp.sTskTblLock) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS018, ERRZERO,
                      "Could not give the Semaphore");
         RETVALUE(RFAILED);
#endif
      }

      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);

} /* SLockOsCp */


/*
*
*       Fun:   SULockOsCp
*
*       Desc:  This function locks OsCp 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PRIVATE S16 SULockOsCp
(
Void
)
#else
PRIVATE S16 SULockOsCp(Void)
#endif
{
   TRC1(SULockOsCp);

   /* unlock the table */
   SS_RELEASE_ALL_SEMA(&osCp.tTskTblSem);

   if ( SUnlock(&osCp.sTskTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS019, ERRZERO,
                      "Could not give the Semaphore");
      RETVALUE(RFAILED);
#endif
   }

   RETVALUE(ROK);

} /* SULockOsCp */



/*
*
*       Fun:   SAddProcIdLst
*
*       Desc:  This function adds given proc ids to the list 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SAddProcIdLst
(
U16 numPIds,
ProcId *pIdLst
)
#else
PUBLIC S16 SAddProcIdLst(numPIds, pIdLst)
U16 numPIds;
ProcId *pIdLst;
#endif
{
   U16 i;
   S16 ret;

   TRC1(SAddProcIdLst);

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* range check */
   if (numPIds > SS_MAX_PROCS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS020, ERRZERO, "number of proc Ids exceeds\
 limit");
      RETVALUE(RFAILED);
   }

   /* find if the entry exist in the table */
   for (i = 0; i < numPIds; i++)
   {
      if (pIdLst[i] == SS_INV_PROCID)
      {
         SSLOGERROR(ERRCLS_INT_PAR, ESS021, ERRZERO, "Invalid proc Ids");
         RETVALUE(RFAILED);
      }
   }

#endif
   
   if (SLockOsCp() != ROK)
      RETVALUE(RFAILED);

#if (ERRCLASS & ERRCLS_INT_PAR)
   for (i = 0; i < numPIds; i++)
      if (SGetProcIdIdx(pIdLst[i]) != SS_INV_PROCID_IDX)
      {
         SSLOGERROR(ERRCLS_INT_PAR, ESS022, ERRZERO, "Duplicate proc id");
         (Void) SULockOsCp();
         RETVALUE(RFAILED);
      }

   if (numPIds > osCp.procLst.free)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS023, ERRZERO, "Total number of proc id \
exceeds");
      (Void) SULockOsCp();
      RETVALUE(RFAILED);
   }
#endif 

   /* insert the entries in the table */
   ret = ROK;

   for (i = 0; i < numPIds; i++)
   {
      if (SInsProcId(pIdLst[i]) == RFAILED)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS024, ERRZERO,
                      "Could not insert the proc id");
#endif
         (Void) SULockOsCp();
         RETVALUE(RFAILED);
      }
   }

   /* unlock the table */
   if (SULockOsCp() != ROK)
      RETVALUE(RFAILED);

   RETVALUE(ret);
} /* SAddProcIdLst */


/*
*
*       Fun:   SRemProcIdLst
*
*       Desc:  This function adds given proc ids to the list 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SRemProcIdLst
(
U16 numPIds,
ProcId *pIdLst
)
#else
PUBLIC S16 SRemProcIdLst(numPIds, pIdLst)
U16 numPIds;
ProcId *pIdLst;
#endif
{
   U16 i;

   TRC1(SRemProcIdLst);

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* range check */
   if (numPIds > SS_MAX_PROCS)
      RETVALUE(RFAILED);
#endif

   if (SLockOsCp() != ROK)
      RETVALUE(RFAILED);

   if (numPIds > (SS_MAX_PROCS - osCp.procLst.free))
   {
      (Void) SULockOsCp();
      RETVALUE(RFAILED);
   }

   /* find if the entry exist in the table */
   for (i = 0; i < numPIds; i++)
   {
      if (SGetProcIdIdx(pIdLst[i]) == SS_INV_PROCID_IDX)
      {
         (Void) SULockOsCp();
         RETVALUE(RFAILED);
      }
   }

   /* insert the entries in the table */
   for (i = 0; i < numPIds; i++)
      SRemProcId(pIdLst[i]);

   if (SULockOsCp() != ROK)
      RETVALUE(RFAILED);

   RETVALUE(ROK);
} /* SRemProcIdLst */


/*
*
*       Fun:   SGetProcIdLst
*
*       Desc:  This function retrieves proc Id list 
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetProcIdLst
(
U16 *numPIds,
ProcId *pIdLst
)
#else
PUBLIC S16 SGetProcIdLst(numPIds, pIdLst)
U16 *numPIds;
ProcId *pIdLst;
#endif
{
   U16 i;
   U16 count = 0;

   TRC1(SGetProcIdLst);

#if (ERRCLASS & ERRCLS_INT_PAR)
   if ((numPIds == NULLP) || (pIdLst == NULLP))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS025, ERRZERO, "Invalid numPIds/pIdLst");
      RETVALUE(RFAILED);
   }
#endif 

   if (SLockOsCp() != ROK)
      RETVALUE(RFAILED);

   for (i = 0; i < SS_MAX_PROCS; i++)
   {
      if (osCp.procLst.procId[i] != PROCNC)
         pIdLst[count++] = osCp.procLst.procId[i];
   }

   *numPIds = count;

   if (SULockOsCp() != ROK)
      RETVALUE(RFAILED);

   if (count == 0)
      RETVALUE(RFAILED);

   RETVALUE(ROK);
} /* SGetProcIdLst */


/*
*
*       Fun:   SGetXxCb
*
*       Desc:  This function retrieves protocol layer control block for given proc,
*              ent and inst IDs
*
*       Ret:   ROK/RFAILED 
*
*       Notes: 
*
*       File:  ss_gen.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetXxCb
(
ProcId proc,
Ent ent,
Inst inst,
Void **xxCb
)
#else
PUBLIC S16 SGetXxCb(proc, ent, inst, xxCb)
ProcId proc;
Ent ent;
Inst inst;
Void **xxCb;
#endif
{
   U16 procIdIdx;
   SsIdx idx;

   TRC1(SGetXxCb);

#if (ERRCLASS & ERRCLS_INT_PAR)
   if ((proc == SS_INV_PROCID) || (ent >= SS_MAX_ENT) ||  (inst >= SS_MAX_INST))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS026, ERRZERO, "Invalid proc/entity/instance");
      RETVALUE(RFAILED);
   }
#endif 
   
   /* 
    * ss030.103: delete: locking/unlocking removed as it causes
    * deadlock/blockage in some cases
    */

   procIdIdx = SGetProcIdIdx(proc);

   if (procIdIdx == SS_INV_PROCID_IDX)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      SSLOGERROR(ERRCLS_INT_PAR, ESS027, ERRZERO, "Could not get proc table idx");
#endif
      RETVALUE(RFAILED);
   }

   idx = osCp.tTskIds[procIdIdx][ent][inst];
   if (idx == SS_TSKNC)
   {
      RETVALUE(RFAILED);
   }

   /* update the CB */
   *xxCb = osCp.tTskTbl[idx].xxCb;
   /*ss032.103 added a check for NULLP */
   if (*xxCb == NULLP)
      RETVALUE(RFAILED);

   RETVALUE(ROK);
} /* SGetXxCb */

#endif /* SS_MULTIPLE_PROCS */



/********************************************************************30**
  
         End of file:     sm_gen.c@@/main/1 - Mon Apr  5 18:01:10 2010
  
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
  
1.2          ---      ag   1. Changed procId for SS to SS_PROC_ID
                              (defined by the implementation)
             ---      ag   2. Fixed a bug in function SInit
             ---      bsr  3. Changed return value for SInit and added
                              error deinit functions
             ---      kp   4. Cosmetic changes

1.3          ---      kp   1. Year display in SLogError() and SError()
                              converted into 4 digits for Y2K related
                              requirements.
1.3+         ss006.13 jn   2. Compile warning - "value computed is 
                              not used" removed for ssDestroySema.
1.3+         ss019.103 bp  3. Fixed bug with OS control point initialization
1.3+         ss028.103 bjp 1. Addition of lock for mBuf reference count      
1.3+         ss029.103 kkj 1. Multiple proc ids support added
1.3+         ss030.103 kkj 1. locking/unlocking removed from SGetXxCb
1.3+         ss032.103 kkj 1. Added a check if cb is NULLP before the return
1.3+         ss033.103 pdb 1. Added the SDeInit API which provides option to
                              remove all the resources during a shutdown.
/main/1      ---       rp  1. SSI enhancements for Multi-core architecture 
                              support
*********************************************************************91*/
