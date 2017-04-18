



/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_sch_uhm.c
  
     Sid:      gk_sch_uhm.c@@/main/2 - Sat Jul 30 02:21:52 2011
  
     Prg:      sd
  
**********************************************************************/

/** @file rg_sch_uhm.c
@brief This module handles uplink harq related functionality in MAC.
*/

/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */

#include "cm_lte.h"        /* Common LTE */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* memory management */

#include "rg_env.h"        /* MAC Environment Defines */
#include "tfu.h"           /* TFU Interface defines */
#include "rgr.h"           /* RGR Interface defines */
#include "lrg.h"           /* LRG Interface defines */

#include "rg_sch.h"            /* Scheduler defines */
#include "rg_sch_inf.h"            /* Scheduler defines */
#include "rg_sch_err.h"        /* MAC error defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* system services */
#include "cm_lte.x"        /* Common LTE */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"       /* memory management */

#include "tfu.x"           /* TFU Interface defines */
#include "rgr.x"           /* RGR Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgm.x"
#include "rg_sch_inf.x"            /* Scheduler defines */
#include "rg_sch.x"            /* Scheduler includes */
#include "rg_sch_cmn.h"
#include "rg_sch_cmn.x"

/* local defines */

/* local typedefs */
 
/* local externs */
 
/* forward references */


PUBLIC U8 rgRvIdxTable[] = {0, 3, 1, 2}; /* This gives rvIdx for a given rv */
PUBLIC U8 rgRvTable[] = {0, 2, 3 ,1};    /* This gives rv for a given rvIdx */

/**
 * @brief Handler for HARQ processing on recieving Data indication from PHY.
 *
 * @details
 *
 *     Function: rgSCHUhmProcDatInd
 *     
 *     Invoked by: rgSCHTomTfuDatInd of  TOM
 *
 *     Processing Steps:
 *      - Set rcvdCrcInd variable to TRUE
 *           
 *  @param[in] *cell
 *  @param[in] *ue
 *  @param[in] frm
 *  @return  Void
 **/
#ifndef MAC_SCH_STATS
#ifdef ANSI
PUBLIC Void rgSCHUhmProcDatInd
(
RgSchCellCb          *cell,
RgSchUeCb            *ue,
CmLteTimingInfo      frm
)
#else
PUBLIC Void rgSCHUhmProcDatInd(cell, ue, frm)
RgSchCellCb          *cell;
RgSchUeCb            *ue;
CmLteTimingInfo      frm;
#endif
#else  /* MAC_SCH_STATS */
#ifdef ANSI
PUBLIC Void rgSCHUhmProcDatInd
(
RgSchCellCb          *cell,
RgSchUeCb            *ue,
CmLteTimingInfo      frm,
U8                   cqi
)
#else
PUBLIC Void rgSCHUhmProcDatInd(cell, ue, frm, cqi)
RgSchCellCb          *cell;
RgSchUeCb            *ue;
CmLteTimingInfo      frm;
U8                   cqi;
#endif
#endif /* MAC_SCH_STATS */
{
   RgSchUlHqProcCb   *hqProc;
#ifdef UL_LA
   RgSchCmnUlUe   *ueUl = RG_SCH_CMN_GET_UL_UE(ue, cell);
   S32            iTbs;
   U8             maxiTbs = rgSchCmnUlCqiToTbsTbl[cell->isCpUlExtend]
                                                 [ueUl->maxUlCqi];
#endif

   TRC2(rgSCHUhmProcDatInd);

   rgSCHUtlUlHqProcForUe(cell, frm, ue, &hqProc);
#ifdef UL_LA
#ifdef LTEMAC_SPS
   if((hqProc->isSpsActvnHqP != TRUE)  &&
      (hqProc->isSpsOccnHqP != TRUE))
#endif
   {
      ueUl->ulLaCb.deltaiTbs += UL_LA_STEPUP;
      iTbs = (ueUl->ulLaCb.cqiBasediTbs + ueUl->ulLaCb.deltaiTbs)/100;

      if (iTbs > maxiTbs)
      {
         ueUl->ulLaCb.deltaiTbs = (maxiTbs * 100) - ueUl->ulLaCb.cqiBasediTbs;
      }

   }
#endif
#ifdef MAC_SCH_STATS
   /** Stats update over here 
    */
   {
      hqFailStats.ulCqiStat[cqi - 1].numOfAcks++;
   }
#endif

   hqProc->rcvdCrcInd = TRUE;
#ifdef TENB_STATS
   /* UL stats are filled in primary index as of now */
   cell->tenbStats->sch.ulAckNack[rgRvTable[hqProc->rvIdx]]++;
   ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(cell)].ulAckNackCnt++;
   if(hqProc->alloc)
   {
      ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(cell)].ulTpt += (hqProc->alloc->grnt.datSz << 3);
      cell->tenbStats->sch.ulTtlTpt +=(hqProc->alloc->grnt.datSz << 3);//pverma
   }
