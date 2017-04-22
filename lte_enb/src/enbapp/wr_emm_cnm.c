
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains CNM realted functions

     File:     wr_emm_cnm.c

     Sid:      fc_emm_cnm.c@@/main/Br_Tenb_Brdcm_Bcm61750_Intg_GA2_0_TDD_GAFDD_final/2 - Mon Jun 30 15:48:26 2014

     Prg:      Sriky

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="EMM";
static int RLOG_MODULE_ID=1;
static int RLOG_FILE_ID=127;

/* header include files (.h) */
#include<stdio.h>
#include "wr.h"
#include "wr_cmn.h"
#include "wr_smm_smallcell.h"
//#include "LtePhyL2Api.h"
#include "wr_emm.h"
#include "wr_smm_init.h"
#include "wr_emm_cnm.h"
#include "wr_ifm_l1.h"

/* Add prototype here */
#ifdef BRDCM
Bool ictaStartMsgTrigd = FALSE;
#endif
U16 bwToNumRb[] = {6,15,25,50,75,100};
#ifdef BRDCM
WrCnmEarfcnTable earfcnTable[WR_CNM_MAX_EARFCN_TABLE_SIZE] =
{
   {1900,36000,36000,36199,33},
   {2010,36200,36200,36349,34},
   {1850,36350,36350,36949,35},
   {1930,36950,36950,37549,36},
   {1910,37550,37550,37749,37},
   {2570,37750,37750,38249,38},
   {1880,38250,38250,38249,39},
   {2300,38650,38650,39649,40},
};
#endif
/* This file contains the CNM related operations API's
 */

/** @brief This function is responsible for selecting  a neighbour cell to be synhronized.
 *
 * @details
 *
 *     Function: wrEmmCnmSelectNghCellToSync
 *
 *         Processing steps:
 *         - Select the strongest Non CSG cell based on RSRP
 *         - Select the strongest CSG cell based on RSRP in absence of non csg cell
 *
 * @param[in] cellToSync     : Selected cell information
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */

PRIVATE S16 wrEmmCnmSelectNghCellToSync
(
WrEutranNeighCellCb      **cellToSync
)
{
   WrNeighEnbCb             *neighEnbCb         = NULLP;
   WrEutranNeighCellCb      *eutranNeighCell    = NULLP;
   WrEutranNeighCellCb      *csgCellSelected    = NULLP;
   WrEutranNeighCellCb      *nonCsgCellSelected = NULLP;
   CmLList                  *nbrLnk             = NULLP;
   PTR                      enbPrevEntry        = NULLP;
   U16                      retVal;
   S16                      nonCsgRsrp          = -300;/* Need to set the lower value */
   S16                      csgRsrp             = -300;

   
   while((retVal = cmHashListGetNext(&(wrEmmCb.neighEnbLstCp),
               enbPrevEntry, (PTR *) &neighEnbCb)) == ROK)
   {
      /* scan thru the servcellList per enb */
      CM_LLIST_FIRST_NODE(&(neighEnbCb->srvdCellLst), nbrLnk);
      while(NULLP != nbrLnk)
      {
         eutranNeighCell =(WrEutranNeighCellCb *)nbrLnk->node;
         if(!eutranNeighCell->isCnmPerformed) 
         {
            if(!eutranNeighCell->isCsgCell)   
            {

               if(nonCsgRsrp < eutranNeighCell->detectedRsrp)
               {
                  nonCsgRsrp = eutranNeighCell->detectedRsrp;
                  nonCsgCellSelected = eutranNeighCell;
               }
            }
            else
            {
               if(csgRsrp < eutranNeighCell->detectedRsrp)
               {
                  csgRsrp = eutranNeighCell->detectedRsrp;
                  csgCellSelected = eutranNeighCell;
               }
            }
         }
         CM_LLIST_NEXT_NODE(&(neighEnbCb->srvdCellLst), nbrLnk);
      }
      enbPrevEntry = (PTR)neighEnbCb;
   }

   
   if(nonCsgCellSelected)
   {
     /* FIll from non csg cell */
      *cellToSync = nonCsgCellSelected;
      RETVALUE(ROK);
   }

   if(csgCellSelected)
   {
      /* Fill from CSG Cell */
      *cellToSync = csgCellSelected;
      RETVALUE(ROK);
   }
   RLOG0(L_ERROR, "Failed to select neighbor to sync");
   RETVALUE(RFAILED);
}

