

/********************************************************************20**
  
        Name:    LTE-RLC Layer - Upper Interface Functions
    
        Type:    C file
  
     Desc:     Source code for RLC Upper Interface Module
               This file contains following functions
      
        --KwUiCkwBndReq
        --KwUiCkwUbndReq
        --KwUiCkwCfgReq

        --KwUiKwuBndReq
        --KwUiKwuUbndReq
        --KwUiKwuDatReq
        --KwUiKwuDiscSduReq 

     File:     kw_uim.c

     Sid:      kw_uim.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:52 2014

     Prg:      gk 

**********************************************************************/
/** @file gp_uim.c
@brief RLC Upper Interface Module 
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
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */
#include "kw_dl.h"
#include "kw_ul.h"
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
#include "kw_err.h"
#include "kw.x"
#include "kw_dl.x"
#include "kw_ul.x"
#include "kw_udx.x"



/* Global variable */
/*****************************************************************************
 *                          CKW INTERFACE
 ****************************************************************************/
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
PUBLIC S16 KwUiCkwBndReq 
(
Pst  *pst,   /* Post structure */ 
SuId suId,   /* service user SAP ID */ 
SpId spId   /* service provider identifier */
)
#else
PUBLIC S16 KwUiCkwBndReq (pst, suId, spId)
Pst *pst;    /* Post structure */
SuId suId;    /* service user SAP ID */
SpId spId;    /* service provider identifier */
#endif
{
   KwCkwSapCb      *ckwSap;            /* pointer to session SAP */
   S16             ret;                /* return value */
   KwCb            *tKwCb;

   TRC3(KwUiCkwBndReq);

   ret = ROK;

   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE(RFAILED);
   }

   tKwCb = KW_GET_KWCB(pst->dstInst);

#ifdef DEBUGP
   /* DEBUG_PRINT */
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
            "KwUiCkwBndReq(pst, spId(%d), suId(%d))\n", spId, suId));
#endif

   ckwSap = &(tKwCb->u.ulCb->ckwSap);

   /*Pradeep - debug*/
   /*printf("\n################### Inst:%d tKwCb:%d ckwSap:%d ckwSap->state:%d\n",pst->dstInst, tKwCb, ckwSap, ckwSap->state);*/

   /* Verify CKW SAP State */
   switch(ckwSap->state)
   {
      /* SAP is configured but not bound */
      case KW_SAP_CFG:
      case KW_SAP_UBND:
      {
         /* copy bind configuration parameters in SSAP sap */
         ckwSap->suId = suId;
         ckwSap->pst.dstProcId = pst->srcProcId;
         ckwSap->pst.dstEnt = pst->srcEnt;
         ckwSap->pst.dstInst = pst->srcInst;

         /* Update the State */
         ckwSap->state = KW_SAP_BND;

#ifdef DEBUGP
         /* DEBUG_PRINT */
         KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_DETAIL), (tKwCb->init.prntBuf,
                  "KwUiCkwBndReq: state (%d)\n", ckwSap->state));
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
         if (ckwSap->pst.dstProcId != pst->srcProcId 
               || ckwSap->pst.dstEnt != pst->srcEnt
               || ckwSap->pst.dstInst != pst->srcInst
               || ckwSap->suId != suId)
         {
            KW_SEND_SAPID_ALARM(tKwCb,spId, 
                                LKW_EVENT_CKW_BND_REQ, LCM_CAUSE_INV_PAR_VAL);

#ifdef DEBUGP
            KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
                 "KwUiCkwBndReq: SAP already bound -- state(%d)\n", 
                    ckwSap->state));
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
               "KwUiCkwBndReq: CKW SAP State is Invalid during Bind Req");

         KW_SEND_SAPID_ALARM(tKwCb,spId, 
                             LKW_EVENT_CKW_BND_REQ, LCM_CAUSE_INV_STATE);
#endif /* ERRCLASS & ERRCLS_INT_PAR */

         /* DEBUG_PRINT */
#ifdef DEBUGP
         KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
                  "KwUiCkwBndReq: CKW SAP State is Invalid during Bind Req"));
