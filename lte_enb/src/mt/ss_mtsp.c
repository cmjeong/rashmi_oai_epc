

/********************************************************************20**
  
     Name:     system services - multi-threaded service provider
  
     Type:     C source file
  
     Desc:     Prototype C source code for the System Service
               service provider primitives that must be supplied
               to work with the multi-threaded OS.
  
     File:     ss_mtsp.c
  
     Sid:      ss_mtsp.c@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:44:13 2014
   
     Prg:      fmg
  
*********************************************************************21*/
  
  
/*
  
System services are the functions required by the protocol
layer for buffer management, timer management, date/time
management, resource checking and initialization.

The following functions are provided in this file for the
system services service user:

     SDisplay       Display
   
     SGetDBuf       Get Dynamic Buffer
     SPutDBuf       Put Dynamic Buffer
     SGetSBuf       Get Static Buffer
     SPutSBuf       Put Static Buffer
     SGetSMem       Get Static Memory
     SPutSMem       Put Static Memory
  
     SChkRes        Check Resources
     SGetDateTime   Get Date and Time
     SGetSysTime    Get System Time
     SRandom        Get Random Number
     SError         Error
  
     SRegTmr        Register Activate Task - timer
     SRegTsk        Register Activate Task - task buffer - non preemptive (old)
     SRegPTsk       Register Prioritized Task routine - non preemptive (old)
     SRegActvTsk    Register Activate Task - non preemptive (new)
     SDeregInitTskTmr  Deregister initialize, task buffer and timer
     SPstTsk        Post task
     SExitTsk       Exit task

     SExitInt       Exit Interrupt
     SHoldInt       Hold Interrupt
     SRelInt        Release Interrupt
     SEnbInt        Enable Interrupt
     SDisInt        Disable Interrupt
     SGetVect       Get Vector
     SPutVect       Put Vector
     SFndProcId     Find Processor Id
    
It should be noted that not all of these functions may be required
by a particular system services service user.

It is assumed that the following functions are provided in the
system services service user file:
  
     SActvInit      Activate layer - initialize
     SActvTmr       Activate layer - timer
     SActvTsk       Activate layer - task
  
*/
  
  
/*
*     The functions provided in this file correspond to the functions
*     provided in the following TRILLIUM software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1020039     Multithreaded System Services (Solaris)
*
*/
  
/*
*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.                      description
*     --------    ----------------------------------------------
*     1000001     Physical Layer - SCC
*     1000002     Data Link Layer - LAPB
*     1000003     Data Link Layer - LAPD
*     1000004     Data Link Layer - Multilink
*     1000005     Data Link Layer - LAPB & LAPD
*     1000006     Network Layer - X.25 Intermediate System
*     1000007     Network Layer - X.25 End System
*     1000008     Network Layer - X.75
*     1000009     Network Layer - Q.930/Q.931
*     1000010     Application Layer - Asynchronous PAD
*     1000012     Spanning Tree
*     1000014     Network Layer - X.25 End & Intermediate System
*     1000016     Network Layer - ISO Internet Protocol - End System
*     1000017     Data Link Layer - Basic Frame Relay
*     1000018     Data Link Layer - Extended Frame Relay
*     1000019     Data Link Layer - Logical Link Control 1
*     1000020     Data Link Layer - Logical Link Control 2
*     1000021     Data Link Layer - Logical Link Control 3
*     1000022     Network Layer - ISO Internet Protocol - Intermediate System
*     1000023     Network Layer - X.31
*     1000024     Signalling System 7
*     1000026     TCP/IP
*     1000034     Physical Layer - ISAC-S
*     1000040     UDP/IP
*     1000041     ESCC
*     1000042     Signalling System 7 - TUP
*     1000043     Network Layer - Q.93B
*     1000044     Data Link Layer - Q.SAAL
*
*/
 
  
  
/* header include files (.h) */
#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers must come first! */
#include "mt.h"            /* mt */
#include "mt_err.h"        /* mt - error */
#include "cm_gen.h"        /* common */
  
/* header/extern include files (.x) */
  
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* common timers must come first! */
#include "mt.x"            /* mt */
#include "cm_gen.x"        /* common */

#ifdef MT_SOL
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <thread.h>
#include <string.h>
#include <termios.h>
#include <poll.h>
#include <errno.h>
#include <unistd.h>
#endif /* MT_SOL */
  
/* local defines */

#define MTPBUFSIZE 256
#define PREBUF 0
#define PSTBUF 1

/* local typedefs */

/* local externs */
  
/* forward references */

PUBLIC S16    mtThreadSelf ARGS((MtThrdId *tId));
PUBLIC Void  *mtDumpTicks ARGS((Void *arg));
PRIVATE S16   mtBldDPool ARGS((Pool pool));  
PRIVATE S16   mtBldSPool ARGS((void));  
PRIVATE S16   mtInitTask ARGS((void));
#ifdef ENB_RELAY
PRIVATE S16   mtInitDrvr ARGS((void)); /* used when relay enabled */
PRIVATE Void *mtDrvrHndlr ARGS((Ptr tskPtr));
#endif /* ENB_RELAY */
#ifdef CONAVL
PRIVATE S16   mtInitCon ARGS((void)); /* used when console enabled */
#endif /* CONAVL */
PRIVATE Void *mtTskHndlr ARGS((Ptr tskPtr));
PRIVATE Void *mtTmrPlaceHndlr ARGS((Ptr tmrPtr));
PRIVATE Void *mtRdConHndlr ARGS((Ptr unused));
PRIVATE S16  mtInitTimer ARGS((void));
PRIVATE S16  mtStartPermTsks ARGS((void));
PRIVATE Void mtGetOpts ARGS((S32 argc, S8 **argv));

/* functions in other modules */

EXTERN Void *mtIntrThrd ARGS((Ptr tskPtr));
EXTERN S16  mtInit ARGS((void));
EXTERN S16  mtPutVect ARGS((VectNmb vNmb, PFVOID vFnct));
EXTERN Void mtTmrEvnt ARGS((PTR tCb, S16 evnt));
EXTERN S16  SAtExit ARGS((MtThrd exitFnct, Void *arg)); 
EXTERN S16  mtThrdSelf ARGS((MtThrdId *tId));
 
/* public variable declarations */
#ifdef MT_SOL
/* ssp (system service provide) */
CONSTANT PUBLIC Txt mtPrgNme[] = "mtss(solaris)";
#else
/* ssp (system service provide) */
CONSTANT PUBLIC Txt mtPrgNme[] = "mtss(unknown)";
#endif /* MT_SOL */
PUBLIC Txt pBuf[MTPBUFSIZE];    /* print buffer */
PUBLIC MtOsCp mtOsCp;           /* os control point */
#ifdef CONAVL
PUBLIC FILE *conInFp;           /* console input file pointer */
PUBLIC FILE *conOutFp;          /* console output file pointer */
#endif /* CONAVL */

#ifndef NOFILESYS
PUBLIC FILE *outFp;             /* output file pointer */
PUBLIC Void *mtCloseOutFp ARGS((Void *arg));
#endif /*  NOFILESYS */

PUBLIC Txt **ssArgv;            /* ss argument vector */
PUBLIC S16 ssArgc;              /* ss argument count */
PUBLIC S16 ssOptInd;            /* SGetOpt vars */
PUBLIC S16 ssOptOpt;            /* SGetOpt vars */
PUBLIC S8 *ssOptArg;            /* SGetOpt vars */


/* private variable declarations */

/*
 * pool table
 */
PUBLIC MtPoolInfo mtPoolInfo[MT_NMB_MSG_POOL]=
{
   /* pool zero (default) used for normal protocol data buffers */
   { 
      MT_POOL_0_STRTIDX, MT_POOL_0_ENDIDX, MT_POOL_0_DSIZE, MT_POOL_0_NMB_BUFS
   },
   /* pool one used for large (wrapper) protocol messages */
   { 
      MT_POOL_1_STRTIDX, MT_POOL_1_ENDIDX, MT_POOL_1_DSIZE, MT_POOL_1_NMB_BUFS
   },
   /* pool two used for timer buffers */
   { 
      MT_POOL_2_STRTIDX, MT_POOL_2_ENDIDX, MT_POOL_2_DSIZE, MT_POOL_2_NMB_BUFS
   },
   /* pool two used for message header buffers */
   { 
      MT_POOL_3_STRTIDX, MT_POOL_3_ENDIDX, MT_POOL_3_DSIZE, MT_POOL_3_NMB_BUFS
   }
};

 
/*
*
*       Fun:   main
*
*       Desc:  This function initializes the system services
*
*       Ret:   none on success
*              exit on failure
*
*       Notes: this is the main function for kicking everything off
*
*       File:  ss_mtsp.c
*
*/
 
#ifdef ANSI
S32 main
(
S32 argc,                       /* argument count */
S8 **argv                       /* argument vector */
)
#else
PUBLIC S32 main(argc, argv)
S32 argc;                       /* argument count */
S8 **argv;                      /* argument vector */
#endif
{
   REG1 Pool pIdx;              /* pool index */
   S16 ret;                     /* return value */
   
   TRC2(mt_init_main)

   /* setup our processor id (can be modified on command line) */ 
#ifdef ENB_RELAY
   mtOsCp.ownProcId = PID_STK(1);
#else
   mtOsCp.ownProcId = 0;
#endif /* ENB_RELAY */

   /* parse command line */
   mtGetOpts(argc, argv);

   /* initialize mt routines */
   if (mtInit() != ROK)
   {
      /*
       * unconditional error, we can't continue
       */
      MTLOGERROR(ERRCLS_DEBUG, EMT001, (ErrVal)-1, "Unable to build SPool");
      exit(1);
   }
   
   /* install an interrupt handler for SIGINT */
   SPutVect(SIGINT, (PIF)SExit);
   
   /* build static pool */
   if (mtBldSPool() != ROK)
   {
      /*
       * unconditional error, we can't continue
       */
      MTLOGERROR(ERRCLS_DEBUG, EMT002, (ErrVal)-1, "Unable to build SPool");
      exit(1);
   }
   

   /* build dynamic pools */
   for (pIdx = 0; pIdx < MT_NMB_MSG_POOL; pIdx++)
   {
      ret = mtBldDPool(pIdx);
      if (ret != ROK)
      {
         /*
          * unconditional error, we can't continue
          */
         MTLOGERROR(ERRCLS_DEBUG, EMT003, (ErrVal)pIdx, 
                    "unable to build DPool");
         exit(1);
      }
      
   }
   
   /* initialize the task table (max number of tasks = MT_MAX_TASK) */
   if (mtInitTask() != ROK)
   {
      /*
       * unconditional error, we can't continue
       */
      MTLOGERROR(ERRCLS_DEBUG, EMT004, (ErrVal)-1, 
                 "unable to initialize task table");
      exit(1);
   }
   
#ifdef ENB_RELAY
   /* initialize the driver table (max number of tasks = MT_MAX_DRVR) */
   if (mtInitDrvr() != ROK)
   {
      /*
       * unconditional error, we can't continue
       */
      MTLOGERROR(ERRCLS_DEBUG, EMT005, (ErrVal)-1, 
                 "unable to initialize driver table");
      exit(1);
   }
#endif /* ENB_RELAY */

   /* initialize the timer table (max number of timers = MT_MAX_TIMER) */
   mtOsCp.sysTicks = 0;

   if (mtInitTimer() != ROK)
   {
      /*
       * unconditional error, we can't continue
       */
      MTLOGERROR(ERRCLS_DEBUG, EMT006, (ErrVal)-1, 
                 "unable to initialize driver table");
      exit(1);
   }
   

#ifdef CONAVL
   /* initialize console */
   if (mtInitCon() !=ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)      
      MTLOGERROR(ERRCLS_DEBUG, EMT007, (ErrVal)-1, 
                 "unable to initialize console");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   }
#endif /* CONAVL */

   /* setup and exit function to dump the total time */
   SAtExit(mtDumpTicks, (Void*)NULLP);
   
   /* call tst() function 
    *
    * tst is function where the user can register protocol tasks,
    * and perform any other bootstrapping required.
    */
   tst();
 
   
   if (mtOsCp.permTask)
   {
      /* kick start permanent task here */
      if (mtStartPermTsks() != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)      
         MTLOGERROR(ERRCLS_DEBUG, EMT008, (ErrVal)-1, 
                    "unable to start permanent tasks");
         exit(1);
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      }
      
   }
   
   thr_exit(NULLP);             /* main thread can exit! */
   exit(0);                     /* NOTREACHED */
} /* end of mt_init_main */


/*
*
*       Fun:   mtBldSPool
*
*       Desc:  Build Static Memory Pool
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PRIVATE S16 mtBldSPool
(
void
)
#else
PRIVATE S16 mtBldSPool()
#endif
{
   MtSPool *s;                         /* static memory pointer  */

   TRC2(mtBldSPool)

   if (SGetMutex(&mtOsCp.sPool.mtx) != ROK)
      RETVALUE(RFAILED);
   if (SLockMutex(mtOsCp.sPool.mtx) != ROK)
      RETVALUE(RFAILED);

   s = &mtOsCp.sPool;  

   s->memResv = 0;
   s->memStrt = (Data*)calloc(MT_SPOOL_SIZE, sizeof(Data));
   if (s->memStrt == (Data*)NULLP)
   {
      SUnlockMutex(mtOsCp.sPool.mtx); /* unlock mutex */
      RETVALUE(RFAILED);        /* not enough memory available */
   }
   
   s->memEnd = (Data *)(s->memStrt + MT_SPOOL_SIZE - PTRSTRIDE);
   s->avlStrt = (SBuf *)s->memStrt;
   s->avlEnd = s->memEnd;

   s->crntSize = s->bufSize = MT_SPOOL_SIZE;
   s->avlStrt->sChn.fwd = s->avlStrt;
   s->avlStrt->size = s->bufSize;
   s->minSize = s->maxSize = s->crntSize;

   SUnlockMutex(mtOsCp.sPool.mtx);

   RETVALUE(ROK);
} /* end of mtBldSPool */
 

