
/********************************************************************20**

     Name:    S1AP Layer

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    czac_scthdl.c

     Sid:      czac_scthdl.c@@/main/2 - Tue Aug 30 18:35:53 2011

     Prg:     sy

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
#include "cm_pasn.h"
#include "cm_dns.h"         /* common DNS libraru defines */

#include "cz.h"            /* defines and macros for CZ */
#include "lcz.h"            /* defines and macros for CZ */
#include "sct.h"            /* defines and macros for CZ */
#include "czt.h"            /* defines and macros for CZ */
#include "cz_err.h"        /* CZ error defines */
#include "czac_acc.h"        /* defines for CZ acceptance tests */
#include "cm_xta.h" 

#ifdef SB
#include "lsb.h"            /* SCTP layer managment defines */
#endif /*SB*/
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/

/* S1AP related header file */
#include "cm_xta.h"
#include "czac_acc.h"
#ifdef HI 
#include "lhi.h"
#endif /*hi*/
#include "sct.h"
#ifdef SB 
#include "lsb.h"            /* SCTP */
#endif /*sb*/
#include "lcz.h"
#include "cz.h"

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
#include "cm_pasn.x"
#include "cm_dns.x"         /* common DNS libraru defines */



/*#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czt.x"*/
/* SCTP Related header files */
#ifdef HI
#include "lhi.x"
#endif /*hi*/
#include "sct.x"
#ifdef SB 
#include "lsb.x"            /* SCTP */
#endif /*sb*/
#include "cm_xta.x"
#include "lcz.x"
#include "czac_acc.x"
#include "czac_sct.x"
#include "czac_lcz.x"
/*#include "czac_czt.x"
#include "cz.x"*/
   
EXTERN S16 czAcUtlBuildX2APPdu_r9 ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb, Buffer
                  **mBuf));
EXTERN S16 czAcUtlBuildX2APPdu_r11 ARGS((CmXtaTCCb *tcCb, CmXtaSpCb *spCb,Buffer
                  **mBuf));

/***********************************************************
This files provides the following set of primitives which 
are used when S1AP is not integrated with the Trillium SCTP.
Instead we will be having dummy SCTP
***********************************************************/
/*--
czAcHdlSctBndReq
czAcHdlSctEndpOpenReq
czAcHdlSctEndpCloseReq
czAcHdlSctAssocReq
czAcHdlSctAssocRsp
czAcHdlSctTermReq
czAcHdlSctSetPriReq
czAcHdlSctHBeatReq
czAcHdlSctDatReq
czAcHdlSctStaReq
--*/
/* cz001.101        : CR Fixes. */
#ifdef DM
#define  CZAC_DFLT_IPADDR1 0xac19005d
/*PRIVATE S16 czAcSctFillCztInfo ( CztEvnt *ptr, CzAcCztInfo  *cztInfo, S16 *fsmType);*/


/*
*
*       Fun:   czAcHdlSctBndReq
*
*       Desc:  Handler for SCT Bind Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   CmXtaMsgQElm  *msg = NULLP;
   CzAccMsgQElm  *czMsg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   SpId          spId = 0;

   CMXTA_ZERO(&pst, sizeof(Pst));
   TRC2(czAcHdlSctBndReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctBndReq(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctBndReq(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "czAcHdlSctBndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   czMsg = (CzAccMsgQElm *)msg->data; 

   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTBNDREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSctBndReq(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   /*-- Set default value & validate for spid --*/
   spId = CZAC_DFLT_SPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if (spId != czMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_ERR((_cmxtap, "SpId match failed exp :(%d) recvd (%d) \n", 
                  spId, czMsg->u.sctInfo.cmInfo.spId));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Flush msg --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctBndReq --*/

/*
*
*       Fun:   czAcHdlSctEndpOpenReq
*
*       Desc:  Handler for SCT Open Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctEndpOpenReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctEndpOpenReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   CmXtaMsgQElm  *msg = NULLP;
   CzAccMsgQElm  *czMsg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   UConnId       suEndpId = 0;
   SuId          spId = 0;             /* service user SAP identifier */

   CMXTA_ZERO(&pst, sizeof(Pst));
   TRC2(czAcHdlSctEndpOpenReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctEndpOpenReq(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctEndpOpenReq(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "czAcHdlSctEndpOpenReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   
      czMsg = (CzAccMsgQElm *)msg->data;

  czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTENDPOPENREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSctEndpOpenReq(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   /*-- Set default value & validate for spid --*/
   spId = CZAC_DFLT_SPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if (spId != czMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId MisMatch: exp (%d) recvd (%d) \n",
                          spId, czMsg->u.sctInfo.cmInfo.spId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for suEndpId --*/
   suEndpId = CZAC_DFLT_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suEndpId",  &(suEndpId));
   if (suEndpId != czMsg->u.sctInfo.suEndpId)
   {
#ifndef ALIGN_64BIT   
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suEndpId MisMatch: exp (%ld) recvd (%ld) \n",
                     suEndpId, czMsg->u.sctInfo.suEndpId), 2);
#else /* ALIGN_64BIT */
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suEndpId MisMatch: exp (%d) recvd (%d) \n",
                     suEndpId, czMsg->u.sctInfo.suEndpId), 2);
#endif /* ALIGN_64BIT */
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- This handler does not validate the port and the IP addresses inside the 
        netAddrLst at this moment, if required, enhance this handler to do the 
        validation for the same --*/

   /*-- free memory --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctEndpOpenReq --*/

/*
*
*       Fun:   czAcHdlSctEndpCloseReq
*
*       Desc:  SCT Endpoint Close Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctEndpCloseReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctEndpCloseReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   CmXtaMsgQElm  *msg = NULLP;
   CzAccMsgQElm  *czMsg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   UConnId       suEndpId = 0;
   U8            endpIdType = 0;
   SuId          spId = 0;             /* service user SAP identifier */

   CMXTA_ZERO(&pst, sizeof(Pst));
   TRC2(czAcHdlSctEndpCloseReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctEndpCloseReq(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctEndpCloseReq(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
         CMXTA_DBG_FATAL((_cmxtap, "czAcHdlSctEndpCloseReq(): cmXtaPeekMsg failed\n"));
         RETVALUE(CMXTA_ERR_FATAL);
   }

   czMsg = (CzAccMsgQElm *)msg->data;

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTENDPCLOSEREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSctEndpCloseReq(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   /*-- Set default value & validate for spid --*/
   spId = CZAC_DFLT_SPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if (spId != czMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId MisMatch: exp (%d) recvd (%d) \n",
                     spId, czMsg->u.sctInfo.cmInfo.spId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for endpIdType --*/
   endpIdType = SCT_ENDPID_SP;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "endpIdType",  &(endpIdType));
   if (endpIdType != czMsg->u.sctInfo.endpIdType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : endpIdType MisMatch: exp (%d) recvd (%d) \n",
                     endpIdType, czMsg->u.sctInfo.endpIdType), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for suEndpId --*/
   suEndpId = CZAC_DFLT_SU_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "spEndpId",  &(suEndpId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suEndpId",  &(suEndpId));
   if (suEndpId != czMsg->u.sctInfo.suEndpId)
   {
#ifndef ALIGN_64BIT   
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suEndpId MisMatch: exp (%ld) recvd (%ld) \n",
                     suEndpId, czMsg->u.sctInfo.suEndpId), 2);
#else /* ALIGN_64BIT */
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suEndpId MisMatch: exp (%d) recvd (%d) \n",
                     suEndpId, czMsg->u.sctInfo.suEndpId), 2);
#endif /* ALIGN_64BIT */
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctEndpCloseReq --*/

/*
*
*       Fun:   czAcHdlSctAssocReq
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctAssocReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctAssocReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   CmXtaMsgQElm  *msg = NULLP;
   CzAccMsgQElm  *czMsg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   UConnId       spEndpId = 0;
   U16           port = 0;
   SuId          spId = 0;             /* service user SAP identifier */
   U32           assocIdx = 0;
   UConnId       suAssocId = 0;
   ProcId        dstProcId = CZAC_ENB2_PROC; 
   U8            indx; 

   CzAcSctAssocCb   *assocCb = NULLP;

   CMXTA_ZERO(&pst, sizeof(Pst));
   TRC2(czAcHdlSctAssocReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctAssocReq(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctAssocReq(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "czAcHdlSctAssocReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   czMsg = (CzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTASSOCREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSctAssocReq(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   /*-- Set default value & validate for spid --*/
   spId = CZAC_DFLT_SPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != czMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId MisMatch: exp (%d) recvd (%d) \n",
                     spId, czMsg->u.sctInfo.cmInfo.spId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   /*-- Set default value & validate for spEndpId --*/
   spEndpId = CZAC_DFLT_SP_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "spEndpId",  &(spEndpId));

   if (spEndpId != czMsg->u.sctInfo.spEndpId)
   {
#ifndef ALIGN_64BIT   
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spEndpId MisMatch: exp (%ld) recvd (%ld) \n",
                     spEndpId, czMsg->u.sctInfo.spEndpId), 2);
#else /* ALIGN_64BIT */
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spEndpId MisMatch: exp (%d) recvd (%d) \n",
                     spEndpId, czMsg->u.sctInfo.spEndpId), 2);
#endif /* ALIGN_64BIT */
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for spEndpId --*/
   /*port = DFL_PORT; */

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "peerProcId",  &(dstProcId));
   CZ_GET_PEERPROF_INDEX(dstProcId, indx);
   port = czENodeB[indx].protCfg.srcAddr.sctPort;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "port",  &(port));
   if (port != czMsg->u.sctInfo.port)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : port MisMatch: exp (%d) recvd (%d) \n",
                     port, czMsg->u.sctInfo.port), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- A new association is being opened by S1AP stack, so there is no validation
        for suAssocId. Create a new assocCb using the suAssocId received from the
        UI interface --*/
   suAssocId = czMsg->u.sctInfo.suAssocId;

   /*-- Create a new assoc control block --*/
   if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, CZT_CONNID_NOTUSED)) == NULLP)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctAssocReq --*/

