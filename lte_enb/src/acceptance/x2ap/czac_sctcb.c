
/********************************************************************20**

     Name:   S1AP Layer 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    czac_sctcb.c

     Sid:      czac_sctcb.c@@/main/2 - Tue Aug 30 18:35:53 2011

     Prg:     sy

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_tpt.h"         /* Transport  header file       */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_dns.h"
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/
#include "sct.h"
#ifdef SB
#include "lsb.h"             /* SCTP */
#endif /* SB */
#include "czt.h"
#include "czac_acc.h"
#include "lcz.h"
#include "cm_xta.h"

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_tpt.x"         /* Transport  header file       */
#include "cm_llist.x"      /* common link list */
#include "cm_dns.x"
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/

#include "sct.x"
#ifdef SB
#include "lsb.x"             /* SCTP */
#endif /* SB */

#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"
#include "lcz.x"
#include "cm_xta.x"
#include "czac_acc.x"
#include "czac_sct.x"

#ifdef DM
/*
*
*       Fun:   Bind request
*
*       Desc:  This function is used for bind Request.
*
*       Ret:   ROK - ok
*
*       Notes: None
*
*       File:  cmXta_sctcb.c
*
*/
#ifdef ANSI
PUBLIC S16 DmUiSctBndReq
(
Pst *pst,                 /* post structure */
SuId suId,                /* Su SAP Id */
SpId spId                 /* Sp SAP Id */
)
#else /* ANSI */
PUBLIC S16 DmUiSctBndReq(pst, suId, spId)
Pst *pst;                 /* post structure */
SuId suId;                /* Su SAP Id */
SpId spId;                /* Sp SAP Id */
#endif /* ANSI */
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   CzAccMsgQElm *czMsg;

   TRC2(DmUiSctBndReq)

   CMXTA_DBG_INFO((_cmxtap,
           "DmUiSctBndReq(pst, suId: %d, spId: %d)\n", suId, spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)czAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctBndReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }
      czMsg = NULLP;
      CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
      if (czMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   czMsg->u.sctInfo.cmInfo.suId = suId;
   czMsg->u.sctInfo.cmInfo.spId = spId;

   pst->event = EVTSCTBNDREQ;
   qElm.msgFreeFun = czAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)czMsg;

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

   RETVALUE(ROK);
} /* end of DmUiSctBndReq */

/*
*
*       Fun:   Opening of endpoint request
*
*       Desc:  This function is used to request the opening of
*              an endpoint at the SCTP layer.
*
*       Ret:   ROK  - ok
*
*       Notes: None
*
*       File:  cmXta_sctcb.c
*
*/

#ifdef SCT_ENDP_MULTI_IPADDR
#ifdef ANSI
PUBLIC S16 DmUiSctEndpOpenReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        suEndpId,         /* Service user Endpoint ID */
SctPort        port,             /* Port number */
SctNetAddrLst *intfNAddrLst      /* Interface IP address list */
)
#else /* ANSI */
PUBLIC S16 DmUiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddrLst)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        suEndpId;         /* Service user Endpoint ID */
SctPort        port;             /* Port number */
SctNetAddrLst *intfNAddrLst;     /* Interface IP address list */
#endif /* ANSI */
#else /* SCT_ENDP_MULTI_IPADDR */
#ifdef ANSI
PUBLIC S16 DmUiSctEndpOpenReq
(
Pst           *pst,              /* Post structure */
SpId           spId,             /* Service provider Id */
UConnId        suEndpId,         /* Service user Endpoint ID */
SctPort        port,             /* Port number */
CmNetAddr     *intfNAddr         /* Interface IP address */
)
#else /* ANSI */
PUBLIC S16 DmUiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddr)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        suEndpId;         /* Service user Endpoint ID */
SctPort        port;             /* Port number */
CmNetAddr     *intfNAddr;        /* Interface IP address */
#endif /* ANSI */
#endif /* SCT_ENDP_MULTI_IPADDR */
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      CzAccMsgQElm *czMsg;

   TRC2(DmUiSctEndpOpenReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctEndpOpenReq(pst, spId: %d, suEndpId: %ld, port: %d )\n",
              spId, suEndpId, port));
