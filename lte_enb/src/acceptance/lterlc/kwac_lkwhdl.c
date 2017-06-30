

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_lkwhdl.c

     Sid:      kwac_lkwhdl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:32 2014

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
#include "kwac_lkw.h"      /* CKW Acceptance defines */

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
#include "kwac_lkw.x"      /* CKW Acceptance defines */

/**
@brief Call handler for command general configuration
@param tcCb
@param spCb
@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwGenCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwGenCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   KwMngmt cfg;
   Pst pst;
   Inst kwInst;

   CmXtaTxnCb* txnCb;
   TRC2(kwAcHdlLkwGenCfgReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwGenCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwGenCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cfg, sizeof(KwMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

/*Pradeep - start. Read the "inst" value for ENTKW*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(kwInst));
/*
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);
   */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
/*Pradeep - end*/

   pst.event = LKW_EVT_CFG_REQ;

   kwAcUtlKwBuildGenCfgReq(tcCb, spCb, &cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
/*Pradeep -start*/   
   /*(Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTKW, CMXTA_INST_ID, STGEN, 
   pst.selector);*/
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTKW, kwInst, STGEN, pst.selector);
/*Pradeep - end*/

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending General Configuration request\n"));

   /* Send the request to the LM */
   (Void) SmMiLkwCfgReq(&pst, &cfg);

   RETVALUE(ROK);
} /* kwAcHdlLkwGenCfgReq */

/**
@brief Call handler for Command Sap configuration Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwSapCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwSapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   KwMngmt cfg;
   Pst pst;
   CmXtaTxnCb* txnCb;
   U8   elmnt = 0;
   Inst kwInst = 0;

   TRC2(kwAcHdlLkwSapCfgReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cfg, sizeof(KwMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   
/*Pradeep - start. Read the "inst" value for ENTKW*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(kwInst));

   /*cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
/*Pradeep - end*/

   pst.event = LKW_EVT_CFG_REQ;

   /* Possible values for elmnt : STKWUSAP, STCKWSAP, STRGUSAP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "elmnt", &(elmnt));
   cfg.hdr.elmId.elmnt = elmnt;

   kwAcUtlKwBuildSapCfgReq(tcCb, spCb, &cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

/*Pradeep - start*/
   /* Prepare header */
   /*(Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTKW, CMXTA_INST_ID, cfg.hdr.elmId.elmnt, pst.selector);*/
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTKW, kwInst, cfg.hdr.elmId.elmnt, pst.selector);
/*Pradeep - end*/

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Sap Configuration request\n"));

   /* Send the request to the LM */
   (Void) SmMiLkwCfgReq(&pst, &cfg);

   RETVALUE(ROK);
} /* kwAcHdlLkwSapCfgReq */


/**
@brief Call handler for Command Trace Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwTrcCntrlReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   KwMngmt  cntrl;
   Pst      pst;
   U16      isEnable = 0;
   /*Pradeep - start*/
   Inst     kwInst = 0;
   /*Pradeep - end*/
 
   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLkwTrcCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(KwMngmt));
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

   /*Pradeep - start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
   /*cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
   /*Pradeep - end*/

   pst.event = LKW_EVT_CNTRL_REQ;


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   /*Pradeep - start*/
   /*(Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTKW, CMXTA_INST_ID, STGEN, pst.selector);*/   
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTKW, kwInst, STGEN, pst.selector);
   /*Pradeep - end*/

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trace Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLkwCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* kwAcHdlLkwTrcCntrlReq */

/**
@brief Call handler for Command USta Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwUStaCntrlReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwUStaCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   KwMngmt  cntrl;
   Pst      pst;
   U16      isEnable = 0;
   /*Pradeep - start*/
   Inst     kwInst = 0;
   /*Pradeep - end*/
   
   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLkwUStaCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwUStaCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwUStaCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(KwMngmt));
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

   /*Pradeep - start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &kwInst);
   /*cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
   /*Pradeep - end*/
   
   pst.event = LKW_EVT_CNTRL_REQ;


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   /*Pradeep - start*/
   /*(Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTKW, CMXTA_INST_ID, STGEN, pst.selector);*/
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTKW, kwInst, STGEN, pst.selector);
   /*Pradeep - end*/
   
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trace Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLkwCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* kwAcHdlLkwUStaCntrlReq */

