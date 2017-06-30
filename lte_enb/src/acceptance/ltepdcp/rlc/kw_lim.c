

/********************************************************************20**
  
        Name:    LTE-RLC Layer - Lower Interface Functions
    
        Type:    C file
  
     Desc:     Source code for RLC Lower Interface Module.
               This file contains following functions
      
        --KwLiRguBndCfm
        --KwLiRguCDatInd
        --KwLiRguDDatInd
        --KwLiRguCStaInd
        --KwLiRguDStaInd
        --KwLiRguHqStaInd

     File:     gp_lim.c

     Sid:      kw_lim.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:47 2014

     Prg:      gk 

**********************************************************************/
/** @file gp_lim.c
@brief RLC Lower Interface Module
*/


/*
 *      This software may be combined with the following TRILLIUM
 *      software:
 *
 *      part no.                      description
 *      --------    ----------------------------------------------
 *      1000241     LTE-MAC
 *      1000369     LTE-RRC
 */


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
#include "kw_err.h"
#include "kw_env.h"        /* RLC environment options */

#include "kw.h"            /* RLC defines */
#include "kw_dl.h"
#include "kw_ul.h"

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

#ifdef __cplusplus
EXTERN "C" {
#endif /* __cplusplus */


/*****************************************************************************
 *                          RGU INTERFACE
 ****************************************************************************/
/**
 *
 * @brief 
 *
 *        Handler for bind confirmation from MAC.
 *
 * @b Description:
 *
 *        This function handles the bind confirmation received
 *        from MAC. 
 *
 *  @param[in] pst     Post structure  
 *  @param[in] suId    Service User ID
 *  @param[in] status  Status of confirmation 
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */

#ifdef ANSI
PUBLIC S16 KwLiRguBndCfm
(
Pst *pst,   /* Post structure */
SuId suId,   /* service user SAP ID */
U8 status   /* status of confirmation */
)
#else
PUBLIC S16 KwLiRguBndCfm (pst, suId, status)
Pst *pst;    /* Post structure */
SuId suId;    /* service user SAP ID */
U8 status;    /* status of confirmation */
#endif
{
   U16             event;              /* Event */
   U16             cause;              /* Cause */
   KwRguSapCb      *rguSap;            /* RGU SAP Control Block */
   KwCb            *tKwCb;

   TRC3(KwLiRguBndCfm)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE (RFAILED);
   }
#endif
   tKwCb = KW_GET_KWCB(pst->dstInst);

#ifdef DEBUGP
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
           "KwLiRguBndCfm(post, suId(%d), status(%d)\n", suId, status));
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (tKwCb->init.cfgDone != TRUE)
   {
      /* INNC: ERROR CLASS */
      KWLOGERROR(tKwCb,ERRCLS_INT_PAR, EKW040, (ErrVal) suId,
                 "KwLiRguBndCfm: General configuration not done\n");
      KW_SEND_SAPID_ALARM(tKwCb,suId, 
                          LKW_EVENT_LI_BND_CFM, LCM_CAUSE_INV_STATE);

      RETVALUE(RFAILED);
   }

   if (suId < 0)
   {
      /* INNC: ERROR CLASS */
      KWLOGERROR(tKwCb,ERRCLS_INT_PAR, EKW041, (ErrVal) suId,
                 "KwLiRguBndCfm: Invalid suId\n");
      KW_SEND_SAPID_ALARM(tKwCb,suId, 
                           LKW_EVENT_LI_BND_CFM, LCM_CAUSE_INV_SUID);

      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   rguSap = (tKwCb->genCfg.rlcMode == LKW_RLC_MODE_DL) ?
            &(tKwCb->u.dlCb->rguDlSap) : &(tKwCb->u.ulCb->rguUlSap);

#ifdef DEBUGP
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_DETAIL),
       (tKwCb->init.prntBuf, "KwLiRguBndCfm: For RGU SAP state=%d\n",
       rguSap->state));
#endif

   /* Check rguSap state */
   switch (rguSap->state)
   {
      case KW_SAP_BINDING:
      {
         kwStopTmr (tKwCb,(PTR)rguSap, KW_EVT_WAIT_BNDCFM);

         rguSap->retryCnt = 0;
          
         if (status == CM_BND_OK)
         {
            rguSap->state = KW_SAP_BND;
            event = LCM_EVENT_BND_OK;
            cause = LKW_CAUSE_SAP_BNDENB;
         }
         else
         {
            rguSap->state = KW_SAP_CFG;
            event = LCM_EVENT_BND_FAIL;
            cause = LKW_CAUSE_UNKNOWN;
         }
      }
      break;

     default:
        event = LKW_EVENT_RGU_BND_CFM;
        cause = LCM_CAUSE_INV_STATE;
        break;
   }

   /* Send an alarm with proper event and cause */
   KW_SEND_SAPID_ALARM(tKwCb,suId, event, cause);

   RETVALUE(ROK);
} /* KwLiRguBndCfm */