/*
*
*       Fun:   czAcHdlSctAssocRsp
*
*       Desc:  SCT Association Response
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctAssocRsp
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctAssocRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   CmXtaMsgQElm  *msg = NULLP;
   CzAccMsgQElm  *czMsg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   SuId          spId = 0;             /* service user SAP identifier */
   U32           assocIdx = 0;
   U8            type = 0;

   CzAcSctAssocCb   *assocCb = NULLP;
   CMXTA_ZERO(&pst, sizeof(Pst));

   TRC2(czAcHdlSctAssocRsp)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctAssocRsp(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctAssocRsp(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "czAcHdlSctAssocRsp(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   czMsg = (CzAccMsgQElm *)msg->data;
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTASSOCRSP;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSctAssocRsp(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   /*-- Set default value & validate for spid --*/
   spId = CZAC_DFLT_SPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != czMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId MisMatch: exp (%d) recvd (%d) \n",
                     spId, czMsg->u.sctInfo.cmInfo.spId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- GET value for srcId, dstId, assocIdx and entId --*/
   assocIdx = CZAC_DFLT_ASSOCIDX;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "assocIdx", &(assocIdx));

   /*-- Find assoc control block --*/
   if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFind(tcCb, assocIdx)) == NULLP)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for AssocRsp Type --*/
   type = SCT_ASSOC_IND_INIT;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "type",  &(type));
   if (type != czMsg->u.sctInfo.assocParams.type)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Assoc Rsp type MisMatch: exp (%d) recvd (%d) \n",
                     type, czMsg->u.sctInfo.assocParams.type), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (type == SCT_ASSOC_IND_COOKIE)
   {
      /*-- Update the suAssocId in the assocCb --*/
      assocCb->suAssocId = czMsg->u.sctInfo.assocParams.t.cookieParams.suAssocId;
   }
   else
   {
      /*-- Note: here the validation for the spAssocId will not 
          be done as it has not been generated till now --*/
   }

   /*-- free memory --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctAssocRsp --*/

/*
*
*       Fun:   czAcHdlSctTermReq
*
*       Desc:  Termination Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctTermReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctTermReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   CmXtaMsgQElm  *msg = NULLP;
   CzAccMsgQElm  *czMsg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   U8            validate = 0;
   SuId          spId = 0;             /* service user SAP identifier */
   U32           assocIdx = 0;
   UConnId       suAssocId = 0;
   UConnId       spAssocId = 0;
   U8            assocIdType = 0;

   CzAcSctAssocCb   *assocCb = NULLP;

   TRC2(czAcHdlSctTermReq)

   CMXTA_ZERO(&pst, sizeof(Pst));
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctTermReq(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctTermReq(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "czAcHdlSctTermReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   czMsg = (CzAccMsgQElm *) msg->data;
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTTERMREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSctTermReq(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   /*-- Set default value & validate for spid --*/
   spId = CZAC_DFLT_SPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != czMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId MisMatch: exp (%d) recvd (%d) \n",
                     spId, czMsg->u.sctInfo.cmInfo.spId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- GET value for srcId, dstId, assocIdx and entId --*/
      assocIdx = CZAC_DFLT_ASSOCIDX;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "assocIdx",  &(assocIdx));

   /*-- Set default value & validate for assocIdType --*/
   assocIdType = SCT_ASSOCID_SP;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "assocIdType",  &(assocIdType));
   if (assocIdType != czMsg->u.sctInfo.assocIdType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : assocIdType MisMatch: exp (%d) recvd (%d) \n",
                     assocIdType, czMsg->u.sctInfo.assocIdType), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   validate = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "validate",  &(validate));

   if (validate == TRUE)
   {
      if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFind(tcCb, assocIdx)) == NULLP)
      {
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   /*-- Create a new assoc control block --*/
   else
   {
      if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFindnCreate(tcCb, assocIdx,
                          czMsg->u.sctInfo.suAssocId, CZT_CONNID_NOTUSED)) == NULLP)
         RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- Set default value & validate for suAssocId, from TA, suAssocId and 
         spAssocId are the same --*/

   if(SCT_ASSOCID_SU == czMsg->u.sctInfo.assocIdType)
   {
      /*-- Validate suAssocId --*/
      suAssocId = assocCb->suAssocId;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suAssocId",  &(suAssocId));
      if (suAssocId != czMsg->u.sctInfo.suAssocId)
      {
#ifndef ALIGN_64BIT      
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : suAssocId MisMatch: exp (%ld) recvd (%ld) \n",
                  suAssocId, czMsg->u.sctInfo.suAssocId), 2);
#else /* ALIGN_64BIT */
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : suAssocId MisMatch: exp (%d) recvd (%d) \n",
                  suAssocId, czMsg->u.sctInfo.suAssocId), 2);
#endif /* ALIGN_64BIT */
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else
   {
      /*-- Validate spAssocId --*/
      spAssocId = assocCb->spAssocId;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "spAssocId",  &(spAssocId));
      if (spAssocId != czMsg->u.sctInfo.spAssocId)
      {
#ifndef ALIGN_64BIT      
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : spAssocId MisMatch: exp (%ld) recvd (%ld) \n",
                  spAssocId, czMsg->u.sctInfo.spAssocId), 2);
#else /* ALIGN_64BIT */
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : spAssocId MisMatch: exp (%d) recvd (%d) \n",
                  spAssocId, czMsg->u.sctInfo.spAssocId), 2);
#endif /* ALIGN_64BIT */
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   /*-- free memory --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctTermReq --*/


/*
*
*       Fun:   czAcHdlSctSetPriReq
*
*       Desc:  Handler for setting the Primary IP address 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctSetPriReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctSetPriReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   CmXtaMsgQElm  *msg = NULLP;
   CzAccMsgQElm  *czMsg = NULLP;
   Pst           pst;
   S16           ret;

   TRC2(czAcHdlSctSetPriReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctSetPriReq(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctSetPriReq(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "czAcHdlSctSetPriReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
      czMsg = (CzAccMsgQElm *) msg->data;

   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTSETPRIREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSctSetPriReq(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/*-- czAcHdlSctSetPriReq --*/


/*
*
*       Fun:   czAcHdlSctHBeatReq
*
*       Desc:  Handler for the HeartBeat Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctHBeatReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctHBeatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   CmXtaMsgQElm  *msg = NULLP;
   CzAccMsgQElm  *czMsg = NULLP;
   Pst           pst;
   S16           ret;

   TRC2(czAcHdlSctHBeatReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctHBeatReq(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctHBeatReq(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "czAcHdlSctHBeatReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   czMsg = (CzAccMsgQElm *)msg->data;
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTHBEATREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSctHBeatReq(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/*-- czAcHdlSctHBeatReq --*/

