

/********************************************************************20**
 
     Name:     System Services -- general
 
     Type:     C include file
 
     Desc:     Data structure definitions that are used by all
               implementations of system services.
 
     File:     ss_gen.x
 
     Sid:      ss_gen.x@@/main/2 - Mon Apr  5 18:01:16 2010
 
     Prg:      kp
 
*********************************************************************21*/


#ifndef __SSGENX__
#define __SSGENX__

#ifdef __cplusplus
extern "C" {
#endif

/* ss029.103: addition: multiple procIds related changes */ 
#ifdef SS_MULTIPLE_PROCS
typedef struct {
   U16 free;
   ProcId procId[SS_MAX_PROCS];
} ProcIdLst;
#endif /* SS_MULTIPLE_PROCS */

/* multi-core enhancements */
#ifdef SS_MULTICORE_SUPPORT

typedef struct {
  SCpuInfo cpuInfo; /* the info about the cores/threads per core */


  /* the currently used core */
  U32 currentCore;
  
  /*COMMENT: add the thread id for use on hyperthreading machines */
  struct {
    U32 thrs;                     /* available no. of threads per core */
    S8 exclusive;                 /* exclusive flag */
    SSTskId tskPerCoreLst[SS_MAX_THREADS_PER_CORE]; /* System tasks running on this core */
  } coreInfo[SS_MAX_CORES];
} SMultiCoreInfo;
#endif /* SS_MULTICORE_SUPPORT */

/* SS control point */
typedef struct ssos
{
   
   SsdOs                dep;                    /* implementation specific */

/* ss029.103: modification: 
   with multiple procId support, SSI shall keep list of registered procIds  */
#ifndef SS_MULTIPLE_PROCS
   ProcId               procId;                 /* processor ID */

    /* TAPA task info */
   SsIdx                tTskIds[SS_MAX_ENT][SS_MAX_INST];
#else
   ProcIdLst            procLst;                /* processor ID list */
   SsIdx                tTskIds[SS_MAX_PROCS][SS_MAX_ENT][SS_MAX_INST];
   /* TAPA task info */
#endif /* SS_MULTIPLE_PROCS */
                                               /* index table */
   SsTTskEntry          tTskTbl[SS_MAX_TTSKS];  /* task table */
   SsCntr               numTTsks;               /* count of tasks */
   SsIdx                nxtTTskEntry;           /* next available slot */

   SsSemaId             tTskTblSem;             /* lock for table access */


   /* system task info */
   SsSTskEntry          sTskTbl[SS_MAX_STSKS];  /* task table */
   SsCntr               numSTsks;               /* count of tasks */
   SsIdx                nxtSTskEntry;           /* next available slot */

   SLockId              sTskTblLock;            /* lock for table access */


   U8                   dmndQLookupTbl[256];    /* demand queue lookup table */


#ifdef SS_DRVR_SUPPORT

   /* driver task info */
   SsDrvrTskEntry       drvrTskTbl[SS_MAX_DRVRTSKS];
                                                /* task table */
   SsCntr               numDrvrTsks;            /* count of tasks */

#endif  /* SS_DRVR_SUPPORT */


#ifdef SS_RTR_SUPPORT

   /* router task info */
   ActvTsk              rtrTskTbl[SS_MAX_RTRTSKS];
   SLockId              rtrTskLocks[SS_MAX_RTRTSKS];

#endif  /* SS_RTR_SUPPORT */


   /* timer info */
   SsTmrEntry           tmrTbl[SS_MAX_TMRS];    /* timer table */
   SsCntr               numTmrs;                /* count of timers */
   SsIdx                nxtTmrEntry;            /* next available slot */

   SLockId              tmrTblLock;             /* lock for table access */


   /* memory info */
   SsRegionEntry        regionTbl[SS_MAX_REGS]; /* region table */
   SsCntr               numRegions;             /* count of regions */

   SsSemaId             regionTblSem;           /* lock for table access */

   /* ss028.103 - Addition of lock for mBuf reference count */
   SLockId              mBufRefLock;            /* lock for mBuf ref access */

#ifdef SS_MULTICORE_SUPPORT
   /* the Information about the CPU */
   SMultiCoreInfo mCInfo;

   SLockId mCILock;                             /* Lock for mCInfo access */

#endif /* SS_MULTICORE_SUPPORT */

} SsOs;



/* configuration data structures */

/* pool configuration */
typedef struct ssPoolCfg
{
   SsPoolType   type;                   /* dynamic or static */
   Size         size;                   /* size to use (for dynamic pools) */

} SsPoolCfg;


/* region content--pools in a region */
typedef struct ssRegCfg
{
   Region       region;                      /* region ID */
   SsCntr       numPools;                    /* count of pools */
   SsPoolCfg    pools[SS_MAX_POOLS_PER_REG]; /* pools configuration */

} SsRegCfg;



/* external variable declaration */
EXTERN SsOs osCp;


/* functions */
EXTERN S16 SInit ARGS((void));
/* ss034.103 */
EXTERN S16 SDeInit ARGS((void));

/* implementation-specific functions */
EXTERN S16 ssdInitGen ARGS((void));
EXTERN S16 ssdInitMem ARGS((void));
EXTERN S16 ssdInitTsk ARGS((void));
EXTERN S16 ssdInitDrvr ARGS((void));
EXTERN S16 ssdInitTmr ARGS((void));
EXTERN S16 ssdInitFinal ARGS((void));

EXTERN Void ssdDeinitGen ARGS((void));
EXTERN Void ssdDeinitMem ARGS((void));
EXTERN Void ssdDeinitTsk ARGS((void));
EXTERN Void ssdDeinitDrvr ARGS((void));
EXTERN Void ssdDeinitTmr ARGS((void));
EXTERN Void ssdDeinitFinal ARGS((void));

EXTERN Void ssdStart ARGS((void));

EXTERN S16 ssdAttachTTsk ARGS((SsTTskEntry *));
EXTERN S16 ssdDetachTTsk ARGS((SsTTskEntry *));
EXTERN S16 ssdCreateSTsk ARGS((SsSTskEntry *));
EXTERN S16 ssdDestroySTsk ARGS((SsSTskEntry *));
EXTERN S16 ssdPstTsk ARGS((Pst *, Buffer *, SsTTskEntry *));
EXTERN S16 ssdRegTmr ARGS((SsTmrEntry *));
EXTERN S16 ssdDeregTmr ARGS((SsTmrEntry *));
EXTERN S16 ssdError ARGS((Seq, Reason));
EXTERN Void ssdLogError ARGS((Ent, Inst, ProcId, Txt *, S32, \
                              ErrCls, ErrCode, ErrVal, Txt *));

#ifdef SS_DRVR_SUPPORT
EXTERN S16 ssdRegDrvrTsk ARGS((SsDrvrTskEntry *));
#endif

/* ss029.103: addition: support function to implement multiple procIds */ 
#ifdef SS_MULTIPLE_PROCS
EXTERN U16 SGetProcIdIdx ARGS((ProcId proc));
#endif /* SS_MULTIPLE_PROCS */

/* multi-core support */
#ifdef SS_MULTICORE_SUPPORT
 
EXTERN S16 ssdSetAffinity ARGS((SSTskId *tskId, U32 coreId));
EXTERN S16 ssdGetAffinity ARGS((SSTskId *tskId, U32 *coreId));
#endif /* SS_MULTICORE_SUPPORT */
 

#ifdef __cplusplus
}
#endif

#endif  /*  __SSGENX__  */



/********************************************************************30**
 
         End of file:     ss_gen.x@@/main/2 - Mon Apr  5 18:01:16 2010
 
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

1.2          ---      bsr  1. moved lock types to ssi.h
             ---      bsr  2. Added prototypes for ssdDeinit* functions 
             ---      kp   1. Prototype for ssdPstTsk added

1.3          ---      kp   1. Added in Message Router support
1.3+        ss028.103 bjp  1. Addition of lock for mBuf reference count
1.3+        ss029.103 kkj  1. Multiple proc ids support added
1.3+        ss034.103 pdb  1. Prototype for SDeInit API is added.
/main/4      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/
