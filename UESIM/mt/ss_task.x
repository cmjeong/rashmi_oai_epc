

/********************************************************************20**
 
     Name:     System Services -- Task Management
 
     Type:     C include file
 
     Desc:     Data structure definitions required for the task mgmt.
 
     File:     ss_task.x
 
     Sid:      ss_task.x@@/main/2 - Mon Apr  5 18:01:21 2010
 
     Prg:      kp
 
*********************************************************************21*/


#ifndef __SSTASKX__
#define __SSTASKX__

#ifdef __cplusplus
extern "C" {
#endif


/* miscellaneous types */
/* ss029.103: modification: 
   data type changed to allow more number of TAPA tasks */ 
#ifndef SS_MULTIPLE_PROCS
typedef U8                      SsCntr;
typedef U8                      SsIdx;
#else /* SS_MULTIPLE_PROCS */
typedef U16                      SsCntr;
typedef U16                      SsIdx;
#endif /* SS_MULTIPLE_PROCS */


/* forward declaration */
typedef struct ssSTskEntry      SsSTskEntry;


/* individual entry in the table of TAPA tasks */
typedef struct ssTTskEntry
{
   SsdTTskEntry dep;                    /* implementation specific */


   Bool         used;                   /* entry is used? */
/* ss029.103: addition: procId added */ 
#ifdef SS_MULTIPLE_PROCS
   ProcId       proc;                   /* task processor ID */
#endif /* SS_MULTIPLE_PROCS */
   Ent          ent;                    /* task entity ID */
   Inst         inst;                   /* task instance ID */
   Ttype        tskType;                /* normal/permanent/driver */
   Prior        tskPrior;               /* priority of task */
   PAIFS16      initTsk;                /* initialization function */
   ActvTsk      actvTsk;                /* activation function */

   SsSTskEntry  *sTsk;                  /* system task */


   SsIdx        nxt;                    /* table implementation */
/* ss029.103: addition: TAPA task control block (user level) added */ 
#ifdef SS_MULTIPLE_PROCS
   Void         *xxCb;                  /* protocol control block */
#endif /* SS_MULTIPLE_PROCS */

} SsTTskEntry;



/* individual entry in the table of system tasks */
struct ssSTskEntry
{
   SsdSTskEntry dep;                    /* implementation specific */


   Bool         used;                   /* entry is used or not */
   Bool         termPend;               /* termination pending */
   SSTskId      tskId;                  /* system task ID */
   SSTskPrior   tskPrior;               /* system task priority */
   SsDmndQ      dQ;                     /* demand queue */


   /* TAPA task information: the TAPA tasks being handled by
    *  this system task.
    */
   SsIdx        tTsks[SS_MAX_TTSKS];    /* indices into TAPA task table */
   SsCntr       numTTsks;               /* count of TAPA tasks */
   SLockId      lock;                   /* lock for table access */


   SsIdx        nxt;                    /* table implementation */
#ifdef SS_MULTICORE_SUPPORT
   Region       region;
#endif

};


#ifdef __cplusplus
}
#endif

#endif  /*  __SSTASKX__  */


  
/********************************************************************30**

         End of file:     ss_task.x@@/main/2 - Mon Apr  5 18:01:21 2010

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

1.2          ---      kp   1. C++ compilable, cosmetic changes
1.3+      ss029.103   kkj  1. Multiple proc ids support added
/main/3      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/
