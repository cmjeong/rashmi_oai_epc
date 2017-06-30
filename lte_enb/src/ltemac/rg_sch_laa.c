

/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#include "cm_hash.h"       /* common hash list */
#include "cm_llist.h"      /* common linked list library */
#include "cm_math.h"      /* common math library */
#include "cm_err.h"        /* common error */
#include "cm_lte.h"        /* common LTE */
#include "cm_math.h"       /* common MATH */
#include "lrg.h"
#include "rgr.h"
#include "rgm.h"
#include "tfu.h"
#include "rg_env.h"
#include "rg_sch_inf.h"
#include "rg_sch_err.h"
#include "rg_sch.h"
#include "rg_sch_cmn.h"
#include "rl_interface.h"
#include "rl_common.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_math.x"       /* common math library */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"        /* common tokens */
#include "cm_math.x"       /* common MATH */
#include "tfu.x"           /* RGU types */
#include "lrg.x"           /* layer management typedefs for MAC */
#include "rgr.x"           /* layer management typedefs for MAC */
#include "rgm.x"           /* layer management typedefs for MAC */
#include "rg_sch_inf.x"    /* typedefs for Scheduler */
#include "rg_sch.x"        /* typedefs for Scheduler */
#include "rg_sch_cmn.x"

#ifdef LTE_ADV
static const char* RLOG_MODULE_NAME="MAC";
static int RLOG_MODULE_ID=4096;
static int RLOG_FILE_ID=174;

#ifdef ANSI
PRIVATE Void rgSchLaaPutLaaTBNode
(
RgSchCellCb *cell,
RgSchLaaTBInfo *laaTBInfo
)
#else
PRIVATE Void rgSchLaaPutLaaTBNode(cell, laaTBInfo)
RgSchCellCb *cell;
RgSchLaaTBInfo *laaTBInfo;
#endif
{
   Inst                 inst = cell->instIdx;

   laaTBInfo->procId = 0xff;
   laaTBInfo->laaSCell = NULLP;
   laaTBInfo->numTBs = 0;
   laaTBInfo->hqPStamp = 0; 
   laaTBInfo->ue = NULLP;
   laaTBInfo->tbSz[0]  = 0;
   laaTBInfo->tbSz[1]  = 0;

   laaTBInfo->laaTbsLnk.node = (PTR)laaTBInfo;
   cmLListAdd2Tail(&rgSchCb[inst].laaMovedTBNodeLst, &(laaTBInfo->laaTbsLnk));
}
#ifdef ANSI
PRIVATE S16 rgSchLaaGetLaaTBNode
(
RgSchCellCb *cell,
RgSchLaaTBInfo **laaTBInfo
)
#else
PRIVATE S16 rgSchLaaGetLaaTBNode(cell, laaTBInfo)
RgSchCellCb *cell;
RgSchLaaTBInfo **laaTBInfo;
#endif
{
   Inst                 inst = cell->instIdx;
   S16 ret = ROK;

   if (rgSchCb[inst].laaMovedTBNodeLst.first != NULLP)
   {
      *laaTBInfo = (RgSchLaaTBInfo *)(rgSchCb[inst].laaMovedTBNodeLst.first->node);
      cmLListDelFrm(&rgSchCb[inst].laaMovedTBNodeLst, rgSchCb[inst].laaMovedTBNodeLst.first);
   }
   else
   {
      ret = rgSCHUtlAllocSBuf(inst, (Data **)laaTBInfo, sizeof(RgSchLaaTBInfo));
      if(ROK != ret)
      {
         RETVALUE(RFAILED);
      }
   }
   RETVALUE(ROK);
}


/**
 * @brief Handler for handling release of sps hq proc
 *
 * @details
 *
 *     Function : rgSCHCmnSpsRelHqProc
 *
 *
 *  @param[in]  RgSchCellCb              *cell
 *  @param[in]  RgSchDlHqProcCb          *hqP
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHLaaAddToRelHqProc
(
RgSchCellCb           *cell,
RgSchDlHqProcCb       *hqP,
U16                   hqStamp,
RgInfRlsHqInfo        *rlsHqBufs
)
#else /* ANSI */
PRIVATE Void rgSCHLaaAddToRelHqProc(cell, hqP, hqStamp, rlsHqBufs)
RgSchCellCb           *cell;
RgSchDlHqProcCb       *hqP;
U16                   hqStamp;
RgInfRlsHqInfo        *rlsHqBufs;
#endif /* ANSI */
{
   RgSchUeCb            *ue = hqP->hqE->ue;
   U8 idx =  rlsHqBufs->numUes;
   TRC2(rgSCHLaaAddToRelHqProc);

   hqP->tbInfo[0].cntrRetxAllocFail = RG_SCH_MAX_RETX_ALLOC_FAIL;
   rlsHqBufs->ueHqInfo[idx].numOfTBs = 1;
   rlsHqBufs->ueHqInfo[idx].status[0] = TRUE;
   rlsHqBufs->ueHqInfo[idx].tbId[0] = 1;
   rgSCHDhmRlsHqpTb(hqP, 0, TRUE);
   if (hqP->tbInfo[1].txCntr)
   {
      rlsHqBufs->ueHqInfo[idx].numOfTBs++;
      rlsHqBufs->ueHqInfo[idx].status[1] = TRUE;
      rlsHqBufs->ueHqInfo[idx].tbId[1] = 2;
      hqP->tbInfo[1].cntrRetxAllocFail = RG_SCH_MAX_RETX_ALLOC_FAIL;
      rgSCHDhmRlsHqpTb(hqP, 1, TRUE);
   }

   /* Fill Release harq sent to MAC to free SPS Hq procs */
   rlsHqBufs->ueHqInfo[idx].rnti = ue->ueId;
   rlsHqBufs->ueHqInfo[idx].hqProcId = hqP->procId;
   rlsHqBufs->ueHqInfo[idx].rlsOperationType = RGINF_RLS_HQ_SAVE_TB;
   rlsHqBufs->ueHqInfo[idx].saveId = hqStamp;
   rlsHqBufs->numUes++;


   RETVOID;
}

