/********************************************************************20**
 
     Name:     LTE UESIM - Sample Application Utilities
  
     Type:     C source file
  
     Desc:     C source code for UE Sample Application Utilities
  
     File:     ue_app_utl.c
  
     Sid:      ue_app_utl.c@@/main/1 - Sun Mar 28 22:59:21 2010
  
     Prg:      vp 
  
*********************************************************************21*/

/************************************************************************
 
     Note: 
 
************************************************************************/


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

#include "ue_app.h"        /* UE application includes */
#include "cm_emm.h"        /* UE App - EMM Defines */
#include "cm_esm.h"        /* UE App - ESM Defines */
#include "cm_emm_esm.h"    /* EMM Includes */
#include "tfu.h"
#include "ue.h"
#include "ue_err.h"

/* ue002.101: Changes for supporting MSPD CL */
#ifdef YS_MSPD
#include "LtePhyL2Api.h" /* Phy api file */
#include "apidefs.h"     /* Phy api file */
#include "resultcodes.h" /* Phy api file */
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
/* ue005.101: Added support for UeCapability */
#ifdef UE_RAD_CAP
#include "ue_nh_db.x"
#endif
#include "ue_nhu_app.x"    /* NHU Interface includes */
#include "cm_esm.x"        /* UE App - ESM Includes */
#include "cm_emm.x"        /* UE App - EMM Includes */
#include "cm_emm_esm.x"    /* EMM Includes */
#include "ue_app.x"        /* UE App Includes */
#include "tfu.x"
#include "ue.x"

/* ue009.101 : Added TAU feature */
#ifdef TRACKING_AREA_UPDATE
#ifdef ANSI
PUBLIC S16 ueAppUtlBldTAURequest
(
 UeAppCb *ueCb,
 CmNasEvnt **ueEvt
)
#else

PUBLIC S16 ueAppUtlBldTAURequest(ueCb, ueEvt)
UeAppCb *ueCb;
CmNasEvnt **ueEvt;
#endif
{

/*   CmEmmTAURequest  *tacReq; */
   CmEmmMsg* emmMsg;
   S16 ret; 
   
   TRC2(ueAppUtlBldTAURequest);


   if(ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;

   /* Fill header information*/
   /*protocol Discrimnator */
   emmMsg->protDisc = CM_EMM_PD;
   /* Security header Typ */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   /* Tracking are update accept message Identity */
   emmMsg->msgId = CM_EMM_MSG_TAU_REQ;

   /* EPS update type */
   emmMsg->u.tauReq.epsUpdType.pres = TRUE;

   /* if actv == 1 Bearer establishment required
    *    actv == 0 No bearer establishment requested
    */
   emmMsg->u.tauReq.epsUpdType.actv = FALSE;
   emmMsg->u.tauReq.epsUpdType.type = CM_EMM_UPD_CMB_TALA_UPD;

   /* NAS key set identifier */
   emmMsg->u.tauReq.nasKsi.pres = TRUE;
   emmMsg->u.tauReq.nasKsi.id = CM_EMM_NONAS_KEY_AVAILABLE;
   emmMsg->u.tauReq.nasKsi.tsc = CM_EMM_NASKEYSID_NATIVE_SEC;

   /* EPS mobile identity */
   emmMsg->u.tauReq.epsMi.pres = TRUE;
   emmMsg->u.tauReq.epsMi.type = CM_EMM_MID_TYPE_IMSI;
   emmMsg->u.tauReq.epsMi.len  = 15;
   emmMsg->u.tauReq.epsMi.evenOddInd = (((emmMsg->u.tauReq.epsMi.len) % 2) != 0)?(UE_ODD):(UE_EVEN);
   cmMemcpy((U8 *)&emmMsg->u.tauReq.epsMi.u.imsi.id, 
                           (U8 *)&ueCb->ueCtxt.ueImsi, emmMsg->u.tauReq.epsMi.len);
   RETVALUE(ROK);
}
#endif /* TRACKING_AREA_UPDATE */

/* 
*
*       Fun:   ueAppUtlBldAttachReq
*       
*       Desc:  This is build a Attach Request that is to be sent to
*              the core network.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldAttachReq
(
 UeAppCb *ueCb,
 CmNasEvnt **ueEvt,
 U8      miType
)
#else
PUBLIC S16 ueAppUtlBldAttachReq(ueCb, ueEvt, miType)
UeAppCb *ueCb;
CmNasEvnt **ueEvt;
U8      miType;
#endif
{
    CmEmmAttachRequest  *attachReq;
    CmEmmMsg* emmMsg;
    S16 ret;

    TRC2(ueAppUtlBldAttachReq);

   UE_DBGP_INFO((UE_PRNTBUF,
        "ueAppUtlBldAttachReq:Building a Attach Request"));

    if(ueEvt == NULLP)
    {
       RETVALUE(RFAILED);
    }
    /* Allocate memory for pdu */
    CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

    if(*ueEvt == NULLP)
    {
       RETVALUE(RFAILED);
    }
    if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
    {
       CM_FREE_NASEVNT(ueEvt);
       RETVALUE(RFAILED);
    }

    (*ueEvt)->m.emmEvnt = emmMsg;
    attachReq = &((*ueEvt)->m.emmEvnt->u.atchReq);

    /*Fill header information*/

    /* Security header type is "Plain NAS message, not security protected" */
    emmMsg->protDisc = CM_EMM_PD;
    emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
    emmMsg->msgId = CM_EMM_MSG_ATTACH_REQ;

    /* Fill mandatory IEs */
    /*EPS attach type IE*/
    attachReq->epsAtchType.pres = TRUE;
    attachReq->epsAtchType.type = CM_EMM_ATCH_RES_EPS_ONLY;

    /*NAS key set identifier IE*/
    attachReq->nasKsi.pres = TRUE;
    /* ue008.101: Changed for IDCC CR CM_EMM_NASKEYSID_NATIVE_SEC 
     * and IDCC CR CM_EMM_NONAS_KEY_AVAILABLE */
    attachReq->nasKsi.id = CM_EMM_NONAS_KEY_AVAILABLE; 
    attachReq->nasKsi.tsc = CM_EMM_NASKEYSID_NATIVE_SEC;
    

    switch(miType)
    {
      case CM_EMM_MID_TYPE_IMSI:
      {
         attachReq->epsMi.pres = TRUE;
         attachReq->epsMi.type = CM_EMM_MID_TYPE_IMSI;
         attachReq->epsMi.len = 15;
         attachReq->epsMi.evenOddInd = (((attachReq->epsMi.len)%2) != 0)? \
                                        (UE_ODD):(UE_EVEN);
         cmMemcpy((U8 *)&attachReq->epsMi.u.imsi.id, 
                  (U8 *)&ueCb->ueCtxt.ueImsi, attachReq->epsMi.len);
         break;
      }
      case CM_EMM_MID_TYPE_GUTI:
      {
         attachReq->epsMi.pres = TRUE;
         attachReq->epsMi.type = CM_EMM_MID_TYPE_GUTI;
         attachReq->epsMi.evenOddInd = UE_EVEN;
         attachReq->epsMi.len = sizeof(GUTI);
         cmMemcpy((U8 *)&attachReq->epsMi.u.guti, (U8 *)&ueCb->ueCtxt.ueGuti, 
              sizeof(GUTI));
          break;
      }
      default:
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE029, (ErrVal)miType,
            "ueAppUtlBldAttachReq : Invalid miType\n"); 
          break;
      }
   }

    /*Copy UE capabilities from UE Cb*/
    /* ue002.101:kworks_fix */
    cmMemcpy((U8 *) &attachReq->ueNwCap, (U8 *)&ueCb->ueCtxt.ueNwCap,
             sizeof(CmEmmUeNwCap));
    
    /*ESM message container IE*/

    if((ret = ueAppUtlBldPdnConReq(ueCb, &(attachReq->esmEvnt))) != ROK)
    {
       CM_FREE_NASEVNT(ueEvt);
       RETVALUE(RFAILED);
    }
    
    RETVALUE(ROK);
}
/* ue003.101: bld service req msg */
/* 
*
*       Fun:   ueAppUtlBldServiceReq
*       
*       Desc:  This is build a Service Request that is to be sent to
*              the core network.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldServiceReq
(
 UeAppCb *ueCb,
 CmNasEvnt **ueEvt
)
#else
PUBLIC S16 ueAppUtlBldServiceReq(ueCb, ueEvt)
UeAppCb *ueCb;
CmNasEvnt **ueEvt;
#endif
{
    CmEmmServiceReq  *serviceReq;
    CmEmmMsg* emmMsg;

    TRC2(ueAppUtlBldServiceReq);

    UE_DBGP_INFO((UE_PRNTBUF,
        "ueAppUtlBldServiceReq:Building a Service Request"));

    /* Allocate memory for pdu */
    CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

    if(*ueEvt == NULLP)
    {
       RETVALUE(RFAILED);
    }
    if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
    {
       CM_FREE_NASEVNT(ueEvt);
       RETVALUE(RFAILED);
    }

    (*ueEvt)->m.emmEvnt = emmMsg;
    serviceReq = &((*ueEvt)->m.emmEvnt->u.srvReq);

    /*Fill header information*/

    /* Security header type is "Plain NAS message, not security protected" */
    emmMsg->protDisc = CM_EMM_PD;
    emmMsg->secHdrType = 12;
    emmMsg->msgId = CM_EMM_MSG_SERVICE_REQ;

    /* Fill mandatory IEs */
    /* KSI and Sequence Number IE*/
    serviceReq->ksiSeqNum.pres = TRUE;
    serviceReq->ksiSeqNum.seqNum = 0;
    /* ue008.101: Changed for IDCC CM_EMM_NASKEYSID_NATIVE_SEC*/
    serviceReq->ksiSeqNum.Ksi    = CM_EMM_NONAS_KEY_AVAILABLE; 

    /*Short MAC IE*/
    serviceReq->shortMac.pres = TRUE;
    serviceReq->shortMac.val  = 0;

    RETVALUE(ROK);
} /* ueAppUtlBldServiceReq */

/* 
*
*       Fun:   ueAppUtlBldAttachComplete
*       
*       Desc:  This is build a Attach Complete that is to be sent to
*              the core network.
*        
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldAttachComplete
(
 UeAppCb *ueCb,
 CmNasEvnt **ueEvt
)
#else

PUBLIC S16 ueAppUtlBldAttachComplete(ueCb, ueEvt)
UeAppCb *ueCb;
CmNasEvnt **ueEvt;
#endif 
{
   CmEmmAttachComplete  *attachCmplt;
   CmEmmMsg* emmMsg;
   S16 ret;

   TRC2(ueAppUtlBldAttachComplete);

   UE_DBGP_INFO((UE_PRNTBUF,
        "ueAppUtlBldAttachComplete:Building a Attach Complete"));

   if(ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   attachCmplt = &((*ueEvt)->m.emmEvnt->u.atchCmp);

   /* Fill header information*/

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId = CM_EMM_MSG_ATTACH_CMP;
   emmMsg->protDisc = CM_EMM_PD;

   /* Fill mandatory IEs */
   /* ESM message container IE*/

   if((ret = ueAppUtlBldActDefltBerContextAccept(ueCb, &(attachCmplt->esmEvnt))) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);
   
}


