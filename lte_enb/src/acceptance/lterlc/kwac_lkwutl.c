

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_lkwutl.c

     Sid:      kwac_lkwutl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:33 2014

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
#include <stdlib.h>

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
@brief Utility Function to Build General Configuration Req 
@param tcCb
@param spCb
@param kwMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlKwBuildGenCfgReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwMngmt     *kwMngmt
)
#else
PUBLIC Void kwAcUtlKwBuildGenCfgReq(tcCb,spCb,kwMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
KwMngmt    *kwMngmt;
#endif
{
   /* local variables */
   KwGenCfg    *cfg;
   Pst         lmPst;              /* Post for layer manager */
   /* kw005.201 added changing timerRes for test cases */
   U32         newTimeRes = 0;
   Inst        kwInst;
  
   TRC2(kwAcUtlKwBuildGenCfgReq)
   cfg   = &(kwMngmt->t.cfg.s.gen);
   CMXTA_ZERO(cfg , sizeof (KwCfg));

   /* Fill general configuration parameters */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "maxUe", &(cfg->maxUe));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "maxKwuSaps", &(cfg->maxKwuSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "timeRes", &(cfg->timeRes));
   /* kw005.201 added changing timerRes for test cases */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "newTimeRes", &newTimeRes);

/*Pradeep - start. Read the "inst" value for ENTKW*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(kwInst));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "rlcMode", &(cfg->rlcMode));
   cfg->maxUdxSaps = 1;
/*Pradeep -end*/
   cfg->maxRguSaps = 1;

   /* kw005.201 added changing timerRes for test cases */
   if(newTimeRes != 0)
   {
      cfg->timeRes = newTimeRes;
   }

   cmXtaGetPst(&lmPst, ENTKW, kwInst, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   cmMemcpy((U8 *) &(cfg->lmPst),(U8 *) &(lmPst),(PTR) sizeof(Pst));

   RETVOID;
} /* kwAcUtlKwBuildGenCfgReq */


