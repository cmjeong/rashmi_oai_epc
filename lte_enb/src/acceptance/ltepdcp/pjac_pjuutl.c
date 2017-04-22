

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_pjucb.c

     Sid:      pjac_pjuutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:06 2015

     Prg:     Adarsh
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
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_kwu.h"      /* KWU Acceptance defines */
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_pju.h"      /* PJU Acceptance defines */

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
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_pju.x"      /* CKW Acceptance defines */

/**
@brief Utility Function to Build data request
@param[in] datReq    -  Data Request Information
@param[in] mBuf      -  SDU mBuf
@param[in] sduSize   -  SDU size

@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 pjAcUtlCpyPjuDatReq 
(
CmLtePdcpId    *pdcpId,
U32            *sduId,
Buffer         *mBuf,
U16            sduSize,
U8             entity
)
#else
PUBLIC S16 pjAcUtlCpyPjuDatReq(pdcpId, sduId, mBuf, sduSize, entity)
CmLtePdcpId    *pdcpId;
U32            *sduId;
Buffer         *mBuf;
U16            sduSize;
U8             entity;
#endif
{
   KwAcPjuDatReq     *tDatReq = NULLP;

   TRC2(pjAcUtlCpyPjuDatReq);

   /* Get the kwAcCb.xxPjuCb.datReq Q node pointer
    * and fill the information from datReq to verify
    * at datInd
    */
   
   if (entity == ENTNH)
   {
      tDatReq = &(kwAcCb.nhPjuCb.datReq.node[\
            pjAcUtlPjuDatReqCircQEnqueue(&kwAcCb.nhPjuCb.datReq)]);
      tDatReq->entity = ENTNH;
      tDatReq->transId = ++kwAcCb.nhPjuCb.nxtTransId;
   }
   else
   {
      tDatReq = &(kwAcCb.pxPjuCb.datReq.node[\
            pjAcUtlPjuDatReqCircQEnqueue(&kwAcCb.pxPjuCb.datReq)]);
      tDatReq->entity = ENTPX;
      tDatReq->transId = kwAcCb.pxPjuCb.nxtTransId++;
   }

   /* Fill kwAcCb.pjuCb.datReq Q node */
   tDatReq->isInQ = TRUE;
   tDatReq->sduSize = sduSize;


   /* Copy mBuf to kwAcCb.pjuCb.datReq Q */
   PJAC_CPY_MBUF(mBuf, tDatReq->mBuf);

   /* As kwAcCb.pjuCb.datReq is array and static,
    * We can use cmMemcpy to copy the structure
    */
   cmMemcpy((U8 *)&tDatReq->pdcpId, (U8 *)pdcpId, sizeof(CmLtePdcpId));
   tDatReq->sduId = *sduId;

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcUtlCpyPjuDatReq */


/**
@brief Utility Function to Build data request
@param[in]  tcCb       -  Test Case Control Block
@param[in]  spCb       -  XML DOM Control Block
@param[out] pdcpId     -  Data Request Information
@param[out] mBuf       -  SDU mBuf

@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 pjAcUtlBuildPjuDatReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
CmLtePdcpId    *pdcpId,
U32            *sduId,
Buffer         **mBuf,
U8             entity
)
#else
PUBLIC S16 pjAcUtlBuildPjuDatReq(tcCb, spCb, pdcpId, sduId, mBuf, entity)
CmXtaTCCb      *tcCb;    /* tcCb data structure  */
CmXtaSpCb      *spCb;
CmLtePdcpId    *pdcpId;
U32            *sduId;
Buffer         **mBuf;
U8             entity;
#endif
{
   U8       sData;
   U8       data[PJAC_PJU_MAX_FLAT_BUF_SIZE];
   U16      sduSize;
   U16      tmpCnt;
   Bool     pass;
 
   TRC2(pjAcUtlBuildPjuDatReq);

   sData = 0x7F;
   sduSize = 0;
   tmpCnt = 0;
   pass = TRUE;

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
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "pass", &(pass));

   /* Allocate memory for SDU mBuf */
   if (SGetMsg(DFLT_REGION, DFLT_POOL, mBuf) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcUtlBuildPjuDatReq(): resource unavailble \n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } /* end of if statement */

   if (sduSize > PJ_MAX_SDU_SIZE)
   {
      tmpCnt = sduSize / 3000;

      PJAC_FORM_SDU(data, (sduSize % 3000), sData, mBuf);

      while (tmpCnt > 0)
      {
         PJAC_FORM_SDU(data, 3000, sData, mBuf);
         tmpCnt--;
      }
   }
   else
   {
      PJAC_FORM_SDU(data, sduSize, sData, mBuf);
   }

   /* Fill SDU ID from kwAcCb.pjuCb.nxtSduId */
   if (entity == ENTNH)
   {
      *sduId = kwAcCb.nhPjuCb.nxtSduId[pdcpId->cellId][pdcpId->ueId][0][pdcpId->rbId];
      kwAcCb.nhPjuCb.nxtSduId[pdcpId->cellId][pdcpId->ueId][0][pdcpId->rbId]++;
   }
   else
   {
      *sduId = kwAcCb.pxPjuCb.nxtSduId[pdcpId->cellId][pdcpId->ueId][1][pdcpId->rbId];
      kwAcCb.pxPjuCb.nxtSduId[pdcpId->cellId][pdcpId->ueId][1][pdcpId->rbId]++;
   }
   if(pass)
   {
   /* Copy datReq to kwAcCb.pxPjuCb/pjuCb */
   if (pjAcUtlCpyPjuDatReq(pdcpId, sduId, *mBuf, sduSize, entity) != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_INT);
   }
   }
   /* Store tcCb and spCb to fetch Off-board attributes in
    * Off-board acceptance code kwac_libcb.c in DL
    */
   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcUtlBuildPjuDatReq */

#ifdef ANSI
PUBLIC S16 pjAcUtlCmpPjuDatReqBuf
(
Buffer *srcBuf,
Buffer *dstBuf,
U32    size
)
#else
PUBLIC S16 pjAcUtlCmpPjuDatReqBuf(srcBuf, dstBuf, size)
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
} /* pjAcUtlCmpPjuDatReqBuf */


/**
 * @brief Validate PJU Data Indication
 *
 * @details
 *
 *     Function : pjAcUtlValdtPjuDatInd
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
PUBLIC S16 pjAcUtlValdtPjuDatInd
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwAcMsgQElm       *kwElm,
U8                entity
)
#else
PUBLIC S16 pjAcUtlValdtPjuDatInd(tcCb, spCb, kwElm, entity)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
KwAcMsgQElm       *kwElm;
U8                entity;
#endif
{
   KwAcPjuDatReq        *datReq;
   Buffer               *mBuf;
   CmLtePdcpId          *pdcpId = NULLP;
   CmLteRnti            tCrnti;
   S16                  idx;
   S32                  sduId;
   Bool                 noCirQ;
   U8                   valdType = 0;

   TRC2(pjAcUtlValdtPjuDatInd);

   tCrnti = 0;
   sduId = -1;
   mBuf = kwElm->mBuf;
   pdcpId = kwElm->u.pjuInfo.pdcpId;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "valdType", &(valdType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "sduId", &(sduId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "noCirQ", &(noCirQ));

   if (valdType == 1)
   {
      RETVALUE(CMXTA_ERR_NONE);
   }
/* adarsh */
#if 0
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
/* Venki */
#ifndef KW_PDCP
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
#endif


   /* adarsh : datReq must be taken with transId */
