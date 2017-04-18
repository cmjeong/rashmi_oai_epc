

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_lpjhdl.c

     Sid:      pjac_lpjhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:58 2015

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
#include "pjac_lpj.h"      /* CKW Acceptance defines */

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
#include "pjac_lpj.x"      /* CKW Acceptance defines */


/*
*
*       Fun:   pjAcHdlLpjDirective
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
PUBLIC S16 pjAcHdlLpjDirective
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjDirective(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   Bool  posTc =  FALSE;
   Bool  negTc =  FALSE;
   TRC2(pjAcHdlLpjDirective)


#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjDirective(): tcCb (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjDirective(): tcCb (%d)\n", tcCb->tcId));
#endif


   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "successTc", &posTc);
   cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_BOOL, "failureTc", &negTc); 

   if(posTc)
      kwAcCb.directive.numPosTc++;
   if(negTc)
      kwAcCb.directive.numNegTc++;

   RETVALUE(CMXTA_ERR_NONE);
}/* pjAcHdlLpjDirective */

/**
@brief Call handler for command general configuration
@param tcCb
@param spCb
@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjGenCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjGenCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt cfg;
   Pst pst;
   Inst pjInst = 0;

   CmXtaTxnCb* txnCb;
   TRC2(pjAcHdlLpjGenCfgReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjGenCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjGenCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cfg, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));
   
   /*cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
    * */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, pjInst, 0, 0, FALSE);
   pst.event = LPJ_EVT_CFG_REQ;

   pjAcUtlPjBuildGenCfgReq(tcCb, spCb, &cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   /*(Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID, STGEN,
    * pst.selector);*/

   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTPJ, pjInst, STGEN, pst.selector);


   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending General Configuration request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCfgReq(&pst, &cfg);

   RETVALUE(ROK);
} /* pjAcHdlLpjGenCfgReq */

/**
@brief Call handler for Command Sap configuration Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjSapCfgReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjSapCfgReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt cfg;
   Pst pst;
   CmXtaTxnCb* txnCb;
   U8   elmnt = 0;
   Inst pjInst = 0;

   TRC2(pjAcHdlLpjSapCfgReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjSapCfgReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjSapCfgReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cfg, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, pjInst, 0, 0, FALSE);
   pst.event = LPJ_EVT_CFG_REQ;

   /* Possible values for elmnt : STKWUSAP, STCKWSAP, STRGUSAP */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "elmnt", &(elmnt));
   cfg.hdr.elmId.elmnt = elmnt;

   pjAcUtlPjBuildSapCfgReq(tcCb, spCb, &cfg);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   /*(Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID,
    * cfg.hdr.elmId.elmnt, pst.selector);*/
   /* venki */
   (Void) cmXtaInitHdr(&(cfg.hdr), txnCb->txnId, ENTPJ, pjInst, cfg.hdr.elmId.elmnt, pst.selector);


   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Sap Configuration request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCfgReq(&pst, &cfg);

   RETVALUE(ROK);
} /* pjAcHdlLpjSapCfgReq */


/**
@brief Call handler for Command Trace Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjTrcCntrlReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjTrcCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt  cntrl;
   Pst      pst;
   U16      isEnable = 0;
   /* Venki */
   Inst pjInst = 0;

   CmXtaTxnCb* txnCb;

   TRC2(pjAcHdlLpjTrcCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjTrcCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjTrcCntrlReq(): tcId (%d)\n", tcCb->tcId));
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

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   /* Venki */
   /*cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, pjInst, 0, 0, FALSE);
   pst.event = LPJ_EVT_CNTRL_REQ;


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPJ, pjInst, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trace Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* pjAcHdlLpjTrcCntrlReq */

/**
@brief Call handler for Command USta Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjUStaCntrlReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjUStaCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt  cntrl;
   Pst      pst;
   U16      isEnable = 0;
   /* Venki */
   Inst pjInst = 0;

   CmXtaTxnCb* txnCb;

   TRC2(pjAcHdlLpjUStaCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjUStaCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjUStaCntrlReq(): tcId (%d)\n", tcCb->tcId));
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

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));
   /*cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, pjInst, 0, 0, FALSE);
   pst.event = LPJ_EVT_CNTRL_REQ;


   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPJ, pjInst, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Trace Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* pjAcHdlLpjUStaCntrlReq */

