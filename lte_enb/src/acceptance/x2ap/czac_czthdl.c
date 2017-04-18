
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    czac_czthdl.c

     Sid:      czac_czthdl.c@@/main/2 - Tue Aug 30 18:35:45 2011

     Prg:      sy
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

#include "cm_xta.x" 
#include "sct.x"           /* typedefs for STCP */
#include "lcz.x"           /* layer management typedefs for CZCP */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL11;
#include "czac_czt_inf.x"           /* typedefs for CZCP */
#include "cz.x"            /* typedefs for CZCP */
#ifdef SB
#include "lsb.x"           /* SCTP layer managment structures */
#endif /*SB*/
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#include "czac_acc.x"      /* typedefs for CZCP acceptance tests */
#include "czac_czt.x"

PUBLIC CzAcCztPduInfo czacPduInfo[CZAC_MAX_PROCS][CZAC_LCZ_MAX_CONN];
EXTERN CztX2AP_PDU *rstAckPdu;

/* cz001.101 : CR Fixes. */

/*
*
*       Fun:   czAcHdlCztStaInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztStaInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztStaInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   U32  peerId = 0;
   TRC2(czAcHdlCztStaInd);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztStaInd(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztStaInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztStaInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czMsg = (CzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTRS, CMXTA_INST_ID);
 
   pst.event = EVTCZTSTAIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlCztStaInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztStaInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != czMsg->u.cztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, czMsg->u.cztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

   if(peerId != czMsg->u.cztInfo.peerId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#endif
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if ((czMsg->u.cztInfo.type.pres == PRSNT_NODEF) && 
       (czMsg->u.cztInfo.type.val == CZAC_STAIND)) 
   {
      U8 staType = CZT_STA_TYPE_FLC;

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "staType",  &staType);
      if (staType != czMsg->u.cztInfo.u.staInd.type)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : staType mismatch: exp (%d) rcvd (%d) \n",
                         staType, czMsg->u.cztInfo.u.staInd.type), 2);
    
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }

      switch (czMsg->u.cztInfo.u.staInd.type)
      {
         case CZT_STA_TYPE_FLC:
         {
            U8 status =  CZT_STATUS_FLC_STOP;
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "status",  &status);
            if (status != czMsg->u.cztInfo.u.staInd.status)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : status mismatch: exp (%d) rcvd (%d) \n",
                               status, czMsg->u.cztInfo.u.staInd.status), 2);
          
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;

         case CZT_STA_TYPE_ASSOC:
         {
            U8 reason =  CZT_REASON_RCVD_TERMIND;
            U8 status =  CZT_STATUS_ASSOC_DOWN;

            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "reason",  &reason);
            if (reason != czMsg->u.cztInfo.u.staInd.reason)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : reason mismatch: exp (%d) rcvd (%d) \n",
                               reason, czMsg->u.cztInfo.u.staInd.reason), 2);
          
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }

            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "status",  &status);
            if (status != czMsg->u.cztInfo.u.staInd.status)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : status mismatch: exp (%d) rcvd (%d) \n",
                               status, czMsg->u.cztInfo.u.staInd.status), 2);
          
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
         }
         break;
         case CZT_STA_TYPE_TMR_EXPIRY:
         {
            U8 status =  0;
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "status",  &status);
            if (status != czMsg->u.cztInfo.u.staInd.status)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : status mismatch: exp (%d) rcvd (%d) \n",
                               status, czMsg->u.cztInfo.u.staInd.status), 2);
          
               cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
               RETVALUE(CMXTA_ERR_INT);
            }
            break;
         }
         default:
            break;
      }
   }
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* czAcHdlCztStaInd */

/*
*
*       Fun:   czAcHdlCztBndReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlCztBndReq
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 czAcHdlCztBndReq(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif    
{
   Pst           pst;
   SuId          suId = 0;             /* service user SAP identifier */
   SpId          spId = 0;             /* service user SAP identifier */
   
   TRC2(czAcHdlCztBndReq);
   
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztBndReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztBndReq(), tcId (%ld)\n", tcCb->tcId));
#endif
   
   CMXTA_ZERO(&pst, sizeof(Pst));
   
   czAcGetPst(spCb, &pst, ENTRS, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);
   
   pst.event = EVTCZTBNDREQ;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP )
   spId  =CZAC_LCZ_KSCTP_SPID;
