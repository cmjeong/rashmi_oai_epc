
/********************************************************************20**

     Name:    LTE UE Simulator

     Type:    C Include file

     Desc:    This file contains the EMM module source code

     File:    ue_emm.c

     Sid:      ue_emm.c@@/main/1 - Sun Mar 28 22:59:22 2010

     Prg:     vp 
*********************************************************************21*/

/* Header include files (.h) */
/* ue008.101: Added new header file inclusion. */
#include<signal.h>         /*  header for signal */
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

/* ue002.101: Changes to support MSPD CL */
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
#include "cm_lte.x"        /* common tokens */
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
#include "tfu.x"
#include "ue.x"

/*EMM handelers prototypes*/
PRIVATE S16 ueAppEmmHndlInAttachAccept ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
PRIVATE S16 ueAppEmmHndlInAttachRej ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
PRIVATE S16 ueAppEmmHndlInAuthReq ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
PRIVATE S16 ueAppEmmHndlInIdentityReq ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
PRIVATE S16 ueAppEmmHndlInSecModecmd  ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
/* ue007.101: Network initiated Detach support */
PRIVATE S16 ueAppEmmHndlInDetachReq ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
PRIVATE S16 ueAppEmmHndlOutDetachAcc ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
PRIVATE S16 ueAppEmmHndlOutAttachReq  ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
/* ue003.101: Dedic Beraer Support */
PRIVATE S16 ueAppEmmHndlOutServiceReq  ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
PRIVATE S16 ueAppEmmHndlOutAttachCmp  ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
PRIVATE S16 ueAppEmmHndlOutDetachReq  ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
PRIVATE S16 ueAppEmmHndlOutAuthRsp  ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
PRIVATE S16 ueAppEmmHndlOutIdentityRsp  ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
PRIVATE S16 ueAppEmmHndlOutSecModCmp  ARGS((CmNasEvnt *evnt, UeAppCb *ueAppCb));
/* ue008.101: Added new function prototype for SndUEInitDtachReq() */
void SndUEInitDtachReq (int temp);


