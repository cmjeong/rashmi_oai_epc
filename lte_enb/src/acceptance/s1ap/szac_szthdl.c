
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    szac_lszhdl.c

     Sid:      szac_szthdl.c@@/main/4 - Mon Jan 10 22:16:01 2011

     Prg:     mn
*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timers defines */
#include "cm_hash.h"       /* common hash list defines */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* common DNS libraru defines */
#include "cm_xta.h" 
#include "cm_pasn.h"
#ifdef SZ_FTHA
#include "cm_ftha.h"        /* common ftha library          */
#include "cm_psfft.h"      /* common psf functions */
#include "cm_psf.h"         /* common psf library           */
#endif /* SZ_FTHA */

/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent*/
#endif /* SZ_FTHA */
#include "lsz.h"           /* defines and macros for SZ */
#include "sct.h"           /* defines and macros for SZ */
#include "szt.h"           /* defines and macros for SZ */
/* sz006.301: Removed un-necessary include files  */
#include "szac_asn.h"
#include "sz.h"            /* defines and macros for SZ */
#include "sz_err.h"        /* SZ error defines */
#include "szac_acc.h"      /* defines for SZ acceptance tests */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_inet.x"       /* common INET */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_tpt.x"        /* common transport types */
#include "cm_dns.x"         /* common DNS libraru defines */
#include "cm_xta.x" 
#include "cm_pasn.x"
#ifdef SZ_FTHA
#include "cm_ftha.x"       /* common ftha library          */
#include "cm_psfft.x"      /* common psf fast trans library*/
#include "cm_psf.x"        /* common pdf library           */
#endif /* SZ_FTHA */

#ifdef SB
#include "lsb.h"            /* SCTP layer managment defines */
#endif /*SB*/
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/

/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent*/
#endif /* SZ_FTHA */
#include "szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL11;
#ifndef SZ_ENC_DEC
#include "szac_asn_pk.x"
#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */
/*#include "szt.h"        */   /* defines and macros for SZ */
#include "sct.x"           /* typedefs for STCP */
#include "lsz.x"           /* layer management typedefs for SZCP */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* typedefs for SZCP */
#ifdef SB
#include "lsb.x"           /* SCTP layer managment structures */
#endif /*SB*/
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#include "sz.x"            /* typedefs for SZCP */
#include "szac_acc.x"      /* typedefs for SZCP acceptance tests */
#include "szac_szt.x"

PUBLIC SzAcSztPduInfo szacPduInfo[SZAC_MAX_PROCS][SZAC_LSZ_MAX_CONN];
EXTERN S1apPdu *rstAckPdu;

/*
*
*       Fun:   szAcHdlSztBndReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlSztBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSztBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   SuId          suId = 0;             /* service user SAP identifier */
   SpId          spId = 0;             /* service user SAP identifier */
   
   TRC2(szAcHdlSztBndReq);
   
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztBndReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztBndReq(), tcId (%ld)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
   
   pst.event = EVTSZTBNDREQ;
   
   /* sz003.301: Updted for PSF-S1AP 3.1 release. Set the route as PRTO so
    * that it will be translated by MR */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "route",  &(pst.route));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dstProcId",  &(pst.dstProcId));
#endif /* SZ_FTHA */

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
 
   /* Send the request to the GCP --*/
   UzLiSztBndReq(&pst, suId, spId);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- szAcHdlSztBndReq --*/

/*
*
*       Fun:   szAcHdlSztBndCfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  mgac_szthdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlSztBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSztBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg;
   SzAccMsgQElm  *szMsg;
   Pst           pst;
   S16           ret = ROK;
   SpId          suId;
   Status        status = CM_BND_OK;
 
   TRC2(szAcHdlSztBndCfm);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztBndCfm(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztBndCfm(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSztBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   szMsg = (SzAccMsgQElm *)msg->data;

   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);

   pst.event = EVTSZTBNDCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   suId = 0; /*-- Note suId = spId --*/

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, szMsg->u.sztInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "status",  &(status));
 
   if (status != szMsg->u.sztInfo.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, szMsg->u.sztInfo.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- szAcHdlSztBndCfm --*/
 
 
 
/*
*
*       Fun:   szAcHdlSztUbndReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  mgac_szthdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlSztUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId;
   Reason         reason;
   TRC2(szAcHdlSztUbndReq);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztUbndReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztUbndReq(), tcId (%ld)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);

   
   pst.event = EVTSZTUBNDREQ;
 
   /* sz003.301: Updted for PSF-S1AP 3.1 release. Set the route as PRTO so
    * that it will be translated by MR */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "route",  &(pst.route));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dstProcId",  &(pst.dstProcId));
#endif /* SZ_FTHA */

   spId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
 
   reason = 0; /*-- Reason is unused --*/
 
   /* Send the request to the GCP --*/
   UzLiSztUbndReq(&pst, spId, reason);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- szAcHdlSztUbndReq --*/

