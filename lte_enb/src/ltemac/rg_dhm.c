




/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_dhm.c
  
     Sid:      gk_dhm.c@@/main/3 - Sat Jul 30 02:21:26 2011
  
     Prg:      ps
  
**********************************************************************/

/** @file rg_dhm.c
@brief APIs related to Downlink HARQ.
*/

static const char* RLOG_MODULE_NAME="MAC";
static int RLOG_FILE_ID=279;
static int RLOG_MODULE_ID=4096;
/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#ifdef L2_OPTMZ
#include "ss_strm.h"
#endif
#include "cm5.h"           /* common timers */
#include "cm_hash.h"       /* common hash list */
#include "cm_mblk.h"       /* common memory link list library */
#include "cm_llist.h"      /* common linked list library */
#include "cm_err.h"        /* common error */
#include "cm_lte.h"        /* common LTE */
#include "lrg.h"
#include "crg.h"
#include "rgu.h"
#include "tfu.h"
#include "rg_sch_inf.h"
#include "rg_env.h"
#include "rg_err.h"
#include "rg.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system service interface */
#ifdef L2_OPTMZ
#include "ss_strm.x"
#endif
#include "cm5.x"           /* common timers */
#include "cm_lib.x"        /* common library */
#include "cm_hash.x"       /* common hash list */
#include "cm_llist.x"      /* common linked list library */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"        /* common LTE */
#include "lrg.x"
#include "crg.x"
#include "rgu.x"
#include "tfu.x"
#include "rg_sch_inf.x"
#include "rg_prg.x"        /* PRG interface typedefs */
#include "rg.x"

#ifdef L2_OPTMZ
#include "ss_queue.h"
#include "ss_queue.x"
#include "ss_task.x"
#include "ss_msg.x"            /* MAC includes */
/* local defines */
//EXTERN  S16 ssGetDBufOfSize(Region region,Size size,Buffer **dBuf);
//void prc_trace_format_string(UINT32 group_mask, UINT16 level, const char *format, ...);
#endif

/* local typedefs */
 
/* local externs */
PRIVATE Void rgDHMBldTfuDatReq ARGS((RgCellCb *cellCb, RgDlSf *dlSf, RgDlHqProcCb *hqP,
                           RgTfuDatReqPduInfo *datReq));
#ifdef L2_OPTMZ
#define RG_MAC_HDR_SIZE 250
#define RG_MAC_CE_SIZE  250
U32 MacPtrAddress;
U32 macHeader[2];
#if 0
#else
#define RG_ADD_DBuf(_dBuf,_size,_mBuf)\
{ \
  SsMsgInfo *mInfo = NULLP; \
  mInfo = (SsMsgInfo *)_mBuf->b_rptr; \
  ssGetDBufOfSize(mInfo->region,_size, &_dBuf); \
  SUpdMsg(_mBuf, _dBuf,0);\
  _dBuf->b_wptr = _dBuf->b_rptr =  (_dBuf->b_datap->db_base + 5);\
  MacPtrAddress = (U32)_dBuf->b_wptr;\
}
#endif
  //printf("The write & read ptr is %p %p %p %p \n", _dBuf->b_wptr, _dBuf->b_rptr,_dBuf->b_datap->db_base, _dBuf->b_datap->db_lim );\
  //printf("The write & read ptr is %p %p \n", _dBuf->b_wptr, _dBuf->b_rptr);
PUBLIC S16 rgDHMFreeHqProcTB
(
RgDlHqProcCb         *hqP,
U8                   tbIndex
);

#endif

/* forward references */

/**
 * @brief This function initializes the DL HARQ Entity of UE
 *
 * @details
 *
 *     Function: rgDHMHqEntInit
 *     Purpose:  This function initializes the DL HARQ entity of 
 *               UE control block. This is performed at the time
 *               of creating UE control block.
 *     
 *     Invoked by: configuration module
 *     
 *  @param[in]  Inst        inst
 *  @param[in]  RgCellCb*  cell
 *  @param[in]  RgUeCb*    ue
 *  @return  S16
 *           -# ROK
 *           -# RFAILED
 *
 **/
#ifdef ANSI
PUBLIC S16 rgDHMHqEntInit
(
Inst               inst,
RgDlHqEnt          *hqE,
U8                 maxHqProcs
)
#else
PUBLIC S16 rgDHMHqEntInit(inst,hqE, maxHqProcs)
Inst               inst,
RgDlHqEnt          *hqE;
U8                 maxHqProcs;
#endif
{
   U8 idx1,idx2;
#ifdef L2_OPTMZ
   Buffer  *hdrDBuf = NULLP;
   Buffer  *ceDBuf = NULLP;
#endif

   TRC2(rgDHMHqEntInit)

   hqE->numHqProcs = maxHqProcs;
   /* for each harq process */
   for (idx1 = 0; idx1 < hqE->numHqProcs; idx1++)
   {
      if (rgAllocSBuf(inst,(Data **)&(hqE->procs[idx1]),sizeof(RgDlHqProcCb)) != ROK) 
      {
         while(idx1--)
         {
            rgFreeSBuf(inst,(Data **)&(hqE->procs[idx1]), sizeof(RgDlHqProcCb));
         }
         RLOG0(L_ERROR, "Memory Alloc Failure for RgDlHqProcCb");        
         RETVALUE(RFAILED);
      }

      hqE->procs[idx1]->procId      = idx1;
      for(idx2 = 0; idx2 < RG_MAX_TB_PER_UE; idx2++)
      {
#ifndef L2_OPTMZ
         hqE->procs[idx1]->tbInfo[idx2].tb = NULLP;
#else
         Buffer *tmpMBuf;
         /* L2 optimization for mUe/Tti: Allocating buffers for macHdr, macCes
          * and macPadding. These buffers shall not be released by MAC/CL.
          * However, Only rPtr and wPtr will be reset while release of hq proc
          */
         tmpMBuf = hqE->procs[idx1]->tbInfo[idx2].tb.macHdr;
         rgGetMsg(inst, &tmpMBuf);
         RG_ADD_DBuf(hdrDBuf, RG_MAC_HDR_SIZE, tmpMBuf);
         hqE->procs[idx1]->tbInfo[idx2].tb.macHdr = tmpMBuf;
         macHeader[idx2] = MacPtrAddress;

         tmpMBuf = hqE->procs[idx1]->tbInfo[idx2].tb.macCes;
         rgGetMsg(inst, &tmpMBuf);
         RG_ADD_DBuf(ceDBuf, RG_MAC_CE_SIZE, tmpMBuf);
         hqE->procs[idx1]->tbInfo[idx2].tb.macCes = tmpMBuf;

         hqE->procs[idx1]->tbInfo[idx2].tb.padSize = 0;
#endif
#ifdef LTE_L2_MEAS
         hqE->procs[idx1]->tbId[idx2] = RGU_INVALID_TBID;
#endif
      }

      cmLListInit(&hqE->savedProcLst[idx1]);
   }


   RETVALUE(ROK);
} /* rgDHMHqEntInit */

/**
 * @brief This function releases a HARQ process
 *
 * @details
 *
 *     Function: rgDHMUeReset
 *     Purpose:  This function resets TB in each HarqProc.
 *     
 *     Invoked by: CFG UE Reset 
 *     
 *  @param[in]  RgDlHqProc    *hqP
 *  @return  Void      
 *
 **/
#ifdef ANSI
PUBLIC Void rgDHMUeReset
(
RgCellCb *cell,
RgDlHqEnt          *hqE
)
#else
PUBLIC Void rgDHMUeReset(cell, hqE)
RgCellCb *cell;
RgDlHqEnt          *hqE;
#endif
{
   U8       i = 0;

   TRC2(rgDHMUeReset)

   if(hqE->procs[0])
   {
      /* Free all the TB memory associated with HARQ */
      for (i=0; i < hqE->numHqProcs; i++)
      {
         rgDHMRlsHqProcTB(cell, hqE->procs[i], 1);
         rgDHMRlsHqProcTB(cell, hqE->procs[i], 2);

         /* Free saved HqP node and TBs */
         rgDHMFreeSavedHqP((cell->macInst - RG_INST_START), hqE, i);
      }
   }
   RETVOID;
} /* rgDHMUeReset*/

/**
 * @brief This function defers shared memory buffer
 *        freeing out of the critical RT path.
 *
 * @details
 *
 *     Function: rgDHMHdlBufFree
 *     Purpose: To defer shared memory freeing post 
 *              critical path. Defer as many if defer queue 
 *              is full then release instantly.
 *     
 *     Invoked by: HARQ TB Release. 
 *     
 *  @return  Void      
 *
 **/