/*
*
*       Fun:   czAcHdlSctDatReq
*
*       Desc:  Handler for SCT Dat Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctDatReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   CmXtaMsgQElm  *msg = NULLP;
   CzAccMsgQElm  *czMsg = NULLP;
   CzAccMsgQElm  *czMsgVal = NULLP;
   /*CztEvnt       *uiEvnt = NULLP;*/
   Pst           pst;
   S16           ret;
   SpId          spId;
   SctStrmId strmId;         /* stream ID */
   U8             eventType;
   Mem  mem; 
   CmPAsnErr pasnErr;




   TRC2(czAcHdlSctDatReq)
   mem.region = 0;
   mem.pool   = 0;
  (Void)cmMemset((U8*)(&pasnErr), 0, sizeof(CmPAsnErr));
   

   czMsgVal = NULLP;
   CMXTA_ALLOC(&czMsgVal, sizeof (CzAccMsgQElm));
   if (czMsgVal == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "DmUiSctStaReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctDatReq(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctDatReq(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   /* Initialize memory control point */
   
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      /* cz001.301: purify fix : in Error case freeing the czMsgVal memorey */
      CMXTA_FREE(czMsgVal, sizeof (CzAccMsgQElm));
      CMXTA_DBG_FATAL((_cmxtap, "czAcHdlSctDatReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   czMsg = (CzAccMsgQElm *)msg->data;

   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTDATREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      /* cz001.301: purify fix : in Error case freeing the czMsgVal memorey */
      CMXTA_FREE(czMsgVal, sizeof (CzAccMsgQElm));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSctDatReq(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
#if 0
   do
   {
      mBuf = czMsg->u.sctInfo.mBuf; 

   dbgFlag = FALSE;

      
   /* Initialize the PASN Error code */ 
   CZ_ALLOCEVNT((Ptr *)&uiEvnt, sizeof(CztEvnt), (&mem));
   if(NULLP == uiEvnt)
   {
      CZ_DBG_FATAL((CZ_PRNT_BUF,"Allocation of CzEvnt Failed \n"));
      CZ_RETVALUE(RFAILED);
   }
      
   pasnErr.errCode = 0;
   msgLen = 0;
 
   ret = (cmPAsnDecMsg((Void *)&(uiEvnt->pdu), CM_PASN_USE_MBUF, 
                  (Void **)&mBuf, &numDecOct, CZ_PASN_VER_ZERO, 
                  (CmPAsnElmDef **)czMsgDb, CM_PASN_GEN_ERR, &pasnErr, 
                  msgLen, (CmMemListCp *)uiEvnt, dbgFlag));
  
   if (ret == RFAILED)
   {
      /* It's an ASN.1 Error */
      CZ_DBG_INFO((CZ_PRNT_BUF,
            " Syntax Error : Decoding failed, Reason %d\n", 
                               err->errCode)); 
      /* CZ_FREEEVNT(event);    */
      /* CZ_RETVALUE(RFAILED); */
   }


      pdu = (Void *)(&(uiEvnt->pdu));
      ret = czAcSctFillCztInfo (uiEvnt, &czMsgVal->u.cztInfo, &fsmType);
      if(ret == RFAILED)
      {
         cmFreeMem((Ptr)uiEvnt);
         break;
      }
      /* Validate whether this is GPM Message or BMP Message 
       * fsmType is filled by czAcSctFillCztInfo */
      ret = czAcUtlValidateMsg(tcCb, spCb, czMsgVal, fsmType);   
      if (ret != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "Validation Failed\n"));
      }
      cmFreeMem((Ptr)uiEvnt);
   }while(0);
#endif

   CMXTA_FREE(czMsgVal, sizeof (CzAccMsgQElm));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType",  &(eventType));

   spId = CZAC_DFLT_SPID;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &spId);
   if (spId != czMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId mismatch: exp (%d) rcvd (%d) \n",
                          spId, czMsg->u.sctInfo.cmInfo.spId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   strmId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "strmId",  &strmId);
   if (strmId != czMsg->u.sctInfo.strmId)
   {
      /* Add validation if requried */
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/*-- czAcHdlSctDatReq --*/

/*
*
*       Fun:   czAcHdlSctStaReq
*
*       Desc:  Handler for SCT Status Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   CmXtaMsgQElm  *msg = NULLP;
   CzAccMsgQElm  *czMsg = NULLP;
   Pst           pst;
   S16           ret;

   TRC2(czAcHdlSctStaReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctStaReq(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctStaReq(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "czAcHdlSctStaReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   
   czMsg = (CzAccMsgQElm *)msg->data;
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTSTAREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
   
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlSctStaReq(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/*-- czAcHdlSctStaReq --*/

/*--
SctBndCfm
SctEndpOpenCfm
SctEndpCloseCfm
SctAssocInd
SctAssocCfm
SctTermInd
SctTermCfm
SctSetPriCfm
SctHBeatCfm
SctDatInd
SctStaCfm
SctStaInd
SctFlcInd
--*/

/*
*
*       Fun:   czAcHdlSctBndCfm
*
*       Desc:  Handler for SCT Bind Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   SctResult     result;

   TRC2(czAcHdlSctBndCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));

   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suid --*/
   suId = CZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   result = CM_BND_OK;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "result",  &(result));
   /* Send the request to S1AP --*/
   DmUiSctBndCfm(&pst, suId, result);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctBndCfm --*/

/*
*
*       Fun:   czAcHdlSctEndpOpenCfm
*
*       Desc:  Handler for End Point Open confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctEndpOpenCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctEndpOpenCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst         pst;
   UConnId     suEndpId;         /* service user endpoint identifier */
   UConnId     spEndpId;         /* service provider endpoint identifier */
   SuId        suId;             /* service user SAP identifier */
   SctResult   result;           /* endpoint open result */
   U16        cause1;            /* cause of failure */

   TRC2(czAcHdlSctEndpOpenCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctEndpOpenCfm(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctEndpOpenCfm(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suId --*/
   suId = CZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   /*-- Set default value & validate for suEndpId --*/
   suEndpId = CZAC_DFLT_SU_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suEndpId",  &(suEndpId));

   /*-- Use the suEndpId value for spEndpId as well, unless overridden by the
        test case. Note that the mapping for suEndpId to spEndpId is not 
        maintained by TA. If required, do that, else use the default logic --*/
   spEndpId = suEndpId;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "spEndpId",  &(spEndpId));

   result = SCT_OK;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "result",  &(result));

   /* Send the request to the S1AP --*/
   cause1 = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "cause",  &(cause1));

   DmUiSctEndpOpenCfm(&pst, suId, suEndpId, spEndpId, result, cause1);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctEndpOpenCfm --*/

/*
*
*       Fun:   czAcHdlSctEndpCloseCfm
*
*       Desc:  Handler for End point Close Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctEndpCloseCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctEndpCloseCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst         pst;
   UConnId     suEndpId = 0;         /* service user endpoint identifier */
   SuId        suId = 0;             /* service user SAP identifier */
   SctResult   result = 0;           /* endpoint open result */
   SctCause    cause = 0;            /* cause of failure */

   TRC2(czAcHdlSctEndpCloseCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctEndpCloseCfm(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctEndpCloseCfm(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suId --*/
   suId = CZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   /*-- Set default value & validate for suEndpId --*/
   suEndpId = CZAC_DFLT_SU_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suEndpId",  &(suEndpId));

   result = SCT_OK;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "result",  &(result));

   /* Send the request to the S1AP --*/
   cause = 0;
   DmUiSctEndpCloseCfm(&pst, suId, suEndpId, result, cause);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctEndpCloseCfm --*/

/*
*
*       Fun:   czAcHdlSctAssocInd
*
*       Desc:  Handler for SCT Association Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctAssocInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctAssocInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst           pst;
   SuId          suId;       
   UConnId       suEndpId;  
   SctAssocIndParams    assocParams;  
   U8            type;               
   CmInetIpAddr     tmpAddr;
   UConnId       suAssocId;      
   U32           assocIdx;
   U8            validate;
   CzAcSctAssocCb   *assocCb;
   U8            numIps;
   U8            i;
   Buffer        *buf;
   Bool           vsInfo;
   Bool           nullParams = FALSE;
   Bool tightCoupled = FALSE;
    S8             ipAddrString[20]= CZAC_LCZ_IPADDR;
       U8             indx;
   ProcId            procId =100;


   TRC2(czAcHdlSctAssocInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctAssocInd(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctAssocInd(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&assocParams, sizeof(SctAssocIndParams));

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suId --*/
   suId = CZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   suEndpId = CZAC_DFLT_SU_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suEndpId",  &(suEndpId));

   type = SCT_ASSOC_IND_INIT;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "type",  &(assocParams.type));

   numIps = CZAC_DFLT_NMB_IPS;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "numIps",  &(numIps));

   suAssocId = 1;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "assocId",  &(suAssocId));
   if (assocParams.type == SCT_ASSOC_IND_INIT)
   {
      /*--    SctInitParams         initParams; --*/
      assocParams.t.initParams.outStrms = CZAC_DFLT_OUT_STRMS;             /* Number of peer outgoing streams */
      assocParams.t.initParams.inStrms = CZAC_DFLT_IN_STRMS;              /* Number of peer incoming streams */
      assocParams.t.initParams.peerPort = CZAC_DFLT_PEER_PORT + 2;             /* SCTP port address of peer */
      assocParams.t.initParams.localPort = CZAC_DFLT_LCL_PORT;            /* Local SCTP port address */

      CZAC_GET_IPADDR(tmpAddr, TRUE);

      assocParams.t.initParams.localAddrLst.nmb = 1;
#ifdef SB_IPV6_SUPPORTED
      assocParams.t.initParams.localAddrLst.nAddr[0].type = CM_TPTADDR_IPV6;
      cmInetPton6(&assocParams.t.initParams.localAddrLst.nAddr[0].u.ipv6NetAddr,
      ipAddrString);
#else /* SB_IPV6_SUPPORTED */
      assocParams.t.initParams.localAddrLst.nAddr[0].type = CM_TPTADDR_IPV4;
      assocParams.t.initParams.localAddrLst.nAddr[0].u.ipv4NetAddr = ntohl(tmpAddr);
#endif /* SB_IPV6_SUPPORTED */

      CZAC_GET_IPADDR(tmpAddr, FALSE);

      assocParams.t.initParams.peerAddrLst.nmb = 1;
#ifdef SB_IPV6_SUPPORTED
      assocParams.t.initParams.peerAddrLst.nAddr[0].type = CM_TPTADDR_IPV6;
      cmInetPton6(&assocParams.t.initParams.peerAddrLst.nAddr[0].u.ipv6NetAddr,
      ipAddrString);
#else /* SB_IPV6_SUPPORTED */
      assocParams.t.initParams.peerAddrLst.nAddr[0].type = CM_TPTADDR_IPV4;
      assocParams.t.initParams.peerAddrLst.nAddr[0].u.ipv4NetAddr = ntohl(tmpAddr);
#endif /* SB_IPV6_SUPPORTED */

#ifndef SB_IPV6_SUPPORTED
      if (numIps > 1)
      {
         /*-- Add more IP's --*/
         for ( i = 1; i < numIps; i++)
         {
            assocParams.t.initParams.peerAddrLst.nmb++;
            assocParams.t.initParams.peerAddrLst.nAddr[assocParams.t.initParams.peerAddrLst.nmb - 1].type = CM_TPTADDR_IPV4;
            assocParams.t.initParams.peerAddrLst.nAddr[assocParams.t.initParams.peerAddrLst.nmb - 1].u.ipv4NetAddr = tmpAddr + i;
         }
      }
#endif /* SB_IPV6_SUPPORTED */
   }
   else
   {
      /*--      SctCookieParams       cookieParams --*/
      CZAC_GET_IPADDR(tmpAddr, FALSE);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "Ipaddr",  &(ipAddrString));
        cmInetAddr(ipAddrString,&tmpAddr);

      
      assocParams.t.cookieParams.peerAddrLst.nmb = 1;
