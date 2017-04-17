

/********************************************************************20**
  
     Name:     Multi-threaded System Services - Solaris
  
     Type:     C source file
  
     Desc:     C source code for the MTSS-Solaris implementation of
               System Services.
  
     File:     mt_ss.c
  
     Sid:      pt_ss.c@@/main/1 - Mon Apr  5 18:19:20 2010
   
     Prg:      kp
  
*********************************************************************21*/



/* POSIX includes */
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE         199309L
#endif

#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
 /* mt015.21: addition */
#ifdef SS_LINUX
#include <sys/time.h>
#endif
 /* mt008.21: addition */
#include <errno.h>                 



/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

#include "cm5.h"           /* common timers */

#include "mt_ss.h"         /* MTSS specific */
#include "mt_err.h"        /* MTSS error defines */

#include "ss_queue.h"      /* queues */
#include "ss_task.h"       /* tasking */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */

#include "cm_mem.h"        /* common memory manager */

/* multi-core support enhancement */

/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timers */

#include "mt_ss.x"         /* MTSS specific */

#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */

#include "cm_mem.x"        /* common memory manager */


/*** TBD: IMPORTANT ***
 *** The following definition is temporary. This must be removed
 *** when all products have been updated with latest ssi.h file OR
 *** all ssi.h files have been updated to contain this definitions
 ***/
/* New error class for FTHA added */
#ifndef ERRCLS_FTHA
#define ERRCLS_FTHA    0x8
#endif /* ERRCLS_FTHA */



/* forward references */

PRIVATE Void *mtTskHdlr ARGS((void *));

PRIVATE Void *mtTmrHdlr ARGS((void *));
PRIVATE Void mtTimeout ARGS((PTR tCb, S16 evnt));

PRIVATE Void mtExit ARGS((int));

#ifdef CONAVL
PRIVATE Void *mtConHdlr ARGS((void *));
#endif

#ifdef SS_DRVR_SUPPORT
PRIVATE Void *mtIsTskHdlr ARGS((void *));
#endif

/* mt020.201 - Addition for no command line available */
#ifndef NOCMDLINE
PRIVATE Void mtGetOpts ARGS((void));
#endif

/* mt033.201 - addition of local function to print the statistics such as 
* (size vs. numAttempts) and (allocations vs. deallocations) 
*/
#ifdef SSI_DEBUG_LEVEL1
PRIVATE S16 SPrintRegMemStats ARGS((Region region));
#endif /* SSI_DEBUG_LEVEL1 */


/* type declarations */

#ifdef SS_DRVR_SUPPORT
typedef struct mtIsFlag
{
   U16 id;
   U8 action;

} MtIsFlag;
#endif



/* public variable declarations */

PUBLIC Cntr cfgNumRegs = SS_MAX_REGS;
/* mt022.201 - Modification for shared memory relay region and memcal tool */
#ifndef SS_MULTICORE_SUPPORT
PUBLIC SsRegCfg cfgRegInfo[SS_MAX_REGS] =
{
   {
      SS_DFLT_REGION, SS_MAX_POOLS_PER_REG - 1,
      {
         { SS_POOL_DYNAMIC, MT_POOL_0_DSIZE },
         { SS_POOL_DYNAMIC, MT_POOL_1_DSIZE },
         { SS_POOL_DYNAMIC, MT_POOL_2_DSIZE },
         { SS_POOL_DYNAMIC, MT_POOL_3_DSIZE },
         { SS_POOL_STATIC, 0 }
      }
   }
#ifdef  RY_ENBS5SHM
   ,{
      RY_SHM_REGION, SS_MAX_POOLS_PER_REG - 1,
      {
         { SS_POOL_DYNAMIC, MT_POOL_0_DSIZE },
         { SS_POOL_DYNAMIC, MT_POOL_1_DSIZE },
         { SS_POOL_DYNAMIC, MT_POOL_2_DSIZE },
         { SS_POOL_DYNAMIC, MT_POOL_3_DSIZE },
         { SS_POOL_STATIC, 0 }
      }
   }
#endif
#ifdef USE_MEMCAL
   ,{
      SS_STATIC_REGION, SS_MAX_POOLS_PER_REG,
      {
         {SS_POOL_DYNAMIC, 16},
         {SS_POOL_DYNAMIC, 32},
         {SS_POOL_DYNAMIC, 80},
         {SS_POOL_DYNAMIC, 256},
         {SS_POOL_DYNAMIC, 320},
      }
   }
#endif
};
#else /*SS_MULTICORE_SUPPORT*/
#endif /*SS_MULTICORE_SUPPORT*/

/* mt022.201 - Modification for memory calculator tool */
/* mt018.201 - added memory configuration matrix */
#ifndef SS_MULTICORE_SUPPORT
PUBLIC MtMemCfg mtMemoCfg =
{
#ifdef  RY_ENBS5SHM
  SS_MAX_REGS - 1,                            /* number of regions */
#else
  SS_MAX_REGS,                                /* number of regions */
#endif
  {
    {
      SS_DFLT_REGION,                         /* region id */
      MT_MAX_BKTS,                            /* number of buckets */
      MT_HEAP_SIZE,                           /* heap size */
      {
         {MT_BKT_0_DSIZE, MT_BKT_0_NUMBLKS},   /* block size, no. of blocks */
         {MT_BKT_1_DSIZE, MT_BKT_1_NUMBLKS},    /* block size, no. of blocks */
         {MT_BKT_2_DSIZE, MT_BKT_2_NUMBLKS},   /* block size, no. of blocks */
         {MT_BKT_3_DSIZE, MT_BKT_3_NUMBLKS}    /* block size, no. of blocks */
      }
    },
    STATIC_MEM_CFG
  }
};
#else /* SS_MULTICORE_SUPPORT */
#endif /* SS_MULTICORE_SUPPORT */

PUBLIC S16 msArgc;              /* argc */
PUBLIC Txt **msArgv;            /* argv */
PUBLIC S16 msOptInd;            /* SGetOpt vars */
PUBLIC S8 *msOptArg;            /* SGetOpt vars */




/* private variable declarations */
/* mt018.201 - change mtCMMRegCfg as array of pointers */
PRIVATE CmMmRegCfg *mtCMMRegCfg[SS_MAX_REGS];
PRIVATE CmMmRegCb *mtCMMRegCb[SS_MAX_REGS];
 /* mt008.21: addition */
PRIVATE struct timespec ts1, ts2;
PRIVATE U32 err_in_nsec;

/* mt028.201 */
#ifndef API_MAIN

/*
*
*       Fun:   main
*
*       Desc:  This function is the entry point for the final binary. It
*              calls SInit() in the common code. It can be replaced by a
*              user function if required (SInit() must still be called).
*
*       Ret:   none on success
*              exit on failure
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC int main
(
int argc,                       /* argument count */
char **argv                     /* argument vector */
)
#else
PUBLIC int main(argc, argv)
int argc;                       /* argument count */
char **argv;                    /* argument vector */
#endif
{
   TRC0(main);


   msArgc = argc;
   msArgv = argv;

   SInit();

   /* mt030.201 added under compilet time flag SS_LINUX and SLES9_PLUS
      a loop to overcome the child processes being killed upon exiting the
      thread */

#ifdef SS_LINUX  /* this should have already been defined */
#ifdef SLES9_PLUS  /* they need to define this one */
   /* wait forever for children */
   for (;;) pause();
#endif
#endif

   pthread_exit(NULLP);

   RETVALUE(0);
}

#else

/*
*
*       Fun:   ssMain
*
*       Desc:  This function is the entry point for the final binary. It
*              calls SInit() in the common code. It can be replaced by a
*              user function if required (SInit() must still be called).
*
*       Ret:   none on success
*              exit on failure
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC int ssMain
(
int argc,                       /* argument count */
char **argv                     /* argument vector */
)
#else
PUBLIC int ssMain(argc, argv)
int argc;                       /* argument count */
char **argv;                    /* argument vector */
#endif
{
   TRC0(ssMain);


   msArgc = argc;
   msArgv = argv;


   SInit();

   RETVALUE(0);
}

#endif


/*
*  initialization functions
*/

/*
*
*       Fun:   Initialize OS control point
*
*       Desc:  This function initializes MTSS-specific information
*              in the OS control point.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdInitGen
(
void
)
#else
PUBLIC S16 ssdInitGen()
#endif
{
   struct sigaction act;
   sigset_t set;


   TRC0(ssdInitGen);


   osCp.dep.sysTicks = 0;

   /* mt020.201 - Addition for no command line available */
#ifndef NOCMDLINE
   /* parse command line */
   mtGetOpts();
#endif


   /* initialize the started semaphore */
   if (sem_init(&osCp.dep.ssStarted, 0, 0) != 0)
   {
      RETVALUE(RFAILED);
   }

   /* mt028.201 added compile time flag to allow not to mask signals */
#ifndef UNMASK_SIG
   /* mask all signals in the main thread */
   sigfillset(&set);
   sigdelset(&set, SIGINT);
   pthread_sigmask(SIG_SETMASK, &set, NULLP);
#endif /* UNMASK_SIG */

   /* install a SIGINT handler to shutdown */
   act.sa_handler = mtExit;
   sigfillset(&act.sa_mask);
   act.sa_flags = 0;
   if (sigaction(SIGINT, &act, NULLP) != 0)
   {
      RETVALUE(RFAILED);
   }
   /* mt040.201 initialise random seed */
   osCp.dep.randSeed = time(NULLP);

   RETVALUE(ROK);
}


/*
*
*       Fun:   De-initialize OS control point
*
*       Desc:  This function reverses the initialization in ssdInitGen().
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC Void ssdDeinitGen
(
void
)
#else
PUBLIC Void ssdDeinitGen()
#endif
{
   TRC0(ssdDeinitGen);


   sem_destroy(&osCp.dep.ssStarted);


   RETVOID;
}



/*
*
*       Fun:   Initialize region/pool tables
*
*       Desc:  This function initializes MTSS-specific information
*              in the region/pool tables and configures the common
*              memory manager for use.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdInitMem
(
void
)
#else
PUBLIC S16 ssdInitMem()
#endif
{
   /* mt018.201 - added local variable */
   U8          i;
   U16         j;
   U8          k;
   MtRegCfg   *region;
   
   TRC0(ssdInitMem);


   /* mt018.201 - CMM Initialization */
   for (i = 0; i < mtMemoCfg.numRegions; i++)
   {
      /* allocate space for the region control block */
      mtCMMRegCb[i] = (CmMmRegCb *)calloc(1, sizeof(CmMmRegCb));
      if (mtCMMRegCb[i] == NULLP)
      {
         for (k = 0; k < i; k++)
         {
            cmMmRegDeInit(mtCMMRegCb[k]);
            free(mtCMMRegCfg[k]->vAddr);
            free(mtCMMRegCb[k]);
            free(mtCMMRegCfg[k]);
         }
         RETVALUE(RFAILED);
      }

      mtCMMRegCfg[i] = (CmMmRegCfg *)calloc(1, sizeof(CmMmRegCfg));
      if (mtCMMRegCfg[i] == NULLP)
      {
         for (k = 0; k < i; k++)
         {
            cmMmRegDeInit(mtCMMRegCb[k]);
            free(mtCMMRegCfg[k]->vAddr);
            free(mtCMMRegCb[k]);
            free(mtCMMRegCfg[k]);
         }
         free(mtCMMRegCb[i]);
         RETVALUE(RFAILED);
      }


      /* allocate space for the region */
      region = &mtMemoCfg.region[i];
      mtCMMRegCfg[i]->size = region->heapsize;
      for (j = 0; j < region->numBkts; j++)
      {
/* mt033.201 - addition for including the header size while computing the total size */
#ifdef SSI_DEBUG_LEVEL1
         mtCMMRegCfg[i]->size += (region->bkt[j].blkSize + sizeof(CmMmBlkHdr)) *\
                                 (region->bkt[j].numBlks);
#else
         mtCMMRegCfg[i]->size += region->bkt[j].blkSize * region->bkt[j].numBlks;
#endif /* SSI_DEBUG_LEVEL1 */
      }
      mtCMMRegCfg[i]->vAddr = (Data *)calloc(mtCMMRegCfg[i]->size, 
                                             sizeof(Data));
      
      if (mtCMMRegCfg[i]->vAddr == NULLP)
      {
         for (k = 0; k < i; k++)
         {
            cmMmRegDeInit(mtCMMRegCb[k]);
            free(mtCMMRegCfg[k]->vAddr);
            free(mtCMMRegCb[k]);
            free(mtCMMRegCfg[k]);
         }
         free(mtCMMRegCb[i]);
         free(mtCMMRegCfg[i]);
         RETVALUE(RFAILED);
      }


      /* set up the CMM configuration structure */
      mtCMMRegCfg[i]->lType = SS_LOCK_MUTEX;
      mtCMMRegCfg[i]->chFlag = 0;
      mtCMMRegCfg[i]->bktQnSize = MT_BKTQNSIZE;
      mtCMMRegCfg[i]->numBkts = region->numBkts;

      for (j = 0; j < region->numBkts; j++)
      {
         mtCMMRegCfg[i]->bktCfg[j].size    = region->bkt[j].blkSize;
         mtCMMRegCfg[i]->bktCfg[j].numBlks = region->bkt[j].numBlks;
      }

      /* initialize the CMM */
      if (cmMmRegInit(region->regionId, mtCMMRegCb[i], mtCMMRegCfg[i]) != ROK)
      {
         for (k = 0; k < i; k++)
         {
            cmMmRegDeInit(mtCMMRegCb[k]);
            free(mtCMMRegCfg[k]->vAddr);
            free(mtCMMRegCb[k]);
            free(mtCMMRegCfg[k]);
         }
         free(mtCMMRegCfg[i]->vAddr);
         free(mtCMMRegCb[i]);
         free(mtCMMRegCfg[i]);
         RETVALUE(RFAILED);
      }


      /* initialize the STREAMS module */
      /* mt019.201: STREAMS module will only apply to DFLT_REGION */
      if (region->regionId == 0)
      {
         if (ssStrmCfg(region->regionId, region->regionId) != ROK)
         {
            for (k = 0; k < i; k++)
            {
               cmMmRegDeInit(mtCMMRegCb[k]);
               free(mtCMMRegCfg[k]->vAddr);
               free(mtCMMRegCb[k]);
               free(mtCMMRegCfg[k]);
            }
            cmMmRegDeInit(mtCMMRegCb[i]);
            free(mtCMMRegCfg[i]->vAddr);
            free(mtCMMRegCb[i]);
            free(mtCMMRegCfg[i]);
            RETVALUE(RFAILED);
         }
      }
   }

   RETVALUE(ROK);
}


