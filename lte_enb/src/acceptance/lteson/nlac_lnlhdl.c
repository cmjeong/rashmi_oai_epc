

/********************************************************************20**

     Name:     Total eNodeB - acc test file

     Type:     C Source File

     Desc:     This file contains the acc source
               

     File:     nlac_lnlhdl.c

     Sid:      nlac_lnlhdl.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/2 - Mon Jan  5 15:41:41 2015

     Prg:      subhamay 

*********************************************************************21*/

#include <stdlib.h>        /* for atoi */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_lte.h"        /* common LTE structures */
#include "cm_xta.h"
//#include "wrac_acc.h"
#include "nl.h"
#include <stdlib.h>        /* For atoi function */
#include <string.h>        /* for strlen */
#include "lnl.h"
#include "nlu.h"
#include "nlac_acc.h"
#include "nlac_nlu.h"
/* external headers */

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_llist.x"      /* common link list */
#include "cm_lte.x"        /* common LTE structures */
#include "cm_xta.x"
//#include "cm_pasn.x"
#include "lnl.x"
#include "nlu.x"
#include "nlac_acc.x"
#include "nlac_lnl.x"
/*
*
*       Fun:   nlAcHdlLnlGenCfgReq
*
*       Desc:  Call Handler for LNL Generic config request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlGenCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlGenCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   U32           pciSelEnable = 0;
   U32           earfcnSelEnable = 0;
   U32           prachSelEnable = 0;
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;
   NlMngmt	 *cfgReq;

   U8          coupling=1;

   TRC2(nlAcHdlLnlGenCfgReq);

   #ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlGenCfgReq(), tcId (%ld)\n", tcCb->tcId));
   #else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlGenCfgReq(), tcId (%d)\n", tcCb->tcId));
   #endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   /*-- Get the Pst information here from SM to NL --*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNL, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event   = EVTLNLCFGREQ;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "pciSelEnable",  &(pciSelEnable));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "earfcnSelEnable",  &(earfcnSelEnable));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "prachSelEnable",  &(prachSelEnable));
   pst.selector = coupling;
   /* Allocate the memory for NlMngmt msg */

   CMXTA_ALLOC(&cfgReq, sizeof(NlMngmt));
	
   if(cfgReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlGenCfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Fill the data values into cfgReq */

   /* Fill the header fields */
   cfgReq->hdr.msgType             = TCFG;
   cfgReq->hdr.msgLen              = 0;
   cfgReq->hdr.entId.ent           = ENTNL;
   //cfgReq->hdr.entId.inst          = RM_INST_ZERO;
   cfgReq->hdr.entId.inst          = 0;
   cfgReq->hdr.elmId.elmnt         = STNLGEN;

   if(coupling == 1)
	   cfgReq->hdr.response.selector   = LNL_SEL_TC;
   else if(coupling == 2)
   	cfgReq->hdr.response.selector   = LNL_SEL_LWLC;

   // Fill the configuration parameters for SON General Configuration. */
   //cfgReq->t.cfg.s.genCfg.lmPst.srcProcId = NL_SM_PROC;
   //cfgReq->t.cfg.s.genCfg.lmPst.dstProcId = NL_NL_PROC;

   cfgReq->u.cfg.u.genCfg.lmPst.srcProcId = CMXTA_DFLT_PROCID;
   cfgReq->u.cfg.u.genCfg.lmPst.dstProcId = CMXTA_DFLT_PROCID;
   //cfgReq->t.cfg.s.genCfg.lmPst.srcEnt = (Ent)ENTSM;
   //cfgReq->t.cfg.s.genCfg.lmPst.dstEnt = (Ent)ENTNL;

   cfgReq->u.cfg.u.genCfg.lmPst.srcEnt = (Ent)ENTNL;
   cfgReq->u.cfg.u.genCfg.lmPst.dstEnt = (Ent)ENTSM;

   cfgReq->u.cfg.u.genCfg.lmPst.srcInst = (Inst)0;
   cfgReq->u.cfg.u.genCfg.lmPst.dstInst = (Inst)0;
   cfgReq->u.cfg.u.genCfg.lmPst.prior = (Prior)0;
   cfgReq->u.cfg.u.genCfg.lmPst.route = (Route)RTESPEC;
   cfgReq->u.cfg.u.genCfg.lmPst.event = (Event)EVTNONE;
   cfgReq->u.cfg.u.genCfg.lmPst.region =  DFLT_REGION;
   cfgReq->u.cfg.u.genCfg.lmPst.pool   =  0;
   if(coupling == 1)
   	cfgReq->u.cfg.u.genCfg.lmPst.selector = LNL_SEL_TC;
   else if (coupling == 2)
   	cfgReq->u.cfg.u.genCfg.lmPst.selector = LNL_SEL_LWLC;

   cfgReq->u.cfg.u.genCfg.mem.region = DFLT_REGION;
   cfgReq->u.cfg.u.genCfg.mem.pool   = 0;
   cfgReq->u.cfg.u.genCfg.maxNluSaps = 1;
   cfgReq->u.cfg.u.genCfg.pciSelType = pciSelEnable;
   cfgReq->u.cfg.u.genCfg.prachSelType = prachSelEnable;
   cfgReq->u.cfg.u.genCfg.earfcnSelType = earfcnSelEnable;
   
   cfgReq->u.cfg.u.genCfg.tmrRes = 1;

   /* Send the msg to the SON --*/

   if(coupling == 1)
   {  
      if(CMXTA_ERR_NONE != NlMiLnlCfgReq(&pst, cfgReq))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlGenCfgReq(): send to SON module FAILED\n"));
      }
   }
   else if(coupling == 2)
   {   
      if(CMXTA_ERR_NONE != cmPkLnlCfgReq(&pst, cfgReq))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlGenCfgReq(): packing FAILED\n"));
      }
   }
    
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcHdlLnlCfgUpdateInd
*
*       Desc:  Call Handler for LNL config update indication
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlCfgUpdateInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlCfgUpdateInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm    *msg = NULLP;
   NlAccMsgQElm    *nlMsg = NULLP;
   Pst             pst;
   S16             ret = 0;
   ProcId          srcProcId;
   ProcId          dstProcId;

   U16             retVal = LCM_PRIM_OK;
   U16             reason = LCM_REASON_NOT_APPL;
   NlCfgUpdateInd  *cfgInd = NULLP;

   TRC2(nlAcHdlLnlCfgUpdateInd);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCfgUpdateInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCfgUpdateInd(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlLnlCfgUpdateInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;


   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLNLCFGUPDATEIND;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);
   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgInd = (NlCfgUpdateInd *)(nlMsg->u.lnlInfo.data);

   if(LNL_CFG_UPDATE_PCI == cfgInd->cfgType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "PCI Update Indication received with PCI :%d \n",
                  cfgInd->u.pciCfgInd.pci), 2);
   }
   else if(LNL_CFG_UPDATE_EARFCN == cfgInd->cfgType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "EARFCN Update Indication received with DL-EARFCN :%d UL-EARFCN %d \n",
                  cfgInd->u.earfcnCfgInd.dlEarfcn, cfgInd->u.earfcnCfgInd.ulEarfcn), 2);
   }
   else if(LNL_CFG_UPDATE_PRACH == cfgInd->cfgType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "PRACH Update Indication received with RootSeqIdx :%d PrachCfgIdx %d "
                   "highSpeedFlg %d zerozonecfg %d freqoffset %d \n",
                  cfgInd->u.prachCfgInd.rootSequenceIndx, cfgInd->u.prachCfgInd.prachCfgIdx, 
                    cfgInd->u.prachCfgInd.highSpeedFlag, cfgInd->u.prachCfgInd.zeroCorrelationZoneCfg,
                         cfgInd->u.prachCfgInd.prachFreqOffset), 2);
   }
   else if(LNL_CFG_UPDATE_TXPWR == cfgInd->cfgType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Tx Power Update Indication received with RefSigPower %d \n",
                cfgInd->u.txPwrCfgInd.refSignalTxPwr), 2);
   }
   nlAcUtlLnlFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcHdlLnlStatusInd
