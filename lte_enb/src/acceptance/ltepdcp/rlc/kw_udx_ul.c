

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by LTE MAC
 
    File:   kw_udx.c
 
    Sid:      kw_udx_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:52 2014
 
    Prg:   mraj
 
**********************************************************************/
/** @file kw_udx.x
@brief This file contains basic data structures for the Uplink Downlink 
interface.
*/
	 

/*
*     The defines in this file correspond to structures and variables 
*     used by the following TRILLIUM software:
*
*     part no.             description
*     --------     ----------------------------------------------
*
*/
 
/* header include files (.h) */
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
#include "kw_err.h"        /* Err defines */
#include "kw_env.h"        /* RLC environment options */

#include "kw.h"            /* RLC defines */
#include "kw_ul.h"
#include "kw_dl.h"
#include "kw_udx.h"

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
#include "kw_udx.x"


/* local defines */

/* local externs */

/* forward references */

/* public variable declarations */
EXTERN S16 kwHdlCkwUlCfgReq ARGS((KwCb  *gCb,KwCfgInfo *cfgInfo,
              UdxCfgCfmInfo *cfmInfo, CkwCfgCfmInfo *cfgCfm));



/**
  * @brief
  * UDX APIs
  */
/**
 *
 * @brief 
 *
 *        Handler for bind confirmation from DL.
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
PUBLIC S16 KwUlUdxBndCfm
(
Pst *pst,   /* Post structure */
SuId suId,   /* service user SAP ID */
U8 status   /* status of confirmation */
)
#else
PUBLIC S16 KwUlUdxBndCfm (pst, suId, status)
Pst *pst;    /* Post structure */
SuId suId;    /* service user SAP ID */
U8 status;    /* status of confirmation */
#endif
{
   U16             event;              /* Event */
   U16             cause;              /* Cause */
   KwUdxUlSapCb      *udxSap;            /* RGU SAP Control Block */
   KwCb            *tKwCb;

   TRC3(KwUlUdxBndCfm)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE (RFAILED);
   }
#endif
   tKwCb = KW_GET_KWCB(pst->dstInst);

#ifdef DEBUGP
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
           "KwUlUdxBndCfm(post, suId(%d), status(%d)\n", suId, status));
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
                 "KwUlUdxBndCfm: Invalid suId\n");
      KW_SEND_SAPID_ALARM(tKwCb,suId, 
                           LKW_EVENT_LI_BND_CFM, LCM_CAUSE_INV_SUID);

      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   udxSap = tKwCb->u.ulCb->udxUlSap + suId;

#ifdef DEBUGP
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_DETAIL),
       (tKwCb->init.prntBuf, "KwLiRguBndCfm: For RGU SAP state=%d\n",
       udxSap->state));