/*
*
*       Fun:   mtBldDPool
*
*       Desc:  Initialize a message pool.  The message pool's msg
*              buffers are allocated and the message pool is set to
*              a full state.
*
*       Ret:   ROK      - ok
*
*       Notes: This function should *only* be invoked once.
*
*       File:  ss_mtsp.c
*
*/

#ifdef ANSI
PRIVATE S16 mtBldDPool
(
Pool pool
)
#else
PRIVATE S16 mtBldDPool(pool)
Pool pool;
#endif
{
   REG1 S16 i;                  /* index */
   REG2 Buffer *dBuf;           /* data buffer */
   MtDPool *mp;               /* message pool */
   MtPoolInfo *pi;              /* pool info */
   REG2 U8 *ptr;
   S32 size;
   
   TRC2(mtBldDPool)

   mp = &mtOsCp.dPool[pool];
   pi = &mtPoolInfo[pool];
   
   if (SGetMutex(&mp->mtx) != ROK)   /* get (allocate) mutex */
      RETVALUE(RFAILED);
   if (SLockMutex(mp->mtx) != ROK)   /* lock mutex */
      RETVALUE(RFAILED);
   if (SInitQueue(&mp->bufQ) != ROK) /* initialize queue */
   {
      (Void)SUnlockMutex(mp->mtx);
      RETVALUE(RFAILED);
   }
   
   mp->status = MT_MSG_POOL_UNINITIALIZED;
   size = pi->nmbBufs * sizeof(Buffer);
   size += pi->nmbBufs * pi->dSize;

   ptr = (U8 *)malloc((U32)size);
   size = sizeof(Buffer) + pi->dSize;
   for (i = 0; i < pi->nmbBufs; i++, ptr += size ) 
   {
      dBuf = (Buffer*)ptr;
      dBuf->t.dat.strtIdx = pi->strtIdx;
      dBuf->t.dat.endIdx = dBuf->t.dat.strtIdx;
      dBuf->t.dat.size = pi->dSize;
      dBuf->t.dat.pool = pool;
      if (dBuf->t.dat.size)
         dBuf->t.dat.data = ((U8 *)dBuf + sizeof(Buffer));
      dBuf->bufType = BDPOOL;
      if (SQueueLast(dBuf, &mtOsCp.dPool[pool].bufQ) != ROK)
      {
         (Void)SUnlockMutex(mp->mtx);
         RETVALUE(RFAILED);
      }
      mp->size++;
   }
   mp->status = MT_MSG_POOL_INITIALIZED;
   SUnlockMutex(mp->mtx);
   RETVALUE(ROK);
}  /* end of mtBldDPool */


/*
*
*       Fun:   mtInitTask
*
*       Desc:  Initialize the static task table for service.
*
*       Ret:   ROK      - ok
*              RFAIELD  - error
*
*       Notes: This function should *only* be invoked once.
*
*       File:  ss_mtsp.c
*
*/
 
#ifdef ANSI
PUBLIC S16 mtInitTask
(
void
)
#else
PUBLIC S16 mtInitTask()
#endif
{
   U32 i;
   U32 j;
   
   TRC2(mtInitTask)

   /* create and obtain task table lock */
   if (SGetMutex(&mtOsCp.tskTblMtx) != ROK)
      RETVALUE(RFAILED);
   if (SLockMutex(mtOsCp.tskTblMtx) != ROK)
      RETVALUE(RFAILED);
   
   /* clear index variable */ 
   mtOsCp.tskTblIdx = 0; 
 
   /* initialize task table */ 
   for (i = 0; i < MT_MAX_TASK; i++) 
   {  
      /* get entry */
      if (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data**)&mtOsCp.tskTbl[i], 
                   sizeof(MtTskEntry)) != ROK)
      {
         SUnlockMutex(mtOsCp.tskTblMtx);
         RETVALUE(RFAILED);
      }
      
      /* initialize */
      mtOsCp.tskTbl[i]->index     = i;
      mtOsCp.tskTbl[i]->type      = MT_TSK_NULL;
      /* mtOsCp.tskTbl[i].dq     = filled in later */
      mtOsCp.tskTbl[i]->tId       = MT_THRDID_NULL;
      mtOsCp.tskTbl[i]->count     = 0;
      mtOsCp.tskTbl[i]->tskCnt    = 0;
      /* initialize tasks */
      for (j = 0; j < MT_MAX_TSKCNT; j++)
      {
         mtOsCp.tskTbl[i]->tsks[j].ent = ENTNC;
         mtOsCp.tskTbl[i]->tsks[j].inst = INSTNC;
         mtOsCp.tskTbl[i]->tsks[j].actvTsk = (ActvTsk)NULLP;
      }
   }  
   /* all done, unlock and return */
   SUnlockMutex(mtOsCp.tskTblMtx);
   RETVALUE(ROK);
}  /* end of mtInitTask */


/*
*
*       Fun:   mtInitTimer
*
*       Desc:  Initialize the timer object.  
*
*       Ret:   ROK      - ok
*              RFAILED  - error
*
*       Notes: This function should *only* be invoked once.
*
*       File:  ss_mtsp.c
*
*/

#ifdef ANSI
PRIVATE S16 mtInitTimer
(
void
)
#else
PRIVATE S16 mtInitTimer()
#endif
{
   U32 i;

   TRC2(mtInitTimer)

   /* create and aquire timer table lock */
   if (SGetMutex(&mtOsCp.tmrTblMtx) != ROK)
      RETVALUE(RFAILED);
   if (SLockMutex(mtOsCp.tmrTblMtx) != ROK)
      RETVALUE(RFAILED);

   /* clear index  */
   mtOsCp.tmrTblIdx = 0;

   /* initialze timer table */
   for (i = 0; i < MT_MAX_TIMER; i++)
   {
      /* allocate entry */
      if (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data**)&mtOsCp.tmrTbl[i], 
               sizeof(MtTmrEntry)) != ROK)
      {
         SUnlockMutex(mtOsCp.tmrTblMtx);
         RETVALUE(RFAILED);
      }
      /* initialize */
      mtOsCp.tmrTbl[i]->timerId   = MT_TMRID_NULL;
      mtOsCp.tmrTbl[i]->ent = ENTNC;
      mtOsCp.tmrTbl[i]->inst = INSTNC;
      mtOsCp.tmrTbl[i]->dq = (MtDq*)NULLP;
      mtOsCp.tmrTbl[i]->tmrFnct = (PFS16)NULLP;      
      mtOsCp.tmrTbl[i]->delay     = 0;
      mtOsCp.tmrTbl[i]->sent      = 0;
      mtOsCp.tmrTbl[i]->drop      = 0;
      mtOsCp.tmrTbl[i]->received  = 0;
   }

   /* get mutex for timer control point */
   if (SGetMutex(&mtOsCp.tmrCp.mtx) != ROK)
   {
      SUnlockMutex(mtOsCp.tmrTblMtx);
      RETVALUE(RFAILED);
   }  

   /* get timer control point condition */
   if (SGetCond(&mtOsCp.tmrCp.cond) != ROK)
   {
      SPutMutex(mtOsCp.tmrCp.mtx);
      SUnlockMutex(mtOsCp.tmrTblMtx);
      RETVALUE(RFAILED);
   }  

   /* initialize timer queue control point length */
   mtOsCp.tmrCp.tmrTqCp.tmrLen = MT_TQNUMENT;
   
   /* create a new thread to handle timer interrupts 
    * (actually, all interrutps) 
    */
   if (SGetThread(mtIntrThrd,              /* thread function */
                  (MT_THR_NEW_LWP |        /* bump concurrency */
                   MT_THR_DAEMON |         /* daemon thread */
                   MT_THR_BOUND |          /* thread should be bound */
                   MT_THR_DETACHED),       /* detached (no join) */
                  (Ptr)NULLP,              /* no arguments */
                  &mtOsCp.intHndlrThrd)    /* thread id */
       != ROK)
   {
      SPutCond(mtOsCp.tmrCp.cond);
      SPutMutex(mtOsCp.tmrCp.mtx);
      SUnlockMutex(mtOsCp.tmrTblMtx);
      RETVALUE(RFAILED);
   }

   /* set this threads priority to normal */
   SSetThrdPrior(mtOsCp.intHndlrThrd, MT_NORM_PRI);

   /*
    * initialize the demand queue of the Timer Placement Thread 
    */
   if (SGetMutex(&mtOsCp.tmrPlace.dq.mtx) != ROK) /* get mutex */
   {
      SPutThread(mtOsCp.intHndlrThrd);
      SPutCond(mtOsCp.tmrCp.cond);
      SPutMutex(mtOsCp.tmrCp.mtx);
      SUnlockMutex(mtOsCp.tmrTblMtx);
      RETVALUE(RFAILED);
   }
   
   if (SLockMutex(mtOsCp.tmrPlace.dq.mtx) != ROK) /* lock dq */
   {
      SPutThread(mtOsCp.intHndlrThrd);
      SPutCond(mtOsCp.tmrCp.cond);
      SPutMutex(mtOsCp.tmrCp.mtx);
      SUnlockMutex(mtOsCp.tmrTblMtx);
      RETVALUE(RFAILED);
   }
   
   if (SGetCond(&mtOsCp.tmrPlace.dq.cond) != ROK)
   {
      SUnlockMutex(mtOsCp.tmrPlace.dq.mtx);
      SPutThread(mtOsCp.intHndlrThrd);
      SPutCond(mtOsCp.tmrCp.cond);
      SPutMutex(mtOsCp.tmrCp.mtx);
      SUnlockMutex(mtOsCp.tmrTblMtx);
      RETVALUE(RFAILED);
   }
   SInitQueue(&mtOsCp.tmrPlace.dq.bufQ);

   /* create the thread to handle the placement of the timer block on
    * the timing queue on expiry of timer
    */
   if (SGetThread(mtTmrPlaceHndlr,         /* thread function */
                  (MT_THR_NEW_LWP |        /* bump concurrency */
                   MT_THR_DAEMON |         /* daemon thread */
                   MT_THR_BOUND |          /* thread should be bound */
                   MT_THR_DETACHED),       /* detached (no join) */
                  (Ptr)mtOsCp.tmrTbl,      /* pointer to timer table */
                  &mtOsCp.tmrPlace.tId)    /* thread id */
       != ROK)
   {
      SUnlockMutex(mtOsCp.tmrPlace.dq.mtx);
      SPutCond(mtOsCp.tmrPlace.dq.cond);
      SPutThread(mtOsCp.intHndlrThrd);
      SPutCond(mtOsCp.tmrCp.cond);
      SPutMutex(mtOsCp.tmrCp.mtx);
      SUnlockMutex(mtOsCp.tmrTblMtx);
      RETVALUE(RFAILED);
   }

   /* set this threads priority to high */
   SSetThrdPrior(mtOsCp.tmrPlace.tId, MT_HIGH_PRI);

   /* release */
   SUnlockMutex(mtOsCp.tmrPlace.dq.mtx); /* unlock dq */
   SUnlockMutex(mtOsCp.tmrTblMtx);

   RETVALUE(ROK);
   /* end of mtInitTimer */
}

/*
*
*       Fun:   mtStartPermTsks
*
*       Desc:  This function starts all permanent tasks in the stack.
*
*       Ret:   ROK     - ok
*              RFAILED - error
*
*       Notes: Permanent tasks are implemented by using low priority threads
*              and continuosly sending messages to themselves.
*       File:  ss_mtsp.c
*
*/
 
#ifdef ANSI
PUBLIC S16 mtStartPermTsks
(
void
)
#else
PUBLIC S16 mtStartPermTsks()
#endif
{
   REG1 U32 i;
   Buffer *mBuf;
   Pst pst;

   TRC0(mtStartPermTsks)

   /* setup post structure */
   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
   pst.selector = SEL_LC_NEW;
   pst.region = DFLT_REGION;
   pst.pool = DFLT_POOL;
   pst.prior = PRIOR0;
   pst.route = RTESPEC;
   pst.event = 0;
   
   /* find all permanent tasks */
   for (i = 0; i < MT_MAX_TASK; i++)
   {
      if (mtOsCp.tskTbl[i]->type == MT_TSK_PERM)
      {
         pst.dstEnt  = mtOsCp.tskTbl[i]->tsks[0].ent;
         pst.dstInst = mtOsCp.tskTbl[i]->tsks[0].inst;
         pst.srcEnt  = mtOsCp.tskTbl[i]->tsks[0].ent;
         pst.srcInst = mtOsCp.tskTbl[i]->tsks[0].inst;
         if (SGetMsg(DFLT_REGION, MT_TMR_POOL, &mBuf) != ROK)
            RETVALUE(RFAILED);
         /* send a message to each permanent task */
         if (SPstTsk(&pst, mBuf) != ROK)
            RETVALUE(RFAILED);
      }
   }
   RETVALUE(ROK);
} /* end of mtStartPermTsks */
 
  
/*
*     interface functions to system services service user
*/

  
/*
*
*       Fun:   SDisplay
*
*       Desc:  This function displays a string to a given output
*              channel.
*
*       Ret:   ROK      - ok
*
*       Notes: Buffer should be null terminated.
*
*              channel 0 is reserved for backwards compatibility
*              with SPrint
*
*       File:  ss_mtsp.c
*
*/
   
