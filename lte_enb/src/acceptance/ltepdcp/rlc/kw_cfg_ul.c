

/********************************************************************20**

        Name:    LTE RLC - Configuration Manager file

        Type:    C source file

        Desc:    It contains the following configuraiton primtives
                 for different actions
                    -- kwCfgValdtEntCfg
                    -- kwCfgFillRbCb
                    -- kwCfgRbInit
                    -- kwCfgAddRb
                    -- kwCfgReCfgRb
                    -- kwCfgDelRb
                    -- kwCfgReEstRb
                    -- kwCfgDelUe

        File:     gp_cfg.c

        Sid:      kw_cfg_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:44 2014

        Prg:      gk

*********************************************************************21*/
/** @file gp_cfg.c
@brief RLC Configuration Module
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
#include "kw_err.h"        /* RLC error options */
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


/** @details
 * This primitive Fills the configuration informtion (entCfg) received in RB Cb
 *
 * @param [out]   rbCb     -  RB Control Block
 * @param [out]   ueCb     -  UE Control Block
 * @param [in]    entCfg   -  RLC Entity configuration
 *
 * @return  ROK
 */
#ifdef ANSI
PRIVATE S16 kwCfgFillUlRbCb
(
KwCb              *gCb,
KwUlRbCb          *rbCb,
KwUlUeCb          *ueCb,
CkwEntCfgInfo     *entCfg
)
#else
PRIVATE S16 kwCfgFillUlRbCb(gCb,rbCb, ueCb, entCfg)
KwCb              *gCb;
KwUlRbCb            *rbCb;
KwUlUeCb            *ueCb;
CkwEntCfgInfo     *entCfg;
#endif
{
   S16            ret;
   U16            winLen;

   TRC3(kwCfgFillUlRbCb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,\
      "kwCfgFillRbCb(ueId(%d), cellId(%d), rbId(%d), rbType(%d))\n",\
      rbCb->rlcId.ueId, rbCb->rlcId.cellId, entCfg->rbId, entCfg->rbType));
#endif

   ret = ROK;

   /* Initialize according to entMode */
   switch (entCfg->entMode)
   {
      case CM_LTE_MODE_TM:
         {
            rbCb->lch.lChId  = entCfg->lCh[0].lChId;
            rbCb->lch.lChType = entCfg->lCh[0].type;

            rbCb->mode = entCfg->entMode;
            rbCb->dir = entCfg->dir;

            break;
         }

      case CM_LTE_MODE_UM:
         {
            /* If rbCb is already present then
             * Check for the direction already configured and verify the new
             * configuration requested is different from the previous.
             * If both directions are different then make
             * indx = 0 as Down Link and 
             * indx = 1 as Up Link
             */
            /* If rbId is same and same logical channel is going to be
             * used then what is the assumption to assign Dl and UL information
             */
            rbCb->lch.lChId  = entCfg->lCh[0].lChId;
            rbCb->lch.lChType = entCfg->lCh[0].type;

            rbCb->mode = entCfg->entMode;
            rbCb->dir = entCfg->dir;

            if (entCfg->m.umInfo.ul.snLen == KW_UM_CFG_SN_5)
            {
               rbCb->m.umUl.snLen = KW_UM_SN_5;
            }
            else
            {
               rbCb->m.umUl.snLen = KW_UM_SN_10;
            }
            rbCb->m.umUl.umWinSz = KW_POWER(2,
                      ((rbCb->m.umUl.snLen * KW_UM_CFG_SN_5) -1 ));
            rbCb->m.umUl.reOrdTmrInt = 
                       entCfg->m.umInfo.ul.reOrdTmr;
            cmInitTimers(&(rbCb->m.umUl.reOrdTmr), 1);
            winLen = rbCb->m.umUl.umWinSz << 1;
            KW_ALLOC(gCb,rbCb->m.umUl.recBuf, winLen * sizeof(KwUmRecBuf*));
#if (ERRCLASS & ERRCLS_ADD_RES)
            /* Sanity check */
            if (rbCb->m.umUl.recBuf == NULLP)
            {
                ret = RFAILED;
                KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW019, (ErrVal) ret,
                             "kwCfgFillRbCb: UM RECBUF allocation Failed.");
            }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

            ueCb->lCh[rbCb->lch.lChId - 1].ulRbCb = rbCb;
            break;
         }

      case CM_LTE_MODE_AM:
         {
            /* Down Link Information */
            rbCb->lch.lChId  = entCfg->lCh[1].lChId;
            rbCb->lch.lChType = entCfg->lCh[1].type;

            rbCb->mode = entCfg->entMode;
            rbCb->dir = KW_DIR_BOTH;

            rbCb->m.amUl.staProhTmrInt = entCfg->m.amInfo.ul.staProhTmr;
            rbCb->m.amUl.reOrdTmrInt = entCfg->m.amInfo.ul.reOrdTmr;
            cmInitTimers(&(rbCb->m.amUl.reOrdTmr), 1);
            cmInitTimers(&(rbCb->m.amUl.staProhTmr), 1);

            rbCb->m.amUl.vrMr = rbCb->m.amUl.vrR + KW_AM_WIN_SZ;
            ueCb->lCh[rbCb->lch.lChId - 1].ulRbCb = rbCb;

            winLen = KW_AM_WIN_SZ << 1;
            KW_ALLOC(gCb,rbCb->m.amUl.recBuf,
                  (winLen * sizeof(KwAmRecBuf *)));
#if (ERRCLASS & ERRCLS_ADD_RES)
            if (rbCb->m.amUl.recBuf == NULLP)
            {
               ret = RFAILED;
               KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW022, (ErrVal) ret,
                     "kwCfgFillRbCb: AM RECBUF allocation Failed.");
            }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
            break;
         }
      default:
         {
            KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
             "kwCfgFillRbCb Failed -- for the invalid mode(%d)\n",
             entCfg->entMode));
         }
   }
   
   /* kw005.201 removed numLc from statistics */

   RETVALUE(ret);
} /* kwCfgFillUlRbCb */


/** @details
 * This primitive Initializes the RB Cb
 *
 * @param [out]   rbCb     -  RB Control Block
 * @param [in]    ueCb     -  UE Control Block
 * @param [in]    entCfg   -  Entity Configuration
 *
 * @return  ROK
 */
