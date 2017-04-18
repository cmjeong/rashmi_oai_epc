

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_kwuhdl.c

     Sid:      kwac_kwuhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:22:38 2015

     Prg:     cp
*********************************************************************21*/

/* header (.h) include files */
#include <stdlib.h>
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
/* Venki - #ifndef KW_PDCP */
#else
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#endif /* KW_PDCP */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_kwu.h"      /* KWU Acceptance defines */

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
/* Venki - #ifndef KW_PDCP */
#else
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#endif /* KW_PDCP */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_kwu.x"      /* KWU Acceptance defines */


/**
@brief Call handler for command Bind Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlKwuBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlKwuBndReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   SpId          spId;             /* service user SAP identifier */
   Bool          entity;
   S16           error;
   Inst          kwInst;
   
   TRC2(kwAcHdlKwuBndReq);

   entity = ENTNH;
   suId = 0;
   spId = 0;
   error = 0;
   kwInst = 0;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuBndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));
/*Pradeep -start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));

   if (entity == ENTNH)
   {
      /*cmXtaGetPst(&pst, entity, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);*/
      cmXtaGetPst(&pst, entity, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
   }
   else
   {
      cmXtaGetPst(&pst, entity, kwInst, ENTKW, kwInst, 0, 0, FALSE);
   }
/*Pradeep -end*/
   pst.event = KWU_EVT_BND_REQ;
   

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "error",  &(error));

   /* Send the request to the RLC --*/
   if (entity == ENTNH)
   {
      /* Store spId and suId to use in configuration requests */
      if(!error)
      {
         kwAcCb.nhKwuCb.suId = suId;
         kwAcCb.nhKwuCb.spId = spId;
      }

      NhLiKwuBndReq(&pst, suId, spId);
   }
/*#ifndef KW_PDCP*/
   else
   {
      /* Store spId and suId to use in configuration requests */
      if(!error)
      {
         kwAcCb.pjKwuCb.suId = suId;
         kwAcCb.pjKwuCb.spId = spId;
      }

      PjLiKwuBndReq(&pst, suId, spId);
   }
/*#endif  KW_PDCP */

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlKwuBndReq */


/**
@brief Call handler for command Bind Confirm
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlKwuBndCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlKwuBndCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *elm;
   KwAcMsgQElm    *kwElm;
   Status         status;
   Pst            pst;
   Bool           entity;
   Inst           kwInst;
   
   TRC2(kwAcHdlKwuBndCfm);

   status = CM_BND_OK;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuBndCfm(): tcId (%ld)\n", tcCb->tcId));
#else
    CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuBndCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwuBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   entity = ENTNH;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "status",  &(status));

/*Pradeep - start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
   if (entity == ENTNH)
   {
      /* Expected post structure */
      /*cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, entity, CMXTA_INST_ID, 0, 0, FALSE);*/
      cmXtaGetPst(&pst, ENTKW, kwInst, entity, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaGetPst(&pst, ENTKW, kwInst, entity, kwInst, 0, 0, FALSE);
   }
/*Pradeep - end*/

   pst.event = KWU_EVT_BND_CFM;

   if (cmXtaValidatePst(&(elm->pst), &pst) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlKwuBndCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

   /* Incorporating intelligence in XTA for kwu interface to check the suId
    * passed before and confirm recieved same or not */
   if (entity == ENTNH)
   {
      if (kwAcCb.nhKwuCb.suId != kwElm->u.kwuInfo.cmInfo.suId)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.ckwCb.suId, kwElm->u.kwuInfo.cmInfo.suId), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
#ifndef KW_PDCP
   else
   {
      if (kwAcCb.pjKwuCb.suId != kwElm->u.kwuInfo.cmInfo.suId)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.ckwCb.suId, kwElm->u.kwuInfo.cmInfo.suId), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
#endif /* KW_PDCP */

   if (status != kwElm->u.kwuInfo.u.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
               status, kwElm->u.kwuInfo.u.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(ROK);

} /* kwAcHdlKwuBndCfm */


/**
@brief Call handler for command Unbind Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlKwuUnBndReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlKwuUnBndReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst           pst;
   Reason        reason;
   Bool          entity;
   /*Pradeep - start*/
   Inst          kwInst;
   /*Pradeep - end*/
   
   TRC2(kwAcHdlKwuUnBndReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuUnBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuUnBndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));
   entity = ENTNH;
  
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

/*Pradeep - start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));

   /*cmXtaGetPst(&pst, entity, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, entity, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
/*Pradeep - end*/

   pst.event = KWU_EVT_UBND_REQ; 


   reason = 0;

   if(entity == ENTNH)
      NhLiKwuUbndReq(&pst,kwAcCb.nhKwuCb.spId,reason);