#ifdef ANSI
PUBLIC S16 SDisplay
(
S16 chan,                   /* channel */
Txt *buf                    /* buffer */
)
#else
PUBLIC S16 SDisplay(chan, buf)
S16 chan;                   /* channel */
Txt *buf;                   /* buffer */
#endif
{
   TRC2(SDisplay)


#ifdef CONAVL
   if (conOutFp)
      fwrite(buf, strlen(buf), 1, conOutFp);
#endif /* CONAVL */

#ifndef NOFILESYS
   if (outFp)
   {
      fwrite(buf,strlen(buf),1,outFp);
   }
#endif /* not NOFILESYS */
   
   RETVALUE(ROK);
} /* end of SDisplay */

  
/*
*
*       Fun:   SLogError
*
*       Desc:  Invoked by layer when a software error is detected. 
*
*       Ret:   Void
*
*       Notes: None
*
*       File:  ss_mtsp.c
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
PUBLIC Void SLogError(ent, inst, procId, file, line, errCls, errCode, errVal, errDesc)
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
   Txt  *errClsMsg;

   TRC1(SLogError)

   
   switch(errCls)
   {

      case ERRCLS_ADD_RES:
         errClsMsg = "ERRCLS_ADD_RES";
         break;

      case ERRCLS_INT_PAR:
         errClsMsg = "ERRCLS_INT_PAR";
         break;

      case ERRCLS_DEBUG:
         errClsMsg = "ERRCLS_DEBUG";
         break;

      default:
         errClsMsg = "INVALID ERROR CLASS !";
         break;
   }

#ifndef CONAVL
   /* we know we have the this, so use it */
   printf("\n%s: sw error:  ent: %03d  inst: %03d  proc id: %03d \n\
                file: %s line: %03d errcode: %05d errcls: %s\n\
                errval: %05d  errdesc: %s\n", mtPrgNme, ent, inst, 
          procId, file, (S32)line, (S32)errCode, errClsMsg, 
          (S32)errVal, errDesc);
#else
   sprintf(pBuf,"\n%s: sw error:  ent: %03d  inst: %03d  proc id: %03d \n\
                file: %s line: %03ld errcode: %05ld errcls: %s\n\
                errval: %05ld  errdesc: %s\n", mtPrgNme, ent, inst, 
           procId, file, line, errCode, errClsMsg, errVal, errDesc);
   SDisplay(0, pBuf);
#endif /* CONAVL */

   if(errCls == ERRCLS_DEBUG )  /* these errors halt the system */
      SExit();

   RETVOID;
} /* end of SLogError */


/*
*
*       Fun:   Get dynamic buffer
*
*       Desc:  This function allocates a buffer from the dynamic
*              memory pool indicated by the caller.
*
*       Ret:   ROK      - ok
*              ROUTRES  - out of resources
*              RFAILED  - error
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetDBuf
(
REG1 Region region,         /* region id */
REG2 Pool pool,             /* pool id */
Buffer **bufPtr             /* pointer to buffer */
)
#else
PUBLIC S16 SGetDBuf(region, pool, bufPtr)
REG1 Region region;         /* region id */
REG2 Pool pool;             /* pool id */
Buffer **bufPtr;            /* pointer to buffer */
#endif
{
   Buffer *dBuf;
   S16 ret;
   
   TRC2(SGetDBuf)

   /* lock the pool */
   if (SLockMutex(mtOsCp.dPool[pool].mtx) != ROK)
   {
      /* this should never happen */
      RETVALUE(RFAILED);
   }

   /* dequeue the first buffer */
   ret = SDequeueFirst(&dBuf, &mtOsCp.dPool[pool].bufQ);
   if (ret != ROK)
   {
      SUnlockMutex(mtOsCp.dPool[pool].mtx);
      RETVALUE(ROUTRES);
   }

   /* unlock mutex */
   SUnlockMutex(mtOsCp.dPool[pool].mtx);
   
   /* initialize buffer */
   dBuf->bufType = BDATA;
   *bufPtr = dBuf;
   
   RETVALUE(ROK);
} /* end of SGetDBuf */

  
/*
*
*       Fun:   Put dynamic buffer
*
*       Desc:  This function deallocates a buffer back to the
*              dynamic memory pool indicated by the caller.
*
*       Ret:   ROK      - ok
*              RFAILED  - error
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPutDBuf
(
REG2 Region region,         /* region id */
REG3 Pool pool,             /* pool id */
REG1 Buffer *buf            /* buffer */
)
#else
PUBLIC S16 SPutDBuf(region, pool, buf)
REG2 Region region;         /* region id */
REG3 Pool pool;             /* pool id */
REG1 Buffer *buf;           /* buffer */
#endif
{

   TRC2(SPutDBuf)

   /* reset everything */
   buf->bufType = BDPOOL;
   buf->dChn.next = NULLP;
   buf->dChn.crnt = NULLP;
   buf->t.dat.strtIdx = mtPoolInfo[pool].strtIdx;
   buf->t.dat.endIdx = buf->t.dat.strtIdx;

   /* lock the mutex */
   if (SLockMutex(mtOsCp.dPool[pool].mtx) != ROK)
      RETVALUE(RFAILED);
   
   /* queue it last */
   if (SQueueLast(buf, &mtOsCp.dPool[pool].bufQ) != ROK)
   {
      SUnlockMutex(mtOsCp.dPool[pool].mtx);
      RETVALUE(RFAILED);
   }
   
   /* unlock and return */
   SUnlockMutex(mtOsCp.dPool[pool].mtx);
   
   RETVALUE(ROK);
} /* end of SPutDBuf */

/*
*
*       Fun:   Get Message
*
*       Desc:  This function allocates a message from a specified region
*              and pool.
*
*       Ret:   ROK      - ok
*              ROUTRES  - out of resources
*              RFAILED  - error
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/

#ifdef ANSI
PUBLIC S16 SGetMsg
(
Region region,              /* region id */
Pool pool,                  /* pool id */
Buffer **mBufPtr            /* pointer to message buffer */
)
#else
PUBLIC S16 SGetMsg(region, pool, mBufPtr)
Region region;              /* region id */
Pool pool;                  /* pool id */
Buffer **mBufPtr;           /* pointer to message buffer */
#endif
{
   Buffer *mBuf;            /* message buffer */
   S16 ret;                 /* return code */
  
   TRC1(SGetMsg)

   UNUSED(region);
   
#if (ERRCLASS & ERRCLS_INT_PAR)
    if( mBufPtr == NULLP)
    {
        MTLOGERROR(ERRCLS_INT_PAR, EMT009, ERRZERO, "Invalid Pointer Passed");
        RETVALUE(RFAILED);
    }
#endif /* ERRCLASS & ERRCLS_INT_PAR */
 
   /* allocate the control point of the message buffer */
   /* we always get messages from the MBUF pool */
   ret = SGetDBuf(DFLT_REGION, MT_MBUF_POOL, &mBuf);
   if (ret != ROK)
      RETVALUE(ret);
 
   /* initialize chain pointer of message buffer */
   mBuf->dChn.next = NULLP;
   mBuf->dChn.prev = NULLP;
   mBuf->dChn.crnt = mBuf;
   
   mBuf->t.msg.bufQ.dChn.next = NULLP;
   mBuf->t.msg.bufQ.dChn.prev = NULLP;
   mBuf->t.msg.bufQ.dChn.crnt = NULLP;
   mBuf->t.msg.bufQ.crntSize = 0;
   
   /* set buffer type to message buffer */
   mBuf->bufType = BMSG;
 
   /* initialize messages to zero length */
   mBuf->t.msg.msgLen = 0;
 
   /* we stamp the pool field with the pool
    * for getting dBufs later. Required For VxWOrks only 
    */
   mBuf->t.msg.pool= pool;
   
   /* return new message */
   *mBufPtr = mBuf;
 
   RETVALUE(ROK);
} /* end of SGetMsg */


/*
*
*       Fun:   SPutMsg
*
*       Desc:  This function deallocates a message back.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: all data attached to message is returned to memory.
*              message is returned to memory. return is ok.
*              
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPutMsg
(
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPutMsg(mBuf)
Buffer *mBuf;               /* message buffer */
#endif
{
   TRC1(SPutMsg)
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT010, ERRZERO, "Null Pointer Passed");
      RETVALUE(RFAILED);
   }
   if (mBuf->bufType != BMSG)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT011, (ErrVal) mBuf->bufType, 
                 "Invalid Buffer Type Passed");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
 
   /* return all data buffers */
   if (SFlushQueue(&mBuf->t.msg.bufQ) != ROK)
      RETVALUE(RFAILED);
 
   /* return message buffer */
   if (SPutDBuf(DFLT_REGION, MT_MBUF_POOL, mBuf) != ROK)
      RETVALUE(RFAILED);
 
   RETVALUE(ROK);
} /* end of SPutMsg */

  
/*
*
*       Fun:   Get static buffer
*
*       Desc:  This function allocates a buffer from the static
*              memory pool indicated by the caller.
*
*       Ret:   ROK      - ok
*              ROUTRES  - out of resources
*              RFAILED  - error
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetSBuf
(
REG1 Region region,         /* region id */
REG2 Pool pool,             /* pool id */
Data **bufPtr,              /* pointer to buffer */
REG3 Size size              /* size */
)
#else
PUBLIC S16 SGetSBuf(region, pool, bufPtr, size)
REG1 Region region;         /* region id */
REG2 Pool pool;             /* pool id */
Data **bufPtr;              /* pointer to buffer */
REG3 Size size;             /* size */
#endif
{
#ifndef USE_PURE
   MtSPool *s;                /* static pool control point */
   Data *tBuf;              /* temporary buffer */
   Size tmpSize;            /* temporary size */
   SBuf FAR *p;             /* current static buffer */
   SBuf FAR *q;             /* previous static buffer */
  
   TRC0(SGetSBuf)

   UNUSED(region);
   UNUSED(pool);

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (bufPtr == NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT012, bufPtr, "null buffer pointer");
      RETVALUE(RFAILED);
   }
   /* check size */
   if (size == (Size) 0)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT013, size, "zero size");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
   /* ignore region and pool ids to reference static pool control point */
   s = &mtOsCp.sPool;
   size = SBUFSIZE(size);
   if (SLockMutex(mtOsCp.sPool.mtx) != ROK)
      RETVALUE(RFAILED);

   q = (SBuf *) PTRALIGN(s->avlStrt);

   /* check if requested size > than size of static buffer */
   if (size > s->bufSize)
   {
      SUnlockMutex(mtOsCp.sPool.mtx);
      RETVALUE(ROUTRES);
   }
   /* check if static buffer available */
   if (!q)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT014, q, "static buffer not available");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

      SUnlockMutex(mtOsCp.sPool.mtx);
      RETVALUE(RFAILED);
   }

   for (p = (SBuf FAR*)q->sChn.fwd;; q = p, p = (SBuf FAR *)p->sChn.fwd)
   {
      tmpSize = (Size) DATAALIGN(p->size);
      if ((tmpSize == size) || (tmpSize >= (size + (Size)MINBUFSIZE)))
      {
         tBuf = (Data *) PTRALIGN(p);
         if (tmpSize == size)
            q->sChn.fwd = p->sChn.fwd;
         else
         {
            tmpSize = (Size) DATAALIGN((tmpSize - size));
            p->size = tmpSize;
            tBuf += tmpSize;
         }
         p = (SBuf *) PTRALIGN(tBuf);
         if (p == s->avlStrt)
         {
            if (p->sChn.fwd == s->avlStrt)
               s->avlStrt = NULLP;
            else
               s->avlStrt = p->sChn.fwd;
         }
         s->bufSize = (Size) DATAALIGN(s->bufSize - size);
         s->crntSize = (Size) DATAALIGN(s->crntSize - size);
         *bufPtr = (Data *) PTRALIGN(tBuf);
#ifdef MSDBG6
         {
            Txt prntBuf[PRNTSZE];    /* data buffer */
            sprintf(prntBuf, "LEAK:GS[%d,%d](%p, %lu, %lu)\n", 
                    region, pool, *bufPtr, size, s->bufSize);
            SDisplay(0, (Txt *) prntBuf);
         }
#endif
         break;
      }
      if (p == s->avlStrt)
      {
         SUnlockMutex(mtOsCp.sPool.mtx);
         RETVALUE(ROUTRES);
      }
   }

   if (s->crntSize < s->minSize)
      s->minSize = s->crntSize;

   SUnlockMutex(mtOsCp.sPool.mtx);
   RETVALUE(ROK);
#else  /* use pure is on */
   *bufPtr = (Data *)malloc(size);
   RETVALUE(ROK);
#endif /* USE_PURE */
} /* end of SGetSBuf */

  
/*
*
*       Fun:   Put static buffer
*
*       Desc:  This function deallocates a buffer back to the
*              static memory pool indicated by the caller.
*
*       Ret:   ROK      - ok
*              RFAILED  - error
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPutSBuf
(
REG2 Region region,         /* region id */
REG3 Pool pool,             /* pool id */
REG1 Data *buf,             /* buffer */
REG4 Size size              /* size */
)
#else
PUBLIC S16 SPutSBuf(region, pool, buf, size)
REG2 Region region;         /* region id */
REG3 Pool pool;             /* pool id */
REG1 Data *buf;             /* buffer */
REG4 Size size;             /* size */
#endif
{
#ifndef USE_PURE
   MtSPool *s;          /* static pool control point */
   SBuf *p;             /* current static buffer */
   SBuf *q;             /* previous static buffer */
  
   TRC0(SPutSBuf)

   UNUSED(region);
   UNUSED(pool);
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer */
   if (buf == NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT015, buf, "null buffer");
      RETVALUE(RFAILED);
   }
   /* check size */
   if (size == (Size) 0)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT016, size, "zero size");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
   /* ignore region and pool ids to reference static pool control point */
   s = &mtOsCp.sPool;

   if (SLockMutex(mtOsCp.sPool.mtx) != ROK)
      RETVALUE(RFAILED);
