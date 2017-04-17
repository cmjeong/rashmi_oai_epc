

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_lpkutl.c

     Sid:      pjac_lpkutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:02 2015

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

/**
@brief Utility Function to Build General Configuration Req 
@param tcCb
@param spCb
@param pkMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlPkBuildGenCfgReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *pkMngmt
)
#else
PUBLIC Void kwAcUtlPkBuildGenCfgReq(tcCb,spCb,pkMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PkMngmt    *pkMngmt;
#endif
{
   /* local variables */
   PkGenCfg    *cfg;
   Pst         lmPst;

   TRC2(kwAcUtlPkBuildGenCfgReq)
   cfg   = &(pkMngmt->t.cfg.s.gen);
   CMXTA_ZERO(cfg , sizeof (PkCfg));

   cfg->maxCpjSaps = 2;
   cfg->nmbUlBins = 5;
   cfg->nmbDlBins = 5;

   /* Fill general configuration parameters */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxCpjSaps", &(cfg->maxCpjSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbUlBins", &(cfg->nmbUlBins));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbDlBins", &(cfg->nmbDlBins));
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "timeRes",&(cfg->timeRes));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pdcpMode", &(cfg->mode));
   cmXtaGetPst(&lmPst, ENTPK, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, 0, 0, FALSE);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxUlCpjSaps", &(cfg->maxUlCpjSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "maxDlCpjSaps", &(cfg->maxDlCpjSaps));
   cmMemcpy((U8 *) &(cfg->lmPst),(U8 *) &(lmPst),(PTR) sizeof(Pst));


   RETVOID;
} /* kwAcUtlPkBuildGenCfgReq */


/**
@brief Utility Function to Build Sap Configuration Req
@param tcCb
@param spCb
@param pkMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlPkBuildSapCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *pkMngmt
)
#else
PUBLIC Void kwAcUtlPkBuildSapCfgReq(tcCb,spCb,pkMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PkMngmt    *pkMngmt;
#endif
{
   PkSapCfg *pkSap;
   U16       sapId = 0;
   Pst       pst;
   S16       spId = 0;
   S16       suId = 0;
   Inst      pkInst = 0;
 
   pkSap = &(pkMngmt->t.cfg.s.sap);
   CMXTA_ZERO(pkSap, sizeof (PkSapCfg));
   CMXTA_ZERO(&pst, sizeof (Pst));

   pkSap->mem.region = DFLT_REGION;
   pkSap->mem.pool = DFLT_POOL;
   pkSap->mem.spare = 0;
   pkSap->procId = 0;
   pkSap->ent = ENTPK; 
   pkSap->inst = 0;
   pkSap->sapId = 0; 
   pkSap->bndTmrIntvl = 1000; 
   pkSap->priority = PRIOR0;
   pkSap->route = RTESPEC;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
         "procId",  &(pkSap->procId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         "priority",  &(pkSap->priority));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
         "route",  &(pkSap->route));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
         "ent",  &(pkSap->ent));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16,
         "sapId",  &(sapId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
         "bndTmrIntvl",  &(pkSap->bndTmrIntvl));

   switch(sapId)
   {
       case PJAC_LOWERCPJ_SAP:
           {
               cmXtaGetPst(&pst, ENTPK, CMXTA_INST_ID, ENTPJ, CMXTA_INST_ID, 0, 0, FALSE);
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16,"suId",  &(suId));
               /* This instance Id is needed to set as destination instance Id */
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "inst", &(pkInst));
               pkSap->suId = suId;
               pkSap->inst = pkInst;
               break;
           }
       case PJAC_UPPERCPJ_SAP:
           {
               cmXtaGetPst(&pst, ENTPK, CMXTA_INST_ID, ENTNH, CMXTA_INST_ID, 0, 0, FALSE);
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16,"spId",  &(spId));
               pkSap->spId = spId;
               break;
           }
       default:
           {
               break;
           }
   }

   pkSap->selector = pst.selector;
   RETVOID;
} /* kwAcUtlPkBuildSapCfgReq */