#else /* ALIGN_64BIT */
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctEndpOpenReq(pst, spId: %d, suEndpId: %d, port: %d )\n",
              spId, suEndpId, port));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)czAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctEndpOpenReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      czMsg = NULLP;
      CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
      if (czMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   czMsg->u.sctInfo.cmInfo.spId = spId;
   czMsg->u.sctInfo.suEndpId = suEndpId;
   czMsg->u.sctInfo.port = port;

   pst->event = EVTSCTENDPOPENREQ;
   qElm.msgFreeFun = czAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)czMsg;


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

   RETVALUE(ROK);
} /* end of DmUiSctEndpOpenReq */

/*
*
*       Fun:   Endpoint closing request
*
*       Desc:  This function is used to send a request for the closing of 
*              the SCTP endpoint
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cmXta_sctcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiSctEndpCloseReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAPID */
UConnId endpId,           /* endpoint ID */
U8 endpIdType             /* endpoint ID type */
)
#else /* ANSI */
PUBLIC S16 DmUiSctEndpCloseReq(pst, spId, endpId, endpIdType)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAPID */
UConnId endpId;           /* endpoint ID */
U8 endpIdType;            /* endpoint ID type */
#endif /* ANSI */
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   CzAccMsgQElm *czMsg;

   TRC2(DmUiSctEndpCloseReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctEndpCloseReq(pst, spId: %d, endpId: %ld, "
              "endpIdType: %d)\n",
              spId, endpId, endpIdType));
#else /* ALIGN_64BIT */
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctEndpCloseReq(pst, spId: %d, endpId: %d, "
              "endpIdType: %d)\n",
              spId, endpId, endpIdType));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)czAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctEndpCloseReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      czMsg = NULLP;
      CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
      if (czMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   czMsg->u.sctInfo.cmInfo.spId = spId;
   czMsg->u.sctInfo.endpIdType = endpIdType;
   /*-- Store endpId in suEndpId and different in the handler function based
        on endpIdType --*/
   czMsg->u.sctInfo.suEndpId = endpId;

   pst->event = EVTSCTENDPCLOSEREQ;
   qElm.msgFreeFun = czAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)czMsg;


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

   RETVALUE(ROK);
} /* end of DmUiSctEndpCloseReq */

/*
*
*       Fun:   Association establishment request
*
*       Desc:  This function is used to send a request for the closing of 
*              the SCTP endpoint
*
*       Ret:   ROK  - ok
*
*       Notes: None
*
*       File:  cmXta_sctcb.c
*
*/