#ifdef SB_IPV6_SUPPORTED
      assocParams.t.cookieParams.peerAddrLst.nAddr[0].type = CM_TPTADDR_IPV6;
      cmInetPton6(&assocParams.t.cookieParams.peerAddrLst.nAddr[0].u.ipv6NetAddr,
      ipAddrString);
#else /* SB_IPV6_SUPPORTED */
      assocParams.t.cookieParams.peerAddrLst.nAddr[0].type = CM_TPTADDR_IPV4;
      assocParams.t.cookieParams.peerAddrLst.nAddr[0].u.ipv4NetAddr = ntohl(tmpAddr);
#endif /* SB_IPV6_SUPPORTED */

#ifndef SB_IPV6_SUPPORTED
      if (numIps > 1)
      {
         /*-- Add more IP's --*/
         for ( i = 1; i < numIps; i++)
         {
            assocParams.t.cookieParams.peerAddrLst.nmb++;
            assocParams.t.cookieParams.peerAddrLst.nAddr[assocParams.t.cookieParams.peerAddrLst.nmb - 1].type = CM_TPTADDR_IPV4;
            assocParams.t.cookieParams.peerAddrLst.nAddr[assocParams.t.cookieParams.peerAddrLst.nmb - 1].u.ipv4NetAddr = tmpAddr + i;
         }
      }
#endif /* SB_IPV6_SUPPORTED */

      assocParams.t.cookieParams.spAssocId = suAssocId;            /* serive provider association ID */
      assocParams.t.cookieParams.suAssocId  = suAssocId;            /* service user association ID */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "procId", &(procId));
   CZ_GET_PEERPROF_INDEX(procId, indx);

#ifdef NOT_USED
      assocParams.t.cookieParams.peerPort = CZAC_DFLT_PEER_PORT+2;             /* SCTP port address of peer */
    assocParams.t.cookieParams.peerPort = czENodeB[indx].protCfg.srcAddr.sctPort;
#endif /* NOT_USED */
      
    assocParams.t.cookieParams.peerPort = czENodeB[indx].peerCfg.assocCfg.dstPort;

   }


   validate = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "validate",  &(validate));

   /*-- Create a new assoc control block --*/
   if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, CZT_CONNID_NOTUSED)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Send the request to the S1AP --*/
   vsInfo = FALSE;
   buf = NULLP;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "vsInfo",  &(vsInfo));

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "nullParams",  &(nullParams));

   if(vsInfo != FALSE)
   {
      /*-- Allocate memory for vsInfo --*/
      SGetMsg(0, 0, (Buffer **) &buf);
   }
   if(nullParams)
      DmUiSctAssocInd (&pst, suId, suEndpId, NULLP, buf);
   else
      DmUiSctAssocInd (&pst, suId, suEndpId, &assocParams, buf);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   RETVALUE(CMXTA_ERR_NONE);


}/*-- czAcHdlSctAssocInd --*/

