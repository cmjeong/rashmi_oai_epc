
/************************************************************************
 
     Name:     LTE MAC Convergence Layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     ys_pal_msg.c
  
     Sid:      ys_pal_msg.c@@/main/2 - Thu Dec  2 02:27:19 2010
  
     Prg:      hsingh
  
**********************************************************************/

/** @file ys_pal_msg.c
@brief This module acts as an interface handler for upper interface and 
manages Pst and Sap related information for upper interface APIs.
*/

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
#include "cm_lte.h"
#include "ctf.h"           /* CTF defines */
#include "lys.h"           /* layer management typedefs for CL */
#include "tfu.h"
#include <sys/time.h>
#include "ys_pal_err.h"        /* YS error defines */
#include "ys_pal.h"

/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"
#include "ctf.x"           /* CTF types */
#include "lys.x"           /* layer management typedefs for CL */
#include "tfu.x"
#include "ys_pal.x" 

/* header/extern include files (.x) */
/* header include files (.h) */
PUBLIC U8  ysMemAlrm;
#ifdef TENB_SPLIT_ARCH_SUPPORT
void ysSendEgtpInd(U32 indType);
#endif

#ifndef SS_CAVIUM
#ifdef LTE_PAL_ENB
PRIVATE Buffer *ysPalPkTfuCntrlReq ARGS(( Pst *pst, SpId spId, TfuCntrlReqInfo *cntrlReq));
PRIVATE Buffer *ysPalPkTfuDatReq ARGS(( Pst *pst, SpId spId, TfuDatReqInfo *datReq));
PRIVATE Buffer *ysPalPkTfuRecpReq ARGS(( Pst *pst, SpId spId, TfuRecpReqInfo *recpReq));
#else /* LTE_PAL_ENB */
PRIVATE Buffer *ysPalPkTfuRaReqInd ARGS(( Pst *pst, SuId suId, TfuRaReqIndInfo *raReqInd));
PRIVATE Buffer *ysPalPkTfuHqInd ARGS(( Pst *pst, SuId suId, TfuHqIndInfo *hqInd));
PRIVATE Buffer *ysPalPkTfuSrInd ARGS(( Pst *pst, SuId suId, TfuSrIndInfo *srInd));
PRIVATE Buffer *ysPalPkTfuDatInd ARGS(( Pst *pst, SuId suId, TfuDatIndInfo *datInd));
PRIVATE Buffer *ysPalPkTfuTimingAdvInd ARGS((
Pst * pst,
SuId suId,
TfuTimingAdvIndInfo* taInd
));
#endif /* LTE_PAL_ENB */
#endif /* SS_CAVIUM */

#ifdef YS_PAL_PERF_MEAS
PRIVATE unsigned long int   ttiCount;
#ifdef LTE_PAL_ENB
PRIVATE unsigned long int   dlBytesSent;
#endif
PRIVATE DateTime  initialDt;
unsigned long ulPktCount=0;
unsigned long ulBytes=0;
#endif
DateTime  startDt;

U32 numEnCodeL1DataReqSent = 0;
U32 numEnCodeL1DataReqRecv = 0;
#ifdef LTE_PAL_ENB
/*
*
*       Fun:   ysPalHdlTtiInd
*
*       Desc:  
*
*       Ret:   
*
*       Notes: None
*
*       File:  ys_pal_utl.c
*
*/

