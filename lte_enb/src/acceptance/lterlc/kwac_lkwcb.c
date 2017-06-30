

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_lkwcb.c

     Sid:      kwac_lkwcb.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:31 2014

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
@brief 
@return CmXtaTCCb* 
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  kwAcLkwTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  kwAcLkwTstCbFind ()
#endif
{
   TRC2(kwAcLkwTstCbFind);

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
} /* End of kwAcLkwTstCbFind */


/**
@brief utility function for sending the message to test engine 
@param pst 
@param cfm  
@param mBuf
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLkwSendMsg
(
Pst         *pst,
KwMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 SmMiLkwSendMsg(pst, cfm, mBuf)
Pst         *pst;
KwMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   KwAcMsgQElm *kwMsg;

   TRC3(SmMiLkwSendMsg);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwSendMsg(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwSendMsg(): txnId(%d)\n", cfm->hdr.transId));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the asmgciated test case */
   if ((tcCb = kwAcLkwTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, " kwAcLkwTstCbFind returning NULL...\n"));
      RETVALUE(ROK);
   }

   /*-- Allocate KW memory data --*/
   kwMsg = NULLP;
   CMXTA_ALLOC(&kwMsg, sizeof (KwAcMsgQElm));
   if (kwMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "SmMiLkwSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   kwMsg->mBuf = mBuf;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(kwMsg->u.kwMngmt), (U8 *)cfm, sizeof(KwMngmt));
   qElm.data = (Void *)kwMsg;
   qElm.msgFreeFun = kwAcUtlLkwFreeCb;


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
PUBLIC S16 SmMiLkwSendL2MeasMsg
(
Pst         *pst,
KwL2MeasCfmEvt *measEvt
)
#else
PUBLIC S16 SmMiLkwSendL2MeasMsg(pst, measEvt)
Pst            *pst;
KwL2MeasCfmEvt *measEvt;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   KwAcMsgQElm *kwMsg;

   TRC3(SmMiLkwSendL2MeasMsg);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwSendL2MeasMsg(): txnId(%ld)\n", measEvt->transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwSendL2MeasMsg(): txnId(%d)\n", measEvt->transId));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the asmgciated test case */
   if ((tcCb = kwAcLkwTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, " kwAcLkwTstCbFind returning NULL...\n"));
      RETVALUE(ROK);
   }

   /*-- Allocate KW memory data --*/
   kwMsg = NULLP;
   CMXTA_ALLOC(&kwMsg, sizeof (KwAcMsgQElm));
   if (kwMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "SmMiLkwSendL2MeasMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(kwMsg->u.kwMeasCfmEvt), (U8 *)measEvt, 
          sizeof(KwL2MeasCfmEvt));
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

}/* End of function SmMiLkwSendL2MeasMsg */
#endif /* LTE_L2_MEAS */

/**
@brief This function is used by to present configuration confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLkwCfgCfm
(
Pst     *pst,          /* post structure */
KwMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLkwCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
KwMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLkwCfgCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwCfgCfm(): txnId(%d)\n", cfm->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LKW_EVT_CFG_CFM;

   SmMiLkwSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* SmMiLkwCfgCfm */


/**
@brief This function is used by to present control confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLkwCntrlCfm
(
Pst     *pst,          /* post structure */
KwMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLkwCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
KwMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLkwCntrlCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwCntrlCfm(): txnId(%d)\n", cfm->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LKW_EVT_CNTRL_CFM;

   SmMiLkwSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* SmMiLkwCntrlCfm */


/**
@brief This function is used by to present Statistics confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLkwStsCfm 
(
Pst     *pst,          /* post structure */
Action  action,        /* Action */
KwMngmt *sts           /* statistics */
)
#else
PUBLIC S16 SmMiLkwStsCfm(pst, action, sts)
Pst     *pst;          /* post structure */
Action  action;        /* Action */
KwMngmt *sts;          /*  statistics */
#endif
{
   TRC2(SmMiLkwStsCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwStsCfm(): txnId(%ld)\n", sts->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwStsCfm(): txnId(%d)\n", sts->hdr.transId));
