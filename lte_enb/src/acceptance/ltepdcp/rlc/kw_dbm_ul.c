

/********************************************************************20**
  
        Name:    RLC - Database module file
    
        Type:    C source file
  
        Desc:    Source code for Database Module functions such as, 

                 - kwDbmInit
                 - kwDbmDeInit
                 - kwDbmCreateRbCb
                 - kwDbmFetchRbCb 
                 - kwDbmFetchRbCbForUi
                 - kwDbmFetchRbCbForLi
                 - kwDbmUpdateRbCb
                 - kwDbmDelRbCb
                 - kwDbmDelAllRb
                 - kwDbmCreateUeCb
                 - kwDbmFetchUeCb
                 - kwDbmUpdateUeCb
                 - kwDbmDelUeCb
                 - kwDbmDelAllUe
                 - kwDbmDelMeasEvtCb
                 - kwDbmCreateCellCb
                 - kwDbmFetchCellCb
                 - kwDbmUpdateCellCb
                 - kwDbmDelCellCb
                 - kwDbmDelAllCell
                 - kwDbmShutdown

        File:    gp_dbm.c

        Sid:      kw_dbm_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:45 2014
 
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
#include "kw_err.h"        /* Err defines */
#include "kw_env.h"        /* RLC environment options */

#include "kw.h"            /* RLC defines */
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
#include "kw_ul.x"


/* local defines */

/* local externs */

/* forward references */

/* public variable declarations */

/* This structure holds all the global structs we need. */

/* private variable declarations */

/* private function declarations */

/** @file gp_dbm.c
@brief RLC Acknowledged Mode Module
**/


/**
 *
 * @brief Handler to initialize hash list
 *       
 *
 * @b Description
 *        This function is invoked by LMM to initialize the UeCb and CellCb
 *        hash List
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmUlInit
(
KwCb *gCb
)
#else
PUBLIC S16 kwDbmUlInit(gCb)
KwCb *gCb;
#endif
{
   S16      ret;              /* Return Value */

   TRC3(kwUlDbmInit)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,\
            "kwUlDbmInit()\n"));
#endif

   /* Initialize ueCb Hash List */
   ret = cmHashListInit(&(gCb->u.ulCb->ueLstCp), (U16) KW_UE_LIST_BUCKET_SIZE,
         (U16) 0, (Bool) FALSE, (U16) CM_HASH_KEYTYPE_DEF,
         KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmInit: cmHashListInit Failed for kwCb.ueLstCp.\n"));
#endif
      RETVALUE(ret);
   }

   /* Initialize cellCb Hash List */
   ret = cmHashListInit(&(gCb->u.ulCb->cellLstCp), 
                        (U16) KW_CELL_LIST_BUCKET_SIZE,
         (U16) 0, (Bool) FALSE, (U16) CM_HASH_KEYTYPE_DEF,
         KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
   if (ret != ROK)
   {
 
      cmHashListDeinit(&gCb->u.ulCb->ueLstCp);
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmInit: cmHashListInit Failed for kwCb.cellLstCp.\n"));
#endif
      RETVALUE(ret);
   }

   ret = cmHashListInit(&(gCb->u.ulCb->transIdLstCp), 
                        (U16) KW_TRANS_ID_LST_BKT_SIZE,
         (U16) 0, (Bool) FALSE, (U16) CM_HASH_KEYTYPE_DEF,
         KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
   if (ret != ROK)
   {
      cmHashListDeinit(&gCb->u.ulCb->ueLstCp);
      cmHashListDeinit(&gCb->u.ulCb->cellLstCp);
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmInit: cmHashListInit Failed for kwCb.transIdLstCp.\n"));
#endif
      RETVALUE(ret);
   }

/* kw005.201 added support for L2 Measurement */         
#ifdef LTE_L2_MEAS_RLC
   /* Initialize qcI Hash List */
   ret = cmHashListInit(&(kwCb.kwL2Cb.qciHlCp), (U16) KW_QCI_LIST_BUCKET_SIZE,
         (U16) 0, (Bool) TRUE, (U16) CM_HASH_KEYTYPE_DEF,
         kwCb.init.region, kwCb.init.pool);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmInit: cmHashListInit Failed for kwCb.qciHlCp.\n"));
#endif
      RETVALUE(ret);
   }
   
   /* Initialize tbHlCp Hash List */
   ret = cmHashListInit(&(kwCb.kwL2Cb.tbHlCp), (U16) KW_TB_LIST_BUCKET_SIZE,
         (U16) 0, (Bool) FALSE, (U16) CM_HASH_KEYTYPE_DEF,
         kwCb.init.region, kwCb.init.pool);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmInit: cmHashListInit Failed for kwCb.tbHlCp.\n"));
#endif
      RETVALUE(ret);
   }

