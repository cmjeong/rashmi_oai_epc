

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_lpjhdl.c

     Sid:      kwac_lpjhdl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:34 2014

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
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_lpj.h"      /* CKW Acceptance defines */

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
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_lpj.x"      /* CKW Acceptance defines */

#ifdef KW_PDCP
/*
*
*       Fun:   kwAcHdlLpjDirective
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  kwac_lpjhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjDirective
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjDirective(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Bool  posTc =  FALSE;
   Bool  negTc =  FALSE;
   TRC2(kwAcHdlLpjDirective)


#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjDirective(): tcCb (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjDirective(): tcCb (%d)\n", tcCb->tcId));
#endif


   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "successTc", &posTc);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "failureTc", &negTc); 

   if(posTc)
      kwAcCb.directive.numPosTc++;
   if(negTc)
      kwAcCb.directive.numNegTc++;

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcHdlLpjDirective */

/**
@brief Call handler for command general configuration
@param tcCb
@param spCb
@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjGenCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjGenCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt cfg;
   Pst pst;

   CmXtaTxnCb* txnCb;
   TRC2(kwAcHdlLpjGenCfgReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjGenCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjGenCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cfg, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_CFG_REQ;

   kwAcUtlPjBuildGenCfgReq(tcCb, spCb, &cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID, STGEN, pst.selector);


   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending General Configuration request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCfgReq(&pst, &cfg);

   RETVALUE(ROK);
} /* kwAcHdlLpjGenCfgReq */

/**
@brief Call handler for Command Sap configuration Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjSapCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjSapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt cfg;
   Pst pst;
   CmXtaTxnCb* txnCb;
   U8   elmnt = 0;

   TRC2(kwAcHdlLpjSapCfgReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cfg, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_CFG_REQ;

   /* Possible values for elmnt : STKWUSAP, STCKWSAP, STRGUSAP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "elmnt", &(elmnt));
   cfg.hdr.elmId.elmnt = elmnt;

   kwAcUtlPjBuildSapCfgReq(tcCb, spCb, &cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID, cfg.hdr.elmId.elmnt, pst.selector);


   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Sap Configuration request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCfgReq(&pst, &cfg);

   RETVALUE(ROK);
} /* kwAcHdlLpjSapCfgReq */


/**
@brief Call handler for Command Trace Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjTrcCntrlReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt  cntrl;
   Pst      pst;
   U16      isEnable = 0;

   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLpjTrcCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "isEnable",  &isEnable);

   if(isEnable == 1)
   {
      cntrl.t.cntrl.action = AENA;
      cntrl.t.cntrl.subAction = SATRC;
   }
   else
   {
      cntrl.t.cntrl.action = ADISIMM;
      cntrl.t.cntrl.subAction = SATRC;
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "trcMask",  &(cntrl.t.cntrl.s.trcCntrl.trcMask));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "trcLen",  &(cntrl.t.cntrl.s.trcCntrl.trcLen));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_CNTRL_REQ;


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trace Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* kwAcHdlLpjTrcCntrlReq */

/**
@brief Call handler for Command USta Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjUStaCntrlReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjUStaCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt  cntrl;
   Pst      pst;
   U16      isEnable = 0;

   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLpjUStaCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjUStaCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjUStaCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "isEnable",  &isEnable);

   if(isEnable == 1)
   {
      cntrl.t.cntrl.action = AENA;
      cntrl.t.cntrl.subAction = SAUSTA;
   }
   else
   {
      cntrl.t.cntrl.action = ADISIMM;
      cntrl.t.cntrl.subAction = SAUSTA;
   }

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_CNTRL_REQ;


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trace Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* kwAcHdlLpjUStaCntrlReq */

/**
@brief Call handler for Command Shutdown Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjSDCntrlReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjSDCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt  cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLpjSDCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjSDCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjSDCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_CNTRL_REQ;

  /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   kwAcUtlPjBuildSDCntrlReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Shutdown Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* kwAcHdlLpjSDCntrlReq */


/**
@brief Call handler for Command Debug Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjDbgCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjDbgCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt  cntrl;
   Pst      pst;
   U16      isEnable = 0;

   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLpjDbgCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjDbgCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjDbgCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "isEnable",  &isEnable);

   if(isEnable == 1)
   {
      cntrl.t.cntrl.action = AENA;
      cntrl.t.cntrl.subAction = SADBG;
   }
   else
   {
      cntrl.t.cntrl.action = ADISIMM;
      cntrl.t.cntrl.subAction = SADBG;
   }

   /* Debug Mask should be provided in decimal (equivalent binary */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dbgMask",  &(cntrl.t.cntrl.s.dbgCntrl.dbgMask));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_CNTRL_REQ;

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Debug Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* kwAcHdlLpjDbgCntrlReq */


/**
@brief Call handler for Command Statistics Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjStsReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt  sts;
   Pst      pst;
   Action  action;         /* zeroing action */
   CmXtaTxnCb* txnCb;
   U16      elmnt;

   TRC2(kwAcHdlLpjStsReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjStsReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjStsReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&sts, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   elmnt = 0;

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_STS_REQ;

   action = ZEROSTS;
   /* read from xml    */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "action",  &action);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "elmnt",  &elmnt);
   /* kw005.201 passing spId for pjuSapSts */
   if(elmnt == STPJUSAP)
   {
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "spId",  &sts.t.sts.s.pjuSap.spId);
   }


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID, elmnt, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Statistics request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjStsReq(&pst, action, &sts);

   RETVALUE(ROK);
} /* kwAcHdlLpjStsReq */