/**
@brief Utility Function to Build Sap Configuration Req
@param tcCb
@param spCb
@param kwMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlKwBuildSapCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwMngmt     *kwMngmt
)
#else
PUBLIC Void kwAcUtlKwBuildSapCfgReq(tcCb,spCb,kwMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
KwMngmt    *kwMngmt;
#endif
{
   KwSapCfg *kwSap;
   U16       sapId = 0;
   Pst       pst;
   /*Pradeep -start*/
   Inst      kwInst = 0;
   /*Pradeep -end*/
   
   kwSap = &(kwMngmt->t.cfg.s.sap);
   CMXTA_ZERO(kwSap, sizeof (KwSapCfg));

   kwSap->mem.region = DFLT_REGION;
   kwSap->mem.pool = DFLT_POOL;
   kwSap->mem.spare = 0;
   kwSap->procId = 0;
   kwSap->ent = ENTKW; 
   kwSap->inst = 0;
   kwSap->sapId = 0; 
   kwSap->bndTmrIntvl = 1000; 
   kwSap->priority = PRIOR0;
   kwSap->route = RTESPEC;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
         "procId",  &(kwSap->procId));
   /*Pradeep -start*/
   /*cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         "inst",  &(kwSap->inst));*/
   /*Pradeep -end*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         "priority",  &(kwSap->priority));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         "route",  &(kwSap->route));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
         "ent",  &(kwSap->ent));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16,
         "sapId",  &(sapId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
         "bndTmrIntvl",  &(kwSap->bndTmrIntvl));

   /*Pradeep -start*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(kwInst));
   /*Pradeep -end*/
   
   pst.selector = 1;

   switch(sapId)
   {
      case KWAC_NH_SAP:
       /*Pradeep - start*/
         /*cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);*/
         cmXtaGetPst(&pst, ENTKW, kwInst, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
       /*Pradeep - end*/         
         kwSap->sapId = KWAC_NH_SAP;
      break;
      case KWAC_PJ_SAP:
        /*Pradeep - start*/
         /*cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);*/
         cmXtaGetPst(&pst, ENTKW, kwInst, ENTPJ, kwInst/*kwSap->inst*/, 0, 0, FALSE);
        /*Pradeep - end*/
         kwSap->sapId = KWAC_PJ_SAP;
      break;
      case KWAC_CKW_SAP:
        /*Pradeep - start*/
         /*cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);*/
         cmXtaGetPst(&pst, ENTKW, kwInst, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
        /*Pradeep - end*/
         kwSap->sapId = 0;
      break;
      case KWAC_RG_SAP:
        /*Pradeep - start*/
         /*cmXtaGetPst(&pst, ENTKW, CMXTA_INST_ID, ENTRG, CMXTA_INST_ID, 0, 0, FALSE);*/
         cmXtaGetPst(&pst, ENTKW, kwInst, ENTRG, CMXTA_INST_ID, 0, 0, FALSE);
        /*Pradeep - end*/
         kwSap->sapId = 0;
         kwSap->procId = pst.dstProcId;
      break;
      
      /*Pradeep - start*/
      case KWAC_UDX_SAP:
         cmXtaGetPst(&pst, ENTKW, kwSap->inst, ENTKW, (1 - kwSap->inst), 0, 0, FALSE);

         kwSap->sapId = 0;
         kwSap->procId = pst.dstProcId;
      break;
      /*Pradeep - end*/
   }

   kwSap->selector = pst.selector;


   RETVOID;
} /* kwAcUtlKwBuildSapCfgReq */


/**
@brief Utility Function to Build Trace control Req 
@param tcCb
@param spCb
@param kwMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlKwBuildTrcCntrlReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwMngmt     *kwMngmt
)
#else
PUBLIC Void kwAcUtlKwBuildTrcCntrlReq(tcCb,spCb,kwMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
KwMngmt    *kwMngmt;
#endif
{
   KwTrcCntrl   *trc;
   trc = &(kwMngmt->t.cntrl.s.trcCntrl);
   CMXTA_ZERO(trc, sizeof (KwTrcCntrl));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "action",  &(kwMngmt->t.cntrl.action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subAction",  &(kwMngmt->t.cntrl.subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "trcMask",  &(trc->trcMask));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "trcLen",  &(trc->trcLen));

   RETVOID;
} /* kwAcUtlKwBuildTrcCntrlReq */

/**
@brief Utility Function to Build Shutdown control Req 
@param tcCb
@param spCb
@param kwMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlKwBuildSDCntrlReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwMngmt     *kwMngmt
)
#else
PUBLIC Void kwAcUtlKwBuildSDCntrlReq(tcCb,spCb,kwMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
KwMngmt    *kwMngmt;
#endif
{
   KwTrcCntrl   *trc;
   
   /* kw005.201 removed warning */
   UNUSED(tcCb);
   UNUSED(spCb);
   trc = &(kwMngmt->t.cntrl.s.trcCntrl);
   CMXTA_ZERO(trc, sizeof (KwTrcCntrl));

   kwMngmt->t.cntrl.action = ASHUTDOWN;

   RETVOID;
} /* kwAcUtlKwBuildSDCntrlReq */

/**
@brief Utility Function to Build Debug control Req
@param tcCb
@param spCb
@param kwMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlKwBuildDbgCntrlReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwMngmt     *kwMngmt
)
#else
PUBLIC Void kwAcUtlKwBuildDbgCntrlReq(tcCb,spCb,kwMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
KwMngmt    *kwMngmt;
#endif
{
   KwDbgCntrl   *dbg;
   dbg = &(kwMngmt->t.cntrl.s.dbgCntrl);
   CMXTA_ZERO(dbg, sizeof (KwDbgCntrl));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "action",  &(kwMngmt->t.cntrl.action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subAction",  &(kwMngmt->t.cntrl.subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dbgMask",  &(dbg->dbgMask));

   RETVOID;
} /* kwAcUtlKwBuildDbgCntrlReq */

