#include<stdio.h>
#ifdef ENABLE_CNM
static const char* RLOG_MODULE_NAME="ENBAPP";
static int RLOG_FILE_ID=12;
static int RLOG_MODULE_ID=64;
#include "wr.h"
#include "wr_cmn.h"
#include "wr_smm_smallcell.h"
#include "LtePhyL2Api.h"
#include "wr_emm.h"
#include "wr_smm_init.h"

#include "wr_cnm.h"
#include<math.h>

/* Add prototype here */
EXTERN PUBLIC U8  wrFillBwCfg(U8  dlBwIn);
PUBLIC S16 wrCnmTrigIctaStopReq(Void);
PUBLIC U16 wrCnmHandleIctaMsg
(
   Buffer *mBuf
);

Bool ictaStartMsgTrigd = FALSE;
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
/* This file contains the CNM related operations API's
 */

/** @brief This function is responsible for selecting  a neighbour cell to be synhronized.
 *
 * @details
 *
 *     Function: wrCnmSelectNghCellToSync
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

PRIVATE S16 wrCnmSelectNghCellToSync
(
WrEutranNeighCellCb      **cellToSync
)
{
   /* scan thru the enb list */
   WrNeighEnbCb *neighEnbCb                     = NULLP;
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

   RETVALUE(RFAILED);
}

/** @brief This function is responsible for initiating SYNC Start procedure
 *
 * @details
 *
 *     Function: wrCnmTrigIctaStartReq
 *
 *         Processing steps:
 *         - Invoke the cell selection algorithm
 *         - Frame the ICTA_START request message using the selected cell information
 *         - Raise an alarm to OAM if no cells are present for synchronization
 *
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PRIVATE S16 wrCnmDeriveFreqBand(U16 earfcn,U8 *freqBand)
{
   U8 bandIdx;
   for( bandIdx = 0; bandIdx < WR_CNM_MAX_EARFCN_TABLE_SIZE;bandIdx++)
   {
      if(earfcn >= earfcnTable[bandIdx].earfcnStart && 
         earfcn <= earfcnTable[bandIdx].earfcnEnd)
      {
         *freqBand = bandIdx;
         break;
      }
   }

   if(bandIdx == WR_CNM_MAX_EARFCN_TABLE_SIZE)
   {
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}
/** @brief This function is responsible for initiating SYNC Start procedure
 *
 * @details
 *
 *     Function: wrCnmTrigIctaStartReq
 *
 *         Processing steps:
 *         - Invoke the cell selection algorithm
 *         - Frame the ICTA_START request message using the selected cell information
 *         - Raise an alarm to OAM if no cells are present for synchronization
 *
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PRIVATE S16 wrCnmDeriveFreqFromEarfcn(U16 earfcn,U16 *freq)
{
   WrCnmEarfcnTable *earfcnTableEntry;
   U8 freqBand = 0;
   /* Freq = FDL_LOW + 0.1(Earfcn - earfcnOffset) . this is as per 36.104 */
   if(ROK != wrCnmDeriveFreqBand(earfcn,&freqBand))
   {
#ifdef CNM_DEBUG
      RLOG1(L_DEBUG, "Freq derivation failed for earfcn %d",earfcn);
#endif
      RETVALUE(RFAILED);
   }

   earfcnTableEntry = &earfcnTable[freqBand];

   /* fDlLow is in MHz */
   *freq = (earfcnTableEntry->fDlLow ) + ( 0.1 * ( earfcn -
            earfcnTableEntry->nOffsetDl));

#ifdef CNM_DEBUG
   RLOG2(L_DEBUG, "Earfcn %d Freq %d",earfcn,*freq);
#endif

   RETVALUE(ROK);

}

