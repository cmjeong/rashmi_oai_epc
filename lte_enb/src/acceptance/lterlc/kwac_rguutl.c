

/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for XTA Testing 
  
     File:     kwac_rguutl.c 
  
     Sid:      kwac_rguutl.c@@/main/TeNB_Main_BR/tenb_br_tdd_e1.2_4.0.0_cr/1 - Thu Nov 20 22:41:29 2014
  
     Prg:      sm
  
**********************************************************************/

/** @file rgac_rguutl.c
@brief This file contains the definitions for utility functions required 
by the handlers of XTA RGU interface
*/


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
#include "kwac_rgu.h"      /* RGU Acceptance defines */
#include "kwac_kwu.h"      /* KWU Acceptance defines */
#ifdef KW_PDCP
#include "kwac_lib.h"      /* RGU Acceptance defines */
#endif /* KW_PDCP */
#include <stdlib.h>
/* kw005.201 including missing header file */
#include <string.h>

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
#include "kwac_rgu.x"      /* RGU Acceptance defines */
#include "kwac_kwu.x"      /* KWU Acceptance defines */


/******************************************************************************
 *                         Extraction Utility Functions
 *****************************************************************************/
#ifdef ANSI
PUBLIC S16 kwAcUtlRguExtractUmHdr
(
Buffer   *mBuf,
KwUmHdr  *hdr,
U16      snType
)
#else
PUBLIC S16 kwAcUtlRguExtractUmHdr(mBuf,hdr,snType)
Buffer   *mBuf;
KwUmHdr  *hdr;
U16      snType;
#endif
{
   U8   e;
   Data *dst;
   Data li[2];
   U16 numLi;
   Buffer *buf;

   dst = li;
   e  = 0;
   numLi = 0;

   /* Copy buf to local mBuf Later local mBuf will be freed */
   KWAC_CPY_MBUF(mBuf, buf);

   if(snType  == 5)
   {
      SRemPreMsg(dst,buf);
      hdr->sn = (dst[0]) & 0x1F;
      e       = ((dst[0]) >> 5) & 0x01;
      hdr->fi = ((dst[0]) >> 6) & 0x03; 
   }
   else if(snType == 10)
   {
      U8 rsrv = 0;
      SRemPreMsgMult(dst,2,buf);

      rsrv = (dst[0] & 0xE0) >> 5;
      if (rsrv)
      {
         CMXTA_DBG_PARAM((_cmxtap, "Failed - Reserve bits are set in Header! \n"));
         RETVALUE(CMXTA_ERR_FATAL);
      }
      
      hdr->sn = ((dst[0]) & 0x3) << 8;
      hdr->sn |= dst[1];
      e       = (dst[0] & 0x04) >> 2;
      hdr->fi = (dst[0] & 0x18) >> 3;
   }
   while (e && (numLi < KW_MAX_LI))
   {
        SRemPreMsgMult(dst,2,buf);
        hdr->li[numLi] = (((U16)(dst[0] & 0x7F)) << 4);
        hdr->li[numLi] |= ((dst[1] & 0xF0) >> 4);
        numLi++;

        e    = ((dst[0]) >> 7) & 0x01;
       
        if(e && (numLi < KW_MAX_LI))
        {
           hdr->li[numLi] = ((dst[1] & 0x07) << 8);
           if(e)
           {
              e = (dst[1] & 0x08) >>3;
              SRemPreMsg(dst,buf);
              hdr->li[numLi] |= (dst[0]);
              numLi++;
           }
        }
   }

    hdr->numLi = numLi;

    KW_FREE_BUF(buf);
    RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlRguExtractUmHdr */


#ifdef ANSI
PUBLIC S16 kwAcUtlRguExtractAmHdr
(
Buffer  *mBuf,
KwAmHdr *hdr
)
#else
PUBLIC S16 kwAcUtlRguExtractAmHdr(mBuf,hdr)
Buffer    *mBuf;
KwAmHdr *hdr;
#endif
{
   U8   e;
   Data dst[2];
   U16 numLi;
   Buffer *buf;

   e  = 0;
   numLi = 0;

   /* Copy buf to local mBuf Later local mBuf will be freed */
   KWAC_CPY_MBUF(mBuf, buf);

   CMXTA_ZERO(hdr, sizeof(KwAmHdr));
   CMXTA_ZERO(dst, sizeof(dst));

   SRemPreMsgMult(dst,2,buf);
   hdr->dc = ((dst[0]) >> 7) & 0x01;
   hdr->rf = ((dst[0]) >> 6) & 0x01;
   hdr->p  = ((dst[0]) >> 5) & 0x01;
   hdr->fi = ((dst[0]) >> 3) & 0x03;
   e = hdr->e =  ((dst[0]) >> 2) & 0x01;
   hdr->sn = ((dst[0]) & 0x03) << 8;
   hdr->sn |= dst[1];
   hdr->lsf = 0;
   hdr->so = 0;

   if (hdr->rf)
   {
      SRemPreMsgMult(dst,2,buf);
      hdr->lsf = ((dst[0]) >>7) & 0x01;
      hdr->so = ((U16)(dst[0] & 0x7F)) << 8;
      hdr->so |= dst[1];

      while (e && (numLi < KW_MAX_LI))
      {
         SRemPreMsgMult(dst,2,buf);
         hdr->li[numLi] = ((dst[0] & 0x7F) << 4);
         hdr->li[numLi++] |= (dst[1] >> 4);
         e    = ((dst[0]) >> 7) & 0x01;

         if (e && (numLi < KW_MAX_LI))
         {
            hdr->li[numLi] = ((dst[1] & 0x07) << 8);
            e = (dst[1] & 0x08) >> 3;
            SRemPreMsg(dst,buf);
            hdr->li[numLi] |= dst[0];
            numLi++;
         }
      }
   }
   else
   {
      while (e && (numLi < KW_MAX_LI))
      {
         SRemPreMsgMult(dst,2,buf);
         hdr->li[numLi] = ((dst[0] & 0x7F) << 4);
         hdr->li[numLi++] |= (dst[1] >> 4);
         e    = ((dst[0]) >> 7) & 0x01;

         if (e && (numLi < KW_MAX_LI))
         {
            hdr->li[numLi] = ((dst[1] & 0x07) << 8);
            e = (dst[1] & 0x08) >> 3;
            SRemPreMsg(dst,buf);
            hdr->li[numLi] |= dst[0];
            numLi++;
         }
      }
   }
 
   hdr->numLi = numLi;

   KW_FREE_BUF(buf);
   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlRguExtractAmHdr */


#ifdef KW_PDCP
#ifdef ANSI
PUBLIC S16 kwAcUtlRguPdcpExtractAmHdr
(
Buffer  *mBuf,
Buffer  **resBuf
)
#else
PUBLIC S16 kwAcUtlRguPdcpExtractAmHdr(mBuf, resBuf)
Buffer    *mBuf;
Buffer  **resBuf;
#endif
{
   U8   e;
   Data dst[2];
   U16 numLi;
   Buffer *buf;
   KwAmHdr *hdr, tHdr;

   e  = 0;
   numLi = 0;
   hdr = &tHdr;

   /* Copy buf to local mBuf Later local mBuf will be freed */
   KWAC_CPY_MBUF(mBuf, buf);

   CMXTA_ZERO(&tHdr, sizeof(KwAmHdr));
   CMXTA_ZERO(dst, sizeof(dst));

   SRemPreMsgMult(dst,2,buf);
   hdr->dc = ((dst[0]) >> 7) & 0x01;
   hdr->rf = ((dst[0]) >> 6) & 0x01;
   hdr->p  = ((dst[0]) >> 5) & 0x01;
   hdr->fi = ((dst[0]) >> 3) & 0x03;
   e = hdr->e =  ((dst[0]) >> 2) & 0x01;
   hdr->sn = ((dst[0]) & 0x03) << 8;
   hdr->sn |= dst[1];
   hdr->lsf = 0;
   hdr->so = 0;

   if (hdr->rf)
   {
      SRemPreMsgMult(dst,2,buf);
      hdr->lsf = ((dst[0]) >>7) & 0x01;
      hdr->so = ((U16)(dst[0] & 0x7F)) << 8;
      hdr->so |= dst[1];

      while (e && (numLi < KW_MAX_LI))
      {
         SRemPreMsgMult(dst,2,buf);
         hdr->li[numLi] = ((dst[0] & 0x7F) << 4);
         hdr->li[numLi++] |= (dst[1] >> 4);
         e    = ((dst[0]) >> 7) & 0x01;

         if (e && (numLi < KW_MAX_LI))
         {
            hdr->li[numLi] = ((dst[1] & 0x07) << 8);
            e = (dst[1] & 0x08) >> 3;
            SRemPreMsg(dst,buf);
            hdr->li[numLi] |= dst[0];
            numLi++;
         }
      }
   }
   else
   {
      while (e && (numLi < KW_MAX_LI))
      {
         SRemPreMsgMult(dst,2,buf);
         hdr->li[numLi] = ((dst[0] & 0x7F) << 4);
         hdr->li[numLi++] |= (dst[1] >> 4);
         e    = ((dst[0]) >> 7) & 0x01;

         if (e && (numLi < KW_MAX_LI))
         {
            hdr->li[numLi] = ((dst[1] & 0x07) << 8);
            e = (dst[1] & 0x08) >> 3;
            SRemPreMsg(dst,buf);
            hdr->li[numLi] |= dst[0];
            numLi++;
         }
      }
   }
 
   hdr->numLi = numLi;

   KWAC_CPY_MBUF(buf, *resBuf);
   KW_FREE_BUF(buf);
   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlRguPdcpExtractAmHdr */

#ifdef ANSI
PUBLIC S16 kwAcUtlRguPdcpExtractUmHdr
(
Buffer   *mBuf,
Buffer   **pdcpBuf,
U16      snType
)
#else
PUBLIC S16 kwAcUtlRguPdcpExtractUmHdr(mBuf,pdcpBuf,snType)
Buffer   *mBuf;
Buffer   **pdcpBuf;
U16      snType;
#endif
{
   U8   e;
   Data *dst;
   Data li[2];
   U16 numLi;
   Buffer *buf;
   KwUmHdr  *hdr, tHdr;

   dst = li;
   e  = 0;
   numLi = 0;
   hdr = &tHdr;

   CMXTA_ZERO(&tHdr, sizeof(KwUmHdr));
   /* Copy buf to local mBuf Later local mBuf will be freed */
   KWAC_CPY_MBUF(mBuf, buf);

   if(snType  == 5)
   {
      SRemPreMsg(dst,buf);
      hdr->sn = (dst[0]) & 0x1F;
      e       = ((dst[0]) >> 5) & 0x01;
      hdr->fi = ((dst[0]) >> 6) & 0x03; 
   }
   else if(snType == 10)
   {
      U8 rsrv = 0;
      SRemPreMsgMult(dst,2,buf);

      rsrv = (dst[0] & 0xE0) >> 5;
      if (rsrv)
      {
         CMXTA_DBG_PARAM((_cmxtap, "Failed - Reserve bits are set in Header! \n"));
         RETVALUE(CMXTA_ERR_FATAL);
      }
      
      hdr->sn = ((dst[0]) & 0x3) << 8;
      hdr->sn |= dst[1];
      e       = (dst[0] & 0x04) >> 2;
      hdr->fi = (dst[0] & 0x18) >> 3;
   }
   while (e && (numLi < KW_MAX_LI))
   {
        SRemPreMsgMult(dst,2,buf);
        hdr->li[numLi] = (((U16)(dst[0] & 0x7F)) << 4);
        hdr->li[numLi] |= ((dst[1] & 0xF0) >> 4);
        numLi++;

        e    = ((dst[0]) >> 7) & 0x01;
       
        if(e && (numLi < KW_MAX_LI))
        {
           hdr->li[numLi] = ((dst[1] & 0x07) << 8);
           if(e)
           {
              e = (dst[1] & 0x08) >>3;
              SRemPreMsg(dst,buf);
              hdr->li[numLi] |= (dst[0]);
              numLi++;
           }
        }
   }

    hdr->numLi = numLi;

    KWAC_CPY_MBUF(buf, *pdcpBuf);
    KW_FREE_BUF(buf);
    RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlRguPdcpExtractUmHdr */
#endif /* KW_PDCP */



/******************************************************************************
 *                         Build Utility Functions
 *****************************************************************************/
/**
 * @brief Build Commom Channel Data Indication
 *
 * @details
 *
 *     Function : kwAcUtlBuildCDatInd
 *
 *     This function fills RguCDatIndInfo structure and keeps copy in XTA before
 *     sending to RLC.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *datInd
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlBuildCDatInd
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguCDatIndInfo    *datInd
)
#else
PUBLIC S16 kwAcUtlBuildCDatInd(tcCb, spCb, datInd)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
RguCDatIndInfo    *datInd;
#endif
{
   S16            ret;
   KwAcRguCDatReq *tmCDatReq = NULLP;
   KwAcLcInfo     *lc;
   CmLteRlcId     *tRlcId;
   U16            idx = 0, idx2 = 0;

   TRC2(kwAcUtlBuildCDatInd);

   ret = CMXTA_ERR_NONE;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &datInd->cellId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "rnti",  &datInd->rnti);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId",  &datInd->lcId);

   /* Get the RLC ID at the RLC (NH) */
   for(idx = 0; idx < kwAcCb.mapDlUlCb.count; idx++)
   {
      if ((kwAcCb.mapDlUlCb.mapDlUl[idx].ueId == 0) &&
          (kwAcCb.mapDlUlCb.mapDlUl[idx].cellId ==  datInd->cellId))
      {
         tRlcId = &(kwAcCb.mapDlUlCb.mapDlUl[idx].\
               lcCb[(datInd->lcId - 1)].othRlcId);
         lc = &(kwAcCb.mapDlUlCb.mapDlUl[idx].\
               lcCb[(datInd->lcId - 1)].dlLc);

         /* Get the PDU tmCDatReq information */
         idx2 = kwAcUtlRguCDatReqCircQGetFront(&kwAcCb.rguCb.cDatReq);
         do
         {
            tmCDatReq = &kwAcCb.rguCb.cDatReq.node[idx2];
            if (tmCDatReq && ((tRlcId->cellId == tmCDatReq->cDatReq->cellId) &&
                  (lc->lcId == tmCDatReq->cDatReq->lcId) &&
                  (lc->lcType == tmCDatReq->cDatReq->lcType)))
            {
               break;
            }
            idx2 = kwAcUtlRguCDatReqCircQGetNext(&kwAcCb.rguCb.cDatReq, idx2);
         } while (idx2);

         break;
      }
   }

   if (tmCDatReq)
   {
      if (SCpyMsgMsg(tmCDatReq->cDatReq->pdu, KWAC_KWU_DFLTRGN, KWAC_KWU_DFLTPOOL, &(datInd->pdu)) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "kwAcUtlCpyKwuDatReq(): resource unavailble \n"));
         RETVALUE(CMXTA_ERR_RSRC);
      }

      KW_FREE_BUF(tmCDatReq->cDatReq->pdu);
      KW_FREE_ACC(tmCDatReq->cDatReq, sizeof(RguCDatReqInfo));
      CMXTA_ZERO(tmCDatReq, sizeof(KwAcRguCDatReq));
      kwAcUtlRguCDatReqCircQDequeue(&kwAcCb.rguCb.cDatReq);
   }
   else
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlBuildCDatInd */


/**
 * @brief Build Dedicated Channel Data Indication
 *
 * @details
 *
 *     Function : kwAcUtlBuildDDatInd
 *
 *     This function fills RguDDatIndInfo structure and keeps copy in XTA before
 *     sending to RLC.
 *     
 *  @param[in]  *tcCb
 *  @param[in]  *spCb
 *  @param[in]  *datInd
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlBuildDDatInd
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguDDatIndInfo    *datInd
)
#else
PUBLIC S16 kwAcUtlBuildDDatInd(tcCb, spCb, datInd)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
RguDDatIndInfo    *datInd;
#endif
{
   S16            ret;
   Txt            lchDataStr[512];
   Txt            *holdMain = NULLP, *tokMain = NULLP, *tok1 = NULLP;
   Txt            *holdSub, *tokSub = NULLP, *tok2 = NULLP;
   Txt            *holdNextSub, *tokNextSub, *tok3 = NULLP;
   U16            tokCount = 0, i = 0, j = 0, idx = 0, idx2 = 0;
   U32            transId = 0;
   U8             numLch = 0;
   U8       		newR1Field = 0;
   U8             remflag = TRUE;
   RguLchDatInd   *lchData;
   KwAcRguDDatReq *datReq;
   S16            lcId = -1;
   Bool           corruptHdr  =  FALSE;
   Buffer	  *mBuffer;
   Data		  dst[2], temp;
   U8 index;
   RguDDatReqPerUe *dDatReqPerUe;

   TRC2(kwAcUtlBuildDDatInd);

   ret = CMXTA_ERR_NONE;

   /* <tapa.rgu.ddatind cellId="1" ueId="1" numLch="2"
    * lchData="lcId:numPdu:indxSeq:crptTypeSeq:hdrCrpt;
    *          lcId:numPdu:indxSeq:crptTypeSeq:hdrCrpt"
    * lchData="1:2:1,0:0:0:0;
    *          2:5:4,3,2,1,0:0:0"
    *
    * saveDecmpMsg="FALSE"
    * saveIntVerMsg="FALSE"
    * saveDecpMsg="FALSE"
    *
    * />
    */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(datInd->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(datInd->rnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &(transId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLch", &(datInd->numLch));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lchData", &(lchDataStr));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "remove", &(remflag));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "corruptHdr", &(corruptHdr));
   /* kw005.201 Added newR1Field to replace the existing R1 field with this new value */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "newR1Field", &(newR1Field));
#ifdef KW_PDCP
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "saveMsg", &(kwAcCb.nhCpjCb.saveMsg));
#endif

   /* lcId command level is used to overwrite lcId in lchData */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "lcId", &(lcId));

   /* Verify pduSize with DStaInd sent previously in every Logical Channel */
   idx = kwAcUtlRguDDatReqCircQGetFront(&kwAcCb.rguCb.dDatReq);
   datReq = &kwAcCb.rguCb.dDatReq.node[idx];

   do
   {
      if (kwAcCb.rguCb.dDatReq.node[idx].isInQ)
      {
         for(index = 0; index < datReq->dDatReq->nmbOfUeGrantPerTti; index++)
         {
            dDatReqPerUe = &datReq->dDatReq->datReq[index];
            if(dDatReqPerUe->transId == transId)
            {
               break;
            }
         }
         if(index !=  datReq->dDatReq->nmbOfUeGrantPerTti)
         {
            break;
         }
      }
      idx = kwAcUtlRguDDatReqCircQGetNext(&kwAcCb.rguCb.dDatReq, idx);
      datReq = &kwAcCb.rguCb.dDatReq.node[idx];
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

   numLch = datInd->numLch;

   /* kw005.201 Added this piece of code to tamper the R1 fields (3 bits) in UMD PDU*/
   if(0 != newR1Field)
   {
      for (j = 0; j < dDatReqPerUe->datReqTb[KWAC_NON_MIMO].nmbLch; j++)
      {
         for (idx2 = 0; idx2 < dDatReqPerUe->datReqTb[KWAC_NON_MIMO].lchData[j].pdu.numPdu; idx2++)
         {
            mBuffer = dDatReqPerUe->datReqTb[KWAC_NON_MIMO].lchData[j].pdu.mBuf[idx2];
            SRemPreMsgMult(dst, 2, mBuffer);
            dst[0] = (dst[0] & 0x1F) | (newR1Field << 5);
            temp = dst[0]; dst[0] = dst[1]; dst[1] = temp;
            SAddPreMsgMult(dst, 2, mBuffer);
         }
      }
   }

   if (numLch != 0)
   {
      tokCount = 0;

      for (holdMain = lchDataStr;;holdMain=NULLP)
      {
         lchData = &datInd->lchData[tokCount];
         /* kw005.201 removed compilation warnig */
         tokMain = (Txt *)strtok_r(holdMain, ";", &tok1);

         if (tokMain == NULLP) break;

         /* process each lcId data */
         /* kw005.201 added support for L2 Measurement */
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
                     if (lcId != -1)
                        lchData->lcId = (U8)lcId;
                     else
                        lchData->lcId = atoi(tokSub);   
                     break;
                  }
               case 1:
                  {
                     lchData->pdu.numPdu = atoi(tokSub);  
                     break;
                  }
               case 2:
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub =(Txt*) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        idx2 = atoi(tokNextSub);
                        if (idx2 < RGU_MAX_PDU)
                        {
                           lchData->pdu.mBuf[j] = dDatReqPerUe->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.mBuf[idx2];
                           dDatReqPerUe->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.mBuf[idx2] = NULLP;
                           /* Mark the PDU in the channel as send already
                            * After sending all PDUs delete DDatReq
                            */
                           datReq->isRem[tokCount][idx2] = 1;
                        }
                     }
                     break;
                  }
               case 3:
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

                        switch (pduCrpt)
                        {
                           case 1:
                              {
                                 SRemPreMsgMult(dst1, 100,
                                       lchData->pdu.mBuf[j]);
                                 break;
                              }
                           case 2:
                              {
                                 SRemPstMsgMult(dst1, 100,
                                       lchData->pdu.mBuf[j]);
                                 break;
                              }
                           case 3:
                              {
                                 Data tmpDat[100];
                                 CMXTA_ZERO(tmpDat, sizeof(tmpDat));
                                 SRemPreMsgMult(dst1, 100,
                                       lchData->pdu.mBuf[j]);
                                 SRemPreMsgMult(tmpDat, 100,
                                       lchData->pdu.mBuf[j]);
                                 SAddPreMsgMult(dst1, 100,
                                       lchData->pdu.mBuf[j]);
                                 break;
                              }
                           case 4:
                              {
                                 Data tmpDat[100];
                                 CMXTA_ZERO(tmpDat, sizeof(tmpDat));
                                 SRemPreMsgMult(dst1, 100,
                                       lchData->pdu.mBuf[j]);
                                 SRemPreMsgMult(tmpDat, 100,
                                       lchData->pdu.mBuf[j]);
                                 dst1[99] &= 0xDF; /* Mask the extension bit of RLC header */
                                 SAddPreMsgMult(dst1, 100,
                                       lchData->pdu.mBuf[j]);
                                 break;
                              }

                        }
                     }
                     break;
                  }
               case 4:
                  {
                     S8 hdrCrpt = 0;
                     Data dst1[100];
                     CMXTA_ZERO(dst1, sizeof(dst1));
                     hdrCrpt = atoi(tokSub);   

                     switch(hdrCrpt )
                     {
                        case 1: 
                          {
                             Data dst2[2];
                             SRemPreMsg(dst2, lchData->pdu.mBuf[0]);
                             dst2[0] |= 0x70;
                             SAddPreMsg(dst2[0], lchData->pdu.mBuf[0]);
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
                             SRemPreMsgMult(dst1, 3,
                                   lchData->pdu.mBuf[0]);
                             SAddPreMsgMult(tmpDat,3,
                                   lchData->pdu.mBuf[0]);
                             break;
                          } 
                        case 3:
                          {

                             /*                        1st Byte  */
                             Data tmpDat[3]={0xF0,0xFF,0x26};
                             SRemPreMsgMult(dst1, 3,
                                   lchData->pdu.mBuf[0]);
                             SAddPreMsgMult(tmpDat,3,
                                   lchData->pdu.mBuf[0]);
                             break;
                          } 

                        case 4:
                          {

                             /*                             1st Byte   */
                             Data tmpDat[4]={0x00,0x08,0x81,0x26};
                             SRemPreMsgMult(dst1, 4,
                                   lchData->pdu.mBuf[0]);
                             SAddPreMsgMult(tmpDat,4,
                                   lchData->pdu.mBuf[0]);
                             break;
                          } 

                        case 5:
                          {

                             /*                             1st Byte  */
                             Data tmpDat[4]={0xFF,0x0F,0x81,0x26};
                             SRemPreMsgMult(dst1, 4,
                                   lchData->pdu.mBuf[0]);
                             SAddPreMsgMult(tmpDat,4,
                                   lchData->pdu.mBuf[0]);
                             break;
                          } 
                        
                        case 6: 
                          {
                             Data dst2[2];
                             SRemPreMsg(dst2, lchData->pdu.mBuf[0]);
                             dst2[0] |= 0x1F; /* Sequnce number invalid */
                             SAddPreMsg(dst2[0], lchData->pdu.mBuf[0]);
                             break;
                          }
                        
                        case 7:
                          {
                             /*                Last Byte                                                                             1st Byte */
                             Data tmpDat[16]={  0x01,     0x18,0x80, 0x01,0x18,0x80, 0x01,0x18,0x80, 0x01,0x18,0x80, 0x01,0x18,0x80, 0x21 };
                             SRemPreMsgMult(dst1,16,
                                   lchData->pdu.mBuf[0]);
                             SAddPreMsgMult(tmpDat,16,
                                   lchData->pdu.mBuf[0]);
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
                             SRemPreMsgMult(dst1,4,
                                   lchData->pdu.mBuf[0]);
                             SAddPreMsgMult(tmpDat,4,
                                   lchData->pdu.mBuf[0]);
                             break;
                          } 
                        case 9:
                          {
                             /*              Last Byte               1st Byte */
                             Data tmpDat[5]={ 0xFF,  0xF7,   0xFF,  0x01 , 0x84 };
                             SRemPreMsgMult(dst1,5,
                                   lchData->pdu.mBuf[0]);
                             SAddPreMsgMult(tmpDat,5,
                                   lchData->pdu.mBuf[0]);
                             break;
                          } 
                        case 10:
                          {
                             /*              Last Byte                                                                                                        1st Byte */
                             Data tmpDat[20]={ 0x01, 0x18, 0x80, 0x01, 0x18, 0x80,0x01, 0x18, 0x80, 0x01, 0x18, 0x80,0x01, 0x18, 0x80,0x01, 0x18, 0x80, 0x01, 0x84 };
                             SRemPreMsgMult(dst1,20,
                                   lchData->pdu.mBuf[0]);
                             SAddPreMsgMult(tmpDat,20,
                                   lchData->pdu.mBuf[0]);
                             break;
                          } 
 
                     }

                  }
               /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
               case 5:
                  {
                     lchData->timeInfo.thrpTimeUl = atoi(tokSub);
                     break;
                  }
               case 6:
                  {
                     lchData->timeInfo.firstLastSegInd = atoi(tokSub);
                     break;
                  }
