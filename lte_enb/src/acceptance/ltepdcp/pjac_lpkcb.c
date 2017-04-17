

/********************************************************************20**

     Name:    LTE-PDCP - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    pjac_lpkcb.c

     Sid:      pjac_lpkcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:01 2015

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
#include "lpk.h"           /* LPK defines */
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "pju.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpk.h"           /* LPK defines */
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
#include "lpk.x"           /* LPK */
#include "ckw.x"           /* CKW */
#include "cpj.x"           /* CPJ */
#include "kwu.x"           /* KWU */
#include "pju.x"           /* KWU */
#include "rgu.x"           /* RGU */
#include "lpj.x"           /* LPK */
#include "lpk.x"           /* LPK */
#include "kw.x"
#include "pk.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_lpk.x"      /* CKW Acceptance defines */


#ifdef KW_PDCP
/**
@brief 
@return CmXtaTCCb* 
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  kwAcLpkTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  kwAcLpkTstCbFind ()
#endif
{
   TRC2(kwAcLpkTstCbFind);

   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change SOAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP) &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif

   RETVALUE(NULLP);
} /* End of kwAcLpkTstCbFind */


/**
@brief utility function for sending the message to test engine 
@param pst 
@param cfm  
@param mBuf
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkSendMsg
(
Pst         *pst,
PkMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 SmMiLpkSendMsg(pst, cfm, mBuf)
Pst         *pst;
PkMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   KwAcMsgQElm *kwMsg;

   TRC3(SmMiLpkSendMsg);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkSendMsg(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkSendMsg(): txnId(%d)\n", cfm->hdr.transId));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the asmgciated test case */
   if ((tcCb = kwAcLpkTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, " kwAcLpkTstCbFind returning NULL...\n"));
      RETVALUE(ROK);
   }

   /*-- Allocate KW memory data --*/
   kwMsg = NULLP;
   CMXTA_ALLOC(&kwMsg, sizeof (KwAcMsgQElm));
   if (kwMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "SmMiLpkSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   kwMsg->mBuf = mBuf;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(kwMsg->u.kwMngmt), (U8 *)cfm, sizeof(PkMngmt));
   qElm.data = (Void *)kwMsg;
   qElm.msgFreeFun = kwAcUtlLpkFreeCb;


   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(ROK);

}
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS

/**
@brief utility function for sending the message to test engine 
@param pst 
@param cfm  
@param mBuf
@return ROK if it is successful
*/
#ifdef ANSI
PRIVATE S16 SmMiLpkSendL2MeasMsg
(
Pst         *pst,
PkL2MeasCfmEvt *measEvt
)
#else
PRIVATE S16 SmMiLpkSendL2MeasMsg(pst, measEvt)
Pst            *pst;
PkL2MeasCfmEvt *measEvt;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   KwAcMsgQElm *kwMsg;

   TRC3(SmMiLpkSendL2MeasMsg);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkSendL2MeasMsg(): txnId(%ld)\n", measEvt->transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkSendL2MeasMsg(): txnId(%d)\n", measEvt->transId));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the asmgciated test case */
   if ((tcCb = kwAcLpkTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, " kwAcLpkTstCbFind returning NULL...\n"));
      RETVALUE(ROK);
   }

   /*-- Allocate KW memory data --*/
   kwMsg = NULLP;
   CMXTA_ALLOC(&kwMsg, sizeof (KwAcMsgQElm));
   if (kwMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "SmMiLpkSendL2MeasMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(kwMsg->u.pkMeasCfmEvt), (U8 *)measEvt, 
          sizeof(PkL2MeasCfmEvt));
   qElm.data = (Void *)kwMsg;
   qElm.msgFreeFun = NULLP;

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(ROK);

}/* End of function SmMiLpkSendL2MeasMsg */
#endif

/**
@brief This function is used by to present configuration confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkCfgCfm
(
Pst     *pst,          /* post structure */
PkMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLpkCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
PkMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLpkCfgCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkCfgCfm(): txnId(%d)\n", cfm->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPK_EVT_CFG_CFM;

   SmMiLpkSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* SmMiLpkCfgCfm */