/**
 *
 * @brief 
 *
 *        Handler for getting the PDU from MAC for common logical channels. 
 *
 * @b Description:
 *
 *        This function receives the PDU from MAC for common logical channels
 *        and invokes the handler for processing the PDU.
 *
 *  @param[in] pst     -   Post structure  
 *  @param[in] suId    -   Service User ID
 *  @param[in] datInd  -   Data Indication Information 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 KwLiRguCDatInd
(
Pst            *pst,                   /* Post Structure */
SuId           suId,                   /* Service User SAP ID */
RguCDatIndInfo *datInd                 /* Data Indication Information */
)
#else
PUBLIC S16 KwLiRguCDatInd(pst,suId,datInd)
Pst            *pst;                   /* Post Structure */
SuId           suId;                   /* Service User SAP ID */
RguCDatIndInfo *datInd;                /* Data Indication Information */
#endif
{
   S16         ret;                    /* Return Value */
   KwUlRbCb      *rbCb;                  /* RB Control Block */
   KwCb          *tKwCb;

   TRC3(KwLiRguCDatInd)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE (RFAILED);
   }
#endif

   tKwCb = KW_GET_KWCB(pst->dstInst);

   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
           "KwLiRguCDatInd(post, suId(%d)\n", suId));

   if (tKwCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
   {
      RETVALUE(RFAILED);
   }

   ret = ROK;
   rbCb = NULLP;

   /* Fetch RbCb from lcId */
   ret = kwDbmFetchUlRbCbForLi(tKwCb,0, datInd->cellId, 
                               datInd->lcId, KW_DIR_UL, &rbCb);
   if (ret != ROK)
   {
      KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
               "KwLiRguCDatInd: kwDbmFetchRbCbForLi --\
               ueId(%d), cellId(%d), lcId(%d)\n",
               0, datInd->cellId, datInd->lcId));
      /* kw002.201 :Freeing from proper region */
      KW_PST_FREE(pst->region, pst->pool, datInd, sizeof(RguCDatIndInfo));
      RETVALUE(ret);
   }

   /* Dispatch to TM Module */
#ifdef CCPU_OPT
   ret = kwTmmRcvFrmLi(tKwCb,rbCb, datInd->rnti, datInd->pdu);
#else /* CCPU_OPT */
   ret = kwTmmRcvFrmLi(tKwCb,rbCb, datInd->pdu);
#endif /* CCPU_OPT */
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
               "KwLiRguCDatInd: kwTmmRcvFrmLi Failed\n"));
      /* kw002.201 :Freeing from proper region */
      KW_PST_FREE(pst->region, pst->pool, datInd, sizeof(RguCDatIndInfo));
      RETVALUE(ret);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

      /* kw002.201 :Freeing from proper region */
   KW_PST_FREE(pst->region, pst->pool, datInd, sizeof(RguCDatIndInfo));

   RETVALUE(ROK);
} /* KwLiRguCDatInd */


/**
 *
 * @brief 
 *
 *        Handler for getting PDU(s) from MAC for one or more 
 *        dedicated logical channels. 
 *
 * @b Description:
 *
 *        This function receives the PDU(s) from MAC for one or 
 *        more dedicated logical channels and invokes the 
 *        respective handlers for processing the PDU(s).
 *
 *  @param[in] pst     -   Post structure  
 *  @param[in] suId    -   Service User ID
 *  @param[in] datInd  -   Data Indication Information 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 KwLiRguDDatInd
(
Pst            *pst,                   /* Post Structure */
SuId           suId,                   /* Service User SAP ID */
RguDDatIndInfo *datInd                 /* Data Indication Information */
)
#else
PUBLIC S16 KwLiRguDDatInd(pst,suId,datInd)
Pst            *pst;                   /* Post Structure */
SuId           suId;                   /* Service User SAP ID */
RguDDatIndInfo *datInd;                /* Data Indication Information */
#endif
{
   KwCb *tKwCb;

   TRC3(KwLiRguDDatInd)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE (RFAILED);
   }
#endif

#ifdef SS_PERF_MEASUREMENT
   SS_START_MEASUREMENT(ssPerf[7],7);
