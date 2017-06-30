
/********************************************************************20**

     Name:    LTE UE Simulator 

     Type:    C Include file

     Desc:    This file contains the ESM module source code

     File:    ue_esm.c

     Sid:      ue_esm.c@@/main/1 - Sun Mar 28 22:59:23 2010

     Prg:     vp
*********************************************************************21*/

/* Header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#ifndef SS_CAVIUM
#include <pcap.h>
#endif /* SS_CAVIUM */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#include "cm_hash.h"       /* common hash list */
#include "cm_llist.h"      /* common linked list library */
#include "cm_err.h"        /* common error */
#include "cm_lte.h"        /* common LTE */
#ifndef SS_CAVIUM
#include "cm_inet.h"       /* common tokens */
#endif /* SS_CAVIUM */
/* ue007.101: cavium compile warning fix */
#ifdef SS_CAVIUM
#include "cvmx.h"
#include "cvmx-wqe.h"
#endif /* SS_CAVIUM */

#include "cm_pasn.h"       /* common LTE */
#include "nhu_asn.h"
#include "nhu.h"
/* ue003.101: Dedic Bearer Support */
#include "tfu.h"
#include "ue.h"            /* UE Defines */
#include "ue_app.h"        /* UE application includes */
#include "cm_emm.h"        /* UE App - EMM Defines */
#include "cm_esm.h"        /* UE App - ESM Defines */
#include "cm_emm_esm.h"    /* EMM Includes */
#include "ue_err.h"
/* ue002.101: Changes to support MSPD CL */
#ifdef YS_MSPD
#include "LtePhyL2Api.h" /* Phy api file */
/* ue003.101: Dedic Bearer Support */
#include "apidefs.h"     /* Required for ue.x */
#include "resultcodes.h"
#endif

/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"       /* common tokens */
#ifndef SS_CAVIUM
#include "cm_inet.x"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_pasn.x"        /* common LTE */
#include "nhu_asn.x"
#include "ue_nhu_app.x"    /* UE App NHU Interface Includes */

#include "cm_esm.x"        /* UE App - ESM Includes */
#include "cm_emm.x"
#include "cm_emm_esm.x"    /* EMM Includes */
#include "ue_app.x"        /* UE App Includes */
/* ue003.101: Dedic Bearer Support */
#include "tfu.x"
#include "ue.x"
/* ue008.101: Added new header file inclusion*/
#include "ue_nhu_app.h"
/*ue008.101 CRID:ccpu00117391 ERAB RELEASE support*/
PUBLIC S16 ueAppIncDeActvBearerReq ARGS((UeEsmCb *esmCb, UeAppCb *ueAppCb, CmNasEvnt *esmEvnt));
/* Function prototypes for ESM handlers */
/* ue002.101: Multi ue support changes */
PRIVATE S16 ueAppEsmHndlOutPDNConnectReq ARGS((UeEsmCb *esmCb, CmNasEvnt *evnt));
PRIVATE S16 ueAppEsmHndlIncPDNConnectRej ARGS((UeEsmCb *esmCb, CmNasEvnt *evnt,UeAppCb *ueAppCb));
PRIVATE S16 ueAppEsmHndlIncActDefBearerReq ARGS((UeEsmCb *esmCb, CmNasEvnt *evnt,UeAppCb *ueAppCb));
PRIVATE S16 ueAppEsmHndlOutActDefBearerAcc ARGS((UeEsmCb *esmCb, CmNasEvnt *evnt));
PRIVATE S16 ueAppEsmHndlOutActDefBearerRej ARGS((UeEsmCb *esmCb, CmNasEvnt *evnt,UeAppCb *ueAppCb));
PRIVATE S16 ueAppEsmHndlInvEvnt ARGS((UeEsmCb *esmCb, CmNasEvnt *evnt,UeAppCb *ueAppCb));

