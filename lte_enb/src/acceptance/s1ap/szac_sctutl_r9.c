
/********************************************************************20**

     Name:     S1AP 

     Type:     C source file

     Desc:     Utility Functions for SCT interface 

     File:     szac_sctutl.c

     Sid:      szac_sctutl_r9.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:13:20 2015

     Prg:      ms

*********************************************************************21*/

/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* timer defines */
#include "cm_hash.h"       /* common hashing */
#include "cm_inet.h"       /* common INET defines */
#include "cm_llist.h"      /* common linked list */
#include "cm_tpt.h"        /* common transport defines */
#include "cm_dns.h"        /* Common DNS library */
#include "cm_mblk.h"       /* common Memory block */
/* sz006.301: Removed un-necessary include files  */
#include "cm_tkns.h"       /* common tokens */
#include "cm_xta.h" 
#include "cm_pasn.h"
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"           /* System Agent */
#endif /* SZ_FTHA */

#include "sct.h"
#include "lsz.h"
#include "szt.h"
#include "szac_asn.h"
#include "sz.h"

#ifdef SB
#include "lsb.h"           /* layer management defines for SCTP layer */
#include "sb_mtu.h"
#include "sb.h"            /* defines and macros for SCTP layer */
#endif
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/
#include "szac_acc.h"
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.h"
#endif


/* header/extern include files (.x) */

#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* timer typedefs */
#include "cm_lib.x"        /* common library functions typedefs */
#include "cm_hash.x"       /* common hashing */

#include "cm_inet.x"       /* common INET */
#include "cm_llist.x"      /* common linked list */
#include "cm_mblk.x"       /* common Memory block */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lib.x"        /* common library */
#include "cm_tpt.x"        /* common transport address */
#include "cm_dns.x"        /* Common DNS library */

#include "cm_xta.x"
#include "cm_pasn.x"
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#endif /* SZ_FTHA */
#include "sct.x"
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "sht.x"           /* System Agent */
#endif
#ifdef SB
#include "lsb.x"           /* layer management typedefs for SCTP layer */
#include "sb_mtu.x"
#include "sb.x"            /* typedefs for SCTP layer */
#endif
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/

#include"szac_asn.x"        /* common ss7 */
using namespace SZ_S1AP_REL9;
#ifndef SZ_ENC_DEC
//#include "szac_asn_pk.x"
//#include "szac_asn_unpk.x"
#endif /* SZ_ENC_DEC */
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"
#include "lsz.x"
#include "szac_acc.x"
#include "szac_sct.x"
#include "szac_szt.x"

EXTERN CmPAsnElmDef *szAcMsgDb_r9[];
EXTERN CmPAsnElmDef *szMsgDbIe[][2];

#ifdef SZTV3
/* sz008.301 Support for Source RNC to Target RNC */
EXTERN CmPAsnElmDef *szMsg3gDbIe[][2];
#endif

/*
 *
 *       Fun:    szAcSctAssocFindnCreate -
 *
 *       Desc:   Find and Create Association Control Block 
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sctutl.c
 *
 */

#ifdef ANSI
PUBLIC SzAcSctAssocCb* szAcSctAssocFindnCreate
(
CmXtaTCCb    *tcCb,
U32   assocIdx,
UConnId   suAssocId,
UConnId   spAssocId
)
#else
PUBLIC SzAcSctAssocCb* szAcSctAssocFindnCreate(tcCb, assocIdx,suAssocId,spAssocId)
CmXtaTCCb    *tcCb;
U32       assocIdx;
UConnId   suAssocId;
UConnId   spAssocId;
#endif
{
   SzAcSctAssocCb* assocCb;

   TRC2(szAcSctAssocFindnCreate)

   assocCb = NULLP;

   CMXTA_DBG_PARAM((_cmxtap, "szAcSctAssocFindnCreate(): \n"));

   /*-- CMXTA_ENHANCE:  Change to Hash Defines --*/
   if (assocIdx >= 10)
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcSctAssocFindnCreate(): resource error\n"));
      RETVALUE(NULLP);
   }

   assocCb = &szAccCb.sctCb.assoc[assocIdx];

   /*-- DSCTP does not maintain the state of the assocCb, if the user
        tries to reuse the same index again, it will result in the old
        values being overwritten by the new values. This is done to 
        aid the use of the same assocCb between different TCs. TA may
        not reset the values in assocCb between different TCs. All TCs
        on DSCTP anyway will not run in parallel with other TCs --*/

   /*-- Generate spAssocId --*/
   if (suAssocId == SZT_CONNID_NOTUSED)
      suAssocId = ++szAccCb.hitCb.nxtConnId;

   assocCb->suAssocId = suAssocId;

   if (spAssocId == SZT_CONNID_NOTUSED)
      assocCb->spAssocId = suAssocId;
   else
      assocCb->spAssocId = spAssocId;

   /*-- Logic not used --*/
   if (assocCb->inUse == FALSE)
   {
      assocCb->inUse = TRUE;
   }

   RETVALUE(assocCb);
} /* end of szAcSctAssocFindnCreate() */

