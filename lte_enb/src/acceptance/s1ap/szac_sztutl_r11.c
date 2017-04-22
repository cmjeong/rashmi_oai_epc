
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    szac_lszhdl.c

     Sid:      szac_sztutl_r11.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:13:31 2015

     Prg:     pk 
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
#ifndef SZ_ENC_DEC
#include "cm_dns.h"         /* common DNS libraru defines */
#endif /* SZ_ENC_DEC */

#include "cm_pasn.h"
#include "sz.h"            /* defines and macros for SZ */
/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.h"
#include "cm_psfft.h"
#include "cm_pftha.h"
#include "cm_psf.h"
#include "sht.h"            /* SZ_FTHA */
#endif /* SZ_FTHA */

#include "sct.h"            /* defines and macros for SZ */
#ifndef SZ_ENC_DEC
#include "lsz.h"            /* defines and macros for SZ */
#endif /* SZ_ENC_DEC */
#include "szac_asn.h"            /* defines and macros for SZ */
#include "szt.h"            /* defines and macros for SZ */
#include "sz_err.h"        /* SZ error defines */
#include "szac_acc.h"        /* defines for SZ acceptance tests */
#ifndef SZ_ENC_DEC
#include "cm_xta.h" 
#endif /* SZ_ENC_DEC */
#ifdef SB
#include "lsb.h"            /* SCTP layer managment defines */
#endif /*SB*/
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/
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
#ifndef SZ_ENC_DEC
#include "cm_dns.x"         /* common DNS libraru defines */
#endif /* SZ_ENC_DEC */

#include "cm_pasn.x"

/* sz003.301: Updted for PSF-S1AP 1.1 release. Added include of FT/HA related
 * header files */
#ifdef SZ_FTHA
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_pftha.x"
#include "cm_psf.x"
#include "sht.x"            /* SZ_FTHA */
#endif /* SZ_FTHA */
#include "sct.x"           /* typedefs for STCP */
#ifndef SZ_ENC_DEC
#include "cm_xta.x" 
#include "lsz.x"           /* layer management typedefs for SZCP */
#endif /* SZ_ENC_DEC */
#include "szac_asn.x"
using namespace SZ_S1AP_REL11;
#ifdef SZTV3
/* sz008.301 Support for source RNC to target RNC */
#include "szt_3gasn.x"
#endif
#include "szt.x"           /* typedefs for SZCP */
#ifndef SZ_ENC_DEC
#include "sz.x"            /* typedefs for SZCP */
#ifdef SB
#include "lsb.x"           /* SCTP layer managment structures */
#endif /*SB*/
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#include "szac_acc.x"      /* typedefs for SZCP acceptance tests */
#endif /* SZ_ENC_DEC */
#include "szac_szt.x"