/**
@brief Call handler for Command Shutdown Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjSDCntrlReq 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjSDCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt  cntrl;
   Pst      pst;

   CmXtaTxnCb* txnCb;

   TRC2(pjAcHdlLpjSDCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjSDCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjSDCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_CNTRL_REQ;

  /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   pjAcUtlPjBuildSDCntrlReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Shutdown Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCntrlReq(&pst, &cntrl);


/* ################################################################################  */

/* Cleanup PDCP-UL */   

/*################################################################################## */

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjSDCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjSDCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
   pst.event = LPJ_EVT_CNTRL_REQ;

   /*-- Fill the data structure here, even the parameters which
     needs to be changed from XML --*/
   pjAcUtlPjBuildSDCntrlReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
       RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID+1, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Shutdown Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* pjAcHdlLpjSDCntrlReq */


/**
@brief Call handler for Command Debug Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjDbgCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjDbgCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt  cntrl;
   Pst      pst;
   U16      isEnable = 0;
   /* Venki */
   Inst pjInst = 0;
   CmXtaTxnCb* txnCb;

   TRC2(pjAcHdlLpjDbgCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjDbgCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjDbgCntrlReq(): tcId (%d)\n", tcCb->tcId));
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
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   /* Venki */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, pjInst, 0, 0, FALSE);
   pst.event = LPJ_EVT_CNTRL_REQ;

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Prepare header */
   /*(Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID, STGEN, pst.selector);*/
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPJ, pjInst, STGEN, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Debug Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
} /* pjAcHdlLpjDbgCntrlReq */


/**
@brief Call handler for Command Statistics Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjStsReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjStsReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt  sts;
   Pst      pst;
   Action  action;         /* zeroing action */
   CmXtaTxnCb* txnCb;
   U16      elmnt;
   /* Venki */
   Inst pjInst = 0;

   TRC2(pjAcHdlLpjStsReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjStsReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjStsReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&sts, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   elmnt = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   /* Venki */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, pjInst, 0, 0, FALSE);
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
   (Void) cmXtaInitHdr(&(sts.hdr), txnCb->txnId, ENTPJ, CMXTA_INST_ID+1, elmnt, pst.selector);

   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Statistics request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjStsReq(&pst, action, &sts);

   RETVALUE(ROK);
} /* pjAcHdlLpjStsReq */


/**
@brief Call handler for Command Status Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjStaReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt     sta;
   Pst         pst;
   Action      action;         /* zeroing action */
   CmXtaTxnCb* txnCb;
   U16         elmnt;

   TRC2(pjAcHdlLpjStaReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjStaReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjStaReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&sta, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));
   elmnt  = 0;

   /* Venki */
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID+1, 0, 0, FALSE);
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
} /* pjAcHdlLpjStaReq */


/**
@brief Callback for Command Configuration Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjCfgCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjCfgCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;   
   CmStatus       status;
   Pst            pst;
   S16            ret;
   Inst           pjInst = 0;

   TRC2(pjAcHdlLpjCfgCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjCfgCfm(): tcId (%ld)\n", tcCb->tcId));  
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjCfgCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   kwElm = NULLP;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlLpjCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   cmXtaGetPst(&pst, ENTPJ, pjInst, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_CFG_CFM;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "pjAcHdlLpjCfgCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the qElm from the Queue --*/
   if (cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "pjAcHdlLpjCfgCfm() : cmXtaPopMsg Failed.\n"));
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
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlLpjCfgCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ROK);

} /* pjAcHdlLpjCfgCfm */