#endif /* LTE_L2_MEAS_RLC */
   RETVALUE(ROK);
} /* kwDbmUlInit */


/**
 *
 * @brief Handler to De initialize hash list
 *       
 *
 * @b Description
 *        This function is invoked by LMM to De initialize the UeCb and CellCb
 *        hash List
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmUlDeInit
(
KwCb *gCb
)
#else
PUBLIC S16 kwDbmUlDeInit(gCb)
KwCb *gCb;
#endif
{
   S16      ret;                       /* Return Value */

   TRC3(kwUlDbmDeInit);

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,\
            "kwUlDbmDeInit()\n"));
#endif

   /* Initialize ueCb Hash List */
   ret = cmHashListDeinit(&(gCb->u.ulCb->ueLstCp));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDeInit: cmHashListDeinit Failed for kwCb.ueLstCp.\n"));
#endif
      RETVALUE(ret);
   }

   /* Initialize cellCb Hash List */
   ret = cmHashListDeinit(&(gCb->u.ulCb->cellLstCp));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDeInit: cmHashListDeinit Failed for kwCb.cellLstCp.\n"));
#endif
      RETVALUE(ret);
   }

   /* Initialize cellCb Hash List */
   ret = cmHashListDeinit(&(gCb->u.ulCb->transIdLstCp));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
            "kwDbmDeInit: cmHashListDeinit Failed for kwCb.transIdLstCp.\n"));
#endif
      RETVALUE(ret);
   }
/* kw005.201 added support for L2 Measurement */         
#ifdef LTE_L2_MEAS_RLC
   /* De Initialize qciCb Hash List */
   ret = cmHashListDeinit(&(kwCb.kwL2Cb.qciHlCp));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDeInit: cmHashListDeinit Failed for kwCb.qciHlCp.\n"));
#endif
      RETVALUE(ret);
   }
#endif /* LTE_L2_MEAS_RLC */
   RETVALUE(ROK);
} /* kwDbmDeInit */


/**
 *
 * @brief Handler to fetch rbCb in the Upper Interface
 *       
 *
 * @b Description
 *        This function is invoked by CFG to fetch rbCb from the cellCb/ueCb in
 *        the upper interface (CKW/KWU).
 *
 *  @param[in]    rlcId    RLC Identifier 
 *  @param[out]   rbCb     RB Control Block
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmFetchUlRbCbForUi
(
KwCb           *gCb,
CmLteRlcId     rlcId,      /* RLC Identifier */
KwUlRbCb         **rbCb       /* RB Cb */
)
#else
PUBLIC S16 kwDbmFetchUlRbCbForUi(gCb,rlcId, rbCb)
KwCb           *gCb;
CmLteRlcId     rlcId;      /* RLC Identifier */
KwUlRbCb         **rbCb;      /* RB Cb */
#endif
{
   KwUlUeCb      *ueCb;                  /* UE Control Block */
   KwUlCellCb    *cellCb;                /* Cell Control Block */
   KwUlRbCb      **rbCbLst;              /* RB Control Block List */
   KwUlRbCb      *tRbCb;                 /* Local RB CB */
   S16            ret;                    /* Return Value */

   TRC3(kwDbmFetchRbCbForUi)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmFetchRbCbForUi(rlcId(ueId(%d), cellId(%d), rbId(%d)),\
   rbCb)\n", rlcId.ueId, rlcId.cellId, rlcId.rbId));
#endif

   /* Validate the RBID in case of TM/UM/AM */
   KW_VALIDATE_RBID(rlcId.ueId, rlcId.rbId, rlcId.rbType, ret);
   if (ret != ROK)
   {
#ifdef DEBUGP
      /* DEBUG_PRINT EROR */
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgReEstRb -- KW_VALIDATE_RBID Failed --\
               rbId(%d), cellId(%d), ueId(%d)\n",\
               rlcId.rbId, rlcId.cellId, rlcId.ueId));

#endif
      RETVALUE(ret);
   }

   /* Check for UE CB or CELL CB */
   if (rlcId.ueId == 0)
   {
      if (kwDbmFetchUlCellCb(gCb,rlcId.cellId, &cellCb) != ROK)
      {
#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwDbmFetchUlRbCbForUi: kwDbmFetchCellCb Failed.\n"));
#endif
         RETVALUE(RFAILED);
      }

      rbCbLst = cellCb->rbCb;
      KW_DBM_FETCH_CELL_UL_RBCB(rlcId.rbId, rbCbLst, tRbCb);
   }
   else
   {
      if (kwDbmFetchUlUeCb(gCb,rlcId.ueId, rlcId.cellId, &ueCb) != ROK)
      {
#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwDbmFetchRbCbForUi: kwDbmFetchUeCb Failed.\n"));
#endif
         RETVALUE(RFAILED);
      }

      KW_DBM_FETCH_UL_RBCB(rlcId.rbId, rlcId.rbType, ueCb, tRbCb);
   }


   if (tRbCb == NULLP)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmFetchRbCbForUi: kwDbmFetchRbCb Failed.\n"));
#endif
      RETVALUE(RFAILED);
   }

   *rbCb = tRbCb;

   RETVALUE(ROK);
} /* kwDbmFetchRbCbForUi */