/* ue009.101 : Added TAU feature */
#ifdef TRACKING_AREA_UPDATE
#ifdef ANSI
PUBLIC S16 ueAppSndTAURequest
(
UeAppCb  *ueAppCb
)
#else
PUBLIC S16 ueAppSndTAURequest(ueAppCb)
UeAppCb  *ueAppCb;
#endif
{
   CmNasEvnt   *tauReqEvnt = NULLP;
   S16 ret; 

   TRC2(ueAppSndTAURequest);

   ret = ueAppUtlBldTAURequest(ueAppCb, &tauReqEvnt);
   if(ROK != ret) 
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE012, (ErrVal)ret,
            " ueAppSndTAURequest: Could not send the TAU Request \n");
      RETVALUE(ret);
   }


   if((ret = ueAppLimSndToLower(tauReqEvnt , C1_ULINFOTFR , ueAppCb)) != ROK) 
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE067, (ErrVal)ret,
         "ueAppEmmTAURequest : Send failed to LI :  TAU request \n");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
}
#endif /* TRACKING_AREA_UPDATE */
/*
 *
 *       Fun:   ueAppEsmHdlIncUeEvnt
 *
 *       Desc:  This function is to handle incoming events
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_esm.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueAppEsmHdlIncUeEvnt
(
CmNasEvnt   *evnt,
UeAppCb     *ueAppCb
)
#else
PUBLIC S16 ueAppEsmHdlIncUeEvnt (evnt,ueAppCb)
CmNasEvnt   *evnt;
UeAppCb     *ueAppCb;
#endif
{
   S16 ret = ROK;
   UeEsmCb  *esmCb = NULLP;
   CmEsmMsg *esmMsg = NULLP;

   TRC2(ueAppEsmHdlIncUeEvnt)

   if(evnt == NULLP)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE077, (ErrVal)ret,
         "ueAppEsmHdlIncUeEvnt: Invalid esm event\n"); 
      RETVALUE(RFAILED);
   }

   UE_DBGP_INFO((UE_PRNTBUF, "ueAppEsmHdlIncUeEvnt: \
         Incoming esm events"));

   esmMsg = evnt->m.esmEvnt;
/* ue002.101: Multi ue support changes */
   ret = ueAppUtlFndEsmCb(&esmCb, esmMsg->prTxnId, UE_ESM_TRANS_KEY,ueAppCb );
   if(ret != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE078, (ErrVal)ret,
         "ueAppEsmHdlIncUeEvnt: ESM Cb is not found\n"); 
      CM_FREE_NASEVNT(&evnt);
      RETVALUE(RFAILED);
   }
   switch(esmMsg->msgType)
   {
      case CM_ESM_MSG_ACTV_DEF_BEAR_REQ:
      {
         ret = ueAppEsmHndlIncActDefBearerReq(esmCb, evnt,ueAppCb);
         break;
      }
      case CM_ESM_MSG_PDN_CONN_REJ:
      {
         ret = ueAppEsmHndlIncPDNConnectRej(esmCb, evnt,ueAppCb);
         break;
      }
/* ue003.101: Dedic Bearer Support */
      case CM_ESM_MSG_ACTV_DED_BEAR_REQ:
      {
         ret = ueAppIncActvDedBearerReq(esmCb,ueAppCb, evnt);
         /* ue007.101: Memory leak fix */
         CM_FREE_NASEVNT(&evnt);
         break;
      }
/*ue008.101 CRID:ccpu00117391 ERAB RELEASE support*/
      case CM_ESM_MSG_DEACTV_BEAR_REQ:
      {
         ret = ueAppIncDeActvBearerReq(esmCb,ueAppCb, evnt);
         /* ue007.101: Memory leak fix */
         CM_FREE_NASEVNT(&evnt);
         break;
      }
      case CM_ESM_MSG_BEAR_RES_MOD_REJ:
      {
         ret = ueAppIncDeActvBearerReq(esmCb,ueAppCb, evnt);
         /* ue007.101: Memory leak fix */
         CM_FREE_NASEVNT(&evnt);
         break;
      }

      default:
      {
         ret = ueAppEsmHndlInvEvnt(esmCb, evnt,ueAppCb);
         break;
      }
   }
   if(ret != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE079, (ErrVal)ret,
         "ueAppEsmHdlIncUeEvnt: Failed to handle esm event\n"); 
      CM_FREE_NASEVNT(&evnt);
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* ueAppEsmHdlIncUeEvnt */

