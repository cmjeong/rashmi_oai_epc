

/********************************************************************20**

     Name:    S1AP Layer

     Type:    C source file

     Desc:    C Source code for upper layer state machine on MME

     File:    sq_smuimme.c

     Sid:      sq_smuimme.c@@/main/4 - Mon Jan 10 22:17:07 2011

     Prg:      sn

*********************************************************************21*/
/* Header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System Services */
#include "cm_tkns.h"       /* common tokens */
#include "cm_hash.h"       /* common structs 1 */
#include "cm_mblk.h"       /* common memory */
#include "cm_llist.h"      /* cm link list */
#include "cm5.h"           /* common structs 3 */
#include "cm_inet.h"       /* common tokens  */
#include "cm_tkns.h"       /* common tokens */
#include "cm_tpt.h"        /* common transport */
#include "sct.h"           /* SCTP Layer */
#include "szt.h"           /* S1AP Upper Interface */
/* sz006.301: Removed un-necessary include files  */
#include "szt_asn.h"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.h"           /* S1AP LM Interface */
#include "sz.h"            /* S1AP Layer */
#include "sz_err.h"            /* S1AP Layer */
#include "cm_pasn.h"
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif

/* Header include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System Services */
#include "cm_tkns.x"       /* common tokens */
#include "cm_hash.x"       /* common structs 1 */
#include "cm_lib.x"        /* common library */
#include "cm_mblk.x"       /* common memory */
#include "cm_llist.x"      /* cm link list */
#include "cm5.x"           /* common structs 3 */
#include "cm_inet.x"       /* common transport */
#include "cm_tpt.x"        /* common transport */
#include"szt_asn.x"        /* common ss7 */
#ifndef SZ_ENC_DEC
#include "szt_pk.x"
#include "szt_unpk.x"
#endif /* SZ_ENC_DEC */
#include "sct.x"           /* SCTP Layer */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* S1AP Upper Interface */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"           /* System Agent */
#endif /* SZ_FTHA */
#include "lsz.x"           /* S1AP LM Interface */
#include "cm_pasn.x"
#include "sz.x"            /* S1AP Layer */

#ifdef SZ_MME
#ifdef __cplusplus
EXTERN "C" {
#endif
/* sz008.301 : Fix to handle Ue context release in connection
 * Establishing state */
PUBLIC S16 szFillTknU32 ARGS((TknU32 *encParam,U32 val));
PUBLIC S16 szFillTknU8 ARGS((TknU8 *encParam,U8 val));
PUBLIC S16 szSmSndUeCtxRlsCmd ARGS((SzConCb *conCb,SzPeerCb *peerCb,S1apPdu *pdu));
#ifdef __cplusplus
}
#endif

