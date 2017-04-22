
/********************************************************************20**

     Name:    S1AP Layer

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    szac_scthdl.c

     Sid:      szac_scthdl.c@@/main/4 - Mon Jan 10 22:15:57 2011

     Prg:     ms

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timers defines        */
#include "cm_hash.h"        /* common hash list             */
#include "cm_inet.h"        /* Inet header file             */
/* sz006.301: Removed un-necessary include files  */
#include "cm_mblk.h"       /* memory management */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"         /* Transport  header file       */
#include "cm_llist.h"      /* common link list */
#include "cm_dns.h"
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timers                */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_tpt.x"         /* Transport  header file       */
#include "cm_llist.x"      /* common link list */
#include "cm_dns.x"
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/


/* S1AP related header file */
#include "cm_xta.h"
#include "szac_acc.h"
#ifdef SB
#include "sb_mtu.h"
#endif /* SB */
#ifdef HI 
#include "lhi.h"
#include "hit.h"
#endif
#include "sct.h"
#include "szac_asn.h"
#include "szt.h"            /* defines and macros for SZ */
#ifdef SB 
#include "lsb.h"            /* SCTP */
#include "sb.h"             /* SCTP */
#endif
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"
#include "sz.h"
#include "cm_pasn.h"
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timers                */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_tpt.x"         /* Transport  header file       */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_llist.x"      /* common link list */
#include "cm_dns.x"
#include"cm_lib.x"        /* common ss7 */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#endif /* SZ_FTHA */

#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/

#include"szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL11;
#ifndef SZ_ENC_DEC
#include "szac_asn_pk.x"
#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */

#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"
/* SCTP Related header files */
#ifdef SB
#include "sb_mtu.x"
#endif /* SB */
#ifdef HI
#include "lhi.x"
#include "hit.x"
#endif
#include "sct.x"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#ifdef SB 
#include "lsb.x"            /* SCTP */
#include "sb.x"             /* SCTP */
#endif
#include "cm_xta.x"
#include "cm_pasn.x"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#endif /* SZ_FTHA */
#include "lsz.x"
#include "szac_acc.x"
#include "szac_sct.x"
#include "sz.x"

/***********************************************************
This files provides the following set of primitives which 
are used when S1AP is not integrated with the Trillium SCTP.
Instead we will be having dummy SCTP
***********************************************************/
/*--
szAcHdlSctBndReq
szAcHdlSctEndpOpenReq
szAcHdlSctEndpCloseReq
szAcHdlSctAssocReq
szAcHdlSctAssocRsp
szAcHdlSctTermReq
szAcHdlSctSetPriReq
szAcHdlSctHBeatReq
szAcHdlSctDatReq
szAcHdlSctStaReq
--*/

#define  SZAC_DFLT_IPADDR1 0xac19005d

/*
*
*       Fun:   szAcHdlSctBndReq
*
*       Desc:  Handler for SCT Bind Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   SzAccMsgQElm  *szMsg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   SpId          spId = 0;

   CMXTA_ZERO(&pst, sizeof(Pst));
   TRC2(szAcHdlSctBndReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctBndReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctBndReq(), tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSctBndReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   szMsg = (SzAccMsgQElm *)msg->data; 

   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTBNDREQ;

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "proc",  &(pst.srcProcId));
#endif /* SZ_FTHA */

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Set default value & validate for spid --*/
   spId = SZAC_DFLT_SPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if (spId != szMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_ERR((_cmxtap, "SpId match failed exp :(%d) recvd (%d) \n", 
                  spId, szMsg->u.sctInfo.cmInfo.spId));
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Flush msg --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctBndReq --*/

/*
*
*       Fun:   szAcHdlSctEndpOpenReq
*
*       Desc:  Handler for SCT Open Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctEndpOpenReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctEndpOpenReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   SzAccMsgQElm  *szMsg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   UConnId       suEndpId = 0;
   SuId          spId = 0;             /* service user SAP identifier */

   CMXTA_ZERO(&pst, sizeof(Pst));
   TRC2(szAcHdlSctEndpOpenReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctEndpOpenReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctEndpOpenReq(), tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSctEndpOpenReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   
      szMsg = (SzAccMsgQElm *)msg->data;

  szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

  /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "proc",  &(pst.srcProcId));
#endif /* SZ_FTHA */

   pst.event = EVTSCTENDPOPENREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Set default value & validate for spid --*/
   spId = SZAC_DFLT_SPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if (spId != szMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId MisMatch: exp (%d) recvd (%d) \n",
                          spId, szMsg->u.sctInfo.cmInfo.spId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for suEndpId --*/
   suEndpId = SZAC_DFLT_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suEndpId",  &(suEndpId));
   if (suEndpId != szMsg->u.sctInfo.suEndpId)
   {
#ifndef ALIGN_64BIT   
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suEndpId MisMatch: exp (%ld) recvd (%ld) \n",
                     suEndpId, szMsg->u.sctInfo.suEndpId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suEndpId MisMatch: exp (%d) recvd (%d) \n",
                     suEndpId, szMsg->u.sctInfo.suEndpId), 2);
#endif
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- This handler does not validate the port and the IP addresses inside the 
        netAddrLst at this moment, if required, enhance this handler to do the 
        validation for the same --*/

   /*-- free memory --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctEndpOpenReq --*/

/*
*
*       Fun:   szAcHdlSctEndpCloseReq
*
*       Desc:  SCT Endpoint Close Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctEndpCloseReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctEndpCloseReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   SzAccMsgQElm  *szMsg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   UConnId       suEndpId = 0;
   U8            endpIdType = 0;
   SuId          spId = 0;             /* service user SAP identifier */

   CMXTA_ZERO(&pst, sizeof(Pst));
   TRC2(szAcHdlSctEndpCloseReq)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctEndpCloseReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctEndpCloseReq(), tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
         CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSctEndpCloseReq(): cmXtaPeekMsg failed\n"));
         RETVALUE(CMXTA_ERR_FATAL);
   }

   szMsg = (SzAccMsgQElm *)msg->data;

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTENDPCLOSEREQ;

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "proc",  &(pst.srcProcId));
#endif /* SZ_FTHA */

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Set default value & validate for spid --*/
   spId = SZAC_DFLT_SPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

   if (spId != szMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId MisMatch: exp (%d) recvd (%d) \n",
                     spId, szMsg->u.sctInfo.cmInfo.spId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for endpIdType --*/
   endpIdType = SCT_ENDPID_SP;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "endpIdType",  &(endpIdType));
   if (endpIdType != szMsg->u.sctInfo.endpIdType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : endpIdType MisMatch: exp (%d) recvd (%d) \n",
                     endpIdType, szMsg->u.sctInfo.endpIdType), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for suEndpId --*/
   suEndpId = SZAC_DFLT_SU_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "spEndpId",  &(suEndpId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suEndpId",  &(suEndpId));
   if (suEndpId != szMsg->u.sctInfo.suEndpId)
   {
#ifndef ALIGN_64BIT   
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suEndpId MisMatch: exp (%ld) recvd (%ld) \n",
                     suEndpId, szMsg->u.sctInfo.suEndpId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suEndpId MisMatch: exp (%d) recvd (%d) \n",
                     suEndpId, szMsg->u.sctInfo.suEndpId), 2);