/**
 * @brief Handler for preparing the info for moved LAA TB and adding it to
 * PCell
 *
 * @details
 *
 *     Function: rgSCHLaaMovToPcell 
 *
 *     Handler for preparing the info for moved LAA TB and adding it to Pcell 
 *
 *     Invoked by: RgLiTfuErrInd
 *
 *     Processing Steps:
 *           
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PRIVATE Void rgSCHLaaMovToPcell
(
RgSchCellCb     *cell,
RgSchUeCb       *ue,
RgSchDlHqProcCb *hqP,
RgInfRlsHqInfo *rlsHqBufs
)
#else
PRIVATE Void rgSCHLaaMovToPcell(cell, ue, hqP)
RgSchCellCb     *cell;
RgSchUeCb       *ue;
RgSchDlHqProcCb *hqP;
#endif
{
   RgSchLaaTBInfo *laaTBInfo=NULLP;
   U8 idx=0;
   CmLteTimingInfo tmpInfo;

   rgSchLaaGetLaaTBNode(cell, &laaTBInfo);

   if(laaTBInfo == NULLP)
   {
      RETVOID;
   }
   laaTBInfo->procId = hqP->procId;
   laaTBInfo->laaSCell = cell;
   laaTBInfo->numTBs = 0;
   tmpInfo = hqP->tbInfo[0].timingInfo;
   laaTBInfo->hqPStamp = (tmpInfo.sfn * 10) + tmpInfo.subframe;
   laaTBInfo->ue = ue;

   for (idx = 0 ;idx < 2; idx++)
   {
      if(hqP->tbInfo[idx].state != HQ_TB_ACKED)
      {
         laaTBInfo->tbSz[idx] =  hqP->tbInfo[idx].tbSz;
         laaTBInfo->numTBs++;
      }
   }
/*Add the info into the PCell List*/
   laaTBInfo->laaTbsLnk.node = (PTR)laaTBInfo;
   cmLListAdd2Tail(&ue->cell->laaCellCb.laaTbsToBeSchedLst,
         &(laaTBInfo->laaTbsLnk));
   /*Save the TB at SMAC*/
   rgSCHLaaAddToRelHqProc(cell, hqP, laaTBInfo->hqPStamp, rlsHqBufs);
   RETVOID;

}

#ifdef ANSI
PRIVATE S16 rgSCHLaaAddToHqPToShiftQ 
(
RgSchCellCb    *cell,
RgSchDlHqProcCb *hqP
)
#else
PRIVATE S16 rgSCHLaaAddToHqPToShiftQ(cell, hqP)
RgSchCellCb    *cell;
RgSchDlHqProcCb *hqP;
#endif
{
   U32 insrtIdx;
   U32 crntTimeIdx;
   RgSchLaaCellCb *pSchLaaCell = (RgSchLaaCellCb*) (&cell->laaCellCb);

   if (hqP->laaHqP.hqPToShiftLnk.node)
   {
      RETVALUE(ROK);
   }

   /* Based on different criteria we decide insrtIdx 
      For now we are taking some default time
      RG_SCH_DEFAULT_HQP_SHIFT_TIME*/

   crntTimeIdx = (cell->crntTime.sfn * RG_MAX_NUM_DLSF + 
         cell->crntTime.subframe);
   insrtIdx = crntTimeIdx + RG_SCH_DEFAULT_HQP_SHIFT_TIME;
   
   hqP->laaHqP.overflowCycles = (insrtIdx - crntTimeIdx) / RG_SCH_MAX_HQP_SHIFT_Q_SZ;
   hqP->laaHqP.hqPToShiftLnk.node = (PTR)hqP;

   insrtIdx %= RG_SCH_MAX_HQP_SHIFT_Q_SZ;
   hqP->laaHqP.hqPToShiftIdx = insrtIdx;
   cmLListAdd2Tail(&pSchLaaCell->hqPToShiftChkQ[insrtIdx], &(hqP->laaHqP.hqPToShiftLnk));
   RETVALUE(ROK);
}
/**
 * @brief Handler for processing harq ACK/NACK indication recieved from PHY.
 *
 * @details
 *
 *     Function: rgSCHLaaErrInd
 *
 *     Handler for processing Error indication recieved from PHY.
 *
 *     Invoked by: RgLiTfuErrInd
 *
 *     Processing Steps:
 *           
 *  @param[in]  TfuErrIndInfo *errInd
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgSCHLaaErrInd
(
RgSchCellCb     *cell,
TfuErrIndInfo    *errInd
)
#else
PUBLIC S16 rgSCHLaaErrInd(cell, err)
RgSchCellCb     *cell; 
TfuErrIndInfo    *errInd;
#endif
{
   RgSchDlSf         *sf;
   RgSchUeCb         *ue;
   RgSchDlHqProcCb   *hqP;
   CmLList           *node;
   CmLList           *tempNode;
   CmLList           *hqNode;
   /*
   Pst             pst;
   RgInfRlsHqInfo  *rlsHqBufs = &(cell->rlsHqArr[cell->crntHqIdx]); 
   */
   
   TRC2(rgSCHLaaErrInd);

   if(cell->cellId != errInd->cellId)
   {
      RLOG_ARG1(L_ERROR,DBG_CELLID,cell->cellId,"rgSCHLaaErrInd() Unable to get"
         " the cell for cellId (%d)", errInd->cellId);
      RETVALUE(RFAILED);
   }
   
   sf = rgSCHUtlSubFrmGet(cell, errInd->timingInfo);

   node =  sf->laaSCellUeLst.first;
                  
   CM_LLIST_FIRST_NODE(&sf->laaSCellUeLst, node);
   tempNode = node;
                  
   while(NULLP != node)
   {
      ue = (RgSchUeCb *)node->node;
      CM_LLIST_NEXT_NODE(&sf->laaSCellUeLst, tempNode);
      hqNode = ue->dl.dlSfHqInfo[sf->dlIdx].hqPLst.first;
      for (;hqNode; hqNode=hqNode->next)
      {
         hqP = (RgSchDlHqProcCb*)hqNode->node;
         if(hqP->hqE->cell == cell)
         {
            /*
            if(TRUE == rgSCHLaaCheckMovToPcell())
            {
               rgSCHLaaMovToPcell(cell, ue, hqP, rlsHqBufs);
               continue;
            }
            */
            /*Add the Harq Proc to the Err Ind List*/
            hqP->laaHqP.errIndHqpLnk.node = (PTR)hqP;
            cmLListAdd2Tail(&cell->laaCellCb.errIndHqpLst, &(hqP->laaHqP.errIndHqpLnk));

            /* Add the HqP to hqPToShiftChkQ to check 
               handle the movement of HqP from SCELL 
               to PCELL */
            rgSCHLaaAddToHqPToShiftQ(cell, hqP);


            /*Remove from  subframe PDCCH List in which queued earlier*/
            rgSCHUtlPdcchPut(cell, &sf->pdcchInfo, hqP->pdcch);

            /*Remove from subframe List in which queued earlier*/
            rgSCHUtlDlHqPTbRmvFrmTx(sf, hqP, 0, FALSE);
         }
      }
      node = tempNode;
   }
   /*
   if(rlsHqBufs->numUes)
   {
      rgSCHUtlGetPstToLyr(&pst, &rgSchCb[cell->instIdx], cell->macInst);
      RgSchMacRlsHq (&pst, rlsHqBufs);
   }
   */
   RETVALUE(ROK);
}  /* rgSCHLaaErrInd */