/* 
*
*       Fun:   ueAppUtlBldIdentityResp
*       
*       Desc:  This is build a Identity Response that is to be sent to
*              the core network.
*        
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldIdentityResp
(
 UeAppCb *ueCb,
 CmNasEvnt **ueEvt
)
#else

PUBLIC S16 ueAppUtlBldIdentityResp(ueCb, ueEvt)
UeAppCb *ueCb;
CmNasEvnt **ueEvt;
#endif 
{
   CmEmmIdRsp  *identityRsp;
   CmEmmMsg* emmMsg;

   TRC2(ueAppUtlBldIdentityResp);

   UE_DBGP_INFO((UE_PRNTBUF,
        "ueAppUtlBldIdentityResp:Building a Identity response for Ue"));

   if(ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   identityRsp = &((*ueEvt)->m.emmEvnt->u.idRsp);

   /* Fill header information*/

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId = CM_EMM_MSG_ID_RSP;
   emmMsg->protDisc = CM_EMM_PD;

   /* Fill mandatory IEs */
   /* Mobile identity IE*/
   identityRsp->msId.pres = TRUE;
   identityRsp->msId.len = cmStrlen(ueCb->ueCtxt.ueImsi);
   identityRsp->msId.type = CM_EMM_MID_TYPE_IMSI;
   identityRsp->msId.evenOddInd = (((identityRsp->msId.len)%2) != 0)? \
                                   (UE_ODD):(UE_EVEN);
   cmMemcpy(identityRsp->msId.u.imsi.id, ueCb->ueCtxt.ueImsi, 
            identityRsp->msId.len);
   
   RETVALUE(ROK);
   
}

/* 
*
*       Fun:   ueAppUtlBldAuthResp
*       
*       Desc:  This is build a Authentication Response that is to be sent to
*              the core network.
*        
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldAuthResp
(
UeAppCb *ueCb,
CmNasEvnt **ueEvt,
CmEmmAuthPrmRES *authParmRes
)
#else
PUBLIC S16 ueAppUtlBldAuthResp(ueCb, ueEvt, authParmRes)
UeAppCb *ueCb;
CmNasEvnt **ueEvt;
CmEmmAuthPrmRES *authParmRes;
#endif 
{
   CmEmmAuthRsp  *authRsp;
   CmEmmMsg* emmMsg;

   TRC2(ueAppUtlBldAuthResp);

   UE_DBGP_INFO((UE_PRNTBUF,
        "ueAppUtlBldAuthResp:Building a  Authentication response for Ue"));

   if(ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   authRsp = &((*ueEvt)->m.emmEvnt->u.authRsp);

   /* Fill header information*/

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->protDisc = CM_EMM_PD;
   emmMsg->msgId = CM_EMM_MSG_AUTH_RSP;

   /* Fill mandatory IEs */
   /* Auth response parameter*/
   cmMemcpy((U8 *)&authRsp->RES, (U8 *)authParmRes, sizeof(CmEmmAuthPrmRES));

   RETVALUE(ROK);
}

/* 
*
*       Fun:   ueAppUtlBldSecModeComplete
*       
*       Desc:  This is build a Security mode complete message.
*        
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldSecModComplete
(
 UeAppCb *ueCb,
 CmNasEvnt **ueEvt
)
#else

PUBLIC S16 ueAppUtlBldSecModComplete(ueCb, ueEvt)
UeAppCb *ueCb;
CmNasEvnt **ueEvt;
#endif 
{
   CmEmmSecModeCmp  *secModeCmp;
   CmEmmMsg* emmMsg;

   TRC2(ueAppUtlBldSecModComplete);

   UE_DBGP_INFO((UE_PRNTBUF,
        "ueAppUtlBldSecModComplete:Building Security Mode complete  for Ue"));

   if(ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
        RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   secModeCmp = &((*ueEvt)->m.emmEvnt->u.secModCmp);

   /*Fill header information*/

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId = CM_EMM_MSG_SEC_MODE_CMP;
   emmMsg->protDisc = CM_EMM_PD;


   RETVALUE(ROK);
   
}

/* 
*
*       Fun:   ueAppUtlBldDetachReq
*       
*       Desc:  This is build a Detach Request that is to be sent to
*              the core network.
*        
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldDetachReq
(
 UeAppCb *ueCb,
 CmNasEvnt **ueEvt,
 U8     detachType,
 U8     miType
)
#else

PUBLIC S16 ueAppUtlBldDetachReq(ueCb, ueEvt, detachType, miType)
UeAppCb *ueCb;
CmNasEvnt **ueEvt;
U8     detachType;
U8     miType;
#endif 
{
   CmEmmDetachReq  *detachReq;
   CmEmmMsg* emmMsg;

   TRC2(ueAppUtlBldDetachReq);

   UE_DBGP_INFO((UE_PRNTBUF,
        "ueAppUtlBldDetachReq:Building Detach Request  for Ue"));

   if(ueEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (ueEvt, CM_EMM_PD);

   if(*ueEvt == NULLP)
   {
      /* ue007.101: Debug print added */
      UELOGERROR(ERRCLS_ADD_RES, EUE030, (ErrVal)0,
            "ueAppUtlBldDetachReq: Failed to allocate memory to NAS event\n"); 
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*ueEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      /* ue007.101: Debug print added */
      UELOGERROR(ERRCLS_ADD_RES, EUE030, (ErrVal)0,
            "ueAppUtlBldDetachReq: Failed to allocate memory to EMM msg\n"); 
      CM_FREE_NASEVNT(ueEvt);
      RETVALUE(RFAILED);
   }

   (*ueEvt)->m.emmEvnt = emmMsg;
   detachReq = &((*ueEvt)->m.emmEvnt->u.dtchReq);

   /*Fill header information*/

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId = CM_EMM_MSG_DETACH_REQ;
   emmMsg->protDisc = CM_EMM_PD;

   /* Fill mandatory IEs */
   /*detach type IE*/
   detachReq->detchType.pres = TRUE;
   detachReq->detchType.type = detachType; 
   detachReq->detchType.switchOff = UE_DETACH_SWITCHOFF;

   /*NAS key set identifier IE*/
   detachReq->nasKsi.pres = TRUE; 
   /* ue008.101: Changed for IDCC CR CM_EMM_NASKEYSID_NATIVE_SEC
    * and *CM_EMM_NONAS_KEY_AVAILABLE */
   detachReq->nasKsi.id = CM_EMM_NONAS_KEY_AVAILABLE; 
   detachReq->nasKsi.tsc = CM_EMM_NASKEYSID_NATIVE_SEC; 

   detachReq->epsMi.pres = TRUE;   
   switch(miType)
   {
      case CM_EMM_MID_TYPE_IMSI:
      {
         detachReq->epsMi.type = CM_EMM_MID_TYPE_IMSI;
         detachReq->epsMi.len = cmStrlen(ueCb->ueCtxt.ueImsi);
         detachReq->epsMi.evenOddInd = (((detachReq->epsMi.len)%2) != 0)?UE_ODD:UE_EVEN;
         cmMemcpy((U8 *)&detachReq->epsMi.u.imsi.id, (U8 *)&ueCb->ueCtxt.ueImsi, detachReq->epsMi.len);
         break;
      }
      case CM_EMM_MID_TYPE_GUTI:
      {
         detachReq->epsMi.type = CM_EMM_MID_TYPE_GUTI;
         detachReq->epsMi.evenOddInd = UE_EVEN;
         detachReq->epsMi.len  = sizeof(GUTI);
         cmMemcpy((U8 *)&detachReq->epsMi.u.guti, (U8 *)&ueCb->ueCtxt.ueGuti, sizeof(GUTI));
         break;
      }
      default:
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE030, (ErrVal)miType,
            "ueAppUtlBldDetachReq: Invalid miType\n"); 
         break;
      }
   }
   
   /*If GUTI is allocated to UE use it to include, otherwise use IMSI*/

   RETVALUE(ROK);
   
}

/* ue007.101: building Detach Accpet */
/* 
 *
 *       Fun:   ueAppUtlBldDetachAcc
 *       
 *       Desc:  This is build a Detach Accept that is to be sent to
 *              the core network.
 *        
 *       Ret:   ROK
 *       
 *       Notes: None
 *              
 *       File:  ue_app_utl.c
 *       
 */
#ifdef ANSI
PUBLIC S16 ueAppUtlBldDetachAcc
(
 UeAppCb   *ueCb,
 CmNasEvnt **detAccEvt
 )
#else

PUBLIC S16 ueAppUtlBldDetachAcc(ueCb, detAccEvt)
   UeAppCb    *ueCb;
   CmNasEvnt  **detAccEvt;
#endif 
{
   CmEmmMsg* emmMsg;
   CmEmmDetachAcc  *detachAcc;

   TRC2(ueAppUtlBldDetachAcc);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppUtlBldDetachAcc:Building Detach Accept  for Ue"));

   /* Allocate memory for pdu */
   CM_ALLOC_NASEVNT (detAccEvt, CM_EMM_PD);

   if(*detAccEvt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (cmGetMem(&((*detAccEvt)->memCp), sizeof(CmEmmMsg), (Ptr *)&emmMsg) != ROK)
   {
      CM_FREE_NASEVNT(detAccEvt);
      RETVALUE(RFAILED);
   }

   (*detAccEvt)->m.emmEvnt = emmMsg;
   detachAcc = &((*detAccEvt)->m.emmEvnt->u.dtchAcc);

   /*Fill header information*/

   /* Security header type is "Plain NAS message, not security protected" */
   emmMsg->secHdrType = CM_EMM_SEC_HDR_TYPE_PLAIN_NAS_MSG;
   emmMsg->msgId = CM_EMM_MSG_DETACH_ACC;
   emmMsg->protDisc = CM_EMM_PD;

   RETVALUE(ROK);
}

/* 
*
*       Fun:   ueAppUtlBldPdnConReq
*       
*       Desc:  This is build a PDN Connectivity Request that is to be sent to
*              the core network.
*        
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldPdnConReq
(
 UeAppCb *ueCb,
 CmNasEvnt **esmEvnt
 )
#else
PUBLIC S16 ueAppUtlBldPdnConReq(ueCb, esmEvnt)
 UeAppCb *ueCb;
 CmNasEvnt **esmEvnt;
#endif
{
   CmEsmMsg    *msg = NULLP;

   TRC2(ueAppUtlBldPdnConReq);

   UE_DBGP_INFO((UE_PRNTBUF,
        "ueAppUtlBldPdnConReq:Building PDN Connection Request for Ue"));

   if(ueCb == NULLP || esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   } 
 
   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);
   if (*esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   msg->protDisc = CM_ESM_PD;
   (*esmEvnt)->m.esmEvnt = msg;

   /* Fill ESM PDN connectivity request message */

   /*Fill mandatory IE's*/
   /* EPS barer ID IE*/
   msg->bearerId = 0;

   /* Procedure transaction identity IE*/
   msg->prTxnId  = 0;

   /* PDN connectivity request message idenmtity*/
   msg->msgType  = CM_ESM_MSG_PDN_CONN_REQ;

   /* Request type IE*/  
   msg->u.conReq.reqType.pres = TRUE;
   msg->u.conReq.reqType.val = CM_ESM_REQTYPE_INIT;
 
   /* PDN type IE*/
   msg->u.conReq.pdnType.pres = TRUE;
   msg->u.conReq.pdnType.val = CM_ESM_PDN_IPV4;

   RETVALUE(ROK);

}

