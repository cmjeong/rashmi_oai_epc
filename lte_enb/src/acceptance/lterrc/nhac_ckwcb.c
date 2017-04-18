
/********************************************************************20**

     Name:   RRC

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_ckwcb.c

     Sid:      nhac_ckwcb.c@@/main/3 - Fri Jul  1 01:12:56 2011

     Prg:     rer

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

#ifdef DM
/*
*
*       Fun:   DmUiCkwBndReq
*
*       Desc:  RLC Bind Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_ckwhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCkwBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 DmUiCkwBndReq (pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCkwBndReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCkwBndReq() suId (%hd), spId (%hd)\n", suId, spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCkwTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCkwBndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCkwBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.ckwInfo.cmInfo.suId = suId;
   rrcMsg->u.ckwInfo.cmInfo.spId = spId;

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCkwCb;

   pst->event = CKW_EVT_BND_REQ;

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
} /* DmUiCkwBndReq */



/*
*
*       Fun:   DmUiCkwUBndReq
*
*       Desc:  MAC UnBind Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_ckwhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCkwUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 DmUiCkwUbndReq (pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCkwUbndReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCkwUbndReq() , spId (%hd), reason(%hd)\n", spId, reason));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCkwTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCkwUbndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCkwUbndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.ckwInfo.cmInfo.spId = spId;
   rrcMsg->u.ckwInfo.cmInfo.reason = reason;

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCkwCb;

   pst->event = CKW_EVT_UBND_REQ;

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
} /* DmUiCkwUbndReq */


/*
*
*       Fun:   DmUiCkwCfgReq
*
*       Desc:  MAC Configuration Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_ckwhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCkwCfgReq
(
Pst *pst,
SpId spId,
CkwCfgInfo *cfgInfo
)
#else
PUBLIC S16 DmUiCkwCfgReq (pst, spId, cfgInfo)
Pst *pst;
SpId spId;
CkwCfgInfo *cfgInfo;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCkwCfgReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCkwCfgReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   if ((tcCb = (CmXtaTCCb*)nhAcCkwTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCkwCfgReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }
   if(nhAccCb.sndErrReq.expRlcErr)
   {
      /* Free the cfgInfo received from RRC */
      CMXTA_FREE(cfgInfo, sizeof(CkwCfgInfo));
      if(pst->selector == 2)
      {
         nhAccCb.sndErrReq.rcvRlcErr++;
         if(nhAccCb.sndErrReq.expRlcErr == nhAccCb.sndErrReq.rcvRlcErr)
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
      CMXTA_DBG_ERR((_cmxtap, "DmUiCkwCfgReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.ckwInfo.cfgInfo = *cfgInfo;
   rrcMsg->u.ckwInfo.cmInfo.spId = spId;

   /* Free the cfgInfo received from RRC */
   CMXTA_FREE(cfgInfo, sizeof(CkwCfgInfo));
   
   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCkwCb;

   pst->event = CKW_EVT_CFG_REQ;

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   if (nhAccCb.reqFail.ckwCfg)
   {
      nhAccCb.reqFail.ckwCfg = FALSE;
      CMXTA_FREE(rrcMsg, sizeof (NhAccMsgQElm));
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);

      RETVALUE(RFAILED);
   }
   (Void) cmXtaPushMsg((CmXtaMsgQ *)&tcCb->msgQ, &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* DmUiCkwCfgReq */

/*
*
*       Fun:   DmUiCkwUeIdChgReq
*
*       Desc:  UE Id Change Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_ckwhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCkwUeIdChgReq
(
Pst *pst,
SpId spId,
U32 transId,
CkwUeInfo *ueInfo, 
CkwUeInfo *newUeInfo
)
#else
PUBLIC S16 DmUiCkwUeIdChgReq (pst, spId, transId, ueInfo, newUeInfo)
Pst *pst;
SpId spId;
U32 transId;
CkwUeInfo *ueInfo; 
CkwUeInfo *newUeInfo;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCkwUeIdChgReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCkwUeIdChgReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   if ((tcCb = (CmXtaTCCb*)nhAcCkwTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCkwUeIdChgReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCkwUeIdChgReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.ckwInfo.transId = transId;
   rrcMsg->u.ckwInfo.ueInfo = *ueInfo;
   rrcMsg->u.ckwInfo.newUeInfo = *newUeInfo;
   rrcMsg->u.ckwInfo.cmInfo.spId = spId;

   CMXTA_FREE(newUeInfo, sizeof(CkwUeInfo));
   CMXTA_FREE(ueInfo, sizeof(CkwUeInfo));
   
   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCkwCb;

   pst->event = CKW_EVT_UEIDCHG_REQ;

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   if (nhAccCb.reqFail.ueIdChg)
   {
      nhAccCb.reqFail.ueIdChg = FALSE;
      CMXTA_FREE(rrcMsg, sizeof (NhAccMsgQElm));
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);

      RETVALUE(RFAILED);
   }
   (Void) cmXtaPushMsg((CmXtaMsgQ *)&tcCb->msgQ, &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(CMXTA_ERR_NONE);
} /* DmUiCkwCfgReq */
#endif /* ifdef DM */

/**********************************************************************
         End of file:     nhac_ckwcb.c@@/main/3 - Fri Jul  1 01:12:56 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      rer                1. LTE RRC Initial Release.
/main/2      ---      ch                 1. RRC Release 2.1.
/main/3      ---      sbalakrishna       1. Updated for Release of 3.1
*********************************************************************91*/