#ifdef ANSI
PRIVATE S16 kwCfgUpdateUlRb
(
KwCb              *gCb,
KwUlRbCb            *rbCb,
KwUlCellCb          *cellCb,
KwUlUeCb            *ueCb,
CkwEntCfgInfo     *entCfg
)
#else
PRIVATE S16 kwCfgUpdateUlRb(gCb,rbCb, cellCb, ueCb, entCfg)
KwCb              *gCb;
KwUlRbCb          *rbCb;
KwUlCellCb        *cellCb;
KwUlUeCb          *ueCb;
CkwEntCfgInfo     *entCfg;
#endif
{
   TRC3(kwCfgUpdateUlRb)


   if (rbCb->mode != entCfg->entMode)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
       "kwCfgUpdateRb():Failed--rbId(%d), rbType(%d), cellId(%d), ueId(%d)\n",\
        rbCb->rlcId.rbId, rbCb->rlcId.rbType ,rbCb->rlcId.cellId, 
        rbCb->rlcId.ueId));
#endif
      RETVALUE(CKW_CFG_REAS_RB_MODE_MIS);
   }

   switch (rbCb->mode)
   {
      case CM_LTE_MODE_TM:
         {
            cellCb->lCh[rbCb->lch.lChId - 1].ulRbCb = NULLP;
            rbCb->dir = entCfg->dir;
            rbCb->lch.lChId = entCfg->lCh[0].lChId;
            rbCb->lch.lChType = entCfg->lCh[0].type;

            cellCb->lCh[rbCb->lch.lChId - 1].ulRbCb = rbCb;
            break;
         }

      case CM_LTE_MODE_UM:
         {
            if (entCfg->lCh[0].type == CM_LTE_LCH_DCCH)
            {
               RETVALUE(CKW_CFG_REAS_LCHTYPE_MIS);
            }

            ueCb->lCh[rbCb->lch.lChId - 1].ulRbCb = NULLP;

            /* Free the Buffers of RbCb */
            kwUtlFreeUlRbCb(gCb,rbCb);

            if (kwCfgFillUlRbCb(gCb,rbCb, ueCb, entCfg) != ROK)
            {
                 RETVALUE(CKW_CFG_REAS_RECFG_FAIL);
            }
            ueCb->lCh[entCfg->lCh[0].lChId - 1].ulRbCb = rbCb;

            rbCb->lch.lChId = entCfg->lCh[0].lChId;
            rbCb->lch.lChType = entCfg->lCh[0].type;
            rbCb->dir = entCfg->dir;

            break;
         }

      case CM_LTE_MODE_AM:
         {
            ueCb->lCh[rbCb->lch.lChId - 1].ulRbCb = NULLP;

            ueCb->lCh[entCfg->lCh[1].lChId - 1].ulRbCb = rbCb;

            /* Up Link */
            rbCb->lch.lChId = entCfg->lCh[1].lChId;
            rbCb->lch.lChType = entCfg->lCh[1].type;
            rbCb->m.amUl.staProhTmrInt = entCfg->m.amInfo.ul.staProhTmr;
            rbCb->m.amUl.reOrdTmrInt = entCfg->m.amInfo.ul.reOrdTmr;

            break;
         }
   }

   RETVALUE(CKW_CFG_REAS_NONE);
} /* kwCfgUpdateRb */


/** @details
 * This primitive adds new RB in Ue/Cell Cb.
 *
 * - If UE ID is 0 then
 *   - Check for CELL CB is present
 *   - If yes, Check for RB ID
 *     - If RB ID is present Status Indication with reason
 *     - Else, Create New RB CB in CELL CB
 *   - If no Create New CELL CB and RB CB
 * - Else,
 *   - Check for UE CB is present
 *   - If yes Check for RB ID
 *     - If RB ID is present Status Indication with reason
 *     - Else, Create New RB CB in UE CB
 *   - If no Create New UE CB and RB CB
 * - Fill entity confirmation
 *
 * @param [in]    ueId     -  UE Identifier
 * @param [in]    cellId   -  CELL Identifier
 * @param [in]    entCfg   -  Entity Configuration to be done.
 * @param [out]   entCfm   -  Entity Confirmation.
 *
 * @return  ROK
 */
#ifdef ANSI
PUBLIC S16 kwCfgAddUlRb
(
KwCb             *gCb,
CmLteRnti         ueId,
CmLteCellId       cellId,
CkwEntCfgInfo     *entCfg,
CkwEntCfgCfmInfo  *entCfm
)
#else
PUBLIC S16 kwCfgAddUlRb(gCb,ueId, cellId, entCfg, entCfm)
KwCb             *gCb;
CmLteRnti         ueId;
CmLteCellId       cellId;
CkwEntCfgInfo     *entCfg;
CkwEntCfgCfmInfo  *entCfm;
#endif
{
   S16                  ret;           /* Return Value */
   KwUlUeCb             *ueCb;         /* UE Control Block */
   KwUlCellCb           *cellCb;       /* Cell Control Block */
   KwUlRbCb             *kwRbCb;       /* KW RB Control Block */
   U8                   rbId;          /* Rb Identifier */
   U8                   rbType;        /* RB type */
   U8                   reason;        /* Rb Identifier */

   TRC3(kwCfgAddUlRb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,\
            "kwCfgAddRb(ueId(%d), cellId(%d), cfgType(%d))\n",\
            ueId, cellId, entCfg->cfgType));
#endif

   /* Get rbId */
   rbId = entCfg->rbId;
   rbType = entCfg->rbType;

   if (cellId == 0)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_CELL_UNKWN);

      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgAddUlRb(ueId(%d), cellId(%d), cfgType(%d))\n",\
               ueId, cellId, entCfg->cfgType));

      RETVALUE(RFAILED);
   }

   /* Validate the RBID in case of TM/UM/AM */
   KW_VALIDATE_RBID(ueId, rbId, rbType, ret);
   if (ret != ROK)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_RB_UNKWN);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgAddUlRb -- KW_VALIDATE_RBID Failed --\
               rbId(%d), rbType(%d), cellId(%d), ueId(%d)\n",\
              rbId, rbType, cellId, ueId));