/* 
*
*       Fun:   ueAppUtlBldActDefltBerContextAccept
*       
*       Desc:  This is build a Active Default Bearer Context Accept
*              message that is to be sent to the core network.
*        
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldActDefltBerContextAccept
(
 UeAppCb *ueCb,
 CmNasEvnt **esmEvnt
)
#else
PUBLIC S16 ueAppUtlBldActDefltBerContextAccept(ueCb, esmEvnt)
 UeAppCb *ueCb;
 CmNasEvnt **esmEvnt;
#endif
{

   CmEsmMsg    *msg = NULLP;

   TRC2(ueAppUtlBldActDefltBerContextAccept);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlBldActDefltBerContextAccept:Building Active Default Bearer Context Accept"));

   if(ueCb == NULLP || esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   } 
 
   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);
 
   if (*esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   (*esmEvnt)->m.esmEvnt = msg;
   msg->protDisc = CM_ESM_PD;

   /* Fill ESM Acticate defauld berer context accept message */
   /* Fill mandatory IE's*/
 
   /* EPS barer ID IE*/
   msg->bearerId = UE_APP_EPS_DFLT_BEARER_INDX;
     
   /* Procedure transaction identity IE*/   
   msg->prTxnId  = ueCb->esmBList[UE_APP_EPS_DFLT_BEARER_INDX]->tId;
  
   /* Activate defaule EPS barer context accept*/
   msg->msgType  = CM_ESM_MSG_ACTV_DEF_BEAR_ACC;

   RETVALUE(ROK);
}
/* 
*
*       Fun:   ueAppUtlBldActDefltBerContextRej
*       
*       Desc:  This is build a Active Default Bearer Context Reject
*              message that is to be sent to the core network.
*        
*       Ret:   ROK 
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/ 
#ifdef ANSI
PUBLIC S16 ueAppUtlBldActDefltBerContextRej
(
 UeAppCb *ueCb,
 CmNasEvnt **esmEvnt,
 U8      cause,
 U8      bId,
 U8      tId
)
#else
PUBLIC S16 ueAppUtlBldActDefltBerContextRej(ueCb, esmEvnt, cause, bId, tId)
 UeAppCb *ueCb;
 CmNasEvnt **esmEvnt;
 U8      cause;
 U8      bId;
 U8      tId;
#endif
{
   CmEsmMsg    *msg = NULLP;

   TRC2(ueAppUtlBldActDefltBerContextRej);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlBldActDefltBerContextRej:Building Active Default Bearer Context Reject"));

   if(ueCb == NULLP || *esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   } 
 
   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);
   if (*esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   (*esmEvnt)->m.esmEvnt = msg;

   /* Fill ESM Activate defauld berer context reject message */
   /* Fill mandatory IE's*/
 
   /* EPS barer ID IE*/
   msg->bearerId = bId; 
     
   /* Procedure transaction identity IE*/   
   msg->prTxnId  = tId; 
  
   /* Activate defaule EPS barer context accept*/
   msg->msgType  = CM_ESM_MSG_ACTV_DEF_BEAR_REJ;

   /* ESM cause IE*/
   msg->u.actRej.cause.pres = TRUE;
   msg->u.actRej.cause.val  = cause;

   RETVALUE(ROK);

}
/*ue008.101 CRID:ccpu00117391 ERAB RELEASE support*/
/* 
*
*       Fun:   ueAppUtlBldDeActBerContextAccept
*       
*       Desc:  This is build a Active Dedicated Bearer Context Accept
*              message that is to be sent to the core network.
*        
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldDeActBerContextAccept
(
 UeEsmCb *esmCb,
 UeAppCb *ueCb,
 CmNasEvnt **esmEvnt
)
#else
PUBLIC S16 ueAppUtlBldDeActBerContextAccept(esmCb, ueCb, esmEvnt)
 UeEsmCb *esmCb;
 UeAppCb *ueCb;
 CmNasEvnt **esmEvnt;
#endif
{

   CmEsmMsg    *msg = NULLP;

   TRC2(ueAppUtlBldDeActBerContextAccept);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlBldDeActBerContextAccept:Building Active Dedicated Bearer Context Accept"));

   if(ueCb == NULLP || esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   } 
 
   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);
 
   if (*esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   (*esmEvnt)->m.esmEvnt = msg;
   msg->protDisc = CM_ESM_PD;

   /* Fill ESM DeActicate  bearer context accept message */
   /* Fill mandatory IE's*/
 
   /* EPS barer ID IE*/
   msg->bearerId = esmCb->bId;
     
   /* Procedure transaction identity IE*/   
   msg->prTxnId  =  esmCb->tId;
  
   /* Activate defaule EPS barer context accept*/
   msg->msgType  = CM_ESM_MSG_DEACTV_BEAR_ACC;
   /*Filling of Protocol configuration is left out as its optional*/  

   RETVALUE(ROK);
}



/* 
*
*       Fun:   ueAppUtlBldActDedBerContextAccept
*       
*       Desc:  This is build a Active Dedicated Bearer Context Accept
*              message that is to be sent to the core network.
*        
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldActDedBerContextAccept
(
 UeEsmCb *esmCb,
 UeAppCb *ueCb,
 CmNasEvnt **esmEvnt
)
#else
PUBLIC S16 ueAppUtlBldActDedBerContextAccept(esmCb, ueCb, esmEvnt)
 UeEsmCb *esmCb;
 UeAppCb *ueCb;
 CmNasEvnt **esmEvnt;
#endif
{

   CmEsmMsg    *msg = NULLP;

   TRC2(ueAppUtlBldActDedBerContextAccept);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlBldActDedBerContextAccept:Building Active Dedicated Bearer Context Accept"));

   if(ueCb == NULLP || esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   } 
 
   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);
 
   if (*esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   (*esmEvnt)->m.esmEvnt = msg;
   msg->protDisc = CM_ESM_PD;

   /* Fill ESM Acticate defauld berer context accept message */
   /* Fill mandatory IE's*/
 
   /* EPS barer ID IE*/
   msg->bearerId = esmCb->bId;
     
   /* Procedure transaction identity IE*/   
   msg->prTxnId  =  esmCb->tId;
  
   /* Activate defaule EPS barer context accept*/
   msg->msgType  = CM_ESM_MSG_ACTV_DED_BEAR_ACC;

   RETVALUE(ROK);
}
/*ue008.101 CRID:ccpu00117391 ERAB RELEASE support*/
/*
*
*       Fun: ueAppSndModBrReq 
*       
*       Desc:  This function sends Bearer Modification Request message to MME 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppSndModBrReq 
(
)
#else
PUBLIC S16 ueAppSndModBrReq(Void)
#endif
{
   CmNasEvnt   *brResModReqEvnt = NULLP;
   S16 ret;
   UeAppCb *ueAppCb;
   UeEsmCb   *esmCb;
   U8        bearerId=0;
   TRC2(ueAppSndModBrReq);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppSndModBrReq:Sending Bearer Resource Modification request"));
   bearerId = 6; /*Dedicated BearerID value */
   /*TODO Change this to get the appCb Appropriately in the Multi UE Setup*/
#if 0
   ueAppCb = &ueAppCellCb.ueAppCbLst[0];
#endif
   ret = ueAppUtlFndEsmCb(&esmCb,1,UE_ESM_TRANS_KEY ,ueAppCb);
   if(ret != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE081, (ErrVal)ret,
         "ueAppSndBrResAllocReq: ESM Cb  is not found\n"); 
      RETVALUE(RFAILED);
   }
   ret = ueAppUtlBldBrResModReq(esmCb,ueAppCb, &brResModReqEvnt);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE011, (ErrVal)ret,
            " ueAppSndModBrReq: Could not build the Bearer Resource Modifcation request\n");
      RETVALUE(ret);
   }

   /*Send message to lower layer*/
   if((ret = ueAppLimSndToLower(brResModReqEvnt, C1_ULINFOTFR, ueAppCb)) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE070, (ErrVal)ret,
         "ueAppSndModBrReq: Sending Uplink info failed\n"); 
      RETVALUE(RFAILED);
   }

   RETVALUE(ret);

} /* End of ueAppSndModBrReq*/

/* ue008.101: Modified function ueAppSndBrResAllocReq ()*/
/*
 *
*
*       Fun:   ueAppSndBrResAllocReq
*       
*       Desc:  This function sends Bearer Resource Allocation Request message to MME 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 ueAppSndBrResAllocReq
(
 UeAppCb *ueAppCb
)
#else
PUBLIC S16 ueAppSndBrResAllocReq(ueAppCb)
UeAppCb *ueAppCb;
#endif
{
   CmNasEvnt   *brResAllocReqEvnt = NULLP;
   S16 ret;
   UeEsmCb   *esmCb;

   TRC2(ueAppSndBrResAllocReq);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppSndBrResAllocReq:Sending Bearer Resource Allocation request"));
   /*TODO Change this to get the appCb Appropriately in the Multi UE Setup*/
   ret = ueAppUtlAddEsmCb(&esmCb,ueAppCb);
   if(ret != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE081, (ErrVal)ret,
         "ueAppSndBrResAllocReq: ESM Cb  not be created\n"); 
      RETVALUE(RFAILED);
   }
   ret = ueAppUtlBldBrResAllocReq(esmCb,ueAppCb, &brResAllocReqEvnt);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE011, (ErrVal)ret,
            " ueAppSndBrResAllocReq: Could not build the Bearer Resource Allocation request\n");
      RETVALUE(ret);
   }

   /*Send message to lower layer*/
   if((ret = ueAppLimSndToLower(brResAllocReqEvnt, C1_ULINFOTFR, ueAppCb)) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE070, (ErrVal)ret,
         "ueAppEmmHndlOutDetachReq: Sending Uplink info failed\n"); 
      RETVALUE(RFAILED);
   }

   RETVALUE(ret);

} /* End of ueAppSndBrResAllocReq */
/*ue008.101 CRID:ccpu00117391 ERAB RELEASE support*/
/* 
*
*       Fun:  ueAppUtlBldBrResModReq 
*       
*       Desc:  This is build a BEARER RESOURCE MODIFICATION REQUEST that is to be sent to
*              the core network.
*        
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldBrResModReq 
(
 UeEsmCb   *esmCb,
 UeAppCb *ueCb,
 CmNasEvnt **esmEvnt
 )
#else
PUBLIC S16 ueAppUtlBldBrResModReq(esmCb,ueCb, esmEvnt)
 UeEsmCb   *esmCb;
 UeAppCb *ueCb;
 CmNasEvnt **esmEvnt;
#endif
{
   CmEsmMsg    *msg = NULLP;

   TRC2(ueAppUtlBldBrResModReq);

   UE_DBGP_INFO((UE_PRNTBUF,
        "ueAppUtlBldBrResModReq :Building BEARER RESOURCE MODIFICATION REQUEST "));

   if(ueCb == NULLP || esmEvnt == NULLP)
   {
           RETVALUE(RFAILED);
   } 
 
   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);
   if (*esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   msg->protDisc = CM_ESM_PD;
   (*esmEvnt)->m.esmEvnt = msg;
   /*Fill the Message type */

   /* Fill ESM PDN connectivity request message */

   /*Fill mandatory IE's*/
   /* EPS barer ID IE*/
   msg->bearerId = esmCb->bId;

   /* Procedure transaction identity IE*/
   msg->prTxnId  = esmCb->tId;

   /* PDN connectivity request message idenmtity*/
   msg->msgType  = CM_ESM_MSG_BEAR_RES_MOD_REQ;
    /* Linked EPS Bearer Id */ 
   msg->u.bearModReq.bearerId = esmCb->bId;

  /* TFT */
   msg->u.bearModReq.tft.pres = PRSNT_NODEF;
   msg->u.bearModReq.tft.opCode = CM_ESM_TFT_OPCODE_DEL_FILTER;
   msg->u.bearModReq.tft.eBit = 0x00;
   msg->u.bearModReq.tft.noOfPfs = 1;
   msg->u.bearModReq.tft.noOfParams = 0;

   msg->u.bearModReq.tft.pfList[0].id = 1;

   /* EPS quality of service */
   msg->u.bearModReq.epsQos.pres = NOTPRSNT;
 
   /*Updating the cause value*/
   msg->u.bearModReq.cause.pres = PRSNT_NODEF;
   msg->u.bearModReq.cause.val = UE_ESM_CAUSE_VALUE;/*36 cause value*/

   /* Protocol Cfg Options */
   msg->u.bearModReq.protCfgOpt.pres = NOTPRSNT;

   RETVALUE(ROK);
}