/*
 *
 *       Fun:   ueAppEsmHdlOutUeEvnt
 *
 *       Desc:  This function is to handle outgoing events
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_esm.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueAppEsmHdlOutUeEvnt
(
CmNasEvnt   *evnt,
UeAppCb     *ueAppCb
)
#else
PUBLIC S16 ueAppEsmHdlOutUeEvnt (evnt, ueAppCb)
CmNasEvnt   *evnt;
UeAppCb     *ueAppCb;
#endif
{
   S16 ret = ROK;
   UeEsmCb  *esmCb = NULLP;
   CmEsmMsg *esmMsg = NULLP;

   TRC2(ueAppEsmHdlOutUeEvnt)

   if(evnt == NULLP)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE080, (ErrVal)ret,
         "ueAppEsmHdlOutUeEvnt: Invalid esm event\n"); 
      RETVALUE(RFAILED);
   }

   UE_DBGP_INFO((UE_PRNTBUF, "ueAppEsmHdlOutUeEvnt: \
         Outgoing esm events"));

   esmMsg = evnt->m.esmEvnt;
   /* ue002.101: Multi ue support changes */
   if(esmMsg->msgType != CM_ESM_MSG_PDN_CONN_REQ)
   {
      ret = ueAppUtlFndEsmCb(&esmCb, esmMsg->bearerId, UE_ESM_BID_KEY,ueAppCb);
   }
   else
   {
      ret = ueAppUtlAddEsmCb(&esmCb,ueAppCb);
   }
   if(ret != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE081, (ErrVal)ret,
         "ueAppEsmHdlOutUeEvnt: ESM Cb  not found\n"); 
      CM_FREE_NASEVNT(&evnt);
      RETVALUE(RFAILED);
   }

   switch(esmMsg->msgType)
   {
      case CM_ESM_MSG_PDN_CONN_REQ:
      {
         ret = ueAppEsmHndlOutPDNConnectReq(esmCb, evnt);
         break;
      }
      case CM_ESM_MSG_ACTV_DEF_BEAR_ACC:
      {
         ret = ueAppEsmHndlOutActDefBearerAcc(esmCb, evnt);
         break;
      }
      case CM_ESM_MSG_ACTV_DEF_BEAR_REJ:
      {
         ret = ueAppEsmHndlOutActDefBearerRej(esmCb, evnt,ueAppCb);
         break;
      }
      default:
      {
         ret = ueAppEsmHndlInvEvnt(esmCb, evnt, ueAppCb);
         break;
      }
   }
   if(ret != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE082, (ErrVal)ret,
         "ueAppEsmHdlOutUeEvnt:Failed to handle esm event \n"); 
      CM_FREE_NASEVNT(&evnt);
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* ueAppEsmHdlOutUeEvnt */

/*
 *
 *       Fun:   ueAppEsmHndlOutPDNConnectReq
 *
 *       Desc:  This function is to handle outgoing PDN conn request
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_esm.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueAppEsmHndlOutPDNConnectReq
(
UeEsmCb     *esmCb,
CmNasEvnt   *evnt
)
#else
PRIVATE S16 ueAppEsmHndlOutPDNConnectReq (esmCb, evnt)
UeEsmCb     *esmCb;
CmNasEvnt   *evnt;
#endif
{
   TRC2(ueAppEsmHndlOutPDNConnectReq)

   UE_DBGP_INFO((UE_PRNTBUF, "ueAppEsmHndlOutPDNConnectReq: \
       PDN connectivity request"));

   /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_PENDING;

   /* Updating bearerId and transaction Id to event */
   evnt->m.esmEvnt->bearerId = esmCb->bId;
   evnt->m.esmEvnt->prTxnId = esmCb->tId;

   RETVALUE(ROK);
} /* ueAppEsmHndlOutPDNConnectReq */

