/********************************************************************20**

     Name:   RRC

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_pjucb.c 

     Sid:      nhac_pjucb.c@@/main/3 - Fri Jul  1 01:13:07 2011

     Prg:     dm

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
*       Fun:   DmUiPjuBndReq
*
*       Desc:  PJU Bind Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_pjucb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiPjuBndReq
(
Pst *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 DmUiPjuBndReq (pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiPjuBndReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiPjuBndReq() suId (%hd), spId (%hd)\n", suId, spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcPjuTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiPjuBndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiPjuBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.pjuInfo.suId = suId;
   rrcMsg->u.pjuInfo.spId = spId;

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlPjuCb;

   pst->event = EVTPJUBNDREQ;

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
} /* DmUiPjuBndReq */


/*
*
*       Fun:   DmUiPjuUbndReq
*
*       Desc:  PJU UnBind Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_pjucb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiPjuUbndReq
(
Pst *pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 DmUiPjuUbndReq (pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiPjuUbndReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiPjuUbndReq() , spId (%hd), reason(%hd)\n", spId, reason));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   if ((tcCb = (CmXtaTCCb*)nhAcPjuTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiPjuUbndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiPjuBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.pjuInfo.spId = spId;
   rrcMsg->u.pjuInfo.reason = reason;

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlPjuCb;

   pst->event = EVTPJUUBNDREQ;

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
} /* DmUiPjuUbndReq */



/*
*
*       Fun:   DmUiPjuDatReq
*
*       Desc:  PJU Data Request 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_pjucb.c
*
*/
#ifdef ANSI
PUBLIC S16 DmUiPjuDatReq
(
Pst *pst,
SpId spId,
CmLtePdcpId *pdcpId,
PjuSduId sduId,
Buffer *mBuf
)
#else
PUBLIC S16 DmUiPjuDatReq(pst, spId, pdcpId, sduId, mBuf)
Pst *pst;
SpId spId;
CmLtePdcpId *pdcpId;
PjuSduId sduId;
Buffer *mBuf;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiPjuDatReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiPjuDatReq() , spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcPjuTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiPjuDatReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiPjuDatReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   nhAccCb.mui = sduId;

   rrcMsg->u.pjuInfo.spId = spId;
   rrcMsg->u.pjuInfo.pdcpId.cellId = pdcpId->cellId;
   rrcMsg->u.pjuInfo.pdcpId.ueId = pdcpId->ueId;
   rrcMsg->u.pjuInfo.pdcpId.rbId = pdcpId->rbId;

   

   /* Free Buffer Allocated by RRC , if not to be validated by handler 
    * otherwise copy this mBuf in rrcMsg and validate in hdl file .
    */
   if(nhAccCb.pjuCb.loopBack == 1)
   {
      /* Loop Back Functionality */
      rrcMsg->mBuf = (Buffer *)mBuf;
   }
   else
   {
      /* Freeing the Buffer here results in a crash. */
      CMXTA_FREEMBUF(mBuf);
   }

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlPjuCb;

   pst->event = EVTPJUDATREQ;

   /* Free the datReq received from RRC */
   /* While passing from RRC, it is changed to pass by value, hence commenting
      this free */
   /* CMXTA_FREE(pdcpId, sizeof(CmLtePdcpId)); */
      
   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   if (nhAccCb.reqFail.pjuDat)
   {
      nhAccCb.reqFail.pjuDat = FALSE;
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

}/* DmUiPjuDatReq*/

#endif /* ifdef DM */

/**********************************************************************
         End of file:     nhac_pjucb.c@@/main/3 - Fri Jul  1 01:13:07 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    dm               1. LTE RRC Initial Release.
/main/2      ---    chebli           1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/

