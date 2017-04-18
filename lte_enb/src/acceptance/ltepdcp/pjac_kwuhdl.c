

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_kwuhdl.c

     Sid:      pjac_kwuhdl.c@@/main/TeNB_Main_BR/1 - Tue Aug 12 15:44:03 2014

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
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_kwu.h"      /* KWU Acceptance defines */

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
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_kwu.x"      /* KWU Acceptance defines */

PUBLIC KwAcKwuCb  kwAcKwuCb;
/**
@brief Call handler for command Bind Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuBndReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   SpId          spId;             /* service user SAP identifier */
   S16           error;
   Inst          Inst;
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   
   TRC2(pjAcHdlKwuBndReq);

   qElm     = NULLP;
   kwElm    = NULLP;
   suId = 0;
   spId = 0;
   error = 0;
   Inst = 0;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuBndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwuBndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
                                                                                                                                                                        
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(Inst));

   cmXtaGetPst(&pst, ENTPJ , Inst, ENTKW, Inst, 0, 0, FALSE);
   
   pst.event = KWU_EVT_BND_REQ;
   
   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
                                                                                                                                                                        
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
                                                                                                                                                                        
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
                                                                                                                                                                        
   if (suId != kwElm->u.kwuInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, kwElm->u.kwuInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }
                                                                                                                                                                        
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
                                                                                                                                                                        
   if (spId != kwElm->u.kwuInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId MisMatch: exp (%d) rcvd (%d) \n",
                  spId, kwElm->u.kwuInfo.spId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }
                                                                                                                                                                        
   /* Store spId and suId to use in configuration requests */
   if(!error)
   {
      kwAcCb.pjKwuCb.suId = suId;
      kwAcCb.pjKwuCb.spId = spId;
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlKwuBndReq */

/**
@brief Call handler for command Bind Confirm
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuBndCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuBndCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm      *elm;
   KwAcMsgQElm       *kwElm;
   Pst               pst;
   S16               ret;
   SuId              suId;
   Inst kwInst;
   Buffer            *mBuf;

   TRC2(pjAcHdlKwuBndCfm)

   elm = NULLP;
   kwElm =  NULLP;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
  
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID+1, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   pst.event = KWU_EVT_BND_CFM;

   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
                                                                                                                                                                        
   /* Send the Indication to the RLC --*/
   KwUiKwuBndCfm(&pst, suId, CM_BND_OK);
   RETVALUE(ROK);

} /* pjAcHdlKwuBndCfm */

/**
@brief Call handler for command Unbind Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuUnBndReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuUnBndReq(tcCb,spCb)
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
   
   TRC2(pjAcHdlKwuUnBndReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuUnBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuUnBndReq(), tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&pst, sizeof(Pst));
   entity = ENTNH;
  
   /* Add print for RRC and PDCP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity",  &(entity));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));

   cmXtaGetPst(&pst, entity, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);

   pst.event = KWU_EVT_UBND_REQ; 

   reason = 0;

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlKwuUnBndReq */


/**
@brief Call handler for command Dat Request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuDatReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuDatReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm    *kwElm;
   Pst            pst;
   SpId           spId;
   KwuDatReqInfo     *datReq;
   S16               ret;
   U8                entity;
   Buffer            *mBuf;

   TRC2(pjAcHdlKwuDatReq);

   datReq = NULLP;
   mBuf = NULLP;
   entity = 0;
   qElm     = NULLP;
   kwElm    = NULLP;
   spId     = 0;
   ret = CMXTA_ERR_NONE;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDatReq(), tcId (%d)\n", tcCb->tcId));
#endif
   /* Get the Entity */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "entity", &(entity));
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlRguDDatReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
                                                                                                                                                                        
   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = PJAC_KWU_EVT_DAT_REQ;
                                                                                                                                                                        
   if (cmXtaValidatePst(&(qElm->pst), &pst) != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
                                                                                                                                                                        
   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);
                                                                                                                                                                        
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
                                                                                                                                                                        
   if (kwAcCb.pjKwuCb.spId != kwElm->u.kwuInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SpId MisMatch: exp (%d) rcvd (%d) \n",
                  spId, kwElm->u.kwuInfo.spId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);
   entity = ENTPJ;

   /* TODO : Need to add this */
   ret = pjAcUtlValdtKwuDatReq(tcCb, spCb, kwElm->u.kwuInfo.u.datReq,kwElm->mBuf); 
   /* handle dat req here , refer rguhdl */
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlKwuDatReq */


/**
@brief Call handler for dat Indication 
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuDatInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm      *elm;
   KwAcMsgQElm       *kwElm;
   Pst               pst;
   S16               ret;
   SuId              suId;
/*Venki - fixing */
   Inst kwInst;
   KwuDatIndInfo datInd;
   Buffer            *mBuf;

   TRC2(pjAcHdlKwuDatInd);

   elm = NULLP;
   kwElm =  NULLP;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDatInd(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
  
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID+1, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   pst.event = KWU_EVT_DAT_IND;

   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
                                                                                                                                                                        
   /* Allocate memory for cfgReq */
/*   KW_ALLOC_ACC(datInd, sizeof(KwuDatIndInfo));
   if (datInd == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwuDatInd(): PJ_ALLOC datInd Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   } */
                                                                                                                                                                        
   ret = pjAcUtlBuildDatInd(tcCb, spCb,&datInd, &mBuf);
   if (ret != CMXTA_ERR_NONE)
   {
   /*   KW_FREE_ACC(datInd, sizeof(KwuDatIndInfo)); */
      RETVALUE(ret);
   }
   /* Send the Indication to the RLC --*/
   KwUiKwuDatInd(&pst, suId,&datInd, mBuf);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlKwuDatInd */


/**
@brief Call handler for ReEst Cmp Ind
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuReEstCmpInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuReEstCmpInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm      *elm;
   KwAcMsgQElm       *kwElm;
   Pst               pst;
   S16               ret;
   SuId              suId;
   CmLteRlcId        rlcId;
   Inst              kwInst;
   KwuDatIndInfo     *datInd;
   Buffer            *mBuf;
   U8                rbId[CPJ_MAX_CFG];
   U8                tnumRbId;
   U8                rbType[CPJ_MAX_CFG];
   U8                tnumRbType;
   U8                count;

   TRC2(pjAcHdlKwuReEstCmpInd);

   elm = NULLP;
   kwElm =  NULLP;
   CMXTA_ZERO(&rlcId,sizeof(rlcId));
   CMXTA_ZERO(rbId, sizeof(rbId));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDatInd(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
  
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID+1, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   pst.event = KWU_EVT_DAT_IND;

   suId = 0;
   /* the assumption will be such that one ReEst Cmp Ind cmd can be used to send CmpInd for all RB of a single UE only*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(rlcId.ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(rlcId.cellId));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "rbId", rbId, &tnumRbId);                                                                                                                                                                        
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "rbType", rbType, &tnumRbType);                                                                                                                                                                        
   for (count = 0; count < tnumRbId; count++ )
   {
      rlcId.rbId = rbId[count];
      rlcId.rbType = rbType[count];
      /* Send the Indication to the RLC --*/
      KwUiKwuReEstCmpInd(&pst, suId, rlcId); /* These needs to be modified in a generic way */
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlKwuDatInd */


/**
/**
@brief Call handler for command Dat Confirm
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuDatCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuDatCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst            pst;
   S16            ret;
   KwuDatCfmInfo  *datCfm;
   SuId           suId;
   U8             sduAckId[256];
   U32            sduCnt = 0;
   Txt            holdMain = NULLP, *tokSub = NULLP, *tok2 = NULLP;   
   U8             tnumSduId = 0;
   KwAcPjuDatReq  *datReq;
   S16            idx;
 
   TRC2(pjAcHdlKwuDatCfm);
  
   CMXTA_ZERO(sduAckId, sizeof(sduAckId));
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDatCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDatCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWU_EVT_DAT_CFM;

   /* Allocate memory for cfgReq */
   PJ_ALLOC_ACC(datCfm, sizeof(KwuDatCfmInfo));
   if (NULLP == datCfm)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwuDatCfm(): PJ_ALLOC datCfm Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId",  &(datCfm->rlcId.ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(datCfm->rlcId.cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId",  &(datCfm->rlcId.rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(datCfm->rlcId.rbType));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "sduAck", sduAckId, &tnumSduId); 
 /*  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "sduAck", sduAckId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numSdu", &(tnumSduId)); */

   while ((sduCnt < 256) && (sduCnt < tnumSduId))
   {
      datCfm->sduIds[sduCnt++] = sduAckId[sduCnt];
   }
   if(sduCnt == 0)
   {
      if (datCfm->rlcId.rbType == 0)
      {
#if 0
         idx = pjAcUtlPjuDatReqCircQGetFront(&kwAcCb.nhPjuCb.datReq);
         datReq = &kwAcCb.nhPjuCb.datReq.node[idx];
#else
         datCfm->sduIds[sduCnt++] = kwAcCb.nhPjuCb.nxtSduId[datCfm->rlcId.cellId][datCfm->rlcId.ueId][0][datCfm->rlcId.rbId]-1;
#endif
      }
      else
      {
#if 0
         idx = pjAcUtlPjuDatReqCircQGetFront(&kwAcCb.pxPjuCb.datReq);
         datReq = &kwAcCb.pxPjuCb.datReq.node[idx];
#else
         datCfm->sduIds[sduCnt++] = kwAcCb.pxPjuCb.nxtSduId[datCfm->rlcId.cellId][datCfm->rlcId.ueId][1][datCfm->rlcId.rbId]-1;
#endif
      }
      datCfm->sduIds[sduCnt++] = datReq->sduId;
   }
   datCfm->numSduIds = sduCnt;

   KwUiKwuDatCfm(&pst, suId, datCfm);

   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlKwuDatCfm */


/**
@brief Call handler for discard sdu request
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuDiscSduCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuDiscSduCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst               pst;
   KwuDiscSduInfo    *discSduInfo;

   TRC2(pjAcHdlKwuDiscSduCfm);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDiscSduCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDiscSduCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(discSduInfo, sizeof(KwuDiscSduInfo));
   if (discSduInfo == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwuDiscSduCfm(): KW_ALLOC discSduInfo Failed\n"));
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
   PjLiKwuDiscSduCfm(&pst, kwAcCb.pjKwuCb.spId, discSduInfo);
#endif
   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlKwuDiscSduCfm */
#if 0

/**
@brief Call handler for Status Indication
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuStaInd(tcCb,spCb)
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

   TRC2(pjAcHdlKwuStaInd);

   elm = NULLP;
   kwElm =  NULLP;
   rbId = 0;
   rbType = 0;
   ueId = 0;
   cellId = 0;
   ret = CMXTA_ERR_NONE;

   CMXTA_ZERO(sduId, sizeof(U32) * KWU_MAX_STA_IND_SDU);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuStaInd(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWU_EVT_STA_IND;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwuStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlKwuStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

#ifndef KW_PDCP
   /* Incorporating intelligence in XTA for ckw interface to check the suId
    * passed before and confirm recieved same or not */
   if (kwAcCb.pjKwuCb.suId != kwElm->u.kwuInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuStaInd():Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
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
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuStaInd():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.kwuInfo.u.staInd->rlcId.rbId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (rbType != kwElm->u.kwuInfo.u.staInd->rlcId.rbType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuStaInd():Failed : rbType MisMatch: exp (%d) rcvd (%d) \n",
                  rbType, kwElm->u.kwuInfo.u.staInd->rlcId.rbType), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.kwuInfo.u.staInd->rlcId.ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuStaInd():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.kwuInfo.u.staInd->rlcId.ueId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.kwuInfo.u.staInd->rlcId.cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuStaInd():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.kwuInfo.u.staInd->rlcId.cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   for (idx = 0; idx < numSdu; idx++)
   {
      if (sduId[idx] != kwElm->u.kwuInfo.u.staInd->sduId[idx])
      {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDatCfm():Failed : sduId MisMatch: exp (%ld) rcvd (%ld) \n",
                  sduId[idx], kwElm->u.kwuInfo.u.staInd->sduId[idx]), 2);
#else
          CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDatCfm():Failed : sduId MisMatch: exp (%d) rcvd (%d) \n",
                  sduId[idx], kwElm->u.kwuInfo.u.staInd->sduId[idx]), 2);
#endif
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);

} /* pjAcHdlKwuStaInd */
#endif

/* kw005.201 Added support for L2 Measurement. */
#ifdef LTE_L2_MEAS

