
/********************************************************************20**

     Name:     LTE UE Simulator

     Type:     C source file

     Desc:     This file contains call back functions for NHU
               interface.

     File:     ue_app_li.c

     Sid:      ue_app_li.c@@/main/1 - Sun Mar 28 22:59:21 2010

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
/* ue003.101: Support for paging and other features */
#include "tfu.h"
/* ue008.101: Added new header file inclusion*/
#include "ys_pal.h"
#include "ue_err.h"
#include "cm_esm.x"
/* ue002.101: Support for MSPD CL */
#ifdef YS_MSPD
#include "LtePhyL2Api.h" /* Phy api file */
#include "apidefs.h"
#include "resultcodes.h"
#endif



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
#include "tfu.x"
#include "ue.x"
/* ue008.101: Added new header file inclusion and
 * variables for Cavium Platform */
#ifndef SS_CAVIUM 
#include <arpa/inet.h>
#endif
EXTERN U8  YS_ENB_PCI[YS_MAX_ENB_SUPP];
EXTERN U8  YS_ENB_CELLID[YS_MAX_ENB_SUPP];



#ifndef SS_CAVIUM
extern struct sockaddr_in dstAddr;  /* local Internet address/port */
extern U8 actvIdx;
#endif

/* Following functions are implemented

UeAppLiNhuBndCfm
UeAppLiNhuDatInd
UeAppLiNhuDatCfm

*/

PRIVATE S16 ueAppHdlDlDcchDatInd ARGS ((NhuDatIndSdus *datIndSdus));


PRIVATE S16 ueAppHdlDlCcchDatInd ARGS((NhuDatIndSdus *datIndSdus));


/* ue002.101: Multi ue support changes*/
PUBLIC S16 ueAppLimHdlUeEvnt ARGS((CmNasEvnt  *ueEvnt, UeAppCb *ueAppCb));


PRIVATE S16 ueAppEdmEncode ARGS((CmNasEvnt              *ueEvnt,
                                 NhuDedicatedInfoNAS *nasPdu));

/* ue003.101: Added for detach support */
PUBLIC S16 ueAppRcvRRCConRls ARGS(( UeAppCb *ueAppCb));

/* ue003.101: latency releated changes */
#ifdef UE_COMPUTE_LATENCY
EXTERN TimeDelayInfo tmDelayInfo;
#endif
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

   /* ue002.101: kworks_fix */
   if (datIndSdus == NULLP )
   {
      UE_DBGP_ERROR((UE_PRNTBUF, "UeAppLiNhuDatInd(): Empty msg received \n"));
      RETVALUE(RFAILED);
   }
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

#ifndef SS_CAVIUM
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
*
*/

#ifdef ANSI
PUBLIC S16 UeAppLiPjuDatInd
(
Pst *pst,
SuId suId,
Buffer *mBuf,
U16    cellId,
U16  ueIdx
)
#else
PUBLIC S16 UeAppLiPjuDatInd (pst, suId, mBuf,ueIdx)
Pst *pst;
SuId suId;
Buffer *mBuf;
U16  ueIdx;
#endif
{
   S16 ret = RFAILED;
   UeAppCellCb *ueAppCellCb;
   U8  flatIpBuf[UEMAXBUFLEN];
   MsgLen mBufLen, msgLen;

   TRC2(UeAppLiPjuDatInd)

   UE_DBGP_INFO((UE_PRNTBUF,
            "UeAppLiPjuDatInd:Forwarding the Received IP packet"));
   /* Convert the entire mBuf to Flat Buf */
   SFndLenMsg(mBuf, &mBufLen);

   ret = SCpyMsgFix(mBuf, 0, mBufLen, flatIpBuf, &msgLen);
   if ((ret != ROK) || (msgLen != mBufLen))
   {
      /* cleanup */
      UELOGERROR(ERRCLS_ADD_RES, EUE018, (ErrVal)ret,
         "UeAppLiPjuDatInd : Conversion of mBuf to flat buffer failed\n"); 
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }


   UE_GET_APPCELLCB(cellId, ueAppCellCb);
   /* ue002.101: Multi ue support changes */
   ret = ueAppFrwdIpPkt(flatIpBuf, msgLen, ueAppCellCb->cellIdx,ueIdx);

   SPutMsg(mBuf);

   RETVALUE(ret);

}
#else
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
*
*/