/*
*
*       Fun:   De-initialize region/pool tables
*
*       Desc:  This function reverses the initialization in ssdInitMem().
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC Void ssdDeinitMem
(
void
)
#else
PUBLIC Void ssdDeinitMem()
#endif
{
   /* mt018.201 - added local variables */
   U8     i;
   
   TRC0(ssdDeinitMem);

   for (i = 0; i < mtMemoCfg.numRegions; i++)
   {
      cmMmRegDeInit(mtCMMRegCb[i]);
      free(mtCMMRegCfg[i]->vAddr);
      free(mtCMMRegCb[i]);
      free(mtCMMRegCfg[i]);
   }

   RETVOID;
}


/*
*
*       Fun:   Initialize task table
*
*       Desc:  This function initializes MTSS-specific information
*              in the task table.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdInitTsk
(
void
)
#else
PUBLIC S16 ssdInitTsk()
#endif
{
   U32 tskInd = 0;

   TRC0(ssdInitTsk);


   RETVALUE(ROK);
}


/*
*
*       Fun:   Deinitialize task table
*
*       Desc:  This function reverses the initialization perfomed in
*              ssdInitTsk().
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC Void ssdDeinitTsk
(
void
)
#else
PUBLIC Void ssdDeinitTsk()
#endif
{
   TRC0(ssdDeinitTsk);

   RETVOID;
}


#ifdef SS_DRVR_SUPPORT
/*
*
*       Fun:   Initialize driver task table
*
*       Desc:  This function initializes MTSS-specific information
*              in the driver task table.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdInitDrvr
(
void
)
#else
PUBLIC S16 ssdInitDrvr()
#endif
{
   S16 i;
   pthread_attr_t attr;


   TRC0(ssdInitDrvr);


   /* initialize the dependent portion of the driver task entries */
   for (i = 0;  i < SS_MAX_DRVRTSKS;  i++)
   {
      osCp.drvrTskTbl[i].dep.flag = FALSE;
   }


   /* create pipe for communication between SSetIntPend() and
    *  the isTskHdlr thread.
    */
   if (pipe(osCp.dep.isFildes) != 0)
   {
      RETVALUE(RFAILED);
   }


   /* create the isTskHdlr thread */
   pthread_attr_init(&attr);
   /* mt021.201 - Addition to set stack size */
   pthread_attr_setstacksize(&attr, (size_t)MT_ISTASK_STACK);
   pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
   if ((pthread_create(&osCp.dep.isTskHdlrTID, &attr, mtIsTskHdlr, NULLP)) != 0)
   {
      /* mt020.201 - Addition for destroying thread attribute object attr */
      pthread_attr_destroy(&attr);

      RETVALUE(RFAILED);
   }

   /* mt020.201 - Addition for destroying thread attribute object attr */
   pthread_attr_destroy(&attr);

   RETVALUE(ROK);
}


/*
*
*       Fun:   Deinitialize driver information
*
*       Desc:  This function reverses the initialization performed in
*              ssdInitDrvr().
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC Void ssdDeinitDrvr
(
void
)
#else
PUBLIC Void ssdDeinitDrvr()
#endif
{
   TRC0(ssdDeinitDrvr);


   RETVOID;
}
#endif /* SS_DRVR_SUPPORT */


/*
*
*       Fun:   Initialize timer table
*
*       Desc:  This function initializes MTSS-specific information
*              in the timer table.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdInitTmr
(
void
)
#else
PUBLIC S16 ssdInitTmr()
#endif
{
   pthread_attr_t attr;
  /* mt010.21: addition */
   S32 i;

   TRC0(ssdInitTmr);


   osCp.dep.tmrTqCp.tmrLen = SS_MAX_TMRS;
  /* mt010.21: addition */
   osCp.dep.tmrTqCp.nxtEnt = 0;
   for (i=0; i< SS_MAX_TMRS; i++)
   {
      osCp.dep.tmrTq[i].first = (CmTimer *)NULLP;
   }

   /* create the timer handler thread */
   pthread_attr_init(&attr);
   /* mt021.201 - Addition to set stack size */
   pthread_attr_setstacksize(&attr, (size_t)MT_TMRTASK_STACK);
   pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
   if ((pthread_create(&osCp.dep.tmrHdlrTID, &attr, mtTmrHdlr, NULLP)) != 0)
   {
      /* mt020.201 - Addition for destroying thread attribute object attr */
      pthread_attr_destroy(&attr);
      
      RETVALUE(RFAILED);
   }

   /* mt020.201 - Addition for destroying thread attribute object attr */
   pthread_attr_destroy(&attr);


   RETVALUE(ROK);
}


/*
*
*       Fun:   Deinitialize timer table
*
*       Desc:  This function reverses the initialization performed in
*              ssdInitTmr().
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC Void ssdDeinitTmr
(
void
)
#else
PUBLIC Void ssdDeinitTmr()
#endif
{

   TRC0(ssdDeinitTmr);


   RETVOID;
}



/*
*
*       Fun:   ssdInitFinal
*
*       Desc:  Pre-tst() initialization.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdInitFinal
(
void
)
#else
PUBLIC S16 ssdInitFinal()
#endif
{
/* mt027.201 - Modification to fix warnings with no STDIN and STDOUT */
#ifdef CONAVL
#ifndef CONRD
   S32 flags;
   pthread_attr_t attr;
#ifndef CONSTDIO
   struct termios tio;
#endif /* CONSTDIO */
   S16 fd;
#endif /* CONRD */
#endif /* CONAVL */

   TRC0(ssdInitFinal);


#ifdef CONAVL

   osCp.dep.conInFp = (FILE *) stdin;
   osCp.dep.conOutFp = (FILE *) stdout;
/* added compile time flag CONRD: mt017.21 */
#ifndef CONRD
#ifndef CONSTDIO

   /* disable canonical input processing */
   fd = fileno(osCp.dep.conInFp);
   if ((tcgetattr(fd, &tio)) != 0)
   {
      RETVALUE(RFAILED);
   }

   tio.c_lflag &= ~ICANON;
   tio.c_cc[VMIN] = 1;   /* wait for a minimum of 1 character input */
   tio.c_cc[VTIME] = 0;
   if ((tcsetattr(fd, TCSANOW, &tio)) != 0)
   {
      RETVALUE(RFAILED);
   }

#endif /* CONSTDIO */


   /* set up the input fd to block when no data is available */
   fd = fileno(osCp.dep.conInFp);
   flags = fcntl(fd, F_GETFL, &flags);
   flags &= ~O_NONBLOCK;
   if (fcntl(fd, F_SETFL, flags) == -1)
   {
      RETVALUE(RFAILED);
   }


   /* create the console handler thread */
   pthread_attr_init(&attr);
   /* mt021.201 - Addition to set stack size */
   pthread_attr_setstacksize(&attr, (size_t)MT_CONSOLE_STACK);
   pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
   if ((pthread_create(&osCp.dep.conHdlrTID, &attr, mtConHdlr, NULLP)) != 0)
   {
      /* mt020.201 - Addition for destroying thread attribute object attr */
      pthread_attr_destroy(&attr);
      
      RETVALUE(RFAILED);
   }

   /* mt020.201 - Addition for destroying thread attribute object attr */
   pthread_attr_destroy(&attr);
   
#endif /* CONRD */
#endif /* CONAVL */


   RETVALUE(ROK);
}


/*
*
*       Fun:   ssdDeinitFinal
*
*       Desc:  This function reverses the initialization performed in
*              ssdInitFinal().
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC Void ssdDeinitFinal
(
void
)
#else
PUBLIC Void ssdDeinitFinal()
#endif
{
   TRC0(ssdDeinitFinal);


   RETVOID;
}


/* mt022.201 - Modification to fix problem when NOCMDLINE is defined */
#ifndef NOCMDLINE
/*
*
*       Fun:   mtGetOpts
*
*       Desc:  This function gets command line options.
*
*       Ret:
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PRIVATE Void mtGetOpts
(
void
)
#else
PRIVATE Void mtGetOpts()
#endif
{
   S32 argc;
   S8 **argv;
   S16 ret;
   /* mt028.201 */
#ifndef NOFILESYS
   FILE         *memOpt;             /* memory options file pointer */
   Txt pBuf[128];
#endif
   U8 i;
#ifdef SS_MULTICORE_SUPPORT
#else
   U32 a;
   U32 b;
#endif



   TRC0(mtGetOpts);


   msOptInd = 1;

#ifndef NOFILESYS
   osCp.dep.fileOutFp = (FILE *)NULLP;

   /* initialize memOpt */
   memOpt = (FILE *) NULLP;
#endif

   argc = msArgc;
   argv = msArgv;

   /* mt028.201 */
   while ((ret = SGetOpt(argc, argv, "o:f:s:")) != EOF)
   {
      switch (ret)
      {
#ifndef NOFILESYS
         case 'o':
            osCp.dep.fileOutFp = fopen(msOptArg, "w");
            break;
         case 'f':
            memOpt = fopen(msOptArg, "r");

            /* if file does not exist or could not be opened then use the
             * default memory configuration as defined in mt_ss.h
             */
            if (memOpt == (FILE *) NULLP)
            {
               sprintf(pBuf, "\nMTSS: Memory configuration file: %s could not\
be opened, using default mem configuration\n", msOptArg);
               SPrint(pBuf);
               break;
            }

            i = 0;
#ifndef SS_MULTICORE_SUPPORT
            /* mt040.201 changed formating from %ld and removed (long *) 
               casting to make fscanf work with 64 bit archtecture */
            while ((ret = fscanf(memOpt, "%d %d", &a, &b))
                           != EOF)
            {
               switch  (i)
               {
                  case 0:
                     mtMemoCfg.numRegions = a;
                     mtMemoCfg.region[0].regionId = b;
                     break;
                  case 1:
                     mtMemoCfg.region[0].numBkts = a;
                     mtMemoCfg.region[0].heapsize = b;
                     break;
                  default:
                     mtMemoCfg.region[0].bkt[i -2].blkSize = a;
                     mtMemoCfg.region[0].bkt[i -2].numBlks = b;
                     break;
               }
               i++;
            }
#else /* SS_MULTICORE_SUPPORT */
#endif /* SS_MULTICORE_SUPPORT */
            fclose (memOpt);
            break;
#endif


         case 's':
/* mt028.201: modification: multiple procs support related changes */
#ifndef SS_MULTIPLE_PROCS

#ifdef ENB_RELAY
            osCp.procId = PID_STK((ProcId) strtol(msOptArg, NULLP, 0));
#else
            osCp.procId = (ProcId) strtol(msOptArg, NULLP, 0);
#endif

#else /* SS_MULTIPLE_PROCS */
        {
           ProcId procId;
#ifdef ENB_RELAY
            procId = PID_STK((ProcId) strtol(msOptArg, NULLP, 0));
#else
            procId = (ProcId) strtol(msOptArg, NULLP, 0);
#endif
           SAddProcIdLst(1, &procId);
        }

#endif /* SS_MULTIPLE_PROCS */
            break;


         case '?':
            /* fall through */


         default:
            break;
      }
   }

   msOptInd = 1;
 

   RETVOID;
}
#endif


/*
*
*       Fun:   SGetOpt
*
*       Desc:  Get options from command line
*
*       Ret:   option  - success
*              '?'     - fail
*              EOF     - end of options
*
*       Notes: Handles command lines like the following
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
*       File:  mt_ss.c
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
   /* mt020.201 - Removed for no command line */