#endif
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctEndpCloseReq --*/

/*
*
*       Fun:   szAcHdlSctAssocReq
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctAssocReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctAssocReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   SzAccMsgQElm  *szMsg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   UConnId       spEndpId = 0;
   U16           port = 0;
   SuId          spId = 0;             /* service user SAP identifier */
   U32           assocIdx = 0;
   UConnId       suAssocId = 0;

   SzAcSctAssocCb   *assocCb = NULLP;

   CMXTA_ZERO(&pst, sizeof(Pst));
   TRC2(szAcHdlSctAssocReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctAssocReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctAssocReq(), tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSctAssocReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   szMsg = (SzAccMsgQElm *)msg->data;
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTASSOCREQ;

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "proc",  &(pst.srcProcId));
#endif /* SZ_FTHA */

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Set default value & validate for spid --*/
   spId = SZAC_DFLT_SPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != szMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId MisMatch: exp (%d) recvd (%d) \n",
                     spId, szMsg->u.sctInfo.cmInfo.spId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   /*-- Set default value & validate for spEndpId --*/
   spEndpId = SZAC_DFLT_SP_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "spEndpId",  &(spEndpId));

   if (spEndpId != szMsg->u.sctInfo.spEndpId)
   {
#ifndef ALIGN_64BIT   
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spEndpId MisMatch: exp (%ld) recvd (%ld) \n",
                     spEndpId, szMsg->u.sctInfo.spEndpId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spEndpId MisMatch: exp (%d) recvd (%d) \n",
                     spEndpId, szMsg->u.sctInfo.spEndpId), 2);
#endif
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for spEndpId --*/
   port = DFL_PORT; 
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "port",  &(port));

   if (port != szMsg->u.sctInfo.port)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : port MisMatch: exp (%d) recvd (%d) \n",
                     port, szMsg->u.sctInfo.port), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /*-- A new association is being opened by S1AP stack, so there is no validation
        for suAssocId. Create a new assocCb using the suAssocId received from the
        UI interface --*/
   suAssocId = szMsg->u.sctInfo.suAssocId;

   /*-- Create a new assoc control block --*/
   if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, SZT_CONNID_NOTUSED)) == NULLP)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- free memory --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctAssocReq --*/

/*
*
*       Fun:   szAcHdlSctAssocRsp
*
*       Desc:  SCT Association Response
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctAssocRsp
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctAssocRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   SzAccMsgQElm  *szMsg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   SuId          spId = 0;             /* service user SAP identifier */
   U32           assocIdx = 0;
   U8            type = 0;

   SzAcSctAssocCb   *assocCb = NULLP;
   CMXTA_ZERO(&pst, sizeof(Pst));

   TRC2(szAcHdlSctAssocRsp)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctAssocRsp(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctAssocRsp(), tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSctAssocRsp(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   szMsg = (SzAccMsgQElm *)msg->data;
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTASSOCRSP;

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "proc",  &(pst.srcProcId));
#endif /* SZ_FTHA */

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Set default value & validate for spid --*/
   spId = SZAC_DFLT_SPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != szMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId MisMatch: exp (%d) recvd (%d) \n",
                     spId, szMsg->u.sctInfo.cmInfo.spId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- GET value for srcId, dstId, assocIdx and entId --*/
   assocIdx = SZAC_DFLT_ASSOCIDX;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "assocIdx", &(assocIdx));

   /*-- Find assoc control block --*/
   if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFind(tcCb, assocIdx)) == NULLP)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Set default value & validate for AssocRsp Type --*/
   type = SCT_ASSOC_IND_INIT;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "type",  &(type));
   if (type != szMsg->u.sctInfo.assocParams.type)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Assoc Rsp type MisMatch: exp (%d) recvd (%d) \n",
                     type, szMsg->u.sctInfo.assocParams.type), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if (type == SCT_ASSOC_IND_COOKIE)
   {
      /*-- Update the suAssocId in the assocCb --*/
      assocCb->suAssocId = szMsg->u.sctInfo.assocParams.t.cookieParams.suAssocId;
   }
   else
   {
      /*-- Note: here the validation for the spAssocId will not 
          be done as it has not been generated till now --*/
   }

   /*-- free memory --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctAssocRsp --*/