#endif  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));
   /* Send the request to the X2AP --*/
   RsLiCztBndReq(&pst, suId, spId);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- czAcHdlCztBndReq --*/

/*
*
*       Fun:   czAcHdlCztBndCfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  mgac_czthdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlCztBndCfm
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb     /* spCb data structure  */
)
#else
PUBLIC S16 czAcHdlCztBndCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
#endif
{
   CmXtaMsgQElm  *msg;
   CzAccMsgQElm  *czMsg;
   Pst           pst;
   S16           ret = ROK;
   SpId          suId;
   Status        status = CM_BND_OK;
 
   TRC2(czAcHdlCztBndCfm);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztBndCfm(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztBndCfm(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   if (ROK != cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg))
   {
      CMXTA_DBG_FATAL((_cmxtap, "czAcHdlCztBndCfm(): cmXtaPeekMsg failed\n"));
      RETVALUE(CMXTA_ERR_FATAL);
   }
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztBndCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czMsg = (CzAccMsgQElm *)msg->data;

   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTRS, CMXTA_INST_ID);

   pst.event = EVTCZTBNDCFM;
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
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztBndCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   suId = 0; /*-- Note suId = spId --*/

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &(suId));

   if (suId != czMsg->u.cztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : SuId MisMatch: exp (%d) rcvd (%d) \n",
                  suId, czMsg->u.cztInfo.cmInfo.suId), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "status",  &(status));
 
   if (status != czMsg->u.cztInfo.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Status MisMatch: exp (%d) rcvd (%d) \n",
                  status, czMsg->u.cztInfo.status), 2);
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
 
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(CMXTA_ERR_NONE);
 
}/*-- czAcHdlCztBndCfm --*/
 
 
 
/*
*
*       Fun:   czAcHdlCztUbndReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  mgac_czthdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlCztUbndReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztUbndReq (tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId;
   Reason         reason;
   TRC2(czAcHdlCztUbndReq);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztUbndReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztUbndReq(), tcId (%ld)\n", tcCb->tcId));
#endif 
   CMXTA_ZERO(&pst, sizeof(Pst));
 
   czAcGetPst(spCb, &pst, ENTRS, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);

   
   pst.event = EVTCZTUBNDREQ;
 
   spId = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP )
   spId  =CZAC_LCZ_KSCTP_SPID;
#endif  
   reason = 0; /*-- Reason is unused --*/
 
   /* Send the request to the GCP --*/
   RsLiCztUbndReq(&pst, spId, reason);
 
   RETVALUE(CMXTA_ERR_NONE);
} /*-- czAcHdlCztUbndReq --*/




/*
*
*       Fun:   czAcHdlCztLclErrInd
*
*       Desc:  Handles X2AP local error indication.
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztLclErrInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztLclErrInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   Pst      pst;
   S16      ret   = ROK;
   U32      peerId = 0;
   U16       errType;
   U16       errCause;
   TRC2(czAcHdlCztLclErrInd);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztLclErrInd(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztLclErrInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztLclErrInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   czMsg = (CzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTRS, CMXTA_INST_ID);

 
 
   pst.event = EVTCZTERRIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlCztLclErrInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztLclErrInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

   if(peerId != czMsg->u.cztInfo.peerId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#endif
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "errType",  &errType);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U16, "errCause",  &errCause);
 
   if (errType != czMsg->u.cztInfo.u.errInd.type ||
       errCause != czMsg->u.cztInfo.u.errInd.value)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : ErrInd mismatch: \
               ERRTYPE( exp (%d) rcvd (%d) ) ERRCAUSE( exp (%d) rcvd (%d) \n",
                errType, czMsg->u.cztInfo.u.errInd.type, errCause,
                czMsg->u.cztInfo.u.errInd.value), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
    
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* czAcHdlCztLclErrInd */