#ifdef SCT3
#ifdef ANSI
PUBLIC S16 DmUiSctAssocReq
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spEndpId,          /* service provider endpoint ID */
UConnId suAssocId,         /* service userassociation ID */
CmNetAddr *priDstNAddr,    /* primary destination network address */
SctPort dstPort,           /* destination port number */
SctStrmId outStrms,        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst, /* dest. network address list */
SctNetAddrLst *srcNAddrLst, /* src. network address list */
SctTos          tos,
Buffer *vsInfo              /* vendor specific info */
)
#else /* ANSI */
PUBLIC S16 DmUiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr, dstPort,
outStrms, dstNAddrLst, srcNAddrLst, tos, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spEndpId;          /* service provider endpoint ID */
UConnId suAssocId;         /* service userassociation ID */
CmNetAddr *priDstNAddr;    /* primary destination network address */
SctPort dstPort;           /* destination port number */
SctStrmId outStrms;        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst; /* dest. network address list */
SctNetAddrLst *srcNAddrLst; /* src. network address list */
SctTos          tos;
Buffer *vsInfo;             /* vendor specific info */
#endif /* ANSI */
#else /* SCT3 */ 
#ifdef ANSI
PUBLIC S16 DmUiSctAssocReq
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spEndpId,          /* service provider endpoint ID */
UConnId suAssocId,         /* service userassociation ID */
CmNetAddr *priDstNAddr,    /* primary destination network address */
SctPort dstPort,           /* destination port number */
SctStrmId outStrms,        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst, /* dest. network address list */
SctNetAddrLst *srcNAddrLst, /* src. network address list */
Buffer *vsInfo              /* vendor specific info */
)
#else /* ANSI */
PUBLIC S16 DmUiSctAssocReq(pst, spId, spEndpId, suAssocId, priDstNAddr, dstPort,
outStrms, dstNAddrLst, srcNAddrLst, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spEndpId;          /* service provider endpoint ID */
UConnId suAssocId;         /* service userassociation ID */
CmNetAddr *priDstNAddr;    /* primary destination network address */
SctPort dstPort;           /* destination port number */
SctStrmId outStrms;        /* no. of outgoing streams */
SctNetAddrLst *dstNAddrLst; /* dest. network address list */
SctNetAddrLst *srcNAddrLst; /* src. network address list */
Buffer *vsInfo;             /* vendor specific info */
#endif /* ANSI */
#endif /* SCT3 */
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      CzAccMsgQElm *czMsg;


   TRC2(DmUiSctAssocReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctAssocReq(pst, spId: %d, spEndpId: %ld, "
              "suAssocId: %ld, dstPort: %d, outStrms: %d)\n",
              spId, spEndpId, suAssocId, dstPort, outStrms));
#else /* ALIGN_64BIT */
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctAssocReq(pst, spId: %d, spEndpId: %d, "
              "suAssocId: %d, dstPort: %d, outStrms: %d)\n",
              spId, spEndpId, suAssocId, dstPort, outStrms));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)czAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctAssocReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      czMsg = NULLP;
      CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
      if (czMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   czMsg->u.sctInfo.cmInfo.spId = spId;
   czMsg->u.sctInfo.spEndpId = spEndpId;
   czMsg->u.sctInfo.suAssocId = suAssocId;
   czMsg->u.sctInfo.port = dstPort;
   czMsg->u.sctInfo.outStrms = outStrms;

   (Void) cmMemcpy((U8 *) &(czMsg->u.sctInfo.dstNAddrLst),
         (U8 *)dstNAddrLst, sizeof(SctNetAddrLst));
   (Void) cmMemcpy((U8 *) &(czMsg->u.sctInfo.srcNAddrLst),
         (U8 *)srcNAddrLst, sizeof(SctNetAddrLst));

   pst->event = EVTSCTASSOCREQ;
   qElm.msgFreeFun = czAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)czMsg;


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


   RETVALUE(ROK);
} /* end of DmUiSctAssocReq */

/*
*
*       Fun:   Association Establishment response
*
*       Desc:  This function is used by the service user to respond to an 
*              association iniitialization indication by accepting the 
*              association.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cmXta_sctcb.c
*
*/

