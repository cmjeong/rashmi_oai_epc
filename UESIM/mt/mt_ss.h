

/********************************************************************20**
 
     Name:     MTSS -- implementation specific definitions
 
     Type:     C include file
 
     Desc:     Various macro definitions demanded by systems services.
               The contents of these are for the MTSS implementation.
 
     File:     mt_ss.h
 
     Sid:      mt_ss.h@@/main/2 - Mon Apr  5 18:19:19 2010
 
     Prg:      kp
 
*********************************************************************21*/


#ifndef __MTSSH__
#define __MTSSH__


/* --- interface to SS --- */

/* general */
#define SS_PROC_ID                      PID_STK(1)

/* task related */
/* mt028.201: addition: multiple procs support related changes */
#ifdef SS_MULTIPLE_PROCS
#define SS_MAX_PROCS                    100 /* max entries for proc list */
#endif /* SS_MULTIPLE_PROCS */

#define SS_MAX_ENT                      255
#define SS_MAX_INST                     8

/* mt028.201: modification: multiple procs support related changes */
#ifndef SS_MULTIPLE_PROCS
#define SS_MAX_TTSKS                    30

#ifndef SS_MULTICORE_SUPPORT
#define SS_MAX_STSKS                    30
#else
#define SS_MAX_STSKS                    6
#endif /* SS_MULTICORE_SUPPORT */

#else /* SS_MULTIPLE_PROCS */
#define SS_MAX_TTSKS                    1000 
#define SS_MAX_STSKS                    30
#endif /* SS_MULTIPLE_PROCS */

#ifdef SS_DRVR_SUPPORT
#define SS_MAX_DRVRTSKS                 70
#endif

#ifdef SS_RTR_SUPPORT
   /* mt0012.21 : Addition */
#define SS_MAX_RTRTSKS                  255
#endif


/* timer related */
#define SS_MAX_TMRS                     45

/* memory related */
/* mt022.201 - Modification for shared memory relay and memcal regions */
#if (defined(RY_ENBS5SHM) && defined(USE_MEMCAL))
#define SS_MAX_REGS                     3
#define RY_SHM_REGION                   (SS_MAX_REGS - 2)
#define SS_STATIC_REGION                (SS_MAX_REGS - 1)
#else

#if (defined(RY_ENBS5SHM) || defined(USE_MEMCAL))
#define SS_MAX_REGS                     2
#ifdef RY_ENBS5SHM
#define RY_SHM_REGION                   (SS_MAX_REGS - 1)
#endif
#ifdef USE_MEMCAL
#define SS_STATIC_REGION                (SS_MAX_REGS - 1)
#endif
#else
#ifndef SS_MULTICORE_SUPPORT
#define SS_MAX_REGS                        1
#else
#define SS_MAX_REGS                    SS_MAX_STSKS 
#endif /* SS_MULTICORE_SUPPORT */
#endif
#endif

#ifdef CMM_MAX_BKT_ENT
#define SS_MAX_POOLS_PER_REG            CMM_MAX_BKT_ENT
#else
#define SS_MAX_POOLS_PER_REG            5
#endif

/* locks */
#define SS_STSKTBL_LOCK                 SS_LOCK_MUTEX
#define SS_STSKENTRY_LOCK               SS_LOCK_MUTEX
#define SS_TMRTBL_LOCK                  SS_LOCK_MUTEX
#define SS_DMNDQ_LOCK                   SS_LOCK_MUTEX
#define SS_DRVRENTRY_LOCK               SS_LOCK_MUTEX
#define SS_RTRENTRY_LOCK                SS_LOCK_MUTEX


/* types needed by common SSI code */
#define SsSemaId                        sem_t
#define SLockId                         pthread_mutex_t


/* calls needed by common SSI code */
#define SInitLock(l, t)                 pthread_mutex_init(l, NULL)
#define SLock(l)                        pthread_mutex_lock(l)
#define SUnlock(l)                      pthread_mutex_unlock(l)
#define SDestroyLock(l)                 pthread_mutex_destroy(l)

#define ssInitSema(s, c)                sem_init(s, 0, c)
#define ssWaitSema(s)                   sem_wait(s)
#define ssPostSema(s)                   sem_post(s)
#define ssDestroySema(s)                sem_destroy(s)

#define SS_CHECK_CUR_STSK(t)            (pthread_equal(pthread_self(), \
                                          (t)->dep.tId))
 /* mt013.21: Addition */
#define SInitSemaphore(s, c)            sem_init(s, 0, c)
#define SWaitSemaphore(s)               sem_wait(s)                   
#define SPostSemaphore(s)               sem_post(s) 
#define SDestroySemaphore(s)            sem_destroy(s)
                
#define ssdPstTsk(p, m, t)

/* added SExit() for exiting process : mt017.21 */
#define SExit()                         exit(0)        
  /* mt007.21 addition */ 
/* calls needed by Message Functions */
#define SMemCpy(d,s,c)  memcpy(d,s,c)
#define SMemSet(s,c,n)  memset(s,c,n)
/* --- internal to MTSS-Solaris --- */


/* mt027.201 - Modification for SRegCfgTmr support */
/* number of nanoseconds per tick (used in nanosleep()) */
#define MT_TICK_CNT             (((U32)0x3B9ACA00)/SS_TICKS_SEC)