/**
@brief Utility Function to Build Trace control Req 
@param tcCb
@param spCb
@param pkMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlPkBuildTrcCntrlReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *pkMngmt
)
#else
PUBLIC Void kwAcUtlPkBuildTrcCntrlReq(tcCb,spCb,pkMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PkMngmt    *pkMngmt;
#endif
{
   PkTrcCntrl   *trc;
   trc = &(pkMngmt->t.cntrl.s.trcCntrl);
   CMXTA_ZERO(trc, sizeof (PkTrcCntrl));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "action",  &(pkMngmt->t.cntrl.action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subAction",  &(pkMngmt->t.cntrl.subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "trcMask",  &(trc->trcMask));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "trcLen",  &(trc->trcLen));

   RETVOID;
} /* kwAcUtlPkBuildTrcCntrlReq */

/**
@brief Utility Function to Build Shutdown control Req 
@param tcCb
@param spCb
@param pkMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlPkBuildSDCntrlReq 
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *pkMngmt
)
#else
PUBLIC Void kwAcUtlPkBuildSDCntrlReq(tcCb,spCb,pkMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PkMngmt    *pkMngmt;
#endif
{
   PkTrcCntrl   *trc;
   trc = &(pkMngmt->t.cntrl.s.trcCntrl);
   CMXTA_ZERO(trc, sizeof (PkTrcCntrl));

   pkMngmt->t.cntrl.action = ASHUTDOWN;

   RETVOID;
} /* kwAcUtlPkBuildSDCntrlReq */

/**
@brief Utility Function to Build Debug control Req
@param tcCb
@param spCb
@param pkMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlPkBuildDbgCntrlReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *pkMngmt
)
#else
PUBLIC Void kwAcUtlPkBuildDbgCntrlReq(tcCb,spCb,pkMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PkMngmt    *pkMngmt;
#endif
{
   PkDbgCntrl   *dbg;
   dbg = &(pkMngmt->t.cntrl.s.dbgCntrl);
   CMXTA_ZERO(dbg, sizeof (PkDbgCntrl));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "action",  &(pkMngmt->t.cntrl.action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subAction",  &(pkMngmt->t.cntrl.subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dbgMask",  &(dbg->dbgMask));

   RETVOID;
} /* kwAcUtlPkBuildDbgCntrlReq */

/**
@brief Utility function for Status verification
@param tcCb
@param spCb
@param sta
@return RETVOID
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlPkVerifyStaCfm
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PkSSta        *sta
)
#else
PUBLIC S16 kwAcUtlPkVerifyStaCfm(tcCb, spCb,sta)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PkSSta        *sta;
#endif
{
   S16 elmnt = 0;
   U8 pkuSapState = 0;
   U8 cpkSapState = 0;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "elmnt",
         &elmnt);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pkuSapState",
         &pkuSapState);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cpkSapState",
         &cpkSapState);

   if(elmnt == STSID)
   {
   }
   else
   if(elmnt == STCPJSAP)
   {
       if(pkuSapState != sta->s.cpjSap.state)
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
PUBLIC S16 kwAcUtlPkVerifyStaInd
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PkUSta        *usta
)
#else
PUBLIC S16 kwAcUtlPkVerifyStaInd(tcCb, spCb,usta)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PkUSta        *usta;
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
      case PJAC_UEID:
         {
            if (ueId != usta->ueId)
               RETVALUE(CMXTA_ERR_INT);
            break;
         }
#ifdef LTE_L2_MEAS
      case PJAC_QCI:
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
       "kwAcUtlPkVerifyStaInd():Failed - MisMatch: event exp (%d) rcvd (%d) \n\
       cause exp(%d) rcvd(%d)\n",
       event, usta->alarm.event, cause, usta->alarm.cause), 2);
      RETVALUE(CMXTA_ERR_INT);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlPkVerifyStaInd */

/**
@brief Utility function for Trcce Indication 
@param tcCb
@param spCb
@param trc 
@return  - CMXTA_ERR_INT
         - CMXTA_ERR_NONE
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlPkVerifyTrcInd
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PkTrc         *trc
)
#else
PUBLIC S16 kwAcUtlPkVerifyTrcInd(tcCb, spCb,trc)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PkTrc         *trc;
#endif
{
   U16      event = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "event",
         &event);
   if (event != trc->event)
   {
      CMXTA_DBG_CALLIND((_cmxtap,
       "kwAcUtlPkVerifyStaInd():Failed - MisMatch: event exp (%d) rcvd (%d) \n",
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
PUBLIC S16 kwAcUtlPkVerifyStsCfm
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
PkSts         *sts
)
#else
PUBLIC S16 kwAcUtlPkVerifyStsCfm(tcCb, spCb,sts)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PkSts         *sts;
#endif
{
   U32 rxPdus = 0;
   U32 txPdus = 0;
   U32 pkuSduRx = 0;
   U32 pkuSduTx = 0;
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
       case STCPJSAP:
       {
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "rxSdus",
             &pkuSduRx);
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "txSdus",
             &pkuSduTx);

          if((pkuSduRx != sts->s.cpjSap.rxSdus) ||
             (pkuSduTx != sts->s.cpjSap.txSdus))
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
PUBLIC S16 kwAcUtlLpkFreeCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 kwAcUtlLpkFreeCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   KwAcMsgQElm *kwMsg;

   TRC2(kwAcUtlLpkFreeCb);

   CMXTA_DBG_PARAM((_cmxtap, "kwAcUtlLpkCb(): \n"));

   kwMsg = (KwAcMsgQElm *)qElm->data;

   if (kwMsg != NULLP)
   {
      if(kwMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(kwMsg->mBuf);

      CMXTA_FREE(kwMsg, sizeof (KwAcMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* kwAcUtlLpkFreeCb */

/**
@brief Utility Function to Build Sap control Req
@param tcCb
@param spCb
@param PkMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlPkBuildSapCntrlReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
PkMngmt     *pkMngmt
)
#else
PUBLIC Void kwAcUtlPkBuildSapCntrlReq(tcCb,spCb,pkMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
PkMngmt    *pkMngmt;
#endif
{
   PkSapCntrl     *sap;

   pkMngmt->t.cntrl.s.sapCntrl.spId = 0;
   pkMngmt->t.cntrl.s.sapCntrl.suId = 0;

   sap = &(pkMngmt->t.cntrl.s.sapCntrl);
   CMXTA_ZERO(sap, sizeof (PkSapCntrl));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "action",
         &(pkMngmt->t.cntrl.action));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subAction",
         &(pkMngmt->t.cntrl.subAction));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "spId",
         &(pkMngmt->t.cntrl.s.sapCntrl.spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "suId",
         &(pkMngmt->t.cntrl.s.sapCntrl.suId));

   RETVOID;
} /* kwAcUtlKwBuildSapCntrlReq */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
/**
@brief Utility Function to Build L2 Measurement Req 
@param tcCb
@param spCb
@param pkMngmt
@return RETVOID
*/
#ifdef ANSI
PUBLIC Void kwAcUtlLpkBuildL2MeasReq 
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PkL2MeasReqEvt *l2MeasReqEvt
)
#else
PUBLIC Void kwAcUtlLpkBuildL2MeasReq (tcCb,spCb,l2MeasReqEvt)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
PkL2MeasReqEvt *l2MeasReqEvt;
#endif
{
   /* local variables */
   PkL2MeasReqInfo *measReq;
  
   TRC2(kwAcUtlLpkBuildL2MeasReq )
   measReq   = &(l2MeasReqEvt->measReq);
   CMXTA_ZERO(measReq , sizeof (PkL2MeasReqInfo));


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
} /* kwAcUtlLpkBuildL2MeasReq */
/**
@brief Utility function for L2 measurement confirm
@param tcCb
@param spCb
@param l2MeasCfm
@return RETVOID
*/
#ifdef ANSI
PUBLIC S16 kwAcUtlLpkVldtL2MeasCfm
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
PkL2MeasCfmEvt *l2MeasCfmEvt
)
#else
PUBLIC S16 kwAcUtlLpkVldtL2MeasCfm(tcCb, spCb,l2MeasCfmEvt)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
PkL2MeasCfmEvt *l2MeasCfmEvt;
#endif
{
   U16              numCfm;
   PkL2MeasCfmInfo  *measCfm;
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
}/* end of kwAcUtlLpkVldtL2MeasCfm */
#endif

/********************************************************************30**
         End of file:     pjac_lpkutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:02 2015
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
/main/1      ---       vb        1. LTE PDCP Release 2.1.
*********************************************************************91*/

