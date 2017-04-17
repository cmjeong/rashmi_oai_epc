
/********************************************************************20**

     Name:    S1AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    szac_lszhdl.c

     Sid:      szac_sztutl_r9.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:13:33 2015

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
#include "szt_asn.h"            /* defines and macros for SZ */
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
using namespace SZ_S1AP_REL9;
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

#ifndef SZ_ENC_DEC
/*
*
*       Fun:   szAcUtlSztGetNewConnId 
*
*       Desc:  Utility Function to get Connection Id
*
*       Ret:   ROK
*
*       Notes: When sending a new request out, you can use this function
*              to store Connection Id of request and a given index in 
*              the global storage array. This can be used later to
*              retrieve the Connection Id based on the index given and match
*              it with the response received.  
*
*       File:  szac_sztutl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcUtlSztGetNewConnId
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
UConnId        *suConnId
)
#else
PUBLIC S16 szAcUtlSztGetNewConnId(tcCb, spCb, suConnId)
CmXtaTCCb      *tcCb;    /* tcCb data structure  */
CmXtaSpCb      *spCb;
UConnId        *suConnId;
#endif
{
  U8 idx = 0;
  Bool reuse = FALSE;

  TRC2(szAcUtlSztGetNewConnId);

  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"connIdx", &(idx));

  if(idx > SZAC_MAX_CONN_IDX)
  {
     CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztGetNewConnId():index size above SZAC_MAX_CONN_IDX size"));
     RETVALUE(RFAILED);
  }

  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL,"reuseConnId", &(reuse));
  if(reuse)
  {
    *suConnId =szAccCb.connArr[idx];
  }
  else
  {
    *suConnId = ++(szAccCb.nxtSuConnId);
  }

  cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId", suConnId);

  RETVALUE(ROK);
} /* szAcUtlSztGetNewConnId */


/*
*
*       Fun:   szAcUtlSztRetrvConnId 
*
*       Desc:  Utility Function to retrieve stored Connection Id*
*              based on Index Id
*
*       Ret:   ROK
*
*       Notes: While sending out response, we fill the Connection
*              ID it corresponds to by specifying the index value.
*              This is already stored in our global array.
*              We just have to specify the INDEX value in which we
*              stored the Connection ID of request(using updConnId)
*              to retrive the Connection ID of request.    
*
*       File:  szac_sztutl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcUtlSztRetrvConnId
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
UConnId        *spConnId
)
#else
PUBLIC S16 szAcUtlSztRetrvConnId(tcCb,spCb,spConnId)
CmXtaTCCb      *tcCb;    /* tcCb data structure  */
CmXtaSpCb      *spCb;
UConnId        *spConnId;
#endif
{
   U8 idx = 0;

   TRC2(szAcUtlSztRetrvConnId);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"connIdx",&(idx));

   if( idx > SZAC_MAX_CONN_IDX )
   {
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztRetrvConnId():index size above SZAC_MAX_CONN_IDX size"));
      RETVALUE(RFAILED);
   }

   *spConnId = szAccCb.connArr[idx];

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"spConnId",spConnId);

   RETVALUE(ROK);
} /* szAcUtlSztRetrvConnId */

/*
*
*       Fun:   szAcUtlSztUpdConnId
*
*       Desc:  Utility Function to set Connection Id*
*               based on Index Id
*
*       Ret:   ROK
*
*       Notes: While receiving a request, we can store the Connection Id
*              of request in the index location specified by the user.  
*              While sending out the response we can fill the Connection
*              Id by retriieving it by giving the index location.
*
*       File:  szac_sztutl.c
*
*/

#ifdef ANSI
PUBLIC S16 szAcUtlSztUpdConnId
(
CmXtaTCCb      *tcCb,    /* tcCb data structure  */
CmXtaSpCb      *spCb,
UConnId        spConnId
)
#else
PUBLIC S16 szAcUtlSztUpdConnId(tcCb, spCb, spConnId)
CmXtaTCCb      *tcCb;    /* tcCb data structure  */
CmXtaSpCb      *spCb;
UConnId        spConnId;
#endif
{
   U8 idx = 0;

   TRC2(szAcUtlSztUpdConnId);
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"connIdx",&(idx));

   if( idx > SZAC_MAX_CONN_IDX )
   {
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztUpdConnId():index size above SZAC_MAX_CONN_IDX size"));
      RETVALUE(RFAILED);
   }

   szAccCb.connArr[idx] = spConnId; 
  
   RETVALUE(ROK);   
}


/*
*
*       Fun:   szAcUtlSztFillUDatReqPdu_
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
PUBLIC S16 szAcUtlSztFillUDatReqPdu
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztUDatEvnt  *uDatEvnt
)
#else
PUBLIC S16 szAcUtlSztFillUDatReqPdu(tcCb, spCb, uDatEvnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SztUDatEvnt  *uDatEvnt;
#endif
{

   U8 eventType;
   TRC2(szAcUtlSztFillUDatReqPdu_r9);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillUDatReqPdu_r9(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillUDatReqPdu_r9(), tcId (%ld)\n", tcCb->tcId));
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
               if(szAcUtlSztFillS1SetupRsp_r9(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
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
               if(szAcUtlSztFillPaging_r9(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
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
                if(szAcUtlSztFillOverloadStart_r9(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
                   RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_OVLD_STOP:
         {
		if(szAcUtlSztFillOverloadStop_r9(tcCb, spCb, &(uDatEvnt->pdu)) != ROK)
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
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUDatReqPdu: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);

} /* szAcUtlSztFillUDatReqPdu_r9 */

/*
*
*       Fun:   szAcUtlSztFillConReqPdu_r9
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
PUBLIC S16 szAcUtlSztFillConReqPdu
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztConReq    *conEvnt
)
#else
PUBLIC S16 szAcUtlSztFillConReqPdu(tcCb, spCb, conEvnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SztConReq    *conEvnt;
#endif
{

   U8 eventType;

   TRC2(szAcUtlSztFillConReqPdu_r9);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillConReqPdu_r9(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillConReqPdu_r9(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &(eventType));

   switch(eventType)
   {
      case SZT_MSG_ID_INIT_UE_MSG:
         {
                if(szAcUtlSztFillInitUeMsg_r9(tcCb, spCb, &(conEvnt->pdu)) != ROK)
                    RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_DL_NAS_TPT:
         {
                if(szAcUtlSztFillDwnlnkNasTpt_r9(tcCb, spCb, &(conEvnt->pdu)) != ROK)
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
                 if(szAcUtlSztFillHovrRqst_r9(tcCb, spCb, &(conEvnt->pdu)) != ROK)
                    RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_PATH_SWTCH_REQ:
         {
                 if(szAcUtlSztFillPathSwRqst_r9(tcCb, spCb, &(conEvnt->pdu)) != ROK)
                     RETVALUE(RFAILED);
         }
         break;
      default:
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillConReqPdu: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);

} /* szAcUtlSztFillConReqPdu_r9 */

/*
*
*       Fun:   szAcUtlSztFillConRspPdu_r9
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
PUBLIC S16 szAcUtlSztFillConRspPdu
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztConRsp    *conEvnt
)
#else
PUBLIC S16 szAcUtlSztFillConRspPdu(tcCb, spCb, conEvnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SztConRsp    *conEvnt;
#endif
{

   U8 eventType;

   TRC2(szAcUtlSztFillConRspPdu_r9);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillConRspPdu_r9(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillConRspPdu_r9(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &(eventType));

   switch(eventType)
   {
      case SZT_MSG_ID_CXT_SETUP_REQ:
         {
                 if(szAcUtlSztFillInitCxtSetupReq_r9(tcCb, spCb, &conEvnt->pdu) != ROK)
                    RETVALUE(RFAILED);
           
         }
         break;
      case SZT_MSG_ID_DL_NAS_TPT:
         {
                 if(szAcUtlSztFillDwnlnkNasTpt_r9(tcCb, spCb, &(conEvnt->pdu)) != ROK)
                     RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_UL_NAS_TPT:
         {
                 if(szAcUtlSztFillUplnkNasTpt_r9(tcCb, spCb, &(conEvnt->pdu)) != ROK)
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
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillConRspPdu: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);

} /* szAcUtlSztFillConRspPdu_r9 */

/*
*
*       Fun:   szAcUtlSztFillRelReqPdu_r9
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
PUBLIC S16 szAcUtlSztFillRelReqPdu
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztRelReq    *relEvnt
)
#else
PUBLIC S16 szAcUtlSztFillRelReqPdu(tcCb, spCb, relEvnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SztRelReq    *relEvnt;
#endif
{
   U8    eventType;

   TRC2(szAcUtlSztFillRelReqPdu_r9);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillRelReqPdu_r9(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillRelReqPdu_r9(), tcId (%ld)\n", tcCb->tcId));
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
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillRelReqPdu: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }

   
   RETVALUE(ROK);

} /* szAcUtlSztFillRelReqPdu_r9 */

/*
*
*       Fun:   szAcUtlSztFillRelRspPdu_r9
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
PUBLIC S16 szAcUtlSztFillRelRspPdu
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztRelRsp    *relEvnt
)
#else
PUBLIC S16 szAcUtlSztFillRelRspPdu(tcCb, spCb, relEvnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SztRelRsp    *relEvnt;
#endif
{
   U8 eventType;

   TRC2(szAcUtlSztFillRelRspPdu);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillRelRspPdu_r9(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillRelRspPdu_r9(), tcId (%ld)\n", tcCb->tcId));
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
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillRelRspPdu: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);

} /* szAcUtlSztFillRelRspPdu_r9 */

/*
*
*       Fun:   szAcUtlSztFillDatReqPdu_r9
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
PUBLIC S16 szAcUtlSztFillDatReqPdu
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SztDatEvntReq *datEvnt
)
#else
PUBLIC S16 szAcUtlSztFillDatReqPdu(tcCb, spCb, datEvnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SztDatEvntReq *datEvnt;
#endif
{
   U8 eventType = 0;
   TRC2(szAcUtlSztFillDatReqPdu_r9);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillDatReqPdu_r9(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillDatReqPdu_r9(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"eventType",&(eventType));

   switch(eventType)
   {
      case SZT_MSG_ID_CXT_SETUP_REQ:
         {  
                 if(szAcUtlSztFillInitCxtSetupReq_r9(tcCb, spCb, &datEvnt->pdu) != ROK)
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
                if(szAcUtlSztFillUplnkNasTpt_r9(tcCb, spCb, &(datEvnt->pdu)) != ROK)
                   RETVALUE(RFAILED);
         }
         break;
      case SZT_MSG_ID_DL_NAS_TPT:
         {
                if(szAcUtlSztFillDwnlnkNasTpt_r9(tcCb, spCb, &(datEvnt->pdu)) != ROK)
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
                 if(szAcUtlSztFillE_RABSetupRqst_r9(tcCb, spCb, &(datEvnt->pdu)) != ROK)
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
                 if(szAcUtlSztFillUeCxtRlsReq_r9(tcCb, spCb, &(datEvnt->pdu)) != ROK)
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
                 if(szAcUtlSztFillTraceStart_r9(tcCb, spCb, &(datEvnt->pdu)) != ROK)
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
                 if(szAcUtlSztFillCellTrafficTrace_r9(tcCb, spCb, &(datEvnt->pdu)) != ROK)
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
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillDatReqPdu_r9: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);

} /* szAcUtlSztFillDatReqPdu_r9 */
#endif
/*
*
*       Fun:   szFillTknStr4
*
*       Desc:  Call handler to fill Octet string of length less than 4
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szFillTknStr4
(
TknStr4 *ptr,     /* Pointer to the structure */
U8      len,      /* length to be filled */
U8      val       /* byte to be repetitively filled in */
)
#else
PUBLIC S16 szFillTknStr4(ptr, len, val)
TknStr4 *ptr;     /* Pointer to the structure */
U8      len;      /* length to be filled */
U8      val;      /* byte to be repetitively filled in */
#endif
{
   U8      i;     /* counter */

   TRC2(szFillTknStr4)

   /* make the element as present */
   ptr->pres = TRUE;

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

   RETVALUE(ROK);

} /* end of szFillTknStr4 */

/*
*
*       Fun:   szFillTknStrOSXL
*
*       Desc:  Call handler to fill Octet string
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szFillTknStrOSXL
(
TknStrOSXL *ptr,     /* Pointer to the structure */
U16         len,     /* length to be filled */
Data       *val,     /* byte to be repetitively filled in */
S1apPdu    **pdu
)
#else
PUBLIC S16 szFillTknStrOSXL(ptr, len, val, pdu)
TknStrOSXL *ptr;  /* Pointer to the structure */
U16         len;  /* lenrah to be filled */
Data       *val;  /* byte to be repetitively filled in */
S1apPdu    **pdu;
#endif
{
   U16     i;     /* counter */

   TRC2(szFillTknStrOSXL)

   /* make the element as present */
   ptr->pres = TRUE;
   ptr->len =  len;

   if (cmGetMem(pdu[0], len * sizeof(U8), (Ptr *)&ptr->val) != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szFillTknStrOSXL: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   for(i = 0; i < len; i++)
   {
      ptr->val[i] = val[i];
   }

   RETVALUE(ROK);

}

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
*       Fun:   szAcUtlSztFillS1SetupReq
*
*       Desc:  Call handler to fill S1 setup request message.
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
PUBLIC S16 szAcUtlSztFillS1SetupReq
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillS1SetupReq(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillS1SetupReq
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillS1SetupReq(pdu)
S1apPdu      **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu *szS1SetupReqPdu = NULLP;
   Mem     mem;
   U16     numComp;
   U8      pLMNId[10];
   U8      enbName[10];
   S16     ret;
   U32     pagDrx;
   U32     enbGlbId;
   U16     len;
   SztProtIE_Field_S1SetupRqstIEs *ie;
   SztSuppTAs_Item *tACItem;

   U32      buggy = 0;
   U32      critBug = 0;

   TRC2(szAcUtlSztFillS1SetupReq);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, 
                     (Ptr *)&szS1SetupReqPdu);
#ifndef SZ_ENC_DEC
   if(ret != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupReq: cmAllocEvnt failed, line %d\n",__LINE__));
      RETVALUE(RFAILED);
   }
#endif /* SZ_ENC_DEC */

   cmMemset((U8 *)&(szS1SetupReqPdu->pdu), 0, sizeof(SztS1AP_PDU));

   szFillTknU8(&(szS1SetupReqPdu->pdu.choice), SZT_TRGR_INTI_MSG);
   szFillTknU8(&(szS1SetupReqPdu->pdu.val.initiatingMsg.pres),PRSNT_NODEF);
   szFillTknU32(&(szS1SetupReqPdu->pdu.val.initiatingMsg.procedureCode),
                  Sztid_S1Setup);
   szFillTknU32(&(szS1SetupReqPdu->pdu.val.initiatingMsg.criticality),
                  SztCriticalityrejectEnum);

   szFillTknU8(&(szS1SetupReqPdu->pdu.val.initiatingMsg.value.u.sztS1SetupRqst.pres),PRSNT_NODEF);

#ifndef SZ_ENC_DEC 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"critBug",&(critBug));
#endif /* SZ_ENC_DEC */

   /* Filling 4 mandatory IEs */
   numComp = 4;

   if(critBug)
   {
      numComp++;
   }
   szFillTknU16(&(szS1SetupReqPdu->pdu.val.initiatingMsg.value.u.sztS1SetupRqst.protocolIEs.noComp),numComp);

   /* Get memory for numComp IEs */
   if ((cmGetMem(szS1SetupReqPdu, numComp*sizeof(SztProtIE_Field_S1SetupRqstIEs), (Ptr*)&szS1SetupReqPdu->pdu.val.initiatingMsg.value.u.sztS1SetupRqst.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC 
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupReq: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }
#ifndef SZ_ENC_DEC 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"bug",&(buggy));
#endif /* SZ_ENC_DEC */

   if(!buggy)
   {

      /* IE1 - Filling ENB Global Id */
      ie = &szS1SetupReqPdu->pdu.val.initiatingMsg.value.u.sztS1SetupRqst.protocolIEs.member[0];

      enbGlbId = 0;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbGlbId",&(enbGlbId));
#endif /* SZ_ENC_DEC */

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_Global_ENB_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
      szFillTknU8(&(ie->value.u.sztGlobal_ENB_ID.pres), PRSNT_NODEF);
      cmMemset(pLMNId,0,sizeof(pLMNId));
      strcpy((char *)pLMNId,"111");
      len = 3;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif /* SZ_ENC_DEC */

      szFillTknStrOSXL(&(ie->value.u.sztGlobal_ENB_ID.pLMNidentity), len, pLMNId, &szS1SetupReqPdu);     
      szFillTknU8(&(ie->value.u.sztGlobal_ENB_ID.eNB_ID.choice), ENB_ID_HOMEENB_ID);

      len = 28;
      szFillTknBStr32(&(ie->value.u.sztGlobal_ENB_ID.eNB_ID.val.homeENB_ID), len, 100);
      ie->value.u.sztGlobal_ENB_ID.iE_Extns.noComp.pres = NOTPRSNT;

      /* IE2 - Filling ENB Name */ 
      ie = &szS1SetupReqPdu->pdu.val.initiatingMsg.value.u.sztS1SetupRqst.protocolIEs.member[1];

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_eNBname);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      cmMemset(enbName,0,sizeof(enbName));
      strcpy((char *)enbName,"ENB"); 
      szFillTknStrOSXL(&(ie->value.u.sztENBname),3,enbName,&szS1SetupReqPdu);
   }
   else
   {

      /* IE1 - Filling ENB Global Id */
      ie = &szS1SetupReqPdu->pdu.val.initiatingMsg.value.u.sztS1SetupRqst.protocolIEs.member[1];

      enbGlbId = 0;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbGlbId",&(enbGlbId));
#endif /* SZ_ENC_DEC */

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_Global_ENB_ID);
      szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
      szFillTknU8(&(ie->value.u.sztGlobal_ENB_ID.pres), PRSNT_NODEF);
      cmMemset(pLMNId,0,sizeof(pLMNId));
      strcpy((char *)pLMNId,"111");
      len = 3;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif /* SZ_ENC_DEC */
      szFillTknStrOSXL(&(ie->value.u.sztGlobal_ENB_ID.pLMNidentity), len, pLMNId, &szS1SetupReqPdu);     
      szFillTknU8(&(ie->value.u.sztGlobal_ENB_ID.eNB_ID.choice), ENB_ID_HOMEENB_ID);

      len = 28;
      szFillTknBStr32(&(ie->value.u.sztGlobal_ENB_ID.eNB_ID.val.homeENB_ID), len, 100);
      ie->value.u.sztGlobal_ENB_ID.iE_Extns.noComp.pres = NOTPRSNT;

      /* IE2 - Filling ENB Name */ 
      ie = &szS1SetupReqPdu->pdu.val.initiatingMsg.value.u.sztS1SetupRqst.protocolIEs.member[0];

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_eNBname);
      szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
      cmMemset(enbName,0,sizeof(enbName));
      strcpy((char *)enbName,"ENB"); 
      szFillTknStrOSXL(&(ie->value.u.sztENBname),3,enbName,&szS1SetupReqPdu);
   }

   /* IE2 - Filling Supported TAs */
   ie = &szS1SetupReqPdu->pdu.val.initiatingMsg.value.u.sztS1SetupRqst.protocolIEs.member[2];

   szFillTknU8(&(ie->pres),PRSNT_NODEF);
   szFillTknU32(&(ie->id),Sztid_SuppTAs);
   szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);

   numComp = 1;
   szFillTknU16(&(ie->value.u.sztSuppTAs.noComp),numComp);

   /* IE3 - Allocate memory for TA items */
   if ((cmGetMem(szS1SetupReqPdu, numComp*sizeof(SztSuppTAs_Item), 
        (Ptr*)&(ie->value.u.sztSuppTAs.member))) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupReq: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   /* IE3 - Filling TA item 1 */
   tACItem = &ie->value.u.sztSuppTAs.member[0];
   szFillTknU8(&(tACItem->pres),PRSNT_NODEF);

   /* IE3 - Filling tAC */
   len = 2;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"tacLen",&(len));
#endif /* SZ_ENC_DEC */

   szFillTknStr4(&(tACItem->tAC), (U8)len, 1);

   /* IE3 - Filling broadcastPLMNs */
   numComp = 1;
   /* Allocate memory for broadcast PLMNs */
   if ((cmGetMem(szS1SetupReqPdu, numComp*sizeof(SztPLMNidentity), 
        (Ptr*)&(tACItem->broadcastPLMNs.member))) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupReq: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }
   szFillTknU16(&(tACItem->broadcastPLMNs.noComp),numComp);

   cmMemset(pLMNId,0,sizeof(pLMNId));
   strcpy((char *)pLMNId,"111");
   len = 3;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"plmnIdVal",&(pLMNId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif /* SZ_ENC_DEC */

   szFillTknStrOSXL(&(tACItem->broadcastPLMNs.member[0]),len,pLMNId,&szS1SetupReqPdu);

   ie = &szS1SetupReqPdu->pdu.val.initiatingMsg.value.u.sztS1SetupRqst.protocolIEs.member[3];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_DefaultPagDRX);

   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   pagDrx = 1;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"pagDrx", &(pagDrx));
#endif /* SZ_ENC_DEC */
   szFillTknU32(&(ie->value.u.sztPagDRX),pagDrx);

   if(critBug)
   {
      ie = &szS1SetupReqPdu->pdu.val.initiatingMsg.value.u.sztS1SetupRqst.protocolIEs.member[4];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);

      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

      szFillTknU32(&(ie->value.u.sztPagDRX), pagDrx);
   }

   *pdu = szS1SetupReqPdu;

   RETVALUE(ROK);
   
} /* End  of szAcUtlSztFillS1SetupReq */