/**
 * @brief Handler for LAA Cell Initialisation 
 *
 * @details
 *
 *     Function : rgSCHLaaRgrCellCfg
 *     
 *     This function will allocate and initialise the LAA Cell control block. 
 *           
 *  @param[in]  RgSchCellCb     *cell 
 *  @param[in]  RgrCellCfg   *cellCfg
 *  @param[out] RgSchErrInfo    *err 
 *
 *  @return     S16
 *                -# ROK 
 *                -# RFAILED 
 **/
#if 0
#ifdef ANSI
PUBLIC Void rgSCHLaaRgrCellCfg
(
RgSchCellCb    *cell,
RgrCellCfg     *cellCfg,
RgSchErrInfo   *err
)
#else
PUBLIC Void rgSCHLaaRgrCellCfg(cell, cellCfg, err)
RgSchCellCb    *cell;
RgrCellCfg     *cellCfg;
RgSchErrInfo   *err;
#endif
{
   TRC2(rgSCHLaaRgrCellCfg);

#if 0
   if (((ret = rgSCHUtlAllocSBuf(cell->instIdx,
                  (Data**)&(cell->laaCell), (sizeof(RgSchLaaCell))))
            != ROK))
   {
      RLOG_ARG0(L_ERROR,DBG_CELLID,cell->cellId,
            "Memory allocation FAILED");
      err->errCause = RGSCHERR_SCH_CFG;
      RETVALUE(ret);
   }
#endif
   cmLListInit(&cell->laaCell.errIndHqpLst);
/*laaTbsToBeSchedLst will not be used if if the Cell is an LAA SCell as it
 * cannot be a PCell*/
   cmLListInit(&cell->laaCell.laaTbsToBeSchedLst);
}
#endif

/**
 * @brief Handler for filling LAA TB info and checking the Rank in the PCell 
 *
 * @details
 *
 *     Function : rgSchLaaCheckTBTrans
 *     
 *     This function will fill the TB info in the UEs temporary storage based
 *     on the Rank number of Tbs moved from SCell and the rank in the PCell. 
 *           
 *  @param[in]  RgSchCellCb     *cell 
 *
 *  @return     S16
 *                -# ROK 
 *                -# RFAILED 
 **/
#ifdef ANSI
PRIVATE Void rgSchLaaFillTBInfo
(
RgSchCellCb    *cell,
RgSchUeCb    *ue,
RgSchLaaTBInfo *laaTBInfo,
U32 *bo,
U8 *tbId
)
#else
PRIVATE Void rgSchLaaFillTBInfo(cell, ue, laaTBInfo, bo)
RgSchCellCb    *cell;
RgSchUeCb    *ue;
RgSchLaaTBInfo *laaTBInfo;
U32 *bo;
U8 *tbId;
#endif
{
   RgSchCmnDlUe  *ueDl = RG_SCH_CMN_GET_DL_UE(ue,cell);
   RgSchDlRbAlloc   *allocInfo = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue,cell);

   TRC2(rgSchLaaFillTBInfo);

   allocInfo->laaDlRbAlloc.isLaaTB = TRUE;
   allocInfo->laaDlRbAlloc.laaTBInfo = laaTBInfo;

