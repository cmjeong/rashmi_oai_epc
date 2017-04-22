
/********************************************************************20**

     Name:     RRC 
     
     Type:     C source file

     Desc:     Provides the utility functions used by RRC Layer Manager 

     File:     nhac_lnhutl.c 

     Sid:      nhac_lnhutl.c@@/main/3 - Fri Jul  1 01:13:04 2011

     Prg:      dm

*********************************************************************21*/

/* header include files (.h) */
/* header include files (.h) */
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
#include "ckw.h"            /* C-RLC interface */
#include "kwu.h"            /* D-RLC interface */
#include "crg.h"            /* C-MAC interface */
#include "cpj.h"            /* C-PDCP interface */
#include "pju.h"            /* D-PDCP interface */
#include "nhu.h"           /* RRC Upper Interface */
#include "ctf.h"           /* PHY Interface */
#include "cm_xta.h"
#include "nhac_acc.h"
#include "nh.h"
#include "lnh.h"
#include "cm_pasn.h"
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
#include "ckw.x"            /* C-RLC interface */
#include "kwu.x"            /* D-RLC interface */
#include "crg.x"            /* C-MAC interface */
#include "cpj.x"            /* C-PDCP interface */
#include "pju.x"            /* D-PDCP interface */
#include "nhac_asn.x"
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"