#ifndef KW_PDCP
   else
      PjLiKwuUbndReq(&pst,kwAcCb.pjKwuCb.spId,reason);
#endif /* KW_PDCP */
   
   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlKwuUnBndReq */


/**
@brief Call handler for command Dat Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlKwuDatReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlKwuDatReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   KwuDatReqInfo     datReq;
   S16               ret;
   U8                entity;
   Buffer            *mBuf;
   Pst               pst;

   TRC2(kwAcHdlKwuDatReq);

   mBuf = NULLP;
   entity = 0;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuDatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuDatReq(), tcId (%d)\n", tcCb->tcId));
#endif
   /* Get the Entity */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity", &(entity));

   if (entity == ENTNH)
   {
      cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);
      entity = ENTPJ;
   }


   ret = kwAcUtlBuildKwuDatReq(tcCb, spCb, &datReq, &mBuf, entity);
   if(ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }

   /* store the KwAcKwuDatReq info */
   if (entity == ENTNH)
   {
      NhLiKwuDatReq(&pst, kwAcCb.nhKwuCb.spId, &datReq, mBuf);
   }
#ifndef KW_PDCP
   else
   {
      PjLiKwuDatReq(&pst, kwAcCb.pjKwuCb.spId, &datReq, mBuf);
   }
#endif /* KW_PDCP */

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlKwuDatReq */


/**
@brief Call handler for dat Indication 
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlKwuDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlKwuDatInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm      *elm;
   KwAcMsgQElm       *kwElm;
   Pst               pst;
   S16               ret;
   U8                entity;
/*Venki - fixing */
   Inst kwInst;

   TRC2(kwAcHdlKwuDatInd);

   elm = NULLP;
   kwElm =  NULLP;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuDatInd(), tcId (%d)\n", tcCb->tcId));
#endif
   entity = ENTNH;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));
/* Venki - fixing here */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
  
   if (entity == ENTNH)
   {
      cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID+1, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID+1, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   }
   pst.event = KWU_EVT_DAT_IND;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwuDatInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwuDatInd() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

   /* Incorporating intelligence in XTA for kwu interface to check the suId
    * passed before and confirm recieved same or not */
   if (entity == ENTNH)
   {
      if (kwAcCb.nhKwuCb.suId != kwElm->u.kwuInfo.cmInfo.suId)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.ckwCb.suId, kwElm->u.kwuInfo.cmInfo.suId), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
#ifndef KW_PDCP
   else
   {
      if (kwAcCb.pjKwuCb.suId != kwElm->u.kwuInfo.cmInfo.suId)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.ckwCb.suId, kwElm->u.kwuInfo.cmInfo.suId), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
#endif /* KW_PDCP */

   /* validate the data */
   if (kwAcUtlValdtKwuDatInd(tcCb, spCb, kwElm, entity) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlCkwCfgCfm(): Validation Failed.\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlKwuDatInd */


/**
@brief Call handler for command Dat Confirm
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlKwuDatCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlKwuDatCfm(tcCb,spCb)
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
   S16            ret;
   S8             sduId[KWU_MAX_DAT_CFM];
   U8             numSduIds;
   Txt            parseStr[100];
   U32            i;

   TRC2(kwAcHdlKwuDatCfm);
   
   elm = NULLP;
   kwElm =  NULLP;
   rbId = 0;
   rbType = 0;
   ueId = 0;
   cellId = 0;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuDatCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuDatCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWU_EVT_DAT_CFM;
   
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwuDatCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwuDatCfm() : No Match, not for this test case\n"));
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
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSduIds", &(numSduIds));
   KWAC_XML_GET_VALLIST(parseStr, "sduId", ":", sduId, S8);

   if (rbId != kwElm->u.kwuInfo.u.datCfm->rlcId.rbId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatCfm():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.kwuInfo.u.datCfm->rlcId.rbId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (rbType != kwElm->u.kwuInfo.u.datCfm->rlcId.rbType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatCfm():Failed : rbType MisMatch: exp (%d) rcvd (%d) \n",
                  rbType, kwElm->u.kwuInfo.u.datCfm->rlcId.rbType), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.kwuInfo.u.datCfm->rlcId.ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatCfm():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.kwuInfo.u.datCfm->rlcId.ueId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.kwuInfo.u.datCfm->rlcId.cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatCfm():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.kwuInfo.u.datCfm->rlcId.cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if ((numSduIds != (U8) kwElm->u.kwuInfo.u.datCfm->numSduIds))
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatCfm():Failed : numSduIds MisMatch: exp (%d) rcvd (%ld) \n",
                  numSduIds, kwElm->u.kwuInfo.u.datCfm->numSduIds), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatCfm():Failed : numSduIds MisMatch: exp (%d) rcvd (%d) \n",
                  numSduIds, kwElm->u.kwuInfo.u.datCfm->numSduIds), 2);
#endif
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   for(i=0; i< numSduIds; i++)
   {
      if(sduId[0] == -1)
         break; /* No need to check sduId */
     
      if ((sduId[0] != -1) && (sduId[0] != (U8) kwElm->u.kwuInfo.u.datCfm->sduIds[0]))
      {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatCfm():Failed : sduId MisMatch: exp (%d) rcvd (%ld) \n",
                  sduId[0], kwElm->u.kwuInfo.u.datCfm->sduIds[0]), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatCfm():Failed : sduId MisMatch: exp (%d) rcvd (%d) \n",
                  sduId[0], kwElm->u.kwuInfo.u.datCfm->sduIds[0]), 2);