/**
@brief Utility function for Status verification
@param tcCb
@param spCb
@param sta
@return RETVOID
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlKwVerifyStaCfm
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
KwSSta        *sta
)
#else
PUBLIC S16 kwAcUtlKwVerifyStaCfm(tcCb, spCb,sta)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
KwSSta        *sta;
#endif
{
   S16 elmnt = 0;
   U8 kwuSapState = 0;
   U8 ckwSapState = 0;
   U8 rguSapState = 0;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "elmnt",
         &elmnt);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "kwuSapState",
         &kwuSapState);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ckwSapState",
         &ckwSapState);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "rguSapState",
         &rguSapState);

   if(elmnt == STSID)
   {
   }
   else
   if(elmnt == STKWUSAP)
   {
       if(kwuSapState != sta->s.kwuSap.state)
       {
          RETVALUE(CMXTA_ERR_INT);
       }
   }
   else
   if(elmnt == STRGUSAP)
   {
      if(rguSapState != sta->s.rguSap.state)
      {
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else
   if(elmnt == STCKWSAP)
   {
      if(ckwSapState != sta->s.ckwSap.state)
      {
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   RETVALUE(ROK);
}


/**
@brief Utility function for Status Indication 
@param tcCb
@param spCb
@param usta
@return  - CMXTA_ERR_INT
         - CMXTA_ERR_NONE
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlKwVerifyStaInd
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
KwUSta        *usta
)
#else
PUBLIC S16 kwAcUtlKwVerifyStaInd(tcCb, spCb,usta)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
KwUSta        *usta;
#endif
{
   U16 category = 0;
   U16 event = 0;
   U16 cause = 0;
   U32 ueId = 0;
   U8  verType = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "category",
         &category);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "event",
         &event);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cause",
         &cause);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ueId",
         &ueId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "verType",
         &verType);

   switch (verType)
   {
      case KWAC_UEID:
         {
            if (ueId != usta->ueId)
               RETVALUE(CMXTA_ERR_INT);
            break;
         }
   }

   if((event != usta->alarm.event) ||
       (cause != usta->alarm.cause))
   {
      CMXTA_DBG_CALLIND((_cmxtap,
       "kwAcUtlKwVerifyStaInd():Failed - MisMatch: event exp (%d) rcvd (%d) \n\
       cause exp(%d) rcvd(%d)\n",
       event, usta->alarm.event, cause, usta->alarm.cause), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlKwVerifyStaInd */

/**
@brief Utility function for Trcce Indication 
@param tcCb
@param spCb
@param trc 
@return  - CMXTA_ERR_INT
         - CMXTA_ERR_NONE
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlKwVerifyTrcInd
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
KwTrc         *trc
)
#else
PUBLIC S16 kwAcUtlKwVerifyTrcInd(tcCb, spCb,trc)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
KwTrc         *trc;
#endif
{
   U16      event = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "event",
         &event);
   if (event != trc->event)
   {
      CMXTA_DBG_CALLIND((_cmxtap,
       "kwAcUtlKwVerifyStaInd():Failed - MisMatch: event exp (%d) rcvd (%d) \n",
       event, trc->event), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   RETVALUE(CMXTA_ERR_NONE);
}


/**
@brief Utility function for Statistics verification
@param tcCb
@param spCb
@param sts
@return RETVOID
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlKwVerifyStsCfm
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
KwSts         *sts
)
#else
PUBLIC S16 kwAcUtlKwVerifyStsCfm(tcCb, spCb,sts)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
KwSts         *sts;
#endif
{
   S16 elmnt = 0;
   S16 servType = 0;
   U32 numUe = 0;
   U32 numPdusRx = 0;
   U32 numPdusTx = 0;
   U32 bytesSent = 0;
   U32 bytesRecv = 0;
   U32 unexpPdusRecv = 0;
   U32 errPdusRecv = 0;
   U32 numSduDisc = 0;
   U32 kwuSduRx = 0;
   U32 kwuSduTx = 0;
   U32 ckwStatMsgs = 0;
   /* kw005.201 ccpu00117318, updating the statistics */
   U32 numOfRb = 0;
   U32 protTimeOut = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "elmnt", &elmnt);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "servType", &servType);

   switch(elmnt)
   {
       case STGEN:
       {
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numUe",
             &numUe);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "pdusRecv",
             &numPdusRx);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "pdusSent",
             &numPdusTx);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "bytesSent",
             &bytesSent);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "bytesRecv",
             &bytesRecv);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "unexpPdusRecv",
             &unexpPdusRecv);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "errorPdusRecv",
             &errPdusRecv);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numSduDisc",
             &numSduDisc);
          /* kw005.201 ccpu00117318, updating the statistics */
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numOfRb",
             &numOfRb);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "protTimeOut",
             &protTimeOut);

          if(numSduDisc != sts->s.gen.numSduDisc)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numSduDisc exp (%ld) rcvd (%ld) \n",
                      numSduDisc, sts->s.gen.numSduDisc), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numSduDisc exp (%d) rcvd (%d) \n",
                      numSduDisc, sts->s.gen.numSduDisc), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (numUe != sts->s.gen.numUe)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numUe exp (%ld) rcvd (%ld) \n",
                      numUe, sts->s.gen.numUe), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numUe exp (%d) rcvd (%d) \n",
                      numUe, sts->s.gen.numUe), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          /* kw005.201 ccpu00117318, removed numLc from the  statistics */

          if (numPdusRx != sts->s.gen.pdusRecv)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: pdusRecv exp (%ld) rcvd (%ld) \n",
                      numPdusRx, sts->s.gen.pdusRecv), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: pdusRecv exp (%d) rcvd (%d) \n",
                      numPdusRx, sts->s.gen.pdusRecv), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }
/*Pradeep - 8May*/
#if 0
          /* Venki */
          tKwCb = KW_GET_KWCB(0);
          sts->s.gen.pdusSent = tKwCb->genSts.pdusSent; 
          /* Venki */
#endif
          if (numPdusTx != sts->s.gen.pdusSent)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: pdusSent exp (%ld) rcvd (%ld) \n",
                      numPdusTx, sts->s.gen.pdusSent), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: pdusSent exp (%d) rcvd (%d) \n",
                      numPdusTx, sts->s.gen.pdusSent), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }
/*Pradeep - 8May*/
#if 0
          /* Venki */
          sts->s.gen.bytesSent = tKwCb->genSts.bytesSent;
#endif
          if (numPdusTx != sts->s.gen.pdusSent)

          if (bytesSent != sts->s.gen.bytesSent)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: bytesSent exp (%ld) rcvd (%ld) \n",
                      bytesSent, sts->s.gen.bytesSent), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: bytesSent exp (%d) rcvd (%d) \n",
                      bytesSent, sts->s.gen.bytesSent), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (bytesRecv != sts->s.gen.bytesRecv)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: bytesRec exp (%ld) rcvd (%ld) \n",
                      bytesRecv, sts->s.gen.bytesRecv), 2);
#else 
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: bytesRec exp (%d) rcvd (%d) \n",
                      bytesRecv, sts->s.gen.bytesRecv), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (unexpPdusRecv != sts->s.gen.unexpPdusRecv)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: unexpPdusRecv exp (%ld) rcvd (%ld) \n",
                      unexpPdusRecv, sts->s.gen.unexpPdusRecv), 2);
#else
            CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: unexpPdusRecv exp (%d) rcvd (%d) \n",
                      unexpPdusRecv, sts->s.gen.unexpPdusRecv), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (errPdusRecv != sts->s.gen.errorPdusRecv)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: errPdusRecv exp (%ld) rcvd (%ld) \n",
                      errPdusRecv, sts->s.gen.errorPdusRecv), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: errPdusRecv exp (%d) rcvd (%d) \n",
                      errPdusRecv, sts->s.gen.errorPdusRecv), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }
          /* kw005.201 ccpu00117318, updating the statistics */