/*
*
*       Fun:   czAcHdlCztLclRelReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztLclRelReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztLclRelReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   CztRlsReq      *rlsReq = NULLP;
   
   TRC2(czAcHdlCztLclRelReq);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztLclRelReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztLclRelReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ALLOC(&rlsReq, sizeof(CztRlsReq));
   
   /* klockwork fix */ 
   if (rlsReq == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztLclRelReq(): rlsReq is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   CMXTA_ZERO(rlsReq, sizeof(CztRlsReq));

   czAcGetPst(spCb, &pst, ENTRS, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);


   pst.event = EVTCZTLOCALRELREQ;
 
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP )
   spId  =CZAC_LCZ_KSCTP_SPID;
#endif  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(rlsReq->peerId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "relType", &(rlsReq->rlsType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "relNodeType", &(rlsReq->idType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "eNb1MeasId",
                                                                  &(rlsReq->u.eNb1MeasId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "oldUEX2APId",
                                                                 &(rlsReq->u.oldUEX2APId));
    


   RsLiCztRelReq(&pst,spId,rlsReq);

   RETVALUE(CMXTA_ERR_NONE);
} /* czAcHdlCztLclRelReq */

/*
*
*       Fun:   czAcHdlCztLclRelCfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztLclRelCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztLclRelCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   ProcId   srcProcId = 0;
   U32      peerId = 0;
   U8       relType = CZT_STA_TYPE_PEER, status = CZT_PRIM_OK, reason = CZT_REASON_NOT_APPL;
   TRC2(czAcHdlCztLclRelCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztLclRelCfm(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztLclRelCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztLclRelCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   czMsg = (CzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTRS, CMXTA_INST_ID);

#if  (defined(CZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   srcProcId   =  czAcGetProc(spCb, ENTCZ, CMXTA_INST_ID);
#endif /* (defined(CZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
 
   pst.event = EVTCZTLOCALRELCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlCztLclRelCfm(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztLclRelCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != czMsg->u.cztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, czMsg->u.cztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

   if(peerId != czMsg->u.cztInfo.peerId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#endif
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "relType",  &relType);
 
   if(relType != czMsg->u.cztInfo.u.rlsCfm.type)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Release confirm mismatch: \
               RELTYPE( exp (%d) rcvd (%d) ) \n",
                relType, czMsg->u.cztInfo.u.staInd.type), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "reason",  &reason);
 
   if(reason != czMsg->u.cztInfo.u.rlsCfm.reason)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Release confirm mismatch: \
               REASON ( exp (%d) rcvd (%d) ) \n",
                reason, czMsg->u.cztInfo.u.staInd.reason), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "status",
         &status);
   if(status != czMsg->u.cztInfo.u.rlsCfm.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Release confirm mismatch: \
               STATUS ( exp (%d) rcvd (%d) ) \n",
                status, czMsg->u.cztInfo.u.staInd.status), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
    
  cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

  RETVALUE(CMXTA_ERR_NONE);
}

/*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztGpReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztGpReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   CztEvnt        *cztEvnt = NULLP;
   Mem            sMem;
   S16            ret = ROK;
   TRC2(czAcHdlCztGpReq);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   czAcGetPst(spCb, &pst, ENTRS, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);

   sMem.region = 0;
   sMem.pool = 0;
 

   pst.event = EVTCZTGPREQ;
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP )
   spId  =CZAC_LCZ_KSCTP_SPID;
#endif  
 
   ret = czAcUtlCztFillGpReqPdu_R11(tcCb, spCb, &cztEvnt);
   if(ret != ROK)
   {
      if(cztEvnt)
         cmFreeMem((Ptr)cztEvnt);
      RETVALUE(CMXTA_ERR_NONE);
   }
   if(cztEvnt)
   {
      cztEvnt->peerId = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(cztEvnt->peerId));
   }
   
    RsLiCztGpReq(&pst, spId, cztEvnt);

   RETVALUE(CMXTA_ERR_NONE);
} /* czAcHdlCztGpReq */

