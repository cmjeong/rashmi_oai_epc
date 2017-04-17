

/********************************************************************20**
 
     Name:     System Services -- Timing
 
     Type:     C include file
 
     Desc:     Data structure definitions required for timing.
 
     File:     ss_timer.x
 
     Sid:      ss_timer.x@@/main/2 - Mon Apr  5 18:01:21 2010
 
     Prg:      kp
 
*********************************************************************21*/


#ifndef __SSTIMERX__
#define __SSTIMERX__

#ifdef __cplusplus
extern "C" {
#endif



/* timer ID and type */
typedef SsIdx           SsTmrId;


/* individual entry in the timer table */
typedef struct ssTmrEntry
{
   SsdTmrEntry  dep;                    /* implementation specific */


   Bool         used;                   /* entry is used? */
   SsTmrId      tmrId;                  /* timer ID */
/* ss029.103: addition: procId added */ 
#ifdef SS_MULTIPLE_PROCS
   ProcId       ownerProc;              /* owner task processor ID */
#endif /* SS_MULTIPLE_PROCS */
   Ent          ownerEnt;               /* owner task entity ID */
   Inst         ownerInst;              /* owner task instance ID */
   /* ss028.103 - Modification for SRegCfgTmr support */
   U32          interval;               /* timer interval */
/* ss029.103: modification: timer function type modified */ 
#ifndef SS_MULTIPLE_PROCS
   /* ss030.103 */
#ifdef SS_MT_TMR
   Bool         mtFlag;                 /* TRUE if tmrActvFnMt to be used */
   PAIFTMRS16   tmrActvFnMt;            /* for MT support, takes ent and inst */
#endif
   PFS16        tmrActvFn;              /* timer activation function */
#else
   PAIFTMRS16      tmrActvFn;
#endif /* SS_MULTIPLE_PROCS */

   Buffer       *mBuf;                  /* timer message buffer */


   SsIdx        nxt;                    /* table implementation */

} SsTmrEntry;



#ifdef __cplusplus
}
#endif

#endif  /*  __SSTIMERX__  */


  
/********************************************************************30**

         End of file:     ss_timer.x@@/main/2 - Mon Apr  5 18:01:21 2010

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
1.2+       ss028.103  bjp 1. Modification for SRegCfgTmr support
1.3+       ss029.103  kkj  1. Multiple proc ids support added
1.3+       ss030.103  apany 1. New timer activation function for
                             multithreading support.
/main/3      ---      rp   1. SSI enhancements for Multi-core architecture
                              support
*********************************************************************91*/
