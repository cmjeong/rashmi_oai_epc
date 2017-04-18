

/********************************************************************20**

     Name:    LTE-RLC - acc test file

     Type:    C Source File

     Desc:    This file contains the acc source

     File:    kwac_kwucb.c

     Sid:      kwac_kwucb.c@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:43:09 2014

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
#include "kwac_kwu.h"      /* CKW Acceptance defines */

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
#include "kwac_kwu.x"      /* CKW Acceptance defines */



/**
@brief
@return CmXtaTCCb*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  kwAcKwuTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  kwAcKwuTstCbFind ()
#endif
{
   TRC2(kwAcKwuTstCbFind);

   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change KWAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif

   RETVALUE(NULLP);
} /* kwAcKwuTstCbFind */


/**
@brief utility function for sending the message to test engine
@param pst
@param suId
@param status
@param ptr
@param mBuf
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 kwAcKwuSendMsg
(
Pst            *pst,
SpId           suId,
U8             status,
Void           *ptr,
Buffer         *mBuf
)
#else
PUBLIC S16 kwAcKwuSendMsg(pst, suId, status, ptr, mBuf)
Pst            *pst;
SpId           suId;
U8             status;
Void           *ptr;
Buffer         *mBuf;
#endif /* ANSI */
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   KwAcMsgQElm    *kwElm;
   KwAcKwuInfo    *kwuInfo;

   S16 ret = CMXTA_ERR_NONE;
 
   TRC3(kwAcKwuSendMsg);

   CMXTA_DBG_PARAM((_cmxtap, "kwAcKwuSendMsg())\n"));

   CMXTA_ZERO(&qElm, sizeof(CmXtaMsgQElm));

   /*-- Find the asmgciated test case */
   if ((tcCb = kwAcKwuTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious
        message, drop it --*/
 
      /*-- Update debug prints --*/
      CMXTA_DBG_INFO((_cmxtap, "kwAcKwuTstCbFind is returning NULL...\n"));
      RETVALUE(ROK);
   }

   /*-- Check if any tapa directives set --*/
 
   /*-- Allocate KW memory data --*/
   kwElm = NULLP;
   CMXTA_ALLOC(&kwElm, sizeof (KwAcMsgQElm));
   if (kwElm == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "kwAcCkwSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)kwElm;
   qElm.msgFreeFun = kwAcUtlKwuFreeCb;
   
    /*** fill the suId in teh Q element****/
   kwuInfo = &(kwElm->u.kwuInfo);
   kwuInfo->cmInfo.suId = suId;

   switch (pst->event) 
   {
      case KWU_EVT_BND_CFM:
      {
         kwuInfo->u.status = status;
         break;
      }

      case KWU_EVT_DAT_IND:
      {
         kwuInfo->u.datInd = (KwuDatIndInfo*)ptr;
         kwElm->mBuf = mBuf; /* Take pointer of mBuf to Element */
         break;
      }

      case KWU_EVT_DAT_CFM:
      {
         kwuInfo->u.datCfm = (KwuDatCfmInfo*)ptr;
         break;
      }

      case KWU_EVT_STA_IND:
      {
         kwuInfo->u.staInd = (KwuStaIndInfo*)ptr;
         break;
      }
      /* kw005.201 added support for L2 measurement */
#ifdef LTE_L2_MEAS
      case KWU_EVT_DISC_SDU_CFM:
      {
         kwuInfo->u.discSduCfm = (KwuDiscSduInfo *)ptr;
         break;
      }
      case KWU_EVT_DAT_ACK_IND:
      {
         kwuInfo->u.datAckInd = (KwuDatAckInfo *)ptr;
         break;
      }
#endif
   }

   if( ret == ROK)
   {
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
   }
   else
   {
      CMXTA_FREE(kwElm, sizeof(KwAcMsgQElm));
   }

   RETVALUE(ROK);
} /* kwAcKwuSendMsg */

/**
@brief Call handler for Bind confirmation 
@param pst
@param suId
@param status
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 NhLiKwuBndCfm
(
Pst *pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 NhLiKwuBndCfm(pst,suId,status)
Pst *pst;
SuId suId;
U8 status;
#endif
{
   TRC2(NhLiKwuBndCfm);
   
   CMXTA_DBG_PARAM((_cmxtap, "NhLiKwuBndCfm():\n"));

   pst->event = KWU_EVT_BND_CFM;

   kwAcKwuSendMsg(pst, suId, status, NULLP, NULLP);

   RETVALUE(ROK);
} /* NhLiKwuBndCfm */

/**
@brief Call handler for Bind confirmation
@param pst
@param suId
@param status
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PjLiKwuBndCfm
(
Pst *pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 PjLiKwuBndCfm(pst,suId,status)
Pst *pst;
SuId suId;
U8 status;
#endif
{
   TRC2(PjLiKwuBndCfm);

   CMXTA_DBG_PARAM((_cmxtap, "PjLiKwuBndCfm():\n"));

   pst->event = KWU_EVT_BND_CFM;

   kwAcKwuSendMsg(pst, suId, status, NULLP, NULLP);

   RETVALUE(ROK);
} /* PjLiKwuBndCfm */

/**
@brief Call handler for Data Indication 
@param pst
@param suId
@param datInd
@param mBuf 
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 NhLiKwuDatInd
(
Pst            *pst,
SuId           suId,
KwuDatIndInfo  *datInd,
Buffer         *mBuf
)
#else
PUBLIC S16 NhLiKwuDatInd(pst, suId, datInd, mBuf)
Pst            *pst;
SuId           suId;
KwuDatIndInfo  *datInd;
Buffer         *mBuf;
#endif
{
   KwuDatIndInfo *tmpdatInd;
   TRC2(NhLiKwuDatInd);
   CMXTA_DBG_PARAM((_cmxtap, "PjLiKwuDatInd():\n"));

   KW_ALLOC_ACC(tmpdatInd, sizeof(KwuDatIndInfo));
   if(tmpdatInd == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "NhLiKwuDatInd(): KW_ALLOC pdcpId Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   tmpdatInd->rlcId.ueId   = datInd->rlcId.ueId;
   tmpdatInd->rlcId.cellId = datInd->rlcId.cellId;
   tmpdatInd->rlcId.rbId   = datInd->rlcId.rbId;
   tmpdatInd->rlcId.rbType = datInd->rlcId.rbType;
#ifdef CCPU_OPT   
   tmpdatInd->tCrnti = datInd->tCrnti;
#endif
   tmpdatInd->isOutOfSeq = datInd->isOutOfSeq;

   pst->event = KWU_EVT_DAT_IND;
   
   kwAcKwuSendMsg(pst, suId, 0, tmpdatInd, mBuf);
   RETVALUE(ROK); 
} /* NhLiKwuDatInd */

/**
@brief Call handler for Data Indication
@param pst
@param suId
@param datInd
@param mBuf
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PjLiKwuDatInd
(
Pst            *pst,
SuId           suId,
KwuDatIndInfo  *datInd,
Buffer         *mBuf
)
#else
PUBLIC S16 PjLiKwuDatInd(pst, suId, datInd, mBuf)
Pst            *pst;
SuId           suId;
KwuDatIndInfo  *datInd;
Buffer         *mBuf;
#endif
{
   KwuDatIndInfo *tmpdatInd;
   TRC2(PjLiKwuDatInd);
   CMXTA_DBG_PARAM((_cmxtap, "PjLiKwuDatInd():\n"));

   KW_ALLOC_ACC(tmpdatInd, sizeof(KwuDatIndInfo));
   if(tmpdatInd == NULLP)
   {
      CMXTA_DBG_FATAL((_cmxtap, "NhLiKwuDatInd(): KW_ALLOC pdcpId Failed\n"));
      RETVALUE(CMXTA_ERR_INT);
   }
   tmpdatInd->rlcId.ueId   = datInd->rlcId.ueId;
   tmpdatInd->rlcId.cellId = datInd->rlcId.cellId;
   tmpdatInd->rlcId.rbId   = datInd->rlcId.rbId;
   tmpdatInd->rlcId.rbType = datInd->rlcId.rbType;
#ifdef CCPU_OPT   
   tmpdatInd->tCrnti = datInd->tCrnti;
#endif
   tmpdatInd->isOutOfSeq = datInd->isOutOfSeq;

   pst->event = KWU_EVT_DAT_IND;
   
   kwAcKwuSendMsg(pst, suId, 0, tmpdatInd, mBuf);
   RETVALUE(ROK); 
} /* PjLiKwuDatInd */

/**
@brief Call handler for Data Confirmation
@param pst
@param suId
@param datCfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PjLiKwuDatCfm
(
Pst            *pst,
SuId           suId,
KwuDatCfmInfo  *datCfm
)
#else
PUBLIC S16 PjLiKwuDatCfm(pst, suId, datCfm)
Pst            *pst;
SuId           suId;
KwuDatCfmInfo  *datCfm;
#endif
{
   TRC2(PjLiKwuDatCfm);
   CMXTA_DBG_PARAM((_cmxtap, "PjLiKwuDatCfm():\n"));

   pst->event = KWU_EVT_DAT_CFM;
   
   kwAcKwuSendMsg(pst, suId, 0, datCfm, NULLP);
   RETVALUE(ROK); 
} /* PjLiKwuDatCfm */

/**
@brief Call handler for Status Indication
@param pst
@param suId
@param staInd
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PjLiKwuStaInd
(
Pst            *pst,
SuId           suId,
KwuStaIndInfo  *staInd
)
#else
PUBLIC S16 PjLiKwuStaInd(pst, suId, staInd)
Pst            *pst;
SuId           suId;
KwuStaIndInfo  *staInd;
#endif
{
   TRC2(PjLiKwuStaInd);
   CMXTA_DBG_PARAM((_cmxtap, "PjLiKwuStaInd():\n"));

   pst->event = KWU_EVT_STA_IND;
   
   kwAcKwuSendMsg(pst, suId, 0, staInd, NULLP);
   RETVALUE(ROK); 
} /* PjLiKwuStaInd */

/**
@brief Call handler for Re-establishment Complete Indication
@param pst
@param suId
@param rlcId
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PjLiKwuReEstCmpInd
(
Pst            *pst,
SuId           suId,
CmLteRlcId     rlcId
)
#else
PUBLIC S16 PjLiKwuReEstCmpInd(pst, suId, rlcId)
Pst            *pst;
SuId           suId;
CmLteRlcId     rlcId;
#endif
{
   TRC2(PjLiKwuReEstCmpInd);
   
   /* kw005.201 removed warning */
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(rlcId);
   CMXTA_DBG_PARAM((_cmxtap, "PjLiKwuReEstCmpInd():\n"));

   /* Drop the Re-establishment Complete indicaiton */

   RETVALUE(ROK); 
} /* PjLiKwuReEstCmpInd */




