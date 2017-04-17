

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing 
  
     File:     rgac_rguutl.c 
  
     Sid:      rgac_rguutl.c@@/main/3 - Sat Jul 30 02:21:06 2011
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_rguutl.c
@brief This file contains the definitions for utility functions required 
by the handlers of XTA RGU interface
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
#include <stdlib.h>

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



/**
 * @brief XTA Utility function to allocate and fill a Common
 * Channel Data Request Primitive. 
 *
 * @details
 *
 *     Function : rgAcUtlRguGenCDatReq
 *     
 *     Allocates and fills a Common Channel Data Request Primitive. 
 *     
 *  @param[out] RguCDatReqInfo  *datReq 
 *  @param[in] CmLteCellId  cellId 
 *  @param[in] CmLteLcId  lcId 
 *  @param[in] CmLteLcType  lcType 
 *  @param[in] CmLteTimingInfo  timingInfo 
 *  @param[in] CmLteRnti  rnti 
 *  @param[in] U32  bufSize 
 *  @param[in] U32  transId 
 *  @param[in] Bool sendNoMatter
 *  @param[in] U8   bcchIdx 
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 rgAcUtlRguGenCDatReq
(
RguCDatReqInfo  *datReq,
CmLteCellId     cellId,
CmLteLcId       lcId,
CmLteLcType     lcType,
CmLteTimingInfo *timingInfo,
CmLteRnti       rnti,
U32             bufSize,
U32             transId,
Bool            sendNoMatter,
U8              bcchIdx
)
#else
PUBLIC S16 rgAcUtlRguGenCDatReq(datReq, cellId, lcId, lcType, timingInfo,
rnti, bufSize, transId, sendNoMatter, bcchIdx)
RguCDatReqInfo  *datReq;
CmLteCellId     cellId;
CmLteLcId       lcId;
CmLteLcType     lcType;
CmLteTimingInfo *timingInfo;
CmLteRnti       rnti;
U32             bufSize;
U32             transId;
Bool            sendNoMatter;
U8              bcchIdx;
#endif    
{
   U32 staCount; 

   TRC2(rgAcUtlRguGenCDatReq);
   
   datReq->cellId = cellId;
   datReq->lcId = lcId;
   datReq->lcType = lcType;
   
   for(staCount = 0; staCount < rgAccCb.rgAcRguCb.nmbCSta; staCount++)
   {
      if ((lcId == rgAccCb.rgAcRguCb.rguCStaInfo[staCount].lcId) &&
          (cellId == rgAccCb.rgAcRguCb.rguCStaInfo[staCount].cellId) &&
          (rgAccCb.rgAcRguCb.rguCStaInfo[staCount].state == 1))
      {
        rgAccCb.rgAcRguCb.rguCStaInfo[staCount].state = 2; /* DatReq is sent */
        break;
      }
   }
   if (sendNoMatter)
   {
      staCount = 0; /* send some junk */
   }
   else if (staCount == rgAccCb.rgAcRguCb.nmbCSta) 
   {
      RETVALUE(RFAILED);
   }

   if ((rnti == 0) || ((timingInfo->sfn == 0) ||
      (timingInfo->subframe == 0)))
   {
      /* Consider default Info from previous sta */

      if ((datReq->lcType == CM_LTE_LCH_BCCH) || (datReq->lcType == CM_LTE_LCH_PCCH))
      {
         datReq->u.timeToTx.sfn = 
         rgAccCb.rgAcRguCb.rguCStaInfo[staCount].u.timeToTx.sfn;
         datReq->u.timeToTx.subframe = 
         rgAccCb.rgAcRguCb.rguCStaInfo[staCount].u.timeToTx.subframe;
      }
      else /* if CCCH */
      {
         datReq->u.rnti = rnti;
         /* Resolution Id dont care */
      }
   }
   else /* Tester wishes to provide his own data */
   {
      if ((datReq->lcType == CM_LTE_LCH_BCCH) || (datReq->lcType == CM_LTE_LCH_PCCH))
      {
         datReq->u.timeToTx.sfn = timingInfo->sfn;
         datReq->u.timeToTx.subframe = timingInfo->subframe;
      }
      else /* if CCCH */
      {
         datReq->u.rnti = rnti;
      }
   }
   if (bufSize == 0)
      /* if tester doesn't provide take stainfo->bo as bufsize */
      {RGAC_RGU_DAT_GETBUF(datReq->pdu, 
                 rgAccCb.rgAcRguCb.rguCStaInfo[staCount].bo);}
   else
      {RGAC_RGU_DAT_GETBUF(datReq->pdu, bufSize);}
   if (rgAccCb.bcchBuf[bcchIdx] != NULLP)
   {
      SPutMsg(rgAccCb.bcchBuf[bcchIdx]);
      rgAccCb.bcchBuf[bcchIdx] = NULLP;
   }
   if ((SCpyMsgMsg (datReq->pdu, CMXTA_TSTREG, 
               CMXTA_TSTPOOL, &(rgAccCb.bcchBuf[bcchIdx]))) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "rgAcUtlRguGenCDatReq(): resource error\n"));
      RETVALUE(RFAILED);
   }
   if (transId == 0)
      /* if tester doesn't provide take stainfo->transId */
      datReq->transId = rgAccCb.rgAcRguCb.rguCStaInfo[staCount].transId;
   else
      datReq->transId = transId;
      
   RETVALUE(ROK);
 
}/*-- rgAcUtlRguGenCDatReq --*/