/* 
*
*       Fun:   ueAppUtlBldBrResAllocReq
*       
*       Desc:  This is build a BEARER RESOURCE ALLOCATION REQUEST that is to be sent to
*              the core network.
*        
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_utl.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlBldBrResAllocReq
(
 UeEsmCb   *esmCb,
 UeAppCb *ueCb,
 CmNasEvnt **esmEvnt
 )
#else
PUBLIC S16 ueAppUtlBldBrResAllocReq(esmCb,ueCb, esmEvnt)
 UeEsmCb   *esmCb;
 UeAppCb *ueCb;
 CmNasEvnt **esmEvnt;
#endif
{
   CmEsmMsg    *msg = NULLP;
#ifdef SS_CAVIUM
   UeInetIpAddr address;
#else
   CmInetIpAddr address;
#endif
   
   U16        uePort = 0;
   U16        enbPort = 0;


   TRC2(ueAppUtlBldBrResAllocReq);

   UE_DBGP_INFO((UE_PRNTBUF,
        "ueAppUtlBldBrResAllocReq:Building BEARER RESOURCE ALLOCATION REQUEST "));

   if(ueCb == NULLP || esmEvnt == NULLP)
   {
           RETVALUE(RFAILED);
   } 
 
   /* Allocate memory for mme evnt */
   CM_ALLOC_NASEVNT (esmEvnt, CM_ESM_PD);
   if (*esmEvnt == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /*Allocate memory for ESM message*/
   if (cmGetMem(&(*esmEvnt)->memCp, sizeof(CmEsmMsg), (Ptr *)&msg) != ROK)
   {
      CM_FREE_NASEVNT(esmEvnt);
      RETVALUE(RFAILED);
   }

   msg->protDisc = CM_ESM_PD;
   (*esmEvnt)->m.esmEvnt = msg;
   /*Fill the Message type */

   /* Fill ESM PDN connectivity request message */

   /*Fill mandatory IE's*/
   /* EPS barer ID IE*/
   msg->bearerId = 0;

   /* Procedure transaction identity IE*/
   msg->prTxnId  = esmCb->tId;

   /* PDN connectivity request message idenmtity*/
   msg->msgType  = CM_ESM_MSG_BEAR_RES_ALLOC_REQ;

   /* Linked EPS Bearer Id */ 
   msg->u.bearAllocReq.bearerId = UE_APP_EPS_DFLT_BEARER_INDX;
   
   /* EPS quality of service */
   msg->u.bearAllocReq.epsQos.pres = PRSNT_NODEF;
   msg->u.bearAllocReq.epsQos.lenQosCont = UE_DED_BR_QOS_LEN_CONT;
   msg->u.bearAllocReq.epsQos.qci = UE_DED_BR_QOS_QCI;
   msg->u.bearAllocReq.epsQos.maxBitRateUL = UE_DED_BR_QOS_MBR_UL;
   msg->u.bearAllocReq.epsQos.maxBitRateDL = UE_DED_BR_QOS_MBR_DL;
   msg->u.bearAllocReq.epsQos.guaraBitRateUL = UE_DED_BR_QOS_GBR_UL;
   msg->u.bearAllocReq.epsQos.guaraBitRateDL = UE_DED_BR_QOS_GBR_DL;
   msg->u.bearAllocReq.epsQos.maxBitRateULExt = UE_DED_BR_QOS_EXT_MBR_UL;
   msg->u.bearAllocReq.epsQos.maxBitRateDLExt = UE_DED_BR_QOS_EXT_MBR_DL;
   msg->u.bearAllocReq.epsQos.guaraBitRateULExt = UE_DED_BR_QOS_EXT_GBR_UL;
   msg->u.bearAllocReq.epsQos.guaraBitRateDLExt = UE_DED_BR_QOS_EXT_GBR_DL;

   /* TFT */
   msg->u.bearAllocReq.tft.pres = PRSNT_NODEF;
   msg->u.bearAllocReq.tft.opCode = CM_ESM_TFT_OPCODE_NEWTFT;
   msg->u.bearAllocReq.tft.eBit = 0x00;
   msg->u.bearAllocReq.tft.noOfPfs = 1;
   msg->u.bearAllocReq.tft.noOfParams = 0;

   msg->u.bearAllocReq.tft.pfList[0].pres = PRSNT_NODEF;
   msg->u.bearAllocReq.tft.pfList[0].id = 1;
   msg->u.bearAllocReq.tft.pfList[0].preced = PRSNT_NODEF;
  
   msg->u.bearAllocReq.tft.pfList[0].ipv4.pres = PRSNT_NODEF;

   address = ueCb->ueCtxt.selfAddr.u.ipv4NetAddr;

   uePort = UE_APP_DED_BEARER_START_PORT;
   enbPort = UE_APP_DATA_SRVR_PORT;

   
   ueUtlIpv4InetToArr(msg->u.bearAllocReq.tft.pfList[0].ipv4.ip4, &address);

   msg->u.bearAllocReq.tft.pfList[0].ipv6.pres = NOTPRSNT;

   msg->u.bearAllocReq.tft.pfList[0].protId.pres = PRSNT_NODEF;
   msg->u.bearAllocReq.tft.pfList[0].protId.protType = PRSNT_NODEF;


   msg->u.bearAllocReq.tft.pfList[0].localPort.pres = PRSNT_NODEF;
   msg->u.bearAllocReq.tft.pfList[0].localPort.port = uePort;

   msg->u.bearAllocReq.tft.pfList[0].remotePort.pres = PRSNT_NODEF;
   msg->u.bearAllocReq.tft.pfList[0].remotePort.port = enbPort;

   msg->u.bearAllocReq.tft.pfList[0].locPortRange.pres = PRSNT_NODEF;
   msg->u.bearAllocReq.tft.pfList[0].locPortRange.rangeLow = (uePort  );
   msg->u.bearAllocReq.tft.pfList[0].locPortRange.rangeHigh = (uePort + 20);

   msg->u.bearAllocReq.tft.pfList[0].remPortRange.pres = PRSNT_NODEF;
   msg->u.bearAllocReq.tft.pfList[0].remPortRange.rangeLow = (enbPort + 1);
   msg->u.bearAllocReq.tft.pfList[0].remPortRange.rangeHigh = (enbPort + 5);

   msg->u.bearAllocReq.tft.pfList[0].secParam.pres = NOTPRSNT;

   msg->u.bearAllocReq.tft.pfList[0].tos.pres = NOTPRSNT;

   msg->u.bearAllocReq.tft.pfList[0].flowLabel.pres = NOTPRSNT;
   
   /* Protocol Cfg Options */
   msg->u.bearAllocReq.protCfgOpt.pres = NOTPRSNT;

   RETVALUE(ROK);
}




/*
 *
 *       Fun:    ueAppUtlBldRRCConReq
 *
 *       Desc:   Build RRC Conn. Req
 *
 *       Ret:    Void 
 *
 *       Notes:  None
 *
 *       File:   ue_app_utl.c
 *
 */

#ifdef ANSI
PUBLIC S16  ueAppUtlBldRRCConReq
(
NhuDatReqSdus  **pdu
)
#else
PUBLIC S16  ueAppUtlBldRRCConReq(pdu)
NhuDatReqSdus  **pdu;
#endif
{
   NhuUL_CCCH_Msg *conReqMsg = NULLP;
   NhuRRCConRqstcriticalExtns *critex = NULLP;
   
   Mem  sMem; 

   TRC2(ueAppUtlBldRRCConReq)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlBldRRCConReq:Building RRC Connection Request"));

/* ue002.101: Multi ue support changes */
   sMem.region = ueSimAppCb.init.region;
   sMem.pool = ueSimAppCb.init.pool;

   UEAPP_ALLOC_RRC_EVNT(pdu, sizeof(NhuDatReqSdus), &sMem, UEAPP_RRC_BLKSZ);
   if (NULLP == *pdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE031, (ErrVal)0,
         "ueAppUtlBldRRCConReq:Memory allocation failed\n"); 
      RETVALUE(RFAILED);
   }

   (*pdu)->sdu.msgCategory = NHU_MSG_ULCCCH;

   conReqMsg = &((*pdu)->sdu.m.ulCcchMsg.ccchMsg);

   UEAPP_FILL_U8_U32_TKN(conReqMsg->pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(conReqMsg->message.choice,TRUE, 0);
   if(!(conReqMsg->message.choice.val))
   {
      UEAPP_FILL_U8_U32_TKN(conReqMsg->message.val.c1.choice, TRUE, C1_RRCCONRQST);
      
      /* If choice=0, then it is for Conn Re Est Req, Need not fill here */

      UEAPP_FILL_U8_U32_TKN(conReqMsg->message.val.c1.val.rrcConRqst.pres, TRUE, 1);
      critex = &(conReqMsg->message.val.c1.val.rrcConRqst.criticalExtns);
      UEAPP_FILL_U8_U32_TKN(critex->choice, TRUE,0);
      if(!(critex->choice.val))
      {
         UEAPP_FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.pres,TRUE,1);
         UEAPP_FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.ue_Identity.choice,TRUE,1);
         if(!(critex->val.rrcConRqst_r8.ue_Identity.choice.val))
         {
            UEAPP_FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.ue_Identity.val.s_TMSI.pres,TRUE,1);
            ueAppUtlFillTknStrBSXL(
            &critex->val.rrcConRqst_r8.ue_Identity.val.s_TMSI.mmec,
             8, 5, *pdu);

            ueAppUtlFillTknStrBSXL(
            &(critex->val.rrcConRqst_r8.ue_Identity.val.s_TMSI.m_TMSI),
              32, 2, *pdu);
         }
         else
         {
            ueAppUtlFillTknStrBSXL(
            &(critex->val.rrcConRqst_r8.ue_Identity.val.randomValue), 40, 3,*pdu);
         }

         UEAPP_FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.establishmentCause,TRUE,2);
         ueAppUtlFillTknStrBSXL(&critex->val.rrcConRqst_r8.spare, 1,1, *pdu);
      }
      else
      {
         UEAPP_FILL_U8_U32_TKN(critex->val.criticalExtnsFuture.pres,TRUE,1);
      }
   }
   else
   {
       UEAPP_FILL_U8_U32_TKN(conReqMsg->message.val.messageClassExtn.pres,TRUE, 1)
   }

   RETVALUE (ROK);
}