#ifdef ANSI
PUBLIC S16 UeAppLiPjuDatInd
(
Pst *pst,
SuId suId,
Buffer *mBuf,
U16 ueIdx
)
#else
PUBLIC S16 UeAppLiPjuDatInd (pst, suId, mBuf, ueIdx)
Pst *pst;
SuId suId;
Buffer *mBuf;
U16 ueIdx;
#endif
{
   S16 ret = RFAILED;

   TRC2(UeAppLiPjuDatInd)

   UE_DBGP_INFO((UE_PRNTBUF,
            "UeAppLiPjuDatInd:Forwarding the Received IP packet"));

   /* ue002.101: Multi ue support changes */
   ret = ueAppFrwdIpPkt(mBuf,ueIdx);

   SPutMsg(mBuf);

   RETVALUE(ret);

}
#endif

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
   UeAppCb     *ueAppCb = NULLP;
   U8  msgType;
   S16 ret;
   /* ue008.101: Added new local variables. */
#ifndef SS_CAVIUM
   CmLteTimingInfo      tmInfo;
   U32 pci = 0;
   U16 idx;
   Buffer      *msg3 = NULLP;
#endif

   NhuDlDcchMsg *dlDcchPdu = &datIndSdus->sdu.m.dlDcchMsg;
   /*ue001.101 : variables for decoding attach accpet from RRC reconfig req */
   /*rrcrecfgn pdu */
   NhuRRCConRecfgn *rrcRecfgn = NULLP;
   U8 nasIdx = 0;
   Bool nasPrsnt = FALSE;
#ifdef TOTAL_ENB
/* ue009.101 : Introduced new variable to make the accessing of structure variable easy. */
   NhuRRCConRecfgn_r8_IEs *recfgIes;