#ifdef ANSI
PUBLIC Void ysPalHdlTtiInd
(
CmLteTimingInfo  *timingInfo
)
#else
PUBLIC Void ysPalHdlTtiInd(timingInfo)
CmLteTimingInfo  *timingInfo;
#endif
{
   TfuTtiIndInfo   ttiInd;
   TfuTtiIndInfo   schTtiInd;
   /* Removed cellCb for optimization */

   TRC2(ysPalHdlTtiInd)

   /* Adding for quantify testing */
   PRIVATE unsigned long ttiCnt = 0;
   ttiCnt++;
   
   /* ys003.102: Fix for CID:1622-02-01 DefectId:ccpu00115333. adding Cell delete 
      feature for PAL.
   */
   /* Condition to check the existence of the cell */
   if ((NULLP != ysCb.cellCb.tfuSap) && (NULLP != ysCb.cellCb.schTfuSap))
   {
      /* allocate TTI indication for MAC */
	   if (ttiCnt < 3) {
#if 0
		   if(SGetSBuf(ysCb.tfuSap.sapPst.region, ysCb.tfuSap.sapPst.pool, 
					   (Data **)&ttiInd, sizeof(TfuTtiIndInfo)) != ROK)
		   {
			   YS_DBG_ERR((_ysp, "Failed to get static memory\n"));
			   RETVOID;
		   }

		   /* allocate TTI indication for scheduler */
		   if(SGetSBuf(ysCb.schTfuSap.sapPst.region, ysCb.schTfuSap.sapPst.pool, 
					   (Data **)&schTtiInd, sizeof(TfuTtiIndInfo)) != ROK)
		   {
			   YS_DBG_ERR((_ysp, "Failed to get static memory\n"));
			   SPutSBuf(ysCb.tfuSap.sapPst.region, 
					   ysCb.tfuSap.sapPst.pool, 
					   (Data *)ttiInd, sizeof(TfuTtiIndInfo));
			   RETVOID;
		   }/* fill TTI indication for MAC */
#endif
#if 0
		   ttiInd->cellId = ysCb.cellCb.cellId;

		   ttiInd->timingInfo = *timingInfo;
		   ttiInd->isDummyTti = FALSE;
#else
		   ttiInd.numCells = 1;
		   ttiInd.cells[0].cellId = ysCb.cellCb.cellId;
		   ttiInd.cells[0].timingInfo = *timingInfo;
		   ttiInd.cells[0].isDummyTti = 0;   
		   ttiInd.cells[0].schTickDelta = 0; 
		   ttiInd.cells[0].dlBlankSf = 0;    
		   ttiInd.cells[0].ulBlankSf = 0; 
#endif

		   /* fill TTI indication for scheduler */
		   schTtiInd = ttiInd;
	   } 
      
	if((ttiCnt == 2) || (ttiCnt == 3)) {
		encodeDl(ttiCnt - 2);
	}
	/* 2 TTIs slower */
	if(ttiCnt == 3) {
#if 0
		start_dl();
#else
         extern U8 isStartDl;
         isStartDl= 1;
#endif
	}
	if(ttiCnt < 2) {
		printf("CL: sending proper TTI to MAC and scheduler sf(%d) sfn(%d)\n", ttiCnt % 10, ttiCnt / 10);
		/* Give TTI indication to MAC */
		YsUiTfuTtiInd(&ysCb.tfuSap.sapPst, ysCb.tfuSap.suId, &ttiInd);

		/* Give TTI indication to scheduler */
		YsUiTfuSchTtiInd(&ysCb.schTfuSap.sapPst, ysCb.schTfuSap.suId, &schTtiInd);
	}
#if 0
#ifdef TENB_SPLIT_ARCH_SUPPORT
      {
         static Bool egTxEvnt;

         ysSendEgtpInd(22);
         if (egTxEvnt)
         {
            ysSendEgtpInd(23);
            egTxEvnt = FALSE;
         }
         else
         {
            egTxEvnt = TRUE;
         }
      }
#endif
#endif
   } 
#if 0 
   ysPalHdlDlMsg(timingInfo);
#endif

   RETVOID;
} /* end of ysPalHdlTtiInd */

#ifdef TENB_SPLIT_ARCH_SUPPORT

/*!<This function is used to send indication to 
eGTP Layer to start Tx/Rx Operation >*/
void ysSendEgtpInd(U32 indType)
{
        static Pst pst;
	pst.dstEnt = ENTEG;
	pst.srcEnt = ENTYS;
        Buffer *mBuf = NULLP;

        /*Get Message for General Use*/
        SGetMsg(ysCb.ysInit.region, ysCb.ysInit.region, (Buffer **) &mBuf);

        pst.event = indType;
        SPstTsk(&pst,mBuf);
        return;
}