#endif
#endif
            }
         }

         if (remflag)
         {
            for (j = 0; j < dDatReqPerUe->datReqTb[KWAC_NON_MIMO].\
                  lchData[tokCount].pdu.numPdu; j++)
            {
               if (!(datReq->isRem[tokCount][j]))
                  break;
            }

            if (j == dDatReqPerUe->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.numPdu)
            {
               datReq->isLchRem[tokCount] = 1;
            }
         }

         tokCount++;
      }

      if (tokCount != numLch)
      {
         CMXTA_DBG_ERR((_cmxtap, "kwAcUtlBuildDDatInd():Insufficient LC data\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      if (remflag)
      {
         for (j = 0; j < dDatReqPerUe->datReqTb[KWAC_NON_MIMO].nmbLch; j++)
         {
            if (!(datReq->isLchRem[j]))
               break;
         }

         if (j == dDatReqPerUe->datReqTb[KWAC_NON_MIMO].nmbLch)
         {
            for (j = 0; j < dDatReqPerUe->datReqTb[KWAC_NON_MIMO].nmbLch; j++)
            {
               for (idx2 = 0; idx2 < dDatReqPerUe->datReqTb[KWAC_NON_MIMO].lchData[j].pdu.numPdu; idx2++)
               {
                  KW_FREE_BUF(dDatReqPerUe->datReqTb[KWAC_NON_MIMO].lchData[j].pdu.mBuf[idx2]);
               }
            }
            KW_FREE_ACC(datReq->dDatReq, sizeof(RguDDatReqInfo));
            CMXTA_ZERO(datReq, sizeof(KwAcRguDDatReq));
         }
      }
      kwAcUtlRguDDatReqCircQDequeue(&kwAcCb.rguCb.dDatReq);
   }

   if(corruptHdr)
   {
      Data hdrData[3];
      SRemPreMsgMult(hdrData, (MsgLen)3,datInd->lchData[0].pdu.mBuf[0]);
      hdrData[2] |= 0xE0;
      SAddPreMsgMult(hdrData, (MsgLen)3,datInd->lchData[0].pdu.mBuf[0]);
   }
   /* Store tcCb and spCb to fetch Off-board attributes in
    * Off-board acceptance code kwac_libcb.c in UL
    */
   kwAcCb.tcCb = tcCb;
   kwAcCb.spCb = spCb;

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlBuildDDatInd */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef ANSI
PRIVATE S16 kwAcUtlRguValdtSnMapInfo
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
RguSnMapInfo   *rguSnInfo
)
#else
PRIVATE S16 kwAcUtlRguValdtSnMapInfo(tcCb, spCb, rguSnInfo)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
RguSnMapInfo   *rguSnInfo;
#endif
{
   U32            tbId;
   U8             numLch, sn;
   RguLchMapInfo  *lchMap;
   Txt            lchDataStr[512];
   Txt            *holdMain = NULLP, *tokMain = NULLP, *tok1 = NULLP;
   Txt            *holdSub, *tokSub = NULLP, *tok2 = NULLP;
   U16            tokCount = 0, i = 0;
   CmLteLcId      lChId;

   TRC2(kwAcUtlRguValdtSnMapInfo);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "tbId",  &tbId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLch",  &numLch);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lchMap", &lchDataStr);

   /* Verify tbId */
   if (tbId != rguSnInfo->tbId)
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:tbId exp (%ld) rcvd (%ld)\n",
               tbId, rguSnInfo->tbId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:tbId exp (%d) rcvd (%d)\n",
               tbId, rguSnInfo->tbId), 2);
#endif
      RETVALUE(CMXTA_ERR_INT);
   }
   
   /* Verify numLch */
   if ((numLch != rguSnInfo->numLch ) ||  
       (rguSnInfo->numLch > RGU_MAX_LC))
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:numLch exp (%d) rcvd (%d)\n",
               numLch, rguSnInfo->numLch), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:numLch exp (%d) rcvd (%d)\n",
               numLch, rguSnInfo->numLch), 2);
#endif
      RETVALUE(CMXTA_ERR_INT);
   }
   
   /* Validate lchId and SN */
   tokCount = 0;
   for (holdMain = lchDataStr;;holdMain=NULLP)
   {
      lchMap = &rguSnInfo->lchMap[tokCount];
      tokMain = (Txt *)strtok_r(holdMain, ";", &tok1);
      if (tokMain == NULLP)
      {
         break;
      }
      /* process each lcId data */
      for (holdSub = tokMain, i = 0; i < 2; i++, holdSub=NULLP)
      {
          if ((tokSub=(Txt *) strtok_r(holdSub,":",&tok2)) == NULLP)
          {
             break;
          }
          switch(i)
          {
             case 0:
             {
                lChId = atoi(tokSub);
                if(lChId != lchMap->lChId)
                {
#ifndef ALIGN_64BIT
                   CMXTA_DBG_CALLIND((_cmxtap, \
                         "Failed - MisMatch:lChId  exp (%d) rcvd (%d)\n", \
                          lChId, lchMap->lChId), 2);
#else
                   CMXTA_DBG_CALLIND((_cmxtap, \
                          "Failed - MisMatch:tbId  exp (%ld) rcvd (%ld)\n", \
                          lChId, lchMap->lChId), 2);
#endif
                   RETVALUE(CMXTA_ERR_INT);
                }
                break;
             }
             case 1:
             {
                sn = atoi(tokSub);
                if(sn != lchMap->snList[0])
                {
#ifndef ALIGN_64BIT
                   CMXTA_DBG_CALLIND((_cmxtap,\
                         "Failed - MisMatch:sn  exp (%d) rcvd (%d)\n",\
                           sn, lchMap->snList[0]), 2);
#else
                   CMXTA_DBG_CALLIND((_cmxtap, \
                         "Failed - MisMatch:tbId exp (%d) rcvd (%d)\n",\
                           sn, lchMap->snList[0]), 2);
#endif
                   RETVALUE(CMXTA_ERR_INT);
                }
                break;
             }
          }
         tokCount++;
      }
   }
   RETVALUE(CMXTA_ERR_NONE);
}/* end of kwAcUtlRguValdtSnMapInfo */