/** @brief This function is responsible for resetting the CNM flag in all
 *         the neighbors.
 *
 * @details
 *
 *     Function: wrEmmCnmResetNbrCnmStatus
 *
 *         Processing steps:
 *         - Fetch the neighbor cell CB.
 *         - reset isCnmPerformed flag to FALSE.
 *
 * @return U16
 *     -# Success  : ROK
 */
PRIVATE S16 wrEmmCnmResetNbrCnmStatus
(
Void
)
{
   WrNeighEnbCb             *neighEnbCb         = NULLP;
   WrEutranNeighCellCb      *eutranNeighCell    = NULLP;
   CmLList                  *nbrLnk             = NULLP;
   PTR                      enbPrevEntry        = NULLP;
   
   while(ROK == cmHashListGetNext(&(wrEmmCb.neighEnbLstCp),
               enbPrevEntry, (PTR *) &neighEnbCb))
   {
      CM_LLIST_FIRST_NODE(&(neighEnbCb->srvdCellLst), nbrLnk);
      while(NULLP != nbrLnk)
      {
         eutranNeighCell =(WrEutranNeighCellCb *)nbrLnk->node;
         if(eutranNeighCell->isCnmPerformed) 
         {
            eutranNeighCell->isCnmPerformed = FALSE;
         }
         CM_LLIST_NEXT_NODE(&(neighEnbCb->srvdCellLst), nbrLnk);
      }
      enbPrevEntry = (PTR)neighEnbCb;
   }

   RETVALUE(ROK);
}

/** @brief This function is responsible for filling Initial Sync Request message
 *
 * @details
 *
 *     Function: wrEmmCnmFillInitalSyncReq
 *
 *         Processing steps:
 *         - Fill the CnmInitialSyncReq message using information in Neighbour
 *           CB
 *
 * @return U16
 *     -# Success  : ROK
 */
PRIVATE S16 wrEmmCnmFillInitalSyncReq
(
WrEutranNeighCellCb          *eutraNeghCell,
CtfCnmInitSyncReq            *cnmInitSyncReq
)
{

   cnmInitSyncReq->mibRequest      = TRUE;
   cnmInitSyncReq->earfcn          = eutraNeghCell->earfcnDl;
   cnmInitSyncReq->measBandWidth   = bwToNumRb[eutraNeghCell->dlBw]; /*100eutraNeghCell->dlBw*/;
   cnmInitSyncReq->numOfPciList    = 1;
   /* Initial Sync Request always contains 1 neighbour */
   cnmInitSyncReq->pciList[0].nbrEarfcn  = eutraNeghCell->earfcnDl;
   cnmInitSyncReq->pciList[0].nbrPCellId  = eutraNeghCell->pci;
   cnmInitSyncReq->pciList[0].nbrTxAntCount  = eutraNeghCell->numAntenna;
   cnmInitSyncReq->pciList[0].nbrCellNRb  = bwToNumRb[eutraNeghCell->dlBw]; /* 100eutraNeghCell->dlBw*/;
#ifdef LTE_TDD
   cnmInitSyncReq->pciList[0].nbrCellCp  = eutraNeghCell->cpDl;
   cnmInitSyncReq->pciList[0].nbrSpecSfCfg  = eutraNeghCell->splSfCfg;
#endif

   eutraNeghCell->isCnmPerformed = TRUE;

   RETVALUE(ROK);
}