/*Pradeep - 8May*/
#if 0
          /* Venki */
          /* consider downlink RBs as well */
          sts->s.gen.numOfRb += tKwCb->genSts.numOfRb;
#endif
          if(numOfRb != sts->s.gen.numOfRb)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numOfRb exp (%ld) rcvd (%ld) \n",
                      numOfRb, sts->s.gen.numOfRb), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numOfRb exp (%d) rcvd (%d) \n",
                      numOfRb, sts->s.gen.numOfRb), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }
          
          if(protTimeOut != sts->s.gen.protTimeOut)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: protTimeOut exp (%ld) rcvd (%ld) \n",
                      protTimeOut, sts->s.gen.protTimeOut), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: protTimeOut exp (%d) rcvd (%d) \n",
                      protTimeOut, sts->s.gen.protTimeOut), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          break;
       }
       case STKWUSAP:
       {
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "kwuSduRx",
             &kwuSduRx);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "kwuSduTx",
             &kwuSduTx);

          if((kwuSduRx != sts->s.kwuSap.sduRx) ||
             (kwuSduTx != sts->s.kwuSap.sduTx))
          {
             RETVALUE(CMXTA_ERR_INT);
          }
          break;
       }
       /*kw005.201 removed RGUSAP statistics support */
       case STCKWSAP:
       {
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ckwStatMsgs",
             &ckwStatMsgs);

          if(ckwStatMsgs != sts->s.ckwSap.statMsgs)
          {
             RETVALUE(CMXTA_ERR_INT);
          }

          break;
       }
       default:
          break;
   }
   RETVALUE(ROK); 
}

/**
@brief Utility Function to Build Sap control Req
@param tcCb
@param spCb
@param kwMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlKwBuildSapCntrlReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
KwMngmt     *kwMngmt
)
#else
PUBLIC Void kwAcUtlKwBuildSapCntrlReq(tcCb,spCb,kwMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
KwMngmt    *kwMngmt;
#endif
{
   KwSapCntrl     *sap;

   kwMngmt->t.cntrl.s.sapCntrl.spId = 0;
   kwMngmt->t.cntrl.s.sapCntrl.suId = 0;

   sap = &(kwMngmt->t.cntrl.s.sapCntrl);
   CMXTA_ZERO(sap, sizeof (KwSapCntrl));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "action",
         &(kwMngmt->t.cntrl.action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subAction",
         &(kwMngmt->t.cntrl.subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "spId",
         &(kwMngmt->t.cntrl.s.sapCntrl.spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "suId",
         &(kwMngmt->t.cntrl.s.sapCntrl.suId));

   RETVOID;
} /* kwAcUtlKwBuildSapCntrlReq */


/**
@brief utility function for releasing CmXtaMsgQElm
@param qElm
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlLkwFreeCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 kwAcUtlLkwFreeCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   KwAcMsgQElm *kwMsg;

   TRC2(kwAcUtlLkwFreeCb);

   CMXTA_DBG_PARAM((_cmxtap, "kwAcUtlLkwCb(): \n"));

   kwMsg = (KwAcMsgQElm *)qElm->data;

   if (kwMsg != NULLP)
   {
      if(kwMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(kwMsg->mBuf);

      CMXTA_FREE(kwMsg, sizeof (KwAcMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlLkwFreeCb */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