#endif

   TRC2(ueAppHdlDlDcchDatInd)
    
   /* ue002.101: kworks_fix */
   ret = ROK;
   msgType = dlDcchPdu->dcchMsg.message.val.c1.choice.val;

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppHdlDlDcchDatInd:Processing the DCCH msgType %d",msgType));

   /* ue002.101: Multi ue support changes */
   UE_GET_APPCB(datIndSdus->hdr.cellId,ueAppCb,datIndSdus->hdr.ueId);

   if(ueAppCb != NULLP)
   {
      switch(msgType)
      {
         case C1_DLINFOTFR: /* Downlink Information Transfer */
         {
            /* Handle upto UE Application Controller */
            /* ueAppUtlBldRRCUpLinkTrfr(&sendBuf); */
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
            /*MULTIPLE_UE_CHANGE: get the ueAppCb and send that to the function */
            ret = ueAppLimHdlUeEvnt(ueEvnt,ueAppCb);
            break;
         }
           
         case C1_RRCCONRECFGN: /* RRC Reconfiguration Request */
         {
#ifdef TOTAL_ENB
            ueAppCb->drpSecMode = FALSE;
            /*get the nasPdu from the dlDcchPdu */
            rrcRecfgn = &(dlDcchPdu->dcchMsg.message.val.c1.val.rrcConRecfgn);
            recfgIes = &rrcRecfgn->criticalExtns.val.c1.val.rrcConRecfgn_r8;

            /* since at time of filling in enodeB we increment this value by 1*/
            nasIdx = recfgIes->dedicatedInfoNASLst.noComp.val - 1;
            if(recfgIes->dedicatedInfoNASLst.member && \
                  recfgIes->dedicatedInfoNASLst.member[nasIdx].pres)
            {
               nasPdu = &recfgIes->dedicatedInfoNASLst.member[nasIdx];
               ret = ueAppEdmDecode(nasPdu, &ueEvnt);
               if(ROK != ret)
               {
                  UE_DBGP_INFO((UE_PRNTBUF,
                           "ueAppHdlDlDcchDatInd: NAS Decode failure for msgType %d", msgType));
                  RETVALUE(ret);
               }
               nasPrsnt = TRUE;
            }

            /* ue008.101*/
            /* 1. If we have Mobility Control Info IE. set the hoState in UeAppCb to macro defined ue.h 
               2. Search for the pci value in the list of global ENB_PCI array. If it is available set
               the actvIdx to that index.
               3. Using the active index set the cellId in the ueCb.*/


#ifndef SS_CAVIUM
            if(recfgIes->mobilityCntrlInfo.pres.pres == TRUE)
            {
               printf("\n ***** RECEIVED MOBILIGY CNTRL **********\n");
               ueAppCb->hoState = UE_HO_IN_PROGRESS;

               pci = recfgIes->mobilityCntrlInfo.targetPhysCellId.val;

               /* Get pci */
               for(idx = 0; idx< YS_MAX_ENB_SUPP; idx++)
               {
                  if( pci ==  YS_ENB_PCI[idx])
                  {
                     actvIdx = idx;
                     dstAddr.sin_port        = htons(YS_PORT_ENB[actvIdx]);
                     dstAddr.sin_addr.s_addr = inet_addr((CONSTANT char *)YS_IP_ADDR_ENB[actvIdx]);
                     ueAppCb->cellId = pci;
                     cellArr[0].ueArr[0].cellId = pci;

                     break;
                  }
               }
               /* Need to Call RACH REQ*/
               cmMemset((U8 *)&tmInfo,0,sizeof(CmLteTimingInfo));
#ifdef TA_NEW
               tmInfo.sfn = cellArr[0].crntTime.sfn;
               tmInfo.subframe = cellArr[0].crntTime.subframe;
#endif
               /* Get UeIdx */
               ueRrcBuildRRCConReCfgComplete(&msg3);
               ueRrcBuildRRCConReq(&msg3 ,&(cellArr[0].ueArr[0]), FALSE);
               ueMacRachReq(&cellArr[0], &cellArr[0].ueArr[0], msg3);
               ueMacHndlRachForHo(tmInfo,YS_ENB_CELLID[actvIdx],
                     recfgIes->mobilityCntrlInfo.rach_ConfigDedicated.ra_PreambleIdx.val);
            }
            else if(recfgIes->measConfig.pres.pres == TRUE)
            {
               printf("\nprocessing measurement config cellId %d ueId %d\n",ueAppCb->cellId, ueAppCb->ueId);
               ueRrcPrcMeasCfg(ueAppCb, &recfgIes->measConfig);
            }
            else
            {
               printf("\n ***** DIDNOT RECEIVE MOBILIGY CNTRL **********\n");
            }
#endif
            /* 
             * Start of Comment.
             * TODO For Testing Purpose, As soon as UE has sent 
             * RRCConnectionReconfigurationComplete message,UE triggers Measurement 
             * Report based on configuration which is given by eNB.
             * End of Comment.
             */

            if(ueAppCb->hoState == 0)
            {
               /* Handle RRC Reconfiguration Request */
               ret = ueAppLimHdlRRCConReCfg(ueAppCb, rrcRecfgn->rrc_TrnsxnId.val);
#ifdef UE_COMPUTE_LATENCY
               tmDelayInfo.rrcConRecfgComp.status = 1;
#endif

               /*after RRC reconfig compl is sent delegate to EMM-ESM handlers*/
               if(ret == ROK && nasPrsnt == TRUE)
               {
                  /* Delegate now to a common entry function to handle
                     EMM-ESM messages */
                  ret = ueAppLimHdlUeEvnt(ueEvnt, ueAppCb);
               }

               switch(rrcRecfgn->rrc_TrnsxnId.val)
               {
                  case 0:    /* Initial Context Setup Request */
                     break;
                  case 1:    /* ERAB Setup Request */
                     break;
                  default:
                     break;
               }
            } /* end of if statement */
#else /* #ifdef TOTAL_ENB */
            ueAppCb->drpSecMode = FALSE;
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

            /* ue008.101*/
            /* 1. If we have Mobility Control Info IE. set the hoState in UeAppCb to macro defined ue.h 
               2. Search for the pci value in the list of global ENB_PCI array. If it is available set
               the actvIdx to that index.
               3. Using the active index set the cellId in the ueCb.*/


#ifndef SS_CAVIUM
            if(rrcRecfgn->criticalExtns.val.c1.val.rrcConRecfgn_r8.mobilityCntrlInfo.pres.pres == TRUE)
            {
               printf("\n ***** RECEIVED MOBILIGY CNTRL **********\n");
               ueAppCb->hoState = UE_HO_IN_PROGRESS;

               pci = rrcRecfgn->criticalExtns.val.c1.val.rrcConRecfgn_r8.mobilityCntrlInfo.targetPhysCellId.val;

               /* Get pci */
               for(idx = 0; idx< YS_MAX_ENB_SUPP; idx++)
               {
                  if( pci ==  YS_ENB_PCI[idx])
                  {
                     //actIndx = idx;
                     actvIdx = idx;
                     dstAddr.sin_port        = htons(YS_PORT_ENB[actvIdx]);
                     dstAddr.sin_addr.s_addr = inet_addr((CONSTANT char *)YS_IP_ADDR_ENB[actvIdx]);
                     ueAppCb->cellId = pci;
                     cellArr[0].ueArr[0].cellId = pci;

                     break;
                  }
               }
#if 1
               /* Need to Call RACH REQ*/
               cmMemset((U8 *)&tmInfo,0,sizeof(CmLteTimingInfo));
#ifdef TA_NEW
               tmInfo.sfn = cellArr[0].crntTime.sfn;
               tmInfo.subframe = cellArr[0].crntTime.subframe;
#endif
               ueMacRachReq(&cellArr[0], &cellArr[0].ueArr[0], msg3);
               //ueMacHndlRachForHo(tmInfo,YS_ENB_CELLID[actIndx],
               ueMacHndlRachForHo(tmInfo,YS_ENB_CELLID[actvIdx],
                     rrcRecfgn->criticalExtns.val.c1.val.rrcConRecfgn_r8.mobilityCntrlInfo.rach_ConfigDedicated.ra_PreambleIdx.val);
#endif
            }
#endif
            /* 
             * Start of Comment.
             * TODO For Testing Purpose, As soon as UE has sent 
             * RRCConnectionReconfigurationComplete message,UE triggers Measurement 
             * Report based on configuration which is given by eNB.
             * End of Comment.
             */

            if(ueAppCb->hoState == 0)
            {
               /* Handle RRC Reconfiguration Request */
               ret = ueAppLimHdlRRCConReCfg(ueAppCb, rrcRecfgn->rrc_TrnsxnId.val);
#ifdef UE_COMPUTE_LATENCY
               tmDelayInfo.rrcConRecfgComp.status = 1;
#endif

               /*after RRC reconfig compl is sent delegate to EMM-ESM handlers*/
               if(ret == ROK && nasPrsnt == TRUE)
               {
                  /* Delegate now to a common entry function to handle
                     EMM-ESM messages */
                  ret = ueAppLimHdlUeEvnt(ueEvnt, ueAppCb);
               }

               switch(rrcRecfgn->rrc_TrnsxnId.val)
            {
               case 0:    /* Initial Context Setup Request */
                      break;
               case 1:    /* ERAB Setup Request */
                     break;
               default:
                     break;
            }
         } /* end of if statement */


#endif /* #ifdef TOTAL_ENB */
         break;
         }
         
         case C1_RRCCONRLS: /* RRC Connection Release */
         {
#ifdef SSI_DEBUG_LEVEL1
            SPrintRegMemStatusInfo(0,0);
#endif
#ifdef SS_HISTOGRAM_SUPPORT
            SHstGrmInfoShow (NULL);
#endif
            ret = ueAppRcvRRCConRls(ueAppCb); 

            break;
          }   
          case C1_SECURITYMODECMD: /* RRC Security Mode Command */
          {
             /* ue007.101:ccpu00117835 Transaction ID used same as enodeb */
              ueAppCb->rcvdTxId.rrc_Sec_ModeTxId =
                              dlDcchPdu->dcchMsg.message.val.c1.val.securityModeCmd.rrc_TrnsxnId.val;
             /* Handle RRC Security Mode Command */
#ifdef TOTAL_ENB
              /* ue009.101: Added feature to drop the diffrent RRC messages.
               *  depends on the RRC timer. */
             if(UE_RRC_TIMER != UE_RRC_SECUCMD_TMR)
             { 
                if(ueAppCb->drpSecMode == FALSE)
                {
                   ret = ueAppLimHdlRRCSecModeCmd(ueAppCb);
                   ueAppCb->drpSecMode = TRUE;
                }
                /* ue009.101: Added feature to drop the diffrent RRC messages.
                 *  depends on the RRC timer. */
             }
             else
             {
               printf("Blocking security command complete message \n");
               ueAppCb->drpSecMode = TRUE;
               return(ROK);
             }
#else /* #ifdef TOTAL_ENB */
             if(ueAppCb->drpSecMode == FALSE)
             {
                ret = ueAppLimHdlRRCSecModeCmd(ueAppCb);
                ueAppCb->drpSecMode = TRUE;
             }
#endif
             break;
           }
/* ue005.101: Added support for UeCapability */
#ifdef UE_RAD_CAP
          case C1_UECAPENQUIRY: /* Ue Cap Enq */
          {
             /* ue007.101:ccpu00117835 Transaction ID used same as enodeb */
             ueAppCb->rcvdTxId.rrc_Cap_InfoTxId =
                               dlDcchPdu->dcchMsg.message.val.c1.val.ueCapEnquiry.rrc_TrnsxnId.val;
#ifdef TOTAL_ENB
              /* ue009.101: Added feature to drop the diffrent RRC messages.
               *  depends on the RRC timer. */
             if(UE_RRC_TIMER != UE_RRC_CAPENQ_TMR)
             {
               ret = ueAppLimHdlRRCUeCapEnq(ueAppCb);
             }
             else
             {
               printf("Blocking ue RRCUeCapEnq message \n");
               return (ROK);
             }
#else /* #ifdef TOTAL_ENB */
             ret = ueAppLimHdlRRCUeCapEnq(ueAppCb);
#endif
             break;
           }
#endif
           default:
             break;
      }
   }
   else
   {
      ret = RFAILED;
      UELOGERROR(ERRCLS_ADD_RES, EUE016, (ErrVal)datIndSdus->hdr.ueId,
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
      case C1_RRCCONSETUP: /* Connection Setup */
         {
#ifdef TOTAL_ENB
            /* ue009.101: Added feature to drop the diffrent RRC messages.
             *  depends on the RRC timer. */
            if(UE_RRC_TIMER != UE_RRC_CONSETUP_TMR)
            {
               ret = ueAppRcvRRCConSetup(datIndSdus);
            }
            else
            {
               printf("Blocking ConnectionSetup complete message UE_RRC_TIMER = %d\n", UE_RRC_TIMER);
               return (ROK);
            }
#else /* #ifdef TOTAL_ENB */
            ret = ueAppRcvRRCConSetup(datIndSdus);
#endif
         }
         break; 
#ifdef TOTAL_ENB
      case C1_RRCCONREESTB:
         {
            if(UE_RRC_TIMER != UE_RRC_REEST_TMR)
            {
               ret = ueAppRcvRRCConReestab(datIndSdus);
            }
            else
            {
               printf("Blocking re establisment complete message \n");
               return (ROK);
            }
         }
         break;
      case C1_RRCCONREESTBREJ:
         {
            if(UE_RRC_TIMER != UE_RRC_REEST_TMR)
            {
               ret = ueAppRcvRRCConReestabRej(datIndSdus);
            }
            else
            {
               printf("Blocking re establisment complete message \n");
               return (ROK);
            }
         }
         break;
#endif /* #ifdef TOTAL_ENB */
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
UeAppCb       *ueAppCb
)
#else
PUBLIC S16 ueAppLimHdlUeEvnt(ueEvnt, ueAppCb)
CmNasEvnt     *ueEvnt;
UeAppCb       *ueAppCb;
#endif
{
   S16 ret = RFAILED;

   TRC2(ueAppLimHdlUeEvnt);

   UE_DBGP_INFO((UE_PRNTBUF,
      "ueAppLimHdlUeEvnt:Processing the received UE event cellId %d ueId %d", ueAppCb->cellId, ueAppCb->ueId));

   /* ue002.101: Multi ue support changes */
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
CmNasEvnt     *ueEvnt,
U8             msgType,
UeAppCb       *ueAppCb
)
#else
PUBLIC S16 ueAppLimSndToLower(ueEvnt, msgType, ueAppCb)
CmNasEvnt     *ueEvnt;
U8             msgType;
UeAppCb       *ueAppCb;
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
      /* ue007.101: Nas event is freed in calling function in error case */

      RETVALUE(ret);
   }

   /* Build the associated RRC SDU */
   /* ue002.101: Multi ue support changes */
   switch(msgType)
   {
      case C1_ULINFOTFR:
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
      case C1_RRCCONSETUPCOMPL:
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

   /* ue008.101: Check the hoState of ueAppCb and then do the appropriate value setting */

   if(ueAppCb->hoState == 0)
   {
#ifdef TOTAL_ENB
      /* ue009.101: Added feature to drop the diffrent RRC messages.
       *  depends on the RRC timer. */
      if(UE_RRC_TIMER != UE_RRC_RECONFIG_TMR)
      { 
         ret = ueAppUtlBldRRCConReCfgComplete(&pdu, transId);
      }
      else
      {
         printf("Blocking Reconfiguration Complete \n");
         RETVALUE(ROK);
      }
#else
      ret = ueAppUtlBldRRCConReCfgComplete(&pdu, transId);
#endif
      if(ROK != ret)
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE024, (ErrVal)ret,
               "ueAppLimHdlRRCConReCfg : Could not build the RRC \
               Reconfiguration Complete\n"); 
            RETVALUE(ret);
      }
      /*ue002.101: Multi ue support changes */ 
      RETVALUE(ueAppLimSndRRCMsg(pdu, ueAppCb));
   }
   RETVALUE(ROK);

} /* End of ueAppLimHdlRRCConReCfg */