/** @brief This function is responsible for initiating SYNC Start procedure
 *
 * @details
 *
 *     Function: wrEmmCnmStartInitalSync
 *
 *         Processing steps:
 *         - Invoke the cell selection algorithm
 *         - Fill the CnmInitialSyncReq message and send to L1
 *         - Raise an alarm to OAM if no cells are present for synchronization
 *
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PUBLIC S16 wrEmmCnmStartInitalSync
(
Void
)
{
   WrEutranNeighCellCb      *eutraNeghCell  = NULLP;
   CtfCnmInitSyncReq        *cnmInitSyncReq = NULLP;
   WrCellCb                 *cellCb         = NULLP;
   U8                       cellIdx;

   if(FALSE == wrEmmCb.isCnmEnabled)
   {
      RLOG0(L_INFO, "[ALARM] Sending INIT_SYNC_SUCCESS to OAM");
      wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_INIT_SYNC_SUCCESS,
            LCM_CAUSE_UNKNOWN);
      RLOG0(L_INFO, "CNM flag is disabled");
      RETVALUE(ROK);
   }

   for(cellIdx = 0; cellIdx < WR_MAX_CELLS; cellIdx++)
   {
      cellCb = wrEmmCb.cellCb[cellIdx];
      if(cellCb == NULLP)
      {
         RLOG1(L_ERROR, "Cell CB not found cellIdx[%d]", cellIdx);
         continue;
      }

      WR_ALLOC(&cnmInitSyncReq, sizeof(CtfCnmInitSyncReq));
      if(NULLP == cnmInitSyncReq)
      {
         RLOG0(L_FATAL, "Memory allocation failed.");
         RETVALUE(RFAILED);
      }

      if(ROK == wrEmmCnmSelectNghCellToSync(&eutraNeghCell))
      {
         RLOG3(L_INFO, "Initial sync start NBR info :: EARFCN %d PCI %d "
               "serving EARFCN %d\n", eutraNeghCell->earfcnDl,
               eutraNeghCell->pci, cellCb->dlCarrierFreq);
         cellCb->cnmLstSyncPci    = eutraNeghCell->pci;

         wrEmmCnmFillInitalSyncReq(eutraNeghCell, cnmInitSyncReq);

         if(ROK != wrIfmPhyCnmInitialSyncReq(cnmInitSyncReq, (U32)cellCb->cellId))
         {
            RLOG0(L_ERROR, "Sending initial sync start request failed");
            RETVALUE(RFAILED);
         }

         cellCb->cnmState = WR_EMM_CNM_INIT_SYNC_IN_PROGRESS;
      }
      else
      {
         RLOG0(L_ERROR, "[ALARM] Sending SYNC_NBR_CELL_UNAVAILABLE to OAM");
         RLOG1(L_ERROR, "Neighbor not found for initial Sync :: "
               "serving EARFCN %d\n", cellCb->dlCarrierFreq);
         wrSendLmAlarm(LCM_CATEGORY_PROTOCOL,
               LWR_EVENT_SYNC_NBR_CELL_UNAVAILABLE, LCM_CAUSE_UNKNOWN);
         continue;
      }
   }

   RETVALUE(ROK);
}

/** @brief This function is responsible for processing Initial Sync Response
 *
 * @details
 *
 *     Function: wrEmmCnmPrcInitSyncRsp
 *
 *         Processing steps:
 *         - If sync response status is OK,
 *           - Update the incoming MIB parameters in NBR CB
 *         - Else,
 *           - select a new PCI for synchronization
 *
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PUBLIC S16 wrEmmCnmPrcInitSyncRsp
(
U16                          cellId,
CtfCnmInitSyncRsp            *cnmInitSyncRsp
)
{
   WrEutranNeighCellCb       *eutraNeghCell  = NULLP;
   CtfCnmInitSyncReq         *cnmInitSyncReq = NULLP;
   WrCellCb                  *cellCb         = NULLP;
   WrEutranNbrCellInfo       nrInfo;
   CtfCnmMibInfo             *mibInfo;

   WR_EMM_GET_CELLCB(cellCb, cellId);
   if(cellCb == NULLP)
   {
      RLOG1(L_ERROR, "CellCb not found [%d]", cellId);
      RETVALUE(RFAILED);
   }

   if(ROK == cnmInitSyncRsp->status)
   {
      RLOG2(L_ERROR, "Initial sync successful EARFCN [%d] PCI [%d]", 
            cnmInitSyncRsp->earfcn, cnmInitSyncRsp->ctfCnmInitSyncInfo[0].pci);
      nrInfo.earfcn    = cnmInitSyncRsp->earfcn;
      /* Initial Sync Response always contains 1 neighbour */
      nrInfo.phyCellId = cnmInitSyncRsp->ctfCnmInitSyncInfo[0].pci;

      eutraNeghCell = wrEmmAnrGetEutranNr(&cellCb->nrCb->eutranCb, &nrInfo);
      if(NULLP == eutraNeghCell)
      {
         RLOG2(L_WARNING,"Failed to get neighbor cell CB PCI [%d] EARFCN [%d]",
               cellCb->cnmLstSyncEarfcn, cellCb->cnmLstSyncPci);
         RLOG0(L_WARNING, "[ALARM] Sending INIT_SYNC_SUCCESS to OAM");
         wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_INIT_SYNC_SUCCESS,
            LCM_CAUSE_UNKNOWN);
         RETVALUE(RFAILED);
      }

      eutraNeghCell->detectedRsrp = cnmInitSyncRsp->ctfCnmInitSyncInfo[0].rsrp;
      mibInfo = &cnmInitSyncRsp->ctfCnmInitSyncInfo[0].ctfCnmMibInfo;
      eutraNeghCell->cnmMibInfo.sfn = mibInfo->sfn;
      eutraNeghCell->cnmMibInfo.numTxAntennas = mibInfo->numTxAntennas;
      eutraNeghCell->cnmMibInfo.phichDuration = mibInfo->phichDuration;
      eutraNeghCell->cnmMibInfo.phichResource = mibInfo->phichResource;
      eutraNeghCell->cnmMibInfo.dlSystemBandWidht = mibInfo->dlSystemBandWidht;

      /* Update last synchronized neighbour info in cellCb */
      cellCb->cnmLstSyncEarfcn = cnmInitSyncRsp->earfcn;
      cellCb->cnmLstSyncPci    = cnmInitSyncRsp->ctfCnmInitSyncInfo[0].pci;
      cellCb->cnmState         = WR_EMM_CNM_IN_SYNC;

      RLOG0(L_INFO, "[ALARM] Sending INIT_SYNC_SUCCESS to OAM");
      wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_INIT_SYNC_SUCCESS,
            LCM_CAUSE_UNKNOWN);
   }
   else
   {
      RLOG3(L_ERROR, "Initial sync failed EARFCN [%d] PCI [%d] status [%d]", 
            cnmInitSyncRsp->earfcn, cellCb->cnmLstSyncPci,
            cnmInitSyncRsp->status);
      if(ROK == wrEmmCnmSelectNghCellToSync(&eutraNeghCell))
      {
         RLOG3(L_INFO, "Initial Sync start NBR Info :: EARFCN %d PCI %d "
               "serving EARFCN %d\n", eutraNeghCell->earfcnDl,
               eutraNeghCell->pci, cellCb->dlCarrierFreq);

         WR_ALLOC(&cnmInitSyncReq, sizeof(CtfCnmInitSyncReq));
         if(NULLP == cnmInitSyncReq)
         {
            RLOG0(L_FATAL, "Memory allocation failed for CNM init sync req");
            RETVALUE(RFAILED);
         }

         wrEmmCnmFillInitalSyncReq(eutraNeghCell, cnmInitSyncReq);

         if(ROK != wrIfmPhyCnmInitialSyncReq(cnmInitSyncReq,
                  (U32)cellCb->cellId))
         {
            RLOG0(L_ERROR, "Sending initial sync start request failed");
            RETVALUE(RFAILED);
         }
      }
      else
      {
         RLOG1(L_ERROR, "Neighbor not found for initial sync :: "
               "serving EARFCN %d\n", cellCb->dlCarrierFreq);
         RLOG0(L_ERROR, "[ALARM] Sending SYNC_NBR_CELL_UNAVAILABLE to OAM");
         wrSendLmAlarm(LCM_CATEGORY_PROTOCOL,
               LWR_EVENT_SYNC_NBR_CELL_UNAVAILABLE, LCM_CAUSE_UNKNOWN);
      }
   }

   RETVALUE(ROK);
}