#ifdef __cplusplus
extern "C"
{
#endif

#ifndef SZ_ENC_DEC
EXTERN SzAcSztPduInfo szacPduInfo[SZAC_MAX_PROCS][SZAC_LSZ_MAX_CONN];

EXTERN S16 szAcUtlSztGetErrCause ARGS((SztS1AP_PDU *pdu, U8 *causeType, U32 *causeVal));
#endif /* SZ_ENC_DEC */
PRIVATE S16 szFillTknBStr32 ARGS ((TknBStr32 *ptr, U16 len, U32 val));


/*
*
*       Fun:   szFillTknBStr32
*
*       Desc:  Call handler to fill Bit String of length less than 32 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PRIVATE S16 szFillTknBStr32
(
TknBStr32  *ptr,     /* Pointer to the structure */
U16         len,     /* length to be filled */
U32         val      /* value to be filled in */
)
#else
PRIVATE S16 szFillTknBStr32(ptr, len, val)
TknBStr32  *ptr;  /* Pointer to the structure */
U16         len;  /* length to be filled */
U32         val;  /* value to be filled in */
#endif
{
   TRC2(szFillTknBStr32)

   if (len > 32)
   {
      RETVALUE(RFAILED);
   }

   /* make the element as present */
   ptr->pres = TRUE;
   ptr->len = (U8) len;

   *(U32*)ptr->val = (val << (32 - len));

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillUDatReqPdu_r11
*
*       Desc:  Call handler to fill common field
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUDatReqPdu_r11
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztUDatEvnt  *uDatEvnt
)
#else
PUBLIC S16 szAcUtlSztFillUDatReqPdu_r11(tcCb, spCb, uDatEvnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SztUDatEvnt  *uDatEvnt;
#endif
{

   U8 eventType;

   TRC2(szAcUtlSztFillUDatReqPdu_r11);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillUDatReqPdu_r11(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillUDatReqPdu_r11(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &(eventType));

   switch(eventType)
   {
      case SZT_MSG_ID_SETUP_REQ:
         {
            if(szAcUtlSztFillS1SetupReq(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_SETUP_RSP:
         {
            if(szAcUtlSztFillS1SetupRsp_r11(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_SETUP_FAIL:
         {
            if(szAcUtlSztFillS1SetupFail(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_RESET:
         {
            if(szAcUtlSztFillReset(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_RESET_ACK:
         {
            if(szAcUtlSztFillResetAck(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_PAGING:
         {
            if(szAcUtlSztFillPaging_r11(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_ERR_IND:
         {
            if(szAcUtlSztFillErrInd(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_OVLD_START:
         {
            if(szAcUtlSztFillOverloadStart_r11(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_OVLD_STOP:
         {
            if(szAcUtlSztFillOverloadStop_r11(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_WARNING_REQ:
         {
            if(szAcUtlSztFillWriteReplaceWarningRqst(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_WARNING_RSP:
         {
            if(szAcUtlSztFillWriteReplaceWarningResp(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_ENB_DIR_TRANS:
         {
            if(szAcUtlSztFillENBDirectInformTfr(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_MME_DIR_TRANS:
         {
            if(szAcUtlSztFillMMEDirectInformTfr(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_ENB_CFG_UPD:
         {
           if(szAcUtlSztFillENBConfigUpd(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_ENB_CFG_UPD_ACK:
         {
           if(szAcUtlSztFillENBConfigUpdAckg(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_ENB_CFG_UPD_FAIL:
         {
           if(szAcUtlSztFillENBConfigUpdFail(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_MME_CFG_UPD:
         {
           if(szAcUtlSztFillMMEConfigUpd(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_MME_CFG_UPD_ACK:
         {
           if(szAcUtlSztFillMMEConfigUpdAckg(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_MME_CFG_UPD_FAIL:
         {
           if(szAcUtlSztFillMMEConfigUpdFail(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
     case SZT_MSG_ID_ENB_CONFIG_TRANS:
         {
           if(szAcUtlSztFillENBConfigTfr(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
     case SZT_MSG_ID_MME_CONFIG_TRANS:
         {
           if(szAcUtlSztFillMMEConfigTfr(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
   
#ifndef S1AP_REL8A0
     case SZT_MSG_ID_KILL_REQ:
         {
           if(szAcUtlSztFillKillRqst(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
         
     case SZT_MSG_ID_KILL_RSP:
         {
           if(szAcUtlSztFillKillResp(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
         
     case SZT_MSG_ID_DNLNK_NON_UE_ASSOC_LPPA_TPRT:
         {
           if(szAcUtlSztFillDlnkNonUeAssocLppaTprt(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
         
     case SZT_MSG_ID_UPLNK_NON_UE_ASSOC_LPPA_TPRT:
         {
           if(szAcUtlSztFillUlnkNonUeAssocLppaTprt(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
#endif
         
      default:
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUDatReqPdu_r11: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);

} /* szAcUtlSztFillUDatReqPdu_r11 */

/*
*
*       Fun:   szAcUtlSztFillConReqPdu_r11
*
*       Desc:  Call handler to fill common field
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillConReqPdu_r11
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztConReq    *conEvnt
)
#else
PUBLIC S16 szAcUtlSztFillConReqPdu_r11(tcCb, spCb, conEvnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SztConReq    *conEvnt;
#endif
{

   U8 eventType;

   TRC2(szAcUtlSztFillConReqPdu_r11);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillConReqPdu_r11(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillConReqPdu_r11(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &(eventType));

   switch(eventType)
   {
      case SZT_MSG_ID_INIT_UE_MSG:
         {
            if(szAcUtlSztFillInitUeMsg_r11(tcCb, spCb, &(conEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_DL_NAS_TPT:
         {
            if(szAcUtlSztFillDwnlnkNasTpt_r11(tcCb, spCb, &(conEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_NO_DATA:
         {
            if(szAcUtlSztFillNoDataMsg(tcCb, spCb, &(conEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_HO_REQ:
         {
            if(szAcUtlSztFillHovrRqst_r11(tcCb, spCb, &(conEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_PATH_SWTCH_REQ:
         {
            if(szAcUtlSztFillPathSwRqst_r11(tcCb, spCb, &(conEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      default:
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillConReqPdu_r11: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);

} /* szAcUtlSztFillConReqPdu_r11 */

/*
*
*       Fun:   szAcUtlSztFillConRspPdu_r11
*
*       Desc:  Call handler to fill common field
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillConRspPdu_r11
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztConRsp    *conEvnt
)
#else
PUBLIC S16 szAcUtlSztFillConRspPdu_r11(tcCb, spCb, conEvnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SztConRsp    *conEvnt;
#endif
{

   U8 eventType;

   TRC2(szAcUtlSztFillConRspPdu_r11);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillConRspPdu_r11(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillConRspPdu_r11(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &(eventType));

   switch(eventType)
   {
      case SZT_MSG_ID_CXT_SETUP_REQ:
         {
            if(szAcUtlSztFillInitCxtSetupReq_r11(tcCb, spCb, &conEvnt->pdu) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_DL_NAS_TPT:
         {
            if(szAcUtlSztFillDwnlnkNasTpt_r11(tcCb, spCb, &(conEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_UL_NAS_TPT:
         {
            if(szAcUtlSztFillUplnkNasTpt_r11(tcCb, spCb, &(conEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_NO_DATA:
         {
            if(szAcUtlSztFillNoDataMsg(tcCb, spCb, &(conEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_HO_REQ_ACK:
         {
            if(szAcUtlSztFillHovrRqstAckg(tcCb, spCb, &(conEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_PATH_SWTCH_REQ_ACK:
         {
            if(szAcUtlSztFillPathSwRqstAckg(tcCb, spCb, &(conEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
         
      default:
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillConRspPdu_r11: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);

} /* szAcUtlSztFillConRspPdu_r11 */

/*
*
*       Fun:   szAcUtlSztFillRelReqPdu_r11
*
*       Desc:  Call handler to fill common field
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillRelReqPdu_r11
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztRelReq    *relEvnt
)
#else
PUBLIC S16 szAcUtlSztFillRelReqPdu_r11(tcCb, spCb, relEvnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SztRelReq    *relEvnt;
#endif
{
   U8    eventType;

   TRC2(szAcUtlSztFillRelReqPdu_r11);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillRelReqPdu_r11(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillRelReqPdu_r11(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &(eventType));

   switch(eventType)
   {
      case SZT_MSG_ID_INIT_CXT_SETUP_FAIL:
         {
            if(szAcUtlSztFillInitCxtSetupFail(tcCb, spCb, &(relEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_UE_CXT_REL_CMD:
         {
            if(szAcUtlSztFillUeCxtRlsCmd(tcCb, spCb, &(relEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_NO_DATA:
         {
            if(szAcUtlSztFillNoDataMsg(tcCb, spCb, &(relEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_HO_FAIL:
         {
            if(szAcUtlSztFillHovrFail(tcCb, spCb, &(relEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_PATH_SWTCH_REQ_FAIL:
         {
            if(szAcUtlSztFillPathSwRqstFail(tcCb, spCb, &(relEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_UE_CXT_REL_CMPL:
         {
            /* for error scenario */
            if(szAcUtlSztFillUeCxtRlsCmpl(tcCb, spCb, &(relEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
       default:
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillRelReqPdu_r11: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }

   
   RETVALUE(ROK);

} /* szAcUtlSztFillRelReqPdu_r11 */

/*
*
*       Fun:   szAcUtlSztFillRelRspPdu_r11
*
*       Desc:  Call handler to fill common field
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillRelRspPdu_r11
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztRelRsp    *relEvnt
)
#else
PUBLIC S16 szAcUtlSztFillRelRspPdu_r11(tcCb, spCb, relEvnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SztRelRsp    *relEvnt;
#endif
{
   U8 eventType;

   TRC2(szAcUtlSztFillRelRspPdu_r11);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillRelRspPdu_r11(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillRelRspPdu_r11(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"eventType",&(eventType));

   switch(eventType)
   {
      case SZT_MSG_ID_UE_CXT_REL_CMPL:
         {
            if(szAcUtlSztFillUeCxtRlsCmpl(tcCb, spCb, &(relEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_PATH_SWTCH_REQ_FAIL:
         {
            /* added for error scenario */
            if(szAcUtlSztFillPathSwRqstFail(tcCb, spCb, &(relEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      default:
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillRelRspPdu_r11: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);

} /* szAcUtlSztFillRelRspPdu_r11 */

/*
*
*       Fun:   szAcUtlSztFillDatReqPdu_r11
*
*       Desc:  Call handler to fill common field
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillDatReqPdu_r11
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztDatEvntReq *datEvnt
)
#else
PUBLIC S16 szAcUtlSztFillDatReqPdu_r11(tcCb, spCb, datEvnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SztDatEvntReq *datEvnt;
#endif
{
   U8 eventType = 0;

   TRC2(szAcUtlSztFillDatReqPdu_r11);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillDatReqPdu_r11(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillDatReqPdu_r11(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"eventType",&(eventType));

   switch(eventType)
   {
      case SZT_MSG_ID_CXT_SETUP_REQ:
         {
            if(szAcUtlSztFillInitCxtSetupReq_r11(tcCb, spCb, &datEvnt->pdu) != ROK)
               RETVALUE(RFAILED);
         }
         break;

      case SZT_MSG_ID_CXT_SETUP_RSP:
         {
            if(szAcUtlSztFillInitCxtSetupRsp(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_UL_NAS_TPT:
         {
            if(szAcUtlSztFillUplnkNasTpt_r11(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_DL_NAS_TPT:
         {
            if(szAcUtlSztFillDwnlnkNasTpt_r11(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_NAS_NON_DEL_IND:
         {
            if(szAcUtlSztFillNasNonDlvryInd(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_E_RAB_BRR_MOD_REQ:
         {
            if(szAcUtlSztFillE_RABMdfyRqst(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_E_RAB_BRR_MOD_RSP:
         {
            if(szAcUtlSztFillE_RABMdfyResp(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_E_RAB_BRR_SETUP_REQ:
         {
            if(szAcUtlSztFillE_RABSetupRqst_r11(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_E_RAB_BRR_SETUP_RSP:
         {
            if(szAcUtlSztFillE_RABSetupResp(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_E_RAB_BRR_REL_CMD:
         {
            if(szAcUtlSztFillE_RABRlsCmmd(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_E_RAB_BRR_REL_CMPLT:
         {
            if(szAcUtlSztFillE_RABRlsResp(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_E_RAB_BRR_REL_REQ:
         {
            if(szAcUtlSztFillE_RABRlsInd(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_UE_CXT_MOD_REQ:
         {
            if(szAcUtlSztFillUECntxtModRqst(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_UE_CXT_MOD_RSP:
         {
            if(szAcUtlSztFillUECntxtModResp(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_UE_CXT_MOD_FAIL:
         {
            if(szAcUtlSztFillUeCxtModFail(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_UE_CXT_REL_REQ:
         {
            if(szAcUtlSztFillUeCxtRlsReq_r11(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_ERR_IND:
         {
           if(szAcUtlSztFillErrInd(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_HO_REQD:
         {
           if(szAcUtlSztFillHovrReqd(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_HO_CMD:
         {
           if(szAcUtlSztFillHovrCmmd(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_HO_PREP_FAIL:
         {
           if(szAcUtlSztFillHovrPrepFail(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_HO_NTFY:
         {
           if(szAcUtlSztFillHovrNtfy(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_HO_CANCEL:
         {
           if(szAcUtlSztFillHovrCancel(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_HO_CANCEL_ACK:
         {
           if(szAcUtlSztFillHovrCancelAckg(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_ENB_STA_TRFR:
         {
           if(szAcUtlSztFillENBStatusTfr(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_MME_STA_TRFR:
         {
           if(szAcUtlSztFillMMEStatusTfr(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_DEACTV_TRACE:
         {
           if(szAcUtlSztFillDeactvTrace(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_TRACE_START:
         {
           if(szAcUtlSztFillTraceStart_r11(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_TRACE_FAIL_IND:
         {
           if(szAcUtlSztFillTraceFailInd(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_LOC_REPORT_CNTRL:
         {
           if(szAcUtlSztFillLocRprtngCntrl(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_LOC_REPORT_FAIL_IND:
         {
           if(szAcUtlSztFillLocRprtngFailInd(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_LOC_REPORT:
         {
           if(szAcUtlSztFillLocReport(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_UPLNK_CDMA_TUNNL:
         {
           if(szAcUtlSztFillUlnkS1cdma2000tunneling(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_DNLNK_CDMA_TUNNL:
         {
           if(szAcUtlSztFillDlnkS1cdma2000tunneling(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_UE_CAP_INFO:
         {
           if(szAcUtlSztFillUECapbltyInfoInd(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_INIT_CXT_SETUP_FAIL:
         {
            /* for error scenario */
            if(szAcUtlSztFillInitCxtSetupFail(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_CELL_TRAFFIC_TRACE:
         {
           if(szAcUtlSztFillCellTrafficTrace_r11(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
        
#ifndef S1AP_REL8A0 
       case SZT_MSG_ID_DNLNK_UE_ASSOC_LPPA_TPRT:
         {
           if(szAcUtlSztFillDlnkUeAssocLppaTprt(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
         
      case SZT_MSG_ID_UPLNK_UE_ASSOC_LPPA_TPRT:
         {
           if(szAcUtlSztFillUlnkUeAssocLppaTprt(tcCb, spCb, &(datEvnt->pdu)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
#endif /* S1AP_REL8A0 */
 
      default:
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillDatReqPdu_r11: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);

} /* szAcUtlSztFillDatReqPdu_r11 */

/*
*
*       Fun:   szAcUtlSztFillS1SetupRsp_r11
*
*       Desc:  Call handler to fill S1 Setup Response message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillS1SetupRsp_r11
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillS1SetupRsp_r11(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillS1SetupRsp_r11
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillS1SetupRsp_r11(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu *szS1SetupRspPdu = NULLP;
   Mem     mem;
   U16     numComp;
   S16     ret;
   U8      pLMNId[10];
   U8      mmeGrpId[10];
   U8      mmeCode[10];
   U8      mmeName[10];
   U32     rltMMECap;
   U16     len;
   SztProtIE_Field_S1SetupRespIEs *ie;
   SztPLMNidentity                *pLMNItem;
   SztSrvdGUMMEIsItem             *gummei;
   SztMME_Group_ID                *mmeGrpId1;
   SztMME_Code                    *mmecode1;
#ifdef S1AP_REL11IE
   U32 mmeRelaySupportIndctr = 0;
#endif
   
   TRC2(szAcUtlSztFillS1SetupRsp_r11);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szS1SetupRspPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupRsp_r11: cmAllocEvnt failed, line%d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szS1SetupRspPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szS1SetupRspPdu->pdu.choice), SZT_TRGR_SUCCESS_OUTCOME);
   szFillTknU8(&(szS1SetupRspPdu->pdu.val.successfulOutcome.pres),PRSNT_NODEF);
   szFillTknU32(&(szS1SetupRspPdu->pdu.val.successfulOutcome.procedureCode),Sztid_S1Setup);
   szFillTknU32(&(szS1SetupRspPdu->pdu.val.successfulOutcome.criticality),SztCriticalityrejectEnum);
   szFillTknU8(&(szS1SetupRspPdu->pdu.val.successfulOutcome.value.u.sztS1SetupResp.pres),PRSNT_NODEF);

   /* Filling 2 mandatory headers */

   numComp = 3;
#ifdef S1AP_REL11IE
   numComp = 4;
#endif
   szFillTknU16(&(szS1SetupRspPdu->pdu.val.successfulOutcome.value.u.sztS1SetupResp.protocolIEs.noComp),numComp);

   /* Allocte memory for 2 IEs */
   if ((cmGetMem(szS1SetupRspPdu, numComp*sizeof(SztProtIE_Field_S1SetupRespIEs),(Ptr*)&szS1SetupRspPdu->pdu.val.successfulOutcome.value.u.sztS1SetupResp.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupRsp_r11: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling MME name*/
   ie = &szS1SetupRspPdu->pdu.val.successfulOutcome.value.u.sztS1SetupResp.protocolIEs.member[0];

   szFillTknU8(&(ie->pres),PRSNT_NODEF);
   szFillTknU32(&(ie->id),Sztid_MMEname);
   szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);

   
   strcpy((char *)mmeName,"MME");
   szFillTknStrOSXL(&(ie->value.u.sztMMEname),3,mmeName,&szS1SetupRspPdu);
  
   

   /* IE3 - Filling servedGUMMEI */
   ie = &szS1SetupRspPdu->pdu.val.successfulOutcome.value.u.sztS1SetupResp.protocolIEs.member[1];

   szFillTknU8(&(ie->pres),PRSNT_NODEF);
   szFillTknU32(&(ie->id),Sztid_SrvdGUMMEIs);
   szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);

   numComp = 1;

   /* IE2 - Allocate memory for GUMMEIs */
   if ((cmGetMem(szS1SetupRspPdu, numComp*sizeof(SztSrvdGUMMEIsItem),(Ptr*)&ie->value.u.sztSrvdGUMMEIs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupReq: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   szFillTknU16(&(ie->value.u.sztSrvdGUMMEIs.noComp),numComp);

   gummei = &(ie->value.u.sztSrvdGUMMEIs.member[0]);

   szFillTknU8(&(gummei->pres),PRSNT_NODEF);

   numComp = 1;

   if ((cmGetMem(szS1SetupRspPdu, numComp*sizeof(SztPLMNidentity),(Ptr*)&gummei->servedPLMNs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupReq: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }
                                                                                                                      
   szFillTknU16(&(gummei->servedPLMNs.noComp),numComp);
                                                                                                                      
   pLMNItem = &(gummei->servedPLMNs.member[0]);
   cmMemset(pLMNId,0,sizeof(pLMNId));
   strcpy((char *)pLMNId,"111");
   len = 3;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"plmnIdVal",&(pLMNId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif
                                                                                                                      
   szFillTknStrOSXL(pLMNItem,len,pLMNId,&szS1SetupRspPdu);


   
     numComp = 1;
                                                                                                                      
   if ((cmGetMem(szS1SetupRspPdu, numComp*sizeof(SztSrvdGroupIDs),(Ptr*)&gummei->servedGroupIDs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupReq: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }
                                                                                                                      
   szFillTknU16(&(gummei->servedGroupIDs.noComp),numComp);
   mmeGrpId1 = &(gummei->servedGroupIDs.member[0]);

   cmMemset(mmeGrpId,0,sizeof(mmeGrpId));
   strcpy((char *)mmeGrpId,"11");
   len = 2;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"mmeGrpVal",&(mmeGrpId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"mmeGrpLen",&(len));
#endif
   szFillTknStr4(mmeGrpId1, (U8)len, 1);


     numComp = 1;
                                                                                                                      
   if ((cmGetMem(szS1SetupRspPdu, numComp*sizeof(SztSrvdMMECs),(Ptr*)&gummei->servedMMECs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupReq: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }
                                                                                                                      
   szFillTknU16(&(gummei->servedMMECs.noComp),numComp);
   mmecode1 = &(gummei->servedMMECs.member[0]);
   cmMemset(mmeCode,0,sizeof(mmeCode));
   strcpy((char *)mmeCode,"1");
   len = 1;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"mmeCodeVal",&(mmeCode));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"mmeCodeLen",&(len));
#endif
  szFillTknStr4((mmecode1), (U8)len, 1);
   gummei->iE_Extns.noComp.pres = NOTPRSNT;

   /* IE4 - Filling Relative MME Capacity */
   ie = &szS1SetupRspPdu->pdu.val.successfulOutcome.value.u.sztS1SetupResp.protocolIEs.member[2];

   szFillTknU8(&(ie->pres),PRSNT_NODEF);
   szFillTknU32(&(ie->id),Sztid_RelativeMMECapacity);
   szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
   /* Get value from xml */
   rltMMECap = 1;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"rltMMECap", &(rltMMECap));
#endif
   szFillTknU32(&(ie->value.u.sztRelativeMMECapacity),rltMMECap);
#ifdef S1AP_REL11IE
   ie = &szS1SetupRspPdu->pdu.val.successfulOutcome.value.u.sztS1SetupResp.protocolIEs.member[3];

   szFillTknU8(&(ie->pres),PRSNT_NODEF);
   szFillTknU32(&(ie->id),Sztid_MMERelaySupportIndicator);
   szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"MMERelaySupportIndctr", &(mmeRelaySupportIndctr));
#endif
    szFillTknU32(&(ie->value.u.sztMMERelaySupportIndicator),mmeRelaySupportIndctr);
#endif   

   *pdu = szS1SetupRspPdu;

   RETVALUE(ROK);
} /* End of szAcUtlSztFillS1SetupRsp_r11 */


/*
*
*       Fun:   szAcUtlSztFillInitUeMsg_r11
*
*       Desc:  Call handler to fill Initial UE message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillInitUeMsg_r11
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInitUeMsg_r11(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillInitUeMsg_r11
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInitUeMsg_r11(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu *szInitUeMsgPdu = NULLP;
   Mem     mem;
   U16     numComp;
   U32     enbId;
   U8      nasPdu[10];
   U8      pLMNId[10];
   U16     len;
   S16     ret;
   S16     idx;
   U32     cause; 
   U8      cellId[28]; 
#ifdef S1AP_REL11IE
   U8   tptAddr[160];
   U8 indx;
   U32 relayNodeIndctr = 0;
#endif
   SztProtIE_Field_InitUEMsg_IEs *ie;

   TRC2(szAcUtlSztFillInitUeMsg_r11);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szInitUeMsgPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitUeMsg_r11: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szInitUeMsgPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szInitUeMsgPdu->pdu.choice), SZT_TRGR_INTI_MSG);
   szFillTknU8(&(szInitUeMsgPdu->pdu.val.initiatingMsg.pres),PRSNT_NODEF);
   szFillTknU32(&(szInitUeMsgPdu->pdu.val.initiatingMsg.procedureCode),Sztid_initialUEMsg);
   szFillTknU32(&(szInitUeMsgPdu->pdu.val.initiatingMsg.criticality),SztCriticalityignoreEnum);

   /* Filling of 3 mandatory IEs */
   szFillTknU8(&(szInitUeMsgPdu->pdu.val.initiatingMsg.value.u.sztInitUEMsg.pres),PRSNT_NODEF);

   numComp = 5;
#ifdef S1AP_REL11IE
   numComp = 7;
#endif
   szFillTknU16(&(szInitUeMsgPdu->pdu.val.initiatingMsg.value.u.sztInitUEMsg.protocolIEs.noComp),numComp);

   /* Allocate memory for 3 IEs */
   if ((cmGetMem(szInitUeMsgPdu, numComp*sizeof(SztProtIE_Field_InitUEMsg_IEs), (Ptr*)&szInitUeMsgPdu->pdu.val.initiatingMsg.value.u.sztInitUEMsg.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitUeMsg_r11: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling enb s1ap id */
   ie = &szInitUeMsgPdu->pdu.val.initiatingMsg.value.u.sztInitUEMsg.protocolIEs.member[0];
  
   enbId = 0; 
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
#endif
   szFillTknU8(&(ie->pres),PRSNT_NODEF);     
   szFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID),enbId);

   /* IE2 - Filling nas pdu */
   ie = &szInitUeMsgPdu->pdu.val.initiatingMsg.value.u.sztInitUEMsg.protocolIEs.member[1];
  
   szFillTknU8(&(ie->pres),PRSNT_NODEF);     
   szFillTknU32(&(ie->id),Sztid_NAS_PDU);
   szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
   cmMemset(nasPdu,0,sizeof(nasPdu));
   strcpy((char *)nasPdu,"111");
   len = 3;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"nasPduVal",&(nasPdu));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"nasPduLen",&(len));
#endif
   szFillTknStrOSXL(&(ie->value.u.sztNAS_PDU), len,nasPdu,&szInitUeMsgPdu);

   /* IE3 - Filling TAI */
   ie = &szInitUeMsgPdu->pdu.val.initiatingMsg.value.u.sztInitUEMsg.protocolIEs.member[2];
  
   szFillTknU8(&(ie->pres),PRSNT_NODEF);     
   szFillTknU32(&(ie->id),Sztid_TAI);
   szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
   szFillTknU8(&(ie->value.u.sztTAI.pres),PRSNT_NODEF);     
   cmMemset(pLMNId,0,sizeof(pLMNId));
   strcpy((char *)pLMNId,"111");
   len = 3;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"plmnIdVal",&(pLMNId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif
   szFillTknStrOSXL(&(ie->value.u.sztTAI.pLMNidentity),len,pLMNId,&szInitUeMsgPdu);     

   len = 2;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"tacLen",&(len));
#endif
   szFillTknStr4(&(ie->value.u.sztTAI.tAC),(U8)len, 1);

   /* IE4 - Filling EUTRAN_CGI */
   ie = &szInitUeMsgPdu->pdu.val.initiatingMsg.value.u.sztInitUEMsg.protocolIEs.member[3];
  
   szFillTknU8(&(ie->pres), PRSNT_NODEF);     
   szFillTknU32(&(ie->id), Sztid_EUTRAN_CGI);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztEUTRAN_CGI.pres), PRSNT_NODEF);
   cmMemset(pLMNId, 0, sizeof(pLMNId));
   strcpy((char *)pLMNId, "111");
   len = 3;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif
   szFillTknStrOSXL(&(ie->value.u.sztEUTRAN_CGI.pLMNidentity), len, pLMNId, &szInitUeMsgPdu);     
   cmMemset(cellId ,0, sizeof(cellId));
   for (idx = 0; idx < 28; idx++)
      cellId[idx] = 0xFF;
   len = 28;
   szFillTknBStr32(&(ie->value.u.sztEUTRAN_CGI.cell_ID), len, 100);

   ie->value.u.sztEUTRAN_CGI.iE_Extns.noComp.pres = NOTPRSNT;

   /* IE4 - Filling sztRRC_Establishment_Cause */
   ie = &szInitUeMsgPdu->pdu.val.initiatingMsg.value.u.sztInitUEMsg.protocolIEs.member[4];
   cause = 0;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause",&(cause));
#endif
   szFillTknU8(&(ie->pres),PRSNT_NODEF);
   szFillTknU32(&(ie->id),Sztid_RRC_Establishment_Cause);
   szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum );
   szFillTknU32(&(ie->value.u.sztRRC_Establishment_Cause),cause);

#ifdef S1AP_REL11IE /* Need to discuss abt remaining IE's*/
      /* IE5 - Filling sztTportLyrAddr */
   ie = &szInitUeMsgPdu->pdu.val.initiatingMsg.value.u.sztInitUEMsg.protocolIEs.member[5];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_GW_TportLyrAddr);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

   cmMemset(tptAddr, 0, sizeof(tptAddr));
            for (indx = 0; indx < 160; indx++)
               tptAddr[indx] = 0xFF;
            len = 160;

    szFillTknStrOSXL(&(ie->value.u.sztTportLyrAddr), len, tptAddr, &szInitUeMsgPdu);
   

     /* IE6 - Filling sztRelayNode_Indicator */
   ie = &szInitUeMsgPdu->pdu.val.initiatingMsg.value.u.sztInitUEMsg.protocolIEs.member[6];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_RelayNode_Indicator);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"RelayNodeIndctr", &(relayNodeIndctr));
#endif
   szFillTknU32(&(ie->value.u.sztRelayNode_Indicator),relayNodeIndctr);

#endif

   *pdu = szInitUeMsgPdu;

   RETVALUE(ROK);

} /* End of szAcUtlSztFillInitUeMsg_r11 */

/*
*
*       Fun:   szAcUtlSztFillInitCxtSetupReq_r11
*
*       Desc:  Call handler to fill Initial Context Setup Request 
*              message.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillInitCxtSetupReq_r11
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInitCxtSetupReq_r11(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillInitCxtSetupReq_r11
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInitCxtSetupReq_r11(pdu)
S1apPdu      **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu *szInitCntxtSetupReqPdu = NULLP;
   S16  ret;
   Mem  mem; 
   U32  enbId;
   U16  idx;
   U16  numComp;
   U32  mmeId;
   U8   gTPId[10];
   U8   tptAddr[10];
   U8   bitrate[8];
   U8   nasPdu[10];
   U16  len;
   U8   secKeyVal[256]; 
#ifndef SZ_ENC_DEC
   ProcId  procId = 0;
   UConnId suConnId = 0;
#endif /* SZ_ENC_DEC */
#ifdef S1AP_REL11IE
   U8 pLMNId[10];
   U8 mmeGrpId[10];
   U8 mmeCode[10];
   SztMME_Group_ID *mmeGrpId1;
   SztMME_Code *mmecode1;
#endif
   SztProtIE_Field_InitCntxtSetupRqstIEs *ie;
   SztProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs *ie1;
#ifdef S1AP_REL11IE
   SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs *ie2;
   U8 correlatn_id[10];
   U32 mngmntBsdMDTAlwedalwed = 0;
#endif

   U32  buggy = 0;
   U32  critBug = 0;

   TRC2(szAcUtlSztFillInitCxtSetupReq_r11);

   mem.region = 0;
   mem.pool   = 0;

   /* Allocate memory for pdu */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, 
         (Ptr *)&szInitCntxtSetupReqPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitCxtSetupReq_r11: cmAllocEvnt failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szInitCntxtSetupReqPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szInitCntxtSetupReqPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.procedureCode),
         Sztid_InitCntxtSetup);
   szFillTknU32(&(szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.criticality),
         SztCriticalityrejectEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
   enbId = szacPduInfo[procId][suConnId].enbId;
   mmeId = szacPduInfo[procId][suConnId].mmeId;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"bug",&(buggy));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"critBug",&(critBug));
#else
   enbId = 0;
   mmeId = 0;
#endif /* SZ_ENC_DEC */

   szFillTknU8(&(szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.pres),PRSNT_NODEF);

   /* Allocate memory for 5 mandatory IEs */
   numComp = 6;
#ifdef S1AP_REL11IE
   numComp = 8;
#endif
   if(critBug)
   {
      numComp++;
   }
   szFillTknU16(&(szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.noComp), numComp);

   if ((cmGetMem(szInitCntxtSetupReqPdu, (numComp * sizeof(SztProtIE_Field_InitCntxtSetupRqstIEs)),
               (Ptr *)&szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitCxtSetupReq_r11: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling MME ID */
   ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[0];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

   /* IE2 - Filling ENB ID */
   ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[1];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

   /* IE3 - Filling Aggregate Max bit rate */
   ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[2];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_uEaggregateMaxBitrate);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU8(&(ie->value.u.sztUEAggMaxBitrate.pres), PRSNT_NODEF);
   cmMemset(bitrate, 0, sizeof(bitrate));
   strcpy((char *)bitrate, "11");
   len = 4;
   szFillTknStrOSXL(&(ie->value.u.sztUEAggMaxBitrate.uEaggregateMaxBitRateDL), len, bitrate, &szInitCntxtSetupReqPdu);
   szFillTknStrOSXL(&(ie->value.u.sztUEAggMaxBitrate.uEaggregateMaxBitRateUL), len, bitrate, &szInitCntxtSetupReqPdu);

   /* IE4 - Filling E-RAB br setup list */
   ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[3];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_E_RABToBeSetupLstCtxtSUReq);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU16(&(ie->value.u.sztE_RABToBeSetupLstCtxtSUReq.noComp), 1);

   numComp = 1;
   if ((cmGetMem(szInitCntxtSetupReqPdu, 1 * sizeof(SztProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs), \
               (Ptr *)&ie->value.u.sztE_RABToBeSetupLstCtxtSUReq.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitCxtSetupReq_r11: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   /* IE4 - Fill in setup List items */
   for(idx = 0; idx < numComp; idx++)
   {
      ie1 = &ie->value.u.sztE_RABToBeSetupLstCtxtSUReq.member[idx];

      szFillTknU8(&(ie1->pres),PRSNT_NODEF);
      szFillTknU32(&(ie1->id), Sztid_E_RABToBeSetupItemCtxtSUReq);
      szFillTknU32(&(ie1->criticality), SztCriticalityrejectEnum);

      szFillTknU8(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.pres), PRSNT_NODEF);
      szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RAB_ID), 15);

      szFillTknU8(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.pres), PRSNT_NODEF);
      szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.qCI), 16);
      szFillTknU8(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.allocationRetentionPriority.pres), PRSNT_NODEF);
      szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.allocationRetentionPriority.priorityLvl), 10);
      szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.allocationRetentionPriority.pre_emptionCapblty), SztPre_emptionCapbltymay_trigger_pre_emptionEnum);
      szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.allocationRetentionPriority.pre_emptionVulnerability), SztPre_emptionVulnerabilitypre_emptableEnum);
      ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.allocationRetentionPriority.iE_Extns.noComp.pres = NOTPRSNT;

      szFillTknU8(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.gbrQosInform.pres), PRSNT_NODEF);
      cmMemset(bitrate, 0, sizeof(bitrate));
      strcpy((char *)bitrate, "11");
      len = 4;
      szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.gbrQosInform.e_RAB_MaxBitrateDL), len, bitrate, &szInitCntxtSetupReqPdu);
      szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.gbrQosInform.e_RAB_MaxBitrateUL), len, bitrate, &szInitCntxtSetupReqPdu);
      szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.gbrQosInform.e_RAB_GuaranteedBitrateDL), len, bitrate, &szInitCntxtSetupReqPdu);
      szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.gbrQosInform.e_RAB_GuaranteedBitrateUL), len, bitrate, &szInitCntxtSetupReqPdu);

      ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.gbrQosInform.iE_Extns.noComp.pres = NOTPRSNT;

      ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.e_RABlevelQoSParams.iE_Extns.noComp.pres = NOTPRSNT;
      cmMemset(tptAddr,0,sizeof(tptAddr));
      strcpy((char *)tptAddr,"11");
      len = 2;
      szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.transportLyrAddr), len, tptAddr, &szInitCntxtSetupReqPdu);
      cmMemset(gTPId,0,sizeof(gTPId));
      strcpy((char *)gTPId,"1111");
      len = 4;
      szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.gTP_TEID), len, gTPId, &szInitCntxtSetupReqPdu);
      cmMemset(nasPdu,0,sizeof(nasPdu));
      strcpy((char *)nasPdu,"111");
      len = 3;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"nasPduVal",&(nasPdu));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"nasPdulen",&(len));
#endif /* SZ_ENC_DEC */
      szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.nAS_PDU), len, nasPdu, &szInitCntxtSetupReqPdu);

#ifndef S1AP_REL11IE
       ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.iE_Extns.noComp.pres = NOTPRSNT;
#else
      szFillTknU16(&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.iE_Extns.noComp), 1);

      if (cmGetMem(szInitCntxtSetupReqPdu, (1 * sizeof(SztProtExtnField_E_RABToBeSetupItemCtxtSUReqExtIEs)), 
           (Ptr *)&(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.iE_Extns.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"szInitCntxtSetupReqPdu: cmGetMem failed, line %d\n", __LINE__));
#endif
               RETVALUE(RFAILED);
       }
          
       ie2 = &(ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.iE_Extns.member[0]);
         
       szFillTknU8(&(ie2->pres), PRSNT_NODEF);
       szFillTknU32(&(ie2->id), Sztid_Correlation_ID);
       szFillTknU32(&(ie2->criticality), SztCriticalityignoreEnum);

       cmMemset(correlatn_id,0,sizeof(correlatn_id));
       cmMemcpy((U8 *)correlatn_id,(const U8 *)"2541",sizeof(correlatn_id));

       len = 4;
       szFillTknStrOSXL(&(ie2->extensionValue.u.sztCorrelation_ID),len,correlatn_id,&szInitCntxtSetupReqPdu);

#endif
   }

   if(!buggy)
   {
      /* IE5 - Filling UE Security Capabilities */
      ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[4];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_UESecurCapabilities);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU8(&(ie->value.u.sztUESecurCapabilities.pres), PRSNT_NODEF);

      len = 16;
      szFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.encryptionAlgorithms), len, 100);

      len = 16;
      szFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.integrityProtectionAlgorithms), len, 100);

      ie->value.u.sztUESecurCapabilities.iE_Extns.noComp.pres = NOTPRSNT;

      /* IE6 - Filling security */
      ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[5];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_SecurKey);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      cmMemset(secKeyVal,0,sizeof(secKeyVal));
      for (idx = 0; idx < 256; idx++)
         secKeyVal[idx] = 0xFF;
      len = 256;
      szFillTknStrOSXL(&(ie->value.u.sztSecurKey), len, secKeyVal, &szInitCntxtSetupReqPdu);
#ifdef S1AP_REL11IE
      /* IE6 - Filling Gummi */
      ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[6];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_GUMMEI_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie->value.u.sztGUMMEI.pres), PRSNT_NODEF);

      cmMemset(pLMNId,0,sizeof(pLMNId));
      cmMemcpy((U8 *)pLMNId,(const U8 *)"111",sizeof(pLMNId));
      len = 3;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"plmnIdVal",&(pLMNId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif
      szFillTknStrOSXL(&(ie->value.u.sztGUMMEI.pLMN_Identity), len, pLMNId, &szInitCntxtSetupReqPdu);

      mmeGrpId1 = &(ie->value.u.sztGUMMEI.mME_Group_ID);
      cmMemset(mmeGrpId,0,sizeof(mmeGrpId));
      cmMemcpy((U8 *)mmeGrpId,(const U8*)"11",sizeof(mmeGrpId));
      len = 2;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"mmeGrpVal",&(mmeGrpId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"mmeGrpLen",&(len));
#endif
      szFillTknStr4(mmeGrpId1, (U8)len, 1);

      mmecode1 = &(ie->value.u.sztGUMMEI.mME_Code);
      cmMemset(mmeCode,0,sizeof(mmeCode));
      cmMemcpy((U8 *)mmeCode,(const U8 *)"1",sizeof(mmeCode));
      len = 1;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"mmeCodeVal",&(mmeCode));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"mmeCodeLen",&(len));
#endif
      szFillTknStr4((mmecode1), (U8)len, 1);
      ie->value.u.sztGUMMEI.iE_Extns.noComp.pres = NOTPRSNT;
           /* IE7 - Filling sztManagementBasedMDTAllowed */
      ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[7];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_ManagementBasedMDTAllowed);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
     
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"ManagementBasedMDTAllowedallowed", &(mngmntBsdMDTAlwedalwed));
#endif

      szFillTknU32(&(ie->value.u.sztManagementBasedMDTAllowed), mngmntBsdMDTAlwedalwed);

#endif
 
   }
   else
   {
      /* IE5 - Filling UE Security Capabilities */
      ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[5];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_UESecurCapabilities);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU8(&(ie->value.u.sztUESecurCapabilities.pres), PRSNT_NODEF);

      len = 16;
      szFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.encryptionAlgorithms), len, 100);

      len = 16;
      szFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.integrityProtectionAlgorithms), len, 100);

      ie->value.u.sztUESecurCapabilities.iE_Extns.noComp.pres = NOTPRSNT;

      /* IE6 - Filling security */
      ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[4];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_SecurKey);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      cmMemset(secKeyVal,0,sizeof(secKeyVal));
      for (idx = 0; idx < 256; idx++)
         secKeyVal[idx] = 0xFF;
      len = 256;
      szFillTknStrOSXL(&(ie->value.u.sztSecurKey), len, secKeyVal, &szInitCntxtSetupReqPdu);

	  
   }

   if(critBug)
   {
#ifndef S1AP_REL11IE   
      ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[6];
#else
      ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[8];
#endif

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

   }

   *pdu = szInitCntxtSetupReqPdu; 

   RETVALUE(ROK);
}


/*
*
*       Fun:   szAcUtlSztFillUeCxtRlsReq_r11 
*
*       Desc:  Call handler to fill UE context release
*              request message.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUeCxtRlsReq_r11
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUeCxtRlsReq_r11(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUeCxtRlsReq_r11
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUeCxtRlsReq_r11(pdu)
S1apPdu   **pdu;
#endif
#endif   /* SZ_ENC_DEC */

{
   S1apPdu *szUeCxtRlsReqPdu = NULLP;
   S16  ret;
   Mem  mem; 
   U32  enbId;
   U16  numComp;
   U32  mmeId;
   U32  cause;
   U8   choice;
#ifndef SZ_ENC_DEC
   ProcId  procId = 0;
   UConnId suConnId = 0;
#endif
   SztProtIE_Field_UECntxtRlsRqst_IEs *ie;

   TRC2(szAcUtlSztFillUeCxtRlsReq_r11);

   mem.region = 0;
   mem.pool   = 0;
#ifdef S1AP_REL11IE
   U32 gwCntxtRlsInd = 0;
#endif
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem,
                     (Ptr *)&szUeCxtRlsReqPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUeCxtRlsReq_r11: cmAllocEvnt failed,line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szUeCxtRlsReqPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szUeCxtRlsReqPdu->pdu.choice), SZT_TRGR_INTI_MSG);
   szFillTknU8(&(szUeCxtRlsReqPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(szUeCxtRlsReqPdu->pdu.val.initiatingMsg.procedureCode),
                  Sztid_UECntxtRlsRqst);
   szFillTknU32(&(szUeCxtRlsReqPdu->pdu.val.initiatingMsg.criticality),
                  SztCriticalityrejectEnum);

   /* Filling 2 mandatory headers */

   /* Get enbId and mmeId */
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
   enbId = szacPduInfo[procId][suConnId].enbId;
   mmeId = szacPduInfo[procId][suConnId].mmeId;
#else
   enbId = 0;
   mmeId = 0;
#endif   /* SZ_ENC_DEC */

   szFillTknU8(&(szUeCxtRlsReqPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsRqst.pres), PRSNT_NODEF);

   numComp = 3;
#ifdef S1AP_REL11IE
    numComp = 4;
#endif
   szFillTknU16(&(szUeCxtRlsReqPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsRqst.protocolIEs.noComp), numComp);

   if ((cmGetMem(szUeCxtRlsReqPdu, (numComp * sizeof(SztProtIE_Field_UECntxtRlsRqst_IEs)),
       (Ptr *)&szUeCxtRlsReqPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsRqst.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUeCxtRlsReq_r11: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   numComp = 0;

   /* IE1 - Filling - MME ID */
   ie = &szUeCxtRlsReqPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsRqst.protocolIEs.member[numComp++];

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#endif
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

   /* IE2 - Filling enb s1ap id */
   ie = &szUeCxtRlsReqPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsRqst.protocolIEs.member[numComp++];
  
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
#endif
   szFillTknU8(&(ie->pres),PRSNT_NODEF);     
   szFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID),enbId);

   /* IE2 - Filling cause */
   ie = &szUeCxtRlsReqPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsRqst.protocolIEs.member[numComp++];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_Cause);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   choice = 0;
   cause = 0;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"choice", &(choice));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
   szFillTknU8(&(ie->value.u.sztCause.choice),choice);
   szFillTknU32(&(ie->value.u.sztCause.val.radioNw),cause);

#ifdef S1AP_REL11IE
   /* IE3 - Filling cause */
   ie = &szUeCxtRlsReqPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsRqst.protocolIEs.member[numComp++];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_GWCntxtRlsInd);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"GWCntxtRlsInd", &(gwCntxtRlsInd));
#endif

   szFillTknU32(&(ie->value.u.sztGWCntxtRlsInd), gwCntxtRlsInd);
#endif

   *pdu = szUeCxtRlsReqPdu; 

   RETVALUE(ROK);

} /* End of szAcUtlSztFillUeCxtRlsReq_r11 */

/*
*
*       Fun:   szAcUtlSztFillUplnkNasTpt_r11
*
*       Desc:  Call handler to fill uplink NAS transport
*              message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUplnkNasTpt_r11
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUplnkNasTpt_r11(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUplnkNasTpt_r11
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUplnkNasTpt_r11(pdu)
S1apPdu      **pdu;
#endif
#endif   /*SZ_ENC_DEC */
{
   S1apPdu *szUplnkNasTptPdu = NULLP;
   Mem     mem;
   U16     numComp;
   U32     mmeId = 0;
   U32     enbId = 0;
   U8      nasPdu[10];
   S16     ret;
   U16     len;
#ifndef SZ_ENC_DEC
   ProcId  procId = 0;
   UConnId suConnId = 0;
#endif
   U8      pLMNId[10];
#ifdef S1AP_REL11IE
   U8   tptAddr[10];
#endif
   SztProtIE_Field_UlnkNASTport_IEs *ie;

   TRC2(szAcUtlSztFillUplnkNasTpt_r11);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szUplnkNasTptPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUplnkNasTpt_r11: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szUplnkNasTptPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szUplnkNasTptPdu->pdu.choice), SZT_TRGR_INTI_MSG);
   szFillTknU8(&(szUplnkNasTptPdu->pdu.val.initiatingMsg.pres),PRSNT_NODEF);
   szFillTknU32(&(szUplnkNasTptPdu->pdu.val.initiatingMsg.procedureCode),Sztid_uplinkNASTport);
   szFillTknU32(&(szUplnkNasTptPdu->pdu.val.initiatingMsg.criticality),SztCriticalityignoreEnum);

   /* Filling of 3 mandatory IEs */
   szFillTknU8(&(szUplnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztUlnkNASTport.pres),PRSNT_NODEF);

   numComp = 5;
#ifdef S1AP_REL11IE
   numComp = 6;
#endif
   szFillTknU16(&(szUplnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztUlnkNASTport.protocolIEs.noComp),numComp);

   /* Allocate memory for 3 IEs */
   if ((cmGetMem(szUplnkNasTptPdu, numComp*sizeof(SztProtIE_Field_UlnkNASTport_IEs), (Ptr*)&szUplnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztUlnkNASTport.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUplnkNasTpt_r11: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   /* Get enbId and mmeId */
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
   enbId = szacPduInfo[procId][suConnId].enbId;
   mmeId = szacPduInfo[procId][suConnId].mmeId;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#endif   /* SZ_ENC_DEC */

   /* IE1 - Filling MME ID */
   ie = &szUplnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztUlnkNASTport.protocolIEs.member[0];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

   /* IE2 - Filling enb s1ap id */
   ie = &szUplnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztUlnkNASTport.protocolIEs.member[1];
  
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
#endif
   szFillTknU8(&(ie->pres),PRSNT_NODEF);     
   szFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID),enbId);

   /* IE3 - Filling nas pdu */
   ie = &szUplnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztUlnkNASTport.protocolIEs.member[2];
  
   szFillTknU8(&(ie->pres),PRSNT_NODEF);     
   szFillTknU32(&(ie->id),Sztid_NAS_PDU);
   szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
   cmMemset(nasPdu,0,sizeof(nasPdu));
   strcpy((char *)nasPdu,"111");
   len = 3;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"nasPduVal",&(nasPdu));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"nasPdulen",&(len));
#endif
   szFillTknStrOSXL(&(ie->value.u.sztNAS_PDU), len, nasPdu, &szUplnkNasTptPdu);

   /* IE4 - Filling EUTRAN_CGI */
   ie = &szUplnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztUlnkNASTport.protocolIEs.member[3];
  
   szFillTknU8(&(ie->pres), PRSNT_NODEF);     
   szFillTknU32(&(ie->id), Sztid_EUTRAN_CGI);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztEUTRAN_CGI.pres), PRSNT_NODEF);
   cmMemset(pLMNId, 0, sizeof(pLMNId));
   strcpy((char *)pLMNId, "111");
   len = 3;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif
   szFillTknStrOSXL(&(ie->value.u.sztEUTRAN_CGI.pLMNidentity), len, pLMNId, &szUplnkNasTptPdu);

   len = 28;
   szFillTknBStr32(&(ie->value.u.sztEUTRAN_CGI.cell_ID), len, 100);

   ie->value.u.sztEUTRAN_CGI.iE_Extns.noComp.pres = NOTPRSNT;

   /* IE5 - Filling TAI */
   ie = &szUplnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztUlnkNASTport.protocolIEs.member[4];
  
   szFillTknU8(&(ie->pres),PRSNT_NODEF);     
   szFillTknU32(&(ie->id),Sztid_TAI);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztTAI.pres),PRSNT_NODEF);     
   cmMemset(pLMNId,0,sizeof(pLMNId));
   strcpy((char *)pLMNId,"111");
   len = 3;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"plmnIdVal",&(pLMNId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif
   szFillTknStrOSXL(&(ie->value.u.sztTAI.pLMNidentity),len,pLMNId,&szUplnkNasTptPdu);     

   len = 2;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"tacLen",&(len));
#endif
   szFillTknStr4(&(ie->value.u.sztTAI.tAC), (U8)len, 1);

   ie->value.u.sztTAI.iE_Extns.noComp.pres = NOTPRSNT;

#ifdef S1AP_REL11IE
    /* IE6 - Filling sztTportLyrAddr */
   ie = &szUplnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztUlnkNASTport.protocolIEs.member[5];
  
   szFillTknU8(&(ie->pres),PRSNT_NODEF);     
   szFillTknU32(&(ie->id),Sztid_GW_TportLyrAddr);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

   cmMemset(tptAddr, 0, sizeof(tptAddr));
   cmMemcpy((U8 *)tptAddr,(const U8 *)"9999",sizeof(tptAddr));
   len = 4;

   szFillTknStrOSXL(&(ie->value.u.sztTportLyrAddr), len, tptAddr, &szUplnkNasTptPdu);

#endif

   *pdu = szUplnkNasTptPdu;

   RETVALUE(ROK);

} /* End of szAcUtlSztFillUplnkNasTpt_r11 */

/*
*
*       Fun:   szAcUtlSztFillDwnlnkNasTpt_r11
*
*       Desc:  Call handler to fill downlink NAS transport
*              message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillDwnlnkNasTpt_r11
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillDwnlnkNasTpt_r11(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillDwnlnkNasTpt_r11
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillDwnlnkNasTpt_r11(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu *szDwnlnkNasTptPdu = NULLP;
   Mem     mem;
   U16     numComp;
   U32     mmeId = 0;
   U32     enbId = 0;
   U8      nasPdu[10];
   S16     ret;
   U16     len;
#ifndef SZ_ENC_DEC
   ProcId  procId = 0;
   UConnId suConnId = 0;
#endif
   SztProtIE_Field_DlnkNASTport_IEs *ie;
   U8     critBug = FALSE;
#ifdef S1AP_REL11IE
   U32 subscriberProfileIDforRFP = 0;
#endif
   TRC2(szAcUtlSztFillDwnlnkNasTpt_r11);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szDwnlnkNasTptPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillDwnlnkNasTpt_r11: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szDwnlnkNasTptPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szDwnlnkNasTptPdu->pdu.choice), SZT_TRGR_INTI_MSG);
   szFillTknU8(&(szDwnlnkNasTptPdu->pdu.val.initiatingMsg.pres),PRSNT_NODEF);
   szFillTknU32(&(szDwnlnkNasTptPdu->pdu.val.initiatingMsg.procedureCode),Sztid_downlinkNASTport);
   szFillTknU32(&(szDwnlnkNasTptPdu->pdu.val.initiatingMsg.criticality),SztCriticalityignoreEnum);

   /* Filling of 3 mandatory IEs */
   szFillTknU8(&(szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.pres),PRSNT_NODEF);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"critBug",&(critBug));
#endif
   numComp = 3;
#ifdef S1AP_REL11IE
   numComp = 4;
#endif
   if(critBug)
   {
      numComp++;
   }
   szFillTknU16(&(szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.protocolIEs.noComp),numComp);

   /* Allocate memory for 3 IEs */
   if ((cmGetMem(szDwnlnkNasTptPdu, numComp*sizeof(SztProtIE_Field_DlnkNASTport_IEs), (Ptr*)&szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillDwnlnkNasTpt_r11: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   /* Get enbId and mmeId */
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
   enbId = szacPduInfo[procId][suConnId].enbId;
   mmeId = szacPduInfo[procId][suConnId].mmeId;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#endif   /* SZ_ENC_DEC */

   /* IE1 - Filling MME ID */
   if(critBug)
   {
      ie = &szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.protocolIEs.member[0];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

      ie = &szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.protocolIEs.member[1];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

      /* IE2 - Filling enb s1ap id */
      ie = &szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.protocolIEs.member[2];

#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
#endif
      szFillTknU8(&(ie->pres),PRSNT_NODEF);     
      szFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID),enbId);

      /* IE3 - Filling nas pdu */
      ie = &szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.protocolIEs.member[3];

      szFillTknU8(&(ie->pres),PRSNT_NODEF);     
      szFillTknU32(&(ie->id),Sztid_NAS_PDU);
      szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
      cmMemset(nasPdu,0,sizeof(nasPdu));
      strcpy((char *)nasPdu,"111");
      len = 3;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"nasPduVal",&(nasPdu));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"nasPduLen",&(len));
#endif
      szFillTknStrOSXL(&(ie->value.u.sztNAS_PDU), len, nasPdu, &szDwnlnkNasTptPdu);
   }
   else
   {
      ie = &szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.protocolIEs.member[0];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

      /* IE2 - Filling enb s1ap id */
      ie = &szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.protocolIEs.member[1];

#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
#endif
      szFillTknU8(&(ie->pres),PRSNT_NODEF);     
      szFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID),enbId);

      /* IE3 - Filling nas pdu */
      ie = &szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.protocolIEs.member[2];

      szFillTknU8(&(ie->pres),PRSNT_NODEF);     
      szFillTknU32(&(ie->id),Sztid_NAS_PDU);
      szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
      cmMemset(nasPdu,0,sizeof(nasPdu));
      strcpy((char *)nasPdu,"111");
      len = 3;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"nasPduVal",&(nasPdu));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"nasPduLen",&(len));
#endif
      szFillTknStrOSXL(&(ie->value.u.sztNAS_PDU), len, nasPdu, &szDwnlnkNasTptPdu);
#ifdef S1AP_REL11IE
      /* IE4 - Filling nas pdu */
      ie = &szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.protocolIEs.member[3];

      szFillTknU8(&(ie->pres),PRSNT_NODEF);     
      szFillTknU32(&(ie->id),Sztid_SubscriberProfileIDforRFP);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      subscriberProfileIDforRFP = 77;
#ifndef SZ_ENC_DEC
	  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"SubscriberProfileIDforRFP", &(subscriberProfileIDforRFP));
#endif
	  szFillTknU32(&(ie->value.u.sztSubscriberProfileIDforRFP),subscriberProfileIDforRFP);

#endif
   }

   *pdu = szDwnlnkNasTptPdu;

   RETVALUE(ROK);

} /* End of szAcUtlSztFillDwnlnkNasTpt_r11 */


/*
*
*       Fun:   szAcUtlSztFillPaging_r11 
*
*       Desc:  Call handler to fill Paging message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillPaging_r11
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillPaging_r11(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillPaging_r11
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillPaging_r11(pdu)
S1apPdu    **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu *szPagingPdu = NULLP;
   S16  ret;
   Mem  mem; 
   U16  numComp;
   U32  pagDrx;
   U8   pLMNId[10];
   U8   ueIdVal[10];
   U8   imsiVal[10];
   U16  len;
   U32  idx;
   SztProtIE_Field_PagIEs *ie;
   SztProtIE_Field_TAIItemIEs *ie1;
   U8   critBug = 0;
#ifdef S1AP_REL11IE
   U32 pagPriotyLevel = 0;
#endif
   TRC2(szAcUtlSztFillPaging_r11);

   mem.region = 0;
   mem.pool   = 0;

   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem,
                     (Ptr *)&szPagingPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPaging_r11: cmAllocEvnt failed,line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szPagingPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szPagingPdu->pdu.choice), SZT_TRGR_INTI_MSG);
   szFillTknU8(&(szPagingPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(szPagingPdu->pdu.val.initiatingMsg.procedureCode),
                  Sztid_Pag);
   szFillTknU32(&(szPagingPdu->pdu.val.initiatingMsg.criticality),
                  SztCriticalityignoreEnum);
   szFillTknU8(&(szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.pres), PRSNT_NODEF);

   /* Filling 5 mandatory headers */

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"critBug",&(critBug));
#endif /* SZ_ENC_DEC */

   numComp = 5;
#ifdef S1AP_REL11IE
   numComp = 6;
#endif
   if(critBug)
   {
      numComp++;
   }

   szFillTknU16(&(szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.noComp), numComp);

   if ((cmGetMem(szPagingPdu, (numComp * sizeof(SztProtIE_Field_PagIEs)),
       (Ptr *)&szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPaging_r11: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   /* IE1 - UE identity index value */
   ie = &szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.member[0];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_UEIdentityIdxValue);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   cmMemset(ueIdVal,0,sizeof(ueIdVal));
   for (idx = 0; idx < 10; idx++)
      ueIdVal[idx] = 0xFF;
   len = 10;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"ueIdVal",&(ueIdVal));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"ueIdLen",&(len));
#endif /* SZ_ENC_DEC */
   szFillTknBStr32(&(ie->value.u.sztUEIdentityIdxValue), len, 100);
   
   /* IE2 - UE Paging Id */
   ie = &szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.member[1];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_UEPagID);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie->value.u.sztUEPagID.choice), UEPAGID_IMSI);
   cmMemset(imsiVal,0,sizeof(imsiVal));
   strcpy((char *)imsiVal,"111");
   len = 3;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"imsiVal",&(imsiVal));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"imsiLen",&(len));
#endif /* SZ_ENC_DEC */
   szFillTknStrOSXL(&(ie->value.u.sztUEPagID.val.iMSI), len, imsiVal, &szPagingPdu);
   /* IE3 - Paging DRX */
   ie = &szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.member[2];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_pagingDRX);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   pagDrx = 1;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"pagDrx", &(pagDrx));
#endif /* SZ_ENC_DEC */
   szFillTknU32(&(ie->value.u.sztPagDRX),pagDrx);

   /* IE4 - Filling paging cause */
   ie = &szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.member[3];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_CNDomain);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU32(&(ie->value.u.sztCNDomain), SztCNDomaincsEnum);

   /* IE5 - Filling paging TAI list */
   ie = &szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.member[4];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_TAILst);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   szFillTknU16(&(ie->value.u.sztTAILst.noComp),1);     

   numComp = 1;

   if ((cmGetMem(szPagingPdu, (numComp * sizeof(SztProtIE_Field_TAIItemIEs)),
       (Ptr *)&(ie->value.u.sztTAILst.member)) !=ROK))
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPaging_r11: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }
  
   ie1 = &(ie->value.u.sztTAILst.member[0]);
   
   szFillTknU8(&(ie1->pres), PRSNT_NODEF);
   szFillTknU32(&(ie1->id), Sztid_TAIItem);
   szFillTknU32(&(ie1->criticality), SztCriticalityignoreEnum);
   szFillTknU8(&(ie1->value.u.sztTAIItem.pres), PRSNT_NODEF);
   szFillTknU8(&(ie1->value.u.sztTAIItem.tAI.pres), PRSNT_NODEF);
 
   cmMemset(pLMNId,0,sizeof(pLMNId));
   strcpy((char *)pLMNId,"111");
   len = 3;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"plmnIdVal",&(pLMNId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif /* SZ_ENC_DEC */

   szFillTknStrOSXL(&(ie1->value.u.sztTAIItem.tAI.pLMNidentity), len, pLMNId, &szPagingPdu);

   len = 2;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"tacLen",&(len));
#endif /* SZ_ENC_DEC */
   szFillTknStr4(&(ie1->value.u.sztTAIItem.tAI.tAC), (U8)len, 1);
#ifdef S1AP_REL11IE
   if (!critBug)
{
      /* IE6 - Filling paging priority */
   ie = &szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.member[5];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_PagPriority);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"PagPrioritypriolevel", &(pagPriotyLevel));
#endif

   szFillTknU32(&(ie->value.u.sztPagPriority), pagPriotyLevel);
}
#endif


   if(critBug)
   {
#ifdef S1AP_REL11IE
      ie = &szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.member[6];
#else
      ie = &szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.member[5];
#endif
      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_Crit_Tst1);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

      len = 10;
 
     szFillTknBStr32(&(ie->value.u.sztUEIdentityIdxValue), len, 100);
   }
   *pdu = szPagingPdu;

   RETVALUE(ROK);

} /* End of szAcUtlSztFillPaging_r11 */

/*
*
*       Fun:   szAcUtlSztFillE_RABSetupRqst_r11 
*
*       Desc:  Call handler to fill E-RAB Setup request
*              message.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillE_RABSetupRqst_r11
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABSetupRqst_r11(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillE_RABSetupRqst_r11
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABSetupRqst_r11(pdu)
S1apPdu    **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu   *eRABSetupRqstPdu = NULLP;
   S16        numComp;
   S16        idx;
   S16        ret;
   Mem        mem; 
   U8         gTPId[10];
   U8         tptAddr[10];
   U8         bitrate[8];
   U8         nasPdu[10];
   U16        len;
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif /* SZ_ENC_DEC */
   SztProtIE_Field_E_RABSetupRqstIEs *ie;
   SztProtIE_SingleCont_E_RABToBeSetupItemBrSUReqIEs *ie1;
#ifdef S1AP_REL11IE
   SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs *ie2;
   U8 correlatn_id[10];
#endif
   TRC2(szAcUtlSztFillErrInd);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eRABSetupRqstPdu);

   cmMemset((U8 *)&(eRABSetupRqstPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(eRABSetupRqstPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(eRABSetupRqstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(eRABSetupRqstPdu->pdu.val.initiatingMsg.procedureCode), Sztid_E_RABSetup);
   szFillTknU32(&(eRABSetupRqstPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;
      szFillTknU8(&(eRABSetupRqstPdu->pdu.val.initiatingMsg.value.u.sztE_RABSetupRqst.pres), PRSNT_NODEF);
      szFillTknU16(&(eRABSetupRqstPdu->pdu.val.initiatingMsg.value.u.sztE_RABSetupRqst.protocolIEs.noComp), numComp);

      if ((cmGetMem(eRABSetupRqstPdu, (numComp * sizeof(SztProtIE_Field_E_RABSetupRqstIEs)), 
             (Ptr *)&eRABSetupRqstPdu->pdu.val.initiatingMsg.value.u.sztE_RABSetupRqst.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABSetupRqst_r11: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
         RETVALUE(RFAILED);
      }

      {
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
         enbId = szacPduInfo[procId][suConnId].enbId;
         mmeId = szacPduInfo[procId][suConnId].mmeId;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#else
         enbId = 0;
         mmeId = 0;
#endif /* SZ_ENC_DEC */

         ie = &eRABSetupRqstPdu->pdu.val.initiatingMsg.value.u.sztE_RABSetupRqst.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &eRABSetupRqstPdu->pdu.val.initiatingMsg.value.u.sztE_RABSetupRqst.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &eRABSetupRqstPdu->pdu.val.initiatingMsg.value.u.sztE_RABSetupRqst.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_E_RABToBeSetupLstBrSUReq);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         numComp = 1;
         szFillTknU16(&(ie->value.u.sztE_RABToBeSetupLstBrSUReq.noComp), numComp);

         if ((cmGetMem(eRABSetupRqstPdu, numComp * sizeof(SztProtIE_SingleCont_E_RABToBeSetupItemBrSUReqIEs), \
                       (Ptr *)&ie->value.u.sztE_RABToBeSetupLstBrSUReq.member)) !=ROK)
         {
#ifndef SZ_ENC_DEC
            CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABSetupRqst_r11: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
            RETVALUE(RFAILED);
         }

         for(idx = 0; idx < numComp; idx++)
         {
            ie1 = &ie->value.u.sztE_RABToBeSetupLstBrSUReq.member[idx];

            szFillTknU8(&(ie1->pres),PRSNT_NODEF);
            szFillTknU32(&(ie1->id), Sztid_E_RABToBeSetupItemBrSUReq);
            szFillTknU32(&(ie1->criticality), SztCriticalityrejectEnum);

            szFillTknU8(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RAB_ID), 15);
            szFillTknU8(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.qCI), 100);
            szFillTknU8(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.allocationRetentionPriority.pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.allocationRetentionPriority.priorityLvl), 10);
            szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.allocationRetentionPriority.pre_emptionCapblty), SztPre_emptionCapbltymay_trigger_pre_emptionEnum);
            szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.allocationRetentionPriority.pre_emptionVulnerability), SztPre_emptionVulnerabilitypre_emptableEnum);
            ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.allocationRetentionPriority.iE_Extns.noComp.pres = NOTPRSNT;

            szFillTknU8(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.gbrQosInform.pres), PRSNT_NODEF);
            cmMemset(bitrate, 0, sizeof(bitrate));
            strcpy((char *)bitrate, "11");
            len = 4;
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.gbrQosInform.e_RAB_MaxBitrateDL), len, bitrate, &eRABSetupRqstPdu);
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.gbrQosInform.e_RAB_MaxBitrateUL), len, bitrate, &eRABSetupRqstPdu);
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.gbrQosInform.e_RAB_GuaranteedBitrateDL), len, bitrate, &eRABSetupRqstPdu);
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.gbrQosInform.e_RAB_GuaranteedBitrateUL), len, bitrate, &eRABSetupRqstPdu);
            ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.gbrQosInform.iE_Extns.noComp.pres = NOTPRSNT;

            ie1->value.u.sztE_RABToBeSetupItemBrSUReq.e_RABlevelQoSParams.iE_Extns.noComp.pres = NOTPRSNT;

            cmMemset(tptAddr,0,sizeof(tptAddr));
            strcpy((char *)tptAddr,"11");
            len = 2;
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.transportLyrAddr), len, tptAddr, &eRABSetupRqstPdu);
            cmMemset(gTPId,0,sizeof(gTPId));
            strcpy((char *)gTPId,"1111");
            len = 4;
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.gTP_TEID), len, gTPId, &eRABSetupRqstPdu);
            cmMemset(nasPdu,0,sizeof(nasPdu));
            strcpy((char *)nasPdu,"111");
            len = 3;