#ifdef MSDBG6
   {
      Txt prntBuf[PRNTSZE];    /* data buffer */
      sprintf(prntBuf, "LEAK:PS[%d,%d](%p, %lu, %lu)\n", region, pool, 
              buf, size, s->bufSize);
      SDisplay(0, (Txt *) prntBuf);
   }
#endif

   size = SBUFSIZE(size);
   p = (SBuf *) PTRALIGN(buf);
   p->size = size;
   q = (SBuf *) PTRALIGN(s->avlStrt);
   if (q == NULLP)
   {
      s->avlStrt = p;
      s->bufSize = size;
      p->sChn.fwd = p;
      s->crntSize += size;
      SUnlockMutex(mtOsCp.sPool.mtx);
      RETVALUE(ROK);
   }
   for (; !(p > q && p < q->sChn.fwd); q = q->sChn.fwd)
      if (q >= q->sChn.fwd && (p > q || p < q->sChn.fwd))
         break;

   if ((SBuf *) PTRALIGN(buf + size) == q->sChn.fwd)
   {
      p->size += q->sChn.fwd->size;
      p->sChn.fwd = (q->sChn.fwd == q) ? p : q->sChn.fwd->sChn.fwd;
   }
   else
      p->sChn.fwd = q->sChn.fwd;

   buf = (Data *) q;
   if ((SBuf *) PTRALIGN(buf + q->size) == p)
   {
      q->size += p->size;
      q->sChn.fwd = p->sChn.fwd;
   }
   else
      q->sChn.fwd = p;

   s->bufSize += size;
   if (p < s->avlStrt)
      s->avlStrt = p;
   s->crntSize = s->crntSize + size;
   SUnlockMutex(mtOsCp.sPool.mtx);
   RETVALUE(ROK);
#else
   TRC1(SPutSBuf)
   (Void)free(buf);
   RETVALUE(ROK);
#endif /* USE_PURE */
} /* end of SPutSBuf */

  
/*
*
*       Fun:   Get Static Memory
*
*       Desc:  This function allocates a static buffer pool within the
*              specified memory region.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetSMem
(
REG1 Region region,         /* region id */
REG3 Size size,             /* size */
REG2 Pool *pool             /* pointer to pool id */
)
#else
PUBLIC S16 SGetSMem(region, size, pool)
REG1 Region region;         /* region id */
REG3 Size size;             /* size */
REG2 Pool *pool;            /* pointer to pool id */
#endif
{
   TRC2(SGetSMem)

   UNUSED(region);          /* parameter unused */
   UNUSED(size);            /* parameter unused */

   *pool = DFLT_POOL;
   
   RETVALUE(ROK);
} /* end of SGetSMem */


/*
*
*       Fun:   Put Static Memory
*
*       Desc:  This function deallocates a static buffer pool within the
*              specified memory region.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPutSMem
(
REG1 Region region,         /* region id */
REG2 Pool pool              /* pool id */
)
#else
PUBLIC S16 SPutSMem(region, size, pool)
REG1 Region region;         /* region id */
REG2 Pool pool;             /* pool id */
#endif
{
   TRC2(SPutSMem)

   UNUSED(region);          /* parameter unused */
   UNUSED(pool);            /* parameter unused */

   RETVALUE(ROK);
} /* end of SPutSMem */


/*
*
*       Fun:   Set date and time
*
*       Desc:  This function is used to set the calendar
*              date and time.
*
*       Ret:   ROK      - ok
*
*       Notes: Unimplemented
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SSetDateTime
(
REG1 DateTime *dt           /* date and time */
)
#else
PUBLIC S16 SSetDateTime(dt)
REG1 DateTime *dt;          /* date and time */
#endif
{
   TRC2(SSetDateTime)

   RETVALUE(ROK);
} /* end of SSetDateTime */
 
  
/*
*
*       Fun:   Get date and time
*
*       Desc:  This function is used to determine the calendar
*              date and time. This information may be used for
*              some management functions.
*
*       Ret:   ROK      - ok
*              RFAILED  - error
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetDateTime
(
REG1 DateTime *dt           /* date and time */
)
#else
PUBLIC S16 SGetDateTime(dt)
REG1 DateTime *dt;          /* date and time */
#endif
{
   time_t t1;               /* unix - time */
   struct tm *t2;           /* unix - time */

   TRC2(SGetDateTime)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (dt == NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT017, dt, "datetime pointer id null");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

   time(&t1);
   t2 = localtime(&t1);
   dt->month = (U8) t2->tm_mon + 1;
   dt->day = (U8) t2->tm_mday;
   dt->year = (U8) t2->tm_year;
   dt->hour = (U8) t2->tm_hour;
   dt->min = (U8) t2->tm_min;
   dt->sec = (U8) t2->tm_sec;
   dt->tenths = 0;

   RETVALUE(ROK);
} /* end of SGetDateTime */

  
/*
*
*       Fun:   Get system time
*
*       Desc:  This function is used to determine the system
*              time. This information may be used for
*              some management functions.
*
*       Ret:   ROK      - ok
*
*       Notes: mtOsCp.sysTicks is updated by the timer 
*              tick signal handler
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetSysTime
(
Ticks *sysTime              /* system time */
)
#else
PUBLIC S16 SGetSysTime(sysTime)
Ticks *sysTime;             /* system time */
#endif
{
   TRC2(SGetSysTime)

#if (ERRCLASS & ERRCLS_INT_PAR)      
   if (sysTime == (Ticks*)NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT018, sysTime, "sysTime pointer is null");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */   
   *sysTime = mtOsCp.sysTicks;
   RETVALUE(ROK);
} /* end of SGetSysTime */

  
/*
*
*       Fun:   Get Random Number
*
*       Desc:  Invoked by layer when a pseudorandom number
*              is required.
*
*       Ret:   ROK      - ok
*
*       Notes: Suggested approach uses shuffled Linear Congruential
*              Operators as described in Byte magazine October
*              1984; "Generating and Testing Pseudorandom Numbers"
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRandom
(
Random *value               /* random number */
)
#else
PUBLIC S16 SRandom(value)
Random *value;              /* random number */
#endif
{
   TRC2(SRandom)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (value == NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT019, value, "value pointer is null");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

   *value = (Random) rand();
   RETVALUE(ROK);
} /* end of SRandom */

  
/*
*
*       Fun:   Error
*
*       Desc:  Invoked by layer when an unrecoverable
*              software error is detected. This function should
*              never return.
*
*       Ret:   None
*
*       Notes: This function has been superceded by SLogError
*
*       File:  ss_mtsp.c
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

   TRC2(SError)

   MTLOGERROR(ERRCLS_INT_PAR, EMT020, seq, "SError");

   RETVALUE(ROK);
} /* end of SError */
 
  
/*
*
*       Fun:   Register Activate Task - timer
*
*       Desc:  This function is used to register a timer function for the
*              layer. The system services will periodically invoke the
*              function passed to it. The timer function will be used by the
*              layer to manage the layers internal protocol timers.
*
*       Ret:   ROK      - ok
*       Ret:   RFAILED  - failed
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRegTmr
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
S16 period,                 /* period */
PFS16 tmrFnct               /* timer function, typically SActvTmr */
)
#else
PUBLIC S16 SRegTmr(ent, inst, period, tmrFnct)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
S16 period;                 /* period */
PFS16 tmrFnct;              /* timer function, typically SActvTmr */
#endif
{
   U32 index;
   REG1 U32 i;
   REG2 U32 j;
   Bool found;
   CmTmrArg arg;
   MtTmrEntry *tEnt;

   TRC2(SRegTmr)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check period */
   if (period == 0)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT021, period, "Invalid parameter (Period) Passed");
      RETVALUE(RFAILED);
   }
   /* check timer function */
   if (tmrFnct == NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT022, tmrFnct, "Invalid parameter (tmrFnct) Passed");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

   /* lock timer table mutex */
   if(SLockMutex(mtOsCp.tmrTblMtx) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)      
      MTLOGERROR(ERRCLS_DEBUG, EMT023, mtOsCp.tmrTblMtx, 
                 "unable to aquire timer table mutex");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */      
      RETVALUE(RFAILED);
   }

   if (mtOsCp.tmrTblIdx >= MT_MAX_TIMER)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT024, mtOsCp.tmrTblIdx ,
                 "Maximum Timers Registered");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      SUnlockMutex(mtOsCp.tmrTblMtx);
      RETVALUE(RFAILED);
   }

   /* Check if the task has been registered */
   /* The assumption is that a task must be registered
    * or attached prior to calling SRegTmr
    */
   found = FALSE;
   for (i = 0; i < mtOsCp.tskTblIdx; i++)
   {
      for (j = 0; j < mtOsCp.tskTbl[i]->tskCnt; j++)
      {
         if ((mtOsCp.tskTbl[i]->tsks[j].ent == ent) &&
             (mtOsCp.tskTbl[i]->tsks[j].inst == inst))
         {
            found = TRUE;
            break;
         }
      }
      if (found == TRUE)
         break;
   }
   
   if (!found)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      MTLOGERROR(ERRCLS_INT_PAR, EMT025, found, 
                 "Attempt to register a timer for a nonexistent task");
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */
      SUnlockMutex(mtOsCp.tmrTblMtx);
      RETVALUE(RFAILED);
   }

   /* reserve a slot in the timer table */
   for(index=0; index<MT_MAX_TIMER; index++)
   {
      if ((mtOsCp.tmrTbl[index]->ent == ENTNC) &&
          (mtOsCp.tmrTbl[index]->inst == INSTNC))
         break;
   }
   
   if(index == MT_MAX_TIMER)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT026, index, "Cannot find Timer Table Entry");
#endif /* ERRCLASS & ERRCLS_DEBUG */
      SUnlockMutex(mtOsCp.tmrTblMtx);
      RETVALUE(RFAILED);
   }
   else
      mtOsCp.tmrTblIdx++;

   tEnt = mtOsCp.tmrTbl[index];
   
   /* update timer table with new information */
   tEnt->timerId  = index;
   tEnt->ent      = ent;
   tEnt->inst     = inst;
   tEnt->tmrFnct  = tmrFnct;
   tEnt->dq       = &mtOsCp.tskTbl[i]->dq;
   tEnt->delay    = period;
   tEnt->sent     = 0;
   tEnt->drop     = 0;
   tEnt->received = 0;
   cmInitTimers(tEnt->timers, TMR_DEF_MAX);
   
   /* start the timer */
   arg.tq = mtOsCp.tmrCp.tmrTq;
   arg.tqCp = &mtOsCp.tmrCp.tmrTqCp;
   arg.timers = tEnt->timers;
   arg.cb = (PTR)tEnt;
   arg.evnt = TMR_DEF;
   arg.wait = 0;
   arg.tNum = NOTUSED;
   arg.max = TMR_DEF_MAX;
   arg.wait = tEnt->delay;
   cmPlcCbTq(&arg);

   /* done */
   SUnlockMutex(mtOsCp.tmrTblMtx);
   RETVALUE(ROK);
} /* end of SRegTmr */

/*
*
*       Fun:   SDeregTmr
*
*       Desc:  Deregister a timer associated with a certain entity
*              and instance
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SDeregTmr
(
Ent ent,                        /* entity */
Inst inst,                      /* instance */
S16 period,                     /* period */
PFS16 tmrFnct                   /* timer function */
)
#else
PUBLIC S16 SDeregTmr(ent, inst, period, tmrFnct)
Ent ent;                        /* entity */
Inst inst;                      /* instance */
S16 period;                     /* period */
PFS16 tmrFnct;                  /* timer function */
#endif
{
   REG1 S32 i;
   MtTmrEntry *tEnt;
   CmTmrArg arg;

   TRC2(SDeregTmr)

   /* lock timer table mutex */
   if(SLockMutex(mtOsCp.tmrTblMtx) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)      
      MTLOGERROR(ERRCLS_DEBUG, EMT027, mtOsCp.tmrTblMtx, 
                 "unable to aquire timer table mutex");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */      
      RETVALUE(RFAILED);
   }
   
   /* find the timer table entry we want to delete */
   for (i = 0; i < MT_MAX_TIMER; i++)
   {
      if (mtOsCp.tmrTbl[i]->tmrFnct == tmrFnct)
         break;
   }
   
   if (i == MT_MAX_TIMER)
   {
      /* oops, not found */
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT028, tmrFnct, "Timer to be deregistered not valid");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */      
      SUnlockMutex(mtOsCp.tmrTblMtx);
      RETVALUE(RFAILED);
   }
   
   /* okay, now stop the timer */
   arg.tq = mtOsCp.tmrCp.tmrTq;
   arg.tqCp = &mtOsCp.tmrCp.tmrTqCp;
   arg.timers = tEnt->timers;
   arg.cb = (PTR)tEnt;
   arg.evnt = TMR_DEF;
   arg.wait = 0;
   arg.tNum = NOTUSED;
   arg.max = TMR_DEF_MAX;
   arg.wait = tEnt->delay;
   cmRmvCbTq(&arg);

   /* reinitialize timer entry */
   tEnt->timerId = MT_TMRID_NULL;
   tEnt->ent = ENTNC;
   tEnt->inst = INSTNC;
   tEnt->dq = (MtDq*)NULLP;
   tEnt->tmrFnct = (PFS16)NULLP;      
   tEnt->delay     = 0;
   tEnt->sent      = 0;
   tEnt->drop      = 0;
   tEnt->received  = 0;
   mtOsCp.tmrTblIdx--;

   /* done */
   SUnlockMutex(mtOsCp.tmrTblMtx);
   RETVALUE(ROK);
} /* end of SDeregTmr */

