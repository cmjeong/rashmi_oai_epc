
/********************************************************************20**

     Name:   S1AP Layer 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    szac_sctcb.c

     Sid:      szac_sctcb.c@@/main/4 - Mon Jan 10 22:15:56 2011

     Prg:     ms

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
#include "sz.h"
/* sz006.301: Removed un-necessary include files  */
#include "cm_dns.h"
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/
#include "sct.h"
/* sz007.301: Gaurded SCTP includes under SB flag */
#ifdef SB
#include "sb_mtu.h"         /* SCTP */
#include "lsb.h"             /* SCTP */
#include "sb.h"             /* SCTP */
#endif /* SB */
#include "szt.h"
#include "szt_asn.h"
#include "szac_acc.h"
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

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
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"


#include "sct.x"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "sht.x"           /* System Agent */
#endif
#ifdef SB
#include "sb_mtu.x"         /* SCTP */
#include "lsb.x"             /* SCTP */
#include "sb.x"             /* SCTP */
#endif

#include"szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL9;
#ifndef SZ_ENC_DEC
#endif /* SZ_ENC_DEC */
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#endif /* SZ_FTHA */
#include "lsz.x"
#include "cm_xta.h"
#include "cm_xta.x"
#include "szac_acc.x"
#include "szac_sct.x"

#ifdef __cplusplus
extern "C" 
{
#endif

EXTERN S16 szAcUtlSztGetErrCause ARGS((SztS1AP_PDU *pdu, U8 *causeType, U32 *causeVal));
EXTERN S16 szUtilsGetMsgIdx ARGS((U8 *evnt,S1apPdu *pdu));
EXTERN S16 szDecode ARGS((Mem *mem, S1apPdu **s1apPdu, Buffer **mBuf));


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
#else
PUBLIC S16 DmUiSctBndReq(pst, suId, spId)
Pst *pst;                 /* post structure */
SuId suId;                /* Su SAP Id */
SpId spId;                /* Sp SAP Id */
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      SzAccMsgQElm *szMsg;

   TRC2(DmUiSctBndReq)

   CMXTA_DBG_INFO((_cmxtap,
           "DmUiSctBndReq(pst, suId: %d, spId: %d)\n", suId, spId));

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)szAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctBndReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }
      szMsg = NULLP;
      CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
      if (szMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   szMsg->u.sctInfo.cmInfo.suId = suId;
   szMsg->u.sctInfo.cmInfo.spId = spId;

   pst->event = EVTSCTBNDREQ;
   qElm.msgFreeFun = szAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)szMsg;

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
#else
PUBLIC S16 DmUiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddrLst)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        suEndpId;         /* Service user Endpoint ID */
SctPort        port;             /* Port number */
SctNetAddrLst *intfNAddrLst;     /* Interface IP address list */
#endif
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
#else
PUBLIC S16 DmUiSctEndpOpenReq(pst, spId, suEndpId, port, intfNAddr)
Pst           *pst;              /* Post structure */
SpId           spId;             /* Service provider Id */
UConnId        suEndpId;         /* Service user Endpoint ID */
SctPort        port;             /* Port number */
CmNetAddr     *intfNAddr;        /* Interface IP address */
#endif
#endif /* SCT_ENDP_MULTI_IPADDR */
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      SzAccMsgQElm *szMsg;

   TRC2(DmUiSctEndpOpenReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctEndpOpenReq(pst, spId: %d, suEndpId: %ld, port: %d )\n",
              spId, suEndpId, port));
#else
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctEndpOpenReq(pst, spId: %d, suEndpId: %d, port: %d )\n",
              spId, suEndpId, port));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)szAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctEndpOpenReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      szMsg = NULLP;
      CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
      if (szMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   szMsg->u.sctInfo.cmInfo.spId = spId;
   szMsg->u.sctInfo.suEndpId = suEndpId;
   szMsg->u.sctInfo.port = port;

   pst->event = EVTSCTENDPOPENREQ;
   qElm.msgFreeFun = szAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)szMsg;


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
#else
PUBLIC S16 DmUiSctEndpCloseReq(pst, spId, endpId, endpIdType)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAPID */
UConnId endpId;           /* endpoint ID */
U8 endpIdType;            /* endpoint ID type */
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      SzAccMsgQElm *szMsg;

   TRC2(DmUiSctEndpCloseReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctEndpCloseReq(pst, spId: %d, endpId: %ld, "
              "endpIdType: %d)\n",
              spId, endpId, endpIdType));
#else
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctEndpCloseReq(pst, spId: %d, endpId: %d, "
              "endpIdType: %d)\n",
              spId, endpId, endpIdType));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)szAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctEndpCloseReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      szMsg = NULLP;
      CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
      if (szMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   szMsg->u.sctInfo.cmInfo.spId = spId;
   szMsg->u.sctInfo.endpIdType = endpIdType;
   /*-- Store endpId in suEndpId and different in the handler function based
        on endpIdType --*/
   szMsg->u.sctInfo.suEndpId = endpId;

   pst->event = EVTSCTENDPCLOSEREQ;
   qElm.msgFreeFun = szAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)szMsg;


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
#else
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
#else
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
#else
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
Buffer *vsInfo;              /* vendor specific info */
#endif /* ANSI */
#endif /* SCT3 */