/**
 * @brief Build Harq Status Indication
 *
 * @details
 *
 *     Function : kwAcUtlBuildRguHqStaInd
 *
 *     This function fills RguHarqstatusInd structure and keeps copy in XTA before
 *     sending to RLC.
 *     
 *  @param[in]  *tcCb
 *  @param[in]  *spCb
 *  @param[in]  *hqStaInd
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlBuildRguHqStaInd
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguHarqStatusInd  *hqStaInd
)
#else
PUBLIC S16 kwAcUtlBuildRguHqStaInd(tcCb, spCb, hqStaInd)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
RguHarqStatusInd  *hqStaInd;
#endif
{
   Txt            lchDataStr[512];
#if 0
   U8            tbIdx;
   Txt            *holdMain = NULLP, *tokMain = NULLP, *tok1 = NULLP;
   Txt            *holdNextSub = NULLP, *tokNextSub = NULLP, *tok3 = NULLP;
   Txt            *holdNextMoreSub = NULLP, *tokNextMoreSub = NULLP, *tok4 = NULLP;
   Txt            *holdSub, *tokSub = NULLP, *tok2 = NULLP;
   U8             i, j,k, snIdx;
#endif
   TRC2(kwAcUtlBuildRguHqStaInd);


   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(hqStaInd->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(hqStaInd->ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numTbs",  &(hqStaInd->numTbs));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,
         "status", &(hqStaInd->status), &hqStaInd->numTbs);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "snMapInfo", &(lchDataStr));
#if 0
   for(tbIdx = 0; tbIdx < hqStaInd->numTbs; tbIdx++)
   {
      KW_ALLOC_ACC(hqStaInd->rguSnMapInfo[tbIdx], sizeof(RguSnMapInfo));
      for (holdMain = lchDataStr;;holdMain=NULLP)
      {
         tokMain = (Txt *)strtok_r(holdMain, ";", &tok1);

         if (tokMain == NULLP) break;
         /* process each tbId data */
         for (holdSub = tokMain, i = 0; i < 3; i++, holdSub=NULLP)
         {
            if ((tokSub=(Txt *) strtok_r(holdSub,":",&tok2)) == NULLP)
               break;
            switch(i)
            {
               case 0:
                  {
                     hqStaInd->rguSnMapInfo[tbIdx]->tbId = atoi(tokSub);   
                     break;
                  }
               case 1:
                  {
                     hqStaInd->rguSnMapInfo[tbIdx]->numLch = atoi(tokSub);   
                     break;
                  }
               case 2:
                  {
                     for(holdNextSub = tokSub,  j = 0; j < hqStaInd->rguSnMapInfo[tbIdx]->numLch;
                           j++, holdNextSub=NULLP)
                     {
                        if((tokNextSub = (Txt *) strtok_r(holdNextSub, ".", &tok3)) == NULLP)
                        {
                           break;
                        }
                        for (holdNextMoreSub = tokNextSub, k = 0; k < 2;
                          k++, holdNextMoreSub=NULLP)
                        {
                           if ((tokNextMoreSub = (Txt *) strtok_r(holdNextMoreSub, ",", &tok4)) == NULLP)
                           {
                              break;
                           }
                           switch(k)
                           {
                              case 0:
                                 {
                                    hqStaInd->rguSnMapInfo[tbIdx]->lchMap[j].lChId = atoi(tokNextSub); 
                                    break;
                                 }
                              case 1:
                                 {
                                    for(snIdx = 0; snIdx < RGU_MAX_PDU; snIdx++)
                                    {
                                        hqStaInd->rguSnMapInfo[tbIdx]->lchMap[j].snList[snIdx] = 0xffff;
                                    }
                                    hqStaInd->rguSnMapInfo[tbIdx]->lchMap[j].snList[0] = atoi(tokNextMoreSub);
                                 }
                           }
                        }
                     }
                     break;
                  }
            }
         }
      }
   }
#endif
   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlBuildRguHqStaInd */

#ifdef LTE_RLC_R9
#ifdef ANSI
PUBLIC S16 kwAcUtlValdtL2MUlThrpMeasReq
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguL2MUlThrpMeasReqInfo *l2mUlThrpMeasReq
)
#else
PUBLIC S16 kwAcUtlValdtL2MUlThrpMeasReq(tcCb, spCb, l2mUlThrpMeasReq)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
RguL2MUlThrpMeasReqInfo *l2mUlThrpMeasReq
#endif
{
   CmLteCellId    cellId = 0;
   CmLteRnti      ueId = 0;
   U8             numLcId;
   U8             lcIdLst[RGU_MAX_LC];
   U8             enbMeas;
   Txt            lchDataStr[512];
   Txt            *tok1 = NULLP;
   U8             idx;
   Txt            *holdMain = NULLP, *tokMain = NULLP;

   TRC2(kwAcUtlValdtL2MUlThrpMeasReq);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &cellId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &ueId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLcId",  &numLcId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "enbMeas",  &enbMeas);

   /* Verify cellId, ueId */
   if (!((cellId == l2mUlThrpMeasReq->cellId) && (ueId == l2mUlThrpMeasReq->rnti)))
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:cellId exp (%d) rcvd (%d) \n\
               ueId exp(%d) rcvd(%d) \n",
               cellId, l2mUlThrpMeasReq->cellId, ueId, l2mUlThrpMeasReq->rnti), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:cellId exp (%d) rcvd (%d) \n\
               ueId exp(%d) rcvd(%d)\n",
               cellId, l2mUlThrpMeasReq->cellId, ueId, l2mUlThrpMeasReq->rnti), 2);
#endif
      RETVALUE(CMXTA_ERR_INT);
   }
   
   /* Verify number of lcId */
   if((numLcId != l2mUlThrpMeasReq->numLcId))
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:numLcId exp (%d) rcvd (%d) \n\
               \n", numLcId, l2mUlThrpMeasReq->numLcId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:numLcId exp (%d) rcvd (%d) \n\
               \n",numLcId, l2mUlThrpMeasReq->numLcId), 2);
#endif
      RETVALUE(CMXTA_ERR_INT);

   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lcIds", &(lchDataStr));

   if ((numLcId != 0))
   {
      /* process each lcId data */
      for(holdMain = lchDataStr, idx = 0; idx < RGU_MAX_LC; idx++, holdMain=NULLP)
      {
          tokMain = (Txt *) strtok_r(holdMain, ",", &tok1);
          if (tokMain == NULLP) 
          {
             break;
          }
          lcIdLst[idx] = atoi(tokMain);
          if(lcIdLst[idx] != l2mUlThrpMeasReq->lcId[idx])
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:lcId at idx (%d )exp (%d) rcvd (%d) \n\
                  \n", idx, lcIdLst[idx], l2mUlThrpMeasReq->lcId[idx]), 3);
#else
             CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:lcId at idx (%d) exp (%d) rcvd (%d) \n\
                  \n", idx, lcIdLst[idx], l2mUlThrpMeasReq->lcId[idx]), 3);
#endif
             RETVALUE(CMXTA_ERR_INT);

          }
      }
   } /* if ((numLcId != 0)) ends */
   
   if(enbMeas != l2mUlThrpMeasReq->enbMeas)
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:enbMeas exp (%d) rcvd (%d) \n\
               \n", enbMeas, l2mUlThrpMeasReq->enbMeas), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:enbMeas exp (%d) rcvd (%d) \n\
               \n",enbMeas, l2mUlThrpMeasReq->enbMeas), 2);
#endif
      RETVALUE(CMXTA_ERR_INT);
   }

   RETVALUE(CMXTA_ERR_NONE);
}
#endif
#endif