/*
*
*       Fun:   szAcHdlSctTermReq
*
*       Desc:  Termination Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctTermReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctTermReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   SzAccMsgQElm  *szMsg = NULLP;
   Pst           pst;
   S16           ret = ROK;
   U8            validate = 0;
   SuId          spId = 0;             /* service user SAP identifier */
   U32           assocIdx = 0;
   UConnId       suAssocId = 0;
   UConnId       spAssocId = 0;
   U8            assocIdType = 0;

   SzAcSctAssocCb   *assocCb = NULLP;

   TRC2(szAcHdlSctTermReq)

   CMXTA_ZERO(&pst, sizeof(Pst));
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctTermReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctTermReq(), tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSctTermReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   szMsg = (SzAccMsgQElm *) msg->data;
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTTERMREQ;

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "proc",  &(pst.srcProcId));
#endif /* SZ_FTHA */

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /*-- Set default value & validate for spid --*/
   spId = SZAC_DFLT_SPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
   if (spId != szMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId MisMatch: exp (%d) recvd (%d) \n",
                     spId, szMsg->u.sctInfo.cmInfo.spId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- GET value for srcId, dstId, assocIdx and entId --*/
      assocIdx = SZAC_DFLT_ASSOCIDX;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "assocIdx",  &(assocIdx));

   /*-- Set default value & validate for assocIdType --*/
   assocIdType = SCT_ASSOCID_SP;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "assocIdType",  &(assocIdType));
   if (assocIdType != szMsg->u.sctInfo.assocIdType)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : assocIdType MisMatch: exp (%d) recvd (%d) \n",
                     assocIdType, szMsg->u.sctInfo.assocIdType), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   validate = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "validate",  &(validate));

   if (validate == TRUE)
   {
      if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFind(tcCb, assocIdx)) == NULLP)
      {
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   /*-- Create a new assoc control block --*/
   else
   {
      if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFindnCreate(tcCb, assocIdx,
                          szMsg->u.sctInfo.suAssocId, SZT_CONNID_NOTUSED)) == NULLP)
         RETVALUE(CMXTA_ERR_RSRC);
   }
   /*-- Set default value & validate for suAssocId, from TA, suAssocId and 
         spAssocId are the same --*/

   if(SCT_ASSOCID_SU == szMsg->u.sctInfo.assocIdType)
   {
      /*-- Validate suAssocId --*/
      suAssocId = assocCb->suAssocId;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suAssocId",  &(suAssocId));
      if (suAssocId != szMsg->u.sctInfo.suAssocId)
      {
#ifndef ALIGN_64BIT      
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : suAssocId MisMatch: exp (%ld) recvd (%ld) \n",
                  suAssocId, szMsg->u.sctInfo.suAssocId), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : suAssocId MisMatch: exp (%d) recvd (%d) \n",
                  suAssocId, szMsg->u.sctInfo.suAssocId), 2);
#endif
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }
   else
   {
      /*-- Validate spAssocId --*/
      spAssocId = assocCb->spAssocId;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "spAssocId",  &(spAssocId));
      if (spAssocId != szMsg->u.sctInfo.spAssocId)
      {
#ifndef ALIGN_64BIT      
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : spAssocId MisMatch: exp (%ld) recvd (%ld) \n",
                  spAssocId, szMsg->u.sctInfo.spAssocId), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : spAssocId MisMatch: exp (%d) recvd (%d) \n",
                  spAssocId, szMsg->u.sctInfo.spAssocId), 2);
#endif
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   }

   /*-- free memory --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctTermReq --*/


/*
*
*       Fun:   szAcHdlSctSetPriReq
*
*       Desc:  Handler for setting the Primary IP address 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctSetPriReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctSetPriReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   SzAccMsgQElm  *szMsg = NULLP;
   Pst           pst;
   S16           ret;

   TRC2(szAcHdlSctSetPriReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctSetPriReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctSetPriReq(), tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSctSetPriReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
      szMsg = (SzAccMsgQElm *) msg->data;

   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTSETPRIREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/*-- szAcHdlSctSetPriReq --*/


/*
*
*       Fun:   szAcHdlSctHBeatReq
*
*       Desc:  Handler for the HeartBeat Request
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctHBeatReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctHBeatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   SzAccMsgQElm  *szMsg = NULLP;
   Pst           pst;
   S16           ret;

   TRC2(szAcHdlSctHBeatReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctHBeatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctHBeatReq(), tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSctHBeatReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }

   szMsg = (SzAccMsgQElm *)msg->data;

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "proc",  &(pst.srcProcId));
#endif /* SZ_FTHA */

   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTHBEATREQ;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/*-- szAcHdlSctHBeatReq --*/