/** @brief This function is responsible for initiating SYNC Start procedure
 *
 * @details
 *
 *     Function: wrCnmTrigIctaStartReq
 *
 *         Processing steps:
 *         - Invoke the cell selection algorithm
 *         - Frame the ICTA_START request message using the selected cell information
 *         - Raise an alarm to OAM if no cells are present for synchronization
 *
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PUBLIC S16 wrCnmTrigIctaStartReq(Void)
{
   /* Select the CELL to be synced
    * Frame the ICTA STart message
    * Send the message to CL
    */
   WrEutranNeighCellCb *eutraNeghCell = NULLP;
   WrCnmIctaStartMsg cnmIctaStartMsg;
   WrCellCb                  *cellCb = NULLP;
   Buffer            *mBuf           = NULLP;
   Pst               pst;
   U32               refClkFreq = 0;/* 40Mhz for avnet
                                 * 25MHz for DM
                                 */
   U32               fracPart        = 0;
   U16               intPart         = 0;
   U16               freqSniff       = 0;
   U8                adiFactor       = 4; /* this is from ADI doc,
                                            * it will be 4 or TDD for all bands */
   U8                *vendorLst;


   if(wrCnmSelectNghCellToSync(&eutraNeghCell) == ROK )
   {
      if( ROK != SGetMsg(smCb.init.region, smCb.init.pool, (Buffer **) &mBuf))
      {
         RLOG0(L_FATAL, "Memory allocation failed.");
         RETVALUE(RFAILED);
      }

      cellCb = wrEmmCb.cellCb[WR_DFLT_CELL_IDX];

      if(cellCb == NULLP)
      {
#ifdef CNM_DEBUG
         RLOG0(L_ERROR,"CellCb Not found");
#endif
         RETVALUE(RFAILED);
      }
      if(wrSmDfltTddBoardType == 1)
      {/* AVNET setup */
         RLOG0(L_ALWAYS, "AVNET SETUP USED...");
         refClkFreq = 40; /* 40MHz */
      }
      else if(wrSmDfltTddBoardType == 2)
      {/* DM board setup */
         RLOG0(L_ALWAYS, "DM SETUP USED...");
         refClkFreq = 50; /* 25MHz */
      }
      /* Frame Start Msg */
#ifdef CNM_DEBUG
      RLOG3(L_DEBUG, "Icta ::Start :: NGH::earfcn %d serv earfcn %d nghPci %d",eutraNeghCell->earfcnDl,
            cellCb->dlCarrierFreq,eutraNeghCell->pci);
#endif
      cnmIctaStartMsg.msgLen              = sizeof(WrCnmIctaStartMsg);
      cnmIctaStartMsg.msgType             = WR_CNM_ICTA_START_REQ;
      cnmIctaStartMsg.phyEntityId         = 0;
      cnmIctaStartMsg.nghEarfcn           = eutraNeghCell->earfcnDl;
      cnmIctaStartMsg.servEarfcn          = cellCb->dlCarrierFreq;
      cnmIctaStartMsg.nghPci              = eutraNeghCell->pci;
      cnmIctaStartMsg.nghCellCp           = 0; /* as per mspd */
      cnmIctaStartMsg.nghSpecSfCfg        = 0;/* as per mspd */
      cnmIctaStartMsg.nghTxAntCount       = 2; /* Need to change hardcoding once this variables are populated from OAM*/
      cnmIctaStartMsg.nghTrackNRb         = wrFillBwCfg(eutraNeghCell->dlBw);
      cnmIctaStartMsg.trackPeriod         = 250; /* As per MSPD input *//* Data on every track_period will be stopped */
                                                 /* valid values are {10,20,40,100,250,500,1000} */
      cnmIctaStartMsg.vendorSpcfcLstCount = 0;
      cnmIctaStartMsg.radioChipType       = 0;/* 0:ADI936x */
#if 1
      cnmIctaStartMsg.vendorSpcfcLstCount = 1;
      /* Populate the 936x params 
       * Few params are board (DM , AVNET) specific
       */
       /* Steps
        * 1. Equation is
        * Integer part = Floor(Freq/Ref_freq)
        * Fractional Part = Round(8,388,593 * ((Freq/Ref_freq) IntegerPart))
        * Ref_freq for AVNET setup is 40MHz, DM board is 25MHz
        * Above equation and values are from intel
        * 2. Derive the freq from earfcn for neigh
        * 3. Calculate the Integer part
        * 4. Calculate the Fractoional Part
        * */
      if( ROK != wrCnmDeriveFreqFromEarfcn(eutraNeghCell->earfcnDl,
                                             &freqSniff))
      {
         RETVALUE(RFAILED);
      }

      vendorLst    = (U8 *)(cnmIctaStartMsg.vendorSpcfcLst.ictaRadioAddElement);

      //intPart      = (U16)(freqSniff/10);/* 10--> 40e6/4 */
      intPart      = (U16)((freqSniff * adiFactor)/refClkFreq);
      *vendorLst++ = (U8)(intPart); /* LSB byte .Little Endian*/
      *vendorLst++ = (U8)(intPart >> 8);  /* MSB byte */


      //fracPart     =  round((float)((freqSniff/1)-(intPart*10))*8388593)/10); /* 1 --> 40e6/4/10)*/
      //fracPart     =  round((float)((((freqSniff * adiFactor)/(refClkFreq/10))-(intPart*10))*8388593)/10); /* 1 --> 40e6/4/10)*/
      fracPart     =  round((float)((((freqSniff * adiFactor)/
                      (((float)(refClkFreq))/10))-(intPart*10))*8388593)/10); /* 1 --> 40e6/4/10)*/

      *vendorLst++ = (U8)(fracPart);/* 0-7 bits */
      *vendorLst++ = (U8)(fracPart >> 8);/* 8-15 bits */
      *vendorLst++ = (U8)(fracPart >> 16);/* 16-22 bits */


      *vendorLst++ = 0x50; // config word 5 data, 242[2:0]+239[3:0]              
      *vendorLst++ = 0x4E; // config word 6 data, 242[4:3]+Icp init <5:0>             
      *vendorLst++ = 0x0E; // config word 7 data, 23B[5:0] Icp <5:0>               
      *vendorLst++ = 0xBB; // config word 8 data, 240[3:0]+R3 init <3:0>               
      *vendorLst++ = 0xFF; // config word 9 data, 23F[3:0]+C3 init <3:0>               
      *vendorLst++ = 0x3C; // config word A data, 23E[3:0]+23E[7:4]              
      *vendorLst++ = 0xEE; // config word B data, 23F[7:4]+R1 init <3:0>               
      *vendorLst++ = 0x71; // config word C data, 250[6:4]+005[3:0]              
      *vendorLst++ = 0xE9; // config word D data, 238[6:3]+251[3:0]              
      *vendorLst++ = 0x45; // config word E data, 237[7:0]             
      *vendorLst++ = 0x48; // config word F data, 236[6:0]+238[0]  

      if(wrSmDfltTddBoardType == 2)
      {/* DM board */
        *vendorLst++=0x03; // Rx: 1A
      }
      else
      {/* non DM boards */
         *vendorLst++=0x4C; // Rx: 1C
      }
      vendorLst+=3;      // reserved

      /* Serving cells params */

      if( ROK != wrCnmDeriveFreqFromEarfcn(cellCb->dlCarrierFreq,
                                             &freqSniff))
      {
         RETVALUE(RFAILED);
      }

      vendorLst    = (U8 *)(cnmIctaStartMsg.vendorSpcfcLst.enbRadioAddElement);

      //intPart      = (U16)(freqSniff/10);
      intPart      = (U16)((freqSniff * adiFactor)/refClkFreq);
      *vendorLst++ = (U8)(intPart); /* LSB byte .Little Endian*/
      *vendorLst++ = (U8)(intPart >> 8);  /* MSB byte */

      //fracPart     =  round((float)(((freqSniff/(1))-(intPart*10))*8388593)/10);
      fracPart     =  round((float)((((freqSniff * adiFactor)/
                      (((float)(refClkFreq))/10))-(intPart*10))*8388593)/10); /* 1 --> 40e6/4/10)*/


      *vendorLst++ = (U8)(fracPart);/* 0-7 bits */
      *vendorLst++ = (U8)(fracPart >> 8);/* 8-15 bits */
      *vendorLst++ = (U8)(fracPart >> 16);/* 16-22 bits */

      *vendorLst++ = 0x50; // config word 5 data, 242[2:0]+239[3:0]              
      *vendorLst++ = 0x4E; // config word 6 data, 242[4:3]+Icp init <5:0>             
      *vendorLst++ = 0x0E; // config word 7 data, 23B[5:0] Icp <5:0>               
      *vendorLst++ = 0xBB; // config word 8 data, 240[3:0]+R3 init <3:0>               
      *vendorLst++ = 0xFF; // config word 9 data, 23F[3:0]+C3 init <3:0>               
      *vendorLst++ = 0x3C; // config word A data, 23E[3:0]+23E[7:4]              
      *vendorLst++ = 0xEE; // config word B data, 23F[7:4]+R1 init <3:0>               
      *vendorLst++ = 0x71; // config word C data, 250[6:4]+005[3:0]              
      *vendorLst++ = 0xE9; // config word D data, 238[6:3]+251[3:0]              
      *vendorLst++ = 0x45; // config word E data, 237[7:0]             
      *vendorLst++ = 0x48; // config word F data, 236[6:0]+238[0]  

      if(wrSmDfltTddBoardType == 2)
      {/* DM board */
        *vendorLst++=0x03; // Rx: 1A
      }
      else
      {/* non DM boards */
         *vendorLst++=0x4C; // Rx: 1C
      }

      vendorLst+=3;      // reserved

#endif
      if(ROK != SAddPstMsgMult((Data *)&cnmIctaStartMsg,
               sizeof(WrCnmIctaStartMsg),mBuf))
      {
#ifdef CNM_DEBUG
         RLOG0(L_ERROR, "SAddPst failed");
#endif
         RETVALUE(RFAILED);
      }

      
      cmMemset((U8*)&pst,0x00,sizeof(Pst));

      eutraNeghCell->isCnmPerformed = TRUE;
      
      /* send it to CL */
      pst.dstEnt = ENTYS;
      pst.srcEnt = ENTWR;
      pst.event  = WR_CNM_ICTA_START_REQ;/*CNM_EVENT;*/
#ifdef L2_L3_SPLIT      
      pst.dstProcId = 1;
#endif
      SPstTsk(&pst,mBuf);
      ictaStartMsgTrigd = TRUE;
      RETVALUE(ROK);
   }

   ictaStartMsgTrigd = FALSE;
   RETVALUE(RFAILED);
}