#ifdef SCT3
#ifdef ANSI
PUBLIC S16 DmUiSctAssocRsp
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spAssocId,         /* service provider association ID */
SctAssocIndParams *assocIndParams, /* association parameters */
SctTos             tos,
SctResult result,          /* result */
Buffer *vsInfo             /* vendor specific info */
)
#else /* ANSI */
PUBLIC S16 DmUiSctAssocRsp(pst, spId, spAssocId, assocIndParams, tos, 
result, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spAssocId;         /* service provider association ID */
SctAssocIndParams *assocIndParams; /* association parameters */
SctTos             tos;
SctResult result;          /* result */
Buffer *vsInfo;            /* vendor specific info */
#endif /* ANSI */
#else /* SCT3 */
#ifdef ANSI
PUBLIC S16 DmUiSctAssocRsp
(
Pst *pst,                  /* post structure */
SpId spId,                 /* service provider SAP ID */
UConnId spAssocId,         /* service provider association ID */
SctAssocIndParams *assocIndParams, /* association parameters */
SctResult result,          /* result */
Buffer *vsInfo             /* vendor specific info */
)
#else /* ANSI */
PUBLIC S16 DmUiSctAssocRsp(pst, spId, spAssocId, assocIndParams,  
result, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spAssocId;         /* service provider association ID */
SctAssocIndParams *assocIndParams; /* association parameters */
SctResult result;          /* result */
Buffer *vsInfo;            /* vendor specific info */
#endif /* ANSI */
#endif /* SCT3 */
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   CzAccMsgQElm *czMsg;


   TRC2(DmUiSctAssocRsp)

#ifdef CMXTA_EXTENSION
   {
      if (assocIndParams->type == SCT_ASSOC_IND_INIT)
      {
         SctInitParams *ip;

         ip = &(assocIndParams->t.initParams);

         CMXTA_DBG_INFO((_cmxtap,
                 "\nDmUiSctAssocRsp(pst, spId: %d, spAssocId: %ld, "
                 "result: %d, assocIndParams->type: %d, "
                 "initParams: iTag: %ld, a_rwnd: %ld, "
                 "outStrms: %d, inStrms: %d, "
                 "iTsn: %ld, cookieLife: %ld, "
                 "peerPort: %d, localPort: %d, "
                 "supAddress: %d)\n",
                 spId, spAssocId, result, assocIndParams->type,
                 ip->iTag, ip->a_rwnd, ip->outStrms, ip->inStrms,
                 ip->iTsn, ip->cookieLife, ip->peerPort,
                 ip->localPort, ip->supAddress));
      }
      else if (assocIndParams->type == SCT_ASSOC_IND_COOKIE)
      {
         /* ICNC : print peerAddrLst contents */

         SctCookieParams *cp;

         cp = &(assocIndParams->t.cookieParams);

         CMXTA_DBG_INFO((_cmxtap,
                 "\nDmUiSctAssocRsp(pst, spId: %d, spAssocId: %ld, "
                 "result: %d, assocIndParams->type: %d, "
                 "cookieParams: spAssocId: %ld, suAssocId: %ld, "
                 "peerPort: %d)\n",
                 spId, spAssocId, result, assocIndParams->type,
                 cp->spAssocId, cp->suAssocId, cp->peerPort));
      }
   }
#endif /* CMXTA_EXTENSION */

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)czAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctAssocRsp(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      czMsg = NULLP;
      CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
      if (czMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   czMsg->u.sctInfo.cmInfo.spId = spId;
   czMsg->u.sctInfo.spAssocId = spAssocId;
   CMXTA_CPY(&czMsg->u.sctInfo.assocParams, assocIndParams, sizeof(SctAssocIndParams));

   pst->event = EVTSCTASSOCRSP;
   qElm.msgFreeFun = czAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)czMsg;


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


   RETVALUE(ROK);
} /* end of DmUiSctAssocRsp */

/*
*
*       Fun:   Association Termination Request
*
*       Desc:  This function is used to request the termination of an 
*              association which is either established or being established.
*
*       Ret:   ROK  - ok
*
*       Notes: None
*
*       File:  cmXta_sctcb.c
*
*/
#ifdef ANSI
PUBLIC S16 DmUiSctTermReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId assocId,          /* association ID */
U8 assocIdType,           /* association ID type */
Bool abrtFlg              /* abort flag */
)
#else /* ANSI */
PUBLIC S16 DmUiSctTermReq(pst, spId, assocId, assocIdType, abrtFlg)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId assocId;          /* association ID */
U8 assocIdType;           /* association ID type */
Bool abrtFlg;             /* abort flag */
#endif /* ANSI */
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      CzAccMsgQElm *czMsg;


   TRC2(DmUiSctTermReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctTermReq(pst, spId: %d, assocId: %ld, "
              "assocIdType: %d, abrtFlg: %d)\n",
              spId, assocId, assocIdType, abrtFlg));
