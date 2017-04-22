

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_lpjutl.c

     Sid:      kwac_lpjutl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:35 2014

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
/**
@brief Utility Function to Build General Configuration Req 
@param tcCb
@param spCb
@param pjMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlPjBuildGenCfgReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *pjMngmt
)
#else
PUBLIC Void kwAcUtlPjBuildGenCfgReq(tcCb,spCb,pjMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PjMngmt    *pjMngmt;
#endif
{
   /* local variables */
   PjGenCfg    *cfg;
#ifdef KW_PDCP
   Pst         lmPst;
#endif /* KW_PDCP */
  
   TRC2(kwAcUtlPjBuildGenCfgReq)
   cfg   = &(pjMngmt->t.cfg.s.gen);
   CMXTA_ZERO(cfg , sizeof (PjCfg));

   cfg->maxPjuSaps = 2;
   cfg->nmbUlBins = 5;
   cfg->nmbDlBins = 5;

   /* Fill general configuration parameters */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxPjuSaps", &(cfg->maxPjuSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbUlBins", &(cfg->nmbUlBins));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbDlBins", &(cfg->nmbDlBins));

   cmXtaGetPst(&lmPst, ENTPJ, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   cmMemcpy((U8 *) &(cfg->lmPst),(U8 *) &(lmPst),(PTR) sizeof(Pst));

#if (defined(PJ_SEC_ASYNC) || defined(PJ_CMP_ASYNC))
   cfg->obdTmrInt = 5;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "obdTmrInt", &(cfg->obdTmrInt));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "obdTmrInt0", &(cfg->obdTmrInt));
   cfg->obdWtTmrInt  =  cfg->obdTmrInt;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "obdWtTmrInt", &(cfg->obdWtTmrInt));
   /* Get the Post structure between ENTPJ (LTE RLC & PDCP) and ENTOC
    * (Off-board Compression) */
   cmXtaGetPst(&lmPst, ENTPJ, CMXTA_INST_ID, ENTOC, CMXTA_INST_ID, 0, 0, FALSE);
   cmMemcpy((U8 *) &(cfg->obdPst.cmpPst),(U8 *) &(lmPst),(PTR) sizeof(Pst));

   /* Get the Post structure between ENTPJ (LTE RLC & PDCP) and ENTOS
    * (Off-board Security) */
   cmXtaGetPst(&lmPst, ENTPJ, CMXTA_INST_ID, ENTOS, CMXTA_INST_ID, 0, 0, FALSE);
   cmMemcpy((U8 *) &(cfg->obdPst.secPst),(U8 *) &(lmPst),(PTR) sizeof(Pst));
#endif /* PJ_SEC_ASYNC || PJ_CMP_ASYNC */

   RETVOID;
} /* kwAcUtlPjBuildGenCfgReq */


/**
@brief Utility Function to Build Sap Configuration Req
@param tcCb
@param spCb
@param pjMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlPjBuildSapCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *pjMngmt
)
#else
PUBLIC Void kwAcUtlPjBuildSapCfgReq(tcCb,spCb,pjMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PjMngmt    *pjMngmt;
#endif
{
   PjSapCfg *kwSap;
   U16       sapId = 0;
   Pst       pst;
 
   kwSap = &(pjMngmt->t.cfg.s.sap);
   CMXTA_ZERO(kwSap, sizeof (PjSapCfg));
   CMXTA_ZERO(&pst, sizeof (Pst));

   kwSap->mem.region = DFLT_REGION;
   kwSap->mem.pool = DFLT_POOL;
   kwSap->mem.spare = 0;
   kwSap->procId = 0;
   kwSap->ent = ENTPJ; 
   kwSap->inst = 0;
   kwSap->sapId = 0; 
   kwSap->bndTmrIntvl = 1000; 
   kwSap->priority = PRIOR0;
   kwSap->route = RTESPEC;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
         "procId",  &(kwSap->procId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         "inst",  &(kwSap->inst));
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

   switch(sapId)
   {
      case KWAC_CPJ_SAP:
         cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
         kwSap->sapId = 0;
      break;
      case KWAC_NH_PJU_SAP:
         cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
         kwSap->sapId = PJ_SRB;
      break;
      case KWAC_PX_PJU_SAP:
         cmXtaGetPst(&pst, ENTPJ, CMXTA_INST_ID, ENTPX, CMXTA_INST_ID, 0, 0, FALSE);
         kwSap->sapId = PJ_DRB;
      break;
   }

   kwSap->selector = pst.selector;


   RETVOID;
} /* kwAcUtlPjBuildSapCfgReq */


