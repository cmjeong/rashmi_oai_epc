

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_lpkhdl.c

     Sid:      pjac_lpkhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:02 2015

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
#include "kwu.h"           /* KWU defines */
#include "pju.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpk.h"           /* LPK defines */
#include "lpj.h"           /* LPK defines */
#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */
#include "pk.h"            /* RLC defines */

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_lpk.h"      /* CKW Acceptance defines */

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
#include "pju.x"           /* KWU */
#include "rgu.x"           /* RGU */
#include "cpj.x"           /* CPJ */
#include "lpk.x"           /* LPK */
#include "lpj.x"           /* LPK */
#include "kw.x"
#include "pk.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_lpk.x"      /* CKW Acceptance defines */


/* Venki */
#ifndef KW_PDCP
/*
*
*       Fun:   kwAcHdlLpkDirective
*
*       Desc:  Call handler for Command Indication 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  kwac_lpkhdl.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkDirective
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkDirective(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Bool  posTc =  FALSE;
   Bool  negTc =  FALSE;
   TRC2(kwAcHdlLpkDirective)


#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkDirective(): tcCb (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkDirective(): tcCb (%d)\n", tcCb->tcId));
#endif


   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "successTc", &posTc);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "failureTc", &negTc); 

   if(posTc)
      kwAcCb.directive.numPosTc++;
   if(negTc)
      kwAcCb.directive.numNegTc++;

   RETVALUE(CMXTA_ERR_NONE);
}/* kwAcHdlLpkDirective */

/**
@brief Call handler for command general configuration
@param tcCb
@param spCb
@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkGenCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkGenCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PkMngmt cfg;
   Pst pst;

   CmXtaTxnCb* txnCb;
   TRC2(kwAcHdlLpkGenCfgReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkGenCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkGenCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cfg, sizeof(PkMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPK_EVT_CFG_REQ;

   kwAcUtlPkBuildGenCfgReq(tcCb, spCb, &cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTPK, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending General Configuration request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpkCfgReq(&pst, &cfg);

   RETVALUE(ROK);
} /* kwAcHdlLpkGenCfgReq */

/**
@brief Call handler for Command Sap configuration Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkSapCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkSapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PkMngmt cfg;
   Pst pst;
   CmXtaTxnCb* txnCb;
   U8   elmnt = 0;

   TRC2(kwAcHdlLpkSapCfgReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cfg, sizeof(PkMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));


   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPK_EVT_CFG_REQ;

   /* Possible values for elmnt : STKWUSAP, STCKWSAP, STRGUSAP, STCPJSAP, STLOWERCPJSAP, STUPPERCPJSAP*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "elmnt", &(elmnt));
   cfg.hdr.elmId.elmnt = elmnt;

   kwAcUtlPkBuildSapCfgReq(tcCb, spCb, &cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTPK, CMXTA_INST_ID, cfg.hdr.elmId.elmnt, pst.selector);


   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Sap Configuration request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpkCfgReq(&pst, &cfg);

   RETVALUE(ROK);
} /* kwAcHdlLpkSapCfgReq */


/**
@brief Call handler for Command Trace Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkTrcCntrlReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PkMngmt  cntrl;
   Pst      pst;
   U16      isEnable = 0;
   /* Venki */
   Inst pkInst;

   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLpkTrcCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PkMngmt));
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

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pkInst));

   /* Venki */
   /*cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, pkInst, 0, 0, FALSE);
   pst.event = LPK_EVT_CNTRL_REQ;


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPK, pkInst, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trace Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpkCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* kwAcHdlLpkTrcCntrlReq */

/**
@brief Call handler for Command USta Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkUStaCntrlReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkUStaCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PkMngmt  cntrl;
   Pst      pst;
   U16      isEnable = 0;
   /* Venki */
   Inst pkInst;

   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLpkUStaCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkUStaCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkUStaCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PkMngmt));
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

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pkInst));
   /*cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, pkInst, 0, 0, FALSE);
   pst.event = LPK_EVT_CNTRL_REQ;


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPK, pkInst, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trace Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpkCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* kwAcHdlLpkUStaCntrlReq */

/**
@brief Call handler for Command Shutdown Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkSDCntrlReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkSDCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PkMngmt  cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLpkSDCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkSDCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkSDCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PkMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPK_EVT_CNTRL_REQ;

  /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   kwAcUtlPkBuildSDCntrlReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPK, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Shutdown Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpkCntrlReq(&pst, &cntrl);


/* ################################################################################  */

/* Venki - added to cleanup PDCP-UL */   