/**
@brief Call handler for Command Shutdown Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwSDCntrlReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwSDCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   KwMngmt  cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLkwSDCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwSDCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwSDCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(KwMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LKW_EVT_CNTRL_REQ;

  /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   kwAcUtlKwBuildSDCntrlReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTKW, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Shutdown Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLkwCntrlReq(&pst, &cntrl);
   /******************************************************************************/

/*Pradeep - start. added to cleanup RLC-UL*/
   /********************************* RLC-UL *************************************/
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwSDCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwSDCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(KwMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID+1, 0, 0, FALSE);
   pst.event = LKW_EVT_CNTRL_REQ;

  /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   kwAcUtlKwBuildSDCntrlReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTKW, CMXTA_INST_ID+1, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Shutdown Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLkwCntrlReq(&pst, &cntrl);
   /******************************************************************************/
/*Pradeep - end*/
   RETVALUE(ROK);
} /* kwAcHdlLkwSDCntrlReq */


/**

@brief Call handler for Command Debug Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwDbgCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwDbgCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   KwMngmt  cntrl;
   Pst      pst;
   U16      isEnable = 0;
   /*Pradeep - start*/
   Inst     kwInst = 0;
   /*Pradeep - end*/
   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLkwDbgCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwDbgCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwDbgCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(KwMngmt));
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
   
/*Pradeep -start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "inst",  &kwInst);
   /*cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
/*Pradeep -end*/

   pst.event = LKW_EVT_CNTRL_REQ;

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
/*Pradeep -start*/   
   /*(Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTKW, CMXTA_INST_ID, STGEN, pst.selector);*/
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTKW, kwInst, STGEN, pst.selector);
/*Pradeep -end*/

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Debug Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLkwCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* kwAcHdlLkwDbgCntrlReq */

/**
@brief Call handler for Command Sap Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwSapCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   KwMngmt  cntrl;
   Pst      pst;
   U8      elmnt = 0;
   Inst    kwInst = 0; 
   CmXtaTxnCb* txnCb;

   TRC2(kwAcHdlLkwSapCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwSapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwSapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(KwMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

/*Pradeep - start*/  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(kwInst));

   /*cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
/*Pradeep - end*/

   pst.event = LKW_EVT_CNTRL_REQ;

  /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   kwAcUtlKwBuildSapCntrlReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Possible values for elmnt are: STGEN and STRGUSAP */
   elmnt = STGEN;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "elmnt",
         &(elmnt));

   /* Prepare header */
   /*Pradeep - start*/
   /*(Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTKW, CMXTA_INST_ID, (S16)elmnt, pst.selector);*/
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTKW, kwInst, (S16)elmnt, pst.selector);
   /*Pradeep - end*/
   
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Sap Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLkwCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* kwAcHdlLkwSapCntrlReq */


/**
@brief Call handler for Command Statistics Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwStsReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   KwMngmt  sts;
   Pst      pst;
   Action  action;         /* zeroing action */
   CmXtaTxnCb* txnCb;
   U16      elmnt;
/*Pradeep - start*/   
   Inst     kwInst;
/*Pradeep - end*/

   TRC2(kwAcHdlLkwStsReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwStsReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwStsReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&sts, sizeof(KwMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   elmnt = 0;

/*Pradeep - start 8May*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "inst",  &kwInst);
   /*cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID+1, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
/*Pradeep - end*/
   pst.event = LKW_EVT_STS_REQ;

   action = ZEROSTS;
   /* read from xml    */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "action",  &action);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "elmnt",  &elmnt);
   /* kw005.201, modified the element of kwuSap from suId to spId */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "spId",  &(sts.t.sts.s.kwuSap.spId));


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   /*Pradeep - start 8May*/
   /*(Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, ENTKW, CMXTA_INST_ID+1, elmnt, pst.selector);*/
   (Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, ENTKW, kwInst, elmnt, pst.selector);
   /*Pradeep - end*/
   
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Statistics request\n"));

   /* Send the request to the LM */
   (Void) SmMiLkwStsReq(&pst, action, &sts);

   RETVALUE(ROK);
} /* kwAcHdlLkwStsReq */


