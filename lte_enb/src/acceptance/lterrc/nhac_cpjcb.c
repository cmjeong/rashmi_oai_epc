/********************************************************************20**

     Name:   RRC

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_cpjcb.c 

     Sid:      nhac_cpjcb.c@@/main/3 - Fri Jul  1 01:12:57 2011

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
using namespace NH_LTERRC_REL11;
#include "nhac_nhu.x"
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"

#include "nhac_acc.x"
#include "nhac_acc_cpj.x"

#ifdef DM
/*
*
*       Fun:  DmUiCpjBndReq 
*
*       Desc:  PDCP Bind Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_cpjcb.c 
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCpjBndReq 
(
Pst *pst,
SuId suId,
SpId spId
)
#else
PUBLIC S16 DmUiCpjBndReq (pst, suId, spId)
Pst *pst;
SuId suId;
SpId spId;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCpjBndReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCpjBndReq() suId (%hd), spId (%hd)\n", suId, spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCpjTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCpjBndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCpjBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }


   rrcMsg->u.cpjInfo.cmInfo.suId = suId;
   rrcMsg->u.cpjInfo.cmInfo.spId = spId;

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCpjCb;

   pst->event = EVTCPJBNDREQ;

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
} /* DmUiCpjBndReq */



/*
*
*       Fun:   DmUiCpjUbndReq 
*
*       Desc:  PDCP UnBind Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File: nhac_cpjcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCpjUbndReq 
(
Pst *pst,
SpId spId,
Reason reason
)
#else
PUBLIC S16 DmUiCpjUbndReq (pst, spId, reason)
Pst *pst;
SpId spId;
Reason reason;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCpjUbndReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCpjUbndReq() , spId (%hd), reason(%hd)\n", spId, reason));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCpjTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCpjUbndReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCpjUbndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.cpjInfo.cmInfo.spId = spId;
   rrcMsg->u.cpjInfo.cmInfo.reason = reason;

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCpjCb;

   pst->event = EVTCPJUBNDREQ;

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   if (nhAccCb.reqFail.cpjCfg)
   {
      nhAccCb.reqFail.cpjCfg = FALSE;
      CMXTA_FREE(rrcMsg, sizeof (NhAccMsgQElm));
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);

      RETVALUE(RFAILED);
   }
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
} /* DmUiCpjUbndReq */

