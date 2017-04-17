
/********************************************************************20**

     Name:     LTE UE Simulator

     Type:     C source file

     Desc:     This file contains call back functions for NHU
               interface.

     File:     ue_app_li.c

     Sid:      ue_app_e2eperf_li.c@@/main/lte_enb_uesim_base_1.1/1 - Thu Sep 16 15:37:22 2010

     Prg:      vp 

*********************************************************************21*/

#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#ifdef SS_CAVIUM
#include "cvmx.h"
#include "cvmx-wqe.h"
#endif

#ifndef SS_CAVIUM
#include <pcap.h>
#endif /* SS_CAVIUM */
#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"           /* Common timer defines */
#include "cm_tkns.h"       /* Common tokens defines */
#include "cm_mblk.h"       /* Common memory allocation library defines */
#include "cm_llist.h"      /* Common link list  defines  */
#include "cm_hash.h"       /* Common hashlist  defines */
#ifndef SS_CAVIUM
#include "cm_inet.h"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_lte.h"        /* Common LTE defines */
#include "cm_pasn.h"       /* Common Pasn includes */
#include <unistd.h>

#include "nhu.h"           /* NHU interface defines */
#include "ue.h"            /* UE Includes */
#include "ue_app.h"        /* UE application includes */
#include "cm_emm.h"        /* UE App - EMM Defines */
#include "cm_esm.h"        /* UE App - ESM Defines */
#include "cm_emm_esm.h"    /* EMM Includes */
#include "ue_err.h"



/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */

#include "cm5.x"           /* Common timer library */
#include "cm_tkns.x"       /* Common tokens */
#include "cm_mblk.x"       /* Common memory allocation */
#include "cm_llist.x"      /* Common link list */
#include "cm_hash.x"       /* Common hashlist */
#include "cm_lib.x"
#ifndef SS_CAVIUM
#include "cm_inet.x"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_lte.x"       /*  Common UMTS includes */
#include "cm_pasn.x"       /* Common Pasn includes */

#include "nhu_asn.x"
#include "ue_nhu_app.x"    /* NHU Interface includes */

#include "cm_esm.x"        /* ESM Includes */
#include "cm_emm.x"        /* EMM Includes */
#include "cm_emm_esm.x"    /* EMM Includes */
#include "ue_app.x"        /* UE App Includes */
#include "ue_pju_app.x"    /* UE App Includes */



/* Following functions are implemented

UeAppLiNhuBndCfm
UeAppLiNhuDatInd
UeAppLiNhuDatCfm

*/

PRIVATE S16 ueAppHdlDlDcchDatInd ARGS ((NhuDatIndSdus *datIndSdus));


PRIVATE S16 ueAppHdlDlCcchDatInd ARGS((NhuDatIndSdus *datIndSdus));


PRIVATE S16 ueAppEdmEncode ARGS((CmNasEvnt              *ueEvnt,
                                 NhuDedicatedInfoNAS *nasPdu));

/* Global variables */
PUBLIC U32      noPkts=0;
PUBLIC U32      noBytes=0;
PUBLIC unsigned long int bpsApp=0;
PUBLIC struct timespec entryRx;
PUBLIC struct timespec exitRx;




/*
*
*       Fun:   UeAppLiNhuBndCfm - NHU Bind Cfm
*
*       Desc:  This function is used by RRC to present Bind Cfm to NHU.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ue_app_li.c
*
*/

#ifdef ANSI
PUBLIC S16 UeAppLiNhuBndCfm
(
Pst     *pst,
SuId    suId,
U8      status
)
#else
PUBLIC S16 UeAppLiNhuBndCfm(pst,suId,status)
Pst     *pst;  
SuId    suId;
U8      status;
#endif
{

   TRC2(UeAppLiNhuBndCfm)

   UE_DBGP_INFO((UE_PRNTBUF,
        "UeAppLiNhuBndCfm:Received a NHU Bind Confirm from the lower layer"));

   RETVALUE(ROK);
} /* end of UeAppLiNhuBndCfm */