/*
*
*       Fun:   szAcHdlSztAuditReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztAuditReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztAuditReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   SztAudEvnt      audit;
   U8            testType=0;
   
   TRC2(szAcHdlSztAuditReq);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztAuditReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztAuditReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);

   pst.event = EVTSZTAUDREQ;

   CMXTA_ZERO(&audit, sizeof(SztAudEvnt));

   /* Issue a Audit request */
   audit.type = SZT_AUD_CONN;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "auditType", &(audit.type));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "testType", &(testType));
 
   if (testType != 1)
   {
      switch (audit.type)
      {
         case SZT_AUD_CONN:
         {
            UConnId connId = 1;
            audit.u.audConn.nmbConn = 1;
            audit.u.audConn.connIdType = SZT_CONN_TYPE_SP;
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbConn", &(audit.u.audConn.nmbConn));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "connIdType", &(audit.u.audConn.connIdType));
            if (audit.u.audConn.connIdType == SZT_CONN_TYPE_SU)
            {
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "usrConnId", &(connId));
            }
            else
            {
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "spConnId", &(connId));
            }
   
            audit.u.audConn.connSt[0].connId = connId;
   
         }
         break;

         case SZT_AUD_PEER:
         case SZT_AUD_FLC:
         {
            audit.u.audPeer.peerId = 0;
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId",
                                 &(audit.u.audPeer.peerId));
         }
         break;

      }

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
 
      UzLiSztAudReq(&pst, spId, &audit);
   }
   else
   {
      pst.selector = 2;
      UzLiSztAudReq(&pst, spId, NULL);
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* szAcHdlSztAuditReq */

/*
*
*       Fun:   szAcHdlSztAuditCfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztAuditCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztAuditCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   CmXtaMsgQElm  *msg; 
   SzAccMsgQElm  *szMsg;
   Pst           pst;
   SpId          suId;
 
   TRC2(szAcHdlSztAuditCfm);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztAuditCfm(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztAuditCfm(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSztAuditCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   szMsg = (SzAccMsgQElm *)msg->data;
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);
 
   pst.event = EVTSZTAUDCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSztAuditCfm() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, szMsg->u.sztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   if ((szMsg->u.sztInfo.type.pres == PRSNT_NODEF) && 
                         (szMsg->u.sztInfo.type.val == SZAC_AUDIT)) 
   {
      switch (szMsg->u.sztInfo.u.audit.type)
      {
         case SZT_AUD_CONN:
         {
            U8 state = SZT_CON_ST_ESTBLD;
            UConnId  connId;
            U8 nmbConn = 1;

            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "nmbConn",  &nmbConn);
            if (nmbConn != szMsg->u.sztInfo.u.audit.u.conn.nmbConn)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : nmbConn mismatch: exp (%d) rcvd (%d) \n",
                               nmbConn, szMsg->u.sztInfo.u.audit.u.conn.nmbConn), 2);
          
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }

            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "spConnId",  &connId);
            if (connId != szMsg->u.sztInfo.u.audit.u.conn.connId[0])
            {
#ifdef ALIGN_64BIT
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : spConnId mismatch: exp (%d) rcvd (%d) \n",
                        connId, szMsg->u.sztInfo.u.audit.u.conn.connId[0]), 2);
#else  
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : spConnId mismatch: exp (%ld) rcvd (%ld) \n",
                        connId, szMsg->u.sztInfo.u.audit.u.conn.connId[0]), 2);
#endif 
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }

            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "connState",  &state);
            if (state != szMsg->u.sztInfo.u.audit.u.conn.connSt[0])
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : state mismatch: exp (%d) rcvd (%d) \n",
                               state, szMsg->u.sztInfo.u.audit.u.conn.connSt[0]), 2);
          
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;

         case SZT_AUD_PEER:
         {
            U32  peerId = 0;
            U8   peerState = 0;
            U16  status = 0; 
            U16  cause =  0;
     
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status", &status);
            if ((status != szMsg->u.sztInfo.u.audit.status))
            {
#ifdef ALIGN_64BIT
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : status mismatch: exp (%d) rcvd (%d) \n",
                               status, szMsg->u.sztInfo.u.audit.status), 2);
#else
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : status mismatch: exp (%d) rcvd (%d) \n",
                               status, szMsg->u.sztInfo.u.audit.status), 2);
#endif
          
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }

            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "cause", &cause);
            if ((cause != szMsg->u.sztInfo.u.audit.cause))
            {
#ifdef ALIGN_64BIT
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : cause mismatch: exp (%d) rcvd (%d) \n",
                               cause, szMsg->u.sztInfo.u.audit.cause), 2);
#else
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : cause mismatch: exp (%d) rcvd (%d) \n",
                               cause, szMsg->u.sztInfo.u.audit.cause), 2);
#endif
          
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }

            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);
            if ((peerId != szMsg->u.sztInfo.u.audit.u.peer.peerId))
            {
#ifdef ALIGN_64BIT
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                               peerId, szMsg->u.sztInfo.u.audit.u.peer.peerId), 2);
#else
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                               peerId, szMsg->u.sztInfo.u.audit.u.peer.peerId), 2);
#endif
          
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }

            if (status == SZT_PRIM_OK)
            {
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "peerState",  &peerState);
               if (peerState != szMsg->u.sztInfo.u.audit.u.peer.peerState)
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerState mismatch: exp (%d) rcvd (%d) \n",
                                  peerState, szMsg->u.sztInfo.u.audit.u.peer.peerState), 2);
          
                  cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
                  RETVALUE(CMXTA_ERR_INT);
               }
            }
         }
         break;
      }
   }
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
} /* szAcHdlSztAuditCfm */


/*
*
*       Fun:   szAcHdlSztFlcInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztFlcInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztFlcInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   S16            ret = ROK;
   CmXtaMsgQElm  *msg; 
   SzAccMsgQElm  *szMsg;
   Pst           pst;
   SpId          suId;
 
   TRC2(szAcHdlSztFlcInd);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztFlcInd(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztFlcInd(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSztFlcInd(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   szMsg = (SzAccMsgQElm *)msg->data;
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);
 
   pst.event = EVTSZTFLCIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcHdlSztFlcInd() : pst mismatch\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, szMsg->u.sztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   if ((szMsg->u.sztInfo.type.pres == PRSNT_NODEF) && 
                         (szMsg->u.sztInfo.type.val == SZAC_FLCIND)) 
   {
      U16   flcStatus = 1;
      U32   peerId = 0;
     
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);
      if (peerId != szMsg->u.sztInfo.peerId.val)
      {
#ifdef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, szMsg->u.sztInfo.peerId.val), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, szMsg->u.sztInfo.peerId.val), 2);
#endif
    
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "flcStatus",  &flcStatus);
      if (flcStatus != szMsg->u.sztInfo.status)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : flcStatus mismatch: exp (%d) rcvd (%d) \n",
                         flcStatus, szMsg->u.sztInfo.status), 2);
    
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
} /* szAcHdlSztFlcInd */

/*
*
*       Fun:   szAcHdlSztStaInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztStaInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztStaInd(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztStaInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);
 
   pst.event = EVTSZTSTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlSztStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, szMsg->u.sztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (szMsg->u.sztInfo.peerId.pres == PRSNT_NODEF)
   {
      U32  peerId = 0;
     
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

      if(peerId != szMsg->u.sztInfo.peerId.val)
      {
#ifdef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, szMsg->u.sztInfo.peerId.val), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, szMsg->u.sztInfo.peerId.val), 2);
#endif
    
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   if ((szMsg->u.sztInfo.type.pres == PRSNT_NODEF) && 
                         (szMsg->u.sztInfo.type.val == SZAC_STAIND)) 
   {
      U8 staType = SZT_STA_TYPE_FLC;

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "staType",  &staType);
      if (staType != szMsg->u.sztInfo.u.staInd.type)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : staType mismatch: exp (%d) rcvd (%d) \n",
                         staType, szMsg->u.sztInfo.u.staInd.type), 2);
    
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }

      switch (szMsg->u.sztInfo.u.staInd.type)
      {
         case SZT_STA_TYPE_FLC:
         {
            U8 reason =  SZT_REASON_FLC_START;
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "reason",  &reason);
            if (reason != szMsg->u.sztInfo.u.staInd.reason)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : reason mismatch: exp (%d) rcvd (%d) \n",
                               staType, szMsg->u.sztInfo.u.staInd.type), 2);
          
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;

         case SZT_STA_TYPE_ASSOC:
         {
            U8 reason =  SZT_REASON_RCVD_TERMIND;
            U8 status =  SZT_STATUS_ASSOC_DOWN;

            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "reason",  &reason);
            if (reason != szMsg->u.sztInfo.u.staInd.reason)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : reason mismatch: exp (%d) rcvd (%d) \n",
                               reason, szMsg->u.sztInfo.u.staInd.reason), 2);
          
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }

            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "status",  &status);
            if (status != szMsg->u.sztInfo.u.staInd.status)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : status mismatch: exp (%d) rcvd (%d) \n",
                               status, szMsg->u.sztInfo.u.staInd.status), 2);
          
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;
      }
   }
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlSztStaInd */


/*
*
*       Fun:   szAcHdlSztErrInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztErrInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztErrInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   U8       causeType = SZT_CAUSE_INV_UNKNOWN;
   U8       causeValue = 0;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztErrInd(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztErrInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);

 
 
   pst.event = EVTSZTERRIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlSztErrInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, szMsg->u.sztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if ((szMsg->u.sztInfo.type.pres == PRSNT_NODEF) && 
       (szMsg->u.sztInfo.type.val == SZAC_ERRIND)) 
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "causeType",  &causeType);
      if (causeType != szMsg->u.sztInfo.u.errInd.type)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : causeType mismatch: exp (%d) rcvd (%d) \n",
                         causeType, szMsg->u.sztInfo.u.errInd.type), 2);
    
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "causeValue",  &causeValue);
      if (causeValue != szMsg->u.sztInfo.u.errInd.value)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : causeValue mismatch: exp (%d) rcvd (%d) \n",
                         causeValue, szMsg->u.sztInfo.u.errInd.value), 2);
    
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlSztErrInd */


/*
*
*       Fun:   szAcHdlSztUDatReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztUDatReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztUDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   SztUDatEvnt    uDatEvnt;
   S16            ret = CMXTA_ERR_NONE;
   U8            eventType = 0;
   Mem           mem;
   U8            testType=0;
   U32           filUDatReq=0;
   
   TRC2(szAcHdlSztUDatReq);

   mem.region = 0;
   mem.pool = 0;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztUDatReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztUDatReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);


   pst.event = EVTSZTUDATREQ;
 
   /* sz003.301: Updted for PSF-S1AP 3.1 release. Set the route as PRTO so
    * that it will be translated by MR */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "route",  &(pst.route));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dstProcId",  &(pst.dstProcId));