#endif
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlKwuDatCfm */


/**
@brief Call handler for discard sdu request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlKwuDiscSduReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlKwuDiscSduReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst               pst;
   KwuDiscSduInfo    *discSduInfo;

   TRC2(kwAcHdlKwuDiscSduReq);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuDiscSduReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuDiscSduReq(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(discSduInfo, sizeof(KwuDiscSduInfo));
   if (discSduInfo == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwuDiscSduReq(): KW_ALLOC discSduInfo Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWU_EVT_DISC_SDU_REQ;

   /* Fill rlcId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(discSduInfo->rlcId.rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(discSduInfo->rlcId.rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(discSduInfo->rlcId.ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(discSduInfo->rlcId.cellId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "sduId", &(discSduInfo->sduIds[0]));
   discSduInfo->numSduIds = 1;

#ifndef KW_PDCP
   PjLiKwuDiscSduReq(&pst, kwAcCb.pjKwuCb.spId, discSduInfo);
#endif /* KW_PDCP */

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlKwuDiscSduReq */


/**
@brief Call handler for Status Indication
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlKwuStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlKwuStaInd(tcCb,spCb)
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
   U8             numSdu;
   U16            idx;
   U32            sduId[KWU_MAX_STA_IND_SDU];

   TRC2(kwAcHdlKwuStaInd);

   elm = NULLP;
   kwElm =  NULLP;
   rbId = 0;
   rbType = 0;
   ueId = 0;
   cellId = 0;
   ret = CMXTA_ERR_NONE;

   CMXTA_ZERO(sduId, sizeof(U32) * KWU_MAX_STA_IND_SDU);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuStaInd(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWU_EVT_STA_IND;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwuStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwuStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

#ifndef KW_PDCP
   /* Incorporating intelligence in XTA for ckw interface to check the suId
    * passed before and confirm recieved same or not */
   if (kwAcCb.pjKwuCb.suId != kwElm->u.kwuInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuStaInd():Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.pjKwuCb.suId, kwElm->u.kwuInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }
#endif /* KW_PDCP */

   /* validate the data */
   /* Fill rlcId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSdu", &(numSdu));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON,
         "sduId", sduId, &numSdu);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));

   if (rbId != kwElm->u.kwuInfo.u.staInd->rlcId.rbId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuStaInd():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.kwuInfo.u.staInd->rlcId.rbId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (rbType != kwElm->u.kwuInfo.u.staInd->rlcId.rbType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuStaInd():Failed : rbType MisMatch: exp (%d) rcvd (%d) \n",
                  rbType, kwElm->u.kwuInfo.u.staInd->rlcId.rbType), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.kwuInfo.u.staInd->rlcId.ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuStaInd():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.kwuInfo.u.staInd->rlcId.ueId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.kwuInfo.u.staInd->rlcId.cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuStaInd():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.kwuInfo.u.staInd->rlcId.cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   for (idx = 0; idx < numSdu; idx++)
   {
      if (sduId[idx] != kwElm->u.kwuInfo.u.staInd->sduId[idx])
      {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatCfm():Failed : sduId MisMatch: exp (%ld) rcvd (%ld) \n",
                  sduId[idx], kwElm->u.kwuInfo.u.staInd->sduId[idx]), 2);
#else
          CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatCfm():Failed : sduId MisMatch: exp (%d) rcvd (%d) \n",
                  sduId[idx], kwElm->u.kwuInfo.u.staInd->sduId[idx]), 2);
#endif
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);

} /* kwAcHdlKwuStaInd */
/* kw005.201 Added support for L2 Measurement. */
#ifdef LTE_L2_MEAS