#ifndef NOCMDLINE
   S16 sp;
   S16 c;
   S8 *cp;
#endif

   TRC1(SGetOpt);

   /* mt020.201 - Addition for no command line */
#ifdef NOCMDLINE
   UNUSED(argc);
   UNUSED(argv);
   UNUSED(opts);

   RETVALUE(EOF);
#else

   sp = 1;
   if (sp == 1)
   {
      if (msOptInd >= (S16) argc  ||  argv[msOptInd][0] == '\0') RETVALUE(EOF);
      else
      {
         if (!strcmp(argv[msOptInd], "--"))
         {
            msOptInd++;
            RETVALUE(EOF);
         }
         else if (argv[msOptInd][0] != '-')
         {
            msOptInd++;
            RETVALUE('?');
         }
      }
   }

   c = argv[msOptInd][sp];
   if (c == ':'  ||  (cp = (S8 *) strchr(opts, c)) == (S8 *) NULLP)
   {
      if (argv[msOptInd][++sp] == '\0')
      {
         msOptInd++;
         sp = 1;
      }

      RETVALUE('?');
   }

   if (*++cp == ':')
   {
      if (argv[msOptInd][sp+1] != '\0') msOptArg = &argv[msOptInd++][sp+1];
      else
      {
         if (++msOptInd >= (S16) argc)
         {
            sp = 1;
            RETVALUE('?');
         }
         else msOptArg = argv[msOptInd++];

         sp = 1;
      }
   }
   else
   {
      if (argv[msOptInd][++sp] == '\0')
      {
         sp = 1;
         msOptInd++;
      }

      msOptArg = NULLP;
   }


   RETVALUE(c);

#endif /* NOCMDLINE */
}


/*
*
*       Fun:   ssdStart
*
*       Desc:  This function starts system services execution; the
*              permanent tasks are started and the system enters a
*              ready state.
*
*       Ret:   Void
*
*       Notes: 
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC Void ssdStart
(
void
)
#else
PUBLIC Void ssdStart()
#endif
{
   S16 i;


   TRC0(ssdStart);


   /* mt025.201 - Modification for adding lock to timer handler */
   for (i = 0;  i <= SS_MAX_STSKS;  i++)
   {
      sem_post(&osCp.dep.ssStarted);
   }


   RETVOID;
}
 

/*
*     indirect interface functions to system services service user
*/


/*
*
*       Fun:   ssdAttachTTsk
*
*       Desc:  This function sends the initial tick message to a TAPA
*              task if the task is a permanent task.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdAttachTTsk
(
SsTTskEntry *tTsk           /* pointer to TAPA task entry */
)
#else
PUBLIC S16 ssdAttachTTsk(tTsk)
SsTTskEntry *tTsk;          /* pointer to TAPA task entry */
#endif
{
   Buffer *mBuf;
   SsMsgInfo *mInfo;
   S16 ret;


   TRC0(ssdAttachTTsk);


   if (tTsk->tskType == SS_TSK_PERMANENT)
   {
      /* Send a permanent tick message to this task, to start
       * execution.
       */
      ret = SGetMsg(SS_DFLT_REGION, SS_DFLT_POOL, &mBuf);
      if (ret != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         MTLOGERROR(ERRCLS_DEBUG, EMT001, ret, "SGetMsg() failed");
#endif
         RETVALUE(RFAILED);
      }

      mInfo = (SsMsgInfo *)mBuf->b_rptr;
      mInfo->eventInfo.event = SS_EVNT_PERMTICK;

      /* set up post structure */
/* mt028.201: modification: multiple procs support related changes */
#ifndef SS_MULTIPLE_PROCS
      mInfo->pst.dstProcId = SFndProcId();
      mInfo->pst.srcProcId = SFndProcId();
#else /* SS_MULTIPLE_PROCS */
      mInfo->pst.dstProcId = tTsk->proc;
      mInfo->pst.srcProcId = tTsk->proc;
#endif /* SS_MULTIPLE_PROCS */
      mInfo->pst.selector  = SEL_LC_NEW;
      mInfo->pst.region    = DFLT_REGION;
      mInfo->pst.pool      = DFLT_POOL;
      mInfo->pst.prior     = PRIOR3;
      mInfo->pst.route     = RTESPEC;
      mInfo->pst.event     = 0;
      mInfo->pst.dstEnt    = tTsk->ent;
      mInfo->pst.dstInst   = tTsk->inst;
      mInfo->pst.srcEnt    = tTsk->ent;
      mInfo->pst.srcInst   = tTsk->inst;

      ret = ssDmndQPutLast(&tTsk->sTsk->dQ, mBuf,
                           (tTsk->tskPrior * SS_MAX_MSG_PRI) + PRIOR3);

      if (ret != ROK)
      {
         SPutMsg(mBuf);

#if (ERRCLASS & ERRCLS_DEBUG)
         MTLOGERROR(ERRCLS_DEBUG, EMT002, ret,
                        "Could not write to demand queue");
#endif
         RETVALUE(RFAILED);
      }
   }


   RETVALUE(ROK);
}


/*
*
*       Fun:   ssdDetachTTsk
*
*       Desc:  Does nothing.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdDetachTTsk
(
SsTTskEntry *tTsk           /* pointer to TAPA task entry */
)
#else
PUBLIC S16 ssdDetachTTsk(tTsk)
SsTTskEntry *tTsk;          /* pointer to TAPA task entry */
#endif
{
   TRC0(ssdDetachTTsk);


   RETVALUE(ROK);
}


/*
*
*       Fun:   ssdCreateSTsk
*
*       Desc:  This function creates a system task. A thread is started
*              on the system task handler function defined later.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdCreateSTsk
(
SsSTskEntry *sTsk           /* pointer to system task entry */
)
#else
PUBLIC S16 ssdCreateSTsk(sTsk)
SsSTskEntry *sTsk;          /* pointer to system task entry */
#endif
{
   pthread_attr_t attr;


   TRC0(ssdCreateSTsk);


#ifdef SS_SINGLE_THREADED
#ifdef SS_MULTICORE_SUPPORT
#else
   if (osCp.numSTsks > 0)
#endif /* SS_MULTICORE_SUPPORT */
   {
      RETVALUE(ROK);
   }
#endif


   /* set the current executing entity and instance IDs to
    * 'not configured'. create the lock to access them.
    */
   sTsk->dep.ent = ENTNC;
   sTsk->dep.inst = INSTNC;


   /* create the thread */
   pthread_attr_init(&attr);
   /* mt021.201 - Addition to set stack size */
   pthread_attr_setstacksize(&attr, (size_t)MT_TASK_STACK);
   pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

   if ((pthread_create(&sTsk->dep.tId, &attr, mtTskHdlr, (Ptr)sTsk)) != 0)
   {

      /* mt020.201 - Addition for destroying thread attribute object attr */
      pthread_attr_destroy(&attr);
 
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT004, ERRZERO, "Could not create thread");
#endif

      RETVALUE(RFAILED);
   }


   /* mt020.201 - Addition for destroying thread attribute object attr */
   pthread_attr_destroy(&attr);

   RETVALUE(ROK);
}

/************* multi-core support **************/
/************ end multi-core support *************/


/*
*
*       Fun:   ssdDestroySTsk
*
*       Desc:  This function destroys a system task. A terminate
*              event message is sent to the thread function.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdDestroySTsk
(
SsSTskEntry *sTsk           /* pointer to system task entry */
)
#else
PUBLIC S16 ssdDestroySTsk(sTsk)
SsSTskEntry *sTsk;          /* pointer to system task entry */
#endif
{
   Buffer *mBuf;
   SsMsgInfo *mInfo;


   TRC0(ssdDestroySTsk);


   /* we send a message to this system task to tell it to die */
   if (SGetMsg(SS_DFLT_REGION, SS_DFLT_POOL, &mBuf) != ROK)
   {

#if (ERRCLASS & ERRCLASS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT005, ERRZERO, "Could not get a message");
#endif

      RETVALUE(RFAILED);
   }

   mInfo = (SsMsgInfo *)mBuf->b_rptr;
   mInfo->eventInfo.event = SS_EVNT_TERM;

   if (ssDmndQPutLast(&sTsk->dQ, mBuf, 0) != ROK)
   {
      SPutMsg(mBuf);

#if (ERRCLASS & ERRCLASS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT006, ERRZERO,
                     "Could not write to demand queue");
#endif

      RETVALUE(RFAILED);
   }


   RETVALUE(ROK);
}

/* mt023.201 - Added SThreadYield function to yield CPU
*
*       Fun:   SThreadYield
*
*       Desc:  This function defers thread execution to any other ready
*              thread.
*
*       Ret:   ROK      - ok
*              RFAILED  - failure
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SThreadYield
(
void
)
#else
PUBLIC S16 SThreadYield()
#endif
{

   TRC0(SThreadYield);

/* mt024.201 - seperated Linux and other UNIX implementations
 */
#ifdef SS_LINUX   
   {
      struct timeval tw;
      
      /* Set sleep value to 0 to yield CPU */
      tw.tv_sec=0; 
      tw.tv_usec=0;

      RETVALUE(select(0,0,0,0,&tw) == 0 ? ROK : RFAILED);
   }
#else /* other UNICes */

   RETVALUE(sleep(0) == 0 ? ROK : RFAILED);
   
#endif /* SS_LINUX */
   
}


/*
*
*       Fun:   Register timer
*
*       Desc:  This function is used to register a timer
*              function for the service user. System services
*              will invoke the timer activation function
*              passed to it at the specified intervals.
*
*       Ret:   ROK      - ok
*
*       Notes: Timing is handled by the common timers. The
*              ticks are handled by a thread that uses
*              nanosleep() and thus timing precision will not
*              be very accurate.
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdRegTmr
(
SsTmrEntry *tmr             /* pointer to timer entry */
)   
#else
PUBLIC S16 ssdRegTmr(tmr)
SsTmrEntry *tmr;            /* pointer to timer entry */
#endif 
{
   CmTmrArg arg;


   TRC0(ssdRegTmr);


   /* initialize common timers */
   cmInitTimers(tmr->dep.timers, TMR_DEF_MAX);

   
   /* start the timer */
   arg.tq = osCp.dep.tmrTq;
   arg.tqCp = &osCp.dep.tmrTqCp;
   arg.timers = tmr->dep.timers;
   arg.cb = (PTR) tmr;
   arg.evnt = TMR_DEF;
   arg.wait = 0;
   arg.tNum = NOTUSED;
   arg.max = TMR_DEF_MAX;
   arg.wait = tmr->interval;
   cmPlcCbTq(&arg);


   RETVALUE(ROK);
}


/*
*
*       Fun:   Deregister timer
*
*       Desc:  This function is used to deregister a timer function.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdDeregTmr
(
SsTmrEntry *tmr             /* pointer to timer entry */
)
#else
PUBLIC S16 ssdDeregTmr(tmr)
SsTmrEntry *tmr;            /* pointer to timer entry */
#endif 
{
   CmTmrArg arg;


   TRC0(ssdDeregTmr);


   /* stop the timer */
   arg.tq = osCp.dep.tmrTq;
   arg.tqCp = &osCp.dep.tmrTqCp;
   arg.timers = tmr->dep.timers;
   arg.cb = (PTR) tmr;
   arg.evnt = TMR_DEF;
   arg.wait = 0;
   arg.tNum = NOTUSED;
   arg.max = TMR_DEF_MAX;
   arg.wait = tmr->interval;
   cmRmvCbTq(&arg);


   RETVALUE(ROK);
}


/*
*
*       Fun:   Critical error
*
*       Desc:  This function is called when a critical error occurs.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdError
(
Seq seq,                    /* sequence number */
Reason reason               /* reset reason */
)
#else
PUBLIC S16 ssdError(seq, reason)
Seq seq;                    /* sequence number */
Reason reason;              /* reset reason */
#endif
{
   S16 i;
   pthread_t tId;
   Txt errBuf[256];


   TRC0(ssdError);


   /* get calling task ID */
   tId = pthread_self();


   /* set up the message to display */
   sprintf(errBuf, "\n\nFATAL ERROR - taskid = %x, errno = %d,"
            "reason = %d\n\n", (U8)tId, seq, reason);
   SPrint(errBuf);


   /* delete all system tasks */
   for (i = 0;  i < SS_MAX_STSKS;  i++)
   {
      if (osCp.sTskTbl[i].used
            &&  !pthread_equal(osCp.sTskTbl[i].dep.tId, tId))
      {
         pthread_kill(osCp.sTskTbl[i].dep.tId, SIGKILL);
      }
   }


   /* delete self */
   pthread_exit(NULLP);


   /* won't reach here */
   RETVALUE(ROK);
}


/*
*
*       Fun:   Log error
*
*       Desc:  This function is called to log an error.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC Void ssdLogError
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
PUBLIC Void ssdLogError(ent, inst, procId, file, line,
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
#ifndef DEBUGNOEXIT
   S16 i;
#endif
   pthread_t tId;
   Txt *errClsMsg;
   Txt errBuf[512];


   TRC0(ssdLogError);


   /* get calling task ID */
   tId = pthread_self();


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