/*
*
*       Fun:   UeAppLiNhuDatInd - NHU Data Indication
*
*       Desc:  This function is used by to present Data Indication to NHU.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ue_app_li.c
*
*/

#ifdef ANSI
PUBLIC S16 UeAppLiNhuDatInd
(
Pst           *pst,          
SuId           suId,
NhuDatIndSdus *datIndSdus           
)
#else
PUBLIC S16 UeAppLiNhuDatInd (pst, suId, datIndSdus)
Pst           *pst;          
SuId           suId;
NhuDatIndSdus *datIndSdus;  
#endif
{
   S16 ret = RFAILED;

   TRC2(UeAppLiNhuDatInd)

   UE_DBGP_INFO((UE_PRNTBUF,
            "UeAppLiNhuDatInd:Processing the received RRC data"));

   switch(datIndSdus->sdu.msgCategory)
   {
      case NHU_MSG_DLCCCH:
         ret = ueAppHdlDlCcchDatInd(datIndSdus);
         break;
      case NHU_MSG_DLDCCH:
         ret = ueAppHdlDlDcchDatInd(datIndSdus);
         break;
      default:
         break;
   } 

   /* Adding this; Once any UE related message EMM/ESM is
      delegated up, to handle through EMM/ESM Module upto the
      controller we shouldnt use/free it again. 
      Respective delegated module or controller shall be responsible
      to free it, associating the RRC SDU with MME's event structure.
      But we try to free the RRC SDU here to handle the cases of not
      freeing the PDU if not delegated through the upper modules
      in all error legs. NULLP check is within macro. */
   if ( datIndSdus != NULLP )
      UEAPP_FREE_RRC_EVNT(datIndSdus);

   RETVALUE(ret);
  
}

/*
*
*       Fun:   UeAppLiPjuDatInd - PDCP Data Indication
*
*       Desc:  This function is used by to present Data Indication to PDCP.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ue_app_li.c
*/
#ifdef ANSI
PUBLIC S16 UeAppLiPjuDatInd
(
Pst    *pst,
SuId    suId,
Buffer *mBuf,
U16     cellIdx,
U16     ueIdx
)
#else
PUBLIC S16 UeAppLiPjuDatInd (pst, suId, mBuf,ueIdx)
Pst    *pst;
SuId    suId;
Buffer *mBuf;
U16     cellIdx;
U16     ueIdx;
#endif
{
   MsgLen msgLen;
   unsigned long int diff_time  = 0;

   TRC2(UeAppLiPjuDatInd)

   /* Calculate the date rate received */
   if(!noPkts)
   {
      clock_gettime(0, &entryRx);
   }

   noPkts++;
   SFndLenMsg(mBuf,&msgLen);
   noBytes+=msgLen;
   if( noPkts > 1000)
   {
      clock_gettime(0, &exitRx);
      if (exitRx.tv_sec - entryRx.tv_sec == 0)
      {
        diff_time = exitRx.tv_nsec - entryRx.tv_nsec;
      }
      else if (exitRx.tv_sec - entryRx.tv_sec == 1)
      {
        diff_time = (exitRx.tv_nsec) + (1000000000 - entryRx.tv_nsec);
      }
      else
      {
       diff_time = ((exitRx.tv_sec - entryRx.tv_sec )*1000000000) + 
                               (exitRx.tv_nsec - entryRx.tv_nsec);
      }
      if(diff_time > 0)
      {
        bpsApp = ((noBytes * 8)*1000000000)/(diff_time *1024*1024);
      }

      UE_DBGP_INFO((UE_PRNTBUF,
         "UeAppLiPjuDatInd:DL Data: bits received per sec in UE APP (%ld)\n", bpsApp));

      printf("UeAppLiPjuDatInd:DL Data: bits received per sec in UE APP (%ld)\n", bpsApp);
      noBytes = 0;
      noPkts  = 0;
      bpsApp = 0;
   }
   
   SPutMsg(mBuf);
   mBuf = NULLP;

   RETVALUE(ROK);

}