#endif
#endif /* LTE_PAL_ENB */

/*
*
*       Fun:   ysPalHdlDlMsg
*
*       Desc:  
*
*       Ret:   
*
*       Notes: None
*
*       File:  ys_pal_utl.c
*
*/

#ifdef ANSI
PUBLIC Void ysPalHdlDlMsg
(
CmLteTimingInfo  *timingInfo
)
#else
PUBLIC Void ysPalHdlDlMsg(timingInfo)
CmLteTimingInfo  *timingInfo;
#endif
{
   YsTxMsgArr      *txMsgArr;
   YsTxMsgInfo     *txMsgInfo;
   U16              idx;
#ifndef SS_CAVIUM   
   Buffer *mBuf;
#endif /* SS_CAVIUM */
#ifdef YS_PAL_PERF_MEAS
#ifdef LTE_PAL_ENB
   DateTime   dt;
   unsigned long int  secDiff;
#endif
#endif

   TRC2(ysPalHdlDlMsg)
#if 0
#ifdef YS_PAL_PERF_MEAS
   if (ttiCount == 0)
   {
      SGetDateTime(&initialDt);
   }
   ttiCount++;
#endif

   txMsgArr = &(ysCb.cellCb.txMsgArr[timingInfo->subframe]);

   if(txMsgArr->num)
   {
      for(idx = 0; idx < txMsgArr->num; idx++)
      {
         txMsgInfo = &(txMsgArr->txMsgInfo[idx]);
         switch(txMsgInfo->event)
         {
#ifdef LTE_PAL_ENB
            case EVTTFUCNTRLREQ:
            {
               TfuCntrlReqInfo  *cntrlReq;
               cntrlReq = (TfuCntrlReqInfo *)txMsgInfo->tfuMsg;
#ifdef SS_CAVIUM   
               cmPkTfuCntrlReq(&ysCb.cellCb.peerPst, 
                     ysCb.schTfuSap.spId, cntrlReq);
#else               
               mBuf = ysPalPkTfuCntrlReq(&ysCb.cellCb.peerPst, 
                                 ysCb.schTfuSap.spId, cntrlReq);
               if(mBuf != NULLP)
               {
                  ysPalSend2Peer(mBuf, EVTTFUCNTRLREQ);
                  SPutMsg(mBuf);
               }
#endif /* SS_CAVIUM */
            }
            break;

            case EVTTFUDATREQ:
            {
               TfuDatReqInfo    *datReq;
               datReq = (TfuDatReqInfo *)txMsgInfo->tfuMsg;
#ifdef YS_PAL_PERF_MEAS
               {
                  CmLList *node;
                  MsgLen  msgLen = 0;
                  TfuDatReqPduInfo *elmnt;
                  unsigned long int bps;
                  U16     i;

                  node = datReq->pdus.last;
                  while(node)
                  {
                     elmnt = (TfuDatReqPduInfo *)node->node;
		printf("ERRRROR CL: numTB numTb(%d) \n", elmnt->nmbOfTBs);
                     for(i = 0; i < elmnt->nmbOfTBs; i++) 
                     {
                        SFndLenMsg(elmnt->mBuf[i], &msgLen);
		printf("ERRRROR CL: msgLen(%d) \n", msgLen);
                        dlBytesSent = dlBytesSent + msgLen;
                     }

                     node = node->prev;
                  }
                  if (ttiCount >= 10000)
                  {
                     /* U32 availMem = 0; */
                     SGetDateTime(&dt);
                     secDiff = (dt.sec + (dt.min * 60) + (dt.hour * 60 * 60)) -
                                  (initialDt.sec + (initialDt.min * 60) +
                                  (initialDt.hour * 60 * 60));
                     if(secDiff)
                     {
                     bps = ((dlBytesSent * 8) / secDiff);
                     YS_DBG_INFO((_ysp, "\nMessage Rate: %ld bps, dl bytes: %ld, \
                                   ttiCount: %ld, time diff: %ld\n", 
                                  bps, dlBytesSent, ttiCount, secDiff));
                     printf("\nMessage Rate: %ld bps, dl bytes: %ld, ttiCount: %ld, time diff: %ld\n", 
                                  bps, dlBytesSent, ttiCount, secDiff);
                     printf("\nMessage Rate: %ld bps, dl bytes: %ld, \
                                   ttiCount: %ld, time diff: %ld\n", 
                                  bps, dlBytesSent, ttiCount, secDiff);
                   /*  SRegInfoShow(0, &availMem);*/
                     }
                     ttiCount = 0;
                     dlBytesSent = 0;
                     bps = 0;
                  }

               }
#endif
#ifdef SS_CAVIUM   
               cmPkTfuDatReq(&ysCb.cellCb.peerPst, 
                     ysCb.tfuSap.spId, datReq);
#else               
               mBuf = ysPalPkTfuDatReq(&ysCb.cellCb.peerPst, 
                                 ysCb.tfuSap.spId, datReq);
               if(mBuf != NULLP)
               {
                  ysPalSend2Peer(mBuf, EVTTFUDATREQ);
                  SPutMsg(mBuf);
               }
#endif /* SS_CAVIUM */               
            }
            break;

            case EVTTFURECPREQ:
            {
               TfuRecpReqInfo   *recpReq;
               recpReq = (TfuRecpReqInfo *)txMsgInfo->tfuMsg;
#ifdef SS_CAVIUM   
               cmPkTfuRecpReq(&ysCb.cellCb.peerPst, 
                     ysCb.schTfuSap.spId, recpReq);
#else               
               mBuf = ysPalPkTfuRecpReq(&ysCb.cellCb.peerPst, 
                                 ysCb.schTfuSap.spId, recpReq);
               if(mBuf != NULLP)
               {
                  ysPalSend2Peer(mBuf, EVTTFURECPREQ);
                  SPutMsg(mBuf);
               }
#endif /* SS_CAVIUM */               
            }
            break;

#else /* LTE_PAL_ENB */ 

            case EVTTFURAREQIND:
            {
               TfuRaReqIndInfo   *raReqInd;
               raReqInd = (TfuRaReqIndInfo *)txMsgInfo->tfuMsg;
#ifdef SS_CAVIUM   
               cmPkTfuRaReqInd(&ysCb.cellCb.peerPst, 
                     ysCb.schTfuSap.suId, raReqInd);
#else
               mBuf = ysPalPkTfuRaReqInd(&ysCb.cellCb.peerPst, 
                                 ysCb.schTfuSap.suId, raReqInd);
               if(mBuf != NULLP)
               {
                  ysPalSend2Peer(mBuf, EVTTFURAREQIND);
                  SPutMsg(mBuf);
               }
#endif /* SS_CAVIUM */               
            }
            break;

            case EVTTFUHQIND:
            {
               TfuHqIndInfo   *hqInd;
               hqInd = (TfuHqIndInfo *)txMsgInfo->tfuMsg;
#ifdef SS_CAVIUM   
               cmPkTfuHqInd(&ysCb.cellCb.peerPst, 
                     ysCb.schTfuSap.suId, hqInd);
#else
               mBuf = ysPalPkTfuHqInd(&ysCb.cellCb.peerPst, 
                                 ysCb.schTfuSap.suId, hqInd);
               if(mBuf != NULLP)
               {
                  ysPalSend2Peer(mBuf, EVTTFUHQIND);
                  SPutMsg(mBuf);
               }
#endif /* SS_CAVIUM */               
            }
            break;

            case EVTTFUTIMINGADVIND:
            {
               TfuTimingAdvIndInfo *taIndInfo;
               taIndInfo = (TfuTimingAdvIndInfo*)txMsgInfo->tfuMsg;
#ifdef SS_CAVIUM   
               cmPkTfuTimingAdvInd(&ysCb.cellCb.peerPst, 
                     ysCb.schTfuSap.suId, taIndInfo);
#else
               mBuf = ysPalPkTfuTimingAdvInd(&ysCb.cellCb.peerPst, 
                                 ysCb.schTfuSap.suId, taIndInfo);
               if(mBuf != NULLP)
               {
                  ysPalSend2Peer(mBuf, EVTTFUTIMINGADVIND);
                  SPutMsg(mBuf);
               }
#endif /* SS_CAVIUM */               
             }
             break;

            case EVTTFUSRIND:
            {
               TfuSrIndInfo   *srInd;
               srInd = (TfuSrIndInfo *)txMsgInfo->tfuMsg;
#ifdef SS_CAVIUM   
               cmPkTfuSrInd(&ysCb.cellCb.peerPst, 
                     ysCb.schTfuSap.suId, srInd);
#else
               mBuf = ysPalPkTfuSrInd(&ysCb.cellCb.peerPst, 
                                 ysCb.schTfuSap.suId, srInd);
               if(mBuf != NULLP)
               {
                  ysPalSend2Peer(mBuf, EVTTFUSRIND);
                  SPutMsg(mBuf);
               }
#endif /* SS_CAVIUM */               
            }
            break;

            case EVTTFUDATIND:
            {
               TfuDatIndInfo   *datInd;
#ifdef YS_PAL_PERF_MEAS
               DateTime         endDt;
               MsgLen           msgLen=0;
               unsigned long    secdiff;
               CmLList          *node1;
               TfuDatInfo       *elmnt1;
               unsigned long     tBps;
#endif
               datInd = (TfuDatIndInfo *)txMsgInfo->tfuMsg;
#ifdef  YS_PAL_PERF_MEAS
               if(ulBytes == 0)
               {
                     SGetDateTime(&startDt);
               }
               ulPktCount++;
               node1 = datInd->datIndLst.last;
               while(node1)
               {
                  elmnt1 =(TfuDatInfo *) node1->node;                  
                  SFndLenMsg(elmnt1->mBuf, &msgLen);
                  ulBytes = ulBytes + msgLen;
                  node1 = node1->prev;
               }
               if(ulPktCount > 10000)
               {
                  SGetDateTime(&endDt);
                  secdiff = (endDt.sec + (endDt.min * 60) + (endDt.hour * 60 * 60)) - (startDt.sec + (startDt.min * 60) + (startDt.hour * 60 * 60));
                  tBps = (ulBytes*8)/secdiff; 
                  YS_DBG_INFO((_ysp, "\n ****** UL Data Rate %d bps  Bytes(%d) SecDiff(%d)***************\n", 
                                  tBps, ulBytes, secdiff));
                   printf("\n ****** UL Data Rate %ld bps  Bytes(%ld) SecDiff(%ld), ulpkt %ld***************\n",tBps, ulBytes, secdiff, ulPktCount);
                  ulBytes = 0;
                  ulPktCount =0; 
                  tBps = 0;
                  secdiff = 0;
               }
#endif
#ifdef SS_CAVIUM   
               cmPkTfuDatInd(&ysCb.cellCb.peerPst, 
                     ysCb.tfuSap.suId, datInd);
#else
               mBuf = ysPalPkTfuDatInd(&ysCb.cellCb.peerPst, 
                                 ysCb.tfuSap.suId, datInd);
               if(mBuf != NULLP)
               {
                  ysPalSend2Peer(mBuf, EVTTFUDATIND);
                  SPutMsg(mBuf);
               }
#endif /* SS_CAVIUM */               
            }
            break;
#endif /* LTE_PAL_ENB */

            default:
               YS_DBG_ERR((_ysp, "Unknown event %d\n", txMsgInfo->event));
         }
      }

      memset ((U8 *)txMsgArr, 0, sizeof(YsTxMsgArr));
   }
#endif
   RETVOID;
} /* end of ysPalHdlDlMsg */