*
*       Desc:  Call Handler for LNL Alarm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlStatusInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlStatusInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NlAccMsgQElm  *nlMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16           retVal = LCM_PRIM_OK;
   U16           reason = LCM_REASON_NOT_APPL;
   NlMngmt	 *staInd = NULLP;
   LnlNlUsta     *alarm  = NULLP;
   TRC2(nlAcHdlLnlStatusInd);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlStatusInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlStatusInd(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlLnlStatusInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;


   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLNLSTAIND;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);
   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   staInd = (NlMngmt *)(nlMsg->u.lnlInfo.data);
   if(LNL_STAT_ALARM == staInd->u.usta.staType)
   {
      alarm = &(staInd->u.usta.u.stAlarm);
      if(LNL_PCI_CONFLICT == alarm->dgn.type)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Alarm Type: %s ", "Pci Conflict"), 2);
      }
      else if (LNL_PCI_CONFUSION == alarm->dgn.type)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Alarm Type: %s ", "Pci Confusion"), 2);
      }
      if(LNL_ALARM_PCI_CONFLICT == alarm->dgn.alarmId)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Alarm Id: %s ", "Alarm Pci Conflict"), 2);
      }
      else if (LNL_ALARM_PCI_CONFUSION == alarm->dgn.alarmId)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Alarm Id: %s ", "Alarm Pci Confusion"), 2);
      }
      switch(alarm->dgn.severity)
      {
         case LNL_ALARM_SEVERITY_CLEARED :
            CMXTA_DBG_CALLIND((_cmxtap, "Alarm Severity: %s ", "Alarm Severity Cleared"), 2);
            break;
         case LNL_ALARM_SEVERITY_WARNING :
            CMXTA_DBG_CALLIND((_cmxtap, "Alarm Severity: %s ", "Alarm Severity Warning"), 2);
            break;
         case LNL_ALARM_SEVERITY_MINOR :
            CMXTA_DBG_CALLIND((_cmxtap, "Alarm Severity: %s ", "Alarm Severity Minor"), 2);
            break;
         case LNL_ALARM_SEVERITY_MAJOR :
            CMXTA_DBG_CALLIND((_cmxtap, "Alarm Severity: %s ", "Alarm Severity Major"), 2);
            break;
         case LNL_ALARM_SEVERITY_CRITICAL :
            CMXTA_DBG_CALLIND((_cmxtap, "Alarm Severity: %s ", "Alarm Severity Critical"), 2);
            break;
         default :
            break;
      }
      
      CMXTA_DBG_CALLIND((_cmxtap, "Additional Information : PCI: %d cellId %d \n", 
                                  alarm->dgn.u.addInfo.pci, alarm->dgn.u.addInfo.cellId),2);
      if(LNL_ALARM_MANUAL_INTER_REQ == alarm->dgn.u.addInfo.action)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Additional Information : Action %s \n", "manual Intervention Req"),2);
      }
      else if(LNL_ALARM_AUTO_RESOLVE == alarm->dgn.u.addInfo.action)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Additional Information : Action %s \n", "Automatic resolution"),2);
      }
   }
   nlAcUtlLnlFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcHdlLnlGenCfgCfm
*
*       Desc:  Call Handler for LNL Generic config Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlGenCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlGenCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NlAccMsgQElm  *nlMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   //SuId          suId;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16           retVal = LCM_PRIM_OK;
   U16           reason = LCM_REASON_NOT_APPL;
   NlMngmt	 *cfgCfm = NULLP;

   TRC2(nlAcHdlLnlGenCfgCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlGenCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlGenCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlLnlGenCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;


   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLNLCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);
   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (NlMngmt *)(nlMsg->u.lnlInfo.data);

   if(cfgCfm->cfm.status != retVal || cfgCfm->cfm.reason != reason )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
                  retVal, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      nlAcUtlLnlFreeCb(msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   nlAcUtlLnlFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:   nlAcHdlNluSapCfgReq
*
*       Desc:  Call Handler for NLU SAP config request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlNluSapCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlNluSapCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   //SuId          suId;             /* service user SAP identifier */
   //SpId          spId;             /* service user SAP identifier */
   //Bool          entity;
   //S16           error;
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;
   NlMngmt	 *cfgReq;
   U8            coupling = 1;

   TRC2(nlAcHdlNluSapCfgReq);

   #ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluSapCfgReq(), tcId (%ld)\n", tcCb->tcId));
   #else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluSapCfgReq(), tcId (%d)\n", tcCb->tcId));
   #endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   /*-- Get the Pst information here from SM to SON --*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNL, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event   = EVTLNLCFGREQ;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));
  
   /* Allocate the memory for NlMngmt msg */

   CMXTA_ALLOC(&cfgReq, sizeof(NlMngmt));
	
   if(cfgReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"nlAcHdlNluSapCfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Fill the data values into cfgReq */
	
   /*Fill the header fields*/

   cfgReq->hdr.msgType		= TCFG;
   cfgReq->hdr.msgLen              = 0;
   cfgReq->hdr.entId.ent           = ENTNL;
   cfgReq->hdr.entId.inst          = 0;
   cfgReq->hdr.elmId.elmnt         = STNLUSAP;

   cfgReq->hdr.response.selector   = NLU_SEL_TC;
   cfgReq->u.cfg.u.nluSap.spId	      = WR_NL_SPID;
   cfgReq->u.cfg.u.nluSap.suId 	      = WR_NL_SUID;
   cfgReq->u.cfg.u.nluSap.procId      = SM_NL_PROC;
   cfgReq->u.cfg.u.nluSap.prior       = PRIOR0;
   cfgReq->u.cfg.u.nluSap.route       = RTESPEC;
   cfgReq->u.cfg.u.nluSap.selector    = coupling;
   cfgReq->u.cfg.u.nluSap.ent         = ENTWR;
   cfgReq->u.cfg.u.nluSap.inst        = 0;
   cfgReq->u.cfg.u.nluSap.mem.pool    = 0;
   cfgReq->u.cfg.u.nluSap.mem.region  = DFLT_REGION;

   /* Send the msg to the SON --*/

   if(cfgReq->hdr.response.selector == 1)
   {
      if(CMXTA_ERR_NONE != NlMiLnlCfgReq(&pst, cfgReq))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlNluSapCfgReq(): send to SON module FAILED\n"));
      }
   }
   else if(cfgReq->hdr.response.selector == 2)
   {
      if(CMXTA_ERR_NONE != cmPkLnlCfgReq(&pst, cfgReq))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlNluSapCfgReq(): send to SON module FAILED\n"));
      }
   }   

   RETVALUE(CMXTA_ERR_NONE);

}


/*
*
*       Fun:   nlAcHdlNluSapCfgCfm
*
*       Desc:  Call Handler for LNL SAP config Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlNluSapCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlNluSapCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NlAccMsgQElm  *nlMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   //SuId          suId;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16           retVal = LCM_PRIM_OK;
   U16           reason = LCM_REASON_NOT_APPL;
   NlMngmt	 *cfgCfm;

   TRC2(nlAcHdlNluSapCfgCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluSapCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluSapCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlNluSapCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   nlMsg = (NlAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLNLCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (NlMngmt *)(nlMsg->u.lnlInfo.data);

   if(cfgCfm->cfm.status != retVal || cfgCfm->cfm.reason != reason )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
            retVal, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      nlAcUtlLnlFreeCb(msg);
      RETVALUE(CMXTA_ERR_INT);

   }

   /*-- free memory, use callback function --*/
   nlAcUtlLnlFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   nlAcHdlNluSapCfgFail