/**
 *
 * @brief Handler to fetch rbCb in the Upper Interface
 *       
 *
 * @b Description
 *        This function is invoked by CFG to fetch rbCb from the cellCb/ueCb in
 *        the upper interface (CKW/KWU).
 *
 *  @param[in]    cellId   -  CELL Identifier 
 *  @param[in]    ueId     -  UE Identifier 
 *  @param[in]    lcId     -  Logical Channel Identifier
 *  @param[in]    dir      -  Direction DL/UL
 *  @param[out]   rbCb     -  RB Control Block
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmFetchUlRbCbForLi
(
KwCb              *gCb,
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
CmLteLcId         lcId,       /* Logical channel instance */
U8                dir,        /* Direciotn DL/UL */
KwUlRbCb            **rbCb       /* RB Cb */
)
#else
PUBLIC S16 kwDbmFetchRbCbForLi(gCb,ueId, cellId, lcId, dir, rbCb)
KwCb              *gCb;
CmLteRnti         ueId;       /* UE Identifier */
CmLteCellId       cellId;     /* Cell Identifier */
CmLteLcId         lcId;       /* Logical channel instance */
U8                dir;        /* Direciotn DL/UL */
KwUlRbCb            **rbCb;      /* RB Cb */
#endif
{
   KwUlUeCb      *ueCb;                  /* UE Control Block */
   KwUlCellCb    *cellCb;                /* Cell Control Block */

   TRC3(kwDbmFetchUlRbCbForUi)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmFetchRbCbForLi(rlcId(ueId(%d), cellId(%d)))\n",
            ueId, cellId));
#endif

   /* Check for UE CB or CELL CB */
   if (ueId == 0)
   {
      if (kwDbmFetchUlCellCb(gCb,cellId, &cellCb) != ROK)
      {

#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwDbmFetchRbCbForLi: kwDbmFetchCellCb Failed.\n"));
#endif
         RETVALUE(RFAILED);
      }

      *rbCb = cellCb->lCh[lcId - 1].ulRbCb;
   }
   else
   {
      if (kwDbmFetchUlUeCb(gCb,ueId, cellId, &ueCb) != ROK)
      {
#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwDbmFetchRbCbForLi: kwDbmFetchUeCb Failed.\n"));
#endif
         RETVALUE(RFAILED);
      }

      *rbCb = ueCb->lCh[lcId - 1].ulRbCb;
   }

   if (*rbCb == NULLP)
   {

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmFetchRbCbForLi: RB CB is NULLP.\n"));
#endif
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* kwDbmFetchRbCbForLi */


/**
 *
 * @brief Handler to delete RbCb
 *       
 *
 * @b Description
 *        This function is invoked by CFG to remove RbCb from Ue/Cell hashlist 
 *
 *
 *  @param[in] rbCbLst   - Rb Cb List
 *  @param[in] numRbCb   - Number of rbCbs
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmDelAllUlRb
(
KwCb          *gCb,
KwUlRbCb      **rbCbLst,              /* RB Cb list */
U8             numRbCb                 /* Number of rbCbs */
)
#else
PUBLIC S16 kwDbmDelAllUlRb(gCb,rbCbLst, numRbCb)
KwCb          *gCb;
RbCb         **rbCbLst;              /* RB Cb list */
U8             numRbCb;                /* Number of rbCbs */
#endif
{
   U8          idx;                    /* Index */
   KwUlRbCb        *rbCb;                  /* RB Control Block */

   TRC3(kwDbmDelAllRb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmDelAllRb(rbCbLst, numRbCb(%d))\n", numRbCb));
#endif

   for (idx = 0; idx < numRbCb; idx++)
   {
      rbCb = rbCbLst[idx];
      if (rbCb != NULLP)
      {
/* kw005.201 added support for L2 Measurement */         
#ifdef LTE_L2_MEAS_RLC
         /* Check if measurement is running, if yes send an alarm to LM. */
         if(rbCb->kwRbCb.rbL2Cb.measOn)
         {
            KW_SEND_UEID_ALARM(rbCb->kwRbCb.ueCb->key.ueId, rbCb->kwRbCb.qci,
                          LKW_EVT_MEAS_HALT, LKW_CAUSE_RB_DELETION);
         }
         cmHashListDelete(&(kwCb.kwL2Cb.qciHlCp), (PTR)&rbCb->kwRbCb);
#endif /* LTE_L2_MEAS_RLC */
         /* Free the Buffers of RbCb */
         kwUtlFreeUlRbCb(gCb,rbCb);

         KW_FREE (gCb,rbCb, sizeof (KwUlRbCb));
#if (ERRCLASS & ERRCLS_INT_PAR)
         if (rbCb != NULLP)
         {
#ifdef DEBUGP
            KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                     "kwDbmDelAllRb: kwDbmDelRbCb Failed.\n"));
#endif
            RETVALUE(RFAILED);
         }
#endif
         rbCbLst[idx] = NULLP;
      }
   }

   RETVALUE(ROK);
} /* kwDbmDelAllRb */


