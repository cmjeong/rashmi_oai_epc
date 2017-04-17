
/********************************************************************20**

     Name:    SZT - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    szac_lszhdl.c

     Sid:      szac_sztcb.c@@/main/4 - Mon Jan 10 22:16:01 2011

     Prg:    pk
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
#include "cm_dns.h"         /* common DNS libraru defines */
#include "cm_xta.h" 
#include "cm_pasn.h"

/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"            /* System Agent  */
#endif /* SZ_FTHA */
#include "lsz.h"            /* defines and macros for SZ */
#include "sct.h"            /* defines and macros for SZ */
#include "szt.h"            /* defines and macros for SZ */
#include "szac_asn.h"        /* defines and macros for SZ ASN */
#ifdef SB
#include "lsb.h"            /* SCTP layer managment defines */
#endif /*SB*/
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/ 
#include "sz_err.h"         /* SZ error defines */
#include "sz.h"            /* defines and macros for SZ */
#include "szac_acc.h"       /* defines for SZ acceptance tests */
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

#include "cm_pasn.x"
#include "cm_xta.x" 

/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"            /* System Agent  */
#endif /* SZ_FTHA */
/* sz006.301: Removed un-necessary include files  */
#include"szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL11;
#ifndef SZ_ENC_DEC
#include "szac_asn_pk.x"
#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* typedefs for STCP */
#include "lsz.x"           /* layer management typedefs for SZCP */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* typedefs for SZCP */
//#include "szt_asn.x"       /* typedefs for ASN */
#ifdef SB
#include "lsb.x"           /* SCTP layer managment structures */
#endif /*SB*/
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#include "sz.x"            /* typedefs for SZCP */
#include "szac_acc.x"      /* typedefs for SZCP acceptance tests */
#include "szac_szt.x"

#ifdef __cplusplus
extern "C"
{
#endif
EXTERN S16 szAcUtlSztGetErrCause ARGS((SztS1AP_PDU *pdu, U8 *causeType, U32 *causeVal));
#ifdef __cplusplus
}
#endif


PUBLIC SztReset szacReset;
PUBLIC S1apPdu *rstAckPdu;


#ifdef SZ_MME
PUBLIC SztNetAddrLst dynamDstAddrLst;
#endif


/*
*
*       Fun:   SzLiSztBndCfm
*       
*       Desc:  Call handler for Bind Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztBndCfm
(
Pst            *pst,
SuId           suId,
U8             status
)
#else
PUBLIC S16 UzLiSztBndCfm(pst, suId, status)
Pst            *pst;
SuId           suId;
U8             status;
#endif
{
   TRC2(UzLiSztBndCfm);
 
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztBndCfm():\n"));

   pst->event = EVTSZTBNDCFM;
 
   szAcSztSendMsg(pst, suId, status, NULLP);    

   RETVALUE(ROK);
} /* End of UzLiSztBndCfm */

/*
*
*       Fun:   UzLiSztAudCfm
*
*       Desc:  Call handler for Aduit Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztAudCfm
(
Pst            *pst,
SuId           suId,
SztAudEvnt     *audEvnt
)
#else
PUBLIC S16 UzLiSztAudCfm(pst, suId, audEvnt)
Pst            *pst;
SuId           suId;
SztAudEvnt     *audEvnt;
#endif /* ANSI */
{
   TRC2(UzLiSztAudCfm);
   
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztAudCfm():\n"));
  
   pst->event = EVTSZTAUDCFM;
 
   szAcSztSendMsg(pst, suId, 0, audEvnt);

   RETVALUE(ROK);
} /* End of UzLiSztAudCfm */