#if 0
   TBSize is different, then drop;
   return FALSE;
#endif

#if 0
   1. RI 1, TBs 1
      no change
      2. RI 1, TBs 2
      Take one TB
      3. RI > 1, TBs 1
      forceTD
      4. RI > 1, TBs 2
      no change
#endif


      if((ueDl->mimoInfo.ri == 1) && (laaTBInfo->numTBs == 1)) 
      {
         /*Here we bo is sum of 2 TBs as one of the TB size will be 0. The
          * valid TB can be either 1st or 2nd based on the harq feedback
          * received in the secondary cell*/
         *bo = laaTBInfo->tbSz[0] + laaTBInfo->tbSz[1];
         if(laaTBInfo->tbSz[0])
         {
            *tbId = 1;
         }
         else
         {
            *tbId = 2;
         }
      }
      else if ((ueDl->mimoInfo.ri > 1)&&(
                  laaTBInfo->numTBs == 2))
      {
         *bo = laaTBInfo->tbSz[0] + laaTBInfo->tbSz[1];
         *tbId = 0;

      } 
      else if((ueDl->mimoInfo.ri > 1) && (laaTBInfo->numTBs == 1))
      {
         RG_SCH_CMN_SET_FORCE_TD(ue, cell, RG_SCH_CMN_TD_LAA_SINGLE_TB);
         /*Here we bo is sum of 2 TBs as one of the TB size will be 0. The
          * valid TB can be either 1st or 2nd based on the harq feedback
          * received in the secondary cell*/
         *bo = laaTBInfo->tbSz[0] + laaTBInfo->tbSz[1];
         if(laaTBInfo->tbSz[0])
         {
            *tbId = 1;
         }
         else
         {
            *tbId = 2;
         }

      }
      else if ((ueDl->mimoInfo.ri == 1) && (laaTBInfo->numTBs == 2))
      {
         *bo = laaTBInfo->tbSz[laaTBInfo->numTBs - 1];
         *tbId = 2;
      }

   RETVOID;

}

/**
 * @brief Handler for handling release of sps hq proc
 *
 * @details
 *
 *     Function : rgSCHLaaRlsHqFrmPCell
 *
 *
 *  @param[in]  RgSchCellCb              *cell
 *  @param[in]  RgSchDlHqProcCb          *hqP
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHLaaRlsHqFrmPCell 
(
RgSchUeCb             *ue,
RgSchLaaTBInfo        *laaTbInfo

)
#else /* ANSI */
PRIVATE Void rgSCHLaaRlsHqFrmPCell(ue, laaTbInfo)
RgSchUeCb             *ue;
RgSchLaaTBInfo        *laaTbInfo;
#endif /* ANSI */
{
   RgSchCellCb           *cell = laaTbInfo->laaSCell;
   Pst             pst;
   RgInfRlsHqInfo  *rlsHqBufs = &(cell->rlsHqArr[cell->crntHqIdx]); 
   TRC2(rgSCHCmnSpsRelHqProc);


   rlsHqBufs->ueHqInfo[0].numOfTBs = laaTbInfo->numTBs;
   /* Fill Release harq sent to MAC to free SPS Hq procs */
   rlsHqBufs->ueHqInfo[0].status[0] = TRUE;
   rlsHqBufs->ueHqInfo[0].tbId[0] = 1;
   if(laaTbInfo->numTBs > 1)
   {
      rlsHqBufs->ueHqInfo[0].tbId[0] = 2;
      rlsHqBufs->ueHqInfo[0].status[1] = TRUE;
   }
   rlsHqBufs->ueHqInfo[0].rnti = ue->ueId;
   rlsHqBufs->ueHqInfo[0].hqProcId = laaTbInfo->procId;
   rlsHqBufs->ueHqInfo[0].rlsOperationType = RGINF_RLS_HQ_DEL_TB;
   rlsHqBufs->ueHqInfo[0].saveId = laaTbInfo->hqPStamp;
   rlsHqBufs->numUes = 1;

   rgSCHUtlGetPstToLyr(&pst, &rgSchCb[cell->instIdx], cell->macInst);
   RgSchMacRlsHq (&pst, rlsHqBufs);

   RETVOID;
}
/**
 * @brief Handler for processing TBs moved from LAA SCell to corresponding
 * PCell 
 *
 * @details
 *
 *     Function : rgSCHLaaSchTbMovdToPCell
 *     
 *     This function will  process TBs moved from LAA SCell to
 *     corresponding PCell
 *           
 *  @param[in]  RgSchCellCb     *cell 
 *
 *  @return     S16
 *                -# ROK 
 *                -# RFAILED 
 **/