/**
@brief Utility Function to Build L2 Measurement Req 
@param tcCb
@param spCb
@param pjMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlLkwBuildL2MeasReq 
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
KwL2MeasReqEvt *l2MeasReqEvt
)
#else
PUBLIC Void kwAcUtlLkwBuildL2MeasReq (tcCb,spCb,l2MeasReqEvt)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
KwL2MeasReqEvt *l2MeasReqEvt;
#endif
{
   /* local variables */
   KwL2MeasReqInfo *measReq;
   U8              numQci;
  
   TRC2(kwAcUtlLkwBuildL2MeasReq )
   measReq   = &(l2MeasReqEvt->measReq);
   numQci    = 0;
   CMXTA_ZERO(measReq , sizeof (KwL2MeasReqInfo));


   /* Fill general configuration parameters */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", 
                  &(l2MeasReqEvt->transId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "measPeriod", 
                  &(l2MeasReqEvt->measPeriod));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "measType", 
                  &(measReq->measType));
#ifdef LTE_RLC_R9
   if((measReq->measType & LKW_L2MEAS_DL_IP) ||
      (measReq->measType & LKW_L2MEAS_UL_IP))
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numQci", 
                  &(measReq->val.ipThMeas.numQci));
      numQci = measReq->val.ipThMeas.numQci;
      cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
               "qci", &(measReq->val.ipThMeas.qci), &(numQci));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", 
                  &(measReq->val.ipThMeas.ueId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", 
                  &(measReq->val.ipThMeas.cellId));
   }
   else
#endif
   {
       cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numQci", \
                    &(measReq->val.nonIpThMeas.numQci));
     
       numQci = measReq->val.nonIpThMeas.numQci;

       cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "numSamples", \
                  &(measReq->val.nonIpThMeas.numSamples));
       cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
               "qci", &(measReq->val.nonIpThMeas.qci), &(numQci));
   }

   RETVOID;
} /* kwAcUtlLkwBuildL2MeasReq */
/**
@brief Utility function for L2 measurement confirm
@param tcCb
@param spCb
@param l2MeasCfm
@return RETVOID
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlLkwVldtL2MeasCfm
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
KwL2MeasCfmEvt *l2MeasCfmEvt
)
#else
PUBLIC S16 kwAcUtlLkwVldtL2MeasCfm(tcCb, spCb,l2MeasCfmEvt)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
KwL2MeasCfmEvt *l2MeasCfmEvt;
#endif
{
#if 0 /*PRERIT */
   U16              numCfm;
   KwL2MeasCfmInfo  *measCfm;
   Txt              measDataStr[512];
   U16              tokCount = 0;
   Txt              *holdMain = NULLP, *tokMain = NULLP, *tok1 = NULLP;
   Txt              *holdSub, *tokSub = NULLP, *tok2 = NULLP;
   U8                qci;
   U32              res = 0;
   U8               i;
   CmStatus         status;
   S16              ret;
   U8               measType;
   U32              transId = 0;
#ifdef LTE_RLC_R9
   CmLteCellId      cellId = 0;
   CmLteRnti        ueId = 0;
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", &transId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "numCfm", &numCfm);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "measData", &(measDataStr));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM, "status", &status.status);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM, "reason", &status.reason);
#ifdef LTE_RLC_R9
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueId", &ueId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cellId", &cellId);
#endif
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "measType", &measType);

   if(transId != l2MeasCfmEvt->transId)
   {
       CMXTA_DBG_CALLIND((_cmxtap,
                   "Failed - MisMatch: transId exp (%ld) rcvd (%ld) \n",
                    transId, l2MeasCfmEvt->transId), 2);
       RETVALUE(CMXTA_ERR_INT);
   }

   if(numCfm != l2MeasCfmEvt->numCfm)
   {
       CMXTA_DBG_CALLIND((_cmxtap,
                   "Failed - MisMatch: numCfm exp (%d) rcvd (%d) \n",
                    numCfm, l2MeasCfmEvt->numCfm), 2);
       RETVALUE(CMXTA_ERR_INT);
   }

   if(measType != l2MeasCfmEvt->measType)
   {
       CMXTA_DBG_CALLIND((_cmxtap,
                   "Failed - MisMatch: measType exp (%d) rcvd (%d) \n",
                    measType, l2MeasCfmEvt->measType), 2);
       RETVALUE(CMXTA_ERR_INT);
   }
   ret = cmXtaValidateStatus(&status, &l2MeasCfmEvt->status);
   
   if(ret != ROK)
   {
       RETVALUE(CMXTA_ERR_INT);
   }

