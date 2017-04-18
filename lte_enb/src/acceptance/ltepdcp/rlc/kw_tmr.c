

/********************************************************************20**
  
        Name:    RLC - TMR module file
    
        Type:    C source file
  
        Desc:    Source code for timer functions such as, 

                 - kwStartTmr
                 - kwStopTmr
                 - kwTmrExpiry
                 - kwBndTmrExpiry  
                  
        File:    gp_tmr.c

        Sid:      kw_tmr.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:50 2014
 
        Prg:     nm
  
*********************************************************************21*/


/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "kw_env.h"        /* RLC environment options */

#include "kw.h"            /* RLC defines */
#include "kw_err.h"        /* Error defines */
#include "kw_ul.h"
#include "kw_dl.h"

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */

#include "kw.x"
#include "kw_dl.x"
#include "kw_ul.x"

/* local defines */

/* local externs */

/* forward references */

/* public variable declarations */

/* This structure holds all the global structs we need. */

/* private variable declarations */

/* private function declarations */
PRIVATE Void kwBndTmrExpiry(PTR cb);

/** @file gp_tmr.c
@brief RLC Timer Module
**/

/**
 *
 * @brief Handler to start timer
 *       
 *
 * @b Description
 *        This function is invoked by AMM/UMM to start the relevant timers for reordering
 *
 *
 *  @param[in] cb      RB control block 
 *  @param[in] tmrEvnt Timer event to be started
 *
 * 
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
*/
#ifdef ANSI
PUBLIC S16 kwStartTmr
(
KwCb     *gCb,
PTR       cb,           /* Parent control block */
S16       tmrEvnt       /* Timer event */
)
#else
PUBLIC S16 kwStartTmr (gCb,cb, tmrEvnt)
KwCb      *gCb;
PTR       cb;           /* Parent control block */
S16       tmrEvnt;      /* Timer event */
#endif
{
   KwUlRbCb *ulRbCb         = NULLP;
   KwDlRbCb *dlRbCb         = NULLP;
   KwUmUl *umUl;
   KwAmDl *amDl         = NULLP;
   KwAmUl *amUl         = NULLP;
   KwRguSapCb *rguSap   = NULLP;
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   KwL2MeasEvtCb *measEvtCb = NULLP;
#endif

   U16         wait     = 0;
   CmTmrArg    arg;
   CmTimer     *tmr     = NULLP;
   U8          maxTmrs  = 0;

   TRC2(kwStartTmr)

/* printf("\n********************************\n %d start timer \n********************************\n", tmrEvnt); */

   /* kw002.201 Adjusting the wait time as per timeRes configured by layer manager */
   switch (tmrEvnt)
   {
      case KW_EVT_UMUL_REORD_TMR:
      {
         ulRbCb = (KwUlRbCb *)cb;
         umUl = &(ulRbCb->m.umUl);
         /* kw005.201 Changed wait calculation ccpu00117634*/ 
         wait = (umUl->reOrdTmrInt * SS_TICKS_SEC)/(gCb->genCfg.timeRes * 1000);
         if( (0 != umUl->reOrdTmrInt) && (0 == wait) )
         {
            wait = 1;
         }
         tmr  = &umUl->reOrdTmr;
         maxTmrs = KW_MAX_UM_TMR;
         break;
      }
      case KW_EVT_AMUL_REORD_TMR:
      {
         ulRbCb = (KwUlRbCb *)cb;
         amUl = &(ulRbCb->m.amUl);
         /* kw005.201 Changed wait calculation ccpu00117634*/ 
         wait = (amUl->reOrdTmrInt * SS_TICKS_SEC)/(gCb->genCfg.timeRes * 1000);
         if( (0 != amUl->reOrdTmrInt) && (0 == wait) )
         {
            wait = 1;
         }
         tmr  = &amUl->reOrdTmr;
         maxTmrs = KW_MAX_AM_TMR;
         break;
      }
      case KW_EVT_AMUL_STA_PROH_TMR:
      {
         ulRbCb = (KwUlRbCb *)cb;
         amUl = &(ulRbCb->m.amUl);
         /* kw005.201 Changed wait calculation ccpu00117634*/ 
         wait = (amUl->staProhTmrInt * SS_TICKS_SEC)/(gCb->genCfg.timeRes * 1000);
         if( (0 != amUl->staProhTmrInt) && (0 == wait) )
         {
            wait = 1;
         }
         tmr  = &amUl->staProhTmr;
         maxTmrs = KW_MAX_AM_TMR;
         break;
      } 
      case KW_EVT_AMDL_POLL_RETX_TMR:
      {
         dlRbCb = (KwDlRbCb *)cb;
         amDl = &(dlRbCb->m.amDl);
         /* kw005.201 Changed wait calculation ccpu00117634*/ 
         wait = (amDl->pollRetxTmrInt * SS_TICKS_SEC)/(gCb->genCfg.timeRes * 1000);
         if( (0 != amDl->pollRetxTmrInt) && (0 == wait) )
         {
            wait = 1;
         }
         tmr  = &amDl->pollRetxTmr;
         maxTmrs = KW_MAX_AM_TMR;
         break;
      } 
      case KW_EVT_WAIT_BNDCFM:
      {
         rguSap = (KwRguSapCb *)cb;
         /* kw005.201 Changed wait calculation ccpu00117634*/ 
         wait   = (rguSap->bndTmrInt * SS_TICKS_SEC)/(gCb->genCfg.timeRes * 1000);
         if( (0 != rguSap->bndTmrInt) && (0 == wait) )
         {
            wait = 1;
         }
         tmr    = &rguSap->bndTmr;
         maxTmrs = KW_MAX_RGUSAP_TMR;
         break;
      }
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
      case KW_EVT_L2_TMR:
      {
         measEvtCb = (KwL2MeasEvtCb *)cb;
         /* kw005.201 Changed wait calculation ccpu00117634*/ 
         wait = (measEvtCb->l2TmrCfg.val * SS_TICKS_SEC)/(gCb->genCfg.timeRes * 1000);
         if( (0 != measEvtCb->l2TmrCfg.val) && (0 == wait) )
         {
            wait = 1;
         }
         tmr       = &measEvtCb->l2Tmr;
         maxTmrs   = KW_L2_MAX_TIMERS;
         break;
      }
#endif
      default:
      {
#if (ERRCLASS & ERRCLS_INT_PAR)
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW204, (ErrVal) 0,
                    "kwStartTmr: Invalid tmrEvnt");
#endif
      }
   } 

   if(wait != 0)
   {
      arg.tqCp   = &gCb->kwTqCp;
      arg.tq     = gCb->kwTq;
      arg.cb     = cb;
      arg.timers = tmr;
      arg.evnt   = tmrEvnt;
      arg.wait   = wait;
      arg.tNum   = 0;
      arg.max    = maxTmrs;

      cmPlcCbTq(&arg);
   }

   RETVALUE(ROK);
}