/*
*
*       Fun:   SRegActvTsk
*
*       Desc:  This function is used to register an activation function
*              for the layer. The system services will invoke the
*              function passed to it whenever a task buffer is received.
*              The activation function will be used by the layer to receive
*              messages from other entities.  
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: SRegActvTsk supercedes SRegTsk and SRegPTsk.
*              Future implementations will use the 'prior' parameter
*
*       File:  ss_mtsp.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SRegActvTsk
(
Ent ent,                    /* entity */
Inst inst,                  /* instance */
Ttype ttype,                /* task type */
Prior prior,                /* task priority */
ActvTsk actvTsk             /* activate task function */
)
#else
PUBLIC S16 SRegActvTsk(ent, inst, ttype, prior, actvTsk)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
Ttype ttype;                /* task type */
Prior prior;                /* task priority */
ActvTsk actvTsk;            /* activate task function */
#endif
{
   U32 i;
   U32 j;
   U32 idx;
   MtOsCp *o;
   MtThrdFlags flags;

   TRC2(SRegActvTsk)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (actvTsk == NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT029, actvTsk, "activation task is null");
      RETVALUE(RFAILED);
   }
   if ((ttype != TTPERM) && (ttype != TTNORM))
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT030, ttype, "unsupported task type");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

   o = &mtOsCp;

   if (SLockMutex(o->tskTblMtx) !=ROK) /* lock task table */
      RETVALUE(RFAILED);
   
   /* make sure this is not a duplicate registration */
   for (i = 0; i < mtOsCp.tskTblIdx; i++)
   {
      for (j = 0; j < o->tskTbl[i]->tskCnt; j++)
         if ((ent == o->tskTbl[i]->tsks[j].ent) &&
             (inst == o->tskTbl[i]->tsks[j].inst))
         {
            SUnlockMutex(o->tskTblMtx); /* unlock task table */
            RETVALUE(RFAILED);
         }
   }

   /* reserve a slot in the task table. */
   idx = o->tskTblIdx;
   o->tskTblIdx++;

   if (o->tskTblIdx > MT_MAX_TASK)
   {
      SUnlockMutex(o->tskTblMtx); /* unlock task table */
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT031, o->tskTblIdx, "task table full");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);        /* no space left in task table */
   }
   
   /*
    * initialize demand queue for this task
    */
   if (SGetMutex(&o->tskTbl[idx]->dq.mtx) != ROK) /* get mutex */
   {
      SUnlockMutex(o->tskTblMtx); /* unlock task table */
      RETVALUE(RFAILED);
   }
   
   if (SLockMutex(o->tskTbl[idx]->dq.mtx) != ROK) /* lock dq */
   {
      SUnlockMutex(o->tskTblMtx); /* unlock task table */
      RETVALUE(RFAILED);
   }
   
   if (SGetCond(&o->tskTbl[idx]->dq.cond) != ROK)
   {
      SUnlockMutex(o->tskTbl[idx]->dq.mtx); /* unlock dq */
      SUnlockMutex(o->tskTblMtx); /* unlock task table */
      RETVALUE(RFAILED);
   }
   SInitQueue(&o->tskTbl[idx]->dq.bufQ);
   SUnlockMutex(o->tskTbl[idx]->dq.mtx); /* unlock dq */
   
   /* update task table with new information */
   o->tskTbl[idx]->index   = idx;

   /* initialize task entry */
   if (ttype == TTPERM)
      o->tskTbl[idx]->type = MT_TSK_PERM;
   else
      o->tskTbl[idx]->type = MT_TSK_NORM;
   o->tskTbl[idx]->count = 0;
   o->tskTbl[idx]->tskCnt = 0;
   o->tskTbl[idx]->tsks[o->tskTbl[idx]->tskCnt].ent = ent;
   o->tskTbl[idx]->tsks[o->tskTbl[idx]->tskCnt].inst = inst;
   o->tskTbl[idx]->tsks[o->tskTbl[idx]->tskCnt].actvTsk = actvTsk;
   o->tskTbl[idx]->tskCnt++;

   /*
    * each thread operates as a separate thread of control
    */

   /* thread creation flags */
   flags = (MT_THR_NEW_LWP |        /* bump concurrency */
            MT_THR_DETACHED);       /* detached (no lwp affinity) */
   

   /* get new thread */
   if (SGetThread(mtTskHndlr, flags, (Ptr)o->tskTbl[idx],
       &o->tskTbl[idx]->tId) != ROK)
   {
      SUnlockMutex(o->tskTblMtx);
      RETVALUE(RFAILED);
   }

   /* save the permanant task entity and instance */
   if (ttype == TTPERM)
   {
      /* permanent tasks are set to low priority */
      SSetThrdPrior(o->tskTbl[idx]->tId, MT_LOW_PRI);
      o->permTask = TRUE;
   }
   else
   {
      /* else normal priority */
      SSetThrdPrior(o->tskTbl[idx]->tId, MT_NORM_PRI);
   }

   /* release and return */
   SUnlockMutex(o->tskTblMtx);
   RETVALUE(ROK);
} /* end of SRegActvTsk */
 
  
/*
*
*       Fun:   Deregister Initialize, task buffer and timer
*
*       Desc:  This function is used to deregister the initialization,
*              activation and timer functions for a task.
*
*       Ret:   RFAILED - error
*
*       Notes: Unsupported
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SDeregInitTskTmr
(
Ent ent,                    /* entity */
Inst inst                   /* instance */
)
#else
PUBLIC S16 SDeregInitTskTmr(ent, inst)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
#endif
{
   TRC2(SDeregInitTskTmr)

   RETVALUE(RFAILED);
} /* end of SDeregInitTskTmr */

  
/*
*
*       Fun:   Exit Task
*
*       Desc:  This function exits from a task.
*
*       Ret:   ROK      - ok
*
*       Notes: Currently empty
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SExitTsk
(
void
)
#else
PUBLIC S16 SExitTsk()
#endif
{
   TRC2(SExitTsk)
   RETVALUE(ROK);
} /* end of SExitTsk */

  
/*
*
*       Fun:   Exit Interrupt
*
*       Desc:  This function exits from an interrupt.
*
*       Ret:   ROK      - ok
*
*       Notes: Currently empty
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SExitInt
(
void
)
#else
PUBLIC S16 SExitInt()
#endif
{
   TRC2(SExitInt)
   RETVALUE(ROK);
} /* end of SExitInt */

  
/*
*
*       Fun:   Hold Interrupt
*
*       Desc:  This function prohibits interrupts from being enabled until
*              release interrupt. This function should be called when
*              interrupts are disabled and prior to any call to system
*              services either by entry to an interrupt service routine or
*              by explicit call to disable interrupt.
*
*       Ret:   ROK      - ok
*
*       Notes: Currently empty
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SHoldInt
(
void
)
#else
PUBLIC S16 SHoldInt()
#endif
{
   TRC2(SHoldInt)

   RETVALUE(ROK);
} /* end of SHoldInt */

  
/*
*
*       Fun:   Release Interrupt
*
*       Desc:  This function allows interrupts to be enabled.
*
*       Ret:   ROK      - ok
*
*       Notes: Currently empty
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SRelInt
(
void
)
#else
PUBLIC S16 SRelInt()
#endif
{
   TRC2(SRelInt)

   RETVALUE(ROK);
} /* end of SRelInt */


/*
*
*       Fun:   SDisInt
*
*       Desc:  disable interrupts (per thread)
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: currently empty
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SDisInt
(
void
)
#else
PUBLIC INLINE S16 SDisInt()
#endif
{
   TRC2(SDisInt)

   RETVALUE(ROK);
} /* end of SDisInt */


/*
*
*       Fun:   SEnbInt
*
*       Desc:  enable interrupts (per thread)
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: currently empty
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SEnbInt
(
void
)
#else
PUBLIC INLINE S16 SEnbInt()
#endif
{
   
   TRC2(SEnbInt)

   RETVALUE(ROK);
} /* end of SEnbInt */


/*
*
*       Fun:   Get Vector
*
*       Desc:  This function gets the function address stored at the
*              specified interrupt vector.
*
*       Ret:   ROK      - ok
*
*       Notes: Currently empty
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetVect
(
VectNmb vectNmb,            /* vector number */
PIF *vectFnct               /* vector function */
)
#else
PUBLIC S16 SGetVect(vectNmb, vectFnct)
VectNmb vectNmb;            /* vector number */
PIF *vectFnct;              /* vector function */
#endif
{
   TRC2(SGetVect)

   UNUSED(vectNmb);
   UNUSED(vectFnct);
   
   RETVALUE(ROK);
} /* end of SGetVect */

  
/*
*
*       Fun:   Put Vector
*
*       Desc:  This function puts the function address at the
*              specified interrupt vector.
*
*       Ret:   ROK      - ok
*
*       Notes: This function actually manages UNIX signals which
*              function like hardware interrupts on UNIX platforms
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPutVect
(
VectNmb vectNmb,            /* vector number */
PIF vectFnct                /* vector function */
)
#else
PUBLIC S16 SPutVect(vectNmb, vectFnct)
VectNmb vectNmb;            /* vector number */
PIF vectFnct;               /* vector function */
#endif
{
   TRC2(SPutVect)

   RETVALUE(mtPutVect(vectNmb, (PFVOID)vectFnct));

} /* end of SPutVect */

  
/*
*
*       Fun:   SGetEntInst
*
*       Desc:  This function gets the current entity and instance.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: This function may be called by the OS
*              or layer1 hardware drivers
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SGetEntInst
(
Ent *ent,                    /* entity */
Inst *inst                   /* instance */
)
#else
PUBLIC S16 SGetEntInst(ent, inst)
Ent *ent;                    /* entity */
Inst *inst;                  /* instance */
#endif
{
   MtTskEntry **tskTbl;
   MtTsk *task;
   MtThrdId tId;
   U32 i;
   
   TRC1(SGetEntInst)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity pointer */
   if (!ent)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT032, ent, "Null entity pointer");
      RETVALUE(RFAILED);
   }
   /* check instance pointer */
   if (!inst)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT033, inst, "Null instance pointer");
      RETVALUE(RFAILED);
   }
#endif

   /* get the thread id */
   if (mtThrdSelf(&tId) != ROK)
      RETVALUE(RFAILED);  

   if (SLockMutex(mtOsCp.tskTblMtx) != ROK)
   {
      /* demand queue lock failed, ought oh! */
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT034, ERRZERO, "can't lock driver mutex");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }

   /* find the task associated with this thread id */
   tskTbl = mtOsCp.tskTbl;

   for (i=0; i < MT_MAX_TASK; i++)
   {
      if (tskTbl[i]->tId == tId)
         break;
   }

   if (i == MT_MAX_TASK)
      RETVALUE(RFAILED);

   /* there are multiple tasks associated with the thread id, but the root
    * task (1st task) is the one from which we should obtain the enity and
    * instance ids
    */
   task = tskTbl[i]->tsks;   
   *ent  = task->ent;  /* get current entity */
   *inst = task->inst; /* get current instance */

   SUnlockMutex(mtOsCp.tskTblMtx);
   RETVALUE(ROK);
} /* end of SGetEntInst */

  
/*
*
*       Fun:   SSetEntInst
*
*       Desc:  This function sets the current entity and instance.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: This function may be called by the OS
*              or layer1 hardware drivers
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SSetEntInst
(
Ent ent,                    /* entity */
Inst inst                   /* instance */
)
#else
PUBLIC S16 SSetEntInst(ent, inst)
Ent ent;                    /* entity */
Inst inst;                  /* instance */
#endif
{
   TRC1(SSetEntInst)

   RETVALUE(ROK);
} /* end of SSetEntInst */


/*
*
*       Fun:   SFndProcId
*
*       Desc:  This function finds the local processor id.
*
*       Ret:   local processor id
*
*       Notes: None
*
*       File:  ss_mtsp.c
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
   TRC1(SFndProcId)

   RETVALUE(mtOsCp.ownProcId);
} /* end of SFndProcId */

  
/*
*
*       Fun:   SSetProcId
*
*       Desc:  This function sets the local processor id.
*
*       Ret:   Void processor id
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PUBLIC Void SSetProcId
(
ProcId pId
)
#else
PUBLIC Void SSetProcId(pId)
ProcId pId;
#endif
{
   TRC1(SSetProcId)
   mtOsCp.ownProcId = pId;
} /* end of SSetProcId */