#ifdef ANSI
PUBLIC Void rgDHMHdlBufFree
(
Inst inst,
Buffer **mBuf
)
#else
PUBLIC Void rgDHMHdlBufFree(Inst inst, Buffer **mBuf)
Inst inst;
#endif
{
   RgCb *rgCbP = &rgCb[inst];
   TRC2(rgDHMHdlBufFree)

   if (rgCbP->bufCnt < RG_MAX_DFRD_FREE_BUFS)
   {
      if (*mBuf)
      {
         rgCbP->bufToFree[rgCbP->bufCnt] = *mBuf;
         rgCbP->bufCnt++;
         *mBuf = NULLP;
      }
   }
   else
   {
      RG_FREE_MSG(*mBuf);
   }
   RETVOID;
}
/**
 * @brief This function is called to release the 
 *        shared memory of the HARQ TBs outside 
 *        the critical RT path.
 *
 * @details
 *
 *     Function: rgDHMFreeTbBufs
 *     Purpose: This function is called to release the 
 *        shared memory of the HARQ TBs outside 
 *        the critical RT path.
 *     
 *     1. Job of releasing TBs is shared across TTIs
 *     Invoked by: MAC every TTI 
 *     
 *  @return  Void      
 *
 **/
#ifdef ANSI
PUBLIC Void rgDHMFreeTbBufs
(
Inst inst
)
#else
PUBLIC Void rgDHMFreeTbBufs(inst)
Inst inst;
#endif
{
   RgCb *rgCbP = &rgCb[inst];
   U8 start = rgCbP->bufCnt;
   U8 end = 0;

   TRC2(rgDHMFreeTbBufs)

   if (rgCbP->bufCnt < RG_MAX_FREE_BUFS_PERTTI)
   {
      end = 0;
   }
   else
   {
      end = rgCbP->bufCnt - RG_MAX_FREE_BUFS_PERTTI;
   }
   while (start != end)
   {
      start--;
      SPutMsg(rgCbP->bufToFree[start]);
   }
   rgCbP->bufCnt = end;
   RETVOID;
} /* rgDHMFreeTbBufs */

/**
 * @brief This function releases a HARQ process
 *
 * @details
 *
 *     Function: rgDHMRlsHqProcTB
 *     Purpose:  This function returns a HARQ process to HARQ Entity 
 *               in the DL direction.
 *     
 *               1. Add the HARQ process to the free queue.
 *     Invoked by: scheduler and HARQ processing
 *     
 *  @param[in]  RgDlHqProc    *hqP
 *  @return  Void      
 *
 **/
#ifdef ANSI
PUBLIC S16 rgDHMRlsHqProcTB
(
RgCellCb             *cell,
RgDlHqProcCb         *hqP,
U8                   tbIndex
)
#else
PUBLIC S16 rgDHMRlsHqProcTB(cell, hqP, tbIndex)
RgCellCb             *cell;
RgDlHqProcCb         *hqP;
U8                   tbIndex;
#endif
{
#ifdef L2_OPTMZ
    RgTfuDatReqTbInfo     *tb;   /* TB to be sent to CL/PHY*/
   // U32 lchIdx, pduIdx;
#endif

   TRC2(rgDHMRlsHqProcTB)

   if((tbIndex > RG_MAX_TB_PER_UE) ||
      (tbIndex == 0))
   {
      RETVALUE(RFAILED);
   }

   hqP->tbInfo[tbIndex-1].numSchLch = 0;
#ifndef L2_OPTMZ
   if (hqP->tbInfo[tbIndex-1].tb)
   {
      rgDHMHdlBufFree(cell->macInst - RG_INST_START, &hqP->tbInfo[tbIndex-1].tb);
   }
#else
   /* L2 Optimization for mUe/Tti:  macHdr, macCes and macPad mBuf pointers
    * shall not be released. However, Inorder to release harq info/TB info,
    * just Resetting rPtr and wPtr of these mbufs to db_base
    */
   tb = &(hqP->tbInfo[tbIndex-1].tb);
//   printf("\nrgDHMRlsHqProcTB: RG_FREE_TB1 \n");
   if (tb->tbPres == TRUE)
   {
      RG_FREE_TB(tb);
   }
#endif
   hqP->tbInfo[tbIndex-1].schdTa.pres = FALSE;
#ifdef LTE_ADV
   hqP->tbInfo[tbIndex -1].sCellActCe.pres = FALSE;
#endif

   /* Decrementing might lead to roundoff error in case of say UE reset
    * where all the HqProcs irrespective whether in use are called for rls.
    * Hence to avoid the same shift operator is being used. */
   hqP->numOfTBs = hqP->numOfTBs >> 1;
   if (hqP->tbInfo[tbIndex-1].sfLnk.node != NULLP)
   {
      cmLListDelFrm(&hqP->tbInfo[tbIndex-1].sf->tbs,
                    &hqP->tbInfo[tbIndex-1].sfLnk);
      hqP->tbInfo[tbIndex-1].sfLnk.node  = (PTR)NULLP;
   }
   hqP->tbInfo[tbIndex-1].sf = NULLP;
   /* Fix : syed It is better to reset these feilds
    * corruption avoidance */
   hqP->tbInfo[tbIndex-1].tbSz = 0;
   hqP->tbInfo[tbIndex-1].contResCe = NOTPRSNT;
   hqP->tbInfo[tbIndex-1].contResId = NULLP;

   RETVALUE(ROK);
} /* rgDHMRlsHqProc */

/**
 * @brief This function gets HARQ process with the given Id
 *
 * @details
 *
 *     Function: rgDHMGetHqProcFrmId
 *     Purpose:  This function returns the HARQ process with the given ID.
 *     Invoked by: ROM
 *     
 *  @param[in]  RgUeCb        *ue
 *  @param[in]  U8            idx
 *  @param[in]  RgDlHqProc    **hqP
 *  @return  S16       
 *         -#   ROK     if successful
 *         -#   RFAILED otherwise
 *
 **/
#ifdef ANSI
PUBLIC S16 rgDHMGetHqProcFrmId
(
RgUeCb               *ue,
U8                   idx,
RgDlHqProcCb         **hqP
)
#else
PUBLIC S16 rgDHMGetHqProcFrmId(ue, idx, hqP)
RgUeCb               *ue;
U8                   idx;
RgDlHqProcCb         **hqP;
#endif
{
   TRC2(rgDHMGetHqProcFrmId)

   /* Pick the proc based on the index provided */
   *hqP = (ue->dl.hqEnt.procs[idx]);

   RETVALUE(ROK);
} /* rgDHMGetHqProcFrmId */