/*
 *
 *       Fun:   ueAppEsmHndlIncPDNConnectRej
 *
 *       Desc:  This function is to handle incoming PDN conn reject
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_esm.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueAppEsmHndlIncPDNConnectRej
(
UeEsmCb     *esmCb,
CmNasEvnt   *evnt,
UeAppCb     *ueAppCb
)
#else
PRIVATE S16 ueAppEsmHndlIncPDNConnectRej (esmCb, evnt, ueAppCb)
UeEsmCb     *esmCb;
CmNasEvnt   *evnt;
UeAppCb     *ueAppCb;
#endif
{
   TRC2(ueAppEsmHndlIncPDNConnectRej)

   UE_DBGP_INFO((UE_PRNTBUF, "ueAppEsmHndlIncPDNConnectRej: \
         PDN connectivity reject"));

   /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_INACTIVE;
   /* delete esmCb */
   /* ue002.101: Multi ue support changes */
   ueAppUtlDelEsmCb(esmCb, ueAppCb);

   RETVALUE(ROK);
} /* ueAppEsmHndlIncPDNConnectRej */
/*ue008.101 CRID:ccpu00117391 ERAB RELEASE support*/
/*
*
*       Fun:   ueAppIncModBearerRej
*       
*       Desc:  This function sends Modify 
*              Bearer  Reject message to MME 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppIncModBearerRej 
(
UeEsmCb *esmCb,
UeAppCb *ueAppCb,
CmNasEvnt *esmEvnt
)
#else
PUBLIC S16 ueAppIncModBearerRej(esmCb, ueAppCb, esmEvnt)
UeEsmCb *esmCb;
UeAppCb *ueAppCb;
CmNasEvnt *esmEvnt;
#endif
{
   S16 ret = 0;

  TRC2(ueAppIncModBearerRej);


   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppIncModBearerRej: Modifying Bearer  reject message processing"));
  /*PKD:Nothing to do in this phase*/
   RETVALUE(ret);

} /* End of ueAppIncDeActvBearerReq  */


/* ue004.101:  Bearer Release Support */
/*
*
*       Fun:   ueAppIncDeActvBearerReq
*       
*       Desc:  This function sends DeActivate 
*              Bearer Accept Request message to MME 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppIncDeActvBearerReq
(
UeEsmCb *esmCb,
UeAppCb *ueAppCb,
CmNasEvnt *esmEvnt
)
#else
PUBLIC S16 ueAppIncDeActvBearerReq(esmCb, ueAppCb, esmEvnt)
UeEsmCb *esmCb;
UeAppCb *ueAppCb;
CmNasEvnt *esmEvnt;
#endif
{
   CmNasEvnt   *deactBrAcc = NULLP;
   S16 ret;

  TRC2(ueAppIncDeActvBearerReq);


   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppIncDeActvBearerReq:Sending DeActivate Ded. Bearer Accept request"));

    /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_INACTIVE;

   /* update bearer Id */
   esmCb->bId = esmEvnt->m.esmEvnt->bearerId;
   /* Update bearer context state */
   esmCb->bState = UE_ESM_ST_BEARER_CTXT_INACTIVE;


   /* Pass the esmCb in this function so that it can get the relevant
    * Parameters from esmCb*/
   ret = ueAppUtlBldDeActBerContextAccept(esmCb, ueAppCb, &deactBrAcc);
  
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE011, (ErrVal)ret,
            " ueAppIncDeActvBearerReq: Could not build the DeActivate Ded. Bearer Accept request\n");
      RETVALUE(ret);
   }

   /*Send message to lower layer*/
   if((ret = ueAppLimSndToLower(deactBrAcc, C1_ULINFOTFR, ueAppCb)) != ROK)
   {
      /* ue007.101: Memory leak fix */
      CM_FREE_NASEVNT(&deactBrAcc);
      UELOGERROR(ERRCLS_ADD_RES, EUE070, (ErrVal)ret,
         "ueAppIncActvDedBearerReq: Sending Uplink info failed\n"); 
      RETVALUE(RFAILED);
   }
  /* delete esmCb */
   ueAppUtlDelEsmCb(esmCb, ueAppCb);
 
   RETVALUE(ret);

} /* End of ueAppIncDeActvBearerReq  */