/**
@brief Call handler for Flow Control Indication
@param pst
@param suId
@param rlcId
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PjLiKwuFlowCntrlInd
(
Pst            *pst,
SuId           suId,
KwuFlowCntrlIndInfo    *flowCntrlIndInfo 
)
#else
PUBLIC S16 PjLiKwuFLowCntrlInd(pst, suId, flowCntrlIndInfo)
Pst            *pst;
SuId           suId;
KwuFlowCntrlIndInfo  *flowCntrlIndInfo;
#endif
{
   TRC2(PjLiKwuFlowCntrlInd);
   
   /* kw005.201 removed warning */
   UNUSED(pst);
   UNUSED(suId);
   UNUSED(flowCntrlIndInfo);
   CMXTA_DBG_PARAM((_cmxtap, "PjLiKwuFlowCntrlInd():\n"));

   /* To be implemented later */

   RETVALUE(ROK); 
} /* PjLiKwuFlowCntrlInd */






/* kw005.201 added support for L2 Measurement */
/**
@brief Call handler for SDU discard confirm
@param pst
@param suId
@param discCfm
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PjLiKwuDiscSduCfm
(
Pst            *pst,
SuId           suId,
KwuDiscSduInfo *discCfm
)
#else
PUBLIC S16 PjLiKwuDiscSduCfm(pst, suId, discCfm)
Pst            *pst;
SuId           suId;
KwuDiscSduInfo *discCfm;
#endif
{
   TRC2(PjLiKwuDiscSduCfm)
   CMXTA_DBG_PARAM((_cmxtap, "PjLiKwuDiscSduCfm():\n"));

   pst->event = KWU_EVT_DISC_SDU_CFM;
   
   kwAcKwuSendMsg(pst, suId, 0, discCfm, NULLP);
   RETVALUE(ROK); 
} /* PjLiKwuDiscSduCfm */