/**
@brief Call handler for Dat Ack indication
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuDatAckInd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuDatAckInd(tcCb,spCb)
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

   TRC2(pjAcHdlKwuDatAckInd);

   elm = NULLP;
   kwElm =  NULLP;
   rbId = 0;
   ueId = 0;
   cellId = 0;
   ret = CMXTA_ERR_NONE;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDatAckInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDatAckInd(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWU_EVT_DAT_ACK_IND;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwuDatAckInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlKwuDatAckInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the elm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm);

#ifndef KW_PDCP
   /* Incorporating intelligence in XTA for ckw interface to check the suId
    * passed before and confirm recieved same or not */
   if (kwAcCb.pjKwuCb.suId != kwElm->u.kwuInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDatAckInd():Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
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
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDatAckInd():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.kwuInfo.u.datAckInd->rlcId.rbId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.kwuInfo.u.datAckInd->rlcId.ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDatAckInd():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.kwuInfo.u.datAckInd->rlcId.ueId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.kwuInfo.u.datAckInd->rlcId.cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDatAckInd():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.kwuInfo.u.datAckInd->rlcId.cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

    if (sduId != kwElm->u.kwuInfo.u.datAckInd->sduId)
    {
#ifndef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDatAckInd():Failed : sduId MisMatch: exp (%ld) rcvd (%ld) \n",
                  sduId, kwElm->u.kwuInfo.u.datAckInd->sduId), 2);
#else
          CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDatAckInd():Failed : sduId MisMatch: exp (%d) rcvd (%d) \n",
                  sduId, kwElm->u.kwuInfo.u.datAckInd->sduId), 2);
#endif
         cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
         RETVALUE(CMXTA_ERR_INT);
    }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);

} /* pjAcHdlKwuDatAckInd */


/**
@brief Call handler for SDU Disc confirm
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
/*
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuDiscSduCfm
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuDiscSduCfm(tcCb,spCb)
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
 
   TRC2(pjAcHdlKwuDiscSduCfm);
   
   elm = NULLP;
   kwElm =  NULLP;
   rbId = 0;
   rbType = 0;
   ueId = 0;
   cellId = 0;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDiscSduCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuDiscSduCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWU_EVT_DISC_SDU_CFM;
   
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &elm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwuDiscSduCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)elm->data;

   ret = cmXtaValidatePst(&(elm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlKwuDiscSduCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
   */
   /*-- Remove the elm from the Queue --
   cmXtaPopMsg (&(tcCb->msgQ[0]), &elm); */

   /* validate the data */
   /* Fill rlcId */
 /*  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(cellId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "sduId", &(sduId));


   if (rbId != kwElm->u.kwuInfo.u.discSduCfm->rlcId.rbId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDiscSduCfm():Failed : rbId MisMatch: exp (%d) rcvd (%d) \n",
                  rbId, kwElm->u.kwuInfo.u.discSduCfm->rlcId.rbId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (rbType != kwElm->u.kwuInfo.u.discSduCfm->rlcId.rbType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDiscSduCfm():Failed : rbType MisMatch: exp (%d) rcvd (%d) \n",
                  rbType, kwElm->u.kwuInfo.u.discSduCfm->rlcId.rbType), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (ueId != kwElm->u.kwuInfo.u.discSduCfm->rlcId.ueId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDiscSduCfm():Failed : ueId MisMatch: exp (%d) rcvd (%d) \n",
                  ueId, kwElm->u.kwuInfo.u.discSduCfm->rlcId.ueId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (cellId != kwElm->u.kwuInfo.u.discSduCfm->rlcId.cellId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDiscSduCfm():Failed : cellId MisMatch: exp (%d) rcvd (%d) \n",
                  cellId, kwElm->u.kwuInfo.u.discSduCfm->rlcId.cellId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   if ((sduId != -1) && (sduId != (S32) kwElm->u.kwuInfo.u.discSduCfm->sduIds[0]))
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDiscSdufm():Failed : sduId MisMatch: exp (%ld) rcvd (%ld) \n",
                  sduId, kwElm->u.kwuInfo.u.discSduCfm->sduIds[0]), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "pjAcHdlKwuDiscSduCfm():Failed : sduId MisMatch: exp (%d) rcvd (%d) \n",
                  sduId, kwElm->u.kwuInfo.u.discSduCfm->sduId), 2);
#endif
      cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), elm);

   RETVALUE(CMXTA_ERR_NONE);
} */   /* pjAcHdlKwuDiscSduCfm */
#endif