#endif

         ret = RFAILED;
         break;
      }
   }

   if (ret == ROK)
   {
      KwUiCkwBndCfm(&(ckwSap->pst), ckwSap->suId, CM_BND_OK);
   }
   else
   {
      KwUiCkwBndCfm(&(ckwSap->pst), ckwSap->suId, CM_BND_NOK);
   }

   RETVALUE(ROK);
} /* KwUiCkwBndReq */


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
PUBLIC S16 KwUiCkwUbndReq
(
Pst      *pst,         /* Post structure */
SpId     spId,       /* service provider identifier */
Reason   reason      /* Reason for Unbinding */
)
#else
PUBLIC S16 KwUiCkwUbndReq(pst, spId, reason)
Pst      *pst;       /* Post structure */
SpId     spId;       /* service provider identifier */
Reason   reason;       /* Reason for Unbinding */
#endif
{
   KwCkwSapCb  *ckwSap;            /* CKW SAP control block */
   KwCb        *tKwCb;

   TRC3(KwUiCkwUbndReq)

   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE(RFAILED);
   }
   tKwCb = KW_GET_KWCB(pst->dstInst);

#ifdef DEBUGP
   /* DEBUG_PRINT */
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
            "KwUiCkwUbndReq(pst, spId(%d), reason(%d))\n", spId, reason));
#endif

   UNUSED(reason);

   /* disable upper sap (CKW) */
   ckwSap = &(tKwCb->u.ulCb->ckwSap);

#if (ERRCLASS & ERRCLS_INT_PAR)
   KW_GET_AND_VALIDATE_CKWSAP(tKwCb,ckwSap, EKW208, "KwUiCkwUbndReq");
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   ckwSap->state = KW_SAP_CFG;

   RETVALUE(ROK);
} /* KwUiCkwUbndReq */


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
PUBLIC S16 KwUiCkwCfgReq
(
Pst         *pst,
SpId        spId,
CkwCfgInfo  *cfg
)
#else
PUBLIC S16 KwUiCkwCfgReq(pst, spId, cfg)
Pst         *pst;
SpId        spId;
CkwCfgInfo  *cfg;
#endif
{
   KwCkwSapCb           *ckwSap;       /* CKW SAP Control Block */
   KwUdxUlSapCb         *udxSap;       /* CKW SAP Control Block */
   S16                  ret;
   KwCb                *tKwCb;
   KwCfgInfo   *cfgInfo;
   UdxCfgInfo  *udxCfg;

   TRC3(KwUiCkwCfgReq)

   /* DEBUG_PRINT */

   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE(RFAILED);
   }

   tKwCb = KW_GET_KWCB(pst->dstInst);

   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), 
             (tKwCb->init.prntBuf,
            "KwUiCkwCfgReq(pst, spId(%d))\n", spId));
   ret       = ROK;

   /* Get the ckwSap */
   ckwSap = &(tKwCb->u.ulCb->ckwSap);

   /* Validate SAP ID under ERRORCLS */
   KW_VALDATE_SAP(tKwCb,spId, ckwSap, ret);
   if (ret != ROK)
   {
      /* kw002.201 Freeing from proper region */
      KW_PST_FREE(pst->region, pst->pool, cfg, sizeof(CkwCfgInfo));
      RETVALUE(RFAILED);
   }

   KW_ALLOC(tKwCb, udxCfg, sizeof (UdxCfgInfo));
   if (udxCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   KW_MEM_CPY(udxCfg,cfg,sizeof(UdxCfgInfo));
   KW_ALLOC(tKwCb, cfgInfo, sizeof (KwCfgInfo));

   if (cfgInfo == NULLP)
   {
      RETVALUE(RFAILED);
   }

   cfgInfo->transId = cfg->transId;
   cfgInfo->cfgInfo  = cfg;
 
   ret = kwDbmAddUlTransIdLst(tKwCb, cfgInfo);
   if (ret != ROK)
   {
      KWLOGERROR(tKwCb,ERRCLS_ADD_RES, EKW210, (ErrVal) RFAILED,
            "KwUiCkwUeIdChgReq: Addition to transId Lst Failed.");
      RETVALUE(RFAILED);
   }

   udxSap = KW_GET_UDX_SAP(tKwCb);
   
   KwUlUdxCfgReq(&(udxSap->pst), udxSap->spId,udxCfg); 

   RETVALUE(ROK);
} /* KwUiCkwCfgReq */

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
PUBLIC S16 KwUiCkwUeIdChgReq
(
Pst *pst, 
SpId spId, 
U32 transId, 
CkwUeInfo *ueInfo,
CkwUeInfo *newUeInfo
)
#else
PUBLIC S16 KwUiCkwUeIdChgReq(pst,spId,transId,ueInfo,newUeInfo)
Pst        *pst;
SpId       spId;
U32        transId;
CkwUeInfo *ueInfo;
CkwUeInfo *newUeInfo;
#endif
{
   S16         ret;
   KwUdxUlSapCb  *udxSap;       /* CKW SAP Control Block */
   UdxUeInfo   *udUeInfo;
   UdxUeInfo   *udNewUeInfo;
   KwCb        *tKwCb;
   KwCfgInfo   *cfgInfo;

   TRC3(KwUiCkwUeIdChgReq)

   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE(RFAILED);
   }

   tKwCb = KW_GET_KWCB(pst->dstInst);