/*
*
*       Fun:   czAcHdlCztGpInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztGpInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztGpInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   ProcId   srcProcId = 0;
   U32 peerId=0;
   TRC2(czAcHdlCztGpInd);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpInd(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztGpInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   czMsg = (CzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTRS, CMXTA_INST_ID);

#if  (defined(CZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   srcProcId   =  czAcGetProc(spCb, ENTCZ, CMXTA_INST_ID);
#endif /* (defined(CZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
 
   pst.event = EVTCZTGPIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlCztGpInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztGpInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != czMsg->u.cztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, czMsg->u.cztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

   if(peerId != czMsg->u.cztInfo.peerId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#endif
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = czAcUtlValidateMsg(tcCb, spCb, czMsg, CZAC_GP);   
   if(ret != ROK)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
      


   /*  Store enbId & mmeId  */
   czacPduInfo[srcProcId][peerId].enbId = 
                                  czMsg->u.cztInfo.enbId;

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* czAcHdlCztGpInd */


/*
*
*       Fun:   czAcHdlCztGpRsp
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztGpRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztGpRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   CztEvnt       *cztEvnt = NULLP;
   Mem            sMem;
   S16           ret = ROK;
   TRC2(czAcHdlCztGpRsp);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpRsp(), tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpRsp(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   czAcGetPst(spCb, &pst, ENTRS, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);


   pst.event = EVTCZTGPRSP;
   
   sMem.region = 0;
   sMem.pool = 0;
 

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP )
   spId  =CZAC_LCZ_KSCTP_SPID;
#endif  

   ret = czAcUtlCztFillGpRspPdu_R11(tcCb, spCb, &cztEvnt);
   if(ret != ROK)
   {
      if(cztEvnt)
         cmFreeMem((Ptr)cztEvnt);
      RETVALUE(CMXTA_ERR_NONE);
   }
   if(cztEvnt)
   {
      cztEvnt->peerId = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(cztEvnt->peerId));
   }
      
   RsLiCztGpRsp(&pst, spId, cztEvnt);

   RETVALUE(CMXTA_ERR_NONE);
} /* czAcHdlCztGpRsp */

/*
*
*       Fun:   czAcHdlCztGpCfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztGpCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztGpCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   ProcId   srcProcId = 0;
   U32 peerId=0;
   TRC2(czAcHdlCztGpCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpCfm(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztGpCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   czMsg = (CzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTRS, CMXTA_INST_ID);

#if  (defined(CZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   srcProcId   =  czAcGetProc(spCb, ENTCZ, CMXTA_INST_ID);
#endif /* (defined(CZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
 
   pst.event = EVTCZTGPCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlCztGpCfm(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztGpCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != czMsg->u.cztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, czMsg->u.cztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

   if(peerId != czMsg->u.cztInfo.peerId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#endif
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = czAcUtlValidateMsg(tcCb, spCb, czMsg, CZAC_GP);   
   if(ret != ROK)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   czacPduInfo[srcProcId][peerId].enbId = 
                                  czMsg->u.cztInfo.enbId;

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* czAcHdlCztGpCfm */

/*
*
*       Fun:   czAcHdlCztGpRetxReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztGpRetxReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztGpRetxReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   Mem            mem;
   CztReTxInfo   *cztReTxInfo = NULLP;
   
   TRC2(czAcHdlCztGpRetxReq);

   mem.region = 0;
   mem.pool = 0;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpRetxReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpRetxReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   czAcGetPst(spCb, &pst, ENTRS, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);

   pst.event = EVTCZTGPRETXREQ;
 
 
   CMXTA_ALLOC(&cztReTxInfo, sizeof(CztReTxInfo));
   
   /* klockwork fix */ 
   if (cztReTxInfo == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztGpRetxReq(): cztReTxInfo is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   CMXTA_ZERO(cztReTxInfo, sizeof(CztReTxInfo));

   cztReTxInfo->u.eNb1MeasId=0;
   cztReTxInfo->msgType=0;
   cztReTxInfo->peerId=0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP )
   spId =CZAC_LCZ_KSCTP_SPID;