/* interrupt service flags */
#define MT_IS_SET               0
#define MT_IS_UNSET             1
#define MT_IS_RESET             2

/******************************************************************
 mt018.201 - Memory Configuration. 

Memory block sizes and counts for memory manager configuration 
There is no restriction in the size of each block for the bucket.
However, it is recommended that the bucket size should be word aligned.
The CMM (Common Memory Manager) also create a look up table which map 
the size to the bucket index. 
The number of entry in the lookup table  (CMM_MAX_MAP_ENT, defined in
cm_mem.h) = ((maximum bucket size)/(bucket quantum size)) + 1. 
The CMM_MAX_MAP_ENT should be changed depending on the bucket sizes
that are configured below.
*******************************************************************/ 

/* Bucket 0 configuration */ 
/* mt032.201 changed  MT_BKT_0_DSIZE from 120 to 128 for 64k compilation */
#define MT_BKT_0_DSIZE          128
#define MT_BKT_0_NUMBLKS        3500

/* Bucket 1 configuration */ 
#define MT_BKT_1_DSIZE          256
#define MT_BKT_1_NUMBLKS        10500

/* Bucket 2 configuration */ 
#define MT_BKT_2_DSIZE      320      /* Fill in this value as required */ 
#define MT_BKT_2_NUMBLKS    1        /* Fill in this value as required */ 


/* Bucket 3 configuration */ 
#define MT_BKT_3_DSIZE     640      /* Fill in this value as required */ 
#define MT_BKT_3_NUMBLKS   1        /* Fill in this value as required */ 


#define MT_MAX_BKTS             2

/* mt029.201 corrected typos */
/* memory pool data size definitions for pool-to-size mapping table */
#define MT_POOL_3_DSIZE        (MT_BKT_3_DSIZE-(sizeof(SsMblk)+sizeof(SsDblk)))
#define MT_POOL_2_DSIZE        (MT_BKT_2_DSIZE-(sizeof(SsMblk)+sizeof(SsDblk)))
#define MT_POOL_1_DSIZE        (MT_BKT_1_DSIZE-(sizeof(SsMblk)+sizeof(SsDblk)))
#define MT_POOL_0_DSIZE        (MT_BKT_0_DSIZE-(sizeof(SsMblk)+sizeof(SsDblk)))

      

/* mt026.201 - Modification to increase default heap size */
/* memory size used for heap by the memory manager (2MB) */
#define MT_HEAP_SIZE            2097152U

#ifndef USE_MEMCAL
#define STATIC_MEM_CFG
#endif

/* mt022.201 - definition of MT_BKTQNSIZE */
#define MT_BKTQNSIZE 16

/* mt021.201 - Addition for setting stack size for threads */
/* Configuration for stack size (in bytes) of spawned threads
 * Size of zero gives default of 1 MB or 2 MB for 32 bit or 64 bit
 * compilers, respectively */
#define MT_TASK_STACK           NULLD        /* stack size for task handler */
#define MT_ISTASK_STACK         NULLD        /* stack size for IS task handler */
#define MT_TMRTASK_STACK        NULLD        /* stack size for timer handler */
#define MT_CONSOLE_STACK        NULLD        /* stack size for console handler */


#endif  /*  __MTSSH__  */


  
/********************************************************************30**

         End of file:     mt_ss.h@@/main/2 - Mon Apr  5 18:19:19 2010

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

1.1+         ---      ada  1. Changed common memory bucket size to
                              improve efficiency  

            mt007.21  jn   2. Defined Macros SMemCpy & SMemSet for
                              multiple byte copy
            mt012.21  jn   3. Defined the macro SS_MAX_RTRTSTS to 255
            mt013.21  jn   4. Defined the following macros:
                              SInitSemaphore,
                              SWaitSemaphore,
                              SPostSemaphore,
                              SDestroySemaphore. 
            mt014.21  jn   5. Corrected the typo in Macro definition for
                              SDestroySemaphore
            mt015.21  ada  6. Changed SS_MAX_TMRS from 15 to 45
                      ada  7. Changes to code to run on Linux
            mt016.21  ada  7. Increased MT_DBUF_NMB_BUFS and MT_HEAP_SIZE
                              to work with H.323 acceptance test
            mt017.21  bdu  8. Added SExit() for exiting use                      
           mt018.201  bdu  9. Remove several macro defines, and change
                              the name of some macros.
           mt021.201  bjp 10. Added macro definition for stack sizes
           mt022.201  bjp 11. Modifications for shared memory relay
                              Modifications for memory calculation tool
1.1+       mt026.201  bjp  1. Modification to increase default heap size
1.1+       mt027.201  bjp  1. Modification for SRegCfgTmr support
2.1+       mt028.201  kkj  1. Support of multiple procs added
           mt029.201  bn    2. corrected typose in memory calculation.
           mt031.201  bn    1. changed  MT_BKT_0_DSIZE from 80 to 120 for 64k 
                               compilation 
           mt032.201  bn    2. changed  MT_BKT_0_DSIZE from 120 to 128 for 64k 
                               compilation 
/main/2      ---        rp    1. SSI enhancements for Multi-core architecture support
*********************************************************************91*/