#ifdef DEBUGP
   /* DEBUG_PRINT */
#ifndef ALIGN_64BIT
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
            "KwUiCkwUeIdChgReq(pst, spId(%d), transId(%ld))\n", spId, transId));
#else
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
            "KwUiCkwUeIdChgReq(pst, spId(%d), transId(%d))\n", spId, transId));
#endif
#endif

   ret = ROK;

   /* Allocate memory for CkwUeInfo */
   KW_ALLOC(tKwCb,udUeInfo, sizeof(UdxUeInfo));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (udUeInfo == NULLP)
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
   /* Allocate memory for CkwUeInfo */
   KW_ALLOC(tKwCb,udNewUeInfo, sizeof(UdxUeInfo));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (udNewUeInfo == NULLP)
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

   KW_MEM_CPY(udUeInfo,ueInfo, sizeof(UdxUeInfo));
   KW_MEM_CPY(udNewUeInfo,newUeInfo, sizeof (UdxUeInfo));

   KW_ALLOC(tKwCb, cfgInfo, sizeof (KwCfgInfo));
   if (cfgInfo == NULLP)
   {
      KW_FREE(tKwCb,udUeInfo, sizeof(UdxUeInfo));
      KW_FREE(tKwCb,udNewUeInfo, sizeof(UdxUeInfo));
      KW_PST_FREE(pst->region, pst->pool, newUeInfo, sizeof(CkwUeInfo));
      KW_PST_FREE(pst->region, pst->pool, ueInfo, sizeof(CkwUeInfo));
      RETVALUE(RFAILED);
   }

   cfgInfo->transId = transId;
   cfgInfo->ueInfo  = ueInfo;
   cfgInfo->newUeInfo  = newUeInfo; 

   ret = kwDbmAddUlTransIdLst(tKwCb, cfgInfo);
   if (ret != ROK)
   {
      KW_FREE(tKwCb,udUeInfo, sizeof(UdxUeInfo));
      KW_FREE(tKwCb,udNewUeInfo, sizeof(UdxUeInfo));
      KWLOGERROR(tKwCb,ERRCLS_ADD_RES, EKW210, (ErrVal) RFAILED,
            "KwUiCkwUeIdChgReq: Addition to transId Lst Failed.");
      RETVALUE(RFAILED);
   }

   udxSap = KW_GET_UDX_SAP(tKwCb);
   
   KwUlUdxUeIdChgReq(&(udxSap->pst),udxSap->spId,transId,
                                         udUeInfo,udNewUeInfo);

   RETVALUE(ROK);
} /* KwUiCkwUeIdChgReq */


/*****************************************************************************
 *                          KWU INTERFACE
 ****************************************************************************/
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
 *        RLC.This function is called by the KWU interfacei to bind 
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
PUBLIC S16 KwUiKwuBndReq 
(
Pst  *pst,   /* Post structure */ 
SuId suId,   /* service user SAP ID */ 
SpId spId   /* service provider identifier */
)
#else
PUBLIC S16 KwUiKwuBndReq (pst, suId, spId)
Pst *pst;    /* Post structure */
SuId suId;    /* service user SAP ID */
SpId spId;    /* service provider identifier */
#endif
{
   S16                  ret;           /* Return Value */
   KwKwuSapCb           *kwuSap;       /* SAP Config Block */
   KwCb        *tKwCb;
   
   TRC3(KwUiKwuBndReq)

   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE(RFAILED);
   }

   tKwCb = KW_GET_KWCB(pst->dstInst);

   /* DEBUG_PRINT */
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
            "KwUiKwuBndReq(pst, spId(%d), suId(%d))\n", spId, suId));

   ret = ROK;
   kwuSap = NULLP;

    /* Validation of input parameters */