#ifdef ANSI
PRIVATE Void rgSCHLaaSchTbMovdToPCell
(
RgSchCellCb    *cell
)
#else
PRIVATE Void rgSCHLaaSchTbMovdToPCell(cell)
RgSchCellCb    *cell;
#endif
{
   CmLList           *node;
   RgSchCmnCell *cellSch = RG_SCH_CMN_GET_CELL(cell);
   RgSchCmnCell *schCmnCell = (RgSchCmnCell *)(cell->sc.sch);
   RgSchUeCb         *ue;
   RgSchLaaTBInfo    *laaTbInfo;
   U32 macBo=0;
   U32 allocBo=0;
   RgSchCmnDlRbAllocInfo   *allocInfo = &(cellSch->allocInfo);
   RgSchDlSf    *dlSf = allocInfo->dedAlloc.dedDlSf;
   RgSchCmnUe   *schCmnUe;
   RgSchCmnDlHqProc *cmnHqDl;
   U8 tbId=0;
#ifdef LTEMAC_SPS
   CmLteTimingInfo schdTime;
#endif

   TRC2(rgSCHLaaSchTbMovdToPCell);
#ifdef LTEMAC_SPS
   schdTime = cell->crntTime;
   /* Increment by DL DELTA to determine the time for which scheduling
    * is done */
   RGSCH_INCR_SUB_FRAME(schdTime, RG_SCH_CMN_DL_DELTA);
#endif


   node = cell->laaCellCb.laaTbsToBeSchedLst.first;
   while(node)
   {
         laaTbInfo  = (RgSchLaaTBInfo *)(node->node);
         ue  = laaTbInfo->ue; 
         node = node->next;
         rgSchLaaFillTBInfo(cell, ue, laaTbInfo, &macBo, &tbId);

      if((ue->dl.dlInactvMask)
#ifdef LTEMAC_SPS
            ||(RG_SCH_CMN_IS_UE_SPS_SCHDLD(ue, cell, schdTime))
#endif
        )
      {
         continue;
      }
      schCmnUe = RG_SCH_CMN_GET_UE(ue, cell); 

      if(schCmnUe->dl.proc != NULLP)
      {
         continue;
      }

      if(rgSCHDhmGetAvlHqProc(cell, ue,
               schCmnCell->dl.time, &(schCmnUe->dl.proc)) != ROK)
      {
         continue;
      }

      schCmnUe->dl.proc->laaHqP.procId = laaTbInfo->procId;
      schCmnUe->dl.proc->laaHqP.sCellMacInstId = laaTbInfo->laaSCell->macInst;
      schCmnUe->dl.proc->laaHqP.tbId = tbId;



      cmnHqDl = RG_SCH_CMN_GET_DL_HQP(schCmnUe->dl.proc);
      cmnHqDl->totBytes = 0;
      if(rgSCHCmnDlAllocTxRb(cell, dlSf, ue,
               macBo, &allocBo, schCmnUe->dl.proc,\
               allocInfo) != ROK)
      {
         rgSCHDhmRlsHqProc(schCmnUe->dl.proc);
         schCmnUe->dl.proc = NULLP;
         rgSCHLaaRlsHqFrmPCell(ue, laaTbInfo);
         /*Remove from List and Put back the node*/
         cmLListDelFrm(&cell->laaCellCb.laaTbsToBeSchedLst, &(laaTbInfo->laaTbsLnk));
         rgSchLaaPutLaaTBNode(cell, laaTbInfo);
         RETVOID;
      }

      if(allocBo)
      {
         /* Added the handling for updating the totBtyes.*/
         cmnHqDl->totBytes += allocBo;

         (dlSf->remUeCnt)--;
      }      /* Add to UeLst is moved to common Scheduler */
      else
      {
         rgSCHDhmRlsHqProc(schCmnUe->dl.proc);
         schCmnUe->dl.proc = NULLP;
         rgSCHLaaRlsHqFrmPCell(ue, laaTbInfo);
         /*Remove from List and Put back the node*/
         cmLListDelFrm(&cell->laaCellCb.laaTbsToBeSchedLst, &(laaTbInfo->laaTbsLnk));
         rgSchLaaPutLaaTBNode(cell, laaTbInfo);
         continue;
      }
   }
}


/**
 * @brief This function removes a HARQ process from the retx
 *
 * @details
 *
 *     Function: rgSCHRrDlProcRmvFrmRetx
 *     Purpose:  This function removes a HARQ process from retransmission
 *               queue. This may be performed when a HARQ ack is successful
 *               for a retransmission or during UE reset
 *
 *  @param[in]  RgSchCellCb      *cell
 *  @param[in]  RgSchDlHqProcCb  *hqP
 *  @return  Void
 *
 **/
#ifdef ANSI
PRIVATE Void rgSCHLAADlProcRmvFrmErrIndLst
(
RgSchCellCb                *cell,
RgSchDlHqProcCb            *hqP 
)
#else
PRIVATE Void rgSCHLAADlProcRmvFrmErrIndLst(cell, hqP) 
RgSchCellCb                *cell;
RgSchDlHqProcCb            *hqP;
#endif
{
   TRC2(rgSCHLAADlProcRmvFrmErrIndLst);

   if(hqP->laaHqP.errIndHqpLnk.node != NULLP)
   {
      cmLListDelFrm(&cell->laaCellCb.errIndHqpLst, &(hqP->laaHqP.errIndHqpLnk));
   }

   RETVOID;
}

/**
 * @brief Handler for deciding which HqP shall be shifted
 * to PCELL for scheduling
 * @details
 *
 *     Function : rgSCHLaaCheckForShifting
 *     
 *     This function shall consider various criteria to
 *     decide if the HqP should be shifted to PCELL for       
 *     reliable scheduling
 *  @param[in]  RgSchCellCb     *cell 
 *
 *  @return     S16
 *                -# ROK 
 *                -# RFAILED 
 **/