/**
 *
 * @brief Handler to stop timer
 *       
 *
 * @b Description
 *        This function is used to stop protocol timer, based on the timer event.
 *
 *
 *  @param[in] cb      RB control block 
 *  @param[in] tmrEvnt Timer event to be started 
 *
 * 
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
*/
#ifdef ANSI
PUBLIC S16 kwStopTmr
(
KwCb   *gCb,
PTR    cb,              /* Parent control block */
U8     tmrType          /* Timer */
)
#else
PUBLIC S16 kwStopTmr (gCb,cb, tmrType)
KwCb   *gCb;
PTR    cb;              /* Parent control block */
U8     tmrType;         /* Timer */
#endif
{
   KwUlRbCb *ulRbCb         = NULLP;
   KwDlRbCb *dlRbCb         = NULLP;
   KwUmUl *umUl;
   KwAmDl *amDl         = NULLP;
   KwAmUl *amUl         = NULLP;
   KwRguSapCb *rguSap   = NULLP;

   CmTmrArg   arg;
   CmTimer    *timers   = NULLP;
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   KwL2MeasEvtCb *measEvtCb = NULLP;
#endif
   TRC2(kwStopTmr)
/* printf("\n********************************\n %d stop timer \n********************************\n", tmrType); */
 
   switch (tmrType)
   {
      case KW_EVT_UMUL_REORD_TMR:
      {
         ulRbCb = (KwUlRbCb *)cb;
         umUl = &(ulRbCb->m.umUl);
         timers  = &umUl->reOrdTmr;
         arg.max = KW_MAX_UM_TMR;
         break;
      }
      case KW_EVT_AMUL_REORD_TMR:
      {
         ulRbCb = (KwUlRbCb *)cb;
         amUl = &(ulRbCb->m.amUl);
         timers = &amUl->reOrdTmr;
         arg.max = KW_MAX_AM_TMR;
         break;
      }
      case KW_EVT_AMUL_STA_PROH_TMR:
      {
         ulRbCb = (KwUlRbCb *)cb;
         amUl = &(ulRbCb->m.amUl);
         timers = &amUl->staProhTmr;
         arg.max = KW_MAX_AM_TMR;
         break;
      } 
      case KW_EVT_AMDL_POLL_RETX_TMR:
      {
       /* venki - print at poll retx timer stop */
         printf("\n********************************\n %d stop timer \n********************************\n", tmrType); 
         dlRbCb = (KwDlRbCb *)cb;
         amDl = &(dlRbCb->m.amDl);
         timers = &amDl->pollRetxTmr;
         arg.max = KW_MAX_AM_TMR;
         break;
      } 
      case KW_EVT_WAIT_BNDCFM:
      {
         rguSap = (KwRguSapCb *)cb;
         timers = &rguSap->bndTmr;
         arg.max = KW_MAX_RGUSAP_TMR;
         break;
      }
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
      case KW_EVT_L2_TMR:
      {
         measEvtCb = (KwL2MeasEvtCb *)cb;
         timers   = &measEvtCb->l2Tmr;
         arg.max  = KW_L2_MAX_TIMERS;
         break;
      }
#endif
      default:
      {
#if (ERRCLASS & ERRCLS_INT_PAR)
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW205, (ErrVal) 0,
                    "kwStopTmr : Invalid tmrEvnt");
#endif
      }
   } 
   if (tmrType != TMR0)
   {
      arg.tqCp    = &gCb->kwTqCp;
      arg.tq      = gCb->kwTq;
      arg.cb      = cb;
      arg.timers  = timers;
      arg.evnt    = tmrType;
      arg.wait    = 0;
      arg.tNum  = 0;
      cmRmvCbTq(&arg);
   }
   
   RETVALUE(ROK);
}