/*
*
*       Fun:   nhAcUtlLnhSendMsg 
*
*       Desc:  This function is used to Send Msg
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_lnhutl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcUtlLnhSendMsg
(
Pst         *pst,
NhMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 nhAcUtlLnhSendMsg(pst, cfm, mBuf)
Pst         *pst;
NhMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
   Bool      del = FALSE;
   CmXtaTCCb *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC3(nhAcUtlLnhSendMsg)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "nhAcUtlLnhSendMsg(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "nhAcUtlLnhSendMsg(): txnId(%d)\n", cfm->hdr.transId));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Check if any tapa directives set --*/

   del = TRUE;
   /*-- Do not delete the txn cb if it is partial confirmation --*/
   if (cfm->cfm.status == LCM_PRIM_OK_NDONE)
      del = FALSE;

    /*-- Find the associated test case using the txnId --*/
   if ((tcCb = cmXtaTxnTstCbFind(cfm->hdr.transId, del)) == NULLP)
   {
      /*-- No associated test case found, spurious 
        message, drop it --*/
#ifndef ALIGN_64BIT
      CMXTA_DBG_INFO((_cmxtap, "nhAcUtlLnhSendMsg(): msg dropped for txnId(%ld)\n",
               cfm->hdr.transId));
#else
      CMXTA_DBG_INFO((_cmxtap, "nhAcUtlLnhSendMsg(): msg dropped for txnId(%d)\n",
               cfm->hdr.transId));
#endif
      if (pst->event == EVTLNHTRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }
      RETVALUE(CMXTA_ERR_NONE);
   }

     /*-- Check if any tapa directives set --*/

   /*-- Drop the message if the status is OK_NDONE and the global directive 
        is set --*/
   if ((tcCb->directives.partialCfm == FALSE) &&
       (cfm->cfm.status == LCM_PRIM_OK_NDONE))
      RETVALUE(ROK);

   /*-- Check if we are logging the traces --*/
   if ((tcCb->directives.logTrc == TRUE) &&
       (pst->event == EVTLNHTRCIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are logging the alarms --*/
   if ((tcCb->directives.logAlarm == TRUE) &&
       (pst->event == EVTLNHSTAIND))
   {
      /*-- Log alarms --*/
   }
   tcCb->directives.capAlarm = TRUE;  
   tcCb->directives.capTrc = FALSE;
 /*-- Check if we are ignoring all the messages, or else it is
        an alarm or a trace and the capture for the same is not
        set --*/
   if ((tcCb->directives.ignoreMsg == TRUE)    ||
       ((pst->event == EVTLNHSTAIND)     &&
        (tcCb->directives.capAlarm == FALSE))  ||
       ((pst->event == EVTLNHTRCIND)     &&
        (tcCb->directives.capTrc == FALSE)))
   {
#ifndef ALIGN_64BIT
      CMXTA_DBG_PARAM((_cmxtap, "nhAcUtlLnhSendMsg(): txnId(%ld) dropping alarm/trace\n", cfm->hdr.transId));
#else
      CMXTA_DBG_PARAM((_cmxtap, "nhAcUtlLnhSendMsg(): txnId(%d) dropping alarm/trace\n", cfm->hdr.transId));
#endif
      /*-- Drop the message --*/
      if (pst->event == EVTLNHTRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }

      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "nhAcAquSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   if (pst->event == EVTLNHTRCIND)
   {
      CMXTA_FREEMBUF(mBuf);
   }

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(rrcMsg->u.nhMngmt), (U8 *)cfm, sizeof(NhMngmt));
   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlLnhCb;

   /*-- Test case found, queue the message for the tcCb --*/
   /*-- Push it onto the message queue --*/
   (Void) cmXtaPushMsg((CmXtaMsgQ*)&tcCb->msgQ, &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);


   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlLnhSendMsg() */

/*
*
*       Fun:   nhAcUtlLnhCb
*
*       Desc:  This function is used to free the Queue Element
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlLnhCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 nhAcUtlLnhCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{  
   NhAccMsgQElm  *rrcMsg = NULLP;

   TRC2(nhAcUtlLnhCb)
  
   rrcMsg = (NhAccMsgQElm *)qElm->data;
 
#ifdef NH_TRACE_ENABLED
   switch (rrcMsg->pst.event)
   {
      case EVTLNHTRCIND:
      {
         CMXTA_FREEMBUF(rrcMsg->mBuf);
         break;
      } /* end of case */

   } /* end of switch case */
#endif /* NH_TRACE_ENABLED */
    if(NULLP != rrcMsg)
    CMXTA_FREE(rrcMsg ,sizeof(NhAccMsgQElm))

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlLnhCb() */


/*
*
*       Fun:  nhAcGetStatus
*
*       Desc:  
*
*       Ret:   Void
*
*       Notes: 
*
*       File:  nhac_lnhutl.c
*
*/

#ifdef ANSI
PUBLIC Void nhAcGetStatus
(
Void           *curStep,
CmStatus       *status
)
#else
PUBLIC Void nhAcGetStatus(curStep, status)
Void           *curStep;
CmStatus       *status;
#endif
{

   /*-- Set Default values of return value and reason --*/
   status->status = LCM_PRIM_OK;
   status->reason = LCM_REASON_NOT_APPL;

   /*-- Update values --*/
   cmXtaXmlGetVal(NULLP,curStep, CMXTA_ATTRIB_ENUM_U16, "status",  &status->status);
   cmXtaXmlGetVal(NULLP,curStep, CMXTA_ATTRIB_ENUM_U16, "reason", &status->reason);

   RETVOID;
}


/*
*
*       Fun:   nhAcValidateStatus
*
*       Desc:  
*
*       Ret:   Void
*
*       Notes: 
*
*       File:  nhac_lnhutl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcValidateStatus
(
CmStatus       *status,
CmStatus       *incStatus
)
#else
PUBLIC S16 nhAcValidateStatus(status, incStatus)
CmStatus       *status;
CmStatus       *incStatus;
#endif
{
   CMXTA_DBG_PARAM((_cmxtap, "nhAcValidateStatus() : Status(%hd) reason(%hd) \n",
                     incStatus->status, incStatus->reason));

   if ((status->status != incStatus->status) ||
         (status->reason != incStatus->reason))
   {
      CMXTA_DBG_CALLIND((_cmxtap,
               "Received: [status '%hd' reason '%hd']\tExpected: [status '%hd' reason '%hd']\n",
               incStatus->status, incStatus->reason, status->status, status->reason), 2);

      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}

/*
*
*       Fun:   nhAcUtlNhBuildGenCfgReq
*
*       Desc:  Utility Function to Build General Configuration Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhBuildGenCfgReq
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
NhMngmt     *nhMngmt   
)
#else
PUBLIC S16 nhAcUtlNhBuildGenCfgReq(tcCb, spCb, nhMngmt)
CmXtaTCCb     *tcCb;    /* tcCb data structure  */
CmXtaSpCb     *spCb;
NhMngmt    *nhMngmt;   
#endif
{
   /* local variables */
   U8          enbCfgTmr=0;
   NhGenCfg    *genCfg = NULLP; 

   TRC2(nhAcUtlNhBuildGenCfgReq)

   genCfg   = &(nhMngmt->u.cfg.u.gen);
   cmMemset ((U8 *) genCfg  , 0, sizeof (NhGenCfg));   

  /*----------- Fill General Configuration Parameters ---------*/

   genCfg->msecTmrRes   = NHAC_DFLT_MSEC_TMR_CFG;   /* Milli Sec Timer Resolution */
   genCfg->cfgTmr.enb = FALSE;
   genCfg->cfgTmr.val  = 0;
   genCfg->nmbKwuSaps = 1;
   genCfg->nmbCkwSaps = 1;
   genCfg->nmbCrgSaps = 1;
   genCfg->nmbCpjSaps = 1;
   genCfg->nmbPjuSaps = 1;
#ifdef RRC_PHY_CFG_SUPP
   genCfg->nmbCtfSaps = 1;
#endif

   /*-- Check if the default values are overridden in the TC --*/
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "msecTmrRes",  &(genCfg->msecTmrRes));
 /*  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "secTmrRes",  &(genCfg->secTmrRes)); */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "minTransLstLen",  &(genCfg->minTransLstLen));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "minMuiLstLen",  &(genCfg->minMuiLstLen));