/*
*
*       Fun:   ueAppHdlDlDcchDatInd
*       
*       Desc:  This function handles the Downlink DCCH control 
*              messages received from the eNodeB.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PRIVATE S16 ueAppHdlDlDcchDatInd
(
NhuDatIndSdus *datIndSdus
)
#else
PRIVATE S16 ueAppHdlDlDcchDatInd(datIndSdus)
NhuDatIndSdus *datIndSdus;  
#endif
{
   NhuDLInfoTfr  *dlInfoTfr = NULLP;
   NhuDedicatedInfoNAS *nasPdu = NULLP;
   CmNasEvnt   *ueEvnt = NULLP;
   U8  msgType;
   S16 ret;
   UeAppCb   *ueAppCb=NULLP;
   /*rrcrecfgn pdu */
   NhuRRCConRecfgn *rrcRecfgn = NULLP;
   U8 nasIdx = 0 ;
   Bool nasPrsnt = FALSE;


   NhuDlDcchMsg *dlDcchPdu = &datIndSdus->sdu.m.dlDcchMsg;

   TRC2(ueAppHdlDlDcchDatInd)

   msgType = dlDcchPdu->dcchMsg.message.val.c1.choice.val;

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppHdlDlDcchDatInd:Processing the DCCH msgType %d",msgType));
   UE_GET_APPCB(ueAppCb,datIndSdus->hdr.ueId);
   if(ueAppCb != NULLP)
   {
      switch(msgType)
      {
         case C4_DLINFOTFR: /* Downlink Information Transfer */
         {
            /* Handle upto UE Application Controller */
            /* Retrieve the NAS PDU IE from message */
            dlInfoTfr = &(dlDcchPdu->dcchMsg.message.val.c1.val.dlInfoTfr); 
            nasPdu = 
            &dlInfoTfr->criticalExtns.val.c1.val.dlInfoTfr_r8.dedicatedInfoTyp.val.dedicatedInfoNAS;

            /* Invoke the decoder for NAS - With EMM-ESM */
            ret = ueAppEdmDecode(nasPdu, &ueEvnt);
            if(ROK != ret)
            {
               UE_DBGP_INFO((UE_PRNTBUF,
               "ueAppHdlDlDcchDatInd: NAS Decode failure for msgType %d", msgType));

               RETVALUE(ret); 
            }
            /* Delegate now to a common entry function to handle
              EMM-ESM messages */
            ret = ueAppLimHdlUeEvnt(ueEvnt,ueAppCb);
            break;
         }
         case C4_RRCCONRECFGN: /* RRC Reconfiguration Request */
         {
            /*get the nasPdu from the dlDcchPdu */
            rrcRecfgn = &(dlDcchPdu->dcchMsg.message.val.c1.val.rrcConRecfgn);
            if(rrcRecfgn != NULLP)
            {
              /* since at time of filling in enodeB we increment this value by 1*/
              nasIdx = rrcRecfgn->criticalExtns.val.c1.val.rrcConRecfgn_r8.\
                                     dedicatedInfoNASLst.noComp.val - 1;
              if(rrcRecfgn->criticalExtns.val.c1.val.rrcConRecfgn_r8.\
                dedicatedInfoNASLst.member && \
                rrcRecfgn->criticalExtns.val.c1.val.rrcConRecfgn_r8.\
                 dedicatedInfoNASLst.member[nasIdx].pres)
              {
                nasPdu =
                &rrcRecfgn->criticalExtns.val.c1.val.rrcConRecfgn_r8.\
                        dedicatedInfoNASLst.member[nasIdx];
                ret = ueAppEdmDecode(nasPdu, &ueEvnt);
                if(ROK != ret)
                {
                  UE_DBGP_INFO((UE_PRNTBUF,
                   "ueAppHdlDlDcchDatInd: NAS Decode failure for msgType %d", msgType));
                  RETVALUE(ret);
                }
                 nasPrsnt = TRUE;
              }
            }
            /* Handle RRC Reconfiguration Request */
/* ue003.101: added transaction id */
            ret = ueAppLimHdlRRCConReCfg(ueAppCb, rrcRecfgn->rrc_TrnsxnId.val);
            /*after RRC reconfig compl is sent delegate to EMM-ESM handlers*/
            if(ret == ROK && nasPrsnt == TRUE)
            {
              /* Delegate now to a common entry function to handle
              EMM-ESM messages */
              ret = ueAppLimHdlUeEvnt(ueEvnt,ueAppCb);
            }
            break;
         }
         case C4_RRCCONRLS: /* RRC Connection Release */
         {
#ifdef SSI_DEBUG_LEVEL1
            SPrintRegMemStatusInfo(0,0);
#endif
            printf(" received RRC coonection release\n");
#ifdef SS_HISTOGRAM_SUPPORT
            SHstGrmInfoShow (NULL);
#endif
            /*  ret = ueAppRcvRRCConRls(); */
            break;
         }   
         case C4_SECURITYMODECMD: /* RRC Security Mode Command */
         {
            /* ue007.101 : ccpu00117835 Transaction ID used same as enodeb */
            ueAppCb->rcvdTxId.rrc_Sec_ModeTxId =
                 dlDcchPdu->dcchMsg.message.val.c1.val.securityModeCmd.rrc_TrnsxnId.val;
            /* Handle RRC Security Mode Command */
            ret = ueAppLimHdlRRCSecModeCmd(ueAppCb);
            break;
         }
         default:
            break;
      }
   }
   else
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE016, 1,
            " ueAppHdlDlDcchDatInd: NULL ueAppCb \n");
   }
  
   RETVALUE(ret);
} /* end of ueAppHdlDlDcchDatInd*/