/*PRIVATE U32 dataAvl; */
/**
 * @brief Handler for sending data to PHY
 *
 * @details
 *
 *     Function : rgDHMSndDatReq
 *     
 *     This function shall send the MAC PDU built for the UE to TOM
 *     when invoked as part of TTI processing and keep track of the number of
 *     transmissions for this TB.
 *     
 *           
 *  @param[in]  RgCellCb      *cell
 *  @param[in]  RgDlHqProcCb  *hqE 
 *  @param[out] RgErrInfo     *err 
 *  @return     S16
 *      -#ROK 
 *      -#RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgDHMSndDatReq
(
RgCellCb        *cellCb,
RgDlSf          *dlSf,
RgTfuDatReqInfo *datInfo,
RgDlHqProcCb   *hqP,
RgErrInfo      *err 
)
#else
PUBLIC S16 rgDHMSndDatReq(cellCb, dlSf, datInfo, hqP, err)
RgCellCb        *cellCb;
RgDlSf          *dlSf;
RgTfuDatReqInfo *datInfo;
RgDlHqProcCb    *hqP;
RgErrInfo       *err;
#endif
{
   U8 i;
   Inst               inst = cellCb->macInst - RG_INST_START;
   RgTfuDatReqPduInfo   *datReq;
   RgBldPduInfo      bldPdu;
   /*Added this variable to figure out that whether this UE data
     has to be inclueded in the TFU Data request.*/
   Bool  dataAvlblUe;

   TRC2(rgDHMSndDatReq)
  
   dataAvlblUe = TRUE;
   for(i=0;i< RG_MAX_TB_PER_UE;i++)
   {
      if (hqP->tbInfo[i].sf == dlSf)
      {
         /* Check if data from RLC had been received and got muxed. */
#ifndef L2_OPTMZ
         if (hqP->tbInfo[i].tb == NULLP) 
#else
         if (!(hqP->tbInfo[i].tb.tbPres)) 
#endif
         {
#ifndef LTE_ADV
            if (hqP->tbInfo[i].schdTa.pres == TRUE ||
                  hqP->tbInfo[i].contResCe == PRSNT_NODEF)
#else
            if ((hqP->tbInfo[i].schdTa.pres == TRUE) ||
                 (hqP->tbInfo[i].contResCe == PRSNT_NODEF) ||
                 (hqP->tbInfo[i].sCellActCe.pres == TRUE))
#endif
            {
               /* Data not received but ta needs to be sent. */
               /* MUX TA and send it */
               bldPdu.datReq    =  NULLP;
               bldPdu.reqType   =  EVTTFUTTIIND;
               bldPdu.schdTbSz  =  hqP->tbInfo[i].tbSz;
               bldPdu.ta        =  hqP->tbInfo[i].schdTa;
#ifdef LTE_ADV
               bldPdu.sCellActCe= hqP->tbInfo[i].sCellActCe;
#endif
               /* changes for CR timer implementation*/
               bldPdu.contResId =  hqP->tbInfo[i].contResId;
               if (ROK != rgMUXBldPdu(inst,&bldPdu, &(hqP->tbInfo[i].tb), err))  
               {
                  RETVALUE(RFAILED);
               }
            }
            else   
            {
#ifdef LTEMAC_RGU_PAD
               /* Data not received from RLC. Padding at MAC */
               bldPdu.datReq    =  NULLP;
               bldPdu.reqType   =  EVTTFUTTIIND;
               bldPdu.schdTbSz  =  hqP->tbInfo[i].tbSz;
               bldPdu.ta        =  hqP->tbInfo[i].schdTa;
#ifdef LTE_ADV
               bldPdu.sCellActCe= hqP->tbInfo[i].sCellActCe;
#endif
               bldPdu.ta.val    =  0;
               bldPdu.contResId =  NULLP;

               if (ROK != rgMUXBldPdu(inst,&bldPdu, &(hqP->tbInfo[i].tb), err))  
               {
                  RETVALUE(RFAILED);
               }
#else
               /*Padding is not done so data for this UE will not be
                 included.*/
               dataAvlblUe = FALSE;
#endif
            }
         }
         else
         {
         }
      }
   }

   /*If Data/Padding is not available for UE, then we can not include
     any Data for this UE in TFU Data Request.*/
   if(!dataAvlblUe)
   {
      /*Free up the HARQ process for this allocation.*/
      /* Release First TB, as this would be anyway there*/
      rgDHMRlsHqProcTB(cellCb, hqP, 1);
      if(2 == hqP->numOfTBs)
      {
         rgDHMRlsHqProcTB(cellCb, hqP, 2);
      }
      
      RETVALUE(ROK);
   }

   if (rgGetEventMem(inst,(Ptr *)&datReq, sizeof(TfuDatReqPduInfo),
            &(datInfo->memCp)) != ROK)
   {
      RETVALUE(RFAILED);
   }
   /* Fill the TFU Dat Req with information from Harq Proc */
  
   rgDHMBldTfuDatReq(cellCb, dlSf, hqP, datReq);

   /* MS_WORKAROUND for ccpu00122894 */
   for(i=0;i< RG_MAX_TB_PER_UE;i++)
   {
      if (hqP->tbInfo[i].sf == dlSf)
      {
         cmLListDelFrm(&dlSf->tbs, &hqP->tbInfo[i].sfLnk);
         hqP->tbInfo[i].sfLnk.node = NULLP;
      }
      hqP->tbInfo[i].sf = NULLP;
   }
   cmLListAdd2Tail(&datInfo->pdus, &(datReq->lnk));
   datReq->lnk.node = (PTR)datReq;

   RETVALUE(ROK);
}  /* rgDHMSndDatReq */

/**
 * @brief Function to handle RGU datReq received from ROM
 *
 * @details
 *
 *     Function : rgDHMHndlDedDatReq
 *     
 *     This function shall act on the datReq received on RGU. It shall 
 *     store the data IDs for all the logical channels and get the MAC 
 *     PDU built.
 *     
 *           
 *  @param[in]  Inst        inst
 *  @param[in]  RgDlHqProcCb   *hqProc 
 *  @param[in]  RgRguDedDatReq *datReq
 *  @param[out] RgErrInfo      *err
 *  @return     S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgDHMHndlDedDatReq
(
Inst           inst,
RgDlHqProcCb   *hqProc,
RgRguDDatReqPerUe *datReq,
RgErrInfo      *err
)
#else
PUBLIC S16 rgDHMHndlDedDatReq(inst,hqProc, datReq, err)
Inst           inst;
RgDlHqProcCb   *hqProc;
RgRguDDatReqPerUe *datReq;
RgErrInfo      *err;
#endif
{
   U8             i;
   U8             j;
   RgBldPduInfo   bldPdu;
   U8             tbIndex;
#ifdef L2_OPTMZ
   RgTfuDatReqTbInfo     *tb;
#endif

   TRC2(rgDHMHndlDedDatReq);

   tbIndex = (U8)(datReq->transId & 0x03);
   /* Accept all the data requests even if delayed in case nothing
    * has been sent earlier on the harq proc.
    */
   if((datReq->nmbOfTbs > RG_MAX_TB_PER_UE) ||
         (tbIndex == 0))
   {
      /* release corresponding TBs from SF tbs List */
      for(j=0;j<datReq->nmbOfTbs;j++)
      {
         if (!(tbIndex & (j+1)))
         {
            j++;
         } 
         rgDHMRlsHqProcTB(rgCb[inst].cell, hqProc, (U8)(j+1));
      }
      RETVALUE(RFAILED);
   }

   for(i=0;i<datReq->nmbOfTbs;i++)
   {
      /* tbIndex 01 corresponds to presence of 1st TB
       * 10 corresponds 2nd TB
       * 11 corresponds two TBs of UE */
      if (!(tbIndex & (i+1)))
      {
          continue;
      }
      if (hqProc->tbInfo[i].sfLnk.node == NULLP)
      {
         /* release corresponding TBs from SF tbs List */
         for(j=0;j<datReq->nmbOfTbs;j++)
         {
            if (!(tbIndex & (j+1)))
            {
               j++;
            }
            rgDHMRlsHqProcTB(rgCb[inst].cell, hqProc, (U8)(j+1));
         }
         RETVALUE(RFAILED);

      }
#ifndef L2_OPTMZ
      RG_FREE_MSG(hqProc->tbInfo[i].tb);
      /* L2 optimization for mUe/Tti: Pre-allocated mBuf pointers(macHdr, 
       * macCes and MacPad) of harq TB need to be reset to db_base
       */
#else
      tb = &hqProc->tbInfo[i].tb;
  //  printf("rgDHMHndlDedDatReq: RG_FREE_TB");
      RG_FREE_TB(tb);
#endif
//printf("Sending from 2 %d \n", datReq->rnti);
      bldPdu.datReq    =  datReq;
      bldPdu.reqType   =  EVTRGUDDATREQ;
      bldPdu.schdTbSz  =  hqProc->tbInfo[i].tbSz;
      bldPdu.tbIndex   =  i+1;
      bldPdu.ta        =  hqProc->tbInfo[i].schdTa;
#ifdef LTE_ADV
      bldPdu.sCellActCe= hqProc->tbInfo[i].sCellActCe;
#endif
      bldPdu.contResId =  NULLP;
#ifdef LTE_L2_MEAS
      /* Store tbId from RLC in DDatRequest */
      hqProc->tbId[i] = datReq->datReqTb[i].tbId;


      hqProc->status[i] =  FALSE;
#endif 
      if(rgMUXBldPdu(inst,&bldPdu, &(hqProc->tbInfo[i].tb), err) != ROK)
      {
         /* release corresponding TBs from SF tbs List */
         for(j=0;j<datReq->nmbOfTbs;j++)
         {
            if (!(tbIndex & (j+1)))
            {
               j++;
            }
            rgDHMRlsHqProcTB(rgCb[inst].cell, hqProc, (U8)(j+1));
         }
         RETVALUE(RFAILED);
      }
   }
   RETVALUE(ROK);
}  /* rgDHMHndlDedDatReq */

/**
 * @brief Function to handle RGU datReq received from ROM
 *
 * @details
 *
 *     Function : rgDHMHndlCmnDatReq
 *     
 *     This function shall act on the datReq received on RGU. It shall 
 *     store the data IDs for all the logical channels and get the MAC 
 *     PDU built.
 *     
 *           
 *  @param[in]  Inst        inst
 *  @param[in]  RgDlHqProcCb   *hqProc 
 *  @param[in]  RgRguCmnDatReq *datReq
 *  @param[out] RgErrInfo      *err
 *  @return     S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgDHMHndlCmnDatReq
(
Inst           inst,
RgDlHqProcCb   *hqProc,
RgRguCmnDatReq *datReq,
RgErrInfo      *err
)
#else
PUBLIC S16 rgDHMHndlCmnDatReq(inst,hqProc, datReq, err)
Inst           inst;
RgDlHqProcCb   *hqProc;
RgRguCmnDatReq *datReq;
RgErrInfo      *err;
#endif
{
   RgUstaDgn      dgn;
   RgBldPduInfo   bldPdu;

   TRC2(rgDHMHndlCmnDatReq)

#ifndef L2_OPTMZ
      if (hqProc->tbInfo[0].tb != NULLP)
#else
      /* If numLch is non zero means HQ Proc is busy*/
      if (hqProc->tbInfo[0].tb.tbPres)
