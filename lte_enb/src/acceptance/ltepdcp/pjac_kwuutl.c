

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_kwuutl.c

     Sid:      pjac_kwuutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:53:09 2016

     Prg:     Vartika
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
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_kwu.h"      /* KWU Acceptance defines */
#include "pjac_lib.h"      /* Lib Acceptance defines */

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
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_kwu.x"      /* CKW Acceptance defines */


#ifdef ANSI
PUBLIC S16 pjAcUtlCmpKwuDatReqBuf
(
Buffer *srcBuf,
Buffer *dstBuf,
U32    size
)
#else
PUBLIC S16 pjAcUtlCmpKwuDatReqBuf(srcBuf, dstBuf, size)
Buffer *srcBuf;
Buffer *dstBuf;
U32    size;
#endif
{
   Data     srcData[5000], dstData[5000];
   MsgLen   srcLen = 0, dstLen = 0, len = 0;
   S16      idx = 0;

   TRC2(pjAcUtlCmpKwuDatReqBuf);

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
} /* pjAcUtlCmpKwuDatReqBuf */


/**
@brief utility function for releasing CmXtaMsgQElm
@param qElm
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcUtlKwuFreeCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 pjAcUtlKwuFreeCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   KwAcMsgQElm *kwElm;

   TRC2(pjAcUtlLkwFreeCb);

   CMXTA_DBG_PARAM((_cmxtap, "pjAcUtlKwuFreeCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   kwElm = (KwAcMsgQElm *)qElm->data;

   if(kwElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   switch (qElm->pst.event)
   {
      case KWU_EVT_BND_REQ:
         break;
      case KWU_EVT_BND_CFM:
         break;
      case KWU_EVT_DISC_SDU_REQ:
         /* TODO */
         break;
      case KWU_EVT_DAT_REQ:
         KW_FREE_ACC(kwElm->u.kwuInfo.u.datReq, sizeof(KwuDatReqInfo));
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
         CMXTA_DBG_CALLIND((_cmxtap, "Failed - pjAcUtlKwuFreeCb: event(%d) is wrong\n",
                  qElm->pst.event), 2);
         RETVALUE(CMXTA_ERR_INT);

   }

   if(kwElm->mBuf != NULLP)
      CMXTA_FREEMBUF(kwElm->mBuf);

   CMXTA_FREE(kwElm, sizeof (KwAcMsgQElm));
   qElm->data = NULLP;

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcUtlKwuFreeCb */


/*************************************************************************
 *                KWU DAT REQ QUEUE PRIMITIVES START
 *************************************************************************/
/**
 * @brief Circular Queue for KWU Data Request Interface
 *
 * @details
 *
 *     Function : pjAcUtlKwuDatReqCQMakeNull
 *
 *     This function Initializes the KWU DatReq Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void pjAcUtlKwuDatReqCQMakeNull
(
PjAcKwuDatReqQ    *queue
)
#else
PUBLIC Void pjAcUtlKwuDatReqCQMakeNull(queue)
PjAcKwuDatReqQ    *queue;
#endif
{
   queue->front = 1;
   queue->rear = PJAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* pjAcUtlKwuDatReqCQMakeNull */

/** @breif It increments index exactly
 * @param[in] queue - Kwu Data Request Queue
 * @return index
 * */
#ifdef ANSI
PUBLIC U16 pjAcUtlKwuDatReqCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 pjAcUtlKwuDatReqCircQAddOne(idx)
U16 idx;
#endif
{
   /* kw005.201 Changes for R9 RLC test cases*/
   /* 0x3FF below is PJAC_MAX_CIRCQ_SIZE(currently 1024) - 1 */
   if (idx == 0x3FF)
      RETVALUE(1);
   else
      RETVALUE((idx + 1) & 0x3FF);
} /* pjAcUtlKwuDatReqCircQAddOne */

/** @breif It moves rear index by one if Queue is not full
 * @param[in] queue - Kwu Data Request Queue
 * @return front index
 * */
#ifdef ANSI
PUBLIC U16 pjAcUtlKwuDatReqCircQEnqueue
(
PjAcKwuDatReqQ *queue
)
#else
PUBLIC U16 pjAcUtlKwuDatReqCircQEnqueue(queue)
PjAcKwuDatReqQ *queue;
#endif
{
   /* Making 3 length difference between rear and front to make
    * sure Q is full
    */
   if (pjAcUtlKwuDatReqCircQAddOne(pjAcUtlKwuDatReqCircQAddOne(
               pjAcUtlKwuDatReqCircQAddOne(queue->rear))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "pjAcUtlKwuDatReqCircQEnqueue(): KWU DatReq Queue is full\n"));
      queue->rear = 1;
      RETVALUE(1);       /* TEST_CASE_FIX 1.31 */
   }

   queue->rear = pjAcUtlKwuDatReqCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* pjAcUtlKwuDatReqCircQEnqueue */