/*
*
*       Fun:   Task handler
*
*       Desc:  This function will pend on a particular message queue.
*              When a message arrives, an event in the first byte of 
*              this message will indicate that the message is a timer
*              message or task message.  If it's a timer message, an
*              identifier in the mesaage will indicate which timer has
*              expired.  The appropriate timer function will then be 
*              called.  If it's a task message, a user registered function
*              will then be invoked.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/

#ifdef ANSI
PRIVATE Void *mtTskHndlr
(
Ptr tskPtr
)
#else
PRIVATE Void *mtTskHndlr(tskPtr)
Ptr tskPtr;
#endif
{
   MtTskEntry *tsk;
   Buffer *mBuf;
   REG1 S32 i;
   U8 event;
   Pst pst;
   
   TRC2(mtTskHndlr)

   tsk = (MtTskEntry*)tskPtr;

   for (;;)                     /* infinite loop */
   {
      if (SLockMutex(tsk->dq.mtx) != ROK)
         continue;

      while(tsk->dq.bufQ.crntSize == 0) /* demand queue is empty */
         SCondWait(tsk->dq.mtx, tsk->dq.cond);

      /*
       * we have the demand queue lock?
       */
      
      if (SDequeueFirst(&mBuf, &tsk->dq.bufQ) != ROK)
      {
         SUnlockMutex(tsk->dq.mtx); /* release the demand queue */
         continue;
      }

      SUnlockMutex(tsk->dq.mtx); /* release the demand queue */

      /* okay, got a buffer */

      /* extract event information from incoming message */
      SUnpkU8(&event, mBuf);

      switch(event)
      {
         case MT_TMR_EVNT:
         {
            S32 timerId;
               
            /* extract timer-id information from incoming message */
            SUnpkS32(&timerId, mBuf);
            
            /* timerId is the index into the timer table */
#if (ERRCLASS & ERRCLS_DEBUG)
            if (mtOsCp.tmrTbl[timerId]->timerId != timerId)
            {
               SPutMsg(mBuf);
               MTLOGERROR(ERRCLS_DEBUG, EMT035, timerId, 
                          "timerId out of range");
               continue;
            }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
            /* invoke the timer routine */ 
            if (mtOsCp.tmrTbl[timerId]->tmrFnct != NULLP)
            {
               /* increment receive counter */
               mtOsCp.tmrTbl[timerId]->received++;
               mtOsCp.tmrTbl[timerId]->tmrFnct();
            }
            else
            {
               /* This is the case, where a timer message is sitting on a
                * task's demand queue.  Before this timer message is 
                * processed, the user (eg Q933) deregisters the timer
                * (SDeregTmr).  The deregistration event is processed before
                * the timer message event
                */

               /* increment counter for number of dropped timer events */
               mtOsCp.tmrTbl[timerId]->drop++;
            }
            
            /* deallocate message */
            SPutMsg(mBuf);
            SThreadYield();     /* timer's yield */
            break;
         }
         case MT_MSG_EVNT:
            /* extract routing information from incoming message */
            cmUnpkPst(&pst, mBuf);
            pst.selector = 0;
            
            if (tsk->type == TTNORM)
            {
               Bool done;
               
               /* find the correct tsk */
               done = FALSE;
               for (i = 0; i < tsk->tskCnt; i++)
               {
                  if (pst.dstEnt == tsk->tsks[i].ent && 
                      pst.dstInst == tsk->tsks[i].inst)
                  {
                     tsk->tsks[i].actvTsk(&pst, mBuf);
                     done = TRUE;
                     break;
                  }
               }

               if (!done)
               {
#if (ERRCLASS & ERRCLS_DEBUG)
                  MTLOGERROR(ERRCLS_DEBUG, EMT036, done, "task not found");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
               }
               else
                  tsk->count++;
               continue;
            }
            else if (tsk->type == TTPERM)
            {
               /*
                * We need to distinguish between messages used to keep
                * permanent tasks moving, and messages that are actually
                * sent to permanent tasks from other tasks
                */
               Bool perm;
#if (ERRCLASS & ERRCLS_DEBUG)
               if (tsk->tskCnt != 1)
                  MTLOGERROR(ERRCLS_DEBUG, EMT037, tsk->tskCnt, 
                             "too many permanent tasks registered");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

               /* call the permanent task function */
               perm = FALSE;
               if (mBuf->t.msg.pool == MT_TMR_POOL)
                  perm = TRUE;
               
               tsk->tsks[0].actvTsk(&pst, mBuf); 
               
               if (!perm)
               {
                  /* we can tell if this is a permanent task keep alive 
                   * message by checking the pool id. Normal tasks sending
                   * messages to a permanent task won't use the timer pool
                   *
                   * if this messages was not using the timer pool than
                   * it came from a normal task and we shouldn't generate
                   * a keep alive message
                   *
                   */
                  continue;
               }               
GETBUF:
               if (SGetMsg(DFLT_REGION, MT_TMR_POOL, &mBuf) != ROK)
               {
                  /* if this fails, we're in trouble. The permanent task
                   * will no longer run without this keep alive message
                   * humm, what to do? I don't like it, but let's go into
                   * a tight loop here trying to get a buffer
                   */
                  goto GETBUF;
               }
               pst.dstEnt  = tsk->tsks[0].ent;
               pst.dstInst = tsk->tsks[0].inst;
               pst.srcEnt  = tsk->tsks[0].ent;
               pst.srcInst = tsk->tsks[0].inst;
               if (SPstTsk(&pst, mBuf) != ROK) /* post when we're done */
               {
                  SPutMsg(mBuf);
                  goto GETBUF;
               }   
               SThreadYield();       /* yield to any other thread */
            }
            break;
         default:
#if (ERRCLASS & ERRCLS_DEBUG)
            MTLOGERROR(ERRCLS_DEBUG, EMT038, event, "Illegal Event");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */            
            break;
      }
      
      /* increment activity counter */
      tsk->count++;

   }
   
   /* NOTREACHED */
}  /* end of mtTskHndlr */
  

/*
*
*       Fun:   Timer Block Placement handler
*
*       Desc:  This function will pend on a particular message queue.
*              When a message arrives, the timer id is extracted.  The
*              timer id points to the timer control block which is then
*              placed back on the common timing queue.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/

#ifdef ANSI
PRIVATE Void *mtTmrPlaceHndlr
(
Ptr tmrPtr
)
#else
PRIVATE Void *mtTmrPlaceHndlr(tmrPtr)
Ptr tmrPtr;
#endif
{
   MtTmrEntry **tmrTbl;
   MtTmrPlace *tmrPlace;
   S32 timerId;
   Buffer *mBuf;
   CmTmrArg arg;
   MtTmrEntry *tEnt;
   
   TRC2(mtTmrPlaceHndlr)

   tmrTbl = (MtTmrEntry**)tmrPtr;
   tmrPlace = &mtOsCp.tmrPlace;
   
   for (;;)                     /* infinite loop */
   {
      if (SLockMutex(tmrPlace->dq.mtx) != ROK)
         continue;

      while(tmrPlace->dq.bufQ.crntSize == 0) /* demand queue is empty */
         SCondWait(tmrPlace->dq.mtx, tmrPlace->dq.cond);

      /*
       * we have the demand queue lock?
       */
      
      if (SDequeueFirst(&mBuf, &tmrPlace->dq.bufQ) != ROK)
      {
         SUnlockMutex(tmrPlace->dq.mtx); /* release the demand queue */
#if (ERRCLASS & ERRCLS_DEBUG)
         MTLOGERROR(ERRCLS_DEBUG, EMT039, ERRZERO, "can't dequeue buffer");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
         continue;
      }

      SUnlockMutex(tmrPlace->dq.mtx); /* release the demand queue */

      /* okay, got a buffer */

      /* extract timer-id information from incoming message */
      SUnpkS32(&timerId, mBuf);

      /* deallocate message */
      SPutMsg(mBuf);
            
      /* timerId is the index into the timer table */
#if (ERRCLASS & ERRCLS_DEBUG)
      if (tmrTbl[timerId]->timerId != timerId)
      {
         MTLOGERROR(ERRCLS_DEBUG, EMT040, timerId, "timerId out of range");
               continue;
      }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

      /* lock timer table mutex */
      if(SLockMutex(mtOsCp.tmrTblMtx) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)      
         MTLOGERROR(ERRCLS_DEBUG, EMT041, mtOsCp.tmrTblMtx, 
                    "unable to aquire timer table mutex");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */      
         continue;
      }

      /* place the timer control block on the timing queue */ 
      tEnt = tmrTbl[timerId];
      
      if (tmrTbl[timerId]->tmrFnct != NULLP)
      {
         /* re-start the timer */
         arg.tq = mtOsCp.tmrCp.tmrTq;
         arg.tqCp = &mtOsCp.tmrCp.tmrTqCp;
         arg.timers = tEnt->timers;
         arg.cb = (PTR)tEnt;
         arg.evnt = TMR_DEF;
         arg.wait = 0;
         arg.tNum = NOTUSED;
         arg.max = TMR_DEF_MAX;
         arg.wait = tEnt->delay;
         cmPlcCbTq(&arg);
      }

      SUnlockMutex(mtOsCp.tmrTblMtx);

      if (tmrPlace->dq.bufQ.crntSize == 0) /* demand queue is empty */
      {
         SThreadYield();     /* timer's yield */
      }
   }
   
   /* NOTREACHED */
}  /* end of mtTmrPlaceHndlr */

/*
*
*       Fun:   Post Task
*
*       Desc:  This function posts a task buffer to a task.
*
*       Ret:   ROK      - ok
*
*       Notes: SPstTsk will replace SPostTsk
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SPstTsk
(
Pst *pst,                   /* post structure */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SPstTsk(pst, mBuf)
Pst *pst;                   /* post structure */
Buffer *mBuf;               /* message buffer */
#endif
{
   REG1 S32  i;
   REG2 S32  j;
   Bool found;

   TRC2(SPstTsk)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (!mBuf || mBuf->bufType != BMSG)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT042, mBuf, "bad message buffer");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR) */

#ifdef ENB_RELAY
   /*
    * check for remote 
    */
   if (pst->dstProcId != mtOsCp.ownProcId)
   {
      found = FALSE;
      for (i = 0; i < mtOsCp.drvrTblIdx; i++)
      {
         if (pst->dstProcId >= mtOsCp.drvrTbl[i]->low &&
             pst->dstProcId <= mtOsCp.drvrTbl[i]->high)
         {
            found = TRUE;
            break;
         }
      }

#if (ERRCLASS & ERRCLS_DEBUG)
      if (found == FALSE)
      {
         MTLOGERROR(ERRCLS_DEBUG, EMT043, pst->dstProcId, 
                    "No relay channel found");
         RETVALUE(RFAILED);
      }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */   

      /* store routing information into the message */
      pst->route = mtOsCp.drvrTbl[i]->inst;
      if (cmPkPst(pst, mBuf) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         MTLOGERROR(ERRCLS_DEBUG, EMT044, -1, "unable to pack post");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      
      
      if (SLockMutex(mtOsCp.drvrTbl[i]->dq.mtx) != ROK)
      {
         /* demand queue lock failed, ought oh! */
         SPutMsg(mBuf);            /* drop message */
#if (ERRCLASS & ERRCLS_DEBUG)
         MTLOGERROR(ERRCLS_DEBUG, EMT045, i, "can't lock driver mutex");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
         RETVALUE(RFAILED);
      }

      /* got mutex */
      SQueueLast(mBuf, &mtOsCp.drvrTbl[i]->dq.bufQ);
      
      if (mtOsCp.drvrTbl[i]->dq.bufQ.crntSize == 1) /* that means it was 0 */
         SCondSignal(mtOsCp.drvrTbl[i]->dq.cond);  /* snd sig on condition */
      
      SUnlockMutex(mtOsCp.drvrTbl[i]->dq.mtx);

      RETVALUE(ROK);
   }
#endif /* ENB_RELAY */

   /* find the destination's message queue */ 
  
   /*
    * anyone with an idea as to how to avoid this linear search,
    * I'd love to hear from you!!!
    *
    * send e-mail to tech_support@trillium.com
    */
         
   found = FALSE;
   for (i = 0; i < mtOsCp.tskTblIdx; i++)
   {
      for (j = 0; j < mtOsCp.tskTbl[i]->tskCnt; j++)
         if ((mtOsCp.tskTbl[i]->tsks[j].ent == pst->dstEnt) &&
             (mtOsCp.tskTbl[i]->tsks[j].inst == pst->dstInst))
         {
            found = TRUE;
            break;
         }
      if (found == TRUE)
         break;
   }

#if (ERRCLASS & ERRCLS_DEBUG)
   if (found == FALSE)
   {
      MTLOGERROR(ERRCLS_DEBUG, EMT046, pst->dstEnt, 
                 "No destination task found");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */   
   
   /* store routing information into the message */
   if (cmPkPst(pst, mBuf) != ROK)
   {
      SPutMsg(mBuf);            /* drop message */
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT047, pst, "unable to pack post");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }
   
   
   /* pack normal task message event */
   if (SPkU8((U8)MT_MSG_EVNT, mBuf ) != ROK)
   {
      SPutMsg(mBuf);            /* drop message */
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT048, mBuf, "unable to pack message event");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }      

   if (SLockMutex(mtOsCp.tskTbl[i]->dq.mtx) != ROK)
   {
      /* demand queue lock failed, ought oh! */
      SPutMsg(mBuf);            /* drop message */
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT049, i, "unable to lock task dq mutex");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }

   /* got mutex */
   SQueueLast(mBuf, &mtOsCp.tskTbl[i]->dq.bufQ);
   
   if (mtOsCp.tskTbl[i]->dq.bufQ.crntSize == 1) /* that means it was zero */
      SCondSignal(mtOsCp.tskTbl[i]->dq.cond);   /* send signal on condition */
   
   SUnlockMutex(mtOsCp.tskTbl[i]->dq.mtx); /* unlock demand queue */

   RETVALUE(ROK);
} /* end of SPstTsk */