#endif

      RETVALUE(ret);
   }

   /* Validate LChId */
   KW_VALIDATE_LCHID(entCfg->lCh[0].lChId);
   if (entCfg->entMode == CM_LTE_MODE_AM)
   {
      KW_VALIDATE_LCHID(entCfg->lCh[1].lChId);
   }

   /* Process Adding new RB */
   if (ueId == 0)
   {
      if ((entCfg->lCh[0].type == CM_LTE_LCH_CCCH) &&
           (entCfg->entMode == CM_LTE_MODE_TM))
      {
         /* Cell CB present */
         if (kwDbmFetchUlCellCb(gCb, cellId, &cellCb) == ROK)
         {
            /* Get rbCb from cellCb->rbCb List */
            KW_DBM_FETCH_CELL_UL_RBCB(rbId, cellCb->rbCb, kwRbCb);

            if (( kwRbCb != NULLP))
            {
               /* Fill entCfm structure */
               KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
                     CKW_CFG_REAS_RB_PRSNT);

#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), 
                        (gCb->init.prntBuf,\
                        "kwCfgAddRb -- kwDbmFetchRbCb - RB CB present --\
                        rbId(%d), cellId(%d)\n",\
                        rbId, kwRbCb->rlcId.cellId));
#endif
               RETVALUE(RFAILED);
            }
         }
         else  /* Cell CB UNKNOWN */
         {
            /* Create CELL CB */
            if ( kwDbmCreateUlCellCb(gCb,cellId, &cellCb) != ROK)
            {
               /* Fill entCfm structure */
               KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
                     CKW_CFG_REAS_CELL_CREAT_FAIL);

#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
                        "kwCfgAddRb -- kwDbmCreateCellCb Failed -- cellId(%d)\
                        \n", cellId));
#endif

               RETVALUE(RFAILED);
            }
         }

         /* Create RB CB */
         KW_ALLOC(gCb,kwRbCb, sizeof (KwUlRbCb));
         if (kwRbCb == NULL)
         {
            /* Fill entCfm structure */                           
            KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType,CKW_CFG_CFM_NOK,
                                    CKW_CFG_REAS_RB_CREAT_FAIL); 
            KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), 
                   (gCb->init.prntBuf,
                    "kwCfgAddRb -- kwDbmCreateRbCb Failed, rbId(%d)\n", rbId));
            RETVALUE(RFAILED); 
         }
         KW_DBM_FILL_CELL_UL_RBCB(kwRbCb,cellCb->rbCb, rbId);
         KW_LMM_RB_STS_INC(gCb);
         cellCb->lCh[entCfg->lCh[0].lChId - 1].ulRbCb = kwRbCb;
      }
      else
      {
         if (entCfg->entMode != CM_LTE_MODE_TM)
         {
            reason = CKW_CFG_REAS_RB_MODE_MIS;
         }
         else
         {
            reason = CKW_CFG_REAS_LCHTYPE_MIS;
         }

         /* Fill entCfm structure */
         KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK, reason);
         RETVALUE(RFAILED);
      }
   }
   else
   {
      if ((((entCfg->lCh[0].type == CM_LTE_LCH_DCCH) && (entCfg->entMode != CM_LTE_MODE_UM)) ||
            (entCfg->lCh[0].type == CM_LTE_LCH_DTCH)) &&
          (entCfg->entMode != CM_LTE_MODE_TM))
      {
         /* UE CB present */
         if ( kwDbmFetchUlUeCb(gCb,ueId, cellId, &ueCb) == ROK)
         {
            /* Get rbCb from ueCb->rbCb list */
            KW_DBM_FETCH_UL_RBCB(rbId, rbType, ueCb, kwRbCb);

            if(( kwRbCb != NULLP))
            {
               /* Fill entCfm structure */
               KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
                     CKW_CFG_REAS_RB_PRSNT);

#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
                        "kwCfgAddUlRb -- kwDbmFetchRbCb - RB CB present --\
                        rbId(%d), rbType(%d), cellId(%d), ueId(%d)\n",\
                        rbId, kwRbCb->rlcId.rbType,\
                        kwRbCb->rlcId.cellId, kwRbCb->rlcId.ueId));
#endif

               RETVALUE(RFAILED);
            }
         }
         else  /* UE CB UNKNOWN */
         {
            /* Create UE CB */
            if ( kwDbmCreateUlUeCb(gCb,ueId, cellId, &ueCb) != ROK)
            {
               /* Fill entCfm structure */
               KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
                     CKW_CFG_REAS_UE_CREAT_FAIL);

#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
                        "kwCfgAddRb -- kwDbmCreateUeCb Failed -- cellId(%d), \
                        ueId(%d)\n", cellId, ueId));
#endif
               RETVALUE(RFAILED);
            }
         }

         /* Create RB CB */
         KW_ALLOC(gCb,kwRbCb, sizeof (KwUlRbCb));
         if (kwRbCb == NULL)
         {
            /* Fill entCfm structure */                           
            KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType,CKW_CFG_CFM_NOK,
                                    CKW_CFG_REAS_RB_CREAT_FAIL); 
            KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), 
                   (gCb->init.prntBuf,
                    "kwCfgAddRb -- kwDbmCreateRbCb Failed, rbId(%d)\n", rbId));
            RETVALUE(RFAILED); 
         }
         KW_DBM_FILL_UE_UL_RBCB(kwRbCb,ueCb,rbId, rbType);
         KW_LMM_RB_STS_INC(gCb);

/* kw005.201 added support for L2 Measurement */         
#ifdef LTE_L2_MEAS_RLC
         kwRbCb->qci = entCfg->qci;
         ret = cmHashListInsert(&(gCb->kwL2Cb.qciHlCp), (PTR)kwRbCb, 
                 (U8 *)&(kwRbCb->qci), (U16) sizeof(kwRbCb->qci));
         if(ret != ROK)
         {
            KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
            "Failed adding rbCb in qciList(ueId(%d), cellId(%d), qci(%d))\n",\
            ueId, cellId, entCfg->qci));
            RETVALUE(RFAILED);
         }
         kwRbCb->ueCb =  ueCb;