/**
 * @brief XTA Utility function to allocate and fill a Dedicated
 * Channel Data Request Primitive. 
 *
 * @details
 *
 *     Function : rgAcUtlRguGenDDatReq
 *     
 *     Allocates and fills a Dedicated Channel Data Request Primitive. 
 *     
 *  @param[out] RguCDatReqInfo  *datReq 
 *  @param[in] CmLteCellId  cellId 
 *  @param[in] CmLteRnti  rnti 
 *  @param[in] U32  transId 
 *  @param[in] U8  numLch 
 *  @param[in] RguLchDatReq  *lchData 
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/
#ifdef LTE_L2_MEAS
#ifdef ANSI
PUBLIC S16 rgAcUtlRguGenDDatReq
(
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
#ifndef RGU_INF_OPTIMIZATION
RguDDatReqInfo  *datReq,
#else
RguDDatReqInfo  *datReqInfo,
#endif
CmLteCellId     cellId,
U8              ueId,
CmLteRnti       rnti,
U32             transId,
U8              numLch,
RguLchDatReq    *lchData,
U8              sndLess,
U8              isMeasTypeDlTpt
)
#else
PUBLIC S16 rgAcUtlRguGenDDatReq(tcCb, spCb, datReq, cellId, ueId, rnti, transId, numLch, lchData, sndLess, isMeasTypeDlTpt)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
#ifndef RGU_INF_OPTIMIZATION
RguDDatReqInfo  *datReq;
#else
RguDDatReqInfo  *datReqInfo;
#endif
CmLteCellId     cellId;
U8              ueId;
CmLteRnti       rnti;
U32             transId;
U8              numLch;
RguLchDatReq    *lchData;
U8              sndLess;
U8              isMeasTypeDlTpt;
#endif
#else
#ifdef ANSI
PUBLIC S16 rgAcUtlRguGenDDatReq
(
#ifndef RGU_INF_OPTIMIZATION
RguDDatReqInfo  *datReq,
#else
RguDDatReqInfo  *datReqInfo,
#endif
CmLteCellId     cellId,
U8              ueId,
CmLteRnti       rnti,
U32             transId,
U8              numLch,
RguLchDatReq    *lchData,
U8              sndLess
)
#else
PUBLIC S16 rgAcUtlRguGenDDatReq(datReq, cellId, ueId, rnti, transId, numLch, lchData, sndLess)
#ifndef RGU_INF_OPTIMIZATION
RguDDatReqInfo  *datReq;
#else
RguDDatReqInfo  *datReqInfo;
#endif
CmLteCellId     cellId;
U8              ueId;
CmLteRnti       rnti;
U32             transId;
U8              numLch;
RguLchDatReq    *lchData;
U8              sndLess;
#endif    
#endif    
{
   U32            count=0;
#ifndef RGU_INF_OPTIMIZATION
   RguDStaIndInfo *dSta;
#else
   RguDStaIndInfo *dStaInfo;
   RguDStaIndPerUe *dSta;
   RguDDatReqPerUe *datReq;
   U8 idx;
#endif
   RgAcUeCb       *ueCb;
   CmLList        *node;
   U16            lcId;

   TRC2(rgAcUtlRguGenDDatReq);
   
   UNUSED(transId);
   UNUSED(numLch);
   UNUSED(lchData);

#ifndef RGU_INF_OPTIMIZATION
   datReq->cellId = cellId;
#else
   datReqInfo->cellId = cellId;
#endif
#ifndef LTEMAC_MIMO
   datReq->nmbOfTbs = 1; 
#endif
  
   ueCb = &rgAccCb.acUeCb[ueId];
#ifndef RGU_INF_OPTIMIZATION
   dSta = (RguDStaIndInfo *)ueCb->staIndLst.first->node;
   datReq->rnti = rnti;
#else
   dStaInfo = (RguDStaIndInfo *)ueCb->staIndLst.first->node;
   for(idx =0; idx < dStaInfo->nmbOfUeGrantPerTti; idx++)
   {
      dSta = &(dStaInfo->staInd[idx]);
      if (rnti == (dSta->rnti))
      {
         datReq = &(datReqInfo->datReq[idx]);
         datReq->rnti = rnti;
         break;
      }
   }
   if(idx == (dStaInfo->nmbOfUeGrantPerTti))
   {
      /* If RNTI is not matched then delete node and dStaInd pointer*/
      node = ueCb->staIndLst.first;
      cmLListDelFrm(&ueCb->staIndLst, ueCb->staIndLst.first);
      SPutSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
               (Data *)node, sizeof(*node));
      SPutSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
            (Data *)dStaInfo, sizeof(RguDStaIndInfo));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
   
   datReqInfo->nmbOfUeGrantPerTti = dStaInfo->nmbOfUeGrantPerTti;

