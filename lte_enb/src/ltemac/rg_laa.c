



/************************************************************************

     Name:     LTE-MAC layer

     Type:     C source file

     Desc:     

     File:     

     Sid:      

     Prg:           

**********************************************************************/

/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_lte.h"       /* common tokens */
#include "rgu.h"           /* RGU defines */
#include "tfu.h"           /* RGU defines */
#include "lrg.h"           /* layer management defines for LTE-MAC */
#include "crg.h"           /* layer management defines for LTE-MAC */
#include "rg_sch_inf.h"           /* layer management defines for LTE-MAC */
#include "rg.h"            /* defines and macros for MAC */
#include "rg_env.h"            /* defines and macros for MAC */
#include "rg_err.h"            /* defines and macros for MAC */
#include "ss_queue.h"


/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"       /* common tokens */
#include "rgu.x"           /* RGU types */
#include "tfu.x"           /* RGU types */
#include "lrg.x"           /* layer management typedefs for MAC */
#include "crg.x"           /* CRG interface typedefs */
#include "rg_sch_inf.x"    /* SCH interface typedefs */
#include "rg_prg.x"        /* PRG interface typedefs */
#include "rgm.x"           /* layer management typedefs for MAC */
#include "rgm.h"           /* layer management typedefs for MAC */
#include "rg.x"            /* typedefs for MAC */
#include "ss_queue.x"
#include "ss_task.x"
#include "ss_msg.x"    

#ifdef LTE_ADV
static const char* RLOG_MODULE_NAME="MAC";
static int RLOG_MODULE_ID=4096;
static int RLOG_FILE_ID=174;

/**
 * @brief Function for sending TB request from PMAC to SMAC
 *
 * @details
 *
 *     Function : rgLaaChkAndReqTbs 
 *     
 *     This function shall be invoked by PMAC to trigger TB request towards all
 *     SMACs
 *     
 *           
 *  @param[in]  RgDlSf         *dlSf, 
 *  @param[in]  RgLaaTbReq**    laaCellHqPLst,
 *  @param[in]  Inst            pMacInst,
 *  @return  Void
 *      -# RETVOID 
 **/
PUBLIC Void rgLaaChkAndReqTbs
(
 RgDlSf         *dlSf,
 RgLaaTbReq**    laaCellHqPLst,
 Inst            pMacInst
)
{
   U32   sMacIdx;
   U32   numTbReqsSent = 0;
   U32   sMacInst[RG_MAX_INST];
   Pst   pst;

   for(sMacIdx = 0; sMacIdx < RG_MAX_INST; sMacIdx++)
   {
      if(NULLP == laaCellHqPLst[sMacIdx]->memCp)
      {
         continue;
      }
      else
      {
         sMacInst[numTbReqsSent++] = sMacIdx;
         rgGetPstToInst(&pst,pMacInst,sMacIdx);
         RgLaaPrgSndPmacTbReq(&pst,(RgLaaPrgTbReq*)laaCellHqPLst[sMacIdx]);
      }
   }
   
   dlSf->numTbReqsSent = numTbReqsSent;

   RETVOID; 
}
/**
 * @brief Function for building TB indication for PMAC
 *
 * @details
 *
 *     Function : rgLaaBldTbInd 
 *            - Build TB indication
 *     
 *           
 *  @param[in] RgLaaTbReq    *hqPLstReq, 
 *  @param[in] Inst          pMacInst,
 *  @param[in] Inst          sMacInst
 *  @return  tbInd 
 *        -# RgLaaPrgTbInd*
 **/