#ifdef RRC_MT
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbThrds",  &(genCfg->nmbWorkerThrds));
#endif
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tmrVal",  &(genCfg->cfgTmr.val));
   if (genCfg->cfgTmr.val)
   {
     genCfg->cfgTmr.enb = TRUE;
   }
   else
   {
      /* To facilitate timer.val==0 and enb=TRUE */
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "enbCfgTmr",  &(enbCfgTmr));
      genCfg->cfgTmr.enb = enbCfgTmr;
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbKwuSaps", &(genCfg->nmbKwuSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbCkwSaps", &(genCfg->nmbCkwSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbCrgSaps", &(genCfg->nmbCrgSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbPjuSaps", &(genCfg->nmbPjuSaps));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbCpjSaps", &(genCfg->nmbCpjSaps));

#ifdef RRC_PHY_CFG_SUPP
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbCtfSaps", &(genCfg->nmbCtfSaps));
#endif

#ifdef DEBUGP
   
   /* By Deafult it should be disable*/
   genCfg->dbgMsk         = 0x00;
  
   if (cmXtaCb.dbgMask > CMXTA_DBGLEVEL_NH)
   {
      genCfg->dbgMsk =  0xFFFFFFFF;
   }
#endif
   
   RETVALUE(CMXTA_ERR_NONE);
} /* nhAcUtlNhBuildGenCfgReq() */


/*
*
*       Fun:   nhAcUtlNhBuildLsapCfgReq
*
*       Desc:  Utility Function to Build Lower SAP Configuration Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhBuildLsapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb     *spCb,
NhMngmt    *nhMngmt   
)
#else
PUBLIC S16 nhAcUtlNhBuildLsapCfgReq(tcCb, spCb, nhMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
NhMngmt   *nhMngmt;   
#endif
{
   /* local variables */
   NhLSapCfg    *lSap=NULLP;  /*  *tSapCfg; */
   U8           bndTmrEnb=1; /* default: TRUE */

   TRC2 (nhAcUtlNhBuildLsapCfgReq)

   lSap   = &(nhMngmt->u.cfg.u.lSap);

   cmMemset ((U8 *) lSap  , 0, sizeof (NhLSapCfg));   
   
   lSap->selector     = NHAC_DFLT_SEL_LCFG;
   lSap->mem.region   = NHAC_DFLT_MEMID_REG_LCFG;
   lSap->mem.pool     = NHAC_DFLT_MEMID_POOL_LCFG;
   lSap->prior        = NHAC_DFLT_PRIOR_LCFG;
   lSap->procId       = NHAC_DFLT_DST_PROC_ID_LCFG;
   lSap->ent          = NHAC_DFLT_DST_ENT_LCFG;
   lSap->inst         = NHAC_DFLT_DST_INST_LCFG;
   lSap->route        = NHAC_DFLT_DST_ROUT_LCFG;
   lSap->spId         = NHAC_DFLT_SPID_LCFG;
   lSap->suId         = NHAC_DFLT_SUID_LCFG;
   lSap->bndRetryCnt  = NHAC_DFLT_BNDRTYCNT_LCFG;
   lSap->bndTmr.enb   = TRUE;
   lSap->bndTmr.val   = NHAC_DFLT_BNDTMR_LCFG;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "selector",  &(lSap->selector));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "mem_reg",  &(lSap->mem.region));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "mem_pool",  &(lSap->mem.pool));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(lSap->spId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(lSap->suId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "prior",  &(lSap->prior));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "procId",  &(lSap->procId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "inst",  &(lSap->inst));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "bndRetryCnt",  &(lSap->bndRetryCnt));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ent",  &(lSap->ent));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "bndTmr.enb",  &(bndTmrEnb));
   if (bndTmrEnb == 1)
   {
      lSap->bndTmr.enb = TRUE;
   }
   else
   {
      lSap->bndTmr.enb = FALSE;
   }
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "bndTmr.val",  &(lSap->bndTmr.val));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "Ent",  &(lSap->ent));


   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcUtlNhBuildLsapCfgReq()*/


/*
*
*       Fun:   nhAcUtlNhBuildUsapCfgReq
*
*       Desc:  Utility Function to Build Upper SAP Configuration Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhBuildUsapCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb,
NhMngmt     *nhMngmt   
)
#else
PUBLIC S16 nhAcUtlNhBuildUsapCfgReq(tcCb, spCb, nhMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
NhMngmt     *nhMngmt;   
#endif
{
   NhUSapCfg *uSap;
   Pst      tmpPst;
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;

   TRC2 (nhAcUtlNhBuildUsapCfgReq)

   uSap   = &(nhMngmt->u.cfg.u.uSap);
   cmMemset ((U8 *) uSap,  0, sizeof (NhUSapCfg));   

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */

 /*  uSap->selector     = 1;*/
   uSap->mem.region   = NHAC_DFLT_MEMID_REG_UCFG;
   uSap->mem.pool     = NHAC_DFLT_MEMID_POOL_UCFG;
   uSap->prior        = NHAC_DFLT_PRIOR_UCFG;
   uSap->procId       = NHAC_DFLT_DST_PROC_ID_UCFG;
   uSap->ent          = NHAC_DFLT_DST_ENT_UCFG;
   uSap->inst         = NHAC_DFLT_DST_INST_UCFG;
   uSap->route        = NHAC_DFLT_DST_ROUT_UCFG;
   uSap->spId         = NHAC_DFLT_SPID_UCFG;
   
   /* Get the values from TA */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "mem_reg",  &(uSap->mem.region));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "mem_pool",  &(uSap->mem.pool));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "prior",  &(uSap->prior));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(uSap->spId));

   cmXtaGetPst(&tmpPst, ENTNH, CMXTA_INST_ID, ENTNX, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   uSap->procId       = tmpPst.dstProcId;
   uSap->ent          = tmpPst.dstEnt;
   uSap->inst         = tmpPst.dstInst;
   uSap->route        = tmpPst.route;
   uSap->selector      = tmpPst.selector;
   
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "selector",
         &(uSap->selector));

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcUtlNhBuildUsapCfgReq()*/


/*
*
*       Fun:   nhAcUtlNhBuildProtCfgReq
*
*       Desc:  Utility Function to Build Protocol SAP Configuration Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhBuildProtCfgReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb  *spCb,
NhMngmt     *nhMngmt   
)
#else
PUBLIC S16 nhAcUtlNhBuildProtCfgReq(tcCb, spCb, nhMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb  *spCb;
NhMngmt     *nhMngmt;   
#endif
{
   NhProtCfg *prot = NULLP;
   Pst      entPst;
   ProcId        srcProcId = 0;
   ProcId        dstProcId = 0;

   TRC2 (nhAcUtlNhBuildProtCfgReq)

   prot   = &(nhMngmt->u.cfg.u.prot);
   cmMemset ((U8 *) prot,  0, sizeof (NhProtCfg));   

   /*-- Get the Pst information here --*/
   /* Moved outside MULTIPLE PROC flag */
   cmXtaGetPst(&entPst, ENTNH, CMXTA_INST_ID, ENTSM, CMXTA_INST_ID,srcProcId,dstProcId,FALSE);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "maxConn",  &(prot->maxConn));

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcUtlNhBuildProtCfgReq()*/



/*
*
*       Fun:   nhAcUtlNhBuildUstaCntrlReq
*
*       Desc:  Utility Function to Build USTA Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhBuildUstaCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
NhMngmt   *nhMngmt
)
#else
PUBLIC S16 nhAcUtlNhBuildUstaCntrlReq(tcCb, spCb, nhMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
NhMngmt   *nhMngmt;
#endif
{

   NhCntrl *cntrl = NULLP;

   TRC2(nhAcUtlNhBuildUstaCntrlReq)

   cntrl = &nhMngmt->u.cntrl;

   cntrl->subAction     = SAUSTA;

   cntrl->action = AENA;

   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "action",  &(cntrl->action));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "subAction",  &(cntrl->subAction));

   RETVALUE(CMXTA_ERR_NONE);

}/* nhAcUtlNhBuildUstaCntrlReq()*/


/*
*
*       Fun:   nhAcUtlNhBuildUsapCntrlReq
*
*       Desc:  Utility Function to Build USAP Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhBuildUsapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
NhMngmt   *nhMngmt   
)
#else
PUBLIC S16 nhAcUtlNhBuildUsapCntrlReq(tcCb, spCb, nhMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
NhMngmt   *nhMngmt;   
#endif
{
   S16 ret = 0;

   NhCntrl *cntrl = NULLP;

   TRC2(nhAcUtlNhBuildUsapCntrlReq)

   cntrl = &nhMngmt->u.cntrl;

   cntrl->action        = ADEL;
   cntrl->u.sap.sapId   = 1;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "action",  &(cntrl->action));
     /* Getting these values from TA*/
   ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(cntrl->u.sap.sapId));

   if( ret == CMXTA_ERR_NO_VALUE)
   {
       CMXTA_DBG_ERR((_cmxtap,"nhAcUtlNhBuildUsapCntrlReq() : spId should be provided from the xml file \n"));
   } /* end of if statement */

   RETVALUE(CMXTA_ERR_NONE);

}/* nhAcUtlNhBuildUsapCntrlReq()*/

/*
*
*       Fun:   nhAcUtlNhBuildLsapCntrlReq
*
*       Desc:  Utility Function to Build Trace Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhBuildLsapCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
NhMngmt   *nhMngmt   
)
#else
PUBLIC S16 nhAcUtlNhBuildLsapCntrlReq(tcCb, spCb, nhMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
NhMngmt   *nhMngmt;   
#endif
{

   NhCntrl *cntrl = NULLP;
   S16 ret = 0;

   TRC2(nhAcUtlNhBuildLsapCntrlReq)

   cntrl = &nhMngmt->u.cntrl;
   cntrl->action        = ABND_ENA;
   cntrl->u.sap.sapId        = 1;
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
    ret = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(cntrl->u.sap.sapId));
    if( ret == CMXTA_ERR_NO_VALUE)
    {
       CMXTA_DBG_ERR((_cmxtap,"nhAcUtlNhBuildLsapCntrlReq() SuId is expected from the xml file\n"));
       RETVALUE(CMXTA_ERR_INT);
    }

    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "action",  &(cntrl->action));

    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "subaction", &(cntrl->subAction));
   
    RETVALUE(CMXTA_ERR_NONE);

}/* nhAcUtlNhBuildLsapCntrlReq()*/
#ifdef NH_TRACE_ENABLED
/*
*
*       Fun:   nhAcUtlNhBuildTrcCntrlReq
*
*       Desc:  Utility Function to Build Trace Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhBuildTrcCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
NhMngmt   *nhMngmt
)
#else
PUBLIC S16 nhAcUtlNhBuildTrcCntrlReq(tcCb, spCb, nhMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
NhMngmt   *nhMngmt;
#endif
{

   NhCntrl *cntrl;
   U8 trcMsk = 0; /* default disable trace */
   
   TRC2(nhAcUtlNhBuildTrcCntrlReq)

   cntrl = &nhMngmt->u.cntrl;

   cntrl->subAction     = SATRC;
   cntrl->action        = AENA;

   /* Getting these values from TA*/
  cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8 , "trcMsk", &trcMsk);
  cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , "action",  &(cntrl->action));


   RETVALUE(CMXTA_ERR_NONE);

}/* nhAcUtlNhBuildTrcCntrlReq()*/
#endif

