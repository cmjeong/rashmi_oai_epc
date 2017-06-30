

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_pjuhdl.c

     Sid:      kwac_pjuhdl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:38 2014

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
#include "kwu.x"           /* KWU */
#include "pju.x"           /* PJU */
#include "rgu.x"           /* RGU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_pju.x"      /* PJU Acceptance defines */


#ifdef KW_PDCP
/**
@brief Call handler for command Bind Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlPjuBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlPjuBndReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   SpId          spId;             /* service user SAP identifier */
   Bool          entity;
   S16           error;

   TRC2(kwAcHdlPjuBndReq);

   entity = ENTPX;
   suId = 0;
   spId = 0;
   error = 0;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuBndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   if (entity == ENTNH)
      cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   else
      cmXtaGetPst(&pst, ENTPX, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);

   pst.event = EVTPJUBNDREQ;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "error",  &(error));

   /* Store spId and suId to use in configuration requests */
   if(!error)
   {
      if (entity == ENTNH)
      {
         kwAcCb.nhPjuCb.suId = suId;
         kwAcCb.nhPjuCb.spId = spId;
      }
      else
      {
         kwAcCb.pxPjuCb.suId = suId;
         kwAcCb.pxPjuCb.spId = spId;
      }
   }

   if (entity == ENTNH)
      NhLiPjuBndReq(&pst, suId, spId);
   else
      PxLiPjuBndReq(&pst, suId, spId);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlPjuBndReq */


/**
@brief Call handler for command Bind Confirm
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlPjuBndCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlPjuBndCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *elm;
   KwAcMsgQElm    *kwElm;
   Status         status;
   Pst            pst;
   U8             entity;

   TRC2(kwAcHdlPjuBndCfm);

   status = CM_BND_OK;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuBndCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuBndCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlPjuBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   entity = ENTPX;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "status",  &(status));

   if (entity == ENTNH)
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   else
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTPX, CMXTA_INST_ID, 0, 0, FALSE);

   pst.event = EVTPJUBNDCFM;

   if (cmXtaValidatePst(&(elm->pst), &pst) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlPjuBndCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

   /* Incorporating intelligence in XTA for pju interface to check the suId
    * passed before and confirm recieved same or not */
   if (entity == ENTNH)
   {
      if (kwAcCb.nhPjuCb.suId != kwElm->u.pjuInfo.cmInfo.suId)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.ckwCb.suId, kwElm->u.pjuInfo.cmInfo.suId), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else
   {
      if (kwAcCb.pxPjuCb.suId != kwElm->u.pjuInfo.cmInfo.suId)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.ckwCb.suId, kwElm->u.pjuInfo.cmInfo.suId), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   if (status != kwElm->u.pjuInfo.u.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
               status, kwElm->u.pjuInfo.u.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(ROK);

} /* kwAcHdlPjuBndCfm */


/**
@brief Call handler for command Unbind Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlPjuUnBndReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlPjuUnBndReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst           pst;
   Reason        reason;
   U8            entity;

   TRC2(kwAcHdlPjuUnBndReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuUnBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuUnBndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));
  
   entity = ENTPX;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   cmXtaGetPst(&pst, entity, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);

   pst.event = EVTPJUUBNDREQ; 

   reason = 0;

   if (entity == ENTNH)
      NhLiPjuUbndReq(&pst,kwAcCb.nhPjuCb.spId, reason);
   else
      PxLiPjuUbndReq(&pst,kwAcCb.pxPjuCb.spId, reason);
   
   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlPjuUnBndReq */


/**
@brief Call handler for command Dat Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlPjuDatReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlPjuDatReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmLtePdcpId       *pdcpId;
   S16               ret;
   Buffer            *mBuf;
   Pst               pst;
   U32               sduId;
   U8                entity;

   TRC2(kwAcHdlPjuDatReq);

   mBuf = NULLP;
   pdcpId = NULLP;
   entity = ENTPX;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuDatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuDatReq(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   if (entity == ENTNH)
   {
      cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaGetPst(&pst, ENTPX, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
      entity = ENTPX;
   }


   /* Allocate memory for pdcpId */
   KW_ALLOC_ACC(pdcpId, sizeof(CmLtePdcpId));
   if (pdcpId == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlPjuDatReq(): KW_ALLOC pdcpId Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = kwAcUtlBuildPjuDatReq(tcCb, spCb, pdcpId, &sduId, &mBuf, entity);
   if(ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }

   if (entity == ENTNH)
      /* kw005.201 corrected arguments in the function */
      NhLiPjuDatReq(&pst, kwAcCb.nhPjuCb.spId, pdcpId, sduId, mBuf);
   else
      PxLiPjuDatReq(&pst, kwAcCb.pxPjuCb.spId, pdcpId, sduId, mBuf);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlPjuDatReq */


/**
@brief Call handler for dat Indication 
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlPjuDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlPjuDatInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm      *elm;
   KwAcMsgQElm       *kwElm;
   Pst               pst;
   S16               ret;
   U8                entity;

   TRC2(kwAcHdlPjuDatInd);

   elm = NULLP;
   kwElm =  NULLP;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuDatInd(), tcId (%d)\n", tcCb->tcId));
#endif

   entity = ENTPX;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   if (entity == ENTNH)
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTPX, CMXTA_INST_ID, 0, 0, FALSE);
   }
   pst.event = EVTPJUDATIND;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlPjuDatInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlPjuDatInd() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

   /* Incorporating intelligence in XTA for pju interface to check the suId
    * passed before and confirm recieved same or not */
   if (entity == ENTNH)
   {
      if (kwAcCb.nhPjuCb.suId != kwElm->u.pjuInfo.cmInfo.suId)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.nhPjuCb.suId, kwElm->u.pjuInfo.cmInfo.suId), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else
   {
      if (kwAcCb.pxPjuCb.suId != kwElm->u.pjuInfo.cmInfo.suId)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.pxPjuCb.suId, kwElm->u.pjuInfo.cmInfo.suId), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   /* validate the data */
   if (kwAcUtlValdtPjuDatInd(tcCb, spCb, kwElm, entity) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlPjuDatInd(): Validation Failed.\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlPjuDatInd */


/**
@brief Call handler for command Dat Confirm
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlPjuDatCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlPjuDatCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *elm;
   KwAcMsgQElm    *kwElm;
   U8             rbId;
   U8             rbType;
   CmLteRnti      ueId;
   CmLteCellId    cellId;
   Pst            pst;
   U8             idx;
   S16            ret;
   S32            sduId[PJU_MAX_SDU_CFM];
   U8             status[PJU_MAX_SDU_CFM];
   U16            numSdu;
   U8             tmpNum = 0;
   U8             entity;
 
   TRC2(kwAcHdlPjuDatCfm);
   
   elm = NULLP;
   kwElm =  NULLP;
   rbId = 0;
   rbType = 0;
   ueId = 0;
   cellId = 0;
   numSdu = 1;

   CMXTA_ZERO(sduId, sizeof(sduId));
   CMXTA_ZERO(status, sizeof(status));
   CMXTA_ZERO(&pst, sizeof(Pst));
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuDatCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuDatCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   entity = ENTPX;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   if (entity == ENTNH)
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTPX, CMXTA_INST_ID, 0, 0, FALSE);
   }
   pst.event = EVTPJUDATCFM;
   
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlPjuDatCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlPjuDatCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
  
   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

   /* validate the data */
   /* Fill rlcId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "numSdu", &(numSdu));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON,
                 "sduId", sduId, &tmpNum);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
                 "status", status, &tmpNum);

   if (rbId != kwElm->u.pjuInfo.pdcpId->rbId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuDatCfm():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.pjuInfo.pdcpId->rbId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (rbType != kwElm->u.pjuInfo.pdcpId->rbType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuDatCfm():Failed : rbType MisMatch: exp (%d) rcvd (%d) \n",
                  rbType, kwElm->u.pjuInfo.pdcpId->rbType), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.pjuInfo.pdcpId->ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuDatCfm():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.pjuInfo.pdcpId->ueId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.pjuInfo.pdcpId->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuDatCfm():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.pjuInfo.pdcpId->cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (numSdu != kwElm->u.pjuInfo.u.datCfm->numSdus)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuDatCfm():Failed : numSdus MisMatch: exp (%d) rcvd (%d) \n",
                  numSdu, kwElm->u.pjuInfo.u.datCfm->numSdus), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   for (idx = 0; idx < numSdu; idx++)
   {
      if ((sduId[idx] != -1) && 
            (sduId[idx] != (S32) kwElm->u.pjuInfo.u.datCfm->cfmSta[idx].sduId) &&
            (status[idx] != kwElm->u.pjuInfo.u.datCfm->cfmSta[idx].status))
      {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap,
                  "kwAcHdlPjuDatCfm():Failed : MisMatch:sduId  exp (%ld) rcvd (%ld) status exp (%d) rcvd (%d) \n",
                  sduId[idx], kwElm->u.pjuInfo.u.datCfm->cfmSta[idx].sduId,
                  status[idx], kwElm->u.pjuInfo.u.datCfm->cfmSta[idx].status), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap,
                  "kwAcHdlPjuDatCfm():Failed : MisMatch:sduId  exp (%d) rcvd (%d) status exp (%d) rcvd (%d) \n",
                  sduId[idx], kwElm->u.pjuInfo.u.datCfm->cfmSta[idx].sduId,
                  status[idx], kwElm->u.pjuInfo.u.datCfm->cfmSta[idx].status), 2);
#endif
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlPjuDatCfm */


/**
@brief Call handler for Status Indication
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlPjuStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlPjuStaInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *elm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   S16            ret;
   U8             rbId;
   U8             rbType;
   CmLteRnti      ueId;
   CmLteCellId    cellId;
   U8             cause;
   MsgLen         msgLen, len;
   U8             bufPrsnt;
   U8             entity;

   TRC2(kwAcHdlPjuStaInd);

   elm = NULLP;
   kwElm =  NULLP;
   rbId = 0;
   rbType = 0;
   ueId = 0;
   cellId = 0;
   ret = CMXTA_ERR_NONE;
   msgLen = 0;
   len = -1;
   bufPrsnt = 0;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuStaInd(), tcId (%d)\n", tcCb->tcId));
#endif
   entity = ENTPX;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   if (entity == ENTNH)
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTPX, CMXTA_INST_ID, 0, 0, FALSE);
   }
   pst.event = EVTPJUSTAIND;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlPjuStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlPjuStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

   /* Incorporating intelligence in XTA for ckw interface to check the suId
    * passed before and confirm recieved same or not */
   if (kwAcCb.pxPjuCb.suId != kwElm->u.pjuInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuStaInd():Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.pxPjuCb.suId, kwElm->u.pjuInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* validate the data */
   /* Fill rlcId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cause", &(cause));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));

   if (rbId != kwElm->u.pjuInfo.pdcpId->rbId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuStaInd():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.pjuInfo.pdcpId->rbId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (rbType != kwElm->u.pjuInfo.pdcpId->rbType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuStaInd():Failed : rbType MisMatch: exp (%d) rcvd (%d) \n",
                  rbType, kwElm->u.pjuInfo.pdcpId->rbType), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.pjuInfo.pdcpId->ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuStaInd():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.pjuInfo.pdcpId->ueId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.pjuInfo.pdcpId->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuStaInd():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.pjuInfo.pdcpId->cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cause != kwElm->u.pjuInfo.u.staInd->cause)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuStaInd():Failed : Cause MisMatch: exp (%d) rcvd (%d) \n",
                  cause, kwElm->u.pjuInfo.u.staInd->cause), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Check for mBuf and msgLen in case of bufPrsnt is TRUE */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bufPrsnt", &(bufPrsnt));
   if (((kwElm->mBuf != NULLP) && (bufPrsnt == 1)) || 
       ((kwElm->mBuf == NULLP) && (bufPrsnt == 0)))
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "len", &(len));
      if(len != -1) SFndLenMsg(kwElm->mBuf, &msgLen);
      if ((len != -1) && (msgLen == len))
      {
         CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuStaInd():Failed : mBuf msgLen Mismatch: exp(%d) rcvd(%d) \n",
                  len, msgLen), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlPjuStaInd():Failed : mBuf Not Present: \n"), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);

} /* kwAcHdlPjuStaInd */


/**
@brief Call handler for command Dat Forward Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlPjuDatFwdReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlPjuDatFwdReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjuDatFwdReqInfo  *datFwdReq;
   CmLtePdcpId       *pdcpId;
   S16               ret;
   Buffer            *mBuf;
   Pst               pst;
   U8                entity;

   TRC2(kwAcHdlPjuDatFwdReq);

   datFwdReq = NULLP;
   mBuf = NULLP;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuDatFwdReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuDatFwdReq(), tcId (%d)\n", tcCb->tcId));
#endif
   entity = ENTPX;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   if (entity == ENTNH)
   {
      cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaGetPst(&pst, ENTPX, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   }

   /* Allocate memory for datFwdReq */
   KW_ALLOC_ACC(datFwdReq, sizeof(PjuDatFwdReqInfo));
   if (datFwdReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlPjuDatFwdReq(): KW_ALLOC datFwdReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = kwAcUtlBuildPjuDatFwdReq(tcCb, spCb, datFwdReq);
   if(ret != CMXTA_ERR_NONE)
   {
      KW_FREE_ACC(datFwdReq, sizeof(PjuDatFwdReqInfo));
      RETVALUE(ret);
   }

   /* Allocate memory for pdcpId */
   KW_ALLOC_ACC(pdcpId, sizeof(CmLtePdcpId));
   if (pdcpId == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlPjuDatFwdReq(): KW_ALLOC pdcpId Failed\n"));
      KW_FREE_ACC(datFwdReq, sizeof(PjuDatFwdReqInfo));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Fill CmLtePdcpId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(pdcpId->rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(pdcpId->ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(pdcpId->cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(pdcpId->rbType));

   if (entity == ENTNH)
      /* kw005.201 corrected arguments in the function */
      NhLiPjuDatFwdReq(&pst, kwAcCb.nhPjuCb.spId, pdcpId, datFwdReq);
   else
      PxLiPjuDatFwdReq(&pst, kwAcCb.pxPjuCb.spId, pdcpId, datFwdReq);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlPjuDatFwdReq */


/**
@brief Call handler for dat Forward Indication 
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlPjuDatFwdInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlPjuDatFwdInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm      *elm;
   KwAcMsgQElm       *kwElm;
   Pst               pst;
   S16               ret;
   U8                entity;

   TRC2(kwAcHdlPjuDatFwdInd);

   elm = NULLP;
   kwElm =  NULLP;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuDatFwdInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlPjuDatFwdInd(), tcId (%d)\n", tcCb->tcId));
#endif
   entity = ENTPX;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   if (entity == ENTNH)
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTPX, CMXTA_INST_ID, 0, 0, FALSE);
   }
   pst.event = EVTPJUDATFWDIND;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlPjuDatFwdInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlPjuDatFwdInd() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

   /* Incorporating intelligence in XTA for pju interface to check the suId
    * passed before and confirm recieved same or not */
   if (kwAcCb.pxPjuCb.suId != kwElm->u.pjuInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
               kwAcCb.ckwCb.suId, kwElm->u.pjuInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* validate the data */
   if (kwAcUtlValdtPjuDatFwdInd(tcCb, spCb, kwElm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcUtlValdtPjuDatFwdInd(): Validation Failed.\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlPjuDatFwdInd */

#endif /* KW_PDCP */
/********************************************************************30**

         End of file:     kwac_pjuhdl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:38 2014

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
/main/2      kw005.201 ap     1. Corrected the arguments in the function NhLiPjuDatReq
                                 and NhLiPjuDatFwdReq.
*********************************************************************91*/