#endif /* LTE_L2_MEAS_RLC */
      }
      else
      {
         if (entCfg->entMode == CM_LTE_MODE_TM)
         {
            reason = CKW_CFG_REAS_RB_MODE_MIS;
         }
         else
         {
            reason = CKW_CFG_REAS_LCHTYPE_MIS;
         }

         /* Fill entCfm structure */
         KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK, reason);
         RETVALUE(RFAILED);
      }
   }


   kwRbCb->rlcId.cellId = cellId;
   kwRbCb->rlcId.ueId   = ueId;
   kwRbCb->rlcId.rbType = rbType;
   kwRbCb->inst         = gCb->init.inst;


   /* Fill RB CB */
   if (kwCfgFillUlRbCb(gCb,kwRbCb, ueCb, entCfg) != ROK)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
               CKW_CFG_REAS_RB_CREAT_FAIL);

      /* Delete RB CB created */
      KW_FREE(gCb,kwRbCb, sizeof(KwUlRbCb));

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgAddRb -- kwCfgFillRbCb Failed -- cellId(%d), \
               ueId(%d), rbId(%d), rbType(%d)\n", cellId, ueId, rbId, rbType));
#endif

      RETVALUE(RFAILED);
   }

   /* Fill entCfm structure */
   KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_OK, CKW_CFG_REAS_NONE);

   RETVALUE(ROK);
} /* kwCfgAddRb */


/** @details
 * This primitive reconfigures the existing RB in Ue/Cell Cb.
 *
 * - If UE ID is 0 then
 *   - Check for CELL CB is present
 *   - If yes, Check for RB ID
 *     - If RB ID is prenset Reconfigure the RB CB
 *     - Else, Status Indication with Reason
 *   - Else, Status Indication with Reason
 * - Else,
 *   - Check for UE CB is present
 *   - If yes, Check for RB ID
 *     - If RB ID is prenset Reconfigure the CELL CB
 *     - Else, Status Indication with Reason
 *   - Else, Status Indication with Reason
 * - Fill entity confirmation
 *
 * @param [in]    ueId     -  UE Identifier
 * @param [in]    cellId   -  CELL Identifier
 * @param [in]    entCfg   -  Entity Configuration to be done.
 * @param [out]   entCfm   -  Entity Confirmation
 *
 * @return  ROK
 */
#ifdef ANSI
PUBLIC S16 kwCfgReCfgUlRb
(
KwCb             *gCb,
CmLteRnti         ueId,
CmLteCellId       cellId,
CkwEntCfgInfo     *entCfg,
CkwEntCfgCfmInfo  *entCfm
)
#else
PUBLIC S16 kwCfgReCfgUlRb(gCb,ueId, cellId, entCfg, entCfm)
KwCb             *gCb;
CmLteRnti         ueId;
CmLteCellId       cellId;
CkwEntCfgInfo     *entCfg;
CkwEntCfgCfmInfo  *entCfm;
#endif
{
   S16                  ret;           /* Return value */
   KwUlRbCb            *rbCb;         /* RB Control Block */
   KwUlRbCb            tRbCb;         /* KW RB Control Block */
   KwUlCellCb         *cellCb;       /* Cell Control Block */
   KwUlUeCb           *ueCb;         /* Ue Control Block */
   U8                  rbId;          /* RB Identifier */
   U8                  rbType;        /* RB Type */

   TRC3(kwCfgReCfgUlRb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,\
            "kwCfgReCfgRb(ueId(%d), cellId(%d), cfgType(%d))\n",\
            ueId, cellId, entCfg->cfgType));
#endif

   rbId = entCfg->rbId;
   rbType = entCfg->rbType;

   /* Validate the RBID in case of TM/UM/AM */
   KW_VALIDATE_RBID(ueId, rbId, rbType, ret);
   if (ret != ROK)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, entCfg->rbId, rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_RB_UNKWN);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgReCfgRb -- KW_VALIDATE_RBID Failed --\
               rbId(%d), rbType(%d), cellId(%d), ueId(%d)\n",\
              rbId, rbType, cellId, ueId));
#endif
      RETVALUE(ret);
   }

   /* Check for UeCb or CellCb */
   if (ueId == 0)
   {
      /* Get cellCb */
      ret = kwDbmFetchUlCellCb(gCb,cellId, &cellCb);
      if (ret != ROK)
      {
         /* Fill entCfm structure */
         KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
               CKW_CFG_REAS_CELL_UNKWN);

#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
                  "kwCfgReCfgRb -- kwDbmFetchCellCb Failed -- cellId(%d), \
                  rbId(%d)\n", cellId, rbId));
#endif
         RETVALUE(ret);
      }

      /* Get rbCb */
      KW_DBM_FETCH_CELL_RBCB(rbId, cellCb->rbCb, rbCb);

      if (rbCb == NULLP)
      {
         /* Fill entCfm structure */
         KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
               CKW_CFG_REAS_RB_UNKWN);

#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
                  "kwCfgReCfgRb -- kwDbmFetchRbCb Failed -- cellId(%d), \
                  rbId(%d)\n", cellId, rbId));
#endif
         RETVALUE(ret);
      }

      /* Take backup of rbCb before updating.
       * Because in failure case restore original rbCb
       */
      cmMemcpy((U8 *)&tRbCb, (U8 *)rbCb, sizeof(KwUlRbCb));

      /* Update rbCb */
      ret = kwCfgUpdateUlRb(gCb,rbCb, cellCb, NULLP, entCfg);
      if (ret != ROK)
      {
         /* Fill entCfm structure */
         KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
               ret);

#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
                  "kwCfgReCfgRb -- kwCfgUpdateRb Failed --\
                  rbId(%d), cellId(%d)\n",\
                  rbId, cellId));
