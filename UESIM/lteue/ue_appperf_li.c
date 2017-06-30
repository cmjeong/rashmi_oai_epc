
/********************************************************************20**

     Name:     LTE UE Simulator 

     Type:     C source file

     Desc:     This file contains call back functions for NHU
               interface.

     File:     ue_app_li.c

     Sid:      ue_appperf_li.c@@/main/1 - Sun Mar 28 22:59:21 2010

     Prg:      vp 

*********************************************************************21*/


#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#include "cm_hash.h"       /* common hash list */
#include "cm_llist.h"      /* common linked list library */
#include "cm_err.h"        /* common error */
#include "cm_lte.h"        /* common LTE */
#ifndef SS_CAVIUM
#include "cm_inet.h"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_pasn.h"       /* common LTE */
#include "nhu_asn.h"
#ifndef SS_CAVIUM
#include <pcap.h>
#else
#include "cvmx-wqe.h"
#endif /* SS_CAVIUM */
#include "ue_nhu_app.h"    /* UE App Interface with RRC */
#include "cm_emm_esm.h"    /* EMM-ESM Defines */
#include "cm_emm.h"        /* EMM Defines */
#include "cm_esm.h"        /* ESM Defines */
#include "ue_app.h"        /* UE application includes */
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
#include "ue_nhu_app.x"    /* UE App Interface with RRC */
#include "cm_emm.x"        /* EMM Includes */
#include "cm_esm.x"        /* ESM Includes */
#include "cm_emm_esm.x"    /* EMM-ESM Includes */
#include "ue_app.x"        /* UE App Includes */
#include "tfu.x"
#include "ue.x"



/* Following functions are implemented

UeAppLiNhuBndCfm
UeAppLiNhuDatInd
UeAppLiNhuDatCfm

*/
#ifdef ENB_PERF_UL_DATA
PUBLIC U8  data[1500] = {0};
#endif
PUBLIC U32 numPdu = 0;

PRIVATE S16 uePerfAppHdlDlCcchDatInd ARGS (( NhuDatIndSdus *datIndSdus));
PRIVATE S16 uePerfAppHdlDlDcchDatInd ARGS (( NhuDatIndSdus *datIndSdus));
PUBLIC S16 uePerfAppRcvRRCConSetup   ARGS (( NhuDatIndSdus *datIndSdus));

/* ue002.101: Multi ue support changes */
PUBLIC S16 ueAppLimHdlUeEvnt ARGS((CmNasEvnt *ueEvnt, UeAppCb *ueAppCb));
/* ue003.101: Moved to ue.x file */

#ifdef ENB_PERF_MEAS

/*
*
*       Fun:   UePerfAppLiPjuDatInd - PDCP Data Indication
*
*       Desc:  This function is used by to present Data Indication to PDCP.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  ue_app_li.c
*
*/

#ifdef ANSI
PUBLIC S16 UePerfAppLiPjuDatInd
(
Pst *pst,
SuId suId,
Buffer *mBuf,
U16 ueIdx
)
#else
PUBLIC S16 UePerfAppLiPjuDatInd (pst, suId, mBuf, ueIdx)
Pst *pst;
SuId suId;
Buffer *mBuf;
U16 ueIdx;
#endif
{
   S16 ret = ROK;
   MsgLen mBufLen;

   TRC2(UePerfAppLiPjuDatInd)

   UE_DBGP_INFO((UE_PRNTBUF,
      "UePerfAppLiPjuDatInd:Processing the Data received from PDCP"));
   /* Convert the entire mBuf to Flat Buf */
   SFndLenMsg(mBuf, &mBufLen);

   SPutMsg(mBuf);
   mBuf = NULLP;
   numPdu++;

   RETVALUE(ret);

}

#ifdef ANSI
PUBLIC S16 UePerfAppLiNhuDatInd
(
Pst           *pst,          
SuId           suId,
NhuDatIndSdus *datIndSdus           
)
#else
PUBLIC S16 UePerfAppLiNhuDatInd (pst, suId, datIndSdus)
Pst           *pst;          
SuId           suId;
NhuDatIndSdus *datIndSdus;  
#endif
{
   S16 ret = RFAILED;

   TRC2(UePerfAppLiNhuDatInd)

   UE_DBGP_INFO((UE_PRNTBUF,
      "UePerfAppLiNhuDatInd:Processing the Data received from RRC"));

   switch(datIndSdus->sdu.msgCategory)
   {
      case NHU_MSG_DLCCCH:
         ret = uePerfAppHdlDlCcchDatInd(datIndSdus);
/* ue003.101: print added */
         printf("Received DLCCCH Msg for UE %d\n",datIndSdus->hdr.ueId);
         break;
      case NHU_MSG_DLDCCH:
         ret = uePerfAppHdlDlDcchDatInd(datIndSdus);
/* ue003.101: print added */
         printf("Received DLDCCH Msg for UE %d\n",datIndSdus->hdr.ueId);
         break;
      default:
         break;
   } 

   if ( datIndSdus != NULLP )
      UEAPP_FREE_RRC_EVNT(datIndSdus);

   RETVALUE(ret);
}