/*
*
*       Fun:   ueAppHdlDlCcchDatInd
*       
*       Desc:  This function handles the Downlink CCCH control messages.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PRIVATE S16 ueAppHdlDlCcchDatInd
(
NhuDatIndSdus *datIndSdus
)
#else
PRIVATE S16 ueAppHdlDlCcchDatInd(datIndSdus)
NhuDatIndSdus *datIndSdus;  
#endif
{
   U8  msgType;
   S16 ret = ROK;
   NhuDlCcchMsg *dlCcchPdu = &datIndSdus->sdu.m.dlCcchMsg;

   TRC2(ueAppHdlDlCcchDatInd)

   msgType = dlCcchPdu->ccchMsg.message.val.c1.choice.val;

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppHdlDlCcchDatInd:Processing the CCCH msgType %d", msgType));

   switch(msgType)
   {
      case C3_RRCCONSETUP: /* Connection Setup */
      {
         ret = ueAppRcvRRCConSetup(datIndSdus);
         break; 
      }
      default:
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE019, (ErrVal)msgType,
            "ueAppHdlDlCcchDatInd: Unhandled message type\n"); 
         break;
      }
   }

   RETVALUE(ret);

}


/*
*
*       Fun:   ueAppEdmDecode
*       
*       Desc:  Entry function for EMM/ESM decoder
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppEdmDecode
(
NhuDedicatedInfoNAS  *nasPdu,
CmNasEvnt              **ueEvnt
)
#else
PUBLIC S16 ueAppEdmDecode(nasPdu, ueEvnt)
NhuDedicatedInfoNAS  *nasPdu;
CmNasEvnt              **ueEvnt;
#endif
{

   TRC2(ueAppEdmDecode);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppEdmDecode:Decoding the received EDM event"));

   /* check the protocol discriminator and call respective decoder */
   switch (nasPdu->val[0] & 0x0f)
   {
      case CM_EMM_PD:
      {
         RETVALUE(cmEmmDecMsg(nasPdu->val, ueEvnt, nasPdu->len));
      }
      case CM_ESM_PD:
      {
         RETVALUE(cmEsmDecMsg(nasPdu->val, ueEvnt, nasPdu->len));
      }
      default:
      {
         RETVALUE(RFAILED);
      }
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   ueAppLimHdlUeEvnt
*       
*       Desc:  This function handles the NAS UE events received.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppLimHdlUeEvnt
(
CmNasEvnt     *ueEvnt,
UeAppCb *ueAppCb
)
#else
PUBLIC S16 ueAppLimHdlUeEvnt(ueEvnt)
CmNasEvnt     *ueEvnt;
UeAppCb      *ueAppCb
#endif
{
   S16 ret = RFAILED;

   TRC2(ueAppLimHdlUeEvnt);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppLimHdlUeEvnt:Processing the received UE event"));

   /* Invoke the EMM / ESM Handler further */
   switch(ueEvnt->protDisc)
   {
      case CM_EMM_PD:
      {
         ret = ueAppEmmHdlIncUeEvnt(ueEvnt, ueAppCb);
         break;
      }
      case CM_ESM_PD:
      {
         ret = ueAppEsmHdlIncUeEvnt(ueEvnt,ueAppCb);
         break;
      }
      default:
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE020, (ErrVal)ueEvnt->protDisc,
            "Invalid protocol discriminator NAS message type\n"); 
      }
   }
   RETVALUE(ret);
}

