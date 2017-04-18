

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_kwucb.c

     Sid:      kwac_kwuutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:52:37 2016

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
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#ifdef KW_PDCP
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#endif /* KW_PDCP */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_kwu.h"      /* CKW Acceptance defines */

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
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#ifdef KW_PDCP
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#endif /* KW_PDCP */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_kwu.x"      /* CKW Acceptance defines */

extern KwCb gKwDummyCb;

/**
@brief Utility Function to Build data request
@param[in] datReq    -  Data Request Information
@param[in] mBuf      -  SDU mBuf
@param[in] sduSize   -  SDU size
@param[in] entity    - Entity

@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlCpyKwuDatReq 
(
KwuDatReqInfo  *datReq,
Buffer         *mBuf,
U32            sduSize,
U8            entity
)
#else
PUBLIC S16 kwAcUtlCpyKwuDatReq(datReq, mBuf, sduSize, entity)
KwuDatReqInfo  *datReq;
Buffer         *mBuf;
U32            sduSize;
U8            entity;
#endif
{
   KwAcKwuDatReq     *tDatReq = NULLP;

   TRC2(kwAcUtlCpyKwuDatReq);

   /* Get the kwAcCb.xxKwuCb.datReq Q node pointer
    * and fill the information from datReq to verify
    * at datInd
    */
   if (entity == ENTNH)
   {
      tDatReq = &(kwAcCb.nhKwuCb.datReq.node[\
            kwAcUtlKwuDatReqCircQEnqueue(&kwAcCb.nhKwuCb.datReq)]);
      tDatReq->entity = ENTNH;
   }
#ifndef KW_PDCP
   else
   {
      tDatReq = &(kwAcCb.pjKwuCb.datReq.node[\
            kwAcUtlKwuDatReqCircQEnqueue(&kwAcCb.pjKwuCb.datReq)]);
      tDatReq->entity = ENTPJ;
   }
#endif /* KW_PDCP */

   /* Fill kwAcCb.kwuCb.datReq Q node */
   if (tDatReq != NULLP)
   {
      tDatReq->isInQ = TRUE;
      tDatReq->sduSize = sduSize;
      tDatReq->entity = entity;
   }
   else
   {
      CMXTA_DBG_PARAM((_cmxtap, "Failed - tDatReq is NULLP.\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Copy mBuf to kwAcCb.kwuCb.datReq Q */
   KWAC_CPY_MBUF(mBuf, tDatReq->mBuf);

   /* As kwAcCb.kwuCb.datReq is array and static,
    * We can use cmMemcpy to copy the structure
    */
   cmMemcpy((U8 *)&tDatReq->datReq, (U8 *)datReq, sizeof(KwuDatReqInfo));

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlCpyKwuDatReq */


/**
@brief Utility Function to Build data request
@param[in]  tcCb       -  Test Case Control Block
@param[in]  spCb       -  XML DOM Control Block
@param[out] datReq     -  Data Request Information
@param[out] mBuf       -  SDU mBuf
@param[in]  entity     -  Entity RRC(NH)/PDCP(DM)

@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlBuildKwuDatReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwuDatReqInfo  *datReq,
Buffer         **mBuf,
U8            entity
)
#else
PUBLIC S16 kwAcUtlBuildKwuDatReq(tcCb, spCb, datReq, mBuf, entity)
CmXtaTCCb      *tcCb;    /* tcCb data structure  */
CmXtaSpCb      *spCb;
KwuDatReqInfo  *datReq;
Buffer         **mBuf;
U8            entity;
#endif
{
   U8       sData;
   U8       data[KWAC_KWU_MAX_FLAT_BUF_SIZE];
   U16      sduSize;
 
   TRC2(kwAcUtlBuildKwuDatReq);

   sData = 0x7F;
   sduSize = 0;

   CMXTA_ZERO(data, sizeof(data));
            
   /* fill CmLteRlcId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(datReq->rlcId.rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(datReq->rlcId.rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(datReq->rlcId.ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(datReq->rlcId.cellId));
   /* Fill SDU ID from kwAcCb.kwuCb.nxtSduId */
   if (entity == ENTNH)
   {
      datReq->sduId = kwAcCb.nhKwuCb.nxtSduId;
      kwAcCb.nhKwuCb.nxtSduId++;
   }
#ifndef KW_PDCP
   else
   {
      datReq->sduId = kwAcCb.pjKwuCb.nxtSduId;
      datReq->lcType = CM_LTE_LCH_DTCH;
      kwAcCb.pjKwuCb.nxtSduId++;
   }
#endif /* KW_PDCP */

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "sduSize", &(sduSize));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sData", &(sData));

#ifdef CCPU_OPT
   if (entity == ENTNH)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "type", &(datReq->lcType));

      /* Fill BCCH or PCCH Information */
      if ((datReq->lcType == CM_LTE_LCH_BCCH) ||
            (datReq->lcType == CM_LTE_LCH_PCCH))
      {
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
               "sfn", &(datReq->tm.tmg.sfn));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
               "subframe", &(datReq->tm.tmg.subframe));
      }
      else if (datReq->lcType == CM_LTE_LCH_CCCH)
      {
         /* Fill CCCH Information */
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
               "rnti", &(datReq->tm.rnti));
      }
   }