/**
@brief This function is used by to present control confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkCntrlCfm
(
Pst     *pst,          /* post structure */
PkMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLpkCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
PkMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLpkCntrlCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkCntrlCfm(): txnId(%d)\n", cfm->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPK_EVT_CNTRL_CFM;

   SmMiLpkSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* SmMiLpkCntrlCfm */


/**
@brief This function is used by to present Statistics confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkStsCfm 
(
Pst     *pst,          /* post structure */
Action  action,        /* Action */
PkMngmt *sts           /* statistics */
)
#else
PUBLIC S16 SmMiLpkStsCfm(pst, action, sts)
Pst     *pst;          /* post structure */
Action  action;        /* Action */
PkMngmt *sts;          /*  statistics */
#endif
{
   TRC2(SmMiLpkStsCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkStsCfm(): txnId(%ld)\n", sts->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkStsCfm(): txnId(%d)\n", sts->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPK_EVT_STS_CFM;

   SmMiLpkSendMsg(pst, sts, NULLP);


   RETVALUE(ROK);

} /* SmMiLpkStsCfm */


/**
@brief This function is used by to present Status confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkStaCfm
(
Pst     *pst,          /* post structure */
PkMngmt *sta           /* Status */
)
#else
PUBLIC S16 SmMiLpkStaCfm(pst,sta)
Pst     *pst;          /* post structure */
PkMngmt *sta;          /* Status */
#endif
{
   TRC2(SmMiLpkStaCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkStaCfm(): txnId(%ld)\n", sta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkStaCfm(): txnId(%d)\n", sta->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPK_EVT_STA_CFM;

   SmMiLpkSendMsg(pst, sta, NULLP);

   RETVALUE(ROK);
} /* SmMiLpkStaCfm */


/**
@brief This function is used by to present Status Indication information to Layer Management.
@param pst 
@param cfm
@return ROK if it is  successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkStaInd
(
Pst     *pst,          /* post structure */
PkMngmt *usta           /* configuration */
)
#else
PUBLIC S16 SmMiLpkStaInd(pst, usta)
Pst     *pst;          /* post structure */
PkMngmt *usta;          /* configuration */
#endif
{
   TRC2(SmMiLpkStaInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkStaInd(): txnId(%ld)\n", usta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkStaInd(): txnId(%d)\n", usta->hdr.transId));
#endif 
   /*-- Update Event --*/
   pst->event = LPK_EVT_STA_IND;

   SmMiLpkSendMsg(pst, usta, NULLP);

   RETVALUE(ROK);
} /* SmMiLpkStaInd */


/**
@brief This function is used by to present Trace Indication information to Layer Management.
@param pst 
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkTrcInd
(
Pst      *pst,          /* post structure */
PkMngmt  *trc,          /* trace indication */
Buffer   *mBuf          /* message buffer */
)
#else
PUBLIC S16 SmMiLpkTrcInd(pst,trc, mBuf)
Pst      *pst;          /* post structure */
PkMngmt  *trc;          /* trace indication */
Buffer   *mBuf;         /* message buffer */
#endif
{
   TRC2(SmMiLpkTrcInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkTrcInd(): txnId(%ld)\n", trc->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkTrcInd(): txnId(%d)\n", trc->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPK_EVT_TRC_IND;

   SmMiLpkSendMsg(pst, trc, mBuf);

   RETVALUE(ROK);
} /* SmMiLpkTrcInd */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
/**
@brief This function is used by to present Statistics confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkL2MeasCfm 
(
Pst     *pst,           /* post structure */
PkL2MeasCfmEvt *measEvt /* measuremnet */
)
#else
PUBLIC S16 SmMiLpkL2MeasCfm(pst, measEvt)
Pst     *pst;           /* post structure */
PkL2MeasCfmEvt *measEvt; /* measuremnet */
#endif
{
   TRC2(SmMiLpkL2MeasCfm);
   /*-- Update Event --*/
   pst->event = LPK_EVT_L2MEAS_CFM;

   SmMiLpkSendL2MeasMsg(pst, measEvt);


   RETVALUE(ROK);

} /* SmMiLpkStsCfm */

