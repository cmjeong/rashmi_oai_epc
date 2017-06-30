

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_pjuhdl.c

     Sid:      pjac_pjuhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:05 2015

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
#include "rgu.h"           /* RGU defines */
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
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
#include "kwu.x"           /* KWU */
#include "pju.x"           /* PJU */
#include "rgu.x"           /* RGU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_pju.x"      /* PJU Acceptance defines */
#include "pjac_lib.x"

/**
@brief Call handler for command Bind Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlPjuBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlPjuBndReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   SpId          spId;             /* service user SAP identifier */
   Bool          entity;
   S16           error;
   Inst          pjInst;

   TRC2(pjAcHdlPjuBndReq);

   entity = ENTPX;
   suId = 0;
   spId = 0;
   error = 0;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuBndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   if (entity == ENTNH)
      cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, pjInst, 0, 0, FALSE);
   else
      cmXtaGetPst(&pst, ENTPX, CMXTA_INST_ID, ENTPJ, pjInst, 0, 0, FALSE);

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
} /* pjAcHdlPjuBndReq */


/**
@brief Call handler for command Bind Confirm
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlPjuBndCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlPjuBndCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *elm;
   KwAcMsgQElm    *kwElm;
   Status         status;
   Pst            pst;
   U8             entity;
   Inst           pjInst;

   TRC2(pjAcHdlPjuBndCfm);

   status = CM_BND_OK;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuBndCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuBndCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlPjuBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   entity = ENTPX;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "status",  &(status));
  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   if (entity == ENTNH)
      cmXtaGetPst(&pst, ENTPJ, pjInst, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   else
      cmXtaGetPst(&pst, ENTPJ, pjInst, ENTPX, CMXTA_INST_ID, 0, 0, FALSE);

   pst.event = EVTPJUBNDCFM;

   if (cmXtaValidatePst(&(elm->pst), &pst) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "pjAcHdlPjuBndCfm() : No Match, not for this test case\n"));
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

} /* pjAcHdlPjuBndCfm */


/**
@brief Call handler for command Unbind Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlPjuUnBndReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlPjuUnBndReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst           pst;
   Reason        reason;
   U8            entity;

   TRC2(pjAcHdlPjuUnBndReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuUnBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuUnBndReq(), tcId (%d)\n", tcCb->tcId));
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
} /* pjAcHdlPjuUnBndReq */


/**
@brief Call handler for command Dat Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlPjuDatReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlPjuDatReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmLtePdcpId       pdcpId;
   S16               ret;
   Buffer            *mBuf;
   Pst               pst;
   U32               sduId;
   U8                entity;

   TRC2(pjAcHdlPjuDatReq);

   mBuf = NULLP;
 /*  pdcpId = NULLP; */
   entity = ENTPX;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuDatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuDatReq(), tcId (%d)\n", tcCb->tcId));
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
 /*  KW_ALLOC_ACC(pdcpId, sizeof(CmLtePdcpId));
   if (pdcpId == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlPjuDatReq(): KW_ALLOC pdcpId Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }  */ 

   ret = pjAcUtlBuildPjuDatReq(tcCb, spCb,&pdcpId, &sduId, &mBuf, entity);
   if(ret != CMXTA_ERR_NONE)
   {
      RETVALUE(ret);
   }

   if (entity == ENTNH)
      /* kw005.201 corrected arguments in the function */
      NhLiPjuDatReq(&pst, kwAcCb.nhPjuCb.spId,&pdcpId, sduId, mBuf);
   else
      PxLiPjuDatReq(&pst, kwAcCb.pxPjuCb.spId, &pdcpId, sduId, mBuf);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlPjuDatReq */


/**
@brief Call handler for dat Indication 
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlPjuDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlPjuDatInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm      *elm;
   KwAcMsgQElm       *kwElm;
   Pst               pst;
   S16               ret;
   U8                entity;

   TRC2(pjAcHdlPjuDatInd);

   elm = NULLP;
   kwElm =  NULLP;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuDatInd(), tcId (%d)\n", tcCb->tcId));
#endif

   entity = ENTPX;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   if (entity == ENTNH)
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID+1, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID+1, ENTPX, CMXTA_INST_ID, 0, 0, FALSE);
   }
   pst.event = EVTPJUDATIND;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlPjuDatInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;
   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlPjuDatInd() : No Match, not for this test case\n"));
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
   if (pjAcUtlValdtPjuDatInd(tcCb, spCb, kwElm, entity) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlPjuDatInd(): Validation Failed.\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlPjuDatInd */


/**
@brief Call handler for command Dat Confirm
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlPjuDatCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlPjuDatCfm(tcCb,spCb)
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
 
   TRC2(pjAcHdlPjuDatCfm);
   
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
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuDatCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuDatCfm(), tcId (%d)\n", tcCb->tcId));
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
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlPjuDatCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlPjuDatCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
  
   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

   /* validate the data */
   /* Fill rlcId */
/*   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));  */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "numSdu", &(numSdu));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, CMXTA_SEP_COLON,
                 "sduId", sduId, &tmpNum);
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,
                 "status", status, &tmpNum);

/*   if (rbId != kwElm->u.pjuInfo.pdcpId->rbId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuDatCfm():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.pjuInfo.pdcpId->rbId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (rbType != kwElm->u.pjuInfo.pdcpId->rbType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuDatCfm():Failed : rbType MisMatch: exp (%d) rcvd (%d) \n",
                  rbType, kwElm->u.pjuInfo.pdcpId->rbType), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.pjuInfo.pdcpId->ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuDatCfm():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.pjuInfo.pdcpId->ueId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.pjuInfo.pdcpId->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuDatCfm():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.pjuInfo.pdcpId->cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   } */

   if (numSdu != kwElm->u.pjuInfo.u.datCfm->numSdus)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuDatCfm():Failed : numSdus MisMatch: exp (%d) rcvd (%d) \n",
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
                  "pjAcHdlPjuDatCfm():Failed : MisMatch:sduId  exp (%ld) rcvd (%ld) status exp (%d) rcvd (%d) \n",
                  sduId[idx], kwElm->u.pjuInfo.u.datCfm->cfmSta[idx].sduId,
                  status[idx], kwElm->u.pjuInfo.u.datCfm->cfmSta[idx].status), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap,
                  "pjAcHdlPjuDatCfm():Failed : MisMatch:sduId  exp (%d) rcvd (%d) status exp (%d) rcvd (%d) \n",
                  sduId[idx], kwElm->u.pjuInfo.u.datCfm->cfmSta[idx].sduId,
                  status[idx], kwElm->u.pjuInfo.u.datCfm->cfmSta[idx].status), 2);
#endif
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlPjuDatCfm */


/**
@brief Call handler for Status Indication
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlPjuStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlPjuStaInd(tcCb,spCb)
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
   /* Venki */
   Inst           pjInst;

   TRC2(pjAcHdlPjuStaInd);

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
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuStaInd(), tcId (%d)\n", tcCb->tcId));
#endif
   entity = ENTPX;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));
   /* venki */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(pjInst));


   if (entity == ENTNH)
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID+1, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID+1, entity, CMXTA_INST_ID, 0, 0, FALSE);
   }
   pst.event = EVTPJUSTAIND;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlPjuStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlPjuStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

   /* Incorporating intelligence in XTA for ckw interface to check the suId
    * passed before and confirm recieved same or not */
   if (kwAcCb.pxPjuCb.suId != kwElm->u.pjuInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuStaInd():Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
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
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuStaInd():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.pjuInfo.pdcpId->rbId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (rbType != kwElm->u.pjuInfo.pdcpId->rbType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuStaInd():Failed : rbType MisMatch: exp (%d) rcvd (%d) \n",
                  rbType, kwElm->u.pjuInfo.pdcpId->rbType), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.pjuInfo.pdcpId->ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuStaInd():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.pjuInfo.pdcpId->ueId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.pjuInfo.pdcpId->cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuStaInd():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.pjuInfo.pdcpId->cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cause != kwElm->u.pjuInfo.u.staInd->cause)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuStaInd():Failed : Cause MisMatch: exp (%d) rcvd (%d) \n",
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
         CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuStaInd():Failed : mBuf msgLen Mismatch: exp(%d) rcvd(%d) \n",
                  len, msgLen), 2);
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlPjuStaInd():Failed : mBuf Not Present: \n"), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);

} /* pjAcHdlPjuStaInd */


/**
@brief Call handler for command Dat Forward Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlPjuDatFwdReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlPjuDatFwdReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjuDatFwdReqInfo  *datFwdReq;
   CmLtePdcpId       pdcpId;
   S16               ret;
   Buffer            *mBuf;
   Pst               pst;
   U8                entity;
   U8                module;
/*Pradeep*/
   U8                inst = 0;
/*Pradeep*/

   TRC2(pjAcHdlPjuDatFwdReq);

   datFwdReq = NULLP;
   mBuf = NULLP;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuDatFwdReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuDatFwdReq(), tcId (%d)\n", tcCb->tcId));
#endif
   entity = ENTPX;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