/* ue003.101: Added support for detach */
/*
*
*       Fun:   ueAppRcvRRCConRls
*       
*       Desc:  This function handles RRC Connection Release from eNodeB. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppRcvRRCConRls
(
UeAppCb *ueAppCb
)
#else
PUBLIC S16 ueAppRcvRRCConRls(ueAppCb)
UeAppCb *ueAppCb;
#endif
{
   CellCb   *cell = NULLP;
   UeCb     *ue = NULLP;
   S16      idx = 0;
   S16      ret = 0;
   TRC2(ueAppRcvRRCConRls);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppRcvRRCConRls : Handling RRC Connection Release "));

   /* Change the State of the UE to UE_ECM_IDLE */
   ueAppCb->ecmCb.state =  UE_ECM_IDLE;

   ueUtlFndCell(ueAppCb->cellId, &cell);
   if (cell == NULLP)
   {
      printf(" \n Unable to get CellCb\n");
      RETVALUE(RFAILED);
   }
   if((ret = ueUtlFndUe(cell,ueAppCb->ueId, &ue)) != ROK)
   {
     printf("\n Unable to get UECb\n");
     RETVALUE(RFAILED); 
   }
  
   for(idx=0; idx<UE_NUM_RLC_RB_PER_UE; idx++)
   {
      printf("\n Values reset for RB %d\n", idx);
      ue->rlc.rbArr[idx].cur_um_seq = 0;
      ue->rlc.rbArr[idx].rcvd_um_seq = 0;
      /* ue008.101: Fixed RRC connection release related issue. */

      ue->rlc.snLen = 2; /* 10 bits SN Len */
      ue->rlc.rbArr[idx].mBuf = NULLP;
      ue->rlc.rbArr[idx].lcId = idx;

      ue->rlc.rbArr[idx].pdcpSn = 0;
      ue->rlc.rbArr[idx].rcvdPdcpSn = 0;
   }
   ue->isDel = 1;
   printf("\n ***************************************** \n");
   printf("\n The State of the UE is changed to ECM_IDLE\n");
   printf("\n ***************************************** \n");
   
   RETVALUE(ROK);

} /* End of ueAppRcvRRCConRls */



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
   /* ue007.101:ccpu00117835 Transaction ID used same as enodeb */
   ret = ueAppUtlBldRRCSecModeComplete(&pdu,ueAppCb->rcvdTxId.rrc_Sec_ModeTxId);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE025, (ErrVal)ret,
         "ueAppLimHdlRRCSecModeCmd : Could not build the Secuirty \
         Mode Complete\n"); 

      RETVALUE(ret);
   }

   /* ue002.101: Multi ue support changes */
   RETVALUE(ueAppLimSndRRCMsg(pdu,ueAppCb));

} /* End of ueAppLimHdlRRCSecModeCmd */