#endif

   /* Check rguSap state */
   switch (udxSap->state)
   {
      case KW_SAP_BINDING:
      {
         if(TRUE == kwChkTmr(tKwCb,(PTR)udxSap,KW_EVT_WAIT_BNDCFM))
         {
             kwStopTmr (tKwCb,(PTR)udxSap, KW_EVT_WAIT_BNDCFM);
         }
         udxSap->retryCnt = 0;
          
         if (status == CM_BND_OK)
         {
            udxSap->state = KW_SAP_BND;
            event = LCM_EVENT_BND_OK;
            cause = LKW_CAUSE_SAP_BNDENB;
         }
         else
         {
            udxSap->state = KW_SAP_CFG;
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
 *        Handler for bind confirmation from DL.
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
PUBLIC S16 KwUlUdxCfgCfm
(
Pst *pst,   /* Post structure */
SuId suId,   /* service user SAP ID */
UdxCfgCfmInfo *cfmInfo   /* status of confirmation */
)
#else
PUBLIC S16 KwUlUdxCfgCfm (pst, suId, cfmInfo)
Pst           *pst;    /* Post structure */
SuId          suId;    /* service user SAP ID */
UdxCfgCfmInfo *cfmInfo;   /* status of confirmation */
#endif
{
   S16              ret;
   KwUdxUlSapCb   *udxSap;            /* RGU SAP Control Block */
   KwCkwSapCb     *ckwSap;
   KwCb            *tKwCb;
   CkwCfgCfmInfo   *cfgCfm;
   KwCfgInfo       *cfgInfo;

   TRC3(KwUlUdxCfgCfm)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE (RFAILED);
   }
#endif
   tKwCb = KW_GET_KWCB(pst->dstInst);

#ifdef DEBUGP
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
           "KwUlUdxBndCfm(post, suId(%d), )\n", suId));
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (suId < 0)
   {
      /* INNC: ERROR CLASS */
      KWLOGERROR(tKwCb,ERRCLS_INT_PAR, EKW041, (ErrVal) suId,
                 "KwUlUdxBndCfm: Invalid suId\n");
      KW_SEND_SAPID_ALARM(tKwCb,suId, 
                           LKW_EVENT_LI_BND_CFM, LCM_CAUSE_INV_SUID);

      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   udxSap = tKwCb->u.ulCb->udxUlSap + suId;

   ret = kwDbmFindUlTransIdLst(tKwCb,cfmInfo->transId, &cfgInfo);
   if (ret != ROK)
   {
      KWLOGERROR(tKwCb,ERRCLS_INT_PAR, EKW041, (ErrVal)cfmInfo->transId,
                 "KwUlUdxUeIdChgCfm: Invalid transId\n");
      KW_PST_FREE(pst->region, pst->pool,cfmInfo, sizeof (UdxCfgCfmInfo));
      RETVALUE (RFAILED);
   }
  
      /* Allocate memory and memset to 0 for cfmInfo */
   KW_ALLOC(tKwCb,cfgCfm, sizeof(CkwCfgCfmInfo));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (cfgCfm == NULLP)
   {
      KWLOGERROR(tKwCb,ERRCLS_ADD_RES, EKW209, (ErrVal) RFAILED,
            "KwUiCkwCfgReq: cfgCfm allocation Failed.");
      /* kw002.201 Freeing from proper region */
      KW_PST_FREE(pst->region, pst->pool, cfmInfo, sizeof(CkwCfgCfmInfo));
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

   ret = kwHdlCkwUlCfgReq(tKwCb,cfgInfo, cfmInfo, cfgCfm);
   
    ckwSap = &(tKwCb->u.ulCb->ckwSap);

    KwUiCkwCfgCfm(&(ckwSap->pst), ckwSap->suId, cfgCfm);

   
   RETVALUE(ROK);
} /* KwLiRguBndCfm */

/**
 *
 * @brief 
 *
 *        Handler for bind confirmation from DL.
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
PUBLIC S16 KwUlUdxUeIdChgCfm
(
Pst *pst,                       /* post structure */
SuId suId,                      /* Service User Id */
U32           transId,
UdxUeInfo     *ueInfo,
CmStatus      status
)
#else
PUBLIC S16 KwUlUdxUeIdChgCfm (pst, suId, cfmInfo)
Pst           *pst;            /* post structure */
SuId          suId;            /* Service User Id */
U32           transId;
UdxUeInfo     *ueInfo;
CmStatus      status;
#endif
{
   S16         ret;
   CmStatus    tStatus;
   KwUdxUlSapCb      *udxSap;            /* RGU SAP Control Block */
   KwCkwSapCb          *ckwSap;
   KwCb            *tKwCb;
   KwCfgInfo       *cfgInfo;

   TRC3(KwUlUdxUeIdChgCfm)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE (RFAILED);
   }
#endif
   tKwCb = KW_GET_KWCB(pst->dstInst);

#ifdef DEBUGP
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
           "KwUlUdxUeIdChgCfm(post, suId(%d), \n", suId));
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (suId < 0)
   {
      /* INNC: ERROR CLASS */
      KWLOGERROR(tKwCb,ERRCLS_INT_PAR, EKW041, (ErrVal) suId,
                 "KwUlUdxUeIdChgCfm: Invalid suId\n");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   udxSap = tKwCb->u.ulCb->udxUlSap + suId;

   ret = kwDbmFindUlTransIdLst(tKwCb, transId, &cfgInfo);
   if (ret != ROK)
   {
      KWLOGERROR(tKwCb,ERRCLS_INT_PAR, EKW041, (ErrVal) transId,
                 "KwUlUdxUeIdChgCfm: Invalid transId\n");
      KW_PST_FREE(pst->region, pst->pool,ueInfo, sizeof (UdxUeInfo));
      RETVALUE (RFAILED);
   }

   ret = ROK;
   tStatus.reason = CKW_CFG_REAS_NONE;
   tStatus.status = CKW_CFG_CFM_OK;

   if ( (ret = kwCfgUlUeIdChng(tKwCb,cfgInfo->ueInfo,
                      cfgInfo->newUeInfo, &tStatus)) != ROK)
   {
#ifdef DEBUGP
      KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
            (tKwCb->init.prntBuf, "KwUiCkwUeIdChgReq(pst, oldUe(ueId(%d),\
         cellId(%d)), newUe(ueId(%d), cellId(%d))\n \
            kwCfgUeIdChng Failed: reason (%d)\n",
             cfgInfo->ueInfo->ueId,cfgInfo->ueInfo->cellId,
             cfgInfo->newUeInfo->ueId,cfgInfo->newUeInfo->cellId,

             status.reason));
#endif
   }

   ckwSap = &(tKwCb->u.ulCb->ckwSap);

   if ((status.status == CKW_CFG_CFM_OK) || 
         (tStatus.status == CKW_CFG_CFM_OK))
   {
      tStatus.reason = CKW_CFG_REAS_NONE;
      tStatus.status = CKW_CFG_CFM_OK;
   }
 
   KwUiCkwUeIdChgCfm(&ckwSap->pst,ckwSap->suId,transId,(CkwUeInfo *)ueInfo,tStatus);

   RETVALUE(ROK);
} /* KwUlUdxUeIdChgCfm */