#endif /* SZ_FTHA */

   CMXTA_ZERO(&uDatEvnt, sizeof(SztUDatEvnt));

   if (ret != ROK)
      RETVALUE(CMXTA_ERR_RSRC);

   uDatEvnt.peerId.pres = PRSNT_NODEF;
   uDatEvnt.peerId.val = 0;
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(uDatEvnt.peerId.val));
   cmXtaXmlGetVal(NULL, spCb->childStep, CMXTA_ATTRIB_U8, "testType", &(testType));
 
   if (testType != 1)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType",  &(eventType));
      /* It is required to fill the connection oriented messages too for testing UE state 
       * machine bypass feature */
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "filUDatReq", &(filUDatReq));
      if(eventType == SZT_MSG_ID_RESET_ACK)
      {
         uDatEvnt.pdu = rstAckPdu;
         rstAckPdu = NULL;
      }
      else if(filUDatReq)
      {
         SztDatEvntReq  datEvnt;
         CMXTA_ZERO(&datEvnt, sizeof(SztDatEvntReq));
         szAcUtlSztFillDatReqPdu (tcCb, spCb, &datEvnt);
         uDatEvnt.pdu = datEvnt.pdu;
      }
      else
      {
         szAcUtlSztFillUDatReqPdu (tcCb, spCb, &uDatEvnt);
      }

      UzLiSztUDatReq(&pst, spId, &uDatEvnt);
   }
   else
   {
      pst.selector = 2;
      UzLiSztUDatReq(&pst, spId, NULL);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* szAcHdlSztUDatReq */

/*
*
*       Fun:   szAcHdlSztUDatInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztUDatInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztUDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   U8       eventType = 0;
   U8       choice = 0;
   U32      cause = 0;

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztUDatInd(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztUDatInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);

 
 
   pst.event = EVTSZTUDATIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlSztUDatInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, szMsg->u.sztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (szMsg->u.sztInfo.peerId.pres == PRSNT_NODEF)
   {
      U32  peerId = 0;
     
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

      if(peerId != szMsg->u.sztInfo.peerId.val)
      {
#ifdef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, szMsg->u.sztInfo.peerId.val), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, szMsg->u.sztInfo.peerId.val), 2);
#endif
    
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &eventType);
   if(eventType != szMsg->u.sztInfo.type.val)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : event mismatch: exp (%d) rcvd (%d) \n", eventType, szMsg->u.sztInfo.type.val), 2);
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Check for error cause type and value for Error msg */
   if(eventType == SZT_MSG_ID_ERR_IND)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "choice", &choice);
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "cause", &cause);
      if ((choice != szMsg->u.sztInfo.u.errInd.type) ||
          (cause != szMsg->u.sztInfo.u.errInd.value))
      {
#ifdef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : cause/Type mismatch: cause exp (%d) cause rcvd (%d) "
             "\n choice exp(%d) choice rcvd (%d) \n", cause, szMsg->u.sztInfo.u.errInd.value, 
             choice, szMsg->u.sztInfo.u.errInd.type), 4);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : cause/Type mismatch: cause exp (%ld) cause rcvd (%d) "
             "\n choice exp(%d) choice rcvd (%d) \n", cause, szMsg->u.sztInfo.u.errInd.value, 
             choice, szMsg->u.sztInfo.u.errInd.type), 4);