/* mt028.201 : Addition - ERRCLS_FTHA changes */
      case ERRCLS_FTHA:
         errClsMsg = "ERRCLS_FTHA";
         break;

      default:
         errClsMsg = "INVALID ERROR CLASS!";
         break;
   }


   sprintf(errBuf,
             "\nmtss(posix): sw error:  ent: %03d  inst: %03d  proc id: %03d \n"
             "file: %s line: %03ld errcode: %05ld errcls: %s\n"
             "errval: %05ld  errdesc: %s\n",
           ent, inst, procId, file, line, errCode, errClsMsg, errVal, errDesc);
   SDisplay(0, errBuf);


#ifndef DEBUGNOEXIT
   /* debug errors halt the system */
   if (errCls == ERRCLS_DEBUG)
   {
      /* delete all system tasks */
      for (i = 0;  i < SS_MAX_STSKS;  i++)
      {
         if (osCp.sTskTbl[i].used
               &&  !pthread_equal(osCp.sTskTbl[i].dep.tId, tId))
         {
            pthread_kill(osCp.sTskTbl[i].dep.tId, SIGKILL);
         }
      }


      /* delete self */
      pthread_exit(NULLP);
   }
#endif


   RETVOID;
}

#ifdef ENB_RELAY

/*
*
*       Fun:   Register driver task
*
*       Desc:  This function is called to register the handlers for a
*              driver task.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 ssdRegDrvrTsk
(
SsDrvrTskEntry *drvrTsk         /* driver task entry */
)
#else
PUBLIC S16 ssdRegDrvrTsk(drvrTsk)
SsDrvrTskEntry *drvrTsk;        /* driver task entry */
#endif
{
   TRC0(ssdRegDrvrTsk);


   RETVALUE(ROK);
}
#endif




/*
*       private support functions
*/


/*
*
*       Fun:   Task handler
*
*       Desc:  This is the system task handler function. It blocks on
*              the system task's demand queue. On receiving a message,
*              it identifies the target TAPA task, verifies that the
*              TAPA task belongs to this system task and if so, calls
*              the activation function of that TAPA task with the
*              received message. The task activation function or the
*              timer activation function may be called.
*
*       Ret:   (thread function)
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC Void *mtTskHdlr
(
Ptr tskPtr                      /* pointer to task entry */
)
#else
PUBLIC Void *mtTskHdlr(tskPtr)
Ptr tskPtr;                     /* pointer to task entry */
#endif
{
   S16 i;
   S16 ret;
   SsIdx idx;
   SsSTskEntry *sTsk;
   SsTTskEntry *tTsk;
   Buffer *mBuf;
#ifdef SS_PERF
   Buffer *mBuf2;
#endif
   SsMsgInfo *mInfo;
   Pst nPst;
/* mt028.201: modification: multiple procs support related changes */
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
   PAIFTMRS16 tmrActvFnMt = NULLP;
#endif
   PFS16 tmrActvFn;
#else
   PAIFTMRS16 tmrActvFn;
   U16 procIdIdx;
#endif /* SS_MULTIPLE_PROCS */

   TRC0(mtTskHdlr);


   /* get out the system task entry from the parameter */
   sTsk = (SsSTskEntry *) tskPtr;


   /* wait for SS to come up */

   /* mt038.201 changed how sem_wait is called  */
   while ((ret = sem_wait(&osCp.dep.ssStarted) != ROK) && (errno == EINTR))
      continue;


   for (; ;)
   {
      /* get a message from the demand queue */
      ret = ssDmndQGet(&sTsk->dQ, &mBuf, SS_DQ_FIRST);
      if (ret != ROK)
         continue;


      /* if we can't lock this system task entry, return the message */
      ret = SLock(&sTsk->lock);
      if (ret != ROK)
      {

#if (ERRCLASS & ERRCLS_DEBUG)
         MTLOGERROR(ERRCLS_DEBUG, EMT007, (ErrVal) ret,
                        "Could not lock system task entry");
#endif
         SPutMsg(mBuf);
         continue;
      }

/* mt034.201 */
#ifdef SS_PERF
      do {    
      mBuf2 = mBuf->b_next;
#endif
      /* find out what kind of message this is */
      mInfo = (SsMsgInfo *)mBuf->b_rptr;
      switch (mInfo->eventInfo.event)
      {
         /* this is a termination event, we die */
         case SS_EVNT_TERM:
            /* release the message */
            SPutMsg(mBuf);

            /* Unlock the system task entry and lock the system
             *  task table to clean our entry up.
             */
            SUnlock(&sTsk->lock);

            ret = SLock(&osCp.sTskTblLock);
            if (ret != ROK)
            {

#if (ERRCLASS & ERRCLS_DEBUG)
               MTLOGERROR(ERRCLS_DEBUG, EMT008, (ErrVal) ret,
                           "Could not lock system task table");
#endif
               /* what to do here? */
               continue;
            }

            /* clean up the system task entry */
            sTsk->used = FALSE;
            sTsk->tskPrior = 0;
            sTsk->numTTsks = 0;
            SDestroyLock(&sTsk->lock);
            ssDestroyDmndQ(&sTsk->dQ);

            /* lock for current executing TAPA task ID */

            /* make this entry available in the system task table */
            sTsk->nxt = osCp.nxtSTskEntry;
            for (i = 0;  i < SS_MAX_STSKS;  i++)
            {
               if (sTsk == &osCp.sTskTbl[i])
               {
                  osCp.nxtSTskEntry = i;
                  break;
               }
            }

            osCp.numSTsks--;

            /* unlock the system task table */
            SUnlock(&osCp.sTskTblLock);

            return NULLP;


         /* this is a data message or a permanent task keep-alive message */
         case SS_EVNT_DATA:
         case SS_EVNT_PERMTICK:
            /* message to a task. find the destination task */
/* mt028.201: modification: multiple procs support related changes */
#ifdef SS_MULTIPLE_PROCS
            procIdIdx = SGetProcIdIdx(mInfo->pst.dstProcId);

            if (procIdIdx == SS_INV_PROCID_IDX)
            {
               SPutMsg(mBuf);
               break;
            }

            idx = osCp.tTskIds[procIdIdx][mInfo->pst.dstEnt][mInfo->pst.dstInst];
#else /* SS_MULTIPLE_PROCS */
            idx = osCp.tTskIds[mInfo->pst.dstEnt][mInfo->pst.dstInst];
#endif /* SS_MULTIPLE_PROCS */

            /* verify that it hasn't been deregistered */
            if (idx == SS_TSKNC)
            {
               SPutMsg(mBuf);
               break;
            }

            /* verify that this system task is still running it */
            tTsk = &osCp.tTskTbl[idx];
            if (tTsk->sTsk != sTsk)
            {
               SPutMsg(mBuf);
               break;
            }

               /* set the current executing TAPA task ID */
               sTsk->dep.ent = mInfo->pst.dstEnt;
               sTsk->dep.inst = mInfo->pst.dstInst;

            /* copy the Pst structure into a local duplicate */
            for (i = 0;  i < (S16) sizeof(Pst);  i++)
               *(((U8 *)(&nPst)) + i) = *(((U8 *)&mInfo->pst) + i);
                                        
            /* Give the message to the task activation function. If
             *  its a normal data message, we pass it, if this is a
             *  keep-alive message for a permanent task then we pass
             *  NULLP in place of the message to the task activation
             *  function.
             */
            if (mInfo->eventInfo.event == SS_EVNT_DATA)
            {
               tTsk->actvTsk(&nPst, mBuf);
            }
            else
            {
#if (ERRCLASS & ERRCLS_DEBUG)
               /* this message should only come to a permanent task */
               if (tTsk->tskType != SS_TSK_PERMANENT)
               {
                  MTLOGERROR(ERRCLS_DEBUG, EMT009, ERRZERO, "Logic failure");
                  break;
               }
#endif
               tTsk->actvTsk(&nPst, NULLP);

               /* We need to re-send this message back to ourselves so
                *  the permanent task continues to run.
                */
               /* Check if this task got deregistered or detached
                *  by the activation function; if so, there's nothing
                *  more to do here, otherwise go ahead.
                */
               ret = ROK;
               if (tTsk->used == TRUE  &&  tTsk->sTsk != NULLP)
               {
                  ret = ssDmndQPutLast(&tTsk->sTsk->dQ, mBuf,
                              ((tTsk->tskPrior) * SS_MAX_MSG_PRI) +
                              mInfo->pst.prior);
               }

               /* failure here is a real problem */
               if (ret != ROK)
               {
#if (ERRCLASS & ERRCLS_DEBUG)
                  MTLOGERROR(ERRCLS_DEBUG, EMT010, ERRZERO,
                              "Could not write to demand queue");
#endif
                  SPutMsg(mBuf);
               }
            }

            /* unset the current executing TAPA task ID */
               sTsk->dep.ent = ENTNC;
               sTsk->dep.inst = INSTNC;
            break;


         case SS_EVNT_TIMER:
            /* timer event. find the timer entry */
            idx = mInfo->eventInfo.u.tmr.tmrIdx;

            /* lock the timer table, coz we're going to peek in it */
            ret = SLock(&osCp.tmrTblLock);
            if (ret != ROK)
            {

#if (ERRCLASS & ERRCLS_DEBUG)
               MTLOGERROR(ERRCLS_DEBUG, EMT011, (ErrVal) ret,
                              "Could not lock timer table");
#endif
               SPutMsg(mBuf);
               break;
            }

            /* Verify that this timer entry is still around and that it
             *  belongs to our task.
             */
            if (osCp.tmrTbl[idx].used == FALSE
/* mt028.201: modification: multiple procs support related changes */
#ifdef SS_MULTIPLE_PROCS
                  ||  osCp.tmrTbl[idx].ownerProc != mInfo->pst.dstProcId
#endif /* SS_MULTIPLE_PROCS */
                  ||  osCp.tmrTbl[idx].ownerEnt != mInfo->pst.dstEnt
                  ||  osCp.tmrTbl[idx].ownerInst != mInfo->pst.dstInst)
            {
               SUnlock(&osCp.tmrTblLock);
               SPutMsg(mBuf);
               break;
            }

 /* mt005.21: addition */
            /* set the current executing TAPA task ID */
               sTsk->dep.ent = mInfo->pst.dstEnt;
               sTsk->dep.inst = mInfo->pst.dstInst;

#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
            if (osCp.tmrTbl[idx].mtFlag == TRUE)
            {
               tmrActvFnMt = osCp.tmrTbl[idx].tmrActvFnMt;
            }
            else
#endif
#endif
            {
               tmrActvFn = osCp.tmrTbl[idx].tmrActvFn;
            }

            /* unlock the timer table */
            SUnlock(&osCp.tmrTblLock);

            /* activate the timer function */
/* mt028.201: modification: multiple procs support related changes */
#ifndef SS_MULTIPLE_PROCS
#ifdef SS_MT_TMR
            if (tmrActvFnMt)
            {
               tmrActvFnMt(osCp.tmrTbl[idx].ownerEnt,
                           osCp.tmrTbl[idx].ownerInst);
            }
            else
#endif
            {
               tmrActvFn();
            }
#else
            tmrActvFn(osCp.tmrTbl[idx].ownerProc, osCp.tmrTbl[idx].ownerEnt,
                        osCp.tmrTbl[idx].ownerInst);
#endif /* SS_MULTIPLE_PROCS */

 /*mt005.21: addition */
            /* unset the current executing TAPA task ID */
               sTsk->dep.ent = ENTNC;
               sTsk->dep.inst = INSTNC;


            /* return the message buffer */
            SPutMsg(mBuf);
            break;


         default:
#if (ERRCLASS & ERRCLS_DEBUG)
            MTLOGERROR(ERRCLS_DEBUG, EMT012, (ErrVal) ret,
                        "Illegal event");
#endif
            break;
      }
#ifdef SS_PERF
         mBuf = mBuf2;
      } while (mBuf != NULLP);
#endif

      /* unlock the system task entry */
      SUnlock(&sTsk->lock);

#ifndef SS_PERF
      /* yield for other threads */
      /* mt024.201 - changed to use SSI SThreadYield instead of sleep */
      SThreadYield();
#endif
   }

   /* should not reach here */
}


/*
*
*       Fun:   mtTmrHdlr
*
*       Desc:  The timer handler thread function. Counts time
*              and invokes the common timer function on each
*              tick.
*
*       Ret:   (thread function)
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
   /* mt009.21: addition */
PRIVATE Void *mtTmrHdlr
(
void *parm                        /* unused */
)
#else
   /* mt009.21: addition */