#ifdef KW_PDCP
/**
 * @brief Build Builds the RX RLC and PDCP PDUs
 *
 * @details
 *
 *     Function : kwAcUtlBuildRxPdcpPduCreate
 *
 *     This function creates and fills RguDDatReqInfo structure
 *     and keeps copy in XTA before sending to RLC.
 *     
 *  @param[in]  *tcCb
 *  @param[in]  *spCb
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlBuildRxPdcpPduCreate
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PUBLIC S16 kwAcUtlBuildRxPdcpPduCreate(tcCb, spCb)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16            ret;
   Txt            lchDataStr[512];
   Txt            *holdMain = NULLP, *tokMain = NULLP, *tok1 = NULLP;
   Txt            *holdSub = NULLP, *tokSub = NULLP, *tok2 = NULLP;
   Txt            *holdNextSub = NULLP, *tokNextSub = NULLP, *tok3 = NULLP;
   U16            tokCount = 0, i = 0, j = 0;
   U8             numLch = 0;
   U8             sData = 0x7F;
   RguLchDatReq   *lchData;
   RguDDatReqInfo *datReq = NULLP;
   U16            pduSzLst[KWAC_MAX_SIZE];
   U8             isSegFlag[KWAC_MAX_SIZE];
   U8             mode = 0;
   KwAmHdr        amHdr[KWAC_MAX_SIZE];
   KwUmHdr        umHdr[KWAC_MAX_SIZE];
   U8             pdcpPduType = 0;

   TRC2(kwAcUtlBuildRxPdcpPduCreate);

   ret = CMXTA_ERR_NONE;
   amHdr[0].dc = 1;
   amHdr[0].sn = 0;
   amHdr[0].rf = 0;
   amHdr[0].e = 0;

   CMXTA_ZERO(pduSzLst, sizeof(pduSzLst));
   CMXTA_ZERO(isSegFlag, sizeof(isSegFlag));
   CMXTA_ZERO(amHdr, KWAC_MAX_SIZE * sizeof(KwAmHdr));
   CMXTA_ZERO(umHdr, KWAC_MAX_SIZE * sizeof(KwUmHdr));

   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(datReq, sizeof(RguDDatReqInfo));
   if (datReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcUtlBuildRxPdcpPduCreate(): KW_ALLOC datReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* <tapa.dummy.rgu.rxPduCreate cellId="1" ueId="1" numLch="2"
    * lchData="mode:lcId:numPdu:pduSzLst:isSegFlag:pduHdrLst(SN:FI:P:DC:RF:LSF:SO:LI:LISZ'LISZ);
    *          mode:lcId:numPdu:pduSzLst:isSegFlag:pduHdrLst(SN:FI:P:DC:RF:LI)"
    * lchData="1:4:2051,2051,2051,20:1:
    *          SN(0,1,2,3):FI(1,3,3,2):P(-1):DC(-1):RF(-1):LSF(-1):SO(-1):LI(-1):LILEN"
    * pdcppdutype="1(OOS)/2(DropPDUs)/3(Duplicate)/4(Invalid)"
    * />
    */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(datReq->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(datReq->rnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &(datReq->transId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLch", &(datReq->datReqTb[KWAC_NON_MIMO].nmbLch));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lchData", &lchDataStr);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sData", &(sData));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pdcppdutype", &(pdcpPduType));

   numLch = datReq->datReqTb[KWAC_NON_MIMO].nmbLch;

   if (numLch == 0)
   {
      CMXTA_DBG_PARAM((_cmxtap, "kwAcUtlBuildRxPdcpPduCreate(), invalid numLch. \n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* AM RLC PDU Creation */
   {
      tokCount = 0;

      for (holdMain = lchDataStr;;holdMain=NULLP)
      {
         U16      idx = 0;
         U8       hdr[KW_MAX_HDRSZ];
         U8       data[KWAC_KWU_MAX_FLAT_BUF_SIZE];

         CMXTA_ZERO(hdr, sizeof(hdr));
         CMXTA_ZERO(data, sizeof(data));

         lchData = &datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount];
         tokMain = (Txt *) strtok_r(holdMain, ";", &tok1);

         if (tokMain == NULLP) break;

         /* process each lcId data */
         for (holdSub = tokMain, i = 0; i < 14; i++, holdSub=NULLP)
         {
            if ((tokSub=(Txt *) strtok_r(holdSub,":",&tok2)) == NULLP)
               break;

            switch(i)
            {
               case 0:        /* mode */
                  {
                     mode = atoi(tokSub);   
                     break;
                  }
               case 1:        /* lcId */
                  {
                     lchData->lcId = atoi(tokSub);   
                     break;
                  }
               case 2:        /* numPdu */
                  {
                     lchData->pdu.numPdu = atoi(tokSub);  
                     break;
                  }
               case 3:        /* PduSizes */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        pduSzLst[j] = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPdcpPduCreate(), pduSzLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 4:     /* isSegmented Flag */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        isSegFlag[j] = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPdcpPduCreate(), pduSzLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 5:        /* SN list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        if (mode == CM_LTE_MODE_AM)
                        {
                           amHdr[j].sn = atoi(tokNextSub);
                        }
                        else
                        {
                           umHdr[j].sn = atoi(tokNextSub);
                        }
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPdcpPduCreate(), snLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 6:        /* FI list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        if (mode == CM_LTE_MODE_AM)
                        {
                           amHdr[j].fi = atoi(tokNextSub);
                        }
                        else
                        {
                           umHdr[j].fi = atoi(tokNextSub);
                        }
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPdcpPduCreate(), fiLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 7:        /* P list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        amHdr[j].p = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPdcpPduCreate(), pollLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 8:        /* DC list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        amHdr[j].dc = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPdcpPduCreate(), dcLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 9:        /* RF list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        amHdr[j].rf = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPdcpPduCreate(), rfLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 10:        /* LSF list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        amHdr[j].lsf = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPdcpPduCreate(), lsfLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 11:        /* SO list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        amHdr[j].so = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPdcpPduCreate(), soLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 12:        /* LI list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        if (mode == CM_LTE_MODE_AM)
                        {
                           amHdr[j].numLi = atoi(tokNextSub);
                        }
                        else
                        {
                           umHdr[j].numLi = atoi(tokNextSub);
                        }
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPdcpPduCreate(), liLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 13:        /* LILEN list */
                  {
                     U8             k = 0;
                     Txt            *tmpTokNextSub = NULLP, *tok4 = NULLP;
                     Txt            *tmpHoldNextSub = NULLP;
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        for (tmpHoldNextSub = tokNextSub, k = 0;;
                              k++, tmpHoldNextSub=NULLP)
                        {
                           if ((tmpTokNextSub = (Txt *) strtok_r(tmpHoldNextSub, "'", &tok4)) == NULLP)
                              break;

                           if (mode == CM_LTE_MODE_AM)
                           {
                              amHdr[j].li[k] = atoi(tmpTokNextSub);
                           }
                           else
                           {
                              umHdr[j].li[k] = atoi(tmpTokNextSub);
                           }
                        }
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPdcpPduCreate(), liSzLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
            }
         }

         /* Construct PDUs for each logical Channels */
         if (mode == CM_LTE_MODE_AM)
         {
            for (j = 0; j < lchData->pdu.numPdu; j++)
            {
               idx = 0;

               /* Construct header with the available hdr Info */
               KW_CONSTRUCT_AM_HDR((amHdr[j]), isSegFlag[j], hdr);

               /* Allocate memory for SDU mBuf */
               if (SGetMsg(DFLT_REGION, DFLT_POOL, &lchData->pdu.mBuf[j]) != ROK)
               {
                  CMXTA_DBG_ERR((_cmxtap, "kwAcUtlBuildRxPdcpPduCreate(): resource unavailble \n"));
                  RETVALUE(CMXTA_ERR_RSRC);
               } /* end of if statement */

               /* Form RLC Data with different combinations of PDCP PDUs */
               /* PDCP PDU creation
                * This PDCP PDU is payload (data) for the RLC PDU
                */
               switch (pdcpPduType)
               {
                  case 1: /* Creation of PDCP PDU with Out of Sequence */
                     {
                        /* Data is packed in reverse */
                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 8, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 7, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 1, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 0, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 10, &lchData->pdu.mBuf[j]);

                     }
                     break;

                  case 2: /* Creation of PDCP PDU with missing */
                     {
                        /* Data is packed in reverse */
                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 6, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 5, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 4, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 2, &lchData->pdu.mBuf[j]);

                     }
                     break;

                  case 3: /* Creation of PDCP PDU with Duplicate */
                     {
                        /* Data is packed in reverse */
                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 16, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 16, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 15, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 15, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 14, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 14, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 12, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 12, &lchData->pdu.mBuf[j]);

                     }
                     break;

                  case 4: /* Creation of Invalid PDCP Control PDU */
                     {
                        KWAC_FORM_SDU(data, pduSzLst[j], sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 5, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, pduSzLst[j], sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_INV_HDR(data, 5, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, pduSzLst[j], sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 4, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, pduSzLst[j], sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 3, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, pduSzLst[j], sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_INV_HDR(data, 3, &lchData->pdu.mBuf[j]);


                        KWAC_FORM_SDU(data, pduSzLst[j], sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 2, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, pduSzLst[j], sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_INV_HDR(data, 2, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, pduSzLst[j], sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 1, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, pduSzLst[j], sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_INV_HDR(data, 3, &lchData->pdu.mBuf[j]);

                     }
                     break;

                  case 5: /* Creation of PDCP PDU with sn as specified */
                     {
                        U16 sn;
                        /* Data is packed in reverse */
                        cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "sn", &(sn));
                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, sn, &lchData->pdu.mBuf[j]);
                     }
                     break;
                  
                  case 6: /* Creation of PDCP AM Data PDU which are invalid */
                     {
                        KWAC_FORM_SDU(data, pduSzLst[j], sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_INV_DRB_HDR(data, 0, &lchData->pdu.mBuf[j]);
                     }
                     break;

                  case 7: /* Creation of PDCP AM Data PDU which are invalid */
                     {
                        KWAC_FORM_SDU(data, pduSzLst[j], sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_INV_SRB_HDR(data, 0, &lchData->pdu.mBuf[j]);
                     }
                     break;

                  case 8: /* Creation of PDCP PDU */
                     {
                        /* Data is packed in reverse */
                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 18, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 17, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 16, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 15, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 14, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 13, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 12, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 11, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 10, &lchData->pdu.mBuf[j]);
                     }
                     break;

                  case 9: /* Creation of PDCP PDU */
                     {
                        /* Data is packed in reverse */
                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 8, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 7, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 6, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 5, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 4, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 3, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 2, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 1, &lchData->pdu.mBuf[j]);

                        KWAC_FORM_SDU(data, 100, sData, &lchData->pdu.mBuf[j]);
                        KWAC_FORM_PDCP_AM_12BIT_HDR(data, 0, &lchData->pdu.mBuf[j]);
                     }
                     break;


                  default:
                     {
                        KW_FREE_ACC(datReq, sizeof(RguDDatReqInfo));
                        CMXTA_DBG_PARAM((_cmxtap, "kwAcUtlBuildRxPdcpPduCreate(), invalid pdcpPduType in DatReq\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
               }

               /* Concatenate hdr and data */
               SAddPreMsgMultInOrder(hdr, idx + 1, lchData->pdu.mBuf[j]);
            }
         }

         tokCount++;
      }

      if (tokCount != numLch)
      {
         CMXTA_DBG_ERR((_cmxtap, "kwAcUtlBuildRxPdcpPduCreate():Insufficient LC data\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   /* Copy the DDatReq information to kwAcCb.rguCb.dDatReq Q */
   ret = kwAcUtlRguCpyDDatReq(datReq);
   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlBuildRxPdcpPduCreate */
#else


/**
 * @brief Build Builds the RX SDUs
 *
 * @details
 *
 *     Function : kwAcUtlBuildRxSduCreate
 *
 *     This function creates and fills KwuDatReqInfo structure
 *     and keeps copy in XTA before sending to RLC. This function is applicable
 *     to PDCP only.
 *     
 *  @param[in]  *tcCb
 *  @param[in]  *spCb
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlBuildRxSduCreate
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PUBLIC S16 kwAcUtlBuildRxSduCreate(tcCb, spCb)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16            ret;
   U8             tmpLen = 0;
   U16            numSdu = 0;
   U16            cellId = 0, ueId = 0;
   U16            sduSzLst[KWAC_MAX_SIZE];
   U8             sData = 0x7F, rbId = 0;
   U8             data[KWAC_KWU_MAX_FLAT_BUF_SIZE];
   Buffer         *mBuf = NULLP;
   KwuDatReqInfo  *datReq = NULLP;
   U16            idx = 0;

   TRC2(kwAcUtlBuildRxSduCreate);

   ret = CMXTA_ERR_NONE;

   CMXTA_ZERO(sduSzLst, sizeof(sduSzLst));
   CMXTA_ZERO(data, sizeof(data));


   /* <tapa.dummy.rgu.rxSduCreate cellId="1" ueId="1" rbId="1" numPdu="3"
    * sduSzLst="2050:2051:2052"
    * />
    */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sData", &sData);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &cellId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &ueId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &rbId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSdu", &numSdu);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,
         "sduSzLst", sduSzLst, &tmpLen);

   /* Create SDUs at KWU interface in PDCP */
   for (idx = 0; idx < numSdu; idx++)
   {
      /* Allocate memory for cfgReq */
      KW_ALLOC_ACC(datReq, sizeof(KwuDatReqInfo));
      if (datReq == NULLP)
      {
         CMXTA_DBG_FATAL((_cmxtap, "kwAcUtlBuildRxSduCreate(): KW_ALLOC datReq Failed\n"));
         RETVALUE(CMXTA_ERR_INT);
      }

      datReq->rlcId.cellId = cellId;
      datReq->rlcId.ueId = ueId;
      datReq->rlcId.rbId = rbId;

      datReq->sduId = kwAcCb.pjKwuCb.nxtSduId;
      kwAcCb.pjKwuCb.nxtSduId++;

      /* Allocate memory for SDU mBuf */
      if (SGetMsg(DFLT_REGION, DFLT_POOL, &mBuf) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "kwAcUtlBuildRxSduCreate(): resource unavailble \n"));
         RETVALUE(CMXTA_ERR_RSRC);
      } /* end of if statement */

      KWAC_FORM_SDU(data, sduSzLst[idx], sData, &mBuf);

      /* Copy datReq to kwAcCb.nhKwuCb/pjKwuCb */
      if (kwAcUtlCpyKwuDatReq(datReq, mBuf, sduSzLst[idx], ENTPJ) != CMXTA_ERR_NONE)
      {
         RETVALUE(CMXTA_ERR_INT);
      }

      /* After make the copy of datReq and mBuf free datReq and mBuf */
      KW_FREE_BUF(mBuf);
      KW_FREE_ACC(datReq, sizeof(KwuDatReqInfo));
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlBuildRxSduCreate */


/**
 * @brief Build Builds the RX PDUs
 *
 * @details
 *
 *     Function : kwAcUtlBuildRxPduCreate
 *
 *     This function creates and fills RguDDatReqInfo structure
 *     and keeps copy in XTA before sending to RLC.
 *     
 *  @param[in]  *tcCb
 *  @param[in]  *spCb
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlBuildRxPduCreate
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PUBLIC S16 kwAcUtlBuildRxPduCreate(tcCb, spCb)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16            ret;
   Txt            lchDataStr[512];
   Txt            *holdMain = NULLP, *tokMain = NULLP, *tok1 = NULLP;
   Txt            *holdSub = NULLP, *tokSub = NULLP, *tok2 = NULLP;
   Txt            *holdNextSub = NULLP, *tokNextSub = NULLP, *tok3 = NULLP;
   U16            tokCount = 0, i = 0, j = 0;
   U8             numLch = 0;
   U8             sData = 0x7F;
   RguLchDatReq   *lchData;
   RguDDatReqInfo *datReq = NULLP;
   U16            pduSzLst[KWAC_MAX_SIZE];
   U8             isSegFlag[KWAC_MAX_SIZE];
   U8             mode = 0;
   KwAmHdr        amHdr[KWAC_MAX_SIZE];
   KwUmHdr        umHdr[KWAC_MAX_SIZE];
   U8             pduType = 0;
   U16            ueId = 0;
   U32            transId = 0;
   U8             nmbLch = 0;

   TRC2(kwAcUtlBuildRxPduCreate);

   ret = CMXTA_ERR_NONE;

   CMXTA_ZERO(pduSzLst, sizeof(pduSzLst));
   CMXTA_ZERO(isSegFlag, sizeof(isSegFlag));
   CMXTA_ZERO(amHdr, KWAC_MAX_SIZE * sizeof(KwAmHdr));
   CMXTA_ZERO(umHdr, KWAC_MAX_SIZE * sizeof(KwUmHdr));

   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(datReq, sizeof(RguDDatReqInfo));
   if (datReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcUtlBuildRxPduCreate(): KW_ALLOC datReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* <tapa.dummy.rgu.rxPduCreate cellId="1" ueId="1" numLch="2"
    * lchData="mode:lcId:numPdu:pduSzLst:isSegFlag:pduHdrLst(SN:FI:P:DC:RF:LSF:SO:LI:LISZ'LISZ);
    *          mode:lcId:numPdu:pduSzLst:isSegFlag:pduHdrLst(SN:FI:P:DC:RF:LI)"
    * lchData="1:4:2051,2051,2051,20:1:
    *          SN(0,1,2,3):FI(1,3,3,2):P(-1):DC(-1):RF(-1):LSF(-1):SO(-1):LI(-1):LILEN"
    * />
    */
   datReq->nmbOfUeGrantPerTti++;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(datReq->cellId));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &ueId);
   datReq->datReq[datReq->nmbOfUeGrantPerTti-1].rnti = ueId;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &transId);
   datReq->datReq[datReq->nmbOfUeGrantPerTti-1].transId = transId;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLch", &nmbLch);
   datReq->datReq[datReq->nmbOfUeGrantPerTti-1].datReqTb[KWAC_NON_MIMO].nmbLch = nmbLch;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lchData", &lchDataStr);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sData", &(sData));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pduType", &(pduType));

   numLch = datReq->datReq[datReq->nmbOfUeGrantPerTti-1].datReqTb[KWAC_NON_MIMO].nmbLch;

   if ((pduType != 2) && (numLch != 0))
   {
      tokCount = 0;

      for (holdMain = lchDataStr;;holdMain=NULLP)
      {
         U16      idx = 0;
         U8       hdr[KW_MAX_HDRSZ];
         U8       data[KWAC_KWU_MAX_FLAT_BUF_SIZE];

         CMXTA_ZERO(data, sizeof(data));

         lchData = &(datReq->datReq[datReq->nmbOfUeGrantPerTti-1].datReqTb[KWAC_NON_MIMO].lchData[tokCount]);
         tokMain = (Txt *) strtok_r(holdMain, ";", &tok1);

         if (tokMain == NULLP) break;

         /* process each lcId data */
         for (holdSub = tokMain, i = 0; i < 14; i++, holdSub=NULLP)
         {
            if ((tokSub=(Txt *) strtok_r(holdSub,":",&tok2)) == NULLP)
               break;

            switch(i)
            {
               case 0:        /* mode */
                  {
                     mode = atoi(tokSub);   
                     break;
                  }
               case 1:        /* lcId */
                  {
                     lchData->lcId = atoi(tokSub);   
                     break;
                  }
               case 2:        /* numPdu */
                  {
                     lchData->pdu.numPdu = atoi(tokSub);  
                     break;
                  }
               case 3:        /* PduSizes */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        pduSzLst[j] = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPduCreate(), pduSzLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 4:     /* isSegmented Flag */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        isSegFlag[j] = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPduCreate(), pduSzLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 5:        /* SN list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        if (mode == CM_LTE_MODE_AM)
                        {
                           amHdr[j].sn = atoi(tokNextSub);
                        }
                        else
                        {
                           umHdr[j].sn = atoi(tokNextSub);
                        }
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPduCreate(), snLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 6:        /* FI list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        if (mode == CM_LTE_MODE_AM)
                        {
                           amHdr[j].fi = atoi(tokNextSub);
                        }
                        else
                        {
                           umHdr[j].fi = atoi(tokNextSub);
                        }
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPduCreate(), fiLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 7:        /* P list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        amHdr[j].p = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPduCreate(), pollLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 8:        /* DC list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        amHdr[j].dc = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPduCreate(), dcLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 9:        /* RF list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        amHdr[j].rf = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPduCreate(), rfLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 10:        /* LSF list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        amHdr[j].lsf = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPduCreate(), lsfLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 11:        /* SO list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        amHdr[j].so = atoi(tokNextSub);
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPduCreate(), soLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 12:        /* LI list */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        if (mode == CM_LTE_MODE_AM)
                        {
                           amHdr[j].numLi = atoi(tokNextSub);
                        }
                        else
                        {
                           umHdr[j].numLi = atoi(tokNextSub);
                        }
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPduCreate(), liLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 13:        /* LILEN list */
                  {
                     U8             k = 0;
                     Txt            *tmpTokNextSub = NULLP, *tok4 = NULLP;
                     Txt            *tmpHoldNextSub = NULLP;
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        for (tmpHoldNextSub = tokNextSub, k = 0;;
                              k++, tmpHoldNextSub=NULLP)
                        {
                           if ((tmpTokNextSub = (Txt *) strtok_r(tmpHoldNextSub, "'", &tok4)) == NULLP)
                              break;

                           if (mode == CM_LTE_MODE_AM)
                           {
                              amHdr[j].li[k] = atoi(tmpTokNextSub);
                           }
                           else
                           {
                              umHdr[j].li[k] = atoi(tmpTokNextSub);
                           }
                        }
                     }

                     if (j != lchData->pdu.numPdu)
                     {
                        CMXTA_DBG_PARAM((_cmxtap,
                                 "kwAcUtlBuildRxPduCreate(), liSzLst is insufficient\n"));
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
            }
         }

         /* Construct PDUs for each logical Channels */
         if (mode == CM_LTE_MODE_AM)
         {
            for (j = 0; j < lchData->pdu.numPdu; j++)
            {
               idx = 0;

               /* Construct header with the available hdr Info */
               KW_CONSTRUCT_AM_HDR((amHdr[j]), isSegFlag[j], hdr);

               /* Allocate memory for SDU mBuf */
               if (SGetMsg(DFLT_REGION, DFLT_POOL, &lchData->pdu.mBuf[j]) != ROK)
               {
                  CMXTA_DBG_ERR((_cmxtap, "kwAcUtlBuildRxPduCreate(): resource unavailble \n"));
                  RETVALUE(CMXTA_ERR_RSRC);
               } /* end of if statement */

               KWAC_FORM_SDU(data, pduSzLst[j], sData, &lchData->pdu.mBuf[j]);

               /* Concatenate hdr and data */
               SAddPreMsgMultInOrder(hdr, idx + 1, lchData->pdu.mBuf[j]);
            }
         }
         else
         {
         }

         tokCount++;
      }

      if (tokCount != numLch)
      {
         CMXTA_DBG_ERR((_cmxtap, "kwAcUtlBuildRxPduCreate():Insufficient LC data\n"));
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else if (pduType == 2)
   {
      Data dat[2];
      /* Allocate memory for SDU mBuf */
      if (SGetMsg(DFLT_REGION, DFLT_POOL, &datReq->datReq[ueId].datReqTb[0].lchData[0].pdu.mBuf[0]) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "kwAcUtlBuildRxPduCreate(): resource unavailble \n"));
         RETVALUE(CMXTA_ERR_RSRC);
      } /* end of if statement */

      dat[0] = 0x00;
      dat[1] = 0x28;
      /* Concatenate hdr and data */
      datReq->datReq[ueId].datReqTb[0].lchData[0].pdu.numPdu = 1;
      SAddPreMsgMult(dat, 2, datReq->datReq[ueId].datReqTb[0].lchData[0].pdu.mBuf[0]);
   }
   else
   {
      KW_FREE_ACC(datReq, sizeof(RguDDatReqInfo))
      CMXTA_DBG_PARAM((_cmxtap, "kwAcUtlBuildRxPduCreate(), numLch is 0 in DatReq\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   
   /* Copy the DDatReq information to kwAcCb.rguCb.dDatReq Q */
   ret = kwAcUtlRguCpyDDatReq(datReq);
   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlBuildRxPduCreate */

#endif /* KW_PDCP */


/**
 * @brief Build Commom Channel Status Indication
 *
 * @details
 *
 *     Function : kwAcUtlBuildRguCStaInd
 *
 *     This function fills RguCStaIndInfo structure and keeps copy in XTA before
 *     sending to RLC.
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *staInd
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlBuildRguCStaInd
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguCStaIndInfo    *staInd
)
#else
PUBLIC S16 kwAcUtlBuildRguCStaInd(tcCb, spCb, staInd)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
RguCStaIndInfo    *staInd;
#endif
{
   TRC2(kwAcUtlBuildRguCStaInd);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(staInd->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId",  &(staInd->lcId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(staInd->transId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "rnti",  &(staInd->rnti));

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlBuildRguCStaInd */


/**
 * @brief Copy Configuration Request
 *
 * @details
 *
 *     Function : kwAcUtlRguCpyDStaInd
 *
 *     This function copies CkwCfgInfo structure.
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PRIVATE S16 kwAcUtlRguCpyDStaInd
(
RguDStaIndInfo   *staInd
)
#else
PRIVATE S16 kwAcUtlRguCpyDStaInd(staInd)
RguDStaIndInfo   *staInd;
#endif
{
   KwAcRguDStaInd *tStaInd;

   TRC2(kwAcUtlRguCpyDStaInd);

   /* Get the next slot in Circular Q in kwAcCb.ckwCb.cfgReq */
   tStaInd = &kwAcCb.rguCb.dStaInd.node[kwAcUtlRguDStaIndCircQEnqueue(&(kwAcCb.rguCb.dStaInd))];

   /* As kwAcCb.ckwCb.cfgReq is array and static,
    * We can use cmMemcpy to copy the structure
    */
   tStaInd->isInQ = TRUE;
   cmMemcpy((U8 *)&(tStaInd->dStaInd), (U8 *)staInd, sizeof(RguDStaIndInfo));

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlRguCpyDStaInd */


/**
 * @brief Build Dedicated Channel Data Indication
 *
 * @details
 *
 *     Function : kwAcUtlBuildRguDStaInd
 *
 *     This function fills RguDDatIndInfo structure and keeps copy in XTA before
 *     sending to RLC.
 *     
 *  @param[in]  *tcCb
 *  @param[in]  *spCb
 *  @param[in]  *staInd
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlBuildRguDStaInd
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguDStaIndInfo    *staIndInfo
)
#else
PUBLIC S16 kwAcUtlBuildRguDStaInd(tcCb, spCb, staInd)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
RguDStaIndInfo    *staIndInfo
#endif
{
   U16            idx;
   CmLteLcId      lcId[RGU_MAX_LC];
   U16            totBufSize[RGU_MAX_LC];
   S16            totBufSize0;
   U8             numLch = 0;
   RguDStaIndPerUe    *staInd = &staIndInfo->staInd[staIndInfo->nmbOfUeGrantPerTti-1];

   TRC2(kwAcUtlBuildRguDStaInd);

   staInd->fillCtrlPdu = 1;
   CMXTA_ZERO(lcId, sizeof(lcId));
   CMXTA_ZERO(totBufSize, sizeof(totBufSize));
   totBufSize0 = -1;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(staIndInfo->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(staInd->rnti));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &(staInd->transId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLch",  &(staInd->staIndTb[0].nmbLch));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId0",  &(staInd->staIndTb[0].lchStaInd[0].lcId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "totBufSize0",  &(totBufSize0));
   
   if ( totBufSize0 != -1 )
      totBufSize[0] = (U16) totBufSize0;
   
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
         "lcId", lcId, &numLch);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, CMXTA_SEP_COLON,
         "totBufSize", totBufSize, &numLch);
   staInd->nmbOfTbs = 1;

   for (idx = 0; idx < staInd->staIndTb[0].nmbLch; idx++)
   {
      staInd->staIndTb[0].lchStaInd[idx].lcId = lcId[idx];
      staInd->staIndTb[0].lchStaInd[idx].totBufSize = totBufSize[idx];
   }

   /* Copy cfgReq to kwAcCb.ckwCb.cfgReq */
   if (kwAcUtlRguCpyDStaInd(staIndInfo) != CMXTA_ERR_NONE)
      RETVALUE(CMXTA_ERR_INT);

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlBuildRguDStaInd */


/******************************************************************************
 *                         Validation Utility Functions
 *****************************************************************************/

/**
 * @brief Copy Configuration Request
 *
 * @details
 *
 *     Function : kwAcUtlKwuCpyDStaInd
 *
 *     This function copies CkwCfgInfo structure.
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PRIVATE S16 kwAcUtlRguCpyCDatReq
(
RguCDatReqInfo   *datReq
)
#else
PRIVATE S16 kwAcUtlRguCpyCDatReq(datReq)
RguCDatReqInfo   *datReq;
#endif
{
   KwAcRguCDatReq *tDatReq;

   TRC2(kwAcUtlRguCpyCDatReq);

   /* Get the next slot in Circular Q in kwAcCb.rguCb */
   tDatReq = &kwAcCb.rguCb.cDatReq.node[kwAcUtlRguCDatReqCircQEnqueue(&(kwAcCb.rguCb.cDatReq))];

   tDatReq->isInQ = TRUE;
   tDatReq->cDatReq = datReq;

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlRguCpyCDatReq */


/**
 * @brief Validate Common Channel Data Request
 *
 * @details
 *
 *     Function : kwAcUtlValdtCDatReq
 *
 *     This function Validates RguCDatReqInfo structure recieved from RLC
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *datReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlValdtCDatReq
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguCDatReqInfo    *datReq
)
#else
PUBLIC S16 kwAcUtlValdtCDatReq(tcCb, spCb, datReq)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
RguCDatReqInfo    *datReq;
#endif
{
   CmLteCellId    cellId;
   CmLteLcId      lcId;
   CmLteLcType    lcType;
   U32            transId;
   KwAcKwuDatReq  *tmDatReq;
   CmLteRlcId     rlcId;
   CmLteRlcId     *tRlcId;
   U16            idx, idx2;
   S32            sduId = -1;
   U8             rbId = 0;
   U8             rbType = 0;

   TRC2(kwAcUtlValdtCDatReq);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &cellId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId",  &lcId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcType",  &lcType);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &transId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "sduId",  &sduId);

   /* Verify cellId, lcId, lcType, and transId */
   if (!((cellId == datReq->cellId) && (lcId == datReq->lcId) &&
       (lcType == datReq->lcType)))
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:cellId exp (%d) rcvd (%d) \n\
               lcId exp(%d) rcvd(%d)\n lcType exp(%d) rcvd(%d)\n\
               transId rcvd(%ld)\n",
               cellId, datReq->cellId, lcId, datReq->lcId, lcType,
               datReq->lcType, datReq->transId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:cellId exp (%d) rcvd (%d) \n\
               lcId exp(%d) rcvd(%d)\n lcType exp(%d) rcvd(%d)\n\
               transId rcvd(%d)\n",
               cellId, datReq->cellId, lcId, datReq->lcId, lcType,
               datReq->lcType, datReq->transId), 2);
#endif
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Get the RLC ID at the RLC (NH) */
   for(idx = 0; idx < kwAcCb.mapDlUlCb.count; idx++)
   {
      if ((kwAcCb.mapDlUlCb.mapDlUl[idx].ueId == 0) &&
          (kwAcCb.mapDlUlCb.mapDlUl[idx].cellId ==  datReq->cellId))
      {
         rlcId.ueId = 0;
         rlcId.cellId = datReq->cellId;
         rlcId.rbId = kwAcCb.mapDlUlCb.mapDlUl[idx].lcCb[(lcId - 1)].rbId;
         rlcId.rbType = kwAcCb.mapDlUlCb.mapDlUl[idx].lcCb[(lcId - 1)].rbType;

         for (idx2 = 0; idx2 < kwAcCb.mapDlUlCb.count; idx2++)
         {
            if(kwAcCb.mapDlUlCb.mapDlUl[idx2].ueId == rlcId.ueId &&
                  kwAcCb.mapDlUlCb.mapDlUl[idx2].cellId ==  rlcId.cellId)
            {
               if (rlcId.rbType == CM_LTE_SRB)
               {
                  rbId = kwAcCb.mapDlUlCb.mapDlUl[idx2].\
                         srbCb[(rlcId.rbId)].rbId;
                  rbType = kwAcCb.mapDlUlCb.mapDlUl[idx2].\
                         srbCb[(rlcId.rbId)].rbType;
                  tRlcId = &(kwAcCb.mapDlUlCb.mapDlUl[idx2].\
                        srbCb[(rlcId.rbId)].othRlcId);   
               }
               else
               {
                  rbId = kwAcCb.mapDlUlCb.mapDlUl[idx2].\
                         drbCb[(rlcId.rbId)].rbId;
                  tRlcId = &(kwAcCb.mapDlUlCb.mapDlUl[idx2].\
                        drbCb[(rlcId.rbId)].othRlcId);   
               }
               break;
            }
         }
         break;
      }
   }

   /* Get the SDU datReq information */
   idx = kwAcUtlKwuDatReqCircQGetFront(&kwAcCb.nhKwuCb.datReq);
   do
   {
       tmDatReq = &kwAcCb.nhKwuCb.datReq.node[idx];
       if ((tmDatReq->datReq.rlcId.ueId == 0) &&
           (cellId == tmDatReq->datReq.rlcId.cellId) &&
           (rbId == tmDatReq->datReq.rlcId.rbId) &&
           (rbType == tmDatReq->datReq.rlcId.rbType))
       {
           if((sduId == -1) || (sduId == (S32)tmDatReq->datReq.sduId))
           break;
       }
       idx = kwAcUtlKwuDatReqCircQGetNext(&kwAcCb.nhKwuCb.datReq, idx);
   } while (idx);

   if (idx == 0)
   {
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlKwuDatReqCircQGetNext: ueId %d cellId %d rbId %d not found.\n",
               0, cellId, rbId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Validate PDU with SDU */
   kwAcUtlCmpKwuDatReqBuf(datReq->pdu, tmDatReq->mBuf, tmDatReq->sduSize);

   /* Copy CDatReq information to kwAcCb.rguCb */
   if (lcType == CM_LTE_LCH_CCCH)
   {
      kwAcUtlRguCpyCDatReq(datReq);
   }
   else
   {
      KW_FREE_BUF(datReq->pdu);
      KW_FREE_ACC(datReq, sizeof(RguCDatReqInfo));
      KW_FREE_BUF(tmDatReq->mBuf);
      CMXTA_ZERO(&kwAcCb.nhKwuCb.datReq.node[idx], sizeof(KwAcKwuDatReq));
      kwAcUtlKwuDatReqCircQDequeue(&kwAcCb.nhKwuCb.datReq);
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlValdtCDatReq */


/**
 * @brief Copy Configuration Request
 *
 * @details
 *
 *     Function : kwAcUtlKwuCpyDStaInd
 *
 *     This function copies CkwCfgInfo structure.
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlRguCpyDDatReq
(
RguDDatReqInfo   *datReq
)
#else
PUBLIC S16 kwAcUtlRguCpyDDatReq(datReq)
RguDDatReqInfo   *datReq;
#endif
{
   KwAcRguDDatReq *tDatReq;

   TRC2(kwAcUtlRguCpyDDatReq);

   /* Get the next slot in Circular Q in kwAcCb.rguCb */
   tDatReq = &kwAcCb.rguCb.dDatReq.node[kwAcUtlRguDDatReqCircQEnqueue(&(kwAcCb.rguCb.dDatReq))];

   /* As kwAcCb.rguCb.dDatReq is array and static,
    * We can use cmMemcpy to copy the structure
    */
   tDatReq->isInQ = TRUE;
   tDatReq->dDatReq = datReq;

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlRguCpyDDatReq */


/**
 * @brief Validate Dedicated Channel Data Request
 *
 * @details
 *
 *     Function : kwAcUtlValdtDDatReq
 *
 *     This function Validates RguDDatReqInfo structure recieved from RLC
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *datReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlValdtDDatReq
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguDDatReqInfo    *datReqInfo
)
#else
PUBLIC S16 kwAcUtlValdtDDatReq(tcCb, spCb, datReq)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
RguDDatReqInfo    *datReqInfo;
#endif
{
   CmLteCellId    cellId = 0;
   CmLteRnti      ueId = 0;
   U32            transId = 0;
   U16            idx = 0, idx2 = 0;
   KwAcRguDStaInd *staInd = NULLP;
   S16            ret;
   Txt            lchDataStr[512];
   Txt            *holdMain = NULLP, *tokMain = NULLP, *tok1 = NULLP;
   Txt            *holdSub = NULLP, *tokSub = NULLP, *tok2 = NULLP;
   Txt            *holdNextSub = NULLP, *tokNextSub = NULLP, *tok3 = NULLP;
   U16            tokCount = 0, i = 0, j = 0;
   RguLchDatReq   *lchData = NULLP;
   U8             numLch = 0;
   U8             valdType = 0;
   KwAcLcCb       *lcCb = NULLP;
   U8             mode = 3;
   S16            lcId = -1;
   S16            pdcpSn = -1;
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   Bool           snMapPres = FALSE;
#if 0
   RguSnMapInfo  *rguSnInfo = NULLP;
#endif
#endif /* LTE_L2_MEAS */

#ifdef KW_PDCP
   Bool           vrfPdcp = FALSE;
   U8             rlcsn = 5;
   Txt            pdcpHdrStr[512];
   Bool           vrfCmp = FALSE;
   Bool           vrfNoSec = FALSE;
   Bool           vrfSec = FALSE;
   Bool           vrfNoCiph = FALSE;
#endif /* KW_PDCP */
  RguDDatReqPerUe *datReq;
  U8               index;

   TRC2(kwAcUtlValdtDDatReq);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &cellId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &ueId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",  &transId);
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "snMapPres",  &snMapPres);
#endif
   for(idx = 0; idx < (datReqInfo->nmbOfUeGrantPerTti); idx++)
   {
      if(ueId == datReqInfo->datReq[idx].rnti)
      {
         datReq = &(datReqInfo->datReq[idx]);
         break;
      }
   }
   /* Verify cellId, ueId */
   if (!(cellId == datReqInfo->cellId) && (idx == (datReqInfo->nmbOfUeGrantPerTti)) &&
         (transId == datReq->transId))
   {
      for(idx = 0; idx < (datReqInfo->nmbOfUeGrantPerTti); idx++)
      {
         datReq = &(datReqInfo->datReq[idx]);
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:cellId exp (%d) rcvd (%d) \n\
                  ueId exp(%d) rcvd(%d) transId exp(%ld) rcvd(%ld)\n",
                  cellId, datReqInfo->cellId, ueId, datReq->rnti, transId,
                  datReq->transId), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed - MisMatch:cellId exp (%d) rcvd (%d) \n\
                  ueId exp(%d) rcvd(%d) transId exp(%d) rcvd(%d)\n",
                  cellId, datReqInfo->cellId, ueId, datReq->rnti, transId,
                  datReq->transId), 2);
#endif
      }
      RETVALUE(CMXTA_ERR_INT);
   }

   for (i = 0; i < kwAcCb.mapDlUlCb.count; i++)
   {
      if ((cellId == kwAcCb.mapDlUlCb.mapDlUl[i].cellId) &&
          (ueId == kwAcCb.mapDlUlCb.mapDlUl[i].ueId))
      {
         lcCb = kwAcCb.mapDlUlCb.mapDlUl[i].lcCb;
         break;
      }
   }

   /* Verify pduSize with DStaInd sent previously in every Logical Channel */
   idx2 = kwAcUtlRguDStaIndCircQGetFront(&kwAcCb.rguCb.dStaInd);
   staInd = &kwAcCb.rguCb.dStaInd.node[idx2];

   do
   {
      if (staInd->dStaInd.cellId == cellId)
      {
         for(index = 0; index < (staInd->dStaInd.nmbOfUeGrantPerTti); index++)
         {
            if((staInd->dStaInd.staInd[index].rnti == ueId) &&
               (staInd->dStaInd.staInd[index].transId == transId)) 
            {
               break;
            }
         }
         if(index != (staInd->dStaInd.nmbOfUeGrantPerTti))
         {
            break;
         }
      }
      idx2 = kwAcUtlRguDStaIndCircQGetNext(&kwAcCb.rguCb.dStaInd, idx2);
      staInd = &kwAcCb.rguCb.dStaInd.node[idx2];
   } while (idx2);

   if (idx2 == 0)
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlRguDStaIndCircQGetNext: ueId %d cellId %d transId %ld not found.\n",
               ueId, cellId, transId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap,\
               "kwAcUtlRguDStaIndCircQGetNext: ueId %d cellId %d transId %d not found.\n",
               ueId, cellId, transId), 2);
#endif
      RETVALUE(CMXTA_ERR_INT);
   }

   for (idx2 = 0; idx2 < datReq->datReqTb[KWAC_NON_MIMO].nmbLch; idx2++)
   {
      if (datReq->datReqTb[0].lchData[idx2].lcId == staInd->dStaInd.staInd[index].staIndTb[0].lchStaInd[idx2].lcId)
      {
         S32 bo = 0;

         for (idx = 0; idx < datReq->datReqTb[KWAC_NON_MIMO].lchData[idx2].pdu.numPdu; idx++)
         {
            MsgLen len = 0;
            SFndLenMsg(datReq->datReqTb[KWAC_NON_MIMO].lchData[idx2].pdu.mBuf[idx], &len);
            bo += len;
         }
         if (bo > staInd->dStaInd.staInd[index].staIndTb[KWAC_NON_MIMO].lchStaInd[idx2].totBufSize )
         {
            /* kw003.201 - Correction to the message printed */
#ifndef ALIGN_64BIT
            CMXTA_DBG_CALLIND((_cmxtap, "Data larger than grant for lcId: rcvd (%ld) exp (%d) lcId(%d)\n",
                  bo, staInd->dStaInd.staInd[index].staIndTb[KWAC_NON_MIMO].lchStaInd[idx2].totBufSize, datReq->datReqTb[0].lchData[idx2].lcId), 2);
#else
            CMXTA_DBG_CALLIND((_cmxtap, "Data larger than grant for lcId: exp (%d) rcvd (%d) lcId(%d)\n",
                  bo, staInd->dStaInd.staInd[index].staIndTb[KWAC_NON_MIMO].lchStaInd[idx2].totBufSize, datReq->datReqTb[0].lchData[idx2].lcId), 2);
#endif
            RETVALUE(CMXTA_ERR_INT);
         }
      }  
   }
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#if 0 /*PRERIT */
   if(snMapPres == TRUE)
   {
      rguSnInfo = datReq->datReqTb[KWAC_NON_MIMO].rguSnInfo;
      kwAcUtlRguValdtSnMapInfo(tcCb, spCb, rguSnInfo);
   }