/**
@brief Call handler for Dat Ack indication
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlKwuDatAckInd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlKwuDatAckInd(tcCb,spCb)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *elm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   S16            ret;
   U8             rbId;
   CmLteRnti      ueId;
   CmLteCellId    cellId;
   U32            sduId;

   TRC2(kwAcHdlKwuDatAckInd);

   elm = NULLP;
   kwElm =  NULLP;
   rbId = 0;
   ueId = 0;
   cellId = 0;
   ret = CMXTA_ERR_NONE;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuDatAckInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuDatAckInd(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWU_EVT_DAT_ACK_IND;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwuDatAckInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwuDatAckInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

#ifndef KW_PDCP
   /* Incorporating intelligence in XTA for ckw interface to check the suId
    * passed before and confirm recieved same or not */
   if (kwAcCb.pjKwuCb.suId != kwElm->u.kwuInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatAckInd():Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  kwAcCb.pjKwuCb.suId, kwElm->u.kwuInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }
#endif /* KW_PDCP */

   /* validate the data */
   /* Fill rlcId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "sduId", &sduId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));

   if (rbId != kwElm->u.kwuInfo.u.datAckInd->rlcId.rbId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatAckInd():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.kwuInfo.u.datAckInd->rlcId.rbId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.kwuInfo.u.datAckInd->rlcId.ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatAckInd():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.kwuInfo.u.datAckInd->rlcId.ueId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.kwuInfo.u.datAckInd->rlcId.cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatAckInd():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.kwuInfo.u.datAckInd->rlcId.cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

    if (sduId != kwElm->u.kwuInfo.u.datAckInd->sduId)
    {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatAckInd():Failed : sduId MisMatch: exp (%ld) rcvd (%ld) \n",
                  sduId, kwElm->u.kwuInfo.u.datAckInd->sduId), 2);
#else
          CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDatAckInd():Failed : sduId MisMatch: exp (%d) rcvd (%d) \n",
                  sduId, kwElm->u.kwuInfo.u.datAckInd->sduId), 2);
#endif
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
    }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);

} /* kwAcHdlKwuDatAckInd */


/**
@brief Call handler for SDU Disc confirm
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlKwuDiscSduCfm
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlKwuDiscSduCfm(tcCb,spCb)
CmXtaTCCb  *tcCb;
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
   S16            ret;
   S32            sduId;
 
   TRC2(kwAcHdlKwuDiscSduCfm);
   
   elm = NULLP;
   kwElm =  NULLP;
   rbId = 0;
   rbType = 0;
   ueId = 0;
   cellId = 0;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuDiscSduCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwuDiscSduCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWU_EVT_DISC_SDU_CFM;
   
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwuDiscSduCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwuDiscSduCfm() : No Match, not for this test case\n"));
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
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "sduId", &(sduId));


   if (rbId != kwElm->u.kwuInfo.u.discSduCfm->rlcId.rbId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDiscSduCfm():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.kwuInfo.u.discSduCfm->rlcId.rbId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (rbType != kwElm->u.kwuInfo.u.discSduCfm->rlcId.rbType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDiscSduCfm():Failed : rbType MisMatch: exp (%d) rcvd (%d) \n",
                  rbType, kwElm->u.kwuInfo.u.discSduCfm->rlcId.rbType), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.kwuInfo.u.discSduCfm->rlcId.ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDiscSduCfm():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.kwuInfo.u.discSduCfm->rlcId.ueId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.kwuInfo.u.discSduCfm->rlcId.cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDiscSduCfm():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.kwuInfo.u.discSduCfm->rlcId.cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if ((sduId != -1) && (sduId != (S32) kwElm->u.kwuInfo.u.discSduCfm->sduIds[0]))
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDiscSdufm():Failed : sduId MisMatch: exp (%ld) rcvd (%ld) \n",
                  sduId, kwElm->u.kwuInfo.u.discSduCfm->sduIds[0]), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "kwAcHdlKwuDiscSduCfm():Failed : sduId MisMatch: exp (%d) rcvd (%d) \n",
                  sduId, kwElm->u.kwuInfo.u.discSduCfm->sduIds[0]), 2);
#endif
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcHdlKwuDiscSduCfm */
#endif
/********************************************************************30**

         End of file:     kwac_kwuhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:22:38 2015

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
/main/3      kw005.201 ap     1. Added support for L2 Measurement.
*********************************************************************91*/