/*
*
*       Fun:   nhAcUtlNhBuildPnodeCntrlReq
*
*       Desc:  Utility Function to Build Trace Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhBuildPnodeCntrlReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,
NhMngmt   *nhMngmt   
)
#else
PUBLIC S16 nhAcUtlNhBuildPnodeCntrlReq(tcCb, spCb, nhMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
NhMngmt   *nhMngmt;   
#endif
{


   TRC2(nhAcUtlNhBuildPnodeCntrlReq)

  RETVALUE(ROK);
}/* nhAcUtlNhBuildPnodeCntrlReq()*/

#ifdef DEBUGP
/*
*
*       Fun:   nhAcUtlNhBuildDebugCntrlReq
*
*       Desc:  Utility Function to Build Debug Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhBuildDebugCntrlReq
(
CmXtaTCCb     *tcCb,    /* tcCb data structure  */
CmXtaSpCb     *spCb,
NhMngmt    *nhMngmt   
)
#else
PUBLIC S16 nhAcUtlNhBuildDebugCntrlReq(tcCb, spCb,nhMngmt)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;
NhMngmt   *nhMngmt;   
#endif
{
   NhCntrl *cntrl;
   U32 dbgMsk = 0;
   
   TRC2(nhAcUtlNhBuildDebugCntrlReq)

   cntrl = &nhMngmt->u.cntrl;

   cntrl->subAction       = SADBG;

   if (cmXtaCb.dbgMask > CMXTA_DBGLEVEL_NH)
   {
      cntrl->action = AENA;
   }
    
   /* Getting these values from TA*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , "action",  &(cntrl->action));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16 , "subAction",  &(cntrl->subAction));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32 , "dbgMsk",  &dbgMsk);
   
  
   if(dbgMsk) /* if debug mask is set fill the debug mask */
   {
      cntrl->u.dbg.dbgMsk = dbgMsk;

   }
   else /* default enable all debug mask */
   {
      cntrl->u.dbg.dbgMsk = 0xffffffff;
   }
   RETVALUE(CMXTA_ERR_NONE);

}/* nhAcUtlNhBuildDebugCntrlReq()*/

#endif /* DEBUGP*/


/*
*
*       Fun:   nhAcUtlNhBuildShutdownCntrlReq
*
*       Desc:  Utility Function to Build Shut Down Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhBuildShutdownCntrlReq
(
NhMngmt     *nhMngmt
)
#else
PUBLIC S16 nhAcUtlNhBuildShutdownCntrlReq(nhMngmt)
NhMngmt     *nhMngmt;
#endif
{
   NhCntrl *cntrl;

   TRC2(nhAcUtlNhBuildShutdownCntrlReq)

   cntrl = &nhMngmt->u.cntrl;

   cntrl->action        =  ASHUTDOWN;
   /* subAction is ignored by RRC for this primitive*/

   RETVALUE(CMXTA_ERR_NONE);

}/* nhAcUtlNhBuildShutdownCntrlReq()*/


/*
*
*       Fun:   nhAcUtlNhBuildStartCntrlReq
*
*       Desc:  Utility Function to Build Start Control Req
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  nhac_lnhutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhBuildStartCntrlReq
(
NhMngmt     *nhMngmt
)
#else
PUBLIC S16 nhAcUtlNhBuildStartCntrlReq(nhMngmt)
NhMngmt     *nhMngmt;
#endif
{
   NhCntrl *cntrl = NULLP;

   TRC2(nhAcUtlNhBuildStartCntrlReq)

   cntrl = &nhMngmt->u.cntrl;

   cntrl->action        = NHAC_START;
   /* subAction is ignored by RRC for this primitive*/

   RETVALUE(CMXTA_ERR_NONE);
}/* nhAcUtlNhBuildStartCntrlReq    */



/********************************************************************30**

         End of file:     nhac_lnhutl.c@@/main/3 - Fri Jul  1 01:13:04 2011

*********************************************************************31*/
/********************************************************************60**

        Revision history:

*********************************************************************61*/
/********************************************************************90**
 
   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    dm               1. LTE RRC Initial Release.
/main/2      ---    chebli           1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