PUBLIC S16  KwUlUdxStaUpdCfm
(
Pst*                pst,
SuId                suId,
CmLteRlcId         *rlcId,
KwUdxBufLst        *pBufLst
)
{
   CmLListCp        *lst;
   KwTx             *pdu;
   KwRetx           *rpdu;
   KwSdu            *sdu;
   KwCb             *tKwCb;

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      KW_FREE(tKwCb, pBufLst, sizeof(KwUdxBufLst));
      RETVALUE (RFAILED);
   }
#endif
   tKwCb = KW_GET_KWCB(pst->dstInst);

   /* Release Tx Lst */
   lst = &(pBufLst->rlsTxLst);
   while(lst->first)
   {
     pdu = (KwTx *)(lst->first->node);
     cmLListDelFrm(lst, lst->first);
     KW_FREE_BUF(pdu->pdu);
     KW_FREE(tKwCb, pdu, sizeof(KwTx));
   }
   /* Release Retx Lst */
   lst = &(pBufLst->rlsRetxLst);
   while(lst->first)
   {
     rpdu = (KwRetx*)(lst->first->node);
     cmLListDelFrm(lst, lst->first);
     KW_FREE_BUF(rpdu->seg);
     KW_FREE(tKwCb, rpdu, sizeof(KwRetx));
   }
   /* Release Sdu Lst */
   lst = &(pBufLst->rlsSduLst);
   while(lst->first)
   {
     sdu = (KwSdu *)(lst->first->node);
     cmLListDelFrm(lst, lst->first);
     if (sdu->mBuf)
     {
        KW_FREE_BUF(sdu->mBuf);
        sdu->mBuf = NULLP;
     }
     KW_FREE(tKwCb, sdu, sizeof(KwSdu));
   }

   KW_FREE(tKwCb, pBufLst, sizeof(KwUdxBufLst));

   RETVALUE (ROK);
} /* KwUdxDlmUlmBufLstReq */