{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      SzAccMsgQElm *szMsg;


   TRC2(DmUiSctAssocReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctAssocReq(pst, spId: %d, spEndpId: %ld, "
              "suAssocId: %ld, dstPort: %d, outStrms: %d)\n",
              spId, spEndpId, suAssocId, dstPort, outStrms));
#else
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctAssocReq(pst, spId: %d, spEndpId: %d, "
              "suAssocId: %d, dstPort: %d, outStrms: %d)\n",
              spId, spEndpId, suAssocId, dstPort, outStrms));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)szAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctAssocReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      szMsg = NULLP;
      CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
      if (szMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   szMsg->u.sctInfo.cmInfo.spId = spId;
   szMsg->u.sctInfo.spEndpId = spEndpId;
   szMsg->u.sctInfo.suAssocId = suAssocId;
   szMsg->u.sctInfo.port = dstPort;
   szMsg->u.sctInfo.outStrms = outStrms;

   (Void) cmMemcpy((U8 *) &(szMsg->u.sctInfo.dstNAddrLst),
         (U8 *)dstNAddrLst, sizeof(SctNetAddrLst));
   (Void) cmMemcpy((U8 *) &(szMsg->u.sctInfo.srcNAddrLst),
         (U8 *)srcNAddrLst, sizeof(SctNetAddrLst));

   pst->event = EVTSCTASSOCREQ;
   qElm.msgFreeFun = szAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)szMsg;


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
#else
PUBLIC S16 DmUiSctAssocRsp(pst, spId, spAssocId, assocIndParams,tos,result, vsInfo)
Pst *pst;                  /* post structure */
SpId spId;                 /* service provider SAP ID */
UConnId spAssocId;         /* service provider association ID */
SctAssocIndParams *assocIndParams; /* association parameters */
SctTos             tos;
SctResult result;          /* result */
Buffer *vsInfo;            /* vendor specific info */
#endif /* ANSI */
#else
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
#else
PUBLIC S16 DmUiSctAssocRsp(pst, spId, spAssocId, assocIndParams,result, vsInfo)
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
      SzAccMsgQElm *szMsg;


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
#endif

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)szAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctAssocRsp(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      szMsg = NULLP;
      CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
      if (szMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   szMsg->u.sctInfo.cmInfo.spId = spId;
   szMsg->u.sctInfo.spAssocId = spAssocId;
   CMXTA_CPY(&szMsg->u.sctInfo.assocParams, assocIndParams, sizeof(SctAssocIndParams));

   pst->event = EVTSCTASSOCRSP;
   qElm.msgFreeFun = szAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)szMsg;


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
#else
PUBLIC S16 DmUiSctTermReq(pst, spId, assocId, assocIdType, abrtFlg)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId assocId;          /* association ID */
U8 assocIdType;           /* association ID type */
Bool abrtFlg;             /* abort flag */
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      SzAccMsgQElm *szMsg;


   TRC2(DmUiSctTermReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctTermReq(pst, spId: %d, assocId: %ld, "
              "assocIdType: %d, abrtFlg: %d)\n",
              spId, assocId, assocIdType, abrtFlg));
#else
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctTermReq(pst, spId: %d, assocId: %d, "
              "assocIdType: %d, abrtFlg: %d)\n",
              spId, assocId, assocIdType, abrtFlg));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)szAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctTermReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      szMsg = NULLP;
      CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
      if (szMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   szMsg->u.sctInfo.cmInfo.spId = spId;
   szMsg->u.sctInfo.assocIdType = assocIdType;

   if(SCT_ASSOCID_SU == szMsg->u.sctInfo.assocIdType)
      szMsg->u.sctInfo.suAssocId = assocId;
   else
      szMsg->u.sctInfo.spAssocId = assocId;

   pst->event = EVTSCTTERMREQ;
   qElm.msgFreeFun = szAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)szMsg;


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
#else
PUBLIC S16 DmUiSctSetPriReq(pst, spId, spAssocId, dstNAddr)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId spAssocId;        /* service provider association ID */
CmNetAddr *dstNAddr;      /* dest. network address */
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      SzAccMsgQElm *szMsg;


   TRC2(DmUiSctSetPriReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctSetPriReq(pst, spId: %d, spAssocId: %ld)\n",
              spId, spAssocId));