/* ue005.101: Added support for UeCapability */
#ifdef UE_RAD_CAP
/*
*
*       Fun:   ueAppLimHdlRRCUeCapEnq
*       
*       Desc:  This function handles RRC Ue Capability Enq from eNodeB. 
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppLimHdlRRCUeCapEnq
(
UeAppCb *ueAppCb
)
#else
PUBLIC S16 ueAppLimHdlRRCUeCapEnq(ueAppCb)
UeAppCb *ueAppCb;
#endif
{
   NhuDatReqSdus *pdu = NULLP;
   S16 ret;

   TRC2(ueAppLimHdlRRCUeCapEnq);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppLimHdlRRCUeCapEnq: Handling Ue Capability Enquiry Request"));
   /* ue007.101:ccpu00117835 Transaction ID used same as enodeb */
   ret = ueAppUtlBldRRCUeCapInfo(&pdu,ueAppCb->rcvdTxId.rrc_Cap_InfoTxId);
   if(ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE025, (ErrVal)ret,
         "ueAppLimHdlRRCUeCapEnq : Could not build the Ue Cap Info \
         message \n"); 

      RETVALUE(ret);
   }

   /* ue002.101: Multi ue support changes */
   RETVALUE(ueAppLimSndRRCMsg(pdu,ueAppCb));

} /* End of ueAppLimHdlRRCUeCapEnq */