#ifdef ANSI
PRIVATE Void rgSCHLaaCheckForShifting
(
RgSchCellCb            *cell
)
#else
PRIVATE Void rgSCHLaaCheckForShifting(cell)
RgSchCellCb            *cell;
#endif
{
   RgSchLaaCellCb *pSchLaaCell = (RgSchLaaCellCb*) (&cell->laaCellCb);
   U32            toChkIdx;
   Pst             pst;
   RgInfRlsHqInfo  *rlsHqBufs = &(cell->rlsHqArr[cell->crntHqIdx]); 
   CmLList         *node;
   RgSchDlHqProcCb  *hqP;

   TRC2(rgSCHLaaCheckForShifting);

   toChkIdx = (cell->crntTime.sfn * RG_MAX_NUM_DLSF + 
         cell->crntTime.subframe)% RG_SCH_MAX_HQP_SHIFT_Q_SZ;

   /* loop till the crnt node */
   node = pSchLaaCell->hqPToShiftChkQ[toChkIdx].crnt;
   while(node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      node = node->next;
      
      if (hqP->laaHqP.overflowCycles)
      {
         hqP->laaHqP.overflowCycles--;
         continue;
      }

      cmLListDelFrm(&pSchLaaCell->hqPToShiftChkQ[toChkIdx], &(hqP->laaHqP.hqPToShiftLnk));
      hqP->laaHqP.hqPToShiftLnk.node = NULLP;

      rgSCHLAADlProcRmvFrmErrIndLst (cell, hqP);
      rgSCHLaaMovToPcell(cell, hqP->hqE->ue, hqP, rlsHqBufs);
   }

   if(rlsHqBufs->numUes)
   {
      rgSCHUtlGetPstToLyr(&pst, &rgSchCb[cell->instIdx], cell->macInst);
      RgSchMacRlsHq (&pst, rlsHqBufs);
   }
   RETVOID;
}

/**
 * @brief Handler for LAA Error Ind List scheduling 
 *
 * @details
 *
 *     Function : rgSCHLaaSchErrIndLst
 *     
 *     This function will schedule the Error Ind List 
 *           
 *  @param[in]  RgSchCellCb     *cell 
 *
 *  @return     S16
 *                -# ROK 
 *                -# RFAILED 
 **/
#ifdef ANSI
PRIVATE Void rgSCHLaaSchErrIndLst
(
 RgSchCellCb            *cell
 )
#else
PRIVATE Void rgSCHLaaSchErrIndLst(cell)
   RgSchCellCb            *cell;
#endif
{
   RgSchLaaCellCb *pSchLaaCell = (RgSchLaaCellCb*) (&cell->laaCellCb);
   RgSchUeCb    *ue;
   RgSchCmnUe   *schCmnUe;
   RgSchDlHqProcCb *hqP;
   U32 allocBo;
   CmLList *node;
   RgSchCmnCell *cellSch = RG_SCH_CMN_GET_CELL(cell);
   RgSchCmnDlRbAllocInfo   *allocInfo = &(cellSch->allocInfo);
   U32 remUe = allocInfo->dedAlloc.dedDlSf->remUeCnt;
#ifdef LTEMAC_HDFDD
   Bool                 dlAllowed = FALSE;
#endif
#ifdef LTE_ADV
   U8  tpcIdx = 0;
   RgSchDlSf         *dlSf = allocInfo->dedAlloc.dedDlSf;
#endif

   TRC2(rgSCHLaaSchErrIndLst);

   if(FALSE == cell->rgSchLAACellCfg.isLaaCell)
   {
      RETVOID;
   }

   /*TODO:REEMA:Define this function
    - If not LAA SCELL return;
    - Scan the errIndHqpLst
    - Check if UE inactive or already picked with a different 
    hqP in this subframe, if yes continue.
    - Add Hqp into allocInfo->dedAlloc.laaTxHqPLst 
    - hqp->laaHqp.errIndFlg to indicate  this is a err ind TB and
    not need to go to RLC for this. This flag needs to be reset at the
    appropriate place. 
    - Decrement the remaining UE count for the subframe.
    - Decrement the cell wide bandwidth.
    - Set schCmnUe->dl.proc to hqP;
    - Fill the  "RgSchDlRbAlloc   *allocInfo" for the UE.
    :*/


   if((NULLP == pSchLaaCell->errIndHqpLst.crnt) || !remUe)
   {
      RETVOID;
   }

   /* loop till the crnt node */
   node = pSchLaaCell->errIndHqpLst.crnt;
   do
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      ue = hqP->hqE->ue;
      schCmnUe = RG_SCH_CMN_GET_UE(ue, cell); 
      node = node->next;

      if(ue->dl.dlInactvMask)
      {
         continue;
      }

      if(schCmnUe->dl.proc != NULLP)
      {
         /*UE is already selected for re-tx*/
         continue;
      }

      if(RG_SCH_IS_CELL_SEC(ue,cell))
      {
	      if(ROK != rgSCHSCellIsActive(cell,ue))
	      {/* Skipping retx if deactivation was triggered */
            continue;
	      }

	      if(ROK != rgSchGetAvlTpcIdx(ue, &tpcIdx, dlSf,cell))
	      {
		      continue;
	      }
	      hqP->tpc = tpcIdx;
      }

      if(rgSCHCmnDlAllocErrIndTxRb(cell, allocInfo->dedAlloc.dedDlSf,
               ue, 0, &allocBo, hqP, allocInfo) != ROK)
      {
         pSchLaaCell->errIndHqpLst.crnt = node->prev;
         rgSchFreeTpcIdxForSCell(ue, hqP, allocInfo->dedAlloc.dedDlSf);
         break;
      }

      if(allocBo == 0)
      {
         rgSchFreeTpcIdxForSCell(ue, hqP, allocInfo->dedAlloc.dedDlSf);
         continue;
      }
      schCmnUe->dl.proc = hqP;
      /* Adding Ue into Retx list is moved to cmn Scheduler */
      --remUe;
   
   }while(node);

   allocInfo->dedAlloc.dedDlSf->remUeCnt = remUe;
   RETVOID;
}