/**
 * @brief Skip Validation Handler for KWU interface.
 *
 * @details
 *
 *     Function : pjAcHdlShutdown
 *
 *     If tester does not want a particular indication from MAC
 *     to be validated, he can just issue the leaf command SKIP,
 *     This is the corresponding handler function for SKIP, which
 *     will pop off the last received indication, without any
 *     further processing.
 *
 *  @param[in]  *tcCb
 *  @param[in]  *spCb
 *  @return  S16
 *      -# CMXTA_ERR_NONE
 *      -# CMXTA_ERR_FATAL
 **/
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuShutdown
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlKwuShutdown(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   U16            idx = 0;
   PjAcKwuDatReq  *kwuDatReq = NULLP;
                                                                                                                                                                        
   TRC2(pjAcHdlShutdown);

   UNUSED(spCb);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuShutdown(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuShutdown(): tcId (%d)\n", tcCb->tcId));
#endif
                                                                                                                                                                           /*************************************************************************
    *                      KWU FREE
    ************************************************************************/
   /* PDCP - ENTPJ Free */
   idx = pjAcUtlKwuDatReqCircQGetFront(&kwAcCb.pjKwuCb.datReq);
   while (idx)
   {
      kwuDatReq = &kwAcCb.pjKwuCb.datReq.node[idx];
      if (kwuDatReq->isInQ)
      {
         PJ_FREE_BUF(kwuDatReq->mBuf);
         CMXTA_ZERO(kwuDatReq, sizeof(PjAcKwuDatReq));
      }
      idx = pjAcUtlKwuDatReqCircQGetNext(&kwAcCb.pjKwuCb.datReq, idx);
      pjAcUtlKwuDatReqCircQDequeue(&kwAcCb.pjKwuCb.datReq);
   }
                                                                                                                                                                        
   /* Configuration Confirmation is freed once we got the confirmation */
                                                                                                                                                                        
   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlKwuShutdown */
                                                                                                                                                                        


/**
@brief Call handler for dat Indication 
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
/*
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuCtrlDatInd
(
CmXtaTCCb    *tcCb,    
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuCtrlDatInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm      *elm;
   KwAcMsgQElm       *kwElm;
   Pst               pst;
   S16               ret;
   SuId              suId;

   Inst kwInst;
   KwuDatIndInfo *datInd;
   Buffer            *mBuf;

   TRC2(pjAcHdlKwuCtrlDatInd);

   elm = NULLP;
   kwElm =  NULLP;
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuCtrlDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuCtrlDatInd(), tcId (%d)\n", tcCb->tcId));
#endif
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
  
   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID+1, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   pst.event = KWU_EVT_DAT_IND;

   suId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
                                                                                                                                                                        
   
   KW_ALLOC_ACC(datInd, sizeof(KwuDatIndInfo));
   if (datInd == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwuCtrlDatInd(): PJ_ALLOC datInd Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
                                                                                                                                                                        
   ret = pjAcUtlBuildCtrlDatInd(tcCb, spCb, datInd, &mBuf);
   if (ret != CMXTA_ERR_NONE)
   {
      KW_FREE_ACC(datInd, sizeof(KwuDatIndInfo));
      RETVALUE(ret);
   }
   
   KwUiKwuDatInd(&pst, suId, datInd, mBuf);

   RETVALUE(CMXTA_ERR_NONE);
} *//* pjAcHdlKwuDatInd */



/**
@brief Call handler for Status Indication
@param tcCb
@param spCb
@return CMXTA_ERR_NONE if success
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlKwuStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlKwuStaInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Pst               pst;
   KwuStaIndInfo    *staIndInfo;

   TRC2(pjAcHdlKwuStaInd);
#ifndef ALIGN_64BIT   
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlKwuStaInd(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* Allocate memory for cfgReq */
   KW_ALLOC_ACC(staIndInfo, sizeof(KwuStaIndInfo));
   if (staIndInfo == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwuStaInd(): KW_ALLOC staIndInfo Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = KWU_EVT_STA_IND;

   /* Fill rlcId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbId", &(staIndInfo->rlcId.rbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rbType", &(staIndInfo->rlcId.rbType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &(staIndInfo->rlcId.ueId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &(staIndInfo->rlcId.cellId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "sduId", &(staIndInfo->sduId[0]));
   staIndInfo->numSdu = 1;
   
#ifndef KW_PDCP   
   PjLiKwuStaInd(&pst, kwAcCb.pjKwuCb.spId, staIndInfo);
#endif
   RETVALUE(CMXTA_ERR_NONE);
} /* pjAcHdlKwuStaInd */

/********************************************************************30**

         End of file:     pjac_kwuhdl.c@@/main/TeNB_Main_BR/1 - Tue Aug 12 15:44:03 2014

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
/main/1      ---       vb        1. LTE PDCP Initial release 2.1
*********************************************************************91*/