#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"nasPduVal",&(nasPdu));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"nasPduLen",&(len));
#endif /* SZ_ENC_DEC */
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.nAS_PDU),len,nasPdu,&eRABSetupRqstPdu);

#ifndef S1AP_REL11IE
            ie1->value.u.sztE_RABToBeSetupItemBrSUReq.iE_Extns.noComp.pres = NOTPRSNT;
#else
            szFillTknU16(&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.iE_Extns.noComp), 1);

            if (cmGetMem(eRABSetupRqstPdu, (1 * sizeof(SztProtExtnField_E_RABToBeSetupItemBrSUReqExtIEs)), 
                 (Ptr *)&(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.iE_Extns.member)) !=ROK)
            {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"eRABSetupRqstPdu: cmGetMem failed, line %d\n", __LINE__));
#endif
               RETVALUE(RFAILED);
            }
           
            ie2 = &(ie1->value.u.sztE_RABToBeSetupItemBrSUReq.iE_Extns.member[0]);

            szFillTknU8(&(ie2->pres), PRSNT_NODEF);
            szFillTknU32(&(ie2->id), Sztid_Correlation_ID);
            szFillTknU32(&(ie2->criticality), SztCriticalityignoreEnum);

           cmMemset(correlatn_id,0,sizeof(correlatn_id));
           cmMemcpy((U8 *)correlatn_id,(const U8 *)"2541",sizeof(correlatn_id)); 
           len = 4;
           szFillTknStrOSXL(&(ie2->extensionValue.u.sztCorrelation_ID),len,correlatn_id,&eRABSetupRqstPdu);

