

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

        Sid:      kw_dbm.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:44 2014
 
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
#ifdef KW_PDCP
#include "lpj.h"           /* LPJ defines */
#include "cpj.h"           /* CPJ defines */
#include "pju.h"           /* PJU defines */
#endif /* KW_PDCP */

#include "kw.h"            /* RLC defines */

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
#ifdef KW_PDCP
#include "lpj.x"           /* LPJ defines */
#include "cpj.x"           /* CPJ defines */
#include "pju.x"           /* PJU defines */
#endif /* KW_PDCP */

#include "kw.x"


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
PUBLIC S16 kwDbmInit
(
)
#else
PUBLIC S16 kwDbmInit()
#endif
{
   S16      ret;              /* Return Value */

   TRC3(kwDbmInit)

#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (_kwPBuf,\
            "kwDbmInit()\n"));
#endif

   /* Initialize ueCb Hash List */
   ret = cmHashListInit(&(kwCb.ueLstCp), (U16) KW_UE_LIST_BUCKET_SIZE,
         (U16) 0, (Bool) FALSE, (U16) CM_HASH_KEYTYPE_DEF,
         KW_GET_MEM_REGION(kwCb), KW_GET_MEM_POOL(kwCb));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmInit: cmHashListInit Failed for kwCb.ueLstCp.\n"));
#endif
      RETVALUE(ret);
   }

   /* Initialize cellCb Hash List */
   ret = cmHashListInit(&(kwCb.cellLstCp), (U16) KW_CELL_LIST_BUCKET_SIZE,
         (U16) 0, (Bool) FALSE, (U16) CM_HASH_KEYTYPE_DEF,
         kwCb.init.region, kwCb.init.pool);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmInit: cmHashListInit Failed for kwCb.cellLstCp.\n"));
#endif
      RETVALUE(ret);
   }

/* kw005.201 added support for L2 Measurement */         
#ifdef LTE_L2_MEAS
   /* Initialize qcI Hash List */
   ret = cmHashListInit(&(kwCb.kwL2Cb.qciHlCp), (U16) KW_QCI_LIST_BUCKET_SIZE,
         (U16) 0, (Bool) TRUE, (U16) CM_HASH_KEYTYPE_DEF,
         kwCb.init.region, kwCb.init.pool);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
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
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmInit: cmHashListInit Failed for kwCb.tbHlCp.\n"));
#endif
      RETVALUE(ret);
   }


#endif /* LTE_L2_MEAS */
   RETVALUE(ROK);
} /* kwDbmInit */


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
PUBLIC S16 kwDbmDeInit
(
)
#else
PUBLIC S16 kwDbmDeInit()
#endif
{
   S16      ret;                       /* Return Value */

   TRC3(kwDbmDeInit);

#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (_kwPBuf,\
            "kwDbmDeInit()\n"));
#endif

   /* De Initialize ueCb Hash List */
   ret = cmHashListDeinit(&(kwCb.ueLstCp));
   if (ret != ROK)
   {
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmDeInit: cmHashListDeinit Failed for kwCb.ueLstCp.\n"));
      RETVALUE(ret);
   }

   /* De Initialize cellCb Hash List */
   ret = cmHashListDeinit(&(kwCb.cellLstCp));
   if (ret != ROK)
   {
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmDeInit: cmHashListDeinit Failed for kwCb.cellLstCp.\n"));
      RETVALUE(ret);
   }
/* kw005.201 added support for L2 Measurement */         
#ifdef LTE_L2_MEAS
   /* De Initialize qciCb Hash List */
   ret = cmHashListDeinit(&(kwCb.kwL2Cb.qciHlCp));
   if (ret != ROK)
   {
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmDeInit: cmHashListDeinit Failed for kwCb.qciHlCp.\n"));
      RETVALUE(ret);
   }
#endif /* LTE_L2_MEAS */
#ifdef KW_BG_UL_PROC
   /*Free the mBufUl used for UL reassembly*/
   ret = SPutMsg(kwCb.mBufUl);
   if (ret != ROK)
   {
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmDeInit: SPutMsg Failed for kwCb.mBufUl.\n"));
      RETVALUE(ret);
   }
#endif /* KW_BG_UL_PROC */
#ifdef KW_BG_DL_PROC
   /*Free the mBufDl used for DL Acked PDU deletion*/
   ret = SPutMsg(kwCb.mBufDl);
   if (ret != ROK)
   {
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmDeInit: SPutMsg Failed for kwCb.mBufDl.\n"));
      RETVALUE(ret);
   }