/*
*
*       Fun:  DmUiCpjCfgReq 
*
*       Desc:  PDCP Configuration Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_cpjcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCpjCfgReq 
(
Pst *pst,
SpId spId,
CpjCfgReqInfo *cfgInfo
)
#else
PUBLIC S16 DmUiCpjCfgReq (pst, spId, cfgInfo)
Pst *pst;
SpId spId;
CpjCfgReqInfo *cfgInfo;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;
   S16   idx=0;
   U32   bitMapSz=0;
   
   TRC2(DmUiCpjCfgReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCpjCfgReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCpjTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCpjCfgReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }
   if(nhAccCb.sndErrReq.expPdcpErr)
   {
      /* Free the cfgInfo received from RRC */
      CMXTA_FREE(cfgInfo, sizeof(CpjCfgReqInfo)); 
      if(pst->selector == 2)
      {
         nhAccCb.sndErrReq.rcvPdcpErr++;
         if(nhAccCb.sndErrReq.expPdcpErr == nhAccCb.sndErrReq.rcvPdcpErr)
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
      CMXTA_DBG_ERR((_cmxtap, "DmUiCpjCfgReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*store the entire config structure -validation change */
   rrcMsg->u.cpjInfo.cfgInfo = *cfgInfo;
   rrcMsg->u.cpjInfo.transId = cfgInfo->transId;
   rrcMsg->u.cpjInfo.cmInfo.spId = spId;
  
   /* Free all allocated pointers inside CpjCfgReqInfo */
   for(idx=0; idx < cfgInfo->numEnt; idx++)
   {
      if ((cfgInfo->cfgEnt[idx].cfgType == CPJ_CFG_MODIFY) &&
          (cfgInfo->cfgEnt[idx].m.modCfg.hoInfo.numBits))
      {
         bitMapSz = (cfgInfo->cfgEnt[idx].m.modCfg.hoInfo.numBits)/8;
         if (cfgInfo->cfgEnt[idx].m.modCfg.hoInfo.numBits % 8 != 0)
            bitMapSz++;
         CMXTA_FREE(cfgInfo->cfgEnt[idx].m.modCfg.hoInfo.ulBitMap, 
            (sizeof(U8) * bitMapSz));
      }
   }

   /* Free the cfgInfo received from RRC */
   CMXTA_FREE(cfgInfo, sizeof(CpjCfgReqInfo)); 
   
   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCpjCb;

   pst->event = EVTCPJCFGREQ;

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   if (nhAccCb.reqFail.cpjCfg)
   {
      nhAccCb.reqFail.cpjCfg = FALSE;
      CMXTA_FREE(rrcMsg, sizeof (NhAccMsgQElm));
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);

      RETVALUE(RFAILED);
   }
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
} /* DmUiCpjCfgReq */

/*
*
*       Fun:  DmUiCpjUeIdChgReq 
*
*       Desc:  PDCP Configuration Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_cpjcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCpjUeIdChgReq 
(
Pst       *pst,
SpId      spId,
U32       transId,
CpjUeInfo *ueInfo,
CpjUeInfo *newUeInfo
)
#else
PUBLIC S16 DmUiCpjUeIdChgReq (pst, spId, transId, ueInfo, newUeInfo)
Pst       *pst;
SpId      spId;
U32       transId;
CpjUeInfo *ueInfo;
CpjUeInfo *newUeInfo;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;
   
   TRC2(DmUiCpjUeIdChgReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCpjUeIdChgReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCpjTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCpjUeIdChgReq(): txn not found, msg dropped \n"));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCpjUeIdChgReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.cpjInfo.transId = transId;
   (Void) cmMemcpy((U8 *) &(rrcMsg->u.cpjInfo.ueInfo), (U8 *)ueInfo,
                   sizeof(CpjUeInfo));
   (Void) cmMemcpy((U8 *) &(rrcMsg->u.cpjInfo.newUeInfo), (U8 *)newUeInfo,
                   sizeof(CpjUeInfo));
   rrcMsg->u.cpjInfo.cmInfo.spId = spId;

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCpjCb;

   pst->event = EVTCPJUEIDCHGREQ;

   CMXTA_FREE(newUeInfo, sizeof(CpjUeInfo));
   CMXTA_FREE(ueInfo, sizeof(CpjUeInfo));

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   if (nhAccCb.reqFail.cpjCfg)
   {
      nhAccCb.reqFail.cpjCfg = FALSE;
      CMXTA_FREE(rrcMsg, sizeof (NhAccMsgQElm));
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);

      RETVALUE(RFAILED);
   }
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
} /* DmUiCpjUeIdChgReq */


/*
*
*       Fun:  DmUiCpjSecCfgReq 
*
*       Desc:  PDCP Security Configuration Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_cpjcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCpjSecCfgReq 
(
Pst *pst,
SpId spId,
CpjSecCfgReqInfo *secCfgInfo
)
#else
PUBLIC S16 DmUiCpjSecCfgReq (pst, spId, secCfgInfo)
Pst *pst;
SpId spId;
CpjSecCfgReqInfo *secCfgInfo;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCpjSecCfgReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCpjSecCfgReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCpjTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCpjSecCfgReq(): txn not found, msg dropped \n"));
      CMXTA_FREE(secCfgInfo, sizeof(CpjSecCfgReqInfo));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCpjSecCfgReq(): resource error\n"));
      CMXTA_FREE(secCfgInfo, sizeof(CpjSecCfgReqInfo));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.cpjInfo.transId = secCfgInfo->transId;
   rrcMsg->u.cpjInfo.cmInfo.spId = spId;
   rrcMsg->u.cpjInfo.secCfgInfo.ueId = secCfgInfo->ueId;
   rrcMsg->u.cpjInfo.secCfgInfo.cellId = secCfgInfo->cellId;
   rrcMsg->u.cpjInfo.secCfgInfo.transId = secCfgInfo->transId;
   rrcMsg->mBuf = (Buffer *)secCfgInfo;

   /* Free the Sec Cfg Info received from RRC */
   CMXTA_FREE(secCfgInfo, sizeof(CpjSecCfgReqInfo));

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCpjCb;

   pst->event = EVTCPJSECCFGREQ;

   /*-- Fill the message in the queue structure --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   if (nhAccCb.reqFail.cpjCfg)
   {
      nhAccCb.reqFail.cpjCfg = FALSE;
      CMXTA_FREE(rrcMsg, sizeof (NhAccMsgQElm));
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);

      RETVALUE(RFAILED);
   }

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
} /*  End of DmUiCpjSecCfgReq */

/*
*
*       Fun:  DmUiCpjCountReq 
*
*       Desc:  PDCP count Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_cpjcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCpjCountReq
(
Pst *pst,
SpId spId,
CpjCountReqInfo *countReqInfo
)
#else
PUBLIC S16 DmUiCpjCountReq (pst, spId, countReqInfo)
Pst *pst;
SpId spId;
CpjCountReqInfo *countReqInfo;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCpjCountReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCpjCountReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCpjTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCpjCountReq(): txn not found, msg dropped \n"));
      CMXTA_FREE(countReqInfo, sizeof(CpjCountReqInfo));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCpjCountReq(): resource error\n"));
      CMXTA_FREE(countReqInfo, sizeof(CpjCountReqInfo));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.cpjInfo.transId = countReqInfo->transId;
   rrcMsg->u.cpjInfo.cmInfo.spId = spId;
   rrcMsg->u.cpjInfo.ueInfo.ueId = countReqInfo->ueId;
   rrcMsg->u.cpjInfo.ueInfo.cellId = countReqInfo->cellId;
   /*(Void) cmMemcpy((U8 *) &(rrcMsg->mBuf), (U8 *)countReqInfo,
                   sizeof(CpjCountReqInfo));
                   */
   rrcMsg->mBuf = (Buffer *) countReqInfo;

   /* Free the Count Req Info received from RRC */
   CMXTA_FREE(countReqInfo, sizeof(CpjCountReqInfo));

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCpjCb;

   pst->event = EVTCPJCOUNTREQ;

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
} /* End of DmUiCpjCountReq */