#endif
#endif

   /* Call Header validation if requried */
   /* <tapa.rgu.ddatreq cellId="1" ueId="1" numLch="2" transId="1"
    *  lchData="bo:estRlcHdrSz:staPduPrsnt:lcId:numPdu:pduSzLst:pduHdrLst;
    *           bo:estRlcHdrSz:staPduPrsnt:lcId:numPdu:pduSzLst:pduHdrLst(SN:FI:P:D/C:RF:LI)"
    *  lchData="2050:4:1:1:3:2050,2051,2052:1,2,3:1,1,1:1,0,0:1,1,1:0,0,0"
    *  vrfPdcp="TRUE" snSize="7" mode="3" (2-UM, 3-AM in case of szSize=12)
    *  pdcpHdr="D/C:pduType:SN:FMS" intgProt="FALSE" ciph="FALSE"
    *  />
    */

   /* lcId is command level attribute to overwrite lcId in lchData */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "lcId", &(lcId));

   /* pdcpSn is command level attribute to overwrite SN in pdcpHdr */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "pdcpSn", &(pdcpSn));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numLch", &(numLch));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lchData", &(lchDataStr));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "valdType", &(valdType));

   if (numLch != datReq->datReqTb[KWAC_NON_MIMO].nmbLch)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "numLch MisMatch: exp (%d) rcvd (%d)\n",
               numLch, datReq->datReqTb[KWAC_NON_MIMO].nmbLch), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if ((valdType != 1) && (numLch != 0))
   {
      tokCount = 0;

      for (holdMain = lchDataStr;;holdMain=NULLP)
      {
         U8 lchId = 0;
         U8 snType = 5;
         mode = 2;
         lchData = &datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount];
         tokMain = (Txt *) strtok_r(holdMain, ";", &tok1);

         if (tokMain == NULLP) break;

         /* process each lcId data */
         for (holdSub = tokMain, i = 0; i < 12; i++, holdSub=NULLP)
         {
            if ((tokSub=(Txt *) strtok_r(holdSub,":",&tok2)) == NULLP)
               break;

            switch (valdType)
            {
               case KWAC_RGU_VALIDATE_LI:
                  {
                     if (i < 11)
                        continue;
                     break;
                  }
               case KWAC_RGU_VALIDATE_BO:
                  {
                     break;
                  }
            }

            switch(i)
            {
               case 0:  /* BO Validation */
                  {
                     S32 bo;
                     bo = atoi(tokSub);
                     if (bo == -1)
                        break;
                     if (datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].boReport.bo != bo)
                     {
#ifndef ALIGN_64BIT
                        CMXTA_DBG_CALLIND((_cmxtap, "bo MisMatch: exp (%ld) rcvd (%ld)\n",
                                 bo, datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].boReport.bo), 2);
#else
                        CMXTA_DBG_CALLIND((_cmxtap, "bo MisMatch: exp (%d) rcvd (%d)\n",
                                 bo, datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].boReport.bo), 2);
#endif
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 1:  /* Estimated RLC Header Size */
                  {
#ifdef CCPU_OPT 
                     S16 estRlcHdrSz = atoi(tokSub);
                     if (estRlcHdrSz == -1)
                        break;
                     if (datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].boReport.estRlcHdrSz != estRlcHdrSz)
                     {
                        CMXTA_DBG_CALLIND((_cmxtap, "estRlcHdrSz MisMatch: exp (%d) rcvd (%d)\n",
                                 estRlcHdrSz, datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].boReport.estRlcHdrSz), 2);
                        RETVALUE(CMXTA_ERR_INT);
                     }
#endif
                     break;
                  }
               case 2:  /* Status Pdu Present Validation */
                  {
#ifdef CCPU_OPT 
                     S8 staPduPrsnt = atoi(tokSub);
                     if (staPduPrsnt == -1)
                        break;
                     if (datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].boReport.staPduPrsnt != staPduPrsnt)
                     {
                        CMXTA_DBG_CALLIND((_cmxtap, "staPduPrsnt MisMatch: exp (%d) rcvd (%d)\n",
                                 staPduPrsnt, datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].boReport.staPduPrsnt), 2);
                        RETVALUE(CMXTA_ERR_INT);
                     }