/*Pradeep*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(inst));
/*Pradeep*/
   if (entity == ENTNH)
   {
      cmXtaGetPst(&pst, ENTNH, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "module",  &(module));
      if(module == PJAC_DL_PDCP)
      {
         /* DL PDCP's Instance is 0 */
         cmXtaGetPst(&pst, ENTPX, CMXTA_INST_ID, ENTPJ, inst, 0, 0, FALSE);
      }     
      else
      {
         /* UL PDCP's Instance is 1 - So dstInst = 1, inst+1 */
         cmXtaGetPst(&pst, ENTPX, CMXTA_INST_ID, ENTPJ, inst+1, 0, 0, FALSE);
      }
   }

   /* Allocate memory for datFwdReq */
   KW_ALLOC_ACC(datFwdReq, sizeof(PjuDatFwdReqInfo));
   if (datFwdReq == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlPjuDatFwdReq(): KW_ALLOC datFwdReq Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = pjAcUtlBuildPjuDatFwdReq(tcCb, spCb, datFwdReq, &pdcpId);
   if(ret != CMXTA_ERR_NONE)
   {
      KW_FREE_ACC(datFwdReq, sizeof(PjuDatFwdReqInfo));
      RETVALUE(ret);
   }

   /* Allocate memory for pdcpId */
/*   KW_ALLOC_ACC(pdcpId, sizeof(CmLtePdcpId));
   if (pdcpId == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlPjuDatFwdReq(): KW_ALLOC pdcpId Failed\n"));
      KW_FREE_ACC(datFwdReq, sizeof(PjuDatFwdReqInfo));
      RETVALUE(CMXTA_ERR_INT);
   }  */

   /* Fill CmLtePdcpId */
 /*  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", pdcpId.rbId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", pdcpId.ueId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", pdcpId.cellId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", pdcpId.rbType);*/

   if (entity == ENTNH)
      /* kw005.201 corrected arguments in the function */
      NhLiPjuDatFwdReq(&pst, kwAcCb.nhPjuCb.spId, &pdcpId, datFwdReq);
   else
      PxLiPjuDatFwdReq(&pst, kwAcCb.pxPjuCb.spId, &pdcpId, datFwdReq);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlPjuDatFwdReq */


/**
@brief Call handler for dat Forward Indication 
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlPjuDatFwdInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlPjuDatFwdInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm      *elm;
   KwAcMsgQElm       *kwElm;
   Pst               pst;
   S16               ret;
   U8                entity;
   U8                module;
   /*Anshika - start*/
   U8                inst;
   /*Anshika - end*/

   TRC2(pjAcHdlPjuDatFwdInd);

   elm = NULLP;
   kwElm =  NULLP;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuDatFwdInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuDatFwdInd(), tcId (%d)\n", tcCb->tcId));
#endif
   entity = ENTPX;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   /*Anshika - start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(inst));
   /*Anshika - end*/

   if (entity == ENTNH)
   {
      cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
   }
   else
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "module",  &(module));
      if(module == PJAC_DL_PDCP)
      {
         /* DL PDCP's Instance is 0 */
         cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTPX, CMXTA_INST_ID, 0, 0, FALSE);
      }     
      else
      {
         /* UL PDCP's Instance is 1 - So CMXTA_INST_ID+1 */
         cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID+1, ENTPX, CMXTA_INST_ID, 0, 0, FALSE);
      }
   }
   pst.event = EVTPJUDATFWDIND;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlPjuDatFwdInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlPjuDatFwdInd() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

   /* Incorporating intelligence in XTA for pju interface to check the suId
    * passed before and confirm recieved same or not */
   if (kwAcCb.pxPjuCb.suId != kwElm->u.pjuInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
               kwAcCb.pxPjuCb.suId, kwElm->u.pjuInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* validate the data */
   if (pjAcUtlValdtPjuDatFwdInd(tcCb, spCb, kwElm) != CMXTA_ERR_NONE)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcUtlValdtPjuDatFwdInd(): Validation Failed.\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlPjuDatFwdInd */


#ifdef ANSI
PUBLIC S16 pjAcHdlPjuShutdown
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlPjuShutdown(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
  /* U16            idx = 0;   
   KwAcPjuDatReq  *pjuDatReq = NULLP; */
                                                                                                                                                                        
   TRC2(pjAcHdlPjuShutdown);

   UNUSED(spCb);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuShutdown(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlPjuShutdown(): tcId (%d)\n", tcCb->tcId));
#endif
                                                                                                                                                                           /*************************************************************************
    *                      PJU FREE
    ************************************************************************/
   /* PDCP - ENTPJ Free */
  U16 idx1 = pjAcUtlPjuDatReqCircQGetFront(&kwAcCb.pxPjuCb.datReq);
   while (idx1)
   {
       KwAcPjuDatReq  *pjuDatReq = &kwAcCb.pxPjuCb.datReq.node[idx1];
       if (pjuDatReq->isInQ)
       {
          PJ_FREE_BUF(pjuDatReq->mBuf);
          CMXTA_ZERO(pjuDatReq, sizeof(PjAcKwuDatReq));
       }
       else
       idx1 = pjAcUtlPjuDatReqCircQGetNext(&kwAcCb.pxPjuCb.datReq, idx1);
       pjAcUtlPjuDatReqCircQDequeue(&kwAcCb.pxPjuCb.datReq);
   }

   U16 idx2 = pjAcUtlPjuDatReqCircQGetFront(&kwAcCb.nhPjuCb.datReq);
   while (idx2)
   {
      KwAcPjuDatReq *pjuDatReq = &kwAcCb.nhPjuCb.datReq.node[idx2];
      if (pjuDatReq->isInQ)
      {
         PJ_FREE_BUF(pjuDatReq->mBuf);
         CMXTA_ZERO(pjuDatReq, sizeof(PjAcKwuDatReq));
      }
      else
      idx2 = pjAcUtlPjuDatReqCircQGetNext(&kwAcCb.nhPjuCb.datReq, idx2);
      pjAcUtlPjuDatReqCircQDequeue(&kwAcCb.nhPjuCb.datReq);
   }
   if (idx2 == 0)
   /* Configuration Confirmation is freed once we got the confirmation */
                                                                                                                                                                        
   /* For the freeing of KwAcLibCb */
   {
      CmLList       *lstEnt = NULLP;
      CmLListCp     *datQ   = NULLP;
      KwAcLibOutEnt *ent    = NULLP;
      KwAcLibSecEnt *secEnt = NULLP;

      datQ = &(libCb.compCb.compOutList);
      while (cmLListFirst(datQ))
      {
         lstEnt = cmLListDelFrm(datQ, cmLListCrnt(datQ));
         if ( lstEnt != NULLP)
         {
            ent = (KwAcLibOutEnt *)cmLListNode(lstEnt);
            if ( ent->mBuf != NULLP )
            {
               PJ_FREE_BUF(ent->mBuf);
            }
            PJ_FREE_ACC(ent, sizeof(KwAcLibOutEnt));
         }
      }
      cmLListInit(datQ);
 
      datQ = &(libCb.cipCb.cipOutList);
      while (cmLListFirst(datQ))
      {
         lstEnt = cmLListDelFrm(datQ, cmLListCrnt(datQ));
         if ( lstEnt != NULLP)
         {
            ent = (KwAcLibOutEnt *)cmLListNode(lstEnt);
            if ( ent->mBuf != NULLP )
            {
               PJ_FREE_BUF(ent->mBuf);
            }
            PJ_FREE_ACC(ent, sizeof(KwAcLibOutEnt));
         }
      }
      cmLListInit(datQ);
  
      datQ = &(libCb.intCb.intOutList);
      while (cmLListFirst(datQ))
      {
         lstEnt = cmLListDelFrm(datQ, cmLListCrnt(datQ));
         if ( lstEnt != NULLP)
         {
            ent = (KwAcLibOutEnt *)cmLListNode(lstEnt);
            if ( ent->mBuf != NULLP )
            {
               PJ_FREE_BUF(ent->mBuf);
            }
            PJ_FREE_ACC(ent, sizeof(KwAcLibOutEnt));
         }
      }
      cmLListInit(datQ);

      datQ = &(libCb.intCb.intList); 
      while (cmLListFirst(datQ))
      {
         lstEnt = cmLListDelFrm(datQ, cmLListCrnt(datQ));
         if ( lstEnt != NULLP)
         {
            secEnt = (KwAcLibSecEnt *)cmLListNode(lstEnt);
            PJ_FREE_ACC(secEnt, sizeof(KwAcLibSecEnt));
         }
      }
      cmLListInit(datQ);
    
      datQ = &(libCb.cipCb.cipList);   
      while (cmLListFirst(datQ))
      {
         lstEnt = cmLListDelFrm(datQ, cmLListCrnt(datQ));
         if ( lstEnt != NULLP)
         {
            secEnt = (KwAcLibSecEnt *)cmLListNode(lstEnt);
            PJ_FREE_ACC(secEnt, sizeof(KwAcLibOutEnt));
         }
      }
      cmLListInit(datQ);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlPjuShutdown */
                                                                                                                                                                        

/********************************************************************30**

         End of file:     pjac_pjuhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:05 2015

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
/main/1      ---       vb         1. LTE PDCP Initial Release 2.1.
*********************************************************************91*/
