


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing 
  
     File:     rgac_rgucb.c 
  
     Sid:      rgac_rgucb.c@@/main/3 - Sat Jul 30 02:21:03 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_rgucb.c
@brief This file contains the definitions for XTA RGU interface call 
handler functions. These functions are called from function defined in
rgac_rguhdl.c
*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_lte.h"        /* Common LTE Defines */
#include "cm_xta.h"        /* Common LTE Defines */
#include "rg_env.h"        /* MAC Environment Defines */
#include "crg.h"           /* CRG Interface defines */
#include "rgr.h"           /* RGR Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_acc.h"        /* MAC error defines */
#include "rgac_rgu.h"        /* MAC error defines */

/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timers */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"       /* memory management */
#include "cm_lte.x"        /* Common LTE Defines */
#include "cm_xta.x"        /* Common LTE Defines */
#include "crg.x"           /* CRG Interface includes */
#include "rgr.x"           /* RGR Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"        /* MAC error defines */
#include "rgac_rgu.x"        /* MAC error defines */



/* Solaris g++ compilation */
/* added the  ifdef __cplusplus to solve the anachronism */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


EXTERN   U32 gSimTti;
EXTERN   Bool startPfsSim;
EXTERN CmXtaTCCb*  rgAcRguTstCbFind ARGS((Void));
EXTERN S16 rgAcUtlFreeRguCb ARGS((CmXtaMsgQElm   *qElm));
EXTERN Void rgAcRguUtlGetUeIdFrmCrnti( CmLteRnti crnti, U8 *ueId);

#ifdef __cplusplus
}
#endif /* __cplusplus */


U8 crntiToUeId[32]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
U8 startCrnti[5] = {11,21,31,41,51};


/**
 * @brief XTA Bind Confirm Handler for RGU interface. 
 *
 * @details
 *
 *     Function : KwLiRguBndCfm
 *     
 *     Enqueues the Bind Confirm received from MAC to XTA queue. 
 *     
 *  @param[in] Pst  *pst 
 *  @param[in] SuId  suId 
 *  @param[in] U8  status 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 KwLiRguBndCfm
(
Pst            *pst,
SuId           suId,
U8             status
)
#else
PUBLIC S16 KwLiRguBndCfm(pst, suId, status)
Pst            *pst;
SuId           suId;
U8             status;
#endif
{
   TRC2(KwLiRguBndCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "KwLiRguBndCfm():\n"));

   pst->event = RGAC_RGU_EVTBNDCFM;

   rgAcRguSendMsg(pst, suId, status, NULLP);    

   RETVALUE(ROK);
} /* End of KwLiRguBndCfm */



/**
 * @brief XTA Common Channel Status Indication for RGU interface.
 *
 * @details
 *
 *     Function : KwLiRguCStaInd
 *     
 *     Enqueues the CStaInd received from MAC to XTA queue. 
 *     
 *  @param[in] Pst  *pst 
 *  @param[in] SuId  suId 
 *  @param[in] RguCStaIndInfo  *staInd 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 KwLiRguCStaInd
(
Pst            *pst,
SuId           suId,
RguCStaIndInfo *staInd
)
#else
PUBLIC S16 KwLiRguCStaInd(pst, suId, staInd)
Pst            *pst;
SuId           suId;
RguCStaIndInfo *staInd;
#endif
{
   TRC2(KwLiRguCStaInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "KwLiRguCStaInd():\n"));

   pst->event = RGAC_RGU_EVTCSTAIND;
 
   rgAcRguSendMsg(pst, suId, 0, staInd);    

   RETVALUE(ROK);
} /* End of KwLiRguCStaInd */