/** @brief This function is responsible for handling the incoming ICTA msgs from PHY
 *
 * @details
 *
 *     Function: wrCnmHandleIctaMsg
 *
 *         Processing steps:
 *         - Invoke the handlers based on the MsgType
 *         - If Sync loss is informed perform the following
 *            - Invoke ICTA Stop handler to stop sync procedure for the previous
 *            - selected cell 
 *            - Initiate Sync start for a new cell
 *
 * @param[in] mBuf : Incoming msg
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PUBLIC U16 wrCnmHandleIctaMsg
(
   Buffer *mBuf
)
{
   Data       *buf = NULLP;
   MsgLen     cLen;
   U16        ictaMsgLen;
   U8         msgStatus;
   
   SFndLenMsg(mBuf,(MsgLen *)&ictaMsgLen);

   if( ROK != SGetSBuf(smCb.init.region, 
            smCb.init.pool, &buf, ictaMsgLen))
   {
      RETVALUE(RFAILED);
   }

   if(ROK != SCpyMsgFix(mBuf, (MsgLen)0, (MsgLen)ictaMsgLen,
               (Data*) (buf), (MsgLen*)&cLen))
   {
      SPutSBuf(smCb.init.region, smCb.init.pool,
            (Data *)buf, (Size)ictaMsgLen);
      RETVALUE(RFAILED);
   }

   msgStatus = *((U8 *)(buf + 1));
   switch(((PGENMSGDESC )buf)->msgType)
   {
      case WR_CNM_ICTA_START_RESP:
         {
#ifdef CNM_DEBUG
            RLOG0(L_INFO, "[APP:] ICTA STAR RESP received....");
#endif
            if(msgStatus)
            {
#ifdef CNM_DEBUG
               RLOG1(L_INFO, "[APP]:: ICTA_START Failed. Status is %d",msgStatus);
#endif
               if(wrCnmTrigIctaStartReq() != ROK)
               {/* Trying to start ICTA_START For the next cell if avialble */
                  wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_CNM_SYNC_NOT_POSSIBLE,
                                LCM_CAUSE_UNKNOWN);
               }
            }
         }
         break;
      case WR_CNM_ICTA_SYNC_IND:
         {
            if(msgStatus) 
            {
#ifdef CNM_DEBUG
               RLOG1(L_WARNING, "SYNC Loss detected start trig is %d",ictaStartMsgTrigd);
#endif
               if(ictaStartMsgTrigd)
               {
                  if(wrCnmTrigIctaStopReq() != ROK)
                  {
#ifdef CNM_DEBUG
                     RLOG0(L_INFO, "STOP REq TRigger failed...");
#endif
                  }
               }

            }
            else
            {
#ifdef CNM_DEBUG
               RLOG0(L_INFO, "[APP]:: ICTA SYNC Resored....");
#endif
            }
         }
         break;
      case WR_CNM_ICTA_STOP_RESP:
         {
#ifdef CNM_DEBUG
            RLOG0(L_INFO, "[APP]:: Received ICTA_STOP_RESP ....");
#endif
            if(msgStatus)
            {
#ifdef CNM_DEBUG
               RLOG0(L_INFO, "[APP]:: ICTA_STOP Failed ....");
#endif
            }
            else
            {
#ifdef CNM_DEBUG
               RLOG0(L_INFO, "[APP]:: ICTA_STOP succeeded ....");
#endif
               /* Sync lost . Try syncing to next cell */
               if(wrCnmTrigIctaStartReq() != ROK)
               {
                  wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_CNM_SYNC_NOT_POSSIBLE,
                               LCM_CAUSE_UNKNOWN);
               }
            }
         }
         break;
      case WR_CNM_ICTA_FOE_RESP:
         {
#ifdef CNM_DEBUG
            RLOG0(L_INFO, "[APP]:: WR_CNM_ICTA_FOE_RESP received...");
            RLOG3(L_DEBUG, "Status is %d shortFoe %d longFoe %d",msgStatus,*((S16 *)(buf + 8)) , *((S16 *)(buf + 10))); 
#endif
         }
         break;
      default:
         {
#ifdef CNM_DEBUG
            RLOG0(L_WARNING, "Invalid Msg Received for CNM...");     
#endif
         }
         break;
   }

   SPutMsg(mBuf);
   RETVALUE(ROK);
}

