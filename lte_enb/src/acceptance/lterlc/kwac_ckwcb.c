

/********************************************************************20**
  
        Name:    CKW user interface
    
        Type:    C file
  
        Desc:    This file Contains the Acceptance Callback Primitive code
                  for CKW Interface
 
        File:    kwac_ckwcb.c

        Sid:      kwac_ckwcb.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:22 2014
  
        Prg:     chakrapani
  
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

#include "cm_xta.h"
#include "kwac_acc.h"      /* Acceptance defines */
#include "kwac_ckw.h"      /* CKW Acceptance defines */

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
#include "kw.h"            /* RLC defines */
#include "kw.x"

#include "cm_xta.x"
#include "kwac_acc.x"      /* Acceptance defines */
#include "kwac_ckw.x"      /* CKW Acceptance defines */

  
/*
*       Fun:   kwAcCkwTstCbFind
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_ckwcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  kwAcCkwTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  kwAcCkwTstCbFind ()
#endif
{
   TRC2(kwAcCkwTstCbFind);

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
} /* End of kwAcCkwTstCbFind */

  
/*
*
*       Fun:   kwAcCkwSendMsg
*
*       Desc:  Call handler for Saving Message
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  mgac_mgtcb.c
*
*/
#ifdef ANSI
PUBLIC S16 kwAcCkwSendMsg
(
Pst            *pst,
SuId           suId,
U8             status,
Void           *ptr
)
#else
PUBLIC S16 kwAcCkwSendMsg(pst, suId, status, ptr)
Pst            *pst;
SuId           suId;
U8             status;
Void           *ptr;
#endif /* ANSI */
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   KwAcMsgQElm    *kwElm;
   KwAcCkwInfo    *ckwInfo;
   S16            ret;
 
   TRC3(kwAcCkwSendMsg);
 
   CMXTA_DBG_PARAM((_cmxtap, "kwAcCkwSendMsg())\n"));

   ret = CMXTA_ERR_NONE;
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the associated test case */
   if ((tcCb = kwAcCkwTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious
        message, drop it --*/
      /*-- Update debug prints --*/
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped KWAC_ENHANCE: may be Sts Ind etc...\n"));
      RETVALUE(ROK);
   }

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
   qElm.msgFreeFun = kwAcUtlCkwFreeCb;
   ckwInfo = &(kwElm->u.ckwInfo);

   /*** fill the suId in teh Q element****/
   ckwInfo->cmInfo.suId = suId;

   switch (pst->event)
   {
      case CKW_EVT_BND_CFM:
      {
         ckwInfo->status = status;
         break;
      }
 
      case CKW_EVT_CFG_CFM:
      {
         ckwInfo->cfgCfm = (CkwCfgCfmInfo*)ptr;
         break;
      }

      case CKW_EVT_UEIDCHG_CFM:
      {
         ckwInfo->status = status;
         break;
      }
   } /* end of pst->evt */

   if( ret == ROK)
   {
      /*-- Test case found, queue the message for the tcCb --*/
      /* Push it onto the message queue --*/
      (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
 
      /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not
        trigger the test engine now in that case, the test engine
        will KWAC_ENHANCE have a look at the queued message --*/
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   } 
   else
   {
      CMXTA_FREE(kwElm, sizeof(KwAcMsgQElm));
   }
 
   RETVALUE(ret);
} /* end of kwAcCkwSendMsg() */

  
/*
*
*       Fun:   NhLiCkwBndCfm
*
*       Desc:  Call handler for Control Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  mgac_mgtcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCkwBndCfm
(
Pst            *pst,
SuId           suId,
U8             status
)
#else
PUBLIC S16 NhLiCkwBndCfm(pst, suId, status)
Pst            *pst;
SuId           suId;
U8             status;
#endif
{
   TRC2(NhLiCkwBndCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCkwBndCfm():\n"));

   pst->event = CKW_EVT_BND_CFM;
  
   kwAcCkwSendMsg(pst, suId, status, NULLP);
 
   RETVALUE(ROK);
} /* End of NhLiCkwBndCfm */

  
/*
*
*       Fun:   NhLiCkwCfgCfm
*
*       Desc:  Call handler for Control Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  mgac_mgtcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCkwCfgCfm
(
Pst            *pst,
SuId           suId,
CkwCfgCfmInfo  *cfmInfo
)
#else
PUBLIC S16 NhLiCkwCfgCfm(pst, suId, cfmInfo)
Pst            *pst;
SuId           suId;
CkwCfgCfmInfo  *cfmInfo;
#endif
{
   TRC2(NhLiCkwCfgCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCkwCfgCfm():\n"));

   pst->event = CKW_EVT_CFG_CFM;
  
   kwAcCkwSendMsg(pst, suId, 0, (Void*)cfmInfo);
 
   RETVALUE(ROK);
} /* End of NhLiCkwCfgCfm */

  
/*
*
*       Fun:   NhLiCkwUeIdChgCfm
*
*       Desc:  Call handler for Control Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  mgac_mgtcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCkwUeIdChgCfm
(
Pst            *pst,
SuId           suId,
U32            transId,
CkwUeInfo      *ueInfo,
CmStatus       status
)
#else
PUBLIC S16  NhLiCkwUeIdChgCfm(pst, suId, transId, ueInfo, status)
Pst            *pst;
SuId           suId;
U32            transId;
CkwUeInfo      *ueInfo;
CmStatus       status;
#endif
{

   TRC2(NhLiCkwUeIdChgCfm);

   /* kw005.201 removed warning */
   UNUSED(transId);
   CMXTA_DBG_PARAM((_cmxtap, " NhLiCkwUeIdChgCfm():\n"));

   pst->event = CKW_EVT_UEIDCHG_CFM;

   kwAcCkwSendMsg(pst, suId, (U8)status.status, NULLP);

   KW_FREE_ACC(ueInfo, sizeof(CkwUeInfo));

   RETVALUE(ROK);
} /* End of NhLiCkwUeIdChgCfm */


  
/********************************************************************30**
         End of file:     kwac_ckwcb.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:08:22 2014
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
/main/3      kw005.201 ap     1. Removed compilation warning
*********************************************************************91*/