#endif /* KW_BG_DL_PROC */
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
PUBLIC S16 kwDbmFetchRbCbForUi
(
CmLteRlcId     rlcId,      /* RLC Identifier */
KwRbCb         **rbCb       /* RB Cb */
)
#else
PUBLIC S16 kwDbmFetchRbCbForUi(rlcId, rbCb)
CmLteRlcId     rlcId;      /* RLC Identifier */
KwRbCb         **rbCb;      /* RB Cb */
#endif
{
   KwUeCb      *ueCb;                  /* UE Control Block */
   KwCellCb    *cellCb;                /* Cell Control Block */
   RbCb        **rbCbLst;              /* RB Control Block List */
   RbCb        *tRbCb;                 /* Local RB CB */
   S16         ret;                    /* Return Value */

   TRC3(kwDbmFetchRbCbForUi)

#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (_kwPBuf,
            "kwDbmFetchRbCbForUi(rlcId(ueId(%d), cellId(%d), rbId(%d)),\
   rbCb)\n", rlcId.ueId, rlcId.cellId, rlcId.rbId));
#endif

   ueCb = NULLP;
   cellCb = NULLP;
   rbCbLst = NULLP;
   ret = ROK;

   /* Validate the RBID in case of TM/UM/AM */
   KW_VALIDATE_RBID(rlcId.ueId, rlcId.rbId, rlcId.rbType, ret);
   if (ret != ROK)
   {
#ifdef DEBUGP
      /* DEBUG_PRINT EROR */
      KWDBGP((KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (_kwPBuf,\
               "kwCfgReEstRb -- KW_VALIDATE_RBID Failed --\
               rbId(%d), cellId(%d), ueId(%d)\n",\
               rlcId.rbId, rlcId.cellId, rlcId.ueId));

#endif
      RETVALUE(ret);
   }

   /* Check for UE CB or CELL CB */
   if (rlcId.ueId == 0)
   {
      if (kwDbmFetchCellCb(rlcId.cellId, &cellCb) != ROK)
      {
#ifdef DEBUGP
         KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
                  "kwDbmFetchRbCbForUi: kwDbmFetchCellCb Failed.\n"));
#endif
         RETVALUE(RFAILED);
      }

      rbCbLst = cellCb->rbCb;
      KW_DBM_FETCH_CELL_RBCB(rlcId.rbId, rbCbLst, tRbCb);
   }
   else
   {
      if (kwDbmFetchUeCb(rlcId.ueId, rlcId.cellId, &ueCb) != ROK)
      {
#ifdef DEBUGP
         KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
                  "kwDbmFetchRbCbForUi: kwDbmFetchUeCb Failed.\n"));
#endif
         RETVALUE(RFAILED);
      }

      KW_DBM_FETCH_RBCB(rlcId.rbId, rlcId.rbType, ueCb, tRbCb);
   }


   if (tRbCb == NULLP)
   {
#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmFetchRbCbForUi: kwDbmFetchRbCb Failed.\n"));
#endif
      RETVALUE(RFAILED);
   }

   *rbCb = &tRbCb->kwRbCb;

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
PUBLIC S16 kwDbmFetchRbCbForLi
(
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
CmLteLcId         lcId,       /* Logical channel instance */
U8                dir,        /* Direciotn DL/UL */
KwRbCb            **rbCb       /* RB Cb */
)
#else
PUBLIC S16 kwDbmFetchRbCbForLi(ueId, cellId, lcId, dir, rbCb)
CmLteRnti         ueId;       /* UE Identifier */
CmLteCellId       cellId;     /* Cell Identifier */
CmLteLcId         lcId;       /* Logical channel instance */
U8                dir;        /* Direciotn DL/UL */
KwRbCb            **rbCb;      /* RB Cb */
#endif
{
   KwUeCb      *ueCb;                  /* UE Control Block */
   KwCellCb    *cellCb;                /* Cell Control Block */
   /* kw006.201, ccpu00120574, fixed the warning */

   TRC3(kwDbmFetchRbCbForUi)

#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (_kwPBuf,
            "kwDbmFetchRbCbForLi(rlcId(ueId(%d), cellId(%d)))\n",
            ueId, cellId));
#endif

   ueCb = NULLP;
   cellCb = NULLP;
   /* kw006.201, ccpu00120574, fixed the warning */

   /* Check for UE CB or CELL CB */
   if (ueId == 0)
   {
      if (kwDbmFetchCellCb(cellId, &cellCb) != ROK)
      {

#ifdef DEBUGP
         KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
                  "kwDbmFetchRbCbForLi: kwDbmFetchCellCb Failed.\n"));
