

/********************************************************************20**

        Name:    LTE - RLC - Layer Manager file

        Type:    C source file

        Desc:    It contains the following common  functions for processing
                 the all the external interfaces.
                    -- KwMiLkwCfgReq
                    -- KwMiLkwCfgCfm 
                    -- KwMiLkwCntrlReq
                    -- KwMiLkwCntrlCfm
                    -- KwMiLkwStaReq
                    -- KwMiLkwStaCfm
                    -- KwMiLkwStaInd
                    -- KwMiLkwStsReq
                    -- KwMiLkwStsCfm
                    -- KwMiLkwTrcInd 

        File:     gp_lmm.c

        Sid:      kw_lmm.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:48 2014

        Prg:     cp 

*********************************************************************21*/
/** @file gp_lmm.c
@brief RLC Layer Manager Module
**/


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
#include "kw_err.h"        /* Err defines */
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

#include "kw.x"
#include "kw_udx.x"
#include "kw_dl.x"
#include "kw_ul.x"


/*********************************************************************
 *             Forward Declaration of LKW Porting Functions
 ********************************************************************/
PUBLIC KwCb *kwCb[KW_MAX_RLC_INSTANCES];
EXTERN S16 kwActvTmr ARGS ((Ent ent, Inst inst));

PRIVATE S16 kwLmmSendCfm ARGS ((KwCb *gCb,Pst *pst,KwMngmt *cfm,U8 type,Header *hdr));
PRIVATE S16 kwLmmGenCfg ARGS ((KwCb *gCb, KwGenCfg *cfg));
PRIVATE S16 kwLmmCfgKwuSap ARGS ((KwCb *gCb,KwSapCfg *cfg));
PRIVATE S16 kwLmmCfgUdxSap ARGS ((KwCb *gCb,KwSapCfg *cfg));
PRIVATE S16 kwLmmCfgCkwSap ARGS ((KwCb *gCb,KwSapCfg   *cfg));
PRIVATE S16 kwLmmCfgRguSap ARGS ((KwCb *gCb,KwSapCfg   *cfg));
PRIVATE S16 kwLmmGenCntrl ARGS ((KwCb *gCb,KwMngmt *cntrl));
PRIVATE S16 kwLmmUdxSapCntrl ARGS ((KwCb *gCb,KwMngmt *cntrl));
PRIVATE S16 kwLmmLSapCntrl ARGS ((KwCb *gCb,KwMngmt *cntrl));
PRIVATE S16 kwLmmFormLmCfm ARGS ((KwCb *gCb,Pst *pst, 
                               Header *hdr, Reason reason));
PRIVATE S16 kwLmmGetKwuSapSta ARGS ((KwCb *gCb,KwKwuSapSta *sta));
PRIVATE S16 kwLmmGetRguSapSta ARGS ((KwCb *gCb,KwRguSapSta *sta));
PRIVATE S16 kwLmmGetCkwCntSapSta ARGS ((KwCb *gCb,KwCkwCntSapSta *sta));
PRIVATE S16 kwLmmGetGenSts ARGS ((KwCb *gCb,KwGenSts *sts,Action action));
PRIVATE S16 kwLmmGetSapSts ARGS ((KwCb *gCb,KwMngmt *sts,Elmnt elmnt,Action action));


/*********************************************************************
 *             Primitives for RGU interface 
 ********************************************************************/
/**
 * @brief
      Stores the general RLC configuration. It calculates the
      memory requirement and reserves it. It also initializes the
      control blocks, the hash lists and registers the timers. In
      case of error it rolls back and reports error in the confirm.
      If the general configuration is already done it is treated as
      reconfiguration, but right now reconfiguration is not supported.
 
 *  @param[in] cfm         RLC LM general config structure
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL 
 *      -# Failure : LCM_REASON_MEM_NOAVAIL
 *                   LCM_REASON_REGTMR_FAIL
 *                   LCM_REASON_INVALID_PAR_VAL
 *                   LCM_REASON_HASHING_FAILED
 */
#ifdef ANSI
PRIVATE S16 kwLmmGenCfg
(
KwCb        *gCb,
KwGenCfg    *cfg
)
#else
PRIVATE S16 kwLmmGenCfg(gCB,cfg)
KwCb        *gCb;
KwGenCfg    *cfg;
#endif
{
   Size       kwMemSize;
   Size       kwSapSize;
   Size       kwUdxSapSize;
   S16        ret;
   CmTqCp     *kwTqCp;
   U8         cnt;

   TRC2(kwLmmGenCfg)

   if((cfg->maxUe > KW_MAX_UE) || (cfg->maxKwuSaps > KW_MAX_KWUSAPS) ||
       (cfg->maxUdxSaps > KW_MAX_UDXSAPS))
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW042, (ErrVal) cfg->maxUe,
               "kwLmmGenCfg: Invalid maxUe ");

#endif /* ERRCLASS & ERRCLS_INT_PAR */

      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }
   if ((cfg->rlcMode != LKW_RLC_MODE_DL) &&
       (cfg->rlcMode != LKW_RLC_MODE_UL))
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW042, (ErrVal) cfg->rlcMode,
               "kwLmmGenCfg: Invalid rlcMode ");

#endif /* ERRCLASS & ERRCLS_INT_PAR */

      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if(gCb->init.cfgDone == TRUE)
   {
      /* reconfiguration not supported */
      RETVALUE(LCM_REASON_RECONFIG_FAIL);
   }

   KW_MEM_CPY(&(gCb->genCfg), cfg, sizeof(KwGenCfg));

   /* Timer Queue Control point initialization */
   kwTqCp         = &(gCb->kwTqCp);
   kwTqCp->tmrLen = KW_TMR_LEN;
   kwTqCp->nxtEnt = 0;

   /* calculate the memory requirements */
   /* Size of kwuSaps */
   kwMemSize = ((Size) gCb->genCfg.maxKwuSaps * \
                    (Size)SBUFSIZE((Size)sizeof(KwKwuSapCb)) );

   kwMemSize = ((Size) gCb->genCfg.maxUdxSaps * \
                    (Size)SBUFSIZE((Size)sizeof(KwUdxUlSapCb)) );
   /* Ue Hash List Size */
   kwMemSize = kwMemSize + \
               (Size)SBUFSIZE(KW_UE_LIST_BUCKET_SIZE * sizeof(CmListEnt));
   /* Cell Hash List Size */
   kwMemSize = kwMemSize + (Size)SBUFSIZE(KW_CELL_LIST_BUCKET_SIZE * \
                             sizeof(CmListEnt));

   /* Reserve the memory */
   if(SGetSMem(KW_GET_MEM_REGION(gCb), kwMemSize,
              KW_GET_MEM_POOL_ADDRESS(gCb)) != ROK)
   {
      RETVALUE(LCM_REASON_MEM_NOAVAIL);
   }

   if(gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
   {
      KW_ALLOC(gCb,gCb->u.dlCb, sizeof (KwDlCb));
      if (gCb->u.dlCb == NULLP)
      {
         (Void) SPutSMem(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
      
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW043, (ErrVal) cfg->rlcMode,
                    "kwLmmGenCfg: SgetSBuf Failed for rlcMode...!");
         RETVALUE(LCM_REASON_MEM_NOAVAIL);
      
      }
      /* allocate memory to the KWU sap's */
      kwSapSize = (Size)((Size) gCb->genCfg.maxKwuSaps *
                   (Size)sizeof(KwKwuSapCb));

      KW_ALLOC(gCb,gCb->u.dlCb->kwuDlSap, kwSapSize);

#if (ERRCLASS & ERRCLS_INT_PAR)
      if(gCb->u.dlCb->kwuDlSap == NULLP)
      {
         KW_FREE(gCb,gCb->u.dlCb, sizeof (KwDlCb));
         (Void) SPutSMem(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
      
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW043, (ErrVal) cfg->maxUe,
                   "kwLmmGenCfg: SgetSBuf Failed for kwuSap...!");
         RETVALUE(LCM_REASON_MEM_NOAVAIL);
      }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

      kwUdxSapSize = (Size)((Size) gCb->genCfg.maxUdxSaps *
                   (Size)sizeof(KwUdxDlSapCb));

      KW_ALLOC(gCb,gCb->u.dlCb->udxDlSap, kwUdxSapSize);
#if (ERRCLASS & ERRCLS_INT_PAR)
      if(gCb->u.dlCb->udxDlSap == NULLP)
      {
         KW_FREE(gCb,gCb->u.dlCb->kwuDlSap, kwSapSize);
         KW_FREE(gCb,gCb->u.dlCb, sizeof (KwDlCb));
         (Void) SPutSMem(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
      
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW043, (ErrVal) cfg->maxUe,
                   "kwLmmGenCfg: SgetSBuf Failed for kwuSap...!");
         RETVALUE(LCM_REASON_MEM_NOAVAIL);
      }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

      
      /* Initialize the Ue and Cell hash list */
      ret = kwDbmDlInit(gCb);
      if (ret != ROK)
      {
          KW_FREE(gCb,gCb->u.dlCb->udxDlSap, kwSapSize);
          KW_FREE(gCb,gCb->u.dlCb->kwuDlSap, kwSapSize);
          KW_FREE(gCb,gCb->u.dlCb, sizeof (KwDlCb));
         (Void) SPutSMem(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
      
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW043, (ErrVal) cfg->maxUe,
                   "kwLmmGenCfg: SgetSBuf Failed for kwuSap...!");
         RETVALUE(LCM_REASON_MEM_NOAVAIL);
         RETVALUE(LCM_REASON_HASHING_FAILED);
      }
      /* Register the timer */
/*Pradeep: changing the SRegTmrMt() to SRegTmr()*/
      if(SRegTmrMt(gCb->init.ent, gCb->init.inst, (U16)cfg->timeRes,
              kwActvTmr) != ROK)
#if 0
      if(SRegTmr(gCb->init.ent, gCb->init.inst, (U16)cfg->timeRes,
              kwActvTmr) != ROK)
#endif
      {
         KW_FREE(gCb,gCb->u.dlCb->udxDlSap, kwUdxSapSize);
         KW_FREE(gCb,gCb->u.dlCb->kwuDlSap, kwSapSize);
         KW_FREE(gCb,gCb->u.dlCb, sizeof (KwDlCb));
         (Void) SPutSMem(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));

         RETVALUE(LCM_REASON_REGTMR_FAIL);
      }
   }
   else
   {
      KW_ALLOC(gCb,gCb->u.ulCb, sizeof (KwUlCb));
      if (gCb->u.ulCb == NULLP)
      {
         (Void) SPutSMem(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
      
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW043, (ErrVal) cfg->rlcMode,
                    "kwLmmGenCfg: SgetSBuf Failed for rlcMode...!");
         RETVALUE(LCM_REASON_MEM_NOAVAIL);
      
      }
      /* allocate memory to the KWU sap's */
      kwSapSize = (Size)((Size) gCb->genCfg.maxKwuSaps *
                   (Size)sizeof(KwKwuSapCb));

      KW_ALLOC(gCb,gCb->u.ulCb->kwuUlSap, kwSapSize);

#if (ERRCLASS & ERRCLS_INT_PAR)
      if(gCb->u.ulCb->kwuUlSap == NULLP)
      {
         KW_FREE(gCb,gCb->u.ulCb, sizeof (KwUlCb));
         (Void) SPutSMem(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
      
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW043, (ErrVal) cfg->maxUe,
                   "kwLmmGenCfg: SgetSBuf Failed for kwuSap...!");
         RETVALUE(LCM_REASON_MEM_NOAVAIL);
      }
#endif /* ERRCLASS & ERRCLS_INT_PAR */
      /* allocate memory to the KWU sap's */
      kwUdxSapSize = (Size)((Size) gCb->genCfg.maxUdxSaps *
                   (Size)sizeof(KwUdxUlSapCb));

      KW_ALLOC(gCb,gCb->u.ulCb->udxUlSap, kwUdxSapSize);

#if (ERRCLASS & ERRCLS_INT_PAR)
      if(gCb->u.ulCb->kwuUlSap == NULLP)
      {
         KW_FREE(gCb,gCb->u.ulCb->kwuUlSap, kwSapSize);
         KW_FREE(gCb,gCb->u.ulCb, sizeof (KwUlCb));
         (Void) SPutSMem(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
      
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW043, (ErrVal) cfg->maxUe,
                   "kwLmmGenCfg: SgetSBuf Failed for kwuSap...!");
         RETVALUE(LCM_REASON_MEM_NOAVAIL);
      }
#endif /* ERRCLASS & ERRCLS_INT_PAR */


      /* Initialize the Ue and Cell hash list */
      ret = kwDbmUlInit(gCb);
      if (ret != ROK)
      {
          KW_FREE(gCb,gCb->u.ulCb->udxUlSap, kwUdxSapSize);
          KW_FREE(gCb,gCb->u.ulCb->kwuUlSap, kwSapSize);
          KW_FREE(gCb,gCb->u.ulCb, sizeof (KwUlCb));
         (Void) SPutSMem(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
      
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW043, (ErrVal) cfg->maxUe,
                   "kwLmmGenCfg: SgetSBuf Failed for kwuSap...!");
         RETVALUE(LCM_REASON_MEM_NOAVAIL);
         RETVALUE(LCM_REASON_HASHING_FAILED);
      }

      /* Register the timer */
/*Pradeep: changing the SRegTmrMt() to SRegTmr()*/
      if(SRegTmrMt(gCb->init.ent, gCb->init.inst, (U16)cfg->timeRes,
              kwActvTmr) != ROK)
#if 0
      if(SRegTmr(gCb->init.ent, gCb->init.inst, (U16)cfg->timeRes,
              kwActvTmr) != ROK)
#endif
      {
         KW_FREE(gCb,gCb->u.ulCb->udxUlSap, kwUdxSapSize);
         KW_FREE(gCb,gCb->u.ulCb->kwuUlSap, kwSapSize);
         KW_FREE(gCb,gCb->u.ulCb, sizeof (KwUlCb));
         (Void) SPutSMem(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));

         RETVALUE(LCM_REASON_REGTMR_FAIL);
      }
   }
   /* Timer Initialization  */
   gCb->kwTqCp.tmrLen = KW_TMR_LEN;
   for(cnt = 0; cnt < KW_TMR_LEN; cnt++)
   {
      gCb->kwTq[cnt].first = NULLP;
      gCb->kwTq[cnt].tail = NULLP;
   }


   KW_MEM_CPY(&(gCb->init.lmPst), &cfg->lmPst,
                   sizeof(Pst));

   gCb->init.lmPst.srcProcId = gCb->init.procId;
   gCb->init.lmPst.srcEnt = gCb->init.ent;
   gCb->init.lmPst.srcInst = gCb->init.inst;
   gCb->init.lmPst.event = EVTNONE;

   /* kw002.201 For multi core and multi region,no need to reinitiailize the region again .
      This would be done with kwActvInit from SSI */