#endif
    
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlSztUDatInd */


/*
*
*       Fun:   szAcHdlSztConReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztConReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztConReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   SztConReq      conEvnt;
   S16            ret = CMXTA_ERR_NONE;
   U8            testType=0;
   
   TRC2(szAcHdlSztConReq);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztConReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztConReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);


   pst.event = EVTSZTCONREQ;
 
   /* sz003.301: Updted for PSF-S1AP 3.1 release. Set the route as PRTO so
    * that it will be translated by MR */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "route",  &(pst.route));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dstProcId",  &(pst.dstProcId));
#endif /* SZ_FTHA */

   CMXTA_ZERO(&conEvnt, sizeof(SztConReq));

   if (ret != ROK)
      RETVALUE(CMXTA_ERR_RSRC);

   conEvnt.peerId.pres = PRSNT_NODEF;
   conEvnt.peerId.val = 0;
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(conEvnt.peerId.val));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "testType", &(testType));
 
   if (testType != 1)
   {
      if(szAcUtlSztGetNewConnId(tcCb, spCb, &conEvnt.u.suConnId) != ROK)
         RETVALUE(RFAILED);
   
      szAcUtlSztFillConReqPdu(tcCb, spCb, &conEvnt);
   
      UzLiSztConReq(&pst, spId, &conEvnt);
   }
   else
   {
      pst.selector = 2;
      UzLiSztConReq(&pst, spId, NULL);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* szAcHdlSztConReq */

/*
*
*       Fun:   szAcHdlSztConInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztConInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztConInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   ProcId   srcProcId = 0;
   U8       eventType = 0;
   U32      suConnId = 0;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztConInd(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztConInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);

#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   srcProcId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
 
   pst.event = EVTSZTCONIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlSztConInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, szMsg->u.sztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (szMsg->u.sztInfo.peerId.pres == PRSNT_NODEF)
   {
      U32  peerId = 0;
     
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

      if(peerId != szMsg->u.sztInfo.peerId.val)
      {
#ifdef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, szMsg->u.sztInfo.peerId.val), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, szMsg->u.sztInfo.peerId.val), 2);
#endif
    
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &eventType);
   if(eventType != szMsg->u.sztInfo.type.val)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : event mismatch: exp (%d) rcvd (%d) \n", eventType, szMsg->u.sztInfo.type.val), 2);
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "usrConnId", &suConnId);

   /*  Store enbId & mmeId  */
   szacPduInfo[srcProcId][suConnId].enbId = 
                                  szMsg->u.sztInfo.u.pduInfo.enbId;
   szacPduInfo[srcProcId][suConnId].mmeId = 
                                  szMsg->u.sztInfo.u.pduInfo.mmeId;

   /* sz003.301: Updted for PSF-S1AP 3.1 release. Set the route as PRTO so
    * that it will be translated by MR */
#ifdef SZ_FTHA
   if(szAcUtlSztUpdConnId(tcCb, spCb, szMsg->u.sztInfo.spConnId) != ROK)
   {
      RETVALUE(RFAILED);
   } 
#endif /* SZ_FTHA */
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlSztConInd */


/*
*
*       Fun:   szAcHdlSztConRsp
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztConRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztConRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   SztConRsp      conEvnt;
   S16            ret = CMXTA_ERR_NONE;
   U8            testType=0;
   
   TRC2(szAcHdlSztConRsp);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztConRsp(), tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztConRsp(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);


   pst.event = EVTSZTCONRSP;
 
   /* sz003.301: Updted for PSF-S1AP 3.1 release. Set the route as PRTO so
    * that it will be translated by MR */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "route",  &(pst.route));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dstProcId",  &(pst.dstProcId));
