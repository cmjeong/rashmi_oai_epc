

/********************************************************************20**
  
        Name:    CPJ user interface
    
        Type:    C file
  
        Desc:    This file Contains the Acceptance Callback Primitive code
                  for CPJ Interface
 
        File:    pjac_cpjcb.c

        Sid:      pjac_cpjcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:43 2015
  
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
#include "kwu.h"           /* KWU defines */
#include "cpj.h"           /* CPJ defines */
#include "lpj.h"           /* LPJ defines */
#include "pju.h"           /* PJU defines */
#include "pj_env.h"        /* RLC environment options */
#include "pj.h"            /* RLC defines */

#include "cm_xta.h"
#include "pjac_acc.h"      /* Acceptance defines */
#include "pjac_cpj.h"      /* CPJ Acceptance defines */

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
#include "kwu.x"           /* KWU */
#include "cpj.x"           /* CPJ */
#include "lpj.x"           /* LPJ */
#include "pju.x"           /* PJU */
#include "pj.x"

#include "cm_xta.x"
#include "pjac_acc.x"      /* Acceptance defines */
#include "pjac_cpj.x"      /* CPJ Acceptance defines */

#ifdef KW_PDCP
  
/*
*       Fun:   pjAcCpjTstCbFind
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  pjAcCpjTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  pjAcCpjTstCbFind ()
#endif
{
   TRC2(pjAcCpjTstCbFind);

   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change PJAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif

   RETVALUE(NULLP);
} /* End of pjAcCpjTstCbFind */

  
/*
*
*       Fun:   pjAcCpjSendMsg
*
*       Desc:  Call handler for Saving Message
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 pjAcCpjSendMsg
(
Pst            *pst,
SuId           suId,
U8             status,
Void           *ptr
)
#else
PUBLIC S16 pjAcCpjSendMsg(pst, suId, status, ptr)
Pst            *pst;
SuId           suId;
U8             status;
Void           *ptr;
#endif /* ANSI */
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   KwAcMsgQElm    *kwElm;
   KwAcCpjInfo    *cpjInfo;
   S16            ret;
 
   TRC3(pjAcCpjSendMsg);
 
   CMXTA_DBG_PARAM((_cmxtap, "pjAcCpjSendMsg())\n"));

   ret = CMXTA_ERR_NONE;
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the associated test case */
   if ((tcCb = pjAcCpjTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious
        message, drop it --*/
      /*-- Update debug prints --*/
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped PJAC_ENHANCE: may be Sts Ind etc...\n"));
      RETVALUE(ROK);
   }

   /*-- Allocate KW memory data --*/
   kwElm = NULLP;
   CMXTA_ALLOC(&kwElm, sizeof (KwAcMsgQElm));
   if (kwElm == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcCpjSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)kwElm;
   qElm.msgFreeFun = pjAcUtlCpjFreeCb;
   cpjInfo = &(kwElm->u.cpjInfo);

   /*** fill the suId in teh Q element****/
   cpjInfo->cmInfo.suId = suId;
   switch (pst->event)
   {
      case EVTCPJBNDCFM:
      {
         cpjInfo->u.status = status;
         break;
      }
 
      case EVTCPJCFGCFM:
      {
         cpjInfo->u.cfgCfm = (CpjCfgCfmInfo*)ptr;
         break;
      }

      case EVTCPJSECCFGCFM:
      {
         cpjInfo->u.secCfgCfm = (CpjSecCfgCfmInfo*)ptr;
         break;
      }

      case EVTCPJUEIDCHGCFM:
      {
         cpjInfo->u.status = status;
         break;
      }

      case EVTCPJREESTCFM:
      {
         cpjInfo->u.reEstCfm = (CpjReEstCfmInfo*)ptr;
         break;
      }

      case EVTCPJCOUNTCFM:
      {
         cpjInfo->u.countCfm = (CpjCountCfmInfo*)ptr;
         break;
      }

      case EVTCPJSDUSTACFM:
      {
         cpjInfo->u.sduStaCfm = (CpjSduStaCfmInfo*)ptr;
         break;
      }
      
      case EVTCPJDATRESUMECFM:
      {
         cpjInfo->u.datResCfm = (CpjDatResumeCfmInfo *)ptr;
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
        will PJAC_ENHANCE have a look at the queued message --*/
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   } 
   else
   {
      CMXTA_FREE(kwElm, sizeof(KwAcMsgQElm));
   }
 
   RETVALUE(ret);
} /* end of pjAcCpjSendMsg() */

  
/*
*
*       Fun:   NhLiCpjBndCfm
*
*       Desc:  Call handler for Bind Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjBndCfm
(
Pst            *pst,
SuId           suId,
U8             status
)
#else
PUBLIC S16 NhLiCpjBndCfm(pst, suId, status)
Pst            *pst;
SuId           suId;
U8             status;
#endif
{
   TRC2(NhLiCpjBndCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjBndCfm():\n"));

   pst->event = EVTCPJBNDCFM;
  
   pjAcCpjSendMsg(pst, suId, status, NULLP);
 
   RETVALUE(ROK);
} /* End of NhLiCpjBndCfm */

  
/*
*
*       Fun:   NhLiCpjCfgCfm
*
*       Desc:  Call handler for Configuration Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjCfgCfm
(
Pst            *pst,
SuId           suId,
CpjCfgCfmInfo  *cfmInfo
)
#else
PUBLIC S16 NhLiCpjCfgCfm(pst, suId, cfmInfo)
Pst            *pst;
SuId           suId;
CpjCfgCfmInfo  *cfmInfo;
#endif
{
   TRC2(NhLiCpjCfgCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjCfgCfm():\n"));

   pst->event = EVTCPJCFGCFM;
  
   pjAcCpjSendMsg(pst, suId, 0, (Void*)cfmInfo);
 
   RETVALUE(ROK);
} /* End of NhLiCpjCfgCfm */

  
/*
*
*       Fun:   NhLiCpjSecCfgCfm
*
*       Desc:  Call handler for Security Configuration Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjSecCfgCfm
(
Pst               *pst,
SuId              suId,
CpjSecCfgCfmInfo  *cfmInfo
)
#else
PUBLIC S16 NhLiCpjSecCfgCfm(pst, suId, cfmInfo)
Pst               *pst;
SuId              suId;
CpjSecCfgCfmInfo  *cfmInfo;
#endif
{
   TRC2(NhLiCpjSecCfgCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjSecCfgCfm():\n"));

   pst->event = EVTCPJSECCFGCFM;
  
   pjAcCpjSendMsg(pst, suId, 0, (Void*)cfmInfo);
 
   RETVALUE(ROK);
} /* End of NhLiCpjSecCfgCfm */

  
/*
*
*       Fun:   NhLiCpjUeIdChgCfm
*
*       Desc:  Call handler for UE ID Change Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjUeIdChgCfm
(
Pst            *pst,
SuId           suId,
U32            transId,
CpjUeInfo      *ueInfo,
CmStatus       status
)
#else
PUBLIC S16  NhLiCpjUeIdChgCfm(pst, suId, transId, ueInfo, status)
Pst            *pst;
SuId           suId;
U32            transId;
CpjUeInfo      *ueInfo;
CmStatus       status;
#endif
{

   TRC2(NhLiCpjUeIdChgCfm);

   CMXTA_DBG_PARAM((_cmxtap, " NhLiCpjUeIdChgCfm():\n"));

   pst->event = EVTCPJUEIDCHGCFM;

   pjAcCpjSendMsg(pst, suId, (U8)status.status, NULLP);

   KW_FREE_ACC(ueInfo, sizeof(CpjUeInfo));

   RETVALUE(ROK);
} /* End of NhLiCpjUeIdChgCfm */

  
/*
*
*       Fun:   NhLiCpjReEstCfm
*
*       Desc:  Call handler for Count Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjReEstCfm
(
Pst               *pst,
SuId              suId,
CpjReEstCfmInfo   *cfmInfo
)
#else
PUBLIC S16 NhLiCpjReEstCfm(pst, suId, cfmInfo)
Pst               *pst;
SuId              suId;
CpjReEstCfmInfo   *cfmInfo;
#endif
{
   TRC2(NhLiCpjReEstCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjReEstCfm():\n"));

   pst->event = EVTCPJREESTCFM;
  
   pjAcCpjSendMsg(pst, suId, 0, (Void*)cfmInfo);
 
   RETVALUE(ROK);
} /* End of NhLiCpjReEstCfm */

  
/*
*
*       Fun:   NhLiCpjCountCfm
*
*       Desc:  Call handler for Count Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjCountCfm
(
Pst               *pst,
SuId              suId,
CpjCountCfmInfo   *cfmInfo
)
#else
PUBLIC S16 NhLiCpjCountCfm(pst, suId, cfmInfo)
Pst               *pst;
SuId              suId;
CpjCountCfmInfo   *cfmInfo;
#endif
{
   TRC2(NhLiCpjCountCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjCountCfm():\n"));

   pst->event = EVTCPJCOUNTCFM;
  
   pjAcCpjSendMsg(pst, suId, 0, (Void*)cfmInfo);
 
   RETVALUE(ROK);
} /* End of NhLiCpjCountCfm */

/*
*
*       Fun:   NhLiCpjSduStaCfm
*
*       Desc:  Call handler for SDU Status Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjSduStaCfm
(
Pst               *pst,
SuId              suId,
CpjSduStaCfmInfo  *cfmInfo
)
#else
PUBLIC S16 NhLiCpjSduStaCfm(pst, suId, cfmInfo)
Pst               *pst;
SuId              suId;
CpjSduStaCfmInfo  *cfmInfo;
#endif
{
   TRC2(NhLiCpjSduStaCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjSduStaCfm():\n"));

   pst->event = EVTCPJSDUSTACFM;
  
   pjAcCpjSendMsg(pst, suId, 0, (Void*)cfmInfo);
 
   RETVALUE(ROK);
} /* End of NhLiCpjSduStaCfm */
/* ######################################ifndef KW_PDCP ########################### */
/* Venki - #ifndef */
#else
/*
*       Fun:   pjAcCpjTstCbFind
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  pjAcCpjTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  pjAcCpjTstCbFind ()
#endif
{
   TRC2(pjAcCpjTstCbFind);

   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change PJAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif

   RETVALUE(NULLP);
} /* End of pjAcCpjTstCbFind */

  
/*
*
*       Fun:   pjAcCpjSendMsg
*
*       Desc:  Call handler for Saving Message
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 pjAcCpjSendMsg
(
Pst            *pst,
SuId           suId,
U8             status,
Void           *ptr
)
#else
PUBLIC S16 pjAcCpjSendMsg(pst, suId, status, ptr)
Pst            *pst;
SuId           suId;
U8             status;
Void           *ptr;
#endif /* ANSI */
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   KwAcMsgQElm    *kwElm;
   KwAcCpjInfo    *cpjInfo;
   S16            ret;
 
   TRC3(pjAcCpjSendMsg);
 
   CMXTA_DBG_PARAM((_cmxtap, "pjAcCpjSendMsg())\n"));

   ret = CMXTA_ERR_NONE;
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the associated test case */
   if ((tcCb = pjAcCpjTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious
        message, drop it --*/
      /*-- Update debug prints --*/
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped PJAC_ENHANCE: may be Sts Ind etc...\n"));
      RETVALUE(ROK);
   }

   /*-- Allocate KW memory data --*/
   kwElm = NULLP;
   CMXTA_ALLOC(&kwElm, sizeof (KwAcMsgQElm));
   if (kwElm == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "pjAcCpjSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)kwElm;
   qElm.msgFreeFun = pjAcUtlCpjFreeCb;
   cpjInfo = &(kwElm->u.cpjInfo);

   /*** fill the suId in teh Q element****/
   cpjInfo->cmInfo.suId = suId;

   switch (pst->event)
   {
      case EVTCPJBNDCFM:
      {
         cpjInfo->u.status = status;
         break;
      }
 
      case EVTCPJCFGCFM:
      {
         cpjInfo->u.cfgCfm = (CpjCfgCfmInfo*)ptr;
         break;
      }

      case EVTCPJSECCFGCFM:
      {
         cpjInfo->u.secCfgCfm = (CpjSecCfgCfmInfo*)ptr;
         break;
      }

      case EVTCPJUEIDCHGCFM:
      {
         cpjInfo->u.status = status;
         break;
      }

      case EVTCPJREESTCFM:
      {
         cpjInfo->u.reEstCfm = (CpjReEstCfmInfo*)ptr;
         break;
      }

      case EVTCPJCOUNTCFM:
      {
         cpjInfo->u.countCfm = (CpjCountCfmInfo*)ptr;
         break;
      }

      case EVTCPJSDUSTACFM:
      {
         cpjInfo->u.sduStaCfm = (CpjSduStaCfmInfo*)ptr;
         break;
      }

      case EVTCPJDATRESUMECFM:
      {
         cpjInfo->u.datResCfm = (CpjDatResumeCfmInfo *)ptr;
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
        will PJAC_ENHANCE have a look at the queued message --*/
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   } 
   else
   {
      CMXTA_FREE(kwElm, sizeof(KwAcMsgQElm));
   }
 
   RETVALUE(ret);
} /* end of pjAcCpjSendMsg() */

  
/*
*
*       Fun:   NhLiCpjBndCfm
*
*       Desc:  Call handler for Bind Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjBndCfm
(
Pst            *pst,
SuId           suId,
U8             status
)
#else
PUBLIC S16 NhLiCpjBndCfm(pst, suId, status)
Pst            *pst;
SuId           suId;
U8             status;
#endif
{
   TRC2(NhLiCpjBndCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjBndCfm():\n"));

   pst->event = EVTCPJBNDCFM;
  
   pjAcCpjSendMsg(pst, suId, status, NULLP);
 
   RETVALUE(ROK);
} /* End of NhLiCpjBndCfm */

  
/*
*
*       Fun:   NhLiCpjCfgCfm
*
*       Desc:  Call handler for Configuration Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjCfgCfm
(
Pst            *pst,
SuId           suId,
CpjCfgCfmInfo  *cfmInfo
)
#else
PUBLIC S16 NhLiCpjCfgCfm(pst, suId, cfmInfo)
Pst            *pst;
SuId           suId;
CpjCfgCfmInfo  *cfmInfo;
#endif
{
   TRC2(NhLiCpjCfgCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjCfgCfm():\n"));

   pst->event = EVTCPJCFGCFM;
  
   pjAcCpjSendMsg(pst, suId, 0, (Void*)cfmInfo);
 
   RETVALUE(ROK);
} /* End of NhLiCpjCfgCfm */

  
/*
*
*       Fun:   NhLiCpjSecCfgCfm
*
*       Desc:  Call handler for Security Configuration Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjSecCfgCfm
(
Pst               *pst,
SuId              suId,
CpjSecCfgCfmInfo  *cfmInfo
)
#else
PUBLIC S16 NhLiCpjSecCfgCfm(pst, suId, cfmInfo)
Pst               *pst;
SuId              suId;
CpjSecCfgCfmInfo  *cfmInfo;
#endif
{
   TRC2(NhLiCpjSecCfgCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjSecCfgCfm():\n"));

   pst->event = EVTCPJSECCFGCFM;
  
   pjAcCpjSendMsg(pst, suId, 0, (Void*)cfmInfo);
 
   RETVALUE(ROK);
} /* End of NhLiCpjSecCfgCfm */

  
/*
*
*       Fun:   NhLiCpjUeIdChgCfm
*
*       Desc:  Call handler for UE ID Change Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjUeIdChgCfm
(
Pst            *pst,
SuId           suId,
U32            transId,
CpjUeInfo      *ueInfo,
CmStatus       status
)
#else
PUBLIC S16  NhLiCpjUeIdChgCfm(pst, suId, transId, ueInfo, status)
Pst            *pst;
SuId           suId;
U32            transId;
CpjUeInfo      *ueInfo;
CmStatus       status;
#endif
{

   TRC2(NhLiCpjUeIdChgCfm);

   CMXTA_DBG_PARAM((_cmxtap, " NhLiCpjUeIdChgCfm():\n"));

   pst->event = EVTCPJUEIDCHGCFM;

   pjAcCpjSendMsg(pst, suId, (U8)status.status, NULLP);

   KW_FREE_ACC(ueInfo, sizeof(CpjUeInfo));

   RETVALUE(ROK);
} /* End of NhLiCpjUeIdChgCfm */

  
/*
*
*       Fun:   NhLiCpjReEstCfm
*
*       Desc:  Call handler for Count Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjReEstCfm
(
Pst               *pst,
SuId              suId,
CpjReEstCfmInfo   *cfmInfo
)
#else
PUBLIC S16 NhLiCpjReEstCfm(pst, suId, cfmInfo)
Pst               *pst;
SuId              suId;
CpjReEstCfmInfo   *cfmInfo;
#endif
{
   TRC2(NhLiCpjReEstCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjReEstCfm():\n"));

   pst->event = EVTCPJREESTCFM;
  
   pjAcCpjSendMsg(pst, suId, 0, (Void*)cfmInfo);
 
   RETVALUE(ROK);
} /* End of NhLiCpjReEstCfm */

  
/*
*
*       Fun:   NhLiCpjCountCfm
*
*       Desc:  Call handler for Count Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjCountCfm
(
Pst               *pst,
SuId              suId,
CpjCountCfmInfo   *cfmInfo
)
#else
PUBLIC S16 NhLiCpjCountCfm(pst, suId, cfmInfo)
Pst               *pst;
SuId              suId;
CpjCountCfmInfo   *cfmInfo;
#endif
{
   TRC2(NhLiCpjCountCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjCountCfm():\n"));

   pst->event = EVTCPJCOUNTCFM;
  
   pjAcCpjSendMsg(pst, suId, 0, (Void*)cfmInfo);
 
   RETVALUE(ROK);
} /* End of NhLiCpjCountCfm */

  
/*
*
*       Fun:   NhLiCpjSduStaCfm
*
*       Desc:  Call handler for SDU Status Confirm
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  kwac_cpjcb.c
*
*/
#ifdef ANSI
PUBLIC S16 NhLiCpjSduStaCfm
(
Pst               *pst,
SuId              suId,
CpjSduStaCfmInfo  *cfmInfo
)
#else
PUBLIC S16 NhLiCpjSduStaCfm(pst, suId, cfmInfo)
Pst               *pst;
SuId              suId;
CpjSduStaCfmInfo  *cfmInfo;
#endif
{
   TRC2(NhLiCpjSduStaCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjSduStaCfm():\n"));

   pst->event = EVTCPJSDUSTACFM;
  
   pjAcCpjSendMsg(pst, suId, 0, (Void*)cfmInfo);
 
   RETVALUE(ROK);
} /* End of NhLiCpjSduStaCfm */

/*#ifdef ANSI
PUBLIC S16 NhLiCpjDatResumeCfm
(
Pst                  *pst,
SuId                 suId,
CpjDatResumeCfmInfo  *cfmInfo
)
#else
PUBLIC S16 NhLiCpjDatResumeCfm(pst, suId, cfmInfo)
Pst                  *pst;
SuId                 suId;
CpjDatResumeCfmInfo  *cfmInfo;
#endif
{
   TRC2(NhLiCpjSduStaCfm);
                                                                                                                                                                        
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjSduStaCfm():\n"));
                                                                                                                                                                        
   pst->event = EVTCPJDATRESUMECFM;
                                                                                                                                                                        
   pjAcCpjSendMsg(pst, suId, 0, (Void*)cfmInfo);
                                                                                                                                                                        
   RETVALUE(ROK);
} */ /* End of NhLiCpjSduStaCfm */
                                                                                                                                                                        

#ifdef ANSI
PUBLIC S16 NhLiCpjDatResumeCfm
(
Pst                  *pst,
SuId                 suId,
CpjDatResumeCfmInfo  *cfmInfo
)
#else
PUBLIC S16 NhLiCpjDatResumeCfm(pst, suId, cfmInfo)
Pst                  *pst;
SuId                 suId;
CpjDatResumeCfmInfo  *cfmInfo;
#endif
{
   TRC2(NhLiCpjSduStaCfm);
                                                                                                                                                                        
   CMXTA_DBG_PARAM((_cmxtap, "NhLiCpjSduStaCfm():\n"));
                                                                                                                                                                        
   pst->event = EVTCPJDATRESUMECFM;
                                                                                                                                                                        
   pjAcCpjSendMsg(pst, suId, 0, (Void*)cfmInfo);
                                                                                                                                                                        
   RETVALUE(ROK);
}

#endif /* KW_PDCP */

  
/********************************************************************30**
         End of file:     pjac_cpjcb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:20:43 2015
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
/main/1      ---     vb        1. LTE PDCP Initial Release 2.1.
*********************************************************************91*/