PRIVATE RgLaaPrgTbInd* rgLaaBldTbInd
(
 RgLaaTbReq    *hqPLstReq,
 Inst          pMacInst,
 Inst          sMacInst
)
{
   RgLaaPrgTbIndInfo   *tbInfo;   
   RgLaaPrgTbInd    *tbInd = NULLP;
   Mem              sMem;
   RgCellCb       *cell;
   CmLList        *lnk = NULLP;
   CmLList        *hqNode= NULLP;
   RgLaaPrgTbReqInfo *tbReq = NULLP;
   RgUeCb     *ue = NULLP;
   RgDlSavedHqProcInfo  *hqP;
   U32        pProcId;
   U32        ueIdx;
   U32        idx;

   sMem.region = rgCb[pMacInst].rgInit.region;
   sMem.pool = rgCb[pMacInst].rgInit.pool;

   if((cell = rgCb[sMacInst].cell) == NULLP)
   {
      RLOG0(L_ERROR, "No cellCb found with cell");
      RETVALUE(NULLP);
   }
   /*Fetch the respective rnti's HqProc from ueCb list
    * Fill RgLaaTbInd struct and free HqProc*/
   if(NULLP != hqPLstReq->memCp)
   {
      /*To be freed by PMAC. Hence allocating using pMacInst*/
      if(RFAILED == cmAllocEvnt(sizeof(RgLaaPrgTbInd),TFU_MAX_MEMBLK_SIZE,&sMem,
               (Ptr *) &tbInd))
      {
         RETVALUE(NULLP);
      }

      CM_LLIST_FIRST_NODE(&hqPLstReq->laaTbInfoLst,lnk);

      for(ueIdx = 0; ueIdx < hqPLstReq->laaTbInfoLst.count; 
            ueIdx++,CM_LLIST_NEXT_NODE(&hqPLstReq->laaTbInfoLst,lnk))
      {
         tbReq = (RgLaaPrgTbReqInfo*)lnk->node;
         if((ue=rgDBMGetUeCb(cell,tbReq->rnti)) == NULLP)
         {
            /*log error*/
            RETVALUE(NULLP);
         }

         CM_LLIST_FIRST_NODE(&ue->dl.hqEnt.savedProcLst[tbReq->sCellHqProcId],hqNode);

            while(hqNode)
            {
               hqP = (RgDlSavedHqProcInfo*)hqNode;
               if(hqP->saveId == tbReq->saveId)
               {
                  pProcId = tbReq->pCellHqProcId;

                  if(RFAILED == cmGetMem((Ptr)&tbInd->memCp,sizeof(RgLaaPrgTbIndInfo),
                           (Ptr*)&tbInfo))
                  {
                     RETVALUE(NULLP);
                  }

                  tbInfo->rnti = tbReq->rnti;
                  tbInfo->pCellHqPId = pProcId;
                  tbInfo->numTbs = tbReq->numOfTBs;
                  if(RGINF_MAX_TB_PER_UE == tbReq->numOfTBs)
                  {
                     for(idx = 0; idx < tbReq->numOfTBs; idx++)
                     {
                        tbInfo->tb[idx] = hqP->tb[idx]; 
                     }
                  }
                  else if((RGINF_MAX_TB_PER_UE > tbReq->numOfTBs) 
                        && tbReq->numOfTBs)
                  {
                      tbInfo->tb[0] = hqP->tb[tbReq->tbId];
                  }
                  tbInfo->lnk.node = (PTR)tbInfo;
                  cmLListAdd2Tail(&(tbInd->laaTbLst),&tbInfo->lnk);
               }
               CM_LLIST_NEXT_NODE(&ue->dl.hqEnt.savedProcLst[tbReq->sCellHqProcId]
                     ,hqNode);
            }
      }
      /*Allocated by PMAC*/
      cmFreeMem(hqPLstReq->memCp);
   }
   else
   {
      /*Log failure*/
   }

   RETVALUE(tbInd);
}

/**
 * @brief Function for bulding and posting TB indication to PMAC 
 *
 * @details
 *
 *     Function : rgLaaSndPMacTbInd 
 *         - Build TB indication structure
 *         - retrieve pst for PMAC
 *         - Invoke wrapper to send to PMAC
 *     
 *  @param[in] RgLaaTbReq    *hqPLstReq, 
 *  @param[in] Inst           pMacInst,
 *  @param[in] Inst           sMacInst
 *  @return  Void
 *      -# RETVOID
 **/
PRIVATE Void rgLaaSndPMacTbInd
(
 RgLaaTbReq    *hqPLstReq,
 Inst           pMacInst,
 Inst           sMacInst
)
{
   RgLaaPrgTbInd*   tbInd = NULLP;
   Pst              pst;

   tbInd = rgLaaBldTbInd(hqPLstReq,pMacInst,sMacInst);

   if(NULLP == tbInd)
   {
      /*Log and RETVOID*/
   }

   rgGetPstToInst(&pst,sMacInst,pMacInst);

   RgLaaPrgSndTbInd(&pst,tbInd);

   RETVOID;
}


/**
 * @brief Function shall be invoked whenever SMAC receives PMAC's TB request
 *
 * @details
 *
 *     Function : rgLaaPrgRcvPmacTbReq 
 *             - Invokes rgLaaSndPMacTbInd
 *           
 *  @param[in]  Pst    *pst
 *  @param[in] RgLaaPrgTbReq  *tbReq
 *  @return  Void
 *      -# RETVOID 
 **/