/*
 *
 *       Fun:    ueAppUtlBldRRCConSetupComplete
 *
 *       Desc:   Build RRC Connection Setup Complete
 *
 *       Ret:    Void 
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */

#ifdef ANSI
PUBLIC S16  ueAppUtlBldRRCConSetupComplete
(
NhuDedicatedInfoNAS *nasPdu,
NhuDatReqSdus       **pdu,
UeAppCb             *ueAppCb
)
#else
PUBLIC S16  ueAppUtlBldRRCConSetupComplete(nasPdu, pdu,ueAppCb)
NhuDedicatedInfoNAS *nasPdu;
NhuDatReqSdus       **pdu;
UeAppCb             *ueAppCb;
#endif
{
   NhuUL_DCCH_Msg *conSetupCompMsg = NULLP;
   NhuRRCConSetupComplcriticalExtns *critex = NULLP;
   NhuMCC_MNC_Digit *member = NULLP;
   NhuMCC_MNC_Digit *member1 = NULLP;
   CmMemListCp       *ptr;

   U8   noComp = 0, idx = 0;
   U8   optional = 0;
   Mem  sMem; 
   S16  ret = ROK;

   TRC2(ueAppUtlBldRRCConSetupComplete)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlBldRRCConSetupComplete:Building RRC Connection Set up Complete"));

  /* ue002.101: Multi ue support changes */
   sMem.region = ueSimAppCb.init.region;
   sMem.pool = ueSimAppCb.init.pool;

   UEAPP_ALLOC_RRC_EVNT(pdu, sizeof(NhuDatReqSdus), &sMem, UEAPP_RRC_BLKSZ);
   if (NULLP == *pdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE032, (ErrVal)0,
         "ueAppUtlBldRRCConSetupComplete:Memory allocation failed \n"); 
      RETVALUE(RFAILED);
   }
   ptr = &(*pdu)->memCp;

   (*pdu)->sdu.msgCategory = NHU_MSG_ULDCCH;

   conSetupCompMsg = &((*pdu)->sdu.m.ulDcchMsg.dcchMsg);

   UEAPP_FILL_U8_U32_TKN(conSetupCompMsg->pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(conSetupCompMsg->message.choice, TRUE, 0);

   /* To fill c1 */
   if(!(conSetupCompMsg->message.choice.val))
   {
      /* This is for Connection Setup Complete */
      UEAPP_FILL_U8_U32_TKN(conSetupCompMsg->message.val.c1.choice, TRUE, C1_RRCCONSETUPCOMPL);
      if(conSetupCompMsg->message.val.c1.choice.val == 4)
      {
         UEAPP_FILL_U8_U32_TKN(conSetupCompMsg->message.val.c1.val.rrcConSetupCompl.pres, TRUE, 1);

         /*ue007.101:7835 RRC TransID used same as enodeb */
         UEAPP_FILL_U8_U32_TKN(conSetupCompMsg->message.val.c1.val.rrcConSetupCompl.rrc_TrnsxnId, TRUE,
               ueAppCb->rcvdTxId.rrc_con_setupTxId);

         critex = &(conSetupCompMsg->message.val.c1.val.rrcConSetupCompl.criticalExtns);

         UEAPP_FILL_U8_U32_TKN(critex->choice, TRUE, 0);
         if (!(critex->choice.val))
         {
            UEAPP_FILL_U8_U32_TKN(critex->val.c1.choice,TRUE, 0);
            UEAPP_FILL_U8_U32_TKN(critex->val.c1.val.rrcConSetupCompl_r8.pres,TRUE, 1);
#ifdef TOTAL_ENB
            /* ue009.101: Added feature to drop the diffrent RRC messages.
             *  depends on the RRC timer. */
            UEAPP_FILL_U8_U32_TKN(critex->val.c1.val.rrcConSetupCompl_r8.selectedPLMN_Identity,TRUE, 1);
#else /* #ifdef TOTAL_ENB */
            UEAPP_FILL_U8_U32_TKN(critex->val.c1.val.rrcConSetupCompl_r8.selectedPLMN_Identity,TRUE, 3);
#endif

            UEAPP_FILL_U8_U32_TKN(critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.pres,
                                  optional, 1);
            if(optional)
            {
               /* Fill It */
               UEAPP_FILL_U8_U32_TKN(
               critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.pres,
               TRUE, 1);

               /* Fill MCC */
               UEAPP_FILL_U8_U32_TKN(
               critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.mcc.noComp,
               TRUE, UE_APP_MAX_MCC_LEN);
               noComp =
               (U8) critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.mcc.noComp.val;

               ret = cmGetMem(ptr, (noComp * sizeof(NhuMCC_MNC_Digit)), (Ptr *)&member);
               if(ROK != ret)
               {
                  UEAPP_FREE_RRC_EVNT(*pdu);
                  RETVALUE(RFAILED);
               } 
               for (idx = 0; idx < noComp; idx++)
               {
                  member[idx].pres = TRUE;
                  /* ue002.101: Multi ue support changes */
                  member[idx].val = ueAppCb->ueCtxt.gummei.nwId.mcc[idx];
               }
               critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.mcc.member = member;

               /* Fill MNC */
               UEAPP_FILL_U8_U32_TKN(
               critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.mnc.noComp,
               TRUE, UE_APP_MAX_MNC_LEN);

               noComp = 
               (U8) critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.mnc.noComp.val;
               ret = cmGetMem(ptr, (noComp * sizeof(NhuMCC_MNC_Digit)), (Ptr *)&member1);
               if(ROK != ret)
               {
                  UEAPP_FREE_RRC_EVNT(*pdu);
                  RETVALUE(RFAILED);
               } 
               for (idx = 0; idx < noComp; idx++)
               {
                  member1[idx].pres = TRUE;
                  /* ue002.101: Multi ue support changes */
                  member1[idx].val = ueAppCb->ueCtxt.gummei.nwId.mnc[idx];
               }
               critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.mnc.member = member1;

               /* Bit String */
               /* MME Group ID */
               ueAppUtlFillTknStrBSXL(
                 &(critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.mmegi), 
                   16,  ueAppCb->ueCtxt.gummei.mmeGrpId, ptr);

               /* MME Code */
               ueAppUtlFillTknStrBSXL(
               &(critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.mmec), 
                 8, ueAppCb->ueCtxt.gummei.mmeCode, ptr);
            }

            /* Octet String -- 1 Octet*/

            /* We should replace with the actual NAS received
               from parameter here. 
               This will be the Initial UE Message [Attach Request + PDN Connectivity Request] */
            ret = ueAppUtlFillTknStrOSXL(
                  &(critex->val.c1.val.rrcConSetupCompl_r8.dedicatedInfoNAS),
                  nasPdu->len, nasPdu->val, ptr);
            if(ROK != ret)
            {
               UEAPP_FREE_RRC_EVNT(*pdu);  
               RETVALUE(RFAILED); 
            }
#ifdef TOTAL_ENB
            /* ue009.101: Added feature to drop the diffrent RRC messages.
             *  depends on the RRC timer. */
            critex->val.c1.val.rrcConSetupCompl_r8.nonCriticalExtn.pres.pres = FALSE;
#else /* #ifdef TOTAL_ENB */
            UEAPP_FILL_U8_U32_TKN(critex->val.c1.val.rrcConSetupCompl_r8.nonCriticalExtn.pres, TRUE, 1);
#endif
         }
         else
         {
            UEAPP_FILL_U8_U32_TKN(critex->val.criticalExtnsFuture.pres,TRUE, 1);
         }
      }
      else
      {
         /* Invalid message type */
      }
   }
   else
   {
      UEAPP_FILL_U8_U32_TKN(conSetupCompMsg->message.val.messageClassExtn.choice, FALSE, 0);
   }

   RETVALUE (ROK);
}

/*
 *
 *       Fun:    ueAppUtlBldRRCSecModeComplete
 *
 *       Desc:   Build RRC Security Mode Complete
 *
 *       Ret:    Void 
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */

#ifdef ANSI
PUBLIC S16  ueAppUtlBldRRCSecModeComplete
(
NhuDatReqSdus    **pdu,
U32       Sec_ModeTxId
)
#else
PUBLIC S16  ueAppUtlBldRRCSecModeComplete(pdu, Sec_ModeTxId)
NhuDatReqSdus    **pdu;
U32       Sec_ModeTxId;
#endif
{
   NhuUL_DCCH_Msg *secModeCompMsg = NULLP;
   NhuSecModeComplcriticalExtns *critex = NULLP;

   Mem  sMem; 

   TRC2(ueAppUtlBldRRCSecModeComplete)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlBldRRCSecModeComplete:Building RRC Security Mode Complete"));

   /* ue002.101: Multi ue support changes */
   sMem.region = ueSimAppCb.init.region;
   sMem.pool = ueSimAppCb.init.pool;

   UEAPP_ALLOC_RRC_EVNT(pdu, sizeof(NhuDatReqSdus), &sMem, UEAPP_RRC_BLKSZ);
   if (NULLP == *pdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE033, (ErrVal)0,
         "ueAppUtlBldRRCSecModeComplete: cmAllocEvnt failed  \n"); 
      RETVALUE(RFAILED);
   }

   (*pdu)->sdu.msgCategory = NHU_MSG_ULDCCH;
   secModeCompMsg = &((*pdu)->sdu.m.ulDcchMsg.dcchMsg);

   UEAPP_FILL_U8_U32_TKN(secModeCompMsg->pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(secModeCompMsg->message.choice, TRUE, 0);

   /* To fill c1 */
   if(!(secModeCompMsg->message.choice.val))
   {
      /* This is for Security mode Complete */
      UEAPP_FILL_U8_U32_TKN(secModeCompMsg->message.val.c1.choice, TRUE, C1_SECURITYMODECOMPL);
      if(secModeCompMsg->message.val.c1.choice.val == 5)
      {
         UEAPP_FILL_U8_U32_TKN(secModeCompMsg->message.val.c1.val.securityModeCompl.pres, TRUE, 1);

         /*ue007.101:ccpu00117835 RRC TransID used same as enodeb */
         UEAPP_FILL_U8_U32_TKN(secModeCompMsg->message.val.c1.val.securityModeCompl.rrc_TrnsxnId, TRUE, Sec_ModeTxId);
         critex = &(secModeCompMsg->message.val.c1.val.securityModeCompl.criticalExtns);

         UEAPP_FILL_U8_U32_TKN(critex->choice, TRUE, 0);
         if (!(critex->choice.val))
         {
            UEAPP_FILL_U8_U32_TKN(critex->val.securityModeCompl_r8.pres, TRUE, 1);
            UEAPP_FILL_U8_U32_TKN(critex->val.securityModeCompl_r8.nonCriticalExtn.pres, TRUE, 1);
         }
         else
         {
            UEAPP_FILL_U8_U32_TKN(critex->val.criticalExtnsFuture.pres, TRUE, 1);
         }
      }
      else
      {
         /* Invalid message type */
      }
   }
   else
   {
      UEAPP_FILL_U8_U32_TKN(secModeCompMsg->message.val.messageClassExtn.choice, FALSE, 0);
   }

   RETVALUE (ROK);
}