/**
 *
 * @brief Handler to invoke events on expiry of timer.
 *       
 *
 * @b Description
 *        This function is used to handle expiry of timer,it invokes relevant functions.
 *
 *
 *  @param[in] rbCb      RB control block 
 *  @param[in] tmrType   Type of the timer to be stopped
 *
 * 
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
*/
#ifdef ANSI
PUBLIC S16 kwTmrExpiry
(
PTR       cb,           /* Parent control block */
S16       tmrEvnt       /* Timer event */
)
#else
PUBLIC S16 kwTmrExpiry (cb, tmrEvnt)
PTR       cb;           /* Parent control block */
S16       tmrEvnt;      /* Timer event */
#endif
{
   KwCb   *gCb;
   KwDlRbCb *dlRbCb         = NULLP;
   KwUlRbCb *ulRbCb         = NULLP;
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   KwL2MeasEvtCb *measEvtCb = NULLP;
#endif

   TRC2(kwTmrExpiry)
printf("\n********************************\n %d timer expiry \n********************************\n", tmrEvnt);

   switch (tmrEvnt)
   {
      case KW_EVT_UMUL_REORD_TMR:
      {
         ulRbCb = (KwUlRbCb *)cb;
         gCb = KW_GET_KWCB(ulRbCb->inst);
         kwUmmReOrdTmrExp(gCb,ulRbCb);

         break;
      }
      case KW_EVT_AMUL_REORD_TMR:
      {
         ulRbCb = (KwUlRbCb *)cb;
         gCb = KW_GET_KWCB(ulRbCb->inst);
         kwAmmReOrdTmrExp(gCb,ulRbCb);
         break;
      }
      case KW_EVT_AMUL_STA_PROH_TMR:
      {
         ulRbCb = (KwUlRbCb *)cb;
         gCb = KW_GET_KWCB(ulRbCb->inst);
         kwAmmStaProTmrExp(gCb,ulRbCb);

         break;
      }
      case KW_EVT_AMDL_POLL_RETX_TMR:
      {
         dlRbCb = (KwDlRbCb *)cb;
         gCb = KW_GET_KWCB(dlRbCb->inst);
#if 1
         kwAmmPollRetxTmrExp(gCb, dlRbCb);
#endif
         gCb->genSts.protTimeOut++;
         break;
      }
      case KW_EVT_WAIT_BNDCFM:
      {
         kwBndTmrExpiry(cb);
         /* kw005.201 added missing break statement */
         break;
      }
      /* kw005.201 L2 Measurement support */
#ifdef LTE_L2_MEAS_RLC
      case KW_EVT_L2_TMR:
      {
         measEvtCb = (KwL2MeasEvtCb *)cb;
         kwUtlHdlL2TmrExp(measEvtCb);
         break;
      }
#endif
      default:
      {
         break;
      }
   }

   RETVALUE(ROK);
}