PUBLIC Void rgLaaPrgRcvPmacTbReq
(
 Pst    *pst,
 RgLaaPrgTbReq  *tbReq
)
{
   rgLaaSndPMacTbInd((RgLaaTbReq*)tbReq,pst->srcInst,pst->dstInst);
}
/**
 * @brief Function for adjusting padding for the received TBs from SMAC
 *
 * @details
 *
 *     Function : rgLaaAdjustPadForTb 
 *             - Find the number of subheaders
 *             - Add padding at beginning or at end of TB based on size
 *             - Insert to UE's harq proc list
 *           
 *  @param[in] RgDlHqProcCb  *hqP 
 *  @param[in] Buffer        *tb
 *  @param[in] U8            tbIdx
 *  @param[in] Inst          inst
 *
 *  @return  S16
 *      -# ROK/RFAILED 
 **/
PRIVATE S16 rgLaaAdjustPadForTb
(
 RgDlHqProcCb   *hqP,
#ifndef L2_OPTMZ
 Buffer  *tb,
#else
RgTfuDatReqTbInfo     tb,
#endif
 U8      tbIdx,
 Inst    inst
)
{
   U32            schdTbSz;
   MsgLen         msgLen = 0;
   U32            numPadSubHdrs = 0;
   U32            extnBit = 0;
   Buffer         tbBuf;
   Buffer         tmpBuf;
   Buffer         *subHdrBuf = NULLP;
   U16            offsetLen = 0;
   U8             iter=0;
   U8             byte;
   U8             lcId;
   RgErrInfo      err;
   Bool           padAtEndPres = FALSE;

#ifndef L2_OPTMZ
   schdTbSz = hqP->tbInfo[tbIdx].tbSz;
   SFndLenMsg(tb, &msgLen);
   tbBuf = *tb;

   do
   {
      ++iter;

      if(SUnpkU8(&byte,&tbBuf) != ROK)
      {
      }
      RG_EXT_LCID(lcId, byte);
      RG_EXT_EXTN_BIT(extnBit, byte);

      if(lcId == RG_PAD_LCID)
      {
         if(extnBit)
         {
            ++numPadSubHdrs;      
            if(iter > 2)
            {
               padAtEndPres = TRUE;
            }
            continue;
         }
      }
      else if ((lcId >= RG_EXT_PHR_LCID) && (lcId <= RG_LONG_BSR_LCID))
      {
         continue;
      }
      else if(lcId <= RG_DEDLC_MAX_LCID)
      {
         if(extnBit)
         {
            if(rgDUXExtSduLen(inst,&tbBuf, &offsetLen, &err) != ROK)
               break;
         }
      }
      else
      {
         extnBit = 1;
      }
   }
   while(extnBit);


   if(padAtEndPres)//already @ end
   {
      if((schdTbSz - msgLen))
      {
         SAddPstMsgMult((Data*)0x3F,(MsgLen)(schdTbSz - msgLen),tb); 
      }
   }
   else//existing padding is either 1/2 byte 
   {
      if((((schdTbSz - msgLen) > 2) && (numPadSubHdrs <= 2))
            || ((schdTbSz - msgLen) + numPadSubHdrs > 2))
      {
         RgMUXSubHdr    subHdr;
         Buffer         *padBuf = NULLP;
         S16   ret;

         //remove all headers
         SRemPreMsgMult((Data *)subHdrBuf,(msgLen-offsetLen),tb);

         // append padding subheader to subheader mBuf
         RG_PACK_LAST_SDU_SHDR(subHdr, 0x1F, subHdrBuf, ret);

         //combine new subheader mBuf and remaining TB
         RG_PACK_SDU(subHdrBuf,tb,ret);

         //padding @ end
         RG_PACK_PAD(padBuf,(schdTbSz - msgLen),tb);

         //Remove previous sub headers
         SRemPreMsgMult((Data *)&tmpBuf,numPadSubHdrs,tb);
      }
      else // No padding present 
      {
         if((schdTbSz - msgLen) && 
               ((schdTbSz - msgLen) + numPadSubHdrs) == 2)
         {
            U8 sHdrArr[RG_MAX_NUM_PAD_HDRS] = {0x3F, 0x3F};
            SAddPreMsgMult(sHdrArr,numPadSubHdrs,tb); 
         }
      }
   }   
#else
   schdTbSz = hqP->tbInfo[tbIdx].tbSz;
   if(schdTbSz > tb.tbSize)
   {
      tb.padSize += schdTbSz  - tb.tbSize;
   }
   else
   {
       tb.padSize -= tb.tbSize - schdTbSz;
   }
   tb.tbSize = schdTbSz;
#endif/*L2_OPTMZ*/
   /*add TB to UE hqp list*/
#ifndef L2_OPTMZ
   if(hqP->tbInfo[tbIdx].tb)
#endif
   {
      hqP->tbInfo[tbIdx].tb = tb;
   }
   RETVALUE(ROK);
}
/**
 * @brief Function for preparing the TB as per PMACs new grant
 *
 * @details
 *
 *     Function : rgLaaPrepTb 
 *          - Derive Harq Proc and invoke rgLaaAdjustPadForTb 
 *           
 *  @param[in]  RgUeCb            *ue,
 *  @param[in]  RgLaaPrgTbIndInfo *tbIndInfo
 *  @param[in]  Inst              pMacInst 
 *  @return Void 
 *      -# RETVOID
 **/