#endif
#ifdef LTE_TDD
   RGSCH_UPD_PHICH(cell->ulDlCfgIdx, frm.subframe, hqProc);
#endif
   
   RETVOID;
}  /* rgSCHUhmProcDatInd */

/**
 * @brief Handler for HARQ processing on recieving Data indication from PHY.
 *
 * @details
 *
 *     Function: rgSCHUhmProcMsg3DatInd
 *     
 *     Invoked by: rgSCHTomTfuDatInd of  TOM
 *
 *     Processing Steps:
 *      - Set rcvdCrcInd variable to TRUE  
 *           
 *  @param[in,out] *hqProc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHUhmProcMsg3DatInd
(
RgSchUlHqProcCb *hqProc
)
#else
PUBLIC Void rgSCHUhmProcMsg3DatInd(hqProc)
RgSchUlHqProcCb *hqProc;
#endif
{
   TRC2(rgSCHUhmProcMsg3DatInd);
   hqProc->rcvdCrcInd = TRUE;
   RETVOID;
}  /* rgSCHUhmProcMsg3DatInd */

/**
 * @brief Handler for HARQ processing on recieving Data indication from PHY.
 *
 * @details
 *
 *     Function: rgSCHUhmProcMsg3Failure
 *     
 *     Invoked by: rgSCHTomTfuDatInd of  TOM
 *
 *     Processing Steps:
 *      - Set rcvdCrcInd variable to TRUE  
 *           
 *  @param[in,out] *hqProc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHUhmProcMsg3Failure
(
RgSchUlHqProcCb *hqProc
)
#else
PUBLIC Void rgSCHUhmProcMsg3Failure(hqProc)
RgSchUlHqProcCb *hqProc;
#endif
{
   TRC2(rgSCHUhmProcMsg3Failure);

   hqProc->rcvdCrcInd = FALSE;
   RETVOID;
}  /* rgSCHUhmProcMsg3Failure */

/**
 * @brief Handler for HARQ processing on recieving Decode failure from PHY.
 *
 * @details
 *
 *     Function: rgSCHUhmProcHqFailure
 *     
 *     Invoked by: rgSCHTomTfuDecFailInd of TOM
 *
 *     Processing Steps: 
 *      - Update NACK information in harq info.
 *      - Update RV index of received RV from PHY in harq info.
 *      - Set PhichInfo in DlSf
 *           
 *  @param[in] *cell
 *  @param[in] *ue
 *  @param[in] frm
 *  @param[in] rv
 *  @return  Void
 **/