/** @brief This function is responsible for framing the ICTA_STOP msg
 *
 * @details
 *
 *     Function: wrCnmTrigIctaStopReq
 *
 *         Processing steps:
 *         - Frame the ICTA_STOP message
 *         - Send the messge to CL
 *
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PUBLIC S16 wrCnmTrigIctaStopReq(Void)
{

   WrCnmIctaStopMsg cnmIctaStopMsg;
   Buffer            *mBuf = NULLP;
   Pst               pst;

   if( ROK != SGetMsg(smCb.init.region, smCb.init.pool, (Buffer **) &mBuf))
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   cnmIctaStopMsg.msgLen              = sizeof(WrCnmIctaStopMsg);
   cnmIctaStopMsg.msgType             = WR_CNM_ICTA_STOP_REQ;
   cnmIctaStopMsg.phyEntityId         = 0;
   cnmIctaStopMsg.vendorSpcfcLstCount = 0;

   if(ROK != SAddPstMsgMult((Data *)&cnmIctaStopMsg,
            sizeof(WrCnmIctaStopMsg),mBuf))
   {
#ifdef CNM_DEBUG
      RLOG0(L_ERROR, "SAddPst failed in StopReq...");
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8*)&pst,0x00,sizeof(Pst));
      /* send it to CL */
   pst.dstEnt = ENTYS;
   pst.srcEnt = ENTWR;
   pst.event  = WR_CNM_ICTA_STOP_REQ;/*CNM_EVENT;*/
   SPstTsk(&pst,mBuf);