/**
 *
 * @brief 
 *
 *        Handler for bind confirmation from DL.
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
PUBLIC S16 kwHdlCkwUlCfgReq
(
KwCb         *gCb,
KwCfgInfo    *cfgInfo,
UdxCfgCfmInfo *cfmInfo,
CkwCfgCfmInfo *cfgCfm
)
#else
PUBLIC S16 kwHdlCkwUlCfgReq(gCb,cfgInfo,cfmInfo,cfmInfo)
KwCb         *gCb;
KwCfgInfo    *cfgInfo;
UdxCfgCfmInfo *cfmInfo;
CkwCfgCfmInfo *cfgCfm;
#endif
{
   CkwCfgInfo *cfg;
   U8    idx;

   cfg = cfgInfo->cfgInfo;

   for (idx = 0; idx < cfg->numEnt; idx++)
   {
      CkwEntCfgCfmInfo  *entCfgCfm;
      UdxEntCfgCfmInfo  *entDlCfgCfm;
      CkwEntCfgInfo     *entCfg;

      entCfg  = &(cfg->entCfg[idx]);
      entCfgCfm   = &(cfgCfm->entCfgCfm[idx]);
      entDlCfgCfm = &(cfmInfo->entCfgCfm[idx]);
      switch (entCfg->cfgType)
      {
         case CKW_CFG_ADD:
            {
               if (entCfg->dir & KW_DIR_UL)
               {
                  /* Add a new RB entity configuration */
                  if (kwCfgAddUlRb(gCb,cfg->ueId, cfg->cellId,\
                              entCfg, entCfgCfm) != ROK)
                  {
#ifdef DEBUGP
                      KWDBGP(gCb,
                       (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                        (gCb->init.prntBuf, "KwUiCkwCfgReq(pst, cfg(ueId(%d),\
                     cellId(%d), cfgType(%d), rbId(%d)) \
                     kwCfgAddRb Failed: reason (%d)\n",
                         cfg->ueId, cfg->cellId, entCfg->cfgType,
                         cfg->entCfg[idx].rbId, entCfgCfm->status.reason));
#endif
                  }
                  if (entCfg->dir & KW_DIR_DL)
                  {
                      if (entDlCfgCfm->status.status != CKW_CFG_CFM_OK)
                      {
                        KW_MEM_CPY(entCfgCfm, entDlCfgCfm, 
                                         sizeof(CkwCfgCfmInfo)); 
                      }
                  }
               }
               else if (entCfg->dir & KW_DIR_DL)
               {
                 KW_MEM_CPY(entCfgCfm, entDlCfgCfm, sizeof(CkwCfgCfmInfo)); 
               }
               break;
            }

         case CKW_CFG_MODIFY:
            {
               if (entCfg->dir & KW_DIR_UL)
               {
                  /* Re-configure the existing RB entity configuration */
                  if (kwCfgReCfgUlRb(gCb,cfg->ueId, cfg->cellId,\
                           entCfg, entCfgCfm) != ROK)
                  {
#ifdef DEBUGP
                     KWDBGP(gCb,
                      (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                        (gCb->init.prntBuf, "KwUiCkwCfgReq(pst, cfg(ueId(%d),\
                     cellId(%d), cfgType(%d), rbId(%d))\n \
                     kwCfgReCfgRb Failed: reason (%d)\n",
                         cfg->ueId, cfg->cellId, entCfg->cfgType,
                         cfg->entCfg[idx].rbId, entCfgCfm->status.reason));
#endif
                  }
                  if (entCfg->dir & KW_DIR_DL)
                  {
                      if (entDlCfgCfm->status.status != CKW_CFG_CFM_OK)
                      {
                        KW_MEM_CPY(entCfgCfm, entDlCfgCfm, 
                                         sizeof(CkwCfgCfmInfo)); 
                      }
                  }
               }
               else if (entCfg->dir & KW_DIR_DL)
               {
                  /* send configuration to DL instance */
                  KW_MEM_CPY(entCfgCfm, entDlCfgCfm,sizeof(CkwCfgCfmInfo)); 
               }
               break;
            }
         case CKW_CFG_DELETE:
            {
               if (entCfg->dir & KW_DIR_UL)
               {
                  /* Delete the existing RB entity configuration */
                  if (kwCfgDelUlRb(gCb,cfg->ueId, cfg->cellId,\
                        entCfg, entCfgCfm) != ROK)
                  {
#ifdef DEBUGP
                     KWDBGP(gCb,
                     (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                        (gCb->init.prntBuf, "KwUiCkwCfgReq(pst, cfg(ueId(%d),\
                     cellId(%d), cfgType(%d), rbId(%d))\n \
                     kwCfgDelRb Failed: reason (%d)\n",
                         cfg->ueId, cfg->cellId, entCfg->cfgType,
                         cfg->entCfg[idx].rbId, entCfgCfm->status.reason));
#endif
                  }

                  if (entCfg->dir & KW_DIR_DL)
                  {
                      if (entDlCfgCfm->status.status != CKW_CFG_CFM_OK)
                      {
                        KW_MEM_CPY(entCfgCfm, entDlCfgCfm, 
                                         sizeof(CkwCfgCfmInfo)); 
                      }
                  }
               }
               else if (entCfg->dir & KW_DIR_DL)
               {
                  KW_MEM_CPY(entCfgCfm, entDlCfgCfm,sizeof(CkwCfgCfmInfo)); 
               }
               break;
            }

         case CKW_CFG_REESTABLISH:
            {
               Bool sendReEstInd;

               if (entCfg->dir & KW_DIR_UL)
               {
                  sendReEstInd = TRUE;
                  if (entCfg->dir & KW_DIR_DL)
                  {
                     if (entDlCfgCfm->status.status != CKW_CFG_CFM_OK)
                     {
                        sendReEstInd = FALSE;
                     }
                  }
                  /* Re-establish the existing RB entity configuration */
                  if (kwCfgReEstUlRb(gCb,cfg->ueId, cfg->cellId,\
                         sendReEstInd, entCfg, entCfgCfm) != ROK)
                  {
#ifdef DEBUGP
                       KWDBGP(gCb,
                       (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                         (gCb->init.prntBuf, "KwUiCkwCfgReq(pst, \
                         cfg(ueId(%d),\
                        cellId(%d), cfgType(%d), rbId(%d))\
                         kwCfgReEstRb Failed: reason (%d)\n",
                          cfg->ueId, cfg->cellId, entCfg->cfgType,
                           cfg->entCfg[idx].rbId, entCfgCfm->status.reason));
#endif
                  }
                  if (entCfg->dir & KW_DIR_DL)
                  {
                     if (entDlCfgCfm->status.status != CKW_CFG_CFM_OK)
                     {
                        KW_MEM_CPY(entCfgCfm, entDlCfgCfm,
                                       sizeof(CkwCfgCfmInfo)); 
                     }
                  }
               }
               if (entCfg->dir & KW_DIR_DL)
               {
                   KW_MEM_CPY(entCfgCfm, entDlCfgCfm,
                                    sizeof(CkwCfgCfmInfo)); 
               }
               break;
            }
         case CKW_CFG_DELETE_UE:
            {
               /* Delete all RB entity configuration under UE */
               if (kwCfgDelUlUe(gCb,cfg->ueId, cfg->cellId,\
                     entCfg, entCfgCfm) != ROK)
               {
#ifdef DEBUGP
                  KWDBGP(gCb,
                   (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                    (gCb->init.prntBuf, "KwUiCkwCfgReq(pst, cfg(ueId(%d),\
                      cellId(%d), cfgType(%d), rbId(%d))\
                    kwCfgDelUe Failed: reason (%d)\n",
                    cfg->ueId, cfg->cellId, entCfg->cfgType,
                   cfg->entCfg[idx].rbId, entCfgCfm->status.reason));
#endif
               }
               if (entDlCfgCfm->status.status == CKW_CFG_CFM_OK)
               {
                   KW_MEM_CPY(entCfgCfm, entDlCfgCfm,
                                    sizeof(CkwCfgCfmInfo)); 
               }
               break;
            }
         case CKW_CFG_DELETE_CELL:
            {
               if ( kwCfgDelUlCell(gCb,cfg->cellId,entCfg,entCfgCfm) != ROK )
               {
#ifdef DEBUGP
                  KWDBGP(gCb,
                        (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                        (gCb->init.prntBuf, "KwUiCkwCfgReq(pst, cfg(ueId(%d),\
                     cellId(%d), cfgType(%d), rbId(%d))\
                      kwCfgDelCell Failed: reason (%d)\n",
                         cfg->ueId, cfg->cellId, entCfg->cfgType,
                         cfg->entCfg[idx].rbId, entCfgCfm->status.reason));
#endif
               }
               if (entDlCfgCfm->status.status == CKW_CFG_CFM_OK)
               {
                   KW_MEM_CPY(entCfgCfm, entDlCfgCfm,
                                    sizeof(CkwCfgCfmInfo)); 
               }
               break;
            }
         default:
            {
               KW_CFG_FILL_CFG_CFM(entCfgCfm, entCfg->rbId, entCfg->rbType,\
                  CKW_CFG_CFM_NOK, CKW_CFG_REAS_INVALID_CFG);

#ifdef DEBUGP
               KWDBGP(gCb,
                     (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                     (gCb->init.prntBuf, "KwUiCkwCfgReq(pst, cfg(ueId(%d),\
                  cellId(%d), cfgType(%d), rbId(%d)) Failed: reason (%d)\n",
                     cfg->ueId, cfg->cellId, entCfg->cfgType,
                     cfg->entCfg[idx].rbId, CKW_CFG_REAS_INVALID_CFG));
#endif
            }
      }
   }

   /* Assign number of entity configuraitons and suId */
   cfgCfm->transId = cfg->transId;
   cfgCfm->ueId = cfg->ueId;
   cfgCfm->cellId = cfg->cellId;
   cfgCfm->numEnt = cfg->numEnt;

    RETVALUE(ROK);
}
#ifdef __cplusplus
}
#endif /* __cplusplus */


/**********************************************************************
         End of file:     kw_udx_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:52 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       mraj   1. LTE RLC Initial Release
*********************************************************************91*/

