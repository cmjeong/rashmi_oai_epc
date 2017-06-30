
/********************************************************************20**

     Name:    eGTP - Layer

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    egac_hitcb.c

     Sid:      egac_hitcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:32 2015

     Prg:     an

*********************************************************************21*/

/* header include files (.h) */
#include "egac_acc.x"
#include "egac_hit.x"
#include "hit.h"
#include "hit.x"
#ifdef REVIEW
#include "eg_socklayer.h"
#endif

/*
*
*       Fun:   DHiLiHitBndReq
*
*       Desc:  Call handler for TSAP Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_hitcb.c
*
*/
#ifndef REVIEW
#ifdef ANSI
PUBLIC S16 DHiLiHitBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 DHiLiHitBndReq (pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(DHiLiHitBndReq)
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitBndReq() suId (%hd), spId (%hd)\n", suId, spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb*)egAcHitTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DHiLiHitBndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate eGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   egtpMsg->u.hitInfo.cmInfo.suId = suId;
   egtpMsg->u.hitInfo.cmInfo.spId = spId;

   qElm.data = (Void *)egtpMsg;
   qElm.msgFreeFun = egAcUtlHitCb;

   pst->event = EVTHITBNDREQ;
   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   /* Support for multiple queues */
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

   RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:   DHiLiHitUbndReq
*
*       Desc:  Call handler for TSAP Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_hitcb.c
*
*/
#ifdef ANSI
PUBLIC S16 DHiLiHitUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 DHiLiHitUbndReq      (pst, spId, reason)
Pst      *pst;
SpId     spId;
Reason   reason;
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(DHiLiHitUbndReq)

   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitUbndReq() reason (%hd), spId (%hd)", reason, spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = egAcHitTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DHiLiHitUbndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate eGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   egtpMsg->u.hitInfo.cmInfo.reason = reason;
   egtpMsg->u.hitInfo.cmInfo.spId = spId;

   qElm.data = (Void *)egtpMsg;
   qElm.msgFreeFun = egAcUtlHitCb;
   pst->event = EVTHITUBNDREQ;
   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

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

   RETVALUE(CMXTA_ERR_NONE);
}



/*
*
*       Fun:   DHiLiHitServOpenReq
*
*       Desc:  Call handler for TSAP Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_hitcb.c
*
*/
#ifdef ANSI
PUBLIC S16 DHiLiHitServOpenReq
(
Pst *pst,
SpId spId,
UConnId servConId,
CmTptAddr *servTAddr,
CmTptParam *tPar,
CmIcmpFilter *icmpFilter,
U8 srvcType
)
#else
PUBLIC S16 DHiLiHitServOpenReq  (pst, spId, servConId, servTAddr, tPar,
                                     icmpFilter, srvcType)