/*
*
*       Fun:   szAcHdlSctDatReq
*
*       Desc:  Handler for SCT Dat Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctDatReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctDatReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   SzAccMsgQElm  *szMsg = NULLP;
   Pst           pst;
   S16           ret;
   SpId          spId;
   SctStrmId strmId;         /* stream ID */
   U8            eventType;
   U8            choice = 0;
   U32           cause = 0;

   TRC2(szAcHdlSctDatReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctDatReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctDatReq(), tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSctDatReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
      szMsg = (SzAccMsgQElm *)msg->data;

   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTDATREQ;

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "proc",  &(pst.srcProcId));
#endif /* SZ_FTHA */

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType",  &(eventType));

   if(eventType != szMsg->u.sctInfo.type.val)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Event mismatch: exp (%d) rcvd (%d) \n",
               eventType, szMsg->u.sctInfo.type.val), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   spId = SZAC_DFLT_SPID;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &spId);
   if (spId != szMsg->u.sctInfo.cmInfo.spId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : spId mismatch: exp (%d) rcvd (%d) \n",
                          spId, szMsg->u.sctInfo.cmInfo.spId), 2);

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   
   /* Check for error cause type and value for Error msg */
   if(eventType == SZT_MSG_ID_ERR_IND)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "choice", &choice);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "cause", &cause);
      if ((choice != szMsg->u.sctInfo.u.errInd.type) ||
          (cause != szMsg->u.sctInfo.u.errInd.value))
      {
#ifdef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : cause/Type mismatch: cause exp (%d) cause rcvd (%d) "
             "\n choice exp(%d) choice rcvd (%d) \n", cause, szMsg->u.sctInfo.u.errInd.value, 
             choice, szMsg->u.sctInfo.u.errInd.type), 4);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : cause/Type mismatch: cause exp (%ld) cause rcvd (%d) "
             "\n choice exp(%d) choice rcvd (%d) \n", cause, szMsg->u.sctInfo.u.errInd.value, 
             choice, szMsg->u.sctInfo.u.errInd.type), 4);
#endif
    
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }
   } 
   
   strmId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "strmId",  &strmId);
   if (strmId != szMsg->u.sctInfo.strmId)
   {
      /* Add validation if requried */
   }

   /*-- free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/*-- szAcHdlSctDatReq --*/

/*
*
*       Fun:   szAcHdlSctStaReq
*
*       Desc:  Handler for SCT Status Request 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctStaReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctStaReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg = NULLP;
   SzAccMsgQElm  *szMsg = NULLP;
   Pst           pst;
   S16           ret;

   TRC2(szAcHdlSctStaReq)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctStaReq(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctStaReq(), tcId (%d)\n", tcCb->tcId));
#endif
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcHdlSctStaReq(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
   
   szMsg = (SzAccMsgQElm *)msg->data;
   szAcGetPst(spCb, &pst, ENTSZ, CMXTA_INST_ID, ENTSB, CMXTA_INST_ID + 5);

   pst.event = EVTSCTSTAREQ;

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "proc",  &(pst.srcProcId));
#endif /* SZ_FTHA */

   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {
      RETVALUE(CMXTA_ERR_NOMATCH);
   }

   /*-- Remove the msg from the Queue --*/
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
   RETVALUE(CMXTA_ERR_NONE);
}/*-- szAcHdlSctStaReq --*/

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
*       Fun:   szAcHdlSctBndCfm
*
*       Desc:  Handler for SCT Bind Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId          suId;             /* service user SAP identifier */
   SctResult     result;

   TRC2(szAcHdlSctBndCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suid --*/
   suId = SZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   result = CM_BND_OK;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "result",  &(result));

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

   /* Send the request to S1AP --*/
   DmUiSctBndCfm(&pst, suId, result);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctBndCfm --*/

/*
*
*       Fun:   szAcHdlSctEndpOpenCfm
*
*       Desc:  Handler for End Point Open confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctEndpOpenCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctEndpOpenCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst         pst;
   UConnId     suEndpId;         /* service user endpoint identifier */
   UConnId     spEndpId;         /* service provider endpoint identifier */
   SuId        suId;             /* service user SAP identifier */
   SctResult   result;           /* endpoint open result */
   SctCause    cause;            /* cause of failure */

   TRC2(szAcHdlSctEndpOpenCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctEndpOpenCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctEndpOpenCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suId --*/
   suId = SZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   /*-- Set default value & validate for suEndpId --*/
   suEndpId = SZAC_DFLT_SU_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suEndpId",  &(suEndpId));

   /*-- Use the suEndpId value for spEndpId as well, unless overridden by the
        test case. Note that the mapping for suEndpId to spEndpId is not 
        maintained by TA. If required, do that, else use the default logic --*/
   spEndpId = suEndpId;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "spEndpId",  &(spEndpId));

   result = SCT_OK;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "result",  &(result));

   /* Send the request to the S1AP --*/
   cause = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "cause",  &(cause));

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

   DmUiSctEndpOpenCfm(&pst, suId, suEndpId, spEndpId, result, cause);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctEndpOpenCfm --*/

/*
*
*       Fun:   szAcHdlSctEndpCloseCfm
*
*       Desc:  Handler for End point Close Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctEndpCloseCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctEndpCloseCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst         pst;
   UConnId     suEndpId = 0;         /* service user endpoint identifier */
   SuId        suId = 0;             /* service user SAP identifier */
   SctResult   result = 0;           /* endpoint open result */
   SctCause    cause = 0;            /* cause of failure */

   TRC2(szAcHdlSctEndpCloseCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctEndpCloseCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctEndpCloseCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suId --*/
   suId = SZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   /*-- Set default value & validate for suEndpId --*/
   suEndpId = SZAC_DFLT_SU_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suEndpId",  &(suEndpId));

   result = SCT_OK;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "result",  &(result));

   /* Send the request to the S1AP --*/
   cause = 0;

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

   DmUiSctEndpCloseCfm(&pst, suId, suEndpId, result, cause);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctEndpCloseCfm --*/