/**
@brief Call handler for Command Status Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt     sta;
   Pst         pst;
   Action      action;         /* zeroing action */
   CmXtaTxnCb* txnCb;
   U16         elmnt;

   TRC2(kwAcHdlLpjStaReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjStaReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjStaReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&sta, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   elmnt  = 0;

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_STA_REQ;

   action = ZEROSTS;

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "elmnt",  &elmnt);
   /* Prepare header */
   (Void) cmXtaInitHdr(&(sta.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID, elmnt, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Statistics request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjStaReq(&pst, &sta);

   RETVALUE(ROK);
} /* kwAcHdlLpjStaReq */


/**
@brief Callback for Command Configuration Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;   
   CmStatus       status;
   Pst            pst;
   S16            ret;

   TRC2(kwAcHdlLpjCfgCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjCfgCfm(): tcId (%ld)\n", tcCb->tcId));  
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjCfgCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   kwElm = NULLP;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlLpjCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_CFG_CFM;
   
   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlLpjCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the qElm from the Queue --*/
   if (cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlLpjCfgCfm() : cmXtaPopMsg Failed.\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   kwElm = (KwAcMsgQElm *)qElm->data;

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(kwElm->u.pjMngmt.cfm));
      
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlLpjCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ROK);

} /* kwAcHdlLpjCfgCfm */

/**
@brief Callback for Command Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjCntrlCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjCntrlCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(kwAcHdlLpjCntrlCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjCntrlCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjCntrlCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwCntrlCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_CNTRL_CFM;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwCntrlCfm() :  No Match, not for this Test Case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(kwElm->u.pjMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwCntrlCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
   RETVALUE(ROK);
} /* kwAcHdlLpjCntrlCfm */

/**
@brief Callback for Command Statistics request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjStsCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjStsCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(kwAcHdlLpjStsCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjStsCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjStsCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwStsCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;
   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_STS_CFM;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStsCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(kwElm->u.pjMngmt.cfm));
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStsCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Verify statistics */
   ret = kwAcUtlPjVerifyStsCfm(tcCb, spCb, &(kwElm->u.pjMngmt.t.sts));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStsCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ROK);
} /* kwAcHdlLpjStsCfm */

/**
@brief Callback for Command Status request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjStaCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(kwAcHdlLpjStaCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjStaCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjStaCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwStaCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_STA_CFM;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStaCfm() : No match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the qElm from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(kwElm->u.pjMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Verify status */
   ret = kwAcUtlPjVerifyStaCfm(tcCb, spCb, &(kwElm->u.pjMngmt.t.ssta));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
   RETVALUE(ROK);
} /* kwAcHdlLpjStaCfm */

/**
@brief Callback for Command Status Indication
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjStaInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   Pst      pst;
   S16      ret=ROK;

   TRC2(kwAcHdlLpjStaInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjStaInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjStaInd(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_STA_IND;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlKwStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);

   /* Verify status */
   ret = kwAcUtlPjVerifyStaInd(tcCb, spCb, &(kwElm->u.pjMngmt.t.usta));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStaInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ret);
} /* kwAcHdlLpjStaInd */

/**
@brief Callback for Command Trace Indication
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjTrcInd 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjTrcInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   Pst      pst;
   S16      ret=ROK;

   TRC2(kwAcHdlLpjTrcInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjTrcInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjTrcInd(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwTrcInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_TRC_IND;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlKwTrcInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);

   /* Handle Trace Indication */
   ret = kwAcUtlPjVerifyTrcInd(tcCb, spCb, &(kwElm->u.pjMngmt.t.trc));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwTrcInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ret);
} /* kwAcHdlLpjTrcInd */

#ifdef LTE_L2_MEAS

/* kw005.201 added support for L2 Measurement */
/**
@brief Call handler for command for L2 MeasReq
@param tcCb
@param spCb
@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjL2MeasReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlLpjL2MeasReq(tcCb,spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   PjL2MeasReqEvt l2MeasEvt;
   Pst pst;

   CmXtaTxnCb* txnCb;
   TRC2(kwAcHdlLpjL2MeasReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjL2MeasReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjL2MeasReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&l2MeasEvt, sizeof(PjL2MeasReqEvt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_L2MEAS_REQ ;

   kwAcUtlLpjBuildL2MeasReq(tcCb, spCb, &l2MeasEvt);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
   
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending L2Measurement request to PDCP\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjL2MeasReq(&pst, &l2MeasEvt);

   RETVALUE(ROK);
} /* kwAcHdlLpjL2MeasReq */

/**
@brief Callback for Command for L2 Measurement confirm
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpjL2MeasCfm
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpjL2MeasCfm(tcCb,spCb)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;   
   CmStatus       status;
   Pst            pst;
   S16            ret;

   TRC2(kwAcHdlLpjL2MeasCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjL2MeasCfm(): tcId (%ld)\n", tcCb->tcId));  
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpjL2MeasCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   kwElm = NULLP;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlLpjL2MeasCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_L2MEAS_CFM;
   
   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlLpjL2MeasCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the qElm from the Queue --*/
   if (cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlLpjL2MeasCfm() : cmXtaPopMsg Failed.\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   kwElm = (KwAcMsgQElm *)qElm->data;

   ret   =  kwAcUtlLpjVldtL2MeasCfm(tcCb, spCb, &kwElm->u.pjMeasCfmEvt);

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlLpjL2MeasCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ROK);

} /* kwAcHdlLpjL2MeasCfm */
#endif
#endif /* KW_PDCP */

/********************************************************************30**

         End of file:     kwac_lpjhdl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:34 2014

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
/main/1      ---   gk         1. LTERLC Release 2.1.
/main/2     kw005.201 ap      1. Passing spId for pjuSapSts.
                              2. Added support for L2 Measurement
*********************************************************************91*/