/*
*
*       Fun:   czAcHdlSctAssocInd1
*
*       Desc:  Handler for SCT Association Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctAssocInd1
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctAssocInd1(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst           pst;
   SuId          suId;       
   UConnId       suEndpId;  
   SctAssocIndParams    assocParams;  
   U8            type;               
   CmInetIpAddr     tmpAddr;
   UConnId       suAssocId;      
   U32           assocIdx;
   U8            validate;
   CzAcSctAssocCb   *assocCb;
   U8            numIps;
   U8            i;
   Buffer        *buf;
   U32           vsInfo;

   TRC2(czAcHdlSctAssocInd1)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctAssocInd1(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctAssocInd1(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&assocParams, sizeof(SctAssocIndParams));

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suId --*/
   suId = CZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   suEndpId = CZAC_DFLT_SU_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suEndpId",  &(suEndpId));

   type = SCT_ASSOC_IND_INIT;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "type",  &(assocParams.type));

   numIps = CZAC_DFLT_NMB_IPS;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "numIps",  &(numIps));

   if (assocParams.type == SCT_ASSOC_IND_INIT)
   {
      /*--    SctInitParams         initParams; --*/
      assocParams.t.initParams.outStrms = CZAC_DFLT_OUT_STRMS;             /* Number of peer outgoing streams */
      assocParams.t.initParams.inStrms = CZAC_DFLT_IN_STRMS;              /* Number of peer incoming streams */
      assocParams.t.initParams.peerPort = CZAC_DFLT_PEER_PORT;             /* SCTP port address of peer */
      assocParams.t.initParams.localPort = CZAC_DFLT_LCL_PORT;            /* Local SCTP port address */

            tmpAddr = CZAC_DFLT_IPADDR1;

      assocParams.t.initParams.localAddrLst.nmb = 1;
#ifdef SB_IPV6_SUPPORTED
      assocParams.t.initParams.localAddrLst.nAddr[0].type = CM_TPTADDR_IPV6;
      cmInetPton6(&assocParams.t.initParams.localAddrLst.nAddr[0].u.ipv6NetAddr, "::1");
#else /* SB_IPV6_SUPPORTED */
      assocParams.t.initParams.localAddrLst.nAddr[0].type = CM_TPTADDR_IPV4;
      assocParams.t.initParams.localAddrLst.nAddr[0].u.ipv4NetAddr = tmpAddr;
#endif /* SB_IPV6_SUPPORTED */
      assocParams.t.initParams.peerAddrLst.nmb = 1;
#ifdef SB_IPV6_SUPPORTED
      assocParams.t.initParams.peerAddrLst.nAddr[0].type = CM_TPTADDR_IPV6;
      cmInetPton6(&assocParams.t.initParams.peerAddrLst.nAddr[0].u.ipv6NetAddr, "::1");
#else /* SB_IPV6_SUPPORTED */
      assocParams.t.initParams.peerAddrLst.nAddr[0].type = CM_TPTADDR_IPV4;
      assocParams.t.initParams.peerAddrLst.nAddr[0].u.ipv4NetAddr = tmpAddr;
#endif /* SB_IPV6_SUPPORTED */

#ifndef SB_IPV6_SUPPORTED
      if (numIps > 1)
      {
         /*-- Add more IP's --*/
         for ( i = 1; i < numIps; i++)
         {
            assocParams.t.initParams.peerAddrLst.nmb++;
            assocParams.t.initParams.peerAddrLst.nAddr[assocParams.t.initParams.peerAddrLst.nmb - 1].type = CM_TPTADDR_IPV4;
            assocParams.t.initParams.peerAddrLst.nAddr[assocParams.t.initParams.peerAddrLst.nmb - 1].u.ipv4NetAddr = tmpAddr + i;
         }
      }
#endif /* SB_IPV6_SUPPORTED */
   }
   else
   {
      /*--      SctCookieParams       cookieParams --*/
            tmpAddr = CZAC_DFLT_IPADDR1;
      assocParams.t.cookieParams.peerAddrLst.nmb = 1;
#ifdef SB_IPV6_SUPPORTED
      assocParams.t.cookieParams.peerAddrLst.nAddr[0].type = CM_TPTADDR_IPV6;
      cmInetPton6(&assocParams.t.cookieParams.peerAddrLst.nAddr[0].u.ipv6NetAddr, "::1");
#else /* SB_IPV6_SUPPORTED */
      assocParams.t.cookieParams.peerAddrLst.nAddr[0].type = CM_TPTADDR_IPV4;
      assocParams.t.cookieParams.peerAddrLst.nAddr[0].u.ipv4NetAddr = tmpAddr;
#endif /* SB_IPV6_SUPPORTED */

#ifndef SB_IPV6_SUPPORTED
      if (numIps > 1)
      {
         /*-- Add more IP's --*/
         for ( i = 1; i < numIps; i++)
         {
            assocParams.t.cookieParams.peerAddrLst.nmb++;
            assocParams.t.cookieParams.peerAddrLst.nAddr[assocParams.t.cookieParams.peerAddrLst.nmb - 1].type = CM_TPTADDR_IPV4;
            assocParams.t.cookieParams.peerAddrLst.nAddr[assocParams.t.cookieParams.peerAddrLst.nmb - 1].u.ipv4NetAddr = tmpAddr + i;
         }
      }
#endif /* SB_IPV6_SUPPORTED */

      assocParams.t.cookieParams.spAssocId = CZAC_DFLT_SP_ASSOCID;            /* serive provider association ID */
      assocParams.t.cookieParams.suAssocId  = CZAC_DFLT_SU_ASSOCID;            /* service user association ID */
      assocParams.t.cookieParams.peerPort = CZAC_DFLT_PEER_PORT;             /* SCTP port address of peer */
   }

   suAssocId = 1;

   validate = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "validate",  &(validate));

   /*-- Create a new assoc control block --*/
   if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, CZT_CONNID_NOTUSED)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* Send the request to the S1AP --*/
   vsInfo = FALSE;
   buf = NULLP;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM, "vsInfo",  &(vsInfo));

   if(vsInfo != FALSE)
   {
      /*-- Allocate memory for vsInfo --*/
      SGetMsg(0, 0, (Buffer **) &buf);
   }
   DmUiSctAssocInd (&pst, suId, suEndpId, &assocParams, buf);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   RETVALUE(CMXTA_ERR_NONE);


}/*-- czAcHdlSctAssocInd --*/

/*
*
*       Fun:   czAcHdlSctAssocCfm
*
*       Desc:  Handler for SCT Association Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctAssocCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctAssocCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst           pst;
   SuId        suId;             /* service user SAP identifier */
   UConnId       suAssocId;      /* service user assoc identifier */
   SctNetAddrLst dstNAddrLst;    /* destination net address list */
   SctPort       dstPort;        /* destination port */
   SctStrmId     inStrms;        /* incoming streams */
#ifdef SCT2
   SctStrmId     outStrms;       /* outgoing streams */
#endif /* SCT2 */
   U32             assocIdx;
   U8             validate;
   CzAcSctAssocCb   *assocCb;
   Buffer         *buf;
   U32            vsInfo;

   TRC2(czAcHdlSctAssocCfm)

   inStrms = CZAC_DFLT_IN_STRMS; 

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctAssocCfm(): tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctAssocCfm(): tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);


   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   CMXTA_ZERO(&dstNAddrLst, sizeof(SctNetAddrLst));
   /*-- Get value for suId --*/
   suId = CZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   /*-- We may come here for two reasons. A new association was opened by S1AP stack, 
        we are trying to send a message for the same. Or else we are trying to pump
        a wrong AssocCfm back to S1AP stack for API sanity purposes. The default mode
        is the validation mode.
        
        For sanity test cases, the TC shall disable the validation --*/

   suAssocId = 0;

   validate = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "validate",  &(validate));

   if (validate == TRUE)
   {
      if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFind(tcCb, assocIdx)) == NULLP)
         RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Create a new assoc control block --*/
   else
   {
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suAssocId",  &(suAssocId));
      if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, CZT_CONNID_NOTUSED)) == NULLP)
         RETVALUE(CMXTA_ERR_RSRC);
   }

   vsInfo = FALSE;
   buf = NULLP;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM, "vsInfo",  &(vsInfo));

   if(vsInfo != FALSE)
   {
      /*-- Allocate memory for vsInfo --*/
      SGetMsg(0, 0, (Buffer **) &buf);
   }

   dstPort = CZAC_DFLT_PEER_PORT;

   /* Send the request to the S1AP --*/
#ifdef SCT2
   DmUiSctAssocCfm (&pst, suId, assocCb->suAssocId,
                    assocCb->spAssocId, &dstNAddrLst, dstPort,
                    inStrms,
                    outStrms, buf);
#else /* SCT2 */
   DmUiSctAssocCfm (&pst, suId, assocCb->suAssocId,
                    assocCb->spAssocId, &dstNAddrLst, dstPort,
                    inStrms,
                     buf);
#endif /* SCT2 */

   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctAssocCfm --*/

/*
*
*       Fun:   czAcHdlSctTermInd
*
*       Desc:  Handler for SCT Term Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctTermInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctTermInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst           pst;
   SuId        suId;             /* service user SAP identifier */
   UConnId       suAssocId;      /* service user assoc identifier */
   U32             assocIdx;
   U8             validate;
   CzAcSctAssocCb   *assocCb;
   SctStatus       status;
   SctCause    cause;            /* cause of failure */
   SctRtrvInfo   rtrvInfo;      /* retrieval information */
   U8             assocIdType;

   TRC2(czAcHdlSctTermInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctTermCfm(): tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctTermCfm(): tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmMemset((U8 *)&rtrvInfo, 0, sizeof(SctRtrvInfo));
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suId --*/
   suId = CZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   /*-- Get value for srcId, dstId, assocIdx and entId --*/
      assocIdx = CZAC_DFLT_ASSOCIDX;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "assocIdx",  &(assocIdx));

   /*-- We may come here for two reasons. We are trying to close an existing 
        association, Or else we are trying to pump a wrong TermInd back to 
        S1AP stack for API sanity purposes. The default mode
        is the validation mode.
        
        For sanity test cases, the TC shall disable the validation --*/

   suAssocId = 2;

   validate = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "validate",  &(validate));

   if (validate == TRUE)
   {
      assocCb = (CzAcSctAssocCb *)czAcSctAssocFind(tcCb, assocIdx);
      if(assocCb == NULLP)
         RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Create a new assoc control block --*/
   else if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, CZT_CONNID_NOTUSED)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   assocIdType = SCT_ENDPID_SU;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "assocIdType",  &(assocIdType));

   /* Send the request to the S1AP --*/
   cause = 0;
   status = SCT_STATUS_COMM_LOST;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "status",  &(status));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "cause",  &(cause));
                      
   if(assocIdType == SCT_ENDPID_SU)
      DmUiSctTermInd (&pst, suId, assocCb->suAssocId, assocIdType, status, cause, &rtrvInfo);
   else
      DmUiSctTermInd (&pst, suId, assocCb->spAssocId, assocIdType, status, cause, &rtrvInfo);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctTermInd --*/