/*
*
*       Fun:   szAcUtlSztFillS1SetupRsp_r9
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
PUBLIC S16 szAcUtlSztFillS1SetupRsp_r9
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillS1SetupRsp_r9(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillS1SetupRsp_r9
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillS1SetupRsp_r9(pdu)
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
   
   
   TRC2(szAcUtlSztFillS1SetupRsp_r9);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szS1SetupRspPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupRsp_r9: cmAllocEvnt failed, line%d\n",__LINE__));
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
   szFillTknU16(&(szS1SetupRspPdu->pdu.val.successfulOutcome.value.u.sztS1SetupResp.protocolIEs.noComp),numComp);

   /* Allocte memory for 2 IEs */
   if ((cmGetMem(szS1SetupRspPdu, numComp*sizeof(SztProtIE_Field_S1SetupRespIEs),(Ptr*)&szS1SetupRspPdu->pdu.val.successfulOutcome.value.u.sztS1SetupResp.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupRsp_r9: cmGetMem failed, line %d\n",__LINE__));
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

   *pdu = szS1SetupRspPdu;

   RETVALUE(ROK);
} /* End of szAcUtlSztFillS1SetupRsp_r9 */

/*
*
*       Fun:   szAcUtlSztFillS1SetupFail
*
*       Desc:  Call handler to fill S1 Setup Failure message
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
PUBLIC S16 szAcUtlSztFillS1SetupFail
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillS1SetupFail(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillS1SetupFail
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillS1SetupFail(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu *szS1SetupFailPdu = NULLP;
   Mem     mem;
   U16     numComp;
   S16     ret;
   U8      choice;
   U32     cause;
   SztProtIE_Field_S1SetupFailIEs *ie;

   TRC2(szAcUtlSztFillS1SetupFail);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szS1SetupFailPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupRsp_r9: cmAllocEvnt failed, line%d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szS1SetupFailPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szS1SetupFailPdu->pdu.choice), SZT_TRGR_UNSUCCESS_OUTCOME);
   szFillTknU8(&(szS1SetupFailPdu->pdu.val.unsuccessfulOutcome.pres),PRSNT_NODEF);
   szFillTknU32(&(szS1SetupFailPdu->pdu.val.unsuccessfulOutcome.procedureCode),Sztid_S1Setup);
   szFillTknU32(&(szS1SetupFailPdu->pdu.val.unsuccessfulOutcome.criticality),SztCriticalityrejectEnum);
   szFillTknU8(&(szS1SetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztS1SetupFail.pres),PRSNT_NODEF);

   /* Filling 1 mandatory header */

   numComp = 1;
   szFillTknU16(&(szS1SetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztS1SetupFail.protocolIEs.noComp),numComp);

   if ((cmGetMem(szS1SetupFailPdu, numComp*sizeof(SztProtIE_Field_S1SetupFailIEs),(Ptr*)&szS1SetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztS1SetupFail.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupFail: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling cause */
   ie = &szS1SetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztS1SetupFail.protocolIEs.member[0];

   szFillTknU8(&(ie->pres),PRSNT_NODEF);
   szFillTknU32(&(ie->id),Sztid_Cause);
   szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
   choice = 0;
   cause = 0;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
   szFillTknU8(&(ie->value.u.sztCause.choice),choice);
   szFillTknU32(&(ie->value.u.sztCause.val.radioNw),cause);

   *pdu = szS1SetupFailPdu;

   RETVALUE(ROK);
} /* End of szAcUtlSztFillS1SetupFail */

/*
*
*       Fun:   szAcUtlSztFillInitUeMsg_r9
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
PUBLIC S16 szAcUtlSztFillInitUeMsg_r9
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInitUeMsg_r9(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillInitUeMsg_r9
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInitUeMsg_r9(pdu)
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
   SztProtIE_Field_InitUEMsg_IEs *ie;

   TRC2(szAcUtlSztFillInitUeMsg_r9);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szInitUeMsgPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitUeMsg_r9: cmAllocEvnt failed, line %d\n",__LINE__));
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
   szFillTknU16(&(szInitUeMsgPdu->pdu.val.initiatingMsg.value.u.sztInitUEMsg.protocolIEs.noComp),numComp);

   /* Allocate memory for 3 IEs */
   if ((cmGetMem(szInitUeMsgPdu, numComp*sizeof(SztProtIE_Field_InitUEMsg_IEs), (Ptr*)&szInitUeMsgPdu->pdu.val.initiatingMsg.value.u.sztInitUEMsg.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitUeMsg_r9: cmGetMem failed, line %d\n",__LINE__));
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


   *pdu = szInitUeMsgPdu;

   RETVALUE(ROK);

} /* End of szAcUtlSztFillInitUeMsg_r9 */

/*
*
*       Fun:   szAcUtlSztFillInitCxtSetupReq_r9
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
PUBLIC S16 szAcUtlSztFillInitCxtSetupReq_r9
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInitCxtSetupReq_r9(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillInitCxtSetupReq_r9
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInitCxtSetupReq_r9(pdu)
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
   SztProtIE_Field_InitCntxtSetupRqstIEs *ie;
   SztProtIE_SingleCont_E_RABToBeSetupItemCtxtSUReqIEs *ie1;

   U32  buggy = 0;
   U32  critBug = 0;

   TRC2(szAcUtlSztFillInitCxtSetupReq_r9);

   mem.region = 0;
   mem.pool   = 0;

   /* Allocate memory for pdu */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, 
         (Ptr *)&szInitCntxtSetupReqPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitCxtSetupReq_r9: cmAllocEvnt failed, line %d\n",__LINE__));
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

   if(critBug)
   {
      numComp++;
   }
   szFillTknU16(&(szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.noComp), numComp);

   if ((cmGetMem(szInitCntxtSetupReqPdu, (numComp * sizeof(SztProtIE_Field_InitCntxtSetupRqstIEs)),
               (Ptr *)&szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitCxtSetupReq_r9: cmGetMem failed, line %d\n",__LINE__));
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
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitCxtSetupReq_r9: cmGetMem failed, line %d\n",__LINE__));
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

      ie1->value.u.sztE_RABToBeSetupItemCtxtSUReq.iE_Extns.noComp.pres = NOTPRSNT;
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
      ie = &szInitCntxtSetupReqPdu->pdu.val.initiatingMsg.value.u.sztInitCntxtSetupRqst.protocolIEs.member[6];

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
*       Fun:   szAcUtlSztFillInitCxtSetupRsp
*
*       Desc:  Call handler to fill Initial Context Setup 
*              Response message.
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
PUBLIC S16 szAcUtlSztFillInitCxtSetupRsp
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
S1apPdu        **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInitCxtSetupRsp(tcCb, spCb, pdu)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
S1apPdu        **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillInitCxtSetupRsp
(
S1apPdu        **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInitCxtSetupRsp(pdu)
S1apPdu        **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu *szInitCntxtSetupRspPdu = NULLP;
   S16  ret;
   Mem  mem; 
   U32  enbId;
   U16  numComp;
   U32  mmeId;
#ifndef SZ_ENC_DEC
   ProcId  procId = 0;
   UConnId suConnId = 0;
#endif /* SZ_ENC_DEC */
   U16     len;
   U8      gTPId[10];
   U8      tptAddr[10];
   SztProtIE_Field_InitCntxtSetupRespIEs *ie;
   SztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs *ie1;

   TRC2(szAcUtlSztFillInitCxtSetupRsp);

   mem.region = 0;
   mem.pool   = 0;

   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem,
                     (Ptr *)&szInitCntxtSetupRspPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitCxtSetupRsp: cmAllocEvnt failed,line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szInitCntxtSetupRspPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szInitCntxtSetupRspPdu->pdu.choice), SZT_TRGR_SUCCESS_OUTCOME);
   szFillTknU8(&(szInitCntxtSetupRspPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(szInitCntxtSetupRspPdu->pdu.val.successfulOutcome.procedureCode),
                  Sztid_InitCntxtSetup);
   szFillTknU32(&(szInitCntxtSetupRspPdu->pdu.val.successfulOutcome.criticality),
                  SztCriticalityrejectEnum);

   /* Filling 2 mandatory headers */

   /* Read enbId and mmeId from xml */
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
   szFillTknU8(&(szInitCntxtSetupRspPdu->pdu.val.successfulOutcome.value.u.sztInitCntxtSetupResp.pres),PRSNT_NODEF);

   numComp = 3;
   szFillTknU16(&(szInitCntxtSetupRspPdu->pdu.val.successfulOutcome.value.u.sztInitCntxtSetupResp.protocolIEs.noComp), numComp);

   if ((cmGetMem(szInitCntxtSetupRspPdu, (numComp * sizeof(SztProtIE_Field_InitCntxtSetupRespIEs)),
       (Ptr *)&szInitCntxtSetupRspPdu->pdu.val.successfulOutcome.value.u.sztInitCntxtSetupResp.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitCxtSetupRsp: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   /* Filling MME ID */
   ie = &szInitCntxtSetupRspPdu->pdu.val.successfulOutcome.value.u.sztInitCntxtSetupResp.protocolIEs.member[0];
   szFillTknU8(&(ie->pres), PRSNT_NODEF);   
   szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);   
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);   
   szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);  

   /* Filling ENB ID */
   ie = &szInitCntxtSetupRspPdu->pdu.val.successfulOutcome.value.u.sztInitCntxtSetupResp.protocolIEs.member[1];    

   szFillTknU8(&(ie->pres), PRSNT_NODEF);  
   szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);   
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum); 
   szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);                        

   ie = &szInitCntxtSetupRspPdu->pdu.val.successfulOutcome.value.u.sztInitCntxtSetupResp.protocolIEs.member[2];    

   szFillTknU8(&(ie->pres), PRSNT_NODEF);  
   szFillTknU32(&(ie->id), Sztid_E_RABSetupLstCtxtSURes);   
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum); 
   {
      numComp = 1;
      szFillTknU16(&(ie->value.u.sztE_RABSetupLstCtxtSURes.noComp), numComp);

      if (cmGetMem(szInitCntxtSetupRspPdu, (numComp * sizeof(SztProtIE_SingleCont_E_RABSetupItemCtxtSUResIEs)), 
               (Ptr *)&(ie->value.u.sztE_RABSetupLstCtxtSURes.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitCxtSetupRsp: cmGetMem failed, line %d\n", __LINE__));
#endif /* SZ_ENC_DEC */
         RETVALUE(RFAILED);
      }

      ie1 = &(ie->value.u.sztE_RABSetupLstCtxtSURes.member[0]);

      szFillTknU8(&(ie1->pres), PRSNT_NODEF);
      szFillTknU32(&(ie1->id), Sztid_E_RABSetupItemCtxtSURes);
      szFillTknU32(&(ie1->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie1->value.u.sztE_RABSetupItemCtxtSURes.pres), PRSNT_NODEF);
      szFillTknU32(&(ie1->value.u.sztE_RABSetupItemCtxtSURes.e_RAB_ID), 15);
      cmMemset(tptAddr,0,sizeof(tptAddr));
      strcpy((char *)tptAddr,"11");
      len = 2;
      szFillTknStrOSXL(&(ie1->value.u.sztE_RABSetupItemCtxtSURes.transportLyrAddr), len, tptAddr, &szInitCntxtSetupRspPdu);
      cmMemset(gTPId,0,sizeof(gTPId));
      strcpy((char *)gTPId,"1111");
      len = 4;
      szFillTknStrOSXL(&(ie1->value.u.sztE_RABSetupItemCtxtSURes.gTP_TEID), len, gTPId, &szInitCntxtSetupRspPdu);
      ie1->value.u.sztE_RABSetupItemCtxtSURes.iE_Extns.noComp.pres = NOTPRSNT;
   }

   *pdu = szInitCntxtSetupRspPdu; 

   RETVALUE(ROK);

}

/*
*
*       Fun:   szAcUtlSztFillInitCxtSetupFail 
*
*       Desc:  Call handler to fill Initial Context Setup
*              Failure message.
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
PUBLIC S16 szAcUtlSztFillInitCxtSetupFail
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInitCxtSetupFail(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillInitCxtSetupFail
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInitCxtSetupFail(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu *szInitCntxtSetupFailPdu = NULLP;
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
   SztProtIE_Field_InitCntxtSetupFailIEs *ie;

   TRC2(szAcUtlSztFillInitCxtSetupFail);

   mem.region = 0;
   mem.pool   = 0;

   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem,
                     (Ptr *)&szInitCntxtSetupFailPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitCxtSetupFail: cmAllocEvnt failed,line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szInitCntxtSetupFailPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szInitCntxtSetupFailPdu->pdu.choice), SZT_TRGR_UNSUCCESS_OUTCOME);
   szFillTknU8(&(szInitCntxtSetupFailPdu->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(szInitCntxtSetupFailPdu->pdu.val.unsuccessfulOutcome.procedureCode),
                  Sztid_InitCntxtSetup);
   szFillTknU32(&(szInitCntxtSetupFailPdu->pdu.val.unsuccessfulOutcome.criticality),
                  SztCriticalityrejectEnum);

   /* Filling 3 mandatory headers */

   /* Get enbId and mmeId */
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
   enbId = szacPduInfo[procId][suConnId].enbId;
   mmeId = szacPduInfo[procId][suConnId].mmeId;

   /* Read enbId and mmeId from xml */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#else
   enbId = 0;
   mmeId = 0;
#endif   /* SZ_ENC_DEC */
   szFillTknU8(&(szInitCntxtSetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.pres), PRSNT_NODEF);

   numComp = 3;
   szFillTknU16(&(szInitCntxtSetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.protocolIEs.noComp), numComp);

   if ((cmGetMem(szInitCntxtSetupFailPdu, (numComp * sizeof(SztProtIE_Field_InitCntxtSetupFailIEs)),
       (Ptr *)&szInitCntxtSetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillInitCxtSetupFail: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling MME ID */
   ie = &szInitCntxtSetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.protocolIEs.member[0];
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

   /* IE2 - Filling ENB ID */
   ie = &szInitCntxtSetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.protocolIEs.member[1];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

   /* IE3 - Filling cause */
   ie = &szInitCntxtSetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztInitCntxtSetupFail.protocolIEs.member[2];

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

   *pdu = szInitCntxtSetupFailPdu; 

   RETVALUE(ROK);

} /* End of szAcUtlSztFillInitCxtSetupFail */

/*
*
*       Fun:   szAcUtlSztFillUeCxtRlsCmd 
*
*       Desc:  Call handler to fill UE context release
*              command message.
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
PUBLIC S16 szAcUtlSztFillUeCxtRlsCmd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUeCxtRlsCmd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUeCxtRlsCmd
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUeCxtRlsCmd(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu *szUeCxtRlsCmdPdu = NULLP;
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
   SztProtIE_Field_UECntxtRlsCmmd_IEs *ie;

   TRC2(szAcUtlSztFillUeCxtRlsCmd);

   mem.region = 0;
   mem.pool   = 0;

   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem,
                     (Ptr *)&szUeCxtRlsCmdPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUeCxtRlsCmd: cmAllocEvnt failed,line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szUeCxtRlsCmdPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szUeCxtRlsCmdPdu->pdu.choice), SZT_TRGR_INTI_MSG);
   szFillTknU8(&(szUeCxtRlsCmdPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(szUeCxtRlsCmdPdu->pdu.val.initiatingMsg.procedureCode),
                  Sztid_UECntxtRls);
   szFillTknU32(&(szUeCxtRlsCmdPdu->pdu.val.initiatingMsg.criticality),
                  SztCriticalityrejectEnum);

   /* Filling 2 mandatory headers */

   /* Read enbId and mmeId from xml */
   /* Get enbId and mmeId */
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
#endif   /* SZ_ENC_DEC */
   szFillTknU8(&(szUeCxtRlsCmdPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsCmmd.pres), PRSNT_NODEF);

   numComp = 2;
   szFillTknU16(&(szUeCxtRlsCmdPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsCmmd.protocolIEs.noComp), numComp);

   if ((cmGetMem(szUeCxtRlsCmdPdu, (numComp * sizeof(SztProtIE_Field_UECntxtRlsCmmd_IEs)),
       (Ptr *)&szUeCxtRlsCmdPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsCmmd.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUeCxtRlsCmd: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling UE IDs - MME and ENB ID */
   ie = &szUeCxtRlsCmdPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsCmmd.protocolIEs.member[0];
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_UE_S1AP_IDs);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU8(&(ie->value.u.sztUE_S1AP_IDs.choice), UE_S1AP_IDS_UE_S1AP_ID_PAIR);
   szFillTknU8(&(ie->value.u.sztUE_S1AP_IDs.val.uE_S1AP_ID_pair.pres), PRSNT_NODEF);
   szFillTknU32(&(ie->value.u.sztUE_S1AP_IDs.val.uE_S1AP_ID_pair.mME_UE_S1AP_ID), mmeId);
   szFillTknU32(&(ie->value.u.sztUE_S1AP_IDs.val.uE_S1AP_ID_pair.eNB_UE_S1AP_ID), enbId);

   /* IE2 - Filling cause */
   ie = &szUeCxtRlsCmdPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsCmmd.protocolIEs.member[1];

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

   *pdu = szUeCxtRlsCmdPdu; 

   RETVALUE(ROK);

} /* End of szAcUtlSztFillUeCxtRlsCmd */

/*
*
*       Fun:   szAcUtlSztFillNoDataMsg 
*
*       Desc:  Call handler to fill No Data Msg
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
PUBLIC S16 szAcUtlSztFillNoDataMsg
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillNoDataMsg(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillNoDataMsg
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillNoDataMsg(pdu)
S1apPdu    **pdu;
#endif
#endif
{
   S1apPdu *szNoData = NULLP;
   S16  ret;
   Mem  mem; 

   TRC2(szAcUtlSztFillNoDataMsg);

   mem.region = 0;
   mem.pool   = 0;

   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem,
                     (Ptr *)&szNoData);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillNoDataMsg: cmAllocEvnt failed,line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szNoData->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szNoData->pdu.choice.pres = NOTPRSNT;
  
   *pdu = szNoData;

   RETVALUE(ROK);

} /* End of szAcUtlSztFillNoDataMsg */

/*
*
*       Fun:   szAcUtlSztFillUeCxtRlsCmpl
*
*       Desc:  Call handler to fill UE context release
*              complete Response message.
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
PUBLIC S16 szAcUtlSztFillUeCxtRlsCmpl
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
S1apPdu        **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUeCxtRlsCmpl(tcCb, spCb, pdu)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
S1apPdu        **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUeCxtRlsCmpl
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUeCxtRlsCmpl(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu *szUeCxtRlsCmplPdu = NULLP;
   S16  ret;
   Mem  mem; 
   U32  enbId;
   U16  numComp;
   U32  mmeId;
#ifndef SZ_ENC_DEC
   ProcId  procId = 0;
   UConnId suConnId = 0;
#endif
   SztProtIE_Field_UECntxtRlsComplete_IEs *ie;

   TRC2(szAcUtlSztFillUeCxtRlsCmpl);

   mem.region = 0;
   mem.pool   = 0;

   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem,
                     (Ptr *)&szUeCxtRlsCmplPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUeCxtRlsCmpl: cmAllocEvnt failed,line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szUeCxtRlsCmplPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szUeCxtRlsCmplPdu->pdu.choice), SZT_TRGR_SUCCESS_OUTCOME);
   szFillTknU8(&(szUeCxtRlsCmplPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(szUeCxtRlsCmplPdu->pdu.val.successfulOutcome.procedureCode),
                  Sztid_UECntxtRls);
   szFillTknU32(&(szUeCxtRlsCmplPdu->pdu.val.successfulOutcome.criticality),
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

   /* Read enbId and mmeId from xml */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#else
   mmeId = 0;
   enbId = 0;
#endif   /* SZ_ENC_DEC */
   szFillTknU8(&(szUeCxtRlsCmplPdu->pdu.val.successfulOutcome.value.u.sztUECntxtRlsComplete.pres),PRSNT_NODEF);
   numComp = 2;
   szFillTknU16(&(szUeCxtRlsCmplPdu->pdu.val.successfulOutcome.value.u.sztUECntxtRlsComplete.protocolIEs.noComp), numComp);

   if ((cmGetMem(szUeCxtRlsCmplPdu, (numComp * sizeof(SztProtIE_Field_UECntxtRlsComplete_IEs)),
       (Ptr *)&szUeCxtRlsCmplPdu->pdu.val.successfulOutcome.value.u.sztUECntxtRlsComplete.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUeCxtRlsCmpl: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling MME ID */
   ie = &szUeCxtRlsCmplPdu->pdu.val.successfulOutcome.value.u.sztUECntxtRlsComplete.protocolIEs.member[0];
   szFillTknU8(&(ie->pres), PRSNT_NODEF);   
   szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);   
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);   
   szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);  

   /* IE2 - Filling ENB ID */
   ie = &szUeCxtRlsCmplPdu->pdu.val.successfulOutcome.value.u.sztUECntxtRlsComplete.protocolIEs.member[1];    

   szFillTknU8(&(ie->pres), PRSNT_NODEF);  
   szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);   
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum); 
   szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);                        

   *pdu = szUeCxtRlsCmplPdu; 

   RETVALUE(ROK);

} /* End of  szAcUtlSztFillUeCxtRlsCmpl */

/*
*
*       Fun:   szAcUtlSztFillUeCxtRlsReq_r9 
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
PUBLIC S16 szAcUtlSztFillUeCxtRlsReq_r9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUeCxtRlsReq_r9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUeCxtRlsReq_r9
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUeCxtRlsReq_r9(pdu)
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

   TRC2(szAcUtlSztFillUeCxtRlsReq_r9);

   mem.region = 0;
   mem.pool   = 0;

   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem,
                     (Ptr *)&szUeCxtRlsReqPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUeCxtRlsReq_r9: cmAllocEvnt failed,line %d\n",__LINE__));
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

   szFillTknU16(&(szUeCxtRlsReqPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsRqst.protocolIEs.noComp), numComp);

   if ((cmGetMem(szUeCxtRlsReqPdu, (numComp * sizeof(SztProtIE_Field_UECntxtRlsRqst_IEs)),
       (Ptr *)&szUeCxtRlsReqPdu->pdu.val.initiatingMsg.value.u.sztUECntxtRlsRqst.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUeCxtRlsReq_r9: cmGetMem failed, line %d\n",__LINE__));
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

   *pdu = szUeCxtRlsReqPdu; 

   RETVALUE(ROK);

} /* End of szAcUtlSztFillUeCxtRlsReq_r9 */

/*
*
*       Fun:   szAcUtlSztFillUplnkNasTpt_r9
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
PUBLIC S16 szAcUtlSztFillUplnkNasTpt_r9
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUplnkNasTpt_r9(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUplnkNasTpt_r9
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUplnkNasTpt_r9(pdu)
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
   SztProtIE_Field_UlnkNASTport_IEs *ie;

   TRC2(szAcUtlSztFillUplnkNasTpt_r9);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szUplnkNasTptPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUplnkNasTpt_r9: cmAllocEvnt failed, line %d\n",__LINE__));
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
   szFillTknU16(&(szUplnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztUlnkNASTport.protocolIEs.noComp),numComp);

   /* Allocate memory for 3 IEs */
   if ((cmGetMem(szUplnkNasTptPdu, numComp*sizeof(SztProtIE_Field_UlnkNASTport_IEs), (Ptr*)&szUplnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztUlnkNASTport.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUplnkNasTpt_r9: cmGetMem failed, line %d\n",__LINE__));
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

   *pdu = szUplnkNasTptPdu;

   RETVALUE(ROK);

} /* End of szAcUtlSztFillUplnkNasTpt_r9 */

/*
*
*       Fun:   szAcUtlSztFillDwnlnkNasTpt_r9
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
PUBLIC S16 szAcUtlSztFillDwnlnkNasTpt_r9
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillDwnlnkNasTpt_r9(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillDwnlnkNasTpt_r9
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillDwnlnkNasTpt_r9(pdu)
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

   TRC2(szAcUtlSztFillDwnlnkNasTpt_r9);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szDwnlnkNasTptPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillDwnlnkNasTpt_r9: cmAllocEvnt failed, line %d\n",__LINE__));
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
   if(critBug)
   {
      numComp++;
   }
   szFillTknU16(&(szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.protocolIEs.noComp),numComp);

   /* Allocate memory for 3 IEs */
   if ((cmGetMem(szDwnlnkNasTptPdu, numComp*sizeof(SztProtIE_Field_DlnkNASTport_IEs), (Ptr*)&szDwnlnkNasTptPdu->pdu.val.initiatingMsg.value.u.sztDlnkNASTport.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillDwnlnkNasTpt_r9: cmGetMem failed, line %d\n",__LINE__));
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
   }

   *pdu = szDwnlnkNasTptPdu;

   RETVALUE(ROK);

} /* End of szAcUtlSztFillDwnlnkNasTpt_r9 */

/*
*
*       Fun:   szAcUtlSztFillNasNonDlvryInd
*
*       Desc:  Call handler to fill uplink NAS non-delivery
*              indication message.
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
PUBLIC S16 szAcUtlSztFillNasNonDlvryInd
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillNasNonDlvryInd(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
S1apPdu      **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillNasNonDlvryInd
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillNasNonDlvryInd(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu *szNasNonDlvryIndPdu = NULLP;
   Mem     mem;
   U16     numComp;
   U32     mmeId = 0;
   U32     enbId = 0;
   U8      nasPdu[10];
   U8      choice;
   U32     cause;
   S16     ret;
   U16     len;
#ifndef SZ_ENC_DEC
   ProcId  procId = 0;
   UConnId suConnId = 0;
#endif
   SztProtIE_Field_NASNonDlvryInd_IEs *ie;

   TRC2(szAcUtlSztFillNasNonDlvryInd);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szNasNonDlvryIndPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillNasNonDlvryInd: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szNasNonDlvryIndPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szNasNonDlvryIndPdu->pdu.choice), SZT_TRGR_INTI_MSG);
   szFillTknU8(&(szNasNonDlvryIndPdu->pdu.val.initiatingMsg.pres),PRSNT_NODEF);
   szFillTknU32(&(szNasNonDlvryIndPdu->pdu.val.initiatingMsg.procedureCode),Sztid_NASNonDlvryInd);
   szFillTknU32(&(szNasNonDlvryIndPdu->pdu.val.initiatingMsg.criticality),SztCriticalityignoreEnum);

   /* Filling of 4 mandatory IEs */
   szFillTknU8(&(szNasNonDlvryIndPdu->pdu.val.initiatingMsg.value.u.sztNASNonDlvryInd.pres),PRSNT_NODEF);

   numComp = 4;
   szFillTknU16(&(szNasNonDlvryIndPdu->pdu.val.initiatingMsg.value.u.sztNASNonDlvryInd.protocolIEs.noComp),numComp);

   /* Allocate memory for 4 IEs */
   if ((cmGetMem(szNasNonDlvryIndPdu, numComp*sizeof(SztProtIE_Field_NASNonDlvryInd_IEs), (Ptr*)&szNasNonDlvryIndPdu->pdu.val.initiatingMsg.value.u.sztNASNonDlvryInd.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillNasNonDlvryInd: cmGetMem failed, line %d\n",__LINE__));
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
   ie = &szNasNonDlvryIndPdu->pdu.val.initiatingMsg.value.u.sztNASNonDlvryInd.protocolIEs.member[0];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

   /* IE2 - Filling enb s1ap id */
   ie = &szNasNonDlvryIndPdu->pdu.val.initiatingMsg.value.u.sztNASNonDlvryInd.protocolIEs.member[1];
  
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
#endif
   szFillTknU8(&(ie->pres),PRSNT_NODEF);     
   szFillTknU32(&(ie->id),Sztid_eNB_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID),enbId);

   /* IE3 - Filling nas pdu */
   ie = &szNasNonDlvryIndPdu->pdu.val.initiatingMsg.value.u.sztNASNonDlvryInd.protocolIEs.member[2];
  
   szFillTknU8(&(ie->pres),PRSNT_NODEF);     
   szFillTknU32(&(ie->id),Sztid_NAS_PDU);
   szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
   cmMemset(nasPdu,0,sizeof(nasPdu));
   strcpy((char *)nasPdu,"111");
   len = 3;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"nasPduVal",&(nasPdu));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"nasPduLen",&(len));
#endif
   szFillTknStrOSXL(&(ie->value.u.sztNAS_PDU), len, nasPdu, &szNasNonDlvryIndPdu);

   /* IE4 - Filling cause */
   ie = &szNasNonDlvryIndPdu->pdu.val.initiatingMsg.value.u.sztNASNonDlvryInd.protocolIEs.member[3];

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

   *pdu = szNasNonDlvryIndPdu;

   RETVALUE(ROK);

} /* End of szAcUtlSztFillNasNonDlvryInd */

/*
*
*       Fun:   szAcUtlSztFillReset 
*
*       Desc:  Call handler to fill reset message
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
PUBLIC S16 szAcUtlSztFillReset
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillReset(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillReset
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillReset(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu *szRstPdu = NULLP;
   S16  ret;
   Mem  mem; 
   U16  numComp;
   U32  cause;
   U8   choice;
   U32  enbId;
   U32  mmeId;
   Txt  enb[SZAC_LSZ_MAX_CONN];
   Txt  mme[SZAC_LSZ_MAX_CONN];
   U16  i;

   SztProtIE_Field_ResetIEs *ie;
   SztProtIE_SingleCont_UE_assocLogS1_ConItemRes *ie1;

   TRC2(szAcUtlSztFillReset);

   mem.region = 0;
   mem.pool   = 0;

   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem,
                     (Ptr *)&szRstPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillReset: cmAllocEvnt failed,line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szRstPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szRstPdu->pdu.choice), SZT_TRGR_INTI_MSG);
   szFillTknU8(&(szRstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(szRstPdu->pdu.val.initiatingMsg.procedureCode),
                  Sztid_Reset);
   szFillTknU32(&(szRstPdu->pdu.val.initiatingMsg.criticality),
                  SztCriticalityrejectEnum);
   szFillTknU8(&(szRstPdu->pdu.val.initiatingMsg.value.u.sztReset.pres),
                  PRSNT_NODEF);

   /* Filling 2 mandatory headers */

   numComp = 2;
   szFillTknU16(&(szRstPdu->pdu.val.initiatingMsg.value.u.sztReset.protocolIEs.noComp), numComp);

   if ((cmGetMem(szRstPdu, (numComp * sizeof(SztProtIE_Field_ResetIEs)),
       (Ptr *)&szRstPdu->pdu.val.initiatingMsg.value.u.sztReset.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillReset: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling cause */
   ie = &szRstPdu->pdu.val.initiatingMsg.value.u.sztReset.protocolIEs.member[0];

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

   /* IE2 - Filling reset type */
   ie = &szRstPdu->pdu.val.initiatingMsg.value.u.sztReset.protocolIEs.member[1];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_ResetTyp);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

   numComp = 0;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"lstCnt",&numComp);
#endif

   if(numComp == 0)
   {
      szFillTknU8(&(ie->value.u.sztResetTyp.choice),SZ_FULL_RESET);
      szFillTknU32(&(ie->value.u.sztResetTyp.val.s1_Intf),SztResetAllreset_allEnum);
   }
   else
   {
      szFillTknU8(&(ie->value.u.sztResetTyp.choice),SZ_PARTIAL_RESET);
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"lstCnt",&numComp);
#endif
      szFillTknU16(&(ie->value.u.sztResetTyp.val.partOfS1_Intf.noComp), numComp);

      /* Allocate memory */
      if (cmGetMem(szRstPdu, (numComp * sizeof(SztProtIE_SingleCont_UE_assocLogS1_ConItemRes)),
          (Ptr *)&(ie->value.u.sztResetTyp.val.partOfS1_Intf.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillReset: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }  

      enbId = 0;
      mmeId = 0;

      for(i = 1; i<= numComp; i++)
      {
         sprintf(enb,"enbId%d",i);
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,enb,&enbId);
#endif
         sprintf(mme,"mmeId%d",i);
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,mme,&mmeId);
#endif
         ie1 = &(ie->value.u.sztResetTyp.val.partOfS1_Intf.member[i - 1]);

         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->id),SZT_ELM_ID_UE_ASSOC_LOG_S1_CON_ITM);
         szFillTknU32(&(ie1->criticality),SztCriticalityignoreEnum);
         szFillTknU8(&(ie1->value.u.sztUE_assocLogS1_ConItem.pres),PRSNT_NODEF);

         if(mmeId != 0)
         {
            szFillTknU32(&(ie1->value.u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID),
                                           mmeId);
         }
         else
         {
            ie1->value.u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID.pres = NOTPRSNT;
         }
         if(enbId != 0)
         {
            szFillTknU32(&(ie1->value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID),
                                           enbId);
         }
         else
         {
            ie1->value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID.pres = NOTPRSNT;
         }

                    
         ie1->value.u.sztUE_assocLogS1_ConItem.iE_Extns.noComp.pres = FALSE;
   
         enbId = 0;
         mmeId = 0;
      }
   }

   *pdu = szRstPdu; 

   RETVALUE(ROK);

} /* End of szAcUtlSztFillReset */

/*
*
*       Fun:   szAcUtlSztFillResetAck
*
*       Desc:  Call handler to fill reset Ack message
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
PUBLIC S16 szAcUtlSztFillResetAck
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillResetAck(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillResetAck
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillResetAck(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *rstAckPdu = NULLP;
   S16        numCon;
   S16        idx;
   S16        ret;
   Mem        mem; 
   SztProtIE_Field_ResetAckgIEs *ie;
   SztProtIE_SingleCont_UE_assocLogS1_ConItemResAck *ie1;
   SztResetTyp rstIe;

   TRC2(szAcUtlSztFillResetAck);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&rstAckPdu);

   cmMemset((U8 *)&(rstAckPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(rstAckPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(rstAckPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(rstAckPdu->pdu.val.successfulOutcome.procedureCode), Sztid_Reset);
   szFillTknU32(&(rstAckPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);
   szFillTknU8(&(rstAckPdu->pdu.val.successfulOutcome.value.u.sztResetAckg.pres), PRSNT_NODEF);

   rstIe.choice.pres = PRSNT_NODEF;
   rstIe.choice.val  = SZT_PARTIAL_RESET;
   rstIe.val.partOfS1_Intf.noComp.val = 2;

   /* Partial reset */
   if(rstIe.choice.val == SZT_PARTIAL_RESET)
   {
      szFillTknU16(&(rstAckPdu->pdu.val.successfulOutcome.value.u.sztResetAckg.protocolIEs.noComp), 1);

      if ((cmGetMem(rstAckPdu, sizeof(SztProtIE_Field_ResetAckgIEs), 
                    (Ptr *)&rstAckPdu->pdu.val.successfulOutcome.value.u.sztResetAckg.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillResetAck: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      ie = rstAckPdu->pdu.val.successfulOutcome.value.u.sztResetAckg.protocolIEs.member;
   
      /* Fill IE container */
      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_UE_assocLogS1_ConLstResAck);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU16(&(ie->value.u.sztUE_assocLogS1_ConLstResAck.noComp), 2);

      numCon = rstIe.val.partOfS1_Intf.noComp.val;

      if ((cmGetMem(rstAckPdu, numCon * sizeof(SztProtIE_SingleCont_UE_assocLogS1_ConItemResAck), \
                    (Ptr *)&ie->value.u.sztUE_assocLogS1_ConLstResAck.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillResetAck: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      for(idx = 0; idx < numCon; idx++)
      {
         ie1 = &ie->value.u.sztUE_assocLogS1_ConLstResAck.member[idx];

         szFillTknU8(&(ie1->pres),PRSNT_NODEF);
         szFillTknU32(&(ie1->id), Sztid_UE_assocLogS1_ConItem);
         szFillTknU32(&(ie1->criticality), SztCriticalityignoreEnum);
         szFillTknU8(&(ie1->value.u.sztUE_assocLogS1_ConItem.pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->value.u.sztUE_assocLogS1_ConItem.mME_UE_S1AP_ID), idx);
         szFillTknU32(&(ie1->value.u.sztUE_assocLogS1_ConItem.eNB_UE_S1AP_ID), idx);
         ie1->value.u.sztUE_assocLogS1_ConItem.iE_Extns.noComp.pres = NOTPRSNT;
      }
   }
   else 
   {
      rstAckPdu->pdu.val.successfulOutcome.value.u.sztResetAckg.protocolIEs.noComp.pres = NOTPRSNT;
   }

   *pdu = rstAckPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillPaging_r9 
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
PUBLIC S16 szAcUtlSztFillPaging_r9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillPaging_r9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillPaging_r9
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillPaging_r9(pdu)
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

   TRC2(szAcUtlSztFillPaging_r9);

   mem.region = 0;
   mem.pool   = 0;

   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem,
                     (Ptr *)&szPagingPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPaging_r9: cmAllocEvnt failed,line %d\n",__LINE__));
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

   if(critBug)
   {
      numComp++;
   }

   szFillTknU16(&(szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.noComp), numComp);

   if ((cmGetMem(szPagingPdu, (numComp * sizeof(SztProtIE_Field_PagIEs)),
       (Ptr *)&szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPaging_r9: cmGetMem failed, line %d\n",__LINE__));
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
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPaging_r9: cmGetMem failed, line %d\n",__LINE__));
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

   if(critBug)
   {
      ie = &szPagingPdu->pdu.val.initiatingMsg.value.u.sztPag.protocolIEs.member[5];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_Crit_Tst1);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

      len = 10;
      szFillTknBStr32(&(ie->value.u.sztUEIdentityIdxValue), len, 100);
   }
   *pdu = szPagingPdu;

   RETVALUE(ROK);

} /* End of szAcUtlSztFillPaging_r9 */

/*
*
*       Fun:   szAcUtlSztFillUECntxtModRqst 
*
*       Desc:  Call handler to fill UE context modification
               request message
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
PUBLIC S16 szAcUtlSztFillUECntxtModRqst
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUECntxtModRqst(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUECntxtModRqst
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUECntxtModRqst(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu    *ueCntxtModRqstPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U8         secKeyVal[256]; 
   U32        idx = 0;
   U16        len;
   U32        mmeId;
   U32        enbId;
#ifndef SZ_ENC_DEC
   ProcId  procId = 0;
   UConnId suConnId = 0;
#endif
   SztProtIE_Field_UECntxtModificationRqstIEs *ie;

   U32      buggy = 0;
   U32      critBug = 0;
  
   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&ueCntxtModRqstPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUECntxtModRqst: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }


   cmMemset((U8 *)&(ueCntxtModRqstPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(ueCntxtModRqstPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(ueCntxtModRqstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(ueCntxtModRqstPdu->pdu.val.initiatingMsg.procedureCode), Sztid_UECntxtModification);
   szFillTknU32(&(ueCntxtModRqstPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"critBug",&(critBug));
#endif
   {
      numComp = 3;

      if(critBug)
      {
         numComp++;
      }
      szFillTknU8(&(ueCntxtModRqstPdu->pdu.val.initiatingMsg.value.u.sztUECntxtModificationRqst.pres), PRSNT_NODEF);
      szFillTknU16(&(ueCntxtModRqstPdu->pdu.val.initiatingMsg.value.u.sztUECntxtModificationRqst.protocolIEs.noComp), numComp);

      if ((cmGetMem(ueCntxtModRqstPdu, (numComp * sizeof(SztProtIE_Field_UECntxtModificationRqstIEs)), 
             (Ptr *)&ueCntxtModRqstPdu->pdu.val.initiatingMsg.value.u.sztUECntxtModificationRqst.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUECntxtModRqst: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {
         /* Get enbId and mmeId */
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"bug",&(buggy));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
         enbId = szacPduInfo[procId][suConnId].enbId;
         mmeId = szacPduInfo[procId][suConnId].mmeId;

         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#else
         enbId = 0;
         mmeId = 0;
#endif   /* SZ_ENC_DEC */
         ie = &ueCntxtModRqstPdu->pdu.val.initiatingMsg.value.u.sztUECntxtModificationRqst.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         if(!buggy)
         {

            ie = &ueCntxtModRqstPdu->pdu.val.initiatingMsg.value.u.sztUECntxtModificationRqst.protocolIEs.member[1];

#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
#endif
            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

            ie = &ueCntxtModRqstPdu->pdu.val.initiatingMsg.value.u.sztUECntxtModificationRqst.protocolIEs.member[2];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_SecurKey);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            cmMemset(secKeyVal,0,sizeof(secKeyVal));
            for (idx = 0; idx < 256; idx++)
               secKeyVal[idx] = 0xFF;
            len = 256;
            szFillTknStrOSXL(&(ie->value.u.sztSecurKey), len, secKeyVal, &ueCntxtModRqstPdu);
         }
         else
         {

            ie = &ueCntxtModRqstPdu->pdu.val.initiatingMsg.value.u.sztUECntxtModificationRqst.protocolIEs.member[2];

#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
#endif
            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

            ie = &ueCntxtModRqstPdu->pdu.val.initiatingMsg.value.u.sztUECntxtModificationRqst.protocolIEs.member[1];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_SecurKey);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            cmMemset(secKeyVal,0,sizeof(secKeyVal));
            for (idx = 0; idx < 256; idx++)
               secKeyVal[idx] = 0xFF;
            len = 256;
            szFillTknStrOSXL(&(ie->value.u.sztSecurKey), len, secKeyVal, &ueCntxtModRqstPdu);
         }
      }
   }

   if(critBug)
   {
      ie = &ueCntxtModRqstPdu->pdu.val.initiatingMsg.value.u.sztUECntxtModificationRqst.protocolIEs.member[3];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);
   }

   *pdu = ueCntxtModRqstPdu;
   
   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillUECntxtModResp 
*
*       Desc:  Call handler to fill UE context modification
               response message
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
PUBLIC S16 szAcUtlSztFillUECntxtModResp
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUECntxtModResp(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUECntxtModResp
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUECntxtModResp(pdu)
S1apPdu      **pdu;
#endif
#endif   /*SZ_ENC_DEC */
{
   S1apPdu   *ueCntxtModRespPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        mmeId = 0;
   U32        enbId = 0;
#ifndef SZ_ENC_DEC
   ProcId  procId = 0;
   UConnId suConnId = 0;
#endif
   SztProtIE_Field_UECntxtModificationRespIEs *ie;

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&ueCntxtModRespPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUECntxtModResp: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }


   cmMemset((U8 *)&(ueCntxtModRespPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(ueCntxtModRespPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(ueCntxtModRespPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(ueCntxtModRespPdu->pdu.val.successfulOutcome.procedureCode), Sztid_UECntxtModification);
   szFillTknU32(&(ueCntxtModRespPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 2;
      szFillTknU8(&(ueCntxtModRespPdu->pdu.val.successfulOutcome.value.u.sztUECntxtModificationResp.pres), PRSNT_NODEF);
      szFillTknU16(&(ueCntxtModRespPdu->pdu.val.successfulOutcome.value.u.sztUECntxtModificationResp.protocolIEs.noComp), numComp);

      if ((cmGetMem(ueCntxtModRespPdu, (numComp * sizeof(SztProtIE_Field_UECntxtModificationRespIEs)), 
             (Ptr *)&ueCntxtModRespPdu->pdu.val.successfulOutcome.value.u.sztUECntxtModificationResp.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUECntxtModResp: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {
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
         ie = &ueCntxtModRespPdu->pdu.val.successfulOutcome.value.u.sztUECntxtModificationResp.protocolIEs.member[0];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &ueCntxtModRespPdu->pdu.val.successfulOutcome.value.u.sztUECntxtModificationResp.protocolIEs.member[1];

#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
#endif
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);
      }
   }

   *pdu = ueCntxtModRespPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillUeCxtModFail 
*
*       Desc:  Call handler to fill UE context modification
*              Failure message.
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
PUBLIC S16 szAcUtlSztFillUeCxtModFail
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUeCxtModFail(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUeCxtModFail
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUeCxtModFail(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu *szUeCxtModFailPdu = NULLP;
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
#endif   /* SZ_ENC_DEC */
   SztProtIE_Field_UECntxtModificationFailIEs *ie;

   TRC2(szAcUtlSztFillUeCxtModFail);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szUeCxtModFailPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUeCxtModFail: cmAllocEvnt failed, line%d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szUeCxtModFailPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szUeCxtModFailPdu->pdu.choice), SZT_TRGR_UNSUCCESS_OUTCOME);
   szFillTknU8(&(szUeCxtModFailPdu->pdu.val.unsuccessfulOutcome.pres),PRSNT_NODEF)
;
   szFillTknU32(&(szUeCxtModFailPdu->pdu.val.unsuccessfulOutcome.procedureCode),Sztid_UECntxtModification);
   szFillTknU32(&(szUeCxtModFailPdu->pdu.val.unsuccessfulOutcome.criticality),SztCriticalityrejectEnum);
   szFillTknU8(&(szUeCxtModFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.pres),PRSNT_NODEF);

   /* Filling 3 mandatory header */

   numComp = 3;
   szFillTknU16(&(szUeCxtModFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.protocolIEs.noComp),numComp);

   if ((cmGetMem(szUeCxtModFailPdu, numComp*sizeof(SztProtIE_Field_UECntxtModificationFailIEs),(Ptr*)&szUeCxtModFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUeCxtModFail: cmGetMem failed, line %d\n",__LINE__));
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
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#else
   enbId = 0;
   mmeId = 0;
#endif   /* SZ_ENC_DEC */

   /* IE1 - Filling MME ID */
   ie = &szUeCxtModFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.protocolIEs.member[0];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

   /* IE2 - Filling ENB ID */
   ie = &szUeCxtModFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.protocolIEs.member[1];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
   szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
   szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

   /* IE3 - Filling cause */
   ie = &szUeCxtModFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztUECntxtModificationFail.protocolIEs.member[2];

   szFillTknU8(&(ie->pres),PRSNT_NODEF);
   szFillTknU32(&(ie->id),Sztid_Cause);
   szFillTknU32(&(ie->criticality),SztCriticalityignoreEnum);
   choice = 0;
   cause = 0;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"choice", &(choice));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
   szFillTknU8(&(ie->value.u.sztCause.choice),choice);
   szFillTknU32(&(ie->value.u.sztCause.val.radioNw),cause);

   *pdu = szUeCxtModFailPdu; 

   RETVALUE(ROK);

} /* End of szAcUtlSztFillUeCxtModFail */

/*
*
*       Fun:   szAcUtlSztFillErrInd 
*
*       Desc:  Call handler to fill Error indication
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
PUBLIC S16 szAcUtlSztFillErrInd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillErrInd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillErrInd
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillErrInd(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu *szErrIndPdu = NULLP;
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
   SztProtIE_Field_ErrIndIEs *ie;

   TRC2(szAcUtlSztFillErrInd);

   mem.region = 0;
   mem.pool   = 0;

   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem,
                     (Ptr *)&szErrIndPdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillErrInd: cmAllocEvnt failed,line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(szErrIndPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(szErrIndPdu->pdu.choice), SZT_TRGR_INTI_MSG);
   szFillTknU8(&(szErrIndPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(szErrIndPdu->pdu.val.initiatingMsg.procedureCode),
                  Sztid_ErrInd);
   szFillTknU32(&(szErrIndPdu->pdu.val.initiatingMsg.criticality),
                  SztCriticalityignoreEnum);

   /* Filling 3 optional headers */

   /* Get enbId and mmeId */
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
   enbId = szacPduInfo[procId][suConnId].enbId;
   mmeId = szacPduInfo[procId][suConnId].mmeId;

   /* Read enbId and mmeId from xml */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#else
   mmeId = 0;
   enbId = 0;
#endif   /* SZ_ENC_DEC */
   szFillTknU8(&(szErrIndPdu->pdu.val.initiatingMsg.value.u.sztErrInd.pres), PRSNT_NODEF);

   numComp = 3;
   szFillTknU16(&(szErrIndPdu->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.noComp), numComp);

   if ((cmGetMem(szErrIndPdu, (numComp * sizeof(SztProtIE_Field_ErrIndIEs)),
       (Ptr *)&szErrIndPdu->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillErrInd: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling  MME ID */
   ie = &szErrIndPdu->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member[0];

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#endif
   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);   
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);   
   szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);  

   /* IE2 - Filling ENB ID */
   ie = &szErrIndPdu->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member[1];

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
#endif
   szFillTknU8(&(ie->pres), PRSNT_NODEF);  
   szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);   
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum); 
   szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);                        

   /* IE3 - Filling cause */
   ie = &szErrIndPdu->pdu.val.initiatingMsg.value.u.sztErrInd.protocolIEs.member[2];

   szFillTknU8(&(ie->pres), PRSNT_NODEF);
   szFillTknU32(&(ie->id), Sztid_Cause);
   szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
   choice = 0;
   cause = 0;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
   szFillTknU8(&(ie->value.u.sztCause.choice),choice);
   szFillTknU32(&(ie->value.u.sztCause.val.radioNw),cause);

   *pdu = szErrIndPdu; 

   RETVALUE(ROK);

} /* End of szAcUtlSztFillErrInd */


/*
*
*       Fun:   szAcUtlSztFillE_RABSetupRqst_r9 
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
PUBLIC S16 szAcUtlSztFillE_RABSetupRqst_r9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABSetupRqst_r9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillE_RABSetupRqst_r9
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABSetupRqst_r9(pdu)
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
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABSetupRqst_r9: cmGetMem failed, line %d\n",__LINE__));
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
            CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABSetupRqst_r9: cmGetMem failed, line %d\n",__LINE__));
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

            ie1->value.u.sztE_RABToBeSetupItemBrSUReq.iE_Extns.noComp.pres = NOTPRSNT;
         }
      }
   }

   *pdu = eRABSetupRqstPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillE_RABSetupResp 
*
*       Desc:  Call handler to fill E-RAB Setup response
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
PUBLIC S16 szAcUtlSztFillE_RABSetupResp
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABSetupResp(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillE_RABSetupResp
(
S1apPdu   **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABSetupResp(pdu)
S1apPdu   **pdu;
#endif
#endif
{
   S1apPdu   *eRABSetupRespPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   U8         choice;
   U32        cause;
   U32        hndoverTrgd = FALSE;
   SztProtIE_Field_E_RABSetupRespIEs *ie;
   SztCriticalityDiag_IE_Item *ie1;
   SztProtIE_SingleCont_E_RABItemIEs *ie2;

   TRC2(szAcUtlSztFillE_RABSetupResp);
 
   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eRABSetupRespPdu);

   cmMemset((U8 *)&(eRABSetupRespPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(eRABSetupRespPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(eRABSetupRespPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(eRABSetupRespPdu->pdu.val.successfulOutcome.procedureCode), Sztid_E_RABSetup);
   szFillTknU32(&(eRABSetupRespPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;

#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"handoverTrgd",&(hndoverTrgd));
#endif
      if(hndoverTrgd == TRUE)
      {
         numComp++;
      }

      szFillTknU8(&(eRABSetupRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABSetupResp.pres), PRSNT_NODEF);
      szFillTknU16(&(eRABSetupRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABSetupResp.protocolIEs.noComp), numComp);

      if ((cmGetMem(eRABSetupRespPdu, (numComp * sizeof(SztProtIE_Field_E_RABSetupRespIEs)), 
             (Ptr *)&eRABSetupRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABSetupResp.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABSetupResp: cmGetMem failed, line %d\n",__LINE__));
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
#endif   /* SZ_ENC_DEC */

         ie = &eRABSetupRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABSetupResp.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &eRABSetupRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABSetupResp.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);
     
         ie = &eRABSetupRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABSetupResp.protocolIEs.member[2];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_CriticalityDiag);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);
         szFillTknU32(&(ie->value.u.sztCriticalityDiag.procedureCode), Sztid_E_RABSetup);
         szFillTknU32(&(ie->value.u.sztCriticalityDiag.triggeringMsg), SztTrgMsgsuccessful_outcomeEnum);
         szFillTknU32(&(ie->value.u.sztCriticalityDiag.procedureCriticality), SztCriticalityignoreEnum);

       numComp = 1;
       szFillTknU16(&(ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp), numComp);

       if ((cmGetMem(eRABSetupRespPdu, (numComp * sizeof(SztCriticalityDiag_IE_Item)), 
                 (Ptr *)&ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member)) !=ROK)
       {
#ifndef SZ_ENC_DEC
            CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABSetupResp: cmGetMem failed, line %d\n",__LINE__));
#endif
            RETVALUE(RFAILED);
       }

         ie1 = &ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.member[0];
         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->iECriticality), SztTrgMsgsuccessful_outcomeEnum);
         szFillTknU32(&(ie1->iE_ID), Sztid_E_RABSetup);
         szFillTknU32(&(ie1->typeOfErr), SztTypOfErrmissingEnum);
         ie1->iE_Extns.noComp.pres = NOTPRSNT;

         ie->value.u.sztCriticalityDiag.iE_Extns.noComp.pres = NOTPRSNT; 

         if(hndoverTrgd == TRUE)
         {
            ie = &eRABSetupRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABSetupResp.protocolIEs.member[3];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_E_RABFailedToSetupLstBrSURes);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            numComp = 1;
          szFillTknU16(&(ie->value.u.sztE_RABLst.noComp), numComp);

            if (cmGetMem(eRABSetupRespPdu, 
                          (numComp * sizeof(SztProtIE_SingleCont_E_RABItemIEs)), 
                          (Ptr *)&(ie->value.u.sztE_RABLst.member)) !=ROK)
            {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABMdfyResp: cmGetMem failed, line %d\n",__LINE__));
#endif
               RETVALUE(RFAILED);
            }
           
            ie2 = &(ie->value.u.sztE_RABLst.member[0]);
         
            szFillTknU8(&(ie2->pres), PRSNT_NODEF);
            szFillTknU32(&(ie2->id), Sztid_E_RABItem);
            szFillTknU32(&(ie2->criticality), SztCriticalityrejectEnum);
            szFillTknU8(&(ie2->value.u.sztE_RABItem.pres), PRSNT_NODEF);
            szFillTknU32(&(ie2->value.u.sztE_RABItem.e_RAB_ID), 15);
            choice = CAUSE_RADIONW;
            cause = SztCauseRadioNwx2_handover_triggeredEnum; 
#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
            szFillTknU8(&(ie2->value.u.sztE_RABItem.cause.choice),choice);
            szFillTknU32(&(ie2->value.u.sztE_RABItem.cause.val.radioNw),cause);
            
         }
      }
   }

   *pdu = eRABSetupRespPdu;

   RETVALUE(ROK);
}