/*
*
*       Fun:   szAcHdlSctAssocInd
*
*       Desc:  Handler for SCT Association Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctAssocInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctAssocInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
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
   SzAcSctAssocCb   *assocCb;
   U8            numIps;
   U8            i;
   Buffer        *buf;
   Bool           vsInfo;
   Bool           nullParams = FALSE;
   Bool tightCoupled = FALSE;

   TRC2(szAcHdlSctAssocInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctAssocInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctAssocInd(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&assocParams, sizeof(SctAssocIndParams));

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tc",&tightCoupled);

   if(tightCoupled)
   {
      pst.selector = 1;
   }
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suId --*/
   suId = SZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   suEndpId = SZAC_DFLT_SU_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suEndpId",  &(suEndpId));

   type = SCT_ASSOC_IND_INIT;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "type",  &(assocParams.type));

   numIps = SZAC_DFLT_NMB_IPS;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "numIps",  &(numIps));

   suAssocId = 1;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "assocId",  &(suAssocId));
   if (assocParams.type == SCT_ASSOC_IND_INIT)
   {
      /*--    SctInitParams         initParams; --*/
      assocParams.t.initParams.outStrms = SZAC_DFLT_OUT_STRMS;             /* Number of peer outgoing streams */
      assocParams.t.initParams.inStrms = SZAC_DFLT_IN_STRMS;              /* Number of peer incoming streams */
      /* sz002.201: Fixed test case for performance fix */
      assocParams.t.initParams.peerPort = SZAC_LSZ_ENB_SCTPORT;             /* SCTP port address of peer */
      assocParams.t.initParams.localPort = SZAC_LSZ_MME_SCTPORT;            /* Local SCTP port address */

      SZAC_GET_IPADDR(tmpAddr, TRUE);

      assocParams.t.initParams.localAddrLst.nmb = 1;
      assocParams.t.initParams.localAddrLst.nAddr[0].type = CM_TPTADDR_IPV4;
      assocParams.t.initParams.localAddrLst.nAddr[0].u.ipv4NetAddr = ntohl(tmpAddr);

      SZAC_GET_IPADDR(tmpAddr, FALSE);

      assocParams.t.initParams.peerAddrLst.nmb = 1;
      assocParams.t.initParams.peerAddrLst.nAddr[0].type = CM_TPTADDR_IPV4;
      assocParams.t.initParams.peerAddrLst.nAddr[0].u.ipv4NetAddr = ntohl(tmpAddr);

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
   }
   else
   {
      /*--      SctCookieParams       cookieParams --*/
      SZAC_GET_IPADDR(tmpAddr, FALSE);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "Ipaddr",  &(tmpAddr));
      assocParams.t.cookieParams.peerAddrLst.nmb = 1;
      assocParams.t.cookieParams.peerAddrLst.nAddr[0].type = CM_TPTADDR_IPV4;
      assocParams.t.cookieParams.peerAddrLst.nAddr[0].u.ipv4NetAddr = ntohl(tmpAddr);

      /* sz005.301: Updated for S1AP to use the negotiated streams from SCTP*/
#ifdef SCT6
      assocParams.t.cookieParams.outStrms = SZAC_DFLT_OUT_STRMS;             /* Number of peer outgoing streams */
      assocParams.t.cookieParams.inStrms = SZAC_DFLT_IN_STRMS;              /* Number of peer incoming streams */
#endif

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

      assocParams.t.cookieParams.spAssocId = suAssocId;            /* serive provider association ID */
      assocParams.t.cookieParams.suAssocId  = suAssocId;            /* service user association ID */

      /* sz002.201: Fixed test case for performance fix */
      assocParams.t.cookieParams.peerPort = SZAC_LSZ_ENB_SCTPORT;             /* SCTP port address of peer */
   }


   validate = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "validate",  &(validate));

   /*-- Create a new assoc control block --*/
   if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, SZT_CONNID_NOTUSED)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

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
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   RETVALUE(CMXTA_ERR_NONE);


}/*-- szAcHdlSctAssocInd --*/