PRIVATE Void *mtTmrHdlr(parm)
void *parm;                       /* unused */
#endif
{
 /* mt008.21: addition */
   struct timespec ts;
   U32 time_int;
   double t1,t2;
   U8 i, cnt, oldTicks, newTicks;
 /* mt015.21: addition */
#ifdef SS_LINUX
   struct timeval tv1,tv2;  
#endif
   /* mt038.201 added return */
   S16 ret;
   /* mt039.201 changes for nanosleep */
   struct timespec tsN;

   TRC0(mtTmrHdlr);


   UNUSED(parm);

   /* mt027.201 - Modification for SRegCfgTmr support */
   /* check SS_TICKS_SEC */
   if (SS_1MS < SS_TICKS_SEC)
   {
      MTLOGERROR(ERRCLS_DEBUG, EMT013, ERRZERO, "Minimum SSI ticks is 1ms");
   }

   /* mt025.201 - Addition to stop timer handler till task registration is done */
   /* wait for SS to come up */
   /* mt038.201 changed how sem_wait is called  */
   while ((ret = sem_wait(&osCp.dep.ssStarted) != ROK) && (errno == EINTR))
      continue;

   /* mt027.201 - Modification for SRegCfgTmr support */
   /* set up parameter to nanosleep() for SS_TICKS_SEC */
   ts.tv_sec = 0;
   ts.tv_nsec = MT_TICK_CNT;
   /* mt039.201 changes for nanosleep */
   tsN.tv_sec = 0;
   tsN.tv_nsec = 0;

 /* mt008.21: addition */
   err_in_nsec =  0;


 /* mt015.21: addition */
#ifndef SS_LINUX
   if (clock_gettime(CLOCK_REALTIME, &ts1) == -1)
#else
   if (gettimeofday(&tv1, NULL) == -1)
#endif
   {
#if (ERRCLASS & ERRCLS_DEBUG)
            MTLOGERROR(ERRCLS_DEBUG, EMT014, (ErrVal) errno,
                        "Error in clock_gettime");
#endif
   }

 /* mt015.21: addition */
#ifdef SS_LINUX
      ts1.tv_sec = tv1.tv_sec;
      ts1.tv_nsec= tv1.tv_usec * 1000;
#endif

   /* infinite loop */
   for (; ;)
   {
     /* mt039.201 changes for nanosleep */
      /* sleep for 100 milliseconds */
      ts.tv_nsec = MT_TICK_CNT;
      while ((ret = nanosleep (&ts, &tsN) != ROK) && (errno == EINTR))
      {
         ts.tv_nsec = tsN.tv_nsec;
         tsN.tv_nsec = 0;
         continue;
      }


 /* mt008.21: addition */

 /* mt015.21: addition */
#ifndef SS_LINUX
      if (clock_gettime(CLOCK_REALTIME, &ts2) == -1)
#else
      if (gettimeofday(&tv2,NULL) == -1)
#endif
      {
#if (ERRCLASS & ERRCLS_DEBUG)
            MTLOGERROR(ERRCLS_DEBUG, EMT015, (ErrVal) errno,
                        "Error in clock_gettime");
#endif
      }

 /* mt015.21: addition */
#ifdef SS_LINUX
      ts2.tv_sec = tv2.tv_sec;
      ts2.tv_nsec= tv2.tv_usec * 1000;
#endif

      t1 = ((double) ts1.tv_sec * (double) 1000000000 + (double) ts1.tv_nsec);
      t2 = ((double) ts2.tv_sec * (double) 1000000000 + (double) ts2.tv_nsec);
      if( ts2.tv_sec >= ts1.tv_sec)
      {
         time_int = (long) (t2-t1);
      }
      else
      {
         t1 = ((double) 1000000000 * (double) 1000000000) - t1; 
         time_int = (long) (t1 + t2);
      }
      /* mt027.201 - Modification for SRegCfgTmr support */
      err_in_nsec += (time_int % MT_TICK_CNT);
      oldTicks = osCp.dep.sysTicks;
      osCp.dep.sysTicks += time_int/MT_TICK_CNT + err_in_nsec/MT_TICK_CNT;  
      err_in_nsec = err_in_nsec % MT_TICK_CNT; 
      newTicks = osCp.dep.sysTicks;
      ts1.tv_nsec = ts2.tv_nsec;
      ts1.tv_sec = ts2.tv_sec;

      cnt = newTicks - oldTicks;
      /* call the common timer tick handler */
      for (i = 0; i < cnt; i++)
      {
         cmPrcTmr(&osCp.dep.tmrTqCp, osCp.dep.tmrTq, mtTimeout);
      }
   }

   /* mt009.21: addition */
   RETVALUE( (Void *) NULLP);
   /* will not reach here */
}


/*
*
*       Fun:   mtTimeout
*
*       Desc:  Process timer event. Called from the common timer
*              code when a timeout occurs.
*
*       Ret:   Void
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC Void mtTimeout
(
PTR tCb,                        /* control block */
S16 evnt                        /* event */
)
#else
PUBLIC Void mtTimeout(tCb, evnt)
PTR tCb;                        /* control block */
S16 evnt;                       /* event */
#endif
{
   Buffer *mBuf;
   SsMsgInfo *mInfo;
   CmTmrArg arg;
   SsTmrEntry *tEnt;
   SsTTskEntry *tTsk;
   SsIdx idx;
   S16 ret;
/* mt028.201: modification: multiple procs support related changes */
#ifdef SS_MULTIPLE_PROCS
   U16 procIdIdx;
#endif /* SS_MULTIPLE_PROCS */

   TRC0(mtTimeout);


   /* get the timer entry */
   tEnt = (SsTmrEntry *) tCb;


   /* if the timer was deleted, this will be NULL, so drop it */
   if (tEnt == NULL)
   {
      RETVOID;
   }


   /* lock the timer table */
   if (SLock(&osCp.tmrTblLock) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT016, ERRZERO, "Could not lock timer table");
#endif

      RETVOID;
   }


   /* Hmmmm, the timer might have been deleted while we've been
    *  working at getting here, so we just skip this.
    */
   if (tEnt->used == FALSE)
   {
      SUnlock(&osCp.tmrTblLock);
      RETVOID;
   }


   /* Set up and send a timer message to the destination tasks'
    * demand queue.
    */
#ifndef SS_MULTICORE_SUPPORT
   if (SGetMsg(SS_DFLT_REGION, SS_DFLT_POOL, &mBuf) != ROK)
#else
#endif
   {
      SUnlock(&osCp.tmrTblLock);

#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT017, ERRZERO, "Could not get message");
#endif

      RETVOID;
   }

   mInfo = (SsMsgInfo *)mBuf->b_rptr;
   mInfo->eventInfo.event = SS_EVNT_TIMER;
   mInfo->eventInfo.u.tmr.tmrIdx = tEnt->tmrId;

   mInfo->pst.dstEnt = tEnt->ownerEnt;
   mInfo->pst.dstInst = tEnt->ownerInst;
   mInfo->pst.srcEnt = tEnt->ownerEnt;
   mInfo->pst.srcInst = tEnt->ownerInst;
/* mt028.201: modification: multiple procs support related changes */
#ifndef SS_MULTIPLE_PROCS
   mInfo->pst.dstProcId = SFndProcId();
   mInfo->pst.srcProcId = SFndProcId();
#else /* SS_MULTIPLE_PROCS */
   mInfo->pst.dstProcId = tEnt->ownerProc;
   mInfo->pst.srcProcId = tEnt->ownerProc;
#endif /* SS_MULTIPLE_PROCS */
   mInfo->pst.selector = SEL_LC_NEW;
#ifndef SS_MULTICORE_SUPPORT
   mInfo->pst.region = DFLT_REGION;
#else
#endif
   mInfo->pst.pool = DFLT_POOL;
   mInfo->pst.prior = PRIOR0;
   mInfo->pst.route = RTESPEC;
   mInfo->pst.event = 0;


   /* get a semaphore for the TAPA task table */
   SS_ACQUIRE_SEMA(&osCp.tTskTblSem, ret);
   if (ret != ROK)
   {
      SPutMsg(mBuf);
      SUnlock(&osCp.tmrTblLock);

#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT018, ret, "Could not lock TAPA task table");
#endif

      RETVOID;
   }


   /* find the owner TAPA task */
/* mt028.201: modification: multiple procs support related changes */
#ifdef SS_MULTIPLE_PROCS
   procIdIdx = SGetProcIdIdx(tEnt->ownerProc);
   idx = osCp.tTskIds[procIdIdx][tEnt->ownerEnt][tEnt->ownerInst];
#else /* SS_MULTIPLE_PROCS */
   idx = osCp.tTskIds[tEnt->ownerEnt][tEnt->ownerInst];
#endif /* SS_MULTIPLE_PROCS */
   if (idx == SS_TSKNC)
   {
      SS_RELEASE_SEMA(&osCp.tTskTblSem);
      SPutMsg(mBuf);
      SUnlock(&osCp.tmrTblLock);
      RETVOID;
   }


   /* ensure that the TAPA task is hale and hearty */
   tTsk = &osCp.tTskTbl[idx];
   if (!tTsk->used)
   {
      SS_RELEASE_SEMA(&osCp.tTskTblSem);
      SPutMsg(mBuf);
      SUnlock(&osCp.tmrTblLock);
      RETVOID;
   }


   /* write the timer message to the queue of the destination task */
   if (ssDmndQPutLast(&tTsk->sTsk->dQ, mBuf,
               (tTsk->tskPrior * SS_MAX_MSG_PRI) + PRIOR0) != ROK)
   {
      SS_RELEASE_SEMA(&osCp.tTskTblSem);
      SPutMsg(mBuf);
      SUnlock(&osCp.tmrTblLock);

#if (ERRCLASS & ERRCLS_DEBUG)
      MTLOGERROR(ERRCLS_DEBUG, EMT019, ERRZERO,
                        "Could not write to demand queue");
#endif

      RETVOID;
   }


   /* release the semaphore for the TAPA task table */
   SS_RELEASE_SEMA(&osCp.tTskTblSem);


   /* restart the timer */
   arg.tq = osCp.dep.tmrTq;
   arg.tqCp = &osCp.dep.tmrTqCp;
   arg.timers = tEnt->dep.timers;
   arg.cb = (PTR) tEnt;
   arg.evnt = TMR_DEF;
   arg.wait = 0;
   arg.tNum = NOTUSED;
   arg.max = TMR_DEF_MAX;
   arg.wait = tEnt->interval;
   cmPlcCbTq(&arg);


   /* unlock the timer table */
   SUnlock(&osCp.tmrTblLock);


   RETVOID;
}


#ifdef CONAVL
/*
*
*       Fun:   mtConHdlr
*
*       Desc:  This thread reads the console and hands over any
*              data read to a user function.
*
*       Ret:   (thread function)
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PRIVATE Void *mtConHdlr
(
Ptr parm                        /* unused */
)
#else
  /* mt009.21: addition */
PRIVATE Void *mtConHdlr(parm)
Ptr parm;                       /* unused */
#endif
{
   int fd;
   Data data;


   TRC0(mtConHdlr);


   UNUSED(parm);


   /* check if we have a console input file handle */
   if (osCp.dep.conInFp == NULLP)
   {
      /* die */
      RETVALUE(NULLP);
   }

   fd = fileno(osCp.dep.conInFp);

   /* infinite loop */
   for (; ;)
   {
      if ((read(fd, &data, 1)) != 1)
      {
         continue;
      }


      /* call rdConQ, defined by the system service user */
      rdConQ(data);
   }


   /* not reached */
}
#endif /* CONAVL */


#ifdef SS_DRVR_SUPPORT
/*
*
*       Fun:   Interrupt service task handler
*
*       Desc:  This is the interrupt service task handler. It blocks
*              on a pipe from which it reads an isFlag structure. The
*              structure indicates which interrupt service task is to
*              be executed. The thread identifies the task, calls the
*              isTsk function and sends itself a message to repeat
*              this operation until it receives a message to cease.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
  /* mt009.21: addition */
PRIVATE Void *mtIsTskHdlr
(
Ptr tskPtr                      /* pointer to task entry */
)
#else
  /* mt009.21: addition */
PRIVATE Void *mtIsTskHdlr(tskPtr)
Ptr tskPtr;                     /* pointer to task entry */
#endif
{
   int ret;
   MtIsFlag isFlag;


   TRC0(mtIsTskHdlr);


   for (; ;)
   {
      if (read(osCp.dep.isFildes[0], &isFlag, sizeof(isFlag)) != sizeof(isFlag))
      {
         continue;
      }

      switch (isFlag.action)
      {
         case MT_IS_SET:
            osCp.drvrTskTbl[isFlag.id].dep.flag = TRUE;

            /* call the interrupt service task activation function */
            osCp.drvrTskTbl[isFlag.id].isTsk(isFlag.id);

            /* send self a message to keep doing this */
            isFlag.action = MT_IS_RESET;
            ret = write(osCp.dep.isFildes[1], &isFlag, sizeof(isFlag));

#if (ERRCLASS & ERRCLS_DEBUG)
            if (ret != sizeof(isFlag))
            {
               MTLOGERROR(ERRCLS_DEBUG, EMT020, ERRZERO,
                              "write() to pipe failed");
            }
#endif

            break;


         case MT_IS_UNSET:
            osCp.drvrTskTbl[isFlag.id].dep.flag = FALSE;
            break;


         case MT_IS_RESET:
            if (osCp.drvrTskTbl[isFlag.id].dep.flag)
            {
               /* call the interrupt service task activation function */
               osCp.drvrTskTbl[isFlag.id].isTsk(isFlag.id);

               /* send self a message to do this again */
               ret = write(osCp.dep.isFildes[1], &isFlag, sizeof(isFlag));

#if (ERRCLASS & ERRCLS_DEBUG)
               if (ret != sizeof(isFlag))
               {
                  MTLOGERROR(ERRCLS_DEBUG, EMT021, ERRZERO,
                                 "write() to pipe failed");
               }
#endif

            }
            break;


         default:
            /* where did THIS come from?? */
            break;
      }
   }
  /* mt009.21: addition */
  RETVALUE( (Void *) NULLP);

   /* not reached */
}
#endif /* SS_DRVR_SUPPORT */