#endif

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

   /* ue002.101: Multi ue support changes */
   ueSimAppCb.rrcSapCb->pst.event = EVTNHUDATREQ;
   
   /* Invoking Tightly copuled primitive */
   ret = UeUiNhuDatReq(&(ueSimAppCb.rrcSapCb->pst), ueSimAppCb.rrcSapCb->spId, 
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


#ifndef SS_CAVIUM
/*
*
*       Fun:   ueAppLimSndPdcpMsg
*       
*       Desc:  This is a sends a IP data packet to PDCP after inserting the
*              proper checksum.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppLimSndPdcpMsg
(
CONSTANT U8 *ipPkt,
U32          len,
UeAppCb     *ueAppCb
)
#else
PUBLIC S16 ueAppLimSndPdcpMsg(ipPkt, len, ueAppCb)
CONSTANT U8 *ipPkt;
U32          len;
UeAppCb     *ueAppCb;
#endif
{
   /* ue002.101: Removed unnecessary code */
   Buffer *mBuf;
   S16     ret;

   /* ue008.101: Added new local Variables*/
   U8      ipHdrLen = 0;
   U16     dstPort = 0;
   U8      lcId = 0;

   TRC2(ueAppLimSndPdcpMsg);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppLimSndPdcpMsg:Sending a message to PDCP"));
   /* Convert the received flat buf to mBuf */
   /* ue006.101: Changes for end to end performance support */
   UE_ALLOC_BUF(mBuf);
   if(mBuf == NULLP)
   { 
      UELOGERROR(ERRCLS_ADD_RES, EUE026, (ErrVal)0,
         "ueAppLimSndPdcpMsg : mBuf allocation failed\n"); 
      RETVALUE(RFAILED);
   }

   /* ue008.101: Dedicated Bearer support for lcId */
   ipHdrLen = (ipPkt[0] & 0x0F) * 4;

   dstPort = (ipPkt[ipHdrLen + 2] << 8 ) + ipPkt[ipHdrLen + 3];
#ifdef UESIM_TRIGGER_DRB_EST /* Default should be choosen by default */
   if( (ipPkt[9] == 6 ) || (ipPkt[9] == 17) )/* UDP is 17 and TCP is 6 */
   {
      if( dstPort < 1235)
      lcId = 3 ;/* default bearer */
      else
      lcId = 4 ;/* dedicated bearer */
   }
   else
#endif      
      lcId = 3; /* for all other protocol using default bearer */

   ret = SAddPstMsgMult((Data *)(ipPkt), (MsgLen)len, mBuf);

   if (ROK != ret)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE026, (ErrVal)ret,
         "ueAppLimSndPdcpMsg : Converting to mBuf failed\n"); 
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
   }