#if !defined(SS_MULTICORE_SUPPORT) && !defined(SS_M_PROTO_REGION)
   gCb->init.region = cfg->lmPst.region;
#endif /* !defined(SS_MULTICORE_SUPPORT) && !defined(SS_M_PROTO_REGION) */
   gCb->init.pool   = cfg->lmPst.pool;

   gCb->init.cfgDone = TRUE;

   RETVALUE(LCM_REASON_NOT_APPL);
} /* kwLmmGenCfg */

/**
 *
 * @brief
 *     Sends confirmation message to LM Called by KwMiLkwCfgReq function
 *  @param[in] pst         Post structure
 *  @param[in] cfm         RLC LM structure 
 *  @param[in] type        type of message
 *  @param[in] hdr         message header
 *  @return  S16
 *      -# ROK
 */
#ifdef ANSI
PRIVATE S16 kwLmmSendCfm
(
KwCb  *gCb,
Pst *pst,                    /* Post structure */
KwMngmt *cfm,                /* RLC LM structure */
U8 type,                     /* type of message */
Header *hdr                  /* message header */
)
#else
PRIVATE S16 kwLmmSendCfm(gCb,pst, cfm, type, hdr)
KwCb  gCb;
Pst *pst;                    /* Post structure */
KwMngmt *cfm;                /* RLC LM structure */
U8 type;                     /* type of message */
Header *hdr;                 /* message header */
#endif
{
   Pst rPst;                 /* Reply post structure */

   TRC2(kwLmmSendCfm);

   KW_MEM_SET(&rPst, 0, sizeof(Pst));   
 
   /* reply post structure for confirmation */
   if (gCb)
   {
      rPst.srcEnt = gCb->init.ent;
      rPst.srcInst = gCb->init.inst;
   }
   else
   {
      rPst.srcEnt = pst->dstEnt;
      rPst.srcInst = pst->dstInst;
   }
   rPst.srcProcId = SFndProcId();
   rPst.dstEnt = pst->srcEnt;
   rPst.dstInst = pst->srcInst;
   rPst.dstProcId = pst->srcProcId;
   rPst.selector = hdr->response.selector;
   rPst.prior = hdr->response.prior;
   rPst.route = hdr->response.route;
   rPst.region = hdr->response.mem.region;
   rPst.pool= hdr->response.mem.pool;

   /* Fill the reply header */
   KW_MEM_SET (&cfm->hdr, '\0', sizeof(cfm->hdr));
   cfm->hdr.elmId.elmnt = hdr->elmId.elmnt;
   if (gCb)
   {
      cfm->hdr.entId.ent = gCb->init.ent;
      cfm->hdr.entId.inst = gCb->init.inst;
   }
   else
   {
      cfm->hdr.entId.ent = pst->dstEnt;
      cfm->hdr.entId.inst = pst->dstInst;
   }
   cfm->hdr.transId = hdr->transId;

   switch(type)
   {
      case TCFG:
         KwMiLkwCfgCfm(&rPst,cfm);
         break;
      case TCNTRL:
         SGetDateTime(&(cfm->t.cntrl.dt));
         KwMiLkwCntrlCfm(&rPst,cfm);
         break;
      case TSTS:
         SGetDateTime(&(cfm->t.sts.dt));
         KwMiLkwStsCfm(&rPst,0,cfm);
         break;
      case TSSTA:
         SGetDateTime(&(cfm->t.ssta.dt));
         KwMiLkwStaCfm(&rPst,cfm);
         break;
      default:
#if (ERRCLASS & ERRCLS_INT_PAR)
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW044, (ErrVal) type,
               "Invalid message type");
          
#endif /* ERRCLASS & ERRCLS_INT_PAR */
         break;
   }

   RETVALUE(ROK);
} /* kwLmmSendCfm */


/**
@brief
This function processes configuration requests received from the layer manager.The configuration requests can be for general configuration, or configuration of RGU, KWU, and CKW SAPs. The type of the configuration request can be determined from the elmId field in the header of the layer manager message.This function is called by the layer manager to configure RLC. 

This function implements the following logic: \n

- switch (cfg->hdr.elmId.elmnt)
   - case STGEN 
      - update the genCfg field in RlCb; 
      - allocate the maximum static memory required by the RLC product; 
      - register the timer service by calling SReqTmr; 
      - set CfgDone for not configuring again; 
   - case STKWUSAP 
      - if genCfg is not done, send negative Cfm to the layer manager; 
      - if all the parameters are valid, then allocate the RlSap control block; 
      - update the SAP control block with the information provided in the 
      - configuration request; 
      - send configuration confirm with the status, success; 
   - case STCKWSAP 
      - if genCfg is not done, send negative Cfm to the layer manager; 
      - if all the parametes are valid, then allocate the CrSap control block; 
      - update the SAP control block with the information provided in the configuration request; 
      - send configuration confirm with the status, success; 
   - case STRGUSAP 
      - if genCfg is not done, send negative Cfm to the layer manager; 
      - if all the parametes are valid, then allocate the MkSap control block; 
      - update the SAP control block with the information provided in the configuration request; 
      - send configuration confirm with the status, success; 
- end switch;
 
 *  @param[in] pst      post structure 
 *  @param[in] cfg      LM management structure 
 *  @return S16
 *      -# Success : ROK
 *      -# Failure : RFAILED
*/

#ifdef ANSI
PUBLIC S16 KwMiLkwCfgReq 
(
Pst *pst, 
KwMngmt *cfg
)
#else
PUBLIC S16 KwMiLkwCfgReq (pst, cfg)
Pst  *pst;
KwMngmt *cfg;
#endif
{
   S16   ret;
   Elmnt elmnt;          /* header element */
   KwMngmt rCfm;         /* Reply cfm */
   Reason reason;        /* failure reason */
   KwCb   *tKwCb;

   TRC3(KwMiLkwCfgReq);

   ret = ROK;

   /* Check if the instance is configured */
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
   }
   
   tKwCb =  KW_GET_KWCB(pst->dstInst);
      /*Pradeep - debug*/
   /*printf("\n################### SAPCfg Inst:%d tKwCb:%d\n",pst->dstInst, tKwCb);*/

   /* check configuration is done or not */
   if ((tKwCb) &&(tKwCb->init.cfgDone != TRUE)
         && (cfg->hdr.elmId.elmnt != STGEN))
   {
      /*
       * if general config is not over then use pst structure
       * in primitive to communicate to stack manager
       */

      rCfm.cfm.status = LCM_PRIM_NOK;
      rCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;
      kwLmmSendCfm(tKwCb,pst, &rCfm, TCFG, &cfg->hdr);     
      RETVALUE(RFAILED);
   }

   KWDBGP(tKwCb,(KW_DBGMASK_LMM | KW_DBGMASK_BRIEF),(tKwCb->init.prntBuf,
              "KwMiLkwCfgReq(post, elmId(%d))\n", cfg->hdr.elmId.elmnt));

   elmnt = cfg->hdr.elmId.elmnt;

   switch(elmnt)
   {
      case STGEN:
      {
         reason = kwLmmGenCfg(tKwCb,&cfg->t.cfg.s.gen);
         break;
      }
      case STKWUSAP:
      {
         reason = kwLmmCfgKwuSap(tKwCb,&cfg->t.cfg.s.sap);
         break;
      }
      case STCKWSAP:
      {
         reason = kwLmmCfgCkwSap(tKwCb,&cfg->t.cfg.s.sap);
         break;
      }
      case STRGUSAP:
      {
         reason = kwLmmCfgRguSap(tKwCb,&cfg->t.cfg.s.sap);
         break;
      }
      case STUDXSAP:
      {
         reason = kwLmmCfgUdxSap(tKwCb,&cfg->t.cfg.s.sap);
         break;
      }
      default:
      {
         reason = LCM_REASON_INVALID_ELMNT;
         break;
      }   
   }

   if (reason == LCM_REASON_NOT_APPL)
   {
      rCfm.cfm.status = LCM_PRIM_OK;
      rCfm.cfm.reason = LCM_REASON_NOT_APPL;

      ret = ROK;
   }
   else
   {
      rCfm.cfm.status = LCM_PRIM_NOK;
      rCfm.cfm.reason = reason;

      ret = RFAILED;
   }

   ret = kwLmmSendCfm(tKwCb,pst, &rCfm, TCFG, &cfg->hdr);

   RETVALUE(ret);
} /* KwMiLkwCfgReq */