#endif
         }
      }
   }

   *pdu = eRABSetupRqstPdu;

   RETVALUE(ROK);
}


/*
*
*       Fun:   szAcUtlSztFillHovrRqst_r11 
*
*       Desc:  Call handler to fill Handover Request message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillHovrRqst_r11
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrRqst_r11(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillHovrRqst_r11
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrRqst_r11(pdu)
S1apPdu    **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu   *hovrRqstPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif /* SZ_ENC_DEC */
   U8         choice;
   U32        cause;
   U8         bitrate[8];
   U8         gTPId[10];
   U8         tptAddr[10];
   U8         encAlgo[16]; 
   U8         tprntCont[10];
   U8         secKeyVal[256]; 
   U16        len;
   S16        idx;
   SztProtIE_Field_HovrRqstIEs *ie;
   SztProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs *ie1;
#ifdef S1AP_REL11IE
   U8 pLMNId[10];
   U8 mmeGrpId[10];
   U8 mmeCode[10];
   SztMME_Group_ID *mmeGrpId1;
   SztMME_Code *mmecode1;
   U32 mngmntBsdMDTAlwedalwed = 0;
#endif

   U16 buggy = 0;
   U32 critBug = 0;

   TRC2(szAcUtlSztFillHovrRqst_r11);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&hovrRqstPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrRqst_r11: cmAllocEvnt failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"critBug", &(critBug)); 