/**
@brief Callback for Command Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjCntrlCfm 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjCntrlCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   Inst     pjInst = 0;

   TRC2(pjAcHdlLpjCntrlCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjCntrlCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjCntrlCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwCntrlCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));
   
   cmXtaGetPst(&pst, ENTPJ, pjInst, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_CNTRL_CFM;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlKwCntrlCfm() :  No Match, not for this Test Case\n"));
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
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlKwCntrlCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
   RETVALUE(ROK);
} /* pjAcHdlLpjCntrlCfm */

/**
@brief Callback for Command Statistics request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjStsCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjStsCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   CmStatus       status;
   Pst      pst;
   S16      ret;
   /* Venki */
   Inst pjInst = 0;

   TRC2(pjAcHdlLpjStsCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjStsCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjStsCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwStsCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;
   /* venki */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   /*cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);*/
   cmXtaGetPst(&pst, ENTPJ, pjInst, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_STS_CFM;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlKwStsCfm() : No Match, not for this test case\n"));
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
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlKwStsCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Verify statistics */
   ret = pjAcUtlPjVerifyStsCfm(tcCb, spCb, &(kwElm->u.pjMngmt.t.sts));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlKwStsCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ROK);
} /* pjAcHdlLpjStsCfm */

/**
@brief Callback for Command Status request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjStaCfm(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   CmStatus       status;
   Pst      pst;
   S16      ret;

   TRC2(pjAcHdlLpjStaCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjStaCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjStaCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwStaCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID+1, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_STA_CFM;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlKwStaCfm() : No match, not for this test case\n"));
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
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlKwStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Verify status */
   ret = pjAcUtlPjVerifyStaCfm(tcCb, spCb, &(kwElm->u.pjMngmt.t.ssta));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlKwStaCfm() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
   RETVALUE(ROK);
} /* pjAcHdlLpjStaCfm */

/**
@brief Callback for Command Status Indication
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjStaInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   Pst      pst;
   S16      ret=ROK;
   Inst     pjInst = 0;


   TRC2(pjAcHdlLpjStaInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjStaInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjStaInd(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwStaInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   cmXtaGetPst(&pst, ENTPJ, pjInst, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_STA_IND;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "pjAcHdlPjStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);

   /* Verify status */
   ret = pjAcUtlPjVerifyStaInd(tcCb, spCb, &(kwElm->u.pjMngmt.t.usta));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlPjStaInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ret);
} /* pjAcHdlLpjStaInd */

/**
@brief Callback for Command Trace Indication
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjTrcInd 
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjTrcInd(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;
   Pst      pst;
   Inst    pjInst = 0; 
   S16      ret=ROK;

   TRC2(pjAcHdlLpjTrcInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjTrcInd(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjTrcInd(): tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlKwTrcInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   cmXtaGetPst(&pst, ENTPJ, pjInst, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);

   pst.event = LPJ_EVT_TRC_IND;

   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "pjAcHdlKwTrcInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   kwElm = (KwAcMsgQElm *)qElm->data;

   cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm);

   /* Handle Trace Indication */
   ret = pjAcUtlPjVerifyTrcInd(tcCb, spCb, &(kwElm->u.pjMngmt.t.trc));
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlKwTrcInd() : result mismatch\n"));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ret);
} /* pjAcHdlLpjTrcInd */
/**
@brief Call handler for Command Sap Control Request
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjSapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjSapCntrlReq(tcCb,spCb)

SapCntrlReq(tcCb,spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
#endif
{
   PjMngmt  cntrl;
   Pst      pst;
   U8      elmnt = 0;
   Inst    pjInst = 0; 
   CmXtaTxnCb* txnCb;

   TRC2(pjAcHdlLpjSapCntrlReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjSapCntrlReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjSapCntrlReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&cntrl, sizeof(PjMngmt));
   CMXTA_ZERO(&pst, sizeof(Pst));

/*Pradeep - start*/  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pjInst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, pjInst, 0, 0, FALSE);
/*Pradeep - end*/

   pst.event = LPJ_EVT_CNTRL_REQ;

  /*-- Fill the data structure here, even the parameters which
        needs to be changed from XML --*/
   pjAcUtlPjBuildSapCntrlReq(tcCb, spCb, &cntrl);

   /*-- Create SM Txn Here and associate this tcCb with that --*/
   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Possible values for elmnt are: STGEN and STRGUSAP */
   elmnt = STGEN;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_FLAG, "elmnt",
         &(elmnt));

   /* Prepare header */
   (Void) cmXtaInitHdr(&(cntrl.hdr), txnCb->txnId, ENTPJ, pjInst, (S16)elmnt, pst.selector);
   
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending Sap Control Request\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjCntrlReq(&pst, &cntrl);

   RETVALUE(ROK);
}/* pjAcHdlLpjSapCntrlReq */