/**
 *
 * @brief Handler to create an UeCb
 *       
 *
 * @b Description
 *        This function is invoked by CFG to create UeCb and insert into the Ue hashlist 
 *        of KwCb.
 *
 *
 *  @param[in] ueId     UE Identifier 
 *  @param[in] cellId   Cell Identifier 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmCreateUlUeCb
(
KwCb              *gCb,
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
KwUlUeCb         **ueCb       /* UE Control Block */
)
#else
PUBLIC S16 kwDbmCreateUlUeCb(gCb,ueId, cellId, ueCb)
KwCb              *gCb;
CmLteRnti         ueId;       /* UE Identifier */
CmLteCellId       cellId;     /* Cell Identifier */
KwUlUeCb          **ueCb;     /* UE Control Block */
#endif
{
   S16      ret;              /* Return Value */
   KwUlUeCb   *tUeCb;           /* UE Control Block */

   TRC3(kwDbmCreateUlUeCb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmCreateUlUeCb(ueId(%d), cellId(%d))\n", ueId, cellId));
#endif

   KW_ALLOC(gCb,*ueCb, sizeof(KwUlUeCb));

#if (ERRCLASS & ERRCLS_ADD_RES)
   if (*ueCb == NULLP)
   {
      ret = RFAILED;
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW023, (ErrVal) ret,
            "kwDbmCreateUeCb: UeCb allocation Failed.");
      RETVALUE(ret);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

   tUeCb = *ueCb;
   tUeCb->key.ueId = ueId;
   tUeCb->key.cellId = cellId;

   ret = cmHashListInsert(&(gCb->u.ulCb->ueLstCp), (PTR)tUeCb, (U8 *)&(tUeCb->key),
         (U16) sizeof(KwUeKey));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmCreateUeCb: cmHashListInsert Failed for ueCb.\n"));
#endif
      RETVALUE(ret);
   }
   /* kw005.201 ccpu00117318, updating the statistics */
   gCb->genSts.numUe++;


   RETVALUE(ret);
} /* kwDbmCreateUeCb */

#ifdef ANSI
PUBLIC S16 kwDbmAddUlTransIdLst
(
KwCb              *gCb,
KwCfgInfo         *cfg       /* UE Control Block */
)
#else
PUBLIC S16 kwDbmAddUlTransIdLst(gCb,cfg)
KwCb              *gCb;
KwCfgInfo         *cfg;     /* UE Control Block */
#endif
{
   S16      ret;              /* Return Value */

   TRC3(kwDbmAddUlTransIdLst)

#ifdef DEBUGP
#ifndef ALIGN_64BIT
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmAddUlTransIdLst(transId(%ld))\n", cfg->transId));
#else
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmAddUlTransIdLst(transId(%d))\n", cfg->transId));
#endif
#endif

   ret = cmHashListInsert(&(gCb->u.ulCb->transIdLstCp), (PTR)cfg, 
         (U8 *)&(cfg->transId), (U16) sizeof(cfg->transId));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmAddUlTransIdLst: cmHashListInsert Failed for transId.\n"));
#endif
      RETVALUE(ret);
   }

   RETVALUE(ret);
} /* kwDbmAddUlTransIdLst */

