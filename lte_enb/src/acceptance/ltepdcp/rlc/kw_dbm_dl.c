

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

        Sid:      kw_dbm_dl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:44 2014
 
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
PUBLIC S16 kwDbmDlInit
(
KwCb *gCb
)
#else
PUBLIC S16 kwDbmDlInit(gCb)
KwCb *gCb;
#endif
{
   S16      ret;              /* Return Value */

   TRC3(kwDlDbmInit)

#ifdef DEBUGP
   KWDBGP(gCb, (KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,\
            "kwDlDbmInit()\n"));
#endif

   /* Initialize ueCb Hash List */
   ret = cmHashListInit(&(gCb->u.dlCb->ueLstCp), (U16) KW_UE_LIST_BUCKET_SIZE,
         (U16) 0, (Bool) FALSE, (U16) CM_HASH_KEYTYPE_DEF,
         KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmInit: cmHashListInit Failed for kwCb.ueLstCp.\n"));
#endif
      RETVALUE(ret);
   }

   /* Initialize cellCb Hash List */
   ret = cmHashListInit(&(gCb->u.dlCb->cellLstCp), (U16) KW_CELL_LIST_BUCKET_SIZE,
         (U16) 0, (Bool) FALSE, (U16) CM_HASH_KEYTYPE_DEF,
         KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmInit: cmHashListInit Failed for kwCb.cellLstCp.\n"));
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
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
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
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmInit: cmHashListInit Failed for kwCb.tbHlCp.\n"));
#endif
      RETVALUE(ret);
   }

#endif /* LTE_L2_MEAS */
   RETVALUE(ROK);
} /* kwDbmDlInit */


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
PUBLIC S16 kwDbmDlDeInit
(
KwCb *gCb
)
#else
PUBLIC S16 kwDbmDlDeInit(gCb)
KwCb *gCb;
#endif
{
   S16      ret;                       /* Return Value */

   TRC3(kwDlDbmDeInit);

#ifdef DEBUGP
   KWDBGP(gCb, (KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,\
            "kwDlDbmDeInit()\n"));
#endif

   /* Initialize ueCb Hash List */
   ret = cmHashListDeinit(&(gCb->u.dlCb->ueLstCp));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDeInit: cmHashListDeinit Failed for kwCb.ueLstCp.\n"));
#endif
      RETVALUE(ret);
   }

   /* Initialize cellCb Hash List */
   ret = cmHashListDeinit(&(gCb->u.dlCb->cellLstCp));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDeInit: cmHashListDeinit Failed for kwCb.cellLstCp.\n"));
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
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDeInit: cmHashListDeinit Failed for kwCb.qciHlCp.\n"));
#endif
      RETVALUE(ret);
   }