#endif
      {
         /* datReq discarded. Generate an alarm */
         rgFillDgnParams(inst,&dgn, LRG_USTA_DGNVAL_HARQ); 
         rgLMMStaInd(inst,LCM_CATEGORY_PROTOCOL, LCM_EVENT_UI_INV_EVT,
               LRG_CAUSE_HQ_PROC_BUSY, &dgn);
         RETVALUE(RFAILED);
      }

   bldPdu.datReq    =  datReq;
   bldPdu.reqType   =  EVTRGUCDATREQ;
   bldPdu.schdTbSz  =  hqProc->tbInfo[0].tbSz;
   bldPdu.ta        =  hqProc->tbInfo[0].schdTa;
#ifdef LTE_ADV
   bldPdu.sCellActCe= hqProc->tbInfo[0].sCellActCe;
#endif

   bldPdu.contResId  =  hqProc->tbInfo[0].contResId;

   if(rgMUXBldPdu(inst,&bldPdu, &(hqProc->tbInfo[0].tb), err) != ROK)
   {
      RG_FREE_MSG(datReq->pdu);
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}  /* rgDHMHndlCmnDatReq */

/**
 * @brief Function to get consolidate grants and send consolidated grant to RLC
 *
 * @details
 *
 *     Function : rgDHMSndConsolidatedStaInd
 *     
 *     This function shall be invoked by Scheduler to trigger DHM to send a
 *     consolidated status indication of all UE scheduled in a TTI as well as
 *     send consolidated CStaInd for MSG4 and for all common channels(PCCH,
 *     if RGR_SI_SCH is not defined then it includes BCH and BCCH also)
 *     
 *           
 *  @param[in]  RgCellCb       *cell
 *  @param[in]  RgInfUeInfo   *ueInfo,
 *  @param[in]  CmLteTimingInfo timingInfo,
 *  @param[out] RgErrInfo      err
 *  @param[in]  RguCStaIndInfo   *cStaInd
 *  @return     S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgDHMSndConsolidatedStaInd
(
RgCellCb        *cell,
RgInfUeInfo     *ueInfo,
CmLteTimingInfo timingInfo,
RgErrInfo       *err
#ifdef LTE_ADV
,
RgLaaTbReq      **laaCellHqPLst
#endif
)
#else
PUBLIC S16 rgDHMSndConsolidatedStaInd(cell, ueInfo, timingInfo, err)
RgCellCb        *cell;
RgInfUeInfo     *ueInfo;
CmLteTimingInfo timingInfo;
RgErrInfo       *err;
RgLaaTbReq      **laaCellHqPLst;
#endif
{
   SuId            rguDlSuId;
   U8              idx;
   U8              ueIdx;
   U8              lcIdx;
   U8              tbIndex=0,idx1;
   RgDlSf          *dlSf = &cell->subFrms[timingInfo.subframe];
   Inst            inst = cell->macInst - RG_INST_START;
//   Bool            isDStaReqrd = FALSE;
   RgRguDedStaInd  *dStaInd[rgCb[inst].numRguSaps] ;
   RgUpSapCb      *rguDlSap[rgCb[inst].numRguSaps];

   int lchBufSize =0;
   RgUeCb         *ue;
   RgDlHqProcCb   *hqP;
   RgInfUeAlloc   *allocInfo;
   U8             activeSapCnt = 0;
   U8             staIndCnt    = 0;
#ifdef L2_OPTMZ
   RgTfuDatReqTbInfo     *tb;   /* TB to be sent to CL/PHY*/