/*
 *
 *       Fun:   ueAppEsmHndlIncActDefBearerReq
 *
 *       Desc:  This function is to handle incoming active def bearer request
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_esm.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueAppEsmHndlIncActDefBearerReq
(
UeEsmCb     *esmCb,
CmNasEvnt   *evnt,
UeAppCb     *ueAppCb
)
#else
PRIVATE S16 ueAppEsmHndlIncActDefBearerReq (esmCb, evnt, ueAppCb)
UeEsmCb     *esmCb;
CmNasEvnt   *evnt;
UeAppCb     *ueAppCb;
#endif
{
#ifdef SS_CAVIUM
   UeInetNetAddr *selfAddr;
#else
   CmInetNetAddr *selfAddr;
#endif /* SS_CAVIUM */
   CmEsmPdnAdd *pAddr;

   TRC2(ueAppEsmHndlIncActDefBearerReq)

   UE_DBGP_INFO((UE_PRNTBUF, "ueAppEsmHndlIncActDefBearerReq: \
         Activate default bearer request"));

   /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_INACTIVE;

   /* update bearer Id */
   esmCb->bId = evnt->m.esmEvnt->bearerId;

   /* ue002.101: Multi ue support changes */
   /* Update pdn address in ue context */
   selfAddr = &(ueAppCb->ueCtxt.selfAddr);
   pAddr = &evnt->m.esmEvnt->u.actReq.pAddr;
   if(pAddr->pdnType == CM_ESM_PDN_IPV4)
   {
      selfAddr->u.ipv4NetAddr = (((U32)(pAddr->addrInfo[0]) << 24) |
            ((U32)(pAddr->addrInfo[1]) << 16) |
            ((U32)(pAddr->addrInfo[2]) << 8) |
            (U32)(pAddr->addrInfo[3]));
   }
   else
   {
#ifdef IPV6_SUPPORTED   
      cmMemcpy((U8 *)&selfAddr->u.ipv6NetAddr, (U8 *)pAddr->addrInfo, pAddr->len);
#endif
   }

   /* ue002.101: Multi ue support changes */
   ueAppUtlMovEsmCbTransToBid (esmCb,ueAppCb);


   RETVALUE(ROK);
} /* ueAppEsmHndlIncActDefBearerReq */

/*
 *
 *       Fun:   ueAppEsmHndlOutActDefBearerAcc
 *
 *       Desc:  This function is to handle outgoing active def bearer accept
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_esm.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueAppEsmHndlOutActDefBearerAcc
(
UeEsmCb     *esmCb,
CmNasEvnt   *evnt
)
#else
PRIVATE S16 ueAppEsmHndlOutActDefBearerAcc (esmCb, evnt)
UeEsmCb     *esmCb;
CmNasEvnt   *evnt;
#endif
{
   TRC2(ueAppEsmHndlOutActDefBearerAcc)

   UE_DBGP_INFO((UE_PRNTBUF, "ueAppEsmHndlOutActDefBearerAcc: \
         Activate default bearer accept"));

   /* Update bearer context state */
   esmCb->bState = UE_ESM_ST_BEARER_CTXT_ACTIVE;

   RETVALUE(ROK);
} /* ueAppEsmHndlOutActDefBearerAcc */

/*
 *
 *       Fun:   ueAppEsmHndlOutActDefBearerRej
 *
 *       Desc:  This function is to handle outgoing active def bearer reject
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_esm.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueAppEsmHndlOutActDefBearerRej
(
UeEsmCb     *esmCb,
CmNasEvnt   *evnt,
UeAppCb     *ueAppCb
)
#else
PRIVATE S16 ueAppEsmHndlOutActDefBearerRej (esmCb, evnt, ueAppCb)
UeEsmCb     *esmCb;
CmNasEvnt   *evnt;
UeAppCb     *ueAppCb;
#endif
{
   TRC2(ueAppEsmHndlOutActDefBearerRej)

   UE_DBGP_INFO((UE_PRNTBUF, "ueAppEsmHndlOutActDefBearerRej: \
         Activate default bearer reject"));

   /* Update bearer context state */
   esmCb->bState = UE_ESM_ST_BEARER_CTXT_INACTIVE;

   /* delete esmCb */
   ueAppUtlDelEsmCb(esmCb, ueAppCb);
   RETVALUE(ROK);
} /* ueAppEsmHndlOutActDefBearerRej */


