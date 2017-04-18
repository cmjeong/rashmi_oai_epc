

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_pjucb.c

     Sid:      kwac_pjuutl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:38 2014

     Prg:     cp
*********************************************************************21*/

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
#include "pju.h"           /* PJU defines */
#include "rgu.h"           /* RGU defines */
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_kwu.h"      /* KWU Acceptance defines */
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_pju.h"      /* PJU Acceptance defines */

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
#include "pju.x"           /* PJU */
#include "rgu.x"           /* RGU */
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_pju.x"      /* CKW Acceptance defines */


#ifdef KW_PDCP
/**
@brief Utility Function to Build data request
@param[in] datReq    -  Data Request Information
@param[in] mBuf      -  SDU mBuf
@param[in] sduSize   -  SDU size

@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlCpyPjuDatReq 
(
CmLtePdcpId    *pdcpId,
U32            *sduId,
Buffer         *mBuf,
U16            sduSize,
U8             entity
)
#else
PUBLIC S16 kwAcUtlCpyPjuDatReq(pdcpId, sduId, mBuf, sduSize, entity)
CmLtePdcpId    *pdcpId;
U32            *sduId;
Buffer         *mBuf;
U16            sduSize;
U8             entity;
#endif
{
   KwAcPjuDatReq     *tDatReq = NULLP;

   TRC2(kwAcUtlCpyPjuDatReq);

   /* Get the kwAcCb.xxPjuCb.datReq Q node pointer
    * and fill the information from datReq to verify
    * at datInd
    */
   if (entity == ENTNH)
   {
      tDatReq = &(kwAcCb.nhPjuCb.datReq.node[\
            kwAcUtlPjuDatReqCircQEnqueue(&kwAcCb.nhPjuCb.datReq)]);
      tDatReq->entity = ENTNH;
   }
   else
   {
      tDatReq = &(kwAcCb.pxPjuCb.datReq.node[\
            kwAcUtlPjuDatReqCircQEnqueue(&kwAcCb.pxPjuCb.datReq)]);
      tDatReq->entity = ENTPX;
   }

   /* Fill kwAcCb.pjuCb.datReq Q node */
   if (tDatReq != NULLP)
   {
      tDatReq->isInQ = TRUE;
      tDatReq->sduSize = sduSize;
   }
   else
   {
      CMXTA_DBG_PARAM((_cmxtap, "Failed - tDatReq is NULLP.\n"));
      RETVALUE(CMXTA_ERR_INT);
   }


   /* Copy mBuf to kwAcCb.pjuCb.datReq Q */
   KWAC_CPY_MBUF(mBuf, tDatReq->mBuf);

   /* As kwAcCb.pjuCb.datReq is array and static,
    * We can use cmMemcpy to copy the structure
    */
   cmMemcpy((U8 *)&tDatReq->pdcpId, (U8 *)pdcpId, sizeof(CmLtePdcpId));
   tDatReq->sduId = *sduId;

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCpyPjuDatReq */


/**
@brief Utility Function to Build data request
@param[in]  tcCb       -  Test Case Control Block
@param[in]  spCb       -  XML DOM Control Block
@param[out] pdcpId     -  Data Request Information
@param[out] mBuf       -  SDU mBuf

@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlBuildPjuDatReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CmLtePdcpId    *pdcpId,
U32            *sduId,
Buffer         **mBuf,
U8             entity
)
#else
PUBLIC S16 kwAcUtlBuildPjuDatReq(tcCb, spCb, pdcpId, sduId, mBuf, entity)
CmXtaTCCb      *tcCb;    /* tcCb data structure  */
CmXtaSpCb      *spCb;
CmLtePdcpId    *pdcpId;
U32            *sduId;
Buffer         **mBuf;
U8             entity;
#endif
{
   U8       sData;
   U8       data[KWAC_PJU_MAX_FLAT_BUF_SIZE];
   U16      sduSize;
   U16      tmpCnt;
 
   TRC2(kwAcUtlBuildPjuDatReq);

   sData = 0x7F;
   sduSize = 0;
   tmpCnt = 0;

   CMXTA_ZERO(data, sizeof(data));
            
   /*
    * <tapa.pju.datreq rbId="1" ueId="1" cellId="1" rbType="1" sduSize="300"
    * entity="ENTNH"
    *
    * intInitFail="FALSE"
    * intProtFail="FALSE"
    * intVerFail="FALSE"
    * cipInitFail="FALSE"
    * cipFail="FALSE"
    * decipFail="FALSE"
    * cmpInitFail="FALSE"
    * cmpFail="FALSE"
    * decmpFail="FALSE"
    *
    * saveCpMsg="FALSE"
    * saveCmpMsg="FALSE"
    * saveIntMsg="FALSE"
    * />
    */
   /* fill CmLteRlcId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(pdcpId->rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(pdcpId->rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(pdcpId->ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(pdcpId->cellId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "sduSize", &(sduSize));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sData", &(sData));

   /* Allocate memory for SDU mBuf */
   if (SGetMsg(DFLT_REGION, DFLT_POOL, mBuf) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcUtlBuildPjuDatReq(): resource unavailble \n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } /* end of if statement */

   if (sduSize > PJ_MAX_SDU_SIZE)
   {
      tmpCnt = sduSize / 3000;

      KWAC_FORM_SDU(data, (sduSize % 3000), sData, mBuf);

      while (tmpCnt > 0)
      {
         KWAC_FORM_SDU(data, 3000, sData, mBuf);
         tmpCnt--;
      }
   }
   else
   {
      KWAC_FORM_SDU(data, sduSize, sData, mBuf);
   }

   /* Fill SDU ID from kwAcCb.pjuCb.nxtSduId */
   if (entity == ENTNH)
   {
      *sduId = kwAcCb.nhPjuCb.nxtSduId;
      kwAcCb.nhPjuCb.nxtSduId++;
   }
   else
   {
      *sduId = kwAcCb.pxPjuCb.nxtSduId;
      kwAcCb.pxPjuCb.nxtSduId++;
   }

   /* Copy datReq to kwAcCb.pxPjuCb/pjuCb */
   if (kwAcUtlCpyPjuDatReq(pdcpId, sduId, *mBuf, sduSize, entity) != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Store tcCb and spCb to fetch Off-board attributes in
    * Off-board acceptance code kwac_libcb.c in DL
    */
   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlBuildPjuDatReq */

#ifdef ANSI
PUBLIC S16 kwAcUtlCmpPjuDatReqBuf
(
Buffer *srcBuf,
Buffer *dstBuf,
U32    size
)
#else
PUBLIC S16 kwAcUtlCmpPjuDatReqBuf(srcBuf, dstBuf, size)
Buffer *srcBuf;
Buffer *dstBuf;
U32    size;
#endif
{
   Data     srcData[8190], dstData[8190];
   MsgLen   srcLen = 0, dstLen = 0, len = 0;
   S16      idx = 0;

   CMXTA_ZERO(srcData, sizeof(srcData));
   CMXTA_ZERO(srcData, sizeof(dstData));

   if (srcBuf == NULLP)
   {
      CMXTA_DBG_PARAM((_cmxtap, "Failed - SDU Verification: srcBuf is NULLP.\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   if (dstBuf == NULLP)
   {
      CMXTA_DBG_PARAM((_cmxtap, "Failed - SDU Verification: dstBuf is NULLP.\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   SFndLenMsg(srcBuf, &srcLen);
   SFndLenMsg(dstBuf, &dstLen);
   
   SCpyMsgFix(srcBuf, 0, srcLen, srcData, &len);
   SCpyMsgFix(dstBuf, 0, dstLen, dstData, &len);

   if (srcLen == dstLen)
   {
      for (idx = 0; idx < srcLen; idx++)
      {
         if (srcData[idx] != dstData[idx])
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed - SDU Verification: idx in SDU is (%d)\n",
                     idx), 2);
            RETVALUE(CMXTA_ERR_INT);
         }
      }
   }
   else
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - SDU Length Mismatch: srcLen (%d) \
               dstLen (%d)\n",
               srcLen, dstLen), 2);
      RETVALUE(CMXTA_ERR_INT);
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCmpPjuDatReqBuf */


/**
 * @brief Validate PJU Data Indication
 *
 * @details
 *
 *     Function : kwAcUtlValdtPjuDatInd
 *
 *     This function Validates CkwCfgCfmInfo structure recieved from RLC
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *kwElm
 *  @param[in]  *entity
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlValdtPjuDatInd
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwAcMsgQElm       *kwElm,
U8                entity
)
#else
PUBLIC S16 kwAcUtlValdtPjuDatInd(tcCb, spCb, kwElm, entity)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
KwAcMsgQElm       *kwElm;
U8                entity;
#endif
{
   KwAcPjuDatReq        *datReq;
   Buffer               *mBuf;
   CmLteRlcId           *rlcId = NULLP;
   CmLtePdcpId          *pdcpId = NULLP;
   CmLteRnti            tCrnti;
   S16                  idx;
   S32                  sduId;
   U8                   valdType = 0;

   TRC2(kwAcUtlValdtPjuDatInd);

   tCrnti = 0;
   sduId = -1;
   mBuf = kwElm->mBuf;
   pdcpId = kwElm->u.pjuInfo.pdcpId;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "valdType", &(valdType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "sduId", &(sduId));

   if (valdType == 1)
   {
      RETVALUE(CMXTA_ERR_NONE);
   }

   for(idx = 0; idx < kwAcCb.mapDlUlCb.count; idx++)
   {
      if(kwAcCb.mapDlUlCb.mapDlUl[idx].ueId == pdcpId->ueId &&
         kwAcCb.mapDlUlCb.mapDlUl[idx].cellId ==  pdcpId->cellId)
      {
         if (entity == ENTNH || entity == ENTPX )
         {
            rlcId = &(kwAcCb.mapDlUlCb.mapDlUl[idx].\
                  srbCb[(pdcpId->rbId)].othRlcId);   
         }
#ifdef KW_PDCP
         else
         {
            CMXTA_DBG_PARAM((_cmxtap, "Failed - rlcId mapping not found.\n"));
            RETVALUE(CMXTA_ERR_INT);
         }
#else
         else
         {
            if (datInd->rlcId.rbType == CM_LTE_SRB)
            {
               rlcId = &(kwAcCb.mapDlUlCb.mapDlUl[idx].\
                     srbCb[(pdcpId->rbId)].othRlcId);   
            }
            else
            {
               rlcId = &(kwAcCb.mapDlUlCb.mapDlUl[idx].\
                     drbCb[(pdcpId->rbId)].othRlcId);   
            }
         }
#endif /* KW_PDCP */
         break;
      }
   }

   /* get rlc id */
   if (entity == ENTNH)
   {
      idx = kwAcUtlPjuDatReqCircQGetFront(&kwAcCb.nhPjuCb.datReq);
      do
      {
          datReq = &kwAcCb.nhPjuCb.datReq.node[idx];
          if (rlcId && ((rlcId->ueId == datReq->pdcpId.ueId) &&
              (rlcId->cellId == datReq->pdcpId.cellId) &&
              (rlcId->rbId == datReq->pdcpId.rbId)))  
          {
              if (sduId == -1 || sduId == (S32)datReq->sduId)
                 break;
              
          }
          idx = kwAcUtlPjuDatReqCircQGetNext(&kwAcCb.nhPjuCb.datReq, idx);
      } while (idx);
      if (!idx)
      {
         CMXTA_DBG_PARAM((_cmxtap, "Failed - idx not found\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else
   {
      idx = kwAcUtlPjuDatReqCircQGetFront(&kwAcCb.pxPjuCb.datReq);
      do
      {
          datReq = &kwAcCb.pxPjuCb.datReq.node[idx];
          if (rlcId && ((rlcId->ueId == datReq->pdcpId.ueId) &&
              (rlcId->cellId == datReq->pdcpId.cellId) &&
              (rlcId->rbId == datReq->pdcpId.rbId)))  
          {
              if (sduId == -1 || sduId == (S32)datReq->sduId)
                 break;
              
          }
          idx = kwAcUtlPjuDatReqCircQGetNext(&kwAcCb.pxPjuCb.datReq, idx);
      } while (idx);
      if (!idx)
      {
         CMXTA_DBG_PARAM((_cmxtap, "Failed - idx not found\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }  
 
   /* validate buffer */
   if (kwAcUtlCmpPjuDatReqBuf(datReq->mBuf, mBuf, datReq->sduSize) !=
         CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,
               "kwAcUtlCmpPjuDatReqBuf(): mBuf comarision Failed.\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Free the Buffers and datInd */
   KW_FREE_BUF(datReq->mBuf);                /*free the stored mBuf */

   /* Memset to 0 for datReq
    * This make isInQ flag to 0 (FALSE) */
   CMXTA_ZERO(datReq, sizeof(KwAcPjuDatReq));/* Memset to 0 for datReq */

   /* Remove the msg from datReq Q if possible */
   if (entity ==ENTNH)
   {
      kwAcUtlPjuDatReqCircQDequeue(&kwAcCb.nhPjuCb.datReq);
   }
   else
   {
      kwAcUtlPjuDatReqCircQDequeue(&kwAcCb.pxPjuCb.datReq);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlValdtPjuDatInd */


/**
@brief utility function for releasing CmXtaMsgQElm
@param qElm
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlPjuFreeCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 kwAcUtlPjuFreeCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   KwAcMsgQElm *kwElm;

   TRC2(kwAcUtlPjuFreeCb);

   CMXTA_DBG_PARAM((_cmxtap, "kwAcUtlPjuFreeCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   if(kwElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   switch (qElm->pst.event)
   {
      case EVTPJUBNDCFM:
         break;
      case EVTPJUDATIND:
         KW_FREE_ACC(kwElm->u.pjuInfo.pdcpId, sizeof(CmLtePdcpId));
         break;
      case EVTPJUDATCFM:
         KW_FREE_ACC(kwElm->u.pjuInfo.u.datCfm, sizeof(PjuDatCfmInfo));
         KW_FREE_ACC(kwElm->u.pjuInfo.pdcpId, sizeof(CmLtePdcpId));
         break;
      case EVTPJUSTAIND:
         KW_FREE_ACC(kwElm->u.pjuInfo.u.staInd, sizeof(PjuStaIndInfo));
         KW_FREE_ACC(kwElm->u.pjuInfo.pdcpId, sizeof(CmLtePdcpId));
         break;
      case EVTPJUDATFWDIND:
      {
         U16 i = 0;
         for ( i = 0; i < kwElm->u.pjuInfo.u.datFwdInd->numSdus; i++)
         {
            KW_FREE_BUF(kwElm->u.pjuInfo.u.datFwdInd->datFwdInfo[i].sdu);
         }

         KW_FREE_ACC(kwElm->u.pjuInfo.u.datFwdInd->datFwdInfo,
               kwElm->u.pjuInfo.u.datFwdInd->numSdus * sizeof(PjuDatFwdInfo));

         KW_FREE_ACC(kwElm->u.pjuInfo.u.datFwdInd, sizeof(PjuDatFwdIndInfo));
         KW_FREE_ACC(kwElm->u.pjuInfo.pdcpId, sizeof(CmLtePdcpId));
      }
         break;
      default:
         CMXTA_DBG_CALLIND((_cmxtap, "Failed - kwAcUtlPjuFreeCb: event(%d) is wrong\n",
                  qElm->pst.event), 2);
         RETVALUE(CMXTA_ERR_INT);

   }

   if(kwElm->mBuf != NULLP)
      CMXTA_FREEMBUF(kwElm->mBuf);

   CMXTA_FREE(kwElm, sizeof (KwAcMsgQElm));
   qElm->data = NULLP;

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlPjuFreeCb */

  
/*************************************************************************
 *                PJU DAT REQ QUEUE PRIMITIVES START
 *************************************************************************/
/**
 * @brief Circular Queue for PJU Data Request Interface
 *
 * @details
 *
 *     Function : kwAcUtlPjuDatReqCQMakeNull
 *
 *     This function Initializes the PJU DatReq Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void kwAcUtlPjuDatReqCQMakeNull
(
KwAcPjuDatReqQ    *queue
)
#else
PUBLIC Void kwAcUtlPjuDatReqCQMakeNull(queue)
KwAcPjuDatReqQ    *queue;
#endif
{
   queue->front = 1;
   queue->rear = KWAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* kwAcUtlPjuDatReqCQMakeNull */

/** @breif It increments index exactly
 * @param[in] queue - Pju Data Request Queue
 * @return index
 * */
#ifdef ANSI
PUBLIC U16 kwAcUtlPjuDatReqCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 kwAcUtlPjuDatReqCircQAddOne(idx)
U16 idx;
#endif
{
   /* kw005.201 Changes for R9 RLC test cases */
   /* 0x3FF below is KWAC_MAX_CIRCQ_SIZE(currently 1024) - 1 */
   if (idx == 0x3FF)
      RETVALUE(1);
   else
      RETVALUE((idx + 1) & 0x3FF);
} /* kwAcUtlPjuDatReqCircQAddOne */

/** @breif It moves rear index by one if Queue is not full
 * @param[in] queue - Pju Data Request Queue
 * @return front index
 * */
#ifdef ANSI
PUBLIC U16 kwAcUtlPjuDatReqCircQEnqueue
(
KwAcPjuDatReqQ *queue
)
#else
PUBLIC U16 kwAcUtlPjuDatReqCircQEnqueue(queue)
KwAcPjuDatReqQ *queue;
#endif
{
   /* Making 3 length difference between rear and front to make
    * sure Q is full
    */
   if (kwAcUtlPjuDatReqCircQAddOne(kwAcUtlPjuDatReqCircQAddOne(
               kwAcUtlPjuDatReqCircQAddOne(queue->rear))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlPjuDatReqCircQEnqueue(): PJU DatReq Queue is full\n"));
      RETVALUE(0);
   }

   queue->rear = kwAcUtlPjuDatReqCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* kwAcUtlPjuDatReqCircQEnqueue */

/** @breif It returns the Front index if Queue is not empty
 * else returns 0
 * @param[in] queue - Pju Data Request Queue
 * @return front index
 * */
#ifdef ANSI
PUBLIC U16 kwAcUtlPjuDatReqCircQGetFront
(
KwAcPjuDatReqQ *queue
)
#else
PUBLIC U16 kwAcUtlPjuDatReqCircQGetFront(queue)
KwAcPjuDatReqQ *queue;
#endif
{
      U8  ret;

    ret = KWAC_UTL_PJU_DATREQ_CQ_ISEMPTY(queue);
 
   if(ret)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlPjuDatReqCircQGetFront(): PJU DatReq Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* kwAcUtlPjuDatReqCircQGetFront */

/** @breif It returns the valid idx if Queue is not empty
 * @param[in] queue - Pju Data Request Queue
 * @param[in] idx   - present index
 * @return Next Valid index
 * */
#ifdef ANSI
PUBLIC U16 kwAcUtlPjuDatReqCircQGetNext
(
KwAcPjuDatReqQ   *queue,
U16            idx
)
#else
PUBLIC U16 kwAcUtlPjuDatReqCircQGetNext(queue, idx)
KwAcPjuDatReqQ   *queue;
U16            idx;
#endif
{
   /* Check whether we reached front or not (empty) */
   if ((idx >= queue->rear) && ((queue->rear == queue->front) ||
         (kwAcUtlPjuDatReqCircQAddOne(idx) == queue->front)))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlPjuDatReqCircQGetNext(): PJU DatReq Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(kwAcUtlPjuDatReqCircQAddOne(idx));
} /* kwAcUtlPjuDatReqCircQGetNext */

/** @breif It moves front pointer by one
 * @param[in] queue - Pju Data Request Queue
 * @return None
 * */
#ifdef ANSI
PUBLIC Void kwAcUtlPjuDatReqCircQDequeue
(
KwAcPjuDatReqQ *queue
)
#else
PUBLIC Void kwAcUtlPjuDatReqCircQDequeue(queue)
KwAcPjuDatReqQ *queue;
#endif
{
   if(KWAC_UTL_PJU_DATREQ_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,\
               "kwAcUtlPjuDatReqCircQDequeue(): PJU DatReq Queue is empty\n"));
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = kwAcUtlPjuDatReqCircQAddOne(queue->front);
      if(KWAC_UTL_PJU_DATREQ_CQ_ISEMPTY(queue))
         break;
   }

   RETVOID;
} /* kwAcUtlPjuDatReqCircQDequeue */

/*************************************************************************
 *                PJU DAT REQ QUEUE PRIMITIVES END
 *************************************************************************/


/**
@brief Utility Function to Build data forward request
@param[in]  tcCb       -  Test Case Control Block
@param[in]  spCb       -  XML DOM Control Block
@param[out] datFwdReq  -  Data Forward Request Information
@param[out] mBuf       -  SDU mBuf

@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlBuildPjuDatFwdReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjuDatFwdReqInfo   *datFwdReq
)
#else
PUBLIC S16 kwAcUtlBuildPjuDatFwdReq(tcCb, spCb, datFwdReq)
CmXtaTCCb      *tcCb;    /* tcCb data structure  */
CmXtaSpCb      *spCb;
PjuDatFwdReqInfo   *datFwdReq;
#endif
{
   U8       sData;
   U8       data[KWAC_PJU_MAX_FLAT_BUF_SIZE];
   U16      sduSize;
   U8       numSdus;
   U32      idx;
   U32      sduId[KWAC_MAX_SIZE];
   U16      sn[KWAC_MAX_SIZE];
   U16      sduSzLst[KWAC_MAX_SIZE];
   U8       sduData[KWAC_MAX_SIZE];
 
   TRC2(kwAcUtlBuildPjuDatFwdReq);

   CMXTA_ZERO(data, sizeof(data));
   CMXTA_ZERO(sduId, sizeof(sduId));
   CMXTA_ZERO(sn, sizeof(sn));
   CMXTA_ZERO(sduSzLst, sizeof(sduSzLst));
   CMXTA_ZERO(sduData, sizeof(sduData));
            
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dir", &(datFwdReq->dir));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "numSdus", &(datFwdReq->numSdus));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON,
                 "sduId", sduId, &numSdus);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,
                 "sn", sn, &numSdus);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,
                 "sduSzLst", sduSzLst, &numSdus);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,
                 "sduData", sduData, &numSdus);

   /* Allocate memory for datFwdInfo */
   KW_ALLOC_ACC(datFwdReq->datFwdInfo, (datFwdReq->numSdus * sizeof(PjuDatFwdInfo)));
   if (datFwdReq->datFwdInfo == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap,
               "kwAcUtlBuildPjuDatFwdReq(): KW_ALLOC datFwdInfo Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   for (idx = 0; idx <datFwdReq->numSdus; idx++)
   {
      datFwdReq->datFwdInfo[idx].sduId = sduId[idx];
      datFwdReq->datFwdInfo[idx].sn = sn[idx];

      if (sduSzLst[idx] == 0)
      {
         sduSize = 100;
         if (sduData[idx] == 0x00)
         {
            sData = 0x7F;
         }
         else
         {
            sData = sduData[idx];
         }

         /* Allocate memory for SDU mBuf */
         if (SGetMsg(DFLT_REGION, DFLT_POOL, &(datFwdReq->datFwdInfo[idx].sdu)) != ROK)
         {
            CMXTA_DBG_ERR((_cmxtap, "kwAcUtlBuildPjuDatFwdReq(): resource unavailble \n"));
            KW_FREE_ACC(datFwdReq->datFwdInfo, (datFwdReq->numSdus * sizeof(PjuDatFwdInfo)));
            RETVALUE(CMXTA_ERR_RSRC);
         } /* end of if statement */

         KWAC_FORM_SDU(data, sduSize, sData, &datFwdReq->datFwdInfo[idx].sdu);
      }
      else
      {
         sduSize = sduSzLst[idx];
         if (sduData[idx] == 0x00)
         {
            sData = 0x7F;
         }
         else
         {
            sData = sduData[idx];
         }

         /* Allocate memory for SDU mBuf */
         if (SGetMsg(DFLT_REGION, DFLT_POOL, &(datFwdReq->datFwdInfo[idx].sdu)) != ROK)
         {
            CMXTA_DBG_ERR((_cmxtap, "kwAcUtlBuildPjuDatFwdReq(): resource unavailble \n"));
            KW_FREE_ACC(datFwdReq->datFwdInfo, (datFwdReq->numSdus * sizeof(PjuDatFwdInfo)));
            RETVALUE(CMXTA_ERR_RSRC);
         } /* end of if statement */

         KWAC_FORM_SDU(data, sduSize, sData, &datFwdReq->datFwdInfo[idx].sdu);
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlBuildPjuDatFwdReq */


/**
 * @brief Validate PJU Data Forward Indication
 *
 * @details
 *
 *     Function : kwAcUtlValdtPjuDatFwdInd
 *
 *     This function Validates PjuDatFwdInd structure recieved from RLC
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *kwElm
 *  @param[in]  *entity
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlValdtPjuDatFwdInd
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwAcMsgQElm       *kwElm
)
#else
PUBLIC S16 kwAcUtlValdtPjuDatFwdInd(tcCb, spCb, kwElm)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
KwAcMsgQElm       *kwElm;
#endif
{
   PjuDatFwdIndInfo     *datFwdInd;
   U8                   rbId;
   U8                   rbType;
   CmLteRnti            ueId;
   CmLteCellId          cellId;
   S16                  idx;
   U32                  sduId[KWAC_MAX_SIZE];
   U16                  sn[KWAC_MAX_SIZE];
   U16                  sduSzLst[KWAC_MAX_SIZE];
   CmLtePdcpId          *pdcpId;
   U16                  numSdus;
   U8                   dir;
   U8                   tmpNum;
   MsgLen               sduLen = 0;

   TRC2(kwAcUtlValdtPjuDatInd);

   ueId = 0;
   rbId = 0;
   rbType = 0;
   cellId = 0;
   dir = 0;
   numSdus = 0;
   datFwdInd = kwElm->u.pjuInfo.u.datFwdInd;
   pdcpId = kwElm->u.pjuInfo.pdcpId;
   CMXTA_ZERO(sduId, sizeof(sduId));
   CMXTA_ZERO(sn, sizeof(sn));
   CMXTA_ZERO(sduSzLst, sizeof(sduSzLst));
            
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "dir", &dir);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "numSdus", &numSdus);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON,
                 "sduId", sduId, &tmpNum);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,
                 "sn", sn, &tmpNum);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,
                 "sduSzLst", sduSzLst, &tmpNum);

   if (rbId != kwElm->u.pjuInfo.pdcpId->rbId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuStaInd():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.pjuInfo.pdcpId->rbId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (rbType != kwElm->u.pjuInfo.pdcpId->rbType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuStaInd():Failed : rbType MisMatch: exp (%d) rcvd (%d) \n",
                  rbType, kwElm->u.pjuInfo.pdcpId->rbType), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.pjuInfo.pdcpId->ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuStaInd():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.pjuInfo.pdcpId->ueId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.pjuInfo.pdcpId->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuStaInd():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.pjuInfo.pdcpId->cellId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   for (idx = 0; idx < numSdus; idx++)
   {
      if (sduId[idx] != datFwdInd->datFwdInfo[idx].sduId)
      {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap,
                  "kwAcUtlValdtPjuDatFwdInd():Failed : sduId MisMatch: exp (%ld) rcvd (%ld) \n",
                  sduId[idx], datFwdInd->datFwdInfo[idx].sduId), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap,
                  "kwAcUtlValdtPjuDatFwdInd():Failed : sduId MisMatch: exp (%d) rcvd (%d) \n",
                  sduId[idx], datFwdInd->datFwdInfo[idx].sduId), 2);
#endif
         RETVALUE(CMXTA_ERR_INT);
      }

      if (sn[idx] != (S32)datFwdInd->datFwdInfo[idx].sn)
      {
         CMXTA_DBG_CALLIND((_cmxtap,
                  "kwAcUtlValdtPjuDatFwdInd():Failed : sn MisMatch: exp (%d) rcvd (%d) \n",
                  sn[idx], datFwdInd->datFwdInfo[idx].sn), 2);
         RETVALUE(CMXTA_ERR_INT);
      }

      SFndLenMsg(datFwdInd->datFwdInfo[idx].sdu, &sduLen);
      if (sduSzLst[idx] != sduLen)
      {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap,
                  "kwAcUtlValdtPjuDatFwdInd():Failed : sduSize MisMatch: sduId exp (%ld) rcvd (%d) sduLen (%d)\n",
                  sduId[idx], sduSzLst[idx], sduLen), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap,
                  "kwAcUtlValdtPjuDatFwdInd():Failed : sduSize MisMatch: sduId exp (%d) rcvd (%d) sduLen (%d)\n",
                  sduId[idx], sduSzLst[idx], sduLen), 2);
#endif
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlValdtPjuDatFwdInd */

/*************************************************************************
 *                PJU DAT CFM QUEUE PRIMITIVES END
 *************************************************************************/

#endif /* KW_PDCP */
/********************************************************************30**

         End of file:     kwac_pjuutl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:38 2014

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
/main/1      ---   mn         1. LTERLC Release 2.1.
/main/2      kw005.201 rd     1. Changes wrt macro KWAC_MAX_CIRCQ_SIZE for
                                 TCs added for RLC R9 upgrade. The following 
                                 funcs are modified:
                                 kwAcUtlPjuDatReqCircQAddOne
*********************************************************************91*/