/* ue005.101: Added support for UeCapability */
#ifdef UE_RAD_CAP
/*
 *
 *       Fun:    ueAppUtlBldRRCUeCapInfo
 *
 *       Desc:   Build RRC Ue Capability Information 
 *
 *       Ret:    Void 
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */

#ifdef ANSI
PUBLIC S16  ueAppUtlBldRRCUeCapInfo
(
NhuDatReqSdus    **pdu,
U32        Cap_InfoTxId
)
#else
PUBLIC S16  ueAppUtlBldRRCUeCapInfo(pdu, Cap_InfoTxId)
NhuDatReqSdus    **pdu;
U32        Cap_InfoTxId;
#endif
{
   NhuUL_DCCH_Msg             *ueCapInfoMsg = NULLP;
   NhuUECapInfocriticalExtns  *critex = NULLP;
   NhuUE_CapRAT_Cont          *ueCapCont=NULLP;
   NhuUE_EUTRA_Cap            nhuUE_EUTRA_Cap;
   CmMemListCp       *ptr;
   Buffer            *mBuf;
   U32  len;      /* Length of static buffer, if applicable */
   MsgLen cnt;      /* Length of static buffer, if applicable */
   CmPAsnErr err;  /* error to be returned back to the caller */ 
   Mem  sMem; 
   S16  ret = ROK;
   U8   *StrVal=NULL;
   Bool dbgFlag = TRUE;  /* Debug Flag */ 

   len = 0;
   cnt = 0;
   TRC2(ueAppUtlBldRRCUeCapInfo)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlBldRRCUeCapInfo:Building Ue Capability Info"));

   sMem.region = ueSimAppCb.init.region;
   sMem.pool = ueSimAppCb.init.pool;

   UEAPP_ALLOC_RRC_EVNT(pdu, sizeof(NhuDatReqSdus), &sMem, UEAPP_RRC_BLKSZ);
   if (NULLP == *pdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE033, (ErrVal)0,
         "ueAppUtlBldRRCUeCapInfo: cmAllocEvnt failed  \n"); 
      RETVALUE(RFAILED);
   }

   ptr = &(*pdu)->memCp;
   (*pdu)->sdu.msgCategory = NHU_MSG_ULDCCH;
   ueCapInfoMsg = &((*pdu)->sdu.m.ulDcchMsg.dcchMsg);

   UEAPP_FILL_U8_U32_TKN(ueCapInfoMsg->pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(ueCapInfoMsg->message.choice, TRUE, 0);

   /* To fill c1 */
   if(!(ueCapInfoMsg->message.choice.val))
   {
      /* This is for Ue Cap Info */
      UEAPP_FILL_U8_U32_TKN(ueCapInfoMsg->message.val.c1.choice, TRUE, C1_UECAPINFO);
      UEAPP_FILL_U8_U32_TKN(ueCapInfoMsg->message.val.c1.val.ueCapInfo.pres, TRUE, 1);

         /*ue007.101:ccpu00117835 RRC TransID used same as enodeb */
         UEAPP_FILL_U8_U32_TKN(ueCapInfoMsg->message.val.c1.val.ueCapInfo.rrc_TrnsxnId, TRUE, Cap_InfoTxId);

      critex = &(ueCapInfoMsg->message.val.c1.val.ueCapInfo.criticalExtns);
 
          /* Fill container list*/
      UEAPP_FILL_U8_U32_TKN(critex->choice, TRUE, 0);
      UEAPP_FILL_U8_U32_TKN(critex->val.c1.choice, TRUE, 0);
 
         /* Fill EUTRA UE CAP */
      UEAPP_FILL_U8_U32_TKN(critex->val.c1.val.ueCapInfo_r8.pres,TRUE, PRSNT_NODEF);
      UEAPP_FILL_U8_U32_TKN(critex->val.c1.val.ueCapInfo_r8.ue_CapRAT_ContLst.noComp, TRUE, 1);    
      ret = cmGetMem(ptr,
                 sizeof(NhuUE_CapRAT_Cont),(Ptr *)&ueCapCont); 
      if(ROK != ret)
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE033, (ErrVal)0,
                   "ueAppUtlBldRRCUeCapInfo:  Alloc  failed  \n"); 
         UEAPP_FREE_RRC_EVNT(*pdu);
         RETVALUE(RFAILED);
      } 
         
         /* FIll Container Octet string */
       UEAPP_FILL_U8_U32_TKN(ueCapCont->pres, TRUE, PRSNT_NODEF);
       UEAPP_FILL_U8_U32_TKN(ueCapCont->rat_Typ, TRUE, NhuRAT_TypeutraEnum);

        memset(&nhuUE_EUTRA_Cap,0x0,sizeof(NhuUE_EUTRA_Cap));
        ret = ueAppUtlFillRRCUECapIE((Ptr)ptr,
                                        &nhuUE_EUTRA_Cap);
        if(ROK == ret)
        {
            if (SGetMsg(0,0, (Buffer **) &mBuf) != ROK) 
            {                                                      
                mBuf = NULLP;                                    
                UELOGERROR(ERRCLS_ADD_RES, EUE033, (ErrVal)0,
                   "ueAppUtlBldRRCUeCapInfo: Msg Alloc  failed  \n"); 
                 UEAPP_FREE_RRC_EVNT(*pdu);
                 RETVALUE(RFAILED);
            }    
          
               /* Encode the message */
            ret = cmPAsnEncMsgUalign ((TknU8*)&nhuUE_EUTRA_Cap,
                   CM_PASN_USE_MBUF, (Void *)(mBuf),0,
                            nhUE_EUTRA_Cap_Pdu, &err, &len, dbgFlag, FALSE);
            if(ROK != ret)
            {
                UELOGERROR(ERRCLS_ADD_RES, EUE033, (ErrVal)0,
                   "ueAppUtlBldRRCUeCapInfo: cmPAsnEncMsgUalign failed  \n"); 
                UEAPP_FREE_RRC_EVNT(*pdu);
                RETVALUE(RFAILED);
            }
            len = 0;
            /* Find the length of the Buffer  */
            SFndLenMsg(mBuf,(MsgLen*) &len);  
            /* Convert the mBuf to U8 array */
            ret = cmGetMem(ptr, len * sizeof(U8),(Ptr *)&StrVal); 
            if(ROK != ret)
            {
               RETVALUE(RFAILED);
            }  
            SCpyMsgFix(mBuf, 0, len, StrVal, &cnt);
             /* Free the mBuf */
            SPutMsg(mBuf); 
             /* Fill the OctStr Stru info for eUtar Cap */
            ueCapCont->ueCapRAT_Cont.pres = TRUE;
            ueCapCont->ueCapRAT_Cont.val = StrVal;
            ueCapCont->ueCapRAT_Cont.len = len;
             
            /* Fill memeber of container list */
            critex->val.c1.val.ueCapInfo_r8.ue_CapRAT_ContLst.member = ueCapCont;
        }
   }
   else
   {
      UEAPP_FILL_U8_U32_TKN(ueCapInfoMsg->message.val.messageClassExtn.choice, FALSE, 0);
   }

   RETVALUE (ROK);
} /* ueAppUtlBldRRCUeCapInfo */

/*
*
*       Fun:   ueAppUtlFillRRCUECapIE
*
*       Desc:  This function fills NHU Radio Resource Configuration
*
*       Ret:   ROK/RFAILED
*
*       Notes: None
*
*       File:  ue_app_utl.c
*
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlFillRRCUECapIE
(
Ptr         evnt,
NhuUE_EUTRA_Cap *ueEutraCap
)
#else
PUBLIC S16 ueAppUtlFillRRCUECapIE(evnt, ueEutraCap)
Ptr         evnt;
NhuUE_EUTRA_Cap *ueEutraCap;
#endif
{
   S16  ret = ROK;
   TRC2(ueAppUtlFillRRCUECapIE);

   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->accessStratumRls, TRUE, NhuAccessStratumRlsrel8Enum);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->ue_Category,TRUE, 4);
   /* Fill PDCP params */
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pdcp_Params.pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0001, TRUE, TRUE);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0002, TRUE, TRUE);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0003, TRUE, TRUE);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0004, TRUE, TRUE);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0006, TRUE, TRUE);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0101, TRUE, TRUE);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0102, TRUE, TRUE);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0103, TRUE, TRUE);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0104, TRUE, TRUE);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->pdcp_Params.maxNumberROHC_CtxtSessions,TRUE, 
                 NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs2Enum);

   /* Fill Phy layer params */
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->phyLyrParams.pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->phyLyrParams.ue_TxAntennaSelectionSupp, TRUE, TRUE);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->phyLyrParams.ue_SpecificRefSigsSupp, TRUE, TRUE);

   /* Fill RF params */
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->rf_Params.pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->rf_Params.supportedBandLstEUTRA.noComp, TRUE, 1);

   ret = cmGetMem(evnt , 
         (ueEutraCap->rf_Params.supportedBandLstEUTRA.noComp.val)*(sizeof(NhuSuppBandEUTRA)),
         (Ptr *)&(ueEutraCap->rf_Params.supportedBandLstEUTRA.member));
   if(ROK != ret)
   {
      RETVALUE(RFAILED);
   } 
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->rf_Params.supportedBandLstEUTRA.member[0].pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->rf_Params.supportedBandLstEUTRA.member[0].\
                 bandEUTRA, TRUE, TRUE);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->rf_Params.supportedBandLstEUTRA.member[0].\
                 halfDuplex, TRUE, TRUE);

   /* Fill measurement params */
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->measParams.pres, TRUE ,1 );
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->measParams.bandLstEUTRA.noComp,TRUE, 1);

   ret = cmGetMem(evnt , 
          (ueEutraCap->measParams.bandLstEUTRA.noComp.val)*(sizeof(NhuBandInfoEUTRA)),
               (Ptr *)&(ueEutraCap->measParams.bandLstEUTRA.member));
   if(ROK != ret)
   {
      RETVALUE(RFAILED);
   } 
   
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->measParams.bandLstEUTRA.member[0].pres, TRUE, PRSNT_NODEF);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->measParams.bandLstEUTRA.member[0].interFreqBandLst.noComp, TRUE, 1);

   ret = cmGetMem(evnt , 
         (ueEutraCap->measParams.bandLstEUTRA.member[0].interFreqBandLst.noComp.val)\
         *(sizeof(NhuInterFreqBandInfo)),
         (Ptr *)&(ueEutraCap->measParams.bandLstEUTRA.member[0].interFreqBandLst.member));
   if(ROK != ret)
   {
      RETVALUE(RFAILED);
   } 
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->measParams.bandLstEUTRA.member[0].interFreqBandLst.\
                 member[0].pres, PRSNT_NODEF, 1);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->measParams.bandLstEUTRA.member[0].interFreqBandLst.\
                 member[0].interFreqNeedForGaps, PRSNT_NODEF, TRUE);
   UEAPP_FILL_U8_U32_TKN(ueEutraCap->interRAT_Params.pres, PRSNT_NODEF, 1);

   RETVALUE(ROK);
} /* end of ueAppUtlFillRRCUECapIE */

