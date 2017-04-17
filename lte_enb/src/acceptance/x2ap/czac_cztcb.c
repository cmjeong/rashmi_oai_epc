
/********************************************************************20**

     Name:    CZT - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    czac_cztcb.c

     Sid:      czac_cztcb.c@@/main/2 - Tue Aug 30 18:35:44 2011
     Prg:    aj
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
#include "cm_pasn.h"       /* Common Asn.1 library           */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "cz.h"            /* defines and macros for CZ */
#include "lcz.h"            /* defines and macros for CZ */
#include "sct.h"            /* defines and macros for CZ */
#include "czt.h"            /* defines and macros for CZ */
#include "czt_asn.h"        /* defines and macros for CZ ASN */
#include "cz_err.h"         /* CZ error defines */
#include "czac_acc.h"       /* defines for CZ acceptance tests */
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
#include "cm_pasn.x"       /* Common Asn.1 library           */
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


PUBLIC CztX2AP_PDU *rstAckPdu;


PUBLIC CztNetAddrLst dynamDstAddrLst;

/* cz001.101 : CR Fixes. */

/*
*
*       Fun:   RsLiCztBndCfm
*       
*       Desc:  Call handler for Bind Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  czac_cztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RsLiCztBndCfm
(
Pst            *pst,
SuId           suId,
U8             status
)
#else
PUBLIC S16 RsLiCztBndCfm(pst, suId, status)
Pst            *pst;
SuId           suId;
U8             status;
#endif
{
   TRC2(RsLiCztBndCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "RsLiCztBndCfm():\n"));

   pst->event = EVTCZTBNDCFM;
 
   czAcCztSendMsg(pst, suId, status, NULLP);    

   RETVALUE(ROK);
} /* End of RsLiCztBndCfm */


/*
*
*       Fun:   RsLiCztGpInd
*
*       Desc:  Call handler for Release Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  czac_cztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RsLiCztGpInd
(
Pst            *pst,
SuId           suId,
CztEvnt      *cztInd
)
#else
PUBLIC S16 RsLiCztGpInd(pst, suId, cztInd)
Pst            *pst;
SuId           suId;
CztEvnt      *cztInd;
#endif /* ANSI */
{
   TRC2(RsLiCztGpInd);
   
   CMXTA_DBG_PARAM((_cmxtap, "RsLiCztGpInd():\n"));
  
   pst->event = EVTCZTGPIND;
 
   czAcCztSendMsg(pst, suId, 0, cztInd);

   CZ_FREEEVNT(cztInd);

   RETVALUE(ROK);
} /* End of RsLiCztGpInd */


/*
*
*       Fun:   RsLiCztGpCfm
*
*       Desc:  Call handler for Release Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  czac_cztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RsLiCztGpCfm
(
Pst            *pst,
SuId           suId,
CztEvnt      *cztCfm
)
#else
PUBLIC S16 RsLiCztGpCfm(pst, suId, cztCfm)
Pst            *pst;
SuId           suId;
CztEvnt      *cztCfm;
#endif /* ANSI */
{
   TRC2(RsLiCztGpCfm);
   
   CMXTA_DBG_PARAM((_cmxtap, "RsLiCztGpCfm():\n"));
  
   pst->event = EVTCZTGPCFM;
 
   czAcCztSendMsg(pst, suId, 0, cztCfm);

   CZ_FREEEVNT(cztCfm);

   RETVALUE(ROK);
} /* End of RsLiCztGpCfm */


/*
*
*       Fun:   RsLiCztBmpInd
*
*       Desc:  Call handler for Release Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  czac_cztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RsLiCztBmpInd
(
Pst            *pst,
SuId           suId,
CztEvnt      *cztInd
)
#else
PUBLIC S16 RsLiCztBmpInd(pst, suId, cztInd)
Pst            *pst;
SuId           suId;
CztEvnt      *cztInd;
#endif /* ANSI */
{
   TRC2(RsLiCztBmpInd);
   
   CMXTA_DBG_PARAM((_cmxtap, "RsLiCztBmpInd():\n"));
  
   pst->event = EVTCZTBMPIND;
 
   czAcCztSendMsg(pst, suId, 0, cztInd);

   CZ_FREEEVNT(cztInd);

   RETVALUE(ROK);
} /* End of RsLiCztBmpInd */