#endif

   TRC2(rgDHMSndConsolidatedStaInd)
   cmMemset ((U8 *)dStaInd, 0, (sizeof(RgRguDedStaInd *) * rgCb[inst].numRguSaps));
   cmMemset ((U8 *)rguDlSap, 0, (sizeof(RgUpSapCb  *) * rgCb[inst].numRguSaps));

   /* Send StaInd for the scheduled UEs */
   for(ueIdx = 0; ueIdx < ueInfo->numUes; ueIdx++)
   {
      if((ue=rgDBMGetUeCb (cell, ueInfo->allocInfo[ueIdx].rnti)) == NULLP)
      {
         /* Check in RachLst */
         if((ue=rgDBMGetUeCbFromRachLst (cell, 
                     ueInfo->allocInfo[ueIdx].rnti)) == NULLP)
         {
            RLOG_ARG1(L_ERROR,DBG_CELLID,cell->cellId,"CRNTI:%d No ueCb found", 
                      ueInfo->allocInfo[ueIdx].rnti);
            /*Fix: If one UE is not present dont return, look for the next.*/
            continue;
         }
      }


      rgDHMGetHqProcFrmId(ue,ueInfo->allocInfo[ueIdx].hqProcId,&hqP);
      allocInfo = &ueInfo->allocInfo[ueIdx];

      /* Fix : syed Avoid sending data for a RETX
       * if initial TX data processing was unsuccessful */
      if((allocInfo->tbInfo[0].isReTx == TRUE) &&
            (hqP->tbInfo[0].tbSz == 0)) 
      {
         RLOG_ARG2(L_ERROR,DBG_CELLID,cell->cellId,
               "CRNTI:%d RETX hqP(%d) tb(0) for a failed New Tx", 
                  allocInfo->rnti, hqP->procId);        
         continue;
      }
      if((allocInfo->tbInfo[1].isReTx == TRUE) &&
            (hqP->tbInfo[1].tbSz == 0)) 
      {
         RLOG_ARG2(L_ERROR,DBG_CELLID,cell->cellId,
                   "CRNTI:%d RETX hqP(%d) tb(1) for a failed New Tx", 
                  allocInfo->rnti, hqP->procId);        
         continue;
      }

      if(ue->rguDlSap != NULLP)
      {
          rguDlSuId = ue->rguDlSap->sapCfg.suId;
      }else
      {/* UeCb is from rachList */
          rguDlSuId = cell->rguDlSap->sapCfg.suId;
      }


      for(idx=allocInfo->tbStrtIdx;((idx-allocInfo->tbStrtIdx) <\
               allocInfo->nmbOfTBs); idx++)
      {
         RguCStaIndInfo  *cStaInd;
#ifdef TFU_UPGRADE
         /* LTE_ADV_FLAG_REMOVED_START */
         hqP->tbInfo[idx].isEnbSFR = allocInfo->isEnbSFR;
         /* update pA value */
         hqP->tbInfo[idx].pa = allocInfo->pa;
         /* LTE_ADV_FLAG_REMOVED_END */
#endif

         hqP->numOfTBs =  allocInfo->nmbOfTBs;
         hqP->tbInfo[idx].sfLnk.node = (PTR)hqP;
         hqP->tbInfo[idx].sf = dlSf;
         cmLListAdd2Tail(&dlSf->tbs,&hqP->tbInfo[idx].sfLnk);

         /* Changes as part of performance testing*/
         /*   hqP->numOfTBs++;*/
         hqP->tbInfo[idx].doa = allocInfo->doa;
         hqP->tbInfo[idx].txMode = allocInfo->txMode;
         hqP->tbInfo[idx].puschRptUsd = allocInfo->puschRptUsd;
         hqP->tbInfo[idx].puschPmiInfo = allocInfo->puschPmiInfo;
#ifdef LTEMAC_SPS
         hqP->tbInfo[idx].pdcch.rnti = allocInfo->pdcchRnti;
#else
         hqP->tbInfo[idx].pdcch.rnti = allocInfo->rnti;
#endif
         if(allocInfo->tbInfo[idx].isReTx == TRUE)
         {
            hqP->tbInfo[idx].pdcch.dci = allocInfo->dciInfo;
            continue;
         }

         hqP->tbInfo[idx].pdcch.dci = allocInfo->dciInfo;
#ifndef L2_OPTMZ
         RG_FREE_MSG(hqP->tbInfo[idx].tb);
#else
         /* L2 optimization for mUe/Tti: Pre-allocated mBuf pointers(macHdr, 
          * macCes and MacPad) of harq TB need to be reset to db_base
          */
         tb = &(hqP->tbInfo[idx].tb);
         RG_FREE_TB(tb);
#endif
         hqP->tbInfo[idx].timingInfo = timingInfo;
         hqP->tbInfo[idx].tbSz = allocInfo->tbInfo[idx].schdTbSz; 

         hqP->tbInfo[idx].schdTa.pres = allocInfo->tbInfo[idx].ta.pres;
         hqP->tbInfo[idx].schdTa.val  = allocInfo->tbInfo[idx].ta.val;

#ifdef LTE_ADV
         hqP->tbInfo[idx].sCellActCe.pres = allocInfo->tbInfo[idx].sCellActCe.pres;
         hqP->tbInfo[idx].sCellActCe.val  = allocInfo->tbInfo[idx].sCellActCe.val;
#endif

#ifdef LTE_ADV
#if 0
         /*REEMA*/
         if(ROK == rgLaaPushHqPToScellLst(allocInfo,laaCellHqPLst,timingInfo))
         {
            continue;
         }
#endif
#endif
         if (allocInfo->tbInfo[idx].schdDat[0].lcId == RG_CCCH_LCID)        
         {
#ifndef L2_OPTMZ
            RG_FREE_MSG(hqP->tbInfo[idx].tb);
#else
           /* L2 optimization for mUe/Tti: Pre-allocated mBuf pointers(macHdr, 
            * macCes and MacPad) of harq TB need to be reset to db_base
            */
           tb = &(hqP->tbInfo[idx].tb);
           RG_FREE_TB(tb);
#endif
            hqP->tbInfo[0].contResCe  = allocInfo->tbInfo[0].contResCe;
            if(allocInfo->tbInfo[0].contResCe)
            {
               hqP->tbInfo[0].contResId = &ue->contResId;
            }


            if(allocInfo->tbInfo[idx].numSchLch == 0)
            {
               RLOG_ARG2(L_DEBUG,DBG_CELLID,cell->cellId,
                        "UEID:%d MSG4 with only contResId hqP(%d)",
               			allocInfo->rnti,
                     	hqP->procId);
               hqP->tbInfo[idx].numSchLch = 0;
               continue;
            }

            /* Increamenting the tbIndex instead of
               assigning it to constant */
            tbIndex++;


            hqP->tbInfo[idx].numSchLch = 1;
            hqP->tbInfo[idx].schdData[0].lcId = 
               allocInfo->tbInfo[idx].schdDat[0].lcId;
            hqP->tbInfo[idx].schdData[0].schdSz = 
               allocInfo->tbInfo[idx].schdDat[0].numBytes;

           // if(cStaInd == NULLP)
            {
               if ((rgAllocShrablSBuf(inst,(Data**)&cStaInd, sizeof(RguCStaIndInfo))) != ROK)
               {
                  err->errType  = RGERR_DHM_SND_STA_IND;
                  err->errCause = RG_DHM_MEM_ALLOC_FAIL;
                  RETVALUE(RFAILED); 
               }
            }

            idx1 = (hqP->procId << 2) | tbIndex;
            
            cStaInd->cellId    = cell->cellId;
            cStaInd->rnti      = allocInfo->rnti;
            cStaInd->lcId      = cell->dlCcchId;
            cStaInd->transId   = (timingInfo.sfn << 16) | 
                                 (timingInfo.subframe << 8) | idx1;
               /* ADD Changes for Downlink UE Timing Optimization */
#ifdef LTEMAC_DLUE_TMGOPTMZ
            dlSf->remDatReqCnt++;
#endif
            RLOG_ARG3(L_DEBUG,DBG_CELLID,cell->cellId,
		               "RNTI:%d UE:MSG4 grant for CCCH hqP(%d) LCID:%d",
                     allocInfo->rnti, 
                     hqP->procId,
		               cStaInd->lcId);       
            /* Fix : syed Avoid return param for interface prim and
             * proceed for other UEs. For the failed UE, MAC shall
             * do padding. */
            rgUIMSndCmnStaInd(cell->macInst,cell->rguDlSap,cStaInd);
            break;
         }
         else
         {
            tbIndex+=idx+1;
#ifndef L2_OPTMZ
            RG_FREE_MSG(hqP->tbInfo[idx].tb);
#else
            /* L2 optimization for mUe/Tti: Pre-allocated mBuf pointers(macHdr, 
             * macCes and MacPad) of harq TB need to be reset to db_base
             */
            tb = &(hqP->tbInfo[idx].tb);
            //printf("rgDHMSndConsolidatedStaInd: sending grant for dedicated chanel: resting TB rebore");
            RG_FREE_TB(tb);
#endif

            if((NULLP == dStaInd[rguDlSuId]) && (allocInfo->tbInfo[idx].numSchLch))
            {
               if ((rgAllocShrablSBuf (inst,(Data**)&dStaInd[rguDlSuId], sizeof(RguDStaIndInfo))) != ROK)
               {
                  err->errType  = RGERR_DHM_SND_STA_IND;
                  err->errCause = RG_DHM_MEM_ALLOC_FAIL;
                  /* Need to return as memory allocation will fail for other UEs also*/
                  RETVALUE(RFAILED);
               }
               dStaInd[rguDlSuId]->nmbOfUeGrantPerTti = 0;
               rguDlSap[rguDlSuId] = ue->rguDlSap;
               activeSapCnt++;
            }

            for (lcIdx = 0; 
                  lcIdx < allocInfo->tbInfo[idx].numSchLch; lcIdx++)
            {
               hqP->tbInfo[idx].schdData[lcIdx].lcId = 
                  allocInfo->tbInfo[idx].schdDat[lcIdx].lcId;
               if (hqP->tbInfo[idx].schdData[lcIdx].lcId == 0)
               {
                  RLOG_ARG2(L_ERROR,DBG_CELLID,cell->cellId, 
                        "CCCH grant in DStaInd for LCID:%d CRNTI:%d",
                        hqP->tbInfo[idx].schdData[lcIdx].lcId,allocInfo->rnti);
               }
               hqP->tbInfo[idx].schdData[lcIdx].schdSz = 
                  allocInfo->tbInfo[idx].schdDat[lcIdx].numBytes;
               if(dStaInd[rguDlSuId])
               {
                  dStaInd[rguDlSuId]->staInd[dStaInd[rguDlSuId]->nmbOfUeGrantPerTti].staIndTb[idx].\
                  lchStaInd[lcIdx].lcId = allocInfo->tbInfo[idx].\
                  schdDat[lcIdx].lcId;
                  dStaInd[rguDlSuId]->staInd[dStaInd[rguDlSuId]->nmbOfUeGrantPerTti].staIndTb[idx].\
                  lchStaInd[lcIdx].totBufSize = allocInfo->tbInfo[idx].\
                  schdDat[lcIdx].numBytes;
               }

               lchBufSize+=allocInfo->tbInfo[idx].schdDat[lcIdx].numBytes;
            }
            hqP->tbInfo[idx].numSchLch = 
               allocInfo->tbInfo[idx].numSchLch;
            if(dStaInd[rguDlSuId])
            {
               dStaInd[rguDlSuId]->staInd[dStaInd[rguDlSuId]->nmbOfUeGrantPerTti].staIndTb[idx].nmbLch =
                  allocInfo->tbInfo[idx].numSchLch;
#ifdef LTE_L2_MEAS
               dStaInd[rguDlSuId]->staInd[dStaInd[rguDlSuId]->nmbOfUeGrantPerTti].staIndTb[idx].tbId =
                  hqP->tbId[idx]; 
#endif
            }
            lchBufSize=0;
         }
      }
      //if((dStaInd) && (tbIndex) && (isDStaReqrd == TRUE))
      if((dStaInd[rguDlSuId]) && (tbIndex))
      {
         idx1 = (hqP->procId << 2) | tbIndex;
         /* Create RguDStaInd struct and send to UIM */
         dStaInd[rguDlSuId]->staInd[dStaInd[rguDlSuId]->nmbOfUeGrantPerTti].rnti    = allocInfo->rnti;
         /*
            dStaInd->transId = (hqP->timingInfo.sfn << 16) | 
            (hqP->timingInfo.subframe << 8) | hqP->procId;
          */
         dStaInd[rguDlSuId]->staInd[dStaInd[rguDlSuId]->nmbOfUeGrantPerTti].transId = (timingInfo.sfn << 16) | 
            (timingInfo.subframe << 8) | idx1;
         dStaInd[rguDlSuId]->staInd[dStaInd[rguDlSuId]->nmbOfUeGrantPerTti].nmbOfTbs = hqP->numOfTBs;
#ifdef LTE_ADV
         dStaInd[rguDlSuId]->staInd[dStaInd[rguDlSuId]->nmbOfUeGrantPerTti].fillCtrlPdu = allocInfo->fillCtrlPdu;
#endif        
         /*increment num of UE as staInd is prepared for it */
         dStaInd[rguDlSuId]->nmbOfUeGrantPerTti++;
         /* ADD Changes for Downlink UE Timing Optimization */
#ifdef LTEMAC_DLUE_TMGOPTMZ
         dlSf->remDatReqCnt++;
#endif
      }
      //isDStaReqrd = FALSE;
      tbIndex = 0;
   }

   for(idx = 0; idx < rgCb[inst].numRguSaps ; idx++)
   {
      if(dStaInd[idx] != NULLP)
      {
         dStaInd[idx]->cellId  = cell->cellId;
         /* Fix : syed Avoid return param for interface prim and
          * proceed for other UEs. For the failed UE, MAC shall
          * do padding. */
         /* printf("\n Sending DedStaInd...\n"); */
         rgUIMSndDedStaInd(inst,rguDlSap[idx],dStaInd[idx]);
   
         staIndCnt++;
         if(staIndCnt == activeSapCnt)
            break;/* all valid staind are considered */
      }

   }
   RETVALUE(ROK);
}  /* rgDHMSndConsolidatedStaInd */