#ifdef LTE_RLC_R9
   if(cellId != l2MeasCfmEvt->cellId)
   {
       CMXTA_DBG_CALLIND((_cmxtap,
                   "Failed - MisMatch: cellId exp (%d) rcvd (%d) \n",
                    cellId, l2MeasCfmEvt->cellId), 2);
       RETVALUE(CMXTA_ERR_INT);
   }

   if(ueId != l2MeasCfmEvt->ueId)
   {
       CMXTA_DBG_CALLIND((_cmxtap,
                   "Failed - MisMatch: ueId exp (%d) rcvd (%d) \n",
                    ueId, l2MeasCfmEvt->ueId), 2);
       RETVALUE(CMXTA_ERR_INT);
   }
#endif
   tokCount = 0;
   for (holdMain = measDataStr;;holdMain=NULLP)
   {
      measCfm = &l2MeasCfmEvt->measCfm[tokCount];
      tokMain = (Txt *)strtok_r(holdMain, ";", &tok1);

      if (tokMain == NULLP)
      {
         break;
      }
      /* process each cfmdata */
      for (holdSub = tokMain, i = 0; i < 6; i++, holdSub=NULLP)
      {
         if ((tokSub=strtok_r(holdSub,":",&tok2)) == NULLP)
         {
            break;
         }
         switch(i)
         {
            case 0:
               {  /* QCI */
                  qci = atoi(tokSub);
                  if(measCfm->qci != qci)
                  {
                     CMXTA_DBG_CALLIND((_cmxtap,
                         "Failed - MisMatch: qci exp (%d) rcvd (%d) \n",
                         qci, measCfm->qci), 2);
                     RETVALUE(CMXTA_ERR_INT);
                  }
                  break;
               }
            case 1:
               {  /* numActUe or dlIpThPut */
                  res = atoi(tokSub);
#ifdef LTE_RLC_R9
                  if( (measType & LKW_L2MEAS_DL_IP) || 
                      (measType & LKW_L2MEAS_UL_IP ))
                  {
                      /*dl ip throughput can not be predicted with accuracy*
                       *since time is involved in this. So the following   *
                       *approach has been taken.                           */
                      if(0 == res)
                      {
                         if(measCfm->val.ipThrput.dlIpThPut != res)
                         {
#ifndef ALIGN_64BIT
                             CMXTA_DBG_CALLIND((_cmxtap,
                               "Failed - MisMatch:DL Ipthrput exp (%ld) rcvd (%ld) \n",
                                res, measCfm->val.ipThrput.dlIpThPut), 2);
#else
                             CMXTA_DBG_CALLIND((_cmxtap,
                               "Failed - MisMatch: DL Ipthrput exp (%d) rcvd (%d) \n",
                                res, measCfm->val.ipThrput.dlIpThPut), 2);
#endif
                             RETVALUE(CMXTA_ERR_INT);
                         }
                      }
                      else
                      {
                         if(0 == measCfm->val.ipThrput.dlIpThPut)
                         {
#ifndef ALIGN_64BIT
                             CMXTA_DBG_CALLIND((_cmxtap,
                               "Failed - MisMatch:DL Ipthrput exp (%ld) rcvd (%ld) \n",
                                res, measCfm->val.ipThrput.dlIpThPut), 2);
#else
                             CMXTA_DBG_CALLIND((_cmxtap,
                               "Failed - MisMatch: DL Ipthrput exp (%d) rcvd (%d) \n",
                                res, measCfm->val.ipThrput.dlIpThPut), 2);
#endif
                             RETVALUE(CMXTA_ERR_INT);
                         }
                         else
                         {
#ifndef ALIGN_64BIT
                            CMXTA_DBG_CALLIND((_cmxtap,
                               "Passed - Dl Ip throughput is %ld \n", 
                                measCfm->val.ipThrput.dlIpThPut), 1);
#else
                            CMXTA_DBG_CALLIND((_cmxtap,
                               "Passed - Dl Ip throughput is %d \n", 
                                measCfm->val.ipThrput.dlIpThPut), 1);
#endif
                         }
                      }
                  }
                  else
#endif /*LTE_RLC_R9*/
                  {
                     if(measCfm->val.nonIpThrput.numActUe != res)
                     {
#ifndef ALIGN_64BIT
                         CMXTA_DBG_CALLIND((_cmxtap,
                             "Failed - MisMatch:numActUe exp (%ld) rcvd (%ld) \n",
                              res, measCfm->val.nonIpThrput.numActUe), 2);
#else
                          CMXTA_DBG_CALLIND((_cmxtap,
                               "Failed - MisMatch: numActUe exp (%d) rcvd (%d) \n",
                                res, measCfm->val.nonIpThrput.numActUe), 2);
#endif
                          RETVALUE(CMXTA_ERR_INT);
                     }
                  }   
                  break;
               }
              case 2:
                  {   /* uuLoss or ulIpThPut */
                      res = atoi(tokSub);
#ifdef LTE_RLC_R9
                      if( (measType & LKW_L2MEAS_DL_IP) ||
                          (measType & LKW_L2MEAS_UL_IP ))
                      {
                         if(measCfm->val.ipThrput.ulIpThPut != res)
                         {
#ifndef ALIGN_64BIT
                            CMXTA_DBG_CALLIND((_cmxtap,
                               "Failed - MisMatch:UL Ipthrput exp (%ld) rcvd (%ld) \n",
                                res, measCfm->val.ipThrput.ulIpThPut), 2);
#else
                            CMXTA_DBG_CALLIND((_cmxtap,
                               "Failed - MisMatch: UL Ipthrput exp (%d) rcvd (%d) \n",
                                res, measCfm->val.ipThrput.ulIpThPut), 2);
#endif
                            RETVALUE(CMXTA_ERR_INT);
                         }
                      }
                      else
#endif /*LTE_RLC_R9*/
                      {
                         if(measCfm->val.nonIpThrput.uuLoss!= res)
                         {
#ifndef ALIGN_64BIT
                            CMXTA_DBG_CALLIND((_cmxtap,
                               "Failed - MisMatch:uuLoss exp (%ld) rcvd (%ld) \n",
                                res, measCfm->val.nonIpThrput.uuLoss), 2);
#else
                            CMXTA_DBG_CALLIND((_cmxtap,
                               "Failed - MisMatch: uuLoss exp (%d) rcvd (%d) \n",
                                res, measCfm->val.nonIpThrput.uuLoss), 2);
#endif
                            RETVALUE(CMXTA_ERR_INT);
                         }
                      }
                      break;
                   }
              default:
                   break;
         }/* end of switch i */
      }/* End of holdSub */
      tokCount++;
   }/* end of for holdMain */
#endif
   RETVALUE(ROK); 
}/* end of kwAcUtlLkwVldtL2MeasCfm */
#endif
/********************************************************************30**
         End of file:     kwac_lkwutl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:33 2014
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
/main/1      ---       gk          1. Initial Release.
/main/2      ---       gk          1. LTE RLC Release 2.1.
/main/3      kw005.201 ap          1. Removed compilation warning.
                                   2. Added missing code for statistics updation.
                                   3. Fix for timerResolution in CfgReq
                       rd          1. Moved extraction of ueId and cellId
                                      outside the switch in kwAcUtlLkwVldtL2MeasCfm.
                                   2. Added the extraction of ueId and cellId
                                      in kwAcUtlLkwBuildL2MeasReq.
                                   3. Modified code after moving measType to
                                      KwL2MeasCfmEvt. 
                                   4. Added few log statements and also modified
                                      the logic for validating dl ip
                                      throughput in kwAcUtlLkwVldtL2MeasCfm.
*********************************************************************91*/