#ifndef MAC_SCH_STATS
#ifdef ANSI
PUBLIC Void rgSCHUhmProcHqFailure
(
RgSchCellCb          *cell,
RgSchUeCb            *ue,
CmLteTimingInfo      frm,
TknU8                rv
)
#else
PUBLIC Void rgSCHUhmProcHqFailure(cell, ue, frm, rv)
RgSchCellCb          *cell;
RgSchUeCb            *ue;
CmLteTimingInfo      frm;
TknU8                rv;
#endif
#else /* MAC_SCH_STATS */
#ifdef ANSI
PUBLIC Void rgSCHUhmProcHqFailure
(
RgSchCellCb          *cell,
RgSchUeCb            *ue,
CmLteTimingInfo      frm,
TknU8                rv,
U8                   cqi
)
#else
PUBLIC Void rgSCHUhmProcHqFailure(cell, ue, frm, rv, cqi)
RgSchCellCb          *cell;
RgSchUeCb            *ue;
CmLteTimingInfo      frm;
TknU8                rv;
U8                   cqi;
#endif
#endif /* MAC_SCH_STATS */
{
   RgSchUlHqProcCb   *hqProc;
#ifdef UL_LA
   RgSchCmnUlUe   *ueUl = RG_SCH_CMN_GET_UL_UE(ue,cell);
   S32               iTbs;
#endif
   TRC2(rgSCHUhmProcHqFailure);

   rgSCHUtlUlHqProcForUe(cell, frm, ue, &hqProc);
#ifdef UL_LA
#ifdef LTEMAC_SPS
   if((hqProc->isSpsActvnHqP != TRUE)  &&
      (hqProc->isSpsOccnHqP != TRUE))
#endif
   {
      ueUl->ulLaCb.deltaiTbs -= UL_LA_STEPDOWN;
      iTbs = (ueUl->ulLaCb.cqiBasediTbs + ueUl->ulLaCb.deltaiTbs)/100;

      if (iTbs < 0)
      {
         ueUl->ulLaCb.deltaiTbs = -(ueUl->ulLaCb.cqiBasediTbs);
      }

   } 
#endif
#ifdef MAC_SCH_STATS
   /** Stats update over here */
   {
      static U32 retxCnt = 0;
      ++retxCnt;
      hqFailStats.ulCqiStat[cqi - 1].numOfNacks++;
   }
#endif /* MAC_SCH_STATS */

   hqProc->rcvdCrcInd = FALSE;
#ifdef TENB_STATS
   /* UL stats are filled in primary index as of now */
   cell->tenbStats->sch.ulAckNack[rgRvTable[hqProc->rvIdx]]++;
   ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(cell)].ulAckNackCnt++;
   cell->tenbStats->sch.ulNack[rgRvTable[hqProc->rvIdx]]++;
   ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(cell)].ulNackCnt++;
#endif
   hqProc->rvIdxPhy.pres = rv.pres;
   if(rv.pres)
   {
      hqProc->rvIdxPhy.val = rgRvIdxTable[rv.val];
   }
#ifdef LTE_TDD
   RGSCH_UPD_PHICH(cell->ulDlCfgIdx, frm.subframe, hqProc);
#endif
   RETVOID;
} /* rgSCHUhmProcHqFailure */

/**
 * @brief Handler for identifying the HARQ process cb associated with the
 * index.
 *
 * @details
 *
 *     Function: rgSCHUhmGetUlHqProc
 *     
 *     Processing Steps: 
 *      - Return pointer to uplink harq process corresponding to the timing
 *        information passed.
 *           
 *  @param[in]  *ue
 *  @param[in]  idx
 *  @return  RgSchUlHqProcCb*
 *      -# Pointer to harq process corresponding to index
 *      -# NULL
 **/
#ifdef ANSI
PUBLIC RgSchUlHqProcCb* rgSCHUhmGetUlHqProc
(
RgSchCellCb      *cell,
RgSchUeCb        *ue, 
U8               idx
)
#else
PUBLIC RgSchUlHqProcCb* rgSCHUhmGetUlHqProc(cell, ue, idx)
RgSchCellCb      *cell;
RgSchUeCb        *ue; 
U8               idx;
#endif
{
   RgSchCmnUlUe *ueUl = RG_SCH_CMN_GET_UL_UE(ue, cell);
   TRC2(rgSCHUhmGetUlHqProc);

#if (ERRCLASS & ERRCLS_DEBUG)
   if(idx >= ueUl->hqEnt.numHqPrcs)
   {
      RETVALUE(NULLP);
   }
#endif
   RETVALUE(&(ueUl->hqEnt.hqProcCb[idx]));
}  /* rgSCHUhmGetUlHqProc */

/**
 * @brief Handler for HARQ processing on recieving new trasmission indication 
 * from USM.
 *
 * @details
 *
 *     Function: rgSCHUhmNewTx
 *     
 *     Invoked by: USM
 *
 *     Processing Steps: 
 *      - Update harq info with values indicating new HARQ transmission.
 *           
 *  @param[in,out]  *hqProc
 *  @param[in]      *alloc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHUhmNewTx
(
RgSchUlHqProcCb *hqProc,
U8              maxHqRetx,
RgSchUlAlloc    *alloc
)
#else
PUBLIC Void rgSCHUhmNewTx(hqProc, maxHqRetx, alloc)
RgSchUlHqProcCb *hqProc;
U8              maxHqRetx;
RgSchUlAlloc    *alloc;
#endif
{
   TRC2(rgSCHUhmNewTx);

   hqProc->ndi ^= 1;
   hqProc->alloc = alloc;
   hqProc->remTx = maxHqRetx;
   hqProc->rcvdCrcInd = FALSE;
   hqProc->rvIdx = 0;
   hqProc->rvIdxPhy.pres = FALSE;
#ifdef LTE_L2_MEAS
   if (hqProc->alloc->ue)
   {
      ((RgUeUlHqCb*)hqProc->hqEnt)->numBusyHqProcs++;
   }
#endif
   RETVOID;
}  /* rgSCHUhmNewTx */

