
/********************************************************************20**

     Name:   RRC

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_kwucb.c

     Sid:      nhac_kwucb.c@@/main/3 - Fri Jul  1 01:13:02 2011

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
*       Fun:   DmUiKwuBndReq
*
*       Desc:  KWU Bind Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_kwucb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiKwuBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 DmUiKwuBndReq (pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiKwuBndReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiKwuBndReq() suId (%hd), spId (%hd)\n", suId, spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcKwuTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, "DmUiKwuBndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiKwuBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.kwuInfo.kwInfo.suId = suId;
   rrcMsg->u.kwuInfo.kwInfo.spId = spId;

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlKwuCb;

   pst->event = KWU_EVT_BND_REQ;

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
} /* DmUiKwuBndReq */


/*
*
*       Fun:   DmUiKwuUbndReq
*
*       Desc:  KWU UnBind Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_kwuhdl.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiKwuUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 DmUiKwuUbndReq (pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiKwuUbndReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiKwuUbndReq() , spId (%hd), \
                   reason(%hd)\n", spId, reason));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   if ((tcCb = (CmXtaTCCb*)nhAcKwuTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, "DmUiKwuUbndReq(): txn not found, \
                      msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiKwuBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.kwuInfo.kwInfo.spId = spId;
   rrcMsg->u.kwuInfo.kwInfo.reason = reason;

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlKwuCb;

   pst->event = KWU_EVT_UBND_REQ;

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
} /* DmUiKwuUbndReq */

/*
*
*       Fun:   DmUiKwuDatReq
*
*       Desc:  KWU Data Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_kwucb.c
*
*/
#ifdef ANSI
PUBLIC S16 DmUiKwuDatReq
(
Pst *pst,
SpId spId,
KwuDatReqInfo *cfg,
Buffer *mBuf
)
#else
PUBLIC S16 DmUiKwuDatReq(pst, spId, cfg, mBuf)
Pst *pst;
SpId spId;
KwuDatReqInfo *cfg;
Buffer *mBuf;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiKwuDatReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiKwuDatReq() , spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcKwuTstCbFind()) == NULLP)
   {
      CMXTA_DBG_INFO((_cmxtap, "DmUiKwuDatReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiKwuDatReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.kwuInfo.kwInfo.spId = spId;
   rrcMsg->u.kwuInfo.kwInfo.datReqInfo.rlcId = cfg->rlcId;
#ifdef CCPU_OPT
   rrcMsg->u.kwuInfo.kwInfo.datReqInfo.lcType = cfg->lcType;

   if ((cfg->lcType == CM_LTE_LCH_BCCH) ||
       (cfg->lcType == CM_LTE_LCH_PCCH))
   {
      cmMemcpy((U8 *) &(rrcMsg->u.kwuInfo.kwInfo.datReqInfo.tm.tmg), 
               (U8 *) &(cfg->tm.tmg), sizeof(CmLteTimingInfo));
   }
   else /* CCCH */
   {
      cmMemcpy((U8 *) &(rrcMsg->u.kwuInfo.kwInfo.datReqInfo.tm.rnti), 
               (U8 *) &(cfg->tm.rnti), sizeof(CmLteRnti));
   }
#endif

   /* Free Buffer Allocated by RRC , if not to be validated by handler 
    * otherwise copy this mBuf in rrcMsg and validate in hdl file .
    */
   if(nhAccCb.kwuCb.loop.loopBack == 1)
   {
      /* Loop Back Functionality */
      rrcMsg->mBuf = (Buffer *)mBuf;
   }
   else
   {
      /* Freeing the Buffer here results in a crash. */
      CMXTA_FREEMBUF(mBuf);
   }

   /* Free the datReq received from RRC */
   /*Commented as a local varibale is being passed from unpack funtion and not a pointer for which memory is allcoated*/
   /*CMXTA_FREE(cfg, sizeof(KwuDatReqInfo));*/

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlKwuCb;

   pst->event = KWU_EVT_DAT_REQ;

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   if (nhAccCb.reqFail.kwuDat)
   {
      nhAccCb.reqFail.kwuDat = FALSE;
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

}/* DmUiKwuDatReq*/
#endif /* ifdef DM */

/**********************************************************************
         End of file:     nhac_kwucb.c@@/main/3 - Fri Jul  1 01:13:02 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     rer              1. LTE RRC Initial Release.
/main/2      ---     chebli           1. RRC Release 2.1.
/main/3      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/