#ifdef LTE_L2_MEAS
/* TODO: Function Header */
#ifdef ANSI
PUBLIC S16 KwLiRguHqStaInd
(
Pst              *pst,
SuId             suId,
RguHarqStatusInd *harqStatusInd
)
#else
PUBLIC S16 KwLiRguHqStaInd(pst, suId, harqStatusInd)
Pst              *pst;
SuId             suId;
RguHarqStatusInd *harqStatusInd;
#endif
{
   TRC2(KwLiRguHqStaInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "KwLiRguHqStaInd():\n"));

   pst->event = RGAC_RGU_EVTHQSTAIND;
 
   rgAcRguSendMsg(pst, suId, 0, harqStatusInd);    

   RETVALUE(ROK);
}
#endif /* LTE_L2_MEAS */

/**
 * @brief XTA Dedicated Channel Status Indication for RGU interface.
 *
 * @details
 *
 *     Function : KwLiRguDStaInd
 *     
 *     Enqueues the DStaInd received from MAC to XTA queue. 
 *     
 *  @param[in] Pst  *pst 
 *  @param[in] SuId  suId 
 *  @param[in] RguDStaIndInfo  *staInd 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 KwLiRguDStaInd
(
Pst            *pst,
SuId           suId,
RguDStaIndInfo *staInd
)
#else
PUBLIC S16 KwLiRguDStaInd(pst, suId, staInd)
Pst            *pst;
SuId           suId;
RguDStaIndInfo *staInd;
#endif
{
#ifdef RGU_INF_OPTIMIZATION
   U8 idx;
   RguDStaIndInfo *staIndInfo;
#endif
   RguDStaIndPerUe *staIndPerUe;
   U32             id, j;
   S16             totBufSize;
   RgAcUeCb        *ueCb=NULLP;
   CmLteLcId       lcId;
   U8              ueId;
   
   TRC2(KwLiRguDStaInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "KwLiRguDStaInd():\n"));

   pst->event = RGAC_RGU_EVTDSTAIND;

   if(startPfsSim == TRUE)
   {
   printf("\nno of UE Scheduled =%d", staInd->nmbOfUeGrantPerTti);
   for(id=0; id<staInd->nmbOfUeGrantPerTti; id++)
   {
      staIndPerUe = &staInd->staInd[id];
      rgAcRguUtlGetUeIdFrmCrnti(staIndPerUe->rnti,&ueId);
      ueCb = &rgAccCb.acUeCb[ueId];
      for (j=0; j<staIndPerUe->staIndTb[0].nmbLch; j++)
      {
         lcId = staIndPerUe->staIndTb[0].lchStaInd[j].lcId;

         totBufSize =staIndPerUe->staIndTb[0].lchStaInd[j].totBufSize;
         ueCb->lcs[lcId].schdBo += totBufSize;
            printf("\nTB0:TTICount::%d Data Scheduled for CellId::%d UeId=%d:: CRNTI=%d LcId=::%d SchdData::%d TotalDataSize=%d\n", \
                  gSimTti, staInd->cellId, ueId, staIndPerUe->rnti, lcId, totBufSize, ueCb->lcs[lcId].schdBo);
      }
      for (j=0; j<staIndPerUe->staIndTb[1].nmbLch; j++)
      {
         lcId = staIndPerUe->staIndTb[1].lchStaInd[j].lcId;
         totBufSize =staIndPerUe->staIndTb[1].lchStaInd[j].totBufSize;
         ueCb->lcs[lcId].schdBo += totBufSize;
            printf("\nTB1:TTICount::%d Data Scheduled for CellId::%d UeId=%d:: CRNTI=%d LcId=::%d SchdData::%d TotalDataSize=%d\n", \
                  gSimTti, staInd->cellId, ueId, staIndPerUe->rnti, lcId, totBufSize, ueCb->lcs[lcId].schdBo);
      }
      totBufSize = 0;
   }
   RGAC_RGU_FREE_DSTAIND(staInd); 
   RETVALUE(ROK);
   }
#ifndef RGU_INF_OPTIMIZATION 
   rgAcRguSendMsg(pst, suId, 0, staInd);
#else
   /* Sending StaInd to XTA nmbOfUeGrantPerTti times as it expect it per UE*/
   for(idx = 0; idx < (staInd->nmbOfUeGrantPerTti); idx++)
   {
      if (SGetSBuf(0, 0, (Data **) &staIndInfo, sizeof(RguDStaIndInfo)) != ROK)
      {
         RGAC_RGU_FREE_DSTAIND(staInd); 
         RETVALUE(ROK);

      }
      /* copy data from pointer sent by mac to local pointer and sent to XTA queue*/
      cmMemcpy((U8 *)staIndInfo, (U8 *)staInd, 
            sizeof(RguDStaIndInfo));
      /* post staIndInfo to XTA */ 
      rgAcRguSendMsg(pst, suId, 0, staIndInfo);
   }
   /* de-allocate the staInd pointer sent by MAC */
   RGAC_RGU_FREE_DSTAIND(staInd); 