/*
*
*       Fun:   ueAppLimSndToLower
*       
*       Desc:  This function encodes and sends a message from application to
*              the lower layer.
*       
*       Ret:   ROK
*              RFAILED
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppLimSndToLower
(
CmNasEvnt        *ueEvnt,
U8             msgType,
UeAppCb        *ueAppCb
)
#else
PUBLIC S16 ueAppLimSndToLower(ueEvnt, msgType,ueAppCb)
CmNasEvnt        *ueEvnt;
U8             msgType;
UeAppCb *ueAppCb;
#endif
{
   NhuDatReqSdus *datReqSdu = NULLP;
   NhuDedicatedInfoNAS nasEncPdu;
   S16          ret;

   TRC2(ueAppLimSndToLower)

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppLimSndToLower:Sending a NAS Message to the lower layer"));

   cmMemset((U8 *)&nasEncPdu, 0, sizeof(NhuDedicatedInfoNAS));
   /* Encode the PDU */
   ret = ueAppEdmEncode(ueEvnt, &nasEncPdu);

   if (ret != ROK)
   {
      UE_DBGP_INFO((UE_PRNTBUF,"ueAppLimSndToLower: Encoding failed: %d \n", 
                      ret));

      /* Free the event structure what we have */
      /* This essentially shouldnt contain RRC SDU, as we encode the 
        EMM-ESM message only. RRC SDU is built locally when trigger from
        upper interface only. however making it NULLP */
      ueEvnt->pdu = NULLP;
      CM_FREE_NASEVNT(&ueEvnt);

      RETVALUE(ret);
   }

   /* Build the associated RRC SDU */
   switch(msgType)
   {
      case C6_ULINFOTFR:
      {
         /* Invoke Encode function here */
         ret = ueAppUtlBldRRCUpLinkTrfr(&nasEncPdu, &datReqSdu);
         if(ROK != ret)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE021, (ErrVal)msgType,
               "ueAppLimSndToLower: RRC SDU couldnt be built \n"); 
         }
         break;
      }
      case C6_RRCCONSETUPCOMPL:
      {
         ret = ueAppUtlBldRRCConSetupComplete(&nasEncPdu, &datReqSdu,ueAppCb);
         if(ROK != ret)
         {
            UELOGERROR(ERRCLS_ADD_RES, EUE022, (ErrVal)msgType,
               "ueAppLimSndToLower : RRC SDU couldnt be built \n"); 
         }
         break;
      }  
      default:
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE023, (ErrVal)msgType,
            "ueAppLimSndToLower: Invalid RRC SDU MsgType \n"); 

         ret = RFAILED;
         break; 
      }
   }
   if(ROK != ret)
   {

      /* Free the encoded pdu since building / sending this message
         itself wasnt success */
      /*UEAPP_FREE(nasEncPdu, CM_MAX_EMM_ESM_PDU);*/
      EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);
      RETVALUE(ret);
   }

   /* Finally delegate the message to send to RRC */
   printf("sending RRC message for cell = %d,ue = %d\n", ueAppCb->cellCb,ueAppCb->ueId,);
   ret = ueAppLimSndRRCMsg(datReqSdu, ueAppCb);

   /* Free the event structure what we have */
   /* This essentially shouldnt contain RRC SDU, as we encode the 
      EMM-ESM message only. RRC SDU is built locally when trigger from
      upper interface only. however making it NULLP */

   ueEvnt->pdu = NULLP;
   if(ret == ROK)
   {
      /* Free NAS event for success case */
      CM_FREE_NASEVNT(&ueEvnt);
   }
   EDM_FREE(nasEncPdu.val, CM_MAX_EMM_ESM_PDU);

   RETVALUE(ret);
}