#endif /* LTE_L2_MEAS */
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
PUBLIC S16 kwDbmFetchDlRbCbForUi
(
KwCb           *gCb,
CmLteRlcId     rlcId,      /* RLC Identifier */
KwDlRbCb         **rbCb       /* RB Cb */
)
#else
PUBLIC S16 kwDbmFetchDlRbCbForUi(gCb,rlcId, rbCb)
KwCb           *gCb;
CmLteRlcId     rlcId;      /* RLC Identifier */
KwDlRbCb         **rbCb;      /* RB Cb */
#endif
{
   KwDlUeCb      *ueCb;                  /* UE Control Block */
   KwDlCellCb    *cellCb;                /* Cell Control Block */
   KwDlRbCb      **rbCbLst;              /* RB Control Block List */
   KwDlRbCb      *tRbCb;                 /* Local RB CB */
   S16            ret;                    /* Return Value */

   TRC3(kwDbmFetchRbCbForUi)

#ifdef DEBUGP
   KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmFetchRbCbForUi(rlcId(ueId(%d), cellId(%d), rbId(%d)),\
   rbCb)\n", rlcId.ueId, rlcId.cellId, rlcId.rbId));
#endif

   /* Validate the RBID in case of TM/UM/AM */
   KW_VALIDATE_RBID(rlcId.ueId, rlcId.rbId, rlcId.rbType, ret);
   if (ret != ROK)
   {
#ifdef DEBUGP
      /* DEBUG_PRINT EROR */
      KWDBGP(gCb, (KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgReEstRb -- KW_VALIDATE_RBID Failed --\
               rbId(%d), cellId(%d), ueId(%d)\n",\
               rlcId.rbId, rlcId.cellId, rlcId.ueId));

#endif
      RETVALUE(ret);
   }

   /* Check for UE CB or CELL CB */
   if (rlcId.ueId == 0)
   {
      if (kwDbmFetchDlCellCb(gCb,rlcId.cellId, &cellCb) != ROK)
      {
#ifdef DEBUGP
         KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwDbmFetchDlRbCbForUi: kwDbmFetchCellCb Failed.\n"));
#endif
         RETVALUE(RFAILED);
      }

      rbCbLst = cellCb->rbCb;
      KW_DBM_FETCH_CELL_DL_RBCB(rlcId.rbId, rbCbLst, tRbCb);
   }
   else
   {
      if (kwDbmFetchDlUeCb(gCb,rlcId.ueId, rlcId.cellId, &ueCb) != ROK)
      {
#ifdef DEBUGP
         KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwDbmFetchRbCbForUi: kwDbmFetchUeCb Failed.\n"));
#endif
         RETVALUE(RFAILED);
      }

      KW_DBM_FETCH_DL_RBCB(rlcId.rbId, rlcId.rbType, ueCb, tRbCb);
   }


   if (tRbCb == NULLP)
   {
#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
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
PUBLIC S16 kwDbmFetchDlRbCbForLi
(
KwCb              *gCb,
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
CmLteLcId         lcId,       /* Logical channel instance */
U8                dir,        /* Direciotn DL/UL */
KwDlRbCb            **rbCb       /* RB Cb */
)
#else
PUBLIC S16 kwDbmFetchRbCbForLi(gCb,ueId, cellId, lcId, dir, rbCb)
KwCb              *gCb;
CmLteRnti         ueId;       /* UE Identifier */
CmLteCellId       cellId;     /* Cell Identifier */
CmLteLcId         lcId;       /* Logical channel instance */
U8                dir;        /* Direciotn DL/UL */
KwDlRbCb            **rbCb;      /* RB Cb */
#endif
{
   KwDlUeCb      *ueCb;                  /* UE Control Block */
   KwDlCellCb    *cellCb;                /* Cell Control Block */

   TRC3(kwDbmFetchDlRbCbForUi)

#ifdef DEBUGP
   KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmFetchRbCbForLi(rlcId(ueId(%d), cellId(%d)))\n",
            ueId, cellId));
#endif

   /* Check for UE CB or CELL CB */
   if (ueId == 0)
   {
      if (kwDbmFetchDlCellCb(gCb,cellId, &cellCb) != ROK)
      {

#ifdef DEBUGP
         KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwDbmFetchRbCbForLi: kwDbmFetchCellCb Failed.\n"));
#endif
         RETVALUE(RFAILED);
      }

      *rbCb = cellCb->lCh[lcId - 1].dlRbCb;
   }
   else
   {
      if (kwDbmFetchDlUeCb(gCb,ueId, cellId, &ueCb) != ROK)
      {
#ifdef DEBUGP
         KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwDbmFetchRbCbForLi: kwDbmFetchUeCb Failed.\n"));
#endif
         RETVALUE(RFAILED);
      }

      *rbCb = ueCb->lCh[lcId - 1].dlRbCb;
   }

   if (*rbCb == NULLP)
   {

#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
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
PUBLIC S16 kwDbmDelAllDlRb
(
KwCb          *gCb,
KwDlRbCb      **rbCbLst,              /* RB Cb list */
U8             numRbCb                 /* Number of rbCbs */
)
#else
PUBLIC S16 kwDbmDelAllRb(gCb,rbCbLst, numRbCb)
KwCb          *gCb;
RbCb         **rbCbLst;              /* RB Cb list */
U8             numRbCb;                /* Number of rbCbs */
#endif
{
   U8          idx;                    /* Index */
   KwDlRbCb        *rbCb;                  /* RB Control Block */

   TRC3(kwDbmDelAllRb)

#ifdef DEBUGP
   KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
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
#endif /* LTE_L2_MEAS */
         /* Free the Buffers of RbCb */
         kwUtlFreeDlRbCb(gCb,rbCb);

         KW_FREE (gCb,rbCb, sizeof (KwDlRbCb));
#if (ERRCLASS & ERRCLS_INT_PAR)
         if (rbCb != NULLP)
         {
#ifdef DEBUGP
            KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
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
PUBLIC S16 kwDbmCreateDlUeCb
(
KwCb              *gCb,
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
KwDlUeCb         **ueCb       /* UE Control Block */
)
#else
PUBLIC S16 kwDbmCreateDlUeCb(gCb,ueId, cellId, ueCb)
KwCb              *gCb;
CmLteRnti         ueId;       /* UE Identifier */
CmLteCellId       cellId;     /* Cell Identifier */
KwDlUeCb          **ueCb;     /* UE Control Block */
#endif
{
   S16      ret;              /* Return Value */
   KwDlUeCb   *tUeCb;           /* UE Control Block */

   TRC3(kwDbmCreateDlUeCb)

#ifdef DEBUGP
   KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmCreateDlUeCb(ueId(%d), cellId(%d))\n", ueId, cellId));
#endif

   KW_ALLOC(gCb,*ueCb, sizeof(KwDlUeCb));

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

   ret = cmHashListInsert(&(gCb->u.dlCb->ueLstCp), (PTR)tUeCb, (U8 *)&(tUeCb->key),
         (U16) sizeof(KwUeKey));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmCreateUeCb: cmHashListInsert Failed for ueCb.\n"));
#endif
      RETVALUE(ret);
   }
   /* kw005.201 ccpu00117318, updating the statistics */
   gCb->genSts.numUe++;


   RETVALUE(ret);
} /* kwDbmCreateUeCb */


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
PUBLIC S16 kwDbmFetchDlUeCb
(
KwCb              *gCb,
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
KwDlUeCb            **ueCb       /* UE Control Block */
)
#else
PUBLIC S16 kwDbmFetchUeCb(gCb,ueId, cellId, ueCb)
KwCb              *gCb;
CmLteRnti         ueId;       /* UE Identifier */
CmLteCellId       cellId;     /* Cell Identifier */
KwDlUeCb            **ueCb;      /* UE Control Block */
#endif
{
   S16      ret;              /* Return Value */
   KwUeKey  key;              /* Key for UE Hash List */

   TRC3(kwDbmFetchDlUeCb)

#ifdef DEBUGP
   KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmFetchDlUeCb(ueId(%d), cellId(%d))\n", ueId, cellId));
#endif

   key.ueId = ueId;
   key.cellId = cellId;

   ret = cmHashListFind(&(gCb->u.dlCb->ueLstCp), (U8 *)&(key), sizeof(KwUeKey),
         KW_DEF_SEQ_NUM, (PTR *) ueCb);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
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
PUBLIC S16 kwDbmDelDlUeCb
(
KwCb        *gCb,
KwDlUeCb      *ueCb,       /* UE Identifier */
Bool        abortFlag    /* Abort Flag */
)
#else
PUBLIC S16 kwDbmDelDlUeCb(gCb,eCb, abortFlag)
KwCb        *gCb;
KwDlUeCb      *ueCb;       /* UE Identifier */
Bool        abortFlag;   /* Abort Flag */
#endif
{
   S16         ret;      /* Return Value */
   U8          idx;      /* Index */
/* kw005.201 Added isLogicalChAvailable flag */

   TRC3(kwDbmDelDlUeCb)

#ifdef DEBUGP
   KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmDelDlUeCb(ueId(%d), cellId(%d))\n",
            ueCb->key.ueId, ueCb->key.cellId));
#endif

#if  (!defined(KW_PDCP) || !(defined(PJ_SEC_ASYNC) || defined(PJ_CMP_ASYNC)))
   UNUSED(abortFlag);
#endif /* (!defined(KW_PDCP) || ! (defined(PJ_SEC_ASYNC) || defined(PJ_CMP_ASYNC)))*/

/* kw005.201 Check to see if there is atleast one logical channel */

   /* Delete all logical channels */
   for (idx = 0; idx < KW_MAX_LCH_PER_UE; idx++)
   {
      ueCb->lCh[idx].dlRbCb = NULLP;
   }


   /* Delete all SRB RbCbs in UeCb */
   ret = kwDbmDelAllDlRb(gCb,ueCb->srbCb, KW_MAX_SRB_PER_UE);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDelUeCb: kwDbmDelAllRb Failed for ueCb.\n"));
#endif
   }

   /* Delete all DRB RbCbs in UeCb */
   ret = kwDbmDelAllDlRb(gCb,ueCb->drbCb, KW_MAX_DRB_PER_UE);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDelUeCb: kwDbmDelAllRb Failed for ueCb.\n"));
#endif
   }


   /* Delete ueCb entry from ueLstCp */
   ret = cmHashListDelete(&(gCb->u.dlCb->ueLstCp), (PTR) ueCb);
   if (ret != ROK)
   {

#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDelUeCb: cmHashListDelete Failed for ueCb.\n"));
#endif
   }
   /* kw005.201 ccpu00117318, updating the statistics */
   gCb->genSts.numUe--;
   /* Deallocate ueCb */
   KW_FREE(gCb,ueCb, sizeof(KwDlUeCb));

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
PUBLIC S16 kwDbmDelAllDlUe
(
KwCb  *gCb
)
#else
PUBLIC S16 kwDbmDelAllDlUe(gCb)
KwCb  *gCb;
#endif
{
   S16         ret;              /* Return Value */
   KwDlUeCb      *ueCb;            /* UE Control Block */

   TRC3(kwDbmDelAllDlUe)

#ifdef DEBUGP
   KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmDelAllDlUe()\n"));
#endif

   ret = ROK;

   /* Until no more ueCb is ueLstCp hash list get and delete ueCb */
   while (cmHashListGetNext(&(gCb->u.dlCb->ueLstCp), (PTR) ueCb, (PTR *)&ueCb) == ROK)
   {
      /* Delete ueCb */
      ret = kwDbmDelDlUeCb(gCb,ueCb, TRUE);
      if (ret != ROK)
      {
#ifdef DEBUGP
         KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
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
   KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
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
         KW_FREE(measEvtCb, sizeof(KwL2MeasEvtCb));
      }
   }

   RETVALUE(ROK);
} /* kwDbmDelMeasEvtCb */
#endif /* LTE_L2_MEAS */

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
PUBLIC S16 kwDbmCreateDlCellCb
(
KwCb              *gCb,
CmLteCellId       cellId,     /* Cell Identifier */
KwDlCellCb          **cellCb    /* UE Control Block */
)
#else
PUBLIC S16 kwDbmCreateDlCellCb(gCb,cellId, cellCb)
KwCb              *gCb;
CmLteCellId       cellId;     /* Cell Identifier */
KwDlCellCb          **cellCb;   /* UE Control Block */
#endif
{
   S16         ret;           /* Return Value */
   KwDlCellCb    *tCellCb;      /* UE Control Block */

   TRC3(kwDbmCreateCellCb)

#ifdef DEBUGP
   KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmCreateCellCb(cellId(%d))\n", cellId));
#endif

   KW_ALLOC(gCb,*cellCb, sizeof(KwDlCellCb));
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

   ret = cmHashListInsert(&(gCb->u.dlCb->cellLstCp), (PTR) tCellCb,
         (U8 *)&(tCellCb->cellId), (U16) sizeof(CmLteCellId));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
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
PUBLIC S16 kwDbmFetchDlCellCb
(
KwCb              *gCb,
CmLteCellId       cellId,     /* Cell Identifier */
KwDlCellCb          **cellCb     /* Cell Control Block */
)
#else
PUBLIC S16 kwDbmFetchDlCellCb(gCb,cellId, cellCb)
KwCb              *gCb;
CmLteCellId       cellId;     /* Cell Identifier */
KwDlCellCb          **cellCb;    /* Cell Control Block */
#endif
{
   S16            ret;              /* Return Value */

   TRC3(kwDbmFetchDlCellCb)

#ifdef DEBUGP
   KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmFetchDlCellCb(cellId(%d))\n", cellId));
#endif

   ret = cmHashListFind(&(gCb->u.dlCb->cellLstCp), (U8 *)&(cellId),
         sizeof(CmLteCellId), KW_DEF_SEQ_NUM, (PTR*) cellCb);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
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
PUBLIC S16 kwDbmDelDlCellCb
(
KwCb          *gCb,
KwDlCellCb    *cellCb      /* Cell Control Block */
)
#else
PUBLIC S16 kwDbmDelDlCellCb(gCb,cellCb)
KwCb          *gCb;
KwCellCb    *cellCb;     /* Cell Control Block */
#endif
{
   S16         ret;              /* Return Value */

   TRC3(kwDbmDelDlCellCb)

#ifdef DEBUGP
   KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmDelDlCellCb(cellId(%d))\n", cellCb->cellId));
#endif

   ret = ROK;

   /* Delete all rbCbs in cellCb */
   ret = kwDbmDelAllDlRb(gCb,cellCb->rbCb, KW_MAX_RB_PER_CELL);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDelCellCb: kwDbmDelAllRb Failed for cellCb.\n"));
#endif
   }

   /* Delete cellCb entry in hash list cellLstCp */
   ret = cmHashListDelete(&(gCb->u.dlCb->cellLstCp), (PTR) cellCb);
   if (ret != ROK)
   {
      KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwDbmDelCellCb: cmHashListDelete Failed for cellCb.\n"));
   }

   /* Deallocate cellCb */
   KW_FREE(gCb,cellCb, sizeof(KwDlCellCb));

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
PUBLIC S16 kwDbmDelAllDlCell
(
   KwCb *gCb
)
#else
PUBLIC S16 kwDbmDelAllDlCell(gCb)
KwCb *gCb;
#endif
{
   S16         ret;              /* Return Value */
   KwDlCellCb    *cellCb;          /* Cell Control Block */

   TRC3(kwDbmDelAllDlCell)

   KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,
            "kwDbmDelAllCell()\n"));

   ret = ROK;
   cellCb = NULLP;

   /* Until no more cellCb is ueLstCp hash list get and delete cellCb */
   while (cmHashListGetNext(&(gCb->u.dlCb->cellLstCp), (PTR) cellCb, (PTR *)&cellCb) == ROK)
   {
      /* Delete cellCb */
      ret = kwDbmDelDlCellCb(gCb,cellCb);
      if (ret != ROK)
      {
         KWDBGP(gCb, (KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwDbmDelAllDlCell: kwDbmDelCellCb Failed.\n"));
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
PUBLIC S16 kwDbmDlShutdown
(
KwCb *gCb
)
#else
PUBLIC S16 kwDbmDlShutdown(gCb)
KwCb *gCb;
#endif
{
   S16 ret;

   TRC3(kwDbmDlShutdown)

   ret = kwDbmDelAllDlCell(gCb);
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
#endif /* LTE_L2_MEAS */
   ret = kwDbmDelAllDlUe(gCb);
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      KWLOGERROR(gCb,ERRCLS_INT_PAR, EKW026, (ErrVal) ret,
               "kwDbmShutdown: kwDbmDelAllUe Failed.\n");
   }
#endif /* ERRCLASS & ERRCLS_DEBUG */
   ret = kwDbmDlDeInit(gCb);
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
  
         End of file:     kw_dbm_dl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:44 2014
  
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