#endif
         RETVALUE(RFAILED);
      }

      if (dir == CKW_CFG_DIR_UL)
      {
         *rbCb = cellCb->lCh[lcId - 1].ulRbCb;
      }
      else
      {
         *rbCb = cellCb->lCh[lcId - 1].dlRbCb;
      }
   }
   else
   {
      if (kwDbmFetchUeCb(ueId, cellId, &ueCb) != ROK)
      {
#ifdef DEBUGP
         KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
                  "kwDbmFetchRbCbForLi: kwDbmFetchUeCb Failed.\n"));
#endif
         RETVALUE(RFAILED);
      }

      if (dir == CKW_CFG_DIR_UL)
      {
         *rbCb = ueCb->lCh[lcId - 1].ulRbCb;
      }
      else
      {
         *rbCb = ueCb->lCh[lcId - 1].dlRbCb;
      }
   }

   if (*rbCb == NULLP)
   {

#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
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
PUBLIC S16 kwDbmDelAllRb
(
RbCb         **rbCbLst,              /* RB Cb list */
U8             numRbCb                 /* Number of rbCbs */
)
#else
PUBLIC S16 kwDbmDelAllRb(rbCbLst, numRbCb)
RbCb         **rbCbLst;              /* RB Cb list */
U8             numRbCb;                /* Number of rbCbs */
#endif
{
   U8          idx;                    /* Index */
   RbCb        *rbCb;                  /* RB Control Block */

   TRC3(kwDbmDelAllRb)

#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (_kwPBuf,
            "kwDbmDelAllRb(rbCbLst, numRbCb(%d))\n", numRbCb));
#endif

   for (idx = 0; idx < numRbCb; idx++)
   {
      rbCb = rbCbLst[idx];
      if (rbCb != NULLP)
      {
/* kw005.201 added support for L2 Measurement */         
#ifdef LTE_L2_MEAS
         /* Check if measurement is running, if yes send an alarm to LM. */
         if(rbCb->kwRbCb.rbL2Cb.measOn)
         {
            KW_SEND_UEID_ALARM(rbCb->kwRbCb.ueCb->key.ueId, rbCb->kwRbCb.qci,
                          LKW_EVT_MEAS_HALT, LKW_CAUSE_RB_DELETION);
         }
         cmHashListDelete(&(kwCb.kwL2Cb.qciHlCp), (PTR)&rbCb->kwRbCb);
#endif /* LTE_L2_MEAS */
         /* Free the Buffers of RbCb */
         kwUtlFreeRbCb(&rbCb->kwRbCb);

         KW_DBM_DELETE_RBCB(rbCb);
#if (ERRCLASS & ERRCLS_INT_PAR)
         if (rbCb != NULLP)
         {
#ifdef DEBUGP
            KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
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
PUBLIC S16 kwDbmCreateUeCb
(
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
KwUeCb            **ueCb       /* UE Control Block */
)
#else
PUBLIC S16 kwDbmCreateUeCb(ueId, cellId, ueCb)
CmLteRnti         ueId;       /* UE Identifier */
CmLteCellId       cellId;     /* Cell Identifier */
KwUeCb            **ueCb;     /* UE Control Block */
#endif
{
   S16      ret;              /* Return Value */
   KwUeCb   *tUeCb;           /* UE Control Block */

   TRC3(kwDbmCreateUeCb)

#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (_kwPBuf,
            "kwDbmCreateUeCb(ueId(%d), cellId(%d))\n", ueId, cellId));
#endif

   KW_ALLOC(*ueCb, sizeof(KwUeCb));

#if (ERRCLASS & ERRCLS_ADD_RES)
   if (*ueCb == NULLP)
   {
      ret = RFAILED;
      KWLOGERROR(ERRCLS_ADD_RES, EKW023, (ErrVal) ret,
            "kwDbmCreateUeCb: UeCb allocation Failed.");
      RETVALUE(ret);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

   tUeCb = *ueCb;
   tUeCb->key.ueId = ueId;
   tUeCb->key.cellId = cellId;

   ret = cmHashListInsert(&(kwCb.ueLstCp), (PTR)tUeCb, (U8 *)&(tUeCb->key),
         (U16) sizeof(KwUeKey));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmCreateUeCb: cmHashListInsert Failed for ueCb.\n"));
#endif
      RETVALUE(ret);
   }
   /* kw005.201 ccpu00117318, updating the statistics */
   kwCb.genSts.numUe++;

#if 0
#ifdef KW_PDCP
   (*ueCb)->libInfo.state =  PJ_STATE_NORMAL;
   cmInitTimers(&((*ueCb)->libInfo.obdTmr), 1);

#endif /* KW_PDCP */
#endif
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
PUBLIC S16 kwDbmFetchUeCb
(
CmLteRnti         ueId,       /* UE Identifier */
CmLteCellId       cellId,     /* Cell Identifier */
KwUeCb            **ueCb       /* UE Control Block */
)
#else
PUBLIC S16 kwDbmFetchUeCb(ueId, cellId, ueCb)
CmLteRnti         ueId;       /* UE Identifier */
CmLteCellId       cellId;     /* Cell Identifier */
KwUeCb            **ueCb;      /* UE Control Block */
#endif
{
   S16      ret;              /* Return Value */
   KwUeKey  key;              /* Key for UE Hash List */

   TRC3(kwDbmFetchUeCb)

#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (_kwPBuf,
            "kwDbmFetchUeCb(ueId(%d), cellId(%d))\n", ueId, cellId));
#endif

   key.ueId = ueId;
   key.cellId = cellId;

   ret = cmHashListFind(&(kwCb.ueLstCp), (U8 *)&(key), sizeof(KwUeKey),
         KW_DEF_SEQ_NUM, (PTR *) ueCb);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
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
PUBLIC S16 kwDbmDelUeCb
(
KwUeCb      *ueCb,       /* UE Identifier */
Bool        abortFlag    /* Abort Flag */
)
#else
PUBLIC S16 kwDbmDelUeCb(ueCb, abortFlag)
KwUeCb      *ueCb;       /* UE Identifier */
Bool        abortFlag;   /* Abort Flag */
#endif
{
   S16         ret;      /* Return Value */
   U8          idx;      /* Index */
/* kw005.201 Added isLogicalChAvailable flag */
#if 0
#ifdef KW_PDCP
   Bool        isLogicalChAvailable = FALSE; /*Flag to ensure UeCb is deleted once*/
#endif /* KW_PDCP */
#endif
   TRC3(kwDbmDelUeCb)

#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (_kwPBuf,
            "kwDbmDelUeCb(ueId(%d), cellId(%d))\n",
            ueCb->key.ueId, ueCb->key.cellId));