/*
*
*       Fun:   SChkRes
*
*       Desc:   check resources
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SChkRes
(
Region region,
Pool pool,
Status *status
)
#else
PUBLIC S16 SChkRes(region, pool, status)
Region region;
Pool pool;
Status *status;
#endif
{

   TRC2(SChkRes)

   /* 
    *  10 = 100% of buffers available.  
    *   5 =  50% of buffers available.
    *   etc.
    */

   if (SLockMutex(mtOsCp.dPool[pool].mtx) != ROK)
      RETVALUE(RFAILED);
   
   *status = (Status)
             (((Status)mtOsCp.dPool[pool].bufQ.crntSize * (Status)10) / 
              (Status)mtPoolInfo[pool].nmbBufs);
                      
   SUnlockMutex(mtOsCp.dPool[pool].mtx);
   
   RETVALUE(ROK);
} /* end of SChkRes */


/*
*
*       Fun:   mtTmrEvnt
*
*       Desc:  process timer event
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: send a timer message to a task
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC Void mtTmrEvnt
(
PTR tCb,                        /* control block */
S16 evnt                        /* event */
)
#else
PUBLIC Void mtTmrEvnt(tCb, evnt)
PTR tCb;                        /* control block */
S16 evnt;                       /* event */
#endif
{
   Buffer *mBuf;
   Buffer *mBufTpt;             /* used by the Timer Placement Thread */
   MtTmrEntry *tEnt;
   MtTmrPlace *tmrPlace;
   
   TRC2(mtTmrEvnt)

   tEnt = (MtTmrEntry*)tCb;
   if (SGetMsg(DFLT_REGION, MT_TMR_POOL, &mBuf) != ROK)
      RETVOID;
   if (SPkS32(tEnt->timerId, mBuf) != ROK)
      RETVOID;
   if (SPkU8((U8)MT_TMR_EVNT, mBuf) != ROK)
      RETVOID;

   /* circumvent SPstTsk because we've cached the demand
    * queue and we don't want to pack the pst structure
    */
      
   if (SLockMutex(tEnt->dq->mtx) != ROK)
   {
      /* demand queue lock failed, ought oh! */
      SPutMsg(mBuf);            /* drop message */
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT050, tEnt->timerId, 
                    "can't lock task demand queue (timer)");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVOID;                  /* return */
   }
      
   /* got mutex */
   SQueueLast(mBuf, &tEnt->dq->bufQ);
      
   if (tEnt->dq->bufQ.crntSize == 1) /* that means it was zero */
      SCondSignal(tEnt->dq->cond);   /* send signal on condition */
      
   SUnlockMutex(tEnt->dq->mtx);

   /* send message to the Timer Placement thread to re-start the timer */
   tmrPlace = &(mtOsCp.tmrPlace);

   if (SGetMsg(DFLT_REGION, MT_TMR_POOL, &mBufTpt) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT051, MT_TMR_POOL, 
                 "can't allocate message ");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVOID;
   }      

   if (SPkS32(tEnt->timerId, mBufTpt) != ROK)
   {
      SPutMsg(mBufTpt);            /* drop message */
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT052, tEnt->timerId, 
                 "can't pack message ");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVOID;
   }
         
   if (SLockMutex(tmrPlace->dq.mtx) != ROK)
   {
      /* demand queue lock failed, ought oh! */
      SPutMsg(mBufTpt);            /* drop message */
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT053, tEnt->timerId, 
                    "can't lock task demand queue (timer)");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVOID;                  /* return */
   }
      
   /* got mutex */
   if (SQueueLast(mBufTpt, &tmrPlace->dq.bufQ) != ROK)
   {
      SUnlockMutex(tmrPlace->dq.mtx);
      SPutMsg(mBufTpt);            /* drop message */
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT054, ERRZERO, 
                 "can't queue buffer");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVOID;
   }

   if (tmrPlace->dq.bufQ.crntSize == 1) /* it means it was zero */
      SCondSignal(tmrPlace->dq.cond);   /* send signal on condition */

   if (SUnlockMutex(tmrPlace->dq.mtx) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT055, tEnt->timerId, 
                    "can't lock task demand queue (timer)");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVOID;                  /* return */
   }

   RETVOID;
} /* end of mtTmrEvnt */


/*
*
*       Fun:   SGetStrtIdx
*
*       Desc:  This function returns the starting index at which data
*              should be placed within a buffer.
*
*       Ret:   ROK
*              RFAILED  - failed, general
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetStrtIdx
(
Region region,              /* region */
Pool pool,                  /* pool */
S16 *idx                    /* Pointer to value */
)
#else
PUBLIC S16 SGetStrtIdx(region, pool, idx)
Region region;              /* region */
Pool pool;                  /* pool */
S16 *idx;                   /* Pointer to Index */
#endif
{
    TRC1(SGetStrtIdx)

#if (ERRCLASS & ERRCLS_INT_PAR)
    if( pool >= MT_NMB_MSG_POOL)
    {
       MTLOGERROR(ERRCLS_INT_PAR, EMT056, ERRZERO, 
                  "Invalid Pool Number Passed");
       RETVALUE(RFAILED);
    }
    if (idx == NULLP)
    {
        MTLOGERROR(ERRCLS_INT_PAR, EMT057, ERRZERO, 
                   "Null Pointer(idx) Passed");
        RETVALUE(RFAILED);
    }
#endif /* ERRCLASS & ERRCLS_INT_PAR */
    *idx = mtPoolInfo[pool].strtIdx;
    RETVALUE(ROK);
}/* end of SGetStrtIdx */
  

/*
*
*       Fun:   SGetEndIdx
*
*       Desc:  This function returns the end index at which data
*              should be placed within a buffer.
*
*       Ret:   ROK
*              RFAILED  - failed, general
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetEndIdx
(
Region region,              /* region */
Pool pool,                  /* pool */
S16 *idx                    /* Pointer to value */
)
#else
PUBLIC S16 SGetEndIdx(region, pool, idx)
Region region;              /* region */
Pool pool;                  /* pool */
S16 *idx;                   /* Pointer to Index */
#endif
{
    TRC1(SGetEndIdx)
#if (ERRCLASS & ERRCLS_INT_PAR)
    if( pool >= MT_NMB_MSG_POOL)
    {
        MTLOGERROR(ERRCLS_INT_PAR, EMT058, ERRZERO, 
                   "Invalid Pool Number Passed");
        RETVALUE(RFAILED);
    }
    if (idx == NULLP)
    {
        MTLOGERROR(ERRCLS_INT_PAR, EMT059, ERRZERO, 
                   "Null Pointer(idx) Passed");
        RETVALUE(RFAILED);
    }
#endif /* ERRCLASS & ERRCLS_INT_PAR */
    *idx = mtPoolInfo[pool].endIdx;
    RETVALUE(ROK);
}/* end of SGetEndIdx */


/*
*
*       Fun:   SGetDBufSiz
*
*       Desc:  This function returns the number of bytes a data 
*              buffer can hold.
*
*       Ret:   ROK
*              RFAILED  - failed, general
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetDBufSiz
(
Region region,              /* region */
Pool pool,                  /* pool */
S16 *size                    /* Pointer to value */
)
#else
PUBLIC S16 SGetDBufSiz(region, pool, size)
Region region;              /* region */
Pool pool;                  /* pool */
S16 *size;                  /* Pointer to Index */
#endif
{
    TRC1(SGetDBufSiz)
#if (ERRCLASS & ERRCLS_INT_PAR)
    if( pool >= MT_NMB_MSG_POOL)
    {
        MTLOGERROR(ERRCLS_INT_PAR, EMT060, ERRZERO, 
                   "Invalid Pool Number Passed");
        RETVALUE(RFAILED);
    }
    if (size == NULLP)
    {
        MTLOGERROR(ERRCLS_INT_PAR, EMT061, ERRZERO, 
                   "Null Pointer(size) Passed");
        RETVALUE(RFAILED);
     }
#endif /* ERRCLASS & ERRCLS_INT_PAR */
    *size = mtPoolInfo[pool].dSize;
    RETVALUE(ROK);
}/* end of SGetDBufSiz */
 
  
/*
*
*       Fun:   SGetStrtPad
*
*       Desc:  This function returns the number of data bytes left
*              unused at the start of the data portion of a data
               buffer.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetStrtPad
(
Region region,              /* region */
Pool pool,                  /* pool */
S16 *pad                    /* Pointer to value */
)
#else
PUBLIC S16 SGetStrtPad(region, pool, pad)
Region region;              /* region */
Pool pool;                  /* pool */
S16 *pad;                   /* Pointer to Index */
#endif
{
    TRC1(SGetDBufSiz)

#if (ERRCLASS & ERRCLS_INT_PAR)
    if( pad == NULLP)
    {
        MTLOGERROR(ERRCLS_INT_PAR, EMT062, ERRZERO, 
                   "Null Pointer(pad) Passed");
        RETVALUE(RFAILED);
    }
#endif /* ERRCLASS & ERRCLS_INT_PAR */
    /* Start Index itself takes care of the Pad */
    *pad = 0;
    RETVALUE(ROK);
}/* end of SGetDBufSiz */

#ifdef ENB_RELAY

/*
*
*       Fun:   SRegDrvrTsk
*
*       Desc:  register driver task
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegDrvrTsk
(
Inst inst, 
ProcId low, 
ProcId high, 
ActvTsk actvTsk, 
ISTsk isTsk
)
#else
PUBLIC S16 SRegDrvrTsk(Inst inst, ProcId low, ProcId high, ActvTsk actvTsk, 
                       ISTsk isTsk)
Inst inst; 
ProcId low; 
ProcId high;
ActvTsk actvTsk;
ISTsk isTsk;
#endif
{
   U32 i;
   U32 idx;
   MtOsCp *o;
   MtThrdFlags flags;

   TRC2(SRegDrvrTsk)

   o = &mtOsCp;

   /* lock driver table mutex */
   if (SLockMutex(o->drvrTblMtx) != ROK)
      RETVALUE(RFAILED);
   
   /* make sure this is not a duplicate registration */
   for (i = 0; i < mtOsCp.drvrTblIdx; i++)
   {
      if (inst == o->drvrTbl[i]->inst)
         RETVALUE(ROK);
   }

   /* reserve a slot in the task table. */
   idx = o->drvrTblIdx;
   o->drvrTblIdx++;

   if (o->drvrTblIdx > MT_MAX_DRVR)
   {
      SUnlockMutex(o->drvrTblMtx); /* unlock task table */
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT063, o->drvrTblIdx, "driver task table full");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */      
      RETVALUE(RFAILED);
   }
   
   /*
    * initialize demand queue for this task
    */
   if (SGetMutex(&o->drvrTbl[idx]->dq.mtx) != ROK) /* get mutex */
   {
      o->drvrTblIdx--;
      RETVALUE(RFAILED);
   }
   
   if (SLockMutex(o->drvrTbl[idx]->dq.mtx) != ROK) /* lock dq */
   {
      o->drvrTblIdx--;
      RETVALUE(RFAILED);
   }
   
   
   if (SGetCond(&o->drvrTbl[idx]->dq.cond) != ROK)
   {
      SUnlockMutex(o->drvrTbl[idx]->dq.mtx); /* unlock dq */
      SUnlockMutex(o->drvrTblMtx); /* unlock task table */
      o->drvrTblIdx--;   
      RETVALUE(RFAILED);
   }

   SInitQueue(&o->drvrTbl[idx]->dq.bufQ);
   SUnlockMutex(o->drvrTbl[idx]->dq.mtx); /* unlock dq */
   
   /* update task table with new information */
   o->drvrTbl[idx]->index   = idx;

   o->drvrTbl[idx]->inst = inst;
   o->drvrTbl[idx]->low = low;
   o->drvrTbl[idx]->high = high;
   o->drvrTbl[idx]->count = 0;
   o->drvrTbl[idx]->actvTsk = actvTsk;

   flags = (MT_THR_NEW_LWP |        /* bump concurrency */
            MT_THR_DETACHED);       /* detached (no join) */
   
   if (SGetThread(mtDrvrHndlr, flags, (Ptr)o->drvrTbl[idx],
       &o->drvrTbl[idx]->tId) != ROK)
   {
      SUnlockMutex(o->tskTblMtx);
      o->drvrTblIdx--;
      o->drvrTbl[idx]->tId       = MT_THRDID_NULL;
      o->drvrTbl[idx]->count     = 0;
      o->drvrTbl[idx]->inst      = INSTNC;
      o->drvrTbl[idx]->low       = PROCIDNC;
      o->drvrTbl[idx]->high      = PROCIDNC;
      o->drvrTbl[idx]->actvTsk   = (ActvTsk)NULLP;
#if (ERRCLASS & ERRCLS_DEBUG)      
      MTLOGERROR(ERRCLS_DEBUG, EMT064, idx, "failed to get thread");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */
      RETVALUE(RFAILED);
   }

   SSetThrdPrior(o->drvrTbl[idx]->tId, MT_NORM_PRI);

   SUnlockMutex(o->drvrTblMtx);
   
   RETVALUE(ROK);
} /* end of SRegDrvrTsk */


/*
*
*       Fun:   mtInitDrvr
*
*       Desc:  Initialize the static driver table for service.
*
*       Ret:   ROK      - ok
*
*       Notes: This function should *only* be invoked once.
*
*       File:  ss_mtsp.c
*
*/
 
