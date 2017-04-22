/********************************************************************20**

     Name:     SON Application

     Type:     

     Desc:     This file contains 
               

     File:     nl_tmr.c

     Sid:      bk_tmr.c@@/main/tenb_main_ccb/1 - Thu Jan 21 17:51:24 2016

     Prg:      subhamay 

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="SON";
static int RLOG_FILE_ID=255;
static int RLOG_MODULE_ID=256;


/* Header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"

#include "cm_tkns.h"       /* Common Token defines */
#include "cm_mblk.h"       /* Common Mem Allocation defines */
#include "cm_llist.h"      /* Common Link List defines */
#include "cm_hash.h"       /* Common Hashlist defines */
#include "cm_pasn.h"       /* Common Pasn defines */
#include "cm_lte.h"        /* Common Pasn defines */
#include "rl_common.h"     /* RLOG defines */
#include "rl_interface.h"
#include "lnl.h"           /* NL Interface defines */
#include "nlu.h"
#include "nl.h"            /* SON defines */

/* Header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */
#include "cm5.x"
#include "cm_tkns.x"       /* Common Token definitions */
#include "cm_mblk.x"       /* Common Memory Allocation */
#include "cm_llist.x"      /* Common Link List definitions */
#include "cm_hash.x"       /* Common Hashlist definitions */
#include "cm_lib.x"        /* Common Library definitions */
#include "cm_pasn.x"       /* Common Hashlist definitions */
#include "cm_lte.x"       /* Common Pasn defines */

#include "lnl.x"           /* NL Interface includes */
#include "nlu.x"
#include "nl.x"            /* SON includes */

/* local defines */
/* local typedefs */
 
/* local externs */
 
/* forward references */

/** @brief This function handles timer expiry. 
 *
 * @details
 *
 *  This function based upon the timer event invokes specific 
 *  routine to handle timer expiry. 
 *
 * @param[in] Cb       : This holds approriate Control block for 
 *                        the timer event passed. 
 * @param[in] tmrEvent : One of the many possible timer types. 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
#ifdef ANSI
PUBLIC Void nlProcTmr
(
Ptr    cb,
S16    event
)
#else
PUBLIC Void nlProcTmr(cb, event)
(
Ptr    cb;
S16    event;
)
#endif
{
   RETVOID;
}

/** @brief This function is used to start a given timer. 
 *
 * @details
 *
 *   This function based upon the timer event, derives the TimerCB 
 *   and adds it to the timer queue.
 *
 * @param[in] Cb       : This holds approriate Control block 
 *                       for the timer event passed. 
 * @param[in] tmrEvent : One of the many possible timer types. 
 * @param[in] delay    : Duration of the timer in second.
 * @return Void
 */
#ifdef ANSI
PUBLIC Void nlStartTmr
(
PTR   cb,
S16   tmrEvnt,
U32   delay
)
#else
PUBLIC Void nlStartTmr(cb, tmrEvnt, delay)
(
PTR   cb;
S16   tmrEvnt;
U32   delay;
)
#endif
{
   delay = NL_CALC_WAIT_TIME(delay);
   RETVOID;
}

/** @brief This function is used to stop a previously running timer. 
 *
 * @details
 *
 *  This function based upon the timer event reterives relevant timerCb and 
 *  tries to determine whether timer is running or not.In case timer 
 *  was running, it is stopped .
 *
 * @param[in] Cb : This holds approriate Control block for the timer event passed. 
 * @param[in] tmrEvent : One of the many possible timer types. 
 * @return Void
 */
#ifdef ANSI
PUBLIC Void nlStopTmr
(
PTR   cb,
S16   event
)
#else
PUBLIC Void nlStopTmr(cb, event)
(
PTR   cb;
S16   event;
)
#endif
{
   RETVOID;
}



/** @brief Invoked by system services to activate a task with
 *              a timer tick.
 *
 * @details 
 *         activate the timer tick
 *
 *
 * @param[in] ent    : Entity Id od SON module
 * @param[in] inst   : Instance Id od SON module
 
 * @return
 -#                  : ROK 
 */

#ifdef ANSI
PUBLIC S16 nlActvTmr
(
Ent    ent,
Inst   inst
)
#else
PUBLIC S16 nlActvTmr(ent, inst)
(
Ent    ent;
Inst   inst;
)
#endif
{
   if(&nlCb.tqCp && nlCb.tq)
   {
      cmPrcTmr(&nlCb.tqCp, nlCb.tq, (PFV) nlProcTmr);
   }

   RETVALUE(ROK);
} 

/**
 * @brief This function registers and initializes the timer
 *         queue structures in SON during general config. 
 *
 * @details
 *
 *     This function will register the timer module for SON
 *
 *  @param[in]   Void
 *
 *  @return  S16
 *     -# Timer module registration success  : ROK
 *     -# Timer module registration failed   : RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 nlRegInitTmr
(
Void
)
#else
PUBLIC S16 nlRegInitTmr()
(
Void;
)
#endif
{
   U16                       idx;
   S16                       ret;

   ret = SRegTmrMt((Ent)ENTNL, (Inst)0, nlCb.timeRes, nlActvTmr);
   if (ret != ROK)
   {
      RLOG0(L_ERROR, "SRegTmr Failed");
      RETVALUE(RFAILED);
   }

   /* initialize timing queues */
   nlCb.tqCp.tmrLen      = NL_NUM_TQENTRY;

   for (idx = 0; idx < NL_NUM_TQENTRY; idx++)
   {
      nlCb.tq[idx].first    = NULLP;
      nlCb.tq[idx].tail     = NULLP;
   }

   RETVALUE(ROK);
}

/**
 * @brief Stop BRCM-SON Timers
 *
 * @details
 *
 *     This function will stop all the timers started for BRCM-SON
 *
 *  @param[in]  Void
 *  @return  Void
 *
 **/
#ifdef ANSI
PUBLIC Void nlStopTimers
(
Void
)
#else
PUBLIC Void nlStopTimers(Void)
(
Void
)
#endif
{
}

/********************************************************************30**

           End of file:     bk_tmr.c@@/main/tenb_main_ccb/1 - Thu Jan 21 17:51:24 2016

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
*********************************************************************91*/