#endif

#if 0
#if  (!defined(KW_PDCP) || !(defined(PJ_SEC_ASYNC) || defined(PJ_CMP_ASYNC)))
   UNUSED(abortFlag);
#endif /* (!defined(KW_PDCP) || ! (defined(PJ_SEC_ASYNC) || defined(PJ_CMP_ASYNC)))*/
#endif

/* kw005.201 Check to see if there is atleast one logical channel */
#if 0
#ifdef KW_PDCP
    for (idx = 0; idx < KW_MAX_LCH_PER_UE; idx++)
    {
        if (ueCb->lCh[idx].dlRbCb != NULLP)
        {
           isLogicalChAvailable = TRUE;
           break;
        }
    }

    if (isLogicalChAvailable == FALSE)
    {
       /* Delete ueCb entry from ueLstCp */
       ret = cmHashListDelete(&(kwCb.ueLstCp), (PTR) ueCb);
       if (ret != ROK)
       {

#ifdef DEBUGP
           KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
	          "kwDbmDelUeCb: cmHashListDelete Failed for ueCb.\n"));
#endif
       }

       /* Deallocate ueCb */
       KW_FREE(ueCb, sizeof(KwUeCb));
       RETVALUE(ret);

    }
#endif /* KW_PDCP */
#endif
   /* Delete all logical channels */
   for (idx = 0; idx < KW_MAX_LCH_PER_UE; idx++)
   {
      /* kw005.201 fixed the error in the code */
      ueCb->lCh[idx].dlRbCb = NULLP;
      ueCb->lCh[idx].ulRbCb = NULLP;
   }

