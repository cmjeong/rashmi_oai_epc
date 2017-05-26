

/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     ys_tmr.c 
  
     Sid:      yw_tmr.c@@/main/2 - Thu Dec  2 02:27:27 2010
  
     Prg:      sd 
  
**********************************************************************/

/** @file ys_tmr.c 
@brief This module does processing related to timers
*/
/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_lte.h"       /* common tokens */
#include "ctf.h"           /* CTF defines */
#include "lys.h"           /* layer management defines for LTE-CL */
#include "tfu.h"
#include "ys_pal.h"            /* defines and macros for CL */
#include <sys/time.h>
#include "ys_pal_err.h"        /* YS error defines */


/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"       /* common tokens */
#include "ctf.x"           /* CTF types */
#include "lys.x"           /* layer management typedefs for CL */
#include "tfu.x"
#include "ys_pal.x"            /* typedefs for CL */

#ifndef SS_CAVIUM
PRIVATE Void * ysPalTtiTmrTsk ARGS((Void *));
#endif

#ifdef YS_LTE_PAL
#if (defined(LTE_PAL_ENB) && defined(SS_CAVIUM))
#ifdef ANSI
PUBLIC Void ttiHdlr
(
Void
)
#else
PUBLIC Void ttiHdlr()
#endif
{
   TRC2(ttiHdlr);
#if 0
   ysPrcTmrExpiry(NULLP, YS_TTI_TMR_EVNT);
#endif
   RETVOID;
}
#endif
#endif /* YS_LTE_PAL */


 /** @brief This function handles timer expiry.
  *
  * @details
  *
  *     Function: 
  *
  *         Processing steps:
  *         - 
  *
  *
  * @param  
  * @param 
  * @return 
  */
#ifdef ANSI
PUBLIC Void ysPrcTmrExpiry 
(
Ptr   cb,
S16   tmrEvnt
)
#else
PUBLIC Void ysPrcTmrExpiry (cb, tmrEvnt)
Ptr   cb;
S16   tmrEvnt;
#endif
{

   TRC2(ysPrcTmrExpiry);

   switch (tmrEvnt)
   {
#if  (defined(LTE_PAL_ENB) || defined(YS_TST_STUB))
      case YS_TTI_TMR_EVNT:
      {
         PRIVATE CmLteTimingInfo  timingInfo;
#ifdef LTE_PAL_ENB
         if (ysCb.ttiReady == TRUE)
#endif
         {
#ifdef YS_LTE_PAL
            ysPalHdlTtiInd(&timingInfo);
            YS_INCR_TIMING_INFO(timingInfo, 1);
#endif /* YS_LTE_PAL */

         }
      }
      break;
#endif /* LTE_PAL_ENB  || YS_TST_STUB */

      default:
         YS_DBG_ERR((_ysp, "ysPrcTmrExpiry(): invalid tmrEvnt = %d", tmrEvnt));
   }   
   RETVOID;
} /* end of ysPrcTmrExpiry */ 



#ifndef SS_CAVIUM
#ifdef ANSI
PUBLIC S16 ysPalInitTtiTmrTsk
(
Void
)
#else
PUBLIC S16 ysPalInitTtiTmrTsk()
#endif
{
   pthread_t tId;
   pthread_attr_t attr;
#ifdef LTE_LNX_AFFINITY
   cpu_set_t cpuSet; 
#endif

   /* ys002.102: Added missed trace macro */
   TRC2(ysPalInitTtiTmrTsk)
   pthread_attr_init(&attr);
   pthread_attr_setstacksize(&attr, (size_t)NULLD);
   pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

#ifndef TENB_SPLIT_ARCH_SUPPORT
   if ((pthread_create(&tId, &attr, ysPalTtiTmrTsk, (Ptr)NULL)) != 0)
#else
#ifdef TELRAD_UESIM
   if ((pthread_create(&tId, &attr, ysPalTtiTmrTsk, (Ptr)NULL)) != 0)
#else
   if ((SCreatePThread(&tId, &attr, ysPalTtiTmrTsk, (Ptr)NULL)) != 0)
#endif
#endif
   {
      pthread_attr_destroy(&attr);

      YS_DBG_ERR((_ysp, "Failed to create TTI generator thread\n"));

      RETVALUE(RFAILED);
   }


#ifdef LTE_LNX_AFFINITY
   /* Initialize the cpu mask */
   CPU_ZERO(&cpuSet);

   /* Set the cpu mask */
   CPU_SET(YS_TTI_CPUCORE_VAL, &cpuSet);

   /* Set thread affinity for linux */
   if (pthread_setaffinity_np(tId, sizeof(cpuSet), &cpuSet) < 0)
   {
      printf("Set affinity failed for TTI generator \n");
      exit(0);
   }
#endif
   RETVALUE(ROK);
}