#endif  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId",
         &(cztReTxInfo->peerId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType",
         &(cztReTxInfo->msgType));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "eNb1MeasId",
         &(cztReTxInfo->u.eNb1MeasId));
   
   RsLiCztGpRetxReq(&pst, spId, cztReTxInfo);

   RETVALUE(CMXTA_ERR_NONE);
} /* czAcHdlCztGpRetxReq */


/*
*
*       Fun:   czAcHdlCztGpErrReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztGpErrReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztGpErrReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   CztEvnt        *cztEvnt = NULLP;
   Mem           mem;
   S16           ret = ROK;
   
   TRC2(czAcHdlCztGpErrReq);

   mem.region = 0;
   mem.pool = 0;

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpErrReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpErrReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   czAcGetPst(spCb, &pst, ENTRS, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);


   pst.event = EVTCZTGPERRREQ;
 
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP )
   spId  =CZAC_LCZ_KSCTP_SPID;
#endif  

   ret = czAcUtlCztFillErrInd(tcCb, spCb, &cztEvnt);
 
   if(ret != ROK)
   {
      if(cztEvnt)
         cmFreeMem((Ptr)cztEvnt);
      RETVALUE(CMXTA_ERR_NONE);
   }
   if(cztEvnt)
   {
      cztEvnt->peerId = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &(cztEvnt->peerId));
   }

   RsLiCztGpErrReq(&pst, spId, cztEvnt);

   RETVALUE(CMXTA_ERR_NONE);
} /* czAcHdlCztGpErrReq */

/*
*
*       Fun:   czAcHdlCztGpErrInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztGpErrInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztGpErrInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   U32      peerId = 0;
   TRC2(czAcHdlCztGpErrInd);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpErrInd(): tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztGpErrInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztGpErrInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   czMsg = (CzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTRS, CMXTA_INST_ID);
 
   pst.event = EVTCZTGPERRIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlCztGpErrInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztGpErrInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != czMsg->u.cztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, czMsg->u.cztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

   if(peerId != czMsg->u.cztInfo.peerId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#endif
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   ret = czAcUtlValidateMsg(tcCb, spCb, czMsg, CZAC_ERR);   
   if(ret != ROK)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* czAcHdlCztGpErrInd */


/*
*
*       Fun:   czAcHdlCztBmpReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztBmpReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztBmpReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   CztEvnt        *evnt = NULLP;
   S16            ret   = ROK;
   TRC2(czAcHdlCztBmpReq);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztBmpReq(), tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztBmpReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   czAcGetPst(spCb, &pst, ENTRS, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);


   pst.event = EVTCZTBMPREQ;
   
   spId=0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP )
   spId  =CZAC_LCZ_KSCTP_SPID;
#endif  

   ret = czAcUtlCztFillBmpReqPdu_R11(tcCb, spCb, &evnt);
   if(ret != ROK)
   {
      if(evnt)
         cmFreeMem((Ptr)evnt);
      RETVALUE(CMXTA_ERR_NONE);
   }
   if(evnt)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId",  &(evnt->peerId));
   }

   RsLiCztBmpReq(&pst, spId, evnt);

   RETVALUE(CMXTA_ERR_NONE);
} /* czAcHdlCztBmpReq */


/*
*
*       Fun:   czAcHdlCztBmpInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcHdlCztBmpInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztBmpInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   U32      peerId = 0;
   TRC2(czAcHdlCztBmpInd);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztBmpInd(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztBmpInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztBmpInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   czMsg = (CzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTRS, CMXTA_INST_ID);

 
 
   pst.event = EVTCZTBMPIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlCztBmpInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztBmpInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != czMsg->u.cztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, czMsg->u.cztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

   if(peerId != czMsg->u.cztInfo.peerId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#endif
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   ret = czAcUtlValidateMsg(tcCb, spCb, czMsg, CZAC_BMP);   
   if(ret != ROK)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* czAcHdlCztBmpInd */