/*
*
*       Fun:   RsLiCztBmpCfm
*
*       Desc:  Call handler for Connection Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  czac_cztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RsLiCztBmpCfm
(
Pst            *pst,
SuId           suId,
CztEvnt      *conCfm
)
#else
PUBLIC S16 RsLiCztBmpCfm(pst, suId, conCfm)
Pst            *pst;
SuId           suId;
CztEvnt      *conCfm;
#endif /* ANSI */
{
   TRC2(RsLiCztBmpCfm);
   
   CMXTA_DBG_PARAM((_cmxtap, "RsLiCztBmpCfm():\n"));
  
   pst->event = EVTCZTBMPCFM;
 
   czAcCztSendMsg(pst, suId, 0, conCfm);

   CZ_FREEEVNT(conCfm);

   RETVALUE(ROK);
} /* End of RsLiCztEvnt */

/*
*
*       Fun:   RsLiCztGpErrInd
*
*       Desc:  Call handler for Connection based data indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  czac_cztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RsLiCztGpErrInd
(
Pst            *pst,
SuId           suId,
CztEvnt  *cztEvent
)
#else
PUBLIC S16 RsLiCztGpErrInd (pst, suId, cztEvent)
Pst            *pst;
SuId           suId;
CztEvnt  *cztEvent;
#endif /* ANSI */
{
   TRC2(RsLiCztGpErrInd);
   
   CMXTA_DBG_PARAM((_cmxtap, "RsLiCztGpErrInd():\n"));
  
   pst->event = EVTCZTGPERRIND;
 
   czAcCztSendMsg(pst, suId, 0, cztEvent);

   CZ_FREEEVNT(cztEvent);

   RETVALUE(ROK);
} /* End of RsLiCztGpErrInd */


/*
*
*       Fun:   RsLiCztLclErrorInd
*
*       Desc:  Call handler for Error Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  czac_cztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RsLiCztLclErrorInd
(
Pst            *post,
SuId           suId,
CztLclErrInd      *cztLclErrorInd
)
#else
PUBLIC S16 RsLiCztLclErrorInd(post, suId, cztLclErrorInd)
Pst            *post;
SuId           suId;
CztLclErrInd      *cztLclErrorInd;
#endif /* ANSI */
{
   TRC2(RsLiCztLclErrorInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "RsLiCztLclErrorInd():\n"));

   post->event = EVTCZTERRIND;

   czAcCztSendMsg(post, suId, 0, cztLclErrorInd);
   if(cztLclErrorInd->event)
      CMXTA_FREEEVNT(cztLclErrorInd->event);
   if(cztLclErrorInd->rcvBuf)
      CMXTA_FREEMBUF(cztLclErrorInd->rcvBuf);

   CMXTA_FREE(cztLclErrorInd, sizeof(CztLclErrInd));
  
   RETVALUE(ROK);
} /* End of RsLiCztLclErrorInd */

/*
*
*       Fun:   RsLiCztRelCfm
*
*       Desc:  Call handler for Connection Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  czac_cztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RsLiCztRelCfm
(
Pst            *pst,
SuId           suId,
CztRlsCfm      *rlsCfm
)
#else
PUBLIC S16 RsLiCztRelCfm(pst, suId, rlsCfm)
Pst            *pst;
SuId           suId;
CztRlsCfm      *rlsCfm;
#endif /* ANSI */
{
   TRC2(RsLiCztRelCfm);
   
   CMXTA_DBG_PARAM((_cmxtap, "RsLiCztRelCfm():\n"));
  
   pst->event = EVTCZTLOCALRELCFM;
 
   czAcCztSendMsg(pst, suId, 0, rlsCfm);
   CMXTA_FREE(rlsCfm, sizeof(CztRlsCfm));

   RETVALUE(ROK);
} /* End of RsLiCztRelCfm */