/**
 * @brief Free an uplink HARQ process.
 *
 * @details
 *
 *     Function: rgSCHUhmFreeProc
 *     
 *     Invoked by: USM
 *
 *     Processing Steps: 
 *      - Set alloc pointer to NULLP
 *           
 *  @param[in]  RgSchUlHqProcCb   *hqProc
 *  @param[in]  RgSchCellCb      *cell
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHUhmFreeProc
(
RgSchUlHqProcCb *hqProc,
RgSchCellCb      *cell
)
#else
PUBLIC Void rgSCHUhmFreeProc(hqProc, cell)
RgSchUlHqProcCb *hqProc;
RgSchCellCb      *cell;
#endif
{
#ifdef LTEMAC_SPS
   RgSchCmnUlUeSpsInfo   *ulSpsUe = NULLP;
#endif
#ifdef LTE_L2_MEAS
   RgSchUeCb         *ueCb;
   U8 qci = 1;
#endif
   TRC2(rgSCHUhmFreeProc);
#ifdef LTEMAC_SPS
   /*For SPS allocations, harq proc will not be linked to
    * alloc at the time of allocation from 2nd occassion onwards and hence harq
    * proc passed to this function may be NULLP*/
   if(hqProc == NULLP)
   {
      RETVOID;
   }
   else
   {
      RgSchUeCb         *ue;
      /* Check if this Harq proc was used for sending UL SPS
         Actvn PDCCH. In this case set pdcchToRetx to TRUE
         to ensure resending of UL SPS Actvn PDCCH */
      if (hqProc->alloc)
      {
         ue = hqProc->alloc->ue;
         if (ue && (TRUE == hqProc->isSpsActvnHqP))
         {
            ulSpsUe = RG_SCH_CMN_GET_UL_SPS_UE(ue, cell);
            if (ulSpsUe->state == RGSCH_SPS_ACTV_PDCCH_SENT)
            {
               ulSpsUe->pdcchToRetx = TRUE;
               ulSpsUe->actPdcchCrcFailCount++;
            }
         }
      }
   }
   hqProc->isSpsActvnHqP = FALSE;
   hqProc->isSpsOccnHqP = FALSE;
#endif

#ifdef LTE_L2_MEAS
   if (hqProc->alloc && hqProc->alloc->ue)
   {
      ueCb = hqProc->alloc->ue;
      if (ueCb && cell)
      {
         U32 nonLcg0ReportedBs = ((RgSchCmnLcg *)(ueCb->ul.lcgArr[1].sch))->reportedBs + \
                               ((RgSchCmnLcg *)(ueCb->ul.lcgArr[2].sch))->reportedBs + \
                               ((RgSchCmnLcg *)(ueCb->ul.lcgArr[3].sch))->reportedBs;
         ((RgUeUlHqCb*)hqProc->hqEnt)->numBusyHqProcs--;
         if (! ((RgUeUlHqCb*)hqProc->hqEnt)->numBusyHqProcs && !(nonLcg0ReportedBs))
         {
            while (ueCb->ulActiveLCs)
            {
               if (ueCb->ulActiveLCs & 0x1)
               {
                  cell->qciArray[qci].ulUeCount--;
               }
               qci++;
               ueCb->ulActiveLCs >>= 1;
            }
         }
      }
   }
#endif
   hqProc->alloc = NULLP;
   hqProc->ulSfIdx = RGSCH_INVALID_INFO;
   /*ccpu00116293 - Correcting relation between UL subframe and DL subframe based on RG_UL_DELTA*/
   hqProc->isRetx  = FALSE;
   RETVOID;
}  /* rgSCHUhmFreeProc */