/*
*
*       Fun:   mtExit
*
*       Desc:  Exit function, shuts down.
*
*       Ret:   Void
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC Void mtExit
(
int arg
)
#else
PUBLIC Void mtExit(arg)
int arg;
#endif
{
   Ticks ticks;
   S8 buf[128];


   TRC0(mtExit);


#ifndef NOFILESYS
   if (osCp.dep.fileOutFp)
   {
      fclose(osCp.dep.fileOutFp);
   }
#endif


   SGetSysTime(&ticks);
   sprintf(buf, "\n\nmtss(posix) ends\nticks: %ld\n", ticks);
   SDisplay(0, buf);


   exit(0);
}


/*
*       interface functions
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
*       File:  mt_ss.c
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
   TRC1(SDisplay);


/* mt020.201 - Fixed typo */
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (buf == NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT022, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif

   
#ifdef CONAVL
   if (osCp.dep.conOutFp) fwrite(buf, strlen(buf), 1, osCp.dep.conOutFp);
#endif


#ifndef NOFILESYS
   if (osCp.dep.fileOutFp) 
      fwrite(buf, strlen(buf), 1, osCp.dep.fileOutFp);
   /*mt031.201 added under compile time flag FLUSHBUFF a call to fflush() */
#ifdef FLUSHBUFF

   fflush(osCp.dep.fileOutFp);

#endif
#endif


   RETVALUE(ROK);
}


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
*       File:  mt_ss.c
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
   TRC1(SSetDateTime);


   UNUSED(dt);


   RETVALUE(ROK);
}
 
  
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
*       Notes:
*
*       File:  mt_ss.c
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
   /*-- mt035.201 : SSI enhancements for micro second in datetime struct --*/
   /* time_t tt; --*/
#ifndef SS_LINUX
   struct timespec ptime;
#else
   struct timeval ptime;
#endif

   struct tm tme;


   TRC1(SGetDateTime);


#if (ERRCLASS & ERRCLS_INT_PAR)
   if (dt == NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT023, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif


/*-- mt035.201 --*/
   /*--
   time(&tt);
   localtime_r(&tt, &tme);
   --*/
#ifndef SS_LINUX
  clock_gettime(CLOCK_REALTIME, &ptime);
#else
  gettimeofday(&ptime, NULL);
#endif
   localtime_r(&ptime.tv_sec, &tme);

   dt->month = (U8) tme.tm_mon + 1;
   dt->day = (U8) tme.tm_mday;
   dt->year = (U8) tme.tm_year;
   dt->hour = (U8) tme.tm_hour;
   dt->min = (U8) tme.tm_min;
   dt->sec = (U8) tme.tm_sec;
   dt->tenths = 0;

#ifdef SS_DATETIME_USEC
#ifndef SS_LINUX
   dt->usec = ptime.tv_nsec / 1000;
#else
   dt->usec = ptime.tv_usec;
#endif
#endif /*-- SS_DATETIME_USEC --*/

   RETVALUE(ROK);
}


/*
*
*       Fun:   Get system time
*
*       Desc:  This function is used to determine the system time.
*
*       Ret:   ROK      - ok
*
*       Notes: osCp.dep.sysTicks is updated by the timer thread.
*
*       File:  mt_ss.c
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
   TRC1(SGetSysTime);


#if (ERRCLASS & ERRCLS_INT_PAR)      
   if (sysTime == NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT024, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif


   *sysTime = osCp.dep.sysTicks;


   RETVALUE(ROK);
}

/* mt021.201 - Addition of SGetRefTime function */
/*
*
*       Fun:   Get referenced time
*
*       Desc:  This function is used to determine the time in seconds
*              and microseconds from a reference time.  The reference
*              time is expressed in seconds from UTC EPOC, January 1,
*              1970.
*
*       Ret:   ROK      - ok
*              RFAILED  - fail
*
*       Notes: Macros are defined for reference times:
*                 SS_REFTIME_01_01_1970
*                 SS_REFTIME_01_01_2002
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetRefTime
(
U32 refTime,             /* reference time */
U32 *sec,
U32 *usec
)
#else
PUBLIC S16 SGetRefTime(refTime, sec, usec)
U32 refTime;             /* reference time */
U32 *sec;
U32 *usec;
#endif
{
     
#ifndef SS_LINUX
   struct timespec ptime;
#else
   struct timeval ptime;
#endif
   
   TRC1(SGetSysTime);

#ifndef SS_LINUX
  clock_gettime(CLOCK_REALTIME, &ptime);
#else
  gettimeofday(&ptime, NULL);
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (sec == NULLP || usec == NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT025, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
   /* mt022.201 - Modification to fix compile warning */
   if (refTime > (U32)(ptime.tv_sec))
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT026, ERRZERO, "Reference time exceeds present time");
      RETVALUE(RFAILED);
   }
#endif

   *sec = ptime.tv_sec - refTime;
#ifndef SS_LINUX
   *usec = ptime.tv_nsec / 1000;
#else
   *usec = ptime.tv_usec;
#endif

  RETVALUE(ROK);

}

  
/*
*
*       Fun:   Get Random Number
*
*       Desc:  Invoked by layer when a pseudorandom number is required.
*
*       Ret:   ROK      - ok
*
*       Notes: Suggested approach uses shuffled Linear Congruential
*              Operators as described in Byte magazine October
*              1984; "Generating and Testing Pseudorandom Numbers"
*
*       File:  mt_ss.c
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
   TRC1(SRandom);


#if (ERRCLASS & ERRCLS_INT_PAR)
   if (value == NULLP)
   {
 /* mt011.21: addition */
      MTLOGERROR(ERRCLS_INT_PAR, EMT028, (ErrVal)0 , "Null pointer");
      RETVALUE(RFAILED);
   }
#endif


   *value = (Random) rand_r(&osCp.dep.randSeed);


   RETVALUE(ROK);
}


/*
*
*       Fun:   Exit Task
*
*       Desc:  This function exits from a task.
*
*       Ret:   ROK      - ok
*
*       Notes: Currently does nothing.
*
*       File:  mt_ss.c
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
   TRC1(SExitTsk);


   RETVALUE(ROK);
}


/*
*
*       Fun:   Exit Interrupt
*
*       Desc:  This function exits from an interrupt.
*
*       Ret:   ROK      - ok
*
*       Notes: Currently does nothing.
*
*       File:  mt_ss.c
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
   TRC1(SExitInt);


   RETVALUE(ROK);
}

  
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
*       Notes: Currently does nothing
*
*       File:  mt_ss.c
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
   TRC1(SHoldInt);


   RETVALUE(ROK);
}


/*
*
*       Fun:   Release Interrupt
*
*       Desc:  This function allows interrupts to be enabled.
*
*       Ret:   ROK      - ok
*
*       Notes: Currently does nothing.
*
*       File:  mt_ss.c
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
   TRC1(SRelInt);


   RETVALUE(ROK);
}


/*
*
*       Fun:   SEnbInt
*
*       Desc:  Enable interrupts
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: Currently does nothing.
*
*       File:  mt_ss.c
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
   TRC1(SEnbInt);


   RETVALUE(ROK);
}


/*
*
*       Fun:   SDisInt
*
*       Desc:  Disable interrupts
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: Currently does nothing.
*
*       File:  mt_ss.c
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
   TRC1(SDisInt);


   RETVALUE(ROK);
}


/*
*
*       Fun:   Get Vector
*
*       Desc:  This function gets the function address stored at the
*              specified interrupt vector.
*
*       Ret:   ROK      - ok
*
*       Notes: Currently does nothing.
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetVect
(
VectNmb vectNmb,                /* vector number */
PIF *vectFnct                   /* vector function */
)
#else
PUBLIC S16 SGetVect(vectNmb, vectFnct)
VectNmb vectNmb;                /* vector number */
PIF *vectFnct;                  /* vector function */
#endif
{
   TRC1(SGetVect);


   UNUSED(vectNmb);
   UNUSED(vectFnct);


   RETVALUE(ROK);
}


/*
*
*       Fun:   Put Vector
*
*       Desc:  This function installs the specified function at the
*              specified interrupt vector.
*
*       Ret:   ROK      - ok
*
*       Notes: Currently does nothing.
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SPutVect
(
VectNmb vectNmb,                /* vector number */
PIF vectFnct                    /* vector function */
)
#else
PUBLIC S16 SPutVect(vectNmb, vectFnct)
VectNmb vectNmb;                /* vector number */
PIF vectFnct;                   /* vector function */
#endif
{
   TRC1(SPutVect);


   UNUSED(vectNmb);
   UNUSED(vectFnct);


   RETVALUE(ROK);
}

/* mt028.201: modification: multiple procs support related changes */
#ifndef SS_MULTIPLE_PROCS

/*
*
*       Fun:   SGetEntInst
*
*       Desc:  This function gets the current entity and instance.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: This function may be called by the OS or Layer 1
*              hardware drivers.
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetEntInst
(
Ent *ent,                       /* entity */
Inst *inst                      /* instance */
)
#else
PUBLIC S16 SGetEntInst(ent, inst)
Ent *ent;                       /* entity */
Inst *inst;                     /* instance */
#endif
{
   S16 i;
   S16 ret;
   pthread_t tId;
   SsSTskEntry *sTsk;


   TRC1(SGetEntInst);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check pointers */
   if (ent == NULLP  ||  inst == NULLP)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT029, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif


   /* get the thread id */
   tId = pthread_self();


   /* find the system task in whose context we're running */
   sTsk = NULLP;
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }
   for (i = 0;  i < SS_MAX_STSKS;  i++)
   {
      if (pthread_equal(osCp.sTskTbl[i].dep.tId, tId))
      {
         sTsk = &osCp.sTskTbl[i];
         break;
      }
   }
   if (sTsk != NULLP)
   {
         *ent = sTsk->dep.ent;
         *inst = sTsk->dep.inst;
   }
   SUnlock(&osCp.sTskTblLock);


   RETVALUE(ret == ROK ? ROK : RFAILED);
}

  
/*
*
*       Fun:   SSetEntInst
*
*       Desc:  This function sets the current entity and instance.
*
*       Ret:   ROK      - ok
*
*       Notes:
*
*       File:  mt_ss.c
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
   S16 i;
   S16 ret;
   pthread_t tId;
   SsSTskEntry *sTsk;


   TRC1(SSetEntInst);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check entity and instance IDs */
   if (ent >= ENTNC  ||  inst >= INSTNC)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT030, ERRZERO, "Invalid entity/instance");
      RETVALUE(RFAILED);
   }
#endif


   /* get the thread id */
   tId = pthread_self();


   /* find the system task in whose context we're running */
   sTsk = NULLP;
   ret = SLock(&osCp.sTskTblLock);
   if (ret != ROK)
   {
      RETVALUE(RFAILED);
   }
   for (i = 0;  i < SS_MAX_STSKS;  i++)
   {
      if (pthread_equal(osCp.sTskTbl[i].dep.tId, tId))
      {
         sTsk = &osCp.sTskTbl[i];
         break;
      }
   }
   if (sTsk != NULLP)
   {
         sTsk->dep.ent = ent;
         sTsk->dep.inst = inst;
   }
   SUnlock(&osCp.sTskTblLock);


   RETVALUE(ret == ROK ? ROK : RFAILED);
}

#endif /* SS_MULTIPLE_PROCS */

#ifdef SS_DRVR_SUPPORT

/*
*
*       Fun:   SSetIntPend
*
*       Desc:  Set interrupt pending flag
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC INLINE S16 SSetIntPend
(
U16 id,                         /* driver task identifier */
Bool flag                       /* flag */
)
#else
PUBLIC INLINE S16 SSetIntPend(id, flag)
U16 id;                         /* driver task identifier */
Bool flag;                      /* flag */
#endif
{
   MtIsFlag isFlag;


   TRC1(SSetIntPend);


#if (ERRCLASS & ERRCLS_INT_PAR)
   if (id >= SS_MAX_DRVRTSKS  ||  osCp.drvrTskTbl[id].used == FALSE)
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT031, id, "Invalid instance");
      RETVALUE(RFAILED);
   }