/*
*
*       Fun:  DmUiCpjStartDataFwdReq 
*
*       Desc:  PDCP Start data forward  Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_cpjcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCpjStartDataFwdReq
(
Pst *pst,
SpId spId,
CpjDataFwdReqInfo *sduStartDataFwdReqInfo
)
#else
PUBLIC S16 DmUiCpjStartDataFwdReq (pst, spId, sduStartDataFwdReqInfo)
Pst *pst;
SpId spId;
CpjDataFwdReqInfo *sduStartDataFwdReqInfo;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;
   
   TRC2(DmUiCpjStartDataFwdReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCpjStartDataFwdReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCpjTstCbFind()) == NULLP)
   {
     /*-- No associated test case found, spurious message, * drop it --*/

     CMXTA_DBG_INFO((_cmxtap, "DmUiCpjStartDataFwdReq(): txn not found, msg dropped \n"));
     CMXTA_FREE(sduStartDataFwdReqInfo, sizeof(CpjDataFwdReqInfo));
     RETVALUE(CMXTA_ERR_NONE);
   }
   
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
     CMXTA_DBG_ERR((_cmxtap, "DmUiCpjStartDataFwdReq(): resource error\n"));
     CMXTA_FREE(sduStartDataFwdReqInfo, sizeof(CpjDataFwdReqInfo));
     RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.cpjInfo.transId = sduStartDataFwdReqInfo->transId;
   rrcMsg->u.cpjInfo.cmInfo.spId = spId;
   rrcMsg->u.cpjInfo.ueInfo.ueId = sduStartDataFwdReqInfo->ueId;
   rrcMsg->u.cpjInfo.ueInfo.cellId = sduStartDataFwdReqInfo->cellId;

   rrcMsg->mBuf = (Buffer *) sduStartDataFwdReqInfo;

   CMXTA_FREE(sduStartDataFwdReqInfo, sizeof(CpjDataFwdReqInfo));

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCpjCb;

   pst->event = EVTCPJSTARTDATAFWDREQ;

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
}

/*
*
*       Fun:  DmUiCpjDatResumeReq
*
*       Desc:  PDCP data resume  Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_cpjcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCpjDatResumeReq
(
Pst *pst,
SpId spId,
CpjDatResumeReqInfo *sduDatResumeReqInfo
)
#else
PUBLIC S16 DmUiCpjDatResumeReq (pst, spId, sduDatResumeReqInfo)
Pst *pst;
SpId spId;
CpjDatResumeReqInfo *sduDatResumeReqInfo;
#endif
{
   RETVALUE(CMXTA_ERR_NONE);
}


/*
*
*       Fun:  DmUiCpjDatForwardReq 
*
*       Desc:  PDCP SDU Status  Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_cpjcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCpjDatForwardReq 
(
Pst *pst,
SpId spId,
CpjDataFwdReqInfo *pdcpDataFwdReq
)
#else
PUBLIC S16 DmUiCpjDatForwardReq(pst, spId, pdcpDataFwdReq)
Pst *pst;
SpId spId;
CpjDataFwdReqInfo *pdcpDataFwdReq;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCpjDatForwardReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCpjDatForwardReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCpjTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCpjDatForwardReq(): txn not found, msg dropped \n"));
      CMXTA_FREE(pdcpDataFwdReq, sizeof(CpjDataFwdReqInfo));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCpjDatForwardReq(): resource error\n"));
      CMXTA_FREE(pdcpDataFwdReq, sizeof(CpjDataFwdReqInfo));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.cpjInfo.transId = pdcpDataFwdReq->transId;
   rrcMsg->u.cpjInfo.cmInfo.spId = spId;
   rrcMsg->u.cpjInfo.ueInfo.ueId = pdcpDataFwdReq->ueId;
   rrcMsg->u.cpjInfo.ueInfo.cellId = pdcpDataFwdReq->cellId;
   /*(Void) cmMemcpy((U8 *) &(rrcMsg->mBuf), (U8 *)sduStaReqInfo,
                   sizeof(CpjSduStaReqInfo));*/

   /* Free the Count Req Info received from RRC */
   CMXTA_FREE(pdcpDataFwdReq, sizeof(CpjDataFwdReqInfo));

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCpjCb;

   pst->event = EVTCPJSTARTDATAFWDREQ;

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
} /*End of DmUiCpjSduStaReq */