#endif /* CCPU_OPT */

   /* Allocate memory for SDU mBuf */
   if (SGetMsg(DFLT_REGION, DFLT_POOL, mBuf) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcUtlBuildKwuDatReq(): resource unavailble \n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } /* end of if statement */

   KWAC_FORM_SDU(data, sduSize, sData, mBuf);

   /* Copy datReq to kwAcCb.nhKwuCb/pjKwuCb */
   if (kwAcUtlCpyKwuDatReq(datReq, *mBuf, sduSize, entity) != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlBuildKwuDatReq */

#ifdef ANSI
PUBLIC S16 kwAcUtlCmpKwuDatReqBuf
(
Buffer *srcBuf,
Buffer *dstBuf,
U32    size
)
#else
PUBLIC S16 kwAcUtlCmpKwuDatReqBuf(srcBuf, dstBuf, size)
Buffer *srcBuf;
Buffer *dstBuf;
U32    size;
#endif
{
   Data     srcData[5000], dstData[5000];
   MsgLen   srcLen = 0, dstLen = 0, len = 0;
   S16      idx = 0;

   TRC2(kwAcUtlCmpKwuDatReqBuf);

   /* kw005.201 removed warning */
   UNUSED(size);
   
   CMXTA_ZERO(srcData, sizeof(srcData));
   CMXTA_ZERO(dstData, sizeof(dstData));

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
} /* kwAcUtlCmpKwuDatReqBuf */


/**
 * @brief Validate KWU Data Indication
 *
 * @details
 *
 *     Function : kwAcUtlValdtKwuDatInd
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
PUBLIC S16 kwAcUtlValdtKwuDatInd
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwAcMsgQElm       *kwElm,
U8                entity
)
#else
PUBLIC S16 kwAcUtlValdtKwuDatInd(tcCb, spCb, kwElm, entity)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
KwAcMsgQElm       *kwElm;
U8                entity;
#endif
{
   KwuDatIndInfo        *datInd;
   KwAcKwuDatReq        *datReq = NULLP;
   Buffer               *mBuf;
   CmLteRlcId           *rlcId = NULLP;
   CmLteRnti            tCrnti;
   S16                  idx;
   S32                  sduId;
   U8                   valdType = 0;
   Bool                 recvIsOutOfSeq = FALSE;
   Bool                 expIsOutOfSeq  = FALSE;
   Bool                 ulDatFwd       = FALSE;

   TRC2(kwAcUtlValdtKwuDatInd);

   tCrnti = 0;
   sduId = -1;
   mBuf = kwElm->mBuf;
   datInd = kwElm->u.kwuInfo.u.datInd;
   
   /* <tapa.kwu.datind valdType="0" sduId="1" />
    */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "valdType", &(valdType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "sduId", &(sduId));

   /* valdType: 0 - Perform validation.
    * valdType: 1 - Skip validation.
    */
   if (valdType == 1)
   {
      if (entity ==ENTNH)
      {
         idx = kwAcUtlKwuDatReqCircQGetFront(&kwAcCb.nhKwuCb.datReq);
         datReq = &kwAcCb.nhKwuCb.datReq.node[idx];
         /* Free the Buffers and datInd */
       //  printf(" freeing mBuf in KwuDatInd with valdType=1 %u\n\n", datReq->mBuf);
         KW_FREE_BUF(datReq->mBuf);           
         /* Memset to 0 for datReq
         * This make isInQ flag to 0 (FALSE) */
         CMXTA_ZERO(datReq, sizeof(KwAcKwuDatReq)); 
         /* Remove the msg from datReq Q if possible */
         /* Remove the msg from datReq Q if possible */
         kwAcUtlKwuDatReqCircQDequeue(&kwAcCb.nhKwuCb.datReq);
      }
#ifndef KW_PDCP
      else
      {
         idx = kwAcUtlKwuDatReqCircQGetFront(&kwAcCb.pjKwuCb.datReq);
         datReq = &kwAcCb.pjKwuCb.datReq.node[idx];
         /* Free the Buffers and datInd */
       //  printf(" freeing mBuf in KwuDatInd with valdType=1 %u\n\n", datReq->mBuf);
         KW_FREE_BUF(datReq->mBuf);           
         /* Memset to 0 for datReq
         * This make isInQ flag to 0 (FALSE) */
         CMXTA_ZERO(datReq, sizeof(KwAcKwuDatReq)); 
         /* Remove the msg from datReq Q if possible */
         kwAcUtlKwuDatReqCircQDequeue(&kwAcCb.pjKwuCb.datReq);
      }
#endif /* KW_PDCP */

      RETVALUE(CMXTA_ERR_NONE);
   }

   for(idx = 0; idx < kwAcCb.mapDlUlCb.count; idx++)
   {
      if(kwAcCb.mapDlUlCb.mapDlUl[idx].ueId == datInd->rlcId.ueId &&
         kwAcCb.mapDlUlCb.mapDlUl[idx].cellId ==  datInd->rlcId.cellId)
      {
         if (entity == ENTNH)
         {
            rlcId = &(kwAcCb.mapDlUlCb.mapDlUl[idx].\
                  srbCb[(datInd->rlcId.rbId)].othRlcId);   
            break;
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
                     srbCb[(datInd->rlcId.rbId)].othRlcId);   
            }
            else
            {
               rlcId = &(kwAcCb.mapDlUlCb.mapDlUl[idx].\
                     drbCb[(datInd->rlcId.rbId)].othRlcId);   
            }
            break;
         }
#endif /* KW_PDCP */
      }
   }

   /* get rlc id */
   if (entity == ENTNH)
   {
      idx = kwAcUtlKwuDatReqCircQGetFront(&kwAcCb.nhKwuCb.datReq);
      do
      {
          datReq = &kwAcCb.nhKwuCb.datReq.node[idx];
          if (rlcId && ((rlcId->ueId == datReq->datReq.rlcId.ueId) &&
              (rlcId->cellId == datReq->datReq.rlcId.cellId) &&
              (rlcId->rbId == datReq->datReq.rlcId.rbId) &&
              (rlcId->rbType == datReq->datReq.rlcId.rbType)))
          {
              break;
          }
          idx = kwAcUtlKwuDatReqCircQGetNext(&kwAcCb.nhKwuCb.datReq, idx);
      } while (idx);
      if (!idx)
      {
         CMXTA_DBG_PARAM((_cmxtap, "Failed - idx not found\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }
#ifdef KW_PDCP
   else
   {
      CMXTA_DBG_PARAM((_cmxtap, "Failed - entity is wrong.\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
#else
   else
   {
      idx = kwAcUtlKwuDatReqCircQGetFront(&kwAcCb.pjKwuCb.datReq);
      do
      {
          datReq = &kwAcCb.pjKwuCb.datReq.node[idx];
          if (rlcId && ((rlcId->ueId == datReq->datReq.rlcId.ueId) &&
              (rlcId->cellId == datReq->datReq.rlcId.cellId) &&
              (rlcId->rbId == datReq->datReq.rlcId.rbId) &&
              (rlcId->rbType == datReq->datReq.rlcId.rbType)))  
          {
              if (sduId == -1 || sduId == (S32)datReq->datReq.sduId)
                 break;
              
          }
          idx = kwAcUtlKwuDatReqCircQGetNext(&kwAcCb.pjKwuCb.datReq, idx);
      } while (idx);
      if (!idx)
      {
         CMXTA_DBG_PARAM((_cmxtap, "Failed - idx not found\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }  
#endif /* KW_PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "ulDatFwd", &(ulDatFwd));
   if(ulDatFwd)
   {
        recvIsOutOfSeq = kwElm->u.kwuInfo.u.datInd->isOutOfSeq;
        cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isOutOfSeq", &(expIsOutOfSeq));
	if(recvIsOutOfSeq != expIsOutOfSeq)
        {
                CMXTA_DBG_PARAM((_cmxtap, "OutOfSeq is wrong"));
		RETVALUE(CMXTA_ERR_INT);
        }
   } 
   /* validate buffer */
   if (kwAcUtlCmpKwuDatReqBuf(datReq->mBuf, mBuf, datReq->sduSize) !=
         CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap,
               "kwAcUtlCmpKwuDatReqBuf(): mBuf comarision Failed.\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Free the Buffers and datInd */
   KW_FREE_BUF(datReq->mBuf);                /*free the stored mBuf */

   /* Memset to 0 for datReq
    * This make isInQ flag to 0 (FALSE) */
   CMXTA_ZERO(datReq, sizeof(KwAcKwuDatReq));/* Memset to 0 for datReq */

   if (entity ==ENTNH)
   {
      /* Remove the msg from datReq Q if possible */
      kwAcUtlKwuDatReqCircQDequeue(&kwAcCb.nhKwuCb.datReq);
   }
#ifndef KW_PDCP
   else
   {
      /* Remove the msg from datReq Q if possible */
      kwAcUtlKwuDatReqCircQDequeue(&kwAcCb.pjKwuCb.datReq);
   }
#endif /* KW_PDCP */

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlValdtKwuDatInd */


/**
@brief utility function for releasing CmXtaMsgQElm
@param qElm
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlKwuFreeCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 kwAcUtlKwuFreeCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   KwAcMsgQElm *kwElm;

   TRC2(kwAcUtlLkwFreeCb);

   CMXTA_DBG_PARAM((_cmxtap, "kwAcUtlKwuFreeCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   if(kwElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   switch (qElm->pst.event)
   {
      case KWU_EVT_BND_CFM:
         break;
      case KWU_EVT_DAT_IND:
         KW_FREE_ACC(kwElm->u.kwuInfo.u.datInd, sizeof(KwuDatIndInfo));
         break;
      case KWU_EVT_DAT_CFM:
         KW_FREE_ACC(kwElm->u.kwuInfo.u.datCfm, sizeof(KwuDatCfmInfo));
         break;
      case KWU_EVT_STA_IND:
         KW_FREE_ACC(kwElm->u.kwuInfo.u.staInd, sizeof(KwuStaIndInfo));
         break;
      /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
      case KWU_EVT_DISC_SDU_CFM:
         KW_FREE_ACC(kwElm->u.kwuInfo.u.discSduCfm, sizeof(KwuDiscSduInfo));
         break;
      case KWU_EVT_DAT_ACK_IND:
         KW_FREE_ACC(kwElm->u.kwuInfo.u.datAckInd, sizeof(KwuDatAckInfo));
         break;
#endif /* LTE_L2_MEAS */
      default:
         CMXTA_DBG_CALLIND((_cmxtap, "Failed - kwAcUtlKwuFreeCb: event(%d) is wrong\n",
                  qElm->pst.event), 2);
         RETVALUE(CMXTA_ERR_INT);

   }

   if(kwElm->mBuf != NULLP)
      CMXTA_FREEMBUF(kwElm->mBuf);

   CMXTA_FREE(kwElm, sizeof (KwAcMsgQElm));
   qElm->data = NULLP;

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlKwuFreeCb */

  
/*************************************************************************
 *                KWU DAT REQ QUEUE PRIMITIVES START
 *************************************************************************/
/**
 * @brief Circular Queue for KWU Data Request Interface
 *
 * @details
 *
 *     Function : kwAcUtlKwuDatReqCQMakeNull
 *
 *     This function Initializes the KWU DatReq Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void kwAcUtlKwuDatReqCQMakeNull
(
KwAcKwuDatReqQ    *queue
)
#else
PUBLIC Void kwAcUtlKwuDatReqCQMakeNull(queue)
KwAcKwuDatReqQ    *queue;
#endif
{
   queue->front = 1;
   queue->rear = KWAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* kwAcUtlKwuDatReqCQMakeNull */

/** @breif It increments index exactly
 * @param[in] queue - Kwu Data Request Queue
 * @return index
 * */
#ifdef ANSI
PUBLIC U16 kwAcUtlKwuDatReqCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 kwAcUtlKwuDatReqCircQAddOne(idx)
U16 idx;
#endif
{
   /* kw005.201 Changes for R9 RLC test cases*/
   /* 0x3FF below is KWAC_MAX_CIRCQ_SIZE(currently 1024) - 1 */
   if (idx == 0x3FF)
      RETVALUE(1);
   else
      RETVALUE((idx + 1) & 0x3FF);
} /* kwAcUtlKwuDatReqCircQAddOne */

/** @breif It moves rear index by one if Queue is not full
 * @param[in] queue - Kwu Data Request Queue
 * @return front index
 * */
#ifdef ANSI
PUBLIC U16 kwAcUtlKwuDatReqCircQEnqueue
(
KwAcKwuDatReqQ *queue
)
#else
PUBLIC U16 kwAcUtlKwuDatReqCircQEnqueue(queue)
KwAcKwuDatReqQ *queue;
#endif
{
   /* Making 3 length difference between rear and front to make
    * sure Q is full
    */
   if (kwAcUtlKwuDatReqCircQAddOne(kwAcUtlKwuDatReqCircQAddOne(
               kwAcUtlKwuDatReqCircQAddOne(queue->rear))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlKwuDatReqCircQEnqueue(): KWU DatReq Queue is full\n"));
      RETVALUE(0);
   }

   queue->rear = kwAcUtlKwuDatReqCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* kwAcUtlKwuDatReqCircQEnqueue */

/** @breif It returns the Front index if Queue is not empty
 * else returns 0
 * @param[in] queue - Kwu Data Request Queue
 * @return front index
 * */
#ifdef ANSI
PUBLIC U16 kwAcUtlKwuDatReqCircQGetFront
(
KwAcKwuDatReqQ *queue
)
#else
PUBLIC U16 kwAcUtlKwuDatReqCircQGetFront(queue)
KwAcKwuDatReqQ *queue;
#endif
{
   if(KWAC_UTL_KWU_DATREQ_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlKwuDatReqCircQGetFront(): KWU DatReq Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* kwAcUtlKwuDatReqCircQGetFront */

/** @breif It returns the valid idx if Queue is not empty
 * @param[in] queue - Kwu Data Request Queue
 * @param[in] idx   - present index
 * @return Next Valid index
 * */
#ifdef ANSI
PUBLIC U16 kwAcUtlKwuDatReqCircQGetNext
(
KwAcKwuDatReqQ   *queue,
U16            idx
)
#else
PUBLIC U16 kwAcUtlKwuDatReqCircQGetNext(queue, idx)
KwAcKwuDatReqQ   *queue;
U16            idx;
#endif
{
   /* Check whether we reached front or not (empty) */
   if ((idx >= queue->rear) && ((queue->rear == queue->front) ||
         (kwAcUtlKwuDatReqCircQAddOne(idx) == queue->front)))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlKwuDatReqCircQGetNext(): KWU DatReq Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(kwAcUtlKwuDatReqCircQAddOne(idx));
} /* kwAcUtlKwuDatReqCircQGetNext */

/** @breif It moves front pointer by one
 * @param[in] queue - Kwu Data Request Queue
 * @return None
 * */
#ifdef ANSI
PUBLIC Void kwAcUtlKwuDatReqCircQDequeue
(
KwAcKwuDatReqQ *queue
)
#else
PUBLIC Void kwAcUtlKwuDatReqCircQDequeue(queue)
KwAcKwuDatReqQ *queue;
#endif
{
   if(KWAC_UTL_KWU_DATREQ_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,\
               "kwAcUtlKwuDatReqCircQDequeue(): KWU DatReq Queue is empty\n"));
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = kwAcUtlKwuDatReqCircQAddOne(queue->front);
      if(KWAC_UTL_KWU_DATREQ_CQ_ISEMPTY(queue))
         break;
   }

   RETVOID;
} /* kwAcUtlKwuDatReqCircQDequeue */

/*************************************************************************
 *                KWU DAT REQ QUEUE PRIMITIVES END
 *************************************************************************/

  
/*************************************************************************
 *                KWU DAT CFM QUEUE PRIMITIVES START
 *************************************************************************/
/**
 * @brief Circular Queue for KWU Data Confirm Interface
 *
 * @details
 *
 *     Function : kwAcUtlKwuDatCfmCQMakeNull
 *
 *     This function Initializes the KWU DatCfm Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void kwAcUtlKwuDatCfmCQMakeNull
(
KwAcKwuDatCfmQ    *queue
)
#else
PUBLIC Void kwAcUtlKwuDatCfmCQMakeNull(queue)
KwAcKwuDatCfmQ    *queue;
#endif
{
   queue->front = 1;
   queue->rear = KWAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* kwAcUtlKwuDatCfmCQMakeNull */

#ifdef ANSI
PUBLIC U16 kwAcUtlKwuDatCfmCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 kwAcUtlKwuDatCfmCircQAddOne(idx)
U16 idx;
#endif
{
   /* kw005.201 Changes for R9 RLC test cases*/
   /* 0x3FF below is KWAC_MAX_CIRCQ_SIZE(currently 1024) - 1 */
   if (idx == 0x3FF)
      RETVALUE(1);
   else
      RETVALUE((idx + 1) & 0x3FF);
} /* kwAcUtlKwuDatCfmCircQAddOne */

#ifdef ANSI
PUBLIC S16 kwAcUtlKwuDatCfmCircQEnqueue
(
KwAcKwuDatCfmQ *queue
)
#else
PUBLIC S16 kwAcUtlKwuDatCfmCircQEnqueue(queue)
KwAcKwuDatCfmQ *queue;
#endif
{
   if(kwAcUtlKwuDatCfmCircQAddOne(kwAcUtlKwuDatCfmCircQAddOne(\
               kwAcUtlKwuDatCfmCircQAddOne(kwAcUtlKwuDatCfmCircQAddOne(\
                     queue->rear)))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlKwuDatCfmCircQEnqueue(): KWU DatCfm Queue is full\n"));
      RETVALUE(-1);
   }

   queue->rear = kwAcUtlKwuDatCfmCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* kwAcUtlKwuDatReqCircQEnqueue */

#ifdef ANSI
PUBLIC U16 kwAcUtlKwuDatCfmCircQGetFront
(
KwAcKwuDatCfmQ *queue
)
#else
PUBLIC U16 kwAcUtlKwuDatCfmCircQGetFront(queue)
KwAcKwuDatCfmQ *queue;
#endif
{
   if(KWAC_UTL_KWU_DATCFM_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlKwuDatCfmCircQGetFront(): KWU DatCfm Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* kwAcUtlKwuDatCfmCircQGetFront */

#ifdef ANSI
PUBLIC S16 kwAcUtlKwuDatCfmCircQGetNext
(
KwAcKwuDatCfmQ   *queue,
U16            idx
)
#else
PUBLIC S16 kwAcUtlKwuDatCfmCircQGetNext(queue, idx)
KwAcKwuDatCfmQ   *queue;
U16            idx;
#endif
{
   if (kwAcUtlKwuDatCfmCircQAddOne(idx) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlKwuDatCfmCircQGetNext(): KWU DatCfm Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(kwAcUtlKwuDatCfmCircQAddOne(queue->front));
} /* kwAcUtlKwuDatCfmCircQGetNext */

#ifdef ANSI
PUBLIC Void kwAcUtlKwuDatCfmCircQDequeue
(
KwAcKwuDatCfmQ *queue
)
#else
PUBLIC Void kwAcUtlKwuDatCfmCircQDequeue(queue)
KwAcKwuDatCfmQ *queue;
#endif
{
   if(KWAC_UTL_KWU_DATCFM_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlKwuDatCfmCircQDequeue(): KWU DatCfm Queue is empty\n"));
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = kwAcUtlKwuDatCfmCircQAddOne(queue->front);
      if(KWAC_UTL_KWU_DATCFM_CQ_ISEMPTY(queue))
         break;
   }

   RETVOID;
} /* kwAcUtlKwuDatCfmCircQDequeue */


U32 rlculDrop;
U32 isMemThreshReached(Region region)
{
   return FALSE;
}

U32 TtiCount = 0;
Void SIncrementTtiCount(Void)
{
   TtiCount++;
}

U32 SGetTtiCount(Void)
{
   return TtiCount;
}

/*
/*************************************************************************
 *                KWU DAT CFM QUEUE PRIMITIVES END
 *************************************************************************/

/********************************************************************30**

         End of file:     kwac_kwuutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/6 - Mon Feb 15 12:52:37 2016

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
/main/1      ---   cp         1. Initial release.
/main/2      ---   gk         1. LTE RLC Release 2.1.
/main/3      kw005.201 ap     1. Removed compilation warning 
                       rd     2. Changes wrt macro KWAC_MAX_CIRCQ_SIZE
                   			      for RLC R9 TCs in functions 
                      				kwAcUtlKwuDatReqCircQAddOne and 
                      				kwAcUtlKwuDatCfmCircQAddOne.
*********************************************************************91*/