/*
*
*       Fun:   czAcHdlCztBmpRsp
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztBmpRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztBmpRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   CztEvnt        *evnt = NULLP;
   S16            ret   = ROK;
   
   TRC2(czAcHdlCztBmpRsp);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztBmpRsp(), tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztBmpRsp(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   czAcGetPst(spCb, &pst, ENTRS, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);

   pst.event = EVTCZTBMPRSP;
 

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP )
   spId  =CZAC_LCZ_KSCTP_SPID;
#endif  

   ret = czAcUtlCztFillBmpRspPdu_R11(tcCb, spCb, &evnt);
   if(ret != ROK)
   {
      if(evnt)
         cmFreeMem((Ptr)evnt);
      RETVALUE(CMXTA_ERR_NONE);
   }
   if(evnt)
   {
      evnt->peerId = 0;
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId",  &(evnt->peerId));
   }

   RsLiCztBmpRsp(&pst, spId, evnt);


   RETVALUE(CMXTA_ERR_NONE);
} /* czAcHdlCztBmpRsp */


/*
*
*       Fun:   czAcHdlCztBmpCfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztBmpCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztBmpCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   U32      peerId = 0;
   TRC2(czAcHdlCztBmpCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztBmpCfm(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztBmpCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztBmpCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   czMsg = (CzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTRS, CMXTA_INST_ID);

 
 
   pst.event = EVTCZTBMPCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlCztBmpCfm(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztBmpCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != czMsg->u.cztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, czMsg->u.cztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

   if(peerId != czMsg->u.cztInfo.peerId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#endif
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }
   ret = czAcUtlValidateMsg(tcCb, spCb, czMsg, CZAC_BMP);   
   if(ret != ROK)
   {
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }


   /* TBD: Add code for validation after pdu finalized */

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* czAcHdlCztBmpCfm */


/*
*
*       Fun:   czAcHdlCztPeerAssocInd
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztPeerAssocInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztPeerAssocInd(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   U32      peerId = 0;
   TRC2(czAcHdlCztPeerAssocInd);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztPeerAssocInd(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztPeerAssocInd(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztPeerAssocInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   czMsg = (CzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTRS, CMXTA_INST_ID);
 
   pst.event = EVTCZTPEERASSOCIND;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlCztPeerAssocInd(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztPeerAssocInd(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != czMsg->u.cztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, czMsg->u.cztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

   if(peerId != czMsg->u.cztInfo.peerId)
   {
#ifdef ALIGN_64BIT
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                         peerId, czMsg->u.cztInfo.peerId), 2);
#endif
    
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   /*-- Free memory, use callback function --*/
   cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
 
   RETVALUE(ROK);
}/* czAcHdlCztPeerAssocInd */

/*
*
*       Fun:   czAcHdlCztPeerAssocRsp
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztPeerAssocRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztPeerAssocRsp(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst              pst;
   SpId             spId = 0;
   CztPeerAssocRsp  *assocRsp = NULLP; 
   S8               tmpAddrArr[16];
   U32              tmpAddr;
   U8            testType=0;
   
   TRC2(czAcHdlCztPeerAssocRsp);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztPeerAssocRsp(), tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztPeerAssocRsp(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));

   czAcGetPst(spCb, &pst, ENTRS, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);

   pst.event = EVTCZTPEERASSOCRSP;
   
   CMXTA_ALLOC(&assocRsp, sizeof(CztPeerAssocRsp));
 
   /* klockwork fix */ 
   if (assocRsp == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztPeerAssocRsp(): assocRsp is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));
#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP )
   spId  =CZAC_LCZ_KSCTP_SPID;
#endif  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "testType", &(testType));
 
   if (testType != 1) 
   {

      CMXTA_ZERO(assocRsp, sizeof(CztPeerAssocRsp));

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId",
            &(assocRsp->peerId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "globalStreamId",
            &(assocRsp->globalStreamId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "locOutStrms",
            &(assocRsp->locOutStrms));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "addressType",
            &(assocRsp->priDstAddr.type) );
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "dstPort",
            &(assocRsp->dstPort) );

      cmMemset ((U8 *)tmpAddrArr, 0, 16);
#ifdef SB_IPV6_SUPPORTED
       assocRsp->priDstAddr.type = CM_NETADDR_IPV6;
      strcpy((S8 *)tmpAddrArr, "::1");