#if 0
#ifdef KW_PDCP
   for ( idx = 0; idx< KW_MAX_SRB_PER_UE; idx++)
       pjCfgDelPjRBCb(ueCb, ueCb->srbCb[idx]);

   for ( idx = 0; idx< KW_MAX_DRB_PER_UE; idx++) 
       pjCfgDelPjRBCb(ueCb, ueCb->drbCb[idx]);

   /* Close the Integrity/Ciphering channels */
   if(ueCb->secInfo.secAct)
   {
      pjUtlIntClose(ueCb->secInfo.intCxtId); 
      pjUtlCipherClose(ueCb->secInfo.cpCxtId);
      pjUtlCipherClose(ueCb->secInfo.upCxtId);
   }

   /* Delete hoInfo if present */
   if (ueCb->hoInfo != NULLP)
   {
      for (idx = 0; idx < KW_MAX_DRB_PER_UE; idx++)
      {
         if (ueCb->hoInfo->hoCfmInfo[idx].pres == TRUE)
         {
            PJ_FREE(ueCb->hoInfo->hoCfmInfo[idx].ul.ulBitMap,
                  (ueCb->hoInfo->hoCfmInfo[idx].ul.numBits % 8)?
                  ((ueCb->hoInfo->hoCfmInfo[idx].ul.numBits / 8) + 1):
                  (ueCb->hoInfo->hoCfmInfo[idx].ul.numBits / 8 ));
         }
      }

      PJ_FREE(ueCb->hoInfo->hoCfmInfo, (KW_MAX_DRB_PER_UE * sizeof(PjHoCfmInfo)));
      PJ_FREE(ueCb->hoInfo, sizeof(PjHoInfo));  
   }

#endif /* KW_PDCP */
#endif

   /* Delete all SRB RbCbs in UeCb */
   ret = kwDbmDelAllRb(ueCb->srbCb, KW_MAX_SRB_PER_UE);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmDelUeCb: kwDbmDelAllRb Failed for ueCb.\n"));
#endif
   }

   /* Delete all DRB RbCbs in UeCb */
   ret = kwDbmDelAllRb(ueCb->drbCb, KW_MAX_DRB_PER_UE);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmDelUeCb: kwDbmDelAllRb Failed for ueCb.\n"));
#endif
   }

#if 0
#ifdef KW_PDCP
#if (defined(PJ_SEC_ASYNC) || defined(PJ_CMP_ASYNC))
   if(!abortFlag)
   {
      RETVALUE(ROK);
   }
#endif /* (defined(PJ_SEC_ASYNC) || defined(PJ_CMP_ASYNC)) */
#endif /* KW_PDCP */
#endif

/* kw005.201 Don't remove hash entry, if KW_PDCP flag is set, and
RLC + PDCP calls this function first time. The second call to 
this function shall delete hash entry and ueCb */

#if 0
#ifdef KW_PDCP
   if (!isLogicalChAvailable)
   {
#endif /* KW_PDCP */
#endif

/* Delete ueCb entry from ueLstCp */
   ret = cmHashListDelete(&(kwCb.ueLstCp), (PTR) ueCb);
   if (ret != ROK)
   {

#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmDelUeCb: cmHashListDelete Failed for ueCb.\n"));
#endif
   }
   /* kw005.201 ccpu00117318, updating the statistics */
   kwCb.genSts.numUe--;
   /* Deallocate ueCb */
   KW_FREE(ueCb, sizeof(KwUeCb));

#if 0
#ifdef KW_PDCP
   }
#endif /* KW_PDCP */
#endif

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
PUBLIC S16 kwDbmDelAllUe
(
)
#else
PUBLIC S16 kwDbmDelAllUe()
#endif
{
   S16         ret;              /* Return Value */
   KwUeCb      *ueCb;            /* UE Control Block */

   TRC3(kwDbmDelAllUe)

#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (_kwPBuf,
            "kwDbmDelAllUe()\n"));
#endif

   ret = ROK;
   ueCb = NULLP;

   /* Until no more ueCb is ueLstCp hash list get and delete ueCb */
   while (cmHashListGetNext(&(kwCb.ueLstCp), (PTR) ueCb, (PTR *)&ueCb) == ROK)
   {
      /* Delete ueCb */
      ret = kwDbmDelUeCb(ueCb, TRUE);
      if (ret != ROK)
      {
#ifdef DEBUGP
         KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
                  "kwDbmDelAllUe: kwDbmDelUeCb Failed.\n"));
#endif
         RETVALUE(ret);
      }
      ueCb = NULLP;
   }

   RETVALUE(ret);
} /* kwDbmDelAllUe */
/* kw005.201 added support for L2 Measurement */         
#ifdef LTE_L2_MEAS

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
   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (_kwPBuf,
            "kwDbmDelMeasEvtCb()\n"));