#if (ERRCLASS & ERRCLS_INT_PAR)
   if(!((spId < (S16) tKwCb->genCfg.maxKwuSaps) && (spId >=0))) 
   {
      KWLOGERROR(tKwCb,ERRCLS_INT_PAR, EKW211, (ErrVal) spId,
            "KwUiKwuBndReq: KWU SAP State is Invalid during Bind Req");

      KW_SEND_SAPID_ALARM(tKwCb,spId, LKW_EVENT_KWU_BND_REQ, LCM_CAUSE_INV_SAP);

      RETVALUE(RFAILED); 
   }
#endif

   /* Get Sap control block */
   kwuSap = (tKwCb->genCfg.rlcMode == LKW_RLC_MODE_DL) ?
            (tKwCb->u.dlCb->kwuDlSap + spId):
            (tKwCb->u.ulCb->kwuUlSap + spId);

  /* Verify KWU SAP State */
   switch(kwuSap->state)
   {
      /* SAP is configured but not bound */
      case KW_SAP_CFG:
      case KW_SAP_UBND:
      {
         /* copy bind configuration parameters in SSAP sap */
         kwuSap->suId          = suId;
         kwuSap->pst.dstProcId = pst->srcProcId;
         kwuSap->pst.dstEnt    = pst->srcEnt;
         kwuSap->pst.dstInst   = pst->srcInst;

         /* Update the State */
         kwuSap->state = KW_SAP_BND;

         /* DEBUG_PRINT */
         KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_DETAIL), (tKwCb->init.prntBuf,
                  "KwUiKwuBndReq: state (%d)\n", kwuSap->state));
         break;
      }

      /* SAP is already bound */
      case KW_SAP_BND:
      {
         /* 
          * Sap is already bound check source, destination Entity and 
          * Proc Id
          */
         if (kwuSap->pst.dstProcId != pst->srcProcId 
               || kwuSap->pst.dstEnt != pst->srcEnt
               || kwuSap->pst.dstInst != pst->srcInst
               || kwuSap->suId != suId)
         {
            KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
                     "KwUiKwuBndReq(pst, suId(%d)<>suId(%d),\n\
               pst->srcProcId(%d)<>kwuSap->pst.dstProcId(%d),\n\
                     pst->srcEnt(%d)<>kwuSap->pst.dstEnt(%d),\n\
                     pst->srcInst(%d)<>kwuSap->pst.dstInst(%d))\n",\
                  suId, kwuSap->suId, pst->srcProcId, kwuSap->pst.dstProcId,\
                  pst->srcEnt, kwuSap->pst.dstEnt, pst->srcInst,\
                  kwuSap->pst.dstInst));

            KW_SEND_SAPID_ALARM(tKwCb,spId, LKW_EVENT_KWU_BND_REQ, LCM_CAUSE_INV_PAR_VAL);
            ret = RFAILED;
         }
         break;
      }

     default:
      {
#if (ERRCLASS & ERRCLS_INT_PAR)
         /* LOG ERROR */
         KWLOGERROR(tKwCb,ERRCLS_INT_PAR, EKW212, (ErrVal) spId,
               "KwUiKwuBndReq: KWU SAP State is Invalid during Bind Req");

         KW_SEND_SAPID_ALARM(tKwCb,spId,
                             LKW_EVENT_KWU_BND_REQ, LCM_CAUSE_INV_STATE);
#endif /* ERRCLASS & ERRCLS_INT_PAR */

         KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
                  "KwUiKwuBndReq: KWU SAP State is Invalid during Bind Req"));

         ret = RFAILED;
         break;
      }
   }

   if (ret == ROK)
   {
      KwUiKwuBndCfm(&(kwuSap->pst), kwuSap->suId, CM_BND_OK);
   }
   else
   {
      KwUiKwuBndCfm(&(kwuSap->pst), kwuSap->suId, CM_BND_NOK);
   }

   RETVALUE(ROK);

} /* KwUiKwuBndReq */