#else
      strcpy((S8 *)tmpAddrArr, "127.0.0.1");
#endif
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "address", (tmpAddrArr) );
      if(strcmp(tmpAddrArr,"\0") == 0)
      {
         CMXTA_ZERO(&assocRsp->priDstAddr, sizeof(CmNetAddr));
      }
      else
      {
         if(assocRsp->priDstAddr.type == CM_NETADDR_IPV4)
         {
            cmInetAddr(tmpAddrArr, &tmpAddr);
            assocRsp->priDstAddr.u.ipv4NetAddr = CM_INET_NTOH_U32(tmpAddr);
         }
#ifdef SB_IPV6_SUPPORTED
         else
         {
            cmInetPton6(&assocRsp->priDstAddr.u.ipv6NetAddr,tmpAddrArr);
         }
#endif
      }
      assocRsp->dstAddrLst.nmb = dynamDstAddrLst.nmb;
      cmMemcpy((U8 *)assocRsp->dstAddrLst.nAddr, (U8 *)dynamDstAddrLst.nAddr,
               sizeof(CmNetAddr)*dynamDstAddrLst.nmb);

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "status",
            &(assocRsp->status.status));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "cause",
            &(assocRsp->status.cause));

      RsLiCztDynamPeerAssocRsp(&pst, spId, assocRsp);
   }
   else
   {
     pst.selector = 2;
     RsLiCztDynamPeerAssocRsp(&pst, spId, NULL);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* czAcHdlCztGpRsp */


/*
*
*       Fun:   czAcHdlCztAudReq
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztAudReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztAudReq(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   Pst            pst;
   SpId           spId = 0;
   CztAudEvnt      *audEvnt = NULLP;
   
   TRC2(czAcHdlCztAudReq);

#ifdef ALIGN_64BIT 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztAudReq(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztAudReq(), tcId (%ld)\n", tcCb->tcId));
#endif
 
   /*-- Get the Pst information here from GCP to GCP User --*/
   CMXTA_ZERO(&pst, sizeof(Pst));
   CMXTA_ALLOC(&audEvnt, sizeof(CztAudEvnt));
   
   /* klockwork fix */ 
   if (audEvnt == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztAudReq(): audEvnt is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   CMXTA_ZERO(audEvnt, sizeof(CztAudEvnt));

   czAcGetPst(spCb, &pst, ENTRS, CMXTA_INST_ID, ENTCZ, CMXTA_INST_ID);


   pst.event = EVTCZTAUDREQ;
 
 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "spId",  &(spId));

#ifdef CZAC_LKSCTP
 if(czAccCb.directives.tptType == CZAC_TPT_KSCTP )
   spId  =CZAC_LCZ_KSCTP_SPID;
#endif  

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "audType", &(audEvnt->type));

   if ((audEvnt->type == CZT_AUD_PEER) || 
         (audEvnt->type == CZT_AUD_FLC))
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", 
                       &(audEvnt->u.audPeer.peerId));
   }   


   RsLiCztAudReq(&pst,spId,audEvnt);

   RETVALUE(CMXTA_ERR_NONE);
} /* czAcHdlCztAudReq */

/*
*
*       Fun:   czAcHdlCztAudCfm
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlCztAudCfm
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlCztAudCfm(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   CmXtaMsgQElm   *msg;
   CzAccMsgQElm   *czMsg;
   Pst      pst;
   S16      ret   = ROK;
   SpId     suId;
   ProcId   srcProcId = 0;
   U32      peerId = 0;
   U8       type = CZT_AUD_PEER; 
   U8       status = CZT_PRIM_OK;
   U8       cause = CZT_STACAUSE_NOT_APPL;
   U8       state;
   TRC2(czAcHdlCztAudCfm);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztAudCfm(): tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlCztAudCfm(): tcId (%ld)\n", tcCb->tcId));
#endif
 
   cmXtaPeekMsg(&(tcCb->msgQ[0]), &msg);
 
   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztAudCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   czMsg = (CzAccMsgQElm *)msg->data;

   CMXTA_ZERO(&pst, sizeof(Pst));
   /*-- Validate if this is the msg for this function --*/
   czAcGetPst(spCb, &pst, ENTCZ, CMXTA_INST_ID, ENTRS, CMXTA_INST_ID);