/**
 * @brief Handler for HARQ processing on recieving re-trasmission 
 * indication from USM.
 *
 * @details
 *
 *     Function: rgSCHUhmRetx
 *     
 *     Invoked by: USM
 *
 *     Processing Steps: 
 *      - Update harq info with values corresponding to
 *        re-transmission. 
 *           
 *  @param[in,out]  *hqProc
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHUhmRetx
(
RgSchUlHqProcCb *hqProc,
RgSchUlAlloc    *alloc
)
#else
PUBLIC Void rgSCHUhmRetx(hqProc, alloc) 
RgSchUlHqProcCb *hqProc;
RgSchUlAlloc    *alloc;
#endif
{
   TRC2(rgSCHUhmRetx);

   hqProc->alloc = alloc;
   --hqProc->remTx;
   hqProc->rvIdx = (hqProc->rvIdx + 1) % 4;
   hqProc->rvIdxPhy.pres = FALSE;
   RETVOID;
}  /* rgSCHUhmRetx */


/**
 * @brief Handler for initializing the HARQ entity.
 *
 * @details
 *
 *     Function: rgSCHUhmRgrUeCfg
 *     
 *     Invoked by: RGR
 *
 *     Processing Steps: 
 *      -  Initialize maxHqRetx
 *           
 *  @param[in]      *cellCb
 *  @param[in,out]  *ueCb
 *  @param[in]      *ueCfg
 *  @param[out]     *err
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHUhmRgrUeCfg
(
RgSchCellCb       *cellCb,
RgSchUeCb         *ueCb,
RgrUeCfg          *ueCfg
)
#else
PUBLIC Void rgSCHUhmRgrUeCfg(cellCb, ueCb, ueCfg) 
RgSchCellCb       *cellCb;
RgSchUeCb         *ueCb;
RgrUeCfg          *ueCfg;
#endif
{
   U8 i;
   RgSchCmnUlUe *ueUl = RG_SCH_CMN_GET_UL_UE(ueCb, cellCb);

   TRC2(rgSCHUhmRgrUeCfg);

   ueUl->hqEnt.maxHqRetx = (ueCfg->ueUlHqCfg.maxUlHqTx - 1); 
#ifdef TFU_UPGRADE
   /* Storing the delta HARQ offset for HARQ + PUSCH */
   ueCb->ul.betaHqOffst = ueCfg->puschDedCfg.bACKIdx;
#endif
   for(i=0; i < ueUl->hqEnt.numHqPrcs; i++)
   {
      ueUl->hqEnt.hqProcCb[i].hqEnt = (void*)(&ueUl->hqEnt);
      ueUl->hqEnt.hqProcCb[i].procId = i;
      ueUl->hqEnt.hqProcCb[i].ulSfIdx = RGSCH_INVALID_INFO;
      ueUl->hqEnt.hqProcCb[i].alloc = NULLP;
#ifdef LTEMAC_SPS
      /* ccpu00139513- Initializing SPS flags*/
      ueUl->hqEnt.hqProcCb[i].isSpsActvnHqP = FALSE;
      ueUl->hqEnt.hqProcCb[i].isSpsOccnHqP = FALSE;
#endif
   }

   RETVOID;
}  /* rgSCHUhmRgrUeCfg */

/**
 * @brief Handler for re-initializing the HARQ entity.
 *
 * @details
 *
 *     Function: rgSCHUhmRgrUeRecfg
 *     
 *     Invoked by: RGR
 *
 *     Processing Steps: 
 *      -  Re-initialize maxHqRetx
 *           
 *  @param[in]      *cellCb
 *  @param[in,out]  *ueCb
 *  @param[in]      *ueCfg
 *  @param[out]     *err
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHUhmRgrUeRecfg
(
RgSchCellCb       *cellCb,
RgSchUeCb         *ueCb,
RgrUeRecfg        *ueRecfg
)
#else
PUBLIC Void rgSCHUhmRgrUeRecfg(cellCb, ueCb, ueRecfg) 
RgSchCellCb       *cellCb;
RgSchUeCb         *ueCb;
RgrUeRecfg        *ueRecfg;
#endif
{
   RgSchCmnUlUe *ueUl = RG_SCH_CMN_GET_UL_UE(ueCb, cellCb);
   TRC2(rgSCHUhmRgrUeRecfg);

   /* [ccpu00123958]-ADD- Check for HARQ Reconfig from the bit mask  */
   if(RGR_UE_ULHARQ_RECFG & ueRecfg->ueRecfgTypes)
   {
      ueUl->hqEnt.maxHqRetx = (ueRecfg->ueUlHqRecfg.maxUlHqTx - 1); 
   }

   RETVOID;
}  /* rgSCHUhmRgrUeRecfg */

