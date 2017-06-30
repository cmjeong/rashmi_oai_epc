

/**********************************************************************
 
    Name:   LTE RLC layer
 
    Type:   C include file
 
    Desc:   Defines required by LTE MAC
 
    File:   kw_udx.c
 
    Sid:      kw_udx_dl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:50 2014
 
    Prg:   mraj
 
**********************************************************************/
 

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
#include "kw_udx.x"


/* local defines */
#define KW_AM_SND_DSTA_RSP() do {\
   U32        _bo;\
   KW_UPD_AMBO(AMDL, _bo);\
   kwUtlSndDStaRsp(tKwCb, rbCb, _bo, AMDL.estHdrSz, AMDL.cntrlBo ? TRUE : FALSE); \
} while(0)

EXTERN S16 kwDlmHndlStaRsp ARGS (( KwCb  *gCb,KwDlRbCb  *rbCb,
                KwUdxStaPdu *pStaPdu, KwUdxBufLst  *rlsPduLst));


/* local externs */

/* forward references */

/* public variable declarations */



/**
  * @brief
  * UDX APIs
  */

/**
 *
 * @brief 
 *
 *        Handler for binding the RLC upper layer service user with 
 *        the RLC layer.
 *
 * @b Description:
 *
 *        This function is used by RLC user to request for binding to 
 *        RLC. This function is called by the CKW interfacei to bind 
 *        RLC's SAP (identified by spId) with the service user's
 *        SAP (identified by suId). 
 *
 *  @param[in] pst   Post structure  
 *  @param[in] suId  Service user SAP ID 
 *  @param[in] spId  Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 KwDlUdxBndReq 
(
Pst  *pst,   /* Post structure */ 
SuId suId,   /* service user SAP ID */ 
SpId spId   /* service provider identifier */
)
#else
PUBLIC S16 KwDlUdxBndReq (pst, suId, spId)
Pst *pst;    /* Post structure */
SuId suId;    /* service user SAP ID */
SpId spId;    /* service provider identifier */
#endif
{
   KwUdxDlSapCb      *udxSap;            /* pointer to session SAP */
   S16             ret;                /* return value */
   KwCb            *tKwCb;

   TRC3(KwDlUdxBndReq);

   ret = ROK;

   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE(RFAILED);
   }
   
   /* Venki */
   /*tKwCb = KW_GET_KWCB(pst->dstInst);*/
   tKwCb = KW_GET_KWCB(0);

#ifdef DEBUGP
   /* DEBUG_PRINT */
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
            "KwDlUdxBndReq(pst, spId(%d), suId(%d))\n", spId, suId));
#endif

   udxSap = (tKwCb->u.dlCb->udxDlSap + spId);

   /* Verify CKW SAP State */
   switch(udxSap->state)
   {
      /* SAP is configured but not bound */
      case KW_SAP_CFG:
      case KW_SAP_UBND:
      {
         /* copy bind configuration parameters in SSAP sap */
         udxSap->suId = suId;
         udxSap->pst.dstProcId = pst->srcProcId;
         udxSap->pst.dstEnt = pst->srcEnt;
         udxSap->pst.dstInst = pst->srcInst;

         /* Update the State */
         udxSap->state = KW_SAP_BND;

#ifdef DEBUGP
         /* DEBUG_PRINT */
         KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_DETAIL),
                      (tKwCb->init.prntBuf,
                  "KwDlUdxBndReq: state (%d)\n", udxSap->state));
#endif
         break;
      }

      /* SAP is already bound */
      case KW_SAP_BND:
      {
         /* 
          * Sap is already bound check source, destination Entity and 
          * Proc Id
          */
         if (udxSap->pst.dstProcId != pst->srcProcId 
               || udxSap->pst.dstEnt != pst->srcEnt
               || udxSap->pst.dstInst != pst->srcInst
               || udxSap->suId != suId)
         {
            KW_SEND_SAPID_ALARM(tKwCb, spId, 
                            LKW_EVENT_UDX_BND_REQ, LCM_CAUSE_INV_PAR_VAL);

#ifdef DEBUGP
            KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR),
                   (tKwCb->init.prntBuf,
                 "KwDlUdxBndReq: SAP already bound -- state(%d)\n", 
                    udxSap->state));
