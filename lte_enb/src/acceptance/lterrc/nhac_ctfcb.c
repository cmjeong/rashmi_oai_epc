
/********************************************************************20**

     Name:   RRC

     Type:    C source file

     Desc:    PHY call back funtions.

     File:    nhac_ctfcb.c

     Sid:      nhac_ctfcb.c@@/main/2 - Fri Jul  1 01:13:00 2011

     Prg:     yk 

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
using namespace NH_LTERRC_REL11;
#include "nhac_nhu.x"

#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"
#include "nhac_acc_ctf.x"

EXTERN NhAccCb nhAccCb;

#if defined(DM) && defined(RRC_PHY_CFG_SUPP)
/*
*
*       Fun:   DmUiCtfBndReq
*
*       Desc:  PHY Bind Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_ctfhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCtfBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 DmUiCtfBndReq (pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCtfBndReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCtfBndReq() suId (%hd), spId (%hd)\n", suId, spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCtfTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCtfBndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCtfBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.ctfInfo.cmInfo.suId = suId;
   rrcMsg->u.ctfInfo.cmInfo.spId = spId;


   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCtfCb;

   pst->event = EVTCTFBNDREQ;

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg((CmXtaMsgQ *)&tcCb->msgQ, &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* DmUiCtfBndReq */



/*
*
*       Fun:   DmUiCtfUbndReq
*
*       Desc:  PHY UnBind Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_ctfhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCtfUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 DmUiCtfUbndReq (pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCtfUbndReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCtfUbndReq() , spId (%hd), reason(%hd)\n", spId, reason));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCtfTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCtfUbndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCtfBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.ctfInfo.cmInfo.spId = spId;
   rrcMsg->u.ctfInfo.cmInfo.reason = reason;

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCtfCb;

   pst->event = EVTCTFUBNDREQ;

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg((CmXtaMsgQ *)&tcCb->msgQ, &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* DmUiCtfUbndReq */



/*
*
*       Fun:   DmUiCtfCfgReq
*
*       Desc:  PHY Configuration Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_ctfhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCtfCfgReq
(
Pst *pst,
SpId spId,
CtfCfgTransId transId,
CtfCfgReqInfo *cfgReqInfo
)
#else
PUBLIC S16 DmUiCtfCfgReq (pst, spId, transId, cfgReqInfo)
Pst *pst;
SpId spId;
CtfCfgTransId transId;
CtfCfgReqInfo *cfgReqInfo;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;
   U32          rvrtTransId = 0;
   S16 ret=ROK;

   TRC2(DmUiCtfCfgReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCtfCfgReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   cmMemcpy((U8*)&rvrtTransId, (U8*)&transId.trans[5], sizeof(U32));

   if (rvrtTransId != NH_RESERVED_TRANS_ID)
   {
      if(ret != ROK)
      {
         CMXTA_DBG_INFO((_cmxtap,"\n VALIDATION :: CTF CFG FAILED \n"));
      }
   }

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCtfTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCtfCfgReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }
   if(nhAccCb.sndErrReq.expPhyErr)
   {
      /* Free memory allocated by RRC layer */
      CMXTA_FREE(cfgReqInfo, sizeof(CtfCfgReqInfo));
      if(pst->selector == 2)
      {
         nhAccCb.sndErrReq.rcvMacErr++;
         if(nhAccCb.sndErrReq.expPhyErr == nhAccCb.sndErrReq.rcvPhyErr)
            RETVALUE(RFAILED);
      }
      else
      {
         RETVALUE(ROK);
      }
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCtfCfgReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

  rrcMsg->u.ctfInfo.cfgInfo = *cfgReqInfo;
  
   rrcMsg->u.ctfInfo.cmInfo.spId = spId;
   /*rrcMsg->u.ctfInfo.cfgInfo.cfgType = cfgReqInfo->cfgTypes;
   rrcMsg->u.ctfInfo.cfgInfo.action = cfgReqInfo->action;*/
   cmMemcpy((U8*)&(rrcMsg->u.ctfInfo.transId),(U8*)&transId,sizeof(CtfCfgTransId));
   
   /* Free memory allocated by RRC layer */
   CMXTA_FREE(cfgReqInfo, sizeof(CtfCfgReqInfo));

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCtfCb;

   pst->event = EVTCTFCFGREQ;

     /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg((CmXtaMsgQ*)&tcCb->msgQ, &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* DmUiCtfCfgReq */


/*
*
*       Fun:  DmUiCtfUeIdChgReq 
*
*       Desc:  PHY Configuration Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_ctfcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCtfUeIdChgReq 
(
Pst            *pst,
SpId           spId,
CtfCfgTransId  transId,
CtfUeInfo      *ueInfo,
CtfUeInfo      *newUeInfo
)
#else
PUBLIC S16 DmUiCtfUeIdChgReq (pst, spId, transId, ueInfo, newUeInfo)
Pst            *pst;
SpId           spId;
CtfCfgTransId  transId;
CtfUeInfo      *ueInfo;
CtfUeInfo      *newUeInfo;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;
   
   TRC2(DmUiCtfUeIdChgReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCtfUeIdChgReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCtfTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCtfUeIdChgReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCtfUeIdChgReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   cmMemcpy((U8*)&(rrcMsg->u.ctfInfo.transId),(U8*)&transId,sizeof(CtfCfgTransId));

   (Void) cmMemcpy((U8 *) &(rrcMsg->u.ctfInfo.ueInfo), (U8 *)ueInfo,
                   sizeof(CtfUeInfo));
   (Void) cmMemcpy((U8 *) &(rrcMsg->u.ctfInfo.newUeInfo), (U8 *)newUeInfo,
                   sizeof(CtfUeInfo));
   rrcMsg->u.ctfInfo.ueInfo.ueId = ueInfo->ueId;
   rrcMsg->u.ctfInfo.ueInfo.cellId = ueInfo->cellId;

   rrcMsg->u.ctfInfo.newUeInfo.cellId = newUeInfo->ueId;
   rrcMsg->u.ctfInfo.newUeInfo.cellId = newUeInfo->cellId;

   rrcMsg->u.ctfInfo.cfgInfo.cfgType = NH_PHY_CFG_UEID_CHNG;
   rrcMsg->u.ctfInfo.cmInfo.spId = spId;
   
   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCtfCb;

   pst->event = EVTCTFUEIDCHGREQ;

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   (Void) cmXtaPushMsg((CmXtaMsgQ *)&tcCb->msgQ, &qElm);

  
   CMXTA_FREE(newUeInfo, sizeof(CtfUeInfo));
   CMXTA_FREE(ueInfo, sizeof(CtfUeInfo));
   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* DmUiCtfUeIdChgReq */

#endif /* ifdef DM && RRC_PHY_CFG_SUPP */

/**********************************************************************
         End of file:     nhac_ctfcb.c@@/main/2 - Fri Jul  1 01:13:00 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    yk               1. LTE RRC Initial Release.
/main/2      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