/*
 *
 *       Fun:    szAcSctAssocFind -
 *
 *       Desc:   Find the Association Control Block 
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sctutl.c
 *
 */

#ifdef ANSI
PUBLIC SzAcSctAssocCb* szAcSctAssocFind
(
CmXtaTCCb    *tcCb,
U32   assocIdx
)
#else
PUBLIC SzAcSctAssocCb* szAcSctAssocFind(tcCb, assocIdx)
CmXtaTCCb    *tcCb;
U32   assocIdx;
#endif /* ANSI */
{
   SzAcSctAssocCb* assocCb;

   TRC2(szAcSctAssocFind)

   assocCb = NULLP;

   CMXTA_DBG_PARAM((_cmxtap, "szAcSctAssocFind(): \n"));

   if (assocIdx >= 10)
   {
      CMXTA_DBG_FATAL((_cmxtap, "szAcSctAssocFind(): resource error\n"));
      RETVALUE(NULLP);
   }

   assocCb = &szAccCb.sctCb.assoc[assocIdx];

   /*-- DSCTP does not maintain the state of the assocCb, if the user
        tries to reuse the same index again, it will result in the old
        values being overwritten by the new values. This is done to 
        aid the use of the same assocCb between different TCs. TA may
        not reset the values in assocCb between different TCs. All TCs
        on DSCTP anyway will not run in parallel with other TCs --*/

   /*-- Use this function only if you do want to do validation --*/
   if (assocCb->inUse == FALSE)
   {
#ifndef ALIGN_64BIT   
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : assoc not found: exp (%ld)\n",
                      assocIdx), 2);
#else
      CMXTA_DBG_CALLIND((_cmxtap, "Failed : assoc not found: exp (%d)\n",
                      assocIdx), 2);
#endif
      RETVALUE(NULLP);
   }

   RETVALUE(assocCb);
} /* end of szAcSctAssocFind() */

/*
 *
 *       Fun:    szAcSctTstCbFind -
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sctutl.c
 *
 */
#ifdef ANSI
PUBLIC CmXtaTCCb*  szAcSctTstCbFind
(
)
#else
PUBLIC CmXtaTCCb*  szAcSctTstCbFind (void)
#endif
{
   TRC2(szAcSctTstCbFind)

   /*-- Optimization, check if only one TC running --*/
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);

   RETVALUE(NULLP);
}

/*
 *
 *       Fun:    szAcUtlBuildS1APPdu_r9
 *
 *       Desc:   
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   xx_sctutl.c
 *
 */