#ifdef ANSI
PRIVATE Void * ysPalTtiTmrTsk
(
Void   *ptr
)
#else
PRIVATE Void * ysPalTtiTmrTsk(ptr)
Void   *ptr;
#endif
{
   PRIVATE struct timespec interval, remInterval;
   PRIVATE struct timespec startTm, wakeup;

   Buffer *tempBuf;
   Pst    pst;
   S16    ret;
   PRIVATE U16 ttiEvnt;
#ifdef YS_DEBUG
   PRIVATE U16 ttiCnt = 0;
   PRIVATE unsigned long diff_time, diff_time_sec = 0;
   PRIVATE struct timespec entryRx, exitRx;
#endif

   pst.dstProcId = SFndProcId();
   pst.srcProcId = SFndProcId();
   pst.dstEnt = ENTTF;
   pst.srcEnt = ENTTF;
   pst.srcInst = 0;
   pst.dstInst = 0;
   pst.route = RTESPEC;
   pst.prior = PRIOR0;
   pst.region = ysCb.ysInit.region;
   pst.pool = ysCb.ysInit.pool;
   pst.event = (Event) EVTTFUTTIIND; 

   /*clock_gettime(CLOCK_REALTIME, &entryRx); */
   clock_gettime(CLOCK_REALTIME, &wakeup);
   clock_gettime(CLOCK_REALTIME, &startTm);
   while(1)
   {
       remInterval.tv_sec = 0;
       remInterval.tv_nsec = 0;
       interval.tv_sec = 0;
       startTm.tv_nsec += YS_TTI_TMR_VAL;
       if (startTm.tv_nsec > 1000000000)
       {
          startTm.tv_nsec -= 1000000000;
          startTm.tv_sec += 1;
       }
       interval.tv_nsec = ((startTm.tv_sec - wakeup.tv_sec )*1000000000) +
                           (startTm.tv_nsec - wakeup.tv_nsec);
       while((nanosleep(&interval, &remInterval))!=0)
       {
          interval = remInterval;
          remInterval.tv_sec = 0;
          remInterval.tv_nsec = 0; 
       }
       clock_gettime(CLOCK_REALTIME, &wakeup); 

#ifdef YS_DEBUG
      /* Adding for quantify testing */
      ttiCnt++;

      if(3000 == ttiCnt)
      {
         printf("TTI Timer task exiting now...\n");
         pthread_exit(NULLP);
      }
#endif

#ifdef YS_DEBUG
      ttiCnt+=YS_TTI_COUNT_VAL;
      if(ttiCnt >= 1000)
      {
         clock_gettime(CLOCK_REALTIME, &exitRx);
         if (exitRx.tv_sec - entryRx.tv_sec > 0)
         {
            diff_time_sec = exitRx.tv_sec - entryRx.tv_sec;
         }
         else if (exitRx.tv_sec - entryRx.tv_sec == 0)
         {
            diff_time = exitRx.tv_nsec - entryRx.tv_nsec;
         }
         else
         {
            diff_time = ((exitRx.tv_sec - entryRx.tv_sec )*1000000000);
            diff_time += ((exitRx.tv_nsec > entryRx.tv_nsec) ? 
                          (exitRx.tv_nsec - entryRx.tv_nsec):
                          (entryRx.tv_nsec - exitRx.tv_nsec));
         }
         if(diff_time_sec)
         {
            printf("TTI Task: %ld TTIs generated in %ldseconds, entrysec %ld, exitsec %ld\n",
                    ttiCnt, diff_time_sec, entryRx.tv_sec, exitRx.tv_sec);
         }
         else
         {
            printf("TTI Task: %d TTIs generated in %ldns, %ldms\n", ttiCnt, 
                    diff_time, (diff_time/(1000000)));
         } 
/*       printf("TTI Task: %d TTIs generated with entryTti%lds, entryTti %ldns exitTti%lds, exitTti%ldns\n", ttiCnt, entryRx.tv_sec, entryRx.tv_nsec, exitRx.tv_sec, exitRx.tv_nsec);*/
         diff_time = 0;
         diff_time_sec = 0;
         ttiCnt = 0;
         clock_gettime(CLOCK_REALTIME, &entryRx); 
         memset(&exitRx, 0, sizeof(struct timespec)); 
      }
#endif 
      ttiEvnt = YS_TTI_COUNT_VAL; 
      while(ttiEvnt)
      {
         ret = SGetMsg(ysCb.ysInit.region, ysCb.ysInit.pool, &tempBuf);
         if (ret != ROK)
         {
            YS_DBG_ERR((_ysp, "SGetMsg failed\n"));
            continue;
         } 
         SPstTsk(&pst, tempBuf);
         ttiEvnt--;
      }
   }
   pthread_exit(NULLP);
}
#endif


/********************************************************************30**
  
         End of file:     yw_tmr.c@@/main/2 - Thu Dec  2 02:27:27 2010
  
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
----------- -------- ---- -----------------------------------------------
/main/2      ---     sgm                   1. eNodeB 1.2 release
/main/2    ys002.102  rk                   1. Added missed trace macro
*********************************************************************91*/