Pst            *pst;
SpId           spId;
UConnId        servConId;
CmTptAddr      *servTAddr;
CmTptParam     *tPar;
CmIcmpFilter   *icmpFilter;
U8             srvcType;
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(DHiLiHitServOpenReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitServOpenReq() spId (%hd), servConId (%d)", spId, servConId));
#else
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitServOpenReq() spId (%hd), servConId (%ld)", spId, servConId));
#endif

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = egAcHitTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/
      CMXTA_DBG_INFO((_cmxtap, "DHiLiHitServOpenReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate eGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   qElm.data = (Void *)egtpMsg;
   qElm.msgFreeFun = egAcUtlHitCb;
   pst->event = EVTHITSRVOPENREQ;
   /*-- Fill the message in the queue structure --*/
   egtpMsg->u.hitInfo.cmInfo.spId = spId;
   egtpMsg->u.hitInfo.suConId = servConId;
   egtpMsg->u.hitInfo.srvcType = egAcDHiUpdSrvType(srvcType);

   (Void) cmMemcpy((U8 *) &(egtpMsg->u.hitInfo.localAddr), (U8 *)servTAddr, sizeof(CmTptAddr));
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

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

   RETVALUE(CMXTA_ERR_NONE);
}



/*
*
*       Fun:   DHiLiHitConReq
*
*       Desc:  Call handler for TSAP Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_hitcb.c
*
*/
#ifdef ANSI
PUBLIC S16 DHiLiHitConReq
(
Pst *pst,
SpId spId,
UConnId suConId,
CmTptAddr *remAddr,
CmTptAddr *localAddr,
CmTptParam *tPar,
U8 srvcType
)
#else
PUBLIC S16 DHiLiHitConReq       (pst, spId, suConId, remAddr, localAddr, tPar, srvcType)
Pst         *pst;
SpId        spId;
UConnId     suConId;
CmTptAddr   *remAddr;
CmTptAddr   *localAddr;
CmTptParam  *tPar;
U8          srvcType;
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(DHiLiHitConReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitConReq() suConId (%d), spId (%hd)", suConId, spId));
#else
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitConReq() suConId (%ld), spId (%hd)", suConId, spId));
#endif

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = egAcHitTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DHiLiHitConReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate eGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   qElm.data = (Void *)egtpMsg;
   qElm.msgFreeFun = egAcUtlHitCb;
   pst->event = EVTHITCONREQ;
   /*-- Fill the message in the queue structure --*/
   egtpMsg->u.hitInfo.cmInfo.spId = spId;
   egtpMsg->u.hitInfo.suConId = suConId;
   egtpMsg->u.hitInfo.srvcType = egAcDHiUpdSrvType(srvcType);
   (Void) cmMemcpy((U8 *) &(egtpMsg->u.hitInfo.remAddr), (U8 *)remAddr, sizeof(CmTptAddr));
   (Void) cmMemcpy((U8 *) &(egtpMsg->u.hitInfo.localAddr), (U8 *)localAddr, sizeof(CmTptAddr));
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));


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

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   DHiLiHitConRsp
*
*       Desc:  Call handler for TSAP Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_hitcb.c
*
*/
#ifdef ANSI
PUBLIC S16 DHiLiHitConRsp
(
Pst *pst,
SpId spId,
UConnId suConId,
UConnId spConId
)
#else
PUBLIC S16 DHiLiHitConRsp       (pst, spId, suConId, spConId)
Pst         *pst;
SpId        spId;
UConnId     suConId;
UConnId     spConId;
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(DHiLiHitConRsp)

#ifdef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitConRsp() suConId (%d), spId (%hd)", suConId, spId));
#else
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitConRsp() suConId (%ld), spId (%hd)", suConId, spId));
#endif

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = egAcHitTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DHiLiHitConRsp(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate eGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   qElm.data = (Void *)egtpMsg;
   qElm.msgFreeFun = egAcUtlHitCb;
   pst->event = EVTHITCONRSP;
   /*-- Fill the message in the queue structure --*/
   egtpMsg->u.hitInfo.cmInfo.spId = spId;
   egtpMsg->u.hitInfo.suConId = suConId;
   egtpMsg->u.hitInfo.spConId = spConId;

   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));


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

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   DHiLiHitDatReq
*
*       Desc:  Call handler for TSAP Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_hitcb.c
*
*/
#ifdef ANSI
PUBLIC S16 DHiLiHitDatReq
(
Pst *pst,
SpId spId,
UConnId spConId,
Buffer *mBuf
)
#else
PUBLIC S16 DHiLiHitDatReq       (pst, spId, spConId, mBuf)
Pst      *pst;
SpId     spId;
UConnId  spConId;
Buffer   *mBuf;
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(DHiLiHitDatReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitDatReq() spConId (%d), spId (%hd)", spConId, spId));
#else
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitDatReq() spConId (%ld), spId (%hd)", spConId, spId));
#endif

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = egAcHitTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DHiLiHitDatReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate eGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   qElm.data = (Void *)egtpMsg;
   qElm.msgFreeFun = egAcUtlHitCb;
   pst->event = EVTHITDATREQ;
   /*-- Fill the message in the queue structure --*/
   egtpMsg->u.hitInfo.cmInfo.spId = spId;
   egtpMsg->u.hitInfo.spConId = spConId;
   /*-- SOAC_ENHANCE:  What to do with mBuf --*/

   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));


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

   RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:   DHiLiHitUDatReq
*
*       Desc:  Call handler for TSAP Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_hitcb.c
*
*/
#ifdef ANSI
PUBLIC S16 DHiLiHitUDatReq
(
Pst *pst,
SpId spId,
UConnId spConId,
CmTptAddr *remAddr,
CmTptAddr *srcAddr,
CmIpHdrParm *hdrParm,
CmTptParam *tPar,
Buffer *mBuf
)
#else
PUBLIC S16 DHiLiHitUDatReq      (pst, spId, spConId, remAddr, srcAddr,
                                    hdrParm, tPar, mBuf)