#endif /* SZ_FTHA */

   CMXTA_ZERO(&conEvnt, sizeof(SztConRsp));

   if (ret != ROK)
      RETVALUE(CMXTA_ERR_RSRC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "testType", &(testType));

   if (testType != 1)
   {
      if(szAcUtlSztGetNewConnId(tcCb, spCb, &conEvnt.suConnId) != ROK) /* RCS */
         RETVALUE(RFAILED);
 
      if(szAcUtlSztRetrvConnId(tcCb, spCb, &conEvnt.spConnId) != ROK)
         RETVALUE(RFAILED);
   
      szAcUtlSztFillConRspPdu(tcCb, spCb, &conEvnt);
   
      UzLiSztConRsp(&pst, spId, &conEvnt);
   }
   else
   {
      pst.selector = 2;
      UzLiSztConRsp(&pst, spId, NULL);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* szAcHdlSztConRsp */

/*
*
*       Fun:   szAcHdlSztConCfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztConCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztConCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   UConnId       suConnId = 0;
   U8 eventType = 0;
   ProcId   srcProcId = 0;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztConCfm(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztConCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);

#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   srcProcId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
 
   pst.event = EVTSZTCONCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlSztConCfm(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, szMsg->u.sztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &eventType);
   if(eventType != szMsg->u.sztInfo.type.val)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : event mismatch: exp (%d) rcvd (%d) \n", eventType, szMsg->u.sztInfo.type.val), 2);
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "usrConnId",  &suConnId);

   /*  Store enbId & mmeId  */
   szacPduInfo[srcProcId][suConnId].enbId = 
                                  szMsg->u.sztInfo.u.pduInfo.enbId;
   szacPduInfo[srcProcId][suConnId].mmeId = 
                                  szMsg->u.sztInfo.u.pduInfo.mmeId;

   /* sz003.301: Updted for PSF-S1AP 3.1 release. Set the route as PRTO so
    * that it will be translated by MR */
#ifdef SZ_FTHA
   if(szAcUtlSztUpdConnId(tcCb, spCb, szMsg->u.sztInfo.spConnId) != ROK)
   {
      RETVALUE(RFAILED);
   } 
#endif /* SZ_FTHA */
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlSztConCfm */

/*
*
*       Fun:   szAcHdlSztRelReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztRelReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztRelReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   SztRelReq      relEvnt;
   S16            ret = CMXTA_ERR_NONE;
   U8             relType;
   U8            testType=0;
   
   TRC2(szAcHdlSztRelReq);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztRelReq(), tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztRelReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);


   pst.event = EVTSZTRELREQ;
 
   /* sz003.301: Updted for PSF-S1AP 3.1 release. Set the route as PRTO so
    * that it will be translated by MR */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "route",  &(pst.route));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dstProcId",  &(pst.dstProcId));
#endif /* SZ_FTHA */

   CMXTA_ZERO(&relEvnt, sizeof(SztRelReq));

   if (ret != ROK)
      RETVALUE(CMXTA_ERR_RSRC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "testType", &(testType));
 
   if (testType != 1)
   {
      relType = SZT_CXT_REL;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "relType",  &(relType));

      relEvnt.relType = relType;

      relEvnt.connIdType = SZT_CONN_TYPE_SP;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "conType",  &(relEvnt.connIdType));

      if (relEvnt.connIdType == SZT_CONN_TYPE_SP)
      {
         if(szAcUtlSztRetrvConnId(tcCb, spCb, &relEvnt.connId) != ROK)
            RETVALUE(RFAILED);
      }
      else
      {
         relEvnt.connId = 1;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "usrConnId",  &(relEvnt.connId));
     
      }
   
      if (relEvnt.relType != SZT_LOCAL_REL)
      {
         szAcUtlSztFillRelReqPdu(tcCb, spCb, &relEvnt);
      }
   
      UzLiSztRelReq(&pst, spId, &relEvnt);
   }
   else
   {
     pst.selector = 2;
     UzLiSztRelReq(&pst, spId, NULL);
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* szAcHdlSztRelReq */

/*
*
*       Fun:   szAcHdlSztRelInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztRelInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztRelInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   U8       eventType = 0;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztRelInd(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztRelInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);

 
 
   pst.event = EVTSZTRELIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlSztRelInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, szMsg->u.sztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &eventType);
   if(eventType != szMsg->u.sztInfo.type.val)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : event mismatch: exp (%d) rcvd (%d) \n", eventType, szMsg->u.sztInfo.type.val), 2);
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlSztRelInd */

/*
*
*       Fun:   szAcHdlSztRelRsp
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztRelRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztRelRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   SztRelRsp      relEvnt;
   S16            ret = CMXTA_ERR_NONE;
   U8            testType=0;
   
   TRC2(szAcHdlSztRelRsp);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztRelRsp(), tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztRelRsp(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);


   pst.event = EVTSZTRELRSP;
 
   /* sz003.301: Updted for PSF-S1AP 3.1 release. Set the route as PRTO so
    * that it will be translated by MR */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "route",  &(pst.route));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dstProcId",  &(pst.dstProcId));