#endif
   node = ueCb->staIndLst.first;
   cmLListDelFrm(&ueCb->staIndLst, ueCb->staIndLst.first);
   SPutSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
               (Data *)node, sizeof(*node));
   datReq->transId = dSta->transId;
   datReq->datReqTb[0].nmbLch  = dSta->staIndTb[0].nmbLch;
#ifdef LTEMAC_MIMO
   if (dSta->staIndTb[0].nmbLch > 0)
   {
      datReq->nmbOfTbs++; 
   }
#endif
#ifdef LTE_L2_MEAS
   datReq->datReqTb[0].tbId = 0;
#endif
   for (count = 0; count < dSta->staIndTb[0].nmbLch; count++)
   {
      datReq->datReqTb[0].lchData[count].lcId = dSta->staIndTb[0].lchStaInd[count].lcId;
      lcId = dSta->staIndTb[0].lchStaInd[count].lcId;
      datReq->datReqTb[0].lchData[count].boReport.bo = ueCb->lcs[lcId].bo;
      datReq->datReqTb[0].lchData[count].pdu.numPdu = 1;
      /* If we are forcing less data to go out, in order to check padding */
      if (sndLess != 0)
      {
#ifdef CCPU_OPT
         /* deduct 3 assuming MAC header estimate */
         RGAC_RGU_DAT_GETBUF(datReq->datReqTb[0].lchData[count].pdu.mBuf[0], 
               (dSta->staIndTb[0].lchStaInd[count].totBufSize - sndLess - 2 - 3));
         /* deduct 3 assuming MAC header estimate */
#else
         RGAC_RGU_DAT_GETBUF(datReq->datReqTb[0].lchData[count].pdu.mBuf[0], 
               (dSta->staIndTb[0].lchStaInd[count].totBufSize + 15 - sndLess - 3));
#endif
      }
      else
      {
         /* deduct 3 assuming MAC header estimate */
#ifdef CCPU_OPT
         RGAC_RGU_DAT_GETBUF(datReq->datReqTb[0].lchData[count].pdu.mBuf[0], 
               (dSta->staIndTb[0].lchStaInd[count].totBufSize - 2 - 3));
#else
         /* deduct 3 assuming MAC header estimate */
         RGAC_RGU_DAT_GETBUF(datReq->datReqTb[0].lchData[count].pdu.mBuf[0], 
               (dSta->staIndTb[0].lchStaInd[count].totBufSize - 3));
#endif
      }
   }