/*
*
*       Fun:  DmUiCpjSduStaReq 
*
*       Desc:  PDCP SDU Status  Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_cpjcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCpjSduStaReq
(
Pst *pst,
SpId spId,
CpjSduStaReqInfo *sduStaReqInfo
)
#else
PUBLIC S16 DmUiCpjSduStaReq (pst, spId, sduStaReqInfo)
Pst *pst;
SpId spId;
CpjSduStaReqInfo *sduStaReqInfo;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCpjSduStaReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCpjSduStaReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCpjTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCpjSduStaReq(): txn not found, msg dropped \n"));
      CMXTA_FREE(sduStaReqInfo, sizeof(CpjSduStaReqInfo));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCpjSduStaReq(): resource error\n"));
      CMXTA_FREE(sduStaReqInfo, sizeof(CpjSduStaReqInfo));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.cpjInfo.transId = sduStaReqInfo->transId;
   rrcMsg->u.cpjInfo.cmInfo.spId = spId;
   rrcMsg->u.cpjInfo.ueInfo.ueId = sduStaReqInfo->ueId;
   rrcMsg->u.cpjInfo.ueInfo.cellId = sduStaReqInfo->cellId;
   /*(Void) cmMemcpy((U8 *) &(rrcMsg->mBuf), (U8 *)sduStaReqInfo,
                   sizeof(CpjSduStaReqInfo));*/

   /* Free the Count Req Info received from RRC */
   CMXTA_FREE(sduStaReqInfo, sizeof(CpjSduStaReqInfo));

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCpjCb;

   pst->event = EVTCPJSDUSTAREQ;

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
} /*End of DmUiCpjSduStaReq */

/*
*
*       Fun:  DmUiCpjReEstReq 
*
*       Desc:  PDCP Re-establishment Req 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*              
*       File:  nhac_cpjcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiCpjReEstReq 
(
Pst *pst,
SpId spId,
CpjReEstReqInfo *reEstReqInfo
)
#else
PUBLIC S16 DmUiCpjReEstReq (pst, spId, reEstReqInfo)
Pst *pst;
SpId spId;
CpjReEstReqInfo *reEstReqInfo;
#endif
{
   CmXtaTCCb   *tcCb = NULLP;
   CmXtaMsgQElm qElm;
   NhAccMsgQElm *rrcMsg = NULLP;

   TRC2(DmUiCpjReEstReq)

   CMXTA_DBG_INFO((_cmxtap, "DmUiCpjReEstReq() spId (%hd)\n", spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/

   if ((tcCb = (CmXtaTCCb*)nhAcCpjTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiCpjReEstReq(): txn not found, msg dropped \n"));
      CMXTA_FREE(reEstReqInfo, sizeof(CpjReEstReqInfo));
      RETVALUE(CMXTA_ERR_NONE);
   }

    /*-- Allocate RRC memory data --*/
   rrcMsg = NULLP;
   CMXTA_ALLOC(&rrcMsg, sizeof (NhAccMsgQElm));
   if (rrcMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiCpjReEstReq(): resource error\n"));
      CMXTA_FREE(reEstReqInfo, sizeof(CpjReEstReqInfo));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   rrcMsg->u.cpjInfo.transId = reEstReqInfo->transId;
   rrcMsg->u.cpjInfo.cmInfo.spId = spId;
   rrcMsg->u.cpjInfo.ueInfo.ueId = reEstReqInfo->pdcpId.ueId;
   rrcMsg->u.cpjInfo.ueInfo.cellId = reEstReqInfo->pdcpId.cellId;
   /*(Void) cmMemcpy((U8 *) &(rrcMsg->mBuf), (U8 *)reEstReqInfo,
                   sizeof(CpjReEstReqInfo));*/

   /* Free the Count Req Info received from RRC */
   CMXTA_FREE(reEstReqInfo, sizeof(CpjReEstReqInfo));

   qElm.data = (Void *)rrcMsg;
   qElm.msgFreeFun = nhAcUtlCpjCb;

   pst->event = EVTCPJREESTREQ;

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
} /* End of DmUiCpjReEstReq */
#endif /* ifdef DM */

/**********************************************************************
         End of file:     nhac_cpjcb.c@@/main/3 - Fri Jul  1 01:12:57 2011
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---    dm               1. LTE RRC Initial Release.
/main/2      ---    ch               1. RRC Release 2.1.
/main/3      ---    sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/