#endif

/*
 *
 *       Fun:    ueAppUtlBldRRCConReCfgComplete
 *
 *       Desc:   Build RRC Connection ReCfg Complete
 *
 *       Ret:    
 *
 *       Notes:  None
 *
 *       File:   
 *
 */

#ifdef ANSI
PUBLIC S16  ueAppUtlBldRRCConReCfgComplete
(
/* ue003.101: added trans Id */
NhuDatReqSdus  **pdu,
U32                    transId
)
#else
PUBLIC S16  ueAppUtlBldRRCConReCfgComplete(pdu, transId)
NhuDatReqSdus  **pdu;
U32                    transId;
#endif
{
   NhuUL_DCCH_Msg *conReCfgCompMsg = NULLP;
   NhuRRCConRecfgnComplcriticalExtns *critex = NULLP;

   Mem  sMem; 

   U8  rrcTransIdPres = 1;
/* ue003.101: removed trans Id hardcoding*/


   TRC2(ueAppUtlBldRRCConReCfgComplete)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlBldRRCConReCfgComplete:Building RRC Reconfiguration Complete"));

   /* ue002.101: Multi ue support changes */
   sMem.region = ueSimAppCb.init.region;
   sMem.pool = ueSimAppCb.init.pool;

   UEAPP_ALLOC_RRC_EVNT(pdu, sizeof(NhuDatReqSdus), &sMem, UEAPP_RRC_BLKSZ);
   if (NULLP == *pdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE034, (ErrVal)0,
         "ueAppUtlBldRRCConReCfgComplete : cmAllocEvnt failed  \n"); 
      RETVALUE(RFAILED);
   }

   (*pdu)->sdu.msgCategory = NHU_MSG_ULDCCH;

   conReCfgCompMsg = &((*pdu)->sdu.m.ulDcchMsg.dcchMsg);

   UEAPP_FILL_U8_U32_TKN(conReCfgCompMsg->pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(conReCfgCompMsg->message.choice,TRUE, 0);

   /* To fill c1 */
   if(!(conReCfgCompMsg->message.choice.val))
   {
      /* This is for Conn Recfg Complete */
      UEAPP_FILL_U8_U32_TKN(conReCfgCompMsg->message.val.c1.choice,TRUE, C1_RRCCONRECFGNCOMPL);
      if(conReCfgCompMsg->message.val.c1.choice.val == 2)
      {
         UEAPP_FILL_U8_U32_TKN(conReCfgCompMsg->message.val.c1.val.rrcConRecfgnCompl.pres, TRUE, 1);

         /* RRC TransID */
         if (rrcTransIdPres)
         {
/* ue003.101: added trans Id */
            UEAPP_FILL_U8_U32_TKN(
            conReCfgCompMsg->message.val.c1.val.rrcConRecfgnCompl.rrc_TrnsxnId,
            TRUE, transId);
         }
         else
         {
             UEAPP_FILL_U8_U32_TKN(
              conReCfgCompMsg->message.val.c1.val.rrcConRecfgnCompl.rrc_TrnsxnId,
              FALSE, 0);
         }
         
         critex = &(conReCfgCompMsg->message.val.c1.val.rrcConRecfgnCompl.criticalExtns);
         UEAPP_FILL_U8_U32_TKN(critex->choice,TRUE, 0);
         if (!(critex->choice.val))
         {
            UEAPP_FILL_U8_U32_TKN(critex->val.rrcConRecfgnCompl_r8.pres,TRUE, 1);
            UEAPP_FILL_U8_U32_TKN(critex->val.rrcConRecfgnCompl_r8.nonCriticalExtn.pres,TRUE,1);
         }
         else
         {
            UEAPP_FILL_U8_U32_TKN(critex->val.criticalExtnsFuture.pres,TRUE, 1);
         }
      }
      else
      {
         /* Invalid message type */
      }
   }
   else
   {
      UEAPP_FILL_U8_U32_TKN(conReCfgCompMsg->message.val.messageClassExtn.choice, FALSE, 0);
   }

   RETVALUE (ROK);
}

/*
 *
 *       Fun:    ueAppUtlBldRRCUpLinkTrfr
 *
 *       Desc:   Build RRC Up Link Transfer
 *
 *       Ret:    Void 
 *
 *       Notes:  None
 *
 *       File:   
 *
 */