/*
*
*       Fun:   ueAppEdmEncode
*       
*       Desc:  Entry function for EMM/ESM encoder
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PRIVATE S16 ueAppEdmEncode
(
CmNasEvnt              *ueEvnt,
NhuDedicatedInfoNAS *nasPdu
)
#else
PRIVATE S16 ueAppEdmEncode(ueEvnt, nasPdu)
CmNasEvnt              *ueEvnt;
NhuDedicatedInfoNAS *nasPdu;
#endif
{

   TRC2(ueAppEdmEncode);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppEdmEncode:Encoding the EDM message and sending it to lower layer"));
   if (NULLP == ueEvnt)
   {
      RETVALUE(RFAILED);
   }

   /* Check the protocol discriminator and call respective encoder */
   switch (ueEvnt->protDisc)
   {
      case CM_EMM_PD:
      {
         RETVALUE(cmEmmEncMsg(ueEvnt,
                            &nasPdu->val,
                            &nasPdu->len));
      }
      case CM_ESM_PD:
      {
         RETVALUE(cmEsmEncMsg(ueEvnt,
                            &nasPdu->val,
                            &nasPdu->len));
      }
      default:
      {
         RETVALUE(RFAILED);
      }
   }

} /* ueAppEdmEncode */


/*
*
*       Fun:   ueAppLimHdlRRCConReCfg
*       
*       Desc:  This function handles RRC Reconfiguration request from eNodeB. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppLimHdlRRCConReCfg
(
UeAppCb *ueAppCb,
U32      transId
)
#else
PUBLIC S16 ueAppLimHdlRRCConReCfg(ueAppCb, transId)
UeAppCb *ueAppCb;
U32      transId;
#endif
{
   NhuDatReqSdus *pdu = NULLP;
   S16 ret;
   TRC2(ueAppLimHdlRRCConReCfg);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppLimHdlRRCConReCfg: Handling RRC Reconfiguration Request"));

/* ue003.101: added transaction id */
   ret = ueAppUtlBldRRCConReCfgComplete(&pdu, transId);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE024, (ErrVal)ret,
         "ueAppLimHdlRRCConReCfg : Could not build the RRC \
         Reconfiguration Complete\n"); 
      RETVALUE(ret);
   }
   
   RETVALUE(ueAppLimSndRRCMsg(pdu, ueAppCb));
/*#ifdef ENB_PERF_MEAS
   ueAppCellCb.state = UE_STATE_DATA_READY; /* Ready to generate UP Link data 
#endif*/

} /* End of ueAppLimHdlRRCConReCfg */