/** @brief This function is responsible for sending sync request for a new cell
 *
 * @details
 *
 *     Function: wrEmmCnmSelectAndSndSyncReq
 *
 *         Processing steps:
 *         - Use the existing selected cell or new cell
 *         - If no cells are present for synchronization,
 *           - Raise an alarm
 *         - Else, Fill and send Cell Sync Request
 *
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PRIVATE S16 wrEmmCnmSelectAndSndSyncReq
(
U16                          cellId
)
{
   WrEutranNeighCellCb       *eutraNeghCell  = NULLP;
   CtfCnmCellSyncReq         *cnmSyncReq     = NULLP;
   WrCellCb                  *cellCb         = NULLP;
   S16                       ret = ROK;

   WR_EMM_GET_CELLCB(cellCb, cellId);
   if(cellCb == NULLP)
   {
      RLOG1(L_ERROR, "CellCb not found [%d]", cellId);
      RETVALUE(RFAILED);
   }

   /* avoiding race condition between any sync ind and sync req */
   if(WR_EMM_CNM_IN_SYNC != cellCb->cnmState)
   {
      RLOG1(L_WARNING, "Ignoring syncInd in state [%d]", cellCb->cnmState);
      RETVALUE(ROK);
   }

   /* select a new PCI for synchronization */
   ret = wrEmmCnmSelectNghCellToSync(&eutraNeghCell);
   if(NULLP == eutraNeghCell)
   {
      RLOG0(L_ERROR,"eutraNeghCell cell not found ");
      RETVALUE(RFAILED);
   }
   WR_ALLOC(&cnmSyncReq, sizeof(CtfCnmCellSyncReq));
   if(NULLP == cnmSyncReq)
   {
      RLOG0(L_FATAL, "Memory allocation failed for CNM cel sync req");
      RETVALUE(RFAILED);
   }

   cnmSyncReq->nbrEarfcn  = eutraNeghCell->earfcnDl;
   cnmSyncReq->nbrPCellId  = eutraNeghCell->pci;
   cnmSyncReq->nbrTxAntCount  = eutraNeghCell->numAntenna;
   cnmSyncReq->nbrCellNRb  = bwToNumRb[eutraNeghCell->dlBw];/*100;*/