#endif

         cmMemcpy((U8*)rbCb, (U8 *)&tRbCb, sizeof(KwUlRbCb));

         RETVALUE(ret);
      }
   }
   else
   {
      /* Get ueCb */
      ret = kwDbmFetchUlUeCb(gCb,ueId, cellId, &ueCb);
      if (ret != ROK)
      {
         /* Fill entCfm structure */
         KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,
               CKW_CFG_REAS_UE_UNKWN);

#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwCfgReCfgRb -- kwDbmFetchUeCb Failed -- ueId(%d),\
            cellId(%d), rbId(%d)\n", ueId, cellId, rbId));
#endif
         RETVALUE(ret);
      }

      /* Get rbCb */
      KW_DBM_FETCH_UL_RBCB(rbId, rbType, ueCb, rbCb);

      if ( rbCb == NULLP)
      {
         /* Fill entCfm structure */
         KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,
               CKW_CFG_REAS_RB_UNKWN);

#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwCfgReCfgRb -- kwDbmFetchRbCb Failed -- ueId(%d),\
            cellId(%d), rbId(%d)\n", ueId, cellId, rbId));
#endif
         RETVALUE(ret);
      }

      /* Take backup of rbCb before updating.
       * Because in failure case restore original rbCb
       */
      cmMemcpy((U8 *)&tRbCb, (U8 *)rbCb, sizeof(KwUlRbCb));

      /* Update rbCb */
      ret = kwCfgUpdateUlRb(gCb,rbCb, NULLP, ueCb, entCfg);
      if (ret != CKW_CFG_REAS_NONE)
      {
         /* Fill entCfm structure */
         KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
               ret);

#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
                  "kwCfgReCfgRb -- kwCfgUpdateRb Failed --\
                  rbId(%d), cellId(%d), ueId(%d)\n",\
                  rbId, cellId, ueId));
#endif
         cmMemcpy((U8*)rbCb, (U8 *)&tRbCb, sizeof(KwUlRbCb));

         RETVALUE(ret);
      }
   }

   /* Fill entCfm structure */
   KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_OK, CKW_CFG_REAS_NONE);

   RETVALUE(ROK);
} /* kwCfgReCfgRb */


/** @details
 * This primitive deletes the existing RB in Ue/Cell Cb.
 *
 * - If UE ID is 0 then
 *   - Check for CELL CB is present
 *   - If yes, Check for RB ID
 *     - If RB ID is prenset Delete the RB CB
 *       - If there is no RB CB exist in CELL CB then Delete CELL CB.
 *     - Else, Status Indication with Reason
 *   - Else, Status Indication with Reason
 * - Else,
 *   - Check for UE CB is present
 *   - If yes, Check for RB ID
 *     - If RB ID is prenset Delete the RB CB
 *       - If there is no RB CB exist in UE CB then Delete UE CB.
 *     - Else, Status Indication with Reason
 *   - Else, Status Indication with Reason
 * - Fill entity confirmation
 *
 * @param [in]    ueId     -  UE Identifier
 * @param [in]    cellId   -  CELL Identifier
 * @param [in]    entCfg   -  Entity Configuration to be done.
 * @param [out]   entCfm   -  Entity Confirmation
 *
 * @return  ROK
 */
#ifdef ANSI
PUBLIC S16 kwCfgDelUlRb
(
KwCb              *gCb,
CmLteRnti         ueId,
CmLteCellId       cellId,
CkwEntCfgInfo     *entCfg,
CkwEntCfgCfmInfo  *entCfm
)
#else
PUBLIC S16 kwCfgDelRb(gCb,ueId, cellId, entCfg, entCfm)
KwCb              *gCb;
CmLteRnti         ueId;
CmLteCellId       cellId;
CkwEntCfgInfo     *entCfg;
CkwEntCfgCfmInfo  *entCfm;
#endif
{
   S16                  ret;           /* Return Value */
   CmLteRlcId           rlcId;         /* RLC Identifier */
   KwUlUeCb               *ueCb;         /* UE Control Block */
   KwUlCellCb             *cellCb;       /* UE Control Block */
   KwUlRbCb               *kwRbCb;       /* KW RB Control Block */
   U8                   rbId;          /* RB Identifier */
   U8                   rbType;        /* RB type */

   TRC3(kwCfgDelUlRb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,\
            "kwCfgDelRb(ueId(%d), cellId(%d), cfgType(%d))\n",\
            ueId, cellId, entCfg->cfgType));
#endif

   ret = ROK;
   rbId = entCfg->rbId;
   rbType = entCfg->rbType;

   /* Validate the RBID in case of TM/UM/AM */
   KW_VALIDATE_RBID(ueId, rbId, rbType, ret);
   if (ret != ROK)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, entCfg->rbId, rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_RB_UNKWN);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgReEstRb -- KW_VALIDATE_RBID Failed --\
               rbId(%d), rbType(%d), cellId(%d), ueId(%d)\n",\
               rbId, rbType, cellId, ueId));
#endif

      RETVALUE(ret);
   }

   /* Get cellCb and delete rbCb from it */
   if (ueId == 0)
   {
      /* Get rbId */
      KW_MEM_ZERO(&rlcId, sizeof(CmLteRlcId));
      rlcId.ueId = ueId;
      rlcId.cellId = cellId;
      rlcId.rbId = entCfg->rbId;

      /* Get cellCb */
      ret = kwDbmFetchUlCellCb(gCb,cellId, &cellCb);
      if (ret != ROK)
      {
         /* Fill entCfm structure */
         KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
               CKW_CFG_REAS_RB_UNKWN);

#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwCfgDelRb -- kwDbmFetchCellCb - RB CB not present --\
                  rbId(%d), cellId(%d)\n", rbId, cellId));
#endif

         RETVALUE(ret);
      }

      /* Get rbCb */
      KW_DBM_FETCH_CELL_UL_RBCB(rbId, cellCb->rbCb, kwRbCb);

      if ( kwRbCb == NULLP)
      {
         /* Fill entCfm structure */
         KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
               CKW_CFG_REAS_RB_UNKWN);

#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwCfgDelRb -- kwDbmFetchRbCb - RB CB present --\
                  rbId(%d), cellId(%d)\n", rbId, cellId));