/**
@brief 
The layer manager initiates and uses the management-control procedure to control RLC elements.The RLC control request primitive (KwMiLkwCntrlReq) can be called more than once and at any time after the management-configuration procedure.The control request primitive is confirmed by a KwMiLkwCntrlCfm primitive.

This function implements the following logic: \n

- if(cfgDone = FALSE) 
   - send negative confirmation to the layer manager; 
   - return; 
- else 
- switch(cntrl->hdr.elmId.elmnt) 
   -  case STGEN 
        - switch (action) 
        - case AENA 
             - switch(subAction) 
             - case SAUSTA 
                  - enable the unsolicited status flag; 
                  - send the control Cfm with success; 
             - case SADBG 
                  - set the debug mask; 
                  - send the control Cfm with success; 
             - case SATRC 
                  - enable the trace flag; 
                  - send the control Cfm with success; 
        - case ADISIMM 
             - switch(subAction) 
             - case SAUSTA 
                  - disable the unsolicited status flag; 
                  - send the control Cfm with success; 
             - case SATRC 
                  - disable the trace flag; 
                  - send the control Cfm with success; 
        - case ASHUTDOWN 
   - case STMKSAP 
        - switch (action) 
        - case ABND 
        - case AUBND 
   - default  
- end else  
 *  @param[in] pst      post structure
 *  @param[in] cntrl    LM management structure
 *  @return S16
 *      -# Success : ROK
 *      -# Failure : RFAILED
*/
#ifdef ANSI
PUBLIC S16 KwMiLkwCntrlReq
(
Pst *pst, 
KwMngmt *cntrl
)
#else
PUBLIC S16 KwMiLkwCntrlReq(pst, cntrl)
Pst     *pst;
KwMngmt *cntrl;
#endif
{
   Elmnt elmnt;          /* header element */
   KwMngmt rCfm;         /* Reply cfm */
   Reason reason;        /* failure reason */
   KwCb   *tKwCb;

   S16 ret;

   TRC3(KwMiLkwCntrlReq)


   ret = ROK;

   /* Check if the instance is configured */
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
   }
   
   tKwCb =  KW_GET_KWCB(pst->dstInst);

   if ((tKwCb) &&(!(tKwCb->init.cfgDone)))
   {
      rCfm.cfm.status = LCM_PRIM_NOK;
      rCfm.cfm.reason = LCM_REASON_GENCFG_NOT_DONE;

      kwLmmSendCfm(tKwCb,pst, &rCfm, TCNTRL, &cntrl->hdr);
      RETVALUE(RFAILED);
   }
   KWDBGP(tKwCb,(KW_DBGMASK_LMM | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
            "KwMiLkwCntrlReq(post, elmId(%d))\n", cntrl->hdr.elmId.elmnt));

   /* In normal cases, LCM_REASON_NOT_APPL is returned in cfm.
    * In all error cases appropriate reason is returned
    * by the functions below
    */

   elmnt = cntrl->hdr.elmId.elmnt;

   reason = LCM_REASON_NOT_APPL;


   switch (elmnt)
   {
      case STGEN:
      {
         /* general control */
         reason = kwLmmGenCntrl(tKwCb,cntrl);
         break;
      }

      /* Configure RLC SAP control */
      case STRGUSAP:
      {
         /* Lower SAP control */
         reason = kwLmmLSapCntrl(tKwCb,cntrl);
         break;
      }
 
      case STUDXSAP:
      {
         /* Udx Sap cntrl */
         reason = kwLmmUdxSapCntrl(tKwCb,cntrl);
         break;
      }

      default:
      {
         reason = LCM_REASON_INVALID_ELMNT;
         break;
      }
   } /* end switch */

   ret = kwLmmFormLmCfm(tKwCb,pst, &cntrl->hdr, reason);
   RETVALUE(ret);
} /* KwMiLkwCntrlReq */

/**
@brief 
This function processes solicited status requests received from the layer
manager. The layer manager can request status information regarding the
system ID, RGSAP,KWSAP, or CKSAP.

 *  @param[in] pst      post structure
 *  @param[in] cfm    LM management structure
 *  @return S16
 *      -# Success : ROK
 *      -# Failure : RFAILED
*/
#ifdef ANSI
PUBLIC S16 KwMiLkwStaReq
(
Pst *pst, 
KwMngmt *sta
)
#else
PUBLIC S16 KwMiLkwStaReq(pst, sta)
Pst     *pst;
KwMngmt *sta;
#endif
{
   S16      ret;
   Elmnt    elmnt;            /* Header element */
   KwMngmt  rSta;             /* Status */
   Reason   reason;           /* Failure reason */
   KwCb    *tKwCb;

   TRC3(KwMiLkwStaReq);


   /* Check if the instance is configured */
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
   }
   
   tKwCb =  KW_GET_KWCB(pst->dstInst);
   if (NULL == tKwCb)
   {
       RETVALUE (RFAILED);
   }

   KWDBGP(tKwCb,(KW_DBGMASK_LMM | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
            "KwMiLkwStaReq(post, elmId(%d))\n", sta->hdr.elmId.elmnt));
   KW_MEM_SET(&rSta, 0, sizeof(KwMngmt));

   reason = LCM_REASON_NOT_APPL;

   elmnt = sta->hdr.elmId.elmnt;

   switch (elmnt)
   {
      case STSID:
      {
         reason = LCM_REASON_NOT_APPL;
         kwGetSId(&rSta.t.ssta.s.sysId);
         break;
      }
      case STGEN:
      {
         break;
      }
      case STKWUSAP:
      {
         KW_MEM_CPY (&rSta.t.ssta.s.kwuSap, &sta->t.ssta.s.kwuSap,
               sizeof (KwKwuSapSta));
         reason = kwLmmGetKwuSapSta (tKwCb,&rSta.t.ssta.s.kwuSap);
         break;
      }
      case STRGUSAP:
      {
         KW_MEM_CPY (&rSta.t.ssta.s.rguSap, &sta->t.ssta.s.rguSap,
               sizeof (KwRguSapSta));
         reason = kwLmmGetRguSapSta (tKwCb,&rSta.t.ssta.s.rguSap);
         break;
      }
      case STCKWSAP:
      {
         KW_MEM_CPY (&rSta.t.ssta.s.ckwSap, &sta->t.ssta.s.ckwSap,
               sizeof (KwCkwCntSapSta));
         reason = kwLmmGetCkwCntSapSta (tKwCb,&rSta.t.ssta.s.ckwSap);
         break;
      }
      default:
      {
         reason = LCM_REASON_INVALID_ELMNT;
         break;
      }
   } /* end of switch */

   ret = kwLmmSendCfm(tKwCb,pst, &rSta, TSSTA, &sta->hdr);

   RETVALUE(ret);
} /* KwMiLkwStaReq */