/**
 *
 * @brief 
 *
 *        Handler for unbinding the RLC upper layer service user with 
 *        the RLC layer.
 *
 * @b Description:
 *
 *        This function is used by RLC user to request for unbinding  
 *        with RLC.This function is called by the KWU interface to 
 *        unbind with RLC. 
 *
 *  @param[in] pst     Post structure  
 *  @param[in] suId    Service user SAP ID 
 *  @param[in] reason  Reason for Unbinding 
 *
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 KwUiKwuUbndReq
(
Pst      *pst,       /* Post structure */
SpId     spId,       /* service provider identifier */
Reason   reason      /* Reason for Unbinding */
)
#else
PUBLIC S16 KwUiKwuUbndReq(pst, spId, reason)
Pst      *pst;       /* Post structure */
SpId     spId;       /* service provider identifier */
Reason   reason;       /* Reason for Unbinding */
#endif
{
   KwKwuSapCb  *kwuSap;            /* CKW SAP control block */
   KwCb        *tKwCb;

   TRC3(KwUiKwuUbndReq)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE (RFAILED);
   }
#endif

   tKwCb = KW_GET_KWCB(pst->dstInst);


   /* DEBUG_PRINT */
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
            "KwUiKwuUbndReq(pst, spId(%d), reason(%d))\n", spId, reason));

   kwuSap = NULLP;


   /* Get Sap control block */
   kwuSap = (tKwCb->genCfg.rlcMode == LKW_RLC_MODE_DL) ?
            (KwKwuSapCb*)(tKwCb->u.dlCb + spId):
            (KwKwuSapCb*)(tKwCb->u.ulCb + spId);

   kwuSap->state = KW_SAP_CFG;

   RETVALUE(ROK);
} /* KwUiKwuUbndReq */

/**
 *
 * @brief 
 *
 *        Handler for receiving the data(SDU) from upper layer. 
 *
 * @b Description:
 *
 *        This function is used by RLC service user (PDCP/RRC) to 
 *        transfer data (SDU) to RLC.
 *
 *  @param[in] pst           Post structure  
 *  @param[in] spId        Service Provider SAP ID 
 *  @param[in] datreqInfo  Data Request Information
 *  @param[in] mBuf      Data Buffer (SDU) 
 *
 *  @return  S16
 *      -# ROK 
 *   -# RFAILED
 */