#endif /*SS_PERF_MEASUREMENT*/
 
   tKwCb = KW_GET_KWCB(pst->dstInst);

   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
          "KwLiRguDDatInd(pst, suId(%d))\n", suId));

   if (tKwCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
   {
       KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
          "KwLiRguDDatInd(pst, suId(%d))recieved in DL Inst\n", suId));
      RETVALUE(RFAILED);
   }
   /* Dispatch to UM Module */
   if (kwUtlRcvFrmLi(tKwCb,datInd) != ROK)
   {
      KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
               "KwLiRguDDatInd: kwUtlRcvFrmLi Failed\n"));
   }

   /* kw002.201 :Freeing from proper region */
   KW_PST_FREE(pst->region, pst->pool, datInd, sizeof(RguDDatIndInfo));

#ifdef SS_PERF_MEASUREMENT
   SS_STOP_MEASUREMENT(ssPerf[7],7);
#endif /*SS_PERF_MEASUREMENT*/

   RETVALUE(ROK);
} /* KwLiRguDDatInd */


/**
 *
 * @brief 
 *
 *        Handler for trigerring the data transfer from RLC to MAC
 *        for common logical channels.
 *
 * @b Description:
 *
 *        This function receives the size of the PDU to be transmitted
 *        and acts as a trigger for forming PDU and sending it to MAC. 
 *
 *  @param[in] pst     -   Post structure  
 *  @param[in] suId    -   Service User ID
 *  @param[in] staInd  -   Status Indication Information.
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 KwLiRguCStaInd
(
Pst       *pst,                         /* Post Structure */
SuId       suId,                         /* Service User ID */
RguCStaIndInfo *staInd   /* Status Indication Information for Common Logical Channels */
)
#else
PUBLIC S16 KwLiRguCStaInd(pst,suId,staInd)
Pst       *pst;                         /* Post Structure */
SuId       suId;                         /* Service User ID */
RguCStaIndInfo *staInd;   /* Status Indication Information for Common Logical Channels */
#endif
{
   S16         ret;                    /* Return Value */
   KwDlRbCb      *rbCb;                  /* RB Control Block */
   KwCb        *tKwCb;

   TRC3(KwLiRguCStaInd)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE (RFAILED);
   }
#endif

   tKwCb = KW_GET_KWCB(pst->dstInst);

   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
           "KwLiRguCStaInd(post, suId(%d)\n", suId));

   if (tKwCb->genCfg.rlcMode == LKW_RLC_MODE_UL)
   {
       KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
          "KwLiRguCStaInd(pst, suId(%d))recieved in UL Inst\n", suId));
      RETVALUE(RFAILED);
   }

   rbCb = NULLP;

   /* Fertch RbCb from lcId */
   ret = kwDbmFetchDlRbCbForLi(tKwCb,0, staInd->cellId, staInd->lcId, 
                                               KW_DIR_DL, &rbCb);
   if (ret != ROK)
   {
      /* INCNC: DEBUG_PRINT_ERROR
       * RB CB not found
       */
      KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
               "KwLiRguCStaInd: kwDbmFetchRbCbForLi --\
               ueId(%d), cellId(%d), lcId(%d)\n",
               0, staInd->cellId, staInd->lcId));
      /* kw002.201 :Freeing from proper region */
      KW_PST_FREE(pst->region, pst->pool, staInd, sizeof(RguCStaIndInfo));
      RETVALUE(ret);
   }

   /* Dispatch to TM Module */
   rbCb->transId = staInd->transId;
   ret = kwTmmSndToLi(tKwCb,rbCb);
   if (ret != ROK)
   {
      KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
               "KwLiRguCStaInd: kwTmmSndToLi Failed\n"));
   }
   /* kw002.201 :Freeing from proper region */
   KW_PST_FREE(pst->region, pst->pool, staInd, sizeof(RguCStaIndInfo));
   RETVALUE(ret);
} /* KwLiRguCStaInd */


/**
 *
 * @brief  
 *
 *        Handler for trigerring the data transfer from RLC to MAC
 *        for dedicated logical channels.
 *
 * @b Description:
 *
 *        This function receives the size of the PDUs to be transmitted to
 *        MAC via one or more dedicated logical channels and acts as a trigger
 *        for forming PDUs and sending them to MAC. 
 *
 *  @param[in] pst     -   Post structure  
 *  @param[in] suId    -   Service User ID
 *  @param[in] staInd  -   Status Indication Information. 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 KwLiRguDStaInd
(
Pst       *pst,          /* Post Structure */
SuId       suId,          /* Service User ID */
RguDStaIndInfo *staInd   /* Status Indication Information for Dedicated Logical Channels */
)
#else
PUBLIC S16 KwLiRguDStaInd(pst,suId,staInd)
Pst       *pst;          /* Post Structure */
SuId       suId;          /* Service User ID */
RguDStaIndInfo *staInd;   /* Status Indication Information for Dedicated Logical Channels */
#endif
{
   S16 ret;
   KwCb *tKwCb;

   TRC3(KwLiRguDStaInd)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE (RFAILED);
   }