#ifdef CNM_DEBUG
   RLOG0(L_INFO, "Posted ICTA_STOP...");
#endif
   RETVALUE(ROK);
}

/** @brief This function is responsible for framing the ICTA_FOE req msg
 *
 * @details
 *
 *     Function: wrCnmTrigIctaFoeReq
 *
 *         Processing steps:
 *         - Frame the ICTA_FOE_REQ message
 *         - Send the messge to CL
 *
 * @return U16
 *     -# Success  : ROK
 *     -# Failure  : RFAILED
 */
PUBLIC S16 wrCnmTrigIctaFoeReq(Void)
{

   WrCnmIctaFoeReqMsg cnmIctaFoeReqMsg;
   Buffer            *mBuf = NULLP;
   Pst               pst;

   if( ROK != SGetMsg(smCb.init.region, smCb.init.pool, (Buffer **) &mBuf))
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   cnmIctaFoeReqMsg.msgLen              = sizeof(WrCnmIctaFoeReqMsg);
   cnmIctaFoeReqMsg.msgType             = WR_CNM_ICTA_FOE_REQ;
   cnmIctaFoeReqMsg.phyEntityId         = 0;
   cnmIctaFoeReqMsg.vendorSpcfcLstCount = 0;

   if(ROK != SAddPstMsgMult((Data *)&cnmIctaFoeReqMsg,
            sizeof(WrCnmIctaFoeReqMsg),mBuf))
   {
      RETVALUE(RFAILED);
   }

   cmMemset((U8*)&pst,0x00,sizeof(Pst));
      /* send it to CL */
   pst.dstEnt = ENTYS;
   pst.srcEnt = ENTWR;
   pst.event  = WR_CNM_ICTA_FOE_REQ;/*CNM_EVENT;*/
   SPstTsk(&pst,mBuf);

#ifdef CNM_DEBUG
   RLOG0(L_INFO, "Posted ICTA_FOE_REQ...");
#endif
   RETVALUE(ROK);
}
#endif