#endif
   /* kw005.201 removed warning */
   UNUSED(action);
   /*-- Update Event --*/
   pst->event = LKW_EVT_STS_CFM;

   SmMiLkwSendMsg(pst, sts, NULLP);


   RETVALUE(ROK);

} /* SmMiLkwStsCfm */


/**
@brief This function is used by to present Status confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLkwStaCfm
(
Pst     *pst,          /* post structure */
KwMngmt *sta           /* Status */
)
#else
PUBLIC S16 SmMiLkwStaCfm(pst,sta)
Pst     *pst;          /* post structure */
KwMngmt *sta;          /* Status */
#endif
{
   TRC2(SmMiLkwStaCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwStaCfm(): txnId(%ld)\n", sta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwStaCfm(): txnId(%d)\n", sta->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LKW_EVT_STA_CFM;

   SmMiLkwSendMsg(pst, sta, NULLP);

   RETVALUE(ROK);
} /* SmMiLkwStaCfm */


/**
@brief This function is used by to present Status Indication information to Layer Management.
@param pst 
@param cfm
@return ROK if it is  successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLkwStaInd
(
Pst     *pst,          /* post structure */
KwMngmt *usta           /* configuration */
)
#else
PUBLIC S16 SmMiLkwStaInd(pst, usta)
Pst     *pst;          /* post structure */
KwMngmt *usta;          /* configuration */
#endif
{
   TRC2(SmMiLkwStaInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwStaInd(): txnId(%ld)\n", usta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwStaInd(): txnId(%d)\n", usta->hdr.transId));
#endif   
   /*-- Update Event --*/
   pst->event = LKW_EVT_STA_IND;

   SmMiLkwSendMsg(pst, usta, NULLP);

   RETVALUE(ROK);
} /* SmMiLkwStaInd */


/**
@brief This function is used by to present Trace Indication information to Layer Management.
@param pst 
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLkwTrcInd
(
Pst      *pst,          /* post structure */
KwMngmt  *trc,          /* trace indication */
Buffer   *mBuf          /* message buffer */
)
#else
PUBLIC S16 SmMiLkwTrcInd(pst,trc, mBuf)
Pst      *pst;          /* post structure */
KwMngmt  *trc;          /* trace indication */
Buffer   *mBuf;         /* message buffer */
#endif
{
   TRC2(SmMiLkwTrcInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwTrcInd(): txnId(%ld)\n", trc->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLkwTrcInd(): txnId(%d)\n", trc->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LKW_EVT_TRC_IND;

   SmMiLkwSendMsg(pst, trc, mBuf);

   RETVALUE(ROK);
} /* SmMiLkwTrcInd */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
/**
@brief This function is used by to present Statistics confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLkwL2MeasCfm 
(
Pst     *pst,           /* post structure */
KwL2MeasCfmEvt *measEvt /* measuremnet */
)
#else
PUBLIC S16 SmMiLkwL2MeasCfm(pst, action, sts)
Pst     *pst,           /* post structure */
KwL2MeasCfmEvt *measEvt /* measuremnet */
#endif
{
   TRC2(SmMiLkwL2MeasCfm);
   /*-- Update Event --*/
   pst->event = LKW_EVT_L2MEAS_CFM;

   SmMiLkwSendL2MeasMsg(pst, measEvt);


   RETVALUE(ROK);

} /* SmMiLpjStsCfm */

#ifdef ANSI
PUBLIC S16 SmMiLkwL2MeasStopCfm 
(
Pst     *pst,           /* post structure */
U8      measType,
U8      status
)
#else
PUBLIC S16 SmMiLkwL2MeasStopCfm(pst, measType, status)
Pst     *pst,           /* post structure */
U8      measType;
U8      status;
#endif
{
   TRC2(SmMiLkwL2MeasCfm);
   /*-- Update Event --*/
   pst->event = LKW_EVT_L2MEAS_CFM;

#if 0
   SmMiLkwSendL2MeasMsg(pst, measEvt);
#endif


   RETVALUE(ROK);

} /* SmMiLpjStsCfm */
#endif /*  LTE_L2_MEAS */
/********************************************************************30**
         End of file:     kwac_lkwcb.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:31 2014
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
/main/3      kw005.201 ap     1. Removed compilation warning
                              2. Added support for L2 Measurement.
*********************************************************************91*/