#endif
                     break;
                  }
               case 3:  /* Lc Id Validation */
                  {
                     lchId = (U8)atoi(tokSub);
                     if (lcId != -1)
                     {
                        lchId = (U8)lcId;
                     }

                     if (datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].lcId != lchId)
                     {
                        CMXTA_DBG_CALLIND((_cmxtap, "lcId MisMatch: exp (%d) rcvd (%d)\n",
                                 lchId, datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].lcId), 2);
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     mode = lcCb[lchId - 1].mode;
                     snType = lcCb[lchId - 1].snType;
                     break;
                  }
               case 4:  /* Number of PDUs Validation */
                  {
                     S8 numPdu = atoi(tokSub);
                     if (numPdu == -1 )
                        break;
                     if (datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.numPdu != numPdu)
                     {
                        CMXTA_DBG_CALLIND((_cmxtap, "numPdu MisMatch: exp (%d) rcvd (%d)\n",
                                 numPdu, datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.numPdu), 2);
                        RETVALUE(CMXTA_ERR_INT);
                     }
                     break;
                  }
               case 5:  /* PDU sizes validation for numPdus */
                  {
                     if (datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.numPdu != 0)
                     {
                        for (holdNextSub = tokSub, j = 0;;
                             j++, holdNextSub=NULLP)
                        {
                           MsgLen len = 0;
                           S32 pduSz = 0;
                           if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                              break;

                           pduSz = atoi(tokNextSub);
                           if(pduSz == -1)
                              break;

                           SFndLenMsg(datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.mBuf[j], &len);
                           if (len != pduSz)
                           {
#ifndef ALIGN_64BIT
                              CMXTA_DBG_CALLIND((_cmxtap, "pduSz MisMatch: exp (%ld) rcvd (%d) idx(%d)\n",
                                    pduSz, len, j), 2);
#else
                              CMXTA_DBG_CALLIND((_cmxtap, "pduSz MisMatch: exp (%d) rcvd (%d) idx(%d)\n",
                                    pduSz, len, j), 2);
#endif
                              RETVALUE(CMXTA_ERR_INT);
                           }
                        }
                     }
                     break;
                  }
               case 6:  /* PDU Header SN Validation for numPdus */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        KwUmHdr   umHdr;
                        KwAmHdr   amHdr;
                        S32         expsn = 0, rcvdsn = 0;
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        expsn = atoi(tokNextSub);

                        /* if sn = -1 then skip this validation */
                        if (expsn == -1)  
                           continue;

                        if (mode == CM_LTE_MODE_UM)
                        {
                           ret = kwAcUtlRguExtractUmHdr(datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.mBuf[j],
                                 &umHdr, snType);
                           if (ret != CMXTA_ERR_NONE)
                           {
                              CMXTA_DBG_CALLIND((_cmxtap,
                                   "UM Header Extraction Failed: snType(%d) Pdu no: (%d)\n",
                                    snType, j), 2);
                              RETVALUE(ret);
                           }
                           rcvdsn = umHdr.sn;
                        }
                        else
                        {
                           ret = kwAcUtlRguExtractAmHdr(datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.mBuf[j],
                                 &amHdr);
                           if (ret != CMXTA_ERR_NONE)
                           {
                              CMXTA_DBG_CALLIND((_cmxtap,
                                   "AM Header Extraction Failed: Pdu no: (%d)\n", j), 2);
                              RETVALUE(ret);
                           }
                           rcvdsn = amHdr.sn;
                        }
                        if (expsn != rcvdsn)
                        {
#ifndef ALIGN_64BIT
                           CMXTA_DBG_CALLIND((_cmxtap, "SN MisMatch: exp (%ld) rcvd (%ld) Pdu no:(%d)\n",
                                    expsn, rcvdsn, j), 2);
#else
                           CMXTA_DBG_CALLIND((_cmxtap, "SN MisMatch: exp (%d) rcvd (%d) Pdu no:(%d)\n",
                                    expsn, rcvdsn, j), 2);
#endif
                           RETVALUE(CMXTA_ERR_INT);
                        }
                     }
                     break;
                  }
               case 7:  /* PDU Header FI Validation for numPdus */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        KwUmHdr   umHdr;
                        KwAmHdr   amHdr;
                        S16         expfi = 0, rvcdfi = 0;
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        expfi = atoi(tokNextSub);

                        /* if sn = -1 then skip this validation */
                        if (expfi == -1)  
                           break;

                        if (mode == CM_LTE_MODE_UM)
                        {
                           ret = kwAcUtlRguExtractUmHdr(datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.mBuf[j],
                                 &umHdr, snType);
                           if (ret != CMXTA_ERR_NONE)
                           {
                              CMXTA_DBG_CALLIND((_cmxtap,
                                   "UM Header Extraction Failed: snType(%d) Pdu no: (%d)\n",
                                    snType, j), 2);
                              RETVALUE(ret);
                           }
                           rvcdfi = umHdr.fi;
                        }
                        else
                        {
                           ret = kwAcUtlRguExtractAmHdr(datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.mBuf[j],
                                 &amHdr);
                           if (ret != CMXTA_ERR_NONE)
                           {
                              CMXTA_DBG_CALLIND((_cmxtap,
                                   "AM Header Extraction Failed: Pdu no: (%d)\n", j), 2);
                              RETVALUE(ret);
                           }
                           rvcdfi = amHdr.fi;
                        }
                        if (expfi != rvcdfi)
                        {
                           CMXTA_DBG_CALLIND((_cmxtap, "FI MisMatch: exp (%d) rcvd (%d) Pdu no:(%d)\n",
                                    expfi, rvcdfi, j), 2);
                           RETVALUE(CMXTA_ERR_INT);
                        }
                     }
                     break;
                  }
               case 8:  /* PDU Header POLL Bit Validation for numPdus */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        KwAmHdr   amHdr;
                        S16         expP = 0, rvcdP = 0;
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        expP = atoi(tokNextSub);

                        /* if sn = -1 then skip this validation */
                        if (expP == -1)  
                           break;

                        if (mode == CM_LTE_MODE_UM)
                        {
                           break;
                        }
                        else
                        {
                           ret = kwAcUtlRguExtractAmHdr(datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.mBuf[j],
                                 &amHdr);
                           if (ret != CMXTA_ERR_NONE)
                           {
                              CMXTA_DBG_CALLIND((_cmxtap,
                                   "AM Header Extraction Failed: Pdu no: (%d)\n", j), 2);
                              RETVALUE(ret);
                           }
                           rvcdP = amHdr.p;
                        }
                        if (expP != rvcdP)
                        {
                           CMXTA_DBG_CALLIND((_cmxtap, "P MisMatch: exp (%d) rcvd (%d) Pdu no:(%d)\n",
                                    expP, rvcdP, j), 2);
                           RETVALUE(CMXTA_ERR_INT);
                        }
                     }
                     break;
                  }
               case 9:  /* PDU Header D/C Bit Validation for numPdus */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        KwAmHdr   amHdr;
                        S16         expDC = 0, rvcdDC = 0;
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        expDC = atoi(tokNextSub);

                        /* if sn = -1 then skip this validation */
                        if (expDC == -1)  
                           break;

                        if (mode == CM_LTE_MODE_UM)
                        {
                           break;
                        }
                        else
                        {
                           ret = kwAcUtlRguExtractAmHdr(datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.mBuf[j],
                                 &amHdr);
                           if (ret != CMXTA_ERR_NONE)
                           {
                              CMXTA_DBG_CALLIND((_cmxtap,
                                   "AM Header Extraction Failed: Pdu no: (%d)\n", j), 2);
                              RETVALUE(ret);
                           }
                           rvcdDC = amHdr.dc;
                        }
                        if (expDC != rvcdDC)
                        {
                           CMXTA_DBG_CALLIND((_cmxtap, "DC MisMatch: exp (%d) rcvd (%d) Pdu no:(%d)\n",
                                    expDC, rvcdDC, j), 2);
                           RETVALUE(CMXTA_ERR_INT);
                        }
                     }
                     break;
                  }
               case 10:  /* PDU Header RF Bit Validation for numPdus */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        KwAmHdr   amHdr;
                        S16         expRF = 0, rvcdRF = 0;
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        expRF = atoi(tokNextSub);

                        /* if sn = -1 then skip this validation */
                        if (expRF == -1)  
                           break;

                        if (mode == CM_LTE_MODE_UM)
                        {
                           break;
                        }
                        else
                        {
                           ret = kwAcUtlRguExtractAmHdr(datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.mBuf[j],
                                 &amHdr);
                           if (ret != CMXTA_ERR_NONE)
                           {
                              CMXTA_DBG_CALLIND((_cmxtap,
                                   "AM Header Extraction Failed: Pdu no: (%d)\n", j), 2);
                              RETVALUE(ret);
                           }
                           rvcdRF = amHdr.rf;
                        }
                        if (expRF != rvcdRF)
                        {
                           CMXTA_DBG_CALLIND((_cmxtap, "RF MisMatch: exp (%d) rcvd (%d) Pdu no:(%d)\n",
                                    expRF, rvcdRF, j), 2);
                           RETVALUE(CMXTA_ERR_INT);
                        }
                     }
                     break;
                  }
               case 11:  /* PDU Header number of LIs Bit Validation for numPdus */
                  {
                     for (holdNextSub = tokSub, j = 0;;
                           j++, holdNextSub=NULLP)
                     {
                        KwUmHdr   umHdr;
                        KwAmHdr   amHdr;
                        S16         expLI = 0, rvcdLI = 0;
                        if ((tokNextSub = (Txt *) strtok_r(holdNextSub, ",", &tok3)) == NULLP)
                           break;

                        expLI = atoi(tokNextSub);

                        /* if sn = -1 then skip this validation */
                        if (expLI == -1)  
                           break;

                        if (mode == CM_LTE_MODE_UM)
                        {
                           ret = kwAcUtlRguExtractUmHdr(datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.mBuf[j],
                                 &umHdr, snType);
                           if (ret != CMXTA_ERR_NONE)
                           {
                              CMXTA_DBG_CALLIND((_cmxtap,
                                   "UM Header Extraction Failed: snType(%d) Pdu no: (%d)\n",
                                    snType, j), 2);
                              RETVALUE(ret);
                           }
                           rvcdLI = umHdr.numLi;
                        }
                        else
                        {
                           ret = kwAcUtlRguExtractAmHdr(datReq->datReqTb[KWAC_NON_MIMO].lchData[tokCount].pdu.mBuf[j],
                                 &amHdr);
                           if (ret != CMXTA_ERR_NONE)
                           {
                              CMXTA_DBG_CALLIND((_cmxtap,
                                   "AM Header Extraction Failed: Pdu no: (%d)\n", j), 2);
                              RETVALUE(ret);
                           }
                           rvcdLI = amHdr.numLi;
                        }
                        if (expLI != rvcdLI)
                        {
                           CMXTA_DBG_CALLIND((_cmxtap, "LI MisMatch: exp (%d) rcvd (%d) Pdu no:(%d)\n",
                                    expLI, rvcdLI, j), 2);
                           RETVALUE(CMXTA_ERR_INT);
                        }
                     }
                     break;
                  }
            }
         }

         tokCount++;
      }

      if (tokCount != numLch)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "numLch MisMatch: exp (%d) rcvd (%d)\n",
                numLch, tokCount), 2);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