/**
 * @brief Function to handle building the TFU Data Request
 *
 * @details
 *
 *     Function : rgDHMBldTfuDatReq
 *     
 *     This function builds the TFU Data Request with the details 
 *     present in HARQ Process.
 *           
 *  @param[in]  RgDlHqProcCb     *hqP 
 *  @param[out] TfuDatReqPduInfo  *datReq 
 *  @return     Void
 *              None 
 **/
#ifdef ANSI
PRIVATE Void rgDHMBldTfuDatReq
(
RgCellCb           *cellCb,
RgDlSf             *dlSf,
RgDlHqProcCb       *hqP,
RgTfuDatReqPduInfo *datReq
)
#else
PRIVATE Void rgDHMBldTfuDatReq(cellCb, dlSf, hqP, datReq)
RgCellCb           *cellCb;
RgDlSf             *dlSf;
RgDlHqProcCb       *hqP;
RgTfuDatReqPduInfo *datReq;
#endif
{

#ifndef BRDCM
   Inst inst;
#endif

   U8 i;

#ifdef L2_OPTMZ
   U32 lchIdx, pduIdx;
#endif
   TRC2(rgDHMBldTfuDatReq)
 
   datReq->nmbOfTBs = 0;
#ifndef BRDCM
   inst = cellCb->macInst - RG_INST_START;
#endif
   /*MS_WORKAROUND  for ccpu00123904*/
   datReq->isTApres = FALSE;
#ifdef TFU_ALLOC_EVENT_NO_INIT
#ifndef L2_OPTMZ   
   datReq->mBuf[0] = 0;
   datReq->mBuf[1] = 0;
#endif    
#endif
 
   for(i=0;i<RG_MAX_TB_PER_UE;i++)
   {
#ifndef L2_OPTMZ
      if ((hqP->tbInfo[i].sf == dlSf) && (hqP->tbInfo[i].tb != NULLP))
#else
      if ((hqP->tbInfo[i].sf == dlSf) && RgUtlIsTbMuxed(&(hqP->tbInfo[i].tb)))
#endif
      {

         datReq->rnti           =  hqP->tbInfo[i].pdcch.rnti;
         datReq->dciInfo        =  hqP->tbInfo[i].pdcch.dci;
         datReq->doa            =  hqP->tbInfo[i].doa;
         datReq->transMode      =  hqP->tbInfo[i].txMode;
         datReq->puschRptUsd    =  hqP->tbInfo[i].puschRptUsd;
         datReq->puschPmiInfo   =  hqP->tbInfo[i].puschPmiInfo;
         /*MS_WORKAROUND  for ccpu00123904*/
         if (hqP->tbInfo[i].schdTa.pres)
         {
            datReq->isTApres       =  TRUE; 
         }
#ifdef   TFU_UPGRADE
         /* update pA value */
         datReq->pa             =  hqP->tbInfo[i].pa;
#endif
         /* LTE_ADV_FLAG_REMOVED_START */
         datReq->isEnbSFR       =  hqP->tbInfo[i].isEnbSFR;
         /* LTE_ADV_FLAG_REMOVED_END */
#ifndef L2_OPTMZ
#if (!(defined TENB_ACC) && !(defined LTE_PAL_ENB))  /* ABHI */ /* This is only temp fix. It needs to be removed
                                after rebasing to MAC CCB */
#ifdef BRDCM
         datReq->mBuf[i] = hqP->tbInfo[i].tb;
#else
         /* Intel Tdd- Commenting out the Optimization for direct Access of 
          * mBuf Index */
         /*Proper clean-up needed as this needs long stability tests
          * in all SoCs*/
#if defined(TENB_T2K3K_SPECIFIC_CHANGES) && defined(LTE_TDD)
EXTERN S16 SIncMsgRef(Buffer *srcBuf,Region dstRegion, Pool dstPool,Buffer **dstBuf);
         SIncMsgRef(hqP->tbInfo[i].tb, RG_GET_MEM_REGION(rgCb[inst]),
               RG_GET_MEM_POOL(rgCb[inst]), &datReq->mBuf[i]); 
#else
         datReq->mBuf[i] = hqP->tbInfo[i].tb;
#endif
#endif/*BRDCM*/
#else
         SIncMsgRef(hqP->tbInfo[i].tb, RG_GET_MEM_REGION(rgCb[inst]),
               RG_GET_MEM_POOL(rgCb[inst]), &datReq->mBuf[i]);
#endif
         {
            MsgLen   dbgBufLen;
            if(SFndLenMsg(datReq->mBuf[i], &dbgBufLen))
            {
               if(dbgBufLen == 0)
               {              
                  RLOG_ARG4(L_ERROR,DBG_CELLID,cellCb->cellId,
			                  "RNTI:%d SFN:%d subframe:%d tbIdx:%d Sdu Length 0 ",
                    	      datReq->rnti,
            			      hqP->tbInfo[i].timingInfo.sfn,
			                  hqP->tbInfo[i].timingInfo.subframe,i);
                  RLOG_ARG3(L_ERROR,DBG_CELLID,cellCb->cellId,
                   	      "taPres [%d] numOfTbs [%d] format[%d]",
                   	      datReq->isTApres, 
                           hqP->numOfTBs, 
                           datReq->dciInfo.format);  
               }              
            }            
         }
#else
         /* L2 optimization for mUe/Tti: Removing SIncMsgRef to avoid additional
          * mBuf allocation. MAC header, MAC Ces, MAC PDU per LCH per TB Per UE
          * and MAC padding Mbufs are being sent to CL. Populating these Ptrs
          * From TB Info to TfuDatReq
          */
         datReq->tbInfo[i].tbPres =  TRUE;
         datReq->tbInfo[i].tbSize =  hqP->tbInfo[i].tbSz;
         datReq->tbInfo[i].macHdr =  hqP->tbInfo[i].tb.macHdr;
         datReq->tbInfo[i].macCes =  hqP->tbInfo[i].tb.macCes;
         datReq->tbInfo[i].numLch =  hqP->tbInfo[i].tb.numLch;
#if 0 
#else
//printf("\n MacHdr in TfuBldReq");
//SPrntMsg(datReq->tbInfo[i].macHdr, 0, 0);
#endif
         for(lchIdx = 0; lchIdx < hqP->tbInfo[i].tb.numLch; lchIdx++)
         {
            datReq->tbInfo[i].lchInfo[lchIdx].numPdu = hqP->tbInfo[i].tb.\
                                                       lchInfo[lchIdx].numPdu;
            for(pduIdx = 0; pduIdx < hqP->tbInfo[i].tb.lchInfo[lchIdx].numPdu;\
                  pduIdx++)
            {
               datReq->tbInfo[i].lchInfo[lchIdx].mBuf[pduIdx] =
                  hqP->tbInfo[i].tb.lchInfo[lchIdx].mBuf[pduIdx];
              // printf("\nTfuDatReq:padSize=%ld rnti=%d  numLch=%ld numPdu=%ld tbSz=%d, tbPres=%d\n",hqP->tbInfo[i].tb.padSize,datReq->rnti, datReq->tbInfo[i].numLch, datReq->tbInfo[i].lchInfo[lchIdx].numPdu, datReq->tbInfo[i].tbSize,  datReq->tbInfo[i].tbPres);
            }
         }
        // datReq->tbInfo[i].macPad  =  hqP->tbInfo[i].tb.macPad;
         datReq->tbInfo[i].padSize =  hqP->tbInfo[i].tb.padSize;
        // prc_trace_format_string(0x40,3,"TfuDatReq:RNTI=%d TbIdx=%d TbSize=%d PdSz=(%d) macHdraddr: (%p) macCEAddr: (%p) noLch=(%d)",datReq->rnti, i,
          //     hqP->tbInfo[i].tbSz, datReq->tbInfo[i].padSize, datReq->tbInfo[i].macHdr, datReq->tbInfo[i].macCes, datReq->tbInfo[i].numLch);

#endif
         datReq->nmbOfTBs++;
      }
   }
   RETVOID;
}  /* rgDHMBldTfuDatReq */


#ifdef L2_OPTMZ
/**
 * @brief This function releases a HARQ process
 *
 * @details
 *
 *     Function: rgDHMFreeHqProcTB
 *     Purpose:  This function returns a HARQ process to HARQ Entity 
 *               in the DL direction.
 *     
 *               1. Add the HARQ process to the free queue.
 *     Invoked by: scheduler and HARQ processing
 *     
 *  @param[in]  RgDlHqProc    *hqP
 *  @return  Void      
 *
 **/