/**
 * @brief Handler for processing LAA functions 
 *
 * @details
 *
 *     Function: rgSCHLaaSch
 *
 *     Handler for processing LAA functions 
 *
 *     Invoked by: rgSCHTomTtiInd 
 *
 *     Processing Steps:
 *           
 *  @param[in]  RgSchCellCb     *cell 
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC Void rgSCHLaaSch
(
RgSchCellCb     *cell
)
#else
PUBLIC Void rgSCHLaaSch(cell)
RgSchCellCb     *cell; 
#endif
{
   if(cell->rgSchLAACellCfg.isLaaCell)
   {
      rgSCHLaaCheckForShifting(cell);
      rgSCHLaaSchErrIndLst(cell);
   }
   else
   {
      rgSCHLaaSchTbMovdToPCell(cell);
   }
}

/**
 * @brief Dl LAA allocations finalizations on PCell for the UEs.
*
 * @details
 *
 *     Function : rgSCHLaaCheckRmvFrmLaaTBLst
 *
 *     Processing Steps:
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo  *allocInfo
 *  @return  Void
 **/
#ifdef ANSI
PRIVATE Void rgSCHLaaCheckRmvFrmLaaTBLst
(
RgSchCellCb     *cell,
RgSchUeCb       *ue,
RgSchDlRbAlloc  *dlRbAlloc
)
#else
PRIVATE Void rgSCHLaaCheckRmvFrmLaaTBLst(cell, ue, allocInfo)
RgSchCellCb     *cell;
RgSchUeCb       *ue;
RgSchDlRbAlloc  *dlRbAlloc;
#endif
{
   RgSchLaaTBInfo    *laaTbInfo;

   TRC2(rgSCHLaaCheckRmvFrmLaaTBLst);

   RG_SCH_CMN_UNSET_FORCE_TD(ue, cell, RG_SCH_CMN_TD_LAA_SINGLE_TB);
   laaTbInfo = dlRbAlloc->laaDlRbAlloc.laaTBInfo;
   if((laaTbInfo->numTBs == 1) || ((laaTbInfo->numTBs == 2) &&
            (dlRbAlloc->tbInfo[1].schdlngForTb) == TRUE))
   {
      /*Remove from List and Put back the node*/
      cmLListDelFrm(&cell->laaCellCb.laaTbsToBeSchedLst, &(laaTbInfo->laaTbsLnk));

      rgSchLaaPutLaaTBNode(cell, laaTbInfo);
   }
   else 
   if(((laaTbInfo->numTBs == 2) &&
            (dlRbAlloc->tbInfo[1].schdlngForTb) == FALSE))
   {
      /*Now only one TB left, the other TB scheduled*/
      laaTbInfo->numTBs--;
      laaTbInfo->tbSz[1] = 0;
   }

}

/**
 * @brief Dl allocation finalization for ErrInd Schdulerd Transmissions.
 *
 * @details
 *
 *     Function : rgSCHErrIndDlAllocFnlz
 *
 *     Processing Steps:
 *     - If allocation succeded then remove from re-transmission list
 *       For SM UEs consider harq state of both TBs in case of MIMO.
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo  *allocInfo
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHLaaErrIndDlAllocFnlz 
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *allocInfo
)
#else
PUBLIC Void rgSCHLaaErrIndDlAllocFnlz(cell, allocInfo)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *allocInfo;
#endif
{
   RgSchUeCb       *ue;
   RgSchDlHqProcCb *hqP;
   RgSchDlRbAlloc  *dlRbAlloc;
   CmLList         *node;
   TRC2(rgSCHLaaErrIndDlAllocFnlz);

   node = allocInfo->dedAlloc.schdErrIndTxHqPLst.first;
   while(node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      hqP->laaHqP.procId = hqP->procId;
      ue  = hqP->hqE->ue;
      dlRbAlloc = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);
      node = node->next;
      rgSCHCmnFillHqPPdcch(cell, dlRbAlloc, hqP);
      rgSCHLAADlProcRmvFrmErrIndLst (cell, hqP);
      rgSCHCmnDlUeResetTemp(ue, hqP);
#ifdef TENB_STATS
      ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(hqP->hqE->cell)].dlRetxOccns++; 
#endif

   }

   node = allocInfo->dedAlloc.nonSchdErrIndTxHqPLst.first;
   while(node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      ue  = hqP->hqE->ue;
      node = node->next;
      rgSCHCmnDlUeResetTemp(ue, hqP);
   }
   RETVOID;
}



/**
 * @brief Dl LAA allocations finalizations on PCell for the UEs.
 *
 * @details
 *
 *     Function : rgSCHLaaDlAllocFnlz
 *
 *     Processing Steps:
 *
 *  @param[in]  RgSchCellCb            *cell
 *  @param[in]  RgSchCmnDlRbAllocInfo  *allocInfo
 *  @return  Void
 **/
