

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_lpjcb.c

     Sid:      kwac_lpjcb.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:34 2014

     Prg:     gk
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
#include "lpj.h"           /* LPJ defines */
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
#include "lpj.x"           /* LPJ */
#include "ckw.x"           /* CKW */
#include "cpj.x"           /* CPJ */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_lpj.x"      /* CKW Acceptance defines */


#ifdef KW_PDCP
/**
@brief 
@return CmXtaTCCb* 
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  kwAcLpjTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  kwAcLpjTstCbFind ()
#endif
{
   TRC2(kwAcLpjTstCbFind);

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
} /* End of kwAcLpjTstCbFind */


/**
@brief utility function for sending the message to test engine 
@param pst 
@param cfm  
@param mBuf
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpjSendMsg
(
Pst         *pst,
PjMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 SmMiLpjSendMsg(pst, cfm, mBuf)
Pst         *pst;
PjMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   KwAcMsgQElm *kwMsg;

   TRC3(SmMiLpjSendMsg);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjSendMsg(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjSendMsg(): txnId(%d)\n", cfm->hdr.transId));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the asmgciated test case */
   if ((tcCb = kwAcLpjTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, " kwAcLpjTstCbFind returning NULL...\n"));
      RETVALUE(ROK);
   }

   /*-- Allocate KW memory data --*/
   kwMsg = NULLP;
   CMXTA_ALLOC(&kwMsg, sizeof (KwAcMsgQElm));
   if (kwMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "SmMiLpjSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   kwMsg->mBuf = mBuf;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(kwMsg->u.kwMngmt), (U8 *)cfm, sizeof(PjMngmt));
   qElm.data = (Void *)kwMsg;
   qElm.msgFreeFun = kwAcUtlLpjFreeCb;


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
PRIVATE S16 SmMiLpjSendL2MeasMsg
(
Pst         *pst,
PjL2MeasCfmEvt *measEvt
)
#else
PRIVATE S16 SmMiLpjSendL2MeasMsg(pst, measEvt)
Pst            *pst;
PjL2MeasCfmEvt *measEvt;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   KwAcMsgQElm *kwMsg;

   TRC3(SmMiLpjSendL2MeasMsg);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjSendL2MeasMsg(): txnId(%ld)\n", measEvt->transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjSendL2MeasMsg(): txnId(%d)\n", measEvt->transId));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the asmgciated test case */
   if ((tcCb = kwAcLpjTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, " kwAcLpjTstCbFind returning NULL...\n"));
      RETVALUE(ROK);
   }

   /*-- Allocate KW memory data --*/
   kwMsg = NULLP;
   CMXTA_ALLOC(&kwMsg, sizeof (KwAcMsgQElm));
   if (kwMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "SmMiLpjSendL2MeasMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(kwMsg->u.pjMeasCfmEvt), (U8 *)measEvt, 
          sizeof(PjL2MeasCfmEvt));
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

}/* End of function SmMiLpjSendL2MeasMsg */
#endif

/**
@brief This function is used by to present configuration confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpjCfgCfm
(
Pst     *pst,          /* post structure */
PjMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLpjCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
PjMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLpjCfgCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjCfgCfm(): txnId(%d)\n", cfm->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPJ_EVT_CFG_CFM;

   SmMiLpjSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* SmMiLpjCfgCfm */