/**
@brief Call handler for Command Status Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   KwMngmt     sta;
   Pst         pst;
   Action      action;         /* zeroing action */
   CmXtaTxnCb* txnCb;
   U16         elmnt;
   Inst        kwInst;

   TRC2(kwAcHdlLkwStaReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwStaReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwStaReq(): tcId (%d)\n", tcCb->tcId));
#endif

   CMXTA_ZERO(&sta, sizeof(KwMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   elmnt  = 0;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(kwInst));
   
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, kwInst, 0, 0, FALSE);
   pst.event = LKW_EVT_STA_REQ;

   action = ZEROSTS;

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "elmnt",  &elmnt);
   /* Prepare header */
   (Void) cmXtaInitHdr(&(sta.hdr), txnCb->txnId, ENTKW, kwInst , elmnt, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Statistics request\n"));

   /* Send the request to the LM */
   (Void) SmMiLkwStaReq(&pst, &sta);

   RETVALUE(ROK);
} /* kwAcHdlLkwStaReq */


/**
@brief Callback for Command Configuration Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;   
   CmStatus       status;
   Pst            pst;
   S16            ret;
   Inst           kwInst = 0;

   TRC2(kwAcHdlLkwCfgCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwCfgCfm(): tcId (%ld)\n", tcCb->tcId));  
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwCfgCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   kwElm = NULLP;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlLkwCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
/*Pradeep -start*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
   /*cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTKW, kwInst, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
/*Pradeep -end*/

   pst.event = LKW_EVT_CFG_CFM;
   
   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlLkwCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the qElm from the Queue --*/
   if (cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlLkwCfgCfm() : cmXtaPopMsg Failed.\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   kwElm = (KwAcMsgQElm *)qElm->data;

   /*-- Validate return value and reason --*/
   ret= cmXtaValidateStatus(&status, &(kwElm->u.kwMngmt.cfm));
      
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlLkwCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ROK);

} /* kwAcHdlLkwCfgCfm */

/**
@brief Callback for Command Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwCntrlCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwCntrlCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   CmStatus       status;
   Pst      pst;
   S16      ret;
/*Pradeep - start*/
   Inst     kwInst;
/*Pradeep - end*/

   TRC2(kwAcHdlLkwCntrlCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwCntrlCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwCntrlCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwCntrlCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

/*Pradeep - start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",&kwInst);
   /*cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTKW, kwInst, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
/*Pradeep - end*/

   pst.event = LKW_EVT_CNTRL_CFM;

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
   ret= cmXtaValidateStatus(&status, &(kwElm->u.kwMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwCntrlCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
   RETVALUE(ROK);
} /* kwAcHdlLkwCntrlCfm */

/**
@brief Callback for Command Statistics request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwStsCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwStsCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   Inst kwInst;
   U8       validType = 0;

   TRC2(kwAcHdlLkwStsCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwStsCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwStsCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwStsCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));/*
   Venki */
   /*Pradeep - 8May*/ 
   cmXtaGetPst(&pst, ENTKW, kwInst, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   /*cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID+1, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);*/
   pst.event = LKW_EVT_STS_CFM;
   /* Venki - validType added */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "validType", &(validType));
   

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
   ret= cmXtaValidateStatus(&status, &(kwElm->u.kwMngmt.cfm));
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStsCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Venki -  validType added */
   /* Verify statistics */
   if(!validType)
   {
        ret = kwAcUtlKwVerifyStsCfm(tcCb, spCb, &(kwElm->u.kwMngmt.t.sts));
        if(ret != ROK)
        {
            CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStsCfm() : result mismatch\n"));
            cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
            RETVALUE(CMXTA_ERR_INT);
        }
    }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ROK);
} /* kwAcHdlLkwStsCfm */

/**
@brief Callback for Command Status request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwStaCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   Inst     kwInst;

   TRC2(kwAcHdlLkwStaCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwStaCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwStaCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwStaCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(kwInst));
   cmXtaGetPst(&pst, ENTKW, kwInst, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LKW_EVT_STA_CFM;

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
   ret= cmXtaValidateStatus(&status, &(kwElm->u.kwMngmt.cfm));

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Verify status */
   ret = kwAcUtlKwVerifyStaCfm(tcCb, spCb, &(kwElm->u.kwMngmt.t.ssta));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
   RETVALUE(ROK);
} /* kwAcHdlLkwStaCfm */