/**
@brief 
This function processes statistics requests received from the layer manager. After collecting the statistics, this function calls the statistics confirm function to send the statistics to the layer manager.

- switch(sts->hdr.elmId.elmnt) 
  - case STGEN 
     - get the general statistics from the KW control block; 
     - if (action = RESET) 
        - reset the general statistic field in the RlCb; 
        - call KwMiLkwStsCfm to send statistics back to layer manager; 
  - case STCKWSAP 
  - case STKWUSAP 
  - case STRGUSAP 
      - get the SAP specific statistics from KW control block; 
      - if (action = RESET) 
      - reset the general statistic field in the RlCb; 
      - call KwMiLkwStsCfm to send statistics to the layer manager; 
-end switch;

 *  @param[in] pst      post structure
 *  @param[in] action   action 
 *  @param[in] cfg      LM management structure
 *  @return S16
 *      -# Success : ROK
 *      -# Failure : RFAILED
*/
#ifdef ANSI
PUBLIC S16 KwMiLkwStsReq 
(
Pst *pst, 
Action action, 
KwMngmt *sts
)
#else
PUBLIC S16 KwMiLkwStsReq (pst, action, sts)
Pst     *pst;
Action  action;
KwMngmt *sts;
#endif
{
   S16      ret;
   KwMngmt  rSts;             /* Statistics */
   Reason   reason;           /* Reason for failure */
   Elmnt    elmnt;            /* Element Id */
   KwCb   *tKwCb;

   TRC3(KwMiLkwStsReq);


   /* Check if the instance is configured */
   if (pst->dstInst >= KW_MAX_RLC_INSTANCES)
   {
   }
   
   tKwCb =  KW_GET_KWCB(pst->dstInst);
   /*Pradeep - fix*/
   /*if (tKwCb)*/
   if (NULL == tKwCb)
   {
      RETVALUE(RFAILED);
   }

   KWDBGP(tKwCb,(KW_DBGMASK_LMM | KW_DBGMASK_BRIEF), (tKwCb->init.prntBuf,
           "KwMiLkwStsReq(post, elmId(%d),action(%d))\n", action, 
           sts->hdr.elmId.elmnt));
   KW_MEM_SET(&rSts, 0, sizeof(KwMngmt));
   elmnt = sts->hdr.elmId.elmnt;

   switch (elmnt)
   {
      case STGEN:
      {
         reason = kwLmmGetGenSts(tKwCb,&rSts.t.sts.s.gen, action);
         break;
      }
      case STKWUSAP:
      case STRGUSAP:
      case STCKWSAP:
      {
         if(elmnt == STKWUSAP)
         {
            /* kw005.201, modified the element of kwuSap from suId to spId */
            rSts.t.sts.s.kwuSap.spId = sts->t.sts.s.kwuSap.spId;
         }
         reason = kwLmmGetSapSts(tKwCb,&rSts, elmnt, action);
         break;
      }
      default:
      {
         reason = LCM_REASON_INVALID_ELMNT;
         break;
      }
   } /* end switch */

   ret = kwLmmSendCfm(tKwCb,pst, &rSts, TSTS, &sts->hdr);

   RETVALUE(ret);
} /* KwMiLkwStsReq */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
/**
@brief 
This function processes L2 Measurement requests received from the layer manager.
The L2 Measurement is start for a time period and after the timer expiry, the 
measurement confirm is sent.

-  Accept only one set of measurements.
-  Allocate and initialise KwL2MeasEvtCb.
-  Validate if the measurement is already in progress.
   -  Loop through the existing measEvtCb with matching measType
      -  Check if measurement is running for any qci present in the measReq
      -  If present, move the qCi to list of invalid qCIs.
-  Set KwL2MeasEvtCb.measOn to TRUE for QCIs to be measured.
-  For the number of measurements requested.
   -  For all Ues with RBs matching qCI.
      -  Add RbCb to the RB linked list.
      -  Set kwRbCb.measOn to measurement type.
      -  If Meas type is DL_DELAY
         -  Update COUNT to startCount.
-  Start l2Timer

 *  @param[in] pst      post structure
 *  @param[in] action   action 
 *  @param[in] cfg      LM management structure
 *  @return S16
 *      -# Success : ROK
 *      -# Failure : RFAILED
*/
#ifdef ANSI
PUBLIC S16 KwMiLkwL2MeasReq 
(
Pst            *pst, 
KwL2MeasReqEvt *measReqEvt 
)
#else
PUBLIC S16 KwMiLkwL2MeasReq (pst, measReqEvt)
Pst            *pst; 
KwL2MeasReqEvt *measReqEvt;
#endif
{
#if 0 /*PRERIT */
   S16            ret = ROK;
   KwL2MeasEvtCb *measEvtCb = NULLP;
   KwL2MeasCb    *measCb    = NULLP;
   U16            cntr;
   KwRbCb         *kwRbCb;
   U16            seqNum;
   U8             measType;
   KwL2MeasCfmEvt measCfmEvt;
   U8             qci;
#ifdef LTE_RLC_R9
   RguL2MUlThrpMeasReqInfo *ulThrpMeasReqInfo = NULLP;
   CmLteLcId               lChId[KW_MAX_LCH_PER_UE];  /*List of LchIds for this UE*/
   U8                      numLCh = 0;                 /*Number of LCH for this UE*/
   KwRguSapCb              *rguSap = &(gCb->rguSap);
   U8                      lcIdIdx;
#endif /* LTE_RLC_R9 */

   TRC3(KwMiLkwL2MeasReq);
  
   /* Initialize measCfmEvt */
   KW_MEM_ZERO(&measCfmEvt, sizeof(KwL2MeasCfmEvt));
  /* validate the received measReqEvt */
#ifdef LTE_RLC_R9
   ret = kwUtlValidateL2Meas(measReqEvt, &measCfmEvt, lChId, &numLCh);
#else /* LTE_RLC_R9 */
   ret = kwUtlValidateL2Meas(measReqEvt, &measCfmEvt);
#endif /* LTE_RLC_R9 */

   if(ret != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
            "KwMiLkwL2MeasReq: Validation of measReq failed.");
#endif /* ERRCLASS & ERRCLS_ADD_RES */
      kwUtlSndL2MeasNCfm(measReqEvt, &measCfmEvt);
      RETVALUE(RFAILED);

   }
   measType = measReqEvt->measReq.measType;
   /* Allocate and intialise the Event Control Block */
   KW_ALLOC(measEvtCb, sizeof(KwL2MeasEvtCb));
   if(measEvtCb == NULLP)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
            "KwMiLkwL2MeasReq: KW_ALLOC Failed for measCfmEvt.");
#endif /* ERRCLASS & ERRCLS_ADD_RES */
      measCfmEvt.numCfm  = 1;
      measCfmEvt.transId = measReqEvt->transId;
      measCfmEvt.measType = measType;
      measCfmEvt.status.status = LCM_PRIM_NOK;
      measCfmEvt.status.reason = LCM_REASON_MEM_NOAVAIL;
      kwUtlSndL2MeasNCfm(measReqEvt, &measCfmEvt);
      RETVALUE(RFAILED);
   }

   measEvtCb->transId      = measReqEvt->transId;

   measCb           = &measEvtCb->measCb;
   measCb->measType = measType;
   if(measCb->measType &  LKW_L2MEAS_ACT_UE)
   {
      measCb->numSamples = measReqEvt->measReq.val.nonIpThMeas.numSamples;
      measReqEvt->measPeriod /= measReqEvt->measReq.val.nonIpThMeas.numSamples;
   }
#ifdef LTE_RLC_R9
   if((measCb->measType & LKW_L2MEAS_DL_IP) ||
      (measCb->measType & LKW_L2MEAS_UL_IP))
   {
      /* Store valid qci in the control block */
      for(cntr = 0; cntr < measReqEvt->measReq.val.ipThMeas.numQci; cntr++)
      {
         measCb->qci[measCb->numQci++]  = 
                        measReqEvt->measReq.val.ipThMeas.qci[cntr];
         gCb->kwL2Cb.measOn[measReqEvt->measReq.val.ipThMeas.qci[cntr]] |= 
                        measType;
      }
      measCb->ueId = measReqEvt->measReq.val.ipThMeas.ueId;
      measCb->cellId = measReqEvt->measReq.val.ipThMeas.cellId;
   }
   else
#endif /* LTE_RLC_R9 */
   {
      /* Store valid qci in the control block */
      for(cntr = 0; cntr < measReqEvt->measReq.val.nonIpThMeas.numQci; cntr++)
      {
         measCb->qci[measCb->numQci++]  = 
                        measReqEvt->measReq.val.nonIpThMeas.qci[cntr];
         gCb->kwL2Cb.measOn[measReqEvt->measReq.val.nonIpThMeas.qci[cntr]] |= 
                        measType;
      }
   }
   measEvtCb->l2TmrCfg.enb = TRUE;
   measEvtCb->l2TmrCfg.val = measReqEvt->measPeriod;
   cmInitTimers(&measEvtCb->l2Tmr,KW_L2_MAX_TIMERS);

   kwRbCb   = NULLP;
   seqNum   = 0;

   /* update the RBCBs of the measurement */
   for(cntr = 0; cntr < measCb->numQci; cntr++)
   {
      qci = measCb->qci[cntr];
      while (cmHashListFind(&(gCb->kwL2Cb.qciHlCp), (U8 *) &qci, 
               (U16) sizeof(qci),  seqNum++, (PTR *)&kwRbCb) == ROK)
      {
         /* If there is allready data in RbCb, then we should increment the
          * number of active ue  counter. This has to be done seperatly
          * for AM and UM.
          * */
         if(((kwRbCb->rbL2Cb.measOn & measCb->measType) == LKW_L2MEAS_NONE))
         {
            if(measCb->measType & LKW_L2MEAS_ACT_UE)
            {
               if ((kwRbCb->mode == CM_LTE_MODE_UM) && 
                      (kwRbCb->dir & KW_DIR_DL ))
               {
                  if(kwRbCb->m.um.umDl.sduQ.count)
                  {
                     if(kwRbCb->ueCb->numActRb[kwRbCb->qci] == 0)
                     {
                        kwRbCb->ueCb->numActRb[kwRbCb->qci]++;
                        gCb->kwL2Cb.numActUe[measCb->qci[cntr]]++;
                     }
                  } 
               }
               else  if( kwRbCb->mode == CM_LTE_MODE_AM )
               {
                  if((kwRbCb->m.am.amDl.cntrlBo) ||
                      (kwRbCb->m.am.amDl.retxBo)  ||
                      (kwRbCb->m.am.amDl.bo))
                  {
                     if(kwRbCb->ueCb->numActRb[kwRbCb->qci] == 0)
                     {
                        kwRbCb->ueCb->numActRb[kwRbCb->qci]++;
                        gCb->kwL2Cb.numActUe[measCb->qci[cntr]]++;
                     }
                  }
               }
            }/* end of if measType */
         }/* end of if rbType */
         kwUtlPlcMeasDatInL2Sts(&measCb->measData[measCb->qci[cntr]], 
                                &kwRbCb->rbL2Cb, measType);
         kwRbCb->rbL2Cb.measOn |= measCb->measType;
      }/* End of while loop */
      seqNum = 0;
   }/* End of for loop */
   for(cntr = 0; cntr < LKW_MAX_L2MEAS; cntr++)
   {
      if(gCb->kwL2Cb.kwL2EvtCb[cntr] == NULLP)
      {
         measEvtCb->cbIdx = cntr;
         gCb->kwL2Cb.kwL2EvtCb[cntr]  = measEvtCb;
         gCb->kwL2Cb.kwNumMeas++;
         break;
      }
   }

#ifdef LTE_RLC_R9
   if(measCb->measType & LKW_L2MEAS_UL_IP)
   {
      /*Send req to MAC to start taking timings for these LCHs*/
      KW_ALLOC(ulThrpMeasReqInfo, sizeof(RguL2MUlThrpMeasReqInfo));
#if (ERRCLASS & ERRCLS_ADD_RES)
      if(NULLP == ulThrpMeasReqInfo)
      {
         KWLOGERROR(gCb,ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
            "KwMiLkwL2MeasReq: KW_ALLOC Failed for ulThrpMeasReqInfo.");
         RETVALUE(RFAILED);
      } 
#endif /* ERRCLASS & ERRCLS_ADD_RES */
      ulThrpMeasReqInfo->cellId = measCb->cellId;
      ulThrpMeasReqInfo->rnti = measCb->ueId;
      ulThrpMeasReqInfo->numLcId = numLCh;
      ulThrpMeasReqInfo->enbMeas = TRUE;
      for(lcIdIdx = 0; lcIdIdx < numLCh; lcIdIdx++)
      {
         ulThrpMeasReqInfo->lcId[lcIdIdx] = lChId[lcIdIdx];
         measCb->lcId[lcIdIdx] = lChId[lcIdIdx];
      }
      /*Storing numLCh and lcId list in measCb so that the same can be used*
       *while sending the indication to MAC for disabling measurement after*
       *the timer expiry.                                                  */
      measCb->numLcId = numLCh;
      /*Send ulThrpMeasReqInfo to MAC*/
      KwLiRguL2MUlThrpMeasReq(&rguSap->pst,rguSap->spId, ulThrpMeasReqInfo);
   }
#endif /* LTE_RLC_R9 */

   kwStartTmr((PTR)measEvtCb, KW_EVT_L2_TMR); 
   KW_FREE(measReqEvt, sizeof(KwL2MeasReqEvt))
   RETVALUE(ret);
#endif
   RETVALUE(ROK);
} /* KwMiLkwL2MeasReq */

#endif /* LTE_L2_MEAS_RLC */

/**
 * @brief
      This function configures the RLC data sap
 *
 *  @param[in] cfm         RLC LM Sap structure
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_SAP 
 *                   LCM_REASON_MEM_NOAVAIL 
 *                   LCM_REASON_RECONFIG_FAIL 
 */