/**
@brief This function is used by to present control confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpjCntrlCfm
(
Pst     *pst,          /* post structure */
PjMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 SmMiLpjCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
PjMngmt *cfm;          /* configuration */
#endif
{
   TRC2(SmMiLpjCntrlCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjCntrlCfm(): txnId(%d)\n", cfm->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPJ_EVT_CNTRL_CFM;

   SmMiLpjSendMsg(pst, cfm, NULLP);

   RETVALUE(ROK);
} /* SmMiLpjCntrlCfm */


/**
@brief This function is used by to present Statistics confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpjStsCfm 
(
Pst     *pst,          /* post structure */
Action  action,        /* Action */
PjMngmt *sts           /* statistics */
)
#else
PUBLIC S16 SmMiLpjStsCfm(pst, action, sts)
Pst     *pst;          /* post structure */
Action  action;        /* Action */
PjMngmt *sts;          /*  statistics */
#endif
{
   TRC2(SmMiLpjStsCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjStsCfm(): txnId(%ld)\n", sts->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjStsCfm(): txnId(%d)\n", sts->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPJ_EVT_STS_CFM;

   SmMiLpjSendMsg(pst, sts, NULLP);


   RETVALUE(ROK);

} /* SmMiLpjStsCfm */


/**
@brief This function is used by to present Status confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpjStaCfm
(
Pst     *pst,          /* post structure */
PjMngmt *sta           /* Status */
)
#else
PUBLIC S16 SmMiLpjStaCfm(pst,sta)
Pst     *pst;          /* post structure */
PjMngmt *sta;          /* Status */
#endif
{
   TRC2(SmMiLpjStaCfm);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjStaCfm(): txnId(%ld)\n", sta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjStaCfm(): txnId(%d)\n", sta->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPJ_EVT_STA_CFM;

   SmMiLpjSendMsg(pst, sta, NULLP);

   RETVALUE(ROK);
} /* SmMiLpjStaCfm */


/**
@brief This function is used by to present Status Indication information to Layer Management.
@param pst 
@param cfm
@return ROK if it is  successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpjStaInd
(
Pst     *pst,          /* post structure */
PjMngmt *usta           /* configuration */
)
#else
PUBLIC S16 SmMiLpjStaInd(pst, usta)
Pst     *pst;          /* post structure */
PjMngmt *usta;          /* configuration */
#endif
{
   TRC2(SmMiLpjStaInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjStaInd(): txnId(%ld)\n", usta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjStaInd(): txnId(%d)\n", usta->hdr.transId));
#endif 
   /*-- Update Event --*/
   pst->event = LPJ_EVT_STA_IND;

   SmMiLpjSendMsg(pst, usta, NULLP);

   RETVALUE(ROK);
} /* SmMiLpjStaInd */


/**
@brief This function is used by to present Trace Indication information to Layer Management.
@param pst 
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpjTrcInd
(
Pst      *pst,          /* post structure */
PjMngmt  *trc,          /* trace indication */
Buffer   *mBuf          /* message buffer */
)
#else
PUBLIC S16 SmMiLpjTrcInd(pst,trc, mBuf)
Pst      *pst;          /* post structure */
PjMngmt  *trc;          /* trace indication */
Buffer   *mBuf;         /* message buffer */
#endif
{
   TRC2(SmMiLpjTrcInd);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjTrcInd(): txnId(%ld)\n", trc->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "SmMiLpjTrcInd(): txnId(%d)\n", trc->hdr.transId));
#endif
   /*-- Update Event --*/
   pst->event = LPJ_EVT_TRC_IND;

   SmMiLpjSendMsg(pst, trc, mBuf);

   RETVALUE(ROK);
} /* SmMiLpjTrcInd */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
/**
@brief This function is used by to present Statistics confirm information to Layer Management.
@param pst
@param cfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 SmMiLpjL2MeasCfm 
(
Pst     *pst,           /* post structure */
PjL2MeasCfmEvt *measEvt /* measuremnet */
)
#else
PUBLIC S16 SmMiLpjL2MeasCfm(pst, action, sts)
Pst     *pst,           /* post structure */
PjL2MeasCfmEvt *measEvt /* measuremnet */
#endif
{
   TRC2(SmMiLpjL2MeasCfm);
   /*-- Update Event --*/
   pst->event = LPJ_EVT_L2MEAS_CFM;

   SmMiLpjSendL2MeasMsg(pst, measEvt);


   RETVALUE(ROK);

} /* SmMiLpjStsCfm */
#endif /*  LTE_L2_MEAS */
#endif /* KW_PDCP */

/********************************************************************30**
         End of file:     kwac_lpjcb.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:34 2014
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
/main/1      ---       mn     1. LTERLC Release 2.1.
/main/2    kw005.201   ap     1. Added support for L2 Measurement.
*********************************************************************91*/