/**
@brief Callback for Command Status Indication
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwStaInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   Pst      pst;
   S16      ret=ROK;
   /*Pradeep -sart*/
   Inst     kwInst = 0;
   /*Pradeep -end*/
   
   TRC2(kwAcHdlLkwStaInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwStaInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwStaInd(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   /*Pradeep -sart*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &kwInst);
   /*cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTKW, kwInst, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   /*Pradeep -end*/
   
   pst.event = LKW_EVT_STA_IND;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlKwStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);

   /* Verify status */
   ret = kwAcUtlKwVerifyStaInd(tcCb, spCb, &(kwElm->u.kwMngmt.t.usta));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwStaInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ret);
} /* kwAcHdlLkwStaInd */

/**
@brief Callback for Command Trace Indication
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwTrcInd 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwTrcInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   Pst      pst;
   S16      ret=ROK;
   Inst     kwInst;

   TRC2(kwAcHdlLkwTrcInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwTrcInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlKwTrcInd(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlKwTrcInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
/* Vemki - fixing here */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));

   cmXtaGetPst(&pst, ENTKW, kwInst, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LKW_EVT_TRC_IND;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlKwTrcInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);

   /* Handle Trace Indication */
   ret = kwAcUtlKwVerifyTrcInd(tcCb, spCb, &(kwElm->u.kwMngmt.t.trc));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlKwTrcInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ret);
} /* kwAcHdlLkwTrcInd */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS

/**
@brief Call handler for command for L2 MeasReq
@param tcCb
@param spCb
@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwL2MeasReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 kwAcHdlLkwL2MeasReq(tcCb,spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   KwL2MeasReqEvt  l2MeasEvt;
   Pst pst;

   CmXtaTxnCb* txnCb;
   TRC2(kwAcHdlLkwL2MeasReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwL2MeasReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwL2MeasReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&l2MeasEvt, sizeof(KwL2MeasReqEvt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   /* AGHOSH commented, using instatnce as 1 for UL RLC, should be changed later 
    * cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, CMXTA_INST_ID, 0, 0, FALSE); */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTKW, 1, 0, 0, FALSE);
   pst.event = LKW_EVT_L2MEAS_REQ ;

   kwAcUtlLkwBuildL2MeasReq(tcCb, spCb, &l2MeasEvt);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending L2Measurement request to RLC\n"));

   /* Send the request to the LM */
   (Void) SmMiLkwL2MeasReq(&pst, &l2MeasEvt);

   RETVALUE(ROK);
} /* kwAcHdlLkwL2MeasReq */

/**
@brief Callback for Command for L2 Measurement confirm
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcHdlLkwL2MeasCfm
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 kwAcHdlLkwL2MeasCfm(tcCb,spCb)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;   
   CmStatus       status;
   Pst            pst;
   S16            ret;

   TRC2(kwAcHdlLkwL2MeasCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwL2MeasCfm(): tcId (%ld)\n", tcCb->tcId));  
#else
   CMXTA_DBG_PARAM((_cmxtap, "kwAcHdlLkwL2MeasCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   kwElm = NULLP;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "kwAcHdlLkwL2MeasCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LKW_EVT_L2MEAS_CFM ;
   
   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlLkwL2MeasCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the qElm from the Queue --*/
   if (cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "kwAcHdlLkwL2MeasCfm() : cmXtaPopMsg Failed.\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   kwElm = (KwAcMsgQElm *)qElm->data;

   ret   =  kwAcUtlLkwVldtL2MeasCfm(tcCb, spCb, &kwElm->u.kwMeasCfmEvt);

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcHdlLkwL2MeasCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ROK);

} /* kwAcHdlLkwL2MeasCfm */
#endif


/********************************************************************30**

         End of file:     kwac_lkwhdl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:32 2014

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
/main/2      ---   gk         1. LTE RLC Release 2.1
/main/3      kw005.201 ap     1. Modified the element of kwuSap from suId to spId.
                              2. Added support for L2 measurement.
*********************************************************************91*/