#ifdef ANSI
PUBLIC S16 ueAppUtlBldRRCUpLinkTrfr
(
NhuDedicatedInfoNAS *nasPdu,
NhuDatReqSdus       **pdu
)
#else
PUBLIC S16 ueAppUtlBldRRCUpLinkTrfr(nasPdu, pdu)
NhuDedicatedInfoNAS *nasPdu;
NhuDatReqSdus       **pdu;
#endif
{
   NhuUL_DCCH_Msg *upLinkTrfrMsg = NULLP;
   NhuULInfoTfrcriticalExtns *critex = NULLP;
   Mem  sMem; 
   S16  ret = ROK;

   TRC2(ueAppUtlBuildiRRCUpLinkTrfr);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlBldRRCUpLinkTrfr:Building RRC Uplink Transfer Info"));

   /* ue002.101: Multi ue support changes */
   sMem.region = ueSimAppCb.init.region;
   sMem.pool = ueSimAppCb.init.pool;

   UEAPP_ALLOC_RRC_EVNT(pdu, sizeof(NhuDatReqSdus),&sMem, UEAPP_RRC_BLKSZ);
   if (NULLP == *pdu)
   {
      UE_DBGP_INFO((UE_PRNTBUF,
         "ueAppUtlBldRRCUpLinkTrfr:Memory Allocation failed"));
      RETVALUE(RFAILED);
   }

   (*pdu)->sdu.msgCategory = NHU_MSG_ULDCCH;

   upLinkTrfrMsg = &((*pdu)->sdu.m.ulDcchMsg.dcchMsg);

   UEAPP_FILL_U8_U32_TKN(upLinkTrfrMsg->pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(upLinkTrfrMsg->message.choice,TRUE, 0);

   /* To fill c1 */
   if(!(upLinkTrfrMsg->message.choice.val))
   {
      /* This is for Uplink Transfer */
      UEAPP_FILL_U8_U32_TKN(upLinkTrfrMsg->message.val.c1.choice,TRUE, C1_ULINFOTFR);
      if(upLinkTrfrMsg->message.val.c1.choice.val == C1_ULINFOTFR)
      {
         UEAPP_FILL_U8_U32_TKN(upLinkTrfrMsg->message.val.c1.val.ulInfoTfr.pres,TRUE, 1);
         critex = &(upLinkTrfrMsg->message.val.c1.val.ulInfoTfr.criticalExtns);

         UEAPP_FILL_U8_U32_TKN(critex->choice,TRUE, 0);
         if (!(critex->choice.val))
         {
            UEAPP_FILL_U8_U32_TKN(critex->val.c1.choice,TRUE, 0);
            UEAPP_FILL_U8_U32_TKN(critex->val.c1.val.ulInfoTfr_r8.pres,TRUE, 1);

            UEAPP_FILL_U8_U32_TKN(critex->val.c1.val.ulInfoTfr_r8.dedicatedInfoTyp.choice,TRUE, 0);
            if (!(critex->val.c1.val.ulInfoTfr_r8.dedicatedInfoTyp.choice.val))
            {
               ret  = 
               ueAppUtlFillTknStrOSXL(
               &(critex->val.c1.val.ulInfoTfr_r8.dedicatedInfoTyp.val.dedicatedInfoNAS),
               nasPdu->len, nasPdu->val, *pdu);
               if(ROK != ret)
               {
                  UEAPP_FREE_RRC_EVNT(*pdu);  
                  RETVALUE(RFAILED); 
               }
            }
            else
            {
               /* CDMA 2000 */
               /* Octet String */
            }

            UEAPP_FILL_U8_U32_TKN(critex->val.c1.val.ulInfoTfr_r8.nonCriticalExtn.pres,TRUE, 1);
         }
         else
         {
         }
      }
      else
      {
         /* Invalid message type */
      }
   }
   else
   {
      UEAPP_FILL_U8_U32_TKN(upLinkTrfrMsg->message.val.messageClassExtn.choice, FALSE, 0);
   }

   RETVALUE (ROK);
}


/*
*
*       Fun:   ueAppUtlFillTknStrOSXL
*
*       Desc:  Call handler to fill Octet string
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  ue_app_utl.c
*
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlFillTknStrOSXL
(
TknStrOSXL *ptr,   
U16         len,    
Data       *val,     
Ptr         memPtr
)
#else
PUBLIC S16 ueAppUtlFillTknStrOSXL(ptr, len, val, memPtr)
TknStrOSXL *ptr; 
U16         len;  
Data       *val;  
Ptr         memPtr;
#endif
{
   U16     i;     /* counter */

   TRC2(ueAppUtlFillTknStrOSXL);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlFillTknStrOSXL:Filling in the Tokens"));

   if (cmGetMem(memPtr, (len * sizeof(U8)), (Ptr *)&ptr->val) != ROK)
   {
      RETVALUE(RFAILED);
   }

   /* make the element as present */
   ptr->pres = PRSNT_NODEF;
   ptr->len =  len;

   for(i = 0; i < len; i++)
   {
      ptr->val[i] = val[i];
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   ueAppUtlFillTknStrBSXL
*
*       Desc:  Call handler to fill Bit string
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  ue_app_utl.c
*
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlFillTknStrBSXL
(
TknStrBSXL *ptr,   
U16         len,    
U8          val, 
Ptr         memPtr
)
#else
PUBLIC S16 ueAppUtlFillTknStrBSXL(ptr, len, val, memPtr)
TknStrBSXL *ptr; 
U16         len;  
U8          val;  
Ptr         memPtr;
#endif
{
   /* ue002.101: kworks_fix */ 
   U16  i, tmplen; 

   TRC2(ueAppUtlFillTknStrBSXL);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlFillTknStrBSXL:Filling in the Bit String"));

   if((len % 8) > 0)                              
   {                                            
      tmplen = (len/8)+1; 
   } 
   else  
   {
      tmplen = len/8;
   }                                         

   if (cmGetMem(memPtr, (tmplen * sizeof(U8)), (Ptr *)&ptr->val) != ROK)
   {
      RETVALUE(RFAILED);
   }

   ptr->pres = PRSNT_NODEF;
   ptr->len =  len; /* Insert Length in bits only */

   for(i = 0; i < tmplen; i++)
   {
      ptr->val[i] = val; /* Value shall be byte aligned */
   }

   RETVALUE(ROK);
}


/*
*
*       Fun:   ueAppUtlFillTknStr4
*
*       Desc:  Call handler to fill Octet string of length less than 4
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  ue_app_utl.c
*
*/
#ifdef ANSI
PUBLIC S16 ueAppUtlFillTknStr4
(
TknStr4 *ptr,     /* Pointer to the structure */
U8      len,      /* length to be filled */
U8      val       /* byte to be repetitively filled in */
)
#else
PUBLIC S16 ueAppUtlFillTknStr4(ptr, len, val)
TknStr4 *ptr;     /* Pointer to the structure */
U8      len;      /* length to be filled */
U8      val;      /* byte to be repetitively filled in */
#endif
{
   U8      i;     /* counter */

   TRC2(ueAppUtlFillTknStr4);


   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppUtlFillTknStr4:Filling octet string "));

   if (len > 4)
   {
      RETVALUE(RFAILED);
   }
   else
   {
      ptr->len = (U8) len;
   }

   for(i=0; i < len; i++)
   {
      ptr->val[i] = val;
   }

   ptr->pres = PRSNT_NODEF;

   RETVALUE(ROK);

} /* end of ueAppUtlFillTknStr4 */

/* ue003.101: added Ipv4Intto array */
#ifdef SS_CAVIUM
#ifdef ANSI
PUBLIC S16 ueUtlIpv4InetToArr
(
U8           *addrArr,        /* ascii address representation */
UeInetIpAddr *address         /* 4 byte interent address */
)
#else
PUBLIC S16 ueUtlIpv4InetToArr(addrArr, address)
U8           *addrArr;        /* ascii address representation */
UeInetIpAddr *address;        /* 4 byte interent address */
#endif
#else
#ifdef ANSI
PUBLIC S16 ueUtlIpv4InetToArr
(
U8           *addrArr,        /* ascii address representation */
CmInetIpAddr *address         /* 4 byte interent address */
)
#else
PUBLIC S16 ueUtlIpv4InetToArr(addrArr, address)
U8           *addrArr;        /* ascii address representation */
CmInetIpAddr *address;        /* 4 byte interent address */
#endif
#endif
{
   addrArr[3] = (U8)(*address & 0xff);
   addrArr[2] = (U8)((*address >> 8) & 0xff);
   addrArr[1] = (U8)((*address >> 16) & 0xff);
   addrArr[0] = (U8)((*address >> 24) & 0xff);
   RETVALUE(ROK);
}
#ifdef TOTAL_ENB
/* ue009.101: Added feature to drop the diffrent RRC messages.
 *  depends on the RRC timer. */
/* RRC Re-Establishment  Start */
/*
 *
 *       Fun:    ueRrcBuildRRCConReq
 *
 *       Desc:   Build RRC Conn. Req
 *
 *       Ret:    Void 
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */

#ifdef ANSI
PUBLIC S16  ueAppUtlBldRRCReEstlmntReqMsg
(
NhuDatReqSdus **pdu, 
UeAppCb       *ueAppCb
)
#else
PUBLIC S16  ueAppUtlBldRRCReEstlmntReqMsg(reEstPdu, ueAppCb)
NhuDatReqSdus **pdu;
UeAppCb       *ueAppCb;
#endif
{
   NhuUL_CCCH_Msg *reEstbMsg=NULLP;
   NhuRRCConReestbRqstcriticalExtns *critex = NULLP;

   Mem  sMem;
   U8  temp = 1;

   TRC2(ueAppUtlBldRRCReEstlmntReqMsg);

   sMem.region = ueSimAppCb.init.region;
   sMem.pool = ueSimAppCb.init.pool;

   UEAPP_ALLOC_RRC_EVNT(pdu, sizeof(NhuDatReqSdus), &sMem, UEAPP_RRC_BLKSZ);
   if (NULLP == *pdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE105, (ErrVal)0,
            "ueAppUtlBldRRCReEstlmntReqMsg: cmAllocEvnt failed for RRC ConReq\n");
      RETVALUE(RFAILED);
   }

   (*pdu)->sdu.msgCategory = NHU_MSG_ULCCCH;
   reEstbMsg = &((*pdu)->sdu.m.ulCcchMsg.ccchMsg);

   UEAPP_FILL_U8_U32_TKN(reEstbMsg->pres, TRUE, PRSNT_NODEF);
   UEAPP_FILL_U8_U32_TKN(reEstbMsg->message.choice,TRUE, UL_CCCH_MSGTYP_C1);
   if(!(reEstbMsg->message.choice.val))
   {
      UEAPP_FILL_U8_U32_TKN(reEstbMsg->message.val.c1.choice,TRUE, C1_RRCCONREESTBRQST);

      /* If choice=0, then it is for Conn Re Est Req, Need not fill here */

      UEAPP_FILL_U8_U32_TKN(reEstbMsg->message.val.c1.val.rrcConReestbRqst.pres, TRUE, 1);
      critex = &(reEstbMsg->message.val.c1.val.rrcConReestbRqst.criticalExtns);
      UEAPP_FILL_U8_U32_TKN(critex->choice, TRUE,CRITICALEXTNS_RRCCONREESTBRQST_R8);
      if(!(critex->choice.val))
      {
         UEAPP_FILL_U8_U32_TKN(critex->val.rrcConReestbRqst_r8.pres,TRUE,1);

         UEAPP_FILL_U8_U32_TKN(critex->val.rrcConReestbRqst_r8.ue_Identity.pres,TRUE,1);

         ueAppUtlFillTknStrBSXL(&critex->val.rrcConReestbRqst_r8.ue_Identity.c_RNTI, 16, ueAppCb->ueId, *pdu);
         critex->val.rrcConReestbRqst_r8.ue_Identity.c_RNTI.val[0] = 0x00;

         UEAPP_FILL_U8_U32_TKN(critex->val.rrcConReestbRqst_r8.ue_Identity.physCellId,TRUE,ueAppCb->cellId);

         /* UEAPP_FILL_U8_U32_TKN(critex->val.rrcConReestbRqst_r8.ue_Identity.shortMAC_I, FALSE, &temp ); */
         ueAppUtlFillTknStrBSXL(&critex->val.rrcConReestbRqst_r8.ue_Identity.shortMAC_I, 16, 0xff, *pdu);
         critex->val.rrcConReestbRqst_r8.ue_Identity.shortMAC_I.val[0] = 0x00;

         /*     FILL_BIT_STR(critex->val.rrcConReestbRqst_r8.ue_Identity.val.randomValue, 40, 3, pdu);*/

         /* if ( (UE_APP_RRC_REEST_CAUSE_TYPE < 3) && (UE_APP_RRC_REEST_CAUSE_TYPE >= 0))
         { */
            UEAPP_FILL_U8_U32_TKN(critex->val.rrcConReestbRqst_r8.reestablishmentCause,TRUE,/* UE_APP_RRC_REEST_CAUSE_TYPE*/2);
        /* } 
         else
         {
            UEAPP_FILL_U8_U32_TKN(critex->val.rrcConReestbRqst_r8.reestablishmentCause,TRUE, NhuReestbCauseotherFailEnum);
         } */

         ueAppUtlFillTknStrBSXL(&critex->val.rrcConReestbRqst_r8.spare, 2, 1, *pdu);
      }
      else
      {
         UEAPP_FILL_U8_U32_TKN(critex->val.criticalExtnsFuture.pres,TRUE,1);
      }
   }
   else
   {
      UEAPP_FILL_U8_U32_TKN(reEstbMsg->message.val.messageClassExtn.pres,TRUE, 1);
   }

   RETVALUE (ROK);

}

/*
 *     Fun:    ueAppUtlBldRRCReEstlmntCmpltMsg
 * 
 *    Desc:   Build RRC Re-Establishment Complete to ENB for failures. 
 *
 *    Ret:    Void 
 * 
 *    Notes:  None
 *   
 *    File:   
 *     
 *
 */ 

#ifdef ANSI
PUBLIC S16  ueAppUtlBldRRCReEstlmntCmpltMsg
(
NhuDatReqSdus       **pdu,
U32                 transId
)
#else
PUBLIC S16  ueAppUtlBldRRCReEstlmntCmpltMsg(pdu, transId)
NhuDatReqSdus       **pdu;
U32                 transId;
#endif
{
   NhuUL_DCCH_Msg *conReestabCompMsg = NULLP;
   NhuRRCConReestbComplcriticalExtns *critex = NULLP;

   Mem  sMem;

   TRC2(ueRrcBuildRRCConReestabComplete);

   sMem.region = ueSimAppCb.init.region;
   sMem.pool = ueSimAppCb.init.pool;

   UEAPP_ALLOC_RRC_EVNT(pdu, sizeof(NhuDatReqSdus),&sMem, UEAPP_RRC_BLKSZ);
   if (NULLP == *pdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE107, (ErrVal)0,
            "ueAppUtlBldRRCReEstlmntCmpltMsg: cmAllocEvnt failed \
            for RRC ConSetUpCom\n");
      RETVALUE(RFAILED);
   }

   (*pdu)->sdu.msgCategory = NHU_MSG_ULDCCH;
   conReestabCompMsg = &((*pdu)->sdu.m.ulDcchMsg.dcchMsg);

   UEAPP_FILL_U8_U32_TKN(conReestabCompMsg->pres, TRUE, 1);
   UEAPP_FILL_U8_U32_TKN(conReestabCompMsg->message.choice,TRUE, UL_DCCH_MSGTYP_C1);
   /* To fill c1 */
   UEAPP_FILL_U8_U32_TKN(conReestabCompMsg->message.val.c1.choice, TRUE, C1_RRCCONREESTBCOMPL);
   if(conReestabCompMsg->message.val.c1.choice.val == C1_RRCCONREESTBCOMPL)
   {
      UEAPP_FILL_U8_U32_TKN(conReestabCompMsg->message.val.c1.val.rrcConReestbCompl.pres,TRUE, 1);
      /* RRC TransID */
      UEAPP_FILL_U8_U32_TKN(conReestabCompMsg->message.val.c1.val.rrcConReestbCompl.rrc_TrnsxnId,TRUE, transId);

      critex = &(conReestabCompMsg->message.val.c1.val.rrcConReestbCompl.criticalExtns);

      UEAPP_FILL_U8_U32_TKN(critex->choice,TRUE, CRITICALEXTNS_RRCCONREESTBCOMPL_R8);
      if (!(critex->choice.val))
      {
         UEAPP_FILL_U8_U32_TKN(critex->val.rrcConReestbCompl_r8.pres,TRUE, 1);
         UEAPP_FILL_U8_U32_TKN(critex->val.rrcConReestbCompl_r8.nonCriticalExtn.pres,FALSE, 0);

      }
      else
      {
         UEAPP_FILL_U8_U32_TKN(critex->val.criticalExtnsFuture.pres,TRUE, 1);
      }
   }
   else
   {
      /* Invalid message type */
   }

   RETVALUE (ROK);
} /* End of ueAppUtlBldRRCReEstlmntCmpltMsg */
/* RRC Re-Establishment End */
#endif /* #ifdef TOTAL_ENB */
/**********************************************************************
 
         End of file:     ue_app_utl.c@@/main/1 - Sun Mar 28 22:59:21 2010
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vp                 1. Initial Release.
/main/1+   ue002.101  sv                 1. Multi ue support changes.
/main/1+   ue003.101  rp                 1. Dedic bearer  support changes.
/main/1+   ue005.101  cshekar            1. Added support for ue capability.
/main/1+   ue007.101  rk                 1. Added support for Network iniatiated Detach.
                      ms                 2. TxId used same as enodeb.
                                         3. Cavium compilation warning fix
/main/1+   ue008.101  ragrawal           1. CRID:ccpu00117391 ERAB RELEASE support.
                                         2. Modified function ueAppSndBrResAllocReq.
                                         3. Fix for IDCC CR. 
/main/1+   ue009.101  akaranth           1. Added TAU feature.
                                         2. Added feature to drop difrent RRC messages depends on the 
                                            RRC timer.
 *********************************************************************91*/