#ifdef ANSI
PUBLIC S16 KwUiKwuDatReq
(
Pst            *pst,            /* Post structure */
SpId           spId,          /* Service Provider SAP ID */   
KwuDatReqInfo  *datReq,       /* Data Request Information */
Buffer         *mBuf            /* Data Buffer (SDU) */
)
#else
PUBLIC S16 KwUiKwuDatReq(pst, spId, datReq, mBuf)
Pst            *pst;          /* Post structure */
SpId           spId;          /* Service Provider SAP ID */ 
KwuDatReqInfo  *datReq;       /* Data Request Information */
Buffer         *mBuf;          /* Data Buffer (SDU) */
#endif
{
   S16         ret;           /* Return Value */
   KwDlRbCb      *rbCb;         /* RB Control Block */
   KwKwuSapCb  *kwuSap;       /* SAP Config Block */
   KwCb        *tKwCb;

   TRC3(KwUiKwuDatReq)

   ret = ROK;
   rbCb = NULLP;
   kwuSap = NULLP;

   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE(RFAILED);
   }

   tKwCb = KW_GET_KWCB(pst->dstInst);

   /* DEBUG_PRINT */
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
            "KwUiKwuDatReq(pst, spId(%d))\n", spId));

   /* Get Sap control block */
   kwuSap = (KwKwuSapCb*)(tKwCb->u.dlCb->kwuDlSap + spId);

   /* Validate SAP ID under ERRORCLS */
   KW_VALDATE_SAP(tKwCb,spId, kwuSap, ret);
   if (ret != ROK)
   {
      /* kw002.201 Freeing from proper region */
      KW_PST_FREE(pst->region, pst->pool, datReq, sizeof(KwuDatReqInfo));
      KW_FREE_BUF(mBuf);
      RETVALUE(RFAILED);
   }

   /* Fetch the RbCb */
   if (kwDbmFetchDlRbCbForUi(tKwCb,datReq->rlcId, &rbCb) != ROK)
   {
      KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
               "KwUiKwuDatReq: RLCID not found ueId(%d), cellId(%d), rbId(%d)",
            datReq->rlcId.ueId, datReq->rlcId.cellId, datReq->rlcId.rbId));
      /* kw002.201 Freeing from proper region */
      KW_PST_FREE(pst->region, pst->pool, datReq, sizeof(KwuDatReqInfo));
      KW_FREE_BUF(mBuf);

      RETVALUE(RFAILED);
   }

   /* kw005.201 update the spId received in datReq to update statistics */
   rbCb->kwuSapId = spId;
   /* Dispatch according to mode of the rbCb */
   switch (rbCb->mode)
   {
      case CM_LTE_MODE_TM:
         {
            /* Verify the mode and user */
            if ( (rbCb->mode == CM_LTE_MODE_TM) && (pst->srcEnt != ENTNH) )
            {
               /* kw002.201 Freeing from proper region */
               KW_PST_FREE(pst->region, pst->pool, datReq, 
                           sizeof(KwuDatReqInfo));
               KW_FREE_BUF(mBuf);
                
               RETVALUE(RFAILED);
            }

            ret = kwTmmQSdu(tKwCb,rbCb, datReq, mBuf);
            if ( ret != ROK )
            {
               KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
                        "KwUiKwuDatReq: kwTmmQSdu failed ueId(%d), cellId(%d), rbId(%d)",
                        datReq->rlcId.ueId, datReq->rlcId.cellId, datReq->rlcId.rbId));
            }
            /* kw005.201 ccpu00117318, updated statistics */
            kwuSap->sts.sduRx++;
            break;
         }
      case CM_LTE_MODE_UM:
         {
            ret = kwUmmQSdu(tKwCb,rbCb, datReq->sduId, mBuf);
            if ( ret != ROK )
            {
               KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
                        "KwUiKwuDatReq: kwUmmQSdu failed ueId(%d), cellId(%d), rbId(%d)",
                        datReq->rlcId.ueId, datReq->rlcId.cellId, datReq->rlcId.rbId));
            }
            /* kw005.201 ccpu00117318, updated statistics */
            kwuSap->sts.sduRx++;
            /* Freeing from the proper region */
            /* KW_FREE(datReq, sizeof(KwuDatReqInfo)); */
            break;
         }
      case CM_LTE_MODE_AM:
         {
#ifdef PRADEEP_DBG		 
printf("\nRLC Pradeep: Received ueId[%d] rbId[%d] sduId[%d] pdu[%x]############\n",datReq->rlcId.ueId,datReq->rlcId.rbId,datReq->sduId,mBuf);
#endif
            ret = kwAmmQSdu(tKwCb,rbCb, mBuf, datReq->sduId);
            if ( ret != ROK )
            {
               KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
                        "KwUiKwuDatReq: kwAmmQSdu failed ueId(%d), cellId(%d), rbId(%d)",
                        datReq->rlcId.ueId, datReq->rlcId.cellId, datReq->rlcId.rbId));
            }
            /* kw005.201 ccpu00117318, updated statistics */
            kwuSap->sts.sduRx++;
            /* Freeing from the proper region */
            /* KW_FREE(datReq, sizeof(KwuDatReqInfo)); */
            break;
         }
      default:
         {
            KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
            "KwUiKwuDatReq: wrong mode ueId(%d), cellId(%d), rbId(%d) mode(%d)",
            datReq->rlcId.ueId, datReq->rlcId.cellId, datReq->rlcId.rbId, rbCb->mode));
            break;
         }
   }
   /* kw002.201 Freeing from proper region */
   KW_PST_FREE(pst->region, pst->pool, datReq, sizeof(KwuDatReqInfo));

   RETVALUE(ret);
} /* KwUiKwuDatReq */


/**
 *
 * @brief 
 *
 *        Handler for discarding a SDU. 
 *
 * @b Description:
 *
 *        This function is used by RLC AM  and RLC UM entities.It send status 
 *        This function is called by the service user to discard a particular
 *        RLC SDU if it is present in the SDU queue of the RB control block 
 *        and if it is not mapped to any PDU. 
 *
 *  @param[in] pst            Post structure  
 *  @param[in] spId           Service Provider SAP ID 
 *  @param[in] discSduInfo    SDU discard Information 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 */