#endif

         RETVALUE(ret);
      }

      /* Assign NULLP to rbCb in rbCbLst */
      cellCb->rbCb[rbId] = NULLP;

      /* Assign NULLP to dlRbCb/ulRbCb.
       * Delete Hashlist allocated for it if any */
      cellCb->lCh[kwRbCb->lch.lChId].ulRbCb = NULLP;
   }
    /* Get ueCb and delete rbCb from it */
   else
   {
      /* Get ueCb */
      ret = kwDbmFetchUlUeCb(gCb,ueId, cellId, &ueCb);
      if (ret != ROK)
      {
         /* Fill entCfm structure */
         KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
               CKW_CFG_REAS_UE_UNKWN);

#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwCfgDelRb -- kwDbmFetchRbCb - RB CB present --\
                  rbId(%d), ueId(%d), cellId(%d)\n", rbId, ueId, cellId));
#endif

         RETVALUE(ret);
      }

      /* Get rbCb */
      KW_DBM_FETCH_UL_RBCB(rbId, rbType, ueCb, kwRbCb);

      if ( kwRbCb == NULLP)
      {
         /* Fill entCfm structure */
         KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
               CKW_CFG_REAS_RB_UNKWN);

#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwCfgDelRb -- kwDbmFetchRbCb - RB CB present --\
                  rbId(%d), ueId(%d), cellId(%d)\n", rbId, ueId, cellId));

#endif

         RETVALUE(ret);
      }

      ueCb->lCh[kwRbCb->lch.lChId].ulRbCb = NULLP;

      /* Free the Buffers of RbCb */
      kwUtlFreeUlRbCb(gCb,kwRbCb);

      /* Assign NULLP to rbCb in rbCbLst */
      if ( rbType == CM_LTE_SRB )
      {
         ueCb->srbCb[rbId] = NULLP;
      }
      else
      {
         ueCb->drbCb[rbId] = NULLP;
      }
   }
/* kw005.201 added support for L2 Measurement */         
#ifdef LTE_L2_MEAS_RLC
   /* Check if measurement is running, if yes send an alarm to LM. */
   if(kwRbCb->rbL2Cb.measOn)
   {
       KW_SEND_UEID_ALARM(gCb,kwRbCb->ueCb->key.ueId, kwRbCb->qci,
                          LKW_EVT_MEAS_HALT, LKW_CAUSE_RB_DELETION);
   }
   cmHashListDelete(&(gCb->kwL2Cb.qciHlCp), (PTR)kwRbCb); 
#endif /* LTE_L2_MEAS_RLC */
   /* Delete RbCb  */

   KW_DBM_DELETE_UL_RBCB(gCb,kwRbCb);
   if (kwRbCb != NULLP)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_RB_UNKWN);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgDelRb -- KW_DBM_DELETE_RBCB - Failed --\
               rbId(%d), cellId(%d), ueId(%d)\n", entCfg->rbId, cellId, ueId));
#endif
      RETVALUE(ret);
   }

   /* Fill entCfm structure */
   KW_CFG_FILL_CFG_CFM(entCfm, rbId, rbType, CKW_CFG_CFM_OK, CKW_CFG_REAS_NONE);

   RETVALUE(ret);
} /* kwCfgDelRb */


/** @details
 * This primitive re-establish the existing RB in Ue/Cell Cb.
 *
 * - If UE ID is 0 then
 *   - Check for CELL CB is present
 *   - If yes, Check for RB ID
 *     - If RB ID is prenset initialize the parameters of the RB CB
 *     - Else, Status Indication with Reason
 *   - Else, Status Indication with Reason
 * - Else,
 *   - Check for UE CB is present
 *   - If yes, Check for RB ID
 *     - If RB ID is prenset initialize the parameters of the RB CB
 *     - Else, Status Indication with Reason
 *   - Else, Status Indication with Reason
 * - Fill entity confirmation
 *
 * @param [in]    ueId     -  UE Identifier
 * @param [in]    cellId   -  CELL Identifier
 * @param [in]    entCfg   -  Entity Configuration to be done.
 * @param [out]   entCfm   -  Entity Confirmation
 *
 * @return  ROK
 */
#ifdef ANSI
PUBLIC S16 kwCfgReEstUlRb
(
KwCb             *gCb,
CmLteRnti         ueId,
CmLteCellId       cellId,
Bool              sndReEstInd,
CkwEntCfgInfo     *entCfg,
CkwEntCfgCfmInfo  *entCfm
)
#else
PUBLIC S16 kwCfgReEstUlRb(gCb,ueId, cellId,sndReEstInd,entCfg, entCfm)
KwCb             *gCb;
CmLteRnti         ueId;
CmLteCellId       cellId;
Bool              sndReEstInd;
CkwEntCfgInfo     *entCfg;
CkwEntCfgCfmInfo  *entCfm;
#endif
{
   S16                  ret;           /* Return Value */
   KwUlRbCb            *rbCb;         /* RB Control Block */
   CmLteRlcId           rlcId;         /* RLC Identifier */

   TRC3(kwCfgReEstUlRb)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,\
            "kwCfgReEstUlRb(ueId(%d), cellId(%d), cfgType(%d))\n",\
            ueId, cellId, entCfg->cfgType));
#endif

   /* Get rlcId */
   KW_MEM_ZERO(&rlcId, sizeof(CmLteRlcId));
   rlcId.ueId = ueId;
   rlcId.cellId = cellId;
   rlcId.rbId = entCfg->rbId;
   rlcId.rbType = entCfg->rbType;
   ret = ROK;

   /* Validate the RBID in case of TM/UM/AM */
   KW_VALIDATE_RBID(ueId, rlcId.rbId, rlcId.rbType, ret);
   if (ret != ROK)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, entCfg->rbId, rlcId.rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_RB_UNKWN);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgReEstRb -- KW_VALIDATE_RBID Failed --\
               rbId(%d), cellId(%d), ueId(%d)\n",\
               rlcId.rbId, rlcId.cellId, rlcId.ueId));
#endif

      RETVALUE(ret);
   }

   ret = kwDbmFetchUlRbCbForUi(gCb,rlcId, &rbCb);
   if (ret != ROK)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, entCfg->rbId, rlcId.rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_RB_UNKWN);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgReEstRb -- kwDbmFetchRbCbForUi Failed --\
               rbId(%d), rbType(%d), cellId(%d), ueId(%d)\n",\
               rlcId.rbId, rlcId.rbType, rlcId.cellId, rlcId.ueId));