*
*       Desc:  Call Handler for LNL SAP config Fail
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlNluSapCfgFail
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlNluSapCfgFail(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NlAccMsgQElm  *nlMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   //SuId          suId;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16           retVal = LCM_PRIM_OK;
   U16           reason = LCM_REASON_NOT_APPL;
   NlMngmt	 *cfgCfm;

   TRC2(nlAcHdlNluSapCfgFail);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluSapCfgFail(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlNluSapCfgFail(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlNluSapCfgFail(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   nlMsg = (NlAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLNLCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (NlMngmt *)(nlMsg->u.lnlInfo.data);

   if(cfgCfm->cfm.status == retVal || cfgCfm->cfm.reason == reason )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
            retVal, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      nlAcUtlLnlFreeCb(msg);
      RETVALUE(CMXTA_ERR_INT);

   }

   /*-- free memory, use callback function --*/
   nlAcUtlLnlFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   nlAcBuildPrachCfg
*
*       Desc:  build the PRACH configurations
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildPrachCfg
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
LnlPrachCfg  *prachCfg
)
#else
PRIVATE S16 nlAcBuildPrachCfg(tcCb, spCb, prachCfg)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
LnlPrachCfg  *prachCfg;
#endif
{
   S16       ret = 0;
   U32       count;
   U16       rootSeqIdx[5];
   U8        prachConfigIdx[5];
   U8        zeroCorrelationZoneCfg[5];
   U8        freqOffset[5];
   TRC2(nlAcBuildPrachCfg);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numRootSeqIndex",  &(prachCfg->numRootSeqIndex));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "rootSeqIdx_0",  &(rootSeqIdx[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "rootSeqIdx_1",  &(rootSeqIdx[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "rootSeqIdx_2",  &(rootSeqIdx[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "rootSeqIdx_3",  &(rootSeqIdx[3]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "rootSeqIdx_4",  &(rootSeqIdx[4]));
   for(count = 0; count < prachCfg->numRootSeqIndex; count ++)
   {
      prachCfg->rootSeqIdx[count] = rootSeqIdx[count];
   }
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numPrachCfgIdx",  &(prachCfg->numPrachCfgIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "prachConfigIdx_0",  &(prachConfigIdx[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "prachConfigIdx_1",  &(prachConfigIdx[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "prachConfigIdx_2",  &(prachConfigIdx[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "prachConfigIdx_3",  &(prachConfigIdx[3]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "prachConfigIdx_4",  &(prachConfigIdx[4]));
   for(count = 0; count < prachCfg->numPrachCfgIdx; count ++)
   {
      prachCfg->prachConfigIdx[count] = prachConfigIdx[count];
   }
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numZeroCorrCfgZone",  &(prachCfg->numZeroCorrCfgZone));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "zeroCorrelationZoneCfg_0",  &(zeroCorrelationZoneCfg[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "zeroCorrelationZoneCfg_1",  &(zeroCorrelationZoneCfg[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "zeroCorrelationZoneCfg_2",  &(zeroCorrelationZoneCfg[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "zeroCorrelationZoneCfg_3",  &(zeroCorrelationZoneCfg[3]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "zeroCorrelationZoneCfg_4",  &(zeroCorrelationZoneCfg[4]));
   for(count = 0; count < prachCfg->numZeroCorrCfgZone; count ++)
   {
      prachCfg->zeroCorrelationZoneCfg[count] = zeroCorrelationZoneCfg[count];
   }
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numFreqOffset",  &(prachCfg->numFreqOffset));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "freqOffset_0",  &(freqOffset[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "freqOffset_1",  &(freqOffset[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "freqOffset_2",  &(freqOffset[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "freqOffset_3",  &(freqOffset[3]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "freqOffset_4",  &(freqOffset[4]));
   for(count = 0; count < prachCfg->numFreqOffset; count ++)
   {
      prachCfg->freqOffset[count] = freqOffset[count];
   }
   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nlAcHdlLnlCellCfgReq
*
*       Desc:  Call Handler for cell config request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlCellCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlCellCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;
   NlMngmt	 *cfgReq;
   LnlCellCfg    *cellCfg ;
   U8            coupling = 1;
   U16           pciList[15];
   U8            numDlEarfcn;
   U32           dlEarfcn[10];
   U8            numUlEarfcn;
   U32           ulEarfcn[10];
   U8            numRemEarfcn;
   U32           remDlEarfcn[2];
   U32           remRssi[2];
   U8            count;

   TRC2(nlAcHdlLnlCellCfgReq);

   #ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCellCfgReq(), tcId (%ld)\n", tcCb->tcId));
   #else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCellCfgReq(), tcId (%d)\n", tcCb->tcId));
   #endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   /*-- Get the Pst information here from SM to SON --*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNL, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event   = EVTLNLCFGREQ;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));

   pst.selector = coupling;

   /* Allocate the memory for NlMngmt msg */

   CMXTA_ALLOC(&cfgReq, sizeof(NlMngmt));
	
   if(cfgReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlCellCfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Fill the data values into cfgReq */
	
   /*Fill the header fields*/

   cfgReq->hdr.msgType		   = TCFG;
   cfgReq->hdr.msgLen              = 0;
   cfgReq->hdr.entId.ent           = ENTNL;
   cfgReq->hdr.entId.inst          = 0;
   cfgReq->hdr.elmId.elmnt         = STNLPROTOCFG;
   cfgReq->u.protoCfg.bCfgType = LNL_CELL_CFG;
   cellCfg = &(cfgReq->u.protoCfg.u.cellCfg);

   if(coupling == 1)
      cfgReq->hdr.response.selector   = NLU_SEL_TC;
   else if(coupling == 2)
      cfgReq->hdr.response.selector   = NLU_SEL_LWLC;   

   /* fill the Cell configuration parameters*/

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "cellId",  &(cellCfg->cellId));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "bandWidth",  &(cellCfg->bandWidth));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "antPorts",  &(cellCfg->numTxAntPorts));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mcc_0",  &(cellCfg->ecgi.plmn.mcc[0]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mcc_1",  &(cellCfg->ecgi.plmn.mcc[1]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mcc_2",  &(cellCfg->ecgi.plmn.mcc[2]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mnc_0",  &(cellCfg->ecgi.plmn.mnc[0]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mnc_1",  &(cellCfg->ecgi.plmn.mnc[1]));
   cellCfg->ecgi.cellId = cellCfg->cellId;
   cellCfg->ecgi.plmn.numMncDigits = 2;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "txPower",  &(cellCfg->txPower));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "subFrameCfg",  &(cellCfg->subFrameCfg));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci",  &(cellCfg->pci));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numPci",  &(cellCfg->numPci));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_0",  &(pciList[0]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_1",  &(pciList[1]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_2",  &(pciList[2]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_3",  &(pciList[3]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_4",  &(pciList[4]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_5",  &(pciList[5]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_6",  &(pciList[6]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_7",  &(pciList[7]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_8",  &(pciList[8]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_9",  &(pciList[9]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numDlEarfcn",  &(numDlEarfcn));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlEarfcn_0",  &(dlEarfcn[0]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlEarfcn_1",  &(dlEarfcn[1]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlEarfcn_2",  &(dlEarfcn[2]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlEarfcn_3",  &(dlEarfcn[3]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "dlEarfcn_4",  &(dlEarfcn[4]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numUlEarfcn",  &(numUlEarfcn));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ulEarfcn_0",  &(ulEarfcn[0]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ulEarfcn_1",  &(ulEarfcn[1]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ulEarfcn_2",  &(ulEarfcn[2]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ulEarfcn_3",  &(ulEarfcn[3]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ulEarfcn_4",  &(ulEarfcn[4]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numRemEarfcn",  &(numRemEarfcn));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "rem_dlEarfcn_0",  &(remDlEarfcn[0]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "rem_rssi_0",  &(remRssi[0]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "rem_dlEarfcn_1",  &(remDlEarfcn[1]));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "rem_rssi_1",  &(remRssi[1]));   
   for(count = 0; count < cellCfg->numPci; count ++)
   {
      cellCfg->pciList[count] = pciList[count];
   }
   cellCfg->numDlEarfcn = numDlEarfcn;
   for(count = 0; count < numDlEarfcn; count ++)
   {
      cellCfg->dlEarfcnList[count] = dlEarfcn[count];
   }
   cellCfg->numUlEarfcn = numUlEarfcn;
   for(count = 0; count < numUlEarfcn; count ++)
   {
      cellCfg->ulEarfcnList[count] = ulEarfcn[count];
   }
   cellCfg->numRemScanEarfcn = numRemEarfcn;
   for(count = 0; count < numRemEarfcn; count ++)
   {
      cellCfg->remScanEarfcn[count].dlEarfcn = remDlEarfcn[count];
      cellCfg->remScanEarfcn[count].rssi = remRssi[count];
   }

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "isCpUlExtend",  &(cellCfg->isCpUlExtend));   
   nlAcBuildPrachCfg(tcCb, spCb, &cellCfg->prachCfgInfo);

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "pucchCqiResIdx",  &(cellCfg->pucchResCfg.pucchCqiResIdx));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "n1PucchAn",  &(cellCfg->pucchResCfg.n1PucchAn));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "deltaShift",  &(cellCfg->pucchResCfg.deltaShift));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "cyclicShift",  &(cellCfg->pucchResCfg.cyclicShift));   

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "ngEnum",  &(cellCfg->phichCfg.ngEnum));   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "isDurExtend",  &(cellCfg->phichCfg.isDurExtend));  
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "isCsgPciCfg",  &(cellCfg->csgPciCfg.isCsgPciCfg));  
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "csgStartPci",  &(cellCfg->csgPciCfg.csgStartPci));  
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "csgRange",  &(cellCfg->csgPciCfg.csgPciRange));  
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "csgMode",  &(cellCfg->csgPciCfg.accessMode));  
    
   /* Send the msg to the SON --*/
   if(coupling == 1)
   {
      if(CMXTA_ERR_NONE != NlMiLnlCfgReq(&pst, cfgReq))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlCellCfgReq(): send to SON module FAILED\n"));
      }
   }
   else if(coupling == 2)
   {
      if(CMXTA_ERR_NONE != cmPkLnlCfgReq(&pst, cfgReq))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlCellCfgReq(): send to SON module FAILED\n"));
      }
   }   

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcHdlLnlCellCfgCfm
*
*       Desc:  Call Handler for LNL cell config Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlCellCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlCellCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NlAccMsgQElm  *nlMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   //SuId          suId;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16           retVal = LCM_PRIM_OK;
   U16           reason = LCM_REASON_NOT_APPL;
   NlMngmt	 *cfgCfm;

   TRC2(nlAcHdlLnlCellCfgCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCellCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCellCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlLnlCellCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   nlMsg = (NlAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLNLCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (NlMngmt *)(nlMsg->u.lnlInfo.data);

   if(cfgCfm->cfm.status != retVal || cfgCfm->cfm.reason != reason )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
            retVal, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      nlAcUtlLnlFreeCb(msg);
      RETVALUE(CMXTA_ERR_INT);

   }
   /*-- free memory, use callback function --*/
   nlAcUtlLnlFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   nlAcHdlLnlCellCfgFail
*
*       Desc:  Call Handler for LNL cell config failure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlCellCfgFail
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlCellCfgFail(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NlAccMsgQElm  *nlMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   //SuId          suId;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16           retVal = LCM_PRIM_OK;
   U16           reason = LCM_REASON_NOT_APPL;
   NlMngmt	 *cfgCfm;

   TRC2(nlAcHdlLnlCellCfgFail);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCellCfgFail(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCellCfgFail(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlLnlCellCfgFail(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   nlMsg = (NlAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLNLCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (NlMngmt *)(nlMsg->u.lnlInfo.data);

   if(cfgCfm->cfm.status == retVal || cfgCfm->cfm.reason == reason )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
            retVal, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      nlAcUtlLnlFreeCb(msg);
      RETVALUE(CMXTA_ERR_INT);

   }
   /*-- free memory, use callback function --*/
   nlAcUtlLnlFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   nlAcBuildEnbOneOneNghNghCellAdd
*
*       Desc:  build neighbor eNodeB one ngh ngh cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildEnbOneOneNghNghCellAdd
(
LnlNghCellAddInfo *cellAddInfo,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildEnbOneOneNghNghCellAdd(cellAddInfo, tcCb, spCb)
LnlNghCellAddInfo *cellAddInfo;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   LnlNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   TRC3(nlAcBuildEnbOneOneNghNghCellAdd);
   nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_0_pci",  &(nghNghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildEnbOneTwoNghNghCellAdd
*
*       Desc:  build neighbor eNodeB two ngh ngh cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildEnbOneTwoNghNghCellAdd
(
LnlNghCellAddInfo *cellAddInfo,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildEnbOneTwoNghNghCellAdd(cellAddInfo, tcCb, spCb)
LnlNghCellAddInfo *cellAddInfo;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   LnlNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   TRC3(nlAcBuildEnbOneTwoNghNghCellAdd);
   nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_0_pci",  &(nghNghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));

   nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[1]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_1_pci",  &(nghNghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_1_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_0_nghNgh_1_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nlAcBuildEnbZeroOneNghNghCellAdd
*
*       Desc:  build neighbor eNodeB one ngh ngh cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildEnbZeroOneNghNghCellAdd
(
LnlNghCellAddInfo *cellAddInfo,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildEnbZeroOneNghNghCellAdd(cellAddInfo, tcCb, spCb)
LnlNghCellAddInfo *cellAddInfo;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   LnlNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   TRC3(nlAcBuildEnbZeroOneNghNghCellAdd);
   nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_0_pci",  &(nghNghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildEnbZeroTwoNghNghCellAdd
*
*       Desc:  build neighbor eNodeB two ngh ngh cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildEnbZeroTwoNghNghCellAdd
(
LnlNghCellAddInfo *cellAddInfo,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildEnbZeroTwoNghNghCellAdd(cellAddInfo, tcCb, spCb)
LnlNghCellAddInfo *cellAddInfo;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   LnlNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   TRC3(nlAcBuildEnbZeroTwoNghNghCellAdd);
   nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_0_pci",  &(nghNghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));

   nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[1]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_1_pci",  &(nghNghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_1_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_0_nghNgh_1_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbOneOneServCellAdd
*
*       Desc:  build neighbor eNodeB one serv cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbOneOneServCellAdd
(
LnlNghCellAdd     *cellAdd,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbOneOneServCellAdd(cellAdd, tcCb, spCb)
LnlNghCellAdd     *cellAdd;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   LnlNghCellAddInfo *cellAddInfo = NULLP;
   LnlNghCellInfo    *nghCellInfo = NULLP;

   S16               ret = 0;
   TRC3(nlAcBuildNghEnbOneOneServCellAdd);
   cellAddInfo = &(cellAdd->nghCellAddInfo[0]);
   nghCellInfo = &(cellAddInfo->nghCellInfo);

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_add_0_cellId",  &(nghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mcc_0",  &(nghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mcc_1",  &(nghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mcc_2",  &(nghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mnc_0",  &(nghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mnc_1",  &(nghCellInfo->ecgi.plmn.mnc[1]));
   nghCellInfo->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_pci",  &(nghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_dlEarfcn",  &(nghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_ulEarfcn",  &(nghCellInfo->ulEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_numNghNgh",  &(cellAddInfo->numNghNgh));

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_add_0_isNghPrachInfo",  &(nghCellInfo->isNghPrachInfo));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_nghRootSeqIdx",  &(nghCellInfo->prachCfgInfo.nghRootSeqIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_nghPrachCfgIdx",  &(nghCellInfo->prachCfgInfo.nghPrachCfgIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_nghZeroCorrelationZoneCfg",
                                                     &(nghCellInfo->prachCfgInfo.nghZeroCorrelationZoneCfg));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_nghPrachFreqOffset",  &(nghCellInfo->prachCfgInfo.nghPrachFreqOffset));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_add_0_highSpeedFlag",  &(nghCellInfo->prachCfgInfo.highSpeedFlag)); 

   if(1 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbOneOneNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }
   else if(2 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbOneTwoNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }
   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nlAcBuildNghEnbZeroOneServCellAdd
*
*       Desc:  build neighbor eNodeB one serv cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbZeroOneServCellAdd
(
LnlNghCellAdd     *cellAdd,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbZeroOneServCellAdd(cellAdd, tcCb, spCb)
LnlNghCellAdd     *cellAdd;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   LnlNghCellAddInfo *cellAddInfo = NULLP;
   LnlNghCellInfo    *nghCellInfo = NULLP;

   S16               ret = 0;
   TRC3(nlAcBuildNghEnbZeroOneServCellAdd);
   cellAddInfo = &(cellAdd->nghCellAddInfo[0]);
   nghCellInfo = &(cellAddInfo->nghCellInfo);

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_0_cellId",  &(nghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mcc_0",  &(nghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mcc_1",  &(nghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mcc_2",  &(nghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mnc_0",  &(nghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mnc_1",  &(nghCellInfo->ecgi.plmn.mnc[1]));
   nghCellInfo->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_pci",  &(nghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_dlEarfcn",  &(nghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_ulEarfcn",  &(nghCellInfo->ulEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_numNghNgh",  &(cellAddInfo->numNghNgh));

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_0_isNghPrachInfo",  &(nghCellInfo->isNghPrachInfo));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_nghRootSeqIdx",  &(nghCellInfo->prachCfgInfo.nghRootSeqIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghPrachCfgIdx",  &(nghCellInfo->prachCfgInfo.nghPrachCfgIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghZeroCorrelationZoneCfg",  
                                                     &(nghCellInfo->prachCfgInfo.nghZeroCorrelationZoneCfg));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghPrachFreqOffset",  &(nghCellInfo->prachCfgInfo.nghPrachFreqOffset));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_0_highSpeedFlag",  &(nghCellInfo->prachCfgInfo.highSpeedFlag));
   if(1 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbZeroOneNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }
   else if(2 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbZeroTwoNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbOneTwoServCellCfg
*
*       Desc:  build neighbor eNodeB two serv cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbOneTwoServCellAdd
(
LnlNghCellAdd     *cellAdd,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuilNghEnbOneTwoServCellAdd(cellAdd, tcCb, spCb)
LnlNghCellAdd     *cellAdd;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   LnlNghCellAddInfo *cellAddInfo = NULLP;
   LnlNghCellInfo    *nghCellInfo = NULLP;
   LnlNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   TRC3(nlAcBuildNghEnbOneTwoServCellAdd);
   cellAddInfo = &(cellAdd->nghCellAddInfo[0]);
   nghCellInfo = &(cellAddInfo->nghCellInfo);

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_add_0_cellId",  &(nghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mcc_0",  &(nghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mcc_1",  &(nghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mcc_2",  &(nghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mnc_0",  &(nghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_mnc_1",  &(nghCellInfo->ecgi.plmn.mnc[1]));
   nghCellInfo->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_pci",  &(nghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_dlEarfcn",  &(nghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_ulEarfcn",  &(nghCellInfo->ulEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_numNghNgh",  &(cellAddInfo->numNghNgh));

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_add_0_isNghPrachInfo",  &(nghCellInfo->isNghPrachInfo));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_0_nghRootSeqIdx",  &(nghCellInfo->prachCfgInfo.nghRootSeqIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_nghPrachCfgIdx",  &(nghCellInfo->prachCfgInfo.nghPrachCfgIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_nghZeroCorrelationZoneCfg",
                                                     &(nghCellInfo->prachCfgInfo.nghZeroCorrelationZoneCfg));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_0_nghPrachFreqOffset",  &(nghCellInfo->prachCfgInfo.nghPrachFreqOffset));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_add_0_highSpeedFlag",  &(nghCellInfo->prachCfgInfo.highSpeedFlag));


   if(1 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbOneOneNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }
   else if(2 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbOneTwoNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }

   cellAddInfo = &(cellAdd->nghCellAddInfo[1]);
   nghCellInfo = &(cellAddInfo->nghCellInfo);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_add_1_cellId",  &(nghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_mcc_0",  &(nghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_mcc_1",  &(nghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_mcc_2",  &(nghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_mnc_0",  &(nghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_mnc_1",  &(nghCellInfo->ecgi.plmn.mnc[1]));
   nghCellInfo->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_1_pci",  &(nghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_1_dlEarfcn",  &(nghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_1_ulEarfcn",  &(nghCellInfo->ulEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_numNghNgh",  &(cellAddInfo->numNghNgh));
   
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_add_1_isNghPrachInfo",  &(nghCellInfo->isNghPrachInfo));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_add_1_nghRootSeqIdx",  &(nghCellInfo->prachCfgInfo.nghRootSeqIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_nghPrachCfgIdx",  &(nghCellInfo->prachCfgInfo.nghPrachCfgIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_nghZeroCorrelationZoneCfg",
                                                     &(nghCellInfo->prachCfgInfo.nghZeroCorrelationZoneCfg));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_add_1_nghPrachFreqOffset",  &(nghCellInfo->prachCfgInfo.nghPrachFreqOffset));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_add_1_highSpeedFlag",  &(nghCellInfo->prachCfgInfo.highSpeedFlag));


   if(1 == cellAddInfo->numNghNgh)
   {
      nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_0_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn)); 
   }
   else if(2 == cellAddInfo->numNghNgh)
   {
      nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_0_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
      nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[1]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_1_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_1_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_1_add_1_nghNgh_1_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   }
   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nlAcBuildNghEnbZeroTwoServCellCfg
*
*       Desc:  build neighbor eNodeB two serv cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbZeroTwoServCellAdd
(
LnlNghCellAdd     *cellAdd,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuilNghEnbZeroTwoServCellAdd(cellAdd, tcCb, spCb)
LnlNghCellAdd     *cellAdd;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   LnlNghCellAddInfo *cellAddInfo = NULLP;
   LnlNghCellInfo    *nghCellInfo = NULLP;
   LnlNghCellInfo    *nghNghCellInfo = NULLP;
   S16               ret = 0;
   TRC3(nlAcBuildNghEnbZeroTwoServCellAdd);
   cellAddInfo = &(cellAdd->nghCellAddInfo[0]);
   nghCellInfo = &(cellAddInfo->nghCellInfo);

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_0_cellId",  &(nghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mcc_0",  &(nghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mcc_1",  &(nghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mcc_2",  &(nghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mnc_0",  &(nghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_mnc_1",  &(nghCellInfo->ecgi.plmn.mnc[1]));
   nghCellInfo->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_pci",  &(nghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_dlEarfcn",  &(nghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_ulEarfcn",  &(nghCellInfo->ulEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_numNghNgh",  &(cellAddInfo->numNghNgh));

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_0_isNghPrachInfo",  &(nghCellInfo->isNghPrachInfo));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_0_nghRootSeqIdx",  &(nghCellInfo->prachCfgInfo.nghRootSeqIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghPrachCfgIdx",  &(nghCellInfo->prachCfgInfo.nghPrachCfgIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghZeroCorrelationZoneCfg",
                                                     &(nghCellInfo->prachCfgInfo.nghZeroCorrelationZoneCfg));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_0_nghPrachFreqOffset",  &(nghCellInfo->prachCfgInfo.nghPrachFreqOffset));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_0_highSpeedFlag",  &(nghCellInfo->prachCfgInfo.highSpeedFlag));


   if(1 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbZeroOneNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }
   else if(2 == cellAddInfo->numNghNgh)
   {
      nlAcBuildEnbZeroTwoNghNghCellAdd(cellAddInfo, tcCb, spCb);
   }

   cellAddInfo = &(cellAdd->nghCellAddInfo[1]);
   nghCellInfo = &(cellAddInfo->nghCellInfo);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_1_cellId",  &(nghCellInfo->ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_mcc_0",  &(nghCellInfo->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_mcc_1",  &(nghCellInfo->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_mcc_2",  &(nghCellInfo->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_mnc_0",  &(nghCellInfo->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_mnc_1",  &(nghCellInfo->ecgi.plmn.mnc[1]));
   nghCellInfo->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_1_pci",  &(nghCellInfo->pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_1_dlEarfcn",  &(nghCellInfo->dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_1_ulEarfcn",  &(nghCellInfo->ulEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_numNghNgh",  &(cellAddInfo->numNghNgh));

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_1_isNghPrachInfo",  &(nghCellInfo->isNghPrachInfo));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_add_1_nghRootSeqIdx",  &(nghCellInfo->prachCfgInfo.nghRootSeqIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_nghPrachCfgIdx",  &(nghCellInfo->prachCfgInfo.nghPrachCfgIdx));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_nghZeroCorrelationZoneCfg",
                                                     &(nghCellInfo->prachCfgInfo.nghZeroCorrelationZoneCfg));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_add_1_nghPrachFreqOffset",  &(nghCellInfo->prachCfgInfo.nghPrachFreqOffset));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_add_1_highSpeedFlag",  &(nghCellInfo->prachCfgInfo.highSpeedFlag));


   if(1 == cellAddInfo->numNghNgh)
   {
      nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_0_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn)); 
   }
   else if(2 == cellAddInfo->numNghNgh)
   {
      nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[0]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_0_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_0_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_0_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
      nghNghCellInfo = &(cellAddInfo->nghNghCellInfo[1]);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_1_pci",  &(nghNghCellInfo->pci));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_1_dlEarfcn",  &(nghNghCellInfo->dlEarfcn));
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
                     "nghEnbId_0_add_1_nghNgh_1_ulEarfcn",  &(nghNghCellInfo->ulEarfcn));
   }
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbOneOneServCellDel
*
*       Desc:  build neighbor eNodeB 1 cell delete config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbOneOneServCellDel
(
LnlNghCellDel     *cellDel,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbOneOneServCellDel(cellDel, tcCb, spCb)
LnlNghCellDel     *cellDel;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16               ret = 0;
   TRC3(nlAcBuildNghEnbOneOneServCellDel);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_del_0_cellId",  &(cellDel->ecgi[0].cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mcc_0",  &(cellDel->ecgi[0].plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mcc_1",  &(cellDel->ecgi[0].plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mcc_2",  &(cellDel->ecgi[0].plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mnc_0",  &(cellDel->ecgi[0].plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mnc_1",  &(cellDel->ecgi[0].plmn.mnc[1]));
   cellDel->ecgi[0].plmn.numMncDigits = 2;
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbOneTwoServCellDel
*
*       Desc:  build neighbor eNodeB 2 cell delete config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbOneTwoServCellDel
(
LnlNghCellDel     *cellDel,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbOneTwoServCellDel(cellDel, tcCb, spCb)
LnlNghCellDel     *cellDel;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16               ret = 0;
   TRC3(nlAcBuildNghEnbOneTwoServCellDel);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_del_0_cellId",  &(cellDel->ecgi[0].cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mcc_0",  &(cellDel->ecgi[0].plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mcc_1",  &(cellDel->ecgi[0].plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mcc_2",  &(cellDel->ecgi[0].plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mnc_0",  &(cellDel->ecgi[0].plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_0_mnc_1",  &(cellDel->ecgi[0].plmn.mnc[1]));
   cellDel->ecgi[0].plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_del_1_cellId",  &(cellDel->ecgi[1].cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_1_mcc_0",  &(cellDel->ecgi[1].plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_1_mcc_1",  &(cellDel->ecgi[1].plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_1_mcc_2",  &(cellDel->ecgi[1].plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_1_mnc_0",  &(cellDel->ecgi[1].plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_del_1_mnc_1",  &(cellDel->ecgi[1].plmn.mnc[1]));
   cellDel->ecgi[1].plmn.numMncDigits = 2;
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbOneOneServCellMod
*
*       Desc:  build neighbor eNodeB 1 cell modify config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbOneOneServCellMod
(
LnlNghCellMod     *cellMod,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbOneOneServCellMod(cellMod, tcCb, spCb)
LnlNghCellMod     *cellMod;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16               ret = 0;
   LnlNghCellModInfo *cellModInfo = NULLP;
   TRC3(nlAcBuildNghEnbOneOneServCellMod);
   cellModInfo = &(cellMod->nghCellModInfo[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_mod_0_old_cellId",  &(cellModInfo->oldEcgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_old_mcc_0",  &(cellModInfo->oldEcgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_old_mcc_1",  &(cellModInfo->oldEcgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_old_mcc_2",  &(cellModInfo->oldEcgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_old_mnc_0",  &(cellModInfo->oldEcgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_old_mnc_1",  &(cellModInfo->oldEcgi.plmn.mnc[1]));
   cellModInfo->oldEcgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_mod_0_cellId",  &(cellModInfo->nghCellInfo.ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_mcc_0",  &(cellModInfo->nghCellInfo.ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_mcc_1",  &(cellModInfo->nghCellInfo.ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_mcc_2",  &(cellModInfo->nghCellInfo.ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_mnc_0",  &(cellModInfo->nghCellInfo.ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_mod_0_mnc_1",  &(cellModInfo->nghCellInfo.ecgi.plmn.mnc[1]));
   cellModInfo->nghCellInfo.ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_mod_0_pci",  &(cellModInfo->nghCellInfo.pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_mod_0_dlEarfcn",  &(cellModInfo->nghCellInfo.dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_1_mod_0_ulEarfcn",  &(cellModInfo->nghCellInfo.ulEarfcn));
   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nlAcBuildNghEnbZeroOneServCellDel
*
*       Desc:  build neighbor eNodeB 1 cell delete config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbZeroOneServCellDel
(
LnlNghCellDel     *cellDel,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbZeroOneServCellDel(cellDel, tcCb, spCb)
LnlNghCellDel     *cellDel;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16               ret = 0;
   TRC3(nlAcBuildNghEnbZeroOneServCellDel);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_del_0_cellId",  &(cellDel->ecgi[0].cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mcc_0",  &(cellDel->ecgi[0].plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mcc_1",  &(cellDel->ecgi[0].plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mcc_2",  &(cellDel->ecgi[0].plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mnc_0",  &(cellDel->ecgi[0].plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mnc_1",  &(cellDel->ecgi[0].plmn.mnc[1]));
   cellDel->ecgi[0].plmn.numMncDigits = 2;
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbZeroTwoServCellDel
*
*       Desc:  build neighbor eNodeB 2 cell delete config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbZeroTwoServCellDel
(
LnlNghCellDel     *cellDel,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbZeroTwoServCellDel(cellDel, tcCb, spCb)
LnlNghCellDel     *cellDel;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16               ret = 0;
   TRC3(nlAcBuildNghEnbZeroTwoServCellDel);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_del_0_cellId",  &(cellDel->ecgi[0].cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mcc_0",  &(cellDel->ecgi[0].plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mcc_1",  &(cellDel->ecgi[0].plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mcc_2",  &(cellDel->ecgi[0].plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mnc_0",  &(cellDel->ecgi[0].plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_0_mnc_1",  &(cellDel->ecgi[0].plmn.mnc[1]));
   cellDel->ecgi[0].plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_del_1_cellId",  &(cellDel->ecgi[1].cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_1_mcc_0",  &(cellDel->ecgi[1].plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_1_mcc_1",  &(cellDel->ecgi[1].plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_1_mcc_2",  &(cellDel->ecgi[1].plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_1_mnc_0",  &(cellDel->ecgi[1].plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_del_1_mnc_1",  &(cellDel->ecgi[1].plmn.mnc[1]));
   cellDel->ecgi[1].plmn.numMncDigits = 2;
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildNghEnbZeroOneServCellMod
*
*       Desc:  build neighbor eNodeB 1 cell modify config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildNghEnbZeroOneServCellMod
(
LnlNghCellMod     *cellMod,
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb
)
#else
PRIVATE S16 nlAcBuildNghEnbZeroOneServCellMod(cellMod, tcCb, spCb)
LnlNghCellMod     *cellMod;
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
#endif
{
   S16               ret = 0;
   LnlNghCellModInfo *cellModInfo = NULLP;
   TRC3(nlAcBuildNghEnbZeroOneServCellMod);
   cellModInfo = &(cellMod->nghCellModInfo[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_mod_0_old_cellId",  &(cellModInfo->oldEcgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_old_mcc_0",  &(cellModInfo->oldEcgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_old_mcc_1",  &(cellModInfo->oldEcgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_old_mcc_2",  &(cellModInfo->oldEcgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_old_mnc_0",  &(cellModInfo->oldEcgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_old_mnc_1",  &(cellModInfo->oldEcgi.plmn.mnc[1]));
   cellModInfo->oldEcgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_mod_0_cellId",  &(cellModInfo->nghCellInfo.ecgi.cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_mcc_0",  &(cellModInfo->nghCellInfo.ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_mcc_1",  &(cellModInfo->nghCellInfo.ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_mcc_2",  &(cellModInfo->nghCellInfo.ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_mnc_0",  &(cellModInfo->nghCellInfo.ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_mod_0_mnc_1",  &(cellModInfo->nghCellInfo.ecgi.plmn.mnc[1]));
   cellModInfo->nghCellInfo.ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_pci",  &(cellModInfo->nghCellInfo.pci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_dlEarfcn",  &(cellModInfo->nghCellInfo.dlEarfcn));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "nghEnbId_0_mod_0_ulEarfcn",  &(cellModInfo->nghCellInfo.ulEarfcn));
   RETVALUE(CMXTA_ERR_NONE);
}
/*
*
*       Fun:   nlAcBuildOneNghEnbCellCfg
*
*       Desc:  build neighbor eNodeB cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildOneNghEnbCellCfg
(
LnlNghCellCfg    *nghCellCfg,
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb
)
#else
PRIVATE S16 nlAcBuildOneNghEnbCellCfg(nghCellCfg, tcCb, spCb)
LnlNghCellCfg    *nghCellCfg;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   S16               ret = 0;
   LnlNghEnbCellCfg *enbCfg = NULLP;
   LnlNghCellAdd     *cellAdd = NULLP;
   LnlNghCellMod     *cellMod = NULLP; 
   LnlNghCellDel     *cellDel = NULLP;
   LnlNghCellAddInfo *cellAddInfo = NULLP;
   LnlNghCellInfo    *nghCellInfo = NULLP;
   LnlNghCellInfo    *nghNghCellInfo = NULLP;
   TRC3(nlAcBuildOneNghEnbCellCfg);
   enbCfg = &(nghCellCfg->nghEnbCellCfg[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0",  &(enbCfg->nghEnbId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_cfgType",  &(enbCfg->nghCellParam.cfgType));
   if(LNL_NGH_ADD == enbCfg->nghCellParam.cfgType)
   {
      cellAdd = &(enbCfg->nghCellParam.u.nghCellAdd);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_numAdd",  &(cellAdd->numNgh));
      if(1 == cellAdd->numNgh)
      {
         nlAcBuildNghEnbZeroOneServCellAdd(cellAdd, tcCb, spCb);
      }
      else if(2 == cellAdd->numNgh)
      {
         nlAcBuildNghEnbZeroTwoServCellAdd(cellAdd, tcCb, spCb);   
      }
   }
   else if(LNL_NGH_DEL == enbCfg->nghCellParam.cfgType)
   {
      cellDel = &(enbCfg->nghCellParam.u.nghCellDel);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_numDel",  &(cellDel->numNgh));
      if(1 == cellDel->numNgh)
      {
         nlAcBuildNghEnbZeroOneServCellDel(cellDel, tcCb, spCb);
      }
      else if(2 == cellDel->numNgh)
      {
         nlAcBuildNghEnbZeroTwoServCellDel(cellDel, tcCb, spCb);
      }
   }
   else if(LNL_NGH_MOD == enbCfg->nghCellParam.cfgType)
   {
      cellMod = &(enbCfg->nghCellParam.u.nghCellMod);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_numMod",  &(cellMod->numNgh));
      if(1 == cellMod->numNgh)
      {
         nlAcBuildNghEnbZeroOneServCellMod(cellMod, tcCb, spCb);
      }
      else if(2 == cellMod->numNgh)
      {


      }
   }
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcBuildTwoNghEnbCellCfg
*
*       Desc:  build neighbor eNodeB cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PRIVATE S16 nlAcBuildTwoNghEnbCellCfg
(
LnlNghCellCfg    *nghCellCfg,
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb
)
#else
PRIVATE S16 nlAcBuildTwoNghEnbCellCfg(nghCellCfg, tcCb, spCb)
LnlNghCellCfg    *nghCellCfg;
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
#endif
{
   S16               ret = 0;
   LnlNghEnbCellCfg *enbCfg = NULLP;
   LnlNghCellAdd     *cellAdd = NULLP;
   LnlNghCellMod     *cellMod = NULLP; 
   LnlNghCellDel     *cellDel = NULLP;
   LnlNghCellAddInfo *cellAddInfo = NULLP;
   LnlNghCellInfo    *nghCellInfo = NULLP;
   LnlNghCellInfo    *nghNghCellInfo = NULLP;

   TRC3(nlAcBuildTwoNghEnbCellCfg);
   enbCfg = &(nghCellCfg->nghEnbCellCfg[0]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0",  &(enbCfg->nghEnbId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_0_cfgType",  &(enbCfg->nghCellParam.cfgType));
   if(LNL_NGH_ADD == enbCfg->nghCellParam.cfgType)
   {
      cellAdd = &(enbCfg->nghCellParam.u.nghCellAdd);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_numAdd",  &(cellAdd->numNgh));
      if(1 == cellAdd->numNgh)
      {
         nlAcBuildNghEnbZeroOneServCellAdd(cellAdd, tcCb, spCb);
      }
      else if(2 == cellAdd->numNgh)
      {
         nlAcBuildNghEnbZeroTwoServCellAdd(cellAdd, tcCb, spCb);   
      }
   }
   else if(LNL_NGH_DEL == enbCfg->nghCellParam.cfgType)
   {
      cellDel = &(enbCfg->nghCellParam.u.nghCellDel);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_numDel",  &(cellDel->numNgh));
      if(1 == cellDel->numNgh)
      {
         nlAcBuildNghEnbZeroOneServCellDel(cellDel, tcCb, spCb);
      }
      else if(2 == cellDel->numNgh)
      {
         nlAcBuildNghEnbZeroTwoServCellDel(cellDel, tcCb, spCb);
      }
   }
   else if(LNL_NGH_MOD == enbCfg->nghCellParam.cfgType)
   {
      cellMod = &(enbCfg->nghCellParam.u.nghCellMod);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_0_numMod",  &(cellMod->numNgh));
      if(1 == cellMod->numNgh)
      {
         nlAcBuildNghEnbZeroOneServCellMod(cellMod, tcCb, spCb);
      }
      else if(2 == cellMod->numNgh)
      {


      }
   }

   enbCfg = &(nghCellCfg->nghEnbCellCfg[1]);
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1",  &(enbCfg->nghEnbId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "nghEnbId_1_cfgType",  &(enbCfg->nghCellParam.cfgType));
   if(LNL_NGH_ADD == enbCfg->nghCellParam.cfgType)
   {
      cellAdd = &(enbCfg->nghCellParam.u.nghCellAdd);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_numAdd",  &(cellAdd->numNgh));
      if(1 == cellAdd->numNgh)
      {
         nlAcBuildNghEnbOneOneServCellAdd(cellAdd, tcCb, spCb);
      }
      else if(2 == cellAdd->numNgh)
      {
         nlAcBuildNghEnbOneTwoServCellAdd(cellAdd, tcCb, spCb);
      }
   }
   else if(LNL_NGH_DEL == enbCfg->nghCellParam.cfgType)
   {
      cellDel = &(enbCfg->nghCellParam.u.nghCellDel);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_numDel",  &(cellDel->numNgh));
      if(1 == cellDel->numNgh)
      {
         nlAcBuildNghEnbOneOneServCellDel(cellDel, tcCb, spCb);
      }
      else if(2 == cellDel->numNgh)
      {
         nlAcBuildNghEnbOneTwoServCellDel(cellDel, tcCb, spCb);
      }
   }
   else if(LNL_NGH_MOD == enbCfg->nghCellParam.cfgType)
   {
      cellMod = &(enbCfg->nghCellParam.u.nghCellMod);
      ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nghEnbId_1_numMod",  &(cellMod->numNgh));
      if(1 == cellMod->numNgh)
      {
         nlAcBuildNghEnbOneOneServCellMod(cellMod, tcCb, spCb);
      }
      else if(2 == cellMod->numNgh)
      {


      }
   }

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcHdlLnlBuildNghCellCfg
*
*       Desc:  build neighbor cell config parameters
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlBuildNghCellCfg
(
LnlNghCellCfg *nghCellCfg,
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb
)
#else
PUBLIC S16 nlAcHdlLnlBuildNghCellCfg(nghCellCfg, tcCb, spCb)
LnlNghCellCfg *nghCellCfg;
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
#endif
{
   S16              ret = 0; 
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "cellId",  &(nghCellCfg->servCellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numNghEnb",  &(nghCellCfg->numNghEnb));
   if(1 == nghCellCfg->numNghEnb)
   {
      nlAcBuildOneNghEnbCellCfg(nghCellCfg, tcCb, spCb);
   }
   else if(2 == nghCellCfg->numNghEnb)
   {
      nlAcBuildTwoNghEnbCellCfg(nghCellCfg, tcCb, spCb);
   }
   else if(3 == nghCellCfg->numNghEnb)
   {

   }
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcHdlLnlNghCellCfgReq
*
*       Desc:  Call Handler for neighbor cell config request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlNghCellCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlNghCellCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;
   NlMngmt	 *cfgReq = NULLP;
   LnlNghCellCfg *nghCellCfg = NULLP; 
   U8            coupling = 1;

   TRC2(nlAcHdlLnlNghCellCfgReq);

   #ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlNghCellCfgReq(), tcId (%ld)\n", tcCb->tcId));
   #else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlNghCellCfgReq(), tcId (%d)\n", tcCb->tcId));
   #endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   /*-- Get the Pst information here from SM to SON --*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNL, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event   = EVTLNLCFGREQ;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));

   pst.selector = coupling;

   /* Allocate the memory for NlMngmt msg */

   CMXTA_ALLOC(&cfgReq, sizeof(NlMngmt));
	
   if(cfgReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlNghCellCfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Fill the data values into cfgReq */
	
   /*Fill the header fields*/

   cfgReq->hdr.msgType		   = TCFG;
   cfgReq->hdr.msgLen              = 0;
   cfgReq->hdr.entId.ent           = ENTNL;
   cfgReq->hdr.entId.inst          = 0;
   cfgReq->hdr.elmId.elmnt         = STNLPROTOCFG;

   if(coupling == 1)
      cfgReq->hdr.response.selector   = NLU_SEL_TC;
   else if(coupling == 2)
      cfgReq->hdr.response.selector   = NLU_SEL_LWLC;   

   /* fill the Cell configuration parameters*/
   cfgReq->u.protoCfg.bCfgType = LNL_NGH_CELL_CFG;
   nghCellCfg = &(cfgReq->u.protoCfg.u.nghCellCfg);
#if 1
   nlAcHdlLnlBuildNghCellCfg(nghCellCfg, tcCb, spCb);
#endif
   /* Send the msg to the SON --*/

   if(coupling == 1)
   {
      if(CMXTA_ERR_NONE != NlMiLnlCfgReq(&pst, cfgReq))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlNghCfgReq(): send to SON module FAILED\n"));
      }
   }

   if(coupling == 2)
   {
      if(CMXTA_ERR_NONE != cmPkLnlCfgReq(&pst, cfgReq))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlNghCfgReq(): send to SON module FAILED\n"));
      }
   }   

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcHdlLnlNghCellCfgFail
*
*       Desc:  Call Handler for LNL neighbor cell config Fail
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlNghCellCfgFail
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlNghCellCfgFail(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NlAccMsgQElm  *nlMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   //SuId          suId;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16           retVal = LCM_PRIM_OK;
   U16           reason = LCM_REASON_NOT_APPL;
   NlMngmt	 *cfgCfm;

   TRC2(nlAcHdlLnlNghCellCfgFail);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlNghCellCfgFail(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlNghCellCfgFail(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlLnlNghCellCfgFail(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   nlMsg = (NlAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLNLCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (NlMngmt *)(nlMsg->u.lnlInfo.data);

   if(cfgCfm->cfm.status == retVal || cfgCfm->cfm.reason == reason )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
            retVal, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);
      nlAcUtlLnlFreeCb(msg);
      RETVALUE(CMXTA_ERR_INT);

   }
   /*-- free memory, use callback function --*/
   nlAcUtlLnlFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   nlAcHdlLnlNghCellCfgCfm
*
*       Desc:  Call Handler for LNL neighbor cell config Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlNghCellCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlNghCellCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NlAccMsgQElm  *nlMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   //SuId          suId;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16           retVal = LCM_PRIM_OK;
   U16           reason = LCM_REASON_NOT_APPL;
   NlMngmt	 *cfgCfm;

   TRC2(nlAcHdlLnlNghCellCfgCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlNghCellCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlNghCellCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlLnlNghCellCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   nlMsg = (NlAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLNLCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (NlMngmt *)(nlMsg->u.lnlInfo.data);

   if(cfgCfm->cfm.status != retVal || cfgCfm->cfm.reason != reason )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
            retVal, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      RETVALUE(CMXTA_ERR_INT);

   }
   /*-- free memory, use callback function --*/
   nlAcUtlLnlFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   nlAcHdlLnlCellReCfgReq
*
*       Desc:  Call Handler for cell reconfig request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlCellReCfgReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlCellReCfgReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;
   NlMngmt	 *cfgReq;
   LnlCellReCfg  *cellReCfg ;
   U8            coupling = 1;
   U16           pciList[LNL_MAX_PCI_CFG];
   U32           pciCount;
   TRC2(nlAcHdlLnlCellReCfgReq);

   #ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCellReCfgReq(), tcId (%ld)\n", tcCb->tcId));
   #else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCellReCfgReq(), tcId (%d)\n", tcCb->tcId));
   #endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   /*-- Get the Pst information here from SM to SON --*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNL, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event   = EVTLNLCFGREQ;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));

   pst.selector = coupling;

   /* Allocate the memory for NlMngmt msg */

   CMXTA_ALLOC(&cfgReq, sizeof(NlMngmt));
	
   if(cfgReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlCellReCfgReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   cfgReq->u.protoCfg.bCfgType = LNL_CELL_RECFG;
   cellReCfg = &(cfgReq->u.protoCfg.u.cellReCfg);

   /* Fill the data values into cfgReq */
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "cellId",  &(cellReCfg->cellId));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mcc_0",  &(cellReCfg->ecgi.plmn.mcc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mcc_1",  &(cellReCfg->ecgi.plmn.mcc[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mcc_2",  &(cellReCfg->ecgi.plmn.mcc[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mnc_0",  &(cellReCfg->ecgi.plmn.mnc[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "mnc_1",  &(cellReCfg->ecgi.plmn.mnc[1]));
   cellReCfg->ecgi.cellId = cellReCfg->cellId;
   cellReCfg->ecgi.plmn.numMncDigits = 2;
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numPci",  &(cellReCfg->numPci));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_0",  &(pciList[0]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_1",  &(pciList[1]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_2",  &(pciList[2]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_3",  &(pciList[3]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_4",  &(pciList[4]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_5",  &(pciList[5]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_6",  &(pciList[6]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_7",  &(pciList[7]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_8",  &(pciList[8]));
   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "pci_9",  &(pciList[9]));

   for(pciCount = 0; pciCount < cellReCfg->numPci; pciCount ++)
   {
      cellReCfg->pciList[pciCount] = pciList[pciCount];
   }
	
   /*Fill the header fields*/

   cfgReq->hdr.msgType		   = TCFG;
   cfgReq->hdr.msgLen              = 0;
   cfgReq->hdr.entId.ent           = ENTNL;
   cfgReq->hdr.entId.inst          = 0;
   cfgReq->hdr.elmId.elmnt         = STNLPROTOCFG;

   if(coupling == 1)
      cfgReq->hdr.response.selector   = NLU_SEL_TC;
   else if(coupling == 2)
      cfgReq->hdr.response.selector   = NLU_SEL_LWLC;   

   /* Send the msg to the SON --*/

   if(coupling == 1)
   {
      if(CMXTA_ERR_NONE != NlMiLnlCfgReq(&pst, cfgReq))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlCellReCfgReq(): send to SON module FAILED\n"));
      }
   }

   if(coupling == 2)
   {
      if(CMXTA_ERR_NONE != cmPkLnlCfgReq(&pst, cfgReq))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlCellReCfgReq(): send to SON module FAILED\n"));
      }
   }   
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nlAcHdlLnlCellReCfgFail
*
*       Desc:  Call Handler for LNL cell reconfig failure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlCellReCfgFail
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlCellReCfgFail(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NlAccMsgQElm  *nlMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   //SuId          suId;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16           retVal = LCM_PRIM_OK;
   U16           reason = LCM_REASON_NOT_APPL;
   NlMngmt	 *cfgCfm;

   TRC2(nlAcHdlLnlCellReCfgFail);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCellReCfgFail(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCellReCfgFail(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlLnlCellReCfgFail(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   nlMsg = (NlAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLNLCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (NlMngmt *)(nlMsg->u.lnlInfo.data);

   if(cfgCfm->cfm.status == retVal || cfgCfm->cfm.reason == reason )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
            retVal, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      nlAcUtlLnlFreeCb(msg);
      RETVALUE(CMXTA_ERR_INT);

   }
   /*-- free memory, use callback function --*/
   nlAcUtlLnlFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);

}


/*
*
*       Fun:   nlAcHdlLnlCellReCfgCfm
*
*       Desc:  Call Handler for LNL cell reconfig Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlCellReCfgCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlCellReCfgCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NlAccMsgQElm  *nlMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   //SuId          suId;
   //SpId          spId;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16           retVal = LCM_PRIM_OK;
   U16           reason = LCM_REASON_NOT_APPL;
   NlMngmt	 *cfgCfm;

   TRC2(nlAcHdlLnlCellReCfgCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCellReCfgCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlCellReCfgCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlLnlCellReCfgCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   nlMsg = (NlAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLNLCFGCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cfgCfm = (NlMngmt *)(nlMsg->u.lnlInfo.data);

   if(cfgCfm->cfm.status != retVal || cfgCfm->cfm.reason != reason )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
            retVal, cfgCfm->cfm.status, reason, cfgCfm->cfm.reason), 2);

      nlAcUtlLnlFreeCb(msg);
      RETVALUE(CMXTA_ERR_INT);

   }
   /*-- free memory, use callback function --*/
   nlAcUtlLnlFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   nlAcHdlLnlShutdownReq
*
*       Desc:  Call Handler for eNB shutdown request
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlShutdownReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlShutdownReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst           pst;
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;
   NlMngmt	 *cntrlReq;
   U8            coupling = 1;

   TRC2(nlAcHdlLnlShutdownReq);

   #ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlShutdownReq(), tcId (%ld)\n", tcCb->tcId));
   #else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlShutdownReq(), tcId (%d)\n", tcCb->tcId));
   #endif

   CMXTA_ZERO(&pst, sizeof(Pst));     /* Initialization of the Pst   */

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   /*-- Get the Pst information here from SM to SON --*/
   cmXtaGetPst(&pst, ENTSM, CMXTA_INST_ID, ENTNL, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event   = EVTLNLCNTRLREQ;

   ret = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "coupling", &(coupling));

   pst.selector = coupling;

   /* Allocate the memory for NlMngmt msg */

   CMXTA_ALLOC(&cntrlReq, sizeof(NlMngmt));
	
   if(cntrlReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlShutdownReq(): failed to allocate memory\n"));
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Fill the data values into cfgReq */
	
   /*Fill the header fields*/
   cntrlReq->u.cntrl.action          = ASHUTDOWN;
   cntrlReq->hdr.msgType	     = TCNTRL;
   cntrlReq->hdr.msgLen              = 0;
   cntrlReq->hdr.entId.ent           = ENTNL;
   cntrlReq->hdr.entId.inst          = 0;
   cntrlReq->hdr.elmId.elmnt         = STNLGEN;

   if(coupling == 1)
      cntrlReq->hdr.response.selector   = NLU_SEL_TC;
   else if(coupling == 2)
      cntrlReq->hdr.response.selector   = NLU_SEL_LWLC;   

   /* Send the msg to the SON --*/

   if(coupling == 1)
   {
      if(CMXTA_ERR_NONE != NlMiLnlCntrlReq(&pst, cntrlReq))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlShutdownReq(): send to SON module FAILED\n"));
      }
   }
   else if(coupling == 2)
   {
      if(CMXTA_ERR_NONE != cmPkLnlCntrlReq(&pst, cntrlReq))
      {
         CMXTA_DBG_ERR((_cmxtap,"nlAcHdlLnlShutdownReq(): send to SON module FAILED\n"));
      }
   }   

   RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:   nlAcHdlLnlShutdownCfm
*
*       Desc:  Call Handler for LNL eNB shutdown Confirm
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nlac_lnlhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 nlAcHdlLnlShutdownCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 nlAcHdlLnlShutdownCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   NlAccMsgQElm  *nlMsg = NULLP;
   Pst           pst;
   S16           ret = 0;
   ProcId        srcProcId;
   ProcId        dstProcId;

   U16           retVal = LCM_PRIM_OK;
   U16           reason = LCM_REASON_NOT_APPL;
   NlMngmt	 *cntrlCfm;

   TRC2(nlAcHdlLnlShutdownCfm);

   cmMemset((U8*)&pst, 0 , sizeof(Pst));

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlShutdownCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nlAcHdlLnlShutdownCfm(), tcId (%d)\n", tcCb->tcId));
#endif

   if (CMXTA_ERR_NONE != cmXtaPeekMsg((CmXtaMsgQ *)&(tcCb->msgQ), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "nlAcHdlLnlShutdownCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   srcProcId   =   CMXTA_DFLT_PROCID;
   dstProcId   =   CMXTA_DFLT_PROCID;

   nlMsg = (NlAccMsgQElm *)msg->data;

   /*-- Get the Pst information  --*/
   cmXtaGetPst(&pst, ENTNL, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID, srcProcId,
                  dstProcId, FALSE);

   pst.event = EVTLNLCNTRLCFM;

   ret = cmXtaValidatePst(&(msg->pst), &pst);

   if (ret != CMXTA_ERR_NONE)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg ((CmXtaMsgQ *)&(tcCb->msgQ), &msg);

   nlMsg = (NlAccMsgQElm *)msg->data;

   /* Compare the value in the message and the value provided from xml */

   cntrlCfm = (NlMngmt *)(nlMsg->u.lnlInfo.data);

   if(cntrlCfm->cfm.status != retVal || cntrlCfm->cfm.reason != reason )
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : MisMatch: expStatus (%d) rcvdStatus (%d)"
                                  ": expReason (%d) rcvdReason (%d) ",
            retVal, cntrlCfm->cfm.status, reason, cntrlCfm->cfm.reason), 2);

      nlAcUtlLnlFreeCb(msg);
      RETVALUE(CMXTA_ERR_INT);

   }
   /*-- free memory, use callback function --*/
   nlAcUtlLnlFreeCb(msg);
   RETVALUE(CMXTA_ERR_NONE);

}

/*utility function begins*/

#ifdef ANSI
PUBLIC S16 nlAcUtlLnlFreeCb
(
CmXtaMsgQElm    *qElm
)
#else
PUBLIC S16 nlAcUtlLnlFreeCb(qElm)
CmXtaMsgQElm   *qElm;
#endif
{
   NlAccMsgQElm *nlMsg;

   TRC2(nlAcUtlLnlFreeCb);

   CMXTA_DBG_PARAM((_cmxtap, "nlAcUtlLnlFreeCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   nlMsg = (NlAccMsgQElm *)qElm->data;

   if(nlMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   if (nlMsg != NULLP)
   {
      if(nlMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(nlMsg->mBuf);
      if(nlMsg->u.lnlInfo.data != NULLP)
      {
         //NLAC_NLUFREEBUF(nlMsg->u.lnlInfo.data, nlMsg->u.lnlInfo.len);
           CMXTA_FREE(nlMsg->u.lnlInfo.data, nlMsg->u.lnlInfo.len);
      }
      CMXTA_FREE(nlMsg, sizeof (NlAccMsgQElm));
      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
}

/*utility function ends*/