/*
*
*       Fun:   szAcHdlSctAssocInd1
*
*       Desc:  Handler for SCT Association Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctAssocInd1
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctAssocInd1(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
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
   SzAcSctAssocCb   *assocCb;
   U8            numIps;
   U8            i;
   Buffer        *buf;
   U32           vsInfo;

   TRC2(szAcHdlSctAssocInd1)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctAssocInd1(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctAssocInd1(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ZERO(&assocParams, sizeof(SctAssocIndParams));

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suId --*/
   suId = SZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   cmXtaXmlGetVal(NULLP,spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   suEndpId = SZAC_DFLT_SU_ENDPID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "suEndpId",  &(suEndpId));

   type = SCT_ASSOC_IND_INIT;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "type",  &(assocParams.type));

   numIps = SZAC_DFLT_NMB_IPS;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "numIps",  &(numIps));

   if (assocParams.type == SCT_ASSOC_IND_INIT)
   {
      /*--    SctInitParams         initParams; --*/
      assocParams.t.initParams.outStrms = SZAC_DFLT_OUT_STRMS;             /* Number of peer outgoing streams */
      assocParams.t.initParams.inStrms = SZAC_DFLT_IN_STRMS;              /* Number of peer incoming streams */
      assocParams.t.initParams.peerPort = SZAC_DFLT_PEER_PORT;             /* SCTP port address of peer */
      assocParams.t.initParams.localPort = SZAC_DFLT_LCL_PORT;            /* Local SCTP port address */

            tmpAddr = SZAC_DFLT_IPADDR1;

      assocParams.t.initParams.localAddrLst.nmb = 1;
      assocParams.t.initParams.localAddrLst.nAddr[0].type = CM_TPTADDR_IPV4;
      assocParams.t.initParams.localAddrLst.nAddr[0].u.ipv4NetAddr = tmpAddr;

      assocParams.t.initParams.peerAddrLst.nmb = 1;
      assocParams.t.initParams.peerAddrLst.nAddr[0].type = CM_TPTADDR_IPV4;
      assocParams.t.initParams.peerAddrLst.nAddr[0].u.ipv4NetAddr = tmpAddr;

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
   }
   else
   {
      /*--      SctCookieParams       cookieParams --*/
            tmpAddr = SZAC_DFLT_IPADDR1;
      assocParams.t.cookieParams.peerAddrLst.nmb = 1;
      assocParams.t.cookieParams.peerAddrLst.nAddr[0].type = CM_TPTADDR_IPV4;
      assocParams.t.cookieParams.peerAddrLst.nAddr[0].u.ipv4NetAddr = tmpAddr;

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

      assocParams.t.cookieParams.spAssocId = SZAC_DFLT_SP_ASSOCID;            /* serive provider association ID */
      assocParams.t.cookieParams.suAssocId  = SZAC_DFLT_SU_ASSOCID;            /* service user association ID */
      assocParams.t.cookieParams.peerPort = SZAC_DFLT_PEER_PORT;             /* SCTP port address of peer */
   }

   suAssocId = 1;

   validate = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "validate",  &(validate));

   /*-- Create a new assoc control block --*/
   if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, SZT_CONNID_NOTUSED)) == NULLP)
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
   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

   DmUiSctAssocInd (&pst, suId, suEndpId, &assocParams, buf);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   RETVALUE(CMXTA_ERR_NONE);


}/*-- szAcHdlSctAssocInd --*/

/*
*
*       Fun:   szAcHdlSctAssocCfm
*
*       Desc:  Handler for SCT Association Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctAssocCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctAssocCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId        suId;             /* service user SAP identifier */
   UConnId       suAssocId;      /* service user assoc identifier */
   SctNetAddrLst dstNAddrLst;    /* destination net address list */
   SctPort       dstPort;        /* destination port */
   SctStrmId     inStrms;        /* incoming streams */
#ifdef SCT2
   SctStrmId     outStrms;       /* outgoing streams */
#endif
   U32             assocIdx;
   U8             validate;
   SzAcSctAssocCb   *assocCb;
   Buffer         *buf;
   U32            vsInfo;

   TRC2(szAcHdlSctAssocCfm)

   inStrms = SZAC_DFLT_IN_STRMS; 

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctAssocCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctAssocCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);


   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   CMXTA_ZERO(&dstNAddrLst, sizeof(SctNetAddrLst));
   /*-- Get value for suId --*/
   suId = SZAC_DFLT_SUID;
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
      if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFind(tcCb, assocIdx)) == NULLP)
         RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Create a new assoc control block --*/
   else
   {
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suAssocId",  &(suAssocId));
      if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, SZT_CONNID_NOTUSED)) == NULLP)
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

   /* sz002.201: Fixed test case for performance fix */
   dstPort = SZAC_LSZ_MME_SCTPORT;

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

   /* Send the request to the S1AP --*/
#ifdef SCT2
   DmUiSctAssocCfm (&pst, suId, assocCb->suAssocId,
                    assocCb->spAssocId, &dstNAddrLst, dstPort,
                    inStrms,
                    outStrms, buf);
#else
   DmUiSctAssocCfm (&pst, suId, assocCb->suAssocId,
                    assocCb->spAssocId, &dstNAddrLst, dstPort,
                    inStrms,
                     buf);
#endif

   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctAssocCfm --*/

/*
*
*       Fun:   szAcHdlSctTermInd
*
*       Desc:  Handler for SCT Term Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctTermInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctTermInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId        suId;             /* service user SAP identifier */
   UConnId       suAssocId;      /* service user assoc identifier */
   U32             assocIdx;
   U8             validate;
   SzAcSctAssocCb   *assocCb;
   SctStatus       status;
   SctCause    cause;            /* cause of failure */
   SctRtrvInfo   rtrvInfo;      /* retrieval information */
   U8             assocIdType;

   TRC2(szAcHdlSctTermInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctTermCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctTermCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   cmMemset((U8 *)&rtrvInfo, 0, sizeof(SctRtrvInfo));
   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suId --*/
   suId = SZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   /*-- Get value for srcId, dstId, assocIdx and entId --*/
      assocIdx = SZAC_DFLT_ASSOCIDX;
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
      assocCb = (SzAcSctAssocCb *)szAcSctAssocFind(tcCb, assocIdx);
      if(assocCb == NULLP)
         RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Create a new assoc control block --*/
   else if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, SZT_CONNID_NOTUSED)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   assocIdType = SCT_ENDPID_SU;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "assocIdType",  &(assocIdType));

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

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

}/*-- szAcHdlSctTermInd --*/