#endif

   for(evtIdx = 0; evtIdx < LKW_MAX_L2MEAS; evtIdx++)
   {
      if(kwCb.kwL2Cb.kwL2EvtCb[evtIdx] != NULLP)
      {
         measEvtCb = kwCb.kwL2Cb.kwL2EvtCb[evtIdx];
         /*ccpu00121544:Added a check before stopping the L2 timer*/
         if(TRUE == kwChkTmr((PTR)measEvtCb, KW_EVT_L2_TMR))
         {
            kwStopTmr((PTR)measEvtCb, KW_EVT_L2_TMR);
         }
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
PUBLIC S16 kwDbmCreateCellCb
(
CmLteCellId       cellId,     /* Cell Identifier */
KwCellCb          **cellCb    /* UE Control Block */
)
#else
PUBLIC S16 kwDbmCreateCellCb(cellId, cellCb)
CmLteCellId       cellId;     /* Cell Identifier */
KwCellCb          **cellCb;   /* UE Control Block */
#endif
{
   S16         ret;           /* Return Value */
   KwCellCb    *tCellCb;      /* UE Control Block */

   TRC3(kwDbmCreateCellCb)

#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (_kwPBuf,
            "kwDbmCreateCellCb(cellId(%d))\n", cellId));
#endif

   KW_ALLOC(*cellCb, sizeof(KwCellCb));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (*cellCb == NULLP)
   {
      ret = RFAILED;
      KWLOGERROR(ERRCLS_ADD_RES, EKW024, (ErrVal) ret,
            "kwDbmCreateUeCb: CellCb allocation Failed.");
      RETVALUE(ret);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

   tCellCb = *cellCb;
   tCellCb->cellId = cellId;

   ret = cmHashListInsert(&(kwCb.cellLstCp), (PTR) tCellCb,
         (U8 *)&(tCellCb->cellId), (U16) sizeof(CmLteCellId));
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
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
PUBLIC S16 kwDbmFetchCellCb
(
CmLteCellId       cellId,     /* Cell Identifier */
KwCellCb          **cellCb     /* Cell Control Block */
)
#else
PUBLIC S16 kwDbmFetchCellCb(cellId, cellCb)
CmLteCellId       cellId;     /* Cell Identifier */
KwCellCb          **cellCb;    /* Cell Control Block */
#endif
{
   S16            ret;              /* Return Value */

   TRC3(kwDbmFetchCellCb)

#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (_kwPBuf,
            "kwDbmFetchCellCb(cellId(%d))\n", cellId));
#endif

   ret = cmHashListFind(&(kwCb.cellLstCp), (U8 *)&(cellId),
         sizeof(CmLteCellId), KW_DEF_SEQ_NUM, (PTR*) cellCb);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
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
PUBLIC S16 kwDbmDelCellCb
(
KwCellCb    *cellCb      /* Cell Control Block */
)
#else
PUBLIC S16 kwDbmDelCellCb(cellCb)
KwCellCb    *cellCb;     /* Cell Control Block */
#endif
{
   S16         ret;              /* Return Value */

   TRC3(kwDbmDelCellCb)

#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (_kwPBuf,
            "kwDbmDelCellCb(cellId(%d))\n", cellCb->cellId));
#endif

   ret = ROK;

   /* Delete all rbCbs in cellCb */
   ret = kwDbmDelAllRb(cellCb->rbCb, KW_MAX_RB_PER_CELL);
   if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmDelCellCb: kwDbmDelAllRb Failed for cellCb.\n"));
#endif
   }

   /* Delete cellCb entry in hash list cellLstCp */
   ret = cmHashListDelete(&(kwCb.cellLstCp), (PTR) cellCb);
   if (ret != ROK)
   {
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
               "kwDbmDelCellCb: cmHashListDelete Failed for cellCb.\n"));
   }

   /* Deallocate cellCb */
   KW_FREE(cellCb, sizeof(KwCellCb));

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
PUBLIC S16 kwDbmDelAllCell
(
)
#else
PUBLIC S16 kwDbmDelAllCell()
#endif
{
   S16         ret;              /* Return Value */
   KwCellCb    *cellCb;          /* Cell Control Block */

   TRC3(kwDbmDelAllCell)

   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_BRIEF), (_kwPBuf,
            "kwDbmDelAllCell()\n"));

   ret = ROK;
   cellCb = NULLP;

   /* Until no more cellCb is ueLstCp hash list get and delete cellCb */
   while (cmHashListGetNext(&(kwCb.cellLstCp), (PTR) cellCb, (PTR *)&cellCb) == ROK)
   {
      /* Delete cellCb */
      ret = kwDbmDelCellCb(cellCb);
      if (ret != ROK)
      {
         KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (_kwPBuf,
                  "kwDbmDelAllCell: kwDbmDelCellCb Failed.\n"));
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
PUBLIC S16 kwDbmShutdown
(
)
#else
PUBLIC S16 kwDbmShutdown()
#endif
{
   S16 ret;

   TRC3(kwDbmDelAllCell)

   ret = kwDbmDelAllCell();
   /* kw006.201, ccpu00120574, fixed the warning */
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      KWLOGERROR(ERRCLS_DEBUG, EKW025, (ErrVal) ret,
               "kwDbmShutdown: kwDbmDelAllCell Failed.\n");
#endif /* ERRCLASS & ERRCLS_DEBUG */
   }
/* kw005.201 added support for L2 Measurement */         
#ifdef LTE_L2_MEAS
   ret = kwDbmDelMeasEvtCb();
   /* kw006.201, ccpu00120574, fixed the warning */
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      KWLOGERROR(ERRCLS_DEBUG, EKWXXX, (ErrVal) ret,
               "kwDbmShutdown: kwDbmDelMeasEvtCb Failed.\n");
#endif /* ERRCLASS & ERRCLS_DEBUG */
   }