/** @breif It returns the Front index if Queue is not empty
 * else returns 0
 * @param[in] queue - Kwu Data Request Queue
 * @return front index
 * */
#ifdef ANSI
PUBLIC U16 pjAcUtlKwuDatReqCircQGetFront
(
PjAcKwuDatReqQ *queue
)
#else
PUBLIC U16 pjAcUtlKwuDatReqCircQGetFront(queue)
PjAcKwuDatReqQ *queue;
#endif
{
   if(PJAC_UTL_KWU_DATREQ_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "pjAcUtlKwuDatReqCircQGetFront(): KWU DatReq Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* pjAcUtlKwuDatReqCircQGetFront */

/** @breif It returns the valid idx if Queue is not empty
 * @param[in] queue - Kwu Data Request Queue
 * @param[in] idx   - present index
 * @return Next Valid index
 * */
#ifdef ANSI
PUBLIC U16 pjAcUtlKwuDatReqCircQGetNext
(
PjAcKwuDatReqQ   *queue,
U16            idx
)
#else
PUBLIC U16 pjAcUtlKwuDatReqCircQGetNext(queue, idx)
PjAcKwuDatReqQ   *queue;
U16            idx;
#endif
{
   /* Check whether we reached front or not (empty) */
   if ((idx >= queue->rear) && ((queue->rear == queue->front) ||
         (pjAcUtlKwuDatReqCircQAddOne(idx) == queue->front)))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "pjAcUtlKwuDatReqCircQGetNext(): KWU DatReq Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(pjAcUtlKwuDatReqCircQAddOne(idx));
} /* pjAcUtlKwuDatReqCircQGetNext */

/** @breif It moves front pointer by one
 * @param[in] queue - Kwu Data Request Queue
 * @return None
 * */
#ifdef ANSI
PUBLIC Void pjAcUtlKwuDatReqCircQDequeue
(
PjAcKwuDatReqQ *queue
)
#else
PUBLIC Void pjAcUtlKwuDatReqCircQDequeue(queue)
PjAcKwuDatReqQ *queue;
#endif
{
   if(PJAC_UTL_KWU_DATREQ_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,\
               "pjAcUtlKwuDatReqCircQDequeue(): KWU DatReq Queue is empty\n"));
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = pjAcUtlKwuDatReqCircQAddOne(queue->front);
      if(PJAC_UTL_KWU_DATREQ_CQ_ISEMPTY(queue))
         break;
   }

   RETVOID;
} /* pjAcUtlKwuDatReqCircQDequeue */

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
 *     Function : pjAcUtlKwuDatCfmCQMakeNull
 *
 *     This function Initializes the KWU DatCfm Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void pjAcUtlKwuDatCfmCQMakeNull