#ifdef ANSI
PUBLIC Void rgSCHLaaDlAllocFnlz
(
RgSchCellCb             *cell,
RgSchCmnDlRbAllocInfo   *allocInfo
)
#else
PUBLIC Void rgSCHLaaDlAllocFnlz(cell, allocInfo)
RgSchCellCb             *cell;
RgSchCmnDlRbAllocInfo   *allocInfo;
#endif
{
   RgSchUeCb       *ue;
   RgSchDlHqProcCb *hqP;
   RgSchDlRbAlloc  *dlRbAlloc;
   CmLList         *node;

   TRC2(rgSCHLaaDlAllocFnlz);

   node = allocInfo->dedAlloc.schdTxLaaHqPLst.first;
   while(node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      ue  = hqP->hqE->ue;
      dlRbAlloc = RG_SCH_CMN_GET_ALLOCCB_FRM_UE(ue, cell);
      node = node->next;
      rgSCHCmnFillHqPPdcch(cell, dlRbAlloc, hqP);
      rgSCHLaaCheckRmvFrmLaaTBLst(cell, ue, dlRbAlloc);

#ifdef LTEMAC_HDFDD
      if (ue->hdFddEnbld)
      {
         rgSCHCmnHdFddUpdDLMark(cell, ue);
      }
#endif
      rgSCHCmnDlUeResetTemp(ue, hqP);
#ifdef TENB_STATS
      ue->tenbStats->stats.nonPersistent.sch[RG_SCH_CELLINDEX(hqP->hqE->cell)].dlRetxOccns++; 
#endif

   }

   node = allocInfo->dedAlloc.nonSchdTxLaaHqPLst.first;
   while(node)
   {
      hqP = (RgSchDlHqProcCb *)(node->node);
      ue  = hqP->hqE->ue;
      node = node->next;
      /* Fix: syed To update Retx Alloc failure counter.
       * Need to do the same in other schedulers as well. */
      /* Not freeing the TPC index as it would have arleady freed
       * during estimation phase itself. Even if scheduling fails for
       * rets corresponding proc will be added to non sched list.
       * so avoiding double deletion*/
#if 0
      rgSCHDhmDlRetxAllocFail(ue, hqP);
#endif
      rgSCHCmnDlUeResetTemp(ue, hqP);
   }
   RETVOID;
}

/**
 * @brief Init Function for the LAA Module
 *
 * @details
 *
 *     Function : rgSCHLaaSCellCbInit
 *     
 *     This function will initialiase the LAA Module Cb
 *           
 *  @param[in]  RgSchCellCb     *cell 
 *
 *  @return     S16
 *              #ROK
 *              #RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 rgSCHLaaSCellCbInit
(
RgSchCellCb    *pSchCellCb
)
#else
PUBLIC S16 rgSCHLaaSCellCbInit(pSchCellCb)
RgSchCellCb    *pSchCellCb;
#endif
{
   RgSchLaaCellCb *pLaaCell = &pSchCellCb->laaCellCb;

   TRC2(rgSCHDbmInitCell);

   if(FALSE == pSchCellCb->rgSchLAACellCfg.isLaaCell)
   {
      RETVALUE(ROK);
   }
#if 0
   /* Allocate the LAA Cell control block */
   if (((rgSCHUtlAllocSBuf(pSchCellCb->instIdx, (Data **)&pLaaCell, sizeof(RgSchLaaCell))) != ROK) ||
          ((U8 *)pLaaCell == NULLP))
   {
      RLOG_ARG1(L_ERROR, DBG_CELLID, pSchCellCb->cellId, "Memory allocation failed for LAA Cell Control Block\n");
      RETVALUE(RFAILED);
   }

   pSchCellCb->laaCell = pLaaCell;
#endif
   /* Initialize hqPs List */
   cmLListInit(&pLaaCell->errIndHqpLst);
   cmLListInit(&pLaaCell->laaTbsToBeSchedLst);


   RETVALUE(ROK);
}

/**
 * @brief DeInit Function for the LAA Module
 *
 * @details
 *
 *     Function : rgSCHLaaSCellCbDeInit
 *     
 *     This function will delete the LAA Module Cb
 *           
 *  @param[in]  RgSchCellCb     *cell 
 *
 *  @return     Void
 *
 **/
#ifdef ANSI
PUBLIC Void rgSCHLaaSCellCbDeInit
(
RgSchCellCb    *pSchCellCb
)
#else
PUBLIC Void rgSCHLaaSCellCbDeInit(pSchCellCb)
RgSchCellCb    *pSchCellCb;
#endif
{
   TRC2(rgSCHLaaSCellCbDeInit);

   if(FALSE == pSchCellCb->rgSchLAACellCfg.isLaaCell)
   {
      RETVOID;
   }
#if 0
   rgSCHUtlFreeSBuf(pSchCellCb->instIdx, (Data**)&(pSchCellCb->laaCell),
               sizeof(RgSchLaaCell));

   pSchCellCb->laaCell = NULLP;
#endif

}

/**
 * @brief Function to check the LAA SCell is enabled
 *
 * @details
 *
 *     Function : rgSCHLaaSCellEnabled
 *     
 *     This function will check if the Cell is LAA SCell Enabled
 *           
 *  @param[in]  RgSchCellCb     *cell 
 *
 *  @return     Bool
 *              #TRUE
 *              #FALSE
 *
 **/
#ifdef ANSI
PUBLIC Bool rgSCHLaaSCellEnabled
(
RgSchCellCb    *pSchCellCb
)
#else
PUBLIC Bool rgSCHLaaSCellEnabled(pSchCellCb)
RgSchCellCb    *pSchCellCb;
#endif
{
   TRC2(rgSCHLaaSCellEnabled);

   RETVALUE(pSchCellCb->rgSchLAACellCfg.isLaaCell);
}

#endif