#endif /* SZ_ENC_DEC */

   cmMemset((U8 *)&(hovrRqstPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(hovrRqstPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(hovrRqstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(hovrRqstPdu->pdu.val.initiatingMsg.procedureCode), Sztid_HovrResourceAllocn);
   szFillTknU32(&(hovrRqstPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 8;
#ifdef S1AP_REL11IE
      numComp = 10;
#endif
      if(critBug)
      {
         numComp++;
      }

      szFillTknU8(&(hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.pres), PRSNT_NODEF);
      szFillTknU16(&(hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.noComp), numComp);

      if ((cmGetMem(hovrRqstPdu, (numComp * sizeof(SztProtIE_Field_HovrRqstIEs)), 
             (Ptr *)&hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrRqst_r11:: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
         RETVALUE(RFAILED);
      }

      {
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
         procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
         enbId = szacPduInfo[procId][suConnId].enbId;
         mmeId = szacPduInfo[procId][suConnId].mmeId;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"bug", &(buggy)); 
#else
         enbId = 0;
         mmeId = 0;
#endif /* SZ_ENC_DEC */
            /* In order */
            ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[0];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

            ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[1];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_HovrTyp);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztHovrTyp), SztHovrTypgerantolteEnum);

            ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[2];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_Cause);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            choice = CAUSE_RADIONW;
            cause  = SztCauseRadioNwunspecifiedEnum;
#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif /* SZ_ENC_DEC */
            switch (choice)
            {
               case CAUSE_RADIONW:
                  szFillTknU8(&(ie->value.u.sztCause.choice), choice);
                  szFillTknU32(&(ie->value.u.sztCause.val.radioNw), cause);
                  break;
               case CAUSE_TRANSPORT:
                  szFillTknU8(&(ie->value.u.sztCause.choice), choice);
                  szFillTknU32(&(ie->value.u.sztCause.val.radioNw), cause);
                  break;
               case CAUSE_NAS:
                  szFillTknU8(&(ie->value.u.sztCause.choice), choice);
                  szFillTknU32(&(ie->value.u.sztCause.val.radioNw), cause);
                  break;
               case CAUSE_PROTOCOL:
                  szFillTknU8(&(ie->value.u.sztCause.choice), choice);
                  szFillTknU32(&(ie->value.u.sztCause.val.radioNw), cause);
                  break;
               case CAUSE_MISC:
                  szFillTknU8(&(ie->value.u.sztCause.choice), choice);
                  szFillTknU32(&(ie->value.u.sztCause.val.radioNw), cause);
                  break;
               default:
                  szFillTknU8(&(ie->value.u.sztCause.choice), CAUSE_RADIONW);
                  szFillTknU32(&(ie->value.u.sztCause.val.radioNw), SztCauseRadioNwunspecifiedEnum);
                  break;
            }

            ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[3];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_uEaggregateMaxBitrate);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU8(&(ie->value.u.sztUEAggMaxBitrate.pres), PRSNT_NODEF);
            cmMemset(bitrate, 0, sizeof(bitrate));
            strcpy((char *)bitrate, "11");
            len = 4;
            szFillTknStrOSXL(&(ie->value.u.sztUEAggMaxBitrate.uEaggregateMaxBitRateDL), len, bitrate, &hovrRqstPdu);
            szFillTknStrOSXL(&(ie->value.u.sztUEAggMaxBitrate.uEaggregateMaxBitRateUL), len, bitrate, &hovrRqstPdu);
            ie->value.u.sztUEAggMaxBitrate.iE_Extns.noComp.pres = NOTPRSNT;

            ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[4];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_E_RABToBeSetupLstHOReq);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

            numComp = 1;
            szFillTknU16(&(ie->value.u.sztE_RABToBeSetupLstHOReq.noComp), numComp);

            if ((cmGetMem(hovrRqstPdu, (numComp * sizeof(SztProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs)), 
                        (Ptr *)&ie->value.u.sztE_RABToBeSetupLstHOReq.member)) !=ROK)
            {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrRqst_r11:: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
               RETVALUE(RFAILED);
            }

            ie1 = &ie->value.u.sztE_RABToBeSetupLstHOReq.member[0];

            szFillTknU8(&(ie1->pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->id), Sztid_E_RABToBeSetupItemHOReq); 
            szFillTknU32(&(ie1->criticality), SztCriticalityrejectEnum);

            szFillTknU8(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RAB_ID), 15);
            cmMemset(tptAddr, 0, sizeof(tptAddr));
            strcpy((char *)tptAddr, "11");
            len = 2;
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.transportLyrAddr), len, tptAddr, &hovrRqstPdu);
            cmMemset(gTPId, 0, sizeof(gTPId));
            strcpy((char *)gTPId, "1111");
            len = 4;
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.gTP_TEID), len, gTPId, &hovrRqstPdu);

            szFillTknU8(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.qCI), 100);
            szFillTknU8(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.allocationRetentionPriority.pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.allocationRetentionPriority.priorityLvl), 10);
            szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.allocationRetentionPriority.pre_emptionCapblty), SztPre_emptionCapbltymay_trigger_pre_emptionEnum);
            szFillTknU32(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.allocationRetentionPriority.pre_emptionVulnerability), SztPre_emptionVulnerabilitypre_emptableEnum);
            ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.allocationRetentionPriority.iE_Extns.noComp.pres = NOTPRSNT;

            szFillTknU8(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.gbrQosInform.pres), PRSNT_NODEF);
            cmMemset(bitrate, 0, sizeof(bitrate));
            strcpy((char *)bitrate, "11");
            len = 4;
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.gbrQosInform.e_RAB_MaxBitrateDL), len, bitrate, &hovrRqstPdu);
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.gbrQosInform.e_RAB_MaxBitrateUL), len, bitrate, &hovrRqstPdu);
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.gbrQosInform.e_RAB_GuaranteedBitrateDL), len, bitrate, &hovrRqstPdu);
            szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.gbrQosInform.e_RAB_GuaranteedBitrateUL), len, bitrate, &hovrRqstPdu);
            ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.gbrQosInform.iE_Extns.noComp.pres = NOTPRSNT;

            ie1->value.u.sztE_RABToBeSetupItemHOReq.e_RABlevelQosParams.iE_Extns.noComp.pres = NOTPRSNT;
            ie1->value.u.sztE_RABToBeSetupItemHOReq.iE_Extns.noComp.pres = NOTPRSNT;
                  

            ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[5];
            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_Src_ToTget_TprntCont);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

            cmMemset(tprntCont, 0, sizeof(tprntCont));
            strcpy((char *)tprntCont,"111");
            len = 3;
            szFillTknStrOSXL(&(ie->value.u.sztSrc_ToTget_TprntCont), len, tprntCont, &hovrRqstPdu);    
         if(!buggy)
         {
            ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[6];
            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_UESecurCapabilities);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU8(&(ie->value.u.sztUESecurCapabilities.pres), PRSNT_NODEF);
            cmMemset(encAlgo, 0, sizeof(encAlgo));
            for (idx = 0; idx < 16; idx++)
               encAlgo[idx] = 0xFF;
            len = 16;
            szFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.encryptionAlgorithms), len, 100);

            len = 16;
            szFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.integrityProtectionAlgorithms), len, 100);

            ie->value.u.sztUESecurCapabilities.iE_Extns.noComp.pres = NOTPRSNT;

            ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[7];
            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_SecurCntxt);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

            szFillTknU8(&(ie->value.u.sztSecurCntxt.pres), PRSNT_NODEF);


            szFillTknU32(&(ie->value.u.sztSecurCntxt.nextHopChainingCount), 5);

            cmMemset(secKeyVal, 0, sizeof(secKeyVal));
            for (idx = 0; idx < 256; idx++)
               secKeyVal[idx] = 0xFF;
            len = 256;

            szFillTknStrOSXL(&(ie->value.u.sztSecurCntxt.nextHopParameter), len, secKeyVal, &hovrRqstPdu);
            ie->value.u.sztSecurCntxt.iE_Extns.noComp.pres = NOTPRSNT;
          
