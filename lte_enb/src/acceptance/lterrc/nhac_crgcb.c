
/********************************************************************20**

     Name:   RRC

     Type:    C source file

     Desc:    MAC call back funtions.

     File:    nhac_crgcb.c

     Sid:      nhac_crgcb.c@@/main/3 - Fri Jul  1 01:12:58 2011

     Prg:     chebli 

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

EXTERN NhAccCb nhAccCb;

#ifdef DM
/*
*
*       Fun:   DmUiCrgBndReq
*
*       Desc:  MAC Bind Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_crghdl.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCrgBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 DmUiCrgBndReq (pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCrgBndReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCrgBndReq() suId (%hd), spId (%hd)\n", suId, spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCrgTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCrgBndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCrgBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.crgInfo.cmInfo.suId = suId;
   rrcMsg->u.crgInfo.cmInfo.spId = spId;

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCrgCb;

   pst->event = EVTCRGBNDREQ;

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
} /* DmUiCrgBndReq */



/*
*
*       Fun:   DmUiCrgUbndReq
*
*       Desc:  MAC UnBind Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_crghdl.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCrgUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 DmUiCrgUbndReq (pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCrgUbndReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCrgUbndReq() , spId (%hd), reason(%hd)\n", spId, reason));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCrgTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCrgUbndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCrgBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.crgInfo.cmInfo.spId = spId;
   rrcMsg->u.crgInfo.cmInfo.reason = reason;

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCrgCb;

   pst->event = EVTCRGUBNDREQ;

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
} /* DmUiCrgUbndReq */



/*
*
*       Fun:   DmUiCrgCfgReq
*
*       Desc:  MAC Configuration Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_crghdl.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCrgCfgReq
(
Pst *pst,
SpId spId,
CrgCfgTransId transId,
CrgCfgReqInfo *cfgReqInfo
)
#else
PUBLIC S16 DmUiCrgCfgReq (pst, spId, transId, cfgReqInfo)
Pst *pst;
SpId spId;
CrgCfgTransId transId;
CrgCfgReqInfo *cfgReqInfo;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;
   U32          rvrtTransId = 0;
   S16 ret=ROK;

   TRC2(DmUiCrgCfgReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCrgCfgReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   cmMemcpy((U8*)&rvrtTransId, (U8*)&transId.trans[5], sizeof(U32));
   /* VALIDATE */
   if (rvrtTransId != NH_RESERVED_TRANS_ID)
   {
      if(ret != ROK)
      {
         CMXTA_DBG_INFO((_cmxtap,"\n VALIDATION :: CRG CFG FAILED \n"));
      }
   }

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCrgTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCrgCfgReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }
   if(nhAccCb.sndErrReq.expMacErr)
   {
      /* Free memory allocated by RRC layer */
      CMXTA_FREE(cfgReqInfo, sizeof(CrgCfgReqInfo));
      if(pst->selector == 2)
      {
         nhAccCb.sndErrReq.rcvMacErr++;
         if(nhAccCb.sndErrReq.expMacErr == nhAccCb.sndErrReq.rcvMacErr)
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
      CMXTA_DBG_ERR((_cmxtap, "DmUiCrgCfgReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

  rrcMsg->u.crgInfo.cfgInfo = *cfgReqInfo;
  
   rrcMsg->u.crgInfo.cmInfo.spId = spId;
   /*rrcMsg->u.crgInfo.cfgInfo.cfgType = cfgReqInfo->cfgTypes;
   rrcMsg->u.crgInfo.cfgInfo.action = cfgReqInfo->action;*/
   cmMemcpy((U8*)&(rrcMsg->u.crgInfo.transId),(U8*)&transId,sizeof(CrgCfgTransId));
   
   /* Write Validate Function to validate the cfg params */

   /* Free memory allocated by RRC layer */
   CMXTA_FREE(cfgReqInfo, sizeof(CrgCfgReqInfo));

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCrgCb;

   pst->event = EVTCRGCFGREQ;

     /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   if (nhAccCb.reqFail.crgCfg)
   {
      nhAccCb.reqFail.crgCfg = FALSE;
      CMXTA_FREE(rrcMsg, sizeof (NhAccMsgQElm));
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);

      RETVALUE(RFAILED);
   }
   (Void) cmXtaPushMsg((CmXtaMsgQ*)&tcCb->msgQ, &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* DmUiCrgCfgReq */

#endif /* ifdef DM */

/**********************************************************************
         End of file:     nhac_crgcb.c@@/main/3 - Fri Jul  1 01:12:58 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     chebli           1. LTE RRC Initial Release.
/main/2      ---     ch               1. RRC Release 2.1.
/main/3      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/