#ifndef SS_CAVIUM
#ifdef LTE_PAL_ENB

#ifdef ANSI
PRIVATE Buffer *ysPalPkTfuCntrlReq
(
Pst * pst,
SpId spId,
TfuCntrlReqInfo * cntrlReq
)
#else
PRIVATE Buffer *ysPalPkTfuCntrlReq(pst, spId, cntrlReq)
Pst * pst;
SpId spId;
TfuCntrlReqInfo * cntrlReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(ysPalPkTfuCntrlReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "SGetMsg() failed\n"));
      SPutSBuf(pst->region, pst->pool, (Data *)cntrlReq, sizeof(TfuCntrlReqInfo));
      RETVALUE(NULLP);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuCntrlReqInfo(cntrlReq, mBuf) != ROK) {
         YS_DBG_ERR((_ysp, "packing failed\n"));
         cmFreeMem((Ptr)cntrlReq);
         SPutMsg(mBuf);
         RETVALUE(NULLP);
      }
   }

   if (SPkS16(spId, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)cntrlReq);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   pst->event = (Event) EVTTFUCNTRLREQ;

   if (SPkU8(pst->event, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)cntrlReq);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }

   cmFreeMem((Ptr)cntrlReq);

   RETVALUE(mBuf);
}

PUBLIC Buffer *ysPalPkTful1EncodeReq
(
Pst * pst,
SpId spId,
U32 tti 
)
{
   Buffer *mBuf = NULLP;
   TRC3(ysPalPkTfuRecpReq)
   numEnCodeL1DataReqSent++;
   if(numEnCodeL1DataReqSent == 1000000)
   {
     numEnCodeL1DataReqSent = 10;
     numEnCodeL1DataReqRecv = 0;
     printf("Resetting the values \n");
   }

   if((numEnCodeL1DataReqSent - numEnCodeL1DataReqRecv) < 30)
   {
      printf("Dropping TTI Ind\n");
      RETVALUE(NULLP);
   }
    
   pst->dstProcId = pst->srcProcId;
   if(SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "SGetMsg() failed\n"));
      RETVALUE(NULLP);
   }

   if (SPkS16(spId, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   
   pst->event = (Event) EVTTFUENCODEL1DATA;
   
   if (SPkU8(pst->event, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   RETVALUE(SPstTsk(pst,mBuf));
}

PUBLIC Buffer *ysPalPkTful1ReadReq
(
Pst * pst,
SpId spId,
U32 tti 
)
{
   Buffer *mBuf = NULLP;
   TRC3(ysPalPkTfuRecpReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "SGetMsg() failed\n"));
      RETVALUE(NULLP);
   }

   if (SPkS16(spId, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   
   pst->event = (Event) EVTTFUREADL1DATA;
   
   if (SPkU8(pst->event, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   RETVALUE(SPstTsk(pst,mBuf));
}

#ifdef ANSI
PRIVATE Buffer *ysPalPkTfuDatReq
(
Pst * pst,
SpId spId,
TfuDatReqInfo * datReq
)
#else
PRIVATE Buffer *ysPalPkTfuDatReq(pst, spId, datReq)
Pst * pst;
SpId spId;
TfuDatReqInfo * datReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(ysPalPkTfuDatReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "SGetMsg() failed\n"));
      SPutSBuf(pst->region, pst->pool, (Data *)datReq, sizeof(TfuDatReqInfo));
      RETVALUE(NULLP);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuDatReqInfo(datReq, mBuf) != ROK) {
         YS_DBG_ERR((_ysp, "packing failed\n"));
         cmFreeMem((Ptr)datReq);
         SPutMsg(mBuf);
         RETVALUE(NULLP);
      }
   }
   
   if (SPkS16(spId, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)datReq);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   
   pst->event = (Event) EVTTFUDATREQ;
   
   if (SPkU8(pst->event, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)datReq);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   
   cmFreeMem((Ptr)datReq);

   RETVALUE(mBuf);
}

#ifdef ANSI
PRIVATE Buffer *ysPalPkTfuRecpReq
(
Pst * pst,
SpId spId,
TfuRecpReqInfo * recpReq
)
#else
PRIVATE Buffer *ysPalPkTfuRecpReq(pst, spId, recpReq)
Pst * pst;
SpId spId;
TfuRecpReqInfo * recpReq;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(ysPalPkTfuRecpReq)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "SGetMsg() failed\n"));
      SPutSBuf(pst->region, pst->pool, (Data *)recpReq, sizeof(TfuRecpReqInfo));
      RETVALUE(NULLP);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuRecpReqInfo(recpReq, mBuf) != ROK) {
         YS_DBG_ERR((_ysp, "packing failed\n"));
         cmFreeMem((Ptr)recpReq);
         SPutMsg(mBuf);
         RETVALUE(NULLP);
      }
   }

   if (SPkS16(spId, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)recpReq);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   
   pst->event = (Event) EVTTFURECPREQ;
   
   if (SPkU8(pst->event, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)recpReq);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   
   cmFreeMem((Ptr)recpReq);
   RETVALUE(mBuf);
}