#ifdef LTE_TDD
   cnmSyncReq->nbrCellCp  = eutraNeghCell->cpDl;
   cnmSyncReq->nbrSpecSfCfg  = eutraNeghCell->splSfCfg;
#endif
   eutraNeghCell->isCnmPerformed = TRUE;

   /* Update last synchronized neighbour info in cellCb */
   cellCb->cnmLstSyncEarfcn = eutraNeghCell->earfcnDl;
   cellCb->cnmLstSyncPci    = eutraNeghCell->pci;
   cellCb->cnmState         = WR_EMM_CNM_SYNC_AFTER_SYNC_LOSS;

   if(ROK != wrIfmPhyCnmCellSyncReq(cnmSyncReq, (U32)cellCb->cellId))
   {
      RLOG0(L_ERROR, "Sending initial sync start request failed");
      RETVALUE(RFAILED);
   }

   RLOG3(L_INFO, "Cell sync request neighbor info :: EARFCN %d PCI %d "
         "serving EARFCN %d\n", eutraNeghCell->earfcnDl,
         eutraNeghCell->pci, cellCb->dlCarrierFreq);

   RETVALUE(ret);
}

/** @brief This function is responsible for processing CNM Sync Indication
 *
 * @details
 *
 *     Function: wrEmmCnmPrcSyncInd
 *
 *         Processing steps:
 *         - Raise an alarm to OAM if no cells are present for synchronization
 *
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PUBLIC S16 wrEmmCnmPrcSyncInd
(
U16                          cellId,
CtfCnmCellSyncInd            *cnmSyncInd
)
{
   if(RFAILED == cnmSyncInd->status)
   {
      RLOG1(L_ERROR, "Sync status indication with status FAILED [%d]",
            cnmSyncInd->status);
      wrEmmCnmSelectAndSndSyncReq(cellId);
   }
   else
   {
      RLOG1(L_ERROR, "Sync status indication with status SUCCESS [%d]",
            cnmSyncInd->status);
   }

   RETVALUE(ROK);
}

/** @brief This function is responsible for processing CNM Sync Response
 *
 * @details
 *
 *     Function: wrEmmCnmPrcSyncRsp
 *
 *         Processing steps:
 *         - Raise an alarm to OAM if no cells are present for synchronization
 *
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PUBLIC S16 wrEmmCnmPrcSyncRsp
(
U16                          cellId,
CtfCnmCellSyncRsp            *cnmSyncRsp
)
{
   WrCellCb                  *cellCb         = NULLP;

   WR_EMM_GET_CELLCB(cellCb, cellId);
   if(cellCb == NULLP)
   {
      RLOG1(L_ERROR, "CellCb not found [%d]", cellId);
      RETVALUE(RFAILED);
   }

   if(ROK == cnmSyncRsp->status)
   {
      RLOG2(L_ERROR, "Cell sync successful EARFCN [%d] PCI [%d]", 
            cellCb->cnmLstSyncEarfcn, cellCb->cnmLstSyncPci);
      cellCb->cnmState = WR_EMM_CNM_IN_SYNC;
   }
   else
   {
      RLOG3(L_ERROR, "Cell sync failed EARFCN [%d] PCI [%d] status [%d]", 
            cellCb->cnmLstSyncEarfcn, cellCb->cnmLstSyncPci,
            cnmSyncRsp->status);
      wrEmmCnmSelectAndSndSyncReq(cellId);
   }

   RETVALUE(ROK);
}

/** @brief This function is responsible for processing S1 Link Up Indication
 *
 * @details
 *
 *     Function: wrEmmCnmPrcS1LnkUp
 *
 *         Processing steps:
 *         - Send Initial Sync Request to CL for last synced neighbor
 *
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PUBLIC S16 wrEmmCnmPrcS1LnkUp
(
Void
)
{
   WrEutranNeighCellCb       *eutraNeghCell  = NULLP;
   CtfCnmInitSyncReq         *cnmInitSyncReq = NULLP;
   WrCellCb                  *cellCb         = NULLP;
   WrEutranNbrCellInfo       nrInfo;
   U8                        cellIdx;

   if(FALSE == wrEmmCb.isCnmEnabled)
   {
      RLOG0(L_INFO, "[ALARM] Sending INIT_SYNC_SUCCESS to OAM");
      wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_INIT_SYNC_SUCCESS,
            LCM_CAUSE_UNKNOWN);
      RLOG0(L_INFO, "CNM flag is disabled");
      RETVALUE(ROK);
   }

   for(cellIdx = 0; cellIdx < WR_MAX_CELLS; cellIdx++)
   {
      cellCb = wrEmmCb.cellCb[cellIdx];
      if(cellCb == NULLP)
      {
         RLOG1(L_ERROR, "Cell CB not found cellIdx[%d]", cellIdx);
         continue;
      }

      if(WR_CELL_STATE_PWR_DOWN == cellCb->cellState)
      {
         /* Use the last PCI with which synchronization was successful */
         nrInfo.earfcn    = cellCb->cnmLstSyncEarfcn;
         nrInfo.phyCellId = cellCb->cnmLstSyncPci;

         cellCb->cnmState = WR_EMM_CNM_INIT_SYNC_AFTER_S1_UP;
         /*vrr */
         wrEmmCnmResetNbrCnmStatus();

         eutraNeghCell = wrEmmAnrGetEutranNr(&cellCb->nrCb->eutranCb, &nrInfo);
         if(NULLP == eutraNeghCell)
         {
            RLOG2(L_ERROR,"Failed to get neighbor Cell CB EARFCN [%d] PCI [%d]",
                  nrInfo.earfcn, nrInfo.phyCellId);
            if(ROK != wrEmmCnmSelectNghCellToSync(&eutraNeghCell))
            {
               RLOG2(L_ERROR, "Neighbor not found for initial sync :: "
                     "serving EARFCN [%d] CellId [%d]\n",
                     cellCb->dlCarrierFreq, cellCb->cellId);
               RLOG0(L_ERROR, "[ALARM] Sending SYNC_NBR_CELL_UNAVAILABLE to OAM");
               wrSendLmAlarm(LCM_CATEGORY_PROTOCOL,
                     LWR_EVENT_SYNC_NBR_CELL_UNAVAILABLE, LCM_CAUSE_UNKNOWN);
               continue;
            }
         }

         WR_ALLOC(&cnmInitSyncReq, sizeof(CtfCnmInitSyncReq));
         if(NULLP == cnmInitSyncReq)
         {
            RLOG0(L_FATAL, "Memory allocation failed for CNM init sync req");
            RETVALUE(RFAILED);
         }

         RLOG3(L_INFO, "Initial sync start NBR info :: EARFCN %d PCI %d "
               "serving EARFCN %d\n", eutraNeghCell->earfcnDl,
               eutraNeghCell->pci, cellCb->dlCarrierFreq);

         wrEmmCnmFillInitalSyncReq(eutraNeghCell, cnmInitSyncReq);

         if(ROK != wrIfmPhyCnmInitialSyncReq(cnmInitSyncReq,
                  (U32)cellCb->cellId))
         {
            RLOG0(L_ERROR, "Sending initial sync start request failed");
            RETVALUE(RFAILED);
         }
      }
      else
      {
         RLOG0(L_INFO, "[ALARM] Sending S1CON_SET_SUCCESS to OAM");
         wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_S1CON_SET_SUCCESS,
               LCM_CAUSE_UNKNOWN);
      }
   }

   RETVALUE(ROK);
}