#ifdef ANSI
PUBLIC S16 rgDHMFreeHqProcTB
(
RgDlHqProcCb         *hqP,
U8                   tbIndex
)
#else
PUBLIC S16 rgDHMFreeHqProcTB(hqP, tbIndex)
RgDlHqProcCb         *hqP;
U8                   tbIndex;
#endif
{
   RgTfuDatReqTbInfo     *tb;   /* TB to be sent to CL/PHY*/

   TRC2(rgDHMFreeHqProcTB)

   if((tbIndex > RG_MAX_TB_PER_UE) ||
      (tbIndex == 0))
   {
      RETVALUE(RFAILED);
   }

   tb = &(hqP->tbInfo[tbIndex-1].tb);
   RG_FREE_MSG(tb->macHdr);
   RG_FREE_MSG(tb->macCes);

   if (hqP->tbInfo[tbIndex-1].sfLnk.node != NULLP)
   {
      cmLListDelFrm(&hqP->tbInfo[tbIndex-1].sf->tbs,
                    &hqP->tbInfo[tbIndex-1].sfLnk);
      hqP->tbInfo[tbIndex-1].sfLnk.node  = (PTR)NULLP;
   }
   RETVALUE(ROK);
}
#endif


/**
 * @brief Handler for freeing up the saved HqP and TBs
 *
 * @details
 *
 *     Function : rgDHMFreeSavedHqP
 *     
 *     This function shall free up the saved HqP and TBs
 *           
 *  @param[in]  Inst        inst
 *  @param[in]  RgDlHqEnt     *hqE 
 *
 *  @return     None.
 *
 **/
#ifdef ANSI
PUBLIC Void rgDHMFreeSavedHqP
(
Inst               inst,
RgDlHqEnt          *hqE,
U8                 procId
)
#else
PUBLIC Void rgDHMFreeSavedHqP(inst,hqE,procId)
Inst               inst;
RgDlHqEnt          *hqE;
U8                 procId;
#endif
{
   CmLList      *node;
   RgDlSavedHqProcInfo *hqPNode;

#ifdef L2_OPTMZ
    RgTfuDatReqTbInfo     *tb;   /* TB to be sent to CL/PHY*/
#endif
   TRC2(rgDHMFreeSavedHqP)

   node = hqE->savedProcLst[procId].first;
   while(node)
   {
      hqPNode = (RgDlSavedHqProcInfo *)node;
      node = node->next;

      cmLListDelFrm(&hqE->savedProcLst[procId],
            &hqPNode->savedHqPLnk);
      /* Release the TB */ 
#ifndef L2_OPTMZ
      if ( hqPNode->tb[0])
      {
         rgDHMHdlBufFree(inst , &hqPNode->tb[0]);
      }
      if ( hqPNode->tb[1])
      {
         rgDHMHdlBufFree(inst , &hqPNode->tb[1]);
      }
#else
      tb = &(hqPNode->tb[0]);
      if (tb->tbPres == TRUE)
      {
         RG_FREE_TB(tb);
      }
      tb = &(hqPNode->tb[1]);
      if (tb->tbPres == TRUE)
      {
         RG_FREE_TB(tb);
      }
#endif
      rgFreeSBuf(inst,(Data **)&(hqPNode),sizeof(RgDlSavedHqProcInfo));

   }

   RETVOID;

}  /* rgDHMFreeSavedHqP */


/**
 * @brief Handler for freeing up the harq related information from ueCb
 *
 * @details
 *
 *     Function : rgDHMFreeUe
 *     
 *     This function shall free up the HARQ specific information from ueCb.
 *           
 *  @param[in]  Inst        inst
 *  @param[in]  RgDlHqEnt     *hqE 
 *
 *  @return     None.
 *
 **/
#ifdef ANSI
PUBLIC Void rgDHMFreeUe
(
Inst               inst,
RgDlHqEnt          *hqE
)
#else
PUBLIC Void rgDHMFreeUe(inst,hqE)
Inst               inst;
RgDlHqEnt          *hqE;
#endif
{
   U8             i;
   TRC2(rgDHMFreeUe)

   if(hqE->procs)
   {
      /* Free all the memory associated with HARQ */
      for (i=0; i < hqE->numHqProcs; i++)
      {
#ifndef L2_OPTMZ
         rgDHMRlsHqProcTB(rgCb[inst].cell, hqE->procs[i], 1);
         rgDHMRlsHqProcTB(rgCb[inst].cell, hqE->procs[i], 2);
#else
         rgDHMFreeHqProcTB(hqE->procs[i], 1);
         rgDHMFreeHqProcTB(hqE->procs[i], 2);
#endif
         
         rgFreeSBuf(inst,(Data **)&(hqE->procs[i]), sizeof(RgDlHqProcCb));

         rgDHMFreeSavedHqP(inst,hqE,i);
      }

      /*ccpu00117052 - MOD - Passing double pointer for proper NULLP
                            assignment */
   }

   RETVOID;

}  /* rgDHMFreeUe */
#ifdef LTE_ADV
/**
 * @brief Function for handling RaResp request received from scheduler to MAC
 *
 * @details
 *
 *     Function : RgSchMacRstHqEntReq
 *     
 *     This function shall be invoked whenever a sec cell of an ue
 *     is deactivated. MAC needs to reset the harqentity associated 
 *     with the deactivated scell of the ue
 *     
 *           
 *  @param[in] Pst             *pst
 *  @param[in] RgInfResetHqEnt *hqEntInfo
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 RgSchMacRstHqEntReq
(
Pst*                 pst,    
RgInfResetHqEnt*     hqEntInfo
)
#else
PUBLIC S16 RgSchMacRstHqEntReq(pst, hqEntInfo)
Pst*                 pst;
RgInfResetHqEnt*     hqEntInfo;
#endif
{
   Inst      inst;
   RgCellCb  *cell;
   RgUeCb    *ue;

   inst = pst->dstInst - RG_INST_START;

   if (((cell = rgCb[inst].cell) == NULLP) ||
       (rgCb[inst].cell->cellId != hqEntInfo->cellId))
   {
      RGDBGERRNEW(inst,(rgPBuf(inst), "For user [%d]Cell does not exist %d\n",
                hqEntInfo->crnti,hqEntInfo->cellId));
      RETVALUE(RFAILED);
   }

   if ((ue = rgDBMGetUeCb(cell, hqEntInfo->crnti)) == NULLP)
   {
      RGDBGERRNEW(inst,(rgPBuf(inst), "[%d]UE does not exist for this hqEntInfo\n",
                       hqEntInfo->crnti));
      RETVALUE(RFAILED);
   }

   rgDHMUeReset(cell, &ue->dl.hqEnt);

   RETVALUE(ROK);
}
#endif

/**
 * @brief Function for handling RaResp request received from scheduler to MAC
 *
 * @details
 *
 *     Function : RgSchMacRlsHqReq
 *     
 *     This function shall be invoked whenever scheduler is done with the
 *     allocations of random access responses for a subframe.
 *     This shall invoke RAM to create ueCbs for all the rapIds allocated and 
 *     shall invoke MUX to create RAR PDUs for raRntis allocated.
 *     
 *           
 *  @param[in] CmLteCellId         cellId,
 *  @param[in] CmLteTimingInfo     timingInfo,
 *  @param[in] RaRespInfo          *rarInfo
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 RgSchMacRlsHqReq
(
Pst                 *pst,
RgInfRlsHqInfo      *rlshqUeInfo
)
#else
PUBLIC S16 RgSchMacRlsHqReq(pst, rlshqUeInfo)
Pst                 *pst;
RgInfRlsHqInfo      *rlshqUeInfo;
#endif
{
   Inst           inst;
   RgCellCb       *cell = NULLP;
   RgUeCb         *ue;
   RgDlHqProcCb   *hqP;
   U8             idx1,idx2;
#ifdef LTE_L2_MEAS
   U8                tbId;
   RguHarqStatusInd  hqStaInd;
   Bool              isValidTbId = FALSE;
#endif
   U32        startTime=0;
   
   TRC2(RgSchMacRlsHqReq)

   RG_IS_INST_VALID(pst->dstInst);
   inst = pst->dstInst - RG_INST_START;
   cell  = rgCb[inst].cell;
   /*starting Task*/
   SStartTask(&startTime, PID_MAC_AM_HARQ_RLS);

   if(NULLP == rlshqUeInfo)
   {
      RETVALUE(RFAILED);
   }

   if((cell  == NULLP)
      ||( cell->cellId != rlshqUeInfo->cellId))
   {
       
      RLOG_ARG0(L_ERROR,DBG_CELLID,rlshqUeInfo->cellId,
                "No cellCb found with cellId");
      RETVALUE(RFAILED);
   }

   if(NULLP == rlshqUeInfo->ueHqInfo)
   {
      RETVALUE(RFAILED);
   }

   for(idx1 = 0; idx1 < rlshqUeInfo->numUes; idx1++)
   {
      if((ue=rgDBMGetUeCb (cell, rlshqUeInfo->ueHqInfo[idx1].rnti)) == NULLP)
      {
         /* Check in RachLst */
         if((ue=rgDBMGetUeCbFromRachLst (cell, 
                     rlshqUeInfo->ueHqInfo[idx1].rnti)) == NULLP)
         {
            RLOG_ARG1(L_ERROR,DBG_CELLID,rlshqUeInfo->cellId, "CRNTI:%d No ueCb found",
                     rlshqUeInfo->ueHqInfo[idx1].rnti);
            continue;
         }
      }

      
      RgSchMacHndlRelReq(cell, ue, &rlshqUeInfo->ueHqInfo[idx1]);

      if (RGINF_RLS_HQ_DEL_TB == rlshqUeInfo->ueHqInfo[idx1].rlsOperationType)
      {
         /* If REQ is to DEL the saved TBs no need to free the HqP as it's already
            freed up earlier */
         continue;
      }

      rgDHMGetHqProcFrmId(ue,rlshqUeInfo->ueHqInfo[idx1].hqProcId,&hqP);
      if(rlshqUeInfo->ueHqInfo[idx1].status[0] != TRUE)
      {
         rgCb[inst].genSts.numHarqFail++;
      }
     
#ifdef LTE_L2_MEAS
      hqStaInd.cellId = cell->cellId;
      hqStaInd.ueId = rlshqUeInfo->ueHqInfo[idx1].rnti;
      hqStaInd.numTbs = rlshqUeInfo->ueHqInfo[idx1].numOfTBs;
#endif

      for(idx2=0; idx2 < rlshqUeInfo->ueHqInfo[idx1].numOfTBs; idx2++)
      {
#ifdef LTE_L2_MEAS
         /* Fill the hq sta Ind stucture. Need to send the Status Ind for only
          those TBID's reported by Scheduler*/
            tbId = rlshqUeInfo->ueHqInfo[idx1].tbId[idx2];
            if (hqP->tbId[tbId-1] != RGU_INVALID_TBID)
            {
            /* Fill the correct Sn Map corresponding to the TBID */
            hqStaInd.tbId[idx2] = hqP->tbId[tbId-1];
            hqStaInd.status[idx2] = rlshqUeInfo->ueHqInfo[idx1].status[idx2];
               isValidTbId = TRUE;
            }
#endif
         if(rgDHMRlsHqProcTB(cell, hqP, 
               rlshqUeInfo->ueHqInfo[idx1].tbId[idx2]) != ROK)
         {
            RLOG_ARG1(L_ERROR,DBG_CELLID,rlshqUeInfo->cellId,
                  "CRNTI:%d Failure in releasing hq TB",
                  rlshqUeInfo->ueHqInfo[idx1].rnti);
            continue;
         }
      }

#ifdef LTE_L2_MEAS

         if (isValidTbId)
         {
            if(ue->rguDlSap)
            {
               RgUiRguHqStaInd(&(ue->rguDlSap->sapCfg.sapPst),
                     ue->rguDlSap->sapCfg.suId,
                     &hqStaInd);
            }
            else
            {/* Ue is from rach list*/
               RgUiRguHqStaInd(&(cell->rguDlSap->sapCfg.sapPst),
                     cell->rguDlSap->sapCfg.suId,
                     &hqStaInd);
            }
         }
#endif
   } /* end of ues loop */

   /*starting Task*/
   SStopTask(startTime,PID_MAC_AM_HARQ_RLS);

   RETVALUE(ROK);
} /* end of RgSchMacRlsHqReq */