#else /* LTE_PAL_ENB */

#ifdef ANSI
PRIVATE Buffer *ysPalPkTfuRaReqInd
(
Pst * pst,
SuId suId,
TfuRaReqIndInfo * raReqInd
)
#else
PRIVATE Buffer *ysPalPkTfuRaReqInd(pst, suId, raReqInd)
Pst * pst;
SuId suId;
TfuRaReqIndInfo * raReqInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(ysPalPkTfuRaReqInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "SGetMsg() failed\n"));
      SPutSBuf(pst->region, pst->pool, (Data *)raReqInd, sizeof(TfuRaReqIndInfo));
      RETVALUE(NULLP);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuRaReqIndInfo(raReqInd, mBuf) != ROK) {
         YS_DBG_ERR((_ysp, "packing failed\n"));
         cmFreeMem((Ptr)raReqInd);
         SPutMsg(mBuf);
         RETVALUE(NULLP);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)raReqInd);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }

   pst->event = (Event) EVTTFURAREQIND;
   if (SPkU8(pst->event, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)raReqInd);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   
   cmFreeMem((Ptr)raReqInd);
   RETVALUE(mBuf);
}

#ifdef ANSI
PRIVATE Buffer *ysPalPkTfuHqInd
(
Pst * pst,
SuId suId,
TfuHqIndInfo * hqInd
)
#else
PRIVATE Buffer *ysPalPkTfuHqInd(pst, suId, hqInd)
Pst * pst;
SuId suId;
TfuHqIndInfo * hqInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(ysPalPkTfuHqInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "SGetMsg() failed\n"));
      SPutSBuf(pst->region, pst->pool, (Data *)hqInd, sizeof(TfuHqIndInfo));
      RETVALUE(NULLP);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuHqIndInfo(hqInd, mBuf) != ROK) {
         YS_DBG_ERR((_ysp, "packing failed\n"));
         cmFreeMem((Ptr)hqInd);
         SPutMsg(mBuf);
         RETVALUE(NULLP);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)hqInd);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   
   pst->event = (Event) EVTTFUHQIND;
   if (SPkU8(pst->event, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)hqInd);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   
   cmFreeMem((Ptr)hqInd);
   RETVALUE(mBuf);
}