#endif
      RETVALUE(ret);
   }

   switch (rbCb->mode)
   {
      case CM_LTE_MODE_TM:
         {
            ret = kwTmmUlReEstablish(gCb,rbCb);
            break;
         }

      case CM_LTE_MODE_UM:
         {
            ret = kwUmmUlReEstablish(gCb,rlcId,sndReEstInd,rbCb);
            break;
         }

      case CM_LTE_MODE_AM:
         {
            ret = kwAmmUlReEstablish(gCb,rlcId,sndReEstInd,rbCb);
            break;
         }
   }
#if (ERRCLASS & ERRCLS_DEBUG)
   if (ret != ROK)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, entCfg->rbId, rlcId.rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_REEST_FAIL);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
            "kwCfgReEstRb Failed -- Mode(%d) rbId(%d), cellId(%d), ueId(%d)\n",\
             rbCb->mode, rlcId.rbId, rlcId.cellId, rlcId.ueId));
#endif

      RETVALUE(ret);
   }
#endif /* (ERRCLASS & ERRCLS_DEBUG) */

   /* Fill entCfm structure */
   KW_CFG_FILL_CFG_CFM(entCfm, entCfg->rbId, entCfg->rbType,\
      CKW_CFG_CFM_OK, CKW_CFG_REAS_NONE);

   RETVALUE(ROK);
} /* kwCfgReEstRb */


/** @details
 * This primitive deletes the RBs in Ue Cb.
 *
 * - If UE ID is 0 then
 *   - Status Indication with Reason
 * - Else,
 *   - Check for UE CB is present
 *   - If yes, Delete all RB CB in UE CB and Delete UE CB also.
 *   - Else, Status Indication with Reason
 * - Fill entity confirmation
 *
 * @param [in]    ueId     -  UE Identifier
 * @param [in]    cellId   -  CELL Identifier
 * @param [in]    entCfg   -  Entity Configuration to be done.
 * @param [out]   entCfm   -  Entity Confirmation
 *
 * @return  ROK
 */
#ifdef ANSI
PUBLIC S16 kwCfgDelUlUe
(
KwCb             *gCb,
CmLteRnti         ueId,
CmLteCellId       cellId,
CkwEntCfgInfo     *entCfg,
CkwEntCfgCfmInfo  *entCfm
)
#else
PUBLIC S16 kwCfgDelUlUe(ueId, cellId, entCfg, entCfm)
KwCb             *gCb;
CmLteRnti         ueId;
CmLteCellId       cellId;
CkwEntCfgInfo     *entCfg;
CkwEntCfgCfmInfo  *entCfm;
#endif
{
   S16            ret;                 /* Return Value */
   KwUlUeCb         *ueCb;               /* UE Control Block */

   TRC3(kwCfgDelUe)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,\
            "kwCfgDelUe(ueId(%d), cellId(%d), cfgType(%d))\n",\
            ueId, cellId, entCfg->cfgType));
#endif

   ret = ROK;

   /* Check for ueId is present or not */
   if ( ueId == 0 )
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, entCfg->rbId, entCfg->rbType,\
          CKW_CFG_CFM_NOK, CKW_CFG_REAS_UE_UNKWN);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwCfgDelUe -- UeId is 0  -- cellId(%d)\n", cellId));
#endif

      RETVALUE(RFAILED);
   }

   /* Fetch Ue Cb */
   ret = kwDbmFetchUlUeCb(gCb,ueId, cellId, &ueCb);
   if (ret != ROK)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, entCfg->rbId, entCfg->rbType,\
         CKW_CFG_CFM_NOK, CKW_CFG_REAS_UE_UNKWN);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
            "kwCfgDelUe -- kwDbmFetchUeCb - Failed -- cellId(%d), ueId(%d)\n",
            cellId, ueId));
#endif
      RETVALUE(RFAILED);
   }

   /* Delete Ue Cb */
   ret = kwDbmDelUlUeCb(gCb,ueCb, FALSE);
   if (ret != ROK)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, entCfg->rbId, entCfg->rbType,\
      CKW_CFG_CFM_NOK, CKW_CFG_REAS_UE_UNKWN);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgDelUe -- kwDbmDelUeCb - Failed --\
               cellId(%d), ueId(%d)\n", cellId, ueId));
#endif
      RETVALUE(RFAILED);
   }

   /* Fill entCfm structure */
   KW_CFG_FILL_CFG_CFM(entCfm, entCfg->rbId, entCfg->rbType,\
      CKW_CFG_CFM_OK, CKW_CFG_REAS_NONE);

   RETVALUE(ROK);
} /* kwCfgDelUe */


/**
 * This primitive deletes the RBs in Ue Cb.
 *
 * - If CELL ID is 0 then
 *   - Status Indication with Reason
 * - Else,
 *   - Check for CELL CB is present
 *   - If yes, Delete all RB CB in CELL CB and Delete CELL CB also.
 *   - Else, Status Indication with Reason
 * - Fill entity confirmation
 *
 * @param [in]    cellId   -  CELL Identifier
 * @param [in]    entCfg   -  Entity Configuration to be done.
 * @param [out]   entCfm   -  Entity Confirmation
 *
 * @return  ROK
 */
#ifdef ANSI
PUBLIC S16 kwCfgDelUlCell
(
KwCb              *gCb,
CmLteCellId       cellId,
CkwEntCfgInfo     *entCfg,
CkwEntCfgCfmInfo  *entCfm
)
#else
PUBLIC S16 kwCfgDelCell(gCb,cellId, entCfg, entCfm)
KwCb              *gCb;
CmLteCellId       cellId;
CkwEntCfgInfo     *entCfg;
CkwEntCfgCfmInfo  *entCfm;
#endif
{
   S16            ret;                 /* Return Value */
   KwUlCellCb       *cellCb;             /* UE Control Block */
   U8             rbId;                /* RB Identifier */

   TRC3(kwCfgDelCell)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_BRIEF), (gCb->init.prntBuf,\
            "kwCfgDelCell( cellId(%d), cfgType(%d))\n",\
            cellId, entCfg->cfgType));