PRIVATE Void rgLaaPrepTb
(
 RgUeCb            *ue,
 RgLaaPrgTbIndInfo *tbIndInfo ,
  Inst              pMacInst 
)
{
   RgDlHqProcCb   *hqP;
   U8   idx;
   
   rgDHMGetHqProcFrmId(ue,tbIndInfo->pCellHqPId,&hqP);

   for(idx = 0; idx < tbIndInfo->numTbs; idx++)
   {
      rgLaaAdjustPadForTb(hqP,tbIndInfo->tb[idx],idx,pMacInst);
   }
   RETVOID;
}

/**
 * @brief Function for handling the received TB indication from SMAC
 *
 * @details
 *
 *     Function : rgLaaHdlTbInd 
 *       - Fetch the UE
 *       - Readjust padding for TB
 *       - Insert Harq Proc into current sub frame
 *           
 *  @param[in] RgPrgLaaTbInd *tbInd,
 *  @param[in] Inst          pMacInst
 *  @return  Void
 *      -# RETVOID
 **/
PRIVATE Void rgLaaHdlTbInd
(
RgLaaPrgTbInd *tbInd,
Inst          pMacInst
)
{

   RgLaaPrgTbIndInfo  *tbIndInfo;
   CmLList            *lnk;
   RgCellCb       *cell;
   RgDlSf         *dlSf = NULLP;
   RgDlHqProcCb   *hqP;
   RgUeCb            *ue;
   U32               idx;

   if((cell = rgCb[pMacInst].cell) == NULLP)
   {
      RLOG0(L_ERROR, "No cellCb found with cell");
      RETVOID;
   }

   CM_LLIST_FIRST_NODE(&tbInd->laaTbLst,lnk);

   while(NULLP != lnk)
   {
      tbIndInfo = (RgLaaPrgTbIndInfo*)lnk->node;
      dlSf = &cell->subFrms[tbIndInfo->timingInfo.subframe];
      if((ue=rgDBMGetUeCb(cell,tbIndInfo->rnti)) == NULLP)
      {
         RETVOID;
      }

      /*prepare the TB and push to HqP*/
      rgLaaPrepTb(ue,tbIndInfo,pMacInst);

      rgDHMGetHqProcFrmId(ue,tbIndInfo->pCellHqPId,&hqP);
      for(idx = 0; idx < hqP->numOfTBs;idx++)
      {
         cmLListAdd2Tail(&dlSf->tbs,&hqP->tbInfo[idx].sfLnk);
      }
      CM_LLIST_NEXT_NODE(&tbInd->laaTbLst,lnk);
   }

   /*Allocated by SMAC*/
   cmFreeMem(&tbInd->memCp);
   if(NULLP != lnk)
   {
   dlSf->numTbReqsSent--;
   }
   RETVOID;
}

/**
 * @brief Function for receiving TB Indication sent from SMAC
 *
 * @details
 *
 *     Function : rgLaaPrgRcvSmacTbInd
 *           - Invokes rgLaaHdlTbInd     
 *           
 *  @param[in]  Pst    *pst,
 *  @param[in] RgLaaPrgTbInd  *tbInd,
 *  @return  Void
 *      -# RETVOID 
 **/