/**
 *
 * @brief Handler to check if the timer is running
 *       
 *
 * @b Description
 *        This function is used to check if the timer is running at the given
 *        moment.
 *
 *
 *  @param[in] rbCb      RB control block 
 *  @param[in] tmrType   Type of the timer to be stopped 
 *
 * 
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 */
#ifdef ANSI
PUBLIC Bool kwChkTmr
(
KwCb      *gCb,
PTR       cb,           /* Parent control block */
S16       tmrEvnt       /* Timer event */
)
#else
PUBLIC Bool kwChkTmr(gCb,cb, tmrEvnt)
KwCb      *gCb;
PTR       cb;           /* Parent control block */
S16       tmrEvnt;      /* Timer event */
#endif
{
   KwUlRbCb *ulRbCb         = NULLP;
   KwDlRbCb *dlRbCb         = NULLP;
   KwUmUl *umUl         = NULLP;
   KwAmDl *amDl         = NULLP;
   KwAmUl *amUl         = NULLP;
   KwRguSapCb *rguSap   = NULLP;
   Bool tmrRunning = FALSE;

   TRC2(kwChkTmr)

   switch (tmrEvnt)
   {
      case KW_EVT_UMUL_REORD_TMR:
      {
         ulRbCb = (KwUlRbCb *)cb;
         umUl = &(ulRbCb->m.umUl);
         if (umUl->reOrdTmr.tmrEvnt == KW_EVT_UMUL_REORD_TMR)
         {
            tmrRunning = TRUE;
         }
         break;
      }
      case KW_EVT_AMUL_REORD_TMR:
      {
         ulRbCb = (KwUlRbCb *)cb;
         amUl = &(ulRbCb->m.amUl);
         if (amUl->reOrdTmr.tmrEvnt == KW_EVT_AMUL_REORD_TMR)
         {
            tmrRunning = TRUE;
         }
         break;
      }
      case KW_EVT_AMUL_STA_PROH_TMR:
      {
         ulRbCb = (KwUlRbCb *)cb;
         amUl = &(ulRbCb->m.amUl);
         if (amUl->staProhTmr.tmrEvnt == KW_EVT_AMUL_STA_PROH_TMR)
         {
            tmrRunning = TRUE;
         }
         break;
      } 
      case KW_EVT_AMDL_POLL_RETX_TMR:
      {
         dlRbCb = (KwDlRbCb *)cb;
         amDl = &(dlRbCb->m.amDl);
         if (amDl->pollRetxTmr.tmrEvnt == KW_EVT_AMDL_POLL_RETX_TMR)
         {
            tmrRunning = TRUE;
         }
         break;
      } 
      case KW_EVT_WAIT_BNDCFM:
      {
         rguSap = (KwRguSapCb *)cb;
         if (rguSap->bndTmr.tmrEvnt == KW_EVT_WAIT_BNDCFM)
         {
            tmrRunning = TRUE;
         }
         break;
      }
      default:
      {

#if (ERRCLASS & ERRCLS_INT_PAR)
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW206, (ErrVal)0,
                    "kwChkTmr: Invalid tmrEvnt");
#endif
      }
   } 

   RETVALUE(tmrRunning);
}