#ifdef ANSI
PRIVATE S16 uePerfAppHdlDlCcchDatInd
(
NhuDatIndSdus *datIndSdus
)
#else
PRIVATE S16 uePerfAppHdlDlCcchDatInd(datIndSdus)
NhuDatIndSdus *datIndSdus;  
#endif
{
   U8  msgType;
   S16 ret = ROK;
   NhuDlCcchMsg *dlCcchPdu = &datIndSdus->sdu.m.dlCcchMsg;

   TRC2(uePerfAppHdlDlCcchDatInd)

   msgType = dlCcchPdu->ccchMsg.message.val.c1.choice.val;

   UE_DBGP_INFO((UE_PRNTBUF,
      "uePerfAppHdlDlCcchDatInd:Received msgType %d  CCCH", msgType));

   switch(msgType)
   {
      case C3_RRCCONSETUP: /* Connection Setup */
      {
         ret = uePerfAppRcvRRCConSetup(datIndSdus);
         break; 
      }
      default:
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE035, (ErrVal)msgType,
            "uePerfAppHdlDlCcchDatInd:Invalid msgType for CCCH channel\n"); 
         break;
      }
   }

   RETVALUE(ret);

}

/*
*
*       Fun:   uePerfAppRcvRRCConSetup
*       
*       Desc:  This function handles connection set up message from RRC
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/

#ifdef ANSI
PUBLIC S16 uePerfAppRcvRRCConSetup
(
NhuDatIndSdus *datIndSdus
)
#else
PUBLIC S16 uePerfAppRcvRRCConSetup(datIndSdus)
NhuDatIndSdus *datIndSdus;
#endif
{
   UeAppCb *ueAppCb = NULLP;

   TRC2(uePerfAppRcvRRCConSetup);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppRcvRRCConSetup:Received Connection setup"));

   /* ue002.101: Multi ue support: Get the ueAppCb
       and send it in this function */   
   UE_GET_APPCB(ueAppCb,datIndSdus->hdr.ueId);
   /* ue007.101: ccpu00117835 enodeb TxId used */
   ueAppCb->rcvdTxId.rrc_con_setupTxId =
      datIndSdus->sdu.m.dlCcchMsg.ccchMsg.message.val.c1.val.rrcConSetup.rrc_TrnsxnId.val;

   if (ueAppCb != NULLP)
   {
      RETVALUE(ueAppSndAttachRequest(ueAppCb));
   }
   else
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE016, 0,
            " ueAppRcvRRCConSetup: NULL ueAppCb \n");
      RETVALUE(RFAILED);
   }
} /* End of ueAppRcvRRCConSetup */