/*
*
*       Fun:   szAcUtlSztFillE_RABMdfyRqst 
*
*       Desc:  Call handler to fill E-RAB Modify request
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
PUBLIC S16 szAcUtlSztFillE_RABMdfyRqst
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABMdfyRqst(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillE_RABMdfyRqst
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABMdfyRqst(pdu)
S1apPdu    **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu   *eRABMdfyRqstPdu = NULLP;
   S16        numComp;
   S16        idx;
   S16        ret;
   Mem        mem; 
   U16        len;
   U8         bitrate[8];
   U8         nasPdu[10];
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif /* SZ_ENC_DEC */
   SztProtIE_Field_E_RABMdfyRqstIEs *ie;
   SztProtIE_SingleCont_E_RABToBeMdfdItemBrModReqIEs *ie1;

   TRC2(szAcUtlSztFillE_RABMdfyRqst);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eRABMdfyRqstPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABMdfyRqst: cmAllocEvnt failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }


   cmMemset((U8 *)&(eRABMdfyRqstPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(eRABMdfyRqstPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(eRABMdfyRqstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(eRABMdfyRqstPdu->pdu.val.initiatingMsg.procedureCode), Sztid_E_RABMdfy);
   szFillTknU32(&(eRABMdfyRqstPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;
      szFillTknU8(&(eRABMdfyRqstPdu->pdu.val.initiatingMsg.value.u.sztE_RABMdfyRqst.pres), PRSNT_NODEF);
      szFillTknU16(&(eRABMdfyRqstPdu->pdu.val.initiatingMsg.value.u.sztE_RABMdfyRqst.protocolIEs.noComp), numComp);

      if ((cmGetMem(eRABMdfyRqstPdu, (numComp * sizeof(SztProtIE_Field_E_RABMdfyRqstIEs)), 
             (Ptr *)&eRABMdfyRqstPdu->pdu.val.initiatingMsg.value.u.sztE_RABMdfyRqst.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABMdfyRqst: cmGetMem failed, line %d\n",__LINE__));
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

         ie = &eRABMdfyRqstPdu->pdu.val.initiatingMsg.value.u.sztE_RABMdfyRqst.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &eRABMdfyRqstPdu->pdu.val.initiatingMsg.value.u.sztE_RABMdfyRqst.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &eRABMdfyRqstPdu->pdu.val.initiatingMsg.value.u.sztE_RABMdfyRqst.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_E_RABToBeMdfdLstBrModReq);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         numComp = 1;
         szFillTknU16(&(ie->value.u.sztE_RABToBeMdfdLstBrModReq.noComp), numComp);

         if ((cmGetMem(eRABMdfyRqstPdu, (numComp * sizeof(SztProtIE_SingleCont_E_RABToBeMdfdItemBrModReqIEs)), \
                       (Ptr *)&ie->value.u.sztE_RABToBeMdfdLstBrModReq.member)) !=ROK)
         {
#ifndef SZ_ENC_DEC
            CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABMdfyRqst: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
            RETVALUE(RFAILED);
         }

       for(idx = 0; idx < numComp; idx++)
       {
          ie1 = &ie->value.u.sztE_RABToBeMdfdLstBrModReq.member[idx];

          szFillTknU8(&(ie1->pres),PRSNT_NODEF);
          szFillTknU32(&(ie1->id), Sztid_E_RABToBeMdfdItemBrModReq);
          szFillTknU32(&(ie1->criticality), SztCriticalityrejectEnum);

          szFillTknU8(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.pres), PRSNT_NODEF);
          szFillTknU32(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RAB_ID), 15);
          szFillTknU8(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.pres), PRSNT_NODEF);
          szFillTknU32(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.qCI), 100);
          szFillTknU8(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.allocationRetentionPriority.pres), PRSNT_NODEF);
          szFillTknU32(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.allocationRetentionPriority.priorityLvl), 10);
          szFillTknU32(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.allocationRetentionPriority.pre_emptionCapblty), SztPre_emptionCapbltymay_trigger_pre_emptionEnum);
          szFillTknU32(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.allocationRetentionPriority.pre_emptionVulnerability), SztPre_emptionVulnerabilitypre_emptableEnum);
          ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.allocationRetentionPriority.iE_Extns.noComp.pres = NOTPRSNT;
     
           szFillTknU8(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.gbrQosInform.pres), PRSNT_NODEF);
          cmMemset(bitrate, 0, sizeof(bitrate));
          strcpy((char *)bitrate, "11");
          len = 4;
          szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.gbrQosInform.e_RAB_MaxBitrateDL), len, bitrate, &eRABMdfyRqstPdu);
          szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.gbrQosInform.e_RAB_MaxBitrateUL), len, bitrate, &eRABMdfyRqstPdu);
          szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.gbrQosInform.e_RAB_GuaranteedBitrateDL), len, bitrate, &eRABMdfyRqstPdu);
          szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.gbrQosInform.e_RAB_GuaranteedBitrateUL), len, bitrate, &eRABMdfyRqstPdu);
          ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.gbrQosInform.iE_Extns.noComp.pres = NOTPRSNT;

          ie1->value.u.sztE_RABToBeMdfdItemBrModReq.e_RABLvlQoSParams.iE_Extns.noComp.pres = NOTPRSNT;
          
          cmMemset(nasPdu,0,sizeof(nasPdu));
          strcpy((char *)nasPdu,"111");
          len = 3;
#ifndef SZ_ENC_DEC
          cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"nasPduVal",&(nasPdu));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"nasPduLen",&(len));
#endif /* SZ_ENC_DEC */
          szFillTknStrOSXL(&(ie1->value.u.sztE_RABToBeMdfdItemBrModReq.nAS_PDU),len,nasPdu,&eRABMdfyRqstPdu);

          ie1->value.u.sztE_RABToBeMdfdItemBrModReq.iE_Extns.noComp.pres = NOTPRSNT;
       }
      }
   }

   *pdu = eRABMdfyRqstPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillE_RABMdfyResp 