/**
 *
 * @brief Private handler to invoke an event for bind timer expiry
 *       
 *
 * @b Description
 *        This function processes the RLC bind timer expiry. If the number of retry is
 *        less than the maximum retry counter, bind request is sent again, else an 
 *        alarm is raised to the layer manager.
 *
 *
 *  @param[in] cb      RB control block 
 *
 * 
 *   @return Void
 *      -# RETVOID
*/
#ifdef ANSI
PRIVATE Void kwBndTmrExpiry
(
PTR       cb            /* Parent control block */
)
#else
PRIVATE Void kwBndTmrExpiry(cb)
PTR       cb;           /* Parent control block */
#endif
{
   KwCb       *gCb;
   KwRguSapCb *rguSapCb; 

   TRC2(kwBndTmrExpiry)

   rguSapCb = (KwRguSapCb *) cb;
   gCb       = KW_GET_KWCB(rguSapCb->pst.srcInst);
   if (rguSapCb->state == KW_SAP_BINDING)
   {
      if (rguSapCb->retryCnt < KW_MAX_SAP_BND_RETRY)
      {
         /* Send bind request */
         rguSapCb->retryCnt++;

         /* start timer to wait for bind confirm */
         kwStartTmr( gCb,(PTR)rguSapCb, KW_EVT_WAIT_BNDCFM);

         KwLiRguBndReq (&rguSapCb->pst, rguSapCb->suId, rguSapCb->spId);
      }
      else
      {
         rguSapCb->retryCnt = 0;
         rguSapCb->state = KW_SAP_CFG;

         /* Send alarm to the layer manager */
#ifdef LTE_L2_MEAS_RLC
         kwLmmSendAlarm(gCb,LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_FAIL,
                        LCM_CAUSE_TMR_EXPIRED, 0, 0, 0);
#else
         kwLmmSendAlarm(gCb,LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_FAIL,
                        LCM_CAUSE_TMR_EXPIRED, 0, 0);
#endif
      }
   }

   RETVOID;
}


  
/********************************************************************30**
  
         End of file:     kw_tmr.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:50 2014
  
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
/main/1      ---      vp   1. initial release.
/main/2      ---      nm   1. LTERLC Release 2.1
/main/3     kw002.201 vp   1. Patch for optimization,fixes for multi-region
                               and retransmission.
/main/4     kw005.201 ap   1. Updated for statistics.
                           2. Added L2 measurement support.
                           3. Changed wait caculation ccpu00117634
                      rd   4. If wait is coming to be 0 and the timer is
                              configured, then wait is set to 1. Change is
                              done is kwStartTmr. 
*********************************************************************91*/