#ifdef ANSI
PRIVATE Buffer *ysPalPkTfuTimingAdvInd
(
Pst * pst,
SuId suId,
TfuTimingAdvIndInfo* taInd
)
#else
PRIVATE Buffer *ysPalPkTfuTimingAdvInd(pst, suId, taInd)
Pst * pst;
SuId suId;
TfuTimingAdvIndInfo* taInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(ysPalPkTfuTimingAdvInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "SGetMsg() failed\n"));
      SPutSBuf(pst->region, pst->pool, (Data *)taInd, sizeof(TfuTimingAdvIndInfo));
      RETVALUE(NULLP);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuTimingAdvIndInfo(taInd, mBuf) != ROK) {
         YS_DBG_ERR((_ysp, "packing failed\n"));
         cmFreeMem((Ptr)taInd);
         SPutMsg(mBuf);
         RETVALUE(NULLP);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)taInd);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   
   pst->event = (Event) EVTTFUTIMINGADVIND;
   if (SPkU8(pst->event, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)taInd);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   
   cmFreeMem((Ptr)taInd);
   RETVALUE(mBuf);
}


#ifdef ANSI
PRIVATE Buffer *ysPalPkTfuSrInd
(
Pst * pst,
SuId suId,
TfuSrIndInfo * srInd
)
#else
PRIVATE Buffer *ysPalPkTfuSrInd(pst, suId, srInd)
Pst * pst;
SuId suId;
TfuSrIndInfo * srInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(ysPalPkTfuSrInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "SGetMsg() failed\n"));
      SPutSBuf(pst->region, pst->pool, (Data *)srInd, sizeof(TfuSrIndInfo));
      RETVALUE(NULLP);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuSrIndInfo(srInd, mBuf) != ROK) {
         YS_DBG_ERR((_ysp, "packing failed\n"));
         cmFreeMem((Ptr)srInd);
         SPutMsg(mBuf);
         RETVALUE(NULLP);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)srInd);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }

   pst->event = (Event) EVTTFUSRIND;
   if (SPkU8(pst->event, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)srInd);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }

   cmFreeMem((Ptr)srInd);
   RETVALUE(mBuf);
}