#ifdef KW_PDCP
   /* Verify PDCP header if vrfPDCP is TRUE */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "vrfPdcp", &(vrfPdcp));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "vrfPdcp0", &(vrfPdcp));
   
   if ((vrfPdcp == TRUE) && (datReq->datReqTb[KWAC_NON_MIMO].lchData[0].pdu.numPdu == 1))
   {
      S8    snSize = 7;
      S16   sn = 0;
      S16   fms = 0;
      S8    dc = 0;
      S8    pduType = 0;
      Data  hdrByte[2];
      Buffer *pdcpBuf = NULLP;

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mode", &(mode));
      if (mode == 2)
      {
         rlcsn = 5;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "rlcsn", &(rlcsn));
         ret = kwAcUtlRguPdcpExtractUmHdr(datReq->datReqTb[KWAC_NON_MIMO].lchData[0].pdu.mBuf[0],
               &pdcpBuf, rlcsn);
         if (ret != CMXTA_ERR_NONE)
         {
            CMXTA_DBG_CALLIND((_cmxtap,
                     "RLC UM Header Extraction Failed: sn(%d) \n", rlcsn), 2);
            RETVALUE(ret);
         }
      }
      else if (mode == 3)
      {
         ret = kwAcUtlRguPdcpExtractAmHdr(datReq->datReqTb[KWAC_NON_MIMO].lchData[0].pdu.mBuf[0],
               &pdcpBuf);
         if (ret != CMXTA_ERR_NONE)
         {
            CMXTA_DBG_CALLIND((_cmxtap,
                     "RLC AM Header Extraction Failed: "), 2);
            RETVALUE(ret);
         }
      }
      /* Read SN size.
       * snSize = 5: means Control plane SRBs.
       * snSize = 7: means User plane UM DRBs.
       * snSize = 12: means User plane AM/UM DRBs.
       */
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "snSize", &(snSize));

      switch(snSize)
      {
         case 5:
            {
               mode = 3;
               ret = SRemPreMsgMult(hdrByte, 1, pdcpBuf);
               dc = -1;
               sn = hdrByte[0] & 0x1F;
               pduType = -1;
               fms = -1;
               break;
            }
         case 7:
            {
               mode = 2;
               ret = SRemPreMsgMult(hdrByte, 1, pdcpBuf);
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
               ret = SRemPreMsgMult(hdrByte, 2, pdcpBuf);
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
         SRemPreMsg(&data, pdcpBuf);

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


         SRemPstMsgMult((Data *)&macI, (MsgLen) 4, pdcpBuf);
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
            SRemPstMsg(&data, pdcpBuf);
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

         SRemPstMsgMult((Data *)&macI, (MsgLen) 4, pdcpBuf);

         for(i = 0; i<300;i++)
         {
            SRemPstMsg(&data, pdcpBuf);
            if(i%255 != data)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Ciphering data MisMatch: exp (%d) rcvd (%d) \n",
                        i, data), 2);
               RETVALUE(CMXTA_ERR_INT);
            }
         }

      }
      KW_FREE_BUF(pdcpBuf);
   }
#endif /* KW_PDCP */

   /* Copy the DDatReq information to kwAcCb.rguCb.dDatReq Q */
   ret = kwAcUtlRguCpyDDatReq(datReqInfo);
   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }

   /* Memset to 0 for DStaInd and dequeue from dStaInd Q */
   CMXTA_ZERO(staInd, sizeof(KwAcRguDStaInd))
   kwAcUtlRguDStaIndCircQDequeue(&kwAcCb.rguCb.dStaInd);

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlValdtDDatReq */


/**
 * @brief Validate Common Channel Status Response
 *
 * @details
 *
 *     Function : kwAcUtlValdtCStaRsp
 *
 *     This function Validates RguCStaRspInfo structure recieved from RLC
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *staRsp
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlValdtCStaRsp
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguCStaRspInfo    *staRsp
)
#else
PUBLIC S16 kwAcUtlValdtCStaRsp(tcCb, spCb, staRsp)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
RguCStaRspInfo    *staRsp;
#endif
{
   CmLteCellId    cellId;
   CmLteLcId      lcId;
   S32            bo;

   TRC2(kwAcUtlValdtCStaRsp);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId",  &(lcId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "bo",  &(bo));

   if (cellId != staRsp->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, staRsp->cellId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (lcId != staRsp->lcId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : lcId MisMatch: exp (%d) rcvd (%d) \n",
                  lcId, staRsp->lcId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (bo != staRsp->bo)
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap,
               "Failed : bo MisMatch: exp (%ld) rcvd (%ld) \n",
               bo, staRsp->bo), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap,
               "Failed : bo MisMatch: exp (%d) rcvd (%d) \n",
               bo, staRsp->bo), 2);
#endif
      RETVALUE(CMXTA_ERR_INT);
   }

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlValdtCStaRsp */


/**
 * @brief Validate Dedicated Channel Status Response
 *
 * @details
 *
 *     Function : kwAcUtlValdtDStaRsp
 *
 *     This function Validates RguDStaRspInfo structure recieved from RLC
 *     
 *  @param[in]  *tcCb 
 *  @param[in]  *spCb 
 *  @param[in]  *staRsp
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlValdtDStaRsp
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
RguDStaRspInfo    *staRsp
)
#else
PUBLIC S16 kwAcUtlValdtDStaRsp(tcCb, spCb, staRsp)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
RguDStaRspInfo    *staRsp;
#endif
{
   CmLteRnti      ueId;
   CmLteCellId    cellId;
   CmLteLcId      lcId;
   S32            bo;
   S16            estHdrSz;
   Bool           staPduPrsnt;
   U8             valdType;
   U8             opatStatus;

   TRC2(kwAcUtlValdtDStaRsp);

   ueId = 0;
   cellId = 0;
   estHdrSz = 0;
   staPduPrsnt = FALSE;
   valdType = 0;
   opatStatus = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId",  &(cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "lcId",  &(lcId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "bo",  &(bo));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "estHdrSz",  &(estHdrSz));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "staPduPrsnt",  &(staPduPrsnt));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "valdType",  &(valdType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "opatStatus",  &(opatStatus));

   if (valdType == KWAC_RGU_VALIDATE_SKIP)
   {
      RETVALUE(CMXTA_ERR_NONE);
   }
   
   if (cellId != staRsp->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, staRsp->cellId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != staRsp->rnti)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, staRsp->rnti), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (lcId != staRsp->lcId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : lcId MisMatch: exp (%d) rcvd (%d) \n",
                  lcId, staRsp->lcId), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if ((bo != staRsp->boReport.bo) && (bo != -1))
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap,
               "Failed : bo MisMatch: exp (%ld) rcvd (%ld) \n",
               bo, staRsp->boReport.bo), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap,
               "Failed : bo MisMatch: exp (%d) rcvd (%d) \n",
               bo, staRsp->boReport.bo), 2);
#endif
      RETVALUE(CMXTA_ERR_INT);
   }

#ifdef CCPU_OPT
   if (( estHdrSz != -1) && (estHdrSz != staRsp->boReport.estRlcHdrSz))
   {
      CMXTA_DBG_CALLIND((_cmxtap,
               "Failed : estRlcHdrSz MisMatch: exp (%d) rcvd (%d) \n",
               estHdrSz, staRsp->boReport.estRlcHdrSz), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   if ((staPduPrsnt != staRsp->boReport.staPduPrsnt) && (staPduPrsnt != 255))
   {
      CMXTA_DBG_CALLIND((_cmxtap,
               "Failed : staPduPrsnt MisMatch: exp (%d) rcvd (%d) \n",
               staPduPrsnt, staRsp->boReport.staPduPrsnt), 2);
      RETVALUE(CMXTA_ERR_INT);
   }
#endif

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcUtlValdtDStaRsp */

/******************************************************************************
 *                         Free Utility Functions
 *****************************************************************************/

/**
 * @brief XTA Function to free resources aquired by the interface messages
 * received from Dummy-MAC to RLC.
 *
 * @details
 *
 *     Function : kwAcUtlFreeRguCb
 *     
 *     A pointer to this function is registered with each 
 *     Queue element that gets enqueued as part of its call
 *     handler functionality. After the interface primitive 
 *     validation is done by the validation handler, the queue
 *     element is flushed, this function gets invoked as part
 *     of this flushing. Based on type of primitive, the memory
 *     freeing takes place.
 *     
 *  @param[in]  *qElm 
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_INT
 **/