/*################################################################################## */

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkSDCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkSDCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PkMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, CMXTA_INST_ID+1, 0, 0, FALSE);
   pst.event = LPK_EVT_CNTRL_REQ;

   /*-- Fill the data structure here, even the parameters which
     needs to be changed from XML --*/
   kwAcUtlPkBuildSDCntrlReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
       RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPK, CMXTA_INST_ID+1, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Shutdown Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpkCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* kwAcHdlLpkSDCntrlReq */


/**
@brief Call handler for Command Debug Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkDbgCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkDbgCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PkMngmt  cntrl;
   Pst      pst;
   U16      isEnable = 0;
   /* Venki */
   Inst pkInst;
   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLpkDbgCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkDbgCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkDbgCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PkMngmt));
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
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pkInst));

   /* Venki */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, pkInst, 0, 0, FALSE);
   pst.event = LPK_EVT_CNTRL_REQ;

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   /*(Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPK, CMXTA_INST_ID, STGEN, pst.selector);*/
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPK, pkInst, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Debug Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpkCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* kwAcHdlLpkDbgCntrlReq */


/**
@brief Call handler for Command Statistics Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkStsReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PkMngmt  sts;
   Pst      pst;
   Action  action;         /* zeroing action */
   CmXtaTxnCb* txnCb;
   U16      elmnt;

   TRC2(kwAcHdlLpkStsReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkStsReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkStsReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&sts, sizeof(PkMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   elmnt = 0;

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPK_EVT_STS_REQ;

   action = ZEROSTS;
   /* read from xml    */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "action",  &action);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "elmnt",  &elmnt);
   /* kw005.201 passing spId for pkuSapSts */
   if(elmnt == STCPJSAP)
   {
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "spId",  &sts.t.sts.s.cpjSap.spId);
   }


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, ENTPK, CMXTA_INST_ID, elmnt, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Statistics request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpkStsReq(&pst, action, &sts);

   RETVALUE(ROK);
} /* kwAcHdlLpkStsReq */


/**
@brief Call handler for Command Status Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PkMngmt     sta;
   Pst         pst;
   Action      action;         /* zeroing action */
   CmXtaTxnCb* txnCb;
   U16         elmnt;

   TRC2(kwAcHdlLpkStaReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkStaReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkStaReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&sta, sizeof(PkMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   elmnt  = 0;

   /* Venki */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, CMXTA_INST_ID+1, 0, 0, FALSE);
   pst.event = LPK_EVT_STA_REQ;

   action = ZEROSTS;

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "elmnt",  &elmnt);
   /* Prepare header */
   (Void) cmXtaInitHdr(&(sta.hdr), txnCb->txnId, ENTPK, CMXTA_INST_ID, elmnt, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Statistics request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpkStaReq(&pst, &sta);

   RETVALUE(ROK);
} /* kwAcHdlLpkStaReq */


/**
@brief Callback for Command Configuration Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;   
   CmStatus       status;
   Pst            pst;
   S16            ret;

   TRC2(kwAcHdlLpkCfgCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkCfgCfm(): tcId (%ld)\n", tcCb->tcId));  
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkCfgCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   kwElm = NULLP;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlLpkCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   

   cmXtaGetPst(&pst, ENTPK, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPK_EVT_CFG_CFM;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlLpkCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the qElm from the Queue --*/
   if (cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlLpkCfgCfm() : cmXtaPopMsg Failed.\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   kwElm = (KwAcMsgQElm *)qElm->data;

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(kwElm->u.pkMngmt.cfm));
      
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlLpkCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ROK);

} /* kwAcHdlLpkCfgCfm */

/**
@brief Callback for Command Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkCntrlCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkCntrlCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(kwAcHdlLpkCntrlCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkCntrlCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkCntrlCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwCntrlCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;
   
   cmXtaGetPst(&pst, ENTPK, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPK_EVT_CNTRL_CFM;

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
   ret= cmXtaValidateStatus(&status, &(kwElm->u.pkMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwCntrlCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
   RETVALUE(ROK);
} /* kwAcHdlLpkCntrlCfm */

/**
@brief Callback for Command Statistics request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkStsCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkStsCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(kwAcHdlLpkStsCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkStsCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkStsCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwStsCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPK, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPK_EVT_STS_CFM;

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
   ret= cmXtaValidateStatus(&status, &(kwElm->u.pkMngmt.cfm));
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStsCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Verify statistics */
   ret = kwAcUtlPkVerifyStsCfm(tcCb, spCb, &(kwElm->u.pkMngmt.t.sts));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStsCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ROK);
} /* kwAcHdlLpkStsCfm */