#ifdef CNE_UESIM_DEBUG
   SPrntMsg(mBuf, 0, 0);
#endif

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppLimSndPdcpMsg: Sending the PDU to eNodeB"));

   /* ue004.101: Passing proper ueIdx. Taken care of increasing CRNTI */
   /* ue002.101: Multi ue support changes */

   /* ue008.101: Added new parameter lcId in UeUiPjuDatReq(). */
   ret = UeUiPjuDatReq(&(ueSimAppCb.pdcpSapCb->pst), 
                       ueSimAppCb.pdcpSapCb->spId,
                       mBuf,ueAppCb->cellId,ueAppCb->ueId, lcId);


   RETVALUE(ret);

}
#else
/* 
*
*       Fun:   ueAppLimSndPdcpMsg
*       
*       Desc:  This is a sends a IP data packet to PDCP after inserting the
*              proper checksum.
*       
*       Ret:   ROK
*       
*       Notes: None
*              
*       File:  ue_app_li.c
*       
*/
#ifdef ANSI
PUBLIC S16 ueAppLimSndPdcpMsg
(
Void    *arg,
UeAppCb *ueAppCb
)
#else
PUBLIC S16 ueAppLimSndPdcpMsg(arg,ueAppCb)
Void    *arg;
UeAppCb *ueAppCb;
#endif
{

   U8 *ipPkt;
   U8  numBufs;
   U8  l2headerSkip;
   /* ue008.101: Added new local variable.*/
   U8      lcId = 0;
  U16     dstPort = 0;
   S16 ret = ROK;
   Buffer *mBuf;
   cvmx_buf_ptr_t ueBufPtr;
   cvmx_wqe_t    *work;

   TRC2(ueAppLimSndPdcpMsg);

   UE_DBGP_INFO((UE_PRNTBUF,
            "ueAppLimSndPdcpMsg:Sending a message to PDCP"));

   work = (cvmx_wqe_t *) arg;
   /* Convert the received flat buf to mBuf */
   UE_ALLOC_BUF(mBuf);

   if (work->word2.s.bufs == 0)
   {
      ipPkt = (U8 *)cvmx_phys_to_ptr((U64)work->packet_data);
      ret = SAddPstMsgMult((Data*)(ipPkt + UE_APP_L2_HEADER_SIZE), 
                           (MsgLen)work->len - UE_APP_L2_HEADER_SIZE , mBuf);
      if (ROK != ret)
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE027, (ErrVal)ret,
            "ueAppLimSndPdcpMsg : Converting to mBuf failed\n"); 
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
   }
   else
   {
      numBufs = work->word2.s.bufs;
      ueBufPtr = work->packet_ptr;
      l2headerSkip = UE_APP_L2_HEADER_SIZE;
      ipPkt = (U8 *) cvmx_phys_to_ptr(ueBufPtr.s.addr + l2headerSkip);
      ret = SAddPstMsgMult((Data*)(ipPkt), 
                           (MsgLen)(work->len - l2headerSkip), mBuf);
      if (ROK != ret)
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE028, (ErrVal)ret,
            "ueAppLimSndPdcpMsg : Converting to mBuf failed\n"); 
         SPutMsg(mBuf);
         RETVALUE(RFAILED);
      }
      
   }