#ifdef ANSI
PUBLIC S16  szAcUtlBuildS1APPdu_r9
(
CmXtaTCCb    *tcCb,    /* tcCb data structure  */
CmXtaSpCb    *spCb,    /* spCb data structure  */
Buffer       **mBuf     /* S1AP PDU structure */
)
#else
PUBLIC S16  szAcUtlBuildS1APPdu_r9 (tcCb, spCb, mBuf)
CmXtaTCCb    *tcCb;    /* tcCb data structure  */
CmXtaSpCb    *spCb;    /* spCb data structure  */
Buffer       **mBuf;    /* S1AP PDU structure */
#endif
{
   U8      eventType = 0;
   S16     ret;

   S1apPdu      *pdu ;    /* S1AP PDU structure */
   Mem           mem;


   TRC2(szAcUtlBuildS1APPdu_r9);

   mem.region = 0;
   mem.pool   = 0;

   ret = ROK;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &eventType);
   switch(eventType)
   {
      case SZT_MSG_ID_CXT_SETUP_REQ:
             ret = szAcUtlSztFillInitCxtSetupReq_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_INIT_UE_MSG:
             ret = szAcUtlSztFillInitUeMsg_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_CXT_SETUP_RSP:
         ret = szAcUtlSztFillInitCxtSetupRsp(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_E_RAB_BRR_SETUP_REQ:
             ret = szAcUtlSztFillE_RABSetupRqst_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_E_RAB_BRR_SETUP_RSP:
         ret = szAcUtlSztFillE_RABSetupResp(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_E_RAB_BRR_MOD_RSP:
         ret = szAcUtlSztFillE_RABMdfyResp(tcCb,spCb, &pdu);
         break;

      case SZT_MSG_ID_E_RAB_BRR_MOD_REQ:
         ret = szAcUtlSztFillE_RABMdfyRqst(tcCb,spCb, &pdu);
         break;

      case SZT_MSG_ID_E_RAB_BRR_REL_CMD:
         ret = szAcUtlSztFillE_RABRlsCmmd(tcCb,spCb, &pdu);
         break;

      case SZT_MSG_ID_E_RAB_BRR_REL_REQ:
         ret = szAcUtlSztFillE_RABRlsInd(tcCb,spCb, &pdu);
         break;

      case SZT_MSG_ID_E_RAB_BRR_REL_CMPLT:
         ret = szAcUtlSztFillE_RABRlsResp(tcCb,spCb, &pdu);
         break;

      case SZT_MSG_ID_UE_CXT_MOD_REQ:
         ret = szAcUtlSztFillUECntxtModRqst(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_UE_CXT_MOD_RSP:
         ret = szAcUtlSztFillUECntxtModResp(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_UE_CXT_REL_CMD:
         ret = szAcUtlSztFillUeCxtRlsCmd(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_UE_CXT_REL_CMPL:
         ret = szAcUtlSztFillUeCxtRlsCmpl(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_UE_CXT_REL_REQ:
             ret = szAcUtlSztFillUeCxtRlsReq_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_PAGING:
             ret = szAcUtlSztFillPaging_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_DL_NAS_TPT:
            ret = szAcUtlSztFillDwnlnkNasTpt_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_UL_NAS_TPT:
             ret = szAcUtlSztFillUplnkNasTpt_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_ERR_IND:
         ret = szAcUtlSztFillErrInd(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_SETUP_REQ:
         ret = szAcUtlSztFillS1SetupReq(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_SETUP_RSP:
             ret = szAcUtlSztFillS1SetupRsp_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_RESET:
         ret = szAcUtlSztFillReset(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_RESET_ACK:
         ret = szAcUtlSztFillResetAck(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_HO_REQD:
         ret = szAcUtlSztFillHovrReqd(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_HO_REQ:
             ret = szAcUtlSztFillHovrRqst_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_HO_REQ_ACK:
         ret = szAcUtlSztFillHovrRqstAckg(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_PATH_SWTCH_REQ:
             ret = szAcUtlSztFillPathSwRqst_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_PATH_SWTCH_REQ_ACK:
         ret = szAcUtlSztFillPathSwRqstAckg(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_HO_CMD:
         ret = szAcUtlSztFillHovrCmmd(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_HO_NTFY:
         ret = szAcUtlSztFillHovrNtfy(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_HO_CANCEL:
         ret = szAcUtlSztFillHovrCancel(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_ENB_STA_TRFR:
         ret = szAcUtlSztFillENBStatusTfr(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_MME_STA_TRFR:
         ret = szAcUtlSztFillMMEStatusTfr(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_DEACTV_TRACE:
         ret = szAcUtlSztFillDeactvTrace(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_TRACE_START:
             ret = szAcUtlSztFillTraceStart_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_TRACE_FAIL_IND:
         ret = szAcUtlSztFillTraceFailInd(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_LOC_REPORT_CNTRL:
         ret = szAcUtlSztFillLocRprtngCntrl(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_LOC_REPORT_FAIL_IND:
         ret = szAcUtlSztFillLocRprtngFailInd(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_LOC_REPORT:
         ret = szAcUtlSztFillLocReport(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_ENB_CFG_UPD:
         ret = szAcUtlSztFillENBConfigUpd(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_ENB_CFG_UPD_ACK:
         ret = szAcUtlSztFillENBConfigUpdAckg(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_ENB_CFG_UPD_FAIL:
         ret = szAcUtlSztFillENBConfigUpdFail(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_MME_CFG_UPD:
         ret = szAcUtlSztFillMMEConfigUpd(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_MME_CFG_UPD_ACK:
         ret = szAcUtlSztFillMMEConfigUpdAckg(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_MME_CFG_UPD_FAIL:
         ret = szAcUtlSztFillMMEConfigUpdFail(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_UPLNK_CDMA_TUNNL:
         ret = szAcUtlSztFillUlnkS1cdma2000tunneling(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_DNLNK_CDMA_TUNNL:
         ret = szAcUtlSztFillDlnkS1cdma2000tunneling(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_UE_CAP_INFO:
         ret = szAcUtlSztFillUECapbltyInfoInd(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_OVLD_START:
             ret = szAcUtlSztFillOverloadStart_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_OVLD_STOP:
             ret = szAcUtlSztFillOverloadStop_r9(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_WARNING_REQ:
         ret = szAcUtlSztFillWriteReplaceWarningRqst(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_WARNING_RSP:
         ret = szAcUtlSztFillWriteReplaceWarningResp(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_ENB_DIR_TRANS:
         ret = szAcUtlSztFillMMEDirectInformTfr(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_MME_DIR_TRANS:
         ret = szAcUtlSztFillMMEDirectInformTfr(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_NAS_NON_DEL_IND:
         ret = szAcUtlSztFillNasNonDlvryInd(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_CELL_TRAFFIC_TRACE:
             ret = szAcUtlSztFillCellTrafficTrace_r9(tcCb, spCb, &pdu);
         break;

#ifndef S1AP_REL8A0
      case SZT_MSG_ID_KILL_REQ:
         szAcUtlSztFillKillRqst(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_KILL_RSP:
         szAcUtlSztFillKillResp(tcCb, spCb, &pdu);
         break;
         
      case SZT_MSG_ID_DNLNK_UE_ASSOC_LPPA_TPRT:
         szAcUtlSztFillDlnkUeAssocLppaTprt(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_UPLNK_UE_ASSOC_LPPA_TPRT:
         szAcUtlSztFillUlnkUeAssocLppaTprt(tcCb, spCb, &pdu);
         break; 

      case SZT_MSG_ID_DNLNK_NON_UE_ASSOC_LPPA_TPRT:
         szAcUtlSztFillDlnkNonUeAssocLppaTprt(tcCb, spCb, &pdu);
         break;

      case SZT_MSG_ID_UPLNK_NON_UE_ASSOC_LPPA_TPRT:
         szAcUtlSztFillUlnkNonUeAssocLppaTprt(tcCb, spCb, &pdu);
         break;
#endif /* S1AP_REL8A0 */

         /* sz002.301: Added the setup fail message building */
      case SZT_MSG_ID_SETUP_FAIL:
         szAcUtlSztFillS1SetupFail(tcCb, spCb, &pdu);
         break;

      default:
         ret = RFAILED;
         break;
   }

   szAcEncode_r9(&mem, &pdu, mBuf);

   SZ_FREE_SDU(pdu);

   RETVALUE(ret);
}

/*
*
*       Fun:   szAcUtlSctCb 
*
*       Desc:  This function is used to 
*
*       Ret:   None
*
*       Notes: None
*
*       File:  xx_lhicb.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcUtlSctCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 szAcUtlSctCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   SzAccMsgQElm  *szMsg;

   TRC2(szAcUtlSctCb)

   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSctCb(): \n"));

   szMsg = (SzAccMsgQElm *)qElm->data;

   if(szMsg->u.sctInfo.mBuf != NULLP)
   {
      SPutMsg(szMsg->u.sctInfo.mBuf);
   }

   if (szMsg != NULLP)
   {
      CMXTA_FREE(szMsg, sizeof (SzAccMsgQElm));

      qElm->data = NULLP;
   }

   RETVALUE(CMXTA_ERR_NONE);
} /* End of szAcUtlSctCb() */

/*
*
*       Fun:   szAcEncode_r9 
*
*       Desc:  This function is used to encode the S1AP message
*              Using the acceptance DB.
*
*       Ret:   Ok     - ROK
*              Failed - RFAILED
*
*       Notes: None
*
*       File:  xx_lhicb.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcEncode_r9
(
Mem      *mem,         /* Memory region and pool information */
S1apPdu  **s1apPdu,    /* PDU to be encoded */
Buffer   **mBuf        /* Buffer */
)
#else
PUBLIC S16 szAcEncode_r9 (mem, s1apPdu, mBuf)
Mem     *mem;        /* Memory region and pool information */
S1apPdu **s1apPdu;   /* PDU to be encoded */
Buffer  **mBuf;      /* Buffer */
#endif
{
   /* Local variables */
   U8        dbgFlag = FALSE; 
   S16       ret;
   CmPAsnErr asnErr;
   U32       len=0;

   TRC2(szAcEncode_r9)

#ifdef DEBUGP
      dbgFlag = TRUE;
#endif
      dbgFlag = TRUE;
printf("\n\n szAcEncode_r9 IN SCTUTILS_R9 :\n\n");
   if ((SGetMsg(mem->region, mem->pool, mBuf)) != ROK)
   {
      CMXTA_DBG_PARAM((_cmxtap, "szAcEncode_r9(): Message Buffer Not allocated"));

      SZ_FREE_SDU(*s1apPdu);

      RETVALUE(RFAILED);
   }
   /* Initialize the PASN Error code */
   asnErr.errCode = 0;

   ret = cmPAsnEncMsg((TknU8 *)(&(*s1apPdu)->pdu), CM_PASN_USE_MBUF,
         (Void *)(*mBuf), 0, /* TODO: */
         (CmPAsnElmDef **)szAcMsgDb_r9,
         (CmPAsnErr*)&asnErr,
         &len, dbgFlag, FALSE );

   if (ret == RFAILED)
   {
      /* It's an ASN.1 Error */
      CMXTA_DBG_PARAM((_cmxtap, "szAcEncode_r9(): Encoding failed, Reason (%d)\n",
                       asnErr.errCode));

      SZ_FREE_SDU(*s1apPdu);

      SZ_FREE_BUF(*mBuf);

      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* End of szAcEncode_r9() */

/*
 *  
 *   Fun:  szAcDecode
 *   
 *   Desc:  To decode the message as per ASN.1 PER. 
 *   
 *   Ret:   ROK/RFAILED
 *   
 *   Notes: Invoked thorugh non-database module. 
 *   
 *   File:  sz_msgfn.c
 *   
*/
#ifdef ANSI
PUBLIC S16 szAcDecode
(
 Mem *mem,
 S1apPdu **s1apPdu, 
 Buffer **mBuf
)
#else
PUBLIC S16 szAcDecode (mem, s1apPdu, mBuf)
 Mem *mem;
 S1apPdu **s1apPdu; 
 Buffer **mBuf;
#endif
{
   CmPAsnErr    err;       /* error received while decoding */
   U32          numDecOct; /* number of octets decoded */
   S16          ret;       /* return value from different procedures */
   U8           dbgFlag;
   U32          msgLen;
      

   TRC2(szAcDecode)
                   
   dbgFlag = FALSE;

#ifdef DEBUGP
      dbgFlag = TRUE;
#endif 
      dbgFlag = TRUE;
 printf("\n\n szAcDecode in SCTUTILS : \n\n"); 
   /* Initialise memCp */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, mem, (Ptr *)s1apPdu); 
   if (ret != ROK)
   {
      CMXTA_DBG_PARAM((_cmxtap, "szAcDecode(): Memory allocation failed in Decode \n")); 

      SZ_FREE_BUF(*mBuf);

      RETVALUE(RFAILED);
   }
   /* Initialize the PASN Error code */ 

   err.errCode = 0;
   
   msgLen = 0;

   ret = (cmPAsnDecMsg((Void *)&((*s1apPdu)->pdu), CM_PASN_USE_MBUF, 
                  (Void **)mBuf, &numDecOct, SZ_PASN_VER_ZERO, 
                  (CmPAsnElmDef **)szAcMsgDb_r9, CM_PASN_DROP_ELMNTS, 
                  (CmPAsnErr*)&err, msgLen,
                  (CmMemListCp *)(&(*s1apPdu)->memCp), dbgFlag));
  
   if (ret == RFAILED)
   {
      /* It's an ASN.1 Error */
      CMXTA_DBG_PARAM((_cmxtap, " szAcDecode(): Decoding failed, Reason (%d)\n", 
                               err.errCode)); 
      
      SZ_FREE_BUF(*mBuf);

      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* end of szAcDecode */
 
#if 0 
/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1

/*
 *  
 *   Fun:  szAcEncodeIe 
 *   
 *   Desc:  To encode the IE message as per ASN.1 PER. 
 *   
 *   Ret:   ROK/RFAILED
 *   
 *   Notes: Invoked thorugh non-database module. 
 *   
 *   File:  szac_sztutl.c
 *   
*/
#ifdef ANSI
PUBLIC S16 szAcEncodeIe
(
 Mem *mem,
 SztEncDecEvnt *sztEncDecEvnt
)
#else
PUBLIC S16 szAcEncodeIe (mem, sztEncDecEvnt)
 Mem *mem;
 SztEncDecEvnt *sztEncDecEvnt;
#endif
{
   U8           dbgFlag;
   S16          ret;
   CmPAsnErr    asnErr;
   U32          len=0;
   Void         *event;
   CmPAsnElmDef **msgDb;
   Buffer       *mBuf;
   
   TRC2(szAcIeEncode)

   dbgFlag = FALSE;

#ifdef DEBUGP
      dbgFlag = TRUE;
#endif 
      dbgFlag = TRUE;
 
   if ((SGetMsg(mem->region, mem->pool, &mBuf)) != ROK)
   {
      CMXTA_DBG_PARAM((_cmxtap, "szAcEncodeIe(): Message Buffer Not allocated"));

      SZ_FREE_SDU(sztEncDecEvnt->u.iePdu);

      RETVALUE(RFAILED);
   }
printf("\n\n szAcEncodeIe IN SCTUTILS :\n\n");
   /* Initialize the PASN Error code */ 
   asnErr.errCode = 0;

   if (sztEncDecEvnt->u.iePdu == NULLP)
   {
     RETVALUE(RFAILED);
   }

   switch (sztEncDecEvnt->ieType.val)
   {
      case SZT_REQ_TYPE_ENCDEC_IE_SRCTGET:
      {
         event = (TknU8 *)(&sztEncDecEvnt->u.iePdu->u.srcToTget);
         msgDb = szMsgDbIe[SZT_REQ_TYPE_ENCDEC_IE_SRCTGET];
      }
      break;

      case SZT_REQ_TYPE_ENCDEC_IE_TGETSRC:
      {
         event = (TknU8 *)(&sztEncDecEvnt->u.iePdu->u.tgetToSrc);
         msgDb = szMsgDbIe[SZT_REQ_TYPE_ENCDEC_IE_TGETSRC];
      }
      break;
#ifdef SZTV3
    /* sz008.301 Support for Source RNC to Target RNC */
      case SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC:
         {
            event = (TknU8 *)(&sztEncDecEvnt->u.iePdu->u.srcRncToTgetRnc);
            msgDb = szMsg3gDbIe[SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC];
         }
         break;

      case SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC:
         {
            event = (TknU8 *)(&sztEncDecEvnt->u.iePdu->u.TgetRncToSrcRnc);
            msgDb = szMsg3gDbIe[SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC];
         }
         break;
#endif
      default:
      {
         RETVALUE(RFAILED);
      }
      break;
   }


   ret = cmPAsnEncMsg(event, CM_PASN_USE_MBUF, 
           (Void *)(mBuf), SZ_PASN_VER_ZERO, 
           (CmPAsnElmDef **) msgDb,(CmPAsnErr*)&asnErr, 
            &len, dbgFlag, FALSE );

   if (ret == RFAILED)
   {
      /* It's an ASN.1 Error */
      CMXTA_DBG_PARAM((_cmxtap, "szAcEncode(): Encoding failed, Reason (%d)\n",
            asnErr.errCode));

      SZ_FREE_SDU(sztEncDecEvnt->u.iePdu);

      SZ_FREE_BUF(mBuf);

      RETVALUE(RFAILED);
  }

   SZ_FREE_SDU(sztEncDecEvnt->u.iePdu);
   sztEncDecEvnt->u.mBuf = mBuf;

   RETVALUE(ROK);
} /* end of szAcEncodeIe */
#endif  /* SZTV1 */
#endif 

/**********************************************************************

         End of file:     szac_sctutl_r9.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:13:20 2015

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
/main/3      ---      pkaX  1. Updated for S1AP release 3.1
/main/3     sz002.301 pkaX  1. Added the S1-Setup Fail message bulding
                               in SCTDATIND handler.
/main/3   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/3   sz004.301   va    1. Updated for Transparent Container 
                                 Enc/Dec
/main/3   sz006.301   ve    1. Removed un-necessary include files
/main/3   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