#ifdef LTE_L2_MEAS

/* kw005.201 added support for L2 Measurement */
/**
@brief Call handler for command for L2 MeasReq
@param tcCb
@param spCb
@return ROK if it is successful 
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjL2MeasReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 pjAcHdlLpjL2MeasReq(tcCb,spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   PjL2MeasReqEvt l2MeasEvt;
   Pst pst;

   CmXtaTxnCb* txnCb;
   TRC2(pjAcHdlLpjL2MeasReq);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjL2MeasReq(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjL2MeasReq(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&l2MeasEvt, sizeof(PjL2MeasReqEvt));
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_L2MEAS_REQ ;

   pjAcUtlLpjBuildL2MeasReq(tcCb, spCb, &l2MeasEvt);

   if ((txnCb = cmXtaTxnCreate(CMXTA_TXN_INVALID, tcCb)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);
   
   /*-- Call SM Wrapper API to send the request --*/
   CMXTA_DBG_INFO((_cmxtap, "Sending L2Measurement request to PDCP\n"));

   /* Send the request to the LM */
   (Void) SmMiLpjL2MeasReq(&pst, &l2MeasEvt);

   RETVALUE(ROK);
} /* pjAcHdlLpjL2MeasReq */

/**
@brief Callback for Command for L2 Measurement confirm
@param tcCb
@param spCb
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 pjAcHdlLpjL2MeasCfm
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb
)
#else
PUBLIC S16 pjAcHdlLpjL2MeasCfm(tcCb,spCb)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
#endif
{
   CmXtaMsgQElm   *qElm;
   KwAcMsgQElm   *kwElm;   
   CmStatus       status;
   Pst            pst;
   S16            ret;

   TRC2(pjAcHdlLpjL2MeasCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjL2MeasCfm(): tcId (%ld)\n", tcCb->tcId));  
#else
   CMXTA_DBG_PARAM((_cmxtap, "pjAcHdlLpjL2MeasCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   kwElm = NULLP;

   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &qElm))
   {
      CMXTA_DBG_FATAL((_cmxtap, "pjAcHdlLpjL2MeasCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   pst.event = LPJ_EVT_L2MEAS_CFM;
   
   ret = cmXtaValidatePst(&(qElm->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "pjAcHdlLpjL2MeasCfm() : No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the qElm from the Queue --*/
   if (cmXtaPopMsg (&(tcCb->msgQ[0]), &qElm) != ROK)
   {
      CMXTA_DBG_INFO((_cmxtap, "pjAcHdlLpjL2MeasCfm() : cmXtaPopMsg Failed.\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Get Default values and of return value and reason
      And Update them for the test case --*/
   cmXtaGetStatus(spCb->childStep, &status);

   kwElm = (KwAcMsgQElm *)qElm->data;

   ret   =  pjAcUtlLpjVldtL2MeasCfm(tcCb, spCb, &kwElm->u.pjMeasCfmEvt);

   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcHdlLpjL2MeasCfm() : result mismatch\n"));
      /*-- Free memory, use callback function --*/
      cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), qElm);

   RETVALUE(ROK);

} /* pjAcHdlLpjL2MeasCfm */
#endif

/********************************************************************30**

         End of file:     pjac_lpjhdl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:58 2015

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
/main/1      ---      vb         1. LTE PDCP Initial Release 2.1.
*********************************************************************91*/