#ifdef ANSI
PUBLIC S16 kwDbmFindUlTransIdLst
(
KwCb              *gCb,
U32               transId,
KwCfgInfo         **cfg       /* UE Control Block */
)
#else
PUBLIC S16 kwDbmFindUlTransIdLst(gCb,cfg)
KwCb              *gCb;
U32                transId;
KwCfgInfo         *cfg;     /* UE Control Block */
#endif
{
   S16      ret;              /* Return Value */

   TRC3(kwDbmFindUlTransIdLst)

#ifdef DEBUGP
#ifndef ALIGN_64BIT
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmFindUlTransIdLst(transId(%ld))\n", transId));
#else
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmFindUlTransIdLst(transId(%d))\n", transId));
#endif
#endif

   ret = cmHashListFind(&(gCb->u.ulCb->transIdLstCp),(U8 *) &transId, 
                  sizeof (transId), KW_DEF_SEQ_NUM,(PTR *) cfg); 
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmAddUlTransIdLst: cmHashListInsert Failed for transId.\n"));
#endif
      printf("Unable to find cfginfo for transId %d\n", transId);
      exit (0);
   }

   ret = kwDbmDelUlTransIdLst(gCb, cfg);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
         "kwDbmDelAllTransIdLst: kwDbmDelTransIdLst Failed.\n"));
#endif
      RETVALUE(ret);
   }

   RETVALUE(ret);
} /* kwDbmAddUlTransIdLst */

#ifdef ANSI
PUBLIC S16 kwDbmDelUlTransIdLst
(
KwCb              *gCb,
KwCfgInfo         **cfg       /* UE Control Block */
)
#else
PUBLIC S16 kwDbmDlUlTransIdLst(gCb,cfg)
KwCb              *gCb;
KwCfgInfo         **cfg;     /* UE Control Block */
#endif
{
   S16      ret;              /* Return Value */

   TRC3(kwDbmDelUlTransIdLst)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmFindUlTransIdLst(transId()\n" ));
#endif

   ret = cmHashListDelete(&(gCb->u.ulCb->transIdLstCp),(PTR) (*cfg)); 
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmAddUlTransIdLst: cmHashListInsert Failed for transId.\n"));
#endif
   }

   RETVALUE(ret);
} /* kwDbmAddUlTransIdLst */

#ifdef ANSI
PUBLIC S16 kwDbmDelAllUlTransIdLst
(
KwCb              *gCb
)
#else
PUBLIC S16 kwDbmDlUlTransIdLst(gCb)
KwCb              *gCb;
#endif
{
   S16      ret;              /* Return Value */
   KwCfgInfo *cfg;

   TRC3(kwDbmDelAllUlTransIdLst)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmFindUlTransIdLst"));
#endif
   /* Until no more ueCb is ueLstCp hash list get and delete ueCb */
   while (cmHashListGetNext(&(gCb->u.ulCb->transIdLstCp), 
               (PTR) cfg, (PTR *)&cfg) == ROK)

   {
      /* Delete ueCb */
      ret = kwDbmDelUlTransIdLst(gCb,&cfg);
      if (ret != ROK)
      {
#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwDbmDelAllTransIdLst: kwDbmDelTransIdLst Failed.\n"));
#endif
         RETVALUE(ret);
      }
      
      cfg = NULLP;
   }

   RETVALUE(ret);
} /* kwDbmAddUlTransIdLst */




/**
 *
 * @brief Handler to Fetch an UeCb
 *       
 *
 * @b Description
 *        This function is invoked by CFG to fetch UeCb from the Ue hashlist 
 *        of KwCb.
 *
 *
 *  @param[in]    ueId     UE Identifier 
 *  @param[in]    cellId   Cell Identifier 
 *  @param[out]   ueCb     UE Control Block
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmFetchUlUeCb
(
KwCb              *gCb,
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
KwUlUeCb            **ueCb       /* UE Control Block */
)
#else
PUBLIC S16 kwDbmFetchUeCb(gCb,ueId, cellId, ueCb)
KwCb              *gCb;
CmLteRnti         ueId;       /* UE Identifier */
CmLteCellId       cellId;     /* Cell Identifier */
KwUlUeCb            **ueCb;      /* UE Control Block */
#endif
{
   S16      ret;              /* Return Value */
   KwUeKey  key;              /* Key for UE Hash List */

   TRC3(kwDbmFetchUlUeCb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmFetchUlUeCb(ueId(%d), cellId(%d))\n", ueId, cellId));
#endif

   key.ueId = ueId;
   key.cellId = cellId;

   ret = cmHashListFind(&(gCb->u.ulCb->ueLstCp), (U8 *)&(key), sizeof(KwUeKey),
         KW_DEF_SEQ_NUM, (PTR *) ueCb);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmFetchUeCb: cmHashListFind Failed for ueCb.\n"));
#endif
      RETVALUE(ret);
   }

   RETVALUE(ROK);
} /* kwDbmFetchUeCb */