#if  (defined(CZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   srcProcId   =  czAcGetProc(spCb, ENTCZ, CMXTA_INST_ID);
#endif /* (defined(CZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
 
   pst.event = EVTCZTAUDCFM;
   ret = cmXtaValidatePst(&(msg->pst), &pst);
   if (ret != ROK)
   {    
      CMXTA_DBG_INFO((_cmxtap, "czAcHdlCztAudCfm(): No Match, not for this test case\n"));
      RETVALUE(CMXTA_ERR_NOMATCH);
   }    
 
   cmXtaPopMsg (&(tcCb->msgQ[0]), &msg);

   /* klockwork fix */ 
   if (msg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcHdlCztAudCfm(): msg is NULL\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
 
   suId = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_S16, "suId",  &suId);
 
   if (suId != czMsg->u.cztInfo.cmInfo.suId)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : suId mismatch: exp (%d) rcvd (%d) \n",
                      suId, czMsg->u.cztInfo.cmInfo.suId), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "audType",  &type);
 
   if(type != czMsg->u.cztInfo.u.audCfm.type)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Audit confirm mismatch: \
               RELTYPE( exp (%d) rcvd (%d) ) \n",
                type, czMsg->u.cztInfo.u.audCfm.type), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "status",
         &status);
   if(status != czMsg->u.cztInfo.u.audCfm.status)
   {
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : Audit confirm mismatch: \
               STATUS ( exp (%d) rcvd (%d) ) \n",
                status, czMsg->u.cztInfo.u.audCfm.status), 2);
 
      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
      RETVALUE(CMXTA_ERR_INT);
   }

   if(status == CZT_PRIM_NOK)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "cause", &cause);

      if(cause != czMsg->u.cztInfo.u.audCfm.cause)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : Cause mismatch: exp (%d) rcvd (%d) \n",
                  cause, czMsg->u.cztInfo.u.audCfm.cause), 2);

         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }

      cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

      RETVALUE(CMXTA_ERR_NONE);
   }   
    
   if (type == CZT_AUD_PEER)
   {

      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "peerId", &peerId);

      if(peerId != czMsg->u.cztInfo.peerId)
      {
#ifdef ALIGN_64BIT
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%d) rcvd (%d) \n",
                  peerId, czMsg->u.cztInfo.peerId), 2);
#else
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : peerId mismatch: exp (%ld) rcvd (%ld) \n",
                  peerId, czMsg->u.cztInfo.peerId), 2);
#endif
         cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
         RETVALUE(CMXTA_ERR_INT);
      }

      if (status == CZT_PRIM_OK) 
      {
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "state", &state);

         if(state != czMsg->u.cztInfo.u.audCfm.peerState)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : Peer state mismatch: exp (%d) rcvd (%d) \n",
                     state, czMsg->u.cztInfo.u.audCfm.peerState), 2);

            cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);
            RETVALUE(CMXTA_ERR_INT);
         }
      }
               
   }/* if (type == CZT_AUD_PEER) */

  cmXtaFlushMsg (&(tcCb->msgQ[0]), msg);

  RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   czAcHdlDirective
*
*       Desc:
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_czthdl.c
*
*/
 
#ifdef ANSI
PUBLIC S16 czAcHdlDirective
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb
)
#else
PUBLIC S16 czAcHdlDirective(tcCb, spCb)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
#endif
{
   TRC2(czAcHdlDirective);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlDirective(), tcId (%d)\n", tcCb->tcId));
#else 
   CMXTA_DBG_PARAM((_cmxtap, "czAcHdlDirective(), tcId (%ld)\n", tcCb->tcId));
#endif
cmXtaXmlGetVal(NULLP, spCb->curStep, CMXTA_ATTRIB_ENUM_U16, "procId",
      &czAccCb.directives.eNb1ProcId);
RETVALUE(ROK);
}
/********************************************************************30**

         End of file:     czac_czthdl.c@@/main/2 - Tue Aug 30 18:35:45 2011

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
/main/1      ---      aj       1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