#endif
            ret = RFAILED;
         }
         break;
      }

     default:
      {
#if (ERRCLASS & ERRCLS_INT_PAR)
         /* LOG ERROR */
         KWLOGERROR(tKwCb,ERRCLS_INT_PAR, EKW207, (ErrVal) spId,
               "KwDlUdxBndReq: udx SAP State is Invalid during Bind Req");

         KW_SEND_SAPID_ALARM(tKwCb,spId, 
                             LKW_EVENT_CKW_BND_REQ, LCM_CAUSE_INV_STATE);
#endif /* ERRCLASS & ERRCLS_INT_PAR */

         /* DEBUG_PRINT */
#ifdef DEBUGP
         KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
                  "KwDlUdxBndReq: CKW SAP State is Invalid during Bind Req"));
#endif

         ret = RFAILED;
         break;
      }
   }

   if (ret == ROK)
   {
      KwDlUdxBndCfm(&(udxSap->pst), udxSap->suId, CM_BND_OK);
   }
   else
   {
      KwDlUdxBndCfm(&(udxSap->pst), udxSap->suId, CM_BND_NOK);
   }

   RETVALUE(ROK);
} /* KwDlUdxBndReq */


/**
 *
 * @brief 
 *
 *        Handler for unbinding the RLC upper layer service user CKW with 
 *        the RLC layer.
 *
 * @b Description:
 *
 *        This function is used by RLC user to request for unbinding  
 *        with RLC.This function is called by the CKW interface to 
 *        unbind with RLC. 
 *
 *  @param[in] pst     Post structure  
 *  @param[in] spId    Service provider SAP ID 
 *  @param[in] reason  Reason for Unbinding 
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 KwDlUdxUbndReq
(
Pst      *pst,         /* Post structure */
SpId     spId,       /* service provider identifier */
Reason   reason      /* Reason for Unbinding */
)
#else
PUBLIC S16 KwDlUdxUbndReq(pst, spId, reason)
Pst      *pst;       /* Post structure */
SpId     spId;       /* service provider identifier */
Reason   reason;       /* Reason for Unbinding */
#endif
{
   KwUdxDlSapCb  *udxSap;            /* CKW SAP control block */
   KwCb        *tKwCb;

   TRC3(KwDlUdxUbndReq)

   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE(RFAILED);
   }
   tKwCb = KW_GET_KWCB(pst->dstInst);

#ifdef DEBUGP
   /* DEBUG_PRINT */
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
            "KwDlUdxUbndReq(pst, spId(%d), reason(%d))\n", spId, reason));
#endif

   UNUSED(reason);

   /* disable upper sap (CKW) */
   udxSap = (tKwCb->u.dlCb->udxDlSap + spId);

#if (ERRCLASS & ERRCLS_INT_PAR)
   KW_GET_AND_VALIDATE_UDXSAP(tKwCb,udxSap, EKW208, "KwUiDlUdxndReq");
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   udxSap->state = KW_SAP_CFG;

   RETVALUE(ROK);
} /* KwDlUdxUbndReq */