#ifdef CNE_UESIM_DEBUG
   SPrntMsg(mBuf, 0, 0);
#endif


   /* ue008.101: Dedicated Bearer support for lcId. */
   if( (ipPkt[9] == 6 ) || (ipPkt[9] == 17) )/* UDP is 17 and TCP is 6 */
   {
      if( dstPort < 1235)
      lcId = 3 ;/* default bearer */
      else
      lcId = 4 ;/* dedicated bearer */
   }
   else
      lcId = 3; 
   /* ue004.101: Passing proper ueIdx. Taken care of increasing CRNTI */
   /* ue002.101: Multi ue support changes */
   /* ue008.101: Added new parameter lcId in UeUiPjuDatReq() */
   ret = UeUiPjuDatReq(&(ueAppCellCb.pdcpSapCb->pst), 
                        ueAppCellCb.pdcpSapCb->spId,
                        mBuf,((ueAppCb->ueId-UE_START_RNTI) % UE_NUM_PER_CELL),lcId);

   RETVALUE(ret);

}
#endif


/**********************************************************************
 
         End of file:     ue_app_li.c@@/main/1 - Sun Mar 28 22:59:21 2010
 
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
/main/1      ---       vp             1. Initial Release.
/main/1      ue001.101 rrm            2. decoding NAS pdu from RRC reconfig req 
/main/1+     ue002.101 sv             1. Multi ue support changes.
                                      2. Changes to support reading uesim
                                         configuration from file.
                                      3. Changes to support MSPD CL.
/main/1+     ue003.101 rp             1. Added support for detach.
                                      2. Added support for paging.
/main/1+     ue004.101 rk             1. Passing proper ueIdx. 
                                         Taken care of increasing CRNTI
/main/1+     ue005.101 cshekar        1. Added support for ue capability.
/main/1+     ue006.101 sriky          1. Performance tuning.
/main/1+     ue007.101 ms             1. enodeb TxId used .
                       rk             1. Memory double delete fix.
/main/1+     ue008.101 ragrawal       1. Added new header file inclusion.
                                      2. Added Dedicated Bearer support for lcId.
                                      3. Added new local variables in ueAppHdlDlDcchDatInd(),
                                         ueAppLimSndPdcpMsg() and ueAppLimSndPdcpMsg().
                                      4. Fixed RRC connection release related issue.
                                      5. Added new parameter lcId in UeUiPjuDatReq().
                                      6. HandOver Support Changes.
/main/1+    ue009.101 akaranth       1. Added feature to drop the diffrent RRC message
                                        depends on the RRC timer.
                                     2. Introduced new variable to make the accessing of 
                                        structure variable easy.
*********************************************************************91*/