#ifdef ANSI
PUBLIC S16 mtInitDrvr
(
void
)
#else
PUBLIC S16 mtInitDrvr()
#endif
{
   U32 i;
   
   TRC2(mtInitDrvr)

   if (SGetMutex(&mtOsCp.drvrTblMtx) != ROK)
      RETVALUE(RFAILED);
   
   if (SLockMutex(mtOsCp.drvrTblMtx) != ROK)
      RETVALUE(RFAILED);
   
   /* reset index variable */ 
   mtOsCp.drvrTblIdx = 0; 
 
   /* clear task table */ 
   for (i = 0; i < MT_MAX_DRVR; i++) 
   {  
      if (SGetSBuf(DFLT_REGION, DFLT_POOL, (Data**)&mtOsCp.drvrTbl[i], 
                   sizeof(MtDrvrEntry)) != ROK)
      {
         SUnlockMutex(mtOsCp.drvrTblMtx);
         RETVALUE(RFAILED);
      }
      
      mtOsCp.drvrTbl[i]->index     = i;
      /* mtOsCp.drvrTbl[i]->dq     = 0; */
      mtOsCp.drvrTbl[i]->tId       = MT_THRDID_NULL;
      mtOsCp.drvrTbl[i]->count     = 0;
      mtOsCp.drvrTbl[i]->inst      = INSTNC;
      mtOsCp.drvrTbl[i]->low       = PROCIDNC;
      mtOsCp.drvrTbl[i]->high      = PROCIDNC;
      mtOsCp.drvrTbl[i]->actvTsk   = (ActvTsk)NULLP;

   }  
   SUnlockMutex(mtOsCp.drvrTblMtx);
   RETVALUE(ROK);
}  /* end of mtInitDrvr */


/*
*
*       Fun:   Driver handler
*
*       Desc:  This function will pend on a particular message queue.
*              When a message arrives, an event in the first byte of 
*              this message will indicate that the message is a timer
*              message or task message.  If it's a timer message, an
*              identifier in the mesaage will indicate which timer has
*              expired.  The appropriate timer function will then be 
*              called.  If it's a task message, a user registered function
*              will then be invoked.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/

#ifdef ANSI
PRIVATE Void *mtDrvrHndlr
(
Ptr tskPtr
)
#else
PRIVATE Void *mtDrvrHndlr(tskPtr)
Ptr tskPtr;
#endif
{
   MtDrvrEntry *tsk;
   Buffer *mBuf;
   Pst pst;
   
   TRC2(mtDrvrHndlr)

   tsk = (MtDrvrEntry*)tskPtr;

   for (;;)                     /* infinite loop */
   {
      if (SLockMutex(tsk->dq.mtx) != ROK)
         continue;

      while(tsk->dq.bufQ.crntSize == 0) /* demand queue is empty */
         SCondWait(tsk->dq.mtx, tsk->dq.cond);

      /*
       * we have the demand queue lock?
       */
      
      if (SDequeueFirst(&mBuf, &tsk->dq.bufQ) != ROK)
      {
         SUnlockMutex(tsk->dq.mtx); /* release the demand queue */
         continue;
      }

      SUnlockMutex(tsk->dq.mtx); /* release the demand queue */

      /* okay, got a buffer */

      /* extract routing information from incoming message */
      cmUnpkPst(&pst, mBuf);
      
      tsk->actvTsk(&pst, mBuf);
      tsk->count++;
   }
   
   /* NOTREACHED */
}  /* end of mtDrvrHndlr */
#endif /* ENB_RELAY */

#ifdef CONAVL

/*
*
*       Fun:   mtInitCon
*
*       Desc:  initialize console
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: Initialize console
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PRIVATE S16 mtInitCon
(
void
)
#else
PRIVATE S16 mtInitCon()
#endif
{
   MtThrdFlags flags;
#ifndef CONSTDIO
   struct termios tio;
#endif /* CONSTDIO */

   TRC2(mtInitCon)

   conInFp = (FILE *)stdin;     /* use standard input  */
   conOutFp = (FILE *)stdout;   /* use standard output */

#ifndef CONSTDIO
   /* 
    * Configure the input to not block and not buffer 
    */

   /* 
    * get the current terminal settings 
    */
   if(ioctl(fileno(conInFp), TCGETS, &tio) < 0)
      RETVALUE(RFAILED);
    
   /* 
    * Disable canonical input processing 
    */
   tio.c_lflag     &= ~ICANON;
   tio.c_cc[VMIN]  = 0;
   tio.c_cc[VTIME] = 0;
 
   /*
    * set the new terminal settings
    */
   if(ioctl(fileno(conInFp), TCSETS, &tio) < 0)
      RETVALUE(RFAILED);
#endif /* CONSTDIO */

   /*
    * input is read only and blocks!
    */

   flags = (MT_THR_NEW_LWP |        /* bump concurrency */
            MT_THR_DETACHED);       /* detached (no join) */
   
   if (SGetThread(mtRdConHndlr, flags, (Ptr)0, &mtOsCp.rdConThrdId) != ROK)
   {
      conInFp = (FILE*)NULLP;
      conOutFp = (FILE*)NULLP;
      RETVALUE(RFAILED);
   }

   /* thread exists,
    * set the priority to normal (maybe low?)
    */
   SSetThrdPrior(mtOsCp.rdConThrdId, MT_NORM_PRI);

   /* okay, we have two file descriptors.
    * 
    * The first is the reader.
    * It has its own thread which will block on input
    * 
    * The second is ther writer.
    * We do not synchronize the writes as the tty driver should
    * handle this.
    */
   RETVALUE(ROK);
} /* end of mtInitCon */


/*
*
*       Fun:   mtRdConHndlr
*
*       Desc:  read the console
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: This is the task thread for reading the console.
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PRIVATE Void *mtRdConHndlr
(
Ptr unused                        /* unused */
)
#else
PRIVATE Void *mtRdConHndlr(unused)
Ptr unused;                     /* unused */
#endif
{
   Data data;
   S32 read_len;
   S32 poll_val;
   struct pollfd fds;
   Bool err;
   
   TRC2(mtRdConHndlr)

   err = FALSE;
   for (;;)
   {
      if (conInFp == (FILE*)NULLP)          /* disabled read file descriptor */
      {
         SThreadExit(0);
         RETVALUE((Void*)RFAILED);
      }
      
      fds.fd = fileno(conInFp);
      fds.events = POLLRDNORM;

      poll_val = poll(&fds, 1, (int) -1); /* block waiting for input */
      if (poll_val < 0)
      {
         if (errno == EINTR)
            continue;
#if (ERRCLASS & ERRCLS_DEBUG)
         MTLOGERROR(ERRCLS_DEBUG, EMT065, errno, "poll failed");
#endif /* (ERRCLASS & ERRCLS_DEBUG) */         
      }   

      
      /* read a single byte */
      if ((read_len = fread((void *)&data, 1, 1, conInFp)) != 1) 
      {
         if (err)
         {
            /* we've been here, disable input */
            conInFp = (FILE*)NULLP;  /* just in case, disable the input fd */
            SThreadExit(0);
            RETVALUE((Void*)RFAILED);
         }
         
         err = TRUE;
         continue;
      }
      
      rdConQ(data);           /* call rdConQ for the system service user */
   }

} /* end of mtRdConHndlr */

#endif /* CONAVL */

  
/*
*
*       Fun:   SGetOpt
*
*       Desc:  get options from command line
*
*       Ret:   option  - success
*              '?'     - fail
*              EOF     - end of options
*
*       Notes: handles command lines like the following
*
*              if opts = "abc:d" 
*                 then command line should look like this...
*                    -a foo -b foo1 -c -d foo
*
*              code usage:
*
*              while ((ret = SGetOpt(msArgc, msArgv, "ls")) != EOF )
*              {
*                 switch(ret)
*                 {
*                    case 'l':
*                       nloops = atoi(msArgv[msOptInd]);
*                       break;
*                    case 's':
*                       state1 = atoi(msArgv[msOptInd]);
*                    case '?':
*                    default:
*                       break;
*                 }
*              }
*
*       File:  ss_mtsp.c
*
*/

#ifdef ANSI
PUBLIC S16 SGetOpt
(
int argc,                   /* argument count */
char **argv,                /* argument value */
char *opts                  /* options */
)
#else
PUBLIC S16 SGetOpt(argc, argv, opts)
int argc;                   /* argument count */
char **argv;                /* argument value */
char *opts;                 /* options */
#endif
{
#ifndef NOCMDLINE
   S16 sp;
   S16 c;
   S8 *cp;
#endif /* NOCMDLINE */

   TRC1(SGetOpt)

#ifdef NOCMDLINE
   UNUSED(argc);
   UNUSED(argv);
   UNUSED(opts);
#endif /* NOCMDLINE */

#ifdef NOCMDLINE
   RETVALUE(EOF);
#else
   sp = 1;
   if (sp == 1)
      if (ssOptInd >= (S16) argc || argv[ssOptInd][0] == '\0')
         RETVALUE(EOF);
      else
      {
         if (!strcmp(argv[ssOptInd], "--"))
         {
            ssOptInd++;
            RETVALUE(EOF);
         }
         else if (argv[ssOptInd][0] != '-')
         {
            ssOptInd++;
            RETVALUE('?');
         }
      }
      ssOptOpt = c = argv[ssOptInd][sp];
      if ( c == ':' || (cp = (S8*)strchr(opts, c)) == (S8 *)NULLP )
      {
         if (argv[ssOptInd][++sp] == '\0')
         {
            ssOptInd++;
            sp = 1;
         }
         RETVALUE('?');
      }
      if (*++cp == ':')
      {
         if (argv[ssOptInd][sp+1] != '\0')
            ssOptArg = &argv[ssOptInd++][sp+1];
         else
         {
            if (++ssOptInd >= (S16) argc)
            {
               sp = 1;
               RETVALUE('?');
            }
            else
               ssOptArg = argv[ssOptInd++];
            sp = 1;
         }
      }
      else
      {
         if (argv[ssOptInd][++sp] == '\0')
         {
            sp = 1;
            ssOptInd++;
         }
         ssOptArg = NULLP;
      }
      RETVALUE(c);
#endif /* NOCMDLINE */
} /* end of SGetOpt */

#ifdef ENB_RELAY

/*
*
*       Fun:   SSetIntPend
*
*       Desc:  Set interrupt pending flag
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: Set interrupt pending flags in mos
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SSetIntPend
(
U16 id,
Bool flag
)
#else
PUBLIC INLINE S16 SSetIntPend(id, flag)
U16 id;
Bool flag;
#endif
{

   TRC2(SSetIntPend)

   UNUSED(id);
   UNUSED(flag);
      
   RETVALUE(ROK);
} /* end of SSetIntPend */
#endif /* ENB_RELAY */

  
/*
*
*       Fun:   mtGetOpts
*
*       Desc:  This function gets command line options.
*
*       Ret:   RETVOID
*
*       Notes: None
*
*       File:  ss_mtsp.c
*
*/
  
#ifdef ANSI
PRIVATE Void mtGetOpts
(
S32 argc,                   /* argument count */
S8 **argv                 /* argument values */
)
#else
PRIVATE Void mtGetOpts(argc, argv)
S32 argc;                   /* argument count */
S8 **argv;                /* argument values */
#endif
{
#ifndef NOCMDLINE
   S16 ret;                 /* return code */
#endif

   TRC0(mtGetOpts)
   ssOptInd = 1;
#ifndef NOFILESYS
   outFp = (FILE *)NULLP;
#endif /* NOFILESYS */

   ssArgv = argv;
   ssArgc = argc;

   while ((ret = SGetOpt(argc, argv, "o:s:")) != EOF)
   {
      switch (ret)
      {
#ifndef NOFILESYS
         case 'o':
            outFp = fopen(ssOptArg, "w");
            SAtExit(mtCloseOutFp, (Void*)&outFp);
            break;
#endif /* NOFILESYS */
         case 's':
#ifdef ENB_RELAY
            mtOsCp.ownProcId = PID_STK((ProcId)strtol(ssOptArg, NULLP, 0));
#else
            mtOsCp.ownProcId =(ProcId)strtol(ssOptArg, NULLP, 0);
#endif /* ENB_RELAY */
         break;
         case '?':
            /* fall through */
         default:
            break;
      }
   }
   ssOptInd = 1;
 
   RETVOID;
} /* end of mtGetOpts */


/*
*
*       Fun:   mtCloseOutFp
*
*       Desc:  close output file descriptor
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC Void *mtCloseOutFp
(
Void *arg
)
#else
PUBLIC Void *mtCloseOutFp(arg)
Void *arg;
#endif
{
   FILE **fp;
   
   TRC2(mtCloseOutFp)

   fp = (FILE**)arg;
   
   if (*fp)
      fclose(*fp);
   
   RETVALUE((Void *)NULLP);

} /* end of mtCloseOutFp */


/*
*
*       Fun:   mtDumpTicks
*
*       Desc:  dump ticks
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: 
*
*       File:  ss_mtsp.c
*
*/
#ifdef ANSI
PUBLIC Void *mtDumpTicks
(
Void *arg
)
#else
PUBLIC Void *mtDumpTicks(arg)
Void *arg;
#endif
{
   Ticks ticks;
   
   TRC2(mtDumpTicks)

   SGetSysTime(&ticks);
   sprintf(pBuf, "Ticks: %ld\n", ticks);
   SPrint(pBuf);

   RETVALUE((Void*)0);
} /* end of mtDumpTicks */

  
/********************************************************************30**
  
         End of file:     ss_mtsp.c@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:44:13 2014
  
*********************************************************************31*/
  

/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revison history:
  
*********************************************************************61*/
  
/********************************************************************80**

  version    pat  init                   description
----------- ----- ----  ------------------------------------------------
1.1          ---  ada   1. initial release

*********************************************************************81*/