#ifdef ANSI
PUBLIC S16 SmMiLpjL2MeasStopCfm 
(
Pst     *pst,           /* post structure */
U8      measType,
U8      status
)
#else
PUBLIC S16 SmMiLpjL2MeasStopCfm(pst, measType, status)
Pst     *pst,           /* post structure */
U8      measType;
U8      status;
#endif
{
   TRC2(SmMiLpjL2MeasCfm);
   /*-- Update Event --*/
   pst->event = LPK_EVT_L2MEAS_CFM;

#if 0
   SmMiLkwSendL2MeasMsg(pst, measEvt);
#endif


   RETVALUE(ROK);

} /* SmMiLpjStsCfm */
#endif /*  LTE_L2_MEAS */
/* ####################################### ifndef KW_PDCP ################################## */
#else /*KW_PDCP */
/**
@brief 
@return CmXtaTCCb* 
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  kwAcLpkTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  kwAcLpkTstCbFind ()
#endif
{
   TRC2(kwAcLpkTstCbFind);

   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change SOAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP) &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif

   RETVALUE(NULLP);
} /* End of kwAcLpkTstCbFind */


/**
@brief utility function for sending the message to test engine 
@param pst 
@param cfm  
@param mBuf
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkSendMsg
(
Pst         *pst,
PkMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 SmMiLpkSendMsg(pst, cfm, mBuf)
Pst         *pst;
PkMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   KwAcMsgQElm *kwMsg;

   TRC3(SmMiLpkSendMsg);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkSendMsg(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkSendMsg(): txnId(%d)\n", cfm->hdr.transId));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the asmgciated test case */
   if ((tcCb = kwAcLpkTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, " kwAcLpkTstCbFind returning NULL...\n"));
      RETVALUE(ROK);
   }

   /*-- Allocate KW memory data --*/
   kwMsg = NULLP;
   CMXTA_ALLOC(&kwMsg, sizeof (KwAcMsgQElm));
   if (kwMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "SmMiLpkSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   kwMsg->mBuf = mBuf;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(kwMsg->u.kwMngmt), (U8 *)cfm, sizeof(PkMngmt));
   qElm.data = (Void *)kwMsg;
   qElm.msgFreeFun = kwAcUtlLpkFreeCb;


   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(ROK);

}
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS

/**
@brief utility function for sending the message to test engine 
@param pst 
@param cfm  
@param mBuf
@return ROK if it is successful
*/
#ifdef ANSI
PRIVATE S16 SmMiLpkSendL2MeasMsg
(
Pst         *pst,
PkL2MeasCfmEvt *measEvt
)
#else
PRIVATE S16 SmMiLpkSendL2MeasMsg(pst, measEvt)
Pst            *pst;
PkL2MeasCfmEvt *measEvt;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   KwAcMsgQElm *kwMsg;

   TRC3(SmMiLpkSendL2MeasMsg);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkSendL2MeasMsg(): txnId(%ld)\n", measEvt->transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkSendL2MeasMsg(): txnId(%d)\n", measEvt->transId));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the asmgciated test case */
   if ((tcCb = kwAcLpkTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, " kwAcLpkTstCbFind returning NULL...\n"));
      RETVALUE(ROK);
   }

   /*-- Allocate KW memory data --*/
   kwMsg = NULLP;
   CMXTA_ALLOC(&kwMsg, sizeof (KwAcMsgQElm));
   if (kwMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "SmMiLpkSendL2MeasMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(kwMsg->u.pkMeasCfmEvt), (U8 *)measEvt, 
          sizeof(PkL2MeasCfmEvt));
   qElm.data = (Void *)kwMsg;
   qElm.msgFreeFun = NULLP;

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(ROK);

}/* End of function SmMiLpkSendL2MeasMsg */
#endif

/**
@brief This function is used by to present configuration confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkCfgCfm
(
Pst     *pst,          /* post structure */
PkMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLpkCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
PkMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLpkCfgCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkCfgCfm(): txnId(%d)\n", cfm->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPK_EVT_CFG_CFM;

   SmMiLpkSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* SmMiLpkCfgCfm */


/**
@brief This function is used by to present control confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkCntrlCfm
(
Pst     *pst,          /* post structure */
PkMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLpkCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
PkMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLpkCntrlCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkCntrlCfm(): txnId(%d)\n", cfm->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPK_EVT_CNTRL_CFM;

   SmMiLpkSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* SmMiLpkCntrlCfm */