PUBLIC Void rgLaaPrgRcvSmacTbInd
(
 Pst    *pst,
 RgLaaPrgTbInd  *tbInd
)
{
   rgLaaHdlTbInd(tbInd,pst->dstInst);
}


/**
 * @brief Function for checking if all TB indications are received from all
 *         SMACs
 *
 * @details
 *
 *     Function : rgLaaChkAllRxTbs 
 *     
 *  @param[in] RgDlSf   *dlSf 
 *  @return  TRUE/FALSE
 *      -# Bool
 **/
/*used to check if all the requested TBs are receved in Ind from all the SCELLs*/
PUBLIC Bool rgLaaChkAllRxTbs
(
 RgDlSf   *dlSf
)
{
   Bool  allTbsRxd = FALSE;

   if(0 == dlSf->numTbReqsSent)
   {
      allTbsRxd = TRUE;
   }

   RETVALUE(allTbsRxd);
}

/**
 * @brief Function is responsible for pushing Harq proc to SMAC list from PMAC
 *
 * @details
 *
 *     Function : rgLaaPushHqPToScellLst 
 *             - Push the tb req info into Scell list maintained at PMAC
 *           
 *  @param[in] RgInfUeAlloc  *allocInfo
 *  @param[in] RgLaaTbReq    **laaCellHqPLst
 *  @param[in] CmLteTimingInfo   timingInfo
 *  @return  S16
 *      -# ROK/RFAILED 
 **/
PUBLIC S16 rgLaaPushHqPToScellLst
(
RgInfUeAlloc  *allocInfo,
RgLaaTbReq**    laaCellHqPLst,
CmLteTimingInfo   timingInfo
)
{
   RgLaaTbInfo  *tbReq;
   Mem         sMem;
   U8          inst = allocInfo->tbReqInfo.sMacInstId;
   sMem.region = rgCb[inst].rgInit.region;
   sMem.pool = rgCb[inst].rgInit.pool;
   /*allocInfo->sCellHqPId will be filled only for pMAC. To be taken care by SCH*/
   if(0xFF != allocInfo->tbReqInfo.sCellHqPId)
   {
      if(NULLP == laaCellHqPLst[inst]) /* laa_ut_fix */
      {
         if(RFAILED == cmAllocEvnt(sizeof(RgLaaTbReq),TFU_MAX_MEMBLK_SIZE,&sMem,
                  (Ptr *) &laaCellHqPLst[inst]))
         {
            RETVALUE(RFAILED);
         }
         cmLListInit(&(laaCellHqPLst[inst]->laaTbInfoLst)); /* laa_ut_fix */
      }
      if(RFAILED == cmGetMem((Ptr)laaCellHqPLst[inst]->memCp,sizeof(RgLaaTbInfo),
               (Ptr*)&tbReq))
      {
         RETVALUE(RFAILED);
      }

      tbReq->rnti = allocInfo->rnti;
      tbReq->pCellHqProcId = allocInfo->hqProcId;
      tbReq->sCellHqProcId = allocInfo->tbReqInfo.sCellHqPId;
      tbReq->saveId = allocInfo->tbReqInfo.hqPStamp;
      tbReq->timingInfo = timingInfo;
      tbReq->tbId = allocInfo->tbReqInfo.tbId;
      tbReq->nmbOfTBs = allocInfo->nmbOfTBs;
      tbReq->lnk.node = (PTR)tbReq;
      cmLListAdd2Tail(&(laaCellHqPLst[inst]->laaTbInfoLst),&tbReq->lnk);

      RETVALUE(ROK);
   }
   RETVALUE(RFAILED);
}
/**
 * @brief Function for initializing TB req list at PMAC
 *
 * @details
 *
 *     Function : rgLaaInitTbInfoLst 
 *     
 *  @param[in] RgLaaTbReq **tbInfoLst 
 *  @return  Void
 *      -# RETVOID
 **/
PUBLIC Void rgLaaInitTbInfoLst
(
RgLaaTbReq **tbInfoLst
)
{
   U32 sCellIdx;
   /*REEMA*/
   RETVOID;
   for(sCellIdx = 0;sCellIdx < RG_MAX_SCELL_PER_UE;sCellIdx++)
   {
      /* laa_ut_fix */
      //cmLListInit(&(tbInfoLst[sCellIdx]->laaTbInfoLst));
      tbInfoLst[sCellIdx] = NULLP;
   }
   RETVOID;
}

#endif

/**********************************************************************

         End of file:     rg_laa.c

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
*********************************************************************91*/