#endif


   isFlag.id = id;
   isFlag.action = (flag ? MT_IS_SET : MT_IS_UNSET);

   if (write(osCp.dep.isFildes[1], &isFlag, sizeof(isFlag)) != sizeof(isFlag))
   {
      RETVALUE(RFAILED);
   }


   RETVALUE(ROK);
}
#endif  /* SS_DRVR_SUPPORT */

/* mt022.201 - Addition of SRegInfoShow function */
/*
*
*       Fun:   SRegInfoShow
*
*       Desc:  This function displays the memory usage information
*              for the destined region. It will show the usage of
*              each configured bucket and the heap for the specified region.
*
*       Ret:   ROK          OK
*              RFAILED      Region not registered
*
*       Notes: A Sample Output from the function 
*       Bucket Memory: region 1
*       ====================================================
*       Bucket  Number of Blks configured  Size  Allocated
*       ====================================================
*       0                     1             16         1
*       1                     1             32         0
*       2                     1             80         0
*       3                     1            256         0
*       4                     1            320         0
*
*       ---------------
*       Heap Memory: region 1
*       Heap Size: 0
*       Heap Allocated: 0
*       Heap Segmented blocks: 0
*
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SRegInfoShow
(
Region region,
U32 *availmem
)
#else
PUBLIC S16 SRegInfoShow(region, availmem)
Region region;
U32 *availmem;
#endif
{
   U16   idx;
   Txt   prntBuf[100];
   
   TRC1(SRegInfoShow);

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (region > (SS_MAX_REGS-1) )
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT032, ERRZERO, "Invalid Region");
      RETVALUE(RFAILED);
   }
#endif

   *availmem = 0;
   
   sprintf(prntBuf, "\n\nBucket Memory: region %d\n", region);
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "====================================================\n");
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "Bucket  Number of Blks configured  Size  Allocated\n");
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "====================================================\n");
   SDisplay(0, prntBuf);
   

   for (idx = 0; idx < mtCMMRegCb[region]->numBkts; idx++)
   {
      sprintf(prntBuf, "%2d              %8lu          %5lu  %8lu\n", 
              idx, mtCMMRegCb[region]->bktTbl[idx].numBlks,
              mtCMMRegCb[region]->bktTbl[idx].size,
              mtCMMRegCb[region]->bktTbl[idx].numAlloc);
      SDisplay(0, prntBuf);
      *availmem = *availmem + (mtCMMRegCb[region]->bktTbl[idx].size * \
          (mtCMMRegCb[region]->bktTbl[idx].numBlks -  \
           mtCMMRegCb[region]->bktTbl[idx].numAlloc));
   }
   sprintf(prntBuf, "\n---------------\n");
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "Heap Memory: region %d\n", region);
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "Heap Size: %lu\n", mtCMMRegCb[region]->heapSize);
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "Heap Allocated: %lu\n", 
           (mtCMMRegCb[region]->heapSize - mtCMMRegCb[region]->heapCb.avlSize));
   SDisplay(0, prntBuf);
   *availmem = *availmem + mtCMMRegCb[region]->heapCb.avlSize;
#if (ERRCLASS & ERRCLS_DEBUG)
   sprintf(prntBuf, "Heap Segmented blocks: %d\n",
                    mtCMMRegCb[region]->heapCb.numFragBlk);
   SDisplay(0, prntBuf);
#endif

   RETVALUE(ROK);
}   

/* mt033.201 - addition of API to return the memory statistical data */
/*
*
*       Fun:   SGetRegInfo
*
*       Desc:  This function returns the memory usage information
*              for the destined region. It will return the usage of
*              each configured bucket and the heap for the specified region.
*
*       Ret:   ROK   OK
*              RFAILED   Region not registered
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetRegInfo
(
Region region,
SsMemDbgInfo *dbgInfo
)
#else
PUBLIC S16 SGetRegInfo(region, dbgInfo)
Region region;
SsMemDbgInfo *dbgInfo;
#endif
{
   U32 idx;

   TRC1(SGetRegInfo);

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (region >= mtMemoCfg.numRegions )
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT033, ERRZERO, "Invalid Region");
      RETVALUE(RFAILED);
   }
#endif

   dbgInfo->availmem = 0;

   if (mtCMMRegCb[region]->numBkts > SS_MAX_BKT_PER_DBGTBL)
      dbgInfo->numBkts = SS_MAX_BKT_PER_DBGTBL;
   else
      dbgInfo->numBkts = mtCMMRegCb[region]->numBkts;

   for (idx = 0; (idx < mtCMMRegCb[region]->numBkts) && (idx < SS_MAX_BKT_PER_DBGTBL); idx++)
   {
      dbgInfo->bktDbgTbl[idx].numBlks = mtCMMRegCb[region]->bktTbl[idx].numBlks;
      dbgInfo->bktDbgTbl[idx].size = mtCMMRegCb[region]->bktTbl[idx].size;
      dbgInfo->bktDbgTbl[idx].numAlloc = mtCMMRegCb[region]->bktTbl[idx].numAlloc;

      dbgInfo->availmem += (mtCMMRegCb[region]->bktTbl[idx].size * \
                           (mtCMMRegCb[region]->bktTbl[idx].numBlks -  \
                            mtCMMRegCb[region]->bktTbl[idx].numAlloc));
   }

   dbgInfo->region = region;

   dbgInfo->heapSize = mtCMMRegCb[region]->heapSize;

   dbgInfo->heapAlloc = (mtCMMRegCb[region]->heapSize - \
                         mtCMMRegCb[region]->heapCb.avlSize);

   dbgInfo->availmem += mtCMMRegCb[region]->heapCb.avlSize;

#if (ERRCLASS & ERRCLS_DEBUG)
   dbgInfo->numFragBlk = mtCMMRegCb[region]->heapCb.numFragBlk;
#endif

   RETVALUE(ROK);
}

/* mt033.201 - addition of APIs to print the memory statistical data
* as defined by SSI enhancements 
*/
#ifdef SSI_DEBUG_LEVEL1
/*
*
*       Fun:   SPrintRegMemStatusInfo
*
*       Desc:  This function displays the memory usage information
*              for the destined region. It will show the total memory
*              used for static and dynamic memory if typeFlag is
*              SS_MEM_BKT_ALLOC_PROFILE. It will show the number of
*              memory block allocated for a particular size if typeFlag
*              is SS_MEM_BLK_SIZE_PROFILE from the hash list by
*              calling SRegPrintMemStats.
*
*       Ret:   ROK
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SPrintRegMemStatusInfo
(
Region region,
U8 typeFlag
)
#else
PUBLIC S16 SPrintRegMemStatusInfo(region, typeFlag)
Region region;
U8 typeFlag;
#endif
{
   Txt prntBuf[150];
   U32 idx;
   U32 statMemSize;
   U32 dynMemSize;

   TRC1(SPrintRegMemStatusInfo);

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (region >= mtMemoCfg.numRegions )
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT034, ERRZERO, "Invalid Region");
      RETVALUE(RFAILED);
   }
#endif

   /* initialize the counters*/
   statMemSize = 0;
   dynMemSize = 0;

   if (typeFlag == SS_MEM_BKT_ALLOC_PROFILE)
   {
      /* total static and dynamic memory allocated from all the buckets in region requested */
      sprintf(prntBuf, "\nAllocated Memory profile of Buckets from region: %d \n", region);
      SDisplay(0, prntBuf);
      sprintf(prntBuf, "===========================================\n");
      SDisplay(0, prntBuf);
      sprintf(prntBuf, "Bucket        Static Memory      Dynamic Memory\n");
      SDisplay(0, prntBuf);
      sprintf(prntBuf, "===========================================\n");
      SDisplay(0, prntBuf);
      for (idx = 0; idx < mtCMMRegCb[region]->numBkts; idx++)
      {
         sprintf(prntBuf, "%2lu           %8lu           %8lu\n", idx,
                     mtCMMRegCb[region]->bktTbl[idx].staticMemUsed,
                     mtCMMRegCb[region]->bktTbl[idx].dynamicMemUsed);
         SDisplay(0, prntBuf);
         /* update the total count */
         statMemSize += mtCMMRegCb[region]->bktTbl[idx].staticMemUsed;
         dynMemSize += mtCMMRegCb[region]->bktTbl[idx].dynamicMemUsed;
      }
      /* from buckets */
      sprintf(prntBuf, "Total Static Memory allocated from buckets: %lu\n", statMemSize);
      SDisplay(0, prntBuf);
      sprintf(prntBuf, "Total Dynamic Memory allocated from buckets: %lu\n", dynMemSize);
      SDisplay(0, prntBuf);
      /* from heap */
      sprintf(prntBuf, "\n\nAllocated Memory profile from Heap of region: %d \n", region);
      SDisplay(0, prntBuf);
      sprintf(prntBuf, "STATIC MEMORY: %lu     DYNAMIC MEMORY:%lu \n",
         mtCMMRegCb[region]->heapCb.staticHeapMemUsed, mtCMMRegCb[region]->heapCb.dynamicHeapMemUsed);
      SDisplay(0, prntBuf);
   }
   else if (typeFlag == SS_MEM_BLK_SIZE_PROFILE)
   {
      /* Bucket Memory allocation Statistics */
      RETVALUE(SPrintRegMemStats(region));
   }
   else
   {
      /* error case */
      sprintf(prntBuf, "\n Invalid choice \n");
      SDisplay(0, prntBuf);
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   SPrintRegMemStats
*
*       Desc:  This function displays the memory usage information for
*              the destined region. It will show the number of memory
*              block allocated for a particular size from the hash list.
*
*       Ret:   ROK
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PRIVATE S16 SPrintRegMemStats
(
Region region
)
#else
PRIVATE S16 SPrintRegMemStats(region)
Region region;
#endif
{
   CmMmHashListCp *hashListCp;
   Txt prntBuf[150];
   U32 idx;
   U32 cntEnt;

   TRC1(SPrintRegMemStats);

   hashListCp = &mtCMMRegCb[region]->hashListCp;

   sprintf(prntBuf, "\n\nSize Vs. NumAttempts and Alloc/Dealloc profile of region %d\n", region);
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "Maximum Entries: %u    Current Entries: %u\n",
                     hashListCp->numOfbins, hashListCp->numOfEntries);
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "===================================\n");
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "Block Size      Total number of requests\n");
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "===================================\n");
   SDisplay(0, prntBuf);

   for (idx = 0, cntEnt=0; (cntEnt < hashListCp->numOfEntries) &&
               (idx < CMM_STAT_HASH_TBL_LEN); idx++)
   {
      if (hashListCp->hashList[idx].numAttempts)
      {
         cntEnt++;
         sprintf(prntBuf, "%8lu           %8lu\n", hashListCp->hashList[idx].size,
                     hashListCp->hashList[idx].numAttempts);
         SDisplay(0, prntBuf);
      }
   }

   sprintf(prntBuf, "\nAllocation/De-allocation profile in Buckets\n");
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "=================================================\n");
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "Bucket    Num of Alloc Attempts    Num of De-alloc Attempts\n");
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "=================================================\n");
   SDisplay(0, prntBuf);

   /* Print the statistics of total number of alloc/de-alloc attempts in each bucket of this region */
   for (idx = 0; idx < mtCMMRegCb[region]->numBkts; idx++)
   {
      sprintf(prntBuf, "%4lu        %8lu             %8lu\n", idx,
                           mtCMMRegCb[region]->bktTbl[idx].numAllocAttempts,
                           mtCMMRegCb[region]->bktTbl[idx].numDeallocAttempts);
      SDisplay(0, prntBuf);
   }
   sprintf(prntBuf, "\nAllocation/De-allocation profile in Heap\n");
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "Num of Alloc Attempts: %lu      Num of De-alloc Attempts: %lu\n",
                           mtCMMRegCb[region]->heapCb.numAllocAttempts,
                           mtCMMRegCb[region]->heapCb.numDeallocAttempts);
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "\n");
   SDisplay(0, prntBuf);

   RETVALUE(ROK);
}