#ifdef S1AP_REL11IE
            /* IE6 - Filling Gummi */
            ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[8];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_GUMMEI_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            szFillTknU8(&(ie->value.u.sztGUMMEI.pres), PRSNT_NODEF);
      
            cmMemset(pLMNId,0,sizeof(pLMNId));
            cmMemcpy((U8 *)pLMNId,(const U8 *)"111",sizeof(pLMNId));
            len = 3;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"plmnIdVal",&(pLMNId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif
            szFillTknStrOSXL(&(ie->value.u.sztGUMMEI.pLMN_Identity), len, pLMNId, &hovrRqstPdu);

	        mmeGrpId1 = &(ie->value.u.sztGUMMEI.mME_Group_ID);
            cmMemset(mmeGrpId,0,sizeof(mmeGrpId));
            cmMemcpy((U8 *)mmeGrpId,(const U8 *)"11",sizeof(mmeGrpId));
            len = 2;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"mmeGrpVal",&(mmeGrpId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"mmeGrpLen",&(len));
#endif
            szFillTknStr4(mmeGrpId1, (U8)len, 1);

            mmecode1 = &(ie->value.u.sztGUMMEI.mME_Code);
            cmMemset(mmeCode,0,sizeof(mmeCode));
            cmMemcpy((U8 *)mmeCode,(const U8 *)"1",sizeof(mmeCode));
            len = 1;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"mmeCodeVal",&(mmeCode));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"mmeCodeLen",&(len));
#endif
           szFillTknStr4((mmecode1), (U8)len, 1);
           ie->value.u.sztGUMMEI.iE_Extns.noComp.pres = NOTPRSNT;
           /* IE7 - Filling sztManagementBasedMDTAllowed */
           ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[9];
      
           szFillTknU8(&(ie->pres), PRSNT_NODEF);
           szFillTknU32(&(ie->id), Sztid_ManagementBasedMDTAllowed);
           szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"ManagementBasedMDTAllowedallowed", &(mngmntBsdMDTAlwedalwed));
#endif
	        
           szFillTknU32(&(ie->value.u.sztManagementBasedMDTAllowed), mngmntBsdMDTAlwedalwed);

#endif

         }
         else
         {
            ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[7];
            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_UESecurCapabilities);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU8(&(ie->value.u.sztUESecurCapabilities.pres), PRSNT_NODEF);
            cmMemset(encAlgo, 0, sizeof(encAlgo));
            for (idx = 0; idx < 16; idx++)
               encAlgo[idx] = 0xFF;
            len = 16;
            szFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.encryptionAlgorithms), len, 100);

            len = 16;
            szFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.integrityProtectionAlgorithms), len, 100);

            ie->value.u.sztUESecurCapabilities.iE_Extns.noComp.pres = NOTPRSNT;

            ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[6];
            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_SecurCntxt);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

            szFillTknU8(&(ie->value.u.sztSecurCntxt.pres), PRSNT_NODEF);

            szFillTknU32(&(ie->value.u.sztSecurCntxt.nextHopChainingCount),5);

            cmMemset(secKeyVal, 0, sizeof(secKeyVal));
            for (idx = 0; idx < 256; idx++)
               secKeyVal[idx] = 0xFF;
            len = 256;

            szFillTknStrOSXL(&(ie->value.u.sztSecurCntxt.nextHopParameter), len, secKeyVal,&hovrRqstPdu);

            ie->value.u.sztSecurCntxt.iE_Extns.noComp.pres = NOTPRSNT;

         }
      }
   }
   if(critBug)
   {
#ifdef S1AP_REL11IE
      ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[10];
#else
      ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[8];
#endif
      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);
   }

   *pdu = hovrRqstPdu;

   RETVALUE(ROK);
}


/*
*
*       Fun:   szAcUtlSztFillPathSwRqst_r11 
*
*       Desc:  Call handler to fill Path Switch Request message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillPathSwRqst_r11
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillPathSwRqst_r11(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillPathSwRqst_r11
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillPathSwRqst_r11( pdu)
S1apPdu    **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu   *pathSwRqstPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif /* SZ_ENC_DEC */
   U8         gTPId[10];
   U8         tptAddr[10];
   U8         pLMNId[10];
#ifdef S1AP_REL11IE
   U8 mmeGrpId[10];
   U8 mmeCode[10];
   SztMME_Group_ID *mmeGrpId1;
   SztMME_Code *mmecode1;
   U32 cellAccessMode = 0;
#endif

   U16        len;
   SztProtIE_Field_PathSwRqstIEs *ie;
   SztProtIE_SingleCont_E_RABToBeSwedDLItemIEs *ie1;

   U32      buggy = 0;
   U8       critBug = FALSE;

   TRC2(szAcUtlSztFillPathSwRqst_r11);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&pathSwRqstPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPathSwRqst_r11: cmAllocEvnt failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(pathSwRqstPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(pathSwRqstPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(pathSwRqstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(pathSwRqstPdu->pdu.val.initiatingMsg.procedureCode), Sztid_PathSwRqst);
   szFillTknU32(&(pathSwRqstPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "critBug", &(critBug));
#endif

   {
      numComp = 6;
#ifdef S1AP_REL11IE
      numComp = 9;
#endif

      if(critBug)
      {
         numComp++;
      }

      szFillTknU8(&(pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.pres), PRSNT_NODEF);
      szFillTknU16(&(pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.noComp), numComp);

      if ((cmGetMem(pathSwRqstPdu, (numComp * sizeof(SztProtIE_Field_PathSwRqstIEs)), 
                  (Ptr *)&pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPathSwRqst_r11:: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
         RETVALUE(RFAILED);
      }

      {
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
         procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
         enbId = szacPduInfo[procId][suConnId].enbId;
         mmeId = szacPduInfo[procId][suConnId].mmeId;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"bug",&(buggy));
#else
         enbId = 0;
         mmeId = 0;
#endif /* SZ_ENC_DEC */

         ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_E_RABToBeSwedDLLst); 
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         numComp = 1;
         szFillTknU16(&(ie->value.u.sztE_RABToBeSwedDLLst.noComp), numComp);

         if ((cmGetMem(pathSwRqstPdu, (numComp * sizeof(SztProtIE_SingleCont_E_RABToBeSwedDLItemIEs)), 
                     (Ptr *)&ie->value.u.sztE_RABToBeSwedDLLst.member)) !=ROK)
         {
#ifndef SZ_ENC_DEC
            CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPathSwRqst_r11:: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
            RETVALUE(RFAILED);
         }

         ie1 = &ie->value.u.sztE_RABToBeSwedDLLst.member[0];

         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->id), Sztid_E_RABToBeSwedDLItem); 
         szFillTknU32(&(ie1->criticality), SztCriticalityrejectEnum);

         szFillTknU8(&(ie1->value.u.sztE_RABToBeSwedDLItem.pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->value.u.sztE_RABToBeSwedDLItem.e_RAB_ID), 15);
         cmMemset(tptAddr, 0, sizeof(tptAddr));
         strcpy((char *)tptAddr, "11");
         len = 2;
         szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSwedDLItem.transportLyrAddr), len, tptAddr, &pathSwRqstPdu);
         cmMemset(gTPId, 0, sizeof(gTPId));
         strcpy((char *)gTPId, "1111");
         len = 4;
         szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeSwedDLItem.gTP_TEID), len, gTPId, &pathSwRqstPdu);
   

         ie1->value.u.sztE_RABToBeSwedDLItem.iE_Extns.noComp.pres = NOTPRSNT;


         ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_SrcMME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[3];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_EUTRAN_CGI);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU8(&(ie->value.u.sztEUTRAN_CGI.pres), PRSNT_NODEF);
         cmMemset(pLMNId, 0, sizeof(pLMNId));
         strcpy((char *)pLMNId, "111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif /* SZ_ENC_DEC */
         szFillTknStrOSXL(&(ie->value.u.sztEUTRAN_CGI.pLMNidentity), len, pLMNId, &pathSwRqstPdu);     
         len = 28;
         szFillTknBStr32(&(ie->value.u.sztEUTRAN_CGI.cell_ID), len, 100);

         ie->value.u.sztEUTRAN_CGI.iE_Extns.noComp.pres = NOTPRSNT;
         if(!buggy)
         {
            ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[4];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);     
            szFillTknU32(&(ie->id), Sztid_TAI);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            szFillTknU8(&(ie->value.u.sztTAI.pres), PRSNT_NODEF);     
            cmMemset(pLMNId, 0, sizeof(pLMNId));
            strcpy((char *)pLMNId, "111");
            len = 3;
#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif /* SZ_ENC_DEC */
            szFillTknStrOSXL(&(ie->value.u.sztTAI.pLMNidentity), len, pLMNId, &pathSwRqstPdu);     

            len = 2;
#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tacLen", &(len));
#endif /* SZ_ENC_DEC */
            szFillTknStr4(&(ie->value.u.sztTAI.tAC), (U8)len, 1);

            ie->value.u.sztTAI.iE_Extns.noComp.pres = NOTPRSNT;

            ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[5];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_UESecurCapabilities);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            szFillTknU8(&(ie->value.u.sztUESecurCapabilities.pres), PRSNT_NODEF);

            len = 16;
            szFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.encryptionAlgorithms), len, 100);

            len = 16;
            szFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.integrityProtectionAlgorithms), len, 100);
            ie->value.u.sztUESecurCapabilities.iE_Extns.noComp.pres = NOTPRSNT;
#ifdef S1AP_REL11IE
            /* Filling CSG ID */
            ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[6];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_CSG_Id);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

	    len = 27;
            szFillTknBStr32(&(ie->value.u.sztCSG_Id), len, 20);

		    /* Filling Cell access mode */
            ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[7];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_CellAccessMode);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
#ifndef SZ_ENC_DEC
        cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"CellAccessMode", &(cellAccessMode));
#endif
            szFillTknU32(&(ie->value.u.sztCellAccessMode), cellAccessMode);

			/* Filling Gummei */
            ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[8];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_SrcMME_GUMMEI);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            szFillTknU8(&(ie->value.u.sztGUMMEI.pres), PRSNT_NODEF);
     
 
            cmMemset(pLMNId,0,sizeof(pLMNId));
            cmMemcpy((U8 *)pLMNId,(const U8 *)"111",sizeof(pLMNId));
            len = 3;
#ifndef SZ_ENC_DEC
        cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"plmnIdVal",&(pLMNId));
        cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif
            szFillTknStrOSXL(&(ie->value.u.sztGUMMEI.pLMN_Identity), len, pLMNId, &pathSwRqstPdu);

	    mmeGrpId1 = &(ie->value.u.sztGUMMEI.mME_Group_ID);
            cmMemset(mmeGrpId,0,sizeof(mmeGrpId));
            cmMemcpy((U8 *)mmeGrpId,(const U8 *)"11",sizeof(mmeGrpId));
            len = 2;
#ifndef SZ_ENC_DEC
       cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"mmeGrpVal",&(mmeGrpId));
       cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"mmeGrpLen",&(len));
#endif
            szFillTknStr4(mmeGrpId1, (U8)len, 1);

            mmecode1 = &(ie->value.u.sztGUMMEI.mME_Code);
            cmMemset(mmeCode,0,sizeof(mmeCode));
            cmMemcpy((U8 *)mmeCode,(const U8 *)"1",sizeof(mmeCode));
            len = 1;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"mmeCodeVal",&(mmeCode));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"mmeCodeLen",&(len));
#endif
           szFillTknStr4((mmecode1), (U8)len, 1);
	   ie->value.u.sztGUMMEI.iE_Extns.noComp.pres = NOTPRSNT;
#endif
         }
         else
         {
            ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[5];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);     
            szFillTknU32(&(ie->id), Sztid_TAI);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            szFillTknU8(&(ie->value.u.sztTAI.pres), PRSNT_NODEF);     
            cmMemset(pLMNId, 0, sizeof(pLMNId));
            strcpy((char *)pLMNId, "111");
            len = 3;
#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif /* SZ_ENC_DEC */
            szFillTknStrOSXL(&(ie->value.u.sztTAI.pLMNidentity), len, pLMNId, &pathSwRqstPdu);     

            len = 2;
#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tacLen", &(len));
#endif /* SZ_ENC_DEC */
            szFillTknStr4(&(ie->value.u.sztTAI.tAC), (U8)len, 1);

            ie->value.u.sztTAI.iE_Extns.noComp.pres = NOTPRSNT;

            ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[4];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_UESecurCapabilities);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            szFillTknU8(&(ie->value.u.sztUESecurCapabilities.pres), PRSNT_NODEF);

            len = 16;
            szFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.encryptionAlgorithms), len, 100);

            len = 16;
            szFillTknBStr32(&(ie->value.u.sztUESecurCapabilities.integrityProtectionAlgorithms), len, 100);
            ie->value.u.sztUESecurCapabilities.iE_Extns.noComp.pres = NOTPRSNT;
         }

         if(critBug)
         {
#ifdef S1AP_REL11IE
            ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[9];
#else
             ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[6];
#endif
            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);
         }
      }
   }

   *pdu = pathSwRqstPdu;

   RETVALUE(ROK);
}


/*
*
*       Fun:   szAcUtlSztFillTraceStart_r11
*
*       Desc:  Call handler to fill Trace Start message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillTraceStart_r11
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillTraceStart_r11(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillTraceStart_r11
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillTraceStart_r11(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *traceStartPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId = 0;
   U32        mmeId = 0;
   U8         traceRef[10];
   U16        len;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   U8         tptAddr[10];
   SztProtIE_Field_TraceStartIEs *ie;
   U8         critBug = FALSE;
#ifdef S1AP_REL11IE
   SztProtExtnField_TraceActvn_ExtIEs *ie1;
   SztEUTRAN_CGI *ie2;
   U8 pLMNId[10];
   U8 choice= 0;
   U32 threshold_RSRP = 0;
   U32 mdtActvnType = 0;
   U32 rprtngTriggerMDT = 0;
   U32 rprtIntrvlMDT = 0;
   U32 rprtngAmntMDT = 0; 
#endif
   TRC2(szAcUtlSztFillTraceStart_r11);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&traceStartPdu);

   cmMemset((U8 *)&(traceStartPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(traceStartPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(traceStartPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(traceStartPdu->pdu.val.initiatingMsg.procedureCode), Sztid_TraceStart);
   szFillTknU32(&(traceStartPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);


   {
      numComp = 3;

#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"critBug",&(critBug));
#endif
      if(critBug)
      {
         numComp++;
      }

      szFillTknU8(&(traceStartPdu->pdu.val.initiatingMsg.value.u.sztTraceStart.pres), PRSNT_NODEF);
      szFillTknU16(&(traceStartPdu->pdu.val.initiatingMsg.value.u.sztTraceStart.protocolIEs.noComp), numComp);

      if ((cmGetMem(traceStartPdu, (numComp * sizeof(SztProtIE_Field_TraceStartIEs)), 
             (Ptr *)&traceStartPdu->pdu.val.initiatingMsg.value.u.sztTraceStart.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillTraceStart_r11Pdu: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
         enbId = szacPduInfo[procId][suConnId].enbId;
         mmeId = szacPduInfo[procId][suConnId].mmeId;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#endif   /* SZ_ENC_DEC */

         ie = &traceStartPdu->pdu.val.initiatingMsg.value.u.sztTraceStart.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &traceStartPdu->pdu.val.initiatingMsg.value.u.sztTraceStart.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &traceStartPdu->pdu.val.initiatingMsg.value.u.sztTraceStart.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_TraceActvn);
         szFillTknU32(&(ie->criticality), SztCriticalitynotifyEnum);

         szFillTknU8(&(ie->value.u.sztTraceActvn.pres), PRSNT_NODEF);
         cmMemset(traceRef,0,sizeof(traceRef));
         strcpy((char *)traceRef,"11112222");
         len = 8;
         szFillTknStrOSXL(&(ie->value.u.sztTraceActvn.e_UTRAN_Trace_ID), len, traceRef, &traceStartPdu);
  
           len = 8;
          szFillTknBStr32(&(ie->value.u.sztTraceActvn.interfacesToTrace),len,100);
  
         szFillTknU32(&(ie->value.u.sztTraceActvn.traceDepth),SztTraceDepthminimumEnum);
          
         cmMemset(tptAddr,0,sizeof(tptAddr));
         strcpy((char *)tptAddr,"11");
         len = 2;
         szFillTknStrOSXL(&(ie->value.u.sztTraceActvn.traceCollectionEntityIPAddr), len, tptAddr, &traceStartPdu);
         