#endif

#ifdef SS_PERF_MEASUREMENT
   SS_START_MEASUREMENT(ssPerf[3],3);
#endif /*SS_PERF_MEASUREMENT*/


   tKwCb = KW_GET_KWCB(pst->dstInst);

   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
          "KwLiRguDStaInd(pst, suId(%d))\n", suId));

   if (tKwCb->genCfg.rlcMode == LKW_RLC_MODE_UL)
   {
       KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
          "KwLiRguDStaInd(pst, suId(%d))recieved in DL Inst\n", suId));
      RETVALUE(RFAILED);
   }
   ret = kwUtlSndToLi(tKwCb,staInd);
   /* Dispatch to UM/AM Module */
   if (ret != ROK)

   {
      KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
               "KwLiRguDStaInd: kwUtlSndToLi Failed\n"));
   }

   /* kw002.201 :Freeing from proper region */
   KW_PST_FREE(pst->region, pst->pool, staInd, sizeof(RguDStaIndInfo));

#ifdef SS_PERF_MEASUREMENT
   SS_STOP_MEASUREMENT(ssPerf[3],3);
#endif /*SS_PERF_MEASUREMENT*/

   RETVALUE(ret);
} /* KwLiRguDStaInd */
/* kw005.201 added support for L2 Measurement */

/**
 *
 * @brief  
 *
 *        Handler for indicating the Harq Status of the data sent.
 *
 * @b Description:
 *
 *        This function receives the harq status of the data sent to MAC.
 *        This information is used for two things.
 *        1. Computing the UuLoss of UM
 *        2. Computing the DL Delay for UM and AM.
 *
 *  @param[in] pst     -   Post structure  
 *  @param[in] suId    -   Service User ID
 *  @param[in] staInd  -   Harq Status Indication Information. 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 KwLiRguHqStaInd
(
Pst              *pst,     /* Post Structure */
SuId             suId,     /* Service User ID */
RguHarqStatusInd *staInd   /* Status Indication Information for Dedicated Logical Channels */
)
#else
PUBLIC S16 KwLiRguHqStaInd(pst,suId,staInd)
Pst              *pst;      /* Post Structure */
SuId             suId;      /* Service User ID */
RguHarqStatusInd *staInd;   /* Status Indication Information for Dedicated Logical Channels */
#endif
{

#ifdef LTE_L2_MEAS_RLC
   KwUeKey    ueKey;
   S16        ret; 
   KwUeCb     *ueCb;
   U8         tbIdx;

   TRC3(KwLiRguHqStaInd)

   KWDBGP((KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
           "KwLiRguHqStaInd(post, suId(%d)\n", suId));

   ueKey.cellId = staInd->cellId;
   ueKey.ueId   = staInd->ueId;

   ret = kwDbmFetchUeCb(ueKey.ueId, ueKey.cellId, &ueCb);
   if (ret != ROK )
   {
      /* Fetch UeCb failed */
      KWLOGERROR(ERRCLS_ADD_RES, EKW217, (ErrVal) RFAILED,
            "kwDbmFetchUeCb : Fetch UeCb Failed.");
      RETVALUE(RFAILED);
   }

   /*Call kwUtlProcHarqInd as many times as number of Tbs present*/
   for ( tbIdx = 0; tbIdx < staInd->numTbs; tbIdx++)
   {
      kwUtlProcHarqInd(staInd, ueCb, tbIdx);
   }
   KW_FREE(staInd,sizeof(RguHarqStatusInd));  

#endif /* LTE_L2_MEAS_RLC */
   RETVALUE(ROK);
} /* KwLiRguHqStaInd */

#ifdef __cplusplus
}
#endif /* __cplusplus */

/********************************************************************30**
         End of file:     kw_lim.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:47 2014
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
/main/1      ---       gk   1. initial release.
/main/2      ---       nm   1. LTERLC Release 2.1
/main/3      kw002.201 vp   1. Patch for optimization,fixes for multi-region
                               and retransmission.
/main/4      kw005.201 ap   1. Changed the for loop condition in KwLiRguHqStaInd
                               for calling kwUtlProcHarqInd as many times as
                               number of TBs present.
                            2. Added support for L2 Measurement.
                       rd   3. Updated with important Avtecs comments.
*********************************************************************91*/