#if 0
#ifdef ANSI
PUBLIC S16 PjLiKwuFlowCntrlInd
(
Pst            *pst,
SuId           suId,
KwuFlowCntrlIndInfo *flowCntrlIndInfo
)
#else
PUBLIC S16 PjLiKwuFlowCntrlInd(pst, suId, flowCntrlIndInfo)
Pst            *pst;
SuId           suId;
KwuFlowCntrlIndInfo *flowCntrlIndInfo;
#endif
{
   TRC2(PjLiKwuFlowCntrlInd)
   CMXTA_DBG_PARAM((_cmxtap, "PjLiKwuFlowCntrlInd():\n"));

 //  pst->event = KWU_EVT_DISC_SDU_CFM;
   
  // kwAcKwuSendMsg(pst, suId, 0, flowCntrlIndInfoCfm, NULLP);
   RETVALUE(ROK); 
} /* PjLiKwuDiscSduCfm */

#endif
#ifdef LTE_L2_MEAS
/**
@brief Call handler for DatAckInd
@param pst
@param suId
@param datAckInd
@return ROK if it is successful
*/
#ifdef ANSI
PUBLIC S16 PjLiKwuDatAckInd
(
Pst            *pst,
SuId           suId,
KwuDatAckInfo  *datAckInd
)
#else
PUBLIC S16 PjLiKwuDatAckInd(pst, suId, datAckInd)
Pst            *pst;
SuId           suId;
KwuDatAckInfo  *datAckInd;
#endif
{
   TRC2(PjLiKwuDatAckInd)
   CMXTA_DBG_PARAM((_cmxtap, "PjLiKwuDatAckInd():\n"));

   pst->event = KWU_EVT_DAT_ACK_IND;
   
   kwAcKwuSendMsg(pst, suId, 0, datAckInd, NULLP);
   RETVALUE(ROK); 
} /* PjLiKwuDatAckInd */
#endif /* LTE_L2_MEAS */


U32 SGetTtiCount()
{
   U32 time;
   SGetSysTime(&time);
 
   return time;
}


/********************************************************************30**

         End of file:     kwac_kwucb.c@@/main/TeNB_Main_BR/5 - Mon Aug 11 16:43:09 2014

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
/main/2      ---   gk         1. LTE RLC Release 2.1.
/main/3      kw005.201 ap     1. Removed compilation warning.
                              2. Added support for L2 Measurement.
*********************************************************************91*/