#else
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctSetPriReq(pst, spId: %d, spAssocId: %d)\n",
              spId, spAssocId));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)szAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctSetPriReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      szMsg = NULLP;
      CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
      if (szMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   szMsg->u.sctInfo.cmInfo.spId = spId;
   szMsg->u.sctInfo.spAssocId = spAssocId;

   pst->event = EVTSCTSETPRIREQ;
   qElm.msgFreeFun = szAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)szMsg;


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
#else
PUBLIC S16 DmUiSctHBeatReq(pst, spId, spAssocId, dstNAddr, intervalTime, status)
Pst            *pst;
SpId            spId;
UConnId         spAssocId;
CmNetAddr      *dstNAddr;
U16             intervalTime;
SctStatus       status;
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      SzAccMsgQElm *szMsg;

   TRC2(DmUiSctHBeatReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctHBeatReq(pst, spId: %d, spAssocId: %ld)\n",
              spId, spAssocId));
#else
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctHBeatReq(pst, spId: %d, spAssocId: %d)\n",
              spId, spAssocId));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)szAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctHBeatReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      szMsg = NULLP;
      CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
      if (szMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   szMsg->u.sctInfo.cmInfo.spId = spId;
   szMsg->u.sctInfo.spAssocId = spAssocId;

   pst->event = EVTSCTHBEATREQ;
   qElm.msgFreeFun = szAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)szMsg;

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
#else
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
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
   SzAccMsgQElm *szMsg;

   Mem      tmpMem;
   S1apPdu  *tmpPdu;
   U8        evnt;
   U8  causeType = 0;
   U32 causeVal  = 0;

   TRC2(DmUiSctDatReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctDatReq(pst, spId: %d, spAssocId: %ld, "
              "strmId: %d, unorderFlg: %d, nobundleFlg: %d, "
              "lifetime: %d, protId: %ld)\n",
              spId, spAssocId, strmId, unorderFlg, nobundleFlg,
              lifetime, protId));
#else
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctDatReq(pst, spId: %d, spAssocId: %d, "
              "strmId: %d, unorderFlg: %d, nobundleFlg: %d, "
              "lifetime: %d, protId: %d)\n",
              spId, spAssocId, strmId, unorderFlg, nobundleFlg,
              lifetime, protId));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)szAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctDatReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

   szMsg = NULLP;
   CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
   if (szMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   szMsg->u.sctInfo.cmInfo.spId = spId;
   szMsg->u.sctInfo.strmId = strmId;
   szMsg->u.sctInfo.mBuf = mBuf;

   tmpMem.region = 0;
   tmpMem.pool = 0;

   szAcDecode(&tmpMem, &tmpPdu, &mBuf);

   szUtilsGetMsgIdx (&evnt, tmpPdu);
   szMsg->u.sctInfo.type.val = evnt;

         
   if(evnt == SZT_MSG_ID_ERR_IND)
   {
       if(szAcUtlSztGetErrCause(&(tmpPdu->pdu), &causeType, &causeVal) == ROK)
       {
          szMsg->u.sctInfo.u.errInd.type   = causeType;
          szMsg->u.sctInfo.u.errInd.value  = causeVal;
       }
   }

/*   CMXTA_FREE(tmpPdu, sizeof(S1apPdu)); */
   SZ_FREE_SDU(tmpPdu);

   pst->event = EVTSCTDATREQ;
   qElm.msgFreeFun = szAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)szMsg;

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
#else
PUBLIC S16 DmUiSctStaReq(pst, spId, spAssocId, dstNAddr, staType)
Pst *pst;                 /* post structure */
SpId spId;                /* service provider SAP ID */
UConnId spAssocId;        /* service provider association ID */
CmNetAddr *dstNAddr;      /* dest. network address */
U8 staType;               /* status type */
#endif
{
   CmXtaTCCb   *tcCb;
   CmXtaMsgQElm qElm;
      SzAccMsgQElm *szMsg;

   TRC2(DmUiSctStaReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctStaReq(pst, spId: %d, spAssocId: %ld, "
              "staType: %d)\n",
              spId, spAssocId, staType));
#else
   CMXTA_DBG_INFO((_cmxtap,
              "DmUiSctStaReq(pst, spId: %d, spAssocId: %d, "
              "staType: %d)\n",
              spId, spAssocId, staType));
#endif
   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Find the associated test case using the txnId --*/
   if ((tcCb = (CmXtaTCCb *)szAcSctTstCbFind()) == NULLP)
   {
      /*-- No associated test case found, spurious message, drop it --*/

      CMXTA_DBG_INFO((_cmxtap, "DmUiSctStaReq(): txn not found, msg dropped \n"));
      RETVALUE(ROK);
   }

      szMsg = NULLP;
      CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
      if (szMsg == NULLP)
      {  
            CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
            RETVALUE(CMXTA_ERR_RSRC);
   }
                                                               

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   szMsg->u.sctInfo.cmInfo.spId = spId;
   szMsg->u.sctInfo.spAssocId = spAssocId;

   pst->event = EVTSCTSTAREQ;
   qElm.msgFreeFun = szAcUtlSctCb;
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   qElm.data = (Void *)szMsg;


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

#ifdef __cplusplus
}
#endif



/********************************************************************30**

         End of file:     szac_sctcb.c@@/main/4 - Mon Jan 10 22:15:56 2011

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
/main/4      ---      vvashishth  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz007.301   ve    1. Gaurded SCTP includes under SB flag
/main/4   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