/**
 *
 * @brief Handler to delete an UeCb
 *       
 *
 * @b Description
 *        This function is invoked by CFG to delete UeCb from the Ue hashlist 
 *        of KwCb.
 *
 *
 *  @param[in] ueCb     UE Control Block
 *  @param[in] abrtFlag Abort Flag
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmDelUlUeCb
(
KwCb        *gCb,
KwUlUeCb      *ueCb,       /* UE Identifier */
Bool        abortFlag    /* Abort Flag */
)
#else
PUBLIC S16 kwDbmDelUlUeCb(gCb,eCb, abortFlag)
KwCb        *gCb;
KwUlUeCb      *ueCb;       /* UE Identifier */
Bool        abortFlag;   /* Abort Flag */
#endif
{
   S16         ret;      /* Return Value */
   U8          idx;      /* Index */
/* kw005.201 Added isLogicalChAvailable flag */

   TRC3(kwDbmDelUlUeCb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmDelUlUeCb(ueId(%d), cellId(%d))\n",
            ueCb->key.ueId, ueCb->key.cellId));
#endif

#if  (!defined(KW_PDCP) || !(defined(PJ_SEC_ASYNC) || defined(PJ_CMP_ASYNC)))
   UNUSED(abortFlag);
#endif /* (!defined(KW_PDCP) || ! (defined(PJ_SEC_ASYNC) || defined(PJ_CMP_ASYNC)))*/

/* kw005.201 Check to see if there is atleast one logical channel */

   /* Delete all logical channels */
   for (idx = 0; idx < KW_MAX_LCH_PER_UE; idx++)
   {
      ueCb->lCh[idx].ulRbCb = NULLP;
   }


   /* Delete all SRB RbCbs in UeCb */
   ret = kwDbmDelAllUlRb(gCb,ueCb->srbCb, KW_MAX_SRB_PER_UE);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDelUeCb: kwDbmDelAllRb Failed for ueCb.\n"));
#endif
   }

   /* Delete all DRB RbCbs in UeCb */
   ret = kwDbmDelAllUlRb(gCb,ueCb->drbCb, KW_MAX_DRB_PER_UE);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDelUeCb: kwDbmDelAllRb Failed for ueCb.\n"));
#endif
   }


   /* Delete ueCb entry from ueLstCp */
   ret = cmHashListDelete(&(gCb->u.ulCb->ueLstCp), (PTR) ueCb);
   if (ret != ROK)
   {

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDelUeCb: cmHashListDelete Failed for ueCb.\n"));
#endif
   }
   /* kw005.201 ccpu00117318, updating the statistics */
   gCb->genSts.numUe--;
   /* Deallocate ueCb */
   KW_FREE(gCb,ueCb, sizeof(KwUlUeCb));

   RETVALUE(ret);
} /* kwDbmDelUeCb */


/**
 *
 * @brief Handler to delete all UeCbs
 *       
 *
 * @b Description
 *        This function is invoked by CFG to delete all UeCbs from the Ue
 *        hashlist of KwCb.
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmDelAllUlUe
(
KwCb  *gCb
)
#else
PUBLIC S16 kwDbmDelAllUlUe(gCb)
KwCb  *gCb;
#endif
{
   S16         ret;              /* Return Value */
   KwUlUeCb      *ueCb;            /* UE Control Block */

   TRC3(kwDbmDelAllUlUe)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmDelAllUlUe()\n"));
#endif

   ret = ROK;

   /* Until no more ueCb is ueLstCp hash list get and delete ueCb */
   while (cmHashListGetNext(&(gCb->u.ulCb->ueLstCp), (PTR) ueCb, (PTR *)&ueCb) == ROK)
   {
      /* Delete ueCb */
      ret = kwDbmDelUlUeCb(gCb,ueCb, TRUE);
      if (ret != ROK)
      {
#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwDbmDelAllUe: kwDbmDelUeCb Failed.\n"));
#endif
         RETVALUE(ret);
      }
      ueCb = NULLP;
   }

   RETVALUE(ret);
} /* kwDbmDelAllUe */
/* kw005.201 added support for L2 Measurement */         
#ifdef LTE_L2_MEAS_RLC