/*
*
*       Fun:   UzLiSztStaInd
*
*       Desc:  Call handler for Status Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztStaInd
(
Pst            *post,
SuId           suId,
SztStaInd      *sztSta
)
#else
PUBLIC S16 UzLiSztStaInd(post, suId, sztSta)
Pst            *post;
SuId           suId;
SztStaInd      *sztSta;
#endif /* ANSI */
{
   TRC2(UzLiSztStaInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztStaInd():\n"));

   post->event = EVTSZTSTAIND;

   szAcSztSendMsg(post, suId, 0, sztSta);
  
   RETVALUE(ROK);
} /* End of UzLiSztStaInd */

/*
*
*       Fun:   UzLiSztFlcInd
*
*       Desc:  Call handler for Status Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztFlcInd
(
Pst            *post,
SuId           suId,
SztFlcInd      *flcInd
)
#else
PUBLIC S16 UzLiSztFlcInd(post, suId, flcInd)
Pst            *post;
SuId           suId;
SztFlcInd      *flcInd;
#endif /* ANSI */
{
   TRC2(UzLiSztFlcInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztFlcInd():\n"));

   post->event = EVTSZTFLCIND;

   szAcSztSendMsg(post, suId, 0, flcInd);
  
   RETVALUE(ROK);
} /* End of UzLiSztFlcInd */

/*
*
*       Fun:   UzLiSztErrInd
*
*       Desc:  Call handler for Error Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztErrInd
(
Pst            *post,
SuId           suId,
SztLclErrInd      *sztLclErrInd
)
#else
PUBLIC S16 UzLiSztErrInd(post, suId, sztLclErrInd)
Pst            *post;
SuId           suId;
SztLclErrInd      *sztLclErrInd;
#endif /* ANSI */
{
   TRC2(UzLiSztErrInd);
 
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztErrInd():\n"));

   post->event = EVTSZTERRIND;

   szAcSztSendMsg(post, suId, 0, sztLclErrInd);
  
   RETVALUE(ROK);
} /* End of UzLiSztErrInd */

/*
*
*       Fun:   UzLiSztUDatInd
*
*       Desc:  Call handler for Connection-less data indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztUDatInd
(
Pst            *pst,
SuId           suId,
SztUDatEvnt    *uDatEvnt
)
#else
PUBLIC S16 UzLiSztUDatInd(pst, suId, uDatEvnt)
Pst            *pst;
SuId           suId;
SztUDatEvnt    *uDatEvnt;
#endif /* ANSI */
{
   TRC2(UzLiSztUDatInd);
   
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztUDatInd():\n"));
  
   pst->event = EVTSZTUDATIND;

   szAcSztSendMsg(pst, suId, 0, uDatEvnt);

   SZ_FREE_SDU(uDatEvnt->pdu);

   RETVALUE(ROK);
} /* End of UzLiSztUDatInd */

/*
*
*       Fun:   UzLiSztConInd
*
*       Desc:  Call handler for Connection Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztConInd
(
Pst            *pst,
SuId           suId,
SztConInd      *conInd
)
#else
PUBLIC S16 UzLiSztConInd(pst, suId, conInd)
Pst            *pst;
SuId           suId;
SztConInd      *conInd;
#endif /* ANSI */
{
   TRC2(UzLiSztConInd);
   
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztConInd():\n"));
  
   pst->event = EVTSZTCONIND;
 
   szAcSztSendMsg(pst, suId, 0, conInd);

   SZ_FREE_SDU(conInd->pdu);

   RETVALUE(ROK);
} /* End of UzLiSztConInd */

/*
*
*       Fun:   UzLiSztConCfm
*
*       Desc:  Call handler for Connection Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztConCfm
(
Pst            *pst,
SuId           suId,
SztConCfm      *conCfm
)
#else
PUBLIC S16 UzLiSztConCfm(pst, suId, conCfm)
Pst            *pst;
SuId           suId;
SztConCfm      *conCfm;
#endif /* ANSI */
{
   TRC2(UzLiSztConCfm);
   
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztConCfm():\n"));
  
   pst->event = EVTSZTCONCFM;
 
   szAcSztSendMsg(pst, suId, 0, conCfm);

   SZ_FREE_SDU(conCfm->pdu);

   RETVALUE(ROK);
} /* End of UzLiSztConCfm */

/* sz005.301 Added for S1 Abort request support by UI */
#ifdef SZTV2
/*
*
*       Fun:   UzLiSztAbortS1Cfm
*
*       Desc:  Call handler for S1 Abort Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztAbortS1Cfm
(
Pst          *pst,
SuId         suId,
SztAbortS1   *abortS1
)
#else
PUBLIC S16 UzLiSztAbortS1Cfm(pst, suId, abortS1)
Pst          *pst;
SuId         suId;
SztAbortS1   *abortS1;
#endif /* ANSI */
{
   TRC2(UzLiSztAbortS1Cfm);
   
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztAbortS1Cfm():\n"));
  
   pst->event = EVTSZTABORTS1CFM;
 
   szAcSztSendMsg(pst, suId, 0, abortS1);

   RETVALUE(ROK);
} /* End of UzLiSztAbortS1Cfm */
#endif /* SZTV2 */

/*
*
*       Fun:   UzLiSztRelInd
*
*       Desc:  Call handler for Release Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztRelInd
(
Pst            *pst,
SuId           suId,
SztRelInd      *relInd
)
#else
PUBLIC S16 UzLiSztRelInd(pst, suId, relInd)
Pst            *pst;
SuId           suId;
SztRelInd      *relInd;
#endif /* ANSI */
{
   TRC2(UzLiSztRelInd);
   
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztRelInd():\n"));
  
   pst->event = EVTSZTRELIND;
 
   szAcSztSendMsg(pst, suId, 0, relInd);

   SZ_FREE_SDU(relInd->pdu);

   RETVALUE(ROK);
} /* End of UzLiSztRelInd */

/*
*
*       Fun:   UzLiSztRelCfm
*
*       Desc:  Call handler for Release Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztRelCfm
(
Pst            *pst,
SuId           suId,
SztRelCfm      *relCfm
)
#else
PUBLIC S16 UzLiSztRelCfm(pst, suId, relCfm)
Pst            *pst;
SuId           suId;
SztRelCfm      *relCfm;
#endif /* ANSI */
{
   TRC2(UzLiSztRelCfm);
   
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztRelCfm():\n"));
  
   pst->event = EVTSZTRELCFM;
 
   szAcSztSendMsg(pst, suId, 0, relCfm);

   SZ_FREE_SDU(relCfm->pdu);

   RETVALUE(ROK);
} /* End of UzLiSztRelCfm */

/*
*
*       Fun:   UzLiSztDatInd
*
*       Desc:  Call handler for Connection based data indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztDatInd
(
Pst            *pst,
SuId           suId,
SztDatEvntInd  *datEvnt
)
#else
PUBLIC S16 UzLiSztDatInd(pst, suId, datEvnt)
Pst            *pst;
SuId           suId;
SztDatEvntInd  *datEvnt;
#endif /* ANSI */
{
   TRC2(UzLiSztDatInd);
   
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztDatInd():\n"));
  
   pst->event = EVTSZTDATIND;
 
   szAcSztSendMsg(pst, suId, 0, datEvnt);

   SZ_FREE_SDU(datEvnt->pdu);

   RETVALUE(ROK);
} /* End of UzLiSztDatInd */

/*
*
*       Fun:   UzLiSztEncDecCfm
*
*       Desc:  Call handler for Encode/Decode Confirmation
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztEncDecCfm
(
Pst            *pst,
SuId           suId,
SztEncDecEvnt  *sztEncDecEvnt,
SztReqStatus   *status
)
#else
PUBLIC S16 UzLiSztEncDecCfm(pst, suId, sztEncDecEvnt,status)
Pst            *pst;
SuId           suId;
SztEncDecEvnt  *sztEncDecEvnt;
SztReqStatus   *status;
#endif /* ANSI */
{
   TRC2(UzLiSztEncDecCfm);
   
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztEncDecCfm():\n"));
  
   pst->event = EVTSZTENCDECCFM;
 
   szAcSztSendMsg(pst, suId, 0, sztEncDecEvnt);

   if(status->status == SZT_PRIM_OK)
   {
     
      if (sztEncDecEvnt->type.pres == PRSNT_NODEF)
      {
         if (sztEncDecEvnt->type.val == SZT_REQ_TYPE_DECODE || sztEncDecEvnt->type.val == SZT_REQ_TYPE_ENCODE)
         {
            if (sztEncDecEvnt->type.val == SZT_REQ_TYPE_DECODE)
            {
               SZ_FREE_SDU(sztEncDecEvnt->u.pdu);
            }
            else
            {
               SZ_FREE_BUF(sztEncDecEvnt->u.mBuf);
            }
         }
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
         else if (sztEncDecEvnt->type.val == SZT_REQ_TYPE_ENCODE_IE || sztEncDecEvnt->type.val == SZT_REQ_TYPE_DECODE_IE)
         {
            if (sztEncDecEvnt->type.val == SZT_REQ_TYPE_DECODE_IE)
            {
               SZ_FREE_SDU(sztEncDecEvnt->u.iePdu);
            }
            else
            {
               SZ_FREE_BUF(sztEncDecEvnt->u.mBuf);
            }
         }
#endif   /* SZTV1 */
      }
      /* sz008.301 : Removed CMXTA_FREE for double free issue */
   }

   RETVALUE(ROK);
} /* End of UzLiSztEncDecCfm */

#ifdef SZ_MME
/*
*
*       Fun:   UzLiSztPeerAssocInd
*
*       Desc:  Call handler for Peer Assoc Indication
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  szac_sztcb.c
*       
*/
#ifdef ANSI
PUBLIC S16 UzLiSztPeerAssocInd
(
Pst              *pst,
SuId             suId,
SztPeerAssocInd  *peerAssocInd
)
#else
PUBLIC S16 UzLiSztPeerAssocInd(pst, suId, peerAssocInd)
Pst              *pst;
SuId             suId;
SztPeerAssocInd  *peerAssocInd;
#endif /* ANSI */
{
   TRC2(UzLiSztPeerAssocInd);
   
   CMXTA_DBG_PARAM((_cmxtap, "UzLiSztPeerAssocInd():\n"));
  
   pst->event = EVTSZTPEERASSOCIND;
 
   szAcSztSendMsg(pst, suId, 0, peerAssocInd);

   RETVALUE(ROK);
} /* End of UzLiSztPeerAssocInd */
#endif

/*
*
*       Fun:   szAcSztSendMsg 
*
*       Desc:  Call handler for Saving Message
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_sztcb.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcSztSendMsg
(
Pst            *pst,
SpId           suId,
Reason         reason,
Void           *ptr
)
#else
PUBLIC S16 szAcSztSendMsg(pst, suId, reason, ptr)
Pst            *pst;
SpId           suId;
Reason         reason;
Void           *ptr;
#endif /* ANSI */
{
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   SzAccMsgQElm *szMsg;
   SzAcSztInfo  *sztInfo;
   S16 ret = ROK;
   U8 evnt;
   U8  causeType = 0;
   U32 causeVal  = 0;
   TknU8 *enbId;
   TknU8 *mmeId;
   Mem   mem;
 
   TRC3(szAcSztSendMsg);

   mem.region = 0;
   mem.pool = 0;
 
   CMXTA_ZERO(&qElm, sizeof(qElm));
 
   /*-- Find the asmgciated test case */
   if ((tcCb = szAcSztTstCbFind()) == NULLP)
   {
      /*-- No asmgciated test case found, spurious
        message, drop it --*/
 
      CMXTA_DBG_INFO((_cmxtap, "Msg dropped ...\n"));
      RETVALUE(ROK);
   }

   /*-- Check if any tapa directives set --*/
 
   /*-- Allocate SZ memory data --*/
   szMsg = NULLP;
   CMXTA_ALLOC(&szMsg, sizeof (SzAccMsgQElm));
   if (szMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "szAcSztSendMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   } 

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));

   qElm.data = (Void *)szMsg;
   qElm.msgFreeFun = szAcUtlSztCb;
   sztInfo = &(szMsg->u.sztInfo);

   /*** fill the suId in teh Q element****/
   sztInfo->cmInfo.suId = suId;

   switch (pst->event) 
   {
      case EVTSZTBNDCFM: 
      {
         sztInfo->status = reason;
         break;
      }

      case EVTSZTAUDCFM:
      {
         SztAudEvnt *audEvnt;
         U8       i;

         audEvnt = (SztAudEvnt *)ptr;

         sztInfo->type.pres = PRSNT_NODEF;
         sztInfo->type.val = SZAC_AUDIT;

         sztInfo->u.audit.type = audEvnt->type;
         sztInfo->u.audit.status = audEvnt->status.status;
         sztInfo->u.audit.cause = audEvnt->status.cause;
         
         switch (audEvnt->type)
         {
            case SZT_AUD_CONN:
            {
               sztInfo->u.audit.u.conn.nmbConn = audEvnt->u.audConn.nmbConn;
               sztInfo->u.audit.u.conn.connIdType = audEvnt->u.audConn.connIdType;
               for(i = 0;i < sztInfo->u.audit.u.conn.nmbConn; i++)
               {
                  sztInfo->u.audit.u.conn.connId[i] = audEvnt->u.audConn.connSt[i].connId;
                  sztInfo->u.audit.u.conn.connSt[i] = audEvnt->u.audConn.connSt[i].state;
               }
               break;
            }
            
            case SZT_AUD_PEER:
            {
               sztInfo->u.audit.u.peer.peerId = audEvnt->u.audPeer.peerId;
               sztInfo->u.audit.u.peer.peerState = audEvnt->u.audPeer.peerState;
               break;
            }
         }
         break;
      }

      case EVTSZTFLCIND:
      {
         SztFlcInd   *flcInd;
         flcInd   =  (SztFlcInd *)ptr;

         sztInfo->type.pres = PRSNT_NODEF;
         sztInfo->type.val = SZAC_FLCIND;

         sztInfo->peerId   =  flcInd->peerId;
         sztInfo->status   =  flcInd->status;

      }
      break;

      case EVTSZTSTAIND: 
      {
         SztStaInd *staInd;

         staInd = (SztStaInd *)ptr;

         cmMemcpy((U8 *)&(sztInfo->peerId), (CONSTANT U8 *)&(staInd->peerId),
                  sizeof(TknU32));

         sztInfo->type.pres = PRSNT_NODEF;
         sztInfo->type.val = SZAC_STAIND;

         sztInfo->u.staInd.type = staInd->type;
         /* since its union.....single line can be used for action and reason */
         sztInfo->u.staInd.reason = staInd->reason;
         sztInfo->u.staInd.status = staInd->status;
         break;
      }

      case EVTSZTERRIND: 
      {
         SztLclErrInd *errInd;

         errInd = (SztLclErrInd *)ptr;

         sztInfo->type.pres = PRSNT_NODEF;
         sztInfo->type.val = SZAC_ERRIND;

         sztInfo->u.errInd.type = errInd->causeType;
         sztInfo->u.errInd.value = errInd->causeValue;
         break;
      }

      case EVTSZTUDATIND: 
      {
         SztUDatEvnt *datEvnt;

         datEvnt = (SztUDatEvnt *)ptr;
         
         cmMemcpy((U8 *)&(sztInfo->peerId), (CONSTANT U8 *)&(datEvnt->peerId),
                  sizeof(TknU32));

         szUtilsGetMsgIdx (&evnt, datEvnt->pdu);
         sztInfo->type.val = evnt;

         if(evnt == SZT_MSG_ID_ERR_IND)
         {
             if(szAcUtlSztGetErrCause(&(datEvnt->pdu->pdu), &causeType, &causeVal) == ROK)
             {
                sztInfo->u.errInd.type   = causeType;
                sztInfo->u.errInd.value  = causeVal;
             }
         }

         if(evnt == SZT_MSG_ID_RESET)
         {
            /* szGetIE(&(datEvnt->pdu->pdu), Sztid_ResetTyp, &resetTyp);
            if(((SztResetTyp *)resetTyp)->choice.val == SZ_PARTIAL_RESET)
            {
               cmMemcpy((U8 *)&szacReset,(U8 *)&(datEvnt->pdu->pdu.val.initiatingMsg.value.u.sztReset),sizeof(SztReset));
            }
            */ 
            /* sz008.301: Fix for kwork. */
            szDbFillResetAck(datEvnt->pdu, &rstAckPdu, mem, &causeType);
         }

         break;
      }

      case EVTSZTCONIND: 
      {
         SztConInd *conInd;

         conInd = (SztConInd *)ptr;

         szUtilsGetMsgIdx (&evnt, conInd->pdu);
         sztInfo->type.val = evnt;
         
         /* sz003.301: Updted for PSF-S1AP 3.1 release. Update connId at
          * this time */
#ifndef SZ_FTHA
         if(szAcUtlSztUpdConnId(tcCb, &tcCb->stack[tcCb->sp], conInd->u.spConnId) != ROK)
         {
            RETVALUE(RFAILED);
         } 
#else /* SZ_FTHA */
         sztInfo->spConnId = conInd->u.spConnId;
#endif /* SZ_FTHA */

         szGetIE(&(conInd->pdu->pdu), Sztid_eNB_UE_S1AP_ID, &enbId);
         szGetIE(&(conInd->pdu->pdu), Sztid_MME_UE_S1AP_ID, &mmeId);
         if(enbId != NULLP)
         {
            sztInfo->u.pduInfo.enbId = ((TknU32 *)enbId)->val;
         }
         if(mmeId != NULLP)
         {
            sztInfo->u.pduInfo.mmeId = ((TknU32 *)mmeId)->val;
         }

         break;
      }

      case EVTSZTCONCFM: 
      {
         SztConCfm *conCfm;

         conCfm = (SztConCfm *)ptr;

         szUtilsGetMsgIdx (&evnt, conCfm->pdu);
         sztInfo->type.val = evnt;
         
         szGetIE(&(conCfm->pdu->pdu), Sztid_eNB_UE_S1AP_ID, &enbId);
         szGetIE(&(conCfm->pdu->pdu), Sztid_MME_UE_S1AP_ID, &mmeId);
         if(enbId != NULLP)
         {
            sztInfo->u.pduInfo.enbId = ((TknU32 *)enbId)->val;
         }
         if(mmeId != NULLP)
         {
            sztInfo->u.pduInfo.mmeId = ((TknU32 *)mmeId)->val;
         }

         /* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
          * header files */
#ifndef SZ_FTHA
         if(szAcUtlSztUpdConnId(tcCb, &tcCb->stack[tcCb->sp], conCfm->spConnId) != ROK)
         {
            RETVALUE(RFAILED);
         } 
#else /* SZ_FTHA */
         sztInfo->spConnId = conCfm->spConnId;
#endif /* SZ_FTHA */

         break;
      }

      case EVTSZTRELIND: 
      {
         SztRelInd *relInd;

         relInd = (SztRelInd *)ptr;
         
         szUtilsGetMsgIdx (&evnt, relInd->pdu);
         sztInfo->type.val = evnt;

         /*if(szAcUtlSztUpdConnId(tcCb, &tcCb->stack[tcCb->sp], relInd->spConnId) != ROK)
         {
            RETVALUE(RFAILED);
         }*/ 

         break;
      }

      case EVTSZTRELCFM: 
      {
         SztRelCfm *relCfm;

         relCfm = (SztRelCfm *)ptr;
         
         if (relCfm->relType != SZT_LOCAL_REL)
         {
            szUtilsGetMsgIdx (&evnt, relCfm->pdu);
            sztInfo->type.val = evnt;
         }

         if(szAcUtlSztUpdConnId(tcCb, &tcCb->stack[tcCb->sp], relCfm->spConnId) != ROK)
         {
            RETVALUE(RFAILED);
         } 

         break;
      }

      case EVTSZTDATIND: 
      {
         SztDatEvntInd *datEvnt;

         datEvnt = (SztDatEvntInd *)ptr;
         
         szUtilsGetMsgIdx (&evnt, datEvnt->pdu);
         sztInfo->type.val = evnt;

         if(evnt == SZT_MSG_ID_ERR_IND)
         {
             if(szAcUtlSztGetErrCause(&(datEvnt->pdu->pdu), &causeType, &causeVal) == ROK)
             {
                sztInfo->u.errInd.type   = causeType;
                sztInfo->u.errInd.value  = causeVal;
             }
         }

         szGetIE(&(datEvnt->pdu->pdu), Sztid_eNB_UE_S1AP_ID, &enbId);
         szGetIE(&(datEvnt->pdu->pdu), Sztid_MME_UE_S1AP_ID, &mmeId);
         if(enbId != NULLP)
         {
            sztInfo->u.pduInfo.enbId = ((TknU32 *)enbId)->val;
         }
         if(mmeId != NULLP)
         {
            sztInfo->u.pduInfo.mmeId = ((TknU32 *)mmeId)->val;
         }


         break;
      }

      case EVTSZTENCDECCFM: 
      {
         SztEncDecEvnt *encDecEvnt;

         encDecEvnt = (SztEncDecEvnt *)ptr;
         
         /* TBD: Add code for validation after pdu finalized */

         break;
      }

#ifdef SZ_MME
      case EVTSZTPEERASSOCIND: 
      {
         SztPeerAssocInd *peerAssocInd;

         peerAssocInd = (SztPeerAssocInd *)ptr;

         dynamDstAddrLst = peerAssocInd->dstAddrLst;
         
         break;
      }
#endif
/* sz005.301 Added for S1 Abort request support by UI */
#ifdef SZTV2
      case EVTSZTABORTS1CFM: 
      {
         SztAbortS1   *abortS1;

         abortS1 = (SztAbortS1 *)ptr;

         sztInfo->status = abortS1->abortS1Cfm.status;
         sztInfo->cmInfo.reason = abortS1->abortS1Cfm.reason;
         
         break;
      }
#endif /* SZTV2 */


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
      CMXTA_FREE(szMsg, sizeof(SzAccMsgQElm));
   }
 
   RETVALUE(ret);
} /* end of szAcSztSaveMsg() */
   
/*
*
*       Fun:   szAcSztTstCbFind
*
*       Desc:  
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_sztcb.c
*
*/
#ifdef ANSI
PUBLIC CmXtaTCCb*  szAcSztTstCbFind
(
Void
)
#else
PUBLIC CmXtaTCCb*  szAcSztTstCbFind ()
#endif
{
   TRC2(szAcSztTstCbFind);
 
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
} /* End of szAcSztTstCbFind */


/*
*
*       Fun:   szAcUtlSztCb
*
*       Desc:  This function is used to
*
*       Ret:   None
*
*       Notes: None
*
*       File:  szac_sztcb.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcUtlSztCb
(
CmXtaMsgQElm   *qElm
)
#else
PUBLIC S16 szAcUtlSztCb(qElm)
CmXtaMsgQElm   *qElm;
#endif /* ANSI */
{
   SzAccMsgQElm *szMsg;
   SzAcSztInfo  *sztInfo = NULLP; 
 
   TRC2(szAcUtlSztCb);
 
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztCb(): \n"));

   if(qElm == NULLP)
     RETVALUE(CMXTA_ERR_NONE);
 
   szMsg = (SzAccMsgQElm *)qElm->data;
  
   if(szMsg == NULLP)
     RETVALUE(CMXTA_ERR_NONE);

   sztInfo = &(szMsg->u.sztInfo);
   
   if( sztInfo->type.pres == PRSNT_NODEF)
   {
      switch(sztInfo->type.val)
      {
        case SZAC_AUDIT:
            /* TBD: deallocate any memory allocated using CMXTA_ALLOC */
             break;
        case SZAC_STAIND:
            /* TBD: deallocate any memory allocated using CMXTA_ALLOC */
             break;
       } 
   } 
 
   if (szMsg != NULLP)
   {
      if(szMsg->mBuf != NULLP)
         CMXTA_FREEMBUF(szMsg->mBuf);

      CMXTA_FREE(szMsg, sizeof (SzAccMsgQElm));
      qElm->data = NULLP;
   }
 
   RETVALUE(CMXTA_ERR_NONE);
} /* End of szAcUtlSztCb() */


/********************************************************************30**

         End of file:     szac_sztcb.c@@/main/4 - Mon Jan 10 22:16:01 2011

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
                             2.Fix for kwork.
*********************************************************************91*/