/* ue003.101: Dedic Bearer Support */
/*
*
*       Fun:   ueAppIncActvDedBearerReq
*       
*       Desc:  This function sends Activate Ded. 
*              Bearer Accept Request message to MME 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppIncActvDedBearerReq
(
UeEsmCb *esmCb,
UeAppCb *ueAppCb,
CmNasEvnt *esmEvnt
)
#else
PUBLIC S16 ueAppIncActvDedBearerReq(esmCb, ueAppCb, esmEvnt)
UeEsmCb *esmCb;
UeAppCb *ueAppCb;
CmNasEvnt *esmEvnt;
#endif
{
   CmNasEvnt   *actDedBrAcc = NULLP;
   S16 ret;

#ifdef LTE_START_UL_DL_DATA
   CellCb *cell;
   UeCb   *ueCb;

   ueUtlFndCell(ueAppCb->cellId,&cell);
   if (cell == NULLP)
   {
      printf("cell not found \n");
      RETVALUE(RFAILED);
   }
   ueUtlFndUe(cell,ueAppCb->ueId,&ueCb);
#endif
   TRC2(ueAppSndActDedBrAcc);


   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppIncActvDedBearerReq:Sending Activate Ded. Bearer Accept request"));

    /* Update procedure transaction state */
   esmCb->pState = UE_ESM_ST_PROC_TXN_INACTIVE;

   /* update bearer Id */
   esmCb->bId = esmEvnt->m.esmEvnt->bearerId;

   /*TODO Update TFT it may be required Later */
   /* Pass the esmCb in this function so that it can get the relevant
    * Parameters from esmCb*/
   ret = ueAppUtlBldActDedBerContextAccept(esmCb, ueAppCb, &actDedBrAcc);
  
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE011, (ErrVal)ret,
            " ueAppIncActvDedBearerReq: Could not build the Activate Ded. Bearer Accept request\n");
      RETVALUE(ret);
   }

   /*Send message to lower layer*/
   if((ret = ueAppLimSndToLower(actDedBrAcc, C1_ULINFOTFR, ueAppCb)) != ROK)
   {
      /* ue007.101: Memory leak fix */
      CM_FREE_NASEVNT(&actDedBrAcc);
      UELOGERROR(ERRCLS_ADD_RES, EUE070, (ErrVal)ret,
         "ueAppIncActvDedBearerReq: Sending Uplink info failed\n"); 
      RETVALUE(RFAILED);
   }
#ifdef LTE_START_UL_DL_DATA
   ueCb->dedDrbEst = TRUE;
#endif
/*ue008.101 CRID:ccpu00117391 ERAB RELEASE support*/
   /*Dedicated Bearer Release Timer has been started*/
   ueAppStartTmr(ueAppCb->cellId,UE_INIT_DED_BEARER_RELEASE_TMR, UE_ESM_DEACTV_BER_TMR_VAL);
   RETVALUE(ret);

} /* End of ueAppIncActvDedBearerReq  */

/*
 *
 *       Fun:   ueAppEsmHndlInvEvnt
 *
 *       Desc:  This function handles the error events.
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_esm.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueAppEsmHndlInvEvnt
(
UeEsmCb     *esmCb,
CmNasEvnt   *evnt,
UeAppCb     *ueAppCb
)
#else
PRIVATE S16 ueAppEsmHndlInvEvnt (esmCb, evnt, ueAppCb )
UeEsmCb     *esmCb;
CmNasEvnt   *evnt;
UeAppCb     *ueAppCb;
#endif
{
   TRC2(ueAppEsmHndlInvEvnt)

   /* Invalid message in the state, returing RFAILED */
   UELOGERROR(ERRCLS_ADD_RES, EUE083, (ErrVal)evnt->m.esmEvnt->msgType,
      "ueAppEsmHndlInvEvnt :Invalid message  \n"); 

   RETVALUE(RFAILED);
} /* ueAppEsmHndlInvEvnt */