/*
*
*       Fun:   szAcHdlSctTermCfm
*
*       Desc:  Handler for SCT Termination Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctTermCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctTermCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId        suId;             /* service user SAP identifier */
   UConnId       suAssocId;      /* service user assoc identifier */
   U32             assocIdx;
   U8             validate;
   SzAcSctAssocCb   *assocCb;
   SctResult   result;           /* endpoint open result */
   SctCause    cause;            /* cause of failure */

   TRC2(szAcHdlSctTermCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctTermCfm(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctTermCfm(): tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   /*-- Get value for suId --*/
   suId = SZAC_DFLT_SUID;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   /*-- Get value for srcId, dstId, assocIdx and entId --*/
      assocIdx = SZAC_DFLT_ASSOCIDX;
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
       ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFind(tcCb, assocIdx)) == NULLP))
      RETVALUE(CMXTA_ERR_INT);
   /*-- Create a new assoc control block --*/
   else if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, SZT_CONNID_NOTUSED)) == NULLP)
      RETVALUE(CMXTA_ERR_RSRC);

   result = SCT_OK;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "result",  &(result));

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

   /* Send the request to the S1AP --*/
   cause = 0;
   DmUiSctTermCfm (&pst, suId, assocCb->suAssocId, result, cause);
   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctTermCfm --*/

/*
*
*       Fun:   szAcHdlSctSetPriCfm
*
*       Desc:  Handler for SCT Primary Address Confirm 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctSetPriCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctSetPriCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId          suId;           /* service user SAP identifier */
   SctResult     result = 0;     /* result */
   SctCause      cause = 0;      /* cause */
   U32           assocIdx=0;
   SzAcSctAssocCb   *assocCb= NULLP;

   TRC2(szAcHdlSctSetPriCfm)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctSetPriCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctSetPriCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   /*-- Find assoc control block --*/
   if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFind(tcCb, assocIdx)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

   suId = SZAC_DFLT_SUID;
   DmUiSctSetPriCfm (&pst, suId, assocCb->suAssocId, result, cause);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctSetPriCfm --*/

/*
*
*       Fun:   szAcHdlSctHBeatCfm
*
*       Desc:  Handler for SCT HeartBeat Confirmation 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctHBeatCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctHBeatCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId          suId;           /* service user SAP identifier */
   CmNetAddr     dstNAddr;      /* destination net address */
   SctStatus     status = 0;     /* status */
   SctResult     result = 0;     /* result */
   SctCause      cause = 0;      /* cause */
   U32           assocIdx=0;
   SzAcSctAssocCb   *assocCb= NULLP;

   TRC2(szAcHdlSctHBeatCfm)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctHBeatCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctHBeatCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);

   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   /*-- Find assoc control block --*/
   if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFind(tcCb, assocIdx)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   suId = SZAC_DFLT_SUID;

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

   DmUiSctHBeatCfm (&pst, suId, assocCb->suAssocId, &dstNAddr, status, result, cause);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctHBeatCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctHBeatCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   RETVALUE(CMXTA_ERR_NONE);


}/*-- szAcHdlSctHBeatCfm --*/

/*
*
*       Fun:   szAcHdlSctDatInd
*
*       Desc:  Handler for Data Indication
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctDatInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctDatInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId          suId;           /* service user SAP identifier */
   UConnId       suAssocId;      /* service user assoc identifier */
   SctStrmId     strmId;         /* SCTP stream identifier */
   SctDatIndType indType;       /* data indication type */
   U32           protId;         /* protocol ID */
   S16           mBufNull= FALSE;
   U32           assocIdx=0;
   SzAcSctAssocCb   *assocCb= NULLP;
   S16           ret;
   Buffer       *mBuf;
   U8 relType = 9; 
   /*S1apPdu      *ptrPdu=NULLP;*/
   /*Mem           mem;*/

   TRC2(szAcHdlSctDatInd)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctDatInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctDatInd(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);

   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   mBufNull = FALSE;
   suId = SZAC_DFLT_SUID;
   suAssocId = SZAC_DFLT_SU_ASSOCID;
   strmId = 0;
   protId = 0;
   CMXTA_ZERO(&indType, sizeof(SctDatIndType));
   indType.type = SCT_PEER_DAT;

   /* Get the value of assocIdx and stream Id */
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16,"suId",&suId);
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16,"strmId",&strmId);

   /*-- Find assoc control block --*/
   if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFind(tcCb, assocIdx)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   /* TO DO - Build the S1AP Pdu and encode it and send */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "relType", &(relType));
   printf("\n\n Release Type : %d\n\n", relType);
   if (relType == 9)
   {
       ret = szAcUtlBuildS1APPdu_r9(tcCb, spCb, &mBuf); /*Create ptrPdu in szAcUtlBuildS1APPdu_r9*/
   }
   else
   {
       ret = szAcUtlBuildS1APPdu_r11(tcCb, spCb, &mBuf);

   }

   if (ret == RFAILED)
      RETVALUE(CMXTA_ERR_INT);


   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

   DmUiSctDatInd (&pst, suId, assocCb->suAssocId, strmId, &indType, protId, mBuf);

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctDatInd(), tcId (%ld)\n", tcCb->tcId));
#else   
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctDatInd(), tcId (%d)\n", tcCb->tcId));
#endif   
   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctDatInd --*/