/*
 *
 *       Fun:   ueAppEmmHndlIncUeEvnt
 *
 *       Desc: This function handels incoming  UE events.
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueAppEmmHdlIncUeEvnt
(
CmNasEvnt    *ueEvnt,
UeAppCb      *ueAppCb
)
#else
PUBLIC S16 ueAppEmmHdlIncUeEvnt(ueEvnt, ueAppCb)
CmNasEvnt     *ueEvnt;
UeAppCb       *ueAppCb;
#endif
{
   S16 ret = ROK;
   TRC2(ueAppEmmHdlIncUeEvnt)
   
#ifdef ERRCLS 
   if(evnt == NULLP)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE060, (ErrVal)0,
         "ueAppEmmHdlIncUeEvnt: Invalid esm event\n"); 
      RETVALUE(RFAILED);
   }
#endif
  /* ue002.101: Multi ue support changes */
   switch(ueEvnt->m.emmEvnt->msgId) 
   { 
      case CM_EMM_MSG_ATTACH_ACC: 
      {
         printf("\nUESIM: Received Attach Accept CellId %d, ueId %d\n", ueAppCb->cellId, ueAppCb->ueId);
         ret = ueAppEmmHndlInAttachAccept(ueEvnt, ueAppCb);
         break; 
      } 
      case CM_EMM_MSG_AUTH_REQ: 
      { 
         printf("\nUESIM: Received Authentication Request\n");
         ret = ueAppEmmHndlInAuthReq(ueEvnt,ueAppCb);
         break; 
      } 
      case CM_EMM_MSG_ID_REQ: 
      { 
         printf("\nUESIM: Received ID Request\n");
         ret = ueAppEmmHndlInIdentityReq(ueEvnt, ueAppCb);
         break; 
      } 
      case CM_EMM_MSG_SEC_MODE_CMD: 
      { 
#ifdef TOTAL_ENB
         /* ue009.101: Added feature to drop the diffrent RRC messages.
          *  depends on the RRC timer. */
         if(UE_RRC_TIMER != UE_RRC_SECUCMD_TMR)
         {
            printf("\nUESIM: Received Security Mode Command\n");
            ret = ueAppEmmHndlInSecModecmd(ueEvnt, ueAppCb);
         }
         else
         {
            printf("Blocking security command \n");
            ret = ROK;
         }
#else /* #ifdef TOTAL_ENB */
         printf("\nUESIM: Received Security Mode Command\n");
         ret = ueAppEmmHndlInSecModecmd(ueEvnt, ueAppCb);
#endif
         break; 
      } 
      case CM_EMM_MSG_ATTACH_REJ: 
      { 
         printf("\nUESIM: Received Attach Reject\n");
         ret = ueAppEmmHndlInAttachRej(ueEvnt, ueAppCb);
         break; 
      }
      /* ue007.101: Network initiated Detach support */
      case CM_EMM_MSG_DETACH_REQ: 
      { 
         printf("\nUESIM: Received Detach Request\n");
         ret = ueAppEmmHndlInDetachReq(ueEvnt, ueAppCb);
         break; 
      }
      /* ue009.101 Added TAU feature */
#ifdef TRACKING_AREA_UPDATE
      case CM_EMM_MSG_TAU_ACC:
      {    
         printf("\nTracking area update accept message received \n");
         break;
      }    
#endif /* TRACKING_AREA_UPDATE */
      default: 
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE061, (ErrVal)ueEvnt->m.esmEvnt->msgType,
            "ueAppEmmHdlIncUeEvnt Invalid message ESM  message\n"); 
         CM_FREE_NASEVNT(&ueEvnt);
         RETVALUE(RFAILED);
      } 
   }
      if(ret != ROK)
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE062, (ErrVal)ueEvnt->m.esmEvnt->msgType,
            "ueAppEmmHdlIncUeEvnt : handling failed for ESM message\n"); 
         CM_FREE_NASEVNT(&ueEvnt);
         RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppEmmHdlOutueEvnt
 *
 *       Desc: This function handles the UE messages sent to the
 *             core network.
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueAppEmmHdlOutUeEvnt
(
CmNasEvnt     *ueEvnt,
UeAppCb       *ueAppCb
)
#else
PUBLIC S16 ueAppEmmHdlOutUeEvnt(ueEvnt, ueAppCb)
CmNasEvnt     *ueEvnt;
UeAppCb       *ueAppCb;
#endif
{
   S16 ret = ROK;
   TRC2(ueAppEmmHdlOutUeEvnt)
      
#ifdef ERRCLS
   if(evnt == NULLP)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE063, (ErrVal)0,
         "ueAppEmmHdlOutUeEvnt : Invalid ESM event \n"); 
      RETVALUE(RFAILED);
   }