/*
 *
 *       Fun:   ueAppUtlAddEsmCb
 *
 *       Desc:  This function creates a ESM Cb
 *
 *       Ret:   ROK      - ok
 *
 *       Notes: None
 *
 *       File:  ue_esm.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueAppUtlAddEsmCb
(
UeEsmCb   **esmCb,
UeAppCb    *ueAppCb
)
#else
PUBLIC S16 ueAppUtlAddEsmCb (esmCb,ueAppCb)
UeEsmCb   **esmCb;
UeAppCb    *ueAppCb;
#endif
{
   UeEsmCb *newEsmCb;
   U8 i = 0;

   TRC2(ueAppUtlAddEsmCb)

   UE_DBGP_INFO((UE_PRNTBUF, "ueAppUtlAddEsmCb: \
         Adding ESM Cb"));

   /* Allocate esmCb */
   UEAPP_ALLOC(&newEsmCb, sizeof(UeEsmCb));

   if(newEsmCb == NULLP)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE084, (ErrVal)0,
         "ueAppUtlAddEsmCb : Failed to allocate memory\n"); 
      RETVALUE(RFAILED);
   }

   /* find out freely available transId from 1 to 254 */
   /* ue002.101: Multi ue support changes */
   for(i=1; i < CM_ESM_MAX_BEARER_ID; i++)
   {
      if(ueAppCb->esmTList[i] == NULLP)
      {
         newEsmCb->tId = i;
         ueAppCb->esmTList[i] = newEsmCb;
         break;
      }
   }
   if(newEsmCb->tId == 0)
   {
      UEAPP_FREE(newEsmCb, sizeof(UeEsmCb));
      UELOGERROR(ERRCLS_ADD_RES, EUE085, (ErrVal)0,
         "ueAppUtlAddEsmCb : Failed to get available transId  \n"); 
      RETVALUE(RFAILED);
   }

   UE_DBGP_INFO((UE_PRNTBUF, "ueAppUtlAddEsmCb: \
            Esm transaction Id: (%d)\n", newEsmCb->tId));
  newEsmCb->bState = UE_ESM_ST_BEARER_CTXT_INACTIVE;
   newEsmCb->pState = UE_ESM_ST_PROC_TXN_INACTIVE;

   *esmCb = newEsmCb;
   RETVALUE(ROK);
} /* end of ueAppUtlAddEsmCb */

/*
 *
 *       Fun:   ueAppUtlFndEsmCb
 *
 *       Desc:  This function finds a  ESM Cb.
 *
 *       Ret:   ROK      - ok
 *
 *       Notes: None
 *
 *       File:  ue_esm.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueAppUtlFndEsmCb
(
UeEsmCb        **esmCb,
U8               key,
UeAppEsmKeyType  type,
UeAppCb         *ueAppCb
)
#else
PUBLIC S16 ueAppUtlFndEsmCb (esmCb, key,type, ueAppCb)
UeEsmCb        **esmCb;
U8               key;
UeAppEsmKeyType  type;
UeAppCb         *ueAppCb;
#endif
{

   TRC2(ueAppUtlFndEsmCb)

   *esmCb = NULLP;
   /* Checking for valid trans id, valid = 1 to 254 */
   if(((key < UE_ESM_TRANS_ID_INDX) ||
            (key > UE_ESM_MAX_TRANS_ID)))
      RETVALUE(RFAILED);

   if(type == UE_ESM_TRANS_KEY )
   {
      *esmCb = ueAppCb->esmTList[key];
   }
   else if(type == UE_ESM_BID_KEY)
   {
      *esmCb = ueAppCb->esmBList[key];
   }
   UE_DBGP_INFO((UE_PRNTBUF, "ueAppUtlFndEsmCb: \
            Esm Cb not found for transaction Id (%d)", key));

   if(*esmCb)
   {
      RETVALUE(ROK);
   }
   RETVALUE(RFAILED);

} /* end of ueAppUtlFndEsmCb */