Pst            *pst;
SpId           spId;
UConnId        spConId;
CmTptAddr      *remAddr;
CmTptAddr      *srcAddr;
CmIpHdrParm    *hdrParm;
CmTptParam     *tPar;
Buffer         *mBuf;
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(DHiLiHitUDatReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitUDatReq() spConId (%d), spId (%hd)", spConId, spId));
#else
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitUDatReq() spConId (%ld), spId (%hd)", spConId, spId));
#endif

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = egAcHitTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DHiLiHitUDatReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }
      /*-- Allocate eGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   qElm.data = (Void *)egtpMsg;
   qElm.msgFreeFun = egAcUtlHitCb;
   pst->event = EVTHITUDATREQ;
   /*-- Fill the message in the queue structure --*/
   egtpMsg->u.hitInfo.cmInfo.spId = spId;
   egtpMsg->u.hitInfo.spConId = spConId;
   (Void) cmMemcpy((U8 *) &(egtpMsg->u.hitInfo.remAddr), (U8 *)remAddr, sizeof(CmTptAddr));
   (Void) cmMemcpy((U8 *) &(egtpMsg->u.hitInfo.localAddr), (U8 *)srcAddr, sizeof(CmTptAddr));
   (Void) cmMemcpy((U8 *) &(egtpMsg->u.hitInfo.hdrParm), (U8 *)hdrParm, sizeof(CmIpHdrParm));
   egtpMsg->u.hitInfo.mBuf = mBuf;

   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

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

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   DHiLiHitDiscReq
*
*       Desc:  Call handler for TSAP Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_hitcb.c
*
*/
#ifdef ANSI
PUBLIC S16 DHiLiHitDiscReq
(
Pst *pst,
SpId spId,
U8 choice,
UConnId conId,
Action action,
CmTptParam *tPar
)
#else
PUBLIC S16 DHiLiHitDiscReq      (pst, spId, choice, conId, action, tPar)
Pst            *pst;
SpId           spId;
U8             choice;
UConnId        conId;
Action         action;
CmTptParam     *tPar;
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(DHiLiHitDiscReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitDiscReq() conId (%d), spId (%hd)", conId, spId));
#else
   CMXTA_DBG_INFO((_cmxtap, "DHiLiHitDiscReq() conId (%ld), spId (%hd)", conId, spId));
#endif

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = egAcHitTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DHiLiHitDiscReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate eGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   egtpMsg->u.hitInfo.cmInfo.spId = spId;
   egtpMsg->u.hitInfo.choice = choice;
   egtpMsg->u.hitInfo.suConId = conId;
   egtpMsg->u.hitInfo.spConId = conId;
   egtpMsg->u.hitInfo.action = action;

   qElm.data = (Void *)egtpMsg;
   qElm.msgFreeFun = egAcUtlHitCb;
   pst->event = EVTHITDISCREQ;
   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));


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

   RETVALUE(CMXTA_ERR_NONE);
}
#else /*review */
/*
*
*       Fun:   egAcDHiUpdSrvType
*
*       Desc:  Call handler for TSAP Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_hitcb.c
*
*/
#ifdef ANSI
PUBLIC U8 egAcDHiUpdSrvType
(
U8 srvcType
)
#else
PUBLIC U8 egAcDHiUpdSrvType(srvcType)
U8 srvcType;
#endif
{
   U8 egtpTptProt;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcDHiUpdSrvType)

   CMXTA_DBG_INFO((_cmxtap, "egAcDHiUpdSrvType() srvcType (%d)", srvcType));

   switch(srvcType)
   {
      case HI_SRVC_TCP :
         egtpTptProt = LEG_TPTPROT_TCP;
         break;
      case HI_SRVC_UDP :
         egtpTptProt = LEG_TPTPROT_UDP;
         break;
      case HI_SRVC_UDP_PRIOR :
         egtpTptProt = LEG_TPTPROT_UDP_PRIOR;
         break;
#ifdef SO_TLS
#ifdef HI_TLS
      case HI_SRVC_TLS :
          egtpTptProt = LEG_TPTPROT_TLS_TCP;
          break;
#endif
#endif
      default:
         egtpTptProt = LEG_TPTPROT_UDP;
         break;
   }

   RETVALUE(egtpTptProt);
}