#endif
  /* ue002.101: Multi ue support changes */
   switch(ueEvnt->m.emmEvnt->msgId) 
   { 
	   case CM_EMM_MSG_ATTACH_REQ: 
		   {
			   /* ue008.101: Added code to trigger detach request for UE
			    * if UE_NUM_PER_CELL is equal to 1 */
			   if(UE_NUM_PER_CELL == 1)
			   {
				   signal(SIGINT, SndUEInitDtachReq);
			   }
			   ret = ueAppEmmHndlOutAttachReq(ueEvnt, ueAppCb);
			   			   break; 
		   } 
		   /* ue003.101: Dedic Beraer Support */
	   case CM_EMM_MSG_SERVICE_REQ: 
		   {
			   printf("\nUESIM: Sending Service Request\n");
			   ret = ueAppEmmHndlOutServiceReq(ueEvnt, ueAppCb);
			   break; 
		   }
	   case CM_EMM_MSG_AUTH_RSP: 
		   {
			   printf("\nUESIM: Sending Authentication Response\n");
			   ret = ueAppEmmHndlOutAuthRsp(ueEvnt, ueAppCb); 
			   break; 
		   } 
	   case CM_EMM_MSG_ID_RSP: 
		   { 
			   printf("\nUESIM: Sending ID Response\n");
			   ret = ueAppEmmHndlOutIdentityRsp(ueEvnt, ueAppCb); 
			   break; 
		   } 
	   case CM_EMM_MSG_SEC_MODE_CMP: 
		   {
			   printf("\nUESIM: Sending Security Mode Complete\n");
			   ret = ueAppEmmHndlOutSecModCmp(ueEvnt, ueAppCb);
			   break; 
		   } 
	   case CM_EMM_MSG_ATTACH_CMP: 
			{
					  printf("\nUESIM: Sending Attach Complete\n");
					  ret = ueAppEmmHndlOutAttachCmp(ueEvnt, ueAppCb); 
					  if(ret != ROK)
					  {
								 UELOGERROR(ERRCLS_ADD_RES, EUE065, (ErrVal)ueEvnt->m.esmEvnt->msgType,
													  "ueAppEmmHdlOutUeEvnt : Handling failed for ESM message \n"); 
								 CM_FREE_NASEVNT(&ueEvnt);
								 RETVALUE(RFAILED);
					  }
      /* ue009.101 Added TAU feature */
#ifdef TRACKING_AREA_UPDATE
					  printf("\nUESIM: Sending Tracking are update request\n");
					  ret = ueAppSndTAURequest(ueAppCb);
					  if(ret != OK)
					  {
								 printf("\nSending TAU Request failed \n");
								 RETVALUE(RFAILED);
					  }
					  else
					  {
								 printf("\nTracking area update request sent\n");
								 RETVALUE(ROK);
					  }
#endif /* TRACKING_AREA_UPDATE */
					  break; 
			}
	   case CM_EMM_MSG_DETACH_REQ:
		   {
			   printf("\nUESIM: Sending Detach Request\n");
			   ret = ueAppEmmHndlOutDetachReq(ueEvnt, ueAppCb);
			   break;
		   }
		   /* ue007.101: Detach accept for NW initiated detach request */
	   case CM_EMM_MSG_DETACH_ACC:
		   {
			   printf("\nUESIM: Sending Detach Accept\n");
			   ret = ueAppEmmHndlOutDetachAcc(ueEvnt, ueAppCb);
			   break;
		   }
	   default: 
		   { 
			   UELOGERROR(ERRCLS_ADD_RES, EUE064, (ErrVal)ueEvnt->m.esmEvnt->msgType,
					   "ueAppEmmHdlOutUeEvnt : Invalid ESM message \n"); 
			   CM_FREE_NASEVNT(&ueEvnt);
			   RETVALUE(RFAILED);
		   }
   }
      if(ret != ROK)
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE065, (ErrVal)ueEvnt->m.esmEvnt->msgType,
            "ueAppEmmHdlOutUeEvnt : Handling failed for ESM message \n"); 
         CM_FREE_NASEVNT(&ueEvnt);
         RETVALUE(RFAILED);
      }
   RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppEmmHndlOutAttachReq
 *
 *       Desc: This function handels outgoing Attach Request
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */


#ifdef ANSI
PRIVATE S16 ueAppEmmHndlOutAttachReq
(
CmNasEvnt *evnt,
UeAppCb   *ueAppCb
)
#else
PRIVATE S16 ueAppEmmHndlOutAttachReq(evnt, ueAppCb)
CmNasEvnt *evnt;
UeAppCb   *ueAppCb;
#endif
{
   S16 ret = ROK;
   TRC2(ueAppEmmHndlOutAttachReq)

  /* ue002.101: Multi ue support changes */
   if((ret = ueAppEsmHdlOutUeEvnt(evnt->m.emmEvnt->u.atchReq.esmEvnt,
                                  ueAppCb))!= ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE066, (ErrVal)ret,
         "ueAppEmmHndlOutAttachReq : Handling Attach Request failed \n"); 
      RETVALUE(RFAILED);
   }

   /* update the EMM state to register initiated*/
   /* ue002.101: Multi ue support changes */
   ueAppCb->emmCb.state = UE_EMM_UE_REG_INIT;

   /*Set piggybacked to TRUE since we are sending attach request
    * piggybacked with PDN connectivity request*/
   /* ue002.101: Multi ue support changes */
   ueAppCb->emmCb.esmPiggyBacked = TRUE;

  /* Send message to lower layer*/
  /* ue002.101: Multi ue support changes */
   if((ret = ueAppLimSndToLower(evnt, C1_RRCCONSETUPCOMPL, ueAppCb)) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE067, (ErrVal)ret,
         "ueAppEmmHndlOutAttachReq : Sending RRC ConSetUpCmpl failed\n"); 
      RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);
}

/* ue003.101: Dedic Beraer Support */
/*
 *
 *       Fun:   ueAppEmmHndlOutServiceReq
 *
 *       Desc: This function handels outgoing Service Request
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */


#ifdef ANSI
PRIVATE S16 ueAppEmmHndlOutServiceReq
(
CmNasEvnt *evnt,
UeAppCb *ueAppCb
)
#else
PRIVATE S16 ueAppEmmHndlOutServiceReq(evnt, ueAppCb)
CmNasEvnt *evnt;
UeAppCb *ueAppCb;
#endif
{
   S16 ret = ROK;
   TRC2(ueAppEmmHndlOutServiceReq)

   /*Set piggybacked to FALSE */
   ueAppCb->emmCb.esmPiggyBacked = FALSE;

  /*Send message to lower layer*/
   if((ret = ueAppLimSndToLower(evnt, C1_RRCCONSETUPCOMPL, ueAppCb)) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE067, (ErrVal)ret,
         "ueAppEmmHndlOutAttachReq : Sending RRC ConSetUpCmpl failed\n"); 
      RETVALUE(RFAILED);
   } /* end of if statement */
   
   RETVALUE(ROK);
} /* ueAppEmmHndlOutServiceReq */

/*
 *
 *       Fun:   ueAppEmmHndlOutAttachCmp
 *
 *       Desc: This function handels outgoing Attach complete 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */


#ifdef ANSI
PRIVATE S16 ueAppEmmHndlOutAttachCmp
(
CmNasEvnt *evnt,
UeAppCb   *ueAppCb
)
#else
PRIVATE S16 ueAppEmmHndlOutAttachCmp(evnt, ueAppCb)
CmNasEvnt *evnt;
UeAppCb   *ueAppCb;
#endif
{
   S16 ret = ROK;
#ifdef LTE_START_UL_DL_DATA
   UeCb *ueCb = &(cellArr[0].ueArr[0]);
#endif


   TRC2(ueAppEmmHndlOutAttachCmp)
   /* ue002.101: Multi ue support changes */
   if((ret != ueAppEsmHdlOutUeEvnt(evnt->m.emmEvnt->u.atchCmp.esmEvnt,ueAppCb)))
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE068, (ErrVal)ret,
         "ueAppEmmHndlOutAttachCmp: ueAppEsmHdlOutUeEvnt failed \n"); 
      /*update the EMM state to register initiated*/
      ueAppCb->emmCb.state = UE_EMM_UE_REG_INIT;
      RETVALUE(RFAILED);
   }
    /*update the EMM state to registered*/
   ueAppCb->emmCb.state = UE_EMM_UE_REGISTERED;
   
   /*Send message to lower layer*/
   if((ret = ueAppLimSndToLower(evnt, C1_ULINFOTFR, ueAppCb)) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE069, (ErrVal)ret,
         "ueAppEmmHndlOutAttachCmp: Sendinf Uplink info failed\n"); 
      /*update the EMM state to register initiated*/
      ueAppCb->emmCb.state = UE_EMM_UE_REG_INIT;

      RETVALUE(RFAILED);
   }
#ifdef LTE_START_UL_DL_DATA
   ueCb->drbEst = TRUE;
#endif   
   RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppEmmHndlOutDetachReq
 *
 *       Desc: This function handels outgoing Detach request 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */


#ifdef ANSI
PRIVATE S16 ueAppEmmHndlOutDetachReq
(
CmNasEvnt *evnt,
UeAppCb   *ueAppCb
)
#else
PRIVATE S16 ueAppEmmHndlOutDetachReq(evnt,ueAppCb)
CmNasEvnt *evnt;
UeAppCb   *ueAppCb;
#endif
{
   S16 ret = ROK;
   TRC2(ueAppEmmHndlOutDetachReq)
     
   /* ue002.101: Multi ue support changes */
   /*update the EMM state to deregister since its a case of UE switchoff*/
   ueAppCb->emmCb.state = UE_EMM_UE_DEREGISTERED;

   /*Set piggybacked to FALSE since no ESM messahe is piggybacked*/
   ueAppCb->emmCb.esmPiggyBacked = FALSE;

 /*Send message to lower layer*/
   if((ret = ueAppLimSndToLower(evnt, C1_ULINFOTFR, ueAppCb)) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE070, (ErrVal)ret,
         "ueAppEmmHndlOutDetachReq: Sending Uplink info failed\n"); 
      RETVALUE(RFAILED);
   }
   
     RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppEmmHndlOutAuthRsp
 *
 *       Desc: This function handels outgoing Auth response 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */


#ifdef ANSI
PRIVATE S16 ueAppEmmHndlOutAuthRsp
(
 CmNasEvnt *evnt,
 UeAppCb   *ueAppCb
)
#else
PRIVATE S16 ueAppEmmHndlOutAuthRsp(evnt,ueAppCb)
CmNasEvnt *evnt;
UeAppCb *ueAppCb;
#endif
{
   S16 ret = ROK;
   TRC2(ueAppEmmHndlOutAuthRsp)
     
   /* Check whether we are in a valid state to received Auth Rsp */
   if (!(ueAppCb->emmCb.emmCommProcInProgress & UE_EMM_COM_PRC_AUTH_REQ))
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE071, (ErrVal)ret,
         "ueAppEmmHndlOutAuthRsp: In invalid state to process Auth Response\n"); 
      RETVALUE(RFAILED);
   }
   
   /* ue002.101: Multi ue support changes */
   /* update the EMM common procedure state*/
   ueAppCb->emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_IDLE;
   
   /*set EMM common procedure in progress*/ 
   ueAppCb->emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_NONE;

   /*Send message to lower layer*/
   if((ret = ueAppLimSndToLower(evnt, C1_ULINFOTFR, ueAppCb)) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE072, (ErrVal)ret,
         "ueAppEmmHndlOutAuthRsp: Sending message to lower layer failed\n"); 
      
      /*reset  EMM common procedure state*/
      ueAppCb->emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_INIT;
      
      /*reset EMM common procedure in progress*/ 
      ueAppCb->emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_AUTH_REQ;
   
      RETVALUE(RFAILED);
   }
   
     RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppEmmHndlOutIdentityRsp
 *
 *       Desc: This function handels outgoing identity response 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */


#ifdef ANSI
PRIVATE S16 ueAppEmmHndlOutIdentityRsp
(
CmNasEvnt *evnt,
UeAppCb *ueAppCb
)
#else
PRIVATE S16 ueAppEmmHndlOutIdentityRsp(evnt,ueAppCb)
CmNasEvnt *evnt;
UeAppCb *ueAppCb;
#endif
{
   S16 ret = ROK;
   TRC2(ueAppEmmHndlOutIdentityRsp)
     
/* Check whether we are in a valid state to received ID Rsp */
   if (!(ueAppCb->emmCb.emmCommProcInProgress & UE_EMM_COM_PRC_ID_REQ))
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE073, (ErrVal)ret,
         "ueAppEmmHndlOutIdentityRsp: Invalid state to process Identity Rsp\n"); 
      RETVALUE(RFAILED);
   }
  
   /* ue002.101: Multi ue support changes */
   /*update the EMM common procedure state*/
   ueAppCb->emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_IDLE;
   
   /*set EMM common procedure in progress*/ 
   ueAppCb->emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_NONE;
   
   
   /*Send message to lower layer*/
   if((ret = ueAppLimSndToLower(evnt, C1_ULINFOTFR, ueAppCb)) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE074, (ErrVal)ret,
         "ueAppEmmHndlOutIdentityRsp: Sending message to lower layer failed\n"); 
      
      /*reset  EMM common procedure state*/
      ueAppCb->emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_INIT;
      
     /*reset EMM common procedure in progress*/ 
     ueAppCb->emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_ID_REQ;
   
      RETVALUE(RFAILED);
   }
   
     RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppEmmHndlOutSecModCmp
 *
 *       Desc: This function handels outgoing sec mod complete 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */


#ifdef ANSI
PRIVATE S16 ueAppEmmHndlOutSecModCmp
(
CmNasEvnt *evnt,
UeAppCb *ueAppCb
)
#else
PRIVATE S16 ueAppEmmHndlOutSecModCmp(evnt, ueAppCb)
CmNasEvnt *evnt;
UeAppCb *ueAppCb;
#endif
{
   S16 ret = ROK;
   TRC2(ueAppEmmHndlOutSecMocCmp)
     
/* Check whether we are in a valid state to received sec mod cmp */
   if (!(ueAppCb->emmCb.emmCommProcInProgress & UE_EMM_COM_PRC_SEC_MOD_CMD))
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE075, (ErrVal)ret,
         "ueAppEmmHndlOutSecMocCmp : Invalid state to handle SecMode COmplete\n"); 
      RETVALUE(RFAILED);
   }
  
   /* ue002.101: Multi ue support changes */
   /* update the EMM common procedure state*/
   ueAppCb->emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_IDLE;
   
   /*set EMM common procedure in progress*/ 
   ueAppCb->emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_NONE;
   
   /*Send message to lower layer*/
   if((ret = ueAppLimSndToLower(evnt, C1_ULINFOTFR, ueAppCb)) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE076, (ErrVal)ret,
         "ueAppEmmHndlOutSecMocCmp : Sending message to lower layer failed\n"); 
      
      /*reset  EMM common procedure state*/
      ueAppCb->emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_INIT;
      
     /*reset EMM common procedure in progress*/ 
     ueAppCb->emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_SEC_MOD_CMD;
   
      RETVALUE(RFAILED);
   }
   
     RETVALUE(ROK);
}