(
PjAcKwuDatCfmQ    *queue
)
#else
PUBLIC Void pjAcUtlKwuDatCfmCQMakeNull(queue)
PjAcKwuDatCfmQ    *queue;
#endif
{
   queue->front = 1;
   queue->rear = PJAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* pjAcUtlKwuDatCfmCQMakeNull */

#ifdef ANSI
PUBLIC U16 pjAcUtlKwuDatCfmCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 pjAcUtlKwuDatCfmCircQAddOne(idx)
U16 idx;
#endif
{
   /* kw005.201 Changes for R9 RLC test cases*/
   /* 0x3FF below is PJAC_MAX_CIRCQ_SIZE(currently 1024) - 1 */
   if (idx == 0x3FF)
      RETVALUE(1);
   else
      RETVALUE((idx + 1) & 0x3FF);
} /* pjAcUtlKwuDatCfmCircQAddOne */

#ifdef ANSI
PUBLIC S16 pjAcUtlKwuDatCfmCircQEnqueue
(
PjAcKwuDatCfmQ *queue
)
#else
PUBLIC S16 pjAcUtlKwuDatCfmCircQEnqueue(queue)
PjAcKwuDatCfmQ *queue;
#endif
{
   if(pjAcUtlKwuDatCfmCircQAddOne(pjAcUtlKwuDatCfmCircQAddOne(\
               pjAcUtlKwuDatCfmCircQAddOne(pjAcUtlKwuDatCfmCircQAddOne(\
                     queue->rear)))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "pjAcUtlKwuDatCfmCircQEnqueue(): KWU DatCfm Queue is full\n"));
      RETVALUE(-1);
   }

   queue->rear = pjAcUtlKwuDatCfmCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* pjAcUtlKwuDatReqCircQEnqueue */

#ifdef ANSI
PUBLIC U16 pjAcUtlKwuDatCfmCircQGetFront
(
PjAcKwuDatCfmQ *queue
)
#else
PUBLIC U16 pjAcUtlKwuDatCfmCircQGetFront(queue)
PjAcKwuDatCfmQ *queue;
#endif
{
   if(PJAC_UTL_KWU_DATCFM_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "pjAcUtlKwuDatCfmCircQGetFront(): KWU DatCfm Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* pjAcUtlKwuDatCfmCircQGetFront */

#ifdef ANSI
PUBLIC S16 pjAcUtlKwuDatCfmCircQGetNext
(
PjAcKwuDatCfmQ   *queue,
U16            idx
)
#else
PUBLIC S16 pjAcUtlKwuDatCfmCircQGetNext(queue, idx)
PjAcKwuDatCfmQ   *queue;
U16            idx;
#endif
{
   if (pjAcUtlKwuDatCfmCircQAddOne(idx) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "pjAcUtlKwuDatCfmCircQGetNext(): KWU DatCfm Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(pjAcUtlKwuDatCfmCircQAddOne(queue->front));
} /* pjAcUtlKwuDatCfmCircQGetNext */

#ifdef ANSI
PUBLIC Void pjAcUtlKwuDatCfmCircQDequeue
(
PjAcKwuDatCfmQ *queue
)
#else
PUBLIC Void pjAcUtlKwuDatCfmCircQDequeue(queue)
PjAcKwuDatCfmQ *queue;
#endif
{
   if(PJAC_UTL_KWU_DATCFM_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "pjAcUtlKwuDatCfmCircQDequeue(): KWU DatCfm Queue is empty\n"));
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = pjAcUtlKwuDatCfmCircQAddOne(queue->front);
      if(PJAC_UTL_KWU_DATCFM_CQ_ISEMPTY(queue))
         break;
   }

   RETVOID;
} /* pjAcUtlKwuDatCfmCircQDequeue */

/**
 * @brief Validate Data Request from PDCP
 *
 * @details
 *
 *     Function : pjAcUtlValdtKwuDatReq
 *
 *     This function Validates kwuDatReqInfo structure recieved from PDCP
 *
 *  @param[in]  *tcCb
 *  @param[in]  *spCb
 *  @param[in]  *datReq
 *  @param[in]  *mBuf
 *  @param[in]  *transId
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 pjAcUtlValdtKwuDatReq
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwuDatReqInfo    *datReq,
Buffer           *mBuf
)
#else
PUBLIC S16 pjAcUtlValdtKwuDatReq(tcCb, spCb, datReq)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
KwuDatReqInfo     *datReq;
Buffer            *mBuf;
#endif
{

   CmLteCellId    cellId = 0;
   CmLteRnti      ueId = 0;
   U32            transId = 0;
   U16            idx = 0, idx2 = 0;
   S16            ret;
   Txt            lchDataStr[512];
   Txt            *holdMain = NULLP, *tokMain = NULLP, *tok1 = NULLP;
   Txt            *holdSub = NULLP, *tokSub = NULLP, *tok2 = NULLP;
   Txt            *holdNextSub = NULLP, *tokNextSub = NULLP, *tok3 = NULLP;
   U16            tokCount = 0, i = 0, j = 0;
   RguLchDatReq   *lchData = NULLP;
   U8             valdType = 0;
   KwAcLcCb       *lcCb = NULLP;
   U8             mode = 3;
   S16            rbId = -1;
   S16            pdcpSn = -1;
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   Bool           snMapPres = FALSE;
   RguSnMapInfo  *rguSnInfo = NULLP;
#endif /* LTE_L2_MEAS */
   Bool           vrfPdcp = FALSE;
   U8             rlcsn = 5;
   Txt            pdcpHdrStr[512];
   Bool           vrfCmp = FALSE;
   Bool           vrfNoSec = FALSE;
   Bool           vrfSec = FALSE;
   Bool           vrfNoCiph = FALSE;
   Bool           pass = TRUE;
   TRC2(pjAcUtlValdtKwuDatReq);
                                                                                                                                                                        
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &cellId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &ueId);
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "snMapPres",  &snMapPres);
#endif
                                                                                                                                                                        
   /* Call Header validation if requried */
   /* <tapa.rgu.ddatreq cellId="1" ueId="1" 
    *  lchData="bo:estRlcHdrSz:staPduPrsnt:rbId:numPdu:pduSzLst:pduHdrLst"
    *  lchData="2050:4:1:1:3:2050"
    *  vrfPdcp="TRUE" snSize="7" mode="3" (2-UM, 3-AM in case of szSize=12)
    *  pdcpHdr="D/C:pduType:SN:FMS" intgProt="FALSE" ciph="FALSE"
    *  />
    */
   /* lcId is command level attribute to overwrite lcId in lchData */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "rbId", &(rbId));
                                                                                                                                                                        
   /* pdcpSn is command level attribute to overwrite SN in pdcpHdr */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "pdcpSn", &(pdcpSn));
                                                                                                                                                                        
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lchData", &(lchDataStr));
                                                                                                                                                                        
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "valdType", &(valdType));
                                                                                                                                                                        
   /* Verify PDCP header if vrfPDCP is TRUE */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "vrfPdcp", &(vrfPdcp));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "vrfPdcp0", &(vrfPdcp));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "pass", &(pass));

   /* commented for bringing up the acc */
   vrfPdcp = FALSE;                                                                                                                                                                     
   if (vrfPdcp == TRUE) 
   {
      S8    snSize = 7;
      S16   sn = 0;
      S16   fms = 0;
      S8    dc = 0;
      S8    pduType = 0;
      Data  hdrByte[2];
                                                                                                                                                                        
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mode", &(mode));
      
      /* Read SN size.
       * snSize = 5: means Control plane SRBs.
       * snSize = 7: means User plane UM DRBs.
       * snSize = 12: means User plane AM/UM DRBs.
       * snSize = 15: means User plane AM DRBs.
       */
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "snSize", &(snSize));
                                                                                                                                                                        
      switch(snSize)
      {
         case 5:
            {
               mode = 3;
               ret = SRemPreMsgMult(hdrByte, 1, mBuf);
               dc = -1;
               sn = hdrByte[0] & 0x1F;
               pduType = -1;
               fms = -1;
               break;
            }
         case 7:
            {
               mode = 2;
               ret = SRemPreMsgMult(hdrByte, 1, mBuf);
               dc = (hdrByte[0] >> 7) & 0x01;
               if (dc == 1)
               {
                  sn = hdrByte[0] & 0x7F;
                  pduType = -1;
                  fms = -1;
               }
               else
               {
                  sn = -1;
                  pduType = (hdrByte[0] >> 4) & 0x07;
                  fms = -1;
               }
               break;
            }
         case 12:
            {
               mode = 3;
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mode", &(mode));
               ret = SRemPreMsgMult(hdrByte, 2, mBuf);
               dc = (hdrByte[0] >> 7) & 0x01;
               if (dc == 1)
               {
                  sn = ((U16)(hdrByte[0] & 0x0F)) << 8;
                  sn |= (hdrByte[1]);
                  pduType = -1;
                  fms = -1;
               }
               else
               {
                  sn = -1;
                  pduType = (hdrByte[0] >> 4) & 0x07;
                  fms = ((U16)(hdrByte[0] & 0x0F)) << 8;
                  fms |= (hdrByte[1]);
               }
               break;
            }
      }
                                                                                                                                                                        
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "pdcpHdr", &(pdcpHdrStr));
      for (holdMain = pdcpHdrStr;;holdMain=NULLP)
      {
         tokMain = (Txt *) strtok_r(holdMain, ";", &tok1);
                                                                                                                                                                        
         if (tokMain == NULLP) break;
                                                                                                                                                                        
         for (holdSub = tokMain, i = 0; i < 4; i++, holdSub=NULLP)
         {
            if ((tokSub=(Txt *) strtok_r(holdSub,":",&tok2)) == NULLP)
               break;
                                                                                                                                                                        
            switch(i)
            {
               case 0:
                  {
                     S8 tdc;
                     tdc = atoi(tokSub);
                     if ((tdc == -1) || dc == -1)
                        break;
                                                                                                                                                                        
                     if (dc != tdc)
                     {
                        CMXTA_DBG_CALLIND((_cmxtap, "DC MisMatch: exp (%d) rcvd (%d) \n",
                                 dc, tdc), 2);
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
                                                                                                                                                                        
               case 1:
                  {
                     S8 tpduType;
                     tpduType = atoi(tokSub);
                     if (tpduType == -1)
                        break;
                                                                                                                                                                        
                     if (tpduType != pduType)
                     {
                        CMXTA_DBG_CALLIND((_cmxtap, "pduType MisMatch: exp (%d) rcvd (%d) \n",
                                 pduType, tpduType), 2);
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 2:
                  {
                     S16   tsn;
                     tsn = atoi(tokSub);
                     if (pdcpSn != -1)
                        tsn = pdcpSn;
                     if (tsn == -1)
                        break;
                                                                                                                                                                        
                     if (sn != tsn)
                     {
                        CMXTA_DBG_CALLIND((_cmxtap, "SN MisMatch: exp (%d) rcvd (%d) \n",
                                 sn, tsn), 2);
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
                                                                                                                                                                        
               case 3:
                  {
                     S16   tfms;
                     tfms = atoi(tokSub);
                     if (tfms == -1)
                        break;
                                                                                                                                                                        
                     if (fms != tfms)
                     {
                        CMXTA_DBG_CALLIND((_cmxtap, "FMS MisMatch: exp (%d) rcvd (%d) \n",
                                 fms, tfms), 2);
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
            }
         }
      }
                                                                                                                                                                        
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "vrfNoSec", &(vrfNoSec));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "vrfSec", &(vrfSec));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "vrfNoCiph", &(vrfNoCiph));
                                                                                                                                                                        
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "vrfCmp", &(vrfCmp));
                                                                                                                                                                        
      /* Validate pdcpBuf according to vrfCmp flags */
      /* Compression verification */
      if (vrfCmp)
      {
         Data data;
                                                                                                                                                                        
         /* Do not alter mBuf, Modify only opSdu */
         SRemPreMsg(&data, mBuf);
                                                                                                                                                                        
         if (data != PJ_ACC_COMP_BYTE)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Compression data MisMatch: exp (%d) rcvd (%d) \n",
                     data, PJ_ACC_COMP_BYTE), 2);
            RETVALUE(CMXTA_ERR_INT);
         }
      }
      if (vrfNoSec || vrfSec)
      {
         Data data = 0;
         U32 macI = 0;
                                                                                                                                                                        
                                                                                                                                                                        
         SRemPstMsgMult((Data *)&macI, (MsgLen) 4, mBuf);
         if((macI != 0) && !vrfSec)
         {
#ifndef ALIGN_64BIT
            CMXTA_DBG_CALLIND((_cmxtap, "MACI not zero MisMatch: exp (%d) rcvd (%ld) \n",
                     0, macI), 2);
#else
            CMXTA_DBG_CALLIND((_cmxtap, "MACI not zero MisMatch: exp (%d) rcvd (%d) \n",
                     0, macI), 2);
#endif
            RETVALUE(CMXTA_ERR_INT);
         }
                                                                                                                                                                        
         for(i = 0; i<300;i++)
         {
            SRemPstMsg(&data, mBuf);
            if(i%255 != data)
            {
               if(vrfSec) break;
               CMXTA_DBG_CALLIND((_cmxtap, "Ciphering data MisMatch: exp (%d) rcvd (%d) \n",
                        i, data), 2);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
         if(i > 300 && vrfSec)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Ciphering Not Done : exp (%d) rcvd (%d) \n",
                     i, data), 2);
            RETVALUE(CMXTA_ERR_INT);
         }
                                                                                                                                                                        
      }
      if (vrfNoCiph)
      {
         Data data = 0;
         U32 macI = 0;
                                                                                                                                                                        
         SRemPstMsgMult((Data *)&macI, (MsgLen) 4, mBuf);
                                                                                                                                                                        
         for(i = 0; i < 300; i++)
         {
            SRemPstMsg(&data, mBuf);
            if(i%255 != data)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Ciphering data MisMatch: exp (%d) rcvd (%d) \n",
                        i, data), 2);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
                                                                                                                                                                        
      }
      PJ_FREE_BUF(mBuf);
   }
   if(pass)
   {
   /* Copy the DatReq information to kwAcCb.pjKwuCb.datReq Q */
   ret = pjAcUtlKwuCpyDatReq(datReq,mBuf);
   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }
   }                                                                                                                                                                      
   RETVALUE(CMXTA_ERR_NONE);
}/* pjAcUtlValdtKwuDatReq */
                                                                                                                                                                        