/*
*
*       Fun:   czAcHdlSctTermCfm
*
*       Desc:  Handler for SCT Termination Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctTermCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctTermCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst           pst;
   SuId        suId;             /* service user SAP identifier */
   UConnId       suAssocId;      /* service user assoc identifier */
   U32             assocIdx;
   U8             validate;
   CzAcSctAssocCb   *assocCb;
   SctResult   result;           /* endpoint open result */
   SctCause    cause;            /* cause of failure */

   TRC2(czAcHdlSctTermCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctTermCfm(): tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctTermCfm(): tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suId --*/
   suId = CZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   /*-- Get value for srcId, dstId, assocIdx and entId --*/
      assocIdx = CZAC_DFLT_ASSOCIDX;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "assocIdx",  &(assocIdx));

   /*-- We may come here for two reasons. An association was closed by S1AP stack, 
        we are trying to send a message for the same. Or else we are trying to pump
        a wrong TermCfm back to S1AP stack for API sanity purposes. The default mode
        is the validation mode.
        
        For sanity test cases, the TC shall disable the validation --*/

   suAssocId = 2;

   validate = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "validate",  &(validate));

   if ((validate == TRUE) &&
       ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFind(tcCb, assocIdx)) == NULLP))
      RETVALUE(CMXTA_ERR_INT);
   /*-- Create a new assoc control block --*/
   else if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, CZT_CONNID_NOTUSED)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   result = SCT_OK;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "result",  &(result));

   /* Send the request to the S1AP --*/
   cause = 0;
   DmUiSctTermCfm (&pst, suId, assocCb->suAssocId, result, cause);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctTermCfm --*/

/*
*
*       Fun:   czAcHdlSctSetPriCfm
*
*       Desc:  Handler for SCT Primary Address Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctSetPriCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctSetPriCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst           pst;
   SuId          suId;           /* service user SAP identifier */
   SctResult     result = 0;     /* result */
   SctCause      cause = 0;      /* cause */
   U32           assocIdx=0;
   CzAcSctAssocCb   *assocCb= NULLP;

   TRC2(czAcHdlSctSetPriCfm)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctSetPriCfm(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctSetPriCfm(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   /*-- Find assoc control block --*/
   if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFind(tcCb, assocIdx)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   suId = CZAC_DFLT_SUID;
   DmUiSctSetPriCfm (&pst, suId, assocCb->suAssocId, result, cause);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctSetPriCfm --*/

/*
*
*       Fun:   czAcHdlSctHBeatCfm
*
*       Desc:  Handler for SCT HeartBeat Confirmation 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctHBeatCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctHBeatCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst           pst;
   SuId          suId;           /* service user SAP identifier */
   CmNetAddr     dstNAddr;      /* destination net address */
   SctStatus     status = 0;     /* status */
   SctResult     result = 0;     /* result */
   SctCause      cause = 0;      /* cause */
   U32           assocIdx=0;
   CzAcSctAssocCb   *assocCb= NULLP;

   TRC2(czAcHdlSctHBeatCfm)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctHBeatCfm(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctHBeatCfm(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);

   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   /*-- Find assoc control block --*/
   if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFind(tcCb, assocIdx)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   suId = CZAC_DFLT_SUID;

   DmUiSctHBeatCfm (&pst, suId, assocCb->suAssocId, &dstNAddr, status, result, cause);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctHBeatCfm(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctHBeatCfm(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   RETVALUE(CMXTA_ERR_NONE);


}/*-- czAcHdlSctHBeatCfm --*/

/**
 * @def CONVERT_HEX_STRINT_TO_INT
 *
 * This macro converts char to equivalent int
 *    
 *
 * @param[in]   c   character to be converted
 * @param[out]  c   converted integer
 *
*/
#define CONVERT_HEX_STRING_TO_INT(c) ((c>='0' && c<='9')?(c-'0'):((c>='A' && c<='F')?(c-'A'+10):((c>='a' && c<='f')? (c-'a'+10):0)))

/*
*
*       Fun:   czAcHdlSctDatInd
*
*       Desc:  Handler for Data Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst           pst;
   SuId          suId;           /* service user SAP identifier */
   UConnId       suAssocId;      /* service user assoc identifier */
   SctStrmId     strmId;         /* SCTP stream identifier */
   SctDatIndType indType;       /* data indication type */
   U32           protId;         /* protocol ID */
   S16           mBufNull= FALSE;
   Bool           corruptPdu = FALSE;
   Bool           unknownMsg = FALSE;
   U32           assocIdx=0;
   CzAcSctAssocCb   *assocCb= NULLP;
   S16           ret;
   Buffer       *mBuf;
/*   CztEvnt      *ptrPdu=NULLP;*/
   Mem           mem;
   Data          junk = 35;
   U8        dbgFlag;
   U8        x2apRel = 9;
   CmPAsnErr asnErr;
   Bool          rawBuffer = FALSE;
   Data          flatBuffer[400];

   TRC2(czAcHdlSctDatInd)

   dbgFlag = TRUE;
   asnErr.errCode = 0;

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctDatInd(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctDatInd(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   mBufNull = FALSE;
   suId = CZAC_DFLT_SUID;
   suAssocId = CZAC_DFLT_SU_ASSOCID;
   strmId = 0;
   protId = 0;
   CMXTA_ZERO(&indType, sizeof(SctDatIndType));
   indType.type = SCT_PEER_DAT;

   /* Get the value of assocIdx and stream Id */
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16,"suId",&suId);
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16,"strmId",&strmId);
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U8,"x2apRel",&x2apRel);

   /*-- Find assoc control block --*/
   if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFind(tcCb, assocIdx)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   /* TO DO - Build the S1AP Pdu and encode it and send */
   mem.region = 0;
   mem.pool   = 0;

   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_BOOL,"rawBuffer",&rawBuffer);

   if(rawBuffer != TRUE) 
   {
      if(x2apRel == 9)
      {
         ret = czAcUtlBuildX2APPdu_r9(tcCb, spCb,&mBuf);
         /* pavana commenting this */
         /*
         if (ret == RFAILED)
         CZ_RETVALUE(RFAILED);*/
         /*RETVALUE(CMXTA_ERR_INT);*/
      }
      else
      {

         ret = czAcUtlBuildX2APPdu_r11(tcCb, spCb,&mBuf);
        /* pavana commenting this */
        /*if (ret == RFAILED)
        CZ_RETVALUE(RFAILED);*/
        /*RETVALUE(CMXTA_ERR_INT);*/
      }
#if 0
   ret = czAcUtlBuildX2APPdu(tcCb, spCb, &ptrPdu);
   if (ret == RFAILED)
      RETVALUE(CMXTA_ERR_INT);

 /*  czEdmEncode(&mem, &(ptrPdu->pdu), &mBuf);*/
   ret = cmPAsnEncMsg((TknU8 *)(&(ptrPdu->pdu)), CM_PASN_USE_MBUF, 
                      (Void *)(&mBuf), CZ_PASN_VER_ZERO, 
                      (CmPAsnElmDef **)czMsgDb, &asnErr, 
                      &len, dbgFlag, FALSE );
  
   if (ret == RFAILED)
   {
      /* It's an ASN.1 Error */
      CZ_DBG_ERROR((CZ_PRNT_BUF,
        "Transfer Syntax Error:Encoding failed, Reason %d\n",asnErr.errCode)); 
      
      CZ_FREEMBUF(mBuf);
      CZ_RETVALUE(RFAILED);
  }
#endif


      /* If we need to corrupt the mBuf to simulate decode failure */
      cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_BOOL,"corruptPdu",&corruptPdu);
      if (TRUE == corruptPdu)
      {
         cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_BOOL,"unknownMsg",&unknownMsg);
         if (unknownMsg)
         {
            SAddPreMsgMult(&junk, 1, mBuf);
         }
         {
            SAddPstMsgMult(&junk, 1, mBuf);
         }
      }
   }
   else
   {
      U8 tmpDat[400];  /* to store the converted integer */
      int indexBuffer; /* index for flat buffer */
      int indexTmpDat; /* index for converted integer string */

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "flatBuffer", flatBuffer);

      for(indexBuffer = 0,indexTmpDat = 0 ; flatBuffer[indexBuffer] != '\0' \
          ; indexBuffer += 2, indexTmpDat++)
      {
         tmpDat[indexTmpDat] = ((CONVERT_HEX_STRING_TO_INT(flatBuffer[indexBuffer]) << 4 ) | 
                                (CONVERT_HEX_STRING_TO_INT(flatBuffer[indexBuffer + 1])));
      }

      CMXTA_ALLOCMBUF(&mBuf);
   
      SAddPstMsgMult((Data *)tmpDat ,(indexTmpDat - 1) , mBuf );
   }

   /*CZ_FREEEVNT(ptrPdu);*/

   DmUiSctDatInd (&pst, suId, assocCb->suAssocId, strmId, &indType, protId, mBuf);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctDatInd(), tcId (%ld)\n", tcCb->tcId));