/*
*
*       Fun:   RsLiCztStatusInd
*
*       Desc:  Call handler for Status Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  czac_cztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RsLiCztStatusInd
(
Pst            *post,
SuId           suId,
CztStaInd      *cztSta
)
#else
PUBLIC S16 RsLiCztStatusInd(post, suId, cztSta)
Pst            *post;
SuId           suId;
CztStaInd      *cztSta;
#endif /* ANSI */
{
   TRC2(RsLiCztStatusInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "RsLiCztStatusInd():\n"));

   post->event = EVTCZTSTAIND;

   czAcCztSendMsg(post, suId, 0, cztSta);
   CMXTA_FREE(cztSta, sizeof(CztStaInd));
  
   RETVALUE(ROK);
} /* End of RsLiCztStatusInd */



/*
*
*       Fun:   RsLiCztDynamPeerAssocInd
*
*       Desc:  Call handler for Peer Assoc Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  czac_cztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RsLiCztDynamPeerAssocInd
(
Pst              *pst,
SuId             suId,
CztPeerAssocInd  *peerAssocInd
)
#else
PUBLIC S16 RsLiCztDynamPeerAssocInd(pst, suId, peerAssocInd)
Pst              *pst;
SuId             suId;
CztPeerAssocInd  *peerAssocInd;
#endif /* ANSI */
{
   TRC2(RsLiCztDynamPeerAssocInd);
   
   CMXTA_DBG_PARAM((_cmxtap, "RsLiCztDynamPeerAssocInd():\n"));
  
   pst->event = EVTCZTPEERASSOCIND;
 
   czAcCztSendMsg(pst, suId, 0, peerAssocInd);
   CMXTA_FREE(peerAssocInd, sizeof(CztPeerAssocInd));


   RETVALUE(ROK);
} /* End of RsLiCztPeerAssocInd */


/*
*
*       Fun:   RsLiCztAudCfm
*
*       Desc:  Call handler for 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  czac_cztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 RsLiCztAudCfm
(
Pst              *pst,
SuId             suId,
CztAudEvnt  *audEvnt
)
#else
PUBLIC S16 RsLiCztAudCfm(pst, suId, audEvnt)
Pst              *pst;
SuId             suId;
CztAudEvnt  *audEvnt;
#endif /* ANSI */
{
   TRC2(RsLiCztAudCfm);
   
   CMXTA_DBG_PARAM((_cmxtap, "RsLiCztAudCfm():\n"));
  
   pst->event = EVTCZTAUDCFM;
 
   czAcCztSendMsg(pst, suId, 0, audEvnt);
   CMXTA_FREE(audEvnt, sizeof(CztAudEvnt));


   RETVALUE(ROK);
} /* End of RsLiCztAudCfm */