PFRAM szSmUiMme[SZ_MAX_MSG_ID][SZ_MAX_ST] = 
{
   /* E-RAB setup request */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* E-RAB setup response */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* E-RAB modify request */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* E-RAB modify response */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* E-RAB release command */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* E-RAB release complete */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* E-RAB release request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Initial Context setup request */
   {
      szSmLclErrState,        /* Idle        */
      szSmSndConnStMsg,      /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Initial context setup response */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Initial context setup failure */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* UE Context release request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* UE Context release command */
   {
      szSmLclErrState,        /* Idle        */
      /* sz008.301 : Fix to handle Ue context release in connection
       * Establishing state */
      szSmSndUeCtxRlsCmd,     /* Connecting  */
      szSmSndUeCtxRlsCmd,     /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* UE Context release complete */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* UE Context Modification request */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* UE Context Modification response */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* UE Context Modification failure */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Initial UE message */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Downlink NAS transport */
   {
      szSmSndIdleStMsg,      /* Idle        */
      szSmSndConnStMsg,      /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Uplink NAS transport */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* NAS non delivery indication */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Error Indication */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmSndEstStMsg,       /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* No Data */
   {
      szSmLclErrState,        /* Idle        */
      szSmLclErrState,        /* Connecting  */
      szSmLclRlsReq,         /* Estbalished */
      szSmLclErrState         /* Releasing   */
   },
   /* Reset */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Reset Acknowledge */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Setup Request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Setup Response */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Setup Fail */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Paging */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Handover Required */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Handover Command */
   {
      szSmLclErrState,      /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmSndEstStMsg,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* Handover Preperation Failure */
   {
      szSmLclErrState,      /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmSndEstStMsg,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* Handover Request */
   {
      szSmSndIdleStMsg,     /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmLclErrState,      /* Established */
      szSmLclErrState       /* Releasing   */
   },
   /* Handover Request Acknowledge */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Handover Request Failure */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Handover Notify */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Path Switch Request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Path Switch Request Acknowledge */
   {
      szSmLclErrState,      /* Idle        */
      szSmSndConnStMsg,     /* Connecting  */
      szSmLclErrState,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* Path Switch Request Failure */
   {
      szSmLclErrState,            /* Idle        */
      szSmSndConnStPathSwReqFail, /* Connecting  */
      szSmLclErrState,            /* Estbalished */
      szSmLclErrState             /* Releasing   */
   },
   /* Handover Cancel */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Handover Cancel Acknowledge */
   {
      szSmLclErrState,      /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmSndEstStMsg,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* ENB Status Transfer */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* MME Status Transfer */
   {
      szSmLclErrState,      /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmSndEstStMsg,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* Deactivate Trace */
   {
      szSmLclErrState,      /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmSndEstStMsg,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* Trace Start */
   {
      szSmLclErrState,      /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmSndEstStMsg,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* Trace Failure Indication */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Location Reporting Control */
   {
      szSmLclErrState,      /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmSndEstStMsg,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* Location Report Failure Indication */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Location Report */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* ENB Configuration Update */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* ENB Configuration Update Acknowledge */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* ENB Configuration Update Failure */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* MME Configuration Update */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* MME Configuration Update Acknowledge */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* MME Configuration Update Failure */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Uplink CDMA 2000 Tunneling */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Downlink CDMA 2000 Tunneling  */
   {
      szSmLclErrState,      /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmSndEstStMsg,      /* Estbalished */
      szSmLclErrState       /* Releasing   */
   },
   /* UE Capability Info */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Overload Start */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Overload Stop */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Write Replace Warning Request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Write Replace Warning Response */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* ENB Information Direct Transfer */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* MME Information Direct Transfer */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Private Message */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* ENB Configuration Transfer */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* MME Configuration Transfer */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Cell Traffic Trace */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Estbalished */
      szSmLclErrMsg         /* Releasing   */
   }
#ifndef S1AP_REL8A0
   ,
   /* Kill Request */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Established */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Kill Response */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Established */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Downlink UE Associated LPPa Transport */
   {
      szSmLclErrState,      /* Idle        */
      szSmLclErrState,      /* Connecting  */
      szSmSndEstStMsg,      /* Established */
      szSmLclErrState       /* Releasing   */
   },
   /* Uplink UE Associated LPPa Transport */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Established */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Downlink non-UE Associated LPPa Transport */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Established */
      szSmLclErrMsg         /* Releasing   */
   },
   /* Uplink non-UE Associated LPPa Transport */
   {
      szSmLclErrMsg,        /* Idle        */
      szSmLclErrMsg,        /* Connecting  */
      szSmLclErrMsg,        /* Established */
      szSmLclErrMsg         /* Releasing   */
   }
#endif /* S1AP_REL8A0 */
};

/*
*
*       Fun:   szSmSndUeCtxRlsCmd
*
*       Desc:  Called to send UE Context release command
*
*       Ret:   ok:     ROK
*              failed: RFAILED
*
*       Notes: None
*
*       File:  sq_smuimme.c
*
*/

#ifdef ANSI
PUBLIC S16 szSmSndUeCtxRlsCmd
(
SzConCb  *conCb,
SzPeerCb *peerCb,
S1apPdu  *pdu
)
#else
PUBLIC S16 szSmSndUeCtxRlsCmd(conCb, peerCb, pdu)
SzConCb  *conCb;
SzPeerCb *peerCb;
S1apPdu  *pdu;
#endif
{
   S16 ret = RFAILED;
#ifdef SZ_MME
   SztUE_S1AP_IDs *szS1apIds;
#endif

   TRC2(szSmSndUeCtxRlsCmd);

#ifdef SZ_MME
   /* sz008.301 : Fix to handle Ue context release in connection
    * Establishing state */
   if (conCb->state == SZ_SMSZ_CONNECTING)
   {
      szGetIE(&pdu->pdu, Sztid_UE_S1AP_IDs, (TknU8**)&szS1apIds);
      szFillTknU8(&(szS1apIds->choice), UE_S1AP_IDS_MME_UE_S1AP_ID); 
      szFillTknU32(&(szS1apIds->val.mME_UE_S1AP_ID), conCb->lclConRefNo); 
   }
#endif /* SZ_MME */
   conCb->state = SZ_SMSZ_RELEASING;

   /* Send decoded data to its User */
   ret = szLiSndToLower(peerCb,conCb, pdu);

   if(ret != ROK)
   {
      if((ret == SZT_CAUSE_PC_TX_SYNTAX_ERR) || 
            (ret == SZT_CAUSE_PC_ABS_SYNTAX_ERR))
      {
         SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.suConnId,
               peerCb->sztSapCb, ret, 0);
      }
      else
      {
         SZ_SEND_LCL_ERR_IND(PRSNT_NODEF, conCb->cd.suConnId,
               peerCb->sztSapCb, SZT_CAUSE_LOWER_LAYER_SND_FAILED, 0);
      }

      SZLOGERROR(ERRCLS_INT_PAR, ESZ162, (ErrVal) conCb->lclConRefNo,
            "szSmSndUeCtxRlsCmd: Lower Interface send failed");
   }

   RETVALUE(ret);
} /* end of szSmSndUeCtxRlsCmd */
#endif

/**********************************************************************
 
         End of file:     sq_smuimme.c@@/main/4 - Mon Jan 10 22:17:07 2011
 
**********************************************************************/

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
/main/4   sz006.301   ve    1. Removed un-necessary include files
/main/4   sz008.301 akaranth 1. Support for source RNC to target RNC.
                             2. Fix to handle Ue context release in connection
                                Establishing state.
*********************************************************************91*/