#endif

   RETVALUE(ROK);
} /* End of KwLiRguDStaInd */



/**
 * @brief XTA Common Channel Data Indication for RGU interface.
 *
 * @details
 *
 *     Function : KwLiRguCDatInd
 *     
 *     Enqueues the CDatInd received from MAC to XTA queue. 
 *     
 *  @param[in] Pst  *pst 
 *  @param[in] SuId  suId 
 *  @param[in] RguCDatIndInfo  *datInd 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 KwLiRguCDatInd
(
Pst            *pst,
SuId           suId,
RguCDatIndInfo *datInd
)
#else
PUBLIC S16 KwLiRguCDatInd(pst, suId, datInd)
Pst            *pst;
SuId           suId;
RguCDatIndInfo *datInd;
#endif
{
   TRC2(KwLiRguCDatInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "KwLiRguCDatInd():\n"));

   pst->event = RGAC_RGU_EVTCDATIND;
 
   rgAcRguSendMsg(pst, suId, 0, datInd);    

   RETVALUE(ROK);
} /* End of KwLiRguCDatInd */

#ifdef ANSI
PUBLIC S16 KwLiRguFlowCntrlInd
(
Pst            *pst,
SuId           suId,
RguFlowCntrlInd  *flowCntrlInd
)
#else
PUBLIC S16 KwLiRguFlowCntrlInd (pst, suId, flowCntrlInd)
(
Pst            *pst;
SuId           suId;
RguFlowCntrlInd  *flowCntrlInd;
)
#endif
{
   TRC2(KwLiRguFlowCntrlInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "KwLiRguFlowCntrlInd():\n"));

   pst->event = RGAC_RGU_EVTCDATIND;
 
   rgAcRguSendMsg(pst, suId, 0, flowCntrlInd);    

   RETVALUE(ROK);
}

/**
 * @brief XTA Dedicated Channel Data Indication for RGU interface.
 *
 * @details
 *
 *     Function : KwLiRguDDatInd
 *     
 *     Enqueues the DDatInd received from MAC to XTA queue. 
 *     
 *  @param[in] Pst  *pst 
 *  @param[in] SuId  suId 
 *  @param[in] RguDDatIndInfo  *datInd 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 KwLiRguDDatInd
(
Pst            *pst,
SuId           suId,
RguDDatIndInfo *datInd
)
#else
PUBLIC S16 KwLiRguDDatInd(pst, suId, datInd)
Pst            *pst;
SuId           suId;
RguDDatIndInfo *datInd;
#endif
{
   TRC2(KwLiRguDDatInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "KwLiRguDDatInd():\n"));

   pst->event = RGAC_RGU_EVTDDATIND;
 
   rgAcRguSendMsg(pst, suId, 0, datInd);    

   RETVALUE(ROK);
} /* End of KwLiRguDDatInd */