/**
 *
 * @brief Handler to delete all MeasEvtCb
 *       
 *
 * @b Description
 *        This function is invoked by CFG to delete all MeasEvtCb from the KwCb
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmDelMeasEvtCb
(
)
#else
PUBLIC S16 kwDbmDelMeasEvtCb()
#endif
{
   U8             evtIdx;
   KwL2MeasEvtCb  *measEvtCb;

   TRC3(kwDbmDelMeasEvtCb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmDelMeasEvtCb()\n"));
#endif

   for(evtIdx = 0; evtIdx < LKW_MAX_L2MEAS; evtIdx++)
   {
      if(kwCb.kwL2Cb.kwL2EvtCb[evtIdx] != NULLP)
      {
         measEvtCb = kwCb.kwL2Cb.kwL2EvtCb[evtIdx];
         kwStopTmr((PTR)measEvtCb, KW_EVT_L2_TMR);
         kwCb.kwL2Cb.kwL2EvtCb[evtIdx] = NULLP;
         kwCb.kwL2Cb.kwNumMeas--;
         KW_FREE(gCb,measEvtCb, sizeof(KwL2MeasEvtCb));
      }
   }

   RETVALUE(ROK);
} /* kwDbmDelMeasEvtCb */
#endif /* LTE_L2_MEAS_RLC */

/**
 *
 * @brief Handler to create CellCb
 *       
 *
 * @b Description
 *        This function is invoked by CFG to create CellCb and insert into the Cell hashlist 
 *        of KwCb.
 *
 *
 *  @param[in] cellId   Cell Identifier 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmCreateUlCellCb
(
KwCb              *gCb,
CmLteCellId       cellId,     /* Cell Identifier */
KwUlCellCb          **cellCb    /* UE Control Block */
)
#else
PUBLIC S16 kwDbmCreateUlCellCb(gCb,cellId, cellCb)
KwCb              *gCb;
CmLteCellId       cellId;     /* Cell Identifier */
KwUlCellCb          **cellCb;   /* UE Control Block */
#endif
{
   S16         ret;           /* Return Value */
   KwUlCellCb    *tCellCb;      /* UE Control Block */

   TRC3(kwDbmCreateCellCb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmCreateCellCb(cellId(%d))\n", cellId));
#endif

   KW_ALLOC(gCb,*cellCb, sizeof(KwUlCellCb));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (*cellCb == NULLP)
   {
      ret = RFAILED;
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW024, (ErrVal) ret,
            "kwDbmCreateUeCb: CellCb allocation Failed.");
      RETVALUE(ret);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

   tCellCb = *cellCb;
   tCellCb->cellId = cellId;

   ret = cmHashListInsert(&(gCb->u.ulCb->cellLstCp), (PTR) tCellCb,
         (U8 *)&(tCellCb->cellId), (U16) sizeof(CmLteCellId));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmCreateCellCb: cmHashListInsert Failed for cellCb.\n"));
#endif
      RETVALUE(ret);
   }

   RETVALUE(ret);
} /* kwDbmCreateCellCb */


/**
 *
 * @brief Handler to Fetch an CellCb
 *       
 *
 * @b Description
 *        This function is invoked by CFG to fetch UeCb from the Ue hashlist 
 *        of KwCb.
 *
 *
 *  @param[in]    ueId     UE Identifier 
 *  @param[in]    cellId   Cell Identifier 
 *  @param[out]   cellCb     UE Control Block
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmFetchUlCellCb
(
KwCb              *gCb,
CmLteCellId       cellId,     /* Cell Identifier */
KwUlCellCb          **cellCb     /* Cell Control Block */
)
#else
PUBLIC S16 kwDbmFetchUlCellCb(gCb,cellId, cellCb)
KwCb              *gCb;
CmLteCellId       cellId;     /* Cell Identifier */
KwUlCellCb          **cellCb;    /* Cell Control Block */
#endif
{
   S16            ret;              /* Return Value */

   TRC3(kwDbmFetchUlCellCb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmFetchUlCellCb(cellId(%d))\n", cellId));
#endif

   ret = cmHashListFind(&(gCb->u.ulCb->cellLstCp), (U8 *)&(cellId),
         sizeof(CmLteCellId), KW_DEF_SEQ_NUM, (PTR*) cellCb);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmFetchCellCb: cmHashListFind Failed for cellCb.\n"));
#endif
      RETVALUE(ret);
   }

   RETVALUE(ROK);
} /* kwDbmFetchCellCb */