#if 0
   /* get rlc id */
   if (entity == ENTNH)
   {
      idx = pjAcUtlPjuDatReqCircQGetFront(&kwAcCb.nhPjuCb.datReq);
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
          idx = pjAcUtlPjuDatReqCircQGetNext(&kwAcCb.nhPjuCb.datReq, idx);
      } while (idx);
      if (!idx)
      {
         CMXTA_DBG_PARAM((_cmxtap, "Failed - idx not found\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else
   {
      idx = pjAcUtlPjuDatReqCircQGetFront(&kwAcCb.pxPjuCb.datReq);
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
          idx = pjAcUtlPjuDatReqCircQGetNext(&kwAcCb.pxPjuCb.datReq, idx);
      } while (idx);
      if (!idx)
      {
         CMXTA_DBG_PARAM((_cmxtap, "Failed - idx not found\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }  
#else
   /* idx needs to be taken from transId : currently for testing*/
   if (entity == ENTNH)
   {
      idx = pjAcUtlPjuDatReqCircQGetFront(&kwAcCb.nhPjuCb.datReq);
      datReq = &kwAcCb.nhPjuCb.datReq.node[idx];
   }
   else
   {
      idx = pjAcUtlPjuDatReqCircQGetFront(&kwAcCb.pxPjuCb.datReq);
      datReq = &kwAcCb.pxPjuCb.datReq.node[idx];
   }
#endif 
   /* validate buffer */
   if(noCirQ != TRUE)
   {
      if (pjAcUtlCmpPjuDatReqBuf(datReq->mBuf, mBuf, datReq->sduSize) !=
            CMXTA_ERR_NONE)
      {
         CMXTA_DBG_ERR((_cmxtap,
                  "pjAcUtlCmpPjuDatReqBuf(): mBuf comarision Failed.\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   /* Free the Buffers and datInd 
   PJ_FREE_BUF(datReq->mBuf);                free the stored mBuf 

    Memset to 0 for datReq
    * This make isInQ flag to 0 (FALSE) 
   CMXTA_ZERO(datReq, sizeof(KwAcPjuDatReq)); Memset to 0 for datReq 

    Remove the msg from datReq Q if possible : this needs to be checked whether required or not
   if (entity ==ENTNH)
   {
      pjAcUtlPjuDatReqCircQDequeue(&kwAcCb.nhPjuCb.datReq);
   }
   else
   {
      pjAcUtlPjuDatReqCircQDequeue(&kwAcCb.pxPjuCb.datReq);
   }   */

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcUtlValdtPjuDatInd */


/**
@brief utility function for releasing CmXtaMsgQElm
@param qElm
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcUtlPjuFreeCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 pjAcUtlPjuFreeCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   KwAcMsgQElm *kwElm;

   TRC2(pjAcUtlPjuFreeCb);

   CMXTA_DBG_PARAM((_cmxtap, "pjAcUtlPjuFreeCb(): \n"));

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
            PJ_FREE_BUF(kwElm->u.pjuInfo.u.datFwdInd->datFwdInfo[i].sdu);
         }

         KW_FREE_ACC(kwElm->u.pjuInfo.u.datFwdInd->datFwdInfo,
               kwElm->u.pjuInfo.u.datFwdInd->numSdus * sizeof(PjuDatFwdInfo));

         KW_FREE_ACC(kwElm->u.pjuInfo.u.datFwdInd, sizeof(PjuDatFwdIndInfo));
         KW_FREE_ACC(kwElm->u.pjuInfo.pdcpId, sizeof(CmLtePdcpId));
      }
         break;
      default:
         CMXTA_DBG_CALLIND((_cmxtap, "Failed - pjAcUtlPjuFreeCb: event(%d) is wrong\n",
                  qElm->pst.event), 2);
         RETVALUE(CMXTA_ERR_INT);

   }

   if(kwElm->mBuf != NULLP)
      CMXTA_FREEMBUF(kwElm->mBuf);

   CMXTA_FREE(kwElm, sizeof (KwAcMsgQElm));
   qElm->data = NULLP;

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcUtlPjuFreeCb */

/*************************************************************************
 *                PJU DAT REQ QUEUE PRIMITIVES START
 *************************************************************************/
/**
 * @brief Circular Queue for PJU Data Request Interface
 *
 * @details
 *
 *     Function : pjAcUtlPjuDatReqCQMakeNull
 *
 *     This function Initializes the PJU DatReq Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void pjAcUtlPjuDatReqCQMakeNull
(
KwAcPjuDatReqQ    *queue
)
#else
PUBLIC Void pjAcUtlPjuDatReqCQMakeNull(queue)
KwAcPjuDatReqQ    *queue;
#endif
{
   queue->front = 1;
   queue->rear = PJAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* pjAcUtlPjuDatReqCQMakeNull */

/** @breif It increments index exactly
 * @param[in] queue - Pju Data Request Queue
 * @return index
 * */
#ifdef ANSI
PUBLIC U16 pjAcUtlPjuDatReqCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 pjAcUtlPjuDatReqCircQAddOne(idx)
U16 idx;
#endif
{
   /* kw005.201 Changes for R9 RLC test cases */
   /* 0x3FF below is PJAC_MAX_CIRCQ_SIZE(currently 1024) - 1 */
   if (idx == 0x3FF)
      RETVALUE(1);
   else
      RETVALUE((idx + 1) & 0x3FF);
} /* pjAcUtlPjuDatReqCircQAddOne */

/** @breif It moves rear index by one if Queue is not full
 * @param[in] queue - Pju Data Request Queue
 * @return front index
 * */
#ifdef ANSI
PUBLIC U16 pjAcUtlPjuDatReqCircQEnqueue
(
KwAcPjuDatReqQ *queue
)
#else
PUBLIC U16 pjAcUtlPjuDatReqCircQEnqueue(queue)
KwAcPjuDatReqQ *queue;
#endif
{
   /* Making 3 length difference between rear and front to make
    * sure Q is full
    */
   if (pjAcUtlPjuDatReqCircQAddOne(pjAcUtlPjuDatReqCircQAddOne(
               pjAcUtlPjuDatReqCircQAddOne(queue->rear))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "pjAcUtlPjuDatReqCircQEnqueue(): PJU DatReq Queue is full\n"));
      queue->rear = 1;
      RETVALUE(1);  
   }

   queue->rear = pjAcUtlPjuDatReqCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* pjAcUtlPjuDatReqCircQEnqueue */

/** @breif It returns the Front index if Queue is not empty
 * else returns 0
 * @param[in] queue - Pju Data Request Queue
 * @return front index
 * */
#ifdef ANSI
PUBLIC U16 pjAcUtlPjuDatReqCircQGetFront
(
KwAcPjuDatReqQ *queue
)
#else
PUBLIC U16 pjAcUtlPjuDatReqCircQGetFront(queue)
KwAcPjuDatReqQ *queue;
#endif
{
      U8  ret;

    ret = PJAC_UTL_PJU_DATREQ_CQ_ISEMPTY(queue);
 
   if(ret)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "pjAcUtlPjuDatReqCircQGetFront(): PJU DatReq Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* pjAcUtlPjuDatReqCircQGetFront */

/** @breif It returns the valid idx if Queue is not empty
 * @param[in] queue - Pju Data Request Queue
 * @param[in] idx   - present index
 * @return Next Valid index
 * */
#ifdef ANSI
PUBLIC U16 pjAcUtlPjuDatReqCircQGetNext
(
KwAcPjuDatReqQ   *queue,
U16            idx
)
#else
PUBLIC U16 pjAcUtlPjuDatReqCircQGetNext(queue, idx)
KwAcPjuDatReqQ   *queue;
U16            idx;
#endif
{
   /* Check whether we reached front or not (empty) */
   if ((idx >= queue->rear) && ((queue->rear == queue->front) ||
         (pjAcUtlPjuDatReqCircQAddOne(idx) == queue->front)))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "pjAcUtlPjuDatReqCircQGetNext(): PJU DatReq Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(pjAcUtlPjuDatReqCircQAddOne(idx));
} /* pjAcUtlPjuDatReqCircQGetNext */

/** @breif It moves front pointer by one
 * @param[in] queue - Pju Data Request Queue
 * @return None
 * */
#ifdef ANSI
PUBLIC Void pjAcUtlPjuDatReqCircQDequeue
(
KwAcPjuDatReqQ *queue
)
#else
PUBLIC Void pjAcUtlPjuDatReqCircQDequeue(queue)
KwAcPjuDatReqQ *queue;
#endif
{
   if(PJAC_UTL_PJU_DATREQ_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,\
               "pjAcUtlPjuDatReqCircQDequeue(): PJU DatReq Queue is empty\n"));
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = pjAcUtlPjuDatReqCircQAddOne(queue->front);
      if(PJAC_UTL_PJU_DATREQ_CQ_ISEMPTY(queue))
         break;
   }

   RETVOID;
} /* pjAcUtlPjuDatReqCircQDequeue */

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
PUBLIC S16 pjAcUtlBuildPjuDatFwdReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjuDatFwdReqInfo   *datFwdReq,
CmLtePdcpId    *pdcpId
)
#else
PUBLIC S16 pjAcUtlBuildPjuDatFwdReq(tcCb, spCb, datFwdReq, pdcpId)
CmXtaTCCb      *tcCb;    /* tcCb data structure  */
CmXtaSpCb      *spCb;
PjuDatFwdReqInfo   *datFwdReq;
CmLtePdcpId    *pdcpId;
#endif
{
   U8       sData;
   U8       data[PJAC_PJU_MAX_FLAT_BUF_SIZE];
   U16      sduSize;
   U8       numSdus;
   U32      idx;
   U32      sduId[PJAC_MAX_SIZE];
   U16      sn[PJAC_MAX_SIZE];
   U16      sduSzLst[PJAC_MAX_SIZE];
   U8       sduData[PJAC_MAX_SIZE];
 
   TRC2(pjAcUtlBuildPjuDatFwdReq);

   CMXTA_ZERO(data, sizeof(data));
   CMXTA_ZERO(sduId, sizeof(sduId));
   CMXTA_ZERO(sn, sizeof(sn));
   CMXTA_ZERO(sduSzLst, sizeof(sduSzLst));
   CMXTA_ZERO(sduData, sizeof(sduData));
            
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(pdcpId->rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(pdcpId->rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(pdcpId->ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(pdcpId->cellId));
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
               "pjAcUtlBuildPjuDatFwdReq(): KW_ALLOC datFwdInfo Failed\n"));
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
            CMXTA_DBG_ERR((_cmxtap, "pjAcUtlBuildPjuDatFwdReq(): resource unavailble \n"));
            KW_FREE_ACC(datFwdReq->datFwdInfo, (datFwdReq->numSdus * sizeof(PjuDatFwdInfo)));
            RETVALUE(CMXTA_ERR_RSRC);
         } /* end of if statement */

         PJAC_FORM_SDU(data, sduSize, sData, &datFwdReq->datFwdInfo[idx].sdu);
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
            CMXTA_DBG_ERR((_cmxtap, "pjAcUtlBuildPjuDatFwdReq(): resource unavailble \n"));
            KW_FREE_ACC(datFwdReq->datFwdInfo, (datFwdReq->numSdus * sizeof(PjuDatFwdInfo)));
            RETVALUE(CMXTA_ERR_RSRC);
         } /* end of if statement */

         PJAC_FORM_SDU(data, sduSize, sData, &datFwdReq->datFwdInfo[idx].sdu);
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcUtlBuildPjuDatFwdReq */


/**
 * @brief Validate PJU Data Forward Indication
 *
 * @details
 *
 *     Function : pjAcUtlValdtPjuDatFwdInd
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
PUBLIC S16 pjAcUtlValdtPjuDatFwdInd
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwAcMsgQElm       *kwElm
)
#else
PUBLIC S16 pjAcUtlValdtPjuDatFwdInd(tcCb, spCb, kwElm)
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
   U32                  sduId[PJAC_MAX_SIZE];
   U16                  sn[PJAC_MAX_SIZE];
   U16                  sduSzLst[PJAC_MAX_SIZE];
   CmLtePdcpId          *pdcpId;
   U16                  numSdus;
   U8                   dir;
   U8                   tmpNum;
   MsgLen               sduLen = 0;
   Bool              isLastDatFwdInd = FALSE;

   TRC2(pjAcUtlValdtPjuDatInd);

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
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isLastDatFwdInd", &(isLastDatFwdInd));
   if(isLastDatFwdInd)
   {
      RETVALUE(CMXTA_ERR_NONE);
   }   
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
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuStaInd():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.pjuInfo.pdcpId->rbId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (rbType != kwElm->u.pjuInfo.pdcpId->rbType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuStaInd():Failed : rbType MisMatch: exp (%d) rcvd (%d) \n",
                  rbType, kwElm->u.pjuInfo.pdcpId->rbType), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.pjuInfo.pdcpId->ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuStaInd():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.pjuInfo.pdcpId->ueId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.pjuInfo.pdcpId->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuStaInd():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.pjuInfo.pdcpId->cellId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   for (idx = 0; idx < numSdus; idx++)
   {
      if (sduId[idx] != datFwdInd->datFwdInfo[idx].sduId)
      {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap,
                  "pjAcUtlValdtPjuDatFwdInd():Failed : sduId MisMatch: exp (%ld) rcvd (%ld) \n",
                  sduId[idx], datFwdInd->datFwdInfo[idx].sduId), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap,
                  "pjAcUtlValdtPjuDatFwdInd():Failed : sduId MisMatch: exp (%d) rcvd (%d) \n",
                  sduId[idx], datFwdInd->datFwdInfo[idx].sduId), 2);
#endif
         RETVALUE(CMXTA_ERR_INT);
      }

      if (sn[idx] != (S32)datFwdInd->datFwdInfo[idx].sn)
      {
         CMXTA_DBG_CALLIND((_cmxtap,
                  "pjAcUtlValdtPjuDatFwdInd():Failed : sn MisMatch: exp (%d) rcvd (%d) \n",
                  sn[idx], datFwdInd->datFwdInfo[idx].sn), 2);
         RETVALUE(CMXTA_ERR_INT);
      }

      SFndLenMsg(datFwdInd->datFwdInfo[idx].sdu, &sduLen);
      if (sduSzLst[idx] != sduLen)
      {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap,
                  "pjAcUtlValdtPjuDatFwdInd():Failed : sduSize MisMatch: sduId exp (%ld) rcvd (%d) sduLen (%d)\n",
                  sduId[idx], sduSzLst[idx], sduLen), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap,
                  "pjAcUtlValdtPjuDatFwdInd():Failed : sduSize MisMatch: sduId exp (%d) rcvd (%d) sduLen (%d)\n",
                  sduId[idx], sduSzLst[idx], sduLen), 2);
#endif
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcUtlValdtPjuDatFwdInd */

/*************************************************************************
 *                PJU DAT CFM QUEUE PRIMITIVES END
 *************************************************************************/

/********************************************************************30**

         End of file:     pjac_pjuutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:06 2015

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
/main/1        ---      av         1. LTE PDCP Initial Release 2.1.
*********************************************************************91*/