/**
 * @brief Handler for de-initializing the HARQ entity.
 *
 * @details
 *
 *     Function: rgSCHUhmFreeUe
 *     
 *     Invoked by: RGR
 *
 *     Processing Steps: 
 *      - 
 *           
 *  @param[in,out]  *ueCb
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHUhmFreeUe
(
RgSchCellCb       *cellCb,
RgUeUlHqCb        *hqEnt
)
#else
PUBLIC Void rgSCHUhmFreeUe(cellCb, hqEnt) 
RgSchCellCb       *cellCb;
RgUeUlHqCb       *hqEnt;
#endif
{
   TRC2(rgSCHUhmFreeUe);
#ifdef LTE_TDD
   /* ccpu00117052 - MOD - Passing double pointer
   for proper NULLP assignment*/
   rgSCHUtlFreeSBuf(cellCb->instIdx, 
                  (Data **)(&(hqEnt->hqProcCb)),
                  hqEnt->numHqPrcs * sizeof(RgSchUlHqProcCb));
#endif

   RETVOID;
}  /* rgSCHUhmFreeUe */


/**
* @brief Handler for appending the PHICH information in to the dlSf.
*
* @details
*
*     Function: rgSCHUhmAppendPhich
*     
*     Invoked by: TOM
*
*     Processing Steps:
*      - Set PhichInfo in DlSf for each Hq
*
*  @param[in] *RgSchCellCb
*  @param[in] CmLteTimingInfo
*  @param[in] idx
*  @return  Void
*/
#ifdef ANSI
PUBLIC S16 rgSCHUhmAppendPhich
(
RgSchCellCb            *cellCb,
CmLteTimingInfo        frm,
U8                     idx
)
#else
PUBLIC S16 rgSCHUhmAppendPhich (cellCb, frm, idx)
RgSchCellCb            *cellCb;
CmLteTimingInfo        frm;
U8                     idx;
#endif
{
   U8              nDmrs;
   U8              rbStart;
#ifdef LTE_TDD
   U8              iPhich;
#endif
   RgSchUlAlloc    *ulAlloc;
#ifdef LTEMAC_HDFDD
   Bool            allwNack = TRUE;
#endif /* LTEMAC_HDFDD */
   RgSchCmnUlCell  *cellUl = RG_SCH_CMN_GET_UL_CELL(cellCb);

   TRC2(rgSCHUhmAppendPhich)

   if(cellUl->hqFdbkIdx[idx] != RGSCH_INVALID_INFO)
   {
      ulAlloc = rgSCHUtlFirstHqFdbkAlloc (cellCb, idx);
      while (ulAlloc)
      {
         /*ccpu00106104 MOD added check for ACKNACK rep*/
         /*added check for acknack so that adaptive retx considers ue 
           inactivity due to ack nack repetition*/
         if((ulAlloc->ue != NULLP) && ((TRUE != ulAlloc->forMsg3) &&
                  ((ulAlloc->ue->measGapCb.isMeasuring == TRUE) ||
                   (ulAlloc->ue->ackNakRepCb.isAckNakRep == TRUE))))
         {
            /* Mark the UE for retransmission */
            /* If UE is measuring then we should not be sending PHICH unless msg3 */
            /*UE assumes ack, if nack then do adaptive re-transmission*/
            /*ulAlloc->hqProc->rcvdCrcInd = FALSE;--*/
            ulAlloc = rgSCHUtlNextHqFdbkAlloc (cellCb, ulAlloc, idx);
            continue;
         }
#ifdef LTE_TDD
         if (rgSCHUtlGetPhichInfo (ulAlloc->hqProc, &rbStart, &nDmrs, &iPhich) != ROK)
#else
            if (rgSCHUtlGetPhichInfo (ulAlloc->hqProc, &rbStart, &nDmrs) != ROK)
#endif
            {
               RETVALUE (RFAILED);
            }
         if(nDmrs != RGSCH_INVALID_NDMRS)
         {
            if(cellCb->dynCfiCb.switchOvrInProgress)
            {
               ulAlloc->hqProc->rcvdCrcInd = TRUE;
            }    

            if(ulAlloc->hqProc->rcvdCrcInd) 
            {
#ifdef LTE_TDD
               rgSCHUtlAddPhich (cellCb, frm, TRUE, nDmrs, rbStart, iPhich);
#else
               rgSCHUtlAddPhich (cellCb, frm, TRUE, nDmrs, rbStart, ulAlloc->forMsg3);
#endif
            }
            /* Sending NACK in PHICH for failed UL TX */
            else
            {
#ifdef LTE_TDD
               rgSCHUtlAddPhich (cellCb, frm, FALSE, nDmrs, rbStart, iPhich);
#else
#ifdef LTEMAC_HDFDD
               if (ulAlloc->ue != NULLP && ulAlloc->ue->hdFddEnbld)
               {
                  rgSCHCmnHdFddChkNackAllow( cellCb, ulAlloc->ue, frm, &allwNack);
                  /* Present implementaion of non-HDFDD does not send phich req
                     incase of NACK. So commented this part to maintain same right
                     now.*/

                  if (allwNack)
                  {
                     rgSCHUtlAddPhich (cellCb, frm, FALSE, nDmrs, rbStart, ulAlloc->forMsg3);
                  }
                  else
                  {
                     rgSCHUtlAddPhich (cellCb, frm, TRUE, nDmrs, rbStart, ulAlloc->forMsg3);
                  }
               }
               else
               {
                  rgSCHUtlAddPhich (cellCb, frm, FALSE, nDmrs, rbStart, ulAlloc->forMsg3);
               }
#else
               rgSCHUtlAddPhich (cellCb, frm, FALSE, nDmrs, rbStart, ulAlloc->forMsg3);
#endif/* LTEMAC_HDFDD */
#endif
            }
         }
         ulAlloc = rgSCHUtlNextHqFdbkAlloc (cellCb, ulAlloc, idx);
      }
   }
   RETVALUE(ROK);
} /* rgSCHUhmAppendPhich */