#else /* ALIGN_64BIT */
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctTermReq(pst, spId: %d, assocId: %d, "
              "assocIdType: %d, abrtFlg: %d)\n",
              spId, assocId, assocIdType, abrtFlg));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)czAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctTermReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      czMsg = NULLP;
      CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
      if (czMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   czMsg->u.sctInfo.cmInfo.spId = spId;
   czMsg->u.sctInfo.assocIdType = assocIdType;

   if(SCT_ASSOCID_SU == czMsg->u.sctInfo.assocIdType)
      czMsg->u.sctInfo.suAssocId = assocId;
   else
      czMsg->u.sctInfo.spAssocId = assocId;

   pst->event = EVTSCTTERMREQ;
   qElm.msgFreeFun = czAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)czMsg;


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


   RETVALUE(ROK);
} /* end of DmUiSctTermReq */

/*
*
*       Fun:   Set Primary Destination Address request
*
*       Desc:  This function is used to set a particular
*              primary destination address.
*
*       Ret:   ROK  - ok
*
*       Notes: None
*
*       File:  cmXta_sctcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiSctSetPriReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId spAssocId,        /* service provider association ID */
CmNetAddr *dstNAddr       /* dest. network address */
)
#else /* ANSI */
PUBLIC S16 DmUiSctSetPriReq(pst, spId, spAssocId, dstNAddr)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId spAssocId;        /* service provider association ID */
CmNetAddr *dstNAddr;      /* dest. network address */
#endif /* ANSI */
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      CzAccMsgQElm *czMsg;


   TRC2(DmUiSctSetPriReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctSetPriReq(pst, spId: %d, spAssocId: %ld)\n",
              spId, spAssocId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctSetPriReq(pst, spId: %d, spAssocId: %d)\n",
              spId, spAssocId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)czAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctSetPriReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      czMsg = NULLP;
      CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
      if (czMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   czMsg->u.sctInfo.cmInfo.spId = spId;
   czMsg->u.sctInfo.spAssocId = spAssocId;

   pst->event = EVTSCTSETPRIREQ;
   qElm.msgFreeFun = czAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)czMsg;


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


   RETVALUE(ROK);
} /* end of DmUiSctSetPriReq */


/*
*
*       Fun:   Set Primary Destination Address request
*
*       Desc:  This function is used to set a particular
*              primary destination address.
*
*       Ret:   ROK  - ok
*
*       Notes: None
*
*       File:  cmXta_sctcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiSctHBeatReq
(
Pst            *pst,
SpId            spId,
UConnId         spAssocId,
CmNetAddr      *dstNAddr,
U16             intervalTime,
SctStatus       status
)
#else /* ANSI */
PUBLIC S16 DmUiSctHBeatReq(pst, spId, spAssocId, dstNAddr, intervalTime, status)
Pst            *pst;
SpId            spId;
UConnId         spAssocId;
CmNetAddr      *dstNAddr;
U16             intervalTime;
SctStatus       status;
#endif /* ANSI */
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      CzAccMsgQElm *czMsg;

   TRC2(DmUiSctHBeatReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctHBeatReq(pst, spId: %d, spAssocId: %ld)\n",
              spId, spAssocId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctHBeatReq(pst, spId: %d, spAssocId: %d)\n",
              spId, spAssocId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)czAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctHBeatReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      czMsg = NULLP;
      CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
      if (czMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   czMsg->u.sctInfo.cmInfo.spId = spId;
   czMsg->u.sctInfo.spAssocId = spAssocId;

   pst->event = EVTSCTHBEATREQ;
   qElm.msgFreeFun = czAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)czMsg;

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


   RETVALUE(ROK);
} /* end of DmUiSctHBeatReq --*/

/*
*
*       Fun:   Data request
*
*       Desc:  This function is used to request the service provider to send a
*              user datagram to the destination.
*
*       Ret:   ROK    - ok
*
*       Notes: None
*
*       File:  cmXta_sctcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiSctDatReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId spAssocId,        /* service provider association ID */
CmNetAddr *dstNAddr,      /* dest. network address */
SctStrmId strmId,         /* stream ID */
Bool unorderFlg,          /* unordered delivery flag */
Bool nobundleFlg,         /* nobundleFlg */
U16 lifetime,             /* datagram lifetime */
U32 protId,               /* protocol ID */
Buffer *mBuf              /* message buffer */
)
#else /* ANSI */
PUBLIC S16 DmUiSctDatReq(pst, spId, spAssocId, dstNAddr, strmId, unorderFlg, 
                         nobundleFlg, lifetime, protId, mBuf)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId spAssocId;        /* service provider association ID */