/**
 * @brief XTA Function to enqueue a interface primitive to Test Engine Queue.
 *
 * @details
 *
 *     Function : rgAcRguSendMsg
 *     
 *     Allocates a queue element data structure and fills in
 *     the appropriate primitive with additional information
 *     like free function pointer and enqueue it to the XTA queue. 
 *     
 *  @param[in] Pst  *pst 
 *  @param[in] SpId  suId 
 *  @param[in] Reason  reason 
 *  @param[in] Void  *ptr 
 *  @return  S16
 *      -# ROK 
 **/
#ifdef ANSI
PUBLIC S16 rgAcRguSendMsg
(
Pst            *pst,
SpId           suId,
Reason         reason,
Void           *ptr
)
#else
PUBLIC S16 rgAcRguSendMsg(pst, suId, reason, ptr)
Pst            *pst;
SpId           suId;
Reason         reason;
Void           *ptr;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   RgAccMsgQElm *rgMsg;
   RgAcRguInfo  *rguInfo;
   S16 ret = CMXTA_ERR_NONE;
 
   TRC2(rgAcRguSendMsg);
 
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the asmgciated test case */
   if ((tcCb = rgAcRguTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped RGAC_ENHANCE: may be Sts Ind etc...\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   rgMsg = NULLP;
   CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
   if (rgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcRguSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)rgMsg;
   qElm.msgFreeFun = rgAcUtlFreeRguCb;
   rguInfo = &(rgMsg->u.rguInfo);

   /*** fill the suId in the Q element****/
   rguInfo->suId = suId;
   rguInfo->event = pst->event;
   switch (pst->event) 
   {
      case RGAC_RGU_EVTCSTAIND:
      {
         RguCStaIndInfo  *sta;
         sta = (RguCStaIndInfo *)ptr;

         rguInfo->u.rguCStaInd = sta; 
         break;
      }
#ifdef LTE_L2_MEAS
      case RGAC_RGU_EVTHQSTAIND:
      {
         RguHarqStatusInd  *hqSta;
         hqSta = (RguHarqStatusInd *)ptr;

         rguInfo->u.rguHqStaInd = hqSta; 
         break;
      }
#endif /* LTE_L2_MEAS */
      case RGAC_RGU_EVTDSTAIND: 
      {
         RguDStaIndInfo  *sta;
         sta = (RguDStaIndInfo *)ptr;

         rguInfo->u.rguDStaInd = sta; 
         break;
      }
      case RGAC_RGU_EVTBNDCFM: 
      {
         rguInfo->status = reason;
         break;
      }
      case RGAC_RGU_EVTCDATIND:
      {
         RguCDatIndInfo  *dat;
         dat = (RguCDatIndInfo *)ptr;

         rguInfo->u.rguCDatInd = dat; 
         break;
      }
      case RGAC_RGU_EVTDDATIND: 
      {
         RguDDatIndInfo  *dat;
         dat = (RguDDatIndInfo *)ptr;

         rguInfo->u.rguDDatInd = dat; 
         break;
      }
      default:
         ret = CMXTA_ERR_INT;
   }/* end fo switch */

   if( ret == CMXTA_ERR_NONE)
   {
      /*-- Test case found, queue the message for the tcCb --*/
      /* Push it onto the message queue --*/
      (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
 
      /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not
        trigger the test engine now in that case, the test engine
        will RGAC_ENHANCE have a look at the queued message --*/
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   } 
   else
   {
      CMXTA_FREE(rgMsg, sizeof(RgAccMsgQElm));
   }
 
   RETVALUE(ret);
} /* end of rgAcRguSendMsg() */



/**
 * @brief XTA Function to test case association for a received message.
 *
 * @details
 *
 *     Function : rgAcRguTstCbFind
 *     
 *     Whenever a message is received from MAC to Dummy-RLC, this 
 *     function is called to check if this is associated to a running 
 *     test case. If test case shut down is done, then any message
 *     received there after is discarded as a spurious message.
 *     
 *  @return  CmXtaTCCb*
 *      -# NULLP
 *      -# CmXtaTCCb*
 **/
#ifdef ANSI
PUBLIC CmXtaTCCb*  rgAcRguTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  rgAcRguTstCbFind ()
#endif
{
   TRC2(rgAcRguTstCbFind);
 
   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change SOAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif
 
   RETVALUE(NULLP);
} /* End of rgAcRguTstCbFind */



/**
 * @brief XTA Function to free resources aquired by the interface messages
 * received from MAC to Dummy-RLC.
 *
 * @details
 *
 *     Function : rgAcUtlFreeRguCb
 *     
 *     A pointer to this function is registered with each 
 *     Queue element that gets enqueued as part of its call
 *     handler functionality. After the interface primitive 
 *     validation is done by the validation handler, the queue
 *     element is flushed, this function gets invoked as part
 *     of this flushing. Based on type of primitive, the memory
 *     freeing takes place.
 *     
 *  @param[in] CmXtaMsgQElm  *qElm 
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 rgAcUtlFreeRguCb
(
CmXtaMsgQElm   *qElm
)
#else
PUBLIC S16 rgAcUtlFreeRguCb(qElm)
CmXtaMsgQElm   *qElm;
#endif /* ANSI */
{
   RgAccMsgQElm *rgMsg;
   U8            idx;
   U8            pduIdx;
 
   TRC2(rgAcUtlFreeRguCb);
 
   CMXTA_DBG_PARAM((_cmxtap, "rgAcUtlFreeRguCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   rgMsg = (RgAccMsgQElm *)qElm->data;
  
   if(rgMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   switch (rgMsg->u.rguInfo.event)
   {
      case RGAC_RGU_EVTCDATIND:
         SPutMsg(rgMsg->u.rguInfo.u.rguCDatInd->pdu);
         RGAC_RGU_FREE_CDATIND(rgMsg->u.rguInfo.u.rguCDatInd);
         break;
      case RGAC_RGU_EVTBNDCFM:
         break;
      case RGAC_RGU_EVTDDATIND:
         for (idx = 0; idx < rgMsg->u.rguInfo.u.rguDDatInd->numLch; idx++)
         {
            for (pduIdx = 0; pduIdx < rgMsg->u.rguInfo.u.rguDDatInd->lchData[idx].pdu.numPdu; pduIdx++)
            {
               SPutMsg(rgMsg->u.rguInfo.u.rguDDatInd->lchData[idx].pdu.mBuf[pduIdx]);
            }
         }
         RGAC_RGU_FREE_DDATIND(rgMsg->u.rguInfo.u.rguDDatInd);
         break;
      case RGAC_RGU_EVTCSTAIND:
         RGAC_RGU_FREE_CSTAIND(rgMsg->u.rguInfo.u.rguCStaInd);
         break;
      case RGAC_RGU_EVTDSTAIND:
         RGAC_RGU_FREE_DSTAIND(rgMsg->u.rguInfo.u.rguDStaInd);
         break;
#ifdef LTE_L2_MEAS
      case RGAC_RGU_EVTHQSTAIND:
         RGAC_RGU_FREE_HQSTAIND(rgMsg->u.rguInfo.u.rguHqStaInd);
         break;
#endif
      default : 
         RETVALUE(CMXTA_ERR_INT);
   }
   
   if (rgMsg != NULLP)
   {
      CMXTA_FREE(rgMsg, sizeof (RgAccMsgQElm));
      qElm->data = NULLP;
   }
 
   RETVALUE(CMXTA_ERR_NONE);
} /* End of rgAcUtlFreeRguCb() */



/**********************************************************************
 
         End of file:     rgac_rgucb.c@@/main/3 - Sat Jul 30 02:21:03 2011
 
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
/main/1      ---     sm                1. Initial Release.
/main/2      ---     sm                1. LTE MAC 2.1 release
         rg003.201   ns                1. Trace added for functions.
/main/3      ---     dvasisht      1. Updated for LTE MAC Release 3.1
$SID$        ---     rt            1. LTE MAC 4.1 release
*********************************************************************91*/