#ifdef ANSI
PUBLIC S16 kwAcUtlFreeRguCb
(
CmXtaMsgQElm   *qElm
)
#else
PUBLIC S16 kwAcUtlFreeRguCb(qElm)
CmXtaMsgQElm   *qElm;
#endif /* ANSI */
{
   KwAcMsgQElm *kwElm;
   KwAcRguInfo  *rguInfo = NULLP; 
 
   TRC2(kwAcUtlFreeRguCb);
 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcUtlFreeRguCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   kwElm = (KwAcMsgQElm *)qElm->data;
  
   if(kwElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   rguInfo = &(kwElm->u.rguInfo);
   
   switch (qElm->pst.event)
   {
      case KWAC_RGU_EVT_BND_REQ:
      case KWAC_RGU_EVT_UBND_REQ:
         break;
      case KWAC_RGU_EVT_CDAT_REQ:
         break;
      case KWAC_RGU_EVT_DDAT_REQ:
         break;
      case KWAC_RGU_EVT_CSTA_RSP:
         KW_FREE_ACC(rguInfo->u.cStaRsp, sizeof(RguCStaRspInfo));
         break;
      case KWAC_RGU_EVT_DSTA_RSP:
         KW_FREE_ACC(rguInfo->u.dStaRsp, sizeof(RguDStaRspInfo));
         break;
      /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
      case KWAC_RGU_EVT_L2MULTHR_REQ:
         KW_FREE_ACC(rguInfo->u.l2mUlThrpMeasReq, sizeof(RguL2MUlThrpMeasReqInfo));
         break;
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS */
      default : 
         CMXTA_DBG_CALLIND((_cmxtap, "Failed - kwAcUtlFreeRguCb: event(%d) is wrong\n",
                  qElm->pst.event), 2);
         RETVALUE(CMXTA_ERR_INT);
   }
   if (kwElm != NULLP)
   {
      if(kwElm->mBuf != NULLP)
         CMXTA_FREEMBUF(kwElm->mBuf);

      CMXTA_FREE(kwElm, sizeof (KwAcMsgQElm));
      qElm->data = NULLP;
   }
 
   RETVALUE(CMXTA_ERR_NONE);
} /* End of kwAcUtlFreeRguCb() */

  
/**
 * @brief Circular Queue for RGU CData Reqeust Interface
 *
 * @details
 *
 *     Function : kwAcUtlRguCDatReqCQMakeNull
 *
 *     This function Initializes theRGU CData Reqeust Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void kwAcUtlRguCDatReqCQMakeNull
(
KwAcRguCDatReqQ   *queue
)
#else
PUBLIC Void kwAcUtlRguCDatReqCQMakeNull(queue)
KwAcRguCDatReqQ   *queue;
#endif
{
   queue->front = 1;
   queue->rear = KWAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* kwAcUtlRguCDatReqCQMakeNull */

#ifdef ANSI
PUBLIC U16 kwAcUtlRguCDatReqCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 kwAcUtlRguCDatReqCircQAddOne(idx)
U16 idx;
#endif
{
   /* kw005.201 Changes for R9 RLC test cases */
   /* 0x3FF below is KWAC_MAX_CIRCQ_SIZE(currently 1024) - 1 */
   if (idx == 0x3FF)
      RETVALUE(1);
   else
      RETVALUE((idx + 1) & 0x3FF);
} /* kwAcUtlRguCDatReqCircQAddOne */

#ifdef ANSI
PUBLIC S16 kwAcUtlRguCDatReqCircQEnqueue
(
KwAcRguCDatReqQ *queue
)
#else
PUBLIC S16 kwAcUtlRguCDatReqCircQEnqueue(queue)
KwAcRguCDatReqQ *queue;
#endif
{
   if(kwAcUtlRguCDatReqCircQAddOne(kwAcUtlRguCDatReqCircQAddOne(
               kwAcUtlRguCDatReqCircQAddOne(queue->rear))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguCDatReqCircQEnqueue(): RGU CDatReq Queue is full\n"));
      RETVALUE(0);
   }

   queue->rear = kwAcUtlRguCDatReqCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* kwAcUtlRguCDatReqCircQEnqueue */

#ifdef ANSI
PUBLIC U16 kwAcUtlRguCDatReqCircQGetFront
(
KwAcRguCDatReqQ *queue
)
#else
PUBLIC U16 kwAcUtlRguCDatReqCircQGetFront(queue)
KwAcRguCDatReqQ *queue;
#endif
{
   if(KWAC_UTL_RGU_CDATREQ_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguCDatReqCircQGetFront(): RGU CDatReq Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* kwAcUtlRguCDatReqCircQGetFront */

#ifdef ANSI
PUBLIC S16 kwAcUtlRguCDatReqCircQGetNext
(
KwAcRguCDatReqQ   *queue,
U16            idx
)
#else
PUBLIC S16 kwAcUtlRguCDatReqCircQGetNext(queue, idx)
KwAcRguCDatReqQ   *queue;
U16            idx;
#endif
{
   if ((idx >= queue->rear) && ((queue->front == queue->rear) ||
         (kwAcUtlRguCDatReqCircQAddOne(idx) == queue->front)))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguCDatReqCircQGetNext(): RGU CDatReq Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(kwAcUtlRguCDatReqCircQAddOne(queue->front));
} /* kwAcUtlRguCDatReqCircQGetNext */

#ifdef ANSI
PUBLIC Void kwAcUtlRguCDatReqCircQDequeue
(
KwAcRguCDatReqQ *queue
)
#else
PUBLIC Void kwAcUtlRguCDatReqCircQDequeue(queue)
KwAcRguCDatReqQ *queue;
#endif
{
   if(KWAC_UTL_RGU_CDATREQ_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguCDatReqCircQDequeue(): RGU CDatReq Queue is empty\n"));
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = kwAcUtlRguCDatReqCircQAddOne(queue->front);
      if(KWAC_UTL_RGU_CDATREQ_CQ_ISEMPTY(queue))
         break;
   }
   RETVOID;
} /* kwAcUtlRguCDatReqCircQDequeue */

  
/**
 * @brief Circular Queue for RGU DData Reqeust Interface
 *
 * @details
 *
 *     Function : kwAcUtlRguDDatReqCQMakeNull
 *
 *     This function Initializes the RGU DData Reqeust Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void kwAcUtlRguDDatReqCQMakeNull
(
KwAcRguDDatReqQ   *queue
)
#else
PUBLIC Void kwAcUtlRguDDatReqCQMakeNull(queue)
KwAcRguDDatReqQ   *queue;
#endif
{
   queue->front = 1;
   queue->rear = KWAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* kwAcUtlRguDDatReqCQMakeNull */

#ifdef ANSI
PUBLIC U16 kwAcUtlRguDDatReqCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 kwAcUtlRguDDatReqCircQAddOne(idx)
U16 idx;
#endif
{
   /* kw005.201 Changes for R9 RLC test cases */
   /* 0x3FF below is KWAC_MAX_CIRCQ_SIZE(currently 1024) - 1 */
   if (idx == 0x3FF)
      RETVALUE(1);
   else
      RETVALUE((idx + 1) & 0x3FF);
} /* kwAcUtlRguDDatReqCircQAddOne */

#ifdef ANSI
PUBLIC S16 kwAcUtlRguDDatReqCircQEnqueue
(
KwAcRguDDatReqQ *queue
)
#else
PUBLIC S16 kwAcUtlRguDDatReqCircQEnqueue(queue)
KwAcRguDDatReqQ *queue;
#endif
{
   if(kwAcUtlRguDDatReqCircQAddOne(kwAcUtlRguDDatReqCircQAddOne(\
               kwAcUtlRguDDatReqCircQAddOne(kwAcUtlRguDDatReqCircQAddOne(\
                     queue->rear)))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguDDatReqCircQEnqueue(): RGU DDatReq Queue is full\n"));
      RETVALUE(0);
   }

   queue->rear = kwAcUtlRguDDatReqCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* kwAcUtlRguDDatReqCircQEnqueue */

#ifdef ANSI
PUBLIC U16 kwAcUtlRguDDatReqCircQGetFront
(
KwAcRguDDatReqQ *queue
)
#else
PUBLIC U16 kwAcUtlRguDDatReqCircQGetFront(queue)
KwAcRguDDatReqQ *queue;
#endif
{
   if(KWAC_UTL_RGU_DDATREQ_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguDDatReqCircQGetFront(): RGU DDatReq Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* kwAcUtlRguDDatReqCircQGetFront */

#ifdef ANSI
PUBLIC S16 kwAcUtlRguDDatReqCircQGetNext
(
KwAcRguDDatReqQ   *queue,
U16            idx
)
#else
PUBLIC S16 kwAcUtlRguDDatReqCircQGetNext(queue, idx)
KwAcRguDDatReqQ   *queue;
U16            idx;
#endif
{
   if ((idx >= queue->rear) && ((queue->front == queue->rear) ||
         (kwAcUtlRguDDatReqCircQAddOne(idx) == queue->front)))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguDDatReqCircQGetNext(): RGU DDatReq Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(kwAcUtlRguDDatReqCircQAddOne(idx));
} /* kwAcUtlRguDDatReqCircQGetNext */

#ifdef ANSI
PUBLIC Void kwAcUtlRguDDatReqCircQDequeue
(
KwAcRguDDatReqQ *queue
)
#else
PUBLIC Void kwAcUtlRguDDatReqCircQDequeue(queue)
KwAcRguDDatReqQ *queue;
#endif
{
   if(KWAC_UTL_RGU_DDATREQ_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguDDatReqCircQDequeue(): RGU DDatReq Queue is empty\n"));
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = kwAcUtlRguDDatReqCircQAddOne(queue->front);
      if(KWAC_UTL_RGU_DDATREQ_CQ_ISEMPTY(queue))
         break;
   }
   RETVOID;
} /* kwAcUtlRguDDatReqCircQDequeue */

  
/**
 * @brief Circular Queue for RGU CData Indication Interface
 *
 * @details
 *
 *     Function : kwAcUtlRguCDatIndCQMakeNull
 *
 *     This function Initializes the RGU CData Indication Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void kwAcUtlRguCDatIndCQMakeNull
(
KwAcRguCDatIndQ   *queue
)
#else
PUBLIC Void kwAcUtlRguCDatIndCQMakeNull(queue)
KwAcRguCDatIndQ   *queue;
#endif
{
   queue->front = 1;
   queue->rear = KWAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* kwAcUtlRguCDatIndCQMakeNull */

#ifdef ANSI
PUBLIC U16 kwAcUtlRguCDatIndCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 kwAcUtlRguCDatIndCircQAddOne(idx)
U16 idx;
#endif
{
   /* kw005.201 Changes for R9 RLC test cases */
   /* 0x3FF below is KWAC_MAX_CIRCQ_SIZE(currently 1024) - 1 */
   if (idx == 0x3FF)
      RETVALUE(1);
   else
      RETVALUE((idx + 1) & 0x3FF);
} /* kwAcUtlRguCDatIndCircQAddOne */

#ifdef ANSI
PUBLIC S16 kwAcUtlRguCDatIndCircQEnqueue
(
KwAcRguCDatIndQ *queue
)
#else
PUBLIC S16 kwAcUtlRguCDatIndCircQEnqueue(queue)
KwAcRguCDatIndQ *queue;
#endif
{
   if(kwAcUtlRguCDatIndCircQAddOne(kwAcUtlRguCDatIndCircQAddOne(\
               kwAcUtlRguCDatIndCircQAddOne(kwAcUtlRguCDatIndCircQAddOne(\
                     queue->rear)))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguCDatIndCircQEnqueue(): RGU CDatInd Queue is full\n"));
      RETVALUE(0);
   }

   queue->rear = kwAcUtlRguCDatIndCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* kwAcUtlRguCDatIndCircQEnqueue */

#ifdef ANSI
PUBLIC U16 kwAcUtlRguCDatIndCircQGetFront
(
KwAcRguCDatIndQ *queue
)
#else
PUBLIC U16 kwAcUtlRguCDatIndCircQGetFront(queue)
KwAcRguCDatIndQ *queue;
#endif
{
   if(KWAC_UTL_RGU_CDATIND_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguCDatIndCircQGetFront(): RGU CDatInd Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* kwAcUtlRguCDatIndCircQGetFront */

#ifdef ANSI
PUBLIC S16 kwAcUtlRguCDatIndCircQGetNext
(
KwAcRguCDatIndQ   *queue,
U16            idx
)
#else
PUBLIC S16 kwAcUtlRguCDatIndCircQGetNext(queue, idx)
KwAcRguCDatIndQ   *queue;
U16            idx;
#endif
{
   if ((queue->front == queue->rear) ||
         (kwAcUtlRguCDatIndCircQAddOne(idx) == queue->front))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguCDatIndCircQGetNext(): RGU CDatInd Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(kwAcUtlRguCDatIndCircQAddOne(idx));
} /* kwAcUtlRguCDatIndCircQGetNext */

#ifdef ANSI
PUBLIC Void kwAcUtlRguCDatIndCircQDequeue
(
KwAcRguCDatIndQ *queue
)
#else
PUBLIC Void kwAcUtlRguCDatIndCircQDequeue(queue)
KwAcRguCDatIndQ *queue;
#endif
{
   if(KWAC_UTL_RGU_CDATIND_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguCDatIndCircQDequeue(): RGU CDatInd Queue is empty\n"));
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = kwAcUtlRguCDatIndCircQAddOne(queue->front);
      if(KWAC_UTL_RGU_CDATIND_CQ_ISEMPTY(queue))
         break;
   }
   RETVOID;
} /* kwAcUtlRguCDatIndCircQDequeue */

  
/**
 * @brief Circular Queue for RGU DData Indication Interface
 *
 * @details
 *
 *     Function : kwAcUtlRguDDatIndCQMakeNull
 *
 *     This function Initializes the RGU DData Indication Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void kwAcUtlRguDDatIndCQMakeNull
(
KwAcRguDDatIndQ   *queue
)
#else
PUBLIC Void kwAcUtlRguDDatIndCQMakeNull(queue)
KwAcRguDDatIndQ   *queue;
#endif
{
   queue->front = 1;
   queue->rear = KWAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* kwAcUtlRguDDatIndCQMakeNull */

#ifdef ANSI
PUBLIC U16 kwAcUtlRguDDatIndCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 kwAcUtlRguDDatIndCircQAddOne(idx)
U16 idx;
#endif
{
   /* kw005.201 Changes for R9 RLC test cases */
   /* 0x3FF below is KWAC_MAX_CIRCQ_SIZE(currently 1024) - 1 */
   if (idx == 0x3FF)
      RETVALUE(1);
   else
      RETVALUE((idx + 1) & 0x3FF);
} /* kwAcUtlRguDDatIndCircQAddOne */

#ifdef ANSI
PUBLIC S16 kwAcUtlRguDDatIndCircQEnqueue
(
KwAcRguDDatIndQ *queue
)
#else
PUBLIC S16 kwAcUtlRguDDatIndCircQEnqueue(queue)
KwAcRguDDatIndQ *queue;
#endif
{
   if(kwAcUtlRguDDatIndCircQAddOne(kwAcUtlRguDDatIndCircQAddOne(\
               kwAcUtlRguDDatIndCircQAddOne(kwAcUtlRguDDatIndCircQAddOne(\
                     queue->rear)))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguDDatIndCircQEnqueue(): RGU DDatInd Queue is full\n"));
      RETVALUE(0);
   }

   queue->rear = kwAcUtlRguDDatIndCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* kwAcUtlRguDDatIndCircQEnqueue */

#ifdef ANSI
PUBLIC U16 kwAcUtlRguDDatIndCircQGetFront
(
KwAcRguDDatIndQ *queue
)
#else
PUBLIC U16 kwAcUtlRguDDatIndCircQGetFront(queue)
KwAcRguDDatIndQ *queue;
#endif
{
   if(KWAC_UTL_RGU_DDATIND_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguDDatIndCircQGetFront(): RGU DDatInd Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* kwAcUtlRguDDatIndCircQGetFront */

#ifdef ANSI
PUBLIC S16 kwAcUtlRguDDatIndCircQGetNext
(
KwAcRguDDatIndQ   *queue,
U16            idx
)
#else
PUBLIC S16 kwAcUtlRguDDatIndCircQGetNext(queue, idx)
KwAcRguDDatIndQ   *queue;
U16            idx;
#endif
{
   if ((queue->front == queue->rear) ||
         (kwAcUtlRguDDatIndCircQAddOne(idx) == queue->front))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguDDatIndCircQGetNext(): RGU DDatInd Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(kwAcUtlRguDDatIndCircQAddOne(idx));
} /* kwAcUtlRguDDatIndCircQGetNext */

#ifdef ANSI
PUBLIC Void kwAcUtlRguDDatIndCircQDequeue
(
KwAcRguDDatIndQ *queue
)
#else
PUBLIC Void kwAcUtlRguDDatIndCircQDequeue(queue)
KwAcRguDDatIndQ *queue;
#endif
{
   if(KWAC_UTL_RGU_DDATIND_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguDDatIndCircQDequeue(): RGU DDatInd Queue is empty\n"))
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = kwAcUtlRguDDatIndCircQAddOne(queue->front);
      if(KWAC_UTL_RGU_DDATIND_CQ_ISEMPTY(queue))
         break;
   }
   RETVOID;
} /* kwAcUtlRguDDatIndCircQDequeue */

  
/**
 * @brief Circular Queue for RGU DStatus Indication Interface
 *
 * @details
 *
 *     Function : kwAcUtlRguDStaIndCQMakeNull
 *
 *     This function Initializes the RGU DStatus Indicattion Circular Q
 *     
 *  @param[in]  *cfgReq
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 **/
#ifdef ANSI
PUBLIC Void kwAcUtlRguDStaIndCQMakeNull
(
KwAcRguDStaIndQ   *queue
)
#else
PUBLIC Void kwAcUtlRguDStaIndCQMakeNull(queue)
KwAcRguDStaIndQ   *queue;
#endif
{
   queue->front = 1;
   queue->rear = KWAC_MAX_CIRCQ_SIZE - 1;

   RETVOID;
} /* kwAcUtlRguDStaIndCQMakeNull */

#ifdef ANSI
PUBLIC U16 kwAcUtlRguDStaIndCircQAddOne
(
U16 idx
)
#else
PUBLIC U16 kwAcUtlRguDStaIndCircQAddOne(idx)
U16 idx;
#endif
{
   /* kw005.201 Changes for R9 RLC test cases */
   /* 0x3FF below is KWAC_MAX_CIRCQ_SIZE(currently 1024) - 1 */
   if (idx == 0x3FF)
      RETVALUE(1);
   else
      RETVALUE((idx + 1) & 0x3FF);
} /* kwAcUtlRguDStaIndCircQAddOne */

#ifdef ANSI
PUBLIC S16 kwAcUtlRguDStaIndCircQEnqueue
(
KwAcRguDStaIndQ *queue
)
#else
PUBLIC S16 kwAcUtlRguDStaIndCircQEnqueue(queue)
KwAcRguDStaIndQ *queue;
#endif
{
   if(kwAcUtlRguDStaIndCircQAddOne(kwAcUtlRguDStaIndCircQAddOne(\
               kwAcUtlRguDStaIndCircQAddOne(kwAcUtlRguDStaIndCircQAddOne(\
                     queue->rear)))) == queue->front)
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguDStaIndCircQEnqueue(): RGU DStaInd Queue is full\n"));
      RETVALUE(0);
   }

   queue->rear = kwAcUtlRguDStaIndCircQAddOne(queue->rear);
   RETVALUE(queue->rear);
} /* kwAcUtlRguDStaIndCircQEnqueue */

#ifdef ANSI
PUBLIC U16 kwAcUtlRguDStaIndCircQGetFront
(
KwAcRguDStaIndQ *queue
)
#else
PUBLIC U16 kwAcUtlRguDStaIndCircQGetFront(queue)
KwAcRguDStaIndQ *queue;
#endif
{
   if(KWAC_UTL_RGU_DSTAIND_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguDStaIndCircQGetFront(): RGU DStaInd Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(queue->front);
} /* kwAcUtlRguDStaIndCircQGetFront */

#ifdef ANSI
PUBLIC S16 kwAcUtlRguDStaIndCircQGetNext
(
KwAcRguDStaIndQ   *queue,
U16            idx
)
#else
PUBLIC S16 kwAcUtlRguDStaIndCircQGetNext(queue, idx)
KwAcRguDStaIndQ   *queue;
U16            idx;
#endif
{
   if ((idx >= queue->rear) && ((queue->front == queue->rear) ||
         (kwAcUtlRguDStaIndCircQAddOne(idx) == queue->front)))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguDStaIndCircQGetNext(): RGU DStaInd Queue is empty\n"));
      RETVALUE(0);
   }

   RETVALUE(kwAcUtlRguDStaIndCircQAddOne(idx));
} /* kwAcUtlRguDStaIndCircQGetNext */

#ifdef ANSI
PUBLIC Void kwAcUtlRguDStaIndCircQDequeue
(
KwAcRguDStaIndQ *queue
)
#else
PUBLIC Void kwAcUtlRguDStaIndCircQDequeue(queue)
KwAcRguDStaIndQ *queue;
#endif
{
   if(KWAC_UTL_RGU_DSTAIND_CQ_ISEMPTY(queue))
   {
      CMXTA_DBG_PARAM((_cmxtap,
               "kwAcUtlRguDStaIndCircQGetFront(): RGU DStaInd Queue is empty\n"));
      RETVOID;
   }

   while (queue->node[queue->front].isInQ == FALSE)
   {
      queue->front = kwAcUtlRguDStaIndCircQAddOne(queue->front);
      if(KWAC_UTL_RGU_DSTAIND_CQ_ISEMPTY(queue))
         break;
   }
   RETVOID;
} /* kwAcUtlRguDStaIndCircQDequeue */

/**********************************************************************
 
         End of file:     kwac_rguutl.c@@/main/TeNB_Main_BR/tenb_br_tdd_e1.2_4.0.0_cr/1 - Thu Nov 20 22:41:29 2014
 
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
/main/1      ---       sm     1. Initial Release.
/main/2      ---       gk     1. LTE RLC Release 2.1.
/main/3      kw003.201 vp     1. Fixes for re-segmentation, segement offset
                                 and optimization 
/main/4      kw005.201 ap     1. Included missing header file string.h
                              2. Removed compilation warning 
                       rd     3. Changes wrt macro KWAC_MAX_CIRCQ_SIZE for
                                 TCs added for RLC R9 upgrade. The following 
                                 funcs are modified:
                                 kwAcUtlRguCDatReqCircQAddOne,
                                 kwAcUtlRguDDatReqCircQAddOne,
                                 kwAcUtlRguCDatIndCircQAddOne, 
                                 kwAcUtlRguDDatIndCircQAddOne,
                                 kwAcUtlRguDStaIndCircQAddOne.
                              4. Added code to change the R1 field value for
                                 UMD PDUs with 10 bit SN in function
                                 kwAcUtlBuildDDatInd()
                              5. Added freeing of l2mUlThrpMeasReq in function
                                 kwAcUtlFreeRguCb.
                              6. Did purify related fixes(UMR) in function 
                                 kwAcUtlValdtL2MUlThrpMeasReq.
                              7. Added support for L2 Measurement.
*********************************************************************91*/