/*
*
*       Fun:   szAcHdlSctStaCfm
*
*       Desc:  Handler for SCT Status Confirmation 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctStaCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctStaCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SuId          suId;           /* service user SAP identifier */
   CmNetAddr     dstNAddr;      /* destination network address */
   SctResult     result = 0;    /* result */
   SctCause      cause = 0;     /* cause */
   SctStaInfo    staInfo;       /* status information */
   U32           assocIdx=0;
   SzAcSctAssocCb   *assocCb= NULLP;

   TRC2(szAcHdlSctStaCfm)

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctStaCfm(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctStaCfm(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);

   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   /*-- Find assoc control block --*/
   if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFind(tcCb, assocIdx)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   suId = SZAC_DFLT_SUID;
   /* Send the confirmation to the S1AP --*/
   DmUiSctStaCfm (&pst, suId, assocCb->suAssocId, &dstNAddr,
                          result, cause, &staInfo);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctBndCfm(), tcId (%ld)\n", tcCb->tcId));
#else   
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctBndCfm(), tcId (%d)\n", tcCb->tcId));
#endif   
   RETVALUE(CMXTA_ERR_NONE);

}/*-- szAcHdlSctStaCfm --*/

/*
*
*       Fun:   szAcHdlSctStaInd
*
*       Desc:  Handler for SCT Status Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctStaInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst           pst;
   SzAcSctAssocCb   *assocCb = NULLP;
   U32           assocIdx=0;
   U8            validate;
   UConnId       suAssocId=0;
   SuId          suId;           /* service user SAP identifier */
   UConnId       spAssocId;      /* service provider assoc identifier */
   CmNetAddr     dstNAddr;      /* destination network address */
   SctStatus     status;         /* status */
   SctCause      cause;          /* cause */
   Buffer        *mBuf;          /* message buffer */

   TRC2(szAcHdlSctStaInd)
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctStaInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctStaInd(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);

   suId = 0;
   suAssocId = 0;
   spAssocId = 0;
   mBuf=NULLP;
   cause =0;
   status = SCT_STATUS_COMM_LOST;

   CMXTA_ZERO(&dstNAddr, sizeof(CmNetAddr));

   suId = SZAC_DFLT_SUID;

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
      if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFind(tcCb, assocIdx)) == NULLP)
         RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Create a new assoc control block --*/
   else
   {
      if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFindnCreate(tcCb, assocIdx, suAssocId, SZT_CONNID_NOTUSED)) == NULLP)
         RETVALUE(CMXTA_ERR_RSRC);

      assocCb->spAssocId = suAssocId;
   }


   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "spAssocId",  &(assocCb->spAssocId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "status",  &(status));
   /* Send the request to the S1AP --*/

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

   DmUiSctStaInd (&pst, suId, assocCb->suAssocId, assocCb->spAssocId, &dstNAddr,
                          status, cause, mBuf);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctStaInd(), tcId (%ld)\n", tcCb->tcId));
#else   
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctStaInd(), tcId (%d)\n", tcCb->tcId));
#endif   
   RETVALUE(CMXTA_ERR_NONE);


}/*-- szAcHdlSctStaInd --*/

/*
*
*       Fun:   szAcHdlSctFlcInd
*
*       Desc:  Handler for SCT Flow Indication 
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_scthdl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcHdlSctFlcInd
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 szAcHdlSctFlcInd(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   Pst        pst;
   SuId       suId;              /* service user SAP identifier */
   UConnId    suAssocId;         /* service user association ID */
   Reason     reason;            /* reason for flow control indication */
   U32        assocIdx=0;
   SzAcSctAssocCb   *assocCb= NULLP;

   TRC2(szAcHdlSctFlcInd)


#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctFlcInd(), tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctFlcInd(), tcId (%d)\n", tcCb->tcId));
#endif
   CMXTA_ZERO(&pst, sizeof(Pst));

   /*-- Validate if this is the msg for this function --*/
   szAcGetPst(spCb, &pst, ENTSB, CMXTA_INST_ID + 5, ENTSZ, CMXTA_INST_ID);

   suId = SZAC_DFLT_SUID;
   reason = SCT_FLC_ACTIVE;
   /*-- Use Python wrapper APIs to extract the parameters which can be changed
        using XML --*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "suAssocId",  &(suAssocId));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "reason",  &(reason));

   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U32,"assocIdx",&assocIdx);

   /*-- Find assoc control block --*/
   if ((assocCb = (SzAcSctAssocCb *)szAcSctAssocFind(tcCb, assocIdx)) == NULLP)
   {
      RETVALUE(CMXTA_ERR_INT);
   }

   /* sz003.301: Updted for PSF-S1AP 3.1 release */
#ifdef SZ_FTHA
   pst.route = RTE_PROTO;
#endif /* SZ_FTHA */

   /* Send the request to the S1AP --*/
   DmUiSctFlcInd (&pst, suId, assocCb->suAssocId, reason);
#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctFlcInd(), tcId (%ld)\n", tcCb->tcId));
#else   
   CMXTA_DBG_PARAM((_cmxtap, "szAcHdlSctFlcInd(), tcId (%d)\n", tcCb->tcId));
#endif   
   RETVALUE(CMXTA_ERR_NONE);
}/*-- szAcHdlSctFlcInd --*/

/********************************************************************30**

         End of file:     szac_scthdl.c@@/main/4 - Mon Jan 10 22:15:57 2011

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
/main/4   sz005.301   va          1. Updated for S1AP to use the 
                                     negotiated streams from SCTP
/main/4   sz006.301   ve          1. Removed un-necessary include files
/main/4   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