#else  /* ALIGN_64BIT */  
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctDatInd(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */   
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctDatInd --*/

/*
*
*       Fun:   czAcHdlSctStaCfm
*
*       Desc:  Handler for SCT Status Confirmation 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctStaCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst           pst;
   SuId          suId;           /* service user SAP identifier */
   CmNetAddr     dstNAddr;      /* destination network address */
   SctResult     result = 0;    /* result */
   SctCause      cause = 0;     /* cause */
   SctStaInfo    staInfo;       /* status information */
   U32           assocIdx=0;
   CzAcSctAssocCb   *assocCb= NULLP;

   TRC2(czAcHdlSctStaCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctStaCfm(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctStaCfm(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);

   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   /*-- Find assoc control block --*/
   if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFind(tcCb, assocIdx)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   suId = CZAC_DFLT_SUID;
   /* Send the confirmation to the S1AP --*/
   DmUiSctStaCfm (&pst, suId, assocCb->suAssocId, &dstNAddr,
                          result, cause, &staInfo);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */   
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */   
   RETVALUE(CMXTA_ERR_NONE);

}/*-- czAcHdlSctStaCfm --*/

/*
*
*       Fun:   czAcHdlSctStaInd
*
*       Desc:  Handler for SCT Status Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst           pst;
   CzAcSctAssocCb   *assocCb = NULLP;
   U32           assocIdx=0;
   U8            validate;
   UConnId       suAssocId=0;
   SuId          suId;           /* service user SAP identifier */
   UConnId       spAssocId;      /* service provider assoc identifier */
   CmNetAddr     dstNAddr;      /* destination network address */
   SctStatus     status;         /* status */
   SctCause      cause;          /* cause */
   Buffer        *mBuf;          /* message buffer */

   TRC2(czAcHdlSctStaInd)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctStaInd(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctStaInd(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);

   suId = 0;
   suAssocId = 0;
   spAssocId = 0;
   mBuf=NULLP;
   cause =0;
   status = SCT_STATUS_COMM_LOST;

   CMXTA_ZERO(&dstNAddr, sizeof(CmNetAddr));

#ifdef SCT_ENDP_MULTI_IPADDR
   /* Hard coded in tst.c */
   dstNAddr.type = CM_IPV4ADDR_TYPE;
   cmInetAddr(IPADDR_2, &dstNAddr.u.ipv4NetAddr);
#endif /* SCT_ENDP_MULTI_IPADDR*/

   suId = CZAC_DFLT_SUID;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   /*-- We may come here for two reasons. A new association was opened by S1AP stack, 
        we are trying to send a message for the same. Or else we are trying to pump
        a wrong StaInd back to S1AP stack for API sanity purposes. The default mode
        is the validation mode.
        
        For sanity test cases, the TC shall disable the validation --*/

   suAssocId = 0;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suAssocId",  &(suAssocId));

   validate = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "validate",  &(validate));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "assocIdx",  &(assocIdx));

   if (validate == TRUE)
   {
      if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFind(tcCb, assocIdx)) == NULLP)
         RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Create a new assoc control block --*/
   else
   {
      if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, CZT_CONNID_NOTUSED)) == NULLP)
         RETVALUE(CMXTA_ERR_RSRC);

      assocCb->spAssocId = suAssocId;
   }


   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "spAssocId",  &(assocCb->spAssocId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",  &(status));
   /* Send the request to the S1AP --*/

   DmUiSctStaInd (&pst, suId, assocCb->suAssocId, assocCb->spAssocId, &dstNAddr,
                          status, cause, mBuf);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctStaInd(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */   
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctStaInd(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */   
   RETVALUE(CMXTA_ERR_NONE);


}/*-- czAcHdlSctStaInd --*/


/*
*
*       Fun:   czAcHdlSctFlcInd
*
*       Desc:  Handler for SCT Status Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 czAcHdlSctFlcInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else /* ANSI */
PUBLIC S16 czAcHdlSctFlcInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif /* ANSI */
{
   Pst           pst;
   CzAcSctAssocCb   *assocCb = NULLP;
   U32           assocIdx=0;
   U8            validate;
   UConnId       suAssocId=0;
   SuId          suId;           /* service user SAP identifier */
   UConnId       spAssocId;      /* service provider assoc identifier */
   CmNetAddr     dstNAddr;      /* destination network address */
   SctStatus     status;         /* status */
   SctCause      cause;          /* cause */
   Buffer        *mBuf;          /* message buffer */

   TRC2(czAcHdlSctFlcInd)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctFlcInd(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctFlcInd(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTCZ, CMXTA_INST_ID);

   suId = 0;
   suAssocId = 0;
   spAssocId = 0;
   mBuf=NULLP;
   cause =0;
   status = SCT_STATUS_COMM_LOST;

   CMXTA_ZERO(&dstNAddr, sizeof(CmNetAddr));

   suId =0;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   /*-- We may come here for two reasons. A new association was opened by S1AP stack, 
        we are trying to send a message for the same. Or else we are trying to pump
        a wrong FlcInd back to S1AP stack for API sanity purposes. The default mode
        is the validation mode.
        
        For sanity test cases, the TC shall disable the validation --*/

   suAssocId = 0;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suAssocId",  &(suAssocId));

   validate = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "validate",  &(validate));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "assocIdx",  &(assocIdx));

   if (validate == TRUE)
   {
      if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFind(tcCb, assocIdx)) == NULLP)
         RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Create a new assoc control block --*/
   else
   {
      if ((assocCb = (CzAcSctAssocCb *)czAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, CZT_CONNID_NOTUSED)) == NULLP)
         RETVALUE(CMXTA_ERR_RSRC);

      assocCb->spAssocId = suAssocId;
   }


   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "spAssocId",  &(assocCb->spAssocId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",  &(status));
   /* Send the request to the S1AP --*/

   DmUiSctFlcInd (&pst, suId, assocCb->suAssocId,status);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctFlcInd(), tcId (%ld)\n", tcCb->tcId));
#else /* ALIGN_64BIT */   
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlSctFlcInd(), tcId (%d)\n", tcCb->tcId));
#endif /* ALIGN_64BIT */   
   RETVALUE(CMXTA_ERR_NONE);


}/*-- czAcHdlSctFlcInd --*/