#endif /* LTE_L2_MEAS */
   ret = kwDbmDelAllUe();
   /* kw006.201, ccpu00120574, fixed the warning */
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      KWLOGERROR(ERRCLS_INT_PAR, EKW026, (ErrVal) ret,
               "kwDbmShutdown: kwDbmDelAllUe Failed.\n");
#endif /* ERRCLASS & ERRCLS_DEBUG */
   }
   ret = kwDbmDeInit();
   /* kw006.201, ccpu00120574, fixed the warning */
   if (ret != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      KWLOGERROR(ERRCLS_INT_PAR, EKW027, (ErrVal) ret,
               "kwDbmShutdown: kwDbmDeInit Failed.\n");
#endif /* ERRCLASS & ERRCLS_DEBUG */
   }

   RETVALUE(ROK);
} /* kwDbmShutdown */

#if 0
#ifdef KW_PDCP
/**
 *
 * @brief Handler to create a RB control block.
 *       
 *
 * @b Description
 *        This function is called to create a RLC control block or PDCP 
 *        control block based on rb flag and update the pointers in RbCb.
 *        If the RbCb is already allocated, the rbId is updated in KwRbCb
 *        or PjRbCb based on rb. If the RbCb has not been allocated earlier,
 *        a new RbCb is created and the pointers are updated along with the
 *        rbIds.
 *
 *  @param[in] rbId      RB ID of the entity
 *  @param[in] rbCbLst   List of the RBs in the UeCb
 *  @param[in] rb        The RB to be created. This can be
 *                       PJ_CFG_PDCP when PDCP is created
 *                       or PJ_CFG_RLC when RLC is being
 *                       created. 
 *  
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
*/
#ifdef ANSI
PUBLIC RbCb* kwDbmCreateRbCb
(
U8      rbId,
U8      rbType, 
KwUeCb  *ueCb, 
U8      rb
)
#else
PUBLIC RbCb* kwDbmCreateRbCb(rbId,rbType,ueCb,rb)
U8      rbId; 
U8      rbType;
KwUeCb  *ueCb; 
U8      rb;
#endif
{
   RbCb   *rbCb;
   RbCb   **rbCbLst;

   TRC2(kwDbmCreateRbCb)

   rbCb = NULLP;
   rbCbLst = NULLP;

   KW_DBM_FETCH_RBCB(rbId, rbType, ueCb, rbCb);

   if(rbCb == NULLP)
   {
      KW_ALLOC( rbCb, sizeof(RbCb) );
      if ( rbCb == NULLP )
      {
         /*PJLOGERROR(rbCb, ERRCLS_DEBUG, EKW028, (ErrVal)0,
               "kwDbmCreateRbCb: PJ_ALLOC failed for rbCb.\n");*/
         RETVALUE(rbCb);
      }
      /* kw006.201 ccpu00121338, numOfRb increments twice for a single *
       * DCCH/DTCH. So, moved it here where allocation happens.        */
      /* kw005.201 ccpu00117318, updating the statistics */   
      KW_LMM_RB_STS_INC();                                    
   }

   if ( rb == PJ_CFG_PDCP )
   {
      rbCb->pjRbCb.rbId   = rbId;
      rbCb->pjRbCb.rbType = rbType;
      rbCb->rbCfgStat    |= rb;
   }
   else
   {
      rbCb->kwRbCb.rlcId.rbId   = rbId;
      rbCb->kwRbCb.rlcId.rbType = rbType;
      rbCb->rbCfgStat          |= rb;
   }

   /* Update the RB Cfg state with PDCP */
   if(rbCb->rbCfgStat == PJ_CFG_BOTH)
   {
      rbCb->kwRbCb.pjRbCb = &(rbCb->pjRbCb);
      rbCb->pjRbCb.kwRbCb = &(rbCb->kwRbCb);

   }
  
   rbCbLst = ((rbType == CM_LTE_SRB)? ueCb->srbCb:ueCb->drbCb); 
   rbCbLst[rbId] = rbCb;
/*Optimization change for ccpu00111716 and ccpu00117290*/
#if ((defined KW_BG_DL_PROC) || (defined KW_BG_UL_PROC))
   /*RbCb pointer is stored in KwRbCb so as to free it after all DL/UL PDUs*
    *are freed.                                                            */
   rbCb->kwRbCb.rb = rbCb;
#endif /* ((defined KW_BG_DL_PROC) || (defined KW_BG_UL_PROC)) */
   
   RETVALUE(rbCb); 
   
} /* kwDbmCreateRbCb */
/**
 *
 * @brief Handler to fetch a  PDCP RB control block.
 *       
 *
 * @b Description
 *        This function is used to fetch the PDCP RB control block based on 
 *        the RB id. The pointer to PjRbCb is returned.
 *       
 *  @param[in]  ueCb    UE control block of the PDCP RB
 *  @param[in]  rbId    RB ID of the required PDCP entity.
 *  @param[out] pjRbCb  PDCP RB Control Block.
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PUBLIC S16 kwDbmFetchPjRbCb
(
KwUeCb  *ueCb,
U8       rbId,
U8       rbType,
PjRbCb  **pjRbCb 
)
#else
PUBLIC S16 kwDbmFetchPjRbCb(ueCb,rbId,rbType,pjRbCb)
KwUeCb  *ueCb;      
U8       rbId;
U8       rbType;
PjRbCb  **pjRbCb;
#endif
{
   RbCb    *rbCb;

   TRC2(kwDbmFetchPjRbCb)

   *pjRbCb = NULLP;

   KW_DBM_FETCH_RBCB(rbId, rbType, ueCb, rbCb);
   if ( rbCb != NULLP )
   {
      if ( rbCb->rbCfgStat & PJ_CFG_PDCP )
      {
         *pjRbCb = &(rbCb->pjRbCb);
      }
   }

   RETVALUE(ROK);

} /* kwDbmFetchPjRbCb */