/*
*
*       Fun:   czAcCztSendMsg 
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
PUBLIC S16 czAcCztSendMsg
(
Pst            *pst,
SpId           suId,
Reason         reason,
Void           *ptr
)
#else
PUBLIC S16 czAcCztSendMsg(pst, suId, reason, ptr)
Pst            *pst;
SpId           suId;
Reason         reason;
Void           *ptr;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   CzAccMsgQElm *czMsg;
   CzAcCztInfo  *cztInfo;
   S16 ret = ROK;
   TknU8 *enbId;
   Mem   mem;
 
   TRC3(czAcCztSendMsg);

   mem.region = 0;
   mem.pool = 0;
 
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the asmgciated test case */
   if ((tcCb = czAcCztTstCbFind()) == NULLP)
   {
      /*-- No asmgciated test case found, spurious
        message, drop it --*/
 
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped ...\n"));
      RETVALUE(ROK);
   }

   /*-- Check if any tapa directives set --*/
 
   /*-- Allocate CZ memory data --*/
   czMsg = NULLP;
   CMXTA_ALLOC(&czMsg, sizeof (CzAccMsgQElm));
   if (czMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "czAcCztSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)czMsg;
   qElm.msgFreeFun = czAcUtlCztCb;
   cztInfo = &(czMsg->u.cztInfo);

   /*** fill the suId in teh Q element****/
   cztInfo->cmInfo.suId = suId;

   switch (pst->event) 
   {
      case EVTCZTBNDCFM: 
      {
         cztInfo->status = reason;
         break;
      }
      case EVTCZTGPIND:
      {
         CztEvnt *conInd;
         conInd = (CztEvnt *)ptr;
         cztInfo->peerId = conInd->peerId;
         cztInfo->msgType = czAcUtlGetMsgType(&(conInd->pdu));
         if(cztInfo->msgType == CZT_MSG_X2_SETUP)
         {
            czUtlGetIE(&(conInd->pdu), Cztid_GlobalENB_ID, &enbId);
            if(enbId != NULLP)
            {
               cztInfo->enbId = ((TknU32 *)enbId)->val;
            }
         }
         if(cztInfo->msgType == CZT_MSG_RESET)
         {
            czAcUtlCztGetErrCause(&(conInd->pdu), &cztInfo->cause.causeType,
               &cztInfo->cause.causeVal);
            
         }
         if(cztInfo->msgType == CZT_MSG_RSRC_ST_REQ ||
            cztInfo->msgType == CZT_MSG_RSRC_ST_UPD)
         {
            czUtlGetIE(&(conInd->pdu), Cztid_ENB1_Measurement_ID, &enbId);
            if(enbId != NULLP)
            {
               cztInfo->u.rsrcInfo.eNb1MeasId = ((TknU32 *)enbId)->val;
            }
            czUtlGetIE(&(conInd->pdu), Cztid_ENB2_Measurement_ID, &enbId);
            if(enbId != NULLP)
            {
               cztInfo->u.rsrcInfo.eNb2MeasId = ((TknU32 *)enbId)->val;
            }
         }
         break;
      }
      case EVTCZTGPCFM:
      {
         CztEvnt *conCfm;
         conCfm = (CztEvnt *)ptr;
         cztInfo->peerId = conCfm->peerId;
         cztInfo->msgType = czAcUtlGetMsgType(&(conCfm->pdu));
         if(cztInfo->msgType == CZT_MSG_X2_SETUP_RSP)
         {
/*
            czUtlGetIE(&(conCfm->pdu), Cztid_GlobalENB_ID, &enbId);
            if(enbId != NULLP)
            {
               cztInfo->enbId = ((TknU32 *)enbId)->val;
            }
*/
         }
         if(cztInfo->msgType == CZT_MSG_X2_SETUP_FAIL ||
            cztInfo->msgType == CZT_MSG_CFG_UPD_FAIL ||
            cztInfo->msgType == CZT_MSG_RSRC_ST_FAIL)
         {
            czAcUtlCztGetErrCause(&(conCfm->pdu), &cztInfo->cause.causeType,
               &cztInfo->cause.causeVal);
            czAcUtlCztGetCritDiag(conCfm, &cztInfo->crit);
            
         }
         if(cztInfo->msgType == CZT_MSG_RSRC_ST_FAIL)
         {
            czUtlGetIE(&(conCfm->pdu), Cztid_ENB1_Measurement_ID, &enbId);
            if(enbId != NULLP)
            {
               cztInfo->u.rsrcInfo.eNb1MeasId = ((TknU32 *)enbId)->val;
            }
            czUtlGetIE(&(conCfm->pdu), Cztid_ENB2_Measurement_ID, &enbId);
            if(enbId != NULLP)
            {
               cztInfo->u.rsrcInfo.eNb2MeasId = ((TknU32 *)enbId)->val;
            }
         }
         break;
      }
    case EVTCZTBMPIND: 
      {
         CztEvnt *conInd;

         conInd = (CztEvnt *)ptr;
         cztInfo->peerId = conInd->peerId;
         cztInfo->msgType = czAcUtlGetMsgType(&(conInd->pdu));

         czUtlGetIE(&(conInd->pdu), Cztid_Old_eNB_UE_X2AP_ID, &enbId);
         if(enbId != NULLP)
         {
            cztInfo->u.ueInfo.oldX2APUEId = ((TknU32 *)enbId)->val;
         }
         if(cztInfo->msgType != CZT_MSG_HO_REQ)
         {
           czUtlGetIE(&(conInd->pdu), Cztid_New_eNB_UE_X2AP_ID, &enbId);
           if(enbId != NULLP)
           {
              cztInfo->u.ueInfo.newX2APUEId = ((TknU32 *)enbId)->val;
           }
         }
         if(cztInfo->msgType == CZT_MSG_HO_CANCEL)
         {
            czAcUtlCztGetErrCause(&(conInd->pdu), &cztInfo->cause.causeType,
               &cztInfo->cause.causeVal);
         }
         cztInfo->type.pres = PRSNT_NODEF;
         break;
      }

      case EVTCZTBMPCFM: 
      {
         CztEvnt *conCfm;

         conCfm = (CztEvnt *)ptr;
         cztInfo->peerId = conCfm->peerId;

         cztInfo->msgType = czAcUtlGetMsgType(&(conCfm->pdu));
         czUtlGetIE(&(conCfm->pdu), Cztid_Old_eNB_UE_X2AP_ID, &enbId);
         if(enbId != NULLP)
         {
            cztInfo->u.ueInfo.oldX2APUEId = ((TknU32 *)enbId)->val;
         }
         if(cztInfo->msgType == CZT_MSG_HO_ACK)
         {
           czUtlGetIE(&(conCfm->pdu), Cztid_New_eNB_UE_X2AP_ID, &enbId);
           if(enbId != NULLP)
           {
              cztInfo->u.ueInfo.newX2APUEId = ((TknU32 *)enbId)->val;
           }
         }
         if(cztInfo->msgType == CZT_MSG_HO_FAIL)
         {
            czAcUtlCztGetErrCause(&(conCfm->pdu), &cztInfo->cause.causeType,
               &cztInfo->cause.causeVal);
            czAcUtlCztGetCritDiag(conCfm, &cztInfo->crit);
         }
         
         break;
      }
      case EVTCZTGPERRIND:
      {
         CztEvnt *errInd;
         errInd = (CztEvnt *)ptr;
         czMsg->u.cztInfo.msgType = CZT_MSG_ERR_IND; 
         cztInfo->peerId = errInd->peerId;
         czUtlGetIE(&(errInd->pdu), Cztid_Old_eNB_UE_X2AP_ID, &enbId);
         if(enbId != NULLP)
         {
            cztInfo->u.ueInfo.oldX2APUEId = ((TknU32 *)enbId)->val;
         }
         czUtlGetIE(&(errInd->pdu), Cztid_New_eNB_UE_X2AP_ID, &enbId);
         if(enbId != NULLP)
         {
            cztInfo->u.ueInfo.newX2APUEId = ((TknU32 *)enbId)->val;
         }
         czAcUtlCztGetErrCause(&(errInd->pdu), &cztInfo->cause.causeType,
               &cztInfo->cause.causeVal);
         czAcUtlCztGetCritDiag(errInd, &cztInfo->crit);
         break;
      }

      case EVTCZTERRIND: 
      {
         CztLclErrInd *errInd;

         errInd = (CztLclErrInd *)ptr;

         cztInfo->peerId = errInd->peerId;
         cztInfo->type.pres = PRSNT_NODEF;
         cztInfo->type.val = CZAC_ERRIND;

         cztInfo->u.errInd.type = errInd->causeType;
         cztInfo->u.errInd.value = errInd->causeValue;
         break;
      }

       case EVTCZTLOCALRELCFM: 
      {
         CztRlsCfm *rlsCfm;

         rlsCfm = (CztRlsCfm *)ptr;
         
         cztInfo->peerId =rlsCfm->peerId;

         cztInfo->type.pres = PRSNT_NODEF;
         cztInfo->type.val = CZAC_RLSCFM;

         cztInfo->u.rlsCfm.type = rlsCfm->type;
         /* since its union.....single line can be used for action and reason */
         cztInfo->u.rlsCfm.reason = rlsCfm->reason;
         cztInfo->u.rlsCfm.status = rlsCfm->status;

         break;
      }

      case EVTCZTSTAIND: 
      {
         CztStaInd *staInd;

         staInd = (CztStaInd *)ptr;

         cztInfo->peerId =staInd->peerId;

         cztInfo->type.pres = PRSNT_NODEF;
         cztInfo->type.val = CZAC_STAIND;

         cztInfo->u.staInd.type = staInd->type;
         /* since its union.....single line can be used for action and reason */
         cztInfo->u.staInd.reason = staInd->reason;
         cztInfo->u.staInd.status = staInd->status;
         break;
      }

      case EVTCZTPEERASSOCIND: 
      {
         CztPeerAssocInd *peerAssocInd;

         peerAssocInd = (CztPeerAssocInd *)ptr;

         dynamDstAddrLst = peerAssocInd->dstAddrLst;
         break;
      }

      case EVTCZTAUDCFM: 
      {
         CztAudEvnt *audEvnt;

         audEvnt = (CztAudEvnt *)ptr;

         cztInfo->type.pres = PRSNT_NODEF;
         cztInfo->type.val = CZAC_AUDCFM;

         if (audEvnt->type == CZT_AUD_PEER)
         {
            cztInfo->peerId =audEvnt->u.audPeer.peerId;
            cztInfo->u.audCfm.peerState = audEvnt->u.audPeer.peerState;
         }


         cztInfo->u.audCfm.type = audEvnt->type;

         /* since its union.....single line can be used for action and reason */
         cztInfo->u.audCfm.status = audEvnt->status.status;
         cztInfo->u.audCfm.cause = audEvnt->status.cause;

         break;
      }
      default:
      break;

   } /* end of pst->evt */

   if( ret == ROK)
   {
      /*-- Test case found, queue the message for the tcCb --*/
      /* Push it onto the message queue --*/
      (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
 
      /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not
        trigger the test engine now in that case, the test engine
        will MGAC_ENHANCE have a look at the queued message --*/
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   } 
   else
   {
      CMXTA_FREE(czMsg, sizeof(CzAccMsgQElm));
   }
 
   RETVALUE(ret);
} /* end of czAcCztSaveMsg() */
   
/*
*
*       Fun:   czAcCztTstCbFind
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  czac_cztcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  czAcCztTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  czAcCztTstCbFind ()
#endif
{
   TRC2(czAcCztTstCbFind);
 
   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   /*-- Change SOAC_ENHANCE --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif
 
   RETVALUE(NULLP);
} /* End of czAcCztTstCbFind */


/*
*
*       Fun:   czAcUtlCztCb
*
*       Desc:  This function is used to
*
*       Ret:   None
*
*       Notes: None
*
*       File:  czac_cztcb.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztCb
(
CmXtaMsgQElm   *qElm
)
#else
PUBLIC S16 czAcUtlCztCb(qElm)
CmXtaMsgQElm   *qElm;
#endif /* ANSI */
{
   CzAccMsgQElm *czMsg;
   CzAcCztInfo  *cztInfo = NULLP; 
 
   TRC2(czAcUtlCztCb);
 
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlCztCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   czMsg = (CzAccMsgQElm *)qElm->data;
  
   if(czMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   cztInfo = &(czMsg->u.cztInfo);
   
   if( cztInfo->type.pres == PRSNT_NODEF)
   {
      switch(cztInfo->type.val)
      {
        case CZAC_STAIND:
            /* TBD: deallocate any memory allocated using CMXTA_ALLOC */
             break;
        default:
           break;
       } 
   } 
 
   if (czMsg != NULLP)
   {
      if(czMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(czMsg->mBuf);

      CMXTA_FREE(czMsg, sizeof (CzAccMsgQElm));
      qElm->data = NULLP;
   }
 
   RETVALUE(CMXTA_ERR_NONE);
} /* End of czAcUtlCztCb() */

/********************************************************************30**

         End of file:     czac_cztcb.c@@/main/2 - Tue Aug 30 18:35:44 2011

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