*
*       Desc:  Call handler to fill E-RAB Modify response
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
PUBLIC S16 szAcUtlSztFillE_RABMdfyResp
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABMdfyResp(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillE_RABMdfyResp
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABMdfyResp(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *eRABMdfyRespPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U8         choice;
   U32        enbId;
   U32        mmeId;
   U32        cause;
   U32        hndoverTrgd = FALSE;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   SztProtIE_Field_E_RABMdfyRespIEs *ie;
   SztProtIE_SingleCont_E_RABItemIEs *ie1;

   TRC2(szAcUtlSztFillE_RABMdfyResp);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eRABMdfyRespPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABMdfyResp: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }


   cmMemset((U8 *)&(eRABMdfyRespPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(eRABMdfyRespPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(eRABMdfyRespPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(eRABMdfyRespPdu->pdu.val.successfulOutcome.procedureCode), Sztid_E_RABMdfy);
   szFillTknU32(&(eRABMdfyRespPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 2;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"handoverTrgd",&(hndoverTrgd));
#endif
      if(hndoverTrgd == TRUE)
      {
         numComp++;
      }

      szFillTknU8(&(eRABMdfyRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABMdfyResp.pres), PRSNT_NODEF);
      szFillTknU16(&(eRABMdfyRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABMdfyResp.protocolIEs.noComp), numComp);

      if ((cmGetMem(eRABMdfyRespPdu, (numComp * sizeof(SztProtIE_Field_E_RABMdfyRespIEs)), 
             (Ptr *)&eRABMdfyRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABMdfyResp.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABMdfyResp: cmGetMem failed, line %d\n",__LINE__));
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
         mmeId = 0;
         enbId = 0;
#endif   /* SZ_ENC_DEC */

         ie = &eRABMdfyRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABMdfyResp.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &eRABMdfyRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABMdfyResp.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);
          
        
         if(hndoverTrgd == TRUE)
         {
            ie = &eRABMdfyRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABMdfyResp.protocolIEs.member[2];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_E_RABFailedToMdfyLst);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            numComp = 1;
            szFillTknU16(&(ie->value.u.sztE_RABLst.noComp), numComp);

            if (cmGetMem(eRABMdfyRespPdu, (numComp * sizeof(SztProtIE_SingleCont_E_RABItemIEs)), 
                          (Ptr *)&(ie->value.u.sztE_RABLst.member)) !=ROK)
            {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABMdfyResp: cmGetMem failed, line %d\n",__LINE__));
#endif
               RETVALUE(RFAILED);
            }
           
            ie1 = &(ie->value.u.sztE_RABLst.member[0]);
         
            szFillTknU8(&(ie1->pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->id), Sztid_E_RABItem);
            szFillTknU32(&(ie1->criticality), SztCriticalityrejectEnum);
            szFillTknU8(&(ie1->value.u.sztE_RABItem.pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztE_RABItem.e_RAB_ID), 15);
            choice = CAUSE_RADIONW;
            cause = SztCauseRadioNwx2_handover_triggeredEnum; 
#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
            szFillTknU8(&(ie1->value.u.sztE_RABItem.cause.choice),choice);
            szFillTknU32(&(ie1->value.u.sztE_RABItem.cause.val.radioNw),cause);
            
         }
      }
   }

   *pdu = eRABMdfyRespPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillE_RABRlsCmmd 
*
*       Desc:  Call handler to fill E-RAB release command
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
PUBLIC S16 szAcUtlSztFillE_RABRlsCmmd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABRlsCmmd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillE_RABRlsCmmd
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABRlsCmmd(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */

{
   S1apPdu   *eRABRlsCmmdPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   U8         choice;
   U32        cause;
   SztProtIE_Field_E_RABRlsCmmdIEs *ie;
   SztProtIE_SingleCont_E_RABItemIEs *ie1;

   TRC2(szAcUtlSztFillE_RABRlsCmmd);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eRABRlsCmmdPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABRlsCmmd: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }


   cmMemset((U8 *)&(eRABRlsCmmdPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(eRABRlsCmmdPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(eRABRlsCmmdPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(eRABRlsCmmdPdu->pdu.val.initiatingMsg.procedureCode), Sztid_E_RABRls);
   szFillTknU32(&(eRABRlsCmmdPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;
      szFillTknU8(&(eRABRlsCmmdPdu->pdu.val.initiatingMsg.value.u.sztE_RABRlsCmmd.pres), PRSNT_NODEF);
      szFillTknU16(&(eRABRlsCmmdPdu->pdu.val.initiatingMsg.value.u.sztE_RABRlsCmmd.protocolIEs.noComp), numComp);

      if ((cmGetMem(eRABRlsCmmdPdu, (numComp * sizeof(SztProtIE_Field_E_RABRlsCmmdIEs)), 
             (Ptr *)&eRABRlsCmmdPdu->pdu.val.initiatingMsg.value.u.sztE_RABRlsCmmd.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABRlsCmmd: cmGetMem failed, line %d\n",__LINE__));
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
#endif   /* SZ_ENC_DEC */

         ie = &eRABRlsCmmdPdu->pdu.val.initiatingMsg.value.u.sztE_RABRlsCmmd.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &eRABRlsCmmdPdu->pdu.val.initiatingMsg.value.u.sztE_RABRlsCmmd.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &eRABRlsCmmdPdu->pdu.val.initiatingMsg.value.u.sztE_RABRlsCmmd.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_E_RABToBeRlsdLst);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         {
            numComp = 1;
            szFillTknU16(&(ie->value.u.sztE_RABLst.noComp), numComp);

            if (cmGetMem(eRABRlsCmmdPdu, (numComp * sizeof(SztProtIE_SingleCont_E_RABItemIEs)), 
                          (Ptr *)&(ie->value.u.sztE_RABLst.member)) !=ROK)
            {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABRlsCmmd: cmGetMem failed, line %d\n", __LINE__));
#endif
               RETVALUE(RFAILED);
            }
           
            ie1 = &(ie->value.u.sztE_RABLst.member[0]);
         
            szFillTknU8(&(ie1->pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->id), Sztid_E_RABItem);
            szFillTknU32(&(ie1->criticality), SztCriticalityignoreEnum);
            szFillTknU8(&(ie1->value.u.sztE_RABItem.pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztE_RABItem.e_RAB_ID), 15);
            choice = CAUSE_RADIONW;
            cause = SztCauseRadioNwx2_handover_triggeredEnum;

#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
            szFillTknU8(&(ie1->value.u.sztE_RABItem.cause.choice), choice);
            szFillTknU32(&(ie1->value.u.sztE_RABItem.cause.val.radioNw), cause);
            ie1->value.u.sztE_RABItem.iE_Extns.noComp.pres = NOTPRSNT;
         }
      }
   }

   *pdu = eRABRlsCmmdPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillE_RABRlsResp 
*
*       Desc:  Call handler to fill E-RAB release response
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
PUBLIC S16 szAcUtlSztFillE_RABRlsResp
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABRlsResp(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillE_RABRlsResp
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABRlsResp(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *eRABRlsRespPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   SztProtIE_Field_E_RABRlsRespIEs *ie;

   TRC2(szAcUtlSztFillE_RABRlsResp);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eRABRlsRespPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABRlsResp: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }


   cmMemset((U8 *)&(eRABRlsRespPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(eRABRlsRespPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(eRABRlsRespPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(eRABRlsRespPdu->pdu.val.successfulOutcome.procedureCode), Sztid_E_RABRls);
   szFillTknU32(&(eRABRlsRespPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 2;
      szFillTknU8(&(eRABRlsRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABRlsResp.pres), PRSNT_NODEF);
      szFillTknU16(&(eRABRlsRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABRlsResp.protocolIEs.noComp), numComp);

      if ((cmGetMem(eRABRlsRespPdu, (numComp * sizeof(SztProtIE_Field_E_RABRlsRespIEs)), 
             (Ptr *)&eRABRlsRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABRlsResp.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABRlsResp: cmGetMem failed, line %d\n",__LINE__));
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
         mmeId = 0;
         enbId = 0;
#endif   /* SZ_ENC_DEC */

         ie = &eRABRlsRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABRlsResp.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &eRABRlsRespPdu->pdu.val.successfulOutcome.value.u.sztE_RABRlsResp.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);
      }
   }

   *pdu = eRABRlsRespPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillE_RABRlsInd 
*
*       Desc:  Call handler to fill E-RAB release indication 
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
PUBLIC S16 szAcUtlSztFillE_RABRlsInd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABRlsInd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillE_RABRlsInd
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillE_RABRlsInd(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */

{
   S1apPdu   *eRABRlsIndPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   U8         choice;
   U32        cause;
   SztProtIE_Field_E_RABRlsIndIEs *ie;
   SztProtIE_SingleCont_E_RABItemIEs *ie1;

   TRC2(szAcUtlSztFillE_RABRlsInd);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eRABRlsIndPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABRlsInd: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }


   cmMemset((U8 *)&(eRABRlsIndPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(eRABRlsIndPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(eRABRlsIndPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(eRABRlsIndPdu->pdu.val.initiatingMsg.procedureCode), Sztid_E_RABRlsInd);
   szFillTknU32(&(eRABRlsIndPdu->pdu.val.initiatingMsg.criticality), SztCriticalityignoreEnum);

   {
      numComp = 3;
      szFillTknU8(&(eRABRlsIndPdu->pdu.val.initiatingMsg.value.u.sztE_RABRlsInd.pres), PRSNT_NODEF);
      szFillTknU16(&(eRABRlsIndPdu->pdu.val.initiatingMsg.value.u.sztE_RABRlsInd.protocolIEs.noComp), numComp);

      if ((cmGetMem(eRABRlsIndPdu, (numComp * sizeof(SztProtIE_Field_E_RABRlsIndIEs)), 
             (Ptr *)&eRABRlsIndPdu->pdu.val.initiatingMsg.value.u.sztE_RABRlsInd.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABRlsInd: cmGetMem failed, line %d\n",__LINE__));
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
#endif   /* SZ_ENC_DEC */

         ie = &eRABRlsIndPdu->pdu.val.initiatingMsg.value.u.sztE_RABRlsInd.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &eRABRlsIndPdu->pdu.val.initiatingMsg.value.u.sztE_RABRlsInd.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &eRABRlsIndPdu->pdu.val.initiatingMsg.value.u.sztE_RABRlsInd.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_E_RABRlsdLst);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         {
            numComp = 1;
            szFillTknU16(&(ie->value.u.sztE_RABLst.noComp), numComp);

            if (cmGetMem(eRABRlsIndPdu, (numComp * sizeof(SztProtIE_SingleCont_E_RABItemIEs)), 
                          (Ptr *)&(ie->value.u.sztE_RABLst.member)) !=ROK)
            {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillE_RABRlsInd: cmGetMem failed, line %d\n", __LINE__));
#endif
               RETVALUE(RFAILED);
            }
           
            ie1 = &(ie->value.u.sztE_RABLst.member[0]);
         
            szFillTknU8(&(ie1->pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->id), Sztid_E_RABItem);
            szFillTknU32(&(ie1->criticality), SztCriticalityignoreEnum);
            szFillTknU8(&(ie1->value.u.sztE_RABItem.pres), PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztE_RABItem.e_RAB_ID), 15);
            choice = CAUSE_RADIONW;
            cause = SztCauseRadioNwx2_handover_triggeredEnum;
#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
            szFillTknU8(&(ie1->value.u.sztE_RABItem.cause.choice), choice);
            szFillTknU32(&(ie1->value.u.sztE_RABItem.cause.val.radioNw), cause);
            ie1->value.u.sztE_RABItem.iE_Extns.noComp.pres = NOTPRSNT;
         }
      }
   }

   *pdu = eRABRlsIndPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillHovrReqd 
*
*       Desc:  Call handler to fill Handover Required message
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
PUBLIC S16 szAcUtlSztFillHovrReqd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrReqd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillHovrReqd
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrReqd(pdu)
S1apPdu    **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu   *hovrReqdPdu = NULLP;
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
   U8         pLMNId[10];
   U16        len;
   U8         tprntCont[10];
   SztProtIE_Field_HovrReqdIEs *ie;
   SztTgeteNB_ID *ie1;

   U16        buggy = 0;
   U32        critBug = 0;

   TRC2(szAcUtlSztFillHovrReqd);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&hovrReqdPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrReqd: cmAllocEvnt failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(hovrReqdPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(hovrReqdPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(hovrReqdPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(hovrReqdPdu->pdu.val.initiatingMsg.procedureCode), Sztid_HovrPrep);
   szFillTknU32(&(hovrReqdPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"critBug",&(critBug));
#endif /* SZ_ENC_DEC */

   numComp = 7;

   if(critBug)
   {
      numComp++;
   }
   szFillTknU8(&(hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.pres), PRSNT_NODEF);
   szFillTknU16(&(hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.protocolIEs.noComp), numComp);

   if ((cmGetMem(hovrReqdPdu, (numComp * sizeof(SztProtIE_Field_HovrReqdIEs)), 
               (Ptr *)&hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrReqd:: cmGetMem failed, line %d\n",__LINE__));
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
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"bug",&(buggy));
#else
      enbId = 0;
      mmeId = 0;
#endif /* SZ_ENC_DEC */
      ie = &hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.protocolIEs.member[0];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

      ie = &hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.protocolIEs.member[1];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

      ie = &hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.protocolIEs.member[2];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_HovrTyp);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztHovrTyp), SztHovrTypgerantolteEnum);

      ie = &hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.protocolIEs.member[3];

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

      ie = &hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.protocolIEs.member[4];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_TgetID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU8(&(ie->value.u.sztTgetID.choice), TGETID_TARGETENB_ID);

      ie1 = &(ie->value.u.sztTgetID.val.targeteNB_ID);
      szFillTknU8(&(ie1->pres), PRSNT_NODEF);

      szFillTknU8(&(ie1->global_ENB_ID.pres), PRSNT_NODEF);
      cmMemset(pLMNId, 0, sizeof(pLMNId));
      strcpy((char *)pLMNId, "111");
      len = 3;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif /* SZ_ENC_DEC */
      szFillTknStrOSXL(&(ie1->global_ENB_ID.pLMNidentity), len, pLMNId, &hovrReqdPdu);     
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
#endif /* SZ_ENC_DEC */
      szFillTknStrOSXL(&(ie1->selected_TAI.pLMNidentity), len, pLMNId, &hovrReqdPdu);     

      len = 2;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"tacLen", &(len));
#endif /* SZ_ENC_DEC */
      szFillTknStr4(&(ie1->selected_TAI.tAC), (U8)len, 1);
      ie1->selected_TAI.iE_Extns.noComp.pres = NOTPRSNT;
      if(!buggy)
      {
         ie = &hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.protocolIEs.member[5];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Src_ToTget_TprntCont);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         cmMemset(tprntCont, 0, sizeof(tprntCont));
         strcpy((char *)tprntCont,"111");
         len = 3;
         szFillTknStrOSXL(&(ie->value.u.sztSrc_ToTget_TprntCont), len, tprntCont, &hovrReqdPdu);

         ie = &hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.protocolIEs.member[6];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Src_ToTget_TprntCont_Secondary);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         cmMemset(tprntCont, 0, sizeof(tprntCont));
         strcpy((char *)tprntCont,"111");
         len = 3;
         szFillTknStrOSXL(&(ie->value.u.sztSrc_ToTget_TprntCont_Secondary), len, tprntCont, &hovrReqdPdu);
      }
      else
      {
         ie = &hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.protocolIEs.member[6];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Src_ToTget_TprntCont);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         cmMemset(tprntCont, 0, sizeof(tprntCont));
         strcpy((char *)tprntCont,"111");
         len = 3;
         szFillTknStrOSXL(&(ie->value.u.sztSrc_ToTget_TprntCont), len, tprntCont, &hovrReqdPdu);

         ie = &hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.protocolIEs.member[5];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Src_ToTget_TprntCont_Secondary);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         cmMemset(tprntCont, 0, sizeof(tprntCont));
         strcpy((char *)tprntCont,"111");
         len = 3;
         szFillTknStrOSXL(&(ie->value.u.sztSrc_ToTget_TprntCont_Secondary), len, tprntCont, &hovrReqdPdu);

      }
   }

   if(critBug)
   {
      ie = &hovrReqdPdu->pdu.val.initiatingMsg.value.u.sztHovrReqd.protocolIEs.member[7];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);
   }

   *pdu = hovrReqdPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillHovrCmmd 
*
*       Desc:  Call handler to fill Handover Command message
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
PUBLIC S16 szAcUtlSztFillHovrCmmd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrCmmd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillHovrCmmd
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrCmmd(pdu)
S1apPdu    **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu   *hovrCmmdPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif /* SZ_ENC_DEC */
   U16        len;
   U8         tprntCont[10];
   SztProtIE_Field_HovrCmmdIEs *ie;

   U16         buggy = 0;

   TRC2(szAcUtlSztFillHovrCmmd);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&hovrCmmdPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrCmmd: cmAllocEvnt failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(hovrCmmdPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(hovrCmmdPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(hovrCmmdPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(hovrCmmdPdu->pdu.val.successfulOutcome.procedureCode), Sztid_HovrPrep);
   szFillTknU32(&(hovrCmmdPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 4;
      szFillTknU8(&(hovrCmmdPdu->pdu.val.successfulOutcome.value.u.sztHovrCmmd.pres), PRSNT_NODEF);
      szFillTknU16(&(hovrCmmdPdu->pdu.val.successfulOutcome.value.u.sztHovrCmmd.protocolIEs.noComp), numComp);

      if ((cmGetMem(hovrCmmdPdu, (numComp * sizeof(SztProtIE_Field_HovrCmmdIEs)), 
             (Ptr *)&hovrCmmdPdu->pdu.val.successfulOutcome.value.u.sztHovrCmmd.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrCmmd:: cmGetMem failed, line %d\n",__LINE__));
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
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"bug",&(buggy));
#else
         enbId = 0;
         mmeId = 0;
#endif /* SZ_ENC_DEC */

         ie = &hovrCmmdPdu->pdu.val.successfulOutcome.value.u.sztHovrCmmd.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &hovrCmmdPdu->pdu.val.successfulOutcome.value.u.sztHovrCmmd.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         if(!buggy)
         {
            ie = &hovrCmmdPdu->pdu.val.successfulOutcome.value.u.sztHovrCmmd.protocolIEs.member[2];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_HovrTyp);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztHovrTyp), SztHovrTypgerantolteEnum);

            ie = &hovrCmmdPdu->pdu.val.successfulOutcome.value.u.sztHovrCmmd.protocolIEs.member[3];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_Tget_ToSrc_TprntCont);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            cmMemset(tprntCont, 0, sizeof(tprntCont));
            strcpy((char *)tprntCont,"111");
            len = 3;
            szFillTknStrOSXL(&(ie->value.u.sztTget_ToSrc_TprntCont), len, tprntCont, &hovrCmmdPdu);     
         }
         else
         {
            ie = &hovrCmmdPdu->pdu.val.successfulOutcome.value.u.sztHovrCmmd.protocolIEs.member[3];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_HovrTyp);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztHovrTyp), SztHovrTypgerantolteEnum);

            ie = &hovrCmmdPdu->pdu.val.successfulOutcome.value.u.sztHovrCmmd.protocolIEs.member[2];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_Tget_ToSrc_TprntCont);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            cmMemset(tprntCont, 0, sizeof(tprntCont));
            strcpy((char *)tprntCont,"111");
            len = 3;
            szFillTknStrOSXL(&(ie->value.u.sztTget_ToSrc_TprntCont), len, tprntCont, &hovrCmmdPdu);     
         }
      }
   }

   *pdu = hovrCmmdPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillHovrPrepFail 
*
*       Desc:  Call handler to fill Handover Preparation Failure message
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
PUBLIC S16 szAcUtlSztFillHovrPrepFail
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrPrepFail(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillHovrPrepFail
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrPrepFail(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *hovrPrepFailPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   U8         choice;
   U32        cause;
   SztProtIE_Field_HovrPrepFailIEs *ie;
   U32        buggy = 0;

   TRC2(szAcUtlSztFillHovrPrepFail);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&hovrPrepFailPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrPrepFail: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(hovrPrepFailPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(hovrPrepFailPdu->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&(hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.procedureCode), Sztid_HovrPrep);
   szFillTknU32(&(hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;
      szFillTknU8(&(hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrPrepFail.pres), PRSNT_NODEF);
      szFillTknU16(&(hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrPrepFail.protocolIEs.noComp), numComp);

      if ((cmGetMem(hovrPrepFailPdu, (numComp * sizeof(SztProtIE_Field_HovrPrepFailIEs)), 
             (Ptr *)&hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrPrepFail.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrPrepFail:: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"bug",&(buggy));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
         enbId = szacPduInfo[procId][suConnId].enbId;
         mmeId = szacPduInfo[procId][suConnId].mmeId;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#else
         mmeId = 0;
         enbId = 0;
#endif   /* SZ_ENC_DEC */

         if(!buggy)
         {
            ie = &hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrPrepFail.protocolIEs.member[0];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

            ie = &hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrPrepFail.protocolIEs.member[1];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);
         }
         else
         {
            ie = &hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrPrepFail.protocolIEs.member[1];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

            ie = &hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrPrepFail.protocolIEs.member[0];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
            szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);
         }

         ie = &hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrPrepFail.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Cause);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         choice = CAUSE_RADIONW;
         cause  = SztCauseRadioNwunspecifiedEnum;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
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
      }
   }

   *pdu = hovrPrepFailPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillHovrRqst_r9 
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
PUBLIC S16 szAcUtlSztFillHovrRqst_r9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrRqst_r9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillHovrRqst_r9
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrRqst_r9(pdu)
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

   U16 buggy = 0;
   U32 critBug = 0;

   TRC2(szAcUtlSztFillHovrRqst_r9);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&hovrRqstPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrRqst_r9: cmAllocEvnt failed, line %d\n",__LINE__));
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
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrRqst_r9:: cmGetMem failed, line %d\n",__LINE__));
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
               CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrRqst_r9:: cmGetMem failed, line %d\n",__LINE__));
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

/*            szFillTknBStr32(&(ie->value.u.sztSecurCntxt.nextHopParameter), len, 100);*/

            ie->value.u.sztSecurCntxt.iE_Extns.noComp.pres = NOTPRSNT;

         }
      }
   }
   if(critBug)
   {
      ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.sztHovrRqst.protocolIEs.member[8];

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
*       Fun:   szAcUtlSztFillHovrRqstAckg 
*
*       Desc:  Call handler to fill Handover Request Acknowledge message
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
PUBLIC S16 szAcUtlSztFillHovrRqstAckg
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrRqstAckg(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillHovrRqstAckg
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrRqstAckg(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *hovrRqstAckgPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId = 0;
   U32        mmeId = 0;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   U16        len;
   U8         tprntCont[10];
   U8         gTPId[10];
   U8         tptAddr[10];
   SztProtIE_Field_HovrRqstAckgIEs *ie;
   SztProtIE_SingleCont_E_RABAdmtdItemIEs *ie1;

   TRC2(szAcUtlSztFillHovrRqstAckg);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&hovrRqstAckgPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrRqstAckg: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(hovrRqstAckgPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(hovrRqstAckgPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(hovrRqstAckgPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(hovrRqstAckgPdu->pdu.val.successfulOutcome.procedureCode), Sztid_HovrResourceAllocn);
   szFillTknU32(&(hovrRqstAckgPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 4;
      szFillTknU8(&(hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztHovrRqstAckg.pres), PRSNT_NODEF);
      szFillTknU16(&(hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztHovrRqstAckg.protocolIEs.noComp), numComp);

      if ((cmGetMem(hovrRqstAckgPdu, (numComp * sizeof(SztProtIE_Field_HovrRqstAckgIEs)), 
             (Ptr *)&hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztHovrRqstAckg.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrRqstAckg:: cmGetMem failed, line %d\n",__LINE__));
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

         ie = &hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztHovrRqstAckg.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztHovrRqstAckg.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztHovrRqstAckg.protocolIEs.member[2];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_E_RABAdmtdLst);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

         numComp = 1;
         szFillTknU16(&(ie->value.u.sztE_RABAdmtdLst.noComp), numComp);

         if ((cmGetMem(hovrRqstAckgPdu, (numComp * sizeof(SztProtIE_SingleCont_E_RABAdmtdItemIEs)), 
                     (Ptr *)&ie->value.u.sztE_RABAdmtdLst.member)) !=ROK)
         {

#ifndef SZ_ENC_DEC
            CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrRqstAckg:: cmGetMem failed, line %d\n",__LINE__));
#endif
            RETVALUE(RFAILED);
         }

         ie1 = &ie->value.u.sztE_RABAdmtdLst.member[0];

         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->id), Sztid_E_RABAdmtdItem);
         szFillTknU32(&(ie1->criticality), SztCriticalityignoreEnum);
         szFillTknU8(&(ie1->value.u.sztE_RABAdmtdItem.pres), PRSNT_NODEF);
         szFillTknU32(&(ie1->value.u.sztE_RABAdmtdItem.e_RAB_ID), 15);
         cmMemset(tptAddr, 0, sizeof(tptAddr));
         strcpy((char *)tptAddr, "11");
         len = 2;
         szFillTknStrOSXL(&(ie1->value.u.sztE_RABAdmtdItem.transportLyrAddr), len, tptAddr, &hovrRqstAckgPdu);
         cmMemset(gTPId, 0, sizeof(gTPId));
         strcpy((char *)gTPId, "1111");
         len = 4;
         szFillTknStrOSXL(&(ie1->value.u.sztE_RABAdmtdItem.gTP_TEID), len, gTPId, &hovrRqstAckgPdu);

         ie1->value.u.sztE_RABAdmtdItem.iE_Extns.noComp.pres = NOTPRSNT;

         ie = &hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztHovrRqstAckg.protocolIEs.member[3];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Tget_ToSrc_TprntCont);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         cmMemset(tprntCont, 0, sizeof(tprntCont));
         strcpy((char *)tprntCont,"111");
         len = 3;
         szFillTknStrOSXL(&(ie->value.u.sztTget_ToSrc_TprntCont), len, tprntCont, &hovrRqstAckgPdu);     
      }
   }

   *pdu = hovrRqstAckgPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillHovrFail 
*
*       Desc:  Call handler to fill Handover Failure message
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
PUBLIC S16 szAcUtlSztFillHovrFail
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrFail(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillHovrFail
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrFail(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *hovrFailPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        mmeId = 0;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   U8         choice;
   U32        cause;
   SztProtIE_Field_HovrFailIEs *ie;

   TRC2(szAcUtlSztFillHovrFail);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&hovrFailPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrFail: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(hovrFailPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(hovrFailPdu->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&(hovrFailPdu->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(hovrFailPdu->pdu.val.unsuccessfulOutcome.procedureCode), Sztid_HovrResourceAllocn);
   szFillTknU32(&(hovrFailPdu->pdu.val.unsuccessfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 2;
      szFillTknU8(&(hovrFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrFail.pres), PRSNT_NODEF);
      szFillTknU16(&(hovrFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrFail.protocolIEs.noComp), numComp);

      if ((cmGetMem(hovrFailPdu, (numComp * sizeof(SztProtIE_Field_HovrFailIEs)), 
             (Ptr *)&hovrFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrFail.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrFail:: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
#if  (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS))
   procId   =  szAcGetProc(spCb, ENTSZ, CMXTA_INST_ID);
#endif /* (defined(SZAC_INTG_TST) || defined (SS_MULTIPLE_PROCS)) */
         mmeId = szacPduInfo[procId][suConnId].mmeId;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
#endif   /* SZ_ENC_DEC */
         ie = &hovrFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrFail.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &hovrFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztHovrFail.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Cause);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         choice = CAUSE_RADIONW;
         cause  = SztCauseRadioNwunspecifiedEnum;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
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
      }
   }

   *pdu = hovrFailPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillHovrNtfy 
*
*       Desc:  Call handler to fill Handover Notify message
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
PUBLIC S16 szAcUtlSztFillHovrNtfy
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrNtfy(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillHovrNtfy
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrNtfy(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *hovrNtfyPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId = 0;
   U32        mmeId = 0;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   U8         pLMNId[10];
   U16        len;
   SztProtIE_Field_HovrNtfyIEs *ie;

   TRC2(szAcUtlSztFillHovrNtfy);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&hovrNtfyPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrNtfy: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(hovrNtfyPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(hovrNtfyPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(hovrNtfyPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(hovrNtfyPdu->pdu.val.initiatingMsg.procedureCode), Sztid_HovrNotification);
   szFillTknU32(&(hovrNtfyPdu->pdu.val.initiatingMsg.criticality), SztCriticalityignoreEnum);

   {
      numComp = 4;
      szFillTknU8(&(hovrNtfyPdu->pdu.val.initiatingMsg.value.u.sztHovrNtfy.pres), PRSNT_NODEF);
      szFillTknU16(&(hovrNtfyPdu->pdu.val.initiatingMsg.value.u.sztHovrNtfy.protocolIEs.noComp), numComp);

      if ((cmGetMem(hovrNtfyPdu, (numComp * sizeof(SztProtIE_Field_HovrNtfyIEs)), 
             (Ptr *)&hovrNtfyPdu->pdu.val.initiatingMsg.value.u.sztHovrNtfy.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrNtfy:: cmGetMem failed, line %d\n",__LINE__));
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

         ie = &hovrNtfyPdu->pdu.val.initiatingMsg.value.u.sztHovrNtfy.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &hovrNtfyPdu->pdu.val.initiatingMsg.value.u.sztHovrNtfy.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &hovrNtfyPdu->pdu.val.initiatingMsg.value.u.sztHovrNtfy.protocolIEs.member[2];

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
         szFillTknStrOSXL(&(ie->value.u.sztEUTRAN_CGI.pLMNidentity), len, pLMNId, &hovrNtfyPdu);

         len = 28;
         szFillTknBStr32(&(ie->value.u.sztEUTRAN_CGI.cell_ID), len, 100);

         ie->value.u.sztEUTRAN_CGI.iE_Extns.noComp.pres = NOTPRSNT;

         ie = &hovrNtfyPdu->pdu.val.initiatingMsg.value.u.sztHovrNtfy.protocolIEs.member[3];
  
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
#endif
         szFillTknStrOSXL(&(ie->value.u.sztTAI.pLMNidentity), len, pLMNId, &hovrNtfyPdu);     

         len = 2;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tacLen", &(len));
#endif
         szFillTknStr4(&(ie->value.u.sztTAI.tAC), (U8)len, 1);

         ie->value.u.sztTAI.iE_Extns.noComp.pres = NOTPRSNT;
      }
   }

   *pdu = hovrNtfyPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillPathSwRqst_r9 
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
PUBLIC S16 szAcUtlSztFillPathSwRqst_r9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillPathSwRqst_r9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillPathSwRqst_r9
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillPathSwRqst_r9( pdu)
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
   U16        len;
   SztProtIE_Field_PathSwRqstIEs *ie;
   SztProtIE_SingleCont_E_RABToBeSwedDLItemIEs *ie1;

   U32      buggy = 0;
   U8       critBug = FALSE;

   TRC2(szAcUtlSztFillPathSwRqst_r9);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&pathSwRqstPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPathSwRqst_r9: cmAllocEvnt failed, line %d\n",__LINE__));
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
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPathSwRqst_r9:: cmGetMem failed, line %d\n",__LINE__));
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
            CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPathSwRqst_r9:: cmGetMem failed, line %d\n",__LINE__));
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
            ie = &pathSwRqstPdu->pdu.val.initiatingMsg.value.u.sztPathSwRqst.protocolIEs.member[6];
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
*       Fun:   szAcUtlSztFillPathSwRqstAckg 
*
*       Desc:  Call handler to fill Path Switch Request Acknowledge message
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
PUBLIC S16 szAcUtlSztFillPathSwRqstAckg
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillPathSwRqstAckg(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillPathSwRqstAckg
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillPathSwRqstAckg(pdu)
S1apPdu    **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu   *pathSwRqstAckgPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif /* SZ_ENC_DEC */
   U16        len;
   U8         secKeyVal[256]; 
   S16        idx;
   SztProtIE_Field_PathSwRqstAckgIEs *ie;

   TRC2(szAcUtlSztFillPathSwRqstAckg);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&pathSwRqstAckgPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPathSwRqstAckg: cmAllocEvnt failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(pathSwRqstAckgPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(pathSwRqstAckgPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(pathSwRqstAckgPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(pathSwRqstAckgPdu->pdu.val.successfulOutcome.procedureCode), Sztid_PathSwRqst);
   szFillTknU32(&(pathSwRqstAckgPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;
      szFillTknU8(&(pathSwRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztPathSwRqstAckg.pres), PRSNT_NODEF);
      szFillTknU16(&(pathSwRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztPathSwRqstAckg.protocolIEs.noComp), numComp);

      if ((cmGetMem(pathSwRqstAckgPdu, (numComp * sizeof(SztProtIE_Field_PathSwRqstAckgIEs)), 
             (Ptr *)&pathSwRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztPathSwRqstAckg.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPathSwRqstAckg:: cmGetMem failed, line %d\n",__LINE__));
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

         ie = &pathSwRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztPathSwRqstAckg.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &pathSwRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztPathSwRqstAckg.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &pathSwRqstAckgPdu->pdu.val.successfulOutcome.value.u.sztPathSwRqstAckg.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_SecurCntxt);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         szFillTknU8(&(ie->value.u.sztSecurCntxt.pres), PRSNT_NODEF);

         len = 3;

         cmMemset(secKeyVal, 0, sizeof(secKeyVal));
         for (idx = 0; idx < 256; idx++)
            secKeyVal[idx] = 0xFF;
         len = 256;
         szFillTknStrOSXL(&(ie->value.u.sztSecurCntxt.nextHopParameter), len, secKeyVal, &pathSwRqstAckgPdu);

         szFillTknU32(&(ie->value.u.sztSecurCntxt.nextHopChainingCount), 5);

         ie->value.u.sztSecurCntxt.iE_Extns.noComp.pres = NOTPRSNT;
      }
   }

   *pdu = pathSwRqstAckgPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillPathSwRqstFail 
*
*       Desc:  Call handler to fill Path Switch Request Failure message
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
PUBLIC S16 szAcUtlSztFillPathSwRqstFail
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillPathSwRqstFail(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillPathSwRqstFail
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillPathSwRqstFail(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *pathSwRqstFailPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   U8         choice;
   U32        cause;
   SztProtIE_Field_PathSwRqstFailIEs *ie;

   TRC2(szAcUtlSztFillPathSwRqstFail);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&pathSwRqstFailPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPathSwRqstFail: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(pathSwRqstFailPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(pathSwRqstFailPdu->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&(pathSwRqstFailPdu->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(pathSwRqstFailPdu->pdu.val.unsuccessfulOutcome.procedureCode), Sztid_PathSwRqst);
   szFillTknU32(&(pathSwRqstFailPdu->pdu.val.unsuccessfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;
      szFillTknU8(&(pathSwRqstFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztPathSwRqstFail.pres), PRSNT_NODEF);
      szFillTknU16(&(pathSwRqstFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztPathSwRqstFail.protocolIEs.noComp), numComp);

      if ((cmGetMem(pathSwRqstFailPdu, (numComp * sizeof(SztProtIE_Field_PathSwRqstFailIEs)), 
             (Ptr *)&pathSwRqstFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztPathSwRqstFail.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillPathSwRqstFail:: cmGetMem failed, line %d\n",__LINE__));
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

         ie = &pathSwRqstFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztPathSwRqstFail.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &pathSwRqstFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztPathSwRqstFail.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &pathSwRqstFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztPathSwRqstFail.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Cause);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         choice = CAUSE_RADIONW;
         cause  = SztCauseRadioNwunspecifiedEnum;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
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
      }
   }

   *pdu = pathSwRqstFailPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillHovrCancel 
*
*       Desc:  Call handler to fill Handover Cancel message
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
PUBLIC S16 szAcUtlSztFillHovrCancel
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrCancel(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillHovrCancel
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrCancel(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *hovrCancelPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   U8         choice;
   U32        cause;
   SztProtIE_Field_HovrCancelIEs *ie;

   TRC2(szAcUtlSztFillHovrCancel);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&hovrCancelPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrCancel: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(hovrCancelPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(hovrCancelPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(hovrCancelPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(hovrCancelPdu->pdu.val.initiatingMsg.procedureCode), Sztid_HovrCancel);
   szFillTknU32(&(hovrCancelPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;
      szFillTknU8(&(hovrCancelPdu->pdu.val.initiatingMsg.value.u.sztHovrCancel.pres), PRSNT_NODEF);
      szFillTknU16(&(hovrCancelPdu->pdu.val.initiatingMsg.value.u.sztHovrCancel.protocolIEs.noComp), numComp);

      if ((cmGetMem(hovrCancelPdu, (numComp * sizeof(SztProtIE_Field_HovrCancelIEs)), 
             (Ptr *)&hovrCancelPdu->pdu.val.initiatingMsg.value.u.sztHovrCancel.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrCancel:: cmGetMem failed, line %d\n",__LINE__));
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
         mmeId = 0;
         enbId = 0;
#endif   /* SZ_ENC_DEC */

         ie = &hovrCancelPdu->pdu.val.initiatingMsg.value.u.sztHovrCancel.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &hovrCancelPdu->pdu.val.initiatingMsg.value.u.sztHovrCancel.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &hovrCancelPdu->pdu.val.initiatingMsg.value.u.sztHovrCancel.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Cause);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         choice = CAUSE_RADIONW;
         cause  = SztCauseRadioNwunspecifiedEnum;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
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
      }
   }

   *pdu = hovrCancelPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillHovrCancelAckg 
*
*       Desc:  Call handler to fill Handover Cancel Acknowledge message
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
PUBLIC S16 szAcUtlSztFillHovrCancelAckg
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrCancelAckg(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillHovrCancelAckg
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillHovrCancelAckg(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *hovrCancelAckgPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   SztProtIE_Field_HovrCancelAckgIEs *ie;

   TRC2(szAcUtlSztFillHovrCancelAckg);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&hovrCancelAckgPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrCancelAckg: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(hovrCancelAckgPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(hovrCancelAckgPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(hovrCancelAckgPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(hovrCancelAckgPdu->pdu.val.successfulOutcome.procedureCode), Sztid_HovrCancel);
   szFillTknU32(&(hovrCancelAckgPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 2;
      szFillTknU8(&(hovrCancelAckgPdu->pdu.val.successfulOutcome.value.u.sztHovrCancelAckg.pres), PRSNT_NODEF);
      szFillTknU16(&(hovrCancelAckgPdu->pdu.val.successfulOutcome.value.u.sztHovrCancelAckg.protocolIEs.noComp), numComp);

      if ((cmGetMem(hovrCancelAckgPdu, (numComp * sizeof(SztProtIE_Field_HovrCancelAckgIEs)), 
             (Ptr *)&hovrCancelAckgPdu->pdu.val.successfulOutcome.value.u.sztHovrCancelAckg.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillHovrCancelAckg:: cmGetMem failed, line %d\n",__LINE__));
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
#endif   /* SZ_ENC_DEC */

         ie = &hovrCancelAckgPdu->pdu.val.successfulOutcome.value.u.sztHovrCancelAckg.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &hovrCancelAckgPdu->pdu.val.successfulOutcome.value.u.sztHovrCancelAckg.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);
      }
   }

   *pdu = hovrCancelAckgPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillENBStatusTfr 
*
*       Desc:  Call handler to fill ENB Status Transfer message
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
PUBLIC S16 szAcUtlSztFillENBStatusTfr
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBStatusTfr(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillENBStatusTfr
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBStatusTfr(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *eNBStatusTfrPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   U8         critBug = FALSE;

   SztProtIE_Field_ENBStatusTfrIEs *ie;
   SztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs *ie1;

   TRC2(szAcUtlSztFillENBStatusTfr);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eNBStatusTfrPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBStatusTfr: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"critBug",&(critBug));
#endif

   cmMemset((U8 *)&(eNBStatusTfrPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(eNBStatusTfrPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(eNBStatusTfrPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(eNBStatusTfrPdu->pdu.val.initiatingMsg.procedureCode), Sztid_eNBStatusTfr);
   szFillTknU32(&(eNBStatusTfrPdu->pdu.val.initiatingMsg.criticality), SztCriticalityignoreEnum);

   {
      numComp = 3;
      if(critBug)
      {
         numComp++;
      }

      szFillTknU8(&(eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztENBStatusTfr.pres), PRSNT_NODEF);
      szFillTknU16(&(eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztENBStatusTfr.protocolIEs.noComp), numComp);

      if ((cmGetMem(eNBStatusTfrPdu, (numComp * sizeof(SztProtIE_Field_ENBStatusTfrIEs)), 
             (Ptr *)&eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztENBStatusTfr.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBStatusTfr:: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

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
#endif   /* SZ_ENC_DEC */

      ie = &eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztENBStatusTfr.protocolIEs.member[0];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

      ie = &eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztENBStatusTfr.protocolIEs.member[1];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

      if(critBug)
      {
         ie = &eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztENBStatusTfr.protocolIEs.member[2];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztENBStatusTfr.protocolIEs.member[3];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_StatusTfr_TprntCont);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU8(&(ie->value.u.sztENB_StatusTfr_TprntCont.pres), PRSNT_NODEF);

         numComp =1;
         if ((cmGetMem(eNBStatusTfrPdu, (numComp * sizeof(SztBrs_SubjToStatusTfrLst)),
                     (Ptr *)&ie->value.u.sztENB_StatusTfr_TprntCont.bearers_SubjToStatusTfrLst.member)) !=ROK)
         {
#ifndef SZ_ENC_DEC
            CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBStatusTfr:: cmGetMem failed, line %d\n",__LINE__));
#endif
            RETVALUE(RFAILED);
         }
         szFillTknU16(&(ie->value.u.sztENB_StatusTfr_TprntCont.bearers_SubjToStatusTfrLst.noComp),numComp); 
         ie1= &ie->value.u.sztENB_StatusTfr_TprntCont.bearers_SubjToStatusTfrLst.member[0];

         szFillTknU8(&(ie1->pres),PRSNT_NODEF);
         szFillTknU32(&(ie1->id), Sztid_Brs_SubjToStatusTfr_Item);
         szFillTknU32(&(ie1->criticality),SztCriticalityrejectEnum);

         szFillTknU8(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.pres),PRSNT_NODEF);
         szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.e_RAB_ID), 15); 

         szFillTknU8(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.pres),PRSNT_NODEF);
         szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.pDCP_SN), 15);
         szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.hFN), 15);


         szFillTknU8(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.pres),PRSNT_NODEF);
         szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.pDCP_SN), 15);
         szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.hFN), 15);

         ie->value.u.sztENB_StatusTfr_TprntCont.iE_Extns.noComp.pres = NOTPRSNT;
      }
      else
      {

         ie = &eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztENBStatusTfr.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_StatusTfr_TprntCont);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU8(&(ie->value.u.sztENB_StatusTfr_TprntCont.pres), PRSNT_NODEF);

         numComp =1;
         if ((cmGetMem(eNBStatusTfrPdu, (numComp * sizeof(SztBrs_SubjToStatusTfrLst)),
                     (Ptr *)&ie->value.u.sztENB_StatusTfr_TprntCont.bearers_SubjToStatusTfrLst.member)) !=ROK)
         {
#ifndef SZ_ENC_DEC
            CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBStatusTfr:: cmGetMem failed, line %d\n",__LINE__));
#endif
            RETVALUE(RFAILED);
         }
         szFillTknU16(&(ie->value.u.sztENB_StatusTfr_TprntCont.bearers_SubjToStatusTfrLst.noComp),numComp); 
         ie1= &ie->value.u.sztENB_StatusTfr_TprntCont.bearers_SubjToStatusTfrLst.member[0];

         szFillTknU8(&(ie1->pres),PRSNT_NODEF);
         szFillTknU32(&(ie1->id), Sztid_Brs_SubjToStatusTfr_Item);
         szFillTknU32(&(ie1->criticality),SztCriticalityrejectEnum);

         szFillTknU8(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.pres),PRSNT_NODEF);
         szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.e_RAB_ID), 15); 

         szFillTknU8(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.pres),PRSNT_NODEF);
         szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.pDCP_SN), 15);
         szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.hFN), 15);


         szFillTknU8(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.pres),PRSNT_NODEF);
         szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.pDCP_SN), 15);
         szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.hFN), 15);

         ie->value.u.sztENB_StatusTfr_TprntCont.iE_Extns.noComp.pres = NOTPRSNT;
      }
   }

   *pdu = eNBStatusTfrPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillMMEStatusTfr 
*
*       Desc:  Call handler to fill MME Status Transfer message
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
PUBLIC S16 szAcUtlSztFillMMEStatusTfr
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillMMEStatusTfr(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillMMEStatusTfr
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillMMEStatusTfr(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *mMEStatusTfrPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   SztProtIE_Field_MMEStatusTfrIEs *ie;
   SztProtIE_SingleCont_Brs_SubjToStatusTfr_ItemIEs *ie1;
   U8        critBug = FALSE;

   TRC2(szAcUtlSztFillMMEStatusTfr);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&mMEStatusTfrPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillMMEStatusTfr: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(mMEStatusTfrPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(mMEStatusTfrPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(mMEStatusTfrPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(mMEStatusTfrPdu->pdu.val.initiatingMsg.procedureCode), Sztid_MMEStatusTfr);
   szFillTknU32(&(mMEStatusTfrPdu->pdu.val.initiatingMsg.criticality), SztCriticalityignoreEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"critBug",&(critBug));
#endif
   {
      numComp = 3;
      if(critBug)
      {
         numComp++;
      }
      szFillTknU8(&(mMEStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEStatusTfr.pres), PRSNT_NODEF);
      szFillTknU16(&(mMEStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEStatusTfr.protocolIEs.noComp), numComp);

      if ((cmGetMem(mMEStatusTfrPdu, (numComp * sizeof(SztProtIE_Field_MMEStatusTfrIEs)), 
             (Ptr *)&mMEStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEStatusTfr.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillMMEStatusTfr:: cmGetMem failed, line %d\n",__LINE__));
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
#endif   /* SZ_ENC_DEC */

         if(critBug)
         {
            ie = &mMEStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEStatusTfr.protocolIEs.member[0];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
            szFillTknU32(&(ie->criticality), SztCriticalitynotifyEnum);
            szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

            ie = &mMEStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEStatusTfr.protocolIEs.member[1];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

            ie = &mMEStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEStatusTfr.protocolIEs.member[2];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

            ie = &mMEStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEStatusTfr.protocolIEs.member[3];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_eNB_StatusTfr_TprntCont);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU8(&(ie->value.u.sztENB_StatusTfr_TprntCont.pres), PRSNT_NODEF);

            numComp =1;
            if ((cmGetMem(mMEStatusTfrPdu, (numComp * sizeof(SztBrs_SubjToStatusTfrLst)),
                        (Ptr *)&ie->value.u.sztENB_StatusTfr_TprntCont.bearers_SubjToStatusTfrLst.member)) !=ROK)
            {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBStatusTfr:: cmGetMem failed, line %d\n",__LINE__));
#endif
               RETVALUE(RFAILED);
            }
            szFillTknU16(&(ie->value.u.sztENB_StatusTfr_TprntCont.bearers_SubjToStatusTfrLst.noComp),numComp); 
            ie1= &ie->value.u.sztENB_StatusTfr_TprntCont.bearers_SubjToStatusTfrLst.member[0];

            szFillTknU8(&(ie1->pres),PRSNT_NODEF);
            szFillTknU32(&(ie1->id), Sztid_Brs_SubjToStatusTfr_Item);
            szFillTknU32(&(ie1->criticality),SztCriticalityrejectEnum);

            szFillTknU8(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.pres),PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.e_RAB_ID), 15); 

            szFillTknU8(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.pres),PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.pDCP_SN), 15);
            szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.hFN), 15);


            szFillTknU8(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.pres),PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.pDCP_SN), 15);
            szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.hFN), 15);

            ie->value.u.sztENB_StatusTfr_TprntCont.iE_Extns.noComp.pres = NOTPRSNT;
         }
         else
         {
            ie = &mMEStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEStatusTfr.protocolIEs.member[0];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

            ie = &mMEStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEStatusTfr.protocolIEs.member[1];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

            ie = &mMEStatusTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEStatusTfr.protocolIEs.member[2];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_eNB_StatusTfr_TprntCont);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU8(&(ie->value.u.sztENB_StatusTfr_TprntCont.pres), PRSNT_NODEF);

            numComp =1;
            if ((cmGetMem(mMEStatusTfrPdu, (numComp * sizeof(SztBrs_SubjToStatusTfrLst)),
                        (Ptr *)&ie->value.u.sztENB_StatusTfr_TprntCont.bearers_SubjToStatusTfrLst.member)) !=ROK)
            {
#ifndef SZ_ENC_DEC
               CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBStatusTfr:: cmGetMem failed, line %d\n",__LINE__));
#endif
               RETVALUE(RFAILED);
            }
            szFillTknU16(&(ie->value.u.sztENB_StatusTfr_TprntCont.bearers_SubjToStatusTfrLst.noComp),numComp); 
            ie1= &ie->value.u.sztENB_StatusTfr_TprntCont.bearers_SubjToStatusTfrLst.member[0];

            szFillTknU8(&(ie1->pres),PRSNT_NODEF);
            szFillTknU32(&(ie1->id), Sztid_Brs_SubjToStatusTfr_Item);
            szFillTknU32(&(ie1->criticality),SztCriticalityrejectEnum);

            szFillTknU8(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.pres),PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.e_RAB_ID), 15); 

            szFillTknU8(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.pres),PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.pDCP_SN), 15);
            szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.uL_COUNTvalue.hFN), 15);


            szFillTknU8(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.pres),PRSNT_NODEF);
            szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.pDCP_SN), 15);
            szFillTknU32(&(ie1->value.u.sztBrs_SubjToStatusTfr_Item.dL_COUNTvalue.hFN), 15);

            ie->value.u.sztENB_StatusTfr_TprntCont.iE_Extns.noComp.pres = NOTPRSNT;
         }
      }
   }

   *pdu = mMEStatusTfrPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillWriteReplaceWarningRqst 
*
*       Desc:  Call handler to fill Write Replace Warning Request message
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
PUBLIC S16 szAcUtlSztFillWriteReplaceWarningRqst
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillWriteReplaceWarningRqst(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillWriteReplaceWarningRqst
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillWriteReplaceWarningRqst(pdu)
S1apPdu    **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu   *writeReplaceWarningRqstPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        rPeriod;
   U32        nBroadcastRqst;
   U8         msgContents[8];
   U16        len;
   U8         critBug = FALSE;
   SztProtIE_Field_WriteReplaceWarningRqstIEs *ie;

   TRC2(szAcUtlSztFillWriteReplaceWarningRqst);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&writeReplaceWarningRqstPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillWriteReplaceWarningRqst: cmAllocEvnt failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(writeReplaceWarningRqstPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(writeReplaceWarningRqstPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.procedureCode), Sztid_WriteReplaceWarning);
   szFillTknU32(&(writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 6;
      
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"critBug",&(critBug));
#endif
      if(critBug)
      {
         numComp++;
      }
      
      szFillTknU8(&(writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.value.u.sztWriteReplaceWarningRqst.pres), PRSNT_NODEF);
      szFillTknU16(&(writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.value.u.sztWriteReplaceWarningRqst.protocolIEs.noComp), numComp);

      if ((cmGetMem(writeReplaceWarningRqstPdu, (numComp * sizeof(SztProtIE_Field_WriteReplaceWarningRqstIEs)), 
             (Ptr *)&writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.value.u.sztWriteReplaceWarningRqst.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillWriteReplaceWarningRqst:: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
         RETVALUE(RFAILED);
      }

      {
         numComp = 0;
         
         if( critBug )
         {
            ie = &writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.value.u.sztWriteReplaceWarningRqst.protocolIEs.member[numComp++];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_Crit_Tst2);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

            len = 16;
           szFillTknBStr32(&(ie->value.u.sztMsgIdentifier), len, 100);
         }   

         ie = &writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.value.u.sztWriteReplaceWarningRqst.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MsgIdentifier);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         len = 16;
        szFillTknBStr32(&(ie->value.u.sztMsgIdentifier), len, 100);

         ie = &writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.value.u.sztWriteReplaceWarningRqst.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_SerialNumber);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         len = 16;
         szFillTknBStr32(&(ie->value.u.sztSerialNumber), len, 100);

         ie = &writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.value.u.sztWriteReplaceWarningRqst.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_RepetitionPeriod);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         rPeriod = 4095;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"rPeriod", &(rPeriod));
#endif /* SZ_ENC_DEC */
         szFillTknU32(&(ie->value.u.sztRepetitionPeriod), rPeriod);

         ie = &writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.value.u.sztWriteReplaceWarningRqst.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_NumberofBroadcastRqst);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         nBroadcastRqst = 65535;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"nBroadcastRqst", &(nBroadcastRqst));
#endif /* SZ_ENC_DEC */
         szFillTknU32(&(ie->value.u.sztNumberofBroadcastRqst), nBroadcastRqst);

         ie = &writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.value.u.sztWriteReplaceWarningRqst.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_DataCodingScheme);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            
         len = 8;
         szFillTknBStr32(&(ie->value.u.sztDataCodingScheme), len, 100);
         
         ie = &writeReplaceWarningRqstPdu->pdu.val.initiatingMsg.value.u.sztWriteReplaceWarningRqst.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_WarningMsgContents);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         cmMemset(msgContents, 0, sizeof(msgContents));
         strcpy((char *)msgContents, "111");
         len = 3;
         szFillTknStrOSXL(&(ie->value.u.sztWarningMsgContents), len, msgContents, &writeReplaceWarningRqstPdu);

      }
   }

   *pdu = writeReplaceWarningRqstPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillWriteReplaceWarningResp 
*
*       Desc:  Call handler to fill Write Replace Warning Response message
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
PUBLIC S16 szAcUtlSztFillWriteReplaceWarningResp
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillWriteReplaceWarningResp(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillWriteReplaceWarningResp
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillWriteReplaceWarningResp(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *writeReplaceWarningRespPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U8         pLMNId[10];
   U16        len;
   SztProtIE_Field_WriteReplaceWarningRespIEs *ie;
   SztCellID_Broadcast_Item                   *ie1;

   TRC2(szAcUtlSztFillWriteReplaceWarningResp);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&writeReplaceWarningRespPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillWriteReplaceWarningResp: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(writeReplaceWarningRespPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(writeReplaceWarningRespPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(writeReplaceWarningRespPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(writeReplaceWarningRespPdu->pdu.val.successfulOutcome.procedureCode), Sztid_WriteReplaceWarning);
   szFillTknU32(&(writeReplaceWarningRespPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;
      szFillTknU8(&(writeReplaceWarningRespPdu->pdu.val.successfulOutcome.value.u.sztWriteReplaceWarningResp.pres), PRSNT_NODEF);
      szFillTknU16(&(writeReplaceWarningRespPdu->pdu.val.successfulOutcome.value.u.sztWriteReplaceWarningResp.protocolIEs.noComp), numComp);

      if ((cmGetMem(writeReplaceWarningRespPdu, (numComp * sizeof(SztProtIE_Field_WriteReplaceWarningRespIEs)), 
             (Ptr *)&writeReplaceWarningRespPdu->pdu.val.successfulOutcome.value.u.sztWriteReplaceWarningResp.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillWriteReplaceWarningResp:: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {
         ie = &writeReplaceWarningRespPdu->pdu.val.successfulOutcome.value.u.sztWriteReplaceWarningResp.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MsgIdentifier);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         len = 16;
         szFillTknBStr32(&(ie->value.u.sztMsgIdentifier), len, 100);

         ie = &writeReplaceWarningRespPdu->pdu.val.successfulOutcome.value.u.sztWriteReplaceWarningResp.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_SerialNumber);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         len = 16;
         szFillTknBStr32(&(ie->value.u.sztSerialNumber), len, 100);

         ie = &writeReplaceWarningRespPdu->pdu.val.successfulOutcome.value.u.sztWriteReplaceWarningResp.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_BroadcastCompletedAreaLst);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         szFillTknU8(&(ie->value.u.sztBroadcastCompletedAreaLst.choice), BROADCASTCOMPLETEDAREALST_CELLID_BROADCAST);

         numComp = 1;
         szFillTknU16(&(ie->value.u.sztBroadcastCompletedAreaLst.val.cellID_Broadcast.noComp), numComp);

         if ((cmGetMem(writeReplaceWarningRespPdu, (numComp * sizeof(SztCellID_Broadcast_Item)),
                    (Ptr *)&ie->value.u.sztBroadcastCompletedAreaLst.val.cellID_Broadcast.member)) !=ROK)
         {
#ifndef SZ_ENC_DEC
            CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillWriteReplaceWarningResp: cmGetMem failed, line %d\n",__LINE__));
#endif
            RETVALUE(RFAILED);
         }

         ie1 = &ie->value.u.sztBroadcastCompletedAreaLst.val.cellID_Broadcast.member[0];

         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU8(&(ie1->eCGI.pres), PRSNT_NODEF);
         cmMemset(pLMNId, 0, sizeof(pLMNId));
         strcpy((char *)pLMNId, "111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif
         szFillTknStrOSXL(&(ie1->eCGI.pLMNidentity), len, pLMNId, &writeReplaceWarningRespPdu);     

         len = 28;
         szFillTknBStr32(&(ie1->eCGI.cell_ID), len, 100);

         ie1->eCGI.iE_Extns.noComp.pres = NOTPRSNT;


      }
   }

   *pdu = writeReplaceWarningRespPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillENBDirectInformTfr 
*
*       Desc:  Call handler to fill ENB Direct Information Transfer message
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
PUBLIC S16 szAcUtlSztFillENBDirectInformTfr
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBDirectInformTfr(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillENBDirectInformTfr
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBDirectInformTfr(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *eNBDirectInformTfrPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U8         rIMInform[8];
   SztProtIE_Field_ENBDirectInformTfrIEs *ie;

   TRC2(szAcUtlSztFillENBDirectInformTfr);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eNBDirectInformTfrPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBDirectInformTfr: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(eNBDirectInformTfrPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(eNBDirectInformTfrPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(eNBDirectInformTfrPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(eNBDirectInformTfrPdu->pdu.val.initiatingMsg.procedureCode), Sztid_eNBDirectInformTfr);
   szFillTknU32(&(eNBDirectInformTfrPdu->pdu.val.initiatingMsg.criticality), SztCriticalityignoreEnum);

   {
      numComp = 1;
      szFillTknU8(&(eNBDirectInformTfrPdu->pdu.val.initiatingMsg.value.u.sztENBDirectInformTfr.pres), PRSNT_NODEF);
      szFillTknU16(&(eNBDirectInformTfrPdu->pdu.val.initiatingMsg.value.u.sztENBDirectInformTfr.protocolIEs.noComp), numComp);

      if ((cmGetMem(eNBDirectInformTfrPdu, (numComp * sizeof(SztProtIE_Field_ENBDirectInformTfrIEs)), 
             (Ptr *)&eNBDirectInformTfrPdu->pdu.val.initiatingMsg.value.u.sztENBDirectInformTfr.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBDirectInformTfr:: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {
         ie = &eNBDirectInformTfrPdu->pdu.val.initiatingMsg.value.u.sztENBDirectInformTfr.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Inter_SystemInformTfrTypEDT);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU8(&(ie->value.u.sztInter_SystemInformTfrTyp.choice), INTER_SYSTEMINFORMTFRTYP_RIMTFR);
         szFillTknU8(&(ie->value.u.sztInter_SystemInformTfrTyp.val.rIMTfr.pres), PRSNT_NODEF);
         strcpy((char *)rIMInform, "111");
         szFillTknStrOSXL(&(ie->value.u.sztInter_SystemInformTfrTyp.val.rIMTfr.rIMInform), 3, rIMInform, &eNBDirectInformTfrPdu);
         ie->value.u.sztInter_SystemInformTfrTyp.val.rIMTfr.rIMRoutingAddr.choice.pres = NOTPRSNT;

         ie->value.u.sztInter_SystemInformTfrTyp.val.rIMTfr.iE_Extns.noComp.pres = NOTPRSNT;
      }
   }

   *pdu = eNBDirectInformTfrPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillMMEDirectInformTfr 
*
*       Desc:  Call handler to fill MME Direct Information Transfer message
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
PUBLIC S16 szAcUtlSztFillMMEDirectInformTfr
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillMMEDirectInformTfr(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillMMEDirectInformTfr
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillMMEDirectInformTfr(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *mMEDirectInformTfrPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U8         rIMInform[8];
   SztProtIE_Field_MMEDirectInformTfrIEs *ie;

   TRC2(szAcUtlSztFillMMEDirectInformTfr);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&mMEDirectInformTfrPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillMMEDirectInformTfr: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(mMEDirectInformTfrPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(mMEDirectInformTfrPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(mMEDirectInformTfrPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(mMEDirectInformTfrPdu->pdu.val.initiatingMsg.procedureCode), Sztid_MMEDirectInformTfr);
   szFillTknU32(&(mMEDirectInformTfrPdu->pdu.val.initiatingMsg.criticality), SztCriticalityignoreEnum);

   {
      numComp = 1;

      szFillTknU8(&(mMEDirectInformTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEDirectInformTfr.pres), PRSNT_NODEF);
      szFillTknU16(&(mMEDirectInformTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEDirectInformTfr.protocolIEs.noComp), numComp);

      if ((cmGetMem(mMEDirectInformTfrPdu, (numComp * sizeof(SztProtIE_Field_MMEDirectInformTfrIEs)), 
             (Ptr *)&mMEDirectInformTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEDirectInformTfr.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillMMEDirectInformTfr:: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {
         numComp = 0;
         
         ie = &mMEDirectInformTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEDirectInformTfr.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Inter_SystemInformTfrTypMDT);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU8(&(ie->value.u.sztInter_SystemInformTfrTyp.choice), INTER_SYSTEMINFORMTFRTYP_RIMTFR);
         szFillTknU8(&(ie->value.u.sztInter_SystemInformTfrTyp.val.rIMTfr.pres), PRSNT_NODEF);
         strcpy((char *)rIMInform, "111");
         szFillTknStrOSXL(&(ie->value.u.sztInter_SystemInformTfrTyp.val.rIMTfr.rIMInform), 3, rIMInform, &mMEDirectInformTfrPdu);
         ie->value.u.sztInter_SystemInformTfrTyp.val.rIMTfr.rIMRoutingAddr.choice.pres = NOTPRSNT;

         ie->value.u.sztInter_SystemInformTfrTyp.val.rIMTfr.iE_Extns.noComp.pres = NOTPRSNT;
      }
   }

   *pdu = mMEDirectInformTfrPdu;

   RETVALUE(ROK);
}


/*
*
*       Fun:   szAcUtlSztFillMMEDirectInformTfr 
*
*       Desc:  Call handler to fill MME Direct Information Transfer message
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
PUBLIC S16 szAcUtlSztFillInvalidPdu
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInvalidPdu(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillInvalidPdu
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillInvalidPdu(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *mMEDirectInformTfrPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U8         rIMInform[8];
   SztProtIE_Field_MMEDirectInformTfrIEs *ie;

   TRC2(szAcUtlSztFillInvalidPdu);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&mMEDirectInformTfrPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillMMEDirectInformTfr: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(mMEDirectInformTfrPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(mMEDirectInformTfrPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(mMEDirectInformTfrPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(mMEDirectInformTfrPdu->pdu.val.initiatingMsg.procedureCode), Sztid_MMEDirectInformTfr);
   szFillTknU32(&(mMEDirectInformTfrPdu->pdu.val.initiatingMsg.criticality), SztCriticalityignoreEnum);

   {
      numComp = 1;
      szFillTknU8(&(mMEDirectInformTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEDirectInformTfr.pres), PRSNT_NODEF);
      szFillTknU16(&(mMEDirectInformTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEDirectInformTfr.protocolIEs.noComp), numComp);

      if ((cmGetMem(mMEDirectInformTfrPdu, (numComp * sizeof(SztProtIE_Field_MMEDirectInformTfrIEs)), 
             (Ptr *)&mMEDirectInformTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEDirectInformTfr.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillMMEDirectInformTfr:: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {
         ie = &mMEDirectInformTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEDirectInformTfr.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Inter_SystemInformTfrTypMDT);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU8(&(ie->value.u.sztInter_SystemInformTfrTyp.choice), INTER_SYSTEMINFORMTFRTYP_RIMTFR);
         szFillTknU8(&(ie->value.u.sztInter_SystemInformTfrTyp.val.rIMTfr.pres), PRSNT_NODEF);
         strcpy((char *)rIMInform, "111");
         szFillTknStrOSXL(&(ie->value.u.sztInter_SystemInformTfrTyp.val.rIMTfr.rIMInform), 3, rIMInform, &mMEDirectInformTfrPdu);
         ie->value.u.sztInter_SystemInformTfrTyp.val.rIMTfr.rIMRoutingAddr.choice.pres = NOTPRSNT;

         ie->value.u.sztInter_SystemInformTfrTyp.val.rIMTfr.iE_Extns.noComp.pres = NOTPRSNT;
      }
   }

   *pdu = mMEDirectInformTfrPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillDeactvTrace
*
*       Desc:  Call handler to fill Deactivate Trace message
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
PUBLIC S16 szAcUtlSztFillDeactvTrace
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillDeactvTrace(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillDeactvTrace
(
S1apPdu      **pdu
)
#else
PUBLIC S16 szAcUtlSztFillDeactvTrace(pdu)
S1apPdu      **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *deactvTracePdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId = 0;
   U32        mmeId = 0;
   U8         traceRef[10];
   U16        len;
   U8         critBug = FALSE;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   SztProtIE_Field_DeactvTraceIEs *ie;

   TRC2(szAcUtlSztFillDeactvTrace);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&deactvTracePdu);

   cmMemset((U8 *)&(deactvTracePdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(deactvTracePdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(deactvTracePdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(deactvTracePdu->pdu.val.initiatingMsg.procedureCode), Sztid_DeactvTrace);
   szFillTknU32(&(deactvTracePdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;
      
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"critBug",&(critBug));
#endif
      if(critBug)
      {
         numComp--;
      }
      
      szFillTknU8(&(deactvTracePdu->pdu.val.initiatingMsg.value.u.sztDeactvTrace.pres), PRSNT_NODEF);
      szFillTknU16(&(deactvTracePdu->pdu.val.initiatingMsg.value.u.sztDeactvTrace.protocolIEs.noComp), numComp);

      if ((cmGetMem(deactvTracePdu, (numComp * sizeof(SztProtIE_Field_DeactvTraceIEs)), 
             (Ptr *)&deactvTracePdu->pdu.val.initiatingMsg.value.u.sztDeactvTrace.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillDeactvTracePdu: cmGetMem failed, line %d\n",__LINE__));
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
#endif

         numComp = 0;
         
         ie = &deactvTracePdu->pdu.val.initiatingMsg.value.u.sztDeactvTrace.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         if( critBug == FALSE )
         {
            ie = &deactvTracePdu->pdu.val.initiatingMsg.value.u.sztDeactvTrace.protocolIEs.member[numComp++];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);
         }

         ie = &deactvTracePdu->pdu.val.initiatingMsg.value.u.sztDeactvTrace.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id),  Sztid_E_UTRAN_Trace_ID);
         szFillTknU32(&(ie->criticality), SztCriticalitynotifyEnum);

         cmMemset(traceRef, 0, sizeof(traceRef));
         strcpy((char *)traceRef, "11112222");
         len = 8;
         szFillTknStrOSXL(&(ie->value.u.sztE_UTRAN_Trace_ID), len, traceRef, &deactvTracePdu);
       }
   }

   *pdu = deactvTracePdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillTraceStart_r9
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
PUBLIC S16 szAcUtlSztFillTraceStart_r9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillTraceStart_r9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillTraceStart_r9
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillTraceStart_r9(pdu)
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

   TRC2(szAcUtlSztFillTraceStart_r9);

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
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillTraceStart_r9Pdu: cmGetMem failed, line %d\n",__LINE__));
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
         

         /* Introduce a invalide IE id for criticality testing */
         if(critBug)
         {
            ie = &traceStartPdu->pdu.val.initiatingMsg.value.u.sztTraceStart.protocolIEs.member[3];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
            szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);
         }

         ie->value.u.sztTraceActvn.iE_Extns.noComp.pres = NOTPRSNT;
       }
   }

   *pdu = traceStartPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillTraceFailInd
*
*       Desc:  Call handler to fill Trace Failure Indication message
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
PUBLIC S16 szAcUtlSztFillTraceFailInd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillTraceFailInd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillTraceFailInd
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillTraceFailInd(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *traceFailIndPdu = NULLP;
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
   U8         choice;
   U32        cause;
   SztProtIE_Field_TraceFailIndIEs *ie;

   TRC2(szAcUtlSztFillTraceFailInd);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&traceFailIndPdu);

   cmMemset((U8 *)&(traceFailIndPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(traceFailIndPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(traceFailIndPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(traceFailIndPdu->pdu.val.initiatingMsg.procedureCode), Sztid_TraceFailInd);
   szFillTknU32(&(traceFailIndPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 4;
      szFillTknU8(&(traceFailIndPdu->pdu.val.initiatingMsg.value.u.sztTraceFailInd.pres), PRSNT_NODEF);
      szFillTknU16(&(traceFailIndPdu->pdu.val.initiatingMsg.value.u.sztTraceFailInd.protocolIEs.noComp), numComp);

      if ((cmGetMem(traceFailIndPdu, (numComp * sizeof(SztProtIE_Field_TraceFailIndIEs)), 
             (Ptr *)&traceFailIndPdu->pdu.val.initiatingMsg.value.u.sztTraceFailInd.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillTraceFailIndPdu: cmGetMem failed, line %d\n",__LINE__));
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
#endif

         ie = &traceFailIndPdu->pdu.val.initiatingMsg.value.u.sztTraceFailInd.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &traceFailIndPdu->pdu.val.initiatingMsg.value.u.sztTraceFailInd.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &traceFailIndPdu->pdu.val.initiatingMsg.value.u.sztTraceFailInd.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_E_UTRAN_Trace_ID);
         szFillTknU32(&(ie->criticality), SztCriticalitynotifyEnum);

         cmMemset(traceRef, 0, sizeof(traceRef));
         strcpy((char *)traceRef, "11112222");
         len = 8;
         szFillTknStrOSXL(&(ie->value.u.sztE_UTRAN_Trace_ID), len, traceRef, &traceFailIndPdu);
         
         ie = &traceFailIndPdu->pdu.val.initiatingMsg.value.u.sztTraceFailInd.protocolIEs.member[3];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Cause);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         choice = CAUSE_RADIONW;
         cause  = SztCauseRadioNwunspecifiedEnum;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
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
       }
   }

   *pdu = traceFailIndPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillLocReport
*
*       Desc:  Call handler to fill Location Report message
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
PUBLIC S16 szAcUtlSztFillLocReport
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillLocReport(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillLocReport
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillLocReport(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *locReportPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId = 0;
   U32        mmeId = 0;
   U8         pLMNId[10];
   U16        len;
   U8         critBug = FALSE;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   SztProtIE_Field_LocReportIEs *ie;

   TRC2(szAcUtlSztFillLocReport);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&locReportPdu);

   cmMemset((U8 *)&(locReportPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(locReportPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(locReportPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(locReportPdu->pdu.val.initiatingMsg.procedureCode), Sztid_LocReport);
   szFillTknU32(&(locReportPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 5;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"critBug",&(critBug));
#endif /* SZ_ENC_DEC */
   
      if( critBug )
      {
         numComp--;
      }
 
      szFillTknU8(&(locReportPdu->pdu.val.initiatingMsg.value.u.sztLocReport.pres), PRSNT_NODEF);
      szFillTknU16(&(locReportPdu->pdu.val.initiatingMsg.value.u.sztLocReport.protocolIEs.noComp), numComp);

      if ((cmGetMem(locReportPdu, (numComp * sizeof(SztProtIE_Field_LocReportIEs)), 
             (Ptr *)&locReportPdu->pdu.val.initiatingMsg.value.u.sztLocReport.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillLocReportPdu: cmGetMem failed, line %d\n",__LINE__));
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

         ie = &locReportPdu->pdu.val.initiatingMsg.value.u.sztLocReport.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &locReportPdu->pdu.val.initiatingMsg.value.u.sztLocReport.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &locReportPdu->pdu.val.initiatingMsg.value.u.sztLocReport.protocolIEs.member[2];

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
         szFillTknStrOSXL(&(ie->value.u.sztEUTRAN_CGI.pLMNidentity), len, pLMNId, &locReportPdu);

         len = 28;
         szFillTknBStr32(&(ie->value.u.sztEUTRAN_CGI.cell_ID), len, 100);

         ie->value.u.sztEUTRAN_CGI.iE_Extns.noComp.pres = NOTPRSNT;

         ie = &locReportPdu->pdu.val.initiatingMsg.value.u.sztLocReport.protocolIEs.member[3];

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
#endif
         szFillTknStrOSXL(&(ie->value.u.sztTAI.pLMNidentity), len, pLMNId, &locReportPdu);     

         len = 2;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "tacLen", &(len));
#endif
         szFillTknStr4(&(ie->value.u.sztTAI.tAC), (U8)len, 1);

         ie->value.u.sztTAI.iE_Extns.noComp.pres = NOTPRSNT;
         
         if(!critBug)
         {
            ie = &locReportPdu->pdu.val.initiatingMsg.value.u.sztLocReport.protocolIEs.member[4];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_RqstTyp);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

            szFillTknU8(&(ie->value.u.sztRqstTyp.pres), PRSNT_NODEF);
            szFillTknU32(&(ie->value.u.sztRqstTyp.eventTyp), SztEventTypstop_change_of_serve_cellEnum);
            /* cmMemset(rArea, 0, sizeof(rArea));
               strcpy((char *)rArea, "111");
               len = 3;
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "rArea", &(rArea));
               cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "rAreaLen", &(len));*/
            szFillTknU32(&(ie->value.u.sztRqstTyp.reportArea),SztReportAreaecgiEnum );     

            ie->value.u.sztRqstTyp.iE_Extns.noComp.pres = NOTPRSNT;
         }
       }
   }

   *pdu = locReportPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillLocRprtngCntrl
*
*       Desc:  Call handler to fill Location Reporting Control message
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
PUBLIC S16 szAcUtlSztFillLocRprtngCntrl
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillLocRprtngCntrl(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillLocRprtngCntrl
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillLocRprtngCntrl(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *locRprtngCntrlPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
   U8         critBug = FALSE;
 /*  U8         rArea[8];*/
/*   U16        len;*/
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   SztProtIE_Field_LocRprtngCntrlIEs *ie;

   TRC2(szAcUtlSztFillLocRprtngCntrl);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&locRprtngCntrlPdu);

   cmMemset((U8 *)&(locRprtngCntrlPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(locRprtngCntrlPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(locRprtngCntrlPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(locRprtngCntrlPdu->pdu.val.initiatingMsg.procedureCode), Sztid_LocRprtngCntrl);
   szFillTknU32(&(locRprtngCntrlPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"critBug",&(critBug));
#endif /* SZ_ENC_DEC */
   
      if( critBug )
      {
         numComp++;
      }
      
      szFillTknU8(&(locRprtngCntrlPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngCntrl.pres), PRSNT_NODEF);
      szFillTknU16(&(locRprtngCntrlPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngCntrl.protocolIEs.noComp), numComp);

      if ((cmGetMem(locRprtngCntrlPdu, (numComp * sizeof(SztProtIE_Field_LocRprtngCntrlIEs)), 
             (Ptr *)&locRprtngCntrlPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngCntrl.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillLocRprtngCntrlPdu: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {
         numComp = 0;
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
#endif   /* SZ_ENC_DEC */

         ie = &locRprtngCntrlPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngCntrl.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &locRprtngCntrlPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngCntrl.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         if( critBug )
         {
            
            ie = &locRprtngCntrlPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngCntrl.protocolIEs.member[numComp++];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_Crit_Tst4);
            szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

            szFillTknU8(&(ie->value.u.sztRqstTyp.pres), PRSNT_NODEF);
            szFillTknU32(&(ie->value.u.sztRqstTyp.eventTyp), SztEventTypstop_change_of_serve_cellEnum);     

            ie->value.u.sztRqstTyp.iE_Extns.noComp.pres = NOTPRSNT;
         }
         ie = &locRprtngCntrlPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngCntrl.protocolIEs.member[numComp++];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_RqstTyp);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         szFillTknU8(&(ie->value.u.sztRqstTyp.pres), PRSNT_NODEF);
         szFillTknU32(&(ie->value.u.sztRqstTyp.eventTyp), SztEventTypstop_change_of_serve_cellEnum);
      /*   cmMemset(rArea, 0, sizeof(rArea));
         strcpy((char *)rArea, "111");
         len = 3;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "rArea", &(rArea));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "rAreaLen", &(len));*/
         szFillTknU32(&(ie->value.u.sztRqstTyp.reportArea), SztReportAreaecgiEnum);     

         ie->value.u.sztRqstTyp.iE_Extns.noComp.pres = NOTPRSNT;
       }
   }


   *pdu = locRprtngCntrlPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillLocRprtngFailInd
*
*       Desc:  Call handler to fill Location Report Failure Indication message
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
PUBLIC S16 szAcUtlSztFillLocRprtngFailInd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillLocRprtngFailInd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillLocRprtngFailInd
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillLocRprtngFailInd(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *locRprtngFailIndPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
   U8      choice;
   U32     cause;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   SztProtIE_Field_LocRprtngFailIndIEs *ie;

   TRC2(szAcUtlSztFillLocRprtngFailInd);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&locRprtngFailIndPdu);

   cmMemset((U8 *)&(locRprtngFailIndPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(locRprtngFailIndPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(locRprtngFailIndPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(locRprtngFailIndPdu->pdu.val.initiatingMsg.procedureCode), Sztid_LocRprtngFailInd);
   szFillTknU32(&(locRprtngFailIndPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;
      szFillTknU8(&(locRprtngFailIndPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngFailInd.pres), PRSNT_NODEF);
      szFillTknU16(&(locRprtngFailIndPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngFailInd.protocolIEs.noComp), numComp);

      if ((cmGetMem(locRprtngFailIndPdu, (numComp * sizeof(SztProtIE_Field_LocRprtngFailIndIEs)), 
             (Ptr *)&locRprtngFailIndPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngFailInd.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillLocRprtngFailInd: cmGetMem failed, line %d\n",__LINE__));
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
#endif   /* SZ_ENC_DEC */

         ie = &locRprtngFailIndPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngFailInd.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &locRprtngFailIndPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngFailInd.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);
        
         ie = &locRprtngFailIndPdu->pdu.val.initiatingMsg.value.u.sztLocRprtngFailInd.protocolIEs.member[2];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Cause);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         choice = CAUSE_RADIONW;
         cause  = SztCauseRadioNwunspecifiedEnum;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
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
        
      }
   }

   *pdu = locRprtngFailIndPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillENBConfigUpd
*
*       Desc:  Call handler to fill ENB Configuration Update message
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
PUBLIC S16 szAcUtlSztFillENBConfigUpd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBConfigUpd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillENBConfigUpd
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBConfigUpd(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *eNBConfigUpdPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U8         enbName[8];
   U16        len;
   SztProtIE_Field_ENBConfigUpdIEs *ie;
   SztCSG_IdLst_Item               *ie1;

   U32        buggy = 0;
   
   
   SztSuppTAs_Item *tACItem;
   U8      pLMNId[10];
   U32       critBug = 0;
   
   TRC2(szAcUtlSztFillENBConfigUpd);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eNBConfigUpdPdu);

   cmMemset((U8 *)&(eNBConfigUpdPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(eNBConfigUpdPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(eNBConfigUpdPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(eNBConfigUpdPdu->pdu.val.initiatingMsg.procedureCode), Sztid_ENBConfigUpd);
   szFillTknU32(&(eNBConfigUpdPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   numComp = 2;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"bug",&(buggy));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"critBug",&(critBug));
#endif

   if(critBug)
   {
      numComp++;
   }
   szFillTknU8(&(eNBConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztENBConfigUpd.pres), PRSNT_NODEF);
   szFillTknU16(&(eNBConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztENBConfigUpd.protocolIEs.noComp), numComp);

   if ((cmGetMem(eNBConfigUpdPdu, (numComp * sizeof(SztProtIE_Field_ENBConfigUpdIEs)), 
               (Ptr *)&eNBConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztENBConfigUpd.protocolIEs.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBConfigUpd: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   if(!buggy)
   {
      ie = &eNBConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztENBConfigUpd.protocolIEs.member[0];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_eNBname);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      cmMemset(enbName, 0, sizeof(enbName));
      strcpy((char *)enbName, "ENB"); 
      szFillTknStrOSXL(&(ie->value.u.sztENBname), 3, enbName, &eNBConfigUpdPdu);

      ie = &eNBConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztENBConfigUpd.protocolIEs.member[1];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CSG_IdLst);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);

      numComp = 1;
      szFillTknU16(&(ie->value.u.sztCSG_IdLst.noComp), numComp);

      if ((cmGetMem(eNBConfigUpdPdu, numComp * sizeof(SztCSG_IdLst_Item), 
                  (Ptr*)&(ie->value.u.sztCSG_IdLst.member))) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBConfigUpd: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      ie1 = &ie->value.u.sztCSG_IdLst.member[0];
      szFillTknU8(&(ie1->pres), PRSNT_NODEF);
      len = 27; 
      szFillTknBStr32(&(ie1->cSG_Id), len, 100);
   }
   else
   {
      ie = &eNBConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztENBConfigUpd.protocolIEs.member[0];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CSG_IdLst);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

      numComp = 1;
      szFillTknU16(&(ie->value.u.sztCSG_IdLst.noComp), numComp);

      if ((cmGetMem(eNBConfigUpdPdu, numComp * sizeof(SztCSG_IdLst_Item), 
                  (Ptr*)&(ie->value.u.sztCSG_IdLst.member))) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBConfigUpd: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      ie1 = &ie->value.u.sztCSG_IdLst.member[0];
      szFillTknU8(&(ie1->pres), PRSNT_NODEF);
      len = 27; 
      szFillTknBStr32(&(ie1->cSG_Id), len, 100);

      /* IE2 - Filling Supported TAs */
      ie = &eNBConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztENBConfigUpd.protocolIEs.member[1];

      szFillTknU8(&(ie->pres),PRSNT_NODEF);
      szFillTknU32(&(ie->id),Sztid_SuppTAs);
      szFillTknU32(&(ie->criticality),SztCriticalityrejectEnum);

      numComp = 1;
      szFillTknU16(&(ie->value.u.sztSuppTAs.noComp),numComp);

      /* IE3 - Allocate memory for TA items */
      if ((cmGetMem(eNBConfigUpdPdu, numComp*sizeof(SztSuppTAs_Item), 
                  (Ptr*)&(ie->value.u.sztSuppTAs.member))) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupReq: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
         RETVALUE(RFAILED);
      }

      /* IE3 - Filling TA item 1 */
      tACItem = &ie->value.u.sztSuppTAs.member[0];
      szFillTknU8(&(tACItem->pres),PRSNT_NODEF);

      /* IE3 - Filling tAC */
      len = 2;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"tacLen",&(len));
#endif /* SZ_ENC_DEC */

      szFillTknStr4(&(tACItem->tAC), (U8)len, 1);

      /* IE3 - Filling broadcastPLMNs */
      numComp = 1;
      /* Allocate memory for broadcast PLMNs */
      if ((cmGetMem(eNBConfigUpdPdu, numComp*sizeof(SztPLMNidentity), 
                  (Ptr*)&(tACItem->broadcastPLMNs.member))) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillS1SetupReq: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
         RETVALUE(RFAILED);
      }
      szFillTknU16(&(tACItem->broadcastPLMNs.noComp),numComp);

      cmMemset(pLMNId,0,sizeof(pLMNId));
      strcpy((char *)pLMNId,"111");
      len = 3;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT,"plmnIdVal",&(pLMNId));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"plmnIdLen",&(len));
#endif /* SZ_ENC_DEC */

      szFillTknStrOSXL(&(tACItem->broadcastPLMNs.member[0]),len,pLMNId,&eNBConfigUpdPdu);

   }
   if(critBug)
   {
      ie = &eNBConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztENBConfigUpd.protocolIEs.member[2];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      cmMemset(enbName, 0, sizeof(enbName));
      strcpy((char *)enbName, "ENB"); 
      szFillTknStrOSXL(&(ie->value.u.sztENBname), 3, enbName, &eNBConfigUpdPdu);
   }

   *pdu = eNBConfigUpdPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillENBConfigUpdAckg
*
*       Desc:  Call handler to fill ENB Configuration Update Ackg message
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
PUBLIC S16 szAcUtlSztFillENBConfigUpdAckg
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBConfigUpdAckg(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillENBConfigUpdAckg
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBConfigUpdAckg(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *eNBConfigUpdAckgPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   SztProtIE_Field_ENBConfigUpdAckgIEs *ie;

   TRC2(szAcUtlSztFillENBConfigUpdAckg);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eNBConfigUpdAckgPdu);

   cmMemset((U8 *)&(eNBConfigUpdAckgPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(eNBConfigUpdAckgPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(eNBConfigUpdAckgPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(eNBConfigUpdAckgPdu->pdu.val.successfulOutcome.procedureCode), Sztid_ENBConfigUpd);
   szFillTknU32(&(eNBConfigUpdAckgPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 1;
      szFillTknU8(&(eNBConfigUpdAckgPdu->pdu.val.successfulOutcome.value.u.sztENBConfigUpdAckg.pres), PRSNT_NODEF);
      szFillTknU16(&(eNBConfigUpdAckgPdu->pdu.val.successfulOutcome.value.u.sztENBConfigUpdAckg.protocolIEs.noComp), numComp);

      if ((cmGetMem(eNBConfigUpdAckgPdu, (numComp * sizeof(SztProtIE_Field_ENBConfigUpdAckgIEs)), 
          (Ptr *)&eNBConfigUpdAckgPdu->pdu.val.successfulOutcome.value.u.sztENBConfigUpdAckg.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBConfigUpdAckg: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      ie = &eNBConfigUpdAckgPdu->pdu.val.successfulOutcome.value.u.sztENBConfigUpdAckg.protocolIEs.member[0];
      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CriticalityDiag);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);
      szFillTknU32(&(ie->value.u.sztCriticalityDiag.procedureCode), Sztid_ENBConfigUpd);
      szFillTknU32(&(ie->value.u.sztCriticalityDiag.triggeringMsg), SztTrgMsgsuccessful_outcomeEnum);
      szFillTknU32(&(ie->value.u.sztCriticalityDiag.procedureCriticality), SztCriticalityignoreEnum);

      ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp.pres = NOTPRSNT;

      ie->value.u.sztCriticalityDiag.iE_Extns.noComp.pres = NOTPRSNT;
   }

   *pdu = eNBConfigUpdAckgPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillENBConfigUpdFail
*
*       Desc:  Call handler to fill ENB Configuration Fail message
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
PUBLIC S16 szAcUtlSztFillENBConfigUpdFail
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBConfigUpdFail(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillENBConfigUpdFail
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBConfigUpdFail(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *eNBConfigUpdFailPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U8         choice;
   U32        cause;
   SztProtIE_Field_ENBConfigUpdFailIEs *ie;

   TRC2(szAcUtlSztFillENBConfigUpdFail);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eNBConfigUpdFailPdu);

   cmMemset((U8 *)&(eNBConfigUpdFailPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(eNBConfigUpdFailPdu->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&(eNBConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(eNBConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.procedureCode), Sztid_ENBConfigUpd);
   szFillTknU32(&(eNBConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 1;
      szFillTknU8(&(eNBConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztENBConfigUpdFail.pres), PRSNT_NODEF);
      szFillTknU16(&(eNBConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztENBConfigUpdFail.protocolIEs.noComp), numComp);

      if ((cmGetMem(eNBConfigUpdFailPdu, (numComp * sizeof(SztProtIE_Field_ENBConfigUpdFailIEs)), 
          (Ptr *)&eNBConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztENBConfigUpdFail.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBConfigUpdFail: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      ie = &eNBConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztENBConfigUpdFail.protocolIEs.member[0];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_Cause);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      choice = CAUSE_RADIONW;
      cause  = SztCauseRadioNwunspecifiedEnum;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
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
   }

   *pdu = eNBConfigUpdFailPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillMMEBConfigUpd
*
*       Desc:  Call handler to fill MME Configuration Update message
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
PUBLIC S16 szAcUtlSztFillMMEConfigUpd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillMMEConfigUpd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillMMEConfigUpd
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillMMEConfigUpd(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *mMEConfigUpdPdu = NULLP;
   S16        numComp;
   U8         mmeName[8];
   S16        ret;
   Mem        mem; 
   SztProtIE_Field_MMEConfigUpdIEs *ie;

   U32      buggy = 0;
   U32      critBug = 0;

   TRC2(szAcUtlSztFillMMEConfigUpd);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&mMEConfigUpdPdu);

   cmMemset((U8 *)&(mMEConfigUpdPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(mMEConfigUpdPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(mMEConfigUpdPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(mMEConfigUpdPdu->pdu.val.initiatingMsg.procedureCode), Sztid_MMEConfigUpd);
   szFillTknU32(&(mMEConfigUpdPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"critBug",&(critBug));
#endif
   {
      numComp = 2;
      if(critBug)
      {
        numComp++;
      } 

      szFillTknU8(&(mMEConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztMMEConfigUpd.pres), PRSNT_NODEF);
      szFillTknU16(&(mMEConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztMMEConfigUpd.protocolIEs.noComp), numComp);

      if ((cmGetMem(mMEConfigUpdPdu, (numComp * sizeof(SztProtIE_Field_MMEConfigUpdIEs)), 
                  (Ptr *)&mMEConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztMMEConfigUpd.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillMMEConfigUpd: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"bug",&(buggy));
#endif
      if(!buggy)
      {
         ie = &mMEConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztMMEConfigUpd.protocolIEs.member[0];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MMEname);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         strcpy((char *)mmeName, "MME");
         szFillTknStrOSXL(&(ie->value.u.sztMMEname), 3, mmeName, &mMEConfigUpdPdu);

         ie = &mMEConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztMMEConfigUpd.protocolIEs.member[1];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_RelativeMMECapacity);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztRelativeMMECapacity), 128);

      }
      else
      {
        
         
         ie = &mMEConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztMMEConfigUpd.protocolIEs.member[1];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MMEname);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         strcpy((char *)mmeName, "MME");
         szFillTknStrOSXL(&(ie->value.u.sztMMEname), 3, mmeName, &mMEConfigUpdPdu);

         ie = &mMEConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztMMEConfigUpd.protocolIEs.member[0];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_RelativeMMECapacity);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztRelativeMMECapacity), 128);

      }
   }

   if(critBug)
   {
      ie = &mMEConfigUpdPdu->pdu.val.initiatingMsg.value.u.sztMMEConfigUpd.protocolIEs.member[2];
      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU32(&(ie->value.u.sztRelativeMMECapacity), 128);
   }
   *pdu = mMEConfigUpdPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillMMEConfigUpdAckg
*
*       Desc:  Call handler to fill MME Configuration Update Ackg message
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
PUBLIC S16 szAcUtlSztFillMMEConfigUpdAckg
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillMMEConfigUpdAckg(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillMMEConfigUpdAckg
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillMMEConfigUpdAckg(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *mMEConfigUpdAckgPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   SztProtIE_Field_MMEConfigUpdAckgIEs *ie;

   TRC2(szAcUtlSztFillMMEConfigUpdAckg);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&mMEConfigUpdAckgPdu);

   cmMemset((U8 *)&(mMEConfigUpdAckgPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(mMEConfigUpdAckgPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(mMEConfigUpdAckgPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(mMEConfigUpdAckgPdu->pdu.val.successfulOutcome.procedureCode), Sztid_MMEConfigUpd);
   szFillTknU32(&(mMEConfigUpdAckgPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 1;
      szFillTknU8(&(mMEConfigUpdAckgPdu->pdu.val.successfulOutcome.value.u.sztMMEConfigUpdAckg.pres), PRSNT_NODEF);
      szFillTknU16(&(mMEConfigUpdAckgPdu->pdu.val.successfulOutcome.value.u.sztMMEConfigUpdAckg.protocolIEs.noComp), numComp);

      if ((cmGetMem(mMEConfigUpdAckgPdu, (numComp * sizeof(SztProtIE_Field_MMEConfigUpdAckgIEs)), 
          (Ptr *)&mMEConfigUpdAckgPdu->pdu.val.successfulOutcome.value.u.sztMMEConfigUpdAckg.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillMMEConfigUpdAckg: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      ie = &mMEConfigUpdAckgPdu->pdu.val.successfulOutcome.value.u.sztMMEConfigUpdAckg.protocolIEs.member[0];
      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_CriticalityDiag);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      szFillTknU8(&(ie->value.u.sztCriticalityDiag.pres), PRSNT_NODEF);
      szFillTknU32(&(ie->value.u.sztCriticalityDiag.procedureCode), Sztid_MMEConfigUpd);
      szFillTknU32(&(ie->value.u.sztCriticalityDiag.triggeringMsg), SztTrgMsgsuccessful_outcomeEnum);
      szFillTknU32(&(ie->value.u.sztCriticalityDiag.procedureCriticality), SztCriticalityignoreEnum);

      ie->value.u.sztCriticalityDiag.iEsCriticalityDiag.noComp.pres = NOTPRSNT;

      ie->value.u.sztCriticalityDiag.iE_Extns.noComp.pres = NOTPRSNT;
   }

   *pdu = mMEConfigUpdAckgPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillMMEConfigUpdFail
*
*       Desc:  Call handler to fill MME Configuration Fail message
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
PUBLIC S16 szAcUtlSztFillMMEConfigUpdFail
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillMMEConfigUpdFail(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillMMEConfigUpdFail
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillMMEConfigUpdFail(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *mMEConfigUpdFailPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U8         choice;
   U32        cause;
   SztProtIE_Field_MMEConfigUpdFailIEs *ie;

   TRC2(szAcUtlSztFillMMEConfigUpdFail);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&mMEConfigUpdFailPdu);

   cmMemset((U8 *)&(mMEConfigUpdFailPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(mMEConfigUpdFailPdu->pdu.choice), S1AP_PDU_UNSUCCESSFULOUTCOME);
   szFillTknU8(&(mMEConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(mMEConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.procedureCode), Sztid_MMEConfigUpd);
   szFillTknU32(&(mMEConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 1;
      szFillTknU8(&(mMEConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztMMEConfigUpdFail.pres), PRSNT_NODEF);
      szFillTknU16(&(mMEConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztMMEConfigUpdFail.protocolIEs.noComp), numComp);

      if ((cmGetMem(mMEConfigUpdFailPdu, (numComp * sizeof(SztProtIE_Field_MMEConfigUpdFailIEs)), 
          (Ptr *)&mMEConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztMMEConfigUpdFail.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillMMEConfigUpdFail: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      ie = &mMEConfigUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.sztMMEConfigUpdFail.protocolIEs.member[0];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_Cause);
      szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
      choice = CAUSE_RADIONW;
      cause  = SztCauseRadioNwunspecifiedEnum;
#ifndef SZ_ENC_DEC
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
#endif
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
   }

   *pdu = mMEConfigUpdFailPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillUlnkS1cdma2000tunneling
*
*       Desc:  Call handler to fill Uplink S1 CDMA2000 Tunneling message
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
PUBLIC S16 szAcUtlSztFillUlnkS1cdma2000tunneling
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUlnkS1cdma2000tunneling(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUlnkS1cdma2000tunneling
(
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUlnkS1cdma2000tunneling(pdu)
S1apPdu    **pdu;
#endif
#endif /* SZ_ENC_DEC */
{
   S1apPdu   *ulnkS1cdma2000tunnelingPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
   U8         cdma2000SecId[8];
   U8         cdma2000Pdu[8];
   U16        len;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif /* SZ_ENC_DEC */
   SztProtIE_Field_UlnkS1cdma2000tunnelingIEs *ie;
   U8         critBug = FALSE;

   TRC2(szAcUtlSztFillUlnkS1cdma2000tunneling);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&ulnkS1cdma2000tunnelingPdu);

   cmMemset((U8 *)&(ulnkS1cdma2000tunnelingPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(ulnkS1cdma2000tunnelingPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(ulnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(ulnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.procedureCode), Sztid_UlnkS1cdma2000tunneling);
   szFillTknU32(&(ulnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"critBug",&(critBug));
#endif
   {
      numComp = 5;
      if(critBug)
      {
         numComp++;
      }
      szFillTknU8(&(ulnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztUlnkS1cdma2000tunneling.pres), PRSNT_NODEF);
      szFillTknU16(&(ulnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztUlnkS1cdma2000tunneling.protocolIEs.noComp), numComp);

      if ((cmGetMem(ulnkS1cdma2000tunnelingPdu, (numComp * sizeof(SztProtIE_Field_UlnkS1cdma2000tunnelingIEs)), 
             (Ptr *)&ulnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztUlnkS1cdma2000tunneling.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUlnkS1cdma2000tunneling: cmGetMem failed, line %d\n",__LINE__));
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

         ie = &ulnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztUlnkS1cdma2000tunneling.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &ulnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztUlnkS1cdma2000tunneling.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &ulnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztUlnkS1cdma2000tunneling.protocolIEs.member[2];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_cdma2000RATTyp);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztCdma2000RATTyp), SztCdma2000RATTyponexRTTEnum);

         ie = &ulnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztUlnkS1cdma2000tunneling.protocolIEs.member[3];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_cdma2000SectorID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         cmMemset(cdma2000SecId, 0, sizeof(cdma2000SecId));
         strcpy((char *)cdma2000SecId, "111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "cdma2000SecId", &(cdma2000SecId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cdma2000SecIdLen", &(len));
#endif /* SZ_ENC_DEC */
         szFillTknStrOSXL(&(ie->value.u.sztCdma2000SectorID), len, cdma2000SecId, &ulnkS1cdma2000tunnelingPdu);     

         ie = &ulnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztUlnkS1cdma2000tunneling.protocolIEs.member[4];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_cdma2000PDU);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         cmMemset(cdma2000Pdu, 0, sizeof(cdma2000Pdu));
         strcpy((char *)cdma2000Pdu, "111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "cdma2000Pdu", &(cdma2000Pdu));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cdma2000PduLen", &(len));
#endif /* SZ_ENC_DEC */
         szFillTknStrOSXL(&(ie->value.u.sztCdma2000PDU), len, cdma2000Pdu, &ulnkS1cdma2000tunnelingPdu);

         if(critBug)
         {
            ie = &ulnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztUlnkS1cdma2000tunneling.protocolIEs.member[5];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
            szFillTknU32(&(ie->criticality), SztCriticalitynotifyEnum);
            szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);
         }

      }
   }

   *pdu = ulnkS1cdma2000tunnelingPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillDlnkS1cdma2000tunneling
*
*       Desc:  Call handler to fill Downlink S1 CDMA2000 Tunneling message
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
PUBLIC S16 szAcUtlSztFillDlnkS1cdma2000tunneling
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillDlnkS1cdma2000tunneling(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillDlnkS1cdma2000tunneling
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillDlnkS1cdma2000tunneling(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *dlnkS1cdma2000tunnelingPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
   U8         cdma2000Pdu[8];
   U16        len;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   SztProtIE_Field_DlnkS1cdma2000tunnelingIEs *ie;
   U8        critBug = FALSE;

   TRC2(szAcUtlSztFillDlnkS1cdma2000tunneling);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&dlnkS1cdma2000tunnelingPdu);

   cmMemset((U8 *)&(dlnkS1cdma2000tunnelingPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(dlnkS1cdma2000tunnelingPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(dlnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(dlnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.procedureCode), Sztid_DlnkS1cdma2000tunneling);
   szFillTknU32(&(dlnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"critBug",&(critBug));
#endif
   {
      numComp = 4;
      if(critBug)
      {
         numComp++;
      }
      szFillTknU8(&(dlnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztDlnkS1cdma2000tunneling.pres), PRSNT_NODEF);
      szFillTknU16(&(dlnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztDlnkS1cdma2000tunneling.protocolIEs.noComp), numComp);

      if ((cmGetMem(dlnkS1cdma2000tunnelingPdu, (numComp * sizeof(SztProtIE_Field_DlnkS1cdma2000tunnelingIEs)), 
             (Ptr *)&dlnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztDlnkS1cdma2000tunneling.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillDlnkS1cdma2000tunneling: cmGetMem failed, line %d\n",__LINE__));
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
#endif   /* SZ_ENC_DEC */

         ie = &dlnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztDlnkS1cdma2000tunneling.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &dlnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztDlnkS1cdma2000tunneling.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &dlnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztDlnkS1cdma2000tunneling.protocolIEs.member[2];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_cdma2000RATTyp);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztCdma2000RATTyp), SztCdma2000RATTyponexRTTEnum);

         if(critBug)
         {
            ie = &dlnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztDlnkS1cdma2000tunneling.protocolIEs.member[3];

            szFillTknU8(&(ie->pres), PRSNT_NODEF);
            szFillTknU32(&(ie->id), Sztid_Crit_Tst_ID);
            szFillTknU32(&(ie->criticality), SztCriticalitynotifyEnum);
            szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &dlnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztDlnkS1cdma2000tunneling.protocolIEs.member[4];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_cdma2000PDU);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         cmMemset(cdma2000Pdu, 0, sizeof(cdma2000Pdu));
         strcpy((char *)cdma2000Pdu, "111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "cdma2000Pdu", &(cdma2000Pdu));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cdma2000PduLen", &(len));
#endif
         szFillTknStrOSXL(&(ie->value.u.sztCdma2000PDU), len, cdma2000Pdu, &dlnkS1cdma2000tunnelingPdu);

         }
         else
        {
         ie = &dlnkS1cdma2000tunnelingPdu->pdu.val.initiatingMsg.value.u.sztDlnkS1cdma2000tunneling.protocolIEs.member[3];
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_cdma2000PDU);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         cmMemset(cdma2000Pdu, 0, sizeof(cdma2000Pdu));
         strcpy((char *)cdma2000Pdu, "111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "cdma2000Pdu", &(cdma2000Pdu));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "cdma2000PduLen", &(len));
#endif
         szFillTknStrOSXL(&(ie->value.u.sztCdma2000PDU), len, cdma2000Pdu, &dlnkS1cdma2000tunnelingPdu);

         }
      }
   }

   *pdu = dlnkS1cdma2000tunnelingPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillOverloadStart_r9
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
PUBLIC S16 szAcUtlSztFillOverloadStart_r9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillOverloadStart_r9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillOverloadStart_r9
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillOverloadStart_r9(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *overloadStartPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   SztProtIE_Field_OverloadStartIEs *ie;

   TRC2(szAcUtlSztFillOverloadStart_r9);

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
      szFillTknU8(&(overloadStartPdu->pdu.val.initiatingMsg.value.u.sztOverloadStart.pres), PRSNT_NODEF);
      szFillTknU16(&(overloadStartPdu->pdu.val.initiatingMsg.value.u.sztOverloadStart.protocolIEs.noComp), numComp);

      if ((cmGetMem(overloadStartPdu, (numComp * sizeof(SztProtIE_Field_OverloadStartIEs)), 
             (Ptr *)&overloadStartPdu->pdu.val.initiatingMsg.value.u.sztOverloadStart.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillOverloadStart_r9: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      ie = &overloadStartPdu->pdu.val.initiatingMsg.value.u.sztOverloadStart.protocolIEs.member[0];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_OverloadResp);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
      szFillTknU8(&(ie->value.u.sztOverloadResp.choice), OVERLOADRESP_OVERLOADACTION);
      szFillTknU32(&(ie->value.u.sztOverloadResp.val.overloadAction), SztOverloadActionreject_non_emergency_mo_dtEnum);
   }

   *pdu = overloadStartPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillOverloadStop_r9
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
PUBLIC S16 szAcUtlSztFillOverloadStop_r9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillOverloadStop_r9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillOverloadStop_r9
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillOverloadStop_r9(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *overloadStopPdu = NULLP;
   S16        ret;
   Mem        mem; 

   TRC2(szAcUtlSztFillOverloadStop_r9);

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
   szFillTknU16(&(overloadStopPdu->pdu.val.initiatingMsg.value.u.sztOverloadStop.protocolIEs.noComp), 0);

   *pdu = overloadStopPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillUECapbltyInfoInd
*
*       Desc:  Call handler to fill UE Capability Info Indication message
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
PUBLIC S16 szAcUtlSztFillUECapbltyInfoInd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUECapbltyInfoInd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUECapbltyInfoInd
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUECapbltyInfoInd(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *uECapbltyInfoIndPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
   U8         ueRadioCap[8];
   U16        len;
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   SztProtIE_Field_UECapbltyInfoIndIEs *ie;

   TRC2(szAcUtlSztFillUECapbltyInfoInd);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&uECapbltyInfoIndPdu);

   cmMemset((U8 *)&(uECapbltyInfoIndPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(uECapbltyInfoIndPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(uECapbltyInfoIndPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(uECapbltyInfoIndPdu->pdu.val.initiatingMsg.procedureCode), Sztid_UECapbltyInfoInd);
   szFillTknU32(&(uECapbltyInfoIndPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;
      szFillTknU8(&(uECapbltyInfoIndPdu->pdu.val.initiatingMsg.value.u.sztUECapbltyInfoInd.pres), PRSNT_NODEF);
      szFillTknU16(&(uECapbltyInfoIndPdu->pdu.val.initiatingMsg.value.u.sztUECapbltyInfoInd.protocolIEs.noComp), numComp);

      if ((cmGetMem(uECapbltyInfoIndPdu, (numComp * sizeof(SztProtIE_Field_UECapbltyInfoIndIEs)), 
             (Ptr *)&uECapbltyInfoIndPdu->pdu.val.initiatingMsg.value.u.sztUECapbltyInfoInd.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUECapbltyInfoInd: cmGetMem failed, line %d\n",__LINE__));
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
#endif   /* SZ_ENC_DEC */

         ie = &uECapbltyInfoIndPdu->pdu.val.initiatingMsg.value.u.sztUECapbltyInfoInd.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &uECapbltyInfoIndPdu->pdu.val.initiatingMsg.value.u.sztUECapbltyInfoInd.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

         ie = &uECapbltyInfoIndPdu->pdu.val.initiatingMsg.value.u.sztUECapbltyInfoInd.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_UERadioCapblty);
         szFillTknU32(&(ie->criticality), SztCriticalityignoreEnum);
         cmMemset(ueRadioCap, 0, sizeof(ueRadioCap));
         strcpy((char *)ueRadioCap, "111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "ueRadioCap", &(ueRadioCap));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "ueRadioCapLen", &(len));
#endif
         szFillTknStrOSXL(&(ie->value.u.sztUERadioCapblty), len, ueRadioCap, &uECapbltyInfoIndPdu);     
       }
   }

   *pdu = uECapbltyInfoIndPdu;

   RETVALUE(ROK);
}


/*
*
*       Fun:   szAcUtlSztFillENBConfigTfr
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
PUBLIC S16 szAcUtlSztFillENBConfigTfr
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBConfigTfr(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillENBConfigTfr
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillENBConfigTfr(pdu)
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

                                                                                                              
   TRC2(szAcUtlSztFillENBConfigTfr);
 
     mem.region = 0;
     mem.pool   = 0;
                                                                                                                  
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&eNBConfigTfrPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBConfigTfr: cmAllocEvnt failed, line %d\n",__LINE__));
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
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillENBConfigTfr:: cmGetMem failed, line %d\n",__LINE__));
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
      
         ie->value.u.sztSONConfigTfr.iE_Extns.noComp.pres = NOTPRSNT; 

      }
   }

   *pdu = eNBConfigTfrPdu;

   RETVALUE(ROK);
}



/*
*
*       Fun:   szAcUtlSztFillMMEConfigTfr
*
*       Desc:  Call handler to fill MME Configuration Transfer message
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
PUBLIC S16 szAcUtlSztFillMMEConfigTfr
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillMMEConfigTfr(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillMMEConfigTfr
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillMMEConfigTfr(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *mMEConfigTfrPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem;
   U8         pLMNId[10];
   U16        len;
   SztProtIE_Field_MMEConfigTfrIEs *ie;
   SztTgeteNB_ID *ie1;
   SztSrceNB_ID *ie2;
   SztSONInform *ie3;     

                                                                                                              
   TRC2(szAcUtlSztFillMMEConfigTfr);
 
     mem.region = 0;
     mem.pool   = 0;
                                                                                                                  
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&mMEConfigTfrPdu);
   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillMMEConfigTfr: cmAllocEvnt failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }
                                                                                                                  
   cmMemset((U8 *)&(mMEConfigTfrPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));
                                                                                                                  
   szFillTknU8(&(mMEConfigTfrPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(mMEConfigTfrPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(mMEConfigTfrPdu->pdu.val.initiatingMsg.procedureCode), Sztid_MMEConfigTfr);
   szFillTknU32(&(mMEConfigTfrPdu->pdu.val.initiatingMsg.criticality), SztCriticalityignoreEnum);

   {
      numComp = 1;
      szFillTknU8(&(mMEConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEConfigTfr.pres), PRSNT_NODEF);
      szFillTknU16(&(mMEConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEConfigTfr.protocolIEs.noComp), numComp);

      if ((cmGetMem(mMEConfigTfrPdu, (numComp * sizeof( SztProtIE_Field_MMEConfigTfrIEs )),
                  (Ptr *)&mMEConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEConfigTfr.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillMMEConfigTfr:: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {
         ie = &mMEConfigTfrPdu->pdu.val.initiatingMsg.value.u.sztMMEConfigTfr.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_SONConfigTfrMCT);
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
         szFillTknStrOSXL(&(ie1->global_ENB_ID.pLMNidentity), len, pLMNId, &mMEConfigTfrPdu);
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
         szFillTknStrOSXL(&(ie1->selected_TAI.pLMNidentity), len, pLMNId, &mMEConfigTfrPdu);

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
         szFillTknStrOSXL(&(ie2->global_ENB_ID.pLMNidentity), len, pLMNId, &mMEConfigTfrPdu);
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
         szFillTknStrOSXL(&(ie2->selected_TAI.pLMNidentity), len, pLMNId, &mMEConfigTfrPdu);

         len = 2;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"tacLen", &(len));
#endif
         szFillTknStr4(&(ie2->selected_TAI.tAC), (U8)len, 1);
         ie2->selected_TAI.iE_Extns.noComp.pres = NOTPRSNT;

         ie3 = &(ie->value.u.sztSONConfigTfr.sONInform);
         szFillTknU8(&(ie3->choice), SONINFORM_SONINFORMRQST);
         szFillTknU32(&(ie3->val.sONInformRqst), SztSONInformRqstx2TNL_Config_InfoEnum);
         
         ie->value.u.sztSONConfigTfr.iE_Extns.noComp.pres = NOTPRSNT; 

      }
   }

   *pdu = mMEConfigTfrPdu;
                                                                                                                  
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
PUBLIC S16 szAcUtlSztFillCellTrafficTrace_r9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillCellTrafficTrace_r9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillCellTrafficTrace_r9
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillCellTrafficTrace_r9(pdu)
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
                                                                                                              
   TRC2(szAcUtlSztFillCellTrafficTrace_r9);
                                                                                                              
   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&celltrficTracePdu);
                                                                                                              
   cmMemset((U8 *)&(celltrficTracePdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));
                                                                                                              
   szFillTknU8(&(celltrficTracePdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(celltrficTracePdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(celltrficTracePdu->pdu.val.initiatingMsg.procedureCode),  Sztid_CellTrafficTrace);
   szFillTknU32(&(celltrficTracePdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 5;
      
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
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillCellTrafficTrace_r9: cmGetMem failed, line %d\n",__LINE__));
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

       }
   }
                                                                                                              
   *pdu = celltrficTracePdu;
                                                                                                              
   RETVALUE(ROK);
}

#ifndef S1AP_REL8A0
/*
*
*       Fun:   szAcUtlSztFillKillRqst
*
*       Desc:  Call handler to fill kill request
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
PUBLIC S16 szAcUtlSztFillKillRqst
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillKillRqst(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillKillRqst
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillKillRqst(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *killRqstPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem;
   U16        len;
   SztProtIE_Field_KillRqstIEs *ie;
                                                                                                              
   TRC2(szAcUtlSztFillKillRqst);
                                                                                                              
   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&killRqstPdu);
                                                                                                              
   cmMemset((U8 *)&(killRqstPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));
                                                                                                              
   szFillTknU8(&(killRqstPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(killRqstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(killRqstPdu->pdu.val.initiatingMsg.procedureCode),  Sztid_Kill);
   szFillTknU32(&(killRqstPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);
   {
      numComp = 2;

      szFillTknU8(&(killRqstPdu->pdu.val.initiatingMsg.value.u.sztKillRqst.pres), PRSNT_NODEF);
      szFillTknU16(&(killRqstPdu->pdu.val.initiatingMsg.value.u.sztKillRqst.protocolIEs.noComp), numComp);
                                                                                                              
      if ((cmGetMem(killRqstPdu, (numComp * sizeof(SztProtIE_Field_KillRqstIEs)),
             (Ptr *)&killRqstPdu->pdu.val.initiatingMsg.value.u.sztKillRqst.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillKillRqst: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      ie = &killRqstPdu->pdu.val.initiatingMsg.value.u.sztKillRqst.protocolIEs.member[0];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_MsgIdentifier);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

      len = 16;
      szFillTknBStr32(&(ie->value.u.sztMsgIdentifier), len, 100);

      ie = &killRqstPdu->pdu.val.initiatingMsg.value.u.sztKillRqst.protocolIEs.member[1];

      szFillTknU8(&(ie->pres), PRSNT_NODEF);
      szFillTknU32(&(ie->id), Sztid_SerialNumber);
      szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

      len = 16;
      szFillTknBStr32(&(ie->value.u.sztMsgIdentifier), len, 100);

   }
                                                                                                              
   *pdu = killRqstPdu;
                                                                                                              
   RETVALUE(ROK);
}
 
/*
*
*       Fun:   szAcUtlSztFillKillResp
*
*       Desc:  Call handler to fill kill response
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
PUBLIC S16 szAcUtlSztFillKillResp
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillKillResp(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillKillResp
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillKillResp(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *killRespPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem;
   U16        len;
   U8         pLMNId[10];
   U32        nBroadcastRqst; 
   SztProtIE_Field_KillRespIEs   *ie;
   SztCellID_Cancelled_Item      *ie1;
                                                                                                              
   TRC2(szAcUtlSztFillKillResp);
                                                                                                              
   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&killRespPdu);
                                                                                                              
   cmMemset((U8 *)&(killRespPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));
                                                                                                              
   szFillTknU8(&(killRespPdu->pdu.choice), S1AP_PDU_SUCCESSFULOUTCOME);
   szFillTknU8(&(killRespPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   szFillTknU32(&(killRespPdu->pdu.val.successfulOutcome.procedureCode),  Sztid_Kill);
   szFillTknU32(&(killRespPdu->pdu.val.successfulOutcome.criticality), SztCriticalityrejectEnum);

   {
      numComp = 3;
      szFillTknU8(&(killRespPdu->pdu.val.successfulOutcome.value.u.sztKillResp.pres), PRSNT_NODEF);
      szFillTknU16(&(killRespPdu->pdu.val.successfulOutcome.value.u.sztKillResp.protocolIEs.noComp), numComp);
                                                                                                              
      if ((cmGetMem(killRespPdu, (numComp * sizeof(SztProtIE_Field_KillRespIEs)),
             (Ptr *)&killRespPdu->pdu.val.successfulOutcome.value.u.sztKillResp.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillKillResp: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {

         ie = &killRespPdu->pdu.val.successfulOutcome.value.u.sztKillResp.protocolIEs.member[0];
                                                                                                              
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MsgIdentifier);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         
         len = 16;
         szFillTknBStr32(&(ie->value.u.sztMsgIdentifier), len, 100);

         ie = &killRespPdu->pdu.val.successfulOutcome.value.u.sztKillResp.protocolIEs.member[1];
                                                                                                              
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_SerialNumber);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         
         len = 16;
         szFillTknBStr32(&(ie->value.u.sztMsgIdentifier), len, 100);

         ie = &killRespPdu->pdu.val.successfulOutcome.value.u.sztKillResp.protocolIEs.member[2];
         
         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_BroadcastCancelledAreaLst);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);

         szFillTknU8(&(ie->value.u.sztBroadcastCancelledAreaLst.choice), BROADCASTCANCELLEDAREALST_CELLID_CANCELLED);

         numComp = 1;
         szFillTknU16(&(ie->value.u.sztBroadcastCancelledAreaLst.val.cellID_Cancelled.noComp), numComp);

         if ((cmGetMem(killRespPdu, (numComp * sizeof(SztCellID_Cancelled_Item)),
                    (Ptr *)&ie->value.u.sztBroadcastCancelledAreaLst.val.cellID_Cancelled.member)) !=ROK)
         {
#ifndef SZ_ENC_DEC
            CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillKillResp: cmGetMem failed, line %d\n",__LINE__));
#endif
            RETVALUE(RFAILED);
         }

         ie1 = &ie->value.u.sztBroadcastCancelledAreaLst.val.cellID_Cancelled.member[0];

         szFillTknU8(&(ie1->pres), PRSNT_NODEF);
         szFillTknU8(&(ie1->eCGI.pres), PRSNT_NODEF);
         cmMemset(pLMNId, 0, sizeof(pLMNId));
         strcpy((char *)pLMNId, "111");
         len = 3;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif
         szFillTknStrOSXL(&(ie1->eCGI.pLMNidentity), len, pLMNId, &killRespPdu);     

         len = 28;
         szFillTknBStr32(&(ie1->eCGI.cell_ID), len, 100);
         
         ie1->eCGI.iE_Extns.noComp.pres = NOTPRSNT;

         nBroadcastRqst = 65535;
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"nBroadcastRqst", &(nBroadcastRqst));
#endif /* SZ_ENC_DEC */
         szFillTknU32(&(ie1->numberOfBroadcasts), nBroadcastRqst);
                  
       }
   }
                                                                                                              
   *pdu = killRespPdu;
                                                                                                              
   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillDlnkUeAssocLppaTprt
*
*       Desc:  Call handler to fill Downlink Ue Associated  LPPa Transport
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
PUBLIC S16 szAcUtlSztFillDlnkUeAssocLppaTprt
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillDlnkUeAssocLppaTprt(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillDlnkUeAssocLppaTprt
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillDlnkUeAssocLppaTprt(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *dlnkUeAssocLppaTprtPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
   U32        routingId;
   U16        len;
   U8         lppaPdu[8];
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs *ie;

   TRC2(szAcUtlSztFillDlnkUeAssocLppaTprt);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&dlnkUeAssocLppaTprtPdu);

   cmMemset((U8 *)&(dlnkUeAssocLppaTprtPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(dlnkUeAssocLppaTprtPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(dlnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(dlnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.procedureCode), Sztid_downlinkUEAssociatedLPPaTport);
   szFillTknU32(&(dlnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 4;
      szFillTknU8(&(dlnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztDlnkUEAssociatedLPPaTport.pres), PRSNT_NODEF);
      szFillTknU16(&(dlnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztDlnkUEAssociatedLPPaTport.protocolIEs.noComp), numComp);

      if ((cmGetMem(dlnkUeAssocLppaTprtPdu, (numComp * sizeof(SztProtIE_Field_DlnkUEAssociatedLPPaTport_IEs)), 
             (Ptr *)&dlnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztDlnkUEAssociatedLPPaTport.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillDlnkUEAssociatedLPPaTport: cmGetMem failed, line %d\n",__LINE__));
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
#endif   /* SZ_ENC_DEC */

         ie = &dlnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztDlnkUEAssociatedLPPaTport.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &dlnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztDlnkUEAssociatedLPPaTport.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"routingId",&(routingId));
#else
         routingId = 255;
#endif
         ie = &dlnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztDlnkUEAssociatedLPPaTport.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Routing_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztRouting_ID), routingId);

         ie = &dlnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztDlnkUEAssociatedLPPaTport.protocolIEs.member[3];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_LPPa_PDU);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         cmMemset(lppaPdu, 0, sizeof(lppaPdu));
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lppaPdu", &(lppaPdu));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "lppaPduLen", &(len));
#else
         strcpy((char *)lppaPdu, "111");
         len = 3;
#endif /* SZ_ENC_DEC */
         szFillTknStrOSXL(&(ie->value.u.sztLPPa_PDU), len, lppaPdu, &dlnkUeAssocLppaTprtPdu);
         
      }
   }

   *pdu = dlnkUeAssocLppaTprtPdu;

   RETVALUE(ROK);   
}

/*
*
*       Fun:   szAcUtlSztFillUlnkUeAssocLppaTprt
*
*       Desc:  Call handler to fill Downlink Ue Associated  LPPa Transport
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
PUBLIC S16 szAcUtlSztFillUlnkUeAssocLppaTprt
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUlnkUeAssocLppaTprt(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUlnkUeAssocLppaTprt
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUlnkUeAssocLppaTprt(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *ulnkUeAssocLppaTprtPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        enbId;
   U32        mmeId;
   U32        routingId;
   U16        len;
   U8         lppaPdu[8];
#ifndef SZ_ENC_DEC
   ProcId     procId = 0;
   UConnId    suConnId = 0;
#endif
   SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs *ie;

   TRC2(szAcUtlSztFillUlnkUeAssocLppaTprt);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&ulnkUeAssocLppaTprtPdu);

   cmMemset((U8 *)&(ulnkUeAssocLppaTprtPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(ulnkUeAssocLppaTprtPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(ulnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(ulnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.procedureCode), Sztid_uplinkUEAssociatedLPPaTport);
   szFillTknU32(&(ulnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 4;
      szFillTknU8(&(ulnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztUlnkUEAssociatedLPPaTport.pres), PRSNT_NODEF);
      szFillTknU16(&(ulnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztUlnkUEAssociatedLPPaTport.protocolIEs.noComp), numComp);

      if ((cmGetMem(ulnkUeAssocLppaTprtPdu, (numComp * sizeof(SztProtIE_Field_UlnkUEAssociatedLPPaTport_IEs)), 
             (Ptr *)&ulnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztUlnkUEAssociatedLPPaTport.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUlnkUEAssociatedLPPaTport: cmGetMem failed, line %d\n",__LINE__));
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
#endif   /* SZ_ENC_DEC */

         ie = &ulnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztUlnkUEAssociatedLPPaTport.protocolIEs.member[0];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_MME_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztMME_UE_S1AP_ID), mmeId);

         ie = &ulnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztUlnkUEAssociatedLPPaTport.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_eNB_UE_S1AP_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztENB_UE_S1AP_ID), enbId);

#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"routingId",&(routingId));
#else
         routingId = 255;
#endif
         ie = &ulnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztUlnkUEAssociatedLPPaTport.protocolIEs.member[2];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Routing_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztRouting_ID), routingId);

         ie = &ulnkUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztUlnkUEAssociatedLPPaTport.protocolIEs.member[3];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_LPPa_PDU);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         cmMemset(lppaPdu, 0, sizeof(lppaPdu));
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lppaPdu", &(lppaPdu));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "lppaPduLen", &(len));
#else
         strcpy((char *)lppaPdu, "111");
         len = 3;
#endif /* SZ_ENC_DEC */
         szFillTknStrOSXL(&(ie->value.u.sztLPPa_PDU), len, lppaPdu, &ulnkUeAssocLppaTprtPdu);
         
      }
   }

   *pdu = ulnkUeAssocLppaTprtPdu;

   RETVALUE(ROK);   
}
  
/*
*
*       Fun:   szAcUtlSztFillDlnkNonUeAssocLppaTprt
*
*       Desc:  Call handler to fill Downlink Non Ue Associated  LPPa Transport
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
PUBLIC S16 szAcUtlSztFillDlnkNonUeAssocLppaTprt
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillDlnkNonUeAssocLppaTprt(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillDlnkNonUeAssocLppaTprt
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillDlnkNonUeAssocLppaTprt(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *dlnkNonUeAssocLppaTprtPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        routingId;
   U16        len;
   U8         lppaPdu[8];
   SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs *ie;

   TRC2(szAcUtlSztFillDlnkNonUeAssocLppaTprt);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&dlnkNonUeAssocLppaTprtPdu);

   cmMemset((U8 *)&(dlnkNonUeAssocLppaTprtPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(dlnkNonUeAssocLppaTprtPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(dlnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(dlnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.procedureCode), Sztid_downlinkNonUEAssociatedLPPaTport);
   szFillTknU32(&(dlnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 2;
      szFillTknU8(&(dlnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztDlnkNonUEAssociatedLPPaTport.pres), PRSNT_NODEF);
      szFillTknU16(&(dlnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztDlnkNonUEAssociatedLPPaTport.protocolIEs.noComp), numComp);

      if ((cmGetMem(dlnkNonUeAssocLppaTprtPdu, (numComp * sizeof(SztProtIE_Field_DlnkNonUEAssociatedLPPaTport_IEs)), 
             (Ptr *)&dlnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztDlnkNonUEAssociatedLPPaTport.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillDlnkNonUeAssociatedLPPaTport: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {

         ie = &dlnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztDlnkNonUEAssociatedLPPaTport.protocolIEs.member[0];

#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"routingId",&(routingId));
#else
         routingId = 255;
#endif

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Routing_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztRouting_ID), routingId);

         ie = &dlnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztDlnkNonUEAssociatedLPPaTport.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_LPPa_PDU);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         cmMemset(lppaPdu, 0, sizeof(lppaPdu));
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lppaPdu", &(lppaPdu));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "lppaPduLen", &(len));
#else
         strcpy((char *)lppaPdu, "111");
         len = 3;
#endif /* SZ_ENC_DEC */
         szFillTknStrOSXL(&(ie->value.u.sztLPPa_PDU), len, lppaPdu, &dlnkNonUeAssocLppaTprtPdu);
         
      }
   }

   *pdu = dlnkNonUeAssocLppaTprtPdu;

   RETVALUE(ROK);   
}

/*
*
*       Fun:   szAcUtlSztFillUlnkNonUeAssocLppaTprt
*
*       Desc:  Call handler to fill Downlink Non Ue Associated  LPPa Transport
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
PUBLIC S16 szAcUtlSztFillUlnkNonUeAssocLppaTprt
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
S1apPdu    **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUlnkNonUeAssocLppaTprt(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
S1apPdu    **pdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillUlnkNonUeAssocLppaTprt
(
S1apPdu     **pdu
)
#else
PUBLIC S16 szAcUtlSztFillUlnkNonUeAssocLppaTprt(pdu)
S1apPdu     **pdu;
#endif
#endif   /* SZ_ENC_DEC */
{
   S1apPdu   *ulnkNonUeAssocLppaTprtPdu = NULLP;
   S16        numComp;
   S16        ret;
   Mem        mem; 
   U32        routingId;
   U16        len;
   U8         lppaPdu[8];
   SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs *ie;

   TRC2(szAcUtlSztFillUlnkNonUeAssocLppaTprt);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(S1apPdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&ulnkNonUeAssocLppaTprtPdu);

   cmMemset((U8 *)&(ulnkNonUeAssocLppaTprtPdu->pdu), 0, sizeof(S1apPdu) - sizeof(CmMemListCp));

   szFillTknU8(&(ulnkNonUeAssocLppaTprtPdu->pdu.choice), S1AP_PDU_INITIATINGMSG);
   szFillTknU8(&(ulnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   szFillTknU32(&(ulnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.procedureCode), Sztid_uplinkNonUEAssociatedLPPaTport);
   szFillTknU32(&(ulnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.criticality), SztCriticalityrejectEnum);

   {
      numComp = 2;
      szFillTknU8(&(ulnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztUlnkNonUEAssociatedLPPaTport.pres), PRSNT_NODEF);
      szFillTknU16(&(ulnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztUlnkNonUEAssociatedLPPaTport.protocolIEs.noComp), numComp);

      if ((cmGetMem(ulnkNonUeAssocLppaTprtPdu, (numComp * sizeof(SztProtIE_Field_UlnkNonUEAssociatedLPPaTport_IEs)), 
             (Ptr *)&ulnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztUlnkNonUEAssociatedLPPaTport.protocolIEs.member)) !=ROK)
      {
#ifndef SZ_ENC_DEC
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillUlnkNonUeAssociatedLPPaTport: cmGetMem failed, line %d\n",__LINE__));
#endif
         RETVALUE(RFAILED);
      }

      {

         ie = &ulnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztUlnkNonUEAssociatedLPPaTport.protocolIEs.member[0];

#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"routingId",&(routingId));
#else
         routingId = 255;
#endif

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_Routing_ID);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         szFillTknU32(&(ie->value.u.sztRouting_ID), routingId);

         ie = &ulnkNonUeAssocLppaTprtPdu->pdu.val.initiatingMsg.value.u.sztUlnkNonUEAssociatedLPPaTport.protocolIEs.member[1];

         szFillTknU8(&(ie->pres), PRSNT_NODEF);
         szFillTknU32(&(ie->id), Sztid_LPPa_PDU);
         szFillTknU32(&(ie->criticality), SztCriticalityrejectEnum);
         cmMemset(lppaPdu, 0, sizeof(lppaPdu));
#ifndef SZ_ENC_DEC
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "lppaPdu", &(lppaPdu));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "lppaPduLen", &(len));
#else
         strcpy((char *)lppaPdu, "111");
         len = 3;
#endif /* SZ_ENC_DEC */
         szFillTknStrOSXL(&(ie->value.u.sztLPPa_PDU), len, lppaPdu, &ulnkNonUeAssocLppaTprtPdu);
         
      }
   }

   *pdu = ulnkNonUeAssocLppaTprtPdu;

   RETVALUE(ROK);   
}
#endif /* S1AP_REL8A0 */

#ifndef SZ_ENC_DEC
/*
*
*       Fun:   szAcUtlSztGetErrCause 
*
*       Desc:  This function gets cause type and cause value
*              from error message.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcUtlSztGetErrCause
(
SztS1AP_PDU    *pdu,
U8             *causeType,
U32            *causeVal
)
#else
PUBLIC S16 szAcUtlSztGetErrCause(pdu,causeType,causeVal)
SztS1AP_PDU    *pdu;
U8             *causeType;
U32            *causeVal;
#endif
{
   TknU8  *ie;

   TRC2(szAcUtlSztGetErrCause);

   ie = NULLP;

#ifndef SZ_ENC_DEC
   szGetIE(pdu, Sztid_Cause, (TknU8 **)&ie);
#endif

   if(ie == NULLP)
   {
       RETVALUE(RFAILED);
   }

   *causeType   = ((SztCause *)ie)->choice.val;

   switch(*causeType)
   {
      case CAUSE_RADIONW: 
   
         *causeVal    = ((SztCause *)ie)->val.radioNw.val;
         break;

      case CAUSE_TRANSPORT:
         *causeVal    = ((SztCause *)ie)->val.transport.val;
         break;
         
         
      case CAUSE_NAS:
         *causeVal    = ((SztCause *)ie)->val.nas.val;
         break;

      case CAUSE_PROTOCOL:
         *causeVal    = ((SztCause *)ie)->val.protocol.val;
         break;
            
      case CAUSE_MISC:
         *causeVal    = ((SztCause *)ie)->val.misc.val;
         break;

      default:       
         RETVALUE(RFAILED);
         break;
   }  

   RETVALUE(ROK);
}

/*
*
*       Fun:   szAcUtlSztFillEncReqPdu 
*
*       Desc:  Call handler to encode Pdu
*              message.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillEncReqPdu
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
SztEncDecEvnt *sztEncDecEvnt
)
#else
PUBLIC S16 szAcUtlSztFillEncReqPdu(tcCb, spCb, sztEncDecEvnt)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
SztEncDecEvnt  *sztEncDecEvnt;
#endif
{
   U8         eventType = 0;

   TRC2(szAcUtlSztFillEncReqPdu);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillEncReqPdu(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillEncReqPdu(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"eventType",&(eventType));

   switch(eventType)
   {
      case SZT_MSG_ID_SETUP_REQ:
           szAcUtlSztFillS1SetupReq(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_SETUP_RSP:
           szAcUtlSztFillS1SetupRsp_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_SETUP_FAIL:
           szAcUtlSztFillS1SetupFail(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_INIT_UE_MSG:
           szAcUtlSztFillInitUeMsg_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_CXT_SETUP_REQ:
           szAcUtlSztFillInitCxtSetupReq_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_CXT_SETUP_RSP:
           szAcUtlSztFillInitCxtSetupRsp(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_INIT_CXT_SETUP_FAIL:
           szAcUtlSztFillInitCxtSetupFail(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_UL_NAS_TPT:
           szAcUtlSztFillUplnkNasTpt_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_DL_NAS_TPT:
           szAcUtlSztFillDwnlnkNasTpt_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_NAS_NON_DEL_IND:
           szAcUtlSztFillNasNonDlvryInd(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_RESET:
           szAcUtlSztFillReset(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_RESET_ACK:
           szAcUtlSztFillResetAck(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_UE_CXT_MOD_FAIL:
           szAcUtlSztFillUeCxtModFail(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_UE_CXT_REL_CMD:
           szAcUtlSztFillUeCxtRlsCmd(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_UE_CXT_REL_CMPL:
           szAcUtlSztFillUeCxtRlsCmpl(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_UE_CXT_REL_REQ:
           szAcUtlSztFillUeCxtRlsReq_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_ERR_IND:
           szAcUtlSztFillErrInd(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_PAGING:
           szAcUtlSztFillPaging_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_E_RAB_BRR_MOD_REQ:
           szAcUtlSztFillE_RABMdfyRqst(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_E_RAB_BRR_MOD_RSP:
           szAcUtlSztFillE_RABMdfyResp(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_E_RAB_BRR_SETUP_REQ:
           szAcUtlSztFillE_RABSetupRqst_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_E_RAB_BRR_SETUP_RSP:
           szAcUtlSztFillE_RABSetupResp(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_E_RAB_BRR_REL_CMD:
           szAcUtlSztFillE_RABRlsCmmd(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_E_RAB_BRR_REL_CMPLT:
           szAcUtlSztFillE_RABRlsResp(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_E_RAB_BRR_REL_REQ:
           szAcUtlSztFillE_RABRlsInd(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_UE_CXT_MOD_REQ:
           szAcUtlSztFillUECntxtModRqst(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_UE_CXT_MOD_RSP:
           szAcUtlSztFillUECntxtModResp(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_HO_REQ:
           szAcUtlSztFillHovrRqst_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_PATH_SWTCH_REQ:
           szAcUtlSztFillPathSwRqst_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_HO_REQ_ACK:
           szAcUtlSztFillHovrRqstAckg(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_PATH_SWTCH_REQ_ACK:
           szAcUtlSztFillPathSwRqstAckg(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_HO_FAIL:
           szAcUtlSztFillHovrFail(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_PATH_SWTCH_REQ_FAIL:
           szAcUtlSztFillPathSwRqstFail(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_HO_REQD:
           szAcUtlSztFillHovrReqd(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_HO_CMD:
           szAcUtlSztFillHovrCmmd(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_HO_PREP_FAIL:
           szAcUtlSztFillHovrPrepFail(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_HO_NTFY:
           szAcUtlSztFillHovrNtfy(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_HO_CANCEL:
           szAcUtlSztFillHovrCancel(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_HO_CANCEL_ACK:
           szAcUtlSztFillHovrCancelAckg(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_ENB_STA_TRFR:
           szAcUtlSztFillENBStatusTfr(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_MME_STA_TRFR:
           szAcUtlSztFillMMEStatusTfr(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_DEACTV_TRACE:
           szAcUtlSztFillDeactvTrace(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
            break;

      case SZT_MSG_ID_TRACE_START:
           szAcUtlSztFillTraceStart_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_TRACE_FAIL_IND:
           szAcUtlSztFillTraceFailInd(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_LOC_REPORT_CNTRL:
           szAcUtlSztFillLocRprtngCntrl(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_LOC_REPORT_FAIL_IND:
           szAcUtlSztFillLocRprtngFailInd(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_LOC_REPORT:
           szAcUtlSztFillLocReport(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_ENB_CFG_UPD:
           szAcUtlSztFillENBConfigUpd(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_ENB_CFG_UPD_ACK:
           szAcUtlSztFillENBConfigUpdAckg(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_ENB_CFG_UPD_FAIL:
           szAcUtlSztFillENBConfigUpdFail(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_MME_CFG_UPD:
           szAcUtlSztFillMMEConfigUpd(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_MME_CFG_UPD_ACK:
           szAcUtlSztFillMMEConfigUpdAckg(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_MME_CFG_UPD_FAIL:
           szAcUtlSztFillMMEConfigUpdFail(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_UPLNK_CDMA_TUNNL:
           szAcUtlSztFillUlnkS1cdma2000tunneling(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_DNLNK_CDMA_TUNNL:
           szAcUtlSztFillDlnkS1cdma2000tunneling(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_UE_CAP_INFO:
           szAcUtlSztFillUECapbltyInfoInd(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_OVLD_START:
           szAcUtlSztFillOverloadStart_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_OVLD_STOP:
           szAcUtlSztFillOverloadStop_r9(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_WARNING_REQ:
           szAcUtlSztFillWriteReplaceWarningRqst(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_WARNING_RSP:
           szAcUtlSztFillWriteReplaceWarningResp(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_ENB_DIR_TRANS:
           szAcUtlSztFillENBDirectInformTfr(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_MME_DIR_TRANS:
           szAcUtlSztFillMMEDirectInformTfr(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_NO_DATA:
           szAcUtlSztFillInvalidPdu(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;
      
#ifndef S1AP_REL8A0
      case SZT_MSG_ID_KILL_REQ:
           szAcUtlSztFillKillRqst(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;
           
      case SZT_MSG_ID_KILL_RSP:
           szAcUtlSztFillKillResp(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;

      case SZT_MSG_ID_DNLNK_NON_UE_ASSOC_LPPA_TPRT:
           szAcUtlSztFillDlnkNonUeAssocLppaTprt(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;
           
      case SZT_MSG_ID_UPLNK_NON_UE_ASSOC_LPPA_TPRT:
           szAcUtlSztFillUlnkNonUeAssocLppaTprt(tcCb, spCb, &(sztEncDecEvnt->u.pdu));
           break;
#endif
      default:
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillEncReqPdu: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

#endif /*  SZ_ENC_DEC */

/* sz004.301: Added for TC Dec/Enc */
#ifdef SZTV1
#ifndef SZ_ENC_DEC

/*
*
*       Fun:   szAcUtlSztFillEncReqIe 
*
*       Desc:  Call handler to encode IE
*              message.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillEncReqIe
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
SztEncDecEvnt *sztEncDecEvnt
)
#else
PUBLIC S16 szAcUtlSztFillEncReqIe(tcCb, spCb, sztEncDecEvnt)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
SztEncDecEvnt  *sztEncDecEvnt;
#endif
{
   U8         ieType = 0;

   TRC2(szAcUtlSztFillEncReqIe);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillEncReqIe(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "szAcUtlSztFillEncReqIe(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"ieType",&(ieType));

   if (ieType == 1)
   {
     ieType = SZT_REQ_TYPE_ENCDEC_IE_SRCTGET;
   }
   else if (ieType == 2)
   {
     ieType = SZT_REQ_TYPE_ENCDEC_IE_TGETSRC;
   }
#ifdef SZTV3
   /* sz008.301 support for Source RNC to Taarget RNC */
   else if (ieType == 3)
   {
     ieType = SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC;
   }
   else if(ieType == 4)
   {
     ieType = SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC;
   }
#endif

   switch(ieType)
   {
      case SZT_REQ_TYPE_ENCDEC_IE_SRCTGET:
           szAcUtlSztFillSrcToTget(tcCb, spCb, &(sztEncDecEvnt->u.iePdu));
           szFillTknU8(&(sztEncDecEvnt->ieType),PRSNT_NODEF);
           sztEncDecEvnt->ieType.val = SZT_REQ_TYPE_ENCDEC_IE_SRCTGET;
           break;

      case SZT_REQ_TYPE_ENCDEC_IE_TGETSRC:
           szAcUtlSztFillTgetToSrc(tcCb, spCb, &(sztEncDecEvnt->u.iePdu));
           szFillTknU8(&(sztEncDecEvnt->ieType),PRSNT_NODEF);
           sztEncDecEvnt->ieType.val = SZT_REQ_TYPE_ENCDEC_IE_TGETSRC;
           break;
#ifdef SZTV3        
   /* sz008.301 support for Source RNC to Taarget RNC */
      case SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC:
           szAcUtlSztFillSrcRncToTgetRnc(tcCb, spCb, &(sztEncDecEvnt->u.iePdu));
           szFillTknU8(&(sztEncDecEvnt->ieType),PRSNT_NODEF);
           sztEncDecEvnt->ieType.val = SZT_REQ_TYPE_ENCDEC_IE_SRCRNCTGETRNC;
           break;

      case SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC:
           szAcUtlSztFillTgetRncToSrcRnc(tcCb, spCb, &(sztEncDecEvnt->u.iePdu));
           szFillTknU8(&(sztEncDecEvnt->ieType),PRSNT_NODEF);
           sztEncDecEvnt->ieType.val = SZT_REQ_TYPE_ENCDEC_IE_TGETRNCSRCRNC;
           break;
#endif
     default:
         CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillEncReqIe: Invalid Msg, msg = %d line =  %d\n",
                        ieType,__LINE__));
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}
 
 
#endif /* SZ_ENC_DEC */
/*                                                             
*
*       Fun:   szFillTknStrOSXLIe
*
*       Desc:  Call handler to fill Octet string for Ie
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  szac_sztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 szFillTknStrOSXLIe
(
TknStrOSXL    *ptr,     /* Pointer to the structure */
U16           len,     /* length to be filled */
Data          *val,     /* byte to be repetitively filled in */
CmMemListCp   *memCp
)
#else
PUBLIC S16 szFillTknStrOSXLIe(ptr, len, val, memCp)
TknStrOSXL    *ptr;  /* Pointer to the structure */
U16           len;  /* lenrah to be filled */
Data          *val;  /* byte to be repetitively filled in */
CmMemListCp   *memCp;
#endif
{
   U16     i;     /* counter */

   TRC2(szFillTknStrOSXLIe)

   /* make the element as present */
   ptr->pres = TRUE;
   ptr->len =  len;

   if (cmGetMem(memCp, len * sizeof(U8), (Ptr *)&ptr->val) != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szFillTknStrOSXLIe: cmGetMem failed, line %d\n",__LINE__));
#endif /* SZ_ENC_DEC */
      RETVALUE(RFAILED);
   }

   for(i = 0; i < len; i++)
   {
      ptr->val[i] = val[i];
   }

   RETVALUE(ROK);

} /* End of szFillTknStrOSXLIe */
 
 
/*
*
*       Fun:   szAcUtlSztFillTgetToSrc
*
*       Desc:  Call handler to fill target to source IE
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
PUBLIC S16 szAcUtlSztFillTgetToSrc
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SzIePdu      **iePdu
)
#else
PUBLIC S16 szAcUtlSztFillTgetToSrc(tcCb, spCb, iePdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SzIePdu      **iePdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillTgetToSrc
(
SzIePdu      **iePdu
)
#else
PUBLIC S16 szAcUtlSztFillTgetToSrc(iePdu)
SzIePdu      **iePdu;
#endif 
#endif 
{
   SzIePdu *szTgetToSrcIePdu = NULLP;

   Mem     mem;
   U8      name[10];
   S16     ret;
   U16     len;


   TRC2(szAcUtlSztFillTgetToSrc);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(SzIePdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szTgetToSrcIePdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillTgetToSrc: cmAllocEvnt failed, line %d\n",__LINE__));
#endif 
      RETVALUE(RFAILED);
   }

   *iePdu = szTgetToSrcIePdu;

   szFillTknU8(&((*iePdu)->u.tgetToSrc.pres),PRSNT_NODEF);
   (*iePdu)->u.tgetToSrc.rRC_Cont.pres = PRSNT_NODEF;
   cmMemset(name,0,sizeof(name));
   strcpy((char *)name,"TgetToSrc"); 
   len = 9;
   szFillTknStrOSXLIe(&((*iePdu)->u.tgetToSrc.rRC_Cont), len, name, &((*iePdu)->memCp));     
   (*iePdu)->u.tgetToSrc.iE_Extns.noComp.pres = NOTPRSNT;

   RETVALUE(ROK);

} /* End of szAcUtlSztFillTgetToSrc */
 
/*
*
*       Fun:   szAcUtlSztFillSrcToTget
*
*       Desc:  Call handler to fill Source to target IE
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
PUBLIC S16 szAcUtlSztFillSrcToTget
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SzIePdu      **iePdu
)
#else
PUBLIC S16 szAcUtlSztFillSrcToTget(tcCb, spCb, iePdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SzIePdu      **iePdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillSrcToTget
(
U8           type, 
SzIePdu      **iePdu
)
#else
PUBLIC S16 szAcUtlSztFillSrcToTget(type, iePdu)
U8           type;   
SzIePdu      **iePdu;
#endif 
#endif 
{
   SzIePdu *szSrcToTgetIePdu = NULLP;

   Mem     mem;
   U16     numComp;
   U8      pLMNId[10];
   U8      name[10];
   S16     ret;
   U16     len;
   U8      choice;

   SztProtIE_SingleCont_E_RABInformLstIEs *ie;
   SztLastVisitedCell_Item *ie1;

   TRC2(szAcUtlSztFillSrcToTget);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(SzIePdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szSrcToTgetIePdu);

   *iePdu = szSrcToTgetIePdu;

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillSrcToTget: cmAllocEvnt failed, line %d\n",__LINE__));
#endif 
      RETVALUE(RFAILED);
   }

   szFillTknU8(&((*iePdu)->u.srcToTget.pres),PRSNT_NODEF);
   (*iePdu)->u.srcToTget.rRC_Cont.pres = PRSNT_NODEF;
   cmMemset(name,0,sizeof(name));
   strcpy((char *)name,"SrcToTget"); 
   len = 1;
   szFillTknStrOSXLIe(&((*iePdu)->u.srcToTget.rRC_Cont), len, name, &((*iePdu)->memCp));     

   numComp = 1;
   szFillTknU16(&((*iePdu)->u.srcToTget.e_RABInformLst.noComp),numComp);

   if ((cmGetMem(szSrcToTgetIePdu, numComp*sizeof(SztProtIE_SingleCont_E_RABInformLstIEs), 
               (Ptr*)&(*iePdu)->u.srcToTget.e_RABInformLst.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillSrcToTget: cmGetMem failed, line %d\n",__LINE__));
#endif 
      RETVALUE(RFAILED);
   }


   szFillTknU8(&((*iePdu)->u.srcToTget.e_RABInformLst.member->pres),PRSNT_NODEF);
   szFillTknU32(&((*iePdu)->u.srcToTget.e_RABInformLst.member->id),Sztid_E_RABInformLstItem);
   szFillTknU32(&((*iePdu)->u.srcToTget.e_RABInformLst.member->criticality),SztCriticalityignoreEnum);

   ie =&((*iePdu)->u.srcToTget.e_RABInformLst.member[0]);

   szFillTknU8(&(ie->value.u.sztE_RABInformLstItem.pres),PRSNT_NODEF);
   szFillTknU32(&(ie->value.u.sztE_RABInformLstItem.e_RAB_ID),Sztid_E_RABInformLstItem);
   szFillTknU32(&(ie->value.u.sztE_RABInformLstItem.dL_Fwding), SztDL_FwdingdL_Fwding_proposedEnum);
   ie->value.u.sztE_RABInformLstItem.iE_Extns.noComp.pres = NOTPRSNT;

   szFillTknU8(&((*iePdu)->u.srcToTget.targetCell_ID.pres),PRSNT_NODEF);
   cmMemset(pLMNId,0,sizeof(pLMNId));
   strcpy((char *)pLMNId,"111");
   len = 3;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif

   szFillTknU8(&((*iePdu)->u.srcToTget.targetCell_ID.pres), PRSNT_NODEF);
   szFillTknStrOSXLIe(&((*iePdu)->u.srcToTget.targetCell_ID.pLMNidentity), len, pLMNId, &((*iePdu)->memCp));      

   len = 28;
#ifndef SZ_ENC_DEC
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"tacLen",&(len));
#endif
   szFillTknBStr32(&((*iePdu)->u.srcToTget.targetCell_ID.cell_ID),(U8)len, 1);
   (*iePdu)->u.srcToTget.targetCell_ID.iE_Extns.noComp.pres = NOTPRSNT;

   szFillTknU32(&((*iePdu)->u.srcToTget.subscriberProfileIDforRFP),1);

   numComp = 1;
   szFillTknU16(&((*iePdu)->u.srcToTget.uE_HistoryInform.noComp),numComp);
 
   if ((cmGetMem(szSrcToTgetIePdu, numComp*sizeof(SztLastVisitedCell_Item), 
               (Ptr*)&(*iePdu)->u.srcToTget.uE_HistoryInform.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillSrcToTget: cmGetMem failed, line %d\n",__LINE__));
#endif
      RETVALUE(RFAILED);
   }

   ie1 = &((*iePdu)->u.srcToTget.uE_HistoryInform.member[0]);
 
#ifndef SZ_ENC_DEC
   choice = LASTVISITEDCELL_ITEM_E_UTRAN_CELL;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,"choice",&(choice));
#endif

#ifdef SZ_ENC_DEC
   choice = type;
#endif

   if (choice == 1)
   {
      choice = LASTVISITEDCELL_ITEM_UTRAN_CELL;
   }
   else if (choice == 2)
   {
      choice = LASTVISITEDCELL_ITEM_GERAN_CELL;
   }

   switch (choice)
   {
      case LASTVISITEDCELL_ITEM_E_UTRAN_CELL:
         {
            szFillTknU8(&(ie1->choice), choice);
            szFillTknU8(&(ie1->val.e_UTRAN_Cell.pres),PRSNT_NODEF);
            szFillTknU8(&(ie1->val.e_UTRAN_Cell.global_Cell_ID.pres),PRSNT_NODEF);

            cmMemset(pLMNId,0,sizeof(pLMNId));
            strcpy((char *)pLMNId,"111");
            len = 3;
#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif

            szFillTknStrOSXLIe(&(ie1->val.e_UTRAN_Cell.global_Cell_ID.pLMNidentity), len, pLMNId, &((*iePdu)->memCp));      

            len = 28;
#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"tacLen",&(len));
#endif
            szFillTknBStr32(&(ie1->val.e_UTRAN_Cell.global_Cell_ID.cell_ID),(U8)len, 1);
            ie1->val.e_UTRAN_Cell.global_Cell_ID.iE_Extns.noComp.pres = NOTPRSNT;

            szFillTknU8(&(ie1->val.e_UTRAN_Cell.cellTyp.pres),PRSNT_NODEF);
            szFillTknU32(&(ie1->val.e_UTRAN_Cell.cellTyp.cell_Size),2);
            ie1->val.e_UTRAN_Cell.cellTyp.iE_Extns.noComp.pres = NOTPRSNT;

            szFillTknU32(&(ie1->val.e_UTRAN_Cell.time_UE_StayedInCell),100);
            ie1->val.e_UTRAN_Cell.iE_Extns.noComp.pres = NOTPRSNT;
         }
         break;

      case LASTVISITEDCELL_ITEM_UTRAN_CELL:
         {
            szFillTknU8(&(ie1->choice), choice);

            ie1->val.uTRAN_Cell.pres = PRSNT_NODEF;
            cmMemset(pLMNId,0,sizeof(pLMNId));
            strcpy((char *)pLMNId,"111");
            len = 3;
#ifndef SZ_ENC_DEC
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_TXT, "plmnIdVal", &(pLMNId));
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "plmnIdLen", &(len));
#endif

            szFillTknStrOSXLIe(&(ie1->val.uTRAN_Cell), len, pLMNId, &((*iePdu)->memCp));      
 
        } 
         break;

        case LASTVISITEDCELL_ITEM_GERAN_CELL:
         {
            szFillTknU8(&(ie1->choice), choice);

            ie1->val.gERAN_Cell.choice.pres = PRSNT_NODEF;
            ie1->val.gERAN_Cell.val.unused.pres = PRSNT_NODEF;
            ie1->val.gERAN_Cell.val.unused.val = 0;

        } 
         break;

        default:
         break;
   }

   (*iePdu)->u.srcToTget.iE_Extns.noComp.pres = NOTPRSNT;


   RETVALUE(ROK);


} /* End of szAcUtlSztFillSrcToTget */
#endif  /* SZTV1 */ 

/* sz008.301 support for Source RNC to Target RNC */
#ifdef SZTV3
/*
*
*       Fun:   szAcUtlSztFillSrcRncToTgetRnc 
*
*       Desc:  Call handler to fill Source RNC to target
*              Rnc IE message.
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
PUBLIC S16 szAcUtlSztFillSrcRncToTgetRnc
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SzIePdu      **iePdu
)
#else
PUBLIC S16 szAcUtlSztFillSrcRncToTgetRnc(tcCb, spCb, iePdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SzIePdu      **iePdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillSrcRncToTgetRnc
(
SzIePdu      **iePdu
)
#else
PUBLIC S16 szAcUtlSztFillSrcRncToTgetRnc(iePdu)
SzIePdu      **iePdu;
#endif
#endif
{

   SzIePdu *szSrcrncToTgetrncIePdu = NULLP;

   Mem     mem;
   U16     numComp;
   U8      name[256];
   S16     ret;
   U16     len;

   TRC2(szAcUtlSztFillSrcRncToTgetRnc);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(SzIePdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szSrcrncToTgetrncIePdu);

   *iePdu = szSrcrncToTgetrncIePdu;

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillSrcRncToTgetRnc: cmAllocEvnt failed, line %d\n",__LINE__));
#endif 
      RETVALUE(RFAILED);
   }
   /* Filling Source RNC to Target RNC container */
   /* Filling RRC container */
   szFillTknU8(&((*iePdu)->u.srcRncToTgetRnc.pres), 1);
   (*iePdu)->u.srcRncToTgetRnc.rRC_Cont.pres = PRSNT_NODEF;
   cmMemset(name,0,sizeof(name));
   strcpy((char *)name,"SrcRncToTgetRnc"); 
   len = 15;

   szFillTknStrOSXLIe(&((*iePdu)->u.srcRncToTgetRnc.rRC_Cont), 
         len, name, &((*iePdu)->memCp));     

   /* Number of IuInstances */
   szFillTknU32(&((*iePdu)->u.srcRncToTgetRnc.numberOfIuInstances), 1);

   /* Relocation Type */
   szFillTknU32(&((*iePdu)->u.srcRncToTgetRnc.relocationTyp), SztRelocationTypue_not_involvedEnum);

   /* chosen Integrity protection algorithum */
   szFillTknU8(&((*iePdu)->u.srcRncToTgetRnc.chosenIntegrityProtectionAlgorithm), 1);

   cmMemset(name,0,sizeof(name));
   strcpy((char *)name,"SrcRncToTgetRnc"); 
   len = 128;
   szFillTknStrOSXLIe(&((*iePdu)->u.srcRncToTgetRnc.integrityProtectionKey), 
         len, name, &((*iePdu)->memCp));

   /* Encryption Algo for signalling */
   szFillTknU8(&((*iePdu)->u.srcRncToTgetRnc.chosenEncryptionAlgorithForSignalling), 1);

   /* ciphering */
   cmMemset(name,0,sizeof(name));
   strcpy((char *)name,"SrcRncToTgetRnc"); 
   len = 128;
   szFillTknStrOSXLIe(&((*iePdu)->u.srcRncToTgetRnc.cipheringKey), len, 
         name, &((*iePdu)->memCp));

   /* Chosen Encryption Algo for CS */
   szFillTknU8(&((*iePdu)->u.srcRncToTgetRnc.chosenEncryptionAlgorithForCS), 1);

   /* chosen Encryptionalgo for Ps */
   szFillTknU8(&((*iePdu)->u.srcRncToTgetRnc.chosenEncryptionAlgorithForPS), 1);

   /* D_RNTI */
   szFillTknU32(&((*iePdu)->u.srcRncToTgetRnc.d_RNTI), 1);

   /* target Cell ID */
   szFillTknU32(&((*iePdu)->u.srcRncToTgetRnc.targetCellId), 1);

   /* RAB TrCh mapping */
   numComp = 1;
   szFillTknU16(&((*iePdu)->u.srcRncToTgetRnc.rAB_TrCH_Mapping.noComp), numComp);

   if ((cmGetMem(szSrcrncToTgetrncIePdu, numComp*sizeof(SztRAB_TrCH_MappingItem), 
               (Ptr*)&(*iePdu)->u.srcRncToTgetRnc.rAB_TrCH_Mapping.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillSrcRncToTgetRnc: cmGetMem failed, line %d\n",__LINE__));
#endif 
      RETVALUE(RFAILED);
   }

   szFillTknU8(&((*iePdu)->u.srcRncToTgetRnc.rAB_TrCH_Mapping.member[0].pres), 1);

      /* RAB ID */
   len = 8;
   szFillTknBStr32(&((*iePdu)->u.srcRncToTgetRnc.rAB_TrCH_Mapping.member[0].
            rAB_ID), len, 1);

      /* trCH_ID_Lst */
   numComp = 1;
   szFillTknU16(&((*iePdu)->u.srcRncToTgetRnc.rAB_TrCH_Mapping.member[0].
            trCH_ID_Lst.noComp), numComp);
   
   numComp = 1;
   if ((cmGetMem(szSrcrncToTgetrncIePdu, numComp*sizeof(SztTrCH_ID), 
       (Ptr*)&(*iePdu)->u.srcRncToTgetRnc.rAB_TrCH_Mapping.member[0].trCH_ID_Lst.member)) !=ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillSrcRncToTgetRnc: cmGetMem failed, line %d\n",__LINE__));
#endif 
      RETVALUE(RFAILED);
   }

   /* s1apTrCH_ID */
   szFillTknU8(&((*iePdu)->u.srcRncToTgetRnc.rAB_TrCH_Mapping.member[0].
            trCH_ID_Lst.member[0].pres), 1);

   /* dSCH_ID */
   szFillTknU32(&((*iePdu)->u.srcRncToTgetRnc.rAB_TrCH_Mapping.member[0].
            trCH_ID_Lst.member[0].dSCH_ID), 1);

   /* dCH_ID */
   szFillTknU32(&((*iePdu)->u.srcRncToTgetRnc.rAB_TrCH_Mapping.member[0].
            trCH_ID_Lst.member[0].dCH_ID), 1);

   /* uSCH_ID */
   szFillTknU32(&((*iePdu)->u.srcRncToTgetRnc.rAB_TrCH_Mapping.member[0].
            trCH_ID_Lst.member[0].uSCH_ID), 1);

   /* SztProtExtnCont_TrCH_ID_ExtIEs */
   (*iePdu)->u.srcRncToTgetRnc.rAB_TrCH_Mapping.member[0].
            trCH_ID_Lst.member[0].iE_Extns.noComp.pres = NOTPRSNT;
   /* SztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs */
   (*iePdu)->u.srcRncToTgetRnc.rAB_TrCH_Mapping.member[0].iE_Extns.noComp.pres = NOTPRSNT;

   /* SztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs */
   (*iePdu)->u.srcRncToTgetRnc.iE_Extns.noComp.pres =  NOTPRSNT;

   RETVALUE(ROK);

} /* End of szAcUtlSztFillSrcRncToTgetRnc */

/*
*
*       Fun:   szAcUtlSztFillTgetRncToSrcRnc 
*
*       Desc:  Call handler to fill Source RNC to target
*              Rnc IE message.
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
PUBLIC S16 szAcUtlSztFillTgetRncToSrcRnc 
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
SzIePdu      **iePdu
)
#else
PUBLIC S16 szAcUtlSztFillTgetRncToSrcRnc(tcCb, spCb, iePdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
SzIePdu      **iePdu;
#endif
#else
#ifdef ANSI
PUBLIC S16 szAcUtlSztFillTgetRncToSrcRnc 
(
SzIePdu      **iePdu
)
#else
PUBLIC S16 szAcUtlSztFillTgetRncToSrcRnc(iePdu)
SzIePdu      **iePdu;
#endif
#endif
{

   SzIePdu *szTgtRnctoSrcRncIePdu = NULLP;

   Mem     mem;
   U8      name[20];
   S16     ret;
   U16     len;


   TRC2(szAcUtlSztFillTgetRncToSrcRnc);

   mem.region = 0;
   mem.pool   = 0;

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(SzIePdu), SZ_MEM_SDU_SIZE, &mem, (Ptr *)&szTgtRnctoSrcRncIePdu);

   if(ret != ROK)
   {
#ifndef SZ_ENC_DEC
      CMXTA_DBG_ERR((_cmxtap,"szAcUtlSztFillTgetRncToSrcRnc : cmAllocEvnt failed, line %d\n",__LINE__));
#endif 
      RETVALUE(RFAILED);
   }

   *iePdu = szTgtRnctoSrcRncIePdu;

   szFillTknU8(&((*iePdu)->u.TgetRncToSrcRnc.pres),PRSNT_NODEF);
   (*iePdu)->u.TgetRncToSrcRnc.rRC_Cont.pres = PRSNT_NODEF;
   cmMemset(name,0,sizeof(name));
   strcpy((char *)name,"TgetRncToSrcRnc"); 
   len = 15;
   szFillTknStrOSXLIe(&((*iePdu)->u.TgetRncToSrcRnc.rRC_Cont), len, 
         name, &((*iePdu)->memCp));     
   /* d_RNTI */
   szFillTknU32(&((*iePdu)->u.TgetRncToSrcRnc.d_RNTI), 1);
   /* Extn Ie's */
   (*iePdu)->u.TgetRncToSrcRnc.iE_Extns.noComp.pres = NOTPRSNT;

   RETVALUE(ROK);
} /* End of szAcUtlSztFillTgetRncToSrcRnc */

#endif 



#ifdef __cplusplus
}
#endif

/********************************************************************30**

         End of file:     szac_sztutl_r9.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:13:33 2015

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