/**
@brief Utility Function to Build Trace control Req 
@param tcCb
@param spCb
@param pjMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlPjBuildTrcCntrlReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *pjMngmt
)
#else
PUBLIC Void kwAcUtlPjBuildTrcCntrlReq(tcCb,spCb,pjMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PjMngmt    *pjMngmt;
#endif
{
   PjTrcCntrl   *trc;
   trc = &(pjMngmt->t.cntrl.s.trcCntrl);
   CMXTA_ZERO(trc, sizeof (PjTrcCntrl));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "action",  &(pjMngmt->t.cntrl.action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subAction",  &(pjMngmt->t.cntrl.subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "trcMask",  &(trc->trcMask));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "trcLen",  &(trc->trcLen));

   RETVOID;
} /* kwAcUtlPjBuildTrcCntrlReq */

/**
@brief Utility Function to Build Shutdown control Req 
@param tcCb
@param spCb
@param pjMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlPjBuildSDCntrlReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *pjMngmt
)
#else
PUBLIC Void kwAcUtlPjBuildSDCntrlReq(tcCb,spCb,pjMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PjMngmt    *pjMngmt;
#endif
{
   PjTrcCntrl   *trc;
   trc = &(pjMngmt->t.cntrl.s.trcCntrl);
   CMXTA_ZERO(trc, sizeof (PjTrcCntrl));

   pjMngmt->t.cntrl.action = ASHUTDOWN;

   RETVOID;
} /* kwAcUtlPjBuildSDCntrlReq */

/**
@brief Utility Function to Build Debug control Req
@param tcCb
@param spCb
@param pjMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlPjBuildDbgCntrlReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PjMngmt     *pjMngmt
)
#else
PUBLIC Void kwAcUtlPjBuildDbgCntrlReq(tcCb,spCb,pjMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PjMngmt    *pjMngmt;
#endif
{
   PjDbgCntrl   *dbg;
   dbg = &(pjMngmt->t.cntrl.s.dbgCntrl);
   CMXTA_ZERO(dbg, sizeof (PjDbgCntrl));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "action",  &(pjMngmt->t.cntrl.action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subAction",  &(pjMngmt->t.cntrl.subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dbgMask",  &(dbg->dbgMask));

   RETVOID;
} /* kwAcUtlPjBuildDbgCntrlReq */

/**
@brief Utility function for Status verification
@param tcCb
@param spCb
@param sta
@return RETVOID
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlPjVerifyStaCfm
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjSSta        *sta
)
#else
PUBLIC S16 kwAcUtlPjVerifyStaCfm(tcCb, spCb,sta)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PjSSta        *sta;
#endif
{
   S16 elmnt = 0;
   U8 pjuSapState = 0;
   U8 cpjSapState = 0;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "elmnt",
         &elmnt);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pjuSapState",
         &pjuSapState);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cpjSapState",
         &cpjSapState);

   if(elmnt == STSID)
   {
   }
   else
   if(elmnt == STPJUSAP)
   {
       if(pjuSapState != sta->s.pjuSap.state)
       {
          RETVALUE(CMXTA_ERR_INT);
       }
   }
   else
   if(elmnt == STCPJSAP)
   {
      if(cpjSapState != sta->s.cpjSap.state)
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
PUBLIC S16 kwAcUtlPjVerifyStaInd
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjUSta        *usta
)
#else
PUBLIC S16 kwAcUtlPjVerifyStaInd(tcCb, spCb,usta)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PjUSta        *usta;
#endif
{
   U16 category = 0;
   U16 event = 0;
   U16 cause = 0;
   U32 ueId = 0;
   U8  verType = 0;
#ifdef LTE_L2_MEAS
   U8  qci = 0;
#endif

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
#ifdef LTE_L2_MEAS
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "qci",
         &qci);
#endif
   switch (verType)
   {
      case KWAC_UEID:
         {
            if (ueId != usta->ueId)
               RETVALUE(CMXTA_ERR_INT);
            break;
         }
#ifdef LTE_L2_MEAS
      case KWAC_QCI:
         {
            if (qci != usta->qci)
               RETVALUE(CMXTA_ERR_INT);
            break;
         }
#endif
   }

   if((event != usta->alarm.event) ||
       (cause != usta->alarm.cause))
   {
      CMXTA_DBG_CALLIND((_cmxtap,
       "kwAcUtlPjVerifyStaInd():Failed - MisMatch: event exp (%d) rcvd (%d) \n\
       cause exp(%d) rcvd(%d)\n",
       event, usta->alarm.event, cause, usta->alarm.cause), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlPjVerifyStaInd */

/**
@brief Utility function for Trcce Indication 
@param tcCb
@param spCb
@param trc 
@return  - CMXTA_ERR_INT
         - CMXTA_ERR_NONE
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlPjVerifyTrcInd
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjTrc         *trc
)
#else
PUBLIC S16 kwAcUtlPjVerifyTrcInd(tcCb, spCb,trc)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PjTrc         *trc;
#endif
{
   U16      event = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "event",
         &event);
   if (event != trc->event)
   {
      CMXTA_DBG_CALLIND((_cmxtap,
       "kwAcUtlPjVerifyStaInd():Failed - MisMatch: event exp (%d) rcvd (%d) \n",
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
PUBLIC S16 kwAcUtlPjVerifyStsCfm
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PjSts         *sts
)
#else
PUBLIC S16 kwAcUtlPjVerifyStsCfm(tcCb, spCb,sts)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PjSts         *sts;
#endif
{
   U32 rxPdus = 0;
   U32 txPdus = 0;
   U32 pjuSduRx = 0;
   U32 pjuSduTx = 0;
   U32 errorPdusRecv = 0;
   U32 numSdusDisc = 0;
   U32 numCmpFails = 0;
   U32 numDecmpFails = 0;
   U32 numIntgPrtFails = 0;
   U32 numIntgVrfFails = 0;
   U32 numCiphFails = 0;
   U32 numDeciphFails = 0;
   U32 numPdusDiscObdTmrExp = 0;
   U32 numSdusDiscObdTmrExp = 0;
   U32 numPktsFrwd = 0;
   U32 numPktsRcvd = 0;
   S16 elmnt = 0;
   S16 servType = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "elmnt", &elmnt);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "servType", &servType);

   switch(elmnt)
   {
       case STGEN:
       {
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "rxPdus",
             &rxPdus);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "txPdus",
             &txPdus);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "errorPdusRecv",
             &errorPdusRecv);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numSdusDisc",
             &numSdusDisc);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numCmpFails",
             &numCmpFails);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numDecmpFails",
             &numDecmpFails);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numIntgPrtFails",
             &numIntgPrtFails);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numIntgVrfFails",
             &numIntgVrfFails);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numCiphFails",
             &numCiphFails);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numDeciphFails",
             &numDeciphFails);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numPdusDiscObdTmrExp",
             &numPdusDiscObdTmrExp);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numSdusDiscObdTmrExp",
             &numSdusDiscObdTmrExp);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numPktsFrwd",
             &numPktsFrwd);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "numPktsRcvd",
             &numPktsRcvd);

          if (rxPdus != sts->s.gen.rxPdus)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: rxPdus exp (%ld) rcvd (%ld) \n",
                      rxPdus, sts->s.gen.rxPdus), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: rxPdus exp (%d) rcvd (%d) \n",
                      rxPdus, sts->s.gen.rxPdus), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (txPdus != sts->s.gen.txPdus)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: txPdus exp (%ld) rcvd (%ld) \n",
                      txPdus, sts->s.gen.txPdus), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: txPdus exp (%d) rcvd (%d) \n",
                      txPdus, sts->s.gen.txPdus), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (errorPdusRecv != sts->s.gen.errorPdusRecv)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: errorPdusRecv exp (%ld) rcvd (%ld) \n",
                      errorPdusRecv, sts->s.gen.errorPdusRecv), 2);
#else
            CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: errorPdusRecv exp (%d) rcvd (%d) \n",
                      errorPdusRecv, sts->s.gen.errorPdusRecv), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (numSdusDisc != sts->s.gen.numSdusDisc)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numSdusDisc exp (%ld) rcvd (%ld) \n",
                      numSdusDisc, sts->s.gen.numSdusDisc), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numSdusDisc exp (%d) rcvd (%d) \n",
                      numSdusDisc, sts->s.gen.numSdusDisc), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (numCmpFails != sts->s.gen.numCmpFails)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numCmpFails exp (%ld) rcvd (%ld) \n",
                      numCmpFails, sts->s.gen.numCmpFails), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numCmpFails exp (%d) rcvd (%d) \n",
                      numCmpFails, sts->s.gen.numCmpFails), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (numDecmpFails != sts->s.gen.numDecmpFails)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numDecmpFails exp (%ld) rcvd (%ld) \n",
                      numDecmpFails, sts->s.gen.numDecmpFails), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numDecmpFails exp (%d) rcvd (%d) \n",
                      numDecmpFails, sts->s.gen.numDecmpFails), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (numIntgPrtFails != sts->s.gen.numIntgPrtFails)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numIntgPrtFails exp (%ld) rcvd (%ld) \n",
                      numIntgPrtFails, sts->s.gen.numIntgPrtFails), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numIntgPrtFails exp (%d) rcvd (%d) \n",
                      numIntgPrtFails, sts->s.gen.numIntgPrtFails), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (numIntgVrfFails != sts->s.gen.numIntgVrfFails)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numIntgVrfFails exp (%ld) rcvd (%ld) \n",
                      numIntgVrfFails, sts->s.gen.numIntgVrfFails), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numIntgVrfFails exp (%d) rcvd (%d) \n",
                      numIntgVrfFails, sts->s.gen.numIntgVrfFails), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (numCiphFails != sts->s.gen.numCiphFails)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numCiphFails exp (%ld) rcvd (%ld) \n",
                      numCiphFails, sts->s.gen.numCiphFails), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numCiphFails exp (%d) rcvd (%d) \n",
                      numCiphFails, sts->s.gen.numCiphFails), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (numDeciphFails != sts->s.gen.numDeciphFails)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numDeciphFails exp (%ld) rcvd (%ld) \n",
                      numDeciphFails, sts->s.gen.numDeciphFails), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numDeciphFails exp (%d) rcvd (%d) \n",
                      numDeciphFails, sts->s.gen.numDeciphFails), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (numPdusDiscObdTmrExp != sts->s.gen.numPdusDiscObdTmrExp)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numPdusDiscObdTmrExp exp (%ld) rcvd (%ld) \n",
                      numPdusDiscObdTmrExp, sts->s.gen.numPdusDiscObdTmrExp), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numPdusDiscObdTmrExp exp (%d) rcvd (%d) \n",
                      numPdusDiscObdTmrExp, sts->s.gen.numPdusDiscObdTmrExp), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (numSdusDiscObdTmrExp != sts->s.gen.numSdusDiscObdTmrExp)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numSdusDiscObdTmrExp exp (%ld) rcvd (%ld) \n",
                      numSdusDiscObdTmrExp, sts->s.gen.numSdusDiscObdTmrExp), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numSdusDiscObdTmrExp exp (%d) rcvd (%d) \n",
                      numSdusDiscObdTmrExp, sts->s.gen.numSdusDiscObdTmrExp), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (numPktsFrwd != sts->s.gen.numPktsFrwd)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numPktsFrwd exp (%ld) rcvd (%ld) \n",
                      numPktsFrwd, sts->s.gen.numPktsFrwd), 2);
#else
              CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numPktsFrwd exp (%d) rcvd (%d) \n",
                      numPktsFrwd, sts->s.gen.numPktsFrwd), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          if (numPktsRcvd != sts->s.gen.numPktsRcvd)
          {
#ifndef ALIGN_64BIT
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numPktsRcvd exp (%ld) rcvd (%ld) \n",
                      numPktsRcvd, sts->s.gen.numPktsRcvd), 2);
#else
             CMXTA_DBG_CALLIND((_cmxtap,
                      "Failed - MisMatch: numPktsRcvd exp (%d) rcvd (%d) \n",
                      numPktsRcvd, sts->s.gen.numPktsRcvd), 2);
#endif
             RETVALUE(CMXTA_ERR_INT);
          }

          break;
       }
       case STPJUSAP:
       {
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "rxSdus",
             &pjuSduRx);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "txSdus",
             &pjuSduTx);

          if((pjuSduRx != sts->s.pjuSap.rxSdus) ||
             (pjuSduTx != sts->s.pjuSap.txSdus))
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
@brief utility function for releasing CmXtaMsgQElm
@param qElm
@return CMXTA_ERR_NONE if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlLpjFreeCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 kwAcUtlLpjFreeCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   KwAcMsgQElm *kwMsg;

   TRC2(kwAcUtlLpjFreeCb);

   CMXTA_DBG_PARAM((_cmxtap, "kwAcUtlLpjCb(): \n"));

   kwMsg = (KwAcMsgQElm *)qElm->data;

   if (kwMsg != NULLP)
   {
      if(kwMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(kwMsg->mBuf);

      CMXTA_FREE(kwMsg, sizeof (KwAcMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlLpjFreeCb */

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
PUBLIC Void kwAcUtlLpjBuildL2MeasReq 
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PjL2MeasReqEvt *l2MeasReqEvt
)
#else
PUBLIC Void kwAcUtlLpjBuildL2MeasReq (tcCb,spCb,l2MeasReqEvt)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
PjL2MeasReqEvt *l2MeasReqEvt;
#endif
{
   /* local variables */
   PjL2MeasReqInfo *measReq;
  
   TRC2(kwAcUtlLpjBuildL2MeasReq )
   measReq   = &(l2MeasReqEvt->measReq);
   CMXTA_ZERO(measReq , sizeof (PjL2MeasReqInfo));


   /* Fill general configuration parameters */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId", 
                  &(l2MeasReqEvt->transId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "measPeriod", 
                  &(l2MeasReqEvt->measPeriod));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "measType", 
                  &(measReq->measType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numQci", 
                  &(measReq->numQci));
   cmXtaXmlGetValList(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, CMXTA_SEP_COLON,\
         "qci", (measReq->qci), &(measReq->numQci));

   RETVOID;
} /* kwAcUtlLpjBuildL2MeasReq */
/**
@brief Utility function for L2 measurement confirm
@param tcCb
@param spCb
@param l2MeasCfm
@return RETVOID
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlLpjVldtL2MeasCfm
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PjL2MeasCfmEvt *l2MeasCfmEvt
)
#else
PUBLIC S16 kwAcUtlLpjVldtL2MeasCfm(tcCb, spCb,l2MeasCfmEvt)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
PjL2MeasCfmEvt *l2MeasCfmEvt;
#endif
{
   U16              numCfm;
   PjL2MeasCfmInfo  *measCfm;
   Txt              measDataStr[512];
   U16              tokCount = 0;
   Txt              *holdMain = NULLP, *tokMain = NULLP, *tok1 = NULLP;
   Txt              *holdSub, *tokSub = NULLP, *tok2 = NULLP;
   U8               measType;
   U8               qci;
   U32              res = 0;
   U8               i;
   CmStatus         status;
   S16              ret;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "numCfm", &numCfm);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "measData", &(measDataStr));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM, "status", &status.status);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM, "reason", &status.reason);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,   "measType", &(measType));

   if(numCfm != l2MeasCfmEvt->numCfm)
   {
#ifndef ALIGN_64BIT
       CMXTA_DBG_CALLIND((_cmxtap,
                   "Failed - MisMatch: numCfm exp (%d) rcvd (%d) \n",
                    numCfm, l2MeasCfmEvt->numCfm), 2);
#else
       CMXTA_DBG_CALLIND((_cmxtap,
                   "Failed - MisMatch: exp (%d) rcvd (%d) \n",
                    numCfm, l2MeasCfmEvt->numCfm), 2);
#endif
       RETVALUE(CMXTA_ERR_INT);
   }
   if(l2MeasCfmEvt->measType != measType)
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap,
                 "Failed - MisMatch: measType exp (%d) rcvd (%d) \n",
                  measType, l2MeasCfmEvt->measType), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap,
                 "Failed - MisMatch: measType exp (%d) rcvd (%d) \n",
                   measType, l2MeasCfmEvt->measType), 2);
#endif
      RETVALUE(CMXTA_ERR_INT);
   }
   ret = cmXtaValidateStatus(&status, &l2MeasCfmEvt->status);
   
   if(ret != ROK)
   {
       RETVALUE(CMXTA_ERR_INT);
   }

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
      for (holdSub = tokMain, i = 0; i < 4; i++, holdSub=NULLP)
      {
         if ((tokSub=(Txt *)strtok_r(holdSub,":",&tok2)) == NULLP)
         {
            break;
         }
         switch(i)
         {
            case 0:
               {
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
               {
                  res = atoi(tokSub);
                  if(res > 0)
                  {
                     if(measCfm->dlDelay == 0)
                     {
#ifndef ALIGN_64BIT
                        CMXTA_DBG_CALLIND((_cmxtap,
                            "Failed Received DL Delay is (%ld)\n", measCfm->dlDelay), 2);
#else
                        CMXTA_DBG_CALLIND((_cmxtap,
                             "Failed Received DL Delay is (%d)\n", measCfm->dlDelay), 2);
#endif
                        RETVALUE(CMXTA_ERR_INT);
                     }
                  }
                  else
                  {
                     if(measCfm->dlDelay != 0)
                     {
#ifndef ALIGN_64BIT
                       CMXTA_DBG_CALLIND((_cmxtap,
                            "Failed Received DL Delay is (%ld)\n", measCfm->dlDelay), 2);
#else
                        CMXTA_DBG_CALLIND((_cmxtap,
                             "Failed Received DL Delay is (%d)\n", measCfm->dlDelay), 2);
#endif
                        RETVALUE(CMXTA_ERR_INT);
                     }
                  }
                  break;
                 }
            case 2:
               {
                  res = atoi(tokSub);
                  if(measCfm->dlDisc != res)
                  {
#ifndef ALIGN_64BIT
                        CMXTA_DBG_CALLIND((_cmxtap,
                           "Failed - MisMatch:dlDisc exp (%ld) rcvd (%ld) \n",
                            res, measCfm->dlDisc), 2);
#else
                         CMXTA_DBG_CALLIND((_cmxtap,
                              "Failed - MisMatch: dlDisc exp (%d) rcvd (%d) \n",
                               res, measCfm->dlDisc), 2);
#endif
                          RETVALUE(CMXTA_ERR_INT);
                  }
                  break;
               }
            case 3:
               {
                  res = atoi(tokSub);
                  if(measCfm->ulLoss != res)
                  {

#ifndef ALIGN_64BIT
                      CMXTA_DBG_CALLIND((_cmxtap,
                          "Failed - MisMatch:ulLoss exp (%ld) rcvd (%ld) \n",
                           res, measCfm->ulLoss), 2);
#else
                      CMXTA_DBG_CALLIND((_cmxtap,
                           "Failed - MisMatch: ulLoss exp (%d) rcvd (%d) \n",
                            res, measCfm->ulLoss), 2);
#endif
                      RETVALUE(CMXTA_ERR_INT);
                  }
                  break;
               }
         }/* End of switch i */
      }/* end of for holdSub */
      tokCount++;
   }/* end of for holdMain */

   RETVALUE(ROK); 
}/* end of kwAcUtlLpjVldtL2MeasCfm */
#endif
#endif /* KW_PDCP */

/********************************************************************30**
         End of file:     kwac_lpjutl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:35 2014
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
/main/     kw005.201 ap       1. Added support for L2 measurement.
*********************************************************************91*/