#ifdef ANSI
PUBLIC S16 KwUiKwuDiscSduReq 
(
Pst                *pst,            /* Post structure */ 
SpId                spId,            /* Service Provider ID */ 
KwuDiscSduInfo    *discSdu       /* SDU discard Information */      
)
#else
PUBLIC S16 KwUiKwuDiscSduReq(pst, spId, discSdu)
Pst               *pst;           /* Post structure */
SpId              spId;           /* Service Provider ID */ 
KwuDiscSduInfo    *discSdu;       /* SDU discard Information */           
#endif
{
   S16         ret;              /* Return Value */
   KwDlRbCb      *rbCb;            /* RB Control Block */
   KwKwuSapCb  *kwuSap;       /* SAP Config Block */
   KwCb        *tKwCb;

   TRC3(KwUiKwuDiscSduReq)

   ret = ROK;
   rbCb = NULLP;
   kwuSap = NULLP;

   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE(RFAILED);
   }

   tKwCb = KW_GET_KWCB(pst->dstInst);


   /* DEBUG_PRINT */
   KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
            "KwUiKwuDiscSduReq(pst, spId(%d))\n", spId));

   /* Get Sap control block */
   kwuSap = (KwKwuSapCb*)(tKwCb->u.dlCb->kwuDlSap + spId);

   /* Validate SAP ID under ERRORCLS */
   KW_VALDATE_SAP(tKwCb,spId, kwuSap, ret);
   if (ret != ROK)
   {
      /* kw002.201 Freeing from proper region */
      KW_PST_FREE(pst->region, pst->pool, discSdu, sizeof(KwuDiscSduInfo));
      RETVALUE(RFAILED);
   }

   /* Fetch the rbCb */
   if (kwDbmFetchDlRbCbForUi(tKwCb,discSdu->rlcId, &rbCb) != ROK)
   {
      KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
               "KwUiKwuDiscSduReq: RLCID not found ueId(%d), cellId(%d), rbId(%d)",
            discSdu->rlcId.ueId, discSdu->rlcId.cellId, discSdu->rlcId.rbId));

      /* kw002.201 Freeing from proper region */
      KW_PST_FREE(pst->region, pst->pool, discSdu, sizeof(KwuDiscSduInfo));
      RETVALUE(RFAILED);
   }

   /* DIspatch according to mode */
   switch (rbCb->mode)
   {
      case CM_LTE_MODE_UM:
         {
            ret = kwUmmDiscSdu(tKwCb,rbCb, discSdu->sduId);
            if ( ret != ROK )
            {
               KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
                "KwUiKwuDiscSduReq: kwUmmDiscSdu failed ueId(%d), cellId(%d), rbId(%d)",
                discSdu->rlcId.ueId, discSdu->rlcId.cellId, discSdu->rlcId.rbId));
            }
            break;
         }
      case CM_LTE_MODE_AM:
         {
            ret = kwAmmDiscSdu(tKwCb,rbCb, discSdu->sduId);
            if ( ret != ROK )
            {
               KWDBGP(tKwCb,(KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
                "KwUiKwuDiscSduReq: kwAmmDiscSdu failed ueId(%d), cellId(%d), rbId(%d)",
                discSdu->rlcId.ueId, discSdu->rlcId.cellId, discSdu->rlcId.rbId));
            }
            break;
         }
      case CM_LTE_MODE_TM:
      default:
         {
            KWDBGP(tKwCb, (KW_DBGMASK_INF | KW_DBGMASK_ERROR), (tKwCb->init.prntBuf,
             "KwUiKwuDiscSduReq: mode wrong ueId(%d), cellId(%d), rbId(%d), mode(%d)",
             discSdu->rlcId.ueId, discSdu->rlcId.cellId, discSdu->rlcId.rbId, rbCb->mode));
            break;
         }
   }
   /* Freeing from proper region */
   KW_PST_FREE(pst->region, pst->pool, discSdu, sizeof(KwuDiscSduInfo));

   RETVALUE(ret);
} /* KwUiKwuDiscSduReq */


/********************************************************************30**
         End of file:     kw_uim.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:52 2014
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
/main/4      kw004.201 av   1. Adding of missing trace
/main/5      kw005.201 ap   1. Updated for statistics.
*********************************************************************91*/