/*
*
*       Fun:   EgTLDiscServerReq
*
*       Desc:  
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_hitcb.c
*
*/
#ifdef ANSI
PUBLIC U32 EgTLDiscServerReq(UConnId conId)
#else
PUBLIC U32 EgTLDiscServerReq(conId)
UConnId conId;
#endif
{

RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:   EgTLOpenServerReq
*
*       Desc: 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_hitcb.c
*/
#ifdef ANSI
PUBLIC U32 EgTLOpenServerReq(Pst *pst,SpId spId,UConnId servConId,CmTptAddr *servTAddr)
#else
PUBLIC U32 EgTLOpenServerReq(pst,spId,servConId,servTAddr)
Pst *pst;
SpId spId;
UConnId servConId;
CmTptAddr *servTAddr;
#endif
{
   
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(EgTLOpenServerReq)

#ifdef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap, "DTLServOpenReq() spId (%hd), servConId (%d)", spId, servConId));
#else
   CMXTA_DBG_INFO((_cmxtap, "DTLServOpenReq() spId (%hd), servConId (%ld)", spId, servConId));
#endif

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = egAcHitTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/
      CMXTA_DBG_INFO((_cmxtap, "DTLServOpenReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate eGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   qElm.data = (Void *)egtpMsg;
   qElm.msgFreeFun = egAcUtlHitCb;
   pst->event = EVTHITSRVOPENREQ;
   /*-- Fill the message in the queue structure --*/
   egtpMsg->u.hitInfo.cmInfo.spId = spId;
   egtpMsg->u.hitInfo.suConId = servConId;
   egtpMsg->u.hitInfo.srvcType = egAcDHiUpdSrvType(HI_SRVC_UDP); /*egtp support udp only */ 

   (Void) cmMemcpy((U8 *) &(egtpMsg->u.hitInfo.localAddr), (U8 *)servTAddr, sizeof(CmTptAddr));
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

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
     RETVALUE(CMXTA_ERR_NONE);
}   


/*
*
*       Fun:   EgTLDatReq
*
*       Desc:  
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  egac_hitcb.c
*/
#ifdef ANSI
PUBLIC U32 EgTLDatReq(UConnId spConId,CmTptAddr *remAddr,CmTptAddr *srcAddr,
                      CmIpHdrParm *hdrParm,Buffer *mBuf)
#else
PUBLIC U32 EgTLDatReq(spConId,remAddr,srcAddr,hdrParm,mBuf)
UConnId spConId;
CmTptAddr *remAddr;
CmTptAddr *srcAddr;
CmIpHdrParm *hdrParm;
Buffer *mBuf;
#endif
{
   
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;
   Pst pst;
   EgTSapCb     *tSapCb=NULLP;
      /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(EgTLDatReq)
/* 
#ifdef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap, "DTLUDatReq() spConId (%d), spId (%hd)", spConId, spId));
#else
   CMXTA_DBG_INFO((_cmxtap, "DTLUDatReq() spConId (%ld), spId (%hd)", spConId, spId));
#endif
*/
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = egAcHitTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DTLUDatReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }
      /*-- Allocate eGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   qElm.data = (Void *)egtpMsg;
   qElm.msgFreeFun = egAcUtlHitCb; 
   tSapCb = egCb.tSapCb;
   /* fill the post structure */
   pst.dstProcId=tSapCb->pst.dstProcId;
   pst.srcProcId=tSapCb->pst.srcProcId;
   pst.dstEnt=tSapCb->pst.dstEnt;
   pst.dstInst=tSapCb->pst.dstInst;
   pst.srcEnt=tSapCb->pst.srcEnt;
   pst.srcInst=tSapCb->pst.srcInst;
   pst.prior=tSapCb->pst.prior;
   pst.route=tSapCb->pst.route;
   pst.event=tSapCb->pst.event;
   pst.region=tSapCb->pst.region;
   pst.pool=tSapCb->pst.pool;
   pst.selector=tSapCb->pst.selector;
   pst.intfVer=tSapCb->pst.intfVer;
   pst.event = EVTHITUDATREQ;
   /*----------------------------------------------*/

   /*-- Fill the message in the queue structure --*/
  /* egtpMsg->u.hitInfo.cmInfo.spId = spId; */
   egtpMsg->u.hitInfo.spConId =spConId; 
   (Void) cmMemcpy((U8 *) &(egtpMsg->u.hitInfo.remAddr), (U8 *)remAddr, sizeof(CmTptAddr));
   (Void) cmMemcpy((U8 *) &(egtpMsg->u.hitInfo.localAddr), (U8 *)srcAddr, sizeof(CmTptAddr));
   (Void) cmMemcpy((U8 *) &(egtpMsg->u.hitInfo.hdrParm), (U8 *)hdrParm, sizeof(CmIpHdrParm));
   egtpMsg->u.hitInfo.mBuf = mBuf;
  (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)&pst, sizeof(Pst));

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
      
      RETVALUE(CMXTA_ERR_NONE);
}
#endif

/********************************************************************30**

         End of file:     egac_hitcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:32 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      rss         1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3     eg003.201 psingh      1. Merged code from eg006.102 to Fix
                                     TRACE5 macro related issue
*********************************************************************91*/