#ifdef ANSI
PRIVATE S16 kwLmmCfgKwuSap
(
KwCb       *gCb,
KwSapCfg   *cfg                /* SAP configuration structure */
)
#else
PRIVATE S16 kwLmmCfgKwuSap(gCb,cfg)
KwCb       *gCb;
KwSapCfg   *cfg;               /* SAP configuration structure */
#endif
{
   KwKwuSapCb   *kwuSapCb;
   TRC2(kwLmmCfgKwuSap)

   /* Validate the protocol parameters */
   if (cfg->sapId >= (S16)gCb->genCfg.maxKwuSaps)
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
   {
      /* Get Sap control block */
      kwuSapCb = (KwKwuSapCb*)(gCb->u.dlCb->kwuDlSap + cfg->sapId);
   }
   else
   {
      /* Get Sap control block */
      kwuSapCb = (KwKwuSapCb*)(gCb->u.ulCb->kwuUlSap + cfg->sapId);
   }

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* Check for reconfiguration */
   if (kwuSapCb->state != KW_SAP_NOT_CFG)
   {
      KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW045, (ErrVal) kwuSapCb->state,
               "kwLmmCfgKwuSap: Invalid kwuSap State");
      /* reconfiguration not allowed */
      RETVALUE(LCM_REASON_RECONFIG_FAIL);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   /* Fill the parameters */
   kwuSapCb->pst.selector = cfg->selector;
   kwuSapCb->pst.route = cfg->route;
   kwuSapCb->pst.prior =  cfg->priority;
   /* kw002.201 With multicore support layer shall use the assigned region
      and pool from SSI */
#if defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION)
   kwuSapCb->pst.region = gCb->init.region; 
   kwuSapCb->pst.pool = gCb->init.pool; 
#else /* defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION) */
   kwuSapCb->pst.region = cfg->mem.region; 
   kwuSapCb->pst.pool = cfg->mem.pool;
#endif /* defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION) */
   kwuSapCb->pst.dstProcId = cfg->procId;
   kwuSapCb->pst.dstEnt = cfg->ent;
   kwuSapCb->pst.dstInst = cfg->inst;
   kwuSapCb->pst.srcProcId = gCb->init.procId;
   kwuSapCb->pst.srcEnt = gCb->init.ent;
   kwuSapCb->pst.srcInst = gCb->init.inst;
   kwuSapCb->pst.event = EVTNONE;
   kwuSapCb->spId = cfg->sapId;
   kwuSapCb->state = KW_SAP_CFG;

   /* update KWU sap counter */
   if (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
   {
      gCb->u.dlCb->numKwuSaps++;
      /* Get Sap control block */
   }
   else
   {
      gCb->u.ulCb->numKwuSaps++;
   }

   RETVALUE(LCM_REASON_NOT_APPL);
} /* kwLmmCfgKwuSap */

/**
 * @brief
      This function configures the RLC control sap
 *
 *  @param[in] cfm         RLC LM Sap structure
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_SAP
 *                   LCM_REASON_INVALID_SAP 
 *                   LCM_REASON_RECONFIG_FAIL 
 */
#ifdef ANSI
PRIVATE S16 kwLmmCfgCkwSap 
(
KwCb       *gCb,
KwSapCfg   *cfg               /* SAP control block */
)
#else
PRIVATE S16 kwLmmCfgCkwSap(gCb,cfg)
KwCb       *gCb;
KwSapCfg   *cfg;              /* SAP control block */
#endif
{
   KwCkwSapCb  *ckwSap;
   
   TRC2(kwLmmCfgCkwSap)

   /* Validate config parameters */
   if (cfg->sapId >= KW_MAX_CKWSAPS )
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   if (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
   {
      /* Get Sap control block */
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
#if 0
      ckwSap = &(gCb->u.dlCb->ckwSap);
#endif
   }
   else
   {
      ckwSap = &(gCb->u.ulCb->ckwSap);
   }
      /*Pradeep - debug*/
   /*printf("\n################### SAPCfg ckwSap:%d ckwSap->state:%d\n",ckwSap, ckwSap->state);*/

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* Check for reconfiguration */
   if(ckwSap->state  != KW_SAP_NOT_CFG)
   {
      KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW046, (ErrVal) ckwSap->state,
               "kwLmmCfgCkwSap: Invalid ckwSap State");
      RETVALUE(LCM_REASON_RECONFIG_FAIL);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */
   
   /* Fill the parameters */
   ckwSap->pst.selector = cfg->selector;
   ckwSap->pst.route = cfg->route;
   ckwSap->pst.prior =  cfg->priority;
   /* kw002.201 With multicore support layer shall use the assigned region
      and pool from SSI */
#if defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION)
   ckwSap->pst.region = gCb->init.region; 
   ckwSap->pst.pool = gCb->init.pool; 
#else /* defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION) */
   ckwSap->pst.region = cfg->mem.region;
   ckwSap->pst.pool = cfg->mem.pool;
#endif /* defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION) */
   ckwSap->pst.dstProcId = cfg->procId;
   ckwSap->pst.dstEnt = cfg->ent;
   ckwSap->pst.dstInst = cfg->inst;
   ckwSap->pst.srcProcId = gCb->init.procId;
   ckwSap->pst.srcEnt = gCb->init.ent;
   ckwSap->pst.srcInst = gCb->init.inst;
   ckwSap->pst.event = EVTNONE;
   ckwSap->spId = cfg->sapId;

   /* make sap unbound initially */
   ckwSap->state = KW_SAP_CFG;

   RETVALUE(LCM_REASON_NOT_APPL);
} /* kwLmmCfgCkwSap */

/**
 * @brief
      This function configures the RGU sap
 *
 *  @param[in] cfm         RLC LM Sap structure
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_SAP
 *                   LCM_REASON_INVALID_SAP
 *                   LCM_REASON_RECONFIG_FAIL
 */
#ifdef ANSI
PRIVATE S16 kwLmmCfgUdxSap 
(
KwCb       *gCb,
KwSapCfg   *cfg               /* pointer to MKU SAP config struct */
)
#else
PRIVATE S16 kwLmmCfgUdxSap(gCb,cfg)
KwCb       *gCb;
KwSapCfg   *cfg;              /* pointer to MKU SAP config struct */
#endif
{
   KwUdxDlSapCb *udxDlSap;
   KwUdxUlSapCb *udxUlSap;

   TRC2(kwLmmCfgUdxSap);
   
   /* Validate the protocol parameters */
   if((cfg->sapId >= KW_MAX_UDXSAPS) || (cfg->sapId < 0))
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* Get Sap control block */
   if (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
   {
      udxDlSap = (gCb->u.dlCb->udxDlSap + cfg->sapId);
#if (ERRCLASS & ERRCLS_INT_PAR)
      /* Check for reconfiguration */
      if(udxDlSap->state != KW_SAP_NOT_CFG)
      {
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW047, (ErrVal) udxDlSap->state,
                  "kwLmmCfgUdxSap: Invalid rguSap State");
         RETVALUE(LCM_REASON_RECONFIG_FAIL);
      }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

      /* Fill the parameters */
      udxDlSap->pst.selector = cfg->selector;
      udxDlSap->pst.route = cfg->route;
      udxDlSap->pst.prior =  cfg->priority;

#if defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION)
      udxDlSap->pst.region = gCb->init.region; 
      udxDlSap->pst.pool = gCb->init.pool; 
#else /* defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION) */
      udxDlSap->pst.region = cfg->mem.region;
      udxDlSap->pst.pool = cfg->mem.pool;
#endif /* defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION) */
      udxDlSap->pst.dstProcId = cfg->procId;
      udxDlSap->pst.dstEnt = cfg->ent;
      udxDlSap->pst.dstInst = cfg->inst;
      udxDlSap->pst.srcProcId = gCb->init.procId;
      udxDlSap->pst.srcEnt = gCb->init.ent;
      udxDlSap->pst.srcInst = gCb->init.inst;
      udxDlSap->pst.event = EVTNONE;
      udxDlSap->spId = cfg->sapId;
      udxDlSap->state = KW_SAP_CFG;

   }
   else
   {
      udxUlSap = (gCb->u.ulCb->udxUlSap + cfg->sapId);

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* Check for reconfiguration */
      if(udxUlSap->state != KW_SAP_NOT_CFG)
      {
         KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW047, (ErrVal) udxUlSap->state,
                  "kwLmmCfgUdxSap: Invalid rguSap State");
         RETVALUE(LCM_REASON_RECONFIG_FAIL);
      }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   /* Fill the parameters */
      udxUlSap->pst.selector = cfg->selector;
      udxUlSap->pst.route = cfg->route;
      udxUlSap->pst.prior =  cfg->priority;

#if defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION)
      udxUlSap->pst.region = gCb->init.region; 
      udxUlSap->pst.pool = gCb->init.pool; 
#else /* defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION) */
      udxUlSap->pst.region = cfg->mem.region;
      udxUlSap->pst.pool = cfg->mem.pool;
#endif /* defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION) */
      udxUlSap->pst.dstProcId = cfg->procId;
      udxUlSap->pst.dstEnt = cfg->ent;
      udxUlSap->pst.dstInst = cfg->inst;
      udxUlSap->pst.srcProcId = gCb->init.procId;
      udxUlSap->pst.srcEnt = gCb->init.ent;
      udxUlSap->pst.srcInst = gCb->init.inst;
      udxUlSap->pst.event = EVTNONE;
      udxUlSap->spId = cfg->sapId;
      udxUlSap->state = KW_SAP_CFG;

      udxUlSap->bndTmrInt = cfg->bndTmrIntvl;
      udxUlSap->retryCnt = 0;
      cmInitTimers(&(udxUlSap->bndTmr), 1);
   }

   RETVALUE(LCM_REASON_NOT_APPL);
} /* kwLmmCfgUdxSap */


/**
 * @brief
      This function configures the RGU sap
 *
 *  @param[in] cfm         RLC LM Sap structure
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_SAP
 *                   LCM_REASON_INVALID_SAP
 *                   LCM_REASON_RECONFIG_FAIL
 */
#ifdef ANSI
PRIVATE S16 kwLmmCfgRguSap 
(
KwCb       *gCb,
KwSapCfg   *cfg               /* pointer to MKU SAP config struct */
)
#else
PRIVATE S16 kwLmmCfgRguSap(gCb,cfg)
KwCb       *gCb;
KwSapCfg   *cfg;              /* pointer to MKU SAP config struct */
#endif
{
   KwRguSapCb *rguSap;

   TRC2(kwLmmCfgRguSap);
   
   /* Validate the protocol parameters */
   if((cfg->sapId >= KW_MAX_RGUSAPS) || (cfg->sapId < 0))
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* Get Sap control block */
   if (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
   {
      rguSap = &(gCb->u.dlCb->rguDlSap);
   }
   else
   {
      rguSap = &(gCb->u.ulCb->rguUlSap);
   }



#if (ERRCLASS & ERRCLS_INT_PAR)
   /* Check for reconfiguration */
   if(rguSap->state != KW_SAP_NOT_CFG)
   {
      KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW047, (ErrVal) rguSap->state,
               "kwLmmCfgRguSap: Invalid rguSap State");
      RETVALUE(LCM_REASON_RECONFIG_FAIL);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   /* Fill the parameters */
   rguSap->pst.selector = cfg->selector;
   rguSap->pst.route = cfg->route;
   rguSap->pst.prior =  cfg->priority;

   /* kw002.201 With multicore support layer shall use the assigned region
      and pool from SSI */
#if defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION)
   rguSap->pst.region = gCb->init.region; 
   rguSap->pst.pool = gCb->init.pool; 
#else /* defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION) */
   rguSap->pst.region = cfg->mem.region;
   rguSap->pst.pool = cfg->mem.pool;
#endif /* defined(SS_MULTICORE_SUPPORT) && defined(SS_M_PROTO_REGION) */
   rguSap->pst.dstProcId = cfg->procId;
   rguSap->pst.dstEnt = cfg->ent;
   rguSap->pst.dstInst = cfg->inst;
   rguSap->pst.srcProcId = gCb->init.procId;
   rguSap->pst.srcEnt = gCb->init.ent;
   rguSap->pst.srcInst = gCb->init.inst;
   rguSap->pst.event = EVTNONE;
#if 1 /* TODO */
   rguSap->spId = cfg->sapId;
#else
   rguSap->suId = cfg->sapId;
#endif
   rguSap->bndTmrInt = cfg->bndTmrIntvl;
   rguSap->retryCnt = 0;
   rguSap->state = KW_SAP_CFG;

   cmInitTimers(&(rguSap->bndTmr), 1);

   RETVALUE(LCM_REASON_NOT_APPL);
} /* kwLmmCfgRguSap */

/**
 * @brief
     Validates the RLC general control parameters 
 *
 *  @param[in] cntrl RLC LM structure 
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_SUBACTION
 *                   LCM_REASON_INVALID_ACTION
 */
#ifdef ANSI
PRIVATE S16 kwLmmValidateGenCntrl
(
KwMngmt *cntrl                 /* RLC LM structure */
)
#else
PRIVATE S16 kwLmmValidateGenCntrl(cntrl)
KwMngmt *cntrl;                /* RLC LM structure */
#endif
{
   S16 reason;                 /* reason for failure */
   U8 action;                  /* action parameter */
   U8 sAction;                 /* subaction field */


   reason = LCM_REASON_NOT_APPL;

   TRC2(kwLmmValidateGenCntrl);

   action = cntrl->t.cntrl.action;
   sAction = cntrl->t.cntrl.subAction;

   switch (action)
   {
      case AENA:
      case ADISIMM:
         if ((sAction != SAUSTA)
            && (sAction != SADBG)
            && (sAction != SATRC))
         {
            reason = LCM_REASON_INVALID_SUBACTION;
         }
         break;
      case ASHUTDOWN:
         break;
      default:
         reason = LCM_REASON_INVALID_ACTION;
         break;
   }
   
   RETVALUE(reason);
} /* kwLmmValidateGenCntrl */

/**
 * @brief
     it deregisters the timers and deregisters the kwuSap Control blocks 
 *
 *  @return  Void
 */
#ifdef ANSI
PRIVATE Void kwLmmCleanGblRsrcs
(
KwCb *gCb
)
#else
PRIVATE Void kwLmmCleanGblRsrcs(gCb)
KwCb *gCb;
#endif
{
   Size    kwSapSize;

   TRC2(kwLmmCleanGblRsrcs)   
 
   if (gCb->init.cfgDone)
   {
      /* Deregister the timers */
/*Pradeep: changing the SDeregTmrMt() to SDeregTmr*/
      (Void) SDeregTmrMt(gCb->init.ent, gCb->init.inst,
                        (S16)gCb->genCfg.timeRes, kwActvTmr);
      /*(Void) SDeregTmr(gCb->init.ent, gCb->init.inst,
                        (S16)gCb->genCfg.timeRes, kwActvTmr);*/

      kwSapSize = (Size)((Size)gCb->genCfg.maxKwuSaps * (Size)sizeof(KwKwuSapCb));
      if (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
      {
         if (gCb->u.dlCb)
         {
            if (gCb->u.dlCb->kwuDlSap != (KwKwuSapCb *)NULLP)
            {
               KW_FREE(gCb,gCb->u.dlCb->kwuDlSap, kwSapSize);
            }
         
            KW_FREE(gCb,gCb->u.dlCb, sizeof (KwDlCb));
         }
         
      }
      else
      {
         if (gCb->u.ulCb)
         {
            if (gCb->u.ulCb->kwuUlSap != (KwKwuSapCb *)NULLP)
            {
               KW_FREE(gCb,gCb->u.ulCb->kwuUlSap, kwSapSize);
            }
         
            KW_FREE(gCb,gCb->u.ulCb, sizeof (KwUlCb));
         }
      }

      (Void) SPutSMem(gCb->init.region, gCb->init.pool);
      gCb->init.cfgDone = FALSE;
      gCb->init.acnt = FALSE;
      gCb->init.trc = FALSE;

      gCb->init.usta = FALSE;
   }


#if 0
   kwActvInit(gCb->init.ent, gCb->init.inst,
                        gCb->init.region, gCb->init.reason);
#endif

   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
} /* kwLmmCleanGblRsrcs */

/**
 * @brief
      Delete all SAPs and Control Blocks
 *
 * @b Description
 *       Shutdown of RLC happens at modules level, tm, um and am modules will be
 *       shutdown using utility functin and dbm shutdown will clean up the SAPs,
 *       control blocks and lists. 
 *
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_HASHING_FAILED 
 */
#ifdef ANSI
PRIVATE S16 kwLmmShutdown
(
KwCb *gCb
)
#else
PRIVATE S16 kwLmmShutdown(gCb)
KwCb *gCb;
#endif
{
   KwRguSapCb *rguSap;

   TRC2(kwLmmShutdown)

   if (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
   {
      rguSap = &(gCb->u.dlCb->rguDlSap); 
   }
   else
   {
      rguSap = &(gCb->u.ulCb->rguUlSap); 
   }
   KwLiRguUbndReq(&(rguSap->pst), rguSap->spId, 0);

   if(gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
   {
      kwDbmDlShutdown(gCb); 
   }
   else
   {
      kwDbmUlShutdown(gCb);
   }
   kwLmmCleanGblRsrcs(gCb);

   /*Pradeep - fix for initialising the stats*/
   cmMemset(&(gCb->genSts), 0, sizeof(KwGenSts));

   RETVALUE(LCM_REASON_NOT_APPL);
} /* end of kwLmmShutdown */

/**
 * @brief
     Function processes the general control request 
 *
 *  @param[in] cntrl RLC LM structure
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_SUBACTION
 *                   LCM_REASON_INVALID_ACTION
 */
#ifdef ANSI
PRIVATE S16 kwLmmGenCntrl
(
KwCb *gCb,
KwMngmt *cntrl                 /* RLC LM structure */
)
#else
PRIVATE S16 kwLmmGenCntrl(gCb,cntrl)
KwCb    *gCb;
KwMngmt *cntrl;                /* RLC LM structure */
#endif
{
   U8 action;            /* action parameter */
   U8 sAction;           /* subaction field */
   KwTrcCntrl *trcCntrl; /* trace */

#ifdef DEBUGP
   KwDbgCntrl *dbgCntrl; /* debug */
#endif /* DEBUGP */

   S16   reason;         /* reason for failure */
   
   TRC2(kwLmmGenCntrl);

   reason = LCM_REASON_NOT_APPL;

   /* Validate control parameters */
   reason = kwLmmValidateGenCntrl (cntrl);

   action = cntrl->t.cntrl.action;
   sAction = cntrl->t.cntrl.subAction;

   if (reason != LCM_REASON_NOT_APPL)
   {
      RETVALUE(reason);
   }

   switch(action)
   {
      case AENA:
      {
         switch(sAction)
         {
            case SAUSTA:
            {
               KW_SET_USTA_FLAG(gCb, TRUE);
               break;
            }
            case SADBG:
            {
#ifdef DEBUGP
               dbgCntrl = &cntrl->t.cntrl.s.dbgCntrl;
               KW_GET_DBG_MASK(gCb) |= dbgCntrl->dbgMask;
#endif /* DEBUGP */
               break;
            }
            case SATRC:
            {
               trcCntrl = &cntrl->t.cntrl.s.trcCntrl;
               gCb->init.trc = TRUE;
               gCb->trcLen = trcCntrl->trcLen;
               (gCb->trcMask) |= trcCntrl->trcMask;
                break;
            }
         }
         break;
      }
      case ADISIMM:
      {
         switch(sAction)
         {
            case SAUSTA:
            {
               gCb->init.usta = FALSE;
            }
            break;
            case SADBG:
            {
#ifdef DEBUGP
               dbgCntrl = &cntrl->t.cntrl.s.dbgCntrl;
               KW_GET_DBG_MASK(gCb) &= ~(dbgCntrl->dbgMask);
#endif /* DEBUGP */
            }
            break;
            case SATRC:
            {
               trcCntrl = &cntrl->t.cntrl.s.trcCntrl;
               gCb->init.trc = FALSE;
               gCb->trcMask &= ~(trcCntrl->trcMask);
            }
            break;
         }
         break;
      }
      case ASHUTDOWN:
      {
         reason = kwLmmShutdown(gCb);
         break;
      }
   }
   RETVALUE(reason);
} /* kwLmmGenCntrl */

/**
 * @brief
     Bind/Unbind RLC lower sap 
 *
 *  @param[in] cntrl RLC LM structure
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_SAP 
 *                   LCM_REASON_INVALID_STATE
 *                   LCM_REASON_INVALID_ACTION 
 */
#ifdef ANSI
PRIVATE S16 kwLmmUdxSapCntrl
(
KwCb    *gCb,
KwMngmt *cntrl                 /* RLC LM structure */
)
#else
PRIVATE S16 kwLmmUdxSapCntrl(gCb,cntrl)
KwCb    *gCb;
KwMngmt *cntrl;                /* RLC LM structure */
#endif
{
   U8         action;                  /* action parameter */
   S16        reason;                 /* reason for failure */
   KwUdxUlSapCb *udxSap;                /* rgu sap pointer */

   TRC2(kwLmmUdxSapCntrl)

   reason = LCM_REASON_NOT_APPL;
   action = cntrl->t.cntrl.action;

   if (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
   {
      reason = LCM_REASON_INVALID_SAP;
      RETVALUE(reason);
   }

   /* validate SuId */
   if((cntrl->t.cntrl.s.sapCntrl.suId < 0)
   || (cntrl->t.cntrl.s.sapCntrl.suId >= KW_MAX_UDXSAPS))
   {
      reason = LCM_REASON_INVALID_SAP;
      RETVALUE(reason);
   }

   udxSap = gCb->u.ulCb->udxUlSap + cntrl->t.cntrl.s.sapCntrl.suId;

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate SAP */
   if(udxSap->state == KW_SAP_NOT_CFG)
   {
      KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW048, (ErrVal) udxSap->state,
               "kwLmmLSapCntrl: Invalid udxSap State");
      reason = LCM_REASON_INVALID_STATE;
      RETVALUE(reason);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   switch(action)
   {
      case ABND:
      {
         if(udxSap->state != KW_SAP_BND)
         {
            /* start timer to wait for bind confirm */
            kwStartTmr(gCb,(PTR)(udxSap), KW_EVT_WAIT_BNDCFM);
            udxSap->state = KW_SAP_BINDING;
            KwUlUdxBndReq(&(udxSap->pst), udxSap->suId, udxSap->spId);
         }
         else
         {
            /* control request received for an already bound SAP */
            reason = LCM_REASON_INVALID_STATE;
         }
      }
      break;
      case AUBND:
      {
         /* make the state of RGUSAP is configure but not bound */
         udxSap->state = KW_SAP_CFG;
         KwUlUdxUbndReq(&(udxSap->pst), udxSap->spId, 0);
      }
      break;
      default:
         reason = LCM_REASON_INVALID_ACTION;
         break;
   } /* end of switch */

   RETVALUE(reason);
} /* kwLmmUdxSapCntrl*/

/**
 * @brief
     Bind/Unbind RLC lower sap 
 *
 *  @param[in] cntrl RLC LM structure
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_SAP 
 *                   LCM_REASON_INVALID_STATE
 *                   LCM_REASON_INVALID_ACTION 
 */
#ifdef ANSI
PRIVATE S16 kwLmmLSapCntrl
(
KwCb    *gCb,
KwMngmt *cntrl                 /* RLC LM structure */
)
#else
PRIVATE S16 kwLmmLSapCntrl(gCb,cntrl)
KwCb    *gCb;
KwMngmt *cntrl;                /* RLC LM structure */
#endif
{
   U8         action;                  /* action parameter */
   S16        reason;                 /* reason for failure */
   KwRguSapCb *rguSap;                /* rgu sap pointer */

   TRC2(kwLmmLSapCntrl)

   reason = LCM_REASON_NOT_APPL;
   action = cntrl->t.cntrl.action;
   rguSap = (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL) ?
            &(gCb->u.dlCb->rguDlSap): &(gCb->u.ulCb->rguUlSap);

   /* validate SuId */
   if((cntrl->t.cntrl.s.sapCntrl.suId < 0)
   || (cntrl->t.cntrl.s.sapCntrl.suId >= KW_MAX_RGUSAPS))
   {
      reason = LCM_REASON_INVALID_SAP;
      RETVALUE(reason);
   }

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate SAP */
   if(rguSap->state == KW_SAP_NOT_CFG)
   {
      KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW048, (ErrVal) rguSap->state,
               "kwLmmLSapCntrl: Invalid rguSap State");
      reason = LCM_REASON_INVALID_STATE;
      RETVALUE(reason);
   }
#endif /* ERRCLASS & ERRCLS_INT_PAR */

   switch(action)
   {
      case ABND:
      {
         if(rguSap->state != KW_SAP_BND)
         {
            /* start timer to wait for bind confirm */
            kwStartTmr(gCb,(PTR)(rguSap), KW_EVT_WAIT_BNDCFM);
            rguSap->state = KW_SAP_BINDING;
            KwLiRguBndReq(&(rguSap->pst), rguSap->suId, rguSap->spId);
         }
         else
         {
            /* control request received for an already bound SAP */
            reason = LCM_REASON_INVALID_STATE;
         }
      }
      break;
      case AUBND:
      {
         /* make the state of RGUSAP is configure but not bound */
         rguSap->state = KW_SAP_CFG;
         KwLiRguUbndReq(&(rguSap->pst), rguSap->spId, 0);
      }
      break;
      default:
         reason = LCM_REASON_INVALID_ACTION;
         break;
   } /* end of switch */

   RETVALUE(reason);
} /* kwLmmLSapCntrl */

/**
 * @brief
     forms Lm Cfm based on the return values 
 *
 *  @param[in] cntrl RLC LM structure
 *  @return  S16
 *      -# Success : ROK 
 *      -# Failure : RFAILED
 */
#ifdef ANSI
PRIVATE S16 kwLmmFormLmCfm
(
KwCb     *gCb,
Pst      *pst,
Header   *hdr,
Reason   reason
)
#else
PRIVATE S16 kwLmmFormLmCfm(gCb,pst, hdr, reason)
KwCb     *gCb;
Pst      *pst;
Header   *hdr;
Reason   reason;
#endif
{
   KwMngmt  rCfm;
   S16      ret;
   TRC3(kwLmmFormLmCfm)

   ret = ROK;

   if (reason == LCM_REASON_NOT_APPL)
   {
      rCfm.cfm.status = LCM_PRIM_OK;
      rCfm.cfm.reason = LCM_REASON_NOT_APPL;

      ret = ROK;
   }
   else
   {
      rCfm.cfm.status = LCM_PRIM_NOK;
      rCfm.cfm.reason = reason;

      ret = RFAILED;
   }

   kwLmmSendCfm(gCb,pst, &rCfm, TCNTRL, hdr);

   RETVALUE(ret);
} /* kwLmmFormLmCfm */

/**
 * @brief
     Function gather the general KWU SAP status 
 *
 *  @param[in] sta LM KWU Sap Status structure 
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_PAR_VAL
 */
#ifdef ANSI
PRIVATE S16 kwLmmGetKwuSapSta 
(
KwCb        *gCb,
KwKwuSapSta *sta                /* RLU SAP status */
)
#else
PRIVATE S16 kwLmmGetKwuSapSta(gCb,sta)
KwCb        *gCb;
KwKwuSapSta *sta;               /* RLU SAP status */
#endif
{
   KwKwuSapCb *kwSapCb;
   
   TRC2(kwLmmGetKwuSapSta);

   /* Validate the protocol parameters */
   if (sta->spId >= (S16)gCb->genCfg.maxKwuSaps)
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   /* Get Sap control block */
   kwSapCb = (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)? 
             (KwKwuSapCb*)(gCb->u.dlCb->kwuDlSap + sta->spId):
             (KwKwuSapCb*)(gCb->u.ulCb->kwuUlSap + sta->spId);

   sta->state = kwSapCb->state;

   RETVALUE(LCM_REASON_NOT_APPL);
} /* kwLmmGetKwuSapSta */

/**
 * @brief
     Function gather the general RGU SAP status
 *
 *  @param[in] sta LM RGU Sap Status structure
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_PAR_VAL
 */
#ifdef ANSI
PRIVATE S16 kwLmmGetRguSapSta 
(
KwCb        *gCb,
KwRguSapSta *sta                /* RLU SAP status */
)
#else
PRIVATE S16 kwLmmGetRguSapSta(gCb,sta)
KwCb        *gCb;
KwRguSapSta *sta;               /* RLU SAP status */
#endif
{
   TRC2(kwLmmGetRguSapSta);

   /* Validate the protocol parameters */
   if((sta->suId >= KW_MAX_RGUSAPS) || (sta->suId < 0))
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   sta->state = (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL) ? 
                 gCb->u.dlCb->rguDlSap.state : 
                 gCb->u.ulCb->rguUlSap.state ;

   RETVALUE(LCM_REASON_NOT_APPL);
} /* kwLmmGetRguSapSta */

/**
 * @brief
     Function gather the general CKW SAP status
 *
 *  @param[in] sta LM CKW Sap Status structure
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_PAR_VAL
 */
#ifdef ANSI
PRIVATE S16 kwLmmGetCkwCntSapSta
(
KwCb           *gCb,
KwCkwCntSapSta *sta              /* RLU SAP status */
)
#else
PRIVATE S16 kwLmmGetCkwCntSapSta(gCb,sta)
kwCb           *gCb,
KwCkwCntSapSta *sta;             /* RLU SAP status */
#endif
{
   TRC2(kwLmmGetCkwCntSapSta);

   /* Validate config parameters */
   if (sta->spId >= KW_MAX_CKWSAPS )
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }
   if (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   sta->state =  gCb->u.ulCb->ckwSap.state ;

   RETVALUE(LCM_REASON_NOT_APPL);

} /* kwLmmGetCkwCntSapSta */

/**
 * @brief
     Gather the general statistics 
 *
 *  @param[in] sts       LM general statistics structure
 *  @param[in] action    action
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_PAR_VAL
 */
#ifdef ANSI
PRIVATE S16 kwLmmGetGenSts
(
KwCb     *gCb,
KwGenSts *sts,              /* general statistics structure */
Action action               /* Action */
)
#else
PRIVATE S16 kwLmmGetGenSts(gCb,sts, action)
KwCb     *gCb;
KwGenSts *sts;              /* general statistics structure */
Action action;              /* Action */
#endif
{
   KwGenSts *genSts;        /* General statistics */

   TRC2(kwLmmGetGenSts);

   /* Validate protocol parameters */
   if ((action != LKW_ZEROSTS) && (action != LKW_NOZEROSTS))
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }

   KW_MEM_CPY (sts, &(gCb->genSts), sizeof (KwGenSts));
   
   if(action == LKW_ZEROSTS)
   {
      genSts = &(gCb->genSts);
      KW_MEM_SET (genSts, 0, sizeof (KwGenSts));
   }

   RETVALUE(LCM_REASON_NOT_APPL);
} /* kwLmmGetGenSts */

/**
 * @brief
     Gather the SAP statistics
 *
 *  @param[in] sts     LM general statistics structure
 *  @param[in] elmnt   element 
 *  @param[in] action  action 
 *  @return  S16
 *      -# Success : LCM_REASON_NOT_APPL
 *      -# Failure : LCM_REASON_INVALID_PAR_VAL
 */
#ifdef ANSI
PRIVATE S16 kwLmmGetSapSts
(
KwCb    *gCb,
KwMngmt *sts,               /* RLC layer management */
Elmnt elmnt,                /* element */
Action action               /* Action */
)
#else
PRIVATE S16 kwLmmGetSapSts(sts, elmnt, action)
KwCb    *gCb;
KwMngmt *sts;               /* RLC layer management */
Elmnt elmnt;                /* element */
Action action;              /* Action */
#endif
{
   KwKwuSapCb   *kwuSapCb;      /* RLU SAP control block */
   KwKwuSapSts  *kwuSap;       /* place holder for SAP statistics */
   KwCkwCntSts  *ckwSap;       /* place holder for SAP statistics */

   TRC2(kwLmmGetSapSts);

   /* Validate protocol parameters */
   if (action != LKW_ZEROSTS && action != LKW_NOZEROSTS)
   {
      RETVALUE(LCM_REASON_INVALID_PAR_VAL);
   }
   switch(elmnt)
   {
      case STKWUSAP:
      {
         kwuSap = &sts->t.sts.s.kwuSap;

         /* Get Sap control block */
         /* kw005.201, modified the element of kwuSap from suId to spId */
         kwuSapCb = (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL)? 
              (KwKwuSapCb*)(gCb->u.dlCb->kwuDlSap + kwuSap->spId):
              (KwKwuSapCb*)(gCb->u.ulCb->kwuUlSap + kwuSap->spId);


         kwuSap->sduRx = kwuSapCb->sts.sduRx;
         kwuSap->sduTx = kwuSapCb->sts.sduTx;
         kwuSap->spId  = kwuSap->spId;

         if (action == LKW_ZEROSTS)
         {
            KW_MEM_SET (&kwuSapCb->sts, 0, sizeof (KwKwuSapSts));
         }
         break;
      }
      /* kw005.201 removed RGUSAP statistics support */
      case STCKWSAP:
      {
         KwCkwSapCb *sapCb;
         ckwSap = &sts->t.sts.s.ckwSap;
         if (gCb->genCfg.rlcMode == LKW_RLC_MODE_DL) 
         {
            RETVALUE(LCM_REASON_INVALID_PAR_VAL);
         }

         sapCb = &gCb->u.ulCb->ckwSap;

         ckwSap->statMsgs = sapCb->sts.statMsgs ;

         if (action == LKW_ZEROSTS)
         {
            KW_MEM_SET (&(sapCb->sts), 0, sizeof (KwCkwCntSts));
         }
         break;
      }
      default:
         RETVALUE(LCM_REASON_INVALID_ELMNT);
   }

   SGetDateTime(&sts->t.sts.dt);

   RETVALUE(LCM_REASON_NOT_APPL);
} /* kwLmmGetSapSts */


/**
 * @brief
    This function sends Unsolicited Status Indication to the Layer Management Entity. 
 *
 *  @param[in] category  Category 
 *  @param[in] event     event
 *  @param[in] cause     cause
 *  @param[in] UeId      ueId 
 *  @param[in] Qci        qci 
 *  @return  Void
 */
#ifdef LTE_L2_MEAS_RLC
#ifdef ANSI
PUBLIC Void kwLmmSendAlarm
(
KwCb     *gCb,
U16      category,  /* Category */
U16      event,     /* Alarm event */
U16      cause,     /* Alarm cause */
SuId     suId,      /* suId */
U32      ueId,      /* ueId */
U8       qci        /* qci */
)
#else
PUBLIC Void kwLmmSendAlarm(category, event, cause, suId, ueId, qci)
KwCb     *gCb;
U16      category;  /* Category */
U16      event;     /* Alarm event */
U16      cause;     /* Alarm cause */
SuId     suId;      /* suId */
U32      ueId;      /* ueId */
U8       qci;       /* qci */
#endif
#else /* LTE_L2_MEAS_RLC */
#ifdef ANSI
PUBLIC Void kwLmmSendAlarm
(
KwCb     *gCb,
U16      category,  /* Category */
U16      event,     /* Alarm event */
U16      cause,     /* Alarm cause */
SuId     suId,      /* suId */
U32      ueId       /* ueId */
)
#else
PUBLIC Void kwLmmSendAlarm(category, event, cause, suId, ueId)
KwCb     *gCb;
U16      category;  /* Category */
U16      event;     /* Alarm event */
U16      cause;     /* Alarm cause */
SuId     suId;      /* suId */
U32      ueId;      /* ueId */
#endif
#endif /* LTE_L2_MEAS_RLC */
{

   KwMngmt usta;    /* Rlc Management Structure */

   TRC2(kwLmmSendAlarm);

   if(gCb->init.usta == FALSE)
   {
      RETVOID;
   }

   /* initialize the management structure */
   KW_MEM_SET(&usta, 0, sizeof(KwMngmt));

   usta.hdr.elmId.elmnt = STGEN;
   usta.hdr.entId.ent = gCb->init.ent;
   usta.hdr.entId.inst = gCb->init.inst;

   /* fill in the event and category */
   usta.t.usta.alarm.category = category;
   usta.t.usta.alarm.event = event;
   usta.t.usta.alarm.cause = cause;

   /* set the suId and ueId */
   usta.t.usta.ueId = ueId;
   usta.t.usta.suId = suId;
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   if(event == LKW_EVT_MEAS_HALT)
   {
      usta.t.usta.qci = qci;
   }
#endif /* LTE_L2_MEAS_RLC */
   /* update the date and time */
   (Void) SGetDateTime(&usta.t.usta.alarm.dt);

   KwMiLkwStaInd(&(gCb->init.lmPst), &usta);

   RETVOID;

} /* kwLmmSendAlarm */

/**
 * @brief
    This function sends trace indication to LM 
 *
 *  @param[in] event    event
 *  @param[in] mBuf     meessage buffer
 *  @return S16
 *      -# Success : ROK 
 *      -# Failure : RFAILED 
 */
#ifdef ANSI
PUBLIC S16 kwLmmSendTrc
(
KwCb  *gCb,
Event event,                 /* event */
Buffer *mBuf                 /* message buffer */
)
#else
PUBLIC S16 kwLmmSendTrc(gCb,event, mBuf)
KwCb  *gCb;
Event event;                 /* event */
Buffer *mBuf;                /* message buffer */
#endif
{
   /* patch kw004.201 Corrected kwLmmSendTrc function definition */
   KwMngmt trc;              /* RLC management control block */
   Buffer   *dstMbuf;   
   MsgLen   bufLen;
   Data     *tempBuf;
   MsgLen   tempCnt;
   Pst      pst;

   TRC2(kwLmmSendTrc)

   KWDBGP(gCb,(KW_DBGMASK_LMM | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
         "\nkwLmmSendTrc(): Trace for event=%d, gCb->trcLen=%d",event,
   gCb->trcLen));

   cmMemset((U8 *)&trc, 0, sizeof(KwMngmt));

   pst = gCb->init.lmPst;

   trc.t.trc.event = event;
   SGetDateTime(&trc.t.trc.dt);
   trc.cfm.status = LCM_PRIM_OK;
   trc.cfm.reason = LCM_REASON_NOT_APPL;
         
   if(mBuf != NULLP)
   {
     /* Check if the whole buffer is to be sent in Trace indication */
     if(gCb->trcLen == LKW_FULL_TRACE)
     {
        if (SCpyMsgMsg(mBuf, pst.region, pst.pool, &dstMbuf)
            != ROK)
        {
           /* rg005.201 removed SPutSBuf on error */
           KWDBGP(gCb,(KW_DBGMASK_LMM | KW_DBGMASK_BRIEF),(gCb->init.prntBuf,
                 "\nkwLmmSendTrc(): SCpyMsgMsg Failed."));
           RETVALUE(RFAILED);
        }
        /* Send Trace Indication to Layer manager */
        KwMiLkwTrcInd(&pst, &trc, dstMbuf);
     }
     /* check if only a specified number of bytes are to be sent */
     else if(gCb->trcLen > 0)
     {
        /* Get the length of the recvd message buffer */
        if (SFndLenMsg(mBuf, &bufLen) != ROK)
        {
           KWDBGP(gCb,(KW_DBGMASK_LMM | KW_DBGMASK_BRIEF),(gCb->init.prntBuf, 
                    "\nkwLmmSendTrc(): SFndLenMsg Failed."));
           RETVALUE(RFAILED);
        }
        /* Check if the recvd buffer size is less than request trace len */
        if(bufLen < gCb->trcLen)
        {
           /* Copy the whole of the recvd buffer in trace indication */
      
           if (SCpyMsgMsg(mBuf, pst.region, pst.pool, &dstMbuf)
              != ROK)
           {
              KWDBGP(gCb,(KW_DBGMASK_LMM | KW_DBGMASK_BRIEF),(gCb->init.prntBuf,
                      "\nkwLmmSendTrc(): SCpyMsgMsg Failed."));
              RETVALUE(RFAILED);
           }
         
           /* Send Trace Indication to Layer manager */
           KwMiLkwTrcInd(&pst, &trc, dstMbuf);
        }
        /* if the recvd buffer size is greater than request trace len */
        if(bufLen >= gCb->trcLen)
        {
           /* Get a temporary buffer to store the msg */
           KW_ALLOC(gCb,tempBuf, gCb->trcLen);

#if (ERRCLASS & ERRCLS_INT_PAR)
           if(tempBuf == NULLP)
           {
              (Void) SPutSMem(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
      
               KWLOGERROR(gCb,ERRCLS_INT_PAR, EKWXXX, (ErrVal)0 ,
                   "kwLmmSendTrc: SGetSBuf Failed for tempBuf...!");
               RETVALUE(LCM_REASON_MEM_NOAVAIL);
           }
#endif /* ERRCLASS & ERRCLS_INT_PAR */
         
           /* Copy trcLen nos of bytes from the recvd message */
           if (SCpyMsgFix(mBuf,0,gCb->trcLen,tempBuf,&tempCnt) != ROK)   
           {
              KWDBGP(gCb,(KW_DBGMASK_LMM | KW_DBGMASK_BRIEF), 
                    (gCb->init.prntBuf,
                      "\nkwLmmSendTrc(): SCpyMsgFix Failed."));
              RETVALUE(RFAILED);
           }

           if (SGetMsg(pst.region, pst.pool, &dstMbuf) != ROK)
           {
              KWDBGP(gCb,(KW_DBGMASK_LMM | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
                      "\nkwLmmSendTrc(): dstMbuf Allocation Failed."));
              RETVALUE(RFAILED);
           }
           /* Copy the tempBuf data to dst mBuf */
           if (SCpyFixMsg(tempBuf,dstMbuf,0,gCb->trcLen,&tempCnt) != ROK)
           {
              KWDBGP(gCb,(KW_DBGMASK_LMM | KW_DBGMASK_BRIEF), 
                    (gCb->init.prntBuf,
                     "\nkwLmmSendTrc(): SCpyFixMsg Failed."));
              RETVALUE(RFAILED);
           }
  
           /* Free the memory allocated for tempBuf */
           KW_FREE(gCb,tempBuf, gCb->trcLen);
           /* Send Trace Indication to Layer manager */
           KwMiLkwTrcInd(&pst, &trc, dstMbuf);
        }
     }
   }
   else
   {
      KwMiLkwTrcInd(&pst, &trc, mBuf);
   }

   RETVALUE(ROK);
} /* end of kwLmmSendTrc */

  
/*
*
*       Fun:   Activate Task - timer
*
*       Desc:  Invoked by system services to activate a task with
*              a timer tick.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  gp_lmm.c
*
*/
 
#ifdef ANSI
PUBLIC S16 kwActvTmr
(
Ent     ent,
Inst    inst
)
#else
PUBLIC S16 kwActvTmr(ent,inst)
Ent     ent;
Inst    inst;
#endif
{
   KwCb  *gCb; 
   TRC2(kwActvTmr)

   if (inst >= KW_MAX_RLC_INSTANCES)
   {
      RETVALUE (RFAILED);
   }
   gCb = KW_GET_KWCB(inst); 
   cmPrcTmr(&(gCb->kwTqCp), gCb->kwTq, (PFV) kwTmrExpiry);

   RETVALUE(ROK);

} /* end of kwActvTmr */

/********************************************************************30**

         End of file:     kw_lmm.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:48 2014

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
/main/4      kw004.201 ap   1. Corrected kwLmmSendTrc function definition
/main/5      kw005.201 ap   1. Modified the element of kwuSap from suId to spId.
                       rd   2. Added code for populating ueId,cellId in measCb
                               from measReqEvt in KwMiLkwL2MeasReq.
                            3. Modified KwMiLkwL2MeasReq after moving measType
                               to KwL2MeasCfmEvt.
*********************************************************************91*/

