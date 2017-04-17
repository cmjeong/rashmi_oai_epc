/********************************************************************20**

     Name:    RRC 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    nhac_nhuutl.c

     Sid:      nhac_nhuutl.c@@/main/3 - Fri Jul  1 01:13:06 2011

     Prg:     rer

*********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_inet.h"        /* Inet header file             */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */
#include "cm_lte.h"        /* common LTE structures */
#include "ckw.h"            /* C-RLC interface */
#include "kwu.h"            /* D-RLC interface */
#include "crg.h"            /* C-MAC interface */
#include "cpj.h"            /* C-PDCP interface */
#include "pju.h"            /* D-PDCP interface */
#include "nhu.h"           /* RRC Upper Interface */
#include "cm_xta.h"
#include "nhac_acc.h"
#include "nh.h"
#include "lnh.h"
#include "cm_pasn.h"
#include "nhu_3gasn.h"     /* 3G RRC asn coding for Ue Capability */
#include <stdlib.h>        /* For atoi function */
/* external headers */

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_llist.x"      /* common link list */
#include "cm_lte.x"        /* common LTE structures */
#include "cm_xta.x"
#include "ckw.x"            /* C-RLC interface */
#include "kwu.x"            /* D-RLC interface */
#include "crg.x"            /* C-MAC interface */
#include "cpj.x"            /* C-PDCP interface */
#include "pju.x"            /* D-PDCP interface */
#if 0
#include "nhu_3gasn.x"     /* 3G RRC asn coding for Ue Capability */
#endif
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_acc_nhu.x"
#include "nh.x"

/******* UE Message filling functions ******************************

Connection Setup           --   nhAcUtlFillNhuDlCcchConSetup
Connection Reject          --   nhAcUtlFillNhuDlCcchConRej
Connection Reestablishment Reject --  nhAcUtlFillNhuDlCcchConReestRej
Security Mode Command      --   nhAcUtlFillNhuSecurityModeCmd
Connection Release         --   nhAcUtlFillNhuConRls
Paging                     --   nhAcUtlFillNhuPagingMsg
DL Transfer Information    --   nhAcUtlFillNhuInfoTfr
Connection Reconfiguration --   nhAcUtlFillNhuRrcConReCfgn
BCCH Msg                   --   nhAcUtlFillNhuNhuBCCH_BCHMsg
System Information         --   nhAcUtlFillNhuSysInfo
System Information Type1   --   nhAcUtlFillNhuSysInfoBlockType1

*******************************************************************/

EXTERN NhAccCpjVal  gCpjCfgStore[25];
EXTERN NhAccCrgVal  gCrgValStore[25];
EXTERN NhAccCkwVal  gCkwValStore[25];
#ifdef RRC_PHY_CFG_SUPP
EXTERN NhAccCtfVal  gCtfValStore[25];
#endif
PUBLIC U8 gValIdx=0;

/*
*
*       Fun:   nhAcUtlFillNhuDlCcchConSetup
*
*       Desc:  This function fills RRC Connection Setup Msg
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuDlCcchConSetup
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatRspSdus *nhuDatRspSdu
)
#else
PUBLIC S16 nhAcUtlFillNhuDlCcchConSetup(tcCb, spCb, nhuDatRspSdu)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuDatRspSdus *nhuDatRspSdu;
#endif
{
   NhuDL_CCCH_Msg *dlMsg;
   NhuRRCConSetup *conStUp;
   U32 rrc_transId;
   U8  rrcTransIdPres;

   TRC2(nhAcUtlFillNhuDlCcchConSetup);

   dlMsg = &(nhuDatRspSdu->sdu.m.dlCcchMsg.ccchMsg);

   FILL_UINT_TKN(dlMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(dlMsg->message.choice,DL_CCCH_MSGTYP_C1);
   FILL_UINT_TKN(dlMsg->message.val.c1.choice,C1_RRCCONSETUP);

   conStUp = &(dlMsg->message.val.c1.val.rrcConSetup);

   FILL_UINT_TKN(conStUp->pres,PRSNT_NODEF);

   rrcTransIdPres = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);

   if (rrcTransIdPres)
   {
      rrc_transId = 0;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(conStUp->rrc_TrnsxnId,rrc_transId);
   }
   else
   {
      FILL_UINT_TKN(conStUp->rrc_TrnsxnId, NOTPRSNT);
      conStUp->rrc_TrnsxnId.pres = NOTPRSNT;
   }

   FILL_UINT_TKN(conStUp->criticalExtns.choice,CRITICALEXTNS_C1);

   if(conStUp->criticalExtns.choice.val == CRITICALEXTNS_C1)
   {
      FILL_UINT_TKN(conStUp->criticalExtns.val.c1.choice,C1_RRCCONSETUP_R8);
      if(conStUp->criticalExtns.val.c1.choice.val == C1_RRCCONSETUP_R8)
      {
         FILL_UINT_TKN(conStUp->criticalExtns.val.c1.val.rrcConSetup_r8.pres,
                       PRSNT_NODEF);

         /* Filling Radio Resource Configuration */
         nhAcUtlFillNhuRadioResCfgDedi(tcCb, spCb,
                  &(conStUp->criticalExtns.val.c1.val.rrcConSetup_r8.\
                  radioResourceConfigDedicated),
                  (Ptr)(nhuDatRspSdu));
         FILL_UINT_TKN(conStUp->criticalExtns.val.c1.val.rrcConSetup_r8.\
               nonCriticalExtn.pres,PRSNT_NODEF);
      }
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuDlCcchConSetup */

/*
*
*       Fun:   nhAcUtlFillNhuDlCcchConRej
*
*       Desc:  This function fills RRC Connection Reject Msg
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuDlCcchConRej
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatRspSdus *nhuDatRspSdu
)
#else
PUBLIC S16 nhAcUtlFillNhuDlCcchConRej(tcCb, spCb, nhuDatRspSdu)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuDatRspSdus *nhuDatRspSdu;
#endif
{
   NhuDL_CCCH_Msg *dlMsg;
   NhuRRCConRej   *conRej;
   U32            waitTime;
   U8             failForEnc = 0;
#ifdef RRC_REL11
   U32            extendedwaitTime = 1;
#endif
   TRC2(nhAcUtlFillNhuDlCcchConRej);

   dlMsg = &(nhuDatRspSdu->sdu.m.dlCcchMsg.ccchMsg);

   FILL_UINT_TKN(dlMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(dlMsg->message.choice,DL_CCCH_MSGTYP_C1);
   FILL_UINT_TKN(dlMsg->message.val.c1.choice,C1_RRCCONREJ);

   conRej = &(dlMsg->message.val.c1.val.rrcConRej);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "failForEnc",
                        &(failForEnc));
   if (failForEnc)
   {
      NHAC_FILL_U8_U32_TKN(conRej->pres, NOTPRSNT, NOTPRSNT);
      NHAC_FILL_U8_U32_TKN(conRej->criticalExtns.choice, NOTPRSNT, NOTPRSNT);
      NHAC_FILL_U8_U32_TKN(conRej->criticalExtns.val.c1.choice, NOTPRSNT, NOTPRSNT);
      NHAC_FILL_U8_U32_TKN(conRej->criticalExtns.val.c1.val.rrcConRej_r8.pres,
                NOTPRSNT, NOTPRSNT);
   }
   else
   {
      FILL_UINT_TKN(conRej->pres,PRSNT_NODEF);
      FILL_UINT_TKN(conRej->criticalExtns.choice,CRITICALEXTNS_C1);

      if(conRej->criticalExtns.choice.val == CRITICALEXTNS_C1)
      {
         FILL_UINT_TKN(conRej->criticalExtns.val.c1.choice,C1_RRCCONREJ_R8);
         if(conRej->criticalExtns.val.c1.choice.val == C1_RRCCONREJ_R8)
         {
            FILL_UINT_TKN(conRej->criticalExtns.val.c1.val.rrcConRej_r8.pres,
                          PRSNT_NODEF);

            waitTime = 1;

            /* Get the wait time from xml */
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "waitTime",
                           &(waitTime));
            FILL_UINT_TKN(conRej->criticalExtns.val.c1.val.rrcConRej_r8.waitTime,
                          waitTime);
            FILL_UINT_TKN(conRej->criticalExtns.val.c1.val.rrcConRej_r8.\
                     nonCriticalExtn.pres, PRSNT_NODEF);
#ifdef RRC_REL11
            FILL_OCT_STR(conRej->criticalExtns.val.c1.val.rrcConRej_r8.\
                     nonCriticalExtn.lateNonCriticalExtn, 1, 1, nhuDatRspSdu);
            FILL_UINT_TKN(conRej->criticalExtns.val.c1.val.rrcConRej_r8.\
                     nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "extendedwaitTime",
                           &(extendedwaitTime));
            FILL_UINT_TKN(conRej->criticalExtns.val.c1.val.rrcConRej_r8.\
                     nonCriticalExtn.nonCriticalExtn.extendedWaitTime_r10, extendedwaitTime);
            FILL_UINT_TKN(conRej->criticalExtns.val.c1.val.rrcConRej_r8.\
                     nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
#endif
         }
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuDlCcchConRej */

/*
*
*       Fun:   nhAcUtlFillNhuDlCcchConReestRej
*
*       Desc:  This function fills RRC Connection Re-establishment
*              Reject Msg
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuDlCcchConReestbRej
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatRspSdus *nhuDatRspSdu
)
#else
PUBLIC S16 nhAcUtlFillNhuDlCcchConReestbRej(tcCb, spCb, nhuDatRspSdu)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuDatRspSdus *nhuDatRspSdu;
#endif
{
   NhuDL_CCCH_Msg *dlMsg;
   NhuRRCConReestbRej *conReestbRej;
   U8    failForEnc = 0;
  
   TRC2(nhAcUtlFillNhuDlCcchConReestbRej);

   dlMsg = &(nhuDatRspSdu->sdu.m.dlCcchMsg.ccchMsg);

   FILL_UINT_TKN(dlMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(dlMsg->message.choice,DL_CCCH_MSGTYP_C1);
   FILL_UINT_TKN(dlMsg->message.val.c1.choice,C1_RRCCONREESTBREJ);

   conReestbRej = &(dlMsg->message.val.c1.val.rrcConReestbRej);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "failForEnc",
                        &(failForEnc));
   if (failForEnc)
   {
      NHAC_FILL_U8_U32_TKN(conReestbRej->pres, NOTPRSNT, NOTPRSNT);
      NHAC_FILL_U8_U32_TKN(conReestbRej->criticalExtns.choice,
                           NOTPRSNT, NOTPRSNT);
      NHAC_FILL_U8_U32_TKN(conReestbRej->criticalExtns.val.rrcConReestbRej_r8.pres,
                                 NOTPRSNT, NOTPRSNT);
      NHAC_FILL_U8_U32_TKN(conReestbRej->criticalExtns.val.rrcConReestbRej_r8.\
            nonCriticalExtn.pres, NOTPRSNT, NOTPRSNT);
   }
   else
   {
      FILL_UINT_TKN(conReestbRej->pres,PRSNT_NODEF);
      FILL_UINT_TKN(conReestbRej->criticalExtns.choice,
                      CRITICALEXTNS_RRCCONREESTBREJ_R8);

      if(conReestbRej->criticalExtns.choice.val ==
                                             CRITICALEXTNS_RRCCONREESTBREJ_R8)
      {
         FILL_UINT_TKN(conReestbRej->criticalExtns.val.rrcConReestbRej_r8.pres,
                       PRSNT_NODEF);
         FILL_UINT_TKN(conReestbRej->criticalExtns.val.rrcConReestbRej_r8.\
                  nonCriticalExtn.pres,PRSNT_NODEF);
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuDlCcchConReestbRej */

/*
*
*       Fun:   nhAcUtlFillNhuSecurityModeCmd
*
*       Desc:  This function fills Downlink Security Mode Command
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuSecurityModeCmd
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhuDatReqSdu
)
#else
PUBLIC S16 nhAcUtlFillNhuSecurityModeCmd(tcCb, spCb, nhuDatReqSdu)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuDatReqSdus *nhuDatReqSdu;
#endif
{
   NhuDL_DCCH_Msg     *dlMsg = NULLP;
   NhuSecModeCmd      *secModeCmd = NULLP;
   U32                rrc_transId;
   U8                 rrcTransIdPres;
   NhuSecAlgorithmConfig          *securityCfg = NULLP;
   U8                 pdcpId = 0;
   U8                 integrityAlgo=1, cipheringAlgo=1;
  
   TRC2(nhAcUtlFillNhuSecurityModeCmd);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpId", &pdcpId);
   nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.pdcpId = pdcpId;

   dlMsg = &(nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.m.dcchMsg);

   FILL_UINT_TKN(dlMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(dlMsg->message.choice,DL_CCCH_MSGTYP_C1);
   FILL_UINT_TKN(dlMsg->message.val.c1.choice,C1_SECURITYMODECMD);

   secModeCmd = &(dlMsg->message.val.c1.val.securityModeCmd);

   FILL_UINT_TKN(secModeCmd->pres,PRSNT_NODEF);

   rrcTransIdPres = 1;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(secModeCmd->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      NHAC_FILL_U8_U32_TKN(secModeCmd->rrc_TrnsxnId, NOTPRSNT, NOTPRSNT);
   }
   FILL_UINT_TKN(secModeCmd->criticalExtns.choice, C1_SECURITYMODECMD_R8);
   FILL_UINT_TKN(secModeCmd->criticalExtns.val.c1.choice, 0);
   FILL_UINT_TKN(secModeCmd->criticalExtns.val.c1.val.securityModeCmd_r8.pres,
               PRSNT_NODEF);

   /* Security Configuration */
   FILL_UINT_TKN(secModeCmd->criticalExtns.val.c1.val.securityModeCmd_r8.securityConfigSMC.pres,1);
   securityCfg = &(secModeCmd->criticalExtns.val.c1.val.securityModeCmd_r8.\
               securityConfigSMC.securityAlgorithmConfig);
   FILL_UINT_TKN(securityCfg->pres, PRSNT_NODEF);


   FILL_UINT_TKN(securityCfg->integrityProtAlgorithm,
                     NhuSecAlgorithmConfigintegrityProtAlgorithmeia1Enum);

   /* Read Integrity algorithm from xml */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "integrityAlgo",
                  &integrityAlgo);

   if (1 != integrityAlgo)   
   {
      securityCfg->integrityProtAlgorithm.pres = NOTPRSNT;
   }

   FILL_UINT_TKN(securityCfg->cipheringAlgorithm,
                     NhuSecAlgorithmConfigcipheringAlgorithmeea1Enum);

   /* Read Ciphering algorithm from xml */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "cipheringAlgo",
                  &cipheringAlgo);

   if (1 != cipheringAlgo)
   {
      securityCfg->cipheringAlgorithm.pres = NOTPRSNT;
   }

   FILL_UINT_TKN(secModeCmd->criticalExtns.val.c1.val.securityModeCmd_r8.\
                 nonCriticalExtn.pres, PRSNT_NODEF);

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuSecurityModeCmd */

/*
*
*       Fun:   nhAcUtlFillNhuConRls
*
*       Desc:  This function fills RRC Connection Release Message
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuConRls
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhuDatReqSdu
)
#else
PUBLIC S16 nhAcUtlFillNhuConRls(tcCb, spCb, nhuDatReqSdu)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuDatReqSdus *nhuDatReqSdu;
#endif
{
   NhuDL_DCCH_Msg     *dlMsg = NULLP;
   NhuRRCConRls       *conRls = NULLP;
   U32                rrc_transId;
   U8                 rrcTransIdPres;
   U8                 pdcpId = 0;
#ifdef RRC_REL11
   U8                 idx=0;
   U32                arfcn_Valueutra = 1;
   U32                extendedWaitTime = 1;
#endif
   TRC2(nhAcUtlFillNhuConRls);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpId", &pdcpId);
   nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.pdcpId = pdcpId;

   dlMsg = &(nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.m.dcchMsg);

   FILL_UINT_TKN(dlMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(dlMsg->message.choice,DL_CCCH_MSGTYP_C1);
   FILL_UINT_TKN(dlMsg->message.val.c1.choice,C1_RRCCONRLS);

   conRls = &(dlMsg->message.val.c1.val.rrcConRls);

   FILL_UINT_TKN(conRls->pres,PRSNT_NODEF);

   rrcTransIdPres = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(conRls->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      NHAC_FILL_U8_U32_TKN(conRls->rrc_TrnsxnId, NOTPRSNT, NOTPRSNT);
   }
   FILL_UINT_TKN(conRls->criticalExtns.choice, CRITICALEXTNS_C1);
   FILL_UINT_TKN(conRls->criticalExtns.val.c1.choice, C1_RRCCONRLS_R8);
   FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.pres,
               PRSNT_NODEF);
   FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.releaseCause,
               NhuRlsCauseloadBalancingTAUrequiredEnum);

   /* Redirection Information Filling */
   FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.redirectedCarrierInfo.\
               choice,REDIRECTEDCARRIERINFO_EUTRA);

   FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.redirectedCarrierInfo.\
               val.eutra,1);
#ifdef RRC_REL11
   if(conRls->criticalExtns.val.c1.val.rrcConRls_r8.redirectedCarrierInfo.\
                     choice.val==6)
   {
     FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.redirectedCarrierInfo.\
               val.utra_TDD_r10.noComp, 1);
     CMXTA_GET_MEM(nhuDatReqSdu,(conRls->criticalExtns.val.c1.val.rrcConRls_r8.redirectedCarrierInfo.\
           val.utra_TDD_r10.noComp.val)*sizeof(NhuARFCN_ValueUTRA),
           &(conRls->criticalExtns.val.c1.val.rrcConRls_r8.redirectedCarrierInfo.val.utra_TDD_r10.member))
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "arfcn_Valueutra", &arfcn_Valueutra);
     for(idx=0;idx<conRls->criticalExtns.val.c1.val.rrcConRls_r8.redirectedCarrierInfo.\
                          val.utra_TDD_r10.noComp.val; idx++)
     {
       FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.redirectedCarrierInfo.\
               val.utra_TDD_r10.member[idx], arfcn_Valueutra);
     }
   }
#endif
   /* Mobility Related information Filling */
   FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.\
               idleModeMobilityCntrlInfo.pres, NOTPRSNT);

#ifndef RRC_REL11
   FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.\
               nonCriticalExtn.pres, NOTPRSNT);
#else
   FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.\
               nonCriticalExtn.pres, PRSNT_NODEF);
   FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.\
               nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
   FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.\
               nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "extendedWaitTime", &extendedWaitTime);
   FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.nonCriticalExtn.\
         nonCriticalExtn.nonCriticalExtn.extendedWaitTime_r10, extendedWaitTime);
   FILL_UINT_TKN(conRls->criticalExtns.val.c1.val.rrcConRls_r8.\
         nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
#endif

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuConRls */

/*
*
*       Fun:   nhAcUtlFillNhuPagingMsg
*
*       Desc:  Fills Paging message (DL PCCH)
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuPagingMsg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhDatReqEvntSdu,
U8 sfn,
U8 subFrmNo
)
#else
PUBLIC S16 nhAcUtlFillNhuPagingMsg(tcCb, spCb, nhDatReqEvntSdu, sfn, subFrmNo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuDatReqSdus *nhDatReqEvntSdu;
U8 sfn;
U8 subFrmNo;
#endif
{
   NhuPCCH_Msg *pcchMsg;
   NhuPag *page;
   Mem   sMem;
   U8    numOfUe;
   U8    stateOfUe;
   U8    ueIdType;
   U8    noOfImsi;
   U16   idx, idx1;
   Bool  tmsiPres;
#ifdef LTERRC_REL9
   Bool isCMASIndEnabled; 
#endif /*LTERRC_REL9*/

   TRC2(nhAcUtlFillNhuPagingMsg);

   sMem.region = 0;
   sMem.pool = 0;

   pcchMsg = &(nhDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmn.pcchMsg);
   stateOfUe = 0; /*-- Idle --*/
   numOfUe = 1;
   ueIdType = 0;
   noOfImsi = 1;

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "numOfUe", &numOfUe);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "stateOfUe", &stateOfUe);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "ueIdType", &ueIdType);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "noOfImsi", &noOfImsi);

   FILL_U8_FRAMENUM(nhDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmnMsgInfo.timingInfo,
                     sfn, subFrmNo);
   FILL_UINT_TKN(pcchMsg->pres, PRSNT_NODEF);
   FILL_UINT_TKN(pcchMsg->message.choice,0);
   if(!(pcchMsg->message.choice.val))
   {
      FILL_UINT_TKN(pcchMsg->message.val.c1.choice,0);
      page = &(pcchMsg->message.val.c1.val.paging);
      if (stateOfUe == 0)
      {
         FILL_UINT_TKN(page->pres, PRSNT_NODEF);
      }
      else
      {
         FILL_UINT_TKN(page->pres, PRSNT_NODEF);
         FILL_UINT_TKN(page->systemInfoModfn, NhuPagsystemInfoModfntrueEnum);
         FILL_UINT_TKN(page->etws_Ind,0);
         FILL_UINT_TKN(page->pagingRecordLst.noComp, numOfUe);
         CMXTA_GET_MEM(nhDatReqEvntSdu, (page->pagingRecordLst.noComp.val)*
               (sizeof(NhuPagRecord)),&(page->pagingRecordLst.member));
         for(  idx = 0;  idx < (page->pagingRecordLst.noComp.val); idx++)
         {
            FILL_UINT_TKN(page->pagingRecordLst.member[idx].pres, PRSNT_NODEF);
            FILL_UINT_TKN(page->pagingRecordLst.member[idx].cn_Domain,
                           NhuPagRecordcn_DomainpsEnum);
            FILL_UINT_TKN(page->pagingRecordLst.member[idx].ue_Identity.choice,
                               ueIdType);
            switch(ueIdType)
            {
               case 0:
                  tmsiPres = TRUE;
                  cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "tmsiPres", &tmsiPres);
                  if(tmsiPres)
                  {
                     FILL_UINT_TKN(page->pagingRecordLst.member[idx].ue_Identity.
                                     val.s_TMSI.pres, PRSNT_NODEF);
                     FILL_BIT_STR(page->pagingRecordLst.member[idx].ue_Identity.
                                     val.s_TMSI.mmec, 8, 1, nhDatReqEvntSdu);
                     FILL_BIT_STR(page->pagingRecordLst.member[idx].ue_Identity.
                                     val.s_TMSI.m_TMSI, 32, (U8)idx, nhDatReqEvntSdu);
                  }
                  break;

               case 1:
                  FILL_UINT_TKN(page->pagingRecordLst.member[idx].ue_Identity.
                                    val.imsi.noComp, noOfImsi);
                  CMXTA_GET_MEM(nhDatReqEvntSdu,
                           (page->pagingRecordLst.member[idx].ue_Identity.val.
                              imsi.noComp.val) * (sizeof(NhuIMSI_Digit)),
                           &(page->pagingRecordLst.member[idx].ue_Identity.
                              val.imsi.member));
                  for(  idx1 = 0;  idx1 < (page->pagingRecordLst.noComp.val); idx1++)
                  {
                     FILL_UINT_TKN(page->pagingRecordLst.member[idx].ue_Identity.
                              val.imsi.member[idx1],  0);
                  }

                  break;
            }

            /*-- ur_Identity and pagingCause are FSS --*/
         }
#ifdef LTERRC_REL9
/*R9 upgrade: filling new IEs added*/
         FILL_UINT_TKN(page->nonCriticalExtn.pres, PRSNT_NODEF);
         FILL_OCT_STR(page->nonCriticalExtn.lateNonCriticalExtn, 1, 1,\
               nhDatReqEvntSdu);
         FILL_UINT_TKN(page->nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
         
         isCMASIndEnabled = FALSE;
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,\
               "isCMASIndEnabled", &isCMASIndEnabled);
         /* if CMAS ind is enabled then only fill the CMAS r9 ie else dont fill it*/
         if (isCMASIndEnabled)
         {
            NHAC_FILL_U8_U32_TKN(page->nonCriticalExtn.nonCriticalExtn.cmas_Ind_r9,\
                  PRSNT_NODEF,NhuPag_v920_IEscmas_Ind_r9trueEnum);
         }
         
         NHAC_FILL_U8_U32_TKN(page->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.pres,\
               NOTPRSNT, 0);
#endif /*LTERRC_REL9*/
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuPagingMsg */


/*
*
*       Fun:   nhAcUtlFillNhuInfoTfr
*
*       Desc:  Fills info DL DCCH Downlink Information Transfer message  
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuInfoTfr
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhDatReqEvntSdu,
U8 sfn,
U8 subFrmNo
)
#else
PUBLIC S16 nhAcUtlFillNhuInfoTfr(tcCb, spCb, nhDatReqEvntSdu, sfn, subFrmNo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuDatReqSdus *nhDatReqEvntSdu;
U8 sfn;
U8 subFrmNo;
#endif
{
   NhuDL_DCCH_Msg *dcchMsg;
   NhuDLInfoTfr *infoTfrMsg;
   NhuDLInfoTfr_r8_IEs *itIEs;
   U32 rrc_transId;
   U8  rrcTransIdPres;
   U8 infoChoice;
   U8 pdcpId;

   TRC2(nhAcUtlFillNhuInfoTfr);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpId", &pdcpId);
   nhDatReqEvntSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.pdcpId = pdcpId;
   dcchMsg = &(nhDatReqEvntSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.m.dcchMsg);
   FILL_UINT_TKN(dcchMsg->pres, PRSNT_NODEF);
   FILL_UINT_TKN(dcchMsg->message.choice,DL_DCCH_MSGTYP_C1);
   FILL_UINT_TKN(dcchMsg->message.val.c1.choice, C1_DLINFOTFR);
   infoTfrMsg = &(dcchMsg->message.val.c1.val.dlInfoTfr);
   FILL_UINT_TKN(infoTfrMsg->pres, PRSNT_NODEF);

   /*-Get rrc_Transation ID -*/
   rrcTransIdPres = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 0;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(infoTfrMsg->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      NHAC_FILL_U8_U32_TKN(infoTfrMsg->rrc_TrnsxnId, NOTPRSNT, NOTPRSNT);
   }

   FILL_UINT_TKN(infoTfrMsg->criticalExtns.choice,CRITICALEXTNS_C1);
   FILL_UINT_TKN(infoTfrMsg->criticalExtns.val.c1.choice, C1_DLINFOTFR_R8);
   itIEs = &(infoTfrMsg->criticalExtns.val.c1.val.dlInfoTfr_r8);
   FILL_UINT_TKN(itIEs->pres, PRSNT_NODEF);

   /*-- Get Information Choice --*/
   infoChoice = 0; /*- NAS3GPP */
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "infoChoice",
               &infoChoice);
   FILL_UINT_TKN(itIEs->dedicatedInfoTyp.choice, infoChoice);

   switch(infoChoice)
   {
      case 0: /*- NAS3GPP -*/
         FILL_OCT_STR(itIEs->dedicatedInfoTyp.val.dedicatedInfoNAS, 4, 1, nhDatReqEvntSdu);
         break;

      case 1: /*- CDMA2000 -*/
         FILL_OCT_STR(itIEs->dedicatedInfoTyp.val.dedicatedInfoCDMA2000_1XRTT,
                     4,  1, nhDatReqEvntSdu);
         break;
     case 2:
         FILL_OCT_STR(itIEs->dedicatedInfoTyp.val.dedicatedInfoCDMA2000_HRPD,
                     4,  1, nhDatReqEvntSdu);
         break;
   }

   FILL_UINT_TKN(itIEs->nonCriticalExtn.pres, PRSNT_NODEF);

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuInfoTfr */

#ifdef RRC_REL11
/*
*
*       Fun:   nhAcUtlFillNhuLoggedMeasurementCfg_r10
*
*       Desc:  Fills Logged Measurement config message (DL DCCH)
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuLoggedMeasurementCfg_r10
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
Ptr            evnt,
NhuDL_DCCH_Msg *dcchMsg
)
#else
PUBLIC S16 nhAcUtlFillNhuLoggedMeasurementCfg_r10(tcCb, spCb, evnt, dcchMsg)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
Ptr            evnt,
NhuDL_DCCH_Msg *dcchMsg
#endif
{
   NhuLoggedMeasurementCfg_r10 *loggedMeasurementCfg_r10;
   NhuLoggedMeasurementCfg_r10_IEs *loggedMeasurementCfgIEs;
   U8 idx=0;
   U8 idx1=0;
   U32 loggingDuration=0;
   U32 loggingInterval=0;

   TRC2(nhAcUtlFillNhuLoggedMeasurementCfg_r10);

   FILL_UINT_TKN(dcchMsg->pres, PRSNT_NODEF);
   FILL_UINT_TKN(dcchMsg->message.choice, DL_DCCH_MSGTYP_C1);
   FILL_UINT_TKN(dcchMsg->message.val.c1.choice, C1_LOGGEDMEASUREMENTCFG_R10__1);
   loggedMeasurementCfg_r10 = &(dcchMsg->message.val.c1.val.loggedMeasurementCfg_r10);
   FILL_UINT_TKN(loggedMeasurementCfg_r10->pres, PRSNT_NODEF);

   FILL_UINT_TKN(loggedMeasurementCfg_r10->criticalExtns.choice, CRITICALEXTNS_C1); /*  pavana check this CRITICALEXTNS_C10 value */
   FILL_UINT_TKN(loggedMeasurementCfg_r10->criticalExtns.val.c1.choice,\
         C1_LOGGEDMEASUREMENTCFG_R10__9); /* Venu */

   loggedMeasurementCfgIEs = &(loggedMeasurementCfg_r10->criticalExtns.val.c1.val.\
            loggedMeasurementCfg_r10);
   FILL_UINT_TKN(loggedMeasurementCfgIEs->pres, PRSNT_NODEF);
   FILL_UINT_TKN(loggedMeasurementCfgIEs->traceReference_r10.pres, PRSNT_NODEF);
   FILL_UINT_TKN(loggedMeasurementCfgIEs->traceReference_r10.plmn_Identity_r10.pres, PRSNT_NODEF);
   FILL_UINT_TKN(loggedMeasurementCfgIEs->traceReference_r10.plmn_Identity_r10.mcc.noComp, 3);
   CMXTA_GET_MEM(evnt,(loggedMeasurementCfgIEs->traceReference_r10.plmn_Identity_r10.\
            mcc.noComp.val)*(sizeof(NhuMCC_MNC_Digit)), &(loggedMeasurementCfgIEs->\
            traceReference_r10.plmn_Identity_r10.mcc.member));
   for(idx=0; idx<loggedMeasurementCfgIEs->traceReference_r10.plmn_Identity_r10.mcc.noComp.val;
         idx++)
   {
     FILL_UINT_TKN(loggedMeasurementCfgIEs->traceReference_r10.plmn_Identity_r10.mcc.member[idx],
           1);
   }
   FILL_UINT_TKN(loggedMeasurementCfgIEs->traceReference_r10.plmn_Identity_r10.mnc.noComp, 2);
   CMXTA_GET_MEM(evnt,(loggedMeasurementCfgIEs->traceReference_r10.plmn_Identity_r10.\
            mnc.noComp.val)*(sizeof(NhuMCC_MNC_Digit)), &(loggedMeasurementCfgIEs->\
            traceReference_r10.plmn_Identity_r10.mnc.member));
   for(idx=0; idx<loggedMeasurementCfgIEs->traceReference_r10.plmn_Identity_r10.mnc.noComp.val;
         idx++)
   {
     FILL_UINT_TKN(loggedMeasurementCfgIEs->traceReference_r10.plmn_Identity_r10.mnc.member[idx],
           1);
   }
   FILL_OCT_STR(loggedMeasurementCfgIEs->traceReference_r10.traceId_r10,3,1,evnt);
   FILL_OCT_STR(loggedMeasurementCfgIEs->traceRecordingSessionRef_r10,2,1,evnt);
   FILL_OCT_STR(loggedMeasurementCfgIEs->tce_Id_r10,1,1,evnt);
   FILL_BIT_STR(loggedMeasurementCfgIEs->absoluteTimeInfo_r10,48,1,evnt);

   FILL_UINT_TKN(loggedMeasurementCfgIEs->areaCfg_r10.choice, 0);
   if(loggedMeasurementCfgIEs->areaCfg_r10.choice.val==0)
   {
     FILL_UINT_TKN(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.noComp, 1);
     CMXTA_GET_MEM(evnt,(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.\
              noComp.val)*(sizeof(NhuCellGlobalIdEUTRA)),
           &(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.member));
     for(idx=0;idx<loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.noComp.val; idx++)
     {
       FILL_UINT_TKN(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.member[idx].\
             pres, PRSNT_NODEF);
       FILL_UINT_TKN(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.member[idx].\
             plmn_Identity.pres, PRSNT_NODEF);
       FILL_UINT_TKN(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.member[idx].\
             plmn_Identity.mcc.noComp, 3);
       CMXTA_GET_MEM(evnt,(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.\
             member[idx].plmn_Identity.mcc.noComp.val)*(sizeof(NhuMCC_MNC_Digit)), 
             &(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.member[idx].\
             plmn_Identity.mcc.member));
       for(idx1=0; idx1<loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.member[idx].\
             plmn_Identity.mcc.noComp.val; idx1++)
       {
         FILL_UINT_TKN(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.member[idx].\
               plmn_Identity.mcc.member[idx1],1);
       }
       FILL_UINT_TKN(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.member[idx].\
             plmn_Identity.mnc.noComp, 2);
       CMXTA_GET_MEM(evnt,(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.\
             member[idx].plmn_Identity.mnc.noComp.val)*(sizeof(NhuMCC_MNC_Digit)), 
             &(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.member[idx].\
             plmn_Identity.mnc.member));
       for(idx1=0; idx1<loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.member[idx].\
             plmn_Identity.mnc.noComp.val; idx1++)
       {
         FILL_UINT_TKN(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.member[idx].\
               plmn_Identity.mnc.member[idx1],1);
       }
       FILL_BIT_STR(loggedMeasurementCfgIEs->areaCfg_r10.val.cellGlobalIdLst_r10.member[idx].\
             cellIdentity, 28,1,evnt);
     }
   }
   else
   {
     FILL_UINT_TKN(loggedMeasurementCfgIEs->areaCfg_r10.val.trackingAreaCodeLst_r10.noComp, 1);
     CMXTA_GET_MEM(evnt,(loggedMeasurementCfgIEs->areaCfg_r10.val.trackingAreaCodeLst_r10.\
             noComp.val)*(sizeof(NhuTrackingAreaCode)), 
             &(loggedMeasurementCfgIEs->areaCfg_r10.val.trackingAreaCodeLst_r10.member));
     for(idx=0;idx<loggedMeasurementCfgIEs->areaCfg_r10.val.trackingAreaCodeLst_r10.noComp.val;idx++)
     {
       FILL_BIT_STR(loggedMeasurementCfgIEs->areaCfg_r10.val.trackingAreaCodeLst_r10.member[idx],16,\
          1,evnt);
     }
   }
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"loggingDuration",
                  &loggingDuration);
   switch(loggingDuration)
   {
     case 0:
         FILL_UINT_TKN(loggedMeasurementCfgIEs->loggingDuration_r10, NhuLoggingDuration_r10min10Enum);
         break;
     case 7:
         FILL_UINT_TKN(loggedMeasurementCfgIEs->loggingDuration_r10, NhuLoggingDuration_r10spare1Enum);
         break;
     default:
         FILL_UINT_TKN(loggedMeasurementCfgIEs->loggingDuration_r10, NhuLoggingDuration_r10min10Enum);
         break;
   }
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"loggingInterval",
                  &loggingInterval);
   switch(loggingInterval)
   {
      case 0:
         FILL_UINT_TKN(loggedMeasurementCfgIEs->loggingInterval_r10, NhuLoggingInterval_r10ms1280Enum);
         break;
      case 7:
         FILL_UINT_TKN(loggedMeasurementCfgIEs->loggingInterval_r10, NhuLoggingInterval_r10ms61440Enum);
         break;
      default:
         FILL_UINT_TKN(loggedMeasurementCfgIEs->loggingInterval_r10, NhuLoggingInterval_r10ms1280Enum);
         break;

   }
   FILL_UINT_TKN(loggedMeasurementCfgIEs->nonCriticalExtn.pres, PRSNT_NODEF);

   RETVALUE(CMXTA_ERR_NONE);
}/* end of nhAcUtlFillNhuLoggedMeasurementCfg_r10*/

/*
*
*       Fun:   nhAcUtlFillNhuRNRecfgn_r10
*
*       Desc:  Fills RN reconfiguration message (DL DCCH)
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuRNRecfgn_r10
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
Ptr            evnt,
NhuDL_DCCH_Msg *dcchMsg
)
#else
PUBLIC S16 nhAcUtlFillNhuRNRecfgn_r10(tcCb, spCb, evnt, dcchMsg)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
Ptr            evnt;
NhuDL_DCCH_Msg *dcchMsg;
#endif
{
   NhuRNRecfgn_r10 *rnRecfg_r10;
   NhuRNRecfgn_r10_IEs *rnRecfgIEs;
   U32 rrc_transId;
   U8  rrcTransIdPres;
   U8  idx=0;
   U32 n1PUCCHANLstMem=1;
   U32 subframeCfgPatternTDD=1;
   U32 n1PucchAnP0=1;
   U32 n1PucchAnP1=1;
   U32 fddn1PucchAnP0=1;
   U32 fddn1PucchAnP1=1;
   U32 pdschStart=1;

   TRC2(nhAcUtlFillNhuRNRecfgn_r10);
  
   FILL_UINT_TKN(dcchMsg->pres, PRSNT_NODEF);
   FILL_UINT_TKN(dcchMsg->message.choice, DL_DCCH_MSGTYP_C1);
   FILL_UINT_TKN(dcchMsg->message.val.c1.choice, C1_RNRECFGN_R10__1);
   rnRecfg_r10 = &(dcchMsg->message.val.c1.val.rnRecfgn_r10);
   FILL_UINT_TKN(rnRecfg_r10->pres, PRSNT_NODEF);

   rrcTransIdPres = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 0;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(rnRecfg_r10->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      rnRecfg_r10->rrc_TrnsxnId.pres = NOTPRSNT;
   }
   FILL_UINT_TKN(rnRecfg_r10->criticalExtns.choice, CRITICALEXTNS_C1);
   FILL_UINT_TKN(rnRecfg_r10->criticalExtns.val.c1.choice, C1_RNRECFGN_R10__15);/*Venu*/

   rnRecfgIEs = &(rnRecfg_r10->criticalExtns.val.c1.val.rnRecfgn_r10);
   FILL_UINT_TKN(rnRecfgIEs->pres, PRSNT_NODEF);
   FILL_UINT_TKN(rnRecfgIEs->rn_SysInfo_r10.pres, PRSNT_NODEF);
   FILL_OCT_STR(rnRecfgIEs->rn_SysInfo_r10.systemInfoBlockTyp1_r10, 1, 1, evnt);
   FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.pres, PRSNT_NODEF);
   FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.subframeConfigPattern_r10.choice,0);
   if(rnRecfgIEs->rn_SubfrmConfig_r10.subframeConfigPattern_r10.choice.val == 0)
   {
     FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.subframeConfigPattern_r10.val.\
           subframeConfigPatternFDD_r10, 8, 1, evnt);
   }
   else
   {
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"subframeCfgPatternTDD",
                  &subframeCfgPatternTDD);
     FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.subframeConfigPattern_r10.val.\
           subframeConfigPatternTDD_r10, subframeCfgPatternTDD);
   }
   FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.resourceAllocnTyp_r10,\
         NhuRN_SubfrmConfig_r10rpdcch_Config_r10resourceAllocnTyp_r10type0Enum);
   FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.choice, 0);
   if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.resourceBlockAssignment_r10.\
         choice.val == 0)
   {
     FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type01_r10.choice, 0);
     if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
                    resourceBlockAssignment_r10.val.type01_r10.choice.val == 0)
     {
       FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type01_r10.val.nrb6_r10, 6, 1, evnt);
     }
     else if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
                    resourceBlockAssignment_r10.val.type01_r10.choice.val == 1)
     {
       FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type01_r10.val.nrb15_r10, 8, 1, evnt);
     }
     else if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
                    resourceBlockAssignment_r10.val.type01_r10.choice.val == 2)
     {
       FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type01_r10.val.nrb25_r10, 13, 1, evnt);
     }
     else if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
                    resourceBlockAssignment_r10.val.type01_r10.choice.val == 3)
     {
       FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type01_r10.val.nrb50_r10, 17, 1, evnt);
     }
     else if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
                    resourceBlockAssignment_r10.val.type01_r10.choice.val == 4)
     {
       FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type01_r10.val.nrb75_r10, 19, 1, evnt);
     }
     else
     {
       FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type01_r10.val.nrb100_r10, 25, 1, evnt);
     }
   }
   else
   {
     FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type2_r10.choice, 0);
     if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
                    resourceBlockAssignment_r10.val.type2_r10.choice.val == 0)
     {
       FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type2_r10.val.nrb6_r10, 5, 1, evnt);
     }
     else if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
                    resourceBlockAssignment_r10.val.type2_r10.choice.val == 1)
     {
       FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type2_r10.val.nrb15_r10, 7, 1, evnt);
     }
     else if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
                    resourceBlockAssignment_r10.val.type2_r10.choice.val == 2)
     {
       FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type2_r10.val.nrb25_r10, 9, 1, evnt);
     }
     else if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
                    resourceBlockAssignment_r10.val.type2_r10.choice.val == 3)
     {
       FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type2_r10.val.nrb50_r10, 11, 1, evnt);
     }
     else if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
                    resourceBlockAssignment_r10.val.type2_r10.choice.val == 4)
     {
       FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type2_r10.val.nrb75_r10, 12, 1, evnt);
     }
     else
     {
       FILL_BIT_STR(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         resourceBlockAssignment_r10.val.type2_r10.val.nrb100_r10, 13, 1, evnt);
     }
   }
   FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
         demodulationRS_r10.choice, 0);
   if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
                  demodulationRS_r10.choice.val == 0)
   {
     FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.demodulationRS_r10.\
           val.interleaving_r10,
           NhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10interleaving_r10crsEnum);
   }
   else
   {
     FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.demodulationRS_r10.\
           val.noInterleaving_r10,
           NhuRN_SubfrmConfig_r10rpdcch_Config_r10demodulationRS_r10noInterleaving_r10dmrsEnum);
   }
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"pdschStart",
                  &pdschStart);
   FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pdsch_Start_r10,\
         pdschStart);
   FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
         choice, 0);
   if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
                  choice.val == 0)
   {
     FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
         val.tdd.choice, 0);
     if(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
                    val.tdd.choice.val == 0)
     {
       FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
           val.tdd.val.channelSelectionMultiplexingBundling.pres, PRSNT_NODEF);
       FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
           val.tdd.val.channelSelectionMultiplexingBundling.n1PUCCH_AN_Lst_r10.noComp, 1);
       CMXTA_GET_MEM(evnt,(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
           val.tdd.val.channelSelectionMultiplexingBundling.n1PUCCH_AN_Lst_r10.noComp.val * 
           sizeof(NhuRN_SubfrmConfig_r10rpdcch_Config_r10pucch_Config_r10tddchannelSelectionMultiplexingBundlingn1PUCCH_AN_Lst_r10Member)),
           &(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.\
           pucch_Config_r10.val.tdd.val.channelSelectionMultiplexingBundling.n1PUCCH_AN_Lst_r10.member));
       cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"n1PUCCHANLstMem",
                  &n1PUCCHANLstMem);
       for(idx=0; idx<rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
           val.tdd.val.channelSelectionMultiplexingBundling.n1PUCCH_AN_Lst_r10.noComp.val;idx++)
       {
         FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
           val.tdd.val.channelSelectionMultiplexingBundling.n1PUCCH_AN_Lst_r10.member[idx],\
           n1PUCCHANLstMem);
       }
     }
     else
     {
       FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
           val.tdd.val.fallbackForFormat3.pres, PRSNT_NODEF);
       cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"n1PucchAnP0",
                  &n1PucchAnP0);
       FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
           val.tdd.val.fallbackForFormat3.n1PUCCH_AN_P0_r10, n1PucchAnP0);
       cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"n1PucchAnP1",
                  &n1PucchAnP1);
       FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
           val.tdd.val.fallbackForFormat3.n1PUCCH_AN_P1_r10, n1PucchAnP1);
     }
   }
   else
   {
     FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
         val.fdd.pres, PRSNT_NODEF);
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"fddn1PucchAnP0",
                  &fddn1PucchAnP0);
     FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
         val.fdd.n1PUCCH_AN_P0_r10, fddn1PucchAnP0);
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"fddn1PucchAnP1",
                  &fddn1PucchAnP1);
     FILL_UINT_TKN(rnRecfgIEs->rn_SubfrmConfig_r10.rpdcch_Config_r10.pucch_Config_r10.\
         val.fdd.n1PUCCH_AN_P1_r10, fddn1PucchAnP1);
   }
   FILL_OCT_STR(rnRecfgIEs->lateNonCriticalExtn, 1, 1, evnt);
   FILL_UINT_TKN(rnRecfgIEs->nonCriticalExtn.pres, PRSNT_NODEF);

   RETVALUE(CMXTA_ERR_NONE);
}/* end of nhAcUtlFillNhuRNRecfgn_r10*/ 
#endif 
/*
*
*       Fun:   nhAcUtlFillNhuRrcConReCfgn
*
*       Desc:  Fills connection reconfiguration message (DL DCCH)
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuRrcConReCfgn
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhDatReqEvntSdu,
U8 sfn,
U8 subFrmNo
)
#else
PUBLIC S16 nhAcUtlFillNhuRrcConReCfgn(tcCb, spCb, nhDatReqEvntSdu, sfn, subFrmNo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuDatReqSdus *nhDatReqEvntSdu;
U8 sfn;
U8 subFrmNo;
#endif
{
   NhuDL_DCCH_Msg *dcchMsg;
   NhuRRCConRecfgn *rrcConReCfg;
   NhuRRCConRecfgn_r8_IEs *conRecfgIEs;
   U8 pdcpId;
   U32 rrc_transId;
   U8  rrcTransIdPres;
   Bool zoneId = FALSE;
   Bool preRegAllowed = FALSE;
   U8  fillForEncFail = 0;

#ifdef LTERRC_REL9
     NhuReportProximityConfig_r9 *proximityCfgR9;
     U8 numComp =1;
     U8 idx;
     U8 idx1;
     NhuMeasObjectUTRA *moUTRA;
     NhuCSG_AllowedRprtngCells_r9 *csgARC;
     NhuReportConfigToAddModreportConfig *rptCfg;
     NhuReportConfigEUTRA *rptCfgEUTRA;
     Bool purposePres = TRUE;
     U32 purposeVal = 0;
     Bool siReqForHOPres = FALSE;
     U32 siReqForHOVal = 0;
     Bool mobilityCntrlInfoPres = FALSE;
#endif
#ifdef RRC_REL11
     Bool a6_ReportOnLeave_r10 = TRUE;
     S16 a6_Offset_r10 = 1;
#endif
   TRC2(nhAcUtlFillNhuRrcConReCfgn);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpId", &pdcpId);
   nhDatReqEvntSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.pdcpId = pdcpId;

   /* If message is already encoded, no need of filling, copy the encoded *
    * mBuf to event structure and return                                  */
   if(nhDatReqEvntSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.isMsgEncoded)
   {
      if(nhAccCb.encBufInfo.encBufPres == TRUE)
      {
         SCpyMsgMsg(nhAccCb.encBufInfo.encBuf, 0, 0, 
               &nhDatReqEvntSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.m.mBuf);
      }
      nhAccCb.encBufInfo.encBufPres = FALSE;
      nhAccCb.encBufInfo.msgLen = 0;
      CMXTA_FREEMBUF(nhAccCb.encBufInfo.encBuf);
      RETVALUE(CMXTA_ERR_NONE);
   }

   dcchMsg = &(nhDatReqEvntSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.m.dcchMsg);

   FILL_UINT_TKN(dcchMsg->pres, PRSNT_NODEF);
   FILL_UINT_TKN(dcchMsg->message.choice, DL_DCCH_MSGTYP_C1);
   FILL_UINT_TKN(dcchMsg->message.val.c1.choice, C1_RRCCONRECFGN);
   rrcConReCfg = &(dcchMsg->message.val.c1.val.rrcConRecfgn);
   FILL_UINT_TKN(rrcConReCfg->pres, PRSNT_NODEF);

   rrcTransIdPres = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 0;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(rrcConReCfg->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      rrcConReCfg->rrc_TrnsxnId.pres = NOTPRSNT;
   }
   FILL_UINT_TKN(rrcConReCfg->criticalExtns.choice, CRITICALEXTNS_C1);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"fillForEncFail",
                  &fillForEncFail);
   if (fillForEncFail)
   {
      NHAC_FILL_U8_U32_TKN(rrcConReCfg->criticalExtns.val.c1.choice, NOTPRSNT, NOTPRSNT);
   }
   else
   {
      FILL_UINT_TKN(rrcConReCfg->criticalExtns.val.c1.choice, C1_RRCCONRECFGN_R8);
   }

   conRecfgIEs = &(rrcConReCfg->criticalExtns.val.c1.val.rrcConRecfgn_r8);
   FILL_UINT_TKN(conRecfgIEs->pres, PRSNT_NODEF);

   /*-Fill NAS Dedicated Information -*/
   FILL_UINT_TKN(conRecfgIEs->dedicatedInfoNASLst.noComp, 1);
   CMXTA_GET_MEM(nhDatReqEvntSdu, (conRecfgIEs->dedicatedInfoNASLst.noComp.val)*(sizeof(NhuDedicatedInfoNAS)),
                  &(conRecfgIEs->dedicatedInfoNASLst.member));
   FILL_OCT_STR(conRecfgIEs->dedicatedInfoNASLst.member[0], 4, 1, nhDatReqEvntSdu);

   /*-Fill Radio Resource Configuration-*/
   nhAcUtlFillNhuRadioResCfgDedi(tcCb, spCb, &(conRecfgIEs->radioResourceConfigDedicated),
                                 (Ptr)nhDatReqEvntSdu);


   /*-Fill UE Related Configuration-*/
   /*nhAcUtlFillNhuUe_RelatedInfo(tcCb, spCb, &(conRecfgIEs->ue_RelatedInfo), 
                             (NhuDatReqSdus*)nhDatReqEvntSdu);*/

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "zoneIdPres",
                  &zoneId);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "preRegAllowed",
                  &preRegAllowed);
   if(zoneId || preRegAllowed)
   {
      FILL_UINT_TKN(conRecfgIEs->measConfig.pres, PRSNT_NODEF);
      FILL_UINT_TKN(conRecfgIEs->measConfig.preRegistrationInfoHRPD.pres, PRSNT_NODEF);
      if(preRegAllowed)
      {
         FILL_UINT_TKN(conRecfgIEs->measConfig.preRegistrationInfoHRPD.\
                     preRegistrationAllowed,TRUE);
      }
      if(zoneId)
      {
         FILL_UINT_TKN(conRecfgIEs->measConfig.preRegistrationInfoHRPD.\
                     preRegistrationZoneId,1);
      }
   }

#ifdef LTERRC_REL9
   /* Filling the CSG related info in measurement config : Lterrc_rel9 */
   /* 1. Filling csg_allowedRprtngCells_v930 */
   /* 2. Filling si_RqstForHo_R9 */
   /* 3. Filling proximityCfgR9 */

     FILL_UINT_TKN(conRecfgIEs->measConfig.pres, PRSNT_NODEF);

     /*Step1: Fill measObjectToAddModLst */
     FILL_UINT_TKN(conRecfgIEs->measConfig.measObjectToAddModLst.noComp,numComp);
     CMXTA_GET_MEM(nhDatReqEvntSdu, (numComp * sizeof(NhuMeasObjectToAddMod)),
                            &(conRecfgIEs->measConfig.measObjectToAddModLst.member));
     for(idx=0;idx<numComp;idx++)
     {
       /*Step2: Fill present field */ 
       FILL_UINT_TKN(conRecfgIEs->measConfig.measObjectToAddModLst.member[idx].pres,PRSNT_NODEF);
      
       /*Step3: Fill measObjectId field */
       /*TODO:MP: corrected the filling of measObjectId */
       NHAC_FILL_U8_U32_TKN(conRecfgIEs->measConfig.measObjectToAddModLst.member[idx].\
             measObjectId, TRUE, PRSNT_NODEF);
      
       /*Step4: Fill measObject field*/
       /*Step4.1: Fill choice field*/
       FILL_UINT_TKN(conRecfgIEs->measConfig.measObjectToAddModLst.member[idx].measObject.choice,
                     MEASOBJECT_MEASOBJECTUTRA);
       moUTRA = &(conRecfgIEs->measConfig.measObjectToAddModLst.member[idx].measObject.val.measObjectUTRA); 
       
       /*Step4.2: Fill measObjectUTRA field*/
       /*Step4.2.1: Fill pres field*/
       FILL_UINT_TKN(moUTRA->pres,PRSNT_NODEF);

       /*Step4.2.2: Fill carrierFreq field as 1: Non Optional*/
       FILL_UINT_TKN(moUTRA->carrierFreq,1);

       /*Step4.2.3: Fill offsetFreq as 0 . This is defaiult value*/
       FILL_UINT_TKN(moUTRA->offsetFreq,NOTPRSNT);

       /*Step4.2.4: Fill cellsToRemoveLst field*/
       /*Step4.2.4.1: Fill numComp field as zero*/
       /*TODO:MP: Macro is corrected since noComp is tknU16 and presence of 
        * noComp is set to FALSE*/
       NHAC_FILL_U8_U32_TKN(moUTRA->cellsToRemoveLst.noComp, FALSE, 0);

       
       /*Step4.2.5: Fill cellsToAddModLst field*/
       /*Step4.2.5.1: Fill choice field*/
       /*TODO:MP: Filling of choice is corrected*/
       NHAC_FILL_U8_U32_TKN(moUTRA->cellsToAddModLst.choice, FALSE, 0);
 
       /*Step4.2.5.2: Fill cellsToAddModLstUTRA_FDD field*/
       /*Step4.2.5.2.1: Fill cellsToAddModLstUTRA_FDD.noComp field wil zero*/
       /*TODO:MP: Filling of noComp is corrected*/
       NHAC_FILL_U8_U32_TKN(moUTRA->cellsToAddModLst.val.cellsToAddModLstUTRA_FDD.noComp, FALSE, 0);
       
       /*Step4.2.6: Fill cellForWhichToReportCGI field*/
       /*Step4.2.6.1: Fill cellForWhichToReportCGI.choice field to zero*/
       /*TODO:MP: Filling of choice is corrected*/
       NHAC_FILL_U8_U32_TKN(moUTRA->cellForWhichToReportCGI.choice, TRUE, 0);

       /*Step4.2.6.1: Fill cellForWhichToReportCGI.val.utra_FDD field */
       /*TODO:MP: Filling of utraFFD is corrected*/
       NHAC_FILL_U8_U32_TKN(moUTRA->cellForWhichToReportCGI.val.utra_FDD, TRUE, PRSNT_NODEF);
      
#ifndef RRC_REL11
       /*Step4.2.6: Fill extaddgrp_r9 field*/
       /*Step4.2.6.1: Fill extaddgrp_r9.pres field*/
       FILL_UINT_TKN(moUTRA->extaddgrp_r9.pres,PRSNT_NODEF);
       
       /*Step4.2.6.2: Fill extaddgrp_r9.csg_allowedRprtngCells_v930 field*/
       csgARC = &(moUTRA->extaddgrp_r9.csg_allowedRprtngCells_v930);
#else
       FILL_UINT_TKN(moUTRA->extaddgrp_1.pres,PRSNT_NODEF);
       
       /*Step4.2.6.2: Fill extaddgrp_1.csg_allowedRprtngCells_v930 field*/
       csgARC = &(moUTRA->extaddgrp_1.csg_allowedRprtngCells_v930);
#endif
       /*Step4.2.6.2.1: Fill extaddgrp_r9.csg_allowedRprtngCells_v930.pres field*/
       /*TODO:MP: Filling is corrected*/
       NHAC_FILL_U8_U32_TKN(csgARC->pres, TRUE, PRSNT_NODEF);
                
       /*Step4.2.6.2.2: Fill extaddgrp_r9.csg_allowedRprtngCells_v930.physCellIdRangeUTRA_FDDLst_r9 field*/
       /*Step4.2.6.2.2.1: Fill noComp field to 1*/
       /*TODO:MP: Filling is corrected*/
       NHAC_FILL_U8_U32_TKN(csgARC->physCellIdRangeUTRA_FDDLst_r9.noComp, TRUE, numComp);
       
       CMXTA_GET_MEM(nhDatReqEvntSdu, (numComp * sizeof(NhuPhysCellIdRangeUTRA_FDD_r9)),
                            &csgARC->physCellIdRangeUTRA_FDDLst_r9.member);
       for(idx1=0;idx1<numComp;idx1++)
       {
          /*Step4.2.6.2.2.2.1: Fill pres field to 1*/
          /*TODO:MP: Filling is corrected*/
            NHAC_FILL_U8_U32_TKN(csgARC->physCellIdRangeUTRA_FDDLst_r9.\
            member[idx1].pres, TRUE, PRSNT_NODEF);

          /*Step4.2.6.2.2.2.1: Fill start_r9 field to 1*/
            /*TODO:MP: Filling is corrected*/
            NHAC_FILL_U8_U32_TKN(csgARC->physCellIdRangeUTRA_FDDLst_r9.\
                  member[idx1].start_r9, TRUE, PRSNT_NODEF);

          /*Step4.2.6.2.2.2.1: Fill range_r9 field to 1*/
            /*TODO:MP: range is set to 3 since accroding to spec it is 2-512*/
            NHAC_FILL_U8_U32_TKN(csgARC->physCellIdRangeUTRA_FDDLst_r9.\
                  member[idx1].range_r9, TRUE, 3);
       } /* for idx1 */
     } /* for idx */
     

#endif

#ifdef LTERRC_REL9
     /*TODO:MP: Corrected the macro. earlier it was wrong*/
     NHAC_FILL_U8_U32_TKN(conRecfgIEs->measConfig.pres, TRUE, PRSNT_NODEF);

     /*Step 1: Fill reportConfigToAddModLst */ 
     /*Step 1.1: Fill noComp */ 
     FILL_UINT_TKN(conRecfgIEs->measConfig.reportConfigToAddModLst.noComp,numComp);
     CMXTA_GET_MEM(nhDatReqEvntSdu, (numComp * sizeof(NhuReportConfigToAddMod)),
                            &conRecfgIEs->measConfig.reportConfigToAddModLst.member);
     for(idx=0;idx<numComp;idx++)
     {
        /*Step 2: Fill pres*/ 
        FILL_UINT_TKN(conRecfgIEs->measConfig.reportConfigToAddModLst.member[idx].pres,PRSNT_NODEF);
        
        /*Step 3: Fill reportConfigId with 1*/ 
        FILL_UINT_TKN(conRecfgIEs->measConfig.reportConfigToAddModLst.member[idx].reportConfigId,1);

        /*Step 3: Fill reportConfig with 1*/ 
         rptCfg = &(conRecfgIEs->measConfig.reportConfigToAddModLst.member[idx].reportConfig);

        /*Step 3.1: Fill choice with 1*/
        /* Check how to get the choce from XTA.iPresently set it to 0.*/
        FILL_UINT_TKN(rptCfg->choice,0); 

        /*Step 3.2: Fill reportConfigEUTRA */
        rptCfgEUTRA = &(rptCfg->val.reportConfigEUTRA);

        /*Step 3.2.1: Fill pres field */
        FILL_UINT_TKN(rptCfgEUTRA->pres,PRSNT_NODEF);
        
        /*Step 3.2.2: Fill triggerTyp field : Non Optional*/
        /*Step 3.2.2.1: Fill triggerTyp.choice field */
        FILL_UINT_TKN(rptCfgEUTRA->triggerTyp.choice,1);
        
        /*Step 3.2.2.1: Fill triggerTyp.val.periodical.pres field */
        FILL_UINT_TKN(rptCfgEUTRA->triggerTyp.val.event.pres,PRSNT_NODEF);
#ifdef RRC_REL11
        FILL_UINT_TKN(rptCfgEUTRA->triggerTyp.val.event.eventId.choice, 5);
        if(rptCfgEUTRA->triggerTyp.val.event.eventId.choice.val == 5)
        {
          FILL_UINT_TKN(rptCfgEUTRA->triggerTyp.val.event.eventId.val.eventA6_r10.pres, PRSNT_NODEF);
          cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_S16, "a6_Offset_r10",
              &a6_Offset_r10);
          FILL_UINT_TKN(rptCfgEUTRA->triggerTyp.val.event.eventId.val.eventA6_r10.a6_Offset_r10,\
                a6_Offset_r10);
          cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "a6_ReportOnLeave_r10",
              &a6_ReportOnLeave_r10);
          FILL_UINT_TKN(rptCfgEUTRA->triggerTyp.val.event.eventId.val.eventA6_r10.a6_ReportOnLeave_r10,\
              a6_ReportOnLeave_r10);
        }
#endif
        /*TODO:MP: filling periodical purpose presence*/ 
        FILL_UINT_TKN(rptCfgEUTRA->triggerTyp.val.periodical.pres,PRSNT_NODEF);
        /*Step 3.2.2.2: Fill triggerTyp.val.periodical.purpose field */
        NHAC_FILL_U8_U32_TKN(rptCfgEUTRA->triggerTyp.val.periodical.purpose,\
              TRUE, 0);
        /*TODO:MP: Read purpose from test case*/
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "purposePres",
              &purposePres);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "purposeVal",
              &purposeVal);
        /*Step 3.2.2.2: Fill triggerTyp.val.periodical.purpose field */
        NHAC_FILL_U8_U32_TKN(rptCfgEUTRA->triggerTyp.val.periodical.purpose,\
              purposePres, purposeVal);

        /*Step 3.2.3: Fill triggerQuantity field */
        FILL_UINT_TKN(rptCfgEUTRA->triggerQuantity,0);
        
        /*Step 3.2.4: Fill reportQuantity field */
        FILL_UINT_TKN(rptCfgEUTRA->reportQuantity,0);
        
        /*Step 3.2.5: Fill maxReportCells field */
        /*TODO:MP: According to spec the value of maxReportCells should be
          from 1 to maxCellReport*/
        FILL_UINT_TKN(rptCfgEUTRA->maxReportCells,1);
        
        /*Step 3.2.6: Fill reportInterval field */
        FILL_UINT_TKN(rptCfgEUTRA->reportInterval,0);
        
        /*Step 3.2.7: Fill reportAmount field */
        FILL_UINT_TKN(rptCfgEUTRA->reportAmount,0);
#ifndef RRC_REL11 
        /*Step 3.2.8: Fill extaddgrp_r9 field */
        /*Step 3.2.8.1: Fill extaddgrp_r9.pres field */
        FILL_UINT_TKN(rptCfgEUTRA->extaddgrp_r9.pres,PRSNT_NODEF);

        /*TODO:MP: Step 3.2.8.2: Fill extaddgrp_r9.si_RqstForHO_r9 field */
        NHAC_FILL_U8_U32_TKN(rptCfgEUTRA->extaddgrp_r9.si_RqstForHO_r9,\
              FALSE,0); /*Setting only this field to 1*/
        /*TODO:MP: Read sireqforHO from test case*/
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "siReqForHOPres",
              &siReqForHOPres);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "siReqForHOVal",
              &siReqForHOVal);
        /*Step 3.2.8.2: Fill extaddgrp_r9.si_RqstForHO_r9 field */
        NHAC_FILL_U8_U32_TKN(rptCfgEUTRA->extaddgrp_r9.si_RqstForHO_r9,\
              siReqForHOPres, siReqForHOVal); /*Setting only this field to 1*/
        
        /*Step 3.2.8.3: Fill extaddgrp_r9.ue_RxTxTimeDiffPeriodical_r9 field */
        FILL_UINT_TKN(rptCfgEUTRA->extaddgrp_r9.ue_RxTxTimeDiffPeriodical_r9,0);
#else
        /*Step 3.2.8: Fill extaddgrp_1 field */
        /*Step 3.2.8.1: Fill extaddgrp_1.pres field */
        FILL_UINT_TKN(rptCfgEUTRA->extaddgrp_1.pres,PRSNT_NODEF);

        /*TODO:MP: Step 3.2.8.2: Fill extaddgrp_1.si_RqstForHO_r9 field */
        NHAC_FILL_U8_U32_TKN(rptCfgEUTRA->extaddgrp_1.si_RqstForHO_r9,\
              FALSE,0); /*Setting only this field to 1*/
        /*TODO:MP: Read sireqforHO from test case*/
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "siReqForHOPres",
              &siReqForHOPres);
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "siReqForHOVal",
              &siReqForHOVal);
        /*Step 3.2.8.2: Fill extaddgrp_1.si_RqstForHO_r9 field */
        NHAC_FILL_U8_U32_TKN(rptCfgEUTRA->extaddgrp_1.si_RqstForHO_r9,\
              siReqForHOPres, siReqForHOVal); /*Setting only this field to 1*/
        
        /*Step 3.2.8.3: Fill extaddgrp_1.ue_RxTxTimeDiffPeriodical_r9 field */
        FILL_UINT_TKN(rptCfgEUTRA->extaddgrp_1.ue_RxTxTimeDiffPeriodical_r9,0);
        FILL_UINT_TKN(rptCfgEUTRA->extaddgrp_2.pres,PRSNT_NODEF);
        FILL_UINT_TKN(rptCfgEUTRA->extaddgrp_2.includeLocInfo_r10,\
              NhuReportConfigEUTRAextaddgrp_2includeLocInfo_r10trueEnum);
        FILL_UINT_TKN(rptCfgEUTRA->extaddgrp_2.reportAddNeighMeas_r10,\
              NhuReportConfigEUTRAextaddgrp_2reportAddNeighMeas_r10setupEnum);
#endif
        /*Step 3.2.1: Fill pres field */

        /*Read mobilityControlInfoPres from test case and if it is present then 
         *fill the IE NhuMobilityCntrlInfo. this is added to test whether
         *SRB2 and one DRB are established or not before sending sending RRC 
         *connection reconfiguration which includes mobility control info
         */
        cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "mobilityCntrlInfoPres",
              &mobilityCntrlInfoPres);

         if (mobilityCntrlInfoPres == TRUE)
         {
            /* fill the IE NhuMobilityCntrlInfo*/
             nhAcUtlFillNhuMobilityCntrlInfo(tcCb, spCb, &(conRecfgIEs->mobilityCntrlInfo),
                                              nhDatReqEvntSdu);
         }
     }
#endif  

   FILL_UINT_TKN(conRecfgIEs->nonCriticalExtn.pres, PRSNT_NODEF);
   
#ifdef LTERRC_REL9
     FILL_UINT_TKN(conRecfgIEs->nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
     FILL_UINT_TKN(conRecfgIEs->nonCriticalExtn.nonCriticalExtn.otherConfig_r9.pres, PRSNT_NODEF);
     proximityCfgR9 = &(conRecfgIEs->nonCriticalExtn.nonCriticalExtn.otherConfig_r9.reportProximityConfig_r9);
     FILL_UINT_TKN(proximityCfgR9->pres,PRSNT_NODEF);
     NHAC_FILL_U8_U32_TKN(proximityCfgR9->proximityIndEUTRA_r9,PRSNT_NODEF,0); /*Filling 0*/
     NHAC_FILL_U8_U32_TKN(proximityCfgR9->proximityIndUTRA_r9,PRSNT_NODEF,0); /*Filling 0*/
#endif

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuRrcConReCfgn */

/*
*
*       Fun:   nhAcUtlFillNhuNhuBCCH_BCHMsg
*
*       Desc:  Fills BCCH_BCH  maseage (DL BCCH BCH)
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuNhuBCCH_BCHMsg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhDatReqEvntSdu,
U8 sfn,
U8 subFrmNo
)
#else
PUBLIC S16 nhAcUtlFillNhuNhuBCCH_BCHMsg(tcCb, spCb, nhDatReqEvntSdu, sfn,
            subFrmNo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuDatReqSdus *nhDatReqEvntSdu;
U8 sfn;
U8 subFrmNo;
#endif
{
   NhuBCCH_BCH_Msg *bcchBchMsg;
   Mem  sMem;

   TRC2(nhAcUtlFillNhuNhuBCCH_BCHMsg);

   sMem.region = 0;
   sMem.pool = 0;

   bcchBchMsg = &(nhDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmn.bcchBchMsg);

   FILL_U8_FRAMENUM(nhDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmnMsgInfo.timingInfo,
                        sfn, subFrmNo);

   FILL_UINT_TKN(bcchBchMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(bcchBchMsg->message.pres,PRSNT_NODEF);
   FILL_UINT_TKN(bcchBchMsg->message.dl_Bandwidth,1);

   FILL_UINT_TKN(bcchBchMsg->message.phich_Config.pres,PRSNT_NODEF);
   FILL_UINT_TKN(bcchBchMsg->message.phich_Config.phich_Duration,1);
   FILL_UINT_TKN(bcchBchMsg->message.phich_Config.phich_Resource,1);

   FILL_BIT_STR(bcchBchMsg->message.systemFrameNumber, 8, sfn, nhDatReqEvntSdu);
   FILL_BIT_STR(bcchBchMsg->message.spare, 10, 1, nhDatReqEvntSdu);

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuNhuBCCH_BCHMsg */


/*
*
*       Fun:   nhAcUtlFillNhuSysInfo
*
*       Desc:  Fills System Info message (DL BCCH DLSCH)
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuSysInfo
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhDatReqEvntSdu,
U8 sfn,
U8 subFrmNo
)
#else
PUBLIC S16 nhAcUtlFillNhuSysInfo(tcCb, spCb, nhDatReqEvntSdu, sfn, subFrmNo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuDatReqSdus *nhDatReqEvntSdu;
U8 sfn;
U8 subFrmNo;
#endif
{
   NhuBCCH_DL_SCH_Msg *bcchSchMsg;
   U8 sibNum;
   NhuSysInfocriticalExtns *critExt;
   U8 choiceARFCN;
   U8 dynCyShiftTyp;
   U8 srsMaxUpPtsAbsent = 0;
   U8 csgPhyRangAbsent = 0;
   Bool zoneId = FALSE;
   Bool preRegAllowed = FALSE;
   Mem  sMem;
   U8 idx;
   U8 idx1;
   U8 idx2;
   NhuSysInfoBlockTyp2 *sib2;
   NhuSysInfoBlockTyp3 *sib3;
   NhuSysInfoBlockTyp4 *sib4;
   NhuSysInfoBlockTyp5 *sib5;
   NhuSysInfoBlockTyp6 *sib6;
   NhuSysInfoBlockTyp7 *sib7;
   NhuSysInfoBlockTyp8 *sib8;
   NhuSysInfoBlockTyp9 *sib9;
   NhuSysInfoBlockTyp10 *sib10;
   NhuSysInfoBlockTyp11 *sib11;
   U8 allSibs=FALSE;
   U8 encErr = 0;
   U8 dataCodSchAbsent = 0;
   U8 segmentNum = 0;
#ifdef LTERRC_REL9
   NhuSysInfoBlockTyp12_r9 *sib12;
   NhuSysInfoBlockTyp13_r9 *sib13;
   U8                      idx3;
#endif /*LTERRC_REL9*/

   TRC2(nhAcUtlFillNhuSysInfo);

   sMem.region = 0;
   sMem.pool = 0;

   bcchSchMsg = &(nhDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmn.bcchDlSchMsg);

   FILL_U8_FRAMENUM(nhDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmnMsgInfo.timingInfo,
                        sfn, subFrmNo);
   FILL_UINT_TKN(bcchSchMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(bcchSchMsg->message.choice,BCCH_DL_SCH_MSGTYP_C1);
   FILL_UINT_TKN(bcchSchMsg->message.val.c1.choice, C1_SYSTEMINFO);
   FILL_UINT_TKN(bcchSchMsg->message.val.c1.val.systemInfo.pres, PRSNT_NODEF);
   critExt = &(bcchSchMsg->message.val.c1.val.systemInfo.criticalExtns);
   FILL_UINT_TKN(critExt->choice, CRITICALEXTNS_SYSTEMINFO_R8);
   FILL_UINT_TKN(critExt->val.systemInfo_r8.pres, PRSNT_NODEF);
   /*FILL_UINT_TKN(critExt->val.systemInfo_r8.nonCriticalExtn.pres, PRSNT_NODEF);*/
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "allSibs", &allSibs);
   if(allSibs)
   {
     FILL_UINT_TKN(critExt->val.systemInfo_r8.sib_TypAndInfo.noComp,10);
     sibNum = 2;
   }
   else
   {
     FILL_UINT_TKN(critExt->val.systemInfo_r8.sib_TypAndInfo.noComp,1);
   }
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "sibNum", &sibNum);
   CMXTA_GET_MEM(nhDatReqEvntSdu, (critExt->val.systemInfo_r8.sib_TypAndInfo.\
                  noComp.val)*(sizeof(NhuSysInfo_r8_IEssib_TypAndInfoMember)),
                  &(critExt->val.systemInfo_r8.sib_TypAndInfo.member));

   for(  idx = 0;
         idx < (critExt->val.systemInfo_r8.sib_TypAndInfo.noComp.val);
         idx++
      )
   {


      FILL_UINT_TKN(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].\
                        choice, (sibNum-2));
      switch (sibNum)
      {
         case 2:
      /*-- For sib2 */
           sib2 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].val.sib2);
            FILL_UINT_TKN(sib2->pres, PRSNT_NODEF);

            /*-Fill Access Barring Info -*/
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "encErr",
                  &encErr);
            FILL_UINT_TKN(sib2->ac_BarringInfo.pres, PRSNT_NODEF);
               
            FILL_UINT_TKN(sib2->ac_BarringInfo.
                         ac_BarringForEmergency,0);
            FILL_UINT_TKN(sib2->ac_BarringInfo.
                         ac_BarringForMO_Signalling.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->ac_BarringInfo.ac_BarringForMO_Signalling.\
                         ac_BarringFactor,
                       0);
            FILL_UINT_TKN(sib2->ac_BarringInfo.ac_BarringForMO_Signalling.\
                         ac_BarringTime, 0 );
            FILL_BIT_STR(sib2->ac_BarringInfo.ac_BarringForMO_Signalling.\
                         ac_BarringForSpecialAC, 5,1,nhDatReqEvntSdu);

            FILL_UINT_TKN(sib2->ac_BarringInfo.\
                     ac_BarringForMO_Data.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->ac_BarringInfo.\
                     ac_BarringForMO_Data.ac_BarringFactor, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->ac_BarringInfo.\
                     ac_BarringForMO_Data.ac_BarringTime,
                     0);
            FILL_BIT_STR(sib2->ac_BarringInfo.ac_BarringForMO_Data.ac_BarringForSpecialAC,5,1,nhDatReqEvntSdu);

            /*-Fill Radio Resource Config Common -*/
            FILL_UINT_TKN(sib2->radioResourceConfigCmn.pres, PRSNT_NODEF);
#ifdef LTERRC_REL9
#define SIB2_RACHCFGCMN          sib2->radioResourceConfigCmn.rach_ConfigCmn
#define SIB2_PDSCHCFGCMN         sib2->radioResourceConfigCmn.pdsch_ConfigCmn
#define SIB2_PUSCHCFGCMN         sib2->radioResourceConfigCmn.pusch_ConfigCmn
#define SIB2_PUCCHCFGCMN         sib2->radioResourceConfigCmn.pucch_ConfigCmn
#define SIB2_SOUNDINGRS_ULCFGCMN sib2->radioResourceConfigCmn.soundingRS_UL_ConfigCmn
#define SIB2_UPLINKPWRCTRLCMN    sib2->radioResourceConfigCmn.uplinkPowerCntrlCmn
#ifdef RRC_REL11
#define SIB2_EXTADDGRP_1         sib2->radioResourceConfigCmn.extaddgrp_1
#endif
#else
#define SIB2_RACHCFGCMN          sib2->radioResourceConfigCmn.rach_Config
#define SIB2_PDSCHCFGCMN         sib2->radioResourceConfigCmn.pdsch_Config
#define SIB2_PUSCHCFGCMN         sib2->radioResourceConfigCmn.pusch_Config
#define SIB2_PUCCHCFGCMN         sib2->radioResourceConfigCmn.pucch_Config
#define SIB2_SOUNDINGRS_ULCFGCMN sib2->radioResourceConfigCmn.soundingRS_UL_Config
#define SIB2_UPLINKPWRCTRLCMN    sib2->radioResourceConfigCmn.uplinkPowerCntrl
#endif

            FILL_UINT_TKN(SIB2_RACHCFGCMN.pres, PRSNT_NODEF);
            FILL_UINT_TKN(SIB2_RACHCFGCMN.preambleInfo.pres, PRSNT_NODEF);
            FILL_UINT_TKN(SIB2_RACHCFGCMN.preambleInfo.numberOfRA_Preambles,
                       NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn4Enum);
            FILL_UINT_TKN(SIB2_RACHCFGCMN.powerRampingParams.pres, 1);
            FILL_UINT_TKN(SIB2_RACHCFGCMN.powerRampingParams.powerRampingStep, 1);
            FILL_UINT_TKN(SIB2_RACHCFGCMN.powerRampingParams.preambleInitReceivedTgtPower,1);

            FILL_UINT_TKN(SIB2_RACHCFGCMN.ra_SupervisionInfo.pres, 1);
            FILL_UINT_TKN(SIB2_RACHCFGCMN.ra_SupervisionInfo.preambleTransMax, 1);
            FILL_UINT_TKN(SIB2_RACHCFGCMN.ra_SupervisionInfo.ra_RspWindowSize, 1);
            FILL_UINT_TKN(SIB2_RACHCFGCMN.ra_SupervisionInfo.mac_ContentionResolutionTimer, 1);

            FILL_UINT_TKN(SIB2_RACHCFGCMN.  maxHARQ_Msg3Tx,1);

            FILL_UINT_TKN(sib2->radioResourceConfigCmn.bcch_Config.pres,
                      PRSNT_NODEF);
            FILL_UINT_TKN(sib2->radioResourceConfigCmn.bcch_Config.\
              modificationPeriodCoeff,0);

            FILL_UINT_TKN(sib2->radioResourceConfigCmn.pcch_Config.pres,
                     PRSNT_NODEF);
            FILL_UINT_TKN(sib2->radioResourceConfigCmn.pcch_Config.defaultPagCycle,
                     0);
            FILL_UINT_TKN(sib2->radioResourceConfigCmn.pcch_Config.nB,
                     0);

            FILL_UINT_TKN(sib2->radioResourceConfigCmn.prach_Config.pres,
                     PRSNT_NODEF);
            FILL_UINT_TKN(sib2->radioResourceConfigCmn.prach_Config.\
                     rootSequenceIdx, 100);
            FILL_UINT_TKN(sib2->radioResourceConfigCmn.prach_Config.\
                     prach_ConfigInfo.pres, 1);
            FILL_UINT_TKN(sib2->radioResourceConfigCmn.prach_Config.\
                     prach_ConfigInfo.prach_ConfigIdx, 10);
            FILL_UINT_TKN(sib2->radioResourceConfigCmn.prach_Config.\
                     prach_ConfigInfo.highSpeedFlag, 1);
            FILL_UINT_TKN(sib2->radioResourceConfigCmn.prach_Config.\
                     prach_ConfigInfo.zeroCorrelationZoneConfig, 1);
            FILL_UINT_TKN(sib2->radioResourceConfigCmn.prach_Config.\
                     prach_ConfigInfo.prach_FreqOffset, 1);


            FILL_UINT_TKN(SIB2_PDSCHCFGCMN.pres, PRSNT_NODEF);
            FILL_UINT_TKN(SIB2_PDSCHCFGCMN.referenceSignalPower, 0);
            FILL_UINT_TKN(SIB2_PDSCHCFGCMN.p_b, 0);

            FILL_UINT_TKN(SIB2_PUSCHCFGCMN.pres, PRSNT_NODEF);
            FILL_UINT_TKN(SIB2_PUSCHCFGCMN.pusch_ConfigBasic.pres, PRSNT_NODEF);
            FILL_UINT_TKN(SIB2_PUSCHCFGCMN.pusch_ConfigBasic.n_SB,1);
            FILL_UINT_TKN(SIB2_PUSCHCFGCMN.pusch_ConfigBasic.hoppingMode, 0);
            FILL_UINT_TKN(SIB2_PUSCHCFGCMN.pusch_ConfigBasic.pusch_HoppingOffset, 0);
            FILL_UINT_TKN(SIB2_PUSCHCFGCMN.pusch_ConfigBasic.enable64QAM, 0);

            FILL_UINT_TKN(SIB2_PUSCHCFGCMN.ul_ReferenceSignalsPUSCH.pres, PRSNT_NODEF);
            FILL_UINT_TKN(SIB2_PUSCHCFGCMN.ul_ReferenceSignalsPUSCH.groupHoppingEnabled, 0);
            FILL_UINT_TKN(SIB2_PUSCHCFGCMN.ul_ReferenceSignalsPUSCH.groupAssignmentPUSCH, 1);
            FILL_UINT_TKN(SIB2_PUSCHCFGCMN.ul_ReferenceSignalsPUSCH.sequenceHoppingEnabled, 0);
            FILL_UINT_TKN(SIB2_PUSCHCFGCMN.ul_ReferenceSignalsPUSCH.cyclicShift, 0);

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                           "dynCyShiftTyp", &dynCyShiftTyp);
            switch (dynCyShiftTyp)
            {
               case 0:
                  /*-Not supported currently -*/
                  break;
               default:
                  break;
            }

            FILL_UINT_TKN(SIB2_PUCCHCFGCMN.pres, PRSNT_NODEF);
            FILL_UINT_TKN(SIB2_PUCCHCFGCMN.deltaPUCCH_Shift, 0);
            FILL_UINT_TKN(SIB2_PUCCHCFGCMN.nRB_CQI, 0);
            FILL_UINT_TKN(SIB2_PUCCHCFGCMN.nCS_AN, 1);
            FILL_UINT_TKN(SIB2_PUCCHCFGCMN.n1PUCCH_AN, 0);


            FILL_UINT_TKN(SIB2_SOUNDINGRS_ULCFGCMN.choice, SOUNDINGRS_UL_CONFIGCMN_SETUP);
            FILL_UINT_TKN(SIB2_SOUNDINGRS_ULCFGCMN.val.setup.pres, PRSNT_NODEF);
            FILL_UINT_TKN(SIB2_SOUNDINGRS_ULCFGCMN.val.setup.srs_BandwidthConfig, 0);
            FILL_UINT_TKN(SIB2_SOUNDINGRS_ULCFGCMN.val.setup.srs_SubfrmConfig, 0);
            FILL_UINT_TKN(SIB2_SOUNDINGRS_ULCFGCMN.val.setup.\
                     ackNackSRS_SimultaneousTransmission, 0);

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "srsMaxUpPtsAbsent",
                  &srsMaxUpPtsAbsent);
            if(srsMaxUpPtsAbsent)
            {
               NHAC_FILL_U8_U32_TKN(SIB2_SOUNDINGRS_ULCFGCMN.val.setup.\
                     srs_MaxUpPts, NOTPRSNT, NOTPRSNT);
            }
            else
            {
               FILL_UINT_TKN(SIB2_SOUNDINGRS_ULCFGCMN.val.setup.\
                        srs_MaxUpPts, NhuSoundingRS_UL_ConfigCmnsetupsrs_MaxUpPtstrueEnum);
            }

            FILL_UINT_TKN(SIB2_UPLINKPWRCTRLCMN.pres, PRSNT_NODEF);
            FILL_UINT_TKN(SIB2_UPLINKPWRCTRLCMN.p0_NominalPUSCH, PRSNT_NODEF);
            FILL_UINT_TKN(SIB2_UPLINKPWRCTRLCMN.alpha, NhuUlnkPowerCntrlCmnalphaal0Enum);
            FILL_UINT_TKN(SIB2_UPLINKPWRCTRLCMN.p0_NominalPUCCH, -100);
            FILL_UINT_TKN(SIB2_UPLINKPWRCTRLCMN.deltaFLst_PUCCH.pres, 1);
            FILL_UINT_TKN(SIB2_UPLINKPWRCTRLCMN.\
                     deltaFLst_PUCCH.deltaF_PUCCH_Format1, 1);
            FILL_UINT_TKN(SIB2_UPLINKPWRCTRLCMN.\
                     deltaFLst_PUCCH.deltaF_PUCCH_Format1b, 1);
            FILL_UINT_TKN(SIB2_UPLINKPWRCTRLCMN.\
                     deltaFLst_PUCCH.deltaF_PUCCH_Format2, 1);
            FILL_UINT_TKN(SIB2_UPLINKPWRCTRLCMN.\
                     deltaFLst_PUCCH.deltaF_PUCCH_Format2a, 1);
            FILL_UINT_TKN(SIB2_UPLINKPWRCTRLCMN.\
                     deltaFLst_PUCCH.deltaF_PUCCH_Format2b, 1);
            
            FILL_UINT_TKN(SIB2_UPLINKPWRCTRLCMN.deltaPreambleMsg3, 1);

#ifdef RRC_REL11
            FILL_UINT_TKN(SIB2_EXTADDGRP_1.pres, PRSNT_NODEF);
            FILL_UINT_TKN(SIB2_EXTADDGRP_1.uplinkPowerCntrlCmn_v1020.pres, PRSNT_NODEF);
            FILL_UINT_TKN(SIB2_EXTADDGRP_1.uplinkPowerCntrlCmn_v1020.deltaF_PUCCH_Format3_r10,
                   NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10deltaF_1Enum);
            FILL_UINT_TKN(SIB2_EXTADDGRP_1.uplinkPowerCntrlCmn_v1020.deltaF_PUCCH_Format1bCS_r10, 
                   NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format1bCS_r10deltaF1Enum);

#endif
#undef SIB2_RACHCFGCMN
#undef SIB2_PDSCHCFGCMN
#undef SIB2_PUSCHCFGCMN 
#undef SIB2_PUCCHCFGCMN
#undef SIB2_SOUNDINGRS_ULCFGCMN
#undef SIB2_UPLINKPWRCTRLCMN
#ifdef RRC_REL11
#undef SIB2_EXTADDGRP_1 
#endif
           FILL_UINT_TKN(sib2->radioResourceConfigCmn.ul_CyclicPrefixLength,0);

            /*-Fill ue Timers And Constants -*/
            FILL_UINT_TKN(sib2->ue_TmrsAndConsts.pres, PRSNT_NODEF);
            if(encErr)
            {
              sib2->ue_TmrsAndConsts.pres.pres = NOTPRSNT;
            }
            FILL_UINT_TKN(sib2->ue_TmrsAndConsts.t300,
                        NhuUE_TmrsAndConstst300ms100Enum);
            FILL_UINT_TKN(sib2->ue_TmrsAndConsts.t301,
                        NhuUE_TmrsAndConstst301ms100Enum);
            FILL_UINT_TKN(sib2->ue_TmrsAndConsts.t310,
                        NhuUE_TmrsAndConstst310ms0Enum);
            FILL_UINT_TKN(sib2->ue_TmrsAndConsts.n310,
                         NhuUE_TmrsAndConstsn310n1Enum);
            FILL_UINT_TKN(sib2->ue_TmrsAndConsts.t311,
                        NhuUE_TmrsAndConstst311ms1000Enum);
            FILL_UINT_TKN(sib2->ue_TmrsAndConsts.n311,
                        NhuUE_TmrsAndConstsn311n1Enum);

            /*-Fill Freuency Infomration -*/
            FILL_UINT_TKN(sib2->freqInfo.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->freqInfo.ul_CarrierFreq, 1);
            FILL_UINT_TKN(sib2->freqInfo.ul_Bandwidth, 0);
            FILL_UINT_TKN(sib2->freqInfo.additionalSpectrumEmission, 1);

            /*-Fill MBSFN-Subframe Configuration -*/
            FILL_UINT_TKN(sib2->mbsfn_SubfrmConfigLst.noComp, 1);
            CMXTA_GET_MEM(nhDatReqEvntSdu, (sib2->mbsfn_SubfrmConfigLst.noComp.val)
                           *(sizeof(NhuMBSFN_SubfrmConfig)),
                           &(sib2->mbsfn_SubfrmConfigLst.member));
            for (idx1 = 0; idx1 < sib2->mbsfn_SubfrmConfigLst.noComp.val; idx1++)
            {
               FILL_UINT_TKN(sib2->mbsfn_SubfrmConfigLst.member[idx1].pres,
                              PRSNT_NODEF);
               FILL_UINT_TKN(sib2->mbsfn_SubfrmConfigLst.member[idx1].
                              radioframeAllocnPeriod,
                        0);
               FILL_UINT_TKN(sib2->mbsfn_SubfrmConfigLst.member[idx1].\
                        radioframeAllocnOffset, 1);
               FILL_UINT_TKN(sib2->mbsfn_SubfrmConfigLst.member[idx1].\
                        subframeAllocn.choice, 0);
               FILL_BIT_STR(sib2->mbsfn_SubfrmConfigLst.member[idx1].\
                        subframeAllocn.val.oneFrame,6, 0,nhDatReqEvntSdu);
            }
            FILL_UINT_TKN(sib2->timeAlignmentTimerCmn,1);

#ifdef LTERRC_REL9
            sib2->lateNonCriticalExtn.pres = NOTPRSNT;
 
#ifndef RRC_REL11
            FILL_UINT_TKN(sib2->extaddgrp_r9.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->extaddgrp_r9.ssac_BarringForMMTEL_Voice_r9.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->extaddgrp_r9.ssac_BarringForMMTEL_Voice_r9.ac_BarringFactor, 0);
            FILL_UINT_TKN(sib2->extaddgrp_r9.ssac_BarringForMMTEL_Voice_r9.ac_BarringTime, 0 );
            FILL_BIT_STR(sib2->extaddgrp_r9.ssac_BarringForMMTEL_Voice_r9.ac_BarringForSpecialAC, 5, 1, nhDatReqEvntSdu);

            FILL_UINT_TKN(sib2->extaddgrp_r9.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->extaddgrp_r9.ssac_BarringForMMTEL_Video_r9.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->extaddgrp_r9.ssac_BarringForMMTEL_Video_r9.ac_BarringFactor, 0);
            FILL_UINT_TKN(sib2->extaddgrp_r9.ssac_BarringForMMTEL_Video_r9.ac_BarringTime, 0 );
            FILL_BIT_STR(sib2->extaddgrp_r9.ssac_BarringForMMTEL_Video_r9.ac_BarringForSpecialAC, 5, 1, nhDatReqEvntSdu);
#else
            FILL_UINT_TKN(sib2->extaddgrp_1.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->extaddgrp_1.ssac_BarringForMMTEL_Voice_r9.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->extaddgrp_1.ssac_BarringForMMTEL_Voice_r9.ac_BarringFactor, 0);
            FILL_UINT_TKN(sib2->extaddgrp_1.ssac_BarringForMMTEL_Voice_r9.ac_BarringTime, 0 );
            FILL_BIT_STR(sib2->extaddgrp_1.ssac_BarringForMMTEL_Voice_r9.ac_BarringForSpecialAC, 5, 1, nhDatReqEvntSdu);

            FILL_UINT_TKN(sib2->extaddgrp_1.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->extaddgrp_1.ssac_BarringForMMTEL_Video_r9.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->extaddgrp_1.ssac_BarringForMMTEL_Video_r9.ac_BarringFactor,\
                  NhuAC_BarringConfigac_BarringFactorp00Enum);
            FILL_UINT_TKN(sib2->extaddgrp_1.ssac_BarringForMMTEL_Video_r9.ac_BarringTime,\
                  NhuAC_BarringConfigac_BarringTimes4Enum);
            FILL_BIT_STR(sib2->extaddgrp_1.ssac_BarringForMMTEL_Video_r9.ac_BarringForSpecialAC, 5, 1, nhDatReqEvntSdu);
            FILL_UINT_TKN(sib2->extaddgrp_2.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->extaddgrp_2.ac_BarringForCSFB_r10.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib2->extaddgrp_2.ac_BarringForCSFB_r10.ac_BarringFactor,\
                  NhuAC_BarringConfigac_BarringFactorp00Enum);
            FILL_UINT_TKN(sib2->extaddgrp_2.ac_BarringForCSFB_r10.ac_BarringTime,\
                  NhuAC_BarringConfigac_BarringTimes4Enum);
            FILL_BIT_STR(sib2->extaddgrp_2.ac_BarringForCSFB_r10.ac_BarringForSpecialAC, 5, 1, nhDatReqEvntSdu);

#endif
#endif

            break;

         case 3:
      /*-- For sib3 */
            sib3 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].
                     val.sib3);
            FILL_UINT_TKN(sib3->pres, PRSNT_NODEF);

            /*-Fill Cell Reselection Information Common -*/
            FILL_UINT_TKN(sib3->cellReselectionInfoCmn.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib3->cellReselectionServingFreqInfo.pres,
                        PRSNT_NODEF);
            FILL_UINT_TKN(sib3->cellReselectionInfoCmn.q_Hyst,
                     NhuSysInfoBlockTyp3cellReselectionInfoCmnq_HystdB0Enum);
            FILL_UINT_TKN(sib3->cellReselectionInfoCmn.\
                     speedStateReselectionPars.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib3->cellReselectionInfoCmn.\
                     speedStateReselectionPars.mobilityStateParams.pres,
                     PRSNT_NODEF);
            FILL_UINT_TKN(sib3->cellReselectionInfoCmn.\
                     speedStateReselectionPars.mobilityStateParams.t_Evaluation,
                     0);
            FILL_UINT_TKN(sib3->cellReselectionInfoCmn.\
                     speedStateReselectionPars.mobilityStateParams.t_HystNormal,
                     NhuMobilityStateParamst_HystNormals30Enum);
            FILL_UINT_TKN(sib3->cellReselectionInfoCmn.\
                     speedStateReselectionPars.mobilityStateParams.\
                     n_CellChangeMedium, 1);
            FILL_UINT_TKN(sib3->cellReselectionInfoCmn.\
                     speedStateReselectionPars.mobilityStateParams.\
                     n_CellChangeHigh, 1);
            FILL_UINT_TKN(sib3->cellReselectionInfoCmn.\
                     speedStateReselectionPars.q_HystSF.pres,PRSNT_NODEF);
            FILL_UINT_TKN(sib3->cellReselectionInfoCmn.\
                     speedStateReselectionPars.q_HystSF.sf_Medium,1);
            FILL_UINT_TKN(sib3->cellReselectionInfoCmn.\
                     speedStateReselectionPars.q_HystSF.sf_High,1);


            /*-Fill Cell Reselection Serving Frequency Information -*/
            FILL_UINT_TKN(sib3->cellReselectionServingFreqInfo.pres,
                  PRSNT_NODEF);
            FILL_UINT_TKN(sib3->cellReselectionServingFreqInfo.s_NonIntraSearch,
                  1);
            FILL_UINT_TKN(sib3->cellReselectionServingFreqInfo.threshServingLow,
                  1);
            FILL_UINT_TKN(sib3->cellReselectionServingFreqInfo.\
                  cellReselectionPriority, 1);

            /*-Fill Intra-Frequency Cell Reselection Information -*/
            FILL_UINT_TKN(sib3->intraFreqCellReselectionInfo.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib3->intraFreqCellReselectionInfo.q_RxLevMin, -70);
            FILL_UINT_TKN(sib3->intraFreqCellReselectionInfo.p_Max, 1);
            FILL_UINT_TKN(sib3->intraFreqCellReselectionInfo.s_IntraSearch, 1);
            FILL_UINT_TKN(sib3->intraFreqCellReselectionInfo.allowedMeasBandwidth, 0);
            FILL_UINT_TKN(sib3->intraFreqCellReselectionInfo.presenceAntennaPort1, 0);
            FILL_BIT_STR(sib3->intraFreqCellReselectionInfo.neighCellConfig,2, 1,nhDatReqEvntSdu);
            FILL_UINT_TKN(sib3->intraFreqCellReselectionInfo.t_ReselectionEUTRA,1);
            FILL_UINT_TKN(sib3->intraFreqCellReselectionInfo.t_ReselectionEUTRA_SF.pres,1);
            FILL_UINT_TKN(sib3->intraFreqCellReselectionInfo.t_ReselectionEUTRA_SF.sf_Medium,1);
            FILL_UINT_TKN(sib3->intraFreqCellReselectionInfo.t_ReselectionEUTRA_SF.sf_High,1);

#ifdef LTERRC_REL9
            /*R9 upgrade: Filling r9 IEs*/
#ifndef RRC_REL11
            FILL_UINT_TKN(sib3->extaddgrp_r9.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib3->extaddgrp_r9.s_IntraSearch_v920.pres, PRSNT_NODEF);
            NHAC_FILL_U8_U32_TKN(sib3->extaddgrp_r9.s_IntraSearch_v920.\
                  s_IntraSearchP_r9, PRSNT_NODEF, PRSNT_NODEF);
            NHAC_FILL_U8_U32_TKN(sib3->extaddgrp_r9.s_IntraSearch_v920.\
                  s_IntraSearchQ_r9, PRSNT_NODEF, PRSNT_NODEF);
            FILL_UINT_TKN(sib3->extaddgrp_r9.s_NonIntraSearch_v920.pres, PRSNT_NODEF);
            NHAC_FILL_U8_U32_TKN(sib3->extaddgrp_r9.s_NonIntraSearch_v920.\
                  s_NonIntraSearchP_r9, PRSNT_NODEF, PRSNT_NODEF);
            NHAC_FILL_U8_U32_TKN(sib3->extaddgrp_r9.s_NonIntraSearch_v920.\
                  s_NonIntraSearchQ_r9, PRSNT_NODEF, PRSNT_NODEF);
            FILL_UINT_TKN(sib3->extaddgrp_r9.q_QualMin_r9, PRSNT_NODEF);
            NHAC_FILL_U8_U32_TKN(sib3->extaddgrp_r9.threshServingLowQ_r9,\
                  PRSNT_NODEF, PRSNT_NODEF);
#else
            FILL_UINT_TKN(sib3->extaddgrp_1.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib3->extaddgrp_1.s_IntraSearch_v920.pres, PRSNT_NODEF);
            NHAC_FILL_U8_U32_TKN(sib3->extaddgrp_1.s_IntraSearch_v920.\
                  s_IntraSearchP_r9, PRSNT_NODEF, PRSNT_NODEF);
            NHAC_FILL_U8_U32_TKN(sib3->extaddgrp_1.s_IntraSearch_v920.\
                  s_IntraSearchQ_r9, PRSNT_NODEF, PRSNT_NODEF);
            FILL_UINT_TKN(sib3->extaddgrp_1.s_NonIntraSearch_v920.pres, PRSNT_NODEF);
            NHAC_FILL_U8_U32_TKN(sib3->extaddgrp_1.s_NonIntraSearch_v920.\
                  s_NonIntraSearchP_r9, PRSNT_NODEF, PRSNT_NODEF);
            NHAC_FILL_U8_U32_TKN(sib3->extaddgrp_1.s_NonIntraSearch_v920.\
                  s_NonIntraSearchQ_r9, PRSNT_NODEF, PRSNT_NODEF);
            FILL_UINT_TKN(sib3->extaddgrp_1.q_QualMin_r9, PRSNT_NODEF);
            NHAC_FILL_U8_U32_TKN(sib3->extaddgrp_1.threshServingLowQ_r9,\
                  PRSNT_NODEF, PRSNT_NODEF);

#endif
#endif /*LTERRC_REL9*/
            break;

         case 4:
      /*-- For sib4 */
            sib4 =&(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].\
                        val.sib4);
            FILL_UINT_TKN(sib4->pres, PRSNT_NODEF);

            /*-Fill Intra-Frequency Neighbouring Cell List-*/
            FILL_UINT_TKN(sib4->intraFreqNeighCellLst.noComp, 1);
            CMXTA_GET_MEM(nhDatReqEvntSdu,
                  (sib4->intraFreqNeighCellLst.noComp.val)
                  *(sizeof(NhuIntraFreqNeighCellInfo)),
                  &(sib4->intraFreqNeighCellLst.member));
            for ( idx1 = 0;
                  idx1 < sib4->intraFreqNeighCellLst.noComp.val;
                  idx1++
                )
            {
               FILL_UINT_TKN(sib4->intraFreqNeighCellLst.member[idx1].\
                    pres, PRSNT_NODEF);
               FILL_UINT_TKN(sib4->intraFreqNeighCellLst.member[idx1].\
                    physCellId, 1);
               FILL_UINT_TKN(sib4->intraFreqNeighCellLst.member[idx1].\
                    q_OffsetCell,
                    0);
            }

            /*-Fill Intra-Frequency Black Listed Cell List-*/
            FILL_UINT_TKN(sib4->intraFreqBlackCellLst.noComp, 1);
            CMXTA_GET_MEM(nhDatReqEvntSdu,
                     (sib4->intraFreqBlackCellLst.noComp.val)
                     *(sizeof(NhuPhysCellIdRange)),
                     &(sib4->intraFreqBlackCellLst.member));
            for (idx1 = 0;
                 idx1 < sib4->intraFreqBlackCellLst.noComp.val; idx1++)
            {
               FILL_UINT_TKN(sib4->intraFreqBlackCellLst.member[idx1].\
                     pres, PRSNT_NODEF);
               FILL_UINT_TKN(sib4->intraFreqBlackCellLst.member[idx1].\
                     start, 1);
               FILL_UINT_TKN(sib4->intraFreqBlackCellLst.member[idx1].\
                     range, 1);
            }

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "csgPhyRangAbsent",
                  &csgPhyRangAbsent);
            if(csgPhyRangAbsent)
            {
               NHAC_FILL_U8_U32_TKN(sib4->csg_PhysCellIdRange.pres, NOTPRSNT, NOTPRSNT);
            }
            else
            {
               FILL_UINT_TKN(sib4->csg_PhysCellIdRange.pres, NOTPRSNT);
               FILL_UINT_TKN(sib4->csg_PhysCellIdRange.start, 1);
               FILL_UINT_TKN(sib4->csg_PhysCellIdRange.range,
                           NhuPhysCellIdRangerangen4Enum);
            }
#ifdef LTERRC_REL9
/*R9 upgrade: filling r9 IEs*/
            FILL_OCT_STR(sib4->lateNonCriticalExtn, 4, 1, nhDatReqEvntSdu);
#endif /*LTERRC_REL9*/
            break;

         case 5:
      /*-- For sib5 */
            sib5 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].
                              val.sib5);
            FILL_UINT_TKN(sib5->pres, PRSNT_NODEF);

            /*-Fill Inter-Frequency Carrier Frequency List -*/
            FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.noComp, 1);
            CMXTA_GET_MEM(nhDatReqEvntSdu, (sib5->interFreqCarrierFreqLst.\
                     noComp.val)
                     *(sizeof(NhuInterFreqCarrierFreqInfo)),
                     &(sib5->interFreqCarrierFreqLst.member));
            for (idx1 = 0;
                 idx1 < sib5->interFreqCarrierFreqLst.noComp.val; idx1++)
            {
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].pres,
                     PRSNT_NODEF);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].dl_CarrierFreq,
                     1);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].q_RxLevMin,
                     -70);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].p_Max,
                     1);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].t_ReselectionEUTRA,
                     1);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].t_ReselectionEUTRA_SF.pres,
                     1);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].t_ReselectionEUTRA_SF.sf_Medium,
                     1);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].t_ReselectionEUTRA_SF.sf_High,
                     1);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     threshX_High, 1);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     threshX_Low, 1);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     allowedMeasBandwidth, 0);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     presenceAntennaPort1, 0);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     cellReselectionPriority, 0);
               FILL_BIT_STR(sib5->interFreqCarrierFreqLst.member[idx1].\
                     neighCellConfig,2, 1,nhDatReqEvntSdu);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     q_OffsetFreq,
                     0);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     interFreqNeighCellLst.noComp, 1);
               CMXTA_GET_MEM(nhDatReqEvntSdu, (sib5->interFreqCarrierFreqLst.\
                     member[idx1].interFreqNeighCellLst.noComp.val)
                     *(sizeof(NhuInterFreqNeighCellInfo)),
                     &(sib5->interFreqCarrierFreqLst.member[idx1].\
                     interFreqNeighCellLst.member));
               for (idx2 = 0;
                    idx2 < sib5->interFreqCarrierFreqLst.member[idx1].\
                           interFreqNeighCellLst.noComp.val;
                    idx2++)
               {
                  FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                        interFreqNeighCellLst.member[idx2].pres,
                        PRSNT_NODEF);
                  FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].
                        interFreqNeighCellLst.member[idx2].
                        physCellId, 1);
                  FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].
                        interFreqNeighCellLst.member[idx2].q_OffsetCell,
                    0);
               }

               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     interFreqBlackCellLst.noComp, 1);
#ifdef LTERRC_REL9
               CMXTA_GET_MEM(nhDatReqEvntSdu, (sib5->interFreqCarrierFreqLst.
                     member[idx1].interFreqBlackCellLst.noComp.val)
                     *(sizeof(NhuPhysCellIdRange)),
                     &(sib5->interFreqCarrierFreqLst.member[idx1].\
                     interFreqBlackCellLst.member));

               for (idx2 = 0;
                    idx2 < sib5->interFreqCarrierFreqLst.member[idx1].\
                    interFreqBlackCellLst.noComp.val; idx2++)
               {
                  FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                    interFreqBlackCellLst.member[idx2].pres, 1);
                  FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                    interFreqBlackCellLst.member[idx2].start, 1);
                  FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                    interFreqBlackCellLst.member[idx2].range, 1);
               }
#else
               CMXTA_GET_MEM(nhDatReqEvntSdu, (sib5->interFreqCarrierFreqLst.
                     member[idx1].interFreqBlackCellLst.noComp.val)
                     *(sizeof(NhuInterFreqBlackCellInfo)),
                     &(sib5->interFreqCarrierFreqLst.member[idx1].\
                     interFreqBlackCellLst.member));

               for (idx2 = 0;
                    idx2 < sib5->interFreqCarrierFreqLst.member[idx1].\
                    interFreqBlackCellLst.noComp.val; idx2++)
               {
                  FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                    interFreqBlackCellLst.member[idx2].pres, PRSNT_NODEF);
                  FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                    interFreqBlackCellLst.member[idx2].physCellIdRange.pres, 1);
                  FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                    interFreqBlackCellLst.member[idx2].physCellIdRange.start, 1);
                  FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                    interFreqBlackCellLst.member[idx2].physCellIdRange.range, 1);
               }
#endif

#ifdef LTERRC_REL9
               /*R9 upgrade: filling the R9 IEs*/
#ifndef RRC_REL11
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     extaddgrp_r9.pres, PRSNT_NODEF);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     extaddgrp_r9.q_QualMin_r9, PRSNT_NODEF);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     extaddgrp_r9.threshX_Q_r9.pres, PRSNT_NODEF);
               NHAC_FILL_U8_U32_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     extaddgrp_r9.threshX_Q_r9.threshX_HighQ_r9, PRSNT_NODEF, PRSNT_NODEF);
               NHAC_FILL_U8_U32_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     extaddgrp_r9.threshX_Q_r9.threshX_LowQ_r9, PRSNT_NODEF, PRSNT_NODEF);
#else
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     extaddgrp_1.pres, PRSNT_NODEF);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     extaddgrp_1.q_QualMin_r9, PRSNT_NODEF);
               FILL_UINT_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     extaddgrp_1.threshX_Q_r9.pres, PRSNT_NODEF);
               NHAC_FILL_U8_U32_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     extaddgrp_1.threshX_Q_r9.threshX_HighQ_r9, PRSNT_NODEF, PRSNT_NODEF);
               NHAC_FILL_U8_U32_TKN(sib5->interFreqCarrierFreqLst.member[idx1].\
                     extaddgrp_1.threshX_Q_r9.threshX_LowQ_r9, PRSNT_NODEF, PRSNT_NODEF);

#endif
               FILL_OCT_STR(sib5->lateNonCriticalExtn, 4, 1, nhDatReqEvntSdu);

#endif /*LTERRC_REL9*/
            }
            break;

         case 6:
      /*-- For sib6 */
            sib6 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].\
                        val.sib6);
            FILL_UINT_TKN(sib6->pres, PRSNT_NODEF);

            /*-Fill UTRA FDD Carrier Frequency List -*/
            /*FILL_UINT_TKN(sib6->carrierFreqLstUTRA_FDD.noComp, 0);*/
            CMXTA_GET_MEM(nhDatReqEvntSdu, (sib6->carrierFreqLstUTRA_FDD.\
                     noComp.val)
                     *(sizeof(NhuCarrierFreqUTRA_FDD)),
                     &(sib6->carrierFreqLstUTRA_FDD.member));
            for (idx1 = 0;
                 idx1 < sib6->carrierFreqLstUTRA_FDD.noComp.val; idx1++)
            {
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].pres,
                     PRSNT_NODEF);
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].\
                     cellReselectionPriority, 1);
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].\
                     threshX_High, 0);
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].\
                     threshX_Low, 0);
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].\
                     q_RxLevMin, 0);
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].\
                     p_MaxUTRA, 0);
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].\
                     q_QualMin, 0);
#ifdef LTERRC_REL9
/*R9 upgrade: filling the R9 IEs*/
#ifndef RRC_REL11
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].\
                     extaddgrp_r9.pres, PRSNT_NODEF);
               NHAC_FILL_U8_U32_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].\
                     extaddgrp_r9.threshX_Q_r9.pres, PRSNT_NODEF, PRSNT_NODEF);
               NHAC_FILL_U8_U32_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].\
                     extaddgrp_r9.threshX_Q_r9.threshX_HighQ_r9,PRSNT_NODEF, PRSNT_NODEF);
#else
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].\
                     extaddgrp_1.pres, PRSNT_NODEF);
               NHAC_FILL_U8_U32_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].\
                     extaddgrp_1.threshX_Q_r9.pres, PRSNT_NODEF, PRSNT_NODEF);
               NHAC_FILL_U8_U32_TKN(sib6->carrierFreqLstUTRA_FDD.member[idx1].\
                     extaddgrp_1.threshX_Q_r9.threshX_HighQ_r9,PRSNT_NODEF, PRSNT_NODEF);
#endif

#endif /*LTERRC_REL9*/
            }

            /*-Fill UTRA TDD Carrier Frequency List -*/
            /*FILL_UINT_TKN(sib6->carrierFreqLstUTRA_TDD.noComp, 1);*/
            CMXTA_GET_MEM(nhDatReqEvntSdu, (sib6->carrierFreqLstUTRA_TDD.\
                     noComp.val)
                     *(sizeof(NhuCarrierFreqUTRA_TDD)),
                     &(sib6->carrierFreqLstUTRA_TDD.member));
            for (idx1 = 0;
                 idx1 < sib6->carrierFreqLstUTRA_TDD.noComp.val; idx1++)
            {
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_TDD.member[idx1].pres,
                     PRSNT_NODEF);
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_TDD.member[idx1].\
                     cellReselectionPriority, 1);
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_TDD.member[idx1].\
                     threshX_High, 0);
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_TDD.member[idx1].\
                     threshX_Low, 0);
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_TDD.member[idx1].\
                     q_RxLevMin, 0);
               FILL_UINT_TKN(sib6->carrierFreqLstUTRA_TDD.member[idx1].\
                     p_MaxUTRA, 0);
            }


            /*- Fill t_Reselection UTRA --*/
            FILL_UINT_TKN(sib6->t_ReselectionUTRA, 1);

            /*-Fill Speed Dependent Scaling Parameters -*/
            FILL_UINT_TKN(sib6->t_ReselectionUTRA_SF.pres, PRSNT_NODEF);
            FILL_UINT_TKN(sib6->t_ReselectionUTRA_SF.sf_Medium,NhuSpeedStateScaleFactorssf_MediumoDot25Enum);
            FILL_UINT_TKN(sib6->t_ReselectionUTRA_SF.sf_High,NhuSpeedStateScaleFactorssf_HighoDot25Enum);
            break;

         case 7:
      /*-- For sib7 */
            sib7 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].val.sib7);
            FILL_UINT_TKN(sib7->pres, 1);

            /*-Fill t_ReselectionGERAN-*/
            FILL_UINT_TKN(sib7->t_ReselectionGERAN, 1);


            /*-Fill GERAN Neigbour Frequency List-*/
            FILL_UINT_TKN(sib7->carrierFreqsInfoLst.noComp, 1);
            CMXTA_GET_MEM(nhDatReqEvntSdu, (sib7->carrierFreqsInfoLst.\
                     noComp.val)
                     *(sizeof(NhuCarrierFreqsInfoGERAN)),
                     &(sib7->carrierFreqsInfoLst.member));
            for (idx1 = 0;
                 idx1 < sib7->carrierFreqsInfoLst.noComp.val; idx1++)
            {
               FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].pres,
                        PRSNT_NODEF);
               FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                        carrierFreqs.pres, PRSNT_NODEF);
               FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                        carrierFreqs.startingARFCN, 1);
               FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                        carrierFreqs.bandIndicator,
                        0);
               FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                        carrierFreqs.followingARFCNs.choice,
                        FOLLOWINGARFCNS_EXPLICITLSTOFARFCNS);
               choiceARFCN= FOLLOWINGARFCNS_EXPLICITLSTOFARFCNS;
               cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                           "ARFCNChoice", &choiceARFCN);
               switch (choiceARFCN)
               {

                  case FOLLOWINGARFCNS_EXPLICITLSTOFARFCNS:
                     FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                           carrierFreqs.followingARFCNs.choice,
                           FOLLOWINGARFCNS_EXPLICITLSTOFARFCNS);
                     FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                              carrierFreqs.followingARFCNs.\
                              val.explicitLstOfARFCNs.noComp, 1);
                     CMXTA_GET_MEM(nhDatReqEvntSdu,
                           (sib7->carrierFreqsInfoLst.member[idx1].\
                            carrierFreqs.followingARFCNs.\
                            val.explicitLstOfARFCNs.noComp.val)
                           *(sizeof(NhuARFCN_ValueGERAN)),
                           &(sib7->carrierFreqsInfoLst.member[idx1].\
                           carrierFreqs.followingARFCNs.\
                           val.explicitLstOfARFCNs.member));
                     for (idx2 = 0;
                          idx2 < sib7->carrierFreqsInfoLst.member[idx1].\
                                 carrierFreqs.\
                                 followingARFCNs.val.explicitLstOfARFCNs.noComp.val;
                           idx2++)
                     {
                        FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                              carrierFreqs.\
                              followingARFCNs.val.explicitLstOfARFCNs.member[idx2],
                              1);
                     }
                     break;
                  case FOLLOWINGARFCNS_EQUALLYSPACEDARFCNS:
                     FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                           carrierFreqs.followingARFCNs.choice,
                           FOLLOWINGARFCNS_EQUALLYSPACEDARFCNS);
                     break;
                  case FOLLOWINGARFCNS_VARIABLEBITMAPOFARFCNS:
                     FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                           carrierFreqs.followingARFCNs.choice,
                           FOLLOWINGARFCNS_VARIABLEBITMAPOFARFCNS);
                     break;
               }

               FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                     commonInfo.pres, PRSNT_NODEF);
               FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                     commonInfo.cellReselectionPriority, 1);
               FILL_BIT_STR(sib7->carrierFreqsInfoLst.member[idx1].\
                     commonInfo.ncc_Permitted, 8, 1, nhDatReqEvntSdu);
               FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                     commonInfo.q_RxLevMin, 1);
               FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                     commonInfo.threshX_High, 1);
               FILL_UINT_TKN(sib7->carrierFreqsInfoLst.member[idx1].\
                     commonInfo.threshX_Low, 1);
            }
            break;

         case 8:
      /*-- For sib8 */
            sib8 =&(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].\
                        val.sib8);
            FILL_UINT_TKN(sib8->pres, PRSNT_NODEF);

            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "zoneIdPres",
                           &zoneId);

            cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "preRegAllowed",
                           &preRegAllowed);
            if(zoneId || preRegAllowed)
            {
               FILL_UINT_TKN(sib8->parametersHRPD.pres, PRSNT_NODEF);
               FILL_UINT_TKN(sib8->parametersHRPD.preRegistrationInfoHRPD.pres, PRSNT_NODEF);
               if(preRegAllowed)
               {
                  FILL_UINT_TKN(sib8->parametersHRPD.preRegistrationInfoHRPD.\
                                 preRegistrationAllowed,TRUE);
               }
               if(zoneId)
               {
                  FILL_UINT_TKN(sib8->parametersHRPD.preRegistrationInfoHRPD.\
                                 preRegistrationZoneId,1);
               }
            }

#ifdef LTERRC_REL9
/*R9 upgrade: filling the R9 IEs*/
#ifndef RRC_REL11
                  FILL_UINT_TKN(sib8->extaddgrp_r9.pres, PRSNT_NODEF);
                  FILL_UINT_TKN(sib8->extaddgrp_r9.csfb_SupportForDualRxUEs_r9,\
                        PRSNT_NODEF);
                  FILL_UINT_TKN(sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                        pres, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                        neighCellLst_v920.noComp, PRSNT_NODEF, 1);
                  CMXTA_GET_MEM(nhDatReqEvntSdu, (sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                        neighCellLst_v920.noComp.val)*(sizeof(NhuNeighCellCDMA2000_v920)),
                        &(sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                        neighCellLst_v920.member));
                  for(idx1 = 0; idx1 < sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                        neighCellLst_v920.noComp.val; idx1++)
                  {
                     FILL_UINT_TKN(sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                           neighCellLst_v920.member[idx1].pres, PRSNT_NODEF);
                     NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                           neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.noComp, PRSNT_NODEF, 1);

                     CMXTA_GET_MEM(nhDatReqEvntSdu, (sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                              neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.noComp.val)*\
                              (sizeof(NhuNeighCellsPerBandclassCDMA2000_v920)),
                           &(sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                              neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member));

                     for(idx2 = 0; idx2 < sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                              neighCellLst_v920.member[idx2].neighCellsPerFreqLst_v920.noComp.val; idx2++)
                        {
                           FILL_UINT_TKN(sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                                 neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].pres,\
                                 PRSNT_NODEF);
                           NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                                 neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                 physCellIdLst_v920.noComp, PRSNT_NODEF, 1);

                           CMXTA_GET_MEM(nhDatReqEvntSdu, (sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                                    neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                    physCellIdLst_v920.noComp.val)*(sizeof(NhuPhysCellIdCDMA2000)),
                                 &(sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                                    neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.\
                                    member[idx2].physCellIdLst_v920.member));
                           for(idx3 = 0; idx3 < sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                                 neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                 physCellIdLst_v920.noComp.val; idx3++)
                           {
                              NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.cellReselectionParamsHRPD_v920.\
                                    neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                    physCellIdLst_v920.member[idx3], PRSNT_NODEF, PRSNT_NODEF);

                           }
                        }
                  }
                  /*-- Filling the IE cellReselectionParams1XRTT_v920*/
                  FILL_UINT_TKN(sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                        pres, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                        neighCellLst_v920.noComp, PRSNT_NODEF, 1);
                  CMXTA_GET_MEM(nhDatReqEvntSdu, (sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                        neighCellLst_v920.noComp.val)*(sizeof(NhuNeighCellCDMA2000_v920)),
                        &(sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                        neighCellLst_v920.member));
                  for(idx1 = 0; idx1 < sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                        neighCellLst_v920.noComp.val; idx1++)
                  {
                     FILL_UINT_TKN(sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                           neighCellLst_v920.member[idx1].pres, PRSNT_NODEF);
                     NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                           neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.noComp, PRSNT_NODEF, 1);

                     CMXTA_GET_MEM(nhDatReqEvntSdu, (sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                              neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.noComp.val)*\
                              (sizeof(NhuNeighCellsPerBandclassCDMA2000_v920)),
                           &(sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                              neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member));

                     for(idx2 = 0; idx2 < sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                              neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.noComp.val; idx2++)
                        {
                           FILL_UINT_TKN(sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                                 neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].pres,\
                                 PRSNT_NODEF);
                           NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                                 neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                 physCellIdLst_v920.noComp, PRSNT_NODEF, 1);

                           CMXTA_GET_MEM(nhDatReqEvntSdu, (sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                                    neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                    physCellIdLst_v920.noComp.val)*(sizeof(NhuPhysCellIdCDMA2000)),
                                 &(sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                                    neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.\
                                    member[idx2].physCellIdLst_v920.member));
                           for(idx3 = 0; idx3 < sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                                 neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                 physCellIdLst_v920.noComp.val; idx3++)
                           {
                              NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.cellReselectionParams1XRTT_v920.\
                                    neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                    physCellIdLst_v920.member[idx3], PRSNT_NODEF, PRSNT_NODEF);

                           }
                        }
                  }

                  /*-- Filling the IE csfb_RegistrationParam1XRTT_v920*/
                  FILL_UINT_TKN(sib8->extaddgrp_r9.csfb_RegistrationParam1XRTT_v920.pres,\
                        PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.csfb_RegistrationParam1XRTT_v920.\
                        powerDownReg_r9, PRSNT_NODEF, PRSNT_NODEF);

                  /*-- Filling the IE cc_BarringConfig1XRTT_r9*/
                  FILL_UINT_TKN(sib8->extaddgrp_r9.ac_BarringConfig1XRTT_r9.pres,\
                        PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.ac_BarringConfig1XRTT_r9.\
                        ac_Barring0to9_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.ac_BarringConfig1XRTT_r9.\
                        ac_Barring10_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.ac_BarringConfig1XRTT_r9.\
                        ac_Barring11_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.ac_BarringConfig1XRTT_r9.\
                        ac_Barring12_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.ac_BarringConfig1XRTT_r9.\
                        ac_Barring13_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.ac_BarringConfig1XRTT_r9.\
                        ac_Barring14_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.ac_BarringConfig1XRTT_r9.\
                        ac_Barring15_r9, PRSNT_NODEF, PRSNT_NODEF);

                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.ac_BarringConfig1XRTT_r9.\
                        ac_BarringMsg_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.ac_BarringConfig1XRTT_r9.\
                        ac_BarringReg_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_r9.ac_BarringConfig1XRTT_r9.\
                        ac_BarringEmg_r9, PRSNT_NODEF, PRSNT_NODEF);
#else                  
                  FILL_UINT_TKN(sib8->extaddgrp_1.pres, PRSNT_NODEF);
                  FILL_UINT_TKN(sib8->extaddgrp_1.csfb_SupportForDualRxUEs_r9,\
                        PRSNT_NODEF);
                  FILL_UINT_TKN(sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                        pres, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                        neighCellLst_v920.noComp, PRSNT_NODEF, 1);
                  CMXTA_GET_MEM(nhDatReqEvntSdu, (sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                        neighCellLst_v920.noComp.val)*(sizeof(NhuNeighCellCDMA2000_v920)),
                        &(sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                        neighCellLst_v920.member));
                  for(idx1 = 0; idx1 < sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                        neighCellLst_v920.noComp.val; idx1++)
                  {
                     FILL_UINT_TKN(sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                           neighCellLst_v920.member[idx1].pres, PRSNT_NODEF);
                     NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                           neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.noComp, PRSNT_NODEF, 1);

                     CMXTA_GET_MEM(nhDatReqEvntSdu, (sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                              neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.noComp.val)*\
                              (sizeof(NhuNeighCellsPerBandclassCDMA2000_v920)),
                           &(sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                              neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member));

                     for(idx2 = 0; idx2 < sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                              neighCellLst_v920.member[idx2].neighCellsPerFreqLst_v920.noComp.val; idx2++)
                        {
                           FILL_UINT_TKN(sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                                 neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].pres,\
                                 PRSNT_NODEF);
                           NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                                 neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                 physCellIdLst_v920.noComp, PRSNT_NODEF, 1);

                           CMXTA_GET_MEM(nhDatReqEvntSdu, (sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                                    neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                    physCellIdLst_v920.noComp.val)*(sizeof(NhuPhysCellIdCDMA2000)),
                                 &(sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                                    neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.\
                                    member[idx2].physCellIdLst_v920.member));
                           for(idx3 = 0; idx3 < sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                                 neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                 physCellIdLst_v920.noComp.val; idx3++)
                           {
                              NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.cellReselectionParamsHRPD_v920.\
                                    neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                    physCellIdLst_v920.member[idx3], PRSNT_NODEF, PRSNT_NODEF);

                           }
                        }
                  }
                  /*-- Filling the IE cellReselectionParams1XRTT_v920*/
                  FILL_UINT_TKN(sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                        pres, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                        neighCellLst_v920.noComp, PRSNT_NODEF, 1);
                  CMXTA_GET_MEM(nhDatReqEvntSdu, (sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                        neighCellLst_v920.noComp.val)*(sizeof(NhuNeighCellCDMA2000_v920)),
                        &(sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                        neighCellLst_v920.member));
                  for(idx1 = 0; idx1 < sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                        neighCellLst_v920.noComp.val; idx1++)
                  {
                     FILL_UINT_TKN(sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                           neighCellLst_v920.member[idx1].pres, PRSNT_NODEF);
                     NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                           neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.noComp, PRSNT_NODEF, 1);

                     CMXTA_GET_MEM(nhDatReqEvntSdu, (sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                              neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.noComp.val)*\
                              (sizeof(NhuNeighCellsPerBandclassCDMA2000_v920)),
                           &(sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                              neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member));

                     for(idx2 = 0; idx2 < sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                              neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.noComp.val; idx2++)
                        {
                           FILL_UINT_TKN(sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                                 neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].pres,\
                                 PRSNT_NODEF);
                           NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                                 neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                 physCellIdLst_v920.noComp, PRSNT_NODEF, 1);

                           CMXTA_GET_MEM(nhDatReqEvntSdu, (sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                                    neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                    physCellIdLst_v920.noComp.val)*(sizeof(NhuPhysCellIdCDMA2000)),
                                 &(sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                                    neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.\
                                    member[idx2].physCellIdLst_v920.member));
                           for(idx3 = 0; idx3 < sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                                 neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                 physCellIdLst_v920.noComp.val; idx3++)
                           {
                              NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.cellReselectionParams1XRTT_v920.\
                                    neighCellLst_v920.member[idx1].neighCellsPerFreqLst_v920.member[idx2].\
                                    physCellIdLst_v920.member[idx3], PRSNT_NODEF, PRSNT_NODEF);

                           }
                        }
                  }

                  /*-- Filling the IE csfb_RegistrationParam1XRTT_v920*/
                  FILL_UINT_TKN(sib8->extaddgrp_1.csfb_RegistrationParam1XRTT_v920.pres,\
                        PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.csfb_RegistrationParam1XRTT_v920.\
                        powerDownReg_r9, PRSNT_NODEF, PRSNT_NODEF);

                  /*-- Filling the IE cc_BarringConfig1XRTT_r9*/
                  FILL_UINT_TKN(sib8->extaddgrp_1.ac_BarringConfig1XRTT_r9.pres,\
                        PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.ac_BarringConfig1XRTT_r9.\
                        ac_Barring0to9_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.ac_BarringConfig1XRTT_r9.\
                        ac_Barring10_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.ac_BarringConfig1XRTT_r9.\
                        ac_Barring11_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.ac_BarringConfig1XRTT_r9.\
                        ac_Barring12_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.ac_BarringConfig1XRTT_r9.\
                        ac_Barring13_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.ac_BarringConfig1XRTT_r9.\
                        ac_Barring14_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.ac_BarringConfig1XRTT_r9.\
                        ac_Barring15_r9, PRSNT_NODEF, PRSNT_NODEF);

                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.ac_BarringConfig1XRTT_r9.\
                        ac_BarringMsg_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.ac_BarringConfig1XRTT_r9.\
                        ac_BarringReg_r9, PRSNT_NODEF, PRSNT_NODEF);
                  NHAC_FILL_U8_U32_TKN(sib8->extaddgrp_1.ac_BarringConfig1XRTT_r9.\
                        ac_BarringEmg_r9, PRSNT_NODEF, PRSNT_NODEF);
                  FILL_UINT_TKN(sib8->extaddgrp_2.pres, PRSNT_NODEF);
                  FILL_UINT_TKN(sib8->extaddgrp_2.csfb_DualRxTxSupport_r10,
                        NhuSysInfoBlockTyp8extaddgrp_2csfb_DualRxTxSupport_r10trueEnum);

#endif
#endif /*LTERRC_REL9*/
            break;

         case 9:
      /*-- For sib9 */
            sib9 =&(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].\
                        val.sib9);
            FILL_UINT_TKN(sib9->pres, PRSNT_NODEF);
            FILL_OCT_STR(sib9->hnb_Name, 48, 1, nhDatReqEvntSdu);
#ifdef LTERRC_REL9
            /*R9 uprade: filling the new IEs added in R9*/
            FILL_OCT_STR(sib9->lateNonCriticalExtn, 4, 1, nhDatReqEvntSdu);
#endif /*LTERRC_REL9*/
            break;

         case 10:
      /*-- For sib10 */
            sib10 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].\
                  val.sib10);
            FILL_UINT_TKN(sib10->pres, PRSNT_NODEF);
            FILL_BIT_STR(sib10->messageId, 16,1,nhDatReqEvntSdu);
            FILL_BIT_STR(sib10->serialNumber, 16,1,  nhDatReqEvntSdu);
            FILL_OCT_STR(sib10->warningTyp, 2,1, nhDatReqEvntSdu);
#ifndef RRC_REL11 /* Venu */
            FILL_OCT_STR(sib10->warningSecInfo,50,1, nhDatReqEvntSdu);
#endif
#ifdef LTERRC_REL9
            /*R9 uprade: filling the new IEs added in R9*/
            FILL_OCT_STR(sib10->lateNonCriticalExtn, 4, 1, nhDatReqEvntSdu);
#endif /*LTERRC_REL9*/
            break;

         case 11:
      /*-- For sib11 */
            sib11 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].\
                  val.sib11);
            FILL_UINT_TKN(sib11->pres, PRSNT_NODEF);
            FILL_BIT_STR(sib11->messageId,16,1, nhDatReqEvntSdu);
            FILL_BIT_STR(sib11->serialNumber,16,1, nhDatReqEvntSdu);
            FILL_UINT_TKN(sib11->warningMsgSegmentTyp, PRSNT_NODEF);
            segmentNum = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "segmentNum",
                  &segmentNum);
            FILL_UINT_TKN(sib11->warningMsgSegmentNumber, segmentNum);
            FILL_OCT_STR(sib11->warningMsgSegment,1,1, nhDatReqEvntSdu);
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "dataCodSchAbsent",
                  &dataCodSchAbsent);
            if(dataCodSchAbsent)
            {
               NHAC_FILL_U8_U32_TKN(sib11->dataCodingScheme, NOTPRSNT, NOTPRSNT);
            }
            else
            {
               FILL_OCT_STR(sib11->dataCodingScheme,1,1, nhDatReqEvntSdu);
            }
#ifdef LTERRC_REL9
            /*R9 uprade: filling the new IEs added in R9*/
            FILL_OCT_STR(sib11->lateNonCriticalExtn, 4, 1, nhDatReqEvntSdu);
#endif /*LTERRC_REL9*/
            break;

#ifdef LTERRC_REL9
            /*R9 upgrade: filling SIB12 */
         case 12:
            /*R9 upgrade: sib12 is added */
            sib12 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].\
                  val.sib12_v920);
                  
            FILL_UINT_TKN(sib12->pres, PRSNT_NODEF);
            FILL_BIT_STR(sib12->messageId_r9,16,1, nhDatReqEvntSdu);
            FILL_BIT_STR(sib12->serialNumber_r9,16,1, nhDatReqEvntSdu);
            
            FILL_UINT_TKN(sib12->warningMsgSegmentTyp_r9,\
                  NhuSysInfoBlockTyp12_r9warningMsgSegmentTyp_r9notLastSegmentEnum);
            
            segmentNum = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "segmentNum",
                  &segmentNum);

            FILL_UINT_TKN(sib12->warningMsgSegmentNumber_r9, segmentNum);
            FILL_OCT_STR(sib12->warningMsgSegment_r9,1,1, nhDatReqEvntSdu);
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "dataCodSchAbsent",
                  &dataCodSchAbsent);
            if(dataCodSchAbsent)
            {
               NHAC_FILL_U8_U32_TKN(sib12->dataCodingScheme_r9, NOTPRSNT, NOTPRSNT);
            }
            else
            {
               FILL_OCT_STR(sib12->dataCodingScheme_r9,1,1, nhDatReqEvntSdu);
            }
            FILL_OCT_STR(sib12->lateNonCriticalExtn,4,1, nhDatReqEvntSdu);
            break;

            /*R9 upgrade: filling SIB13 */
         case 13:
            /*R9 upgrade: sib12 is added */
           sib13 = &(critExt->val.systemInfo_r8.sib_TypAndInfo.member[idx].val.sib13_v920);
           FILL_UINT_TKN(sib13->pres, PRSNT_NODEF);
           
           NHAC_FILL_U8_U32_TKN(sib13->mbsfn_AreaInfoLst_r9.noComp, PRSNT_NODEF, 1);

           CMXTA_GET_MEM(nhDatReqEvntSdu, (sib13->mbsfn_AreaInfoLst_r9.noComp.val) * \
                 (sizeof(NhuMBSFN_AreaInfo_r9)), &(sib13->mbsfn_AreaInfoLst_r9.member));

           for (idx1 = 0; idx1 < sib13->mbsfn_AreaInfoLst_r9.noComp.val; idx1++)
           {
              FILL_UINT_TKN(sib13->mbsfn_AreaInfoLst_r9.member[idx1].pres,\
                    PRSNT_NODEF);
              NHAC_FILL_U8_U32_TKN(sib13->mbsfn_AreaInfoLst_r9.member[idx1].\
                    mbsfn_AreaId_r9, PRSNT_NODEF, 1);
              NHAC_FILL_U8_U32_TKN(sib13->mbsfn_AreaInfoLst_r9.member[idx1].\
                    non_MBSFNregionLength, PRSNT_NODEF, 1);
              NHAC_FILL_U8_U32_TKN(sib13->mbsfn_AreaInfoLst_r9.member[idx1].\
                    notificationIndicator_r9, PRSNT_NODEF, 1);
              FILL_UINT_TKN(sib13->mbsfn_AreaInfoLst_r9.member[idx1].\
                    mcch_Config_r9.pres, PRSNT_NODEF);
              NHAC_FILL_U8_U32_TKN(sib13->mbsfn_AreaInfoLst_r9.member[idx1].\
                    mcch_Config_r9.mcch_RepetitionPeriod_r9, PRSNT_NODEF, 1);
              NHAC_FILL_U8_U32_TKN(sib13->mbsfn_AreaInfoLst_r9.member[idx1].\
                    mcch_Config_r9.mcch_Offset_r9, PRSNT_NODEF, 1);
              NHAC_FILL_U8_U32_TKN(sib13->mbsfn_AreaInfoLst_r9.member[idx1].\
                    mcch_Config_r9.mcch_ModfnPeriod_r9, PRSNT_NODEF, 1);
              /*Filling sf_AllocInfo_r9*/
              FILL_BIT_STR(sib13->mbsfn_AreaInfoLst_r9.member[idx1].\
                    mcch_Config_r9.sf_AllocInfo_r9, 6, 1, nhDatReqEvntSdu);
              NHAC_FILL_U8_U32_TKN(sib13->mbsfn_AreaInfoLst_r9.member[idx1].\
                    mcch_Config_r9.signallingMCS_r9, PRSNT_NODEF, 1);
           }

           /*Filling the IE notificationConfig_r9 */
           FILL_UINT_TKN(sib13->notificationConfig_r9.pres, PRSNT_NODEF);
           NHAC_FILL_U8_U32_TKN(sib13->notificationConfig_r9.notificationRepetitionCoeff_r9,\
                 PRSNT_NODEF, 1);
           NHAC_FILL_U8_U32_TKN(sib13->notificationConfig_r9.notificationOffset_r9,\
                 PRSNT_NODEF, 1);
           NHAC_FILL_U8_U32_TKN(sib13->notificationConfig_r9.notificationSF_Idx_r9,\
                 PRSNT_NODEF, 1);
           FILL_OCT_STR(sib13->lateNonCriticalExtn, 4, 1, nhDatReqEvntSdu);

#endif /*LTERRC_REL9*/

         default:
            break;
      }
      if(allSibs)
      sibNum ++;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuSysInfo */

/*
*
*       Fun:   nhAcUtlFillNhuSysInfoBlockType1
*
*       Desc:  Fills System Info Block Type1 message (DL BCCH DLSCH)
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuSysInfoBlockType1
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatReqSdus *nhDatReqEvntSdu,
U8 sfn,
U8 subFrmNo
)
#else
PUBLIC S16 nhAcUtlFillNhuSysInfoBlockType1(tcCb, spCb, nhDatReqEvntSdu,
            sfn, subFrmNo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuDatReqSdus *nhDatReqEvntSdu;
U8 sfn;
U8 subFrmNo;
#endif
{
   NhuBCCH_DL_SCH_Msg *bcchSchMsg;
   NhuSysInfoBlockTyp1 *typ1;
   Mem  sMem;
   U8 idx;
   U8 idx1;
   U8 fdd_mode = 0;
   U8 isCSGCell = 0;

   TRC2(nhAcUtlFillNhuSysInfo);

   sMem.region = 0;
   sMem.pool = 0;

   bcchSchMsg = &(nhDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmn.bcchDlSchMsg);

   FILL_U8_FRAMENUM(nhDatReqEvntSdu->sdu.ueMsg.msg.cmnMsg.cmnMsgInfo.\
                     timingInfo, sfn, subFrmNo);
   FILL_UINT_TKN(bcchSchMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(bcchSchMsg->message.choice, BCCH_DL_SCH_MSGTYP_C1);
   FILL_UINT_TKN(bcchSchMsg->message.val.c1.choice, C1_SYSTEMINFOBLOCKTYP1);
   typ1 = &(bcchSchMsg->message.val.c1.val.systemInfoBlockTyp1);
   FILL_UINT_TKN(typ1->pres,PRSNT_NODEF);
   FILL_UINT_TKN(typ1->cellAccessRelatedInfo.pres,PRSNT_NODEF);
   FILL_UINT_TKN(typ1->cellAccessRelatedInfo.plmn_IdentityLst.noComp,1);
   CMXTA_GET_MEM(nhDatReqEvntSdu, (typ1->cellAccessRelatedInfo.\
               plmn_IdentityLst.noComp.val)
               *(sizeof(NhuPLMN_IdentityInfo)),
               &(typ1->cellAccessRelatedInfo.plmn_IdentityLst.member));

   for(idx=0;
       idx < (typ1->cellAccessRelatedInfo.plmn_IdentityLst.noComp.val); idx++)
   {
      FILL_UINT_TKN(typ1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
            pres,PRSNT_NODEF);
      FILL_UINT_TKN(typ1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
            plmn_Identity.pres,PRSNT_NODEF);
      FILL_UINT_TKN(typ1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
            plmn_Identity.mnc.noComp,2);
      CMXTA_GET_MEM(nhDatReqEvntSdu,2 * (sizeof(NhuMCC_MNC_Digit)),
            &(typ1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
            plmn_Identity.mnc.member));

      for(idx1 = 0;
          idx1 < (typ1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
               plmn_Identity.mcc.noComp.val); idx1++)
      {
         FILL_UINT_TKN(typ1->cellAccessRelatedInfo.plmn_IdentityLst.\
               member[idx].plmn_Identity.mcc.member[idx1],1);
      }
      for(idx1=0;
          idx1<(typ1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
            plmn_Identity.mnc.noComp.val); idx1++)
      {
         FILL_UINT_TKN(typ1->cellAccessRelatedInfo.plmn_IdentityLst.\
               member[idx].plmn_Identity.mnc.member[idx1],1);
      }
      FILL_UINT_TKN(typ1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
            cellReservedForOperatorUse,1);
   }
   FILL_BIT_STR(typ1->cellAccessRelatedInfo.trackingAreaCode, 16,1,nhDatReqEvntSdu);

   FILL_BIT_STR(typ1->cellAccessRelatedInfo.cellIdentity, 28, 1,
            nhDatReqEvntSdu);
   FILL_UINT_TKN(typ1->cellAccessRelatedInfo.cellBarred,1);
   FILL_UINT_TKN(typ1->cellAccessRelatedInfo.intraFreqReselection,1);
   FILL_UINT_TKN(typ1->cellAccessRelatedInfo.csg_Ind, TRUE);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "isCSGCell",  &(isCSGCell));
   if (isCSGCell == 0)
   {
      NHAC_FILL_U8_U32_TKN(typ1->cellAccessRelatedInfo.csg_Identity, NOTPRSNT, NOTPRSNT);
   }
   else
   {
      FILL_BIT_STR(typ1->cellAccessRelatedInfo.csg_Identity,27, 1, nhDatReqEvntSdu);
   }

   FILL_UINT_TKN(typ1->cellSelectionInfo.pres,PRSNT_NODEF);
   FILL_UINT_TKN(typ1->cellSelectionInfo.q_RxLevMin,-50);
   FILL_UINT_TKN(typ1->cellSelectionInfo.q_RxLevMinOffset,1);

   FILL_UINT_TKN(typ1->freqBandIndicator,1);
   FILL_UINT_TKN(typ1->schedulingInfoLst.noComp,1);
   CMXTA_GET_MEM(nhDatReqEvntSdu,1 * (sizeof(NhuSchedulingInfo)),
                 &(typ1->schedulingInfoLst.member));

   for(idx=0;idx<(typ1->schedulingInfoLst.noComp.val);idx++)
   {
       FILL_UINT_TKN(typ1->schedulingInfoLst.member[idx].pres,PRSNT_NODEF);
       FILL_UINT_TKN(typ1->schedulingInfoLst.member[idx].si_Periodicity,1);
       FILL_UINT_TKN(typ1->schedulingInfoLst.member[idx].sib_MappingInfo.noComp,1);
       CMXTA_GET_MEM(nhDatReqEvntSdu,1 * (sizeof(NhuSIB_Typ)),
                     &(typ1->schedulingInfoLst.member[idx].sib_MappingInfo.member));
       for(idx1=0;
           idx1<(typ1->schedulingInfoLst.member[idx].sib_MappingInfo.noComp.val);
           idx1++)
       {
          FILL_UINT_TKN(typ1->schedulingInfoLst.member[idx].sib_MappingInfo.\
                member[idx],1);
       }
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "fdd_mode",
                &fdd_mode);
   if(fdd_mode)
   {
      FILL_UINT_TKN(typ1->tdd_Config.pres, NOTPRSNT);
   }
   else
   {
      FILL_UINT_TKN(typ1->tdd_Config.pres, PRSNT_NODEF);
      FILL_UINT_TKN(typ1->tdd_Config.subframeAssignment,
                  NhuTDD_ConfigsubframeAssignmentsa0Enum);
      FILL_UINT_TKN(typ1->tdd_Config.specialSubfrmPatterns,
                  NhuTDD_ConfigspecialSubfrmPatternsssp0Enum);
   }


   FILL_UINT_TKN(typ1->si_WindowLength,1);
   FILL_UINT_TKN(typ1->systemInfoValueTag,1);
   FILL_UINT_TKN(typ1->nonCriticalExtn.pres,PRSNT_NODEF);

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuSysInfoBlockType1 */

/*
*
*       Fun:   nhAcUtlFillNhuHoCmd
*
*       Desc:  This function fills Handover Command
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuHoCmd
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
Ptr           evnt,
NhuHovrCmd    *hoCmd
)
#else
PUBLIC S16 nhAcUtlFillNhuHoCmd(tcCb, spCb, evnt, hoCmd)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
Ptr           evnt;
NhuHovrCmd    *hoCmd;
#endif
{
   TRC2(nhAcUtlFillNhuHoCmd);

   FILL_UINT_TKN(hoCmd->pres,PRSNT_NODEF);
   FILL_UINT_TKN(hoCmd->criticalExtns.choice, CRITICALEXTNS_C1);
   FILL_UINT_TKN(hoCmd->criticalExtns.val.c1.choice,C1_HANDOVERCMD_R8);
   FILL_UINT_TKN(hoCmd->criticalExtns.val.c1.val.handoverCmd_r8.pres,PRSNT_NODEF);

   FILL_OCT_STR(hoCmd->criticalExtns.val.c1.val.handoverCmd_r8.handoverCmdMsg, 4, 1, evnt); 

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuHoCmd */

/*
*
*       Fun:   nhAcUtlFillNhuUeRadAccessCapInfo
*
*       Desc:  This function fills UE Radio Access Capability Information
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuUeRadAccessCapInfo
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
Ptr           evnt,
NhuUERadioAccessCapInfo *ueRACapInfo
)
#else
PUBLIC S16 nhAcUtlFillNhuUeRadAccessCapInfo(tcCb, spCb, evnt, ueRACapInfo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
Ptr           evnt;
NhuUERadioAccessCapInfo *ueRACapInfo;
#endif
{
   TRC2(nhAcUtlFillNhuUeRadAccessCapInfo);

   FILL_UINT_TKN(ueRACapInfo->pres,PRSNT_NODEF);
   FILL_UINT_TKN(ueRACapInfo->criticalExtns.choice, CRITICALEXTNS_C1);
   FILL_UINT_TKN(ueRACapInfo->criticalExtns.val.c1.choice,C1_UERADIOACCESSCAPINFO_R8);
   FILL_UINT_TKN(ueRACapInfo->criticalExtns.val.c1.val.ueRadioAccessCapInfo_r8.pres,PRSNT_NODEF);

   FILL_OCT_STR(ueRACapInfo->criticalExtns.val.c1.val.ueRadioAccessCapInfo_r8.\
                ue_RadioAccessCapInfo, 4, 1, evnt); 

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuUeRadAccessCapInfo */

/*
*
*       Fun:   nhAcUtlFillNhuUeCapInfo
*
*       Desc:  This function fills UE Capability Information
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuUeCapInfo
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
Ptr           evnt,
NhuUECapInfo  *ueCapInfo
)
#else
PUBLIC S16 nhAcUtlFillNhuUeCapInfo(tcCb, spCb, evnt, ueCapInfo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
Ptr           evnt;
NhuUECapInfo  *ueCapInfo;
#endif
{
   U32                  rrc_transId;
   U8                   rrcTransIdPres;
   NhuUE_CapRAT_ContLst *ueContLst = NULLP;
  
   TRC2(nhAcUtlFillNhuUeCapInfo);

   FILL_UINT_TKN(ueCapInfo->pres,PRSNT_NODEF);
   rrcTransIdPres = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 0;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(ueCapInfo->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      ueCapInfo->rrc_TrnsxnId.pres = NOTPRSNT;
   }
   FILL_UINT_TKN(ueCapInfo->criticalExtns.choice, CRITICALEXTNS_C1);
   FILL_UINT_TKN(ueCapInfo->criticalExtns.val.c1.choice,C1_UECAPINFO_R8);
   FILL_UINT_TKN(ueCapInfo->criticalExtns.val.c1.val.ueCapInfo_r8.pres,PRSNT_NODEF);

   ueContLst = &ueCapInfo->criticalExtns.val.c1.val.ueCapInfo_r8.ue_CapRAT_ContLst;
   FILL_UINT_TKN(ueContLst->noComp,1);
   
   /* Allocate memory required for num components */
   CMXTA_GET_MEM(evnt, sizeof(NhuUE_CapRAT_Cont)*ueContLst->noComp.val,
                 &(ueContLst->member));

   FILL_UINT_TKN(ueContLst->member[0].pres,PRSNT_NODEF);
   FILL_UINT_TKN(ueContLst->member[0].rat_Typ,NhuRAT_TypeutraEnum);
   FILL_OCT_STR(ueContLst->member[0].ueCapRAT_Cont, 4, 1, evnt); 
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuUeCapInfo */

/*
*
*       Fun:   nhAcUtlFillNhuHoPrepInfoSIB1
*
*       Desc:  Fills System Info Block Type1 message in HO prep Info message.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuHoPrepInfoSIB1
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuSysInfoBlockTyp1 *sib1,
Ptr           evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuHoPrepInfoSIB1(tcCb, spCb, sib1, evnt)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuSysInfoBlockTyp1 *sib1;
Ptr           evnt;
#endif
{
   U8 idx;
   U8 idx1;

   TRC2(nhAcUtlFillNhuSysInfo);

   FILL_UINT_TKN(sib1->pres,PRSNT_NODEF);
   FILL_UINT_TKN(sib1->cellAccessRelatedInfo.pres,PRSNT_NODEF);
   FILL_UINT_TKN(sib1->cellAccessRelatedInfo.plmn_IdentityLst.noComp,1);
   CMXTA_GET_MEM(evnt, (sib1->cellAccessRelatedInfo.\
               plmn_IdentityLst.noComp.val)
               *(sizeof(NhuPLMN_IdentityInfo)),
               &(sib1->cellAccessRelatedInfo.plmn_IdentityLst.member));

   for(idx=0;
       idx < (sib1->cellAccessRelatedInfo.plmn_IdentityLst.noComp.val); idx++)
   {
      FILL_UINT_TKN(sib1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
            pres,PRSNT_NODEF);
      FILL_UINT_TKN(sib1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
            plmn_Identity.pres,PRSNT_NODEF);
      FILL_UINT_TKN(sib1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
            plmn_Identity.mnc.noComp,2);
      CMXTA_GET_MEM(evnt, 2 * (sizeof(NhuMCC_MNC_Digit)),
            &(sib1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
            plmn_Identity.mnc.member));

      for(idx1 = 0;
          idx1 < (sib1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
               plmn_Identity.mcc.noComp.val); idx1++)
      {
         FILL_UINT_TKN(sib1->cellAccessRelatedInfo.plmn_IdentityLst.\
               member[idx].plmn_Identity.mcc.member[idx1],1);
      }
      for(idx1=0;
          idx1<(sib1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
            plmn_Identity.mnc.noComp.val); idx1++)
      {
         FILL_UINT_TKN(sib1->cellAccessRelatedInfo.plmn_IdentityLst.\
               member[idx].plmn_Identity.mnc.member[idx1],1);
      }
      FILL_UINT_TKN(sib1->cellAccessRelatedInfo.plmn_IdentityLst.member[idx].\
            cellReservedForOperatorUse,1);
   }
   FILL_BIT_STR(sib1->cellAccessRelatedInfo.trackingAreaCode, 16,1,evnt);

   FILL_BIT_STR(sib1->cellAccessRelatedInfo.cellIdentity, 28, 1,
            evnt);
   FILL_UINT_TKN(sib1->cellAccessRelatedInfo.cellBarred,1);
   FILL_UINT_TKN(sib1->cellAccessRelatedInfo.intraFreqReselection,1);
   FILL_UINT_TKN(sib1->cellAccessRelatedInfo.csg_Ind,1);

   FILL_UINT_TKN(sib1->cellSelectionInfo.pres,PRSNT_NODEF);
   FILL_UINT_TKN(sib1->cellSelectionInfo.q_RxLevMin,-50);
   FILL_UINT_TKN(sib1->cellSelectionInfo.q_RxLevMinOffset,1);

   FILL_UINT_TKN(sib1->freqBandIndicator,1);
   FILL_UINT_TKN(sib1->schedulingInfoLst.noComp,1);
   CMXTA_GET_MEM(evnt,1 * (sizeof(NhuSchedulingInfo)),
                 &(sib1->schedulingInfoLst.member));

   for(idx=0;idx<(sib1->schedulingInfoLst.noComp.val);idx++)
   {
       FILL_UINT_TKN(sib1->schedulingInfoLst.member[idx].pres,PRSNT_NODEF);
       FILL_UINT_TKN(sib1->schedulingInfoLst.member[idx].si_Periodicity,1);
       FILL_UINT_TKN(sib1->schedulingInfoLst.member[idx].sib_MappingInfo.noComp,1);
       CMXTA_GET_MEM(evnt,1 * (sizeof(NhuSIB_Typ)),
                     &(sib1->schedulingInfoLst.member[idx].sib_MappingInfo.member));
       for(idx1=0;
           idx1<(sib1->schedulingInfoLst.member[idx].sib_MappingInfo.noComp.val);
           idx1++)
       {
          FILL_UINT_TKN(sib1->schedulingInfoLst.member[idx].sib_MappingInfo.\
                member[idx],1);
       }
   }

   FILL_UINT_TKN(sib1->si_WindowLength,1);
   FILL_UINT_TKN(sib1->systemInfoValueTag,1);
   FILL_UINT_TKN(sib1->nonCriticalExtn.pres,PRSNT_NODEF);
#ifdef LTE_RRC
/*R9 upgrade: NH_NW_82 */
   FILL_OCT_STR(sib1->nonCriticalExtn.lateNonCriticalExtn, 4, 1, (NhuEncReqSdus *)Ptr);
   FILL_UINT_TKN(sib1->nonCriticalExtn.nonCriticalExtn.pres,NOTPRSNT);
   NHAC_FILL_U8_U32_TKN(sib1->nonCriticalExtn.nonCriticalExtn.\
         ims_EmergencySupport_r9, PRSNT_NODEF, PRSNT_NODEF);
   FILL_UINT_TKN(sib1->nonCriticalExtn.nonCriticalExtn.cellSelectionInfo_v920.pres,PRSNT_NODEF);
   FILL_UINT_TKN(sib1->nonCriticalExtn.nonCriticalExtn.cellSelectionInfo_v920.\
         q_QualMin_r9, PRSNT_NODEF);
   NHAC_FILL_U8_U32_TKN(sib1->nonCriticalExtn.nonCriticalExtn.cellSelectionInfo_v920.\
         q_QualMinOffset_r9, PRSNT_NODEF, PRSNT_NODEF);
   FILL_UINT_TKN(sib1->nonCriticalExtn.nonCriticalExtn.cellSelectionInfo_v920.\
         nonCriticalExtn, PRSNT_NODEF);
#endif/*LTE_RRC*/

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuSysInfoBlockType1 */
/*
*
*       Fun:   nhAcUtlFillNhuHoPrepInfo
*
*       Desc:  This function fills HO Preparation Information message
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuHoPrepInfo
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
Ptr            evnt,
NhuHovrPrepInfo *hoPrepInfo
)
#else
PUBLIC S16 nhAcUtlFillNhuHoPrepInfo(tcCb, spCb, evnt, hoPrepInfo)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb; 
Ptr            evnt;
NhuHovrPrepInfo *hoPrepInfo;
#endif
{
   NhuHovrPrepInfo_r8_IEs *hoPrepInfoIe = NULLP;
   NhuUE_CapRAT_ContLst   *ueContLst = NULLP;
   Bool                   preRegAllowed;
   Bool                   zoneId;
   NhuMeasConfig          *measCfg = NULLP;
   NhuMasterInfoBlock     *mib = NULLP;
   NhuSysInfoBlockTyp2    *sib2 = NULLP;

#ifdef LTERRC_REL9
   NhuReportProximityConfig_r9 *prxCfg;
#endif

#ifdef RRC_REL11
   U8                     idx=0;
   U8                     idx1=0;
   U32                    sCellIdx=1;
   U32                    physCellId=1;
   U32                    dlCarrierFreq=1;
   U32                    pb=1;
   U32                    prachCfgIdx=1;
   U32                    cyclicShift=0;
   U32                    pSRSOffset=0;
   U32                    transmissionCombAp=0;
   U32                    freqDomainPosition=1;
#endif
  
   TRC2(nhAcUtlFillNhuHoPrepInfo);

   FILL_UINT_TKN(hoPrepInfo->pres,PRSNT_NODEF);
   FILL_UINT_TKN(hoPrepInfo->criticalExtns.choice, CRITICALEXTNS_C1);
   FILL_UINT_TKN(hoPrepInfo->criticalExtns.val.c1.choice,C1_HANDOVERPREPINFO_R8);
   FILL_UINT_TKN(hoPrepInfo->criticalExtns.val.c1.val.handoverPrepInfo_r8.pres,PRSNT_NODEF);

   hoPrepInfoIe = &hoPrepInfo->criticalExtns.val.c1.val.handoverPrepInfo_r8;
   FILL_UINT_TKN(hoPrepInfoIe->pres,PRSNT_NODEF);
   ueContLst = &hoPrepInfoIe->ue_RadioAccessCapInfo;
   FILL_UINT_TKN(ueContLst->noComp,1);
   
   /* Allocate memory required for num components */
   CMXTA_GET_MEM(evnt, sizeof(NhuUE_CapRAT_Cont)*ueContLst->noComp.val,
                 &(ueContLst->member));

   FILL_UINT_TKN(ueContLst->member[0].pres,PRSNT_NODEF);
   FILL_UINT_TKN(ueContLst->member[0].rat_Typ,NhuRAT_TypeutraEnum);
   FILL_OCT_STR(ueContLst->member[0].ueCapRAT_Cont, 4, 1, evnt); 

   zoneId = FALSE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "zoneIdPres",
                  &zoneId);
   preRegAllowed = FALSE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "preRegAllowed",
                  &preRegAllowed);
   FILL_UINT_TKN(hoPrepInfoIe->as_Config.pres, PRSNT_NODEF);
   measCfg = &hoPrepInfoIe->as_Config.sourceMeasConfig;
   FILL_UINT_TKN(measCfg->pres, PRSNT_NODEF);
   if(zoneId || preRegAllowed)
   {
      FILL_UINT_TKN(measCfg->preRegistrationInfoHRPD.pres, PRSNT_NODEF);
      if(preRegAllowed)
      {
         FILL_UINT_TKN(measCfg->preRegistrationInfoHRPD.preRegistrationAllowed,TRUE);
      }
      if(zoneId)
      {
         FILL_UINT_TKN(measCfg->preRegistrationInfoHRPD.preRegistrationZoneId,1);
      }
   }
   /* Filling Radio Resource Configuration */
   nhAcUtlFillNhuRadioResCfgDedi(tcCb, spCb,
                  &(hoPrepInfoIe->as_Config.sourceRadioResourceConfig),
                  evnt);
   /* Filling Security Configuration */
   nhAcUtlFillNhuSecurityCfg(tcCb, spCb,
                   &(hoPrepInfoIe->as_Config.sourceSecAlgorithmConfig));
   /* Filling RNTI */
   FILL_BIT_STR(hoPrepInfoIe->as_Config.sourceUE_Identity, 16, 1,
                evnt);
   /* Filling Master Information Block */
   mib = &hoPrepInfoIe->as_Config.sourceMasterInfoBlock;
   FILL_UINT_TKN(mib->pres, TRUE);
   FILL_UINT_TKN(mib->dl_Bandwidth, NhuMasterInfoBlockdl_Bandwidthn6Enum);
   FILL_UINT_TKN(mib->phich_Config.pres, PRSNT_NODEF);
   FILL_UINT_TKN(mib->phich_Config.phich_Duration, 
                 NhuPHICH_Configphich_DurationnormalEnum);
   FILL_UINT_TKN(mib->phich_Config.phich_Resource, 
                 NhuPHICH_Configphich_ResourceoneSixthEnum);
   FILL_BIT_STR(mib->systemFrameNumber, 8, 1, evnt);
   FILL_BIT_STR(mib->spare, 10, 1, evnt);
       
   /* Filling SIB1 */
   nhAcUtlFillNhuHoPrepInfoSIB1(tcCb, spCb, 
               &hoPrepInfoIe->as_Config.sourceSysInfoBlockTyp1, evnt);
   /* Filling SIB2 info -
          - radio Resource Cfg common info, 
          - ue Timers And Constants,
          - Frequency Info
          - Timer alignment info   */
   sib2 = &hoPrepInfoIe->as_Config.sourceSysInfoBlockTyp2;
   FILL_UINT_TKN(sib2->pres,PRSNT_NODEF);
   nhAcUtlFillNhuRadioResCfgCmnSibIE(tcCb, spCb, &sib2->radioResourceConfigCmn,
                                     evnt);

   FILL_UINT_TKN(sib2->ue_TmrsAndConsts.pres, PRSNT_NODEF);
   FILL_UINT_TKN(sib2->ue_TmrsAndConsts.t300,
                  NhuUE_TmrsAndConstst300ms100Enum);
   FILL_UINT_TKN(sib2->ue_TmrsAndConsts.t301,
                  NhuUE_TmrsAndConstst301ms100Enum);
   FILL_UINT_TKN(sib2->ue_TmrsAndConsts.t310,
                  NhuUE_TmrsAndConstst310ms0Enum);
   FILL_UINT_TKN(sib2->ue_TmrsAndConsts.n310,
                   NhuUE_TmrsAndConstsn310n1Enum);
   FILL_UINT_TKN(sib2->ue_TmrsAndConsts.t311,
                  NhuUE_TmrsAndConstst311ms1000Enum);
   FILL_UINT_TKN(sib2->ue_TmrsAndConsts.n311,
                  NhuUE_TmrsAndConstsn311n1Enum);

   FILL_UINT_TKN(sib2->freqInfo.pres, PRSNT_NODEF);
   FILL_UINT_TKN(sib2->freqInfo.ul_CarrierFreq, 1);
   FILL_UINT_TKN(sib2->freqInfo.ul_Bandwidth, 0);
   FILL_UINT_TKN(sib2->freqInfo.additionalSpectrumEmission, 1);
   
   FILL_UINT_TKN(sib2->timeAlignmentTimerCmn,1);

   /* Filling antenna info */
   FILL_UINT_TKN(hoPrepInfoIe->as_Config.antennaInfoCmn.pres, PRSNT_NODEF);
   FILL_UINT_TKN(hoPrepInfoIe->as_Config.antennaInfoCmn.antennaPortsCount, 
                 NhuAntennaInfoCmnantennaPortsCountan1Enum);

   /* Filling ARFCN EUTRA info */
   FILL_UINT_TKN(hoPrepInfoIe->as_Config.sourceDl_CarrierFreq, 1);

#ifdef LTERRC_REL9
#ifndef RRC_REL11
   /* Filling the CSG related information :Lterrc_rel9 */
   /* Step 1: Fill extaddgrp_r9 */
   /* Step 1.1: Fill pres field */
   NHAC_FILL_U8_U32_TKN(hoPrepInfoIe->as_Config.extaddgrp_r9.pres,FALSE, 0);

   /* Step 1.2: Fill sourceSysInfoBlockTyp1Ext field *//*Check for 2,3 and 4th parameters Lterrc_rel9 */
   FILL_OCT_STR(hoPrepInfoIe->as_Config.extaddgrp_r9.sourceSysInfoBlockTyp1Ext,4,1,evnt);

   /* Step 1.3: Fill sourceOtherConfig_r9 field */
   /* Step 1.3.1: Fill sourceOtherConfig_r9.pres field */
   FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_r9.sourceOtherConfig_r9.pres, PRSNT_NODEF);
  
   /* Step 1.3.2: Fill sourceOtherConfig_r9.reportProximityConfig_r9 field */
    prxCfg = &(hoPrepInfoIe->as_Config.extaddgrp_r9.sourceOtherConfig_r9.reportProximityConfig_r9); 

   /* Step 1.3.2.1: Fill sourceOtherConfig_r9.reportProximityConfig_r9.pres field */
   FILL_UINT_TKN(prxCfg->pres, PRSNT_NODEF);

   /* Step 1.3.2.1: Fill proximityIndEUTRA_r9 field */
   FILL_UINT_TKN(prxCfg->proximityIndEUTRA_r9, 1);

   /* Step 1.3.2.1: Fill proximityIndUTRA_r9 field */
   FILL_UINT_TKN(prxCfg->proximityIndUTRA_r9, 1);
#else 
   /* Filling the CSG related information :Lterrc_rel11 */
   /* Step 1: Fill extaddgrp_r1 */
   /* Step 1.1: Fill pres field */
   NHAC_FILL_U8_U32_TKN(hoPrepInfoIe->as_Config.extaddgrp_1.pres,FALSE, 0);

   /* Step 1.2: Fill sourceSysInfoBlockTyp1Ext field *//*Check for 2,3 and 4th parameters Lterrc_rel9 */
   FILL_OCT_STR(hoPrepInfoIe->as_Config.extaddgrp_1.sourceSysInfoBlockTyp1Ext,4,1,evnt);

   /* Step 1.3: Fill sourceOtherConfig_1 field */
   /* Step 1.3.1: Fill sourceOtherConfig_1.pres field */
   FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_1.sourceOtherConfig_r9.pres, PRSNT_NODEF);
  
   /* Step 1.3.2: Fill sourceOtherConfig_r9.reportProximityConfig_r9 field */
    prxCfg = &(hoPrepInfoIe->as_Config.extaddgrp_1.sourceOtherConfig_r9.reportProximityConfig_r9); 

   /* Step 1.3.2.1: Fill sourceOtherConfig_r9.reportProximityConfig_r9.pres field */
   FILL_UINT_TKN(prxCfg->pres, PRSNT_NODEF);

   /* Step 1.3.2.1: Fill proximityIndEUTRA_r9 field */
   FILL_UINT_TKN(prxCfg->proximityIndEUTRA_r9, 1);

   /* Step 1.3.2.1: Fill proximityIndUTRA_r9 field */
   FILL_UINT_TKN(prxCfg->proximityIndUTRA_r9, 1);
#endif

#ifndef RRC_REL11
   NHAC_FILL_U8_U32_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.pres,FALSE, 0);
#else
   NHAC_FILL_U8_U32_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.pres,TRUE, 1);
   FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.noComp, 1);
   CMXTA_GET_MEM(evnt,(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.noComp.val)*
               (sizeof(NhuSCellToAddMod_r10)),&(hoPrepInfoIe->as_Config.extaddgrp_2.\
                  sourceSCellConfigLst_r10.member));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "sCellIdx", &sCellIdx);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "physCellId", &physCellId);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "dlCarrierFreq", &dlCarrierFreq);
   for(idx=0; idx<hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.noComp.val; idx++)
   {
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].pres,\
           PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           sCellIdx_r10, sCellIdx);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           cellIdentification_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           cellIdentification_r10.physCellId_r10, physCellId);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           cellIdentification_r10.dl_CarrierFreq_r10, dlCarrierFreq);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.dl_Bandwidth_r10,\
           NhuRadioResourceConfigCmnSCell_r10nonUL_Cfg_r10dl_Bandwidth_r10n6Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.antennaInfoCmn_r10.\
           pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.antennaInfoCmn_r10.\
           antennaPortsCount, NhuAntennaInfoCmnantennaPortsCountan1Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.mbsfn_SubfrmConfigLst_r10.noComp, 1);
     CMXTA_GET_MEM(evnt,(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.mbsfn_SubfrmConfigLst_r10.noComp.val)*
           (sizeof(NhuMBSFN_SubfrmConfig)),&(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.\
           member[idx].radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.mbsfn_SubfrmConfigLst_r10.member));
     for(idx1=0; idx1<hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.mbsfn_SubfrmConfigLst_r10.\
                                 noComp.val; idx1++)
     {
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.mbsfn_SubfrmConfigLst_r10.\
           member[idx1].pres, PRSNT_NODEF);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.mbsfn_SubfrmConfigLst_r10.\
           member[idx1].radioframeAllocnPeriod, NhuMBSFN_SubfrmConfigradioframeAllocnPeriodn1Enum);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.mbsfn_SubfrmConfigLst_r10.\
           member[idx1].radioframeAllocnOffset, 1);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.mbsfn_SubfrmConfigLst_r10.\
           member[idx1].subframeAllocn.choice, 0);
       if(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
                        radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.mbsfn_SubfrmConfigLst_r10.\
                                   member[idx1].subframeAllocn.choice.val==0)
       {
         FILL_BIT_STR(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.mbsfn_SubfrmConfigLst_r10.\
           member[idx1].subframeAllocn.val.oneFrame, 6, 1, evnt);
       }
       else
       {
         FILL_BIT_STR(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.mbsfn_SubfrmConfigLst_r10.\
           member[idx1].subframeAllocn.val.fourFrames, 24, 1, evnt);

       }
     }
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.phich_Config_r10.\
           pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.phich_Config_r10.\
           phich_Duration, NhuPHICH_Configphich_DurationnormalEnum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.phich_Config_r10.\
           phich_Resource, NhuPHICH_Configphich_ResourceoneSixthEnum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.pdsch_ConfigCmn_r10.\
           pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.pdsch_ConfigCmn_r10.\
           referenceSignalPower, 1);
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "pb", &pb);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.pdsch_ConfigCmn_r10.\
           p_b, pb);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.tdd_Config_r10.\
           pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.tdd_Config_r10.\
           subframeAssignment, NhuTDD_ConfigsubframeAssignmentsa0Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.nonUL_Cfg_r10.tdd_Config_r10.\
           specialSubfrmPatterns, NhuTDD_ConfigspecialSubfrmPatternsssp0Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.ul_FreqInfo_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.ul_FreqInfo_r10.ul_CarrierFreq_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.ul_FreqInfo_r10.ul_Bandwidth_r10,\
           NhuRadioResourceConfigCmnSCell_r10ul_Cfg_r10ul_FreqInfo_r10ul_Bandwidth_r10n6Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.ul_FreqInfo_r10.additionalSpectrumEmissionSCell_r10,\
           1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.p_Max_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.uplinkPowerCntrlCmnSCell_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.uplinkPowerCntrlCmnSCell_r10.p0_NominalPUSCH_r10,\
           1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.uplinkPowerCntrlCmnSCell_r10.alpha_r10,\
           NhuUlnkPowerCntrlCmnSCell_r10alpha_r10al0Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.soundingRS_UL_ConfigCmn_r10.choice,0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.soundingRS_UL_ConfigCmn_r10.val.setup.pres,\
           PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.soundingRS_UL_ConfigCmn_r10.val.setup.\
           srs_BandwidthConfig, NhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfigbw0Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.soundingRS_UL_ConfigCmn_r10.val.setup.\
           srs_SubfrmConfig, NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc0Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.soundingRS_UL_ConfigCmn_r10.val.setup.\
           ackNackSRS_SimultaneousTransmission, 0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.soundingRS_UL_ConfigCmn_r10.val.setup.\
           srs_MaxUpPts, NhuSoundingRS_UL_ConfigCmnsetupsrs_MaxUpPtstrueEnum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.ul_CyclicPrefixLength_r10,\
           NhuUL_CyclicPrefixLengthlen1Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.prach_ConfigSCell_r10.pres, PRSNT_NODEF);
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "prachCfgIdx", &prachCfgIdx);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.prach_ConfigSCell_r10.prach_ConfigIdx_r10,\
           prachCfgIdx);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.pusch_ConfigCmn_r10.pres,\
           PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.pusch_ConfigCmn_r10.pusch_ConfigBasic.pres,\
           PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.pusch_ConfigCmn_r10.pusch_ConfigBasic.n_SB,\
           1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.pusch_ConfigCmn_r10.pusch_ConfigBasic.hoppingMode,\
           NhuPUSCH_ConfigCmnpusch_ConfigBasichoppingModeinterSubFrameEnum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.pusch_ConfigCmn_r10.pusch_ConfigBasic.pusch_HoppingOffset,\
           1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.pusch_ConfigCmn_r10.pusch_ConfigBasic.enable64QAM,\
           0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.pusch_ConfigCmn_r10.ul_ReferenceSignalsPUSCH.pres,\
           PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.pusch_ConfigCmn_r10.ul_ReferenceSignalsPUSCH.\
           groupHoppingEnabled, 0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.pusch_ConfigCmn_r10.ul_ReferenceSignalsPUSCH.\
           groupAssignmentPUSCH, 0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.pusch_ConfigCmn_r10.ul_ReferenceSignalsPUSCH.\
           sequenceHoppingEnabled, 0);
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "cyclicShift", &cyclicShift);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigCmnSCell_r10.ul_Cfg_r10.pusch_ConfigCmn_r10.ul_ReferenceSignalsPUSCH.\
           cyclicShift, cyclicShift);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.pres,\
           PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           antennaInfo_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           antennaInfo_r10.transmissionMode_r10, NhuAntennaInfoDedicated_r10transmissionMode_r10tm1Enum);
     FILL_BIT_STR(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           antennaInfo_r10.codebookSubsetRestrn_r10, 255, 1, evnt);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           antennaInfo_r10.ue_TransmitAntennaSelection.choice, 0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           antennaInfo_r10.ue_TransmitAntennaSelection.val.setup,\
           NhuAntennaInfoDedicated_r10ue_TransmitAntennaSelectionsetupclosedLoopEnum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           crossCarrierSchedulingConfig_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           crossCarrierSchedulingConfig_r10.schedulingCellInfo_r10.choice, 0);
     if(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
        radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
        crossCarrierSchedulingConfig_r10.schedulingCellInfo_r10.choice.val == 0)
     {
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           crossCarrierSchedulingConfig_r10.schedulingCellInfo_r10.val.own_r10.pres, PRSNT_NODEF);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           crossCarrierSchedulingConfig_r10.schedulingCellInfo_r10.val.own_r10.cif_Presence_r10,1);
     }
     else
     {
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           crossCarrierSchedulingConfig_r10.schedulingCellInfo_r10.val.other_r10.pres, PRSNT_NODEF);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           crossCarrierSchedulingConfig_r10.schedulingCellInfo_r10.val.other_r10.schedulingCellId_r10,\
           1);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           crossCarrierSchedulingConfig_r10.schedulingCellInfo_r10.val.other_r10.pdsch_Start_r10, 1);
     }
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           csi_RS_Config_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           csi_RS_Config_r10.csi_RS_r10.choice, 0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           csi_RS_Config_r10.csi_RS_r10.val.setup.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           csi_RS_Config_r10.csi_RS_r10.val.setup.antennaPortsCount_r10,\
           NhuCSI_RS_Config_r10csi_RS_r10setupantennaPortsCount_r10an1Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           csi_RS_Config_r10.csi_RS_r10.val.setup.resourceConfig_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           csi_RS_Config_r10.csi_RS_r10.val.setup.subframeConfig_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           csi_RS_Config_r10.csi_RS_r10.val.setup.p_C_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           csi_RS_Config_r10.zeroTxPowerCSI_RS_r10.choice, 0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           csi_RS_Config_r10.zeroTxPowerCSI_RS_r10.val.setup.pres, PRSNT_NODEF);
     FILL_BIT_STR(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           csi_RS_Config_r10.zeroTxPowerCSI_RS_r10.val.setup.zeroTxPowerResourceConfigLst_r10,\
           16, 1, evnt);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           csi_RS_Config_r10.zeroTxPowerCSI_RS_r10.val.setup.zeroTxPowerSubfrmConfig_r10,1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           pdsch_ConfigDedicated_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.nonUL_Cfg_r10.\
           pdsch_ConfigDedicated_r10.p_a, NhuPDSCH_ConfigDedicatedp_adB_6Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.pres,\
           PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           antennaInfoUL_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           antennaInfoUL_r10.transmissionModeUL_r10,NhuAntennaInfoUL_r10transmissionModeUL_r10tm1Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           antennaInfoUL_r10.fourAntennaPortActivated_r10,\
           NhuAntennaInfoUL_r10fourAntennaPortActivated_r10setupEnum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           pusch_ConfigDedicatedSCell_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           pusch_ConfigDedicatedSCell_r10.groupHoppingDisabled_r10,\
           NhuPUSCH_ConfigDedicatedSCell_r10groupHoppingDisabled_r10trueEnum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           pusch_ConfigDedicatedSCell_r10.dmrs_WithOCC_Activated_r10,\
           NhuPUSCH_ConfigDedicatedSCell_r10dmrs_WithOCC_Activated_r10trueEnum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           uplinkPowerCntrlDedicatedSCell_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           uplinkPowerCntrlDedicatedSCell_r10.p0_UE_PUSCH_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           uplinkPowerCntrlDedicatedSCell_r10.deltaMCS_Enabled_r10,\
           NhuUlnkPowerCntrlDedicatedSCell_r10deltaMCS_Enabled_r10en0Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           uplinkPowerCntrlDedicatedSCell_r10.accumulationEnabled_r10, 0);
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "pSRSOffset", &pSRSOffset);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           uplinkPowerCntrlDedicatedSCell_r10.pSRS_Offset_r10, pSRSOffset);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           uplinkPowerCntrlDedicatedSCell_r10.pSRS_OffsetAp_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           uplinkPowerCntrlDedicatedSCell_r10.filterCoefficient_r10,\
           NhuFilterCoefficientfc0Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           uplinkPowerCntrlDedicatedSCell_r10.pathlossReferenceLinking_r10,\
           NhuUlnkPowerCntrlDedicatedSCell_r10pathlossReferenceLinking_r10pCellEnum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportModeAperiodic_r10, NhuCQI_ReportModeAperiodicrm12Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.nomPDSCH_RS_EPRE_Offset_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.choice, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.pres,PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.cqi_PUCCH_ResourceIdx_r10,\
           1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.cqi_PUCCH_ResourceIdxP1_r10,\
           1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.cqi_pmi_ConfigIdx, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.\
           cqi_FormatIndicatorPeriodic_r10.choice, 0);
     if(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
        radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
        cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.cqi_FormatIndicatorPeriodic_r10.\
        choice.val == 0)
     {
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.\
           cqi_FormatIndicatorPeriodic_r10.val.widebandCQI_r10.pres, PRSNT_NODEF);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.\
           cqi_FormatIndicatorPeriodic_r10.val.widebandCQI_r10.csi_ReportMode_r10,\
           NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10widebandCQI_r10csi_ReportMode_r10submode1Enum);
     }
     else
     {
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.\
           cqi_FormatIndicatorPeriodic_r10.val.subbandCQI_r10.pres, PRSNT_NODEF);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.\
           cqi_FormatIndicatorPeriodic_r10.val.subbandCQI_r10.k, 1);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.\
           cqi_FormatIndicatorPeriodic_r10.val.subbandCQI_r10.periodicityFactor_r10,\
           NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10periodicityFactor_r10n2Enum);
     }
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.ri_ConfigIdx, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.simultaneousAckNackAndCQI, 0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.cqi_Mask_r9,\
           NhuCQI_ReportPeriodic_r10setupcqi_Mask_r9setupEnum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.csi_ConfigIdx_r10.choice, 0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.csi_ConfigIdx_r10.val\
           .setup.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.csi_ConfigIdx_r10.val\
           .setup.cqi_pmi_ConfigIdx2_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.cqi_ReportPeriodicSCell_r10.val.setup.csi_ConfigIdx_r10.val\
           .setup.ri_ConfigIdx2_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           cqi_ReportConfigSCell_r10.pmi_RI_Report_r10,\
           NhuCQI_ReportConfigSCell_r10pmi_RI_Report_r10setupEnum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicated_r10.choice, 0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicated_r10.val.setup.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicated_r10.val.setup.srs_Bandwidth,\
           NhuSoundingRS_UL_ConfigDedicatedsetupsrs_Bandwidthbw0Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicated_r10.val.setup.srs_HoppingBandwidth,\
           NhuSoundingRS_UL_ConfigDedicatedsetupsrs_HoppingBandwidthhbw0Enum);
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "freqDomainPosition",\
           &freqDomainPosition);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicated_r10.val.setup.freqDomainPosition, freqDomainPosition);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicated_r10.val.setup.duration, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicated_r10.val.setup.srs_ConfigIdx, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicated_r10.val.setup.transmissionComb, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicated_r10.val.setup.cyclicShift,\
           NhuSoundingRS_UL_ConfigDedicatedsetupcyclicShiftcs0Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicated_v1020.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicated_v1020.srs_AntennaPort_r10,NhuSRS_AntennaPortan1Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.choice, 0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ConfigIdxAp_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ConfigApDCI_Format4_r10.\
           noComp, 1);
     CMXTA_GET_MEM(evnt,(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ConfigApDCI_Format4_r10.noComp.val)*
           (sizeof(NhuSRS_ConfigAp_r10)),&(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.\
           member[idx].radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ConfigApDCI_Format4_r10.member));
     for(idx1=0; idx1<hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
            radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
             soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ConfigApDCI_Format4_r10.\
                                            noComp.val; idx1++)
     {
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ConfigApDCI_Format4_r10.\
           member[idx1].pres, PRSNT_NODEF);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ConfigApDCI_Format4_r10.\
           member[idx1].srs_AntennaPortAp_r10, NhuSRS_AntennaPortan1Enum);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ConfigApDCI_Format4_r10.\
           member[idx1].srs_BandwidthAp_r10,NhuSRS_ConfigAp_r10srs_BandwidthAp_r10bw0Enum);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ConfigApDCI_Format4_r10.\
           member[idx1].freqDomainPositionAp_r10, 1);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ConfigApDCI_Format4_r10.\
           member[idx1].transmissionCombAp_r10, 1);
       FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ConfigApDCI_Format4_r10.\
           member[idx1].cyclicShiftAp_r10, NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs0Enum);
     }
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.choice, 0);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           srs_ConfigApDCI_Format0_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           srs_ConfigApDCI_Format0_r10.srs_AntennaPortAp_r10, NhuSRS_AntennaPortan1Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           srs_ConfigApDCI_Format0_r10.srs_BandwidthAp_r10,NhuSRS_ConfigAp_r10srs_BandwidthAp_r10bw0Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           srs_ConfigApDCI_Format0_r10.freqDomainPositionAp_r10, 1);
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "transmissionCombAp",
           &transmissionCombAp);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           srs_ConfigApDCI_Format0_r10.transmissionCombAp_r10, transmissionCombAp);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           srs_ConfigApDCI_Format0_r10.cyclicShiftAp_r10,NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs0Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           srs_ConfigApDCI_Format1a2b2c_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           srs_ConfigApDCI_Format1a2b2c_r10.srs_AntennaPortAp_r10, NhuSRS_AntennaPortan1Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           srs_ConfigApDCI_Format1a2b2c_r10.srs_BandwidthAp_r10,NhuSRS_ConfigAp_r10srs_BandwidthAp_r10bw0Enum);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           srs_ConfigApDCI_Format1a2b2c_r10.freqDomainPositionAp_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           srs_ConfigApDCI_Format1a2b2c_r10.transmissionCombAp_r10, 1);
     FILL_UINT_TKN(hoPrepInfoIe->as_Config.extaddgrp_2.sourceSCellConfigLst_r10.member[idx].\
           radioResourceConfigDedicatedSCell_r10.physicalConfigDedicatedSCell_r10.ul_Cfg_r10.\
           soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.srs_ActivateAp_r10.val.setup.\
           srs_ConfigApDCI_Format1a2b2c_r10.cyclicShiftAp_r10,NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs0Enum);
   }
#endif
#endif
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuHoPrepInfo */

#ifdef NHU_VER2
/*
*
*       Fun:   nhAcUtlFillNhuVarShortMACInput
*
*       Desc:  This function fills the var-ShortMAC-I message
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuVarShortMACInput
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
Ptr            evnt,
NhuVarShortMAC_Input *varShortMacInput
)
#else
PUBLIC S16 nhAcUtlFillNhuVarShortMACInput(tcCb, spCb, evnt, varShortMacInput)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb; 
Ptr            evnt;
NhuVarShortMAC_Input *varShortMacInput;
#endif
{
   U8    cellIdentityVal =1; 
   U32   physCellIdVal   =1;
   U8    c_RNTIVal; 

   TRC2(nhAcUtlFillNhuVarShortMACInput);
   
   /* Filling varShortMacInput->pres */
   FILL_UINT_TKN(varShortMacInput->pres,PRSNT_NODEF);
   
   /* Filling cellIdentity */
   FILL_BIT_STR(varShortMacInput->cellIdentity, 28, 1, evnt); 
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cellIdentityVal", &cellIdentityVal);
   FILL_BIT_STR(varShortMacInput->cellIdentity, 28, cellIdentityVal, evnt);

   /* Filling physCellId */
   NHAC_FILL_U8_U32_TKN(varShortMacInput->physCellId, TRUE, 1);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "physCellIdVal", &physCellIdVal);
   NHAC_FILL_U8_U32_TKN(varShortMacInput->physCellId, TRUE, physCellIdVal);
   
   /* Filling c_RNTI */
   FILL_BIT_STR(varShortMacInput->c_RNTI, 16, 1, evnt); 
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "c_RNTIVal", &c_RNTIVal);
   FILL_BIT_STR(varShortMacInput->c_RNTI, 16, c_RNTIVal, evnt);
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuVarShortMACInput */
#endif /* NHU_VER2 */

/*
*
*       Fun:   nhAcUtlFillNhuUeCapEnq
*
*       Desc:  This function fills UE capability enquiry message.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuUeCapEnq
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
NhuDatReqSdus  *nhuDatReqSdu
)
#else
PUBLIC S16 nhAcUtlFillNhuUeCapEnq(tcCb, spCb, nhuDatReqSdu)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb; 
NhuDatReqSdus  *nhuDatReqSdu;
#endif
{
   NhuDL_DCCH_Msg     *dlMsg = NULLP;
   NhuUECapEnquiry    *ueCapEnq = NULLP;
   U32                rrc_transId;
   U8                 rrcTransIdPres;
   U8                 pdcpId = 0;
   U8                 ratType;
   NhuUE_CapRqst      *ueCapReq;
  
   TRC2(nhAcUtlFillNhuUeCapEnq);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpId", &pdcpId);
   nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.pdcpId = pdcpId;

   dlMsg = &(nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.m.dcchMsg);

   FILL_UINT_TKN(dlMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(dlMsg->message.choice,DL_DCCH_MSGTYP_C1);
   FILL_UINT_TKN(dlMsg->message.val.c1.choice,C1_UECAPENQUIRY);

   ueCapEnq = &(dlMsg->message.val.c1.val.ueCapEnquiry);

   FILL_UINT_TKN(ueCapEnq->pres,PRSNT_NODEF);

   rrcTransIdPres = 1;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 1;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(ueCapEnq->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      NHAC_FILL_U8_U32_TKN(ueCapEnq->rrc_TrnsxnId, NOTPRSNT, NOTPRSNT);
   }
   FILL_UINT_TKN(ueCapEnq->criticalExtns.choice, C1_UECAPENQUIRY_R8);
   FILL_UINT_TKN(ueCapEnq->criticalExtns.val.c1.choice, CRITICALEXTNS_C1);
   FILL_UINT_TKN(ueCapEnq->criticalExtns.val.c1.val.ueCapEnquiry_r8.pres,
               PRSNT_NODEF);

   ueCapReq = &(ueCapEnq->criticalExtns.val.c1.val.ueCapEnquiry_r8.ue_CapRqst);
   ratType = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ratType",
                  &ratType);
   if(ratType == 0 || ratType == 1) /* E-UTRA only(0) or UTRA only(1) */
   {
      FILL_UINT_TKN(ueCapReq->noComp, 1);
      /* Allocate memory required for num components */
      CMXTA_GET_MEM(nhuDatReqSdu, sizeof(NhuRAT_Typ)*ueCapReq->noComp.val,
                    &(ueCapReq->member));
      if(ratType == 0)
      {
         FILL_UINT_TKN(ueCapReq->member[0], NhuRAT_TypeutraEnum);
      }
      else
      {
         FILL_UINT_TKN(ueCapReq->member[0], NhuRAT_TyputraEnum);
      }
   }
   else if(ratType == 2) /* both E-UTRA and UTRA */
   {
      FILL_UINT_TKN(ueCapReq->noComp, 2);
      /* Allocate memory required for num components */
      CMXTA_GET_MEM(nhuDatReqSdu, sizeof(NhuRAT_Typ)*ueCapReq->noComp.val,
                    &(ueCapReq->member));
      FILL_UINT_TKN(ueCapReq->member[0], NhuRAT_TypeutraEnum);
      FILL_UINT_TKN(ueCapReq->member[1], NhuRAT_TyputraEnum);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuUeCapEnq */

/*
*
*       Fun:   nhAcUtlFillNhuMobFrmEutraCmd
*
*       Desc:  This function fills Mobility From E-UTRA Command.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuMobFrmEutraCmd
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
NhuDatReqSdus  *nhuDatReqSdu
)
#else
PUBLIC S16 nhAcUtlFillNhuMobFrmEutraCmd(tcCb, spCb, nhuDatReqSdu)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb; 
NhuDatReqSdus  *nhuDatReqSdu;
#endif
{
   NhuDL_DCCH_Msg     *dlMsg = NULLP;
   NhuMobilityFromEUTRACmd    *mobFrmEutraCmd = NULLP;
   U32                rrc_transId;
   U8                 rrcTransIdPres;
   U8                 pdcpId = 0;
   U8                 ratType;
   NhuMobilityFromEUTRACmd_r8_IEs *mobFrmEutraIe;
   Bool               isSIPres;
   Bool               isNasSecPrmPres;
#ifdef LTERRC_REL9
/*R9 upgrade: Filling the R9 IEs*/
   NhuMobilityFromEUTRACmd_r9_IEs *mobFrmEutraR9Ies;
   U16 count;
   U16 idx;
#endif /*LTERRC_REL9*/
  
   TRC2(nhAcUtlFillNhuMobFrmEutraCmd);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpId", &pdcpId);
   nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.pdcpId = pdcpId;

   dlMsg = &(nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.m.dcchMsg);

   FILL_UINT_TKN(dlMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(dlMsg->message.choice,DL_DCCH_MSGTYP_C1);
   FILL_UINT_TKN(dlMsg->message.val.c1.choice,C1_MOBILITYFROMEUTRACMD);

   mobFrmEutraCmd = &(dlMsg->message.val.c1.val.mobilityFromEUTRACmd);

   FILL_UINT_TKN(mobFrmEutraCmd->pres,PRSNT_NODEF);

   rrcTransIdPres = 1;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 1;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(mobFrmEutraCmd->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      NHAC_FILL_U8_U32_TKN(mobFrmEutraCmd->rrc_TrnsxnId, NOTPRSNT, NOTPRSNT);
   }
   FILL_UINT_TKN(mobFrmEutraCmd->criticalExtns.choice, C1_MOBILITYFROMEUTRACMD_R8);
   FILL_UINT_TKN(mobFrmEutraCmd->criticalExtns.val.c1.choice, CRITICALEXTNS_C1);

   mobFrmEutraIe = &mobFrmEutraCmd->criticalExtns.val.c1.val.mobilityFromEUTRACmd_r8;
   FILL_UINT_TKN(mobFrmEutraIe->pres, PRSNT_NODEF);
   FILL_UINT_TKN(mobFrmEutraIe->cs_FallbackIndicator, FALSE);

   /* Fill Handover information */
   FILL_UINT_TKN(mobFrmEutraIe->purpose.choice, PURPOSE_HANDOVER);
   FILL_UINT_TKN(mobFrmEutraIe->purpose.val.handover.pres, PRSNT_NODEF);
   ratType = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ratType",
                  &ratType);
   if(ratType == 0) /* utra */
   {
      FILL_UINT_TKN(mobFrmEutraIe->purpose.val.handover.targetRAT_Typ, 
                    NhuHovrtargetRAT_TyputraEnum);
      FILL_OCT_STR(mobFrmEutraIe->purpose.val.handover.targetRAT_MsgCont, 
                   4, 1, nhuDatReqSdu); 
   }
   else if(ratType == 1) /* geran */
   {
      FILL_UINT_TKN(mobFrmEutraIe->purpose.val.handover.targetRAT_Typ, 
                    NhuHovrtargetRAT_TypgeranEnum);
      FILL_OCT_STR(mobFrmEutraIe->purpose.val.handover.targetRAT_MsgCont, 
                   4, 1, nhuDatReqSdu); 
   }
   isSIPres = 0;
   isNasSecPrmPres = 1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "siPres",
                  &isSIPres);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "nasSecPrmPres",
                  &isNasSecPrmPres);
   if(isSIPres)
   { 
      FILL_UINT_TKN(mobFrmEutraIe->purpose.val.handover.systemInfo.choice, 
                    SI_ORPSI_GERAN_SI);
      FILL_UINT_TKN(mobFrmEutraIe->purpose.val.handover.systemInfo.val.si.noComp, 
                    1);
      /* Allocate memory required for num components */
      CMXTA_GET_MEM(nhuDatReqSdu, sizeof(NhuSysInfoLstGERANMember)*
                    mobFrmEutraIe->purpose.val.handover.systemInfo.val.si.noComp.val,
                    &(mobFrmEutraIe->purpose.val.handover.systemInfo.val.si.member));
      FILL_OCT_STR(mobFrmEutraIe->purpose.val.handover.systemInfo.val.si.\
                    member[0],4, 1, nhuDatReqSdu); 
   }
   if(isNasSecPrmPres)
   {
      FILL_OCT_STR(mobFrmEutraIe->purpose.val.handover.nas_SecParamFromEUTRA, 
                    1, 1, nhuDatReqSdu);
   }
#ifdef RRC_REL11
   FILL_UINT_TKN(mobFrmEutraIe->nonCriticalExtn.pres, PRSNT_NODEF);
   FILL_OCT_STR(mobFrmEutraIe->nonCriticalExtn.lateNonCriticalExtn, 1, 1, nhuDatReqSdu);
   FILL_UINT_TKN(mobFrmEutraIe->nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
   FILL_UINT_TKN(mobFrmEutraIe->nonCriticalExtn.nonCriticalExtn.bandIndicator,\
         NhuBandIndicatorGERANdcs1800Enum);
   FILL_UINT_TKN(mobFrmEutraIe->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);

#endif
#ifdef LTERRC_REL9
/*R9 upgrade: Filling the R9 IEs*/
   mobFrmEutraR9Ies = &mobFrmEutraCmd->criticalExtns.val.c1.val.\
                       mobilityFromEUTRACmd_r9;
   FILL_UINT_TKN(mobFrmEutraR9Ies->pres, PRSNT_NODEF);
   FILL_UINT_TKN(mobFrmEutraR9Ies->cs_FallbackIndicator, PRSNT_NODEF);
  
  
  /* purpose is set to Handover*/
   FILL_UINT_TKN(mobFrmEutraR9Ies->purpose.choice, PURPOSE_HANDOVER);

   if ((mobFrmEutraR9Ies->purpose.choice.val) == PURPOSE_HANDOVER)
   {
      FILL_UINT_TKN(mobFrmEutraR9Ies->purpose.val.handover.pres, PRSNT_NODEF);

      if(ratType == 0)
      {
          NHAC_FILL_U8_U32_TKN(mobFrmEutraR9Ies->purpose.val.handover.targetRAT_Typ,\
                PRSNT_NODEF, NhuHovrtargetRAT_TyputraEnum);
      }
      else  if(ratType == 1)
      {
          NHAC_FILL_U8_U32_TKN(mobFrmEutraR9Ies->purpose.val.handover.targetRAT_Typ,\
                PRSNT_NODEF, NhuHovrtargetRAT_TypgeranEnum);
      }
      FILL_OCT_STR(mobFrmEutraR9Ies->purpose.val.handover.targetRAT_MsgCont, 
            4, 1, nhuDatReqSdu);

      FILL_OCT_STR(mobFrmEutraR9Ies->purpose.val.handover.nas_SecParamFromEUTRA, 
            1, 1, nhuDatReqSdu);
      if(!isNasSecPrmPres)
      {
         mobFrmEutraR9Ies->purpose.val.handover.nas_SecParamFromEUTRA.pres = 0;
      }

      if(isSIPres)
      {
          FILL_UINT_TKN(mobFrmEutraR9Ies->purpose.val.handover.systemInfo.choice,\
                PRSNT_NODEF);
          
          NHAC_FILL_U8_U32_TKN(mobFrmEutraR9Ies->purpose.val.handover.systemInfo.val.\
                si.noComp, PRSNT_NODEF,1);
          
          /* Allocate memory required for num components */
          CMXTA_GET_MEM(nhuDatReqSdu, sizeof(NhuSysInfoLstGERANMember)*
                (mobFrmEutraR9Ies->purpose.val.handover.systemInfo.val.si.noComp.val),
                &(mobFrmEutraR9Ies->purpose.val.handover.systemInfo.val.si.member));
          
          count = mobFrmEutraR9Ies->purpose.val.handover.systemInfo.val.si.noComp.val;
          
          for(idx =0; idx < count; idx++)
          {
             FILL_OCT_STR(mobFrmEutraR9Ies->purpose.val.handover.systemInfo.val.si.\
                   member[idx], 4, 1, nhuDatReqSdu); 
          }
          
          NHAC_FILL_U8_U32_TKN(mobFrmEutraR9Ies->purpose.val.handover.systemInfo.val.\
                psi.noComp, PRSNT_NODEF,1);
          
          /* Allocate memory required for num components */
          CMXTA_GET_MEM(nhuDatReqSdu, sizeof(NhuSysInfoLstGERANMember)*
                (mobFrmEutraR9Ies->purpose.val.handover.systemInfo.val.psi.noComp.val),
                &(mobFrmEutraR9Ies->purpose.val.handover.systemInfo.val.psi.member));
          
          count = mobFrmEutraR9Ies->purpose.val.handover.systemInfo.val.psi.noComp.val;
          
          for(idx =0; idx < count; idx++)
          {
             FILL_OCT_STR(mobFrmEutraR9Ies->purpose.val.handover.systemInfo.val.psi.\
                   member[idx], 4, 1, nhuDatReqSdu); 
          }
      }
   }/*handover*/
   else if ((mobFrmEutraR9Ies->purpose.choice.val) == PURPOSE_CELLCHANGEORDER)
   {
      FILL_UINT_TKN(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.pres,\
            PRSNT_NODEF);

      NHAC_FILL_U8_U32_TKN(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.t304,\
            PRSNT_NODEF, 2);

      FILL_UINT_TKN(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.choice, PRSNT_NODEF);

      FILL_UINT_TKN(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.val.geran.pres, PRSNT_NODEF);

      FILL_UINT_TKN(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.val.geran.physCellId.pres, PRSNT_NODEF);

      FILL_UINT_TKN(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.val.geran.physCellId.pres, PRSNT_NODEF);

      FILL_BIT_STR(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.val.geran.physCellId.networkColourCode,3,1,nhuDatReqSdu);

      FILL_BIT_STR(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.val.geran.physCellId.baseStationColourCode,3,1,nhuDatReqSdu);

      FILL_UINT_TKN(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.val.geran.carrierFreq.pres, PRSNT_NODEF);

      NHAC_FILL_U8_U32_TKN(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.val.geran.carrierFreq.arfcn, PRSNT_NODEF, PRSNT_NODEF);

      NHAC_FILL_U8_U32_TKN(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.val.geran.carrierFreq.bandIndicator, PRSNT_NODEF,\
            NhuBandIndicatorGERANdcs1800Enum);

      FILL_BIT_STR(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.val.geran.networkCntrlOrder, 2, 1, nhuDatReqSdu);

      FILL_UINT_TKN(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.val.geran.systemInfo.choice, PRSNT_NODEF);

      NHAC_FILL_U8_U32_TKN(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.val.geran.systemInfo.val.si.noComp, PRSNT_NODEF, 1);

      /* Allocate memory required for num components */
      CMXTA_GET_MEM(nhuDatReqSdu, sizeof(NhuSysInfoLstGERANMember)*
            (mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
             targetRAT_Typ.val.geran.systemInfo.val.si.noComp.val),
            &(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
               targetRAT_Typ.val.geran.systemInfo.val.si.member));

      count = mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
              targetRAT_Typ.val.geran.systemInfo.val.si.noComp.val;

      for(idx =0; idx < count; idx++)
      {
         FILL_OCT_STR(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
               targetRAT_Typ.val.geran.systemInfo.val.si.\
               member[idx], 4, 1, nhuDatReqSdu); 
      }

      NHAC_FILL_U8_U32_TKN(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
            targetRAT_Typ.val.geran.systemInfo.val.psi.noComp, PRSNT_NODEF, 1);

      /* Allocate memory required for num components */
      CMXTA_GET_MEM(nhuDatReqSdu, sizeof(NhuSysInfoLstGERANMember)*
            (mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
             targetRAT_Typ.val.geran.systemInfo.val.psi.noComp.val),
            &( mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
               targetRAT_Typ.val.geran.systemInfo.val.psi.member));

      count = mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
              targetRAT_Typ.val.geran.systemInfo.val.psi.noComp.val;

      for(idx =0; idx < count; idx++)
      {
         FILL_OCT_STR(mobFrmEutraR9Ies->purpose.val.cellChangeOrder.\
               targetRAT_Typ.val.geran.systemInfo.val.psi.\
               member[idx], 4, 1, nhuDatReqSdu); 
      }
   }/*cellChangeOrder*/
   else if ((mobFrmEutraR9Ies->purpose.choice.val) == PURPOSE_E_CSFB_R9)
   {
      FILL_UINT_TKN(mobFrmEutraR9Ies->purpose.val.e_CSFB_r9.pres, PRSNT_NODEF);
      FILL_OCT_STR(mobFrmEutraR9Ies->purpose.val.e_CSFB_r9.messageContCDMA2000_1XRTT_r9,\
            4,1,nhuDatReqSdu);

      NHAC_FILL_U8_U32_TKN(mobFrmEutraR9Ies->purpose.val.e_CSFB_r9.mobilityCDMA2000_HRPD_r9,\
            PRSNT_NODEF, NhuE_CSFB_r9mobilityCDMA2000_HRPD_r9handoverEnum);

      FILL_OCT_STR(mobFrmEutraR9Ies->purpose.val.e_CSFB_r9.messageContCDMA2000_HRPD_r9,\
            4,1,nhuDatReqSdu);

      FILL_UINT_TKN(mobFrmEutraR9Ies->purpose.val.e_CSFB_r9.redirectCarrierCDMA2000_HRPD_r9.\
            pres, PRSNT_NODEF);

      NHAC_FILL_U8_U32_TKN(mobFrmEutraR9Ies->purpose.val.e_CSFB_r9.redirectCarrierCDMA2000_HRPD_r9.\
            bandClass, PRSNT_NODEF, PRSNT_NODEF);

      NHAC_FILL_U8_U32_TKN(mobFrmEutraR9Ies->purpose.val.e_CSFB_r9.redirectCarrierCDMA2000_HRPD_r9.\
            arfcn, PRSNT_NODEF, PRSNT_NODEF);
   }/*e_CSFB_r9*/
         
   FILL_UINT_TKN(mobFrmEutraR9Ies->nonCriticalExtn.pres, PRSNT_NODEF);
   
   FILL_OCT_STR(mobFrmEutraR9Ies->nonCriticalExtn.lateNonCriticalExtn,\
         4,1,nhuDatReqSdu);
         
   FILL_UINT_TKN(mobFrmEutraR9Ies->nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
#ifdef RRC_REL11
   FILL_UINT_TKN(mobFrmEutraR9Ies->nonCriticalExtn.nonCriticalExtn.bandIndicator,\
         NhuBandIndicatorGERANdcs1800Enum);
   FILL_UINT_TKN(mobFrmEutraR9Ies->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
#endif
#endif/*LTERRC_REL9*/
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuMobFrmEutraCmd */
/*
*
*       Fun:   nhAcUtlFillNhuHoFrmEutraPrep
*
*       Desc:  This function fills HO From EUTRA Prepatration Request message.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuHoFrmEutraPrep
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
NhuDatReqSdus  *nhuDatReqSdu
)
#else
PUBLIC S16 nhAcUtlFillNhuHoFrmEutraPrep(tcCb, spCb, nhuDatReqSdu)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb; 
NhuDatReqSdus  *nhuDatReqSdu;
#endif
{
   NhuDL_DCCH_Msg     *dlMsg = NULLP;
   NhuHovrFromEUTRAPrepRqst    *hoFrmEutraPrp = NULLP;
   U32                rrc_transId;
   U8                 rrcTransIdPres;
   U8                 pdcpId = 0;
   NhuHovrFromEUTRAPrepRqst_r8_IEs *hoPrepIe = NULLP;
   Bool               isCdmaRandPres;
   Bool               isCdmaMbPrmsPres;
#ifdef RRC_REL11
   U32                arfcn = 0;
#endif
   TRC2(nhAcUtlFillNhuHoFrmEutraPrep);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpId", &pdcpId);
   nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.pdcpId = pdcpId;

   dlMsg = &(nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.m.dcchMsg);

   FILL_UINT_TKN(dlMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(dlMsg->message.choice,DL_DCCH_MSGTYP_C1);
   FILL_UINT_TKN(dlMsg->message.val.c1.choice,C1_HANDOVERFROMEUTRAPREPRQST);

   hoFrmEutraPrp = &(dlMsg->message.val.c1.val.handoverFromEUTRAPrepRqst);

   FILL_UINT_TKN(hoFrmEutraPrp->pres,PRSNT_NODEF);

   rrcTransIdPres = 1;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 1;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(hoFrmEutraPrp->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      NHAC_FILL_U8_U32_TKN(hoFrmEutraPrp->rrc_TrnsxnId, NOTPRSNT, NOTPRSNT);
   }
   FILL_UINT_TKN(hoFrmEutraPrp->criticalExtns.choice, C1_HANDOVERPREPINFO_R8);
   FILL_UINT_TKN(hoFrmEutraPrp->criticalExtns.val.c1.choice, CRITICALEXTNS_C1);

   hoPrepIe = &hoFrmEutraPrp->criticalExtns.val.c1.val.handoverFromEUTRAPrepRqst_r8;
   FILL_UINT_TKN(hoPrepIe->pres, PRSNT_NODEF);
   FILL_UINT_TKN(hoPrepIe->cdma2000_Typ, NhuCDMA2000_Typtype1XRTTEnum);

   isCdmaRandPres = 1;
   isCdmaMbPrmsPres = 1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "cdmaRandPres",
                  &isCdmaRandPres);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "cdmaMbPrmsPres",
                  &isCdmaMbPrmsPres);
   if(isCdmaRandPres)
   { 
      FILL_BIT_STR(hoPrepIe->rand, 32, 1, nhuDatReqSdu);
   }
   if(isCdmaMbPrmsPres)
   {
      FILL_OCT_STR(hoPrepIe->mobilityParams, 4, 1, nhuDatReqSdu);
   }

#ifdef LTERRC_REL9
   /*R9 upgrade: Filling R9 IEs*/
   FILL_UINT_TKN(hoPrepIe->nonCriticalExtn.pres, PRSNT_NODEF);
   FILL_OCT_STR(hoPrepIe->nonCriticalExtn.lateNonCriticalExtn, 4, 1, nhuDatReqSdu);
   FILL_UINT_TKN(hoPrepIe->nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
   FILL_UINT_TKN(hoPrepIe->nonCriticalExtn.nonCriticalExtn.concurrPrepCDMA2000_HRPD_r9, PRSNT_NODEF);
   FILL_UINT_TKN(hoPrepIe->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
#ifdef RRC_REL11
   FILL_UINT_TKN(hoPrepIe->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.dualRxTxRedirectIndicator_r10,\
         NhuHovrFromEUTRAPrepRqst_v1020_IEsdualRxTxRedirectIndicator_r10trueEnum);
   FILL_UINT_TKN(hoPrepIe->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.redirectCarrierCDMA2000_1XRTT_r10.pres,\
        PRSNT_NODEF );
   FILL_UINT_TKN(hoPrepIe->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.redirectCarrierCDMA2000_1XRTT_r10.bandClass,\
         NhuBandclassCDMA2000bc0Enum);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "arfcn", &arfcn);
   FILL_UINT_TKN(hoPrepIe->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.redirectCarrierCDMA2000_1XRTT_r10.arfcn,\
         arfcn);
   FILL_UINT_TKN(hoPrepIe->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.pres,\
         PRSNT_NODEF);
#endif
#endif /*LTERRC_REL9 */
      
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuHoFrmEutraPrep */

#ifdef LTERRC_REL9
/******************************************************************************/
/*
*
*       Fun:   nhAcUtlFillNhuUEInfoRqst
*
*       Desc:  This function fills the UE Information Request Message
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: Part of release 9 CSG activity.
*
*       File:  nhac_nhuutl.c
*
*/

#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuUEInfoRqst
(
  CmXtaTCCb      *tcCb,
  CmXtaSpCb      *spCb,
  NhuDatReqSdus  *nhuDatReqSdu
)
#else
PUBLIC S16 nhAcUtlFillNhuUEInfoRqst(tcCb, spCb, nhuDatReqSdu)
  CmXtaTCCb      *tcCb;
  CmXtaSpCb      *spCb;
  NhuDatReqSdus  *nhuDatReqSdu;
#endif
{

  NhuDL_DCCH_Msg     *dlMsg = NULLP;
  NhuUEInfoRqst_r9 *ueInforeq = NULLP;
  NhuUEInfoRqst_r9_IEs *ueInforeq_ie = NULL;
  NhuUEInfoRqst_v930_IEs *v930_ie = NULL;

  U8                 rrcTransIdPres;
  U8                 pdcpId = 0;
  U32                rrc_transId;  
  
  TRC2(nhAcUtlFillUEInfoRqst_r9);
  cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpId", &pdcpId);
  nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.pdcpId = pdcpId; 

  dlMsg = &(nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.m.dcchMsg);
  FILL_UINT_TKN(dlMsg->pres,PRSNT_NODEF);
  FILL_UINT_TKN(dlMsg->message.choice,DL_DCCH_MSGTYP_C1);
  FILL_UINT_TKN(dlMsg->message.val.c1.choice,C1_UEINFORQST_R9__1);

  ueInforeq = &(dlMsg->message.val.c1.val.ueInfoRqst_r9);
  
  FILL_UINT_TKN(ueInforeq->pres,PRSNT_NODEF);
  rrcTransIdPres = 1;

  cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
  if (rrcTransIdPres)
  {
     rrc_transId = 0;
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                 &rrc_transId);
     FILL_UINT_TKN(ueInforeq->rrc_TrnsxnId, rrc_transId);
  }
  else
  {
     NHAC_FILL_U8_U32_TKN(ueInforeq->rrc_TrnsxnId, NOTPRSNT, NOTPRSNT);
  }
 
  FILL_UINT_TKN(ueInforeq->criticalExtns.choice, CRITICALEXTNS_C1);
  /*TODO:MP: Filling the choice */
  FILL_UINT_TKN(ueInforeq->criticalExtns.val.c1.choice,C1_UEINFORQST_R9__27);/*Venu*/
  ueInforeq_ie =&(ueInforeq->criticalExtns.val.c1.val.ueInfoRqst_r9);  

  FILL_UINT_TKN(ueInforeq_ie->pres,PRSNT_NODEF);  

  /* Step 1: Fill rach_ReportReq_r9 */
  /*TODO:MP: Filling the PRSNT_NODEF */
  NHAC_FILL_U8_U32_TKN(ueInforeq_ie->rach_ReportReq_r9,PRSNT_NODEF,NOTPRSNT); 

  /* Step 2: Fill rlf_ReportReq_r9  */
  /*TODO:MP: Filling the PRSNT_NODEF*/
  NHAC_FILL_U8_U32_TKN(ueInforeq_ie->rlf_ReportReq_r9,PRSNT_NODEF,NOTPRSNT);

  /* Step 3: Fill nonCriticalExtn   */
  v930_ie = &(ueInforeq_ie->nonCriticalExtn);
 
  FILL_UINT_TKN(v930_ie->pres,NOTPRSNT); 

  /* Step 4: Fill lateNonCriticalExtn*//*Check for the second param */
  FILL_OCT_STR(v930_ie->lateNonCriticalExtn,4,1,nhuDatReqSdu);

  /* Step 5: Fill nonCriticalExtn: Should be made PRSNT_NODEF when future
             values are filled.*/
#ifndef RRC_REL11  
  FILL_UINT_TKN(v930_ie->nonCriticalExtn.pres,NOTPRSNT);
#else 
  FILL_UINT_TKN(v930_ie->nonCriticalExtn.pres,PRSNT_NODEF);
  FILL_UINT_TKN(v930_ie->nonCriticalExtn.logMeasReportReq_r10,\
        NhuUEInfoRqst_v1020_IEslogMeasReportReq_r10trueEnum);
  FILL_UINT_TKN(v930_ie->nonCriticalExtn.nonCriticalExtn.pres,PRSNT_NODEF);
#endif

  RETVALUE(CMXTA_ERR_NONE);

}

/******************************************************************************/
#endif /*LTERRC_REL9*/

/*
*
*       Fun:   nhAcUtlFillNhuCounterCheckMsg
*
*       Desc:  This function fills Counter Check UE Message
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuCounterCheckMsg
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
NhuDatReqSdus  *nhuDatReqSdu
)
#else
PUBLIC S16 nhAcUtlFillNhuCounterCheckMsg(tcCb, spCb, nhuDatReqSdu)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb; 
NhuDatReqSdus  *nhuDatReqSdu;
#endif
{
   NhuDL_DCCH_Msg     *dlMsg = NULLP;
   NhuCounterCheck    *cntrChk = NULLP;
   U32                rrc_transId;
   U8                 rrcTransIdPres;
   U8                 pdcpId = 0;
   NhuCounterCheck_r8_IEs *cntrChkIe = NULLP;
   S16                i;
   U8                 numDrb;
   U8                 numDrbCnt;
   Txt                msgStr[100];
   Txt                frstWrd[3];
   U16                drb[32];
   U16                rbVal;
   U16                len;
  
   TRC2(nhAcUtlFillNhuCounterCheckMsg);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pdcpId", &pdcpId);
   nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.pdcpId = pdcpId;

   dlMsg = &(nhuDatReqSdu->sdu.ueMsg.msg.dedMsg.dlDcchMsg.m.dcchMsg);

   FILL_UINT_TKN(dlMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(dlMsg->message.choice,DL_DCCH_MSGTYP_C1);
   FILL_UINT_TKN(dlMsg->message.val.c1.choice,C1_COUNTERCHECK);

   cntrChk = &(dlMsg->message.val.c1.val.counterCheck);

   FILL_UINT_TKN(cntrChk->pres,PRSNT_NODEF);

   rrcTransIdPres = 1;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(cntrChk->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      NHAC_FILL_U8_U32_TKN(cntrChk->rrc_TrnsxnId, NOTPRSNT, NOTPRSNT);
   }
   FILL_UINT_TKN(cntrChk->criticalExtns.choice, C1_COUNTERCHECK_R8);
   FILL_UINT_TKN(cntrChk->criticalExtns.val.c1.choice, CRITICALEXTNS_C1);

   cntrChkIe = &cntrChk->criticalExtns.val.c1.val.counterCheck_r8;
   FILL_UINT_TKN(cntrChkIe->pres, PRSNT_NODEF);
   FILL_UINT_TKN(cntrChkIe->drb_CountMSB_InfoLst.noComp, 1);
   /* Allocate memory required for num components */
   CMXTA_GET_MEM(nhuDatReqSdu, sizeof(NhuDRB_CountMSB_Info)*
                 cntrChkIe->drb_CountMSB_InfoLst.noComp.val,
                 &(cntrChkIe->drb_CountMSB_InfoLst.member));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "numDrbs", &numDrb);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "drbIdStr", msgStr);
   len = 0;
   numDrbCnt = 0;
   while(len < strlen(msgStr))
   {
      CMXTA_ZERO(frstWrd, sizeof(frstWrd));
      nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      drb[numDrbCnt] = rbVal;
      numDrbCnt++;
   }
   for(i = 0; i < numDrb; i++)
   {
      FILL_UINT_TKN(cntrChkIe->drb_CountMSB_InfoLst.member[i].pres, PRSNT_NODEF);
      FILL_UINT_TKN(cntrChkIe->drb_CountMSB_InfoLst.member[i].drb_Identity, drb[i]);
      FILL_UINT_TKN(cntrChkIe->drb_CountMSB_InfoLst.member[i].countMSB_Ulnk, 10);
      FILL_UINT_TKN(cntrChkIe->drb_CountMSB_InfoLst.member[i].countMSB_Dlnk, 10);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuCounterCheckMsg */

/*
*
*       Fun:   nhAcUtlFillNhuDlCcchConReestb
*
*       Desc:  This function fills RRC Connection Re-establishment message.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuDlCcchConReestb
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatRspSdus *nhuDatRspSdu
)
#else
PUBLIC S16 nhAcUtlFillNhuDlCcchConReestb(tcCb, spCb, nhuDatRspSdu)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuDatRspSdus *nhuDatRspSdu;
#endif
{
   NhuDL_CCCH_Msg   *dlMsg;
   NhuRRCConReestb  *conReestb;
   U32              rrc_transId;
   U8               rrcTransIdPres;
   NhuRRCConReestb_r8_IEs *reestabIe = NULLP;
   U8              decdErr=FALSE;
  
   TRC2(nhAcUtlFillNhuDlCcchConReestb);

   dlMsg = &(nhuDatRspSdu->sdu.m.dlCcchMsg.ccchMsg);

   FILL_UINT_TKN(dlMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(dlMsg->message.choice,DL_CCCH_MSGTYP_C1);
   FILL_UINT_TKN(dlMsg->message.val.c1.choice,C1_RRCCONREESTB);

   conReestb = &(dlMsg->message.val.c1.val.rrcConReestb);

   FILL_UINT_TKN(conReestb->pres,PRSNT_NODEF);
   rrcTransIdPres = 0;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(conReestb->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"decode_error",
                     &decdErr);
      if(decdErr == FALSE)
      FILL_UINT_TKN(conReestb->rrc_TrnsxnId,  1);
   }
   FILL_UINT_TKN(conReestb->criticalExtns.choice, CRITICALEXTNS_C1);

   if(conReestb->criticalExtns.choice.val == 
                                          CRITICALEXTNS_C1)
   {
      FILL_UINT_TKN(conReestb->criticalExtns.val.c1.choice,
                    C1_RRCCONREESTB_R8);
      reestabIe = &conReestb->criticalExtns.val.c1.val.rrcConReestb_r8;
      FILL_UINT_TKN(reestabIe->pres, PRSNT_NODEF);
      /*-Fill Radio Resource Configuration-*/
      nhAcUtlFillNhuRadioResCfgDedi(tcCb, spCb, 
                                 &(reestabIe->radioResourceConfigDedicated),
                                 (Ptr)nhuDatRspSdu);
      FILL_UINT_TKN(reestabIe->nextHopChainingCount, 1);
      FILL_UINT_TKN(reestabIe->nonCriticalExtn.pres, 1);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuDlCcchConReestb */

/*
*
*       Fun:   nhAcUtlFillNhuDlDcchCDMACsfbPrmRsp
*
*       Desc:  This function fills CDMA CSFB Parameter Response message.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuDlDcchCDMACsfbPrmRsp
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDatRspSdus *nhuDatRspSdu
)
#else
PUBLIC S16 nhAcUtlFillNhuDlDcchCDMACsfbPrmRsp(tcCb, spCb, nhuDatRspSdu)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuDatRspSdus *nhuDatRspSdu;
#endif
{
   NhuDL_DCCH_Msg   *dlMsg;
   U32              rrc_transId;
   U8               rrcTransIdPres;
   NhuCSFBParamsRspCDMA2000  *csfbPrmRsp;
   NhuCSFBParamsRspCDMA2000_r8_IEs *csfbRspIe = NULLP;
  
   TRC2(nhAcUtlFillNhuDlDcchCDMACsfbPrmRsp);

   dlMsg = &(nhuDatRspSdu->sdu.m.dlDcchMsg.m.dcchMsg);

   FILL_UINT_TKN(dlMsg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(dlMsg->message.choice,DL_DCCH_MSGTYP_C1);
   FILL_UINT_TKN(dlMsg->message.val.c1.choice,C1_CSFBPARAMSRSPCDMA2000);

   csfbPrmRsp = &(dlMsg->message.val.c1.val.csfbParamsRspCDMA2000);

   FILL_UINT_TKN(csfbPrmRsp->pres,PRSNT_NODEF);
   rrcTransIdPres = 1;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 1;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(csfbPrmRsp->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      NHAC_FILL_U8_U32_TKN(csfbPrmRsp->criticalExtns.choice, NOTPRSNT, NOTPRSNT);
   }
   FILL_UINT_TKN(csfbPrmRsp->criticalExtns.choice, 
                 CRITICALEXTNS_CSFBPARAMSRSPCDMA2000_R8);

   csfbRspIe = &csfbPrmRsp->criticalExtns.val.csfbParamsRspCDMA2000_r8;
   FILL_UINT_TKN(csfbRspIe->pres, PRSNT_NODEF);
   FILL_BIT_STR(csfbRspIe->rand, 32, 1, nhuDatRspSdu);
   FILL_OCT_STR(csfbRspIe->mobilityParams, 4, 1, nhuDatRspSdu);

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuDlDcchCDMACsfbPrmRsp */
/*
*
*       Fun:   nhAcUtlFillNhuRrcConReCfgnHo
*
*       Desc:  This function fills RRC Reconfiguration message in case of HO.
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuRrcConReCfgnHo
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
Ptr            evnt,
NhuDL_DCCH_Msg *dcchMsg
)
#else
PUBLIC S16 nhAcUtlFillNhuRrcConReCfgnHo(tcCb, spCb, evnt, dcchMsg)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb; 
Ptr            evnt;
NhuDL_DCCH_Msg *dcchMsg;
#endif
{
   NhuRRCConRecfgn *rrcConReCfg;
   NhuRRCConRecfgn_r8_IEs *conRecfgIEs;
   U32 rrc_transId;
   U8  rrcTransIdPres;
   Bool reCfgDedInfo;
   Bool preRegAllowed;
   Bool zoneId;
   NhuMeasConfig *measCfg = NULLP;

   TRC2(nhAcUtlFillNhuRrcConReCfgnHo);

   FILL_UINT_TKN(dcchMsg->pres, PRSNT_NODEF);
   FILL_UINT_TKN(dcchMsg->message.choice, DL_DCCH_MSGTYP_C1);
   FILL_UINT_TKN(dcchMsg->message.val.c1.choice, C1_RRCCONRECFGN);
   rrcConReCfg = &(dcchMsg->message.val.c1.val.rrcConRecfgn);
   FILL_UINT_TKN(rrcConReCfg->pres, PRSNT_NODEF);

   rrcTransIdPres = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"rrcTransIdPres",
                  &rrcTransIdPres);
   if (rrcTransIdPres)
   {
      rrc_transId = 0;
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, "rrc_transId",
                  &rrc_transId);
      FILL_UINT_TKN(rrcConReCfg->rrc_TrnsxnId, rrc_transId);
   }
   else
   {
      rrcConReCfg->rrc_TrnsxnId.pres = NOTPRSNT;
   }
   FILL_UINT_TKN(rrcConReCfg->criticalExtns.choice, CRITICALEXTNS_C1);
   FILL_UINT_TKN(rrcConReCfg->criticalExtns.val.c1.choice, C1_RRCCONRECFGN_R8);

   conRecfgIEs = &(rrcConReCfg->criticalExtns.val.c1.val.rrcConRecfgn_r8);
   FILL_UINT_TKN(conRecfgIEs->pres, PRSNT_NODEF);

   /*-Fill Mobility Control Information -*/
   nhAcUtlFillNhuMobilityCntrlInfo(tcCb, spCb, &(conRecfgIEs->mobilityCntrlInfo),
                                 evnt);

   /*-Fill NAS Dedicated Information -*/
   reCfgDedInfo = FALSE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"reCfgDedInfoPres",
                  &reCfgDedInfo);
   if(reCfgDedInfo)
   {
      FILL_UINT_TKN(conRecfgIEs->dedicatedInfoNASLst.noComp, 1);
      CMXTA_GET_MEM(evnt, 
         (conRecfgIEs->dedicatedInfoNASLst.noComp.val)*(sizeof(NhuDedicatedInfoNAS)),
         &(conRecfgIEs->dedicatedInfoNASLst.member));
      FILL_OCT_STR(conRecfgIEs->dedicatedInfoNASLst.member[0], 4, 1, evnt);
   }

   /*-Fill Radio Resource Configuration-*/
   nhAcUtlFillNhuRadioResCfgDedi(tcCb, spCb, &(conRecfgIEs->radioResourceConfigDedicated),
                                 evnt);

   /*-Fill HO Security Configuration-*/
   nhAcUtlFillNhuHOSecurityCfg(tcCb, spCb, &(conRecfgIEs->securityConfigHO),
                                 evnt);
   
   zoneId = FALSE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "zoneIdPres",
                  &zoneId);
   preRegAllowed = FALSE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL, "preRegAllowed",
                  &preRegAllowed);
   if(zoneId || preRegAllowed)
   {
      measCfg = &conRecfgIEs->measConfig;
      FILL_UINT_TKN(measCfg->pres, PRSNT_NODEF);
      FILL_UINT_TKN(measCfg->preRegistrationInfoHRPD.pres, PRSNT_NODEF);
      if(preRegAllowed)
      {
         FILL_UINT_TKN(measCfg->preRegistrationInfoHRPD.preRegistrationAllowed,TRUE);
      }
      if(zoneId)
      {
         FILL_UINT_TKN(measCfg->preRegistrationInfoHRPD.preRegistrationZoneId,1);
      }
   }
   FILL_UINT_TKN(conRecfgIEs->nonCriticalExtn.pres, PRSNT_NODEF);
  
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuRrcConReCfgnHo */

/************** IE filling Related functions in UE message ************/
/*
*
*       Fun:   nhAcUtlFillNhuRadioResCfgCmnSibIE
*
*       Desc:  This function fills NHU Radio Resource Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuRadioResCfgCmnSibIE
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigCmnSIB *radioResCfgCmn,
Ptr         evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuRadioResCfgCmnSibIE(tcCb, spCb, radioResCfgCmn, evnt)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb; 
NhuRadioResourceConfigCmnSIB *radioResCfgCmn;
Ptr         evnt;
#endif
{
   TRC2(nhAcUtlFillNhuRadioResCfgCmnSibIE);

   /*-Fill Radio Resource Config Common -*/
   FILL_UINT_TKN(radioResCfgCmn->pres, PRSNT_NODEF);

#ifdef LTERRC_REL9
#define RACHCFGCMN          radioResCfgCmn->rach_ConfigCmn
#define PDSCHCFGCMN         radioResCfgCmn->pdsch_ConfigCmn
#define PUSCHCFGCMN         radioResCfgCmn->pusch_ConfigCmn
#define PUCCHCFGCMN         radioResCfgCmn->pucch_ConfigCmn
#define SOUNDINGRS_ULCFGCMN radioResCfgCmn->soundingRS_UL_ConfigCmn
#define UPLINKPWRCTRLCMN    radioResCfgCmn->uplinkPowerCntrlCmn
#else
#define RACHCFGCMN          radioResCfgCmn->rach_Config
#define PDSCHCFGCMN         radioResCfgCmn->pdsch_Config
#define PUSCHCFGCMN         radioResCfgCmn->pusch_Config
#define PUCCHCFGCMN         radioResCfgCmn->pucch_Config
#define SOUNDINGRS_ULCFGCMN radioResCfgCmn->soundingRS_UL_Config
#define UPLINKPWRCTRLCMN    radioResCfgCmn->uplinkPowerCntrl
#endif

   /* Filling RACH config */
   FILL_UINT_TKN(RACHCFGCMN.pres, PRSNT_NODEF);
   FILL_UINT_TKN(RACHCFGCMN.preambleInfo.pres, PRSNT_NODEF);
   FILL_UINT_TKN(RACHCFGCMN.preambleInfo.numberOfRA_Preambles,
              NhuRACH_ConfigCmnpreambleInfonumberOfRA_Preamblesn4Enum);
   FILL_UINT_TKN(RACHCFGCMN.powerRampingParams.pres, 1);
   FILL_UINT_TKN(RACHCFGCMN.powerRampingParams.powerRampingStep, 1);
   FILL_UINT_TKN(RACHCFGCMN.powerRampingParams.preambleInitReceivedTgtPower, 1);
   FILL_UINT_TKN(RACHCFGCMN.ra_SupervisionInfo.pres, 1);
   FILL_UINT_TKN(RACHCFGCMN.ra_SupervisionInfo.preambleTransMax, 1);
   FILL_UINT_TKN(RACHCFGCMN.ra_SupervisionInfo.ra_RspWindowSize, 1);
   FILL_UINT_TKN(RACHCFGCMN.ra_SupervisionInfo.mac_ContentionResolutionTimer, 1);
   FILL_UINT_TKN(RACHCFGCMN.maxHARQ_Msg3Tx, 1);

   /* Filling BCCH config */
   FILL_UINT_TKN(radioResCfgCmn->bcch_Config.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfgCmn->bcch_Config.modificationPeriodCoeff,0);

   /* Filling PCCH config */
   FILL_UINT_TKN(radioResCfgCmn->pcch_Config.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfgCmn->pcch_Config.defaultPagCycle, 0);
   FILL_UINT_TKN(radioResCfgCmn->pcch_Config.nB, 0);

   /* Filling PRACH config */
   FILL_UINT_TKN(radioResCfgCmn->prach_Config.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfgCmn->prach_Config.rootSequenceIdx, 100);
   FILL_UINT_TKN(radioResCfgCmn->prach_Config.prach_ConfigInfo.pres, 1);
   FILL_UINT_TKN(radioResCfgCmn->prach_Config.prach_ConfigInfo.\
                 prach_ConfigIdx, 10);
   FILL_UINT_TKN(radioResCfgCmn->prach_Config.prach_ConfigInfo.highSpeedFlag,
                 1);
   FILL_UINT_TKN(radioResCfgCmn->prach_Config.prach_ConfigInfo.\
                 zeroCorrelationZoneConfig, 1);
   FILL_UINT_TKN(radioResCfgCmn->prach_Config.prach_ConfigInfo.\
                 prach_FreqOffset, 1);

   /* Filling PDSCH config */
   FILL_UINT_TKN(PDSCHCFGCMN.pres, PRSNT_NODEF);
   FILL_UINT_TKN(PDSCHCFGCMN.referenceSignalPower, 0);
   FILL_UINT_TKN(PDSCHCFGCMN.p_b, 0);

   /* Filling PUSCH config */
   FILL_UINT_TKN(PUSCHCFGCMN.pres, PRSNT_NODEF);
   FILL_UINT_TKN(PUSCHCFGCMN.pusch_ConfigBasic.pres, PRSNT_NODEF);
   FILL_UINT_TKN(PUSCHCFGCMN.pusch_ConfigBasic.n_SB,1);
   FILL_UINT_TKN(PUSCHCFGCMN.pusch_ConfigBasic.hoppingMode, 0);
   FILL_UINT_TKN(PUSCHCFGCMN.pusch_ConfigBasic.pusch_HoppingOffset, 0);
   FILL_UINT_TKN(PUSCHCFGCMN.pusch_ConfigBasic.enable64QAM, 0);
   FILL_UINT_TKN(PUSCHCFGCMN.ul_ReferenceSignalsPUSCH.pres, PRSNT_NODEF);
   FILL_UINT_TKN(PUSCHCFGCMN.ul_ReferenceSignalsPUSCH.groupHoppingEnabled, 0);
   FILL_UINT_TKN(PUSCHCFGCMN.ul_ReferenceSignalsPUSCH.groupAssignmentPUSCH, 1);
   FILL_UINT_TKN(PUSCHCFGCMN.ul_ReferenceSignalsPUSCH.sequenceHoppingEnabled, 0);
   FILL_UINT_TKN(PUSCHCFGCMN.ul_ReferenceSignalsPUSCH.cyclicShift, 0);

   /* Filling PUCCH config */
   FILL_UINT_TKN(PUCCHCFGCMN.pres, PRSNT_NODEF);
   FILL_UINT_TKN(PUCCHCFGCMN.deltaPUCCH_Shift, 0);
   FILL_UINT_TKN(PUCCHCFGCMN.nRB_CQI, 0);
   FILL_UINT_TKN(PUCCHCFGCMN.nCS_AN, 1);
   FILL_UINT_TKN(PUCCHCFGCMN.n1PUCCH_AN, 0);

   /* Filling SRS UL config */
   FILL_UINT_TKN(SOUNDINGRS_ULCFGCMN.choice, 0);
   switch(SOUNDINGRS_ULCFGCMN.choice.val)
   {
      case 0:
            FILL_UINT_TKN(SOUNDINGRS_ULCFGCMN.val.setup.\
                     srs_BandwidthConfig, 0);
      break;
      case 1:
            FILL_UINT_TKN(SOUNDINGRS_ULCFGCMN.val.setup.\
                     srs_SubfrmConfig, 0);
      break;
      case 2:
            FILL_UINT_TKN(SOUNDINGRS_ULCFGCMN.val.setup.\
                     ackNackSRS_SimultaneousTransmission, 0);
      break;
      case 3:
            FILL_UINT_TKN(SOUNDINGRS_ULCFGCMN.val.setup.\
                     srs_MaxUpPts, 0);
      break;
   }

   /* Filling UL power control config */
   FILL_UINT_TKN(UPLINKPWRCTRLCMN.pres, PRSNT_NODEF);
   FILL_UINT_TKN(UPLINKPWRCTRLCMN.p0_NominalPUSCH, PRSNT_NODEF);
   FILL_UINT_TKN(UPLINKPWRCTRLCMN.alpha, NhuUlnkPowerCntrlCmnalphaal0Enum);
   FILL_UINT_TKN(UPLINKPWRCTRLCMN.p0_NominalPUCCH, -100);
   FILL_UINT_TKN(UPLINKPWRCTRLCMN.deltaFLst_PUCCH.pres, 1);
   FILL_UINT_TKN(UPLINKPWRCTRLCMN.deltaFLst_PUCCH.deltaF_PUCCH_Format1, 1);
   FILL_UINT_TKN(UPLINKPWRCTRLCMN.deltaFLst_PUCCH.deltaF_PUCCH_Format1b, 1);
   FILL_UINT_TKN(UPLINKPWRCTRLCMN.deltaFLst_PUCCH.deltaF_PUCCH_Format2, 1);
   FILL_UINT_TKN(UPLINKPWRCTRLCMN.deltaFLst_PUCCH.deltaF_PUCCH_Format2a, 1);
   FILL_UINT_TKN(UPLINKPWRCTRLCMN.deltaFLst_PUCCH.deltaF_PUCCH_Format2b, 1);
   FILL_UINT_TKN(UPLINKPWRCTRLCMN.deltaPreambleMsg3, 1);

#undef RACHCFGCMN
#undef PDSCHCFGCMN
#undef PUSCHCFGCMN
#undef PUCCHCFGCMN
#undef SOUNDINGRS_ULCFGCMN
#undef UPLINKPWRCTRLCMN

   /* Filling UL cyclic prefix length */
   FILL_UINT_TKN(radioResCfgCmn->ul_CyclicPrefixLength,0);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcUtlFillNhuRadioResCfgCmnSibIE */
/*
*
*       Fun:   nhAcUtlFillNhuUECapIE
*
*       Desc:  This function fills NHU Radio Resource Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuUECapIE
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
Ptr         evnt,
NhuUE_EUTRA_Cap *ueEutraCap
)
#else
PUBLIC S16 nhAcUtlFillNhuUECapIE(tcCb, spCb, evnt, ueEutraCap)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
Ptr         evnt;
NhuUE_EUTRA_Cap *ueEutraCap;
#endif
{
#ifdef RRC_REL11
   U8       idx=0, idx1=0, idx2=0;
   U32      ueCategory=6;
/* As bandEUTRA-range is modified in nh_db.c file, 
   encoding will fail if we give out of range value for 
   bandEUTRA */
   U8       bandEUTRA=1;
   U8       interFreqNeedForGap=1;
   U8       interRATNeedForGaps=1; 
#endif
   TRC2(nhAcUtlFillNhuUECapIE);
 
   FILL_UINT_TKN(ueEutraCap->pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->accessStratumRls, NhuAccessStratumRlsrel8Enum);
   FILL_UINT_TKN(ueEutraCap->ue_Category, 1);
   /* Fill PDCP params */
   FILL_UINT_TKN(ueEutraCap->pdcp_Params.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0001, TRUE);
   FILL_UINT_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0002, FALSE);
   FILL_UINT_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0003, FALSE);
   FILL_UINT_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0004, FALSE);
   FILL_UINT_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0006, FALSE);
   FILL_UINT_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0101, FALSE);
   FILL_UINT_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0102, FALSE);
   FILL_UINT_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0103, FALSE);
   FILL_UINT_TKN(ueEutraCap->pdcp_Params.supportedROHC_Profiles.profile0x0104, FALSE);
   FILL_UINT_TKN(ueEutraCap->pdcp_Params.maxNumberROHC_CtxtSessions, 
                 NhuPDCP_ParamsmaxNumberROHC_CtxtSessionscs2Enum);

   /* Fill Phy layer params */
   FILL_UINT_TKN(ueEutraCap->phyLyrParams.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->phyLyrParams.ue_TxAntennaSelectionSupp, TRUE);
   FILL_UINT_TKN(ueEutraCap->phyLyrParams.ue_SpecificRefSigsSupp, TRUE);

   /* Fill RF params */
   FILL_UINT_TKN(ueEutraCap->rf_Params.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->rf_Params.supportedBandLstEUTRA.noComp, 1);
   CMXTA_GET_MEM(evnt, 
         (ueEutraCap->rf_Params.supportedBandLstEUTRA.noComp.val)*(sizeof(NhuSuppBandEUTRA)),
         &(ueEutraCap->rf_Params.supportedBandLstEUTRA.member));
   FILL_UINT_TKN(ueEutraCap->rf_Params.supportedBandLstEUTRA.member[0].pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->rf_Params.supportedBandLstEUTRA.member[0].\
                 bandEUTRA, 1);
   FILL_UINT_TKN(ueEutraCap->rf_Params.supportedBandLstEUTRA.member[0].\
                 halfDuplex, FALSE);

   /* Fill measurement params */
   FILL_UINT_TKN(ueEutraCap->measParams.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->measParams.bandLstEUTRA.noComp, 1);
   CMXTA_GET_MEM(evnt, 
         (ueEutraCap->measParams.bandLstEUTRA.noComp.val)*(sizeof(NhuBandInfoEUTRA)),
         &(ueEutraCap->measParams.bandLstEUTRA.member));
   FILL_UINT_TKN(ueEutraCap->measParams.bandLstEUTRA.member[0].pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->measParams.bandLstEUTRA.member[0].interFreqBandLst.noComp, 1);
   CMXTA_GET_MEM(evnt, 
         (ueEutraCap->measParams.bandLstEUTRA.member[0].interFreqBandLst.noComp.val)\
         *(sizeof(NhuInterFreqBandInfo)),
         &(ueEutraCap->measParams.bandLstEUTRA.member[0].interFreqBandLst.member));
   FILL_UINT_TKN(ueEutraCap->measParams.bandLstEUTRA.member[0].interFreqBandLst.\
                 member[0].pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->measParams.bandLstEUTRA.member[0].interFreqBandLst.\
                 member[0].interFreqNeedForGaps, TRUE);
   FILL_UINT_TKN(ueEutraCap->interRAT_Params.pres, PRSNT_NODEF);

#ifdef LTERRC_REL9
   /*R9 upgrade: filling the R9 IeS*/
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.phyLyrParams_v920.pres, PRSNT_NODEF);
   
   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.phyLyrParams_v920.enhancedDualLyrFDD_r9,\
         PRSNT_NODEF, NhuPhyLyrParams_v920enhancedDualLyrFDD_r9supportedEnum);
         
   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.phyLyrParams_v920.enhancedDualLyrTDD_r9,\
         PRSNT_NODEF, NhuPhyLyrParams_v920enhancedDualLyrTDD_r9supportedEnum);

   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.interRAT_ParamsGERAN_v920.pres, PRSNT_NODEF);
   
   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.interRAT_ParamsGERAN_v920.dtm_r9,\
         PRSNT_NODEF, NhuIRAT_ParamsGERAN_v920dtm_r9supportedEnum);
         
   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.interRAT_ParamsGERAN_v920.\
         e_RedirectionGERAN_r9, PRSNT_NODEF, NhuIRAT_ParamsGERAN_v920e_RedirectionGERAN_r9supportedEnum);

   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.interRAT_ParamsUTRA_v920.pres, PRSNT_NODEF);
   
   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.interRAT_ParamsUTRA_v920.\
         e_RedirectionUTRA_r9, PRSNT_NODEF, NhuIRAT_ParamsUTRA_v920e_RedirectionUTRA_r9supportedEnum);

   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.interRAT_ParamsCDMA2000_v920.pres,\
         PRSNT_NODEF);
         
   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.interRAT_ParamsCDMA2000_v920.\
         e_CSFB_1XRTT_r9, PRSNT_NODEF, NhuIRAT_ParamsCDMA2000_1XRTT_v920e_CSFB_1XRTT_r9supportedEnum);
         
   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.interRAT_ParamsCDMA2000_v920.\
         e_CSFB_ConcPS_Mob1XRTT_r9, PRSNT_NODEF, NhuIRAT_ParamsCDMA2000_1XRTT_v920e_CSFB_ConcPS_Mob1XRTT_r9supportedEnum);
         
   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.deviceTyp_r9, PRSNT_NODEF,\
         NhuUE_EUTRA_Cap_v920_IEsdeviceTyp_r9noBenFromBatConsumpOptEnum);

   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.csg_ProximityIndParams_r9.pres,\
         PRSNT_NODEF);
         
   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.csg_ProximityIndParams_r9.\
         intraFreqProximityInd_r9, PRSNT_NODEF, NhuCSG_ProximityIndParams_r9intraFreqProximityInd_r9supportedEnum);

   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.csg_ProximityIndParams_r9.\
         interFreqProximityInd_r9, PRSNT_NODEF, NhuCSG_ProximityIndParams_r9interFreqProximityInd_r9supportedEnum);

   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.csg_ProximityIndParams_r9.\
         utran_ProximityInd_r9, PRSNT_NODEF, NhuCSG_ProximityIndParams_r9utran_ProximityInd_r9supportedEnum);

   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.neighCellSI_AcquisitionParams_r9.pres,\
         PRSNT_NODEF);
         
   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.neighCellSI_AcquisitionParams_r9.\
         intraFreqSI_AcquisitionForHO_r9, PRSNT_NODEF, \
         NhuNeighCellSI_AcquisitionParams_r9intraFreqSI_AcquisitionForHO_r9supportedEnum);
         
   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.neighCellSI_AcquisitionParams_r9.\
         interFreqSI_AcquisitionForHO_r9, PRSNT_NODEF,\
         NhuNeighCellSI_AcquisitionParams_r9interFreqSI_AcquisitionForHO_r9supportedEnum);
         
   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.neighCellSI_AcquisitionParams_r9.\
         utran_SI_AcquisitionForHO_r9, PRSNT_NODEF,\
         NhuNeighCellSI_AcquisitionParams_r9utran_SI_AcquisitionForHO_r9supportedEnum);

   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.son_Params_r9.pres,\
         PRSNT_NODEF);

   NHAC_FILL_U8_U32_TKN(ueEutraCap->nonCriticalExtn.son_Params_r9.rach_Report_r9,\
         PRSNT_NODEF, NhuSON_Params_r9rach_Report_r9supportedEnum);

   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.pres,\
         PRSNT_NODEF);
   FILL_OCT_STR(ueEutraCap->nonCriticalExtn.nonCriticalExtn.lateNonCriticalExtn,\
         4, 1, (NhuDatReqSdus *)evnt);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.pres,\
         PRSNT_NODEF);
#ifdef RRC_REL11
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"ueCategory", &ueCategory);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.ue_Category_v1020,\
         ueCategory);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.\
         twoAntennaPortsForPUCCH_r10, NhuPhyLyrParams_v1020twoAntennaPortsForPUCCH_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.\
         tm9_With_8Tx_FDD_r10, NhuPhyLyrParams_v1020tm9_With_8Tx_FDD_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.\
         pmi_Disabling_r10, NhuPhyLyrParams_v1020pmi_Disabling_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.\
         crossCarrierScheduling_r10, NhuPhyLyrParams_v1020crossCarrierScheduling_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.\
         simultaneousPUCCH_PUSCH_r10, NhuPhyLyrParams_v1020simultaneousPUCCH_PUSCH_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.\
         multiClusterPUSCH_WithinCC_r10, NhuPhyLyrParams_v1020multiClusterPUSCH_WithinCC_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.\
         nonContiguousUL_RA_WithinCC_Lst_r10.noComp,1);
   CMXTA_GET_MEM(evnt,(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.\
         nonContiguousUL_RA_WithinCC_Lst_r10.noComp.val)*(sizeof(NhuNonContiguousUL_RA_WithinCC_r10)),\
         &(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.\
                     nonContiguousUL_RA_WithinCC_Lst_r10.member));
   for(idx=0; idx<ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.\
                  nonContiguousUL_RA_WithinCC_Lst_r10.noComp.val; idx++)
   {
     FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.\
         nonContiguousUL_RA_WithinCC_Lst_r10.member[idx].pres, PRSNT_NODEF);
     FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.phyLyrParams_v1020.\
         nonContiguousUL_RA_WithinCC_Lst_r10.member[idx].nonContiguousUL_RA_WithinCC_Info_r10,\
         NhuNonContiguousUL_RA_WithinCC_r10nonContiguousUL_RA_WithinCC_Info_r10supportedEnum);
   }
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
         supportedBandCombination_r10.noComp, 1);
   CMXTA_GET_MEM(evnt,(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
         supportedBandCombination_r10.noComp.val)*(sizeof(NhuBandCombinationParams_r10)),\
         &(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
                     supportedBandCombination_r10.member));
   for(idx=0;idx<ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
         supportedBandCombination_r10.noComp.val; idx++)
   {
     FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
         supportedBandCombination_r10.member[idx].noComp, 1);
     CMXTA_GET_MEM(evnt,(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
         supportedBandCombination_r10.member[idx].noComp.val)*(sizeof(NhuBandParams_r10)),\
         &(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
                       supportedBandCombination_r10.member[idx].member));
     for(idx1=0;idx1<ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
           supportedBandCombination_r10.member[idx].noComp.val; idx++)
     {
       FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
            supportedBandCombination_r10.member[idx].member[idx1].pres, PRSNT_NODEF);
       cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"bandEUTRA", &bandEUTRA);
       FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
           supportedBandCombination_r10.member[idx].member[idx1].bandEUTRA_r10, bandEUTRA);
       FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
           supportedBandCombination_r10.member[idx].member[idx1].bandParamsUL_r10.noComp, 1);
       CMXTA_GET_MEM(evnt,(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
           supportedBandCombination_r10.member[idx].member[idx1].bandParamsUL_r10.noComp.val)*
           (sizeof(NhuCA_MIMO_ParamsUL_r10)),&(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
           rf_Params_v1020.supportedBandCombination_r10.member[idx].member[idx1].bandParamsUL_r10.member));
       for(idx2=0;idx2<ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
           supportedBandCombination_r10.member[idx].member[idx1].bandParamsUL_r10.noComp.val; idx2++)
       {
         FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         rf_Params_v1020.supportedBandCombination_r10.member[idx].member[idx1].bandParamsUL_r10.\
          member[idx2].pres, PRSNT_NODEF);
         FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         rf_Params_v1020.supportedBandCombination_r10.member[idx].member[idx1].bandParamsUL_r10.\
          member[idx2].ca_BandwidthClassUL_r10, NhuCA_BandwidthClass_r10aEnum);
         FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         rf_Params_v1020.supportedBandCombination_r10.member[idx].member[idx1].bandParamsUL_r10.\
          member[idx2].supportedMIMO_CapUL_r10, NhuMIMO_CapUL_r10twoLyrsEnum);
       }
       FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         rf_Params_v1020.supportedBandCombination_r10.member[idx].member[idx1].bandParamsDL_r10.\
         noComp, 1);
       CMXTA_GET_MEM(evnt,(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
           supportedBandCombination_r10.member[idx].member[idx1].bandParamsDL_r10.noComp.val)*
           (sizeof(NhuCA_MIMO_ParamsDL_r10)),&(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
           rf_Params_v1020.supportedBandCombination_r10.member[idx].member[idx1].bandParamsDL_r10.member));
       for(idx2=0; idx2<ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
            rf_Params_v1020.supportedBandCombination_r10.member[idx].member[idx1].bandParamsDL_r10.\
            noComp.val; idx2++)
       {
         FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         rf_Params_v1020.supportedBandCombination_r10.member[idx].member[idx1].bandParamsDL_r10.\
          member[idx2].pres, PRSNT_NODEF);
         FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         rf_Params_v1020.supportedBandCombination_r10.member[idx].member[idx1].bandParamsDL_r10.\
          member[idx2].ca_BandwidthClassDL_r10, NhuCA_BandwidthClass_r10aEnum);
         FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.rf_Params_v1020.\
          supportedBandCombination_r10.member[idx].member[idx1].bandParamsDL_r10.\
          member[idx2].supportedMIMO_CapDL_r10, NhuMIMO_CapDL_r10twoLyrsEnum);
       }
     }
   }
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
         bandCombinationLstEUTRA_r10.noComp, 1);
   CMXTA_GET_MEM(evnt,(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
         bandCombinationLstEUTRA_r10.noComp.val)*(sizeof(NhuBandInfoEUTRA)),\
         &(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
                     bandCombinationLstEUTRA_r10.member));
   for(idx=0;idx<ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
         bandCombinationLstEUTRA_r10.noComp.val;idx++)
   {
     FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
           bandCombinationLstEUTRA_r10.member[idx].pres, PRSNT_NODEF);
     FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
           bandCombinationLstEUTRA_r10.member[idx].interFreqBandLst.noComp, 1);
     CMXTA_GET_MEM(evnt,(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
           bandCombinationLstEUTRA_r10.member[idx].interFreqBandLst.noComp.val)*(sizeof(NhuInterFreqBandInfo)),\
           &(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
                         bandCombinationLstEUTRA_r10.member[idx].interFreqBandLst.member));
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"interFreqNeedForGaps", &interFreqNeedForGap);
     for(idx1=0;idx1<ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
           bandCombinationLstEUTRA_r10.member[idx].interFreqBandLst.noComp.val;idx1++)
     {
       FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
             bandCombinationLstEUTRA_r10.member[idx].interFreqBandLst.member[idx1].pres, PRSNT_NODEF);
       FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
             bandCombinationLstEUTRA_r10.member[idx].interFreqBandLst.member[idx1].interFreqNeedForGaps,\
             interFreqNeedForGap);
     }
     FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         measParams_v1020.bandCombinationLstEUTRA_r10.member[idx].interRAT_BandLst.noComp, 1);
     CMXTA_GET_MEM(evnt,(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         measParams_v1020.bandCombinationLstEUTRA_r10.member[idx].interRAT_BandLst.noComp.val)*
         (sizeof(NhuInterRAT_BandInfo)),&(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         measParams_v1020.bandCombinationLstEUTRA_r10.member[idx].interRAT_BandLst.member));
     cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"interRATNeedForGaps", &interRATNeedForGaps);
     for(idx1=0;idx1<ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
           bandCombinationLstEUTRA_r10.member[idx].interRAT_BandLst.noComp.val;idx1++)
     {
       FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
             bandCombinationLstEUTRA_r10.member[idx].interRAT_BandLst.member[idx1].pres, PRSNT_NODEF);
       FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.measParams_v1020.\
             bandCombinationLstEUTRA_r10.member[idx].interRAT_BandLst.member[idx1].interRAT_NeedForGaps,\
             interRATNeedForGaps);
     }
   }
   FILL_BIT_STR(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.featureGroupIndRel10_r10,\
         32, 1, evnt);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.interRAT_ParamsCDMA2000_v1020.\
         pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.interRAT_ParamsCDMA2000_v1020.\
         e_CSFB_dual_1XRTT_r10, NhuIRAT_ParamsCDMA2000_1XRTT_v1020e_CSFB_dual_1XRTT_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.ue_BasedNetwPerfMeasParams_r10.\
         pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.ue_BasedNetwPerfMeasParams_r10.\
         loggedMeasurementsIdle_r10, NhuUE_BasedNetwPerfMeasParams_r10loggedMeasurementsIdle_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.ue_BasedNetwPerfMeasParams_r10.\
         standaloneGNSS_Loc_r10, NhuUE_BasedNetwPerfMeasParams_r10standaloneGNSS_Loc_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.interRAT_ParamsUTRA_TDD_v1020.\
         pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.interRAT_ParamsUTRA_TDD_v1020.\
         e_RedirectionUTRA_TDD_r10, NhuIRAT_ParamsUTRA_TDD_v1020e_RedirectionUTRA_TDD_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.twoAntennaPortsForPUCCH_r10,\
         NhuPhyLyrParams_v1020twoAntennaPortsForPUCCH_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.tm9_With_8Tx_FDD_r10,\
         NhuPhyLyrParams_v1020tm9_With_8Tx_FDD_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.pmi_Disabling_r10,\
         NhuPhyLyrParams_v1020pmi_Disabling_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.crossCarrierScheduling_r10,\
         NhuPhyLyrParams_v1020crossCarrierScheduling_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.simultaneousPUCCH_PUSCH_r10,\
         NhuPhyLyrParams_v1020simultaneousPUCCH_PUSCH_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.multiClusterPUSCH_WithinCC_r10,\
         NhuPhyLyrParams_v1020multiClusterPUSCH_WithinCC_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.nonContiguousUL_RA_WithinCC_Lst_r10.\
         noComp, 1);
   CMXTA_GET_MEM(evnt,(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.nonContiguousUL_RA_WithinCC_Lst_r10.noComp.val)*
         (sizeof(NhuNonContiguousUL_RA_WithinCC_r10)),&(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         nonCriticalExtn.fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.nonContiguousUL_RA_WithinCC_Lst_r10.member));
   for(idx=0;idx<ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.nonContiguousUL_RA_WithinCC_Lst_r10.noComp.val; idx++)
   {
     FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.nonContiguousUL_RA_WithinCC_Lst_r10.member[idx].\
         pres, PRSNT_NODEF);
     FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         fdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.nonContiguousUL_RA_WithinCC_Lst_r10.member[idx].\
         nonContiguousUL_RA_WithinCC_Info_r10,\
         NhuNonContiguousUL_RA_WithinCC_r10nonContiguousUL_RA_WithinCC_Info_r10supportedEnum);
   }
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.twoAntennaPortsForPUCCH_r10,\
         NhuPhyLyrParams_v1020twoAntennaPortsForPUCCH_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.tm9_With_8Tx_FDD_r10,\
         NhuPhyLyrParams_v1020tm9_With_8Tx_FDD_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.pmi_Disabling_r10,\
         NhuPhyLyrParams_v1020pmi_Disabling_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.crossCarrierScheduling_r10,\
         NhuPhyLyrParams_v1020crossCarrierScheduling_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.simultaneousPUCCH_PUSCH_r10,\
         NhuPhyLyrParams_v1020simultaneousPUCCH_PUSCH_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.multiClusterPUSCH_WithinCC_r10,\
         NhuPhyLyrParams_v1020multiClusterPUSCH_WithinCC_r10supportedEnum);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.nonContiguousUL_RA_WithinCC_Lst_r10.\
         noComp, 1);
   CMXTA_GET_MEM(evnt,(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.nonContiguousUL_RA_WithinCC_Lst_r10.noComp.val)*\
         (sizeof(NhuNonContiguousUL_RA_WithinCC_r10)),&(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         nonCriticalExtn.tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.nonContiguousUL_RA_WithinCC_Lst_r10.member));
   for(idx=0;idx<ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.nonContiguousUL_RA_WithinCC_Lst_r10.noComp.\
         val; idx++)
   {
     FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.nonContiguousUL_RA_WithinCC_Lst_r10.member[idx].\
         pres, PRSNT_NODEF);
     FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         tdd_Add_UE_EUTRA_Capabilities_v1060.phyLyrParams_v1060.nonContiguousUL_RA_WithinCC_Lst_r10.member[idx].\
         nonContiguousUL_RA_WithinCC_Info_r10,\
         NhuNonContiguousUL_RA_WithinCC_r10nonContiguousUL_RA_WithinCC_Info_r10supportedEnum);
   }
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         rf_Params_v1060.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         rf_Params_v1060.supportedBandCombinationExt_r10.noComp, 1);
   CMXTA_GET_MEM(evnt,(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         rf_Params_v1060.supportedBandCombinationExt_r10.noComp.val)*(sizeof(NhuBandCombinationParamsExt_r10)),\
         &(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
                     rf_Params_v1060.supportedBandCombinationExt_r10.member));
   for(idx=0;idx<ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         rf_Params_v1060.supportedBandCombinationExt_r10.noComp.val; idx++)
   {
     FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         rf_Params_v1060.supportedBandCombinationExt_r10.member[idx].pres, PRSNT_NODEF);
     FILL_BIT_STR(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         rf_Params_v1060.supportedBandCombinationExt_r10.member[idx].supportedBandwidthCombinationSet_r10,\
         1, 1, evnt);
   }
   FILL_UINT_TKN(ueEutraCap->nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.nonCriticalExtn.\
         nonCriticalExtn.pres, PRSNT_NODEF);


#endif
#endif /*LTERRC_REL9*/

   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcUtlFillNhuUECapIE */
/*
*
*       Fun:   nhAcUtlFillNhuMobilityCntrlInfo
*
*       Desc:  This function fills NHU Radio Resource Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuMobilityCntrlInfo
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuMobilityCntrlInfo *mobCntrlInfo,
Ptr         evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuMobilityCntrlInfo(tcCb, spCb, mobCntrlInfo, evnt)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb; 
NhuMobilityCntrlInfo *mobCntrlInfo;
Ptr         evnt;
#endif
{
   NhuPUSCH_ConfigCmn *puschCfgCmn = NULLP;
   Bool               tdd;
   Bool               crFreq;
   NhuCarrierFreqEUTRA *carFreq = NULLP;

   TRC2(nhAcUtlFillNhuMobilityCntrlInfo);

   FILL_UINT_TKN(mobCntrlInfo->pres, PRSNT_NODEF);
   FILL_UINT_TKN(mobCntrlInfo->targetPhysCellId, 1);
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"tgtPhyCellId",
                  &mobCntrlInfo->targetPhysCellId.val);
   FILL_UINT_TKN(mobCntrlInfo->t304, NhuMobilityCntrlInfot304ms50Enum);
   FILL_BIT_STR(mobCntrlInfo->newUE_Identity, 16, 1, evnt);

   FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.pres, PRSNT_NODEF);

   /* Fill PRACH configuration */
   FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.prach_Config.pres, PRSNT_NODEF);
   FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.prach_Config.rootSequenceIdx, 10);

   /* Fill PUSCH configuration */
   puschCfgCmn = &mobCntrlInfo->radioResourceConfigCmn.pusch_ConfigCmn;
   FILL_UINT_TKN(puschCfgCmn->pres, PRSNT_NODEF);
   FILL_UINT_TKN(puschCfgCmn->pusch_ConfigBasic.pres, PRSNT_NODEF);
   FILL_UINT_TKN(puschCfgCmn->pusch_ConfigBasic.n_SB, 2);
   FILL_UINT_TKN(puschCfgCmn->pusch_ConfigBasic.hoppingMode, 
                 NhuPUSCH_ConfigCmnpusch_ConfigBasichoppingModeinterSubFrameEnum);
   FILL_UINT_TKN(puschCfgCmn->pusch_ConfigBasic.pusch_HoppingOffset, 6);
   FILL_UINT_TKN(puschCfgCmn->pusch_ConfigBasic.enable64QAM, FALSE);
   FILL_UINT_TKN(puschCfgCmn->ul_ReferenceSignalsPUSCH.pres, PRSNT_NODEF);
   FILL_UINT_TKN(puschCfgCmn->ul_ReferenceSignalsPUSCH.groupHoppingEnabled, FALSE);
   FILL_UINT_TKN(puschCfgCmn->ul_ReferenceSignalsPUSCH.groupAssignmentPUSCH, 5);
   FILL_UINT_TKN(puschCfgCmn->ul_ReferenceSignalsPUSCH.sequenceHoppingEnabled, FALSE);
   FILL_UINT_TKN(puschCfgCmn->ul_ReferenceSignalsPUSCH.cyclicShift, 1);
   
   /* Filling Carrier frequency */
   crFreq = TRUE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"ulCarrierFreqPres",
                  &crFreq);
   if(crFreq)
   {
      carFreq = &mobCntrlInfo->carrierFreq;
      FILL_UINT_TKN(carFreq->pres, PRSNT_NODEF);
      FILL_UINT_TKN(carFreq->dl_CarrierFreq, 1);
      FILL_UINT_TKN(carFreq->ul_CarrierFreq, 1);
   }

   /* Fill TDD Config */
   tdd = FALSE;
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"tddPres",
                  &tdd);
   if(tdd)
   {   
      FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.\
                    soundingRS_UL_ConfigCmn.choice, 
                    SOUNDINGRS_UL_CONFIGCMN_SETUP);
      FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.\
                    soundingRS_UL_ConfigCmn.val.setup.pres, PRSNT_NODEF);
      FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.\
                    soundingRS_UL_ConfigCmn.val.setup.srs_BandwidthConfig,
                NhuSoundingRS_UL_ConfigCmnsetupsrs_BandwidthConfigbw0Enum);
      FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.\
                    soundingRS_UL_ConfigCmn.val.setup.srs_SubfrmConfig,
                NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc0Enum);
      FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.\
           soundingRS_UL_ConfigCmn.val.setup.ackNackSRS_SimultaneousTransmission,
                NhuSoundingRS_UL_ConfigCmnsetupsrs_SubfrmConfigsc0Enum);
      FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.\
                    soundingRS_UL_ConfigCmn.val.setup.srs_MaxUpPts,
                NhuSoundingRS_UL_ConfigCmnsetupsrs_MaxUpPtstrueEnum);
   }

   FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.ul_CyclicPrefixLength, 
                 NhuUL_CyclicPrefixLengthlen1Enum);
#ifdef RRC_REL11
   FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.extaddgrp_1.pres, 
                 PRSNT_NODEF);
   FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.extaddgrp_1.uplinkPowerCntrlCmn_v1020.\
         pres, PRSNT_NODEF);
   FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.extaddgrp_1.uplinkPowerCntrlCmn_v1020.\
         deltaF_PUCCH_Format3_r10, NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format3_r10deltaF_1Enum);
   FILL_UINT_TKN(mobCntrlInfo->radioResourceConfigCmn.extaddgrp_1.uplinkPowerCntrlCmn_v1020.\
         deltaF_PUCCH_Format1bCS_r10, NhuUlnkPowerCntrlCmn_v1020deltaF_PUCCH_Format1bCS_r10deltaF1Enum);
#endif
   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcUtlFillNhuMobilityCntrlInfo */
/*
*
*       Fun:   nhAcUtlFillNhuHOSecurityCfg
*
*       Desc:  This function fills NHU Radio Resource Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuHOSecurityCfg
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuSecConfigHO *secCfgHo,
Ptr         evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuHOSecurityCfg(tcCb, spCb, secCfgHo, evnt)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb; 
NhuSecConfigHO *secCfgHo;
Ptr         evnt;
#endif
{
   Bool secCfgPres = TRUE;
   TRC2(nhAcUtlFillNhuHOSecurityCfg);

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_BOOL,"secHoPres",
                  &secCfgPres);

   if(TRUE == secCfgPres)
   {
      FILL_UINT_TKN(secCfgHo->pres, PRSNT_NODEF);
      FILL_UINT_TKN(secCfgHo->handoverTyp.choice, HANDOVERTYP_INTRALTE);
      FILL_UINT_TKN(secCfgHo->handoverTyp.val.intraLTE.pres, PRSNT_NODEF);
      FILL_UINT_TKN(secCfgHo->handoverTyp.val.intraLTE.keyChangeIndicator, 1);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"keyChanInd",
                  &secCfgHo->handoverTyp.val.intraLTE.keyChangeIndicator.val);
      FILL_UINT_TKN(secCfgHo->handoverTyp.val.intraLTE.nextHopChainingCount, 3);
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32,"nextHopCnt",
                  &secCfgHo->handoverTyp.val.intraLTE.nextHopChainingCount.val);
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcUtlFillNhuHOSecurityCfg */

/*
*
*       Fun:   nhAcUtlFillNhuRadioResCfgDedi
*
*       Desc:  This function fills NHU Radio Resource Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuRadioResCfgDedi
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuRadioResCfgDedi(tcCb, spCb, radioResCfg, evnt)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb; 
NhuRadioResourceConfigDedicated *radioResCfg;
Ptr         evnt;
#endif
{
   TRC2(nhAcUtlFillNhuRadioResCfgDedi);

   FILL_UINT_TKN(radioResCfg->pres, PRSNT_NODEF);

   /* SRB Configuration */
   nhAcUtlFillNhuSRBAddModLst(tcCb, spCb, radioResCfg, evnt);

   /* DRB Configuration - ADD/MODIFY */
   nhAcUtlFillNhuDRBAddModLst(tcCb, spCb, radioResCfg, evnt);

   /* DRB Release */
   nhAcUtlFillNhuDRBRlsLst(tcCb, spCb, radioResCfg, evnt);

#ifdef LTERRC_REL9
/* MAC main Config*/
   nhAcUtlFillNhuMACMainCfg(tcCb, spCb, radioResCfg, evnt);
#endif /*LTERRC_REL9*/

   /* SPS Config */
   nhAcUtlFillNhuSpsCfg(tcCb, spCb, radioResCfg, evnt);

   /* Transport Channel Configuration */
   /*nhAcUtlFillNhuRRCDediTrChCfg(tcCb, spCb, radioResCfg, evnt);*/

   /* Physical Channel Configuration */
   nhAcUtlFillNhuRRCPhyCfgDedi(tcCb, spCb, radioResCfg, evnt);
   
#ifdef LTERRC_REL9
     /*R9 upgrade: 
      *Step 1. Fill extaddgrp_1*/
     /*Step 1.1. Fill pres*/
     /*TODO:MP: Filling is corrected*/
#ifndef RRC_REL11
      NHAC_FILL_U8_U32_TKN(radioResCfg->extaddgrp_r9.pres, TRUE, PRSNT_NODEF); 
     /*Step 1.2. Fill rlf_TmrsAndConsts_r9*/
     /*Step 1.2.1. Fill rlf_TmrsAndConsts_r9i.rlf_TmrsAndConsts_r9.choice*/
     FILL_UINT_TKN(radioResCfg->extaddgrp_r9.rlf_TmrsAndConsts_r9.choice,0);

     /*Step 1.2.2. Fill rlf_TmrsAndConsts_r9i.rlf_TmrsAndConsts_r9.setup.present*/
     FILL_UINT_TKN(radioResCfg->extaddgrp_r9.rlf_TmrsAndConsts_r9.val.setup.pres,PRSNT_NODEF);

     FILL_UINT_TKN(radioResCfg->extaddgrp_r9.rlf_TmrsAndConsts_r9.val.setup.t301_r9,0);
     FILL_UINT_TKN(radioResCfg->extaddgrp_r9.rlf_TmrsAndConsts_r9.val.setup.t310_r9,0);
     FILL_UINT_TKN(radioResCfg->extaddgrp_r9.rlf_TmrsAndConsts_r9.val.setup.n310_r9,0);
     FILL_UINT_TKN(radioResCfg->extaddgrp_r9.rlf_TmrsAndConsts_r9.val.setup.t311_r9,0);
     FILL_UINT_TKN(radioResCfg->extaddgrp_r9.rlf_TmrsAndConsts_r9.val.setup.n311_r9,0);
#else
     NHAC_FILL_U8_U32_TKN(radioResCfg->extaddgrp_1.pres, TRUE, PRSNT_NODEF); 
     /*Step 1.2. Fill rlf_TmrsAndConsts_r9*/
     /*Step 1.2.1. Fill rlf_TmrsAndConsts_r9i.rlf_TmrsAndConsts_r9.choice*/
     FILL_UINT_TKN(radioResCfg->extaddgrp_1.rlf_TmrsAndConsts_r9.choice,0);

     /*Step 1.2.2. Fill rlf_TmrsAndConsts_r9i.rlf_TmrsAndConsts_r9.setup.present*/
     FILL_UINT_TKN(radioResCfg->extaddgrp_1.rlf_TmrsAndConsts_r9.val.setup.pres,PRSNT_NODEF);

     FILL_UINT_TKN(radioResCfg->extaddgrp_1.rlf_TmrsAndConsts_r9.val.setup.t301_r9,\
           NhuRLF_TmrsAndConsts_r9setupt301_r9ms100Enum);
     FILL_UINT_TKN(radioResCfg->extaddgrp_1.rlf_TmrsAndConsts_r9.val.setup.t310_r9,\
           NhuRLF_TmrsAndConsts_r9setupt310_r9ms0Enum);
     FILL_UINT_TKN(radioResCfg->extaddgrp_1.rlf_TmrsAndConsts_r9.val.setup.n310_r9,\
           NhuRLF_TmrsAndConsts_r9setupn310_r9n1Enum);
     FILL_UINT_TKN(radioResCfg->extaddgrp_1.rlf_TmrsAndConsts_r9.val.setup.t311_r9,\
           NhuRLF_TmrsAndConsts_r9setupt311_r9ms1000Enum);
     FILL_UINT_TKN(radioResCfg->extaddgrp_1.rlf_TmrsAndConsts_r9.val.setup.n311_r9,\
           NhuRLF_TmrsAndConsts_r9setupn311_r9n1Enum);
     FILL_UINT_TKN(radioResCfg->extaddgrp_2.pres,PRSNT_NODEF);
     FILL_UINT_TKN(radioResCfg->extaddgrp_2.measSubfrmPatternPCell_r10.choice,0);
     FILL_UINT_TKN(radioResCfg->extaddgrp_2.measSubfrmPatternPCell_r10.val.setup.choice, 0);
     if(radioResCfg->extaddgrp_2.measSubfrmPatternPCell_r10.val.setup.choice.val==0)
     {
       FILL_BIT_STR(radioResCfg->extaddgrp_2.measSubfrmPatternPCell_r10.val.setup.val.subframePatternFDD_r10,\
             40,1,evnt);
     }
     else
     {
       FILL_UINT_TKN(radioResCfg->extaddgrp_2.measSubfrmPatternPCell_r10.val.setup.val.subframePatternTDD_r10.choice, 0);
       if(radioResCfg->extaddgrp_2.measSubfrmPatternPCell_r10.val.setup.val.subframePatternTDD_r10.choice.val==0)
       {
         FILL_BIT_STR(radioResCfg->extaddgrp_2.measSubfrmPatternPCell_r10.val.setup.val.subframePatternTDD_r10.val.\
               subframeConfig1_5_r10, 20, 1, evnt);
       }
       else if(radioResCfg->extaddgrp_2.measSubfrmPatternPCell_r10.val.setup.val.subframePatternTDD_r10.choice.val==1)
       {
         FILL_BIT_STR(radioResCfg->extaddgrp_2.measSubfrmPatternPCell_r10.val.setup.val.subframePatternTDD_r10.val.\
               subframeConfig0_r10, 70, 1, evnt );
       }
       else
       {
         FILL_BIT_STR(radioResCfg->extaddgrp_2.measSubfrmPatternPCell_r10.val.setup.val.subframePatternTDD_r10.val.\
               subframeConfig6_r10, 60, 1, evnt);
       }
     }

#endif
#endif/*LTERRC_REL9*/
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nhAcUtlFillNhuSRBAddModLst
*
*       Desc:  This function fills SRB(SRB1/SRB2) Add Modify List in the message 
*              to be sent to UE
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuSRBAddModLst
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuSRBAddModLst(tcCb, spCb, radioResCfg, evnt)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb; 
NhuRadioResourceConfigDedicated *radioResCfg;
Ptr         evnt;
#endif
{
   NhuSRB_ToAddMod *srbIe = NULLP;
   U16    numRb;
   U16    idx;
   U16    numAddModSrb=0;
   U8     rlcCfgMode;
   U16    addModSrb[2];
   U16    rbVal;
   U8     logchDed = 0;
   U8     rlcDed = 0;
   U8     srbPres = 1;
   U8     rlcCfgAbsent = 0;
   U8     logChCfgAbsent = 0;
   U16    len;
   Txt    msgStr[100];
   Txt    frstWrd[3];
   Txt    secWrd[3];
   U8     rbType = 0; 
#ifdef LTERRC_REL9
   U8     ulSpecPrmAbsent = 0; 
   U8     srMaskAbsent = 0; 
#endif

   TRC2(nhAcUtlFillNhuSRBAddModLst);  
 
   numRb = 0;
   rbVal = 0;
   numAddModSrb = 0;

   CMXTA_ZERO(msgStr, sizeof(msgStr));
   CMXTA_ZERO(addModSrb, sizeof(addModSrb));

   /* Store the SRB to be added into addModSrb */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "numAddRb", &numRb);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "addRbIdStr", msgStr);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "srbLogChCfgAbsent",
            &logChCfgAbsent);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "srbRlcCfgAbsent",
            &rlcCfgAbsent);

   len = 0;
   while(len < strlen(msgStr))
   {
      CMXTA_ZERO(frstWrd, sizeof(frstWrd));
      /* Get RbId */
      nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      CMXTA_ZERO(secWrd, sizeof(secWrd));
      /* Get RbType */
      nhAcUtlStrToken(&msgStr[len], secWrd, ',');
      len = len + strlen(secWrd) + 1;
      rbType =  atoi(secWrd);
      if( (rbVal == 1 || rbVal == 2) && (rbType == CM_LTE_SRB) ) 
      {
         addModSrb[numAddModSrb] = rbVal;
         numAddModSrb++;
      }
   }

   CMXTA_ZERO(msgStr, sizeof(msgStr));

   /* Store the SRB to be modified into addModSrb */
   numRb = 0;   
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "numModRb", &numRb);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "modRbIdStr", msgStr);
   len = 0;
   while(len < strlen(msgStr))
   {
      CMXTA_ZERO(frstWrd, sizeof(frstWrd));
      /* Get RbId */
      nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      CMXTA_ZERO(secWrd, sizeof(secWrd));
      /* Get RbType */
      nhAcUtlStrToken(&msgStr[len], secWrd, ',');
      len = len + strlen(secWrd) + 1;
      rbType =  atoi(secWrd);
      if( (rbVal == 1 || rbVal == 2) && (rbType == CM_LTE_SRB) ) 
      {
         addModSrb[numAddModSrb] = rbVal;
         numAddModSrb++;
      }
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "srbPresent",
                              &srbPres);
   if(srbPres && (numAddModSrb == 0))
   {
      numAddModSrb = 1;
      addModSrb[0] = 1;
   }

   /* Allocate memory required for numAddModSrb */
   CMXTA_GET_MEM(evnt,sizeof(NhuSRB_ToAddMod)*numAddModSrb,
                 &(radioResCfg->srb_ToAddModLst.member));

   if(numAddModSrb > 0)
      FILL_UINT_TKN(radioResCfg->srb_ToAddModLst.noComp, numAddModSrb);

   /* Filling SrbAddModLst */
   for(idx = 0; idx < numAddModSrb; idx++)
   {
      srbIe = &(radioResCfg->srb_ToAddModLst.member[idx]);
      FILL_UINT_TKN(srbIe->pres,PRSNT_NODEF);
      FILL_UINT_TKN(srbIe->srb_Identity,addModSrb[idx]);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "rlcCfgDed",
                              &rlcDed);
      if(rlcCfgAbsent)
      {
         NHAC_FILL_U8_U32_TKN(srbIe->rlc_Config.choice, NOTPRSNT, NOTPRSNT);
      }
      else
      {
         FILL_UINT_TKN(srbIe->rlc_Config.choice, rlcDed);
         if(rlcDed == RLC_CONFIG_EXPLICITVALUE)
         {
            rlcCfgMode = RLC_CONFIG_AM;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "rlcCfgMode",
                  &rlcCfgMode);
            FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.choice,rlcCfgMode)

               /* RLC Configuration for AM Mode */
               if(rlcCfgMode == RLC_CONFIG_AM )
               {
                  FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.val.am.pres,PRSNT_NODEF);

                  /* Uplink AM RLC Config */
                  FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.val.am.ul_AM_RLC.pres,
                        PRSNT_NODEF);
                  FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.val.am.ul_AM_RLC.\
                        t_PollRetransmit,NhuT_PollRetransmitms5Enum);
                  FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.val.am.ul_AM_RLC.pollPDU,
                        NhuPollPDUp4Enum);
                  FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.val.am.ul_AM_RLC.pollByte,
                        0);
                  FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.val.am.ul_AM_RLC.\
                        maxRetxThreshold,NhuUL_AM_RLCmaxRetxThresholdt1Enum);

                  /* Downlink AM RLC Config */
                  FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.val.am.dl_AM_RLC.pres,
                        PRSNT_NODEF);
                  FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.val.am.dl_AM_RLC.\
                        t_Reordering, NhuT_Reorderingms0Enum);
                  FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.val.am.dl_AM_RLC.\
                        t_StatusProhibit,NhuT_StatusProhibitms0Enum);
               }
            /* RLC Configuration for UM Bi-Directional Mode */
               else if(rlcCfgMode == RLC_CONFIG_UM_BI_DIRECTIONAL)
               {
                  FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.val.um_Bi_Directional.pres,
                        PRSNT_NODEF);

                  nhAcUtlFillNhuUlUmRlc(tcCb, spCb,
                        &srbIe->rlc_Config.val.explicitValue.val.um_Bi_Directional.ul_UM_RLC);

                  nhAcUtlFillNhuDlUmRlc(tcCb, spCb,
                        &srbIe->rlc_Config.val.explicitValue.val.um_Bi_Directional.dl_UM_RLC);
               }
            /* RLC Configuration for UM UL-Directional Mode */
               else if(rlcCfgMode == RLC_CONFIG_UM_UNI_DIRECTIONAL_UL)
               {
                  FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.val.um_Uni_Directional_UL.pres,
                        PRSNT_NODEF);

                  nhAcUtlFillNhuUlUmRlc(tcCb, spCb,
                        &srbIe->rlc_Config.val.explicitValue.val.um_Uni_Directional_UL.ul_UM_RLC);
               }
            /* RLC Configuration for UM DL-Directional Mode */
               else if(rlcCfgMode == RLC_CONFIG_UM_UNI_DIRECTIONAL_DL)
               {
                  FILL_UINT_TKN(srbIe->rlc_Config.val.explicitValue.val.um_Uni_Directional_DL.pres,
                        PRSNT_NODEF);

                  nhAcUtlFillNhuDlUmRlc(tcCb, spCb,
                        &srbIe->rlc_Config.val.explicitValue.val.um_Uni_Directional_DL.dl_UM_RLC);
               }
         }
      }

      /* Logical Channel Configuration for SRB */
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "logCfgDed",
            &logchDed);
      if(logChCfgAbsent)
      {
         NHAC_FILL_U8_U32_TKN(srbIe->logicalChannelConfig.choice, NOTPRSNT, NOTPRSNT);
      }
      else
      {
#ifdef LTERRC_REL9
         /* UL Specific Parameters for SRB */
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "srbULSpecPrmAbsent",
               &ulSpecPrmAbsent);
         if(ulSpecPrmAbsent)
         {
             NHAC_FILL_U8_U32_TKN(srbIe->logicalChannelConfig.val.\
                 explicitValue.ul_SpecificParams.pres, NOTPRSNT, NOTPRSNT);
         }
         else
         {
#endif
             FILL_UINT_TKN(srbIe->logicalChannelConfig.choice,
                logchDed);
             if(logchDed == LOGICALCHANNELCONFIG_EXPLICITVALUE)
             {
                FILL_UINT_TKN(srbIe->logicalChannelConfig.val.explicitValue.\
                      pres,PRSNT_NODEF);
                FILL_UINT_TKN(srbIe->logicalChannelConfig.val.explicitValue.\
                      ul_SpecificParams.pres, PRSNT_NODEF);
                FILL_UINT_TKN(srbIe->logicalChannelConfig.val.explicitValue.\
                      ul_SpecificParams.priority,1);
                FILL_UINT_TKN(srbIe->logicalChannelConfig.val.explicitValue.\
                      ul_SpecificParams.prioritisedBitRate,0);
                FILL_UINT_TKN(srbIe->logicalChannelConfig.val.explicitValue.\
                      ul_SpecificParams.bucketSizeDuration,1);
                FILL_UINT_TKN(srbIe->logicalChannelConfig.val.explicitValue.\
                      ul_SpecificParams.logicalChannelGroup,1);
             }                
#ifdef LTERRC_REL9
         }
         /* SR-MASK for SRB */
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, 
                      "srMaskAbsent", &srMaskAbsent);
#ifndef RRC_REL11
         if(srMaskAbsent)
         {
             NHAC_FILL_U8_U32_TKN(srbIe->logicalChannelConfig.val.\
                      explicitValue.extaddgrp_r9.pres, NOTPRSNT, NOTPRSNT);
         }
         else
         {
             /*R9 upgrade: filling the R9 IEs*/
             FILL_UINT_TKN(srbIe->logicalChannelConfig.val.explicitValue.\
                   extaddgrp_r9.pres, PRSNT_NODEF);
             NHAC_FILL_U8_U32_TKN(srbIe->logicalChannelConfig.val.
                   explicitValue.extaddgrp_r9.logicalChannelSR_Mask_r9,\
                   PRSNT_NODEF, NhuLogChannelConfigextaddgrp_r9logicalChannelSR_Mask_r9setupEnum);
         }
#else 
         if(srMaskAbsent)
         {
             NHAC_FILL_U8_U32_TKN(srbIe->logicalChannelConfig.val.\
                      explicitValue.extaddgrp_1.pres, NOTPRSNT, NOTPRSNT);
         }
         else
         {
             /*R9 upgrade: filling the R9 IEs*/
             FILL_UINT_TKN(srbIe->logicalChannelConfig.val.explicitValue.\
                   extaddgrp_1.pres, PRSNT_NODEF);
             NHAC_FILL_U8_U32_TKN(srbIe->logicalChannelConfig.val.
                   explicitValue.extaddgrp_1.logicalChannelSR_Mask_r9,\
                   PRSNT_NODEF, NhuLogChannelConfigextaddgrp_1logicalChannelSR_Mask_r9setupEnum);
         }
#endif
#endif /*LTERRC_REL9*/
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nhAcUtlFillNhuDRBAddModLst
*
*       Desc:  This function fills DRB Add Modify List in the message to UE
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuDRBAddModLst
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuDRBAddModLst(tcCb, spCb, radioResCfg, evnt)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb; 
NhuRadioResourceConfigDedicated *radioResCfg;
Ptr         evnt;
#endif
{
   U16             numRb;
   U8             rbVal;
   U16             len;
   U16             idx;
   U16             numAddModDrb;
   U16             numLogicalIds;
   U8              addModDrb[30];
   U8              logicalDrbId[30];
   U16              lcIdlen = 0;
   U8              pdcpCfgAbsent = 0;
   U8              rlcCfgAbsent = 0;
   U8              ulSpecParamAbsent = 0;
   U8              logChCfgAbsent = 0;
   Txt             msgStr[100];
   Txt             lChIdStr[100];
   Txt             frstWrd[3];
   U8              eps_BrIdAbsent = 0;
   Txt             secWrd[3];
   U8              rbType = 0;
   NhuLogChannelConfig *logChCfg;

   TRC2(nhAcUtlFillNhuDRBAddModLst);

   numRb = 0;
   numAddModDrb = 0;
   numLogicalIds = 0;

   CMXTA_ZERO(msgStr, sizeof(msgStr));
   CMXTA_ZERO(addModDrb, sizeof(addModDrb));
   CMXTA_ZERO(lChIdStr, sizeof(lChIdStr));

   /* Store the SRB to be added into addModSrb */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "numAddRb", &numRb);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "addRbIdStr", msgStr);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "addLcIdStr",
                           lChIdStr);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "pdcpCfgAbsent",
                           &pdcpCfgAbsent);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "drbRlcCfgAbsent",
                           &rlcCfgAbsent);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "drbLogChCfgAbsent",
                           &logChCfgAbsent);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ulSpecParamAbsent",
                           &ulSpecParamAbsent);

   len = 0;
   while(len <= strlen(msgStr))
   {
      CMXTA_ZERO(frstWrd, sizeof(frstWrd));
      /* Get RbId */
      nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      CMXTA_ZERO(secWrd, sizeof(secWrd));
      /* Get RbType */
      nhAcUtlStrToken(&msgStr[len], secWrd, ',');
      len = len + strlen(secWrd) + 1;
      rbType = atoi(secWrd);
      if(rbType == CM_LTE_DRB) 
      {
         addModDrb[numAddModDrb] = rbVal;
         numAddModDrb++;
      }
   }

   lcIdlen = 0;
   len = lcIdlen;
   while(len <= strlen(lChIdStr))
   {
      if(!strlen(lChIdStr))
         break;
      CMXTA_ZERO(frstWrd, sizeof(frstWrd));
      nhAcUtlStrToken(&lChIdStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      /* adding 1 bcoz lcId is given as 2,3,4 in xml.
                                    But allowed values - 3 to 10 */
      logicalDrbId[numLogicalIds] = atoi(frstWrd)+ 1;
      numLogicalIds++;
   }
   lcIdlen = len;

   CMXTA_ZERO(msgStr, sizeof(msgStr));

   /* Store the DRB Ids to be modified into addModDrb array */
   numRb = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "numModRb", &numRb);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "modRbIdStr", msgStr);
   len = 0;
   while(len <= strlen(msgStr))
   {
      CMXTA_ZERO(frstWrd, sizeof(frstWrd));
      /* Get RbId */
      nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      CMXTA_ZERO(secWrd, sizeof(secWrd));
      /* Get RbType */
      nhAcUtlStrToken(&msgStr[len], secWrd, ',');
      len = len + strlen(secWrd) + 1;
      rbType = atoi(secWrd);
      if(rbType == CM_LTE_DRB) 
      {
         addModDrb[numAddModDrb] = rbVal;
         numAddModDrb++;
      }
   }

   if(numAddModDrb == 0)
   {
      RETVALUE(CMXTA_ERR_NONE);
   }

   /* Allocate memory required for numAddModDrb */
   CMXTA_GET_MEM(evnt,sizeof(NhuDRB_ToAddMod)*numAddModDrb,
                 &(radioResCfg->drb_ToAddModLst.member));

   FILL_UINT_TKN(radioResCfg->drb_ToAddModLst.noComp, numAddModDrb);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "eps_BrIdAbsent", &eps_BrIdAbsent);

   /* Filling DrbAddModLst */
   for(idx = 0; idx < numAddModDrb; idx++)
   {
      FILL_UINT_TKN(radioResCfg->drb_ToAddModLst.member[idx].pres,\
               PRSNT_NODEF);
      FILL_UINT_TKN(radioResCfg->drb_ToAddModLst.member[idx].drb_Identity,
                    addModDrb[idx]);
      if (1 == eps_BrIdAbsent)
      {
         NHAC_FILL_U8_U32_TKN(radioResCfg->drb_ToAddModLst.member[idx].\
                    eps_BrIdentity, NOTPRSNT, NOTPRSNT);
      }
      else
      {
         FILL_UINT_TKN(radioResCfg->drb_ToAddModLst.member[idx].eps_BrIdentity,
                    addModDrb[idx]+1);
      }

      /* Fill PDCP Config in DRB list */
      if(pdcpCfgAbsent)
      {
         NHAC_FILL_U8_U32_TKN(radioResCfg->drb_ToAddModLst.member[idx].pdcp_Config.pres,
                     NOTPRSNT, NOTPRSNT);
      }
      else
      {
         nhAcUtlFillNhuPDCPDrbCfg(tcCb, spCb,
                   &(radioResCfg->drb_ToAddModLst.member[idx].pdcp_Config), evnt);
      }

      /* Fill RLC Config in DRB list */
      if(rlcCfgAbsent)
      {
         NHAC_FILL_U8_U32_TKN(radioResCfg->drb_ToAddModLst.member[idx].rlc_Config.choice,
               NOTPRSNT, NOTPRSNT);
      }
      else
      {
         nhAcUtlFillNhuRLCDrbCfg(tcCb, spCb,
                   &(radioResCfg->drb_ToAddModLst.member[idx].rlc_Config), evnt);
      }

      /* Logical Channel Id for DRB */
      if(lcIdlen == 0)
      {
         NHAC_FILL_U8_U32_TKN(radioResCfg->drb_ToAddModLst.member[idx].\
               logicalChannelIdentity, NOTPRSNT, NOTPRSNT);
      }
      else
      {
         FILL_UINT_TKN(radioResCfg->drb_ToAddModLst.member[idx].logicalChannelIdentity,
               logicalDrbId[idx]); 
      }

      /* Logical Channel Configuration for DRB */
      if (logChCfgAbsent)
      {
         NHAC_FILL_U8_U32_TKN(radioResCfg->drb_ToAddModLst.member[idx].\
               logicalChannelConfig.pres, NOTPRSNT, NOTPRSNT);
      }
      else
      {
         logChCfg = &(radioResCfg->drb_ToAddModLst.member[idx].logicalChannelConfig);
         FILL_UINT_TKN(logChCfg->pres, PRSNT_NODEF);
         FILL_UINT_TKN(logChCfg->ul_SpecificParams.pres, PRSNT_NODEF);
         FILL_UINT_TKN(logChCfg->ul_SpecificParams.priority,1);
         FILL_UINT_TKN(logChCfg->ul_SpecificParams.prioritisedBitRate, 0);
         FILL_UINT_TKN(logChCfg->ul_SpecificParams.logicalChannelGroup,1);
         FILL_UINT_TKN(logChCfg->ul_SpecificParams.bucketSizeDuration,1);

#ifdef LTERRC_REL9
         /*R9 upgrade: filling the R9 IEs*/
#ifndef RRC_REL11
         FILL_UINT_TKN(logChCfg->extaddgrp_r9.pres, PRSNT_NODEF);
         NHAC_FILL_U8_U32_TKN(logChCfg->extaddgrp_r9.logicalChannelSR_Mask_r9,\
               PRSNT_NODEF, NhuLogChannelConfigextaddgrp_1logicalChannelSR_Mask_r9setupEnum);
#else
         FILL_UINT_TKN(logChCfg->extaddgrp_1.pres, PRSNT_NODEF);
         NHAC_FILL_U8_U32_TKN(logChCfg->extaddgrp_1.logicalChannelSR_Mask_r9,\
               PRSNT_NODEF, NhuLogChannelConfigextaddgrp_1logicalChannelSR_Mask_r9setupEnum);
#endif
#endif /*LTERRC_REL9*/

         if(ulSpecParamAbsent)
         {
            NHAC_FILL_U8_U32_TKN(logChCfg->ul_SpecificParams.pres, NOTPRSNT, NOTPRSNT);
         }
         else
         {
            FILL_UINT_TKN(logChCfg->pres, PRSNT_NODEF);
            FILL_UINT_TKN(logChCfg->ul_SpecificParams.pres, PRSNT_NODEF);
            FILL_UINT_TKN(logChCfg->ul_SpecificParams.priority,1);
            FILL_UINT_TKN(logChCfg->ul_SpecificParams.prioritisedBitRate, 0);
            FILL_UINT_TKN(logChCfg->ul_SpecificParams.logicalChannelGroup,1);
            FILL_UINT_TKN(logChCfg->ul_SpecificParams.bucketSizeDuration,1);
         }
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nhAcUtlFillNhuDRBRlsLst
*
*       Desc:  This function fills Release DRB List in the message to UE
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuDRBRlsLst
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuDRBRlsLst(tcCb, spCb, radioResCfg, evnt)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb; 
NhuRadioResourceConfigDedicated *radioResCfg;
Ptr         evnt;
#endif
{
   U16             numRb;
   U16             idx;
   Txt             msgStr[100];
   Txt             frstWrd[3];
   Txt             secWrd[3];
   U8              rlsRb[32];
   U8              rbVal;
   U8              rbType = 0;
   U16             len;

   TRC2(nhAcUtlFillNhuDRBRlsLst);

   CMXTA_ZERO(msgStr, sizeof(msgStr));
   CMXTA_ZERO(rlsRb, sizeof(rlsRb));

   numRb = 0;
   /* Get the number of DRBs to be released from xml */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, "numRlsRb", &numRb);
   if(0 == numRb)
   {
      RETVALUE(CMXTA_ERR_NONE);
   }
   
   FILL_UINT_TKN(radioResCfg->drb_ToRlsLst.noComp, numRb);


   CMXTA_GET_MEM(evnt, (sizeof(NhuDRB_Identity)*numRb), &(radioResCfg->drb_ToRlsLst.member));

   /* Reading the DRB id to be released from xml */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "rlsRbIdStr", msgStr);

   idx = 0;
   len = 0;
   while(len < strlen(msgStr))
   {
      CMXTA_ZERO(frstWrd, sizeof(frstWrd));
      /* Get rbId */
      nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      CMXTA_ZERO(secWrd, sizeof(secWrd));
      /* Get rbType */
      nhAcUtlStrToken(&msgStr[len], secWrd, ',');
      len = len + strlen(secWrd) + 1;
      rbType = atoi(secWrd);
      if(rbType == CM_LTE_DRB)
      {
         rlsRb[idx] = rbVal;
         idx++;
      }
   }

   /* Filling the DRB Release list */
   for(idx = 0; idx < radioResCfg->drb_ToRlsLst.noComp.val; idx++)
   {
      radioResCfg->drb_ToRlsLst.member[idx].pres =  TRUE;
      radioResCfg->drb_ToRlsLst.member[idx].val =  rlsRb[idx];


      /*FILL_UINT_TKN(radioResCfg->drb_ToRlsLst.member[idx].pres,PRSNT_NODEF);
      FILL_UINT_TKN(radioResCfg->drb_ToRlsLst.member[idx].drb_Identity, 
                    rlsRb[idx]);*/
   }

   RETVALUE(CMXTA_ERR_NONE);
}

#ifdef LTERRC_REL9
/*
*
*       Fun:   nhAcUtlFillNhuMACMainCfg
*
*       Desc:  This function fills the MAC Main Config
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuMACMainCfg
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuMACMainCfg(tcCb, spCb, radioResCfg, evnt)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb; 
NhuRadioResourceConfigDedicated *radioResCfg;
Ptr         evnt;
#endif
{
        NhuRadioResourceConfigDedicatedmac_MainConfig *mac_MainConfig;

   TRC2(nhAcUtlFillNhuMACMainCfg);

   mac_MainConfig = &(radioResCfg->mac_MainConfig);

   FILL_UINT_TKN(mac_MainConfig->choice, 0);
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.pres, PRSNT_NODEF);
   /* Filling NhuMAC_MainConfigul_SCH_Config */
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.ul_SCH_Config.pres, PRSNT_NODEF);
   NHAC_FILL_U8_U32_TKN(mac_MainConfig->val.explicitValue.ul_SCH_Config.maxHARQ_Tx,\
         PRSNT_NODEF, PRSNT_NODEF);
   NHAC_FILL_U8_U32_TKN(mac_MainConfig->val.explicitValue.ul_SCH_Config.periodicBSR_Timer,\
         PRSNT_NODEF, PRSNT_NODEF);
   NHAC_FILL_U8_U32_TKN(mac_MainConfig->val.explicitValue.ul_SCH_Config.retxBSR_Timer,\
         PRSNT_NODEF, PRSNT_NODEF);
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.ul_SCH_Config.ttiBundling, PRSNT_NODEF);

   /* Filling NhuDRX_Config */
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.drx_Config.choice, 0);
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.drx_Config.val.setup.pres,\
         PRSNT_NODEF);
   NHAC_FILL_U8_U32_TKN(mac_MainConfig->val.explicitValue.drx_Config.val.setup.\
         onDurationTimer, PRSNT_NODEF, NhuDRX_ConfigsetuponDurationTimerpsf1Enum);
   NHAC_FILL_U8_U32_TKN(mac_MainConfig->val.explicitValue.drx_Config.val.setup.\
         drx_InactivityTimer, PRSNT_NODEF, NhuDRX_Configsetupdrx_InactivityTimerpsf1Enum);
   NHAC_FILL_U8_U32_TKN(mac_MainConfig->val.explicitValue.drx_Config.val.setup.\
         drx_ReTxTimer, PRSNT_NODEF, NhuDRX_Configsetupdrx_ReTxTimerpsf1Enum);
   NHAC_FILL_U8_U32_TKN(mac_MainConfig->val.explicitValue.drx_Config.val.setup.\
         longDRX_CycleStartOffset.choice, PRSNT_NODEF, 0);
   NHAC_FILL_U8_U32_TKN(mac_MainConfig->val.explicitValue.drx_Config.val.setup.\
         longDRX_CycleStartOffset.val.sf10, PRSNT_NODEF, PRSNT_NODEF);
         /*Filling shortDRX */
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.drx_Config.val.setup.\
         shortDRX.pres, PRSNT_NODEF);
   NHAC_FILL_U8_U32_TKN(mac_MainConfig->val.explicitValue.drx_Config.val.setup.\
         shortDRX.shortDRX_Cycle, PRSNT_NODEF, NhuDRX_ConfigsetupshortDRXshortDRX_Cyclesf2Enum);
   NHAC_FILL_U8_U32_TKN(mac_MainConfig->val.explicitValue.drx_Config.val.setup.\
         shortDRX.drxShortCycleTimer, PRSNT_NODEF, PRSNT_NODEF);

   NHAC_FILL_U8_U32_TKN(mac_MainConfig->val.explicitValue.timeAlignmentTimerDedicated,\
         PRSNT_NODEF, PRSNT_NODEF);
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.phr_Config.choice, PRSNT_NODEF);
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.phr_Config.val.setup.pres, PRSNT_NODEF);

   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.phr_Config.val.setup.periodicPHR_Timer,\
         NhuMAC_MainConfigphr_ConfigsetupperiodicPHR_Timersf10Enum);
   
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.phr_Config.val.setup.prohibitPHR_Timer,\
         NhuMAC_MainConfigphr_ConfigsetupprohibitPHR_Timersf0Enum);
   
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.phr_Config.val.setup.dl_PathlossChange,\
         NhuMAC_MainConfigphr_Configsetupdl_PathlossChangedB1Enum);
 
 /* Fill NhuMAC_MainConfigextaddgrp_r9 */
#ifndef RRC_REL11
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.extaddgrp_r9.pres, PRSNT_NODEF);
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.extaddgrp_r9.sr_ProhibitTimer_r9, PRSNT_NODEF);
#else
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.extaddgrp_1.pres, PRSNT_NODEF);
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.extaddgrp_1.sr_ProhibitTimer_r9, PRSNT_NODEF);
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.extaddgrp_2.pres, PRSNT_NODEF);
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.extaddgrp_2.mac_MainConfig_v1020.pres, PRSNT_NODEF);
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.extaddgrp_2.mac_MainConfig_v1020.sCellDeactivationTimer_r10, 
          NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020sCellDeactivationTimer_r10rf2Enum);
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.extaddgrp_2.mac_MainConfig_v1020.extendedBSR_Sizes_r10, 
          NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020extendedBSR_Sizes_r10setupEnum);
   FILL_UINT_TKN(mac_MainConfig->val.explicitValue.extaddgrp_2.mac_MainConfig_v1020.extendedPHR_r10, 
          NhuMAC_MainConfigextaddgrp_2mac_MainConfig_v1020extendedPHR_r10setupEnum);

#endif

   RETVALUE(CMXTA_ERR_NONE);
}
#endif /*LTERRC_REL9*/

/*
*
*       Fun:   nhAcUtlFillNhuSpsCfg
*
*       Desc:  This function fills Release DRB List in the message to UE
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuSpsCfg
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuSpsCfg(tcCb, spCb, radioResCfg, evnt)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb; 
NhuRadioResourceConfigDedicated *radioResCfg;
Ptr         evnt;
#endif
{
   TRC2(nhAcUtlFillNhuSpsCfg);

   FILL_UINT_TKN(radioResCfg->sps_Config.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->sps_Config.sps_ConfigUL.choice, SPS_CONFIGUL_SETUP);
   FILL_UINT_TKN(radioResCfg->sps_Config.sps_ConfigUL.val.setup.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->sps_Config.sps_ConfigUL.val.setup.\
                 semiPersistSchedIntervalUL, 
                 NhuSPS_ConfigULsetupsemiPersistSchedIntervalULsf10Enum);
   FILL_UINT_TKN(radioResCfg->sps_Config.sps_ConfigUL.val.setup.implicitRlsAfter,
                 NhuSPS_ConfigULsetupimplicitRlsAftere2Enum);
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nhAcUtlFillNhuRRCPhyCfgDedi
*
*       Desc:  This function fills Physical Configuration for UE
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuRRCPhyCfgDedi
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
NhuRadioResourceConfigDedicated *radioResCfg,
Ptr         evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuRRCPhyCfgDedi(tcCb, spCb, radioResCfg, evnt)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb; 
NhuRadioResourceConfigDedicated *radioResCfg;
Ptr         evnt;
#endif
{
   NhuPDSCH_ConfigDedicated              *pdschCfg;
   NhuPUCCH_ConfigDedicated              *pucchCfg;
   NhuUlnkPowerCntrlDedicated            *uplnkPwrCntrl;
   NhuTPC_PDCCH_Config                   *tpcPdcchCfgPucch;
   NhuTPC_PDCCH_Config                   *tpcPdcchCfgPusch;
   NhuCQI_ReportConfig                   *cqiRprtng;
   NhuSoundingRS_UL_ConfigDedicated      *soundngRsUlCfg;
   NhuSchedulingRqstConfig               *schedulingRqstConfig;
   NhuPhysicalConfigDedicatedantennaInfo *antennaInfo;
   Bool                                  isCodeBookRestn;
   Bool                                  tdd;
   U8                                    txMode;
   Bool                                  cqiRprtAperiodicPres;
#ifdef LTERRC_REL9
   Bool                                  cqiMaskPres;
   Bool                                  setupPres;
   Bool                                  isPmiRprtPres;
   Bool                                  isCodeBkSubsetRestnv920Pres;
#endif /*LTERRC_REL9*/

#ifdef RRC_REL11
   U16   idx=0;
   U16   idx1=0;
   U8    cifPresence=0;
   U32   cqiPUCCHResIdxr10=0;
   U32   cqiPUCCHResIdxP1r10=0;
   U32   cqipmiCfgIdx=0;
   U32   riCfgIdx=0;
   U8    simulAckNackAndCQI=0;
   U32   cqipmiCfgIdx2r10=0;
   U32   riCfgIdx2r10=0;
   U32   resourceConfigr10=0;
   U32   subframeConfigr10=0;
   S32   pcr10=1;
   U32   zeroTxPwrSubfrmCfgr10=0;
   U32   n3PUCCHAnLstMem=0;
   U32   n3PUCCHAnLstP1Mem=0;
   U32   n1PUCCHAnRepP1=0;
   U32   AckIdxMc=0;
   U32   riIdxMc=0;
   U32   cqiIdxMc=0;
   U32   srPucchResIdxP1=0;

#endif
   TRC2(nhAcUtlFillNhuRRCPhyCfgDedi);

   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.pres,PRSNT_NODEF);

   /* PDSCH Configuration */
   pdschCfg = &(radioResCfg->physicalConfigDedicated.pdsch_ConfigDedicated);

   FILL_UINT_TKN(pdschCfg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(pdschCfg->p_a,NhuPDSCH_ConfigDedicatedp_adB_6Enum);

   /* PUCCH Configuration */
   pucchCfg = &(radioResCfg->physicalConfigDedicated.pucch_ConfigDedicated);

   FILL_UINT_TKN(pucchCfg->pres,PRSNT_NODEF);
   FILL_UINT_TKN(pucchCfg->ackNackRepetition.choice,ACKNACKREPETITION_SETUP);
   FILL_UINT_TKN(pucchCfg->ackNackRepetition.val.setup.pres,PRSNT_NODEF);
   FILL_UINT_TKN(pucchCfg->ackNackRepetition.val.setup.repetitionFactor,
       NhuPUCCH_ConfigDedicatedackNackRepetitionsetuprepetitionFactorn2Enum);
   FILL_UINT_TKN(pucchCfg->ackNackRepetition.val.setup.n1PUCCH_AN_Rep,1);
   tdd = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "tddPres", 
                  &tdd);
   if(tdd)
   {
      FILL_UINT_TKN(pucchCfg->tdd_AckNackFeedbackMode,
             NhuPUCCH_ConfigDedicatedtdd_AckNackFeedbackModebundlingEnum);
   }

   /* Uplink Power Control Configuration */
   uplnkPwrCntrl = &(radioResCfg->physicalConfigDedicated.uplinkPowerCntrlDedicated); 

   FILL_UINT_TKN(uplnkPwrCntrl->pres,PRSNT_NODEF);
   FILL_UINT_TKN(uplnkPwrCntrl->p0_UE_PUSCH,PRSNT_NODEF);
   FILL_UINT_TKN(uplnkPwrCntrl->deltaMCS_Enabled,
                 NhuUlnkPowerCntrlDedicateddeltaMCS_Enableden0Enum);
   FILL_UINT_TKN(uplnkPwrCntrl->accumulationEnabled,1);
   FILL_UINT_TKN(uplnkPwrCntrl->p0_UE_PUCCH,1);
   FILL_UINT_TKN(uplnkPwrCntrl->pSRS_Offset,1);
 
   /* PDCCH-PUCCH Configuration */
   tpcPdcchCfgPucch = &(radioResCfg->physicalConfigDedicated.\
            tpc_PDCCH_ConfigPUCCH);

   FILL_UINT_TKN(tpcPdcchCfgPucch->choice,TPC_PDCCH_CONFIG_RELEASE);
   FILL_UINT_TKN(tpcPdcchCfgPucch->val.setup.pres,PRSNT_NODEF);
    FILL_BIT_STR(tpcPdcchCfgPucch->val.setup.tpc_RNTI, 16, 1, evnt); 
   FILL_UINT_TKN(tpcPdcchCfgPucch->val.setup.tpc_Idx.choice,
                 TPC_IDX_INDEXOFFORMAT3);

   if(tpcPdcchCfgPucch->val.setup.tpc_Idx.choice.val == TPC_IDX_INDEXOFFORMAT3)
   {
      FILL_UINT_TKN(tpcPdcchCfgPucch->val.setup.tpc_Idx.val.indexOfFormat3,1);
   }
   else
   {
      FILL_UINT_TKN(tpcPdcchCfgPucch->val.setup.tpc_Idx.val.indexOfFormat3A,1);
   }

   /* PDCCH-PUSCH Configuration */
   tpcPdcchCfgPusch = &(radioResCfg->physicalConfigDedicated.\
                        tpc_PDCCH_ConfigPUSCH);

   FILL_UINT_TKN(tpcPdcchCfgPusch->choice,TPC_PDCCH_CONFIG_RELEASE);
   FILL_UINT_TKN(tpcPdcchCfgPusch->val.setup.pres,PRSNT_NODEF);
   FILL_BIT_STR(tpcPdcchCfgPusch->val.setup.tpc_RNTI, 16, 1, evnt);
   FILL_UINT_TKN(tpcPdcchCfgPusch->val.setup.tpc_Idx.choice,
            TPC_IDX_INDEXOFFORMAT3);
   if((tpcPdcchCfgPusch->val.setup.tpc_Idx.choice.val) ==
            TPC_IDX_INDEXOFFORMAT3)
   {
      FILL_UINT_TKN(tpcPdcchCfgPusch->val.setup.tpc_Idx.val.indexOfFormat3,1);
   }
   else
   {
      FILL_UINT_TKN(tpcPdcchCfgPusch->val.setup.tpc_Idx.val.indexOfFormat3A,1);
   } 
   /* CQI Reporting Related Information */
   cqiRprtng = &(radioResCfg->physicalConfigDedicated.cqi_ReportConfig);
   /* CQI Reporting Aperiodic */
   cqiRprtAperiodicPres = FALSE;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "cqiRprtAperiodicPres", 
                  &cqiRprtAperiodicPres);
   if(cqiRprtAperiodicPres)
   {   
       FILL_UINT_TKN(cqiRprtng->pres,PRSNT_NODEF);
       FILL_UINT_TKN(cqiRprtng->cqi_ReportModeAperiodic, 0);
   }
   else
   {
       NHAC_FILL_U8_U32_TKN(cqiRprtng->cqi_ReportModeAperiodic,NOTPRSNT,0);
   }
   FILL_UINT_TKN(cqiRprtng->nomPDSCH_RS_EPRE_Offset,1);

#ifdef LTERRC_REL9
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "cqiMaskPres", 
                  &cqiMaskPres);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "cqiRprtPeriodicSetupPres", 
                  &setupPres);
   if(cqiMaskPres)
   {
      FILL_UINT_TKN(cqiRprtng->pres,PRSNT_NODEF);
      FILL_UINT_TKN(cqiRprtng->cqi_ReportPeriodic.choice,1);
      FILL_UINT_TKN(cqiRprtng->cqi_ReportPeriodic.val.setup.pres, setupPres);
      FILL_UINT_TKN(cqiRprtng->cqi_ReportPeriodic.val.setup.cqi_PUCCH_ResourceIdx, 1185);
      FILL_UINT_TKN(cqiRprtng->cqi_ReportPeriodic.val.setup.cqi_pmi_ConfigIdx, 1023);
      FILL_UINT_TKN(cqiRprtng->cqi_ReportPeriodic.val.setup.cqi_FormatIndicatorPeriodic.choice, CQI_FORMATINDICATORPERIODIC_WIDEBANDCQI);
      FILL_UINT_TKN(cqiRprtng->cqi_ReportPeriodic.val.setup.simultaneousAckNackAndCQI, 0);
   }
#endif /*LTERRC_REL9*/

   /* Sounding Rs Uplink Configuration */
   soundngRsUlCfg = &(radioResCfg->physicalConfigDedicated.soundingRS_UL_ConfigDedicated);

   /*  Antenna Configuration */
   antennaInfo = &(radioResCfg->physicalConfigDedicated.antennaInfo);

   FILL_UINT_TKN(antennaInfo->choice,ANTENNAINFO_EXPLICITVALUE);
   FILL_UINT_TKN(antennaInfo->val.explicitValue.pres,PRSNT_NODEF);
   FILL_UINT_TKN(antennaInfo->val.explicitValue.transmissionMode,
                 NhuAntennaInfoDedicatedtransmissionModetm1Enum);
   txMode = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "txMode", 
                  &txMode);
   if(txMode)
   {
      FILL_UINT_TKN(antennaInfo->val.explicitValue.transmissionMode,
                    txMode);
   }
   isCodeBookRestn = FALSE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "codeBookRestnPres", 
                  &isCodeBookRestn);
   if(isCodeBookRestn)
   {
      FILL_UINT_TKN(antennaInfo->val.explicitValue.codebookSubsetRestrn.choice,
                    CODEBOOKSUBSETRESTRN_N2TXANTENNA_TM3);
      FILL_BIT_STR(antennaInfo->val.explicitValue.codebookSubsetRestrn.val.n2TxAntenna_tm3,
                   2, 1, evnt);
   }
   FILL_UINT_TKN(antennaInfo->val.explicitValue.ue_TransmitAntennaSelection.choice, 0);
   FILL_UINT_TKN(antennaInfo->val.explicitValue.ue_TransmitAntennaSelection.val.setup, 0);

   /* Scheduling Request Configuration */
   schedulingRqstConfig = &(radioResCfg->physicalConfigDedicated.\
               schedulingRqstConfig);
#ifdef LTERRC_REL9
/* R9 upgrade : filling the r9 IEs*/
#ifndef RRC_REL11
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_r9.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_r9.\
         cqi_ReportConfig_v920.pres, PRSNT_NODEF);

   if(cqiMaskPres)
   {
      NHAC_FILL_U8_U32_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_r9.\
            cqi_ReportConfig_v920.cqi_Mask_r9, PRSNT_NODEF,\
            NhuCQI_ReportConfig_v920cqi_Mask_r9setupEnum);
   }
         
   isPmiRprtPres = FALSE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "pmiRprtPres", 
                  &isPmiRprtPres);
   if(isPmiRprtPres)
   {
       NHAC_FILL_U8_U32_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_r9.\
             cqi_ReportConfig_v920.pmi_RI_Report_r9, PRSNT_NODEF,\
             NhuCQI_ReportConfig_v920pmi_RI_Report_r9setupEnum);
   }

   /* filling antennaInfo_v920 IE*/      
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_r9.\
         antennaInfo_v920.pres, PRSNT_NODEF);

   isCodeBkSubsetRestnv920Pres = FALSE;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "codeBkSubsetRestnv920Pres", 
                  &isCodeBkSubsetRestnv920Pres);

   if(isCodeBkSubsetRestnv920Pres)
   {
        FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_r9.\
                antennaInfo_v920.codebookSubsetRestrn_v920.choice, CODEBOOKSUBSETRESTRN_V920_N2TXANTENNA_TM8_R9);

        FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_r9.\
                 antennaInfo_v920.codebookSubsetRestrn_v920.val.n2TxAntenna_tm8_r9,\
                 6, 1, (NhuDatReqSdus *)evnt);
   }
#else
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_1.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_1.\
         cqi_ReportConfig_v920.pres, PRSNT_NODEF);

   if(cqiMaskPres)
   {
      NHAC_FILL_U8_U32_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_1.\
            cqi_ReportConfig_v920.cqi_Mask_r9, PRSNT_NODEF,\
            NhuCQI_ReportConfig_v920cqi_Mask_r9setupEnum);
   }
         
   isPmiRprtPres = FALSE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "pmiRprtPres", 
                  &isPmiRprtPres);
   if(isPmiRprtPres)
   {
       NHAC_FILL_U8_U32_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_1.\
             cqi_ReportConfig_v920.pmi_RI_Report_r9, PRSNT_NODEF,\
             NhuCQI_ReportConfig_v920pmi_RI_Report_r9setupEnum);
   }

   /* filling antennaInfo_v920 IE*/      
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_1.\
         antennaInfo_v920.pres, PRSNT_NODEF);

   isCodeBkSubsetRestnv920Pres = FALSE;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "codeBkSubsetRestnv920Pres", 
                  &isCodeBkSubsetRestnv920Pres);

   if(isCodeBkSubsetRestnv920Pres)
   {
        FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_1.\
                antennaInfo_v920.codebookSubsetRestrn_v920.choice, CODEBOOKSUBSETRESTRN_V920_N2TXANTENNA_TM8_R9);

        FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_1.\
                 antennaInfo_v920.codebookSubsetRestrn_v920.val.n2TxAntenna_tm8_r9,\
                 6, 1, (NhuDatReqSdus *)evnt);
   }
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.antennaInfo_r10.choice,\
         0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.antennaInfo_r10.val.explicitValue_r10.\
         pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.antennaInfo_r10.val.explicitValue_r10.\
         transmissionMode_r10, NhuAntennaInfoDedicated_r10transmissionMode_r10tm1Enum);
   FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_2.antennaInfo_r10.val.explicitValue_r10.\
         codebookSubsetRestrn_r10, 255, 1, evnt);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.antennaInfo_r10.val.explicitValue_r10.\
         ue_TransmitAntennaSelection.choice, 0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.antennaInfo_r10.val.explicitValue_r10.\
         ue_TransmitAntennaSelection.val.setup, NhuAntennaInfoDedicated_r10ue_TransmitAntennaSelectionsetupclosedLoopEnum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.antennaInfoUL_r10.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.antennaInfoUL_r10.transmissionModeUL_r10,\
         NhuAntennaInfoUL_r10transmissionModeUL_r10tm1Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.antennaInfoUL_r10.fourAntennaPortActivated_r10,\
         NhuAntennaInfoUL_r10fourAntennaPortActivated_r10setupEnum);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "cifPresence", &(cifPresence));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cif_Presence_r10,\
         cifPresence); 
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportAperiodic_r10.choice,\
         0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportAperiodic_r10.val.setup.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportAperiodic_r10.\
         val.setup.cqi_ReportModeAperiodic_r10, NhuCQI_ReportModeAperiodicrm12Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportAperiodic_r10.\
         val.setup.aperiodicCSI_Trigger_r10.pres, PRSNT_NODEF );
   FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportAperiodic_r10.\
         val.setup.aperiodicCSI_Trigger_r10.trigger1_r10, 8, 1, evnt );
   FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportAperiodic_r10.\
         val.setup.aperiodicCSI_Trigger_r10.trigger2_r10, 8, 1, evnt );
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.nomPDSCH_RS_EPRE_Offset,\
        -1);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.choice,\
        0 );
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
        val.setup.pres, PRSNT_NODEF);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "cqiPUCCHResIdxr10",&(cqiPUCCHResIdxr10));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
        val.setup.cqi_PUCCH_ResourceIdx_r10, cqiPUCCHResIdxr10);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "cqiPUCCHResIdxP1r10",&(cqiPUCCHResIdxP1r10));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
        val.setup.cqi_PUCCH_ResourceIdxP1_r10, cqiPUCCHResIdxP1r10);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "cqipmiCfgIdx",&(cqipmiCfgIdx));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
        val.setup.cqi_pmi_ConfigIdx, cqipmiCfgIdx);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
        val.setup.cqi_FormatIndicatorPeriodic_r10.choice, 0);
   if(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
                 val.setup.cqi_FormatIndicatorPeriodic_r10.choice.val==0)
   {
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
          val.setup.cqi_FormatIndicatorPeriodic_r10.val.widebandCQI_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
          val.setup.cqi_FormatIndicatorPeriodic_r10.val.widebandCQI_r10.csi_ReportMode_r10,\
          NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10widebandCQI_r10csi_ReportMode_r10submode1Enum);
   }
   else
   {
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
          val.setup.cqi_FormatIndicatorPeriodic_r10.val.subbandCQI_r10.pres, PRSNT_NODEF);
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
          val.setup.cqi_FormatIndicatorPeriodic_r10.val.subbandCQI_r10.k, 1);
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
          val.setup.cqi_FormatIndicatorPeriodic_r10.val.subbandCQI_r10.periodicityFactor_r10,\
          NhuCQI_ReportPeriodic_r10setupcqi_FormatIndicatorPeriodic_r10subbandCQI_r10periodicityFactor_r10n2Enum);
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "riCfgIdx",&(riCfgIdx));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
          val.setup.ri_ConfigIdx, riCfgIdx);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "simulAckNackAndCQI",&(simulAckNackAndCQI));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
          val.setup.simultaneousAckNackAndCQI, simulAckNackAndCQI);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
          val.setup.cqi_Mask_r9, NhuCQI_ReportPeriodic_r10setupcqi_Mask_r9setupEnum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
          val.setup.csi_ConfigIdx_r10.choice, 0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
          val.setup.csi_ConfigIdx_r10.val.setup.pres, PRSNT_NODEF);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "cqipmiCfgIdx2r10",&(cqipmiCfgIdx2r10));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
          val.setup.csi_ConfigIdx_r10.val.setup.cqi_pmi_ConfigIdx2_r10, cqipmiCfgIdx2r10);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "riCfgIdx2r10",&(riCfgIdx2r10));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.cqi_ReportPeriodic_r10.\
          val.setup.csi_ConfigIdx_r10.val.setup.ri_ConfigIdx2_r10, riCfgIdx2r10);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.pmi_RI_Report_r9,\
         NhuCQI_ReportConfig_r10pmi_RI_Report_r9setupEnum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         choice, 0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.csi_MeasSubfrmSet1_r10.choice, 0);
   if(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
                  val.setup.csi_MeasSubfrmSet1_r10.choice.val==0)
   {
     FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.csi_MeasSubfrmSet1_r10.val.subframePatternFDD_r10, 40, 1, evnt );
   }
   else
   {
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.csi_MeasSubfrmSet1_r10.val.subframePatternTDD_r10.choice, 0);
     if(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
                    val.setup.csi_MeasSubfrmSet1_r10.val.subframePatternTDD_r10.choice.val==0)
     {
       FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.csi_MeasSubfrmSet1_r10.val.subframePatternTDD_r10.val.subframeConfig1_5_r10, 20, 1, evnt );
     }
     else if(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
                    val.setup.csi_MeasSubfrmSet1_r10.val.subframePatternTDD_r10.choice.val==1)
     {
       FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.csi_MeasSubfrmSet1_r10.val.subframePatternTDD_r10.val.subframeConfig0_r10, 70, 1, evnt);
     }
     else
     {
       FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.csi_MeasSubfrmSet1_r10.val.subframePatternTDD_r10.val.subframeConfig6_r10, 60, 1, evnt);
     }
   }
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.csi_MeasSubfrmSet2_r10.choice, 0);
   if(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
                  val.setup.csi_MeasSubfrmSet2_r10.choice.val==0)
   {
     FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.csi_MeasSubfrmSet2_r10.val.subframePatternFDD_r10, 40, 1, evnt);
   }
   else
   {
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.csi_MeasSubfrmSet2_r10.val.subframePatternTDD_r10.choice, 0);
     if(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
                    val.setup.csi_MeasSubfrmSet2_r10.val.subframePatternTDD_r10.choice.val==0)
     {
       FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.csi_MeasSubfrmSet2_r10.val.subframePatternTDD_r10.val.subframeConfig1_5_r10, 20, 1, evnt);
     }
     else if(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
                    val.setup.csi_MeasSubfrmSet2_r10.val.subframePatternTDD_r10.choice.val==1)
     {
       FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.csi_MeasSubfrmSet2_r10.val.subframePatternTDD_r10.val.subframeConfig0_r10, 70, 1, evnt);
     }
     else
     {
       FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_2.cqi_ReportConfig_r10.csi_SubfrmPatternConfig_r10.\
         val.setup.csi_MeasSubfrmSet2_r10.val.subframePatternTDD_r10.val.subframeConfig6_r10, 60, 1, evnt);
     }
   }
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.csi_RS_Config_r10.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.csi_RS_Config_r10.csi_RS_r10.choice, 0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.csi_RS_Config_r10.csi_RS_r10.val.setup.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.csi_RS_Config_r10.csi_RS_r10.val.setup.\
         antennaPortsCount_r10, NhuCSI_RS_Config_r10csi_RS_r10setupantennaPortsCount_r10an1Enum);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "resourceConfigr10",&(resourceConfigr10));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.csi_RS_Config_r10.csi_RS_r10.val.setup.\
         resourceConfig_r10, resourceConfigr10);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "subframeConfigr10",&(subframeConfigr10));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.csi_RS_Config_r10.csi_RS_r10.val.setup.\
         subframeConfig_r10, subframeConfigr10);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_S16, "pcr10",&(pcr10));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.csi_RS_Config_r10.csi_RS_r10.val.setup.\
         p_C_r10, pcr10);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.csi_RS_Config_r10.zeroTxPowerCSI_RS_r10.choice,0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.csi_RS_Config_r10.zeroTxPowerCSI_RS_r10.val.setup.\
         pres, PRSNT_NODEF);
   FILL_BIT_STR(radioResCfg->physicalConfigDedicated.extaddgrp_2.csi_RS_Config_r10.zeroTxPowerCSI_RS_r10.val.setup.\
         zeroTxPowerResourceConfigLst_r10, 16, 1, evnt);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "zeroTxPwrSubfrmCfgr10",&(zeroTxPwrSubfrmCfgr10));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.csi_RS_Config_r10.zeroTxPowerCSI_RS_r10.val.setup.\
         zeroTxPowerSubfrmConfig_r10, zeroTxPwrSubfrmCfgr10);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.choice,\
         0);
   if(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.choice.val==0)
   {
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         format3_r10.pres, PRSNT_NODEF );
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         format3_r10.n3PUCCH_AN_Lst_r10.noComp, 1);
     CMXTA_GET_MEM(evnt,(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.\
         pucch_Format_r10.val.format3_r10.n3PUCCH_AN_Lst_r10.noComp.val)*
         (sizeof(NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10n3PUCCH_AN_Lst_r10Member)),\
         &(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
                     format3_r10.n3PUCCH_AN_Lst_r10.member));
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "n3PUCCHAnLstMem",&(n3PUCCHAnLstMem));
     for(idx=0; idx<radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
                    format3_r10.n3PUCCH_AN_Lst_r10.noComp.val; idx++)
     {
       FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
                      format3_r10.n3PUCCH_AN_Lst_r10.member[idx], n3PUCCHAnLstMem);
     }
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         format3_r10.twoAntennaPortActivatedPUCCH_Format3_r10.choice, 0 );
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         format3_r10.twoAntennaPortActivatedPUCCH_Format3_r10.val.setup.pres, PRSNT_NODEF);
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         format3_r10.twoAntennaPortActivatedPUCCH_Format3_r10.val.setup.n3PUCCH_AN_LstP1_r10.noComp,1);
     CMXTA_GET_MEM(evnt,(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         format3_r10.twoAntennaPortActivatedPUCCH_Format3_r10.val.setup.n3PUCCH_AN_LstP1_r10.noComp.val)*
         (sizeof(NhuPUCCH_ConfigDedicated_v1020pucch_Format_r10format3_r10twoAntennaPortActivatedPUCCH_Format3_r10setupn3PUCCH_AN_LstP1_r10Member)),
         &(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         format3_r10.twoAntennaPortActivatedPUCCH_Format3_r10.val.setup.n3PUCCH_AN_LstP1_r10.member));
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "n3PUCCHAnLstP1Mem",&(n3PUCCHAnLstP1Mem));
     for(idx=0; idx<radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
               format3_r10.twoAntennaPortActivatedPUCCH_Format3_r10.val.setup.n3PUCCH_AN_LstP1_r10.noComp.val; idx++)
     {
       FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
                      format3_r10.twoAntennaPortActivatedPUCCH_Format3_r10.val.setup.n3PUCCH_AN_LstP1_r10.member[idx],\
                      n3PUCCHAnLstP1Mem);
     }
   }
   else
   {
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         channelSelection_r10.pres, PRSNT_NODEF );
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         channelSelection_r10.n1PUCCH_AN_CS_r10.choice, 0);
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         channelSelection_r10.n1PUCCH_AN_CS_r10.val.setup.pres, PRSNT_NODEF);
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         channelSelection_r10.n1PUCCH_AN_CS_r10.val.setup.n1PUCCH_AN_CS_Lst_r10.noComp, 1);
     CMXTA_GET_MEM(evnt,(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.\
          val.channelSelection_r10.n1PUCCH_AN_CS_r10.val.setup.n1PUCCH_AN_CS_Lst_r10.noComp.val)*
          (sizeof(NhuN1PUCCH_AN_CS_r10)),&(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.\
          pucch_Format_r10.val.channelSelection_r10.n1PUCCH_AN_CS_r10.val.setup.n1PUCCH_AN_CS_Lst_r10.member));
     for(idx=0; idx<radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
                    channelSelection_r10.n1PUCCH_AN_CS_r10.val.setup.n1PUCCH_AN_CS_Lst_r10.noComp.val; idx++)
     {
       FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         channelSelection_r10.n1PUCCH_AN_CS_r10.val.setup.n1PUCCH_AN_CS_Lst_r10.member[idx].noComp, 1);
       CMXTA_GET_MEM(evnt,(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
         channelSelection_r10.n1PUCCH_AN_CS_r10.val.setup.n1PUCCH_AN_CS_Lst_r10.member[idx].noComp.val)*\
         (sizeof(NhuN1PUCCH_AN_CS_r10Member)),&(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.\
         pucch_Format_r10.val.channelSelection_r10.n1PUCCH_AN_CS_r10.val.setup.n1PUCCH_AN_CS_Lst_r10.member[idx].member));
       for(idx1=0; idx1<radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
                    channelSelection_r10.n1PUCCH_AN_CS_r10.val.setup.n1PUCCH_AN_CS_Lst_r10.member[idx].noComp.val; idx1++)
       {
         FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.pucch_Format_r10.val.\
           channelSelection_r10.n1PUCCH_AN_CS_r10.val.setup.n1PUCCH_AN_CS_Lst_r10.member[idx].member[idx1], 1);
       }
     }
   }
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.twoAntennaPortActivatedPUCCH_Format1a1b_r10,\
        NhuPUCCH_ConfigDedicated_v1020twoAntennaPortActivatedPUCCH_Format1a1b_r10trueEnum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.simultaneousPUCCH_PUSCH_r10,\
         NhuPUCCH_ConfigDedicated_v1020simultaneousPUCCH_PUSCH_r10trueEnum);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "n1PUCCHAnRepP1",&(n1PUCCHAnRepP1));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pucch_ConfigDedicated_v1020.n1PUCCH_AN_RepP1_r10,\
         n1PUCCHAnRepP1);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pusch_ConfigDedicated_v1020.pres, PRSNT_NODEF );
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pusch_ConfigDedicated_v1020.betaOffsetMC_r10.pres, PRSNT_NODEF );
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "AckIdxMc",&(AckIdxMc));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pusch_ConfigDedicated_v1020.betaOffsetMC_r10.\
         betaOffset_ACK_Idx_MC_r10, AckIdxMc);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "riIdxMc",&(riIdxMc));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pusch_ConfigDedicated_v1020.betaOffsetMC_r10.\
         betaOffset_RI_Idx_MC_r10, riIdxMc);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "cqiIdxMc",&(cqiIdxMc));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pusch_ConfigDedicated_v1020.betaOffsetMC_r10.\
         betaOffset_CQI_Idx_MC_r10, cqiIdxMc);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pusch_ConfigDedicated_v1020.groupHoppingDisabled_r10,\
         NhuPUSCH_ConfigDedicated_v1020groupHoppingDisabled_r10trueEnum );
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.pusch_ConfigDedicated_v1020.dmrs_WithOCC_Activated_r10,\
         NhuPUSCH_ConfigDedicated_v1020dmrs_WithOCC_Activated_r10trueEnum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.schedulingRqstConfig_v1020.pres,\
         PRSNT_NODEF);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, "srPucchResIdxP1",&(srPucchResIdxP1));
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.schedulingRqstConfig_v1020.sr_PUCCH_ResourceIdxP1_r10,\
         srPucchResIdxP1);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicated_v1020.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicated_v1020.srs_AntennaPort_r10,\
         NhuSRS_AntennaPortan1Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.choice,\
         0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ConfigIdxAp_r10, 0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ConfigApDCI_Format4_r10.noComp, 1);
   CMXTA_GET_MEM(evnt,(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.\
         setup.srs_ConfigApDCI_Format4_r10.noComp.val)*(sizeof(NhuSRS_ConfigAp_r10)),\
         &(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
                       srs_ConfigApDCI_Format4_r10.member));
   for(idx=0; idx<radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
                  srs_ConfigApDCI_Format4_r10.noComp.val; idx++)
   {
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ConfigApDCI_Format4_r10.member[idx].pres, PRSNT_NODEF);
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ConfigApDCI_Format4_r10.member[idx].srs_AntennaPortAp_r10, NhuSRS_AntennaPortan1Enum);
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ConfigApDCI_Format4_r10.member[idx].srs_BandwidthAp_r10,\
         NhuSRS_ConfigAp_r10srs_BandwidthAp_r10bw0Enum);
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ConfigApDCI_Format4_r10.member[idx].freqDomainPositionAp_r10, 0);
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ConfigApDCI_Format4_r10.member[idx].transmissionCombAp_r10, 0);
     FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ConfigApDCI_Format4_r10.member[idx].cyclicShiftAp_r10, NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs0Enum);
   }
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.choice, 0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.srs_ConfigApDCI_Format0_r10.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.srs_ConfigApDCI_Format0_r10.srs_AntennaPortAp_r10, NhuSRS_AntennaPortan1Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.srs_ConfigApDCI_Format0_r10.srs_BandwidthAp_r10, NhuSRS_ConfigAp_r10srs_BandwidthAp_r10bw0Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.srs_ConfigApDCI_Format0_r10.freqDomainPositionAp_r10, 0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.srs_ConfigApDCI_Format0_r10.transmissionCombAp_r10, 0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.srs_ConfigApDCI_Format0_r10.cyclicShiftAp_r10,\
         NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs0Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.srs_ConfigApDCI_Format1a2b2c_r10.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.srs_ConfigApDCI_Format1a2b2c_r10.srs_AntennaPortAp_r10, NhuSRS_AntennaPortan1Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.srs_ConfigApDCI_Format1a2b2c_r10.srs_BandwidthAp_r10,\
         NhuSRS_ConfigAp_r10srs_BandwidthAp_r10bw0Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.srs_ConfigApDCI_Format1a2b2c_r10.freqDomainPositionAp_r10, 0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.srs_ConfigApDCI_Format1a2b2c_r10.transmissionCombAp_r10, 0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.soundingRS_UL_ConfigDedicatedAperiodic_r10.val.setup.\
         srs_ActivateAp_r10.val.setup.srs_ConfigApDCI_Format1a2b2c_r10.cyclicShiftAp_r10,\
         NhuSRS_ConfigAp_r10cyclicShiftAp_r10cs0Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.uplinkPowerCntrlDedicated_v1020.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.uplinkPowerCntrlDedicated_v1020.deltaTxD_OffsetLstPUCCH_r10.\
         pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.uplinkPowerCntrlDedicated_v1020.deltaTxD_OffsetLstPUCCH_r10.\
         deltaTxD_OffsetPUCCH_Format1_r10, NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1_r10dB0Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.uplinkPowerCntrlDedicated_v1020.deltaTxD_OffsetLstPUCCH_r10.\
         deltaTxD_OffsetPUCCH_Format1a1b_r10, NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format1a1b_r10dB0Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.uplinkPowerCntrlDedicated_v1020.deltaTxD_OffsetLstPUCCH_r10.\
         deltaTxD_OffsetPUCCH_Format22a2b_r10, NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format22a2b_r10dB0Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.uplinkPowerCntrlDedicated_v1020.deltaTxD_OffsetLstPUCCH_r10.\
         deltaTxD_OffsetPUCCH_Format3_r10, NhuDeltaTxD_OffsetLstPUCCH_r10deltaTxD_OffsetPUCCH_Format3_r10dB0Enum);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_2.uplinkPowerCntrlDedicated_v1020.pSRS_OffsetAp_r10,\
         0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_3.pres, PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_3.additionalSpectrumEmissionCA_r10.choice, 0);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_3.additionalSpectrumEmissionCA_r10.val.setup.pres,\
         PRSNT_NODEF);
   FILL_UINT_TKN(radioResCfg->physicalConfigDedicated.extaddgrp_3.additionalSpectrumEmissionCA_r10.val.setup.\
         additionalSpectrumEmissionPCell_r10, 0);

#endif
#endif
   RETVALUE(CMXTA_ERR_NONE);
  
} /* End of nhAcUtlFillNhuRRCPhyCfgDedi */

/*
*
*       Fun:   PHR
*
*       Desc:  This function fills Security Configuration in the message required
*              for UE 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuSecurityCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuSecAlgorithmConfig     *securityCfg
)
#else
PUBLIC S16 nhAcUtlFillNhuSecurityCfg(tcCb, spCb, securityCfg)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuSecAlgorithmConfig     *securityCfg;
#endif
{
   U8    integrityAlgo=1, cipheringAlgo=1;

   TRC2(nhAcUtlFillNhuSecurityCfg);

   FILL_UINT_TKN(securityCfg->pres, PRSNT_NODEF);

   FILL_UINT_TKN(securityCfg->integrityProtAlgorithm, 
                     NhuSecAlgorithmConfigintegrityProtAlgorithmeia1Enum);

   /* Read Integrity algorithm from xml */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "integrityAlgo",
                  &(integrityAlgo));

   if (1 != integrityAlgo)
   {
      securityCfg->integrityProtAlgorithm.pres = NOTPRSNT;
   }

   FILL_UINT_TKN(securityCfg->cipheringAlgorithm, 
                     NhuSecAlgorithmConfigcipheringAlgorithmeea1Enum);

   /* Read Ciphering algorithm from xml */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "cipheringAlgo",
                  &(cipheringAlgo));

   if (1 != cipheringAlgo)
   {
      securityCfg->cipheringAlgorithm.pres = NOTPRSNT;
   }

   RETVALUE(CMXTA_ERR_NONE);

} /* End of nhAcUtlFillNhuSecurityCfg */

/*
*
*       Fun:   nhAcUtlFillNhuUlUmRlc
*
*       Desc:  This function fills Uplink RLC Configuration for UM Mode
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuUlUmRlc
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuUL_UM_RLC  *ulUmRlc
)
#else
PUBLIC S16 nhAcUtlFillNhuUlUmRlc(tcCb, spCb, ulUmRlc)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuUL_UM_RLC  *ulUmRlc;
#endif
{
   TRC2(nhAcUtlFillNhuUlUmRlc);

   FILL_UINT_TKN(ulUmRlc->pres, PRSNT_NODEF);
   FILL_UINT_TKN(ulUmRlc->sn_FieldLength, NhuSN_FieldLengthsize5Enum);

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nhAcUtlFillNhuDlUmRlc
*
*       Desc:  This function fills Downlink RLC Configuration for UM Mode
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuDlUmRlc
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDL_UM_RLC  *dlUmRlc
)
#else
PUBLIC S16 nhAcUtlFillNhuDlUmRlc(tcCb, spCb, dlUmRlc)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuDL_UM_RLC  *dlUmRlc;
#endif
{
   TRC2(nhAcUtlFillNhuDlUmRlc);

   FILL_UINT_TKN(dlUmRlc->pres, PRSNT_NODEF);
   FILL_UINT_TKN(dlUmRlc->sn_FieldLength, NhuSN_FieldLengthsize5Enum);

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nhAcUtlFillNhuPDCPDrbCfg
*
*       Desc:  This function fills PDCP config in DRB List 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuPDCPDrbCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuPDCP_Config   *pdcpCfg,
Ptr           evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuPDCPDrbCfg(tcCb, spCb, pdcpCfg, evnt)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuPDCP_Config   *pdcpCfg;
Ptr           evnt;
#endif
{
   U8       pdcpHdrCompPres = TRUE;
   U8       disTimAbsent = 0;
   U8       pdcpCfgRlcUmAbsent = 1;
   U8       pdcpCfgRlcAmAbsent = 0;


   TRC2(nhAcUtlFillNhuPDCPDrbCfg);

   FILL_UINT_TKN(pdcpCfg->pres, PRSNT_NODEF);
   FILL_UINT_TKN(pdcpCfg->rlc_AM.pres, PRSNT_NODEF);
   FILL_UINT_TKN(pdcpCfg->rlc_AM.statusReportReqd, 1);
   FILL_UINT_TKN(pdcpCfg->headerCompression.choice, HEADERCOMPRESSION_ROHC);
   FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.pres, PRSNT_NODEF);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "pdcpHdrCompPres", 
                  &pdcpHdrCompPres);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "disTimAbsent", 
                  &disTimAbsent);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "pdcpCfgRlcUmAbsent", 
                  &pdcpCfgRlcUmAbsent);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "pdcpCfgRlcAmAbsent", 
                  &pdcpCfgRlcAmAbsent);

   if(disTimAbsent)
   {
       NHAC_FILL_U8_U32_TKN(pdcpCfg->discardTimer, NOTPRSNT, NOTPRSNT);
   }
   else
   {
      FILL_UINT_TKN(pdcpCfg->discardTimer, NhuPDCP_ConfigdiscardTimerms50Enum)
   }

   if(pdcpCfgRlcUmAbsent)
   {
       NHAC_FILL_U8_U32_TKN(pdcpCfg->rlc_UM.pres, NOTPRSNT, NOTPRSNT);
   }
   else
   {
      FILL_UINT_TKN(pdcpCfg->rlc_UM.pres, PRSNT_NODEF);
      FILL_UINT_TKN(pdcpCfg->rlc_UM.pdcp_SN_Size,
            NhuPDCP_Configrlc_UMpdcp_SN_Sizelen7bitsEnum);
   }

   if(pdcpCfgRlcAmAbsent)
   {
       NHAC_FILL_U8_U32_TKN(pdcpCfg->rlc_AM.pres, NOTPRSNT, NOTPRSNT);
   }
   else
   {
      FILL_UINT_TKN(pdcpCfg->rlc_AM.pres, PRSNT_NODEF);
      FILL_UINT_TKN(pdcpCfg->rlc_AM.statusReportReqd,
            FALSE);
   }

   if(pdcpHdrCompPres == FALSE)
   {
      FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.pres, NOTPRSNT);
   }
   else
   {
      FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.maxCID, 15);
      FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.profiles.pres,
                    PRSNT_NODEF);

      FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.profiles.profile0x0001,
                    1);
      FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.profiles.profile0x0002,
                    1);
      FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.profiles.profile0x0003,
                    1);
      FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.profiles.profile0x0004,
                    1);
      FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.profiles.profile0x0006,
                    1);
      FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.profiles.profile0x0101,
                    1);
      FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.profiles.profile0x0102,
                    1);
      FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.profiles.profile0x0103,
                    1);
      FILL_UINT_TKN(pdcpCfg->headerCompression.val.rohc.profiles.profile0x0104,
                    1);
   }
#ifdef RRC_REL11
      FILL_UINT_TKN(pdcpCfg->extaddgrp_1.pres, PRSNT_NODEF);
      FILL_UINT_TKN(pdcpCfg->extaddgrp_1.rn_IntegrityProtection_r10, 
            NhuPDCP_Configextaddgrp_1rn_IntegrityProtection_r10enabledEnum);
      
#endif
   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nhAcUtlFillNhuRLCDrbCfg
*
*       Desc:  This function fills RLC config in DRB List 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuRLCDrbCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuRLC_Config    *rlcCfg,
Ptr           evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuRLCDrbCfg(tcCb, spCb, rlcCfg, evnt)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuRLC_Config    *rlcCfg;
Ptr           evnt;
#endif
{
   Bool rlcCfgUlUmDir;

   TRC2(nhAcUtlFillNhuRLCDrbCfg);

   FILL_UINT_TKN(rlcCfg->choice, RLC_CONFIG_AM);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "rlcCfgMode", 
                  &(rlcCfg->choice.val));

   if(rlcCfg->choice.val == RLC_CONFIG_AM)
   {
      FILL_UINT_TKN(rlcCfg->val.am.pres, PRSNT_NODEF);
      FILL_UINT_TKN(rlcCfg->val.am.ul_AM_RLC.pres, PRSNT_NODEF);
      FILL_UINT_TKN(rlcCfg->val.am.ul_AM_RLC.t_PollRetransmit, 
                    NhuT_PollRetransmitms5Enum);
      FILL_UINT_TKN(rlcCfg->val.am.ul_AM_RLC.pollPDU, 
                    NhuPollPDUp4Enum);
      FILL_UINT_TKN(rlcCfg->val.am.ul_AM_RLC.pollByte,1);
      FILL_UINT_TKN(rlcCfg->val.am.ul_AM_RLC.maxRetxThreshold, 
                    NhuUL_AM_RLCmaxRetxThresholdt1Enum);
      FILL_UINT_TKN(rlcCfg->val.am.dl_AM_RLC.pres, PRSNT_NODEF);
      FILL_UINT_TKN(rlcCfg->val.am.dl_AM_RLC.t_Reordering, 
                    NhuT_Reorderingms0Enum);
      FILL_UINT_TKN(rlcCfg->val.am.dl_AM_RLC.t_StatusProhibit, 
                    NhuT_StatusProhibitms0Enum);
   }
   else if(rlcCfg->choice.val == RLC_CONFIG_UM_BI_DIRECTIONAL)
   {
      FILL_UINT_TKN(rlcCfg->val.um_Bi_Directional.pres, PRSNT_NODEF);
      nhAcUtlFillNhuUlUmRlc(tcCb, spCb, 
                            &(rlcCfg->val.um_Bi_Directional.ul_UM_RLC));
      nhAcUtlFillNhuDlUmRlc(tcCb, spCb, 
                            &(rlcCfg->val.um_Bi_Directional.dl_UM_RLC));
   }
   else if(rlcCfg->choice.val == RLC_CONFIG_UM_UNI_DIRECTIONAL_UL)
   {
      rlcCfgUlUmDir = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL, "rlcCfgUlUmDir", 
                  &(rlcCfgUlUmDir));
      
      if(rlcCfgUlUmDir == TRUE)
      {
         FILL_UINT_TKN(rlcCfg->val.um_Uni_Directional_UL.pres, PRSNT_NODEF);
         nhAcUtlFillNhuUlUmRlc(tcCb, spCb, 
                            &(rlcCfg->val.um_Uni_Directional_UL.ul_UM_RLC));
      }
   }
   else if(rlcCfg->choice.val == RLC_CONFIG_UM_UNI_DIRECTIONAL_DL)
   {
      FILL_UINT_TKN(rlcCfg->val.um_Uni_Directional_DL.pres, PRSNT_NODEF);
      nhAcUtlFillNhuDlUmRlc(tcCb, spCb, 
                            &(rlcCfg->val.um_Uni_Directional_DL.dl_UM_RLC));
   }
   
   RETVALUE(CMXTA_ERR_NONE);
}

/**************** Cell Config Related functions **************/
/*
*
*       Fun:   nhAcUtlFillCellRbCfg
*
*       Desc:  This function Cell RB Configuration 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillCellRbCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuRbCfgList  **rbCfgList
)
#else
PUBLIC S16 nhAcUtlFillCellRbCfg(tcCb, spCb, rbCfgList)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuRbCfgList  **rbCfgList;
#endif
{
   NhuRbCfgList *lclRbCfgList;
   U8 dlrlcCfgType;
   U8 ulrlcCfgType;
   Bool inValidLogChTrChMap;
   Bool dupCcchSchMap;
   Bool dupBcchBchMap;
   Bool dupPcchPchMap;
   Bool dupBcchDlSchMap;

   TRC2(nhAcUtlFillCellRbCfg);

   lclRbCfgList = *rbCfgList;
   
   /* Filling RB1 for CCCH to UL-SCH Mapping */
   {
      lclRbCfgList->rbCfgInfoList[0].rbId.rbId =  CCCH_RBID2;
      /* Bit Mask (UL, DL Cfg present) */ 
      lclRbCfgList->rbCfgInfoList[0].rbCfgBitMsk |= NHU_RB_CFG_UL;

      /* UlRbCfg */
      {
         /* Bit mask calculate properly */
         lclRbCfgList->rbCfgInfoList[0].ulRbCfg.ulRbBitMsk |= 
                                                        NHU_RB_CFG_LOGCH_MAP_UL;
         lclRbCfgList->rbCfgInfoList[0].ulRbCfg.ulRbBitMsk |= 
                                                        NHU_RB_CFG_RLC_MODE_UL;

         /* ulLogChMapInfo */
         {
            /* Transport Channel type */
            lclRbCfgList->rbCfgInfoList[0].ulRbCfg.ulLogChMap.trChType = 
                                                        CM_LTE_TRCH_UL_SCH;
            inValidLogChTrChMap = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_BOOL,"inValidUlLogChTrChMap",
                           &inValidLogChTrChMap);
            if(inValidLogChTrChMap)
            {
               /* Transport Channel type */
               lclRbCfgList->rbCfgInfoList[0].ulRbCfg.ulLogChMap.trChType = 
                                                        CM_LTE_TRCH_DL_SCH;
            }
            dupCcchSchMap = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_BOOL,"dupCcchDlSchMap",
                           &dupCcchSchMap);
            if(dupCcchSchMap)
            {
               lclRbCfgList->rbCfgInfoList[0].rbCfgBitMsk |= NHU_RB_CFG_DL;
               /* Bit mask calculate properly */
               lclRbCfgList->rbCfgInfoList[0].dlRbCfg.dlRbBitMsk |=
                                                        NHU_RB_CFG_LOGCH_MAP_DL;
               /* Transport Channel type */
               lclRbCfgList->rbCfgInfoList[0].dlRbCfg.dlLogChMap.trChType = 
                                                        CM_LTE_TRCH_DL_SCH;
            }

            /* Logical Channel Id and Type */
            lclRbCfgList->rbCfgInfoList[0].lcId.lcId =
                                                             CCCH_UL_SCH_ID;
            lclRbCfgList->rbCfgInfoList[0].lcId.logChType = 
                                                              CM_LTE_LCH_CCCH;

            /* Fill Logical Channel Cfg */
            nhAcUtlFillUlLogChCfg(tcCb, spCb,
                         &(lclRbCfgList->rbCfgInfoList[0].ulRbCfg.ulLogChMap));
         }
         /* ulRlcMode */
         {
            ulrlcCfgType = NHU_CFG_TYPE_EXPLICIT;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U8,"ulrlcCfgType",
                           &ulrlcCfgType);
            lclRbCfgList->rbCfgInfoList[0].ulRbCfg.ulRlcMode.rlcCfgType = 
                                                         ulrlcCfgType;
            lclRbCfgList->rbCfgInfoList[0].ulRbCfg.ulRlcMode.mode = NHU_RLC_MODE_TM;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ulRlcMode",
                  &lclRbCfgList->rbCfgInfoList[0].ulRbCfg.ulRlcMode.mode);
            nhAcUtlFillUlRlcModeInfo(tcCb, spCb,
                             &(lclRbCfgList->rbCfgInfoList[0].ulRbCfg.ulRlcMode));
         } /* ulRlcMode */
      }
   }

   /* Filling RB2 for CCCH to DL-SCH Mapping */
   {
      lclRbCfgList->rbCfgInfoList[1].rbId.rbId =  CCCH_RBID1;
      /* Bit Mask (UL, DL Cfg present) */ 
      lclRbCfgList->rbCfgInfoList[1].rbCfgBitMsk |= NHU_RB_CFG_DL;

      /* DlRbCfg */
      {
         lclRbCfgList->rbCfgInfoList[1].dlRbCfg.dlRbBitMsk |= 
                                                        NHU_RB_CFG_LOGCH_MAP_DL;
         lclRbCfgList->rbCfgInfoList[1].dlRbCfg.dlRbBitMsk |=
                                                        NHU_RB_CFG_RLC_MODE_DL;
         /* dlLogChMapInfo */
         {
            /* Logical Channel ID and type */
            lclRbCfgList->rbCfgInfoList[1].lcId.lcId = 
                                                             CCCH_DL_SCH_ID;
            lclRbCfgList->rbCfgInfoList[1].lcId.logChType = 
                                                             CM_LTE_LCH_CCCH;
            /* Transport Channel Type */
            lclRbCfgList->rbCfgInfoList[1].dlRbCfg.dlLogChMap.trChType = 
                                                             CM_LTE_TRCH_DL_SCH;
            inValidLogChTrChMap = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_BOOL,"inValidDlLogChTrChMap",
                           &inValidLogChTrChMap);
            if(inValidLogChTrChMap)
            {
               /* Transport Channel type */
               lclRbCfgList->rbCfgInfoList[1].dlRbCfg.dlLogChMap.trChType = 
                                                        CM_LTE_TRCH_UL_SCH;
            }
            dupCcchSchMap = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_BOOL,"dupCcchUlSchMap",
                           &dupCcchSchMap);
            if(dupCcchSchMap)
            {
               lclRbCfgList->rbCfgInfoList[1].rbCfgBitMsk |= NHU_RB_CFG_UL;
               /* Bit mask calculate properly */
               lclRbCfgList->rbCfgInfoList[1].ulRbCfg.ulRbBitMsk |=
                                                        NHU_RB_CFG_LOGCH_MAP_UL;
               lclRbCfgList->rbCfgInfoList[1].rbCfgBitMsk |= NHU_RB_CFG_UL;
               /* Transport Channel type */
               lclRbCfgList->rbCfgInfoList[1].ulRbCfg.ulLogChMap.trChType = 
                                                        CM_LTE_TRCH_UL_SCH;

            }
            dupBcchBchMap = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_BOOL,"dupBcchBchMap",
                           &dupBcchBchMap);
            if(dupBcchBchMap)
            {
               lclRbCfgList->rbCfgInfoList[1].lcId.logChType = 
                                                              CM_LTE_LCH_BCCH;
               /* Transport Channel type */
               lclRbCfgList->rbCfgInfoList[1].dlRbCfg.dlLogChMap.trChType = 
                                                        CM_LTE_TRCH_BCH;
            }
            dupPcchPchMap = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_BOOL,"dupPcchPchMap",
                           &dupPcchPchMap);
            if(dupPcchPchMap)
            {
               lclRbCfgList->rbCfgInfoList[1].lcId.logChType = 
                                                              CM_LTE_LCH_PCCH;
               /* Transport Channel type */
               lclRbCfgList->rbCfgInfoList[1].dlRbCfg.dlLogChMap.trChType = 
                                                        CM_LTE_TRCH_PCH;
            }
            dupBcchDlSchMap = 0;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_BOOL,"dupBcchDlSchMap",
                           &dupBcchDlSchMap);
            if(dupBcchDlSchMap)
            {
               lclRbCfgList->rbCfgInfoList[1].lcId.logChType = 
                                                              CM_LTE_LCH_BCCH;
               /* Transport Channel type */
               lclRbCfgList->rbCfgInfoList[1].dlRbCfg.dlLogChMap.trChType = 
                                                        CM_LTE_TRCH_DL_SCH;
            }
         }
         /* DL-RLC mode */
         {
            dlrlcCfgType = NHU_CFG_TYPE_EXPLICIT;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U8,"dlrlcCfgType",
                           &dlrlcCfgType);
            lclRbCfgList->rbCfgInfoList[1].dlRbCfg.dlRlcMode.rlcCfgType = 
                                                          dlrlcCfgType;
            lclRbCfgList->rbCfgInfoList[1].dlRbCfg.dlRlcMode.mode = NHU_RLC_MODE_TM;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "dlRlcMode",
                  &lclRbCfgList->rbCfgInfoList[1].dlRbCfg.dlRlcMode.mode);
            nhAcUtlFillDlRlcModeInfo(tcCb, spCb,
                           &(lclRbCfgList->rbCfgInfoList[1].dlRbCfg.dlRlcMode));
         }
      }
   }

   /* Filling RB3 for BCCH to DL-BCH Mapping */
   {
      lclRbCfgList->rbCfgInfoList[2].rbId.rbId =  BCCH_RBID1;
      /* Bit Mask (UL, DL Cfg present) */ 
      lclRbCfgList->rbCfgInfoList[2].rbCfgBitMsk |= NHU_RB_CFG_DL;
       
      /* DlRbCfg */
      {
         lclRbCfgList->rbCfgInfoList[2].dlRbCfg.dlRbBitMsk |= 
                                                       NHU_RB_CFG_LOGCH_MAP_DL;
         lclRbCfgList->rbCfgInfoList[2].dlRbCfg.dlRbBitMsk |= 
                                                       NHU_RB_CFG_RLC_MODE_DL;
         /* dlLogChMapInfo */
         {
            /* Logical Channel ID and type */
            lclRbCfgList->rbCfgInfoList[2].lcId.lcId = 
                                                              BCCH_DL_BCH_ID;
            lclRbCfgList->rbCfgInfoList[2].lcId.logChType = 
                                                              CM_LTE_LCH_BCCH;
            /* Transport Channel Type */
            lclRbCfgList->rbCfgInfoList[2].dlRbCfg.dlLogChMap.trChType =
                                                              CM_LTE_TRCH_BCH;
         }
         /* DL-RLC mode */
         {
            dlrlcCfgType = NHU_CFG_TYPE_EXPLICIT;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U8,"dlrlcCfgType",
                           &dlrlcCfgType);
            lclRbCfgList->rbCfgInfoList[2].dlRbCfg.dlRlcMode.rlcCfgType = 
                                                        dlrlcCfgType;
            lclRbCfgList->rbCfgInfoList[2].dlRbCfg.dlRlcMode.mode = NHU_RLC_MODE_TM;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "dlRlcMode",
                  &lclRbCfgList->rbCfgInfoList[2].dlRbCfg.dlRlcMode.mode);
            nhAcUtlFillDlRlcModeInfo(tcCb, spCb,
                          &(lclRbCfgList->rbCfgInfoList[2].dlRbCfg.dlRlcMode));
         }
      }
   }

   /* Filling RB4 for BCCH to DL-SCH Mapping */
   {
      lclRbCfgList->rbCfgInfoList[3].rbId.rbId =  BCCH_RBID2;
      /* Bit Mask (UL, DL Cfg present) */ 
      lclRbCfgList->rbCfgInfoList[3].rbCfgBitMsk |= NHU_RB_CFG_DL;
       
      /* DlRbCfg */
      {
         lclRbCfgList->rbCfgInfoList[3].dlRbCfg.dlRbBitMsk |= 
                                                        NHU_RB_CFG_LOGCH_MAP_DL;
         lclRbCfgList->rbCfgInfoList[3].dlRbCfg.dlRbBitMsk |= 
                                                        NHU_RB_CFG_RLC_MODE_DL;
         /* dlLogChMapInfo */
         {
            /* Logical Channel ID and type */
            lclRbCfgList->rbCfgInfoList[3].lcId.lcId = 
                                                        BCCH_DL_SCH_ID1;
            lclRbCfgList->rbCfgInfoList[3].lcId.logChType = 
                                                        CM_LTE_LCH_BCCH;
            /* Transport Channel Type */
            lclRbCfgList->rbCfgInfoList[3].dlRbCfg.dlLogChMap.trChType = 
                                                        CM_LTE_TRCH_DL_SCH;
         }
         /* DL-RLC mode */
         {
            dlrlcCfgType = NHU_CFG_TYPE_EXPLICIT;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U8,"dlrlcCfgType",
                           &dlrlcCfgType);
            lclRbCfgList->rbCfgInfoList[3].dlRbCfg.dlRlcMode.rlcCfgType =
                                                        dlrlcCfgType;
            lclRbCfgList->rbCfgInfoList[3].dlRbCfg.dlRlcMode.mode = NHU_RLC_MODE_TM;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "dlRlcMode",
                  &lclRbCfgList->rbCfgInfoList[3].dlRbCfg.dlRlcMode.mode);
            nhAcUtlFillDlRlcModeInfo(tcCb, spCb,
                           &(lclRbCfgList->rbCfgInfoList[3].dlRbCfg.dlRlcMode));
         }
      }
   }

   /* Filling RB5 for BCCH to DL-SCH Mapping instance 2*/
   {
      lclRbCfgList->rbCfgInfoList[4].rbId.rbId =  BCCH_RBID3;
      /* Bit Mask (UL, DL Cfg present) */ 
      lclRbCfgList->rbCfgInfoList[4].rbCfgBitMsk |= NHU_RB_CFG_DL;
       
      /* DlRbCfg */
      {
         lclRbCfgList->rbCfgInfoList[4].dlRbCfg.dlRbBitMsk |= 
                                                        NHU_RB_CFG_LOGCH_MAP_DL;
         lclRbCfgList->rbCfgInfoList[4].dlRbCfg.dlRbBitMsk |= 
                                                        NHU_RB_CFG_RLC_MODE_DL;
         /* dlLogChMapInfo */
         {
            /* Logical Channel ID and type */
            lclRbCfgList->rbCfgInfoList[4].lcId.lcId = 
                                                        BCCH_DL_SCH_ID2;
            lclRbCfgList->rbCfgInfoList[4].lcId.logChType = 
                                                        CM_LTE_LCH_BCCH;
            /* Transport Channel Type */
            lclRbCfgList->rbCfgInfoList[4].dlRbCfg.dlLogChMap.trChType = 
                                                        CM_LTE_TRCH_DL_SCH;
         }
         /* DL-RLC mode */
         {
            dlrlcCfgType = NHU_CFG_TYPE_EXPLICIT;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U8,"dlrlcCfgType",
                           &dlrlcCfgType);
            lclRbCfgList->rbCfgInfoList[4].dlRbCfg.dlRlcMode.rlcCfgType =
                                                        dlrlcCfgType;
            lclRbCfgList->rbCfgInfoList[4].dlRbCfg.dlRlcMode.mode = NHU_RLC_MODE_TM;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "dlRlcMode",
                  &lclRbCfgList->rbCfgInfoList[4].dlRbCfg.dlRlcMode.mode);
            nhAcUtlFillDlRlcModeInfo(tcCb, spCb,
                           &(lclRbCfgList->rbCfgInfoList[4].dlRbCfg.dlRlcMode));
         }
      }
   }
 
   /* Filling RB6 for PCCH to PCH  Mapping */
   {
      lclRbCfgList->rbCfgInfoList[5].rbId.rbId =  PCCH_RBID;
      /* Bit Mask (UL, DL Cfg present) */ 
      lclRbCfgList->rbCfgInfoList[5].rbCfgBitMsk |= NHU_RB_CFG_DL;
       
      /* DlRbCfg */
      {
         lclRbCfgList->rbCfgInfoList[5].dlRbCfg.dlRbBitMsk |= 
                                                     NHU_RB_CFG_LOGCH_MAP_DL;
         lclRbCfgList->rbCfgInfoList[5].dlRbCfg.dlRbBitMsk |= 
                                                     NHU_RB_CFG_RLC_MODE_DL;
         /* dlLogChMapInfo */
         {
            /* Logical Channel ID and type */
            lclRbCfgList->rbCfgInfoList[5].lcId.lcId = 
                                                                 PCCH_DL_PCH_ID;
            lclRbCfgList->rbCfgInfoList[5].lcId.logChType = 
                                                                 CM_LTE_LCH_PCCH;
            /* Transport Channel Type */
            lclRbCfgList->rbCfgInfoList[5].dlRbCfg.dlLogChMap.trChType =
                                                                 CM_LTE_TRCH_PCH;
         }
         /* DL-RLC mode */
         {
            dlrlcCfgType = NHU_CFG_TYPE_EXPLICIT;
            cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_U8,"dlrlcCfgType",
                           &dlrlcCfgType);
            lclRbCfgList->rbCfgInfoList[5].dlRbCfg.dlRlcMode.rlcCfgType =
                                                       NHU_CFG_TYPE_EXPLICIT;
            lclRbCfgList->rbCfgInfoList[5].dlRbCfg.dlRlcMode.mode = NHU_RLC_MODE_TM;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "dlRlcMode",
                  &lclRbCfgList->rbCfgInfoList[5].dlRbCfg.dlRlcMode.mode);
            nhAcUtlFillDlRlcModeInfo(tcCb, spCb,
                           &(lclRbCfgList->rbCfgInfoList[5].dlRbCfg.dlRlcMode));
         }
      }
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillCellRbCfg */

/*
*
*       Fun:   nhAcUtlFillRachCfg
*
*       Desc:  This function fills RACH Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillRachCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuRachCfg    *rachCfg
)
#else
PUBLIC S16 nhAcUtlFillRachCfg(tcCb, spCb, rachCfg)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuRachCfg    *rachCfg;
#endif
{
   TRC2(nhAcUtlFillRachCfg);

   rachCfg->maxMsg3Tx = 2;
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillRachCfg */

/*
*
*       Fun:   nhAcUtlFillPucchCfg
*
*       Desc:  This function fills PUCCH Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillPucchCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuPucchCfg   *pucchCfg
)
#else
PUBLIC S16 nhAcUtlFillPucchCfg(tcCb, spCb, pucchCfg)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuPucchCfg   *pucchCfg;
#endif
{
   TRC2(nhAcUtlFillPucchCfg);

   pucchCfg->pucchFixBw = 1;
   pucchCfg->deltaShift = NHU_PUCCH_DS1;
   pucchCfg->cyclShift = 1;
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillPucchCfg */

/*
*
*       Fun:   nhAcUtlFillPhichCfg
*
*       Desc:  This function fills PUCCH Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillPhichCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuPhichCfg   *phichCfg
)
#else
PUBLIC S16 nhAcUtlFillPhichCfg(tcCb, spCb, phichCfg)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuPhichCfg   *phichCfg;
#endif
{
   TRC2(nhAcUtlFillPhichCfg);

   phichCfg->resrc = NHU_NG_ONESIXTH;
   phichCfg->duration = NHU_PHICH_DUR_NORMAL;
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillPhichCfg */

#ifdef TENB_MULT_CELL_SUPPRT
/*
*
*       Fun:   nhAcUtlFillUeMsapCfg
*
*       Desc:  This function fills System MSAP Configuration for a UE
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillUeMsapCfg
(
CmXtaTCCb          *tcCb,
CmXtaSpCb          *spCb,
NhuUeLLyrSapIdInfo *uellyrSapIdInfo
)
#else
PUBLIC S16 nhAcUtlFillUeMsapCfg(tcCb, spCb, uellyrSapIdInfo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuUeLLyrSapIdInfo *uellyrSapIdInfo;
#endif
{
   TRC2(nhAcUtlFillUeMsapCfg);

   uellyrSapIdInfo->kwuSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "kwuSapId",
                           &(uellyrSapIdInfo->kwuSapId));
   uellyrSapIdInfo->ckwSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "ckwSapId",
                           &(uellyrSapIdInfo->ckwSapId));
   uellyrSapIdInfo->crgSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "crgSapId",
                           &(uellyrSapIdInfo->crgSapId));
   uellyrSapIdInfo->cpjSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "cpjSapId",
                           &(uellyrSapIdInfo->cpjSapId));
   uellyrSapIdInfo->pjuSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "pjuSapId",
                           &(uellyrSapIdInfo->pjuSapId));
   uellyrSapIdInfo->macRguUlSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "crgSapId",
                           &(uellyrSapIdInfo->macRguUlSapId));

   uellyrSapIdInfo->macRguDlSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "crgSapId",
                           &(uellyrSapIdInfo->macRguDlSapId));
   uellyrSapIdInfo->rlcRguSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "rguUlSapId",
                           &(uellyrSapIdInfo->rlcRguSapId));

   uellyrSapIdInfo->rlcKwuUlSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "rguDlSapId",
                           &(uellyrSapIdInfo->rlcKwuUlSapId));

   uellyrSapIdInfo->rlcKwuDlSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "rguDlSapId",
                           &(uellyrSapIdInfo->rlcKwuDlSapId));

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillUeMsapCfg */

/*
*
*       Fun:   nhAcUtlFillUeSapCfg
*
*       Desc:  This function fills System MSAP Configuration for a UE
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillUeSapCfg
(
CmXtaTCCb          *tcCb,
CmXtaSpCb          *spCb,
U16                cellId,
NhuUeLLyrSapIdInfo *uellyrSapIdInfo
)
#else
PUBLIC S16 nhAcUtlFillUeSapCfg(tcCb, spCb, cellId, uellyrSapIdInfo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
U16           cellId;
NhuUeLLyrSapIdInfo *uellyrSapIdInfo;
#endif
{
   TRC2(nhAcUtlFillUeSapCfg);
   if(1 == cellId)
   {
      uellyrSapIdInfo->kwuSapId = 0;
      uellyrSapIdInfo->ckwSapId = 0;
      uellyrSapIdInfo->crgSapId = 0;
      uellyrSapIdInfo->cpjSapId = 0;
      uellyrSapIdInfo->pjuSapId = 0;
      uellyrSapIdInfo->macRguUlSapId = 0;
      uellyrSapIdInfo->macRguDlSapId = 0;
      uellyrSapIdInfo->rlcRguSapId = 0;
      uellyrSapIdInfo->rlcKwuUlSapId = 0;
      uellyrSapIdInfo->rlcKwuDlSapId = 0;
   }
   if(2 == cellId)
   {
      uellyrSapIdInfo->kwuSapId = 1;
      uellyrSapIdInfo->ckwSapId = 1;
      uellyrSapIdInfo->crgSapId = 1;
      uellyrSapIdInfo->cpjSapId = 1;
      /* Changed for spId */
      uellyrSapIdInfo->pjuSapId = 1;
      uellyrSapIdInfo->macRguUlSapId = 1;
      uellyrSapIdInfo->macRguDlSapId = 1;
      uellyrSapIdInfo->rlcRguSapId = 1;
      uellyrSapIdInfo->rlcKwuUlSapId = 1;
      uellyrSapIdInfo->rlcKwuDlSapId = 1;
   }
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillUeSapCfg */
#endif /* TENB_MULT_CELL_SUPPRT */

#ifdef TENB_MULT_CELL_SUPPRT
/*
*
*       Fun:   nhAcUtlFillMsapCfg
*
*       Desc:  This function fills System MSAP Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillMsapCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuLLyrSapIdInfo *llyrSapIdInfo
)
#else
PUBLIC S16 nhAcUtlFillMsapCfg(tcCb, spCb, llyrSapIdInfo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuLLyrSapIdInfo *llyrSapIdInfo;
#endif
{
   TRC2(nhAcUtlFillMsapCfg);

   llyrSapIdInfo->ckwSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "ckwSapId",
                           &(llyrSapIdInfo->ckwSapId));
   llyrSapIdInfo->kwuSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "kwuSapId",
                           &(llyrSapIdInfo->kwuSapId));
   llyrSapIdInfo->crgSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "crgSapId",
                           &(llyrSapIdInfo->crgSapId));
   llyrSapIdInfo->cpjSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "cpjSapId",
                           &(llyrSapIdInfo->cpjSapId));
   llyrSapIdInfo->pjuSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "pjuSapId",
                           &(llyrSapIdInfo->pjuSapId));
   llyrSapIdInfo->crgSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "crgSapId",
                           &(llyrSapIdInfo->crgSapId));

   llyrSapIdInfo->rguUlSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "rguUlSapId",
                           &(llyrSapIdInfo->rguUlSapId));

   llyrSapIdInfo->rguDlSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "rguDlSapId",
                           &(llyrSapIdInfo->rguDlSapId));

   llyrSapIdInfo->rguSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "rguSapId",
                           &(llyrSapIdInfo->rguSapId));
#ifdef RRC_PHY_CFG_SUPP
   llyrSapIdInfo->ctfSapId = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep,CMXTA_ATTRIB_S16, "ctfSapId",
                           &(llyrSapIdInfo->ctfSapId));
#endif
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillMsapCfg */
#endif /* TENB_MULT_CELL_SUPPRT */

/*
*
*       Fun:   nhAcUtlFillValRbRlsCfgUe 
*
*       Desc:  This function fills UE RB Configuration in ueCfgInfo structure
*              of event structure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillValRbRlsCfgUe 
(
NhuRbRlsCfgList  *lclRlsRbCfg
)
#else
PUBLIC S16 nhAcUtlFillValRbRlsCfgUe(lclRlsRbCfg)
NhuRbRlsCfgList  *lclRlsRbCfg;
#endif
{
U8 idx;

   for(idx = 0; idx < lclRlsRbCfg->numOfRbCfgInfo; idx++)
   {
      gCkwValStore[gValIdx].entity[idx].rbId = lclRlsRbCfg->rbsToRel[idx].rbId;
       /*gCkwValStore[gValIdx].entity[idx].cfgType = ->rbCfgInfoList[idx].rbCfgBitMsk ;*/
   }
  RETVALUE(ROK);
}

/******************* UE Config Info structure filling functions *****/
/*
*
*       Fun:   nhAcUtlFillRlsRbCfg
*
*       Desc:  This function fills Release RB Configuration in UeCfgInfo structure
*              of event structure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillRlsRbCfg
(
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
NhuRbRlsCfgList **rlsRbCfg,
Ptr             evnt
)
#else
PUBLIC S16 nhAcUtlFillRlsRbCfg(tcCb, spCb, rlsRbCfg, evnt)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb; 
NhuRbRlsCfgList **rlsRbCfg;
Ptr             evnt;
#endif
{
   NhuRbRlsCfgList *lclRlsRbCfg;
   U8              numRb;
   Txt             msgStr[100];
   Txt             frstWrd[3];
   Txt             secWrd[3];
   U16             idx;
   U16             len;
   U8              rbVal;
   U8              rbType = 0;

   TRC2(nhAcUtlFillRlsRbCfg);
  
   idx = 0;
   len = 0;

   lclRlsRbCfg = *rlsRbCfg;

   CMXTA_ZERO(msgStr, sizeof(msgStr));

   numRb = 1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "numRlsRb", &numRb);
   lclRlsRbCfg->numOfRbCfgInfo = numRb;
   CMXTA_GET_MEM(evnt, sizeof(NhuRbId)*numRb, &(lclRlsRbCfg->rbsToRel));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "rlsRbIdStr", msgStr);
   while(len < strlen(msgStr))
   {
      CMXTA_ZERO(frstWrd, sizeof(frstWrd));
      nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      CMXTA_ZERO(secWrd, sizeof(secWrd));
      nhAcUtlStrToken(&msgStr[len], secWrd, ',');
      len = len + strlen(secWrd) + 1;
      rbType = atoi(secWrd);
      lclRlsRbCfg->rbsToRel[idx].rbId = rbVal;
      lclRlsRbCfg->rbsToRel[idx].rbTyp = rbType;
      idx++;
   }

   if(nhAccCb.valChk)
   {
     nhAcUtlFillValRbRlsCfgUe(lclRlsRbCfg);
   }

   RETVALUE(CMXTA_ERR_NONE);
}

/*
*
*       Fun:   nhAcUtlFillValRbCfgLstUe 
*
*       Desc:  This function fills UE RB Configuration in ueCfgInfo structure
*              of event structure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillValRbCfgLstUe 
(
U8            rbBitMask,
NhuRbCfgList  **rbCfgList
)
#else
PUBLIC S16 nhAcUtlFillValRbCfgLstUe(rbBitMask, rbCfgList)
U8            rbBitMask;
NhuRbCfgList  **rbCfgList;
#endif
{
NhuRbCfgList  *lclRbCfgList= NULLP;
U8 idx=0;

   lclRbCfgList = *rbCfgList;

   for(idx = 0; idx < lclRbCfgList->numOfRbCfgInfo; idx++)
   {
      gCkwValStore[gValIdx].entity[idx].rbId = lclRbCfgList->rbCfgInfoList[idx].rbId.rbId;
      gCpjCfgStore[gValIdx].entity[idx].rbId = lclRbCfgList->rbCfgInfoList[idx].rbId.rbId;

      /* Bit Mask (UL, DL and PDCP Cfg present) */ 
      gCkwValStore[gValIdx].entity[idx].cfgType = lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk;
       
      /* UlRbCfg */
      if(lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk & NHU_RB_CFG_UL)
      {
          gCkwValStore[gValIdx].entity[idx].dir |= CKW_CFG_DIR_UL;
          gCkwValStore[gValIdx].entity[idx].entMode =lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRlcMode.mode;
          /*mac validation params*/
          if(rbBitMask == NHU_CFG_RB_ADD)
          {
          gCrgValStore[gValIdx].u.crgCfg.lchCfg[idx].rbId = lclRbCfgList->rbCfgInfoList[idx].rbId.rbId;
          gCrgValStore[gValIdx].u.crgCfg.lchCfg[idx].lcId = lclRbCfgList->rbCfgInfoList[idx].lcId.lcId;
          gCrgValStore[gValIdx].u.crgCfg.lchCfg[idx].ulTrchType = lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulLogChMap.trChType;
          gCrgValStore[gValIdx].u.crgCfg.lchCfg[idx].dlTrchType = lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlLogChMap.trChType;
          }

          if(rbBitMask == NHU_CFG_RB_MODIFY)
          {
          gCrgValStore[gValIdx].u.crgReCfg.lchCfg[idx].rbId = lclRbCfgList->rbCfgInfoList[idx].rbId.rbId;
          gCrgValStore[gValIdx].u.crgReCfg.lchCfg[idx].lcId = lclRbCfgList->rbCfgInfoList[idx].lcId.lcId;
          }
      }
      /* DlRbCfg */
      if(lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk & NHU_RB_CFG_DL)
      {
          gCkwValStore[gValIdx].entity[idx].dir |= CKW_CFG_DIR_DL;
          gCkwValStore[gValIdx].entity[idx].entMode =lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRlcMode.mode;
          /*mac validation params*/
          if(rbBitMask == NHU_CFG_RB_ADD)
          {
          gCrgValStore[gValIdx].u.crgCfg.lchCfg[idx].rbId = lclRbCfgList->rbCfgInfoList[idx].rbId.rbId;
          gCrgValStore[gValIdx].u.crgCfg.lchCfg[idx].lcId = lclRbCfgList->rbCfgInfoList[idx].lcId.lcId;
          gCrgValStore[gValIdx].u.crgCfg.lchCfg[idx].dlTrchType = lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlLogChMap.trChType;
          gCrgValStore[gValIdx].u.crgCfg.lchCfg[idx].ulTrchType = lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulLogChMap.trChType;
          }
          if(rbBitMask == NHU_CFG_RB_MODIFY)
          {
          gCrgValStore[gValIdx].u.crgReCfg.lchCfg[idx].rbId = lclRbCfgList->rbCfgInfoList[idx].rbId.rbId;
          gCrgValStore[gValIdx].u.crgReCfg.lchCfg[idx].lcId = lclRbCfgList->rbCfgInfoList[idx].lcId.lcId;
          }
      }
      /* PDCP Cfg */
      {
         if(lclRbCfgList->rbCfgInfoList[idx].pdcpCfg.pdcpCfgBitMsk &
                                 NHU_PDCP_HDR_COMPR_INFO)
         {

            gCpjCfgStore[gValIdx].entity[idx].hdrComCfg.
               rohcInfo.maxCid = lclRbCfgList->rbCfgInfoList[idx].pdcpCfg.
                                          hdrComprInfo.rohcInfo.maxCid;
            gCpjCfgStore[gValIdx].entity[idx].hdrComCfg.rohcInfo.
                  profLst[0] = lclRbCfgList->rbCfgInfoList[idx].pdcpCfg.
                                    hdrComprInfo.rohcInfo.rohcProfileList[0];
         }
      }
   }

   RETVALUE(ROK);
}


/*
*
*       Fun:   nhAcUtlFilUeModRbCfg
*
*       Desc:  This function fills UE ADD RB Configuration 
*               in ueCfgInfo structure of event structure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFilUeModRbCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuRbCfgList  **rbCfgList,
U8            rbTypeBitMask,
Ptr           evnt
)
#else
PUBLIC S16 nhAcUtlFilUeModRbCfg(tcCb, spCb, rbCfgList, rbTypeBitMask, evnt)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuRbCfgList  **rbCfgList;
U8            rbTypeBitMask;
Ptr           evnt;
#endif
{
   

   NhuRbCfgList *lclRbCfgList;
   U8           msgType=0;
   U16          idx=0;
   U16          logChType=0;
   U8          rbVal=0;
   U8           rbType=0;
   U8          lcVal=0;
   U8          rbDirVal=0;
   Txt          msgRbStr[100];
   Txt          msgLchStr[100];
   Txt          rbBitMskStr[100];
   Txt          frstWrd[10];
   Txt          secWrd[3];
   NhuRbId      modRb[32];
   U8          modLc[32];
   U8          modRbDir[32];
   U16          numModRb = 0;
   U16          numModLc = 0;
   U16          numModRbDir = 0;
   U16          len=0;
   U8           pdcpId=0;
   U8           ulrlcCfgType;
   U8           dlrlcCfgType;
   Txt          dlRlcModStr[100];
   Txt          ulRlcModStr[100];
   U8           ulRlcMod[32];
   U8           dlRlcMod[32];

   TRC2(nhAcUtlFilUeModRbCfg);

   lclRbCfgList = *rbCfgList;

   CMXTA_ZERO(msgRbStr, sizeof(msgRbStr));
   CMXTA_ZERO(msgLchStr, sizeof(msgLchStr));
   CMXTA_ZERO(rbBitMskStr, sizeof(rbBitMskStr));
   CMXTA_ZERO(ulRlcModStr, sizeof(ulRlcModStr));
   CMXTA_ZERO(dlRlcModStr, sizeof(dlRlcModStr));

   CMXTA_ZERO(frstWrd, sizeof(frstWrd));

   CMXTA_ZERO(modRb, sizeof(modRb));
   CMXTA_ZERO(modLc, sizeof(modLc));
   CMXTA_ZERO(modRbDir, sizeof(modRbDir));
   CMXTA_ZERO(ulRlcMod, 32*sizeof(U8));
   CMXTA_ZERO(dlRlcMod, 32*sizeof(U8));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "modRbIdStr", 
                     &msgRbStr);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "modLcIdStr", 
                     &msgLchStr);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "modBitMskStr", 
                     &rbBitMskStr);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "dlRlcModStr", 
                     &dlRlcModStr);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "ulRlcModStr", 
                     &ulRlcModStr);

   len = 0;
   numModRb = 0;
   while(len < strlen(dlRlcModStr))
   {
      nhAcUtlStrToken(&dlRlcModStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      dlRlcMod[numModRb] = rbVal;
      numModRb++;
   }
   rbVal = 0;
   numModRb = 0;
   len = 0;
   while(len < strlen(ulRlcModStr))
   {
      nhAcUtlStrToken(&ulRlcModStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      ulRlcMod[numModRb] =  rbVal;
      numModRb++;
   }
   numModRb = 0;
   len = 0;
   while(len < strlen(msgRbStr))
   {
      nhAcUtlStrToken(&msgRbStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      nhAcUtlStrToken(&msgRbStr[len], secWrd, ',');
      len = len + strlen(secWrd) + 1;
      rbType = atoi(secWrd);
      modRb[numModRb].rbId = rbVal;
      modRb[numModRb].rbTyp = rbType;
      numModRb++;
   }

   numModLc = 0;
   len = 0;
   CMXTA_ZERO(frstWrd, sizeof(frstWrd));
   while(len < strlen(msgLchStr))
   {
      nhAcUtlStrToken(&msgLchStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      lcVal = atoi(frstWrd);
      /* adding 1 bcoz lcId is given as 2,3,4 in xml.
                         But allowed values - 3 to 10 */
      modLc[numModLc] = lcVal +1;
      numModLc++;
   }

   numModRbDir = 0;
   len = 0;
   CMXTA_ZERO(frstWrd, sizeof(frstWrd));
   while(len < strlen(rbBitMskStr))
   {
      nhAcUtlStrToken(&rbBitMskStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbDirVal = atoi(frstWrd);
      modRbDir[numModRbDir] = rbDirVal;
      numModRbDir++;
   }

   /* Fill the values now */

   for(idx = 0; idx < lclRbCfgList->numOfRbCfgInfo; idx++)
   {
      lclRbCfgList->rbCfgInfoList[idx].rbId.rbId =  modRb[idx].rbId;
      lclRbCfgList->rbCfgInfoList[idx].rbId.rbTyp =  modRb[idx].rbTyp;
      msgType = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "msgType", 
                     &msgType);

      if(msgType == C1_SECURITYMODECMD)
      {
         lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk |= NHU_RB_CFG_PDCP_INFO;
      }
      else
      {
         
         lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk =  modRbDir[idx];

         if (!lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk)
         {
            /* Bit Mask (UL, DL and PDCP Cfg present)  by Default */ 
            lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk |= NHU_RB_CFG_UL;
            lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk |= NHU_RB_CFG_DL;
            lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk |= NHU_RB_CFG_PDCP_INFO;
         }
      }/* else */

      if(lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk & NHU_RB_CFG_UL)
      {
         /* Bit mask calculate properly */
         lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRbBitMsk |=
                           NHU_RB_CFG_LOGCH_MAP_UL;
         lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRbBitMsk |=
                           NHU_RB_CFG_RLC_MODE_UL;

         /* ulLogChMapInfo [idx] */
         {
            /* Transport Channel type */
            lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulLogChMap.trChType =
                           CM_LTE_TRCH_UL_SCH;

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, 
                                 "logChType", &logChType);
            /* Logical Channel Id and Type */
            lclRbCfgList->rbCfgInfoList[idx].lcId.lcId = modLc[idx]; 
            if (!modLc[idx])
               lclRbCfgList->rbCfgInfoList[idx].lcId.lcId = modRb[idx].rbId;

            lclRbCfgList->rbCfgInfoList[idx].lcId.logChType = (CmLteLcType)logChType;

            /* Fill Logical Channel Cfg */
            nhAcUtlFillUlLogChCfg(tcCb, spCb,
                        &(lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulLogChMap));

         }
         /* ulRlcMode */
         {
            ulrlcCfgType = NHU_CFG_TYPE_EXPLICIT;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, 
                     "ulrlcCfgType", &ulrlcCfgType);
            lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRlcMode.rlcCfgType =
                           ulrlcCfgType;
            if (ulrlcCfgType == NHU_CFG_TYPE_EXPLICIT)
            {
               lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRlcMode.mode =
                  NHU_RLC_MODE_UM;
               if(ulRlcMod[idx])
                 lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRlcMode.mode =
                    ulRlcMod[idx];
               nhAcUtlFillUlRlcModeInfo(tcCb, spCb,
                         &(lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRlcMode));
            }
         } /* ulRlcMode */
      }

      /* DlRbCfg */
      if(lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk & NHU_RB_CFG_DL)
      {
         lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRbBitMsk |=
                        NHU_RB_CFG_LOGCH_MAP_DL;
         lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRbBitMsk |=
                        NHU_RB_CFG_RLC_MODE_DL;

         /* dlLogChMapInfo [idx] */
         {
            /* Logical Channel ID and type */
            lclRbCfgList->rbCfgInfoList[idx].lcId.lcId = modLc[idx];
            lclRbCfgList->rbCfgInfoList[idx].lcId.logChType = (CmLteLcType)logChType;
            /* Transport Channel Type */
            lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlLogChMap.trChType =
                        CM_LTE_TRCH_DL_SCH;
         }
         /* DL-RLC mode */
         {
            dlrlcCfgType = NHU_CFG_TYPE_EXPLICIT;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "dlrlcCfgType",
                     &dlrlcCfgType);
            lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRlcMode.rlcCfgType =
                           dlrlcCfgType;
            if (dlrlcCfgType == NHU_CFG_TYPE_EXPLICIT)
            {
               lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRlcMode.mode =
                  NHU_RLC_MODE_UM;
               if(dlRlcMod[idx])
                 lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRlcMode.mode =
                    dlRlcMod[idx];
               nhAcUtlFillDlRlcModeInfo(tcCb, spCb,
                       &(lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRlcMode));
            }
         }
      }

      /* PDCP Cfg */
      if(lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk & NHU_RB_CFG_PDCP_INFO)
      {
          cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"pdcpId",
                          &(pdcpId));
          lclRbCfgList->rbCfgInfoList[idx].pdcpCfg.pdcpCfgType
                                 = NHU_CFG_TYPE_EXPLICIT;
          nhAcUtlFillPdcpCfg(tcCb, spCb,
                             &(lclRbCfgList->rbCfgInfoList[idx].pdcpCfg), evnt);
      }
   }

   RETVALUE(CMXTA_ERR_NONE);

}

/*
*
*       Fun:   nhAcUtlFilUeAddRbCfg
*
*       Desc:  This function fills UE ADD RB Configuration 
*               in ueCfgInfo structure of event structure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFilUeAddRbCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuRbCfgList  **rbCfgList,
U8            rbTypeBitMask,
Ptr           evnt
)
#else
PUBLIC S16 nhAcUtlFilUeAddRbCfg(tcCb, spCb, rbCfgList, rbTypeBitMask, evnt)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuRbCfgList  **rbCfgList;
U8            rbTypeBitMask;
Ptr           evnt;
#endif
{
   
   NhuRbCfgList *lclRbCfgList;
   U8           msgType=0;
   U16          idx=0;
   U16          logChType=0;
   U8          rbVal=0;
   U8           rbType=0;
   U8          lcVal=0;
   U8          rbDirVal=0;
   Txt          msgRbStr[100];
   Txt          msgLchStr[100];
   Txt          rbBitMskStr[100];
   Txt          frstWrd[10];
   Txt          secWrd[3];
   NhuRbId      addRb[32];
   U8          addLc[32];
   U8          addRbDir[32];
   U16          numAddRb = 0;
   U16          numAddLc = 0;
   U16          numAddRbDir = 0;
   U16          len=0;
   U8           pdcpId=0;
   U8           ulrlcCfgType;
   U8           dlrlcCfgType;
   Txt          dlRlcModStr[100];
   Txt          ulRlcModStr[100];
   U8           ulRlcMod[32];
   U8           dlRlcMod[32];


   TRC2(nhAcUtlFilUeAddRbCfg);


   lclRbCfgList = *rbCfgList;

   CMXTA_ZERO(msgRbStr, sizeof(msgRbStr));
   CMXTA_ZERO(msgLchStr, sizeof(msgLchStr));
   CMXTA_ZERO(rbBitMskStr, sizeof(rbBitMskStr));
   CMXTA_ZERO(ulRlcModStr, sizeof(ulRlcModStr));
   CMXTA_ZERO(dlRlcModStr, sizeof(dlRlcModStr));

   CMXTA_ZERO(frstWrd, sizeof(frstWrd));

   CMXTA_ZERO(addRb, sizeof(addRb));
   CMXTA_ZERO(addLc, sizeof(addLc));
   CMXTA_ZERO(addRbDir, sizeof(addRbDir));
   CMXTA_ZERO(ulRlcMod, 32*sizeof(U8));
   CMXTA_ZERO(dlRlcMod, 32*sizeof(U8));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "addRbIdStr", 
                     &msgRbStr);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "addLcIdStr", 
                     &msgLchStr);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "addBitMskStr", 
                     &rbBitMskStr);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "dlRlcModStr", 
                     &dlRlcModStr);
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "ulRlcModStr", 
                     &ulRlcModStr);

   len = 0;
   numAddRb = 0;
   while(len < strlen(dlRlcModStr))
   {
      nhAcUtlStrToken(&dlRlcModStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      dlRlcMod[numAddRb] = rbVal;
      numAddRb++;
   }
   rbVal = 0;
   numAddRb = 0;
   len = 0;
   while(len < strlen(ulRlcModStr))
   {
      nhAcUtlStrToken(&ulRlcModStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      ulRlcMod[numAddRb] = rbVal;
      numAddRb++;
   }
   rbVal = 0;
   numAddRb = 0;
   len = 0;
   while(len < strlen(msgRbStr))
   {
      nhAcUtlStrToken(&msgRbStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbVal = atoi(frstWrd);
      addRb[numAddRb].rbId = rbVal;
      nhAcUtlStrToken(&msgRbStr[len], secWrd, ',');
      len = len + strlen(secWrd) + 1;
      rbType = atoi(secWrd);
      addRb[numAddRb].rbTyp = rbType;
      numAddRb++;
   }

   numAddLc = 0;
   len = 0;
   CMXTA_ZERO(frstWrd, sizeof(frstWrd));
   while(len < strlen(msgLchStr))
   {
      nhAcUtlStrToken(&msgLchStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      lcVal = atoi(frstWrd);
      /* adding 1 bcoz lcId is given as 2,3,4 in xml.
                         But allowed values - 3 to 10 */
      addLc[numAddLc] = lcVal + 1;
      numAddLc++;
   }

   numAddRbDir = 0;
   len = 0;
   CMXTA_ZERO(frstWrd, sizeof(frstWrd));
   while(len < strlen(rbBitMskStr))
   {
      nhAcUtlStrToken(&rbBitMskStr[len], frstWrd, ',');
      len = len + strlen(frstWrd) + 1;
      rbDirVal = atoi(frstWrd);
      addRbDir[numAddRbDir] = rbDirVal;
      numAddRbDir++;
   }

   /* Fill the values now */

   for(idx = 0; idx < lclRbCfgList->numOfRbCfgInfo; idx++)
   {
      lclRbCfgList->rbCfgInfoList[idx].rbId.rbId = addRb[idx].rbId;
      lclRbCfgList->rbCfgInfoList[idx].rbId.rbTyp = addRb[idx].rbTyp;
      msgType = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "msgType", 
                     &msgType);

      if(msgType == C1_SECURITYMODECMD)
      {
         lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk |= NHU_RB_CFG_PDCP_INFO;
      }
      else
      {
         
         lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk =  addRbDir[idx];

         if (!lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk)
         {
            /* Bit Mask (UL, DL and PDCP Cfg present)  by Default */ 
            lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk |= NHU_RB_CFG_UL;
            lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk |= NHU_RB_CFG_DL;
            lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk |= NHU_RB_CFG_PDCP_INFO;
         }
      }/* else */

      if(lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk & NHU_RB_CFG_UL)
      {
         /* Bit mask calculate properly */
         lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRbBitMsk |=
                           NHU_RB_CFG_LOGCH_MAP_UL;
         lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRbBitMsk |=
                           NHU_RB_CFG_RLC_MODE_UL;

         /* ulLogChMapInfo [idx] */
         {
            /* Transport Channel type */
            lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulLogChMap.trChType =
                           CM_LTE_TRCH_UL_SCH;

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16, 
                                 "logChType", &logChType);
            /* Logical Channel Id and Type */
            lclRbCfgList->rbCfgInfoList[idx].lcId.lcId =  addLc[idx];
            if(!lclRbCfgList->rbCfgInfoList[idx].lcId.lcId)
               lclRbCfgList->rbCfgInfoList[idx].lcId.lcId = idx+1;
            lclRbCfgList->rbCfgInfoList[idx].lcId.logChType = (CmLteLcType)logChType;

            /* Fill Logical Channel Cfg */
            nhAcUtlFillUlLogChCfg(tcCb, spCb,
                        &(lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulLogChMap));

         }
         /* ulRlcMode */
         {
            ulrlcCfgType = NHU_CFG_TYPE_EXPLICIT;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, 
                     "ulrlcCfgType", &ulrlcCfgType);
            lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRlcMode.rlcCfgType =
                           ulrlcCfgType;
            if ( ulrlcCfgType == NHU_CFG_TYPE_EXPLICIT)
            {
               lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRlcMode.mode =
                  NHU_RLC_MODE_UM;
               if(ulRlcMod[idx])
               lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRlcMode.mode =
                  ulRlcMod[idx];
               nhAcUtlFillUlRlcModeInfo(tcCb, spCb,
                         &(lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRlcMode));
            }
         } /* ulRlcMode */
      }

      /* DlRbCfg */
      if(lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk & NHU_RB_CFG_DL)
      {
         lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRbBitMsk |=
                        NHU_RB_CFG_LOGCH_MAP_DL;
         lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRbBitMsk |=
                        NHU_RB_CFG_RLC_MODE_DL;

         /* dlLogChMapInfo [idx] */
         {
            /* Logical Channel ID and type */
            lclRbCfgList->rbCfgInfoList[idx].lcId.lcId = addLc[idx];
            if(!lclRbCfgList->rbCfgInfoList[idx].lcId.lcId)
                        lclRbCfgList->rbCfgInfoList[idx].lcId.lcId = idx+1;
            lclRbCfgList->rbCfgInfoList[idx].lcId.logChType = (CmLteLcType)logChType;
            /* Transport Channel Type */
            lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlLogChMap.trChType =
                        CM_LTE_TRCH_DL_SCH;
         }
         /* DL-RLC mode */
         {
            dlrlcCfgType = NHU_CFG_TYPE_EXPLICIT;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "dlrlcCfgType",
                     &dlrlcCfgType);
            lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRlcMode.rlcCfgType =
                           dlrlcCfgType;
            if (dlrlcCfgType == NHU_CFG_TYPE_EXPLICIT)
            {
               lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRlcMode.mode =
                  NHU_RLC_MODE_UM;
               if(dlRlcMod[idx])
               lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRlcMode.mode =
                  dlRlcMod[idx];
               nhAcUtlFillDlRlcModeInfo(tcCb, spCb,
                       &(lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRlcMode));
            }
         }
      }

      /* PDCP Cfg */
      if(lclRbCfgList->rbCfgInfoList[idx].rbCfgBitMsk & NHU_RB_CFG_PDCP_INFO)
      {
          cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"pdcpId",
                  &(pdcpId));
          lclRbCfgList->rbCfgInfoList[idx].pdcpCfg.pdcpCfgType
                                 = NHU_CFG_TYPE_EXPLICIT;
          nhAcUtlFillPdcpCfg(tcCb, spCb,
                             &(lclRbCfgList->rbCfgInfoList[idx].pdcpCfg), evnt);
          if ((lclRbCfgList->rbCfgInfoList[idx].rbId.rbTyp == CM_LTE_DRB) &&
             ((lclRbCfgList->rbCfgInfoList[idx].dlRbCfg.dlRlcMode.mode == NHU_RLC_MODE_AM) ||
             (lclRbCfgList->rbCfgInfoList[idx].ulRbCfg.ulRlcMode.mode == NHU_RLC_MODE_AM)))
          {
             lclRbCfgList->rbCfgInfoList[idx].pdcpCfg.pdcpCfgBitMsk |= NHU_PDCP_SN_SIZE;
             lclRbCfgList->rbCfgInfoList[idx].pdcpCfg.snSize = NHU_PDCP_SN_SIZE_12BITS;
          }
      }
   }

   
   RETVALUE(CMXTA_ERR_NONE);

}


/*
*
*       Fun:   nhAcUtlFillUeRbCfg
*
*       Desc:  This function fills UE RB Configuration in ueCfgInfo structure
*              of event structure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillUeRbCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuRbCfgList  **rbCfgList,
U8            rbTypeBitMask,
Ptr           evnt
)
#else
PUBLIC S16 nhAcUtlFillUeRbCfg(tcCb, spCb, rbCfgList, rbTypeBitMask, evnt)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuRbCfgList  **rbCfgList;
U8            rbTypeBitMask;
Ptr           evnt;
#endif
{

   TRC2(nhAcUtlFillUeRbCfg);
   
   if (rbTypeBitMask == NHU_CFG_RB_ADD)
   {
      nhAcUtlFilUeAddRbCfg(tcCb, spCb, rbCfgList, rbTypeBitMask,evnt);
   }
   if (rbTypeBitMask == NHU_CFG_RB_MODIFY)
   {
      nhAcUtlFilUeModRbCfg(tcCb, spCb, rbCfgList, rbTypeBitMask,evnt);
   }
   
   if(nhAccCb.valChk)
   {
     nhAcUtlFillValRbCfgLstUe(rbTypeBitMask, rbCfgList);
   }

   RETVALUE(CMXTA_ERR_NONE);
   
} /* End of nhAcUtlFillUeRbCfg */

#ifdef RRC_PHY_CFG_SUPP
/*
*
*       Fun:   nhAcUtlFillUePhyAddCfg
*
*       Desc:  This function fills UE Phy Configuration in ueCfgInfo structure
*              of event structure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillUePhyAddCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuPhyCfg     *phyCfg,
U8            phyCfgType
)
#else
PUBLIC S16 nhAcUtlFillUePhyAddCfg(tcCb, spCb, phyCfg, phyCfgType)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuPhyCfg     *phyCfg;
U8            phyCfgType;
#endif
{
   U8  bitMask;
   U8  expOrDflt;
   U8  reportingMode;
   U8  txMode;


   TRC2(nhAcUtlFillUePhyAddCfg);

   CMXTA_ZERO(&bitMask, sizeof(U8));
   expOrDflt = NHU_CFG_TYPE_EXPLICIT;


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ExplicitOrDefault", 
                     &expOrDflt);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "phyCfgBitMask", 
                     &bitMask);

   phyCfg->bitMask = bitMask;
   
   if (phyCfg->bitMask & NHU_DED_PHY_CFG_UE_CAT)
   {
      phyCfg->ueCategory = CM_LTE_UE_CAT_1;
   }

   if (expOrDflt == NHU_CFG_TYPE_DFLT)
   {
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_PDSCH)
        phyCfg->pdschCfg.cfgTyp = NHU_CFG_TYPE_DFLT;
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_PUCCH)
        phyCfg->pucchCfg.cfgTyp = NHU_CFG_TYPE_DFLT;
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_PUSCH)
        phyCfg->puschCfg.cfgTyp = NHU_CFG_TYPE_DFLT;
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_CQI)
        phyCfg->cqiCfg.cfgType = NHU_CFG_TYPE_DFLT;
     
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_UL_SRS)
       phyCfg->srsUlCfg.cfgTyp = NHU_CFG_TYPE_DFLT;
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_SR)
       phyCfg->srCfg.cfgTyp = NHU_CFG_TYPE_DFLT;
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_ANT)
       phyCfg->antCfg.cfgTyp = NHU_CFG_TYPE_DFLT;
   }
   else
   {
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_PDSCH)
     {
        phyCfg->pdschCfg.cfgTyp = NHU_CFG_TYPE_EXPLICIT;
        phyCfg->pdschCfg.pa = NHU_PDSCH_PA_ONE;
     }
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_PUCCH)
     {
        phyCfg->pucchCfg.cfgTyp = NHU_CFG_TYPE_EXPLICIT;
        phyCfg->pucchCfg.choice = NHU_CFGTYPE_SETUP;
        phyCfg->pucchCfg.setup.factor = NHU_N2;
        phyCfg->pucchCfg.setup.n1PUCCH_AN_Rep = 10;
     }
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_PUSCH)
     {
        phyCfg->puschCfg.cfgTyp = NHU_CFG_TYPE_EXPLICIT;
        phyCfg->puschCfg.betaOffsetAckIdx = 10;
        phyCfg->puschCfg.betaOffsetRiIdx = 11;
        phyCfg->puschCfg.betaOffsetCqiIdx = 11;
     }
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_CQI)
     {
        phyCfg->cqiCfg.cfgType = NHU_CFG_TYPE_EXPLICIT;
 
        cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"reportingMode",
                       &reportingMode);
#ifndef NHU_VER2
	     if ((reportingMode != NHU_CQI_RPTMODE_APERIODIC) && 
            (reportingMode != NHU_CQI_RPTMODE_PERIODIC))
        {
           reportingMode = NHU_CQI_RPTMODE_PERIODIC;
        }

        phyCfg->cqiCfg.reportingMode = reportingMode;
  
        if (NHU_CQI_RPTMODE_APERIODIC == phyCfg->cqiCfg.reportingMode)
        {
           phyCfg->cqiCfg.reportMode.aPeriodicRpt = NHU_CQI_RPT_MODE_APERIODIC_RM12;
        }

        else if (NHU_CQI_RPTMODE_PERIODIC == reportingMode)
        {
#else
  
        if ((NHU_CQI_RPTMODE_APERIODIC == reportingMode) ||
            (3 == reportingMode))
        {
           phyCfg->cqiCfg.reportMode.aPeriodicRpt.pres = TRUE;
           phyCfg->cqiCfg.reportMode.aPeriodicRpt.aPeriodicRptMode = NHU_CQI_RPT_MODE_APERIODIC_RM12;
        }
  
        if ((NHU_CQI_RPTMODE_PERIODIC == reportingMode) ||
            (3 == reportingMode))
        {
           phyCfg->cqiCfg.reportMode.periodicRpt.pres = TRUE;
#endif
           phyCfg->cqiCfg.reportMode.periodicRpt.cqiPeriodicCfgType = NHU_CFGTYPE_SETUP;
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.cqiPUCCHRsrcIndx = 100;
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.cqiPmiCfgIndx = 1022;
           /* formatIndicator could be wideband or subband, it's not defined in nhu.h, 
              so just filling value 1, needs to be checked */
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.formatIndicator = 1;  
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.subbandCqi.k = 1;
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.riCfgPres = 1;
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.riCfgIndx = 1021;
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.simultaneousAckNack = TRUE;
        }
     }
     
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_UL_SRS)
     {
       phyCfg->srsUlCfg.cfgTyp = NHU_CFG_TYPE_EXPLICIT;
       phyCfg->srsUlCfg.choice = NHU_CFGTYPE_SETUP;
       phyCfg->srsUlCfg.setup.srsBwCfg = 2;
       phyCfg->srsUlCfg.setup.srsHopBwCfg = 3;
       phyCfg->srsUlCfg.setup.freqDomPos = 21;
       phyCfg->srsUlCfg.setup.duration = FALSE;
       phyCfg->srsUlCfg.setup.srsCfgIndx = 1001;
       phyCfg->srsUlCfg.setup.transComb = 1;
       phyCfg->srsUlCfg.setup.cycleshft = 6;
     }
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_SR)
     {
       phyCfg->srCfg.cfgTyp = NHU_CFG_TYPE_EXPLICIT;
       phyCfg->srCfg.dedSRCfgType = NHU_CFGTYPE_SETUP;
       phyCfg->srCfg.setup.srPUCCHRi = 2042;
       phyCfg->srCfg.setup.srCfgIdx = 142;
     }
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_ANT)
     {
#ifndef NHU_VER2
       txMode = NHU_DED_ANT_CFG_TX_MODE_TM1;
#else
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"txMode",
                       &txMode);
#endif
       phyCfg->antCfg.cfgTyp = NHU_CFG_TYPE_EXPLICIT;
       phyCfg->antCfg.txMode = (NhuDedAntCfgTxMode)txMode;
       phyCfg->antCfg.txAntSelectchoice = NHU_CFGTYPE_SETUP;
       phyCfg->antCfg.txAntSelect = NHU_UE_TX_ANT_CLOSEDLOOP;

#ifdef NHU_VER2
       switch(txMode)
       {
           case NHU_DED_ANT_CFG_TX_MODE_TM3:
               phyCfg->antCfg.codeBookSubsetRes.nhuCdBkRestType =
                       N4TX_ANTENNA_TM3;
               phyCfg->antCfg.codeBookSubsetRes.codeBookSubsetRestn.n4TxAntTm3
                       = 0x03;
           break;

           case NHU_DED_ANT_CFG_TX_MODE_TM4:
               phyCfg->antCfg.codeBookSubsetRes.nhuCdBkRestType =
                       N2TX_ANTENNA_TM4;
               phyCfg->antCfg.codeBookSubsetRes.codeBookSubsetRestn.n2TxAntTm4
                       = 0x04;
           break;

           case NHU_DED_ANT_CFG_TX_MODE_TM5:
               phyCfg->antCfg.codeBookSubsetRes.nhuCdBkRestType =
                       N4TX_ANTENNA_TM5;
               phyCfg->antCfg.codeBookSubsetRes.codeBookSubsetRestn.n4TxAntTm5
                       = 0x05;
           break;

           case NHU_DED_ANT_CFG_TX_MODE_TM6:
               phyCfg->antCfg.codeBookSubsetRes.nhuCdBkRestType =
                       N4TX_ANTENNA_TM6;
               phyCfg->antCfg.codeBookSubsetRes.codeBookSubsetRestn.n4TxAntTm6
                       = 0x06;
           break;
           default:
               break;
       }
#endif
     }
   }

   if(nhAccCb.valChk)
   {
     cmMemcpy((U8*)&(gCtfValStore[gValIdx].u.phyCfg),
                 (U8*)(phyCfg),sizeof(NhuPhyCfg));
   }

   RETVALUE(CMXTA_ERR_NONE);
   
} /* End of nhAcUtlFillUePhyAddCfg */

/*
*
*       Fun:   nhAcUtlFillUePhyModCfg
*
*       Desc:  This function fills UE Phy ReConfiguration in ueCfgInfo structure
*              of event structure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillUePhyModCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuPhyCfg     *phyCfg,
U8            phyCfgType
)
#else
PUBLIC S16 nhAcUtlFillUePhyModCfg(tcCb, spCb, phyCfg, phyCfgType)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuPhyCfg     *phyCfg;
U8            phyCfgType;
#endif
{
   U8  bitMask;
   U8  expOrDflt;
   U8  reportingMode;
   U8  txMode;


   TRC2(nhAcUtlFillUePhyModCfg);

   CMXTA_ZERO(&bitMask, sizeof(U8));
   expOrDflt = NHU_CFG_TYPE_EXPLICIT;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ExplicitOrDefault", 
                     &expOrDflt);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "phyCfgBitMask", 
                     &bitMask);
   
   phyCfg->bitMask = bitMask;

   if (phyCfg->bitMask & NHU_DED_PHY_CFG_UE_CAT)
   {
      phyCfg->ueCategory = CM_LTE_UE_CAT_2;
   }

   if (expOrDflt == NHU_CFG_TYPE_DFLT)
   {
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_PDSCH)
        phyCfg->pdschCfg.cfgTyp = NHU_CFG_TYPE_DFLT;
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_PUCCH)
        phyCfg->pucchCfg.cfgTyp = NHU_CFG_TYPE_DFLT;
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_PUSCH)
        phyCfg->puschCfg.cfgTyp = NHU_CFG_TYPE_DFLT;
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_UL_SRS)
       phyCfg->srsUlCfg.cfgTyp = NHU_CFG_TYPE_DFLT;
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_SR)
       phyCfg->srCfg.cfgTyp = NHU_CFG_TYPE_DFLT;
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_ANT)
       phyCfg->antCfg.cfgTyp = NHU_CFG_TYPE_DFLT;
   }
   else
   {
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_PDSCH)
     {
        phyCfg->pdschCfg.cfgTyp = NHU_CFG_TYPE_EXPLICIT;
        phyCfg->pdschCfg.pa = NHU_PDSCH_PA_TWO;
     }
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_PUCCH)
     {
        phyCfg->pucchCfg.cfgTyp = NHU_CFG_TYPE_EXPLICIT;
        phyCfg->pucchCfg.choice = NHU_CFGTYPE_SETUP;
        phyCfg->pucchCfg.setup.factor = NHU_N4;
        phyCfg->pucchCfg.setup.n1PUCCH_AN_Rep = 20;
     }
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_PUSCH)
     {
        phyCfg->puschCfg.cfgTyp = NHU_CFG_TYPE_EXPLICIT;
        phyCfg->puschCfg.betaOffsetAckIdx = 20;
        phyCfg->puschCfg.betaOffsetRiIdx = 21;
        phyCfg->puschCfg.betaOffsetCqiIdx = 21;
     }
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_CQI)
     {
        phyCfg->cqiCfg.cfgType = NHU_CFG_TYPE_EXPLICIT;
  
        cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"reportingMode",
                       &reportingMode);
#ifndef NHU_VER2
        phyCfg->cqiCfg.reportingMode = reportingMode;
  
        if (NHU_CQI_RPTMODE_APERIODIC == reportingMode)
        {
           phyCfg->cqiCfg.reportMode.aPeriodicRpt = NHU_CQI_RPT_MODE_APERIODIC_RM12;
        }

        else if (NHU_CQI_RPTMODE_PERIODIC == reportingMode)
        {
#else
  
        if ((NHU_CQI_RPTMODE_APERIODIC == reportingMode) ||
            (3 == reportingMode))
        {
           phyCfg->cqiCfg.reportMode.aPeriodicRpt.pres = TRUE;
           phyCfg->cqiCfg.reportMode.aPeriodicRpt.aPeriodicRptMode = NHU_CQI_RPT_MODE_APERIODIC_RM12;
        }
  
        if ((NHU_CQI_RPTMODE_PERIODIC == reportingMode) ||
            (3 == reportingMode))
        {
           phyCfg->cqiCfg.reportMode.periodicRpt.pres = TRUE;
#endif
           phyCfg->cqiCfg.reportMode.periodicRpt.cqiPeriodicCfgType = NHU_CFGTYPE_SETUP;
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.cqiPUCCHRsrcIndx = 100;
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.cqiPmiCfgIndx = 1022;
           /* formatIndicator could be wideband or subband, it's not defined in nhu.h, 
              so just filling value 1, needs to be checked */
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.formatIndicator = 1;  
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.subbandCqi.k = 1;
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.riCfgPres = 1;
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.riCfgIndx = 1021;
           phyCfg->cqiCfg.reportMode.periodicRpt.setup.simultaneousAckNack = TRUE;
        }
     }
     
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_UL_SRS)
     {
       phyCfg->srsUlCfg.cfgTyp = NHU_CFG_TYPE_EXPLICIT;
       phyCfg->srsUlCfg.choice = NHU_CFGTYPE_SETUP;
       phyCfg->srsUlCfg.setup.srsBwCfg = 4;
       phyCfg->srsUlCfg.setup.srsHopBwCfg = 5;
       phyCfg->srsUlCfg.setup.freqDomPos = 22;
       phyCfg->srsUlCfg.setup.duration = FALSE;
       phyCfg->srsUlCfg.setup.srsCfgIndx = 1002;
       phyCfg->srsUlCfg.setup.transComb = 2;
       phyCfg->srsUlCfg.setup.cycleshft = 7;
     }
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_SR)
     {
       phyCfg->srCfg.cfgTyp = NHU_CFG_TYPE_EXPLICIT;
       phyCfg->srCfg.dedSRCfgType = NHU_CFGTYPE_SETUP;
       phyCfg->srCfg.setup.srPUCCHRi = 2043;
       phyCfg->srCfg.setup.srCfgIdx = 143;
     }
  
     if (phyCfg->bitMask & NHU_DED_PHY_CFG_ANT)
     {
#ifndef NHU_VER2
       txMode = NHU_DED_ANT_CFG_TX_MODE_TM1;
#else
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"txMode",
                       &txMode);
#endif
       phyCfg->antCfg.cfgTyp = NHU_CFG_TYPE_EXPLICIT;
       phyCfg->antCfg.txMode = (NhuDedAntCfgTxMode)txMode;
       phyCfg->antCfg.txAntSelectchoice = NHU_CFGTYPE_SETUP;
       phyCfg->antCfg.txAntSelect = NHU_UE_TX_ANT_OPENLOOP;
#ifdef NHU_VER2
       switch(txMode)
       {
           case NHU_DED_ANT_CFG_TX_MODE_TM3:
               phyCfg->antCfg.codeBookSubsetRes.nhuCdBkRestType =
                       N4TX_ANTENNA_TM3;
               phyCfg->antCfg.codeBookSubsetRes.codeBookSubsetRestn.n4TxAntTm3
                       = 0x03;
           break;

           case NHU_DED_ANT_CFG_TX_MODE_TM4:
               phyCfg->antCfg.codeBookSubsetRes.nhuCdBkRestType =
                       N2TX_ANTENNA_TM4;
               phyCfg->antCfg.codeBookSubsetRes.codeBookSubsetRestn.n2TxAntTm4
                       = 0x04;
           break;

           case NHU_DED_ANT_CFG_TX_MODE_TM5:
               phyCfg->antCfg.codeBookSubsetRes.nhuCdBkRestType =
                       N4TX_ANTENNA_TM5;
               phyCfg->antCfg.codeBookSubsetRes.codeBookSubsetRestn.n4TxAntTm5
                       = 0x05;
           break;

           case NHU_DED_ANT_CFG_TX_MODE_TM6:
               phyCfg->antCfg.codeBookSubsetRes.nhuCdBkRestType =
                       N4TX_ANTENNA_TM6;
               phyCfg->antCfg.codeBookSubsetRes.codeBookSubsetRestn.n4TxAntTm6
                       = 0x06;
           break;
           default:
               break;
       }
#endif
     }
   }
      

   if(nhAccCb.valChk)
   {
     cmMemcpy((U8*)&(gCtfValStore[gValIdx].u.phyCfg),
                 (U8*)(phyCfg),sizeof(NhuPhyCfg));
   }

   RETVALUE(CMXTA_ERR_NONE);
   
} /* End of nhAcUtlFillUePhyModCfg */

/*
*
*       Fun:   nhAcUtlFillCmnPhyAddCfg
*
*       Desc:  This function fills UE Phy Configuration in ueCfgInfo structure
*              of event structure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillCmnPhyAddCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuCmnPhyCfg  *cellCfgInfo
)
#else
PUBLIC S16 nhAcUtlFillCmnPhyAddCfg(tcCb, spCb, cellCfgInfo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuCmnPhyCfg  *cellCfgInfo;
#endif
{
   U8  bitMask;

   TRC2(nhAcUtlFillCmnPhyAddCfg);

   CMXTA_ZERO(&bitMask, sizeof(U8));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "phyBitMask", 
                     &bitMask);
   
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "cellId", 
                     &(cellCfgInfo->pcellCfg.physCellId));

   cellCfgInfo->pcellCfg.cellIdGrpId = 10;

   /* nh002.201 : changes due to structure modification */
   cellCfgInfo->eUtraBand = 12;

   cellCfgInfo->schmCfg.scSpacing = NHU_TX_SCHM_SC_SPACING_15KHZ;

   cellCfgInfo->numOfTxAnt = 2;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "numTxAntennas", 
                     &(cellCfgInfo->numOfTxAnt));

   cellCfgInfo->bitmask = bitMask;

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_PRACH)
   {
      cellCfgInfo->prachCfg.rootSequenceIndex = 10;
      cellCfgInfo->prachCfg.prachCfgIndex = 20;
      cellCfgInfo->prachCfg.zeroCorrelationZoneCfg = 12;
      cellCfgInfo->prachCfg.highSpeedFlag = TRUE;
      cellCfgInfo->prachCfg.prachFreqOffset = 80;
   }

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_PDSCH)
   {
      cellCfgInfo->cmnPdschCfg.refSigPower = 25;
      cellCfgInfo->cmnPdschCfg.pb = 2;
   }

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_PUSCH)
   {
      cellCfgInfo->cmnPuschCfg.nSB = 2;
      cellCfgInfo->cmnPuschCfg.hoppingMode = 1;
      cellCfgInfo->cmnPuschCfg.puschHoppingOffset = 75;
      cellCfgInfo->cmnPuschCfg.enable64QAM = TRUE;
      cellCfgInfo->cmnPuschCfg.refSig.grpHoppngEnb = TRUE;
      cellCfgInfo->cmnPuschCfg.refSig.seqHoppingEnb = TRUE;
      cellCfgInfo->cmnPuschCfg.refSig.grpAssignPUSCH = 17;
      cellCfgInfo->cmnPuschCfg.refSig.cyclicShift = 6;
   }

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_PHICH)
   {
      cellCfgInfo->cmnPhichCfg.duration = NHU_PHICH_DUR_NORMAL;
      cellCfgInfo->cmnPhichCfg.resrc = NHU_NG_HALF;
   }

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_PUCCH)
   {
      cellCfgInfo->cmnPucchCfg.pucchFixBw = 16;
      cellCfgInfo->cmnPucchCfg.cyclShift = 5;
      cellCfgInfo->cmnPucchCfg.n1PucchAn = 3;
      cellCfgInfo->cmnPucchCfg.deltaShift = NHU_PUCCH_DS1;
   }

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_UL_SRS)
   {
      cellCfgInfo->srsUlCfg.srsCfgType = NHU_CFGTYPE_SETUP;
      cellCfgInfo->srsUlCfg.setup.bwCfg = NHU_SRS_BW4;
      cellCfgInfo->srsUlCfg.setup.subfrmCfg = NHU_SRS_SC12;
      cellCfgInfo->srsUlCfg.setup.srsANSimultTx = TRUE;
      cellCfgInfo->srsUlCfg.setup.srsMaxUpPts = TRUE;
   }

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_TDD_SF)
   {
      cellCfgInfo->tddSfCfg.sfAssignment = 4;
      cellCfgInfo->tddSfCfg.spclSfPatterns = 6;
   }

   if(nhAccCb.valChk)
   {
     cmMemcpy((U8*)&(gCtfValStore[gValIdx].u.cellCfgInfo),
                 (U8*)(cellCfgInfo),sizeof(NhuCmnPhyCfg));
   }

   RETVALUE(CMXTA_ERR_NONE);
   
} /* End of nhAcUtlFillCmnPhyAddCfg */

/*
*
*       Fun:   nhAcUtlFillCmnPhyModCfg
*
*       Desc:  This function fills UE Phy ReConfiguration in ueCfgInfo structure
*              of event structure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillCmnPhyModCfg
(
CmXtaTCCb       *tcCb,
CmXtaSpCb       *spCb,
NhuCmnPhyRecfg  *cellCfgInfo
)
#else
PUBLIC S16 nhAcUtlFillCmnPhyModCfg(tcCb, spCb, cellCfgInfo)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb; 
NhuCmnPhyRecfg  *cellCfgInfo;
#endif
{
   U8  bitMask;

   TRC2(nhAcUtlFillCmnPhyModCfg);

   CMXTA_ZERO(&bitMask, sizeof(U8));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "phyBitMask", 
                     &bitMask);
   
   cellCfgInfo->actvTime.sfn = 10;
   cellCfgInfo->actvTime.subframe = 1;

   cellCfgInfo->bitmask = bitMask;

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_PRACH)
   {
      cellCfgInfo->prachCfg.rootSequenceIndex = 12;
      cellCfgInfo->prachCfg.prachCfgIndex = 22;
      cellCfgInfo->prachCfg.zeroCorrelationZoneCfg = 14;
      cellCfgInfo->prachCfg.highSpeedFlag = TRUE;
      cellCfgInfo->prachCfg.prachFreqOffset = 82;
   }

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_PDSCH)
   {
      cellCfgInfo->cmnPdschCfg.refSigPower = 27;
      cellCfgInfo->cmnPdschCfg.pb = 4;
   }

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_PUSCH)
   {
      cellCfgInfo->cmnPuschCfg.nSB = 4;
      cellCfgInfo->cmnPuschCfg.hoppingMode = 3;
      cellCfgInfo->cmnPuschCfg.puschHoppingOffset = 77;
      cellCfgInfo->cmnPuschCfg.enable64QAM = TRUE;
      cellCfgInfo->cmnPuschCfg.refSig.grpHoppngEnb = TRUE;
      cellCfgInfo->cmnPuschCfg.refSig.seqHoppingEnb = TRUE;
      cellCfgInfo->cmnPuschCfg.refSig.grpAssignPUSCH = 19;
      cellCfgInfo->cmnPuschCfg.refSig.cyclicShift = 8;
   }

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_PHICH)
   {
      cellCfgInfo->cmnPhichCfg.duration = NHU_PHICH_DUR_NORMAL;
      cellCfgInfo->cmnPhichCfg.resrc = NHU_NG_HALF;
   }

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_PUCCH)
   {
      cellCfgInfo->cmnPucchCfg.pucchFixBw = 18;
      cellCfgInfo->cmnPucchCfg.cyclShift = 7;
      cellCfgInfo->cmnPucchCfg.n1PucchAn = 5;
      cellCfgInfo->cmnPucchCfg.deltaShift = NHU_PUCCH_DS1;
   }

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_UL_SRS)
   {
      cellCfgInfo->srsUlCfg.srsCfgType = NHU_CFGTYPE_SETUP;
      cellCfgInfo->srsUlCfg.setup.bwCfg = NHU_SRS_BW4;
      cellCfgInfo->srsUlCfg.setup.subfrmCfg = NHU_SRS_SC12;
      cellCfgInfo->srsUlCfg.setup.srsANSimultTx = TRUE;
      cellCfgInfo->srsUlCfg.setup.srsMaxUpPts = TRUE;
   }

   if (cellCfgInfo->bitmask & NHU_CMN_PHY_CFG_TDD_SF)
   {
      cellCfgInfo->tddSfCfg.sfAssignment = 6;
      cellCfgInfo->tddSfCfg.spclSfPatterns = 8;
   }

   if(nhAccCb.valChk)
   {
     cmMemcpy((U8*)&(gCtfValStore[gValIdx].u.cellRecfgInfo),
                 (U8*)(cellCfgInfo),sizeof(NhuCmnPhyRecfg));
   }


   RETVALUE(CMXTA_ERR_NONE);
   
} /* End of nhAcUtlFillCmnPhyModCfg */
#endif /* RRC_PHY_CFG_SUPP */

/*
*
*       Fun:   nhAcUtlFillNhuUeCfgInfo
*
*       Desc:  This function fills UeCfgInfo in event structure
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuUeCfgInfo
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuUeCfgInfo  *ueCfg,
Ptr           evnt
)
#else
PUBLIC S16 nhAcUtlFillNhuUeCfgInfo(tcCb, spCb, ueCfg, evnt)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuUeCfgInfo  *ueCfg;
Ptr           evnt;
#endif
{
   U8       numAddRb;
   U8       numModRb;
   U8       numRlsRb;
   U8       fillUeIdCfg = 1;
#ifdef RRC_PHY_CFG_SUPP
   U8       uePhyCfgType=0;
#endif /* RRC_PHY_CFG_SUPP */
   NhuRbCfgList      *rbCfgList;
   NhuRbRlsCfgList   *rlsRbCfgList;
   NhuRbCfgList      *rbToAddList;
   U8                 invalideUeCfg = 0;

   TRC2(nhAcUtlFillNhuUeCfgInfo);

   ueCfg->conReCfgCause = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"conReCfgCause",
                  &ueCfg->conReCfgCause);

   /* RB Configuration - ADD/MODIFY/RELEASE */
   if(ueCfg->ueCfgBitMsk & NHU_EXP_CFG_RB_CFG)
   {
      ueCfg->rbCfgAllList.rbCfgTypBitMsk = NHU_CFG_RB_ADD;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"rbCfgType",
                     &(ueCfg->rbCfgAllList.rbCfgTypBitMsk));

      numAddRb = 1;
      numModRb = 0;
      numRlsRb = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"numAddRb",
                     &numAddRb);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"numModRb",
                     &numModRb);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"numRlsRb",
                     &numRlsRb);

      /* ADD RB Configuration */
      if (ueCfg->rbCfgAllList.rbCfgTypBitMsk & NHU_CFG_RB_ADD)
      {
         rbCfgList = &(ueCfg->rbCfgAllList.rbToAddCfgList);
         rbCfgList->numOfRbCfgInfo = numAddRb;
         CMXTA_GET_MEM(evnt, sizeof(NhuRbCfgInfo)*numAddRb,
                    &(rbCfgList->rbCfgInfoList));
         nhAcUtlFillUeRbCfg(tcCb,spCb,&rbCfgList,NHU_CFG_RB_ADD,evnt);
      }

      /* MODIFY RB Configuration */
      if (ueCfg->rbCfgAllList.rbCfgTypBitMsk & NHU_CFG_RB_MODIFY)
      {
         rbCfgList = &(ueCfg->rbCfgAllList.rbToModCfgList);
         rbCfgList->numOfRbCfgInfo = numModRb;
         CMXTA_GET_MEM(evnt, sizeof(NhuRbCfgInfo)*numModRb,
                       &(rbCfgList->rbCfgInfoList));
         nhAcUtlFillUeRbCfg(tcCb,spCb,&rbCfgList,NHU_CFG_RB_MODIFY,evnt);
      }

      /* Release RB Configuration */
      if (ueCfg->rbCfgAllList.rbCfgTypBitMsk & NHU_CFG_RB_RLS)
      {
         rlsRbCfgList = &(ueCfg->rbCfgAllList.rbToRlsCfgList);
         rlsRbCfgList->numOfRbCfgInfo = numRlsRb;
         CMXTA_GET_MEM(evnt, sizeof(NhuRbId)*numRlsRb,
                       &(rlsRbCfgList->rbsToRel));
         nhAcUtlFillRlsRbCfg(tcCb,spCb,&rlsRbCfgList,evnt);
      }
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"invalideUeCfg",
                  &invalideUeCfg);
      if (invalideUeCfg)
      {
         ueCfg->rbCfgAllList.rbCfgTypBitMsk |= NHU_CFG_RB_ADD;
         rbToAddList = &(ueCfg->rbCfgAllList.rbToAddCfgList);
         rbToAddList->rbCfgInfoList[0].rbId.rbId = 0;
      }
   }

#ifdef RRC_PHY_CFG_SUPP
   /* PHY Configuration - ADD/MODIFY/RELEASE */
   if(ueCfg->ueCfgBitMsk & NHU_EXP_CFG_PHY_CFG)
   {
      /* Get the cfgType */
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"uePhyCfgType",
                     &uePhyCfgType);

      /* ADD UE PHY Configuration */
      if (uePhyCfgType & NH_PHY_CFG_ADD)
      {
         nhAcUtlFillUePhyAddCfg(tcCb,spCb,&(ueCfg->phyCfg),NH_PHY_CFG_ADD);
      }

      /* Modify UE PHY Configuration */
      if (uePhyCfgType & NH_PHY_CFG_MODIFY)
      {
         nhAcUtlFillUePhyModCfg(tcCb,spCb,&(ueCfg->phyCfg),NH_PHY_CFG_MODIFY);
      }
   }
#endif /* RRC_PHY_CFG_SUPP */

   /* Transport Channel Configuration */
   if(ueCfg->ueCfgBitMsk & NHU_EXP_CFG_TRCH_CFG)
   {
      nhAcUtlFillTrChCfg(tcCb,spCb,&(ueCfg->trChCfg));
   }

   /* Security Channel Configuration */
   if(ueCfg->ueCfgBitMsk & NHU_EXP_CFG_SEC_CFG)
   {
      nhAcUtlFillSecCfg(tcCb,spCb,&(ueCfg->secCfg));
   }

   /* UE Info Configuration */
   if(ueCfg->ueCfgBitMsk & NHU_EXP_CFG_UE_CFG)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"fillUeIdCfg",
                     &fillUeIdCfg);
      if(fillUeIdCfg)
      {
         nhAcUtlFillNewUeCfg(tcCb,spCb,&(ueCfg->ueInfo));
      }
   }
#ifdef LTE_ADV 
   if(ueCfg->ueCfgBitMsk & NHU_EXP_CFG_UESEC_CFG)
   {
         nhAcUtlFillSCellUeCfg(tcCb,spCb, &(ueCfg->ueSCellCfgInfo));
   }
#endif /* LTE_ADV */

   RETVALUE(CMXTA_ERR_NONE);
} /*-- End of nhAcUtlFillNhuUeCfgInfo --*/

/*
*
*       Fun:   nhAcUtlFillPdcpCfg
*
*       Desc:  This function fills PDCP Configuration 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillPdcpCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuPdcpCfg    *pdcpCfg,
Ptr           evnt
)
#else
PUBLIC S16 nhAcUtlFillPdcpCfg(tcCb, spCb, pdcpCfg, evnt)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuPdcpCfg    *pdcpCfg;
Ptr           evnt;
#endif
{
   U8      bitSta;
   Txt     msgStr[100];
   Txt     frstWrd[3];
   U16     len;
   Size    size;
   Size    arrSize;
   U8      numBitCnt;
   U8      *tmp;
   Bool    cfmReqd=FALSE;
   /* Adding another field to check if ulBitMap is present */
   Bool    ulBitMapStrPres=FALSE;
   
   TRC2(nhAcUtlFillPdcpCfg);

   pdcpCfg->pdcpCfgBitMsk = NHU_PDCP_DISCARD_TMR;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"pdcpCfgBitMsk",
                  &(pdcpCfg->pdcpCfgBitMsk));

   if(pdcpCfg->pdcpCfgBitMsk & NHU_PDCP_DISCARD_TMR)
   {
      pdcpCfg->discardTmr = NHU_PDCP_DISCARD_TMR_MS50;
   }
   if(pdcpCfg->pdcpCfgBitMsk & NHU_PDCP_FLUSH_TMR)
   {
      pdcpCfg->flushTmr = NHU_PDCP_FLUSH_TMR_MS10;
   }
   if(pdcpCfg->pdcpCfgBitMsk & NHU_PDCP_SN_SIZE)
   {
      pdcpCfg->snSize = NHU_PDCP_SN_SIZE_7BITS;
   }
   if(pdcpCfg->pdcpCfgBitMsk & NHU_PDCP_STATUS_RPT)
   {
      pdcpCfg->statusRptReq = TRUE;
   }
   if(pdcpCfg->pdcpCfgBitMsk & NHU_PDCP_HDR_COMPR_INFO)
   {
      pdcpCfg->hdrComprInfo.rohcInfo.maxCid = 1;
      pdcpCfg->hdrComprInfo.rohcInfo.rohcProfileList[0] = 3;
      pdcpCfg->hdrComprInfo.rohcInfo.rohcProfileList[1] = 0;
      pdcpCfg->hdrComprInfo.rohcInfo.rohcProfileList[2] = 0;
      pdcpCfg->hdrComprInfo.rohcInfo.rohcProfileList[3] = 0;
      pdcpCfg->hdrComprInfo.rohcInfo.rohcProfileList[4] = 0;
      pdcpCfg->hdrComprInfo.rohcInfo.rohcProfileList[5] = 0;
      pdcpCfg->hdrComprInfo.rohcInfo.rohcProfileList[6] = 0;
      pdcpCfg->hdrComprInfo.rohcInfo.rohcProfileList[7] = 0;
      pdcpCfg->hdrComprInfo.rohcInfo.rohcProfileList[8] = 0;
   }
   if(pdcpCfg->pdcpCfgBitMsk & NHU_PDCP_SDU_STA_INFO)
   {
      pdcpCfg->hoPdcpSduStaInfo.isHoPres = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"isHoPres",
                  &(pdcpCfg->hoPdcpSduStaInfo.isHoPres));
      if(pdcpCfg->hoPdcpSduStaInfo.isHoPres)
      {
         pdcpCfg->hoPdcpSduStaInfo.ulCountVal = 0;
         if(pdcpCfg->hoPdcpSduStaInfo.isHoPres & NHU_HO_UL)
         {
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,"ulCntVal",
                      &(pdcpCfg->hoPdcpSduStaInfo.ulCountVal));
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"snLen",
                      &(pdcpCfg->hoPdcpSduStaInfo.snLen));

            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32, 
               "ulBitMapStrPres",&ulBitMapStrPres);
            pdcpCfg->hoPdcpSduStaInfo.numBits = 0;;
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"numBits",
                      &(pdcpCfg->hoPdcpSduStaInfo.numBits));
            size = 0;
            size = pdcpCfg->hoPdcpSduStaInfo.numBits / 8;
            if(pdcpCfg->hoPdcpSduStaInfo.numBits % 8)
            {
               size++;
            }
            if ((ulBitMapStrPres == TRUE) && 
                  (pdcpCfg->hoPdcpSduStaInfo.numBits != 0))
            {
               CMXTA_GET_MEM(evnt, sizeof(U8)*size, &(pdcpCfg->hoPdcpSduStaInfo.ulBitMap));
               cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT, "ulBitMapStr", msgStr);

               len = 0;
               arrSize = 0;
               tmp = &pdcpCfg->hoPdcpSduStaInfo.ulBitMap[arrSize];
               while(len < strlen(msgStr))
               {
                  CMXTA_ZERO(frstWrd, sizeof(frstWrd));
                  nhAcUtlStrToken(&msgStr[len], frstWrd, ',');
                  len = len + strlen(frstWrd) + 1;
                  bitSta = atoi(frstWrd);
                  *tmp |= bitSta; 
                  if( arrSize < size)
                  {
                     arrSize++;
                     tmp = &pdcpCfg->hoPdcpSduStaInfo.ulBitMap[arrSize];
                  }
               }
            }
            else
            {
               pdcpCfg->hoPdcpSduStaInfo.numBits = 0;;
            }
         }
         pdcpCfg->hoPdcpSduStaInfo.dlCountVal = 0;
         if(pdcpCfg->hoPdcpSduStaInfo.isHoPres & NHU_HO_DL)
         {
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,"dlCntVal",
                      &(pdcpCfg->hoPdcpSduStaInfo.dlCountVal));
            cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"snLen",
                      &(pdcpCfg->hoPdcpSduStaInfo.snLen));
         }
      }
   }
   if(pdcpCfg->pdcpCfgBitMsk & NHU_PDCP_CFM_REQD)
   {
      pdcpCfg->cfmReqd = 0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,"cfmReqd",
                  &(cfmReqd));
      pdcpCfg->cfmReqd = cfmReqd;
   }
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillPdcpCfg */

/*
*
*       Fun:   nhAcUtlFillTrChCfg
*
*       Desc:  This function fills Transport Channel Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillTrChCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuTrChCfg    *trChCfg
)
#else
PUBLIC S16 nhAcUtlFillTrChCfg(tcCb, spCb, trChCfg)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuTrChCfg    *trChCfg;
#endif
{
   U8 trChCfgType;
   TRC2(nhAcUtlFillTrChCfg);

   trChCfgType = NHU_CFG_TYPE_EXPLICIT;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"trChCfgType",
                  &trChCfgType);

   trChCfg->trChCfgType = trChCfgType;
   if(trChCfg->trChCfgType == NHU_CFG_TYPE_EXPLICIT)
   {
      trChCfg->trChBitMsk |= NHU_TRCH_CFG_UL_HARQ;
      trChCfg->ulHarqCfg.ulMaxHarqTx = NHU_MAX_HARQ_TX_N1;
      trChCfg->ulHarqCfg.deltaHarqOffset = 1;
   } 
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillTrChCfg */

#ifdef ANSI
PUBLIC S16 nhAcFillCpjSecValid
(
NhuSecurityCfg *secCfg
)
#else
PUBLIC S16 nhAcFillCpjSecValid(secCfg)
NhuSecurityCfg *secCfg;
#endif
{
   S16 keyIndex;
   /* Integrity Info */
   if(secCfg->secCfgBitMsk & NHU_SEC_INTG_ALGO)
   {
      gCpjCfgStore[gValIdx].secInfo.intgCfgInfo.intgAlgo
                        =  secCfg->intgCfgInfo.intgAlgo;

      for(keyIndex = 0; keyIndex < NHU_INTG_KEY_LEN; keyIndex++)
         gCpjCfgStore[gValIdx].secInfo.intgCfgInfo.intgKey[keyIndex]
                        = secCfg->intgCfgInfo.intgKey[keyIndex];
   }

   /* Ciphering Info */
   if( secCfg->secCfgBitMsk & NHU_SEC_CIPHER_ALGO)
   {
      gCpjCfgStore[gValIdx].secInfo.cipCfgInfo.ciphAlgo
                        = secCfg->cipherCfgInfo.ciphAlgo;
      for(keyIndex=0; keyIndex < NHU_CIPH_KEY_LEN; keyIndex++)
         gCpjCfgStore[gValIdx].secInfo.cipCfgInfo.cipherCpKey[keyIndex]
                        = secCfg->cipherCfgInfo.cipherCpKey[keyIndex];

      for(keyIndex=0; keyIndex < NHU_CIPH_KEY_LEN; keyIndex++)
         gCpjCfgStore[gValIdx].secInfo.cipCfgInfo.cipherUpKey[keyIndex]
                        = secCfg->cipherCfgInfo.cipherUpKey[keyIndex];
   }
  RETVALUE(ROK);
}


/*
*
*       Fun:   nhAcUtlFillSecCfg
*
*       Desc:  This function fills Security Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillSecCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuSecurityCfg     *secCfg
)
#else
PUBLIC S16 nhAcUtlFillSecCfg(tcCb, spCb, secCfg)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuSecurityCfg     *secCfg;
#endif
{
   U8 i;
   U8 intPres = 1;
   U8 ciphPres = 1;
   U8 intAlgo;
   U8 ciphAlgo;

   TRC2(nhAcUtlFillSecCfg);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"integrityAlgo",
                 &intPres); 
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"cipheringAlgo",
                 &ciphPres); 

   secCfg->secCfgBitMsk = 0;
   if(intPres)
   {
      secCfg->secCfgBitMsk |= NHU_SEC_INTG_ALGO;

      /* Integrity Info */
      secCfg->intgCfgInfo.action = NHU_ACTION_ADD;
      secCfg->intgCfgInfo.intgAlgo = NHU_INTG_ALGO_EIA1;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"chngIntAlgo",
                 &intAlgo);
      if(intAlgo)
         secCfg->intgCfgInfo.intgAlgo = NHU_INTG_ALGO_EIA2;

      for(i=0; i < NHU_INTG_KEY_LEN; i++)
         secCfg->intgCfgInfo.intgKey[i] = i;
   }
   
   if(ciphPres)
   {
      secCfg->secCfgBitMsk |= NHU_SEC_CIPHER_ALGO;
      /* Ciphering Info */
      secCfg->cipherCfgInfo.ciphAlgo = NHU_CIPHER_ALGO_EEA0;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"chngCiphAlgo",
                 &ciphAlgo);
      if(ciphAlgo==1)
        secCfg->cipherCfgInfo.ciphAlgo = NHU_CIPHER_ALGO_EEA1;
      else if(ciphAlgo==2)
        secCfg->cipherCfgInfo.ciphAlgo = NHU_CIPHER_ALGO_EEA2;

      for(i=0; i < NHU_CIPH_KEY_LEN; i++)
         secCfg->cipherCfgInfo.cipherCpKey[i]=i;

      for(i=0; i < NHU_CIPH_KEY_LEN; i++)
         secCfg->cipherCfgInfo.cipherUpKey[i]=i;
   }

   if(nhAccCb.valChk)
   {
      nhAcFillCpjSecValid(secCfg);
   }
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillSecCfg */
#ifdef LTE_ADV
/*
*
*       Fun:   nhAcUtlFillSCellUeCfg
*
*       Desc:  This function fills New UE Info
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillSCellUeCfg
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
NhuUeSecCellInfo  *ueSCellCfgInfo
)
#else
PUBLIC S16 nhAcUtlFillSCellUeCfg(tcCb, spCb, ueSCellCfgInfo)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb; 
NhuUeSecCellInfo  *ueSCellCfgInfo;
#endif
{
   TRC2(nhAcUtlFillSCellUeCfg);

   Txt             parseStr[200];
   U8              numSCells = 0;
   U16             sCellId[7] = {0};
   Inst            macInst[7] = {0};
   SuId            rguUlSapId[7] = {0};
   SuId            rguDlSapId[7] = {0};
   S16             retValue = CMXTA_ERR_NO_VALUE;
   U8              idx = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"numSCells",
         &(ueSCellCfgInfo->numSCells));
   NHAC_XML_GET_VALLIST(parseStr, "sCellId", ":", sCellId, U16, retValue);
   NHAC_XML_GET_VALLIST(parseStr, "macInst", ":", macInst, U8, retValue);
   NHAC_XML_GET_VALLIST(parseStr, "rguUlSapId", ":", rguUlSapId, S16, retValue);
   NHAC_XML_GET_VALLIST(parseStr, "rguDlSapId", ":", rguDlSapId, S16, retValue);

   for (idx = 0; idx < ueSCellCfgInfo->numSCells; idx++)
   {
      if(retValue != CMXTA_ERR_NO_VALUE)
      {
         ueSCellCfgInfo->ueSCellCfg[idx].sCellId = sCellId[idx];
         ueSCellCfgInfo->ueSCellCfg[idx].macInst = macInst[idx];
         ueSCellCfgInfo->ueSCellCfg[idx].rguUlSapId = rguUlSapId[idx];
         ueSCellCfgInfo->ueSCellCfg[idx].rguDlSapId = rguDlSapId[idx];
      }
   }
   RETVALUE(CMXTA_ERR_NONE);
}
#endif /* LTE_ADV */
/*
*
*       Fun:   nhAcUtlFillNewUeCfg
*
*       Desc:  This function fills New UE Info
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNewUeCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuNewUeInfo  *ueInfo
)
#else
PUBLIC S16 nhAcUtlFillNewUeCfg(tcCb, spCb, ueInfo)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb; 
NhuNewUeInfo  *ueInfo;
#endif
{
   TRC2(nhAcUtlFillNewUeCfg);

   ueInfo->newCrnti = 10;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"tCrnti",
                  &(ueInfo->newCrnti));

   RETVALUE(CMXTA_ERR_NONE);
}

/******************  RB related functions required for filling CellCfgInfo 
                     and UeCfgInfo structures  ***************/

/*
*
*       Fun:   nhAcUtlFillUlLogChCfg
*
*       Desc:  This function fills Uplink Logical Channel Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillUlLogChCfg
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuUlLogChMap *ulLogChMap
)
#else
PUBLIC S16 nhAcUtlFillUlLogChCfg(tcCb, spCb, ulLogChMap)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuUlLogChMap *ulLogChMap;
#endif
{
   TRC2(nhAcUtlFillUlLogChCfg);

   ulLogChMap->lcCfg.logChCfgpres = PRSNT_NODEF;
   ulLogChMap->lcCfgType = NHU_CFG_TYPE_EXPLICIT;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"logChCfgpres",
                  &(ulLogChMap->lcCfg.logChCfgpres));
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,"ulLcCfgType",
                  &(ulLogChMap->lcCfgType));

   if(ulLogChMap->lcCfg.logChCfgpres == PRSNT_NODEF &&
      ulLogChMap->lcCfgType == NHU_CFG_TYPE_EXPLICIT)
   {
      ulLogChMap->lcCfg.logChGrp = 1;
   }
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillUlLogChCfg */

/*
*
*       Fun:   nhAcUtlFillUlRlcModeInfo
*
*       Desc:  This function fills Uplink RLC Mode information
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillUlRlcModeInfo
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuUlRlcMode  *ulRlcMode
)
#else
PUBLIC S16 nhAcUtlFillUlRlcModeInfo(tcCb, spCb, ulRlcMode)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuUlRlcMode  *ulRlcMode;
#endif
{
   TRC2(nhAcUtlFillUlRlcModeInfo);


   if(ulRlcMode->mode == NHU_RLC_MODE_UM)
   {
      ulRlcMode->m.umRlc.snFieldLen = 2;
      ulRlcMode->m.umRlc.tReordring = NHU_TREORD_MS5;
   }
   if(ulRlcMode->mode == NHU_RLC_MODE_AM)
   {
      ulRlcMode->m.amRlc.tStatusProh = NHU_STATUS_PROH_MS5;
      ulRlcMode->m.amRlc.tReordring = NHU_TREORD_MS5;
   }
   if(ulRlcMode->mode == NHU_RLC_MODE_TM)
   {
   }
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillUlRlcModeInfo */

#ifdef ANSI
PUBLIC U8 nhAcUtlGetNxtValIdx
(
)
#else
PUBLIC U8 nhAcUtlGetNxtValIdx()
#endif
{
U8 idx=0;
  for(idx=0;idx<25;idx++)
  {
     if(gCpjCfgStore[idx].used == FALSE)
     {
        gValIdx = idx;
        gCkwValStore[idx].used = TRUE;
        gCrgValStore[idx].used = TRUE;
        gCpjCfgStore[idx].used = TRUE;
        RETVALUE(ROK);
     }
  }
  RETVALUE(RFAILED);
}

/*
*
*       Fun:   nhAcUtlFillDlRlcModeInfo
*
*       Desc:  This function fills Downlink RLC Mode information
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillDlRlcModeInfo
(
CmXtaTCCb     *tcCb,
CmXtaSpCb     *spCb,
NhuDlRlcMode  *dlRlcMode
)
#else
PUBLIC S16 nhAcUtlFillDlRlcModeInfo(tcCb, spCb, dlRlcMode)
CmXtaTCCb     *tcCb;
CmXtaSpCb     *spCb;
NhuDlRlcMode  *dlRlcMode;
#endif
{
   TRC2(nhAcUtlFillDlRlcModeInfo);


   if(dlRlcMode->mode == NHU_RLC_MODE_UM)
   {
      dlRlcMode->m.umRlc.snFieldLen = 2;
   }
   if(dlRlcMode->mode == NHU_RLC_MODE_AM)
   {
      dlRlcMode->m.amRlc.maxRetxThresh = NHU_MAX_RETX_THRES_T1;
      dlRlcMode->m.amRlc.pollByte = NHU_POLL_BYTE_KB25;
      dlRlcMode->m.amRlc.pollPdu = NHU_POLL_PDU_P4;
      dlRlcMode->m.amRlc.tPollRetx = NHU_TPOLL_RETX_MS5;
   }
   if(dlRlcMode->mode == NHU_RLC_MODE_TM)
   {
      dlRlcMode->m.tmRlc.bufferSize = 1024;
   }
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillDlRlcModeInfo */

/******************* Miscelleneous functions  ************************/

/*
*
*       Fun:   nhAcUtlFillNhuEvntHdr
*
*       Desc:  This function fills NHU Event Header 
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuEvntHdr
(
CmXtaTCCb   **tcCb,
CmXtaSpCb   **spCb,
NhuHdr      *nhuHdr
)
#else
PUBLIC S16 nhAcUtlFillNhuEvntHdr(tcCb, spCb, nhuHdr)
CmXtaTCCb   **tcCb;
CmXtaSpCb   **spCb; 
NhuHdr      *nhuHdr;
#endif
{

   TRC2(nhAcUtlFillNhuEvntHdr);

   cmXtaXmlGetVal(*tcCb, (*spCb)->childStep, CMXTA_ATTRIB_U16, "cellId",
                  &(nhuHdr->cellId));

   cmXtaXmlGetVal(*tcCb, (*spCb)->childStep, CMXTA_ATTRIB_U16, "ueId",
                  &(nhuHdr->ueId));

   cmXtaXmlGetVal(*tcCb, (*spCb)->childStep, CMXTA_ATTRIB_U32, "transId",
                  &(nhuHdr->transId));
   
   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlFillNhuEvntHdr */

/*
*
*       Fun:   nhAcUtlStrToken
*
*       Desc:  This function extracts the string till delimiter
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlStrToken
(
Txt      *line,                  /* text buffer */
Txt      *frstWord,              /* target for first word after : */
Txt      delimiter
)
#else
PUBLIC S16 nhAcUtlStrToken(line, frstWord,  delimiter)
Txt      *line;                  /* text buffer */
Txt      *frstWord;
Txt      delimiter;
#endif
{
   /* local variable */

   U16         i;
   U16         j;

   TRC2(nhAcUtlStrToken)

   /* extract the first word */
   i = 0;
   j = 0;
   while (line[i] != delimiter)
   {
      /* have we reached the end of the line */
      if ((line[i] == '\0') || (line[i] == '\n'))
      {
         /* NULL terminate it */
         frstWord[j] = '\0';
         /* no ":" found so far so there is an error */
         RETVALUE(RFAILED);
      }

      frstWord[j++] = line[i];
      i++;
   }

   /* NULL terminate it */
   frstWord[j] = '\0';

   RETVALUE(ROK);
}

/*
* 
*       Fun:   nhAcUtlNhuCb
*
*       Desc:  This function is used to free the Queue element
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlNhuCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 nhAcUtlNhuCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   NhAccMsgQElm  *rrcMsg = NULLP;

   TRC2(nhAcUtlNhuCb)

   CMXTA_DBG_PARAM((_cmxtap, "nhAcUtlNhuCb(): \n"));

   rrcMsg = (NhAccMsgQElm *)qElm->data;

   switch (qElm->pst.event)
   {
      case EVTNHUBNDCFM:
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;

      case EVTNHUDATIND:
         CMXTA_FREE(rrcMsg->mBuf, sizeof(NhuDatIndSdus));
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;

      case EVTNHUDATCFM:
         CMXTA_FREE(rrcMsg->mBuf, sizeof(NhuDatCfmSdus));
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;

      case EVTNHUSTAIND:
         CMXTA_FREE(rrcMsg->mBuf, sizeof(NhuStaIndSdus));
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;

      case EVTNHUERRIND:
         CMXTA_FREE(rrcMsg->mBuf, sizeof(NhuErrIndSdus));
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;

      case EVTNHUCFGCFM:
         CMXTA_FREE(rrcMsg->mBuf, sizeof (NhuCfgCfmSdus));
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;

      case EVTNHUCELLCFGCFM:
         CMXTA_FREE(rrcMsg->mBuf, sizeof (NhuCellCfgCfmSdus));
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;

      case EVTNHUCOUNTCFM:
         CMXTA_FREE(((NhuDRBCountInfoLst *)(rrcMsg->mBuf))->member,
                       ((NhuDRBCountInfoLst *)(rrcMsg->mBuf))->numDrbs *
                       sizeof (NhuDrbCountInfo));
         CMXTA_FREE(rrcMsg->mBuf, sizeof (NhuDRBCountInfoLst));
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;

      case EVTNHUPDCPSDUSTACFM:
         CMXTA_FREE(rrcMsg->mBuf, sizeof (NhuPdcpSduStaCfm));
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;
      case EVTNHUDCODECFM:
         /*CMXTA_FREE(rrcMsg->mBuf, sizeof (NhuDecodeSduCfm));*/
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;

      case EVTNHUENCODECFM:
         CMXTA_FREE(rrcMsg->mBuf, sizeof (NhuEncCfmSdus));
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;

      default:
         RETVALUE(CMXTA_ERR_INT);
         break;

   } /* end of switch case */

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlNhuCb() */

#if 0 /*TODO - Need to enahnce for IRAT HO Test */
/*
*
*       Fun:   nhAcUtlFillNhuUE_UTRANHovrInfo
*
*       Desc:  This function fills NHU UTRAN Radio Resource Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuUE_UTRANHovrInfo
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
Ptr         evnt,
NhuUTRANInterRATHovrInfo *ueUtraHovrIfo
)
#else
PUBLIC S16 nhAcUtlFillNhuUE_UTRANHovrInfo(tcCb, spCb, evnt, ueUtraHovrIfo)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
Ptr         evnt;
NhuUTRANInterRATHovrInfo *ueUtraHovrIfo;
#endif
{
   U8             ueCapPresent = 0;
   U32            fLen;
   MsgLen         msgLen, msgLenTemp;
   S16             ret;
   CmPAsnErr      err;
   Buffer         *mBuf;
   Bool           dbgFlag = NH_PASN_DBG_FLAG;
   NhuUTRANUE_RadioAccessCapInfo  uTraUueCap;

   TRC2(nhAcUtlFillNhuUE_UTRANHovrInfo);

   FILL_UINT_TKN(ueUtraHovrIfo->pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraHovrIfo->predefinedConfigStatusLst.choice,
                                    PREDEFINEDCONFIGSTATUSLST_ABSENT);
   FILL_UINT_TKN(ueUtraHovrIfo->uE_SecInfo.choice, UE_SECINFO_PRESENT);
   FILL_UINT_TKN(ueUtraHovrIfo->uE_SecInfo.val.present.pres, PRSNT_NODEF);
   FILL_BIT_STR(ueUtraHovrIfo->uE_SecInfo.val.present.start_CS, 20, 1, evnt);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "ueCapPresent",
                  &ueCapPresent);
   if (ueCapPresent)
   {
      cmMemset((U8 *)&uTraUueCap, 0, sizeof(NhuUTRANUE_RadioAccessCapInfo));
      nhAcUtlFillNhuUE_UTRANCapIE(tcCb, spCb, evnt, &uTraUueCap);
      CMXTA_ALLOCMBUF(&mBuf);

      /* Encode the message */
      ret = cmPAsnEncMsgUalign ((TknU8*)(&uTraUueCap),
                                CM_PASN_USE_MBUF, (Void *)(mBuf),0,
                    nhUTRANUE_RadioAccessCapInfo_Pdu, &err, &fLen, dbgFlag, FALSE);

      if (ret != ROK)
      {
         CMXTA_DBG_PARAM((_cmxtap, "Encoding UTRA UE Capability failed\n"));
         CMXTA_FREEMBUF(mBuf);
         RETVALUE(RFAILED);
      }

      ret = SFndLenMsg(mBuf, (MsgLen *)&msgLenTemp);
      if (ret != ROK)
      {
         CMXTA_DBG_PARAM((_cmxtap, "SFndLenMsg in UTRA UE Capability failed\n"));
         CMXTA_FREEMBUF(mBuf);
         RETVALUE(RFAILED);
      }

      CMXTA_GET_MEM(evnt, msgLenTemp * sizeof(U8),
            (Ptr *)&(ueUtraHovrIfo->ue_CapCont.val.present.val));
      ret = SCpyMsgFix(mBuf, 0, msgLenTemp, ueUtraHovrIfo->ue_CapCont.val.present.val, &msgLen );
      if ((ROK != ret) || (msgLenTemp != msgLen))
      {
         CMXTA_DBG_PARAM((_cmxtap, "SCpyMsgFix in UTRA UE Capability failed\n"));
         CMXTA_FREEMBUF(mBuf);
         RETVALUE(RFAILED);
      }
      
/*      cmMemcpy(ueUtraHovrIfo->ue_CapCont.val.present.val, (CONSTANT U8*)mBuf,
               fLen);*/
      ueUtraHovrIfo->ue_CapCont.val.present.pres = PRSNT_NODEF;
      FILL_UINT_TKN(ueUtraHovrIfo->ue_CapCont.choice, UE_CAPCONT_PRESENT);

      CMXTA_FREEMBUF(mBuf);
   }
   else
   {
      FILL_UINT_TKN(ueUtraHovrIfo->ue_CapCont.choice, UE_CAPCONT_ABSENT);
   }

   FILL_UINT_TKN(ueUtraHovrIfo->v390NonCriticalExtns.choice,
                                          V390NONCRITICALEXTNS_PRESENT);
   FILL_UINT_TKN(ueUtraHovrIfo->v390NonCriticalExtns.val.present.pres,
                                          PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraHovrIfo->v390NonCriticalExtns.val.present.
         interRATHovrInfo_v390ext.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraHovrIfo->v390NonCriticalExtns.val.present.
         interRATHovrInfo_v390ext.ue_RadioAccessCap_v380ext.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraHovrIfo->v390NonCriticalExtns.val.present.
         interRATHovrInfo_v390ext.ue_RadioAccessCap_v380ext.
         ue_PositioningCapExt_v380.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraHovrIfo->v390NonCriticalExtns.val.present.
         interRATHovrInfo_v390ext.ue_RadioAccessCap_v380ext.
         ue_PositioningCapExt_v380.rx_tx_TimeDifferenceTyp2Capable, 1);
   FILL_UINT_TKN(ueUtraHovrIfo->v390NonCriticalExtns.val.present.
         interRATHovrInfo_v390ext.dl_PhysChCapFDD_v380ext.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraHovrIfo->v390NonCriticalExtns.val.present.
         interRATHovrInfo_v390ext.dl_PhysChCapFDD_v380ext.dummy, 0);
   NHAC_FILL_U8_U32_TKN(ueUtraHovrIfo->v390NonCriticalExtns.val.present.
         v3a0NonCriticalExtns.pres, NOTPRSNT, NOTPRSNT);

   RETVALUE(ROK);
}

/*
*
*       Fun:   nhAcUtlFillNhuUE_UTRANCapIE
*
*       Desc:  This function fills NHU UTRAN Radio Resource Configuration
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillNhuUE_UTRANCapIE
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb,
Ptr         evnt,
NhuUTRANUE_RadioAccessCapInfo *ueUtraCapInfo
)
#else
PUBLIC S16 nhAcUtlFillNhuUE_UTRANCapIE(tcCb, spCb, evnt, ueUtraCapInfo)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
Ptr         evnt;
NhuUTRANUE_RadioAccessCapInfo *ueUtraCapInfo;
#endif
{
   NhuUE_RadioAccessCap *ueUtraCap = NULLP;
   NhuUE_RadioAccessCap_v370ext *capExt = NULLP;
   NhuUE_RadioAccessCapabBandFDD *measExt = NULLP;
   NhuCompressedModeMeasCapabFDD  *measCapFDD = NULLP;
   NhuCompressedModeMeasCapabTDD  *measCapTDD = NULLP;
   NhuCompressedModeMeasCapabGSM  *measCapGSM = NULLP;
   S16   idx;
   S16   idx1;

   TRC2(nhAcUtlFillNhuUE_UTRANCapIE);

   FILL_UINT_TKN(ueUtraCapInfo->pres,PRSNT_NODEF);
   ueUtraCap = &(ueUtraCapInfo->ue_RadioAccessCap);
   FILL_UINT_TKN(ueUtraCap->pres, PRSNT_NODEF);
   /* Fill PDCP Cap */
   FILL_UINT_TKN(ueUtraCap->pdcp_Cap.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->pdcp_Cap.losslessSRNS_RelocationSupport, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->pdcp_Cap.supportForRfc2507.choice, 1);
   FILL_UINT_TKN(ueUtraCap->pdcp_Cap.supportForRfc2507.val.supported,
                                       NhuMaxHcCtxtSpacedummyEnum);

   /* RLC Cap */
   FILL_UINT_TKN(ueUtraCap->rlc_Cap.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->rlc_Cap.totalRLC_AM_BufferSize,
                           NhuTotalRLC_AM_BufferSizekb10Enum);
   FILL_UINT_TKN(ueUtraCap->rlc_Cap.maximumRLC_WindowSize,
                                   NhuMaxRLC_WindowSizemws4095Enum);
   FILL_UINT_TKN(ueUtraCap->rlc_Cap.maximumAM_EntityNumber,
                                       NhuMaxAM_EntityNumberRLC_Capam5Enum);

   /* Transport Chennel Cap */
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.dl_TransChCap.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.dl_TransChCap.maxNoBitsReceived,
                            NhuMaxNoBitsb640Enum);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.dl_TransChCap.
         maxConvCodeBitsReceived, NhuMaxNoBitsb640Enum);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.dl_TransChCap.
         turboDecodingSupport.choice, TURBOSUPPORT_NOTSUPP);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.dl_TransChCap.
         maxSimultaneousTransChs, NhuMaxSimultaneousTransChsDLe4Enum);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.dl_TransChCap.
         maxSimultaneousCCTrCH_Count, 1);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.dl_TransChCap.
         maxReceivedTportBlocks, NhuMaxTportBlocksDLtb4Enum);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.dl_TransChCap.maxNumberOfTFC,
                            NhuMaxNumberOfTFC_DLtfc16Enum);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.dl_TransChCap.maxNumberOfTF,
                            NhuMaxNumberOfTFtf32Enum);

   FILL_UINT_TKN(ueUtraCap->transportChannelCap.ul_TransChCap.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.ul_TransChCap.
         maxNoBitsTransmitted, NhuMaxNoBitsb640Enum);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.ul_TransChCap.
         maxConvCodeBitsTransmitted, NhuMaxNoBitsb640Enum);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.ul_TransChCap.
         turboEncodingSupport.choice, TURBOSUPPORT_NOTSUPP);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.ul_TransChCap.
         maxSimultaneousTransChs, NhuMaxSimultaneousTransChsULe4Enum);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.ul_TransChCap.
         modeSpecificInfo.choice, MODESPECIFICINFO_TDD);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.ul_TransChCap.modeSpecificInfo
         .choice,0);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.ul_TransChCap.modeSpecificInfo
         .val.tdd.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.ul_TransChCap.modeSpecificInfo
         .val.tdd.maxSimultaneousCCTrCH_Count, 0);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.ul_TransChCap.
         maxTransmittedBlocks, NhuMaxTportBlocksULtb4Enum);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.ul_TransChCap.maxNumberOfTFC,
                            NhuMaxNumberOfTFC_ULtfc16Enum);
   FILL_UINT_TKN(ueUtraCap->transportChannelCap.ul_TransChCap.maxNumberOfTF,
                            NhuMaxNumberOfTFtf32Enum);

   /* RF Cap */
   FILL_UINT_TKN(ueUtraCap->rf_Cap.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->rf_Cap.tddRF_Cap.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->rf_Cap.tddRF_Cap.ue_PowerClass, 1);
   FILL_UINT_TKN(ueUtraCap->rf_Cap.tddRF_Cap.radioFrequencyTDDBandLst,
                                          NhuRadioFrequencyBandTDDLstaEnum);
   FILL_UINT_TKN(ueUtraCap->rf_Cap.tddRF_Cap.chipRateCap, NhuChipRateCapmcps3_84Enum);
   FILL_UINT_TKN(ueUtraCap->rf_Cap.fddRF_Cap.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->rf_Cap.fddRF_Cap.ue_PowerClass, 1);
   FILL_UINT_TKN(ueUtraCap->rf_Cap.fddRF_Cap.txRxFrequencySeparation,
                  NhuTxRxFrequencySeparationdefault_TxRx_separationEnum);

   /* Fill Phy Channel Cap */
   FILL_UINT_TKN(ueUtraCap->physicalChannelCap.pres, PRSNT_NODEF);
   NHAC_FILL_U8_U32_TKN(ueUtraCap->physicalChannelCap.fddPhysChCap.pres, NOTPRSNT, NOTPRSNT);
   NHAC_FILL_U8_U32_TKN(ueUtraCap->physicalChannelCap.tddPhysChCap.pres, NOTPRSNT, NOTPRSNT);

   /* Fill Multimode RAT Cap */
   FILL_UINT_TKN(ueUtraCap->ue_MultiModeRAT_Cap.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->ue_MultiModeRAT_Cap.multiRAT_CapLst.pres,
                     PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->ue_MultiModeRAT_Cap.multiRAT_CapLst.
                     supportOfGSM, 1);
   FILL_UINT_TKN(ueUtraCap->ue_MultiModeRAT_Cap.multiRAT_CapLst.
                     supportOfMulticarrier, 1);
   FILL_UINT_TKN(ueUtraCap->ue_MultiModeRAT_Cap.multiModeCap, NhuMultiModeCaptddEnum);

   /* Fill Security Cap */
   FILL_UINT_TKN(ueUtraCap->securityCap.pres, PRSNT_NODEF);
   FILL_BIT_STR(ueUtraCap->securityCap.cipheringAlgorithmCap, 16, 1, evnt);
   FILL_BIT_STR(ueUtraCap->securityCap.integrityProtectionAlgorithmCap, 16, 1, evnt);

   /* Fill UE Positioning Cap */
   FILL_UINT_TKN(ueUtraCap->ue_positioning_Cap.pres, PRSNT_NODEF );
   FILL_UINT_TKN(ueUtraCap->ue_positioning_Cap.standaloneLocMethodsSupp, 1);
   FILL_UINT_TKN(ueUtraCap->ue_positioning_Cap.ue_BasedOTDOA_Supp, 1);
   FILL_UINT_TKN(ueUtraCap->ue_positioning_Cap.networkAssistedGPS_Supp,
                  NhuNwAssistedGPS_SuppnetworkBasedEnum);
   FILL_UINT_TKN(ueUtraCap->ue_positioning_Cap.
                  supportForUE_GPS_TimingOfCellFrames, 1);
   FILL_UINT_TKN(ueUtraCap->ue_positioning_Cap.supportForIPDL, 1);

   /* Fill Measurement Cap */
   FILL_UINT_TKN(ueUtraCap->measurementCap.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->measurementCap.downlinkCompressedMode.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->measurementCap.downlinkCompressedMode.
         fdd_Measurements, 1);
   FILL_UINT_TKN(ueUtraCap->measurementCap.downlinkCompressedMode.
         tdd_Measurements, 1);
   NHAC_FILL_U8_U32_TKN(ueUtraCap->measurementCap.downlinkCompressedMode.
         gsm_Measurements.pres, NOTPRSNT, NOTPRSNT);
   FILL_UINT_TKN(ueUtraCap->measurementCap.downlinkCompressedMode.
         multiCarrierMeasurements, 1);
   FILL_UINT_TKN(ueUtraCap->measurementCap.uplinkCompressedMode.pres, PRSNT_NODEF);
   FILL_UINT_TKN(ueUtraCap->measurementCap.uplinkCompressedMode.
         fdd_Measurements, 1);
   FILL_UINT_TKN(ueUtraCap->measurementCap.uplinkCompressedMode.
         tdd_Measurements, 1);
   NHAC_FILL_U8_U32_TKN(ueUtraCap->measurementCap.uplinkCompressedMode.
         gsm_Measurements.pres, NOTPRSNT, NOTPRSNT);
   FILL_UINT_TKN(ueUtraCap->measurementCap.uplinkCompressedMode.
         multiCarrierMeasurements, 1);

   capExt = &(ueUtraCapInfo->ue_RadioAccessCap_v370ext);
   FILL_UINT_TKN(capExt->pres, PRSNT_NODEF);
   FILL_UINT_TKN(capExt->ue_RadioAccessCapabBandFDDLst.noComp, 1);
   CMXTA_GET_MEM(evnt, (capExt->ue_RadioAccessCapabBandFDDLst.noComp.val)*
         (sizeof(NhuUE_RadioAccessCapabBandFDD)),
         &(capExt->ue_RadioAccessCapabBandFDDLst.member));
   for(  idx = 0;  idx < (capExt->ue_RadioAccessCapabBandFDDLst.noComp.val); idx++)
   {
      measExt = &(capExt->ue_RadioAccessCapabBandFDDLst.member[idx]);
      FILL_UINT_TKN(measExt->pres, PRSNT_NODEF);
      FILL_UINT_TKN(measExt->
            radioFrequencyBandFDD, NhuRadioFrequencyBandFDDfdd2100Enum);
      FILL_UINT_TKN(measExt->fddRF_Cap.pres, PRSNT_NODEF);
      FILL_UINT_TKN(measExt->fddRF_Cap.ue_PowerClass,
            NhuUE_PowerClassExtclass1Enum);
      FILL_UINT_TKN(measExt->fddRF_Cap.txRxFrequencySeparation,
            NhuTxRxFrequencySeparationspare2Enum);
      FILL_UINT_TKN(measExt->  measurementCap.pres, PRSNT_NODEF);
      FILL_UINT_TKN(measExt->measurementCap.compressedModeMeasCapabFDDLst.
            noComp, 1);
      CMXTA_GET_MEM(evnt, (measExt->measurementCap.compressedModeMeasCapabFDDLst.noComp.val)*
            (sizeof(NhuCompressedModeMeasCapabFDD)),
            &(measExt->measurementCap.compressedModeMeasCapabFDDLst.member));
      for(  idx1 = 0;  idx1 < (measExt->measurementCap.
                  compressedModeMeasCapabFDDLst.noComp.val); idx1++)
      {
         measCapFDD = &(measExt->measurementCap.compressedModeMeasCapabFDDLst.
                        member[idx1]);
         FILL_UINT_TKN(measCapFDD->pres, PRSNT_NODEF);
         FILL_UINT_TKN(measCapFDD->radioFrequencyBandFDD,
                  NhuRadioFrequencyBandFDDfdd2100Enum);
         FILL_UINT_TKN(measCapFDD->dl_MeasurementsFDD, 1);
         FILL_UINT_TKN(measCapFDD->ul_MeasurementsFDD, 1);
      }
      FILL_UINT_TKN(measExt->measurementCap.compressedModeMeasCapabTDDLst.
            noComp, 1);
      CMXTA_GET_MEM(evnt, (measExt->measurementCap.compressedModeMeasCapabTDDLst.noComp.val)*
            (sizeof(NhuCompressedModeMeasCapabTDD)),
            &(measExt->measurementCap.compressedModeMeasCapabTDDLst.member));
      for(  idx1 = 0;  idx1 < (measExt->measurementCap.
                  compressedModeMeasCapabTDDLst.noComp.val); idx1++)
      {
         measCapTDD = &(measExt->measurementCap.compressedModeMeasCapabTDDLst.
                        member[idx1]);
         FILL_UINT_TKN(measCapTDD->pres, PRSNT_NODEF);
         FILL_UINT_TKN(measCapTDD->radioFrequencyBandTDD,
                  NhuRadioFrequencyBandTDDaEnum);
         FILL_UINT_TKN(measCapTDD->dl_MeasurementsTDD, 1);
         FILL_UINT_TKN(measCapTDD->ul_MeasurementsTDD, 1);
      }
      FILL_UINT_TKN(measExt->measurementCap.compressedModeMeasCapabGSMLst.
            noComp, 1);
      CMXTA_GET_MEM(evnt, (measExt->measurementCap.compressedModeMeasCapabGSMLst.noComp.val)*
            (sizeof(NhuCompressedModeMeasCapabGSM)),
            &(measExt->measurementCap.compressedModeMeasCapabGSMLst.member));
      for(  idx1 = 0;  idx1 < (measExt->measurementCap.
                  compressedModeMeasCapabGSMLst.noComp.val); idx1++)
      {
         measCapGSM = &(measExt->measurementCap.compressedModeMeasCapabGSMLst.
                        member[idx1]);
         FILL_UINT_TKN(measCapGSM->pres, PRSNT_NODEF);
         FILL_UINT_TKN(measCapGSM->radioFrequencyBandGSM,
                  NhuRadioFrequencyBandGSMgsm450Enum);
         FILL_UINT_TKN(measCapGSM->dl_MeasurementsGSM, 1);
         FILL_UINT_TKN(measCapGSM->ul_MeasurementsGSM, 1);
      }
      FILL_UINT_TKN(measExt->measurementCap.compressedModeMeasCapabMC.pres,
           PRSNT_NODEF);
      FILL_UINT_TKN(measExt->measurementCap.compressedModeMeasCapabMC.
           dl_MeasurementsMC, 1);
      FILL_UINT_TKN(measExt->measurementCap.compressedModeMeasCapabMC.
           ul_MeasurementsMC, 1);
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* end of nhAcUtlFillNhuUE_UTRANCapIE */
#endif

/*
*
*       Fun:   nhAcUtlFillFailStatus
*
*       Desc:  This function fills failure status that will be sent as RETVALUE
*              from lower layer primitives
*
*       Ret:   CMXTA_ERR_NONE
*
*       Notes: None
*
*       File:  nhac_nhuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlFillFailStatus
(
CmXtaTCCb   *tcCb,
CmXtaSpCb   *spCb
)
#else
PUBLIC S16 nhAcUtlFillFailStatus(tcCb, spCb)
CmXtaTCCb   *tcCb;
CmXtaSpCb   *spCb;
#endif
{
   U8            pjuDatReqFail = 0;
   U8            kwuDatReqFail = 0;
   U8            crgCfgReqFail = 0;
   U8            ckwCfgReqFail = 0;
   U8            cpjCfgReqFail = 0;
   U8            ueIdChgReqFail = 0;

   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "pjuDatReqFail",
            &(pjuDatReqFail));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "crgCfgReqFail",
            &(crgCfgReqFail));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "ckwCfgReqFail",
            &(ckwCfgReqFail));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "cpjCfgReqFail",
            &(cpjCfgReqFail));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "kwuDatReqFail",
            &(kwuDatReqFail));
   cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, "ueIdChgReqFail",
            &(ueIdChgReqFail));

   if(pjuDatReqFail)
   {
      nhAccCb.reqFail.pjuDat = TRUE;
   }
   else
   {
      nhAccCb.reqFail.pjuDat = FALSE;
   }

   if(kwuDatReqFail)
   {
      nhAccCb.reqFail.kwuDat = TRUE;
   }
   else
   {
      nhAccCb.reqFail.kwuDat = FALSE;
   }

   if(crgCfgReqFail)
   {
      nhAccCb.reqFail.crgCfg = TRUE;
   }
   else
   {
      nhAccCb.reqFail.crgCfg = FALSE;
   }

   if(ckwCfgReqFail)
   {
      nhAccCb.reqFail.ckwCfg = TRUE;
   }
   else
   {
      nhAccCb.reqFail.ckwCfg = FALSE;
   }

   if(cpjCfgReqFail)
   {
      nhAccCb.reqFail.cpjCfg = TRUE;
   }
   else
   {
      nhAccCb.reqFail.cpjCfg = FALSE;
   }

   if(ueIdChgReqFail)
   {
      nhAccCb.reqFail.ueIdChg = TRUE;
   }
   else
   {
      nhAccCb.reqFail.ueIdChg = FALSE;
   }

   RETVALUE(CMXTA_ERR_NONE);

} /* end of nhAcUtlFillFailStatus */
/********************************************************************30**

         End of file:     nhac_nhuutl.c@@/main/3 - Fri Jul  1 01:13:06 2011

*********************************************************************31*/

/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************90**

     ver       pat       init                  description
------------ --------    ---- ----------------------------------------------
/main/1      ---         rer             1. LTE RRC Initial Release.
/main/2      ---         chebli          1. RRC Release 2.1.
nh002.201    ---         vkulkarni       1. Changes due to NhuSysBwCfg 
                                            structure modification
/main/3      ---         sbalakrishna    1. Updated for Release of 3.1.
*********************************************************************91*/