/**
 * @brief Function for handling rlsOperationType of HQ REL REQ from SCH
 *
 * @details
 *
 *     Function : RgSchMacHndlRelReq
 *     
 *     This function shall handle Hq Release Req based on release operation
 *     type
 *     
 *     0x00 RGINF_RLS_HQ_NO_ACTION - Free Hq Procs and TBs
 *     0x01 RGINF_RLS_HQ_SAVE_TB - Free Hq Proc but save the TBs
 *     0x02 RGINF_RLS_HQ_DEL_TB - Del already saved TBs 
 *           
 *  @param[in] cell
 *  @param[in] ue
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 RgSchMacHndlRelReq
(
 RgCellCb       *cell,
 RgUeCb         *ue,
 RgInfUeHqInfo  *ueHqInfo
)
#else
PUBLIC S16 RgSchMacHndlRelReq(cell, ue, rlshqUeInfo)
 RgCellCb       *cell;
 RgUeCb         *ue;
 RgInfUeHqInfo *ueHqInfo;
#endif
{
   U8           idx;
   U8           tbId;
   CmLList      *node;
   RgDlSavedHqProcInfo *hqPNode = NULLP;
   U8             procId;
   U16            saveId;
   Inst             inst = cell->macInst - RG_INST_START;
#ifdef L2_OPTMZ
   RgTfuDatReqTbInfo  *tb;   /* TB to be sent to CL/PHY*/
#endif

   TRC2(RgSchMacHndlRelReq)

   procId = ueHqInfo->hqProcId;
   saveId = ueHqInfo->saveId;

   switch (ueHqInfo->rlsOperationType)
   {
      case RGINF_RLS_HQ_SAVE_TB:
      {
         RgDlHqProcCb   *hqP;
         
         rgDHMGetHqProcFrmId(ue, procId, &hqP);

         /* Alloc Node */
         if (rgAllocSBuf(inst,(Data **)&(hqPNode),
                  sizeof(RgDlSavedHqProcInfo)) != ROK)
         {
            RETVALUE(RFAILED);
         }

         hqPNode->saveId = saveId;
         hqPNode->tb[0] = hqP->tbInfo[0].tb;
         hqPNode->tb[1] = hqP->tbInfo[1].tb;

#ifdef L2_OPTMZ
         hqP->tbInfo[0].tb.tbPres = FALSE;
#else
         hqP->tbInfo[0].tb = NULLP;
#endif

         hqPNode->savedHqPLnk.node = (PTR)hqPNode;
         cmLListAdd2Tail(&ue->dl.hqEnt.savedProcLst[procId],
               &hqPNode->savedHqPLnk);
         break;
      }
      case RGINF_RLS_HQ_DEL_TB:
      {
         node = ue->dl.hqEnt.savedProcLst[procId].first;

         while(node)
         {
            hqPNode = (RgDlSavedHqProcInfo *)node;
            node = node->next;

            if (saveId != hqPNode->saveId)
            {
               continue;
            }
           

            for (idx = 0; idx < ueHqInfo->numOfTBs; idx++)
            {
               tbId = ueHqInfo->tbId[idx];
               /* Release the TB */ 
#ifndef L2_OPTMZ
               rgDHMHdlBufFree(cell->macInst - RG_INST_START,
                     &hqPNode->tb[tbId]);
               hqPNode->tb[tbId] = NULLP;
#else
               tb = &(hqPNode->tb[tbId]);
               RG_FREE_TB(tb);
#endif
            }
#ifndef L2_OPTMZ
            if (! hqPNode->tb[0] && ! hqPNode->tb[1])
#else
               if ((FALSE ==  hqPNode->tb[0].tbPres) && 
                     (FALSE ==  hqPNode->tb[1].tbPres))
#endif
            {
               cmLListDelFrm(&ue->dl.hqEnt.savedProcLst[procId],
                     &hqPNode->savedHqPLnk);
               /* Free HqP Node */
               rgFreeSBuf(inst,(Data **)&(hqPNode),
                     sizeof(RgDlSavedHqProcInfo));
            }
         }
         break;
      }
      case RGINF_RLS_HQ_NO_ACTION:
      default:
      break;
   }

   RETVALUE(ROK);
} /* end of RgSchMacHndlRelReq */


/**********************************************************************
 
         End of file:     gk_dhm.c@@/main/3 - Sat Jul 30 02:21:26 2011
 
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
/main/1      ---     ps              1. Initial Release.
/main/2      ---     ps              1. LTE MAC 2.1 release
             rg001.201 sm 1. Removed extra comments. 
             rg003.201 sm 1. changes for CR ccpu00108099. 
             rg004.201 sm 1. ABR fixed
             rg005.201 sm 1. Changes for optimization.
             rg007.201   ap  1. Added support for MIMO
             rg008.201 sd  1. Removed dependncy on MIMO compile-time flag
             rg009.201 rsharon 1.[ccpu00112372] Changes for CR timer implementation.
/main/3      ---        gvj  1. Updated for LTE MAC Rel 3.1         
      rg001.301   nudupi   1. Changes for the TB indexing issue.
                           2. Added the changes corresponding to the CR ccpu00119023
      rg002.301  asehgal   1. ccpu00120298 ADD sf is reset to NULLP
$SID$        ---    rt     1. LTE MAC 4.1 release
*********************************************************************91*/