#endif /* SZ_FTHA */

   CMXTA_ZERO(&relEvnt, sizeof(SztRelRsp));

   if (ret != ROK)
     RETVALUE(CMXTA_ERR_RSRC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "testType", &(testType));
 
   if (testType != 1)
   {
      if(szAcUtlSztRetrvConnId(tcCb, spCb, &relEvnt.spConnId) != ROK)
         RETVALUE(RFAILED);
   
      szAcUtlSztFillRelRspPdu(tcCb, spCb, &relEvnt);
   
      UzLiSztRelRsp(&pst, spId, &relEvnt);
   }
   else
   {
      pst.selector = 2;
      UzLiSztRelRsp(&pst, spId, NULL);
   }


   RETVALUE(CMXTA_ERR_NONE);
} /* szAcHdlSztRelRsp */

/*
*
*       Fun:   szAcHdlSztRelCfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztRelCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztRelCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztRelCfm(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztRelCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);

 
 
   pst.event = EVTSZTRELCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlSztRelCfm(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, szMsg->u.sztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /* TBD: Add code for validation after pdu finalized */

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlSztRelCfm */

/*
*
*       Fun:   szAcHdlSztDatReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztDatReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   SztDatEvntReq  datEvnt;
   S16            ret = CMXTA_ERR_NONE;
   U8            testType=0;
   
   TRC2(szAcHdlSztDatReq);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztDatReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztDatReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);


   pst.event = EVTSZTDATREQ;
 
   /* sz003.301: Updted for PSF-S1AP 3.1 release. Set the route as PRTO so
    * that it will be translated by MR */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "route",  &(pst.route));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dstProcId",  &(pst.dstProcId));
#endif /* SZ_FTHA */

   CMXTA_ZERO(&datEvnt, sizeof(SztDatEvntReq));

   if (ret != ROK)
      RETVALUE(CMXTA_ERR_RSRC);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "testType", &(testType));
 
   if (testType != 1)
   {
 
      if(szAcUtlSztRetrvConnId(tcCb, spCb, &datEvnt.spConnId) != ROK)
         RETVALUE(RFAILED);
   
      szAcUtlSztFillDatReqPdu(tcCb, spCb, &datEvnt);
   
      UzLiSztDatReq(&pst, spId, &datEvnt);
   }
   else
   {
     pst.selector = 2;
     UzLiSztDatReq(&pst, spId, NULL);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* szAcHdlSztDatReq */

/*
*
*       Fun:   szAcHdlSztDatInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztDatInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   ProcId   srcProcId = 0;
   U8       eventType = 0;
   U8       choice = 0;
   U32      cause = 0;
   UConnId  suConnId = 0;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztDatInd(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztDatInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);

#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   srcProcId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
 
   pst.event = EVTSZTDATIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlSztDatInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, szMsg->u.sztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &eventType);
   if(eventType != szMsg->u.sztInfo.type.val)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : event mismatch: exp (%d) rcvd (%d) \n", eventType, szMsg->u.sztInfo.type.val), 2);
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /* Check for error cause type and value for Error msg */
   if(eventType == SZT_MSG_ID_ERR_IND)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "choice", &choice);
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "cause", &cause);
      if ((choice != szMsg->u.sztInfo.u.errInd.type) ||
          (cause != szMsg->u.sztInfo.u.errInd.value))
      {
#ifdef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : cause/Type mismatch: cause exp (%d) cause rcvd (%d) "
             "\n choice exp(%d) choice rcvd (%d) \n", cause, szMsg->u.sztInfo.u.errInd.value, 
             choice, szMsg->u.sztInfo.u.errInd.type), 4);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : cause/Type mismatch: cause exp (%ld) cause rcvd (%d) "
             "\n choice exp(%d) choice rcvd (%d) \n", cause, szMsg->u.sztInfo.u.errInd.value, 
             choice, szMsg->u.sztInfo.u.errInd.type), 4);
#endif
    
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "usrConnId", &suConnId);

   /*  Store enbId & mmeId  */
   szacPduInfo[srcProcId][suConnId].enbId = 
                                  szMsg->u.sztInfo.u.pduInfo.enbId;
   szacPduInfo[srcProcId][suConnId].mmeId = 
                                  szMsg->u.sztInfo.u.pduInfo.mmeId;

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlSztDatInd */

/*
*
*       Fun:   szAcHdlSztEncReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztEncReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztEncReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   SztEncDecEvnt  *encEvnt;
   U8             reqType = 0;
   S16            ret = CMXTA_ERR_NONE;
   U8             eventType = 0;
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
   U8             type = 0;
#endif   /* SZTV1 */
   Bool           tightCoupled = FALSE;
   
   TRC2(szAcHdlSztEncReq);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztEncReq(), tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztEncReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);
   if(tightCoupled)
   {
      pst.selector = 2;
   }

   pst.event = EVTSZTENCDECREQ;

   CMXTA_ALLOC(&encEvnt, sizeof(SztEncDecEvnt)); 

   if (ret != ROK)
      RETVALUE(CMXTA_ERR_RSRC);

   encEvnt->transId = 1;
   encEvnt->type.pres = PRSNT_NODEF;
   encEvnt->type.val = SZT_REQ_TYPE_ENCODE;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "reqType",  &(reqType));
   if (reqType == 1)
   {
     encEvnt->type.val = 0;
   }
   if (reqType == 2)
   {
      encEvnt->type.pres = NOTPRSNT;
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",
                                             &(encEvnt->transId));
  if (reqType == 3)
  {
     pst.selector = 2;
     encEvnt->u.pdu = NULL;
  }
  else
  {
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"eventType",&(eventType));
     if (eventType == SZT_MSG_ID_NO_DATA)
     {
        pst.selector = 2;
     }

/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
     cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"type",&(type));
     if (type == 3)
     {
        encEvnt->type.val = SZT_REQ_TYPE_ENCODE_IE;
     }
     if (encEvnt->type.val == SZT_REQ_TYPE_ENCODE)
     {
#endif   /* SZTV1 */
        szAcUtlSztFillEncReqPdu(tcCb, spCb, encEvnt);
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
     }
     else
     {
        szAcUtlSztFillEncReqIe(tcCb, spCb, encEvnt);
     }
#endif    /* SZTV1 */
  }

   UzLiSztEncDecReq(&pst, spId, encEvnt);
   /* purify fix */
   if(pst.selector == 2)
   {
      CMXTA_FREE(encEvnt, sizeof(SztEncDecEvnt));
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* szAcHdlSztEncReq */

/*
*
*       Fun:   szAcHdlSztDecReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztDecReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztDecReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   SztEncDecEvnt  *encEvnt;
   SztEncDecEvnt  tmpEncEvnt;
   Mem            mem;
   U8             msgStr[1000];
   U8             reqType = 0;
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
   U8             type = 0;
#endif   /* SZTV1 */
   
   TRC2(szAcHdlSztDecReq);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztDecReq(), tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztDecReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   mem.region = SZ_ACC_DFLT_RGN;
   mem.pool   = SZ_ACC_DFLT_POOL;

   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);


   pst.event = EVTSZTENCDECREQ;
 
   CMXTA_ALLOC(&encEvnt, sizeof(SztEncDecEvnt));

   encEvnt->transId = 1;
   encEvnt->type.pres = PRSNT_NODEF;
   encEvnt->type.val = SZT_REQ_TYPE_DECODE;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "transId",
                                             &(encEvnt->transId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "reqType",  &(reqType));
   if (reqType == 1)
   {
      pst.selector = 2;
      encEvnt->u.mBuf = NULL;
   }
   else
   {
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"type",&(type));
      if (type == 4)
      {
         encEvnt->type.val = SZT_REQ_TYPE_DECODE_IE;
      }
      if (encEvnt->type.val == SZT_REQ_TYPE_DECODE)
      {
#endif    /* SZTV1 */
         szAcUtlSztFillEncReqPdu(tcCb, spCb, &tmpEncEvnt);
         if (szAcEncode_r11(&mem, &(tmpEncEvnt.u.pdu), &(encEvnt->u.mBuf)) != ROK)
         {
            RETVALUE(RFAILED);
         }
         SZ_FREE_SDU(tmpEncEvnt.u.pdu);
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
      }
      else
      {
         szAcUtlSztFillEncReqIe(tcCb, spCb, encEvnt);
         if (szAcEncodeIe(&mem, encEvnt) != ROK)
         {
            RETVALUE(RFAILED);
         }
      }
#endif   /* SZTV1 */


       msgStr[0] = '\0';
       cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "msgStr", msgStr);

   
       if(msgStr != NULLP)
       {
          SAddPstMsgMult((U8 *)msgStr, cmStrlen((U8 *)msgStr), encEvnt->u.mBuf); 
       }
   }
   UzLiSztEncDecReq(&pst, spId, encEvnt);
   /* purify fix */
   if(pst.selector == 2)
   {
      CMXTA_FREE(encEvnt, sizeof(SztEncDecEvnt));
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* szAcHdlSztDecReq */


/*
*
*       Fun:   szAcHdlSztEncDecCfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztEncDecCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztEncDecCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztEncDecCfm(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztEncDecCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);
 
   pst.event = EVTSZTENCDECCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlSztEncDecCfm(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, szMsg->u.sztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /* TBD: Add code for validation after pdu finalized */

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlSztEncDecCfm */

#ifdef SZ_MME
/*
*
*       Fun:   szAcHdlSztPeerAssocInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztPeerAssocInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztPeerAssocInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   SzAccMsgQElm   *szMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztPeerAssocInd(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztPeerAssocInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   szMsg = (SzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);
 
   pst.event = EVTSZTPEERASSOCIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "szAcHdlSztPeerAssocInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, szMsg->u.sztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* szAcHdlSztPeerAssocInd */

/*
*
*       Fun:   szAcHdlSztPeerAssocRsp
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 szAcHdlSztPeerAssocRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 szAcHdlSztPeerAssocRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst              pst;
   SpId             spId = 0;
   SztPeerAssocRsp  assocRsp; 
   S8               tmpAddrArr[16];
   U32              tmpAddr;
   U8            testType=0;
   
   TRC2(szAcHdlSztPeerAssocRsp);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztPeerAssocRsp(), tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztPeerAssocRsp(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);

   pst.event = EVTSZTPEERASSOCRSP;
 
   /* sz003.301: Updted for PSF-S1AP 3.1 release. Set the route as PRTO so
    * that it will be translated by MR */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "route",  &(pst.route));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dstProcId",  &(pst.dstProcId));