/**
@brief Callback for Command Status request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkStaCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(kwAcHdlLpkStaCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkStaCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkStaCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwStaCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPK, CMXTA_INST_ID+1, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPK_EVT_STA_CFM;

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
   ret= cmXtaValidateStatus(&status, &(kwElm->u.pkMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Verify status */
   ret = kwAcUtlPkVerifyStaCfm(tcCb, spCb, &(kwElm->u.pkMngmt.t.ssta));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
   RETVALUE(ROK);
} /* kwAcHdlLpkStaCfm */

/**
@brief Callback for Command Status Indication
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkStaInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   Pst      pst;
   S16      ret=ROK;


   TRC2(kwAcHdlLpkStaInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkStaInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkStaInd(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   cmXtaGetPst(&pst, ENTPK, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPK_EVT_STA_IND;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlPkStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);

   /* Verify status */
   ret = kwAcUtlPkVerifyStaInd(tcCb, spCb, &(kwElm->u.pkMngmt.t.usta));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlPkStaInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ret);
} /* kwAcHdlLpkStaInd */

/**
@brief Callback for Command Trace Indication
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkTrcInd 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkTrcInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   Pst      pst;
   S16      ret=ROK;

   TRC2(kwAcHdlLpkTrcInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkTrcInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkTrcInd(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwTrcInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   cmXtaGetPst(&pst, ENTPK, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPK_EVT_TRC_IND;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlKwTrcInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);

   /* Handle Trace Indication */
   ret = kwAcUtlPkVerifyTrcInd(tcCb, spCb, &(kwElm->u.pkMngmt.t.trc));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwTrcInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ret);
} /* kwAcHdlLpkTrcInd */
/**
@brief Call handler for Command Sap Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkSapCntrlReq(tcCb,spCb)

SapCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PkMngmt  cntrl;
   Pst      pst;
   U8      elmnt = 0;
   Inst    pkInst = 0; 
   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLpkSapCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkSapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkSapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PkMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pkInst));

   /*cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, CMXTA_INST_ID, 0, 0, FALSE);

   pst.event = LKW_EVT_CNTRL_REQ;

  /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   kwAcUtlPkBuildSapCntrlReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Possible values for elmnt are: STGEN and STRGUSAP */
   elmnt = STGEN;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "elmnt",
         &(elmnt));

   /* Prepare header */
   /*(Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTKW, CMXTA_INST_ID, (S16)elmnt, pst.selector);*/
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPK, CMXTA_INST_ID, (S16)elmnt, pst.selector);
   
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Sap Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpkCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
}/* kwAcHdlLpkSapCntrlReq */

#ifdef LTE_L2_MEAS

/* kw005.201 added support for L2 Measurement */
/**
@brief Call handler for command for L2 MeasReq
@param tcCb
@param spCb
@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkL2MeasReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlLpkL2MeasReq(tcCb,spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   PkL2MeasReqEvt l2MeasEvt;
   Pst pst;

   CmXtaTxnCb* txnCb;
   TRC2(kwAcHdlLpkL2MeasReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkL2MeasReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkL2MeasReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&l2MeasEvt, sizeof(PkL2MeasReqEvt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPK, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPK_EVT_L2MEAS_REQ ;

   kwAcUtlLpkBuildL2MeasReq(tcCb, spCb, &l2MeasEvt);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
   
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending L2Measurement request to PDCP\n"));

   /* Send the request to the LM */
   (Void) SmMiLpkL2MeasReq(&pst, &l2MeasEvt);

   RETVALUE(ROK);
} /* kwAcHdlLpkL2MeasReq */

/**
@brief Callback for Command for L2 Measurement confirm
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLpkL2MeasCfm
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLpkL2MeasCfm(tcCb,spCb)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;   
   CmStatus       status;
   Pst            pst;
   S16            ret;

   TRC2(kwAcHdlLpkL2MeasCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkL2MeasCfm(): tcId (%ld)\n", tcCb->tcId));  
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLpkL2MeasCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   kwElm = NULLP;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlLpkL2MeasCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   cmXtaGetPst(&pst, ENTPK, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPK_EVT_L2MEAS_CFM;
   
   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlLpkL2MeasCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the qElm from the Queue --*/
   if (cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlLpkL2MeasCfm() : cmXtaPopMsg Failed.\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   kwElm = (KwAcMsgQElm *)qElm->data;

   ret   =  kwAcUtlLpkVldtL2MeasCfm(tcCb, spCb, &kwElm->u.pkMeasCfmEvt);

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlLpkL2MeasCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ROK);

} /* kwAcHdlLpkL2MeasCfm */
#endif
#endif /* KW_PDCP */

/********************************************************************30**

         End of file:     pjac_lpkhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:02 2015

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
/main/1      ---      vb      1. LTE PDCP Release 2.1.
*********************************************************************91*/