/*
 *
 *       Fun:   ueAppEmmHndlInAttachAccept
 *
 *       Desc: This function handels incomming Attach accept 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */


#ifdef ANSI
PRIVATE S16 ueAppEmmHndlInAttachAccept
(
CmNasEvnt *evnt,
UeAppCb  *ueAppCb
)
#else
PRIVATE S16 ueAppEmmHndlInAttachAccept(evnt, ueAppCb)
CmNasEvnt *evnt;
UeAppCb   *ueAppCb;
#endif
{
   S16 ret = ROK;
   TRC2(ueAppEmmHndlInAttachAccept)
      
   if(evnt->m.emmEvnt->u.atchAcc.esmEvnt)
   {
      ret = ueAppEsmHdlIncUeEvnt(evnt->m.emmEvnt->u.atchAcc.esmEvnt,ueAppCb);
      
      /*Set piggybacked to TRUE since we have received attach accept piggybacked
       * with Activate default barer context*/
      ueAppCb->emmCb.esmPiggyBacked = TRUE;
      if(ret != ROK)
      RETVALUE(RFAILED);
   }
   /*copy GUTI received from CNE in to UE's context*/
   cmMemcpy((U8 *)&ueAppCb->ueCtxt.ueGuti, (U8*)&evnt->m.emmEvnt->u.atchAcc.guti.u.guti, sizeof(GUTI));
   
   /*send message to USER*/
   ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueAppCb);
   
   RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppEmmHndlInAttachRej
 *
 *       Desc: This function handels incomming Attach reject 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */


#ifdef ANSI
PRIVATE S16 ueAppEmmHndlInAttachRej
(
CmNasEvnt *evnt,
UeAppCb *ueAppCb
)
#else
PRIVATE S16 ueAppEmmHndlInAttachRej(evnt, ueAppCb)
CmNasEvnt *evnt;
UeAppCb *ueAppCb
#endif
{
   S16 ret = ROK;
   TRC2(ueAppEmmHndlInAttachRej)
       
   /* ue002.101: Multi ue support changes */
   if(evnt->m.emmEvnt->u.atchAcc.esmEvnt)
   {
      if((ret = ueAppEsmHdlIncUeEvnt(evnt->m.emmEvnt->u.atchRej.esmEvnt,ueAppCb))!= ROK)
      RETVALUE(RFAILED);
   }
   
   /*set EMM state to register initiated, while sending Attach complete
    * we update it to Registered*/
   ueAppCb->emmCb.state = UE_EMM_UE_DEREGISTERED;

   ueAppCb->emmCb.esmPiggyBacked = FALSE;
   /*send message to USER*/
   ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId,ueAppCb);

   RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppEmmHndlInAuthReq
 *
 *       Desc: This function handels incomming Auth response 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */


#ifdef ANSI
PRIVATE S16 ueAppEmmHndlInAuthReq
(
CmNasEvnt *evnt,
UeAppCb *ueAppCb
)
#else
PRIVATE S16 ueAppEmmHndlInAuthReq(evnt,ueAppCb)
CmNasEvnt *evnt;
UeAppCb *ueAppCb;
#endif
{
   TRC2(ueAppEmmHndlInAuthReq)
     
    /*update the EMM common procedure state*/
   ueAppCb->emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_INIT;
   
   /*set EMM common procedure in progress*/ 
   ueAppCb->emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_AUTH_REQ;
   
   /*send message to USER*/
   ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueAppCb);

     RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppEmmHndlInIdentityReq
 *
 *       Desc: This function handels incomming Auth response 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */


#ifdef ANSI
PRIVATE S16 ueAppEmmHndlInIdentityReq
(
CmNasEvnt *evnt,
UeAppCb *ueAppCb
)
#else
PRIVATE S16 ueAppEmmHndlInIdentityReq(evnt, ueAppCb)
CmNasEvnt *evnt;
UeAppCb *ueAppCb;
#endif
{
   TRC2(ueAppEmmHndlInIdentityReq)
     
    /*update the EMM common procedure state*/
   ueAppCb->emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_INIT;
   
   /*set EMM common procedure in progress*/ 
   ueAppCb->emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_ID_REQ;
   
   /*send message to USER*/
   ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueAppCb);
   
     RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppEmmHndlInSecModecmd
 *
 *       Desc: This function handels incomming sec mod command 
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueAppEmmHndlInSecModecmd
(
CmNasEvnt *evnt,
UeAppCb *ueAppCb
)
#else
PRIVATE S16 ueAppEmmHndlInSecModecmd(evnt,ueAppCb)
CmNasEvnt *evnt;
UeAppCb *ueAppCb
#endif
{
   TRC2(ueAppEmmHndlInSecModecmd)

    /*update the EMM common procedure state*/
   ueAppCb->emmCb.emmCommProcSubState = UE_EMM_COMM_PROC_INIT;
   
   /*set EMM common procedure in progress*/ 
   ueAppCb->emmCb.emmCommProcInProgress = UE_EMM_COM_PRC_SEC_MOD_CMD;
   
   /*send message to USER*/
   ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueAppCb);
   
     RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppEmmHndlInDetachReq
 *
 *       Desc: This function handels incomming Detach Request
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */


#ifdef ANSI
PRIVATE S16 ueAppEmmHndlInDetachReq
(
 CmNasEvnt *evnt,
 UeAppCb  *ueAppCb
 )
#else
PRIVATE S16 ueAppEmmHndlInDetachReq (evnt, ueAppCb)
   CmNasEvnt *evnt;
   UeAppCb   *ueAppCb;
#endif
{
   TRC2(ueAppEmmHndlInDetachReq)

   /*update the EMM state to deregister since its a case of UE switchoff*/
   ueAppCb->emmCb.state = UE_EMM_UE_DEREG_INIT;

   /*send message to USER*/
   ueAppRcvEmmMsg(evnt, evnt->m.emmEvnt->msgId, ueAppCb);

   RETVALUE(ROK);
}

/*
 *
 *       Fun:   ueAppEmmHndlOutDetachAcc
 *
 *       Desc: This function handels outgoing Detach accept
 *
 *       Ret:  ROK - ok; RFAILED - failed
 *
 *       Notes: none
 *
 *       File:  ue_emm.c
 *
 */

#ifdef ANSI
PRIVATE S16 ueAppEmmHndlOutDetachAcc
(
 CmNasEvnt *evnt,
 UeAppCb   *ueAppCb
 )
#else
PRIVATE S16 ueAppEmmHndlOutDetachAcc(evnt,ueAppCb)
   CmNasEvnt *evnt;
   UeAppCb   *ueAppCb;
#endif
{
   S16 ret = ROK;
   TRC2(ueAppEmmHndlOutDetachAcc)

   /*update the EMM state to deregister since */
   ueAppCb->emmCb.state = UE_EMM_UE_DEREGISTERED;

   /*Set piggybacked to FALSE since no ESM message is piggybacked*/
   ueAppCb->emmCb.esmPiggyBacked = FALSE;

   /*Send message to lower layer*/
   if((ret = ueAppLimSndToLower(evnt, C1_ULINFOTFR, ueAppCb)) != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE070, (ErrVal)ret,
            "ueAppEmmHndlOutDetachAcc: Sending Uplink info failed\n"); 
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}


/********************************************************************30**

         End of file:     ue_emm.c@@/main/1 - Sun Mar 28 22:59:22 2010

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
/main/1      ---       vp            1.Initial Release
/main/1+   ue002.101   sv            1. Multi ue support changes.
/main/1+   ue003.101   rp            1. Dedicated Bearer support changes.
/main/1+   ue007.101   rk            1. Added support Network initiated Detach.
                                     2. Cavium warning fix
/main/1+   ue008.101  ragrawal       1. Added code to trigger detach request for UE
                                        if UE_NUM_PER_CELL is equal to 1.
                                     2. Added new header file inclusion.
/main/1+   ue009.101  akaranth       1. Added TAU feature.
                                     2. Added feature to drop the RRC messages, Depends on the RRC timer.
 *********************************************************************91*/