/**
 * @brief Build Dedicated Channel Data Indication
 *
 * @details
 *
 *     Function : pjAcUtlBuildDatInd
 *
 *     This function fills KwuDatIndInfo structure and keeps copy in XTA before
 *     sending to PDCP.
 *
 *  @param[in]  *tcCb
 *  @param[in]  *spCb
 *  @param[in]  *datInd
 *  @param[in]  **mBuf
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 pjAcUtlBuildDatInd
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
KwuDatIndInfo     *datInd,
Buffer            **mBuf
)
#else
PUBLIC S16 pjAcUtlBuildDatInd(tcCb, spCb, datInd, mBuf)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
RguDDatIndInfo    *datInd;
Buffer            **mBuf;
#endif
{
   S16            ret;
   Txt            lchDataStr[512];
   Txt            *holdMain = NULLP, *tokMain = NULLP, *tok1 = NULLP;
   Txt            *holdSub, *tokSub = NULLP, *tok2 = NULLP;
   Txt            *holdNextSub, *tokNextSub, *tok3 = NULLP;
   U16            i = 0, j = 0, idx = 0, idx2 = 0;
   U32            transId = 0;
   U8             newR1Field = 0;
   U8             remflag = TRUE;
   PjAcKwuDatReq *datReq;
   S16            rbId = -1;
   S16            rbType = -1;
   Bool           corruptHdr  =  FALSE;
   Data           dst[2], temp;
   U8             pdcpSNSize = 0; 
   U8             statusPdu = 0;
   MsgLen         srcLen = 0; 
   Data tmpData[512];
   Data tmpStatusPdu[3] = {0x00, 0x00, 0x00};
                                                                                                                                                                        
   TRC2(kwAcUtlBuildDDatInd);
                                                                                                                                                                        
   ret = CMXTA_ERR_NONE;
                                                                                                                                                                        
   /* <tapa.kwu.datind cellId="1" ueId="1" 
    * lchData="indxSeq:crptTypeSeq:hdrCrpt"
    * lchData="0:0:0"
    *
    * saveDecmpMsg="FALSE"
    * saveIntVerMsg="FALSE"
    * saveDecpMsg="FALSE"
    *
    * />
    */
   memset(datInd,0,sizeof(*datInd));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(datInd->rlcId.cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(datInd->rlcId.ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(datInd->rlcId.rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(datInd->rlcId.rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "isOutOfSeq", &(datInd->isOutOfSeq));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &(transId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lchData", &(lchDataStr));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "remove", &(remflag));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "corruptHdr", &(corruptHdr));
   /* kw005.201 Added newR1Field to replace the existing R1 field with this new value */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "newR1Field", &(newR1Field));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pdcpSNSize", &pdcpSNSize);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "statusPdu", &statusPdu);
                                                                                                                                                                           
   /* rbId from XML */
                                                                                                                                                                        
   /* Verify pduSize with DStaInd sent previously in every Logical Channel */
   idx = pjAcUtlKwuDatReqCircQGetFront(&kwAcCb.pjKwuCb.datReq);
   datReq = &kwAcCb.pjKwuCb.datReq.node[idx];
   if (transId == 0)
   {
      transId = kwAcCb.pjKwuCb.nxtTransId;
   }


   do
   {
      if (kwAcCb.pjKwuCb.datReq.node[idx].isInQ  && (datReq->transId == transId) )
      {
         break;
      }
      idx = pjAcUtlKwuDatReqCircQGetNext(&kwAcCb.pjKwuCb.datReq, idx);
      datReq = &kwAcCb.pjKwuCb.datReq.node[idx];
   } while (idx);
                                                                                                                                                                        
   if (idx == 0)
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlRguDDatReqCircQGetNext: transId %ld not found.\n", transId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlRguDDatReqCircQGetNext: transId %d not found.\n", transId), 2);
#endif
      RETVALUE(CMXTA_ERR_INT);
   }
  holdMain = lchDataStr;
  {
         tokMain = (Txt *)strtok_r(holdMain, ";", &tok1);
                                                                                                                                                                        
         if (tokMain == NULLP)
         {
            RETVALUE(CMXTA_ERR_INT);
         }
                                                                                                                                                                        
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
         for (holdSub = tokMain, i = 0; i < 8; i++, holdSub=NULLP)
#else
         for (holdSub = tokMain, i = 0; i < 6; i++, holdSub=NULLP)
#endif
#else
         for (holdSub = tokMain, i = 0; i < 6; i++, holdSub=NULLP)
#endif
         {
            if ((tokSub=(Txt *)strtok_r(holdSub,":",&tok2)) == NULLP)
               break;
            switch(i)
            {
               case 0:
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub =(Txt*) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;
                                                                                                                                                                        
                        PJAC_CPY_MBUF(datReq->mBuf,*mBuf);
                     }
                     break;
                  }
               case 1:
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        S8 pduCrpt = 0;
                        Data dst1[100];
                                                                                                                                                                        
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;
                                                                                                                                                                        
                        CMXTA_ZERO(dst1, sizeof(dst1));
                        pduCrpt = atoi(tokNextSub);
                                                                                                                                                                       
                        /*  TODO, not verifying as of now */
                        pduCrpt = 0; 
                        switch (pduCrpt)
                        {
                           case 1:
                              {
                                 SRemPreMsgMult(dst1, 100, *mBuf);
                                 break;
                              }
                           case 2:
                              {
                                 SRemPstMsgMult(dst1, 100, *mBuf);
                                 break;
                              }
                           case 3:
                              {
                                 Data tmpDat[100];
                                 CMXTA_ZERO(tmpDat, sizeof(tmpDat));
                                 SRemPreMsgMult(dst1, 100, *mBuf);
                                 SRemPreMsgMult(tmpDat, 100, *mBuf);
                                 SAddPreMsgMult(dst1, 100, *mBuf);
                                 break;
                              }
                           case 4:
                              {
                                 Data tmpDat[100];
                                 CMXTA_ZERO(tmpDat, sizeof(tmpDat));
                                 SRemPreMsgMult(dst1, 100, *mBuf);
                                 SRemPreMsgMult(tmpDat, 100, *mBuf);
                                 dst1[99] &= 0xDF; /* Mask the extension bit of RLC header */
                                 SAddPreMsgMult(dst1, 100, *mBuf);
                                 break;
                              }
                                                                                                                                                                        
                        }
                     }
                     break;
                  }
               case 2:
                  {
                     S8 hdrCrpt = 0;
                     Data dst1[100];
                     CMXTA_ZERO(dst1, sizeof(dst1));
                     hdrCrpt = atoi(tokSub);
                     hdrCrpt = 0;                                                                                                                                                   
                     switch(hdrCrpt )
                     {
                        case 1:
                          {
                             Data dst2[2];
                             SRemPreMsg(dst2, *mBuf);
                             dst2[0] |= 0x70;
                             SAddPreMsg(dst2[0], *mBuf);
                             break;
                          }
                                                                                                                                                                        
                                                                                                                                                                        
                        /* Following 5 id's are UMM cases & are used for covering
                         * the errorneous  paths of function "kwUmmExtractHdr()"
                         * Note : corrupt header bytes are in reverse order is "tmpDat"
                         */
                        case 2:
                          {
                                                                                                                                                                        
                             /*                        1st Byte */
                             Data tmpDat[3]={0x00,0x80,0x26};
                             SRemPreMsgMult(dst1, 3, *mBuf);
                             SAddPreMsgMult(tmpDat,3, *mBuf);
                             break;
                          }
                        case 3:
                          {
                                                                                                                                                                        
                             /*                        1st Byte  */
                             Data tmpDat[3]={0xF0,0xFF,0x26};
                             SRemPreMsgMult(dst1, 3, *mBuf);
                             SAddPreMsgMult(tmpDat,3, *mBuf);
                             break;
                          }
                                                                                                                                                                        
                        case 4:
                          {
                                                                                                                                                                        
                             /*                             1st Byte   */
                             Data tmpDat[4]={0x00,0x08,0x81,0x26};
                             SRemPreMsgMult(dst1, 4, *mBuf);
                             SAddPreMsgMult(tmpDat,4, *mBuf);
                             break;
                          }
                                                                                                                                                                        
                        case 5:
                          {
                                                                                                                                                                        
                             /*                             1st Byte  */
                             Data tmpDat[4]={0xFF,0x0F,0x81,0x26};
                             SRemPreMsgMult(dst1, 4, *mBuf);
                             SAddPreMsgMult(tmpDat,4, *mBuf);
                             break;
                          }
                                                                                                                                                                        
                        case 6:
                          {
                             Data dst2[2];
                             SRemPreMsg(dst2, *mBuf);
                             dst2[0] |= 0x1F; /* Sequnce number invalid */
                             SAddPreMsg(dst2[0], *mBuf);
                             break;
                          }
                                                                                                                                                                        
                        case 7:
                          {
                             /*                Last Byte                                                                      1st Byte */
                             Data tmpDat[16]={  0x01,     0x18,0x80, 0x01,0x18,0x80, 0x01,0x18,0x80, 0x01,0x18,0x80, 0x01,0x18,0x80, 0x21 };
                             SRemPreMsgMult(dst1,16, *mBuf);
                             SAddPreMsgMult(tmpDat,16, *mBuf);
                             break;
                          }
                        /* Following  id's are AMM cases & are used for covering
                         * the errorneous  paths of function "kwUmmExtractHdr()"
                         * Note : corrupt header bytes are in reverse order is "tmpDat"
                         */
                        case 8:
                          {
                             /*              Last Byte               1st Byte */
                             Data tmpDat[4]={ 0x00,     0x80,  0x01 , 0x84 };
                             SRemPreMsgMult(dst1,4, *mBuf);
                             SAddPreMsgMult(tmpDat,4, *mBuf);
                             break;
                          }
                        case 9:
                          {
                             /*              Last Byte               1st Byte */
                             Data tmpDat[5]={ 0xFF,  0xF7,   0xFF,  0x01 , 0x84 };
                             SRemPreMsgMult(dst1,5, *mBuf);
                             SAddPreMsgMult(tmpDat,5, *mBuf);
                             break;
                          }
                        case 10:
                          {
                             /*              Last Byte                                                                                                        1st Byte */
                             Data tmpDat[20]={ 0x01, 0x18, 0x80, 0x01, 0x18, 0x80,0x01, 0x18, 0x80, 0x01, 0x18, 0x80,0x01, 0x18, 0x80,0x01, 0x18, 0x80, 0x01, 0x84 };
                             SRemPreMsgMult(dst1,20, *mBuf);
                             SAddPreMsgMult(tmpDat,20, *mBuf);
                             break;
                          }
                                                                                                                                                                        
                     }
                                                                                                                                                                        
                  }
               /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
               case 3:
                  {
                     lchData->timeInfo.thrpTimeUl = atoi(tokSub);
                     break;
                  }
               case 4:
                  {
                     lchData->timeInfo.firstLastSegInd = atoi(tokSub);
                     break;
                  }