/**
@brief This function is used by to present Statistics confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkStsCfm 
(
Pst     *pst,          /* post structure */
Action  action,        /* Action */
PkMngmt *sts           /* statistics */
)
#else
PUBLIC S16 SmMiLpkStsCfm(pst, action, sts)
Pst     *pst;          /* post structure */
Action  action;        /* Action */
PkMngmt *sts;          /*  statistics */
#endif
{
   TRC2(SmMiLpkStsCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkStsCfm(): txnId(%ld)\n", sts->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkStsCfm(): txnId(%d)\n", sts->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPK_EVT_STS_CFM;

   SmMiLpkSendMsg(pst, sts, NULLP);


   RETVALUE(ROK);

} /* SmMiLpkStsCfm */


/**
@brief This function is used by to present Status confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkStaCfm
(
Pst     *pst,          /* post structure */
PkMngmt *sta           /* Status */
)
#else
PUBLIC S16 SmMiLpkStaCfm(pst,sta)
Pst     *pst;          /* post structure */
PkMngmt *sta;          /* Status */
#endif
{
   TRC2(SmMiLpkStaCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkStaCfm(): txnId(%ld)\n", sta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkStaCfm(): txnId(%d)\n", sta->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPK_EVT_STA_CFM;

   SmMiLpkSendMsg(pst, sta, NULLP);

   RETVALUE(ROK);
} /* SmMiLpkStaCfm */


/**
@brief This function is used by to present Status Indication information to Layer Management.
@param pst 
@param cfm
@return ROK if it is  successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkStaInd
(
Pst     *pst,          /* post structure */
PkMngmt *usta           /* configuration */
)
#else
PUBLIC S16 SmMiLpkStaInd(pst, usta)
Pst     *pst;          /* post structure */
PkMngmt *usta;          /* configuration */
#endif
{
   TRC2(SmMiLpkStaInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkStaInd(): txnId(%ld)\n", usta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkStaInd(): txnId(%d)\n", usta->hdr.transId));
#endif 
   /*-- Update Event --*/
   pst->event = LPK_EVT_STA_IND;

   SmMiLpkSendMsg(pst, usta, NULLP);

   RETVALUE(ROK);
} /* SmMiLpkStaInd */


/**
@brief This function is used by to present Trace Indication information to Layer Management.
@param pst 
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkTrcInd
(
Pst      *pst,          /* post structure */
PkMngmt  *trc,          /* trace indication */
Buffer   *mBuf          /* message buffer */
)
#else
PUBLIC S16 SmMiLpkTrcInd(pst,trc, mBuf)
Pst      *pst;          /* post structure */
PkMngmt  *trc;          /* trace indication */
Buffer   *mBuf;         /* message buffer */
#endif
{
   TRC2(SmMiLpkTrcInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkTrcInd(): txnId(%ld)\n", trc->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpkTrcInd(): txnId(%d)\n", trc->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPK_EVT_TRC_IND;

   SmMiLpkSendMsg(pst, trc, mBuf);

   RETVALUE(ROK);
} /* SmMiLpkTrcInd */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
/**
@brief This function is used by to present Statistics confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpkL2MeasCfm 
(
Pst     *pst,           /* post structure */
PkL2MeasCfmEvt *measEvt /* measuremnet */
)
#else
PUBLIC S16 SmMiLpkL2MeasCfm(pst, measEvt)
Pst     *pst;           /* post structure */
PkL2MeasCfmEvt *measEvt; /* measuremnet */
#endif
{
   TRC2(SmMiLpkL2MeasCfm);
   /*-- Update Event --*/
   pst->event = LPK_EVT_L2MEAS_CFM;

   SmMiLpkSendL2MeasMsg(pst, measEvt);


   RETVALUE(ROK);

} /* SmMiLpkStsCfm */
#endif /*  LTE_L2_MEAS */
#endif /* KW_PDCP */
/********************************************************************30**
         End of file:     pjac_lpkcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:21:01 2015
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
/main/1      ---       vb    1. LTE PDCP Release 2.1.
*********************************************************************91*/