/*
*
*       Fun:   SRegMemErrHdlr
*
*       Desc:  This function handles the errors returned from the memory
*              related functions. Customers are suggested to modify this
*              API according to their specific requirement.
*
*       Ret:   ROK   OK
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC Void SRegMemErrHdlr
(
Region region,
Data *ptr,
S16 errCode
)
#else
PUBLIC Void SRegMemErrHdlr(region, ptr, errCode)
Region region;
Data *ptr;
S16 errCode;
#endif
{
   Txt prntBuf[150];

   TRC1(SRegMemErrHdlr);

   if (errCode == RDBLFREE)
   {
      sprintf(prntBuf, "\nDouble free attempted at location:%8p  in region:%d\n", ptr, region);
      SDisplay(0, prntBuf);
   }
   else if (errCode == RTRAMPLINGNOK)
   {
      sprintf(prntBuf, "\nMemory Trampling crossed Threshold in region:%d\n", region);
      SDisplay(0, prntBuf);
   }

   RETVOID;
}

/*
*
*       Fun:   SPrintRegMemProfile
*
*       Desc:  This function displays the memory profile information
*              for the destined region. This function prints for:
*              1) each memory bucket-Block address, size, size for which it is allocated, free/allocated, static/dynamic
*              2) heap - memory block address, size, requested size, free/allocated, static/dynamic
*
*       Ret:   ROK   OK
*
*       Notes:
*
*       File:  mt_ss.c
*
*/
#ifdef ANSI
PUBLIC S16 SPrintRegMemProfile
(
Region region
)
#else
PUBLIC S16 SPrintRegMemProfile(region)
Region region;
#endif
{
   CmMmHeapCb *heapCb;
   CmMmRegCb *regCb;
   CmMmBlkHdr *curBktBlk;
   CmHEntry *curHBlk;
   Size offsetToNxtBlk;
   Size hdrSize;
   Txt prntBuf[250];
   U32 idx;
   U32 blkCnt;


   TRC1(SPrintRegMemProfile);

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (region >= mtMemoCfg.numRegions )
   {
      MTLOGERROR(ERRCLS_INT_PAR, EMT035, ERRZERO, "Invalid Region");
      RETVALUE(RFAILED);
   }
#endif

   regCb = mtCMMRegCb[region];

   /* memory profile */
   sprintf(prntBuf, "\n\nFull Memory Profile of region %d\n", region);
   SDisplay(0, prntBuf);

   /* bucket profile */
   sprintf(prntBuf, "\nBucket Profile\n");
   SDisplay(0, prntBuf);

   for (idx = 0; idx < regCb->numBkts; idx++)
   {

      sprintf(prntBuf, "\nBucket number:%4lu  of Size:%lu  Num of Blocks: %lu\n",
                        idx, regCb->bktTbl[idx].size, regCb->bktTbl[idx].numBlks);
      SDisplay(0, prntBuf);

      sprintf(prntBuf, "==========================================================================\n");
      SDisplay(0, prntBuf);
      sprintf(prntBuf, " Block    Location    Free/Allocated  Static/dynamic  Size requested\n");
      SDisplay(0, prntBuf);
      sprintf(prntBuf, "==========================================================================\n");
      SDisplay(0, prntBuf);

      offsetToNxtBlk = regCb->bktTbl[idx].size + sizeof(CmMmBlkHdr);

      for (blkCnt=0, curBktBlk = (CmMmBlkHdr *)(regCb->bktTbl[idx].bktStartPtr);
            ((curBktBlk) && (blkCnt < regCb->bktTbl[idx].numBlks));
            curBktBlk = (CmMmBlkHdr *)((Data *)curBktBlk + offsetToNxtBlk), blkCnt++)
      {
         sprintf(prntBuf, "%6lu   %8p", blkCnt, (void *)curBktBlk);
         SDisplay(0, prntBuf);
         /* check if it is a sane block, elxe jump to next block */
         if (cmMmRegIsBlkSane(curBktBlk) != ROK)
         {
            sprintf(prntBuf, "     Trampled                         \n");
            SDisplay(0, prntBuf);

            continue;
         }

         if (CMM_IS_STATIC(curBktBlk->memFlags))
         {
            sprintf(prntBuf, "     Allocated     Static      %8lu\n", curBktBlk->requestedSize);
            SDisplay(0, prntBuf);
         }
         else if (CMM_IS_DYNAMIC(curBktBlk->memFlags))
         {
            sprintf(prntBuf, "     Allocated       Dynamic      %8lu\n", curBktBlk->requestedSize);
            SDisplay(0, prntBuf);
         }
         else if (CMM_IS_FREE(curBktBlk->memFlags))
         {
            sprintf(prntBuf, "     Free                        %8lu\n", curBktBlk->requestedSize);
            SDisplay(0, prntBuf);
         }
         else
         {
            sprintf(prntBuf, "     Trampled                         \n");
            SDisplay(0, prntBuf);
         }
      }
   }

   /* heap profile */
   sprintf(prntBuf, "\nHeap Profile\n");
   SDisplay(0, prntBuf);

   /* point to heapCb */
   heapCb = &(regCb->heapCb);

   sprintf(prntBuf, "\nHeap Start: %8p          Heap End: %8p\n", heapCb->vStart, heapCb->vEnd);
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "==========================================================================\n");
   SDisplay(0, prntBuf);
   sprintf(prntBuf, " Block     Location      Size    Free/Allocated   Static/dynamic  Size requested\n");
   SDisplay(0, prntBuf);
   sprintf(prntBuf, "==========================================================================\n");
   SDisplay(0, prntBuf);

   /* traverse the entire heap to output the heap profile */
   hdrSize = sizeof(CmHEntry);
   for (blkCnt=0, curHBlk = (CmHEntry *)heapCb->vStart;
            ((curHBlk) && (curHBlk < (CmHEntry *)heapCb->vEnd)); blkCnt++)
   {
      sprintf(prntBuf, "%6lu   %8p", blkCnt, (void *)curHBlk);
      SDisplay(0, prntBuf);

      /* check if it is a sane block, elxe jump to next block */
      if (cmMmRegIsBlkSane((CmMmBlkHdr *)curHBlk) != ROK)
      {
         sprintf(prntBuf, "                Trampled                         \n");
         SDisplay(0, prntBuf);

         sprintf(prntBuf, "Trampled block encountered: Stopping heap profile\n");
         SDisplay(0, prntBuf);

         /* 
         * To go to next block in the heap we do not have any offset value
         * other than curHBlk->size. As the block is already trampled
         * we cannot rely on this size. So it is better to stop here unless there
         * exists any other mechanism(?) to know the offset to next block. 
         */
         RETVALUE(ROK);
      }

      sprintf(prntBuf, "   %8lu", curHBlk->size);
      SDisplay(0, prntBuf);

      if (CMM_IS_STATIC(curHBlk->memFlags))
      {
         sprintf(prntBuf, "     Allocated       Static       %8lu\n", curHBlk->requestedSize);
         SDisplay(0, prntBuf);
      }
      else if (CMM_IS_DYNAMIC(curHBlk->memFlags))
      {
         sprintf(prntBuf, "     Allocated       Dynamic      %8lu\n", curHBlk->requestedSize);
         SDisplay(0, prntBuf);
      }
      else if (CMM_IS_FREE(curHBlk->memFlags))
      {
         sprintf(prntBuf, "     Free                      %8lu\n", curHBlk->requestedSize);
         SDisplay(0, prntBuf);
      }
      else
      {
         sprintf(prntBuf, "     Trampled                         \n");
         SDisplay(0, prntBuf);
      }
      /* goto next block in the heap */
      curHBlk = (CmHEntry *)((Data *)curHBlk + hdrSize + curHBlk->size);

   }

   RETVALUE(ROK);
}
#endif /* SSI_DEBUG_LEVEL1 */

/*-- mt035.201 : Added new API for timestamp --*/
/*--
*
*       Fun:   Get TimeStamp
*
*       Desc:  This function is used to Get TimeStamp in micro seconds
*
*       Ret:   ROK      - ok
*              RFAILED  - error
*
*       Notes:
*
*       File:  mt_ss.c
*
--*/
#ifdef ANSI
PUBLIC S16 SGetTimeStamp
(
S8    *ts
)
#else
PUBLIC S16 SGetTimeStamp(ts)
S8    *ts;
#endif
{

#ifndef SS_LINUX
   struct timespec ptime;
#else
   struct timeval ptime;
#endif

   struct tm* ptm;
   S8 time_string[40];
   S32 microseconds;

   TRC1(SGetTimeStamp);

#ifndef SS_LINUX
  clock_gettime(CLOCK_REALTIME, &ptime);
#else
  gettimeofday(&ptime, NULL);
#endif

   /* Obtain the time of day, and convert it to a tm struct. --*/
   ptm = localtime (&ptime.tv_sec);

   /* Format the date and time, down to a single second. --*/
   strftime (time_string, sizeof (time_string), "%a %b %d %Y %H:%M:%S", ptm);

   /* Compute microseconds. --*/
#ifndef SS_LINUX
   microseconds = ptime.tv_nsec / 1000;
#else
   microseconds = ptime.tv_usec;
#endif

   /* Print the formatted time, in seconds, followed by a decimal point
      and the microseconds. --*/
   sprintf(ts, "%s.%03ld", time_string, microseconds);

   RETVALUE(ROK);

}
/*-- mt037.201 : Added new API for SGetSystemTsk --*/
/*
*
*       Fun:   Get SGetSystemTsk
*
*       Desc:  This function is used to Get sytem task id
*
*       Ret:   task id
*
*       Notes:
*
*       File:  mt_ss.c
*
--*/
#ifdef ANSI
PUBLIC U32 SGetSystemTsk
(
Void
)
#else
PUBLIC U32 SGetSystemTsk()
#endif
{
   TRC1(SGetSystemTskS);

   RETVALUE(pthread_self());

} /* end of SGetSystemTsk */



/********************************************************************30**
  
         End of file:     pt_ss.c@@/main/1 - Mon Apr  5 18:19:20 2010
  
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
1.1          ---      kp   1. MTSS-Solaris release 2.1

1.1+         mt003.21 kp   1. Bug fix in mtTskHdlr(); do not resend the
                              permanent tick message to a task that got
                              deregistered/detached
             mt005.21 vrp  2. Task set prior to invoking timer activation
                              function
             mt006.21 ada  3. Console thread made to block
1.1+         mt008.21 jn   4. mtTmrHdlr changed to correct the time 
                              difference between MTSS time and real
                              Unix Time. "Nanosleep" resulted in longer
                              then set time delay.  This is because
                              the timer thread would be suspended for
                              more than the set delay because of the
                              scheduling of other activity by the system.
                              The problem has now been corrected. 
1.1+         mt009.21 jn   5. Removed errors generated while using
                              C++ compiler.
             mt010.21 ada  6. Initialized the common timer library 
                              structures in ssdInitTmr 
             mt011.21 jjn  7. In the MTLOGERROR macro, parameter Errval was
                              passed as PTR. Errval is of type U32. The 
                              parameter datatype has been corrected.
             mt014.21 jjn  8. In the function, the variable fd was 
                              declared under ifndef CONSTDIO, whereas
                              it was also used if CONSTDIO was defined.
                              This has been corrected.
             mt015.21 ada  9. Changes to compile on Linux captured
                              under flag SS_LINUX
             mt017.21 bdu 10. Added compile time flag CONRD
            mt018.201 bdu 11. Added the mtss memory configuration matrix,
                              this will make memory configuration easier.
            mt019.201 bdu 12. We only need to apply strm module for 
                              the DFLT_REGION.
            mt020.201 bjp 13. Fixed support for no command line NOCMDLINE
                              Added destroy of attr object when creating
                              system task.
                              Typo fix for SDisplay
            mt021.201 bjp 14. Added SGetRefTime function
                              Added configuration of stack size for threads
            mt022.201 bjp 15. Fixed bug in mtGetOpts when NOCMDLINE is defined
                              Addition of region info for shared relay
                              Addition of region for memory configuration tool
                              Addition of SRegInfoShow function
                              Modification to fix warning in SGetRefTime
            mt023.201 sdg 1.  Added SThreadYield() to support thread yield.
            mt024.201 fa 1.  modified SThreadYield implementation
                         2.  used SThreadYield implementation in mtTskHdlr
                             instead of sleep(0) to yield
            mt025.201 bjp  1. Modification to lock mtTmrHdlr until
                              tst() task registration is complete 
2.1+        mt027.201 bjp  1. Modification for SRegCfgTmr support
2.1+        mt028.201 bn   1. Added compile time flag UNMASK_SIG in ssdInitGen
                              to allow not to mask signals
                           2. Surrounded main by compile time flag API_MAIN to
                              allow customers use their own main and provided 
                              ssMain function with the same parameters instead 
                              to be called from customer's main
                           3. modified mtGetOpts() so that if executable called
                              with "-f" option and file name residing in the 
                              same directory and specifying memory 
                              configuration, the defaule memory configuration 
                              will be overwritten.
                      rk   4. Modification for ERRCLS_FTHA support
                      kkj  5. Added support for multiple procIds
2.1+        mt030.201 bn   1. Added added a loop under #ifdef SLES9_PLUS in 
                              main() to avoid child processes being killed upon
                              exiting main thread.
            mt031.201 bn   1. added a call to fflush() in SDisplay under compile                              time flag FLUSHBUFF.
2.1+        mt033.201 vk   1. addition of API SGetRegInfo and SSI enhancements
2.1+        mt034.201 gs   1. SSI enhancements under SS_PERF
2.1+        mt035.201 ss   1. SSI enhancements for micro second in datetime struct.
                           2. Added new API for timestamp
2.1+        mt036.201 bn   3. Corrected non-ansi declaration of SGetTimeStamp
2.1+        mt037.201 bn   4. removed redundant locks
                           5. added SGetSystemTsk
2.1+        mt038.201 bn   6. changed how sem_wait is called in mtTskHdlr and 
                              mtTmrHdlr
2.1+        mt039.201 bn   7. changed how nanosleep is called in mtTmrHdlr
2.1+        mt040.201 bn   1. changed how fcanf is called for 64 bit architectre
/main/1      ---      rp   1. SSI enhancements for Multi-core architecture support
*********************************************************************91*/