#endif /* SZ_FTHA */

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "testType", &(testType));
 
   if (testType != 1) 
   {

      CMXTA_ZERO(&assocRsp, sizeof(SztPeerAssocRsp));

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId",  &(assocRsp.peerId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "comProcStrm",  &(assocRsp.comProcStrm));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "locOutStrms",  &(assocRsp.locOutStrms));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "addressType", &(assocRsp.priDstAddr.type) );
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dstPort", &(assocRsp.dstPort) );

      cmMemset ((U8 *)tmpAddrArr, 0, 16);
      strcpy((S8 *)tmpAddrArr, "127.0.0.1");

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "address", (tmpAddrArr) );
      if(strcmp(tmpAddrArr,"\0") == 0)
      {
         CMXTA_ZERO(&assocRsp.priDstAddr, sizeof(CmNetAddr));
      }
      else
      {
         if(assocRsp.priDstAddr.type == CM_NETADDR_IPV4)
         {
            cmInetAddr(tmpAddrArr, &tmpAddr);
            assocRsp.priDstAddr.u.ipv4NetAddr = CM_INET_NTOH_U32(tmpAddr);
         }
         else
         {
            strcpy((S8 *)assocRsp.priDstAddr.u.ipv6NetAddr,tmpAddrArr);
         }
      }

      assocRsp.dstAddrLst = dynamDstAddrLst; 

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",  &(assocRsp.status.status));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "cause",  &(assocRsp.status.cause));

      UzLiSztPeerAssocRsp(&pst, spId, &assocRsp);
   }
   else
   {
     pst.selector = 2;
     UzLiSztPeerAssocRsp(&pst, spId, NULL);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* szAcHdlSztConRsp */
#endif

/* sz005.301 Added for S1 Abort request support by UI */
#ifdef SZTV2
/*
*
*       Fun:   szAcHdlSztAborts1Req
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlSztAbortS1Req
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSztAbortS1Req(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   SuId          suId = 0;             /* service user SAP identifier */
   SpId          spId = 0;             /* service user SAP identifier */
   SztAbortS1    *abortS1 = NULLP;
   
   TRC2(szAcHdlSztAbortS1Req);
   
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztAbortS1Req(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztAbortS1Req(), tcId (%ld)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   CMXTA_ALLOC(&abortS1, sizeof(SztAbortS1)); 

   szAcGetPst(spCb, &pst, ENTUZ, CMXTA_INST_ID, ENTSZ, CMXTA_INST_ID);
   
   pst.event = EVTSZTABORTS1REQ;

   abortS1->peerId.pres = PRSNT_NODEF; 
   abortS1->peerId.val = 0;
   
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "route",  &(pst.route));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dstProcId",  &(pst.dstProcId));
#endif /* SZ_FTHA */

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(abortS1->peerId.val));
 
   /* Send the request to the GCP --*/
   UzLiSztAbortS1Req(&pst, spId, abortS1);
   /* purify fix */
   CMXTA_FREE(abortS1, sizeof(SztAbortS1));

   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- szAcHdlSztAbortS1Req --*/

/*
*
*       Fun:   szAcHdlSztAbortS1Cfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_szthdl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcHdlSztAbortS1Cfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSztAbortS1Cfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg;
   SzAccMsgQElm  *szMsg;
   Pst           pst;
   S16           ret = ROK;
   SpId          suId;
   Status        status = SZT_PRIM_OK;
 
   TRC2(szAcHdlSztAbortS1Cfm);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztAbortS1Cfm(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSztAbortS1Cfm(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSztAbortS1Cfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   szMsg = (SzAccMsgQElm *)msg->data;

   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTUZ, CMXTA_INST_ID);

   pst.event = EVTSZTABORTS1CFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }
 
   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
 
   suId = 0; /*-- Note suId = spId --*/

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != szMsg->u.sztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, szMsg->u.sztInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",  &(status));
 
   if (status != szMsg->u.sztInfo.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, szMsg->u.sztInfo.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- szAcHdlSztAbortS1Cfm --*/
 

#endif /* SZTV2 */

/********************************************************************30**

         End of file:     szac_szthdl.c@@/main/4 - Mon Jan 10 22:16:01 2011

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/4      ---      pkaX  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/4   sz004.301   va    1. Updated for Transparent Container 
                                 Enc/Dec
/main/4   sz005.301   va    1. Updated for S1 Abort request support by UI
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