#ifndef S1AP_REL11IE
         ie->value.u.sztTraceActvn.iE_Extns.noComp.pres = NOTPRSNT;
#else
         szFillTknU16(&(ie->value.u.sztTraceActvn.iE_Extns.noComp),1);

		 if (cmGetMem(traceStartPdu, (1 * sizeof(SztProtExtnField_TraceActvn_ExtIEs)), 
			   (Ptr *)&(ie->value.u.sztTraceActvn.iE_Extns.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"traceStartPdu: cmGetMem failed, line %d\n", __LINE__));
#endif
               RETVALUE(RFAILED);
       }
          
	  ie1 = &(ie->value.u.sztTraceActvn.iE_Extns.member[0]);
         
          szFillTknU8(&(ie1->pres), PRSNT_NODEF);
          szFillTknU32(&(ie1->id), Sztid_MDTConfig);
          szFillTknU32(&(ie1->criticality), SztCriticalityignoreEnum);
	  szFillTknU8(&(ie1->extensionValue.u.sztMDT_Config.pres), PRSNT_NODEF);
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"MDTActvnType", &(mdtActvnType));
#endif
	  szFillTknU32(&(ie1->extensionValue.u.sztMDT_Config.mdt_Actvn), mdtActvnType);
	  choice = AREASCOPEOFMDT_CELLBASED;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"choice", &(choice));
#endif	   
	   szFillTknU8(&(ie1->extensionValue.u.sztMDT_Config.areaScopeOfMDT.choice), choice);

	   szFillTknU8(&(ie1->extensionValue.u.sztMDT_Config.areaScopeOfMDT.val.cellBased.pres),PRSNT_NODEF);
	   szFillTknU16(&(ie1->extensionValue.u.sztMDT_Config.areaScopeOfMDT.val.cellBased.cellIdLstforMDT.noComp),1);

        if (cmGetMem(traceStartPdu, (1 * sizeof(SztEUTRAN_CGI)), 
		   (Ptr *)&(ie1->extensionValue.u.sztMDT_Config.areaScopeOfMDT.val.cellBased.cellIdLstforMDT.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"traceStartPdu: cmGetMem failed, line %d\n", __LINE__));
#endif
               RETVALUE(RFAILED);
       }
          
       ie2 = &(ie1->extensionValue.u.sztMDT_Config.areaScopeOfMDT.val.cellBased.cellIdLstforMDT.member[0]);
          
	   szFillTknU8(&(ie2->pres), PRSNT_NODEF);
       cmMemset(pLMNId, 0, sizeof(pLMNId));
       cmMemcpy((U8 *)pLMNId,(const U8 *)"111",sizeof(pLMNId)); 
       len = 3;
#ifndef SZ_ENC_DEC
       cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
       cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif
       szFillTknStrOSXL(&(ie2->pLMNidentity), len, pLMNId, &traceStartPdu);     

       len = 28;
       szFillTknBStr32(&(ie2->cell_ID), len, 100);

       ie2->iE_Extns.noComp.pres = NOTPRSNT;
       ie1->extensionValue.u.sztMDT_Config.areaScopeOfMDT.val.cellBased.iE_Extns.noComp.pres = NOTPRSNT;
       choice = MDTMODE_IMMEDIATEMDT;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"choice1", &(choice));
#endif	   

       szFillTknU8(&(ie1->extensionValue.u.sztMDT_Config.mDTMode.choice), choice);
       szFillTknU8(&(ie1->extensionValue.u.sztMDT_Config.mDTMode.val.immediateMDT.pres), PRSNT_NODEF);
       len = 8;
       szFillTknBStr32(&(ie1->extensionValue.u.sztMDT_Config.mDTMode.val.immediateMDT.measurementsToActivate), len, 100);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"RprtngTriggerMDT", &(rprtngTriggerMDT));
#endif
       szFillTknU32(&(ie1->extensionValue.u.sztMDT_Config.mDTMode.val.immediateMDT.reportingTriggerMDT), 
	   	             rprtngTriggerMDT);
       szFillTknU8(&(ie1->extensionValue.u.sztMDT_Config.mDTMode.val.immediateMDT.thresholdeventA2.pres),PRSNT_NODEF);
       choice = MEASUREMENTTHRESHOLDA2_THRESHOLD_RSRP;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"choice2", &(choice));
#endif	
       szFillTknU8(&(ie1->extensionValue.u.sztMDT_Config.mDTMode.val.immediateMDT.thresholdeventA2.measurementThreshold.choice),
	   	            choice);
       threshold_RSRP = 97;
#ifndef SZ_ENC_DEC
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"thresholRSRP", &(threshold_RSRP));
#endif
       szFillTknU32(&(ie1->extensionValue.u.sztMDT_Config.mDTMode.val.immediateMDT.thresholdeventA2.measurementThreshold.val.threshold_RSRP), 
                       threshold_RSRP);
       ie1->extensionValue.u.sztMDT_Config.mDTMode.val.immediateMDT.thresholdeventA2.iE_Extns.noComp.pres = NOTPRSNT;

       szFillTknU8(&(ie1->extensionValue.u.sztMDT_Config.mDTMode.val.immediateMDT.periodicRprtngMDT.pres),PRSNT_NODEF);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"RprtIntrvlMDT", &(rprtIntrvlMDT));
#endif

       szFillTknU32(&(ie1->extensionValue.u.sztMDT_Config.mDTMode.val.immediateMDT.periodicRprtngMDT.reportInterval),
	   	              rprtIntrvlMDT);
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"RprtngAmountMDT", &(rprtngAmntMDT));
#endif
       szFillTknU32(&(ie1->extensionValue.u.sztMDT_Config.mDTMode.val.immediateMDT.periodicRprtngMDT.reportAmount), 
	   	              rprtngAmntMDT);
       ie1->extensionValue.u.sztMDT_Config.mDTMode.val.immediateMDT.periodicRprtngMDT.iE_Extns.noComp.pres = NOTPRSNT;

       ie1->extensionValue.u.sztMDT_Config.mDTMode.val.immediateMDT.iE_Extns.noComp.pres = NOTPRSNT;
       ie1->extensionValue.u.sztMDT_Config.iE_Extns.noComp.pres = NOTPRSNT;
#endif
      /* Introduce a invalide IE id for criticality testing */
         if(critBug)
         {
            ie = &traceStartPdu->pdu.val.initiatingMsg.value.u.sztTraceStart.protocolIEs.member[3];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);
         }
 
       }
   }

   *pdu = traceStartPdu;

   RETVALUE(ROK);
}


/*
*
*       Fun:   szAcUtlSztFillOverloadStart_r11
*
*       Desc:  Call handler to fill Overload Start message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillOverloadStart_r11
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillOverloadStart_r11(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillOverloadStart_r11
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillOverloadStart_r11(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *overloadStartPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   SztProtIE_Field_OverloadStartIEs *ie;

#ifdef S1AP_REL11IE
   SztGUMMEI *ie1;
   
   U8 pLMNId[10];
   U8 mmeGrpId[10];
   U8 mmeCode[10];
   U8 len;
   U32 trafficLoadReductionInd =0;
#endif

   TRC2(szAcUtlSztFillOverloadStart_r11);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&overloadStartPdu);

   cmMemset((U8 *)&(overloadStartPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(overloadStartPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(overloadStartPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(overloadStartPdu->pdu.val.initiatingMsg.procedureCode), Sztid_OverloadStart);
   szFillTknU32(&(overloadStartPdu->pdu.val.initiatingMsg.criticality), SztCriticalityignoreEnum);

   {
      numComp = 1;
#ifdef S1AP_REL11IE
      numComp = 3;
#endif
      szFillTknU8(&(overloadStartPdu->pdu.val.initiatingMsg.value.u.sztOverloadStart.pres), PRSNT_NODEF);
      szFillTknU16(&(overloadStartPdu->pdu.val.initiatingMsg.value.u.sztOverloadStart.protocolIEs.noComp), numComp);

      if ((cmGetMem(overloadStartPdu, (numComp * sizeof(SztProtIE_Field_OverloadStartIEs)), 
             (Ptr *)&overloadStartPdu->pdu.val.initiatingMsg.value.u.sztOverloadStart.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillOverloadStart_r11: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      ie = &overloadStartPdu->pdu.val.initiatingMsg.value.u.sztOverloadStart.protocolIEs.member[0];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_OverloadResp);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU8(&(ie->value.u.sztOverloadResp.choice), OVERLOADRESP_OVERLOADACTION);
      szFillTknU32(&(ie->value.u.sztOverloadResp.val.overloadAction), SztOverloadActionreject_non_emergency_mo_dtEnum);
#ifdef S1AP_REL11IE
      ie = &overloadStartPdu->pdu.val.initiatingMsg.value.u.sztOverloadStart.protocolIEs.member[1];
      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_GUMMEILst);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU16(&(ie->value.u.sztGUMMEILst.noComp), 1);
      if ((cmGetMem(overloadStartPdu, (1 * sizeof(SztGUMMEI)), 
             (Ptr *)&(ie->value.u.sztGUMMEILst.member)) !=ROK))
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillOverloadStart_r11: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      ie1 = &(ie->value.u.sztGUMMEILst.member[0]);
      szFillTknU8(&(ie1->pres), PRSNT_NODEF);
      
      cmMemset(pLMNId,0,sizeof(pLMNId));
      cmMemcpy((U8 *)pLMNId,(const U8 *)"111",sizeof(pLMNId));
      len = 3;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"plmnIdVal",&(pLMNId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif
      szFillTknStrOSXL(&(ie1->pLMN_Identity), len, pLMNId, &overloadStartPdu);

      
	  cmMemset(mmeGrpId,0,sizeof(mmeGrpId));
      cmMemcpy((U8 *)mmeGrpId,(const U8 *)"11",sizeof(mmeGrpId));
      len = 2;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"mmeGrpVal",&(mmeGrpId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"mmeGrpLen",&(len));
#endif
      szFillTknStr4(&(ie1->mME_Group_ID), (U8)len, 1);

      
      cmMemset(mmeCode,0,sizeof(mmeCode));
      cmMemcpy((U8 *)mmeCode,(const U8 *)"1",sizeof(mmeCode));
      len = 1;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"mmeCodeVal",&(mmeCode));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"mmeCodeLen",&(len));
#endif
      szFillTknStr4(&(ie1->mME_Code), (U8)len, 1);
      ie1->iE_Extns.noComp.pres = 0;

      /*sztTrafficLoadReductionInd IE */
      ie = &(overloadStartPdu->pdu.val.initiatingMsg.value.u.sztOverloadStart.protocolIEs.member[2]);
      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_TrafficLoadReductionInd);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
	  trafficLoadReductionInd = 1;
#ifndef SZ_ENC_DEC	  
cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"trafficLoadReductionInd", &(trafficLoadReductionInd));	  
#endif
      szFillTknU32(&(ie->value.u.sztTrafficLoadReductionInd), trafficLoadReductionInd);  	  

#endif
	  
   }

   *pdu = overloadStartPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillOverloadStop_r11