#if 0
/*
*
*       Fun:   czAcSctFillCztInfo 
*
*       Desc:  Call handler for Saving Message
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_cztcb.c
*
*/
#ifdef ANSI
PRIVATE S16 czAcSctFillCztInfo
(
CztEvnt      *uiEvnt,
CzAcCztInfo  *cztInfo,
S16           *fsmType
)
#else /* ANSI */
PRIVATE S16 czAcSctFillCztInfo (uiEvnt, cztInfo, fsmType)
CztEvnt      *uiEvnt;
CzAcCztInfo  *cztInfo;
S16           *fsmType;
#endif /* ANSI */
{
   S16 ret = ROK;
   TknU8 *enbId;
   Mem   mem;
   U8             msgType;
   Bool          isResponse;
 
   TRC3(czAcSctFillCztInfo);

   mem.region = 0;
   mem.pool = 0;
 
   /*-- Check if any tapa directives set --*/
 
   /*-- Allocate CZ memory data --*/
    /* Retrieve the X2AP Message type */
   msgType = czUtlGetMsgType(&uiEvnt->pdu, &isResponse, fsmType);


   switch (msgType) 
   {
      /*Please add related to gpind here */
       case CZT_MSG_X2_SETUP:
       case CZT_MSG_RESET:
       case CZT_MSG_CFG_UPD_REQ:
       case CZT_MSG_RSRC_ST_REQ:
       case CZT_MSG_LOAD_IND:
       case CZT_MSG_MOB_CHANGE_REQ:
       case CZT_MSG_RLF_INDICATION:
       case CZT_MSG_HO_REPORT:
       case CZT_MSG_CELL_ACTIVATION_REQ:
      {
         cztInfo->peerId = uiEvnt->peerId;
         cztInfo->msgType = czAcUtlGetMsgType(&(uiEvnt->pdu));
         if(cztInfo->msgType == CZT_MSG_X2_SETUP)
         {
            czUtlGetIE(&(uiEvnt->pdu), Cztid_GlobalENB_ID, &enbId);
            if(enbId != NULLP)
            {
               cztInfo->enbId = ((TknU32 *)enbId)->val;
            }
         }
         if(cztInfo->msgType == CZT_MSG_RESET)
         {
            czAcUtlCztGetErrCause(&(uiEvnt->pdu), &cztInfo->cause.causeType,
               &cztInfo->cause.causeVal);
            
         }
         if(cztInfo->msgType == CZT_MSG_RSRC_ST_REQ ||
            cztInfo->msgType == CZT_MSG_RSRC_ST_UPD)
         {
            czUtlGetIE(&(uiEvnt->pdu), Cztid_ENB1_Measurement_ID, &enbId);
            if(enbId != NULLP)
            {
               cztInfo->u.rsrcInfo.eNb1MeasId = ((TknU32 *)enbId)->val;
            }
            czUtlGetIE(&(uiEvnt->pdu), Cztid_ENB2_Measurement_ID, &enbId);
            if(enbId != NULLP)
            {
               cztInfo->u.rsrcInfo.eNb2MeasId = ((TknU32 *)enbId)->val;
            }
         }
         break;
      }
      /*Add all the cass of GpCfm here */
      case CZT_MSG_X2_SETUP_RSP:
      case CZT_MSG_X2_SETUP_FAIL:
      case CZT_MSG_RESET_RSP:
      case CZT_MSG_CFG_UPD_ACK:
      case CZT_MSG_RSRC_ST_RSP:
      case CZT_MSG_RSRC_ST_FAIL:
      case CZT_MSG_CFG_UPD_FAIL:
      case CZT_MSG_MOB_CHANGE_ACK:
      case CZT_MSG_MOB_CHANGE_FAIL:
      case CZT_MSG_CELL_ACTIVATION_RES:
      case CZT_MSG_CELL_ACTIVATION_FAIL:
      {
         cztInfo->msgType = czAcUtlGetMsgType(&(uiEvnt->pdu));
         if(cztInfo->msgType == CZT_MSG_X2_SETUP_RSP)
         {
/*
            czUtlGetIE(&(uiEvnt->pdu), Cztid_GlobalENB_ID, &enbId);
            if(enbId != NULLP)
            {
               cztInfo->enbId = ((TknU32 *)enbId)->val;
            }
*/
         }
         if(cztInfo->msgType == CZT_MSG_X2_SETUP_FAIL ||
            cztInfo->msgType == CZT_MSG_CFG_UPD_FAIL ||
            cztInfo->msgType == CZT_MSG_MOB_CHANGE_FAIL ||
            cztInfo->msgType == CZT_MSG_CELL_ACTIVATION_FAIL ||
            cztInfo->msgType == CZT_MSG_RSRC_ST_FAIL)
         {
            czAcUtlCztGetErrCause(&(uiEvnt->pdu), &cztInfo->cause.causeType,
               &cztInfo->cause.causeVal);
            czAcUtlCztGetCritDiag(uiEvnt, &cztInfo->crit);
            
         }
         if(cztInfo->msgType == CZT_MSG_RSRC_ST_FAIL)
         {
            czUtlGetIE(&(uiEvnt->pdu), Cztid_ENB1_Measurement_ID, &enbId);
            if(enbId != NULLP)
            {
               cztInfo->u.rsrcInfo.eNb1MeasId = ((TknU32 *)enbId)->val;
            }
            czUtlGetIE(&(uiEvnt->pdu), Cztid_ENB2_Measurement_ID, &enbId);
            if(enbId != NULLP)
            {
               cztInfo->u.rsrcInfo.eNb2MeasId = ((TknU32 *)enbId)->val;
            }
         }
         break;
      }

    case CZT_MSG_HO_REQ: 
    case CZT_MSG_HO_CANCEL: 
    case CZT_MSG_SN_STATUS_TRFR: 
    case CZT_MSG_UE_CXT_RELEASE: 
      {
         cztInfo->peerId = uiEvnt->peerId;
         cztInfo->msgType = czAcUtlGetMsgType(&(uiEvnt->pdu));

         czUtlGetIE(&(uiEvnt->pdu), Cztid_Old_eNB_UE_X2AP_ID, &enbId);
         if(enbId != NULLP)
         {
            cztInfo->u.ueInfo.oldX2APUEId = ((TknU32 *)enbId)->val;
         }
         if(cztInfo->msgType != CZT_MSG_HO_REQ)
         {
           czUtlGetIE(&(uiEvnt->pdu), Cztid_New_eNB_UE_X2AP_ID, &enbId);
           if(enbId != NULLP)
           {
              cztInfo->u.ueInfo.newX2APUEId = ((TknU32 *)enbId)->val;
           }
         }
         if(cztInfo->msgType == CZT_MSG_HO_CANCEL)
         {
            czAcUtlCztGetErrCause(&(uiEvnt->pdu), &cztInfo->cause.causeType,
               &cztInfo->cause.causeVal);
         }
         cztInfo->type.pres = PRSNT_NODEF;
         break;
      }

      case CZT_MSG_HO_ACK: 
      case CZT_MSG_HO_FAIL: 
      {

         cztInfo->peerId = uiEvnt->peerId;

         cztInfo->msgType = czAcUtlGetMsgType(&(uiEvnt->pdu));
         czUtlGetIE(&(uiEvnt->pdu), Cztid_Old_eNB_UE_X2AP_ID, &enbId);
         if(enbId != NULLP)
         {
            cztInfo->u.ueInfo.oldX2APUEId = ((TknU32 *)enbId)->val;
         }
         if(cztInfo->msgType == CZT_MSG_HO_ACK)
         {
           czUtlGetIE(&(uiEvnt->pdu), Cztid_New_eNB_UE_X2AP_ID, &enbId);
           if(enbId != NULLP)
           {
              cztInfo->u.ueInfo.newX2APUEId = ((TknU32 *)enbId)->val;
           }
         }
         if(cztInfo->msgType == CZT_MSG_HO_FAIL)
         {
            czAcUtlCztGetErrCause(&(uiEvnt->pdu), &cztInfo->cause.causeType,
               &cztInfo->cause.causeVal);
            czAcUtlCztGetCritDiag(uiEvnt, &cztInfo->crit);
         }
         
         break;
      }
      case CZT_MSG_ERR_IND:
      {
         cztInfo->msgType = CZT_MSG_ERR_IND; 
         cztInfo->peerId = uiEvnt->peerId;
         czUtlGetIE(&(uiEvnt->pdu), Cztid_Old_eNB_UE_X2AP_ID, &enbId);
         if(enbId != NULLP)
         {
            cztInfo->u.ueInfo.oldX2APUEId = ((TknU32 *)enbId)->val;
         }
         czUtlGetIE(&(uiEvnt->pdu), Cztid_New_eNB_UE_X2AP_ID, &enbId);
         if(enbId != NULLP)
         {
            cztInfo->u.ueInfo.newX2APUEId = ((TknU32 *)enbId)->val;
         }
         czAcUtlCztGetErrCause(&(uiEvnt->pdu), &cztInfo->cause.causeType,
               &cztInfo->cause.causeVal);
         czAcUtlCztGetCritDiag(uiEvnt, &cztInfo->crit);
         break;
      }
      default: 
         CMXTA_DBG_ERR((_cmxtap,
                  "Unknown Meesage Type Failed\n"));
         break;
       
   } /* end of pst->evt */
 
   RETVALUE(ret);
} /* end of czAcCztSaveMsg() */
#endif

#endif /* ifdef DM */
/********************************************************************30**

         End of file:     czac_scthdl.c@@/main/2 - Tue Aug 30 18:35:53 2011

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
/main/1      ---      ng               1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---      pt       1. LTE-X2AP 3.1 release.
/main/3    cz001.301 akaranth  1. Freeing the czMsgVal  memorey in case of Error 
                                  Scenarion
*********************************************************************91*/