/**
 *
 * @brief 
 *
 *        Handler for configuring RLC entities.
 *
 * @b Description:
 *
 *        This function is used by RRC to configure(add/delete/modify)
 *        one or more RLC entities. 
 *
 *        - CKW_CFG_ADD          => kwCfgAddRb
 *        - CKW_CFG_MODIFY       => kwCfgReCfgRb
 *        - CKW_CFG_DELETE       => kwCfgDelRb
 *        - CKW_CFG_REESTABLISH  => kwCfgReEstRb
 *        - CKW_CFG_DELETE_UE    => kwCfgDelUe
 *
 *  @param[in] pst   -  Post structure  
 *  @param[in] spId  -  Serive Provider ID 
 *  @param[in] cfg   -  Configuration information for one or more RLC entities. 
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 KwDlUdxCfgReq
(
Pst         *pst,
SpId        spId,
UdxCfgInfo  *cfg
)
#else
PUBLIC S16 KwDlUdxCfgReq(pst, spId, cfg)
Pst         *pst;
SpId        spId;
UdxCfgInfo  *cfg;
#endif
{
   UdxCfgCfmInfo        *cfgCfm;       /* Configuraiton Confirm */
   U8                   idx;           /* Index */
   KwUdxDlSapCb          *udxSap;       /* CKW SAP Control Block */
   S16                  ret;
   Bool                 ueDelWait;     /* Add present */
   KwCb                *tKwCb;

   TRC3(KwDlUdxCfgReq)

   /* DEBUG_PRINT */

   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE(RFAILED);
   }

   tKwCb = KW_GET_KWCB(pst->dstInst);

   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), 
             (tKwCb->init.prntBuf,
            "KwDlUdxCfgReq(pst, spId(%d))\n", spId));
   ret       = ROK;
   ueDelWait = FALSE;

   /* Get the ckwSap */
   udxSap = (tKwCb->u.dlCb->udxDlSap + spId);

   /* Validate SAP ID under ERRORCLS */
   KW_VALDATE_SAP(tKwCb,spId, udxSap, ret);
   if (ret != ROK)
   {
      /* kw002.201 Freeing from proper region */
      KW_PST_FREE(pst->region, pst->pool, cfg, sizeof(UdxCfgInfo));
      RETVALUE(RFAILED);
   }

   /* Allocate memory and memset to 0 for cfmInfo */
   KW_ALLOC(tKwCb,cfgCfm, sizeof(UdxCfgCfmInfo));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (cfgCfm == NULLP)
   {
      KWLOGERROR(tKwCb,ERRCLS_ADD_RES, EKW209, (ErrVal) RFAILED,
            "KwUiCkwCfgReq: cfgCfm allocation Failed.");
      /* kw002.201 Freeing from proper region */
      KW_PST_FREE(pst->region, pst->pool, cfg, sizeof(UdxCfgInfo));
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

   /* For every entity configuration process by cfgType */
   for (idx = 0; idx < cfg->numEnt; idx++)
   {
      CkwEntCfgCfmInfo  *entCfgCfm;
      CkwEntCfgInfo     *entCfg;

      entCfg  = (CkwEntCfgInfo *)&(cfg->entCfg[idx]);
      entCfgCfm   = (CkwEntCfgCfmInfo *)&(cfgCfm->entCfgCfm[idx]);

      switch (entCfg->cfgType)
      {
         case CKW_CFG_ADD:
            {
               if (entCfg->dir & KW_DIR_DL)
               { 
                  /* Add a new RB entity configuration */
                  if (kwCfgAddDlRb(tKwCb,cfg->ueId, cfg->cellId,\
                              entCfg, entCfgCfm) != ROK)
                  {
#ifdef DEBUGP
                      KWDBGP(tKwCb,
                       (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                        (tKwCb->init.prntBuf, "KwDlUdxCfgReq(pst, cfg(ueId(%d),\
                     cellId(%d), cfgType(%d), rbId(%d)) \
                     kwCfgAddRb Failed: reason (%d)\n",
                         cfg->ueId, cfg->cellId, entCfg->cfgType,
                         cfg->entCfg[idx].rbId, entCfgCfm->status.reason));
#endif
                  }
               }
               break;
            }

         case CKW_CFG_MODIFY:
            {
               if (entCfg->dir & KW_DIR_DL)
               {
                  /* Re-configure the existing RB entity configuration */
                  if (kwCfgReCfgDlRb(tKwCb,cfg->ueId, cfg->cellId,\
                           entCfg, entCfgCfm) != ROK)
                  {
#ifdef DEBUGP
                     KWDBGP(tKwCb,
                      (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                        (tKwCb->init.prntBuf, "KwUiCkwCfgReq(pst, cfg(ueId(%d),\
                     cellId(%d), cfgType(%d), rbId(%d))\n \
                     kwCfgReCfgRb Failed: reason (%d)\n",
                         cfg->ueId, cfg->cellId, entCfg->cfgType,
                         cfg->entCfg[idx].rbId, entCfgCfm->status.reason));
#endif
                   }
               }
               break;
            }

         case CKW_CFG_DELETE:
            {
               if (entCfg->dir & KW_DIR_DL)
               {
                  /* Delete the existing RB entity configuration */
                  if (kwCfgDelDlRb(tKwCb,cfg->ueId, cfg->cellId,\
                        entCfg, entCfgCfm) != ROK)
                  {
#ifdef DEBUGP
                     KWDBGP(tKwCb,
                     (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                        (tKwCb->init.prntBuf, "KwUiCkwCfgReq(pst, cfg(ueId(%d),\
                     cellId(%d), cfgType(%d), rbId(%d))\n \
                     kwCfgDelRb Failed: reason (%d)\n",
                         cfg->ueId, cfg->cellId, entCfg->cfgType,
                         cfg->entCfg[idx].rbId, entCfgCfm->status.reason));
#endif
                  } 
               }
               break;
            }

         case CKW_CFG_REESTABLISH:
            {
               if (entCfg->dir & KW_DIR_DL)
               {
                  Bool sndReEst;
                  sndReEst = TRUE;
                  if (entCfg->dir & KW_DIR_UL)
                  {
                     sndReEst = FALSE;
                  }
                  /* Re-establish the existing RB entity configuration */
                  if (kwCfgReEstDlRb(tKwCb,cfg->ueId, cfg->cellId,\
                           sndReEst,entCfg, entCfgCfm) != ROK)
                  {
#ifdef DEBUGP
                      KWDBGP(tKwCb,
                      (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                        (tKwCb->init.prntBuf, "KwUiCkwCfgReq(pst, cfg(ueId(%d),\
                        cellId(%d), cfgType(%d), rbId(%d))\
                         kwCfgReEstRb Failed: reason (%d)\n",
                          cfg->ueId, cfg->cellId, entCfg->cfgType,
                           cfg->entCfg[idx].rbId, entCfgCfm->status.reason));
#endif
                  }
               }
               break;
            }

         case CKW_CFG_DELETE_UE:
            {
               /* Delete all RB entity configuration under UE */
               if (kwCfgDelDlUe(tKwCb,cfg->ueId, cfg->cellId,\
                     entCfg, entCfgCfm) != ROK)
               {
#ifdef DEBUGP
                  KWDBGP(tKwCb,
                   (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                    (tKwCb->init.prntBuf, "KwUiCkwCfgReq(pst, cfg(ueId(%d),\
                      cellId(%d), cfgType(%d), rbId(%d))\
                    kwCfgDelUe Failed: reason (%d)\n",
                    cfg->ueId, cfg->cellId, entCfg->cfgType,
                   cfg->entCfg[idx].rbId, entCfgCfm->status.reason));
#endif
               }
               break;
            }
         case CKW_CFG_DELETE_CELL:
            {
               if (kwCfgDelDlCell(tKwCb,cfg->cellId,entCfg,entCfgCfm) 
                                                                != ROK )
               {
#ifdef DEBUGP
                  KWDBGP(tKwCb,
                        (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                        (tKwCb->init.prntBuf, "KwDlUdxCfgReq(pst, cfg(ueId(%d),\
                     cellId(%d), cfgType(%d), rbId(%d))\
                      kwCfgDelCell Failed: reason (%d)\n",
                         cfg->ueId, cfg->cellId, entCfg->cfgType,
                         cfg->entCfg[idx].rbId, entCfgCfm->status.reason));
#endif
               } 
               break;
            }

         default:
            {
               KW_CFG_FILL_CFG_CFM(entCfgCfm, entCfg->rbId, entCfg->rbType,\
                  CKW_CFG_CFM_NOK, CKW_CFG_REAS_INVALID_CFG);

#ifdef DEBUGP
               KWDBGP(tKwCb,
                     (KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
                     (tKwCb->init.prntBuf, "KwUiCkwCfgReq(pst, cfg(ueId(%d),\
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


   /* kw002.201 Freeing from proper region */
   KW_PST_FREE(pst->region, pst->pool, cfg, sizeof(UdxCfgInfo));
   /* Send Configuration confirm primitive */
   KwDlUdxCfgCfm(&(udxSap->pst), udxSap->suId, cfgCfm);

   RETVALUE(ROK);
} /* KwDlUdxCfgReq */

/**
 *@details This primitive is used by RRC to change the UeId for the existing UE
           context.

 * @param pst     -  Point to the pst structure
 * @param spId    -  The ID of the service provider SAP in the RLC layer 
 * @param transId -  Transaction ID. This field uniquily identifies
 *                   transaction between RRC and RLC
 * @param ueInfo    -  Old UE Id Info for which the change request has come 
 * @param newUeInfo -  New UE Id Info for existing UE context 
 * @return ROK
 */
#ifdef ANSI
PUBLIC S16 KwDlUdxUeIdChgReq
(
Pst *pst, 
SpId spId, 
U32 transId, 
UdxUeInfo *ueInfo,
UdxUeInfo *newUeInfo
)
#else
PUBLIC S16 KwDlUdxUeIdChgReq(pst,spId,transId,ueInfo,newUeInfo)
Pst        *pst;
SpId       spId;
U32        transId;
UdxUeInfo *ueInfo;
UdxUeInfo *newUeInfo;
#endif
{
   S16         ret;
   CmStatus    status;
   KwUdxDlSapCb  *udxSap;       /* CKW SAP Control Block */
   UdxUeInfo   *tUeInfo;
   KwCb        *tKwCb;

   TRC3(KwDlUdxUeIdChgReq)

   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE(RFAILED);
   }

   tKwCb = KW_GET_KWCB(pst->dstInst);
#ifdef DEBUGP
   /* DEBUG_PRINT */
#ifndef ALIGN_64BIT
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_BRIEF),
                (tKwCb->init.prntBuf,
            "KwDlUdxUeIdChgReq(pst, spId(%d), transId(%ld))\n", 
                  spId, transId));
#else
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_BRIEF),
         (tKwCb->init.prntBuf,
            "KwDlUdxUeIdChgReq(pst, spId(%d), transId(%d))\n", 
          spId, transId));
#endif
#endif

   ret = ROK;
   udxSap = (tKwCb->u.dlCb->udxDlSap + spId);
   status.reason = CKW_CFG_REAS_NONE;
   status.status = CKW_CFG_CFM_OK;
   
   if (kwCfgDlUeIdChng(tKwCb,(CkwUeInfo *)ueInfo,(CkwUeInfo *) newUeInfo,\
                        &status) != ROK)
   {
#ifdef DEBUGP
      KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_ERROR),
            (tKwCb->init.prntBuf, "KwDlUdxUeIdChgReq(pst, oldUe(ueId(%d),\
         cellId(%d)), newUe(ueId(%d), cellId(%d))\n kwCfgUeIdChng Failed:\
          reason (%d)\n", ueInfo->ueId, ueInfo->cellId, 
         newUeInfo->ueId, newUeInfo->cellId, status.reason));
#endif
   }

   /* Allocate memory for CkwUeInfo */
   KW_ALLOC(tKwCb,tUeInfo, sizeof(UdxUeInfo));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (tUeInfo == NULLP)
   {
      /* Free memory for CkwUeInfo */
      /* Freeing from proper region */
      KW_PST_FREE(pst->region, pst->pool, newUeInfo, sizeof(CkwUeInfo));
      KW_PST_FREE(pst->region, pst->pool, ueInfo, sizeof(CkwUeInfo));

      KWLOGERROR(tKwCb,ERRCLS_ADD_RES, EKW210, (ErrVal) RFAILED,
            "KwUiCkwUeIdChgReq: tUeInfo allocation Failed.");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

   tUeInfo->ueId = ueInfo->ueId;
   tUeInfo->cellId = ueInfo->cellId;

   /* kw002.201 Freeing from proper region */
   KW_PST_FREE(pst->region, pst->pool, newUeInfo, sizeof(UdxUeInfo));
   KW_PST_FREE(pst->region, pst->pool, ueInfo, sizeof(UdxUeInfo));

   KwDlUdxUeIdChgCfm(&(udxSap->pst), udxSap->suId, transId, tUeInfo, status);

   RETVALUE(ROK);
} /* KwUiCkwUeIdChgReq */


#ifndef ANSI
PUBLIC S16  KwDlUdxStaPduReq
(
Pst                 *pst,
SpId                spId,
CmLteRlcId          *rlcId,
KwUdxDlStaPdu       *pStaPdu
)
#else
PUBLIC S16  KwDlUdxStaPduReq(pst, spId,rlcId, pStaPdu)
Pst*                pst;
SpId                spId;
CmLteRlcId          *rlcId;
KwUdxDlStaPdu       *pStaPdu;
#endif
{
   S16              ret;
   KwDlRbCb         *rbCb;
   KwCb             *tKwCb;

   tKwCb =  KW_GET_KWCB (pst->dstInst);

   ret  = kwDbmFetchDlRbCbForUi(tKwCb, *rlcId, &rbCb); /* Fetch DBM RbCb */
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(tKwCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
               "KwUlUdxStaPduReq: kwDbmFetchRbCb Failed.\n"));
#endif
      RETVALUE(RFAILED);
   }

   if (AMDL.mBuf != NULLP)
   {
      AMDL.cntrlBo = 0;
      KW_FREE_BUF(AMDL.mBuf);
      AMDL.mBuf = NULLP;
#if (ERRCLASS & ERRCLS_INT_PAR)
      KWLOGERROR(tKwCb, ERRCLS_INT_PAR, EKW043, (ErrVal) 0,
               "KwDlUdxStaUpdReq: RLC had failed to dispatch StaPdu!");
#endif /* ERRCLASS & ERRCLS_INT_PAR */
   }

   AMDL.mBuf = pStaPdu->mBuf;
/*Pradeep - doubt, why multiply with 8*/
   /* Update Control Bo to Mac */
   AMDL.cntrlBo = pStaPdu->pduSz;
   /*Pradeep - temp commented. AMDL.cntrlBo = pStaPdu->pduSz * 8;*/

   /* TODO : No need to send sta response everytime there is sta pdu 
             Can be sent once along with dat request bo*/
   KW_AM_SND_DSTA_RSP();

   KW_FREE(tKwCb, pStaPdu, sizeof(KwUdxDlStaPdu)); 

   RETVALUE (ROK);
}
/**
* @brief Request from ULM to DLM for UE Status
*
* @details
*
*     Function : KwUdxAmmStatUpdReq 
*
*  @param[in]   Pst*           pst
*  @param[in]   KwRbCb         rbCb
*  @param[in]   KwUdxStaPdu    staPdu
*  @return   S16
*      -# ROK
**/
#ifdef ANSI
PUBLIC S16  KwDlUdxStaUpdReq
(
Pst*                pst,
SpId                spId,
CmLteRlcId          *rlcId,
KwUdxStaPdu         *pStaPdu
)
#else
PUBLIC S16 KwDlUdxStaUpdReq(pst, spId, rlcId,pStaPdu)
Pst*                pst;
SpId                spId;
CmLteRlcId          *rlcId;
KwUdxStaPdu         *pStaPdu;
#endif
{
   S16 ret = RFAILED;
   KwUdxBufLst  *rlsPduLst;
   KwCb         *tKwCb;
   KwDlRbCb     *rbCb;
   KwUdxDlSapCb *udxSap;
   Pst          *tmpPst = NULLP;

   tKwCb = KW_GET_KWCB(pst->dstInst);

   ret = kwDbmFetchDlRbCbForUi(tKwCb, *rlcId, &rbCb);
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      KWLOGERROR(tKwCb,ERRCLS_INT_PAR, EKW043, (ErrVal) 0,
               "KwDlUdxStaUpdReq: Fetch RbCb failed...!");
#endif /* ERRCLASS & ERRCLS_INT_PAR */
      RETVALUE(RFAILED);

   }

   udxSap = (tKwCb->u.dlCb->udxDlSap + spId);

   KW_ALLOC(tKwCb, rlsPduLst, sizeof(KwUdxBufLst));

   if(rlsPduLst == NULLP)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      KWLOGERROR(tKwCb,ERRCLS_INT_PAR, EKW043, (ErrVal) 0,
               "KwAmmUlmDlmStaUpdReq: SgetSBuf Failed for rlsPduLst ...!");
#endif /* ERRCLASS & ERRCLS_INT_PAR */
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }
   cmLListInit(&rlsPduLst->rlsTxLst);
   cmLListInit(&rlsPduLst->rlsRetxLst);
   cmLListInit(&rlsPduLst->rlsSduLst);


   ret = kwDlmHndlStaRsp(tKwCb, rbCb, pStaPdu, rlsPduLst);

   if (ret == ROK)
   {
      if (rlsPduLst->rlsTxLst.count > 0 || \
          rlsPduLst->rlsRetxLst.count > 0 || \
          rlsPduLst->rlsSduLst.count > 0)
      {
         tmpPst = &(udxSap->pst);
         if (ret != ROK)
         {
#if (ERRCLASS & ERRCLS_ADD_RES)
            KWLOGERROR(tKwCb,ERRCLS_ADD_RES, EKWXXX, (ErrVal)0,
            "kwHndlStaRsp: Failed to find relevant post structure\n");
#endif /* ERRCLASS & ERRCLS_RES */
            KW_FREE_BUF(rlsPduLst);
            RETVALUE(RFAILED);
         }

         KwDlUdxStaUpdCfm(tmpPst, udxSap->suId, rlcId, rlsPduLst);
      }
   }
   else
   {
      KW_FREE(tKwCb, pStaPdu, sizeof(KwUdxBufLst));
   }
   KW_FREE(tKwCb, pStaPdu, sizeof(KwUdxStaPdu));

   RETVALUE(ret);
} /* KwDlUdxStaUpdCfm */


#ifdef __cplusplus
}
#endif /* __cplusplus */


/**********************************************************************
         End of file:     kw_udx_dl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:50 2014
**********************************************************************/
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       mraj   1. LTE RLC Initial Release
*********************************************************************91*/