*
*       Desc:  Call handler to fill Overload Stop message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillOverloadStop_r11
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillOverloadStop_r11(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillOverloadStop_r11
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillOverloadStop_r11(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *overloadStopPdu = NULLP;
   S16        ret;
   Mem        mem; 
#ifdef S1AP_REL11IE
   SztProtIE_Field_OverloadStopIEs *ie;
   SztGUMMEI *ie1;
   
   U8 pLMNId[10];
   U8 mmeGrpId[10];
   U8 mmeCode[10];
   U8 len;
   
#endif
   TRC2(szAcUtlSztFillOverloadStop_r11);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&overloadStopPdu);

   cmMemset((U8 *)&(overloadStopPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(overloadStopPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(overloadStopPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(overloadStopPdu->pdu.val.initiatingMsg.procedureCode), Sztid_OverloadStop);
   szFillTknU32(&(overloadStopPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   szFillTknU8(&(overloadStopPdu->pdu.val.initiatingMsg.value.u.sztOverloadStop.pres), PRSNT_NODEF);
#ifndef S1AP_REL11IE
   szFillTknU16(&(overloadStopPdu->pdu.val.initiatingMsg.value.u.sztOverloadStop.protocolIEs.noComp), 0);

#else
   szFillTknU16(&(overloadStopPdu->pdu.val.initiatingMsg.value.u.sztOverloadStop.protocolIEs.noComp), 1);


  if ((cmGetMem(overloadStopPdu, (1 * sizeof(SztProtIE_Field_OverloadStopIEs)), 
       (Ptr *)&overloadStopPdu->pdu.val.initiatingMsg.value.u.sztOverloadStop.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"overloadStopPdu:: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
         RETVALUE(RFAILED);
      }
   
   ie = &overloadStopPdu->pdu.val.initiatingMsg.value.u.sztOverloadStop.protocolIEs.member[0];

   szFillTknU8(&(ie->pres), PRSNT_DEF);
   szFillTknU32(&(ie->id), Sztid_GUMMEILst); 
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   
   szFillTknU16(&(ie->value.u.sztGUMMEILst.noComp), 1);
   
   if ((cmGetMem(overloadStopPdu, (1 * sizeof(SztGUMMEI)), 
               (Ptr *)&ie->value.u.sztGUMMEILst.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"overloadStopPdu: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }   

   ie1 = &ie->value.u.sztGUMMEILst.member[0];
   szFillTknU8(&(ie1->pres), PRSNT_NODEF);

      
      cmMemset(pLMNId,0,sizeof(pLMNId));
      cmMemcpy((U8 *)pLMNId,(const U8 *)"111",sizeof(pLMNId));
      len = 3;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"plmnIdVal",&(pLMNId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif
      szFillTknStrOSXL(&(ie1->pLMN_Identity), len, pLMNId, &overloadStopPdu);


       cmMemset(mmeGrpId,0,sizeof(mmeGrpId));
      cmMemcpy((U8 *)mmeGrpId,(const U8 *)"11",sizeof(mmeGrpId)); 
      len = 2;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"mmeGrpVal",&(mmeGrpId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"mmeGrpLen",&(len));
#endif
      szFillTknStr4(&(ie1->mME_Group_ID), (U8)len, 1);


      cmMemset(mmeCode,0,sizeof(mmeCode));
      cmMemcpy((U8 *)mmeCode,(const U8 *)"1",sizeof(mmeCode));
      len = 1;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"mmeCodeVal",&(mmeCode));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"mmeCodeLen",&(len));
#endif
      szFillTknStr4(&(ie1->mME_Code), (U8)len, 1);
      ie1->iE_Extns.noComp.pres = 0;

#endif
   
   *pdu = overloadStopPdu;

   RETVALUE(ROK);
}


/*
*
*       Fun:   szAcUtlSztFillENBConfigTfr_r11
*
*       Desc:  Call handler to fill ENB Configuration Transfer message
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillENBConfigTfr_r11
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBConfigTfr_r11(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillENBConfigTfr_r11
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBConfigTfr_r11(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *eNBConfigTfrPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem;
   U8         pLMNId[10];
   U16        len;
   SztProtIE_Field_ENBConfigTfrIEs *ie;
   SztTgeteNB_ID *ie1;
   SztSrceNB_ID *ie2;
   SztSONInform *ie3;     
#ifdef S1AP_REL11IE
   SztProtExtnField_SONConfigTfr_ExtIEs *ie4;
   SztProtExtnField_X2TNLConfigInfo_ExtIEs *ie5;
   SztENBX2ExtTLA *ie6;
   U8 tptAddr[10];
#endif
                                                                                                              
   TRC2(szAcUtlSztFillENBConfigTfr_r11);
 
     mem.region = 0;
     mem.pool   = 0;
                                                                                                                  
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eNBConfigTfrPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBConfigTfr_r11: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }
                                                                                                                  
   cmMemset((U8 *)&(eNBConfigTfrPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));
                                                                                                                  
   szFillTknU8(&(eNBConfigTfrPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(eNBConfigTfrPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(eNBConfigTfrPdu->pdu.val.initiatingMsg.procedureCode), Sztid_eNBConfigTfr);
   szFillTknU32(&(eNBConfigTfrPdu->pdu.val.initiatingMsg.criticality), SztCriticalityignoreEnum);

   {
      numComp = 1;
      szFillTknU8(&(eNBConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztENBConfigTfr.pres), PRSNT_NODEF);
      szFillTknU16(&(eNBConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztENBConfigTfr.protocolIEs.noComp), numComp);

      if ((cmGetMem(eNBConfigTfrPdu, (numComp * sizeof( SztProtIE_Field_ENBConfigTfrIEs )),
                  (Ptr *)&eNBConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztENBConfigTfr.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBConfigTfr_r11:: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {
         ie = &eNBConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztENBConfigTfr.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_SONConfigTfrECT);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU8(&(ie->value.u.sztSONConfigTfr.pres), PRSNT_NODEF);

         ie1 = &(ie->value.u.sztSONConfigTfr.targeteNB_ID); 
       
         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU8(&(ie1->global_ENB_ID.pres), PRSNT_NODEF);
         cmMemset(pLMNId, 0, sizeof(pLMNId));
         strcpy((char *)pLMNId, "111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif
         szFillTknStrOSXL(&(ie1->global_ENB_ID.pLMNidentity), len, pLMNId, & eNBConfigTfrPdu);
         szFillTknU8(&(ie1->global_ENB_ID.eNB_ID.choice), ENB_ID_HOMEENB_ID);

         len = 28;
         szFillTknBStr32(&(ie1->global_ENB_ID.eNB_ID.val.homeENB_ID), len, 100);
         ie1->global_ENB_ID.iE_Extns.noComp.pres = NOTPRSNT;

         szFillTknU8(&(ie1->selected_TAI.pres), PRSNT_NODEF);
         cmMemset(pLMNId, 0, sizeof(pLMNId));
         strcpy((char *)pLMNId,"111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"plmnIdVal",&(pLMNId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif
         szFillTknStrOSXL(&(ie1->selected_TAI.pLMNidentity), len, pLMNId, & eNBConfigTfrPdu);

         len = 2;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"tacLen", &(len));
#endif
         szFillTknStr4(&(ie1->selected_TAI.tAC), (U8)len, 1);
         ie1->selected_TAI.iE_Extns.noComp.pres = NOTPRSNT;

         ie2 = &(ie->value.u.sztSONConfigTfr.sourceeNB_ID);
         
         szFillTknU8(&(ie2->pres), PRSNT_NODEF);
         szFillTknU8(&(ie2->global_ENB_ID.pres), PRSNT_NODEF);
         cmMemset(pLMNId, 0, sizeof(pLMNId));
         strcpy((char *)pLMNId, "111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif
         szFillTknStrOSXL(&(ie2->global_ENB_ID.pLMNidentity), len, pLMNId, &eNBConfigTfrPdu);
         szFillTknU8(&(ie2->global_ENB_ID.eNB_ID.choice), ENB_ID_HOMEENB_ID);

         len = 28;
         szFillTknBStr32(&(ie2->global_ENB_ID.eNB_ID.val.homeENB_ID), len, 100);
         ie2->global_ENB_ID.iE_Extns.noComp.pres = NOTPRSNT;

         szFillTknU8(&(ie2->selected_TAI.pres), PRSNT_NODEF);
         cmMemset(pLMNId, 0, sizeof(pLMNId));
         strcpy((char *)pLMNId,"111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"plmnIdVal",&(pLMNId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif
         szFillTknStrOSXL(&(ie2->selected_TAI.pLMNidentity), len, pLMNId, &eNBConfigTfrPdu);

         len = 2;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"tacLen", &(len));
#endif
         szFillTknStr4(&(ie2->selected_TAI.tAC), (U8)len, 1);
         ie2->selected_TAI.iE_Extns.noComp.pres = NOTPRSNT;

         ie3 = &(ie->value.u.sztSONConfigTfr.sONInform);
         szFillTknU8(&(ie3->choice), SONINFORM_SONINFORMRQST);
         szFillTknU32(&(ie3->val.sONInformRqst), SztSONInformRqstx2TNL_Config_InfoEnum);
      
#ifndef S1AP_REL11IE
         ie->value.u.sztSONConfigTfr.iE_Extns.noComp.pres = NOTPRSNT; 
#else
         szFillTknU16(&(ie->value.u.sztSONConfigTfr.iE_Extns.noComp),1);

	 if (cmGetMem(eNBConfigTfrPdu, (1 * sizeof(SztProtExtnField_SONConfigTfr_ExtIEs)), 
			   (Ptr *)&(ie->value.u.sztSONConfigTfr.iE_Extns.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"eNBConfigTfrPdu: cmGetMem failed, line %d\n", __LINE__));
#endif
               RETVALUE(RFAILED);
       }
          
       ie4 = &(ie->value.u.sztSONConfigTfr.iE_Extns.member[0]);
         
       szFillTknU8(&(ie4->pres), PRSNT_NODEF);
       szFillTknU32(&(ie4->id), Sztid_x2TNLConfigInfo);
       szFillTknU32(&(ie4->criticality), SztCriticalityignoreEnum);

       szFillTknU8(&(ie4->extensionValue.u.sztX2TNLConfigInfo.pres), PRSNT_NODEF);
	   
       szFillTknU16(&(ie4->extensionValue.u.sztX2TNLConfigInfo.eNBX2TportLyrAddres.noComp), 1);

      if (cmGetMem(eNBConfigTfrPdu, (1 * sizeof(SztTportLyrAddr)), 
	   (Ptr *)&(ie4->extensionValue.u.sztX2TNLConfigInfo.eNBX2TportLyrAddres.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"eNBConfigTfrPdu: cmGetMem failed, line %d\n", __LINE__));
#endif
               RETVALUE(RFAILED);
       }

       cmMemset(tptAddr, 0, sizeof(tptAddr));
       cmMemcpy((U8 *)tptAddr,(const U8 *)"1111",sizeof(tptAddr));
       len = 4;
       szFillTknStrOSXL(&(ie4->extensionValue.u.sztX2TNLConfigInfo.eNBX2TportLyrAddres.member[0]), len, tptAddr, &eNBConfigTfrPdu);
	

       szFillTknU16(&(ie4->extensionValue.u.sztX2TNLConfigInfo.iE_Extns.noComp), 1);

       if (cmGetMem(eNBConfigTfrPdu, (1 * sizeof(SztProtExtnField_X2TNLConfigInfo_ExtIEs)), 
			   (Ptr *)&(ie4->extensionValue.u.sztX2TNLConfigInfo.iE_Extns.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"eNBConfigTfrPdu: cmGetMem failed, line %d\n", __LINE__));
#endif
               RETVALUE(RFAILED);
       }

       ie5 = &(ie4->extensionValue.u.sztX2TNLConfigInfo.iE_Extns.member[0]);
       szFillTknU8(&(ie5->pres), PRSNT_NODEF);
       szFillTknU32(&(ie5->id), Sztid_eNBX2ExtendedTportLyrAddres);
       szFillTknU32(&(ie5->criticality), SztCriticalityignoreEnum);
       szFillTknU16(&(ie5->extensionValue.u.sztENBX2ExtTLAs.noComp), 1);

	if (cmGetMem(eNBConfigTfrPdu, (1 * sizeof(SztENBX2ExtTLA)), 
			   (Ptr *)&(ie5->extensionValue.u.sztENBX2ExtTLAs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"eNBConfigTfrPdu: cmGetMem failed, line %d\n", __LINE__));
#endif
               RETVALUE(RFAILED);
       }

       ie6 = &(ie5->extensionValue.u.sztENBX2ExtTLAs.member[0]);
       szFillTknU8(&(ie6->pres), PRSNT_NODEF);

       cmMemset(tptAddr, 0, sizeof(tptAddr));
       cmMemcpy((U8 *)tptAddr,(const U8 *)"1122",sizeof(tptAddr));

       len = 4;
       szFillTknStrOSXL(&(ie6->iPsecTLA), len, tptAddr, &eNBConfigTfrPdu);
       szFillTknU16(&(ie6->gTPTLAa.noComp), 1);

       if (cmGetMem(eNBConfigTfrPdu, (1 * sizeof(SztENBX2GTPTLAs)), 
			   (Ptr *)&(ie6->gTPTLAa.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"eNBConfigTfrPdu: cmGetMem failed, line %d\n", __LINE__));
#endif
               RETVALUE(RFAILED);
       }

	   cmMemset(tptAddr, 0, sizeof(tptAddr));
       cmMemcpy((U8 *)tptAddr,(const U8 *)"1231",sizeof(tptAddr));
       len = 4;
       szFillTknStrOSXL(&(ie6->gTPTLAa.member[0]), len, tptAddr, &eNBConfigTfrPdu);	
       ie6->iE_Extns.noComp.pres = NOTPRSNT;

#endif

      }
   }

   *pdu = eNBConfigTfrPdu;

   RETVALUE(ROK);
}


/*
*
*       Fun:   szAcUtlSztFillCellTrafficTrc
*
*       Desc:  Call handler to fill Cell Traffic Trace
*
*       Ret:   ROK
*
*       Notes: None
*
*       File:  szac_sztutl.c
*
*/
#ifndef SZ_ENC_DEC
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillCellTrafficTrace_r11
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillCellTrafficTrace_r11(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillCellTrafficTrace_r11
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillCellTrafficTrace_r11(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *celltrficTracePdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem;
   U32        enbId;
   U32        mmeId;
   U8         traceRef[10];
   U16        len;
   U8         critBug = FALSE;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   U8   tptAddr[10];
   U8      pLMNId[10];
   U8      cellId[28];
   U8 idx = 0;
   SztProtIE_Field_CellTrafficTraceIEs *ie;
                                                                                                              
   TRC2(szAcUtlSztFillCellTrafficTrace_r11);
                                                                                                              
   mem.region = 0;
   mem.pool   = 0;
#ifdef S1AP_REL11IE
   U32 privacyIndctr = 0;
#endif
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&celltrficTracePdu);
                                                                                                              
   cmMemset((U8 *)&(celltrficTracePdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));
                                                                                                              
   szFillTknU8(&(celltrficTracePdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(celltrficTracePdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(celltrficTracePdu->pdu.val.initiatingMsg.procedureCode),  Sztid_CellTrafficTrace);
   szFillTknU32(&(celltrficTracePdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 5;
#ifdef S1AP_REL11IE
      numComp = 6;
#endif
      
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"critBug",&(critBug));
#endif /* SZ_ENC_DEC */

      if( critBug )
      {
         numComp++;
      }
 
      szFillTknU8(&(celltrficTracePdu->pdu.val.initiatingMsg.value.u.sztCellTrafficTrace.pres), PRSNT_NODEF);
      szFillTknU16(&(celltrficTracePdu->pdu.val.initiatingMsg.value.u.sztCellTrafficTrace.protocolIEs.noComp), numComp);
                                                                                                              
      if ((cmGetMem(celltrficTracePdu, (numComp * sizeof(SztProtIE_Field_CellTrafficTraceIEs)),
             (Ptr *)&celltrficTracePdu->pdu.val.initiatingMsg.value.u.sztCellTrafficTrace.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillCellTrafficTrace_r11: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

 {
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
         enbId = szacPduInfo[procId][suConnId].enbId;
         mmeId = szacPduInfo[procId][suConnId].mmeId;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#else
         enbId = 0;
         mmeId = 0;
#endif

         numComp = 0;
         
        if( critBug )
        {
           ie = &celltrficTracePdu->pdu.val.initiatingMsg.value.u.sztCellTrafficTrace.protocolIEs.member[numComp++];
                                                                                                              
           szFillTknU8(&(ie->pres), PRSNT_NODEF);  
           szFillTknU32(&(ie->id), Sztid_Crit_Tst3);
           szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

           cmMemset(tptAddr, 0, sizeof(tptAddr));
           strcpy((char *)tptAddr, "11");
           len = 2;
           szFillTknStrOSXL(&(ie->value.u.sztTportLyrAddr), len, tptAddr, &celltrficTracePdu); 
        }
           
         ie = &celltrficTracePdu->pdu.val.initiatingMsg.value.u.sztCellTrafficTrace.protocolIEs.member[numComp++];
                                                                                                              
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &celltrficTracePdu->pdu.val.initiatingMsg.value.u.sztCellTrafficTrace.protocolIEs.member[numComp++];
                                                                                                              
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &celltrficTracePdu->pdu.val.initiatingMsg.value.u.sztCellTrafficTrace.protocolIEs.member[numComp++];
                                                                                                              
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id),  Sztid_E_UTRAN_Trace_ID);
         szFillTknU32(&(ie->criticality), SztCriticalitynotifyEnum);
                                                                                                              
         cmMemset(traceRef, 0, sizeof(traceRef));
         strcpy((char *)traceRef, "11112222");
         len = 8;
         szFillTknStrOSXL(&(ie->value.u.sztE_UTRAN_Trace_ID), len, traceRef, &celltrficTracePdu);

         ie = &celltrficTracePdu->pdu.val.initiatingMsg.value.u.sztCellTrafficTrace.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_EUTRAN_CGI);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU8(&(ie->value.u.sztEUTRAN_CGI.pres), PRSNT_NODEF);
         cmMemset(pLMNId, 0, sizeof(pLMNId));
         strcpy((char *)pLMNId, "111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif
         szFillTknStrOSXL(&(ie->value.u.sztEUTRAN_CGI.pLMNidentity), len, pLMNId, &celltrficTracePdu);
         cmMemset(cellId ,0, sizeof(cellId));
         for (idx = 0; idx < 28; idx++)
         cellId[idx] = 0xFF;
         len = 28;
         szFillTknBStr32(&(ie->value.u.sztEUTRAN_CGI.cell_ID), len, 100);
                                                                                                              
        ie->value.u.sztEUTRAN_CGI.iE_Extns.noComp.pres = NOTPRSNT;

        ie = &celltrficTracePdu->pdu.val.initiatingMsg.value.u.sztCellTrafficTrace.protocolIEs.member[numComp++];
                                                                                                              
        szFillTknU8(&(ie->pres), PRSNT_NODEF);
        szFillTknU32(&(ie->id), Sztid_TraceCollectionEntityIPAddr);
        szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

        cmMemset(tptAddr, 0, sizeof(tptAddr));
        strcpy((char *)tptAddr, "11");
        len = 2;
        szFillTknStrOSXL(&(ie->value.u.sztTportLyrAddr), len, tptAddr, &celltrficTracePdu);

#ifdef S1AP_REL11IE
        ie = &celltrficTracePdu->pdu.val.initiatingMsg.value.u.sztCellTrafficTrace.protocolIEs.member[numComp++];
                                                                                                              
        szFillTknU8(&(ie->pres), PRSNT_NODEF);
        szFillTknU32(&(ie->id), Sztid_PrivacyIndicator);
        szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"PrivacyIndctr", &(privacyIndctr));
#endif       
	szFillTknU32(&(ie->value.u.sztPrivacyIndicator), privacyIndctr);

#endif

       }
   }
                                                                                                              
   *pdu = celltrficTracePdu;
                                                                                                              
   RETVALUE(ROK);
}


#ifdef __cplusplus
}
#endif

/********************************************************************30**

         End of file:     szac_sztutl_r11.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:13:31 2015

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
/main/4      ---      vvashishth  1. Updated for S1AP release 3.1
/main/4   sz003.301   pka   1. Updated for PSF-S1AP 1.1 release
/main/1   sz004.301   va    1. Updated for Transparent Container 
                                 Enc/Dec
/main/4   sz008.301 akaranth 1.support for Source RNC to Target RNC.
*********************************************************************91*/