/** @brief This function is responsible for displaying all intra-frequency
 *         neighbors from the NRT list of the corresponding cellId.
 *
 * @details
 *
 *     Function: wrEmmCnmPrntEutraNbrInfo
 *
 *         Processing steps:
 *         - Fetch cellCb
 *         - Display all the intra-frequency neighbors from the NRT list
 *
 * @return Void
 */
PUBLIC Void wrEmmCnmPrntEutraNbrInfo
(
U16                          cellId
)
{
   WrNeighEnbCb              *neighEnbCb         = NULLP;
   WrEutranNeighCellCb       *eutranNeighCell    = NULLP;
   CmLList                   *nbrLnk             = NULLP;
   PTR                       enbPrevEntry        = NULLP;
   WrCellCb                  *cellCb             = NULLP;
   WrEutranNbrCellInfo       nrInfo;
   U16                       retVal;

   WR_EMM_GET_CELLCB(cellCb, cellId);
   if(cellCb == NULLP)
   {
      RLOG1(L_ERROR, "Cell CB not found cellId [%d]", cellId);
      RETVOID;
   }

   nrInfo.earfcn    = cellCb->cnmLstSyncEarfcn;
   nrInfo.phyCellId = cellCb->cnmLstSyncPci;

   eutranNeighCell = wrEmmAnrGetEutranNr(&cellCb->nrCb->eutranCb, &nrInfo);
   if(NULLP == eutranNeighCell)
   {
      RLOG2(L_ERROR,"Failed to get neighbor Cell EARFCN [%d] PCI [%d]",
            cellCb->cnmLstSyncEarfcn, cellCb->cnmLstSyncPci);
      RETVOID;
   }

   if(WR_EMM_CNM_IN_SYNC == cellCb->cnmState)
   {
      RLOG3(L_INFO, "Current synchronized NBR info syncstate [%d] "
            "DL EARFCN [%d] PCI [%d]",
            cellCb->cnmState,
            eutranNeighCell->earfcnDl,
            eutranNeighCell->pci);
      RLOG_STR(L_INFO,"ENB Type [%s]",((eutranNeighCell->enbType == WR_ENODEB_TYPE_MACRO)?"MACRO":"HOME"));
   }
   else
   {
      RLOG3(L_INFO, "Last synchronized neighbor info syncstate [%d] "
            "DL EARFCN [%d] PCI [%d]",
            cellCb->cnmState,
            eutranNeighCell->earfcnDl,
            eutranNeighCell->pci);
      RLOG_STR(L_INFO,"ENB Type [%s]",((eutranNeighCell->enbType == WR_ENODEB_TYPE_MACRO)?"MACRO":"HOME"));
   }

   RLOG0(L_INFO, "Display overall CNM neighbor info");

   while((retVal = cmHashListGetNext(&(wrEmmCb.neighEnbLstCp),
               enbPrevEntry, (PTR *) &neighEnbCb)) == ROK)
   {
      CM_LLIST_FIRST_NODE(&(neighEnbCb->srvdCellLst), nbrLnk);
      while(NULLP != nbrLnk)
      {
         eutranNeighCell =(WrEutranNeighCellCb *)nbrLnk->node;

         RLOG2(L_INFO, "DL EARFCN [%d] "
               "PCI [%d]",
               eutranNeighCell->earfcnDl,
               eutranNeighCell->pci);
         RLOG_STR(L_INFO,"ENB Type [%s]",((eutranNeighCell->enbType == WR_ENODEB_TYPE_MACRO)?"MACRO":"HOME"));
         RLOG_STR(L_INFO,"Used for CNM [%s]",((eutranNeighCell->isCnmPerformed == TRUE)?"YES":"NO"));

         CM_LLIST_NEXT_NODE(&(neighEnbCb->srvdCellLst), nbrLnk);
      }
      enbPrevEntry = (PTR)neighEnbCb;
   }
   RETVOID;
}

/********************************************************************30**

           End of file:     fc_emm_cnm.c@@/main/Br_Tenb_Brdcm_Bcm61750_Intg_GA2_0_TDD_GAFDD_final/2 - Mon Jun 30 15:48:26 2014

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

*********************************************************************91*/