/**
 *
 * @brief Handler to delete CellCb
 *       
 *
 * @b Description
 *        This function is invoked by CFG to delete CellCb from the Cell hashlist 
 *        of KwCb.
 *
 *
 *  @param[in] cellCb   Cell Control Block
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmDelUlCellCb
(
KwCb          *gCb,
KwUlCellCb    *cellCb      /* Cell Control Block */
)
#else
PUBLIC S16 kwDbmDelUlCellCb(gCb,cellCb)
KwCb          *gCb;
KwCellCb    *cellCb;     /* Cell Control Block */
#endif
{
   S16         ret;              /* Return Value */

   TRC3(kwDbmDelUlCellCb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmDelUlCellCb(cellId(%d))\n", cellCb->cellId));
#endif

   ret = ROK;

   /* Delete all rbCbs in cellCb */
   ret = kwDbmDelAllUlRb(gCb,cellCb->rbCb, KW_MAX_RB_PER_CELL);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDelCellCb: kwDbmDelAllRb Failed for cellCb.\n"));
#endif
   }

   /* Delete cellCb entry in hash list cellLstCp */
   ret = cmHashListDelete(&(gCb->u.ulCb->cellLstCp), (PTR) cellCb);
   if (ret != ROK)
   {
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDelCellCb: cmHashListDelete Failed for cellCb.\n"));
   }

   /* Deallocate cellCb */
   KW_FREE(gCb,cellCb, sizeof(KwUlCellCb));

   RETVALUE(ret);
} /* kwDbmDelCellCb */


/**
 *
 * @brief Handler to delete all UeCbs
 *       
 *
 * @b Description
 *        This function is invoked by CFG to delete all UeCbs from the Ue
 *        hashlist of KwCb.
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmDelAllUlCell
(
   KwCb *gCb
)
#else
PUBLIC S16 kwDbmDelAllUlCell(gCb)
KwCb *gCb;
#endif
{
   S16         ret;              /* Return Value */
   KwUlCellCb    *cellCb;          /* Cell Control Block */

   TRC3(kwDbmDelAllUlCell)

   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmDelAllCell()\n"));

   ret = ROK;
   cellCb = NULLP;

   /* Until no more cellCb is ueLstCp hash list get and delete cellCb */
   while (cmHashListGetNext(&(gCb->u.ulCb->cellLstCp), (PTR) cellCb, (PTR *)&cellCb) == ROK)
   {
      /* Delete cellCb */
      ret = kwDbmDelUlCellCb(gCb,cellCb);
      if (ret != ROK)
      {
         KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwDbmDelAllUlCell: kwDbmDelCellCb Failed.\n"));
         RETVALUE(ret);
      }

      cellCb = NULLP;
   }

   RETVALUE(ret);
} /* kwDbmDelAllCell */


/**
 *
 * @brief Handler to delete all UeCbs and CellCbs
 *       
 *
 * @b Description
 *        This function is invoked by LMM to delete all UeCbs from the Ue
 *        hashlist of KwCb and cellCbs from the Cell hashlist of kwCb.
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC S16 kwDbmUlShutdown
(
KwCb *gCb
)
#else
PUBLIC S16 kwDbmUlShutdown(gCb)
KwCb *gCb;
#endif
{
   S16 ret;

   TRC3(kwDbmUlShutdown)

   ret = kwDbmDelAllUlCell(gCb);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      KWLOGERROR(gCb,ERRCLS_DEBUG, EKW025, (ErrVal) ret,
               "kwDbmShutdown: kwDbmDelAllCell Failed.\n");
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */
/* kw005.201 added support for L2 Measurement */         
#ifdef LTE_L2_MEAS_RLC
   ret = kwDbmDelMeasEvtCb();
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      KWLOGERROR(gCb,ERRCLS_DEBUG, EKWXXX, (ErrVal) ret,
               "kwDbmShutdown: kwDbmDelMeasEvtCb Failed.\n");
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */
#endif /* LTE_L2_MEAS_RLC */
   ret = kwDbmDelAllUlUe(gCb);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW026, (ErrVal) ret,
               "kwDbmShutdown: kwDbmDelAllUe Failed.\n");
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */
   ret = kwDbmUlDeInit(gCb);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW027, (ErrVal) ret,
               "kwDbmShutdown: kwDbmDeInit Failed.\n");
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */

   RETVALUE(ROK);
} /* kwDbmShutdown */


/********************************************************************30**
  
         End of file:     kw_dbm_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:45 2014
  
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
/main/1      ---      gk     1. Initial release.
/main/2      ---      nm     1. LTERLC Release 2.1
/main/3      kw005.201 ap    1. Updating the statistics.
                             2. Added support for L2 Measurement.
/main/4      kw005.201 rd    3. Added code for deleting the KwRbCb entry
                                from the qciHlCp when all RBs are deleted
                                in function kwDbmDelAllRb.
                             4. Updated with important Avtecs comments.
*********************************************************************91*/