CmNetAddr *dstNAddr;      /* dest. network address */
SctStrmId strmId;         /* stream ID */
Bool unorderFlg;          /* unordered delivery flag */
Bool nobundleFlg;         /* nobundleFlg */
U16 lifetime;             /* datagram lifetime */
U32 protId;               /* protocol ID */
Buffer *mBuf;             /* message buffer */
#endif /* ANSI */
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      CzAccMsgQElm *czMsg;

   TRC2(DmUiSctDatReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctDatReq(pst, spId: %d, spAssocId: %ld, "
              "strmId: %d, unorderFlg: %d, nobundleFlg: %d, "
              "lifetime: %d, protId: %ld)\n",
              spId, spAssocId, strmId, unorderFlg, nobundleFlg,
              lifetime, protId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctDatReq(pst, spId: %d, spAssocId: %d, "
              "strmId: %d, unorderFlg: %d, nobundleFlg: %d, "
              "lifetime: %d, protId: %d)\n",
              spId, spAssocId, strmId, unorderFlg, nobundleFlg,
              lifetime, protId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)czAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctDatReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

   czMsg = NULLP;
   CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
   if (czMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   czMsg->u.sctInfo.cmInfo.spId = spId;
   czMsg->u.sctInfo.strmId = strmId;
   czMsg->u.sctInfo.mBuf = mBuf;

   pst->event = EVTSCTDATREQ;
   qElm.msgFreeFun = czAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)czMsg;

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


   RETVALUE(ROK);
} /* end of DmUiSctDatReq */

/*
*
*       Fun:   Status request
*
*       Desc:  This function is used to retrieve 
*              unsent/unacknowledged/undelivered datagrams from the service 
*              provider and to get statistical information from the service 
*              provider.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  cmXta_sctcb.c
*
*/

#ifdef ANSI
PUBLIC S16 DmUiSctStaReq
(
Pst *pst,                 /* post structure */
SpId spId,                /* service provider SAP ID */
UConnId spAssocId,        /* service provider association ID */
CmNetAddr *dstNAddr,      /* dest. network address */
U8 staType                /* status type */
)
#else /* ANSI */
PUBLIC S16 DmUiSctStaReq(pst, spId, spAssocId, dstNAddr, staType)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId spAssocId;        /* service provider association ID */
CmNetAddr *dstNAddr;      /* dest. network address */
U8 staType;               /* status type */
#endif /* ANSI */
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      CzAccMsgQElm *czMsg;

   TRC2(DmUiSctStaReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctStaReq(pst, spId: %d, spAssocId: %ld, "
              "staType: %d)\n",
              spId, spAssocId, staType));
#else /* ALIGN_64BIT */
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctStaReq(pst, spId: %d, spAssocId: %d, "
              "staType: %d)\n",
              spId, spAssocId, staType));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)czAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctStaReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      czMsg = NULLP;
      CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
      if (czMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
                                                               

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   czMsg->u.sctInfo.cmInfo.spId = spId;
   czMsg->u.sctInfo.spAssocId = spAssocId;

   pst->event = EVTSCTSTAREQ;
   qElm.msgFreeFun = czAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)czMsg;


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


   RETVALUE(ROK);
} /* end of DmUiSctStaReq */

#endif /* ifdef DM */

/********************************************************************30**

         End of file:     czac_sctcb.c@@/main/2 - Tue Aug 30 18:35:53 2011

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
/main/1      ---      sy                1. LTE-X2AP Initial Release.
/main/2      ---      pt                1. LTE-X2AP 3.1 release.
*********************************************************************91*/