/* 
 *
 *       Fun:   ueAppUtlMovEsmCbTransToBid
 *
 *       Desc:  This function moves the ESM control block
 *              from Transaction list to Bid.
 * 
 *       Ret:   ROK      - ok
 * 
 *       Notes: None
 * 
 *       File:  ue_esm.c
 * 
 */
#ifdef ANSI
PUBLIC S16 ueAppUtlMovEsmCbTransToBid
(
UeEsmCb      *esmCb,
UeAppCb      *ueAppCb
)
#else
PUBLIC S16 ueAppUtlMovEsmCbTransToBid (esmCb, ueAppCb)
UeEsmCb      *esmCb;
UeAppCb      *ueAppCb;
#endif
{

   TRC2(ueAppUtlMovEsmCbTransToBid)
    
   UE_DBGP_INFO((UE_PRNTBUF,"ueAppUtlMovEsmCbTransToBid: Moving\
      EsmCb to bid list"));

/* ue002.101: Multi ue support changes */
   ueAppCb->esmTList[esmCb->tId] = NULLP;   
   if(!ueAppCb->esmBList[esmCb->bId])
   {
      ueAppCb->esmBList[esmCb->bId] =  esmCb;
   }
   else
   {
      UE_DBGP_INFO((UE_PRNTBUF,"The bid Entry Exist in the List bid(%d)\n",esmCb->bId));
   }

   RETVALUE(ROK);
} /* end of ueAppUtlFndEsmCb */

/*
 *
 *       Fun:   ueAppUtlDelEsmCb
 *
 *       Desc:  This function deletes the esmCb.
 *             
 *
 *       Ret:   ROK      - ok
 *
 *       Notes: None
 *
 *       File:  ue_esm.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueAppUtlDelEsmCb
(
UeEsmCb  *esmCb,
UeAppCb *ueAppCb
)
#else
PUBLIC S16 ueAppUtlDelEsmCb (esmCb,ueAppCb)
UeEsmCb  *esmCb;
UeAppCb *ueAppCb;
#endif
{

   TRC2(ueAppUtlDelEsmCb)

   if(NULLP == esmCb)
   {
      /* Debug print here */
      UELOGERROR(ERRCLS_ADD_RES, EUE086, (ErrVal)0,
         "ueAppUtlDelEsmCb: NULL ESM Cb is received\n"); 
      RETVALUE(RFAILED);
   }

   UE_DBGP_INFO((UE_PRNTBUF, "ueAppUtlDelEsmCb: \
            Deleting Esm Cb for transaction Id: (%d)\n", esmCb->bId));

/* ue002.101: Multi ue support changes */
   if(esmCb->tId < CM_ESM_MAX_BEARER_ID)
   {
      ueAppCb->esmTList[esmCb->tId] = NULLP;
   }
   if(esmCb->bId < CM_ESM_MAX_BEARER_ID)
   {
      ueAppCb->esmBList[esmCb->bId] = NULLP;
   }

   UEAPP_FREE(esmCb, sizeof(UeEsmCb));
   RETVALUE(ROK);
} /* end of ueAppUtlDelEsmCb */


/********************************************************************30**

         End of file:     ue_esm.c@@/main/1 - Sun Mar 28 22:59:23 2010

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
/main/1      ---      vp              1. Initial Release
/main/1+   ue002.101  sv              1. Multi ue support changes.
/main/1+   ue003.101  rp              1. Dedicated Bearer Support changes.
/main/1+   ue007.101  rk              1. Memory leak fix.
                                      2. Cavium compile warning fix
/main/1+   ue008.101  ragrawal        1. CRID:ccpu00117391 ERAB_RELEASE feature. 
                                      2. Added new header file inclusion.
/main/1+   ue009.101  akaranth        1. Added TAU feature. 
*********************************************************************91*/