/**
 *
 * @brief Handler to delete a PDCP/RLC RB control block.
 *       
 *
 * @b Description
 *        This function is used to delete the PDCP/RLC RB control block based 
 *        on RB id and the RB type (PDCP/RLC). If the corresponding RB is 
 *        present, the cfgStat flag is unset. If the cfgStat flag is zero,
 *        the RBCB is freed.
 *
 *  @param[in]  rbId    RB ID of the to be deleted RB
 *  @param[in]  rbCbLst RbCb list in UE CB
 *  @param[in]  rb      The RB to be deleted. This can be
 *                      PJ_CFG_PDCP when PDCP is created
 *                      or PJ_CFG_RLC when RLC is being
 *                      created.
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PUBLIC S16 kwDbmDelRbCb
(
U8      rbId,
U8      rbType,
RbCb   **rbCb, 
U8      rb
)
#else
PUBLIC S16 kwDbmDelRbCb(rbId,rbType,rbCb,rb)
U8      rbId;
U8      rbType;
RbCb   **rbCb;
U8      rb;
#endif
{
   S16      ret;
 
   TRC2(kwDbmDelRbCb)

   ret   = RFAILED;
   if ( (*rbCb) != NULLP )
   {
      (*rbCb)->rbCfgStat &= ~(rb);
      if ( !((*rbCb)->rbCfgStat & (PJ_CFG_BOTH)) )
      {
         KW_DBM_DELETE_RBCB((*rbCb));
      }
      ret = ROK;
   }
   RETVALUE(ret);

} /* kwDbmDelRbCb */

#endif /* KW_PDCP */
#endif

/********************************************************************30**
  
         End of file:     kw_dbm.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:44 2014
  
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
/main/5      kw006.201 rd    1. ccpu00111716 and ccpu00117290, added code for
                                storing RbCb in KwRbCb in kwDbmCreateRbCb.
                       ap    2. ccpu00120574, fixed the warning.
                       rd    3. Freeing of mBufUl is done in kwDbmDeInit.
                       rd    4. ccpu00121338, numOfRb increments twice for a
                                single DCCH/DTCH.
                             5. ccpu00121544:Added a check before stopping the
                                L2 timer in kwDbmDelMeasEvtCb.
*********************************************************************91*/