/**
 * @brief This function initializes the DL HARQ Entity of UE.
 *
 * @details
 *
 *     Function: rgSCHUhmHqEntInit
 *     Purpose:  This function initializes the UL HARQ Processes of 
 *               UE control block. This is performed at the time
 *               of creating UE control block.
 *     
 *     Invoked by: configuration module
 *     
 *  @param[in]  RgSchUeCb*    ueCb
 *  @return  S16
 *           -# ROK
 *           -# RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 rgSCHUhmHqEntInit
(
RgSchCellCb       *cellCb,
RgSchUeCb           *ueCb
)
#else
PUBLIC S16 rgSCHUhmHqEntInit(cellCb, ueCb)
RgSchCellCb       *cellCb;
RgSchUeCb           *ueCb;
#endif
{
   RgSchCmnUlUe *ueUl = RG_SCH_CMN_GET_UL_UE(ueCb, cellCb);
#ifdef LTE_TDD   
   Inst              inst = ueCb->cell->instIdx;
#endif
   TRC2(rgSCHUhmHqEntInit)

#ifndef LTE_TDD
   /* Init the HARQ processes */
   ueUl->hqEnt.numHqPrcs = RGSCH_NUM_UL_HQ_PROC;
#else
   /* Init the HARQ processes */
   ueUl->hqEnt.numHqPrcs = 
                        rgSchTddUlNumHarqProcTbl[ueCb->cell->ulDlCfgIdx];
   if (rgSCHUtlAllocSBuf(inst, (Data **)&ueUl->hqEnt.hqProcCb, 
                           ueUl->hqEnt.numHqPrcs * \
                           sizeof(RgSchUlHqProcCb)) != ROK)
   {
      RETVALUE(RFAILED);
   }
#endif

   RETVALUE(ROK);
} /* rgSCHUhmHqEntInit */



/**********************************************************************
 
         End of file:     gk_sch_uhm.c@@/main/2 - Sat Jul 30 02:21:52 2011
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     sd    1. LTE MAC 2.1 release
           rg003.201 ns    1. Trace added to functions.
           rg005.201 sm    1. Renamed rcvdDatInd to rcvdCrcInd
           rg006.201 ms    1. ccpu00111742: Sending NACK in PHICH for failed UL TX
           rg008.201 rsharon    2. Added support for SPS.
           rg009.201 dv   1. Added changes of TFU_UPGRADE.
                          2. ccpu00116309:Changes for storing and passing iPhich at TFU
                          interface.
/main/2      ---        gvj  1. Updated for LTE MAC Rel 3.1           
$SID$        ---     rt      1. LTE MAC 4.1 release
*********************************************************************91*/