#endif

   ret = ROK;
   cellCb = NULLP;
   rbId = entCfg->rbId;

   /* Check for ueId is present or not */
   if ( cellId == 0 )
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, rbId, entCfg->rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_CELL_UNKWN);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
               "kwCfgDelCell Failed -- cellId is 0  -- cellId(%d)\n", cellId));
#endif

      RETVALUE(RFAILED);
   }

   /* Fetch Ue Cb */
   ret = kwDbmFetchUlCellCb(gCb,cellId, &cellCb);
   if (ret != ROK)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, rbId, entCfg->rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_CELL_UNKWN);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
            "kwCfgDelCell -- kwDbmFetchCellCb - Failed -- cellId(%d)\n",
            cellId));
#endif
      RETVALUE(RFAILED);
   }

   /* Delete Ue Cb */
   ret = kwDbmDelUlCellCb(gCb,cellCb);
   if (ret != ROK)
   {
      /* Fill entCfm structure */
      KW_CFG_FILL_CFG_CFM(entCfm, rbId, entCfg->rbType, CKW_CFG_CFM_NOK,\
            CKW_CFG_REAS_CELL_UNKWN);

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgDelCell -- kwDbmDelCellCb - Failed --\
               cellId(%d)\n", cellId));
#endif
      RETVALUE(RFAILED);
   }

   /* Fill entCfm structure */
  /* kw005.201 added support for L2 Measurement */         
   KW_CFG_FILL_CFG_CFM(entCfm, rbId, entCfg->rbType, CKW_CFG_CFM_OK,\
                       CKW_CFG_REAS_NONE);

   RETVALUE(ROK);
} /* kwCfgDelCell */

/**
 * This primitive changes the ueId of Ue Cb.
 *
 * - If oldUeId and newUeId are
 *   - Confirm the Status with Reason
 * - If UeId not present
 *   - Confirm the Status with Reason
 * - Create New UeCb
 * - Copy rbCbs from old UeCb to new UeCb
 * - Delete old UeCb
 * - Fill entity confirmation
 *
 * @param [in]    ueInfo      -  Old UE Information
 * @param [in]    newUeInfo   -  New UE Information
 * @param [out]   status      -  Status
 *
 * @return  ROK
 */
#ifdef ANSI
PUBLIC S16 kwCfgUlUeIdChng
(
KwCb      *gCb,
CkwUeInfo *ueInfo,
CkwUeInfo *newUeInfo,
CmStatus  *status
)
#else
PUBLIC S16 kwCfgUlUeIdChng(gCb,ueInfo,newUeInfo,status)
KwCb      *gCb;
CkwUeInfo *ueInfo;
CkwUeInfo *newUeInfo;
CmStatus  *status;
#endif
{
   KwUlUeCb *ueCb;
   S16    ret;
/*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   TRC3(kwCfgUeIdChng)

   if ( (ueInfo->ueId == newUeInfo->ueId) && 
        (ueInfo->cellId == newUeInfo->cellId))
   {
      status->reason = CKW_CFG_REAS_SAME_UEID;
      status->status = CKW_CFG_CFM_NOK; 

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgUeIdChng -- Failed -- cellId(%d), ueId(%d) --\
         newCellId(%d), newUeId(%d)\n", ueInfo->cellId, ueInfo->ueId,
         newUeInfo->cellId, newUeInfo->ueId));
#endif
      RETVALUE(RFAILED);
   } 
   
   ret = kwDbmFetchUlUeCb(gCb,newUeInfo->ueId, newUeInfo->cellId, &ueCb);
   if (ret == ROK)
   {

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgUeIdChng -- NewUeCb already Exists -- cellId(%d), \
               ueId(%d)\n", newUeInfo->cellId, newUeInfo->ueId));
#endif
      status->reason = CKW_CFG_REAS_UE_EXISTS;
      status->status = CKW_CFG_CFM_NOK;
      RETVALUE(RFAILED);
   }
  
   ret = kwDbmFetchUlUeCb(gCb,ueInfo->ueId, ueInfo->cellId, &ueCb);
   if (ret != ROK)
   {

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgUeIdChng -- kwDbmFetchUeCb Failed -- cellId(%d), \
               ueId(%d)\n", ueInfo->cellId, ueInfo->ueId));
#endif
      status->reason = CKW_CFG_REAS_UE_UNKWN;
      status->status = CKW_CFG_CFM_NOK;
      RETVALUE(RFAILED);
   }
  
   ret = cmHashListDelete(&(gCb->u.ulCb->ueLstCp), (PTR) ueCb);
   if (ret != ROK)
   {

#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgUeIdChng -- cmHashListDelete Failed -- cellId(%d), \
               ueId(%d)\n", ueInfo->cellId, ueInfo->ueId));
#endif
      status->reason = CKW_CFG_REAS_UE_CREAT_FAIL;
      status->status = CKW_CFG_CFM_NOK;
      RETVALUE(RFAILED);
   }
   
   /* update the hash key with new values */ 
   ueCb->key.ueId = newUeInfo->ueId;
   ueCb->key.cellId = newUeInfo->cellId;

    ret = cmHashListInsert(&(gCb->u.ulCb->ueLstCp), (PTR)ueCb, (U8 *)&(ueCb->key),
         (U16) sizeof(KwUeKey));

  if (ret != ROK)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_CFG | KW_DBGMASK_ERROR), (gCb->init.prntBuf,\
               "kwCfgUeIdChng -- cmHashListInsert Failed -- cellId(%d), \
               ueId(%d)\n", newUeInfo->cellId, newUeInfo->ueId));
#endif
      status->reason = CKW_CFG_REAS_UE_CREAT_FAIL;
      status->status = CKW_CFG_CFM_NOK;
   }  
  
   RETVALUE(ret);
} /* kwCfgUeIdChng */

/********************************************************************30**

         End of file:     kw_cfg_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:44 2014

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
/main/1      ---       gk        1. Initial release.
/main/2      ---       nm        1. LTERLC Release 2.1.
/main/3      kw004.201 av        1. Adding missing trace  
/main/4      kw005.201 ap        1. Removed numLc from statistics. 
                                 2. Added support for L2 Measurement.
                                 3. Fix for ccpu00119143. 
                       rd        4. Code updated with important Avtecs comments.
*********************************************************************91*/