/*
*
*       Fun:   uePerfAppHdlDlDcchDatInd
*       
*       Desc:  This function handles DCCH data indication.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/
#ifdef ANSI
PRIVATE S16 uePerfAppHdlDlDcchDatInd
(
NhuDatIndSdus *datIndSdus
)
#else
PRIVATE S16 uePerfAppHdlDlDcchDatInd(datIndSdus)
NhuDatIndSdus *datIndSdus;  
#endif
{
   NhuDLInfoTfr  *dlInfoTfr = NULLP;
   NhuDedicatedInfoNAS *nasPdu = NULLP;
   CmNasEvnt   *ueEvnt = NULLP;
   NhuDlDcchMsg *dlDcchPdu = &datIndSdus->sdu.m.dlDcchMsg;
   U8  msgType;
   /* ue002.101: Multi ue support; Decoding NAS from RRC reconfiguration */
   UeAppCb *ueAppCb = NULLP;
   NhuRRCConRecfgn *rrcRecfgn = NULLP;
   U8 nasIdx = 0 ;
   Bool nasPrsnt = FALSE;
   S16 ret;
   U16 ueIdx = 0;

   TRC2(uePerfAppHdlDlDcchDatInd)

   msgType = dlDcchPdu->dcchMsg.message.val.c1.choice.val;

   UE_DBGP_INFO((UE_PRNTBUF,
      "uePerfAppHdlDlDcchDatInd:Processing msgType %d on DCCH", msgType));

   /* ue002.101: Multi ue support: Get the ueAppCb from the CellCb */
   UE_GET_APPCB(ueAppCb,datIndSdus->hdr.ueId);

   if(ueAppCb !=NULLP)
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
            UELOGERROR(ERRCLS_ADD_RES, EUE036, (ErrVal)0,
               " uePerfAppHdlDlDcchDatInd: NAS Decode failure  for DL Info\n"); 

            RETVALUE(ret); 
         }
        /* ue002.101: Multi ue support changes */
        /* Delegate now to a common entry function to handle
           EMM-ESM messages */
         ret = ueAppLimHdlUeEvnt(ueEvnt, ueAppCb);

         break;
      }
         
      case C4_RRCCONRECFGN: /* RRC Reconfiguration Request */
      {
         /* ue002.101: Decode NAS if present.
            Changes for supporting pcap performance on Uu interface */
         /* Get the nasPdu from the dlDcchPdu */
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
#if !(defined(UESIM_ENABLE_PCAP) && defined(ENB_PERF_MEAS))
         /* Handle RRC Reconfiguration Request : 
            Build Reconfig Comp and send to RRC */
/* ue003.101: trans Id passed as parameter */
         ret = ueAppLimHdlRRCConReCfg(ueAppCb, rrcRecfgn->rrc_TrnsxnId.val);
#else
         /* Send the ifconfig/ARP request to the PDN address received */
         printf("ueAppCfgrPdnAssignedAddr:Configuring the PDN assigned IP Add 0\n");
         ueAppCb->ueCtxt.selfAddr.u.ipv4NetAddr = UE_APP_SELF_PDN_ADDR;
         /* ue007.101: Get the proper ueIdx */
         ueIdx=(UE_NUM_PER_CELL > 1)? (ueAppCb->ueId - UE_START_RNTI): 0;

         ret = ueAppCfgrPdnAssignedAddr(ueAppCb->ueCtxt.selfAddr.u.ipv4NetAddr,
                                  (ueIdx));
         RETVALUE(ret);
#endif /* UE_PCAP_PERF */

         /* After RRC reconfig compl is sent delegate to EMM-ESM handlers*/
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
#ifdef SS_HISTOGRAM_SUPPORT
         SHstGrmInfoShow (NULL);
#endif
        /*  ret = ueAppRcvRRCConRls(); */

         break;
      }   
      case C4_SECURITYMODECMD: /* RRC Security Mode Command */
      {
         /* ue007.101:ccpu00117835 enodeb TxId used */
         ueAppCb->rcvdTxId.rrc_Sec_ModeTxId =
                         dlDcchPdu->dcchMsg.message.val.c1.val.securityModeCmd.rrc_TrnsxnId.val;
         /* Handle RRC Security Mode Command */
         /* ue002.101: Multi ue support changes */
         ret = ueAppLimHdlRRCSecModeCmd(ueAppCb);
         break;
      }
      default:
         break;
   }
   RETVALUE(ret);
   }/*end of if ueAppCb !=NULLP) */
   else
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE016, 1,
            " ueAppHdlDcchDatInd: NULL ueAppCb \n");
      RETVALUE(RFAILED);
   }
} /* end of ueAppHdlDlDcchDatInd*/

/*
*
*       Fun:   ueAppTti
*       
*       Desc:  This function handles the TTI indication to generate data.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppTti
(
CmLteTimingInfo    tti
)
#else
PUBLIC S16 ueAppTti(tti)
CmLteTimingInfo    tti;
#endif
{

   UeCb            *ueCb;
   Buffer          *buf;
   S16             i;
    
   /* For now we will check for a single UEs state */
   /* When active, we shall start UL data          */
   ueCb = &cellArr[0].ueArr[0];
   /* ue002.101: Multi ue support changes */
   if (ueAppCellCb.state == TRUE)
   {
      if(ueAppCellCb.wait < 2)
      { 
#ifdef ENB_PERF_UL_DATA
      /* Generate data every 10 ms  6 packets of each size 1450 now */
      if (tti.subframe == 0)
      {
            for(i=0; i < UE_MAX_NO_SDUS; i++)
            {
               UE_ALLOC_BUF(buf);
               SAddPstMsgMult((Data *)data, UE_MAX_SDU_SIZE, buf);
/* ue003.101: Dedic bearer changes */
#ifndef UE_USE_DRB
               ueRlcDatReq(ueCb, UE_LC_DRB1, buf);
#else
               ueRlcDatReq(ueCb, UE_LC_DRB2, buf);
#endif
               ueCb->mac.reportBsr = TRUE;
            }
      }
#endif
     }
     else 
     {
        ueAppCellCb.wait--;
     }
   }

   RETVALUE(ROK);
}
#endif

/**********************************************************************
 
         End of file:     ue_appperf_li.c@@/main/1 - Sun Mar 28 22:59:21 2010
 
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
/main/1+   ue003.101  rp                 1. Added Multiple DRB support. 
/main/1+   ue007.101  rk                 1. Added support for multiple attach and detach.
                      ms                 1. Enodeb TxId used.
 *********************************************************************91*/