#ifdef LTEMAC_MIMO
   datReq->datReqTb[1].nmbLch  = dSta->staIndTb[1].nmbLch;
   if (dSta->staIndTb[1].nmbLch > 0)
   {
      datReq->nmbOfTbs++; 
   }
#ifdef LTE_L2_MEAS
   if(datReq->nmbOfTbs == 2)
   {
     datReq->datReqTb[1].tbId = 1;
   }
   if (isMeasTypeDlTpt == 0)
   {
     datReq->datReqTb[0].tbId = RGU_INVALID_TBID;
     datReq->datReqTb[1].tbId = RGU_INVALID_TBID;
   }
#endif
   for (count = 0; count < dSta->staIndTb[1].nmbLch; count++)
   {
      datReq->datReqTb[1].lchData[count].lcId = dSta->staIndTb[1].lchStaInd[count].lcId;
      lcId = dSta->staIndTb[1].lchStaInd[count].lcId;
      datReq->datReqTb[1].lchData[count].boReport.bo = ueCb->lcs[lcId].bo;
      datReq->datReqTb[1].lchData[count].pdu.numPdu = 1;
      /* If we are forcing less data to go out, in order to check padding */
      if (sndLess != 0)
      {
#ifdef CCPU_OPT
         /* deduct 3 assuming MAC header estimate */
         RGAC_RGU_DAT_GETBUF(datReq->datReqTb[1].lchData[count].pdu.mBuf[0], 
               (dSta->staIndTb[1].lchStaInd[count].totBufSize - sndLess - 2 - 3));
         /* deduct 3 assuming MAC header estimate */
#else
         RGAC_RGU_DAT_GETBUF(datReq->datReqTb[1].lchData[count].pdu.mBuf[0], 
               (dSta->staIndTb[1].lchStaInd[count].totBufSize + 15 - sndLess - 3));
#endif
      }
      else
      {
         /* deduct 3 assuming MAC header estimate */
#ifdef CCPU_OPT
         RGAC_RGU_DAT_GETBUF(datReq->datReqTb[1].lchData[count].pdu.mBuf[0], 
               (dSta->staIndTb[1].lchStaInd[count].totBufSize - 2 - 3));
#else
         /* deduct 3 assuming MAC header estimate */
         RGAC_RGU_DAT_GETBUF(datReq->datReqTb[1].lchData[count].pdu.mBuf[0], 
               (dSta->staIndTb[1].lchStaInd[count].totBufSize - 3));
#endif
      }
   }
  datReq->nmbOfTbs = dSta->nmbOfTbs;  
#endif
#ifndef RGU_INF_OPTIMIZATION
   SPutSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
               (Data *)dSta, sizeof(RguDStaIndInfo));
#else
   SPutSBuf(RGAC_RGU_DFLTRGN, RGAC_RGU_DFLTPOOL, 
               (Data *)dStaInfo, sizeof(RguDStaIndInfo));
#endif
   RETVALUE(ROK);
}/*-- rgAcUtlRguGenDDatReq --*/

PUBLIC Void rgAcRguUtlGetUeIdFrmCrnti
(
 CmLteRnti  crnti,
 U8         *ueId
)
{
   U8   ueIdx=0;
   for(;ueIdx<RG_ACC_MAX_UE; ueIdx++)
   {
      if(rgAccCb.acUeCb[ueIdx].crnti == crnti)
      {
         *ueId = ueIdx;
         RETVOID;
      }
   }
}

/**********************************************************************
 
         End of file:     rgac_rguutl.c@@/main/3 - Sat Jul 30 02:21:06 2011
 
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
           rg007.201   ap  1. Added support for MIMO
/main/3      ---       nu  1. Updated for release LTE-MAC 3.1.
           rg002.301   asehgal  1.ccpu00119494-corrected the numOfTbs updation
/main/4      ---           1. LTE MAC 4.1 release
*********************************************************************91*/