#endif
#endif
            }
         }
    }
                                                                                                                                                                        
   if(corruptHdr)
   {
      Data hdrData[3];
      SRemPreMsgMult(hdrData, (MsgLen)3, *mBuf);
      hdrData[2] |= 0xE0;
      SAddPreMsgMult(hdrData, (MsgLen)3, *mBuf);
   }

   if(pdcpSNSize == 15)
   {
      if(statusPdu == 1)
      {
         /* Prepare Control PDU with PDU type Status Report for 15 bit SN */
         SFndLenMsg(*mBuf, &srcLen);
         /* Remove the data */
         SRemPreMsgMult(tmpData, srcLen, *mBuf);
         /* Copy the status PDU to the mBuf */
         SAddPreMsgMult(tmpStatusPdu, (MsgLen)3,*mBuf);
      }
   }
   
   /* Store tcCb and spCb to fetch Off-board attributes in
    * Off-board acceptance code kwac_libcb.c in UL
    */
   kwAcCb.tcCb = tcCb;
   kwAcCb.spCb = spCb;
                                                                                                                                                                        
   RETVALUE(CMXTA_ERR_NONE);
}/* pjAcUtlBuildDatInd */

/**
 * @brief Copy Configuration Request
 *
 * @details
 *
 *     Function : pjAcUtlKwuCpyDStaInd
 *
 *     This function copies CkwCfgInfo structure.
 *
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 pjAcUtlKwuCpyDatReq
(
KwuDatReqInfo   *datReq,
Buffer          *mBuf
)
#else
PUBLIC S16 pjAcUtlKwuCpyDatReq(datReq, mBuf )
KwuDatReqInfo   *datReq;
Buffer          *mBuf;
#endif
{
   PjAcKwuDatReq *tDatReq;
   U32 idx;
                                                                                                                                                                        
   TRC2(pjAcUtlKwuCpyDatReq);
                                                                                                                                                                        
   /* Get the next slot in Circular Q in kwAcCb.rguCb */
   tDatReq = &kwAcCb.pjKwuCb.datReq.node[idx=pjAcUtlKwuDatReqCircQEnqueue(&(kwAcCb.pjKwuCb.datReq))];
   /* As kwAcCb.rguCb.dDatReq is array and static,
    * We can use cmMemcpy to copy the structure
    */
   tDatReq->isInQ = TRUE;
   tDatReq->datReq = datReq;
   PJAC_CPY_MBUF(mBuf, tDatReq->mBuf);  
   tDatReq->transId = ++kwAcCb.pjKwuCb.nxtTransId;
   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcUtlKwuCpyDatReq */


/*************************************************************************
 *                KWU DAT CFM QUEUE PRIMITIVES END
 *************************************************************************/

/********************************************************************30**

         End of file:     pjac_kwuutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:53:09 2016

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
/main/1      ---      vb        1. LTE PDCP Initial release 2.1
*********************************************************************91*/