/*
*
*       Fun:   ueAppLimHdlRRCSecModeCmd
*       
*       Desc:  This function handles RRC Security Mode Command from eNodeB. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppLimHdlRRCSecModeCmd
(
UeAppCb *ueAppCb
)
#else
PUBLIC S16 ueAppLimHdlRRCSecModeCmd(ueAppCb)
UeAppCb *ueAppCb;
#endif
{
   NhuDatReqSdus *pdu = NULLP;
   S16 ret;

   TRC2(ueAppLimHdlRRCSecModeCmd);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppLimHdlRRCSecModeCmd: Handling RRC Reconfiguration Request"));
   /* ue007.101 : ccpu00117835 Transaction ID used same as enodeb */
   ret = ueAppUtlBldRRCSecModeComplete(&pdu,ueAppCb->rcvdTxId.rrc_Sec_ModeTxId);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE025, (ErrVal)ret,
         "ueAppLimHdlRRCSecModeCmd : Could not build the Secuirty \
         Mode Complete\n"); 

      RETVALUE(ret);
   }

   RETVALUE(ueAppLimSndRRCMsg(pdu,ueAppCb));

} /* End of ueAppLimHdlRRCSecModeCmd */

/*
*
*       Fun:   ueAppLimSndRRCMsg
*       
*       Desc:  This is a common wrapper to send the message to RRC.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppLimSndRRCMsg
(
NhuDatReqSdus *datReqSdu,
UeAppCb       *ueAppCb
)
#else
PUBLIC S16 ueAppLimSndRRCMsg(datReqSdu, ueAppCb)
NhuDatReqSdus *datReqSdu;
UeAppCb       *ueAppCb;
#endif
{
   S16     ret = ROK;

   TRC2(ueAppLimSndRRCMsg)
   
   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppLimSndRRCMsg:Sending a RRC Msg to the lower layer"));

   ueAppCellCb.rrcSapCb->pst.event = EVTNHUDATREQ;
   
   /* Invoking Tightly copuled primitive */
  /* ret = UeAppNhUiNhuDatReq(&(ueAppCellCb.rrcSapCb->pst), ueAppCellCb.rrcSapCb->spId, 
                            datReqSdu);*/

   ret = UeUiNhuDatReq(&(ueAppCellCb.rrcSapCb->pst), ueAppCellCb.rrcSapCb->spId, 
                         datReqSdu, ueAppCb->cellId, ueAppCb->ueId);

   RETVALUE(ret);
}


/*
*
*       Fun:   UeAppLiNhuDatCfm - NHU Data Confirm
*
*       Desc:  This function is used by to present Data Confirmation to NHU.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ue_app_li.c
*
*/

#ifdef ANSI
PUBLIC S16 UeAppLiNhuDatCfm
(
Pst           *pst,          
SuId           suId,
NhuDatCfmSdus *datCfmSdus           
)
#else
PUBLIC S16 UeAppLiNhuDatCfm (pst, suId, datCfmSdus)
Pst           *pst;          
SuId           suId;
NhuDatCfmSdus *datCfmSdus;
#endif
{
   TRC2(UeAppLiNhuDatCfm)
   
   UE_DBGP_INFO((UE_PRNTBUF,
            "UeAppLiNhuDatCfm:Received a Data Confirm from RRC"));

   RETVALUE(ROK);
} /* end of UeAppLiNhuDatCfm */



/**********************************************************************
 
         End of file:     ue_app_e2eperf_li.c@@/main/lte_enb_uesim_base_1.1/1 - Thu Sep 16 15:37:22 2010
 
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
/main/1    ue002.101   sv              1. Adding the file for e2e
                                          performance.
/main/1    ue003.101   rp              1. Changes for paging support.
/main/1    ue007.101   ms              1.enodeb TxId used .
*********************************************************************91*/