#ifdef ANSI
PRIVATE Buffer *ysPalPkTfuDatInd
(
Pst * pst,
SuId suId,
TfuDatIndInfo * datInd
)
#else
PRIVATE Buffer *ysPalPkTfuDatInd(pst, suId, datInd)
Pst * pst;
SuId suId;
TfuDatIndInfo * datInd;
#endif
{
   Buffer *mBuf = NULLP;
   TRC3(ysPalPkTfuDatInd)

   if (SGetMsg(pst->region, pst->pool, &mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "SGetMsg() failed\n"));
      SPutSBuf(pst->region, pst->pool, (Data *)datInd, sizeof(TfuDatIndInfo));
      RETVALUE(NULLP);
   }
   if (pst->selector == TFU_SEL_LC) {
      if (cmPkTfuDatIndInfo(datInd, mBuf) != ROK) {
         YS_DBG_ERR((_ysp, "packing failed\n"));
         cmFreeMem((Ptr)datInd);
         SPutMsg(mBuf);
         RETVALUE(NULLP);
      }
   }

   if (SPkS16(suId, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)datInd);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }

   pst->event = (Event) EVTTFUDATIND;
   if (SPkU8(pst->event, mBuf) != ROK) {
      YS_DBG_ERR((_ysp, "packing failed\n"));
      cmFreeMem((Ptr)datInd);
      SPutMsg(mBuf);
      RETVALUE(NULLP);
   }
   
   cmFreeMem((Ptr)datInd);
   RETVALUE(mBuf);
}
#endif /* LTE_PAL_ENB */

#endif /* SS_CAVIUM */

/********************************************************************30**
  
         End of file:     ys_pal_msg.c@@/main/2 - Thu Dec  2 02:27:19 2010
  
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
----------- -------- ---- -----------------------------------------------
/main/2      ---     sgm    1. eNodeB 1.2 release
/main/2    ys003.102 sgm    1. Fix for CID:1622-02-01 DefectId:ccpu00115333
                                adding Cell delete feature for PAL.
/main/2    ys005.102 pbyadgi 1. TIC_ID:ccpu00119532 : Fixed warning when YS_DEBUG 
                                flag is enabled.
*********************************************************************91*/
